/*
 * @company: image+
 * @Version: 1.0
 * @Autor: young
 * @Description: 
 * @LastEditors: young
 * @Date: 2020-11-05 16:18:35
 * @LastEditTime: 2021-01-29 09:31:11
 */
#ifndef OemUart_h
#define OemUart_h

#define Str_MAX_Len       64

//*****************************************************************************
// UART debug interface
// Timer 2 baudrate = Fosc / 32 / (0x10000-RCAP2)�C
//*****************************************************************************
#if UART_Debug
// 9600 bps-------------------------
#define R2HV                  0xFF
#define R2LV                  0xE2  
// 9600 bps-------------------------

// 19200 bps------------------------
//#define R2HV                  0xFF
//#define R2LV                  0xF1  
// 19200 bps------------------------

// 57600 bps------------------------
// #define R2HV                    0xFF
// #define R2LV                    0xFB  
// 57600 bps------------------------
#endif

typedef struct uart_cmd
{
	const unsigned char *CmdName;
	FUNCT_PTR_V_V        CmdFun;
}UART_CMD;

extern void UART_Send_Byte(void);
extern void UART_Print_Byte(unsigned char ch);
extern void UART_Print_HEX(unsigned char HEX_Dat);
extern void UART_Print_Int(unsigned int aInt);
extern void UART_Print_Str(unsigned char *str);
extern void uart_printf(const char *fmt,...);

extern void uart_print(unsigned char *str);
extern void uart_hex_show(unsigned char ch);
//extern void UART_RX_Command(void);

extern void uart_Initial_Host(void);
extern void uart_Initial(void);

// 16550 相关函数
extern unsigned char   uart1_16550_check_rx(void);
extern void TASK_UART_A_set_tx_data(unsigned char dat);
extern void TASK_UART_cfg_set_base(unsigned char fifo_en);

#endif
