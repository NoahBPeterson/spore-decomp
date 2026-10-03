# Hash-bucket iterator walk (begin..end over bucket array, node->next at offset K), returns true.
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [edx] ; mov ecx, edx ; test eax, eax ; jne +N ; cmp dword ptr [edx + N], eax ; lea ecx, [edx + N] ; jne +N ; add ecx, N ; cmp dword ptr [ecx], N ; je +N ; mov eax, dword ptr [ecx] ; mov esi, dword ptr [esi + N] ; mov edx, dword ptr [edx + esi*N] ; pop esi ; cmp eax, edx ; je +N ; lea ecx, [ecx] ; mov eax, dword ptr [eax + N] ; test eax, eax ; jne +N ; mov eax, dword ptr [ecx + N] ; add ecx, N ; test eax, eax ; je +N ; cmp eax, edx ; jne +N ; mov al, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    # operand order: esp+0xc, esi+4, edx+4 (x3), ..., esi+8, ... eax+K ...
    k = [n for n in N if n not in (0,)]
    # K is the immediate of 'mov eax,[eax+K]': find by index from the end
    # N list (non-zero order): 0xc,4,4,4,4,8,4,K,4,4,... pick index 7 of full list
    K = N[N.index(8) + 2] if 8 in N else 4
    src = """struct Node%(v)08x { int pad[%(w)d]; Node%(v)08x* next; };
struct T%(v)08x { int a; Node%(v)08x** b; int n; };
bool FUN_%(v)08x(int, T%(v)08x* t) {
    Node%(v)08x** b = t->b;
    Node%(v)08x** p = b;
    Node%(v)08x* cur = *p;
    if (!cur) { p = b + 1; if (!*p) { do ++p; while (!*p); } cur = *p; }
    Node%(v)08x* end = b[t->n];
    while (cur != end) {
        cur = cur->next;
        while (!cur) { ++p; cur = *p; }
    }
    return true;
}""" % dict(v=va, w=K // 4)
    return src, "?FUN_%08x@@YA_NHPAUT%08x@@@Z" % (va, va)
