//Jason Chang 	 015610151
//Zachery Takkesh 015656509
#include <ds89c4xx.h>
#include <math.h>

// Receive function
// This function receives the ASCII code via HyperTerminal
// for any character on keyboard
// returns character to main 
unsigned char receive(void){
	
		while (RI_0 == 0);
		//clear receive interrupt flag
		RI_0 = 0;
		return SBUF0;
}

// Transfer function
// This function takes in a variable from
// main and outputs via HyperTerminal
void transfer(unsigned char send){
	
	SBUF0 = send;
	while(TI_0 == 0);
	// clear transfer interrupt flag
	TI_0 = 0;
	
}

// Main function
void main (void){
	
// Initialize Variables for each bit input
unsigned char op1, op2, op3, operator, op4, op5, op6;

// Variable for left and right hand sign of operation
unsigned char operand1, operand2;

// Variable for each bit place holder
unsigned int  bit_9, bit_8, bit_7, bit_6, bit_5;
unsigned int  bit_4, bit_3, bit_2, bit_1 ;	

// long data type required for power operation
long  result, temp; 

	// Initialize timer mode
	TMOD  = 0x20; // 8-bit auto reload mode
	TH1   = 0xFD; // baud rate for 9600
	SCON0 = 0x50; // 8-bit data, 1 stop bit, 1 start bit
	TR1   = 1;    // start timer 
	
	// Continuous  loop
	while (1)
	{
		
	// Clearing all of the bits for a new  set of an arithmetic operation
	 bit_9    = 0;
	 bit_8    = 0;
	 bit_7    = 0;	
 	 bit_6    = 0;
 	 bit_5    = 0;
	 bit_4    = 0;
   bit_3    = 0;
	 bit_2    = 0;
	 bit_1    = 0;
	 result   = 0; 	
	 temp     = 0;
		
		// 1st bit receive and transfer
		op1 = receive();
		transfer(op1);
		
		// convert from ASCII to number
		op1 = op1 - 48;
	
		// 2nd bit receive and transfer
		op2 = receive();
		transfer(op2);
		
		// convert from ASCII to number
		op2 = op2 - 48;
		
		// 3rd bit receive and transfer
		op3 = receive();
		transfer(op3);
		
		// convert from ASCII to number
		op3 = op3 - 48;

		// combine the first three inputs 
		operand1 =(op1*100)+ (op2*10) + op3;
		
		
		// operator receive and transfer (4th bit)
		operator = receive();
		transfer(operator);
		
		//4th bit receive and transfer
		op4 = receive();
		transfer(op4);
		
		//convert from ASCII to number
		op4 = op4 - 48;
		
		//5th bit receive and transfer
		op5 = receive();
		transfer(op5);
		
		//convert from ASCII to number
		op5 = op5 - 48;
		
		//6th bit receive and transfer
		op6 = receive();
		transfer(op6);
		
		//convert from ASCII to number
		op6 = op6 - 48;

		//combine last three inputs 
		operand2 = (op4*100) + (op5*10) + op6;
		
		
		
	 // Conditional evalution statements
   // for arithmetic operations
	
	 // add operation
	 if(operator == '+')
			result = operand1 + operand2;
	 
	 // subtract operation
	 else if(operator == '-')
			result = operand1 - operand2;
	 
	 // multiply operation
	 else if(operator == '*')
			result = operand1 * operand2;
	 
	 // divide operation
	 else if(operator == '/' )
			result = operand1 / operand2;
	 
	 // power operation 
	 else if(operator == '^')
	 		result =  pow(operand1,operand2);
				
	// default condition
	 else
		 result = 'E';
		
		
	// Set result into temp to get the
	// accurate bit in each number location
	temp = result;

	  // Value at hundred-millionth spot 
		while (temp >= 100000000)
		{
			temp = temp - 100000000; 
			bit_9 = bit_9 + 1; 
		}
		// Value at ten-millionth spot
		while (temp >= 10000000)
		{
			temp = temp  - 10000000; 
			bit_8 = bit_8 + 1; 
		}
		
		// Value at millionth spot
		while (temp >= 1000000)
		{
			temp = temp  - 1000000; 
			bit_7 = bit_7 + 1; 
		}
		
		// Value at hundred-thousandth spot
		while (temp >= 100000)
		{
			temp = temp  - 100000; 
			bit_6 = bit_6 + 1; 
		}
	  
		// Value at ten-thousandth spot
		while (temp >= 10000)
		{
			temp = temp  - 10000; 
			bit_5 = bit_5 + 1; 
		}
		
		// Value at thousandth spot
		while (temp >= 1000)
		{
			temp = temp  - 1000; 
			bit_4 = bit_4 + 1; 
		}
		
		// Value at hundredth spot
		while (temp >= 100)
		{
			temp = temp - 100; 
			bit_3 = bit_3 + 1; 
		}
		
		// Value at tenth spot
		while (temp >= 10)
		{
			temp = temp - 10; 
			bit_2 = bit_2 + 1; 
		}
		// Value at ones spot
		while (temp >= 1)
		{
			temp = temp - 1 ; 
			bit_1 = bit_1 + 1; 
		}
		
	  // Convert each value location back to ASCII
		bit_9  = bit_9 + 48;
		bit_8  = bit_8 + 48;
		bit_7  = bit_7 + 48;
		bit_6  = bit_6 + 48;
		bit_5  = bit_5 + 48;
		bit_4  = bit_4 + 48;
		bit_3  = bit_3 + 48;
		bit_2  = bit_2 + 48;
		bit_1  = bit_1 + 48;
		
	 // for visual purposes
	 // being sent back to terminal
	 // new line
	 transfer('\n');
	 // carriage return
	 transfer('\r');
	 // equal sign
	 transfer(61);
	 // space sign 
	 transfer(32);
	 
	 // transfer each bit back to terminal 
	 // bit_9 being the most significant bit(hundred-millionth)
	 // bit_1 being the least signicant bit(ones)
	 transfer(bit_9);
	 transfer(bit_8);
	 transfer(bit_7);
	 transfer(bit_6);
	 transfer(bit_5);
	 transfer(bit_4);
	 transfer(bit_3);
	 transfer(bit_2);
	 transfer(bit_1);
	 
	 // new line transfer for visual purposes
	 transfer('\n');
	 // carriage return to start at beginning of line
	 transfer('\r');
	 // visual pointer for terminal  
	 transfer('>');
	
	} // end of continous loop
	
} // end of main function