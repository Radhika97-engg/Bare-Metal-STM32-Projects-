# Project 4: Pulse Width Measurement using STM32 TIM2 Input Capture

This project measures the pulse width of a signal using TIM2's input capture feature.  
The result is indicated by blinking the onboard LED (PC13) once per pulse measurement.

## Features

- Configures PA0 as input (TIM2_CH1)
- Captures rising and falling edges
- Calculates pulse width in microseconds
- Blinks LED on each successful pulse capture
- Timer3 used for accurate delay

## Demo

![Pulse Width Capture Demo](https://github.com/Radhika97-engg/Bare-Metal-STM32-Projects-/raw/main/Bare_Metal_Projects/Project4_Timer_Input_Capture_Pulse_Width/LED_pulse_capture_demo.gif)

## How to Run
1. Flash the code via STM32CubeIDE or OpenOCD
2. Input PWM signal on PA0 - from signal generator or another MCU
3. Observe onboard LED blinking after each pulse capture

## Concepts Used

- GPIO Alternate Function
- TIM2 Input Capture
- Timer delay using TIM3
- Bitwise register control

## Tools Used

- STM32F446RE (Nucleo)
- STM32CubeIDE
- Bare-metal C
- GitHub for version control

## Learning Reflection

This project helped me understand how input capture works, how to extract timing info from CCR registers, and how timers can work together to control delays and GPIO.
