#include "BN.h"

int main() {
	bn_err err;
	bn* k = bn_new(&err);
	bn* t = bn_new(&err);
	bn_init_string(t, "100000000000000000", &err);
	bn_init_string(k, "200000000000000000", &err);
	t = bn_mul(t, k);
	print(t);
	bn_delete(t);
	bn_delete(k);
	return 0;
}
