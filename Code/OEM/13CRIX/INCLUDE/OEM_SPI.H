/*-----------------------------------------------------------------------------
 * TITLE: OEM_SPI.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *---------------------------------------------------------------------------*/
 
#ifndef OEM_SPI_H
#define OEM_SPI_H

#define SPI_Channel_0   0x00
#define SPI_Channel_1   0x01
#define SPI_Channel_0N1 0x02

#define SPI_SupportBusy     0x01
#define SPI_NoSupportBusy   0x00

#define SSCK            GPCRA6
#define SMOSI           GPCRC3
#define SMISO           GPCRC5
#define SSCE1           GPCRG0
#define SSCE0           GPCRG2

#define SPI_BLOCK            0x01
#define SPI_NON_BLOCK        0x00
#define SPI_BLOCK_MODE       SPI_NON_BLOCK

extern void Init_SPIInterface(BYTE channel, BYTE supportbusy, BYTE mode);
extern void Disable_SPIInterface(BYTE channel);
extern void Enable_SPIInterface(void);
extern void SPIWriteByte(BYTE spidata, BYTE channel , BYTE block_mode);
extern void SPIWriteWord(BYTE MSB, BYTE LSB, BYTE channel, BYTE block_mode);
extern BYTE SPIReadByte(BYTE channel, BYTE block_mode);

//-----------------------------------------------------------------------------
// Function selection
//-----------------------------------------------------------------------------
#define SPI_Channel                 SPI_Channel_0

XBYTE Sensor_Flash_WR(LWORD addr, XBYTE ch);

#endif