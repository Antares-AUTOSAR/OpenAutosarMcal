/**
 * @file    Mcu_Arch.c
 * @brief   **Mcu Architecture Driver**
 * @author  Angel Lozano
 *
 * Mcu driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Mcu driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Mcu_Cfg.h"
#include "Mcu_Arch.h"
#include "Bfx.h"

/**
 * @brief Global Rcc registers pointer
 */
static Rcc_RegisterType *Rcc = RCC;

/**
 * @brief    ** Validate value inside a range **
 *
 * Validates that passed avlue is allowed. If allowed values are sorted, is possible to verify
 * that is between max and min values
 *
 * @param   Value Value to validate
 * @param   MinValue Min value
 * @param   MaxValue Max value
 *
 * @retval  boolean: E_OK if the value is valid, E_NOT_OK otherwise
 */
static boolean Validate_ValueInRange( uint32 Value, uint32 MinValue, uint32 MaxValue )
{
    boolean returnValue = E_NOT_OK;

    if( ( Value >= MinValue ) && ( Value <= MaxValue ) )
    {
        returnValue = E_OK;
    }

    return returnValue;
}

/**
 * @brief    ** Validate PLL clock source **
 *
 * Validates that PLL source is an allowed value. If allowed values are sorted, is
 * possible to verify that is between max and min values
 *
 * @param   PllSource PLL source to validate
 *
 * @retval  boolean: E_OK if the value is valid, E_NOT_OK otherwise
 */
static boolean Validate_PllSource( uint32 PllSource )
{
    boolean returnValue = E_NOT_OK;

    if( ( PllSource >= MCU_PLL_SOURCE_NONE ) && ( PllSource <= MCU_PLL_SOURCE_HSE ) )
    {
        if( PllSource != MCU_PLL_SOURCE_NOT_VALID )
        {
            returnValue = E_OK;
        }
    }

    return returnValue;
}

/**
 * @brief    ** Get actual system clock **
 *
 * Get the actual clock used by system (RCC_CFGR[5:3])
 *
 * @retval  uint8: Used sysclock
 */
static uint8 Get_SysClk( void )
{
    uint8 returnValue;
    Rcc_RegisterType *RccRegisters = Rcc;

    returnValue = (uint8)Bfx_GetBits_u32u8u8_u32( RccRegisters->CFGR, RCC_CFGR_SWS_LSB, RCC_CFGR_SWS_BITS );

    return returnValue;
}

/**
 * @brief    **MCU Low Level Initialization**
 *
 * Service to initialize the MCU driver
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   ConfigPtr  Pointer to MCU driver configuration set
 *
 * @reqs    SWS_Mcu_00153
 */
