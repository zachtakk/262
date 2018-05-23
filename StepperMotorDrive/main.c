#include <DS89C4xx.h>

void delay_cw(void)
{
	//create 2ms delay
	TH0 = 0xEE;
	TL0 = 0x82;
	TR0 = 1;
	
	while (TF0 == 0); // wait here until TFO == 1 
	
	TR0 = 0; // stop timer 
	TF0 = 0; //clear flag
	
} //delay_cw

void delay_ccw(void)
{
		//create 2ms delay
	TH0 = 0xB9;
	TL0 = 0xB6;
	TR0 = 1;
	
	while (TF0 == 0); // wait here until TFO == 1 
	
	TR0 = 0; // stop timer 
	TF0 = 0; //clear flag
	
} //delay_ccw

void main(void)
{
	TMOD = 0x01;
	while(1)
	{
        int i; 
        int j; 
        //turning cw
        // Stepping 16 times for 180 degrees
        for (j = 0 ; j <16; j=j+1)
        {
            
            for (i = 0 ; i <16 ; i = i+1)
            {
                P1 = 0x66;
                delay_cw();
                P1 = 0x33;
                delay_cw();
                P1 = 0x99;
                delay_cw();
                P1 = 0xCC;
                delay_cw();
            }		
					}
				for (j = 0 ; j < 8 ; j=j+1)
        {
            
            for (i = 0 ; i <16 ; i = i+1)
            {
                P1 = 0x66;
                delay_ccw();
                P1 = 0xCC;
                delay_ccw();
                P1 = 0x99;
                delay_ccw();
                P1 = 0x33;
                delay_ccw();
            }
        }
	}//end of while{1}
}//end of main