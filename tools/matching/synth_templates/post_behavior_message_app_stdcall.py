# Free stdcall(a, b): allocate an "App" UI::BehaviorMessage (inlined ctor chain, interlocked refcount init),
# AddRef via vcall, set id (+0x30) and +8 = b, post via singleton GetSink()->Post(id, m, 0), Release via vcall.
PATTERN = 'push esi ; push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov dword ptr [eax + N], N ; mov dword ptr [eax], A ; xor ecx, ecx ; lea edx, [eax + N] ; xchg dword ptr [edx], ecx ; mov dword ptr [eax], A ; mov dword ptr [eax + N], N ; mov edx, dword ptr [eax] ; mov esi, eax ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esi + N], A ; mov dword ptr [esi + N], ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [eax] ; mov edx, dword ptr [edx + N] ; push N ; push esi ; push ecx ; mov ecx, eax ; call edx ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; mov ecx, esi ; call edx ; pop esi ; ret N ; xor esi, esi'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = '''inline void* operator new(unsigned, void* p) { return p; }
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
void* __cdecl Alloc(unsigned, const char*, int, int, int, int);
struct Fields { long rc; int pad[10]; unsigned id; int p; Fields() : id(0) {} };
struct Base : Fields { virtual void a(); virtual void AddRef(); virtual void Release();
  Base() { _InterlockedExchange(&rc, 0); } };
struct Msg : Base { int f38; Msg() : f38(0) {} virtual void a(); virtual void AddRef(); virtual void Release(); };
struct Sink { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void Post(unsigned, Msg*, int); };
Sink* __cdecl GetSink();
'''
def emit(va, A, N):
    src = ("void __stdcall FUN_%08x(int, int b) {\n"
           "  void* mem = Alloc(0x40, \"App\", 0, 0, 0, 0);\n"
           "  Msg* m = mem ? new(mem) Msg : 0;\n"
           "  if (m) m->AddRef();\n"
           "  m->id = 0x%x;\n"
           "  m->pad[0] = b;\n"
           "  GetSink()->Post(m->id, m, 0);\n"
           "  m->Release();\n"
           "}" % (va, A[-1]))
    return src, "?FUN_%08x@@YGXHH@Z" % va
