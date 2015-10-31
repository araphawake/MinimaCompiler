#include <stdio.h>
#include <stdlib.h>

/* Maximum quantity of parameters accepted by a function in the Minima language */
static const int LIMIT_VARIABLES = 5;

/* Maximum size of the array which must hold the machine code for a Minima function */
static const int MAX_CODE_SIZE = 1024;

/* Maximum quantity of lines of a function written in Minima language code */
static const int LIMIT_LINES = 50;

/* Position of the byte that starts a line of Minima language code */
static const int BEGIN = 0;

/* Position of the byte that ends a line of Minima language code */
static const int END = 1;


/*
 *
 * Description:
 * 	This function adds the bytes for the prologue of an assembly function to the 
 * 	block of memory of the function to be returned as a pointer.
 * 
 * Parameters:
 * 	unsigned char * code: pointer to the block of memory which holds the machine
 * 	code of a function written in Minima and mapped into assembly.
 * 
 * Returns:
 * 	Nothing.
 *
 */

void addPrologue( unsigned char * code )
{

   /* 
	* push %ebp
	* movl %esp, %ebp
    */
	
	code[0] = 0x55;
	code[1] = 0x89;
	code[2] = 0xe5;
}


/*
 *
 * Description:
 * 	This function adds the bytes for the epilogue of an assembly function to the 
 * 	block of memory of the function to be returned as a pointer.
 * 
 * Parameters:
 * 	unsigned char * code: pointer to the block of memory which holds the machine
 * 	code of a function written in Minima and mapped into assembly.
 * 
 * Returns:
 * 	Nothing.
 *
 */

void addEpilogue( unsigned char * code, int codeByte )
{
	
   /* 
	* movl %ebp, %esp
	* pop %ebp
	* ret
    */
    	
	code[codeByte] = 0x89;
	code[(codeByte + 1)] = 0xec;
	code[(codeByte + 2)] = 0x5d;
	code[(codeByte + 3)] = 0xc3;
}

/*
 *
 * Description:
 * 	Tables as arrays for mapping assembly into machine code.
 *
 */

unsigned char parametersReturn [ ][ 3 ] = { 

	// mov  8(%ebp), %eax
	{ 0x8b, 0x45, 0x08 },
	
	// mov 12(%ebp), %eax  
	{ 0x8b, 0x45, 0x0c },  
	
	// mov 16(%ebp), %eax
	{ 0x8b, 0x45, 0x10 },  
	
	// mov 20(%ebp), %eax
	{ 0x8b, 0x45, 0x14 },  
	
	// mov 24(%ebp), %eax
	{ 0x8b, 0x45, 0x18 } 				 };
									  			 
unsigned char localsReturn 	[ ][ 3 ] = { 

	/* mov  -4(%ebp),%eax */
	{ 0x8b, 0x45, 0xfc },     
	
	/* mov  -8(%ebp),%eax */
	{ 0x8b, 0x45, 0xf8 },
	
	/* mov -12(%ebp),%eax */
	{ 0x8b, 0x45, 0xf4 },
	
	/* mov -16(%ebp),%eax */
	{ 0x8b, 0x45, 0xf0 },
	
	/* mov -20(%ebp),%eax */
	{ 0x8b, 0x45, 0xec } };
						 	 		 
unsigned char parameterMove[ ][ 3 ] = { 

	/* mov  8(%ebp),%ecx */
	{ 0x8b, 0x4d, 0x08 },
  	
  	/* mov  12(%ebp),%ecx */
  	{ 0x8b, 0x4d, 0x0c },
	
	/* mov  16(%ebp),%ecx */
	{ 0x8b, 0x4d, 0x10 },
  	
  	/* mov  20(%ebp),%ecx */
  	{ 0x8b, 0x4d, 0x14 },
  	
  	/* mov  24(%ebp),%ecx */
  	{ 0x8b, 0x4d, 0x18 },			};

