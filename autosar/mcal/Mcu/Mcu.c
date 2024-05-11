/**
 * @file    Mcu.c
 * @brief   **Mcu Driver**
 * @author  Angel Lozano
 *
 * The MCU driver provides services for basic microcontroller initialization, power down
 * functionality, reset and microcontroller specific functions required by other MCAL
 * software modules. The initialization services allow a flexible and application related
 * MCU initialization in addition to the start-up code.
 */

#include "Std_Types.h"
#include "Mcu.h"
#include "Mcu_Arch.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Mcu_Cfg.h */
#if MCU_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    Module ID number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Api id
 * @param   ErrorId     Error code
 */
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
/* clang-format off */
/* cppcheck-suppress misra-c2012-8.4 ; qualifier is declared at Mcu.h */
MCU_STATIC Mcu_HwUnit HwUnit_Mcu =
{
    .HwUnitState = MCU_STATE_UNINIT,
    .Config      = NULL_PTR
};
/* clang-format on */

/**
 * @brief    **MCU Initialization**
 *
 * Service to initialize the MCU driver
 *
 * @param   ConfigPtr  Pointer to MCU driver configuration set
 *
 * @reqs    SWS_Mcu_00153
 */
void Mcu_Init( Mcu_ConfigType *ConfigPtr )
{
    Mcu_Arch_Init( &HwUnit_Mcu, ConfigPtr );

    HwUnit_Mcu.HwUnitState = MCU_STATE_INIT;
    HwUnit_Mcu.Config      = ConfigPtr;
}

/**
 * @brief    **MCU RAM Initialization**
 *
 * Service to initialize the RAM section wise
 *
 * @param   RamSection  Selects RAM memory section provided in configuration set
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00154, SWS_Mcu_00017, SWS_Mcu_00125
 */
Std_ReturnType Mcu_InitRamSection( Mcu_RamSectionType RamSection )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_INIT_RAM, MCU_E_UNINIT );
    }
    else
    {
        ReturnValue = Mcu_Arch_InitRamSection( &HwUnit_Mcu, RamSection );
    }

    return ReturnValue;
}

#if MCU_INIT_CLOCK == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **MCU Clock Initialization**
 *
 * Service to initialize the PLL and other MCU specific clock options.
 *
 * @param   ClockSetting  Pass the settings to configure Mcu clock
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00155, SWS_Mcu_00017, SWS_Mcu_00125
 */
Std_ReturnType Mcu_InitClock( Mcu_ClkConfigType ClockSetting )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_INIT_CLOCK, MCU_E_UNINIT );
    }
    else
    {
        ReturnValue = Mcu_Arch_InitClock( &HwUnit_Mcu, &ClockSetting );
    }

    return ReturnValue;
}
#endif

#if MCU_NO_PLL == STD_OFF /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **PLL to MCU Clock distribution**
 *
 * Service to activate the PLL clock to the MCU clock distribution.
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00156, SWS_Mcu_00017, SWS_Mcu_00122, SWS_Mcu_00125
 */
Std_ReturnType Mcu_DistributePllClock( void )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_DISTRIBUTE_PLL_CLOCK, MCU_E_UNINIT );
    }
    else if( ( HwUnit_Mcu.Config->PllStatus == MCU_PLL_UNLOCKED ) || ( HwUnit_Mcu.Config->PllStatus == MCU_PLL_STATUS_UNDEFINED ) )
    {
        /* If the development error detection is enabled for the MCU module:
        A error shall be reported if the status of the PLL is detected as not locked.
        The DET error reporting shall be used. Related error value: MCU_E_PLL_NOT_LOCKED */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_DISTRIBUTE_PLL_CLOCK, MCU_E_PLL_NOT_LOCKED );
    }
    else
    {
        ReturnValue = Mcu_Arch_DistributePllClock( &HwUnit_Mcu );
    }

    return ReturnValue;
}
#endif

/**
 * @brief    **Get PLL lock status**
 *
 * Service which provides the lock status of the PLL
 *
 * @retval  Mcu_PllStatusType: MCU_PLL_LOCKED when the PLL is locked, MCU_PLL_UNLOCKED,
 *          MCU_PLL_STATUS_UNDEFINED when status is unknown
 *
 * @reqs    SWS_Mcu_00157, SWS_Mcu_00017, SWS_Mcu_00125
 */
