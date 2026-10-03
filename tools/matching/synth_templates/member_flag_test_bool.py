# bool test of (this->field & mask) != 0, thiscall, ret 4
PATTERN = "mov eax, dword ptr [ecx + N] ; and eax, dword ptr [esp + N] ; neg eax ; sbb eax, eax ; neg eax ; ret N"
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    pad = "char pad[%d]; " % off if off else ""
    src = "struct C_%08x { %sunsigned m; bool FUN_%08x(unsigned mask) { return (m & mask) != 0; } };\nbool dummy_%08x(C_%08x* c) { return c->FUN_%08x(1); }" % (va, pad, va, va, va, va)
    # keep method out-of-line symbol via explicit definition below
    src = "struct C_%08x { %sunsigned m; bool FUN_%08x(unsigned mask); };\nbool C_%08x::FUN_%08x(unsigned mask) { return (m & mask) != 0; }" % (va, pad, va, va, va)
    return src, "?FUN_%08x@C_%08x@@QAE_NI@Z" % (va, va)
