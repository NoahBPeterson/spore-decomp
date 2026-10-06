// Spore retail 00b5f040..00b600a0 -- App::cSuperPowersCommand and related UI helpers.
// The larger functions are game-side and are reconstructed approximately here.

#include "types.h"
#include <intrin.h>

typedef unsigned int uint32;
typedef unsigned int size_type;

extern "C" void* EASTL_deallocate(void* p);      // 0x00f47380
extern "C" int   strcmp(const char*, const char*);
extern "C" int   atoi(const char*);

// ---------------------------------------------------------------------------
// Small exact helpers
// ---------------------------------------------------------------------------

void FUN_00b5e0b0(int a);                        // 0x00b5e0b0

// @ 0x00b5f1b0
unsigned char FUN_00b5f1b0(int a, int b)
{
    if (b != 0)
        FUN_00b5e0b0(a);
    return 1;
}

// @ 0x00b5f950  EA::AutoRefCount<EA::UTFWinControls::IWinText>::operator=
namespace EA { namespace UTFWinControls {
class IWinText {
public:
    virtual int AddRef();
    virtual int Release();
};
} }

namespace EA {
template <typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p);
};
template struct AutoRefCount<UTFWinControls::IWinText>;
}

EA::AutoRefCount<EA::UTFWinControls::IWinText>&
EA::AutoRefCount<EA::UTFWinControls::IWinText>::operator=(UTFWinControls::IWinText* p)
{
    UTFWinControls::IWinText* old = mpObject;
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mpObject = p;
        if (old != 0)
            old->Release();
    }
    return *this;
}

// @ 0x00b60070
int* __fastcall FUN_00b60070(int* self)
{
    int z = 0;
    self[1] = z;
    self[0] = 0x1462d70;
    self[4] = z;
    self[5] = z;
    int d = 0x1667bac;
    self[6] = d;
    self[7] = d;
    self[8] = 0x1667bad;
    return self;
}

// @ 0x00b600a0
void __fastcall FUN_00b600a0(int* self)
{
    int a = self[6];
    int b = self[8];
    if (b - a > 1 && a != 0)
        EASTL_deallocate((void*)a);
    // release the shared refcount block at +0x14
    int* ref = (int*)self[5];
    if (ref != 0)
        _InterlockedDecrement((volatile long*)(ref + 2));
    int* obj = (int*)self[4];
    if (obj != 0) {
        typedef void (__fastcall *Fn)(void*);
        (*(Fn*)obj[0])(obj);
    }
    self[0] = 0x13ef094;
}

// ---------------------------------------------------------------------------
// Larger game-side functions (approximate)
// ---------------------------------------------------------------------------

// @ 0x00b5f040
void FUN_00b5f040(int* self, int param_2, unsigned char* param_3)
{
    // formats / collects the command's argument values into param_3
    (void)self; (void)param_2; (void)param_3;
}

// @ 0x00b5f1d0
int __fastcall FUN_00b5f1d0(int self)
{
    return self;
}

// @ 0x00b5f620
void* __fastcall FUN_00b5f620(void* self)
{
    *(void**)self = (void*)0x1462a1c;
    return self;
}

// @ 0x00b5f670
void __fastcall FUN_00b5f670(void* self, int a)
{
    (void)self; (void)a;
}

// @ 0x00b5f7b0
void __fastcall FUN_00b5f7b0(void* self, int a)
{
    (void)self; (void)a;
}

// @ 0x00b5fa90
void __fastcall FUN_00b5fa90(void* self, int a)
{
    (void)self; (void)a;
}

// @ 0x00b5fde0
void __fastcall FUN_00b5fde0(void* self, int a)
{
    (void)self; (void)a;
}
