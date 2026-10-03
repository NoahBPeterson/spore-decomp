# Unoptimized (/Od /Ob1) factory returning pr<unsigned,O*> by value (hidden ret ptr), pr has a user copy ctor:
#   P f() { return mk6(KEY, new("OTDB",0,0,0,0) O); }   // template mk6(T1 a,T2 b){ pr<T1,T2> r(a,b); return r; }
# A order: name str, base vptr, derived vptr, key. (The template form matters; a plain inline fn does not match.)
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; mov dword ptr [ebp - N], eax ; cmp dword ptr [ebp - N], N ; je +N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax], A ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx], A ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; jmp +N ; mov dword ptr [ebp - N], N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov dword ptr [ebp - N], A ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [eax], ecx ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [ebp - N] ; mov dword ptr [edx + N], eax ; mov eax, dword ptr [ebp + N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int a, int b, int c, int d);\n"
           "struct B { virtual void fb(); };\n"
           "struct O : B { virtual void fb(); };\n"
           "template<class T1,class T2> struct pr { T1 first; T2 second; pr(const T1& a,const T2& b):first(a),second(b){} pr(const pr& o):first(o.first),second(o.second){} };\n"
           "template<class T1,class T2> inline pr<T1,T2> mk6(T1 a, T2 b){ pr<T1,T2> r(a,b); return r; }\n")

def emit(va, A, N):
    src = ("pr<unsigned,O*> FUN_%08x() { return mk6(0x%08xu, (O*)new(\"OTDB\", 0, 0, 0, 0) O); }" % (va, A[3]))
    return src, "?FUN_%08x@@YA?AU?$pr@IPAUO@@@@XZ" % va
