#ifndef _GEOTOP_PEDO_FUNCT_H
#define _GEOTOP_PEDO_FUNCT_H

/* STATEMENT:

   Geotop MODELS THE ENERGY AND WATER FLUXES AT THE LAND SURFACE
   Geotop 2.0.0 - 31 Oct 2013

   Copyright (c), 2013 - Stefano Endrizzi

   This file is part of Geotop 2.0.0

   Geotop 2.0.0  is a free software and is distributed under GNU General Public License v. 3.0 <http://www.gnu.org/licenses/>
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE

   Geotop 2.0.0  is distributed as a free software in the hope to create and support a community of developers and users that constructively interact.
   If you just use the code, please give feedback to the authors and the community.
   Any way you use the model, may be the most trivial one, is significantly helpful for the future development of the Geotop model. Any feedback will be highly appreciated.

   If you have satisfactorily used the code, please acknowledge the authors.

*/

#include "struct.geotop.h"
#include "pedo.funct.h"
#include "constants.h"
#include "math.optim.h"
#include "timer.h"
extern char **files;

/*
  in all the following subroutine
  w=theta
  i=theta_ice
  s=saturated water content
  r=residual water content
  a=alpha van genuchten
  n=n van genuchten
  m=m van genuchten
  pmin=psi min
  Ss=specific storativity
*/

/*--------------------------------------------*/
inline double psi_teta(double w, double i, double s, double r, double a, double n,
                double m, double pmin, double Ss )

{
/**
 * calculate psi from theta
 */
  double psi,TETA,TETAsat,TETAmin;
  short sat;

  TETAsat=1.0-i/(s-r);
  TETAmin=1.0/pow((1.0+pow(a*(-pmin),n)),m);

  if (w>s-i)
    {
      TETA=TETAsat;
      sat=1;
    }
  else
    {
      TETA=(w-r)/(s-r);
      sat=0;
    }

  if (TETA<TETAmin) TETA=TETAmin;

  if (TETA>1.0-1.E-6)
    {
      psi=0.0;
    }
  else
    {
      psi=(pow((pow(TETA,-1.0/m)-1.0),1.0/n))*(-1.0/a);
    }
  if (sat==1) psi += (w-(s-i))/Ss;

  return psi;
}

/*--------------------------------------------*/
inline double teta_psi(double psi, double i, double s, double r, double a, double n,
                       double m, double pmin, double Ss)
{
  /**
   * calculate theta from psi
   */
  double teta,TETA,psisat;
  short sat=0;

  psisat = (power((power(1.0-i/(s-r),-1.0/m)-1.0),1.0/n))*(-1.0/a); // power() works but NOT Padè approximation
  if (psi>psisat)
    sat=1;

  if (psi<pmin)
    psi=pmin;

  if (sat==0)
    {
      if (psi>-1.E-6)
        {
	  TETA=1.0;
        }
      else
        {
	  TETA=1.0/pow((1.0+pow(a*(-psi),n)),m);
        }
      teta=r+TETA*(s-r);
    }
  else
    {
      teta= s-i + Ss * (psi-psisat);
    }

  return teta;
}

/*--------------------------------------------*/
inline double dteta_dpsi(double psi, double i, double s, double r, double a,
                  double n, double m, double  /*pmin*/, double Ss )
/*
 * derivative of teta with respect to psi [mm^-1]
 */
{
  double dteta,psisat;

  psisat = (power((power(1.0-i/(s-r),-1.0/m)-1.0),1.0/n))*(-1.0/a); // power() works but NOT Padè approximation

  if (psi>=psisat)
    {
      dteta=Ss;
    }
  else
    {
      dteta=(s-r)*(a*m*n)*(pow(-a*psi,n-1.0))*pow(1.0+pow(-a*psi,n),-m-1.0);
    }

  return dteta;
}

/*--------------------------------------------*/
inline double k_hydr_soil(double psi, double ksat, double imp, double i, double s,
                   double r, double a, double n, double m, double v, double T, double ratio)

{
  double k,TETA,psisat;

  psisat = (power((power(1.0-i/(s-r),-1.0/m)-1.0),1.0/n))*(-1.0/a); // power() works but NOT Padè approximation
  TETA = 1.0/pow((1.0+pow(a*(-std::min<double>(psisat,psi)),n)),m); // power() does NOT work

  k = ksat * pow(TETA,v) * pow_2((1.0-pow((1.0-pow(TETA,(1.0/m))),m))); // power() does NOT work

  if (k/ksat < ratio)
    k = ratio * ksat;

  if (T>=0)
    {
      k *= (0.000158685828*T*T+0.025263459766*T+0.731495819);
    }
  else
    {
      k *= 0.731495819;
    }

  k *= (pow(10.0, -imp*i/(s-r))); // power() does NOT work

  return k;
}


inline double k_air_soil(double psi, double ksat, double i, double s,
                   double r, double a, double n, double m, double v, double ratio,double ThetaAir)

