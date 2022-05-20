#include "BN.h"


bn* bn_new() {
	bn* t = (bn*)malloc(sizeof(*t));
	t->sign = 1;
	t->size = 1;
	t->r_s = 1;
	t->d = (int*)calloc(1, sizeof(t->d));
	return t;
	}
	
bn* bn_init(bn const *orig, bn_err *err){
	if (orig == NULL) {
		*err = EINVARG;
		return NULL;
	}
	bn * t = (bn*)malloc(sizeof(*t));
	t->sign = orig->sign;
	t->size = orig->size;
	t->r_s = orig->r_s;
	t->d = (int*)calloc(t->size, sizeof(t->d));
	for(int i = 0; i < t->r_s; ++i){
		t->d[i] = orig->d[i];
		}
	return t;
	}
	
int bn_delete(bn *t){
	if (t == NULL) {
		return 0;
	}
	free(t->d);
	free(t);
	return 0;
	}
	
int bn_null(bn const * t){
	if((t->r_s == 1) && (t->d[0] == 0)){
		return 1;
		}
	return 0;
	}	
	
// добавление int к bn
void add_int(bn* t, int c, bn_err *err){
	if (t == NULL) {
		*err = EINVARG;
		return;
	}
	int x = c + t->d[0];
	if (x < base){
		t->d[0] = x;
		return;
	} else if (t->r_s == 1){
		t->size += 1;
		t->r_s += 1;
		t->d = realloc(t->d, 2 * sizeof(int));
		t->d[1] = x / base;
		t->d[0] = x % base;	
	} else {
	int r = 0, i = 0;
	for(; i < t->r_s; ++i){
		x = t->d[i] + x + r;
		if(x >= base){
			x -= base;
			r = 1;
		} else {
			r = 0;
			}
		t->d[i] = x;
		x = 0;
		}
	if (r == 1){
		t->d[i] = 1;
	}	
	}
	return;
	}

// умножение bn на int
void multiple_int(bn* t, long c, bn_err *err){
	if (t == NULL) {
		*err = EINVARG;
		return;
	}
	long x = 0;
	int r = 0;
	for( int i = 0; i < t->r_s; ++i){	
		x = t->d[i] * c + r;		
		r = x / base;
		x -= r * base;			
		t->d[i] = x;
		}	
	if(r > 0){
		t->r_s += 1;
		t->size += 1;
		t->d = realloc(t->d, t->r_s * sizeof(int));
		t->d[t->r_s - 1] = r;
		}
	return;
	}

int multiple_int_bn(bn* rez, const bn* t, long c){
	rez->r_s = t->r_s;	
	if (c == 0){
		rez->r_s = 1;
		rez->d[0] = 0;
		return 0;		
		}
	long x = 0;
	int r = 0;
	for( int i = 0; i < t->r_s; ++i){	
		x = t->d[i] * c + r;		
		r = x / base;
		x-= r * base;			
		rez->d[i] = x;
		}	
	if(r > 0){
		rez->r_s += 1;		
		rez->d[rez->r_s - 1] = r;
		}
	return 0;
	}
	
// деление bn на int
int div_int(bn* t, long c){
	long x = 0;
	long r = 0;
	long z = 0;
	for(int i = t->r_s - 1; i >= 0; --i){	
		z = (t->d[i] + r * base);
		x = z / c;
		r = z - x*c;
		t->d[i] = x;
		}
	return r;
	}
			
