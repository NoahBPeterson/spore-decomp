// Slice s0099afe0: EA::UTFWinTools::UTFWinToolsInternal::XmlReaderState XML reader.
// Reconstructed from the annotated disassembly; real names from the 2008 PDB where known.
#include "types.h"

// ---------------------------------------------------------------------------
// generic stubs
// ---------------------------------------------------------------------------
struct RefObj {
  virtual void r0();
  virtual void Release();
};
struct S962100b { int* op(void*); };        // eastl hash_map<unsigned,AutoRefCount<...>>::operator[]
struct S693230 { void f(void*, unsigned); }; // hashtable bucket dealloc/copy helper
struct S620230b { void f(); };               // intrusive_list_base::~intrusive_list_base
struct S928dc0 { void f(); };                // allocator reset
struct S928cd0 { void init(int, int, int, int, int); }; // StackAllocator::StackAllocator
struct S928b00 { void init(int, int, int, int, int); }; // StackAllocator::Init
struct S928c40 { void f(void*); };
struct S99a470 { void f(int); };
struct S99a380 { int f(int); };
struct S99a3f0 { int f(int); };
struct S99a4c0 { bool f(void*); };
struct S99a7c0 { bool f(void*, void*); };
struct S99a9d0 { void f(void*); };
struct S99ac80 { bool f(void*); };
struct S95dda0 { bool f(void*, void*, void*); };
struct S95dd00 { void* f(void*, int, void*); };
struct S95dbd0 { bool f(void*, void*, void*, int); };
struct S900720 { void* f(wchar_t*); };
struct S900660 { int f(); };
struct S900690 { void* f(); };
struct S9007b0 { void f(); };
struct SFcc210 { int f(); };

extern void FUN_f47380(void*);     // operator delete(void*)
extern bool FUN_928ba0_fn(int);
extern void FUN_11e073e(void*, int, int);

// ---------------------------------------------------------------------------
// functions defined here
// ---------------------------------------------------------------------------
struct S99afe0 { bool f(void*); };
struct S99b110 { void* f(void*, int, void*, int); };
struct S99b1f0 { bool f(int, int); };
struct S99b5a0 { void f(int, int); };
struct S99b5e0 { void f(); };
struct S99b660 { S99b660* f(int, int, int, int, int); };
struct S99b730 { unsigned f(int, int); };
struct S99b8a0 { bool f(int, int); };
struct S99b9e0 { bool f(); };
struct S99bac0 { unsigned f(); };
struct S99bc00 { unsigned f(); };
struct S99be60 { bool f(int, int, int, int, int, int); };

