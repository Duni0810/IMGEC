/*-----------------------------------------------------------------------------
 * TITLE: OEM_INIT.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>


// BAT_LED1_ON();  电源灯1  白色
// BAT_LED2_ON();  电源灯2  橙色

#define uchar  unsigned char

static void __1s_delay(void)
{
//	int i = 0;
//	int j = 0;
//	
//	for(;i < 250;i++) {
//		for(;j < 250; j++) {
//			
//			_nop_();
//		}
//	}
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
   Delay1MS(200);
}

// 看门狗测试
#if 0

/**
 * 试验一内容  : RSTS 寄存器属性判断
 * 实验一现象  : 在断点之后插入适配器，会先亮橙色，后一段时间粗发看门狗之后亮白色
 *             并且在之后一直处于白色灯的亮灭；
 *
 * 试验步骤    : 连续读取两次状态，分别保存不同的变量中，判断两个变量是否相等
 *             关于 RSTS 寄存器我认为是读清的状态,
 * 结论        : RSTS 是一个读清操作，如果不读取他的状态就不会更新；
 */
static void __test1_rets(void)
{ 
    uchar i = 0;
    uchar j = 0;

    //  Init_GPIO();
    CLEAR_MASK(GPDRC ,BIT(6));
    CLEAR_MASK(GPDRJ ,BIT(4));

    GPCRC6 = OUTPUT;
    GPCRJ4 = OUTPUT;

    i = RSTS;
    j = RSTS;

    if(i == j) {
        BAT_LED1_OFF();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
        BAT_LED2_OFF();
    }

    ETWCFG = 0x20;  // 使能外部看门狗

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();

    EWDKEYR = 0xff;

    while(1) {

    };
}

/**
 * 试验二内容 : 外部看门狗试验
 * 实验二现象: 白色的led1 会先亮，然后会间接性亮橙色的，因为外部看萌狗的作用,一直复位;
 *             
 * 试验步骤    : 进入函数先读取状态状态寄存器，判断是如果是
 *                    内部看门狗 --- 不操作LED
 *                    外部看门狗 --- LED2 亮(橙色)
 *                    power reset--- LED1 亮(白色)
 *               然后设置一段时间后使能外部看门狗；
 * 结论        : 外部看门狗产生不会复位状态寄存器的数值；
 */
static void __test_ETWD(void)
{ 
    uchar i = 0;
    Init_GPIO();

    i = RSTS;  // 读取 电源状态状态
    
    if ((i & 0x03) == 0x02) {        // 内部看门狗
        // BAT_LED1_ON();
        // BAT_LED2_OFF();
    } else if ((i & 0x03) == 0x03){  // 外部看门狗
        BAT_LED1_OFF();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
        BAT_LED2_OFF();
    }

    ETWCFG = 0x20;  // 使能外部看门狗

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();

    EWDKEYR = 0xff;
    for(;;);
}

/**
 * 试验三内容 : 内部看门狗试验
 * 实验三现象: 橙色的led1 会先亮7s左右，然后会亮白色的，因为外部看萌狗的作用,一直复位;
 *             
 * 试验步骤    : 进入函数先读取状态状态寄存器，判断是如果是
 *                    内部看门狗 --- LED1 亮(白色)
 *                    外部看门狗 --- 不操作LED
 *                    power reset--- LED2 亮(橙色)
 *               然后设置内部看门狗；
 * 结论        : 内部看门狗产生不会复位状态寄存器的数值；
 */
static void __test_ITWD(void)
{ 
    uchar i = 0;
    
    EnableInternalWDT();
    Init_GPIO();

    BAT_LED1_OFF();
    BAT_LED2_OFF();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();

    i = RSTS;


    if ((i & 0x03) == 0x02) {        // 内部看门狗
        BAT_LED1_ON();
        BAT_LED2_OFF();
    } else if ((i & 0x03) == 0x03){  // 外部看门狗
    } else {
        BAT_LED1_OFF();
        BAT_LED2_ON();
    }
    InternalWDTNow();
    for(;;);
}

#endif



ECReg	SPCTRL4	    _at_ 0x201C;	// PG 状态寄存器

#if 0
/**
 * 试验五内容  : 验证power good 功能
 * 实验五现象  : 开机先常亮两个灯，一段时间熄灭，这个表示程序启动正常；
 *               之后会产生一亮一灭的效果表示power good 没有被使能成功；
 *             
 * 试验步骤    :  (1) 使能 power good   ====>   GCR5 |= 0x04;
 *                (2) 使能检测引脚为 GPIOE0，并使能GPIOE0位GPO模式;
 *                (3) 配置 GPB5-7, GPJ1，(GPH0-6) 状态为GPO模式;
 *                (4) 配置 GPB5-7, GPJ1，(GPH0-6) 状态为GPO1模式;
 *                (5) 做测试GPIOE0的电平翻转;
 * 
 * 结论        : 
 */
