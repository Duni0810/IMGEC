@echo off

REM ***********************************************************************************************************
REM	Setting
REM ***********************************************************************************************************
REM -----------------------------------------------------------------------------------------------------------
REM (64, 96, 128, and 160 are valid)
	SET EC_ROM_SIZE=128

REM 	path=C:\Keil\C51\BIN;.\Tools;.\Tools\NMake;
REM 	path=C:\keil3\C51\BIN;.\Tools;.\Tools\NMake;
		path=C:\Keil_v5\C51\BIN;.\..\Tools;.\..\Tools\NMake;
REM -----------------------------------------------------------------------------------------------------------
set filename=%2
set buildfile=IMGEC
set workspace=cmd_MDK
REM ***********************************************************************************************************
REM	Parameter
REM ***********************************************************************************************************
REM -----------------------------------------------------------------------------------------------------------

if not exist bin mkdir bin
if not exist KeilMisc mkdir KeilMisc

if not exist .\KeilMisc\Lst mkdir .\KeilMisc\Lst
if not exist .\KeilMisc\Obj mkdir .\KeilMisc\Obj
if not exist .\KeilMisc\Map mkdir .\KeilMisc\Map






IF  "%1" == ""     GOTO OPTIONS
IF  "%1" == "?"    GOTO OPTIONS
IF  "%1" == "/?"   GOTO OPTIONS

IF  "%1" == "clear"   GOTO clear
IF  "%1" == "CLEAR"   GOTO clear

IF  "%3" == ""	   GOTO BUILD
IF  "%3" == "all"  GOTO BUILDALL
IF  "%3" == "ALL"  GOTO BUILDALL
GOTO OPTIONS
REM -----------------------------------------------------------------------------------------------------------

REM ***********************************************************************************************************
REM	Clean build
REM ***********************************************************************************************************
:BUILDALL
del /q .\KeilMisc\Obj\*.*

REM ***********************************************************************************************************
REM	make file
REM ***********************************************************************************************************
:BUILD
cd ..\Code
cd OEM
if not exist %1 goto NotExit
mkdir INCLUDE
copy .\%1\OEM_BANK0\*.c
copy .\%1\OEM_BANK1\*.c
copy .\%1\OEM_BANK2\*.c
copy .\%1\OEM_BANK3\*.c
cd INCLUDE
copy ..\%1\INCLUDE\*.h
cd..
cd..
cd..

cd Code
cd CORE
copy .\CORE_BANK0\*.c
copy .\CORE_COMMON\*.c
copy .\CORE_COMMON\*.a51
cd..
cd..

cd %workspace%
cls


REM ***********************************************************************************************************
REM	Building
REM ***********************************************************************************************************
NMAKE %buildfile%.mak





if errorlevel 2 goto errorend

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

::-----------------------------------------------------------
:: OK
::-----------------------------------------------------------
copy %buildfile%.bin .\bin\%filename%.bin



::-----------------------------------------------------------
:: young test
::-----------------------------------------------------------
REM DEL /q  .\bin\%filename%.bb0
REM DEL /q  .\bin\%filename%.BBIN

REM copy ITEEC.b0 .\bin\%filename%.bb0
REM copy BANK0.BIN .\bin\%filename%.BBIN
::-----------------------------------------------------------
:: young test
::-----------------------------------------------------------



move %buildfile%.ALL .\bin
DEL /q *.BIN*
DEL /q *.H*
DEL /q *.b0*
DEL /q *.b1
DEL /q *.b2
DEL /q *.b3
DEL /q *.ABS*
move *.m51 .\KeilMisc\Map
cls
ECHO    ********************************************************************
ECHO    *    ITE Embedded Controller Firmware Build Process                *
ECHO    *    Copyright (c) 2006-2010, ITE Tech. Inc. All Rights Reserved.  *
ECHO    ********************************************************************
ECHO.  
ECHO    Making EC bin file successfully !!!


cd ..
cd Code
cd OEM
del *.c
rd /S /Q INCLUDE
cd..
cd..

cd Code
cd CORE
del *.c
del *.a51
REM del *.src
cd..
cd..
cd %workspace%

GOTO done

REM GOTO End


:NotExit
cls
ECHO    ********************************************************************
ECHO    *    ITE Embedded Controller Firmware Build Process                *
ECHO    *    Copyright (c) 2006-2010, ITE Tech. Inc. All Rights Reserved.  *
ECHO    ********************************************************************
ECHO.  
ECHO    Project folder isn't exit.
cd ..
cd ..
cd %workspace%
GOTO done


:OPTIONS
cls
ECHO    ********************************************************************
ECHO    *    ITE Embedded Controller Firmware Build Process                *
ECHO    *    Copyright (c) 2006-2010, ITE Tech. Inc. All Rights Reserved.  *
ECHO    ********************************************************************
ECHO.    
ECHO    USAGE:  build [P1] [P2]
ECHO                  P1 = The project name of OEM folder. or [clear]
ECHO                  P2 = [all] [ALL] []
ECHO.
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
:: Fail
::-----------------------------------------------------------
:errorend
cd ..\Code
cd OEM
del *.lst
del *.obj
cd..
cd..

cd Code
cd CORE
del *.lst
del *.obj
cd..
cd..
cd %workspace%
GOTO done

REM :End
REM cd ..
REM cd Code
REM cd OEM
REM del *.c
REM rd /S /Q INCLUDE
REM cd..
REM cd..

REM cd Code
REM cd CORE
REM del *.c
REM del *.a51
REM del *.src
REM cd..
REM cd..
REM cd %workspace%

::-----------------------------------------------------------
:: Done
::-----------------------------------------------------------
:done

@echo on