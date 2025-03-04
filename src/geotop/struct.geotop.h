#ifndef _GEOTOP_STRUCT_GEOTOP_H
#define _GEOTOP_STRUCT_GEOTOP_H


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

#include "turtle.h"
#include "t_datamanipulation.h"
/*   #include "tensor3D.h"  */
#include <memory>
#include <algorithm>

/*---------------------------------------------------------------------------*/
typedef struct {

    std::unique_ptr<Vector<double>> Rn_mean;
    std::unique_ptr<Vector<double>> LWin_mean;
    std::unique_ptr<Vector<double>> LW_mean;
    std::unique_ptr<Vector<double>> SW_mean;
    std::unique_ptr<Vector<double>> ET_mean;
    std::unique_ptr<Vector<double>> H_mean;
    std::unique_ptr<Vector<double>> SEB_mean;
    std::unique_ptr<Vector<double>> Ts_mean;  /** averaged surface Temperature (on nDt_output_basin Dt time intervals) */
    std::unique_ptr<Vector<double>> Rswdown_mean;
    std::unique_ptr<Vector<double>> Rswbeam_mean;
    std::unique_ptr<Vector<long>> nDt_shadow;
    std::unique_ptr<Vector<long>> nDt_sun;

    std::unique_ptr<Vector<double>> Rn;
    std::unique_ptr<Vector<double>> LWin;
    std::unique_ptr<Vector<double>> LW;
    std::unique_ptr<Vector<double>> SW;
    std::unique_ptr<Vector<double>> LE;
    std::unique_ptr<Vector<double>> H;
    std::unique_ptr<Vector<double>> G;
    std::unique_ptr<Vector<double>> Ts;
    std::unique_ptr<Vector<double>> SWin;
    std::unique_ptr<Vector<double>> SWinb;
    std::unique_ptr<Vector<short>> shad;

    std::unique_ptr<Vector<double>> Hgplot;
    std::unique_ptr<Vector<double>> LEgplot;
    std::unique_ptr<Vector<double>> Hvplot;
    std::unique_ptr<Vector<double>> LEvplot;
    std::unique_ptr<Vector<double>> SWinplot;
    std::unique_ptr<Vector<double>> SWgplot;
    std::unique_ptr<Vector<double>> SWvplot;
    std::unique_ptr<Vector<double>> LWinplot;
    std::unique_ptr<Vector<double>> LWgplot;
    std::unique_ptr<Vector<double>> LWvplot;
    std::unique_ptr<Vector<double>> Tgplot;
    std::unique_ptr<Vector<double>> Tsplot;
    std::unique_ptr<Vector<double>> Tvplot;

    std::unique_ptr<Vector<double>> Hgp;
    std::unique_ptr<Vector<double>> LEgp;
    std::unique_ptr<Vector<double>> Hvp;
    std::unique_ptr<Vector<double>> LEvp;
    std::unique_ptr<Vector<double>> SWinp;
    std::unique_ptr<Vector<double>> SWgp;
    std::unique_ptr<Vector<double>> SWvp;
    std::unique_ptr<Vector<double>> LWinp;
    std::unique_ptr<Vector<double>> LWgp;
    std::unique_ptr<Vector<double>> LWvp;
    std::unique_ptr<Vector<double>> Tgp;
    std::unique_ptr<Vector<double>> Tsp;

    double *sun;
    double hsun;
    double sinhsun;
    double dsun;

    std::unique_ptr<Vector<double>> Dlayer;
    std::unique_ptr<Vector<double>> liq;
    std::unique_ptr<Vector<double>> ice;
    std::unique_ptr<Vector<double>> Temp;
    std::unique_ptr<Vector<double>> TempAir;  /**Air temperature for the 1D Energy Balance */
    std::unique_ptr<Vector<double>> deltaw;
    std::unique_ptr<Vector<double>> SWlayer;
    std::unique_ptr<Vector<double>> soil_transp_layer;  /** its size = n° of layer in which there is transpiration */
    std::unique_ptr<Vector<double>> dFenergy;
    std::unique_ptr<Vector<double>> udFenergy;
    std::unique_ptr<Vector<double>> Kth0;
    std::unique_ptr<Vector<double>> Kth1;
    std::unique_ptr<Vector<double>> Kthcm;
    std::unique_ptr<Vector<double>> Fenergy;
    std::unique_ptr<Vector<double>> Newton_dir;
    std::unique_ptr<Vector<double>> T0;
    std::unique_ptr<Vector<double>> T1;
    std::unique_ptr<Vector<double>> Tstar;
    std::unique_ptr<Vector<double>> THETA;
    std::unique_ptr<Vector<double>> THETACM;//** Composite medium volume content
    std::unique_ptr<Vector<double>> soil_evap_layer_bare; /** its size = n° of layer in which there is evaporation from bare soil */
    std::unique_ptr<Vector<double>> soil_evap_layer_veg; /** its size = n° of layer in which there is evaporation from vegetation */

    std::unique_ptr<Matrix<double>> Tgskin_surr;
    std::unique_ptr<Matrix<double>> SWrefl_surr;
    std::unique_ptr<Matrix<double>> KSnow0; // Water content of the first snow layer
    double iternumber;

} ENERGY;

