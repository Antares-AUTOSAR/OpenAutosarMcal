/**
 * @file    Mcu_Types.h
 * @brief   **Mcu Driver Types**
 * @author  Angel Lozano
 *
 * This header file contains type definitions used by Mcu module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef MCU_TYPES_H__
#define MCU_TYPES_H__

#include "Registers.h"
#include "Std_Types.h"

/**
 * @defgroup MCU_Ids MCU Id number for module and each API service
 *
 * @{ */
#define MCU_ID_INIT                 0x00u /*!< Mcu_Init() api service id */
#define MCU_ID_INIT_RAM             0x01u /*!< Mcu_InitRamSection() api service id */
#define MCU_ID_INIT_CLOCK           0x02u /*!< Mcu_InitClock() api service id */
#define MCU_ID_DISTRIBUTE_PLL_CLOCK 0x03u /*!< Mcu_DistributePllClock() api service id */
#define MCU_ID_GET_PLL_STATUS       0x04u /*!< Mcu_GetPllStatus() api service id */
#define MCU_ID_GET_RESET_REASON     0x05u /*!< Mcu_GetResetReason() api service id */
#define MCU_ID_GET_RESET_RAW_VALUE  0x06u /*!< Mcu_GetResetRawValue() api service id */
#define MCU_ID_PERFORM_RESET        0x07u /*!< Mcu_PerformReset() api service id */
#define MCU_ID_SET_MODE             0x08u /*!< Mcu_SetMode() api service id */
#define MCU_ID_GET_VERSION_INFO     0x09u /*!< Mcu_GetVersionInfo() api service id */
#define MCU_ID_GET_RAM_STATE        0x0Au /*!< Mcu_GetRamState() api service id */
/**
 * @} */

/**
 * @defgroup MCU_Error_Type MCU Development Error Types
 *
 * @{ */
#define MCU_E_PARAM_CONFIG          0x0Au /*!< API service called with wrong parameter */
#define MCU_E_PARAM_CLOCK           0x0Bu /*!< API service called with wrong parameter */
#define MCU_E_PARAM_MODE            0x0Cu /*!< API service called with wrong parameter */
#define MCU_E_PARAM_RAMSECTION      0x0Du /*!< API service called with wrong parameter */
#define MCU_E_PLL_NOT_LOCKED        0x0Eu /*!< API service called with wrong parameter */
#define MCU_E_UNINIT                0x0Fu /*!< API service called with wrong parameter */
#define MCU_E_PARAM_POINTER         0x10u /*!< API service called with wrong parameter */
#define MCU_E_INIT_FAILED           0x11u /*!< API service called with wrong parameter */
/**
 * @} */

/**
 * @defgroup MCU_STATIC MCU static define for testing purposes
 *
 * @{ */
#ifndef UTEST
#define MCU_STATIC static /*!< Add static when no testing */
#else
#define MCU_STATIC /*!< remove static for testing purposes */
#endif
/**
 * @} */

/**
 * @defgroup MCU_PLL_SOURCE MCU available clock sources for PLL (HSI and HSE)
 *
 * @{ */
#define MCU_PLL_SOURCE_MASK          0x03u       /*!< Mask for PLL Source bits                   */
#define MCU_PLL_SOURCE_NONE          0x00000000u /*!< No clock source selected as source for PLL */
#define MCU_PLL_SOURCE_NOT_VALID     0x00000001u /*!< Avoid this value. Reserved                 */
#define MCU_PLL_SOURCE_HSI           0x00000002u /*!< HSI as source for PLL (RC internal)        */
#define MCU_PLL_SOURCE_HSE           0x00000003u /*!< HSE as source for PLL (XTAL external)      */
/**
 * @} */

/**
 * @defgroup MCU_PLL_OUTPUT MCU available clock outputs for PLL (P, Q and R)
 *
 * @{ */
#define MCU_PLL_OUTPUT_PLLP          0u /*!< PLL P as clock output from PLL */
#define MCU_PLL_OUTPUT_PLLQ          1u /*!< PLL Q as clock output from PLL */
#define MCU_PLL_OUTPUT_PLLR          2u /*!< PLL R as clock output from PLL */
/**
 * @} */

/**
 * @defgroup MCU_PLLM_DIV MCU PLLM Clock Divider possible values
 *
 * @{ */
