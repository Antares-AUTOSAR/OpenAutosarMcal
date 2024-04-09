/**
 * @file    test_Mcu.c
 * @brief   **Unit testing for MCU Driver**
 * @author  Angel Lozano
 *
 * This file contains 23 unit test cases for the module Mcu, covering its 11 functions and
 * 24 branches
 * ...
 */
#include "unity.h"
#include "Mcu_Cfg.h"
#include "Mcu.h"
#include "mock_Mcu_Arch.h"
#include "mock_Det.h"

extern Mcu_HwUnit HwUnit_Mcu;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    /* For test uninit check of every function assume that HwUnit is uninit */
    HwUnit_Mcu.HwUnitState = MCU_STATE_UNINIT;
    HwUnit_Mcu.Config      = NULL_PTR;
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   **Test Init when module is uninitialized**
 *
 * The test runs Init function and checks that HwUnitState of the HwUnit struct changed by
 * MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_Init__run_for_first_time( void )
{
    Mcu_ConfigType McuConfig_test = { 0 };

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Mcu.HwUnitState, MCU_STATE_INIT, "Expected HwUnitState changed to MCU_STATE_INIT(1)" );
    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Mcu.Config, &McuConfig_test, "Expected Config points to McuConfigTest" );
}

/**
 * @brief   **Test InitRamSection with module Uninitialized**
 *
 * The test runs InitRamSection function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Expected E_NOT_OK (1) since function
 * executed with an error
 */
void test__Mcu_InitRamSection__run_before_Mcu_init( void )
{
    Mcu_RamSectionType RamSection_test = 0;
    Std_ReturnType ReturnValue         = E_NOT_OK;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_InitRamSection( RamSection_test );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_NOT_OK (1) due to UNINIT error" );
}

/**
 * @brief   **Test InitRamSection with module Initialized**
 *
 * The test runs InitRamSection function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock,
 * returning the E_OK value (0) which is used to validate that the function runs as expected
 */
void test__Mcu_InitRamSection__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test      = { 0 };
    Mcu_RamSectionType RamSection_test = 0;
    Std_ReturnType ReturnValue         = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_InitRamSection_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_InitRamSection( RamSection_test );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0) due to sucessful execution" );
}

/**
 * @brief   **Test InitClock with module Uninitialized**
 *
 * The test runs InitClock function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Expected E_NOT_OK (1) since function
 * executed with an error
 */
void test__Mcu_InitClock__run_before_Mcu_init( void )
{
    Mcu_ClockType ClockSetting_test = 0;
    Std_ReturnType ReturnValue      = E_NOT_OK;

    Det_ReportError_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_InitClock( ClockSetting_test );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_NOT_OK (1) due to UNINIT error" );
}

/**
 * @brief   **Test InitClock with module Initialized**
 *
 * The test runs InitClock function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock,
 * returning the E_OK value (0) which is used to validate that the function runs as expected
 */
void test__Mcu_InitClock__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test   = { 0 };
    Mcu_ClockType ClockSetting_test = 0;
    Std_ReturnType ReturnValue      = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_InitClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_InitClock( ClockSetting_test );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0) due to sucessful execution" );
}

/**
 * @brief   **Test DistributePllClock with module Uninitialized**
 *
 * The test runs DistributePllClock function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Since function finished with an error, the
 * expected return value is E_NOT_OK (1)
 */
void test__Mcu_DistributePllClock__run_before_Mcu_init( void )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    Det_ReportError_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_NOT_OK (1) due to UNINIT error" );
}

/**
 * @brief   **Test DistributePllClock with module Initialized and pll unlocked**
 *
 * The test runs DistributePllClock function after the Mcu module is initialized, but with pll
 * status as MCU_PLL_UNLOCKED, just to check the DET executes. Since function finished with an
 * error, the expected return value is E_NOT_OK (1)
 */
void test__Mcu_DistributePllClock__run_after_Mcu_init_with_pll_unlocked( void )
{
    Mcu_ConfigType McuConfig_test = { .PllStatus = MCU_PLL_UNLOCKED };
    Std_ReturnType ReturnValue    = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Det_ReportError_IgnoreAndReturn( E_OK );

    Mcu_Arch_DistributePllClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_NOT_OK (1) due to PLL error" );
}