/*---------------------------------------------------------------------------*/

struct SOIL_STATE {
    SOIL_STATE(const long n, const long nl);
    std::unique_ptr<Matrix<double>> P; /** psi */
    std::unique_ptr<Matrix<double>> thi; /** theta ice */
    std::unique_ptr<Matrix<double>> T; /** temperature */
    std::unique_ptr<Matrix<double>> T0; /** temperature previous time */
    std::unique_ptr<Matrix<double>> Tair_internal; /**Air temperature inside the soil */
    std::unique_ptr<Matrix<double>> Hair_internal; /**heat transfer coefficient */
    std::unique_ptr<Matrix<double>> totw0;
};


/*---------------------------------------------------------------------------*/

struct STATE_VEG {

    std::unique_ptr<Vector<double>> Tv;
    std::unique_ptr<Vector<double>> wrain; /** intercepted precipitation [mm] */
    std::unique_ptr<Vector<double>> wsnow; /** intercepted precipitation [mm] */

};

/*---------------------------------------------------------------------------*/

struct SOIL {
    std::unique_ptr<Matrix<long>> type; /** soil type map */
    std::unique_ptr<Tensor<double>> pa;
    std::unique_ptr<Matrix<double>> T_av_tensor;
    std::unique_ptr<Matrix<double>> Tair_av_tensor;
    std::unique_ptr<Matrix<double>> thw_av_tensor;
    std::unique_ptr<Matrix<double>> thi_av_tensor;
    std::unique_ptr<Matrix<double>> Ptot; /** total precipitation */
    std::unique_ptr<Matrix<double>> th; /** theta (soil water content) */

    std::unique_ptr<Tensor<double>> ET;

    std::unique_ptr<Matrix<double>> Tzplot;
    std::unique_ptr<Matrix<double>> Tzavplot;
    std::unique_ptr<Matrix<double>> Ptotzplot;
    std::unique_ptr<Matrix<double>> Pzplot;
    std::unique_ptr<Matrix<double>> thzplot;
    std::unique_ptr<Matrix<double>> thzavplot;
    std::unique_ptr<Matrix<double>> thizplot;
    std::unique_ptr<Matrix<double>> thizavplot;
    std::unique_ptr<Matrix<double>> satratio;
    std::unique_ptr<SOIL_STATE> SS;
    std::unique_ptr<STATE_VEG> VS;

    std::unique_ptr<Matrix<double>> Tzrun;
    std::unique_ptr<Matrix<double>> wzrun;
    std::unique_ptr<Matrix<double>> dUzrun;
    std::unique_ptr<Matrix<double>> SWErun;

    std::unique_ptr<Matrix<double>> Tzmaxrun;
    std::unique_ptr<Matrix<double>> wzmaxrun;
    std::unique_ptr<Matrix<double>> Tzminrun;
    std::unique_ptr<Matrix<double>> wzminrun;

