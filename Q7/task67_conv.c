#include <stdio.h>
#include <math.h>

long round_to_paise(double rupees) {
    return (rupees >= 0.0) ? (long)(rupees * 100.0 + 0.5) : (long)(rupees * 100.0 - 0.5);
}

int main(void)
{
    printf("=== Task 6: Formatted Output & Input Validation ===\n");
    long paise = 16250L;
    printf("Formatted Paise (%ld) -> Rs %ld.%02ld\n", paise, paise / 100, paise % 100);

    int prev = 0, curr = 0;
    const char *bad_input = "1200 abc";
    int parsed = sscanf(bad_input, "%d %d", &prev, &curr);
    printf("sscanf(\"%s\") returned %d (expected 2) -> Invalid input detected!\n", bad_input, parsed);

    printf("\n=== Task 7: Three Type-Conversion & Precision Surprises ===\n");
    int units = 150;
    double wrong_div = (units / 100) * 225.0;          /* Surprise 1: 150/100 truncates to 1 */
    printf("1. Integer division (150 / 100) * 225.0 = %.2f (expected 337.50)\n", wrong_div);

    unsigned int u = 10;
    int delta = -25;
    printf("2. Signed/Unsigned promotion (10u + (-25) > 0) = %d (wraps to %u!)\n",
           (u + delta > 0), u + delta);

    long big_paise = 3000000000L; /* Exceeds 32-bit signed INT_MAX (2,147,483,647) */
    int narrowed = (int)big_paise;
    printf("3. Narrowing cast (int)3000000000L = %d (overflows 32-bit int!)\n", narrowed);
    printf("4. Consistent rounding: Rs 2.256 -> %ld paise | Rs 2.254 -> %ld paise\n",
           round_to_paise(2.256), round_to_paise(2.254));
    return 0;
}
