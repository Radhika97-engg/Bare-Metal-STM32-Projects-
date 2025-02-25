#include "stm32f446xx.h"  // Include STM32F446RE header file

// Define GPIO clock enable bits
#define GPIOAEN    (1U<<0)  // Enable clock for GPIOA
#define GPIOCEN    (1U<<2)  // Enable clock for GPIOC

// Define pin positions
#define PIN5       (1U<<5)   // PA5 for LED
#define PIN13      (1U<<13)  // PC13 for Button

// Define LED and Button pins
#define LED_PIN     PIN5      // Assign PA5 as LED pin
#define BTN_PIN     PIN13     // Assign PC13 as Button pin

int main(void)
{
	/* Enable clock access to GPIOA (LED) and GPIOC (Button) */
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	/* Set PA5 as output pin for LED */
	GPIOA->MODER |= (1U << 10);  // Set bit 10 to configure PA5 as output
	GPIOA->MODER &= ~(1U << 11); // Clear bit 11 to complete the output mode configuration

	/* Set PC13 as input pin for Button */
	GPIOC->MODER &= ~(1U << 26); // Clear bit 26 to configure PC13 as input
	GPIOC->MODER &= ~(1U << 27); // Clear bit 27 to complete the input mode configuration

   while(1)
   {
	   /* Check if Button is pressed (Active LOW) */
	   if(GPIOC->IDR & BTN_PIN)  // If PC13 is HIGH (not pressed)
	   {
		   /* Turn ON LED */
	       GPIOA->BSRR = LED_PIN;  // Set PA5 (Turn ON LED)
	   }
	   else
	   {
		   /* Turn OFF LED */
	       GPIOA->BSRR = (1U << 21);  // Reset PA5 (Turn OFF LED)
	   }
   }
}
