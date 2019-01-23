#ifndef __NPB_C_H__
#define __NPB_C_H__

/*
  NAS Parallel Benchmarks 2.3 OpenMP C Versions
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if defined(_OPENMP)
#include <omp.h>
#endif /* _OPENMP */
#include "softposit_cpp.h"
#include <quadmath.h>
#include <type_traits>

typedef int boolean;
typedef struct { double real; double imag; } dcomplex;
typedef struct { float real; float imag; } fcomplex;
typedef struct { __float128 real; __float128 imag; } qcomplex;
typedef struct { posit32 real; posit32 imag; } pcomplex;

#define TRUE	1
#define FALSE	0

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define	pow2(a) ((a)*(a))

#define get_real(c) c.real
#define get_imag(c) c.imag
#define cadd(c,a,b) (c.real = a.real + b.real, c.imag = a.imag + b.imag)
#define csub(c,a,b) (c.real = a.real - b.real, c.imag = a.imag - b.imag)
#define cmul(c,a,b) (c.real = a.real * b.real - a.imag * b.imag, \
                     c.imag = a.real * b.imag + a.imag * b.real)
#define crmul(c,a,b) (c.real = a.real * b, c.imag = a.imag * b)

extern double randlc(double *, double);
extern void vranlc(int, double *, double, double *);
extern void vranlc(int, double *, double, posit32 *);
extern void timer_clear(int);
extern void timer_start(int);
extern void timer_stop(int);
extern double timer_read(int);

extern void c_print_results(char *name, char problem_class, int n1, int n2,
			    int n3, int niter, int nthreads, double t,
			    double mops, char *optype, int passed_verification,
			    char *npbversion, char *compiletime, char *cc,
			    char *clink, char *c_lib, char *c_inc,
			    char *cflags, char *clinkflags, char *rand);

#endif
