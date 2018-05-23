#include  <at89c51xd2.h>

void delay(void) // see if p0.2 is 1 or 0
{
	
	unsigned char speed;
	unsigned int x;
	speed = (P0&0x04);
	
	if(speed) //sw2 = 1
	{
		for(x = 0; x <35000; x++); //short delay
	}
	else //sw = 0
	{
		for(x = 0; x <65000;x++); //long delay
		
	}
	
}
void main(void){
	
	int i;
	unsigned char result;
	P0 = 0xFF; //Init P0 to input for switches
	// Initialization
	while(1)
	{
		result = (P0&0x02); //to see if p0.1 is 1 or 0
		if (result){ //sw1 = 1
			i = 0;
			P1 = 0x05;
			while (i<8)
			{
				delay();
				P1 = P1 >> 1; //shifting right 1bit
				P1 = P1 | 0x80;
				i++;
			}
		} //end if
		else{ //sw1 = 0
			i = 0;
			P1 = 0xAF;
			while (i<8)
			{
				delay();
				P1 = P1>>1; //shifting right 1bit
				P1 = P1 | 0x80;
				i++;
			}
		} //end else
	} //end of while loop
} //end main