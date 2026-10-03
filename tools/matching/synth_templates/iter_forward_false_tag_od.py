# Unoptimized (/Od /Ob1) EASTL-style wrapper: iterator-by-value + const key& forwarded to a member with an
# extra empty tag argument (false_type). The empty struct passed by value is the 1-byte temp
# (xor eax,eax; mov [ebp-1],al; movzx ecx,[ebp-1]; push ecx) that gives this pattern.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; xor eax, eax ; mov byte ptr [ebp - N], al ; movzx ecx, byte ptr [ebp - N] ; push ecx ; mov edx, dword ptr [ebp + N] ; push edx ; push ecx ; mov ecx, esp ; lea eax, [ebp + N] ; push eax ; call EXT ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov eax, dword ptr [ebp + N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct It { void* p; It(const It&); };
struct K { int k; };
struct Ft {};
"""
def emit(va, A, N):
    return ("struct S_%08x { It g(It, const K&, Ft); It FUN_%08x(It pos, const K& k); };\n"
            "It S_%08x::FUN_%08x(It pos, const K& k) { return g(pos, k, Ft()); }" % (va, va, va, va),
            "?FUN_%08x@S_%08x@@QAE?AUIt@@U2@ABUK@@@Z" % (va, va))
