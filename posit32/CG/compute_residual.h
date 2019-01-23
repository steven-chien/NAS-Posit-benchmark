#ifndef __COMPUTE_RESIDUAL_H__
#define __COMPUTE_RESIDUAL_H__

#include "softposit_cpp.h"
#include <quadmath.h>
#include <type_traits>

template<class T>
typename std::enable_if<std::is_same<T, posit32>::value, void>::type
compute_residual(int iter, T *a, T *z, T *x, int NA, int firstrow, int lastrow, int firstcol, int lastcol, int *rowstr, int *colidx)
{
	/* compute r */
	static __float128 d, explicit_r;
	__float128 tmp_r[NA+2+1];	/* r[1:NA+2] */
	static int j, k;

	for (j = 1; j <= lastrow-firstrow+1; j++) {
		d = 0.0q;
		for (k = rowstr[j]; k <= rowstr[j+1]-1; k++) {
			d = d + static_cast<__float128>(a[k].toDouble())*static_cast<__float128>(z[colidx[k]].toDouble());
		}
		tmp_r[j] = d;
	}

	/*--------------------------------------------------------------------
	  c  At this point, r contains A.z
	  c-------------------------------------------------------------------*/
	explicit_r = 0.0q;

	for (j = 1; j <= lastcol-firstcol+1; j++) {
		tmp_r[j] = static_cast<__float128>(x[j].toDouble()) - tmp_r[j];

		explicit_r = explicit_r + tmp_r[j]*tmp_r[j]; 
	}

	explicit_r = sqrtq(explicit_r);
	printf("CG:\t%d\t%20.14Qe\n", iter, explicit_r);
}

template<class T>
typename std::enable_if<!std::is_same<T, posit32>::value, void>::type
compute_residual(int iter, T *a, T *z, T *x, int NA, int firstrow, int lastrow, int firstcol, int lastcol, int *rowstr, int *colidx)
{
	/* compute r */
	static __float128 d, explicit_r;
	__float128 tmp_r[NA+2+1];	/* r[1:NA+2] */
	static int j, k;

	for (j = 1; j <= lastrow-firstrow+1; j++) {
		d = 0.0q;
		for (k = rowstr[j]; k <= rowstr[j+1]-1; k++) {
			d = d + static_cast<__float128>(a[k])*static_cast<__float128>(z[colidx[k]]);
		}
		tmp_r[j] = d;
	}

	/*--------------------------------------------------------------------
	  c  At this point, r contains A.z
	  c-------------------------------------------------------------------*/
	explicit_r = 0.0q;

	for (j = 1; j <= lastcol-firstcol+1; j++) {
		tmp_r[j] = static_cast<__float128>(x[j]) - tmp_r[j];

		explicit_r = explicit_r + tmp_r[j]*tmp_r[j]; 
	}

	explicit_r = sqrtq(explicit_r);
	printf("CG:\t%d\t%20.14Qe\n", iter, explicit_r);
}

#endif