void Mcu_Arch_Init( Mcu_HwUnit *HwUnit, Mcu_ConfigType *ConfigPtr )
{
    Rcc_RegisterType *RccRegisters = Rcc;

    (void)HwUnit;

    /* -------- HSE configuration -------- */
    if( ConfigPtr->ClockConfig.OscConfig.OscillatorType == MCU_OSCILLATORTYPE_HSE )
    {
        // Verify that HSE is not actual sysclock
        if( Get_SysClk( ) != MCU_SYSCLKSOURCE_HSE )
        {
            if( ConfigPtr->ClockConfig.OscConfig.HSEState == MCU_HSE_ON )
            {
                // Disable HSE, disable bypass and Enable HSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
            }
            else if( ConfigPtr->ClockConfig.OscConfig.HSEState == MCU_HSE_BYPASS )
            {
                // Disable HSE, enable bypass and Enable HSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
            }
            else
            {
                // Disable HSE and disable bypass
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEBYP );
            }
        }
    }

    /* -------- HSI configuration -------- */
    else if( ConfigPtr->ClockConfig.OscConfig.OscillatorType == MCU_OSCILLATORTYPE_HSI )
    {
        if( ConfigPtr->ClockConfig.OscConfig.HSIState == MCU_HSI_ON )
        {
            // Set divider
            uint32 setting = 0u;
            setting        = ConfigPtr->ClockConfig.OscConfig.HSIDivider;
            if( Validate_ValueInRange( setting, MCU_HSI_DIV1, MCU_HSI_DIV128 ) == E_OK )
            {
                Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->CR, MCU_HSI_DIV_MASK );
                Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CR, setting );
            }

            // Set calibration value
            setting = ConfigPtr->ClockConfig.OscConfig.HSICalibrationValue;
            if( Validate_ValueInRange( setting, MCU_HSICALIBRATION_MIN_VALUE, MCU_HSICALIBRATION_MAX_VALUE ) == E_OK )
            {
                Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->ICSCR, MCU_HSICALIBRATION_MASK );
                Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CR, ( setting << MCU_HSICALIBRATION_OFFSET ) );
            }

            // Enable HSI
            Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSION );
        }
        else
        {
            // Verify that HSI is not actual sysclock
            if( Get_SysClk( ) != MCU_SYSCLKSOURCE_HSI )
            {
                // Clear bit to disable HSI
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSION );
            }
        }
    }

    /* ------- HSI48 configuration ------- */
    else if( ConfigPtr->ClockConfig.OscConfig.OscillatorType == MCU_OSCILLATORTYPE_HSI48 )
    {
        if( ConfigPtr->ClockConfig.OscConfig.HSI48State == MCU_HSI48_ON )
        {
            // Set bit to enable HSI48
            Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSI48ON );
        }
        else
        {
            // Clear bit to disable HSI48
            Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSI48ON );
        }
    }

    /* -------- LSE configuration -------- */
    else if( ConfigPtr->ClockConfig.OscConfig.OscillatorType == MCU_OSCILLATORTYPE_LSE )
    {
        // Verify that LSE is not actual sysclock
        if( Get_SysClk( ) != MCU_SYSCLKSOURCE_LSE )
        {
            if( ConfigPtr->ClockConfig.OscConfig.LSEState == MCU_LSE_ON )
            {
                // Disable LSE, disable bypass and Enable LSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
            }
            else if( ConfigPtr->ClockConfig.OscConfig.LSEState == MCU_LSE_BYPASS )
            {
                // Disable HSE, enable bypass and Enable HSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
            }
            else
            {
                // Clear bit to disable LSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
            }
        }
    }

    /* -------- LSI configuration -------- */
    else if( ConfigPtr->ClockConfig.OscConfig.OscillatorType == MCU_OSCILLATORTYPE_LSI )
    {
        // Verify that LSI is not actual sysclock
        if( Get_SysClk( ) != MCU_SYSCLKSOURCE_LSI )
        {
            if( ConfigPtr->ClockConfig.OscConfig.LSEState == MCU_LSI_ON )
            {
                // Set bit to enable LSI
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CSR, RCC_CSR_LSION );
            }
            else
            {
                // Clear bit to disable LSI
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CSR, RCC_CSR_LSION );
            }
        }
    }

    /* ------- Other configuration ------- */
    else
    {
    }
}

/**
 * @brief    **MCU Low Level RAM Initialization**
 *
 * Service to initialize the RAM section wise
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   RamSection  Selects RAM memory section provided in configuration set
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00154
 */
Std_ReturnType Mcu_Arch_InitRamSection( Mcu_HwUnit *HwUnit, Mcu_RamSectionType RamSection )
{
    (void)HwUnit;
    (void)RamSection;
    return E_NOT_OK;
}

/**
 * @brief    **MCU Low Level Clock Initialization**
 *
 * Service to initialize the PLL and other MCU specific clock options.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   ClockSetting  Pass the settings to configure Mcu clock
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00155
 */
