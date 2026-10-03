# Range helper: if (last-first > 1) { tmp = alloc(n*4,"name",0,0,file,line); zero-fill n ints; helper(first,last,tmp,arg); free(tmp); }
import re
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; mov ebp, dword ptr [esp + N] ; mov eax, ebx ; sub eax, ebp ; sar eax, N ; cmp eax, N ; jle +N ; push esi ; push edi ; push N ; push A ; push N ; push N ; lea edi, [eax*N] ; push A ; push edi ; call EXT ; mov esi, eax ; lea ecx, [edi + esi] ; add esp, N ; cmp esi, ecx ; je +N ; mov dword ptr [eax], N ; add eax, N ; cmp eax, ecx ; jne +N ; mov eax, dword ptr [esp + N] ; push eax ; push esi ; push ebx ; push ebp ; call EXT ; push esi ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def _cstr(pe, va):
    d = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, 300)
    return d.split(b"\0")[0].decode("latin1").replace("\\", "\\\\").replace('"', '\\"')
def emit(va, A, N):
    from synth import pe, bounds, load_funcs
    import capstone
    starts, _ = load_funcs()
    ins = list(capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(bounds(va, starts), va))
    calls = [int(i.op_str, 16) for i in ins if i.mnemonic == "call"]
    pushes = [i for i in ins if i.mnemonic == "push" and i.op_str.startswith("0x")]
    line = int(pushes[0].op_str, 16)
    file_ = int(pushes[1].op_str, 16)
    name = int(pushes[2].op_str, 16)
    src = """extern void* __cdecl alloc_%(v)08x(unsigned, const char*, int, int, const char*, int);
extern void __cdecl free_%(v)08x(void*);
extern void __cdecl help_%(v)08x(int*, int*, int*, int);
void __cdecl FUN_%(v)08x(int* first, int* last, int, int arg) {
    int n = last - first;
    if (n > 1) {
        int* buf = (int*)alloc_%(v)08x(n * 4, "%(name)s", 0, 0, "%(file)s", %(line)d);
        for (int* p = buf; p != buf + n; ++p) *p = 0;
        help_%(v)08x(first, last, buf, arg);
        free_%(v)08x(buf);
    }
}""" % dict(v=va, name=_cstr(pe, name), file=_cstr(pe, file_), line=line)
    return src, "?FUN_%08x@@YAXPAH0HH@Z" % va
