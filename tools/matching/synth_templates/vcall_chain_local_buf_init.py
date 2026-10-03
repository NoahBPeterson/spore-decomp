# this-adjusted (this-N) method taking a stream: p->vf8()->vf6() result passed with a 4-byte out local to a
# cdecl helper, then a 2580-byte local is constructed (thiscall, this-N, &global, imm) and finished with 1 arg.
# Frame: sub esp,0xa18; locals out@+0, big@+4. Modeled as __fastcall(self, unused_edx, p) (ecx=this, ret 4).
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push A ; push A ; add edi, -N ; push edi ; lea ecx, [esp + N] ; call EXT ; push esi ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32;
struct Q { virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4(); virtual void q5(); virtual int q6(); };
struct P { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual Q* p8(); };
struct Big { u32 d[645]; void init(void*, const void*, const void*); void fin(P*); };
struct Out { u32 d; };
void __cdecl helper(int, Out*, int, int);
"""
def emit(va, A, N):
    adj = N[8]
    src = ("extern char g_%08x[], g_%08x[];\n"
           "void __fastcall FUN_%08x(char* self, int, P* p) {\n"
           "    Out o; Big b;\n"
           "    int r = p->p8()->q6(); helper(r, &o, 1, 0);\n"
           "    b.init(self - %d, g_%08x, g_%08x);\n"
           "    b.fin(p);\n"
           "}") % (A[0], A[1], va, adj, A[1], A[0])
    return src, "?FUN_%08x@@YIXPADHPAUP@@@Z" % va
