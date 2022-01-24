#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pair { size_t begin, end; };

int findLocation(const char *s1, const char *s2, struct pair *p) {
	size_t lenSrc = strlen(s2);
	size_t lenDest = strlen(s1);

	for(size_t i=0;i<lenDest;i++) {
		size_t cnt=0, j,m;

		for(m=i, j=0;m<lenDest && j < lenSrc;m++, j++)
			if(s1[m] == s2[j])
				cnt++;
		if(cnt == lenSrc) {
			/*for(size_t idx=i;idx<lenSrc+i;idx++)
				s1[idx] = '*';
			*/

			p->begin = i;
			p->end = m;

			return 1;
		}
	}

	return 0;
}

int main() {
	struct pair p = {0,0};

	const char *dest = "I watched you, my arms are tied";
	const char *src = "my arms";

	if(findLocation(dest, src, &p))
		printf("[ begin, end ] : %zu %zu\n", p.begin, p.end);
	else
		printf("not found\n");
}
