@echo off

set filename=FIC628


IF  "%1" == ""     GOTO MAKE
IF  "%1" == "?"    GOTO MAKE
IF  "%1" == "/?"   GOTO MAKE

IF  "%1" == "clear"   GOTO CLEAR
IF  "%1" == "CLEAR"   GOTO CLEAR

GOTO done

:MAKE
build.bat 13CRIX %filename%
GOTO done

:CLEAR
build.bat  clear
cls
ECHO    ********************************************************************
ECHO    *    IMAGE+ Embedded Controller Firmware Build Process             *
ECHO    *   Copyright (c) 2020-2025, IMAGE+ Tech. Inc. All Rights Reserved.*
ECHO    ********************************************************************
ECHO.   
GOTO done


:done
@echo on