/**
 * @file    Gpt_Cfg.h
 * @brief   **GPT driver configuration file**
 * @author  Rodrigo Lopez
 *
 * Configuration for GPT driver, this file as per AUTOSAR indication is not application dependant
 * and shall be generated by a configuration tool. for the moment the files shall be written manually
 * by the user according its application. Also the user is responsible for setting the paramter in
 * the right way.
 */
#ifndef GPT_CFG_H_
#define GPT_CFG_H_

#include "Gpt_Types.h"

/**
 * @brief   **Number of channels to configure**
 *
 * Number of channels to configure, this is the number of channels that will be configured by the
 * driver and shall be set by the user.
 */
#define GPT_NUMBER_OF_CHANNELS              2u

/**
 * @defgroup   Test values of the two different possible operation modes of the GPT channels
 */
#define TEST_GPT_CH_MODE_CONTINUOUS         0  /**< Channel on Continuous mode */
#define TEST_GPT_CH_MODE_ONESHOT            1u /**< Channel on One-Pulse mode */
/**
 * @} */

/**
 * @defgroup    GPT_SETTINGS  These are options to enable or disable some driver interfaces,
 *              the user only needs to define as STD_ON or STD_OFF
 * @{ */
#define GPT_DEINIT_API                      STD_ON /**< Enable or disable the Deinit API */
#define GPT_TIME_ELAPSED_API                STD_ON /**< Enable or disable the Time Elapsed API */
#define GPT_TIME_REMAINING_API              STD_ON /**< Enable or disable the Time Remaining API */
#define GPT_VERSION_INFO_API                STD_ON /**< Enable or disable the Version Info API */
#define GPT_ENABLE_DISABLE_NOTIFICATION_API STD_ON /**< Enable or disable the Enable/Disable Notification API */
/**
 * @} */

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define GPT_DEV_ERROR_DETECT                STD_ON

/**
  * @defgroup GPT-ID to get the version information of this module.
  @{ */
#define GPT_VENDOR_ID                       (uint16)1000u /*!< Id for the company in the AUTOSAR*/
#define GPT_MODULE_ID                       (uint16)120u  /*!< GPT Module Id */
#define GPT_INSTANCE_ID                     (uint16)0u    /*!< GPT Instance ID */
#define GPT_SW_MAJOR_VERSION                (uint8)1u     /*!< GPT Module Major Version */
#define GPT_SW_MINOR_VERSION                (uint8)0u     /*!< GPT Module Major Version */
#define GPT_SW_PATCH_VERSION                (uint8)0u     /*!< GPT Module Major Version */
/**
 * @} */

/*External reference to Gpt_Config array*/
extern const Gpt_ConfigType GptConfig;

#endif /* GPT_CFG_H_ */