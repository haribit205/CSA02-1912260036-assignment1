#include <stdio.h>
#include <limits.h>

typedef unsigned short meter_t;

long compute_bill_paise(unsigned int units) {
    long paise = 5000L;
    if (units > 200U) {
        paise += (long)(units - 200U) * 450L + 100L * 225L;
    } else if (units > 100U) {
        paise += (long)(units - 100U) * 225L;
    }
    return paise;
}

float compute_bill_float(unsigned int units) {
    float rs = 50.0f;
    if (units > 200U) {
        rs += (units - 200U) * 4.50f + 100.0f * 2.25f;
    } else if (units > 100U) {
        rs += (units - 100U) * 2.25f;
    }
    return rs;
}

int main(void) {
    printf("=== Task 9: Boundary & Rollover Validation ===\n");
    struct { const char *label; long prev; long curr; int valid; } cases[] = {
        {"Zero units (500->500)", 500, 500, 1},
        {"Slab 1 boundary (100->200)", 100, 200, 1},
        {"Slab 2 normal (100->250)", 100, 250, 1},
        {"Slab 2 boundary (100->300)", 100, 300, 1},
        {"Slab 3 normal (100->450)", 100, 450, 1},
        {"16-bit rollover (65400->120)", 65400, 120, 1},
        {"Negative reading (-10->200)", -10, 200, 0},
        {"Non-rollover drop (500->420)", 500, 420, 0}
    };
    long hand_5_total = 0;
    for (int i = 0; i < 8; i++) {
        if (!cases[i].valid || cases[i].prev < 0 || cases[i].curr < 0 || cases[i].prev > 65535 || cases[i].curr > 65535) {
            printf("%-30s -> REJECTED (Invalid reading)\n", cases[i].label);
            continue;
        }
        unsigned int u = (meter_t)((meter_t)cases[i].curr - (meter_t)cases[i].prev);
        if (cases[i].curr < cases[i].prev && cases[i].prev < 60000) {
            printf("%-30s -> REJECTED (Backward reading without rollover)\n", cases[i].label);
            continue;
        }
        long bill = compute_bill_paise(u);
        if (i < 5) hand_5_total += bill;
        printf("%-30s -> %3u units | Bill = Rs %ld.%02ld\n",
               cases[i].label, u, bill / 100, bill % 100);
    }
    printf("Hand-Verified 5-Bill Total = Rs %ld.%02ld\n", hand_5_total / 100, hand_5_total % 100);

    printf("\n=== Task 10: Village (4k), Taluk (60k), District (800k) Scale Comparison ===\n");
    long counts[] = {4000L, 60000L, 800000L};
    const char *names[] = {"Village (4,000)", "Taluk (60,000)", "District (800,000)"};
    for (int s = 0; s < 3; s++) {
        float f_sum = 0.0f;
        long long ll_paise = 0LL;
        for (long i = 0; i < counts[s]; i++) {
            unsigned int u = (unsigned int)(80 + (i % 250));
            f_sum += compute_bill_float(u);
            ll_paise += compute_bill_paise(u);
        }
        double exact_rs = ll_paise / 100.0;
        printf("%-18s | Exact(ll)=Rs %12.2f | float=Rs %12.2f | Drift=Rs %+.2f\n",
               names[s], exact_rs, (double)f_sum, (double)f_sum - exact_rs);
    }
    return 0;
}
