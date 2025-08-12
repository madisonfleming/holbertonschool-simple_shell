#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For malloc and free

int main(int argc, char *argv[]) {
    /* Check if the correct number of arguments is provided*/
	if (argc != 2) 
	{
		printf("%s\n", argv[0]);
		return 1;
	}

    /*Create a mutable copy of the input string because strtok modifies the original string*/
	char *input = strdup(argv[1]);
	if (input == NULL) 
	{
		printf("Error");
		return 1;
	}

	char *token;
	const char *delimiter = " "; /* Example delimiter: space*/

	printf("%s\n", input);

    /* Get the first token*/
	token = strtok(input, delimiter);

    /* Loop through the string to extract all other tokens*/
	while (token != NULL) 
	{
		printf("  %s\n", token);
	/* Get the next token by passing NULL as the first argument*/
	token = strtok(NULL, delimiter);
	}

    /* Free the dynamically allocated memory */
	free(input);

	return 0;
}
