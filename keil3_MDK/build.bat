@echo off

	path=..\Tools;..\Tools\NMake;


set buildfile=%1
set EC_ROM_SIZE=128

if not exist bin mkdir bin
if not exist KeilMisc mkdir KeilMisc

if not exist .\KeilMisc\Lst mkdir .\KeilMisc\Lst
if not exist .\KeilMisc\Obj mkdir .\KeilMisc\Obj
if not exist .\KeilMisc\Map mkdir .\KeilMisc\Map







IF  "%1" == "clear"   GOTO clear
IF  "%1" == "CLEAR"   GOTO clear


copy .\KeilMisc\Lst\*.m51 .\KeilMisc\Map\
copy .\KeilMisc\Obj\%buildfile%.B00
copy .\KeilMisc\Obj\%buildfile%.B01
copy .\KeilMisc\Obj\%buildfile%.B02
copy .\KeilMisc\Obj\%buildfile%.B03


NMAKE %buildfile%.mak



::-----------------------------------------------------------
:: Common + Bank0 + Bank1 + Bank2 + Bank3 [160KB]
::-----------------------------------------------------------
REM *** The FU instruction is to fill the ITEEc.b0 file with FF to a size of 64KB    young
FU /SIZE 64 %buildfile%.b0 BANK0.BIN FF
FU /SIZE 32 %buildfile%.b1 BANK1.BIN FF
FU /SIZE 32 %buildfile%.b2 BANK2.BIN FF
FU /SIZE 32 %buildfile%.b3 BANK3.BIN FF

COPY /b BANK0.BIN+BANK1.BIN+BANK2.BIN+BANK3.BIN %buildfile%.ALL

FU /SIZE %EC_ROM_SIZE% %buildfile%.ALL %buildfile%.BIN FF



copy .\%buildfile%.BIN .\bin
ren .\bin\%buildfile%.BIN %buildfile%.fd

copy .\%buildfile%.BIN .\bin




DEL *.BIN
DEL *.ALL
DEL *.b0 *.b1 *.b2 *.b3
DEL *.H0*
DEL *.B0*




cls
ECHO 
ECHO    ********************************************************************
ECHO    *    IMAGE Embedded Controller Firmware Build Process              *
ECHO    *    Copyright (c) 2020-2025, IMAGE Tech. Inc. All Rights Reserved.*
ECHO    ********************************************************************
ECHO.  
ECHO    Making EC bin file successfully !!!
GOTO done




REM ***********************************************************************************************************
REM	To clear obj, lst, and bin files.
REM ***********************************************************************************************************
:clear
del /q .\KeilMisc\Obj\*.*
del /q .\KeilMisc\Lst\*.*
del /q .\KeilMisc\Map\*.*
del /q .\bin\*.*
GOTO done



::-----------------------------------------------------------
:: Done
::-----------------------------------------------------------
:done
@echo on
