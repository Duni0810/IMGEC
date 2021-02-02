#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

#if UART_Debug
// #include "stdio.h"
// #include<stdarg.h>
#endif

void uart_Initial_Host(void)
{
	BADRSEL = 0x01;
  //  RSTDMMC = 0x00;
	GCR1 = 0x05;
	GPCRB0 = ALT;
	GPCRB1 = ALT;
}


#define T1H_DAT                  0xFB    //  0xFB = 4800

// 关于初始化串口波特率设置，在手册193 ，公式为 UCT_Freq（9.2M）/32/(0x10000 - RCAP2)
void uart_Initial(void)
{
#if UART_Debug

	// 使用定时器2 产生波特率 --->
	SCON=0x40;         // Mode 1
	SCON |= BIT4;      // Receive data enable

    T2MOD=0x00;

	// PCON  |= 0x80;  
	// CKCON |= 0x20;


    RCAP2H=R2HV;
    RCAP2L=R2LV;

	TL2 = R2LV;  // CC
    TH2 = R2HV;  // CD

	// 对于定时器2 没有影响
    T2CON &= 0xF0;     // EXEN2=0; TR2=0; C/T2#=0; CP/RL2#=0;
    T2CON |= 0x30;     // RCLK = 1; TCLK=1;     receive and send use time2
	TR2=1;
	// <---


	// ---> 使用定时器1产生波特率
	// SCON=0x40;         // Mode 1
	// SCON |= BIT4;      // Receive data enable
    // TMOD=0x00;

	// TH1 = T1H_DAT;
	// TL1 = 0xFF;

	// // 自动重装载
	// TMOD |= 0x20;

	// // 翻倍
	// // PCON  |= 0x80;  
	// // CKCON |= 0x10;

	// TR1=1;
	//<---
	
	UART_RX_Buffer_In = 0;
	
	SET_MASK(UART_Buffer_Status,_buffer_Empty);   // Set buffer empty flag
	SET_MASK(UART_Buffer_Status,_Send_Ready);     // Set send ready flag
	
	SET_MASK(IE, BIT4); // Enable UART intrrupt

#endif	
}



volatile u8 tmp_ch = 0;
//------------------------------------------------------
//    Send out an char by 8032 UART from buffer
// 1. Just call in the event of 1 ms
// 2. It wil send a byte by 8032 UART when the macro UART_Debug is TRUE
//------------------------------------------------------
void UART_Send_Byte(void)
{
#if UART_Debug
	unsigned char ch;

	if(IS_MASK_SET(UART_Buffer_Status,_buffer_Empty)) // The buffer is empty
	{
		tmp_ch = 0x55;
		return;
	}

	CLEAR_MASK(UART_Buffer_Status,_Send_Ready);  // Set busy for send data, wait for ready when send next data
	
	ch = (*(char xdata *)((&Uart_Base_Add)+UART_TX_Buffer_Out)); // Get a char from buffer
	
	UART_TX_Buffer_Out++;

	if(UART_TX_Buffer_Out == DebugUartRange)
	{
		UART_TX_Buffer_Out = 0;
	}

	CLEAR_MASK(UART_Buffer_Status,_buffer_Full);  // Clear buffer full flag

	if(UART_TX_Buffer_Out == UART_TX_Buffer_In) 
	{
		SET_MASK(UART_Buffer_Status,_buffer_Empty); // Set bufer empty flag
	}
	
	SBUF = ch; // SBUF is the Register for UART TX
	           // After the success to send a char, TI will set to 1 automatically


	// if(ch == '\n') {
	// 	tmp_ch = 0x55;
	// }

#endif
}


//------------------------------------------------------
//    Print out an BYTE to UART buffer
//------------------------------------------------------
void UART_Print_Byte(unsigned char ch)
{
#if UART_Debug

	if(IS_MASK_SET(UART_Buffer_Status,_buffer_Full))   // The UART buffer is full
	{
		UART_TX_Buffer_In=0x06;
		UART_TX_Buffer_Out=0x00;
		((*(XBYTE *)((&Uart_Base_Add)+0))='\n');
		((*(XBYTE *)((&Uart_Base_Add)+1))='l');
		((*(XBYTE *)((&Uart_Base_Add)+2))='o');
		((*(XBYTE *)((&Uart_Base_Add)+3))='s');
		((*(XBYTE *)((&Uart_Base_Add)+4))='t');
		((*(XBYTE *)((&Uart_Base_Add)+5))='\n');
		
		CLEAR_MASK(UART_Buffer_Status,_buffer_Empty);  // Clear buffer empty flag
	}
	else
	{
		((*(char xdata *)((&Uart_Base_Add)+UART_TX_Buffer_In))=ch); // Put the char to buffer
		
		UART_TX_Buffer_In++;
		
		if(UART_TX_Buffer_In == DebugUartRange)
		{
			UART_TX_Buffer_In = 0;
		}
		
		CLEAR_MASK(UART_Buffer_Status,_buffer_Empty);  // Clear buffer empty flag
		
		if(UART_TX_Buffer_In == UART_TX_Buffer_Out)
		{
			SET_MASK(UART_Buffer_Status,_buffer_Full); // Set bufer full flag
		}
	}

#endif
}




