#include "monty.h"

/**
 * err - Prints appropriate error messages determined by their error code.
 * @error_code: The error codes and their meanings:
 *   (1) => User provides no file or more than one file to the program.
 *   (2) => The provided file cannot be opened or read.
 *   (3) => The file contains an unknown instruction.
 *   (4) => Malloc fails to allocate more memory.
 *   (5) => The "push" instruction is not followed by an integer parameter.
 *   (6) => Attempting to print an empty stack with the "pint" instruction.
 */
void err(int error_code, ...)
{
	va_list args;
	char *operation;
	int line_number;

	va_start(args, error_code);
	switch (error_code)
	{
	case 1:
		fprintf(stderr, "USAGE: monty file\n");
		break;
	case 2:
		fprintf(stderr, "Error: Can't open file %s\n", va_arg(args, char *));
		break;
	case 3:
		line_number = va_arg(args, int);
		operation = va_arg(args, char *);
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, operation);
		break;
	case 4:
		fprintf(stderr, "Error: malloc failed\n");
		break;
	case 5:
		fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
		break;
	default:
		break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * more_err - Handles additional errors.
 * @error_code: The error codes and their meanings:
 *   (6) => Attempting to print an empty stack with the "pint" instruction.
 *   (7) => Attempting to pop from an empty stack.
 *   (8) => The stack is too short for the given operation.
 *   (9) => Division by zero.
 */
void more_err(int error_code, ...)
{
	va_list args;
	char *operation;
	int line_number;

	va_start(args, error_code);
	switch (error_code)
	{
	case 6:
		fprintf(stderr, "L%d: can't pint, stack empty\n", va_arg(args, int));
		break;
	case 7:
		fprintf(stderr, "L%d: can't pop an empty stack\n", va_arg(args, int));
		break;
	case 8:
		line_number = va_arg(args, unsigned int);
		operation = va_arg(args, char *);
		fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, operation);
		break;
	case 9:
		fprintf(stderr, "L%d: division by zero\n", va_arg(args, unsigned int));
		break;
	default:
		break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * string_err - Handles errors related to string operations.
 * @error_code: The error codes and their meanings:
 *   (10) => The value inside a node is outside ASCII bounds.
 *   (11) => The stack is empty for string operations.
 */
void string_err(int error_code, ...)
{
	va_list args;
	int line_number;

	va_start(args, error_code);
	line_number = va_arg(args, int);
	switch (error_code)
	{
	case 10:
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		break;
	case 11:
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		break;
	default:
		break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
