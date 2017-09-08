TMP175
Interface with Beaglebone to TMP175
Using Beaglebone I2C-2, this code readbacks the value in the Temp register.
Using i2cdetect, find out whats I2C adapter on the Sitara:
root@beaglebone:~# i2cdetect -l
i2c-0   i2c             OMAP I2C adapter I2C adapter
i2c-2   i2c             OMAP I2C adapter I2C adapter
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
The 8 bit Pointer register is used to address a given data register
The Pointer register uses two LSBs to identify which of the data registers must respond to a read or write commands
Pointer Address:
P1  P0  Type  Register
0   0   R     Temp register
0   1   R/W   Configuration register
1   0   R/W   Tlow register
1   1   R/W   Thigh register
Assuming we're not not using shutdown SD=0, thermostat mode in comparator mode TM=0, polarity bit is POL=0, Fault queue is F0/F1=00 , 
converter resolution is 12 bits R1/R0= 11 , one-shot is 0,
Byte to be written = 0x60
# i2cset -y 2 0x37 0x01 0x60
# i2cset -y 2 0x37 0x00
# i2cget -y 2 0x37 0x00 w
0xf01c
A value of hex 1CF is returned. This correspond to a decimal value of 463. Dividing by 16, we get 28.93 degree C

