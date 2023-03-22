# EK-TM4C123GXL
Tiva C Series TM4C123GXL LaunchPad. Includes: LCD library for HD44780U LCD Display (16x2 implementation).
Successful initialization:
![DisplayHI](https://user-images.githubusercontent.com/112997769/226771616-17a75fc4-abc0-48fc-b697-a91d77312c48.jpg)

Troubleshooting LCD: Ensure contrast is set correctly.
Contrast that is set too low will show no characters:
![MinContrast](https://user-images.githubusercontent.com/112997769/226771527-af93c151-b054-41f6-a856-26343b1d6983.jpg)

Contrast that is set too high will show white boxes and no characters:
![MaxContrast](https://user-images.githubusercontent.com/112997769/226771570-b4e7852e-1c29-485b-b683-b13f9827a3dc.jpg)

Power Supply Warning: Do not try to power both the TI TivaC LaunchPad and 16x2 display from the same generic breadboard power supply. In this case, the JBtek Breadboard Power Supply Module burnt due to its 700mA max rating being exceeded.
![BurntPowerSupply](https://user-images.githubusercontent.com/112997769/226771836-280657cf-b915-472f-a81d-87ee993c5ac5.jpg)