unsigned char localMove[ ][ 3 ] = { 

	/* mov  -4(%ebp),%ecx */
	{ 0x8b, 0x4d, 0xfc },
	
	/* mov  -8(%ebp),%ecx */
	{ 0x8b, 0x4d, 0xf8 },
	
	/* mov -12(%ebp),%ecx */
	{ 0x8b, 0x4d, 0xf4 },
	
	/* mov -16(%ebp),%ecx */
	{ 0x8b, 0x4d, 0xf0 },
	
	/* mov -20(%ebp),%ecx */
	{ 0x8b, 0x4d, 0xec },	};

unsigned char parameterEDXMove[ ][ 3 ] = { 

	/* mov  8(%ebp),%edx */
	{ 0x8b, 0x55, 0x08 },
  	
  	/* mov  12(%ebp),%edx */
  	{ 0x8b, 0x55, 0x0c },
	
	/* mov  16(%ebp),%edx */
	{ 0x8b, 0x55, 0x10 },
  	
  	/* mov  20(%ebp),%edx */
  	{ 0x8b, 0x55, 0x14 },
  	
  	/* mov  24(%ebp),%edx */
  	{ 0x8b, 0x55, 0x18 },			};

unsigned char localEDXMove[ ][ 3 ] = { 

	/* mov  -4(%ebp),%edx */
	{ 0x8b, 0x55, 0xfc },
	
	/* mov  -8(%ebp),%edx */
	{ 0x8b, 0x55, 0xf8 },
	
	/* mov -12(%ebp),%edx */
	{ 0x8b, 0x55, 0xf4 },
	
	/* mov -16(%ebp),%edx */
	{ 0x8b, 0x55, 0xf0 },
	
	/* mov -20(%ebp),%edx */
	{ 0x8b, 0x55, 0xec },	};


unsigned char addParameter [ ][ 3 ] = { 

	/* addl 8(%ebp), %ecx */
	{ 0x03, 0x4d, 0x08 },
	
	/* addl 12(%ebp), %ecx */
	{ 0x03, 0x4d, 0x0c },  
	
	/* addl 16(%ebp), %ecx */
	{ 0x03, 0x4d, 0x10 },  
	
	/* addl 20(%ebp), %ecx */
	{ 0x03, 0x4d, 0x14 },  
	
	/* addl 24(%ebp), %ecx */
	{ 0x03, 0x4d, 0x18 } 			  };
	
unsigned char addLocals [ ][ 3 ] = { 

	/* addl -4(%ebp), %ecx */
	{ 0x03, 0x4d, 0xfc },
	
	/* addl -8(%ebp), %ecx */
	{ 0x03, 0x4d, 0xf8 },  
	
	/* addl -12(%ebp), %ecx */
	{ 0x03, 0x4d, 0xf4 },  
	
	/* addl -16(%ebp), %ecx */
	{ 0x03, 0x4d, 0xf0 },  
	
	/* addl -20(%ebp), %ecx */
	{ 0x03, 0x4d, 0xec } 			  };
	
unsigned char subParameter [ ][ 3 ] = { 

	/* addl 8(%ebp), %ecx */
	{ 0x2b, 0x4d, 0x08 },
	
	/* addl 12(%ebp), %ecx */
	{ 0x2b, 0x4d, 0x0c },  
	
	/* addl 16(%ebp), %ecx */
	{ 0x2b, 0x4d, 0x10 },  
	
	/* addl 20(%ebp), %ecx */
	{ 0x2b, 0x4d, 0x14 },  
	
	/* addl 24(%ebp), %ecx */
	{ 0x2b, 0x4d, 0x18 } 			  };
	
unsigned char subLocals [ ][ 3 ] = { 

	/* subl -4(%ebp), %ecx */
	{ 0x2b, 0x4d, 0xfc },
	
	/* subl -8(%ebp), %ecx */
	{ 0x2b, 0x4d, 0xf8 },  
	
	/* subl  -12(%ebp), %ecx */
	{ 0x2b, 0x4d, 0xf4 },  
	
	/* subl -16(%ebp), %ecx */
	{ 0x2b, 0x4d, 0xf0 },  
	
	/* subl -20(%ebp), %ecx */
	{ 0x2b, 0x4d, 0xec } 			  };
	
