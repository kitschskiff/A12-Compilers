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
    /* check if mode is valid */
    if(mode != MODE_ADDIT && mode != MODE_MULTI && mode != MODE_FIXED) { /* invalid mode */
        return NULL;
    }
    /* initialize in memory */
    readerPointer = (BufferPointer) calloc(1, sizeof(Buffer));
    if (!readerPointer) {     /* if allocation fails. */
        readerFree(readerPointer);
        return NULL;
    }
    if(size<0)
        size=READER_DEFAULT_SIZE;
    if(increment<0)
        increment=READER_DEFAULT_INCREMENT;
    readerPointer->content = (mexico_string) malloc(size);
    if (!readerPointer->content) { /* malloc fail check */
        /* free memory */
        readerFree(readerPointer);
        return NULL;
    }
    readerPointer->size = size;     /* set size property */
    int i;  /* initialize histogram */
    for(i=0;i<NCHAR;i++)
        readerPointer->histogram[i]=0;

    readerPointer->increment = increment;
    readerPointer->mode = mode;

    readerPointer->flags = READER_DEFAULT_FLAG;    /* default flag */
	readerPointer->flags|=READER_EMP;       /* set empty flag */
    /* NEW: Cleaning the content */
	if (readerPointer->content)         
		readerPointer->content[0] = READER_TERMINATOR;
	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;

	return readerPointer;
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
	mexico_string tempBuffer = NULL;
    mexico_int newSize = 0;
    if(readerPointer==NULL)                                 /* BufferReader does not exist */
        return NULL;
    if(((mexico_int)ch < 0) || ((mexico_int)ch >= NCHAR))  /* CHAR exceeds range */
        return NULL;
    if((readerPointer->flags&READER_FUL)==READER_FUL)        /* CHK FUL flag SET  */
        return NULL;

    readerPointer->flags &= ~READER_REL;                    /* RST Reallocation flag */
    /* check if next memory address exceeds allocation (write displacement in chars * sizeof char < buffer allocation) */
	if (readerPointer->position.wrte * (mexico_int)sizeof(mexico_char) < readerPointer->size) {
        /* not full */
        readerPointer->flags &= ~READER_FUL;        /* RST Full flag */
        /* check if ultimate capacity has been reached. */
        if(readerPointer->position.wrte >= READER_MAX_SIZE) {
            readerPointer->flags |= READER_FUL;        /* SET Full flag */
            return NULL;
        }
        /* fall through to after else statement body */
	} else {
        readerPointer->flags &= ~READER_FUL;        /* RST ful flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:       /* can't resize reader on fixed mode */
            readerPointer->flags|=READER_FUL;   /* set FUL flag */
			return NULL;
		case MODE_ADDIT:        /* Additive */
            /* Add reader increment to size. */
            newSize = readerPointer->position.wrte+readerPointer->increment;
			break;
		case MODE_MULTI:        /* Multiplicative */
            /* Multiply reader size by increment. */
            newSize = readerPointer->position.wrte*(readerPointer->increment++);    /* add 1 to multiplicative increment */
			break;
		default:
			return NULL;
		}
        if(newSize<0 || newSize > READER_MAX_SIZE) { /* check for condition newSize not within valid bounds (overflow possible) */
            readerPointer->flags|=READER_FUL;       /* set FUL flag */
            return NULL;
        }
        tempBuffer = realloc(
                readerPointer->content,
                newSize);
        if(tempBuffer==NULL)                        /* check if allocation failed */
            return NULL;
        if(tempBuffer!=readerPointer->content) {  /* address changed (could not resize on same address) */
            readerPointer->content = tempBuffer;  /* assign new address location (previous allocation was freed) */
            readerPointer->flags |= READER_REL;     /* set MEMORY RELOCATION bit */
        }
        readerPointer->size = newSize;          /* update size */
	}
	readerPointer->content[readerPointer->position.wrte++] = ch;    /* add char */
    readerPointer->histogram[(mexico_int)ch]++;                     /* update histogram */

	return readerPointer;           /* return initialized readerPointer */
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
    int i;
    if(readerPointer==NULL) /* check if readerPointer NULL. */
        return MEXICO_FALSE;

    readerPointer->flags = READER_DEFAULT_FLAG;        /* reset flags */
    readerPointer->flags|=READER_EMP;

    for(i=0;i<NCHAR;i++)        /* reset histogram */
        readerPointer->histogram[i]=0;

    /*  not necessary to set content values to 0 */

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
    if(!readerPointer)  /* check if exists */
        return MEXICO_FALSE;
    if(!readerPointer->content)
        return MEXICO_FALSE;
    /* free memory allocations */
    free(readerPointer->content);
    free(readerPointer);

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
	/* Defensive programming */
    if(!readerPointer)
        return MEXICO_FALSE;
	/* Check flag if buffer is FUL */
    if((readerPointer->flags&READER_FUL)==READER_FUL)
        return MEXICO_TRUE;

    /* Check if buffer is full if wrte exceeds or equals size */
    Position* position = &readerPointer->position;
    if(position->wrte>=readerPointer->size) {
        return MEXICO_TRUE;
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
	/* Defensive programming */
    if(!readerPointer)
        return MEXICO_FALSE;
	/* Check flag if buffer is EMP */
    if((readerPointer->flags&READER_EMP)==READER_EMP)
        return MEXICO_TRUE;

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
	/* Defensive programming */
    if(!readerPointer)                                  /* reader not initialized */
        return MEXICO_FALSE;
    if(mark<0 || mark>=readerPointer->position.wrte)    /* invalid mark */
        return MEXICO_FALSE;
	/* Adjust mark */
	readerPointer->position.mark = mark;                /* adjust mark */
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
	/* Defensive programming (including invalid chars) */
    if(!readerPointer)      /* on-fail return Error value */
        return READER_ERROR;
	c = readerGetChar(readerPointer);
    if(((mexico_int)c<0) || ((mexico_int)c>=NCHAR))
        return READER_ERROR;  /* invalid char, return error. */
	/* Check flag if buffer EOB has achieved */
    if((readerPointer->flags&READER_END)==READER_END)
        return cont;  /* skip look if End-Of-Buffer */
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
        if((readerPointer->flags&READER_END)==READER_END)
            break;      /* break look if End-Of-Buffer reached. */
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR;      /* ERR value */
    if(!fileDescriptor)
        return READER_ERROR;
	c = (mexico_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
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
	/* Defensive programming */
    if(!readerPointer)
        return MEXICO_FALSE;
	/* Recover positions */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
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
	/* Defensive programming */
    if(!readerPointer)
        return MEXICO_FALSE;
	/* Retract (return 1 pos read) */
    if((readerPointer->position.read-1)<0)    /* check if read will be negative */
        return MEXICO_FALSE;
    readerPointer->position.read--;

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
	/* Defensive programming */
    if(!readerPointer)
        return MEXICO_FALSE;
	/* Restore positions (read/mark) */
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
	char c;

    if(!readerPointer)
        return MEXICO_FALSE;
    if((readerPointer->flags&READER_END) == READER_END)     /* check if already reached end */
        return MEXICO_FALSE;
    if(readerPointer->position.read>=readerPointer->position.wrte || readerPointer->position.wrte<=0) {/* check if reached end of character buffer */
        readerPointer->flags |= READER_END;
        return READER_TERMINATOR;
    }
    c=readerPointer->content[readerPointer->position.read++];       /* get character */
    readerPointer->flags &= !READER_END;

	return c;
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
	/* Defensive programming */
    if(!readerPointer)
        return MEXICO_FALSE;
    /* pos should be greater than 0, shouldn't be equivalent or greater than next write position. */
    if(pos<0 || pos>=readerPointer->position.wrte) {
        return MEXICO_FALSE;
    }
	/* Return content (string) */
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR;  /* return sentinel */
	/* Return read */
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR;   /* return sentinel */
	/* Return wrte */
	return readerPointer->position.wrte;
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR;  /* return sentinel */
	/* Return mark */
	return readerPointer->position.mark;
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR;      /* return sentinel */
	/* Return size */
	return readerPointer->size;
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
	/* Defensive programming */
    if(!readerPointer)
        return MEXICO_FALSE;
	/* Return increment */
	return readerPointer->increment;
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR;      /* return sentinel */
	/* Return mode */
	return readerPointer->mode;
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR;  /* sentinel */
	/* Return flags */
	return readerPointer->flags;    /*Entire flag?*/
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
    int i;
    /* Defensive programming */
    if(!readerPointer)
        return;     /* quit subroutine if invalid */
	/* Print the histogram */
    printf("Histogram:\n");
    for(i=0;i<NCHAR;i++) {
        if(i<33)
            switch(i) {
                case(0):
                    printf("ASCII NUL appears %d times\n", readerPointer->histogram[i]);
                    break;
                case (10):
                    printf("ASCII LF appears %d times\n", readerPointer->histogram[i]);
                    break;
                case (32):
                    printf("ASCII SPACE appears %d times\n", readerPointer->histogram[i]);
                    break;
                default:
                    printf("ASCII %d appears %d times\n", i, readerPointer->histogram[i]);
            }
        else if(i==127)
            printf("ASCII DEL appears %d times\n", readerPointer->histogram[i]);
        else
            printf("ASCII %c appears %d times\n", i, readerPointer->histogram[i]);
    }
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
	/* Defensive programming */
    if(!readerPointer)
        return READER_ERROR; /* sentinel */
	/* Returns the number of errors */
	return readerPointer->numReaderErrors;
}
