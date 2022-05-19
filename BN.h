#ifndef _BN_H_
#define _BN_H_
//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("no-stack-protector")
//#pragma GCC target ("tune=native")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
//#pragma GCC optimize ("conserve-stack")
//#pragma GCC optimize ("no-stack-limit")
//#pragma clang optimize on
//#pragma clang loop unroll(enable)


#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>


static const int base = 1000000000;

struct bn_s {
	int* d;
	int size;
	int r_s;
	unsigned int sign; //  0 = - ; 1 = +
};

typedef struct bn_s bn;

typedef enum {
	ESUCCESS = 0,
	EMALLOC,
	EFULL,
	EEMPTY,
	EINVARG
} bn_err;

bn* bn_new(void);

bn* bn_init(bn const* orig);

int bn_delete(bn* t);

int bn_null(bn const* t);

int add_int(bn* t, int c);

int multiple_int(bn* t, long c);

int multiple_int_bn(bn* rez, const bn* t, long c);

int div_int(bn* t, long c);

int bn_init_string(bn* t, const char* init_string);

int ch_to_int(char c);

char int_to_ch(int c);

int bn_init_string_radix(bn* t, const char* init_string, int radix);

const char* bn_to_string(bn const* t, int radix);

int bn_init_int(bn* t, int init_int);

int print(bn* t);

int bn_abs_cmp(bn const* left, bn const* right);

int bn_cmp(bn const* left, bn const* right);

int bn_neg(bn* t);

int bn_abs(bn* t);

int bn_sign(bn const* t);

int* add(const bn* t, const  bn* right, int* size);

int* diff(const bn* t, const bn* right, int* size);

int* multiple(const bn* t, const  bn* right, int* size);

int bn_add_to(bn* t, bn const* right);

int bn_sub_to(bn* t, bn const* right);

bn* bn_add(bn const* left, bn const* right);

bn* bn_sub(bn const* left, bn const* right);

int bn_mul_to(bn* t, bn const* right);

bn* bn_mul(bn const* left, bn const* right);

int move(bn* t);

int bn_div_to(bn* t, bn const* right);

bn* bn_div(bn const* left, bn const* right);

int copy(bn* t, bn* f); 

#endif // BN