#ifndef CRC_H_
#define CRC_H_

#include "Platform_Types.h"

uint8 Crc_CalculateCRC8( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall );
uint8 Crc_CalculateCRC8H2F( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall );
uint16 Crc_CalculateCRC16( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall );

/**
 * @brief   **Crc_CalculateCRC8**
 *
 * This service makes a CRC8 calculation on Crc_Length data bytes, with SAE J1850 parameters
 */
uint8 Crc_CalculateCRC8( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall )
{
    const uint8 Crc_Polynomial = 0x1D; // Polynomial for CRC-8
    uint8 crcValue             = Crc_StartValue8;

    if( Crc_IsFirstCall )
    {
        crcValue = 0xFF; // Initialize the CRC value with 0xFF
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= Crc_DataPtr[ i ]; // XOR with data byte

        for( uint8 bit = 0; bit < 8; bit++ )
        {
            if( crcValue & 0x80 ) // Check if MSB is 1
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial; // XOR with polynomial
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue ^ 0xFF;
}

uint8 Crc_CalculateCRC8H2F( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall )
{
    const uint8 Crc_Polynomial = 0x2F;
    uint8 crcValue             = Crc_StartValue8H2F;

    if( Crc_IsFirstCall )
    {
        crcValue = 0xFF;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= Crc_DataPtr[ i ];

        for( uint8 bit = 0; bit < 8; bit++ )
        {
            if( crcValue & 0x80 )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue;
}

uint16 Crc_CalculateCRC16( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall )
{
    const uint16 Crc_Polynomial = 0x1021;
    uint16 crcValue             = Crc_StartValue16;

    if( Crc_IsFirstCall )
    {
        crcValue = 0xFFFF;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= (uint16)Crc_DataPtr[ i ] << 8;

        for( uint8 bit = 0; bit < 8; bit++ )
        {
            if( crcValue & 0x8000 )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue;
}

#endif