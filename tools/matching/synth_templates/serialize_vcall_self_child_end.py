# Serialize-style member: void C::S(Stream* s) { s->v1("Name",1,this); s->v3("Child",1,this->field); s->v6(); }
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; push edi ; mov edi, ecx ; push edi ; push N ; push A ; mov ecx, esi ; call dword ptr [eax + N] ; mov eax, dword ptr [edi + N] ; mov edx, dword ptr [esi] ; push eax ; push N ; push A ; mov ecx, esi ; call dword ptr [edx + N] ; mov edx, dword ptr [esi] ; mov ecx, esi ; call dword ptr [edx + N] ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/Os", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = '''
struct Stream { virtual void v0(); virtual void F1(const char *n, int k, void *p); virtual void v2();
  virtual void F3(const char *n, int k, void *p); virtual void v4(); virtual void v5(); virtual void End(); };
'''
def emit(va, A, N):
    n = "%08x" % va
    off = [x for x in N if x in (0xc, 0x10, 0x14, 0x8, 0x18, 0x1c, 0x20)]
    return ('''extern const char g_%08x[];
extern const char g_%08x[];
struct C_%s { char pad[%d]; void *child; void S(Stream *s); };
void C_%s::S(Stream *s) {
    s->F1(g_%08x, 1, this);
    s->F3(g_%08x, 1, child ? child : 0);
    s->End();
}''' % (A[0], A[1], n, N[2], n, A[0], A[1])), "?S@C_%s@@QAEXPAUStream@@@Z" % n