{
  double k,TETA,psisat;

  psisat = (power((power(1.0-i/(s-r),-1.0/m)-1.0),1.0/n))*(-1.0/a); // power() works but NOT Padè approximation
  TETA = 1.0/pow((1.0+pow(a*(-std::min<double>(psisat,psi)),n)),m); // power() does NOT work
  
  k = ksat * pow((1.0-TETA),v) * pow((1.0-pow(TETA,(1.0/m))),(2.0*m)); // power() does NOT work
  
  if (k/ksat < ratio){
    k = ratio * ksat;}
    
  if (ThetaAir<GTConst::ThetaAirMin){
    k = ratio * ksat;}
    
  //printf("AIR BALANCE : %f,%f,%f,%f,%f,%f,%f,%f \n",TETA,i,s,psi,v,m,k,ksat);    
  return k;
}

/*--------------------------------------------*/

inline double psi_saturation(double i, double s, double r, double a, double n,
                      double m)
{
  double psisat;

  if (i<0) i=0.;
  if (1.0-i/(s-r)>1.E-6)
    {
      psisat=(power((power(1.0-i/(s-r),-1.0/m)-1.0),1.0/n))*(-1.0/a);
    }
  else
    {
      psisat=0.0;
    }

  return (psisat);
}
/*------------------------------------------------------------------------------------------------------*/

inline double Harmonic_Mean(double D1, double D2, double K1, double K2)
/*  calculates the harmonic mean of a property K weighted on the layer depth D
 * It is used to calculate the property K at the interface between two consecutive layers K1,D1 and K2,D2
 *  mean=(D1+D2)/(D1/K1+D2/K2)
 * Author: Matteo Dall'Amico, Sept 2011 */
{
  return ((D1+D2)/(D1/K1+D2/K2));
}


inline double Arithmetic_Mean(double D1, double D2, double K1, double K2)
{
  return ((D1*K2+D2*K1)/(D1+D2));
}

/*------------------------------------------------------------------------------------------------------*/

inline double Mean(short a, double D1, double D2, double K1, double K2)
{
  if (a==0)
    {
      return (Harmonic_Mean(D1,D2,K1,K2));
    }
  else if (a==1)
    {
      return (Arithmetic_Mean(D1,D2,K1,K2));
    }
  else
    {
      return (0.0);
    }
}


/*------------------------------------------------------------------------------------------------------*/

inline double Psif(double T)
{
  if (T<0)
    {
      return T*(1000.0*GTConst::Lf)/(GTConst::g*(GTConst::Tfreezing+GTConst::tk));
    }
  return 0;
}

/******************************************************************************************************************************************/
inline double theta_from_psi(double psi, double ice, long l, MatrixView<double> &&pa,
                      double pmin)
{
  const double s = pa(jsat,l);
  const double res = pa(jres,l);
  const double a = pa(ja,l);
  const double n = pa(jns,l);
  const double m = 1.-1./n;
  const double Ss = pa(jss,l);

  return teta_psi(psi, ice, s, res, a, n, m, pmin, Ss);

}

/******************************************************************************************************************************************/
inline double psi_from_theta(double th, double ice, long l, MatrixView<double> &&pa, double pmin)
{
  const double s=pa(jsat,l);
  const double res=pa(jres,l);
  const double a=pa(ja,l);
  const double n=pa(jns,l);
  const double m=1.-1./n;
  const double Ss=pa(jss,l);

  return psi_teta(th, ice, s, res, a, n, m, pmin, Ss);
}

/******************************************************************************************************************************************/

inline double dtheta_dpsi_from_psi(double psi, double ice, long l, MatrixView<double> &&pa,
                            double pmin)
{
  const double s = pa(jsat,l);
  const double res = pa(jres,l);
  const double a = pa(ja,l);
  const double n = pa(jns,l);
  const double m = 1.-1./n;
  const double Ss = pa(jss,l);

  return dteta_dpsi(psi, ice, s, res, a, n, m, pmin, Ss);
}

/******************************************************************************************************************************************/
inline double k_from_psi(long jK, double psi, double ice, double T, long l,
                         MatrixView<double> &&pa, double imp, double ratio)
{
  const double kmax = pa(jK,l);
  const double s = pa(jsat,l);
  const double res = pa(jres,l);
  const double a = pa(ja,l);
  const double n = pa(jns,l);
  const double m = 1.-1./n;
  const double v = pa(jv,l);

  return k_hydr_soil(psi, kmax, imp, ice, s, res, a, n, m, v, T, ratio);
}

/******************************************************************************************************************************************/

 inline double kair_from_psi(long jK, double psi, double ice, long l,
                         MatrixView<double> &&pa, double ratio, double ThetaAir)
{ 
  const double kmax = pa(jK,l);
  const double s = pa(jsat,l);
  const double res = pa(jres,l);
  const double a = pa(ja,l);
  const double n = pa(jns,l);
  const double m = 1.-1./n;
  const double v = pa(jv,l);

  return k_air_soil(psi, kmax, ice, s, res, a, n, m, v,ratio,ThetaAir);
}

/******************************************************************************************************************************************/

inline double psisat_from(double ice, long l, MatrixView<double> &&pa)
{
  const double s =pa(jsat,l);
  const double res =pa(jres,l);
  const double a = pa(ja,l);
  const double n = pa(jns,l);
  const double m = 1.-1./n;

  return psi_saturation(ice, s, res, a, n, m);
}
/******************************************************************************************************************************************/

#endif