/**
 * @brief   **Test DistributePllClock with module Initialized and pll undefined**
 *
 * The test runs DistributePllClock function after the Mcu module is initialized, but with pll
 * status as MCU_PLL_STATUS_UNDEFINED, just to check the DET executes. Since function finished
 * with an error, the expected return value is E_NOT_OK (1)
 */
void test__Mcu_DistributePllClock__run_after_Mcu_init_with_pll_undefined( void )
{
    Mcu_ConfigType McuConfig_test = { .PllStatus = MCU_PLL_STATUS_UNDEFINED };
    Std_ReturnType ReturnValue    = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Det_ReportError_IgnoreAndReturn( E_OK );

    Mcu_Arch_DistributePllClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_NOT_OK (1) due to PLL error" );
}

/**
 * @brief   **Test DistributePllClock with module Initialized and pll locked**
 *
 * The test runs DistributePllClock function after the Mcu module is initialized, but with pll
 * status as MCU_PLL_LOCKED, which means that Arch function can be executed. Since function
 * finished without errors, the expected return value is E_OK (0)
 */
void test__Mcu_DistributePllClock__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test = { .PllStatus = MCU_PLL_LOCKED };
    Std_ReturnType ReturnValue    = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_DistributePllClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0) due to succesful execution" );
}

/**
 * @brief   **Test GetPllStatus with module Uninitialized**
 *
 * The test runs GetPllStatus function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Since function finished with an error, the
 * expected return value is MCU_PLL_UNLOCKED (1)
 */
void test__Mcu_GetPllStatus__run_before_Mcu_init( void )
{
    Mcu_PllStatusType ReturnValue = MCU_PLL_UNLOCKED;

    Det_ReportError_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetPllStatus( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, MCU_PLL_UNLOCKED, "Expected MCU_PLL_UNLOCKED (1) due to UNINIT error" );
}

/**
 * @brief   **Test GetPllStatus with module Initialized**
 *
 * The test runs GetPllStatus function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock,
 * returning the MCU_PLL_LOCKED value (0) which is used to validate that the function runs
 * as expected
 */
void test__Mcu_GetPllStatus__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test = { 0 };
    Mcu_PllStatusType ReturnValue = MCU_PLL_UNLOCKED;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_GetPllStatus_IgnoreAndReturn( MCU_PLL_LOCKED );
    ReturnValue = Mcu_GetPllStatus( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, MCU_PLL_LOCKED, "Expected MCU_PLL_LOCKED (0)" );
}

/**
 * @brief   **Test GetResetReason with module Uninitialized**
 *
 * The test runs GetResetReason function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Since function finished with an error, the
 * expected return value is MCU_RESET_UNDEFINED (3)
 */
void test__Mcu_GetResetReason__run_before_Mcu_init( void )
{
    Mcu_ResetType ReturnValue = MCU_RESET_UNDEFINED;

    Det_ReportError_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetResetReason( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, MCU_RESET_UNDEFINED, "Expected MCU_RESET_UNDEFINED (3)" );
}

/**
 * @brief   **Test GetResetReason with module Initialized**
 *
 * The test runs GetResetReason function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock,
 * returning the MCU_POWER_ON_RESET value (0) which is used to validate that the function runs
 * as expected
 */
void test__Mcu_GetResetReason__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test = { 0 };
    Mcu_ResetType ReturnValue     = MCU_RESET_UNDEFINED;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_GetResetReason_IgnoreAndReturn( MCU_POWER_ON_RESET );
    ReturnValue = Mcu_GetResetReason( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, MCU_POWER_ON_RESET, "Expected MCU_POWER_ON_RESET (0) due to successful execution" );
}

/**
 * @brief   **Test GetResetRawValue with module Uninitialized**
 *
 * The test runs GetResetRawValue function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Since function finished with an error, the
 * expected return value is 1
 */
void test__Mcu_GetResetRawValue__run_before_Mcu_init( void )
{
    Mcu_RawResetType ReturnValue = 1;

    Det_ReportError_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetResetRawValue( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, 1, "Expected 1 value due to error" );
}

/**
 * @brief   **Test GetResetRawValue with module Initialized**
 *
 * The test runs GetResetRawValue function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock,
 * returning the 0 value, which is used to validate that the function runs as expected
 */
