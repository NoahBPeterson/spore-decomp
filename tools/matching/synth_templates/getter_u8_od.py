# Byte getter at member offset in an unoptimized (/Od /Ob1) module: return this->b;
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov al, byte ptr [eax + N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[-1]
    return ("struct S_%08x { char pad[%d]; unsigned char b; unsigned char get(); };\n"
            "unsigned char S_%08x::get() { return b; }" % (va, off, va),
            "?get@S_%08x@@QAEEXZ" % va)
