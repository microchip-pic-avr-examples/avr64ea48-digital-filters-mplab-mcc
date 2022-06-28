 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/data_streamer/data_streamer.h"
/* #include <avr/io.h>*/ 
#include "filter/kiss_fftr.h" 
#include "filter/sine.h"
#include <math.h>


int main(void)
{
   SYSTEM_Initialize();
    
   volatile int nfft = 512;  
   volatile int out = (nfft/2)+1;
   
   kiss_fftr_cfg cfg = kiss_fftr_alloc(nfft, 0, NULL, NULL);  //kiss_fft_alloc( nfft ,is_inverse_fft ,0,0 );
   kiss_fft_scalar cpx_in[nfft]; 
   kiss_fft_cpx cpx_out[out];   
   
   
    for(int m =0;m<nfft;m++){               // fill cpx_in with nfft data points from sinewave[]
        cpx_in[m] = sinewave[m];            
     };                                     
    
    volatile int16_t watch_real=4;
    volatile int16_t watch_imag = 35;
    volatile uint32_t pwr;
    volatile uint16_t cnt=0;
	
    IO_PD6_SetHigh(); // Make PD6 output logic high
    kiss_fftr(cfg, cpx_in , cpx_out);      // The actual FFT operation
    IO_PD6_SetLow(); // Make PD6 output logic low
    while(1)
    {
  
        for(int n=0;n<out;n++)
        {
            //putting cpx_out.r  into watchable variables
            cnt = n;
            watch_real = cpx_out[n].r;
            watch_imag = cpx_out[n].i;

            //Calculating the power spectrum
            pwr = sqrt(cpx_out[n].r * cpx_out[n].r + cpx_out[n].i * cpx_out[n].i);


            //Writing four variables to USART, so they can be read by MPLAB DV:
            // 0. Start token
            // 1. watch_real (int16_t)
            // 2. watch_imag (int16_t)
            // 3. cnt (uint16_t))
            // 4. pwr (uint_32_t))
            // .. and the end token
            variableWrite_SendFrame(watch_real, watch_imag, cnt, pwr);
        }
    }      
    kiss_fft_cleanup();                         // Tidy up after you.
    
}