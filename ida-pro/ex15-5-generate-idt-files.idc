#include <idc.idc>

static main() {
	auto fname = AskFile(1, "*.idt", "Select IDT save file");
	auto fp = fopen(fname, "w");
	auto entryPoints = GetEntryPointQty();
	fprintf(fp, "ALIGNMENT 4\n");
	fprintf(fp, "0 Name=%s\n", GetInputFile());
	auto i;
	for (i = 0; i < entryPoints; i = i + 1) {
		auto ord = GetEntryOrdinal(i);
		if (ord == 0) continue;
		auto addr = GetEntryPoint(ord);
		if (ord == addr) {
			continue;
		}

		auto name = Name(addr);
		fprintf(fp, "%d Name=%s", ord, name);
		auto purged = GetFunctionAttr(addr, FUNCATTR_ARGSIZE);
		if (purged > 0) {
			fprintf(fp, " Pascal=%d", purged);
		}
		fprintf(fp, "\n");
	}
}

