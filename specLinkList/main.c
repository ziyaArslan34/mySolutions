#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedlist.h"

typedef struct {
	char adSoyad[30];
	int no;
	int vize, odev, final;
	char oncekiKod[8], ozelKod[8];
}person_t;

void print(const void *data) {
	const person_t *pr = (const person_t*)data;
	printf("([%s][%d]) ([%d][%d][%d]) ([%s][%s])\n",pr->adSoyad, pr->no, pr->vize, pr->odev, pr->final, pr->oncekiKod, pr->ozelKod);
}

int cmp(const void *a, const void *b) {
	return ((const person_t*)a)->no < ((const person_t*)b)->no;
}

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

char *combining(const person_t *pr) {
	char str[1024] = {0};
	sprintf(str, "%s:%d:%d:%d:%d:%s:%s",
			pr->adSoyad, pr->no,
			pr->vize, pr->odev, pr->final,
			pr->oncekiKod, pr->ozelKod);

	int sums[7] = {0};
	size_t i, len = strlen(str);

	for(i=0;i<len;i++)
		sums[0] += (int)str[i];
	for(i=1;i<len;i += 2)
		sums[1] += (int)str[i];
	for(i=2;i<len;i += 2)
		sums[2] += (int)str[i];
	for(i=1;i<len;i += 3)
		sums[3] += (int)str[i];
	for(i=2;i<len;i += 3)
		sums[4] += (int)str[i];
	for(i=1;i<len;i += 4)
		sums[5] += (int)str[i];
	for(i=2;i<len;i += 4)
		sums[6] += (int)str[i];

	char *specNumber;

	if((specNumber = (char*)malloc(sizeof(char)*8)) == NULL) {
		perror("");
		return NULL;
	}

	for(i=0;i<7;i++)
		specNumber[i] = (char)(sums[i] % 8) + '0';
	specNumber[7] = '\0';

	return specNumber;
}

person_t create_pr(const char *name, const char *prev) {
	person_t pr;

	strcpy(pr.adSoyad, name);
	strcpy(pr.oncekiKod, prev);

	pr.no = my_rand(100, 999);
	pr.vize = my_rand(10, 100);
	pr.odev = my_rand(10, 100);
	pr.final = my_rand(10, 100);


	return pr;
}

void set_spec_code(person_t *pr) {
	char *spec;
	if((spec = combining(pr)) == NULL) {
		perror("");
		return;
	}

	strcpy(pr->ozelKod, spec);
	free(spec);
}

int main() {
	srand((unsigned)time(NULL));

	person_t proot = create_pr("rname", "0000000");
	set_spec_code(&proot);

	char prev[10];
	strcpy(prev, proot.ozelKod);

	person_t tmp = proot;

	linkedList *root = init_root(&proot, sizeof(person_t));

	for(int i=0;i<10;i++) {
		tmp = create_pr("rname", prev);
		set_spec_code(&tmp);
		add_to(&root, &tmp);
		strcpy(prev, tmp.ozelKod);
	}

	print_list(&root, print);
	destroy_list(&root);
}
