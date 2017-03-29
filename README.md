# Getting started with entropy tester on mbed OS

This example collects data from entropy source on given platform and shows information about:
* Entropy
* Chi square distribution
* Arithmetic mean
* Monte Carlo
* Serial correlation

This is port of ent - public domain code (http://www.fourmilab.ch/random/). There is one change in ent files - Added extern "C" in randtest.h .

## Required hardware
* A supported board - [nRF52840 DK](https://developer.mbed.org/platforms/Nordic-nRF52-DK/).

## Import the example application

Just clone this repository.

```
mbed import https://github.com/kl-cruz/mbed-os-example-ent
cd mbed-os-example-ent
```

## Now compile

Invoke `mbed compile`, and specify the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`). For example, for the ARM Compiler 5:

```
mbed compile -m <TARGET_NAME> -t ARM
```

Your PC may take a few minutes to compile your code. At the end, you see the following result:

```
+-----------------------+-------+-------+-------+
| Module                | .text | .data |  .bss |
+-----------------------+-------+-------+-------+
| Fill                  |    98 |     7 |    54 |
| Misc                  | 43762 |  2217 |  3325 |
| features/mbedtls      |  5582 |     0 |     0 |
| hal                   |   384 |     0 |    16 |
| platform              |  1229 |     4 |   264 |
| rtos                  |    38 |     4 |     4 |
| rtos/rtx              |  5915 |    20 |  7550 |
| targets/TARGET_NORDIC |  9732 |    36 |  1019 |
| Subtotals             | 66740 |  2288 | 12232 |
+-----------------------+-------+-------+-------+
Allocated Heap: 232392 bytes
Allocated Stack: 2048 bytes
Total Static RAM memory (data + bss): 14520 bytes
Total RAM memory (data + bss + heap + stack): 248960 bytes
Total Flash memory (text + data + misc): 69028 bytes
Image: .\BUILD\<TARGET_NAME>\ARM\mbed-os-example-ent.bin
```

### Program application

1. Connect your mbed device to the computer over USB.
2. Copy the application binary file to the mbed device.
3. Open terminal with proper serial port (9600 bauds, 8 bytes, one stop bit, no hw flow control).
4. Press the reset button to start the program.

## Troubleshooting

1. Make sure `mbed-cli` is working correctly and its version is `>1.0.0`.

    ```
    mbed --version
    ```

 If not, you can update it:

    ```
    pip install mbed-cli --upgrade
    ```
