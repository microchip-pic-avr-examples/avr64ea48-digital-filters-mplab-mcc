/**
 * USART1 Generated Driver API Header File
 *
 * @file usart1.h
 *
 * @defgroup usart1 USART1
 *
 * @brief This header file provides APIs for the USART1 driver.
 *
 * @version USART1 Driver Version 1.0.1
*/
/*
? [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef USART1_H
#define USART1_H

#include <stdbool.h>
#include <stdio.h>
#include "../system/utils/compiler.h"
#include "../system/utils/atomic.h"
#include "../system/clock.h"
#include "uart_interface.h"

/* Normal Mode, Baud register value */
#define USART1_BAUD_RATE(BAUD_RATE) (((float)2000000 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

extern const struct UART_INTERFACE USART1_Interface;

/**
 * @ingroup usart1
 * @brief Initialize USART1 interface.
 * @param none
 * @retval 0 - the USART1 init was successful
 * @retval 1 - the USART1 init was not successful
 */ 
void USART1_Initialize(void);

/**
 * @ingroup usart1
 * @brief API to Enable RX and TX in USART1 interface.
 * @param none
 * @return none
 */
void USART1_Enable(void);

/**
 * @ingroup usart1
 * @brief APi to Enable RX in USART1 interface.
 * @param none
 * @return none
 */ 
void USART1_EnableRx(void);

/**
 * @ingroup usart1
 * @brief API to Enable TX in USART1 interface.
 * @param none
 * @return none
 */
void USART1_EnableTx(void);

/**
 * @ingroup usart1
 * @brief API to Disable USART1 interface.
 * @param none
 * @return none
 */
void USART1_Disable(void);

/**
 * @ingroup usart1
 * @brief API to Get recieved data from USART1 interface.
 * @param none
 * @return uint8_t - Data register from USART1 module
 */
uint8_t USART1_GetData(void);

/**
 * @ingroup usart1
 * @brief API to check if the USART1 can accept data to be transmitted.
 * @param none
 * @retval false - the USART1 transmitter is not ready
 * @retval true  - the USART1 transmitter is ready
 */ 
bool USART1_IsTxReady(void);

/**
 * @ingroup usart1
 * @brief API to check if the USART1 has received data.
 * @param none
 * @retval false - the USART1 has not received data
 * @retval true  - the USART1 has received data
 */
bool USART1_IsRxReady(void);

/**
 * @ingroup usart1
 * @brief API to check if the USART1 has transmitter is Busy.
 * @param none
 * @retval true  - the USART1 transmitter is busy
 * @retval false - the USART1 transmitter is free
 */
bool USART1_IsTxBusy(void);

/**
 * @ingroup usart1
 * @brief API to check if the USART1 data is transmitted.
 * @param none
 * @retval false - Data completely shifted out of the USART shift register
 * @retval true  - Data is not completely shifted out of the shift register
 */
bool USART1_IsTxDone(void);

/**
 * @ingroup usart1
 * @brief API to Read one character from USART1. Function will block if a character is not available.
 * @param none
 * @return uint8_t - Data read from the USART1 module
 */
uint8_t USART1_Read(void);

/**
 * @ingroup usart1
 * @brief API to Write one character from USART1. Function will block if a character can be accepted.
 * @param const uint8_t data - The character to write to the USART
 * @return none
 */
void USART1_Write(const uint8_t data);

/**
 * @ingroup usart1
 * @brief API for ErrorCheck USART1 interface. Checks the Recieve Error for Parity, Framing, OverRun
 * @param none
 * @return none
 */
void USART1_ErrorCheck(void);

/**
 * @ingroup usart1
 * @brief Callback function to be called if the Framing Error is occured.
 * @param void* callbackHandler - A pointer to the function to be set as framing error interrupt handler
 * @return none
 */
void USART1_FramingErrorCallbackRegister(void* callbackHandler);

/**
 * @ingroup usart1
 * @brief Callback function to be called if the Overrun Error is occured.
 * @param void* callbackHandler - A pointer to the function to be set as Overrun error interrupt handler
 * @return none
 */
void USART1_OverrunErrorCallbackRegister(void* callbackHandler);

/**
 * @ingroup usart1
 * @brief Callback function to be called if the Parity check Error is occured.
 * @param void* callbackHandler - A pointer to the function to be set as Parity error interrupt handler
 * @return none
 */
void USART1_ParityErrorCallbackRegister(void* callbackHandler);

#endif /* USART1_H */