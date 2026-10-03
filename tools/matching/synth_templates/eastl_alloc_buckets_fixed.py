# EASTL hashtable::DoAllocateBuckets(n) on a fixed_hashtable_allocator (/O2):
#   if (n*4+4 == kNodeSize) { p = pool.head; if (p) pool.head = *p; else p = allocate(...); }
#   else p = mpBucketBuffer; memset(p,0,n*4); p[n] = (void*)-1; return p;
# The overflow allocator is copied by value into a local before allocate() (this forces ecx).
# Layout: +0x1c pool head, +0x2c allocator name/ctx, +0x30 bucket buffer.
PATTERN = 'push esi ; push edi ; mov edi, dword ptr [esp + N] ; add edi, edi ; add edi, edi ; lea eax, [edi + N] ; cmp eax, N ; jne +N ; mov eax, dword ptr [ecx + N] ; test eax, eax ; je +N ; mov edx, dword ptr [eax] ; mov dword ptr [ecx + N], edx ; mov esi, eax ; jmp +N ; mov ecx, dword ptr [ecx + N] ; push N ; push A ; push N ; push N ; push A ; push ecx ; call EXT ; add esp, N ; mov esi, eax ; jmp +N ; mov esi, dword ptr [ecx + N] ; push edi ; push N ; push esi ; call EXT ; add esp, N ; mov dword ptr [edi + esi], A ; pop edi ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = r"""typedef unsigned int size_t;
extern "C" void* memset(void*, int, size_t);
void* EASTL_allocator_allocate(void* a, const char* name, int flags, int dflags, const char* file, int line);
struct Link { Link* mpNext; };
struct Alloc { void* mCtx;
  void* allocate(const char* nm) { return EASTL_allocator_allocate(mCtx, nm, 0, 0, "allocator.h", 209); } };
struct Pool { Link* mpHead;
  void* allocate() { Link* l = mpHead; if (l) { mpHead = l->mpNext; return l; } return 0; } };
"""
def emit(va, A, N):
    k = N[2]
    t = "HT_%08x" % va
    src = ("struct %(t)s { unsigned pad0[7]; Pool mPool; unsigned pad1[3]; Alloc mAlloc; void** mpBuf;\n"
           "  void* palloc() { void* p = mPool.allocate(); if (!p) { Alloc a = mAlloc; p = a.allocate(\"EASTL\"); } return p; }\n"
           "  void** DoAllocateBuckets(size_t n);\n};\n"
           "void** %(t)s::DoAllocateBuckets(size_t n) {\n"
           "  void** p;\n"
           "  if (n * 4 + 4 == %(k)#x) p = (void**)palloc(); else p = mpBuf;\n"
           "  memset(p, 0, n * 4);\n"
           "  p[n] = (void*)-1;\n"
           "  return p;\n}") % dict(t=t, k=k)
    return src, "?DoAllocateBuckets@%s@@QAEPAPAXI@Z" % t