int bn_init_string(bn *t, const char *init_string, bn_err *err){
	if (t == NULL) {
		*err = EINVARG;
		return INT_MAX;
	}
	long from = 0, count = strlen(init_string);
	t->sign = 1;
	if(count == 0){
		t->sign = 1;
		t->size = 1;
		t->r_s = 1;
		free(t->d);
		t->d = (int*)calloc(1, sizeof(t->d));
		return 0;
	} else {
		int z = 0;
		
		if(init_string[0] == '-'){
			t->sign = 0;
			from = 1;
			}
		if(init_string[0] == '+'){
			from = 1;
			}
		while(init_string[from] == '0'){
			++from;
			}
		if(init_string[from] == '\0'){
			t->sign = 1;
			t->size = 1;
			t->r_s = 1;
			free(t->d);
			t->d = (int*)calloc(1, sizeof(t->d));
			return 0;
			}
		t->size = (count - from - 1)/9 + 1;
		t->r_s = t->size;
		free(t->d);
		t->d = (int*)calloc(t->size, sizeof(t->d));
		int x = 0;
		count -= 9;
		for (; count >= from; count -= 9){
			for(int j = 0; j < 9; j++){
				x = x*10 + (init_string[j + count] - '0');
				}
			t->d[z++] = x;	
			x = 0;	
			}
		if ((count < from) && (count != from - 9)){
			for(int i = from; i < count + 9; ++i){
			x = x*10 + (init_string[i] - '0');
			}
			t->d[z++] = x;	
		}
	}
	return count;
	}
	
char int_to_ch (int c){
	if(c >= 0 && c < 10){
		return c + '0';
	} else {
		return c + 'A' - 10;
		}
	}

char* bn_to_string(bn const *t, int radix, bn_err *err){
	if(bn_null(t) == 1){
		char * c = (char*)malloc(2*sizeof(*c));
		c[0] = '0';
		c[1] = '\0';
		return c;
		}
	bn * z = bn_init(t, err);
	int s = 10;
	int it = 0, from = 0;
	char q;
	int a;
	char * c = (char*)malloc(s*sizeof(*c));
	for(int i = 0; i < s; ++i){
		c[i] = '\0';
		}
	if(t->sign == 0){
		c[0] = '-';
		from = 1;
		it = 1;
		}		
	while(bn_null(z) == 0){
		a = div_int(z, radix);
		q = int_to_ch(a);
		c[it++] = q;
		if(it == s - 1){
			s += 15;
			c = realloc(c, s);
			for(int i = it; i < s; ++i){
				c[i] = '\0';
				}
			}
		if((z->r_s > 1) && (z->d[z->r_s - 1] == 0)){
			--(z->r_s);		
			}	
		}
	bn_delete(z);
	for(int i = 0; i < (it / 2); ++i){
		q = c[i + from];
		c[i + from] = c[it - i - 1];
		c[it - i - 1] = q;
		}
	return c;
	}

int bn_init_int(bn *t, int init_int, bn_err *err){
	if (t == NULL) {
		*err = EINVARG;
		return INT_MAX;
	}
	if(init_int > 0){
		t->sign = 1;
	} else{
		t->sign = 0;
		init_int *= -1;
		}
	if (init_int < base){
		t->size = 1;
		t->r_s = 1;
		free(t->d);
		t->d = (int*)calloc(t->size, sizeof(t->d));
		*t->d = init_int;
	} else {
		t->size = 2;
		t->r_s = 2;
		free(t->d);
		t->d = (int*)calloc(t->size, sizeof(t->d));
		*t->d = init_int % base;
		*(t->d + 1) = init_int / base;	
		}
	return t->r_s;
	}
	
int print(bn* t){
	if( bn_null(t) ){
		printf("0\n");
		return 0;
		}
	if(t->sign == 0){
		printf("-");
		}
	if (t->d[t->r_s - 1] != 0){
	printf("%d", t->d[t->r_s - 1]);
		}
	for(int i = t->r_s - 2; i >= 0; --i){
		printf("%09d", t->d[i]);
		}
	printf("\n");
	return 0;
	}
		
int bn_abs_cmp(bn const *left, bn const *right){
	if (bn_null(right) && bn_null(left)){
		return 0;
	} else if (left->r_s > right->r_s){
		return 1;
	} else if(left->r_s < right->r_s){
		return -1;
	} else{
		int i = left->r_s - 1;
		while((left->d[i] == right->d[i]) && (i > 0)) { --i; }
		return (left->d[i] - right->d[i]);
		}
	}	
		
