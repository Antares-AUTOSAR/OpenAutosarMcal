/**
 * @file    Adc_Cfg.h
 * @brief   **Adc Driver**
 * @author  Naim Leon
 *
 * Configuration for ADC driver, this file as per AUTOSAR indication is not application dependant
 * and shall be generated by a configuration tool. for the moment the files shall be written
 * manually by the user according its application. Also the user is responsible for setting the
 * parameter in the right way.
 */
#ifndef ADC_CFG_H__
#define ADC_CFG_H__

#include "Adc_Types.h"

/**
 * @defgroup ADC_SWC_Ids ADC software Ids
 *
 * {@ */
#define ADC_MODULE_ID                   5u /*!< ADC Module ID */
#define ADC_INSTANCE_ID                 5u /*!< ADC Instance ID */
#define ADC_VENDOR_ID                   0u /*!< ADC Module Vendor ID */
/**
 * @} */

/**
 * @defgroup ADC_SWC_Ids ADC software version
 *
 * {@ */
#define ADC_SW_MAJOR_VERSION            0u /*!< ADC Module Major Version */
#define ADC_SW_MINOR_VERSION            0u /*!< ADC Module Minor Version */
#define ADC_SW_PATCH_VERSION            0u /*!< ADC Module Patch Version */
/**
 * @} */

/**
 * @brief Adds / removes the service Adc_DeInit() from the code.
 * @typedef EcucBooleanParamDef
 */
#define ADC_DE_INIT_API                 STD_ON

/**
 * @brief Adds / removes the services Adc_StartGroupConversion() and Adc_StopGroupConversion() from
 *          the code.
 * @typedef EcucBooleanParamDef
 */
#define ADC_ENABLE_START_STOP_GROUP_API STD_ON

/**
 * @brief Adds / removes the service Adc_ReadGroup() and from the code.
 * @typedef EcucBooleanParamDef
 */
#define ADC_READ_GROUP_API              STD_ON

/**
 * @brief Adds / removes the services Adc_EnableHardwareTrigger() and Adc_DisableHardwareTrigger()
 *          from the code
 * @typedef EcucBooleanParamDef
 */
#define ADC_HW_TRIGGER_API              STD_ON

/**
 * @brief Adds / removes the services Adc_GetVersionInfo() from the code
 * @typedef EcucBooleanParamDef
 */
#define ADC_VERSION_INFO_API            STD_ON

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define ADC_DEV_ERROR_DETECT            STD_ON

extern const Adc_ConfigType AdcConfig;

#endif /* CAN_CFG_H__ */
