COREInclude=..\Code\CORE\INCLUDE\*.H
OEMInclude=..\Code\OEM\INCLUDE\*.H
CHIPInclude=..\Code\CHIP\INCLUDE\*.H
CDirectives=LA WL(1) CD OT(9, size) NOAREGS OR INCDIR(..\Code\CORE\INCLUDE\;..\Code\OEM\INCLUDE\;..\Code\CHIP\INCLUDE\)
CDirectives1=LA WL(1) CD OT(9, size) NOAREGS OR SRC INCDIR(..\Code\CORE\INCLUDE\;..\Code\OEM\INCLUDE\;..\Code\CHIP\INCLUDE\)
CDirectives2=LA WL(1) CD OT(8, size) NOAREGS OR INCDIR(..\Code\CORE\INCLUDE\;..\Code\OEM\INCLUDE\;..\Code\CHIP\INCLUDE\)
ADirectives=SET (LA) DEBUG EP 
CC=C51
AS=A51
Linker=BL51

filename=FIC628

ALL:$(filename).b0
#------------------------------------------------------------------
# Hex file to bin file
# Syntax : 
#	Hex2bin -s 0x0000 -e b0 $(filename).H00	# common + bank0 (0x0000 ~ 0xFFFF)
#	Hex2bin -s 0x8000 -e b1 $(filename).H01	# bank1 (0x10000 ~ 0x17FFF)
#	Hex2bin -s 0x8000 -e b2 $(filename).H02	# bank2 (0x18000 ~ 0x1FFFF)
#	Hex2bin -s 0x8000 -e b3 $(filename).H03	# bank3 (0x20000 ~ 0x27FFF)

#	OH51 $(filename).B00 HEXFILE($(filename).H00)	# common + bank0 (0x0000 ~ 0xFFFF)
#	OH51 $(filename).B01 HEXFILE($(filename).H01)	# bank1 (0x10000 ~ 0x17FFF)
#	OH51 $(filename).B02 HEXFILE($(filename).H02)	# bank2 (0x18000 ~ 0x1FFFF)
#	OH51 $(filename).B03 HEXFILE($(filename).H03)	# bank3 (0x20000 ~ 0x27FFF)
#=-----------------------------------------------------------------	
$(filename).b0:$(filename).H00
	Hex2bin -s 0x0000 -e b0 $(filename).H00
	Hex2bin -s 0x8000 -e b1 $(filename).H01
	Hex2bin -s 0x8000 -e b2 $(filename).H02
	Hex2bin -s 0x8000 -e b3 $(filename).H03

$(filename).H00:$(filename).B00
	OH51 $(filename).B00 HEXFILE($(filename).H00)
	OH51 $(filename).B01 HEXFILE($(filename).H01)
	OH51 $(filename).B02 HEXFILE($(filename).H02)
	OH51 $(filename).B03 HEXFILE($(filename).H03)

$(filename).B00:$(filename).ABS
	OC51 $(filename).ABS
