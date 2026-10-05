// Slice 5: nSPSkinner texture/refcount helpers plus paint-system ctor and a large render job.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void  EASTL_allocator_deallocate(void* p);                         // 0x00f47380
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  AtomicRefCounted_Release(void* p);                           // 0x00402420
void  ThreadedObject_Release(void* p);                             // 0x00404f90
void  Memset32(void* dst, int value, int count);                   // 0x0092cb00
void  BaseBca_ctor(void* self, int w, int h);                      // 0x00432960

extern void* g_vtblSimCreatureAbility;   // 0x013ef094
extern void* g_vtblF1c6c;                // 0x013f1c6c
extern void* g_vtblBca4;                 // 0x013ebca4
extern void* g_vtblBcb8;                 // 0x013ebcb8

struct SimAbility {
    void* deleting_dtor(unsigned flags);
};
struct AtomicRefCounted {
    int vtbl;
    int mCount;
};
struct RefHolder {
    int vtbl;                    // +0x00
    AtomicRefCounted mRef;       // +0x04 (mCount at +0x08)
    int AddRef();
};
struct ThreadedRes {
    void dtor();
};
struct Bitmap {
    Bitmap(int w, int h, int fill);
};

// @ 0x0051d300 FUN_0051d300  -- PARTIAL skeleton (large /Od body not reconstructed)
void FUN_0051d300(void* self) { (void)self; }

// @ 0x0051d720 FUN_0051d720  -- PARTIAL skeleton (2065-byte /Od body not reconstructed)
void FUN_0051d720(void* self) { (void)self; }

// @ 0x0051df40 FUN_0051df40  -- PARTIAL skeleton (394-byte /Od body not reconstructed)
void FUN_0051df40(void* self) { (void)self; }

// @ 0x0051e180 ??0PaintSystem@Skinner@@... -- PARTIAL skeleton (435-byte ctor not reconstructed)
void FUN_0051e180(void* self) { (void)self; }

// @ 0x0051d5f0 SimAbility scalar deleting dtor
void* SimAbility::deleting_dtor(unsigned flags)
{
    *(void**)((char*)this + 4) = &g_vtblSimCreatureAbility;
    if ((flags & 1) != 0)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x0051d690 Bitmap ctor
Bitmap::Bitmap(int w, int h, int fill)
{
    BaseBca_ctor(this, w, h);
    *(void**)this = &g_vtblBca4;
    *(void**)((char*)this + 0x18) = &g_vtblBcb8;
    void* buf = EA_alloc((unsigned)(w * h * 4), "Graphics", 0, 0, 0, 0);
    *(void**)((char*)this + 0x28) = buf;
    *(int*)((char*)this + 0x24) = 2;
    Memset32(buf, fill, w * h);
}

// @ 0x0051e100 ThreadedRes dtor
void ThreadedRes::dtor()
{
    *(void**)this = &g_vtblF1c6c;
    if (*(void**)((char*)this + 0x80) != 0)
        AtomicRefCounted_Release(*(void**)((char*)this + 0x80));
    if (*(void**)((char*)this + 0x7c) != 0)
        AtomicRefCounted_Release(*(void**)((char*)this + 0x7c));
    if (*(void**)((char*)this + 8) != 0)
        ThreadedObject_Release(*(void**)((char*)this + 8));
    *(void**)this = &g_vtblSimCreatureAbility;
}

// @ 0x0051e340 RefHolder::AddRef (non-atomic)
int RefHolder::AddRef()
{
    AtomicRefCounted& r = mRef;
    int n = r.mCount + 1;
    r.mCount = r.mCount + 1;
    return n;
}
