/*
 * stm32f407xx_gpio.c
 *
 *  Created on: Oct 14, 2021
 *      Author: Jeremy
 */

#include "stm32f407xx_gpio.h"


/**
 * This function is used to enable or disable the GPIO Peripheral Clock.
 *
 * @param pGPIOx Pointer to the GPIO Port base address
 * @param EnorDi Enable or Disable
 * @return No value is returned
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
			GPIOA_PCLK_EN();
		else if(pGPIOx == GPIOA)
			GPIOA_PCLK_EN();
		else if(pGPIOx == GPIOB)
			GPIOB_PCLK_EN();
		else if(pGPIOx == GPIOC)
			GPIOC_PCLK_EN();
		else if(pGPIOx == GPIOD)
			GPIOD_PCLK_EN();
		else if(pGPIOx == GPIOE)
			GPIOE_PCLK_EN();
		else if(pGPIOx == GPIOF)
			GPIOF_PCLK_EN();
		else if(pGPIOx == GPIOH)
			GPIOH_PCLK_EN();
		else if(pGPIOx == GPIOI)
			GPIOI_PCLK_EN();
	}
	else
	{
		if(pGPIOx == GPIOA)
			GPIOA_PCLK_DI();
		else if(pGPIOx == GPIOA)
			GPIOA_PCLK_DI();
		else if(pGPIOx == GPIOB)
			GPIOB_PCLK_DI();
		else if(pGPIOx == GPIOC)
			GPIOC_PCLK_DI();
		else if(pGPIOx == GPIOD)
			GPIOD_PCLK_DI();
		else if(pGPIOx == GPIOE)
			GPIOE_PCLK_DI();
		else if(pGPIOx == GPIOF)
			GPIOF_PCLK_DI();
		else if(pGPIOx == GPIOH)
			GPIOH_PCLK_DI();
		else if(pGPIOx == GPIOI)
			GPIOI_PCLK_DI();
	}
}

/**
 * This function is used to initialize a GPIO Pin for use.
 *
 * @param pGPIOHandle Pointer to the structure containing the GPIO Pin configuration information.
 * @return No value is returned
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t buf = 0; // Create a temporary register initialized to all 0s;

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		/* Here we are setting the Pin Mode value into the register buffer
		 * The register allots 2 bits per pin number so we first pull
		 * the Pin Mode to set from the provided handle, then left
		 * shift INTO the buffer. Our position is 2 (width of
		 * the allotment) times our pin number. The width is defined by ST
		 * and can be verified in section 8.4.1 of the Reference Manual.
		 */
		buf = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );

		/*
		 * Write the inverse of 0x3 (binary 11) to the the Pin Position's Mode Register
		 * This is the proper way to ensure a 2 bit wide field such as Mode is
		 * set to 0 since the logical inverse of 1 = 0
		 */
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		/*
		 * Set the temporary buffer to the MCU's memory using bitwise OR
		 * Using a bitwise OR will only change the bits assigned in the temporary buffer
		 */
		pGPIOHandle->pGPIOx->MODER |= buf;

	}
	else
	{
		// TODO: HANDLE INTERRUPTS
	}

	/*
	 * Re-Initialize the temporary buffer
	 */
	buf = 0;

	// The GPIOx_OSPEEDR register is also 2 bits wide so we perform the same shift as above
	buf = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (  2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OSPEEDR |= buf;

	buf = 0;

	// The GPIOx_PUPDR register is also 2 bits wide so we perform the same shift as above
	buf = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (  2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );
	pGPIOHandle->pGPIOx->PUPDR |= buf;

	buf = 0;

	// GPIOx_OTYPER is only a single bit wide so we do not need to multiply by 2
	buf = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER |= buf;

	buf = 0;

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint32_t register_pos, pin_offset;

		// This is integer math to determine if we are AF High or Low Register
		register_pos = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		// Now we use a modulus operator to determine which pin position we start at
		pin_offset = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

		/*
		 * To Clear 4-bit wide we need to write the binary inverse of 1111 which converts to
		 * 0xF starting at our calculated pin_offset
		 */
		pGPIOHandle->pGPIOx->AFR[register_pos] &= ~(0xF << ( 4 * pin_offset ));

		// The GPIO Alternate Registers are 4 bits wide since we have up to 16 alternate functions
		// So adjust our left shift to allow for 4 bit values starting at our pin offset
		pGPIOHandle->pGPIOx->AFR[register_pos] |= ( pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (  4 * pin_offset ) );
	}
}

