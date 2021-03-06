#include "stdafx.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("usage: binhex <input file> [output file]\n");
		return 0;
	}

	FILE* input = 0;
	fopen_s(&input, argv[1], "rb");
	if (!input)
	{
		printf("binhex: failed to open '%s'\n", argv[1]);
		return 0;
	}

	FILE* output = stdout;
	if (argv[2])
	{
		fopen_s(&output, argv[2], "w");
		if (!output)
		{
			printf("binhex: failed to open output file '%s'. writing to stdout instead.\n", argv[2]);
			output = stdout;
		}
	}

	fseek(input, 0, SEEK_END);
	long filesize = ftell(input);
	fseek(input, 0, SEEK_SET);

	for (int i = 0; i < filesize; i++)
	{
		unsigned char c;
		size_t numRead = fread_s(&c, sizeof(c), 1, 1, input);
		if (numRead != 1 || feof(input))
		{
			printf("binhex: eof while reading from file\n");
			break;
		}

		fprintf_s(output, "%02x", c);
	}

	fprintf_s(output, "\n");
	fclose(input);

	if (output != stdout)
		fclose(output);

    return 0;
}

