# GY953
A library for the Tilt compensated compass GY-953 in SPI mode.

The GY-953 it's a tiny Tilt Compensated compass module based on a sensor and a onboard 32 CPU from ST. The board works in serial or SPI mode.
This library handle only the SPI version.
The reason I wrote this is simple, cannot find any documentation and the module seems be copied 1:1 from a solution appears time ago on the net, maybe the chinese who copied don't want to expose himself...<br><br>

First, since I don't have any documentation, this is just an experiment so please do not ask me!<br>
The purpose of the library is expose the data I want in simple way and have the full SPI transaction compatibility, since the chip uses SPI mode 3 it will not play nice if other SPI devices are in the same bus.<br>
The MAX SPI speed it's 400Khz and need SPI MODE 3! This library uses SPI Transactions to enhanche compatibility with other SPI devices but be sure that every device has an SPI Transaction compatible library!<br>



Registry description (Preliminary):<br>

<b>configuration register A (0x01) R/W</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td>0</td><td>Magnetometer</td><td>Gyro</td><td>Acc</td><td>1</td><td>f3</td><td>f2</td><td>f1</td>
</tr>
</table>

<table>
<tr>
<td><b>Bit</b></td><td><b>Description</b></td>
</tr>
<tr>
<td>7:</td><td>This bit must be 0</td>
</tr>
<tr>
<td>6:</td><td>Magnetometer, Default = 1, (0:OFF,1:ON)</td>
</tr>
<tr>
<td>5:</td><td>Gyro, , Default = 1, (0:OFF,1:ON)</td>
</tr>
<tr>
<td>4:</td><td>Acc, , Default = 1, (0:OFF,1:ON)</td>
</tr>
<tr>
<td>3:</td><td>This bit must be 1</td>
</tr>
<tr>
<td>2..0:</td><td>Set the data output rate: 3(011): 50hz, 4(100): 100hz, 5a(101): 200hz</td>
</tr>
</table>

<b>configuration register B (0x02) R/W</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td>Factory</td><td>0</td><td>0</td><td>1</td><td>Magn self-cal</td><td>self-test</td><td>0</td><td>1</td>
</tr>
</table>

<table>
<tr>
<td><b>Bit</b></td><td><b>Description</b></td>
</tr>
<tr>
<td>7:</td><td>1:restore factory settings</td>
</tr>
<tr>
<td>6:</td><td>Must be 0</td>
</tr>
<tr>
<td>5:</td><td>Must be 0</td>
</tr>
<tr>
<td>4:</td><td>Must be 1</td>
</tr>
<tr>
<td>3:</td><td>1:Magnetometer self-cal, automatically save the data</td>
</tr>
<tr>
<td>2:</td><td>1:self-test and calibration of accelerometers and gyroscopes, automatically save data</td>
</tr>
<tr>
<td>1:</td><td>Must be 0</td>
</tr>
<tr>
<td>0:</td><td>Must be 1</td>
</tr>
</table>


Register <b>ACC_X_H (0x03)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">X-axis acceleration HSB</td>
</tr>
</table>

Register <b>ACC_X_L (0x04)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">X-axis acceleration LSB</td>
</tr>
</table>

Register <b>ACC_Y_H (0x05)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Y-axis acceleration HSB</td>
</tr>
</table>

Register <b>ACC_Y_L (0x06)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Y-axis acceleration LSB</td>
</tr>
</table>

Register <b>ACC_Z_H (0x07)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Z-axis acceleration HSB</td>
</tr>
</table>

Register <b>ACC_Z_L (0x08)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Z-axis acceleration LSB</td>
</tr>
</table>

Register <b>GYRO_X_H (0x09)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">X-axis gyro HSB</td>
</tr>
</table>

Register <b>GYRO_X_L (0x0A)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">X-axis gyro LSB</td>
</tr>
</table>

Register <b>GYRO_Y_H (0x0B)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Y axis gyro HSB</td>
</tr>
</table>

Register <b>GYRO_Y_L (0x0C)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Y axis gyro LSB</td>
</tr>
</table>

Register <b>GYRO_Z_H (0x0D)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Z axis gyro HSB</td>
</tr>
</table>

Register <b>GYRO_Z_L (0x0E)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Z axis gyro LSB</td>
</tr>
</table>

Register <b>COMPASS_X_H (0x0F)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">X axis compass HSB</td>
</tr>
</table>

Register <b>COMPASS_X_L (0x10)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">X axis compass LSB</td>
</tr>
</table>


Register <b>COMPASS_Y_H (0x11)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Y axis compass HSB</td>
</tr>
</table>

Register <b>COMPASS_Y_L (0x12)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Y axis compass LSB</td>
</tr>
</table>

Register <b>COMPASS_Z_H (0x13)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Z axis compass HSB</td>
</tr>
</table>