//------------------------------------------------------
//    Print HEX to UART buffer
// 1. The HEX data rang is 0--FF
//------------------------------------------------------
void UART_Print_HEX(unsigned char HEX_Dat)
{
#if UART_Debug

	unsigned char ch;
	ch = HEX_Dat >> 4;
	if(ch <= 9)
	{
		ch = ch + '0';
	}
    else
    {
		ch = ch + 'A' - 10;
    }
    UART_Print_Byte(ch);

	ch = HEX_Dat & 0x0F;
	if(ch <= 9)
	{
		ch = ch + '0';
	}
    else
    {
		ch = ch + 'A' - 10;
    }
    UART_Print_Byte(ch);
	
#endif
}

//------------------------------------------------------
//    Print integer to UART buffer
//------------------------------------------------------
void UART_Print_Int(unsigned int aInt)
{
#if UART_Debug

	unsigned char temp;
	
	temp = aInt / 10000;
	if (temp != 0)
	{
		 UART_Print_Byte(temp + '0');
	}

	temp = aInt % 10000 / 1000;
	if (temp != 0)
	{
		UART_Print_Byte(temp + '0');
	}

	temp = aInt % 1000 / 100;
	if (temp != 0)
	{
		UART_Print_Byte(temp + '0');
	}

	temp = aInt % 100 / 10;
	if (temp != 0)
	{
		UART_Print_Byte(temp + '0');
	}
	
   	temp = aInt % 10;
	UART_Print_Byte(temp + '0');
	
#endif
}


//------------------------------------------------------
//    Print  an string to UART buffer
//  1. If the string has '\n', don't care, the receive software will parse
//------------------------------------------------------
void UART_Print_Str(unsigned char *str)
{
#if UART_Debug

	unsigned char i;
	unsigned char j;
	unsigned char ch;

	for (i = 0; i < Str_MAX_Len; i++)
	{
		ch = *(str + i);

		// 添加一个变量测试
		// tmp_ch = ch;

		if (ch == '\0')  // String end
		{
			break;
		}
		else
		{
			UART_Print_Byte(ch);
		}
	}

#endif
}


extern void Oem_Hook_Timer1ms(void);
void uart_printf(const char *fmt,...)
{
	#if UART_Debug


	#if 0  // 代码太大  不建议使用
	va_list ap;
	char xdata string[32];//访问内部拓展RAM，非访问外部RAM，不能超过内部拓展RAM大小(此处为64)
	
	va_start(ap,fmt);
	vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去
	UART_Print_Str(string);
	va_end(ap);
	#else

	UART_Print_Str(fmt);

	#endif

	#endif
}


void uart_hex_show(unsigned char ch)
{
	#if UART_Debug
    UART_Print_HEX(ch);

    for(;;){
		if(tmp_ch == 0x55) {
            tmp_ch = 0;
            break;
        }
        Oem_Hook_Timer1ms();
    };
	#endif
}

void uart_print(unsigned char *str)
{
#if UART_Debug
    UART_Print_Str(str);

    for(;;){
		if(tmp_ch == 0x55) {
            tmp_ch = 0;
            break;
        }
        Oem_Hook_Timer1ms();
    };
#endif
}


void Cmd_Hello(void)
{
	UART_Print_Str("This is CF03-T say hello\n");
}

void Cmd_Battery(void)
{
	UART_Print_Str("This is CF03-T say Battery\n");
}

void Cmd_Charger(void)
{
	UART_Print_Str("This is CF03-T say Charger\n");
}

