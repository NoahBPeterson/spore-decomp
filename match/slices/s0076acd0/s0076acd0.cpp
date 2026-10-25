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
void  __fastcall InitPhysics(void* self, int unused, int v);               // 0x7c4dd0
void* __fastcall NewPhys(void* self, int unused);                          // 0x7c3f70
void  __fastcall PhysFini(void* self, int unused);                         // 0x7c3ba0
void  __fastcall PhysDel(void* self, int unused);                          // 0x7c4000
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
void  __cdecl QuatFromMatrix(void* out, void* m, float f);          // 0x472b80
void  __cdecl Matrix3Assign(void* p, void* src);                           // 0x41cb40
void  __cdecl Basis3Build(void* out, void* a, void* b);                    // 0x6b9440
void  __cdecl CaptureCubeMap(void* worlds, float* w, void* center, int size, float nearDist,
                             float farDist, void* dir, int flags);          // 0x6e4210
extern float g_f1630698;                                         // 0x01630698
extern float g_f163069c;                                         // 0x0163069c
extern float g_f16306a0;                                         // 0x016306a0
extern float g_m16307d8;                                         // 0x016307d8
extern char vtbl_13eb938[];
extern char vtbl_13ec458[];
extern char vtbl_140e254[];
extern char vtbl_140e244[];
extern char vtbl_140e278[];
extern char vtbl_140e268[];
}

// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Matrix33 { void Assign(const void* src); };   // 0x0041cb40
struct cSPTransform {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    Vec3 mTranslation;                  // +0x04
    float mScale;                       // +0x10
    float mRotation[9];                 // +0x14
};

// SP::cRTTCapture - the cube-map capture object (0x174 bytes of state).
struct RTTCapture {
    void* mVt0;              // +0x00
    void* mVt1;              // +0x04
    void* mListenerBase;     // +0x08 base address handed to the message server
    void* mRes0c;            // +0x0c refcounted resource
    void* mRes10;            // +0x10 refcounted resource
    void* mPhysA[6];         // +0x14 six physics worlds (mode 0)
    void* mPhysB[6];         // +0x2c six physics worlds (mode 1)
    float mBasis[3];         // +0x44
    int   mFaceSize;         // +0x50 face dimension
    unsigned char m54;       // +0x54
    int   m58;               // +0x58
    unsigned char m5c;       // +0x5c
    unsigned char m5d;       // +0x5d
    void* m60;               // +0x60
    void* mPhysMain;         // +0x64 main physics world
    int   m68;               // +0x68
    void* mRenderTarget;     // +0x6c
    void* mRenderCtx;        // +0x70
    unsigned char pad74[0x9c - 0x74];
    void* mRes9c;            // +0x9c refcounted resource
};

// Refcounted pointer swap used by the viewer constructor.
static void SwapRefOwner(void** slot, void* value)
{
    void* old = *slot;
    if (value != old) {
        if (value) {                                                        // AddRef (vtable slot 0)
            void* vt = *(void**)value;
            ((void(__cdecl*)(void))*(void**)vt)();
        }
        *slot = value;
        if (old) {                                                          // Release (vtable slot 1)
            void* vt = *(void**)old;
            ((void(__cdecl*)(void))*((void**)((char*)vt + 4)))();
        }
    }
}

