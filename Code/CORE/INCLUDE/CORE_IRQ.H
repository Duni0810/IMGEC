/*
 * @company: image+
 * @Version: 1.0
 * @Autor: young
 * @Description: 
 * @LastEditors: young
 * @Date: 2020-11-05 16:18:34
 * @LastEditTime: 2020-12-26 17:19:52
 */
/*-----------------------------------------------------------------------------
 * TITLE: CORE_IRQ.H - Interrupt Service Routines (ISR).
 *
 * The Interrupt Service Routines (ISR).  The actual interrupt functions are
 * implemented in the "CHIP_IRQ.C".
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/

#ifndef CORE_IRQ_H
#define CORE_IRQ_H


// #if EC_MODE
#define PS2Interrupt2   (0x10+18)   // 18
#define PS2Interrupt1   (0x10+19)
#define PS2Interrupt0   (0x10+20)   // 20
// #else
// #define PS2Interrupt2   (0x10+20)   // 18
// #define PS2Interrupt1   (0x10+19)
// #define PS2Interrupt0   (0x10+18)   // 20
// #endif

extern void DisableAllInterrupt(void);
extern void EnableAllInterrupt(void);
extern void EnableKBCIBFInt(void);
extern void EnablePMCIBFInt(void);
extern void IRQ_INT18_PS2Interrupt2(void);
extern void IRQ_INT19_PS2Interrupt1(void);
extern void IRQ_INT20_PS2Interrupt0(void);
extern void InitEnableInterrupt(void);
extern void EnableModuleInterrupt(void);		  

#endif