#define MCU_PLLM_OFFSET              4u                                 /*!< Bit where starts PLLM */
#define MCU_PLLM_MASK                0x70u                              /*!< Mask for PLLM         */
#define MCU_PLLM_DIV1                ( 0x00000000u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 1     */
#define MCU_PLLM_DIV2                ( 0x00000001u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 2     */
#define MCU_PLLM_DIV3                ( 0x00000002u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 3     */
#define MCU_PLLM_DIV4                ( 0x00000003u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 4     */
#define MCU_PLLM_DIV5                ( 0x00000004u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 5     */
#define MCU_PLLM_DIV6                ( 0x00000005u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 6     */
#define MCU_PLLM_DIV7                ( 0x00000006u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 7     */
#define MCU_PLLM_DIV8                ( 0x00000007u << MCU_PLLM_OFFSET ) /*!< PLL M divide by 8     */
/**
 * @} */

/**
 * @defgroup MCU_PLLN_Clock_Multiplicator MCU PLLN Clock Multiplicator range values
 *
 * @{ */
#define MCU_PLLN_OFFSET              8u      /*!< Bit where starts PLLN             */
#define MCU_PLLN_MASK                0x7F00u /*!< Bits used by PLLN value           */
#define MCU_PLLN_MIN_VALUE           8u      /*!< PLLN Multiplcator min value is 8  */
#define MCU_PLLN_MAX_VALUE           86u     /*!< PLLN Multiplcator max value is 86 */
/**
 * @} */

/**
 * @defgroup MCU_PLLP_Clock_Divider MCU PLLP Clock Divider possible values
 *
 * @{ */
#define MCU_PLLP_OFFSET              17u                         /*!< Bit where starts PLLP */
#define MCU_PLLP_MASK                0x003E0000u                 /*!< PLLP mask             */
#define MCU_PLLP_DIV2                ( 1UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 2     */
#define MCU_PLLP_DIV3                ( 2UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 3     */
#define MCU_PLLP_DIV4                ( 3UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 4     */
#define MCU_PLLP_DIV5                ( 4UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 5     */
#define MCU_PLLP_DIV6                ( 5UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 6     */
#define MCU_PLLP_DIV7                ( 6UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 7     */
#define MCU_PLLP_DIV8                ( 7UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 8     */
#define MCU_PLLP_DIV9                ( 8UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 9     */
#define MCU_PLLP_DIV10               ( 9UL << MCU_PLLP_OFFSET )  /*!< PLL P divide by 10    */
#define MCU_PLLP_DIV11               ( 10UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 11    */
#define MCU_PLLP_DIV12               ( 11UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 12    */
#define MCU_PLLP_DIV13               ( 12UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 13    */
#define MCU_PLLP_DIV14               ( 13UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 14    */
#define MCU_PLLP_DIV15               ( 14UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 15    */
#define MCU_PLLP_DIV16               ( 15UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 16    */
#define MCU_PLLP_DIV17               ( 16UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 17    */
#define MCU_PLLP_DIV18               ( 17UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 18    */
#define MCU_PLLP_DIV19               ( 18UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 19    */
#define MCU_PLLP_DIV20               ( 19UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 20    */
#define MCU_PLLP_DIV21               ( 20UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 21    */
#define MCU_PLLP_DIV22               ( 21UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 22    */
#define MCU_PLLP_DIV23               ( 22UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 23    */
#define MCU_PLLP_DIV24               ( 23UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 24    */
#define MCU_PLLP_DIV25               ( 24UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 25    */
#define MCU_PLLP_DIV26               ( 25UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 26    */
#define MCU_PLLP_DIV27               ( 26UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 27    */
#define MCU_PLLP_DIV28               ( 27UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 28    */
#define MCU_PLLP_DIV29               ( 28UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 29    */
#define MCU_PLLP_DIV30               ( 29UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 30    */
#define MCU_PLLP_DIV31               ( 30UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 31    */
#define MCU_PLLP_DIV32               ( 31UL << MCU_PLLP_OFFSET ) /*!< PLL P divide by 32    */
/**
 * @} */

/**
 * @defgroup MCU_PLLQ_Clock_Divider MCU PLLQ Clock Divider possible values
 *
 * @{ */
