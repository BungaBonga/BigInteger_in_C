#include "BN.h"

int main() {
	bn_err err;

	int* a = NULL;

	bn* t = NULL;

	bn* u;

	u = bn_init(t, &err);
	bn_delete(u);

	add_int(t, 1, &err);

	multiple_int(t, 1, &err);

	bn_init_string(t, "", &err);

	bn_init_int(t, 100, &err);

	free(add(t, u, a, &err));

	free(diff(t, u, a, &err));

	free(multiple(t, u, a, &err));

	bn_add_to(t, u, &err);

	bn_mul_to(t, u, &err);

	bn_div_to(t, u, &err);

	copy(t, u, &err);



	t = bn_new();
	u = bn_new();

	bn_mul_to(u, t, &err);

	bn_div_to(u, t, &err);

	print(t);

	free(bn_to_string(t, 10, &err));

	bn_init_int(t, -100, &err);

	bn_init_string(t, "", &err);

	bn_init_string(t, "- \0", &err);

	bn_init_int(t, 100000, &err);

	multiple_int(t, 10000000, &err);

	bn_delete(t);
	t = bn_new();
	add_int(t, 1, &err);

	bn_delete(t);
	t = bn_new();
	add_int(t, base + 1, &err);

	bn_abs(t);

	bn_null(t);

	bn_init_string(t, "1000000000000000000", &err);

	bn* k = bn_init(t, &err);

	bn* l = bn_mul(t, k);
	
	bn* p = bn_add(t, k);
	
	bn* m = bn_div(t, k);

	bn* f = bn_sub(m, t);

	bn_cmp(f, t);

	bn_delete(l);
	l = bn_add(f, k);

	add_int(f, 1000000, &err);

	add_int(f, base + 1, &err);

	bn_sign(f);

	multiple_int(m, 10, &err);

	multiple_int_bn(k, m, 10);

	div_int(p, 10000000);

	bn_init_int(l ,	1, &err);

	bn_delete(p);
	p = bn_div(t, l);

	bn_init_int(p, base + 1, &err);

	bn_delete(l);
	l = bn_div(t, p);

	char* c = bn_to_string(k, 10, &err);

	bn_cmp(t, k);

	copy(l, m, &err);

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
	free(c);
	free(a);
	return 0;
}