Mcu_PllStatusType Mcu_GetPllStatus( void )
{
    Mcu_PllStatusType ReturnValue = MCU_PLL_UNLOCKED;

    /* clang-format off */
    /* cppcheck-suppress misra-c2012-20.9 ; if PLL is not supported must return specified value */
    #if MCU_NO_PLL == STD_ON
        ReturnValue = MCU_PLL_STATUS_UNDEFINED;
    #else
        if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
        {
            ReturnValue = MCU_PLL_STATUS_UNDEFINED;
        }
        else
        {
            ReturnValue = Mcu_Arch_GetPllStatus( &HwUnit_Mcu );
        }
    #endif
    /* clang-format on */

    return ReturnValue;
}

/**
 * @brief    **Get MCU reset type**
 *
 * Service which reads the reset type from the hardware, if supported
 *
 * @retval  Mcu_ResetType: MCU_POWER_ON_RESET, MCU_WATCHDOG_RESET, MCU_SW_RESET,
 *          MCU_RESET_UNDEFINED
 *
 * @reqs    SWS_Mcu_00158, SWS_Mcu_00017, SWS_Mcu_00125
 */
Mcu_ResetType Mcu_GetResetReason( void )
{
    Mcu_ResetType ReturnValue = MCU_RESET_UNDEFINED;

    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_GET_RESET_REASON, MCU_E_UNINIT );
    }
    else
    {
        ReturnValue = Mcu_Arch_GetResetReason( &HwUnit_Mcu );
    }

    return ReturnValue;
}

/**
 * @brief    **Get reset raw value**
 *
 * Service which reads the reset type from the hardware register, if supported
 *
 * @retval  Mcu_RawResetType: Reset raw value
 *
 * @reqs    SWS_Mcu_00159, SWS_Mcu_00017, SWS_Mcu_00125
 */
Mcu_RawResetType Mcu_GetResetRawValue( void )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_GET_RESET_RAW_VALUE, MCU_E_UNINIT );
    }
    else
    {
        ReturnValue = Mcu_Arch_GetResetRawValue( &HwUnit_Mcu );
    }

    return ReturnValue;
}

#if MCU_PERFORM_RESET_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Reset the MCU**
 *
 * Service to perform a microcontroller reset
 *
 * @reqs    SWS_Mcu_00160, SWS_Mcu_00017, SWS_Mcu_00125
 */
void Mcu_PerformReset( void )
{
    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_PERFORM_RESET, MCU_E_UNINIT );
    }
    else
    {
        Mcu_Arch_PerformReset( &HwUnit_Mcu );
    }
}
#endif

/**
 * @brief    **Set MCU power mode**
 *
 * Service to activate the MCU power modes
 *
 * @param   McuMode  Set different MCU power modes configured in the configuration set
 *
 * @reqs    SWS_Mcu_00161, SWS_Mcu_00017, SWS_Mcu_00125
 */
void Mcu_SetMode( Mcu_ModeType McuMode )
{
    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_SET_MODE, MCU_E_UNINIT );
    }
    else
    {
        Mcu_Arch_SetMode( &HwUnit_Mcu, McuMode );
    }
}

#if MCU_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Get version information**
 *
 * Service to return the version information of this module
 *
 * @param   versioninfo  Pointer to where to store the version information of this module
 *
 * @reqs    SWS_Mcu_00162, SWS_Mcu_00125
 */
void Mcu_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo == NULL_PTR )
    {
        /* If development error detection for the Mcu module is enabled:
        The function Mcu_GetVersionInfo shall raise the error MCU_E_PARAM_POINTER if the parameter
        versionInfo is a null pointer */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_GET_VERSION_INFO, MCU_E_PARAM_POINTER );
    }
    else
    {
        versioninfo->moduleID         = MCU_MODULE_ID;
        versioninfo->vendorID         = MCU_VENDOR_ID;
        versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;
    }
}
#endif

#if MCU_GET_RAM_STATE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Get status of MCU RAM**
 *
 * Service which provides the actual status of the microcontroller RAM. (if supported)
 *
 * @retval  Mcu_RamStateType: Status of the RAM Content
 *
 * @reqs    SWS_Mcu_00207, SWS_Mcu_00017, SWS_Mcu_00125
 */
Mcu_RamStateType Mcu_GetRamState( void )
{
    Mcu_RamStateType ReturnValue = MCU_RAMSTATE_INVALID;

    if( HwUnit_Mcu.HwUnitState == MCU_STATE_UNINIT )
    {
        /* If the development error detection is enabled for the MCU module:
        If any function except Mcu_GetVersionInfo of the MCU module is called before
        Mcu_Init function, the error code MCU_E_UNINIT shall be reported to the DET. */
        Det_ReportError( MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_ID_GET_RAM_STATE, MCU_E_UNINIT );
    }
    else
    {
        ReturnValue = Mcu_Arch_GetRamState( &HwUnit_Mcu );
    }

    return ReturnValue;
}
#endif