Std_ReturnType Mcu_Arch_InitClock( Mcu_HwUnit *HwUnit, Mcu_ClkConfigType *ClockSetting )
{
    Std_ReturnType returnValue     = E_NOT_OK;
    Rcc_RegisterType *RccRegisters = Rcc;
    uint32 setting                 = 0u;

    /* -------- HSE configuration -------- */
    if( ClockSetting->OscConfig.OscillatorType == MCU_OSCILLATORTYPE_HSE )
    {
        // Verify that HSE is not actual sysclock
        if( Get_SysClk( ) != MCU_SYSCLKSOURCE_HSE )
        {
            if( ClockSetting->OscConfig.HSEState == MCU_HSE_ON )
            {
                // Disable HSE, disable bypass and Enable HSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
            }
            else if( ClockSetting->OscConfig.HSEState == MCU_HSE_BYPASS )
            {
                // Disable HSE, enable bypass and Enable HSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
            }
            else
            {
                // Disable HSE and disable bypass
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEON );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSEBYP );
            }
        }

        returnValue = E_OK;
    }

    /* -------- HSI configuration -------- */
    else if( ClockSetting->OscConfig.OscillatorType == MCU_OSCILLATORTYPE_HSI )
    {
        if( ClockSetting->OscConfig.HSIState == MCU_HSI_ON )
        {
            // Set divider
            setting = ClockSetting->OscConfig.HSIDivider;
            if( Validate_ValueInRange( setting, MCU_HSI_DIV1, MCU_HSI_DIV128 ) == E_OK )
            {
                Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->CR, MCU_HSI_DIV_MASK );
                Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CR, setting );
            }

            // Set calibration value
            setting = ClockSetting->OscConfig.HSICalibrationValue;
            if( Validate_ValueInRange( setting, MCU_HSICALIBRATION_MIN_VALUE, MCU_HSICALIBRATION_MAX_VALUE ) == E_OK )
            {
                Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->ICSCR, MCU_HSICALIBRATION_MASK );
                Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CR, ( setting << MCU_HSICALIBRATION_OFFSET ) );
            }

            // Enable HSI
            Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSION );
        }
        else
        {
            // Verify that HSI is not actual sysclock
            if( Get_SysClk( ) != MCU_SYSCLKSOURCE_HSI )
            {
                // Clear bit to disable HSI
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSION );
            }
        }

        returnValue = E_OK;
    }

    /* ------- HSI48 configuration ------- */
    else if( ClockSetting->OscConfig.OscillatorType == MCU_OSCILLATORTYPE_HSI48 )
    {
        if( ClockSetting->OscConfig.HSIState == MCU_HSI48_ON )
        {
            // Set bit to enable HSI48
            Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSI48ON );
        }
        else
        {
            // Clear bit to disable HSI48
            Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_HSI48ON );
        }

        returnValue = E_OK;
    }

    /* -------- LSE configuration -------- */
    else if( ClockSetting->OscConfig.OscillatorType == MCU_OSCILLATORTYPE_LSE )
    {
        // Verify that LSE is not actual sysclock
        if( Get_SysClk( ) != MCU_SYSCLKSOURCE_LSE )
        {
            if( ClockSetting->OscConfig.HSIState == MCU_LSE_ON )
            {
                // Disable LSE, disable bypass and Enable LSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
            }
            else if( ClockSetting->OscConfig.HSIState == MCU_HSE_BYPASS )
            {
                // Disable HSE, enable bypass and Enable HSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEBYP );
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
            }
            else
            {
                // Clear bit to disable LSE
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->BDCR, RCC_BDCR_LSEON );
            }

            returnValue = E_OK;
        }
    }

    /* -------- LSI configuration -------- */
    else if( ClockSetting->OscConfig.OscillatorType == MCU_OSCILLATORTYPE_LSI )
    {
        // Verify that LSI is not actual sysclock
        if( Get_SysClk( ) != MCU_SYSCLKSOURCE_LSI )
        {
            if( ClockSetting->OscConfig.HSIState == MCU_LSI_ON )
            {
                // Set bit to enable LSI
                Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CSR, RCC_CSR_LSION );
            }
            else
            {
                // Clear bit to disable LSI
                Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CSR, RCC_CSR_LSION );
            }

            returnValue = E_OK;
        }
    }

    /* ------- Other configuration ------- */
    else
    {
    }

    /* -------- PLL configuration -------- */
    // If new PLL status is enabled
    if( ClockSetting->OscConfig.PLL.PllState == MCU_PLL_STATE_ENABLED )
    {
        uint32 PllConfigValue = 0u;

        // Clear bit to disable PLL
        Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_PLLON );

        // Setting PLL Source
        PllConfigValue = ClockSetting->OscConfig.PLL.PllSource;
        if( Validate_PllSource( PllConfigValue ) == E_OK )
        {
            Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, MCU_PLL_SOURCE_MASK );
            Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, PllConfigValue );
        }

        // Setting PLLM
        PllConfigValue = ClockSetting->OscConfig.PLL.PllM;
        if( Validate_ValueInRange( PllConfigValue, MCU_PLLM_DIV1, MCU_PLLM_DIV8 ) == E_OK )
        {
            Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, MCU_PLLM_MASK );
            Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, PllConfigValue );
        }

        // Setting PLLN
        PllConfigValue = ClockSetting->OscConfig.PLL.PLLN;

        if( Validate_ValueInRange( PllConfigValue, MCU_PLLN_MIN_VALUE, MCU_PLLN_MAX_VALUE ) == E_OK )
        {
            Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, MCU_PLLN_MASK );
            Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, PllConfigValue << MCU_PLLN_OFFSET );
        }

        // PLL P
        PllConfigValue = ClockSetting->OscConfig.PLL.PllP;
        if( Validate_ValueInRange( PllConfigValue, MCU_PLLP_DIV2, MCU_PLLP_DIV32 ) == E_OK )
        {
            Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, MCU_PLLP_MASK );
            Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, PllConfigValue );
            Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->PLLCFGR, RCC_PLLCFGR_PLLPEN );
        }


        // PLL Q
        PllConfigValue = ClockSetting->OscConfig.PLL.PllQ;
        if( Validate_ValueInRange( PllConfigValue, MCU_PLLQ_DIV2, MCU_PLLQ_DIV8 ) == E_OK )
        {
            Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, MCU_PLLQ_MASK );
            Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, PllConfigValue );
            Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->PLLCFGR, RCC_PLLCFGR_PLLQEN );
        }

        // PLL R
        PllConfigValue = ClockSetting->OscConfig.PLL.PllR;
        if( Validate_ValueInRange( PllConfigValue, MCU_PLLR_DIV2, MCU_PLLR_DIV8 ) == E_OK )
        {
            Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, MCU_PLLR_MASK );
            Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->PLLCFGR, PllConfigValue );
            Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->PLLCFGR, RCC_PLLCFGR_PLLREN );
        }

        // Set bit to enable PLL
        Bfx_SetBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_PLLON );

        returnValue |= E_OK;
        HwUnit->Config->PllStatus = MCU_PLL_UNLOCKED;
    }
    else
    {
        // Clear bit to disable PLL
        Bfx_ClrBit_u32u8( (uint32 *)&RccRegisters->CR, RCC_CR_PLLON );
        returnValue               = E_OK;
        HwUnit->Config->PllStatus = MCU_PLL_STATUS_UNDEFINED;
    }

    /* ------- Clock configuration ------- */

    uint8 applySettingFlag = STD_IDLE;

    setting = ClockSetting->ClkConfig.SysClockSource;
    // Verify that selected clock is ready
    switch( setting )
    {
        case MCU_SYSCLKSOURCE_HSI:
            if( Bfx_GetBit_u32u8_u8( RccRegisters->CR, RCC_CR_HSIRDY ) == STD_ACTIVE )
            {
                applySettingFlag = STD_ACTIVE;
            }
            break;

        case MCU_SYSCLKSOURCE_HSE:
            if( Bfx_GetBit_u32u8_u8( RccRegisters->CR, RCC_CR_HSERDY ) == STD_ACTIVE )
            {
                applySettingFlag = STD_ACTIVE;
            }
            break;

        case MCU_SYSCLKSOURCE_PLLCLK:
            if( Bfx_GetBit_u32u8_u8( RccRegisters->CR, RCC_CR_PLLRDY ) == STD_ACTIVE )
            {
                applySettingFlag = STD_ACTIVE;
            }
            break;

        case MCU_SYSCLKSOURCE_LSI:
            if( Bfx_GetBit_u32u8_u8( RccRegisters->CSR, RCC_CSR_LSIRDY ) == STD_ACTIVE )
            {
                applySettingFlag = STD_ACTIVE;
            }
            break;

        case MCU_SYSCLKSOURCE_LSE:
            if( Bfx_GetBit_u32u8_u8( RccRegisters->BDCR, RCC_BDCR_LSERDY ) == STD_ACTIVE )
            {
                applySettingFlag = STD_ACTIVE;
            }
            break;

        default:
            break;
    }
    // Apply new Clock source only if is detected as ready
    if( applySettingFlag == STD_ACTIVE )
    {
        Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, MCU_SYSCLKSOURCE_MASK );
        Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, setting );

        returnValue = E_OK;
    }

    setting = ClockSetting->ClkConfig.AHBClockDivider;
    if( Validate_ValueInRange( setting, MCU_AHB_DIV128, MCU_AHB_DIV512 ) == E_OK )
    {
        Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, MCU_AHB_DIV_MASK );
        Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, setting );

        returnValue = E_OK;
    }

    setting = ClockSetting->ClkConfig.APB1ClockDivider;
    if( Validate_ValueInRange( setting, MCU_APB1_DIV1, MCU_APB1_DIV16 ) == E_OK )
    {
        Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, MCU_APB1_DIV_MASK );
        Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, setting );

        returnValue = E_OK;
    }

    return returnValue;
}

