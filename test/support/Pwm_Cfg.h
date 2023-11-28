/**
 * @file    Pwm_Cfg.h
 * @brief   **Pwm Driver Configuration Header**
 * @author  Jazmin Melendrez
 *
 * Configuration for the PWM driver. This file, as per AUTOSAR guidelines, is not
 * application-dependent and should be generated by a configuration tool. For the moment,
 * the files shall be written manually by the user according to their application. Also,
 * the user is responsible for setting the parameter in the right way.
 */
#ifndef Pwm_CFG_H__
#define Pwm_CFG_H__

#include "Pwm_Types.h"

/**
 * @defgroup PWM_SWC_Ids PWM software version and Ids
 *
 * {@ */
#define PWM_MODULE_ID              0u /*!< Pwm Module ID */
#define PWM_INSTANCE_ID            0u /*!< Pwm Instance ID */
#define PWM_VENDOR_ID              0u /*!< Pwm Module Vendor ID */
/**
 * @} */

/**
 * @defgroup PWM_SWC_Ids PWM software version and Ids
 *
 * {@ */
#define PWM_SW_MAJOR_VERSION       0u /*!< PWM Module Major Version */
#define PWM_SW_MINOR_VERSION       0u /*!< Pwm Module Minor Version */
#define PWM_SW_PATCH_VERSION       0u /*!< Pwm Module Patch Version */
/**
 * @} */

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define PWM_DEV_ERROR_DETECT       STD_ON

/**
 * @brief Adds / removes the service Pwm_DeInit() from the code.
 * @typedef EcucBooleanParamDef
 */
#define PWM_DE_INIT_API            STD_ON

/**
 * @brief Adds / removes the service Pwm_SetDutyCycle() from the code.
 * @typedef EcucBooleanParamDef
 */
#define PWM_SET_DUTY_CYCLE         STD_ON

/**
 * @brief Adds / removes the service Pwm_SetPeriodAndDuty() from the code.
 * @typedef EcucBooleanParamDef
 */
#define PWM_SET_PERIOD_AND_DUTY    STD_ON

/**
 * @brief Adds / removes the service Pwm_SetOutputToIdle() from the code.
 * @typedef EcucBooleanParamDef
 */
#define PWM_SET_OUTPUT_TO_IDLE     STD_ON

/**
 * @brief Adds / removes the service Pwm_GetOutputState() from the code.
 * @typedef EcucBooleanParamDef
 */
#define PWM_GET_OUTPUT_STATE       STD_ON

/**
 * @brief Switch to indicate that the notifications are supported
 * @typedef EcucBooleanParamDef
 */
#define PWM_NOTIFICATION_SUPPORTED STD_ON

/**
 * @brief Specifies if the Pwm_GetVersionInfo API shall be supported.
 * @typedef EcucBooleanParamDef
 */
#define PWM_VERSION_INFO_API       STD_ON

extern const Pwm_ConfigType PwmConfig;

#endif /* PWM_CFG_H__ */