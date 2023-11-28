/**
 * @file    CanIf_Lcfg.c
 * @brief   **Can Interface cnfiguration file**
 * @author  Diego Perez
 *
 * This file contains the configuration structures for the CAN driver, this file as per AUTOSAR indication
 * is not application dependant and shall be generated by a configuration tool. for the moment the files
 * shall be written manually by the user according its application. Also the user is responsible for setting
 * the paramter in the right way.
 */
#include "Std_Types.h"
#include "CanIf_Cfg.h"

/* clang-format off */
const CanIf_ConfigType CanIfConfig =
{
    .dummy = 0x11223344,
};
/* clang-format off */
