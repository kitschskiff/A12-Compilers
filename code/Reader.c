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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

BufferPointer readerCreate(mexico_int size, mexico_int increment, mexico_int mode) {
    BufferPointer readerPointer;
    /* TODO: Defensive programming */
    /* TODO: Adjust the values according to parameters */
    // initialize in memory
    readerPointer = (BufferPointer) calloc(1, sizeof(Buffer));
    if (!readerPointer)     // if allocation fails.
        goto clean;
    readerPointer->content = (mexico_string) malloc(size);
    if (!readerPointer->content) {// malloc fail check
        // free memory
        goto clean;
    }
	/* TODO: Defensive programming */
	/* TODO: Initialize the histogram */
    // assigning parameters
    if(size>0)      // assign size argument
        readerPointer->size = size;
    else            // zero or less argument, assign default size
	    readerPointer->size = READER_DEFAULT_SIZE;
    if(increment>=0) {
        readerPointer->increment = increment;
        // check if mode is valid
        if(mode != MODE_ADDIT | mode != MODE_MULTI) {   // mode should not be fixed when provided increment
            goto clean;
        }
        readerPointer->mode = mode;
    } else         // if increment is not provided, mode is always fixed.
        readerPointer->mode = MODE_FIXED;

    // flags
    readerPointer->flags = READER_DEFAULT_FLAG;    // default flag

	/* TODO: Initialize flags */
	/* TODO: The created flag must be signalized as EMP */
	/* NEW: Cleaning the content */
	if (readerPointer->content)
		readerPointer->content[0] = READER_TERMINATOR;
	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return readerPointer;

    //-------------------------------

    clean: // cleanup on fail-case
    if(readerPointer)
        free(readerPointer->content);
    if(readerPointer)
        free(readerPointer);

    return NULL;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, mexico_char ch) {
	mexico_string tempReader = NULL;
    mexico_int newSize = 0;
	/* TODO: Defensive programming */
	/* TODO: Reset Realocation */
	/* TODO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (mexico_int)sizeof(mexico_char) < readerPointer->size) {
		/* TODO: This buffer is NOT full */
	} else {
		/* TODO: Reset Full flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TODO: Adjust new size */
			/* TODO: Defensive programming */
			break;
		case MODE_MULTI:
			/* TODO: Adjust new size */
			/* TODO: Defensive programming */
			break;
		default:
			return NULL;
		}
		/* TODO: New reader allocation */
		/* TODO: Defensive programming */
		/* TODO: Check Relocation */
	}
	/* TODO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TODO: Updates histogram */
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerClear(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Adjust flags original */

    readerPointer->flags = 0x00;        // reset flags

	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;
	return MEXICO_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerFree(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Free pointers */

	return MEXICO_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerIsFull(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Check flag if buffer is FUL */
    Position* position = &readerPointer->position;
    if(position->wrte>=readerPointer->size) {

    }

	return MEXICO_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerIsEmpty(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Check flag if buffer is EMP */
	return MEXICO_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerSetMark(BufferPointer const readerPointer, mexico_int mark) {
	/* TODO: Defensive programming */
	/* TODO: Adjust mark */
	readerPointer->position.mark = mark;
	return MEXICO_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerPrint(BufferPointer const readerPointer) {
    mexico_int cont = 0;
	mexico_char c;
	/* TODO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TODO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerLoad(BufferPointer const readerPointer, FILE* const fileDescriptor) {
    mexico_int size = 0;
	mexico_char c;
	/* TODO: Defensive programming */
	c = (mexico_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TODO: Defensive programming */
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerRecover(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Recover positions */
	readerPointer->position.read = 0;
	return MEXICO_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerRetract(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Retract (return 1 pos read) */
	return MEXICO_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_bool readerRestore(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return MEXICO_TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_char readerGetChar(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Check condition to read/wrte */
	/* TODO: Set EOB flag */
	/* TODO: Reset EOB flag */
	if (readerPointer->position.wrte>0)
		return readerPointer->content[readerPointer->position.read++];
	return READER_TERMINATOR;
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_string readerGetContent(BufferPointer const readerPointer, mexico_int pos) {
	/* TODO: Defensive programming */
	/* TODO: Return content (string) */
	return readerPointer->content + pos;;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerGetPosRead(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerGetPosWrte(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Return wrte */
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerGetPosMark(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Return mark */
	return 0;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerGetSize(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Return size */
	return 0;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerGetInc(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Return increment */
	return 0;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerGetMode(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Return mode */
	return 0;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TODO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_byte readerGetFlags(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Return flags */
	return 0;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TODO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_void readerPrintStat(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Print the histogram */
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TODO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mexico_int readerNumErrors(BufferPointer const readerPointer) {
	/* TODO: Defensive programming */
	/* TODO: Returns the number of errors */
	return 0;
}
