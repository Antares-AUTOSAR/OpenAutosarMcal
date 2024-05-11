/**
 * @file    Mcu_Arch.c
 * @brief   **Mcu Specific Architecture Driver**
 * @author  Angel Lozano
 *
 * Mcu driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Mcu driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef MCU_ARCH_H__
#define MCU_ARCH_H__

#include "Mcu_Types.h"

/**
 * @defgroup RCC_CR_Bit_Values RCC CR register bits
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define RCC_CR_HSION       8u  /*!< RCC_CR -> HSION: HSI16 clock enable */
#define RCC_CR_HSIRDY      10u /*!< RCC_CR -> HSION: HSI16 clock ready flag */
#define RCC_CR_HSEON       16u /*!< RCC_CR -> HSEON: HSE clock enable */
#define RCC_CR_HSERDY      17u /*!< RCC_CR -> HSERDY: HSE clock ready flag */
#define RCC_CR_HSEBYP      18u /*!< RCC_CR -> HSEBYP: HSE crystal oscillator bypass */
#define RCC_CR_HSI48ON     22u /*!< RCC_CR -> HSI48ON: Enable HSI48 RC Oscillator */
#define RCC_CR_HSI48RDY    23u /*!< RCC_CR -> HSI48RDY: HSI48 clock ready flag */
#define RCC_CR_PLLON       24u /*!< RCC_CR -> PLLON: PLL enable */
#define RCC_CR_PLLRDY      25u /*!< RCC_CR -> PLLRDY: PLL clock ready flag */
/**
 * @} */

/**
 * @defgroup RCC_CFGR_Bit_Values RCC CFGR register bits
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define RCC_CFGR_SWS_LSB   3u /*!< RCC_MCOPRE -> SW: System clock switch */
#define RCC_CFGR_SWS_BITS  3u /*!< RCC_MCOPRE -> SW: System clock switch */
/**
 * @} */

/**
 * @defgroup RCC_PLLCFGR_Bit_Values RCC PLL Configuration register bits
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define RCC_PLLCFGR_PLLPEN 16u /*!< RCC_PLLCFGR -> PLLPEN: PLLPCLK clock output enable */
#define RCC_PLLCFGR_PLLQEN 24u /*!< RCC_PLLCFGR -> PLLQEN: PLLQCLK clock output enable */
#define RCC_PLLCFGR_PLLREN 28u /*!< RCC_PLLCFGR -> PLLREN: PLLRCLK clock output enable */
/**
 * @} */

/**
 * @defgroup RCC_BDCR_Bit_Values RCC BDCR register bits
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define RCC_BDCR_LSEON     0u /*!< RCC_BDCR -> LSEON:  LSE oscillator enable           */
#define RCC_BDCR_LSERDY    1u /*!< RCC_BDCR -> LSERDY: LSE oscillator ready            */
#define RCC_BDCR_LSEBYP    2u /*!< RCC_BDCR -> LSEBYP: LSE oscillator bypass           */
/**
 * @} */

/**
 * @defgroup RCC_CSR_Bit_Values RCC CSR register bits
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define RCC_CSR_LSION      0u /*!< RCC_CSR -> LSION:  LSI oscillator enable           */
#define RCC_CSR_LSIRDY     1u /*!< RCC_CSR -> LSIRDY: LSI oscillator ready            */
/**
 * @} */

void Mcu_Arch_Init( Mcu_HwUnit *HwUnit, Mcu_ConfigType *ConfigPtr );
Std_ReturnType Mcu_Arch_InitRamSection( Mcu_HwUnit *HwUnit, Mcu_RamSectionType RamSection );
Std_ReturnType Mcu_Arch_InitClock( Mcu_HwUnit *HwUnit, Mcu_ClkConfigType *ClockSetting );
Std_ReturnType Mcu_Arch_DistributePllClock( Mcu_HwUnit *HwUnit );
Mcu_PllStatusType Mcu_Arch_GetPllStatus( Mcu_HwUnit *HwUnit );
Mcu_ResetType Mcu_Arch_GetResetReason( Mcu_HwUnit *HwUnit );
Mcu_RawResetType Mcu_Arch_GetResetRawValue( Mcu_HwUnit *HwUnit );
void Mcu_Arch_PerformReset( Mcu_HwUnit *HwUnit );
void Mcu_Arch_SetMode( Mcu_HwUnit *HwUnit, Mcu_ModeType McuMode );
Mcu_RamStateType Mcu_Arch_GetRamState( Mcu_HwUnit *HwUnit );

#endif