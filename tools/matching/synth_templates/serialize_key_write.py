# bool __thiscall Write(this, Stream* s): s->vf8()->vf6() -> call F(r,&buf,1,0); this->M(s); buf.G(this,A,A); buf.H(s)
PATTERN = 'sub esp, N ; push ebx ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], A ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push esi ; mov ecx, edi ; call EXT ; push A ; push A ; push edi ; lea ecx, [esp + N] ; mov bl, al ; call EXT ; test bl, bl ; je +N ; push esi ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; pop edi ; pop esi ; mov al, N ; pop ebx ; add esp, N ; ret N ; pop edi ; pop esi ; xor al, al ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = '''
struct R { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void *v6(); };
struct S { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual R *v8(); };
struct Buf { unsigned int d[645]; void G(void *o, unsigned a, unsigned b); bool H(S *s); };
void __cdecl FUN_0093aa70(void *r, void *b, int one, int zero);
'''
def emit(va, A, N):
    n = "%08x" % va
    return ('''struct C_%s { bool M(S *s); bool W(S *s); };
bool C_%s::W(S *s) {
    Buf b; unsigned int key; 
    R *r = s->v8();
    void *t = r->v6();
    key = 0x%x;
    FUN_0093aa70(t, (void*)&key, 1, 0);
    bool ok = M(s);
    b.G(this, 0x%x, 0x%x);
    if (ok && b.H(s)) return true;
    return false;
}''' % (n, n, A[0], A[2], A[1])), "?W@C_%s@@QAE_NPAUS@@@Z" % n
