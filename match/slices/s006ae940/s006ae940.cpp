// Slice s006ae940: SP::cAsyncResourceManager and related async resource helpers.
// Mostly /O2 with old-style EH; a few leaf helpers match directly.
#include "../../include/types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// globals (undefined externs -> relocations)
// ---------------------------------------------------------------------------
extern void* g_pRegistry;   // 0x1603118

// ---------------------------------------------------------------------------
// 006af5c0  void FUN_006af5c0(void* p)
// ---------------------------------------------------------------------------
void __stdcall FUN_006af5c0(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[9])(p);
}

// ---------------------------------------------------------------------------
// 006af940  bool FUN_006af940(int self)    (try-lock refcount addref)
// ---------------------------------------------------------------------------
bool __fastcall FUN_006af940(int self)
{
    volatile long* rc = (volatile long*)(self + 8);
    if (_InterlockedExchangeAdd(rc, 0) != 0) {
        _InterlockedExchangeAdd(rc, 1);
        return true;
    }
    return false;
}

// ===========================================================================
// remaining functions
// ===========================================================================
extern void* vtbl_14094d0;
extern void* vtbl_14094cc;
extern void* vtbl_13eb938;
extern void* vtbl_13ef094;
extern void* vtbl_14095f4;
extern void* vtbl_13effb8;
extern void* vtbl_13f1ab0;
extern void* vtbl_13fa72c;
extern void* vtbl_1408500;
extern void* vtbl_14084f0;
extern void* vtbl_1409630;
extern void* vtbl_140961c;
extern "C" void IO_WriteUint32(void* stream, void* src, int n, int flags); // 0x93aa70
extern "C" void FUN_0093ab10(void* stream, void* src, int n, int flags);   // 0x93ab10

struct XRBNode { XRBNode* left; XRBNode* right; };
struct XRBTree { void DoNukeSubtree(void* n); };
struct Mutex2 { void dtor(); };   // EA::Thread::Mutex::~Mutex (0x922130)

// ---------------------------------------------------------------------------
// 006aebd0  SP::cAsyncResourceManager::~cAsyncResourceManager
// ---------------------------------------------------------------------------
// @ 0x006aebd0
void __fastcall FUN_006aebd0(void* self)
{
    *(void**)self = &vtbl_14094d0;
    *(void**)((char*)self + 4) = &vtbl_14094cc;
    void* anchor = *(void**)((char*)self + 0x4c);
    ((XRBTree*)((char*)self + 0x40))->DoNukeSubtree(anchor);
    ((Mutex2*)((char*)self + 0x10))->dtor();
    *(void**)((char*)self + 4) = &vtbl_13ef094;
    *(void**)self = &vtbl_13eb938;
}

// ---------------------------------------------------------------------------
// 006aedc0  SP::cAsyncResourceManager::cAsyncResourceManager
// ---------------------------------------------------------------------------
// @ 0x006aedc0
void __fastcall FUN_006aedc0(void* self)
{
    *(void**)self = &vtbl_13fa72c;
    *(void**)((char*)self + 4) = &vtbl_13ef094;
    *(void**)((char*)self + 8) = 0;
    *(void**)self = &vtbl_14094d0;
    *(void**)((char*)self + 4) = &vtbl_14094cc;
    ((Mutex2*)((char*)self + 0x10))->dtor();  // real: Mutex ctor
}

// ---------------------------------------------------------------------------
// 006af8a0  dtor
// ---------------------------------------------------------------------------
// @ 0x006af8a0
void __fastcall FUN_006af8a0(void* self)
{
    *(void**)self = &vtbl_14095f4;
    void* p = *(void**)((char*)self + 0x10);
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    void* q = *(void**)((char*)self + 0xc);
    if (q) {
        void* r = (char*)q + 4;
        ((void(__thiscall*)(void*))(*(void***)r)[1])(r);
    }
    *(void**)self = &vtbl_13effb8;
}

