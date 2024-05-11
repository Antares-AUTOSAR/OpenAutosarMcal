/**
 * @file    Mcu.h
 * @brief   **Mcu Driver header**
 * @author  Angel Lozano
 *
 * The MCU driver provides services for basic microcontroller initialization, power down
 * functionality, reset and microcontroller specific functions required by other MCAL
 * software modules. The initialization services allow a flexible and application related
 * MCU initialization in addition to the start-up code.
 */
#ifndef MCU_H__
#define MCU_H__

#include "Mcu_Cfg.h"


void Mcu_Init( Mcu_ConfigType *ConfigPtr );
Std_ReturnType Mcu_InitRamSection( Mcu_RamSectionType RamSection );
#if MCU_INIT_CLOCK == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Mcu_InitClock( Mcu_ClkConfigType ClockSetting );
#endif
#if MCU_NO_PLL == STD_OFF /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Mcu_DistributePllClock( void );
#endif
Mcu_PllStatusType Mcu_GetPllStatus( void );
Mcu_ResetType Mcu_GetResetReason( void );
Mcu_RawResetType Mcu_GetResetRawValue( void );
#if MCU_PERFORM_RESET_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Mcu_PerformReset( void );
#endif
void Mcu_SetMode( Mcu_ModeType McuMode );
#if MCU_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Mcu_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
#if MCU_GET_RAM_STATE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Mcu_RamStateType Mcu_GetRamState( void );
#endif

#endif