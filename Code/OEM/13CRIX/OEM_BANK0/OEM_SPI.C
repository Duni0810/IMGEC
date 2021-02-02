/*-----------------------------------------------------------------------------
 * TITLE: OEM_SPI.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

#define SSPI_MODE0  0x00
#define SSPI_MODE1  0x01
#define SSPI_MODE2  0x02
#define SSPI_MODE3  0x03

#define SSPI_SPEED_1_2   0x00
#define SSPI_SPEED_1_4   0x01
#define SSPI_SPEED_1_6   0x02
#define SSPI_SPEED_1_8   0x03
#define SSPI_SPEED_1_10  0x04
#define SSPI_SPEED_1_12  0x05
#define SSPI_SPEED_1_14  0x06
#define SSPI_SPEED_1_16  0x07


static void SSPI_Mode_Set(u8 mode)
{
     SPICTRL1 |= ((mode&0x03) << 5);
}


//000b: 1/2 FreqEC
//001b: 1/4 FreqEC
//010b: 1/6 FreqEC
//011b: 1/8 FreqEC
//100b: 1/10 FreqEC
//101b: 1/12 FreqEC
//110b: 1/14 FreqEC
//111b: 1/16 FreqEC
static void SSPI_Speed_set(u8 speed)
{
    SPICTRL1 |= ((speed&0x07) << 2);
}
//-----------------------------------------------------------------------
// Init SPI interface function
//-----------------------------------------------------------------------
void Init_SPIInterface(BYTE channel, BYTE supportbusy, BYTE mode)
{
    BYTE settingOK;

    settingOK = 0x01;   // Pr-set OK
    
    if(channel==SPI_Channel_0)
    {
        GCR1 |= SPICTRL_0;
        SSCE0 =ALT;
    }
    else if(channel==SPI_Channel_1)
    {
        GCR1 |= SPICTRL_1;
        SSCE1 =ALT;
    }
    else if(channel==SPI_Channel_0N1)
    {
        GCR1 |= (SPICTRL_0+SPICTRL_1);
        SSCE0 =ALT;
        SSCE1 =ALT;
    }
    else
    {
        GCR1 &= ~(SPICTRL_0+SPICTRL_1);
        settingOK = 0x00;
    }

    if(settingOK==0x01)
    {
        if(supportbusy == SPI_SupportBusy)
        {
            GCR1 |= SSSPIBP;
        }
        
        SSCK = ALT;
        SMOSI = ALT;
        SMISO = ALT;

        //SPICTRL1 |= (SCKFREQ2+NTREN); // 100b: 1/10 FreqEC, Interrupt Enable, 4-wire
        // SPICTRL1 |= SCKFREQ2+CLPOL+CLPHS;   // 100b: 1/10 FreqEC, Interrupt Disable, 4-wir, mode 3
        SSPI_Mode_Set(SSPI_MODE3);
        SSPI_Speed_set(SSPI_SPEED_1_10);
    }

    if (!mode) {
        SPICTRL1 |= NTREN;
        SET_MASK(ISR4, Int_SSPI);  // clear
        SET_MASK(IER4, Int_SSPI);  // enalbe
    }
}

//-----------------------------------------------------------------------
// Disable SPI interface function
//-----------------------------------------------------------------------
void Disable_SPIInterface(BYTE channel)
{
    GCR1 &= ~(SPICTRL_0+SPICTRL_1+SSSPIBP);
    
    if(channel==SPI_Channel_0)
    {
        SSCE0 =INPUT;
    }
    else if(channel==SPI_Channel_1)
    {
        SSCE1 =INPUT;
    }
    else if(channel==SPI_Channel_0N1)
    {
        SSCE0 =INPUT;
        SSCE1 =INPUT;
    }
    
    SSCK = INPUT;
    SMOSI = INPUT;
    SMISO = INPUT;

    SET_MASK(ISR4, Int_SSPI);    // clear
    CLEAR_MASK(IER4, Int_SSPI);  // disable
}

//-----------------------------------------------------------------------
// Enable SPI interface function
//-----------------------------------------------------------------------
void Enable_SPIInterface(void)
{
    Init_SPIInterface(SPI_Channel_0, SPI_NoSupportBusy, SPI_NON_BLOCK);
}

// 设置block模式
void SPI_Block_Set(BYTE mode)
{
    SET_MASK(SPICTRL2, (mode & 0x01) << 1);    // Blocking selection.
}

// 等待SPI中断产生
void SPI_Int_Wait(void)
{
    while(!SPI_Flash_IntFlag);
    SPI_Flash_IntFlag = 0;
}

//-----------------------------------------------------------------------
// mode0: block   mode1: non-block
//-----------------------------------------------------------------------
void SPIWriteByte(BYTE spidata, BYTE channel, BYTE block_mode)
{
    BYTE settingok;
    settingok = 0x00;
    
    SPIDATA = spidata;

    SPI_Block_Set(block_mode);
    CLEAR_MASK(SPICTRL2, CHRW);    // Write cycle.

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);
        settingok = 0x01;
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
        settingok = 0x01;
    }

    if(!block_mode){ SPI_Int_Wait();};
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void SPIWriteWord(BYTE MSB, BYTE LSB, BYTE channel, BYTE block_mode)
{
    BYTE settingok;
    settingok = 0x00;
    
    SPIDATA = MSB;

    SPI_Block_Set(block_mode);

    // SET_MASK(SPICTRL2, BLKSEL);    // Blocking selection.
    CLEAR_MASK(SPICTRL2, CHRW);    // Write cycle.

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);

        if(!block_mode){ SPI_Int_Wait();};

        SPIDATA = LSB;
        SET_MASK(SPISTS, CH0START);
        settingok = 0x01;
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
        if(!block_mode){ SPI_Int_Wait();};
        SPIDATA = LSB;
        SET_MASK(SPISTS, CH1START);
        settingok = 0x01;
    }
    if(!block_mode){ SPI_Int_Wait();};
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
BYTE SPIReadByte(BYTE channel, BYTE block_mode)
{
    BYTE settingok;
    settingok = 0x00;

    SPI_Block_Set(block_mode);

    SET_MASK(SPICTRL2, CHRW);      // Read cycle.

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);
        settingok = 0x01;
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
        settingok = 0x01;
    }

    if(!block_mode){ SPI_Int_Wait(); }

    return(SPIDATA);
}


//----------------------------------------------------------------------------
// demo SPI 读操作
//----------------------------------------------------------------------------
XBYTE Sensor_Flash_WR(LWORD addr, XBYTE ch)
{
    XBYTE dat = 0x00;

    // 先设置flash读操作
    SPIWriteByte(SPICmd_Read_Data, SPI_Channel, SPI_BLOCK_MODE);

    // 写地址操作
    SPIWriteByte((addr >> 16) & 0xff, SPI_Channel, SPI_BLOCK_MODE);
    SPIWriteByte((addr >> 8) & 0xff, SPI_Channel, SPI_BLOCK_MODE);
    SPIWriteByte((addr & 0xFF), SPI_Channel, SPI_BLOCK_MODE);

    // 读数据
    dat = SPIReadByte(SPI_Channel, SPI_BLOCK_MODE);

    SPISTS = 0x20;
    while(!IS_MASK_SET(SPISTS, BIT1));
    SPISTS = 0x02;

    return dat;
}
