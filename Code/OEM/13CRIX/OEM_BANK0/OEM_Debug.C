/*-----------------------------------------------------------------------------
 * TITLE: OEM_Debug.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/*------------------;
 ;EC2I READ			;
 ;------------------*/	
BYTE ReadSioInterface(BYTE Ldnumber, BYTE offset)
{
	#if EC_MODE
	BYTE rval;

	SET_MASK(LSIOHA,LKCFG);
  	SET_MASK(IBMAE,CFGAE);
  	SET_MASK(IBCTL,CSAE);

    IHIOA=0;              // Set indirect Host I/O Address
    IHD=0x07;
    while(IS_MASK_SET(IBCTL,CWIB));
  
    IHIOA=1;              // Set indirect Host I/O Address
    IHD=Ldnumber;
    while(IS_MASK_SET(IBCTL,CWIB)); 

    IHIOA=0;              // Set indirect Host I/O Address
    IHD=offset;
    while(IS_MASK_SET(IBCTL,CWIB));    

    IHIOA=1;              // Set indirect Host I/O Address
    SET_MASK(IBCTL, CRIB);    
	while(IS_MASK_SET(IBCTL, CRIB));
	
	rval = IHD;

 	CLEAR_MASK(LSIOHA,LKCFG);
  	CLEAR_MASK(IBMAE,CFGAE);
  	CLEAR_MASK(IBCTL,CSAE);

	return rval;
	#else 

	BYTE rval;

	// 写操作
	SET_MASK(LSIOHA,LKCFG);
  	SET_MASK(IBMAE,CFGAE);
  	SET_MASK(IBCTL,CSAE);

    IHIOA=0x07;              // Set indirect Host I/O Address
    IHD=Ldnumber;
    while(IS_MASK_SET(IBCTL,CWIB));

 	CLEAR_MASK(LSIOHA,LKCFG);
  	CLEAR_MASK(IBMAE,CFGAE);
  	CLEAR_MASK(IBCTL,CSAE);


	// 读操作
	SET_MASK(LSIOHA,LKCFG);
  	SET_MASK(IBMAE,CFGAE);
  	//SET_MASK(IBCTL,CSAE);

    IHIOA=offset;              // Set indirect Host I/O Address
    SET_MASK(IBCTL, CRIB | CSAE);    
	while(IS_MASK_SET(IBCTL, CRIB));
	
	rval = IHD;

 	CLEAR_MASK(LSIOHA,LKCFG);
  	CLEAR_MASK(IBMAE,CFGAE);
  	CLEAR_MASK(IBCTL,CSAE);

	return rval;
	#endif
}


BYTE Get_P80_CurrentIndex(void)
{
	BYTE index;
	index =	ReadSioInterface(0x10,0xF5);
	return index;
}

//------------------------------------------------------------
// RAM Debug function
// 1. You can Set the macro RAM_Debug to TRUE to enable RAM debug
// 2. You can print a Byte data to EC RAM for debug use this function
//------------------------------------------------------------
void RamDebug(unsigned char dbgcode)
{
#if RAM_Debug
  	PORT_BYTE_PNTR ClearIndex;
 	PORT_BYTE_PNTR byte_register_pntr;
    XBYTE index;
  	XBYTE i;
	
    byte_register_pntr = DebugRamAddr+DebugRamRange;
    index = *byte_register_pntr;
    *byte_register_pntr +=1;
	
    if ( *byte_register_pntr == DebugRamRange )
   	{
   		*byte_register_pntr = 0;
       	ClearIndex= DebugRamAddr;

		//for (i=0x00;i<DebugRamRange;i++)
     	//{
        // 	*ClearIndex=0x00;
        //  	ClearIndex++;
     	//}
  	}

	byte_register_pntr = DebugRamAddr + index;
    *byte_register_pntr = dbgcode;
#endif
}


//----------------------------------------------------------------------------
// The function of copy Bram bank 0x2200 to ram 0x0a00
// 
//----------------------------------------------------------------------------
void Copy_BRAM_SRAM(void)
{
	PORT_BYTE_PNTR Bram_Source_pntr;
	PORT_BYTE_PNTR Sram_destination_pntr,Sram_temp_pntr;

	Sram_temp_pntr = 0x0AFF;
    Bram_Source_pntr = 0x2200;
	Sram_destination_pntr = BRAM_RAM_Addr;
    while(Bram_Source_pntr <= 0x22FF)
    {
        *Sram_destination_pntr = *Bram_Source_pntr;
        Sram_destination_pntr++;
		Bram_Source_pntr++;
    }
	
	*Sram_temp_pntr = Get_P80_CurrentIndex();


}

//----------------------------------------------------------------------------
//(0x2210~0x0x224F)
//----------------------------------------------------------------------------
void BRAMDebug(unsigned char dbgcode)
{
	PORT_BYTE_PNTR Bram_pntr;
	XBYTE index;
	
	Bram_pntr = DebugBRamAddr+DebugBRamRange;
	index = *Bram_pntr;
	
	*Bram_pntr +=1;	
	
    if(*Bram_pntr == DebugBRamRange)
    {
    	
 		*Bram_pntr = 0;
		
    }

	Bram_pntr = DebugBRamAddr + index;		
	*Bram_pntr = dbgcode ;	

}


//----------------------------------------------------------------------------
// The function of clearing battery ram for oem debug
//----------------------------------------------------------------------------
void ClearBRam(void)
{
	PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr=0x2210;
    while(byte_register_pntr<=0x223F) // Clear battery ram (0x2200~0x22FF)   
    {
        *byte_register_pntr=0;
        byte_register_pntr ++;
    }							

}


