// Slice s0076acd0: SP::cGraphicsResourceFactory / editor resource viewers —
// message registration, ctor/dtor pairs, cube-map capture setup and small
// copy/convert helpers. /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>

extern char g_file[];

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void* __cdecl MessageServer();                                             // 0x67dcc0
void* __cdecl App6750();                                                   // 0x67dd50
void* __cdecl App6740();                                                   // 0x67dd40
void* __cdecl App67dda0();                                                 // 0x67dda0
void* __cdecl Sub67de70();                                                 // 0x67de70
void  __cdecl InitPhysics(void* p, int v);                                 // 0x7c4dd0
void* __cdecl NewPhys(void* p);                                            // 0x7c3f70
void  __cdecl PhysFini(void* p);                                           // 0x7c3ba0
void  __cdecl PhysDel(void* p);                                            // 0x7c4000
void  __cdecl FUN_00761110(void* p);                                       // 0x761110
void* __cdecl CreateRaster(int a, int b, int c, int d, int e);             // 0x761420
void  __cdecl SetCubeMap(void* a, void* b, int c, int d, int e);          // 0x6e51b0
bool  __cdecl FUN_011ef750r(void* out, int a, int b, void* p);             // 0x11ef750
void  __cdecl FUN_011ef880r(void* p, void* out);                           // 0x11ef880
void  __cdecl FUN_011ef750(void* p, int a, int b, void* out);              // 0x11ef750
void  __cdecl FUN_011ef880(void* p, void* out);                            // 0x11ef880
void  __cdecl CopyViewer(void* p, void* a, int b, int c);                  // 0x7c50b0
void  __cdecl JobRelease(void* p);                                         // 0x690120
void  __cdecl FUN_7c4be0(void* p, void* a, int b);                         // 0x7c4be0
void  __cdecl FUN_7c4ba0(void* p, float f);                                // 0x7c4ba0
void  __cdecl FUN_7c53d0(void* p, float f);                                // 0x7c53d0
void  __cdecl FUN_7c40f0(void* p);                                         // 0x7c40f0
void  __cdecl QuatFromMatrix(void* out, void* m, float f, int a);          // 0x472b80
void  __cdecl Matrix3Assign(void* p, void* src);                           // 0x41cb40
void  __cdecl Basis3Build(void* out, void* a, void* b);                    // 0x6b9440
void  __cdecl CaptureCubeMap(void* a, void* b, void* c, void* d, int e, int f); // 0x6e4210
}

// ---------------------------------------------------------------------------
// @ 0x0076acd0  register a graphics-resource message listener
// ---------------------------------------------------------------------------
struct CAlloc {
    char pad[0x64];
    void* m64;
};
bool __fastcall RegisterListener(void* self, int, int unused) {
    (void)unused;
    CAlloc* s = (CAlloc*)self;
    void* ms = MessageServer();
    if (ms) {
        int tags[11] = {0x1c91267, 0x3ea7e1b, 0x1c7f3db, 0x1c7f90a, 0x1c7fd85,
                        0x202ce02, 0x1fb2458, 0x1c91276, 0x1c9127b, 0, 0};
        for (int i = 0; i < 9; i++) {
            void* p = self ? (char*)self + 8 : 0;
            ((void(__thiscall**)(void*, void*, int))*(void***)ms)[8](ms, p, tags[i]);
        }
    }
    void* a = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* obj = a ? NewPhys(a) : 0;
    s->m64 = obj;
    InitPhysics(obj, 0);
    for (int i = 0; i < 6; i++) {
        void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
        void* o = q ? NewPhys(q) : 0;
        *(void**)((char*)self + 0x14 + i * 4) = o;
        InitPhysics(o, 0);
        FUN_7c53d0(o, 1.0f);
    }
    for (int i = 0; i < 6; i++) {
        void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
        void* o = q ? NewPhys(q) : 0;
        *(void**)((char*)self + 0x2c + i * 4) = o;
        InitPhysics(o, 1);
        FUN_7c53d0(o, 1.0f);
        FUN_7c4ba0(o, 1.0f);
    }
    void* app = App6750();
    ((void(__thiscall**)(void*))*(void***)app)[7](app);
    *(void**)((char*)self + 0x6c) = App67dda0();
    *(void**)((char*)self + 0x70) = App6740();
    return true;
}

