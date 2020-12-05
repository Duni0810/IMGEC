
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












