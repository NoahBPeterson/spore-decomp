# this->member.at(idx) = v;  where at(const int&) returns int& (arg passed by address of own stack param)
PATTERN = 'lea eax, [esp + N] ; push eax ; add ecx, N ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax], ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[1]
    src = ("struct M_%08x { int& at(const int&); };\n"
           "struct S_%08x { char p[%d]; M_%08x m; void set(int i, int v); };\n"
           "void S_%08x::set(int i, int v) { m.at(i) = v; }" % (va, va, off, va, va))
    return src, "?set@S_%08x@@QAEXHH@Z" % va