// ===========================================================================
// @ 0x0076af50  ctor (2-vtable class, 0x174 object)
// ===========================================================================
struct B1af { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); };
struct B2af { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); };
struct Daf : B1af, B2af {
    int mAtomic;              // +8
    char m0c;                 // +0xc
    char padD[0x103];
    int m110, m114, m118, m11c;
    char m120;
    Daf();
    virtual ~Daf();
};
Daf::Daf() {
    (void)_InterlockedExchange((volatile long*)&mAtomic, 0);
    m0c = 0;
    m110 = 0; m114 = 0; m118 = 0; m11c = 0;
    m120 = 1;
}
Daf::~Daf() { if (m11c) Dealloc((void*)m11c); }
void DeleteDaf(Daf* p) { delete p; }

// ===========================================================================
// @ 0x0076b000  tear down a viewer's arrays and physics objects
// ===========================================================================
bool __fastcall TeardownViewer(void* self, int, int unused) {
    (void)unused;
    void* ms = MessageServer();
    if (ms) {
        int tags[9] = {0x1c91267, 0x3ea7e1b, 0x1c7f3db, 0x1c7f90a, 0x1c7fd85,
                       0x202ce02, 0x1fb2458, 0x1c91276, 0x1c9127b};
        for (int i = 0; i < 9; i++) {
            void* p = self ? (char*)self + 8 : 0;
            ((void(__thiscall**)(void*, int, void*, int))*(void***)ms)[11](ms, (int)p, p, tags[i]);
        }
    }
    if (*(void**)((char*)self + 0x64)) {
        PhysFini(*(void**)((char*)self + 0x64));
        void* p = *(void**)((char*)self + 0x64);
        if (p) { PhysDel(p); Dealloc(p); }
    }
    for (int i = 0; i < 6; i++)
        if (*(void**)((char*)self + 0x14 + i * 4)) {
            PhysFini(*(void**)((char*)self + 0x14 + i * 4));
            void* p = *(void**)((char*)self + 0x14 + i * 4);
            if (p) { PhysDel(p); Dealloc(p); }
        }
    for (int i = 0; i < 6; i++)
        if (*(void**)((char*)self + 0x2c + i * 4)) {
            PhysFini(*(void**)((char*)self + 0x2c + i * 4));
            void* p = *(void**)((char*)self + 0x2c + i * 4);
            if (p) { PhysDel(p); Dealloc(p); }
        }
    int* r = *(int**)((char*)self + 0x9c);
    if (r) {
        ((void(__thiscall**)(int*, int))*(void***)r)[3](r, 6);
        r = *(int**)((char*)self + 0x9c);
        if (r) {
            *(void**)((char*)self + 0x9c) = 0;
            ((void(__thiscall**)(int*))*(void***)r)[1](r);
        }
    }
    return true;
}

// ===========================================================================
// @ 0x0076b1f0  element assignment (0x28 bytes, float fields)
// ===========================================================================
struct E28 {
    int a0, a4;
    float f8, fc, f10, f14;
    unsigned char b18, b19;
    int i1c, i20, i24;
    E28& operator=(const E28& o);
};
E28& E28::operator=(const E28& o) {
    a0 = o.a0; a4 = o.a4;
    f8 = o.f8; fc = o.fc; f10 = o.f10; f14 = o.f14;
    b18 = o.b18; b19 = o.b19;
    i1c = o.i1c; i20 = o.i20; i24 = o.i24;
    return *this;
}

// ===========================================================================
// @ 0x0076b240  refresh cube-map faces and capture
// ===========================================================================
bool __fastcall RefreshCubeMap(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    void* v = *(void**)(s + 0x70);
    int r = ((int(__thiscall**)(void*))*(void***)v)[0x80 / 4](v);
    if (r)
        FUN_00761110((void*)r);
    void* raster = CreateRaster(*(int*)(s + 0x50), *(int*)(s + 0x50), 1, 0x1208, 0x15);
    for (int i = 0; i < 6; i++) {
        char out[8] = {0};
        *(char*)((char*)raster + 0x12) = (char)i;
        if (FUN_011ef750r(out, 0, 2, raster)) {
            void* m = *(void**)(s + 0x6c);
            ((void(__thiscall**)(void*, char*, char*, char*))*(void***)m)[0xc](m, s + 0xc, s + 0x10, out);
            FUN_011ef880r(raster, out);
        }
    }
    void* m2 = *(void**)(s + 0x70);
    ((void(__thiscall**)(void*, void*))*(void***)m2)[0x94 / 4](m2, raster);
    void* m3 = *(void**)(s + 0x6c);
    ((void(__thiscall**)(void*, char*, char*))*(void***)m3)[5](m3, s + 0xc, s + 0x10);
    if (*(char*)(s + 0x5d))
        SetCubeMap(raster, *(void**)(s + 0x50), *(unsigned char*)(s + 0x5c), *(int*)(s + 0x58), 0);
    if (*(void**)(s + 0x60) && MessageServer()) {
        void* ms = MessageServer();
        ((void(__thiscall**)(void*, void*, int, int, int))*(void***)ms)[6](ms, *(void**)(s + 0x60), 0, 0, 0);
    }
    void* m4 = *(void**)(s + 0x70);
    ((void(__thiscall**)(void*, int))*(void***)m4)[0x44 / 4](m4, 0);
    return true;
}

