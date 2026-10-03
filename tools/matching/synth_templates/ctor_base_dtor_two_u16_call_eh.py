# EH ctor: class D : B (B has dtor, 0x10 bytes) { u16 a,b; D(arg) { a=..; b=..; Set(arg); } }
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push esi ; mov esi, ecx ; mov dword ptr [esp + N], esi ; mov edx, dword ptr [esp + N] ; mov ecx, N ; mov eax, N ; mov word ptr [esi + N], cx ; push edx ; mov ecx, esi ; mov dword ptr [esp + N], N ; mov word ptr [esi + N], ax ; call EXT ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    c = "C_" + t
    src = ("struct B_%s { unsigned pad[4]; ~B_%s(); };\n"
           "struct %s : B_%s { unsigned short a, b; void Set(unsigned); %s(unsigned x); };\n"
           "%s::%s(unsigned x) { b = %d; a = %d; Set(x); }") % (t, t, c, t, c, c, c, N[6], N[5])
    return src, "??0%s@@QAE@I@Z" % c
