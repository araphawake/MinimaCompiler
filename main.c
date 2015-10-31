#include <stdio.h>
#include <stdlib.h>

typedef int (*funcp) (int i, ...);
funcp geracod (FILE *f);

int main ( int argc, char* argv[] )
{
	int returnValue = 0;
	funcp function;
	FILE * input;
	
	input = fopen( argv[1], "r" );
	if( input == NULL )
	{
		printf("\n\n>>>> Erro de abertura de arquivo na linguagem Minima.\n\n");
		exit(1);
	}
	
	function = geracod( input );	

	returnValue = (*function)( 2, 4, 5, 6, 7 );
	
	printf("\n%d\n\n", returnValue);
	
	if( input != NULL )
		fclose( input );
	
	return 0;

}
