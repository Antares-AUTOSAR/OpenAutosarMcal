/**
 * @file    Port_Cfg.h
 * @brief   **Port driver configuration file**
 * @author  Daniel Byuerly, Diego Perez
 *
 * Configuration for Port driver, this file as per AUTOSAR indication is not application dependant
 * and shall be generated by a configuration tool. for the moent the files shall be written manually
 * by the user according its application. Also the user is responsible for setting the paramter in
 * the right way
 */
#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#include "Port_Types.h"

/**
 * @defgroup PORT_SWC_Ids PORT software version and Ids
 *
 * {@ */
#define PORT_MODULE_ID             0u /*!< Port Module ID */
#define PORT_INSTANCE_ID           0u /*!< Port Instance ID */
#define PORT_VENDOR_ID             0u /*!< Port Module Vendor ID */
/**
 * @} */

/**
 * @defgroup PORT_SWC_Ids PORT software version and Ids
 *
 * {@ */
#define PORT_SW_MAJOR_VERSION      0u /*!< Port Module Major Version */
#define PORT_SW_MINOR_VERSION      0u /*!< Port Module Minor Version */
#define PORT_SW_PATCH_VERSION      0u /*!< Port Module Patch Version */
/**
 * @} */

/**
 * @defgroup    PORTS_SETTINGS  This are option to enable or disable some driver interfaces
 *              user only needs to define as STD_ON or STD_OFF
 * @{ */
#define PORT_SET_PIN_DIRECTION_API STD_ON /**< Enable or disable the set pin direction API */
#define PORT_SET_PIN_MODE_API      STD_ON /**< Enable or disable the set pin mode API */
#define PORT_VERSION_INFO_API      STD_ON /**< Enable or disable the version info API */
/**
 * @} */

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define PORT_DEV_ERROR_DETECT      STD_ON

/**
 * @brief   **Number of port settings to configure**
 *
 * Number of ports to configure, this is the number of ports that will be configured by the driver
 * and shall be set by the user according to the number of elements defined in Port_Config array
 * shall be greater than zero
 */
#define PORT_PIN_NUMBER_OF_PORTS   2

/**
 * @defgroup PORT_pins_in_use  Port IDs in use by the driver
 * @{ */
#define PORT_PIN_LCD_CS            0 /**< Port ID for LCD chip select */
#define PORT_PIN_LCD_RS            1 /**< Port ID for LCD register select */
/**
 * @} */

/*external reference to Port_Config array*/
extern const Port_ConfigType PortConfig;

#endif /* PORT_CFG_H_ */