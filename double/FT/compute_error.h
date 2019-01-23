#ifndef __COMPUTE_ERROR_H__
#define __COMPUTE_ERROR_H__

#include <string.h>
#include <errno.h>
#include <quadmath.h>

#include "npb-C.h"

template<class T>
typename std::enable_if<std::is_same<T, pcomplex>::value, void>::type
compute_error(T *array, T *truth, int size)
{
	__float128 real_error = 0.0q;
	__float128 imag_error = 0.0q;
	__float128 rmse = 0.0q;

	for(int i=0; i<size; i++) {
		real_error = ((__float128)array[i].real.toDouble() - (__float128)truth[i].real.toDouble());
		imag_error = ((__float128)array[i].imag.toDouble() - (__float128)truth[i].imag.toDouble());
		__float128 distance = sqrtq((real_error * real_error) + (imag_error * imag_error));
		rmse += distance * distance;
	}

	//rmse = sqrtq(rmse / (__float128)size);
	rmse = sqrtq(rmse);
	printf("error: %22.12Qe\n", rmse);

}

template<class T>
typename std::enable_if<!std::is_same<T, pcomplex>::value, void>::type
compute_error(T *array, T *truth, int size)
{
	__float128 real_error = 0.0q;
	__float128 imag_error = 0.0q;
	__float128 rmse = 0.0q;

	for(int i=0; i<size; i++) {
		real_error = ((__float128)array[i].real - (__float128)truth[i].real);
		imag_error = ((__float128)array[i].imag - (__float128)truth[i].imag);
		__float128 distance = sqrtq((real_error * real_error) + (imag_error * imag_error));
		rmse += distance * distance;
	}

	//rmse = sqrtq(rmse / (__float128)size);
	rmse = sqrtq(rmse);
	printf("error: %22.12Qe\n", rmse);
}

template<class T, class Q>
typename std::enable_if<std::is_same<T, pcomplex>::value, void>::type
compute_error(T *array, Q *truth, int size)
{
	__float128 real_error = 0.0q;
	__float128 imag_error = 0.0q;
	__float128 rmse = 0.0q;

	for(int i=0; i<size; i++) {
		real_error = ((__float128)array[i].real.toDouble() - (__float128)truth[i].real);
		imag_error = ((__float128)array[i].imag.toDouble() - (__float128)truth[i].imag);
		__float128 distance = sqrtq((real_error * real_error) + (imag_error * imag_error));
		rmse += distance * distance;
	}

	//rmse = sqrtq(rmse / (__float128)size);
	rmse = sqrtq(rmse);
	printf("error: %22.12Qe\n", rmse);
}

template<class T, class Q>
typename std::enable_if<!std::is_same<T, pcomplex>::value, void>::type
compute_error(T *array, Q *truth, int size)
{
	__float128 real_error = 0.0q;
	__float128 imag_error = 0.0q;
	__float128 rmse = 0.0q;

	for(int i=0; i<size; i++) {
		real_error = ((__float128)array[i].real - (__float128)truth[i].real);
		imag_error = ((__float128)array[i].imag - (__float128)truth[i].imag);
		__float128 distance = sqrtq((real_error * real_error) + (imag_error * imag_error));
		rmse += distance * distance;
	}

	//rmse = sqrtq(rmse / (__float128)size);
	rmse = sqrtq(rmse);
	printf("error: %22.12Qe\n", rmse);
}

template<class T>
void load_array(const char *path, const char *application, const char *datatype, const char problem_class, const int iter, T *out, const int size)
{
	FILE *file;
	char filename[1024];
	snprintf(filename, 1024, "%s/%s_%s_%c_%d.bin", path, application, datatype, problem_class, iter);

	if((file=fopen(filename, "rb"))!=NULL) {
		fread(out, sizeof(T), size, file);
		fclose(file);
	}
	else {
		fprintf(stderr, "%s\n", strerror(errno));
	}
}

template<class T>
void save_array(const char *path, const char *application, const char *datatype, const char problem_class, int iter, T *out, int size)
{
	FILE *file;
	char filename[1024];
	sprintf(filename, "%s/%s_%s_%c_%d.bin", path, application, datatype, problem_class, iter);

	if((file=fopen(filename, "wb"))!=NULL) {
		fwrite(out, sizeof(T), size, file);
		fclose(file);
	}
	else {
		fprintf(stderr, "%s\n", strerror(errno));
	}
}

template<class T>
void scale(int size, T u0[NZ][NY][NX], T u1[NZ][NY][NX])
{
	for(int i=0; i<NZ; i++) {
		for(int j=0; j<NY; j++) {
			for(int k=0; k<NX; k++) {
				u1[i][j][k].real = u0[i][j][k].real / size;
				u1[i][j][k].imag = u0[i][j][k].imag / size;
			}
		}
	}
}

#endif
