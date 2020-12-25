/*-----------------------------------------------------------------------------
 * TITLE: CORE_MAIN.C - Main Program for KBC firmware.
 *
 * Main processing loop (interrupt driven) for the keyboard controller/scanner.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/* ----------------------------------------------------------------------------
 *  FUNCTION: main - Main service loop.
 *
 *  Wait in idle state until an IRQ causes an exit from idle.  If the IRQ
 *  handler posted a service request (via bSERVICE) then dispatch control to
 *  the appropriate service handler.  Otherwise, go back to idle state.  After
 *  all service requests have been handled, return to idle state.
 * ------------------------------------------------------------------------- */

static void __1s_delay(void)
{
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
}




BYTE code __initsio_table[]=
{
				// Configure and Enable Logical Device 06h(KBD)
	0x07 ,0x06,	// Select Logical Device 06h(KBD)
  	0x70 ,0x33,	// Set IRQ=01h for Logical Device 06h(KBD)
};



static void __InitSio(BYTE Ldnumber, BYTE offset)
{
    # if 0
    BYTE code * data_pntr;
    BYTE cnt;

	// 0X1200
  	SET_MASK(LSIOHA,LKCFG);
  	SET_MASK(IBMAE,CFGAE);
  	SET_MASK(IBCTL,CSAE);

    cnt=0;
    data_pntr=__initsio_table;
    while(cnt < (sizeof(__initsio_table)/2) )
    {
        IHIOA=0;              // Set indirect Host I/O Address
        IHD=*data_pntr;
        while( IS_MASK_SET(IBCTL,CWIB)) {
			BAT_LED1_ON();
		};

		BAT_LED1_OFF();
		// for(;;);


        data_pntr ++;

        IHIOA=1;              // Set indirect Host I/O Address
        IHD=*data_pntr;
        while( IS_MASK_SET(IBCTL,CWIB)) {
			BAT_LED1_ON();
		};
		BAT_LED1_OFF();

        data_pntr ++;
        cnt ++;
    }

 	CLEAR_MASK(LSIOHA,LKCFG);
  	CLEAR_MASK(IBMAE,CFGAE);
  	CLEAR_MASK(IBCTL,CSAE);
        
        #else

	SET_MASK(LSIOHA,LKCFG);
  	SET_MASK(IBMAE,CFGAE);
  	SET_MASK(IBCTL,CSAE);

    // while(1) {
        IHIOA=Ldnumber;              // Set indirect Host I/O Address
        IHD=offset;
        Delay1MS(2);
        while(IS_MASK_SET(IBCTL,CWIB)) {
            BAT_LED1_ON();
            for(;;);
        };
            BAT_LED1_OFF();

    // }

 	CLEAR_MASK(LSIOHA,LKCFG);
  	CLEAR_MASK(IBMAE,CFGAE);
  	CLEAR_MASK(IBCTL,CSAE);
        #endif

}


