#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REC_ARRAY_SIZE 26

struct Record {
	char name[50], surname[50];
	int id;
	char policlinic[50];
};

struct Node {
	struct Record rec;
	struct Node *next;
};

struct Rec {
	char ch;
	struct Node *ptr;
}*rec_array = NULL;

typedef struct Record record_t;
typedef struct Node node_t;

int search_record(const record_t*);

void destroy(void) {
	for(size_t i=0;i<REC_ARRAY_SIZE;i++) {
		node_t *iter = rec_array[i].ptr;
		while(iter != NULL) {
			free(iter);
			iter = iter->next;
		}
		rec_array[i].ptr = NULL;
	}
}

node_t *get_node_index(node_t **nd, int idx) {
	node_t *tmp = *nd;

	if(!idx)
		return tmp;

	for(int i=0;i<idx-1;i++)
		tmp = tmp->next;
	return tmp->next;
}

node_t *create_node(const record_t *rc) {
	node_t *root = (node_t*)malloc(sizeof(node_t));

	if(!root) {
		destroy();
		exit(-1);
	}

	root->next = NULL;
	root->rec = *rc;

	return root;
}

void print_node(const node_t *nd) {
	if(!nd)
		return;

	printf("\nisim       : %s\n", nd->rec.name);
	printf("soyisim    : %s\n", nd->rec.surname);
	printf("policlinic : %s\n", nd->rec.policlinic);
	printf("numara     : %d\n\n", nd->rec.id);
}

void print_record(void) {
	for(size_t i=0;i<REC_ARRAY_SIZE;i++) {
		if(!rec_array[i].ptr)
			continue;

		printf("\n------[%c bolumu]------\n", rec_array[i].ch);
		node_t *iter = rec_array[i].ptr;

		while(iter != NULL) {
			print_node(iter);
			iter = iter->next;
		}
		printf("\n----------------------\n");
	}
}

void del_record(const record_t *rc) {
	int idx = search_record(rc);
	if(idx == -1) {
		printf("\nBoyle bi kayit yok\n");
		return;
	}

	int del = rc->name[0] - 'a';
	node_t *iter = rec_array[del].ptr;

	for(int i=0;i<idx-1;i++)
		iter = iter->next;

	node_t *tmp = iter->next;
	iter->next = iter->next->next;
	free(tmp);
}

void add_record(const record_t *rc) {
	int idx = rc->name[0] - 'a';

	node_t *tmp = create_node(rc);
	node_t *iter = rec_array[idx].ptr;

	if(!iter) {
		rec_array[idx].ptr = tmp;
		return;
	}

	while(iter->next != NULL)
		iter = iter->next;
	iter->next = tmp;
}


int cmp(const record_t* r1, const record_t* r2) {
	return !strcmp(r1->name, r2->name) &&
			!strcmp(r1->surname, r2->surname) &&
			!strcmp(r1->policlinic, r2->policlinic);
}

int search_record(const record_t *rc) {
	int idx = rc->name[0] - 'a', i=0;

	node_t *iter = rec_array[idx].ptr;
	while(iter != NULL) {
		if(cmp(&iter->rec, rc))
			return i;
		i++;
		iter = iter->next;
	}

	return -1;
}

void rc_copy(record_t *arr, const node_t *tmp, size_t idx) {
	strcpy(arr[idx].name, tmp->rec.name);
	strcpy(arr[idx].surname, tmp->rec.surname);
	strcpy(arr[idx].policlinic, tmp->rec.policlinic);
	arr[idx].id = tmp->rec.id;
}

