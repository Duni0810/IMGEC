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
    Delay1MS(200);
    Delay1MS(200);
    Delay1MS(200);
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

    Init_GPIO();

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

    i = RSTS;


    if ((i & 0x03) == 0x02) {        // 内部看门狗
        BAT_LED1_ON();
        BAT_LED2_OFF();
    } else if ((i & 0x03) == 0x03){  // 外部看门狗
        // BAT_LED1_OFF();
        // BAT_LED2_ON();
    } else {
        BAT_LED1_OFF();
        BAT_LED2_ON();
        // BAT_LED1_OFF();
        // BAT_LED2_OFF();
    }
    InternalWDTNow();
    for(;;);
}

XBYTE test_rdata1	_at_(0x0430 + 0); 
XBYTE test_rdata2	_at_(0x0430 + 1); 
XBYTE test_rdata3	_at_(0x0430 + 2); 
XBYTE test_rdata4	_at_(0x0430 + 3); 
XBYTE test_rdata5	_at_(0x0430 + 4); 
XBYTE test_rdata6	_at_(0x0430 + 5); 
XBYTE test_rdata7	_at_(0x0430 + 6); 
XBYTE test_rdata8	_at_(0x0430 + 7); 
XBYTE test_rdata9	_at_(0x0430 + 8); 
XBYTE test_rdataa	_at_(0x0430 + 9); 
XBYTE test_rdatab	_at_(0x0430 + 10); 
XBYTE test_rdatac	_at_(0x0430 + 11); 

#define __UNEQUAL(reg, data)   (FBCFG != data)

// 这个得保留测试, 发现可能有好多不大一样
static void __test_SMFI(void)
{
    test_rdata1 = FBCFG;
    test_rdata2 = FPCFG;
    test_rdata3 = HSPICTRL3R;
    test_rdata4 = HINSTC2;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x3f) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    FBCFG       = 0x80;
    FPCFG       = 0xff;
    HSPICTRL3R  = 0x70;
    HINSTC2     = 0x0f;
}


// intc 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_INTC(void)
{
    test_rdata1 = IER0;
    test_rdata2 = IER1;
    test_rdata3 = IPOLR0;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    IER0       = 0xff;
    IER1       = 0xff;
    IPOLR0     = 0xff;
}

// EC2I 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_EC2I(void)
{
    test_rdata1 = IHIOA;
    test_rdata2 = IHD;
    test_rdata3 = LSIOHA;
    test_rdata4 = IBMAE;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    IHIOA      = 0xff;
    IHD        = 0xff;
    LSIOHA     = 0xff;
    IBMAE      = 0x05;
}