// ===========================================================================
// @ 0x0076b350  ctor (0x2-vtable class)
// ===========================================================================
struct B1_350 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); };
struct B2_350 { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); };
struct D350 : B1_350, B2_350 {
    int m8;                   // +8
    int mc, m10, m14;
    int m1c, m20;             // +0x1c
    char pad24[0x118];
    int m13c;                 // +0x13c
    D350();
    virtual ~D350();
};
D350::D350() {
    m8 = 0; mc = 0; m10 = 0; m14 = 0;
    m1c = -1; m20 = -1;
    m13c = 0;
}
D350::~D350() {
    if (m13c) JobRelease((void*)m13c);
    if (mc) ((void(__thiscall**)(void*))*(void***)mc)[1]((void*)mc);
    if (m10) ((void(__thiscall**)(void*))*(void***)m10)[1]((void*)m10);
    if (m14) ((void(__thiscall**)(void*))*(void***)m14)[1]((void*)m14);
}
void DeleteD350(D350* p) { delete p; }

// ===========================================================================
// @ 0x0076b460  ctor with a 0x2c-byte argument block + refcounted member set
// ===========================================================================
void __fastcall Ctor76b460(void* self, int, int a4, int a5, int a6, int a7, int a8,
                           int a9, int a10, int a11, int a12) {
    char* s = (char*)self;
    void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* o = q ? NewPhys(q) : 0;
    *(void**)(s + 0x18) = o;
    InitPhysics(o, 0);
    *(int*)(s + 0x1c) = a4;
    *(int*)(s + 0x20) = a5;
    // refcounted pointer swaps (approximated)
    *(int*)(s + 0x28) = a6;
    *(int*)(s + 0x2c) = a7;
    *(int*)(s + 0x30) = a8;
    *(char*)(s + 0x24) = (char)a9;
    *(char*)(s + 0x138) = (char)(int)(size_t)(void*)a10;
    *(char*)(s + 0x139) = (char)a11;
    (void)a12;
}

// ===========================================================================
// @ 0x0076b5d0  reset viewer references
// ===========================================================================
void __fastcall ResetRefs76bs(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    if (*(void**)(s + 0x13c)) {
        void* p = *(void**)(s + 0x13c);
        if (p) { *(void**)(s + 0x13c) = 0; JobRelease(p); }
    }
    if (*(void**)(s + 0x18)) {
        PhysFini(*(void**)(s + 0x18));
        void* p = *(void**)(s + 0x18);
        if (p) { PhysDel(p); Dealloc(p); }
    }
    if (*(void**)(s + 0xc)) { void* p = *(void**)(s + 0xc); *(void**)(s + 0xc) = 0; ((void(__thiscall**)(void*))*(void***)p)[1](p); }
    if (*(void**)(s + 0x10)) { void* p = *(void**)(s + 0x10); *(void**)(s + 0x10) = 0; ((void(__thiscall**)(void*))*(void***)p)[1](p); }
    if (*(void**)(s + 0x14)) { void* p = *(void**)(s + 0x14); *(void**)(s + 0x14) = 0; ((void(__thiscall**)(void*))*(void***)p)[1](p); }
}

// ===========================================================================
// @ 0x0076b660  ctor (2-vtable class)
// ===========================================================================
struct B1_660 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); };
struct B2_660 { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); };
struct D660 : B1_660, B2_660 {
    int m8;
    int mc, m10, m14, m18;
    D660();
    virtual ~D660();
};
D660::D660() {
    m8 = 0; mc = 0; m10 = 0; m14 = -1; m18 = -1;
}
D660::~D660() { if (mc) ((void(__thiscall**)(void*))*(void***)mc)[1]((void*)mc); }
void DeleteD660(D660* p) { delete p; }

