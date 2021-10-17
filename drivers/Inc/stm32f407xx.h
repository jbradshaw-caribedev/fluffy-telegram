/*
 * stm32f407xx.h
 * This file contains various addresses and macros required for
 * proper functionality of the STM32F407XX MCU family.
 *
 *  Created on: Oct 14, 2021
 *      Author: Jeremy Bradshaw
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>
#define _vo		volatile	// Shorthand for Volatile to save tabs

/*
 * Base address of Flash and SRAM Memories
 */

#define FLASH_BASEADDR				0x08000000U
#define SRAM1_BASEADDR				0x20000000U
#define SRAM2_BASEADDR				0x2001C000U 	// SRAM1 is 112Kbytes large so shift the address by that amount
#define ROM							0x1FFF0000		// System Memory location of the MCU
#define SRAM						SRAM1_BASEADDR


/*
 * Base addresses of AHBx and APBx Bus Peripherals
 */

#define PERIPH_BASEADDR				0x40000000U
#define APB1PERIPH_BASEADDR			PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR			0x40010000U
#define AHB1PERIPH_BASEADDR			0x40020000U
#define AHB2PERIPH_BASEADDR			0x50000000U

/*
 * Base address of peripherals which are hanging on AHB1 bus
 * TODO: Complete for all other peripherals
 */

#define GPIOA_BASEADDR				( AHB1PERIPH_BASEADDR + 0x0000 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOB_BASEADDR				( AHB1PERIPH_BASEADDR + 0x0400 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOC_BASEADDR				( AHB1PERIPH_BASEADDR + 0x0800 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOD_BASEADDR				( AHB1PERIPH_BASEADDR + 0x0C00 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOE_BASEADDR				( AHB1PERIPH_BASEADDR + 0x1000 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOF_BASEADDR				( AHB1PERIPH_BASEADDR + 0x1400 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOG_BASEADDR				( AHB1PERIPH_BASEADDR + 0x1800 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOH_BASEADDR				( AHB1PERIPH_BASEADDR + 0x1C00 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */
#define GPIOI_BASEADDR				( AHB1PERIPH_BASEADDR + 0x2000 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */

#define RCC_BASEADDR				( AHB1PERIPH_BASEADDR + 0x3800 ) /* Address is AHB1 Bus plus offset found in MCU Reference Manual */

/*
 * Base address of peripherals which are hanging on APB1 bus
 * TODO: Complete for all other peripherals
 */

#define I2C1_BASEADDR				( APB1PERIPH_BASEADDR + 0x5400 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */
#define I2C2_BASEADDR				( APB1PERIPH_BASEADDR + 0x5800 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */
#define I2C3_BASEADDR				( APB1PERIPH_BASEADDR + 0x5C00 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */

#define SPI2_BASEADDR				( APB1PERIPH_BASEADDR + 0x5400 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */
#define SPI3_BASEADDR				( APB1PERIPH_BASEADDR + 0x5400 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */

#define USART2_BASEADDR				( APB1PERIPH_BASEADDR + 0x4400 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */
#define USART3_BASEADDR				( APB1PERIPH_BASEADDR + 0x4800 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */

#define UART4_BASEADDR				( APB1PERIPH_BASEADDR + 0x4C00 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */
#define UART5_BASEADDR				( APB1PERIPH_BASEADDR + 0x5000 ) /* Address is APB1 Bus plus offset found in MCU Reference Manual */


/*
 * Base address of peripherals which are hanging on APB2 bus
 * TODO: Complete for all other peripherals
 */

#define SPI1_BASEADDR				( APB2PERIPH_BASEADDR + 0x3000 ) /* Address is APB2 Bus plus offset found in MCU Reference Manual */
#define SPI4_BASEADDR				( APB2PERIPH_BASEADDR + 0x3400 ) /* Address is APB2 Bus plus offset found in MCU Reference Manual */
#define USART1_BASEADDR				( APB2PERIPH_BASEADDR + 0x1000 ) /* Address is APB2 Bus plus offset found in MCU Reference Manual */
#define USART6_BASEADDR				( APB2PERIPH_BASEADDR + 0x1400 ) /* Address is APB2 Bus plus offset found in MCU Reference Manual */
#define EXTI_BASEADDR				( APB2PERIPH_BASEADDR + 0x3C00 ) /* Address is APB2 Bus plus offset found in MCU Reference Manual */
#define SYSCFG_BASEADDR				( APB2PERIPH_BASEADDR + 0x3800 ) /* Address is APB2 Bus plus offset found in MCU Reference Manual */


