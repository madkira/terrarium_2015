/************************************************************************************
 * configs/sam4s-xplained/src/sam4s-xplained.h
 *
 *   Copyright (C) 2009-2011, 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __CONFIGS_SAM4S_XPLAINED_SRC_SAM4S_XPLAINED_H
#define __CONFIGS_SAM4S_XPLAINED_SRC_SAM4S_XPLAINED_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <stdint.h>

#include <arch/irq.h>
#include <nuttx/irq.h>

#include "chip/sam_pinmap.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Configuration ********************************************************************/

#define HAVE_HSMCI      1
#define HAVE_PROC       1
#define HAVE_USBDEV     1
#undef  HAVE_USBMONITOR

/* USB Device */
/* CONFIG_SAM34_UDP and CONFIG_USBDEV must be defined, or there is no USB
 * device.
 */

#if !defined(CONFIG_SAM34_UDP) || !defined(CONFIG_USBDEV) ||!defined(CONFIG_CDCACM)
#  undef HAVE_USBDEV
#endif

/* Check if we should enable the USB monitor before starting NSH */

#ifndef HAVE_USBDEV
#  undef CONFIG_USBDEV_TRACE
#endif

#if !defined(CONFIG_SYSTEM_USBMONITOR) && !defined(CONFIG_USBDEV_TRACE)
#  undef HAVE_USBMONITOR
#endif

/* There are four LEDs on board the SAM4S Xplained board, two of these can be
 * controlled by software in the SAM4S:
 *
 *   LED              GPIO
 *   ---------------- -----
 *   D9  Yellow LED   PC10
 *   D10 Yellow LED   PC17
 *
 * Both can be illuminated by driving the GPIO output to ground (low).
 *
 * These LEDs are not used by the board port unless CONFIG_ARCH_LEDS is
 * defined.  In that case, the usage by the board port is defined in
 * include/board.h and src/up_leds.c. The LEDs are used to encode OS-related
 * events as follows:
 *
 *   SYMBOL                Meaning                     LED state
 *                                                   D9     D10
 *   -------------------  -----------------------  -------- --------
 *   LED_STARTED          NuttX has been started     OFF      OFF
 *   LED_HEAPALLOCATE     Heap has been allocated    OFF      OFF
 *   LED_IRQSENABLED      Interrupts enabled         OFF      OFF
 *   LED_STACKCREATED     Idle stack created         ON       OFF
 *   LED_INIRQ            In an interrupt              No change
 *   LED_SIGNAL           In a signal handler          No change
 *   LED_ASSERTION        An assertion failed          No change
 *   LED_PANIC            The system has crashed     OFF      Blinking
 *   LED_IDLE             MCU is is sleep mode         Not used
 *
 * Thus if D9 is statically on, NuttX has successfully booted and is,
 * apparently, running normmally.  If D10 is flashing at approximately
 * 2Hz, then a fatal error has been detected and the system has halted.
 */

#define GPIO_D9      (GPIO_OUTPUT | GPIO_CFG_PULLUP | GPIO_OUTPUT_SET | \
                      GPIO_PORT_PIOC | GPIO_PIN10)
#define GPIO_D10     (GPIO_OUTPUT | GPIO_CFG_PULLUP | GPIO_OUTPUT_SET | \
                      GPIO_PORT_PIOC | GPIO_PIN17)

/* Mechanical buttons:
 *
 * The SAM4S Xplained has two mechanical buttons. One button is the RESET button
 * connected to the SAM4S reset line and the other is a generic user configurable
 * button labeled BP2. When a button is pressed it will drive the I/O line to GND.
 *
 *   PA5 BP2
 */

#define GPIO_BP2     (GPIO_INPUT | GPIO_CFG_PULLUP | GPIO_CFG_DEGLITCH | \
                      GPIO_INT_BOTHEDGES | GPIO_PORT_PIOA | GPIO_PIN5)
#define IRQ_BP2      SAM_IRQ_PA5

/* SRAM Enable.  EBI_NLB PC16.  Active=low; Standby=high */

#define GPIO_EBI_NLB (GPIO_OUTPUT | GPIO_CFG_PULLUP | GPIO_OUTPUT_SET | \
                      GPIO_PORT_PIOC | GPIO_PIN16)

/************************************************************************************
 * Public Types
 ************************************************************************************/

/************************************************************************************
 * Public data
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Public Functions
 ************************************************************************************/

/************************************************************************************
 * Name: sam_sram_initialize
 *
 * Description:
 *   Configure and enable SRAM on board the SAM4S Xplained
 *
 ************************************************************************************/

#ifdef CONFIG_SAM34_EXTSRAM0
void sam_sram_initialize(void);
#endif

/************************************************************************************
 * Name: sam_timerinitialize()
 *
 * Description:
 *   Perform architecture-specific initialization of the timer hardware.
 *
 ************************************************************************************/

#ifdef CONFIG_TIMER
int board_timerinitialize(void);
#else
#  define sam_timerinitialize() (0)
#endif

#ifdef CONFIG_SAM34_ADC12B
int board_adc_initialize(void);
#endif

#if defined(CONFIG_PWM) && defined(CONFIG_SAM34_PWM)
int board_pwm_initialize(void);
#endif

#endif /* __ASSEMBLY__ */
#endif /* __CONFIGS_SAM4S_XPLAINED_SRC_SAM4S_XPLAINED_H */