#------------------------------------------------------------------
# Link all obj fils
#=-----------------------------------------------------------------
$(filename).ABS:KeilMisc\Obj\CORE_IRQ.OBJ\
			KeilMisc\Obj\CORE_BITADDR.OBJ\
			KeilMisc\Obj\CORE_ACPI.OBJ\
			KeilMisc\Obj\CORE_Memory.OBJ\
			KeilMisc\Obj\CORE_HOSTIF.OBJ\
			KeilMisc\Obj\CORE_MAIN.OBJ\
			KeilMisc\Obj\CORE_PORT6064.OBJ\
			KeilMisc\Obj\CORE_PS2.OBJ\
			KeilMisc\Obj\CORE_SCAN.OBJ\
			KeilMisc\Obj\CORE_SMBUS.OBJ\
			KeilMisc\Obj\CORE_TIMERS.OBJ\
			KeilMisc\Obj\CORE_XLT.OBJ\
			KeilMisc\Obj\CORE_FLASH.OBJ\
			KeilMisc\Obj\CORE_CHIPREGS.OBJ\
			KeilMisc\Obj\CORE_ITEString.OBJ\
			KeilMisc\Obj\CORE_INIT.OBJ\
			KeilMisc\Obj\CORE_ASM.OBJ\
			KeilMisc\Obj\CORE_GPIO.OBJ\
			KeilMisc\Obj\L51_BANK.OBJ\
			KeilMisc\Obj\STARTUP.OBJ\
			KeilMisc\Obj\OEM_GPIO.OBJ\
			KeilMisc\Obj\OEM_LED.OBJ\
			KeilMisc\Obj\OEM_MAIN.OBJ\
			KeilMisc\Obj\OEM_SCANTABS.OBJ\
			KeilMisc\Obj\OEM_FAN.OBJ\
			KeilMisc\Obj\OEM_BATTERY.OBJ\
			KeilMisc\Obj\OEM_EVENT.OBJ\
			KeilMisc\Obj\OEM_POWER.OBJ\
			KeilMisc\Obj\OEM_SMBUS.OBJ\
			KeilMisc\Obj\OEM_ADC.OBJ\
			KeilMisc\Obj\OEM_ACPI.OBJ\
			KeilMisc\Obj\OEM_FLASH.OBJ\
			KeilMisc\Obj\OEM_INIT.OBJ\
			KeilMisc\Obj\OEM_HOSTIF.OBJ\
			KeilMisc\Obj\OEM_6064.OBJ\
			KeilMisc\Obj\OEM_MEMORY.OBJ\
            KeilMisc\Obj\OEM_Ver.OBJ\
            KeilMisc\Obj\OEM_LCD.OBJ\
            KeilMisc\Obj\OEM_PORT686C.OBJ\
            KeilMisc\Obj\OEM_PM3.OBJ\
            KeilMisc\Obj\OEM_IRQ.OBJ\
            KeilMisc\Obj\OEM_PM2.OBJ\
            KeilMisc\Obj\OEM_PS2.OBJ\
            KeilMisc\Obj\OEM_SPI.OBJ\
            KeilMisc\Obj\OEM_LPC.OBJ\
            KeilMisc\Obj\OEM_TIMER.OBJ\
            KeilMisc\Obj\OEM_ASM.OBJ\
            KeilMisc\Obj\OEM_Debug.OBJ\
            KeilMisc\Obj\OEM_ECPDM.OBJ\
			KeilMisc\Obj\UCSI.OBJ\
            KeilMisc\Obj\ANX7447_LIB.OBJ\
            KeilMisc\Obj\OEM_UART.OBJ\
            KeilMisc\Obj\OEM_BANK1_Func.OBJ\
            KeilMisc\Obj\OEM_BANK2_Func.OBJ\
            KeilMisc\Obj\OEM_BANK3_Func.OBJ
	$(Linker) @$(filename).lin

#------------------------------------------------------------------
# Compile chip file
#=----------------------------------------------------------------- 
KeilMisc\Obj\CORE_CHIPREGS.OBJ:..\Code\CHIP\CORE_CHIPREGS.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CHIP\CORE_CHIPREGS.C $(CDirectives)
	move ..\Code\CHIP\CORE_CHIPREGS.OBJ KeilMisc\Obj
	move ..\Code\CHIP\CORE_CHIPREGS.LST KeilMisc\Lst

KeilMisc\Obj\CORE_ITEString.OBJ:..\Code\CHIP\CORE_ITEString.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CHIP\CORE_ITEString.C $(CDirectives)
	move ..\Code\CHIP\CORE_ITEString.OBJ KeilMisc\Obj
	move ..\Code\CHIP\CORE_ITEString.LST KeilMisc\Lst	
	
#------------------------------------------------------------------
# Compile core file
#=-----------------------------------------------------------------   
KeilMisc\Obj\CORE_IRQ.OBJ:..\Code\CORE\CORE_IRQ.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_IRQ.C $(CDirectives)
	move ..\Code\CORE\CORE_IRQ.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_IRQ.LST KeilMisc\Lst

KeilMisc\Obj\CORE_BITADDR.OBJ:..\Code\CORE\CORE_BITADDR.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_BITADDR.C $(CDirectives)
	move ..\Code\CORE\CORE_BITADDR.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_BITADDR.LST KeilMisc\Lst	

KeilMisc\Obj\CORE_ACPI.OBJ:..\Code\CORE\CORE_ACPI.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_ACPI.C $(CDirectives)
	move ..\Code\CORE\CORE_ACPI.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_ACPI.LST KeilMisc\Lst
	
KeilMisc\Obj\CORE_Memory.OBJ:..\Code\CORE\CORE_Memory.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_Memory.C $(CDirectives)	
	move ..\Code\CORE\CORE_Memory.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_Memory.LST KeilMisc\Lst

KeilMisc\Obj\CORE_HOSTIF.OBJ:..\Code\CORE\CORE_HOSTIF.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_HOSTIF.C $(CDirectives)
	move ..\Code\CORE\CORE_HOSTIF.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_HOSTIF.LST KeilMisc\Lst

