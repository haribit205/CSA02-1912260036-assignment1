#include <stdio.h>
#include "tariff.h"

unsigned int calc_units(meter_t prev, meter_t curr) {
    unsigned int u = (meter_t)(curr - prev);
#ifdef DEBUG
    printf("[DEBUG] prev=%u, curr=%u -> units=%u\n", prev, curr, u);
#endif
    return u;
}

long calc_bill_paise(unsigned int units) {
    long total = FIXED_FEE_PAISE;
    if (units > SLAB2_LIMIT) {
        total += (units - SLAB2_LIMIT) * RATE_SLAB3_PAISE + (SLAB2_LIMIT - SLAB1_LIMIT) * RATE_SLAB2_PAISE;
    } else if (units > SLAB1_LIMIT) {
        total += (units - SLAB1_LIMIT) * RATE_SLAB2_PAISE;
    }
#ifdef DEBUG
    printf("[DEBUG] units=%u -> total_paise=%ld\n", units, total);
#endif
    return total;
}

int main(void) {
    unsigned int u = calc_units(65400, 120);
    long bill = calc_bill_paise(u);
    printf("Final Bill: %u units -> Rs %ld.%02ld\n", u, bill / 100, bill % 100);
    return 0;
}