Register <b>COMPASS_Z_L (0x14)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Z axis compass LSB</td>
</tr>
</table>

Register <b>ROLL_H (0x15)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Roll angle HSB</td>
</tr>
</table>

Register <b>ROLL_L (0x16)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Roll angle LSB</td>
</tr>
</table>

Register <b>PITCH_H (0x17)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Pitch angle HSB</td>
</tr>
</table>

Register <b>PITCH_L (0x18)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Pitch angle LSB</td>
</tr>
</table>


Register <b>YAW_H (0x19)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Yaw angle HSB</td>
</tr>
</table>

Register <b>YAW_L (0x1A)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Yaw angle LSB</td>
</tr>
</table>

Register <b>Q0_H (0x1B)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q0 HSB</td>
</tr>
</table>

Register <b>Q0_L (0x1C)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q0 LSB</td>
</tr>
</table>

Register <b>Q1_H (0x1D)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q1 HSB</td>
</tr>
</table>

Register <b>Q1_L (0x1E)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q1 LSB</td>
</tr>
</table>

Register <b>Q2_H (0x1F)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q2 HSB</td>
</tr>
</table>

Register <b>Q2_L (0x20)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q2 LSB</td>
</tr>
</table>

Register <b>Q3_H (0x21)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q3 HSB</td>
</tr>
</table>

Register <b>Q3_L (0x22)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Quaternion Q3 LSB</td>
</tr>
</table>


<b>Status Register D (0x23)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="2">0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td>
</tr>
</table>

<table>
<tr>
<td><b>Bit</b></td><td><b>Description</b></td>
</tr>
<tr>
<td>7..6:</td><td>Reserved</td>
</tr>
<tr>
<td>5..4:</td><td>Acceleration Range 0:+-2g, 1:+-4g, 2:+-8g, 3:+-16g</td>
</tr>
<tr>
<td>3..2:</td><td>Gyro Range 0:+250dps, 1:+500dps, 2:+1000dps, 3:+2000dps</td>
</tr>
<tr>
<td>1..0:</td><td>Magnetometer range 0:14bit(0.6ut, 4915), 1:16bit(0.15ut, 4915)</td>
</tr>
</table>


<b>Status Register C (0x24)</b><br>
<table>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td>new</td><td>0</td><td colspan="2">Accelleration</td><td colspan="2">Gyro</td><td colspan="2">Magnetometer</td>
</tr>
</table>

<table>
<tr>
<td><b>Bit</b></td><td><b>Description</b></td>
</tr>
<tr>
<td>7:</td><td>Data update automatically cleared after reading</td>
</tr>
<tr>
<td>6:</td><td>Reserved</td>
</tr>
<tr>
<td>5..4:</td><td>Get accelerometer calibration accuracy, 11: highest, lowest 00</td>
</tr>
<tr>
<td>3..2:</td><td>Get gyro meter calibration accuracy, 11: highest, lowest 00</td>
</tr>
<tr>
<td>1..0:</td><td>Get magnetometer calibration accuracy, 11: highest, lowest 00</td>
</tr>
</table>


Register <b>ACC_SUM (0x25)</b><br>
<table>
<tr>
<td colspan="8">8bit: Accelerometer six data registers and data accumulation (0x03 ~ 0x08)</td>
</tr>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">ACC_X_H + ACC_X_L +. . . ACC_Z_L</td>
</tr>
</table>

Register <b>GYRO_SUM (0x26)</b><br>
<table>
<tr>
<td colspan="8">8bit: gyroscope 6 data register data accumulation and (0x09 ~ 0x0E)</td>
</tr>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">GYRO_X_H + GYRO_X_L + . . . GYRO_Z_L</td>
</tr>
</table>

Register <b>COMPASS_SUM (0x27)</b><br>
<table>
<tr>
<td colspan="8">8bit: 6 magnetometer data accumulation and data register (0x0F ~ 0x14)</td>
</tr>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">COMPASS_X_H + COMPASS_X_L + . . . COMPASS_Z_L</td>
</tr>
</table>

Register <b>RPY_SUM (0x28)</b><br>
<table>
<tr>
<td colspan="8">8bit: Euler angles 6 data accumulation and data registers (0x15 ~ 0x1A)</td>
</tr>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">ROLL_H + ROLL_L + . . . YAW_L</td>
</tr>
</table>

Register <b>Q_SUM (0x29)</b><br>
<table>
<tr>
<td colspan="8">8bit: quaternion eight data registers and data accumulation (0x1B ~ 0x22)</td>
</tr>
<tr>
<td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td>
</tr>
<tr>
<td colspan="8">Q0_H + Q0_L + . . . Q3_L</td>
</tr>
</table>

<br>
<b>Note:</b> The accuracy of the magnetic field, the magnetic field can be used as a calibration completion flag.<br>

