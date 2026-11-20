#include <stdio.h>

#define RUPEES_TO_PAISE(rs) ((long)((rs) * 100.0 + 0.5))
#define BAD_SQUARE(x) x * x
#define SAFE_SQUARE(x) ((x) * (x))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static inline int max_inline(int a, int b) {
    return (a > b) ? a : b;
}

int main(void)
{
    int a = 4;
    printf("RUPEES_TO_PAISE(162.50) = %ld paise\n", RUPEES_TO_PAISE(162.50));
    printf("BAD_SQUARE(a + 1)  = %d (expands to 4 + 1 * 4 + 1 = 9!)\n", BAD_SQUARE(a + 1));
    printf("SAFE_SQUARE(a + 1) = %d (expands to ((4 + 1) * (4 + 1)) = 25)\n", SAFE_SQUARE(a + 1));

    int i = 5, j = 3;
    int m1 = MAX(i++, j); /* i++ evaluated TWICE because i > j is true */
    printf("MAX(i++, j) with i=5, j=3 -> result=%d, i became %d (double increment!)\n", m1, i);

    i = 5; j = 3;
    int m2 = max_inline(i++, j);
    printf("max_inline(i++, j) with i=5, j=3 -> result=%d, i became %d (safe)\n", m2, i);
    return 0;
}
