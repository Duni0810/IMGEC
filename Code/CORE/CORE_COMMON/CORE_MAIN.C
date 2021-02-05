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


#if 0
void main(void)
{
    u8    young_flag  = 0x00;
    u8    young_flag1 = 0x00;

#if !EC_MODE
    // 控制flash 读写拍数
    SMFI_FIC_CTL0  = 0x98;
    SMFI_FIC_CTL1  = 0x00;
#endif

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


    // KSI0 GPI
    // KSIGCTRL = 0x01;
    // KSIGOEN  = 0x00;

    // // KSO12 GPO0
    // KSOHGCTRL = 0x10;
    // KSOHGOEN  = 0x10;
    // KSOH1     = 0x00;
    
	for(;;) {
        // DelayXms(5);
        // INVERSE_REG(KSOH1, 4);
        // KSOHGDMRR = 0x10;
        //-----------------------------------
        // 1 millisecond elapsed
        //-----------------------------------
        // if(F_Service_MS_1)
        // {
        //     F_Service_MS_1=0;
        //     service_1mS();

        //     // if(young_flag >= 250) {
        //     //     INVERSE_REG(GPDRC, 6);
        //     //     uart_print("test code \r\n");
        //     //     young_flag = 0;
        //     // }
        //     // young_flag++;

        //     continue;
        // }

        // INVERSE_REG(GPDRJ, 4);
        // uart_print("idle code \r\n");
        //-----------------------------------
        // Keyboard scanner service
        //-----------------------------------
        // if(F_Service_KEY)
        // {
        	// F_Service_KEY=0;
            // uart_print("KBS code \r\n");
			service_scan();
			// continue;
        // }
        // KSOL  = 0x00;
        // KSOH1 = 0x00;
        young_flag1 = Get_Buffer();
        if ((young_flag1 != 0xff) && ((young_flag1 != 0x00))) {
            uart_print("\r\ndata:");
            uart_hex_show(young_flag1);
        }
	};

#else 

void main(void)
{
#if !EC_MODE
    // 控制flash 读写拍数
    SMFI_FIC_CTL0  = 0x98;
    SMFI_FIC_CTL1  = 0x00;
#endif

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

    // 初始化 pS2 消抖参数
    PSDCNUM1 = 0x01;
    PSDCNUM2 = 0x01;
    PSDCNUM3 = 0x01;

    // 初始化 pS2 时钟
    PSCLKEN = 0x07;  // PSCLKEN
#endif


    // BAT_LED1_ON();
    // BAT_LED2_ON();



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
                // // 暂时   young
         		PCON=1;      		// enter idle mode
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                // INVERSE_REG(GPDRJ, 4);
                // INVERSE_REG(GPDRC, 6);

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
        // 做PM2 操作  68/6c  这个好像与 bios 有关操作
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