void test__Mcu_GetResetRawValue__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test = { 0 };
    Mcu_RawResetType ReturnValue  = 1;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_GetResetRawValue_IgnoreAndReturn( 0 );
    ReturnValue = Mcu_GetResetRawValue( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, 0, "Expected 0 value due to successful execution" );
}

/**
 * @brief   **Test PerformReset with module Uninitialized**
 *
 * The test runs PerformReset function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed
 */
void test__Mcu_PerformReset__run_before_Mcu_init( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_PerformReset( );
}

/**
 * @brief   **Test GetResetRawValue with module Initialized**
 *
 * The test runs GetResetRawValue function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock. This
 * is a non-return function, so no check value-change validation is performed
 */
void test__Mcu_PerformReset__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test = { 0 };

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_PerformReset_Ignore( );
    Mcu_PerformReset( );
}

/**
 * @brief   **Test SetMode with module Uninitialized**
 *
 * The test runs SetMode function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed
 */
void test__Mcu_SetMode__run_before_Mcu_init( void )
{
    Mcu_ModeType McuMode_test = 0;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_SetMode( McuMode_test );
}

/**
 * @brief   **Test SetMode with module Initialized**
 *
 * The test runs SetMode function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock. This
 * is a non-return function, so no check value-change validation is performed
 */
void test__Mcu_SetMode__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test = { 0 };
    Mcu_ModeType McuMode_test     = 0;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_SetMode_Ignore( );
    Mcu_SetMode( McuMode_test );
}

/**
 * @brief   **Test GetVersionInfo with module Uninitialized**
 *
 * The test runs GetVersionInfo function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Noo check value-change validation is performed
 * due to no passing a VersionInfoType pointer
 */
void test__Mcu_GetVersionInfo__run_without_rigth_parameter( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_GetVersionInfo( NULL_PTR );
}

/**
 * @brief   **Test GetVersionInfo with module Initialized**
 *
 * The test runs GetVersionInfo function after the Mcu module is initialized.
 * value-change validation is performed on the VersionInfo struct
 */
void test__Mcu_GetVersionInfo__run_with_rigth_parameter( void )
{
    Std_VersionInfoType versionInfo_test = { 0 };

    Mcu_GetVersionInfo( &versionInfo_test );

    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.moduleID, MCU_MODULE_ID, "Expected MCU_MODULE_ID (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.vendorID, MCU_VENDOR_ID, "Expected MCU_VENDOR_ID (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.sw_major_version, MCU_SW_MAJOR_VERSION, "Expected MCU_SW_MAJOR_VERSION (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.sw_minor_version, MCU_SW_MINOR_VERSION, "Expected MCU_SW_MINOR_VERSION (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.sw_patch_version, MCU_SW_PATCH_VERSION, "Expected MCU_SW_MINOR_VERSION (0)" );
}

/**
 * @brief   **Test GetRamState with module Uninitialized**
 *
 * The test runs GetRamState function before the Mcu module is initialized, just to check
 * the branch which executes the Det for this case. Since function finished with an error, the
 * expected return value is MCU_RAMSTATE_INVALID (0)
 */
void test__Mcu_GetRamState__run_before_Mcu_init( void )
{
    Mcu_RamStateType ReturnValue = MCU_RAMSTATE_INVALID;

    Det_ReportError_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetRamState( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, MCU_RAMSTATE_INVALID, "Expected MCU_RAMSTATE_INVALID (0) value due to error" );
}

/**
 * @brief   **Test GetRamState with module Initialized**
 *
 * The test runs GetRamState function after the Mcu module is initialized, just to check
 * the branch which executes the Arch function. The arch function is ignored with a mock,
 * returning the MCU_RAMSTATE_VALID value (1) which is used to validate that the function runs
 * as expected
 */
void test__Mcu_GetRamState__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfig_test = { 0 };
    Mcu_RamStateType ReturnValue  = MCU_RAMSTATE_INVALID;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfig_test );

    Mcu_Arch_GetRamState_IgnoreAndReturn( MCU_RAMSTATE_VALID );
    ReturnValue = Mcu_GetRamState( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, MCU_RAMSTATE_VALID, "Expected MCU_RAMSTATE_VALID (1)" );
}