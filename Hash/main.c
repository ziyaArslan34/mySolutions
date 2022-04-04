#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main() {
	hash_t hash = init_hash();
	char str[1024] = {0};
	printf("enter text: ");
	fgets(str, 1024, stdin);
	str[strlen(str)-1] = '\0';

	encrypt(&hash, str);
	print_hash(&hash);

	char *dec = decrypt(&hash);

	printf("%s\n", dec);

	destroy_hash(&hash);
	free(dec);
}
