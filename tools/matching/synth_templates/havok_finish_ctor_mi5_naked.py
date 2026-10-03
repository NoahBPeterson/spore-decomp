# Havok-style finish-loaded placement ctor of a class with four secondary polymorphic bases (+8..+0x14):
#   if (p) { refcount(int16 @+6)=1; base vptrs @+8..+0x14 (shared); final vptrs @+0,+8..+0x14 }
# Same imm16 store as hk_finish_ctor_naked: cl 15 always hoists the constant into cx
# (mov ecx,1; mov word ptr [eax+6],cx) for every flag/source shape tried (inline MI ctors with
# placement new, /O1 /Os /Ox /Ob2, volatile, bitfield, base-class body assignment), so prebuilt
# Havok code from another compiler build is assumed; emitted as naked inline asm.
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; mov word ptr [eax + N], N ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; mov dword ptr [eax], A ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    v = ["g_%08x" % a for a in A]
    s = "".join('extern "C" const void* %s;\n' % n for n in dict.fromkeys(v))
    s += "__declspec(naked) void FUN_%08x(void* p) {\n    __asm {\n" % va
    s += "        mov eax, dword ptr [esp + 4]\n        test eax, eax\n        je done\n"
    s += "        mov word ptr [eax + 6], 1\n"
    offs = [8, 0xc, 0x10, 0x14]
    for o, n in zip(offs, v[0:4]):
        s += "        mov dword ptr [eax + %d], offset %s\n" % (o, n)
    s += "        mov dword ptr [eax], offset %s\n" % v[4]
    for o, n in zip(offs, v[5:9]):
        s += "        mov dword ptr [eax + %d], offset %s\n" % (o, n)
    s += "    done:\n        ret\n    }\n}"
    return s, "?FUN_%08x@@YAXPAX@Z" % va
