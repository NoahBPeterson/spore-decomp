// Slice s00dfc5b0 (batch bfs1 #37).  UI-layout / vector helpers (GGE editor
// scenario layout).  32-bit MSVC 2008 SP1, /O2 /arch:SSE.
//
// Functions whose bodies are the inlined eastl vector machinery are stubbed
// (see partial.txt); the standalone ones are reproduced.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" void __cdecl operator_delete(void* p);
extern "C" void __cdecl sub_f280f0(void* p);   // (element + 4) destructor
// A destructed element with a sub-object at +4.
struct Elem44 { void sub_f280f0(); };
struct Sub28Vec {
    void sub_dfb850(void* first, void* last);
};

// ===========================================================================
//  0x00dfc5b0  destructor: delete two arrays
// ===========================================================================
struct Blob5b0 {
    char pad_00[0x28];
    void* mp28;              // +0x28
    void* mp2c;              // +0x2c
    char pad_30[0x20c - 0x30];
    void* mp20c;             // +0x20c
    void dtor();
};
// @ 0x00dfc5b0
void Blob5b0::dtor() {
    if (mp20c && *(int*)((char*)mp20c - 4) != 0) operator_delete(mp20c);
    ((Sub28Vec*)((char*)this + 0x28))->sub_dfb850(mp28, mp2c);
    void* b = *(void**)((char*)this + 0x28);
    if (b && *(int*)((char*)b - 4) != 0) operator_delete(b);
}

// ===========================================================================
//  0x00dfc600  range destructor, stride 0x188, inner vector of 0x44 elements
//  (member so `this` lives in ECX; body does not use it)
// ===========================================================================
struct EffectVec { void EraseRange(void* first, void* last); };
// @ 0x00dfc600
void EffectVec::EraseRange(void* firstP, void* lastP) {
    char* first = (char*)firstP;
    char* last = (char*)lastP;
    for (; first < last; first += 0x188) {
        u32 end = *(u32*)(first + 0x1c);
        for (u32 e = *(u32*)(first + 0x18); e < end; e += 0x44) {
            ((Elem44*)(e + 4))->sub_f280f0();
        }
        int p = *(int*)(first + 0x18);
        if (p && *(int*)(p - 4) != 0) operator_delete((void*)p);
    }
}

// ===========================================================================
//  0x00dfcac0  destroy vector of 0x4e0-byte elements
// ===========================================================================
struct Elem4e0 { void sub_dfbba0(); };
struct BlobAC0 {
    u32 mpBegin;             // +0x00
    u32 mpEnd;               // +0x04
    void dtor();
};
// @ 0x00dfcac0
void BlobAC0::dtor() {
    u32 end = mpEnd;
    for (u32 e = mpBegin; e < end; e += 0x4e0) ((Elem4e0*)e)->sub_dfbba0();
    u32 v = mpBegin;
    if (v && *(int*)(v - 4) != 0) operator_delete((void*)v);
}

// ===========================================================================
//  0x00dfcc40  conditional destructor (uses this+0x210, +0x2c, +0x30)
// ===========================================================================
struct BlobC40 {
    char pad_00[0x2c];
    void* mp2c;              // +0x2c
    void* mp30;              // +0x30
    char pad_34[0x210 - 0x34];
    int   mField210;         // +0x210
    void dtor();
};
// @ 0x00dfcc40
void BlobC40::dtor() {
    if (mField210 < 0) return;
    int a = mField210;
    if (a && *(int*)(a - 4) != 0) operator_delete((void*)a);
    ((Sub28Vec*)((char*)this + 0x2c))->sub_dfb850(mp2c, mp30);
    int b = *(int*)((char*)this + 0x2c);
    if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
}

// ===========================================================================
//  0x00dfce40  destructor chain
// ===========================================================================
struct Elem3c { void sub_f280f0(); };
struct BlobE40 {
    char pad_00[0x3c];
    Elem3c m3c;              // +0x3c
    char pad_40[0x84 - 0x40];
    void* mp84;              // +0x84
    void* mp88;              // +0x88
    void dtor();
};
// @ 0x00dfce40
void BlobE40::dtor() {
    ((EffectVec*)((char*)this + 0x84))->EraseRange(mp84, mp88);
    if (mp84 && *(int*)((char*)mp84 - 4) != 0) operator_delete(mp84);
    m3c.sub_f280f0();
    ((Elem3c*)this)->sub_f280f0();
}

// ===========================================================================
//  0x00dfce90  destructor: one member + vector of 0x4e0 elements
// ===========================================================================
struct BlobE90 {
    char pad_00[0x70];
    u32 mpBegin70;           // +0x70
    u32 mpEnd74;             // +0x74
    char pad_78[0x2788 - 0x78];
    Elem3c m2788;            // +0x2788
    void dtor();
};
// @ 0x00dfce90
void BlobE90::dtor() {
    m2788.sub_f280f0();
    u32 end = mpEnd74;
    for (u32 e = mpBegin70; e < end; e += 0x4e0) ((Elem4e0*)e)->sub_dfbba0();
    u32 v = mpBegin70;
    if (v && *(int*)(v - 4) != 0) operator_delete((void*)v);
}

// ===========================================================================
//  0x00dfd300  range destructor over 0x238-byte records
// ===========================================================================
// @ 0x00dfd300
void __cdecl d300(int* first, int* last) {
    if (first >= last) return;
    int* pi = first + 0x84;
    do {
        if (*first >= 0) {
            int x = *pi;
            if (x && *(int*)(x - 4) != 0) operator_delete((void*)x);
            u32 e1 = (u32)pi[-0x78];
            for (u32 u = (u32)pi[-0x79]; u < e1; u += 0x34) {
                int y = *(int*)(u + 0x1c);
                if (y && *(int*)(y - 4) != 0) operator_delete((void*)y);
            }
            int z = pi[-0x79];
            if (z && *(int*)(z - 4) != 0) operator_delete((void*)z);
        }
        first += 0x8e;
        pi += 0x8e;
    } while (first < last);
}

// ===========================================================================
//  Stubs for the inlined-vector functions (partial)
// ===========================================================================
// @ 0x00dfca50
void __fastcall ca50(void* self, void* other) { (void)self; (void)other; }
// @ 0x00dfcb00
void* __fastcall cb00(void* self, void* other) { (void)other; return self; }
// @ 0x00dfcc90
void* __fastcall cc90(void* self, void* other) { (void)other; return self; }
// @ 0x00dfcce0
void* __fastcall cce0(void* self, void* other) { (void)other; return self; }
// @ 0x00dfcee0
void* __fastcall cee0(void* self, void* other) { (void)other; return self; }
// @ 0x00dfd020
void* __fastcall d020(void* self, void* other) { (void)other; return self; }
// @ 0x00dfd080
void* __fastcall d080(void* self, void* other) { (void)other; return self; }
// @ 0x00dfd250
void* __cdecl d250(void* first, void* last, void* dst) { (void)first; (void)last; return dst; }
// @ 0x00dfd3a0
void* __fastcall d3a0(void* self, void* other) { (void)other; return self; }
// @ 0x00dfd4e0
void* __cdecl d4e0(void* out, void* first, void* last, void* dst) {
    (void)first; (void)last; (void)dst; return out;
}
// @ 0x00dfc6f0
void __fastcall c6f0(void* self) { (void)self; }