#define MCU_PLLQ_OFFSET              25u                        /*!< Bit where starts PLLQ */
#define MCU_PLLQ_MASK                0x0E000000u                /*!< PLLQ mask             */
#define MCU_PLLQ_DIV2                ( 1UL << MCU_PLLQ_OFFSET ) /*!< PLL Q divide by 2 */
#define MCU_PLLQ_DIV3                ( 2UL << MCU_PLLQ_OFFSET ) /*!< PLL Q divide by 3 */
#define MCU_PLLQ_DIV4                ( 3UL << MCU_PLLQ_OFFSET ) /*!< PLL Q divide by 4 */
#define MCU_PLLQ_DIV5                ( 4UL << MCU_PLLQ_OFFSET ) /*!< PLL Q divide by 5 */
#define MCU_PLLQ_DIV6                ( 5UL << MCU_PLLQ_OFFSET ) /*!< PLL Q divide by 6 */
#define MCU_PLLQ_DIV7                ( 6UL << MCU_PLLQ_OFFSET ) /*!< PLL Q divide by 7 */
#define MCU_PLLQ_DIV8                ( 7UL << MCU_PLLQ_OFFSET ) /*!< PLL Q divide by 8 */
/**
 * @} */

/**
 * @defgroup MCU_PLLR_Clock_Divider MCU PLLR Clock Divider possible values
 *
 * @{ */
#define MCU_PLLR_OFFSET              9u                         /*!< Bit where starts PLLR */
#define MCU_PLLR_MASK                0xE0000000u                /*!< PLLR mask             */
#define MCU_PLLR_DIV2                ( 1UL << MCU_PLLR_OFFSET ) /*!< PLL R divide by 2 */
#define MCU_PLLR_DIV3                ( 2UL << MCU_PLLR_OFFSET ) /*!< PLL R divide by 3 */
#define MCU_PLLR_DIV4                ( 3UL << MCU_PLLR_OFFSET ) /*!< PLL R divide by 4 */
#define MCU_PLLR_DIV5                ( 4UL << MCU_PLLR_OFFSET ) /*!< PLL R divide by 5 */
#define MCU_PLLR_DIV6                ( 5UL << MCU_PLLR_OFFSET ) /*!< PLL R divide by 6 */
#define MCU_PLLR_DIV7                ( 6UL << MCU_PLLR_OFFSET ) /*!< PLL R divide by 7 */
#define MCU_PLLR_DIV8                ( 7UL << MCU_PLLR_OFFSET ) /*!< PLL R divide by 8 */
/**
 * @} */

/**
 * @defgroup MCU_Oscillator_Type MCU Oscillator to be configured
 *
 * @{ */
#define MCU_OSCILLATORTYPE_NONE      0u /*!< Default value       */
#define MCU_OSCILLATORTYPE_HSE       1u /*!< High-speed External */
#define MCU_OSCILLATORTYPE_HSI       2u /*!< High-speed Internal */
#define MCU_OSCILLATORTYPE_LSE       3u /*!< Low-speed External  */
#define MCU_OSCILLATORTYPE_LSI       4u /*!< Low-speed Internal  */
#define MCU_OSCILLATORTYPE_HSI48     5u /*!< 48MHz Internal RC   */
/**
 * @} */

/**
 * @defgroup MCU_HSE_State MCU HSE possible states
 *
 * @{ */
#define MCU_HSE_OFF                  0u /*!< HSE Disabled                        */
#define MCU_HSE_ON                   1u /*!< HSE Enabled                         */
#define MCU_HSE_BYPASS               2u /*!< External clock source for HSE clock */
/**
 * @} */

/**
 * @defgroup MCU_LSE_State MCU LSE possible states
 *
 * @{ */
#define MCU_LSE_OFF                  0u /*!< LSE Disabled                        */
#define MCU_LSE_ON                   1u /*!< LSE Enabled                         */
#define MCU_LSE_BYPASS               2u /*!< External clock source for LSE clock */
/**
 * @} */

/**
 * @defgroup MCU_HSI_State MCU HSI possible states
 *
 * @{ */
#define MCU_HSI_OFF                  0u  /*!< HSI Disabled                   */
#define MCU_HSI_ON                   1u  /*!< HSI Enabled                    */
#define MCU_HSICALIBRATION_DEFAULT   64u /*!< HSI calibration trimming value */
/**
 * @} */

/**
 * @defgroup MCU_LSI_State MCU LSI possible states
 *
 * @{ */
