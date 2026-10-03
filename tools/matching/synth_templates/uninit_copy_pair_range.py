# uninitialized_copy of range of {int first; T second;} : copy first, call copy-ctor on second.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; lea ecx, [esi + N] ; push ecx ; lea ecx, [edi + N] ; mov dword ptr [edi], eax ; call EXT ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "#include <new>\n"
def emit(va, A, N):
    off, stride = N[3], N[5]
    sym = "?FUN_%08x@@YAPAUEl_%08x@@PAU1@00@Z" % (va, va)
    src = """struct In_%(v)08x { unsigned pad[%(n)d]; void init(const In_%(v)08x&); };
struct El_%(v)08x { unsigned a; %(pre)sIn_%(v)08x b; };
El_%(v)08x* FUN_%(v)08x(El_%(v)08x* f, El_%(v)08x* l, El_%(v)08x* d) {
    for (; f != l; ++f, ++d) { d->a = f->a; d->b.init(f->b); }
    return d;
}""" % dict(v=va, n=(stride - off) // 4, pre=("unsigned pre[%d]; " % ((off - 4) // 4)) if off > 4 else "")
    return src, sym
