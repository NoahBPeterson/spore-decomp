// slice s00709cf0: cLightingWorld shutdown / state helpers and the local light
// deque destructor.  /O2 + SSE region.
#include <new>
#include <intrin.h>
#include "types.h"

void __cdecl EastlFree(void* p);                       // 0x00F47380

struct Alloc {
    void Destroy(void* p);
};
extern Alloc* g_pAlloc;                                // 0x016C8B44

// ===========================================================================
// spstl::simple_deque<slot_vector_entry<cLocalLightInfo>>::ClearImpl
// ===========================================================================
struct ClearDeque {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    char pad8[0xc];
    int mField14;       // +0x14
    void ClearImpl(int unused);
};

// @ 0x0070a1f0
void ClearDeque::ClearImpl(int)
{
    while (mpBegin != mpEnd) {
        char* e = (char*)(mField14 * 0xc4 + *(int*)((char*)mpEnd - 4));
        if (((*(int*)e >> 31) & 1) == 0) {
            void* x = *(void**)(e + 0x2c);
            if (x && x != *(void**)(e + 0x3c))
                EastlFree(x);
        }
        if (mField14 == 0) {
            g_pAlloc->Destroy(*(void**)((char*)mpEnd - 4));
            mpEnd -= 1;
            mField14 = 0x7f;
        } else {
            --mField14;
        }
    }
}

// ===========================================================================
// cLightingWorld state helpers
// ===========================================================================
struct StateSource {
    void* Create(void* state);          // 0x705af0
};

struct cLightingWorld {
    void SetLightingState(void* state);
    void Update();                       // 0x7094c0
    void Shutdown();
    bool LoadProperties();
    void ConfigFromProperties(int* self);
    void DestroySlotDequeEh();           // 0x70a070
    void ConstructSampleVec(int n);      // 0x70a0d0
    void CopyConfig(int* self);          // 0x70a130
};

// @ 0x0070a560
void cLightingWorld::SetLightingState(void* state)
{
    if (*(void**)((char*)this + 0x14) != state) {
        if (state) {
            void* v = ((StateSource*)*(void**)((char*)this + 0xc))->Create(state);
            *(void**)((char*)this + 0x10) = v;
            _ReadWriteBarrier();
            *(void**)((char*)this + 0x14) = state;
            Update();
        } else {
            *(void**)((char*)this + 0x10) = 0;
            *(void**)((char*)this + 0x14) = state;
            Update();
        }
    }
}

// ===========================================================================
// remaining cLightingWorld entry points (not reconstructed; see partial.txt)
// ===========================================================================
// @ 0x00709cf0
bool cLightingWorld::LoadProperties()
{
    return true;
}

// @ 0x0070a3f0
void cLightingWorld::Shutdown()
{
}

// @ 0x0070a2a0
void cLightingWorld::ConfigFromProperties(int* self)
{
    (void)self;
}

// @ 0x0070a070
void cLightingWorld::DestroySlotDequeEh()
{
}

// @ 0x0070a0d0
void cLightingWorld::ConstructSampleVec(int)
{
}

// @ 0x0070a130
void cLightingWorld::CopyConfig(int* self)
{
    (void)self;
}

