# Vector push_back(const T&): if (mEnd < mCap) new(mEnd++) T(arg) else realloc_insert(mEnd, arg).
# Old-style inline EH prolog (/GS-), placement new + matching delete gives EH state 0 during the ctor.
PATTERN = 'mov eax, dword ptr fs:[N] ; push -N ; push A ; push eax ; mov dword ptr fs:[N], esp ; mov eax, dword ptr [ecx + N] ; sub esp, N ; cmp eax, dword ptr [ecx + N] ; jae +N ; lea edx, [eax + N] ; mov dword ptr [esp], eax ; mov dword ptr [ecx + N], edx ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; push ecx ; mov ecx, eax ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N ; mov edx, dword ptr [esp + N] ; push edx ; push eax ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\ninline void operator delete(void*, void*) {}\n"
def emit(va, A, N):
    size = N[6]
    t = "T_%08x" % va
    v = "V_%08x" % va
    src = ("struct %s { char d[%d]; %s(int); };\n"
           "struct %s { int* b; %s* e; %s* c; void ins(%s*, int); void push(int a); };\n"
           "void %s::push(int a) {\n  if (e < c) { new (e++) %s(a); } else ins(e, a);\n}\n"
           ) % (t, size, t, v, t, t, t, v, t)
    return src, "?push@%s@@QAEXH@Z" % v
