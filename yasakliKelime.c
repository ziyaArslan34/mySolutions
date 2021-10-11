/* Girilen metinde onceden belirlenmis
	kelimeleri sansurleyen kod

	ornek "merhaba illegal1 nasilsin" seklindeki inputun
	outputu "merhaba ******** nasilsin" seklinde olcaktir
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void foo(char *str) {
	int len = strlen(str);

	const char *banned[] = {"illegal1", "illegal2", "illegal3"};

	for(size_t i=0;i<len;i++) {
		for(size_t ban=0;ban<3;ban++) {
			int len2 = strlen(banned[ban]), index=0, flag=0;
			for(size_t tmp=i;tmp<len2+i;tmp++)
				if(str[tmp] == banned[ban][index++])
					flag++;
			if(flag == len2)
				for(size_t j=i;j<len2+i;)
					for(size_t m=0;m<len2;m++)
						if(str[j++] == banned[ban][m])
							str[j-1] = '*';
		}
	}
}

int main() {
	char str[100];
	fgets(str, sizeof(str), stdin);

	foo(str);
	printf("str: %s\n", str);

	return 0;
}
