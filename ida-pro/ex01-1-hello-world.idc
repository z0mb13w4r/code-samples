#include <idc.idc>

static main()
{
	if (ARGV.count < 3)
		Message("Hello world from IDC!\n");
	else
		Message("Hello world from IDC: %s %s %s\n", ARGV[0], ARGV[1], ARGV[2]);

	Message("EXE: %s\n", get_input_file_path());

	return 0;
}