KeilMisc\Obj\CORE_MAIN.OBJ:..\Code\CORE\CORE_MAIN.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_MAIN.C $(CDirectives)
	move ..\Code\CORE\CORE_MAIN.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_MAIN.LST KeilMisc\Lst

KeilMisc\Obj\CORE_PORT6064.OBJ:..\Code\CORE\CORE_PORT6064.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_PORT6064.C $(CDirectives)
	move ..\Code\CORE\CORE_PORT6064.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_PORT6064.LST KeilMisc\Lst

KeilMisc\Obj\CORE_PS2.OBJ:..\Code\CORE\CORE_PS2.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_PS2.C $(CDirectives)
	move ..\Code\CORE\CORE_PS2.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_PS2.LST KeilMisc\Lst

KeilMisc\Obj\CORE_SCAN.OBJ:..\Code\CORE\CORE_SCAN.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_SCAN.C $(CDirectives)
	move ..\Code\CORE\CORE_SCAN.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_SCAN.LST KeilMisc\Lst

KeilMisc\Obj\CORE_SMBUS.OBJ:..\Code\CORE\CORE_SMBUS.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_SMBUS.C $(CDirectives)
	move ..\Code\CORE\CORE_SMBUS.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_SMBUS.LST KeilMisc\Lst

KeilMisc\Obj\CORE_TIMERS.OBJ:..\Code\CORE\CORE_TIMERS.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_TIMERS.C $(CDirectives)
	move ..\Code\CORE\CORE_TIMERS.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_TIMERS.LST KeilMisc\Lst
	
KeilMisc\Obj\CORE_XLT.OBJ:..\Code\CORE\CORE_XLT.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_XLT.C $(CDirectives)
	move ..\Code\CORE\CORE_XLT.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_XLT.LST KeilMisc\Lst
	
KeilMisc\Obj\CORE_FLASH.OBJ:..\Code\CORE\CORE_FLASH.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_FLASH.C $(CDirectives2)
	move ..\Code\CORE\CORE_FLASH.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_FLASH.LST KeilMisc\Lst	

KeilMisc\Obj\CORE_INIT.OBJ:..\Code\CORE\CORE_INIT.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_INIT.C $(CDirectives)
	move ..\Code\CORE\CORE_INIT.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_INIT.LST KeilMisc\Lst

KeilMisc\Obj\CORE_ASM.OBJ:..\Code\CORE\CORE_ASM.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_ASM.C $(CDirectives1)
	$(AS) ..\Code\CORE\CORE_ASM.SRC $(ADirectives) 
	move ..\Code\CORE\CORE_ASM.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_ASM.LST KeilMisc\Lst	
	del ..\Code\CORE\CORE_ASM.SRC

KeilMisc\Obj\CORE_GPIO.OBJ:..\Code\CORE\CORE_GPIO.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\CORE\CORE_GPIO.C $(CDirectives)
	move ..\Code\CORE\CORE_GPIO.OBJ KeilMisc\Obj
	move ..\Code\CORE\CORE_GPIO.LST KeilMisc\Lst	

KeilMisc\Obj\L51_BANK.OBJ:..\Code\CORE\L51_BANK.A51 
	$(AS) ..\Code\CORE\L51_BANK.A51 $(ADirectives) 
	move ..\Code\CORE\L51_BANK.OBJ KeilMisc\Obj
	move ..\Code\CORE\L51_BANK.LST KeilMisc\Lst

KeilMisc\Obj\STARTUP.OBJ:..\Code\CORE\STARTUP.A51 
	$(AS) ..\Code\CORE\STARTUP.A51 $(ADirectives) 
	move ..\Code\CORE\STARTUP.OBJ KeilMisc\Obj
	move ..\Code\CORE\STARTUP.LST KeilMisc\Lst

#------------------------------------------------------------------
# Compile oem bank0 file
#=-----------------------------------------------------------------
KeilMisc\Obj\OEM_GPIO.OBJ:..\Code\OEM\OEM_GPIO.C $(COREInclude) $(OEMInclude) $(CHIPInclude) 
	$(CC) ..\Code\OEM\OEM_GPIO.C $(CDirectives)
	move ..\Code\OEM\OEM_GPIO.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_GPIO.LST KeilMisc\Lst

KeilMisc\Obj\OEM_LED.OBJ:..\Code\OEM\OEM_LED.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_LED.C $(CDirectives)
	move ..\Code\OEM\OEM_LED.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_LED.LST KeilMisc\Lst
	
KeilMisc\Obj\OEM_MAIN.OBJ:..\Code\OEM\OEM_MAIN.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_MAIN.C $(CDirectives)
	move ..\Code\OEM\OEM_MAIN.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_MAIN.LST KeilMisc\Lst
	