#define MCU_LSI_OFF                  0u /*!< LSI Disabled */
#define MCU_LSI_ON                   1u /*!< LSI Enabled  */
/**
 * @} */

/**
 * @defgroup MCU_HSI48_State MCU HSI48 possible states
 *
 * @{ */
#define MCU_HSI48_OFF                0u /*!< HSI48 Disabled */
#define MCU_HSI48_ON                 1u /*!< HSI48 Enabled  */
/**
 * @} */

/**
 * @defgroup MCU_HSI_DIVIDER MCU HSI possible divider values
 *
 * @{ */
#define MCU_HSI_DIV_OFFSET           11u                           /*!< HSI div register offset     */
#define MCU_HSI_DIV_MASK             0x3800u                       /*!< HSI div mask                */
#define MCU_HSI_DIV1                 ( 0UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock not divided    */
#define MCU_HSI_DIV2                 ( 1UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock divided by 2   */
#define MCU_HSI_DIV4                 ( 2UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock divided by 4   */
#define MCU_HSI_DIV8                 ( 3UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock divided by 8   */
#define MCU_HSI_DIV16                ( 4UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock divided by 16  */
#define MCU_HSI_DIV32                ( 5UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock divided by 32  */
#define MCU_HSI_DIV64                ( 6UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock divided by 64  */
#define MCU_HSI_DIV128               ( 7UL << MCU_HSI_DIV_OFFSET ) /*!< HSI clock divided by 128 */
/**
 * @} */

/**
 * @defgroup MCU_HSI_Calibration_Value MCU HSI max and min calibration values
 *
 * @{ */
#define MCU_HSICALIBRATION_OFFSET    8u      /*!< HSI calibration min value */
#define MCU_HSICALIBRATION_MASK      0x7F00u /*!< HSI calibration min value */
#define MCU_HSICALIBRATION_MIN_VALUE 0u      /*!< HSI calibration min value */
#define MCU_HSICALIBRATION_MAX_VALUE 127u    /*!< HSI calibration max value */
/**
 * @} */

/**
 * @defgroup MCU_SYSCLOCK_Source MCU system clock possible sources
 *
 * @{ */
#define MCU_SYSCLKSOURCE_MASK        0x07u                             /*!< Mask for SYS CLOCK SOURCE   */
#define MCU_SYSCLKSOURCE_OFFSET      0u                                /*!< Offset for SYS CLOCK SOURCE */
#define MCU_SYSCLKSOURCE_HSI         ( 0u << MCU_SYSCLKSOURCE_OFFSET ) /*!< HSI as system clock         */
#define MCU_SYSCLKSOURCE_HSE         ( 1u << MCU_SYSCLKSOURCE_OFFSET ) /*!< HSE as system clock         */
#define MCU_SYSCLKSOURCE_PLLCLK      ( 2u << MCU_SYSCLKSOURCE_OFFSET ) /*!< PLL output as system clock  */
#define MCU_SYSCLKSOURCE_LSI         ( 3u << MCU_SYSCLKSOURCE_OFFSET ) /*!< LSI as system clock         */
#define MCU_SYSCLKSOURCE_LSE         ( 4u << MCU_SYSCLKSOURCE_OFFSET ) /*!< LSE as system clock         */
/**
 * @} */

/**
 * @defgroup MCU_Clock_Type MCU clock type to be configured
 *
 * @{ */
#define MCU_CLOCKTYPE_SYSCLK         0u /*!< Configure system clock */
#define MCU_CLOCKTYPE_HCLK           1u /*!< Configure AHB          */
#define MCU_CLOCKTYPE_PCLK1          2u /*!< Configure APB1         */
/**
 * @} */

/**
 * @defgroup MCU_AHB_Clock_Divider MCU AHB clock divider possible values
 *
 * @{ */