    std::unique_ptr<Vector<double>> Pnetcum;
    std::unique_ptr<Vector<double>> ETcum;

};


/*---------------------------------------------------------------------------*/
typedef struct {
    std::unique_ptr<Matrix<double>> Z0; /** elevation of each pixel (DEM) [m a.s.l]*/
    std::unique_ptr<Matrix<double>> Z0S; /** elevation of each pixel (DEM) of extended Shadow DEM [m a.s.l]*/
    //std::unique_ptr<Vector<double>> UVS;  /**UV parameters of extended Shadow DEM   */
    
    std::unique_ptr<Tensor<double>> Z;

    std::unique_ptr<Matrix<double>> sky; /** sky view factor for each pixel */
    std::unique_ptr<Matrix<short>> pixel_type;

    std::unique_ptr<Matrix<double>> aspect; /** aspect; ex: matr_ev->azimuth */
    std::unique_ptr<Matrix<double>> slope; /** slope of the pixels; ex: matr_ev->slope */

    std::unique_ptr<Matrix<double>> curvature1;
    std::unique_ptr<Matrix<double>> curvature2;
    std::unique_ptr<Matrix<double>> curvature3;
    std::unique_ptr<Matrix<double>> curvature4;

    double ***horizon_height;
    long *horizon_numlines;
    std::unique_ptr<Matrix<long>> horizon_point;
    long num_horizon_point;

    long ***i_cont;
    std::unique_ptr<Matrix<long>> lrc_cont;

    long **j_cont;
    std::unique_ptr<Matrix<long>> rc_cont;

    std::unique_ptr<Vector<long>> Lp;
    std::unique_ptr<Vector<long>> Li;

    std::unique_ptr<Vector<long>> Up;
    std::unique_ptr<Vector<long>> Ui;

    std::unique_ptr<Matrix<long>> Jdown;
    std::unique_ptr<Matrix<double>> Qdown;

    std::unique_ptr<Matrix<short>> is_on_border;

    std::unique_ptr<Matrix<double>> East;
    std::unique_ptr<Matrix<double>> North;

    std::unique_ptr<Matrix<long>> BC_counter;
    std::unique_ptr<Vector<double>> BC_DepthFreeSurface;

    std::unique_ptr<Matrix<double>> dzdE;
    std::unique_ptr<Matrix<double>> dzdN;

    std::unique_ptr<Matrix<double>> latitude;
    std::unique_ptr<Matrix<double>> longitude;
    
    long DifNxShadow; /** Number of elements (direction x) that separate the Elevation DEM with the extended shadow DEM**/
    long DifNyShadow; /** Number of elements (direction y) that separate the Elevation DEM with the extended shadow DEM**/

} TOPO;


/*---------------------------------------------------------------------------*/
typedef struct {
    std::unique_ptr<Matrix<double>> LC; /** land cover for each pixel */
    std::unique_ptr<Matrix<double>> delay;
    std::unique_ptr<Matrix<short>> shadow; /** parameter equal to 1 if shadow, otherwise 0 */
    std::unique_ptr<Matrix<double>> ty;

    double ***vegpars; /** tensor with time dependent vegetation parameters */
    double **vegparv; /** matrix with time dependent vegetation parameters */
    std::unique_ptr<Vector<double>> vegpar;
    long *NumlinesVegTimeDepData;

    std::unique_ptr<Matrix<double>> root_fraction;

} LAND; /** all this data are calculated on the basis of land use data and some other parameters */


/*---------------------------------------------------------------------------*/