int bn_cmp(bn const *left, bn const *right){
	if (bn_null(right) && bn_null(left)){
		return 0;
	} else if (left->r_s > right->r_s || (left->sign == 1 && bn_null(right)) || (left->sign == 1 && right->sign == 0)){
		return 1;
	} else if(left->r_s < right->r_s  || (right->sign == 1 && left->sign == 0) || (right->sign == 1 && bn_null(left))){
		return -1;
	} else{
		int sign = 1;
		if((left->sign + right->sign) == 0){
			sign = -1;
			}
		int i = left->r_s - 1;
		while((left->d[i] == right->d[i]) && (i < left->r_s)) { --i; }
		if(left->d[i] - right->d[i] == 0){
			return 0;
			}
		return (left->d[i] - right->d[i])*sign;
		}
	}
		
int bn_neg(bn *t){
	return t->sign = (t->sign + 1) % 2;
	} 

int bn_abs(bn* t){
	if (bn_null(t)){
		return 0;
	} else {
		if (t->sign == 0){
			t->sign = 1;
			return -1;
		} else {
			return 1;
			}
		} // В(:т+ модул+
	}
	
int bn_sign(bn const *t){
	if (t == 0){
		return 0;
	} else if(t->sign == 0){
		return -1;
	} else {
		return 1;
		}	
	}

	// для  + +		
int *add(const bn *t, const  bn *right, int * size, bn_err *err){
	if (t == NULL || right == NULL) {
		*err = EINVARG;
		return NULL;
	}
	*size = (right->r_s > t->r_s ? right->r_s : t->r_s) + 1 ;
	int * z = (int *)calloc(*size, sizeof(int));
	int r = 0, i = 0;
	int x = 0, mi = (right->r_s > t->r_s ? t->r_s : right->r_s);
	for(; i < mi; ++i){
		x = t->d[i] + right->d[i] + r;
		if(x >= base){
			x -= base;
			r = 1;
		} else {
			r = 0;
			}
		z[i] = x;
		x = 0;
		}
	if (r == 1){
		z[i] = 1;
		r = 0;
		}
		i = mi;
	if (right->r_s > t->r_s){
		for(; i < right->r_s; ++i){		
			z[i] = z[i] + right->d[i] + r;
			if(z[i] >= base){
			z[i] -= base;
			r = 1;
		} else {
			r = 0;
			}
		}
	} else if (right->r_s < t->r_s){
		for(; i < t->r_s; ++i){
			z[i] = z[i] + t->d[i] + r;
			if(z[i] >= base){
			z[i] -= base;
			r = 1;
		} else {
			r = 0;
			}
		}
	}
	if (r == 1){
		z[i] = 1;
		r = 0;
		}
		i = mi;
	return z;
	}
	
	// для  t>=right
int *diff(const bn *t, const bn *right, int * size, bn_err *err){
	if (t == NULL || right == NULL) {
		*err = EINVARG;
		return NULL;
	}
	*size = (right->r_s > t->r_s ? right->r_s : t->r_s) + 1;
	int * z = (int *)calloc(*size, sizeof(int));
	int r = 0;
	int x = 0, mi = (right->r_s > t->r_s ? t->r_s : right->r_s);
	for(int i = 0; i < mi; ++i){
		x = t->d[i] - right->d[i] + r;
		if(x < 0){
			x = base + x;
			r = -1;
		} else {
			r = 0;
			}
		z[i] = x;
		x = 0;
		}
	if(r < 0){
		int p = mi;
		while(t->d[p] == 0){ ++p; }
		t->d[p--] -= 1;
		for(; p >= mi; --p){
			t->d[p] = base - 1;
			}
		r = 0; 
		}
	if (right->r_s < t->r_s){
		for(int i = mi; i < t->r_s; ++i){		
			z[i] = t->d[i] + r;
			r = 0;
			}
		}
	return z;
	}	
	
	//для перемножения модулей чисел
