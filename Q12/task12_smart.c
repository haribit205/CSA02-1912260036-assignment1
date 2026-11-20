#include <stdio.h>
#include <stdint.h>

typedef struct {
    long fixed_charge_paise;
    long offpeak_rate_paise_per_kwh;
    int  peak_surcharge_percent; /* +20% between 18:00 and 22:00 */
} TariffConfig;

int main(void)
{
    /* Loaded at runtime (e.g., from tariff.cfg) instead of hardcoded #define */
    TariffConfig cfg = {5000L, 450L, 20};

    /* Simulate 1 day (96 intervals of 15 min) for a smart meter in Watt-hours (Wh) */
    uint64_t total_wh = 0ULL;
    uint64_t peak_wh = 0ULL;
    for (int slot = 0; slot < 96; slot++) {
        int hour = slot / 4;
        uint32_t interval_wh = (hour >= 18 && hour < 22) ? 450U : 150U;
        total_wh += interval_wh;
        if (hour >= 18 && hour < 22) {
            peak_wh += interval_wh;
        }
    }
    uint64_t offpeak_wh = total_wh - peak_wh;
    uint64_t monthly_offpeak_wh = offpeak_wh * 30ULL;
    uint64_t monthly_peak_wh    = peak_wh * 30ULL;

    long offpeak_paise = (long)((monthly_offpeak_wh * cfg.offpeak_rate_paise_per_kwh + 500ULL) / 1000ULL);
    long peak_rate     = cfg.offpeak_rate_paise_per_kwh * (100 + cfg.peak_surcharge_percent) / 100;
    long peak_paise    = (long)((monthly_peak_wh * peak_rate + 500ULL) / 1000ULL);
    long total_paise   = cfg.fixed_charge_paise + offpeak_paise + peak_paise;

    printf("=== Task 12: Smart-Meter 64-bit ToD Billing Validation ===\n");
    printf("Monthly Off-Peak Energy : %llu Wh (%.2f kWh) @ Rs %ld.%02ld/kWh = Rs %ld.%02ld\n",
           (unsigned long long)monthly_offpeak_wh, monthly_offpeak_wh / 1000.0,
           cfg.offpeak_rate_paise_per_kwh / 100, cfg.offpeak_rate_paise_per_kwh % 100,
           offpeak_paise / 100, offpeak_paise % 100);
    printf("Monthly Peak (6-10 PM)  : %llu Wh (%.2f kWh) @ Rs %ld.%02ld/kWh = Rs %ld.%02ld\n",
           (unsigned long long)monthly_peak_wh, monthly_peak_wh / 1000.0,
           peak_rate / 100, peak_rate % 100,
           peak_paise / 100, peak_paise % 100);
    printf("Total Monthly Smart Bill: Rs %ld.%02ld (Fixed Rs %ld.%02ld included)\n",
           total_paise / 100, total_paise % 100,
           cfg.fixed_charge_paise / 100, cfg.fixed_charge_paise % 100);
    return 0;
}
