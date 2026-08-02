#include <idc.idc>

static main() {
	auto search = SEARCH_DOWN | SEARCH_NEXT;
	auto addr = GetFunctionAttr(ScreenEA(), FUNCATTR_START);
	auto func_flags = GetFunctionFlags(addr);
	if (func_flags & FUNC_FRAME) {	// is this an ebp-based frame?
		auto end = GetFunctionAttr(addr, FUNCATTR_END);
		for (; addr < end && addr != BADADDR; addr = FindCode(addr, search)) {
			auto type = GetOpType(addr, 0);
			if (type == 3) {	// is this a register indirect operand?
				if (GetOperandValue(addr, 0) == 4) {	// is the register esp?
					MakeComm(addr, "arg_0");	// [esp] equates to arg_0
				}
			} else if (type == 4) {		// is this a register + displacement operand?
				auto idx = strstr(GetOpnd(addr, 0), "[esp");	// is the register esp?
				if (idx != -1) {
					auto val = GetOperandValue(addr, 0);	// get the displacement
					MakeComm(addr, form("arg_%d", val));	// add a comment
				}
			}
		}
	}
}

