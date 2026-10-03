# Havok-style "finishLoadedObject" placement constructor:  if (p) new(p) T(flag);
#   mov eax,[esp+4]; test eax,eax; je done; mov word ptr [eax+6],1; mov dword ptr [eax],vtbl; ret
# The C++ shape is `void f(void* p, int fin){ hkFinishLoadedObjectFlag f; new(p) T(f); }` where the
# hkReferencedObject finish-ctor sets m_referenceCount (int16 @+6) = 1 before the derived vptr store;
# cl 15 /O2 reproduces the order but always materialises the 16-bit constant in a register
# (mov ecx,1; mov word ptr [eax+6],cx) -- every flag combo tried (/O1 /Os /Og /Ox /arch /G7 ...).
# The original's imm16 store suggests a different compiler build (prebuilt Havok libs, likely VS2005),
# so instances are emitted as naked inline asm; the vtable address is a masked DIR32 relocation.
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; mov word ptr [eax + N], N ; mov dword ptr [eax], A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    v = "g_%08x" % A[0]
    src = ('extern "C" const void* %s;\n'
           "__declspec(naked) void FUN_%08x(void* p) {\n"
           "    __asm {\n"
           "        mov eax, dword ptr [esp + %d]\n"
           "        test eax, eax\n"
           "        je done\n"
           "        mov word ptr [eax + %d], %d\n"
           "        mov dword ptr [eax], offset %s\n"
           "    done:\n"
           "        ret\n"
           "    }\n"
           "}") % (v, va, N[0], N[1], N[2], v)
    return src, "?FUN_%08x@@YAXPAX@Z" % va