// ===========================================================================
// @ 0x0076b720  ctor: copy a viewer and attach refcounted resources
// ===========================================================================
void __fastcall Ctor76b720(void* self, int, int a2, int a3, int a4, int a5, int a6, char a7, int a8) {
    char* s = (char*)self;
    void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* o = q ? NewPhys(q) : 0;
    *(void**)(s + 0x10) = o;
    InitPhysics(o, 0);
    CopyViewer(o, (void*)a2, 0, 0);
    *(int*)(s + 0x14) = a3;
    *(int*)(s + 0x18) = a4;
    void* src = (void*)a5;
    if (src) ((void(__thiscall**)(void*))*(void***)src)[0](src);
    *(void**)(s + 0xc) = src;
    (void)a6;
    *(char*)(s + 0x1c) = a7;
    *(int*)(s + 0x20) = a8;
}

// ===========================================================================
// @ 0x0076b840  release a viewer instance
// ===========================================================================
void __fastcall ReleaseViewer76b8(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    void* p = *(void**)(s + 0x10);
    if (p) {
        PhysFini(p);
        void* q = *(void**)(s + 0x10);
        if (q) { PhysDel(q); Dealloc(q); }
    }
    void* r = *(void**)(s + 0xc);
    if (r) {
        *(void**)(s + 0xc) = 0;
        ((void(__thiscall**)(void*))*(void***)r)[1](r);
    }
}

// ===========================================================================
// @ 0x0076b890  render/serialize a viewer
// ===========================================================================
void __fastcall RenderViewer76b8(void* self, int, void* a2, void* a3, void* a4) {
    char* s = (char*)self;
    if (!*(void**)(s + 0xc))
        return;
    FUN_7c4be0(*(void**)(s + 0x10), s + 0x14, 1);
    void* m = App6740();
    ((void(__thiscall**)(void*, int))*(void***)m)[0x44 / 4](m, 1);
    void* m2 = App6740();
    ((void(__thiscall**)(void*, char*))*(void***)m2)[0x9c / 4](m2, s + 0x14);
    void* c = *(void**)(s + 0xc);
    int zero[3] = {0, 0, 0};
    ((void(__thiscall**)(void*, void*, void*, void*, void*))*(void***)c)[3](c, a2, a3, a4, zero);
    void* m3 = App6740();
    ((void(__thiscall**)(void*, int))*(void***)m3)[0x44 / 4](m3, 0);
}

// ===========================================================================
// @ 0x0076b930  build a quaternion from a 3x3 matrix
// ===========================================================================
void* __stdcall QuatFromBasis(void* out, void* src, float w) {
    int m[12];
    m[0] = *(int*)((char*)src + 0);
    m[1] = *(int*)((char*)src + 4);
    m[2] = *(int*)((char*)src + 8);
    m[3] = *(int*)((char*)src + 0xc);
    m[4] = *(int*)((char*)src + 0x10);
    m[5] = *(int*)((char*)src + 0x14);
    m[6] = *(int*)((char*)src + 0x18);
    m[7] = *(int*)((char*)src + 0x1c);
    m[8] = *(int*)((char*)src + 0x20);
    m[9] = *(int*)((char*)src + 0x24);
    m[10] = *(int*)((char*)src + 0x28);
    QuatFromMatrix(out, m, w, (int)(size_t)src);
    return out;
}

// ===========================================================================
// @ 0x0076b9a0  copy a range of 0x28-byte elements
// ===========================================================================
E28* __cdecl CopyRange28(E28* first, E28* last, E28* dest) {
    E28* d = dest;
    while (first != last) {
        if (d)
            *d = *first;
        first = (E28*)((char*)first + 0x28);
        d = (E28*)((char*)d + 0x28);
    }
    return d;
}

// ===========================================================================
// @ 0x0076ba30  capture a cube map from a viewer basis
// ===========================================================================
void __fastcall CaptureCubeMap76ba(void* self, int, void* a1, void* a2, void* a3,
                                   int a4, char a5, int a6, void* a7, char a8,
                                   void* a9, int a10) {
    char* s = (char*)self;
    float zero[3] = {0, 0, 0};
    *(int*)(s + 0x44) = *(int*)&zero[0];
    *(int*)(s + 0x48) = *(int*)&zero[1];
    *(int*)(s + 0x4c) = *(int*)&zero[2];
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6; (void)a7; (void)a8; (void)a9; (void)a10;
}