const UART_CMD code UART_Cmd_Table[] = {
		{"Hello",   Cmd_Hello    },
		{"Battery", Cmd_Battery  },
		{"Charger", Cmd_Charger  },
		{0,0},
};
/*
//------------------------------------------------------
//    Processing of 8032 UART receiving commands
//  1. The command must be end of '\r' & '\n', 0x0D  0x0A
//  2. This function must be call in S0/S3/S4/S5
//------------------------------------------------------
void UART_RX_Command(void)
{
	unsigned char i;
	unsigned char j;
	unsigned char k;
	unsigned char Rx_index;

	Rx_index = UART_RX_Buffer_In;
	if(Rx_index)
	{
		for(i=0; i<Rx_index; i++)
		{
			if(0x0D == UART_RX_Buffer[i])  // 0x0D is the char '\r'
			{
				break;
			}
		}

		if(i<Rx_index)  // Receives the command
		{
			for(j=0; 0!=(UART_Cmd_Table[j].CmdFun); j++)  // Search command
			{
				for(k=0; (0x0D!=UART_RX_Buffer[k])&&(0!=(UART_Cmd_Table[j].CmdName[k])); k++)  // Rx command end of '\r'
				{
					if(UART_Cmd_Table[j].CmdName[k] == UART_RX_Buffer[k]) // compare command
					{
						continue;
					}
					else
					{
						break;
					}
				}

				if(0x0D==UART_RX_Buffer[k])  // There is match command
				{
					(UART_Cmd_Table[j].CmdFun)();
					UART_RX_Buffer_In = 0;
					break;
				}
			}

			if(0==(UART_Cmd_Table[j].CmdFun))  // There is no command match
			{
				UART_Print_Str("Command : ");
				for(i=0; i<Rx_index; i++)
				{
					UART_Print_Byte(UART_RX_Buffer[i]);
				}
				UART_Print_Str("\nThis command is not support!\n");
				UART_RX_Buffer_In = 0;
			}
		}

		if(i==(UART_RX_MAX_LEN-1))  // Rx Buffer overflow
		{
			UART_Print_Str("The Rx buffer is overflow and it's self-reset !!!\n");
			UART_RX_Buffer_In = 0;
		}
	}
}
*/


static void UART_GPIO_INIT(void)
{
    // 第一步
    // 16550 通用使能配置
    GCR6 = 0x03; // UART SOUT0 Enable 
    GCR1 = 0x01; // SIN0/SOUT0 are enabled

    // init GPIO 设置复用模式
    GPCRB0 = ALT;
    GPCRB1 = ALT;

    // set ec side  SSPI and uart to the ec side
    RSTDMMC = 0x0a;
}



static void TASK_UART_A_cfg_set_bitlen(u8 len)
{
    UART1_LCR |= (len & 0x07);
}

static void TASK_UART_A_cfg_set_Parity(u8 Parity)
{
    UART1_LCR |= ((Parity << 4) | (1 << 3));
}

static void TASK_UART_A_cfg_set_Break(u8 break_data)
{
    UART1_LCR |= (break_data << 6);
}

static void TASK_UART_A_cfg_set_baud(u16 dl)
{
    UART1_LCR |= (1 << 7);

    UART1_RBR |=   (dl & 0xff);
    UART1_IER |=  ((dl >> 8) & 0xff);

    CLEAR_MASK(UART1_LCR, BIT(7));

    // 高速模式
    if ((dl == 32770) || (dl == 32769)) {
        SET_MASK(UART1_ECSPMR, BIT(1));
    }
}


void TASK_UART_cfg_set_base(u8 fifo_en)
{
    UART_GPIO_INIT();

    // 第二部配置信息
    UART1_IER = 0x08;  // enable status
    UART1_IIR = 0xC0 | fifo_en;
    UART1_LCR = 0x03;  // 设置 8 数据位置，1 停止位 不进行奇偶校验
    UART1_MCR = 0x00;

    // 设置波特率
    // UART1_LCR  = 0x83;
    // UART1_RBR  = 0x01;
    // UART1_IER  = 0x00;

	TASK_UART_A_cfg_set_baud(1);
    // UART1_LCR  = 0x03; 


    // 使能INTC
    SET_MASK(ISR4, Int_UART1);  // clear
    SET_MASK(IER4, Int_UART1);  // enalbe
    
}



static void TASK_UART_A_cfg_set_modem(u8 mode)
{
    UART1_MCR = mode;
}

void TASK_UART_A_set_tx_data(u8 dat)
{
    u8 tmp8_data = 0x00;
    u8 width     = 0x00;  

    // tmp8_data = UART1_LCR;
    width = (UART1_LCR & 0x03) + 5;
    UART1_RBR = dat;
}

u8 uart1_16550_check_rx(void)
{
    u8 tmp8_data = 0x00;
    u8 width     = 0x00;  

    while(!(UART1_LSR & 0x01)); // 等状态
    width = (UART1_LCR & 0x03) + 5;
    tmp8_data = UART1_RBR; // data 

    return tmp8_data;
}


