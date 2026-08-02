#include <idc.idc>

static save_asm(name)
{
	auto fp = fopen(name, "w");
	if (fp)
	{
		gen_file(OFILE_ASM, fp, 0, 0, GENFLG_ASMTYPE);
		fclose(fp);
	}
}

static main()
{
	auto FALSE = 0;
	auto TRUE  = 1;

	ARGV.count = 3;
	ARGV[1] = "--george";
	ARGV[2] = "--ursula";
	ARGV[3] = "--exit";

	auto closedown = FALSE;

	if (ARGV.count < 2)
	{
	}
	else
	{
		auto i;
		for (i = 0; i < ARGV.count; i = i + 1)
		{
			if (strlen(ARGV[i]) < 3)
				continue;

			if (ARGV[i][0:2] != "--")
				continue;

			if (ARGV[i][2:] == "george")
				print("Watch out for that tree!");

			if (ARGV[i][2:] == "exit")
				closedown = TRUE;
		}
	}

	Message("EXE: %s\n", get_input_file_path());

	auto name = get_input_file_path() + ".txt";

	save_asm(name);

	if (closedown)
		Exit(0); // Exit IDA Pro

	
	return 0;
}