unsigned char mulParameters [ ][ 4 ] = { 

	/* imull 8(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0x08 },
	
	/* imull 12(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0x0c },  
	
	/* imull 16(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0x10 },  
	
	/* imull 20(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0x14 },  
	
	/* imull 24(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0x18 } 			  };
	
unsigned char mulLocals [ ][ 4 ] = { 

	/* imull -4(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0xfc },
	
	/* imull -8(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0xf8 },  
	
	/* imull -12(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0xf4 },  
	
	/* imull -16(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0xf0 },  
	
	/* imull -20(%ebp), %ecx */
	{ 0xf, 0xaf, 0x4d, 0xec } 			  };
	
unsigned char updateParameter [ ][ 3 ] = { 

	/* movl %ecx, 8(%ebp) */
	{ 0x89, 0x4d, 0x08 },
	
	/* movl %ecx, 12(%ebp) */
	{ 0x89, 0x4d, 0x0c },  
	
	/* movl %ecx, 16(%ebp) */
	{ 0x89, 0x4d, 0x10 },  
	
	/* addl %ecx, 20(%ebp) */
	{ 0x89, 0x4d, 0x14 },  
	
	/* movl %ecx, 24(%ebp) */
	{ 0x89, 0x4d, 0x18 } 			  };
			
unsigned char updateLocals [ ][ 3 ] = { 

	/* movl  %ecx, 8(%ebp) */
	{ 0x89, 0x4d, 0xfc },
	
	/* movl  %ecx, 12(%ebp) */
	{ 0x89, 0x4d, 0xf8 },  
	
	/* movl  %ecx, 16(%ebp) */
	{ 0x89, 0x4d, 0xf4 },  
	
	/* movl  %ecx, 20(%ebp) */
	{ 0x89, 0x4d, 0xf0 },  
	
	/* movll  %ecx, 24(%ebp) */
	{ 0x89, 0x4d, 0xec } 			  };

typedef int (*funcp) ( int, ... );

/*
 *
 * Description:
 *	This function reads a file containing a function written in the Minima language 
 *	and returns a pointer which holds the address for a block of memory containing
 *	the function, written in Minima language and then mapped into assembly, 
 *	in machine code.
 * 
 *	This compiler does not expects files with errors in respect to the Minima
 *	language syntax. Any error will be dealt in such a manner the returned pointer 
 *	will hold the address for a block of memory hosting corrupted code.
 * 
 * Using:
 * 
 * 1. Compile the geracod.c in the Terminal:
 * 
 * 		gcc -z execstack -m32 -Wall geracod.c main.c
 *
 * NOTE: main.c must hold the function int main ( int argc, char* argv[] ) which
 * opens the file passed to geracod function and calls geracod.c, obtaining the 
 * pointer to the block of memory holding the machine code that corresponds to 
 * the function compiled from Minima.
 * 
 * 2. Execute the program to execute a minima function written in a separated file.
 * 
 * 		./a.out minima
 *  
 * Parameters:
 *	FILE * input: a FILE * that corresponds to the file, already open, holding code
 *	written in Minima.
 * 
 * Returns:
 *	funcp code: pointer for a block of memory which holds machine code for
 *	a function written previously in Minima Language. In Minima language, a function
 *	can receive a maximum of five parameters. This information is essential whenever
 *	the function returned by geracod is called.
 *
 */

