/*-----------------------------------------------------------------------------
 * TITLE: OEM_GPIO.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------
// External ram GPIO Registers 
//-----------------------------------------------------------------
const sInitGPIOReg code asInitGPIOReg[] = 
{
 	{ &GCR,		GCR_Init		},	// 
 	{ &GCR2,	GCR2_Init		},	//
 	{ &GPOTD,	0x80		    },  // D7, Open-drain output
 	
	{ &GPDRA,	PortA_Init		},	// Port A Data port Init    46
	{ &GPDRB,	PortB_Init		},	// Port B Data port Init    82
	{ &GPDRC,	PortC_Init		},	// Port C Data port Init    00
	{ &GPDRD,	PortD_Init		},	// Port D Data port Init    01
	{ &GPDRE,	PortE_Init		},	// Port E Data port Init    00
	{ &GPDRF,	PortF_Init		},	// Port F Data port Init    00
	{ &GPDRG,	PortG_Init		},	// Port G Data port Init    00
	{ &GPDRH,	PortH_Init		},	// Port H Data port Init    00
	{ &GPDRI,	PortI_Init		},	// Port I Data port Init    04
	{ &GPDRJ,	PortJ_Init		},	// Port J Data port Init    04

	{ &GPCRA0,	PortA0_Ctrl		},
	{ &GPCRA1,	PortA1_Ctrl		},
	{ &GPCRA2,	PortA2_Ctrl		},
	{ &GPCRA3,	PortA3_Ctrl		},
	{ &GPCRA4,	PortA4_Ctrl		},
	{ &GPCRA5,	PortA5_Ctrl		},
	{ &GPCRA6,	PortA6_Ctrl		},
	{ &GPCRA7,	PortA7_Ctrl		},
	
	{ &GPCRB0,	PortB0_Ctrl		},
	{ &GPCRB1,	PortB1_Ctrl		},
	{ &GPCRB2,	PortB2_Ctrl		},
	{ &GPCRB3,	PortB3_Ctrl		},
	{ &GPCRB4,	PortB4_Ctrl		},
	{ &GPCRB5,	PortB5_Ctrl		},
	{ &GPCRB6,	PortB6_Ctrl		},
	{ &GPCRB7,	PortB7_Ctrl		},

	{ &GPCRC0,	PortC0_Ctrl		},
	{ &GPCRC1,	PortC1_Ctrl		},
	{ &GPCRC2,	PortC2_Ctrl		},
	{ &GPCRC3,	PortC3_Ctrl		},
	{ &GPCRC4,	PortC4_Ctrl		},
	{ &GPCRC5,	PortC5_Ctrl		},
	{ &GPCRC6,	PortC6_Ctrl		},
	{ &GPCRC7,	PortC7_Ctrl		},

   	{ &GPCRD0,	PortD0_Ctrl		},
	{ &GPCRD1,	PortD1_Ctrl		},
	{ &GPCRD2,	PortD2_Ctrl		},
	{ &GPCRD3,	PortD3_Ctrl		},
	{ &GPCRD4,	PortD4_Ctrl		},
	{ &GPCRD5,	PortD5_Ctrl		},
	{ &GPCRD6,	PortD6_Ctrl		},
	{ &GPCRD7,	PortD7_Ctrl		},
	
		

	{ &GPCRE0,	PortE0_Ctrl		},
	{ &GPCRE1,	PortE1_Ctrl		},
	{ &GPCRE2,	PortE2_Ctrl		},
	{ &GPCRE3,	PortE3_Ctrl		},
	{ &GPCRE4,	PortE4_Ctrl  	},	
	{ &GPCRE5,	PortE5_Ctrl		},
	{ &GPCRE6,	PortE6_Ctrl		},
	{ &GPCRE7,	PortE7_Ctrl		},	
	

	{ &GPCRF0,	PortF0_Ctrl		},
	{ &GPCRF1,	PortF1_Ctrl		},
	{ &GPCRF2,	PortF2_Ctrl		},
	{ &GPCRF3,	PortF3_Ctrl		},
	{ &GPCRF4,	PortF4_Ctrl		},
	{ &GPCRF5,	PortF5_Ctrl		},
	{ &GPCRF6,	PortF6_Ctrl		},
	{ &GPCRF7,	PortF7_Ctrl		},

	{ &GPCRG0,	PortG0_Ctrl		},
	{ &GPCRG1,	PortG1_Ctrl		},
	{ &GPCRG2,	PortG2_Ctrl		},
	{ &GPCRG3,	PortG3_Ctrl		},
	{ &GPCRG4,	PortG4_Ctrl		},
	{ &GPCRG5,	PortG5_Ctrl		},
	{ &GPCRG6,	PortG6_Ctrl		},
	{ &GPCRG7,	PortG7_Ctrl		},

	{ &GPCRH0,	PortH0_Ctrl		},
	{ &GPCRH1,	PortH1_Ctrl		},
	{ &GPCRH2,	PortH2_Ctrl		},
	{ &GPCRH3,	PortH3_Ctrl		},
	{ &GPCRH4,	PortH4_Ctrl		},
	{ &GPCRH5,	PortH5_Ctrl		},
	{ &GPCRH6,	PortH6_Ctrl		},

	{ &GPCRI0,	PortI0_Ctrl		},
	{ &GPCRI1,	PortI1_Ctrl		},
	{ &GPCRI2,	PortI2_Ctrl		},
	{ &GPCRI3,	PortI3_Ctrl		},
	{ &GPCRI4,	PortI4_Ctrl		},
	{ &GPCRI5,	PortI5_Ctrl		},
	{ &GPCRI6,	PortI6_Ctrl		},
	{ &GPCRI7,	PortI7_Ctrl		},

	{ &GPCRJ0,	PortJ0_Ctrl		},
	{ &GPCRJ1,	PortJ1_Ctrl		},
	{ &GPCRJ2,	PortJ2_Ctrl		},
	{ &GPCRJ3,	PortJ3_Ctrl		},
	{ &GPCRJ4,	PortJ4_Ctrl		},
	{ &GPCRJ5,	PortJ5_Ctrl		}

};

//-----------------------------------------------------------------------------
// The function of GPIO register init.
//-----------------------------------------------------------------------------
void Init_GPIO(void)
{
	BYTE index;
	index=0x00;
	while(index<(sizeof(asInitGPIOReg)/sizeof(sInitGPIOReg)))
	{
		*asInitGPIOReg[index].reg=asInitGPIOReg[index].value;
		index++;
	}
}


void TurnOnOffCamera(void)
{
	if(IS_MASK_SET(Device_Status_Lenovo,Camera_S_B))
	{
		//CAM_PWR_EN_ON();
	}
	else
	{
		//CAM_PWR_EN_OFF();
	}					
}


void TurnOnOffWlan(void)
{
	if(IS_MASK_SET(Device_Status_Lenovo,Wireless_S_B))
	{
		//WLAN_PWR_EN_ON();
	}
	else
	{
		//WLAN_PWR_EN_OFF();
	}
}

void TurnOnOffBT(void)
{
	if(OS_Type >= 12)
	{
		if(IS_MASK_SET(Device_Status_Lenovo,Bluetooth_S_B))
		{
			//BT_EN_ON();
		}
		else
		{
			//BT_EN_OFF();
		}
	}
	else
	{
		//BT_EN_OFF();
	}
}



//----------------------------------------------------------------------------
// Hook function of SCI high
//----------------------------------------------------------------------------
void Hook_SCION(void)
{
	CLEAR_MASK(PM1IC,PMIC_SCI);
}

//----------------------------------------------------------------------------
// Hook function of SCI low
//----------------------------------------------------------------------------
void Hook_SCIOFF(void)
{
	SET_MASK(PM1IC,PMIC_SCI);
}

//----------------------------------------------------------------------------
// Hook function of SMI high
//----------------------------------------------------------------------------
void Hook_SMION(void)
{
	SMI_ON();
}

//----------------------------------------------------------------------------
// Hook function of SMI low
//----------------------------------------------------------------------------
void Hook_SMIOFF(void)
{
	SMI_OFF();
}

//----------------------------------------------------------------------------
// Hook function of A20 high
//----------------------------------------------------------------------------
void Hook_A20ON(void)
{
 	//GATEA20_ON();
}

//----------------------------------------------------------------------------
// Hook function of A20 low
//----------------------------------------------------------------------------
void Hook_A20OFF(void)
{
	//GATEA20_OFF();
}

//----------------------------------------------------------------------------
// Hook function of keyboard reset low
//----------------------------------------------------------------------------
void Hook_KBRSTON(void)
{
	//KBRST_ON();
}

//----------------------------------------------------------------------------
// Hook function of keyboard reset high
//----------------------------------------------------------------------------
void Hook_KBRSTOFF(void)
{
	//KBRST_OFF();
}

//----------------------------------------------------------------------------
// Hook function of NUM LED ON
//----------------------------------------------------------------------------
void Hook_NUMLED_ON(void)
{
    //NUMLED_ON();
}

//----------------------------------------------------------------------------
// Hook function of NUM LED OFF
//----------------------------------------------------------------------------
void Hook_NUMLED_OFF(void)
{
    //NUMLED_OFF();
}

//----------------------------------------------------------------------------
// Hook function of CAP LED ON
//----------------------------------------------------------------------------
void Hook_CAPLED_ON(void)
{
    CAPLED_ON();
}

//----------------------------------------------------------------------------
// Hook function of CAP LED OFF
//----------------------------------------------------------------------------
void Hook_CAPLED_OFF(void)
{
    CAPLED_OFF();
}

//----------------------------------------------------------------------------
// Hook function of BACKLIGHT on off
//----------------------------------------------------------------------------
	    


void BackLight_ON(BYTE Blk_tye)
{
	CLEAR_MASK(Oem_GPU_EC_BLK,Blk_tye);
	if(0x00==Oem_GPU_EC_BLK)
	{
		Setup_Brightness(LCD_BRIGHTNESS);
		//BLK_EC_EN_ON();
	}
	

}

void BackLight_OFF(BYTE Blk_tye)
{
	SET_MASK(Oem_GPU_EC_BLK,Blk_tye);
	//if(Oem_GPU_EC_BLK)
	//{
		//BLK_EC_EN_OFF();
		//PWM_VADJ = 0x40;  //BrightnessTBL_PWM[12] 
		
	//}
}

     