int* multiple(const bn *t, const  bn *right, int * size, bn_err *err){
	if (t == NULL || right == NULL) {
		*err = EINVARG;
		return NULL;
	}
	*size = right->r_s + t->r_s + 1;
	int* z = (int *)calloc(*size, sizeof(int));
	int r = 0, i = 0, j = 0;
	long long x;
	for(i = 0; i < right->r_s; ++i){
		x = 0;	
		
		for(j = 0; j < t->r_s; ++j){			
			x = r + (long)z[i + j] + (long int)t->d[j] * (long int)right->d[i];			
			r = (int)(x / base);	
			x -= r * base;
			z[i + j] = (int)x;
			}	
		if(r > 0){			
			z[i + j] = r;
			r = 0;
			}			
		r = 0;
		}
	if(r > 0){		
			z[i + j - 1] = r;
			r = 0;
			}
		
	return z;
	}
		
//----------------------------------------------------	
int bn_add_to(bn *t, bn const *right, bn_err *err){	
	if (t == NULL || right == NULL) {
		*err = EINVARG;
		return INT_MAX;
	}
	int si;
	int * size = &si;
	int *z;
	if(t->sign ^ right->sign){
		int s = bn_abs_cmp(t, right);		
		if(s == 0){
			free(t->d);
			t->sign = 1;
			t->r_s = 1;
			t->size = 2;
			t->d = (int *)calloc(2, sizeof(int));
			return 0;
		} else if(s > 0){
			z = diff(t, right, size, err);			
		} else {
			z = diff(right, t, size, err);
			t->sign = (t->sign + 1) % 2;
			}			
		free(t->d);
		t->size = *size;
		t->d = z;
		while(t->d[*size - 1] == 0 &&  *size-1 > 0) { --*size; }
		t->r_s = *size;
		
		if(t->size - t->r_s > 1){
			z = calloc((t->r_s + 1), sizeof(int));
			for(int i = 0; i < t->r_s; ++i){
				z[i] = t->d[i];
				}
			free(t->d);
			t->d = z;
			t->size = t->r_s + 1;
			}
	} else {	
		z = add(t, right, size, err);
		t->size = *size;
		free(t->d);
		t->d = z;
		while(t->d[*size-1] == 0 && *size > 1) { --*size; }// посмотреть тут
		t->r_s = *size;
		}
	return 0;
	}

int bn_sub_to(bn *t, bn const *right){
	bn_err err;
	bn * f = bn_new();
	f->size = right->size;
	f->r_s = right->r_s;
	free(f->d);
	f->d = right->d;
	f->sign = right->sign;
	bn_neg(f);
	bn_add_to(t, f, &err);
	f->d = NULL;
	bn_delete(f);
	return 0;
	}

bn* bn_add(bn const *left, bn const *right){
	bn_err err;
	bn* f = bn_init(left, &err);
	bn_add_to(f, right, &err);
	return f;
	}

bn* bn_sub(bn const *left, bn const *right){
	bn* f = bn_new();
	free(f->d);
	f->size = right->size;
	f->r_s = right->r_s;
	f->d = right->d;
	f->sign = right->sign;
	bn_neg(f);
	bn* t = bn_add(left, f);
	f->d = NULL;
	bn_delete(f);
	return t;
	
	}

int bn_mul_to(bn *t, bn const *right, bn_err *err){
	if (t == NULL || right == NULL) {
		*err = EINVARG;
		return INT_MAX;
	}
	int si = 0;
	int * size = &si;
	if (t->sign ^ right->sign){
		t->sign = 0;
	} else {
		t->sign = 1;
		}
	if(bn_null(right) || bn_null(t)){
		t->size = 2;
		t->r_s = 1;
		free(t->d);
		t->d = (int*)calloc(t->size, sizeof(*t->d));
		return 0;
		}
	if (right->r_s == 1 && right->d[0] == 1){
			return 0;
		} 
	
	int * z = multiple(t, right, size, err);
	free(t->d);
	t->size = *size;
	t->d = z;
	z = NULL;
	
	while(*size > 1 && t->d[*size-1] == 0) { --*size; }
	t->r_s = *size;
	if(t->size - t->r_s > 1){
		t->d = realloc(t->d, (t->r_s + 1)*sizeof(int));
		t->size = t->r_s + 1;
		}
	return 0;
	

	}

bn* bn_mul(bn const *left, bn const *right){
	bn_err err;
	bn *t = bn_init(left, &err);
	bn_mul_to(t, right, &err);
	return t;
	}

