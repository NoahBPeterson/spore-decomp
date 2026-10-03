# bool f(S* s, T* v) { if (s && v) { s->field = v; return true; } return false; }  cdecl
PATTERN = 'mov edx, dword ptr [esp + N] ; xor al, al ; test edx, edx ; je +N ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov dword ptr [edx + N], ecx ; mov al, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[2]
    src = ("struct S_%08x { char p[%d]; void* f; };\n"
           "bool FUN_%08x(S_%08x* s, void* v) {\n"
           "  bool r = false;\n"
           "  if (s && v) { s->f = v; r = true; }\n"
           "  return r;\n}") % (va, off, va, va)
    return src, "?FUN_%08x@@YA_NPAUS_%08x@@PAX@Z" % (va, va)