typedef struct {
    /**
     * CHANNEL parameters:
     * - nch = number of channel-pixel
     * - ns = number of virtual stretches of channel
     * - L = number of layers
     * - R = number of rows of the basin
     * - C = number of columns in the basin
     */
    std::unique_ptr<Vector<long>> r; /** rows indexes of the channel pixels */
    std::unique_ptr<Vector<long>> c; /** columns indexes of the channel pixels */
    std::unique_ptr<Matrix<long>> ch;
    std::unique_ptr<Vector<long>> ch_down;
    std::unique_ptr<Vector<double>> Vsup;
    std::unique_ptr<Vector<double>> Vsub;
    std::unique_ptr<Vector<double>> h_sup;
    std::unique_ptr<Vector<double>> length;
    double Vout;
    long **ch3;
    std::unique_ptr<Matrix<long>> lch;
    std::unique_ptr<Vector<long>> soil_type; /** soil type for channel pixels */
    std::unique_ptr<Matrix<double>> th; /** theta (SWC) */
    std::unique_ptr<Matrix<double>> ET;
    std::unique_ptr<Vector<double>> Kbottom;
    std::unique_ptr<Vector<double>> Kthermalairbottom;
    std::unique_ptr<Vector<double>> Kairbottom;
    SOIL_STATE *SS;
} CHANNEL;


/*---------------------------------------------------------------------------*/

typedef struct {
    /**
     * WATER parameters:
     * - nstations=number of all the rain-stations
     * - number_of_pixels=number of all the pixels of the basin R*C
     * - R=number of rows
     * - C=number of columns
     * - nt=number of time-step of the whole similation
     */
    std::unique_ptr<Matrix<double>> PrecTot; /** total (snow+rain) precipitation (in a Dt) [mm] */
    std::unique_ptr<Matrix<double>> Pnet;  /** liquid precipitation which reaches the soil surface in a Dt as input
                                            * of "punctual_energy" subroutine [mm],
                                            * (rain intensity as output of the same subroutine and
                                            * in "water.balance.c" module [mm/s]) */
    std::unique_ptr<Vector<double>> PrTOT_mean;  /** total precipitation (on nDt_output_basin Dt time intervals) [mm] */
    std::unique_ptr<Vector<double>> PrSNW_mean;
    std::unique_ptr<Vector<double>> Pt;
    std::unique_ptr<Vector<double>> Ps;

    std::unique_ptr<Vector<double>> h_sup;

    std::unique_ptr<Matrix<double>> error;

    std::unique_ptr<Vector<double>> Lx;
    std::unique_ptr<Vector<double>> Ux;

    std::unique_ptr<Vector<double>> H0;
    std::unique_ptr<Vector<double>> H1;
    std::unique_ptr<Vector<double>> dH;
    std::unique_ptr<Vector<double>> B;
    std::unique_ptr<Vector<double>> f;
    std::unique_ptr<Vector<double>> df;
    std::unique_ptr<Matrix<double>> Klat;
    std::unique_ptr<Matrix<double>> Kbottom;

    double Voutlandsub;
    double Voutlandsup;
    double Voutbottom;
    double iternumber;

} WATER;

typedef struct {
    std::unique_ptr<Matrix<double>> error;
    std::unique_ptr<Vector<double>> Lx;
    std::unique_ptr<Vector<double>> LxB;//Lx only considering buyancy
    std::unique_ptr<Vector<double>> LxJair;
    std::unique_ptr<Vector<double>> Ux;
    std::unique_ptr<Vector<double>> P0;
    std::unique_ptr<Vector<double>> P1;
    std::unique_ptr<Vector<double>> MaxVel;
    std::unique_ptr<Vector<double>> VxW;
    std::unique_ptr<Vector<double>> VxE;
    std::unique_ptr<Vector<double>> VyN;
    std::unique_ptr<Vector<double>> VyS;
    std::unique_ptr<Vector<double>> VzT;
    std::unique_ptr<Vector<double>> VzB;
    std::unique_ptr<Vector<double>> dP;
    std::unique_ptr<Vector<double>> B;
    std::unique_ptr<Vector<double>> f;
    std::unique_ptr<Vector<double>> df;
    std::unique_ptr<Matrix<double>> Klat;
    std::unique_ptr<Matrix<double>> Kbottom;
    std::unique_ptr<Vector<short>> FluxDir;
    double Courant;
    
} AIRFLUX;

