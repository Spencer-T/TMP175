#include "beagle_gpio.h"
#include "beagle_hd44780.h"
#include <stdio.h>
#include <math.h>
#include <string.h> 
#include <stdlib.h> 
#include "i2c-dev.h" 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <arm_neon.h>

/*
Connect a HD44780 compatible screen to the beaglebone using the 
follwing connections:
P8_12 ==> DB7
P8_14 ==> DB6
P8_16 ==> DB5
P8_18 ==> DB4 
P8_8  ==> RS
P8_10  ==> E

TMP175 is connected to Beaglebone I2C-2 bus.
TMP175 A0-A2 is floating, giving the address of 0x37
*/ 
		

int main(int argc, char **argv)
{
	
	int file;
	char *filename = "/dev/i2c-2";
	if ((file=open(filename, O_RDWR)) < 0)
		exit(1);
	int addr=0x37;		//device address is 0x37
	if(ioctl(file,I2C_SLAVE,addr) < 0)
		exit(1);
	unsigned char buf[10] = {0};
        if(write(file, buf,1) != 1)
            exit(1);
        int r = read(file,buf,2);
        unsigned char tempH = buf[0];
        unsigned char tempL = buf[1];
//***	Shift the tempH byte by 8 bits and combine with tempL
	unsigned int temp;
        temp=(tempH<<8) + tempL;
//***	Shift the 2 bytes by four bits as the actual data is 12 bits resolution
	temp=temp>>4;

//***   convert char to integer so that it can be divide
	char temp_s[4];
	sprintf(temp_s, "%d", temp);	
	
//**	change to float so that the final value has floating number 
//***	after divide

	float temp_i = atoi(temp_s);	

	float temp_final;
	temp_final = temp_i/16;	
	char str_temp[16];
	sprintf(str_temp, "%f", temp_final);

	int count=0;
		
	//specifies the pins that will be used for LCD

	int selectedPins[]={P8_12,P8_14,P8_16,P8_18,P8_8,P8_10};


	struct gpioID enabled_gpio[6];
	struct gpioID LED1;
//***	assign P9_23 as output pin;

	pinMode(&LED1,P9_23,"out");
//***	turn on LED
	digitalWrite(LED1,1);

	
	initialize_Screen(enabled_gpio,selectedPins);
	
	// Turn on P9_23, look at selectedPins[]arrry. P9_23 at position 6
	// need to set bits 6 on the variable data_to_write. In base 2,
	//setting bit 6 looks like:
	// 0100 0000, this is equivalent to 40, in base 10
	
//***	clear screen
	clear_Screen(enabled_gpio);
	
//***	types "yo!" to the screen
	stringToScreen("yo!",enabled_gpio);

//***	go to the the second line 
	goto_ScreenLine(1,enabled_gpio);
	
	//stringToScreen(datetime.now().strftime('%b %d %H:%M:%S'));
	
	stringToScreen("execute code..",enabled_gpio);
	sleep(2.0);
	while (count<10)
	{	
	
	
		clear_Screen(enabled_gpio);
//		time_t t=time(NULL);
//       	struct tm *tm=localtime(&t);
//        	char s[64];
//		sleep(1.0);
//		goto_ScreenLine(0,enabled_gpio);
//        	strftime(s, sizeof(s), "%x",tm);

//		sleep(1.0);
//***	turn off LED
		digitalWrite(LED1,0);
		
		
//***	and types "Done!"
//		stringToScreen("Done!",enabled_gpio);
//		goto_ScreenLine(1, enabled_gpio);
//		stringToScreen(s, enabled_gpio);
		
		stringToScreen("Temp in C :\n" , enabled_gpio);
		goto_ScreenLine(1, enabled_gpio);
		
		printf("tempH : %x\n",tempH);
		printf("tempL : %x\n",tempL);
		printf("temp : %x\n",temp);
		printf("temp_s : %s\n",temp_s);
		printf("temp_i : %d\n",temp_i);
		printf("temp_final : %f\n",temp_final);		
//		charToScreen(test1, enabled_gpio);
		stringToScreen(str_temp, enabled_gpio);
//		sleep(1.0);


	//don't forget to terminate the screen... or you may get
		digitalWrite(LED1,1);
//		goto_ScreenLine(1, enabled_gpio);
		sleep(1.0);
//		strftime(s, sizeof(s), "%X",tm);
//		stringToScreen(s, enabled_gpio);
//		clear_Screen(enabled_gpio);
//  		terminate_Screen(enabled_gpio,selectedPins);
		sleep(1.0);
		digitalWrite(LED1,0);
		cleanup(LED1);
		count++;
	}
	terminate_Screen(enabled_gpio,selectedPins);
	return 1;
}

