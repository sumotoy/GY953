# GY953
A library for the Tilt compensated compass GY-953

The GY-953 it's a tiny Tilt Compensated compass module based on a sensor and a onboard 32 CPU from ST. The board works in serial or SPI mode.
This library handle only the SPI version.
The reason I wrote this is simple, cannot find any documentation and the module seems be copied 1:1 from a solution appears time ago on the net, maybe the chinese who copied don't want to expose himself...<br><br>

First, since I don't have any documentation, this is just an experiment so please do not ask me!<br>
The purpose of the library is expose the data I want in simple way and have the full SPI transaction compatibility, since the chip uses SPI mode 3 it will not play nice if other SPI devices are in the same bus.



Preliminary:<br>

<b>configuration register A (0x01) R/W</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td>0</td><td>magnetic field</td><td>Gyro</td><td>Keke</td><td>1</td><td>f3</td><td>f2</td><td>f1</td>
</tr>
</table>

<table>
<tr>
<td>Bit</td><td>Description</td>
</tr>
<tr>
<td>7:</td><td>This bit must be 0</td>
</tr>
<tr>
<td>6:</td><td>Default bit6 = 1, when bit6 = 0 is off magnetometer sensor 1 is ON</td>
</tr>
<tr>
<td>5:</td><td>Default bit5 = 1, when the bit5 = 0 is off gyro sensor 1 is ON</td>
</tr>
<tr>
<td>4:</td><td>Default bit4 = 1, when bit4 = 0 plus the sensor is off, 1 is ON</td>
</tr>
<tr>
<td>3:</td><td>This bit must be 1</td>
</tr>
<tr>
<td>2..0:</td><td>Set the data output rate: 3(011): 50hz, 4(100): 100hz, 5a(101): 200hz</td>
</tr>
</table>
