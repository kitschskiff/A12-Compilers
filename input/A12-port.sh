#!/bin/bash
# ---------------------------------------------------------------------
# COMPILERS COURSE - SCRIPT                                           -
# SCRIPT A12 - CST8152 - Fall 2023                                    -
# ---------------------------------------------------------------------

clear
COMPILER=./Compiler

FILE1=INPUT0_Empty
FILE2=INPUT1_Hello
FILE3=INPUT2_Volume
FILE4=INPUT3_Factorial
FILE5=INPUT4_Datatypes
FILE6=INPUT5_General
FILE7=INPUT6_Big

ASSIGNMENT=A12
EXTENSION=sof
OUTPUT=out
ERROR=err

PARAM=r

# ---------------------------------------------------------------------
# Begin of Tests (A12 - F23) ------------------------------------------
# ---------------------------------------------------------------------

echo "=---------------------------------------="
echo "|  COMPILERS - ALGONQUIN COLLEGE (F23)  |"
echo "=---------------------------------------="
echo "|              ....                     |"
echo "|          ........#.###.           |"
echo "|        .:........#.:^^^~~~:          |"
echo "|        :^^###^^^#^!7??7~^.        |"
echo "|       .:^~~^!77777~~7?YY?7??7^.       |"
echo "|       :.^~!??!^::::^^~!?5PY??!~.      |"
echo "|       ~!!7J~.:::^^^^~!!~~?G5J?~       |"
echo "|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |"
echo "|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |"
echo "|       .~77..    . .~^:^^^~7?:         |"
echo "|       .^!^~:::.:^!7?~^~!77J:          |"
echo "|        ^^!Y~^^^^~?YJ77??7JJ^          |"
echo "|       .^7J?~^~~^~7??7??7JY?~:         |"
echo "|        ::^^~^7?!^~~!7???J?J7~:.       |"
echo "|         ^~~!.^7YPPPP5Y?7J7777~.       |"
echo "|        ..:~..:^!JPP5YJ?!777!^.        |"
echo "| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |"
echo "|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |"
echo "|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |"
echo "|    :~75 \__ \/ _ \  _| / _\` | 5?.     |"
echo "|     7~7 |___/\___/_| |_\__,_| Y5?.    |"
echo "|    .^~!~.....................P5YY7.   |"
echo "|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |"
echo "|                                       |"
echo "=---------------------------------------="
echo "                                   "
echo "[READER SCRIPT .........................]"
echo ""

mv *.exe $COMPILER

#
# BASIC TESTS  ----------------------------------------------------------
#
# Basic Tests (A12 - F23) - - - - - - - - - - - - - - - - - - - - - -

mkdir output

$COMPILER $PARAM $FILE1.$EXTENSION	> output/$FILE1-$ASSIGNMENT.$OUTPUT	2> output/$FILE1-$ASSIGNMENT.$ERROR
$COMPILER $PARAM $FILE2.$EXTENSION	> output/$FILE2-$ASSIGNMENT.$OUTPUT	2> output/$FILE2-$ASSIGNMENT.$ERROR
$COMPILER $PARAM $FILE3.$EXTENSION	> output/$FILE3-$ASSIGNMENT.$OUTPUT	2> output/$FILE3-$ASSIGNMENT.$ERROR
$COMPILER $PARAM $FILE4.$EXTENSION	> output/$FILE4-$ASSIGNMENT.$OUTPUT	2> output/$FILE4-$ASSIGNMENT.$ERROR
$COMPILER $PARAM $FILE5.$EXTENSION	> output/$FILE5-$ASSIGNMENT.$OUTPUT	2> output/$FILE5-$ASSIGNMENT.$ERROR
$COMPILER $PARAM $FILE6.$EXTENSION	> output/$FILE6-$ASSIGNMENT.$OUTPUT	2> output/$FILE6-$ASSIGNMENT.$ERROR

#
# ADVANCED TESTS  -------------------------------------------------------
#
# Advanced Tests (A12 - F23) - - - - - - - - -- - - - - - - - - - - -

$COMPILER $PARAM $FILE7.$EXTENSION	f 100 10	> output/$FILE7-$ASSIGNMENT-f-100-10.$OUTPUT	2> output/$FILE7-$ASSIGNMENT-f-100-10.$ERROR
$COMPILER $PARAM $FILE7.$EXTENSION	a 100 10	> output/$FILE7-$ASSIGNMENT-a-100-10.$OUTPUT	2> output/$FILE7-$ASSIGNMENT-a-100-10.$ERROR
$COMPILER $PARAM $FILE7.$EXTENSION	m 100 10	> output/$FILE7-$ASSIGNMENT-m-100-10.$OUTPUT	2> output/$FILE7-$ASSIGNMENT-m-100-10.$ERROR

# SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -

cat output/*.out
cat output/*.err

# ---------------------------------------------------------------------
# End of Tests (A12 - F23) --------------------------------------------
# ---------------------------------------------------------------------
