#include <idc.idc>

static list_callers(name) {
	auto func = LocByName(name);
	if (func == BADADDR) {
		Warning("Sorry, %s not found in database", name);
	} else {
		auto addr;
		for (addr = RfirstB(func); addr != BADADDR; addr = RnextB(func, addr)) {
			auto xref = XrefType();
			if (xref == fl_CN || xref == fl_CF) {
				auto source = GetFunctionName(addr);
				Message("%s is called from %x in %s\n", name, addr, source);
			}
		}
	}
}

static main() {
	list_callers("_strcpy");
	list_callers("_sprintf");
	return 0;
}

