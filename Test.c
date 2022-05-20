#include "BN.h"

int main() {
	bn_err err;
	bn* t = bn_new(&err);

	bn_null(t);

	bn_init_string(t, "100000000000000000", &err);

	bn* k = bn_init(t, &err);

	bn* l = bn_mul(t, k);
	
	bn* p = bn_add(l, k);
	
	bn* m = bn_div(t, k);

	bn* f = bn_sub(t, k);

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
