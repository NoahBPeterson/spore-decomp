# Member swap of a 20-byte container (3 swapped ptrs + 2 untouched dwords) with a refcount-at-[p-4]==0
# "locked" check: fast path swaps fields via a template swap, slow path copy-ctor temp + 2 assigns + dtor.
# Callee declarations are throw() so no EH frame is emitted. Real class name unknown.
PATTERN = 'sub esp, N ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi] ; push edi ; mov edi, dword ptr [esp + N] ; test ecx, ecx ; je +N ; cmp dword ptr [ecx - N], N ; je +N ; mov eax, dword ptr [edi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; jne +N ; push esi ; lea ecx, [esp + N] ; call EXT ; push edi ; mov ecx, esi ; call EXT ; lea eax, [esp + N] ; push eax ; mov ecx, edi ; call EXT ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; add esp, N ; ret N ; mov dword ptr [esi], eax ; mov dword ptr [edi], ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [edi + N] ; mov dword ptr [esi + N], ecx ; mov dword ptr [edi + N], eax ; mov edx, dword ptr [edi + N] ; mov eax, dword ptr [esi + N] ; mov dword ptr [esi + N], edx ; mov dword ptr [edi + N], eax ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "template<class T> inline void sw(T& a, T& b){ T t(a); a=b; b=t; }\n"
def emit(va, A, N):
    s = "V_%08x" % va
    src = ("struct %(s)s {\n int *p; int *b; int *c; int d; int e;\n"
           " %(s)s(const %(s)s&) throw();\n %(s)s& assign(const %(s)s&) throw();\n ~%(s)s() throw();\n"
           " void swap(%(s)s& o) throw();\n};\n"
           "void %(s)s::swap(%(s)s& o) throw() {\n"
           "  if (!((p && p[-1]==0) || (o.p && o.p[-1]==0))) {\n"
           "    sw(p,o.p); sw(b,o.b); sw(c,o.c);\n"
           "  } else {\n    %(s)s t(*this); assign(o); o.assign(t);\n  }\n}\n") % {"s": s}
    return src, "?swap@%s@@QAEXAAU1@@Z" % s
