# Owner method (thiscall, 1 stack arg): allocate a "Simulator" UI::BehaviorMessage (inlined ctor chain with
# interlocked refcount init), AddRef via vcall, set its id (+0x30), post it via owner->sink, Release via vcall.
PATTERN = 'push esi ; push edi ; push N ; push N ; push N ; push N ; push A ; push N ; mov edi, ecx ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov dword ptr [eax + N], N ; mov dword ptr [eax], A ; xor ecx, ecx ; lea edx, [eax + N] ; xchg dword ptr [edx], ecx ; mov dword ptr [eax], A ; mov dword ptr [eax + N], N ; mov edx, dword ptr [eax] ; mov esi, eax ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; mov ecx, dword ptr [esp + N] ; push N ; push esi ; mov dword ptr [esi + N], A ; push ecx ; mov ecx, dword ptr [edi + N] ; call EXT ; mov edx, dword ptr [esi] ; mov eax, dword ptr [edx + N] ; mov ecx, esi ; call eax ; pop edi ; pop esi ; ret N ; xor esi, esi ; jmp +N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = '''inline void* operator new(unsigned, void* p) { return p; }
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
void* __cdecl Alloc(unsigned, const char*, int, int, int, int);
struct Fields { long rc; int pad[10]; unsigned id; int p; Fields() : id(0) {} };
struct Base : Fields { virtual void a(); virtual void AddRef(); virtual void Release();
  Base() { _InterlockedExchange(&rc, 0); } };
struct Msg : Base { int f38; Msg() : f38(0) {} virtual void a(); virtual void AddRef(); virtual void Release(); };
struct Sink { void Post(unsigned, Msg*, int); };
'''
def emit(va, A, N):
    o = "O_%08x" % va
    src = ("struct %s { int a, b, c; Sink* s; void FUN_%08x(unsigned x); };\n"
           "void %s::FUN_%08x(unsigned x) {\n"
           "  void* mem = Alloc(0x40, \"Simulator\", 0, 0, 0, 0);\n"
           "  Msg* m = mem ? new(mem) Msg : 0;\n"
           "  if (m) m->AddRef();\n"
           "  m->id = 0x%x;\n"
           "  s->Post(x, m, 0);\n"
           "  m->Release();\n"
           "}" % (o, va, o, va, A[-1]))
    return src, "?FUN_%08x@%s@@QAEXI@Z" % (va, o)
