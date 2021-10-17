/*
 * stm32f407xx_gpio.h
 *
 *  Created on: Oct 14, 2021
 *      Author: Jeremy
 */

#ifndef INC_STM32F407XX_GPIO_H_
#define INC_STM32F407XX_GPIO_H_

#include "stm32f407xx.h"

/*
 * This is a configuration structure for a GPIO pin
 */
typedef struct
{
	uint8_t GPIO_PinNumber;					/* Configuration Pin Number Possible values from @GPIO_PIN_NUMBERS */
	uint8_t GPIO_PinMode;					/* Pin Mode Possible values from @GPIO_PIN_MODES */
	uint8_t GPIO_PinSpeed;					/* Pin Speed Possible values from @GPIO_PIN_SPEED*/
	uint8_t GPIO_PinPuPdControl;			/* Pull Up / Pull Down Control Possible values from @GPIO_PUPD_CONFIG */
	uint8_t GPIO_PinOPType;					/* Output type Possible values from @GPIO_OP_TYPES */
	uint8_t GPIO_PinAltFunMode;				/* Alternate function mode */
}GPIO_PinConfig_t;

/*
 * This is a Handle structure for a GPIO Pin
 */

typedef struct
{
	GPIO_RegDef_t 		*pGPIOx;			/* This holds the base address of the GPIO port to which the pin belongs */
	GPIO_PinConfig_t 	GPIO_PinConfig;		/* This holds the GPIO Pin Config Settings */

}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO Pin Numbers
 */
#define GPIO_PIN_NO_0			 0
#define GPIO_PIN_NO_1			 1
#define GPIO_PIN_NO_2			 2
#define GPIO_PIN_NO_3			 3
#define GPIO_PIN_NO_4			 4
#define GPIO_PIN_NO_5			 5
#define GPIO_PIN_NO_6			 6
#define GPIO_PIN_NO_7			 7
#define GPIO_PIN_NO_8			 8
#define GPIO_PIN_NO_9			 9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15

/*
 * @GPIO_PIN_MODES
 * GPIO Pin Possible Modes
 */
#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ALTFN			2
#define GPIO_MODE_ANALOG		3
/* These GPIO Modes are for our internal tracking they are not present in the GPIOx_MODER */
#define GPIO_MODE_IT_FT			4			/* Interrupt Falling Edge Trigger 		 */
#define GPIO_MODE_IT_RT			5			/* Interrupt Rising Edge Trigger 		 */
#define GPIO_MODE_IT_RFT		6			/* Interrupt Rising-Falling Edge Trigger */

/*
 * @GPIO_OP_TYPES
 * GPIO Pin Output Types
 */
#define GPIO_OP_TYPE_PP			0			/* Output Mode Push-Pull				*/
#define GPIO_OP_TYPE_OD			1			/* Output Mode Open-Drain				*/

/*
 * @GPIO_PIN_SPEED
 * GPIO Pin Output Speed Types
 */
#define GPIO_SPD_LS				0			/* Output Low Speed						*/
#define GPIO_SPD_MS				1			/* Output Medium Speed					*/
#define GPIO_SPD_HS				2			/* Output High Speed					*/
#define GPIO_SPD_VHS			3			/* Output Very High Speed				*/

/*
 * @GPIO_PUPD_CONFIG
 * GPIO Pullup-Pulldown Configuration
 */
#define GPIO_NO_PUPD			0			/* Internal Pullup-Pulldown is off		*/
#define GPIO_PIN_PU				1			/* Internal Pullup turned on			*/
#define GPIO_PIN_PD				2			/* Internal Pulldown turned on			*/

/***********************************************************************************************************************
 *                                           APIs supported by this driver
 *                         For more information about the APIs check the function definitions
 ************************************************************************************************************************/

/*
 * Peripheral Clock Setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and De-Init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data Read and Write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * IRQ Configuration and ISR Handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F407XX_GPIO_H_ */
