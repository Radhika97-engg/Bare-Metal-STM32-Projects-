# Bare-Metal LED Toggle (STM32)

This is my first **bare-metal embedded project!** :) 
It toggles an LED connected to **GPIOA Pin 5 (PA5)** on an **STM32** microcontroller.

## 🛠️ How to Compile & Flash
1. Use an **ARM GCC toolchain**: `arm-none-eabi-gcc`
2. Compile:
3. Flash the binary using **OpenOCD** or **ST-Link Utility**.

## 📜 Registers Used
- **RCC_AHB1ENR** → Enables GPIOA clock
- **GPIOA_MODER** → Configures PA5 as output
- **GPIOA_ODR** → Controls PA5 (LED ON/OFF)

## 📌 GitHub Repository:
🔗 [https://github.com/Radhika97-engg/baremetal-led-toggle](https://github.com/Radhika97-engg/baremetal-led-toggle)

🚀 Excited to build more!  

