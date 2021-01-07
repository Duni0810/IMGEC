/*
 * @company: image+
 * @Version: 1.0
 * @Autor: young
 * @Description: 
 * @LastEditors: young
 * @Date: 2020-11-05 16:18:34
 * @LastEditTime: 2021-01-05 17:24:18
 */
#ifndef	OEM_Debug_H
#define OEM_Debug_H



//---------------------------------------
// BRAM debug range
//---------------------------------------
#define BRAM_Debug      FALSE
#define DebugBRamAddr   0x2210
#define DebugBRamRange  0x2F
#define BRAM_RAM_Addr   0xA00

//---------------------------------------
// RAM debug range is 0x900--0x9FF
//---------------------------------------
#define RAM_Debug       TRUE
#define DebugRamAddr    0x900
#define DebugRamRange   0xFF

//---------------------------------------
// UART debug range is 0xE00--0xFFF
//---------------------------------------
#define UART_Debug      FALSE  //FALSE
#define Uart_Base_Add   (*(XBYTE *)0x0E00)
#define DebugUartRange  0x1FF
#define UART_RX_MAX_LEN 32




extern void RamDebug(unsigned char dbgcode);
extern void BRAMDebug(unsigned char dbgcode);
extern void ClearBRam(void);

extern void Copy_BRAM_SRAM(void);

extern BYTE ReadSioInterface(BYTE Ldnumber, BYTE offset);
#endif