# ISimulatorSerializable::Write-style member (bool result): scope key stored in a local, helper call,
# then ok = this->P(s) && (this+off)->Q(s); buf.G(this, name, desc); return ok && buf.H(s).
# UNSOLVED: the original stores the key after the v6 vptr/fnptr loads (just before `call eax`);
# every source shape tried stores it right after the v8 call, so 0 instances are byte-exact (otherwise identical).
PATTERN = 'sub esp, N ; push ebx ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], A ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push esi ; mov ecx, edi ; call EXT ; test al, al ; je +N ; push esi ; lea ecx, [edi + N] ; call EXT ; test al, al ; je +N ; mov bl, N ; jmp +N ; xor bl, bl ; push A ; push A ; push edi ; lea ecx, [esp + N] ; call EXT ; test bl, bl ; je +N ; push esi ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; pop edi ; pop esi ; mov al, N ; pop ebx ; add esp, N ; ret N ; pop edi ; pop esi ; xor al, al ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = '''
struct R { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void *v6(); };
struct S { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual R *v8(); };
struct Sub { bool Q(S *s); };
void __cdecl FUN_0093aa70(void *r, void *b, int one, int zero);
'''
def emit(va, A, N):
    n = "%08x" % va
    size = N[0]
    # find the lea ecx,[edi+off] operand: first N after the vtable/stack offsets; scan for a plausible one
    off = [x for x in N if 0 < x < 0x400 and x not in (0x20, 0x18, 0xc, 0x14, 0x1c, 0x10, 1, 0, 4)]
    off = off[0] if off else 0x34
    return ('''struct Buf_%s { unsigned int d[%d]; void G(void *o, unsigned a, unsigned b); bool H(S *s); };
struct C_%s { char pad[%d]; Sub sub; bool P(S *s); bool W(S *s); };
bool C_%s::W(S *s) {
    Buf_%s b; unsigned int key[1];
    R *r = s->v8();
    key[0] = 0x%x;
    void *t = r->v6();
    FUN_0093aa70(t, key, 1, 0);
    bool ok = P(s) && sub.Q(s);
    b.G(this, 0x%x, 0x%x);
    if (ok) { if (b.H(s)) return true; }
    return false;
}''' % (n, (size - 4) // 4, n, off, n, n, A[0], A[2], A[1])), "?W@C_%s@@QAE_NPAUS@@@Z" % n
