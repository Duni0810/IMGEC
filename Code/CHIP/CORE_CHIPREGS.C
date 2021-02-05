/*-----------------------------------------------------------------------------
 * TITLE: CORE_CHIPREGS.C
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/
 
#include "CORE_INCLUDE.H"
#include "OEM_INCLUDE.H"
#if 0

#define		FIC628_REG_SMFI_BASE	(0x1000)
#define		FIC628_REG_INTC_BASE	(0x1100)	//(0x2100)
#define		FIC628_REG_EC2I_BASE	(0x1200)
#define		FIC628_REG_KBC_BASE	    (0x1300)
#define		FIC628_REG_SWUC_BASE	(0x1400)
#define		FIC628_REG_PMC_BASE	    (0x1500)
#define		FIC628_REG_GPIO_BASE	(0x1600)
#define		FIC628_REG_PS2_BASE	    (0x1700)
#define		FIC628_REG_PWM_BASE	    (0x1800)
#define		FIC628_REG_ADC_BASE		(0x1900)
#define		FIC628_REG_DAC_BASE		(0x1A00)
#define		FIC628_REG_WUC_BASE		(0x1B00)
#define		FIC628_REG_SMBUS_BASE	(0x1C00)
#define		FIC628_REG_KBS_BASE		(0x1D00)
#define		FIC628_REG_ECPM_BASE	(0x1E00)
#define		FIC628_REG_ETWD_BASE	(0x1F00)

#define		FIC628_REG_GCTRL_BASE	(0x2000)
#define		FIC628_REG_EGPC_BASE	(0x2100)
#define		FIC628_REG_BRAM_BASE	(0x2200)
#define		FIC628_REG_CIR_BASE		(0x2300)
#define		FIC628_REG_DBGR_BASE	(0x2500)
#define		FIC628_REG_SSPI_BASE	(0x2600)
#define		FIC628_REG_UART1_BASE	(0x2700)
#define		FIC628_REG_UART2_BASE	(0x2800)
#define		FIC628_REG_TMR_BASE		(0x2900)

#define		FIC628_REG_PECI_BASE	(0x3000)
#else

#define		FIC628_REG_SMFI_BASE	(0x1000)
#define		FIC628_REG_INTC_BASE	(0x2100)	//(0x2100)
#define		FIC628_REG_EC2I_BASE	(0x1200)
#define		FIC628_REG_KBC_BASE	    (0x1300)
#define		FIC628_REG_SWUC_BASE	(0x2400)
#define		FIC628_REG_PMC_BASE	    (0x1500)
#define		FIC628_REG_GPIO_BASE	(0x2600)
#define		FIC628_REG_PS2_BASE	    (0x2700)
#define		FIC628_REG_PWM_BASE	    (0x2800)
#define		FIC628_REG_ADC_BASE		(0x2900)
#define		FIC628_REG_DAC_BASE		(0x2A00)
#define		FIC628_REG_WUC_BASE		(0x2B00)
#define		FIC628_REG_SMBUS_BASE	(0x2C00)
#define		FIC628_REG_KBS_BASE		(0x2D00)
#define		FIC628_REG_ECPM_BASE	(0x2E00)
#define		FIC628_REG_ETWD_BASE	(0x2F00)

#define		FIC628_REG_GCTRL_BASE	(0x2000)
#define		FIC628_REG_EGPC_BASE	(0x3100)
#define		FIC628_REG_BRAM_BASE	(0x2200)
#define		FIC628_REG_CIR_BASE		(0x3300)
#define		FIC628_REG_DBGR_BASE	(0x3500)
#define		FIC628_REG_SSPI_BASE	(0x3600)
#define		FIC628_REG_UART1_BASE	(0x3700)
#define		FIC628_REG_UART2_BASE	(0x3800)
#define		FIC628_REG_TMR_BASE		(0x3900)

#define		FIC628_REG_PECI_BASE	(0x4000)

#endif

//-----------------------------------------------------------------------------
// (10XXh) Shared Memory Flash Interface Bridge (SMFI) 
//-----------------------------------------------------------------------------
ECReg 	FBCFG			_at_ (FIC628_REG_SMFI_BASE |  0x00);	// FBIU Configuration
ECReg 	FPCFG			_at_ (FIC628_REG_SMFI_BASE |  0x01);	// Flash Programming Configuration Register
ECReg 	FECBSR			_at_ (FIC628_REG_SMFI_BASE |  0x05);	// Flash EC Code Banking Select Register
ECReg 	FMSSR			_at_ (FIC628_REG_SMFI_BASE |  0x07);	// Flash Memory Size Select Registe
ECReg 	SMECCS			_at_ (FIC628_REG_SMFI_BASE |  0x20);	// Shared Memory EC Control and Status
ECReg 	SMHSR			_at_ (FIC628_REG_SMFI_BASE |  0x22);	// Shared Memory Host Semaphore
ECReg	FLHCTRL1R		_at_ (FIC628_REG_SMFI_BASE |  0x31);	// Flash Control Register 1	
ECReg	FLHCTRL2R		_at_ (FIC628_REG_SMFI_BASE |  0x32);	// Flash Control Register 2
ECReg	DCache			_at_ (FIC628_REG_SMFI_BASE |  0x33);	// 256 bytes cache
ECReg	UCCTRLR			_at_ (FIC628_REG_SMFI_BASE |  0x34);	// uC Control Register
ECReg	HCTRL2R			_at_ (FIC628_REG_SMFI_BASE |  0x36);	// Host Control 2 Register
ECReg   HSPICTRL2R      _at_ (FIC628_REG_SMFI_BASE |  0x39);	// HSPI Control 2 Register
ECReg	HSPICTRL3R	    _at_ (FIC628_REG_SMFI_BASE |  0x3A);	// HSPI
ECReg 	ECINDAR0		_at_ (FIC628_REG_SMFI_BASE |  0x3B);	// EC-Indirect Memory Address Register 0
ECReg 	ECINDAR1		_at_ (FIC628_REG_SMFI_BASE |  0x3C);	// EC-Indirect Memory Address Register 1
ECReg 	ECINDAR2		_at_ (FIC628_REG_SMFI_BASE |  0x3D);	// EC-Indirect Memory Address Register 2
ECReg 	ECINDAR3		_at_ (FIC628_REG_SMFI_BASE |  0x3E);	// EC-Indirect Memory Address Register 3
ECReg 	ECINDDR			_at_ (FIC628_REG_SMFI_BASE |  0x3F);	// EC-Indirect Memory Data Register
ECReg	SCRA0L			_at_ (FIC628_REG_SMFI_BASE |  0x40);	// Scratch SRAM 0 Address Low Byte Register
ECReg	SCRA0M			_at_ (FIC628_REG_SMFI_BASE |  0x41);	// Scratch SRAM 0 Address Middle Byte Register
ECReg	SCRA0H			_at_ (FIC628_REG_SMFI_BASE |  0x42);	// Scratch SRAM 0 Address High Byte Register
ECReg	SCRA1L			_at_ (FIC628_REG_SMFI_BASE |  0x43);	// Scratch SRAM 1 Address Low Byte Register
ECReg	SCRA1M			_at_ (FIC628_REG_SMFI_BASE |  0x44);	// Scratch SRAM 1 Address Middle Byte Register
ECReg	SCRA1H			_at_ (FIC628_REG_SMFI_BASE |  0x45);	// Scratch SRAM 1 Address High Byte Register
ECReg	SCRA2L			_at_ (FIC628_REG_SMFI_BASE |  0x46);	// Scratch SRAM 2 Address Low Byte Register
ECReg	SCRA2M			_at_ (FIC628_REG_SMFI_BASE |  0x47);	// Scratch SRAM 2 Address Middle Byte Register
ECReg	SCRA2H			_at_ (FIC628_REG_SMFI_BASE |  0x48);	// Scratch SRAM 2 Address High Byte Register
ECReg	SCRA3L			_at_ (FIC628_REG_SMFI_BASE |  0x49);	// Scratch SRAM 3 Address Low Byte Register
ECReg	SCRA3M			_at_ (FIC628_REG_SMFI_BASE |  0x4A);	// Scratch SRAM 3 Address Middle Byte Register
ECReg	SCRA3H			_at_ (FIC628_REG_SMFI_BASE |  0x4B);	// Scratch SRAM 3 Address High Byte Register
ECReg	SCRA4L			_at_ (FIC628_REG_SMFI_BASE |  0x4C);	// Scratch SRAM 4 Address Low Byte Register
ECReg	SCRA4M			_at_ (FIC628_REG_SMFI_BASE |  0x4D);	// Scratch SRAM 4 Address Middle Byte Register
ECReg	SCRA4H			_at_ (FIC628_REG_SMFI_BASE |  0x4E);	// Scratch SRAM 4 Address High Byte Register

ECReg	P0BA0R			_at_ (FIC628_REG_SMFI_BASE |  0x4F);	// Protect 0 Base Addr Register 0
ECReg	P0BA1R			_at_ (FIC628_REG_SMFI_BASE |  0x50);	// Protect 0 Base Addr Register 1
ECReg	P0ZR			_at_ (FIC628_REG_SMFI_BASE |  0x51);	// Protect 0 Size Register
ECReg	P1BA0R			_at_ (FIC628_REG_SMFI_BASE |  0x52);	// Protect 1 Base Addr Register 0
ECReg	P1BA1R			_at_ (FIC628_REG_SMFI_BASE |  0x53);	// Protect 1 Base Addr Register 1
ECReg	P1ZR			_at_ (FIC628_REG_SMFI_BASE |  0x54);	// Protect 1 Size Register
ECReg	DSINST			_at_ (FIC628_REG_SMFI_BASE |  0x55);	// Deferred SPI Instruction
ECReg	DSADR1			_at_ (FIC628_REG_SMFI_BASE |  0x56);	// Deferred SPI Address
ECReg	DSADR2			_at_ (FIC628_REG_SMFI_BASE |  0x57);	// Deferred SPI Address
ECReg	HINSTC1			_at_ (FIC628_REG_SMFI_BASE |  0x58);	// Host Instruction Control 1
ECReg	HINSTC2			_at_ (FIC628_REG_SMFI_BASE |  0x59);	// Host Instruction Control 2
ECReg	HRAMWC			_at_ (FIC628_REG_SMFI_BASE |  0x5A);	// Host RAM Window Control
ECReg	HRAMW0BA		_at_ (FIC628_REG_SMFI_BASE |  0x5B);	// Host RAM Winodw 0 Base Address
ECReg	HRAMW1BA		_at_ (FIC628_REG_SMFI_BASE |  0x5C);	// Host RAM Window 1 Base Address
ECReg	HRAMW0AAS		_at_ (FIC628_REG_SMFI_BASE |  0x5D);	// Host RAM Window 0 Access Allow Size
ECReg	HRAMW1AAS		_at_ (FIC628_REG_SMFI_BASE |  0x5E);	// Host RAM Window 1 Access Allow Size
ECReg	SCAR5H			_at_ (FIC628_REG_SMFI_BASE |  0x5F);
ECReg	FLHCTRL3R		_at_ (FIC628_REG_SMFI_BASE |  0x63);

ECReg	SMFI_FIC_CTL0	_at_ (FIC628_REG_SMFI_BASE |  0xB0);
ECReg	SMFI_FIC_CTL1	_at_ (FIC628_REG_SMFI_BASE |  0xB1);

//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC) 
//-----------------------------------------------------------------------------
ECReg 	ISR0      		_at_ (FIC628_REG_INTC_BASE | 0x00);	// Interrupt Status Register 0
ECReg 	ISR1       		_at_ (FIC628_REG_INTC_BASE | 0x01);	// Interrupt Status Register 1
ECReg 	ISR2       		_at_ (FIC628_REG_INTC_BASE | 0x02);	// Interrupt Status Register 2
ECReg 	ISR3       		_at_ (FIC628_REG_INTC_BASE | 0x03);	// Interrupt Status Register 3
ECReg 	ISR4    		_at_ (FIC628_REG_INTC_BASE | 0x14);	// Interrupt Status Register 4
ECReg 	ISR5    		_at_ (FIC628_REG_INTC_BASE | 0x18);	// Interrupt Status Register 5
ECReg 	ISR6    		_at_ (FIC628_REG_INTC_BASE | 0x1C);	// Interrupt Status Register 6
ECReg 	ISR7    		_at_ (FIC628_REG_INTC_BASE | 0x20);	// Interrupt Status Register 7
ECReg 	ISR8            _at_ (FIC628_REG_INTC_BASE | 0x24);	// Interrupt Status Register 8
ECReg 	ISR9            _at_ (FIC628_REG_INTC_BASE | 0x28);	// Interrupt Status Register 9
ECReg 	ISR10           _at_ (FIC628_REG_INTC_BASE | 0x2C);	// Interrupt Status Register 10
ECReg 	ISR15           _at_ (FIC628_REG_INTC_BASE | 0x40);	// Interrupt Status Register 15	//J80_011||

ECReg 	IER0      		_at_ (FIC628_REG_INTC_BASE | 0x04);	// Interrupt Enable Register 0
ECReg 	IER1       		_at_ (FIC628_REG_INTC_BASE | 0x05);	// Interrupt Enable Register 1
ECReg 	IER2      		_at_ (FIC628_REG_INTC_BASE | 0x06);	// Interrupt Enable Register 2
ECReg 	IER3       		_at_ (FIC628_REG_INTC_BASE | 0x07);	// Interrupt Enable Register 3
ECReg 	IER4    		_at_ (FIC628_REG_INTC_BASE | 0x15);	// Interrupt Enable Register 4
ECReg 	IER5    		_at_ (FIC628_REG_INTC_BASE | 0x19);	// Interrupt Enable Register 5
ECReg 	IER6    		_at_ (FIC628_REG_INTC_BASE | 0x1D);	// Interrupt Enable Register 6
ECReg 	IER7    		_at_ (FIC628_REG_INTC_BASE | 0x21);	// Interrupt Enable Register 7
ECReg 	IER8    		_at_ (FIC628_REG_INTC_BASE | 0x25);	// Interrupt Enable Register 8
ECReg 	IER9    		_at_ (FIC628_REG_INTC_BASE | 0x29);	// Interrupt Enable Register 9
ECReg 	IER10    		_at_ (FIC628_REG_INTC_BASE | 0x2D);	// Interrupt Enable Register 10
ECReg 	IER15    		_at_ (FIC628_REG_INTC_BASE | 0x41);	// Interrupt Enable Register 15	//J80_011||

ECReg 	IELMR0    		_at_ (FIC628_REG_INTC_BASE | 0x08);	// Interrupt Edge/Level-Triggered Mode Register 0
ECReg 	IELMR1     		_at_ (FIC628_REG_INTC_BASE | 0x09);	// Interrupt Edge/Level-Triggered Mode Register 1
ECReg 	IELMR2   		_at_ (FIC628_REG_INTC_BASE | 0x0A);	// Interrupt Edge/Level-Triggered Mode Register 2
ECReg 	IELMR3     		_at_ (FIC628_REG_INTC_BASE | 0x0B);	// Interrupt Edge/Level-Triggered Mode Register 3
ECReg 	IELMR4    		_at_ (FIC628_REG_INTC_BASE | 0x16);	// Interrupt Edge/Level-Triggered Mode Register 4
ECReg 	IELMR5    		_at_ (FIC628_REG_INTC_BASE | 0x1A);	// Interrupt Edge/Level-Triggered Mode Register 5
ECReg 	IELMR6    		_at_ (FIC628_REG_INTC_BASE | 0x1E);	// Interrupt Edge/Level-Triggered Mode Register 6
ECReg 	IELMR7    		_at_ (FIC628_REG_INTC_BASE | 0x22);	// Interrupt Edge/Level-Triggered Mode Register 7
ECReg 	IELMR8    		_at_ (FIC628_REG_INTC_BASE | 0x26);	// Interrupt Edge/Level-Triggered Mode Register 8
ECReg 	IELMR9    		_at_ (FIC628_REG_INTC_BASE | 0x2A);	// Interrupt Edge/Level-Triggered Mode Register 9

ECReg 	IPOLR0     		_at_ (FIC628_REG_INTC_BASE | 0x0C);	// Interrupt Polarity Register 0
ECReg 	IPOLR1    		_at_ (FIC628_REG_INTC_BASE | 0x0D);	// Interrupt Polarity Register 1
ECReg 	IPOLR2    		_at_ (FIC628_REG_INTC_BASE | 0x0E);	// Interrupt Polarity Register 2
ECReg 	IPOLR3    		_at_ (FIC628_REG_INTC_BASE | 0x0F);	// Interrupt Polarity Register 3
ECReg 	IPOLR4    		_at_ (FIC628_REG_INTC_BASE | 0x17);	// Interrupt Polarity Register 4
ECReg 	IPOLR5    		_at_ (FIC628_REG_INTC_BASE | 0x1B);	// Interrupt Polarity Register 5
ECReg 	IPOLR6    		_at_ (FIC628_REG_INTC_BASE | 0x1F);	// Interrupt Polarity Register 6
ECReg 	IPOLR7    		_at_ (FIC628_REG_INTC_BASE | 0x23);	// Interrupt Polarity Register 7
ECReg 	IPOLR8    		_at_ (FIC628_REG_INTC_BASE | 0x27);	// Interrupt Polarity Register 8
ECReg 	IPOLR9    		_at_ (FIC628_REG_INTC_BASE | 0x2B);	// Interrupt Polarity Register 9

ECReg 	IVECT    		_at_ (FIC628_REG_INTC_BASE | 0x10);	// Interrupt Vector Register
ECReg 	INT0ST    		_at_ (FIC628_REG_INTC_BASE | 0x11);	// INT0# status
ECReg 	PFAILR    		_at_ (FIC628_REG_INTC_BASE | 0x12);	// Power Fail Register

//-----------------------------------------------------------------------------
// (12xxh) EC Access to ost Controlled Modules (EC2I Bridge) 
//-----------------------------------------------------------------------------
ECReg 	IHIOA     		_at_ (FIC628_REG_EC2I_BASE | 0x00);	// Indirect Host I/O Address
ECReg 	IHD      		_at_ (FIC628_REG_EC2I_BASE | 0x01);	// Indirect Host Data
ECReg 	LSIOHA    		_at_ (FIC628_REG_EC2I_BASE | 0x02);	// Lock Super I/O Host Access
ECReg 	SIOLV     		_at_ (FIC628_REG_EC2I_BASE | 0x03);	// Super I/O Access Lock Violation
ECReg 	IBMAE			_at_ (FIC628_REG_EC2I_BASE | 0x04);	// EC to I-Bus Modules Access Enable
ECReg 	IBCTL   		_at_ (FIC628_REG_EC2I_BASE | 0x05);	// I-Bus Control

//-----------------------------------------------------------------------------
// (13xxh) Keyboard Controller (KBC) 
//-----------------------------------------------------------------------------
ECReg 	KBHICR   		_at_ (FIC628_REG_KBC_BASE |0x00);	// KBC Host Interface Control Register
ECReg 	KBIRQR     		_at_ (FIC628_REG_KBC_BASE |0x02);	// KBC Interrupt Control Register
ECReg 	KBHISR   		_at_ (FIC628_REG_KBC_BASE |0x04);	// KBC Host Interface Keyboard/Mouse Status Register
ECReg 	KBHIKDOR 		_at_ (FIC628_REG_KBC_BASE |0x06);	// KBC Host Interface Keyboard Data Output Register
ECReg 	KBHIMDOR  		_at_ (FIC628_REG_KBC_BASE |0x08);	// KBC Host Interface Mouse Data Output Register
ECReg 	KBHIDIR   		_at_ (FIC628_REG_KBC_BASE |0x0A);	// KBC Host Interface Keyboard/Mouse Data Input Register

//-----------------------------------------------------------------------------
// (14xxh) System Wake-Up Control (SWUC) 
//-----------------------------------------------------------------------------
ECReg 	SWCTL1			_at_ (FIC628_REG_SWUC_BASE | 0x00);	// SWUC Control Status 1 Register
ECReg 	SWCTL2			_at_ (FIC628_REG_SWUC_BASE | 0x02);	// SWUC Control Status 2 Register
ECReg 	SWCTL3			_at_ (FIC628_REG_SWUC_BASE | 0x04);	// SWUC Control Status 3 Register
ECReg 	SWCBALR			_at_ (FIC628_REG_SWUC_BASE | 0x08);	// SWUC Host Configuration Base Address Low Byte Register
ECReg 	SWCBAHR			_at_ (FIC628_REG_SWUC_BASE | 0x0A);	// SWUC Host Configuration Base Address High Byte Register
ECReg 	SWCIER     		_at_ (FIC628_REG_SWUC_BASE | 0x0C);	// SWUC Interrupt Enable Register
ECReg 	SWCHSTR    		_at_ (FIC628_REG_SWUC_BASE | 0x0E);	// SWUC Host Event Status Register
ECReg 	SWCHIER  		_at_ (FIC628_REG_SWUC_BASE | 0x10);	// SWUC Host Event Interrupt Enable Register

//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC) 
//-----------------------------------------------------------------------------
										// PM1
ECReg 	PM1STS   		_at_ (FIC628_REG_PMC_BASE | 0x00);	// Host Interface PM Channel 1 Status
ECReg 	PM1DO      		_at_ (FIC628_REG_PMC_BASE | 0x01);	// Host Interface PM Channel 1 Data Out Port
ECReg 	PM1DOSCI  		_at_ (FIC628_REG_PMC_BASE | 0x02);	// Host Interface PM Channel 1 Data Out Port with SCI
ECReg 	PM1DOSMI  		_at_ (FIC628_REG_PMC_BASE | 0x03);	// Host Interface PM Channel 1 Data Out Port with SMI
ECReg 	PM1DI			_at_ (FIC628_REG_PMC_BASE | 0x04);	// Host Interface PM Channel 1 Data In Port
ECReg 	PM1DISCI   		_at_ (FIC628_REG_PMC_BASE | 0x05);	// Host Interface PM Channel 1 Data In Port with SCI
ECReg 	PM1CTL     		_at_ (FIC628_REG_PMC_BASE | 0x06);	// Host Interface PM Channel 1 Control
ECReg 	PM1IC     		_at_ (FIC628_REG_PMC_BASE | 0x07);	// Host Interface PM Channel 1 Interrupt Control
ECReg 	PM1IE    		_at_ (FIC628_REG_PMC_BASE | 0x08);	// Host Interface PM Channel 1 Interrupt Enable
										// PM2
ECReg 	PM2STS    		_at_ (FIC628_REG_PMC_BASE | 0x10);	// Host Interface PM Channel 2 Status
ECReg 	PM2DO     		_at_ (FIC628_REG_PMC_BASE | 0x11);	// Host Interface PM Channel 2 Data Out Port
ECReg 	PM2DOSCI   		_at_ (FIC628_REG_PMC_BASE | 0x12);	// Host Interface PM Channel 2 Data Out Port with SCI
ECReg 	PM2DOSMI  		_at_ (FIC628_REG_PMC_BASE | 0x13);	// Host Interface PM Channel 2 Data Out Port with SMI
ECReg 	PM2DI     		_at_ (FIC628_REG_PMC_BASE | 0x14);	// Host Interface PM Channel 2 Data In Port
ECReg 	PM2DISCI   		_at_ (FIC628_REG_PMC_BASE | 0x15);	// Host Interface PM Channel 2 Data In Port with SCI
ECReg 	PM2CTL     		_at_ (FIC628_REG_PMC_BASE | 0x16);	// Host Interface PM Channel 2 Control
ECReg 	PM2IC     		_at_ (FIC628_REG_PMC_BASE | 0x17);	// Host Interface PM Channel 2 Interrupt Control
ECReg 	PM2IE     		_at_ (FIC628_REG_PMC_BASE | 0x18);	// Host Interface PM Channel 2 Interrupt Enable
										// Mailbox
ECReg	MBXCTRL			_at_ (FIC628_REG_PMC_BASE | 0x19);	// Mailbox Control

ECReg 	PM3STS    		_at_ (FIC628_REG_PMC_BASE | 0x20);	// Host Interface PM Channel 3 Status
ECReg 	PM3DO     		_at_ (FIC628_REG_PMC_BASE | 0x21);	// Host Interface PM Channel 3 Data Out Port
ECReg 	PM3DI     		_at_ (FIC628_REG_PMC_BASE | 0x22);	// Host Interface PM Channel 3 Data In Port
ECReg 	PM3CTL     		_at_ (FIC628_REG_PMC_BASE | 0x23);	// Host Interface PM Channel 3 Control
ECReg 	PM3IC     		_at_ (FIC628_REG_PMC_BASE | 0x24);	// Host Interface PM Channel 3 Interrupt Control
ECReg 	PM3IE     		_at_ (FIC628_REG_PMC_BASE | 0x25);	// Host Interface PM Channel 3 Interrupt Enable

ECReg 	PM4STS    		_at_ (FIC628_REG_PMC_BASE | 0x30);	// Host Interface PM Channel 4 Status
ECReg 	PM4DO     		_at_ (FIC628_REG_PMC_BASE | 0x31);	// Host Interface PM Channel 4 Data Out Port
ECReg 	PM4DI     		_at_ (FIC628_REG_PMC_BASE | 0x32);	// Host Interface PM Channel 4 Data In Port
ECReg 	PM4CTL     		_at_ (FIC628_REG_PMC_BASE | 0x33);	// Host Interface PM Channel 4 Control
ECReg 	PM4IC     		_at_ (FIC628_REG_PMC_BASE | 0x34);	// Host Interface PM Channel 4 Interrupt Control
ECReg 	PM4IE     		_at_ (FIC628_REG_PMC_BASE | 0x35);	// Host Interface PM Channel 4 Interrupt Enable

ECReg	MBXEC[16]		_at_ (FIC628_REG_PMC_BASE | 0xF0);// 16-byte PMC2EX Mailbox 0 ~ Mailbox 15

//-----------------------------------------------------------------------------
// (16XXh) General Purpose I/O Control Register                           
//-----------------------------------------------------------------------------
										// GPIO data register
ECReg	GCR     		_at_ (FIC628_REG_GPIO_BASE | 0x00);	// General Control Register
ECReg	GCR1     		_at_ (FIC628_REG_GPIO_BASE | 0xF0);	// General Control 1 Register
ECReg	GCR2     		_at_ (FIC628_REG_GPIO_BASE | 0xF1);	// General Control 2 Register
ECReg	GCR3     		_at_ (FIC628_REG_GPIO_BASE | 0xF2);	// General Control 3 Register
ECReg	GCR4     		_at_ (FIC628_REG_GPIO_BASE | 0xF3);	// General Control 4 Register
ECReg	GCR5     		_at_ (FIC628_REG_GPIO_BASE | 0xF4);	// General Control 5 Register
ECReg	GCR6     		_at_ (FIC628_REG_GPIO_BASE | 0xF5);	// General Control 6 Register
ECReg	GCR7     		_at_ (FIC628_REG_GPIO_BASE | 0xF6);	// General Control 7 Register
ECReg	GCR8     		_at_ (FIC628_REG_GPIO_BASE | 0xF7);	// General Control 8 Register
ECReg	GCR9     		_at_ (FIC628_REG_GPIO_BASE | 0xF8);	// General Control 9 Register
ECReg	GCR10     		_at_ (FIC628_REG_GPIO_BASE | 0xF9);	// General Control 10 Register

ECReg	GPDRA 			_at_ (FIC628_REG_GPIO_BASE | 0x01);	// Port A Data Register
ECReg	GPDRB 			_at_ (FIC628_REG_GPIO_BASE | 0x02);	// Port B Data Register
ECReg	GPDRC 			_at_ (FIC628_REG_GPIO_BASE | 0x03);	// Port C Data Register
ECReg	GPDRD 			_at_ (FIC628_REG_GPIO_BASE | 0x04);	// Port D Data Register
ECReg	GPDRE 			_at_ (FIC628_REG_GPIO_BASE | 0x05);	// Port E Data Register
ECReg	GPDRF 			_at_ (FIC628_REG_GPIO_BASE | 0x06);	// Port F Data Register
ECReg	GPDRG 			_at_ (FIC628_REG_GPIO_BASE | 0x07);	// Port G Data Register
ECReg	GPDRH 			_at_ (FIC628_REG_GPIO_BASE | 0x08);	// Port H Data Register
ECReg	GPDRI 			_at_ (FIC628_REG_GPIO_BASE | 0x09);	// Port I Data Register
ECReg	GPDRJ 			_at_ (FIC628_REG_GPIO_BASE | 0x0A);	// Port J Data Register
ECReg	GPDRM 			_at_ (FIC628_REG_GPIO_BASE | 0x0D);	// Port M Data Register
										// GPIO control register
ECReg 	GPCRA0			_at_ (FIC628_REG_GPIO_BASE | 0x10);	// Port Control A0 Registers
ECReg 	GPCRA1			_at_ (FIC628_REG_GPIO_BASE | 0x11);	// Port Control A1 Registers
ECReg 	GPCRA2			_at_ (FIC628_REG_GPIO_BASE | 0x12);	// Port Control A2 Registers
ECReg 	GPCRA3			_at_ (FIC628_REG_GPIO_BASE | 0x13);	// Port Control A3 Registers
ECReg 	GPCRA4			_at_ (FIC628_REG_GPIO_BASE | 0x14);	// Port Control A4 Registers
ECReg 	GPCRA5			_at_ (FIC628_REG_GPIO_BASE | 0x15);	// Port Control A5 Registers
ECReg 	GPCRA6			_at_ (FIC628_REG_GPIO_BASE | 0x16);	// Port Control A6 Registers
ECReg 	GPCRA7			_at_ (FIC628_REG_GPIO_BASE | 0x17);	// Port Control A7 Registers

ECReg 	GPCRB0			_at_ (FIC628_REG_GPIO_BASE | 0x18);	// Port Control B0 Registers
ECReg 	GPCRB1			_at_ (FIC628_REG_GPIO_BASE | 0x19);	// Port Control B1 Registers
ECReg 	GPCRB2			_at_ (FIC628_REG_GPIO_BASE | 0x1A);	// Port Control B2 Registers
ECReg 	GPCRB3			_at_ (FIC628_REG_GPIO_BASE | 0x1B);	// Port Control B3 Registers
ECReg 	GPCRB4			_at_ (FIC628_REG_GPIO_BASE | 0x1C);	// Port Control B4 Registers
ECReg 	GPCRB5			_at_ (FIC628_REG_GPIO_BASE | 0x1D);	// Port Control B5 Registers
ECReg 	GPCRB6			_at_ (FIC628_REG_GPIO_BASE | 0x1E);	// Port Control B6 Registers
ECReg 	GPCRB7			_at_ (FIC628_REG_GPIO_BASE | 0x1F);	// Port Control B7 Registers

ECReg 	GPCRC0			_at_ (FIC628_REG_GPIO_BASE | 0x20);	// Port Control C0 Registers
ECReg 	GPCRC1			_at_ (FIC628_REG_GPIO_BASE | 0x21);	// Port Control C1 Registers
ECReg 	GPCRC2			_at_ (FIC628_REG_GPIO_BASE | 0x22);	// Port Control C2 Registers
ECReg 	GPCRC3			_at_ (FIC628_REG_GPIO_BASE | 0x23);	// Port Control C3 Registers
ECReg 	GPCRC4			_at_ (FIC628_REG_GPIO_BASE | 0x24);	// Port Control C4 Registers
ECReg 	GPCRC5			_at_ (FIC628_REG_GPIO_BASE | 0x25);	// Port Control C5 Registers
ECReg 	GPCRC6			_at_ (FIC628_REG_GPIO_BASE | 0x26);	// Port Control C6 Registers
ECReg 	GPCRC7			_at_ (FIC628_REG_GPIO_BASE | 0x27);	// Port Control C7 Registers

ECReg 	GPCRD0			_at_ (FIC628_REG_GPIO_BASE | 0x28);	// Port Control D0 Registers
ECReg 	GPCRD1			_at_ (FIC628_REG_GPIO_BASE | 0x29);	// Port Control D1 Registers
ECReg 	GPCRD2			_at_ (FIC628_REG_GPIO_BASE | 0x2A);	// Port Control D2 Registers
ECReg 	GPCRD3			_at_ (FIC628_REG_GPIO_BASE | 0x2B);	// Port Control D3 Registers
ECReg 	GPCRD4			_at_ (FIC628_REG_GPIO_BASE | 0x2C);	// Port Control D4 Registers
ECReg 	GPCRD5			_at_ (FIC628_REG_GPIO_BASE | 0x2D);	// Port Control D5 Registers
ECReg 	GPCRD6			_at_ (FIC628_REG_GPIO_BASE | 0x2E);	// Port Control D6 Registers
ECReg 	GPCRD7			_at_ (FIC628_REG_GPIO_BASE | 0x2F);	// Port Control D7 Registers

ECReg 	GPCRE0			_at_ (FIC628_REG_GPIO_BASE | 0x30);	// Port Control E0 Registers
ECReg 	GPCRE1			_at_ (FIC628_REG_GPIO_BASE | 0x31);	// Port Control E1 Registers
ECReg 	GPCRE2			_at_ (FIC628_REG_GPIO_BASE | 0x32);	// Port Control E2 Registers
ECReg 	GPCRE3			_at_ (FIC628_REG_GPIO_BASE | 0x33);	// Port Control E3 Registers
ECReg 	GPCRE4			_at_ (FIC628_REG_GPIO_BASE | 0x34);	// Port Control E4 Registers
ECReg 	GPCRE5			_at_ (FIC628_REG_GPIO_BASE | 0x35);	// Port Control E5 Registers
ECReg 	GPCRE6			_at_ (FIC628_REG_GPIO_BASE | 0x36);	// Port Control E6 Registers
ECReg 	GPCRE7			_at_ (FIC628_REG_GPIO_BASE | 0x37);	// Port Control E7 Registers

ECReg 	GPCRF0			_at_ (FIC628_REG_GPIO_BASE | 0x38);	// Port Control F0 Registers
ECReg 	GPCRF1			_at_ (FIC628_REG_GPIO_BASE | 0x39);	// Port Control F1 Registers
ECReg 	GPCRF2			_at_ (FIC628_REG_GPIO_BASE | 0x3A);	// Port Control F2 Registers
ECReg 	GPCRF3			_at_ (FIC628_REG_GPIO_BASE | 0x3B);	// Port Control F3 Registers
ECReg 	GPCRF4			_at_ (FIC628_REG_GPIO_BASE | 0x3C);	// Port Control F4 Registers
ECReg 	GPCRF5			_at_ (FIC628_REG_GPIO_BASE | 0x3D);	// Port Control F5 Registers
ECReg 	GPCRF6			_at_ (FIC628_REG_GPIO_BASE | 0x3E);	// Port Control F6 Registers
ECReg 	GPCRF7			_at_ (FIC628_REG_GPIO_BASE | 0x3F);	// Port Control F7 Registers

ECReg 	GPCRG0			_at_ (FIC628_REG_GPIO_BASE | 0x40);	// Port Control G0 Registers
ECReg 	GPCRG1			_at_ (FIC628_REG_GPIO_BASE | 0x41);	// Port Control G1 Registers
ECReg 	GPCRG2			_at_ (FIC628_REG_GPIO_BASE | 0x42);	// Port Control G2 Registers
ECReg 	GPCRG3			_at_ (FIC628_REG_GPIO_BASE | 0x43);	// Port Control G3 Registers
ECReg 	GPCRG4			_at_ (FIC628_REG_GPIO_BASE | 0x44);	// Port Control G4 Registers
ECReg 	GPCRG5			_at_ (FIC628_REG_GPIO_BASE | 0x45);	// Port Control G5 Registers
ECReg 	GPCRG6			_at_ (FIC628_REG_GPIO_BASE | 0x46);	// Port Control G6 Registers
ECReg 	GPCRG7			_at_ (FIC628_REG_GPIO_BASE | 0x47);	// Port Control G7 Registers

ECReg 	GPCRH0			_at_ (FIC628_REG_GPIO_BASE | 0x48);	// Port Control H0 Registers
ECReg 	GPCRH1			_at_ (FIC628_REG_GPIO_BASE | 0x49);	// Port Control H1 Registers
ECReg 	GPCRH2			_at_ (FIC628_REG_GPIO_BASE | 0x4A);	// Port Control H2 Registers
ECReg 	GPCRH3			_at_ (FIC628_REG_GPIO_BASE | 0x4B);	// Port Control H3 Registers
ECReg 	GPCRH4			_at_ (FIC628_REG_GPIO_BASE | 0x4C);	// Port Control H4 Registers
ECReg 	GPCRH5			_at_ (FIC628_REG_GPIO_BASE | 0x4D);	// Port Control H5 Registers
ECReg 	GPCRH6			_at_ (FIC628_REG_GPIO_BASE | 0x4E);	// Port Control H6 Registers

ECReg 	GPCRI0			_at_ (FIC628_REG_GPIO_BASE | 0x50);	// Port Control I0 Registers
ECReg 	GPCRI1			_at_ (FIC628_REG_GPIO_BASE | 0x51);	// Port Control I1 Registers
ECReg 	GPCRI2			_at_ (FIC628_REG_GPIO_BASE | 0x52);	// Port Control I2 Registers
ECReg 	GPCRI3			_at_ (FIC628_REG_GPIO_BASE | 0x53);	// Port Control I3 Registers
ECReg 	GPCRI4			_at_ (FIC628_REG_GPIO_BASE | 0x54);	// Port Control I4 Registers
ECReg 	GPCRI5			_at_ (FIC628_REG_GPIO_BASE | 0x55);	// Port Control I5 Registers
ECReg 	GPCRI6			_at_ (FIC628_REG_GPIO_BASE | 0x56);	// Port Control I6 Registers
ECReg 	GPCRI7			_at_ (FIC628_REG_GPIO_BASE | 0x57);	// Port Control I7 Registers

ECReg 	GPCRJ0			_at_ (FIC628_REG_GPIO_BASE | 0x58);	// Port Control J0 Registers
ECReg 	GPCRJ1			_at_ (FIC628_REG_GPIO_BASE | 0x59);	// Port Control J1 Registers
ECReg 	GPCRJ2			_at_ (FIC628_REG_GPIO_BASE | 0x5A);	// Port Control J2 Registers
ECReg 	GPCRJ3			_at_ (FIC628_REG_GPIO_BASE | 0x5B);	// Port Control J3 Registers
ECReg 	GPCRJ4			_at_ (FIC628_REG_GPIO_BASE | 0x5C);	// Port Control J4 Registers
ECReg 	GPCRJ5			_at_ (FIC628_REG_GPIO_BASE | 0x5D);	// Port Control J5 Registers

ECReg 	GPCRM0			_at_ (FIC628_REG_GPIO_BASE | 0xA0);	// Port Control M0 Registers
ECReg 	GPCRM1			_at_ (FIC628_REG_GPIO_BASE | 0xA1);	// Port Control M1 Registers
ECReg 	GPCRM2			_at_ (FIC628_REG_GPIO_BASE | 0xA2);	// Port Control M2 Registers
ECReg 	GPCRM3			_at_ (FIC628_REG_GPIO_BASE | 0xA3);	// Port Control M3 Registers
ECReg 	GPCRM4			_at_ (FIC628_REG_GPIO_BASE | 0xA4);	// Port Control M4 Registers
ECReg 	GPCRM5			_at_ (FIC628_REG_GPIO_BASE | 0xA5);	// Port Control M5 Registers
ECReg 	GPCRM6			_at_ (FIC628_REG_GPIO_BASE | 0xA6);	// Port Control M6 Registers

										// Port Data Mirror Register
ECReg 	GPDMRA			_at_ (FIC628_REG_GPIO_BASE | 0x61);	// Port A Data Mirror Register
ECReg 	GPDMRB			_at_ (FIC628_REG_GPIO_BASE | 0x62);	// Port B Data Mirror Register
ECReg 	GPDMRC			_at_ (FIC628_REG_GPIO_BASE | 0x63);	// Port C Data Mirror Register
ECReg 	GPDMRD			_at_ (FIC628_REG_GPIO_BASE | 0x64);	// Port D Data Mirror Register
ECReg 	GPDMRE			_at_ (FIC628_REG_GPIO_BASE | 0x65);	// Port E Data Mirror Register
ECReg 	GPDMRF			_at_ (FIC628_REG_GPIO_BASE | 0x66);	// Port F Data Mirror Register
ECReg 	GPDMRG			_at_ (FIC628_REG_GPIO_BASE | 0x67);	// Port G Data Mirror Register
ECReg 	GPDMRH			_at_ (FIC628_REG_GPIO_BASE | 0x68);	// Port H Data Mirror Register
ECReg 	GPDMRI			_at_ (FIC628_REG_GPIO_BASE | 0x69);	// Port I Data Mirror Register
ECReg 	GPDMRJ			_at_ (FIC628_REG_GPIO_BASE | 0x6A);	// Port J Data Mirror Register
ECReg 	GPDMRM			_at_ (FIC628_REG_GPIO_BASE | 0x6D);	// Port M Data Mirror Register

ECReg 	GPOTA			_at_ (FIC628_REG_GPIO_BASE | 0x71);	// Output Type Register
ECReg 	GPOTB			_at_ (FIC628_REG_GPIO_BASE | 0x72);	// Output Type Register
ECReg 	GPOTD			_at_ (FIC628_REG_GPIO_BASE | 0x74);	// Output Type Register
ECReg 	GPOTE			_at_ (FIC628_REG_GPIO_BASE | 0x75);	// Output Type Register
ECReg 	GPOTH			_at_ (FIC628_REG_GPIO_BASE | 0x78);	// Output Type Register

ECReg	GCR15			_at_ (FIC628_REG_GPIO_BASE | 0xFE);	// General Control 15 Register


//-----------------------------------------------------------------------------
// (17XXh) PS/2 Interface Register                            			  
//-----------------------------------------------------------------------------
ECReg 	PSCTL1    		_at_ (FIC628_REG_PS2_BASE | 0x00);	// PS/2 Control Register 1
ECReg 	PSCTL2			_at_ (FIC628_REG_PS2_BASE | 0x01);	// PS/2 Control Register 2
ECReg 	PSCTL3     		_at_ (FIC628_REG_PS2_BASE | 0x02);	// PS/2 Control Register 3
ECReg 	PSINT1   		_at_ (FIC628_REG_PS2_BASE | 0x04);	// PS/2 Interrupt Control Register 1
ECReg 	PSINT2    		_at_ (FIC628_REG_PS2_BASE | 0x05);	// PS/2 Interrupt Control Register 2
ECReg 	PSINT3    		_at_ (FIC628_REG_PS2_BASE | 0x06);	// PS/2 Interrupt Control Register 3
ECReg 	PSSTS1    		_at_ (FIC628_REG_PS2_BASE | 0x08);	// PS/2 Status Register 1
ECReg 	PSSTS2    		_at_ (FIC628_REG_PS2_BASE | 0x09);	// PS/2 Status Register 2
ECReg 	PSSTS3    		_at_ (FIC628_REG_PS2_BASE | 0x0A);	// PS/2 Status Register 3
ECReg 	PSDAT1    		_at_ (FIC628_REG_PS2_BASE | 0x0C);	// PS/2 Data Register 1
ECReg 	PSDAT2     		_at_ (FIC628_REG_PS2_BASE | 0x0D);	// PS/2 Data Register 2
ECReg	PSDAT3 			_at_ (FIC628_REG_PS2_BASE | 0x0E);	// PS/2 Data Register 3

ECReg	PSDCNUM1 		_at_ (FIC628_REG_PS2_BASE | 0x03);	// PS/2 Data Register 3
ECReg	PSDCNUM2 		_at_ (FIC628_REG_PS2_BASE | 0x07);	// PS/2 Data Register 3
ECReg	PSDCNUM3 		_at_ (FIC628_REG_PS2_BASE | 0x0B);	// PS/2 Data Register 3
ECReg	PSCLKEN 		_at_ (FIC628_REG_PS2_BASE | 0x0F);	// PS/2 Data Register 3
//-----------------------------------------------------------------------------
// (18xxh) PWM & SmartAuto Fan Control (PWM) 
//-----------------------------------------------------------------------------
ECReg	C0CPRS  		_at_ (FIC628_REG_PWM_BASE | 0x00);	// Channel 0 Clock Prescaler Register
ECReg	CTR       		_at_ (FIC628_REG_PWM_BASE | 0x01);	// Cycle Time 0
ECReg	DCR0     		_at_ (FIC628_REG_PWM_BASE | 0x02);	// Channel 0 PWM Duty Cycle		
ECReg	DCR1      		_at_ (FIC628_REG_PWM_BASE | 0x03);	// Channel 0 PWM Duty Cycle	
ECReg	DCR2     		_at_ (FIC628_REG_PWM_BASE | 0x04);	// Channel 0 PWM Duty Cycle	
ECReg	DCR3       		_at_ (FIC628_REG_PWM_BASE | 0x05);	// Channel 0 PWM Duty Cycle	
ECReg	DCR4      		_at_ (FIC628_REG_PWM_BASE | 0x06);	// Channel 0 PWM Duty Cycle	
ECReg	DCR5      		_at_ (FIC628_REG_PWM_BASE | 0x07);	// Channel 0 PWM Duty Cycle	
ECReg	DCR6       		_at_ (FIC628_REG_PWM_BASE | 0x08);	// Channel 0 PWM Duty Cycle	
ECReg	DCR7     		_at_ (FIC628_REG_PWM_BASE | 0x09);	// Channel 0 PWM Duty Cycle	
ECReg	PWMPOL        	_at_ (FIC628_REG_PWM_BASE | 0x0A);	// PWM Polarity
ECReg	PCFSR      		_at_ (FIC628_REG_PWM_BASE | 0x0B);	// Prescaler Clock Frequency Select Register
ECReg	PCSSGL   		_at_ (FIC628_REG_PWM_BASE | 0x0C);	// Prescaler Clock Source Select Group Low
ECReg	PCSSGH    		_at_ (FIC628_REG_PWM_BASE | 0x0D);	// Prescaler Clock Source Select Group High
ECReg	CR256PCSSG		_at_ (FIC628_REG_PWM_BASE | 0x0E);	// CR256 Prescaler Clock Source Select Group
ECReg	PCSGR			_at_ (FIC628_REG_PWM_BASE | 0x0F);	// Prescaler Clock Source Gating Register
ECReg	F1TLRR     		_at_ (FIC628_REG_PWM_BASE | 0x1E);	// Fan 1 Tachometer LSB Reading
ECReg	F1TMRR    		_at_ (FIC628_REG_PWM_BASE | 0x1F);	// Fan 1 Tachometer MSB Reading
ECReg	F2TLRR    		_at_ (FIC628_REG_PWM_BASE | 0x20);	// Fan 2 Tachometer LSB Reading
ECReg	F2TMRR     		_at_ (FIC628_REG_PWM_BASE | 0x21);	// Fan 2 Tachometer MSB Reading
ECReg	ZINTSCR   		_at_ (FIC628_REG_PWM_BASE | 0x22);	// Zone Interrupt Status Control
ECReg	ZTIER      		_at_ (FIC628_REG_PWM_BASE | 0x23);	// PWM Clock Control Register
ECReg	TSWCTLR    		_at_ (FIC628_REG_PWM_BASE | 0x24);	// Tachometer Switch Control Register
ECReg	C4CPRS    		_at_ (FIC628_REG_PWM_BASE | 0x27);	// Channel 4 Clock Prescaler Register
ECReg	C4MCPRS    		_at_ (FIC628_REG_PWM_BASE | 0x28);	// Channel 4 Clock Prescaler MSB Register
ECReg	C6CPRS    		_at_ (FIC628_REG_PWM_BASE | 0x2B);	// Channel 6 Clock Prescaler Register
ECReg	C6MCPRS    		_at_ (FIC628_REG_PWM_BASE | 0x2C);	// Channel 6 Clock Prescaler MSB Register
ECReg	C7CPRS     		_at_ (FIC628_REG_PWM_BASE | 0x2D);	// Channel 7 Clock Prescaler Register
ECReg	C7MCPRS    		_at_ (FIC628_REG_PWM_BASE | 0x2E);	// Channel 7 Clock Prescaler MSB Register
ECReg	CLK6MSEL   		_at_ (FIC628_REG_PWM_BASE | 0x40);	// PWM Clock 6MHz Select Register
ECReg	CTR1    		_at_ (FIC628_REG_PWM_BASE | 0x41);	// Cycle Time 1
ECReg	CTR2    		_at_ (FIC628_REG_PWM_BASE | 0x42);	// Cycle Time 2
ECReg	CTR3    		_at_ (FIC628_REG_PWM_BASE | 0x43);	// Cycle Time 3
ECReg	PWM5TOCTRL		_at_ (FIC628_REG_PWM_BASE | 0x44);	// PWM5 Timeout Control Register
ECReg	CFLRR    		_at_ (FIC628_REG_PWM_BASE | 0x45);	// Color Frequency LSB Register
ECReg	CFMRR    		_at_ (FIC628_REG_PWM_BASE | 0x46);	// Color Frequency MSB Register
ECReg	CFINTCTRL		_at_ (FIC628_REG_PWM_BASE | 0x47);	// Color Frequency Interrupt Control Register

ECReg	TSWCTRL    		_at_ (FIC628_REG_PWM_BASE | 0x48);	// Tachometer Switch Control Register
ECReg	PWMODENR		_at_ (FIC628_REG_PWM_BASE | 0x49);	// PWM Output Open-Drain Enable Register

ECReg	PWM0LHE         _at_ (FIC628_REG_PWM_BASE | 0x50);	// PWM0 LED Dimming Enable Register
ECReg	PWM0LCR1		_at_ (FIC628_REG_PWM_BASE | 0x51);	// PWM0 LED Dimming Control Register 1
ECReg	PWM0LCR2		_at_ (FIC628_REG_PWM_BASE | 0x52);	// PWM0 LED Dimming Control Register 2
ECReg	PWM1LHE         _at_ (FIC628_REG_PWM_BASE | 0x53);	// PWM1 LED Dimming Enable Register
ECReg	PWM1LCR1		_at_ (FIC628_REG_PWM_BASE | 0x54);	// PWM1 LED Dimming Control Register 1
ECReg	PWM1LCR2		_at_ (FIC628_REG_PWM_BASE | 0x55);	// PWM1 LED Dimming Control Register 2

//-----------------------------------------------------------------------------
// (19xxh) Analog to Digital converter (ADC) 
//-----------------------------------------------------------------------------
ECReg	ADCSTS			_at_ (FIC628_REG_ADC_BASE | 0x00);	// ADC Status
ECReg	ADCCFG			_at_ (FIC628_REG_ADC_BASE | 0x01);	// ADC Configuration
ECReg	ADCCTL			_at_ (FIC628_REG_ADC_BASE | 0x02);	// ADC Clock Control
ECReg	VCH0CTL			_at_ (FIC628_REG_ADC_BASE | 0x04);	// Voltage Channel 0 Channel Control
ECReg	KDCTL			_at_ (FIC628_REG_ADC_BASE | 0x05);	// Calibration Data Control Register
ECReg	VCH1CTL      	_at_ (FIC628_REG_ADC_BASE | 0x06);	// Voltage Channel 1 Control
ECReg	VCH1DATL     	_at_ (FIC628_REG_ADC_BASE | 0x07);	// Voltage Channel 1 Data Buffer LSB
ECReg	VCH1DATM       	_at_ (FIC628_REG_ADC_BASE | 0x08);	// Voltage Channel 1 Data Buffer MSB
ECReg	VCH2CTL        	_at_ (FIC628_REG_ADC_BASE | 0x09);	// Voltage Channel 2 Control
ECReg	VCH2DATL      	_at_ (FIC628_REG_ADC_BASE | 0x0A);	// Voltage Channel 2 Data Buffer LSB
ECReg	VCH2DATM     	_at_ (FIC628_REG_ADC_BASE | 0x0B);	// Voltage Channel 2 Data Buffer MSB
ECReg	VCH3CTL       	_at_ (FIC628_REG_ADC_BASE | 0x0C);	// Voltage Channel 3 Control
ECReg	VCH3DATL      	_at_ (FIC628_REG_ADC_BASE | 0x0D);	// Voltage Channel 3 Data Buffer LSB
ECReg	VCH3DATM      	_at_ (FIC628_REG_ADC_BASE | 0x0E);	// Voltage Channel 3 Data Buffer MSB
ECReg	VHSCDBL      	_at_ (FIC628_REG_ADC_BASE | 0x14);	// Voltage High Scale Calibration Data Buffer LSB
ECReg	VHSCDBM       	_at_ (FIC628_REG_ADC_BASE | 0x15);	// Voltage High Scale Calibration Data Buffer MSB
ECReg	VCH0DATL		_at_ (FIC628_REG_ADC_BASE | 0x18);	// Voltage Channel 0 Data Buffer LSB
ECReg	VCH0DATM		_at_ (FIC628_REG_ADC_BASE | 0x19);	// Voltage Channel 0 Data Buffer MSB
ECReg	VHSGCDBL      	_at_ (FIC628_REG_ADC_BASE | 0x1C);	// Voltage High Scale Gain-error Calibration Data Buffer LSB
ECReg	VHSGCDBM     	_at_ (FIC628_REG_ADC_BASE | 0x1d);	// Voltage High Scale Gain-error Calibration Data Buffer MSB

ECReg   VCH4CTL         _at_ (FIC628_REG_ADC_BASE | 0x38);    // Voltage Channel 4 Control Register
ECReg   VCH4DATM        _at_ (FIC628_REG_ADC_BASE | 0x39);    // Volt Channel 4 Data Buffer MSB
ECReg   VCH4DATL        _at_ (FIC628_REG_ADC_BASE | 0x3A);    // Volt Channel 4 Data Buffer LSB
ECReg   VCH5CTL         _at_ (FIC628_REG_ADC_BASE | 0x3B);    // Voltage Channel 5 Control Register
ECReg   VCH5DATM        _at_ (FIC628_REG_ADC_BASE | 0x3C);    // Volt Channel 5 Data Buffer MSB
ECReg   VCH5DATL        _at_ (FIC628_REG_ADC_BASE | 0x3D);    // Volt Channel 5 Data Buffer LSB
ECReg   VCH6CTL         _at_ (FIC628_REG_ADC_BASE | 0x3E);    // Voltage Channel 6 Control Register
ECReg   VCH6DATM        _at_ (FIC628_REG_ADC_BASE | 0x3F);    // Volt Channel 6 Data Buffer MSB
ECReg   VCH6DATL        _at_ (FIC628_REG_ADC_BASE | 0x40);    // Volt Channel 6 Data Buffer LSB
ECReg   VCH7CTL         _at_ (FIC628_REG_ADC_BASE | 0x41);    // Voltage Channel 7 Control Register
ECReg   VCH7DATM        _at_ (FIC628_REG_ADC_BASE | 0x42);    // Volt Channel 7 Data Buffer MSB
ECReg   VCH7DATL        _at_ (FIC628_REG_ADC_BASE | 0x43);    // Volt Channel 7 Data Buffer LSB

ECReg   ADCDVSTS        _at_ (FIC628_REG_ADC_BASE | 0x44); 	// ADC Data Valid Status
ECReg   VCMPSTS	        _at_ (FIC628_REG_ADC_BASE | 0x45); 	// Voltage Compare Status
ECReg   VCMP0CTL        _at_ (FIC628_REG_ADC_BASE | 0x46); 	// Voltage Compare 0 Control Register
ECReg   CMP0THRDATM     _at_ (FIC628_REG_ADC_BASE | 0x47);  	// Voltage Comparator 0 Threshold Data Buffer MSB
ECReg   CMP0THRDATL     _at_ (FIC628_REG_ADC_BASE | 0x48); 	// Voltage Comparator 0 Threshold Data Buffer LSB 
ECReg   VCMP1CTL        _at_ (FIC628_REG_ADC_BASE | 0x49); 	// Voltage Compare 1 Control Register 
ECReg   CMP1THRDATM     _at_ (FIC628_REG_ADC_BASE | 0x4A); 	// Voltage Comparator 1 Threshold Data Buffer MSB
ECReg   CMP1THRDATL     _at_ (FIC628_REG_ADC_BASE | 0x4B); 	// Voltage Comparator 1 Threshold Data Buffer LSB
ECReg   VCMP2CTL        _at_ (FIC628_REG_ADC_BASE | 0x4C); 	// Voltage Compare 2 Control Register
ECReg   CMP2THRDATM     _at_ (FIC628_REG_ADC_BASE | 0x4D); 	// Voltage Comparator 2 Threshold Data Buffer MSB
ECReg   CMP2THRDATL     _at_ (FIC628_REG_ADC_BASE | 0x4E); 	// Voltage Comparator 2 Threshold Data Buffer LSB
ECReg   VCMPOTR        	_at_ (FIC628_REG_ADC_BASE | 0x4F); 	// Voltage Comparator Output Type Register
ECReg   VCMPLR        	_at_ (FIC628_REG_ADC_BASE | 0x52); 	// Voltage Comparator Lock Register

//-----------------------------------------------------------------------------
// (1Axxh) Digital to Analog Converter (DAC) 
//-----------------------------------------------------------------------------
ECReg	DACPWRDN      	_at_ (FIC628_REG_DAC_BASE | 0x01);	// DAC Power Down Register
ECReg	DACDAT0      	_at_ (FIC628_REG_DAC_BASE | 0x02);	// DAC Data Channel 0
ECReg	DACDAT1       	_at_ (FIC628_REG_DAC_BASE | 0x03);	// DAC Data Channel 1
ECReg	DACDAT2        	_at_ (FIC628_REG_DAC_BASE | 0x04);	// DAC Data Channel 2
ECReg	DACDAT3       	_at_ (FIC628_REG_DAC_BASE | 0x05);	// DAC Data Channel 3
ECReg	DACDAT4       	_at_ (FIC628_REG_DAC_BASE | 0x06);	// DAC Data Channel 4
ECReg	DACDAT5       	_at_ (FIC628_REG_DAC_BASE | 0x07);	// DAC Data Channel 5

//-----------------------------------------------------------------------------
// (1Bxxh) Wack-Up control (WUC) 
//-----------------------------------------------------------------------------
ECReg	WUEMR1			_at_ (FIC628_REG_WUC_BASE | 0x00);	// Wake-Up Edge Mode Register 1
ECReg	WUEMR2      	_at_ (FIC628_REG_WUC_BASE | 0x01);	// Wake-Up Edge Mode Register 2
ECReg	WUEMR3       	_at_ (FIC628_REG_WUC_BASE | 0x02);	// Wake-Up Edge Mode Register 3
ECReg	WUEMR4       	_at_ (FIC628_REG_WUC_BASE | 0x03);	// Wake-Up Edge Mode Register 4
ECReg	WUEMR6       	_at_ (FIC628_REG_WUC_BASE | 0x10);	// Wake-Up Edge Mode Register 6
ECReg	WUEMR7       	_at_ (FIC628_REG_WUC_BASE | 0x14);	// Wake-Up Edge Mode Register 7
ECReg	WUEMR13       	_at_ (FIC628_REG_WUC_BASE | 0x2C);	// Wake-Up Edge Mode Register 13	//J80_011||
ECReg	WUESR1       	_at_ (FIC628_REG_WUC_BASE | 0x04);	// Wake-Up Edge Sense Register 1
ECReg	WUESR2       	_at_ (FIC628_REG_WUC_BASE | 0x05);	// Wake-Up Edge Sense Register 2
ECReg	WUESR3       	_at_ (FIC628_REG_WUC_BASE | 0x06);	// Wake-Up Edge Sense Register 3
ECReg	WUESR4        	_at_ (FIC628_REG_WUC_BASE | 0x07);	// Wake-Up Edge Sense Register 4
ECReg	WUESR6        	_at_ (FIC628_REG_WUC_BASE | 0x11);	// Wake-Up Edge Sense Register 6
ECReg	WUESR7        	_at_ (FIC628_REG_WUC_BASE | 0x15);	// Wake-Up Edge Sense Register 7
ECReg	WUESR13       	_at_ (FIC628_REG_WUC_BASE | 0x2D);	// Wake-Up Edge Sense Register 13	//J80_011||
ECReg	WUENR1        	_at_ (FIC628_REG_WUC_BASE | 0x08);	// Wake-Up Enable Register 1
ECReg	WUENR2       	_at_ (FIC628_REG_WUC_BASE | 0x09);	// Wake-Up Enable Register 2
ECReg	WUENR3       	_at_ (FIC628_REG_WUC_BASE | 0x0A);	// Wake-Up Enable Register 3
ECReg	WUENR4			_at_ (FIC628_REG_WUC_BASE | 0x0B);	// Wake-Up Enable Register 4
ECReg	WUENR6			_at_ (FIC628_REG_WUC_BASE | 0x12);	// Wake-Up Enable Register 6
ECReg	WUENR7			_at_ (FIC628_REG_WUC_BASE | 0x16);	// Wake-Up Enable Register 7

//-----------------------------------------------------------------------------
// (1Cxxh) SMBus Interface (SMB) 
//-----------------------------------------------------------------------------
ECReg	HOSTA_A      	_at_ (FIC628_REG_SMBUS_BASE | 0x00);	// Host Status A
ECReg	HOSTA_B      	_at_ (FIC628_REG_SMBUS_BASE | 0x11);	// Host Status B
ECReg	HOSTA_C      	_at_ (FIC628_REG_SMBUS_BASE | 0x29);	// Host Status C
ECReg	HOSTA_D      	_at_ (FIC628_REG_SMBUS_BASE | 0x35);	// Host Status D
ECReg	HOCTL_A       	_at_ (FIC628_REG_SMBUS_BASE | 0x01);	// Host Control A
ECReg	HOCTL_B       	_at_ (FIC628_REG_SMBUS_BASE | 0x12);	// Host Control B
ECReg	HOCTL_C       	_at_ (FIC628_REG_SMBUS_BASE | 0x2A);	// Host Control C
ECReg	HOCTL_D       	_at_ (FIC628_REG_SMBUS_BASE | 0x36);	// Host Control D
ECReg	HOCMD_A       	_at_ (FIC628_REG_SMBUS_BASE | 0x02);	// Host Command A
ECReg	HOCMD_B       	_at_ (FIC628_REG_SMBUS_BASE | 0x13);	// Host Command B
ECReg	HOCMD_C       	_at_ (FIC628_REG_SMBUS_BASE | 0x2B);	// Host Command C
ECReg	HOCMD_D       	_at_ (FIC628_REG_SMBUS_BASE | 0x37);	// Host Command D
ECReg	TRASLA_A      	_at_ (FIC628_REG_SMBUS_BASE | 0x03);	// Transmit Slave Address A
ECReg	TRASLA_B      	_at_ (FIC628_REG_SMBUS_BASE | 0x14);	// Transmit Slave Address B
ECReg	TRASLA_C      	_at_ (FIC628_REG_SMBUS_BASE | 0x2C);	// Transmit Slave Address C
ECReg	TRASLA_D      	_at_ (FIC628_REG_SMBUS_BASE | 0x38);	// Transmit Slave Address D
ECReg	D0REG_A       	_at_ (FIC628_REG_SMBUS_BASE | 0x04);	// Host Data 0 A
ECReg	D0REG_B       	_at_ (FIC628_REG_SMBUS_BASE | 0x15);	// Host Data 0 B
ECReg	D0REG_C       	_at_ (FIC628_REG_SMBUS_BASE | 0x2D);	// Host Data 0 C
ECReg	D0REG_D       	_at_ (FIC628_REG_SMBUS_BASE | 0x39);	// Host Data 0 D
ECReg	D1REG_A       	_at_ (FIC628_REG_SMBUS_BASE | 0x05);	// Host Data 1 A
ECReg	D1REG_B      	_at_ (FIC628_REG_SMBUS_BASE | 0x16);	// Host Data 1 B
ECReg	D1REG_C      	_at_ (FIC628_REG_SMBUS_BASE | 0x2E);	// Host Data 1 C
ECReg	D1REG_D      	_at_ (FIC628_REG_SMBUS_BASE | 0x3A);	// Host Data 1 D
ECReg	HOBDB_A       	_at_ (FIC628_REG_SMBUS_BASE | 0x06);	// Host Block Data Byte A
ECReg	HOBDB_B        	_at_ (FIC628_REG_SMBUS_BASE | 0x17);	// Host Block Data Byte B
ECReg	HOBDB_C        	_at_ (FIC628_REG_SMBUS_BASE | 0x2F);	// Host Block Data Byte C
ECReg	HOBDB_D        	_at_ (FIC628_REG_SMBUS_BASE | 0x3B);	// Host Block Data Byte D
ECReg	PECERC_A      	_at_ (FIC628_REG_SMBUS_BASE | 0x07);	// Packet Error Check A
ECReg	PECERC_B    	_at_ (FIC628_REG_SMBUS_BASE | 0x18);	// Packet Error Check B
ECReg	PECERC_C    	_at_ (FIC628_REG_SMBUS_BASE | 0x30);	// Packet Error Check C
ECReg	PECERC_D    	_at_ (FIC628_REG_SMBUS_BASE | 0x3C);	// Packet Error Check D

// 改版本中的slave 没用到 ---------------------------------------------------->
ECReg	RESLADR_A		_at_ (FIC628_REG_SMBUS_BASE | 0x08);	// Receive Slave Adress A
ECReg	RESLADR_B		_at_ (FIC628_REG_SMBUS_BASE | 0x19);	// Receive Slave Adress B
ECReg	RESLADR_2_A		_at_ (FIC628_REG_SMBUS_BASE | 0x3F);	// Receive Slave Adress_2 A
ECReg	RESLADR_2_B		_at_ (FIC628_REG_SMBUS_BASE | 0x44);	// Receive Slave Adress_2 B
ECReg	SLDA_A			_at_ (FIC628_REG_SMBUS_BASE | 0x09);	// Slave Data A
ECReg	SLDA_B			_at_ (FIC628_REG_SMBUS_BASE | 0x1A);	// Slave Data B
//----------------------------------------------------------------------------<

ECReg	SMBPCTL_A      	_at_ (FIC628_REG_SMBUS_BASE | 0x0A);	// SMBUS Pin Control A
ECReg	SMBPCTL_B      	_at_ (FIC628_REG_SMBUS_BASE | 0x1B);	// SMBUS Pin Control B
ECReg	SMBPCTL_C      	_at_ (FIC628_REG_SMBUS_BASE | 0x31);	// SMBUS Pin Control C
ECReg	SMBPCTL_D      	_at_ (FIC628_REG_SMBUS_BASE | 0x3D);	// SMBUS Pin Control D

// 没用到-------------------------------------------------------------------->
ECReg	SLSTA_A			_at_ (FIC628_REG_SMBUS_BASE | 0x0B);	// Slave Status A
ECReg	SLSTA_B			_at_ (FIC628_REG_SMBUS_BASE | 0x1C);	// Slave Status B
ECReg	SICR_A			_at_ (FIC628_REG_SMBUS_BASE | 0x0C);	// Slave Interrupt Control A
ECReg	SICR_B			_at_ (FIC628_REG_SMBUS_BASE | 0x1D);	// Slave Interrupt Control B
ECReg	NDADR_A			_at_ (FIC628_REG_SMBUS_BASE | 0x0D);	// Notify Device Adress A
ECReg	NDADR_B			_at_ (FIC628_REG_SMBUS_BASE | 0x1E);	// Notify Device Adress B
ECReg	NDLB_A			_at_ (FIC628_REG_SMBUS_BASE | 0x0E);	// Notify Data Low Byte A
ECReg	NDLB_B			_at_ (FIC628_REG_SMBUS_BASE | 0x1F);	// Notify Data Low Byte B
ECReg	NDHB_A			_at_ (FIC628_REG_SMBUS_BASE | 0x0F);	// Notify Data High Byte A
ECReg	NDHB_B			_at_ (FIC628_REG_SMBUS_BASE | 0x20);	// Notify Data High Byte B
//--------------------------------------------------------------------------<

ECReg	HOCTL2_A      	_at_ (FIC628_REG_SMBUS_BASE | 0x10);	// Host Control2 A
ECReg	HOCTL2_B      	_at_ (FIC628_REG_SMBUS_BASE | 0x21);	// Host Control2 B
ECReg	HOCTL2_C      	_at_ (FIC628_REG_SMBUS_BASE | 0x32);	// Host Control2 C
ECReg	HOCTL2_D      	_at_ (FIC628_REG_SMBUS_BASE | 0x3E);	// Host Control2 D
ECReg	SMB4P7USL   	_at_ (FIC628_REG_SMBUS_BASE | 0x22);	// 4.7 �gs Low Register
ECReg	SMB4P0USH   	_at_ (FIC628_REG_SMBUS_BASE | 0x23);	// 4.7 �gs High Register
ECReg	SMB300NS  		_at_ (FIC628_REG_SMBUS_BASE | 0x24);	// 300 ns Register
ECReg	SMB250NS  		_at_ (FIC628_REG_SMBUS_BASE | 0x25);	// 250 ns Register
ECReg	SMB25MS   		_at_ (FIC628_REG_SMBUS_BASE | 0x26);	// 25 ms Register
ECReg	SMB45P3USL 		_at_ (FIC628_REG_SMBUS_BASE | 0x27);	// 45.3 �gs Low Register
ECReg	SMBS4P3USH 		_at_ (FIC628_REG_SMBUS_BASE | 0x28);	// 45.3 �gs High Register
ECReg	SMB4P7A4P0H		_at_ (FIC628_REG_SMBUS_BASE | 0x33);	// 4.7 �gs and 4.0 �gs High Register

ECReg   SMB_FIC_CTRL1   _at_ (FIC628_REG_SMBUS_BASE | 0xC1);   // 新增功能

// 没用到-------------------------------------------------------------------->
ECReg	SLVISEL			_at_ (FIC628_REG_SMBUS_BASE | 0x34);	// Slave Interface Select
ECReg	SCLKTS_A		_at_ (FIC628_REG_SMBUS_BASE | 0x40);	// SMCLK Timing Setting Register A
ECReg	SCLKTS_B		_at_ (FIC628_REG_SMBUS_BASE | 0x41);	// SMCLK Timing Setting Register B
ECReg	SCLKTS_C		_at_ (FIC628_REG_SMBUS_BASE | 0x42);	// SMCLK Timing Setting Register C
ECReg	SCLKTS_D		_at_ (FIC628_REG_SMBUS_BASE | 0x43);	// SMCLK Timing Setting Register D
//--------------------------------------------------------------------------<

//-----------------------------------------------------------------------------
// (1Dxxh) Keyboard Matrix Scan control (KBS) 
//-----------------------------------------------------------------------------
ECReg	KSOL          	_at_ (FIC628_REG_KBS_BASE | 0x00);	// Keyboard Scan Out
ECReg	KSOH1          	_at_ (FIC628_REG_KBS_BASE | 0x01);	// Keyboard Scan Out
ECReg	KSOCTRL      	_at_ (FIC628_REG_KBS_BASE | 0x02);	// Keyboard Scan Out Control
ECReg	KSOH2			_at_ (FIC628_REG_KBS_BASE | 0x03);	// Keyboard Scan Out
ECReg	KSI           	_at_ (FIC628_REG_KBS_BASE | 0x04);	// Keyboard Scan In
ECReg	KSICTRL       	_at_ (FIC628_REG_KBS_BASE | 0x05);	// Keyboard Scan In Control

ECReg	KSIGCTRL       	_at_ (FIC628_REG_KBS_BASE | 0x06);	// Keyboard Scan In [7:0] GPIO Control
ECReg	KSIGOEN       	_at_ (FIC628_REG_KBS_BASE | 0x07);	// Keyboard Scan In [7:0] GPIO Output Enable
ECReg	KSIGDAT       	_at_ (FIC628_REG_KBS_BASE | 0x08);	// Keyboard Scan In [7:0] GPIO DATA
ECReg	KSIGDMRR       	_at_ (FIC628_REG_KBS_BASE | 0x09);	// Keyboard Scan In [7:0] GPIO DATA Mirror
ECReg	KSOHGCTRL       _at_ (FIC628_REG_KBS_BASE | 0x0A);	// Keyboard Scan Out [15:8] GPIO Control
ECReg	KSOHGOEN       	_at_ (FIC628_REG_KBS_BASE | 0x0B);	// Keyboard Scan Out [15:8] GPIO Output Enable
ECReg	KSOHGDMRR       _at_ (FIC628_REG_KBS_BASE | 0x0C);	// Keyboard Scan Out [15:8] GPIO DATA Mirror
ECReg	KSOLGCTRL       _at_ (FIC628_REG_KBS_BASE | 0x0D);	// Keyboard Scan Out [7:0] GPIO Control
ECReg	KSOLGOEN       	_at_ (FIC628_REG_KBS_BASE | 0x0E);	// Keyboard Scan Out [7:0] GPIO Output Enable
ECReg	KSOLGDMRR       _at_ (FIC628_REG_KBS_BASE | 0x0F);	// Keyboard Scan Out [7:0] GPIO DATA Mirror


ECReg	KSO0LSDR        _at_ (FIC628_REG_KBS_BASE | 0x10);	// KSO1 Low Scan Data Register
ECReg	KSO1LSDR        _at_ (FIC628_REG_KBS_BASE | 0x11);	// KSO1 Low Scan Data Register
ECReg	KSO2LSDR      	_at_ (FIC628_REG_KBS_BASE | 0x12);	// KSO2 Low Scan Data Register
ECReg	KSO3LSDR	    _at_ (FIC628_REG_KBS_BASE | 0x13);	// KSO3 Low Scan Data Register
ECReg	KSO4LSDR        _at_ (FIC628_REG_KBS_BASE | 0x14);	// KSO4 Low Scan Data Register
ECReg	KSO5LSDR       	_at_ (FIC628_REG_KBS_BASE | 0x15);	// KSO5 Low Scan Data Register
ECReg	KSO6LSDR       	_at_ (FIC628_REG_KBS_BASE | 0x16);	// KSO6 Low Scan Data Register
ECReg	KSO7LSDR       	_at_ (FIC628_REG_KBS_BASE | 0x17);	// KSO7 Low Scan Data Register
ECReg	KSO8LSDR       	_at_ (FIC628_REG_KBS_BASE | 0x18);	// KSO8 Low Scan Data Register
ECReg	KSO9LSDR       	_at_ (FIC628_REG_KBS_BASE | 0x19);	// KSO9 Low Scan Data Register
ECReg	KSO10LSDR       _at_ (FIC628_REG_KBS_BASE | 0x1A);	// KSO10 Low Scan Data Register
ECReg	KSO11LSDR       _at_ (FIC628_REG_KBS_BASE | 0x1B);	// KSO11 Low Scan Data Register
ECReg	KSO12LSDR       _at_ (FIC628_REG_KBS_BASE | 0x1C);	// KSO12 Low Scan Data Register
ECReg	KSO13LSDR       _at_ (FIC628_REG_KBS_BASE | 0x1D);	// KSO13 Low Scan Data Register
ECReg	KSO14LSDR       _at_ (FIC628_REG_KBS_BASE | 0x1E);	// KSO14 Low Scan Data Register
ECReg	KSO15LSDR       _at_ (FIC628_REG_KBS_BASE | 0x1F);	// KSO15 Low Scan Data Register
ECReg	KSO16LSDR       _at_ (FIC628_REG_KBS_BASE | 0x20);	// KSO16 Low Scan Data Register
ECReg	KSO17LSDR       _at_ (FIC628_REG_KBS_BASE | 0x21);	// KSO17 Low Scan Data Register
ECReg	SDCR1      	    _at_ (FIC628_REG_KBS_BASE | 0x22);	// Scan Data Control1 Register 
ECReg	SDCR2			_at_ (FIC628_REG_KBS_BASE | 0x23);	// Scan Data Control2 Register 
ECReg	SDCR3           _at_ (FIC628_REG_KBS_BASE | 0x24);	// Scan Data Control3 Register 
ECReg	SDSR       	    _at_ (FIC628_REG_KBS_BASE | 0x25);	// Scan Data Status Register

//-----------------------------------------------------------------------------
// (1Exxh) EC Clock and Power Management controller (ECPM) 
//-----------------------------------------------------------------------------
ECReg	CGCTRL1R    	_at_ (FIC628_REG_ECPM_BASE | 0x01);	// Clock Gating Control 1
ECReg	CGCTRL2R      	_at_ (FIC628_REG_ECPM_BASE | 0x02);	// Clock Gating Control 2
ECReg	CGCTRL3R		_at_ (FIC628_REG_ECPM_BASE | 0x05);	// Clock Gating Control 3
ECReg	PLLCTRL        	_at_ (FIC628_REG_ECPM_BASE | 0x03);	// PLL Control
ECReg	AUTOCG			_at_ (FIC628_REG_ECPM_BASE | 0x04);	// Auto Clock Gating
ECReg	PLLFREQR		_at_ (FIC628_REG_ECPM_BASE | 0x06);	// PLL Frequency
ECReg	PLLSSCR			_at_ (FIC628_REG_ECPM_BASE | 0x07);	// PLL Frequency
//-----------------------------------------------------------------------------
// (1Fxxh) External Timer & External Watchdog (ETWD) 
//-----------------------------------------------------------------------------
ECReg	ETWCFG        	_at_ (FIC628_REG_ETWD_BASE | 0x01);	// External Timer/WDT Configuration Register
ECReg	ETPSR         	_at_ (FIC628_REG_ETWD_BASE | 0x02);	// External Timer Prescaler Register
ECReg	ETCNTLHR     	_at_ (FIC628_REG_ETWD_BASE | 0x03);	// External Timer Counter High Byte
ECReg	ETCNTLLR      	_at_ (FIC628_REG_ETWD_BASE | 0x04);	// External Timer Counter Low Byte
ECReg	ETWCTRL      	_at_ (FIC628_REG_ETWD_BASE | 0x05);	// External Timer/WDT Control Register
ECReg	EWDCNTLR      	_at_ (FIC628_REG_ETWD_BASE | 0x06);	// External WDT Counter Low Byte
ECReg	EWDKEYR      	_at_ (FIC628_REG_ETWD_BASE | 0x07);	// External WDT Key Register
ECReg	EWDCNTHR		_at_ (FIC628_REG_ETWD_BASE | 0x09);	// External WDT Counter High Byte

ECReg	ET2PSR      	_at_ (FIC628_REG_ETWD_BASE | 0x0A);	// External Timer 2 Prescaler Register
ECReg	ET2CNTLHR      	_at_ (FIC628_REG_ETWD_BASE | 0x0B);	// External Timer 2 Counter High Byte
ECReg	ET2CNTLLR      	_at_ (FIC628_REG_ETWD_BASE | 0x0C);	// External Timer 2 Counter Low Byte
ECReg	ET2CNTLH2R		_at_ (FIC628_REG_ETWD_BASE | 0x0E);	// External Timer 2 Counter High Byte 

//-----------------------------------------------------------------------------
// General Control (GCTRL) (20xxh)
//-----------------------------------------------------------------------------
ECReg	ECHIPID1		_at_ (FIC628_REG_GCTRL_BASE | 0x00);	// Chip ID Byte 1
ECReg	ECHIPID2		_at_ (FIC628_REG_GCTRL_BASE | 0x01);	// Chip ID Byte 2
ECReg	ECHIPVER		_at_ (FIC628_REG_GCTRL_BASE | 0x02);	// Chip Version
ECReg	IDR				_at_ (FIC628_REG_GCTRL_BASE | 0x04);	// Identify Input Register
ECReg	RSTS			_at_ (FIC628_REG_GCTRL_BASE | 0x06);	// Reset Status
ECReg	RSTC1			_at_ (FIC628_REG_GCTRL_BASE | 0x07);	// Reset Control 1
ECReg	RSTC2			_at_ (FIC628_REG_GCTRL_BASE | 0x08);	// Reset Control 2
ECReg	RSTC3			_at_ (FIC628_REG_GCTRL_BASE | 0x09);	// Reset Control 3
ECReg	RSTC4			_at_ (FIC628_REG_GCTRL_BASE | 0x11);	// Reset Control 4
ECReg	RSTDMMC			_at_ (FIC628_REG_GCTRL_BASE | 0x10);	// Reset Control DMMC
ECReg	BADRSEL			_at_ (FIC628_REG_GCTRL_BASE | 0x0A);	// Base Address Select
ECReg	WNCKR			_at_ (FIC628_REG_GCTRL_BASE | 0x0B);	// Wait Next Clock Rising
ECReg	OSCTRL			_at_ (FIC628_REG_GCTRL_BASE | 0x0C);	// Oscillator Control Register
ECReg	SPCTRL1			_at_ (FIC628_REG_GCTRL_BASE | 0x0D);	// Special Control 1
ECReg	RSTCH			_at_ (FIC628_REG_GCTRL_BASE | 0x0E);	// Reset Control Host Side
ECReg	GENIRQ			_at_ (FIC628_REG_GCTRL_BASE | 0x0F);	// Generate IRQ
ECReg	SPECTRL2		_at_ (FIC628_REG_GCTRL_BASE | 0x12);	// Special Control 2
ECReg	SPECTRL3		_at_ (FIC628_REG_GCTRL_BASE | 0x16);	// Special Control 3

ECReg	PI2ECH			_at_ (FIC628_REG_GCTRL_BASE | 0x14);	// Port I2EC High-Byte Register
ECReg	PI2ECL			_at_ (FIC628_REG_GCTRL_BASE | 0x15);	// Port I2EC Low-Byte Register
ECReg	BINTADDR0R		_at_ (FIC628_REG_GCTRL_BASE | 0x19);	// BRAM Interrupt Address 0 Register
ECReg	BINTADDR1R		_at_ (FIC628_REG_GCTRL_BASE | 0x1A);	// BRAM Interrupt Address 1 Register
ECReg	BINTCTRLR		_at_ (FIC628_REG_GCTRL_BASE | 0x1B);	// BRAM Interrupt Control Register
ECReg	SPCTRL4	   	 	_at_ (FIC628_REG_GCTRL_BASE | 0x1C);	// PG 状态寄存器


//-----------------------------------------------------------------------------
// (21xxh) External GPIO Controller (EGPC) 
//-----------------------------------------------------------------------------
ECReg	EADDR			_at_ (FIC628_REG_EGPC_BASE | 0x00);	// External GPIO Address Register
ECReg	EDAT			_at_ (FIC628_REG_EGPC_BASE | 0x01);	// External GPIO Data Register
ECReg	ECNT			_at_ (FIC628_REG_EGPC_BASE | 0x02);	// External GPIO Control Register
ECReg	ESTS			_at_ (FIC628_REG_EGPC_BASE | 0x03);	// External GPIO Status Register

//-----------------------------------------------------------------------------
// (22xxh) Battery-Backed SRAM (BRAM) 
//-----------------------------------------------------------------------------
ECReg	BRAM[64]			_at_ (FIC628_REG_BRAM_BASE | 0x80);	// 64 bytes bram
ECReg	BRAM_OEM[128]		_at_ (FIC628_REG_BRAM_BASE | 0x00);	// 10 bytes bram

//-----------------------------------------------------------------------------
// (23xxh) Consumer IR (CIR) 
//-----------------------------------------------------------------------------
ECReg	C0DR			_at_ (FIC628_REG_CIR_BASE | 0x00);	// CIR Data Register
ECReg	C0MSTCR			_at_ (FIC628_REG_CIR_BASE | 0x01); 	// CIR Master Control Register
ECReg	C0IER			_at_ (FIC628_REG_CIR_BASE | 0x02); 	// CIR Interrupt Enable Register
ECReg	C0IIR			_at_ (FIC628_REG_CIR_BASE | 0x03);	// CIR Interrupt Identification Register
ECReg	C0CFR			_at_ (FIC628_REG_CIR_BASE | 0x04);	// CIR Carrier Frequency Register
ECReg	C0RCR			_at_ (FIC628_REG_CIR_BASE | 0x05);	// CIR Receive Control Register
ECReg	C0TCR			_at_ (FIC628_REG_CIR_BASE | 0x06);	// CIR Transmitter Register
ECReg	C0SCK			_at_ (FIC628_REG_CIR_BASE | 0x07);	// CIR for sleep mode
ECReg	C0BDLR			_at_ (FIC628_REG_CIR_BASE | 0x08);	// CIR Baud Rate Divisor Low Byte Register
ECReg	C0BDHR			_at_ (FIC628_REG_CIR_BASE | 0x09);	// CIR Baud Rate Divisor High Byte Register
ECReg	C0TFSR			_at_ (FIC628_REG_CIR_BASE | 0x0A);	// CIR Transmitter FIFO Status Register
ECReg	C0RFSR			_at_ (FIC628_REG_CIR_BASE | 0x0B);	// CIR Receiver FIFO Status Register
ECReg	C0WCSSR			_at_ (FIC628_REG_CIR_BASE | 0x0C);	// CIR Wakeup Code Set Select Register
ECReg	C0WCL			_at_ (FIC628_REG_CIR_BASE | 0x0D);	// CIR Wakeup Code Length Register
ECReg	C0WCR			_at_ (FIC628_REG_CIR_BASE | 0x0E);	// CIR Wakeup Code Read/Write Register
ECReg	C0WPS			_at_ (FIC628_REG_CIR_BASE | 0x0F);	// CIR Wakeup Code Power Control/Status Register
ECReg	CSCRR			_at_ (FIC628_REG_CIR_BASE | 0x10);	// CIR Scratch Register

//-----------------------------------------------------------------------------
// (25xxh) Debugger (DBGR) 
//-----------------------------------------------------------------------------
ECReg 	BKA1L           _at_ (FIC628_REG_DBGR_BASE | 0x10);	// Trigger 1 Address Low Byte Register
ECReg 	BKA1M           _at_ (FIC628_REG_DBGR_BASE | 0x11);	// Trigger 1 Address Middle Byte Register
ECReg 	BKA1H           _at_ (FIC628_REG_DBGR_BASE | 0x12);	// Trigger 1 Address High Byte Register
ECReg 	BKA2L           _at_ (FIC628_REG_DBGR_BASE | 0x13);	// Trigger 2 Address Low Byte Register
ECReg 	BKA2M           _at_ (FIC628_REG_DBGR_BASE | 0x14);	// Trigger 2 Address Middle Byte Register
ECReg 	BKA2H           _at_ (FIC628_REG_DBGR_BASE | 0x15);	// Trigger 2 Address High Byte Register
ECReg 	BKA3L           _at_ (FIC628_REG_DBGR_BASE | 0x16);	// Trigger 3 Address Low Byte Register
ECReg 	BKA3M           _at_ (FIC628_REG_DBGR_BASE | 0x17);	// Trigger 3 Address Middle Byte Register
ECReg 	BKA3H           _at_ (FIC628_REG_DBGR_BASE | 0x18);	// Trigger 3 Address High Byte Register

//-----------------------------------------------------------------------------
// (26xxh) Serial Peripheral Interface (SSPI) 
//-----------------------------------------------------------------------------
ECReg 	SPIDATA			_at_ (FIC628_REG_SSPI_BASE | 0x00);	// SPI Data Register
ECReg 	SPICTRL1		_at_ (FIC628_REG_SSPI_BASE | 0x01);	// SPI Control 1 Register
ECReg 	SPICTRL2		_at_ (FIC628_REG_SSPI_BASE | 0x02);	// SPI Control 2 Register
ECReg 	SPICTRL3		_at_ (FIC628_REG_SSPI_BASE | 0x04);	// SPI Control 3 Register
ECReg 	SPISTS			_at_ (FIC628_REG_SSPI_BASE | 0x03);	// SPI Status Register

//-----------------------------------------------------------------------------
// (27xxh) Extern Serial Port (UART1) 
//-----------------------------------------------------------------------------
ECReg 	UART1_RBR		_at_ (FIC628_REG_UART1_BASE |  0x00);	// Receiver Buffer Register
ECReg 	UART1_IER		_at_ (FIC628_REG_UART1_BASE |  0x01);	// Interrupt Enable Register
ECReg 	UART1_IIR		_at_ (FIC628_REG_UART1_BASE |  0x02);	// Interrupt Identification Register
ECReg 	UART1_LCR		_at_ (FIC628_REG_UART1_BASE |  0x03);	// Line Control Register
ECReg 	UART1_MCR		_at_ (FIC628_REG_UART1_BASE |  0x04);	// Modem Control Register
ECReg 	UART1_LSR		_at_ (FIC628_REG_UART1_BASE |  0x05);	// Line Status Register
ECReg 	UART1_MSR		_at_ (FIC628_REG_UART1_BASE |  0x06);	// Modem Status Register
ECReg 	UART1_SCR		_at_ (FIC628_REG_UART1_BASE |  0x07);	// Scratch Pad Register
ECReg 	UART1_ECSPMR	_at_ (FIC628_REG_UART1_BASE |  0x08);	// EC Serial Port Mode Register

//-----------------------------------------------------------------------------
// (28xxh) Extern Serial Port (UART2) 
//-----------------------------------------------------------------------------
ECReg 	UART2_RBR		_at_ (FIC628_REG_UART2_BASE |  0x00);	// Receiver Buffer Register
ECReg 	UART2_IER		_at_ (FIC628_REG_UART2_BASE |  0x01);	// Interrupt Enable Register
ECReg 	UART2_IIR		_at_ (FIC628_REG_UART2_BASE |  0x02);	// Interrupt Identification Register
ECReg 	UART2_LCR		_at_ (FIC628_REG_UART2_BASE |  0x03);	// Line Control Register
ECReg 	UART2_MCR		_at_ (FIC628_REG_UART2_BASE |  0x04);	// Modem Control Register
ECReg 	UART2_LSR		_at_ (FIC628_REG_UART2_BASE |  0x05);	// Line Status Register
ECReg 	UART2_MSR		_at_ (FIC628_REG_UART2_BASE |  0x06);	// Modem Status Register
ECReg 	UART2_SCR		_at_ (FIC628_REG_UART2_BASE |  0x07);	// Scratch Pad Register
ECReg 	UART2_ECSPMR	_at_ (FIC628_REG_UART2_BASE |  0x08);	// EC Serial Port Mode Register

//-----------------------------------------------------------------------------
// (29xxh) 8 Bit Timer (TMR)
//-----------------------------------------------------------------------------
ECReg	PRSC			_at_ (FIC628_REG_TMR_BASE |  0x00);	// TMR Prescaler Register
ECReg	GCSMS			_at_ (FIC628_REG_TMR_BASE |  0x01);	// Group Clock Source and Mode Select Register
ECReg	CTR_A0			_at_ (FIC628_REG_TMR_BASE |  0x02);	// A0 Cycle Time Register
ECReg	CTR_A1			_at_ (FIC628_REG_TMR_BASE |  0x03);	// A1 Cycle Time Register
ECReg	CTR_B0			_at_ (FIC628_REG_TMR_BASE |  0x04);	// B0 Cycle Time Register
ECReg	CTR_B1			_at_ (FIC628_REG_TMR_BASE |  0x05);	// B1 Cycle Time Register
ECReg	DCR_A0			_at_ (FIC628_REG_TMR_BASE |  0x06);	// A0 Duty Time Register
ECReg	DCR_A1			_at_ (FIC628_REG_TMR_BASE |  0x07);	// A1 Duty Time Register
ECReg	DCR_B0			_at_ (FIC628_REG_TMR_BASE |  0x08);	// B0 Duty Time Register
ECReg	DCR_B1			_at_ (FIC628_REG_TMR_BASE |  0x09);	// B1 Duty Time Register
ECReg	CCGSR			_at_ (FIC628_REG_TMR_BASE |  0x0A);	// Channel Clock Group Select Register
ECReg	TMRCE			_at_ (FIC628_REG_TMR_BASE |  0x0B);	// TMR Clock Enable Register
ECReg	TMEIE			_at_ (FIC628_REG_TMR_BASE |  0x0C);	// TMR Interrupt Enable Register
//-----------------------------------------------------------------------------
// (30xxh) Platform Environment Control Interface (PECI)
//-----------------------------------------------------------------------------
ECReg   HOSTAR          _at_ (FIC628_REG_PECI_BASE | 0x00);    // Host Status Register
ECReg   HOCTLR          _at_ (FIC628_REG_PECI_BASE | 0x01);    // Host Control Register
ECReg   HOCMDR          _at_ (FIC628_REG_PECI_BASE | 0x02);    // Host Command Register
ECReg   HOTRADDR        _at_ (FIC628_REG_PECI_BASE | 0x03);    // Host Target Address Register
ECReg   HOWRLR          _at_ (FIC628_REG_PECI_BASE | 0x04);    // Host Write Length Register
ECReg   HORDLR          _at_ (FIC628_REG_PECI_BASE | 0x05);    // Host Read Length Register
ECReg   HOWRDR          _at_ (FIC628_REG_PECI_BASE | 0x06);    // Host Write Data Register
ECReg   HORDDR          _at_ (FIC628_REG_PECI_BASE | 0x07);    // Host Read Data Register

ECReg   HOCTL2R         _at_ (FIC628_REG_PECI_BASE | 0x08);    // Host Control 2 Register
