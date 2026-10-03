# class T : Base { T(int x) : Base(Tmp(x)) {} } where Tmp is a 56-byte polymorphic temporary
# {V v1; V v2; int z[8]} with out-of-line dtor, and Base has an out-of-line ctor(const Tmp&) and dtor.
# EH states: Tmp alive = 0, Base alive after temp destroyed = 2 (state 1 store is dead).
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; sub esp, N ; xor eax, eax ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; mov edx, A ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], eax ; lea eax, [esp + N] ; push eax ; mov ecx, esi ; call EXT ; lea ecx, [esp + N] ; mov byte ptr [esp + N], N ; call EXT ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = """struct V { virtual void f(); int a; int b; V(int x):a(0),b(x){} };
struct Tmp { V v1; V v2; int z[8]; Tmp(int x):v1(x),v2(x){ for(int i=0;i<8;i++) z[i]=0; } ~Tmp(); };
struct Base { Base(const Tmp&); ~Base(); int q; };
"""
def emit(va, A, N):
    c = "T_%08x" % va
    src = "struct %s : Base { %s(int x); };\n%s::%s(int x) : Base(Tmp(x)) {}" % (c, c, c, c)
    return src, "??0%s@@QAE@H@Z" % c