// KBC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_KBC(void)
{
    test_rdata1 = KBHICR;

    // 判断状态
    if((test_rdata1 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    KBHICR      = 0x0f;
}


// SWUC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_SWUC(void)
{
    // test_rdata1 = SWCBALR;
    // test_rdata2 = SWCBAHR;
    test_rdata3 = SWCIER;
    test_rdata4 = SWCHIER;

    // 判断状态
    if((test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    // SWCBALR    = 0xfE;
    // SWCBAHR    = 0xff;
    SWCIER     = 0xff;
    SWCHIER    = 0xCB;
}


// PMC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_PMC(void)
{
    test_rdata1 = PM1CTL;
    test_rdata2 = PM1IE;
    test_rdata3 = MBXCTRL;
    test_rdata4 = PM3CTL;

    // 判断状态
    if((test_rdata1 != 0x40) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    PM1CTL   = 0x43;
    PM1IE    = 0x3f;
    MBXCTRL  = 0xE0;
    PM3CTL   = 0x03;
}

// PS2 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_PS2(void)
{
    test_rdata1 = PSCTL1;
    test_rdata2 = PSINT1;
    test_rdata3 = PSDAT1;

    // 判断状态
    if((test_rdata1 != 0x01) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    PSCTL1 = 0x1F;
    PSINT1 = 0x0F;
    PSDAT1 = 0xFF;
}


// PWM 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_PWM(void)
{
    test_rdata1 = C0CPRS;
    test_rdata2 = CTR;
    test_rdata3 = PWMPOL;
    test_rdata4 = ZTIER;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0xFF) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    C0CPRS  = 0xFF;
    CTR     = 0x00;
    PWMPOL  = 0xFF;
    ZTIER   = 0x03;
}


ECReg	VCMP0CTL       	_at_ 0x1946;	
ECReg	VCMPLR       	_at_ 0x1952;	

// ADC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_ADC(void)
{
    test_rdata1 = ADCCFG;
    test_rdata2 = ADCCTL;
    test_rdata3 = VCMP0CTL;
    test_rdata4 = VCMPLR;

    // 判断状态
    if((test_rdata1 != 0x80) || (test_rdata2 != 0x15) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    ADCCFG      = 0xF5;
    ADCCTL      = 0xBF;
    VCMP0CTL    = 0xFF;
    VCMPLR      = 0x07;
}

// DAC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_DAC(void)
{
    test_rdata1 = DACPWRDN;

    // 判断状态
    if((test_rdata1 != 0x3F)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    DACPWRDN      = 0x03;
}


// WUC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_WUC(void)
{
    test_rdata1 = WUEMR1;
    test_rdata2 = WUENR1;
    test_rdata3 = WUENR3;
    test_rdata4 = WUEMR6;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    WUEMR1    = 0xFF;
    WUENR1    = 0xFF;
    WUENR3    = 0xFF;
    WUEMR6    = 0xFF;
}


// SMBus 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_SMB(void)
{
    test_rdata1 = HOCMD_A;
    test_rdata2 = TRASLA_B;
    test_rdata3 = NDHB_A;
    test_rdata4 = SICR_A;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    HOCMD_A   = 0x0F;
    TRASLA_B  = 0xFF;
    NDHB_A    = 0x0F;
    SICR_A    = 0xFC;
}


// KBS 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_KBS(void)
{
    test_rdata1 = KSOL;
    test_rdata2 = KSOCTRL;
    test_rdata3 = KSIGCTRL;
    test_rdata4 = KSOLGOEN;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    KSOL        = 0x3F;
    KSOCTRL     = 0xFF;
    KSIGCTRL    = 0xFF;
    KSOLGOEN    = 0xFF;
}


// ECPM 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_ECPM(void)
{
    test_rdata1 = CGCTRL2R;
    test_rdata2 = AUTOCG;
    test_rdata3 = PLLSSCR;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x70) || (test_rdata3 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    CGCTRL2R   = 0x70;
    AUTOCG     = 0x7F;
    PLLSSCR    = 0x07;
}

// ETWD 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test1_ETWD(void)
{
    test_rdata1 = ETWCFG;
    test_rdata2 = ETPSR;
    test_rdata3 = ET2PSR;
    test_rdata4 = EWDCNTHR;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) || (test_rdata4 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    ETWCFG      = 0x20;
    ETPSR       = 0x02;
    ET2PSR      = 0x03;
    EWDCNTHR    = 0xFF;
}


// GCTRC 功能测试
// 现象是：开始一段时间不亮，相当于一开始是默认参数；等第一次看门狗复位之后，
// 先亮LED1,在亮LED2,最后两个一直亮，知道看门狗复位；
static void __test_GCTRC(void)
{
    test_rdata1 = RSTDMMC;
    test_rdata2 = BADRSEL;
    test_rdata3 = BINTADDR0R;

    // 判断状态
    if((test_rdata1 != 0x13) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();

        if (test_rdata1 != 0x13) {
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            BAT_LED1_ON();
        }

        if (test_rdata2 != 0x00) {
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            BAT_LED2_ON();
        }

        if (test_rdata3 != 0x00) {

            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            __1s_delay();
            BAT_LED1_OFF();
            BAT_LED2_OFF();
            BAT_LED1_ON();
            BAT_LED2_ON();
        }


    } else {
        // BAT_LED1_ON();
    }

    RSTDMMC      = 0x1F;
    BADRSEL      = 0x03;
    BINTADDR0R   = 0xff;
}


// EGPC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test1_EGPC(void)
{
    test_rdata1 = ECNT;
    test_rdata2 = EDAT;
    test_rdata3 = EADDR;

    // 判断状态
    if((test_rdata1 != 0x11) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    ECNT      = 0x1f;
    EDAT      = 0xFF;
    EADDR     = 0xFF;
}


ECReg	__BATT_RAM1       	_at_ 0x2201;	
ECReg	__BATT_RAM2       	_at_ 0x2203;

// Batt 功能测试
// 不受控，橙色灯，而且掉电数据也不丢失
static void __test_Batt(void)
{
    test_rdata1 = __BATT_RAM1;
    test_rdata2 = __BATT_RAM2;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    __BATT_RAM1      = 0xFf;
    __BATT_RAM2      = 0xFF;
}


// CIR 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_CIR(void)
{
    test_rdata1 = C0MSTCR;
    test_rdata2 = C0IER;
    test_rdata3 = C0CFR;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x0B) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    C0MSTCR      = 0xFC;
    C0IER        = 0xC7;
    C0CFR        = 0x00;
}


// SSPI 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_SSPI(void)
{
    test_rdata1 = SPICTRL1;
    test_rdata2 = SPICTRL2;
    test_rdata3 = SPICTRL3;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    SPICTRL1      = 0xFF;
    SPICTRL2      = 0xFF;
    SPICTRL3      = 0xFF;
}


// UART1 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_UART1(void)
{
    uchar i = RSTDMMC;

    if(i == 0x13) {
        RSTDMMC = 0x1F;
    }


    i = CGCTRL3R;
    if (i == 0x51) {
        CGCTRL3R = 0x55;
    }
 
    i = AUTOCG;
    if (i == 0x70) {
        AUTOCG = 0x10;
    }
    // test_rdata1 = UART1_LCR;
    // test_rdata2 = UART1_IER;

    // 判断状态
    // if((test_rdata1 != 0x00) || (test_rdata2 != 0x00)) {
    //     // BAT_LED1_ON();
    //     BAT_LED2_ON();
    // } else {
    //     // BAT_LED1_ON();
    // }

    UART1_LCR      = 0xFf;
    UART1_IER      = 0xFF;

    test_rdata1 = UART1_LCR;
    test_rdata2 = UART1_IER;

    // BAT_LED1_ON();
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        // BAT_LED1_ON();
    }

    if((UART1_LCR == 0xFF) || (UART1_IER == 0xFF)) {
        BAT_LED1_ON();
    }

}


// UART2 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_UART2(void)
{
    test_rdata1 = UART2_LCR;
    test_rdata2 = UART2_IER;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    UART2_LCR      = 0xFf;
    UART2_IER      = 0xFF;
}


// TMR 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_TMR(void)
{
    test_rdata1 = PRSC;
    test_rdata2 = TMRCE;
    test_rdata3 = TMEIE;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00) || (test_rdata3 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    PRSC       = 0xFF;
    TMRCE      = 0x03;
    TMEIE      = 0xFF;
}

ECReg	__CEC_CECDLA       	_at_ 0x2E02;	
ECReg	__CEC_CECIE       	_at_ 0x2E05;
// CEC 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_CEC(void)
{
    test_rdata1 = __CEC_CECDLA;
    test_rdata2 = __CEC_CECIE;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x00)) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    __CEC_CECDLA      = 0x0F;
    __CEC_CECIE       = 0x3F;
}


ECReg	__PECI_PADCTLR     _at_ 0x300E;
// PECI 功能测试
// 一直亮白灯，说明 寄存器被初始化
static void __test_PECI(void)
{
    test_rdata1 = HOTRADDR;
    test_rdata2 = HOCTL2R;
    test_rdata3 = __PECI_PADCTLR;

    // 判断状态
    if((test_rdata1 != 0x00) || (test_rdata2 != 0x40) || (test_rdata3 != 0x00) ) {
        // BAT_LED1_ON();
        BAT_LED2_ON();
    } else {
        BAT_LED1_ON();
    }

    HOTRADDR            = 0xFF;
    HOCTL2R             = 0x47;
    __PECI_PADCTLR      = 0xC3;
}

/**
 * 试验四内容  : 利用外部看门狗测试看门狗的作用范围
 * 实验四现象  : 具体看函数内部注释
 *             
 * 试验步骤    : 首先设置不同功能的寄存器(一般设置配置寄存器的数值)数值，
 *              然后启动看门狗判断寄存器是否被复位;
 * 
 * 结论        : 具体看函数内部注释
 */
static void __test_function(void)
{

    Init_GPIO();

    // SMFI 寄存器判断设置   不完全受控 待验证
    // __test_SMFI();

    // INTC 寄存器判断设置  受控
    //  __test_INTC();

    // EC2I 寄存器判断设置  受控
    // __test_EC2I();

    // KBC 寄存器判断设置   受控
    //  __test_KBC();

    // SWUC 寄存器判断设置   不完全受控 待验证
    // __test_SWUC();

    // PMC 寄存器判断设置   受控
    // __test_PMC();

    // 关于GPIO 寄存器受控 ，这个原因就是看萌狗复位会导致灯闪

    // PS2 寄存器判断设置   受控
    //  __test_PS2();

    // ADC 寄存器判断设置   受控
    // __test_ADC();

    // PWM 寄存器判断设置   受控
    // __test_PWM();

    // DAC 寄存器判断设置   受控
    // __test_DAC();

    // WUC 寄存器判断设置   受控
    // __test_WUC();

    // SMB 寄存器判断设置   受控
    // __test_SMB();

    // KBS 寄存器判断设置   受控
    // __test_KBS();

    // ECPM 寄存器判断设置   不完全受控 待验证
    // __test_ECPM();

    // ETWD 寄存器判断设置   受控
    // __test1_ETWD();  

    // GCTRC 寄存器判断设置   完全不受控
    // __test_GCTRC();

    // ETWD 寄存器判断设置   受控
    // __test1_EGPC();

    // Batt_RAM 寄存器判断设置   完全不受控，掉电数据也不丢失
    // __test_Batt();

    // CIR 寄存器判断设置    受控
    //  __test_CIR();

    // SSPI 寄存器判断设置    受控
    //   __test_SSPI();

    // UART1 寄存器判断设置    受控
    // __test_UART1();

    // UART2 寄存器判断设置    受控
    // __test_UART2();

    // TMR 寄存器判断设置    受控
    //  __test_TMR();

    // CEC 寄存器判断设置    受控
    //   __test_CEC();

    // PECI 寄存器判断设置    受控
    //    __test_PECI();

    // ETWCFG = 0x20;  // 使能外部看门狗

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

    // EWDKEYR = 0xff; // 开启看门狗复位

    for(;;) {
        _nop_();
    };
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

    
    // i_data = GPDRB;
    // i_data = GPDRB;


    for(;;);

}

#endif


#if 0
void __test_UART(void)
{
    uchar i_status = 0;
    uchar j_status = 0;

    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();

    // 设置 UART为1
    RSTDMMC |= 0x0C;


    UART1_LCR = 0x55; 

    // 复位 UART
    RSTC4 = 0x06;

    // 读寄存器
    i_status = UART1_LCR;

    // 写寄存器
    // UART1_LCR = 0xFF;

    j_status = UART1_LCR;

    if (j_status == 0x55) {
        BAT_LED2_ON();  // 橙色
    } else {
        BAT_LED1_ON();
    }
    // if(j_status ^ i_status) {
    //     BAT_LED1_ON();
    // } else {
    //     BAT_LED2_ON();  // 橙色
    // }

    for(;;);
}
#endif

#if 0
void __test_ETime(void)
{
    // // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();

    EX1=1;					// enable external 1 interrupt 
	EnableAllInterrupt();

    ETPSR = 0x00;                   
    ETCNTLHR = 0x80;        //
    ETCNTLLR = 0x00;        // "g_ECPowerDownPeriodWakeUpTime" second

    ISR3 = Int_EXTimer;             // Write to clear external timer 1 interrupt 
    SET_MASK(IER3, Int_EXTimer);    // Enable external timer 1 interrupt 

    ETWCTRL = 0x01;

    
    for(;;);
}
#endif

#if 1
void __test_ET2_Timer(void)
{
    // 初始化默认的GPIO功能（主要是LED）
    Init_GPIO();

    GCR10 = 0x01;
	GCR8 = 0x10;
	
    // 关总中断
	DisableAllInterrupt();

    //*************************************************************************
	// Set Wake up pin -> alt function
	//*************************************************************************
	// GPCRE4 = ALT;			// pwrsw to alternate pin
	WUEMR2 |= 0x20;         //  设置边缘触发方式
	WUESR2 |= 0x20;			//  清除 电源按键唤醒中断状态并使能
	WUENR2 |= 0x20;  
	ISR1 |= Int_WKO25;		// 清除 int14 for  pwrsw
	IER1 |= Int_WKO25;		// 使能 int14 for  pwrsw


    EX1=1;					// enable external 1 interrupt 
	EnableAllInterrupt();

    // 设置外部定时器2
    ET2PSR=0x00;		// SELECT 32.768Khz
    ET2CNTLH2R= 0x00;
	ET2CNTLHR = 0x80;	   	// SET EXTERNAL TIMERR = 1sec
	ET2CNTLLR = 0x00;		// SET EXTERNAL TIMERR = 1sec 
    

    // int58  IRQ_INT58_ET2
    ISR7 = Int_ET2Intr;             // Write to clear external timer 1 interrupt 
    SET_MASK(IER7, Int_ET2Intr);    // Enable external timer 1 interrupt 

    // ETWCTRL = 0x04;

    for(;;)
    {
        
    };

}

void __test_SMFI1(void)
{
    // unsigned int i = 0;

    // // 初始化默认的GPIO功能（主要是LED）
     Init_GPIO();

    // (*(volatile unsigned char xdata *) 0x1901) = 0x85;
    // (*(volatile unsigned char xdata *) 0x1902) = 0x00;

    // // 对0x1000 ~ 0x107F 所有位置写 0xFF
    // for(i = 0x1000; i < 0x1080; i++) {
    //     (*(volatile unsigned char xdata *) i) = 0xff;
    // }

    // // RSTC1 = 0x80;

    for(;;) {
         BAT_LED2_ON();  // 橙色
    };
}
#endif

#if 0
// 程序进入为 idle 模式， 通过开机按钮唤醒
void __idle_to_wakeup(void)
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

    BAT_LED2_ON();  // 橙色


    BRAM_OEM[40]




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


    // 改变PLL
    // PLLFREQR = 0x07;	


	// InitEnableInterrupt();

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

    BAT_LED2_ON();  // 橙色

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

         
        #else

        // __ASM_young
            
            // #pragma asm
            // nop
            // #pragma endasm



// //                 MOV  DPTR,#0x1A06

// //                 MOV  A,#0xff
// //                 MOVX @DPTR,A

// // LOOP:
// //                 CPL A
// //                 MOVX @DPTR,A
// //                 CPL A
// //                 MOVX @DPTR,A
// //                 CPL A
// //                 MOVX @DPTR,A
// //                 CPL A
// //                 MOVX @DPTR,A
// //                 CPL A
// //                 MOVX @DPTR,A
// //                 CPL A
// //                 MOVX @DPTR,A
// //                 CPL A
// //                 MOVX @DPTR,A
// //                 CPL A
// //                 MOVX @DPTR,A

// //                 SJMP LOOP 


//                 // MOV  A,#0xff
//                 // MOVX @DPTR,A

//                 // MOV  A,#0xff
//                 // MOVX @DPTR,A

//             #pragma endasm

        #endif
    };
#endif
}

#if 1

// 程序进入为 sleep 模式， 通过开机按钮唤醒
static void __change_PLL_req(void)
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


    // 改变PLL
    PLLFREQR = 0x07;	


	// InitEnableInterrupt();

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
//----------------------------------------------------------------------------
// Oem_StartUp
//----------------------------------------------------------------------------
void Oem_StartUp(void)
{
    // Core_Init_ClearRam();
    // Init_ClearRam();

    // // DisableAllInterrupt();
	// SP = 0xC0;					// Setting stack pointer

    // (*(volatile unsigned char xdata *) 0x400) = 0x55;

    /** \brief 测试电源状态寄存器 */
    // __test1_rets();

    /** \brief 测试外部看门狗 */
    // __test_ETWD();

    /** \brief 测试内部看门狗 */
    // __test_ITWD();

    /** \brief 用外部看门狗测试看门狗的复位作用阈 */
    // __test_function();

    // power good 测试
    // __test_power_good();

    // GFLE 相应寄存器测试
    // __test_GPIO_GFLE();

    // 
    // __test_UART();

    //外部定时器1 相应功能测试
    // __test_ETime();

    //外部定时器2 相应功能测试
    // __test_ET2_Timer();

    // __test_SMFI1();

    // idle 唤醒测试
    // __idle_to_wakeup();

    // 瞌睡唤醒
    // __doze_to_wakeup();

    // __deepdoze_to_wakeup();

    // __sleep_to_wakeup();

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



//----------------------------------------------------------------------------
// Oem_Initialization - Initialize the registers, data variables, and oem 
// functions after kernel init. function.
//----------------------------------------------------------------------------
void Oem_Initialization(void)
{

	LWORD *pnt;
//	WORD Fvalue = 0x4000;

//	pnt = sha1_auth(&HashRandom);           // only for compile
	

	Init_GPIO();
	//TF_010++>>
	if(IS_BOARD_ID1_HI())
		EC_PWR_CTR1_ON();
	//TF_010++<<
    #ifdef HSPI
	GPIO_HSPI_INIT();
    #endif

    #ifdef SPIReadMode
    ChangeSPIFlashReadMode(SPIReadMode);
    #endif

    #ifdef HSRSMode
    ChangeHSRSMode(HSRSMode);
    #endif

    #ifdef PLLFrequency
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

    #if CIRFuncSupport	
	Init_CIR();
    #endif

	Init_Cache();
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
    ResetSCIEvent();
	Init_OEMVariable();

	if(ExtendScanPin==0x02)		// KSO16 and KSO17 are used.
	{  
		if(ExternMatrixGPO)
		{
			ExtendScanPin++;
		}
	}

	ExtWDTInit();	
	InitThermalChip();

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
	PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr=0x100;
    while(byte_register_pntr<0x1000)// Clear external ram (0x100~0xFFF)
    {
        *byte_register_pntr=0;
        byte_register_pntr ++;
    }

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

	ECMainVersionInfo = OEM_Version_MSB;
	VCMD_Lenovo = OEM_Version_MSB;
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
