#include "mbed.h"

#include "mbedtls/cipher.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

#include "randtest.h"

#include "mbedtls/platform.h"
#define ENT_SAMPLES 10000

#ifdef M_PI
#define PI	 M_PI
#else
#define PI	 3.14159265358979323846
#endif

DigitalOut led1(LED1);

extern "C"{
extern double pochisq(const double ax, const int df);
}

// main() runs in its own thread in the OS
int main()
{
    uint8_t rnd_val;
    double montepi, chip, scc, ent, mean, chisq;
    mbedtls_entropy_context entropy;    /* entropy pool for seeding PRNG */

    /*
     * Setup random number generator
     * (Note: later this might be done automatically.)
     */

    mbedtls_entropy_init(&entropy);

    int mbedtls_entropy_func( void *data, unsigned char *output, size_t len );

    /* Init random test suite. */
    rt_init(0);

    /* Collect bytes to tests of the source. */
    for (uint32_t i = 0; i < ENT_SAMPLES; ++i)
    {
        /* Wait for random value. */
        while (mbedtls_entropy_func(&entropy, &rnd_val, 1) != 0);
        /* Add value to the tests pool. */
        rt_add(&rnd_val, 1);
        /* Print something sometimes to get developers know that everything works. */
        if (i % 100 == 0)
        {
            mbedtls_printf("Collected %lu bytes.\n", i);
            led1 = !led1;
        }
    }

    /* Finish tests and prepare values for printing. */
    rt_end(&ent, &chisq, &mean, &montepi, &scc);

    /* Calculate probability of observed distribution occurring from
     * the results of the Chi-Square test */

    chip = pochisq(chisq, 255);

    /* Show out interesting numbers. */
    mbedtls_printf("Entropy = %f bits per byte.\n", ent);
    mbedtls_printf("\nOptimum compression would reduce the size\n");
    mbedtls_printf("of this %d byte file by %d percent.\n\n", ENT_SAMPLES, (short) ((100 * ( 8 - ent) / (8.0))));
    mbedtls_printf("Chi square distribution for %d samples is %1.2f, and randomly\n", ENT_SAMPLES, chisq);
    if (chip < 0.0001) {
        mbedtls_printf("would exceed this value less than 0.01 percent of the times.\n\n");
    } else if (chip > 0.9999) {
        mbedtls_printf("would exceed this value more than than 99.99 percent of the times.\n\n");
    } else {
        mbedtls_printf("would exceed this value %1.2f percent of the times.\n\n", chip * 100);
    }
    mbedtls_printf( "Arithmetic mean value of data bytes is %1.4f (%.1f = random).\n", mean, 127.5);
    mbedtls_printf("Monte Carlo value for Pi is %1.9f (error %1.2f percent).\n", montepi, 100.0 * (fabs(PI - montepi) / PI));
    mbedtls_printf("Serial correlation coefficient is ");
    if (scc >= -99999) {
        mbedtls_printf("%1.6f (totally uncorrelated = 0.0).\n", scc);
    } else {
        mbedtls_printf("undefined (all values equal!).\n");
    }


    while (true) {
        led1 = !led1;
        wait(0.5);
    }
}
