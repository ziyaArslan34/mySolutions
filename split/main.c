#include "split.h"

int main() {
	split_t spl = init_split(10);
	str_split(&spl, "ziya arslan#0536 294 96 10#25#erxurum#istanbul", "#");
	str_split(&spl, "test1+test2-test3:test4&test5", "&:+-");

	print_split(&spl);
	destroy_split(&spl);
}