static void __test_power_good(void)
{
    uchar i_data = 0;

    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();

    BAT_LED1_ON();
    BAT_LED2_ON();

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay(); 
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();



    BAT_LED1_OFF();
    BAT_LED2_OFF();

    i_data = SPCTRL4;

    // 判断状态 如果状态为1表示这次复位为 power good引起的复位，就不进行状态操作
    if((i_data & 0x01) == 0x01) {
        
        BAT_LED2_ON();
    } else {

        // 第一步: 使能 power good
        GCR5 |= 0x04;

        // 第二步： 使能检测引脚为 GPIOE0，并使能GPIOE0 位GPO模式
        GCR6  |= 0x20;

        GPCRE0 = 0x40;  // 这个引脚默认为80，GPI模式， 设置GPE0 为GPO 模式

        // 第三步：配置 GPB5-7, GPJ1，(GPH0-6) 状态为GPO模式
        // GPB5-7 : 161D - 161F
        // GPJ1   : 1658
        // GPH0-6 : 1648 - 164E
        GPCRB5 = 0x40;
        GPCRB6 = 0x40;
        GPCRB7 = 0x40;

        GPCRJ1 = 0x40;

        GPCRH0 = 0x40;
        GPCRH1 = 0x40;
        GPCRH2 = 0x40;
        GPCRH3 = 0x40;
        GPCRH4 = 0x40;
        GPCRH5 = 0x40;
        GPCRH6 = 0x40;

        // 第四步：配置 GPB5-7, GPJ1，(GPH0-6) 状态为GPO1模式
        // GPB5-7 : 1602 (bit5-7)
        // GPJ1   : 160A (bit1)
        // GPH0-6 : 1608 (bit0-6)
        GPDRB |= 0xE0;
        GPDRB |= 0x20;
        GPDRB |= 0x7F;


        // 第五步: 做测试IO的电平翻转
        GPDRE &= 0xfE;  // 电平为0

        __1s_delay();
        __1s_delay();

        GPDRE |= 0x01;  // 电平为1

        __1s_delay();
        __1s_delay();

        GPDRE &= 0xfE;  // 电平为0

        __1s_delay();
        __1s_delay();

        GPDRE |= 0x01;  // 电平为1
        
        __1s_delay();
        __1s_delay();

    }
    
    i_data = SPCTRL4;

    if((i_data & 0x01) == 0x01) {
        BAT_LED1_ON();
        for(;;);
    }
    
    for(;;)
    {
        __1s_delay();
        __1s_delay();
        __1s_delay();
        __1s_delay();
        BAT_LED1_ON();
        BAT_LED2_OFF();

        __1s_delay();
        __1s_delay();
        __1s_delay();
        __1s_delay();
        BAT_LED1_OFF();
        BAT_LED2_ON();
    };
}

