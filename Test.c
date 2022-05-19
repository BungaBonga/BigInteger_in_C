#include "BN.h"

int main() {
	bn* k = bn_new();

	/*for(int i = 1;i < 10000;++i){
		multiple_int(k,i);
	}*/
	bn_init_int(k, 1000000000);
	print(k);
	//printf("%d \n %.06f \n",k->r_s,(clock()- tt)*1.0/CLOCKS_PER_SEC);
	//print(k);
	return 0;
}