KeilMisc\Obj\OEM_SCANTABS.OBJ:..\Code\OEM\OEM_SCANTABS.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_SCANTABS.C $(CDirectives)	
	move ..\Code\OEM\OEM_SCANTABS.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_SCANTABS.LST KeilMisc\Lst

KeilMisc\Obj\OEM_FAN.OBJ:..\Code\OEM\OEM_FAN.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_FAN.C $(CDirectives)
	move ..\Code\OEM\OEM_FAN.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_FAN.LST KeilMisc\Lst
	
KeilMisc\Obj\OEM_BATTERY.OBJ:..\Code\OEM\OEM_BATTERY.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_BATTERY.C $(CDirectives)
	move ..\Code\OEM\OEM_BATTERY.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_BATTERY.LST KeilMisc\Lst

KeilMisc\Obj\OEM_EVENT.OBJ:..\Code\OEM\OEM_EVENT.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_EVENT.C $(CDirectives)
	move ..\Code\OEM\OEM_EVENT.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_EVENT.LST KeilMisc\Lst

KeilMisc\Obj\OEM_POWER.OBJ:..\Code\OEM\OEM_POWER.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_POWER.C $(CDirectives)
	move ..\Code\OEM\OEM_POWER.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_POWER.LST KeilMisc\Lst

KeilMisc\Obj\OEM_SMBUS.OBJ:..\Code\OEM\OEM_SMBUS.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_SMBUS.C $(CDirectives)
	move ..\Code\OEM\OEM_SMBUS.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_SMBUS.LST KeilMisc\Lst

KeilMisc\Obj\OEM_ADC.OBJ:..\Code\OEM\OEM_ADC.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_ADC.C $(CDirectives)
	move ..\Code\OEM\OEM_ADC.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_ADC.LST KeilMisc\Lst

KeilMisc\Obj\OEM_ACPI.OBJ:..\Code\OEM\OEM_ACPI.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_ACPI.C $(CDirectives)
	move ..\Code\OEM\OEM_ACPI.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_ACPI.LST KeilMisc\Lst	


KeilMisc\Obj\OEM_FLASH.OBJ:..\Code\OEM\OEM_FLASH.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\OEM\OEM_FLASH.C $(CDirectives2)
	move ..\Code\OEM\OEM_FLASH.OBJ KeilMisc\Obj
	move ..\Code\OEM\OEM_FLASH.LST KeilMisc\Lst		

KeilMisc\Obj\OEM_INIT.OBJ:..\Code\Oem\OEM_INIT.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_INIT.C $(CDirectives)
	move ..\Code\Oem\OEM_INIT.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_INIT.LST KeilMisc\Lst

KeilMisc\Obj\OEM_HOSTIF.OBJ:..\Code\Oem\OEM_HOSTIF.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_HOSTIF.C $(CDirectives)
	move ..\Code\Oem\OEM_HOSTIF.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_HOSTIF.LST KeilMisc\Lst

KeilMisc\Obj\OEM_6064.OBJ:..\Code\Oem\OEM_6064.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_6064.C $(CDirectives)
	move ..\Code\Oem\OEM_6064.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_6064.LST KeilMisc\Lst

KeilMisc\Obj\OEM_MEMORY.OBJ:..\Code\Oem\OEM_MEMORY.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_MEMORY.C $(CDirectives)
	move ..\Code\Oem\OEM_MEMORY.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_MEMORY.LST KeilMisc\Lst

KeilMisc\Obj\OEM_Ver.OBJ:..\Code\Oem\OEM_Ver.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_Ver.C $(CDirectives)
	move ..\Code\Oem\OEM_Ver.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_Ver.LST KeilMisc\Lst

KeilMisc\Obj\OEM_LCD.OBJ:..\Code\Oem\OEM_LCD.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_LCD.C $(CDirectives)
	move ..\Code\Oem\OEM_LCD.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_LCD.LST KeilMisc\Lst

KeilMisc\Obj\OEM_PORT686C.OBJ:..\Code\Oem\OEM_PORT686C.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_PORT686C.C $(CDirectives)
	move ..\Code\Oem\OEM_PORT686C.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_PORT686C.LST KeilMisc\Lst	

KeilMisc\Obj\OEM_PM3.OBJ:..\Code\Oem\OEM_PM3.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_PM3.C $(CDirectives)
	move ..\Code\Oem\OEM_PM3.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_PM3.LST KeilMisc\Lst

