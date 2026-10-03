# if type is T or 0x10: (flags&0x30 ? *this : type ? this : 0) else tail-call helper
PATTERN = 'movzx eax, word ptr [ecx + N] ; cmp ax, N ; je +N ; cmp ax, N ; je +N ; jmp EXT ; test byte ptr [ecx + N], N ; je +N ; mov eax, dword ptr [ecx] ; ret  ; movzx eax, ax ; neg eax ; sbb eax, eax ; and eax, ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct S { unsigned a; unsigned b; unsigned c; unsigned d; unsigned flags; unsigned short type; };
"""
def emit(va, A, N):
    t, fl = N[1], N[4]
    src = """struct S%08x { void* p; int pad[3]; unsigned char fl; char pad2; unsigned short type; };
void* __fastcall ext_%08x(S%08x*);
void* __fastcall FUN_%08x(S%08x* s) {
    unsigned short t = s->type;
    if (t != 0x%x && t != 0x10) return ext_%08x(s);
    if (s->fl & 0x%x) return s->p;
    return t ? s : 0;
}""" % (va, va, va, va, va, t, va, fl)
    return src, "?FUN_%08x@@YIPAXPAUS%08x@@@Z" % (va, va)