int move(bn* t){
	for(int i = t->r_s; i > 0; --i){
		t->d[i] = t->d[i - 1];
		}
	++(t->r_s);
	return 0;
	}

int bn_div_to(bn *t, bn const *right, bn_err *err){	
	if (t == NULL || right == NULL) {
		*err = EINVARG;
		return INT_MAX;
	}
	if (t->sign ^ right->sign){
		t->sign = 0;
	} else {
		t->sign = 1;
		}
	if (right->r_s == 1){
		if (right->d[0] == 1){
			return 0;
		} else if (right->d[0] == 0){
			t->sign = 1;
			t->size = 2;
			t->r_s = 1;
			t->d = realloc(t->d, t->size*sizeof(*t->d));
			t->d[0] = 0;
			return 0;
			}	
		}
	int h;
	if((h = bn_abs_cmp(t, right)) <= 0){
		t->size = 2;
		t->r_s = 1;
		t->d = realloc(t->d, t->size*sizeof(*t->d));
		t->d[0] = 0;
		if (h == 0){
			t->d[0] = 1;
			}
		return 0;
		}
	bn * proto_t = bn_init(t, err);
	bn *rez = bn_new();
	rez->size = t->size + 1;
	rez->r_s = 0;
	free(rez->d);
	rez->d = NULL;
	rez->d = (int*)calloc(rez->size, sizeof(*rez->d));
	bn * cur = bn_init(rez, err);
	cur->r_s = 0;
	bn * prom = bn_init(rez, err);
	int x, l, r, m;
	long long i;
	for (i = t->r_s - 1; i >= 0; --i) {		
		move(cur); // cur*base
		cur->d[0] = t->d[i];             
		x = 0;
		l = 0;
		r = base;
		if((bn_abs_cmp(cur, right)) < 0){
			r = -1;	
		}	      
		while (l <= r) {
			m = (l + r) / 2;
			multiple_int_bn(prom, right, m);										
			if((bn_abs_cmp(cur, prom)) >= 0){					
				 x = m;					
				 l = m + 1;                   
			}
			else {
				r = m - 1;
			}
		}
		multiple_int_bn(prom, right, x);
		rez->d[i] = x;
		++rez->r_s;																		
		bn_sub_to(cur, prom);			
		while(cur->r_s > 0 && cur->d[cur->r_s - 1] == 0) { --cur->r_s; }					   	                     
	}			
    bn_delete(prom);
    bn_delete(cur);
    free(t->d);
    if (rez->r_s == 0){
		rez->r_s = 1;
		}
    t->r_s = rez->r_s;
    t->d = rez->d;
    rez->d = NULL;
    bn_delete(rez);	
    if(t->sign == 0){
		rez = bn_mul(t, right);
		if(bn_abs_cmp(rez, proto_t) < 0){
			add_int(t, 1, err);
			}
		bn_delete(rez);	
		}
	bn_delete(proto_t);
	
	while((t->d[t->r_s - 1] == 0) &&  (t->r_s - 1 > 0)){ --t->r_s; }
	if(t->size - t->r_s > 1){
		int *z = calloc((t->r_s + 1), sizeof(*z));
		for(int i = 0; i < t->r_s; ++i){
			z[i] = t->d[i];
			}
		free(t->d);
		t->d = z;
		t->size = t->r_s + 1;
		}
     return 0;
	}
			
bn* bn_div(bn const *left, bn const *right){
	bn_err err;
	bn * m = bn_init(left, &err);
	bn_div_to(m, right, &err);
	return m;	
	}

int copy(bn* t, bn* f, bn_err *err) {
	if (t == NULL || f == NULL) {
		*err = EINVARG;
		return INT_MAX;
	}
	if (t->r_s < f->r_s) {
		t->size = f->size;
		t->d = realloc(t->d, f->size * sizeof(int));
	}
	for (int j = 0; j < f->r_s; ++j) {
		t->d[j] = f->d[j];
	}
	t->r_s = f->r_s;
	return 0;
}