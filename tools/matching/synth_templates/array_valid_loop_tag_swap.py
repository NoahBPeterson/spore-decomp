# Loop over a global array of 0x3c-byte records: while (rec.valid()) { save/patch tag at +0x18, ok = ok && rec.f(a, rec.first); restore }.
# The first valid() call uses one extern symbol, the loop pointer a second extern (unrelated to the compiler), which
# gives the original partial prologue (esi loaded after the first call). Shape-equivalent: both externs are unresolved.
PATTERN = 'push ebx ; mov ecx, A ; mov bl, N ; call EXT ; test al, al ; je +N ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, A ; lea ecx, [ecx] ; mov edi, dword ptr [esi] ; test edi, edi ; jne +N ; mov eax, dword ptr [esp + N] ; mov dword ptr [esi], eax ; mov eax, dword ptr [esi - N] ; lea ecx, [esi - N] ; test bl, bl ; je +N ; push eax ; push ebp ; call EXT ; test al, al ; je +N ; mov bl, N ; jmp +N ; xor bl, bl ; mov dword ptr [esi], edi ; add esi, N ; lea ecx, [esi - N] ; call EXT ; test al, al ; jne +N ; pop edi ; pop esi ; pop ebp ; mov al, bl ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Rec { int first; int pad[5]; int *tag; int pad2[8]; bool valid(); bool f(int a, int b); };
"""
def emit(va, A, N):
    src = ("extern Rec ga_%08x[];\nextern int *gb_%08x[];\n"
           "bool FUN_%08x(int a, int b, int *c) {\n"
           "  bool ok = true;\n"
           "  if (ga_%08x[0].valid()) {\n"
           "    int **t = gb_%08x;\n"
           "    do {\n"
           "      int *saved = *t;\n"
           "      if (!saved) *t = c;\n"
           "      Rec *p = (Rec *)(t - 6);\n"
           "      int first = p->first;\n"
           "      ok = ok && p->f(a, first);\n"
           "      *t = saved;\n"
           "      t += 15;\n"
           "    } while (((Rec *)(t - 6))->valid());\n"
           "  }\n  return ok;\n}") % ((va,) * 5)
    return src, "?FUN_%08x@@YA_NHHPAH@Z" % va