#define MCU_AHB_DIV_OFFSET           8u                             /*!< Bit where starts AHB div */
#define MCU_AHB_DIV_MASK             0xF00u                         /*!< Mask for AHB div */
#define MCU_AHB_DIV1                 ( 7UL << MCU_AHB_DIV_OFFSET )  /*!< AHB Clock not divided    */
#define MCU_AHB_DIV2                 ( 8UL << MCU_AHB_DIV_OFFSET )  /*!< AHB Clock divided by 2   */
#define MCU_AHB_DIV4                 ( 9UL << MCU_AHB_DIV_OFFSET )  /*!< AHB Clock divided by 4   */
#define MCU_AHB_DIV8                 ( 10UL << MCU_AHB_DIV_OFFSET ) /*!< AHB Clock divided by 8   */
#define MCU_AHB_DIV16                ( 11UL << MCU_AHB_DIV_OFFSET ) /*!< AHB Clock divided by 16  */
#define MCU_AHB_DIV64                ( 12UL << MCU_AHB_DIV_OFFSET ) /*!< AHB Clock divided by 64  */
#define MCU_AHB_DIV128               ( 13UL << MCU_AHB_DIV_OFFSET ) /*!< AHB Clock divided by 128 */
#define MCU_AHB_DIV256               ( 14UL << MCU_AHB_DIV_OFFSET ) /*!< AHB Clock divided by 256 */
#define MCU_AHB_DIV512               ( 15UL << MCU_AHB_DIV_OFFSET ) /*!< AHB Clock divided by 256 */
/**
 * @} */

/**
 * @defgroup MCU_APB1_Clock_Divider MCU APB1 clock divider possible values
 *
 * @{ */
#define MCU_APB1_DIV_OFFSET          12u                            /*!< Bit where starts APB1 div */
#define MCU_APB1_DIV_MASK            0x7000u                        /*!< Mask for APB1 div */
#define MCU_APB1_DIV1                ( 3UL << MCU_APB1_DIV_OFFSET ) /*!< APB1 Clock not divided    */
#define MCU_APB1_DIV2                ( 4UL << MCU_APB1_DIV_OFFSET ) /*!< APB1 Clock divided by 2   */
#define MCU_APB1_DIV4                ( 5UL << MCU_APB1_DIV_OFFSET ) /*!< APB1 Clock divided by 4   */
#define MCU_APB1_DIV8                ( 6UL << MCU_APB1_DIV_OFFSET ) /*!< APB1 Clock divided by 8   */
#define MCU_APB1_DIV16               ( 7UL << MCU_APB1_DIV_OFFSET ) /*!< APB1 Clock divided by 16  */
/**
 * @} */

/**
 * @defgroup MCU_PLL_STATUS MCU PLL status possible values
 *
 * @{ */
#define MCU_PLL_STATE_DISABLED       0u /*!< PLL will bedisabled  */
#define MCU_PLL_STATE_ENABLED        1u /*!< PLL will enabled     */
/**
 * @} */

/**
 * @brief   **Status value returned by the function Mcu_GetPllStatus of the MCU module**
 *
 * @reqs    SWS_Mcu_00250
 */
typedef enum _Mcu_PllStatusType
{
    MCU_PLL_LOCKED = 0x00,   /*!< The PLL is locked         */
    MCU_PLL_UNLOCKED,        /*!< The PLL is unlocked       */
    MCU_PLL_STATUS_UNDEFINED /*!< The PLL Status is unknown */
} Mcu_PllStatusType;

/**
 * @brief   **ID for a clock setting**
 *
 * The range is dependent on the number of different clock settings provided in the
 * configuration structure
 *
 * @reqs    SWS_Mcu_00251
 */
typedef uint32 Mcu_ClockType;

/**
 * @brief   **Reset types**
 *
 * @reqs    SWS_Mcu_00252
 */
typedef enum _Mcu_ResetType
{
    MCU_POWER_ON_RESET = 0x00, /*!< Power On Reset                */
    MCU_WATCHDOG_RESET,        /*!< Internal Watchdog Timer Reset */
    MCU_SW_RESET,              /*!< Software Reset                */
    MCU_RESET_UNDEFINED        /*!< Reset is undefined            */
} Mcu_ResetType;

/**
 * @brief   **Specifies the reset reason in raw register format read from reset status register**
 *
 * @reqs    SWS_Mcu_00253
 */
typedef uint32 Mcu_RawResetType;

/**
 * @brief   **Specifies the identification (ID) for a MCU mode**
 *
 * @reqs    SWS_Mcu_00254
 */
typedef uint32 Mcu_ModeType;

/**
 * @brief   **Specifies the identification (ID) for a RAM section**
 *
 * @reqs    SWS_Mcu_00255
 */
typedef uint32 Mcu_RamSectionType;

/**
 * @brief   **RAM state (valid or invalid)**
 *
 * Ram State data type returned by the function Mcu_GetRamState of the Mcu module
 *
 * @reqs    SWS_Mcu_00256
 */
