## UTP wiring for Edt-Trak

The connection between the controller unit of the Edt-Trak and the gametrak itself is a simple UTP cable, which has 4 pairs of cable.

Only the Orange and Green wires are used in normal UTP cables, while Blue and Brown can also be used for PoE. 

UTP pin diagram, with UTP color, Trak color, Analog pin, axis

````
1: Green /		- red left - A0 - Z
2: Green		- red right - A3 - Z
3: Orange /		- orange left - A1 - Y
4: blue 		- 5v
5: blue /		- yellow left - A2 - X
6: Orange		- orange right - A4 - Y
7: brown /		- yellow right - A5 - X
8: brown 		- 0v
````

When you have soldered the Edt-Trak wires you can test for shorts with a multimeter:

Blue -> Brown should be a lot of Ohm
Blue -> rest should be responsive to the XYZ values of the sensors