// @ 0x0076acd0  register a graphics-resource message listener
// ---------------------------------------------------------------------------
bool __fastcall RegisterListener(RTTCapture* self, int unused) {
    (void)unused;
    void* ms = MessageServer();
    if (ms) {
        static const int tags[9] = {0x1c91267, 0x3ea7e1b, 0x1c7f3db, 0x1c7f90a, 0x1c7fd85,
                                    0x202ce02, 0x1fb2458, 0x1c91276, 0x1c9127b};
        void* base = self ? &self->mListenerBase : 0;
        for (int i = 0; i < 9; i++)
            ((void(__thiscall**)(void*, void*, int))*(void***)ms)[8](ms, base, tags[i]);
    }
    void* a = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* obj = a ? NewPhys(a, 0) : 0;
    self->mPhysMain = obj;
    InitPhysics(obj, 0, 0);
    for (int i = 0; i < 6; i++) {
        void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
        void* o = q ? NewPhys(q, 0) : 0;
        self->mPhysA[i] = o;
        InitPhysics(o, 0, 0);
        FUN_7c53d0(o, 90.0f);
    }
    for (int i = 0; i < 6; i++) {
        void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
        void* o = q ? NewPhys(q, 0) : 0;
        self->mPhysB[i] = o;
        InitPhysics(o, 0, 1);
        FUN_7c53d0(o, 90.0f);
        FUN_7c4ba0(o, 2.0f);
    }
    void* app = App6750();
    ((void(__thiscall**)(void*))*(void***)app)[7](app);
    self->mRenderTarget = App67dda0();
    self->mRenderCtx = App6740();
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
static void FreePhysWorld(void*& slot)
{
    if (slot == 0)
        return;
    PhysFini(slot, 0);
    void* p = slot;
    if (p) {
        PhysDel(p, 0);
        Dealloc(p);
    }
}

bool __fastcall TeardownViewer(RTTCapture* self, int unused) {
    (void)unused;
    void* ms = MessageServer();
    if (ms) {
        static const int tags[9] = {0x1c91267, 0x3ea7e1b, 0x1c7f3db, 0x1c7f90a, 0x1c7fd85,
                                    0x202ce02, 0x1fb2458, 0x1c91276, 0x1c9127b};
        void* base = self ? &self->mListenerBase : 0;
        for (int i = 0; i < 9; i++)
            ((void(__thiscall**)(void*, void*, int, int))*(void***)ms)[11](ms, base, tags[i], -9999);
    }
    FreePhysWorld(self->mPhysMain);
    for (int i = 0; i < 6; i++)
        FreePhysWorld(self->mPhysA[i]);
    for (int i = 0; i < 6; i++)
        FreePhysWorld(self->mPhysB[i]);
    int* r = (int*)self->mRes9c;
    if (r) {
        ((void(__thiscall**)(int*, int))*(void***)r)[3](r, 0);
        r = (int*)self->mRes9c;
        if (r) {
            self->mRes9c = 0;
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
struct D350 {
    void* vtbl0;              // +0
    void* vtbl1;              // +4
    int m8;                   // +8
    int mc, m10, m14;
    int pad18;                // +0x18
    int m1c, m20;             // +0x1c
    char pad24[0x118];
    int m13c;                 // +0x13c
    D350();
    ~D350();
};
D350::D350() {
    vtbl1 = vtbl_13ec458;
    m8 = 0;
    vtbl0 = vtbl_140e254;
    vtbl1 = vtbl_140e244;
    mc = 0; m10 = 0; m14 = 0;
    m1c = -1; m20 = -1;
    m13c = 0;
}
// @ 0x0076b3c0
D350::~D350() {
    if (m13c)
        ((void(__thiscall*)(void*))JobRelease)((void*)m13c);
    if (m14)
        ((void(__thiscall**)(void*))*(void***)m14)[1]((void*)m14);
    if (m10)
        ((void(__thiscall**)(void*))*(void***)m10)[1]((void*)m10);
    if (mc)
        ((void(__thiscall**)(void*))*(void***)mc)[1]((void*)mc);
    vtbl0 = vtbl_13eb938;
    vtbl1 = vtbl_13ec458;
}
void DeleteD350(D350* p) { delete p; }

// ===========================================================================
// @ 0x0076b460  ctor with a 0x2c-byte argument block + refcounted member set
// ===========================================================================
// Editor resource viewer (the class whose ctor/dtor/render helpers follow).
struct Viewer76 {
    void* mVt0;                 // +0x00
    void* mVt1;                 // +0x04
    void* m8;                   // +0x08
    void* mRes0c;               // +0x0c refcounted resource
    void* mRes10;               // +0x10 refcounted resource
    void* mRes14;               // +0x14 refcounted resource
    void* mPhys18;              // +0x18 physics world
    int   m1c;                  // +0x1c
    int   m20;                  // +0x20
    unsigned char m24;          // +0x24
    int   m28;                  // +0x28
    int   m2c;                  // +0x2c
    int   m30;                  // +0x30
    char  mName[0x138 - 0x34];  // +0x34 resource name
    unsigned char mHasName;     // +0x138
    unsigned char m139;         // +0x139
    void* mJob13c;              // +0x13c refcounted render job
};

void __fastcall Ctor76b460(Viewer76* self, int unused, int* block, void* res0c, void* res10,
                           void* res14, int a6, int a7, const char* name, int a9,
                           unsigned char a10, int a11, unsigned char a12) {
    (void)unused;
    void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* o = q ? NewPhys(q, 0) : 0;
    self->mPhys18 = o;
    InitPhysics(o, 0, 0);
    self->m1c = block[0];
    self->m20 = block[1];
    SwapRefOwner(&self->mRes0c, res0c);
    SwapRefOwner(&self->mRes10, res10);
    SwapRefOwner(&self->mRes14, res14);
    self->m24 = a10;
    self->m30 = a7;
    self->m28 = a11;
    self->m2c = a6;
    self->mHasName = a9 != 0;
    self->m139 = a12;
    if (name) {
        char* d = self->mName;
        do { *d++ = *name; } while (*name++);
    } else {
        self->mName[0] = 0;
    }
}

// ===========================================================================
// @ 0x0076b5d0  reset viewer references
// ===========================================================================
void __fastcall ResetRefs76bs(void* self) {
    char* s = (char*)self;
    if (*(void**)(s + 0x13c)) {
        void* p = *(void**)(s + 0x13c);
        if (p) { *(void**)(s + 0x13c) = 0; ((void(__thiscall*)(void*))JobRelease)(p); }
    }
    if (*(void**)(s + 0x18)) {
        ((void(__thiscall*)(void*))PhysFini)(*(void**)(s + 0x18));
        void* p = *(void**)(s + 0x18);
        if (p) { ((void(__thiscall*)(void*))PhysDel)(p); Dealloc(p); }
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
struct D660 {
    void* vtbl0;              // +0
    void* vtbl1;              // +4
    int m8;                   // +8
    int mc, m10, m14, m18;
    D660();
    ~D660();
};
D660::D660() {
    vtbl1 = vtbl_13ec458;
    m8 = 0;
    vtbl0 = vtbl_140e278;
    vtbl1 = vtbl_140e268;
    mc = 0; m10 = 0;
    m14 = -1; m18 = -1;
}
// @ 0x0076b6c0
D660::~D660() {
    if (mc)
        ((void(__thiscall**)(void*))*(void***)mc)[1]((void*)mc);
    vtbl0 = vtbl_13eb938;
    vtbl1 = vtbl_13ec458;
}
void DeleteD660(D660* p) { delete p; }

// ===========================================================================
// @ 0x0076b720  ctor: copy a viewer and attach refcounted resources
// ===========================================================================
void __fastcall Ctor76b720(void* self, int, int a2, int a3, int* a4, void* a5, char a6) {
    char* s = (char*)self;
    volatile int pad[4];
    pad[0] = 0;
    void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* o = q ? ((void*(__thiscall*)(void*))NewPhys)(q) : 0;
    *(void**)(s + 0x10) = o;
    ((void(__thiscall*)(void*, int))InitPhysics)(o, 0);
    ((void(__thiscall*)(void*, void*, int, int))CopyViewer)(o, (void*)a3, 0, 0);
    *(int*)(s + 0x14) = a4[0];
    *(int*)(s + 0x18) = a4[1];
    void* old = *(void**)(s + 0xc);
    if (a5 != old) {
        if (a5) ((void(__thiscall**)(void*))*(void***)a5)[0](a5);
        *(void**)(s + 0xc) = a5;
        if (old) ((void(__thiscall**)(void*))*(void***)old)[1](old);
    }
    *(char*)(s + 0x1c) = a6;
    *(int*)(s + 0x20) = a2;
}

// ===========================================================================
// @ 0x0076b840  release a viewer instance
// ===========================================================================
void __fastcall ReleaseViewer76b8(void* self) {
    char* s = (char*)self;
    void* p = *(void**)(s + 0x10);
    if (p) {
        ((void(__thiscall*)(void*))PhysFini)(p);
        void* q = *(void**)(s + 0x10);
        if (q) { ((void(__thiscall*)(void*))PhysDel)(q); Dealloc(q); }
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
void __fastcall RenderViewer76b8(void* self, int, void* a2, void* a3, void* a4, void* a5) {
    char* s = (char*)self;
    if (!*(void**)(s + 0xc))
        return;
    ((void(__thiscall*)(void*, void*, int))FUN_7c4be0)(*(void**)(s + 0x10), s + 0x14, 1);
    void* m = App6740();
    ((void(__thiscall**)(void*, int))*(void***)m)[0x44 / 4](m, 1);
    void* m2 = App6740();
    ((void(__thiscall**)(void*, char*))*(void***)m2)[0x9c / 4](m2, s + 0x14);
    void* c = *(void**)(s + 0xc);
    int data[4];
    data[0] = *(int*)(s + 0x10);
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    ((void(__thiscall**)(void*, void*, void*, int*, void*))*(void***)c)[3](c, a2, a3, data, a5);
    void* m3 = App6740();
    ((void(__thiscall**)(void*, int))*(void***)m3)[0x44 / 4](m3, 0);
    (void)a4;
}

// ===========================================================================
// @ 0x0076b930  build a quaternion from a 3x3 matrix
// ===========================================================================
void* __cdecl QuatFromBasis(void* out, void* src, float w) {
    float m[9];
    int* s9 = (int*)src;
    m[0] = *(float*)&s9[0];
    m[1] = *(float*)&s9[1];
    m[2] = *(float*)&s9[2];
    m[3] = *(float*)&s9[4];
    m[4] = *(float*)&s9[5];
    m[5] = *(float*)&s9[6];
    m[6] = *(float*)&s9[8];
    m[7] = *(float*)&s9[9];
    m[8] = *(float*)&s9[10];
    QuatFromMatrix(out, m, w);
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
void __fastcall CaptureCubeMap76ba(RTTCapture* self, int unused, int faceSize, Vec3* center,
                                   int a4, int a5, char orient, char a7, unsigned char a8,
                                   int a9, unsigned char a10, Vec3* dir, int a12) {
    (void)unused; (void)a4; (void)a5;
    self->mBasis[0] = 0.0f;
    self->mBasis[1] = 0.0f;
    self->mBasis[2] = 0.0f;
    Vec3 from = {0.0f, 0.0f, 0.0f};
    if (center)
        from = *center;
    if (dir) {
        self->mBasis[0] = dir->x;
        self->mBasis[1] = dir->y;
        self->mBasis[2] = dir->z;
    }
    float w = 1.0f;
    if (orient) {
        cSPTransform xf;                       // orientation basis for the capture
        xf.mFlags = 0;
        xf.mModificationCount = 0;
        xf.mTranslation.x = g_f1630698;
        xf.mTranslation.y = g_f163069c;
        xf.mTranslation.z = g_f16306a0;
        xf.mScale = 1.0f;
        ((Matrix33*)xf.mRotation)->Assign(&g_m16307d8);
        int* app = (int*)App6740();
        int* ctx = (int*)(*(int(__thiscall**)(int*))(*app + 0x50))(app);
        (*(void(__thiscall**)(int*, cSPTransform*))(*ctx + 0x1c))(ctx, &xf);
        FUN_7c40f0(&xf);
        from = xf.mTranslation;
        float basis[16];                        // 4x4 basis the quaternion is read from
        Basis3Build(basis, &xf, 0);
        float* quat = (float*)QuatFromBasis(&basis[8], basis, 0.0f);
        w = quat[3];
    }
    self->m58 = a9;
    self->m54 = a8;
    self->m60 = (void*)a5;
    self->m5d = a7;
    self->mFaceSize = faceSize;
    self->m5c = a10;
    ((void(__thiscall**)(void*, int))*(void***)self->mRenderCtx)[0x44 / 4](self->mRenderCtx, 1);
    CaptureCubeMap(self->mPhysA, &w, &from, faceSize, 0.1f, 10000.0f, dir, a12);
}
