# Out-of-line default ctor of a Simulator::cCreatureAbility-derived class (/O2 /arch:SSE):
#   class X : public IUnknownLike /*novtable, +0*/, public cCreatureAbility /*+4, two novtable
#   interface bases at +4/+8*/ { eastl::string mName /*+0x24*/; int mValue /*+0x34*/; };
# Inlined base ctor writes cCreatureAbility's two vptrs then its fields (int 0, bool true,
# float 0.0f, three zero words); derived then writes its three vptrs, the string
# (begin=end=&gEmptyString, capacity=&gEmptyString+1) and the trailing int. Vtables are relocs.
PATTERN = 'xorps xmm0, xmm0 ; mov eax, ecx ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; xor ecx, ecx ; mov dword ptr [eax + N], ecx ; mov byte ptr [eax + N], N ; movss dword ptr [eax + N], xmm0 ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax], A ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], A ; mov edx, A ; mov dword ptr [eax + N], edx ; mov dword ptr [eax + N], edx ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/GR-"]
PRELUDE = r'''extern char gEmptyString[];
struct ability_allocator { const char* mpName; ability_allocator() {} };
struct ability_string { char* mpBegin; char* mpEnd; char* mpCapacity; ability_allocator mAllocator;
  ability_string() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {} };
struct __declspec(novtable) IAbilityRef { virtual int AddRef() = 0; virtual int Release() = 0; };
struct __declspec(novtable) IAbility1 { virtual void f1() = 0; };
struct __declspec(novtable) IAbility2 { virtual void f2() = 0; };
struct cCreatureAbility : IAbility1, IAbility2 {
  int a; bool b; float c; int d, e, f;
  cCreatureAbility() : a(0), b(true), c(0.0f), d(0), e(0), f(0) {}
  virtual void f1(); virtual void f2();
};
'''
def emit(va, A, N):
    # N[11] = string offset (0x24 + derived fields left uninitialized), N[14] = trailing int offset
    c = "C_%08x" % va
    pre = (N[11] - 0x24) // 4
    gap = (N[14] - N[11] - 0x10) // 4
    pad1 = (" int pad1[%d];" % pre) if pre else ""
    pad2 = (" int pad2[%d];" % gap) if gap else ""
    src = ("struct %(c)s : IAbilityRef, cCreatureAbility {\n"
           " %(pad1)s ability_string s;%(pad2)s int x;\n  %(c)s();\n"
           "  virtual int AddRef(); virtual int Release(); virtual void f1(); virtual void f2();\n};\n"
           "%(c)s::%(c)s() : x(0) {}") % dict(c=c, pad1=pad1, pad2=pad2)
    return src, "??0%s@@QAE@XZ" % c
