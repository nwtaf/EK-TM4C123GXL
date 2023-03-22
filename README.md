# EK-TM4C123GXL
Tiva C Series TM4C123GXL LaunchPad. Includes: LCD library for HD44780U LCD Display (16x2 implementation).

Successful initialization:

![DisplayHI](https://user-images.githubusercontent.com/112997769/226772129-79a9f26b-f8bc-448c-b1a4-683dd663bb92.jpg)

Troubleshooting LCD: Ensure contrast is set correctly.

Contrast that is set too low will show no characters:

![MinContrast](https://user-images.githubusercontent.com/112997769/226772158-05beb381-325a-400b-8d9a-f5eafc7462d4.jpg)

Contrast that is set too high will show white boxes and no characters:

![MaxContrast](https://user-images.githubusercontent.com/112997769/226772171-5ac3b4c4-4689-44d3-8d84-c61ec75e3225.jpg)


Power Supply Warning: Do not try to power both the TI TivaC LaunchPad and 16x2 display from the same generic breadboard power supply. In this case, the JBtek Breadboard Power Supply Module burnt due to its 700mA max rating being exceeded.

![BurntPowerSupply](https://user-images.githubusercontent.com/112997769/226772191-e8d72b9b-32ef-409f-876e-f422f6d2a056.jpg)
