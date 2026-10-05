// Slice s0066bf70: SP::cSPUIFeedListItem-adjacent feed-card/layout helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"
#include <intrin.h>

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void  __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380
void  __cdecl FUN_00f47040(void* p);                 // 0x00f47040
void* __cdecl SP_AppSystem();                        // 0x0067dd00
void  __cdecl FUN_00571db0(void* h, void* a, void* b, void* c, void* d);

extern int gVt140075c;   // 0x0140075c
extern int gVt13ef094;   // 0x013ef094

struct RefObj {
    virtual void v0();
    virtual int  Release();
    virtual void Release2();
};

struct cSPUILayout {
    virtual void s0();
    virtual void s1();
    virtual int  Release();
    void Shutdown(bool);
};

struct Sub54 { void FUN_0054eac0(int); };
struct Sub64 { void FUN_006571e0(int, int, int); };

struct Cb70 {
    Cb70* FUN_0066cb70(unsigned flags);
};

// -----------------------------------------------------------------------------
// @ 0x0066cb70  scalar deleting destructor
// -----------------------------------------------------------------------------
Cb70* Cb70::FUN_0066cb70(unsigned flags) {
    *(void**)this = &gVt140075c;
    _ReadWriteBarrier();
    void* p;
    p = *(void**)((char*)this + 0x14); if (p) ((RefObj*)p)->Release();
    p = *(void**)((char*)this + 0x10); if (p) ((RefObj*)p)->Release();
    p = *(void**)((char*)this + 0xc);  if (p) ((RefObj*)p)->Release();
    p = *(void**)((char*)this + 8);    if (p) ((RefObj*)p)->Release();
    *(void**)this = &gVt13ef094;
    if (flags & 1) EASTL_allocator_deallocate(this);
    return this;
}

// -----------------------------------------------------------------------------
// @ 0x0066c370  shutdown / release all owned sub-objects
// -----------------------------------------------------------------------------
void __fastcall FUN_0066c370(void* self) {
    if (*(uint8_t*)((char*)self + 0xac)) {
        *(uint8_t*)((char*)self + 0xac) = 0;
        void* app = SP_AppSystem();
        ((FnVoidI)VT(app)[16])(app, 0);
    }
    *(uint8_t*)((char*)self + 0x9e) = 0;
    void* p;
    p = *(void**)((char*)self + 0xc);
    if (p) {
        ((cSPUILayout*)p)->Shutdown(true);
        if (p) { *(void**)((char*)self + 0xc) = 0; ((RefObj*)p)->Release2(); }
    }
    p = *(void**)((char*)self + 0x54);
    if (p) {
        FUN_00f47040(p);
        if (p) { *(void**)((char*)self + 0x54) = 0; ((RefObj*)p)->Release(); }
    }
    p = *(void**)((char*)self + 0x58);
    if (p) {
        FUN_00f47040(p);
        if (p) { *(void**)((char*)self + 0x58) = 0; ((RefObj*)p)->Release(); }
    }
    p = *(void**)((char*)self + 0x64);
    if (p) ((Sub64*)p)->FUN_006571e0(0, 0, 0);
    p = *(void**)((char*)self + 0x68);
    if (p) { *(void**)((char*)self + 0x68) = 0; ((RefObj*)((char*)p + 0x10))->Release(); }
    p = *(void**)((char*)self + 0x6c);
    if (p) { *(void**)((char*)self + 0x6c) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0x7c);
    if (p) { *(void**)((char*)self + 0x7c) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0xb0);
    if (p) {
        void* a = *(void**)((char*)self + 0xb4);
        void* b = *(void**)((char*)self + 0xb8);
        void* c = *(void**)((char*)self + 0xbc);
        void* d = *(void**)((char*)self + 0xc0);
        *(void**)((char*)self + 0xb0) = 0;
        FUN_00571db0(p, a, b, c, d);
    }
    p = *(void**)((char*)self + 0x14);
    if (p) ((FnVoidI)VT(p)[0x1e])(p, 0x1002);
}

// -----------------------------------------------------------------------------
// @ 0x0066bf70 / 0x0066c0c0 / 0x0066c490 / 0x0066c720 / 0x0066c9e0 / 0x0066cbd0
// @ 0x0066cd20  (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void __fastcall FUN_0066bf70(void* self) { (void)self; }
void __fastcall FUN_0066c0c0(void* self) { (void)self; }
void __fastcall FUN_0066c490(void* self) { (void)self; }
void __fastcall FUN_0066c720(void* self) { (void)self; }
void __fastcall FUN_0066c9e0(void* self) { (void)self; }
void __fastcall FUN_0066cbd0(void* self) { (void)self; }
void __fastcall FUN_0066cd20(void* self) { (void)self; }