// ---------------------------------------------------------------------------
// 006af960  resource handle ctor  (__thiscall, 2 stack args)
// ---------------------------------------------------------------------------
struct C_006af960 {
    void* mpVtbl0;     // +0x00
    void* mpVtbl1;     // +0x04
    long  mRefs;       // +0x08
    void* mpOwner;     // +0x0c
    void* mpPayload;   // +0x10
    void* mpExtra;     // +0x14
    C_006af960* ctor(void* a, void* b);
};

// @ 0x006af960
C_006af960* C_006af960::ctor(void* a, void* b)
{
    mpVtbl1 = (void*)&vtbl_13f1ab0;
    mpVtbl0 = (void*)&vtbl_1408500;
    mpVtbl1 = (void*)&vtbl_14084f0;
    _InterlockedExchange(&mRefs, 0);
    mpVtbl0 = (void*)&vtbl_1409630;
    mpVtbl1 = (void*)&vtbl_140961c;
    mpOwner = a;
    if (a) {
        void* r = (char*)a + 4;
        ((void(__thiscall*)(void*))(*(void***)r)[0])(r);
    }
    mpPayload = b;
    if (b)
        ((void(__thiscall*)(void*))(*(void***)b)[0])(b);
    mpExtra = 0;
    return this;
}

// ---------------------------------------------------------------------------
// 006af670  serialize a vector of 0x10-byte records  (__thiscall, 1 arg)
// ---------------------------------------------------------------------------
struct C_006af670 {
    void* mpVtbl0;     // +0x00
    void* mpVtbl1;     // +0x04
    int   mFlags;      // +0x08
    int   mKind;       // +0x0c
    char* mpBegin;     // +0x10
    char* mpEnd;       // +0x14
    void serialize(void* stream);
};

// @ 0x006af670
void C_006af670::serialize(void* stream)
{
    int header[2];
    header[0] = mFlags;
    header[1] = mKind;
    FUN_0093ab10(stream, header, 1, 0);
    int count = (int)(mpEnd - mpBegin) >> 4;
    IO_WriteUint32(stream, &count, 1, 0);
    for (char* p = mpBegin; p != mpEnd; p += 0x10) {
        int v8 = *(int*)(p + 8);
        IO_WriteUint32(stream, &v8, 1, 0);
        int v4 = *(int*)(p + 4);
        IO_WriteUint32(stream, &v4, 1, 0);
        int vc = *(int*)(p + 0xc);
        IO_WriteUint32(stream, &vc, 1, 0);
    }
}

// ---------------------------------------------------------------------------
// 006af5d0  bool V5d0::f(bool a, void* b, bool c)
// ---------------------------------------------------------------------------
struct V5d0 {
    char pad[0x14];
    void* m14;              // +0x14
    bool f(bool a, void* b, bool c);
};

// @ 0x006af5d0
bool V5d0::f(bool a, void* b, bool c)
{
    bool result = false;
    if (a) {
        void* x = m14;
        if (x && b != x)
            ((bool(__thiscall*)(void*, int, void*, bool))(*(void***)this)[17])(this, 0, x, c);
        if (b) {
            if (c) {
                m14 = b;
                return true;
            }
            return ((bool(__thiscall*)(void*, int, void*, int))(*(void***)b)[20])(b, 1, this, 0);
        }
    } else {
        if (b) {
            if (b != m14)
                return false;
            if (c) {
                m14 = 0;
                return true;
            }
            void* old = m14;
            return ((bool(__thiscall*)(void*, int, void*, int))(*(void***)old)[20])(old, 0, this, 0);
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// complex functions left as partial skeletons (see partial.txt)
// ---------------------------------------------------------------------------
void FUN_006ae940() {}
void FUN_006aea90() {}
void FUN_006aec60() {}
void FUN_006aee60() {}
void FUN_006af080() {}
void FUN_006af150() {}
void FUN_006af260() {}
void FUN_006af720() {}

