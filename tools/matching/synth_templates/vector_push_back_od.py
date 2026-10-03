# /Od eastl-style vector push_back: if (end_ < cap_) new(end_++) T(x); else insert_slow(end_, x);
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [eax + N] ; cmp edx, dword ptr [ecx + N] ; jae +N ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx + N] ; add eax, N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx + N], eax ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; cmp dword ptr [ebp - N], N ; je +N ; mov eax, dword ptr [ebp + N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; jmp +N ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx + N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned, void* p) { return p; }\n"
def emit(va, A, N):
    frame, sz = N[0], N[11]
    pd = frame - 20
    pad = ("char pad[%d]; " % pd) if pd > 0 else ""
    t = "T_%08x" % va
    c = "V_%08x" % va
    src = ("struct %s { char d[%d]; %s(const int& a); };\n"
           "struct %s { int x; %s* last; %s* cap;\n"
           "  void ins(%s* p, const int& a);\n"
           "  void f(const int& a);\n};\n"
           "void %s::f(const int& a) {\n"
           "    if (last < cap) { new(last++) %s(a); }\n"
           "    else ins(last, a);\n    %s\n}\n") % (t, sz, t, c, t, t, t, c, t, pad)
    return src, "?f@%s@@QAEXABH@Z" % c