KeilMisc\Obj\OEM_IRQ.OBJ:..\Code\Oem\OEM_IRQ.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_IRQ.C $(CDirectives)
	move ..\Code\Oem\OEM_IRQ.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_IRQ.LST KeilMisc\Lst

KeilMisc\Obj\OEM_PM2.OBJ:..\Code\Oem\OEM_PM2.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_PM2.C $(CDirectives)
	move ..\Code\Oem\OEM_PM2.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_PM2.LST KeilMisc\Lst

KeilMisc\Obj\OEM_PS2.OBJ:..\Code\Oem\OEM_PS2.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_PS2.C $(CDirectives)
	move ..\Code\Oem\OEM_PS2.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_PS2.LST KeilMisc\Lst

KeilMisc\Obj\OEM_SPI.OBJ:..\Code\Oem\OEM_SPI.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_SPI.C $(CDirectives)
	move ..\Code\Oem\OEM_SPI.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_SPI.LST KeilMisc\Lst

KeilMisc\Obj\OEM_LPC.OBJ:..\Code\Oem\OEM_LPC.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_LPC.C $(CDirectives)
	move ..\Code\Oem\OEM_LPC.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_LPC.LST KeilMisc\Lst

KeilMisc\Obj\OEM_TIMER.OBJ:..\Code\Oem\OEM_TIMER.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_TIMER.C $(CDirectives)
	move ..\Code\Oem\OEM_TIMER.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_TIMER.LST KeilMisc\Lst

KeilMisc\Obj\OEM_ASM.OBJ:..\Code\Oem\OEM_ASM.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_ASM.C $(CDirectives1)
	$(AS) ..\Code\Oem\OEM_ASM.SRC $(ADirectives) 
	move ..\Code\Oem\OEM_ASM.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_ASM.LST KeilMisc\Lst
	del ..\Code\Oem\OEM_ASM.SRC

KeilMisc\Obj\OEM_Debug.OBJ:..\Code\Oem\OEM_Debug.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_Debug.C $(CDirectives)
	move ..\Code\Oem\OEM_Debug.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_Debug.LST KeilMisc\Lst		
	
KeilMisc\Obj\OEM_ECPDM.OBJ:..\Code\Oem\OEM_ECPDM.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_ECPDM.C $(CDirectives)
	move ..\Code\Oem\OEM_ECPDM.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_ECPDM.LST KeilMisc\Lst	

KeilMisc\Obj\UCSI.OBJ:..\Code\Oem\UCSI.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\UCSI.C $(CDirectives)
	move ..\Code\Oem\UCSI.OBJ KeilMisc\Obj
	move ..\Code\Oem\UCSI.LST KeilMisc\Lst

KeilMisc\Obj\ANX7447_LIB.OBJ:..\Code\Oem\ANX7447_LIB.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\ANX7447_LIB.C $(CDirectives)
	move ..\Code\Oem\ANX7447_LIB.OBJ KeilMisc\Obj
	move ..\Code\Oem\ANX7447_LIB.LST KeilMisc\Lst
	
KeilMisc\Obj\OEM_UART.OBJ:..\Code\Oem\OEM_UART.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_UART.C $(CDirectives)
	move ..\Code\Oem\OEM_UART.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_UART.LST KeilMisc\Lst
#------------------------------------------------------------------
# Compile oem bank1 file
#=-----------------------------------------------------------------
KeilMisc\Obj\OEM_BANK1_Func.OBJ:..\Code\Oem\OEM_BANK1_Func.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_BANK1_Func.C $(CDirectives)
	move ..\Code\Oem\OEM_BANK1_Func.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_BANK1_Func.LST KeilMisc\Lst
#------------------------------------------------------------------
# Compile oem bank2 file
#=-----------------------------------------------------------------
KeilMisc\Obj\OEM_BANK2_Func.OBJ:..\Code\Oem\OEM_BANK2_Func.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_BANK2_Func.C $(CDirectives)
	move ..\Code\Oem\OEM_BANK2_Func.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_BANK2_Func.LST KeilMisc\Lst

#------------------------------------------------------------------
# Compile oem bank2 file
#=-----------------------------------------------------------------
KeilMisc\Obj\OEM_BANK3_Func.OBJ:..\Code\Oem\OEM_BANK3_Func.C $(COREInclude) $(OEMInclude) $(CHIPInclude)
	$(CC) ..\Code\Oem\OEM_BANK3_Func.C $(CDirectives)
	move ..\Code\Oem\OEM_BANK3_Func.OBJ KeilMisc\Obj
	move ..\Code\Oem\OEM_BANK3_Func.LST KeilMisc\Lst	