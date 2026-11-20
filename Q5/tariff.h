#ifndef TARIFF_H
#define TARIFF_H

#define SLAB1_LIMIT        100U
#define SLAB2_LIMIT        200U
#define RATE_SLAB1_PAISE   0L
#define RATE_SLAB2_PAISE   225L
#define RATE_SLAB3_PAISE   450L
#define FIXED_FEE_PAISE    5000L

typedef unsigned short meter_t;

unsigned int calc_units(meter_t prev, meter_t curr);
long calc_bill_paise(unsigned int units);

#endif /* TARIFF_H */
