/*****************************************************************************
 *
 * Copyright (C) 2020 Atmel Corporation, a wholly owned subsidiary of Microchip Technology Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************/


#ifndef _AVR_IO_H_
#  error "Include <avr/io.h> instead of this file."
#endif

#ifndef _AVR_IOXXX_H_
#  define _AVR_IOXXX_H_ "iox64b1.h"
#else
#  error "Attempt to include more than one <avr/ioXXX.h> file."
#endif

#ifndef _AVR_ATXMEGA64B1_H_INCLUDED
#define _AVR_ATXMEGA64B1_H_INCLUDED

/* Ungrouped common registers */
#define GPIOR0  _SFR_MEM8(0x0000)  /* General Purpose IO Register 0 */
#define GPIOR1  _SFR_MEM8(0x0001)  /* General Purpose IO Register 1 */
#define GPIOR2  _SFR_MEM8(0x0002)  /* General Purpose IO Register 2 */
#define GPIOR3  _SFR_MEM8(0x0003)  /* General Purpose IO Register 3 */

/* Deprecated */
#define GPIO0  _SFR_MEM8(0x0000)  /* General Purpose IO Register 0 */
#define GPIO1  _SFR_MEM8(0x0001)  /* General Purpose IO Register 1 */
#define GPIO2  _SFR_MEM8(0x0002)  /* General Purpose IO Register 2 */
#define GPIO3  _SFR_MEM8(0x0003)  /* General Purpose IO Register 3 */

#define CCP  _SFR_MEM8(0x0034)  /* Configuration Change Protection */
#define RAMPD  _SFR_MEM8(0x0038)  /* Ramp D */
#define RAMPX  _SFR_MEM8(0x0039)  /* Ramp X */
#define RAMPY  _SFR_MEM8(0x003A)  /* Ramp Y */
#define RAMPZ  _SFR_MEM8(0x003B)  /* Ramp Z */
#define EIND  _SFR_MEM8(0x003C)  /* Extended Indirect Jump */
#define SPL  _SFR_MEM8(0x003D)  /* Stack Pointer Low */
#define SPH  _SFR_MEM8(0x003E)  /* Stack Pointer High */
#define SREG  _SFR_MEM8(0x003F)  /* Status Register */

/* C Language Only */
#if !defined (__ASSEMBLER__)

#include <stdint.h>

typedef volatile uint8_t register8_t;
typedef volatile uint16_t register16_t;
typedef volatile uint32_t register32_t;


#ifdef _WORDREGISTER
#undef _WORDREGISTER
#endif
#define _WORDREGISTER(regname)   \
    __extension__ union \
    { \
        register16_t regname; \
        struct \
        { \
            register8_t regname ## L; \
            register8_t regname ## H; \
        }; \
    }

#ifdef _DWORDREGISTER
#undef _DWORDREGISTER
#endif
#define _DWORDREGISTER(regname)  \
    __extension__ union \
    { \
        register32_t regname; \
        struct \
        { \
            register8_t regname ## 0; \
            register8_t regname ## 1; \
            register8_t regname ## 2; \
            register8_t regname ## 3; \
        }; \
    }


/*
==========================================================================
IO Module Structures
==========================================================================
*/


/*
--------------------------------------------------------------------------
AC - Analog Comparator
--------------------------------------------------------------------------
*/

/* Analog Comparator */
typedef struct AC_struct
{
    register8_t AC0CTRL;  /* Analog Comparator 0 Control */
    register8_t AC1CTRL;  /* Analog Comparator 1 Control */
    register8_t AC0MUXCTRL;  /* Analog Comparator 0 MUX Control */
    register8_t AC1MUXCTRL;  /* Analog Comparator 1 MUX Control */
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t WINCTRL;  /* Window Mode Control */
    register8_t STATUS;  /* Status */
    register8_t CURRCTRL;  /* Current Source Control Register */
    register8_t CURRCALIB;  /* Current Source Calibration Register */
} AC_t;

/* Hysteresis mode selection */
typedef enum AC_HYSMODE_enum
{
    AC_HYSMODE_NO_gc = (0x00<<1),  /* No hysteresis */
    AC_HYSMODE_SMALL_gc = (0x01<<1),  /* Small hysteresis */
    AC_HYSMODE_LARGE_gc = (0x02<<1),  /* Large hysteresis */
} AC_HYSMODE_t;

/* Interrupt level */
typedef enum AC_INTLVL_enum
{
    AC_INTLVL_OFF_gc = (0x00<<4),  /* Interrupt disabled */
    AC_INTLVL_LO_gc = (0x01<<4),  /* Low level */
    AC_INTLVL_MED_gc = (0x02<<4),  /* Medium level */
    AC_INTLVL_HI_gc = (0x03<<4),  /* High level */
} AC_INTLVL_t;

/* Interrupt mode */
typedef enum AC_INTMODE_enum
{
    AC_INTMODE_BOTHEDGES_gc = (0x00<<6),  /* Interrupt on both edges */
    AC_INTMODE_FALLING_gc = (0x02<<6),  /* Interrupt on falling edge */
    AC_INTMODE_RISING_gc = (0x03<<6),  /* Interrupt on rising edge */
} AC_INTMODE_t;

/* Negative input multiplexer selection */
typedef enum AC_MUXNEG_enum
{
    AC_MUXNEG_PIN0_gc = (0x00<<0),  /* Pin 0 */
    AC_MUXNEG_PIN1_gc = (0x01<<0),  /* Pin 1 */
    AC_MUXNEG_PIN3_gc = (0x02<<0),  /* Pin 3 */
    AC_MUXNEG_PIN5_gc = (0x03<<0),  /* Pin 5 */
    AC_MUXNEG_PIN7_gc = (0x04<<0),  /* Pin 7 */
    AC_MUXNEG_BANDGAP_gc = (0x06<<0),  /* Bandgap Reference */
    AC_MUXNEG_SCALER_gc = (0x07<<0),  /* Internal voltage scaler */
} AC_MUXNEG_t;

/* Positive input multiplexer selection */
typedef enum AC_MUXPOS_enum
{
    AC_MUXPOS_PIN0_gc = (0x00<<3),  /* Pin 0 */
    AC_MUXPOS_PIN1_gc = (0x01<<3),  /* Pin 1 */
    AC_MUXPOS_PIN2_gc = (0x02<<3),  /* Pin 2 */
    AC_MUXPOS_PIN3_gc = (0x03<<3),  /* Pin 3 */
    AC_MUXPOS_PIN4_gc = (0x04<<3),  /* Pin 4 */
    AC_MUXPOS_PIN5_gc = (0x05<<3),  /* Pin 5 */
    AC_MUXPOS_PIN6_gc = (0x06<<3),  /* Pin 6 */
} AC_MUXPOS_t;

/* Window interrupt level */
typedef enum AC_WINTLVL_enum
{
    AC_WINTLVL_OFF_gc = (0x00<<0),  /* Interrupt disabled */
    AC_WINTLVL_LO_gc = (0x01<<0),  /* Low priority */
    AC_WINTLVL_MED_gc = (0x02<<0),  /* Medium priority */
    AC_WINTLVL_HI_gc = (0x03<<0),  /* High priority */
} AC_WINTLVL_t;

/* Windows interrupt mode */
typedef enum AC_WINTMODE_enum
{
    AC_WINTMODE_ABOVE_gc = (0x00<<2),  /* Interrupt on above window */
    AC_WINTMODE_INSIDE_gc = (0x01<<2),  /* Interrupt on inside window */
    AC_WINTMODE_BELOW_gc = (0x02<<2),  /* Interrupt on below window */
    AC_WINTMODE_OUTSIDE_gc = (0x03<<2),  /* Interrupt on outside window */
} AC_WINTMODE_t;

/* Window mode state */
typedef enum AC_WSTATE_enum
{
    AC_WSTATE_ABOVE_gc = (0x00<<6),  /* Signal above window */
    AC_WSTATE_INSIDE_gc = (0x01<<6),  /* Signal inside window */
    AC_WSTATE_BELOW_gc = (0x02<<6),  /* Signal below window */
} AC_WSTATE_t;

/*
--------------------------------------------------------------------------
ADC - Analog/Digital Converter
--------------------------------------------------------------------------
*/

/* ADC Channel */
typedef struct ADC_CH_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t MUXCTRL;  /* MUX Control */
    register8_t INTCTRL;  /* Channel Interrupt Control Register */
    register8_t INTFLAGS;  /* Interrupt Flags */
    _WORDREGISTER(RES);  /* Channel Result */
    register8_t SCAN;  /* Input Channel Scan */
    register8_t reserved_1[1];
} ADC_CH_t;


/* Analog-to-Digital Converter */
typedef struct ADC_struct
{
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t REFCTRL;  /* Reference Control */
    register8_t EVCTRL;  /* Event Control */
    register8_t PRESCALER;  /* Clock Prescaler */
    register8_t reserved_1[1];
    register8_t INTFLAGS;  /* Interrupt Flags */
    register8_t TEMP;  /* Temporary Register */
    register8_t SAMPCTRL;  /* ADC Sampling Time Control Register */
    register8_t reserved_2[3];
    _WORDREGISTER(CAL);  /* Calibration Value */
    register8_t reserved_3[2];
    _WORDREGISTER(CH0RES);  /* Channel 0 Result */
    register8_t reserved_4[6];
    _WORDREGISTER(CMP);  /* Compare Value */
    register8_t reserved_5[6];
    ADC_CH_t CH0;  /* ADC Channel 0 */
} ADC_t;

/* Gain factor */
typedef enum ADC_CH_GAIN_enum
{
    ADC_CH_GAIN_1X_gc = (0x00<<2),  /* 1x gain */
    ADC_CH_GAIN_2X_gc = (0x01<<2),  /* 2x gain */
    ADC_CH_GAIN_4X_gc = (0x02<<2),  /* 4x gain */
    ADC_CH_GAIN_8X_gc = (0x03<<2),  /* 8x gain */
    ADC_CH_GAIN_16X_gc = (0x04<<2),  /* 16x gain */
    ADC_CH_GAIN_32X_gc = (0x05<<2),  /* 32x gain */
    ADC_CH_GAIN_64X_gc = (0x06<<2),  /* 64x gain */
    ADC_CH_GAIN_DIV2_gc = (0x07<<2),  /* x/2 gain */
} ADC_CH_GAIN_t;

/* Input mode */
typedef enum ADC_CH_INPUTMODE_enum
{
    ADC_CH_INPUTMODE_INTERNAL_gc = (0x00<<0),  /* Internal inputs, no gain (INPUTMODE = 0) */
    ADC_CH_INPUTMODE_SINGLEENDED_gc = (0x01<<0),  /* Single-ended input, no gain (INPUTMODE = 1) */
    ADC_CH_INPUTMODE_DIFF_gc = (0x02<<0),  /* Differential input, no gain (INPUTMODE = 2) */
    ADC_CH_INPUTMODE_DIFFWGAIN_gc = (0x03<<0),  /* Differential input, with gain (INPUTMODE = 3) */
} ADC_CH_INPUTMODE_t;

/* Interrupt level */
typedef enum ADC_CH_INTLVL_enum
{
    ADC_CH_INTLVL_OFF_gc = (0x00<<0),  /* Interrupt disabled */
    ADC_CH_INTLVL_LO_gc = (0x01<<0),  /* Low level */
    ADC_CH_INTLVL_MED_gc = (0x02<<0),  /* Medium level */
    ADC_CH_INTLVL_HI_gc = (0x03<<0),  /* High level */
} ADC_CH_INTLVL_t;

/* Interupt mode */
typedef enum ADC_CH_INTMODE_enum
{
    ADC_CH_INTMODE_COMPLETE_gc = (0x00<<2),  /* Interrupt on conversion complete */
    ADC_CH_INTMODE_BELOW_gc = (0x01<<2),  /* Interrupt on result below compare value */
    ADC_CH_INTMODE_ABOVE_gc = (0x03<<2),  /* Interrupt on result above compare value */
} ADC_CH_INTMODE_t;

/* Internal input multiplexer selections */
typedef enum ADC_CH_MUXINT_enum
{
    ADC_CH_MUXINT_TEMP_gc = (0x00<<3),  /* Temperature Reference */
    ADC_CH_MUXINT_BANDGAP_gc = (0x01<<3),  /* Bandgap Reference */
    ADC_CH_MUXINT_SCALEDVCC_gc = (0x02<<3),  /* 1/10 scaled VCC */
} ADC_CH_MUXINT_t;

/* Negative input multiplexer selection */
typedef enum ADC_CH_MUXNEG_enum
{
    ADC_CH_MUXNEG_PIN0_gc = (0x00<<0),  /* Input pin 0 (if INPUTMODE = 2) */
    ADC_CH_MUXNEG_PIN4_gc = (0x00<<0),  /* Input pin 4 (if INPUTMODE = 3) */
    ADC_CH_MUXNEG_PIN1_gc = (0x01<<0),  /* Input pin 1 (if INPUTMODE = 2) */
    ADC_CH_MUXNEG_PIN5_gc = (0x01<<0),  /* Input pin 5 (if INPUTMODE = 3) */
    ADC_CH_MUXNEG_PIN2_gc = (0x02<<0),  /* Input pin 2 (if INPUTMODE = 2) */
    ADC_CH_MUXNEG_PIN6_gc = (0x02<<0),  /* Input pin 6 (if INPUTMODE = 3) */
    ADC_CH_MUXNEG_PIN3_gc = (0x03<<0),  /* Input pin 3 (if INPUTMODE = 2) */
    ADC_CH_MUXNEG_PIN7_gc = (0x03<<0),  /* Input pin 7 (if INPUTMODE = 3) */
    ADC_CH_MUXNEG_INTGND_MODE4_gc = (0x04<<0),  /* Internal Ground (if INPUTMODE = 3) */
    ADC_CH_MUXNEG_GND_MODE3_gc = (0x05<<0),  /* PAD Ground (if INPUTMODE = 2) */
    ADC_CH_MUXNEG_INTGND_MODE3_gc = (0x07<<0),  /* Internal Ground (if INPUTMODE = 2) */
    ADC_CH_MUXNEG_GND_MODE4_gc = (0x07<<0),  /* PAD Ground (if INPUTMODE = 3) */
} ADC_CH_MUXNEG_t;

/* Negative input multiplexer selection when gain on 4 MSB pins */
typedef enum ADC_CH_MUXNEGH_enum
{
    ADC_CH_MUXNEGH_PIN4_gc = (0x00<<0),  /* Input pin 4 */
    ADC_CH_MUXNEGH_PIN5_gc = (0x01<<0),  /* Input pin 5 */
    ADC_CH_MUXNEGH_PIN6_gc = (0x02<<0),  /* Input pin 6 */
    ADC_CH_MUXNEGH_PIN7_gc = (0x03<<0),  /* Input pin 7 */
    ADC_CH_MUXNEGH_INTGND_gc = (0x04<<0),  /* Internal ground */
    ADC_CH_MUXNEGH_GND_gc = (0x07<<0),  /* PAD ground */
} ADC_CH_MUXNEGH_t;

/* Negative input multiplexer selection when gain on 4 LSB pins */
typedef enum ADC_CH_MUXNEGL_enum
{
    ADC_CH_MUXNEGL_PIN0_gc = (0x00<<0),  /* Input pin 0 */
    ADC_CH_MUXNEGL_PIN1_gc = (0x01<<0),  /* Input pin 1 */
    ADC_CH_MUXNEGL_PIN2_gc = (0x02<<0),  /* Input pin 2 */
    ADC_CH_MUXNEGL_PIN3_gc = (0x03<<0),  /* Input pin 3 */
    ADC_CH_MUXNEGL_GND_gc = (0x05<<0),  /* PAD ground */
    ADC_CH_MUXNEGL_INTGND_gc = (0x07<<0),  /* Internal ground */
} ADC_CH_MUXNEGL_t;

/* Positive input multiplexer selection */
typedef enum ADC_CH_MUXPOS_enum
{
    ADC_CH_MUXPOS_PIN0_gc = (0x00<<3),  /* Input pin 0 */
    ADC_CH_MUXPOS_PIN1_gc = (0x01<<3),  /* Input pin 1 */
    ADC_CH_MUXPOS_PIN2_gc = (0x02<<3),  /* Input pin 2 */
    ADC_CH_MUXPOS_PIN3_gc = (0x03<<3),  /* Input pin 3 */
    ADC_CH_MUXPOS_PIN4_gc = (0x04<<3),  /* Input pin 4 */
    ADC_CH_MUXPOS_PIN5_gc = (0x05<<3),  /* Input pin 5 */
    ADC_CH_MUXPOS_PIN6_gc = (0x06<<3),  /* Input pin 6 */
    ADC_CH_MUXPOS_PIN7_gc = (0x07<<3),  /* Input pin 7 */
    ADC_CH_MUXPOS_PIN8_gc = (0x08<<3),  /* Input pin 8 */
    ADC_CH_MUXPOS_PIN9_gc = (0x09<<3),  /* Input pin 9 */
    ADC_CH_MUXPOS_PIN10_gc = (0x0A<<3),  /* Input pin 10 */
    ADC_CH_MUXPOS_PIN11_gc = (0x0B<<3),  /* Input pin 11 */
    ADC_CH_MUXPOS_PIN12_gc = (0x0C<<3),  /* Input pin 12 */
    ADC_CH_MUXPOS_PIN13_gc = (0x0D<<3),  /* Input pin 13 */
    ADC_CH_MUXPOS_PIN14_gc = (0x0E<<3),  /* Input pin 14 */
    ADC_CH_MUXPOS_PIN15_gc = (0x0F<<3),  /* Input pin 15 */
} ADC_CH_MUXPOS_t;

/* Current Limitation */
typedef enum ADC_CURRLIMIT_enum
{
    ADC_CURRLIMIT_NO_gc = (0x00<<5),  /* No current limit,     300ksps max sampling rate */
    ADC_CURRLIMIT_LOW_gc = (0x01<<5),  /* Low current limit,    250ksps max sampling rate */
    ADC_CURRLIMIT_MED_gc = (0x02<<5),  /* Medium current limit, 150ksps max sampling rate */
    ADC_CURRLIMIT_HIGH_gc = (0x03<<5),  /* High current limit,   50ksps max sampling rate */
} ADC_CURRLIMIT_t;

/* Event action selection */
typedef enum ADC_EVACT_enum
{
    ADC_EVACT_NONE_gc = (0x00<<0),  /* No event action */
    ADC_EVACT_CH0_gc = (0x01<<0),  /* First event triggers channel 0 */
    ADC_EVACT_SYNCSWEEP_gc = (0x06<<0),  /* The ADC is flushed and restarted for accurate timing */
} ADC_EVACT_t;

/* Event channel input selection */
typedef enum ADC_EVSEL_enum
{
    ADC_EVSEL_0_gc = (0x00<<3),  /* Event Channel 0 */
    ADC_EVSEL_1_gc = (0x01<<3),  /* Event Channel 1 */
    ADC_EVSEL_2_gc = (0x02<<3),  /* Event Channel 2 */
    ADC_EVSEL_3_gc = (0x03<<3),  /* Event Channel 3 */
} ADC_EVSEL_t;

/* Clock prescaler */
typedef enum ADC_PRESCALER_enum
{
    ADC_PRESCALER_DIV4_gc = (0x00<<0),  /* Divide clock by 4 */
    ADC_PRESCALER_DIV8_gc = (0x01<<0),  /* Divide clock by 8 */
    ADC_PRESCALER_DIV16_gc = (0x02<<0),  /* Divide clock by 16 */
    ADC_PRESCALER_DIV32_gc = (0x03<<0),  /* Divide clock by 32 */
    ADC_PRESCALER_DIV64_gc = (0x04<<0),  /* Divide clock by 64 */
    ADC_PRESCALER_DIV128_gc = (0x05<<0),  /* Divide clock by 128 */
    ADC_PRESCALER_DIV256_gc = (0x06<<0),  /* Divide clock by 256 */
    ADC_PRESCALER_DIV512_gc = (0x07<<0),  /* Divide clock by 512 */
} ADC_PRESCALER_t;

/* Voltage reference selection */
typedef enum ADC_REFSEL_enum
{
    ADC_REFSEL_INT1V_gc = (0x00<<4),  /* Internal 1V */
    ADC_REFSEL_INTVCC_gc = (0x01<<4),  /* Internal VCC / 1.6 */
    ADC_REFSEL_AREFA_gc = (0x02<<4),  /* External reference on PORT A */
    ADC_REFSEL_AREFB_gc = (0x03<<4),  /* External reference on PORT B */
    ADC_REFSEL_INTVCC2_gc = (0x04<<4),  /* Internal VCC / 2 */
} ADC_REFSEL_t;

/* Conversion result resolution */
typedef enum ADC_RESOLUTION_enum
{
    ADC_RESOLUTION_12BIT_gc = (0x00<<1),  /* 12-bit right-adjusted result */
    ADC_RESOLUTION_8BIT_gc = (0x02<<1),  /* 8-bit right-adjusted result */
    ADC_RESOLUTION_LEFT12BIT_gc = (0x03<<1),  /* 12-bit left-adjusted result */
} ADC_RESOLUTION_t;

/*
--------------------------------------------------------------------------
AES - AES Module
--------------------------------------------------------------------------
*/

/* AES Module */
typedef struct AES_struct
{
    register8_t CTRL;  /* AES Control Register */
    register8_t STATUS;  /* AES Status Register */
    register8_t STATE;  /* AES State Register */
    register8_t KEY;  /* AES Key Register */
    register8_t INTCTRL;  /* AES Interrupt Control Register */
} AES_t;

/* Interrupt level */
typedef enum AES_INTLVL_enum
{
    AES_INTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    AES_INTLVL_LO_gc = (0x01<<0),  /* Low Level */
    AES_INTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    AES_INTLVL_HI_gc = (0x03<<0),  /* High Level */
} AES_INTLVL_t;

/*
--------------------------------------------------------------------------
AWEX - Timer/Counter Advanced Waveform Extension
--------------------------------------------------------------------------
*/

/* Advanced Waveform Extension */
typedef struct AWEX_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t reserved_1[1];
    register8_t FDEMASK;  /* Fault Detection Event Mask */
    register8_t FDCTRL;  /* Fault Detection Control Register */
    register8_t STATUS;  /* Status Register */
    register8_t STATUSSET;  /* Status Set Register */
    register8_t DTBOTH;  /* Dead Time Both Sides */
    register8_t DTBOTHBUF;  /* Dead Time Both Sides Buffer */
    register8_t DTLS;  /* Dead Time Low Side */
    register8_t DTHS;  /* Dead Time High Side */
    register8_t DTLSBUF;  /* Dead Time Low Side Buffer */
    register8_t DTHSBUF;  /* Dead Time High Side Buffer */
    register8_t OUTOVEN;  /* Output Override Enable */
} AWEX_t;

/* Fault Detect Action */
typedef enum AWEX_FDACT_enum
{
    AWEX_FDACT_NONE_gc = (0x00<<0),  /* No Fault Protection */
    AWEX_FDACT_CLEAROE_gc = (0x01<<0),  /* Clear Output Enable Bits */
    AWEX_FDACT_CLEARDIR_gc = (0x03<<0),  /* Clear I/O Port Direction Bits */
} AWEX_FDACT_t;

/*
--------------------------------------------------------------------------
CLK - Clock System
--------------------------------------------------------------------------
*/

/* Clock System */
typedef struct CLK_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t PSCTRL;  /* Prescaler Control Register */
    register8_t LOCK;  /* Lock register */
    register8_t RTCCTRL;  /* RTC Control Register */
    register8_t USBCTRL;  /* USB Control Register */
} CLK_t;

/* Prescaler A Division Factor */
typedef enum CLK_PSADIV_enum
{
    CLK_PSADIV_1_gc = (0x00<<2),  /* Divide by 1 */
    CLK_PSADIV_2_gc = (0x01<<2),  /* Divide by 2 */
    CLK_PSADIV_4_gc = (0x03<<2),  /* Divide by 4 */
    CLK_PSADIV_8_gc = (0x05<<2),  /* Divide by 8 */
    CLK_PSADIV_16_gc = (0x07<<2),  /* Divide by 16 */
    CLK_PSADIV_32_gc = (0x09<<2),  /* Divide by 32 */
    CLK_PSADIV_64_gc = (0x0B<<2),  /* Divide by 64 */
    CLK_PSADIV_128_gc = (0x0D<<2),  /* Divide by 128 */
    CLK_PSADIV_256_gc = (0x0F<<2),  /* Divide by 256 */
    CLK_PSADIV_512_gc = (0x11<<2),  /* Divide by 512 */
} CLK_PSADIV_t;

/* Prescaler B and C Division Factor */
typedef enum CLK_PSBCDIV_enum
{
    CLK_PSBCDIV_1_1_gc = (0x00<<0),  /* Divide B by 1 and C by 1 */
    CLK_PSBCDIV_1_2_gc = (0x01<<0),  /* Divide B by 1 and C by 2 */
    CLK_PSBCDIV_4_1_gc = (0x02<<0),  /* Divide B by 4 and C by 1 */
    CLK_PSBCDIV_2_2_gc = (0x03<<0),  /* Divide B by 2 and C by 2 */
} CLK_PSBCDIV_t;

/* RTC Clock Source */
typedef enum CLK_RTCSRC_enum
{
    CLK_RTCSRC_ULP_gc = (0x00<<1),  /* 1.024 kHz from internal 32kHz ULP */
    CLK_RTCSRC_TOSC_gc = (0x01<<1),  /* 1.024 kHz from 32.768 kHz crystal oscillator on TOSC */
    CLK_RTCSRC_RCOSC_gc = (0x02<<1),  /* 1.024 kHz from internal 32.768 kHz RC oscillator */
    CLK_RTCSRC_TOSC32_gc = (0x05<<1),  /* 32.768 kHz from 32.768 kHz crystal oscillator on TOSC */
    CLK_RTCSRC_RCOSC32_gc = (0x06<<1),  /* 32.768 kHz from internal 32.768 kHz RC oscillator */
    CLK_RTCSRC_EXTCLK_gc = (0x07<<1),  /* External Clock from TOSC1 */
} CLK_RTCSRC_t;

/* System Clock Selection */
typedef enum CLK_SCLKSEL_enum
{
    CLK_SCLKSEL_RC2M_gc = (0x00<<0),  /* Internal 2 MHz RC Oscillator */
    CLK_SCLKSEL_RC32M_gc = (0x01<<0),  /* Internal 32 MHz RC Oscillator */
    CLK_SCLKSEL_RC32K_gc = (0x02<<0),  /* Internal 32.768 kHz RC Oscillator */
    CLK_SCLKSEL_XOSC_gc = (0x03<<0),  /* External Crystal Oscillator or Clock */
    CLK_SCLKSEL_PLL_gc = (0x04<<0),  /* Phase Locked Loop */
} CLK_SCLKSEL_t;

/* USB Prescaler Division Factor */
typedef enum CLK_USBPSDIV_enum
{
    CLK_USBPSDIV_1_gc = (0x00<<3),  /* Divide by 1 */
    CLK_USBPSDIV_2_gc = (0x01<<3),  /* Divide by 2 */
    CLK_USBPSDIV_4_gc = (0x02<<3),  /* Divide by 4 */
    CLK_USBPSDIV_8_gc = (0x03<<3),  /* Divide by 8 */
    CLK_USBPSDIV_16_gc = (0x04<<3),  /* Divide by 16 */
    CLK_USBPSDIV_32_gc = (0x05<<3),  /* Divide by 32 */
} CLK_USBPSDIV_t;

/* USB Clock Source */
typedef enum CLK_USBSRC_enum
{
    CLK_USBSRC_PLL_gc = (0x00<<1),  /* PLL */
    CLK_USBSRC_RC32M_gc = (0x01<<1),  /* Internal 32 MHz RC Oscillator */
} CLK_USBSRC_t;

/*
--------------------------------------------------------------------------
CPU - CPU
--------------------------------------------------------------------------
*/

/* CCP signatures */
typedef enum CCP_enum
{
    CCP_SPM_gc = (0x9D<<0),  /* SPM Instruction Protection */
    CCP_IOREG_gc = (0xD8<<0),  /* IO Register Protection */
} CCP_t;

/*
--------------------------------------------------------------------------
CRC - Cyclic Redundancy Checker
--------------------------------------------------------------------------
*/

/* Cyclic Redundancy Checker */
typedef struct CRC_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t STATUS;  /* Status Register */
    register8_t reserved_1[1];
    register8_t DATAIN;  /* Data Input */
    register8_t CHECKSUM0;  /* Checksum byte 0 */
    register8_t CHECKSUM1;  /* Checksum byte 1 */
    register8_t CHECKSUM2;  /* Checksum byte 2 */
    register8_t CHECKSUM3;  /* Checksum byte 3 */
} CRC_t;

/* Reset */
typedef enum CRC_RESET_enum
{
    CRC_RESET_NO_gc = (0x00<<6),  /* No Reset */
    CRC_RESET_RESET0_gc = (0x02<<6),  /* Reset CRC with CHECKSUM to all zeros */
    CRC_RESET_RESET1_gc = (0x03<<6),  /* Reset CRC with CHECKSUM to all ones */
} CRC_RESET_t;

/* Input Source */
typedef enum CRC_SOURCE_enum
{
    CRC_SOURCE_DISABLE_gc = (0x00<<0),  /* Disabled */
    CRC_SOURCE_IO_gc = (0x01<<0),  /* I/O Interface */
    CRC_SOURCE_FLASH_gc = (0x02<<0),  /* Flash */
    CRC_SOURCE_DMAC0_gc = (0x04<<0),  /* DMAC Channel 0 */
    CRC_SOURCE_DMAC1_gc = (0x05<<0),  /* DMAC Channel 1 */
} CRC_SOURCE_t;

/*
--------------------------------------------------------------------------
DFLL - DFLL
--------------------------------------------------------------------------
*/

/* DFLL */
typedef struct DFLL_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t reserved_1[1];
    register8_t CALA;  /* Calibration Register A */
    register8_t CALB;  /* Calibration Register B */
    register8_t COMP0;  /* Oscillator Compare Register 0 */
    register8_t COMP1;  /* Oscillator Compare Register 1 */
    register8_t COMP2;  /* Oscillator Compare Register 2 */
    register8_t reserved_2[1];
} DFLL_t;


/*
--------------------------------------------------------------------------
DMA - DMA Controller
--------------------------------------------------------------------------
*/

/* DMA Channel */
typedef struct DMA_CH_struct
{
    register8_t CTRLA;  /* Channel Control */
    register8_t CTRLB;  /* Channel Control */
    register8_t ADDRCTRL;  /* Address Control */
    register8_t TRIGSRC;  /* Channel Trigger Source */
    _WORDREGISTER(TRFCNT);  /* Channel Block Transfer Count */
    register8_t REPCNT;  /* Channel Repeat Count */
    register8_t reserved_1[1];
    register8_t SRCADDR0;  /* Channel Source Address 0 */
    register8_t SRCADDR1;  /* Channel Source Address 1 */
    register8_t reserved_2[2];
    register8_t DESTADDR0;  /* Channel Destination Address 0 */
    register8_t DESTADDR1;  /* Channel Destination Address 1 */
    register8_t reserved_3[2];
} DMA_CH_t;


/* DMA Controller */
typedef struct DMA_struct
{
    register8_t CTRL;  /* Control */
    register8_t reserved_1[2];
    register8_t INTFLAGS;  /* Transfer Interrupt Status */
    register8_t STATUS;  /* Status */
    register8_t reserved_2[1];
    _WORDREGISTER(TEMP);  /* Temporary Register For 16-bit Access */
    register8_t reserved_3[8];
    DMA_CH_t CH0;  /* DMA Channel 0 */
    DMA_CH_t CH1;  /* DMA Channel 1 */
} DMA_t;

/* Burst mode */
typedef enum DMA_CH_BURSTLEN_enum
{
    DMA_CH_BURSTLEN_1BYTE_gc = (0x00<<0),  /* 1-byte burst mode */
    DMA_CH_BURSTLEN_2BYTE_gc = (0x01<<0),  /* 2-byte burst mode */
    DMA_CH_BURSTLEN_4BYTE_gc = (0x02<<0),  /* 4-byte burst mode */
    DMA_CH_BURSTLEN_8BYTE_gc = (0x03<<0),  /* 8-byte burst mode */
} DMA_CH_BURSTLEN_t;

/* Destination addressing mode */
typedef enum DMA_CH_DESTDIR_enum
{
    DMA_CH_DESTDIR_FIXED_gc = (0x00<<0),  /* Fixed */
    DMA_CH_DESTDIR_INC_gc = (0x01<<0),  /* Increment */
    DMA_CH_DESTDIR_DEC_gc = (0x02<<0),  /* Decrement */
} DMA_CH_DESTDIR_t;

/* Destination address reload mode */
typedef enum DMA_CH_DESTRELOAD_enum
{
    DMA_CH_DESTRELOAD_NONE_gc = (0x00<<2),  /* No reload */
    DMA_CH_DESTRELOAD_BLOCK_gc = (0x01<<2),  /* Reload at end of block */
    DMA_CH_DESTRELOAD_BURST_gc = (0x02<<2),  /* Reload at end of burst */
    DMA_CH_DESTRELOAD_TRANSACTION_gc = (0x03<<2),  /* Reload at end of transaction */
} DMA_CH_DESTRELOAD_t;

/* Interrupt level */
typedef enum DMA_CH_ERRINTLVL_enum
{
    DMA_CH_ERRINTLVL_OFF_gc = (0x00<<2),  /* Interrupt disabled */
    DMA_CH_ERRINTLVL_LO_gc = (0x01<<2),  /* Low level */
    DMA_CH_ERRINTLVL_MED_gc = (0x02<<2),  /* Medium level */
    DMA_CH_ERRINTLVL_HI_gc = (0x03<<2),  /* High level */
} DMA_CH_ERRINTLVL_t;

/* Source addressing mode */
typedef enum DMA_CH_SRCDIR_enum
{
    DMA_CH_SRCDIR_FIXED_gc = (0x00<<4),  /* Fixed */
    DMA_CH_SRCDIR_INC_gc = (0x01<<4),  /* Increment */
    DMA_CH_SRCDIR_DEC_gc = (0x02<<4),  /* Decrement */
} DMA_CH_SRCDIR_t;

/* Source address reload mode */
typedef enum DMA_CH_SRCRELOAD_enum
{
    DMA_CH_SRCRELOAD_NONE_gc = (0x00<<6),  /* No reload */
    DMA_CH_SRCRELOAD_BLOCK_gc = (0x01<<6),  /* Reload at end of block */
    DMA_CH_SRCRELOAD_BURST_gc = (0x02<<6),  /* Reload at end of burst */
    DMA_CH_SRCRELOAD_TRANSACTION_gc = (0x03<<6),  /* Reload at end of transaction */
} DMA_CH_SRCRELOAD_t;

/* Transfer trigger source */
typedef enum DMA_CH_TRIGSRC_enum
{
    DMA_CH_TRIGSRC_OFF_gc = (0x00<<0),  /* Off software triggers only */
    DMA_CH_TRIGSRC_EVSYS_CH0_gc = (0x01<<0),  /* Event System Channel 0 */
    DMA_CH_TRIGSRC_EVSYS_CH1_gc = (0x02<<0),  /* Event System Channel 1 */
    DMA_CH_TRIGSRC_EVSYS_CH2_gc = (0x03<<0),  /* Event System Channel 2 */
    DMA_CH_TRIGSRC_AES_gc = (0x04<<0),  /* AES */
    DMA_CH_TRIGSRC_ADCA_CH0_gc = (0x10<<0),  /* ADCA Channel 0 */
    DMA_CH_TRIGSRC_ADCB_CH0_gc = (0x20<<0),  /* ADCB Channel 0 */
    DMA_CH_TRIGSRC_TCC0_OVF_gc = (0x40<<0),  /* Timer/Counter C0 Overflow */
    DMA_CH_TRIGSRC_TCC0_ERR_gc = (0x41<<0),  /* Timer/Counter C0 Error */
    DMA_CH_TRIGSRC_TCC0_CCA_gc = (0x42<<0),  /* Timer/Counter C0 Compare or Capture A */
    DMA_CH_TRIGSRC_TCC0_CCB_gc = (0x43<<0),  /* Timer/Counter C0 Compare or Capture B */
    DMA_CH_TRIGSRC_TCC0_CCC_gc = (0x44<<0),  /* Timer/Counter C0 Compare or Capture C */
    DMA_CH_TRIGSRC_TCC0_CCD_gc = (0x45<<0),  /* Timer/Counter C0 Compare or Capture D */
    DMA_CH_TRIGSRC_TCC1_OVF_gc = (0x46<<0),  /* Timer/Counter C1 Overflow */
    DMA_CH_TRIGSRC_TCC1_ERR_gc = (0x47<<0),  /* Timer/Counter C1 Error */
    DMA_CH_TRIGSRC_TCC1_CCA_gc = (0x48<<0),  /* Timer/Counter C1 Compare or Capture A */
    DMA_CH_TRIGSRC_TCC1_CCB_gc = (0x49<<0),  /* Timer/Counter C1 Compare or Capture B */
    DMA_CH_TRIGSRC_SPIC_gc = (0x4A<<0),  /* SPI C Transfer Complete */
    DMA_CH_TRIGSRC_USARTC0_RXC_gc = (0x4B<<0),  /* USART C0 Receive Complete */
    DMA_CH_TRIGSRC_USARTC0_DRE_gc = (0x4C<<0),  /* USART C0 Data Register Empty */
    DMA_CH_TRIGSRC_TCE0_OVF_gc = (0x80<<0),  /* Timer/Counter E0 Overflow */
    DMA_CH_TRIGSRC_TCE0_ERR_gc = (0x81<<0),  /* Timer/Counter E0 Error */
    DMA_CH_TRIGSRC_TCE0_CCA_gc = (0x82<<0),  /* Timer/Counter E0 Compare or Capture A */
    DMA_CH_TRIGSRC_TCE0_CCB_gc = (0x83<<0),  /* Timer/Counter E0 Compare or Capture B */
    DMA_CH_TRIGSRC_TCE0_CCC_gc = (0x84<<0),  /* Timer/Counter E0 Compare or Capture C */
    DMA_CH_TRIGSRC_TCE0_CCD_gc = (0x85<<0),  /* Timer/Counter E0 Compare or Capture D */
    DMA_CH_TRIGSRC_USARTE0_RXC_gc = (0x8B<<0),  /* USART E0 Receive Complete */
    DMA_CH_TRIGSRC_USARTE0_DRE_gc = (0x8C<<0),  /* USART E0 Data Register Empty */
} DMA_CH_TRIGSRC_t;

/* Interrupt level */
typedef enum DMA_CH_TRNINTLVL_enum
{
    DMA_CH_TRNINTLVL_OFF_gc = (0x00<<0),  /* Interrupt disabled */
    DMA_CH_TRNINTLVL_LO_gc = (0x01<<0),  /* Low level */
    DMA_CH_TRNINTLVL_MED_gc = (0x02<<0),  /* Medium level */
    DMA_CH_TRNINTLVL_HI_gc = (0x03<<0),  /* High level */
} DMA_CH_TRNINTLVL_t;

/* Double buffering mode */
typedef enum DMA_DBUFMODE_enum
{
    DMA_DBUFMODE_DISABLED_gc = (0x00<<2),  /* Double buffering disabled */
    DMA_DBUFMODE_CH01_gc = (0x01<<2),  /* Double buffering enabled on channel 0/1 */
} DMA_DBUFMODE_t;

/* Priority mode */
typedef enum DMA_PRIMODE_enum
{
    DMA_PRIMODE_RR01_gc = (0x00<<0),  /* Round Robin */
    DMA_PRIMODE_CH0RR1_gc = (0x01<<0),  /* Channel 0 > channel 1 */
} DMA_PRIMODE_t;

/*
--------------------------------------------------------------------------
EVSYS - Event System
--------------------------------------------------------------------------
*/

/* Event System */
typedef struct EVSYS_struct
{
    register8_t CH0MUX;  /* Event Channel 0 Multiplexer */
    register8_t CH1MUX;  /* Event Channel 1 Multiplexer */
    register8_t CH2MUX;  /* Event Channel 2 Multiplexer */
    register8_t CH3MUX;  /* Event Channel 3 Multiplexer */
    register8_t reserved_1[4];
    register8_t CH0CTRL;  /* Channel 0 Control Register */
    register8_t CH1CTRL;  /* Channel 1 Control Register */
    register8_t CH2CTRL;  /* Channel 2 Control Register */
    register8_t CH3CTRL;  /* Channel 3 Control Register */
    register8_t reserved_2[4];
    register8_t STROBE;  /* Event Strobe */
    register8_t DATA;  /* Event Data */
} EVSYS_t;

/* Event Channel multiplexer input selection */
typedef enum EVSYS_CHMUX_enum
{
    EVSYS_CHMUX_OFF_gc = (0x00<<0),  /* Off */
    EVSYS_CHMUX_RTC_OVF_gc = (0x08<<0),  /* RTC Overflow */
    EVSYS_CHMUX_RTC_CMP_gc = (0x09<<0),  /* RTC Compare Match */
    EVSYS_CHMUX_USB_gc = (0x0A<<0),  /* USB Setup, SOF, CRC error and UNF/OVF */
    EVSYS_CHMUX_ACA_CH0_gc = (0x10<<0),  /* Analog Comparator A Channel 0 */
    EVSYS_CHMUX_ACA_CH1_gc = (0x11<<0),  /* Analog Comparator A Channel 1 */
    EVSYS_CHMUX_ACA_WIN_gc = (0x12<<0),  /* Analog Comparator A Window */
    EVSYS_CHMUX_ACB_CH0_gc = (0x13<<0),  /* Analog Comparator B Channel 0 */
    EVSYS_CHMUX_ACB_CH1_gc = (0x14<<0),  /* Analog Comparator B Channel 1 */
    EVSYS_CHMUX_ACB_WIN_gc = (0x15<<0),  /* Analog Comparator B Window */
    EVSYS_CHMUX_ADCA_CH0_gc = (0x20<<0),  /* ADC A Channel */
    EVSYS_CHMUX_ADCB_CH0_gc = (0x24<<0),  /* ADC B Channel */
    EVSYS_CHMUX_PORTA_PIN0_gc = (0x50<<0),  /* Port A, Pin0 */
    EVSYS_CHMUX_PORTA_PIN1_gc = (0x51<<0),  /* Port A, Pin1 */
    EVSYS_CHMUX_PORTA_PIN2_gc = (0x52<<0),  /* Port A, Pin2 */
    EVSYS_CHMUX_PORTA_PIN3_gc = (0x53<<0),  /* Port A, Pin3 */
    EVSYS_CHMUX_PORTA_PIN4_gc = (0x54<<0),  /* Port A, Pin4 */
    EVSYS_CHMUX_PORTA_PIN5_gc = (0x55<<0),  /* Port A, Pin5 */
    EVSYS_CHMUX_PORTA_PIN6_gc = (0x56<<0),  /* Port A, Pin6 */
    EVSYS_CHMUX_PORTA_PIN7_gc = (0x57<<0),  /* Port A, Pin7 */
    EVSYS_CHMUX_PORTB_PIN0_gc = (0x58<<0),  /* Port B, Pin0 */
    EVSYS_CHMUX_PORTB_PIN1_gc = (0x59<<0),  /* Port B, Pin1 */
    EVSYS_CHMUX_PORTB_PIN2_gc = (0x5A<<0),  /* Port B, Pin2 */
    EVSYS_CHMUX_PORTB_PIN3_gc = (0x5B<<0),  /* Port B, Pin3 */
    EVSYS_CHMUX_PORTB_PIN4_gc = (0x5C<<0),  /* Port B, Pin4 */
    EVSYS_CHMUX_PORTB_PIN5_gc = (0x5D<<0),  /* Port B, Pin5 */
    EVSYS_CHMUX_PORTB_PIN6_gc = (0x5E<<0),  /* Port B, Pin6 */
    EVSYS_CHMUX_PORTB_PIN7_gc = (0x5F<<0),  /* Port B, Pin7 */
    EVSYS_CHMUX_PORTC_PIN0_gc = (0x60<<0),  /* Port C, Pin0 */
    EVSYS_CHMUX_PORTC_PIN1_gc = (0x61<<0),  /* Port C, Pin1 */
    EVSYS_CHMUX_PORTC_PIN2_gc = (0x62<<0),  /* Port C, Pin2 */
    EVSYS_CHMUX_PORTC_PIN3_gc = (0x63<<0),  /* Port C, Pin3 */
    EVSYS_CHMUX_PORTC_PIN4_gc = (0x64<<0),  /* Port C, Pin4 */
    EVSYS_CHMUX_PORTC_PIN5_gc = (0x65<<0),  /* Port C, Pin5 */
    EVSYS_CHMUX_PORTC_PIN6_gc = (0x66<<0),  /* Port C, Pin6 */
    EVSYS_CHMUX_PORTC_PIN7_gc = (0x67<<0),  /* Port C, Pin7 */
    EVSYS_CHMUX_PORTD_PIN0_gc = (0x68<<0),  /* Port D, Pin0 */
    EVSYS_CHMUX_PORTD_PIN1_gc = (0x69<<0),  /* Port D, Pin1 */
    EVSYS_CHMUX_PORTD_PIN2_gc = (0x6A<<0),  /* Port D, Pin2 */
    EVSYS_CHMUX_PORTE_PIN0_gc = (0x70<<0),  /* Port E, Pin0 */
    EVSYS_CHMUX_PORTE_PIN1_gc = (0x71<<0),  /* Port E, Pin1 */
    EVSYS_CHMUX_PORTE_PIN2_gc = (0x72<<0),  /* Port E, Pin2 */
    EVSYS_CHMUX_PORTE_PIN3_gc = (0x73<<0),  /* Port E, Pin3 */
    EVSYS_CHMUX_PORTE_PIN4_gc = (0x74<<0),  /* Port E, Pin4 */
    EVSYS_CHMUX_PORTE_PIN5_gc = (0x75<<0),  /* Port E, Pin5 */
    EVSYS_CHMUX_PORTE_PIN6_gc = (0x76<<0),  /* Port E, Pin6 */
    EVSYS_CHMUX_PORTE_PIN7_gc = (0x77<<0),  /* Port E, Pin7 */
    EVSYS_CHMUX_PRESCALER_1_gc = (0x80<<0),  /* Prescaler, divide by 1 */
    EVSYS_CHMUX_PRESCALER_2_gc = (0x81<<0),  /* Prescaler, divide by 2 */
    EVSYS_CHMUX_PRESCALER_4_gc = (0x82<<0),  /* Prescaler, divide by 4 */
    EVSYS_CHMUX_PRESCALER_8_gc = (0x83<<0),  /* Prescaler, divide by 8 */
    EVSYS_CHMUX_PRESCALER_16_gc = (0x84<<0),  /* Prescaler, divide by 16 */
    EVSYS_CHMUX_PRESCALER_32_gc = (0x85<<0),  /* Prescaler, divide by 32 */
    EVSYS_CHMUX_PRESCALER_64_gc = (0x86<<0),  /* Prescaler, divide by 64 */
    EVSYS_CHMUX_PRESCALER_128_gc = (0x87<<0),  /* Prescaler, divide by 128 */
    EVSYS_CHMUX_PRESCALER_256_gc = (0x88<<0),  /* Prescaler, divide by 256 */
    EVSYS_CHMUX_PRESCALER_512_gc = (0x89<<0),  /* Prescaler, divide by 512 */
    EVSYS_CHMUX_PRESCALER_1024_gc = (0x8A<<0),  /* Prescaler, divide by 1024 */
    EVSYS_CHMUX_PRESCALER_2048_gc = (0x8B<<0),  /* Prescaler, divide by 2048 */
    EVSYS_CHMUX_PRESCALER_4096_gc = (0x8C<<0),  /* Prescaler, divide by 4096 */
    EVSYS_CHMUX_PRESCALER_8192_gc = (0x8D<<0),  /* Prescaler, divide by 8192 */
    EVSYS_CHMUX_PRESCALER_16384_gc = (0x8E<<0),  /* Prescaler, divide by 16384 */
    EVSYS_CHMUX_PRESCALER_32768_gc = (0x8F<<0),  /* Prescaler, divide by 32768 */
    EVSYS_CHMUX_TCC0_OVF_gc = (0xC0<<0),  /* Timer/Counter C0 Overflow */
    EVSYS_CHMUX_TCC0_ERR_gc = (0xC1<<0),  /* Timer/Counter C0 Error */
    EVSYS_CHMUX_TCC0_CCA_gc = (0xC4<<0),  /* Timer/Counter C0 Compare or Capture A */
    EVSYS_CHMUX_TCC0_CCB_gc = (0xC5<<0),  /* Timer/Counter C0 Compare or Capture B */
    EVSYS_CHMUX_TCC0_CCC_gc = (0xC6<<0),  /* Timer/Counter C0 Compare or Capture C */
    EVSYS_CHMUX_TCC0_CCD_gc = (0xC7<<0),  /* Timer/Counter C0 Compare or Capture D */
    EVSYS_CHMUX_TCC1_OVF_gc = (0xC8<<0),  /* Timer/Counter C1 Overflow */
    EVSYS_CHMUX_TCC1_ERR_gc = (0xC9<<0),  /* Timer/Counter C1 Error */
    EVSYS_CHMUX_TCC1_CCA_gc = (0xCC<<0),  /* Timer/Counter C1 Compare or Capture A */
    EVSYS_CHMUX_TCC1_CCB_gc = (0xCD<<0),  /* Timer/Counter C1 Compare or Capture B */
    EVSYS_CHMUX_TCE0_OVF_gc = (0xE0<<0),  /* Timer/Counter E0 Overflow */
    EVSYS_CHMUX_TCE0_ERR_gc = (0xE1<<0),  /* Timer/Counter E0 Error */
    EVSYS_CHMUX_TCE0_CCA_gc = (0xE4<<0),  /* Timer/Counter E0 Compare or Capture A */
    EVSYS_CHMUX_TCE0_CCB_gc = (0xE5<<0),  /* Timer/Counter E0 Compare or Capture B */
    EVSYS_CHMUX_TCE0_CCC_gc = (0xE6<<0),  /* Timer/Counter E0 Compare or Capture C */
    EVSYS_CHMUX_TCE0_CCD_gc = (0xE7<<0),  /* Timer/Counter E0 Compare or Capture D */
} EVSYS_CHMUX_t;

/* Digital filter coefficient */
typedef enum EVSYS_DIGFILT_enum
{
    EVSYS_DIGFILT_1SAMPLE_gc = (0x00<<0),  /* 1 SAMPLE */
    EVSYS_DIGFILT_2SAMPLES_gc = (0x01<<0),  /* 2 SAMPLES */
    EVSYS_DIGFILT_3SAMPLES_gc = (0x02<<0),  /* 3 SAMPLES */
    EVSYS_DIGFILT_4SAMPLES_gc = (0x03<<0),  /* 4 SAMPLES */
    EVSYS_DIGFILT_5SAMPLES_gc = (0x04<<0),  /* 5 SAMPLES */
    EVSYS_DIGFILT_6SAMPLES_gc = (0x05<<0),  /* 6 SAMPLES */
    EVSYS_DIGFILT_7SAMPLES_gc = (0x06<<0),  /* 7 SAMPLES */
    EVSYS_DIGFILT_8SAMPLES_gc = (0x07<<0),  /* 8 SAMPLES */
} EVSYS_DIGFILT_t;

/* Quadrature Decoder Index Recognition Mode */
typedef enum EVSYS_QDIRM_enum
{
    EVSYS_QDIRM_00_gc = (0x00<<5),  /* QDPH0 = 0, QDPH90 = 0 */
    EVSYS_QDIRM_01_gc = (0x01<<5),  /* QDPH0 = 0, QDPH90 = 1 */
    EVSYS_QDIRM_10_gc = (0x02<<5),  /* QDPH0 = 1, QDPH90 = 0 */
    EVSYS_QDIRM_11_gc = (0x03<<5),  /* QDPH0 = 1, QDPH90 = 1 */
} EVSYS_QDIRM_t;

/*
--------------------------------------------------------------------------
FUSE - Fuses and Lockbits
--------------------------------------------------------------------------
*/

/* Fuses */
typedef struct NVM_FUSES_struct
{
    register8_t FUSEBYTE0;  /* JTAG User ID */
    register8_t FUSEBYTE1;  /* Watchdog Configuration */
    register8_t FUSEBYTE2;  /* Reset Configuration */
    register8_t reserved_1[1];
    register8_t FUSEBYTE4;  /* Start-up Configuration */
    register8_t FUSEBYTE5;  /* EESAVE and BOD Level */
} NVM_FUSES_t;

/* BOD operation */
typedef enum BODACT_enum
{
    BODACT_SAMPLED_gc = (0x01<<4),  /* BOD enabled in sampled mode */
    BODACT_CONTINUOUS_gc = (0x02<<4),  /* BOD enabled continuously */
    BODACT_DISABLED_gc = (0x03<<4),  /* BOD Disabled */
} BODACT_t;

/* Brownout Detection Voltage Level */
typedef enum BODLEVEL_enum
{
    BODLEVEL_3V0_gc = (0x00<<0),  /* 3.0 V */
    BODLEVEL_2V8_gc = (0x01<<0),  /* 2.8 V */
    BODLEVEL_2V6_gc = (0x02<<0),  /* 2.6 V */
    BODLEVEL_2V4_gc = (0x03<<0),  /* 2.4 V */
    BODLEVEL_2V2_gc = (0x04<<0),  /* 2.2 V */
    BODLEVEL_2V0_gc = (0x05<<0),  /* 2.0 V */
    BODLEVEL_1V8_gc = (0x06<<0),  /* 1.8 V */
    BODLEVEL_1V6_gc = (0x07<<0),  /* 1.6 V */
} BODLEVEL_t;

/* BOD operation */
typedef enum BODPD_enum
{
    BODPD_SAMPLED_gc = (0x01<<0),  /* BOD enabled in sampled mode */
    BODPD_CONTINUOUS_gc = (0x02<<0),  /* BOD enabled continuously */
    BODPD_DISABLED_gc = (0x03<<0),  /* BOD Disabled */
} BODPD_t;

/* Boot Loader Section Reset Vector */
typedef enum BOOTRST_enum
{
    BOOTRST_BOOTLDR_gc = (0x00<<6),  /* Boot Loader Reset */
    BOOTRST_APPLICATION_gc = (0x01<<6),  /* Application Reset */
} BOOTRST_t;

/* Start-up Time */
typedef enum STARTUPTIME_enum
{
    STARTUPTIME_64MS_gc = (0x00<<2),  /* 64 ms */
    STARTUPTIME_4MS_gc = (0x01<<2),  /* 4 ms */
    STARTUPTIME_0MS_gc = (0x03<<2),  /* 0 ms */
} STARTUPTIME_t;

/* Timer Oscillator pin location */
typedef enum TOSCSEL_enum
{
    TOSCSEL_ALTERNATE_gc = (0x00<<5),  /* TOSC1 / TOSC2 on separate pins */
    TOSCSEL_XTAL_gc = (0x01<<5),  /* TOSC1 / TOSC2 shared with XTAL1 / XTAL2 */
} TOSCSEL_t;

/* Watchdog (Window) Timeout Period */
typedef enum WDPER_enum
{
    WDPER_8CLK_gc = (0x00<<0),  /* 8 cycles (8ms @ 3.3V) */
    WDPER_16CLK_gc = (0x01<<0),  /* 16 cycles (16ms @ 3.3V) */
    WDPER_32CLK_gc = (0x02<<0),  /* 32 cycles (32ms @ 3.3V) */
    WDPER_64CLK_gc = (0x03<<0),  /* 64 cycles (64ms @ 3.3V) */
    WDPER_128CLK_gc = (0x04<<0),  /* 128 cycles (0.125s @ 3.3V) */
    WDPER_256CLK_gc = (0x05<<0),  /* 256 cycles (0.25s @ 3.3V) */
    WDPER_512CLK_gc = (0x06<<0),  /* 512 cycles (0.5s @ 3.3V) */
    WDPER_1KCLK_gc = (0x07<<0),  /* 1K cycles (1s @ 3.3V) */
    WDPER_2KCLK_gc = (0x08<<0),  /* 2K cycles (2s @ 3.3V) */
    WDPER_4KCLK_gc = (0x09<<0),  /* 4K cycles (4s @ 3.3V) */
    WDPER_8KCLK_gc = (0x0A<<0),  /* 8K cycles (8s @ 3.3V) */
} WDPER_t;

/* Watchdog (Window) Timeout Period */
typedef enum WDWPER_enum
{
    WDWPER_8CLK_gc = (0x00<<4),  /* 8 cycles (8ms @ 3.3V) */
    WDWPER_16CLK_gc = (0x01<<4),  /* 16 cycles (16ms @ 3.3V) */
    WDWPER_32CLK_gc = (0x02<<4),  /* 32 cycles (32ms @ 3.3V) */
    WDWPER_64CLK_gc = (0x03<<4),  /* 64 cycles (64ms @ 3.3V) */
    WDWPER_128CLK_gc = (0x04<<4),  /* 128 cycles (0.125s @ 3.3V) */
    WDWPER_256CLK_gc = (0x05<<4),  /* 256 cycles (0.25s @ 3.3V) */
    WDWPER_512CLK_gc = (0x06<<4),  /* 512 cycles (0.5s @ 3.3V) */
    WDWPER_1KCLK_gc = (0x07<<4),  /* 1K cycles (1s @ 3.3V) */
    WDWPER_2KCLK_gc = (0x08<<4),  /* 2K cycles (2s @ 3.3V) */
    WDWPER_4KCLK_gc = (0x09<<4),  /* 4K cycles (4s @ 3.3V) */
    WDWPER_8KCLK_gc = (0x0A<<4),  /* 8K cycles (8s @ 3.3V) */
} WDWPER_t;

/*
--------------------------------------------------------------------------
HIRES - Timer/Counter High-Resolution Extension
--------------------------------------------------------------------------
*/

/* High-Resolution Extension */
typedef struct HIRES_struct
{
    register8_t CTRLA;  /* Control Register */
} HIRES_t;

/* High Resolution Enable */
typedef enum HIRES_HREN_enum
{
    HIRES_HREN_NONE_gc = (0x00<<0),  /* No Fault Protection */
    HIRES_HREN_TC0_gc = (0x01<<0),  /* Enable High Resolution on Timer/Counter 0 */
    HIRES_HREN_TC1_gc = (0x02<<0),  /* Enable High Resolution on Timer/Counter 1 */
    HIRES_HREN_BOTH_gc = (0x03<<0),  /* Enable High Resolution both Timer/Counters */
} HIRES_HREN_t;

/*
--------------------------------------------------------------------------
IRCOM - IR Communication Module
--------------------------------------------------------------------------
*/

/* IR Communication Module */
typedef struct IRCOM_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t TXPLCTRL;  /* IrDA Transmitter Pulse Length Control Register */
    register8_t RXPLCTRL;  /* IrDA Receiver Pulse Length Control Register */
} IRCOM_t;

/* Event channel selection */
typedef enum IRCOM_EVSEL_enum
{
    IRCOM_EVSEL_OFF_gc = (0x00<<0),  /* No Event Source */
    IRCOM_EVSEL_0_gc = (0x08<<0),  /* Event Channel 0 */
    IRCOM_EVSEL_1_gc = (0x09<<0),  /* Event Channel 1 */
    IRCOM_EVSEL_2_gc = (0x0A<<0),  /* Event Channel 2 */
    IRCOM_EVSEL_3_gc = (0x0B<<0),  /* Event Channel 3 */
} IRCOM_EVSEL_t;

/*
--------------------------------------------------------------------------
LCD - LCD Controller
--------------------------------------------------------------------------
*/

/* LCD Controller */
typedef struct LCD_struct
{
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t CTRLC;  /* Control Register C */
    register8_t INTCTRL;  /* Interrupt Enable Register */
    register8_t INTFLAG;  /* Interrupt Flag Register */
    register8_t CTRLD;  /* Control Register D */
    register8_t CTRLE;  /* Control Register E */
    register8_t CTRLF;  /* Control Register F */
    register8_t CTRLG;  /* Control Register G */
    register8_t CTRLH;  /* Control Register H */
    register8_t reserved_1[6];
    register8_t DATA0;  /* LCD Data Register 0 */
    register8_t DATA1;  /* LCD Data Register 1 */
    register8_t DATA2;  /* LCD Data Register 2 */
    register8_t DATA3;  /* LCD Data Register 3 */
    register8_t DATA4;  /* LCD Data Register 4 */
    register8_t DATA5;  /* LCD Data Register 5 */
    register8_t DATA6;  /* LCD Data Register 6 */
    register8_t DATA7;  /* LCD Data Register 7 */
    register8_t DATA8;  /* LCD Data Register 8 */
    register8_t DATA9;  /* LCD Data Register 9 */
    register8_t DATA10;  /* LCD Data Register 10 */
    register8_t DATA11;  /* LCD Data Register 11 */
    register8_t DATA12;  /* LCD Data Register 12 */
    register8_t DATA13;  /* LCD Data Register 13 */
    register8_t DATA14;  /* LCD Data Register 14 */
    register8_t DATA15;  /* LCD Data Register 15 */
    register8_t DATA16;  /* LCD Data Register 16 */
    register8_t DATA17;  /* LCD Data Register 17 */
    register8_t DATA18;  /* LCD Data Register 18 */
    register8_t DATA19;  /* LCD Data Register 19 */
} LCD_t;

/* LCD Blink Rate */
typedef enum LCD_BLINKRATE_enum
{
    LCD_BLINKRATE_4Hz_gc = (0x00<<0),  /* 4Hz Blink Rate */
    LCD_BLINKRATE_2Hz_gc = (0x01<<0),  /* 2Hz Blink Rate */
    LCD_BLINKRATE_1Hz_gc = (0x02<<0),  /* 1Hz Blink Rate */
    LCD_BLINKRATE_0Hz5_gc = (0x03<<0),  /* 0.5Hz Blink Rate */
} LCD_BLINKRATE_t;

/* LCD Clock Divide */
typedef enum LCD_CLKDIV_enum
{
    LCD_CLKDIV_DivBy1_gc = (0x00<<4),  /* frame rate of 256 Hz */
    LCD_CLKDIV_DivBy2_gc = (0x01<<4),  /* frame rate of 128 Hz */
    LCD_CLKDIV_DivBy3_gc = (0x02<<4),  /* frame rate of 83.5 Hz */
    LCD_CLKDIV_DivBy4_gc = (0x03<<4),  /* frame rate of 64 Hz */
    LCD_CLKDIV_DivBy5_gc = (0x04<<4),  /* frame rate of 51.2 Hz */
    LCD_CLKDIV_DivBy6_gc = (0x05<<4),  /* frame rate of 42.7 Hz */
    LCD_CLKDIV_DivBy7_gc = (0x06<<4),  /* frame rate of 36.6 Hz */
    LCD_CLKDIV_DivBy8_gc = (0x07<<4),  /* frame rate of 32 Hz */
} LCD_CLKDIV_t;

/* Duty Select */
typedef enum LCD_DUTY_enum
{
    LCD_DUTY_1_4_gc = (0x00<<0),  /* Duty=1/4, Bias=1/3, COM0:3 */
    LCD_DUTY_Static_gc = (0x01<<0),  /* Duty=Static, Bias=Static, COM0 */
    LCD_DUTY_1_2_gc = (0x02<<0),  /* Duty=1/2, Bias=1/3, COM0:1 */
    LCD_DUTY_1_3_gc = (0x03<<0),  /* Duty=1/3, Bias=1/3, COM0:2 */
} LCD_DUTY_t;

/* Interrupt level */
typedef enum LCD_FCINTLVL_enum
{
    LCD_FCINTLVL_OFF_gc = (0x00<<0),  /* Interrupt disabled */
    LCD_FCINTLVL_LO_gc = (0x01<<0),  /* Low level */
    LCD_FCINTLVL_MED_gc = (0x02<<0),  /* Medium level */
    LCD_FCINTLVL_HI_gc = (0x03<<0),  /* High level */
} LCD_FCINTLVL_t;

/* LCD Prescaler Select */
typedef enum LCD_PRESC_enum
{
    LCD_PRESC_8_gc = (0x00<<7),  /* clk_lcd/8 */
    LCD_PRESC_16_gc = (0x01<<7),  /* clk_lcd/16 */
} LCD_PRESC_t;

/* Type of Digit */
typedef enum LCD_TDG_enum
{
    LCD_TDG_7S_3C_gc = (0x00<<6),  /* 7-segment with 3 COMs */
    LCD_TDG_7S_4C_gc = (0x01<<6),  /* 7-segment with 4 COMs */
    LCD_TDG_14S_4C_gc = (0x02<<6),  /* 14-segment with 4 COMs */
    LCD_TDG_16S_3C_gc = (0x03<<6),  /* 16-segment with 3 COMs */
} LCD_TDG_t;

/*
--------------------------------------------------------------------------
LOCKBIT - Fuses and Lockbits
--------------------------------------------------------------------------
*/

/* Lock Bits */
typedef struct NVM_LOCKBITS_struct
{
    register8_t LOCK_BITS;  /* Lock Bits (Changed from LOCKBITS to avoid avr-libc collision) */
} NVM_LOCKBITS_t;

/* Boot lock bits - application section */
typedef enum BLBA_enum
{
    BLBA_RWLOCK_gc = (0x00<<4),  /* Read and write not allowed */
    BLBA_RLOCK_gc = (0x01<<4),  /* Read not allowed */
    BLBA_WLOCK_gc = (0x02<<4),  /* Write not allowed */
    BLBA_NOLOCK_gc = (0x03<<4),  /* No locks */
} BLBA_t;

/* Boot lock bits - application table section */
typedef enum BLBAT_enum
{
    BLBAT_RWLOCK_gc = (0x00<<2),  /* Read and write not allowed */
    BLBAT_RLOCK_gc = (0x01<<2),  /* Read not allowed */
    BLBAT_WLOCK_gc = (0x02<<2),  /* Write not allowed */
    BLBAT_NOLOCK_gc = (0x03<<2),  /* No locks */
} BLBAT_t;

/* Boot lock bits - boot section */
typedef enum BLBB_enum
{
    BLBB_RWLOCK_gc = (0x00<<6),  /* Read and write not allowed */
    BLBB_RLOCK_gc = (0x01<<6),  /* Read not allowed */
    BLBB_WLOCK_gc = (0x02<<6),  /* Write not allowed */
    BLBB_NOLOCK_gc = (0x03<<6),  /* No locks */
} BLBB_t;

/* Lock bits */
typedef enum LB_enum
{
    LB_RWLOCK_gc = (0x00<<0),  /* Read and write not allowed */
    LB_WLOCK_gc = (0x02<<0),  /* Write not allowed */
    LB_NOLOCK_gc = (0x03<<0),  /* No locks */
} LB_t;

/*
--------------------------------------------------------------------------
MCU - MCU Control
--------------------------------------------------------------------------
*/

/* MCU Control */
typedef struct MCU_struct
{
    register8_t DEVID0;  /* Device ID byte 0 */
    register8_t DEVID1;  /* Device ID byte 1 */
    register8_t DEVID2;  /* Device ID byte 2 */
    register8_t REVID;  /* Revision ID */
    register8_t JTAGUID;  /* JTAG User ID */
    register8_t reserved_1[1];
    register8_t MCUCR;  /* MCU Control */
    register8_t ANAINIT;  /* Analog Startup Delay */
    register8_t EVSYSLOCK;  /* Event System Lock */
    register8_t AWEXLOCK;  /* AWEX Lock */
    register8_t reserved_2[2];
} MCU_t;


/*
--------------------------------------------------------------------------
NVM - Non Volatile Memory Controller
--------------------------------------------------------------------------
*/

/* Non-volatile Memory Controller */
typedef struct NVM_struct
{
    register8_t ADDR0;  /* Address Register 0 */
    register8_t ADDR1;  /* Address Register 1 */
    register8_t ADDR2;  /* Address Register 2 */
    register8_t reserved_1[1];
    register8_t DATA0;  /* Data Register 0 */
    register8_t DATA1;  /* Data Register 1 */
    register8_t DATA2;  /* Data Register 2 */
    register8_t reserved_2[3];
    register8_t CMD;  /* Command */
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t INTCTRL;  /* Interrupt Control */
    register8_t reserved_3[1];
    register8_t STATUS;  /* Status */
    register8_t LOCK_BITS;  /* Lock Bits (Changed from LOCKBITS to avoid avr-libc collision) */
} NVM_t;

/* Boot lock bits - application section */
typedef enum NVM_BLBA_enum
{
    NVM_BLBA_RWLOCK_gc = (0x00<<4),  /* Read and write not allowed */
    NVM_BLBA_RLOCK_gc = (0x01<<4),  /* Read not allowed */
    NVM_BLBA_WLOCK_gc = (0x02<<4),  /* Write not allowed */
    NVM_BLBA_NOLOCK_gc = (0x03<<4),  /* No locks */
} NVM_BLBA_t;

/* Boot lock bits - application table section */
typedef enum NVM_BLBAT_enum
{
    NVM_BLBAT_RWLOCK_gc = (0x00<<2),  /* Read and write not allowed */
    NVM_BLBAT_RLOCK_gc = (0x01<<2),  /* Read not allowed */
    NVM_BLBAT_WLOCK_gc = (0x02<<2),  /* Write not allowed */
    NVM_BLBAT_NOLOCK_gc = (0x03<<2),  /* No locks */
} NVM_BLBAT_t;

/* Boot lock bits - boot section */
typedef enum NVM_BLBB_enum
{
    NVM_BLBB_RWLOCK_gc = (0x00<<6),  /* Read and write not allowed */
    NVM_BLBB_RLOCK_gc = (0x01<<6),  /* Read not allowed */
    NVM_BLBB_WLOCK_gc = (0x02<<6),  /* Write not allowed */
    NVM_BLBB_NOLOCK_gc = (0x03<<6),  /* No locks */
} NVM_BLBB_t;

/* NVM Command */
typedef enum NVM_CMD_enum
{
    NVM_CMD_NO_OPERATION_gc = (0x00<<0),  /* Noop/Ordinary LPM */
    NVM_CMD_READ_USER_SIG_ROW_gc = (0x01<<0),  /* Read user signature row */
    NVM_CMD_READ_CALIB_ROW_gc = (0x02<<0),  /* Read calibration row */
    NVM_CMD_READ_EEPROM_gc = (0x06<<0),  /* Read EEPROM */
    NVM_CMD_READ_FUSES_gc = (0x07<<0),  /* Read fuse byte */
    NVM_CMD_WRITE_LOCK_BITS_gc = (0x08<<0),  /* Write lock bits */
    NVM_CMD_ERASE_USER_SIG_ROW_gc = (0x18<<0),  /* Erase user signature row */
    NVM_CMD_WRITE_USER_SIG_ROW_gc = (0x1A<<0),  /* Write user signature row */
    NVM_CMD_ERASE_APP_gc = (0x20<<0),  /* Erase Application Section */
    NVM_CMD_ERASE_APP_PAGE_gc = (0x22<<0),  /* Erase Application Section page */
    NVM_CMD_LOAD_FLASH_BUFFER_gc = (0x23<<0),  /* Load Flash page buffer */
    NVM_CMD_WRITE_APP_PAGE_gc = (0x24<<0),  /* Write Application Section page */
    NVM_CMD_ERASE_WRITE_APP_PAGE_gc = (0x25<<0),  /* Erase-and-write Application Section page */
    NVM_CMD_ERASE_FLASH_BUFFER_gc = (0x26<<0),  /* Erase/flush Flash page buffer */
    NVM_CMD_ERASE_BOOT_PAGE_gc = (0x2A<<0),  /* Erase Boot Section page */
    NVM_CMD_ERASE_FLASH_PAGE_gc = (0x2B<<0),  /* Erase Flash Page */
    NVM_CMD_WRITE_BOOT_PAGE_gc = (0x2C<<0),  /* Write Boot Section page */
    NVM_CMD_ERASE_WRITE_BOOT_PAGE_gc = (0x2D<<0),  /* Erase-and-write Boot Section page */
    NVM_CMD_WRITE_FLASH_PAGE_gc = (0x2E<<0),  /* Write Flash Page */
    NVM_CMD_ERASE_WRITE_FLASH_PAGE_gc = (0x2F<<0),  /* Erase-and-write Flash Page */
    NVM_CMD_ERASE_EEPROM_gc = (0x30<<0),  /* Erase EEPROM */
    NVM_CMD_ERASE_EEPROM_PAGE_gc = (0x32<<0),  /* Erase EEPROM page */
    NVM_CMD_LOAD_EEPROM_BUFFER_gc = (0x33<<0),  /* Load EEPROM page buffer */
    NVM_CMD_WRITE_EEPROM_PAGE_gc = (0x34<<0),  /* Write EEPROM page */
    NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc = (0x35<<0),  /* Erase-and-write EEPROM page */
    NVM_CMD_ERASE_EEPROM_BUFFER_gc = (0x36<<0),  /* Erase/flush EEPROM page buffer */
    NVM_CMD_APP_CRC_gc = (0x38<<0),  /* Application section CRC */
    NVM_CMD_BOOT_CRC_gc = (0x39<<0),  /*  Boot Section CRC */
    NVM_CMD_FLASH_RANGE_CRC_gc = (0x3A<<0),  /* Flash Range CRC */
    NVM_CMD_CHIP_ERASE_gc = (0x40<<0),  /* Erase Chip */
    NVM_CMD_READ_NVM_gc = (0x43<<0),  /* Read NVM */
    NVM_CMD_WRITE_FUSE_gc = (0x4C<<0),  /* Write Fuse byte */
    NVM_CMD_ERASE_BOOT_gc = (0x68<<0),  /* Erase Boot Section */
    NVM_CMD_FLASH_CRC_gc = (0x78<<0),  /* Flash CRC */
} NVM_CMD_t;

/* EEPROM ready interrupt level */
typedef enum NVM_EELVL_enum
{
    NVM_EELVL_OFF_gc = (0x00<<0),  /* Interrupt disabled */
    NVM_EELVL_LO_gc = (0x01<<0),  /* Low level */
    NVM_EELVL_MED_gc = (0x02<<0),  /* Medium level */
    NVM_EELVL_HI_gc = (0x03<<0),  /* High level */
} NVM_EELVL_t;

/* Lock bits */
typedef enum NVM_LB_enum
{
    NVM_LB_RWLOCK_gc = (0x00<<0),  /* Read and write not allowed */
    NVM_LB_WLOCK_gc = (0x02<<0),  /* Write not allowed */
    NVM_LB_NOLOCK_gc = (0x03<<0),  /* No locks */
} NVM_LB_t;

/* SPM ready interrupt level */
typedef enum NVM_SPMLVL_enum
{
    NVM_SPMLVL_OFF_gc = (0x00<<2),  /* Interrupt disabled */
    NVM_SPMLVL_LO_gc = (0x01<<2),  /* Low level */
    NVM_SPMLVL_MED_gc = (0x02<<2),  /* Medium level */
    NVM_SPMLVL_HI_gc = (0x03<<2),  /* High level */
} NVM_SPMLVL_t;

/*
--------------------------------------------------------------------------
OSC - Oscillator
--------------------------------------------------------------------------
*/

/* Oscillator */
typedef struct OSC_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t STATUS;  /* Status Register */
    register8_t XOSCCTRL;  /* External Oscillator Control Register */
    register8_t XOSCFAIL;  /* Oscillator Failure Detection Register */
    register8_t RC32KCAL;  /* 32.768 kHz Internal Oscillator Calibration Register */
    register8_t PLLCTRL;  /* PLL Control Register */
    register8_t DFLLCTRL;  /* DFLL Control Register */
} OSC_t;

/* Oscillator Frequency Range */
typedef enum OSC_FRQRANGE_enum
{
    OSC_FRQRANGE_04TO2_gc = (0x00<<6),  /* 0.4 - 2 MHz */
    OSC_FRQRANGE_2TO9_gc = (0x01<<6),  /* 2 - 9 MHz */
    OSC_FRQRANGE_9TO12_gc = (0x02<<6),  /* 9 - 12 MHz */
    OSC_FRQRANGE_12TO16_gc = (0x03<<6),  /* 12 - 16 MHz */
} OSC_FRQRANGE_t;

/* PLL Clock Source */
typedef enum OSC_PLLSRC_enum
{
    OSC_PLLSRC_RC2M_gc = (0x00<<6),  /* Internal 2 MHz RC Oscillator */
    OSC_PLLSRC_RC32M_gc = (0x02<<6),  /* Internal 32 MHz RC Oscillator */
    OSC_PLLSRC_XOSC_gc = (0x03<<6),  /* External Oscillator */
} OSC_PLLSRC_t;

/* 2 MHz DFLL Calibration Reference */
typedef enum OSC_RC2MCREF_enum
{
    OSC_RC2MCREF_RC32K_gc = (0x00<<0),  /* Internal 32.768 kHz RC Oscillator */
    OSC_RC2MCREF_XOSC32K_gc = (0x01<<0),  /* External 32.768 kHz Crystal Oscillator */
} OSC_RC2MCREF_t;

/* 32 MHz DFLL Calibration Reference */
typedef enum OSC_RC32MCREF_enum
{
    OSC_RC32MCREF_RC32K_gc = (0x00<<1),  /* Internal 32.768 kHz RC Oscillator */
    OSC_RC32MCREF_XOSC32K_gc = (0x01<<1),  /* External 32.768 kHz Crystal Oscillator */
    OSC_RC32MCREF_USBSOF_gc = (0x02<<1),  /* USB Start of Frame */
} OSC_RC32MCREF_t;

/* External Oscillator Selection and Startup Time */
typedef enum OSC_XOSCSEL_enum
{
    OSC_XOSCSEL_EXTCLK_gc = (0x00<<0),  /* External Clock on port R1 - 6 CLK */
    OSC_XOSCSEL_EXTCLK_C0_gc = (0x01<<0),  /* External Clock on port C0 - 6 CLK */
    OSC_XOSCSEL_32KHz_gc = (0x02<<0),  /* 32kHz TOSC - 32K CLK */
    OSC_XOSCSEL_XTAL_256CLK_gc = (0x03<<0),  /* 0.4-16MHz XTAL - 256 CLK */
    OSC_XOSCSEL_EXTCLK_C1_gc = (0x05<<0),  /* External Clock on port C1 - 6 CLK */
    OSC_XOSCSEL_XTAL_1KCLK_gc = (0x07<<0),  /* 0.4-16MHz XTAL - 1K CLK */
    OSC_XOSCSEL_EXTCLK_C2_gc = (0x09<<0),  /* External Clock on port C2 - 6 CLK */
    OSC_XOSCSEL_XTAL_16KCLK_gc = (0x0B<<0),  /* 0.4-16MHz XTAL - 16K CLK */
    OSC_XOSCSEL_EXTCLK_C3_gc = (0x0D<<0),  /* External Clock on port C3 - 6 CLK */
    OSC_XOSCSEL_EXTCLK_C4_gc = (0x11<<0),  /* External Clock on port C4 - 6 CLK */
    OSC_XOSCSEL_EXTCLK_C5_gc = (0x15<<0),  /* External Clock on port C5 - 6 CLK */
    OSC_XOSCSEL_EXTCLK_C6_gc = (0x19<<0),  /* External Clock on port C6 - 6 CLK */
    OSC_XOSCSEL_EXTCLK_C7_gc = (0x1D<<0),  /* External Clock on port C7 - 6 CLK */
} OSC_XOSCSEL_t;

/*
--------------------------------------------------------------------------
PMIC - Programmable Multi-level Interrupt Controller
--------------------------------------------------------------------------
*/

/* Programmable Multi-level Interrupt Controller */
typedef struct PMIC_struct
{
    register8_t STATUS;  /* Status Register */
    register8_t INTPRI;  /* Interrupt Priority */
    register8_t CTRL;  /* Control Register */
    register8_t reserved_1[13];
} PMIC_t;


/*
--------------------------------------------------------------------------
PORT - I/O Port Configuration
--------------------------------------------------------------------------
*/

/* I/O Ports */
typedef struct PORT_struct
{
    register8_t DIR;  /* I/O Port Data Direction */
    register8_t DIRSET;  /* I/O Port Data Direction Set */
    register8_t DIRCLR;  /* I/O Port Data Direction Clear */
    register8_t DIRTGL;  /* I/O Port Data Direction Toggle */
    register8_t OUT;  /* I/O Port Output */
    register8_t OUTSET;  /* I/O Port Output Set */
    register8_t OUTCLR;  /* I/O Port Output Clear */
    register8_t OUTTGL;  /* I/O Port Output Toggle */
    register8_t IN;  /* I/O port Input */
    register8_t INTCTRL;  /* Interrupt Control Register */
    register8_t INT0MASK;  /* Port Interrupt 0 Mask */
    register8_t INT1MASK;  /* Port Interrupt 1 Mask */
    register8_t INTFLAGS;  /* Interrupt Flag Register */
    register8_t reserved_1[1];
    register8_t REMAP;  /* I/O Port Pin Remap Register */
    register8_t reserved_2[1];
    register8_t PIN0CTRL;  /* Pin 0 Control Register */
    register8_t PIN1CTRL;  /* Pin 1 Control Register */
    register8_t PIN2CTRL;  /* Pin 2 Control Register */
    register8_t PIN3CTRL;  /* Pin 3 Control Register */
    register8_t PIN4CTRL;  /* Pin 4 Control Register */
    register8_t PIN5CTRL;  /* Pin 5 Control Register */
    register8_t PIN6CTRL;  /* Pin 6 Control Register */
    register8_t PIN7CTRL;  /* Pin 7 Control Register */
} PORT_t;

/* Port Interrupt 0 Level */
typedef enum PORT_INT0LVL_enum
{
    PORT_INT0LVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    PORT_INT0LVL_LO_gc = (0x01<<0),  /* Low Level */
    PORT_INT0LVL_MED_gc = (0x02<<0),  /* Medium Level */
    PORT_INT0LVL_HI_gc = (0x03<<0),  /* High Level */
} PORT_INT0LVL_t;

/* Port Interrupt 1 Level */
typedef enum PORT_INT1LVL_enum
{
    PORT_INT1LVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
    PORT_INT1LVL_LO_gc = (0x01<<2),  /* Low Level */
    PORT_INT1LVL_MED_gc = (0x02<<2),  /* Medium Level */
    PORT_INT1LVL_HI_gc = (0x03<<2),  /* High Level */
} PORT_INT1LVL_t;

/* Input/Sense Configuration */
typedef enum PORT_ISC_enum
{
    PORT_ISC_BOTHEDGES_gc = (0x00<<0),  /* Sense Both Edges */
    PORT_ISC_RISING_gc = (0x01<<0),  /* Sense Rising Edge */
    PORT_ISC_FALLING_gc = (0x02<<0),  /* Sense Falling Edge */
    PORT_ISC_LEVEL_gc = (0x03<<0),  /* Sense Level (Transparent For Events) */
    PORT_ISC_INPUT_DISABLE_gc = (0x07<<0),  /* Disable Digital Input Buffer */
} PORT_ISC_t;

/* Output/Pull Configuration */
typedef enum PORT_OPC_enum
{
    PORT_OPC_TOTEM_gc = (0x00<<3),  /* Totempole */
    PORT_OPC_BUSKEEPER_gc = (0x01<<3),  /* Totempole w/ Bus keeper on Input and Output */
    PORT_OPC_PULLDOWN_gc = (0x02<<3),  /* Totempole w/ Pull-down on Input */
    PORT_OPC_PULLUP_gc = (0x03<<3),  /* Totempole w/ Pull-up on Input */
    PORT_OPC_WIREDOR_gc = (0x04<<3),  /* Wired OR */
    PORT_OPC_WIREDAND_gc = (0x05<<3),  /* Wired AND */
    PORT_OPC_WIREDORPULL_gc = (0x06<<3),  /* Wired OR w/ Pull-down */
    PORT_OPC_WIREDANDPULL_gc = (0x07<<3),  /* Wired AND w/ Pull-up */
} PORT_OPC_t;

/*
--------------------------------------------------------------------------
PORTCFG - Port Configuration
--------------------------------------------------------------------------
*/

/* I/O port Configuration */
typedef struct PORTCFG_struct
{
    register8_t MPCMASK;  /* Multi-pin Configuration Mask */
    register8_t reserved_1[1];
    register8_t VPCTRLA;  /* Virtual Port Control Register A */
    register8_t VPCTRLB;  /* Virtual Port Control Register B */
    register8_t CLKEVOUT;  /* Clock and Event Out Register */
    register8_t reserved_2[1];
    register8_t EVOUTSEL;  /* Event Output Select */
} PORTCFG_t;

/* Clock and Event Output Port */
typedef enum PORTCFG_CLKEVPIN_enum
{
    PORTCFG_CLKEVPIN_PIN7_gc = (0x00<<7),  /* Clock and Event Output on PIN 7 */
    PORTCFG_CLKEVPIN_PIN4_gc = (0x01<<7),  /* Clock and Event Output on PIN 4 */
} PORTCFG_CLKEVPIN_t;

/* System Clock Output Port */
typedef enum PORTCFG_CLKOUT_enum
{
    PORTCFG_CLKOUT_OFF_gc = (0x00<<0),  /* System Clock Output Disabled */
    PORTCFG_CLKOUT_PC_gc = (0x01<<0),  /* System Clock Output on Port C */
    PORTCFG_CLKOUT_PE_gc = (0x03<<0),  /* System Clock Output on Port E */
} PORTCFG_CLKOUT_t;

/* Peripheral Clock Output Select */
typedef enum PORTCFG_CLKOUTSEL_enum
{
    PORTCFG_CLKOUTSEL_CLK1X_gc = (0x00<<2),  /* 1x Peripheral Clock Output to pin */
    PORTCFG_CLKOUTSEL_CLK2X_gc = (0x01<<2),  /* 2x Peripheral Clock Output to pin */
    PORTCFG_CLKOUTSEL_CLK4X_gc = (0x02<<2),  /* 4x Peripheral Clock Output to pin */
} PORTCFG_CLKOUTSEL_t;

/* Event Output Port */
typedef enum PORTCFG_EVOUT_enum
{
    PORTCFG_EVOUT_OFF_gc = (0x00<<4),  /* Event Output Disabled */
    PORTCFG_EVOUT_PC_gc = (0x01<<4),  /* Event Channel 0 Output on Port C */
    PORTCFG_EVOUT_PE_gc = (0x03<<4),  /* Event Channel 0 Output on Port E */
} PORTCFG_EVOUT_t;

/* Event Output Select */
typedef enum PORTCFG_EVOUTSEL_enum
{
    PORTCFG_EVOUTSEL_0_gc = (0x00<<2),  /* Event Channel 0 output to pin */
    PORTCFG_EVOUTSEL_1_gc = (0x01<<2),  /* Event Channel 1 output to pin */
    PORTCFG_EVOUTSEL_2_gc = (0x02<<2),  /* Event Channel 2 output to pin */
    PORTCFG_EVOUTSEL_3_gc = (0x03<<2),  /* Event Channel 3 output to pin */
} PORTCFG_EVOUTSEL_t;

/* Virtual Port Mapping */
typedef enum PORTCFG_VP0MAP_enum
{
    PORTCFG_VP0MAP_PORTA_gc = (0x00<<0),  /* Mapped To PORTA */
    PORTCFG_VP0MAP_PORTB_gc = (0x01<<0),  /* Mapped To PORTB */
    PORTCFG_VP0MAP_PORTC_gc = (0x02<<0),  /* Mapped To PORTC */
    PORTCFG_VP0MAP_PORTD_gc = (0x03<<0),  /* Mapped To PORTD */
    PORTCFG_VP0MAP_PORTE_gc = (0x04<<0),  /* Mapped To PORTE */
    PORTCFG_VP0MAP_PORTG_gc = (0x06<<0),  /* Mapped To PORTG */
    PORTCFG_VP0MAP_PORTM_gc = (0x0B<<0),  /* Mapped To PORTM */
    PORTCFG_VP0MAP_PORTR_gc = (0x0F<<0),  /* Mapped To PORTR */

    /* Deprecated aliases */
    PORTCFG_VP02MAP_PORTA_gc = (0x00<<0),  /* Deprecated Mapped To PORTA */
    PORTCFG_VP02MAP_PORTB_gc = (0x01<<0),  /* Deprecated Mapped To PORTB */
    PORTCFG_VP02MAP_PORTC_gc = (0x02<<0),  /* Deprecated Mapped To PORTC */
    PORTCFG_VP02MAP_PORTD_gc = (0x03<<0),  /* Deprecated Mapped To PORTD */
    PORTCFG_VP02MAP_PORTE_gc = (0x04<<0),  /* Deprecated Mapped To PORTE */
    PORTCFG_VP02MAP_PORTG_gc = (0x06<<0),  /* Deprecated Mapped To PORTG */
    PORTCFG_VP02MAP_PORTM_gc = (0x0B<<0),  /* Deprecated Mapped To PORTM */
    PORTCFG_VP02MAP_PORTR_gc = (0x0F<<0),  /* Deprecated Mapped To PORTR */
} PORTCFG_VP0MAP_t;

/* Deprecated type definition */
typedef enum PORTCFG_VP0MAP_enum PORTCFG_VP02MAP_t;

/* Virtual Port Mapping */
typedef enum PORTCFG_VP1MAP_enum
{
    PORTCFG_VP1MAP_PORTA_gc = (0x00<<4),  /* Mapped To PORTA */
    PORTCFG_VP1MAP_PORTB_gc = (0x01<<4),  /* Mapped To PORTB */
    PORTCFG_VP1MAP_PORTC_gc = (0x02<<4),  /* Mapped To PORTC */
    PORTCFG_VP1MAP_PORTD_gc = (0x03<<4),  /* Mapped To PORTD */
    PORTCFG_VP1MAP_PORTE_gc = (0x04<<4),  /* Mapped To PORTE */
    PORTCFG_VP1MAP_PORTG_gc = (0x06<<4),  /* Mapped To PORTG */
    PORTCFG_VP1MAP_PORTM_gc = (0x0B<<4),  /* Mapped To PORTM */
    PORTCFG_VP1MAP_PORTR_gc = (0x0F<<4),  /* Mapped To PORTR */

    /* Deprecated aliases */
    PORTCFG_VP13MAP_PORTA_gc = (0x00<<4),  /* Deprecated Mapped To PORTA */
    PORTCFG_VP13MAP_PORTB_gc = (0x01<<4),  /* Deprecated Mapped To PORTB */
    PORTCFG_VP13MAP_PORTC_gc = (0x02<<4),  /* Deprecated Mapped To PORTC */
    PORTCFG_VP13MAP_PORTD_gc = (0x03<<4),  /* Deprecated Mapped To PORTD */
    PORTCFG_VP13MAP_PORTE_gc = (0x04<<4),  /* Deprecated Mapped To PORTE */
    PORTCFG_VP13MAP_PORTG_gc = (0x06<<4),  /* Deprecated Mapped To PORTG */
    PORTCFG_VP13MAP_PORTM_gc = (0x0B<<4),  /* Deprecated Mapped To PORTM */
    PORTCFG_VP13MAP_PORTR_gc = (0x0F<<4),  /* Deprecated Mapped To PORTR */
} PORTCFG_VP1MAP_t;

/* Deprecated type definition */
typedef enum PORTCFG_VP1MAP_enum PORTCFG_VP13MAP_t;

/* Virtual Port Mapping */
typedef enum PORTCFG_VP2MAP_enum
{
    PORTCFG_VP2MAP_PORTA_gc = (0x00<<0),  /* Mapped To PORTA */
    PORTCFG_VP2MAP_PORTB_gc = (0x01<<0),  /* Mapped To PORTB */
    PORTCFG_VP2MAP_PORTC_gc = (0x02<<0),  /* Mapped To PORTC */
    PORTCFG_VP2MAP_PORTD_gc = (0x03<<0),  /* Mapped To PORTD */
    PORTCFG_VP2MAP_PORTE_gc = (0x04<<0),  /* Mapped To PORTE */
    PORTCFG_VP2MAP_PORTG_gc = (0x06<<0),  /* Mapped To PORTG */
    PORTCFG_VP2MAP_PORTM_gc = (0x0B<<0),  /* Mapped To PORTM */
    PORTCFG_VP2MAP_PORTR_gc = (0x0F<<0),  /* Mapped To PORTR */
} PORTCFG_VP2MAP_t;

/* Virtual Port Mapping */
typedef enum PORTCFG_VP3MAP_enum
{
    PORTCFG_VP3MAP_PORTA_gc = (0x00<<4),  /* Mapped To PORTA */
    PORTCFG_VP3MAP_PORTB_gc = (0x01<<4),  /* Mapped To PORTB */
    PORTCFG_VP3MAP_PORTC_gc = (0x02<<4),  /* Mapped To PORTC */
    PORTCFG_VP3MAP_PORTD_gc = (0x03<<4),  /* Mapped To PORTD */
    PORTCFG_VP3MAP_PORTE_gc = (0x04<<4),  /* Mapped To PORTE */
    PORTCFG_VP3MAP_PORTG_gc = (0x06<<4),  /* Mapped To PORTG */
    PORTCFG_VP3MAP_PORTM_gc = (0x0B<<4),  /* Mapped To PORTM */
    PORTCFG_VP3MAP_PORTR_gc = (0x0F<<4),  /* Mapped To PORTR */
} PORTCFG_VP3MAP_t;

/*
--------------------------------------------------------------------------
PR - Power Reduction
--------------------------------------------------------------------------
*/

/* Power Reduction */
typedef struct PR_struct
{
    register8_t PRGEN;  /* General Power Reduction */
    register8_t PRPA;  /* Power Reduction Port A */
    register8_t PRPB;  /* Power Reduction Port B */
    register8_t PRPC;  /* Power Reduction Port C */
    register8_t reserved_1[1];
    register8_t PRPE;  /* Power Reduction Port E */
} PR_t;


/*
--------------------------------------------------------------------------
RST - Reset
--------------------------------------------------------------------------
*/

/* Reset */
typedef struct RST_struct
{
    register8_t STATUS;  /* Status Register */
    register8_t CTRL;  /* Control Register */
} RST_t;


/*
--------------------------------------------------------------------------
RTC - Real-Time Counter
--------------------------------------------------------------------------
*/

/* Real-Time Counter */
typedef struct RTC_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t STATUS;  /* Status Register */
    register8_t INTCTRL;  /* Interrupt Control Register */
    register8_t INTFLAGS;  /* Interrupt Flags */
    register8_t TEMP;  /* Temporary register */
    register8_t reserved_1[3];
    _WORDREGISTER(CNT);  /* Count Register */
    _WORDREGISTER(PER);  /* Period Register */
    _WORDREGISTER(COMP);  /* Compare Register */
} RTC_t;

/* Compare Interrupt level */
typedef enum RTC_COMPINTLVL_enum
{
    RTC_COMPINTLVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
    RTC_COMPINTLVL_LO_gc = (0x01<<2),  /* Low Level */
    RTC_COMPINTLVL_MED_gc = (0x02<<2),  /* Medium Level */
    RTC_COMPINTLVL_HI_gc = (0x03<<2),  /* High Level */
} RTC_COMPINTLVL_t;

/* Overflow Interrupt level */
typedef enum RTC_OVFINTLVL_enum
{
    RTC_OVFINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    RTC_OVFINTLVL_LO_gc = (0x01<<0),  /* Low Level */
    RTC_OVFINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    RTC_OVFINTLVL_HI_gc = (0x03<<0),  /* High Level */
} RTC_OVFINTLVL_t;

/* Prescaler Factor */
typedef enum RTC_PRESCALER_enum
{
    RTC_PRESCALER_OFF_gc = (0x00<<0),  /* RTC Off */
    RTC_PRESCALER_DIV1_gc = (0x01<<0),  /* RTC Clock */
    RTC_PRESCALER_DIV2_gc = (0x02<<0),  /* RTC Clock / 2 */
    RTC_PRESCALER_DIV8_gc = (0x03<<0),  /* RTC Clock / 8 */
    RTC_PRESCALER_DIV16_gc = (0x04<<0),  /* RTC Clock / 16 */
    RTC_PRESCALER_DIV64_gc = (0x05<<0),  /* RTC Clock / 64 */
    RTC_PRESCALER_DIV256_gc = (0x06<<0),  /* RTC Clock / 256 */
    RTC_PRESCALER_DIV1024_gc = (0x07<<0),  /* RTC Clock / 1024 */
} RTC_PRESCALER_t;

/*
--------------------------------------------------------------------------
SIGROW - Signature Row
--------------------------------------------------------------------------
*/

/* Production Signatures */
typedef struct NVM_PROD_SIGNATURES_struct
{
    register8_t RCOSC2M;  /* RCOSC 2 MHz Calibration Value B */
    register8_t RCOSC2MA;  /* RCOSC 2 MHz Calibration Value A */
    register8_t RCOSC32K;  /* RCOSC 32.768 kHz Calibration Value */
    register8_t RCOSC32M;  /* RCOSC 32 MHz Calibration Value B */
    register8_t RCOSC32MA;  /* RCOSC 32 MHz Calibration Value A */
    register8_t reserved_1[3];
    register8_t LOTNUM0;  /* Lot Number Byte 0, ASCII */
    register8_t LOTNUM1;  /* Lot Number Byte 1, ASCII */
    register8_t LOTNUM2;  /* Lot Number Byte 2, ASCII */
    register8_t LOTNUM3;  /* Lot Number Byte 3, ASCII */
    register8_t LOTNUM4;  /* Lot Number Byte 4, ASCII */
    register8_t LOTNUM5;  /* Lot Number Byte 5, ASCII */
    register8_t reserved_2[2];
    register8_t WAFNUM;  /* Wafer Number */
    register8_t reserved_3[1];
    register8_t COORDX0;  /* Wafer Coordinate X Byte 0 */
    register8_t COORDX1;  /* Wafer Coordinate X Byte 1 */
    register8_t COORDY0;  /* Wafer Coordinate Y Byte 0 */
    register8_t COORDY1;  /* Wafer Coordinate Y Byte 1 */
    register8_t reserved_4[4];
    register8_t USBCAL0;  /* USB Calibration Byte 0 */
    register8_t USBCAL1;  /* USB Calibration Byte 1 */
    register8_t USBRCOSC;  /* USB RCOSC Calibration Value B */
    register8_t USBRCOSCA;  /* USB RCOSC Calibration Value A */
    register8_t reserved_5[2];
    register8_t ADCACAL0;  /* ADCA Calibration Byte 0 */
    register8_t ADCACAL1;  /* ADCA Calibration Byte 1 */
    register8_t reserved_6[2];
    register8_t ADCBCAL0;  /* ADCB Calibration Byte 0 */
    register8_t ADCBCAL1;  /* ADCB Calibration Byte 1 */
    register8_t reserved_7[8];
    register8_t TEMPSENSE0;  /* Temperature Sensor Calibration Byte 0 */
    register8_t TEMPSENSE1;  /* Temperature Sensor Calibration Byte 1 */
    register8_t reserved_8[24];
} NVM_PROD_SIGNATURES_t;


/*
--------------------------------------------------------------------------
SLEEP - Sleep Controller
--------------------------------------------------------------------------
*/

/* Sleep Controller */
typedef struct SLEEP_struct
{
    register8_t CTRL;  /* Control Register */
} SLEEP_t;

/* Sleep Mode */
typedef enum SLEEP_SMODE_enum
{
    SLEEP_SMODE_IDLE_gc = (0x00<<1),  /* Idle mode */
    SLEEP_SMODE_PDOWN_gc = (0x02<<1),  /* Power-down Mode */
    SLEEP_SMODE_PSAVE_gc = (0x03<<1),  /* Power-save Mode */
    SLEEP_SMODE_STDBY_gc = (0x06<<1),  /* Standby Mode */
    SLEEP_SMODE_ESTDBY_gc = (0x07<<1),  /* Extended Standby Mode */
} SLEEP_SMODE_t;

#define SLEEP_MODE_IDLE (0x00<<1)
#define SLEEP_MODE_PWR_DOWN (0x02<<1)
#define SLEEP_MODE_PWR_SAVE (0x03<<1)
#define SLEEP_MODE_STANDBY (0x06<<1)
#define SLEEP_MODE_EXT_STANDBY (0x07<<1)
/*
--------------------------------------------------------------------------
SPI - Serial Peripheral Interface
--------------------------------------------------------------------------
*/

/* Serial Peripheral Interface */
typedef struct SPI_struct
{
    register8_t CTRL;  /* Control Register */
    register8_t INTCTRL;  /* Interrupt Control Register */
    register8_t STATUS;  /* Status Register */
    register8_t DATA;  /* Data Register */
} SPI_t;

/* Interrupt level */
typedef enum SPI_INTLVL_enum
{
    SPI_INTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    SPI_INTLVL_LO_gc = (0x01<<0),  /* Low Level */
    SPI_INTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    SPI_INTLVL_HI_gc = (0x03<<0),  /* High Level */
} SPI_INTLVL_t;

/* SPI Mode */
typedef enum SPI_MODE_enum
{
    SPI_MODE_0_gc = (0x00<<2),  /* SPI Mode 0 */
    SPI_MODE_1_gc = (0x01<<2),  /* SPI Mode 1 */
    SPI_MODE_2_gc = (0x02<<2),  /* SPI Mode 2 */
    SPI_MODE_3_gc = (0x03<<2),  /* SPI Mode 3 */
} SPI_MODE_t;

/* Prescaler setting */
typedef enum SPI_PRESCALER_enum
{
    SPI_PRESCALER_DIV4_gc = (0x00<<0),  /* System Clock / 4 */
    SPI_PRESCALER_DIV16_gc = (0x01<<0),  /* System Clock / 16 */
    SPI_PRESCALER_DIV64_gc = (0x02<<0),  /* System Clock / 64 */
    SPI_PRESCALER_DIV128_gc = (0x03<<0),  /* System Clock / 128 */
} SPI_PRESCALER_t;

/*
--------------------------------------------------------------------------
TC - 16-bit Timer/Counter With PWM
--------------------------------------------------------------------------
*/

/* 16-bit Timer/Counter 0 */
typedef struct TC0_struct
{
    register8_t CTRLA;  /* Control  Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t CTRLC;  /* Control register C */
    register8_t CTRLD;  /* Control Register D */
    register8_t CTRLE;  /* Control Register E */
    register8_t reserved_1[1];
    register8_t INTCTRLA;  /* Interrupt Control Register A */
    register8_t INTCTRLB;  /* Interrupt Control Register B */
    register8_t CTRLFCLR;  /* Control Register F Clear */
    register8_t CTRLFSET;  /* Control Register F Set */
    register8_t CTRLGCLR;  /* Control Register G Clear */
    register8_t CTRLGSET;  /* Control Register G Set */
    register8_t INTFLAGS;  /* Interrupt Flag Register */
    register8_t reserved_2[2];
    register8_t TEMP;  /* Temporary Register For 16-bit Access */
    register8_t reserved_3[16];
    _WORDREGISTER(CNT);  /* Count */
    register8_t reserved_4[4];
    _WORDREGISTER(PER);  /* Period */
    _WORDREGISTER(CCA);  /* Compare or Capture A */
    _WORDREGISTER(CCB);  /* Compare or Capture B */
    _WORDREGISTER(CCC);  /* Compare or Capture C */
    _WORDREGISTER(CCD);  /* Compare or Capture D */
    register8_t reserved_5[6];
    _WORDREGISTER(PERBUF);  /* Period Buffer */
    _WORDREGISTER(CCABUF);  /* Compare Or Capture A Buffer */
    _WORDREGISTER(CCBBUF);  /* Compare Or Capture B Buffer */
    _WORDREGISTER(CCCBUF);  /* Compare Or Capture C Buffer */
    _WORDREGISTER(CCDBUF);  /* Compare Or Capture D Buffer */
} TC0_t;


/* 16-bit Timer/Counter 1 */
typedef struct TC1_struct
{
    register8_t CTRLA;  /* Control  Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t CTRLC;  /* Control register C */
    register8_t CTRLD;  /* Control Register D */
    register8_t CTRLE;  /* Control Register E */
    register8_t reserved_1[1];
    register8_t INTCTRLA;  /* Interrupt Control Register A */
    register8_t INTCTRLB;  /* Interrupt Control Register B */
    register8_t CTRLFCLR;  /* Control Register F Clear */
    register8_t CTRLFSET;  /* Control Register F Set */
    register8_t CTRLGCLR;  /* Control Register G Clear */
    register8_t CTRLGSET;  /* Control Register G Set */
    register8_t INTFLAGS;  /* Interrupt Flag Register */
    register8_t reserved_2[2];
    register8_t TEMP;  /* Temporary Register For 16-bit Access */
    register8_t reserved_3[16];
    _WORDREGISTER(CNT);  /* Count */
    register8_t reserved_4[4];
    _WORDREGISTER(PER);  /* Period */
    _WORDREGISTER(CCA);  /* Compare or Capture A */
    _WORDREGISTER(CCB);  /* Compare or Capture B */
    register8_t reserved_5[10];
    _WORDREGISTER(PERBUF);  /* Period Buffer */
    _WORDREGISTER(CCABUF);  /* Compare Or Capture A Buffer */
    _WORDREGISTER(CCBBUF);  /* Compare Or Capture B Buffer */
} TC1_t;

/* Byte Mode */
typedef enum TC_BYTEM_enum
{
    TC_BYTEM_NORMAL_gc = (0x00<<0),  /* 16-bit mode */
    TC_BYTEM_BYTEMODE_gc = (0x01<<0),  /* Timer/Counter operating in byte mode only */
    TC_BYTEM_SPLITMODE_gc = (0x02<<0),  /* Timer/Counter split into two 8-bit Counters */
} TC_BYTEM_t;

/* Compare or Capture A Interrupt Level */
typedef enum TC_CCAINTLVL_enum
{
    TC_CCAINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    TC_CCAINTLVL_LO_gc = (0x01<<0),  /* Low Level */
    TC_CCAINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    TC_CCAINTLVL_HI_gc = (0x03<<0),  /* High Level */
} TC_CCAINTLVL_t;

/* Compare or Capture B Interrupt Level */
typedef enum TC_CCBINTLVL_enum
{
    TC_CCBINTLVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
    TC_CCBINTLVL_LO_gc = (0x01<<2),  /* Low Level */
    TC_CCBINTLVL_MED_gc = (0x02<<2),  /* Medium Level */
    TC_CCBINTLVL_HI_gc = (0x03<<2),  /* High Level */
} TC_CCBINTLVL_t;

/* Compare or Capture C Interrupt Level */
typedef enum TC_CCCINTLVL_enum
{
    TC_CCCINTLVL_OFF_gc = (0x00<<4),  /* Interrupt Disabled */
    TC_CCCINTLVL_LO_gc = (0x01<<4),  /* Low Level */
    TC_CCCINTLVL_MED_gc = (0x02<<4),  /* Medium Level */
    TC_CCCINTLVL_HI_gc = (0x03<<4),  /* High Level */
} TC_CCCINTLVL_t;

/* Compare or Capture D Interrupt Level */
typedef enum TC_CCDINTLVL_enum
{
    TC_CCDINTLVL_OFF_gc = (0x00<<6),  /* Interrupt Disabled */
    TC_CCDINTLVL_LO_gc = (0x01<<6),  /* Low Level */
    TC_CCDINTLVL_MED_gc = (0x02<<6),  /* Medium Level */
    TC_CCDINTLVL_HI_gc = (0x03<<6),  /* High Level */
} TC_CCDINTLVL_t;

/* Clock Selection */
typedef enum TC_CLKSEL_enum
{
    TC_CLKSEL_OFF_gc = (0x00<<0),  /* Timer Off */
    TC_CLKSEL_DIV1_gc = (0x01<<0),  /* System Clock */
    TC_CLKSEL_DIV2_gc = (0x02<<0),  /* System Clock / 2 */
    TC_CLKSEL_DIV4_gc = (0x03<<0),  /* System Clock / 4 */
    TC_CLKSEL_DIV8_gc = (0x04<<0),  /* System Clock / 8 */
    TC_CLKSEL_DIV64_gc = (0x05<<0),  /* System Clock / 64 */
    TC_CLKSEL_DIV256_gc = (0x06<<0),  /* System Clock / 256 */
    TC_CLKSEL_DIV1024_gc = (0x07<<0),  /* System Clock / 1024 */
    TC_CLKSEL_EVCH0_gc = (0x08<<0),  /* Event Channel 0 */
    TC_CLKSEL_EVCH1_gc = (0x09<<0),  /* Event Channel 1 */
    TC_CLKSEL_EVCH2_gc = (0x0A<<0),  /* Event Channel 2 */
    TC_CLKSEL_EVCH3_gc = (0x0B<<0),  /* Event Channel 3 */
} TC_CLKSEL_t;

/* Timer/Counter Command */
typedef enum TC_CMD_enum
{
    TC_CMD_NONE_gc = (0x00<<2),  /* No Command */
    TC_CMD_UPDATE_gc = (0x01<<2),  /* Force Update */
    TC_CMD_RESTART_gc = (0x02<<2),  /* Force Restart */
    TC_CMD_RESET_gc = (0x03<<2),  /* Force Hard Reset */
} TC_CMD_t;

/* Error Interrupt Level */
typedef enum TC_ERRINTLVL_enum
{
    TC_ERRINTLVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
    TC_ERRINTLVL_LO_gc = (0x01<<2),  /* Low Level */
    TC_ERRINTLVL_MED_gc = (0x02<<2),  /* Medium Level */
    TC_ERRINTLVL_HI_gc = (0x03<<2),  /* High Level */
} TC_ERRINTLVL_t;

/* Event Action */
typedef enum TC_EVACT_enum
{
    TC_EVACT_OFF_gc = (0x00<<5),  /* No Event Action */
    TC_EVACT_CAPT_gc = (0x01<<5),  /* Input Capture */
    TC_EVACT_UPDOWN_gc = (0x02<<5),  /* Externally Controlled Up/Down Count */
    TC_EVACT_QDEC_gc = (0x03<<5),  /* Quadrature Decode */
    TC_EVACT_RESTART_gc = (0x04<<5),  /* Restart */
    TC_EVACT_FRQ_gc = (0x05<<5),  /* Frequency Capture */
    TC_EVACT_PW_gc = (0x06<<5),  /* Pulse-width Capture */
} TC_EVACT_t;

/* Event Selection */
typedef enum TC_EVSEL_enum
{
    TC_EVSEL_OFF_gc = (0x00<<0),  /* No Event Source */
    TC_EVSEL_CH0_gc = (0x08<<0),  /* Event Channel 0 */
    TC_EVSEL_CH1_gc = (0x09<<0),  /* Event Channel 1 */
    TC_EVSEL_CH2_gc = (0x0A<<0),  /* Event Channel 2 */
    TC_EVSEL_CH3_gc = (0x0B<<0),  /* Event Channel 3 */
} TC_EVSEL_t;

/* Overflow Interrupt Level */
typedef enum TC_OVFINTLVL_enum
{
    TC_OVFINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    TC_OVFINTLVL_LO_gc = (0x01<<0),  /* Low Level */
    TC_OVFINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    TC_OVFINTLVL_HI_gc = (0x03<<0),  /* High Level */
} TC_OVFINTLVL_t;

/* Waveform Generation Mode */
typedef enum TC_WGMODE_enum
{
    TC_WGMODE_NORMAL_gc = (0x00<<0),  /* Normal Mode */
    TC_WGMODE_FRQ_gc = (0x01<<0),  /* Frequency Generation Mode */
    TC_WGMODE_SINGLESLOPE_gc = (0x03<<0),  /* Single Slope */
    TC_WGMODE_SS_gc = (0x03<<0),  /* Single Slope */
    TC_WGMODE_DSTOP_gc = (0x05<<0),  /* Dual Slope, Update on TOP */
    TC_WGMODE_DS_T_gc = (0x05<<0),  /* Dual Slope, Update on TOP */
    TC_WGMODE_DSBOTH_gc = (0x06<<0),  /* Dual Slope, Update on both TOP and BOTTOM */
    TC_WGMODE_DS_TB_gc = (0x06<<0),  /* Dual Slope, Update on both TOP and BOTTOM */
    TC_WGMODE_DSBOTTOM_gc = (0x07<<0),  /* Dual Slope, Update on BOTTOM */
    TC_WGMODE_DS_B_gc = (0x07<<0),  /* Dual Slope, Update on BOTTOM */
} TC_WGMODE_t;

/*
--------------------------------------------------------------------------
TC2 - 16-bit Timer/Counter type 2
--------------------------------------------------------------------------
*/

/* 16-bit Timer/Counter type 2 */
typedef struct TC2_struct
{
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t CTRLC;  /* Control register C */
    register8_t reserved_1[1];
    register8_t CTRLE;  /* Control Register E */
    register8_t reserved_2[1];
    register8_t INTCTRLA;  /* Interrupt Control Register A */
    register8_t INTCTRLB;  /* Interrupt Control Register B */
    register8_t reserved_3[1];
    register8_t CTRLF;  /* Control Register F */
    register8_t reserved_4[2];
    register8_t INTFLAGS;  /* Interrupt Flag Register */
    register8_t reserved_5[19];
    register8_t LCNT;  /* Low Byte Count */
    register8_t HCNT;  /* High Byte Count */
    register8_t reserved_6[4];
    register8_t LPER;  /* Low Byte Period */
    register8_t HPER;  /* High Byte Period */
    register8_t LCMPA;  /* Low Byte Compare A */
    register8_t HCMPA;  /* High Byte Compare A */
    register8_t LCMPB;  /* Low Byte Compare B */
    register8_t HCMPB;  /* High Byte Compare B */
    register8_t LCMPC;  /* Low Byte Compare C */
    register8_t HCMPC;  /* High Byte Compare C */
    register8_t LCMPD;  /* Low Byte Compare D */
    register8_t HCMPD;  /* High Byte Compare D */
} TC2_t;

/* Byte Mode */
typedef enum TC2_BYTEM_enum
{
    TC2_BYTEM_NORMAL_gc = (0x00<<0),  /* 16-bit mode */
    TC2_BYTEM_BYTEMODE_gc = (0x01<<0),  /* Timer/Counter operating in byte mode only (TC2) */
    TC2_BYTEM_SPLITMODE_gc = (0x02<<0),  /* Timer/Counter split into two 8-bit Counters */
} TC2_BYTEM_t;

/* Clock Selection */
typedef enum TC2_CLKSEL_enum
{
    TC2_CLKSEL_OFF_gc = (0x00<<0),  /* Timer Off */
    TC2_CLKSEL_DIV1_gc = (0x01<<0),  /* System Clock */
    TC2_CLKSEL_DIV2_gc = (0x02<<0),  /* System Clock / 2 */
    TC2_CLKSEL_DIV4_gc = (0x03<<0),  /* System Clock / 4 */
    TC2_CLKSEL_DIV8_gc = (0x04<<0),  /* System Clock / 8 */
    TC2_CLKSEL_DIV64_gc = (0x05<<0),  /* System Clock / 64 */
    TC2_CLKSEL_DIV256_gc = (0x06<<0),  /* System Clock / 256 */
    TC2_CLKSEL_DIV1024_gc = (0x07<<0),  /* System Clock / 1024 */
    TC2_CLKSEL_EVCH0_gc = (0x08<<0),  /* Event Channel 0 */
    TC2_CLKSEL_EVCH1_gc = (0x09<<0),  /* Event Channel 1 */
    TC2_CLKSEL_EVCH2_gc = (0x0A<<0),  /* Event Channel 2 */
    TC2_CLKSEL_EVCH3_gc = (0x0B<<0),  /* Event Channel 3 */
} TC2_CLKSEL_t;

/* Timer/Counter Command */
typedef enum TC2_CMD_enum
{
    TC2_CMD_NONE_gc = (0x00<<2),  /* No Command */
    TC2_CMD_RESTART_gc = (0x02<<2),  /* Force Restart */
    TC2_CMD_RESET_gc = (0x03<<2),  /* Force Hard Reset */
} TC2_CMD_t;

/* Timer/Counter Command */
typedef enum TC2_CMDEN_enum
{
    TC2_CMDEN_LOW_gc = (0x01<<0),  /* Low Byte Timer/Counter */
    TC2_CMDEN_HIGH_gc = (0x02<<0),  /* High Byte Timer/Counter */
    TC2_CMDEN_BOTH_gc = (0x03<<0),  /* Both Low Byte and High Byte Timer/Counters */
} TC2_CMDEN_t;

/* High Byte Underflow Interrupt Level */
typedef enum TC2_HUNFINTLVL_enum
{
    TC2_HUNFINTLVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
    TC2_HUNFINTLVL_LO_gc = (0x01<<2),  /* Low Level */
    TC2_HUNFINTLVL_MED_gc = (0x02<<2),  /* Medium Level */
    TC2_HUNFINTLVL_HI_gc = (0x03<<2),  /* High Level */
} TC2_HUNFINTLVL_t;

/* Low Byte Compare A Interrupt Level */
typedef enum TC2_LCMPAINTLVL_enum
{
    TC2_LCMPAINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    TC2_LCMPAINTLVL_LO_gc = (0x01<<0),  /* Low Level */
    TC2_LCMPAINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    TC2_LCMPAINTLVL_HI_gc = (0x03<<0),  /* High Level */
} TC2_LCMPAINTLVL_t;

/* Low Byte Compare B Interrupt Level */
typedef enum TC2_LCMPBINTLVL_enum
{
    TC2_LCMPBINTLVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
    TC2_LCMPBINTLVL_LO_gc = (0x01<<2),  /* Low Level */
    TC2_LCMPBINTLVL_MED_gc = (0x02<<2),  /* Medium Level */
    TC2_LCMPBINTLVL_HI_gc = (0x03<<2),  /* High Level */
} TC2_LCMPBINTLVL_t;

/* Low Byte Compare C Interrupt Level */
typedef enum TC2_LCMPCINTLVL_enum
{
    TC2_LCMPCINTLVL_OFF_gc = (0x00<<4),  /* Interrupt Disabled */
    TC2_LCMPCINTLVL_LO_gc = (0x01<<4),  /* Low Level */
    TC2_LCMPCINTLVL_MED_gc = (0x02<<4),  /* Medium Level */
    TC2_LCMPCINTLVL_HI_gc = (0x03<<4),  /* High Level */
} TC2_LCMPCINTLVL_t;

/* Low Byte Compare D Interrupt Level */
typedef enum TC2_LCMPDINTLVL_enum
{
    TC2_LCMPDINTLVL_OFF_gc = (0x00<<6),  /* Interrupt Disabled */
    TC2_LCMPDINTLVL_LO_gc = (0x01<<6),  /* Low Level */
    TC2_LCMPDINTLVL_MED_gc = (0x02<<6),  /* Medium Level */
    TC2_LCMPDINTLVL_HI_gc = (0x03<<6),  /* High Level */
} TC2_LCMPDINTLVL_t;

/* Low Byte Underflow Interrupt Level */
typedef enum TC2_LUNFINTLVL_enum
{
    TC2_LUNFINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    TC2_LUNFINTLVL_LO_gc = (0x01<<0),  /* Low Level */
    TC2_LUNFINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    TC2_LUNFINTLVL_HI_gc = (0x03<<0),  /* High Level */
} TC2_LUNFINTLVL_t;

/*
--------------------------------------------------------------------------
TWI - Two-Wire Interface
--------------------------------------------------------------------------
*/

/*  */
typedef struct TWI_MASTER_struct
{
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t CTRLC;  /* Control Register C */
    register8_t STATUS;  /* Status Register */
    register8_t BAUD;  /* Baurd Rate Control Register */
    register8_t ADDR;  /* Address Register */
    register8_t DATA;  /* Data Register */
} TWI_MASTER_t;


/*  */
typedef struct TWI_SLAVE_struct
{
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t STATUS;  /* Status Register */
    register8_t ADDR;  /* Address Register */
    register8_t DATA;  /* Data Register */
    register8_t ADDRMASK;  /* Address Mask Register */
} TWI_SLAVE_t;


/* Two-Wire Interface */
typedef struct TWI_struct
{
    register8_t CTRL;  /* TWI Common Control Register */
    TWI_MASTER_t MASTER;  /* TWI master module */
    TWI_SLAVE_t SLAVE;  /* TWI slave module */
} TWI_t;

/* Master Bus State */
typedef enum TWI_MASTER_BUSSTATE_enum
{
    TWI_MASTER_BUSSTATE_UNKNOWN_gc = (0x00<<0),  /* Unknown Bus State */
    TWI_MASTER_BUSSTATE_IDLE_gc = (0x01<<0),  /* Bus is Idle */
    TWI_MASTER_BUSSTATE_OWNER_gc = (0x02<<0),  /* This Module Controls The Bus */
    TWI_MASTER_BUSSTATE_BUSY_gc = (0x03<<0),  /* The Bus is Busy */
} TWI_MASTER_BUSSTATE_t;

/* Master Command */
typedef enum TWI_MASTER_CMD_enum
{
    TWI_MASTER_CMD_NOACT_gc = (0x00<<0),  /* No Action */
    TWI_MASTER_CMD_REPSTART_gc = (0x01<<0),  /* Issue Repeated Start Condition */
    TWI_MASTER_CMD_RECVTRANS_gc = (0x02<<0),  /* Receive or Transmit Data */
    TWI_MASTER_CMD_STOP_gc = (0x03<<0),  /* Issue Stop Condition */
} TWI_MASTER_CMD_t;

/* Master Interrupt Level */
typedef enum TWI_MASTER_INTLVL_enum
{
    TWI_MASTER_INTLVL_OFF_gc = (0x00<<6),  /* Interrupt Disabled */
    TWI_MASTER_INTLVL_LO_gc = (0x01<<6),  /* Low Level */
    TWI_MASTER_INTLVL_MED_gc = (0x02<<6),  /* Medium Level */
    TWI_MASTER_INTLVL_HI_gc = (0x03<<6),  /* High Level */
} TWI_MASTER_INTLVL_t;

/* Inactive Timeout */
typedef enum TWI_MASTER_TIMEOUT_enum
{
    TWI_MASTER_TIMEOUT_DISABLED_gc = (0x00<<2),  /* Bus Timeout Disabled */
    TWI_MASTER_TIMEOUT_50US_gc = (0x01<<2),  /* 50 Microseconds */
    TWI_MASTER_TIMEOUT_100US_gc = (0x02<<2),  /* 100 Microseconds */
    TWI_MASTER_TIMEOUT_200US_gc = (0x03<<2),  /* 200 Microseconds */
} TWI_MASTER_TIMEOUT_t;

/* Slave Command */
typedef enum TWI_SLAVE_CMD_enum
{
    TWI_SLAVE_CMD_NOACT_gc = (0x00<<0),  /* No Action */
    TWI_SLAVE_CMD_COMPTRANS_gc = (0x02<<0),  /* Used To Complete a Transaction */
    TWI_SLAVE_CMD_RESPONSE_gc = (0x03<<0),  /* Used in Response to Address/Data Interrupt */
} TWI_SLAVE_CMD_t;

/* Slave Interrupt Level */
typedef enum TWI_SLAVE_INTLVL_enum
{
    TWI_SLAVE_INTLVL_OFF_gc = (0x00<<6),  /* Interrupt Disabled */
    TWI_SLAVE_INTLVL_LO_gc = (0x01<<6),  /* Low Level */
    TWI_SLAVE_INTLVL_MED_gc = (0x02<<6),  /* Medium Level */
    TWI_SLAVE_INTLVL_HI_gc = (0x03<<6),  /* High Level */
} TWI_SLAVE_INTLVL_t;

/* SDA Hold Time */
typedef enum TWI_SDAHOLD_enum
{
    TWI_SDAHOLD_OFF_gc = (0x00<<1),  /* SDA Hold Time off */
    TWI_SDAHOLD_50NS_gc = (0x01<<1),  /* SDA Hold Time 50 ns */
    TWI_SDAHOLD_300NS_gc = (0x02<<1),  /* SDA Hold Time 300 ns */
    TWI_SDAHOLD_400NS_gc = (0x03<<1),  /* SDA Hold Time 400 ns */
} TWI_SDAHOLD_t;

/*
--------------------------------------------------------------------------
USART - Universal Asynchronous Receiver-Transmitter
--------------------------------------------------------------------------
*/

/* Universal Synchronous/Asynchronous Receiver/Transmitter */
typedef struct USART_struct
{
    register8_t DATA;  /* Data Register */
    register8_t STATUS;  /* Status Register */
    register8_t reserved_1[1];
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t CTRLC;  /* Control Register C */
    register8_t BAUDCTRLA;  /* Baud Rate Control Register A */
    register8_t BAUDCTRLB;  /* Baud Rate Control Register B */
} USART_t;

/* Character Size */
typedef enum USART_CHSIZE_enum
{
    USART_CHSIZE_5BIT_gc = (0x00<<0),  /* Character size: 5 bit */
    USART_CHSIZE_6BIT_gc = (0x01<<0),  /* Character size: 6 bit */
    USART_CHSIZE_7BIT_gc = (0x02<<0),  /* Character size: 7 bit */
    USART_CHSIZE_8BIT_gc = (0x03<<0),  /* Character size: 8 bit */
    USART_CHSIZE_9BIT_gc = (0x07<<0),  /* Character size: 9 bit */
} USART_CHSIZE_t;

/* Communication Mode */
typedef enum USART_CMODE_enum
{
    USART_CMODE_ASYNCHRONOUS_gc = (0x00<<6),  /* Asynchronous Mode */
    USART_CMODE_SYNCHRONOUS_gc = (0x01<<6),  /* Synchronous Mode */
    USART_CMODE_IRDA_gc = (0x02<<6),  /* IrDA Mode */
    USART_CMODE_MSPI_gc = (0x03<<6),  /* Master SPI Mode */
} USART_CMODE_t;

/* Data Register Empty Interrupt level */
typedef enum USART_DREINTLVL_enum
{
    USART_DREINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
    USART_DREINTLVL_LO_gc = (0x01<<0),  /* Low Level */
    USART_DREINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
    USART_DREINTLVL_HI_gc = (0x03<<0),  /* High Level */
} USART_DREINTLVL_t;

/* Parity Mode */
typedef enum USART_PMODE_enum
{
    USART_PMODE_DISABLED_gc = (0x00<<4),  /* No Parity */
    USART_PMODE_EVEN_gc = (0x02<<4),  /* Even Parity */
    USART_PMODE_ODD_gc = (0x03<<4),  /* Odd Parity */
} USART_PMODE_t;

/* Receive Complete Interrupt level */
typedef enum USART_RXCINTLVL_enum
{
    USART_RXCINTLVL_OFF_gc = (0x00<<4),  /* Interrupt Disabled */
    USART_RXCINTLVL_LO_gc = (0x01<<4),  /* Low Level */
    USART_RXCINTLVL_MED_gc = (0x02<<4),  /* Medium Level */
    USART_RXCINTLVL_HI_gc = (0x03<<4),  /* High Level */
} USART_RXCINTLVL_t;

/* Transmit Complete Interrupt level */
typedef enum USART_TXCINTLVL_enum
{
    USART_TXCINTLVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
    USART_TXCINTLVL_LO_gc = (0x01<<2),  /* Low Level */
    USART_TXCINTLVL_MED_gc = (0x02<<2),  /* Medium Level */
    USART_TXCINTLVL_HI_gc = (0x03<<2),  /* High Level */
} USART_TXCINTLVL_t;

/*
--------------------------------------------------------------------------
USB - USB
--------------------------------------------------------------------------
*/

/* USB Endpoint */
typedef struct USB_EP_struct
{
    register8_t STATUS;  /* Endpoint Status */
    register8_t CTRL;  /* Endpoint Control */
    _WORDREGISTER(CNT);  /* USB Endpoint Counter */
    _WORDREGISTER(DATAPTR);  /* Data Pointer */
    _WORDREGISTER(AUXDATA);  /* Auxiliary Data */
} USB_EP_t;


/* Universal Serial Bus */
typedef struct USB_struct
{
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t STATUS;  /* Status Register */
    register8_t ADDR;  /* Address Register */
    register8_t FIFOWP;  /* FIFO Write Pointer Register */
    register8_t FIFORP;  /* FIFO Read Pointer Register */
    _WORDREGISTER(EPPTR);  /* Endpoint Configuration Table Pointer */
    register8_t INTCTRLA;  /* Interrupt Control Register A */
    register8_t INTCTRLB;  /* Interrupt Control Register B */
    register8_t INTFLAGSACLR;  /* Clear Interrupt Flag Register A */
    register8_t INTFLAGSASET;  /* Set Interrupt Flag Register A */
    register8_t INTFLAGSBCLR;  /* Clear Interrupt Flag Register B */
    register8_t INTFLAGSBSET;  /* Set Interrupt Flag Register B */
    register8_t reserved_1[44];
    register8_t CAL0;  /* Calibration Byte 0 */
    register8_t CAL1;  /* Calibration Byte 1 */
} USB_t;


/* USB Endpoint Table */
typedef struct USB_EP_TABLE_struct
{
    USB_EP_t EP0OUT;  /* Endpoint 0 */
    USB_EP_t EP0IN;  /* Endpoint 0 */
    USB_EP_t EP1OUT;  /* Endpoint 1 */
    USB_EP_t EP1IN;  /* Endpoint 1 */
    USB_EP_t EP2OUT;  /* Endpoint 2 */
    USB_EP_t EP2IN;  /* Endpoint 2 */
    USB_EP_t EP3OUT;  /* Endpoint 3 */
    USB_EP_t EP3IN;  /* Endpoint 3 */
    USB_EP_t EP4OUT;  /* Endpoint 4 */
    USB_EP_t EP4IN;  /* Endpoint 4 */
    USB_EP_t EP5OUT;  /* Endpoint 5 */
    USB_EP_t EP5IN;  /* Endpoint 5 */
    USB_EP_t EP6OUT;  /* Endpoint 6 */
    USB_EP_t EP6IN;  /* Endpoint 6 */
    USB_EP_t EP7OUT;  /* Endpoint 7 */
    USB_EP_t EP7IN;  /* Endpoint 7 */
    USB_EP_t EP8OUT;  /* Endpoint 8 */
    USB_EP_t EP8IN;  /* Endpoint 8 */
    USB_EP_t EP9OUT;  /* Endpoint 9 */
    USB_EP_t EP9IN;  /* Endpoint 9 */
    USB_EP_t EP10OUT;  /* Endpoint 10 */
    USB_EP_t EP10IN;  /* Endpoint 10 */
    USB_EP_t EP11OUT;  /* Endpoint 11 */
    USB_EP_t EP11IN;  /* Endpoint 11 */
    USB_EP_t EP12OUT;  /* Endpoint 12 */
    USB_EP_t EP12IN;  /* Endpoint 12 */
    USB_EP_t EP13OUT;  /* Endpoint 13 */
    USB_EP_t EP13IN;  /* Endpoint 13 */
    USB_EP_t EP14OUT;  /* Endpoint 14 */
    USB_EP_t EP14IN;  /* Endpoint 14 */
    USB_EP_t EP15OUT;  /* Endpoint 15 */
    USB_EP_t EP15IN;  /* Endpoint 15 */
    register8_t reserved_1[16];
    register8_t FRAMENUML;  /* Frame Number Low Byte */
    register8_t FRAMENUMH;  /* Frame Number High Byte */
} USB_EP_TABLE_t;

/* USB Endpoint Buffersize */
typedef enum USB_EP_BUFSIZE_enum
{
    USB_EP_BUFSIZE_8_gc = (0x00<<0),  /* 8 bytes buffer size */
    USB_EP_BUFSIZE_16_gc = (0x01<<0),  /* 16 bytes buffer size */
    USB_EP_BUFSIZE_32_gc = (0x02<<0),  /* 32 bytes buffer size */
    USB_EP_BUFSIZE_64_gc = (0x03<<0),  /* 64 bytes buffer size */
    USB_EP_BUFSIZE_128_gc = (0x04<<0),  /* 128 bytes buffer size */
    USB_EP_BUFSIZE_256_gc = (0x05<<0),  /* 256 bytes buffer size */
    USB_EP_BUFSIZE_512_gc = (0x06<<0),  /* 512 bytes buffer size */
    USB_EP_BUFSIZE_1023_gc = (0x07<<0),  /* 1023 bytes buffer size */
} USB_EP_BUFSIZE_t;

/* USB Endpoint Type */
typedef enum USB_EP_TYPE_enum
{
    USB_EP_TYPE_DISABLE_gc = (0x00<<6),  /* Endpoint Disabled */
    USB_EP_TYPE_CONTROL_gc = (0x01<<6),  /* Control */
    USB_EP_TYPE_BULK_gc = (0x02<<6),  /* Bulk/Interrupt */
    USB_EP_TYPE_ISOCHRONOUS_gc = (0x03<<6),  /* Isochronous */
} USB_EP_TYPE_t;

/* Interrupt level */
typedef enum USB_INTLVL_enum
{
    USB_INTLVL_OFF_gc = (0x00<<0),  /* Interrupt disabled */
    USB_INTLVL_LO_gc = (0x01<<0),  /* Low level */
    USB_INTLVL_MED_gc = (0x02<<0),  /* Medium level */
    USB_INTLVL_HI_gc = (0x03<<0),  /* High level */
} USB_INTLVL_t;

/*
--------------------------------------------------------------------------
VPORT - Virtual Ports
--------------------------------------------------------------------------
*/

/* Virtual Port */
typedef struct VPORT_struct
{
    register8_t DIR;  /* I/O Port Data Direction */
    register8_t OUT;  /* I/O Port Output */
    register8_t IN;  /* I/O Port Input */
    register8_t INTFLAGS;  /* Interrupt Flag Register */
} VPORT_t;


/*
--------------------------------------------------------------------------
WDT - Watch-Dog Timer
--------------------------------------------------------------------------
*/

/* Watch-Dog Timer */
typedef struct WDT_struct
{
    register8_t CTRL;  /* Control */
    register8_t WINCTRL;  /* Windowed Mode Control */
    register8_t STATUS;  /* Status */
} WDT_t;

/* Period setting */
typedef enum WDT_PER_enum
{
    WDT_PER_8CLK_gc = (0x00<<2),  /* 8 cycles (8ms @ 3.3V) */
    WDT_PER_16CLK_gc = (0x01<<2),  /* 16 cycles (16ms @ 3.3V) */
    WDT_PER_32CLK_gc = (0x02<<2),  /* 32 cycles (32ms @ 3.3V) */
    WDT_PER_64CLK_gc = (0x03<<2),  /* 64 cycles (64ms @ 3.3V) */
    WDT_PER_128CLK_gc = (0x04<<2),  /* 128 cycles (0.128s @ 3.3V) */
    WDT_PER_256CLK_gc = (0x05<<2),  /* 256 cycles (0.256s @ 3.3V) */
    WDT_PER_512CLK_gc = (0x06<<2),  /* 512 cycles (0.512s @ 3.3V) */
    WDT_PER_1KCLK_gc = (0x07<<2),  /* 1K cycles (1s @ 3.3V) */
    WDT_PER_2KCLK_gc = (0x08<<2),  /* 2K cycles (2s @ 3.3V) */
    WDT_PER_4KCLK_gc = (0x09<<2),  /* 4K cycles (4s @ 3.3V) */
    WDT_PER_8KCLK_gc = (0x0A<<2),  /* 8K cycles (8s @ 3.3V) */
} WDT_PER_t;

/* Closed window period */
typedef enum WDT_WPER_enum
{
    WDT_WPER_8CLK_gc = (0x00<<2),  /* 8 cycles (8ms @ 3.3V) */
    WDT_WPER_16CLK_gc = (0x01<<2),  /* 16 cycles (16ms @ 3.3V) */
    WDT_WPER_32CLK_gc = (0x02<<2),  /* 32 cycles (32ms @ 3.3V) */
    WDT_WPER_64CLK_gc = (0x03<<2),  /* 64 cycles (64ms @ 3.3V) */
    WDT_WPER_128CLK_gc = (0x04<<2),  /* 128 cycles (0.128s @ 3.3V) */
    WDT_WPER_256CLK_gc = (0x05<<2),  /* 256 cycles (0.256s @ 3.3V) */
    WDT_WPER_512CLK_gc = (0x06<<2),  /* 512 cycles (0.512s @ 3.3V) */
    WDT_WPER_1KCLK_gc = (0x07<<2),  /* 1K cycles (1s @ 3.3V) */
    WDT_WPER_2KCLK_gc = (0x08<<2),  /* 2K cycles (2s @ 3.3V) */
    WDT_WPER_4KCLK_gc = (0x09<<2),  /* 4K cycles (4s @ 3.3V) */
    WDT_WPER_8KCLK_gc = (0x0A<<2),  /* 8K cycles (8s @ 3.3V) */
} WDT_WPER_t;

/*
--------------------------------------------------------------------------
XOCD - On-Chip Debug System
--------------------------------------------------------------------------
*/

/* On-Chip Debug System */
typedef struct OCD_struct
{
    register8_t OCDR0;  /* OCD Register 0 */
    register8_t OCDR1;  /* OCD Register 1 */
} OCD_t;

/*
==========================================================================
IO Module Instances. Mapped to memory.
==========================================================================
*/

#define VPORT0              (*(VPORT_t *) 0x0010) /* Virtual Port */
#define VPORT1              (*(VPORT_t *) 0x0014) /* Virtual Port */
#define VPORT2              (*(VPORT_t *) 0x0018) /* Virtual Port */
#define VPORT3              (*(VPORT_t *) 0x001C) /* Virtual Port */
#define OCD                   (*(OCD_t *) 0x002E) /* On-Chip Debug System */
#define CLK                   (*(CLK_t *) 0x0040) /* Clock System */
#define SLEEP               (*(SLEEP_t *) 0x0048) /* Sleep Controller */
#define OSC                   (*(OSC_t *) 0x0050) /* Oscillator */
#define DFLLRC32M            (*(DFLL_t *) 0x0060) /* DFLL */
#define DFLLRC2M             (*(DFLL_t *) 0x0068) /* DFLL */
#define PR                     (*(PR_t *) 0x0070) /* Power Reduction */
#define RST                   (*(RST_t *) 0x0078) /* Reset */
#define WDT                   (*(WDT_t *) 0x0080) /* Watch-Dog Timer */
#define MCU                   (*(MCU_t *) 0x0090) /* MCU Control */
#define PMIC                 (*(PMIC_t *) 0x00A0) /* Programmable Multi-level Interrupt Controller */
#define PORTCFG           (*(PORTCFG_t *) 0x00B0) /* I/O port Configuration */
#define AES                   (*(AES_t *) 0x00C0) /* AES Module */
#define CRC                   (*(CRC_t *) 0x00D0) /* Cyclic Redundancy Checker */
#define DMA                   (*(DMA_t *) 0x0100) /* DMA Controller */
#define EVSYS               (*(EVSYS_t *) 0x0180) /* Event System */
#define NVM                   (*(NVM_t *) 0x01C0) /* Non-volatile Memory Controller */
#define ADCA                  (*(ADC_t *) 0x0200) /* Analog-to-Digital Converter */
#define ADCB                  (*(ADC_t *) 0x0240) /* Analog-to-Digital Converter */
#define ACA                    (*(AC_t *) 0x0380) /* Analog Comparator */
#define ACB                    (*(AC_t *) 0x0390) /* Analog Comparator */
#define RTC                   (*(RTC_t *) 0x0400) /* Real-Time Counter */
#define TWIC                  (*(TWI_t *) 0x0480) /* Two-Wire Interface */
#define USB                   (*(USB_t *) 0x04C0) /* Universal Serial Bus */
#define PORTA                (*(PORT_t *) 0x0600) /* I/O Ports */
#define PORTB                (*(PORT_t *) 0x0620) /* I/O Ports */
#define PORTC                (*(PORT_t *) 0x0640) /* I/O Ports */
#define PORTD                (*(PORT_t *) 0x0660) /* I/O Ports */
#define PORTE                (*(PORT_t *) 0x0680) /* I/O Ports */
#define PORTG                (*(PORT_t *) 0x06C0) /* I/O Ports */
#define PORTM                (*(PORT_t *) 0x0760) /* I/O Ports */
#define PORTR                (*(PORT_t *) 0x07E0) /* I/O Ports */
#define TCC0                  (*(TC0_t *) 0x0800) /* 16-bit Timer/Counter 0 */
#define TCC2                  (*(TC2_t *) 0x0800) /* 16-bit Timer/Counter type 2 */
#define TCC1                  (*(TC1_t *) 0x0840) /* 16-bit Timer/Counter 1 */
#define AWEXC                (*(AWEX_t *) 0x0880) /* Advanced Waveform Extension */
#define HIRESC              (*(HIRES_t *) 0x0890) /* High-Resolution Extension */
#define USARTC0             (*(USART_t *) 0x08A0) /* Universal Synchronous/Asynchronous Receiver/Transmitter */
#define SPIC                  (*(SPI_t *) 0x08C0) /* Serial Peripheral Interface */
#define IRCOM               (*(IRCOM_t *) 0x08F8) /* IR Communication Module */
#define TCE0                  (*(TC0_t *) 0x0A00) /* 16-bit Timer/Counter 0 */
#define TCE2                  (*(TC2_t *) 0x0A00) /* 16-bit Timer/Counter type 2 */
#define USARTE0             (*(USART_t *) 0x0AA0) /* Universal Synchronous/Asynchronous Receiver/Transmitter */
#define LCD                   (*(LCD_t *) 0x0D00) /* LCD Controller */

#endif /* !defined (__ASSEMBLER__) */


/* ========== Flattened fully qualified IO register names ========== */


/* GPIO - General Purpose IO Registers */
#define GPIO_GPIOR0  _SFR_MEM8(0x0000)
#define GPIO_GPIOR1  _SFR_MEM8(0x0001)
#define GPIO_GPIOR2  _SFR_MEM8(0x0002)
#define GPIO_GPIOR3  _SFR_MEM8(0x0003)


/* Deprecated */
#define GPIO_GPIO0  _SFR_MEM8(0x0000)
#define GPIO_GPIO1  _SFR_MEM8(0x0001)
#define GPIO_GPIO2  _SFR_MEM8(0x0002)
#define GPIO_GPIO3  _SFR_MEM8(0x0003)


/* NVM_FUSES (FUSE) - Fuses */
#define FUSE_FUSEBYTE0  _SFR_MEM8(0x0000)
#define FUSE_FUSEBYTE1  _SFR_MEM8(0x0001)
#define FUSE_FUSEBYTE2  _SFR_MEM8(0x0002)
#define FUSE_FUSEBYTE4  _SFR_MEM8(0x0004)
#define FUSE_FUSEBYTE5  _SFR_MEM8(0x0005)


/* NVM_LOCKBITS (LOCKBIT) - Lock Bits */
#define LOCKBIT_LOCKBITS  _SFR_MEM8(0x0000)


/* NVM_PROD_SIGNATURES (PROD_SIGNATURES) - Production Signatures */
#define PRODSIGNATURES_RCOSC2M  _SFR_MEM8(0x0000)
#define PRODSIGNATURES_RCOSC2MA  _SFR_MEM8(0x0001)
#define PRODSIGNATURES_RCOSC32K  _SFR_MEM8(0x0002)
#define PRODSIGNATURES_RCOSC32M  _SFR_MEM8(0x0003)
#define PRODSIGNATURES_RCOSC32MA  _SFR_MEM8(0x0004)
#define PRODSIGNATURES_LOTNUM0  _SFR_MEM8(0x0008)
#define PRODSIGNATURES_LOTNUM1  _SFR_MEM8(0x0009)
#define PRODSIGNATURES_LOTNUM2  _SFR_MEM8(0x000A)
#define PRODSIGNATURES_LOTNUM3  _SFR_MEM8(0x000B)
#define PRODSIGNATURES_LOTNUM4  _SFR_MEM8(0x000C)
#define PRODSIGNATURES_LOTNUM5  _SFR_MEM8(0x000D)
#define PRODSIGNATURES_WAFNUM  _SFR_MEM8(0x0010)
#define PRODSIGNATURES_COORDX0  _SFR_MEM8(0x0012)
#define PRODSIGNATURES_COORDX1  _SFR_MEM8(0x0013)
#define PRODSIGNATURES_COORDY0  _SFR_MEM8(0x0014)
#define PRODSIGNATURES_COORDY1  _SFR_MEM8(0x0015)
#define PRODSIGNATURES_USBCAL0  _SFR_MEM8(0x001A)
#define PRODSIGNATURES_USBCAL1  _SFR_MEM8(0x001B)
#define PRODSIGNATURES_USBRCOSC  _SFR_MEM8(0x001C)
#define PRODSIGNATURES_USBRCOSCA  _SFR_MEM8(0x001D)
#define PRODSIGNATURES_ADCACAL0  _SFR_MEM8(0x0020)
#define PRODSIGNATURES_ADCACAL1  _SFR_MEM8(0x0021)
#define PRODSIGNATURES_ADCBCAL0  _SFR_MEM8(0x0024)
#define PRODSIGNATURES_ADCBCAL1  _SFR_MEM8(0x0025)
#define PRODSIGNATURES_TEMPSENSE0  _SFR_MEM8(0x002E)
#define PRODSIGNATURES_TEMPSENSE1  _SFR_MEM8(0x002F)


/* VPORT (VPORT0) - Virtual Port */
#define VPORT0_DIR  _SFR_MEM8(0x0010)
#define VPORT0_OUT  _SFR_MEM8(0x0011)
#define VPORT0_IN  _SFR_MEM8(0x0012)
#define VPORT0_INTFLAGS  _SFR_MEM8(0x0013)


/* VPORT (VPORT1) - Virtual Port */
#define VPORT1_DIR  _SFR_MEM8(0x0014)
#define VPORT1_OUT  _SFR_MEM8(0x0015)
#define VPORT1_IN  _SFR_MEM8(0x0016)
#define VPORT1_INTFLAGS  _SFR_MEM8(0x0017)


/* VPORT (VPORT2) - Virtual Port */
#define VPORT2_DIR  _SFR_MEM8(0x0018)
#define VPORT2_OUT  _SFR_MEM8(0x0019)
#define VPORT2_IN  _SFR_MEM8(0x001A)
#define VPORT2_INTFLAGS  _SFR_MEM8(0x001B)


/* VPORT (VPORT3) - Virtual Port */
#define VPORT3_DIR  _SFR_MEM8(0x001C)
#define VPORT3_OUT  _SFR_MEM8(0x001D)
#define VPORT3_IN  _SFR_MEM8(0x001E)
#define VPORT3_INTFLAGS  _SFR_MEM8(0x001F)


/* OCD - On-Chip Debug System */
#define OCD_OCDR0  _SFR_MEM8(0x002E)
#define OCD_OCDR1  _SFR_MEM8(0x002F)


/* CPU - CPU registers */
#define CPU_CCP  _SFR_MEM8(0x0034)
#define CPU_RAMPD  _SFR_MEM8(0x0038)
#define CPU_RAMPX  _SFR_MEM8(0x0039)
#define CPU_RAMPY  _SFR_MEM8(0x003A)
#define CPU_RAMPZ  _SFR_MEM8(0x003B)
#define CPU_EIND  _SFR_MEM8(0x003C)
#define CPU_SPL  _SFR_MEM8(0x003D)
#define CPU_SPH  _SFR_MEM8(0x003E)
#define CPU_SREG  _SFR_MEM8(0x003F)


/* CLK - Clock System */
#define CLK_CTRL  _SFR_MEM8(0x0040)
#define CLK_PSCTRL  _SFR_MEM8(0x0041)
#define CLK_LOCK  _SFR_MEM8(0x0042)
#define CLK_RTCCTRL  _SFR_MEM8(0x0043)
#define CLK_USBCTRL  _SFR_MEM8(0x0044)


/* SLEEP - Sleep Controller */
#define SLEEP_CTRL  _SFR_MEM8(0x0048)


/* OSC - Oscillator */
#define OSC_CTRL  _SFR_MEM8(0x0050)
#define OSC_STATUS  _SFR_MEM8(0x0051)
#define OSC_XOSCCTRL  _SFR_MEM8(0x0052)
#define OSC_XOSCFAIL  _SFR_MEM8(0x0053)
#define OSC_RC32KCAL  _SFR_MEM8(0x0054)
#define OSC_PLLCTRL  _SFR_MEM8(0x0055)
#define OSC_DFLLCTRL  _SFR_MEM8(0x0056)


/* DFLL (DFLLRC32M) - DFLL */
#define DFLLRC32M_CTRL  _SFR_MEM8(0x0060)
#define DFLLRC32M_CALA  _SFR_MEM8(0x0062)
#define DFLLRC32M_CALB  _SFR_MEM8(0x0063)
#define DFLLRC32M_COMP0  _SFR_MEM8(0x0064)
#define DFLLRC32M_COMP1  _SFR_MEM8(0x0065)
#define DFLLRC32M_COMP2  _SFR_MEM8(0x0066)


/* DFLL (DFLLRC2M) - DFLL */
#define DFLLRC2M_CTRL  _SFR_MEM8(0x0068)
#define DFLLRC2M_CALA  _SFR_MEM8(0x006A)
#define DFLLRC2M_CALB  _SFR_MEM8(0x006B)
#define DFLLRC2M_COMP0  _SFR_MEM8(0x006C)
#define DFLLRC2M_COMP1  _SFR_MEM8(0x006D)
#define DFLLRC2M_COMP2  _SFR_MEM8(0x006E)


/* PR - Power Reduction */
#define PR_PRGEN  _SFR_MEM8(0x0070)
#define PR_PRPA  _SFR_MEM8(0x0071)
#define PR_PRPB  _SFR_MEM8(0x0072)
#define PR_PRPC  _SFR_MEM8(0x0073)
#define PR_PRPE  _SFR_MEM8(0x0075)


/* RST - Reset */
#define RST_STATUS  _SFR_MEM8(0x0078)
#define RST_CTRL  _SFR_MEM8(0x0079)


/* WDT - Watch-Dog Timer */
#define WDT_CTRL  _SFR_MEM8(0x0080)
#define WDT_WINCTRL  _SFR_MEM8(0x0081)
#define WDT_STATUS  _SFR_MEM8(0x0082)


/* MCU - MCU Control */
#define MCU_DEVID0  _SFR_MEM8(0x0090)
#define MCU_DEVID1  _SFR_MEM8(0x0091)
#define MCU_DEVID2  _SFR_MEM8(0x0092)
#define MCU_REVID  _SFR_MEM8(0x0093)
#define MCU_JTAGUID  _SFR_MEM8(0x0094)
#define MCU_MCUCR  _SFR_MEM8(0x0096)
#define MCU_ANAINIT  _SFR_MEM8(0x0097)
#define MCU_EVSYSLOCK  _SFR_MEM8(0x0098)
#define MCU_AWEXLOCK  _SFR_MEM8(0x0099)


/* PMIC - Programmable Multi-level Interrupt Controller */
#define PMIC_STATUS  _SFR_MEM8(0x00A0)
#define PMIC_INTPRI  _SFR_MEM8(0x00A1)
#define PMIC_CTRL  _SFR_MEM8(0x00A2)


/* PORTCFG - I/O port Configuration */
#define PORTCFG_MPCMASK  _SFR_MEM8(0x00B0)
#define PORTCFG_VPCTRLA  _SFR_MEM8(0x00B2)
#define PORTCFG_VPCTRLB  _SFR_MEM8(0x00B3)
#define PORTCFG_CLKEVOUT  _SFR_MEM8(0x00B4)
#define PORTCFG_EVOUTSEL  _SFR_MEM8(0x00B6)


/* AES - AES Module */
#define AES_CTRL  _SFR_MEM8(0x00C0)
#define AES_STATUS  _SFR_MEM8(0x00C1)
#define AES_STATE  _SFR_MEM8(0x00C2)
#define AES_KEY  _SFR_MEM8(0x00C3)
#define AES_INTCTRL  _SFR_MEM8(0x00C4)


/* CRC - Cyclic Redundancy Checker */
#define CRC_CTRL  _SFR_MEM8(0x00D0)
#define CRC_STATUS  _SFR_MEM8(0x00D1)
#define CRC_DATAIN  _SFR_MEM8(0x00D3)
#define CRC_CHECKSUM0  _SFR_MEM8(0x00D4)
#define CRC_CHECKSUM1  _SFR_MEM8(0x00D5)
#define CRC_CHECKSUM2  _SFR_MEM8(0x00D6)
#define CRC_CHECKSUM3  _SFR_MEM8(0x00D7)


/* DMA - DMA Controller */
#define DMA_CTRL  _SFR_MEM8(0x0100)
#define DMA_INTFLAGS  _SFR_MEM8(0x0103)
#define DMA_STATUS  _SFR_MEM8(0x0104)
#define DMA_TEMP  _SFR_MEM16(0x0106)
#define DMA_TEMPL  _SFR_MEM8(0x0106)
#define DMA_TEMPH  _SFR_MEM8(0x0107)
#define DMA_CH0_CTRLA  _SFR_MEM8(0x0110)
#define DMA_CH0_CTRLB  _SFR_MEM8(0x0111)
#define DMA_CH0_ADDRCTRL  _SFR_MEM8(0x0112)
#define DMA_CH0_TRIGSRC  _SFR_MEM8(0x0113)
#define DMA_CH0_TRFCNT  _SFR_MEM16(0x0114)
#define DMA_CH0_REPCNT  _SFR_MEM8(0x0116)
#define DMA_CH0_SRCADDR0  _SFR_MEM8(0x0118)
#define DMA_CH0_SRCADDR1  _SFR_MEM8(0x0119)
#define DMA_CH0_DESTADDR0  _SFR_MEM8(0x011C)
#define DMA_CH0_DESTADDR1  _SFR_MEM8(0x011D)


#define DMA_CH1_CTRLA  _SFR_MEM8(0x0120)
#define DMA_CH1_CTRLB  _SFR_MEM8(0x0121)
#define DMA_CH1_ADDRCTRL  _SFR_MEM8(0x0122)
#define DMA_CH1_TRIGSRC  _SFR_MEM8(0x0123)
#define DMA_CH1_TRFCNT  _SFR_MEM16(0x0124)
#define DMA_CH1_REPCNT  _SFR_MEM8(0x0126)
#define DMA_CH1_SRCADDR0  _SFR_MEM8(0x0128)
#define DMA_CH1_SRCADDR1  _SFR_MEM8(0x0129)
#define DMA_CH1_DESTADDR0  _SFR_MEM8(0x012C)
#define DMA_CH1_DESTADDR1  _SFR_MEM8(0x012D)




/* EVSYS - Event System */
#define EVSYS_CH0MUX  _SFR_MEM8(0x0180)
#define EVSYS_CH1MUX  _SFR_MEM8(0x0181)
#define EVSYS_CH2MUX  _SFR_MEM8(0x0182)
#define EVSYS_CH3MUX  _SFR_MEM8(0x0183)
#define EVSYS_CH0CTRL  _SFR_MEM8(0x0188)
#define EVSYS_CH1CTRL  _SFR_MEM8(0x0189)
#define EVSYS_CH2CTRL  _SFR_MEM8(0x018A)
#define EVSYS_CH3CTRL  _SFR_MEM8(0x018B)
#define EVSYS_STROBE  _SFR_MEM8(0x0190)
#define EVSYS_DATA  _SFR_MEM8(0x0191)


/* NVM - Non-volatile Memory Controller */
#define NVM_ADDR0  _SFR_MEM8(0x01C0)
#define NVM_ADDR1  _SFR_MEM8(0x01C1)
#define NVM_ADDR2  _SFR_MEM8(0x01C2)
#define NVM_DATA0  _SFR_MEM8(0x01C4)
#define NVM_DATA1  _SFR_MEM8(0x01C5)
#define NVM_DATA2  _SFR_MEM8(0x01C6)
#define NVM_CMD  _SFR_MEM8(0x01CA)
#define NVM_CTRLA  _SFR_MEM8(0x01CB)
#define NVM_CTRLB  _SFR_MEM8(0x01CC)
#define NVM_INTCTRL  _SFR_MEM8(0x01CD)
#define NVM_STATUS  _SFR_MEM8(0x01CF)
#define NVM_LOCKBITS  _SFR_MEM8(0x01D0)


/* ADC (ADCA) - Analog-to-Digital Converter */
#define ADCA_CTRLA  _SFR_MEM8(0x0200)
#define ADCA_CTRLB  _SFR_MEM8(0x0201)
#define ADCA_REFCTRL  _SFR_MEM8(0x0202)
#define ADCA_EVCTRL  _SFR_MEM8(0x0203)
#define ADCA_PRESCALER  _SFR_MEM8(0x0204)
#define ADCA_INTFLAGS  _SFR_MEM8(0x0206)
#define ADCA_TEMP  _SFR_MEM8(0x0207)
#define ADCA_SAMPCTRL  _SFR_MEM8(0x0208)
#define ADCA_CAL  _SFR_MEM16(0x020C)
#define ADCA_CALL  _SFR_MEM8(0x020C)
#define ADCA_CALH  _SFR_MEM8(0x020D)
#define ADCA_CH0RES  _SFR_MEM16(0x0210)
#define ADCA_CH0RESL  _SFR_MEM8(0x0210)
#define ADCA_CH0RESH  _SFR_MEM8(0x0211)
#define ADCA_CMP  _SFR_MEM16(0x0218)
#define ADCA_CMPL  _SFR_MEM8(0x0218)
#define ADCA_CMPH  _SFR_MEM8(0x0219)
#define ADCA_CH0_CTRL  _SFR_MEM8(0x0220)
#define ADCA_CH0_MUXCTRL  _SFR_MEM8(0x0221)
#define ADCA_CH0_INTCTRL  _SFR_MEM8(0x0222)
#define ADCA_CH0_INTFLAGS  _SFR_MEM8(0x0223)
#define ADCA_CH0_RES  _SFR_MEM16(0x0224)
#define ADCA_CH0_SCAN  _SFR_MEM8(0x0226)




/* ADC (ADCB) - Analog-to-Digital Converter */
#define ADCB_CTRLA  _SFR_MEM8(0x0240)
#define ADCB_CTRLB  _SFR_MEM8(0x0241)
#define ADCB_REFCTRL  _SFR_MEM8(0x0242)
#define ADCB_EVCTRL  _SFR_MEM8(0x0243)
#define ADCB_PRESCALER  _SFR_MEM8(0x0244)
#define ADCB_INTFLAGS  _SFR_MEM8(0x0246)
#define ADCB_TEMP  _SFR_MEM8(0x0247)
#define ADCB_SAMPCTRL  _SFR_MEM8(0x0248)
#define ADCB_CAL  _SFR_MEM16(0x024C)
#define ADCB_CALL  _SFR_MEM8(0x024C)
#define ADCB_CALH  _SFR_MEM8(0x024D)
#define ADCB_CH0RES  _SFR_MEM16(0x0250)
#define ADCB_CH0RESL  _SFR_MEM8(0x0250)
#define ADCB_CH0RESH  _SFR_MEM8(0x0251)
#define ADCB_CMP  _SFR_MEM16(0x0258)
#define ADCB_CMPL  _SFR_MEM8(0x0258)
#define ADCB_CMPH  _SFR_MEM8(0x0259)
#define ADCB_CH0_CTRL  _SFR_MEM8(0x0260)
#define ADCB_CH0_MUXCTRL  _SFR_MEM8(0x0261)
#define ADCB_CH0_INTCTRL  _SFR_MEM8(0x0262)
#define ADCB_CH0_INTFLAGS  _SFR_MEM8(0x0263)
#define ADCB_CH0_RES  _SFR_MEM16(0x0264)
#define ADCB_CH0_SCAN  _SFR_MEM8(0x0266)




/* AC (ACA) - Analog Comparator */
#define ACA_AC0CTRL  _SFR_MEM8(0x0380)
#define ACA_AC1CTRL  _SFR_MEM8(0x0381)
#define ACA_AC0MUXCTRL  _SFR_MEM8(0x0382)
#define ACA_AC1MUXCTRL  _SFR_MEM8(0x0383)
#define ACA_CTRLA  _SFR_MEM8(0x0384)
#define ACA_CTRLB  _SFR_MEM8(0x0385)
#define ACA_WINCTRL  _SFR_MEM8(0x0386)
#define ACA_STATUS  _SFR_MEM8(0x0387)
#define ACA_CURRCTRL  _SFR_MEM8(0x0388)
#define ACA_CURRCALIB  _SFR_MEM8(0x0389)


/* AC (ACB) - Analog Comparator */
#define ACB_AC0CTRL  _SFR_MEM8(0x0390)
#define ACB_AC1CTRL  _SFR_MEM8(0x0391)
#define ACB_AC0MUXCTRL  _SFR_MEM8(0x0392)
#define ACB_AC1MUXCTRL  _SFR_MEM8(0x0393)
#define ACB_CTRLA  _SFR_MEM8(0x0394)
#define ACB_CTRLB  _SFR_MEM8(0x0395)
#define ACB_WINCTRL  _SFR_MEM8(0x0396)
#define ACB_STATUS  _SFR_MEM8(0x0397)
#define ACB_CURRCTRL  _SFR_MEM8(0x0398)
#define ACB_CURRCALIB  _SFR_MEM8(0x0399)


/* RTC - Real-Time Counter */
#define RTC_CTRL  _SFR_MEM8(0x0400)
#define RTC_STATUS  _SFR_MEM8(0x0401)
#define RTC_INTCTRL  _SFR_MEM8(0x0402)
#define RTC_INTFLAGS  _SFR_MEM8(0x0403)
#define RTC_TEMP  _SFR_MEM8(0x0404)
#define RTC_CNT  _SFR_MEM16(0x0408)
#define RTC_CNTL  _SFR_MEM8(0x0408)
#define RTC_CNTH  _SFR_MEM8(0x0409)
#define RTC_PER  _SFR_MEM16(0x040A)
#define RTC_PERL  _SFR_MEM8(0x040A)
#define RTC_PERH  _SFR_MEM8(0x040B)
#define RTC_COMP  _SFR_MEM16(0x040C)
#define RTC_COMPL  _SFR_MEM8(0x040C)
#define RTC_COMPH  _SFR_MEM8(0x040D)


/* TWI (TWIC) - Two-Wire Interface */
#define TWIC_CTRL  _SFR_MEM8(0x0480)
#define TWIC_MASTER_CTRLA  _SFR_MEM8(0x0481)
#define TWIC_MASTER_CTRLB  _SFR_MEM8(0x0482)
#define TWIC_MASTER_CTRLC  _SFR_MEM8(0x0483)
#define TWIC_MASTER_STATUS  _SFR_MEM8(0x0484)
#define TWIC_MASTER_BAUD  _SFR_MEM8(0x0485)
#define TWIC_MASTER_ADDR  _SFR_MEM8(0x0486)
#define TWIC_MASTER_DATA  _SFR_MEM8(0x0487)


#define TWIC_SLAVE_CTRLA  _SFR_MEM8(0x0488)
#define TWIC_SLAVE_CTRLB  _SFR_MEM8(0x0489)
#define TWIC_SLAVE_STATUS  _SFR_MEM8(0x048A)
#define TWIC_SLAVE_ADDR  _SFR_MEM8(0x048B)
#define TWIC_SLAVE_DATA  _SFR_MEM8(0x048C)
#define TWIC_SLAVE_ADDRMASK  _SFR_MEM8(0x048D)




/* USB - Universal Serial Bus */
#define USB_CTRLA  _SFR_MEM8(0x04C0)
#define USB_CTRLB  _SFR_MEM8(0x04C1)
#define USB_STATUS  _SFR_MEM8(0x04C2)
#define USB_ADDR  _SFR_MEM8(0x04C3)
#define USB_FIFOWP  _SFR_MEM8(0x04C4)
#define USB_FIFORP  _SFR_MEM8(0x04C5)
#define USB_EPPTR  _SFR_MEM16(0x04C6)
#define USB_EPPTRL  _SFR_MEM8(0x04C6)
#define USB_EPPTRH  _SFR_MEM8(0x04C7)
#define USB_INTCTRLA  _SFR_MEM8(0x04C8)
#define USB_INTCTRLB  _SFR_MEM8(0x04C9)
#define USB_INTFLAGSACLR  _SFR_MEM8(0x04CA)
#define USB_INTFLAGSASET  _SFR_MEM8(0x04CB)
#define USB_INTFLAGSBCLR  _SFR_MEM8(0x04CC)
#define USB_INTFLAGSBSET  _SFR_MEM8(0x04CD)
#define USB_CAL0  _SFR_MEM8(0x04FA)
#define USB_CAL1  _SFR_MEM8(0x04FB)


/* PORT (PORTA) - I/O Ports */
#define PORTA_DIR  _SFR_MEM8(0x0600)
#define PORTA_DIRSET  _SFR_MEM8(0x0601)
#define PORTA_DIRCLR  _SFR_MEM8(0x0602)
#define PORTA_DIRTGL  _SFR_MEM8(0x0603)
#define PORTA_OUT  _SFR_MEM8(0x0604)
#define PORTA_OUTSET  _SFR_MEM8(0x0605)
#define PORTA_OUTCLR  _SFR_MEM8(0x0606)
#define PORTA_OUTTGL  _SFR_MEM8(0x0607)
#define PORTA_IN  _SFR_MEM8(0x0608)
#define PORTA_INTCTRL  _SFR_MEM8(0x0609)
#define PORTA_INT0MASK  _SFR_MEM8(0x060A)
#define PORTA_INT1MASK  _SFR_MEM8(0x060B)
#define PORTA_INTFLAGS  _SFR_MEM8(0x060C)
#define PORTA_REMAP  _SFR_MEM8(0x060E)
#define PORTA_PIN0CTRL  _SFR_MEM8(0x0610)
#define PORTA_PIN1CTRL  _SFR_MEM8(0x0611)
#define PORTA_PIN2CTRL  _SFR_MEM8(0x0612)
#define PORTA_PIN3CTRL  _SFR_MEM8(0x0613)
#define PORTA_PIN4CTRL  _SFR_MEM8(0x0614)
#define PORTA_PIN5CTRL  _SFR_MEM8(0x0615)
#define PORTA_PIN6CTRL  _SFR_MEM8(0x0616)
#define PORTA_PIN7CTRL  _SFR_MEM8(0x0617)


/* PORT (PORTB) - I/O Ports */
#define PORTB_DIR  _SFR_MEM8(0x0620)
#define PORTB_DIRSET  _SFR_MEM8(0x0621)
#define PORTB_DIRCLR  _SFR_MEM8(0x0622)
#define PORTB_DIRTGL  _SFR_MEM8(0x0623)
#define PORTB_OUT  _SFR_MEM8(0x0624)
#define PORTB_OUTSET  _SFR_MEM8(0x0625)
#define PORTB_OUTCLR  _SFR_MEM8(0x0626)
#define PORTB_OUTTGL  _SFR_MEM8(0x0627)
#define PORTB_IN  _SFR_MEM8(0x0628)
#define PORTB_INTCTRL  _SFR_MEM8(0x0629)
#define PORTB_INT0MASK  _SFR_MEM8(0x062A)
#define PORTB_INT1MASK  _SFR_MEM8(0x062B)
#define PORTB_INTFLAGS  _SFR_MEM8(0x062C)
#define PORTB_REMAP  _SFR_MEM8(0x062E)
#define PORTB_PIN0CTRL  _SFR_MEM8(0x0630)
#define PORTB_PIN1CTRL  _SFR_MEM8(0x0631)
#define PORTB_PIN2CTRL  _SFR_MEM8(0x0632)
#define PORTB_PIN3CTRL  _SFR_MEM8(0x0633)
#define PORTB_PIN4CTRL  _SFR_MEM8(0x0634)
#define PORTB_PIN5CTRL  _SFR_MEM8(0x0635)
#define PORTB_PIN6CTRL  _SFR_MEM8(0x0636)
#define PORTB_PIN7CTRL  _SFR_MEM8(0x0637)


/* PORT (PORTC) - I/O Ports */
#define PORTC_DIR  _SFR_MEM8(0x0640)
#define PORTC_DIRSET  _SFR_MEM8(0x0641)
#define PORTC_DIRCLR  _SFR_MEM8(0x0642)
#define PORTC_DIRTGL  _SFR_MEM8(0x0643)
#define PORTC_OUT  _SFR_MEM8(0x0644)
#define PORTC_OUTSET  _SFR_MEM8(0x0645)
#define PORTC_OUTCLR  _SFR_MEM8(0x0646)
#define PORTC_OUTTGL  _SFR_MEM8(0x0647)
#define PORTC_IN  _SFR_MEM8(0x0648)
#define PORTC_INTCTRL  _SFR_MEM8(0x0649)
#define PORTC_INT0MASK  _SFR_MEM8(0x064A)
#define PORTC_INT1MASK  _SFR_MEM8(0x064B)
#define PORTC_INTFLAGS  _SFR_MEM8(0x064C)
#define PORTC_REMAP  _SFR_MEM8(0x064E)
#define PORTC_PIN0CTRL  _SFR_MEM8(0x0650)
#define PORTC_PIN1CTRL  _SFR_MEM8(0x0651)
#define PORTC_PIN2CTRL  _SFR_MEM8(0x0652)
#define PORTC_PIN3CTRL  _SFR_MEM8(0x0653)
#define PORTC_PIN4CTRL  _SFR_MEM8(0x0654)
#define PORTC_PIN5CTRL  _SFR_MEM8(0x0655)
#define PORTC_PIN6CTRL  _SFR_MEM8(0x0656)
#define PORTC_PIN7CTRL  _SFR_MEM8(0x0657)


/* PORT (PORTD) - I/O Ports */
#define PORTD_DIR  _SFR_MEM8(0x0660)
#define PORTD_DIRSET  _SFR_MEM8(0x0661)
#define PORTD_DIRCLR  _SFR_MEM8(0x0662)
#define PORTD_DIRTGL  _SFR_MEM8(0x0663)
#define PORTD_OUT  _SFR_MEM8(0x0664)
#define PORTD_OUTSET  _SFR_MEM8(0x0665)
#define PORTD_OUTCLR  _SFR_MEM8(0x0666)
#define PORTD_OUTTGL  _SFR_MEM8(0x0667)
#define PORTD_IN  _SFR_MEM8(0x0668)
#define PORTD_INTCTRL  _SFR_MEM8(0x0669)
#define PORTD_INT0MASK  _SFR_MEM8(0x066A)
#define PORTD_INT1MASK  _SFR_MEM8(0x066B)
#define PORTD_INTFLAGS  _SFR_MEM8(0x066C)
#define PORTD_REMAP  _SFR_MEM8(0x066E)
#define PORTD_PIN0CTRL  _SFR_MEM8(0x0670)
#define PORTD_PIN1CTRL  _SFR_MEM8(0x0671)
#define PORTD_PIN2CTRL  _SFR_MEM8(0x0672)
#define PORTD_PIN3CTRL  _SFR_MEM8(0x0673)
#define PORTD_PIN4CTRL  _SFR_MEM8(0x0674)
#define PORTD_PIN5CTRL  _SFR_MEM8(0x0675)
#define PORTD_PIN6CTRL  _SFR_MEM8(0x0676)
#define PORTD_PIN7CTRL  _SFR_MEM8(0x0677)


/* PORT (PORTE) - I/O Ports */
#define PORTE_DIR  _SFR_MEM8(0x0680)
#define PORTE_DIRSET  _SFR_MEM8(0x0681)
#define PORTE_DIRCLR  _SFR_MEM8(0x0682)
#define PORTE_DIRTGL  _SFR_MEM8(0x0683)
#define PORTE_OUT  _SFR_MEM8(0x0684)
#define PORTE_OUTSET  _SFR_MEM8(0x0685)
#define PORTE_OUTCLR  _SFR_MEM8(0x0686)
#define PORTE_OUTTGL  _SFR_MEM8(0x0687)
#define PORTE_IN  _SFR_MEM8(0x0688)
#define PORTE_INTCTRL  _SFR_MEM8(0x0689)
#define PORTE_INT0MASK  _SFR_MEM8(0x068A)
#define PORTE_INT1MASK  _SFR_MEM8(0x068B)
#define PORTE_INTFLAGS  _SFR_MEM8(0x068C)
#define PORTE_REMAP  _SFR_MEM8(0x068E)
#define PORTE_PIN0CTRL  _SFR_MEM8(0x0690)
#define PORTE_PIN1CTRL  _SFR_MEM8(0x0691)
#define PORTE_PIN2CTRL  _SFR_MEM8(0x0692)
#define PORTE_PIN3CTRL  _SFR_MEM8(0x0693)
#define PORTE_PIN4CTRL  _SFR_MEM8(0x0694)
#define PORTE_PIN5CTRL  _SFR_MEM8(0x0695)
#define PORTE_PIN6CTRL  _SFR_MEM8(0x0696)
#define PORTE_PIN7CTRL  _SFR_MEM8(0x0697)


/* PORT (PORTG) - I/O Ports */
#define PORTG_DIR  _SFR_MEM8(0x06C0)
#define PORTG_DIRSET  _SFR_MEM8(0x06C1)
#define PORTG_DIRCLR  _SFR_MEM8(0x06C2)
#define PORTG_DIRTGL  _SFR_MEM8(0x06C3)
#define PORTG_OUT  _SFR_MEM8(0x06C4)
#define PORTG_OUTSET  _SFR_MEM8(0x06C5)
#define PORTG_OUTCLR  _SFR_MEM8(0x06C6)
#define PORTG_OUTTGL  _SFR_MEM8(0x06C7)
#define PORTG_IN  _SFR_MEM8(0x06C8)
#define PORTG_INTCTRL  _SFR_MEM8(0x06C9)
#define PORTG_INT0MASK  _SFR_MEM8(0x06CA)
#define PORTG_INT1MASK  _SFR_MEM8(0x06CB)
#define PORTG_INTFLAGS  _SFR_MEM8(0x06CC)
#define PORTG_REMAP  _SFR_MEM8(0x06CE)
#define PORTG_PIN0CTRL  _SFR_MEM8(0x06D0)
#define PORTG_PIN1CTRL  _SFR_MEM8(0x06D1)
#define PORTG_PIN2CTRL  _SFR_MEM8(0x06D2)
#define PORTG_PIN3CTRL  _SFR_MEM8(0x06D3)
#define PORTG_PIN4CTRL  _SFR_MEM8(0x06D4)
#define PORTG_PIN5CTRL  _SFR_MEM8(0x06D5)
#define PORTG_PIN6CTRL  _SFR_MEM8(0x06D6)
#define PORTG_PIN7CTRL  _SFR_MEM8(0x06D7)


/* PORT (PORTM) - I/O Ports */
#define PORTM_DIR  _SFR_MEM8(0x0760)
#define PORTM_DIRSET  _SFR_MEM8(0x0761)
#define PORTM_DIRCLR  _SFR_MEM8(0x0762)
#define PORTM_DIRTGL  _SFR_MEM8(0x0763)
#define PORTM_OUT  _SFR_MEM8(0x0764)
#define PORTM_OUTSET  _SFR_MEM8(0x0765)
#define PORTM_OUTCLR  _SFR_MEM8(0x0766)
#define PORTM_OUTTGL  _SFR_MEM8(0x0767)
#define PORTM_IN  _SFR_MEM8(0x0768)
#define PORTM_INTCTRL  _SFR_MEM8(0x0769)
#define PORTM_INT0MASK  _SFR_MEM8(0x076A)
#define PORTM_INT1MASK  _SFR_MEM8(0x076B)
#define PORTM_INTFLAGS  _SFR_MEM8(0x076C)
#define PORTM_REMAP  _SFR_MEM8(0x076E)
#define PORTM_PIN0CTRL  _SFR_MEM8(0x0770)
#define PORTM_PIN1CTRL  _SFR_MEM8(0x0771)
#define PORTM_PIN2CTRL  _SFR_MEM8(0x0772)
#define PORTM_PIN3CTRL  _SFR_MEM8(0x0773)
#define PORTM_PIN4CTRL  _SFR_MEM8(0x0774)
#define PORTM_PIN5CTRL  _SFR_MEM8(0x0775)
#define PORTM_PIN6CTRL  _SFR_MEM8(0x0776)
#define PORTM_PIN7CTRL  _SFR_MEM8(0x0777)


/* PORT (PORTR) - I/O Ports */
#define PORTR_DIR  _SFR_MEM8(0x07E0)
#define PORTR_DIRSET  _SFR_MEM8(0x07E1)
#define PORTR_DIRCLR  _SFR_MEM8(0x07E2)
#define PORTR_DIRTGL  _SFR_MEM8(0x07E3)
#define PORTR_OUT  _SFR_MEM8(0x07E4)
#define PORTR_OUTSET  _SFR_MEM8(0x07E5)
#define PORTR_OUTCLR  _SFR_MEM8(0x07E6)
#define PORTR_OUTTGL  _SFR_MEM8(0x07E7)
#define PORTR_IN  _SFR_MEM8(0x07E8)
#define PORTR_INTCTRL  _SFR_MEM8(0x07E9)
#define PORTR_INT0MASK  _SFR_MEM8(0x07EA)
#define PORTR_INT1MASK  _SFR_MEM8(0x07EB)
#define PORTR_INTFLAGS  _SFR_MEM8(0x07EC)
#define PORTR_REMAP  _SFR_MEM8(0x07EE)
#define PORTR_PIN0CTRL  _SFR_MEM8(0x07F0)
#define PORTR_PIN1CTRL  _SFR_MEM8(0x07F1)
#define PORTR_PIN2CTRL  _SFR_MEM8(0x07F2)
#define PORTR_PIN3CTRL  _SFR_MEM8(0x07F3)
#define PORTR_PIN4CTRL  _SFR_MEM8(0x07F4)
#define PORTR_PIN5CTRL  _SFR_MEM8(0x07F5)
#define PORTR_PIN6CTRL  _SFR_MEM8(0x07F6)
#define PORTR_PIN7CTRL  _SFR_MEM8(0x07F7)


/* TC0 (TCC0) - 16-bit Timer/Counter 0 */
#define TCC0_CTRLA  _SFR_MEM8(0x0800)
#define TCC0_CTRLB  _SFR_MEM8(0x0801)
#define TCC0_CTRLC  _SFR_MEM8(0x0802)
#define TCC0_CTRLD  _SFR_MEM8(0x0803)
#define TCC0_CTRLE  _SFR_MEM8(0x0804)
#define TCC0_INTCTRLA  _SFR_MEM8(0x0806)
#define TCC0_INTCTRLB  _SFR_MEM8(0x0807)
#define TCC0_CTRLFCLR  _SFR_MEM8(0x0808)
#define TCC0_CTRLFSET  _SFR_MEM8(0x0809)
#define TCC0_CTRLGCLR  _SFR_MEM8(0x080A)
#define TCC0_CTRLGSET  _SFR_MEM8(0x080B)
#define TCC0_INTFLAGS  _SFR_MEM8(0x080C)
#define TCC0_TEMP  _SFR_MEM8(0x080F)
#define TCC0_CNT  _SFR_MEM16(0x0820)
#define TCC0_CNTL  _SFR_MEM8(0x0820)
#define TCC0_CNTH  _SFR_MEM8(0x0821)
#define TCC0_PER  _SFR_MEM16(0x0826)
#define TCC0_PERL  _SFR_MEM8(0x0826)
#define TCC0_PERH  _SFR_MEM8(0x0827)
#define TCC0_CCA  _SFR_MEM16(0x0828)
#define TCC0_CCAL  _SFR_MEM8(0x0828)
#define TCC0_CCAH  _SFR_MEM8(0x0829)
#define TCC0_CCB  _SFR_MEM16(0x082A)
#define TCC0_CCBL  _SFR_MEM8(0x082A)
#define TCC0_CCBH  _SFR_MEM8(0x082B)
#define TCC0_CCC  _SFR_MEM16(0x082C)
#define TCC0_CCCL  _SFR_MEM8(0x082C)
#define TCC0_CCCH  _SFR_MEM8(0x082D)
#define TCC0_CCD  _SFR_MEM16(0x082E)
#define TCC0_CCDL  _SFR_MEM8(0x082E)
#define TCC0_CCDH  _SFR_MEM8(0x082F)
#define TCC0_PERBUF  _SFR_MEM16(0x0836)
#define TCC0_PERBUFL  _SFR_MEM8(0x0836)
#define TCC0_PERBUFH  _SFR_MEM8(0x0837)
#define TCC0_CCABUF  _SFR_MEM16(0x0838)
#define TCC0_CCABUFL  _SFR_MEM8(0x0838)
#define TCC0_CCABUFH  _SFR_MEM8(0x0839)
#define TCC0_CCBBUF  _SFR_MEM16(0x083A)
#define TCC0_CCBBUFL  _SFR_MEM8(0x083A)
#define TCC0_CCBBUFH  _SFR_MEM8(0x083B)
#define TCC0_CCCBUF  _SFR_MEM16(0x083C)
#define TCC0_CCCBUFL  _SFR_MEM8(0x083C)
#define TCC0_CCCBUFH  _SFR_MEM8(0x083D)
#define TCC0_CCDBUF  _SFR_MEM16(0x083E)
#define TCC0_CCDBUFL  _SFR_MEM8(0x083E)
#define TCC0_CCDBUFH  _SFR_MEM8(0x083F)


/* TC2 (TCC2) - 16-bit Timer/Counter type 2 */
#define TCC2_CTRLA  _SFR_MEM8(0x0800)
#define TCC2_CTRLB  _SFR_MEM8(0x0801)
#define TCC2_CTRLC  _SFR_MEM8(0x0802)
#define TCC2_CTRLE  _SFR_MEM8(0x0804)
#define TCC2_INTCTRLA  _SFR_MEM8(0x0806)
#define TCC2_INTCTRLB  _SFR_MEM8(0x0807)
#define TCC2_CTRLF  _SFR_MEM8(0x0809)
#define TCC2_INTFLAGS  _SFR_MEM8(0x080C)
#define TCC2_LCNT  _SFR_MEM8(0x0820)
#define TCC2_HCNT  _SFR_MEM8(0x0821)
#define TCC2_LPER  _SFR_MEM8(0x0826)
#define TCC2_HPER  _SFR_MEM8(0x0827)
#define TCC2_LCMPA  _SFR_MEM8(0x0828)
#define TCC2_HCMPA  _SFR_MEM8(0x0829)
#define TCC2_LCMPB  _SFR_MEM8(0x082A)
#define TCC2_HCMPB  _SFR_MEM8(0x082B)
#define TCC2_LCMPC  _SFR_MEM8(0x082C)
#define TCC2_HCMPC  _SFR_MEM8(0x082D)
#define TCC2_LCMPD  _SFR_MEM8(0x082E)
#define TCC2_HCMPD  _SFR_MEM8(0x082F)


/* TC1 (TCC1) - 16-bit Timer/Counter 1 */
#define TCC1_CTRLA  _SFR_MEM8(0x0840)
#define TCC1_CTRLB  _SFR_MEM8(0x0841)
#define TCC1_CTRLC  _SFR_MEM8(0x0842)
#define TCC1_CTRLD  _SFR_MEM8(0x0843)
#define TCC1_CTRLE  _SFR_MEM8(0x0844)
#define TCC1_INTCTRLA  _SFR_MEM8(0x0846)
#define TCC1_INTCTRLB  _SFR_MEM8(0x0847)
#define TCC1_CTRLFCLR  _SFR_MEM8(0x0848)
#define TCC1_CTRLFSET  _SFR_MEM8(0x0849)
#define TCC1_CTRLGCLR  _SFR_MEM8(0x084A)
#define TCC1_CTRLGSET  _SFR_MEM8(0x084B)
#define TCC1_INTFLAGS  _SFR_MEM8(0x084C)
#define TCC1_TEMP  _SFR_MEM8(0x084F)
#define TCC1_CNT  _SFR_MEM16(0x0860)
#define TCC1_CNTL  _SFR_MEM8(0x0860)
#define TCC1_CNTH  _SFR_MEM8(0x0861)
#define TCC1_PER  _SFR_MEM16(0x0866)
#define TCC1_PERL  _SFR_MEM8(0x0866)
#define TCC1_PERH  _SFR_MEM8(0x0867)
#define TCC1_CCA  _SFR_MEM16(0x0868)
#define TCC1_CCAL  _SFR_MEM8(0x0868)
#define TCC1_CCAH  _SFR_MEM8(0x0869)
#define TCC1_CCB  _SFR_MEM16(0x086A)
#define TCC1_CCBL  _SFR_MEM8(0x086A)
#define TCC1_CCBH  _SFR_MEM8(0x086B)
#define TCC1_PERBUF  _SFR_MEM16(0x0876)
#define TCC1_PERBUFL  _SFR_MEM8(0x0876)
#define TCC1_PERBUFH  _SFR_MEM8(0x0877)
#define TCC1_CCABUF  _SFR_MEM16(0x0878)
#define TCC1_CCABUFL  _SFR_MEM8(0x0878)
#define TCC1_CCABUFH  _SFR_MEM8(0x0879)
#define TCC1_CCBBUF  _SFR_MEM16(0x087A)
#define TCC1_CCBBUFL  _SFR_MEM8(0x087A)
#define TCC1_CCBBUFH  _SFR_MEM8(0x087B)


/* AWEX (AWEXC) - Advanced Waveform Extension */
#define AWEXC_CTRL  _SFR_MEM8(0x0880)
#define AWEXC_FDEMASK  _SFR_MEM8(0x0882)
#define AWEXC_FDCTRL  _SFR_MEM8(0x0883)
#define AWEXC_STATUS  _SFR_MEM8(0x0884)
#define AWEXC_STATUSSET  _SFR_MEM8(0x0885)
#define AWEXC_DTBOTH  _SFR_MEM8(0x0886)
#define AWEXC_DTBOTHBUF  _SFR_MEM8(0x0887)
#define AWEXC_DTLS  _SFR_MEM8(0x0888)
#define AWEXC_DTHS  _SFR_MEM8(0x0889)
#define AWEXC_DTLSBUF  _SFR_MEM8(0x088A)
#define AWEXC_DTHSBUF  _SFR_MEM8(0x088B)
#define AWEXC_OUTOVEN  _SFR_MEM8(0x088C)


/* HIRES (HIRESC) - High-Resolution Extension */
#define HIRESC_CTRLA  _SFR_MEM8(0x0890)


/* USART (USARTC0) - Universal Synchronous/Asynchronous Receiver/Transmitter */
#define USARTC0_DATA  _SFR_MEM8(0x08A0)
#define USARTC0_STATUS  _SFR_MEM8(0x08A1)
#define USARTC0_CTRLA  _SFR_MEM8(0x08A3)
#define USARTC0_CTRLB  _SFR_MEM8(0x08A4)
#define USARTC0_CTRLC  _SFR_MEM8(0x08A5)
#define USARTC0_BAUDCTRLA  _SFR_MEM8(0x08A6)
#define USARTC0_BAUDCTRLB  _SFR_MEM8(0x08A7)


/* SPI (SPIC) - Serial Peripheral Interface */
#define SPIC_CTRL  _SFR_MEM8(0x08C0)
#define SPIC_INTCTRL  _SFR_MEM8(0x08C1)
#define SPIC_STATUS  _SFR_MEM8(0x08C2)
#define SPIC_DATA  _SFR_MEM8(0x08C3)


/* IRCOM - IR Communication Module */
#define IRCOM_CTRL  _SFR_MEM8(0x08F8)
#define IRCOM_TXPLCTRL  _SFR_MEM8(0x08F9)
#define IRCOM_RXPLCTRL  _SFR_MEM8(0x08FA)


/* TC0 (TCE0) - 16-bit Timer/Counter 0 */
#define TCE0_CTRLA  _SFR_MEM8(0x0A00)
#define TCE0_CTRLB  _SFR_MEM8(0x0A01)
#define TCE0_CTRLC  _SFR_MEM8(0x0A02)
#define TCE0_CTRLD  _SFR_MEM8(0x0A03)
#define TCE0_CTRLE  _SFR_MEM8(0x0A04)
#define TCE0_INTCTRLA  _SFR_MEM8(0x0A06)
#define TCE0_INTCTRLB  _SFR_MEM8(0x0A07)
#define TCE0_CTRLFCLR  _SFR_MEM8(0x0A08)
#define TCE0_CTRLFSET  _SFR_MEM8(0x0A09)
#define TCE0_CTRLGCLR  _SFR_MEM8(0x0A0A)
#define TCE0_CTRLGSET  _SFR_MEM8(0x0A0B)
#define TCE0_INTFLAGS  _SFR_MEM8(0x0A0C)
#define TCE0_TEMP  _SFR_MEM8(0x0A0F)
#define TCE0_CNT  _SFR_MEM16(0x0A20)
#define TCE0_CNTL  _SFR_MEM8(0x0A20)
#define TCE0_CNTH  _SFR_MEM8(0x0A21)
#define TCE0_PER  _SFR_MEM16(0x0A26)
#define TCE0_PERL  _SFR_MEM8(0x0A26)
#define TCE0_PERH  _SFR_MEM8(0x0A27)
#define TCE0_CCA  _SFR_MEM16(0x0A28)
#define TCE0_CCAL  _SFR_MEM8(0x0A28)
#define TCE0_CCAH  _SFR_MEM8(0x0A29)
#define TCE0_CCB  _SFR_MEM16(0x0A2A)
#define TCE0_CCBL  _SFR_MEM8(0x0A2A)
#define TCE0_CCBH  _SFR_MEM8(0x0A2B)
#define TCE0_CCC  _SFR_MEM16(0x0A2C)
#define TCE0_CCCL  _SFR_MEM8(0x0A2C)
#define TCE0_CCCH  _SFR_MEM8(0x0A2D)
#define TCE0_CCD  _SFR_MEM16(0x0A2E)
#define TCE0_CCDL  _SFR_MEM8(0x0A2E)
#define TCE0_CCDH  _SFR_MEM8(0x0A2F)
#define TCE0_PERBUF  _SFR_MEM16(0x0A36)
#define TCE0_PERBUFL  _SFR_MEM8(0x0A36)
#define TCE0_PERBUFH  _SFR_MEM8(0x0A37)
#define TCE0_CCABUF  _SFR_MEM16(0x0A38)
#define TCE0_CCABUFL  _SFR_MEM8(0x0A38)
#define TCE0_CCABUFH  _SFR_MEM8(0x0A39)
#define TCE0_CCBBUF  _SFR_MEM16(0x0A3A)
#define TCE0_CCBBUFL  _SFR_MEM8(0x0A3A)
#define TCE0_CCBBUFH  _SFR_MEM8(0x0A3B)
#define TCE0_CCCBUF  _SFR_MEM16(0x0A3C)
#define TCE0_CCCBUFL  _SFR_MEM8(0x0A3C)
#define TCE0_CCCBUFH  _SFR_MEM8(0x0A3D)
#define TCE0_CCDBUF  _SFR_MEM16(0x0A3E)
#define TCE0_CCDBUFL  _SFR_MEM8(0x0A3E)
#define TCE0_CCDBUFH  _SFR_MEM8(0x0A3F)


/* TC2 (TCE2) - 16-bit Timer/Counter type 2 */
#define TCE2_CTRLA  _SFR_MEM8(0x0A00)
#define TCE2_CTRLB  _SFR_MEM8(0x0A01)
#define TCE2_CTRLC  _SFR_MEM8(0x0A02)
#define TCE2_CTRLE  _SFR_MEM8(0x0A04)
#define TCE2_INTCTRLA  _SFR_MEM8(0x0A06)
#define TCE2_INTCTRLB  _SFR_MEM8(0x0A07)
#define TCE2_CTRLF  _SFR_MEM8(0x0A09)
#define TCE2_INTFLAGS  _SFR_MEM8(0x0A0C)
#define TCE2_LCNT  _SFR_MEM8(0x0A20)
#define TCE2_HCNT  _SFR_MEM8(0x0A21)
#define TCE2_LPER  _SFR_MEM8(0x0A26)
#define TCE2_HPER  _SFR_MEM8(0x0A27)
#define TCE2_LCMPA  _SFR_MEM8(0x0A28)
#define TCE2_HCMPA  _SFR_MEM8(0x0A29)
#define TCE2_LCMPB  _SFR_MEM8(0x0A2A)
#define TCE2_HCMPB  _SFR_MEM8(0x0A2B)
#define TCE2_LCMPC  _SFR_MEM8(0x0A2C)
#define TCE2_HCMPC  _SFR_MEM8(0x0A2D)
#define TCE2_LCMPD  _SFR_MEM8(0x0A2E)
#define TCE2_HCMPD  _SFR_MEM8(0x0A2F)


/* USART (USARTE0) - Universal Synchronous/Asynchronous Receiver/Transmitter */
#define USARTE0_DATA  _SFR_MEM8(0x0AA0)
#define USARTE0_STATUS  _SFR_MEM8(0x0AA1)
#define USARTE0_CTRLA  _SFR_MEM8(0x0AA3)
#define USARTE0_CTRLB  _SFR_MEM8(0x0AA4)
#define USARTE0_CTRLC  _SFR_MEM8(0x0AA5)
#define USARTE0_BAUDCTRLA  _SFR_MEM8(0x0AA6)
#define USARTE0_BAUDCTRLB  _SFR_MEM8(0x0AA7)


/* LCD - LCD Controller */
#define LCD_CTRLA  _SFR_MEM8(0x0D00)
#define LCD_CTRLB  _SFR_MEM8(0x0D01)
#define LCD_CTRLC  _SFR_MEM8(0x0D02)
#define LCD_INTCTRL  _SFR_MEM8(0x0D03)
#define LCD_INTFLAG  _SFR_MEM8(0x0D04)
#define LCD_CTRLD  _SFR_MEM8(0x0D05)
#define LCD_CTRLE  _SFR_MEM8(0x0D06)
#define LCD_CTRLF  _SFR_MEM8(0x0D07)
#define LCD_CTRLG  _SFR_MEM8(0x0D08)
#define LCD_CTRLH  _SFR_MEM8(0x0D09)
#define LCD_DATA0  _SFR_MEM8(0x0D10)
#define LCD_DATA1  _SFR_MEM8(0x0D11)
#define LCD_DATA2  _SFR_MEM8(0x0D12)
#define LCD_DATA3  _SFR_MEM8(0x0D13)
#define LCD_DATA4  _SFR_MEM8(0x0D14)
#define LCD_DATA5  _SFR_MEM8(0x0D15)
#define LCD_DATA6  _SFR_MEM8(0x0D16)
#define LCD_DATA7  _SFR_MEM8(0x0D17)
#define LCD_DATA8  _SFR_MEM8(0x0D18)
#define LCD_DATA9  _SFR_MEM8(0x0D19)
#define LCD_DATA10  _SFR_MEM8(0x0D1A)
#define LCD_DATA11  _SFR_MEM8(0x0D1B)
#define LCD_DATA12  _SFR_MEM8(0x0D1C)
#define LCD_DATA13  _SFR_MEM8(0x0D1D)
#define LCD_DATA14  _SFR_MEM8(0x0D1E)
#define LCD_DATA15  _SFR_MEM8(0x0D1F)
#define LCD_DATA16  _SFR_MEM8(0x0D20)
#define LCD_DATA17  _SFR_MEM8(0x0D21)
#define LCD_DATA18  _SFR_MEM8(0x0D22)
#define LCD_DATA19  _SFR_MEM8(0x0D23)



/*================== Bitfield Definitions ================== */

/* AC - Analog Comparator */
/* AC.AC0CTRL  bit masks and bit positions */
#define AC_ENABLE_bm  0x01  /* Enable bit mask. */
#define AC_ENABLE_bp  0  /* Enable bit position. */
#define AC_HYSMODE_gm  0x06  /* Hysteresis Mode group mask. */
#define AC_HYSMODE_gp  1  /* Hysteresis Mode group position. */
#define AC_HYSMODE0_bm  (1<<1)  /* Hysteresis Mode bit 0 mask. */
#define AC_HYSMODE0_bp  1  /* Hysteresis Mode bit 0 position. */
#define AC_HYSMODE1_bm  (1<<2)  /* Hysteresis Mode bit 1 mask. */
#define AC_HYSMODE1_bp  2  /* Hysteresis Mode bit 1 position. */
#define AC_INTLVL_gm  0x30  /* Interrupt Level group mask. */
#define AC_INTLVL_gp  4  /* Interrupt Level group position. */
#define AC_INTLVL0_bm  (1<<4)  /* Interrupt Level bit 0 mask. */
#define AC_INTLVL0_bp  4  /* Interrupt Level bit 0 position. */
#define AC_INTLVL1_bm  (1<<5)  /* Interrupt Level bit 1 mask. */
#define AC_INTLVL1_bp  5  /* Interrupt Level bit 1 position. */
#define AC_INTMODE_gm  0xC0  /* Interrupt Mode group mask. */
#define AC_INTMODE_gp  6  /* Interrupt Mode group position. */
#define AC_INTMODE0_bm  (1<<6)  /* Interrupt Mode bit 0 mask. */
#define AC_INTMODE0_bp  6  /* Interrupt Mode bit 0 position. */
#define AC_INTMODE1_bm  (1<<7)  /* Interrupt Mode bit 1 mask. */
#define AC_INTMODE1_bp  7  /* Interrupt Mode bit 1 position. */

/* AC.AC1CTRL  bit masks and bit positions */
/* AC_ENABLE  is already defined. */
/* AC_HYSMODE  is already defined. */
/* AC_INTLVL  is already defined. */
/* AC_INTMODE  is already defined. */

/* AC.AC0MUXCTRL  bit masks and bit positions */
#define AC_MUXNEG_gm  0x07  /* MUX Negative Input group mask. */
#define AC_MUXNEG_gp  0  /* MUX Negative Input group position. */
#define AC_MUXNEG0_bm  (1<<0)  /* MUX Negative Input bit 0 mask. */
#define AC_MUXNEG0_bp  0  /* MUX Negative Input bit 0 position. */
#define AC_MUXNEG1_bm  (1<<1)  /* MUX Negative Input bit 1 mask. */
#define AC_MUXNEG1_bp  1  /* MUX Negative Input bit 1 position. */
#define AC_MUXNEG2_bm  (1<<2)  /* MUX Negative Input bit 2 mask. */
#define AC_MUXNEG2_bp  2  /* MUX Negative Input bit 2 position. */
#define AC_MUXPOS_gm  0x38  /* MUX Positive Input group mask. */
#define AC_MUXPOS_gp  3  /* MUX Positive Input group position. */
#define AC_MUXPOS0_bm  (1<<3)  /* MUX Positive Input bit 0 mask. */
#define AC_MUXPOS0_bp  3  /* MUX Positive Input bit 0 position. */
#define AC_MUXPOS1_bm  (1<<4)  /* MUX Positive Input bit 1 mask. */
#define AC_MUXPOS1_bp  4  /* MUX Positive Input bit 1 position. */
#define AC_MUXPOS2_bm  (1<<5)  /* MUX Positive Input bit 2 mask. */
#define AC_MUXPOS2_bp  5  /* MUX Positive Input bit 2 position. */

/* AC.AC1MUXCTRL  bit masks and bit positions */
/* AC_MUXNEG  is already defined. */
/* AC_MUXPOS  is already defined. */

/* AC.CTRLA  bit masks and bit positions */
#define AC_AC0OUT_bm  0x01  /* Analog Comparator 0 Output Enable bit mask. */
#define AC_AC0OUT_bp  0  /* Analog Comparator 0 Output Enable bit position. */
#define AC_AC1OUT_bm  0x02  /* Analog Comparator 1 Output Enable bit mask. */
#define AC_AC1OUT_bp  1  /* Analog Comparator 1 Output Enable bit position. */

/* AC.CTRLB  bit masks and bit positions */
#define AC_SCALEFAC_gm  0x3F  /* VCC Voltage Scaler Factor group mask. */
#define AC_SCALEFAC_gp  0  /* VCC Voltage Scaler Factor group position. */
#define AC_SCALEFAC0_bm  (1<<0)  /* VCC Voltage Scaler Factor bit 0 mask. */
#define AC_SCALEFAC0_bp  0  /* VCC Voltage Scaler Factor bit 0 position. */
#define AC_SCALEFAC1_bm  (1<<1)  /* VCC Voltage Scaler Factor bit 1 mask. */
#define AC_SCALEFAC1_bp  1  /* VCC Voltage Scaler Factor bit 1 position. */
#define AC_SCALEFAC2_bm  (1<<2)  /* VCC Voltage Scaler Factor bit 2 mask. */
#define AC_SCALEFAC2_bp  2  /* VCC Voltage Scaler Factor bit 2 position. */
#define AC_SCALEFAC3_bm  (1<<3)  /* VCC Voltage Scaler Factor bit 3 mask. */
#define AC_SCALEFAC3_bp  3  /* VCC Voltage Scaler Factor bit 3 position. */
#define AC_SCALEFAC4_bm  (1<<4)  /* VCC Voltage Scaler Factor bit 4 mask. */
#define AC_SCALEFAC4_bp  4  /* VCC Voltage Scaler Factor bit 4 position. */
#define AC_SCALEFAC5_bm  (1<<5)  /* VCC Voltage Scaler Factor bit 5 mask. */
#define AC_SCALEFAC5_bp  5  /* VCC Voltage Scaler Factor bit 5 position. */

/* AC.WINCTRL  bit masks and bit positions */
#define AC_WINTLVL_gm  0x03  /* Window Interrupt Level group mask. */
#define AC_WINTLVL_gp  0  /* Window Interrupt Level group position. */
#define AC_WINTLVL0_bm  (1<<0)  /* Window Interrupt Level bit 0 mask. */
#define AC_WINTLVL0_bp  0  /* Window Interrupt Level bit 0 position. */
#define AC_WINTLVL1_bm  (1<<1)  /* Window Interrupt Level bit 1 mask. */
#define AC_WINTLVL1_bp  1  /* Window Interrupt Level bit 1 position. */
#define AC_WINTMODE_gm  0x0C  /* Window Interrupt Mode group mask. */
#define AC_WINTMODE_gp  2  /* Window Interrupt Mode group position. */
#define AC_WINTMODE0_bm  (1<<2)  /* Window Interrupt Mode bit 0 mask. */
#define AC_WINTMODE0_bp  2  /* Window Interrupt Mode bit 0 position. */
#define AC_WINTMODE1_bm  (1<<3)  /* Window Interrupt Mode bit 1 mask. */
#define AC_WINTMODE1_bp  3  /* Window Interrupt Mode bit 1 position. */
#define AC_WEN_bm  0x10  /* Window Mode Enable bit mask. */
#define AC_WEN_bp  4  /* Window Mode Enable bit position. */

/* AC.STATUS  bit masks and bit positions */
#define AC_AC0IF_bm  0x01  /* Analog Comparator 0 Interrupt Flag bit mask. */
#define AC_AC0IF_bp  0  /* Analog Comparator 0 Interrupt Flag bit position. */
#define AC_AC1IF_bm  0x02  /* Analog Comparator 1 Interrupt Flag bit mask. */
#define AC_AC1IF_bp  1  /* Analog Comparator 1 Interrupt Flag bit position. */
#define AC_WIF_bm  0x04  /* Window Mode Interrupt Flag bit mask. */
#define AC_WIF_bp  2  /* Window Mode Interrupt Flag bit position. */
#define AC_AC0STATE_bm  0x10  /* Analog Comparator 0 State bit mask. */
#define AC_AC0STATE_bp  4  /* Analog Comparator 0 State bit position. */
#define AC_AC1STATE_bm  0x20  /* Analog Comparator 1 State bit mask. */
#define AC_AC1STATE_bp  5  /* Analog Comparator 1 State bit position. */
#define AC_WSTATE_gm  0xC0  /* Window Mode State group mask. */
#define AC_WSTATE_gp  6  /* Window Mode State group position. */
#define AC_WSTATE0_bm  (1<<6)  /* Window Mode State bit 0 mask. */
#define AC_WSTATE0_bp  6  /* Window Mode State bit 0 position. */
#define AC_WSTATE1_bm  (1<<7)  /* Window Mode State bit 1 mask. */
#define AC_WSTATE1_bp  7  /* Window Mode State bit 1 position. */

/* AC.CURRCTRL  bit masks and bit positions */
#define AC_AC0CURR_bm  0x01  /* Analog Comparator 0 current source output bit mask. */
#define AC_AC0CURR_bp  0  /* Analog Comparator 0 current source output bit position. */
#define AC_AC1CURR_bm  0x02  /* Analog Comparator 1 current source output bit mask. */
#define AC_AC1CURR_bp  1  /* Analog Comparator 1 current source output bit position. */
#define AC_CURRMODE_bm  0x40  /* Current Mode bit mask. */
#define AC_CURRMODE_bp  6  /* Current Mode bit position. */
#define AC_CURREN_bm  0x80  /* Current Source Enable bit mask. */
#define AC_CURREN_bp  7  /* Current Source Enable bit position. */

/* AC.CURRCALIB  bit masks and bit positions */
#define AC_CALIB_gm  0x0F  /* Current Source Calibration group mask. */
#define AC_CALIB_gp  0  /* Current Source Calibration group position. */
#define AC_CALIB0_bm  (1<<0)  /* Current Source Calibration bit 0 mask. */
#define AC_CALIB0_bp  0  /* Current Source Calibration bit 0 position. */
#define AC_CALIB1_bm  (1<<1)  /* Current Source Calibration bit 1 mask. */
#define AC_CALIB1_bp  1  /* Current Source Calibration bit 1 position. */
#define AC_CALIB2_bm  (1<<2)  /* Current Source Calibration bit 2 mask. */
#define AC_CALIB2_bp  2  /* Current Source Calibration bit 2 position. */
#define AC_CALIB3_bm  (1<<3)  /* Current Source Calibration bit 3 mask. */
#define AC_CALIB3_bp  3  /* Current Source Calibration bit 3 position. */

/* ADC - Analog/Digital Converter */
/* ADC_CH.CTRL  bit masks and bit positions */
#define ADC_CH_INPUTMODE_gm  0x03  /* Input Mode Select group mask. */
#define ADC_CH_INPUTMODE_gp  0  /* Input Mode Select group position. */
#define ADC_CH_INPUTMODE0_bm  (1<<0)  /* Input Mode Select bit 0 mask. */
#define ADC_CH_INPUTMODE0_bp  0  /* Input Mode Select bit 0 position. */
#define ADC_CH_INPUTMODE1_bm  (1<<1)  /* Input Mode Select bit 1 mask. */
#define ADC_CH_INPUTMODE1_bp  1  /* Input Mode Select bit 1 position. */
#define ADC_CH_GAIN_gm  0x1C  /* Gain Factor group mask. */
#define ADC_CH_GAIN_gp  2  /* Gain Factor group position. */
#define ADC_CH_GAIN0_bm  (1<<2)  /* Gain Factor bit 0 mask. */
#define ADC_CH_GAIN0_bp  2  /* Gain Factor bit 0 position. */
#define ADC_CH_GAIN1_bm  (1<<3)  /* Gain Factor bit 1 mask. */
#define ADC_CH_GAIN1_bp  3  /* Gain Factor bit 1 position. */
#define ADC_CH_GAIN2_bm  (1<<4)  /* Gain Factor bit 2 mask. */
#define ADC_CH_GAIN2_bp  4  /* Gain Factor bit 2 position. */
#define ADC_CH_START_bm  0x80  /* Channel Start Conversion bit mask. */
#define ADC_CH_START_bp  7  /* Channel Start Conversion bit position. */

/* ADC_CH.MUXCTRL  bit masks and bit positions */
#define ADC_CH_MUXNEG_gm  0x07  /* MUX selection on Negative ADC input group mask. */
#define ADC_CH_MUXNEG_gp  0  /* MUX selection on Negative ADC input group position. */
#define ADC_CH_MUXNEG0_bm  (1<<0)  /* MUX selection on Negative ADC input bit 0 mask. */
#define ADC_CH_MUXNEG0_bp  0  /* MUX selection on Negative ADC input bit 0 position. */
#define ADC_CH_MUXNEG1_bm  (1<<1)  /* MUX selection on Negative ADC input bit 1 mask. */
#define ADC_CH_MUXNEG1_bp  1  /* MUX selection on Negative ADC input bit 1 position. */
#define ADC_CH_MUXNEG2_bm  (1<<2)  /* MUX selection on Negative ADC input bit 2 mask. */
#define ADC_CH_MUXNEG2_bp  2  /* MUX selection on Negative ADC input bit 2 position. */
#define ADC_CH_MUXNEGL_gm  0x07  /* MUX selection on Negative ADC Input Gain on 4 LSB pins group mask. */
#define ADC_CH_MUXNEGL_gp  0  /* MUX selection on Negative ADC Input Gain on 4 LSB pins group position. */
#define ADC_CH_MUXNEGL0_bm  (1<<0)  /* MUX selection on Negative ADC Input Gain on 4 LSB pins bit 0 mask. */
#define ADC_CH_MUXNEGL0_bp  0  /* MUX selection on Negative ADC Input Gain on 4 LSB pins bit 0 position. */
#define ADC_CH_MUXNEGL1_bm  (1<<1)  /* MUX selection on Negative ADC Input Gain on 4 LSB pins bit 1 mask. */
#define ADC_CH_MUXNEGL1_bp  1  /* MUX selection on Negative ADC Input Gain on 4 LSB pins bit 1 position. */
#define ADC_CH_MUXNEGL2_bm  (1<<2)  /* MUX selection on Negative ADC Input Gain on 4 LSB pins bit 2 mask. */
#define ADC_CH_MUXNEGL2_bp  2  /* MUX selection on Negative ADC Input Gain on 4 LSB pins bit 2 position. */
#define ADC_CH_MUXNEGH_gm  0x07  /* MUX selection on Negative ADC Input Gain on 4 MSB pins group mask. */
#define ADC_CH_MUXNEGH_gp  0  /* MUX selection on Negative ADC Input Gain on 4 MSB pins group position. */
#define ADC_CH_MUXNEGH0_bm  (1<<0)  /* MUX selection on Negative ADC Input Gain on 4 MSB pins bit 0 mask. */
#define ADC_CH_MUXNEGH0_bp  0  /* MUX selection on Negative ADC Input Gain on 4 MSB pins bit 0 position. */
#define ADC_CH_MUXNEGH1_bm  (1<<1)  /* MUX selection on Negative ADC Input Gain on 4 MSB pins bit 1 mask. */
#define ADC_CH_MUXNEGH1_bp  1  /* MUX selection on Negative ADC Input Gain on 4 MSB pins bit 1 position. */
#define ADC_CH_MUXNEGH2_bm  (1<<2)  /* MUX selection on Negative ADC Input Gain on 4 MSB pins bit 2 mask. */
#define ADC_CH_MUXNEGH2_bp  2  /* MUX selection on Negative ADC Input Gain on 4 MSB pins bit 2 position. */
#define ADC_CH_MUXPOS_gm  0x78  /* MUX selection on Positive ADC input group mask. */
#define ADC_CH_MUXPOS_gp  3  /* MUX selection on Positive ADC input group position. */
#define ADC_CH_MUXPOS0_bm  (1<<3)  /* MUX selection on Positive ADC input bit 0 mask. */
#define ADC_CH_MUXPOS0_bp  3  /* MUX selection on Positive ADC input bit 0 position. */
#define ADC_CH_MUXPOS1_bm  (1<<4)  /* MUX selection on Positive ADC input bit 1 mask. */
#define ADC_CH_MUXPOS1_bp  4  /* MUX selection on Positive ADC input bit 1 position. */
#define ADC_CH_MUXPOS2_bm  (1<<5)  /* MUX selection on Positive ADC input bit 2 mask. */
#define ADC_CH_MUXPOS2_bp  5  /* MUX selection on Positive ADC input bit 2 position. */
#define ADC_CH_MUXPOS3_bm  (1<<6)  /* MUX selection on Positive ADC input bit 3 mask. */
#define ADC_CH_MUXPOS3_bp  6  /* MUX selection on Positive ADC input bit 3 position. */
#define ADC_CH_MUXINT_gm  0x78  /* MUX selection on Internal ADC input group mask. */
#define ADC_CH_MUXINT_gp  3  /* MUX selection on Internal ADC input group position. */
#define ADC_CH_MUXINT0_bm  (1<<3)  /* MUX selection on Internal ADC input bit 0 mask. */
#define ADC_CH_MUXINT0_bp  3  /* MUX selection on Internal ADC input bit 0 position. */
#define ADC_CH_MUXINT1_bm  (1<<4)  /* MUX selection on Internal ADC input bit 1 mask. */
#define ADC_CH_MUXINT1_bp  4  /* MUX selection on Internal ADC input bit 1 position. */
#define ADC_CH_MUXINT2_bm  (1<<5)  /* MUX selection on Internal ADC input bit 2 mask. */
#define ADC_CH_MUXINT2_bp  5  /* MUX selection on Internal ADC input bit 2 position. */
#define ADC_CH_MUXINT3_bm  (1<<6)  /* MUX selection on Internal ADC input bit 3 mask. */
#define ADC_CH_MUXINT3_bp  6  /* MUX selection on Internal ADC input bit 3 position. */

/* ADC_CH.INTCTRL  bit masks and bit positions */
#define ADC_CH_INTLVL_gm  0x03  /* Interrupt Level group mask. */
#define ADC_CH_INTLVL_gp  0  /* Interrupt Level group position. */
#define ADC_CH_INTLVL0_bm  (1<<0)  /* Interrupt Level bit 0 mask. */
#define ADC_CH_INTLVL0_bp  0  /* Interrupt Level bit 0 position. */
#define ADC_CH_INTLVL1_bm  (1<<1)  /* Interrupt Level bit 1 mask. */
#define ADC_CH_INTLVL1_bp  1  /* Interrupt Level bit 1 position. */
#define ADC_CH_INTMODE_gm  0x0C  /* Interrupt Mode group mask. */
#define ADC_CH_INTMODE_gp  2  /* Interrupt Mode group position. */
#define ADC_CH_INTMODE0_bm  (1<<2)  /* Interrupt Mode bit 0 mask. */
#define ADC_CH_INTMODE0_bp  2  /* Interrupt Mode bit 0 position. */
#define ADC_CH_INTMODE1_bm  (1<<3)  /* Interrupt Mode bit 1 mask. */
#define ADC_CH_INTMODE1_bp  3  /* Interrupt Mode bit 1 position. */

/* ADC_CH.INTFLAGS  bit masks and bit positions */
#define ADC_CH_CHIF_bm  0x01  /* Channel Interrupt Flag bit mask. */
#define ADC_CH_CHIF_bp  0  /* Channel Interrupt Flag bit position. */


/* ADC_CH.SCAN  bit masks and bit positions */
#define ADC_CH_COUNT_gm  0x0F  /* Number of Channels included in scan group mask. */
#define ADC_CH_COUNT_gp  0  /* Number of Channels included in scan group position. */
#define ADC_CH_COUNT0_bm  (1<<0)  /* Number of Channels included in scan bit 0 mask. */
#define ADC_CH_COUNT0_bp  0  /* Number of Channels included in scan bit 0 position. */
#define ADC_CH_COUNT1_bm  (1<<1)  /* Number of Channels included in scan bit 1 mask. */
#define ADC_CH_COUNT1_bp  1  /* Number of Channels included in scan bit 1 position. */
#define ADC_CH_COUNT2_bm  (1<<2)  /* Number of Channels included in scan bit 2 mask. */
#define ADC_CH_COUNT2_bp  2  /* Number of Channels included in scan bit 2 position. */
#define ADC_CH_COUNT3_bm  (1<<3)  /* Number of Channels included in scan bit 3 mask. */
#define ADC_CH_COUNT3_bp  3  /* Number of Channels included in scan bit 3 position. */
#define ADC_CH_OFFSET_gm  0xF0  /* Positive MUX setting offset group mask. */
#define ADC_CH_OFFSET_gp  4  /* Positive MUX setting offset group position. */
#define ADC_CH_OFFSET0_bm  (1<<4)  /* Positive MUX setting offset bit 0 mask. */
#define ADC_CH_OFFSET0_bp  4  /* Positive MUX setting offset bit 0 position. */
#define ADC_CH_OFFSET1_bm  (1<<5)  /* Positive MUX setting offset bit 1 mask. */
#define ADC_CH_OFFSET1_bp  5  /* Positive MUX setting offset bit 1 position. */
#define ADC_CH_OFFSET2_bm  (1<<6)  /* Positive MUX setting offset bit 2 mask. */
#define ADC_CH_OFFSET2_bp  6  /* Positive MUX setting offset bit 2 position. */
#define ADC_CH_OFFSET3_bm  (1<<7)  /* Positive MUX setting offset bit 3 mask. */
#define ADC_CH_OFFSET3_bp  7  /* Positive MUX setting offset bit 3 position. */

/* ADC.CTRLA  bit masks and bit positions */
#define ADC_ENABLE_bm  0x01  /* Enable ADC bit mask. */
#define ADC_ENABLE_bp  0  /* Enable ADC bit position. */
#define ADC_FLUSH_bm  0x02  /* ADC Flush bit mask. */
#define ADC_FLUSH_bp  1  /* ADC Flush bit position. */
#define ADC_CH0START_bm  0x04  /* Channel 0 Start Conversion bit mask. */
#define ADC_CH0START_bp  2  /* Channel 0 Start Conversion bit position. */

/* ADC.CTRLB  bit masks and bit positions */
#define ADC_RESOLUTION_gm  0x06  /* Result Resolution group mask. */
#define ADC_RESOLUTION_gp  1  /* Result Resolution group position. */
#define ADC_RESOLUTION0_bm  (1<<1)  /* Result Resolution bit 0 mask. */
#define ADC_RESOLUTION0_bp  1  /* Result Resolution bit 0 position. */
#define ADC_RESOLUTION1_bm  (1<<2)  /* Result Resolution bit 1 mask. */
#define ADC_RESOLUTION1_bp  2  /* Result Resolution bit 1 position. */
#define ADC_FREERUN_bm  0x08  /* Free Running Mode Enable bit mask. */
#define ADC_FREERUN_bp  3  /* Free Running Mode Enable bit position. */
#define ADC_CONMODE_bm  0x10  /* Conversion Mode bit mask. */
#define ADC_CONMODE_bp  4  /* Conversion Mode bit position. */
#define ADC_CURRLIMIT_gm  0x60  /* Current limit group mask. */
#define ADC_CURRLIMIT_gp  5  /* Current limit group position. */
#define ADC_CURRLIMIT0_bm  (1<<5)  /* Current limit bit 0 mask. */
#define ADC_CURRLIMIT0_bp  5  /* Current limit bit 0 position. */
#define ADC_CURRLIMIT1_bm  (1<<6)  /* Current limit bit 1 mask. */
#define ADC_CURRLIMIT1_bp  6  /* Current limit bit 1 position. */

/* ADC.REFCTRL  bit masks and bit positions */
#define ADC_TEMPREF_bm  0x01  /* Temperature Reference Enable bit mask. */
#define ADC_TEMPREF_bp  0  /* Temperature Reference Enable bit position. */
#define ADC_BANDGAP_bm  0x02  /* Bandgap enable bit mask. */
#define ADC_BANDGAP_bp  1  /* Bandgap enable bit position. */
#define ADC_REFSEL_gm  0x70  /* Reference Selection group mask. */
#define ADC_REFSEL_gp  4  /* Reference Selection group position. */
#define ADC_REFSEL0_bm  (1<<4)  /* Reference Selection bit 0 mask. */
#define ADC_REFSEL0_bp  4  /* Reference Selection bit 0 position. */
#define ADC_REFSEL1_bm  (1<<5)  /* Reference Selection bit 1 mask. */
#define ADC_REFSEL1_bp  5  /* Reference Selection bit 1 position. */
#define ADC_REFSEL2_bm  (1<<6)  /* Reference Selection bit 2 mask. */
#define ADC_REFSEL2_bp  6  /* Reference Selection bit 2 position. */

/* ADC.EVCTRL  bit masks and bit positions */
#define ADC_EVACT_gm  0x07  /* Event Action Select group mask. */
#define ADC_EVACT_gp  0  /* Event Action Select group position. */
#define ADC_EVACT0_bm  (1<<0)  /* Event Action Select bit 0 mask. */
#define ADC_EVACT0_bp  0  /* Event Action Select bit 0 position. */
#define ADC_EVACT1_bm  (1<<1)  /* Event Action Select bit 1 mask. */
#define ADC_EVACT1_bp  1  /* Event Action Select bit 1 position. */
#define ADC_EVACT2_bm  (1<<2)  /* Event Action Select bit 2 mask. */
#define ADC_EVACT2_bp  2  /* Event Action Select bit 2 position. */
#define ADC_EVSEL_gm  0x18  /* Event Input Select group mask. */
#define ADC_EVSEL_gp  3  /* Event Input Select group position. */
#define ADC_EVSEL0_bm  (1<<3)  /* Event Input Select bit 0 mask. */
#define ADC_EVSEL0_bp  3  /* Event Input Select bit 0 position. */
#define ADC_EVSEL1_bm  (1<<4)  /* Event Input Select bit 1 mask. */
#define ADC_EVSEL1_bp  4  /* Event Input Select bit 1 position. */

/* ADC.PRESCALER  bit masks and bit positions */
#define ADC_PRESCALER_gm  0x07  /* Clock Prescaler Selection group mask. */
#define ADC_PRESCALER_gp  0  /* Clock Prescaler Selection group position. */
#define ADC_PRESCALER0_bm  (1<<0)  /* Clock Prescaler Selection bit 0 mask. */
#define ADC_PRESCALER0_bp  0  /* Clock Prescaler Selection bit 0 position. */
#define ADC_PRESCALER1_bm  (1<<1)  /* Clock Prescaler Selection bit 1 mask. */
#define ADC_PRESCALER1_bp  1  /* Clock Prescaler Selection bit 1 position. */
#define ADC_PRESCALER2_bm  (1<<2)  /* Clock Prescaler Selection bit 2 mask. */
#define ADC_PRESCALER2_bp  2  /* Clock Prescaler Selection bit 2 position. */

/* ADC.INTFLAGS  bit masks and bit positions */
#define ADC_CH0IF_bm  0x01  /* Channel 0 Interrupt Flag bit mask. */
#define ADC_CH0IF_bp  0  /* Channel 0 Interrupt Flag bit position. */


/* ADC.SAMPCTRL  bit masks and bit positions */
#define ADC_SAMPVAL_gm  0x3F  /* Sampling time control register group mask. */
#define ADC_SAMPVAL_gp  0  /* Sampling time control register group position. */
#define ADC_SAMPVAL0_bm  (1<<0)  /* Sampling time control register bit 0 mask. */
#define ADC_SAMPVAL0_bp  0  /* Sampling time control register bit 0 position. */
#define ADC_SAMPVAL1_bm  (1<<1)  /* Sampling time control register bit 1 mask. */
#define ADC_SAMPVAL1_bp  1  /* Sampling time control register bit 1 position. */
#define ADC_SAMPVAL2_bm  (1<<2)  /* Sampling time control register bit 2 mask. */
#define ADC_SAMPVAL2_bp  2  /* Sampling time control register bit 2 position. */
#define ADC_SAMPVAL3_bm  (1<<3)  /* Sampling time control register bit 3 mask. */
#define ADC_SAMPVAL3_bp  3  /* Sampling time control register bit 3 position. */
#define ADC_SAMPVAL4_bm  (1<<4)  /* Sampling time control register bit 4 mask. */
#define ADC_SAMPVAL4_bp  4  /* Sampling time control register bit 4 position. */
#define ADC_SAMPVAL5_bm  (1<<5)  /* Sampling time control register bit 5 mask. */
#define ADC_SAMPVAL5_bp  5  /* Sampling time control register bit 5 position. */




/* AES - AES Module */
/* AES.CTRL  bit masks and bit positions */
#define AES_XOR_bm  0x04  /* State XOR Load Enable bit mask. */
#define AES_XOR_bp  2  /* State XOR Load Enable bit position. */
#define AES_DECRYPT_bm  0x10  /* Decryption / Direction bit mask. */
#define AES_DECRYPT_bp  4  /* Decryption / Direction bit position. */
#define AES_RESET_bm  0x20  /* AES Software Reset bit mask. */
#define AES_RESET_bp  5  /* AES Software Reset bit position. */
#define AES_AUTO_bm  0x40  /* Auto Start Trigger bit mask. */
#define AES_AUTO_bp  6  /* Auto Start Trigger bit position. */
#define AES_START_bm  0x80  /* Start/Run bit mask. */
#define AES_START_bp  7  /* Start/Run bit position. */

/* AES.STATUS  bit masks and bit positions */
#define AES_SRIF_bm  0x01  /* State Ready Interrupt Flag bit mask. */
#define AES_SRIF_bp  0  /* State Ready Interrupt Flag bit position. */
#define AES_ERROR_bm  0x80  /* AES Error bit mask. */
#define AES_ERROR_bp  7  /* AES Error bit position. */



/* AES.INTCTRL  bit masks and bit positions */
#define AES_INTLVL_gm  0x03  /* Interrupt level group mask. */
#define AES_INTLVL_gp  0  /* Interrupt level group position. */
#define AES_INTLVL0_bm  (1<<0)  /* Interrupt level bit 0 mask. */
#define AES_INTLVL0_bp  0  /* Interrupt level bit 0 position. */
#define AES_INTLVL1_bm  (1<<1)  /* Interrupt level bit 1 mask. */
#define AES_INTLVL1_bp  1  /* Interrupt level bit 1 position. */

/* AWEX - Timer/Counter Advanced Waveform Extension */
/* AWEX.CTRL  bit masks and bit positions */
#define AWEX_DTICCAEN_bm  0x01  /* Dead Time Insertion Compare Channel A Enable bit mask. */
#define AWEX_DTICCAEN_bp  0  /* Dead Time Insertion Compare Channel A Enable bit position. */
#define AWEX_DTICCBEN_bm  0x02  /* Dead Time Insertion Compare Channel B Enable bit mask. */
#define AWEX_DTICCBEN_bp  1  /* Dead Time Insertion Compare Channel B Enable bit position. */
#define AWEX_DTICCCEN_bm  0x04  /* Dead Time Insertion Compare Channel C Enable bit mask. */
#define AWEX_DTICCCEN_bp  2  /* Dead Time Insertion Compare Channel C Enable bit position. */
#define AWEX_DTICCDEN_bm  0x08  /* Dead Time Insertion Compare Channel D Enable bit mask. */
#define AWEX_DTICCDEN_bp  3  /* Dead Time Insertion Compare Channel D Enable bit position. */
#define AWEX_CWCM_bm  0x10  /* Common Waveform Channel Mode bit mask. */
#define AWEX_CWCM_bp  4  /* Common Waveform Channel Mode bit position. */
#define AWEX_PGM_bm  0x20  /* Pattern Generation Mode bit mask. */
#define AWEX_PGM_bp  5  /* Pattern Generation Mode bit position. */


/* AWEX.FDCTRL  bit masks and bit positions */
#define AWEX_FDACT_gm  0x03  /* Fault Detect Action group mask. */
#define AWEX_FDACT_gp  0  /* Fault Detect Action group position. */
#define AWEX_FDACT0_bm  (1<<0)  /* Fault Detect Action bit 0 mask. */
#define AWEX_FDACT0_bp  0  /* Fault Detect Action bit 0 position. */
#define AWEX_FDACT1_bm  (1<<1)  /* Fault Detect Action bit 1 mask. */
#define AWEX_FDACT1_bp  1  /* Fault Detect Action bit 1 position. */
#define AWEX_FDMODE_bm  0x04  /* Fault Detect Mode bit mask. */
#define AWEX_FDMODE_bp  2  /* Fault Detect Mode bit position. */
#define AWEX_FDDBD_bm  0x10  /* Fault Detect on Disable Break Disable bit mask. */
#define AWEX_FDDBD_bp  4  /* Fault Detect on Disable Break Disable bit position. */

/* AWEX.STATUS  bit masks and bit positions */
#define AWEX_DTLSBUFV_bm  0x01  /* Dead Time Low Side Buffer Valid bit mask. */
#define AWEX_DTLSBUFV_bp  0  /* Dead Time Low Side Buffer Valid bit position. */
#define AWEX_DTHSBUFV_bm  0x02  /* Dead Time High Side Buffer Valid bit mask. */
#define AWEX_DTHSBUFV_bp  1  /* Dead Time High Side Buffer Valid bit position. */
#define AWEX_FDF_bm  0x04  /* Fault Detect Flag bit mask. */
#define AWEX_FDF_bp  2  /* Fault Detect Flag bit position. */

/* AWEX.STATUSSET  bit masks and bit positions */
/* AWEX_DTLSBUFV  is already defined. */
/* AWEX_DTHSBUFV  is already defined. */
/* AWEX_FDF  is already defined. */








/* CLK - Clock System */
/* CLK.CTRL  bit masks and bit positions */
#define CLK_SCLKSEL_gm  0x07  /* System Clock Selection group mask. */
#define CLK_SCLKSEL_gp  0  /* System Clock Selection group position. */
#define CLK_SCLKSEL0_bm  (1<<0)  /* System Clock Selection bit 0 mask. */
#define CLK_SCLKSEL0_bp  0  /* System Clock Selection bit 0 position. */
#define CLK_SCLKSEL1_bm  (1<<1)  /* System Clock Selection bit 1 mask. */
#define CLK_SCLKSEL1_bp  1  /* System Clock Selection bit 1 position. */
#define CLK_SCLKSEL2_bm  (1<<2)  /* System Clock Selection bit 2 mask. */
#define CLK_SCLKSEL2_bp  2  /* System Clock Selection bit 2 position. */

/* CLK.PSCTRL  bit masks and bit positions */
#define CLK_PSBCDIV_gm  0x03  /* Prescaler B and C Division factor group mask. */
#define CLK_PSBCDIV_gp  0  /* Prescaler B and C Division factor group position. */
#define CLK_PSBCDIV0_bm  (1<<0)  /* Prescaler B and C Division factor bit 0 mask. */
#define CLK_PSBCDIV0_bp  0  /* Prescaler B and C Division factor bit 0 position. */
#define CLK_PSBCDIV1_bm  (1<<1)  /* Prescaler B and C Division factor bit 1 mask. */
#define CLK_PSBCDIV1_bp  1  /* Prescaler B and C Division factor bit 1 position. */
#define CLK_PSADIV_gm  0x7C  /* Prescaler A Division Factor group mask. */
#define CLK_PSADIV_gp  2  /* Prescaler A Division Factor group position. */
#define CLK_PSADIV0_bm  (1<<2)  /* Prescaler A Division Factor bit 0 mask. */
#define CLK_PSADIV0_bp  2  /* Prescaler A Division Factor bit 0 position. */
#define CLK_PSADIV1_bm  (1<<3)  /* Prescaler A Division Factor bit 1 mask. */
#define CLK_PSADIV1_bp  3  /* Prescaler A Division Factor bit 1 position. */
#define CLK_PSADIV2_bm  (1<<4)  /* Prescaler A Division Factor bit 2 mask. */
#define CLK_PSADIV2_bp  4  /* Prescaler A Division Factor bit 2 position. */
#define CLK_PSADIV3_bm  (1<<5)  /* Prescaler A Division Factor bit 3 mask. */
#define CLK_PSADIV3_bp  5  /* Prescaler A Division Factor bit 3 position. */
#define CLK_PSADIV4_bm  (1<<6)  /* Prescaler A Division Factor bit 4 mask. */
#define CLK_PSADIV4_bp  6  /* Prescaler A Division Factor bit 4 position. */

/* CLK.LOCK  bit masks and bit positions */
#define CLK_LOCK_bm  0x01  /* Clock System Lock bit mask. */
#define CLK_LOCK_bp  0  /* Clock System Lock bit position. */

/* CLK.RTCCTRL  bit masks and bit positions */
#define CLK_RTCEN_bm  0x01  /* Clock Source Enable bit mask. */
#define CLK_RTCEN_bp  0  /* Clock Source Enable bit position. */
#define CLK_RTCSRC_gm  0x0E  /* Clock Source group mask. */
#define CLK_RTCSRC_gp  1  /* Clock Source group position. */
#define CLK_RTCSRC0_bm  (1<<1)  /* Clock Source bit 0 mask. */
#define CLK_RTCSRC0_bp  1  /* Clock Source bit 0 position. */
#define CLK_RTCSRC1_bm  (1<<2)  /* Clock Source bit 1 mask. */
#define CLK_RTCSRC1_bp  2  /* Clock Source bit 1 position. */
#define CLK_RTCSRC2_bm  (1<<3)  /* Clock Source bit 2 mask. */
#define CLK_RTCSRC2_bp  3  /* Clock Source bit 2 position. */

/* CLK.USBCTRL  bit masks and bit positions */
#define CLK_USBSEN_bm  0x01  /* Clock Source Enable bit mask. */
#define CLK_USBSEN_bp  0  /* Clock Source Enable bit position. */
#define CLK_USBSRC_gm  0x06  /* Clock Source group mask. */
#define CLK_USBSRC_gp  1  /* Clock Source group position. */
#define CLK_USBSRC0_bm  (1<<1)  /* Clock Source bit 0 mask. */
#define CLK_USBSRC0_bp  1  /* Clock Source bit 0 position. */
#define CLK_USBSRC1_bm  (1<<2)  /* Clock Source bit 1 mask. */
#define CLK_USBSRC1_bp  2  /* Clock Source bit 1 position. */
#define CLK_USBPSDIV_gm  0x38  /* Prescaler Division Factor group mask. */
#define CLK_USBPSDIV_gp  3  /* Prescaler Division Factor group position. */
#define CLK_USBPSDIV0_bm  (1<<3)  /* Prescaler Division Factor bit 0 mask. */
#define CLK_USBPSDIV0_bp  3  /* Prescaler Division Factor bit 0 position. */
#define CLK_USBPSDIV1_bm  (1<<4)  /* Prescaler Division Factor bit 1 mask. */
#define CLK_USBPSDIV1_bp  4  /* Prescaler Division Factor bit 1 position. */
#define CLK_USBPSDIV2_bm  (1<<5)  /* Prescaler Division Factor bit 2 mask. */
#define CLK_USBPSDIV2_bp  5  /* Prescaler Division Factor bit 2 position. */

/* CPU - CPU */
/* CPU.CCP  bit masks and bit positions */
#define CPU_CCP_gm  0xFF  /* CCP signature group mask. */
#define CPU_CCP_gp  0  /* CCP signature group position. */
#define CPU_CCP0_bm  (1<<0)  /* CCP signature bit 0 mask. */
#define CPU_CCP0_bp  0  /* CCP signature bit 0 position. */
#define CPU_CCP1_bm  (1<<1)  /* CCP signature bit 1 mask. */
#define CPU_CCP1_bp  1  /* CCP signature bit 1 position. */
#define CPU_CCP2_bm  (1<<2)  /* CCP signature bit 2 mask. */
#define CPU_CCP2_bp  2  /* CCP signature bit 2 position. */
#define CPU_CCP3_bm  (1<<3)  /* CCP signature bit 3 mask. */
#define CPU_CCP3_bp  3  /* CCP signature bit 3 position. */
#define CPU_CCP4_bm  (1<<4)  /* CCP signature bit 4 mask. */
#define CPU_CCP4_bp  4  /* CCP signature bit 4 position. */
#define CPU_CCP5_bm  (1<<5)  /* CCP signature bit 5 mask. */
#define CPU_CCP5_bp  5  /* CCP signature bit 5 position. */
#define CPU_CCP6_bm  (1<<6)  /* CCP signature bit 6 mask. */
#define CPU_CCP6_bp  6  /* CCP signature bit 6 position. */
#define CPU_CCP7_bm  (1<<7)  /* CCP signature bit 7 mask. */
#define CPU_CCP7_bp  7  /* CCP signature bit 7 position. */








/* CPU.SREG  bit masks and bit positions */
#define CPU_C_bm  0x01  /* Carry Flag bit mask. */
#define CPU_C_bp  0  /* Carry Flag bit position. */
#define CPU_Z_bm  0x02  /* Zero Flag bit mask. */
#define CPU_Z_bp  1  /* Zero Flag bit position. */
#define CPU_N_bm  0x04  /* Negative Flag bit mask. */
#define CPU_N_bp  2  /* Negative Flag bit position. */
#define CPU_V_bm  0x08  /* Two's Complement Overflow Flag bit mask. */
#define CPU_V_bp  3  /* Two's Complement Overflow Flag bit position. */
#define CPU_S_bm  0x10  /* N Exclusive Or V Flag bit mask. */
#define CPU_S_bp  4  /* N Exclusive Or V Flag bit position. */
#define CPU_H_bm  0x20  /* Half Carry Flag bit mask. */
#define CPU_H_bp  5  /* Half Carry Flag bit position. */
#define CPU_T_bm  0x40  /* Transfer Bit bit mask. */
#define CPU_T_bp  6  /* Transfer Bit bit position. */
#define CPU_I_bm  0x80  /* Global Interrupt Enable Flag bit mask. */
#define CPU_I_bp  7  /* Global Interrupt Enable Flag bit position. */

/* CRC - Cyclic Redundancy Checker */
/* CRC.CTRL  bit masks and bit positions */
#define CRC_SOURCE_gm  0x0F  /* Input Source group mask. */
#define CRC_SOURCE_gp  0  /* Input Source group position. */
#define CRC_SOURCE0_bm  (1<<0)  /* Input Source bit 0 mask. */
#define CRC_SOURCE0_bp  0  /* Input Source bit 0 position. */
#define CRC_SOURCE1_bm  (1<<1)  /* Input Source bit 1 mask. */
#define CRC_SOURCE1_bp  1  /* Input Source bit 1 position. */
#define CRC_SOURCE2_bm  (1<<2)  /* Input Source bit 2 mask. */
#define CRC_SOURCE2_bp  2  /* Input Source bit 2 position. */
#define CRC_SOURCE3_bm  (1<<3)  /* Input Source bit 3 mask. */
#define CRC_SOURCE3_bp  3  /* Input Source bit 3 position. */
#define CRC_CRC32_bm  0x20  /* CRC Mode bit mask. */
#define CRC_CRC32_bp  5  /* CRC Mode bit position. */
#define CRC_RESET_gm  0xC0  /* Reset group mask. */
#define CRC_RESET_gp  6  /* Reset group position. */
#define CRC_RESET0_bm  (1<<6)  /* Reset bit 0 mask. */
#define CRC_RESET0_bp  6  /* Reset bit 0 position. */
#define CRC_RESET1_bm  (1<<7)  /* Reset bit 1 mask. */
#define CRC_RESET1_bp  7  /* Reset bit 1 position. */

/* CRC.STATUS  bit masks and bit positions */
#define CRC_BUSY_bm  0x01  /* Busy bit mask. */
#define CRC_BUSY_bp  0  /* Busy bit position. */
#define CRC_ZERO_bm  0x02  /* Zero detection bit mask. */
#define CRC_ZERO_bp  1  /* Zero detection bit position. */






/* DFLL - DFLL */
/* DFLL.CTRL  bit masks and bit positions */
#define DFLL_ENABLE_bm  0x01  /* DFLL Enable bit mask. */
#define DFLL_ENABLE_bp  0  /* DFLL Enable bit position. */

/* DFLL.CALA  bit masks and bit positions */
#define DFLL_CALL_gm  0x7F  /* DFLL Calibration Value A group mask. */
#define DFLL_CALL_gp  0  /* DFLL Calibration Value A group position. */
#define DFLL_CALL0_bm  (1<<0)  /* DFLL Calibration Value A bit 0 mask. */
#define DFLL_CALL0_bp  0  /* DFLL Calibration Value A bit 0 position. */
#define DFLL_CALL1_bm  (1<<1)  /* DFLL Calibration Value A bit 1 mask. */
#define DFLL_CALL1_bp  1  /* DFLL Calibration Value A bit 1 position. */
#define DFLL_CALL2_bm  (1<<2)  /* DFLL Calibration Value A bit 2 mask. */
#define DFLL_CALL2_bp  2  /* DFLL Calibration Value A bit 2 position. */
#define DFLL_CALL3_bm  (1<<3)  /* DFLL Calibration Value A bit 3 mask. */
#define DFLL_CALL3_bp  3  /* DFLL Calibration Value A bit 3 position. */
#define DFLL_CALL4_bm  (1<<4)  /* DFLL Calibration Value A bit 4 mask. */
#define DFLL_CALL4_bp  4  /* DFLL Calibration Value A bit 4 position. */
#define DFLL_CALL5_bm  (1<<5)  /* DFLL Calibration Value A bit 5 mask. */
#define DFLL_CALL5_bp  5  /* DFLL Calibration Value A bit 5 position. */
#define DFLL_CALL6_bm  (1<<6)  /* DFLL Calibration Value A bit 6 mask. */
#define DFLL_CALL6_bp  6  /* DFLL Calibration Value A bit 6 position. */

/* DFLL.CALB  bit masks and bit positions */
#define DFLL_CALH_gm  0x3F  /* DFLL Calibration Value B group mask. */
#define DFLL_CALH_gp  0  /* DFLL Calibration Value B group position. */
#define DFLL_CALH0_bm  (1<<0)  /* DFLL Calibration Value B bit 0 mask. */
#define DFLL_CALH0_bp  0  /* DFLL Calibration Value B bit 0 position. */
#define DFLL_CALH1_bm  (1<<1)  /* DFLL Calibration Value B bit 1 mask. */
#define DFLL_CALH1_bp  1  /* DFLL Calibration Value B bit 1 position. */
#define DFLL_CALH2_bm  (1<<2)  /* DFLL Calibration Value B bit 2 mask. */
#define DFLL_CALH2_bp  2  /* DFLL Calibration Value B bit 2 position. */
#define DFLL_CALH3_bm  (1<<3)  /* DFLL Calibration Value B bit 3 mask. */
#define DFLL_CALH3_bp  3  /* DFLL Calibration Value B bit 3 position. */
#define DFLL_CALH4_bm  (1<<4)  /* DFLL Calibration Value B bit 4 mask. */
#define DFLL_CALH4_bp  4  /* DFLL Calibration Value B bit 4 position. */
#define DFLL_CALH5_bm  (1<<5)  /* DFLL Calibration Value B bit 5 mask. */
#define DFLL_CALH5_bp  5  /* DFLL Calibration Value B bit 5 position. */




/* DMA - DMA Controller */
/* DMA_CH.CTRLA  bit masks and bit positions */
#define DMA_CH_BURSTLEN_gm  0x03  /* Channel Transfer Mode group mask. */
#define DMA_CH_BURSTLEN_gp  0  /* Channel Transfer Mode group position. */
#define DMA_CH_BURSTLEN0_bm  (1<<0)  /* Channel Transfer Mode bit 0 mask. */
#define DMA_CH_BURSTLEN0_bp  0  /* Channel Transfer Mode bit 0 position. */
#define DMA_CH_BURSTLEN1_bm  (1<<1)  /* Channel Transfer Mode bit 1 mask. */
#define DMA_CH_BURSTLEN1_bp  1  /* Channel Transfer Mode bit 1 position. */
#define DMA_CH_SINGLE_bm  0x04  /* Channel Single Shot Data Transfer bit mask. */
#define DMA_CH_SINGLE_bp  2  /* Channel Single Shot Data Transfer bit position. */
#define DMA_CH_TRFREQ_bm  0x10  /* Channel Transfer Request bit mask. */
#define DMA_CH_TRFREQ_bp  4  /* Channel Transfer Request bit position. */
#define DMA_CH_REPEAT_bm  0x20  /* Channel Repeat Mode bit mask. */
#define DMA_CH_REPEAT_bp  5  /* Channel Repeat Mode bit position. */
#define DMA_CH_CHRST_bm  0x40  /* Channel Software Reset bit mask. */
#define DMA_CH_CHRST_bp  6  /* Channel Software Reset bit position. */
#define DMA_CH_CHEN_bm  0x80  /* Channel Enable bit mask. */
#define DMA_CH_CHEN_bp  7  /* Channel Enable bit position. */

/* DMA_CH.CTRLB  bit masks and bit positions */
#define DMA_CH_TRNINTLVL_gm  0x03  /* Transaction Complete Interrupt Level group mask. */
#define DMA_CH_TRNINTLVL_gp  0  /* Transaction Complete Interrupt Level group position. */
#define DMA_CH_TRNINTLVL0_bm  (1<<0)  /* Transaction Complete Interrupt Level bit 0 mask. */
#define DMA_CH_TRNINTLVL0_bp  0  /* Transaction Complete Interrupt Level bit 0 position. */
#define DMA_CH_TRNINTLVL1_bm  (1<<1)  /* Transaction Complete Interrupt Level bit 1 mask. */
#define DMA_CH_TRNINTLVL1_bp  1  /* Transaction Complete Interrupt Level bit 1 position. */
#define DMA_CH_ERRINTLVL_gm  0x0C  /* Transfer Error Interrupt Level group mask. */
#define DMA_CH_ERRINTLVL_gp  2  /* Transfer Error Interrupt Level group position. */
#define DMA_CH_ERRINTLVL0_bm  (1<<2)  /* Transfer Error Interrupt Level bit 0 mask. */
#define DMA_CH_ERRINTLVL0_bp  2  /* Transfer Error Interrupt Level bit 0 position. */
#define DMA_CH_ERRINTLVL1_bm  (1<<3)  /* Transfer Error Interrupt Level bit 1 mask. */
#define DMA_CH_ERRINTLVL1_bp  3  /* Transfer Error Interrupt Level bit 1 position. */
#define DMA_CH_TRNIF_bm  0x10  /* Transaction Complete Interrupt Flag bit mask. */
#define DMA_CH_TRNIF_bp  4  /* Transaction Complete Interrupt Flag bit position. */
#define DMA_CH_ERRIF_bm  0x20  /* Block Transfer Error Interrupt Flag bit mask. */
#define DMA_CH_ERRIF_bp  5  /* Block Transfer Error Interrupt Flag bit position. */
#define DMA_CH_CHPEND_bm  0x40  /* Block Transfer Pending bit mask. */
#define DMA_CH_CHPEND_bp  6  /* Block Transfer Pending bit position. */
#define DMA_CH_CHBUSY_bm  0x80  /* Block Transfer Busy bit mask. */
#define DMA_CH_CHBUSY_bp  7  /* Block Transfer Busy bit position. */

/* DMA_CH.ADDRCTRL  bit masks and bit positions */
#define DMA_CH_DESTDIR_gm  0x03  /* Channel Destination Address Mode group mask. */
#define DMA_CH_DESTDIR_gp  0  /* Channel Destination Address Mode group position. */
#define DMA_CH_DESTDIR0_bm  (1<<0)  /* Channel Destination Address Mode bit 0 mask. */
#define DMA_CH_DESTDIR0_bp  0  /* Channel Destination Address Mode bit 0 position. */
#define DMA_CH_DESTDIR1_bm  (1<<1)  /* Channel Destination Address Mode bit 1 mask. */
#define DMA_CH_DESTDIR1_bp  1  /* Channel Destination Address Mode bit 1 position. */
#define DMA_CH_DESTRELOAD_gm  0x0C  /* Channel Destination Address Reload group mask. */
#define DMA_CH_DESTRELOAD_gp  2  /* Channel Destination Address Reload group position. */
#define DMA_CH_DESTRELOAD0_bm  (1<<2)  /* Channel Destination Address Reload bit 0 mask. */
#define DMA_CH_DESTRELOAD0_bp  2  /* Channel Destination Address Reload bit 0 position. */
#define DMA_CH_DESTRELOAD1_bm  (1<<3)  /* Channel Destination Address Reload bit 1 mask. */
#define DMA_CH_DESTRELOAD1_bp  3  /* Channel Destination Address Reload bit 1 position. */
#define DMA_CH_SRCDIR_gm  0x30  /* Channel Source Address Mode group mask. */
#define DMA_CH_SRCDIR_gp  4  /* Channel Source Address Mode group position. */
#define DMA_CH_SRCDIR0_bm  (1<<4)  /* Channel Source Address Mode bit 0 mask. */
#define DMA_CH_SRCDIR0_bp  4  /* Channel Source Address Mode bit 0 position. */
#define DMA_CH_SRCDIR1_bm  (1<<5)  /* Channel Source Address Mode bit 1 mask. */
#define DMA_CH_SRCDIR1_bp  5  /* Channel Source Address Mode bit 1 position. */
#define DMA_CH_SRCRELOAD_gm  0xC0  /* Channel Source Address Reload group mask. */
#define DMA_CH_SRCRELOAD_gp  6  /* Channel Source Address Reload group position. */
#define DMA_CH_SRCRELOAD0_bm  (1<<6)  /* Channel Source Address Reload bit 0 mask. */
#define DMA_CH_SRCRELOAD0_bp  6  /* Channel Source Address Reload bit 0 position. */
#define DMA_CH_SRCRELOAD1_bm  (1<<7)  /* Channel Source Address Reload bit 1 mask. */
#define DMA_CH_SRCRELOAD1_bp  7  /* Channel Source Address Reload bit 1 position. */

/* DMA_CH.TRIGSRC  bit masks and bit positions */
#define DMA_CH_TRIGSRC_gm  0xFF  /* Channel Trigger Source group mask. */
#define DMA_CH_TRIGSRC_gp  0  /* Channel Trigger Source group position. */
#define DMA_CH_TRIGSRC0_bm  (1<<0)  /* Channel Trigger Source bit 0 mask. */
#define DMA_CH_TRIGSRC0_bp  0  /* Channel Trigger Source bit 0 position. */
#define DMA_CH_TRIGSRC1_bm  (1<<1)  /* Channel Trigger Source bit 1 mask. */
#define DMA_CH_TRIGSRC1_bp  1  /* Channel Trigger Source bit 1 position. */
#define DMA_CH_TRIGSRC2_bm  (1<<2)  /* Channel Trigger Source bit 2 mask. */
#define DMA_CH_TRIGSRC2_bp  2  /* Channel Trigger Source bit 2 position. */
#define DMA_CH_TRIGSRC3_bm  (1<<3)  /* Channel Trigger Source bit 3 mask. */
#define DMA_CH_TRIGSRC3_bp  3  /* Channel Trigger Source bit 3 position. */
#define DMA_CH_TRIGSRC4_bm  (1<<4)  /* Channel Trigger Source bit 4 mask. */
#define DMA_CH_TRIGSRC4_bp  4  /* Channel Trigger Source bit 4 position. */
#define DMA_CH_TRIGSRC5_bm  (1<<5)  /* Channel Trigger Source bit 5 mask. */
#define DMA_CH_TRIGSRC5_bp  5  /* Channel Trigger Source bit 5 position. */
#define DMA_CH_TRIGSRC6_bm  (1<<6)  /* Channel Trigger Source bit 6 mask. */
#define DMA_CH_TRIGSRC6_bp  6  /* Channel Trigger Source bit 6 position. */
#define DMA_CH_TRIGSRC7_bm  (1<<7)  /* Channel Trigger Source bit 7 mask. */
#define DMA_CH_TRIGSRC7_bp  7  /* Channel Trigger Source bit 7 position. */







/* DMA.CTRL  bit masks and bit positions */
#define DMA_PRIMODE_bm  0x01  /* Channel Priority Mode bit mask. */
#define DMA_PRIMODE_bp  0  /* Channel Priority Mode bit position. */
#define DMA_DBUFMODE_bm  0x04  /* Double Buffering Mode bit mask. */
#define DMA_DBUFMODE_bp  2  /* Double Buffering Mode bit position. */
#define DMA_RESET_bm  0x40  /* Software Reset bit mask. */
#define DMA_RESET_bp  6  /* Software Reset bit position. */
#define DMA_ENABLE_bm  0x80  /* Enable bit mask. */
#define DMA_ENABLE_bp  7  /* Enable bit position. */

/* DMA.INTFLAGS  bit masks and bit positions */
#define DMA_CH0TRNIF_bm  0x01  /* Channel 0 Transaction Complete Interrupt Flag bit mask. */
#define DMA_CH0TRNIF_bp  0  /* Channel 0 Transaction Complete Interrupt Flag bit position. */
#define DMA_CH1TRNIF_bm  0x02  /* Channel 1 Transaction Complete Interrupt Flag bit mask. */
#define DMA_CH1TRNIF_bp  1  /* Channel 1 Transaction Complete Interrupt Flag bit position. */
#define DMA_CH0ERRIF_bm  0x10  /* Channel 0 Block Transfer Error Interrupt Flag bit mask. */
#define DMA_CH0ERRIF_bp  4  /* Channel 0 Block Transfer Error Interrupt Flag bit position. */
#define DMA_CH1ERRIF_bm  0x20  /* Channel 1 Block Transfer Error Interrupt Flag bit mask. */
#define DMA_CH1ERRIF_bp  5  /* Channel 1 Block Transfer Error Interrupt Flag bit position. */

/* DMA.STATUS  bit masks and bit positions */
#define DMA_CH0PEND_bm  0x01  /* Channel 0 Block Transfer Pending bit mask. */
#define DMA_CH0PEND_bp  0  /* Channel 0 Block Transfer Pending bit position. */
#define DMA_CH1PEND_bm  0x02  /* Channel 1 Block Transfer Pending bit mask. */
#define DMA_CH1PEND_bp  1  /* Channel 1 Block Transfer Pending bit position. */
#define DMA_CH0BUSY_bm  0x10  /* Channel 0 Block Transfer Busy bit mask. */
#define DMA_CH0BUSY_bp  4  /* Channel 0 Block Transfer Busy bit position. */
#define DMA_CH1BUSY_bm  0x20  /* Channel 1 Block Transfer Busy bit mask. */
#define DMA_CH1BUSY_bp  5  /* Channel 1 Block Transfer Busy bit position. */


/* EVSYS - Event System */
/* EVSYS.CH0MUX  bit masks and bit positions */
#define EVSYS_CHMUX_gm  0xFF  /* Event Channel 0 Multiplexer group mask. */
#define EVSYS_CHMUX_gp  0  /* Event Channel 0 Multiplexer group position. */
#define EVSYS_CHMUX0_bm  (1<<0)  /* Event Channel 0 Multiplexer bit 0 mask. */
#define EVSYS_CHMUX0_bp  0  /* Event Channel 0 Multiplexer bit 0 position. */
#define EVSYS_CHMUX1_bm  (1<<1)  /* Event Channel 0 Multiplexer bit 1 mask. */
#define EVSYS_CHMUX1_bp  1  /* Event Channel 0 Multiplexer bit 1 position. */
#define EVSYS_CHMUX2_bm  (1<<2)  /* Event Channel 0 Multiplexer bit 2 mask. */
#define EVSYS_CHMUX2_bp  2  /* Event Channel 0 Multiplexer bit 2 position. */
#define EVSYS_CHMUX3_bm  (1<<3)  /* Event Channel 0 Multiplexer bit 3 mask. */
#define EVSYS_CHMUX3_bp  3  /* Event Channel 0 Multiplexer bit 3 position. */
#define EVSYS_CHMUX4_bm  (1<<4)  /* Event Channel 0 Multiplexer bit 4 mask. */
#define EVSYS_CHMUX4_bp  4  /* Event Channel 0 Multiplexer bit 4 position. */
#define EVSYS_CHMUX5_bm  (1<<5)  /* Event Channel 0 Multiplexer bit 5 mask. */
#define EVSYS_CHMUX5_bp  5  /* Event Channel 0 Multiplexer bit 5 position. */
#define EVSYS_CHMUX6_bm  (1<<6)  /* Event Channel 0 Multiplexer bit 6 mask. */
#define EVSYS_CHMUX6_bp  6  /* Event Channel 0 Multiplexer bit 6 position. */
#define EVSYS_CHMUX7_bm  (1<<7)  /* Event Channel 0 Multiplexer bit 7 mask. */
#define EVSYS_CHMUX7_bp  7  /* Event Channel 0 Multiplexer bit 7 position. */

/* EVSYS.CH1MUX  bit masks and bit positions */
/* EVSYS_CHMUX  is already defined. */

/* EVSYS.CH2MUX  bit masks and bit positions */
/* EVSYS_CHMUX  is already defined. */

/* EVSYS.CH3MUX  bit masks and bit positions */
/* EVSYS_CHMUX  is already defined. */

/* EVSYS.CH0CTRL  bit masks and bit positions */
#define EVSYS_DIGFILT_gm  0x07  /* Digital Filter group mask. */
#define EVSYS_DIGFILT_gp  0  /* Digital Filter group position. */
#define EVSYS_DIGFILT0_bm  (1<<0)  /* Digital Filter bit 0 mask. */
#define EVSYS_DIGFILT0_bp  0  /* Digital Filter bit 0 position. */
#define EVSYS_DIGFILT1_bm  (1<<1)  /* Digital Filter bit 1 mask. */
#define EVSYS_DIGFILT1_bp  1  /* Digital Filter bit 1 position. */
#define EVSYS_DIGFILT2_bm  (1<<2)  /* Digital Filter bit 2 mask. */
#define EVSYS_DIGFILT2_bp  2  /* Digital Filter bit 2 position. */
#define EVSYS_QDEN_bm  0x08  /* Quadrature Decoder Enable bit mask. */
#define EVSYS_QDEN_bp  3  /* Quadrature Decoder Enable bit position. */
#define EVSYS_QDIEN_bm  0x10  /* Quadrature Decoder Index Enable bit mask. */
#define EVSYS_QDIEN_bp  4  /* Quadrature Decoder Index Enable bit position. */
#define EVSYS_QDIRM_gm  0x60  /* Quadrature Decoder Index Recognition Mode group mask. */
#define EVSYS_QDIRM_gp  5  /* Quadrature Decoder Index Recognition Mode group position. */
#define EVSYS_QDIRM0_bm  (1<<5)  /* Quadrature Decoder Index Recognition Mode bit 0 mask. */
#define EVSYS_QDIRM0_bp  5  /* Quadrature Decoder Index Recognition Mode bit 0 position. */
#define EVSYS_QDIRM1_bm  (1<<6)  /* Quadrature Decoder Index Recognition Mode bit 1 mask. */
#define EVSYS_QDIRM1_bp  6  /* Quadrature Decoder Index Recognition Mode bit 1 position. */

/* EVSYS.CH1CTRL  bit masks and bit positions */
/* EVSYS_DIGFILT  is already defined. */

/* EVSYS.CH2CTRL  bit masks and bit positions */
/* EVSYS_DIGFILT  is already defined. */

/* EVSYS.CH3CTRL  bit masks and bit positions */
/* EVSYS_DIGFILT  is already defined. */



/* FUSE - Fuses and Lockbits */
/* NVM_FUSES.FUSEBYTE0  bit masks and bit positions */
#define NVM_FUSES_JTAGUSERID_gm  0xFF  /* JTAG User ID group mask. */
#define NVM_FUSES_JTAGUSERID_gp  0  /* JTAG User ID group position. */
#define NVM_FUSES_JTAGUSERID0_bm  (1<<0)  /* JTAG User ID bit 0 mask. */
#define NVM_FUSES_JTAGUSERID0_bp  0  /* JTAG User ID bit 0 position. */
#define NVM_FUSES_JTAGUSERID1_bm  (1<<1)  /* JTAG User ID bit 1 mask. */
#define NVM_FUSES_JTAGUSERID1_bp  1  /* JTAG User ID bit 1 position. */
#define NVM_FUSES_JTAGUSERID2_bm  (1<<2)  /* JTAG User ID bit 2 mask. */
#define NVM_FUSES_JTAGUSERID2_bp  2  /* JTAG User ID bit 2 position. */
#define NVM_FUSES_JTAGUSERID3_bm  (1<<3)  /* JTAG User ID bit 3 mask. */
#define NVM_FUSES_JTAGUSERID3_bp  3  /* JTAG User ID bit 3 position. */
#define NVM_FUSES_JTAGUSERID4_bm  (1<<4)  /* JTAG User ID bit 4 mask. */
#define NVM_FUSES_JTAGUSERID4_bp  4  /* JTAG User ID bit 4 position. */
#define NVM_FUSES_JTAGUSERID5_bm  (1<<5)  /* JTAG User ID bit 5 mask. */
#define NVM_FUSES_JTAGUSERID5_bp  5  /* JTAG User ID bit 5 position. */
#define NVM_FUSES_JTAGUSERID6_bm  (1<<6)  /* JTAG User ID bit 6 mask. */
#define NVM_FUSES_JTAGUSERID6_bp  6  /* JTAG User ID bit 6 position. */
#define NVM_FUSES_JTAGUSERID7_bm  (1<<7)  /* JTAG User ID bit 7 mask. */
#define NVM_FUSES_JTAGUSERID7_bp  7  /* JTAG User ID bit 7 position. */

/* NVM_FUSES.FUSEBYTE1  bit masks and bit positions */
#define NVM_FUSES_WDPER_gm  0x0F  /* Watchdog Timeout Period group mask. */
#define NVM_FUSES_WDPER_gp  0  /* Watchdog Timeout Period group position. */
#define NVM_FUSES_WDPER0_bm  (1<<0)  /* Watchdog Timeout Period bit 0 mask. */
#define NVM_FUSES_WDPER0_bp  0  /* Watchdog Timeout Period bit 0 position. */
#define NVM_FUSES_WDPER1_bm  (1<<1)  /* Watchdog Timeout Period bit 1 mask. */
#define NVM_FUSES_WDPER1_bp  1  /* Watchdog Timeout Period bit 1 position. */
#define NVM_FUSES_WDPER2_bm  (1<<2)  /* Watchdog Timeout Period bit 2 mask. */
#define NVM_FUSES_WDPER2_bp  2  /* Watchdog Timeout Period bit 2 position. */
#define NVM_FUSES_WDPER3_bm  (1<<3)  /* Watchdog Timeout Period bit 3 mask. */
#define NVM_FUSES_WDPER3_bp  3  /* Watchdog Timeout Period bit 3 position. */
#define NVM_FUSES_WDWPER_gm  0xF0  /* Watchdog Window Timeout Period group mask. */
#define NVM_FUSES_WDWPER_gp  4  /* Watchdog Window Timeout Period group position. */
#define NVM_FUSES_WDWPER0_bm  (1<<4)  /* Watchdog Window Timeout Period bit 0 mask. */
#define NVM_FUSES_WDWPER0_bp  4  /* Watchdog Window Timeout Period bit 0 position. */
#define NVM_FUSES_WDWPER1_bm  (1<<5)  /* Watchdog Window Timeout Period bit 1 mask. */
#define NVM_FUSES_WDWPER1_bp  5  /* Watchdog Window Timeout Period bit 1 position. */
#define NVM_FUSES_WDWPER2_bm  (1<<6)  /* Watchdog Window Timeout Period bit 2 mask. */
#define NVM_FUSES_WDWPER2_bp  6  /* Watchdog Window Timeout Period bit 2 position. */
#define NVM_FUSES_WDWPER3_bm  (1<<7)  /* Watchdog Window Timeout Period bit 3 mask. */
#define NVM_FUSES_WDWPER3_bp  7  /* Watchdog Window Timeout Period bit 3 position. */

/* NVM_FUSES.FUSEBYTE2  bit masks and bit positions */
#define NVM_FUSES_BODPD_gm  0x03  /* BOD Operation in Power-Down Mode group mask. */
#define NVM_FUSES_BODPD_gp  0  /* BOD Operation in Power-Down Mode group position. */
#define NVM_FUSES_BODPD0_bm  (1<<0)  /* BOD Operation in Power-Down Mode bit 0 mask. */
#define NVM_FUSES_BODPD0_bp  0  /* BOD Operation in Power-Down Mode bit 0 position. */
#define NVM_FUSES_BODPD1_bm  (1<<1)  /* BOD Operation in Power-Down Mode bit 1 mask. */
#define NVM_FUSES_BODPD1_bp  1  /* BOD Operation in Power-Down Mode bit 1 position. */
#define NVM_FUSES_TOSCSEL_bm  0x20  /* Timer Oscillator pin location bit mask. */
#define NVM_FUSES_TOSCSEL_bp  5  /* Timer Oscillator pin location bit position. */
#define NVM_FUSES_BOOTRST_bm  0x40  /* Boot Loader Section Reset Vector bit mask. */
#define NVM_FUSES_BOOTRST_bp  6  /* Boot Loader Section Reset Vector bit position. */

/* NVM_FUSES.FUSEBYTE4  bit masks and bit positions */
#define NVM_FUSES_JTAGEN_bm  0x01  /* JTAG Interface Enable bit mask. */
#define NVM_FUSES_JTAGEN_bp  0  /* JTAG Interface Enable bit position. */
#define NVM_FUSES_WDLOCK_bm  0x02  /* Watchdog Timer Lock bit mask. */
#define NVM_FUSES_WDLOCK_bp  1  /* Watchdog Timer Lock bit position. */
#define NVM_FUSES_STARTUPTIME_gm  0x0C  /* Start-up Time group mask. */
#define NVM_FUSES_STARTUPTIME_gp  2  /* Start-up Time group position. */
#define NVM_FUSES_STARTUPTIME0_bm  (1<<2)  /* Start-up Time bit 0 mask. */
#define NVM_FUSES_STARTUPTIME0_bp  2  /* Start-up Time bit 0 position. */
#define NVM_FUSES_STARTUPTIME1_bm  (1<<3)  /* Start-up Time bit 1 mask. */
#define NVM_FUSES_STARTUPTIME1_bp  3  /* Start-up Time bit 1 position. */
#define NVM_FUSES_RSTDISBL_bm  0x10  /* External Reset Disable bit mask. */
#define NVM_FUSES_RSTDISBL_bp  4  /* External Reset Disable bit position. */

/* NVM_FUSES.FUSEBYTE5  bit masks and bit positions */
#define NVM_FUSES_BODLEVEL_gm  0x07  /* Brownout Detection Voltage Level group mask. */
#define NVM_FUSES_BODLEVEL_gp  0  /* Brownout Detection Voltage Level group position. */
#define NVM_FUSES_BODLEVEL0_bm  (1<<0)  /* Brownout Detection Voltage Level bit 0 mask. */
#define NVM_FUSES_BODLEVEL0_bp  0  /* Brownout Detection Voltage Level bit 0 position. */
#define NVM_FUSES_BODLEVEL1_bm  (1<<1)  /* Brownout Detection Voltage Level bit 1 mask. */
#define NVM_FUSES_BODLEVEL1_bp  1  /* Brownout Detection Voltage Level bit 1 position. */
#define NVM_FUSES_BODLEVEL2_bm  (1<<2)  /* Brownout Detection Voltage Level bit 2 mask. */
#define NVM_FUSES_BODLEVEL2_bp  2  /* Brownout Detection Voltage Level bit 2 position. */
#define NVM_FUSES_EESAVE_bm  0x08  /* Preserve EEPROM Through Chip Erase bit mask. */
#define NVM_FUSES_EESAVE_bp  3  /* Preserve EEPROM Through Chip Erase bit position. */
#define NVM_FUSES_BODACT_gm  0x30  /* BOD Operation in Active Mode group mask. */
#define NVM_FUSES_BODACT_gp  4  /* BOD Operation in Active Mode group position. */
#define NVM_FUSES_BODACT0_bm  (1<<4)  /* BOD Operation in Active Mode bit 0 mask. */
#define NVM_FUSES_BODACT0_bp  4  /* BOD Operation in Active Mode bit 0 position. */
#define NVM_FUSES_BODACT1_bm  (1<<5)  /* BOD Operation in Active Mode bit 1 mask. */
#define NVM_FUSES_BODACT1_bp  5  /* BOD Operation in Active Mode bit 1 position. */





/* HIRES - Timer/Counter High-Resolution Extension */
/* HIRES.CTRLA  bit masks and bit positions */
#define HIRES_HREN_gm  0x03  /* High Resolution Enable group mask. */
#define HIRES_HREN_gp  0  /* High Resolution Enable group position. */
#define HIRES_HREN0_bm  (1<<0)  /* High Resolution Enable bit 0 mask. */
#define HIRES_HREN0_bp  0  /* High Resolution Enable bit 0 position. */
#define HIRES_HREN1_bm  (1<<1)  /* High Resolution Enable bit 1 mask. */
#define HIRES_HREN1_bp  1  /* High Resolution Enable bit 1 position. */
#define HIRES_HRPLUS_bm  0x04  /* High Resolution Plus bit mask. */
#define HIRES_HRPLUS_bp  2  /* High Resolution Plus bit position. */

/* IRCOM - IR Communication Module */
/* IRCOM.CTRL  bit masks and bit positions */
#define IRCOM_EVSEL_gm  0x0F  /* Event Channel Select group mask. */
#define IRCOM_EVSEL_gp  0  /* Event Channel Select group position. */
#define IRCOM_EVSEL0_bm  (1<<0)  /* Event Channel Select bit 0 mask. */
#define IRCOM_EVSEL0_bp  0  /* Event Channel Select bit 0 position. */
#define IRCOM_EVSEL1_bm  (1<<1)  /* Event Channel Select bit 1 mask. */
#define IRCOM_EVSEL1_bp  1  /* Event Channel Select bit 1 position. */
#define IRCOM_EVSEL2_bm  (1<<2)  /* Event Channel Select bit 2 mask. */
#define IRCOM_EVSEL2_bp  2  /* Event Channel Select bit 2 position. */
#define IRCOM_EVSEL3_bm  (1<<3)  /* Event Channel Select bit 3 mask. */
#define IRCOM_EVSEL3_bp  3  /* Event Channel Select bit 3 position. */



/* LCD - LCD Controller */
/* LCD.CTRLA  bit masks and bit positions */
#define LCD_BLANK_bm  0x01  /* Blanking Display Mode bit mask. */
#define LCD_BLANK_bp  0  /* Blanking Display Mode bit position. */
#define LCD_SEGON_bm  0x02  /* Segments On bit mask. */
#define LCD_SEGON_bp  1  /* Segments On bit position. */
#define LCD_CLRDT_bm  0x04  /* Clear Data Register bit mask. */
#define LCD_CLRDT_bp  2  /* Clear Data Register bit position. */
#define LCD_SEGSWP_bm  0x08  /* Segment Bus Swap bit mask. */
#define LCD_SEGSWP_bp  3  /* Segment Bus Swap bit position. */
#define LCD_COMSWP_bm  0x10  /* Common Bus Swap bit mask. */
#define LCD_COMSWP_bp  4  /* Common Bus Swap bit position. */
#define LCD_DATCLK_bm  0x20  /* Data Register Lock bit mask. */
#define LCD_DATCLK_bp  5  /* Data Register Lock bit position. */
#define LCD_XBIAS_bm  0x40  /* External Register Bias Generation bit mask. */
#define LCD_XBIAS_bp  6  /* External Register Bias Generation bit position. */
#define LCD_ENABLE_bm  0x80  /* LCD Enable bit mask. */
#define LCD_ENABLE_bp  7  /* LCD Enable bit position. */

/* LCD.CTRLB  bit masks and bit positions */
#define LCD_DUTY_gm  0x03  /* Duty Select group mask. */
#define LCD_DUTY_gp  0  /* Duty Select group position. */
#define LCD_DUTY0_bm  (1<<0)  /* Duty Select bit 0 mask. */
#define LCD_DUTY0_bp  0  /* Duty Select bit 0 position. */
#define LCD_DUTY1_bm  (1<<1)  /* Duty Select bit 1 mask. */
#define LCD_DUTY1_bp  1  /* Duty Select bit 1 position. */
#define LCD_LPWAV_bm  0x08  /* Low Power Waveform bit mask. */
#define LCD_LPWAV_bp  3  /* Low Power Waveform bit position. */
#define LCD_CLKDIV_gm  0x70  /* LCD Clock Divide group mask. */
#define LCD_CLKDIV_gp  4  /* LCD Clock Divide group position. */
#define LCD_CLKDIV0_bm  (1<<4)  /* LCD Clock Divide bit 0 mask. */
#define LCD_CLKDIV0_bp  4  /* LCD Clock Divide bit 0 position. */
#define LCD_CLKDIV1_bm  (1<<5)  /* LCD Clock Divide bit 1 mask. */
#define LCD_CLKDIV1_bp  5  /* LCD Clock Divide bit 1 position. */
#define LCD_CLKDIV2_bm  (1<<6)  /* LCD Clock Divide bit 2 mask. */
#define LCD_CLKDIV2_bp  6  /* LCD Clock Divide bit 2 position. */
#define LCD_PRESC_bm  0x80  /* LCD Prescaler Select bit mask. */
#define LCD_PRESC_bp  7  /* LCD Prescaler Select bit position. */

/* LCD.CTRLC  bit masks and bit positions */
#define LCD_PMSK_gm  0x3F  /* LCD Port Mask group mask. */
#define LCD_PMSK_gp  0  /* LCD Port Mask group position. */
#define LCD_PMSK0_bm  (1<<0)  /* LCD Port Mask bit 0 mask. */
#define LCD_PMSK0_bp  0  /* LCD Port Mask bit 0 position. */
#define LCD_PMSK1_bm  (1<<1)  /* LCD Port Mask bit 1 mask. */
#define LCD_PMSK1_bp  1  /* LCD Port Mask bit 1 position. */
#define LCD_PMSK2_bm  (1<<2)  /* LCD Port Mask bit 2 mask. */
#define LCD_PMSK2_bp  2  /* LCD Port Mask bit 2 position. */
#define LCD_PMSK3_bm  (1<<3)  /* LCD Port Mask bit 3 mask. */
#define LCD_PMSK3_bp  3  /* LCD Port Mask bit 3 position. */
#define LCD_PMSK4_bm  (1<<4)  /* LCD Port Mask bit 4 mask. */
#define LCD_PMSK4_bp  4  /* LCD Port Mask bit 4 position. */
#define LCD_PMSK5_bm  (1<<5)  /* LCD Port Mask bit 5 mask. */
#define LCD_PMSK5_bp  5  /* LCD Port Mask bit 5 position. */

/* LCD.INTCTRL  bit masks and bit positions */
#define LCD_FCINTLVL_gm  0x03  /* Interrupt Level group mask. */
#define LCD_FCINTLVL_gp  0  /* Interrupt Level group position. */
#define LCD_FCINTLVL0_bm  (1<<0)  /* Interrupt Level bit 0 mask. */
#define LCD_FCINTLVL0_bp  0  /* Interrupt Level bit 0 position. */
#define LCD_FCINTLVL1_bm  (1<<1)  /* Interrupt Level bit 1 mask. */
#define LCD_FCINTLVL1_bp  1  /* Interrupt Level bit 1 position. */
#define LCD_XIME_gm  0xF8  /* eXtended Interrupt Mode Enable group mask. */
#define LCD_XIME_gp  3  /* eXtended Interrupt Mode Enable group position. */
#define LCD_XIME0_bm  (1<<3)  /* eXtended Interrupt Mode Enable bit 0 mask. */
#define LCD_XIME0_bp  3  /* eXtended Interrupt Mode Enable bit 0 position. */
#define LCD_XIME1_bm  (1<<4)  /* eXtended Interrupt Mode Enable bit 1 mask. */
#define LCD_XIME1_bp  4  /* eXtended Interrupt Mode Enable bit 1 position. */
#define LCD_XIME2_bm  (1<<5)  /* eXtended Interrupt Mode Enable bit 2 mask. */
#define LCD_XIME2_bp  5  /* eXtended Interrupt Mode Enable bit 2 position. */
#define LCD_XIME3_bm  (1<<6)  /* eXtended Interrupt Mode Enable bit 3 mask. */
#define LCD_XIME3_bp  6  /* eXtended Interrupt Mode Enable bit 3 position. */
#define LCD_XIME4_bm  (1<<7)  /* eXtended Interrupt Mode Enable bit 4 mask. */
#define LCD_XIME4_bp  7  /* eXtended Interrupt Mode Enable bit 4 position. */

/* LCD.INTFLAG  bit masks and bit positions */
#define LCD_FCIF_bm  0x01  /* LCD Frame Completed Interrupt Flag bit mask. */
#define LCD_FCIF_bp  0  /* LCD Frame Completed Interrupt Flag bit position. */

/* LCD.CTRLD  bit masks and bit positions */
#define LCD_BLINKRATE_gm  0x03  /* LCD Blink Rate group mask. */
#define LCD_BLINKRATE_gp  0  /* LCD Blink Rate group position. */
#define LCD_BLINKRATE0_bm  (1<<0)  /* LCD Blink Rate bit 0 mask. */
#define LCD_BLINKRATE0_bp  0  /* LCD Blink Rate bit 0 position. */
#define LCD_BLINKRATE1_bm  (1<<1)  /* LCD Blink Rate bit 1 mask. */
#define LCD_BLINKRATE1_bp  1  /* LCD Blink Rate bit 1 position. */
#define LCD_BLINKEN_bm  0x08  /* Blink Enable bit mask. */
#define LCD_BLINKEN_bp  3  /* Blink Enable bit position. */

/* LCD.CTRLE  bit masks and bit positions */
#define LCD_BPS0_gm  0x0F  /* Blink Pixel Selection 0 group mask. */
#define LCD_BPS0_gp  0  /* Blink Pixel Selection 0 group position. */
#define LCD_BPS00_bm  (1<<0)  /* Blink Pixel Selection 0 bit 0 mask. */
#define LCD_BPS00_bp  0  /* Blink Pixel Selection 0 bit 0 position. */
#define LCD_BPS01_bm  (1<<1)  /* Blink Pixel Selection 0 bit 1 mask. */
#define LCD_BPS01_bp  1  /* Blink Pixel Selection 0 bit 1 position. */
#define LCD_BPS02_bm  (1<<2)  /* Blink Pixel Selection 0 bit 2 mask. */
#define LCD_BPS02_bp  2  /* Blink Pixel Selection 0 bit 2 position. */
#define LCD_BPS03_bm  (1<<3)  /* Blink Pixel Selection 0 bit 3 mask. */
#define LCD_BPS03_bp  3  /* Blink Pixel Selection 0 bit 3 position. */
#define LCD_BPS1_gm  0xF0  /* Blink Pixel Selection 1 group mask. */
#define LCD_BPS1_gp  4  /* Blink Pixel Selection 1 group position. */
#define LCD_BPS10_bm  (1<<4)  /* Blink Pixel Selection 1 bit 0 mask. */
#define LCD_BPS10_bp  4  /* Blink Pixel Selection 1 bit 0 position. */
#define LCD_BPS11_bm  (1<<5)  /* Blink Pixel Selection 1 bit 1 mask. */
#define LCD_BPS11_bp  5  /* Blink Pixel Selection 1 bit 1 position. */
#define LCD_BPS12_bm  (1<<6)  /* Blink Pixel Selection 1 bit 2 mask. */
#define LCD_BPS12_bp  6  /* Blink Pixel Selection 1 bit 2 position. */
#define LCD_BPS13_bm  (1<<7)  /* Blink Pixel Selection 1 bit 3 mask. */
#define LCD_BPS13_bp  7  /* Blink Pixel Selection 1 bit 3 position. */

/* LCD.CTRLF  bit masks and bit positions */
#define LCD_FCONT_gm  0x3F  /* Fine Contrast group mask. */
#define LCD_FCONT_gp  0  /* Fine Contrast group position. */
#define LCD_FCONT0_bm  (1<<0)  /* Fine Contrast bit 0 mask. */
#define LCD_FCONT0_bp  0  /* Fine Contrast bit 0 position. */
#define LCD_FCONT1_bm  (1<<1)  /* Fine Contrast bit 1 mask. */
#define LCD_FCONT1_bp  1  /* Fine Contrast bit 1 position. */
#define LCD_FCONT2_bm  (1<<2)  /* Fine Contrast bit 2 mask. */
#define LCD_FCONT2_bp  2  /* Fine Contrast bit 2 position. */
#define LCD_FCONT3_bm  (1<<3)  /* Fine Contrast bit 3 mask. */
#define LCD_FCONT3_bp  3  /* Fine Contrast bit 3 position. */
#define LCD_FCONT4_bm  (1<<4)  /* Fine Contrast bit 4 mask. */
#define LCD_FCONT4_bp  4  /* Fine Contrast bit 4 position. */
#define LCD_FCONT5_bm  (1<<5)  /* Fine Contrast bit 5 mask. */
#define LCD_FCONT5_bp  5  /* Fine Contrast bit 5 position. */

/* LCD.CTRLG  bit masks and bit positions */
#define LCD_STSEG_gm  0x3F  /* Start Segment group mask. */
#define LCD_STSEG_gp  0  /* Start Segment group position. */
#define LCD_STSEG0_bm  (1<<0)  /* Start Segment bit 0 mask. */
#define LCD_STSEG0_bp  0  /* Start Segment bit 0 position. */
#define LCD_STSEG1_bm  (1<<1)  /* Start Segment bit 1 mask. */
#define LCD_STSEG1_bp  1  /* Start Segment bit 1 position. */
#define LCD_STSEG2_bm  (1<<2)  /* Start Segment bit 2 mask. */
#define LCD_STSEG2_bp  2  /* Start Segment bit 2 position. */
#define LCD_STSEG3_bm  (1<<3)  /* Start Segment bit 3 mask. */
#define LCD_STSEG3_bp  3  /* Start Segment bit 3 position. */
#define LCD_STSEG4_bm  (1<<4)  /* Start Segment bit 4 mask. */
#define LCD_STSEG4_bp  4  /* Start Segment bit 4 position. */
#define LCD_STSEG5_bm  (1<<5)  /* Start Segment bit 5 mask. */
#define LCD_STSEG5_bp  5  /* Start Segment bit 5 position. */
#define LCD_TDG_gm  0xC0  /* Type of Digit group mask. */
#define LCD_TDG_gp  6  /* Type of Digit group position. */
#define LCD_TDG0_bm  (1<<6)  /* Type of Digit bit 0 mask. */
#define LCD_TDG0_bp  6  /* Type of Digit bit 0 position. */
#define LCD_TDG1_bm  (1<<7)  /* Type of Digit bit 1 mask. */
#define LCD_TDG1_bp  7  /* Type of Digit bit 1 position. */

/* LCD.CTRLH  bit masks and bit positions */
#define LCD_DCODE_gm  0x7F  /* Display Code group mask. */
#define LCD_DCODE_gp  0  /* Display Code group position. */
#define LCD_DCODE0_bm  (1<<0)  /* Display Code bit 0 mask. */
#define LCD_DCODE0_bp  0  /* Display Code bit 0 position. */
#define LCD_DCODE1_bm  (1<<1)  /* Display Code bit 1 mask. */
#define LCD_DCODE1_bp  1  /* Display Code bit 1 position. */
#define LCD_DCODE2_bm  (1<<2)  /* Display Code bit 2 mask. */
#define LCD_DCODE2_bp  2  /* Display Code bit 2 position. */
#define LCD_DCODE3_bm  (1<<3)  /* Display Code bit 3 mask. */
#define LCD_DCODE3_bp  3  /* Display Code bit 3 position. */
#define LCD_DCODE4_bm  (1<<4)  /* Display Code bit 4 mask. */
#define LCD_DCODE4_bp  4  /* Display Code bit 4 position. */
#define LCD_DCODE5_bm  (1<<5)  /* Display Code bit 5 mask. */
#define LCD_DCODE5_bp  5  /* Display Code bit 5 position. */
#define LCD_DCODE6_bm  (1<<6)  /* Display Code bit 6 mask. */
#define LCD_DCODE6_bp  6  /* Display Code bit 6 position. */
#define LCD_DEC_bm  0x80  /* Decrement of Start Segment bit mask. */
#define LCD_DEC_bp  7  /* Decrement of Start Segment bit position. */





















/* LOCKBIT - Fuses and Lockbits */
/* NVM_LOCKBITS.LOCKBITS  bit masks and bit positions */
#define NVM_LOCKBITS_LB_gm  0x03  /* Lock Bits group mask. */
#define NVM_LOCKBITS_LB_gp  0  /* Lock Bits group position. */
#define NVM_LOCKBITS_LB0_bm  (1<<0)  /* Lock Bits bit 0 mask. */
#define NVM_LOCKBITS_LB0_bp  0  /* Lock Bits bit 0 position. */
#define NVM_LOCKBITS_LB1_bm  (1<<1)  /* Lock Bits bit 1 mask. */
#define NVM_LOCKBITS_LB1_bp  1  /* Lock Bits bit 1 position. */
#define NVM_LOCKBITS_BLBAT_gm  0x0C  /* Boot Lock Bits - Application Table group mask. */
#define NVM_LOCKBITS_BLBAT_gp  2  /* Boot Lock Bits - Application Table group position. */
#define NVM_LOCKBITS_BLBAT0_bm  (1<<2)  /* Boot Lock Bits - Application Table bit 0 mask. */
#define NVM_LOCKBITS_BLBAT0_bp  2  /* Boot Lock Bits - Application Table bit 0 position. */
#define NVM_LOCKBITS_BLBAT1_bm  (1<<3)  /* Boot Lock Bits - Application Table bit 1 mask. */
#define NVM_LOCKBITS_BLBAT1_bp  3  /* Boot Lock Bits - Application Table bit 1 position. */
#define NVM_LOCKBITS_BLBA_gm  0x30  /* Boot Lock Bits - Application Section group mask. */
#define NVM_LOCKBITS_BLBA_gp  4  /* Boot Lock Bits - Application Section group position. */
#define NVM_LOCKBITS_BLBA0_bm  (1<<4)  /* Boot Lock Bits - Application Section bit 0 mask. */
#define NVM_LOCKBITS_BLBA0_bp  4  /* Boot Lock Bits - Application Section bit 0 position. */
#define NVM_LOCKBITS_BLBA1_bm  (1<<5)  /* Boot Lock Bits - Application Section bit 1 mask. */
#define NVM_LOCKBITS_BLBA1_bp  5  /* Boot Lock Bits - Application Section bit 1 position. */
#define NVM_LOCKBITS_BLBB_gm  0xC0  /* Boot Lock Bits - Boot Section group mask. */
#define NVM_LOCKBITS_BLBB_gp  6  /* Boot Lock Bits - Boot Section group position. */
#define NVM_LOCKBITS_BLBB0_bm  (1<<6)  /* Boot Lock Bits - Boot Section bit 0 mask. */
#define NVM_LOCKBITS_BLBB0_bp  6  /* Boot Lock Bits - Boot Section bit 0 position. */
#define NVM_LOCKBITS_BLBB1_bm  (1<<7)  /* Boot Lock Bits - Boot Section bit 1 mask. */
#define NVM_LOCKBITS_BLBB1_bp  7  /* Boot Lock Bits - Boot Section bit 1 position. */






/* MCU - MCU Control */
/* MCU.MCUCR  bit masks and bit positions */
#define MCU_JTAGD_bm  0x01  /* JTAG Disable bit mask. */
#define MCU_JTAGD_bp  0  /* JTAG Disable bit position. */

/* MCU.ANAINIT  bit masks and bit positions */
#define MCU_STARTUPDLYA_gm  0x03  /* Analog startup delay Port A group mask. */
#define MCU_STARTUPDLYA_gp  0  /* Analog startup delay Port A group position. */
#define MCU_STARTUPDLYA0_bm  (1<<0)  /* Analog startup delay Port A bit 0 mask. */
#define MCU_STARTUPDLYA0_bp  0  /* Analog startup delay Port A bit 0 position. */
#define MCU_STARTUPDLYA1_bm  (1<<1)  /* Analog startup delay Port A bit 1 mask. */
#define MCU_STARTUPDLYA1_bp  1  /* Analog startup delay Port A bit 1 position. */
#define MCU_STARTUPDLYB_gm  0x0C  /* Analog startup delay Port B group mask. */
#define MCU_STARTUPDLYB_gp  2  /* Analog startup delay Port B group position. */
#define MCU_STARTUPDLYB0_bm  (1<<2)  /* Analog startup delay Port B bit 0 mask. */
#define MCU_STARTUPDLYB0_bp  2  /* Analog startup delay Port B bit 0 position. */
#define MCU_STARTUPDLYB1_bm  (1<<3)  /* Analog startup delay Port B bit 1 mask. */
#define MCU_STARTUPDLYB1_bp  3  /* Analog startup delay Port B bit 1 position. */

/* MCU.EVSYSLOCK  bit masks and bit positions */
#define MCU_EVSYS0LOCK_bm  0x01  /* Event Channel 0-3 Lock bit mask. */
#define MCU_EVSYS0LOCK_bp  0  /* Event Channel 0-3 Lock bit position. */
#define MCU_EVSYS1LOCK_bm  0x10  /* Event Channel 4-7 Lock bit mask. */
#define MCU_EVSYS1LOCK_bp  4  /* Event Channel 4-7 Lock bit position. */

/* MCU.AWEXLOCK  bit masks and bit positions */
#define MCU_AWEXCLOCK_bm  0x01  /* AWeX on T/C C0 Lock bit mask. */
#define MCU_AWEXCLOCK_bp  0  /* AWeX on T/C C0 Lock bit position. */







/* NVM - Non Volatile Memory Controller */
/* NVM.CMD  bit masks and bit positions */
#define NVM_CMD_gm  0x7F  /* Command group mask. */
#define NVM_CMD_gp  0  /* Command group position. */
#define NVM_CMD0_bm  (1<<0)  /* Command bit 0 mask. */
#define NVM_CMD0_bp  0  /* Command bit 0 position. */
#define NVM_CMD1_bm  (1<<1)  /* Command bit 1 mask. */
#define NVM_CMD1_bp  1  /* Command bit 1 position. */
#define NVM_CMD2_bm  (1<<2)  /* Command bit 2 mask. */
#define NVM_CMD2_bp  2  /* Command bit 2 position. */
#define NVM_CMD3_bm  (1<<3)  /* Command bit 3 mask. */
#define NVM_CMD3_bp  3  /* Command bit 3 position. */
#define NVM_CMD4_bm  (1<<4)  /* Command bit 4 mask. */
#define NVM_CMD4_bp  4  /* Command bit 4 position. */
#define NVM_CMD5_bm  (1<<5)  /* Command bit 5 mask. */
#define NVM_CMD5_bp  5  /* Command bit 5 position. */
#define NVM_CMD6_bm  (1<<6)  /* Command bit 6 mask. */
#define NVM_CMD6_bp  6  /* Command bit 6 position. */

/* NVM.CTRLA  bit masks and bit positions */
#define NVM_CMDEX_bm  0x01  /* Command Execute bit mask. */
#define NVM_CMDEX_bp  0  /* Command Execute bit position. */

/* NVM.CTRLB  bit masks and bit positions */
#define NVM_SPMLOCK_bm  0x01  /* SPM Lock bit mask. */
#define NVM_SPMLOCK_bp  0  /* SPM Lock bit position. */
#define NVM_EPRM_bm  0x02  /* EEPROM Power Reduction Enable bit mask. */
#define NVM_EPRM_bp  1  /* EEPROM Power Reduction Enable bit position. */
#define NVM_FPRM_bm  0x04  /* Flash Power Reduction Enable bit mask. */
#define NVM_FPRM_bp  2  /* Flash Power Reduction Enable bit position. */
#define NVM_EEMAPEN_bm  0x08  /* EEPROM Mapping Enable bit mask. */
#define NVM_EEMAPEN_bp  3  /* EEPROM Mapping Enable bit position. */

/* NVM.INTCTRL  bit masks and bit positions */
#define NVM_EELVL_gm  0x03  /* EEPROM Interrupt Level group mask. */
#define NVM_EELVL_gp  0  /* EEPROM Interrupt Level group position. */
#define NVM_EELVL0_bm  (1<<0)  /* EEPROM Interrupt Level bit 0 mask. */
#define NVM_EELVL0_bp  0  /* EEPROM Interrupt Level bit 0 position. */
#define NVM_EELVL1_bm  (1<<1)  /* EEPROM Interrupt Level bit 1 mask. */
#define NVM_EELVL1_bp  1  /* EEPROM Interrupt Level bit 1 position. */
#define NVM_SPMLVL_gm  0x0C  /* SPM Interrupt Level group mask. */
#define NVM_SPMLVL_gp  2  /* SPM Interrupt Level group position. */
#define NVM_SPMLVL0_bm  (1<<2)  /* SPM Interrupt Level bit 0 mask. */
#define NVM_SPMLVL0_bp  2  /* SPM Interrupt Level bit 0 position. */
#define NVM_SPMLVL1_bm  (1<<3)  /* SPM Interrupt Level bit 1 mask. */
#define NVM_SPMLVL1_bp  3  /* SPM Interrupt Level bit 1 position. */

/* NVM.STATUS  bit masks and bit positions */
#define NVM_FLOAD_bm  0x01  /* Flash Page Buffer Active Loading bit mask. */
#define NVM_FLOAD_bp  0  /* Flash Page Buffer Active Loading bit position. */
#define NVM_EELOAD_bm  0x02  /* EEPROM Page Buffer Active Loading bit mask. */
#define NVM_EELOAD_bp  1  /* EEPROM Page Buffer Active Loading bit position. */
#define NVM_FBUSY_bm  0x40  /* Flash Memory Busy bit mask. */
#define NVM_FBUSY_bp  6  /* Flash Memory Busy bit position. */
#define NVM_NVMBUSY_bm  0x80  /* Non-volatile Memory Busy bit mask. */
#define NVM_NVMBUSY_bp  7  /* Non-volatile Memory Busy bit position. */

/* NVM.LOCKBITS  bit masks and bit positions */
#define NVM_LB_gm  0x03  /* Lock Bits group mask. */
#define NVM_LB_gp  0  /* Lock Bits group position. */
#define NVM_LB0_bm  (1<<0)  /* Lock Bits bit 0 mask. */
#define NVM_LB0_bp  0  /* Lock Bits bit 0 position. */
#define NVM_LB1_bm  (1<<1)  /* Lock Bits bit 1 mask. */
#define NVM_LB1_bp  1  /* Lock Bits bit 1 position. */
#define NVM_BLBAT_gm  0x0C  /* Boot Lock Bits - Application Table group mask. */
#define NVM_BLBAT_gp  2  /* Boot Lock Bits - Application Table group position. */
#define NVM_BLBAT0_bm  (1<<2)  /* Boot Lock Bits - Application Table bit 0 mask. */
#define NVM_BLBAT0_bp  2  /* Boot Lock Bits - Application Table bit 0 position. */
#define NVM_BLBAT1_bm  (1<<3)  /* Boot Lock Bits - Application Table bit 1 mask. */
#define NVM_BLBAT1_bp  3  /* Boot Lock Bits - Application Table bit 1 position. */
#define NVM_BLBA_gm  0x30  /* Boot Lock Bits - Application Section group mask. */
#define NVM_BLBA_gp  4  /* Boot Lock Bits - Application Section group position. */
#define NVM_BLBA0_bm  (1<<4)  /* Boot Lock Bits - Application Section bit 0 mask. */
#define NVM_BLBA0_bp  4  /* Boot Lock Bits - Application Section bit 0 position. */
#define NVM_BLBA1_bm  (1<<5)  /* Boot Lock Bits - Application Section bit 1 mask. */
#define NVM_BLBA1_bp  5  /* Boot Lock Bits - Application Section bit 1 position. */
#define NVM_BLBB_gm  0xC0  /* Boot Lock Bits - Boot Section group mask. */
#define NVM_BLBB_gp  6  /* Boot Lock Bits - Boot Section group position. */
#define NVM_BLBB0_bm  (1<<6)  /* Boot Lock Bits - Boot Section bit 0 mask. */
#define NVM_BLBB0_bp  6  /* Boot Lock Bits - Boot Section bit 0 position. */
#define NVM_BLBB1_bm  (1<<7)  /* Boot Lock Bits - Boot Section bit 1 mask. */
#define NVM_BLBB1_bp  7  /* Boot Lock Bits - Boot Section bit 1 position. */

/* OSC - Oscillator */
/* OSC.CTRL  bit masks and bit positions */
#define OSC_RC2MEN_bm  0x01  /* Internal 2 MHz RC Oscillator Enable bit mask. */
#define OSC_RC2MEN_bp  0  /* Internal 2 MHz RC Oscillator Enable bit position. */
#define OSC_RC32MEN_bm  0x02  /* Internal 32 MHz RC Oscillator Enable bit mask. */
#define OSC_RC32MEN_bp  1  /* Internal 32 MHz RC Oscillator Enable bit position. */
#define OSC_RC32KEN_bm  0x04  /* Internal 32.768 kHz RC Oscillator Enable bit mask. */
#define OSC_RC32KEN_bp  2  /* Internal 32.768 kHz RC Oscillator Enable bit position. */
#define OSC_XOSCEN_bm  0x08  /* External Oscillator Enable bit mask. */
#define OSC_XOSCEN_bp  3  /* External Oscillator Enable bit position. */
#define OSC_PLLEN_bm  0x10  /* PLL Enable bit mask. */
#define OSC_PLLEN_bp  4  /* PLL Enable bit position. */

/* OSC.STATUS  bit masks and bit positions */
#define OSC_RC2MRDY_bm  0x01  /* Internal 2 MHz RC Oscillator Ready bit mask. */
#define OSC_RC2MRDY_bp  0  /* Internal 2 MHz RC Oscillator Ready bit position. */
#define OSC_RC32MRDY_bm  0x02  /* Internal 32 MHz RC Oscillator Ready bit mask. */
#define OSC_RC32MRDY_bp  1  /* Internal 32 MHz RC Oscillator Ready bit position. */
#define OSC_RC32KRDY_bm  0x04  /* Internal 32.768 kHz RC Oscillator Ready bit mask. */
#define OSC_RC32KRDY_bp  2  /* Internal 32.768 kHz RC Oscillator Ready bit position. */
#define OSC_XOSCRDY_bm  0x08  /* External Oscillator Ready bit mask. */
#define OSC_XOSCRDY_bp  3  /* External Oscillator Ready bit position. */
#define OSC_PLLRDY_bm  0x10  /* PLL Ready bit mask. */
#define OSC_PLLRDY_bp  4  /* PLL Ready bit position. */

/* OSC.XOSCCTRL  bit masks and bit positions */
#define OSC_XOSCPWR_bm  0x10  /* 16 MHz Crystal Oscillator High Power mode bit mask. */
#define OSC_XOSCPWR_bp  4  /* 16 MHz Crystal Oscillator High Power mode bit position. */
#define OSC_XOSCSEL_gm  0x1F  /* External Oscillator Selection and Startup Time group mask. */
#define OSC_XOSCSEL_gp  0  /* External Oscillator Selection and Startup Time group position. */
#define OSC_XOSCSEL0_bm  (1<<0)  /* External Oscillator Selection and Startup Time bit 0 mask. */
#define OSC_XOSCSEL0_bp  0  /* External Oscillator Selection and Startup Time bit 0 position. */
#define OSC_XOSCSEL1_bm  (1<<1)  /* External Oscillator Selection and Startup Time bit 1 mask. */
#define OSC_XOSCSEL1_bp  1  /* External Oscillator Selection and Startup Time bit 1 position. */
#define OSC_XOSCSEL2_bm  (1<<2)  /* External Oscillator Selection and Startup Time bit 2 mask. */
#define OSC_XOSCSEL2_bp  2  /* External Oscillator Selection and Startup Time bit 2 position. */
#define OSC_XOSCSEL3_bm  (1<<3)  /* External Oscillator Selection and Startup Time bit 3 mask. */
#define OSC_XOSCSEL3_bp  3  /* External Oscillator Selection and Startup Time bit 3 position. */
#define OSC_XOSCSEL4_bm  (1<<4)  /* External Oscillator Selection and Startup Time bit 4 mask. */
#define OSC_XOSCSEL4_bp  4  /* External Oscillator Selection and Startup Time bit 4 position. */
#define OSC_X32KLPM_bm  0x20  /* 32.768 kHz XTAL OSC Low-power Mode bit mask. */
#define OSC_X32KLPM_bp  5  /* 32.768 kHz XTAL OSC Low-power Mode bit position. */
#define OSC_FRQRANGE_gm  0xC0  /* Frequency Range group mask. */
#define OSC_FRQRANGE_gp  6  /* Frequency Range group position. */
#define OSC_FRQRANGE0_bm  (1<<6)  /* Frequency Range bit 0 mask. */
#define OSC_FRQRANGE0_bp  6  /* Frequency Range bit 0 position. */
#define OSC_FRQRANGE1_bm  (1<<7)  /* Frequency Range bit 1 mask. */
#define OSC_FRQRANGE1_bp  7  /* Frequency Range bit 1 position. */

/* OSC.XOSCFAIL  bit masks and bit positions */
#define OSC_XOSCFDEN_bm  0x01  /* XOSC Failure Detection Enable bit mask. */
#define OSC_XOSCFDEN_bp  0  /* XOSC Failure Detection Enable bit position. */
#define OSC_XOSCFDIF_bm  0x02  /* XOSC Failure Detection Interrupt Flag bit mask. */
#define OSC_XOSCFDIF_bp  1  /* XOSC Failure Detection Interrupt Flag bit position. */
#define OSC_PLLFDEN_bm  0x04  /* PLL Failure Detection Enable bit mask. */
#define OSC_PLLFDEN_bp  2  /* PLL Failure Detection Enable bit position. */
#define OSC_PLLFDIF_bm  0x08  /* PLL Failure Detection Interrupt Flag bit mask. */
#define OSC_PLLFDIF_bp  3  /* PLL Failure Detection Interrupt Flag bit position. */


/* OSC.PLLCTRL  bit masks and bit positions */
#define OSC_PLLFAC_gm  0x1F  /* Multiplication Factor group mask. */
#define OSC_PLLFAC_gp  0  /* Multiplication Factor group position. */
#define OSC_PLLFAC0_bm  (1<<0)  /* Multiplication Factor bit 0 mask. */
#define OSC_PLLFAC0_bp  0  /* Multiplication Factor bit 0 position. */
#define OSC_PLLFAC1_bm  (1<<1)  /* Multiplication Factor bit 1 mask. */
#define OSC_PLLFAC1_bp  1  /* Multiplication Factor bit 1 position. */
#define OSC_PLLFAC2_bm  (1<<2)  /* Multiplication Factor bit 2 mask. */
#define OSC_PLLFAC2_bp  2  /* Multiplication Factor bit 2 position. */
#define OSC_PLLFAC3_bm  (1<<3)  /* Multiplication Factor bit 3 mask. */
#define OSC_PLLFAC3_bp  3  /* Multiplication Factor bit 3 position. */
#define OSC_PLLFAC4_bm  (1<<4)  /* Multiplication Factor bit 4 mask. */
#define OSC_PLLFAC4_bp  4  /* Multiplication Factor bit 4 position. */
#define OSC_PLLDIV_bm  0x20  /* Divide by 2 bit mask. */
#define OSC_PLLDIV_bp  5  /* Divide by 2 bit position. */
#define OSC_PLLSRC_gm  0xC0  /* Clock Source group mask. */
#define OSC_PLLSRC_gp  6  /* Clock Source group position. */
#define OSC_PLLSRC0_bm  (1<<6)  /* Clock Source bit 0 mask. */
#define OSC_PLLSRC0_bp  6  /* Clock Source bit 0 position. */
#define OSC_PLLSRC1_bm  (1<<7)  /* Clock Source bit 1 mask. */
#define OSC_PLLSRC1_bp  7  /* Clock Source bit 1 position. */

/* OSC.DFLLCTRL  bit masks and bit positions */
#define OSC_RC2MCREF_bm  0x01  /* 2 MHz DFLL Calibration Reference bit mask. */
#define OSC_RC2MCREF_bp  0  /* 2 MHz DFLL Calibration Reference bit position. */
#define OSC_RC32MCREF_gm  0x06  /* 32 MHz DFLL Calibration Reference group mask. */
#define OSC_RC32MCREF_gp  1  /* 32 MHz DFLL Calibration Reference group position. */
#define OSC_RC32MCREF0_bm  (1<<1)  /* 32 MHz DFLL Calibration Reference bit 0 mask. */
#define OSC_RC32MCREF0_bp  1  /* 32 MHz DFLL Calibration Reference bit 0 position. */
#define OSC_RC32MCREF1_bm  (1<<2)  /* 32 MHz DFLL Calibration Reference bit 1 mask. */
#define OSC_RC32MCREF1_bp  2  /* 32 MHz DFLL Calibration Reference bit 1 position. */

/* PMIC - Programmable Multi-level Interrupt Controller */
/* PMIC.STATUS  bit masks and bit positions */
#define PMIC_LOLVLEX_bm  0x01  /* Low Level Interrupt Executing bit mask. */
#define PMIC_LOLVLEX_bp  0  /* Low Level Interrupt Executing bit position. */
#define PMIC_MEDLVLEX_bm  0x02  /* Medium Level Interrupt Executing bit mask. */
#define PMIC_MEDLVLEX_bp  1  /* Medium Level Interrupt Executing bit position. */
#define PMIC_HILVLEX_bm  0x04  /* High Level Interrupt Executing bit mask. */
#define PMIC_HILVLEX_bp  2  /* High Level Interrupt Executing bit position. */
#define PMIC_NMIEX_bm  0x80  /* Non-maskable Interrupt Executing bit mask. */
#define PMIC_NMIEX_bp  7  /* Non-maskable Interrupt Executing bit position. */

/* PMIC.INTPRI  bit masks and bit positions */
#define PMIC_INTPRI_gm  0xFF  /* Interrupt Priority group mask. */
#define PMIC_INTPRI_gp  0  /* Interrupt Priority group position. */
#define PMIC_INTPRI0_bm  (1<<0)  /* Interrupt Priority bit 0 mask. */
#define PMIC_INTPRI0_bp  0  /* Interrupt Priority bit 0 position. */
#define PMIC_INTPRI1_bm  (1<<1)  /* Interrupt Priority bit 1 mask. */
#define PMIC_INTPRI1_bp  1  /* Interrupt Priority bit 1 position. */
#define PMIC_INTPRI2_bm  (1<<2)  /* Interrupt Priority bit 2 mask. */
#define PMIC_INTPRI2_bp  2  /* Interrupt Priority bit 2 position. */
#define PMIC_INTPRI3_bm  (1<<3)  /* Interrupt Priority bit 3 mask. */
#define PMIC_INTPRI3_bp  3  /* Interrupt Priority bit 3 position. */
#define PMIC_INTPRI4_bm  (1<<4)  /* Interrupt Priority bit 4 mask. */
#define PMIC_INTPRI4_bp  4  /* Interrupt Priority bit 4 position. */
#define PMIC_INTPRI5_bm  (1<<5)  /* Interrupt Priority bit 5 mask. */
#define PMIC_INTPRI5_bp  5  /* Interrupt Priority bit 5 position. */
#define PMIC_INTPRI6_bm  (1<<6)  /* Interrupt Priority bit 6 mask. */
#define PMIC_INTPRI6_bp  6  /* Interrupt Priority bit 6 position. */
#define PMIC_INTPRI7_bm  (1<<7)  /* Interrupt Priority bit 7 mask. */
#define PMIC_INTPRI7_bp  7  /* Interrupt Priority bit 7 position. */

/* PMIC.CTRL  bit masks and bit positions */
#define PMIC_LOLVLEN_bm  0x01  /* Low Level Enable bit mask. */
#define PMIC_LOLVLEN_bp  0  /* Low Level Enable bit position. */
#define PMIC_MEDLVLEN_bm  0x02  /* Medium Level Enable bit mask. */
#define PMIC_MEDLVLEN_bp  1  /* Medium Level Enable bit position. */
#define PMIC_HILVLEN_bm  0x04  /* High Level Enable bit mask. */
#define PMIC_HILVLEN_bp  2  /* High Level Enable bit position. */
#define PMIC_IVSEL_bm  0x40  /* Interrupt Vector Select bit mask. */
#define PMIC_IVSEL_bp  6  /* Interrupt Vector Select bit position. */
#define PMIC_RREN_bm  0x80  /* Round-Robin Priority Enable bit mask. */
#define PMIC_RREN_bp  7  /* Round-Robin Priority Enable bit position. */










/* PORT - I/O Port Configuration */
/* PORT.INTCTRL  bit masks and bit positions */
#define PORT_INT0LVL_gm  0x03  /* Port Interrupt 0 Level group mask. */
#define PORT_INT0LVL_gp  0  /* Port Interrupt 0 Level group position. */
#define PORT_INT0LVL0_bm  (1<<0)  /* Port Interrupt 0 Level bit 0 mask. */
#define PORT_INT0LVL0_bp  0  /* Port Interrupt 0 Level bit 0 position. */
#define PORT_INT0LVL1_bm  (1<<1)  /* Port Interrupt 0 Level bit 1 mask. */
#define PORT_INT0LVL1_bp  1  /* Port Interrupt 0 Level bit 1 position. */
#define PORT_INT1LVL_gm  0x0C  /* Port Interrupt 1 Level group mask. */
#define PORT_INT1LVL_gp  2  /* Port Interrupt 1 Level group position. */
#define PORT_INT1LVL0_bm  (1<<2)  /* Port Interrupt 1 Level bit 0 mask. */
#define PORT_INT1LVL0_bp  2  /* Port Interrupt 1 Level bit 0 position. */
#define PORT_INT1LVL1_bm  (1<<3)  /* Port Interrupt 1 Level bit 1 mask. */
#define PORT_INT1LVL1_bp  3  /* Port Interrupt 1 Level bit 1 position. */



/* PORT.INTFLAGS  bit masks and bit positions */
#define PORT_INT0IF_bm  0x01  /* Port Interrupt 0 Flag bit mask. */
#define PORT_INT0IF_bp  0  /* Port Interrupt 0 Flag bit position. */
#define PORT_INT1IF_bm  0x02  /* Port Interrupt 1 Flag bit mask. */
#define PORT_INT1IF_bp  1  /* Port Interrupt 1 Flag bit position. */

/* PORT.REMAP  bit masks and bit positions */
#define PORT_TC0A_bm  0x01  /* Timer/Counter 0 Output Compare A bit mask. */
#define PORT_TC0A_bp  0  /* Timer/Counter 0 Output Compare A bit position. */
#define PORT_TC0B_bm  0x02  /* Timer/Counter 0 Output Compare B bit mask. */
#define PORT_TC0B_bp  1  /* Timer/Counter 0 Output Compare B bit position. */
#define PORT_TC0C_bm  0x04  /* Timer/Counter 0 Output Compare C bit mask. */
#define PORT_TC0C_bp  2  /* Timer/Counter 0 Output Compare C bit position. */
#define PORT_TC0D_bm  0x08  /* Timer/Counter 0 Output Compare D bit mask. */
#define PORT_TC0D_bp  3  /* Timer/Counter 0 Output Compare D bit position. */
#define PORT_USART0_bm  0x10  /* USART0 bit mask. */
#define PORT_USART0_bp  4  /* USART0 bit position. */
#define PORT_SPI_bm  0x20  /* SPI bit mask. */
#define PORT_SPI_bp  5  /* SPI bit position. */

/* PORT.PIN0CTRL  bit masks and bit positions */
#define PORT_ISC_gm  0x07  /* Input/Sense Configuration group mask. */
#define PORT_ISC_gp  0  /* Input/Sense Configuration group position. */
#define PORT_ISC0_bm  (1<<0)  /* Input/Sense Configuration bit 0 mask. */
#define PORT_ISC0_bp  0  /* Input/Sense Configuration bit 0 position. */
#define PORT_ISC1_bm  (1<<1)  /* Input/Sense Configuration bit 1 mask. */
#define PORT_ISC1_bp  1  /* Input/Sense Configuration bit 1 position. */
#define PORT_ISC2_bm  (1<<2)  /* Input/Sense Configuration bit 2 mask. */
#define PORT_ISC2_bp  2  /* Input/Sense Configuration bit 2 position. */
#define PORT_OPC_gm  0x38  /* Output/Pull Configuration group mask. */
#define PORT_OPC_gp  3  /* Output/Pull Configuration group position. */
#define PORT_OPC0_bm  (1<<3)  /* Output/Pull Configuration bit 0 mask. */
#define PORT_OPC0_bp  3  /* Output/Pull Configuration bit 0 position. */
#define PORT_OPC1_bm  (1<<4)  /* Output/Pull Configuration bit 1 mask. */
#define PORT_OPC1_bp  4  /* Output/Pull Configuration bit 1 position. */
#define PORT_OPC2_bm  (1<<5)  /* Output/Pull Configuration bit 2 mask. */
#define PORT_OPC2_bp  5  /* Output/Pull Configuration bit 2 position. */
#define PORT_INVEN_bm  0x40  /* Inverted I/O Enable bit mask. */
#define PORT_INVEN_bp  6  /* Inverted I/O Enable bit position. */
#define PORT_SRLEN_bm  0x80  /* Slew Rate Enable bit mask. */
#define PORT_SRLEN_bp  7  /* Slew Rate Enable bit position. */

/* PORT.PIN1CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_OPC  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT_SRLEN  is already defined. */

/* PORT.PIN2CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_OPC  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT_SRLEN  is already defined. */

/* PORT.PIN3CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_OPC  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT_SRLEN  is already defined. */

/* PORT.PIN4CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_OPC  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT_SRLEN  is already defined. */

/* PORT.PIN5CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_OPC  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT_SRLEN  is already defined. */

/* PORT.PIN6CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_OPC  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT_SRLEN  is already defined. */

/* PORT.PIN7CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_OPC  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT_SRLEN  is already defined. */


/* PORTCFG - Port Configuration */
/* PORTCFG.VPCTRLA  bit masks and bit positions */
#define PORTCFG_VP0MAP_gm  0x0F  /* Virtual Port 0 Mapping group mask. */
#define PORTCFG_VP0MAP_gp  0  /* Virtual Port 0 Mapping group position. */
#define PORTCFG_VP0MAP0_bm  (1<<0)  /* Virtual Port 0 Mapping bit 0 mask. */
#define PORTCFG_VP0MAP0_bp  0  /* Virtual Port 0 Mapping bit 0 position. */
#define PORTCFG_VP0MAP1_bm  (1<<1)  /* Virtual Port 0 Mapping bit 1 mask. */
#define PORTCFG_VP0MAP1_bp  1  /* Virtual Port 0 Mapping bit 1 position. */
#define PORTCFG_VP0MAP2_bm  (1<<2)  /* Virtual Port 0 Mapping bit 2 mask. */
#define PORTCFG_VP0MAP2_bp  2  /* Virtual Port 0 Mapping bit 2 position. */
#define PORTCFG_VP0MAP3_bm  (1<<3)  /* Virtual Port 0 Mapping bit 3 mask. */
#define PORTCFG_VP0MAP3_bp  3  /* Virtual Port 0 Mapping bit 3 position. */
#define PORTCFG_VP1MAP_gm  0xF0  /* Virtual Port 1 Mapping group mask. */
#define PORTCFG_VP1MAP_gp  4  /* Virtual Port 1 Mapping group position. */
#define PORTCFG_VP1MAP0_bm  (1<<4)  /* Virtual Port 1 Mapping bit 0 mask. */
#define PORTCFG_VP1MAP0_bp  4  /* Virtual Port 1 Mapping bit 0 position. */
#define PORTCFG_VP1MAP1_bm  (1<<5)  /* Virtual Port 1 Mapping bit 1 mask. */
#define PORTCFG_VP1MAP1_bp  5  /* Virtual Port 1 Mapping bit 1 position. */
#define PORTCFG_VP1MAP2_bm  (1<<6)  /* Virtual Port 1 Mapping bit 2 mask. */
#define PORTCFG_VP1MAP2_bp  6  /* Virtual Port 1 Mapping bit 2 position. */
#define PORTCFG_VP1MAP3_bm  (1<<7)  /* Virtual Port 1 Mapping bit 3 mask. */
#define PORTCFG_VP1MAP3_bp  7  /* Virtual Port 1 Mapping bit 3 position. */

/* PORTCFG.VPCTRLB  bit masks and bit positions */
#define PORTCFG_VP2MAP_gm  0x0F  /* Virtual Port 2 Mapping group mask. */
#define PORTCFG_VP2MAP_gp  0  /* Virtual Port 2 Mapping group position. */
#define PORTCFG_VP2MAP0_bm  (1<<0)  /* Virtual Port 2 Mapping bit 0 mask. */
#define PORTCFG_VP2MAP0_bp  0  /* Virtual Port 2 Mapping bit 0 position. */
#define PORTCFG_VP2MAP1_bm  (1<<1)  /* Virtual Port 2 Mapping bit 1 mask. */
#define PORTCFG_VP2MAP1_bp  1  /* Virtual Port 2 Mapping bit 1 position. */
#define PORTCFG_VP2MAP2_bm  (1<<2)  /* Virtual Port 2 Mapping bit 2 mask. */
#define PORTCFG_VP2MAP2_bp  2  /* Virtual Port 2 Mapping bit 2 position. */
#define PORTCFG_VP2MAP3_bm  (1<<3)  /* Virtual Port 2 Mapping bit 3 mask. */
#define PORTCFG_VP2MAP3_bp  3  /* Virtual Port 2 Mapping bit 3 position. */
#define PORTCFG_VP3MAP_gm  0xF0  /* Virtual Port 3 Mapping group mask. */
#define PORTCFG_VP3MAP_gp  4  /* Virtual Port 3 Mapping group position. */
#define PORTCFG_VP3MAP0_bm  (1<<4)  /* Virtual Port 3 Mapping bit 0 mask. */
#define PORTCFG_VP3MAP0_bp  4  /* Virtual Port 3 Mapping bit 0 position. */
#define PORTCFG_VP3MAP1_bm  (1<<5)  /* Virtual Port 3 Mapping bit 1 mask. */
#define PORTCFG_VP3MAP1_bp  5  /* Virtual Port 3 Mapping bit 1 position. */
#define PORTCFG_VP3MAP2_bm  (1<<6)  /* Virtual Port 3 Mapping bit 2 mask. */
#define PORTCFG_VP3MAP2_bp  6  /* Virtual Port 3 Mapping bit 2 position. */
#define PORTCFG_VP3MAP3_bm  (1<<7)  /* Virtual Port 3 Mapping bit 3 mask. */
#define PORTCFG_VP3MAP3_bp  7  /* Virtual Port 3 Mapping bit 3 position. */

/* PORTCFG.CLKEVOUT  bit masks and bit positions */
#define PORTCFG_CLKOUT_gm  0x03  /* Peripheral Clock Output Port group mask. */
#define PORTCFG_CLKOUT_gp  0  /* Peripheral Clock Output Port group position. */
#define PORTCFG_CLKOUT0_bm  (1<<0)  /* Peripheral Clock Output Port bit 0 mask. */
#define PORTCFG_CLKOUT0_bp  0  /* Peripheral Clock Output Port bit 0 position. */
#define PORTCFG_CLKOUT1_bm  (1<<1)  /* Peripheral Clock Output Port bit 1 mask. */
#define PORTCFG_CLKOUT1_bp  1  /* Peripheral Clock Output Port bit 1 position. */
#define PORTCFG_CLKOUTSEL_gm  0x0C  /* Peripheral Clock Output Select group mask. */
#define PORTCFG_CLKOUTSEL_gp  2  /* Peripheral Clock Output Select group position. */
#define PORTCFG_CLKOUTSEL0_bm  (1<<2)  /* Peripheral Clock Output Select bit 0 mask. */
#define PORTCFG_CLKOUTSEL0_bp  2  /* Peripheral Clock Output Select bit 0 position. */
#define PORTCFG_CLKOUTSEL1_bm  (1<<3)  /* Peripheral Clock Output Select bit 1 mask. */
#define PORTCFG_CLKOUTSEL1_bp  3  /* Peripheral Clock Output Select bit 1 position. */
#define PORTCFG_EVOUT_gm  0x30  /* Event Output Port group mask. */
#define PORTCFG_EVOUT_gp  4  /* Event Output Port group position. */
#define PORTCFG_EVOUT0_bm  (1<<4)  /* Event Output Port bit 0 mask. */
#define PORTCFG_EVOUT0_bp  4  /* Event Output Port bit 0 position. */
#define PORTCFG_EVOUT1_bm  (1<<5)  /* Event Output Port bit 1 mask. */
#define PORTCFG_EVOUT1_bp  5  /* Event Output Port bit 1 position. */
#define PORTCFG_RTCOUT_bm  0x40  /* RTC Clock Output bit mask. */
#define PORTCFG_RTCOUT_bp  6  /* RTC Clock Output bit position. */
#define PORTCFG_CLKEVPIN_bm  0x80  /* Peripheral Clock and Event Output pin Select bit mask. */
#define PORTCFG_CLKEVPIN_bp  7  /* Peripheral Clock and Event Output pin Select bit position. */

/* PORTCFG.EVOUTSEL  bit masks and bit positions */
#define PORTCFG_EVOUTSEL_bm  0x04  /* Event Output Select bit mask. */
#define PORTCFG_EVOUTSEL_bp  2  /* Event Output Select bit position. */

/* PR - Power Reduction */
/* PR.PRGEN  bit masks and bit positions */
#define PR_DMA_bm  0x01  /* DMA-Controller bit mask. */
#define PR_DMA_bp  0  /* DMA-Controller bit position. */
#define PR_EVSYS_bm  0x02  /* Event System bit mask. */
#define PR_EVSYS_bp  1  /* Event System bit position. */
#define PR_RTC_bm  0x04  /* Real-time Counter bit mask. */
#define PR_RTC_bp  2  /* Real-time Counter bit position. */
#define PR_AES_bm  0x10  /* AES bit mask. */
#define PR_AES_bp  4  /* AES bit position. */
#define PR_USB_bm  0x40  /* USB bit mask. */
#define PR_USB_bp  6  /* USB bit position. */
#define PR_LCD_bm  0x80  /* LCD Module bit mask. */
#define PR_LCD_bp  7  /* LCD Module bit position. */

/* PR.PRPA  bit masks and bit positions */
#define PR_AC_bm  0x01  /* Port A Analog Comparator bit mask. */
#define PR_AC_bp  0  /* Port A Analog Comparator bit position. */
#define PR_ADC_bm  0x02  /* Port A ADC bit mask. */
#define PR_ADC_bp  1  /* Port A ADC bit position. */

/* PR.PRPB  bit masks and bit positions */
/* PR_AC  is already defined. */
/* PR_ADC  is already defined. */

/* PR.PRPC  bit masks and bit positions */
#define PR_TC0_bm  0x01  /* Port C Timer/Counter0 bit mask. */
#define PR_TC0_bp  0  /* Port C Timer/Counter0 bit position. */
#define PR_TC1_bm  0x02  /* Port C Timer/Counter1 bit mask. */
#define PR_TC1_bp  1  /* Port C Timer/Counter1 bit position. */
#define PR_HIRES_bm  0x04  /* Port C AWEX bit mask. */
#define PR_HIRES_bp  2  /* Port C AWEX bit position. */
#define PR_SPI_bm  0x08  /* Port C SPI bit mask. */
#define PR_SPI_bp  3  /* Port C SPI bit position. */
#define PR_USART0_bm  0x10  /* Port C USART0 bit mask. */
#define PR_USART0_bp  4  /* Port C USART0 bit position. */
#define PR_TWI_bm  0x40  /* Port C Two-wire Interface bit mask. */
#define PR_TWI_bp  6  /* Port C Two-wire Interface bit position. */

/* PR.PRPE  bit masks and bit positions */
/* PR_TC0  is already defined. */
/* PR_USART0  is already defined. */

/* RST - Reset */
/* RST.STATUS  bit masks and bit positions */
#define RST_PORF_bm  0x01  /* Power-on Reset Flag bit mask. */
#define RST_PORF_bp  0  /* Power-on Reset Flag bit position. */
#define RST_EXTRF_bm  0x02  /* External Reset Flag bit mask. */
#define RST_EXTRF_bp  1  /* External Reset Flag bit position. */
#define RST_BORF_bm  0x04  /* Brown-out Reset Flag bit mask. */
#define RST_BORF_bp  2  /* Brown-out Reset Flag bit position. */
#define RST_WDRF_bm  0x08  /* Watchdog Reset Flag bit mask. */
#define RST_WDRF_bp  3  /* Watchdog Reset Flag bit position. */
#define RST_PDIRF_bm  0x10  /* Programming and Debug Interface Interface Reset Flag bit mask. */
#define RST_PDIRF_bp  4  /* Programming and Debug Interface Interface Reset Flag bit position. */
#define RST_SRF_bm  0x20  /* Software Reset Flag bit mask. */
#define RST_SRF_bp  5  /* Software Reset Flag bit position. */
#define RST_SDRF_bm  0x40  /* Spike Detection Reset Flag bit mask. */
#define RST_SDRF_bp  6  /* Spike Detection Reset Flag bit position. */

/* RST.CTRL  bit masks and bit positions */
#define RST_SWRST_bm  0x01  /* Software Reset bit mask. */
#define RST_SWRST_bp  0  /* Software Reset bit position. */

/* RTC - Real-Time Counter */
/* RTC.CTRL  bit masks and bit positions */
#define RTC_PRESCALER_gm  0x07  /* Prescaling Factor group mask. */
#define RTC_PRESCALER_gp  0  /* Prescaling Factor group position. */
#define RTC_PRESCALER0_bm  (1<<0)  /* Prescaling Factor bit 0 mask. */
#define RTC_PRESCALER0_bp  0  /* Prescaling Factor bit 0 position. */
#define RTC_PRESCALER1_bm  (1<<1)  /* Prescaling Factor bit 1 mask. */
#define RTC_PRESCALER1_bp  1  /* Prescaling Factor bit 1 position. */
#define RTC_PRESCALER2_bm  (1<<2)  /* Prescaling Factor bit 2 mask. */
#define RTC_PRESCALER2_bp  2  /* Prescaling Factor bit 2 position. */

/* RTC.STATUS  bit masks and bit positions */
#define RTC_SYNCBUSY_bm  0x01  /* Synchronization Busy Flag bit mask. */
#define RTC_SYNCBUSY_bp  0  /* Synchronization Busy Flag bit position. */

/* RTC.INTCTRL  bit masks and bit positions */
#define RTC_OVFINTLVL_gm  0x03  /* Overflow Interrupt Level group mask. */
#define RTC_OVFINTLVL_gp  0  /* Overflow Interrupt Level group position. */
#define RTC_OVFINTLVL0_bm  (1<<0)  /* Overflow Interrupt Level bit 0 mask. */
#define RTC_OVFINTLVL0_bp  0  /* Overflow Interrupt Level bit 0 position. */
#define RTC_OVFINTLVL1_bm  (1<<1)  /* Overflow Interrupt Level bit 1 mask. */
#define RTC_OVFINTLVL1_bp  1  /* Overflow Interrupt Level bit 1 position. */
#define RTC_COMPINTLVL_gm  0x0C  /* Compare Match Interrupt Level group mask. */
#define RTC_COMPINTLVL_gp  2  /* Compare Match Interrupt Level group position. */
#define RTC_COMPINTLVL0_bm  (1<<2)  /* Compare Match Interrupt Level bit 0 mask. */
#define RTC_COMPINTLVL0_bp  2  /* Compare Match Interrupt Level bit 0 position. */
#define RTC_COMPINTLVL1_bm  (1<<3)  /* Compare Match Interrupt Level bit 1 mask. */
#define RTC_COMPINTLVL1_bp  3  /* Compare Match Interrupt Level bit 1 position. */

/* RTC.INTFLAGS  bit masks and bit positions */
#define RTC_OVFIF_bm  0x01  /* Overflow Interrupt Flag bit mask. */
#define RTC_OVFIF_bp  0  /* Overflow Interrupt Flag bit position. */
#define RTC_COMPIF_bm  0x02  /* Compare Match Interrupt Flag bit mask. */
#define RTC_COMPIF_bp  1  /* Compare Match Interrupt Flag bit position. */































/* SLEEP - Sleep Controller */
/* SLEEP.CTRL  bit masks and bit positions */
#define SLEEP_SEN_bm  0x01  /* Sleep Enable bit mask. */
#define SLEEP_SEN_bp  0  /* Sleep Enable bit position. */
#define SLEEP_SMODE_gm  0x0E  /* Sleep Mode group mask. */
#define SLEEP_SMODE_gp  1  /* Sleep Mode group position. */
#define SLEEP_SMODE0_bm  (1<<1)  /* Sleep Mode bit 0 mask. */
#define SLEEP_SMODE0_bp  1  /* Sleep Mode bit 0 position. */
#define SLEEP_SMODE1_bm  (1<<2)  /* Sleep Mode bit 1 mask. */
#define SLEEP_SMODE1_bp  2  /* Sleep Mode bit 1 position. */
#define SLEEP_SMODE2_bm  (1<<3)  /* Sleep Mode bit 2 mask. */
#define SLEEP_SMODE2_bp  3  /* Sleep Mode bit 2 position. */

/* SPI - Serial Peripheral Interface */
/* SPI.CTRL  bit masks and bit positions */
#define SPI_PRESCALER_gm  0x03  /* Prescaler group mask. */
#define SPI_PRESCALER_gp  0  /* Prescaler group position. */
#define SPI_PRESCALER0_bm  (1<<0)  /* Prescaler bit 0 mask. */
#define SPI_PRESCALER0_bp  0  /* Prescaler bit 0 position. */
#define SPI_PRESCALER1_bm  (1<<1)  /* Prescaler bit 1 mask. */
#define SPI_PRESCALER1_bp  1  /* Prescaler bit 1 position. */
#define SPI_MODE_gm  0x0C  /* SPI Mode group mask. */
#define SPI_MODE_gp  2  /* SPI Mode group position. */
#define SPI_MODE0_bm  (1<<2)  /* SPI Mode bit 0 mask. */
#define SPI_MODE0_bp  2  /* SPI Mode bit 0 position. */
#define SPI_MODE1_bm  (1<<3)  /* SPI Mode bit 1 mask. */
#define SPI_MODE1_bp  3  /* SPI Mode bit 1 position. */
#define SPI_MASTER_bm  0x10  /* Master Operation Enable bit mask. */
#define SPI_MASTER_bp  4  /* Master Operation Enable bit position. */
#define SPI_DORD_bm  0x20  /* Data Order Setting bit mask. */
#define SPI_DORD_bp  5  /* Data Order Setting bit position. */
#define SPI_ENABLE_bm  0x40  /* Enable Module bit mask. */
#define SPI_ENABLE_bp  6  /* Enable Module bit position. */
#define SPI_CLK2X_bm  0x80  /* Enable Double Speed bit mask. */
#define SPI_CLK2X_bp  7  /* Enable Double Speed bit position. */

/* SPI.INTCTRL  bit masks and bit positions */
#define SPI_INTLVL_gm  0x03  /* Interrupt level group mask. */
#define SPI_INTLVL_gp  0  /* Interrupt level group position. */
#define SPI_INTLVL0_bm  (1<<0)  /* Interrupt level bit 0 mask. */
#define SPI_INTLVL0_bp  0  /* Interrupt level bit 0 position. */
#define SPI_INTLVL1_bm  (1<<1)  /* Interrupt level bit 1 mask. */
#define SPI_INTLVL1_bp  1  /* Interrupt level bit 1 position. */

/* SPI.STATUS  bit masks and bit positions */
#define SPI_WRCOL_bm  0x40  /* Write Collision bit mask. */
#define SPI_WRCOL_bp  6  /* Write Collision bit position. */
#define SPI_IF_bm  0x80  /* Interrupt Flag bit mask. */
#define SPI_IF_bp  7  /* Interrupt Flag bit position. */


/* TC - 16-bit Timer/Counter With PWM */
/* TC0.CTRLA  bit masks and bit positions */
#define TC0_CLKSEL_gm  0x0F  /* Clock Selection group mask. */
#define TC0_CLKSEL_gp  0  /* Clock Selection group position. */
#define TC0_CLKSEL0_bm  (1<<0)  /* Clock Selection bit 0 mask. */
#define TC0_CLKSEL0_bp  0  /* Clock Selection bit 0 position. */
#define TC0_CLKSEL1_bm  (1<<1)  /* Clock Selection bit 1 mask. */
#define TC0_CLKSEL1_bp  1  /* Clock Selection bit 1 position. */
#define TC0_CLKSEL2_bm  (1<<2)  /* Clock Selection bit 2 mask. */
#define TC0_CLKSEL2_bp  2  /* Clock Selection bit 2 position. */
#define TC0_CLKSEL3_bm  (1<<3)  /* Clock Selection bit 3 mask. */
#define TC0_CLKSEL3_bp  3  /* Clock Selection bit 3 position. */

/* TC0.CTRLB  bit masks and bit positions */
#define TC0_WGMODE_gm  0x07  /* Waveform generation mode group mask. */
#define TC0_WGMODE_gp  0  /* Waveform generation mode group position. */
#define TC0_WGMODE0_bm  (1<<0)  /* Waveform generation mode bit 0 mask. */
#define TC0_WGMODE0_bp  0  /* Waveform generation mode bit 0 position. */
#define TC0_WGMODE1_bm  (1<<1)  /* Waveform generation mode bit 1 mask. */
#define TC0_WGMODE1_bp  1  /* Waveform generation mode bit 1 position. */
#define TC0_WGMODE2_bm  (1<<2)  /* Waveform generation mode bit 2 mask. */
#define TC0_WGMODE2_bp  2  /* Waveform generation mode bit 2 position. */
#define TC0_CCAEN_bm  0x10  /* Compare or Capture A Enable bit mask. */
#define TC0_CCAEN_bp  4  /* Compare or Capture A Enable bit position. */
#define TC0_CCBEN_bm  0x20  /* Compare or Capture B Enable bit mask. */
#define TC0_CCBEN_bp  5  /* Compare or Capture B Enable bit position. */
#define TC0_CCCEN_bm  0x40  /* Compare or Capture C Enable bit mask. */
#define TC0_CCCEN_bp  6  /* Compare or Capture C Enable bit position. */
#define TC0_CCDEN_bm  0x80  /* Compare or Capture D Enable bit mask. */
#define TC0_CCDEN_bp  7  /* Compare or Capture D Enable bit position. */

/* TC0.CTRLC  bit masks and bit positions */
#define TC0_CMPA_bm  0x01  /* Compare A Output Value bit mask. */
#define TC0_CMPA_bp  0  /* Compare A Output Value bit position. */
#define TC0_CMPB_bm  0x02  /* Compare B Output Value bit mask. */
#define TC0_CMPB_bp  1  /* Compare B Output Value bit position. */
#define TC0_CMPC_bm  0x04  /* Compare C Output Value bit mask. */
#define TC0_CMPC_bp  2  /* Compare C Output Value bit position. */
#define TC0_CMPD_bm  0x08  /* Compare D Output Value bit mask. */
#define TC0_CMPD_bp  3  /* Compare D Output Value bit position. */

/* TC0.CTRLD  bit masks and bit positions */
#define TC0_EVSEL_gm  0x0F  /* Event Source Select group mask. */
#define TC0_EVSEL_gp  0  /* Event Source Select group position. */
#define TC0_EVSEL0_bm  (1<<0)  /* Event Source Select bit 0 mask. */
#define TC0_EVSEL0_bp  0  /* Event Source Select bit 0 position. */
#define TC0_EVSEL1_bm  (1<<1)  /* Event Source Select bit 1 mask. */
#define TC0_EVSEL1_bp  1  /* Event Source Select bit 1 position. */
#define TC0_EVSEL2_bm  (1<<2)  /* Event Source Select bit 2 mask. */
#define TC0_EVSEL2_bp  2  /* Event Source Select bit 2 position. */
#define TC0_EVSEL3_bm  (1<<3)  /* Event Source Select bit 3 mask. */
#define TC0_EVSEL3_bp  3  /* Event Source Select bit 3 position. */
#define TC0_EVDLY_bm  0x10  /* Event Delay bit mask. */
#define TC0_EVDLY_bp  4  /* Event Delay bit position. */
#define TC0_EVACT_gm  0xE0  /* Event Action group mask. */
#define TC0_EVACT_gp  5  /* Event Action group position. */
#define TC0_EVACT0_bm  (1<<5)  /* Event Action bit 0 mask. */
#define TC0_EVACT0_bp  5  /* Event Action bit 0 position. */
#define TC0_EVACT1_bm  (1<<6)  /* Event Action bit 1 mask. */
#define TC0_EVACT1_bp  6  /* Event Action bit 1 position. */
#define TC0_EVACT2_bm  (1<<7)  /* Event Action bit 2 mask. */
#define TC0_EVACT2_bp  7  /* Event Action bit 2 position. */

/* TC0.CTRLE  bit masks and bit positions */
#define TC0_BYTEM_gm  0x03  /* Byte Mode group mask. */
#define TC0_BYTEM_gp  0  /* Byte Mode group position. */
#define TC0_BYTEM0_bm  (1<<0)  /* Byte Mode bit 0 mask. */
#define TC0_BYTEM0_bp  0  /* Byte Mode bit 0 position. */
#define TC0_BYTEM1_bm  (1<<1)  /* Byte Mode bit 1 mask. */
#define TC0_BYTEM1_bp  1  /* Byte Mode bit 1 position. */

/* TC0.INTCTRLA  bit masks and bit positions */
#define TC0_OVFINTLVL_gm  0x03  /* Overflow interrupt level group mask. */
#define TC0_OVFINTLVL_gp  0  /* Overflow interrupt level group position. */
#define TC0_OVFINTLVL0_bm  (1<<0)  /* Overflow interrupt level bit 0 mask. */
#define TC0_OVFINTLVL0_bp  0  /* Overflow interrupt level bit 0 position. */
#define TC0_OVFINTLVL1_bm  (1<<1)  /* Overflow interrupt level bit 1 mask. */
#define TC0_OVFINTLVL1_bp  1  /* Overflow interrupt level bit 1 position. */
#define TC0_ERRINTLVL_gm  0x0C  /* Error Interrupt Level group mask. */
#define TC0_ERRINTLVL_gp  2  /* Error Interrupt Level group position. */
#define TC0_ERRINTLVL0_bm  (1<<2)  /* Error Interrupt Level bit 0 mask. */
#define TC0_ERRINTLVL0_bp  2  /* Error Interrupt Level bit 0 position. */
#define TC0_ERRINTLVL1_bm  (1<<3)  /* Error Interrupt Level bit 1 mask. */
#define TC0_ERRINTLVL1_bp  3  /* Error Interrupt Level bit 1 position. */

/* TC0.INTCTRLB  bit masks and bit positions */
#define TC0_CCAINTLVL_gm  0x03  /* Compare or Capture A Interrupt Level group mask. */
#define TC0_CCAINTLVL_gp  0  /* Compare or Capture A Interrupt Level group position. */
#define TC0_CCAINTLVL0_bm  (1<<0)  /* Compare or Capture A Interrupt Level bit 0 mask. */
#define TC0_CCAINTLVL0_bp  0  /* Compare or Capture A Interrupt Level bit 0 position. */
#define TC0_CCAINTLVL1_bm  (1<<1)  /* Compare or Capture A Interrupt Level bit 1 mask. */
#define TC0_CCAINTLVL1_bp  1  /* Compare or Capture A Interrupt Level bit 1 position. */
#define TC0_CCBINTLVL_gm  0x0C  /* Compare or Capture B Interrupt Level group mask. */
#define TC0_CCBINTLVL_gp  2  /* Compare or Capture B Interrupt Level group position. */
#define TC0_CCBINTLVL0_bm  (1<<2)  /* Compare or Capture B Interrupt Level bit 0 mask. */
#define TC0_CCBINTLVL0_bp  2  /* Compare or Capture B Interrupt Level bit 0 position. */
#define TC0_CCBINTLVL1_bm  (1<<3)  /* Compare or Capture B Interrupt Level bit 1 mask. */
#define TC0_CCBINTLVL1_bp  3  /* Compare or Capture B Interrupt Level bit 1 position. */
#define TC0_CCCINTLVL_gm  0x30  /* Compare or Capture C Interrupt Level group mask. */
#define TC0_CCCINTLVL_gp  4  /* Compare or Capture C Interrupt Level group position. */
#define TC0_CCCINTLVL0_bm  (1<<4)  /* Compare or Capture C Interrupt Level bit 0 mask. */
#define TC0_CCCINTLVL0_bp  4  /* Compare or Capture C Interrupt Level bit 0 position. */
#define TC0_CCCINTLVL1_bm  (1<<5)  /* Compare or Capture C Interrupt Level bit 1 mask. */
#define TC0_CCCINTLVL1_bp  5  /* Compare or Capture C Interrupt Level bit 1 position. */
#define TC0_CCDINTLVL_gm  0xC0  /* Compare or Capture D Interrupt Level group mask. */
#define TC0_CCDINTLVL_gp  6  /* Compare or Capture D Interrupt Level group position. */
#define TC0_CCDINTLVL0_bm  (1<<6)  /* Compare or Capture D Interrupt Level bit 0 mask. */
#define TC0_CCDINTLVL0_bp  6  /* Compare or Capture D Interrupt Level bit 0 position. */
#define TC0_CCDINTLVL1_bm  (1<<7)  /* Compare or Capture D Interrupt Level bit 1 mask. */
#define TC0_CCDINTLVL1_bp  7  /* Compare or Capture D Interrupt Level bit 1 position. */

/* TC0.CTRLFCLR  bit masks and bit positions */
#define TC0_DIR_bm  0x01  /* Direction bit mask. */
#define TC0_DIR_bp  0  /* Direction bit position. */
#define TC0_LUPD_bm  0x02  /* Lock Update bit mask. */
#define TC0_LUPD_bp  1  /* Lock Update bit position. */
#define TC0_CMD_gm  0x0C  /* Command group mask. */
#define TC0_CMD_gp  2  /* Command group position. */
#define TC0_CMD0_bm  (1<<2)  /* Command bit 0 mask. */
#define TC0_CMD0_bp  2  /* Command bit 0 position. */
#define TC0_CMD1_bm  (1<<3)  /* Command bit 1 mask. */
#define TC0_CMD1_bp  3  /* Command bit 1 position. */

/* TC0.CTRLFSET  bit masks and bit positions */
/* TC0_DIR  is already defined. */
/* TC0_LUPD  is already defined. */
/* TC0_CMD  is already defined. */

/* TC0.CTRLGCLR  bit masks and bit positions */
#define TC0_PERBV_bm  0x01  /* Period Buffer Valid bit mask. */
#define TC0_PERBV_bp  0  /* Period Buffer Valid bit position. */
#define TC0_CCABV_bm  0x02  /* Compare or Capture A Buffer Valid bit mask. */
#define TC0_CCABV_bp  1  /* Compare or Capture A Buffer Valid bit position. */
#define TC0_CCBBV_bm  0x04  /* Compare or Capture B Buffer Valid bit mask. */
#define TC0_CCBBV_bp  2  /* Compare or Capture B Buffer Valid bit position. */
#define TC0_CCCBV_bm  0x08  /* Compare or Capture C Buffer Valid bit mask. */
#define TC0_CCCBV_bp  3  /* Compare or Capture C Buffer Valid bit position. */
#define TC0_CCDBV_bm  0x10  /* Compare or Capture D Buffer Valid bit mask. */
#define TC0_CCDBV_bp  4  /* Compare or Capture D Buffer Valid bit position. */

/* TC0.CTRLGSET  bit masks and bit positions */
/* TC0_PERBV  is already defined. */
/* TC0_CCABV  is already defined. */
/* TC0_CCBBV  is already defined. */
/* TC0_CCCBV  is already defined. */
/* TC0_CCDBV  is already defined. */

/* TC0.INTFLAGS  bit masks and bit positions */
#define TC0_OVFIF_bm  0x01  /* Overflow Interrupt Flag bit mask. */
#define TC0_OVFIF_bp  0  /* Overflow Interrupt Flag bit position. */
#define TC0_ERRIF_bm  0x02  /* Error Interrupt Flag bit mask. */
#define TC0_ERRIF_bp  1  /* Error Interrupt Flag bit position. */
#define TC0_CCAIF_bm  0x10  /* Compare or Capture A Interrupt Flag bit mask. */
#define TC0_CCAIF_bp  4  /* Compare or Capture A Interrupt Flag bit position. */
#define TC0_CCBIF_bm  0x20  /* Compare or Capture B Interrupt Flag bit mask. */
#define TC0_CCBIF_bp  5  /* Compare or Capture B Interrupt Flag bit position. */
#define TC0_CCCIF_bm  0x40  /* Compare or Capture C Interrupt Flag bit mask. */
#define TC0_CCCIF_bp  6  /* Compare or Capture C Interrupt Flag bit position. */
#define TC0_CCDIF_bm  0x80  /* Compare or Capture D Interrupt Flag bit mask. */
#define TC0_CCDIF_bp  7  /* Compare or Capture D Interrupt Flag bit position. */













/* TC1.CTRLA  bit masks and bit positions */
#define TC1_CLKSEL_gm  0x0F  /* Clock Selection group mask. */
#define TC1_CLKSEL_gp  0  /* Clock Selection group position. */
#define TC1_CLKSEL0_bm  (1<<0)  /* Clock Selection bit 0 mask. */
#define TC1_CLKSEL0_bp  0  /* Clock Selection bit 0 position. */
#define TC1_CLKSEL1_bm  (1<<1)  /* Clock Selection bit 1 mask. */
#define TC1_CLKSEL1_bp  1  /* Clock Selection bit 1 position. */
#define TC1_CLKSEL2_bm  (1<<2)  /* Clock Selection bit 2 mask. */
#define TC1_CLKSEL2_bp  2  /* Clock Selection bit 2 position. */
#define TC1_CLKSEL3_bm  (1<<3)  /* Clock Selection bit 3 mask. */
#define TC1_CLKSEL3_bp  3  /* Clock Selection bit 3 position. */

/* TC1.CTRLB  bit masks and bit positions */
#define TC1_WGMODE_gm  0x07  /* Waveform generation mode group mask. */
#define TC1_WGMODE_gp  0  /* Waveform generation mode group position. */
#define TC1_WGMODE0_bm  (1<<0)  /* Waveform generation mode bit 0 mask. */
#define TC1_WGMODE0_bp  0  /* Waveform generation mode bit 0 position. */
#define TC1_WGMODE1_bm  (1<<1)  /* Waveform generation mode bit 1 mask. */
#define TC1_WGMODE1_bp  1  /* Waveform generation mode bit 1 position. */
#define TC1_WGMODE2_bm  (1<<2)  /* Waveform generation mode bit 2 mask. */
#define TC1_WGMODE2_bp  2  /* Waveform generation mode bit 2 position. */
#define TC1_CCAEN_bm  0x10  /* Compare or Capture A Enable bit mask. */
#define TC1_CCAEN_bp  4  /* Compare or Capture A Enable bit position. */
#define TC1_CCBEN_bm  0x20  /* Compare or Capture B Enable bit mask. */
#define TC1_CCBEN_bp  5  /* Compare or Capture B Enable bit position. */

/* TC1.CTRLC  bit masks and bit positions */
#define TC1_CMPA_bm  0x01  /* Compare A Output Value bit mask. */
#define TC1_CMPA_bp  0  /* Compare A Output Value bit position. */
#define TC1_CMPB_bm  0x02  /* Compare B Output Value bit mask. */
#define TC1_CMPB_bp  1  /* Compare B Output Value bit position. */

/* TC1.CTRLD  bit masks and bit positions */
#define TC1_EVSEL_gm  0x0F  /* Event Source Select group mask. */
#define TC1_EVSEL_gp  0  /* Event Source Select group position. */
#define TC1_EVSEL0_bm  (1<<0)  /* Event Source Select bit 0 mask. */
#define TC1_EVSEL0_bp  0  /* Event Source Select bit 0 position. */
#define TC1_EVSEL1_bm  (1<<1)  /* Event Source Select bit 1 mask. */
#define TC1_EVSEL1_bp  1  /* Event Source Select bit 1 position. */
#define TC1_EVSEL2_bm  (1<<2)  /* Event Source Select bit 2 mask. */
#define TC1_EVSEL2_bp  2  /* Event Source Select bit 2 position. */
#define TC1_EVSEL3_bm  (1<<3)  /* Event Source Select bit 3 mask. */
#define TC1_EVSEL3_bp  3  /* Event Source Select bit 3 position. */
#define TC1_EVDLY_bm  0x10  /* Event Delay bit mask. */
#define TC1_EVDLY_bp  4  /* Event Delay bit position. */
#define TC1_EVACT_gm  0xE0  /* Event Action group mask. */
#define TC1_EVACT_gp  5  /* Event Action group position. */
#define TC1_EVACT0_bm  (1<<5)  /* Event Action bit 0 mask. */
#define TC1_EVACT0_bp  5  /* Event Action bit 0 position. */
#define TC1_EVACT1_bm  (1<<6)  /* Event Action bit 1 mask. */
#define TC1_EVACT1_bp  6  /* Event Action bit 1 position. */
#define TC1_EVACT2_bm  (1<<7)  /* Event Action bit 2 mask. */
#define TC1_EVACT2_bp  7  /* Event Action bit 2 position. */

/* TC1.CTRLE  bit masks and bit positions */
#define TC1_BYTEM_bm  0x01  /* Byte Mode bit mask. */
#define TC1_BYTEM_bp  0  /* Byte Mode bit position. */

/* TC1.INTCTRLA  bit masks and bit positions */
#define TC1_OVFINTLVL_gm  0x03  /* Overflow interrupt level group mask. */
#define TC1_OVFINTLVL_gp  0  /* Overflow interrupt level group position. */
#define TC1_OVFINTLVL0_bm  (1<<0)  /* Overflow interrupt level bit 0 mask. */
#define TC1_OVFINTLVL0_bp  0  /* Overflow interrupt level bit 0 position. */
#define TC1_OVFINTLVL1_bm  (1<<1)  /* Overflow interrupt level bit 1 mask. */
#define TC1_OVFINTLVL1_bp  1  /* Overflow interrupt level bit 1 position. */
#define TC1_ERRINTLVL_gm  0x0C  /* Error Interrupt Level group mask. */
#define TC1_ERRINTLVL_gp  2  /* Error Interrupt Level group position. */
#define TC1_ERRINTLVL0_bm  (1<<2)  /* Error Interrupt Level bit 0 mask. */
#define TC1_ERRINTLVL0_bp  2  /* Error Interrupt Level bit 0 position. */
#define TC1_ERRINTLVL1_bm  (1<<3)  /* Error Interrupt Level bit 1 mask. */
#define TC1_ERRINTLVL1_bp  3  /* Error Interrupt Level bit 1 position. */

/* TC1.INTCTRLB  bit masks and bit positions */
#define TC1_CCAINTLVL_gm  0x03  /* Compare or Capture A Interrupt Level group mask. */
#define TC1_CCAINTLVL_gp  0  /* Compare or Capture A Interrupt Level group position. */
#define TC1_CCAINTLVL0_bm  (1<<0)  /* Compare or Capture A Interrupt Level bit 0 mask. */
#define TC1_CCAINTLVL0_bp  0  /* Compare or Capture A Interrupt Level bit 0 position. */
#define TC1_CCAINTLVL1_bm  (1<<1)  /* Compare or Capture A Interrupt Level bit 1 mask. */
#define TC1_CCAINTLVL1_bp  1  /* Compare or Capture A Interrupt Level bit 1 position. */
#define TC1_CCBINTLVL_gm  0x0C  /* Compare or Capture B Interrupt Level group mask. */
#define TC1_CCBINTLVL_gp  2  /* Compare or Capture B Interrupt Level group position. */
#define TC1_CCBINTLVL0_bm  (1<<2)  /* Compare or Capture B Interrupt Level bit 0 mask. */
#define TC1_CCBINTLVL0_bp  2  /* Compare or Capture B Interrupt Level bit 0 position. */
#define TC1_CCBINTLVL1_bm  (1<<3)  /* Compare or Capture B Interrupt Level bit 1 mask. */
#define TC1_CCBINTLVL1_bp  3  /* Compare or Capture B Interrupt Level bit 1 position. */

/* TC1.CTRLFCLR  bit masks and bit positions */
#define TC1_DIR_bm  0x01  /* Direction bit mask. */
#define TC1_DIR_bp  0  /* Direction bit position. */
#define TC1_LUPD_bm  0x02  /* Lock Update bit mask. */
#define TC1_LUPD_bp  1  /* Lock Update bit position. */
#define TC1_CMD_gm  0x0C  /* Command group mask. */
#define TC1_CMD_gp  2  /* Command group position. */
#define TC1_CMD0_bm  (1<<2)  /* Command bit 0 mask. */
#define TC1_CMD0_bp  2  /* Command bit 0 position. */
#define TC1_CMD1_bm  (1<<3)  /* Command bit 1 mask. */
#define TC1_CMD1_bp  3  /* Command bit 1 position. */

/* TC1.CTRLFSET  bit masks and bit positions */
/* TC1_DIR  is already defined. */
/* TC1_LUPD  is already defined. */
/* TC1_CMD  is already defined. */

/* TC1.CTRLGCLR  bit masks and bit positions */
#define TC1_PERBV_bm  0x01  /* Period Buffer Valid bit mask. */
#define TC1_PERBV_bp  0  /* Period Buffer Valid bit position. */
#define TC1_CCABV_bm  0x02  /* Compare or Capture A Buffer Valid bit mask. */
#define TC1_CCABV_bp  1  /* Compare or Capture A Buffer Valid bit position. */
#define TC1_CCBBV_bm  0x04  /* Compare or Capture B Buffer Valid bit mask. */
#define TC1_CCBBV_bp  2  /* Compare or Capture B Buffer Valid bit position. */

/* TC1.CTRLGSET  bit masks and bit positions */
/* TC1_PERBV  is already defined. */
/* TC1_CCABV  is already defined. */
/* TC1_CCBBV  is already defined. */

/* TC1.INTFLAGS  bit masks and bit positions */
#define TC1_OVFIF_bm  0x01  /* Overflow Interrupt Flag bit mask. */
#define TC1_OVFIF_bp  0  /* Overflow Interrupt Flag bit position. */
#define TC1_ERRIF_bm  0x02  /* Error Interrupt Flag bit mask. */
#define TC1_ERRIF_bp  1  /* Error Interrupt Flag bit position. */
#define TC1_CCAIF_bm  0x10  /* Compare or Capture A Interrupt Flag bit mask. */
#define TC1_CCAIF_bp  4  /* Compare or Capture A Interrupt Flag bit position. */
#define TC1_CCBIF_bm  0x20  /* Compare or Capture B Interrupt Flag bit mask. */
#define TC1_CCBIF_bp  5  /* Compare or Capture B Interrupt Flag bit position. */









/* TC2 - 16-bit Timer/Counter type 2 */
/* TC2.CTRLA  bit masks and bit positions */
#define TC2_CLKSEL_gm  0x0F  /* Clock Selection group mask. */
#define TC2_CLKSEL_gp  0  /* Clock Selection group position. */
#define TC2_CLKSEL0_bm  (1<<0)  /* Clock Selection bit 0 mask. */
#define TC2_CLKSEL0_bp  0  /* Clock Selection bit 0 position. */
#define TC2_CLKSEL1_bm  (1<<1)  /* Clock Selection bit 1 mask. */
#define TC2_CLKSEL1_bp  1  /* Clock Selection bit 1 position. */
#define TC2_CLKSEL2_bm  (1<<2)  /* Clock Selection bit 2 mask. */
#define TC2_CLKSEL2_bp  2  /* Clock Selection bit 2 position. */
#define TC2_CLKSEL3_bm  (1<<3)  /* Clock Selection bit 3 mask. */
#define TC2_CLKSEL3_bp  3  /* Clock Selection bit 3 position. */

/* TC2.CTRLB  bit masks and bit positions */
#define TC2_LCMPAEN_bm  0x01  /* Low Byte Compare A Enable bit mask. */
#define TC2_LCMPAEN_bp  0  /* Low Byte Compare A Enable bit position. */
#define TC2_LCMPBEN_bm  0x02  /* Low Byte Compare B Enable bit mask. */
#define TC2_LCMPBEN_bp  1  /* Low Byte Compare B Enable bit position. */
#define TC2_LCMPCEN_bm  0x04  /* Low Byte Compare C Enable bit mask. */
#define TC2_LCMPCEN_bp  2  /* Low Byte Compare C Enable bit position. */
#define TC2_LCMPDEN_bm  0x08  /* Low Byte Compare D Enable bit mask. */
#define TC2_LCMPDEN_bp  3  /* Low Byte Compare D Enable bit position. */
#define TC2_HCMPAEN_bm  0x10  /* High Byte Compare A Enable bit mask. */
#define TC2_HCMPAEN_bp  4  /* High Byte Compare A Enable bit position. */
#define TC2_HCMPBEN_bm  0x20  /* High Byte Compare B Enable bit mask. */
#define TC2_HCMPBEN_bp  5  /* High Byte Compare B Enable bit position. */
#define TC2_HCMPCEN_bm  0x40  /* High Byte Compare C Enable bit mask. */
#define TC2_HCMPCEN_bp  6  /* High Byte Compare C Enable bit position. */
#define TC2_HCMPDEN_bm  0x80  /* High Byte Compare D Enable bit mask. */
#define TC2_HCMPDEN_bp  7  /* High Byte Compare D Enable bit position. */

/* TC2.CTRLC  bit masks and bit positions */
#define TC2_LCMPA_bm  0x01  /* Low Byte Compare A Output Value bit mask. */
#define TC2_LCMPA_bp  0  /* Low Byte Compare A Output Value bit position. */
#define TC2_LCMPB_bm  0x02  /* Low Byte Compare B Output Value bit mask. */
#define TC2_LCMPB_bp  1  /* Low Byte Compare B Output Value bit position. */
#define TC2_LCMPC_bm  0x04  /* Low Byte Compare C Output Value bit mask. */
#define TC2_LCMPC_bp  2  /* Low Byte Compare C Output Value bit position. */
#define TC2_LCMPD_bm  0x08  /* Low Byte Compare D Output Value bit mask. */
#define TC2_LCMPD_bp  3  /* Low Byte Compare D Output Value bit position. */
#define TC2_HCMPA_bm  0x10  /* High Byte Compare A Output Value bit mask. */
#define TC2_HCMPA_bp  4  /* High Byte Compare A Output Value bit position. */
#define TC2_HCMPB_bm  0x20  /* High Byte Compare B Output Value bit mask. */
#define TC2_HCMPB_bp  5  /* High Byte Compare B Output Value bit position. */
#define TC2_HCMPC_bm  0x40  /* High Byte Compare C Output Value bit mask. */
#define TC2_HCMPC_bp  6  /* High Byte Compare C Output Value bit position. */
#define TC2_HCMPD_bm  0x80  /* High Byte Compare D Output Value bit mask. */
#define TC2_HCMPD_bp  7  /* High Byte Compare D Output Value bit position. */

/* TC2.CTRLE  bit masks and bit positions */
#define TC2_BYTEM_gm  0x03  /* Byte Mode group mask. */
#define TC2_BYTEM_gp  0  /* Byte Mode group position. */
#define TC2_BYTEM0_bm  (1<<0)  /* Byte Mode bit 0 mask. */
#define TC2_BYTEM0_bp  0  /* Byte Mode bit 0 position. */
#define TC2_BYTEM1_bm  (1<<1)  /* Byte Mode bit 1 mask. */
#define TC2_BYTEM1_bp  1  /* Byte Mode bit 1 position. */

/* TC2.INTCTRLA  bit masks and bit positions */
#define TC2_LUNFINTLVL_gm  0x03  /* Low Byte Underflow interrupt level group mask. */
#define TC2_LUNFINTLVL_gp  0  /* Low Byte Underflow interrupt level group position. */
#define TC2_LUNFINTLVL0_bm  (1<<0)  /* Low Byte Underflow interrupt level bit 0 mask. */
#define TC2_LUNFINTLVL0_bp  0  /* Low Byte Underflow interrupt level bit 0 position. */
#define TC2_LUNFINTLVL1_bm  (1<<1)  /* Low Byte Underflow interrupt level bit 1 mask. */
#define TC2_LUNFINTLVL1_bp  1  /* Low Byte Underflow interrupt level bit 1 position. */
#define TC2_HUNFINTLVL_gm  0x0C  /* High Byte Underflow Interrupt Level group mask. */
#define TC2_HUNFINTLVL_gp  2  /* High Byte Underflow Interrupt Level group position. */
#define TC2_HUNFINTLVL0_bm  (1<<2)  /* High Byte Underflow Interrupt Level bit 0 mask. */
#define TC2_HUNFINTLVL0_bp  2  /* High Byte Underflow Interrupt Level bit 0 position. */
#define TC2_HUNFINTLVL1_bm  (1<<3)  /* High Byte Underflow Interrupt Level bit 1 mask. */
#define TC2_HUNFINTLVL1_bp  3  /* High Byte Underflow Interrupt Level bit 1 position. */

/* TC2.INTCTRLB  bit masks and bit positions */
#define TC2_LCMPAINTLVL_gm  0x03  /* Low Byte Compare A Interrupt Level group mask. */
#define TC2_LCMPAINTLVL_gp  0  /* Low Byte Compare A Interrupt Level group position. */
#define TC2_LCMPAINTLVL0_bm  (1<<0)  /* Low Byte Compare A Interrupt Level bit 0 mask. */
#define TC2_LCMPAINTLVL0_bp  0  /* Low Byte Compare A Interrupt Level bit 0 position. */
#define TC2_LCMPAINTLVL1_bm  (1<<1)  /* Low Byte Compare A Interrupt Level bit 1 mask. */
#define TC2_LCMPAINTLVL1_bp  1  /* Low Byte Compare A Interrupt Level bit 1 position. */
#define TC2_LCMPBINTLVL_gm  0x0C  /* Low Byte Compare B Interrupt Level group mask. */
#define TC2_LCMPBINTLVL_gp  2  /* Low Byte Compare B Interrupt Level group position. */
#define TC2_LCMPBINTLVL0_bm  (1<<2)  /* Low Byte Compare B Interrupt Level bit 0 mask. */
#define TC2_LCMPBINTLVL0_bp  2  /* Low Byte Compare B Interrupt Level bit 0 position. */
#define TC2_LCMPBINTLVL1_bm  (1<<3)  /* Low Byte Compare B Interrupt Level bit 1 mask. */
#define TC2_LCMPBINTLVL1_bp  3  /* Low Byte Compare B Interrupt Level bit 1 position. */
#define TC2_LCMPCINTLVL_gm  0x30  /* Low Byte Compare C Interrupt Level group mask. */
#define TC2_LCMPCINTLVL_gp  4  /* Low Byte Compare C Interrupt Level group position. */
#define TC2_LCMPCINTLVL0_bm  (1<<4)  /* Low Byte Compare C Interrupt Level bit 0 mask. */
#define TC2_LCMPCINTLVL0_bp  4  /* Low Byte Compare C Interrupt Level bit 0 position. */
#define TC2_LCMPCINTLVL1_bm  (1<<5)  /* Low Byte Compare C Interrupt Level bit 1 mask. */
#define TC2_LCMPCINTLVL1_bp  5  /* Low Byte Compare C Interrupt Level bit 1 position. */
#define TC2_LCMPDINTLVL_gm  0xC0  /* Low Byte Compare D Interrupt Level group mask. */
#define TC2_LCMPDINTLVL_gp  6  /* Low Byte Compare D Interrupt Level group position. */
#define TC2_LCMPDINTLVL0_bm  (1<<6)  /* Low Byte Compare D Interrupt Level bit 0 mask. */
#define TC2_LCMPDINTLVL0_bp  6  /* Low Byte Compare D Interrupt Level bit 0 position. */
#define TC2_LCMPDINTLVL1_bm  (1<<7)  /* Low Byte Compare D Interrupt Level bit 1 mask. */
#define TC2_LCMPDINTLVL1_bp  7  /* Low Byte Compare D Interrupt Level bit 1 position. */

/* TC2.CTRLF  bit masks and bit positions */
#define TC2_CMDEN_gm  0x03  /* Command Enable group mask. */
#define TC2_CMDEN_gp  0  /* Command Enable group position. */
#define TC2_CMDEN0_bm  (1<<0)  /* Command Enable bit 0 mask. */
#define TC2_CMDEN0_bp  0  /* Command Enable bit 0 position. */
#define TC2_CMDEN1_bm  (1<<1)  /* Command Enable bit 1 mask. */
#define TC2_CMDEN1_bp  1  /* Command Enable bit 1 position. */
#define TC2_CMD_gm  0x0C  /* Command group mask. */
#define TC2_CMD_gp  2  /* Command group position. */
#define TC2_CMD0_bm  (1<<2)  /* Command bit 0 mask. */
#define TC2_CMD0_bp  2  /* Command bit 0 position. */
#define TC2_CMD1_bm  (1<<3)  /* Command bit 1 mask. */
#define TC2_CMD1_bp  3  /* Command bit 1 position. */

/* TC2.INTFLAGS  bit masks and bit positions */
#define TC2_LUNFIF_bm  0x01  /* Low Byte Underflow Interrupt Flag bit mask. */
#define TC2_LUNFIF_bp  0  /* Low Byte Underflow Interrupt Flag bit position. */
#define TC2_HUNFIF_bm  0x02  /* High Byte Underflow Interrupt Flag bit mask. */
#define TC2_HUNFIF_bp  1  /* High Byte Underflow Interrupt Flag bit position. */
#define TC2_LCMPAIF_bm  0x10  /* Low Byte Compare A Interrupt Flag bit mask. */
#define TC2_LCMPAIF_bp  4  /* Low Byte Compare A Interrupt Flag bit position. */
#define TC2_LCMPBIF_bm  0x20  /* Low Byte Compare B Interrupt Flag bit mask. */
#define TC2_LCMPBIF_bp  5  /* Low Byte Compare B Interrupt Flag bit position. */
#define TC2_LCMPCIF_bm  0x40  /* Low Byte Compare C Interrupt Flag bit mask. */
#define TC2_LCMPCIF_bp  6  /* Low Byte Compare C Interrupt Flag bit position. */
#define TC2_LCMPDIF_bm  0x80  /* Low Byte Compare D Interrupt Flag bit mask. */
#define TC2_LCMPDIF_bp  7  /* Low Byte Compare D Interrupt Flag bit position. */













/* TWI - Two-Wire Interface */
/* TWI_MASTER.CTRLA  bit masks and bit positions */
#define TWI_MASTER_ENABLE_bm  0x08  /* Enable TWI Master bit mask. */
#define TWI_MASTER_ENABLE_bp  3  /* Enable TWI Master bit position. */
#define TWI_MASTER_WIEN_bm  0x10  /* Write Interrupt Enable bit mask. */
#define TWI_MASTER_WIEN_bp  4  /* Write Interrupt Enable bit position. */
#define TWI_MASTER_RIEN_bm  0x20  /* Read Interrupt Enable bit mask. */
#define TWI_MASTER_RIEN_bp  5  /* Read Interrupt Enable bit position. */
#define TWI_MASTER_INTLVL_gm  0xC0  /* Interrupt Level group mask. */
#define TWI_MASTER_INTLVL_gp  6  /* Interrupt Level group position. */
#define TWI_MASTER_INTLVL0_bm  (1<<6)  /* Interrupt Level bit 0 mask. */
#define TWI_MASTER_INTLVL0_bp  6  /* Interrupt Level bit 0 position. */
#define TWI_MASTER_INTLVL1_bm  (1<<7)  /* Interrupt Level bit 1 mask. */
#define TWI_MASTER_INTLVL1_bp  7  /* Interrupt Level bit 1 position. */

/* TWI_MASTER.CTRLB  bit masks and bit positions */
#define TWI_MASTER_SMEN_bm  0x01  /* Smart Mode Enable bit mask. */
#define TWI_MASTER_SMEN_bp  0  /* Smart Mode Enable bit position. */
#define TWI_MASTER_QCEN_bm  0x02  /* Quick Command Enable bit mask. */
#define TWI_MASTER_QCEN_bp  1  /* Quick Command Enable bit position. */
#define TWI_MASTER_TIMEOUT_gm  0x0C  /* Inactive Bus Timeout group mask. */
#define TWI_MASTER_TIMEOUT_gp  2  /* Inactive Bus Timeout group position. */
#define TWI_MASTER_TIMEOUT0_bm  (1<<2)  /* Inactive Bus Timeout bit 0 mask. */
#define TWI_MASTER_TIMEOUT0_bp  2  /* Inactive Bus Timeout bit 0 position. */
#define TWI_MASTER_TIMEOUT1_bm  (1<<3)  /* Inactive Bus Timeout bit 1 mask. */
#define TWI_MASTER_TIMEOUT1_bp  3  /* Inactive Bus Timeout bit 1 position. */

/* TWI_MASTER.CTRLC  bit masks and bit positions */
#define TWI_MASTER_CMD_gm  0x03  /* Command group mask. */
#define TWI_MASTER_CMD_gp  0  /* Command group position. */
#define TWI_MASTER_CMD0_bm  (1<<0)  /* Command bit 0 mask. */
#define TWI_MASTER_CMD0_bp  0  /* Command bit 0 position. */
#define TWI_MASTER_CMD1_bm  (1<<1)  /* Command bit 1 mask. */
#define TWI_MASTER_CMD1_bp  1  /* Command bit 1 position. */
#define TWI_MASTER_ACKACT_bm  0x04  /* Acknowledge Action bit mask. */
#define TWI_MASTER_ACKACT_bp  2  /* Acknowledge Action bit position. */

/* TWI_MASTER.STATUS  bit masks and bit positions */
#define TWI_MASTER_BUSSTATE_gm  0x03  /* Bus State group mask. */
#define TWI_MASTER_BUSSTATE_gp  0  /* Bus State group position. */
#define TWI_MASTER_BUSSTATE0_bm  (1<<0)  /* Bus State bit 0 mask. */
#define TWI_MASTER_BUSSTATE0_bp  0  /* Bus State bit 0 position. */
#define TWI_MASTER_BUSSTATE1_bm  (1<<1)  /* Bus State bit 1 mask. */
#define TWI_MASTER_BUSSTATE1_bp  1  /* Bus State bit 1 position. */
#define TWI_MASTER_BUSERR_bm  0x04  /* Bus Error bit mask. */
#define TWI_MASTER_BUSERR_bp  2  /* Bus Error bit position. */
#define TWI_MASTER_ARBLOST_bm  0x08  /* Arbitration Lost bit mask. */
#define TWI_MASTER_ARBLOST_bp  3  /* Arbitration Lost bit position. */
#define TWI_MASTER_RXACK_bm  0x10  /* Received Acknowledge bit mask. */
#define TWI_MASTER_RXACK_bp  4  /* Received Acknowledge bit position. */
#define TWI_MASTER_CLKHOLD_bm  0x20  /* Clock Hold bit mask. */
#define TWI_MASTER_CLKHOLD_bp  5  /* Clock Hold bit position. */
#define TWI_MASTER_WIF_bm  0x40  /* Write Interrupt Flag bit mask. */
#define TWI_MASTER_WIF_bp  6  /* Write Interrupt Flag bit position. */
#define TWI_MASTER_RIF_bm  0x80  /* Read Interrupt Flag bit mask. */
#define TWI_MASTER_RIF_bp  7  /* Read Interrupt Flag bit position. */




/* TWI_SLAVE.CTRLA  bit masks and bit positions */
#define TWI_SLAVE_SMEN_bm  0x01  /* Smart Mode Enable bit mask. */
#define TWI_SLAVE_SMEN_bp  0  /* Smart Mode Enable bit position. */
#define TWI_SLAVE_PMEN_bm  0x02  /* Promiscuous Mode Enable bit mask. */
#define TWI_SLAVE_PMEN_bp  1  /* Promiscuous Mode Enable bit position. */
#define TWI_SLAVE_PIEN_bm  0x04  /* Stop Interrupt Enable bit mask. */
#define TWI_SLAVE_PIEN_bp  2  /* Stop Interrupt Enable bit position. */
#define TWI_SLAVE_ENABLE_bm  0x08  /* Enable TWI Slave bit mask. */
#define TWI_SLAVE_ENABLE_bp  3  /* Enable TWI Slave bit position. */
#define TWI_SLAVE_APIEN_bm  0x10  /* Address/Stop Interrupt Enable bit mask. */
#define TWI_SLAVE_APIEN_bp  4  /* Address/Stop Interrupt Enable bit position. */
#define TWI_SLAVE_DIEN_bm  0x20  /* Data Interrupt Enable bit mask. */
#define TWI_SLAVE_DIEN_bp  5  /* Data Interrupt Enable bit position. */
#define TWI_SLAVE_INTLVL_gm  0xC0  /* Interrupt Level group mask. */
#define TWI_SLAVE_INTLVL_gp  6  /* Interrupt Level group position. */
#define TWI_SLAVE_INTLVL0_bm  (1<<6)  /* Interrupt Level bit 0 mask. */
#define TWI_SLAVE_INTLVL0_bp  6  /* Interrupt Level bit 0 position. */
#define TWI_SLAVE_INTLVL1_bm  (1<<7)  /* Interrupt Level bit 1 mask. */
#define TWI_SLAVE_INTLVL1_bp  7  /* Interrupt Level bit 1 position. */

/* TWI_SLAVE.CTRLB  bit masks and bit positions */
#define TWI_SLAVE_CMD_gm  0x03  /* Command group mask. */
#define TWI_SLAVE_CMD_gp  0  /* Command group position. */
#define TWI_SLAVE_CMD0_bm  (1<<0)  /* Command bit 0 mask. */
#define TWI_SLAVE_CMD0_bp  0  /* Command bit 0 position. */
#define TWI_SLAVE_CMD1_bm  (1<<1)  /* Command bit 1 mask. */
#define TWI_SLAVE_CMD1_bp  1  /* Command bit 1 position. */
#define TWI_SLAVE_ACKACT_bm  0x04  /* Acknowledge Action bit mask. */
#define TWI_SLAVE_ACKACT_bp  2  /* Acknowledge Action bit position. */

/* TWI_SLAVE.STATUS  bit masks and bit positions */
#define TWI_SLAVE_AP_bm  0x01  /* Slave Address or Stop bit mask. */
#define TWI_SLAVE_AP_bp  0  /* Slave Address or Stop bit position. */
#define TWI_SLAVE_DIR_bm  0x02  /* Read/Write Direction bit mask. */
#define TWI_SLAVE_DIR_bp  1  /* Read/Write Direction bit position. */
#define TWI_SLAVE_BUSERR_bm  0x04  /* Bus Error bit mask. */
#define TWI_SLAVE_BUSERR_bp  2  /* Bus Error bit position. */
#define TWI_SLAVE_COLL_bm  0x08  /* Collision bit mask. */
#define TWI_SLAVE_COLL_bp  3  /* Collision bit position. */
#define TWI_SLAVE_RXACK_bm  0x10  /* Received Acknowledge bit mask. */
#define TWI_SLAVE_RXACK_bp  4  /* Received Acknowledge bit position. */
#define TWI_SLAVE_CLKHOLD_bm  0x20  /* Clock Hold bit mask. */
#define TWI_SLAVE_CLKHOLD_bp  5  /* Clock Hold bit position. */
#define TWI_SLAVE_APIF_bm  0x40  /* Address/Stop Interrupt Flag bit mask. */
#define TWI_SLAVE_APIF_bp  6  /* Address/Stop Interrupt Flag bit position. */
#define TWI_SLAVE_DIF_bm  0x80  /* Data Interrupt Flag bit mask. */
#define TWI_SLAVE_DIF_bp  7  /* Data Interrupt Flag bit position. */



/* TWI_SLAVE.ADDRMASK  bit masks and bit positions */
#define TWI_SLAVE_ADDREN_bm  0x01  /* Address Enable bit mask. */
#define TWI_SLAVE_ADDREN_bp  0  /* Address Enable bit position. */
#define TWI_SLAVE_ADDRMASK_gm  0xFE  /* Address Mask group mask. */
#define TWI_SLAVE_ADDRMASK_gp  1  /* Address Mask group position. */
#define TWI_SLAVE_ADDRMASK0_bm  (1<<1)  /* Address Mask bit 0 mask. */
#define TWI_SLAVE_ADDRMASK0_bp  1  /* Address Mask bit 0 position. */
#define TWI_SLAVE_ADDRMASK1_bm  (1<<2)  /* Address Mask bit 1 mask. */
#define TWI_SLAVE_ADDRMASK1_bp  2  /* Address Mask bit 1 position. */
#define TWI_SLAVE_ADDRMASK2_bm  (1<<3)  /* Address Mask bit 2 mask. */
#define TWI_SLAVE_ADDRMASK2_bp  3  /* Address Mask bit 2 position. */
#define TWI_SLAVE_ADDRMASK3_bm  (1<<4)  /* Address Mask bit 3 mask. */
#define TWI_SLAVE_ADDRMASK3_bp  4  /* Address Mask bit 3 position. */
#define TWI_SLAVE_ADDRMASK4_bm  (1<<5)  /* Address Mask bit 4 mask. */
#define TWI_SLAVE_ADDRMASK4_bp  5  /* Address Mask bit 4 position. */
#define TWI_SLAVE_ADDRMASK5_bm  (1<<6)  /* Address Mask bit 5 mask. */
#define TWI_SLAVE_ADDRMASK5_bp  6  /* Address Mask bit 5 position. */
#define TWI_SLAVE_ADDRMASK6_bm  (1<<7)  /* Address Mask bit 6 mask. */
#define TWI_SLAVE_ADDRMASK6_bp  7  /* Address Mask bit 6 position. */

/* TWI.CTRL  bit masks and bit positions */
#define TWI_EDIEN_bm  0x01  /* External Driver Interface Enable bit mask. */
#define TWI_EDIEN_bp  0  /* External Driver Interface Enable bit position. */
#define TWI_SDAHOLD_gm  0x06  /* SDA Hold Time Enable group mask. */
#define TWI_SDAHOLD_gp  1  /* SDA Hold Time Enable group position. */
#define TWI_SDAHOLD0_bm  (1<<1)  /* SDA Hold Time Enable bit 0 mask. */
#define TWI_SDAHOLD0_bp  1  /* SDA Hold Time Enable bit 0 position. */
#define TWI_SDAHOLD1_bm  (1<<2)  /* SDA Hold Time Enable bit 1 mask. */
#define TWI_SDAHOLD1_bp  2  /* SDA Hold Time Enable bit 1 position. */


/* USART - Universal Asynchronous Receiver-Transmitter */
/* USART.STATUS  bit masks and bit positions */
#define USART_RXB8_bm  0x01  /* Receive Bit 8 bit mask. */
#define USART_RXB8_bp  0  /* Receive Bit 8 bit position. */
#define USART_PERR_bm  0x04  /* Parity Error bit mask. */
#define USART_PERR_bp  2  /* Parity Error bit position. */
#define USART_BUFOVF_bm  0x08  /* Buffer Overflow bit mask. */
#define USART_BUFOVF_bp  3  /* Buffer Overflow bit position. */
#define USART_FERR_bm  0x10  /* Frame Error bit mask. */
#define USART_FERR_bp  4  /* Frame Error bit position. */
#define USART_DREIF_bm  0x20  /* Data Register Empty Flag bit mask. */
#define USART_DREIF_bp  5  /* Data Register Empty Flag bit position. */
#define USART_TXCIF_bm  0x40  /* Transmit Interrupt Flag bit mask. */
#define USART_TXCIF_bp  6  /* Transmit Interrupt Flag bit position. */
#define USART_RXCIF_bm  0x80  /* Receive Interrupt Flag bit mask. */
#define USART_RXCIF_bp  7  /* Receive Interrupt Flag bit position. */

/* USART.CTRLA  bit masks and bit positions */
#define USART_DREINTLVL_gm  0x03  /* Data Register Empty Interrupt Level group mask. */
#define USART_DREINTLVL_gp  0  /* Data Register Empty Interrupt Level group position. */
#define USART_DREINTLVL0_bm  (1<<0)  /* Data Register Empty Interrupt Level bit 0 mask. */
#define USART_DREINTLVL0_bp  0  /* Data Register Empty Interrupt Level bit 0 position. */
#define USART_DREINTLVL1_bm  (1<<1)  /* Data Register Empty Interrupt Level bit 1 mask. */
#define USART_DREINTLVL1_bp  1  /* Data Register Empty Interrupt Level bit 1 position. */
#define USART_TXCINTLVL_gm  0x0C  /* Transmit Interrupt Level group mask. */
#define USART_TXCINTLVL_gp  2  /* Transmit Interrupt Level group position. */
#define USART_TXCINTLVL0_bm  (1<<2)  /* Transmit Interrupt Level bit 0 mask. */
#define USART_TXCINTLVL0_bp  2  /* Transmit Interrupt Level bit 0 position. */
#define USART_TXCINTLVL1_bm  (1<<3)  /* Transmit Interrupt Level bit 1 mask. */
#define USART_TXCINTLVL1_bp  3  /* Transmit Interrupt Level bit 1 position. */
#define USART_RXCINTLVL_gm  0x30  /* Receive Interrupt Level group mask. */
#define USART_RXCINTLVL_gp  4  /* Receive Interrupt Level group position. */
#define USART_RXCINTLVL0_bm  (1<<4)  /* Receive Interrupt Level bit 0 mask. */
#define USART_RXCINTLVL0_bp  4  /* Receive Interrupt Level bit 0 position. */
#define USART_RXCINTLVL1_bm  (1<<5)  /* Receive Interrupt Level bit 1 mask. */
#define USART_RXCINTLVL1_bp  5  /* Receive Interrupt Level bit 1 position. */

/* USART.CTRLB  bit masks and bit positions */
#define USART_TXB8_bm  0x01  /* Transmit bit 8 bit mask. */
#define USART_TXB8_bp  0  /* Transmit bit 8 bit position. */
#define USART_MPCM_bm  0x02  /* Multi-processor Communication Mode bit mask. */
#define USART_MPCM_bp  1  /* Multi-processor Communication Mode bit position. */
#define USART_CLK2X_bm  0x04  /* Double transmission speed bit mask. */
#define USART_CLK2X_bp  2  /* Double transmission speed bit position. */
#define USART_TXEN_bm  0x08  /* Transmitter Enable bit mask. */
#define USART_TXEN_bp  3  /* Transmitter Enable bit position. */
#define USART_RXEN_bm  0x10  /* Receiver Enable bit mask. */
#define USART_RXEN_bp  4  /* Receiver Enable bit position. */

/* USART.CTRLC  bit masks and bit positions */
#define USART_CHSIZE_gm  0x07  /* Character Size group mask. */
#define USART_CHSIZE_gp  0  /* Character Size group position. */
#define USART_CHSIZE0_bm  (1<<0)  /* Character Size bit 0 mask. */
#define USART_CHSIZE0_bp  0  /* Character Size bit 0 position. */
#define USART_CHSIZE1_bm  (1<<1)  /* Character Size bit 1 mask. */
#define USART_CHSIZE1_bp  1  /* Character Size bit 1 position. */
#define USART_CHSIZE2_bm  (1<<2)  /* Character Size bit 2 mask. */
#define USART_CHSIZE2_bp  2  /* Character Size bit 2 position. */
#define USART_SBMODE_bm  0x08  /* Stop Bit Mode bit mask. */
#define USART_SBMODE_bp  3  /* Stop Bit Mode bit position. */
#define USART_PMODE_gm  0x30  /* Parity Mode group mask. */
#define USART_PMODE_gp  4  /* Parity Mode group position. */
#define USART_PMODE0_bm  (1<<4)  /* Parity Mode bit 0 mask. */
#define USART_PMODE0_bp  4  /* Parity Mode bit 0 position. */
#define USART_PMODE1_bm  (1<<5)  /* Parity Mode bit 1 mask. */
#define USART_PMODE1_bp  5  /* Parity Mode bit 1 position. */
#define USART_CMODE_gm  0xC0  /* Communication Mode group mask. */
#define USART_CMODE_gp  6  /* Communication Mode group position. */
#define USART_CMODE0_bm  (1<<6)  /* Communication Mode bit 0 mask. */
#define USART_CMODE0_bp  6  /* Communication Mode bit 0 position. */
#define USART_CMODE1_bm  (1<<7)  /* Communication Mode bit 1 mask. */
#define USART_CMODE1_bp  7  /* Communication Mode bit 1 position. */

/* USART.BAUDCTRLA  bit masks and bit positions */
#define USART_BSEL_gm  0xFF  /* Baud Rate Selection Bits [7:0] group mask. */
#define USART_BSEL_gp  0  /* Baud Rate Selection Bits [7:0] group position. */
#define USART_BSEL0_bm  (1<<0)  /* Baud Rate Selection Bits [7:0] bit 0 mask. */
#define USART_BSEL0_bp  0  /* Baud Rate Selection Bits [7:0] bit 0 position. */
#define USART_BSEL1_bm  (1<<1)  /* Baud Rate Selection Bits [7:0] bit 1 mask. */
#define USART_BSEL1_bp  1  /* Baud Rate Selection Bits [7:0] bit 1 position. */
#define USART_BSEL2_bm  (1<<2)  /* Baud Rate Selection Bits [7:0] bit 2 mask. */
#define USART_BSEL2_bp  2  /* Baud Rate Selection Bits [7:0] bit 2 position. */
#define USART_BSEL3_bm  (1<<3)  /* Baud Rate Selection Bits [7:0] bit 3 mask. */
#define USART_BSEL3_bp  3  /* Baud Rate Selection Bits [7:0] bit 3 position. */
#define USART_BSEL4_bm  (1<<4)  /* Baud Rate Selection Bits [7:0] bit 4 mask. */
#define USART_BSEL4_bp  4  /* Baud Rate Selection Bits [7:0] bit 4 position. */
#define USART_BSEL5_bm  (1<<5)  /* Baud Rate Selection Bits [7:0] bit 5 mask. */
#define USART_BSEL5_bp  5  /* Baud Rate Selection Bits [7:0] bit 5 position. */
#define USART_BSEL6_bm  (1<<6)  /* Baud Rate Selection Bits [7:0] bit 6 mask. */
#define USART_BSEL6_bp  6  /* Baud Rate Selection Bits [7:0] bit 6 position. */
#define USART_BSEL7_bm  (1<<7)  /* Baud Rate Selection Bits [7:0] bit 7 mask. */
#define USART_BSEL7_bp  7  /* Baud Rate Selection Bits [7:0] bit 7 position. */

/* USART.BAUDCTRLB  bit masks and bit positions */
/* USART_BSEL  is already defined. */
#define USART_BSCALE_gm  0xF0  /* Baud Rate Scale group mask. */
#define USART_BSCALE_gp  4  /* Baud Rate Scale group position. */
#define USART_BSCALE0_bm  (1<<4)  /* Baud Rate Scale bit 0 mask. */
#define USART_BSCALE0_bp  4  /* Baud Rate Scale bit 0 position. */
#define USART_BSCALE1_bm  (1<<5)  /* Baud Rate Scale bit 1 mask. */
#define USART_BSCALE1_bp  5  /* Baud Rate Scale bit 1 position. */
#define USART_BSCALE2_bm  (1<<6)  /* Baud Rate Scale bit 2 mask. */
#define USART_BSCALE2_bp  6  /* Baud Rate Scale bit 2 position. */
#define USART_BSCALE3_bm  (1<<7)  /* Baud Rate Scale bit 3 mask. */
#define USART_BSCALE3_bp  7  /* Baud Rate Scale bit 3 position. */

/* USB - USB */
/* USB_EP.STATUS  bit masks and bit positions */
#define USB_EP_TOGGLE_bm  0x01  /* Data Toggle bit mask. */
#define USB_EP_TOGGLE_bp  0  /* Data Toggle bit position. */
#define USB_EP_BUSNACK0_bm  0x02  /* Data Buffer 0 Not Acknowledge bit mask. */
#define USB_EP_BUSNACK0_bp  1  /* Data Buffer 0 Not Acknowledge bit position. */
#define USB_EP_BUSNACK1_bm  0x04  /* Data Buffer 1 Not Acknowledge bit mask. */
#define USB_EP_BUSNACK1_bp  2  /* Data Buffer 1 Not Acknowledge bit position. */
#define USB_EP_BANK_bm  0x08  /* Bank Select bit mask. */
#define USB_EP_BANK_bp  3  /* Bank Select bit position. */
#define USB_EP_TRNCOMPL1_bm  0x10  /* Transaction Complete 1 Flag bit mask. */
#define USB_EP_TRNCOMPL1_bp  4  /* Transaction Complete 1 Flag bit position. */
#define USB_EP_SETUP_bm  0x10  /* SETUP Transaction Complete Flag bit mask. */
#define USB_EP_SETUP_bp  4  /* SETUP Transaction Complete Flag bit position. */
#define USB_EP_TRNCOMPL0_bm  0x20  /* Transaction Complete 0 Flag bit mask. */
#define USB_EP_TRNCOMPL0_bp  5  /* Transaction Complete 0 Flag bit position. */
#define USB_EP_UNF_bm  0x40  /* Underflow Enpoint FLag bit mask. */
#define USB_EP_UNF_bp  6  /* Underflow Enpoint FLag bit position. */
#define USB_EP_OVF_bm  0x40  /* Overflow Enpoint Flag for Output Endpoints bit mask. */
#define USB_EP_OVF_bp  6  /* Overflow Enpoint Flag for Output Endpoints bit position. */
#define USB_EP_STALLF_bm  0x80  /* Endpoint Stall Flag bit mask. */
#define USB_EP_STALLF_bp  7  /* Endpoint Stall Flag bit position. */
#define USB_EP_CRC_bm  0x80  /* CRC Error Flag bit mask. */
#define USB_EP_CRC_bp  7  /* CRC Error Flag bit position. */

/* USB_EP.CTRL  bit masks and bit positions */
#define USB_EP_STALL_bm  0x04  /* Data Stall bit mask. */
#define USB_EP_STALL_bp  2  /* Data Stall bit position. */
#define USB_EP_BUFSIZE_gm  0x07  /* Data Buffer Size group mask. */
#define USB_EP_BUFSIZE_gp  0  /* Data Buffer Size group position. */
#define USB_EP_BUFSIZE0_bm  (1<<0)  /* Data Buffer Size bit 0 mask. */
#define USB_EP_BUFSIZE0_bp  0  /* Data Buffer Size bit 0 position. */
#define USB_EP_BUFSIZE1_bm  (1<<1)  /* Data Buffer Size bit 1 mask. */
#define USB_EP_BUFSIZE1_bp  1  /* Data Buffer Size bit 1 position. */
#define USB_EP_BUFSIZE2_bm  (1<<2)  /* Data Buffer Size bit 2 mask. */
#define USB_EP_BUFSIZE2_bp  2  /* Data Buffer Size bit 2 position. */
#define USB_EP_INTDSBL_bm  0x08  /* Interrupt Disable bit mask. */
#define USB_EP_INTDSBL_bp  3  /* Interrupt Disable bit position. */
#define USB_EP_PINGPONG_bm  0x10  /* Ping-Pong Enable bit mask. */
#define USB_EP_PINGPONG_bp  4  /* Ping-Pong Enable bit position. */
#define USB_EP_MULTIPKT_bm  0x20  /* Multi Packet Transfer Enable bit mask. */
#define USB_EP_MULTIPKT_bp  5  /* Multi Packet Transfer Enable bit position. */
#define USB_EP_TYPE_gm  0xC0  /* Endpoint Type group mask. */
#define USB_EP_TYPE_gp  6  /* Endpoint Type group position. */
#define USB_EP_TYPE0_bm  (1<<6)  /* Endpoint Type bit 0 mask. */
#define USB_EP_TYPE0_bp  6  /* Endpoint Type bit 0 position. */
#define USB_EP_TYPE1_bm  (1<<7)  /* Endpoint Type bit 1 mask. */
#define USB_EP_TYPE1_bp  7  /* Endpoint Type bit 1 position. */

/* USB_EP.CNT  bit masks and bit positions */
#define USB_EP_ZLP_bm  0x8000  /* Zero Length Packet bit mask. */
#define USB_EP_ZLP_bp  15  /* Zero Length Packet bit position. */



/* USB.CTRLA  bit masks and bit positions */
#define USB_MAXEP_gm  0x0F  /* Maximum Endpoint Addresses group mask. */
#define USB_MAXEP_gp  0  /* Maximum Endpoint Addresses group position. */
#define USB_MAXEP0_bm  (1<<0)  /* Maximum Endpoint Addresses bit 0 mask. */
#define USB_MAXEP0_bp  0  /* Maximum Endpoint Addresses bit 0 position. */
#define USB_MAXEP1_bm  (1<<1)  /* Maximum Endpoint Addresses bit 1 mask. */
#define USB_MAXEP1_bp  1  /* Maximum Endpoint Addresses bit 1 position. */
#define USB_MAXEP2_bm  (1<<2)  /* Maximum Endpoint Addresses bit 2 mask. */
#define USB_MAXEP2_bp  2  /* Maximum Endpoint Addresses bit 2 position. */
#define USB_MAXEP3_bm  (1<<3)  /* Maximum Endpoint Addresses bit 3 mask. */
#define USB_MAXEP3_bp  3  /* Maximum Endpoint Addresses bit 3 position. */
#define USB_STFRNUM_bm  0x10  /* Store Frame Number Enable bit mask. */
#define USB_STFRNUM_bp  4  /* Store Frame Number Enable bit position. */
#define USB_FIFOEN_bm  0x20  /* USB FIFO Enable bit mask. */
#define USB_FIFOEN_bp  5  /* USB FIFO Enable bit position. */
#define USB_SPEED_bm  0x40  /* Speed Select bit mask. */
#define USB_SPEED_bp  6  /* Speed Select bit position. */
#define USB_ENABLE_bm  0x80  /* USB Enable bit mask. */
#define USB_ENABLE_bp  7  /* USB Enable bit position. */

/* USB.CTRLB  bit masks and bit positions */
#define USB_ATTACH_bm  0x01  /* Attach bit mask. */
#define USB_ATTACH_bp  0  /* Attach bit position. */
#define USB_GNACK_bm  0x02  /* Global NACK bit mask. */
#define USB_GNACK_bp  1  /* Global NACK bit position. */
#define USB_RWAKEUP_bm  0x04  /* Remote Wake-up bit mask. */
#define USB_RWAKEUP_bp  2  /* Remote Wake-up bit position. */
#define USB_PULLRST_bm  0x10  /* Pull during Reset bit mask. */
#define USB_PULLRST_bp  4  /* Pull during Reset bit position. */

/* USB.STATUS  bit masks and bit positions */
#define USB_BUSRST_bm  0x01  /* Bus Reset bit mask. */
#define USB_BUSRST_bp  0  /* Bus Reset bit position. */
#define USB_SUSPEND_bm  0x02  /* Bus Suspended bit mask. */
#define USB_SUSPEND_bp  1  /* Bus Suspended bit position. */
#define USB_RESUME_bm  0x04  /* Resume bit mask. */
#define USB_RESUME_bp  2  /* Resume bit position. */
#define USB_URESUME_bm  0x08  /* Upstream Resume bit mask. */
#define USB_URESUME_bp  3  /* Upstream Resume bit position. */

/* USB.ADDR  bit masks and bit positions */
#define USB_ADDR_gm  0x7F  /* Device Address group mask. */
#define USB_ADDR_gp  0  /* Device Address group position. */
#define USB_ADDR0_bm  (1<<0)  /* Device Address bit 0 mask. */
#define USB_ADDR0_bp  0  /* Device Address bit 0 position. */
#define USB_ADDR1_bm  (1<<1)  /* Device Address bit 1 mask. */
#define USB_ADDR1_bp  1  /* Device Address bit 1 position. */
#define USB_ADDR2_bm  (1<<2)  /* Device Address bit 2 mask. */
#define USB_ADDR2_bp  2  /* Device Address bit 2 position. */
#define USB_ADDR3_bm  (1<<3)  /* Device Address bit 3 mask. */
#define USB_ADDR3_bp  3  /* Device Address bit 3 position. */
#define USB_ADDR4_bm  (1<<4)  /* Device Address bit 4 mask. */
#define USB_ADDR4_bp  4  /* Device Address bit 4 position. */
#define USB_ADDR5_bm  (1<<5)  /* Device Address bit 5 mask. */
#define USB_ADDR5_bp  5  /* Device Address bit 5 position. */
#define USB_ADDR6_bm  (1<<6)  /* Device Address bit 6 mask. */
#define USB_ADDR6_bp  6  /* Device Address bit 6 position. */

/* USB.FIFOWP  bit masks and bit positions */
#define USB_FIFOWP_gm  0x1F  /* FIFO Write Pointer group mask. */
#define USB_FIFOWP_gp  0  /* FIFO Write Pointer group position. */
#define USB_FIFOWP0_bm  (1<<0)  /* FIFO Write Pointer bit 0 mask. */
#define USB_FIFOWP0_bp  0  /* FIFO Write Pointer bit 0 position. */
#define USB_FIFOWP1_bm  (1<<1)  /* FIFO Write Pointer bit 1 mask. */
#define USB_FIFOWP1_bp  1  /* FIFO Write Pointer bit 1 position. */
#define USB_FIFOWP2_bm  (1<<2)  /* FIFO Write Pointer bit 2 mask. */
#define USB_FIFOWP2_bp  2  /* FIFO Write Pointer bit 2 position. */
#define USB_FIFOWP3_bm  (1<<3)  /* FIFO Write Pointer bit 3 mask. */
#define USB_FIFOWP3_bp  3  /* FIFO Write Pointer bit 3 position. */
#define USB_FIFOWP4_bm  (1<<4)  /* FIFO Write Pointer bit 4 mask. */
#define USB_FIFOWP4_bp  4  /* FIFO Write Pointer bit 4 position. */

/* USB.FIFORP  bit masks and bit positions */
#define USB_FIFORP_gm  0x1F  /* FIFO Read Pointer group mask. */
#define USB_FIFORP_gp  0  /* FIFO Read Pointer group position. */
#define USB_FIFORP0_bm  (1<<0)  /* FIFO Read Pointer bit 0 mask. */
#define USB_FIFORP0_bp  0  /* FIFO Read Pointer bit 0 position. */
#define USB_FIFORP1_bm  (1<<1)  /* FIFO Read Pointer bit 1 mask. */
#define USB_FIFORP1_bp  1  /* FIFO Read Pointer bit 1 position. */
#define USB_FIFORP2_bm  (1<<2)  /* FIFO Read Pointer bit 2 mask. */
#define USB_FIFORP2_bp  2  /* FIFO Read Pointer bit 2 position. */
#define USB_FIFORP3_bm  (1<<3)  /* FIFO Read Pointer bit 3 mask. */
#define USB_FIFORP3_bp  3  /* FIFO Read Pointer bit 3 position. */
#define USB_FIFORP4_bm  (1<<4)  /* FIFO Read Pointer bit 4 mask. */
#define USB_FIFORP4_bp  4  /* FIFO Read Pointer bit 4 position. */


/* USB.INTCTRLA  bit masks and bit positions */
#define USB_INTLVL_gm  0x03  /* Interrupt Level group mask. */
#define USB_INTLVL_gp  0  /* Interrupt Level group position. */
#define USB_INTLVL0_bm  (1<<0)  /* Interrupt Level bit 0 mask. */
#define USB_INTLVL0_bp  0  /* Interrupt Level bit 0 position. */
#define USB_INTLVL1_bm  (1<<1)  /* Interrupt Level bit 1 mask. */
#define USB_INTLVL1_bp  1  /* Interrupt Level bit 1 position. */
#define USB_STALLIE_bm  0x10  /* STALL Interrupt Enable bit mask. */
#define USB_STALLIE_bp  4  /* STALL Interrupt Enable bit position. */
#define USB_BUSERRIE_bm  0x20  /* Bus Error Interrupt Enable bit mask. */
#define USB_BUSERRIE_bp  5  /* Bus Error Interrupt Enable bit position. */
#define USB_BUSEVIE_bm  0x40  /* Bus Event Interrupt Enable bit mask. */
#define USB_BUSEVIE_bp  6  /* Bus Event Interrupt Enable bit position. */
#define USB_SOFIE_bm  0x80  /* Start Of Frame Interrupt Enable bit mask. */
#define USB_SOFIE_bp  7  /* Start Of Frame Interrupt Enable bit position. */

/* USB.INTCTRLB  bit masks and bit positions */
#define USB_SETUPIE_bm  0x01  /* SETUP Transaction Complete Interrupt Enable bit mask. */
#define USB_SETUPIE_bp  0  /* SETUP Transaction Complete Interrupt Enable bit position. */
#define USB_TRNIE_bm  0x02  /* Transaction Complete Interrupt Enable bit mask. */
#define USB_TRNIE_bp  1  /* Transaction Complete Interrupt Enable bit position. */

/* USB.INTFLAGSACLR  bit masks and bit positions */
#define USB_STALLIF_bm  0x01  /* STALL Interrupt Flag bit mask. */
#define USB_STALLIF_bp  0  /* STALL Interrupt Flag bit position. */
#define USB_OVFIF_bm  0x02  /* Overflow Interrupt Flag bit mask. */
#define USB_OVFIF_bp  1  /* Overflow Interrupt Flag bit position. */
#define USB_UNFIF_bm  0x04  /* Underflow Interrupt Flag bit mask. */
#define USB_UNFIF_bp  2  /* Underflow Interrupt Flag bit position. */
#define USB_CRCIF_bm  0x08  /* Isochronous CRC Error Interrupt Flag bit mask. */
#define USB_CRCIF_bp  3  /* Isochronous CRC Error Interrupt Flag bit position. */
#define USB_RSTIF_bm  0x10  /* Reset Interrupt Flag bit mask. */
#define USB_RSTIF_bp  4  /* Reset Interrupt Flag bit position. */
#define USB_RESUMEIF_bm  0x20  /* Resume Interrupt Flag bit mask. */
#define USB_RESUMEIF_bp  5  /* Resume Interrupt Flag bit position. */
#define USB_SUSPENDIF_bm  0x40  /* Suspend Interrupt Flag bit mask. */
#define USB_SUSPENDIF_bp  6  /* Suspend Interrupt Flag bit position. */
#define USB_SOFIF_bm  0x80  /* Start Of Frame Interrupt Flag bit mask. */
#define USB_SOFIF_bp  7  /* Start Of Frame Interrupt Flag bit position. */

/* USB.INTFLAGSASET  bit masks and bit positions */
/* USB_STALLIF  is already defined. */
/* USB_OVFIF  is already defined. */
/* USB_UNFIF  is already defined. */
/* USB_CRCIF  is already defined. */
/* USB_RSTIF  is already defined. */
/* USB_RESUMEIF  is already defined. */
/* USB_SUSPENDIF  is already defined. */
/* USB_SOFIF  is already defined. */

/* USB.INTFLAGSBCLR  bit masks and bit positions */
#define USB_SETUPIF_bm  0x01  /* SETUP Transaction Complete Interrupt Flag bit mask. */
#define USB_SETUPIF_bp  0  /* SETUP Transaction Complete Interrupt Flag bit position. */
#define USB_TRNIF_bm  0x02  /* Transaction Complete Interrupt Flag bit mask. */
#define USB_TRNIF_bp  1  /* Transaction Complete Interrupt Flag bit position. */

/* USB.INTFLAGSBSET  bit masks and bit positions */
/* USB_SETUPIF  is already defined. */
/* USB_TRNIF  is already defined. */








/* VPORT - Virtual Ports */
/* VPORT.INTFLAGS  bit masks and bit positions */
#define VPORT_INT0IF_bm  0x01  /* Port Interrupt 0 Flag bit mask. */
#define VPORT_INT0IF_bp  0  /* Port Interrupt 0 Flag bit position. */
#define VPORT_INT1IF_bm  0x02  /* Port Interrupt 1 Flag bit mask. */
#define VPORT_INT1IF_bp  1  /* Port Interrupt 1 Flag bit position. */

/* WDT - Watch-Dog Timer */
/* WDT.CTRL  bit masks and bit positions */
#define WDT_CEN_bm  0x01  /* Change Enable bit mask. */
#define WDT_CEN_bp  0  /* Change Enable bit position. */
#define WDT_ENABLE_bm  0x02  /* Enable bit mask. */
#define WDT_ENABLE_bp  1  /* Enable bit position. */
#define WDT_PER_gm  0x3C  /* Period group mask. */
#define WDT_PER_gp  2  /* Period group position. */
#define WDT_PER0_bm  (1<<2)  /* Period bit 0 mask. */
#define WDT_PER0_bp  2  /* Period bit 0 position. */
#define WDT_PER1_bm  (1<<3)  /* Period bit 1 mask. */
#define WDT_PER1_bp  3  /* Period bit 1 position. */
#define WDT_PER2_bm  (1<<4)  /* Period bit 2 mask. */
#define WDT_PER2_bp  4  /* Period bit 2 position. */
#define WDT_PER3_bm  (1<<5)  /* Period bit 3 mask. */
#define WDT_PER3_bp  5  /* Period bit 3 position. */

/* WDT.WINCTRL  bit masks and bit positions */
#define WDT_WCEN_bm  0x01  /* Windowed Mode Change Enable bit mask. */
#define WDT_WCEN_bp  0  /* Windowed Mode Change Enable bit position. */
#define WDT_WEN_bm  0x02  /* Windowed Mode Enable bit mask. */
#define WDT_WEN_bp  1  /* Windowed Mode Enable bit position. */
#define WDT_WPER_gm  0x3C  /* Windowed Mode Period group mask. */
#define WDT_WPER_gp  2  /* Windowed Mode Period group position. */
#define WDT_WPER0_bm  (1<<2)  /* Windowed Mode Period bit 0 mask. */
#define WDT_WPER0_bp  2  /* Windowed Mode Period bit 0 position. */
#define WDT_WPER1_bm  (1<<3)  /* Windowed Mode Period bit 1 mask. */
#define WDT_WPER1_bp  3  /* Windowed Mode Period bit 1 position. */
#define WDT_WPER2_bm  (1<<4)  /* Windowed Mode Period bit 2 mask. */
#define WDT_WPER2_bp  4  /* Windowed Mode Period bit 2 position. */
#define WDT_WPER3_bm  (1<<5)  /* Windowed Mode Period bit 3 mask. */
#define WDT_WPER3_bp  5  /* Windowed Mode Period bit 3 position. */

/* WDT.STATUS  bit masks and bit positions */
#define WDT_SYNCBUSY_bm  0x01  /* Syncronization busy bit mask. */
#define WDT_SYNCBUSY_bp  0  /* Syncronization busy bit position. */

/* XOCD - On-Chip Debug System */
/* OCD.OCDR0  bit masks and bit positions */
#define OCD_OCDRD_gm  0xFF  /* OCDR Dirty group mask. */
#define OCD_OCDRD_gp  0  /* OCDR Dirty group position. */
#define OCD_OCDRD0_bm  (1<<0)  /* OCDR Dirty bit 0 mask. */
#define OCD_OCDRD0_bp  0  /* OCDR Dirty bit 0 position. */
#define OCD_OCDRD1_bm  (1<<1)  /* OCDR Dirty bit 1 mask. */
#define OCD_OCDRD1_bp  1  /* OCDR Dirty bit 1 position. */
#define OCD_OCDRD2_bm  (1<<2)  /* OCDR Dirty bit 2 mask. */
#define OCD_OCDRD2_bp  2  /* OCDR Dirty bit 2 position. */
#define OCD_OCDRD3_bm  (1<<3)  /* OCDR Dirty bit 3 mask. */
#define OCD_OCDRD3_bp  3  /* OCDR Dirty bit 3 position. */
#define OCD_OCDRD4_bm  (1<<4)  /* OCDR Dirty bit 4 mask. */
#define OCD_OCDRD4_bp  4  /* OCDR Dirty bit 4 position. */
#define OCD_OCDRD5_bm  (1<<5)  /* OCDR Dirty bit 5 mask. */
#define OCD_OCDRD5_bp  5  /* OCDR Dirty bit 5 position. */
#define OCD_OCDRD6_bm  (1<<6)  /* OCDR Dirty bit 6 mask. */
#define OCD_OCDRD6_bp  6  /* OCDR Dirty bit 6 position. */
#define OCD_OCDRD7_bm  (1<<7)  /* OCDR Dirty bit 7 mask. */
#define OCD_OCDRD7_bp  7  /* OCDR Dirty bit 7 position. */

/* OCD.OCDR1  bit masks and bit positions */
/* OCD_OCDRD  is already defined. */



// Generic Port Pins

#define PIN0_bm 0x01
#define PIN0_bp 0
#define PIN1_bm 0x02
#define PIN1_bp 1
#define PIN2_bm 0x04
#define PIN2_bp 2
#define PIN3_bm 0x08
#define PIN3_bp 3
#define PIN4_bm 0x10
#define PIN4_bp 4
#define PIN5_bm 0x20
#define PIN5_bp 5
#define PIN6_bm 0x40
#define PIN6_bp 6
#define PIN7_bm 0x80
#define PIN7_bp 7

/* ========== Interrupt Vector Definitions ========== */
/* Vector 0 is the reset vector */

/* OSC interrupt vectors */
#define OSC_OSCF_vect_num  1
#define OSC_OSCF_vect      _VECTOR(1)  /* Oscillator Failure Interrupt (NMI) */

/* PORTC interrupt vectors */
#define PORTC_INT0_vect_num  2
#define PORTC_INT0_vect      _VECTOR(2)  /* External Interrupt 0 */
#define PORTC_INT1_vect_num  3
#define PORTC_INT1_vect      _VECTOR(3)  /* External Interrupt 1 */

/* PORTR interrupt vectors */
#define PORTR_INT0_vect_num  4
#define PORTR_INT0_vect      _VECTOR(4)  /* External Interrupt 0 */
#define PORTR_INT1_vect_num  5
#define PORTR_INT1_vect      _VECTOR(5)  /* External Interrupt 1 */

/* DMA interrupt vectors */
#define DMA_CH0_vect_num  6
#define DMA_CH0_vect      _VECTOR(6)  /* Channel 0 Interrupt */
#define DMA_CH1_vect_num  7
#define DMA_CH1_vect      _VECTOR(7)  /* Channel 1 Interrupt */

/* RTC interrupt vectors */
#define RTC_OVF_vect_num  10
#define RTC_OVF_vect      _VECTOR(10)  /* Overflow Interrupt */
#define RTC_COMP_vect_num  11
#define RTC_COMP_vect      _VECTOR(11)  /* Compare Interrupt */

/* TWIC interrupt vectors */
#define TWIC_TWIS_vect_num  12
#define TWIC_TWIS_vect      _VECTOR(12)  /* TWI Slave Interrupt */
#define TWIC_TWIM_vect_num  13
#define TWIC_TWIM_vect      _VECTOR(13)  /* TWI Master Interrupt */

/* TCC0 interrupt vectors */
#define TCC0_OVF_vect_num  14
#define TCC0_OVF_vect      _VECTOR(14)  /* Overflow Interrupt */

/* TCC2 interrupt vectors */
#define TCC2_LUNF_vect_num  14
#define TCC2_LUNF_vect      _VECTOR(14)  /* Low Byte Underflow Interrupt */

/* TCC0 interrupt vectors */
#define TCC0_ERR_vect_num  15
#define TCC0_ERR_vect      _VECTOR(15)  /* Error Interrupt */

/* TCC2 interrupt vectors */
#define TCC2_HUNF_vect_num  15
#define TCC2_HUNF_vect      _VECTOR(15)  /* High Byte Underflow Interrupt */

/* TCC0 interrupt vectors */
#define TCC0_CCA_vect_num  16
#define TCC0_CCA_vect      _VECTOR(16)  /* Compare or Capture A Interrupt */

/* TCC2 interrupt vectors */
#define TCC2_LCMPA_vect_num  16
#define TCC2_LCMPA_vect      _VECTOR(16)  /* Low Byte Compare A Interrupt */

/* TCC0 interrupt vectors */
#define TCC0_CCB_vect_num  17
#define TCC0_CCB_vect      _VECTOR(17)  /* Compare or Capture B Interrupt */

/* TCC2 interrupt vectors */
#define TCC2_LCMPB_vect_num  17
#define TCC2_LCMPB_vect      _VECTOR(17)  /* Low Byte Compare B Interrupt */

/* TCC0 interrupt vectors */
#define TCC0_CCC_vect_num  18
#define TCC0_CCC_vect      _VECTOR(18)  /* Compare or Capture C Interrupt */

/* TCC2 interrupt vectors */
#define TCC2_LCMPC_vect_num  18
#define TCC2_LCMPC_vect      _VECTOR(18)  /* Low Byte Compare C Interrupt */

/* TCC0 interrupt vectors */
#define TCC0_CCD_vect_num  19
#define TCC0_CCD_vect      _VECTOR(19)  /* Compare or Capture D Interrupt */

/* TCC2 interrupt vectors */
#define TCC2_LCMPD_vect_num  19
#define TCC2_LCMPD_vect      _VECTOR(19)  /* Low Byte Compare D Interrupt */

/* TCC1 interrupt vectors */
#define TCC1_OVF_vect_num  20
#define TCC1_OVF_vect      _VECTOR(20)  /* Overflow Interrupt */
#define TCC1_ERR_vect_num  21
#define TCC1_ERR_vect      _VECTOR(21)  /* Error Interrupt */
#define TCC1_CCA_vect_num  22
#define TCC1_CCA_vect      _VECTOR(22)  /* Compare or Capture A Interrupt */
#define TCC1_CCB_vect_num  23
#define TCC1_CCB_vect      _VECTOR(23)  /* Compare or Capture B Interrupt */

/* SPIC interrupt vectors */
#define SPIC_INT_vect_num  24
#define SPIC_INT_vect      _VECTOR(24)  /* SPI Interrupt */

/* USARTC0 interrupt vectors */
#define USARTC0_RXC_vect_num  25
#define USARTC0_RXC_vect      _VECTOR(25)  /* Reception Complete Interrupt */
#define USARTC0_DRE_vect_num  26
#define USARTC0_DRE_vect      _VECTOR(26)  /* Data Register Empty Interrupt */
#define USARTC0_TXC_vect_num  27
#define USARTC0_TXC_vect      _VECTOR(27)  /* Transmission Complete Interrupt */

/* USB interrupt vectors */
#define USB_BUSEVENT_vect_num  31
#define USB_BUSEVENT_vect      _VECTOR(31)  /* SOF, suspend, resume, reset bus event interrupts, crc, underflow, overflow and stall error interrupts */
#define USB_TRNCOMPL_vect_num  32
#define USB_TRNCOMPL_vect      _VECTOR(32)  /* Transaction complete interrupt */

/* LCD interrupt vectors */
#define LCD_INT_vect_num  35
#define LCD_INT_vect      _VECTOR(35)  /* LCD Interrupt */

/* AES interrupt vectors */
#define AES_INT_vect_num  36
#define AES_INT_vect      _VECTOR(36)  /* AES Interrupt */

/* NVM interrupt vectors */
#define NVM_EE_vect_num  37
#define NVM_EE_vect      _VECTOR(37)  /* EE Interrupt */
#define NVM_SPM_vect_num  38
#define NVM_SPM_vect      _VECTOR(38)  /* SPM Interrupt */

/* PORTB interrupt vectors */
#define PORTB_INT0_vect_num  39
#define PORTB_INT0_vect      _VECTOR(39)  /* External Interrupt 0 */
#define PORTB_INT1_vect_num  40
#define PORTB_INT1_vect      _VECTOR(40)  /* External Interrupt 1 */

/* ACB interrupt vectors */
#define ACB_AC0_vect_num  41
#define ACB_AC0_vect      _VECTOR(41)  /* AC0 Interrupt */
#define ACB_AC1_vect_num  42
#define ACB_AC1_vect      _VECTOR(42)  /* AC1 Interrupt */
#define ACB_ACW_vect_num  43
#define ACB_ACW_vect      _VECTOR(43)  /* ACW Window Mode Interrupt */

/* ADCB interrupt vectors */
#define ADCB_CH0_vect_num  44
#define ADCB_CH0_vect      _VECTOR(44)  /* Interrupt 0 */

/* PORTD interrupt vectors */
#define PORTD_INT0_vect_num  48
#define PORTD_INT0_vect      _VECTOR(48)  /* External Interrupt 0 */
#define PORTD_INT1_vect_num  49
#define PORTD_INT1_vect      _VECTOR(49)  /* External Interrupt 1 */

/* PORTG interrupt vectors */
#define PORTG_INT0_vect_num  50
#define PORTG_INT0_vect      _VECTOR(50)  /* External Interrupt 0 */
#define PORTG_INT1_vect_num  51
#define PORTG_INT1_vect      _VECTOR(51)  /* External Interrupt 1 */

/* PORTM interrupt vectors */
#define PORTM_INT0_vect_num  52
#define PORTM_INT0_vect      _VECTOR(52)  /* External Interrupt 0 */
#define PORTM_INT1_vect_num  53
#define PORTM_INT1_vect      _VECTOR(53)  /* External Interrupt 1 */

/* PORTE interrupt vectors */
#define PORTE_INT0_vect_num  54
#define PORTE_INT0_vect      _VECTOR(54)  /* External Interrupt 0 */
#define PORTE_INT1_vect_num  55
#define PORTE_INT1_vect      _VECTOR(55)  /* External Interrupt 1 */

/* TCE0 interrupt vectors */
#define TCE0_OVF_vect_num  58
#define TCE0_OVF_vect      _VECTOR(58)  /* Overflow Interrupt */

/* TCE2 interrupt vectors */
#define TCE2_LUNF_vect_num  58
#define TCE2_LUNF_vect      _VECTOR(58)  /* Low Byte Underflow Interrupt */

/* TCE0 interrupt vectors */
#define TCE0_ERR_vect_num  59
#define TCE0_ERR_vect      _VECTOR(59)  /* Error Interrupt */

/* TCE2 interrupt vectors */
#define TCE2_HUNF_vect_num  59
#define TCE2_HUNF_vect      _VECTOR(59)  /* High Byte Underflow Interrupt */

/* TCE0 interrupt vectors */
#define TCE0_CCA_vect_num  60
#define TCE0_CCA_vect      _VECTOR(60)  /* Compare or Capture A Interrupt */

/* TCE2 interrupt vectors */
#define TCE2_LCMPA_vect_num  60
#define TCE2_LCMPA_vect      _VECTOR(60)  /* Low Byte Compare A Interrupt */

/* TCE0 interrupt vectors */
#define TCE0_CCB_vect_num  61
#define TCE0_CCB_vect      _VECTOR(61)  /* Compare or Capture B Interrupt */

/* TCE2 interrupt vectors */
#define TCE2_LCMPB_vect_num  61
#define TCE2_LCMPB_vect      _VECTOR(61)  /* Low Byte Compare B Interrupt */

/* TCE0 interrupt vectors */
#define TCE0_CCC_vect_num  62
#define TCE0_CCC_vect      _VECTOR(62)  /* Compare or Capture C Interrupt */

/* TCE2 interrupt vectors */
#define TCE2_LCMPC_vect_num  62
#define TCE2_LCMPC_vect      _VECTOR(62)  /* Low Byte Compare C Interrupt */

/* TCE0 interrupt vectors */
#define TCE0_CCD_vect_num  63
#define TCE0_CCD_vect      _VECTOR(63)  /* Compare or Capture D Interrupt */

/* TCE2 interrupt vectors */
#define TCE2_LCMPD_vect_num  63
#define TCE2_LCMPD_vect      _VECTOR(63)  /* Low Byte Compare D Interrupt */

/* USARTE0 interrupt vectors */
#define USARTE0_RXC_vect_num  69
#define USARTE0_RXC_vect      _VECTOR(69)  /* Reception Complete Interrupt */
#define USARTE0_DRE_vect_num  70
#define USARTE0_DRE_vect      _VECTOR(70)  /* Data Register Empty Interrupt */
#define USARTE0_TXC_vect_num  71
#define USARTE0_TXC_vect      _VECTOR(71)  /* Transmission Complete Interrupt */

/* PORTA interrupt vectors */
#define PORTA_INT0_vect_num  75
#define PORTA_INT0_vect      _VECTOR(75)  /* External Interrupt 0 */
#define PORTA_INT1_vect_num  76
#define PORTA_INT1_vect      _VECTOR(76)  /* External Interrupt 1 */

/* ACA interrupt vectors */
#define ACA_AC0_vect_num  77
#define ACA_AC0_vect      _VECTOR(77)  /* AC0 Interrupt */
#define ACA_AC1_vect_num  78
#define ACA_AC1_vect      _VECTOR(78)  /* AC1 Interrupt */
#define ACA_ACW_vect_num  79
#define ACA_ACW_vect      _VECTOR(79)  /* ACW Window Mode Interrupt */

/* ADCA interrupt vectors */
#define ADCA_CH0_vect_num  80
#define ADCA_CH0_vect      _VECTOR(80)  /* Interrupt 0 */

#define _VECTOR_SIZE 4 /* Size of individual vector. */
#define _VECTORS_SIZE (81 * _VECTOR_SIZE)


/* ========== Constants ========== */

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define PROGMEM_START     (0x0000)
#  define PROGMEM_SIZE      (69632)
#else
#  define PROGMEM_START     (0x0000U)
#  define PROGMEM_SIZE      (69632U)
#endif
#define PROGMEM_END       (PROGMEM_START + PROGMEM_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define APP_SECTION_START     (0x0000)
#  define APP_SECTION_SIZE      (65536)
#  define APP_SECTION_PAGE_SIZE (256)
#else
#  define APP_SECTION_START     (0x0000U)
#  define APP_SECTION_SIZE      (65536U)
#  define APP_SECTION_PAGE_SIZE (256U)
#endif
#define APP_SECTION_END       (APP_SECTION_START + APP_SECTION_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define APPTABLE_SECTION_START     (0xF000)
#  define APPTABLE_SECTION_SIZE      (4096)
#  define APPTABLE_SECTION_PAGE_SIZE (256)
#else
#  define APPTABLE_SECTION_START     (0xF000U)
#  define APPTABLE_SECTION_SIZE      (4096U)
#  define APPTABLE_SECTION_PAGE_SIZE (256U)
#endif
#define APPTABLE_SECTION_END       (APPTABLE_SECTION_START + APPTABLE_SECTION_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define BOOT_SECTION_START     (0x10000)
#  define BOOT_SECTION_SIZE      (4096)
#  define BOOT_SECTION_PAGE_SIZE (256)
#else
#  define BOOT_SECTION_START     (0x10000U)
#  define BOOT_SECTION_SIZE      (4096U)
#  define BOOT_SECTION_PAGE_SIZE (256U)
#endif
#define BOOT_SECTION_END       (BOOT_SECTION_START + BOOT_SECTION_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define DATAMEM_START     (0x0000)
#  define DATAMEM_SIZE      (12288)
#else
#  define DATAMEM_START     (0x0000U)
#  define DATAMEM_SIZE      (12288U)
#endif
#define DATAMEM_END       (DATAMEM_START + DATAMEM_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define IO_START     (0x0000)
#  define IO_SIZE      (4096)
#  define IO_PAGE_SIZE (0)
#else
#  define IO_START     (0x0000U)
#  define IO_SIZE      (4096U)
#  define IO_PAGE_SIZE (0U)
#endif
#define IO_END       (IO_START + IO_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define MAPPED_EEPROM_START     (0x1000)
#  define MAPPED_EEPROM_SIZE      (2048)
#  define MAPPED_EEPROM_PAGE_SIZE (0)
#else
#  define MAPPED_EEPROM_START     (0x1000U)
#  define MAPPED_EEPROM_SIZE      (2048U)
#  define MAPPED_EEPROM_PAGE_SIZE (0U)
#endif
#define MAPPED_EEPROM_END       (MAPPED_EEPROM_START + MAPPED_EEPROM_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define INTERNAL_SRAM_START     (0x2000)
#  define INTERNAL_SRAM_SIZE      (4096)
#  define INTERNAL_SRAM_PAGE_SIZE (0)
#else
#  define INTERNAL_SRAM_START     (0x2000U)
#  define INTERNAL_SRAM_SIZE      (4096U)
#  define INTERNAL_SRAM_PAGE_SIZE (0U)
#endif
#define INTERNAL_SRAM_END       (INTERNAL_SRAM_START + INTERNAL_SRAM_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define EEPROM_START     (0x0000)
#  define EEPROM_SIZE      (2048)
#  define EEPROM_PAGE_SIZE (32)
#else
#  define EEPROM_START     (0x0000U)
#  define EEPROM_SIZE      (2048U)
#  define EEPROM_PAGE_SIZE (32U)
#endif
#define EEPROM_END       (EEPROM_START + EEPROM_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define SIGNATURES_START     (0x0000)
#  define SIGNATURES_SIZE      (3)
#  define SIGNATURES_PAGE_SIZE (0)
#else
#  define SIGNATURES_START     (0x0000U)
#  define SIGNATURES_SIZE      (3U)
#  define SIGNATURES_PAGE_SIZE (0U)
#endif
#define SIGNATURES_END       (SIGNATURES_START + SIGNATURES_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define FUSES_START     (0x0000)
#  define FUSES_SIZE      (6)
#  define FUSES_PAGE_SIZE (0)
#else
#  define FUSES_START     (0x0000U)
#  define FUSES_SIZE      (6U)
#  define FUSES_PAGE_SIZE (0U)
#endif
#define FUSES_END       (FUSES_START + FUSES_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define LOCKBITS_START     (0x0000)
#  define LOCKBITS_SIZE      (1)
#  define LOCKBITS_PAGE_SIZE (0)
#else
#  define LOCKBITS_START     (0x0000U)
#  define LOCKBITS_SIZE      (1U)
#  define LOCKBITS_PAGE_SIZE (0U)
#endif
#define LOCKBITS_END       (LOCKBITS_START + LOCKBITS_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define USER_SIGNATURES_START     (0x0000)
#  define USER_SIGNATURES_SIZE      (256)
#  define USER_SIGNATURES_PAGE_SIZE (256)
#else
#  define USER_SIGNATURES_START     (0x0000U)
#  define USER_SIGNATURES_SIZE      (256U)
#  define USER_SIGNATURES_PAGE_SIZE (256U)
#endif
#define USER_SIGNATURES_END       (USER_SIGNATURES_START + USER_SIGNATURES_SIZE - 1)

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define PROD_SIGNATURES_START     (0x0000)
#  define PROD_SIGNATURES_SIZE      (52)
#  define PROD_SIGNATURES_PAGE_SIZE (256)
#else
#  define PROD_SIGNATURES_START     (0x0000U)
#  define PROD_SIGNATURES_SIZE      (52U)
#  define PROD_SIGNATURES_PAGE_SIZE (256U)
#endif
#define PROD_SIGNATURES_END       (PROD_SIGNATURES_START + PROD_SIGNATURES_SIZE - 1)

#define FLASHSTART   PROGMEM_START
#define FLASHEND     PROGMEM_END
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define SPM_PAGESIZE 256
#else
#  define SPM_PAGESIZE 256U
#endif
#define RAMSTART     INTERNAL_SRAM_START
#define RAMSIZE      INTERNAL_SRAM_SIZE
#define RAMEND       INTERNAL_SRAM_END
#define E2END        EEPROM_END
#define E2PAGESIZE   EEPROM_PAGE_SIZE


/* ========== Fuses ========== */
#define FUSE_MEMORY_SIZE 6

/* Fuse Byte 0 (FUSEBYTE0) */
#define FUSE_JTAGUSERID0  (unsigned char)~_BV(0)  /* JTAG User ID Bit 0 */
#define FUSE_JTAGUSERID1  (unsigned char)~_BV(1)  /* JTAG User ID Bit 1 */
#define FUSE_JTAGUSERID2  (unsigned char)~_BV(2)  /* JTAG User ID Bit 2 */
#define FUSE_JTAGUSERID3  (unsigned char)~_BV(3)  /* JTAG User ID Bit 3 */
#define FUSE_JTAGUSERID4  (unsigned char)~_BV(4)  /* JTAG User ID Bit 4 */
#define FUSE_JTAGUSERID5  (unsigned char)~_BV(5)  /* JTAG User ID Bit 5 */
#define FUSE_JTAGUSERID6  (unsigned char)~_BV(6)  /* JTAG User ID Bit 6 */
#define FUSE_JTAGUSERID7  (unsigned char)~_BV(7)  /* JTAG User ID Bit 7 */
#define FUSE0_DEFAULT  (0xff)
#define FUSE_FUSEBYTE0_DEFAULT  (0xff)

/* Fuse Byte 1 (FUSEBYTE1) */
#define FUSE_WDPER0  (unsigned char)~_BV(0)  /* Watchdog Timeout Period Bit 0 */
#define FUSE_WDPER1  (unsigned char)~_BV(1)  /* Watchdog Timeout Period Bit 1 */
#define FUSE_WDPER2  (unsigned char)~_BV(2)  /* Watchdog Timeout Period Bit 2 */
#define FUSE_WDPER3  (unsigned char)~_BV(3)  /* Watchdog Timeout Period Bit 3 */
#define FUSE_WDWPER0  (unsigned char)~_BV(4)  /* Watchdog Window Timeout Period Bit 0 */
#define FUSE_WDWPER1  (unsigned char)~_BV(5)  /* Watchdog Window Timeout Period Bit 1 */
#define FUSE_WDWPER2  (unsigned char)~_BV(6)  /* Watchdog Window Timeout Period Bit 2 */
#define FUSE_WDWPER3  (unsigned char)~_BV(7)  /* Watchdog Window Timeout Period Bit 3 */
#define FUSE1_DEFAULT  (0x0)
#define FUSE_FUSEBYTE1_DEFAULT  (0x0)

/* Fuse Byte 2 (FUSEBYTE2) */
#define FUSE_BODPD0  (unsigned char)~_BV(0)  /* BOD Operation in Power-Down Mode Bit 0 */
#define FUSE_BODPD1  (unsigned char)~_BV(1)  /* BOD Operation in Power-Down Mode Bit 1 */
#define FUSE_TOSCSEL  (unsigned char)~_BV(5)  /* Timer Oscillator pin location */
#define FUSE_BOOTRST  (unsigned char)~_BV(6)  /* Boot Loader Section Reset Vector */
#define FUSE2_DEFAULT  (0xff)
#define FUSE_FUSEBYTE2_DEFAULT  (0xff)

/* Fuse Byte 3 Reserved */

/* Fuse Byte 4 (FUSEBYTE4) */
#define FUSE_JTAGEN  (unsigned char)~_BV(0)  /* JTAG Interface Enable */
#define FUSE_WDLOCK  (unsigned char)~_BV(1)  /* Watchdog Timer Lock */
#define FUSE_STARTUPTIME0  (unsigned char)~_BV(2)  /* Start-up Time Bit 0 */
#define FUSE_STARTUPTIME1  (unsigned char)~_BV(3)  /* Start-up Time Bit 1 */
#define FUSE_RSTDISBL  (unsigned char)~_BV(4)  /* External Reset Disable */
#define FUSE4_DEFAULT  (0xff)
#define FUSE_FUSEBYTE4_DEFAULT  (0xff)

/* Fuse Byte 5 (FUSEBYTE5) */
#define FUSE_BODLEVEL0  (unsigned char)~_BV(0)  /* Brownout Detection Voltage Level Bit 0 */
#define FUSE_BODLEVEL1  (unsigned char)~_BV(1)  /* Brownout Detection Voltage Level Bit 1 */
#define FUSE_BODLEVEL2  (unsigned char)~_BV(2)  /* Brownout Detection Voltage Level Bit 2 */
#define FUSE_EESAVE  (unsigned char)~_BV(3)  /* Preserve EEPROM Through Chip Erase */
#define FUSE_BODACT0  (unsigned char)~_BV(4)  /* BOD Operation in Active Mode Bit 0 */
#define FUSE_BODACT1  (unsigned char)~_BV(5)  /* BOD Operation in Active Mode Bit 1 */
#define FUSE5_DEFAULT  (0xff)
#define FUSE_FUSEBYTE5_DEFAULT  (0xff)

/* ========== Lock Bits ========== */
#define __LOCK_BITS_EXIST
#define __BOOT_LOCK_APPLICATION_TABLE_BITS_EXIST
#define __BOOT_LOCK_APPLICATION_BITS_EXIST
#define __BOOT_LOCK_BOOT_BITS_EXIST

/* ========== Signature ========== */
#define SIGNATURE_0 0x1E
#define SIGNATURE_1 0x96
#define SIGNATURE_2 0x52

/* ========== Power Reduction Condition Definitions ========== */

/* PR.PRGEN */
#define __AVR_HAVE_PRGEN	(PR_LCD_bm|PR_USB_bm|PR_AES_bm|PR_RTC_bm|PR_EVSYS_bm|PR_DMA_bm)
#define __AVR_HAVE_PRGEN_LCD
#define __AVR_HAVE_PRGEN_USB
#define __AVR_HAVE_PRGEN_AES
#define __AVR_HAVE_PRGEN_RTC
#define __AVR_HAVE_PRGEN_EVSYS
#define __AVR_HAVE_PRGEN_DMA

/* PR.PRPA */
#define __AVR_HAVE_PRPA	(PR_ADC_bm|PR_AC_bm)
#define __AVR_HAVE_PRPA_ADC
#define __AVR_HAVE_PRPA_AC

/* PR.PRPB */
#define __AVR_HAVE_PRPB	(PR_ADC_bm|PR_AC_bm)
#define __AVR_HAVE_PRPB_ADC
#define __AVR_HAVE_PRPB_AC

/* PR.PRPC */
#define __AVR_HAVE_PRPC	(PR_TWI_bm|PR_USART0_bm|PR_SPI_bm|PR_HIRES_bm|PR_TC1_bm|PR_TC0_bm)
#define __AVR_HAVE_PRPC_TWI
#define __AVR_HAVE_PRPC_USART0
#define __AVR_HAVE_PRPC_SPI
#define __AVR_HAVE_PRPC_HIRES
#define __AVR_HAVE_PRPC_TC1
#define __AVR_HAVE_PRPC_TC0

/* PR.PRPE */
#define __AVR_HAVE_PRPE	(PR_USART0_bm|PR_TC0_bm)
#define __AVR_HAVE_PRPE_USART0
#define __AVR_HAVE_PRPE_TC0


#endif /* #ifdef _AVR_ATXMEGA64B1_H_INCLUDED */