// ---------------------------------------------------------------------------
// @ 0x0099afe0  recursive LazyReference / object-map fixup walk
// ---------------------------------------------------------------------------
bool S99afe0::f(void* node) {
  char* self = (char*)this;
  char* anchor = (char*)node;
  for (char* p = *(char**)anchor; p != anchor; p = *(char**)p) {
    char* sub = p + 8;
    if (*(char**)(p + 0xc) != sub) ((S99afe0*)self)->f(sub);
    if (*(int*)(p + 0x28) != 0) {
      unsigned cnt = *(unsigned*)(p + 0x30);
      if (cnt != 0) {
        int* out = *(int**)(p + 0x20);
        unsigned i = 0;
        do {
          int key = *(int*)(*(int*)(p + 0x2c) + i * 4);
          int v = 0;
          if (key != 0) {
            int found[1];
            ((S962100b*)(self + 0x64))->op(found);
            if (found[0] != *(int*)(*(int*)(self + 0x68) + *(int*)(self + 0x6c) * 4)) {
              v = *(int*)(found[0] + 4);
            } else {
              char* c = *(char**)(self + 0x84) + 0x1c;
              int found2[1];
              ((S962100b*)c)->op(found2);
              if (found2[0] != *(int*)(*(int*)(*(int*)(self + 0x84) + 0x20) +
                                       *(int*)(*(int*)(self + 0x84) + 0x24) * 4))
                v = *(int*)(found2[0] + 4);
            }
          }
          *out = v;
          out++;
          i++;
        } while (i < cnt);
      }
      ((S95dda0*)(p + 4))->f(p + 0x1c, p + 0x10, self);
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x0099b110  XmlReaderState::CreateLazyReference
// ---------------------------------------------------------------------------
void* S99b110::f(void* a, int b, void* c, int d) {
  char* self = (char*)this;
  char* pool = self + 4;
  int avail = (int)(*(int*)(pool + 0xc) + (-0x38 - *(int*)(pool + 0x10)));
  char* obj = 0;
  if (avail < 0) {
    if (!FUN_928ba0_fn(0x38)) goto fail;
    obj = *(char**)(pool + 0xc);
    *(int*)(pool + 0xc) = (int)(obj + 0x38);
    *(int*)(pool + 0x10) = (int)(obj + 0x38);
  } else {
    obj = *(char**)(pool + 0xc);
    *(int*)(pool + 0xc) = (int)(obj + 0x38);
    *(int*)(pool + 0x10) = (int)(obj + 0x38);
  }
  if (!obj) goto fail;
  *(int*)(obj + 4) = 0;
  *(int*)(obj) = 0;
  *(int*)(obj + 0xc) = (int)(obj + 8);
  *(int*)(obj + 8) = (int)(obj + 8);
  goto cont;
fail:
  obj = 0;
cont:
  *(int*)(obj + 0x10) = *(int*)(a);
  *(int*)(obj + 0x14) = *(int*)((char*)a + 4);
  *(int*)(obj + 0x18) = *(int*)((char*)a + 8);
  *(int*)(obj + 0x28) = b;
  *(int*)(obj + 0x1c) = *(int*)(c);
  *(int*)(obj + 0x20) = *(int*)((char*)c + 4);
  *(int*)(obj + 0x24) = *(int*)((char*)c + 8);
  *(int*)(obj + 0x30) = d;
  if (d > 0) {
    int bytes = d * 4;
    char* mem = 0;
    if ((int)(*(int*)(pool + 8) - *(int*)(pool + 0xc)) - ((bytes + 7) & ~7) < 0) {
      if (!FUN_928ba0_fn((bytes + 7) & ~7)) { *(int*)(obj + 0x2c) = 0; return obj; }
    }
    mem = *(char**)(pool + 0xc);
    *(int*)(pool + 0xc) = (int)(mem + ((bytes + 7) & ~7));
    *(int*)(pool + 0x10) = (int)(mem + ((bytes + 7) & ~7));
    if (mem) FUN_11e073e(mem, 0, bytes);
    *(int*)(obj + 0x2c) = (int)mem;
  }
  return obj;
}

// ---------------------------------------------------------------------------
// @ 0x0099b1f0  XmlReaderState::ReadProperty  (skeleton)
// ---------------------------------------------------------------------------
bool S99b1f0::f(int a, int b) {
  (void)this; (void)a; (void)b;   // full property parser not reconstructed
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x0099b5a0  hash_map<unsigned,AutoRefCount<...>> slot assign
// ---------------------------------------------------------------------------
void S99b5a0::f(int key, int obj) {
  int* slot = ((S962100b*)this)->op(&key);
  int old = *slot;
  if (obj != old) {
    if (obj) ((RefObj*)(size_t)obj)->r0();
    *slot = obj;
    if (old) ((RefObj*)(size_t)old)->Release();
  }
}

// ---------------------------------------------------------------------------
// @ 0x0099b5e0  XmlReaderState base destructor
// ---------------------------------------------------------------------------
void S99b5e0::f() {
  char* self = (char*)this;
  char* ht = self + 0x64;
  *(int*)self = (int)0x1446c44;
  ((S693230*)ht)->f(*(void**)(ht + 4), *(unsigned*)(ht + 8));
  *(int*)(ht + 0xc) = 0;
  if (*(unsigned*)(ht + 8) > 1) FUN_f47380(*(void**)(ht + 4));
  ((S620230b*)(self + 0x5c))->f();
  ((S928dc0*)(self + 0x28))->f();
  ((S928dc0*)(self + 4))->f();
  *(int*)self = (int)0x14613b8;
}

// ---------------------------------------------------------------------------
// @ 0x0099b660  XmlReaderState::XmlReaderState
// ---------------------------------------------------------------------------
S99b660* S99b660::f(int a, int b, int c, int d, int e) {
  char* self = (char*)this;
  *(int*)self = (int)0x1446c44;
  ((S928cd0*)(self + 4))->init(0, -1, 0, 0, 0);
  ((S928cd0*)(self + 0x28))->init(0, -1, 0, 0, 0);
  *(int*)(self + 0x4c) = d;
  *(int*)(self + 0x50) = e;
  *(int*)(self + 0x54) = (int)0xef54054c;
  *(int*)(self + 0x58) = 0;
  *(int*)(self + 0x60) = (int)(self + 0x5c);
  *(int*)(self + 0x5c) = (int)(self + 0x5c);
  *(int*)(self + 0x74) = 0x3f800000;
  *(int*)(self + 0x78) = 0x40000000;
  *(int*)(self + 0x6c) = 1;
  *(int*)(self + 0x68) = (int)0x154df28;
  *(int*)(self + 0x70) = 0;
  *(int*)(self + 0x7c) = 0;
  *(int*)(self + 0x94) = a;
  *(int*)(self + 0x84) = b;
  *(int*)(self + 0x88) = c;
  *(int*)(self + 0x8c) = 0;
  *(int*)(self + 0x90) = 0;
  ((S928b00*)(self + 0x28))->init(0, 0, 0, 0, 0);
  ((S928b00*)(self + 4))->init(0, 0, 0, 0, 0);
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x0099b730  XmlReaderState::ReadPropertyList  (skeleton)
// ---------------------------------------------------------------------------
unsigned S99b730::f(int a, int b) {
  (void)this; (void)a; (void)b;
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0099b8a0  XmlReaderState::ReadObject  (skeleton)
// ---------------------------------------------------------------------------
bool S99b8a0::f(int a, int b) {
  (void)this; (void)a; (void)b;
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x0099b9e0  XmlReaderState::ReadBindings  (skeleton)
// ---------------------------------------------------------------------------
bool S99b9e0::f() {
  (void)this;
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x0099bac0  XmlReaderState::ReadGraph  (skeleton)
// ---------------------------------------------------------------------------
unsigned S99bac0::f() {
  (void)this;
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0099bc00  reader-state traversal  (skeleton)
// ---------------------------------------------------------------------------
unsigned S99bc00::f() {
  (void)this;
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0099be60  XmlReaderState finaliser  (skeleton)
// ---------------------------------------------------------------------------
bool S99be60::f(int a, int b, int c, int d, int e, int f6) {
  (void)this; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f6;
  return false;
}
