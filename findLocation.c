#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pair { size_t begin, end; };

struct pair *find_location_all(const char *s1, const char *s2, size_t *len) {
	size_t size=0, cap=4;

	struct pair *p = (struct pair*)malloc(sizeof(struct pair)*cap);
	if(!p) {
		fprintf(stderr, "memory errror\n");
		return NULL;
	}

	size_t lenSrc = strlen(s2);
	size_t lenDest = strlen(s1);

	for(size_t i=0;i<lenDest;i++) {
		size_t cnt=0, j,m;

		for(m=i, j=0;m<lenDest && j < lenSrc;m++, j++)
			if(s1[m] == s2[j])
				cnt++;
		if(cnt == lenSrc) {
			if(size >= cap) {
				cap *= 2;
				p = (struct pair*)realloc(p,sizeof(struct pair)*cap);
				if(!p) {
					fprintf(stderr, "memory error\n");
					free(p);
					return NULL;
				}
			}

			p[size].begin = i;
			p[size].end = m;
			size++;
		}
	}

	*len = size;
	return p;
}

int main() {
	const char *dest = "mert mert mert mert mert";
	const char *src = "mert";

	size_t size=0;

	struct pair *p = find_location_all(dest, src, &size);

	if(!size) {
		fprintf(stderr, "element not found\n");
		return 1;
	}

	if(!p)
		return 1;

	for(size_t i=0;i<size;i++)
		printf("\n[ %zu %zu ]\n", p[i].begin, p[i].end);

	free(p);
}
