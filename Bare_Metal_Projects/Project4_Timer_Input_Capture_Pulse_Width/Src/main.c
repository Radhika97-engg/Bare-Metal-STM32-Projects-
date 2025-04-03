#include "stm32f446xx.h"

/*Clock Enable Macros*/
#define GPIOAEN     (1U<<0)
#define GPIOCEN     (1U<<2)
#define TIM2EN      (1U<<0)
#define TIM3EN      (1U<<1)

/*Timer & GPIO Config */
#define SYS_FREQ            16000000
#define TIMER_TICK_HZ       1000000 // 1 µs per tick
#define PRESCALAR_VALUE     ((SYS_FREQ / TIMER_TICK_HZ) - 1)
#define MAX_COUNTER_VALUE   0xFFFFFFFF

/*TIM2 CC1 Input Capture Settings*/
#define CC1E        (1U<<0)
#define CC1S        (1U<<0)
#define CC1P        (1U<<1)
#define CC1NP       (1U<<3)
#define CEN         (1U<<0)

/*LED GPIO*/
#define LED_PIN         (1U << 13)         // PC13
#define MODER13_MASK    (3U << 26)         // Bits 27:26

/*Global Variables*/
static uint32_t first_edge = 0;
static uint32_t second_edge = 0;
static uint32_t pulse_width = 0;
static uint8_t edge_counter = 0;

/*TIM3 Delay Function*/
void timer3_delay_ms(int timer_delay)
{
    RCC->APB1ENR |= TIM3EN;
    TIM3->PSC = 16000 - 1;          // 1ms tick
    TIM3->ARR = timer_delay;       // Delay duration
    TIM3->CNT = 0;
    TIM3->SR = 0;
    TIM3->CR1 |= CEN;
    while (!(TIM3->SR & (1U << 0)));   // Wait for UIF
    TIM3->CR1 &= ~CEN;
    TIM3->SR = 0;
}

/*Capture Logic*/
void capture_pulse_width(void)
{
    if (edge_counter == 0)
    {
        first_edge = TIM2->CCR1;
        edge_counter = 1;
    }
    else if (edge_counter == 1)
    {
        second_edge = TIM2->CCR1;

        if (second_edge >= first_edge)
            pulse_width = second_edge - first_edge;
        else
            pulse_width = (MAX_COUNTER_VALUE - first_edge) + second_edge + 1;

        edge_counter = 0;

        // LED Blink (active low)
        GPIOC->ODR &= ~LED_PIN;        // LED ON
        timer3_delay_ms(100);          // Delay 100ms
        GPIOC->ODR |= LED_PIN;         // LED OFF
    }
}

int main(void)
{
    /* Enable Clocks */
    RCC->AHB1ENR |= GPIOAEN | GPIOCEN;
    RCC->APB1ENR |= TIM2EN;

    /* PA0 → Alternate Function TIM2_CH1 */
    GPIOA->MODER &= ~(3U << 0);           // Clear mode
    GPIOA->MODER |=  (2U << 0);           // AF mode
    GPIOA->AFR[0] &= ~(0xF << 0);         // Clear AFRL
    GPIOA->AFR[0] |=  (0x1 << 0);         // AF1 (TIM2)

    /* PC13 → Output for LED */
    GPIOC->MODER &= ~MODER13_MASK;
    GPIOC->MODER |=  (1U << 26);          // Output mode

    /* TIM2 Configuration */
    TIM2->PSC = PRESCALAR_VALUE;
    TIM2->ARR = MAX_COUNTER_VALUE;
    TIM2->CCER &= ~CC1E;                  // Disable Channel 1
    TIM2->CCMR1 &= ~(3U << 0);            // Clear CC1S
    TIM2->CCMR1 |= (1U << 0);             // CC1S = 01 → TI1
    TIM2->CCER |= (CC1P | CC1NP);         // Both edges
    TIM2->CCER |= CC1E;                   // Enable capture
    TIM2->CR1 |= CEN;                     // Start TIM2


    while (1)
    {
        capture_pulse_width();
    }
}
