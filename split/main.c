#include "split.h"

int main() {
	type_t spl = init(10);
	split_str(&spl, "ziya arslan#0536 294 96 10#25#erxurum#istanbul", "#");
	split_str(&spl, "test1+test2-test3:test4&test5", "&:+-");

	print_split(&spl);
	destroy_split(&spl);
}
