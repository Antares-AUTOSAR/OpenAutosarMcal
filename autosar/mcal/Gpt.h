<<<<<<< HEAD
#ifndef GPT_H__
#define GPT_H__

#define GPT_NUMBER_OF_CHANNELS 2

typedef struct _Gpt_ConfigType
{
    uint8 Channel;
    uint8 NotificationMode;
    uint8 ChannelMode;
    uint16 Prescaler;
<<<<<<< HEAD
<<<<<<< HEAD
    uint16 Period;
=======
#include "Registers.h"
#include "Std_Types.h"
#include "Bfx.h"

typedef struct _Gpt_ConfigType
{
    
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
=======
>>>>>>> bbfe89e (GPT-Code-Implementation. Rest of the functions filled.)
=======
    void ( *Notifications[ 2u ] )( void );
>>>>>>> d5b5122 (GPT-Code-Implementation. Corrections made on the functions.)
} Gpt_ConfigType;

typedef enum
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	Channel1,
	Channel2,
=======
	TIM6 = 0,
	TIM7,
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
=======
    Channel1,
=======
    Channel1 = 0,
>>>>>>> bbfe89e (GPT-Code-Implementation. Rest of the functions filled.)
    Channel2,
>>>>>>> 8a205fd (GPT-Code-Implementation. Autoformat runned, fixed some warnings.)
=======
    Channel0 = 0,
    Channel1,
>>>>>>> d5b5122 (GPT-Code-Implementation. Corrections made on the functions.)
} Gpt_ChannelType;

typedef enum
{
    GPT_CH_MODE_CONTINUOUS = 0,
    GPT_CH_MODE_ONESHOT,
} Gpt_ChannelMode;

typedef enum
{
    Enabled = 0,
    Disabled,
} Gpt_NotificationMode;

typedef enum
{
    Uninitialized = 0,
    Initialized,
    Running,
    Stopped,
    Expired
} Gpt_ChannelState;

typedef uint32 Gpt_ValueType;

<<<<<<< HEAD
=======
typedef enum
{
	GPT_MODE_NORMAL = 0x00,
	GPT_MODE_SLEEP = 0x01
} Gpt_ModeType;

void Gpt_GetVersionInfo( Std_VersionInfoType *VersionInfoPtr );
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
void Gpt_Init( const Gpt_ConfigType *ConfigPtr );
void Gpt_DeInit( void );
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_StopTimer( Gpt_ChannelType Channel );
void Gpt_EnableNotification( Gpt_ChannelType Channel );
void Gpt_DisableNotification( Gpt_ChannelType Channel );
<<<<<<< HEAD
<<<<<<< HEAD
void Gpt_Notification_TIM6( void );
void Gpt_Notification_TIM7( void );
=======
void Gpt_Notification_Channel1( void );
void Gpt_Notification_Channel2( void );
>>>>>>> d5b5122 (GPT-Code-Implementation. Corrections made on the functions.)

#endif
=======
void Gpt_SetMode( Gpt_ModeType Mode );
void Gpt_DisableWakeUp( Gpt_ChannelType Channel );
void Gpt_EnableWakeUp( Gpt_ChannelType Channel );
void Gpt_Notification_TIM6( void );
void Gpt_Notification_TIM7( void );
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