/**
 * @brief    **Low Level PLL to MCU Clock distribution**
 *
 * Service to activate the PLL clock to the MCU clock distribution.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00156
 */
Std_ReturnType Mcu_Arch_DistributePllClock( Mcu_HwUnit *HwUnit )
{
    Std_ReturnType returnValue     = E_NOT_OK;
    Rcc_RegisterType *RccRegisters = Rcc;

    // Verify that PLL is ready
    if( Bfx_GetBit_u32u8_u8( RccRegisters->CR, RCC_CR_PLLRDY ) == STD_ACTIVE )
    {
        // Verify that PLL R output is enabled (its the usable as SYSCLK source)
        if( Bfx_GetBit_u32u8_u8( RccRegisters->PLLCFGR, RCC_PLLCFGR_PLLREN ) == STD_ACTIVE )
        {
            Bfx_ClrBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, MCU_SYSCLKSOURCE_MASK );
            Bfx_SetBitMask_u32u32( (uint32 *)&RccRegisters->CFGR, MCU_SYSCLKSOURCE_PLLCLK );

            returnValue = E_OK;
        }

        HwUnit->Config->PllStatus = MCU_PLL_LOCKED;
    }

    return returnValue;
}

/**
 * @brief    **Get PLL Low Level  lock status**
 *
 * Service which provides the lock status of the PLL
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_PllStatusType: MCU_PLL_LOCKED when the PLL is locked, MCU_PLL_UNLOCKED,
 *          MCU_PLL_STATUS_UNDEFINED when status is unknown
 *
 * @reqs    SWS_Mcu_00157
 */
