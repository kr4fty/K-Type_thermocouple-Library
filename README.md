# K-Type_thermocouple-Library

Library to handle a type K thermocouple.

## Hardware

In this example an operational amplifier winning 270 to thermocouple work between 0 and 420°C is used. Quietly you can change the gain of the operational amplifier to work in a wider range or smaller.

As advantages we can say that when working with this AO, LM358, we only need a simple source. It is also very economical in comparison to the dedicated circuits dedicated to this purpose, as is the case of the MAX31855.

As a disadvantage we can say that the resistances have to be smaller tolerance and more stable source among other things. It also has problems detecting low temperatures ( <60ºC ).

![alt tag](https://github.com/kr4fty/K-Type_thermocouple-Library/blob/master/Hardware/circuit.png)


### Example

**Temp_to_serialPort**

Reads data from analog port A2 and sends them through the serial port, then the script receives them and graphs in a window

To be able to use this script should have the libraries **Python, matplotlib, pySerial,** and backend **TK**

Note that you must configure the serial port used within the script:

For example in Linux:

`ser=serial.Serial("/dev/ttyUSB0", 9600, timeout=1)`

Running the script:

`$> python temp.py`

![alt tag](https://github.com/kr4fty/K-Type_thermocouple-Library/blob/master/examples/Temp_to_serialPort/plot.gif)