void display_sorted(node_t *iter, const char* type) {
	int cap = 1;
	size_t idx=0;
	node_t *tmp = iter;

	while(tmp != NULL) {
		cap++;
		tmp = tmp->next;
	}

	record_t *array = (record_t*)malloc(sizeof(record_t)*(size_t)(cap+1));
	tmp = iter;
	while(tmp != NULL) {
		rc_copy(array, tmp, idx++);
		tmp = tmp->next;
	}

	for(int i=0;i<cap-1;i++) {
		for(int j=0;j<cap-1;j++) {
			if(!strcmp(type, "isim")) {
				if(array[i].name[0] < array[j].name[0]) {
					record_t tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
				}
			} else if(!strcmp(type, "soyisim")) {
				if(array[i].surname[0] < array[j].surname[0]) {
					record_t tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
				}
			} else if(!strcmp(type, "polikilinik")) {
				if(array[i].name[0] < array[j].name[0]) {
					record_t tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
				}
			}
		}
	}

	for(int i=0;i<cap-1;i++) {
		printf("\nisim       : %s\n", array[i].name);
		printf("soyisim    : %s\n", array[i].surname);
		printf("policlinic : %s\n", array[i].policlinic);
		printf("numara     : %d\n\n", array[i].id);
	}

	free(array);
}

void sort_record(const char *type) {
	for(size_t i=0;i<REC_ARRAY_SIZE;i++) {
		node_t *iter = rec_array[i].ptr;
		if(iter == NULL)
			continue;

		printf("\n------[%c bolumu]------\n", rec_array[i].ch);
		display_sorted(iter, type);
		printf("\n-----------------------\n");
	}
}

void menu(void) {
	printf("\n\nKayit ekle            [1]\n");
	printf("Kayit sil             [2]\n");
	printf("Kayit arama           [3]\n");
	printf("isme gore sirala      [4]\n");
	printf("soyisme gire sirala   [5]\n");
	printf("pol. gore sirala      [6]\n");
	printf("Kayit listeleme       [7]\n\n");

	printf("exit                  [8]\n\n");
}

int entry_control(const char *e) {
	return strlen(e) > 1 ? 0 : (e[0] > '0' && e[0] < '9');
}

int clinic_control(const char *clinic) {
	static const char *clinics[] = {
		"kardiyoloji", "implant",
		"endoskopi", "ortodonti", NULL
	};

	for(size_t i=0;clinics[i] != NULL;i++)
		if(!strcmp(clinics[i], clinic))
			return 1;
	return 0;
}

int main(void) {
	rec_array = (struct Rec*)malloc(sizeof(struct Rec)*REC_ARRAY_SIZE);

	if(!rec_array)
		return -1;

	for(size_t i=0;i<REC_ARRAY_SIZE;i++) {
		rec_array[i].ch = (char)('a' + i);
		rec_array[i].ptr = NULL;
	}

	while(1) {
		char entry[5];
		record_t rc;

		menu();
		printf("islem: ");
		scanf("%s", entry);
		if(!entry_control(entry)) {
			printf("yanlis giris. Lutfen tekrar deneyin\n");
			continue;
		}

		int ent = atoi(entry);

		switch(ent) {
			case 1:
				printf("isim : "); scanf("%s", rc.name);
				printf("soyisim: "); scanf("%s", rc.surname);

				printf("(ortodonti, endoskopi, kardiyoloji, implant)\n");
				printf("poliklinik: "); scanf("%s", rc.policlinic);
				printf("numara : "); scanf("%d", &rc.id);

				add_record(&rc);
				break;
			case 2:
				printf("isim : "); scanf("%s", rc.name);
				printf("soyisim : "); scanf("%s", rc.surname);

				printf("(ortodonti, endoskopi, kardiyoloji, implant)\n");
				printf("poliklinik: ");
				scanf("%s", rc.policlinic);

				del_record(&rc);
				break;
			case 3:
				printf("isim : "); scanf("%s", rc.name);
				printf("soyisim : "); scanf("%s", rc.surname);

				printf("(ortodonti, endoskopi, kardiyoloji, implant)\n");
				printf("poliklinik: ");
				scanf("%s", rc.policlinic);

				int idx = search_record(&rc);
				if(idx != -1)
					print_node(get_node_index(&rec_array[rc.name[0] - 'a'].ptr, idx));
				else
					printf("kayit bulunamadi\n");
				break;
			case 4:
				sort_record("isim");
				break;
			case 5:
				sort_record("soyisim");
				break;
			case 6:
				sort_record("policlinic");
				break;
			case 7:
				system("clear");
				print_record();
				break;
			case 8:
				printf("hoscakalin. :)\n");
				free(rec_array);
				destroy();
				exit(0);
			default:
				printf("yanlis secim\n");
		}
	}

	return 0;
}
