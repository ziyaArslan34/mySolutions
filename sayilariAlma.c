/* ekrana yazdiginiz sey bidaha silinmez dikkatli kullanin */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int foo() {
	struct termios _old, _new;
	int ch;
	tcgetattr(STDIN_FILENO, &_old);
	_new = _old;
	_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &_new);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &_old);
	return ch;
}

struct ARRAY {
	int cap;
	int size;
};

void init(struct ARRAY *info) {
	info->cap = 4;
	info->size = 0;
}

char *getStr(struct ARRAY *info) {
	char *str = (char*)malloc(sizeof(char)*info->cap);
	printf("str: ");

	while(1) {
		if(info->size >= info->cap) {
			info->cap *= 2;
			str = (char*)realloc(str, sizeof(char)*info->cap);
		}
		int ch = foo();
		str[info->size] = ch;
		if(str[info->size] == '\b') {
			fprintf(stdout, "\r%d", (int)strlen(str)-1);
			continue;
		} if(str[info->size] == '\n') {
				str[info->size] = '\0';
				break;
		}

		fprintf(stdout, "%c", ch);
		info->size++;
	}

	return str;
}

int ctrlNum(const char ch) { return (ch >= 48 && ch <= 57); }

int *getNum(const char *str, struct ARRAY *info) {
	int len = strlen(str);
	int *array = (int*)malloc(sizeof(int)*info->cap);

	for(int i=0;i<len;) {
		char tmp[10];
		int index=0, j;

		for(j=i;ctrlNum(str[i++]);j++)
			tmp[index++] = str[j];
		tmp[index] = '\0';
		if(info->size >= info->cap) {
			info->cap *= 2;
			array = (int*)realloc(array, sizeof(int)*info->cap);
		}

		if(tmp[0] >= 48 && tmp[0] <= 57)
			array[info->size++] = atoi(tmp);
		memset(tmp, 0, strlen(tmp));
	}

	return array;
}

int main() {
	struct ARRAY chars, ints;
	init(&chars);
	init(&ints);

	char *str = getStr(&chars);
	str[strlen(str)] = '\0';

	printf("\nstr: %s\n", str);

	int *nums = getNum(str, &ints);

	for(int i=0;i<ints.size;i++) {
		for(int j=0;j<ints.size;j++) {
			if(nums[i] > nums[j]) {
				int tmp = nums[i];
				nums[i] = nums[j];
				nums[j] = tmp;
			}
		}
	}

	for(int i=0;i<ints.size;i++)
		printf("%d  ", nums[i]);

	printf("\n");

	free(str);
	free(nums);

	return 0;
}
