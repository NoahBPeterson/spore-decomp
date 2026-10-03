# EASTL-style introsort_loop(first,last,depth,cmp) over 4-byte intrusive smart pointers (copy ctor AddRefs via
# vtable slot 0), empty comparator by value (4-byte slot), /O2 (no SSE). Median takes cmp too, nested inside partition's args.
import os
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, edi ; sub eax, ebx ; and eax, A ; cmp eax, N ; jle +N ; lea esp, [esp] ; test ebp, ebp ; jle +N ; mov ecx, dword ptr [esp + N] ; push ecx ; mov edx, ecx ; push edx ; lea eax, [edi - N] ; push eax ; mov eax, edi ; sub eax, ebx ; sar eax, N ; cdq  ; sub eax, edx ; sar eax, N ; lea ecx, [ebx + eax*N] ; push ecx ; push ebx ; call EXT ; mov ecx, dword ptr [eax] ; add esp, N ; mov edx, esp ; mov dword ptr [edx], ecx ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx] ; call eax ; push edi ; push ebx ; call EXT ; mov ecx, dword ptr [esp + N] ; push ecx ; dec ebp ; push ebp ; mov esi, eax ; push edi ; push esi ; call +N ; mov edi, esi ; sub esi, ebx ; and esi, A ; add esp, N ; cmp esi, N ; jg +N ; test ebp, ebp ; jne +N ; mov edx, dword ptr [esp + N] ; push edx ; push edi ; push edi ; push ebx ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct C {};\n"
           "struct Obj { virtual void AddRef(); };\n"
           "struct P { Obj* p; P(const P& o) : p(o.p) { if (p) p->AddRef(); } };\n")

def _calls(va):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    code = _pe.get_data(va - _base, 152)
    out = []
    for i in md.disasm(code, va):
        if i.mnemonic == "call" and i.op_str.startswith("0x") and int(i.op_str, 0) != va:
            out.append(int(i.op_str, 0))
    return out

def emit(va, A, N):
    c = _calls(va)
    med, part, hs = c[0], c[1], c[2]
    f = "FUN_%08x"
    src = ("P* %s(P*, P*, P*, C);\n"
           "P* %s(P*, P*, P, C);\n"
           "void %s(P*, P*, P*, C);\n"
           "void FUN_%08x(P* first, P* last, int depth, C cmp) {\n"
           "    while (last - first > 28 && depth > 0) {\n"
           "        P* cut = %s(first, last, *%s(first, first + (last - first) / 2, last - 1, cmp), cmp);\n"
           "        --depth;\n"
           "        FUN_%08x(cut, last, depth, cmp);\n"
           "        last = cut;\n"
           "    }\n"
           "    if (depth == 0) %s(first, last, last, cmp);\n}\n") % (
               f % med, f % part, f % hs, va, f % part, f % med, va, f % hs)
    return src, "?FUN_%08x@@YAXPAUP@@0HUC@@@Z" % va
