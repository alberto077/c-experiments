#include <stdio.h>
#include <stdint.h>


typedef int32_t i32 ;
typedef int64_t i64 ;


int main(void) {
    i32 c;

    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
    return 0;
}
