# Silicon Labs SLSTK3301A

## Overview
Silicon Labs EFM32 Tiny Gecko 11 Starter Kit is equipped with the EFM32 microcontroller. It is specifically designed for low-power applications, having energy-saving peripherals, different energy modes and short wake-up times.

The starter kit is equipped with an Advanced Energy Monitor. This allows you to actively measure the power consumption of your hardware and code, in real-time.

## Hardware
![SLSTK3301A Starter Kit](images/slstk3301a.png)

### MCU
| MCU             | EFM32TG11B520F128GM80                                |
|-----------------|------------------------------------------------------|
| Family          | ARM Cortex-M0PLUS                                    |
| Vendor          | Silicon Labs                                         |
| Vendor Family   | EFM32 Tiny Gecko 11B                                 |
| RAM             | 32.0KB                                               |
| Flash           | 128.0KB                                              |
| EEPROM          | no                                                   |
| Frequency       | up to 48 MHz                                         |
| FPU             | no                                                   |
| MPU             | yes                                                  |
| Datasheet       | [Datasheet](https://www.silabs.com/documents/public/data-sheets/efm32tg11-datasheet.pdf)                                 |
| Manual          | [Manual](https://www.silabs.com/documents/public/reference-manuals/efm32tg11-rm.pdf)                                     |
| Board Manual    | [Board Manual](https://www.silabs.com/documents/public/user-guides/ug303-stk3301.pdf)                                    |
| Board Schematic | [Board Schematic](https://www.silabs.com/documents/public/schematic-files/BRD2102A-A04-schematic.pdf)                    |

### Pinout
This is the pinout of the expansion header on the right side of the board. PIN 1 is the bottom-left contact when the header faces  you horizontally.

|      | PIN | PIN |      |
|------|-----|-----|------|
| 3V3  | 20  | 19  | RES  |
| 5V   | 18  | 17  | RES  |
| PCD6 | 16  | 15  | PD7  |
| PC15 | 14  | 13  | PC9  |
| PC14 | 12  | 11  | PD5  |
| PC8  | 10  | 9   | PC13 |
| PC12 | 8   | 7   | PD2  |
| PC10 | 6   | 5   | PC1  |
| PC11 | 4   | 3   | PC0  |
| VMCU | 2   | 1   | GND  |

**Note**: not all starter kits by Silicon Labs share the same pinout!

**Note:** some pins are connected to the board controller, when enabled!

### Peripheral mapping
| Peripheral | Number  | Hardware        | Pins                            | Comments                                                  |
|------------|---------|-----------------|---------------------------------|-----------------------------------------------------------|

### User interface
| Peripheral | Mapped to | Hardware | Pin  | Comments   |
|------------|-----------|----------|------|------------|
| Button     | PB0      | PD5  |            |
|            | PB1      | PC9  |            |
| LED        | LED0     | PD2  | Yellow LED |
|            | LED1     | PC2  | Yellow LED |

## Implementation Status
| Device                        | ID                                  | Supported | Comments                                                       |
|-------------------------------|-------------------------------------|-----------|----------------------------------------------------------------|
| MCU                           | EFM32TG11B                          | yes       | Power modes supported                                          |
| Low-level driver              | ADC                                 | yes       |                                                                |
|                               | Flash                               | yes       |                                                                |
|                               | GPIO                                | yes       | Interrupts are shared across pins (see reference manual)       |
|                               | HW Crypto                           | yes       |                                                                |
|                               | I2C                                 | yes       |                                                                |
|                               | PWM                                 | yes       |                                                                |
|                               | RTCC                                | yes       | As RTT or RTC                                                  |
|                               | SPI                                 | partially | Only master mode                                               |
|                               | Timer                               | yes       |                                                                |
|                               | UART                                | yes       | USART is shared with SPI. LEUART baud rate limited (see below) |
|                               | USB                                 | no        |                                                                |



## Board configuration

### Board controller
The starter kit is equipped with a Board Controller. This controller provides a virtual serial port. The board controller is enabled via a GPIO pin.

By default, this pin is enabled. You can disable the board controller module by passing `DISABLE_MODULE=silabs_bc` to the `make` command.

**Note:** to use the virtual serial port, ensure you have the latest board controller firmware installed.

**Note:** the board controller *always* configures the virtual serial port at 115200 baud with 8 bits, no parity and one stop bit. This also means that it expects data from the MCU with the same settings.

### Clock selection
There are several clock sources that are available for the different peripherals. You are advised to read [AN0004](https://www.silabs.com/Support%20Documents/TechnicalDocs/AN0004.pdf) to get familiar with the different clocks.

| Source  | Internal | Speed                            | Comments                           |
|---------|----------|----------------------------------|------------------------------------|
| HFRCO   | Yes      | 19 MHz                           | Enabled during startup, changeable |
| HFXO    | No       | 48 MHz                           |                                    |
| LFRCO   | Yes      | 32.768 kHz                       |                                    |
| LFXO    | No       | 32.768 kHz                       |                                    |
| ULFRCO  | No       | 1.000 kHz                        | Not very reliable as a time source |

The sources can be used to clock following branches:

| Branch | Sources                 | Comments                     |
|--------|-------------------------|------------------------------|
| HF     | HFRCO, HFXO             | Core, peripherals            |
| LFA    | LFRCO, LFXO             | Low-power timers             |
| LFB    | LFRCO, LFXO, CORELEDIV2 | Low-power UART               |
| LFE    | LFRCO, LFXO             | Real-time Clock and Calendar |

CORELEDIV2 is a source that depends on the clock source that powers the core. It is divided by 2 or 4 to not exceed maximum clock frequencies (emlib takes care of this).

The frequencies mentioned in the tables above are specific for this starter kit.

It is important that the clock speeds are known to the code, for proper calculations of speeds and baud rates. If the HFXO or LFXO are different from the speeds above, ensure to pass `EFM32_HFXO_FREQ=freq_in_hz` and `EFM32_LFXO_FREQ=freq_in_hz` to your compiler.

You can override the branch's clock source by adding `CLOCK_LFA=source` to your compiler defines, e.g. `CLOCK_LFA=cmuSelect_LFRCO`.

### Low-power peripherals
The low-power UART is capable of providing an UART peripheral using a low-speed clock. When the LFB clock source is the LFRCO or LFXO, it can still be used in EM2. However, this limits the baud rate to 9600 baud. If a higher baud rate is desired, set the clock source to CORELEDIV2.

If you don't need low-power peripheral support, passing `LOW_POWER_ENABLED=0` to the compiler will disable support in the drivers (currently LEUART). This feature costs approximately 600 bytes (default compilation settings, LEUART only).

**Note:** peripheral mappings in your board definitions will not be affected by this setting. Ensure you do not refer to any low-power peripherals.

### RTC or RTT
RIOT-OS has support for *Real-Time Tickers* and *Real-Time Clocks*.

However, this board MCU family has support for a 32-bit *Real-Time Clock and Calendar*, which can be configured in ticker mode **or** calendar mode. Therefore, only one of both peripherals can be enabled at the same time.

Configured at 1 Hz interval, the RTCC will overflow each 136 years.

### Hardware crypto
This MCU is equipped with a hardware accelerated crypto peripheral that can speed up AES128, AES256, SHA1, SHA256 and several other cryptographic computations.

A peripheral driver interface for RIOT-OS is proposed, but not yet implemented.

### Usage of emlib
This port makes uses of emlib by Silicon Labs to abstract peripheral registers. While some overhead is to be expected, it ensures proper setup of devices, provides chip errata and simplifies development. The exact overhead depends on the application and peripheral usage, but the largest overhead is expected during peripheral setup. A lot of read/write/get/set methods are implemented as inline methods or macros (which have no overhead).

Another advantage of emlib are the included assertions. These assertions ensure that peripherals are used properly. To enable this, pass `DEBUG_EFM` to your compiler.

### Pin locations
The EFM32 platform supports peripherals to be mapped to different pins (predefined locations). The definitions in `periph_conf.h` mostly consist of a location number and the actual pins. The actual pins are required to configure the pins via GPIO driver, while the location is used to map the peripheral to these pins.

In other words, these definitions must match. Refer to the data sheet for more information.

This MCU has extended pin mapping support. Each pin of a peripheral can be connected separately to one of the predefined pins for that peripheral.

## Flashing the device
To flash, [SEGGER JLink](https://www.segger.com/jlink-software.html) is required.

Flashing is supported by RIOT-OS using the command below:

```
make flash
```

To run the GDB debugger, use the command:

```
make debug
```

Or, to connect with your own debugger:

```
make debug-server
```

Some boards have (limited) support for emulation, which can be started with:

```
make emulate
```

## Supported Toolchains
For using the Silicon Labs SLSTK3301A starter kit we strongly recommend the usage of the [GNU Tools for ARM Embedded Processors](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm) toolchain.

## License information
* Silicon Labs' emlib: zlib-style license (permits distribution of source).
* Images: taken from starter kit user manual.
