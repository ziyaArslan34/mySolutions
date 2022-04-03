#include "split.h"
#include <stdio.h>

int main() {
	split_t spl = init_split(10);
	str_split(&spl, "[25][arslan]", "[]");

	print_split(&spl);

	destroy_split(&spl);
}