/**************************************************** Peripheral Register Definition Structures ***************************************/

/*
 * These structures are defined for configuration and operation of peripherals attached to a specific MCU
 * This code was developed for the STM32F407 family of MCUs. The address space will be different as will the specific
 * peripherals. Consult with the MCU's reference manual for how to properly address the below code.
 *
 * - Jeremy Bradshaw 10/14/2021
 */

/*
 * This structure is for controlling the RCC (Reset and Clock Control) Registers
 * on the STM32F407 MCU. For a detailed description on what bit position will
 * control and it's appropriate value please review the reference manual
 * starting at section 7.1
 */
typedef struct
{
	_vo	uint32_t	CR;				/* RCC clock control register										Address offset: 0x00		*/
	_vo	uint32_t	PLLCFGR;		/* RCC PLL configuration register									Address offset: 0x04		*/
	_vo	uint32_t	CFGR;			/* RCC clock configuration register									Address offset: 0x08		*/
	_vo	uint32_t	CIR;			/* RCC clock interrupt register										Address offset: 0x0C		*/
	_vo	uint32_t	AHB1RSTR;		/* RCC AHB1 peripheral reset register								Address offset: 0x10		*/
	_vo	uint32_t	AHB2RSTR;		/* RCC AHB2 peripheral reset register								Address offset: 0x14		*/
	_vo	uint32_t	AHB3RSTR;		/* RCC AHB3 peripheral reset register								Address offset: 0x18		*/
	_vo	uint32_t	RESERVED_1;		/* This memory space is reserved do not use it						Address offset: 0x1C		*/
	_vo	uint32_t	APB1RSTR;		/* RCC APB1 peripheral reset register 								Address offset: 0x20		*/
	_vo	uint32_t	APB2RSTR;		/* RCC APB2 peripheral reset register								Address offset: 0x24		*/
	_vo	uint32_t	RESERVED_2;		/* This memory space is reserved do not use it						Address offset: 0x28		*/
	_vo	uint32_t	RESERVED_3;		/* This memory space is reserved do not use it						Address offset: 0x2C		*/
	_vo	uint32_t	AHB1ENR;		/* RCC AHB1 peripheral clock enable register						Address offset: 0x30		*/
	_vo	uint32_t	AHB2ENR;		/* RCC AHB2 peripheral clock enable register						Address offset: 0x34		*/
	_vo	uint32_t	AHB3ENR;		/* RCC AHB3 peripheral clock enable register						Address offset: 0x38		*/
	_vo	uint32_t	RESERVED_4;		/* This memory space is reserved do not use it						Address offset: 0x3C		*/
	_vo	uint32_t	APB1ENR;		/* RCC APB1 peripheral clock enable register 						Address offset: 0x40		*/
	_vo	uint32_t	APB2ENR;		/* RCC APB2 peripheral clock enable register						Address offset: 0x44		*/
	_vo	uint32_t	RESERVED_5;		/* This memory space is reserved do not use it						Address offset: 0x48		*/
	_vo	uint32_t	RESERVED_6;		/* This memory space is reserved do not use it						Address offset: 0x4C		*/
	_vo	uint32_t	AHB1LPENR;		/* RCC AHB1 peripheral clock enable in low power mode register		Address offset: 0x50		*/
	_vo	uint32_t	AHB2LPENR;		/* RCC AHB2 peripheral clock enable in low power mode register		Address offset: 0x54		*/
	_vo	uint32_t	AHB3LPENR;		/* RCC AHB3 peripheral clock enable in low power mode register		Address offset: 0x58		*/
	_vo	uint32_t	RESERVED_7;		/* This memory space is reserved do not use it						Address offset: 0x5C		*/
	_vo	uint32_t	APB1LPENR;		/* RCC AHB3 peripheral clock enable in low power mode register		Address offset: 0x60		*/
	_vo	uint32_t	APB2LPENR;		/* RCC AHB3 peripheral clock enable in low power mode register		Address offset: 0x64		*/
	_vo	uint32_t	RESERVED_8;		/* This memory space is reserved do not use it						Address offset: 0x68		*/
	_vo	uint32_t	RESERVED_9;		/* This memory space is reserved do not use it						Address offset: 0x6C		*/
	_vo	uint32_t	BDCR;			/* RCC Backup domain control register								Address offset: 0x70		*/
	_vo	uint32_t	CSR;			/* RCC clock control & status register								Address offset: 0x74		*/
	_vo	uint32_t	RESERVED_10;	/* This memory space is reserved do not use it						Address offset: 0x74		*/
	_vo	uint32_t	RESERVED_11;	/* This memory space is reserved do not use it						Address offset: 0x7C		*/
	_vo	uint32_t	SSCGR;			/* RCC spread spectrum clock generation register					Address offset: 0x80		*/
	_vo	uint32_t	PLLI2SCFGR;		/* RCC PLLI2S configuration register								Address offset: 0x84		*/

}RCC_RegDef_t;

