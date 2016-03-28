# GY953
A library for the Tilt compensated compass GY-953

The GY-953 it's a tiny Tilt Compensated compass module based on a sensor and a onboard 32 CPU from ST. The board works in serial or SPI mode.
This library handle only the SPI version.
The reason I wrote this is simple, cannot find any documentation and the module seems be copied 1:1 from a solution appears time ago on the net, maybe the chinese who copied don't want to expose himself...<br><br>

First, since I don't have any documentation, this is just an experiment so please do not ask me!<br>
The purpose of the library is expose the data I want in simple way and have the full SPI transaction compatibility, since the chip uses SPI mode 3 it will not play nice if other SPI devices are in the same bus.



Preliminary:<br>

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Content Cell  | Content Cell  | ------------- | ------------- | ------------- | ------------- | ------------- |
| Content Cell  | Content Cell  | ------------- | ------------- | ------------- | ------------- | ------------- |
