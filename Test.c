#include "BN.h"

int main() {
	bn_err err;

	bn* t = bn_new();

	bn_init_string(t, "", &err);

	bn_init_string(t, "\0", &err);

	bn_init_int(t, 100000, &err);

	bn_abs(t);

	bn_null(t);

	bn_init_string(t, "1000000000000000000", &err);

	bn* k = bn_init(t, &err);

	bn* l = bn_mul(t, k);
	
	bn* p = bn_add(t, k);
	
	bn* m = bn_div(t, k);

	bn* f = bn_sub(m, t);

	bn_cmp(f, t);

	bn* h = bn_add(f, k);

	add_int(f, 1000000, &err);

	add_int(f, base + 1, &err);

	bn_sign(f);

	multiple_int(m, 10, &err);

	multiple_int_bn(k, m, 10);

	div_int(p, 10000000);

	bn_init_int(h ,	1, &err);

	copy(p, bn_div(t, h), &err);

	bn_init_int(p, base + 1, &err);

	copy(h, bn_div(t, p), &err);

	char* c = bn_to_string(k, 10, &err);

	bn_cmp(t, k);

	print(m);
	print(k);
	print(p);
	print(l);
	print(f);
	printf("%c", *c);

	bn_delete(t);
	bn_delete(k);
	bn_delete(l);
	bn_delete(p);
	bn_delete(m);
	bn_delete(f);
	bn_delete(h);
	free(c);
	return 0;
}