typedef struct {
    std::unique_ptr<Matrix<double>> error;
    std::unique_ptr<Vector<double>> Lx;
    std::unique_ptr<Vector<double>> Ux;
    std::unique_ptr<Vector<double>> T0;
    std::unique_ptr<Vector<double>> T1;
    std::unique_ptr<Vector<double>> dT;
    std::unique_ptr<Vector<double>> B;
    std::unique_ptr<Vector<double>> f;
    std::unique_ptr<Vector<double>> df;
    std::unique_ptr<Matrix<double>> Klat;
    std::unique_ptr<Matrix<double>> SFlux0; /*Heat flux from snow to air first layer */
    double iternumber;

} AIRENERGY;
/*---------------------------------------------------------------------------*/
typedef struct {

    std::unique_ptr<Vector<double>> JD_plots;
    double time; /** current time from the begin of simulation [s] */
    long iplot;
    double **Dt_matrix;
    long numlinesDt_matrix;
    double *Dt_vector;

} TIMES;


/*---------------------------------------------------------------------------*/
typedef struct {
    double Dt; /** integration time interval [s] */
    double ST;
    short print; /** parameter equal to 1 if you want to print matrices with intermediate results, otherwise equal to 0 */
    short monin_obukhov;
    double gamma_m; /** exponent of the law of uniform motion on the surface */
    double T_rain; /** temperature above wich all precipitaion is rain [°C] */
    double T_snow; /** temperature below wich all precipitaion is snow [°C] */
    double aep; /** albedo extinction parameter [m] */
    double avo; /** new snow visible band reflectance */
    double airo; /** new near infrared band reflectance */
    double Sr;      /** water fraction retained by capillary forces in snow */
    double rho_ice;     /** ice density [kg/mc] */
    long total_pixel;    /** the number of the valid pixel of the whole basin */
    long total_channel;
    double total_area;

    double max_weq_snow;
    long max_snow_layers;
    std::unique_ptr<Vector<long>> inf_snow_layers;

    double max_weq_glac;
    long max_glac_layers; /** glacier layers */
    std::unique_ptr<Vector<long>> inf_glac_layers;

    double Sr_glac;

    short state_turb;
    short state_lwrad;

    double imp;
    double f_bound_Richards;

    double epsilon_snow;

    std::unique_ptr<Vector<double>> output_soil;
    std::unique_ptr<Vector<double>> output_snow;
    std::unique_ptr<Vector<double>> output_glac;
    std::unique_ptr<Vector<double>> output_surfenergy;
    std::unique_ptr<Vector<double>> output_vegetation;
    std::unique_ptr<Vector<double>> output_meteo;

    short output_soil_bin;
    short output_snow_bin;
    short output_glac_bin;
    short output_surfenergy_bin; /** set to 1 if we want to know the surface energy balance data in the output station [TO CHECK] */
    short output_meteo_bin; /** set to 1 if we want to know the meteo data in the output station [TO CHECK] */

    std::unique_ptr<Matrix<double>> chkpt;
    std::unique_ptr<Matrix<long>> rc; /** rows and cols indexes of the selected output points */
    std::unique_ptr<Vector<long>> jplot; /** size = valid pixels; value can be the output point index or 0 */

    short recover; /** if equal to 1, enables recovery [default = 0]*/

    double Vmin;

    double snowcorrfact;
    double raincorrfact;

    double RHmin;

    short format_out;
    short sky;

    std::unique_ptr<Vector<double>> saving_points;
    double ContRecovery;
    long n_ContRecovery;

    short point_sim;

    double snow_maxpor;
    double snow_density_cutoff;
    double drysnowdef_rate;
    double wetsnowdef_rate;
    double snow_viscosity;

    double latitude;
    double longitude;

    double z0_snow;

    long n_landuses;

    short blowing_snow;

    std::unique_ptr<Vector<long>> r_points;
    std::unique_ptr<Vector<long>> c_points;

    double psimin;
    double stmin;

    short wat_balance;
    short en_balance;
    short air_balance;
    short air_energy_balance;
    short PlotAirVel;
    double AirRichardTol;

    long nLC;

    double fetch_up;
    double fetch_down;

    short iobsint;
    double dn;
    double slopewt;
    double curvewt;
    double slopewtI;
    double curvewtI;
    double slopewtD;
    double curvewtD;

    short LRflag;

    std::unique_ptr<Vector<short>> vegflag;

    //short harm_or_arit_mean_normal;
    //short harm_or_arit_mean_parallel;

    long MaxiterTol;
    double MaxErrWb;
    double TolVWb;

    double incr_V_factor;

    double alpha_snow;
    double tol_energy;
    long maxiter_energy;
    long maxiter_canopy;
    long maxiter_Ts;
    long maxiter_Loc;
    long maxiter_Businger;
    short stabcorr_incanopy;

    double TolCG;
    long MaxiterCorr;
    short UpdateK;

    double thres_hsup_1;
    double thres_hsup_2;

    double thres_hchannel;

    double w_dx;

    double RelTolVWb;

    double snow_smin;
    double snow_smax;
    double snow_curv;

    double Zboundary; /** Z at which 0 annual temperature takes place [mm]*/
    double Tboundary;
    double Fboundary;

    double Ks_channel;
    double depr_channel; /** default = 500 */

    short tsteps_from_file;

    std::unique_ptr<Vector<short>> plot_discharge_with_Dt_integration;
    std::unique_ptr<Vector<short>> plot_point_with_Dt_integration;
    std::unique_ptr<Vector<short>> plot_basin_with_Dt_integration;

    std::unique_ptr<Vector<double>> Dtplot_point;
    std::unique_ptr<Vector<double>> Dtplot_basin;
    std::unique_ptr<Vector<double>> Dtplot_discharge;

    short state_pixel; /** equal to 1 if output pixels are set */
    short state_discharge;
    short state_basin;

    double Dt_PBSM;

    long lowpass;
    long lowpass_curvatures;

    short dew;

    std::unique_ptr<Vector<double>> init_date;
    std::unique_ptr<Vector<double>> end_date;
    std::unique_ptr<Vector<long>> run_times;

    double delay_day_recover;

    short all_point;
    short all_basin;
    short all_snow;
    short all_glac;
    short all_soil;

    double Wice_PBSM;

    std::unique_ptr<Matrix<double>> maxSWE;

    long soil_type_land_default;
    long soil_type_chan_default;
    long soil_type_bedr_default;

    double MinIncrFactWithElev;
    double MaxIncrFactWithElev;

    long nsurface;

    double max_courant_land;
    double max_courant_channel;
    double max_courant_land_channel;
    double min_hsup_land;
    double min_hsup_channel;
    double min_dhsup_land_channel_in;
    double min_dhsup_land_channel_out;
    double dtmin_sup;

    long nsoiltypes;

    std::unique_ptr<Vector<long>> IDpoint;

    double min_lambda_en;
    long max_times_min_lambda_en;
    short exit_lambda_min_en;

    double min_lambda_wat;
    long max_times_min_lambda_wat;
    short exit_lambda_min_wat;

    double free_drainage_bottom;
    double free_drainage_lateral;

    short surroundings;

    std::unique_ptr<Vector<double>> soil_plot_depths;
    std::unique_ptr<Vector<double>> snow_plot_depths;
    std::unique_ptr<Vector<double>> glac_plot_depths;

    short ric_cloud;
    short vap_as_RH;
    short vap_as_Td;
    long ndivdaycloud;
    short cast_shadow;
    short ExtendedShadowCalcl;
    short wind_as_dir;
    short wind_as_xy;

    double snow_aging_vis;
    double snow_aging_nir;

    double DepthFreeSurface;

    short prec_as_intensity;

    std::unique_ptr<Vector<short>> linear_interpolation_meteo;

    short output_vertical_distances;

    short upwindblowingsnow;

    double Wmin_BS;
    double SWE_top;
    double SWE_bottom;
    double GWE_top;
    double GWE_bottom;

    double min_Dt;
    double dem_rotation;

    short qin;
    short flag1D;

    double k_to_ksat;
    short RunIfAnOldRunIsPresent;

    std::unique_ptr<Vector<long>> Nl_spinup; /** (*par->Nl_spinup)(1),default = 10'000 */

    short newperiodinit;

    /** spin-up variables (*run) */
    short Tzrun;
    short wzrun;
    short dUzrun;
    short SWErun;

    short Tzmaxrun;
    short wzmaxrun;
    short Tzminrun;
    short wzminrun;

    double k1;
    double k2;
    double Lozone;
    double alpha_iqbal;
    double beta_iqbal;

    short albedoSWin;
    short micro;

    double EB;
    double Cair;
    double Tsup;
    double Tbottom;

    double Tair_default;
    double RH_default;
    double V_default;
    double Vdir_default;
    double IPrec_default; /** precipitation intensity */

    double simulation_hours;

    double minP_torestore_A;
    short snow_conductivity;
    short snow_wind_compaction_1D;
    short snow_plot;

    short DDchannel;
    short DDland;
    
    double MaxK;
    short HeatTransferModel;
    /**Heat transfer model parameters (a, b and n)*/
    double Ht_a;
    double Ht_b;
    double Ht_n;
    double SnowDepthAirFlowLimit;

} PAR;


