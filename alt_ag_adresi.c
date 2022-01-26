#include <stdio.h>

struct info {
	int n, nHost, nIp;
};

void set_info(struct info *inf, int mask) {
	inf->n = 32-mask;
	inf->nIp = 2^inf->n;
	inf->nHost = (2^inf->n)-2;
}

void print(const unsigned char *ip) {
	printf("\n[ ");
	for(size_t i=0;i<4;i++)
		printf("%d.", ip[i]);
	printf(" ]\n");
}

void print_bit(unsigned char val) {
	printf("\n[ ");
	for(int i=sizeof(val)*8-1;i>=0;i--) {
		if(val & 1<<i)
			printf("1");
		else
			printf("0");
	}
	printf(" ]\n");
}

void value_copy(unsigned char *dest, const unsigned char *src) {
	for(size_t i=0;i<4;i++)
		dest[i] = src[i];
}

void find_u_ip(unsigned char *ip, unsigned char *uip, int bit) {
	unsigned char subnet[4] = {0};

	// find network mask
	for(size_t i=0;i<4;i++) {
		for(int j=sizeof(subnet[i])*8-1;j>=0;j--) {
			subnet[i] |= 1<<j;
			bit--;
			if(!bit) break;
		}
		if(!bit) break;
	}

	//print(subnet);

	for(size_t i=0;i<4;i++)
		uip[i] = ip[i] & subnet[i];

/*
	for(size_t i=0;i<4;i++)
		print_bit(subnet[i]);
*/
}

int main() {
	unsigned char ip[4] = {192,168,10,16};

	unsigned char uip[4] = {0};

	find_u_ip(ip, uip, 24);

	print(uip);
}
