#include "monty.h"

/**
 * main - monty porgramming language
 * @argc: number of args
 * @argv: pointer to arg array
 *
 * Return: Always 0
 */

int main(int argc, char **argv)
{
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	
	read_file(argv[1], &stack);
	free_list(stack);

	return (0);
}
