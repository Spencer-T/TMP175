# TMP175
Interface with Beaglebone to TMP175
Using Beaglebone I2C-2, this code readbacks the value in the Temp register.
Using i2cdetect, find out whats I2C adapter on the Sitara:
root@beaglebone:~# i2cdetect -l
i2c-0   i2c             OMAP I2C adapter                        I2C adapter
i2c-2   i2c             OMAP I2C adapter                        I2C adapter
root@beaglebone:~# i2cdetect -y -r 2     
0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- 37 -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- UU UU UU UU -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
A bus adapter is detected on address 0x37, and this is the TMP175, whereby A0~A2 is left floating.