/*---------------------------------------------------------------------------*/
struct STATEVAR_3D {

    STATEVAR_3D(double nan, long nl, long nr, long nc);

    ~STATEVAR_3D();

    std::unique_ptr<Matrix<short>> type;
    std::unique_ptr<Matrix<long>> lnum;
    std::unique_ptr<Tensor<double>> Dzl; /** snow depth */
    std::unique_ptr<Tensor<double>> w_liq;
    std::unique_ptr<Tensor<double>> w_ice; /** SWE (snow water equivalent) */
    std::unique_ptr<Tensor<double>> T; /** temperature */
};


typedef struct {
    short type;
    long lnum;
    std::unique_ptr<Vector<double>> Dzl; /** snow depth */
    std::unique_ptr<Vector<double>> w_liq;
    std::unique_ptr<Vector<double>> w_ice; /** SWE (snow water equivalent) */
    std::unique_ptr<Vector<double>> T;
} STATEVAR_1D;

typedef struct {
    STATEVAR_3D *S;
    STATEVAR_1D *S_for_BS;
    std::unique_ptr<Vector<double>> age; /** snow age */
    std::unique_ptr<Vector<double>> MELTED;
    std::unique_ptr<Vector<double>> melted;
    std::unique_ptr<Vector<double>> SUBL;
    std::unique_ptr<Vector<double>> subl;
    std::unique_ptr<Vector<double>> t_snow;
    std::unique_ptr<Vector<short>> yes;

    std::unique_ptr<Matrix<double>> Qsub;
    std::unique_ptr<Matrix<double>> Qsub_x;
    std::unique_ptr<Matrix<double>> Qsub_y;
    std::unique_ptr<Matrix<double>> Nabla2_Qtrans;
    std::unique_ptr<Matrix<double>> Qtrans;
    std::unique_ptr<Matrix<double>> Qsalt;
    std::unique_ptr<Matrix<double>> Qtrans_x;
    std::unique_ptr<Matrix<double>> Qtrans_y;
    std::unique_ptr<Matrix<double>> Wsubl_plot;
    std::unique_ptr<Matrix<double>> Wtrans_plot;

    std::unique_ptr<Vector<double>> Dplot;
    std::unique_ptr<Vector<long>> change_dir_wind;
} SNOW;

