# Hinted unique insert: lower_bound in [first,pos) or [pos,end), then insert if not equal.
PATTERN = 'mov eax, dword ptr [esp + N] ; push ebx ; push esi ; mov esi, ecx ; mov ebx, dword ptr [esi + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp eax, ebx ; je +N ; mov ecx, dword ptr [edi] ; cmp ecx, dword ptr [eax] ; jae +N ; movzx edx, byte ptr [esi + N] ; push edx ; push edi ; push eax ; mov eax, dword ptr [esi] ; jmp +N ; movzx ecx, byte ptr [esi + N] ; push ecx ; push edi ; push ebx ; push eax ; call EXT ; add esp, N ; cmp eax, ebx ; je +N ; mov edx, dword ptr [edi] ; cmp edx, dword ptr [eax] ; jae +N ; push edi ; push eax ; mov ecx, esi ; call EXT ; pop edi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = max(N)
    s = """typedef unsigned U;
struct C_%08x {
    U* first; U* last; char pad[%d]; bool flag;
    void ins(U* p, const U* k);
    void f(U* pos, const U* key);
};
U* __cdecl lb_%08x(U* a, U* b, const U* k, bool f);
void C_%08x::f(U* pos, const U* key) {
    U* e = last;
    U* r;
    if (pos != e && *key < *pos) r = lb_%08x(first, pos, key, flag);
    else r = lb_%08x(pos, e, key, flag);
    if (r == e || *key < *r) ins(r, key);
}""" % (va, off - 8, va, va, va, va)
    return s, "?f@C_%08x@@QAEXPAIPBI@Z" % va
