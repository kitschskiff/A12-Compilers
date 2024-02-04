/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: Damir Rimad 041067785
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <stdlib.h> /* malloc is included here */
//#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity, can't resize past this capacity */

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TODO: BIT 3: END = End of buffer flag */
#define READER_END   0x08
/* TODO: BIT 2: REL = Rellocation memory flag */
#define READER_REL      0x04
/* TODO: BIT 1: EMP = Buffer empty flag */
#define READER_EMP        0x02
/* TODO: BIT 0: FUL = Buffer full flag */
#define READER_FUL         0x01     // indicates that reader is full (wrte of position is equal to size of bufferReader)

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	mexico_int mark;			/* the offset to the mark position (in chars) */
    mexico_int read;			/* the offset to the get a char position (in chars) */
    mexico_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	mexico_string	content;			/* pointer to the beginning of character array (character buffer) */
    mexico_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
    mexico_int		increment;			/* character array increment factor */
    mexico_int		mode;				/* operational mode indicator */
	mexico_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
    mexico_int		histogram[NCHAR];	/* Statistics of chars */
    mexico_int		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(mexico_int, mexico_int, mexico_int);
BufferPointer	readerAddChar		(BufferPointer const, mexico_char);
mexico_bool		readerClear		    (BufferPointer const);
mexico_bool		readerFree		    (BufferPointer const);
mexico_bool		readerIsFull		(BufferPointer const);
mexico_bool		readerIsEmpty		(BufferPointer const);
mexico_bool		readerSetMark		(BufferPointer const, mexico_int);
mexico_int		readerPrint		    (BufferPointer const);
mexico_int		readerLoad			(BufferPointer const, FILE* const);
mexico_bool		readerRecover		(BufferPointer const);
mexico_bool		readerRetract		(BufferPointer const);
mexico_bool		readerRestore		(BufferPointer const);
/* Getters */
mexico_char		readerGetChar		(BufferPointer const);
mexico_string	readerGetContent	(BufferPointer const, mexico_int);
mexico_int		readerGetPosRead	(BufferPointer const);
mexico_int		readerGetPosWrte	(BufferPointer const);
mexico_int		readerGetPosMark	(BufferPointer const);
mexico_int		readerGetSize		(BufferPointer const);
mexico_int		readerGetInc		(BufferPointer const);
mexico_int		readerGetMode		(BufferPointer const);
mexico_byte		readerGetFlags		(BufferPointer const);
mexico_void		readerPrintStat		(BufferPointer const);
mexico_int		readerNumErrors		(BufferPointer const);

#endif
