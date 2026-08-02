#include <idc.idc>

static main() {
	auto flags = SEARCH_DOWN | SEARCH_NEXT;
	auto func = GetFunctionAttr(ScreenEA(), FUNCATTR_START);
	if (func != -1) {
		auto name = Name(func);
		auto end = GetFunctionAttr(func, FUNCATTR_END);
		auto inst;
		for (inst = func; inst < end; inst = FindCode(inst, flags)) {
			auto target;
			for (target = Rfirst(inst); target != BADADDR; target = Rnext(inst, target)) {
				auto xref = XrefType();
				if (xref == fl_CN || xref == fl_CF) {
					Message("%s calls %s from 0x%x\n", name, Name(target), inst);
				}
			}
		}
	} else {
		Warning("No functions found at location %x\n", ScreenEA());
	}
}

