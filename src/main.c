// LED Connection
// Port: A
// Pin: 5

#include <stdint.h>

#define __IO volatile

// Base Addresses
#define PERIPH_BASE           0x40000000UL
#define AHB1PERIPH_OFFSET     0x00020000UL
#define AHB1PERIPH_BASE       (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET          0x0000U
#define GPIOA_BASE            (AHB1PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET            0x3800UL
#define RCC_BASE              (AHB1PERIPH_BASE + RCC_OFFSET)

// GPIOA and RCC Enable Macros
#define GPIOAEN               (1U << 0)  // Enable GPIOA Clock
#define PIN5                  (1U << 5)  // LED on PA5
#define LED_PIN               PIN5

// GPIO Struct Definition
typedef struct {
    __IO uint32_t MODER;   /* GPIO Mode Register (Offset 0x00) */
    __IO uint32_t RESERVED[4]; /* Skipping OTYPER, OSPEEDR, PUPDR, IDR */
    __IO uint32_t ODR;     /* GPIO Output Data Register (Offset 0x14) */
} GPIO_Typedef;

// RCC Struct Definition
typedef struct {
    __IO uint32_t RESERVED[12]; /* Skipping unnecessary RCC registers */
    __IO uint32_t AHB1ENR;      /* RCC AHB1ENR Register (Offset 0x30) */
} RCC_Typedef;

// Struct Pointers to Memory-Mapped Registers
#define RCC    ((RCC_Typedef*) RCC_BASE)
#define GPIOA  ((GPIO_Typedef*) GPIOA_BASE)

// Simple Delay Function
void delay(void) {
    for (volatile int i = 0; i < 100000; i++);
}

int main(void)
{
    /* 1️. Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* 2️. Set PA5 as output pin */
    GPIOA->MODER |= (1U << 10);  // Set bit 10 to 1 (Output Mode)
    GPIOA->MODER &= ~(1U << 11); // Clear bit 11 to 0 (Output Mode)

    while (1)
    {
        /* 3️.Toggle PA5 (LED ON/OFF) */
        GPIOA->ODR ^= LED_PIN;
        delay();
    }
}

