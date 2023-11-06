/**
 * @file    Spi.h
 * @brief   **Spi Driver**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 * The Spi module provides servic ...
 * ...
 */
#ifndef SPI_H__
#define SPI_H__

#include "Spi_Cfg.h"

/**
 * @defgroup Spi_Ids Spi Id number for module and each API
 *
 * @{ */
#define SPI_ID_INIT               0x00u /*!< Spi_Init() api service id */
/**
 * @} */

/**
 * @defgroup Spi_Error_Typse Spi Developtmnet Error Types
 *
 * @{ */
#define SPI_E_PARAM_CHANNEL       0x0Au /*!< API service called with wrong channel  */
#define SPI_E_PARAM_JOB           0x0Bu /*!< API service called with wrong job */
#define SPI_E_PARAM_SEQ           0x0Cu /*!< API service called with wrong sequence */
#define SPI_E_PARAM_LENGTH        0x0Du /*!< API service called with wrong length for EB */
#define SPI_E_PARAM_UNIT          0x0Eu /*!< API service called with wrong hardware unit */
#define SPI_E_PARAM_POINTER       0x10u /*!< APIs called with an unexpected value for the pointer */
#define SPI_E_UNINIT              0x1Au /*!< API service used without module initialization */
#define SPI_E_ALREADY_INITIALIZED 0x4Au /*!< API SPI_Init service called while the SPI driver has been already initialized*/
/**
 * @} */

void Spi_Init( const Spi_ConfigType *Config );


#endif /* SPI_H__ */
