/**
 * @file    Can_Cfg.h
 * @brief   **Can Driver**
 * @author  Diego Perez
 *
 * Configuration for CAN driver, this file as per AUTOSAR indication is not application dependant
 * and shall be generated by a configuration tool. for the moment the files shall be written manually
 * by the user according its application. Also the user is responsible for setting the paramter in
 * the right way.
 */
#ifndef CAN_CFG_H__
#define CAN_CFG_H__

#include "Can_Types.h"

/**
 * @defgroup CAN_SWC_Ids CAN software version and Ids
 *
 * {@ */
#define CAN_MODULE_ID                 0u /*!< Can Module ID */
#define CAN_INSTANCE_ID               0u /*!< Can Instance ID */
#define CAN_VENDOR_ID                 0u /*!< Can Module Vendor ID */
/**
 * @} */

/**
 * @defgroup CAN_SWC_Ids CAN software version and Ids
 *
 * {@ */
#define CAN_SW_MAJOR_VERSION          0u /*!< Can Module Major Version */
#define CAN_SW_MINOR_VERSION          0u /*!< Can Module Minor Version */
#define CAN_SW_PATCH_VERSION          0u /*!< Can Module Patch Version */
/**
 * @} */

/**
 * @brief Specifies the number of controller to mange by the driver.
 * @typedef EcucIntegerParamDef
 */
#define CAN_NUMBER_OF_CONTROLLERS     2

/**
 * @defgroup Controller_IDs Can controllers
 *
 * Specifies the controller IDs starting from zero and up to CAN_NUMBER_OF_CONTROLLERS - 1
 *
 * @typedef EcucIntegerParamDef
 *
 * @{ */
#define CAN_CONTROLLER_0              0 /*!< Controller zero */
#define CAN_CONTROLLER_1              1 /*!< Controller one  */
/**
 * @} */

/**
 * @brief Specifies the number of buadrate configuration for controller 0
 * @typedef EcucIntegerParamDef
 */
#define CAN_NUMBER_OF_BAUDRATES_CTRL0 2
#define CAN_BAUDRATE_CTRL0_100K       0
#define CAN_BAUDRATE_CTRL0_500K       1

/**
 * @brief Specifies the number of buadrate configuration for controller 1
 * @typedef EcucIntegerParamDef
 */
#define CAN_NUMBER_OF_BAUDRATES_CTRL1 2
#define CAN_BAUDRATE_CTRL1_100K       0
#define CAN_BAUDRATE_CTRL1_500K       1

/**
 * @brief Specifies the number of hardware objects to mange by each controller.
 * @typedef EcucIntegerParamDef
 */
#define CAN_NUMBER_OF_HOHS            3

/**
 * @defgroup HOHs_IDs Can hardware object
 *
 * Specifies the transmit hardware objects an its corresponding controller, where the most significant
 * nibble represent the controller ID and the least significant nibble represent the HOH ID.
 *
 * @typedef EcucIntegerParamDef
 *
 * @{ */
#define CAN_HTH_0_CTRL_0              0
#define CAN_HRH_0_CTRL_0              1
#define CAN_HTH_0_CTRL_1              2
/**
 * @} */

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define CAN_DEV_ERROR_DETECT          STD_ON

/**
 * @brief Enables/Disables the Global Time APIs used when hardware timestamping is supported.
 * @typedef EcucBooleanParamDef
 */
#define CAN_GLOBAL_TIME_SUPPORT       STD_ON

/**
 * @brief Specifies if the Can_SetBaudrate API shall be supported.
 * @typedef EcucBooleanParamDef
 */
#define CAN_SET_BAUDRATE_API          STD_ON

/**
 * @brief Specifies if the Can_GetVersionInfo API shall be supported.
 * @typedef EcucBooleanParamDef
 */
#define CAN_VERSION_INFO_API          STD_ON

extern const Can_ConfigType CanConfig;

#endif /* CAN_CFG_H__ */