/*
 * This structure is for controlling GPIO Port Registers on the STM32F407 MCU
 * For a detailed description of each member and what each bit position will control
 * please review the reference manual starting at section 8.4
 */
typedef struct
{
	_vo	uint32_t 	MODER;			/* GPIO port mode register											Address offset: 0x00		*/
	_vo	uint32_t	OTYPER;			/* GPIO port output type register									Address offset: 0x04		*/
	_vo	uint32_t	OSPEEDR;		/* GPIO port output speed register									Address offset: 0x08		*/
	_vo	uint32_t	PUPDR;			/* GPIO port pull-up/pull-down register								Address offset: 0x0C		*/
	_vo	uint32_t	IDR;			/* GPIO port input data register 									Address offset: 0x10		*/
	_vo	uint32_t	ODR;			/* GPIO port output data register									Address offset: 0x14		*/
	_vo	uint32_t	BSRR;			/* GPIO Bit set/reset register.										Address offset: 0x18		*/
	_vo	uint32_t	LCKR;			/* GPIO port configuration lock register							Address offset: 0x1C		*/
									/* [0]:GPIO alternate function low register							Address offset: 0x20		*/
	_vo	uint32_t	AFR[2];			/* [1]:GPIO alternate function high register						Address offset: 0x24		*/
}GPIO_RegDef_t;

/*
 * Peripheral Definitions
 * This is simply the Peripheral base addresses type-casted to their RegDef_t from above
 * Doing this so it's easier to use in Application-Land
 */
#define GPIOA	( (GPIO_RegDef_t *) GPIOA_BASEADDR )
#define GPIOB	( (GPIO_RegDef_t *) GPIOB_BASEADDR )
#define GPIOC	( (GPIO_RegDef_t *) GPIOC_BASEADDR )
#define GPIOD	( (GPIO_RegDef_t *) GPIOD_BASEADDR )
#define GPIOE	( (GPIO_RegDef_t *) GPIOE_BASEADDR )
#define GPIOF	( (GPIO_RegDef_t *) GPIOF_BASEADDR )
#define GPIOH	( (GPIO_RegDef_t *) GPIOH_BASEADDR )
#define GPIOI	( (GPIO_RegDef_t *) GPIOI_BASEADDR )

#define RCC		( (RCC_RegDef_t *)  RCC_BASEADDR )

/*
 * Clock Enable Macros to GPIOx Peripherals
 */
#define GPIOA_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 0 ) )
#define GPIOB_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 1 ) )
#define GPIOC_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 2 ) )
#define GPIOD_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 3 ) )
#define GPIOE_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 4 ) )
#define GPIOF_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 5 ) )
#define GPIOG_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 6 ) )
#define GPIOH_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 7 ) )
#define GPIOI_PCLK_EN()	( RCC->AHB1ENR |= ( 1 << 8 ) )

/*
 * Clock Enable Macros for I2Cx Peripherals
 */
#define I2C1_PCLK_EN() ( RCC->APB1ENR |= ( 1 << 21 ) )
#define I2C2_PCLK_EN() ( RCC->APB1ENR |= ( 1 << 22 ) )
#define I2C3_PCLK_EN() ( RCC->APB1ENR |= ( 1 << 23 ) )

/*
 * Clock Enable Macros for SPIx Peripherals
 */
#define SPI1_PCLK_EN() ( RCC->APB2ENR |= ( 1 << 12 ) )
#define SPI2_PCLK_EN() ( RCC->APB1ENR |= ( 1 << 14 ) )
#define SPI3_PCLK_EN() ( RCC->APB1ENR |= ( 1 << 15 ) )
#define SPI4_PCLK_EN() ( RCC->APB2ENR |= ( 1 << 13 ) )


/*
 * Clock Enable Macros for USARTx Peripherals
 */
