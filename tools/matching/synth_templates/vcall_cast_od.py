# p ? p->vfunc3(imm) : 0, cdecl free function, /Od module
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; cmp dword ptr [ebp + N], N ; je +N ; push A ; mov eax, dword ptr [ebp + N] ; mov edx, dword ptr [eax] ; mov ecx, dword ptr [ebp + N] ; mov eax, dword ptr [edx + N] ; call eax ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct IObj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void* Cast(unsigned int t); };\n"
def emit(va, A, N):
    imm = (A + N)[0] if (A or N) else 0
    # first N may be 8 / 0 stack offsets; the immediate is the one that is large
    cands = [x for x in (A + N) if x > 0xff]
    imm = cands[0] if cands else imm
    return ("void* FUN_%08x(IObj* p) { return p ? p->Cast(0x%x) : 0; }" % (va, imm),
            "?FUN_%08x@@YAPAXPAUIObj@@@Z" % va)