//  现象为先亮橙色灯(LED2)， 在亮白色灯(LED3)
//  说明GPB5 先是低电平，配置之后为高电平
void __test_GPIO_GFLE(void)
{
    uchar i_status = 0;
    uchar j_status = 0;
    uchar h_status = 0;
    uchar i_data   = 0;

    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();

    BAT_LED1_ON();
    BAT_LED2_ON();

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay(); 
    __1s_delay();
    __1s_delay();


    BAT_LED1_OFF();
    BAT_LED2_OFF();



    // 测试
    // for(;;);


    // 第一步：设置 1600 = 0x84
    // 
    GCR = 0x84;

    // 第二步：读取GPB5 状态 1602
    i_status = GPDRB;

    if(IS_MASK_SET(i_status, BIT5)){    // GPB5 是否为高电平
        BAT_LED1_ON();
    } else {                            // GPB个为低电平
        BAT_LED2_ON();
    }

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay(); 
    __1s_delay();
    __1s_delay();

    // 延时一段时间熄灭
    BAT_LED1_OFF();
    BAT_LED2_OFF();

    // 控制GPD2引脚高电电平到低电平变化
    // 162A 设置为输出模式并且为高电平，这个是为了保持外部电平为高电平
    // 然后设置GPD2 为复用模式之后
    GPCRD2 = 0x40;
    GPDRD  = 0x37;

    __1s_delay();
    // 执行高电平到低电平的跳变
    GPCRD2 = 0x04;
    __1s_delay();
    GPCRD2 = 0x02;

    // 延时一段时间读取GPB5 状态
    __1s_delay();
    j_status = GPDRB;

    if(IS_MASK_SET(j_status, BIT5)){
        BAT_LED1_ON();
    } else {
        BAT_LED2_ON();
    }

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay(); 
    __1s_delay();
    __1s_delay();

    // 延时一段时间熄灭
    BAT_LED1_OFF();
    BAT_LED2_OFF();



    // 到这里为止，GPB5 为高电平，现在 修改GPB5 电平为低电平
    GPDRB = j_status & (~(BIT5));
    __1s_delay();

    // 读取GPB5 状态
    i_data = GPDRB;
    __1s_delay();

    // 如果有 写0成功 亮白色灯，否则亮橙色灯
    if(IS_MASK_SET(i_data, BIT5)){
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay(); 
    __1s_delay();
    __1s_delay();

    // 延时一段时间熄灭
    BAT_LED1_OFF();
    BAT_LED2_OFF();

    // 读取GPB5 状态
    i_data = GPDRB;
    __1s_delay();

    // 如果有 写0成功 亮白色灯，否则亮橙色灯
    // 判断 BIT5 是否为1
    if(IS_MASK_SET(i_data, BIT5)){
        BAT_LED2_ON();  // 橙色
    } else {
        BAT_LED1_ON();  // 白色
    }

    for(;;);

}

#endif




#if 1
// 程序进入为 idle 模式， 通过开机按钮唤醒
void __idle_to_wakeup(void)
{
    
    // 只是写一个标志位而已
    (*(volatile unsigned char xdata *) 0x401) = 0x55;

    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();
    
    BAT_LED1_OFF();
    BAT_LED2_OFF();

	// Init_Timers();
    // 关总中断
	DisableAllInterrupt();

    //*************************************************************************
	// Set Wake up pin -> alt function
	//*************************************************************************
	GPCRE4 = ALT;			// pwrsw to alternate pin
    GCR10 = 0x01;
	GCR8 = 0x10;

	WUEMR2 |= 0x20;         //  设置边缘触发方式
	WUESR2 |= 0x20;			//  清除 电源按键唤醒中断状态并使能
	WUENR2 |= 0x20;  
	ISR1 |= Int_WKO25;		// 清除 int14 for  pwrsw
	IER1 |= Int_WKO25;		// 使能 int14 for  pwrsw


    // EX1=1;					// enable external 1 interrupt 
	// EnableAllInterrupt();

    _nop_();
	_nop_();
    _nop_();
	_nop_();

	InitEnableInterrupt();

    PCON=1;      		// enter idle mode

    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();

	Init_GPIO();
	GPCRE4 = INPUT; 		// pwrsw to alternate pin



    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();


    
    BAT_LED2_ON();  // 橙色

    for(;;);
}

// 程序进入为 doze 模式， 通过开机按钮唤醒
void __doze_to_wakeup(void)
{
    // 只是写一个标志位而已
    (*(volatile unsigned char xdata *) 0x401) = 0x55;

    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();

    GCR10 = 0x01;
	GCR8 = 0x10;
	
    // 关总中断
	DisableAllInterrupt();

    //*************************************************************************
	// Set Wake up pin -> alt function
	//*************************************************************************
	GPCRE4 = ALT;			// pwrsw to alternate pin
	WUEMR2 |= 0x20;         //  设置边缘触发方式
	WUESR2 |= 0x20;			//  清除 电源按键唤醒中断状态并使能
	WUENR2 |= 0x20;  
	ISR1 |= Int_WKO25;		// 清除 int14 for  pwrsw
	IER1 |= Int_WKO25;		// 使能 int14 for  pwrsw


    EX1=1;					// enable external 1 interrupt 
	EnableAllInterrupt();

    _nop_();
	_nop_();
    _nop_();
	_nop_();

	// InitEnableInterrupt();

    PLLCTRL = 0x00;
    PCON    = 2;      		// enter idle mode

    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();

	Init_GPIO();
	GPCRE4 = INPUT; 		// pwrsw to alternate pin

    BAT_LED1_ON();  // 白色

    for(;;);
}




// 程序进入为 deep doze 模式， 通过开机按钮唤醒
void __deepdoze_to_wakeup(void)
{
    // 只是写一个标志位而已
    (*(volatile unsigned char xdata *) 0x401) = 0x55;

    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();

    GCR10 = 0x01;
	GCR8 = 0x10;
	
    // 关总中断
	DisableAllInterrupt();

    //*************************************************************************
	// Set Wake up pin -> alt function
	//*************************************************************************
	GPCRE4 = ALT;			// pwrsw to alternate pin
	WUEMR2 |= 0x20;         //  设置边缘触发方式
	WUESR2 |= 0x20;			//  清除 电源按键唤醒中断状态并使能
	WUENR2 |= 0x20;  
	ISR1 |= Int_WKO25;		// 清除 int14 for  pwrsw
	IER1 |= Int_WKO25;		// 使能 int14 for  pwrsw


    EX1=1;					// enable external 1 interrupt 
	EnableAllInterrupt();

    _nop_();
	_nop_();
    _nop_();
	_nop_();

	// InitEnableInterrupt();

    PLLCTRL = 0x03;
    PCON    = 2;      		// enter idle mode

    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();

	Init_GPIO();
	GPCRE4 = INPUT; 		// pwrsw to alternate pin

    BAT_LED2_ON();  // 橙色

    for(;;);
}

#endif

#if 1

// 程序进入为 sleep 模式， 通过开机按钮唤醒
void __sleep_to_wakeup(void)
{


    
    Core_Init_ClearRam();
    Init_ClearRam();
     SP = 0xC0;					// Setting stack pointer
    Init_GPIO();
    GCR10 = 0x01;
	GCR8 = 0x10;
	
    BAT_LED2_ON();
    // // 关总中断
	DisableAllInterrupt();

    // //*************************************************************************
	// // Set Wake up pin -> alt function
	// //*************************************************************************
	GPCRE4 = ALT;			// pwrsw to alternate pin
	WUEMR2 |= 0x20;         //  设置边缘触发方式
	WUESR2 |= 0x20;			//  清除 电源按键唤醒中断状态并使能
	WUENR2 |= 0x20;  
	ISR1 |= Int_WKO25;		// 清除 int14 for  pwrsw
	IER1 |= Int_WKO25;		// 使能 int14 for  pwrsw


    EX1=1;					// enable external 1 interrupt 
	EnableAllInterrupt();

    PLLCTRL = 0x01;
    PCON    = 2;      		

    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();
    _nop_();
	_nop_();

	Init_GPIO();
	GPCRE4 = INPUT; 		// pwrsw to alternate pin

    BAT_LED1_ON();  // 橙色

    for(;;);
}


#endif

#if 0
void __test_bram1(void)
{
    unsigned char i = 0;
    unsigned char j = 0;

    // // 初始化默认的GPIO功能（主要是LED）
     Init_GPIO();

    i = BRAM_OEM[40];

    BRAM_OEM[40] = 0x00;

    j = BRAM_OEM[40];

    if( j == 0x00) {
        BAT_LED1_ON();
    } else {
        BAT_LED2_ON();
    }

    for(;;);
    // for(;;) {
    //     //  BAT_LED2_ON();  // 橙色
    // };
}

#endif



void __test_dac_pin_invert()
{
    Core_Init_ClearRam();
    Init_ClearRam();

	SP = 0xC0;					// Setting stack pointer
    
    // DCache &= 0xFC;
    DCache |= 0x03;

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


    // DACPWRDN = 0x2F;    // 使能DAC通道4  GPJ4 DAC4
    GPCRJ4   = 0x40;    // 设置GPIOJ4 位复用模式

    for(;;){
        // GPDRJ = 0x10;  
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x00; 
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x10;  
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x00; 
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x10;  
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x00; 
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x10;  
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x00; 
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x10;  
        // _nop_();
        // _nop_(); 
        // _nop_();
        // GPDRJ = 0x00; 
        // _nop_();
        // _nop_(); 
        // _nop_();

        // GPDRJ = 0x10;  
        // GPDRJ = 0x00;
        // GPDRJ = 0x10;  
        // GPDRJ = 0x00; 
        // GPDRJ = 0x10;  
        // GPDRJ = 0x00; 
        // GPDRJ = 0x10;  
        // GPDRJ = 0x00; 
        // GPDRJ = 0x10;  
        // GPDRJ = 0x00;  

    }


#if 0
    for(;;){
        // DACDAT4  = 0xff;   
        // __1s_delay(); 
        // __1s_delay(); 
        // __1s_delay(); 
        // __1s_delay(); 
        // __1s_delay(); 
        // DACDAT4  = 0xff;    
        // __1s_delay();

       #if 1 
        DACDAT4  = 0xff;  
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_(); 
        DACDAT4  = 0x00;
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();     
        DACDAT4  = 0xff;    
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_(); 
        DACDAT4  = 0x00;    
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();       
        DACDAT4  = 0xff;     
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();   
        DACDAT4  = 0x00;       
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_(); 
        DACDAT4  = 0xff;        
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();
        DACDAT4  = 0x00;       
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();   
        DACDAT4  = 0xff;        
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();
        DACDAT4  = 0x00;      
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();  
        DACDAT4  = 0xff;       
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_(); 
        DACDAT4  = 0x00;      
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();    
        DACDAT4  = 0xff;     
        _nop_();
        _nop_(); 
        _nop_();
        // _nop_(); 
        // _nop_();
        // _nop_(); 
        // _nop_();   
        DACDAT4  = 0x00;    
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;      
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;    
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;      
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;    
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;      
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;    
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;    
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;       
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;    
        DACDAT4  = 0xff;    
        DACDAT4  = 0x00;      
        DACDAT4  = 0xff;    

        #endif
    };
#endif
}

#if 0


static void __test_flash2sram()
{
    BAT_LED2_ON(); 
    BAT_LED1_ON(); 
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    BAT_LED2_OFF(); 
    BAT_LED1_OFF(); 
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
    __1s_delay();
}

// 程序进入为 sleep 模式， 通过开机按钮唤醒
static void __change_PLL_req(void)
{
    // 只是写一个标志位而已
    (*(volatile unsigned char xdata *) 0x401) = 0x55;

    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();


    EX1=1;					// enable external 1 interrupt 
	EnableAllInterrupt();
	Init_GPIO();

    DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(__test_flash2sram);		// Load function to ram



	// SET_MASK(FBCFG,SSMC);       		// enable scatch ROM

	SCRA0L = 0x00;
	SCRA0M = 0xF8;
	SCRA0H = 0x00;

    
    __test_flash2sram();

    for(;;){
        BAT_LED2_ON();  // 橙色
        __1s_delay();
        __1s_delay();
        __1s_delay();
        __1s_delay();
        BAT_LED2_OFF();  // 橙色
        __1s_delay();
        __1s_delay();
        __1s_delay();
        __1s_delay();
    };
}


#endif




static void __test_uart_code(void)
{
    u8 __tmp = 0x00;
    SP = 0xC0;					// Setting stack pointer
    Init_ClearRam();
    Core_Initialization();
	Oem_Initialization();
    InitEnableInterrupt();


#if 1
    TASK_UART_cfg_set_base(0); 

    SET_MASK(UART1_IER, BIT1);
    for(;;){
        TASK_UART_A_set_tx_data(0x55);
        DelayXms(200);
        DelayXms(200);
        DelayXms(200);
        DelayXms(200);
        DelayXms(200);
    }
#endif
}


static void __read_flash_function(void)
{
    static u32 addr = 0x00;
    if (addr > 0x10) {
        return;
    }

    TASK_UART_A_set_tx_data(Sensor_Flash_WR(addr++,SPI_Channel));
}


static void __test_sspi_code(void)
{
    SP = 0xC0;					// Setting stack pointer
    Init_ClearRam();
    Core_Initialization();
	Oem_Initialization();
    InitEnableInterrupt();

    TASK_UART_cfg_set_base(0); 

    RSTDMMC |= 0x02;  // sspi ec side
    Enable_SPIInterface();

    for(;;) {
        __read_flash_function();

        INVERSE_REG(GPDRJ, 4);
        DelayXms(200);
    };
}

//----------------------------------------------------------------------------
// Oem_StartUp
//----------------------------------------------------------------------------
void Oem_StartUp(void)
{
    // __test_sspi_code();
    // __test_uart_code();

    // // 控制flash 读写拍数
    // SMFI_FIC_CTL0  = 0x98;
    // SMFI_FIC_CTL1  = 0x00;


    // Core_Initialization();
	// Oem_Initialization();
    // InitEnableInterrupt();

    // for(;;){

    // };

    // ITE_Flash_Utility();
    // for(;;);
    // Init_GPIO();

    // EX1=1;					// enable external 1 interrupt 
	// EnableAllInterrupt();

    // ExtWDTInit();

    // ISR3 = Int_EXTimer;             // Write to clear external timer 1 interrupt 
    // SET_MASK(IER3, Int_EXTimer);    // Enable external timer 1 interrupt 

    // ETWCTRL = 0x01;
    // BAT_LED1_ON();  // 白色
    // BAT_LED2_ON();  // 白色
    
    // for(;;);


    //  __test_speed_code();
    // for(;;);


    // u8    young_flag = 0x00;
    // // 关闭内部看门狗
    
    // u8 __young_flag;

 	// Init_ClearRam();
    //  SP = 0xC0;					// Setting stack pointer


    // WDTEB = 0;
    // Init_Timers();
    // Init_GPIO();
    // InitEnableInterrupt();

    // while(1) {
    //     if ((*(volatile unsigned char xdata *) 0x814) == 0x22) {
    //         break;
    //     }
    //     Loop_Delay(5);
    // };

    // for(;;){
    //     INVERSE_REG(GPDRC, 6);
    //     __1s_delay();
    // };

    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // __1s_delay();
    // BAT_LED2_ON();
    // __1s_delay();
    // // 第一组
    // ECINDAR3 = 0x0F;        // Enter follow mode
   	// ECINDAR2 = 0xFF;
	// ECINDAR1 = 0xFE;
   	// ECINDAR0 = 0x00;   		// FFFFExx = 0xFF   
   	// ECINDDR = 0x00;			// SCE# high level

    // Loop_Delay(3);

    // // 第二组
	// ECINDAR3 = 0x0F;        // Enter follow mode
   	// ECINDAR2 = 0xFF;
	// ECINDAR1 = 0xFD;
   	// ECINDAR0 = 0x00;   		// FFFFExx = 0xFF   
   	// ECINDDR = 0x03;			// SCE# high level

    // // 第三组
    // ECINDDR = 0x00;			// SCE# high level
    // ECINDDR = 0x00;			// SCE# high level
    // ECINDDR = 0x00;			// SCE# high level

    // // 连续读两次
    // (*(volatile unsigned char xdata *) 0x824) = ECINDDR;
    // (*(volatile unsigned char xdata *) 0x825) = ECINDDR;

    // BAT_LED1_ON();


    // while(1) {
    //     if ((*(volatile unsigned char xdata *) 0x815) == 0x11) {
    //         break;
    //     }
    //     Loop_Delay(5);
    // }

    // // BAT_LED2_ON();

    // for(;;){
    //     INVERSE_REG(GPDRC, 6);
    //     __1s_delay();
    // };


    // Oem_TriggerS5S0();
    
    // Oem_S5S0Sequence();
    // for(;;) {
    //     if (SysPowState != SYSTEM_S0) {
    //         Oem_S5S0Sequence();
    //     }
    // };
    // Init_GPIO();
    //  for(;;){
    //         INVERSE_REG(GPDRJ, 4);
    //         INVERSE_REG(GPDRC, 6);
    //         __1s_delay();
    //         __1s_delay();
    //         __1s_delay();
    //         __1s_delay();
    //         __1s_delay();
    //  };

    //   SP = 0xC0;					// Setting stack pointer

	//  Init_GPIO();

    // UART GPIO初始化
    // GPCRB0 = ALT;
    // GPCRB1 = ALT;

    // LED GPIO 初始化
 	// GPCRJ4 = OUTPUT; // 0x40 
 	// GPCRC6 = OUTPUT;
    //  for(;;) {
    //      INVERSE_REG(GPDRJ, 4);
    //      __1s_delay();
    //  }
	
    // init timer
    // Init_Timers();
    // // init uart
	// uart_Initial();

    // InitEnableInterrupt();
    // uart_printf("FIC628 say hello\n");

    // Bank1_Test();
    // Bank2_Test();
    
    // uart_printf("young_Test\n");
    // while(1);

// 	for(;;) {

//         //-----------------------------------
//         // 1 millisecond elapsed
//         //-----------------------------------
//         if(F_Service_MS_1)
//         {
//             F_Service_MS_1=0;
//             service_1mS();

//             if(young_flag >= 250) {
//                 young_flag = 0;
//             }
//             young_flag++;

//             continue;
//         }
// 	};
	
	
	//  Init_ClearRam();

    // DisableAllInterrupt();
	// SP = 0xC0;					// Setting stack pointer

    // (*(volatile unsigned char xdata *) 0x400) = 0x55;

    /** \brief 测试电源状态寄存器 */
    //   __test1_rets();

    /** \brief 测试外部看门狗 */
    //  __test_ETWD();

    /** \brief 测试内部看门狗 */
    // __test_ITWD();


    // power good 测试
    // __test_power_good();

    // GFLE 相应寄存器测试
    // __test_GPIO_GFLE();

    // idle 唤醒测试
    //   __idle_to_wakeup();

    // 瞌睡唤醒
    // __doze_to_wakeup();

    // __deepdoze_to_wakeup();

    // __sleep_to_wakeup();
// 
    // Init_ADC();

    
    // __test_bram1();


    // 测试DAC 翻转
    // __test_dac_pin_invert();


    // change PLL
    // __change_PLL_req();

    // for(;;){
    //     // IHD += 0x01;
    // }
}


// static unsigned char SpiFlash_Read_Status2()
// {
// 	unsigned char rData;
// 	sfc_cmd cmd;
//     memset(&cmd, 0,sizeof(sfc_cmd));
// 	cmd.cmd_index = 0x35;
// 	cmd.read_write = SFC_READ;
// 	cmd.cmd_mode = SFC_CMD_MODE_CMD_DATA;
// 	cmd.buf = &rData;
// 	cmd.len = 1;
// 	cmd.addr = 0;

// 	SYS_SFC_Transmit(&cmd);

// 	return rData;
// }

extern void Do_SPI_function(void);
//----------------------------------------------------------------------------
// Oem_Initialization - Initialize the registers, data variables, and oem 
// functions after kernel init. function.
//----------------------------------------------------------------------------
void Oem_Initialization(void)
{
	Init_GPIO();
	//TF_010++>>
	if(IS_BOARD_ID1_HI()) {
        EC_PWR_CTR1_ON();
    }
    
	//TF_010++<<
    #ifdef HSPI
	GPIO_HSPI_INIT();
    #endif

#if EC_MODE
    
    #ifdef SPIReadMode
    ChangeSPIFlashReadMode(SPIReadMode);   // SPIReadMode_2   SPIReadMode
    #endif

#else

    #ifdef SPIReadMode
    ChangeSPIFlashReadMode(SPIReadMode);  // SPIReadMode_2
    #endif

 #endif



    #ifdef HSRSMode
    ChangeHSRSMode(HSRSMode);
    #endif

    #ifdef PLLFrequency

    // fpga 验证的时候不要使用，因为进入sleep之后就不能唤醒了  young
    ChangePLLFrequency(PLLFrequency);
    #endif

    #ifdef PECI_Support
    Init_PECI();
    #endif

	Init_Regs();

    #ifdef SMBusChannel4Support
    InitSMBusChannel4();
    #endif
	Init_SMBus_Regs();
    
    #if ADCFuncSupport    
	Init_ADC();
    #endif

	// Init_Cache();
	Init_PS2Port();
    
    #ifdef SysMemory2ECRam	
	InitSysMemory2ECRam();
    #endif

	//Label:BLD_TIPIA_001
	#if _8S_Reset_Support
	GCR10 = 0x01;
	GCR8 = 0x10;
	#endif

	
    InitSMBus();

    // NACk 硬件处理
    SMB_FIC_CTRL1 |= 0x40; 


    ResetSCIEvent();
	Init_OEMVariable();

	if(ExtendScanPin==0x02)		// KSO16 and KSO17 are used.
	{  
		if(ExternMatrixGPO)
		{
			ExtendScanPin++;
		}
	}

    // EnableInternalWDT();

	ExtWDTInit();	

    // ISR3 = Int_EXTimer;             // Write to clear external timer 1 interrupt 
    // SET_MASK(IER3, Int_EXTimer);    // Enable external timer 1 interrupt 

	InitThermalChip();  // 98

	#if Support_ANX7447
	ucsi_init();
	#endif

	Warning_flag = 0xFF;	//TF_004++
}

//----------------------------------------------------------------------------
// The function of init. registers 
//----------------------------------------------------------------------------
//const struct REG_INIT_DEF code reg_init_table[] = 
const sREG_INIT_DEF code reg_init_table[] = 
{
        { &FMSSR 		,Init_FMSSR         }, 	// share rom size
// HOST interface
    	{ &SPCTRL1      ,Init_I2EC+0x80          },  // Enable I2EC R/W
    	{ &BADRSEL      ,Init_BADR          },  // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define
    	{ &SWCBALR      ,Init_SWCBALR       },
    	{ &SWCBAHR      ,Init_SWCBAHR       },
		{ &RSTS			,0x84				},
//        { &GCR1         ,0x05               },

// KBC and PM interface
		{ &KBIRQR 		,0x00              	}, 	// Disable KBC IRQ
        { &KBHICR 		,IBFCIE+PM1ICIE     }, 	// KBC port control IBFCIE+PMICIE
//        { &PM1CTL		,IBFIE+SCINP        }, 	// EC port control  IBFCIE+SCI low active
//       { &PM2CTL 		,IBFIE+SCINP        }, 	// EC port2 control IBFCIE+SCI low active  
// KBC and PM3 interface
        #ifdef PMC3_Support
        { &PM3CTL 		,IBFIE         	    }, 	// PMC3 input buffer full interrupt enable
        #endif	

// PS2
        { &PSCTL1 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL2 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL3 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
		{ &PSINT1		,0x04				}, 	// Transation Done,Start Clock Interrupt
        { &PSINT2		,0x04				},	// Transation Done,Start Clock Interrupt 
        { &PSINT3		,0x04				},	// Transation Done,Start Clock Interrupt 

// Key Scan
        { &KSOCTRL   	,KSOOD + KSOPU      },	//
  		{ &KSICTRL   	,KSIPU       		},	//
	
// ADC								
  		{ &ADCSTS    	,AINITB             }, 	// Enable Analog accuracy initialization
        //{ &ADCSTS    	,0                 	}, 	// Stop adc accuracy initialization
        { &ADCSTS    	,0x80          		}, 	// Stop adc accuracy initialization
		{ &ADCCFG    	,0         			}, 	//
        { &KDCTL     	,AHCE              	}, 	// Enable Hardware Callibration
		{ &ADCCFG    	,DFILEN  		    },	// Enable Digital Filter enable,
		{ &ADCCTL		,0x15				},

// DAC
        { &DACPWRDN  	,0x00              	}, 	//

//PWM
//========================================================================================
// Setp 1, Group Main Clock Select
//	PCFSi	@ PCFSR    bit 0-3	   PCFSR[0-3]	 = 06h = 0110b
//	G6MSELi @ CLK6MSEL bit 0-3	   CLK6MSEL[0-3] = 00h = 0b
//
//	Group  {G6MSELi, PCFSi}   Value    Main Clock
//	  0    {G6MSEL0, PCFS0}   00	   32.768kHz
//	  1    {G6MSEL1, PCFS1}   01	   9.2MHz
//	  2    {G6MSEL2, PCFS2}   01	   9.2MHz
//	  3    {G6MSEL3, PCFS3}   00	   32.768kHz
//
//========================================================================================
// Setp 2, Group Main clock fractional frequency
// Group		 Prescaler		  Value 	Group Clock
//	 0		C0CPRS				[00]		G0=32768/((0+1)*(63+1)) 	 = 512Hz
//	 1		C4MCPRS   C4CPRS	[00,05] 	G1=9200000/((05+1) *(63+1))  = 23958.33Hz
//	 2		C6MCPRS   C6CPRS	[00,8F] 	G2=9200000/((143+1)*(63+1))  = 998.26Hz
//	 3		C7MCPRS   C7CPRS	[00,00] 	G3=32768/((0+1)*(63+1)) 	 = 512Hz
//
//	CTR0 is 0x3F, and CTR1/CTR2/CTR3 is not write
//========================================================================================
// Setp 3, Channel Select Group Clock

//	Select		Prescaler	 Group Clock
//	 0 0	C0CPRS			  G0
//	 0 1	C4MCPRS  C4CPRS   G1
//	 1 0	C6MCPRS  C6CPRS   G2
//	 1 1	C7MCPRS  C7CPRS   G3
//
//						Channel: C7 C6 C5 C4 C3 C2 C1 C0
// [PCSSGH,CCSSGL] = [00,01]h = [00 00 00 00 00 00 00 01]b
//						  Group: G1 G0 G0 G0 G0 G2 G0 G0
//========================================================================================
//According to the mentioned, Set PWM
//channel 2: Beep		-----> G2	 1KHz
//channel 4: blacklight -----> G0	 512Hz
//channel 7: Fan		-----> G1	 24KHz
//=========================================================================================
		{ &ZTIER        ,0x00       		},   // Disable
        { &CTR      	,0x3F      		    },	
		{ &C4CPRS    	,0x05				},	 // Fan = 24K HZ
		{ &C4MCPRS	    ,0x00				},   //
		{ &C6CPRS    	,0x8F				},	 // Beep =1KHz
		{ &C6MCPRS		,0x00				},	 //
		{ &C7CPRS    	,0x00				},	 // 
		{ &C7MCPRS		,0x00				},   //
		{ &PCFSR        ,0x8A      		    },	
        { &PCSSGL       ,0x00      		    },   // Select channel 0-3 Group
		{ &PCSSGH       ,0x41				},	
		{ &ZTIER        ,0x02       		},   // Enable
        { &DCR0         ,0x00      		    },   // Default 
        { &DCR4         ,0x00      		    },   // Default 
        { &DCR7         ,0x00      			},   // Default

		{&PWM1LCR1		,0x30				},
		{&PWM1LCR2		,0x22				},		
		{&PWM1LHE		,0x00				},
};


void Init_Regs(void)
{
	BYTE index = 0x00;
    while(index < (sizeof(reg_init_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = reg_init_table[index].address;
		*Tmp_XPntr = reg_init_table[index].initdata;
        index ++;
    }
}

//const struct REG_INIT_DEF code Init_SMBus_table[] = 
const sREG_INIT_DEF code Init_SMBus_table[] = 
{
// SMBus   100K 

	    { &SMB4P7USL	, 0x28				},	// 100K	
	    { &SMB4P0USH  	, 0x25      		},  
        { &SMB300NS     , 0x03      		},  
        { &SMB250NS     , 0x02      		},   
        { &SMB25MS      , 0x19      		},   
        { &SMB45P3USL   , 0xA5      		},  
        { &SMBS4P3USH   , 0x01      		},   
        { &SMB4P7A4P0H	, 0x00      		},  


/*
	    { &SMB4P7USL	, 0x71				},	// 20K	
	    { &SMB4P0USH  	, 0xdd      		},  
        { &SMB300NS     , 0x03      		},  
        { &SMB250NS     , 0x71      		},   
        { &SMB25MS      , 0x19      		},   
        { &SMB45P3USL   , 0x5c      		},  
        { &SMBS4P3USH   , 0x01      		},   
        { &SMB4P7A4P0H	, 0x00      		},  
*/

        { &HOCTL2_A 	, 0x01      		},  
        { &HOCTL_A   	, 0x03      		},  
        { &HOCTL_A  	, 0x01      		},  
        { &HOSTA_A    	, 0xFF      		},  
        
        { &HOCTL2_B   	, 0x01      		},  
        { &HOCTL_B    	, 0x03      		},	
        { &HOCTL_B    	, 0x01      		},	
        { &HOSTA_B    	, 0xFF      		},	
        
    	{ &HOCTL2_C		, 0x01				},	 
   	 	{ &HOCTL_C		, 0x03				},	 
   		{ &HOCTL_C		, 0x01				},	 
    	{ &HOSTA_C		, 0xFF				},
            
        #ifdef SMBusChannel4Support
    	{ &HOCTL2_D		, 0x01				},	 
   	 	{ &HOCTL_D		, 0x03				},	 
   		{ &HOCTL_D		, 0x01				},	 
    	{ &HOSTA_D		, 0xFF				},
        #endif
};

void Init_SMBus_Regs(void)
{
	BYTE index = 0x00;
    while(index < (sizeof(Init_SMBus_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_SMBus_table[index].address;
		*Tmp_XPntr = Init_SMBus_table[index].initdata;
        index ++;
    }
}

//----------------------------------------------------------------------------
// The function of clearing external ram for OEM code
// Clear external ram (0x100~0xFFF)
//----------------------------------------------------------------------------
void Init_ClearRam(void)
{
    // u16 i = 0;
	PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr=0x100;
    while(byte_register_pntr<0x1000)// Clear external ram (0x100~0xFFF)
    {   
        // i++;
        *byte_register_pntr=0;
        byte_register_pntr ++;
    }

    // (*(volatile unsigned char xdata *) 0x803) = (i >> 8) & 0xff;
    // (*(volatile unsigned char xdata *) 0x804) = i & 0xFF;
}

//----------------------------------------------------------------------------
// The function of DMA for scratch sram
//----------------------------------------------------------------------------
const sDMAScratchSRAM code asDMAScratchSRAM[]=    // For 8500 Dino
{
	{	&SCRA1H,	&SCRA1M,	&SCRA1L	},		// 1024 bytes (externl ram 0x800 ~ 0xBFF)
	{	&SCRA2H,	&SCRA2M,	&SCRA2L	},		// 512 bytes  (externl ram 0xC00 ~ 0xDFF)
	{	&SCRA3H,	&SCRA3M,	&SCRA3L	},		// 256 bytes  (externl ram 0xE00 ~ 0xEFF)
	{	&SCRA4H,	&SCRA4M,	&SCRA4L	}		// 256 bytes  (externl ram 0xF00 ~ 0xFFF)

};
void  CacheDma(BYTE sramnum,WORD addr)
{
	*asDMAScratchSRAM[sramnum].scarh = 0x80;
	*asDMAScratchSRAM[sramnum].scarm = (WORD) addr >> 8;   	// high byte of function address
	*asDMAScratchSRAM[sramnum].scarl = (WORD) addr & 0xff;	// low byte of function address
	*asDMAScratchSRAM[sramnum].scarh = 0x00;	// start cache dma     			
}

//----------------------------------------------------------------------------
// Init. DMA for scratch sram
//----------------------------------------------------------------------------
void Init_Cache(void)
{
#ifdef ITE8500					// Dino For 8500 no cache ram 0x800 ~ 0xFFF

#else
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        CacheDma(3, HSPI_RamCode);  // Cache to memory 0xF00 ~ 0xFFF
        #endif
    #endif
#endif

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

//----------------------------------------------------------------------------
// Select touch pad, mouse, and keyboard port number
//----------------------------------------------------------------------------
void Init_PS2Port(void)
{

}

//----------------------------------------------------------------------------
// Function Name : Init_OEMVariable
// Purpose : setup default variable when EC reset
//----------------------------------------------------------------------------
void Init_OEMVariable(void)
{
	Oem_GPU_EC_BLK = Oem_GPU_BLK + Oem_EC_BLK;

	LED_FLASH_CNT = 0x0001;	// for LED control

	ECMainVersionInfo = OEM_Version_MSB;    // OEM_Version_MSB
	VCMD_Lenovo   = OEM_Version_MSB;
	ECVersionInfo = OEM_Version_LSB;
	ECVersionPCB = OEM_Version_PCB;
	
	PECI_PowerCtrlStep = 0x01;

	Device_Status_Lenovo |= Wireless_S_B;
	Device_Status_Lenovo |= Bluetooth_S_B;
	Device_Status_Lenovo |= Inverter_S_B;
	Device_Status_Lenovo |= Camera_S_B;	

	Oem_Device_Status |= Wireless_IN;
	Oem_Device_Status |= Bluetooth_IN;
	Oem_Device_Status |= Inverter_IN;
	Oem_Device_Status |= Camera_IN;

	Oem_Globe_Flag2 = 0;
	SysPostTime = 0;
	
    
	SysPowState=SYSTEM_S5;		

	//TF_014++>> 
	if(BRAM[63]==0x55)
	{
		BRAM[63]=0x00;
		CLEAR_MASK(KBHISR,SYSF);
        Ccb42_SYS_FLAG=0;
		DelayDoPowerSeq=250;
		Oem_TriggerS5S0();
	}
	//TF_014++<<
	
	if(Read_ACIN())
	{
		BAT1_STATUS |= OS_AC_IN;
		POWER_FLAG1	|= adapter_in;
		ECQEvent(AC_HOT_PLUG_EVT,SCIMode_Normal);
	}
	RamDebug(0x30);
	Hook_EnablePS2Port_0();
	
}

/*-----------------------------------------------------------------------------
 * @subroutine - ucsi_ppm_notify_opm
 * @function - ucsi_ppm_notify_opm
 * @Upstream - By call
 * @input    -
 * @return   -
 * @note     -
 *---------------------------------------------------------------------------*/
void ucsi_ppm_notify_opm(void)
{
    /* Generate SCI/Q-event to notify the OPM. */
    RamDebug(0x79);
    RamDebug(xUCSI_DS_CCI3);
    RamDebug(xUCSI_DS_CCI2);
    RamDebug(xUCSI_DS_CCI1);
    RamDebug(xUCSI_DS_CCI0);
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      Before jump to main function [WinFlashMark = 0x33;] is necessary.
//----------------------------------------------------------------------------
void Hook_ECExitFollowMode(void)
{
    Init_Cache();
    
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        SET_MASK(IER7,Int_DeferredSPI); // Enable HSPI interrupt
        #endif
    #endif 
    
    InitSMBus();
    
    #if Insyde_Bios
    if(RamCodePort==0x64)   // for insyde bios
    {
        KBHIKDOR = 0xFA;
    }
    else if(RamCodePort==0x66)
    {
	    PM1DO = 0xFA;
    }	
    else if(RamCodePort==0x6C)
    {
	    PM2DO = 0xFA;
    }  
    #endif
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      1. Before jump to main function if want to keep EC setting [return(0x33);] is necessary.
//      2. If you don't understand the use of Hook_ECRetunrMainFuncKeepCondition function, 
//          don't change anything.
//      3. Always at bank0 (0x9000)
//----------------------------------------------------------------------------
BYTE Hook_ECRetunrMainFuncKeepCondition(void)
{
    if(WinFlashMark==0x33)
    {
        return(0x33);
    }
    else
    {
        return(0x00);
    }
}