funcp geracod ( FILE * input )
{
	
	char command = '0', operator = '0', firstIdentifier = '0', secondIdentifier = '0';
	unsigned char * code;
	int line = 1, codeByte = 0, number = 0, numberOne = 0, numberTwo = 0, search = 1;
	int i = 0, reference = 0, difference = 0;
	int ifTable[LIMIT_LINES][2], ifStatement[LIMIT_LINES];
	
	/* Initialize the tables for reference and control of if statements */
	for( i = 0; i < LIMIT_LINES; i++ )
	{
		ifTable[i][BEGIN] = -1;
		ifTable[i][END] = -1;
		ifStatement[i] = -1;
	}
	
	/* Allocate memory for the array to be the holder of the machine code */
	code = ( unsigned char * ) malloc ( MAX_CODE_SIZE * sizeof( unsigned char ) );
	if( code == NULL )
	{
		printf("\n\nUnexpected memory allocation error ocurred.\n\n");
		exit(1);
	}
	
	/* Add machine code for the prologue of the assembly into which Minima is mapped */
	addPrologue( code );
	
	#ifdef _DEBUG
		printf("\n\nPrologue\n\n");	
	#endif
	
	/* Adds three to the counter of bytes considering the prologue adds three bytes */
	codeByte += 3;
	
	/* Reads the initial letter, identifies the Minima command and executes it */
	while( fscanf( input, " %c", &command ) == 1 && codeByte < MAX_CODE_SIZE )
	{
		/* Sets default value for search allowing initial search for '\n' */
		search = 1;

		switch( command )
		{
			
			/* In case of ret xi command (return), x being 'p'/'v'/'$' and i being a number */
			case 'r':

				if( fscanf( input, "et %c%d", &firstIdentifier, &number ) == 2 )
				{
				
					if( firstIdentifier == 'p' )
					{
						/* Assures the paremeter is valid as one out of a maximum of five */
						if( number < LIMIT_VARIABLES && number >= 0 )
						{
							/* Saves the first byte of the current line of Minima function */
							ifTable[line][BEGIN] = codeByte;
							
							/* Adds bytes to the array concerning the return of the current parameter */
							code[codeByte++] = parametersReturn[number][0];
							code[codeByte++] = parametersReturn[number][1];
							code[codeByte++] = parametersReturn[number][2];
							
							#ifdef _DEBUG
								printf("\n\nParametro\n\n");
							#endif
							
							/* Saves the last byte of the current line of Minima function */
							ifTable[line][END] = codeByte - 1;
						}
						else
						{
							printf("\n\nError: number of parameters was exceeded.\n\n");
							exit(1);
						}
					}
					else if( firstIdentifier == 'v' )
					{
						/* Assures the local variable is valid as one out of a maximum of five */
						if( number < LIMIT_VARIABLES && number >= 0 )
						{
							/* Saves the first byte of the current line of Minima function */
							ifTable[line][BEGIN] = codeByte;
							ifTable[line][BEGIN] = codeByte;
							
							/* Adds bytes to the array concerning the return of a local variable */
							code[codeByte++] = localsReturn[number][0];
							code[codeByte++] = localsReturn[number][1];
							code[codeByte++] = localsReturn[number][2];
							
							#ifdef _DEBUG
								printf("\n\nLocal\n\n");
							#endif
							
							/* Saves the last byte of the current line of Minima function */
							ifTable[line][END] = codeByte - 1;
						}
						else
						{
							printf("\n\nError: number of local variables was exceeded.\n\n");
							exit(1);
						}


					}
					else if( firstIdentifier == '$' )
					{
						/* Saves the first byte of the current line of Minima function */
						ifTable[line][BEGIN] = codeByte;
						
						/*  Adds bytes for the return of a constant value "$i" */
						code[codeByte++] = 0xb8;
						code[codeByte++] = (unsigned char)  number;
						code[codeByte++] = (unsigned char) (number >> 8);
						code[codeByte++] = (unsigned char) (number >> 16);
						code[codeByte++] = (unsigned char) (number >> 24);  
						
						#ifdef _DEBUG
							printf("\n\nConstante\n\n");
						#endif
						
						/* Saves the last byte of the current line of Minima function */
						ifTable[line][END] = codeByte - 1;
					}
					else
					{
						printf("\n\nInvalid minima identifier found: '%c'\n\n", firstIdentifier );
						exit(1);
					}
					
				}
				
				break;
			
				
			/* In case of line starting with 'p' or 'v' */
			case 'p': case 'v':
			
				
				if (fscanf(input, "%d := %c%d%c",&number, &firstIdentifier, &numberOne, &operator ) == 4 )
				{
					/* Saves the first byte of the current line of Minima function */
					ifTable[line][BEGIN] = codeByte;
					
					/* Search for '\n' or '+'/'-'/'*' characters on the current line of the Minima function */
					while( search == 1 )
					{
						/* Assures that parameters are valid as one out of a maximum of five */
						/* Assures that the second element might be a constant type "$i", i = integers */
						if( number < LIMIT_VARIABLES && number >= 0 
							&& ( ( numberOne < LIMIT_VARIABLES && numberOne >= 0 ) || firstIdentifier == '$' )  ) 
						{
							/* In case operator found equals '\n', end of line and attribution must be completed */
							if( operator == '\n' )
							{
								/* Moves value of the parameter to %ecx */
								if( firstIdentifier == 'p' )
								{
								
									code[codeByte++] = parameterMove[numberOne][0];
									code[codeByte++] = parameterMove[numberOne][1];
									code[codeByte++] = parameterMove[numberOne][2];
								}
								/* Moves value of the local variable to %ecx */
								else if( firstIdentifier == 'v' )
								{
									
									
									code[codeByte++] = localMove[numberOne][0];
									code[codeByte++] = localMove[numberOne][1];
									code[codeByte++] = localMove[numberOne][2];
								}
								/* Moves value of a constant integer to %ecx */
								else if( firstIdentifier == '$' )
								{
									
									code[codeByte++] = 0xb9;
									code[codeByte++] = (unsigned char)  numberOne;
									code[codeByte++] = (unsigned char) (numberOne >> 8);
									code[codeByte++] = (unsigned char) (numberOne >> 16);
									code[codeByte++] = (unsigned char) (numberOne >> 24);
								}
								else
								{
									printf("\n\nInvalid minima identifier found: '%c'\n\n", firstIdentifier);
									exit(1);
								}		
							}
					  	 }
					  	 else
					  	 {
						 	printf("\neError: number of parameters or local variables was exceeded.\n\n");
					 		exit(1);
						 }
					
						 if( operator == '\n' )
						 {
							if( command == 'p' )
							{
								/* Update the value stored by the current parameter */
								code[codeByte++] = updateParameter[number][0];
								code[codeByte++] = updateParameter[number][1];
								code[codeByte++] = updateParameter[number][2];
							}
							else
							{
								/* Update the value stored by the current parameter */
								code[codeByte++] = updateLocals[number][0];
								code[codeByte++] = updateLocals[number][1];
								code[codeByte++] = updateLocals[number][2];
							}
							
							search = 0;
							
							ifTable[line][END] = codeByte - 1;
							break;
						 }
						 /* Reads a new character until it's different than ' ' */
						 else if( operator == ' ' )
						 { 
							if( fscanf( input, "%c", &operator ) == 1 )
							{
								if( operator == ' ' || operator == '\n' )
								{
									search = 1;
								}
								else if( operator == '+' || operator == '-' || operator == '*' )
								{
									/* while must continue to operations '+'/'-'/'*' */
									search = 0;
								}
								else
								{
									search = 2;
								}
							
							}
							else
							{
								printf("\neError: Invalid function of minima. Minima terminated unexpectedly.\n\n");
								exit(1);
							}
						
						 }
						 else if( operator == '+' || operator == '-' || operator == '*' )
						 { 
							search = 0;
						 }
					}
				}
				
				/* Finish while as attribution has been completed */
				if( operator == '\n' )
				{
					break;
				}
				
				/* Addition or Subtraction or Multiplication is executed */
				if( operator == '+' || operator == '-' || operator == '*' )
				{
					/* Reads the second element of the operation */
					if (fscanf(input, " %c%d", &secondIdentifier, &numberTwo) == 2)
					{
					
						/* Validates all elements */
						if( number < LIMIT_VARIABLES && number >= 0 
							&& ( ( numberOne < LIMIT_VARIABLES && numberOne >= 0 ) || firstIdentifier == '$' ) 
							&& ( ( numberTwo < LIMIT_VARIABLES && numberTwo >= 0 ) || secondIdentifier == '$' ) ) 
						{
						
							if( operator == '+' || operator == '-' || operator == '*' )
							{
								/* Moves the parameter (first element) to %ecx */
								if( firstIdentifier == 'p' )
								{
									code[codeByte++] = parameterMove[numberOne][0];
									code[codeByte++] = parameterMove[numberOne][1];
									code[codeByte++] = parameterMove[numberOne][2];
								}
								/* Moves the local variable (first element) to %ecx */
								else if( firstIdentifier == 'v' )
								{
									code[codeByte++] = localMove[numberOne][0];
									code[codeByte++] = localMove[numberOne][1];
									code[codeByte++] = localMove[numberOne][2];
								}
								/* Moves the constant (first element) to %ecx */
								else if( firstIdentifier == '$' )
								{
									code[codeByte++] = 0xb9;
									code[codeByte++] = (unsigned char)  numberOne;
									code[codeByte++] = (unsigned char) (numberOne >> 8);
									code[codeByte++] = (unsigned char) (numberOne >> 16);
									code[codeByte++] = (unsigned char) (numberOne >> 24);
								}
								else
								{
									printf("\n\nInvalid minima identifier found: '%c'\n\n", command);
									exit(1);
								}
							}
							else
							{
								printf("\n\nInvalid minima identifier found: '%c'\n\n", command);
								exit(1);
							}
							
						
							if( operator == '+' )
							{
								/* Adds the parameter (second element) to %ecx */
								if( secondIdentifier == 'p' )
								{
									code[codeByte++] = addParameter[numberTwo][0];
									code[codeByte++] = addParameter[numberTwo][1];
									code[codeByte++] = addParameter[numberTwo][2];
								}
								/* Adds the local variable (second element) to %ecx */								
								else if( secondIdentifier == 'v' )
								{
									code[codeByte++] = addLocals[numberTwo][0];
									code[codeByte++] = addLocals[numberTwo][1];
									code[codeByte++] = addLocals[numberTwo][2];
								}
								/* Adds the constant (second element) to %ecx */
								else if( secondIdentifier == '$' )
								{
									/* Moves constant to %edx */
									code[codeByte++] = 0xba;
									code[codeByte++] = (unsigned char)  numberTwo;
									code[codeByte++] = (unsigned char) (numberTwo >> 8);
									code[codeByte++] = (unsigned char) (numberTwo >> 16);
									code[codeByte++] = (unsigned char) (numberTwo >> 24);
									
									/* addl %edx, %ecx */
									code[codeByte++] = 0x01;
									code[codeByte++] = 0xd1;
								
								}
								else
								{
									
									printf("\n\nInvalid minima identifier found: '%c'\n\n", command);
									exit(1);
								}
						
							}
							else if( operator == '-' )
							{
								/* Subtracts the parameter variable (second element) to %ecx */	
								if( secondIdentifier == 'p' )
								{
									code[codeByte++] = subParameter[numberTwo][0];
									code[codeByte++] = subParameter[numberTwo][1];
									code[codeByte++] = subParameter[numberTwo][2];
								}
								/* Subtracts the local variable (second element) to %ecx */
								else if( secondIdentifier == 'v' )
								{
									code[codeByte++] = subLocals[numberTwo][0];
									code[codeByte++] = subLocals[numberTwo][1];
									code[codeByte++] = subLocals[numberTwo][2];
								}
								/* Subtracts the constant (second element) to %ecx */
								else if( secondIdentifier == '$' )
								{
									/* Moves constant to %edx */
									code[codeByte++] = 0xba;
									code[codeByte++] = (unsigned char)  numberTwo;
									code[codeByte++] = (unsigned char) (numberTwo >> 8);
									code[codeByte++] = (unsigned char) (numberTwo >> 16);
									code[codeByte++] = (unsigned char) (numberTwo >> 24);
									
									/* subl %edx, %ecx */
									code[codeByte++] = 0x29;
									code[codeByte++] = 0xd1;

								}
								else
								{
									printf("\n\nInvalid minima identifier found: '%c'\n\n", command);
									exit(1);
								}
						
							}
							else if( operator == '*' )
							{
								/* Multiplies the parameter variable (second element) to %ecx */
								if( secondIdentifier == 'p' )
								{
									code[codeByte++] = mulParameters[numberTwo][0];
									code[codeByte++] = mulParameters[numberTwo][1];
									code[codeByte++] = mulParameters[numberTwo][2];
									code[codeByte++] = mulParameters[numberTwo][3];
								}
								/* Multiplies the parameter variable (second element) to %ecx */
								else if( secondIdentifier == 'v' )
								{
									code[codeByte++] = mulLocals[numberTwo][0];
									code[codeByte++] = mulLocals[numberTwo][1];
									code[codeByte++] = mulLocals[numberTwo][2];
									code[codeByte++] = mulLocals[numberTwo][3];
								}
								/* Multiplies the parameter variable (second element) to %ecx */
								else if( secondIdentifier == '$' )
								{
									code[codeByte++] = 0xba;
									code[codeByte++] = (unsigned char)  numberTwo;
									code[codeByte++] = (unsigned char) (numberTwo >> 8);
									code[codeByte++] = (unsigned char) (numberTwo >> 16);
									code[codeByte++] = (unsigned char) (numberTwo >> 24);
									code[codeByte++] = 0x0f;
									code[codeByte++] = 0xaf;
									code[codeByte++] = 0xca;
								}
								else
								{
									printf("\n\nInvalid minima identifier found: '%c'\n\n", command);
									exit(1);
								}
							
							}

						}				
						else 
						{
							printf("\neError: number of parameters or local variables was exceeded.\n\n");
							exit(1);
						}
					
						if( command == 'p' )
						{
							/* Update the value stored by the current parameter */
							code[codeByte++] = updateParameter[number][0];
							code[codeByte++] = updateParameter[number][1];
							code[codeByte++] = updateParameter[number][2];
						}
						else
						{
							/* Update the value stored by the current parameter */
							code[codeByte++] = updateLocals[number][0];
							code[codeByte++] = updateLocals[number][1];
							code[codeByte++] = updateLocals[number][2];
						}
						
						ifTable[line][END] = codeByte - 1;
					}
				}
				else
				{
					printf("\n\nInvalid minima identifier found: '%c'\n\n", command);
					exit(1);
				}
				
				break;	
				
			/* In case of if statement */	
			case 'i':
			{
		
				if( fscanf( input, "feq %c%d %c%d %d", &firstIdentifier, &numberOne, &secondIdentifier, &numberTwo, &reference ) == 5 )
				{

					/* Saves the first byte of the current line of Minima function */
					ifTable[line][BEGIN] = codeByte;
						
					/* Moves value of the parameter (first element) to %ecx */
					if( firstIdentifier == 'p' )
					{	
						code[codeByte++] = parameterMove[numberOne][0];
						code[codeByte++] = parameterMove[numberOne][1];
						code[codeByte++] = parameterMove[numberOne][2];
					}
					/* Moves value of the local variable (first element) to %ecx */
					else if( firstIdentifier == 'v' )
					{	
						code[codeByte++] = localMove[numberOne][0];
						code[codeByte++] = localMove[numberOne][1];
						code[codeByte++] = localMove[numberOne][2];
					}
					/* Moves value of the constant (first element) to %ecx */
					else if( firstIdentifier == '$' )
					{	
						code[codeByte++] = 0xb9;
						code[codeByte++] = (unsigned char)  numberOne;
						code[codeByte++] = (unsigned char) (numberOne >> 8);
						code[codeByte++] = (unsigned char) (numberOne >> 16);
						code[codeByte++] = (unsigned char) (numberOne >> 24);
					}
					else
					{
						printf("\n\nInvalid minima identifier found: '%c'\n\n", firstIdentifier);
						exit(1);
					}
					
					/* Moves value of the parameter (second element) to %edx */
					if( secondIdentifier == 'p' )
					{
						code[codeByte++] = parameterEDXMove[numberTwo][0];
						code[codeByte++] = parameterEDXMove[numberTwo][1];
						code[codeByte++] = parameterEDXMove[numberTwo][2];
					}
					/* Moves value of the local parameter (second element) to %edx */
					else if( secondIdentifier == 'v' )
					{
						code[codeByte++] = localEDXMove[numberTwo][0];
						code[codeByte++] = localEDXMove[numberTwo][1];
						code[codeByte++] = localEDXMove[numberTwo][2];
					}
					/* Moves value of the constant (second element) to %edx */
					else if( secondIdentifier == '$' )
					{
						code[codeByte++] = 0xba;
						code[codeByte++] = (unsigned char)  numberTwo;
						code[codeByte++] = (unsigned char) (numberTwo >> 8);
						code[codeByte++] = (unsigned char) (numberTwo >> 16);
						code[codeByte++] = (unsigned char) (numberTwo >> 24);
						
					}
					else
					{
						printf("\n\nInvalid minima identifier found: '%c'\n\n", secondIdentifier);
						exit(1);
					}
					
					/* Adds the bytes mapped into assembly cmpl %ecx, %edx */
					if( line != reference && line + 1 != reference )
					{
						code[codeByte++] = 0x39;
						code[codeByte++] = 0xd1;
					}
					
					/* Assures the line to go to from the current if statement has been visited already */
					if( ifTable[reference][BEGIN] != -1 && line != reference && line + 1 != reference && ifStatement[i] == -1 )
					{
					
					   /* Difference between the first byte of the line to go to from
						* the current if statement and the last byte of the line of the current
						* if statement
						*/
						difference = ifTable[reference][BEGIN] - 1 - codeByte + 2;

						/* if statement concerning small distance between origin and destination */
						if( difference < 128 && difference > -128 )
						{
							/* je */
							code[codeByte++] = 0x74;
							code[codeByte++] = (unsigned char) ( difference );
						}
						/* Concerns great distance between origin and destination */
						else
						{
						   /* Difference between the first byte of the line to go to from
							* the current if statement and the last byte of the line of the current
							* if statement
							*/
							difference = ifTable[reference][BEGIN] - 1 - codeByte + 4;

							if( difference < 128 && difference > -128 )
							{
								/* je */
								code[codeByte++] = 0x0f;
								code[codeByte++] = 0x84;
								code[codeByte++] = (unsigned char) ( difference );
								code[codeByte++] = (unsigned char) ( difference >>  8 );
								code[codeByte++] = (unsigned char) ( difference >> 16 );
								code[codeByte++] = (unsigned char) ( difference >> 24 );
							}
						}

					}
					/* Assures the line to go to from the current if statement has not been visited yet */
					else
					{
						
						ifStatement[line] = reference; 
						
						/* if statement concerning great distance between origin and destination */
						if( difference >= 128 && difference <= -128 )
						{
							/* je */
							code[codeByte++] = 0x0f;
							code[codeByte++] = 0x84;
							codeByte += 4;
						}
						/* Concerns small distance between origin and destination */
						else
						{
							/* je */
							code[codeByte++] = 0x74;
							codeByte++;
						}
						
					}
					
					ifTable[line][END] = codeByte - 1;
				}

				break;
			}

			default:
				printf("\n\nInvalid minima line starter identifier found: '%c'\n\n", command);
				exit(1);
				break;
			
		}
		
		/* Line of the Minima function being read through the opened file */
		line++;
		
	}

	#ifdef _DEBUG	
		printf("\n\nAntes epilogo %d\n\n", line);
	#endif
	
   /* Assures every if statement of each line is filled with information of the distance
	* between the origin byte and the destination byte
	*/

	for( i = 0; i < LIMIT_LINES; i++ )
	{

		if( ifStatement[i] != -1 && ifStatement[i] != i && ifStatement[i] != i + 1  )
		{
			
			difference = ifTable[ ifStatement[i] ][BEGIN] - 1 - ifTable[i][END];		
			if( difference < 128 && difference > -128 )
			{

				code[ ifTable[i][END] ] = (unsigned char) ( difference );

			}
			else
			{
				code[ ifTable[i][END] - 3 ] = (unsigned char) ( difference );
				code[ ifTable[i][END] - 2 ] = (unsigned char) ( difference >>  8 );
				code[ ifTable[i][END] - 1 ] = (unsigned char) ( difference >> 16 );
				code[ ifTable[i][END] - 0 ] = (unsigned char) ( difference >> 24 );
			}
		}
	}

	/* Adds the bytes concerning the epilogue */	
	addEpilogue( code, codeByte );
	
	#ifdef _DEBUG
		printf("\n\nFim\n\n");
	#endif
	
	return (funcp) code;

}
