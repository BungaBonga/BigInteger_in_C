#include "BN.h"

int main() {
	bn_err err;

	int* a = NULL;

	bn* t = NULL;

	bn* u;

	u = bn_init(t, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_1\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_1\t->\tPASSED\n");
	bn_delete(u);

	add_int(t, 1, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_2\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_2\t->\tPASSED\n");

	multiple_int(t, 1, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_3\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_3\t->\tPASSED\n");

	bn_init_string(t, "", &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_4\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_4\t->\tPASSED\n");

	bn_init_int(t, 100, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_5\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_5\t->\tPASSED\n");

	free(add(t, u, a, &err));
	if (err != EINVARG)
		fprintf(stdout, "Test_6\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_6\t->\tPASSED\n");

	free(diff(t, u, a, &err));
	if (err != EINVARG)
		fprintf(stdout, "Test_7\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_7\t->\tPASSED\n");

	free(multiple(t, u, a, &err));
	if (err != EINVARG)
		fprintf(stdout, "Test_8\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_8\t->\tPASSED\n");

	bn_add_to(t, u, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_9\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_9\t->\tPASSED\n");

	bn_mul_to(t, u, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_10\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_10\t->\tPASSED\n");

	bn_div_to(t, u, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_11\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_11\t->\tPASSED\n");

	copy(t, u, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_12\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_12\t->\tPASSED\n");

	t = bn_new();
	u = bn_new();

	if (bn_mul_to(u, t, &err) != 0) 
		fprintf(stdout, "Test_13\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_13\t->\tPASSED\n");

	if(bn_div_to(u, t, &err)!= 0)
		fprintf(stdout, "Test_14\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_14\t->\tPASSED\n");

	if (print(t) != 0)
		fprintf(stdout, "PRINT Test FAILED\n");
	else
		fprintf(stdout, "PRINT Test PASSED\n");

	free(bn_to_string(t, 10, &err));

	if (bn_init_int(t, -100, &err) != 1) 
		fprintf(stdout, "Test_15\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_15\t->\tPASSED\n");

	if (bn_init_string(t, "", &err) != 0)
		fprintf(stdout, "Test_16\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_16\t->\tPASSED\n");

	if (bn_init_string(t, "\0", &err) != 0)
		fprintf(stdout, "Test_17\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_17\t->\tPASSED\n");

	bn_init_int(t, 100000, &err);
	if (t->d[0] != 100000)
		fprintf(stdout, "Test_18\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_18\t->\tPASSED\n");

	multiple_int(t, 10000000, &err);
	if (err != EINVARG)
		fprintf(stdout, "Test_19\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_19\t->\tPASSED\n");

	bn_delete(t);
	t = bn_new();
	add_int(t, 1, &err);
	if (t->d[0] != 1)
		fprintf(stdout, "Test_20\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_20\t->\tPASSED\n");

	bn_delete(t);
	t = bn_new();
	add_int(t, 1000000001, &err);
	if ((t->d[0] != 1) && (t->r_s != 2) && (t->size != 2))
		fprintf(stdout, "Test_21\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_21\t->\tPASSED\n");

	if(bn_abs(t) != 1)
		fprintf(stdout, "Test_22\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_22\t->\tPASSED\n");

	if (bn_null(t) != 0)
		fprintf(stdout, "Test_23\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_23\t->\tPASSED\n");

	if (bn_init_string(t, "1000000000000000000", &err) == 0)
		fprintf(stdout, "Test_24\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_24\t->\tPASSED\n");

	err = ESUCCESS;
	bn* k = bn_init(t, &err);
	if (err == EINVARG) 
		fprintf(stdout, "Test_25\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_25\t->\tPASSED\n");

	err = ESUCCESS;
	bn* l = bn_mul(t, k);
	if (err == EINVARG)
		fprintf(stdout, "Test_26\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_26\t->\tPASSED\n");
	
	err = ESUCCESS;
	bn* p = bn_add(t, k);
	if (err == EINVARG)
		fprintf(stdout, "Test_27\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_27\t->\tPASSED\n");

	err = ESUCCESS;
	bn* m = bn_div(t, k);
	if (err == EINVARG)
		fprintf(stdout, "Test_28\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_28\t->\tPASSED\n");

	err = ESUCCESS;
	bn* f = bn_sub(m, t);
	if (err == EINVARG)
		fprintf(stdout, "Test_29\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_29\t->\tPASSED\n");

	if (bn_cmp(f, t) != -1)
		fprintf(stdout, "Test_30\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_30\t->\tPASSED\n");

	if (bn_cmp(t, k) == 0)
		fprintf(stdout, "Test_31\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_31\t->\tPASSED\n");

	bn_delete(l);
	l = bn_add(f, k);
	if((l->d[0] != 1) || (l->r_s != 1) || (l->size != 2))
		fprintf(stdout, "Test_32\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_32\t->\tPASSED\n");

	bn_delete(l);
	l = bn_add(t, m);
	if ((l->d[0] != 1) || (l->r_s != 2) || (l->size != 4))
		fprintf(stdout, "Test_33\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_33\t->\tPASSED\n");


	bn_delete(l);
	l = bn_add(m, t);
	if ((l->d[0] != 1) || (l->r_s != 2) || (l->size != 4))
		fprintf(stdout, "Test_34\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_34\t->\tPASSED\n");

	add_int(f, 1000000, &err);
	if ((f->d[0] != 1000999998) || (f->r_s != 2) || (f->size != 3))
		fprintf(stdout, "Test_35\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_35\t->\tPASSED\n");

	add_int(f, base + 1, &err);
	if (err == EINVARG) 
		fprintf(stdout, "Test_36\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_36\t->\tPASSED\n");

	if (bn_sign(f) != -1) 
		fprintf(stdout, "Test_37\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_37\t->\tPASSED\n");

	multiple_int(m, 10, &err);
	if ((m->d[0] != 10) || (m->r_s != 1) || (m->size != 2))
		fprintf(stdout, "Test_38\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_38\t->\tPASSED\n");

	multiple_int_bn(k, m, 10);
	if ((k->d[0] != 100) || (k->r_s != 1) || (k->size != 3))
		fprintf(stdout, "Test_39\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_39\t->\tPASSED\n");

	if ((div_int(p, 10000000) != 0) || (p->d[0] != 0) || (p->r_s != 3) || (p->size != 4))
		fprintf(stdout, "Test_40\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_40\t->\tPASSED\n");

	if ((bn_init_int(l, 1, &err) != 1) || (l->d[0] != 1) || (l->r_s != 1) || (l->size != 1))
		fprintf(stdout, "Test_41\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_41\t->\tPASSED\n");

	bn_delete(p);
	p = bn_div(t, l);
	if ((p->d[0] != 0) || (p->r_s != 3) || (p->size != 3))
		fprintf(stdout, "Test_42\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_42\t->\tPASSED\n");

	if ((bn_init_int(p, base + 1, &err) == 0) || (p->d[0] != 1) || (p->r_s != 2) || (p->size != 2))
		fprintf(stdout, "Test_43\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_43\t->\tPASSED\n");

	bn_delete(l);
	l = bn_div(t, p);
	if ((l->d[0] != 999999998) || (l->r_s != 1) || (l->size != 2))
		fprintf(stdout, "Test_44\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_44\t->\tPASSED\n");

	if (bn_cmp(t, k) != 1)
		fprintf(stdout, "Test_44\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_44\t->\tPASSED\n");

	if (copy(l, m, &err) == INT_MAX)
		fprintf(stdout, "Test_46\t->\tFAILED\n");
	else
		fprintf(stdout, "Test_46\t->\tPASSED\n");

	bn_delete(u);
	bn_delete(t);
	bn_delete(k);
	bn_delete(l);
	bn_delete(p);
	bn_delete(m);
	bn_delete(f);
	free(a);
	return 0;
}
