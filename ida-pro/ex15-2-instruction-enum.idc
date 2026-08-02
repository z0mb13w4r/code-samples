#include <idc.idc>

static main() {
	auto func = GetFunctionAttr(ScreenEA(), FUNCATTR_START);
	if (func != -1) {
		auto end = GetFunctionAttr(func, FUNCATTR_END);
		auto count = 0;
		auto inst = func;
		while (inst < end) {
			count++;
			inst = FindCode(inst, SEARCH_DOWN | SEARCH_NEXT);
		}
		Warning("%s contains %d instruction\n", Name(func), count);
	} else {
		Warning("No function found at location %x\n", ScreenEA());
	}
}