#define USART1_PCLK_EN() ( RCC->APB2ENR |= ( 1 << 4  ) )
#define USART2_PCLK_EN() ( RCC->APB1ENR |= ( 1 << 17 ) )
#define USART3_PCLK_EN() ( RCC->APB1ENR |= ( 1 << 18 ) )
#define UART4_PCLK_EN()  ( RCC->APB1ENR |= ( 1 << 19 ) )
#define UART5_PCLK_EN()  ( RCC->APB1ENR |= ( 1 << 20 ) )
#define USART6_PCLK_EN() ( RCC->APB2ENR |= ( 1 << 5  ) )


/*
 * Clock Enable Macros for SYSCFG Peripherals
 */
#define SYSCFG_PCLK_EN() ( RCC->APB2ENR |= ( 1 << 14  ) )


/*
 * Clock Disable Macros to GPIOx Peripherals
 */
#define GPIOA_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 0 ) )
#define GPIOB_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 1 ) )
#define GPIOC_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 2 ) )
#define GPIOD_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 3 ) )
#define GPIOE_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 4 ) )
#define GPIOF_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 5 ) )
#define GPIOG_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 6 ) )
#define GPIOH_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 7 ) )
#define GPIOI_PCLK_DI()	( RCC->AHB1ENR &= ~( 1 << 8 ) )

/*
 * Clock Disable Macros for I2Cx Peripherals
 */
#define I2C1_PCLK_DI() ( RCC->APB1ENR &= ~( 1 << 21 ) )
#define I2C2_PCLK_DI() ( RCC->APB1ENR &= ~( 1 << 22 ) )
#define I2C3_PCLK_DI() ( RCC->APB1ENR &= ~( 1 << 23 ) )

/*
 * Clock Disable Macros for SPIx Peripherals
 */
#define SPI1_PCLK_DI() ( RCC->APB2ENR &= ~( 1 << 12 ) )
#define SPI2_PCLK_DI() ( RCC->APB1ENR &= ~( 1 << 14 ) )
#define SPI3_PCLK_DI() ( RCC->APB1ENR &= ~( 1 << 15 ) )
#define SPI4_PCLK_DI() ( RCC->APB2ENR &= ~( 1 << 13 ) )


/*
 * Clock Disable Macros for USARTx Peripherals
 */
#define USART1_PCLK_DI() ( RCC->APB2ENR &= ~( 1 << 4  ) )
#define USART2_PCLK_DI() ( RCC->APB1ENR &= ~( 1 << 17 ) )
#define USART3_PCLK_DI() ( RCC->APB1ENR &= ~( 1 << 18 ) )
#define UART4_PCLK_DI()  ( RCC->APB1ENR &= ~( 1 << 19 ) )
#define UART5_PCLK_DI()  ( RCC->APB1ENR &= ~( 1 << 20 ) )
#define USART6_PCLK_DI() ( RCC->APB2ENR &= ~( 1 << 5  ) )


/*
 * Clock Disable Macros for SYSCFG Peripherals
 */
#define SYSCFG_PCLK_DI() ( RCC->APB2ENR &= ~( 1 << 14  ) )

/*
 * Register Reset Macros for GPIOs
 */
#define GPIOA_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 0 ) );	( RCC->AHB1RSTR &= ~( 1 << 0 ) ); } while(0)
#define GPIOB_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 1 ) );	( RCC->AHB1RSTR &= ~( 1 << 1 ) ); } while(0)
#define GPIOC_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 2 ) );	( RCC->AHB1RSTR &= ~( 1 << 2 ) ); } while(0)
#define GPIOD_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 3 ) );	( RCC->AHB1RSTR &= ~( 1 << 3 ) ); } while(0)
#define GPIOE_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 4 ) );	( RCC->AHB1RSTR &= ~( 1 << 4 ) ); } while(0)
#define GPIOF_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 5 ) );	( RCC->AHB1RSTR &= ~( 1 << 5 ) ); } while(0)
#define GPIOG_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 6 ) );	( RCC->AHB1RSTR &= ~( 1 << 6 ) ); } while(0)
#define GPIOH_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 7 ) );	( RCC->AHB1RSTR &= ~( 1 << 7 ) ); } while(0)
#define GPIOI_REG_RESET()		do { ( RCC->AHB1RSTR |= ( 1 << 8 ) );	( RCC->AHB1RSTR &= ~( 1 << 8 ) ); } while(0)

/*
 * Generic Macros
 */
#define ENABLE 				1
#define DISABLE 			0
#define SET					ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET


#include "stm32f407xx_gpio.h"

#endif /* INC_STM32F407XX_H_ */