Mcu_PllStatusType Mcu_Arch_GetPllStatus( Mcu_HwUnit *HwUnit )
{
    Mcu_PllStatusType returnValue;
    Rcc_RegisterType *RccRegisters = Rcc;
    boolean bitState;

    bitState = Bfx_GetBit_u32u8_u8( RccRegisters->CR, RCC_CR_PLLRDY );

    if( bitState == STD_ACTIVE )
    {
        HwUnit->Config->PllStatus = MCU_PLL_LOCKED;
    }
    else
    {
        HwUnit->Config->PllStatus = MCU_PLL_UNLOCKED;
    }

    returnValue = HwUnit->Config->PllStatus;
    return returnValue;
}

/**
 * @brief    **Get MCU Low Level reset type**
 *
 * Service which reads the reset type from the hardware, if supported
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_ResetType: MCU_POWER_ON_RESET, MCU_WATCHDOG_RESET, MCU_SW_RESET,
 *          MCU_RESET_UNDEFINED
 *
 * @reqs    SWS_Mcu_00158
 */
Mcu_ResetType Mcu_Arch_GetResetReason( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

/**
 * @brief    **Get reset raw value Low Level**
 *
 * Service which reads the reset type from the hardware register, if supported
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_RawResetType: Reset raw value
 *
 * @reqs    SWS_Mcu_00159
 */
Mcu_RawResetType Mcu_Arch_GetResetRawValue( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

/**
 * @brief    **Reset the MCU Low Level**
 *
 * Service to perform a microcontroller reset
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @reqs    SWS_Mcu_00160
 */
void Mcu_Arch_PerformReset( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
}

/**
 * @brief    **Set MCU Low Level power mode**
 *
 * Service to activate the MCU power modes
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   McuMode  Set different MCU power modes configured in the configuration set
 *
 * @reqs    SWS_Mcu_00161
 */
void Mcu_Arch_SetMode( Mcu_HwUnit *HwUnit, Mcu_ModeType McuMode )
{
    (void)HwUnit;
    (void)McuMode;
}

/**
 * @brief    **Get status of MCU RAM Low Level **
 *
 * Service which provides the actual status of the microcontroller RAM. (if supported)
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_RamStateType: Status of the RAM Content
 *
 * @reqs    SWS_Mcu_00207
 */
Mcu_RamStateType Mcu_Arch_GetRamState( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}