/**
 * This function is used to de-initialize a GPIO port's configuration.
 *
 * @param pGPIOx Pointer to the GPIO Port base address
 * @return No value is returned
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
		GPIOA_REG_RESET();
	else if(pGPIOx == GPIOA)
		GPIOA_REG_RESET();
	else if(pGPIOx == GPIOB)
		GPIOB_REG_RESET();
	else if(pGPIOx == GPIOC)
		GPIOC_REG_RESET();
	else if(pGPIOx == GPIOD)
		GPIOD_REG_RESET();
	else if(pGPIOx == GPIOE)
		GPIOE_REG_RESET();
	else if(pGPIOx == GPIOF)
		GPIOF_REG_RESET();
	else if(pGPIOx == GPIOH)
		GPIOH_REG_RESET();
	else if(pGPIOx == GPIOI)
		GPIOI_REG_RESET();
}

/**
 * This function is used to read digital input from a GPIO pin.
 *
 * @param pGPIOx Pointer to the GPIO Port base address
 * @param PinNumber Pin number to read from
 * @return Returns 0 or 1
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	// Temporary input buffer
	uint8_t input_value = 0;

	/*
	 * Right-Shift the Input Data Register to make the Pin Number our
	 * most significant bit on the right side. Mask all other bits by
	 * 0. We are only interested in returning our Pin Number position
	 */
	input_value = (uint8_t)( ( pGPIOx->IDR >> PinNumber) & 0x00000001 );

	return input_value;
}

/**
 * Read input from all 16 pins on a GPIO port.
 *
 * @param pGPIOx Pointer to the GPIO Port base address
 * @return Bit array of data representing binary input from pins on GPIO Port
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	// Temporary input buffer
	uint16_t input_value = 0;

	/*
	 * Read the Input Data Register
	 * Cast it to 16 Bit Array
	 * Return it
	 */
	input_value = (uint16_t)pGPIOx->IDR;

	return input_value;
}

/**
 * Write a digital value to a GPIO pin.
 *
 * @param pGPIOx Pointer to the GPIO Port base address
 * @param PinNumber Pin number to write to
 * @param Value Digital value you wish to write
 * @return No value is returned
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// Write 1
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		// Write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

/**
 * Write a value to a 16 pins on a GPIO port.
 *
 * @param pGPIOx Pointer to the GPIO Port base address
 * @param Value Bit array of data representing binary output to write to GPIO pins.
 * @return No value is returned
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR	= Value;
}

/**
 * Toggle Output mode for a Pin. This will switch between Open Drain and Pull-Pull
 *
 * @param pGPIOx Pointer to the GPIO Port base address
 * @param PinNumber The pin number you wish to toggle
 * @return No value is returned
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	/*
	 * To Toggle we simply perform a bitwise
	 * XOR operation on the provided Pin
	 */
	pGPIOx->ODR ^= ( 1 << PinNumber );
}

/**
 * Configure the Interrupt Request settings for a GPIO.
 *
 * @param IRQNumber The Interrupt ID being configured
 * @param IRQPriority The priority to set the interrupt to
 * @param EnorDi Is this interrupt being Enabled or Disabled
 * @return No value is returned
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

}

/**
 * This function handles the Interrupt Requests for GPIOs.
 *
 * @param PinNumber The pin number the interrupt request was called on
 * @return No value is returned
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
