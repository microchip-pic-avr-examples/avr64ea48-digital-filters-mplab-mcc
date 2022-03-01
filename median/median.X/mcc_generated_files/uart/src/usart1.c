/**
  * USART1 Generated Driver File
  *
  * @file usart1.c
  *
  * @ingroup usart1
  *
  * @brief This file contains the driver code for USART1 module.
  *
  * @version USART1 Driver Version 1.0.1
*/
/*
© [2022] Microchip Technology Inc. and its subsidiaries.

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


#include "../usart1.h"
#define RECEIVE_ERROR_MASK 0x46


static void DefaultFramingErrorCallback(void);
static void DefaultOverrunErrorCallback(void);
static void DefaultParityErrorCallback(void);
void (*USART1_framing_err_cb)(void) = &DefaultFramingErrorCallback;
void (*USART1_overrun_err_cb)(void) = &DefaultOverrunErrorCallback;
void (*USART1_parity_err_cb)(void) = &DefaultParityErrorCallback;

const struct UART_INTERFACE USART1_Interface = {
  .Initialize = USART1_Initialize,
  .Write = USART1_Write,
  .Read = USART1_Read,
  .RxCompleteCallbackRegister = NULL,
  .TxCompleteCallbackRegister = NULL,
  .ErrorCallbackRegister = NULL,
  .FramingErrorCallbackRegister = USART1_FramingErrorCallbackRegister,
  .OverrunErrorCallbackRegister = USART1_OverrunErrorCallbackRegister,
  .ParityErrorCallbackRegister = USART1_ParityErrorCallbackRegister,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = USART1_IsRxReady,
  .IsTxReady = USART1_IsTxReady,
  .IsTxDone = USART1_IsTxDone
};

void USART1_Initialize(void)
{
    //set baud rate register
    USART1.BAUD = (uint16_t)USART1_BAUD_RATE(115200);
	
    // ABEIE disabled; DREIE disabled; LBME disabled; RS485 DISABLE; RXCIE disabled; RXSIE disabled; TXCIE disabled; 
    USART1.CTRLA = 0x0;
	
    // MPCM disabled; ODME disabled; RXEN enabled; RXMODE NORMAL; SFDEN disabled; TXEN enabled; 
    USART1.CTRLB = 0xC0;
	
    // CMODE Asynchronous Mode; UCPHA enabled; UDORD disabled; CHSIZE Character size: 8 bit; PMODE No Parity; SBMODE 1 stop bit; 
    USART1.CTRLC = 0x3;
	
    //DBGCTRL_DBGRUN
    USART1.DBGCTRL = 0x0;
	
    //EVCTRL_IREI
    USART1.EVCTRL = 0x0;
	
    //RXPLCTRL_RXPL
    USART1.RXPLCTRL = 0x0;
	
    //TXPLCTRL_TXPL
    USART1.TXPLCTRL = 0x0;
	

}

void USART1_FramingErrorCallbackRegister(void* callbackHandler)
{
    USART1_framing_err_cb=callbackHandler;
}

void USART1_OverrunErrorCallbackRegister(void* callbackHandler)
{
    USART1_overrun_err_cb=callbackHandler;
}

void USART1_ParityErrorCallbackRegister(void* callbackHandler)
{
    USART1_parity_err_cb=callbackHandler;
}

static void DefaultFramingErrorCallback(void)
{
    /* Add your interrupt code here or use USART1.FramingCallbackRegister function to use Custom ISR */
}

static void DefaultOverrunErrorCallback(void)
{
   /* Add your interrupt code here or use USART1.OverrunCallbackRegister function to use Custom ISR */
}

static void DefaultParityErrorCallback(void)
{
    /* Add your interrupt code here or use USART1.ParityCallbackRegister function to use Custom ISR */
}

void USART1_Enable(void)
{
    USART1.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART1_EnableRx(void)
{
    USART1.CTRLB |= USART_RXEN_bm;
}

void USART1_EnableTx(void)
{
    USART1.CTRLB |= USART_TXEN_bm;
}

void USART1_Disable(void)
{
    USART1.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART1_GetData(void)
{
    return USART1.RXDATAL;
}

bool USART1_IsTxReady(void)
{
    return (USART1.STATUS & USART_DREIF_bm);
}

bool USART1_IsRxReady(void)
{
    return (USART1.STATUS & USART_RXCIF_bm);
}

bool USART1_IsTxBusy(void)
{
    return (!(USART1.STATUS & USART_TXCIF_bm));
}

bool USART1_IsTxDone(void)
{
    return (USART1.STATUS & USART_TXCIF_bm);
}

void USART1_ErrorCheck(void)
{
    uint8_t errorMask = USART1.RXDATAH;
    if(errorMask & RECEIVE_ERROR_MASK)
    {
        if(errorMask & USART_PERR_bm)
        {
            USART1_parity_err_cb();
        } 
        if(errorMask & USART_FERR_bm)
        {
            USART1_framing_err_cb();
        }
        if(errorMask & USART_BUFOVF_bm)
        {
            USART1_overrun_err_cb();
        }
    }
    
}

uint8_t USART1_Read(void)
{       
    return USART1.RXDATAL;
}

void USART1_Write(const uint8_t data)
{
    USART1.TXDATAL = data;
}