#if 0
void main(void)
{
    u8    young_flag  = 0x00;
    u8    young_flag1 = 0x00;

	DisableAllInterrupt();
	SP = 0xC0;					// Setting stack pointer

	if(Hook_ECRetunrMainFuncKeepCondition()==0x33)  // Exit from follow mode or EC scatch ROM
	{
		CLEAR_MASK(FBCFG,SSMC); // disable scatch ROM
		_nop_();
	    MPRECF = 0x01;
	    _nop_();
	    MPRECF = 0x01;
	    _nop_(); 
	    MPRECF = 0x01;
	    _nop_();
	    MPRECF = 0x01;
	    _nop_();
	    _nop_();
        WinFlashMark = 0x00;
        ResetBANKDATA();        // init bank mechanism to code bank 0
        Hook_ECExitFollowMode();
        Init_Timers();
		EnableModuleInterrupt();    
	}
	else
	{
		Core_Initialization();
		Oem_Initialization();
        InitEnableInterrupt();
		
        #if UART_Debug
		uart_Initial();
        GPCRB0 = ALT;
        GPCRB1 = ALT;

        uart_print("\r\n------------------------------------\r\n");
        uart_print("  EC Init OK !!! ");
        uart_print("\r\n------------------------------------\r\n");

		#else
		//uart_Initial_Host();
		#endif
	}

    DCache         = 0x00;

	if((0x55==BRAM_FLASH_ID0)&&(0xaa==BRAM_FLASH_ID1)&&(0x55==BRAM_FLASH_ID2)&&(0xaa==BRAM_FLASH_ID3))
	{
		//PulseSBPowerButton();
	}

	BRAM_FLASH_ID0=0;
	BRAM_FLASH_ID1=0;
	BRAM_FLASH_ID2=0;
	BRAM_FLASH_ID3=0;	


    SCLKTS_A = 0x02;

    CHARGER_OPTION_L = 0x08;
    CHARGER_OPTION_H = 0xE1;  // 默认为E1  建议别乱写

    // ServiceSMBus();

    // if(bRWSMBus(SmartChargerChannel, SMbusWW, Charger_Addr, _CMD_ChargerOption0, &CHARGER_OPTION_L, 0) == FALSE ) {
    //     // UART_Print_Str("Write ERROR \r\n");
    //     // BAT_LED1_ON();
    //     // while(1);
    // }
    
    // ServiceSMBus();

    // if(bRWSMBus(SmartChargerChannel, SMbusRW, Charger_Addr, _CMD_ChargerOption0, &CHARGER_OPTION_L, 0)) {
    //     uart_print("CHARGER_OPTION:  ");
    //     UART_Print_HEX(CHARGER_OPTION_L);
    //     uart_print(" \r\nCHARGER_OPTION: ");
    //     UART_Print_HEX(CHARGER_OPTION_H);
    //     uart_print(" \r\n");
    // }


    // ServiceSMBus();
    

    // anx_write_reg(0x58, 0xa1 , 0x20);

    // ServiceSMBus();
    // young_flag = anx_read_reg(0x58, 0xa1); // ANALOG_CTRL_1  0xa1
    // uart_print("anx_read_reg:  ");
    // uart_hex_show(young_flag);
    // young_flag = 0x00;


	for(;;) {
        //-----------------------------------
        // 1 millisecond elapsed
        //-----------------------------------
        if(F_Service_MS_1)
        {
            F_Service_MS_1=0;
            service_1mS();

            // if(young_flag >= 250) {
            //     INVERSE_REG(GPDRC, 6);
            //     uart_print("test code \r\n");
            //     young_flag = 0;
            // }
            // young_flag++;

            continue;
        }

        // INVERSE_REG(GPDRJ, 4);
        // uart_print("idle code \r\n");
        //-----------------------------------
        // Keyboard scanner service
        //-----------------------------------
        if(F_Service_KEY)
        {
        	F_Service_KEY=0;
            // uart_print("KBS code \r\n");
			service_scan();
			continue;
        }

        young_flag1 = Get_Buffer();
        if ((young_flag1 != 0xff) && ((young_flag1 != 0x00))) {
            uart_print("\r\ndata:");
            uart_hex_show(young_flag1);
        }
	};

#else 
void main(void)
{
    u8    young_flag  = 0x00;
    u8    young_flag1 = 0x00;
    

	DisableAllInterrupt();
	SP = 0xC0;					// Setting stack pointer

	if(Hook_ECRetunrMainFuncKeepCondition()==0x33)  // Exit from follow mode or EC scatch ROM
	{
		CLEAR_MASK(FBCFG,SSMC); // disable scatch ROM
		_nop_();
	    MPRECF = 0x01;
	    _nop_();
	    MPRECF = 0x01;
	    _nop_(); 
	    MPRECF = 0x01;
	    _nop_();
	    MPRECF = 0x01;
	    _nop_();
	    _nop_();
        WinFlashMark = 0x00;
        ResetBANKDATA();        // init bank mechanism to code bank 0
        Hook_ECExitFollowMode();
        Init_Timers();
		EnableModuleInterrupt();    
	}
	else
	{
        // SMBUS1_test1 = 0x00;
        // SMBUS1_test2 = 0x00;
        // SMBUS1_test3 = 0x00;
        // SMBUS1_test4 = 0x00;
        // SMBUS1_test5 = 0x00;
        // SMBUS1_test6 = 0x00;

		Core_Initialization();
		Oem_Initialization();
        InitEnableInterrupt();
		
        #if UART_Debug
		uart_Initial();
        GPCRB0 = ALT;
        GPCRB1 = ALT;

        uart_print("\r\n------------------------------------\r\n");
        uart_print("  EC Init OK !!! ");
        uart_print("\r\n------------------------------------\r\n");

		#else
		//uart_Initial_Host();
		#endif
	}
#endif


	if((0x55==BRAM_FLASH_ID0)&&(0xaa==BRAM_FLASH_ID1)&&(0x55==BRAM_FLASH_ID2)&&(0xaa==BRAM_FLASH_ID3))
	{
		//PulseSBPowerButton();
	}

	BRAM_FLASH_ID0=0;
	BRAM_FLASH_ID1=0;
	BRAM_FLASH_ID2=0;
	BRAM_FLASH_ID3=0;	

            
#if !EC_MODE

    /* 提高代码执行效率 */
    // 使能Dcache 代码执行效率更高点
     DCache         = 0x00;

    // 控制flash 读写拍数
     SMFI_FIC_CTL1  = 0x00;

    // 初始化 pS2 时钟
    PSDCNUM1 = 0x03;
    PSDCNUM2 = 0x03;
    PSDCNUM3 = 0x03;

    // 初始化 pS2 时钟
    PSCLKEN = 0x07;  // PSCLKEN


#endif

    


#if 0
    // 使能Dcache 代码执行效率更高点
     DCache = 0x00;

    // 设置时钟为100K
    SCLKTS_A = 0x02;
    SCLKTS_B = 0x02;
    SCLKTS_C = 0x02;

    CHARGER_OPTION_L = 0x08;
    CHARGER_OPTION_H = 0xE2;  // 默认为E1  建议别乱写


    // GPDRM  =  0x00;

    // __1s_delay();


    //  (*(volatile unsigned char xdata *) 0x1206) = 0x01;
    //  (*(volatile unsigned char xdata *) 0x1208) = 0x04;

    

  


	for(;;) {
        //-----------------------------------
        // 1 millisecond elapsed
        //-----------------------------------
        if(F_Service_MS_1)
        {
            F_Service_MS_1=0;
            service_1mS();

            if(young_flag >= 250) {
                INVERSE_REG(GPDRC, 6);
                young_flag = 0;
            }
            young_flag++;
            continue;
        }


        if (SysPowState == SYSTEM_S0) {
            // INVERSE_REG(GPDRC, 6);

            // __InitSio();
            __InitSio(0x07, 0x06);
            __InitSio(0x70, 0x33);

            // __InitSio(0x07, 0x06);
            // __InitSio(0x71, 0x55);
            


            (*(volatile unsigned char xdata *) 0x812) = ReadSioInterface(0x06,0x70);

            if ((*(volatile unsigned char xdata *) 0x812) != 0x13) {
                BAT_LED2_ON();
                    for(;;);
            }   


            __InitSio(0x07, 0x06);
            __InitSio(0x70, 0x11);

            // __InitSio(0x07, 0x06);
            // __InitSio(0x71, 0x55);
            


            (*(volatile unsigned char xdata *) 0x813) = ReadSioInterface(0x06,0x70);
            if ((*(volatile unsigned char xdata *) 0x813) != 0x11) {
                BAT_LED2_ON();
                    for(;;);
            }  


            // (*(volatile unsigned char xdata *) 0x814) = ReadSioInterface(0x10,0x62);
            // (*(volatile unsigned char xdata *) 0x813) = ReadSioInterface(0x06,0x71);
        }
        // INVERSE_REG(GPDRJ, 4);

	};
#endif

    // __test_speed_code();
            

	while(1)
   	{
        if(OEM_SkipMainServiceFunc()==Normal_MainService)
        {


    		main_service();
    		EnableModuleInterrupt();
    		_nop_();
    		_nop_();
    		_nop_();
    		_nop_();

			#if TouchPad_only
            if(PS2CheckPendingISR()==0x00)
            {
                ScanAUXDeviceStep();
            }
			#endif

            #ifdef SMBusServiceCenterFunc
    		if((Service==0x00)&&(Service1==0x00)&&(CheckSMBusNeedService()==SMBus_ClearService))
            #else
            if((Service==0x00)&&(Service1==0x00))
            #endif
    		{
                // 暂时   young
                #if EC_MODE
         		PCON=1;      		// enter idle mode
                 #endif
    		}
        }
  	} 
}


#define  __DEBUG__  1
/* ----------------------------------------------------------------------------
 * FUNCTION: main_service - Check for new/more service requests.
 *
 * Check for a request flag.  The check is done according to priority.  If a
 * request flag is set, handle the request and loop back to get the flags
 * again.  Do not follow through to check the next flag.  The flags are to be
 * checked in order.
 * ------------------------------------------------------------------------- */
void main_service(void) 
{
    #ifdef SMBusServiceCenterFunc
    while((Service!=0x00)||(Service1!=0x00)||(CheckSMBusNeedService()==SMBus_NeedService))
    #else
    while((Service!=0x00)||(Service1!=0x00))
    #endif
    {
        // 这些其实不影响点亮，但是会卡在初始化位置（屏幕显示银河麒麟的界面）
        // 
        #if __DEBUG__
        //-----------------------------------
        // Host command/data service    6064
        //-----------------------------------
        if(F_Service_PCI)
        {
            F_Service_PCI=0;
            service_pci1();
            continue;
        }

        //-----------------------------------
        // Service unlock
        //-----------------------------------
        if(F_Service_UNLOCK)
        {
            F_Service_UNLOCK=0;
            service_unlock();
            continue;
        }

        //-----------------------------------
        // Send byte from KBC       6064
        //-----------------------------------
        if(F_Service_SEND)
        {
            F_Service_SEND=0;
            service_send();
            continue;
        }

#if 1
        //-----------------------------------
        // Send PS2 interface data	
        //-----------------------------------
        if(F_Service_Send_PS2)
        {
            F_Service_Send_PS2=0;
            service_PS2_data();
            continue;
        }

        //-----------------------------------
        // process PS2 interface data
        //-----------------------------------
        if(F_Service_PS2)
        {
            F_Service_PS2=0;
            service_ps2();
            continue;
        }
#endif
        //-----------------------------------
        // process SMBus interface data
        //-----------------------------------
        #ifdef SMBusServiceCenterFunc
		
		if (IS_MASK_CLEAR(SYS_MISC1, BAT_FW_UP))
	 	{
        	ServiceSMBus();
		}	
		
        #endif

#endif

        //-----------------------------------
        // Secondary Host command/data service
        // pm1 事件操作  与 ACPI 有关指令 bios
        //-----------------------------------
        if(F_Service_PCI2)
        {
            F_Service_PCI2=0;
            service_pci2();
            continue;
        }


        //-----------------------------------
        // 1 millisecond elapsed
        //-----------------------------------
        if(F_Service_MS_1)
        {
            F_Service_MS_1=0;
            service_1mS();
            continue;
        }

#if 1
        //-----------------------------------
        // Keyboard scanner service
        //-----------------------------------
        if(F_Service_KEY)
        {
        	F_Service_KEY=0;
			service_scan();
			continue;
        }
 #endif     

        //-----------------------------------
        // Low level event  5ms 使能一次
        //-----------------------------------
        if(F_Service_Low_LV)
        {
            F_Service_Low_LV=0;
            service_Low_LVEvent();
            continue;
        } 

#if __DEBUG__
        //-----------------------------------
        // Third Host command/data service
        // 做PM2 操作  68/6c  这个好像与 系统 有关操作
        //-----------------------------------
        if(F_Service_PCI3)
        {
            F_Service_PCI3=0;
            service_pci3();
            continue;
        }


        //-----------------------------------
        // fourth command/data service
        // 做PM3 操作  好像没进来过
        //-----------------------------------
        if(F_Service_PCI4)
        {
            F_Service_PCI4=0;
            service_pci4();
            continue;
        }
#endif
    }
}

static void service_Low_LVEvent(void)
{
	if((KBPendingTXCount != KBPendingRXCount )||(scan.kbf_head != scan.kbf_tail))
	{
		SetServiceSendFlag();
	}

    if(IS_MASK_SET(KBHISR,P_IBF))
    {
  	    F_Service_PCI = 1;
    }
    
    if(IS_MASK_SET(PM1STS,P_IBF))
    {
  	    F_Service_PCI2 = 1;
    }
}

//----------------------------------------------------------------------------
// FUNCTION: service_unlock
// Unlock aux devices and re-enable Host interface IRQ if it is ok to do so.
//----------------------------------------------------------------------------
static void service_unlock(void)
{
	Unlock_Scan();
}

//------------------------------------------------------------
// Polling events
//------------------------------------------------------------
void service_1mS(void)
{
	Timer1msEvent();
	Timer1msCnt++;

    if(Timer1msCnt>=10)
    {
        Timer1msCnt = 0x00;
    }

    // 判断强制关机事件
    if(Hook_Only_Timer1msEvent()==Only_Timer1msEvent)
    {   
        return;
    }

    if((Timer1msCnt%5)==0x00)
    {
	    Timer5msEvent();            // 检查系统状态，这个与系统有关
	    Timer5msCnt++;
	    if ( Timer5msCnt & 1 )  	// 10ms events
	    {
            Timer10msEventA();      // 电磁管理事件
	    }
	    else
	    {
		    Timer10msEventB();                          // ANX7447 事件
     	    switch( Timer5msCnt )   // Share Loading Branch Control
    	    {
       		    case 2: Timer50msEventA();              // LED 灯控制
                    break;
          	    case 4: Timer50msEventB();              // 适配器热插拔事件
             	    break;
        	    case 6: Timer50msEventC();              // 电池热插拔事件，SCI         
              	    break;
          	    case 8: Timer100msCntB++;
         		    if ( Timer100msCntB & 1 )
             	    {
                  	    Timer100msEventA();             // 做 ADC 温度获取
              	    }
             	    else
             	    {
                   	    Timer100msEventB();             // 获取风扇1，2转速，在500ms事件做调速
              	    }
               	    break;

           	    default:        
				    Timer5msCnt=0;
              	    break;
     	    }

    	    if ( Timer5msCnt == 0x00 )
    	    {       			// 50msec
          	    Timer100msCnt ++;
          	    if ( Timer100msCnt & 1 )
         	    {
             	    Timer100msEventC();                 // 空函数
          	    }
         	    else
     		    {       		// 100msec
          		    switch( Timer100msCnt )
              	    {
                	    case 2:	Timer500msEventA();     // 系统睡眠唤醒 例如S3->S0 有关
                 		    break;
                 	    case 4:	Timer500msEventB();     // 与进入sleep
                      	    break;
                 	    case 6:	Timer500msEventC();     // GPU 温度有关
                     	    break;
                 	    case 8:	Timer1SecEventA();      // 风扇1 检查风速，调速
                     	    break;
					    case 10: 	Timer1SecEventB();  // 风扇2 检查风速，调速
                     	    break;	
                 	    case 12:	Timer500msEventA(); // 系统睡眠唤醒 例如S3->S0 有关
                      	    break;
                	    case 14:	Timer500msEventB(); // 与进入sleep
                      	    break;
               		    case 16: 	Timer500msEventC(); // GPU 温度有关
                      	    break;
                 	    case 18: 	Timer1SecEventC();  // ADC温度有关
                     	    break;
                  	    default:        // 1 Sec
                      	    Timer100msCnt = 0;
                  		    Timer1SecCnt ++;

                    	    if ( Timer1SecCnt == 60 )
                      	    {
                         	    Timer1MinEvent();   // 空
                         	    Timer1SecCnt=0;
                     	    }
                    	    break;
          		    }
              	}
       		}
   		}
	} 
}

//------------------------------------------------------------
// 1ms events
//------------------------------------------------------------
void Timer1msEvent(void)
{
    // 暂时屏蔽
    ReSendPS2PendingData();
    Hook_Timer1msEvent(Timer1msCnt);
}

//------------------------------------------------------------
// 5ms events
//------------------------------------------------------------
void Timer5msEvent(void)
{
    F_Service_Low_LV = 1;
	if (Timer_A.fbit.TMR_SCAN) 
	{
        // uart_print("Timer_A.fbit.TMR_SCAN\r\n");
  		F_Service_KEY = 1;		// Request scanner service. 
  	}
    // uart_print("Timer5msEvent\r\n");
    Hook_Timer5msEvent();
}

//------------------------------------------------------------
// 10ms events
//------------------------------------------------------------
void Timer10msEventA(void)
{
    SetStartScanAUXFlag();
	Hook_Timer10msEventA();	
}

//------------------------------------------------------------
// 10ms events
//------------------------------------------------------------
void Timer10msEventB(void)
{
	Hook_Timer10msEventB();	 
}

//------------------------------------------------------------
// 50ms events A
//------------------------------------------------------------
void Timer50msEventA(void)
{
	Hook_Timer50msEventA();
}

//------------------------------------------------------------
// 50ms events B
//------------------------------------------------------------
void Timer50msEventB(void)
{
	Hook_Timer50msEventB();
}

//------------------------------------------------------------
// 50ms events C
//------------------------------------------------------------
void Timer50msEventC(void)
{
	Hook_Timer50msEventC();
}

//------------------------------------------------------------
// 100ms events A
//------------------------------------------------------------
void Timer100msEventA(void)
{
	Hook_Timer100msEventA();
}

//------------------------------------------------------------
// 100ms events B
//------------------------------------------------------------
void Timer100msEventB(void)
{
	Hook_Timer100msEventB();
}

//------------------------------------------------------------
// 100ms events C
//------------------------------------------------------------
void Timer100msEventC(void)
{
	Hook_Timer100msEventC();
}

//------------------------------------------------------------
// 500ms events A
//------------------------------------------------------------
void Timer500msEventA(void)
{
	Hook_Timer500msEventA();
}

//------------------------------------------------------------
// 500ms events B
//------------------------------------------------------------
void Timer500msEventB(void)
{
	Hook_Timer500msEventB();
}

//------------------------------------------------------------
// 500ms events C
//------------------------------------------------------------
void Timer500msEventC(void)
{
	Hook_Timer500msEventC();
}

//------------------------------------------------------------
// 1sec events A
//------------------------------------------------------------
void Timer1SecEventA(void)
{	
	Hook_Timer1SecEventA();
}

//------------------------------------------------------------
// 1sec events B
//------------------------------------------------------------
void Timer1SecEventB(void)
{
	Hook_Timer1SecEventB();
}

//------------------------------------------------------------
// 1sec events C
//------------------------------------------------------------
void Timer1SecEventC(void)
{
	Hook_Timer1SecEventC();
}

//------------------------------------------------------------
// 1min events
//------------------------------------------------------------
void Timer1MinEvent(void)
{
    Hook_Timer1MinEvent();
}

