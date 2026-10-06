// Slice s00d00ee0: SP simulator container/set helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast
#include "types.h"

extern "C" void __cdecl Opaque();
extern "C" void* __cdecl FUN_00921580(void* node);

// ===========================================================================
// @ 0x00d011e0  __cdecl: destroy tree from root until sentinel
// ===========================================================================
extern "C" int __cdecl Fd011e0(int unused, void* t)
{
    char* base = (char*)t;
    void* node = *(void**)(base + 8);
    void* sentinel = base + 4;
    while (node != sentinel)
        node = FUN_00921580(node);
    return 1;
}

// ===========================================================================
// @ 0x00d01210  __cdecl lower_bound over 0x20-byte elements
// ===========================================================================
extern "C" int* __cdecl Fd01210(int* first, int* last, int* value)
{
    int n = (int)((char*)last - (char*)first) >> 5;
    if (n > 0) {
        unsigned v = *(unsigned*)value;
        do {
            int half = n >> 1;
            int* mid = (int*)((char*)first + (half << 5));
            if (*(unsigned*)mid < v) {
                first = (int*)((char*)mid + 0x20);
                n -= half + 1;
            } else {
                n = half;
            }
        } while (n > 0);
    }
    return first;
}

// ===========================================================================
// @ 0x00d01260  __cdecl lower_bound over 8-byte elements
// ===========================================================================
extern "C" int* __cdecl Fd01260(int* first, int* last, int* value)
{
    int n = (int)((char*)last - (char*)first) >> 3;
    if (n > 0) {
        unsigned v = *(unsigned*)value;
        do {
            int half = n >> 1;
            int* mid = (int*)((char*)first + (half << 3));
            if (*(unsigned*)mid < v) {
                first = (int*)((char*)mid + 8);
                n -= half + 1;
            } else {
                n = half;
            }
        } while (n > 0);
    }
    return first;
}

// ===========================================================================
// @ 0x00d018d0  __thiscall: erase range [first,last) of 8-byte elements
// ===========================================================================
int* __fastcall Fd018d0(void* self, int, int* first, int* last)
{
    char* end = *(char**)((char*)self + 4);
    char* d = (char*)first;
    char* s = (char*)last;
    int cnt = (int)((char*)last - (char*)first);
    while (s != end) {
        *(int*)d = *(int*)s;
        *(int*)(d + 4) = *(int*)(s + 4);
        d += 8;
        s += 8;
    }
    *(char**)((char*)self + 4) = end - cnt;
    return first;
}

// ===========================================================================
// Remaining helpers (not reconstructed) -- stubs keep their addresses' slots.
// ===========================================================================
struct D0 {
    void A0ee0(void* a, void* b);
    void A0f80(void* a);
    void A0ff0();
    void A1110();
    void A12a0();
    void A1340();
    void A1410();
    void A1470();
    void A14e0();
    void A15d0();
    void A1820();
    void A1920();
    void A1ab0();
    void A1b50();
    void A1b80();
    void A1bb0();
    void A1db0();
    void A1e30();
    void A1f20();
};

void D0::A0ee0(void* a, void* b) { (void)a; (void)b; Opaque(); }
void D0::A0f80(void* a) { (void)a; Opaque(); }
void D0::A0ff0() { Opaque(); }
void D0::A1110() { Opaque(); }
void D0::A12a0() { Opaque(); }
void D0::A1340() { Opaque(); }
void D0::A1410() { Opaque(); }
void D0::A1470() { Opaque(); }
void D0::A14e0() { Opaque(); }
void D0::A15d0() { Opaque(); }
void D0::A1820() { Opaque(); }
void D0::A1920() { Opaque(); }
void D0::A1ab0() { Opaque(); }
void D0::A1b50() { Opaque(); }
void D0::A1b80() { Opaque(); }
void D0::A1bb0() { Opaque(); }
void D0::A1db0() { Opaque(); }
void D0::A1e30() { Opaque(); }
void D0::A1f20() { Opaque(); }
