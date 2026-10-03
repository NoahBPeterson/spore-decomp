# Stream-read method: vcall chain on stream, Fa(p,&a4,1,0), two bool member calls (second on a member at +N),
# then a 0xa14-byte scope local constructed from (this, name, id), finalized with the stream if both succeeded.
# Needs /GS- (no cookie); the vcall result is held in a local so it is evaluated before the push of 0,1.
PATTERN = 'sub esp, N ; push ebx ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push esi ; mov ecx, edi ; call EXT ; test al, al ; je +N ; push esi ; lea ecx, [edi + N] ; call EXT ; test al, al ; je +N ; mov bl, N ; jmp +N ; xor bl, bl ; push A ; push A ; push edi ; lea ecx, [esp + N] ; call EXT ; test bl, bl ; je +N ; push esi ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; mov al, N ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = """struct Obj { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void* get(); };
struct Stream { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual Obj* get(); };
struct A4 { int x; };
void __cdecl Fa(void*, A4*, int, int);
struct Big { char pad[0xa14]; Big(void* o, const void* n, const void* id); void fin(Stream*); };
struct M { bool m(Stream*); };
"""
def emit(va, A, N):
    t = "T_%08x" % va
    src = ("extern char g_%08x[], g_%08x[];\n"
           "struct %s { char pad0[0x%x]; M mm; bool A_(Stream*); bool read_%08x(Stream* s); };\n"
           "bool %s::read_%08x(Stream* s) {\n  A4 a;\n  void* p = s->get()->get();\n  Fa(p, &a, 1, 0);\n"
           "  bool ok = A_(s) && mm.m(s);\n  Big b(this, g_%08x, g_%08x);\n  if (ok) b.fin(s);\n  return true;\n}\n"
           % (A[1], A[0], t, N[8], va, t, va, A[1], A[0]))
    return src, "?read_%08x@%s@@QAE_NPAUStream@@@Z" % (va, t)
