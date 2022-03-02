[![MCHP](images/microchip.png)](https://www.microchip.com)

# Demo of Digital filters on AVR EA on AVR EA using MPLAB® X

In signal processing various problems can be solved by using different type of filters. This can range from smoothing signals to estimating future values based on other analog signals. In this demo we have created demos using median-, *FFT-*, *iir-* and *kalman-filter*.

[Median Filter](median/README.md)

The Median filter is a simple idea to smooth a signal by removing spikes from the signal. The median filter can be used both on images and on 1-dimensional signal problems, which is what will be covered here. 

[Fast Fourier Transform](fft/README.md)

The Fast Fourier Transformation (FFT) is a versatile tool for signal analysis. The general idea, in terms of electronic signals, is to de-compose a given signal (in the time domain) into sinus-shaped components (in the frequency domain).

[Infinite Impulse Response](iir/README.md)

Infinite Impulse Response (IIR) filters are a class of filters that are feedback-based, i.e. the previous output plays a role in the current output. The demo will cover *Band Pass Filter* and *Low Pass Filter*, but the library also supports *High Pass Filter*, *Notch Filter*, *Peaking Band EQ Filter*, *Low Shelf Filter* and *High Shelf Filter*.

[Kalman](kalman/README.md)

The Kalman filter, also called linear quadratic estimation (LQE), is an algorithm that uses a series of measurements to estimate unknown variables in the future. State estimation can for example be used to predict the placement of a robotic vacuum cleaner to avoid hitting into walls, or for creating a balancing robot.

    
## Related Documentation

- [The Road to Median Filter Mastery](https://blog.eddyfi.com/en/the-road-to-median-filter-mastery)
- [FFT Visualization and Explanation](https://www.karlsims.com/fft.html)
- [Digital Filters and IIR](http://musicweb.ucsd.edu/~trsmyth/filters/Digital_Filters.html)
- [Kalman Filter For Dummies](http://bilgin.esme.org/BitsAndBytes/KalmanFilterforDummies)


## Software Used
- [MPLAB® X IDE v5.50](https://www.microchip.com/mplab/mplab-x-ide) or newer
- [MPLAB® Xpress IDE](https://www.microchip.com/xpress) (alternative to MPLAB X IDE)
- [XC8 Compiler v2.32](https://www.microchip.com/mplab/compilers) or newer
- [MPLAB® Code Configurator (MCC) v5.0.3](https://www.microchip.com/mplab/mplab-code-configurator) or newer
- [MPLAB® Melody Library 1.37.30 or  newer](https://www.microchip.com/mplab/mplab-code-configurator) or newer
- [Microchip AVR64EA48 Device Support Pack AVR-Dx_DFP 1.0.38](https://packs.download.microchip.com/) or newer

## Hardware Used

* [AVR64EA48 Curiosity Nano](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EV66E56A)

## Setup

<!-- Explain how to connect hardware and set up software. Depending on complexity, step-by-step instructions and/or tables and/or images can be used -->

## Operation



<!-- Explain how to operate the example. Depending on complexity, step-by-step instructions and/or tables and/or images can be used -->

## Summary
After going through these use cases, you should better understand how to use the mentioned filters in an AVR context. This includes how this can be used together with the MPLAB® Code Configurator called Melody and also measuring the speed of the filters.