typedef struct {
    STATEVAR_3D *G;
    std::unique_ptr<Vector<double>> MELTED;
    std::unique_ptr<Vector<double>> melted;
    std::unique_ptr<Vector<double>> SUBL;
    std::unique_ptr<Vector<double>> subl;
} GLACIER;

struct METEO_STATIONS{
    std::unique_ptr<Vector<double>> E; /** East */
    std::unique_ptr<Vector<double>> N; /** North */
    std::unique_ptr<Vector<double>> lat; /** latitude */
    std::unique_ptr<Vector<double>> lon; /** longitude */
    std::unique_ptr<Vector<double>> Z; /** elevations [m a.s.l] */
    std::unique_ptr<Vector<double>> sky; /** sky view factor */
    std::unique_ptr<Vector<double>> ST; /** identifier for the meteo station */
    std::unique_ptr<Vector<double>> Vheight; /** height of wind sensor [m] */
    std::unique_ptr<Vector<double>> Theight; /** height of temperature sensor [m] */
};


struct METEO {
    std::unique_ptr<METEO_STATIONS> st;

    double ***data; /** meteo data */

    long *numlines; /** number of line of meteo data */
    double ***horizon; /** horizon for meteo stations */
    long *horizonlines; /** number of line in the horizon file */
    double **var; /** meteo variables for the current instant */
    long *line_interp_WEB;
    long *line_interp_Bsnow;
    long line_interp_WEB_LR;
    long line_interp_Bsnow_LR;

