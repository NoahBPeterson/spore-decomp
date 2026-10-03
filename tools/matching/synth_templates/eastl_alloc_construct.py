# Stdcall(n, a, b) wrapper: allocate n*elemsize via EASTL allocator (null if n==0), then call 5-arg cdecl init(&n,a,b,ptr,n).
import re
PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; test eax, eax ; je +N ; push N ; push A ; push N ; lea eax, [eax + eax*N] ; push N ; add eax, eax ; add eax, eax ; push A ; push eax ; call EXT ; add esp, N ; mov esi, eax ; jmp +N ; xor esi, esi ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push ecx ; push esi ; push edx ; push eax ; lea ecx, [esp + N] ; push ecx ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def _cstr(pe, va):
    d = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, 300)
    t = d.split(b"\0")[0].decode("latin1")
    return t.replace("\\", "\\\\").replace('"', '\\"')
def emit(va, A, N):
    from synth import pe, bounds, load_funcs
    import capstone
    starts, _ = load_funcs()
    code = bounds(va, starts)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    ins = list(md.disasm(code, va))
    calls = [int(i.op_str, 16) for i in ins if i.mnemonic == "call"]
    lea = next(i for i in ins if i.mnemonic == "lea")
    mul = (int(re.search(r"\*(\d)", lea.op_str).group(1)) + 1) * 4
    pushes = [i for i in ins if i.mnemonic == "push" and i.op_str.startswith("0x")]
    line = int(pushes[0].op_str, 16)
    file_ = int(pushes[1].op_str, 16)
    name = int(pushes[2].op_str, 16)
    src = """extern void* __cdecl alloc_%08x(unsigned, const char*, int, int, const char*, int);
extern void __cdecl init_%08x(int*, int, int, void*, int);
void* __stdcall FUN_%08x(int n, int a, int b) {
    void* p = n ? alloc_%08x(n * %d, "%s", 0, 0, "%s", %d) : 0;
    init_%08x(&n, a, b, p, *(volatile int*)&n);
    return p;
}""" % (va, va, va, va, mul, _cstr(pe, name), _cstr(pe, file_), line, va)
    return src, "?FUN_%08x@@YGPAXHHH@Z" % va
