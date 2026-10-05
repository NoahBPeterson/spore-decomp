// Slice s0073f320 (0x0073f320-0x00740370): SP::cModelInstance bindings / dispatch.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"
#include <intrin.h>

// External callees (masked relocations).
extern "C" void FUN_007c5490();          // 0x7c5490
extern "C" void FUN_01200940();          // 0x1200940
extern "C" void FUN_0073eca0(void*, void*);  // 0x73eca0
extern "C" void FUN_0073bb40(void*);     // 0x73bb40
void __cdecl EASTL_allocator_deallocate(void* p);   // 0xf47380
struct IdPtrVec { void dtor(); };
struct RefVector { void dtor(); };

// ---------------------------------------------------------------------------
// @ 0x0073fe50  eastl::copy_backward<8-byte POD*>
// ---------------------------------------------------------------------------
struct T8 { int a, b; };

void __cdecl copy_backward8(T8* first, T8* last, T8* result)
{
    while (last != first) {
        *--result = *--last;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0073f440  copy_backward for an 8-byte element with a refcounted pointer
// ---------------------------------------------------------------------------
struct RC {
    virtual void v0(int mode);
    virtual void v1();
    int mnRefCount;                  // +0x4
};

struct RefPair {
    int value;                       // +0x0
    RC* p;                           // +0x4
};

RefPair* __cdecl copy_backward_ref(RefPair* first, RefPair* last, RefPair* result)
{
    if (last == first)
        return result;
    do {
        --last;
        --result;
        result->value = last->value;
        RC* p = last->p;
        RC* old = result->p;
        if (p != old) {
            if (p)
                ++p->mnRefCount;
            result->p = p;
            if (old) {
                int n = (old->mnRefCount += -1);
                if (n == 0) {
                    old->mnRefCount = 1;
                    old->v0(1);
                }
            }
        }
    } while (last != first);
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00740370  set a refcounted array pointer member at +0xd0
// ---------------------------------------------------------------------------
struct DynArray {
    void* first;                     // +0x0
};

struct ArrayHolder {
    char pad[0xd0];
    DynArray* mArray;                // +0xd0
    void SetArray(DynArray* p);
};

void ArrayHolder::SetArray(DynArray* p)
{
    DynArray* old = mArray;
    if (old) {
        void* first = old->first;
        if (first && *(int*)((char*)first - 4) != 0)
            EASTL_allocator_deallocate(first);
        EASTL_allocator_deallocate(old);
    }
    mArray = p;
}

// ---------------------------------------------------------------------------
// @ 0x0073f320  SP::cModelInstance::cSkinBinding::operator=
// ---------------------------------------------------------------------------
struct cSPTransformS {
    uint16_t mFlags;
    uint16_t mModificationCount;
    float    mTranslation[3];
    float    mScale;
    float    mRotation[9];           // +0x14
    cSPTransformS& operator=(const cSPTransformS& o);
};

struct cSkinBinding {
    int f0, f4, f8;
    RC* p0c;                         // +0xc
    cSPTransformS t10;               // +0x10
    cSPTransformS t48;               // +0x48
    cSPTransformS t80;               // +0x80
    int b8, bc, c0;
    cSkinBinding& operator=(const cSkinBinding& o);
};

cSkinBinding& cSkinBinding::operator=(const cSkinBinding& o)
{
    f0 = o.f0;
    f4 = o.f4;
    f8 = o.f8;
    if (o.p0c != p0c) {
        RC* p = o.p0c;
        RC* old = p0c;
        if (p)
            ++p->mnRefCount;
        p0c = p;
        if (old) {
            int n = (old->mnRefCount += -1);
            if (n == 0) {
                old->mnRefCount = 1;
                _ReadWriteBarrier();
                old->v0(1);
            }
        }
    }
    t10 = o.t10;
    t48 = o.t48;
    t80 = o.t80;
    b8 = o.b8;
    bc = o.bc;
    c0 = o.c0;
    return *this;
}

// ===========================================================================
// Remaining binding/dispatch functions (large; reconstruction in progress).
// ===========================================================================
struct cModelInstance_Bindings {
    char pad[0x154];

    int  Dispatch(int a2, int a3);                    // 0x73fd20
    void DispatchMesh(int a2, void* a3, int a4, int a5);  // 0x73ede0
    void ctorStub();                                  // 0x7400f0
    int  PickLine(int a2, int a3);                    // 0x73f540
    int  IntersectsSphere(int a2, int a3);            // 0x73f910
    void SetAnimationGroupTransform(int a2, int a3);  // 0x73f4b0
};

// @ 0x0073fd20
int cModelInstance_Bindings::Dispatch(int a2, int a3)
{
    (void)a2; (void)a3;
    return 0;
}

// @ 0x0073ede0
void cModelInstance_Bindings::DispatchMesh(int a2, void* a3, int a4, int a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
}

// @ 0x7400f0
void cModelInstance_Bindings::ctorStub()
{
}

// @ 0x0073f540
int cModelInstance_Bindings::PickLine(int a2, int a3) { (void)a2; (void)a3; return 0; }

// @ 0x0073f910
int cModelInstance_Bindings::IntersectsSphere(int a2, int a3) { (void)a2; (void)a3; return 0; }

// @ 0x0073f4b0
void cModelInstance_Bindings::SetAnimationGroupTransform(int a2, int a3) { (void)a2; (void)a3; }

// ---------------------------------------------------------------------------
// @ 0x007402e0  destructor of the skin/animation binding container (EH)
// ---------------------------------------------------------------------------
void __fastcall BindingContainer_dtor(char* p)
{
    ((IdPtrVec*)(p + 0x50))->dtor();
    ((RefVector*)(p + 0x3c))->dtor();
    void* v;
    v = *(void**)(p + 0x28);
    if (v && *(int*)((char*)v - 4) != 0)
        EASTL_allocator_deallocate(v);
    v = *(void**)(p + 0x14);
    if (v && *(int*)((char*)v - 4) != 0)
        EASTL_allocator_deallocate(v);
    v = *(void**)(p);
    if (v && *(int*)((char*)v - 4) != 0)
        EASTL_allocator_deallocate(v);
}

// ---------------------------------------------------------------------------
// @ 0x0073fe80  eastl::vector<...>::DoInsertValue  (partial)
// @ 0x00740160  eastl::vector<...>::DoInsertFromIterator  (partial)
// @ 0x0073ffb0  (partial)
// ---------------------------------------------------------------------------
void EastlDoInsertValue(void* self) { (void)self; }
void EastlDoInsertFromIterator(void* self) { (void)self; }
void Sub73ffb0(void* self) { (void)self; }
