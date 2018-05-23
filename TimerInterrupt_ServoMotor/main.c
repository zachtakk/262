/// Zachery Takkesh
// CECS 262
// Lab 4, Servo

#include <DS89C4XX.h> 

// global variable of P0 (switches) so delay function can 
// calculate delay time depending on user switches input
unsigned char p0_variable;

// Delay function that calculates the delay time to turn 
// the servo from -45 to 45 degrees. 1 ms (0x00 on switches)
// will generate a -45 turn, 2 ms (0xFF on switches) will 
// turn 45 degrees, and everything in between. 
void delay() 
{
    unsigned char sw = p0_variable;
    unsigned int delta  = sw*11;
    unsigned int iterations = delta + 2777; 

    unsigned int i;

    for ( i = 0; i < iterations ; i++);

} // end of delay function 

// Timer delay to generate a 10 ms clock period
void TimerISR (void) interrupt 1 
{
    TR0 = 0; // stop timer 

    // Reset timer 
    TMOD = 0X01; // timer mode is 16-bit timer
	TH0 = 0xDB;  // timer high, MSB 8-bit
    TL0 = 0xFF; // timer low, LSB 8-bit 
    TR0 = 1;    // start timer 

    // Setting port 0 pin 1
    P1 |= 0x01;

    delay();

    // Clearing port 0 pin 1
    P1 &= 0xFE;

} // end of timer interrupt

// Main function 
void main(void)
{
    // Initiation of interrupt enable 
    // 0x82 will enable EA and external hardware 1
    IE = 0x82;

    //Initiation of timer variables 
    TMOD = 0X01;
	TH0 = 0xDB; 
    TL0 = 0xFF;
    TR0 = 1;

    P0 = 0xFF;

    // Input Port 0 from switches and assign it to global variable 
    while(1) {
        p0_variable = P0;
    } 

} // end of main