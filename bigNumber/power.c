#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "big_number.h"

bignum_t big_pow(const char *base, const char *power) {
        bignum_t pw = init_initValue(power), i;
        char *ptr = (char*)malloc(sizeof(char)*3);
        if(!ptr)
                exit(254);

        strcpy(ptr, "1");

        for(i = init_initValue("0");;operator_plus(&i, "1")) {
                if(data_less(&i, &pw)) {
                        bignum_t res = init(20);
                        multiplication(&res, ptr, base);

                        free(ptr);

                        if((ptr = (char*)malloc(sizeof(char)*res.size + 1)) == NULL)
                                exit(255);
                        strcpy(ptr, res.data);
                        destroy(&res);
                } else {
                        break;
                }
        }

        destroy(&pw);
        destroy(&i);


        bignum_t result = init_initValue(ptr);
        free(ptr);

        return result;
}

int main(int argc, const char **argv) {
        if(argc != 3) {
                fprintf(stderr, "invalid args\n");
                return 256;
        }

        bignum_t res = big_pow(argv[1], argv[2]);

        printf("%s  uzeri %s : ", argv[1], argv[2]);
        print_bignum(&res);
        destroy(&res);
}
