// Same shape as s00432830's ??_GPropertyList (0x00432b10): the inlined empty-dtor
// chain stores the two vtables, then the deleting flag picks the free (0x00926060 here).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include <intrin.h>
#pragma intrinsic(_InterlockedExchange)

void Free_00926060(void* p);                         // 0x00926060

struct EditorResource_004c0210 {
    virtual void v0();
    virtual void v1();
    virtual ~EditorResource_004c0210() {}
    void operator delete(void* p) { Free_00926060(p); }
};

struct Triple_004c0210 { int a, b, c; Triple_004c0210() { a = 0; b = 0; c = 0; } };
struct AtomicInt_004c0210 {
    volatile long v;
    AtomicInt_004c0210() { _InterlockedExchange(&v, 0); }
};

struct BakeSprites_004c0210 : EditorResource_004c0210 {
    virtual void v0();
    virtual void v1();
};

struct PropertyList_004c0210 : BakeSprites_004c0210 {
    AtomicInt_004c0210 mRefCount;
    Triple_004c0210 mList;
    virtual void v0();
    virtual void v1();
    virtual ~PropertyList_004c0210() {}
    PropertyList_004c0210();   // defined to key the class (emits the vtable and the deleting dtor)
};

// @ 0x004c0210
PropertyList_004c0210::PropertyList_004c0210() {}
