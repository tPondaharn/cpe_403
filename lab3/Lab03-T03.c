#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//	Unsigned integer variable used to cycle through LEDs
uint8_t ui8PinData=13;

int main(void)
{
	//	Configure clk: XTAL 16MHz drives 400MHz PLL. Default /2 divider and /16 divider = 12.5MHz
	SysCtlClockSet(SYSCTL_SYSDIV_16|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	//	Enable peripheral - general input/output of F port.
	//	Configure port F pins as output
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	while(1)
	{
		//	Writes corresponding bit values of ui8PinData variable to port F
		//	Delay
		//	Writes 0 to port F, turning LED off
		//	Delay
		//	LEDs are Red at PF1, Blue at PF2, Green at PF3; ui8PinData must cycle through 110X,101X,011X
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);
		SysCtlDelay(2000000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
		SysCtlDelay(2000000);
		if(ui8PinData<=7) {ui8PinData=13;} else {ui8PinData=ui8PinData-3;}
	}
}
