#include "monty.h"

/**
 * isnumber - checks if a string is a number
 * @s: pointer to the string
 *
 * Return: 1 if true, else 0
 */

int isnumber(char *s)
{
	unsigned int i = 0;

	if (!s)
		return (0);
	while (s[i])
	{
		if (s[0] == '-')
		{
			++i;
			continue;
		}
		if (s[i] < 48 && s[i] > 58)
			return (0);
		++i;
	}
	return (1);
}

/**
 * parse_line - parse each line of command
 * @line: line to be parsed
 * @stack: pointer to the head
 * @line_num: current line count
 *
 * Return: NULL on false, else opcode
 */
char *parse_line(char *line, stack_t **stack, unsigned int line_num)
{
	char *opcode, *arg, *push = "push";
	(void)stack;

	opcode = strtok(line, "\n ");
	if (opcode == NULL)
		return (NULL);

	if (strcmp(opcode, push) == 0)
	{
		arg = strtok(NULL, "\n ");
		if (isnumber(arg) == 1)
			global_var.push_val = atoi(arg);
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_num);
			exit(EXIT_FAILURE);
		}
	}
	return (opcode);
}


/**
 * get_op_func - gets the appropriate function based on the opcode
 * @s: pointer to the opcode
 *
 * Return: NULL or function
 */
instruct_func get_op_func(char *s)
{
	int i = 0;
	instruction_t instructions[] = {
					{"push", _push},
					{"pall", _pall},
					{"pint", _pint},
					{"pop", _pop},
					{"swap", _swap},
					{"add", _add},
					{"nop", _nop},
					{"sub", _sub},
					{"mul", _mul},
					{"div", _div},
					{"mod", _mod},
					{"pstr", _pstr},
					{"pchar", _pchar},
					{"rotl", _rotl},
					{"rotr", _rotr},
					{NULL, NULL},
	};

	while (instructions[i].f != NULL && strcmp(instructions[i].opcode, s) != 0)
		++i;

	return (instructions[i].f);
}

/**
 * read_file - reads bycode and runs commnads
 * @filename: file name
 * @stack: pointer to the head
 */
void read_file(char *filename, stack_t **stack)
{
	char *line;
	size_t i = 0;
	int check, read, line_count = 1;
	instruct_func s;

	global_var.file = fopen(filename, "r");

	if (global_var.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&global_var.buffer, &i, global_var.file)) != -1)
	{
		line = parse_line(global_var.buffer, stack, line_count);

		if (line == NULL || line[0] == '#')
		{
			++line_count;
			continue;
		}

		s = get_op_func(line);
		if (s == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_count, line);
			exit(EXIT_FAILURE);
		}

		s(stack, line_count);
		++line_count;
	}
	free(global_var.buffer);
	check = fclose(global_var.file);
	if (check == -1)
		exit(-1);
}
