/**
 * @file        ComStack_Types.h
 * @brief       This file is the AUTOSAR communication stack type header file. 
 * 
 * It contains all types that are used across several modules of the communication stack of the 
 * basic software and all types of all basic software modules that are platform and compiler 
 * independent.
 * This file contains definitions of variables, structs an enums for the use of ComStack.
 */
#include "Std_Types.h"

/**
 * @brief This type is used within the entire AUTOSAR Com Stack except for bus drivers.
 * 
 * Variables of this type serve as a unique identifier of a PDU within a software module or
 * a set thereof, and also for interaction of two software modules where the PduId of the
 * corresponding target module is being used for referencing.
 * The size of this global type depends on the maximum number of PDUs used within one software
 * module.
 * This parameter shall be generated by the generator tool depending on the value configured in
 * EcuC virtual layer.
 *
 * @reqs  SWS_COMTYPE_00005, SWS_Comtype_00006, SWS_Comtype_00007, SWS_Comtype_00014
 */
typedef uint8 PduIdType;

/**
 * @brief This type shall be used within the entire AUTOSAR Com Stack except for bus drivers.
 *
 * Variables of this type serve as length information of a PDU. The length information is provided 
 * in number of bytes.
 * The maximum length of a Pdu, is the length of the largest (possibly segmented) PDU to be sent by
 * the ECU.
 * This parameter shall be generated by the generator tool depending on the value configured in
 * EcuC virtual layer.
 *
 * @reqs  SWS_COMTYPE_00008, SWS_Comtype_00010, SWS_Comtype_00017
 */
typedef uint32 PduLengthType;

/**
 * @brief This variables shall be used to store the basic information about a PDU.
 * 
 * Variables of this type shall be used to store the basic information about a PDU of any
 * type, namely a pointer variable pointing to its SDU (payload), a pointer to Meta Data of the
 * PDU, and the corresponding length of the SDU in bytes.
 *
 * @reqs  SWS_COMTYPE_00011
 */
typedef struct
{
    uint8 *SduDataPtr;       /*!< Pointer to the SDU (i.e. payload data) of the PDU. The type of
                             this pointer depends on the memory model being used at compile time*/
    uint8 *MetaDataPtr;      /*!<Pointer to the meta data (e.g. CAN ID, socket ID, diagnostic
                             addresses) of the PDU, consisting of a sequence of meta data items.
                             The length and type of the meta data items is statically configured
                             for each PDU. Meta data items with more than 8 bits use platform
                             byte order.*/
    PduLengthType SduLength; /*!<Length of the SDU in bytes.*/
} PduInfoType;

/**
 * @brief Used to store the identifier of a partial network cluster.
 *
 * @reqs  SWS_COMTYPE_00036
 */
typedef uint8 PNCHandleType;

/**
 * @brief Specify the parameter to which the value has to be changed (BS or STmin).
 *
 * @reqs  SWS_COMTYPE_00031
 */
typedef enum
{
    TP_STMIN = 0x00, /*Separation Time*/
    TP_BS    = 0x01, /*Block Size*/
    TP_BC    = 0x02  /*The Band width control parameter used in FlexRay transport protocol
                     module.*/
} TPParameterType;

/**
 * @brief Variables of this type shall be used to store the result of a buffer request.
 *
 * @reqs  SWS_COMTYPE_00012
 */
typedef enum
{
    BUFREQ_OK = 0x00,       /*Buffer request accomplished successful. This status shall have the
                            value 0.*/
    BUFREQ_E_NOT_OK = 0x01, /*Buffer request not successful. Buffer cannot be accessed. This status
                            shall have the value 1.*/
    BUFREQ_E_BUSY = 0x02,   /*Temporarily no buffer available. It's up the requester to retry
                            request for a certain time. This status shall have the value 2.*/
    BUFREQ_E_OVFL = 0x03    /*No Buffer of the required length can be provided. This status shall
                            have the value 3.*/
} BufReq_ReturnType;

/**
 * @brief Variables of this type shall be used to store the state of TP buffer.
 *
 * @reqs  SWS_COMTYPE_00027
 */
typedef enum
{
    TP_DATACONF = 0x00,   /*TP_DATACONF indicates that all data, that have been copied so far,
                          are confirmed and can be removed from the TP buffer. Data copied by
                          this API call are excluded and will be confirmed later.*/
    TP_DATARETRY = 0x01,  /*TP_DATARETRY indicates that this API call shall copy already copied
                          data in order to recover from an error. In this case TxTpDataCnt
                          specifies the offset of the first byte to be copied by the API call.*/
    TP_CONFPENDING = 0x02 /*TP_CONFPENDING indicates that the previously copied data must remain
                          in the TP.*/
} TpDataStateType;

/**
 * @brief Variables of this type shall be used to store the information about Tp buffer handling.
 *
 * @reqs  SWS_COMTYPE_00037
 */
typedef struct
{
    TpDataStateType TpDataState; /*!<The enum type to be used to store the state of Tp buffer.*/
    PduLengthType TxTpDataCnt;   /*!<Offset from the current position which identifies the number
                                 of bytes to be retransmitted.*/
} RetryInfoType;

/**
 * @brief This variables shall be used to store the identifier of a communication channel.
 *
 * @reqs  SWS_COMTYPE_00038
 */
typedef uint8 NetworkHandleType;

/**
 * @brief Used for the handle Ids of Com and LdCom user callbacks. Tags: atp.Status=draft
 *
 * @reqs  SWS_COMTYPE_91001 DRAFT
 */
typedef uint16 CbkHandleIdType;