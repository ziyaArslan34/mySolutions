/*
 * date        : 20.03.2021
 * copyright   : NONE
 * author      : Ziya ARSLAN
 * information : ascii table
*/

#include <stdio.h>

#define TABSIZE 10

void printTable(const char (*table)[][70]) {
	for(size_t i=0;i<TABSIZE;i++)
		printf("%s\n", (*table)[i]);
}

int main() {
	char table[TABSIZE][70] = {
		"_____________________________________________________________",
		"| a: \\x61 | b: \\x62 | c: \\x63 | d: \\x64 | e: \\x65 | f: \\x66 |",
		"| g: \\x67 | h: \\x68 | i: \\x69 | j: \\x6a | k: \\x6b | l: \\x6c |",
		"| m: \\x6d | n: \\x6e | o: \\x6f | p: \\x70 | r: \\x71 | s: \\x73 |",
		"| t: \\x74 | u: \\x75 | v: \\x76 | y: \\x79 | z: \\x7a | x: \\x78 |",
		"| q: \\x71 | w: \\x77 | .: \\x2e |  : \\x20 | {: \\x7b | }: \\x7d |",
		"| 0: \\x30 | 1: \\x31 | 2: \\x32 | 3: \\x33 | 4: \\x34 | 5: \\x35 |",
		"| 6: \\x36 | 7: \\x37 | 8: \\x38 | 9: \\x39|",
		"|____________________________________________________________"
	};

	printTable(&table);
}