typedef enum _Mcu_RamStateType
{
    MCU_RAMSTATE_INVALID = 0x00, /*!< Ram content is not valid or unknown */
    MCU_RAMSTATE_VALID,          /*!< Ram content is valid                */
} Mcu_RamStateType;

/**
 * @brief   **Hardware unit status datatype**
 *
 * Data type which describes the status of MCU Module (initialized or not-initialized)
 */
typedef enum _Mcu_StatusType
{
    MCU_STATE_UNINIT = 0x00, /*!< MCU Module not initialized         */
    MCU_STATE_INIT,          /*!< MCU Module has been initialized    */
} Mcu_StatusType;

/**
 * @brief **Pll Config unit structure**
 *
 * This structure contains Pll configuration parameters
 */
typedef struct _Mcu_PllConfigType
{
    uint32 PllSource; /*!< Clock source of PLL                         */
    uint32 PllState;  /*!< Indicate if PLL must be enabled or disabled */
    uint32 PllM;      /*!< PLL M Clock Divider                         */
    uint32 PLLN;      /*!< PLL N Clock Multiplicator                   */
    uint32 PllP;      /*!< PLL P Clock Divider                         */
    uint32 PllQ;      /*!< PLL Q Clock Divider                         */
    uint32 PllR;      /*!< PLL R Clock Divider                         */
} Mcu_PllConfigType;

/**
 * @brief **Osc Config unit structure**
 *
 * This structure contains Oscillators configuration parameters
 */
typedef struct _Mcu_OscConfigType
{
    uint32 OscillatorType;      /*!< Oscillator to configure      */
    uint32 HSEState;            /*!< High-speed external state    */
    uint32 LSEState;            /*!< Low-speed external state     */
    uint32 HSIState;            /*!< High-speed internal state    */
    uint32 HSIDivider;          /*!< High-speed internal divider  */
    uint32 HSICalibrationValue; /*!< High-speed calibration value */
    uint32 LSIState;            /*!< Low-speed internal state     */
    uint32 HSI48State;          /*!< High-speed internal state    */
    Mcu_PllConfigType PLL;      /*!< PLL configuration struct     */
} Mcu_OscConfigType;

/**
 * @brief **Clk Config unit structure**
 *
 * This structure contains System Clock configuration parameters
 */
typedef struct _Mcu_SysClkConfigType
{
    uint32 SysClockSource;   /*!< Clock source used as system clock */
    uint32 AHBClockDivider;  /*!< AHB (HCLK) divider                */
    uint32 APB1ClockDivider; /*!< APB1 (PCLK1) divider              */
} Mcu_SysClkConfigType;

/**
 * @brief **McuClk Config unit structure**
 *
 * This structure contains general Clock configuration parameters
 */
typedef struct _Mcu_ClkConfigType
{
    Mcu_OscConfigType OscConfig;    /*!< Specifies the MCU Oscillators configuration parameters   */
    Mcu_SysClkConfigType ClkConfig; /*!< Specifies the MCU Clock configuration parameters      */
} Mcu_ClkConfigType;

/**
 * @brief **Hardware dependent structure**
 *
 * A pointer to this type is provided to MCU initialization routines for configuration
 *
 * @reqs SWS_Mcu_00249, SWS_Mcu_00017, SWS_Mcu_00019, SWS_Mcu_00020, SWS_Mcu_00021
 */
typedef struct _Mcu_ConfigType
{
    Mcu_ClockType ClockSetting;    /*!< Specifies the identification (ID) for a clock setting    */
    Mcu_ModeType McuMode;          /*!< Specifies the identification (ID) for a MCU mode         */
    Mcu_RamSectionType RamSection; /*!< Specifies the identification (ID) for a RAM section      */
    Mcu_PllStatusType PllStatus;   /*!< Stores the status of PLL (locked, unlocked or undefined) */
    Mcu_ClkConfigType ClockConfig; /*!< Specifies clock setting related parameters               */
} Mcu_ConfigType;

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware
 * unit pointers to controller structures.
 */
typedef struct _Mcu_HwUnit
{
    Mcu_ConfigType *Config;     /*!< Pointer to the configuration structure */
    Mcu_StatusType HwUnitState; /*!< MCU hardware unit state                */
} Mcu_HwUnit;

#endif