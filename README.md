# EK-TM4C123GXL
Tiva C Series TM4C123GXL LaunchPad Projects. Includes: LCD library for HD44780U LCD Display (16x2 implementation).

### Successful initialization:

![DisplayHI](https://user-images.githubusercontent.com/112997769/226772720-25589d87-6fe0-4b9a-bb4f-caab1d4b0e87.jpg)

### Helpful resources for getting started:
- [SparkFun Basic LCD tutorial](tutorials/basic-character-lcd-hookup-guide)

- [Datasheet walkthrough and programming by hand](https://www.youtube.com/watch?v=cXpeTxC3_A4)

### Troubleshooting LCD: Ensure contrast is set correctly.

Contrast that is set too low will show no characters and contrast that is set too high will show white boxes and no characters:

![MinContrast](https://user-images.githubusercontent.com/112997769/226772747-b44620a9-7ff0-4b7f-82bb-c431faaeeb8d.jpg)
![MaxContrast](https://user-images.githubusercontent.com/112997769/226772763-a77e803d-2cad-4b5f-ac11-9da99e3bce69.jpg)


### Power Supply Warning: 

Do not try to power both the TI TivaC LaunchPad and 16x2 display from the same generic breadboard power supply. In this case, the [JBtek Breadboard Power Supply Module](https://www.amazon.com/gp/product/B010UJFVTU/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) burnt due to its 700mA max rating being exceeded.

![BurntPowerSupply](https://user-images.githubusercontent.com/112997769/226772191-e8d72b9b-32ef-409f-876e-f422f6d2a056.jpg)
