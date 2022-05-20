#include "BN.h"

int main() {
	bn_err err;
	bn* t = bn_new(&err);
	bn_init_string(t, "", &err);

	bn_init_string(t, "\0", &err);

	bn_init_int(t, 100000, &err);

	bn_init_int(t, base + 1, &err);

	bn_abs(t);

	bn_null(t);

	bn_init_string(t, "100000000000000000", &err);


	bn* k = bn_init(t, &err);

	bn* l = bn_mul(t, k);
	
	bn* p = bn_add(l, k);
	
	bn* m = bn_div(t, k);

	bn* f = bn_sub(t, k);

	add_int(f, 1000000, &err);

	int sign = bn_sign(f);

	multiple_int(m, 10, &err);

	multiple_int_bn(k, m, 10);

	int division = div_int(p, 10000000);

	const char* c = bn_to_string(p, base, &err);

	bn_cmp(t, k);

	print(m);
	print(k);
	print(p);
	print(l);
	print(f);

	bn_delete(f);
	bn_delete(m);
	bn_delete(p);
	bn_delete(l);
	bn_delete(t);
	bn_delete(k);
	return 0;
}