    /** Lapse Rate parameters */
    double **LRs; /** matrix read from the external value */
    long LRsnr; /** number of lines of the matrix */
    double *LRv;  /** vector of interpolated values */
    double **LRc; /** cyclic values from the parameter file (one vector for each LR variable) */
    long *LRcnc;  /** number of components of the vector (for each component) */
    double *LRd;  /** vector of default values */

    double **qins;
    double *qinv;
    long qinsnr;
    long qinline;

    double tau_cloud;
    double tau_cloud_av;
    short tau_cloud_yes;
    short tau_cloud_av_yes;

    std::unique_ptr<Matrix<double>> Tgrid;
    std::unique_ptr<Matrix<double>> Pgrid;
    std::unique_ptr<Matrix<double>> Vgrid;
    std::unique_ptr<Matrix<double>> Vdir;
    std::unique_ptr<Matrix<double>> RHgrid;

    std::unique_ptr<Vector<double>> Tamean;
    std::unique_ptr<Vector<double>> Vspdmean;
    std::unique_ptr<Vector<double>> Vdirmean;
    std::unique_ptr<Vector<double>> RHmean;

    std::unique_ptr<Vector<double>> Taplot;
    std::unique_ptr<Vector<double>> Vxplot;
    std::unique_ptr<Vector<double>> Vyplot;
    std::unique_ptr<Vector<double>> RHplot;

    double V;

    std::unique_ptr<Matrix<double>> Tday;
    std::unique_ptr<Matrix<double>> Tvar;

    long nstsrad;
    long nstlrad;
    long nstcloud;
    long nstTs;
    long nstTbottom;

    std::unique_ptr<Vector<long>> imeteo_stations;

};


struct ALLDATA {
    std::unique_ptr<SOIL> S;
    std::unique_ptr<WATER> W;
    std::unique_ptr<AIRFLUX> AF;
    std::unique_ptr<AIRENERGY> AE;
    std::unique_ptr<LAND> L;
    std::unique_ptr<PAR> P;
    std::unique_ptr<TOPO> T;
    std::unique_ptr<CHANNEL> C;
    std::unique_ptr<ENERGY> E;
    std::unique_ptr<SNOW> N;
    std::unique_ptr<GLACIER> G;
    std::unique_ptr<METEO> M;
    std::unique_ptr<TIMES> I;

    ALLDATA() : S{new SOIL{}},
                W{new WATER{}},
                AF{new AIRFLUX{}},
                AE{new AIRENERGY{}},
                L{new LAND{}},
                P{new PAR{}},
                T{new TOPO{}},
                C{new CHANNEL{}},
                E{new ENERGY{}},
                N{new SNOW{}},
                G{new GLACIER{}},
                M{new METEO{}},
                I{new TIMES{}} {}
};

#endif
