/* 
 * File:   biquad.c
 *
 * Created on 20. juli 2021, 10:03
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/**
 * @file biquad.c
 *
 * Simple implementation of Biquad filters -- Tom St Denis
 *
 * Based on the work
 *
 *   Cookbook formulae for audio EQ biquad filter coefficients
 *   ---------------------------------------------------------
 *   by Robert Bristow-Johnson, pbjrbj@viconet.com  a.k.a. robert@audioheads.com
 *
 * Available on the web at
 *    http://www.musicdsp.org/files/biquad.c
 *
 * Enjoy.
 *
 * This work is hereby placed in the public domain for all purposes, whether
 * commercial, free [as in speech] or educational, etc.  Use the code and please
 * give me credit if you wish.
 *
 * Tom St Denis -- http://tomstdenis.home.dhs.org
 *
 * See also: http://musicweb.ucsd.edu/~tre/biquad.pdf
 *
 * Source: https://github.com/wooters/miniDSP/blob/master/biquad.c 
*/
#include "biquad.h"

/* Computes a BiQuad filter on a sample */
smp_type BiQuad(const smp_type sample, biquad* const b)
{
  smp_type result;

  /* compute result */
  result = b->a0 * sample + b->a1 * b->x1 + b->a2 * b->x2 -
    b->a3 * b->y1 - b->a4 * b->y2;

  /* shift x1 to x2, sample to x1 */
  b->x2 = b->x1;
  b->x1 = sample;

  /* shift y1 to y2, result to y1 */
  b->y2 = b->y1;
  b->y1 = result;

  return result;
}

/* sets up a BiQuad Filter */
/* Note that dbGain is only used when the type is LSH or HSH */
biquad *BiQuad_new(const int type, const smp_type dbGain, const smp_type freq,
		   const smp_type srate, const smp_type bandwidth)
{
  biquad *b;
  smp_type A, omega, sn, cs, alpha, beta;
  smp_type a0, a1, a2, b0, b1, b2;

  b = malloc(sizeof(biquad));
  if (b == NULL)
    return NULL;

  /* setup variables */
  A = pow(10, dbGain /40);
  omega = 2 * M_PI * freq /srate;
  sn = sin(omega);
  cs = cos(omega);
  alpha = sn * sinh(M_LN2 /2 * bandwidth * omega /sn);
  beta = sqrt(A + A);

  switch (type) {
  case LPF:
    b0 = (1 - cs) /2;
    b1 = 1 - cs;
    b2 = (1 - cs) /2;
    a0 = 1 + alpha;
    a1 = -2 * cs;
    a2 = 1 - alpha;
    break;
  case HPF:
    b0 = (1 + cs) /2;
    b1 = -(1 + cs);
    b2 = (1 + cs) /2;
    a0 = 1 + alpha;
    a1 = -2 * cs;
    a2 = 1 - alpha;
    break;
  case BPF:
    b0 = alpha;
    b1 = 0;
    b2 = -alpha;
    a0 = 1 + alpha;
    a1 = -2 * cs;
    a2 = 1 - alpha;
    break;
  case NOTCH:
    b0 = 1;
    b1 = -2 * cs;
    b2 = 1;
    a0 = 1 + alpha;
    a1 = -2 * cs;
    a2 = 1 - alpha;
    break;
  case PEQ:
    b0 = 1 + (alpha * A);
    b1 = -2 * cs;
    b2 = 1 - (alpha * A);
    a0 = 1 + (alpha /A);
    a1 = -2 * cs;
    a2 = 1 - (alpha /A);
    break;
  case LSH:
    b0 = A * ((A + 1) - (A - 1) * cs + beta * sn);
    b1 = 2 * A * ((A - 1) - (A + 1) * cs);
    b2 = A * ((A + 1) - (A - 1) * cs - beta * sn);
    a0 = (A + 1) + (A - 1) * cs + beta * sn;
    a1 = -2 * ((A - 1) + (A + 1) * cs);
    a2 = (A + 1) + (A - 1) * cs - beta * sn;
    break;
  case HSH:
    b0 = A * ((A + 1) + (A - 1) * cs + beta * sn);
    b1 = -2 * A * ((A - 1) + (A + 1) * cs);
    b2 = A * ((A + 1) + (A - 1) * cs - beta * sn);
    a0 = (A + 1) - (A - 1) * cs + beta * sn;
    a1 = 2 * ((A - 1) - (A + 1) * cs);
    a2 = (A + 1) - (A - 1) * cs - beta * sn;
    break;
  default:
    free(b);
    return NULL;
  }

  /* precompute the coefficients */
  b->a0 = b0 /a0;
  b->a1 = b1 /a0;
  b->a2 = b2 /a0;
  b->a3 = a1 /a0;
  b->a4 = a2 /a0;

  /* zero initial samples */
  b->x1 = b->x2 = 0;
  b->y1 = b->y2 = 0;

  return b;
}
