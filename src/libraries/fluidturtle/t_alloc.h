#ifndef _LIBRARIES_FLUIDTURTLE_T_ALLOC_H
#define _LIBRARIES_FLUIDTURTLE_T_ALLOC_H

float *vector(long nl,long nh);

float **matrix(long nrl, long nrh, long ncl,long nch);


double ***d3tensor( long nrl, long nrh, long ncl, long nch, long ndl,long ndh);

DOUBLETENSOR *new_doubletensor(long nrh,long nch,long ndh);

DOUBLETENSOR *new_doubletensor0(long ndh,long nrh,long nch);

void free_d3tensor(double ***t, long nrl, long ncl, long ndl);

void free_doubletensor( DOUBLETENSOR *m);


#endif
