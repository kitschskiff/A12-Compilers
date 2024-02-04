:: ---------------------------------------------------------------------
:: COMPILERS COURSE - SCRIPT                                           -
:: SCRIPT A12 - CST8152 - Fall 2023                                    -
:: ---------------------------------------------------------------------

CLS
SET COMPILER=Compiler.exe

SET FILE1=INPUT0_Empty
SET FILE2=INPUT1_Hello
SET FILE3=INPUT2_Volume
SET FILE4=INPUT3_Factorial
SET FILE5=INPUT4_Datatypes
SET FILE6=INPUT5_General
SET FILE7=INPUT6_Big

SET ASSIGNMENT=A12
SET EXTENSION=mx
SET OUTPUT=out
SET ERROR=err

SET PARAM=r

:: ---------------------------------------------------------------------
:: Begin of Tests (A12 - F23) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "=---------------------------------------="
ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F23)  |"
ECHO "=---------------------------------------="
ECHO "                                   "
ECHO "[READER SCRIPT .........................]"
ECHO "                                   "

if not exist output\ md output

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A12 - F23) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> output/%FILE1%-%ASSIGNMENT%.%OUTPUT%	2> output/%FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> output/%FILE2%-%ASSIGNMENT%.%OUTPUT%	2> output/%FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> output/%FILE3%-%ASSIGNMENT%.%OUTPUT%	2> output/%FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> output/%FILE4%-%ASSIGNMENT%.%OUTPUT%	2> output/%FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> output/%FILE5%-%ASSIGNMENT%.%OUTPUT%	2> output/%FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> output/%FILE6%-%ASSIGNMENT%.%OUTPUT%	2> output/%FILE6%-%ASSIGNMENT%.%ERROR%

::
:: ADVANCED TESTS  -------------------------------------------------------
::
:: Advanced Tests (A12 - F23) - - - - - - - - -- - - - - - - - - - - -

%COMPILER% %PARAM% %FILE7%.%EXTENSION%	f 100 10	> output/%FILE7%-%ASSIGNMENT%-f-100-10.%OUTPUT%	2> output/%FILE7%-%ASSIGNMENT%-f-100-10.%ERROR%
%COMPILER% %PARAM% %FILE7%.%EXTENSION%	a 100 10	> output/%FILE7%-%ASSIGNMENT%-a-100-10.%OUTPUT%	2> output/%FILE7%-%ASSIGNMENT%-a-100-10.%ERROR%
%COMPILER% %PARAM% %FILE7%.%EXTENSION%	m 100 10	> output/%FILE7%-%ASSIGNMENT%-m-100-10.%OUTPUT%	2> output/%FILE7%-%ASSIGNMENT%-m-100-10.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
type output\*.OUT
type output\*.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A12 - F23) --------------------------------------------
:: ---------------------------------------------------------------------
