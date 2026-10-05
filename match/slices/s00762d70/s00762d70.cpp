// slice s00762d70
// SP::cGraphicsResourceFactory / cEditorResource serialization module.
// /O2 /MD /Gy /EHsc /TP
#include <intrin.h>
#include <string.h>
#include "types.h"

// ---------------------------------------------------------------------------
// externs (relocation targets; bodies live outside the slice)
// ---------------------------------------------------------------------------
extern "C" {
void* __cdecl EA_New(uint32_t size, const char* file, int a, int b, int c, int d); // 0x0f473a0
void  __cdecl EA_Delete(void* p);                                                  // 0x0f47380
bool  __cdecl EA_IO_ReadInt32(void* stream, void* dst, int count, int flags);      // 0x093a780
void  __cdecl RemoveRegistrationCallback(int id, void* cb);                        // 0x06ad070
void* __cdecl GetGlobal67dd60();                                                   // 0x067dd60
void* __cdecl GetGlobal67de80();                                                   // 0x067de80
void* __cdecl MaterialManager();                                                   // 0x067dd70
void* __cdecl CreateRasterFn(int w, int h, int a, int b, int c);                   // 0x0761420
void* __cdecl GetGlobal16c8b44();                                                  // 0x011f3130 area
}

// thiscall externs modelled as stub members (bodies out of slice)
struct RefVec {
    void* b; void* e; void* c;
    RefVec() { b = 0; e = 0; c = 0; }
    ~RefVec() { destroy(); }
    void destroy();   // 0x0041eb80
};
struct Raster { void D3D9GetStreamedMipLevelSize(unsigned char*, int); }; // 0x011f0270
struct LockMap { void read64(); void store(int, int); };             // 0x068c140 / 0x068c1b0
struct Arena { unsigned char f(void* addr, unsigned n); };           // vtbl +0x38 call
struct Obj6c { void v6c(int); void v70(int); };
struct Obj50 { void v50(int); void v54(int); };

struct IObj { virtual void s0(); virtual void s1(); virtual void s2(int); };

struct Color3 { int r, g, b; };
struct KeyDef { int a, b; int key; };

// generic virtual call helpers
static inline void VCall0(void* self, int off) {
    ((void(__thiscall*)(void*))(*(void***)self)[off / 4])(self);
}
static inline void VCall1(void* self, int off, int arg) {
    ((void(__thiscall*)(void*, int))(*(void***)self)[off / 4])(self, arg);
}

// globals
extern unsigned char g_flags1630180;   // 0x01630180
extern void* g_sAppProperties;         // 0x015fd918
extern Color3 g_colors[];              // 0x016304bc
extern void* g_arena16303f0;           // 0x016303f0
extern void* g_arena16303f4;           // 0x016303f4
extern int g_word160077c;              // 0x0160077c
extern char g_140e00c[];               // 0x0140e00c

namespace SP {

class cGraphicsResourceFactory {
public:
    bool Shutdown();                                                  // 00763520
    unsigned int GetSupportedTypes(uint32_t* types, unsigned int n);  // 00763550
    bool ReadResourcePCAWeights(void* a, void* b);                    // 00763950
};

struct cRasterFromGimexLoadState {
    uint32_t mFormat; uint32_t mWidth; uint32_t mHeight;
    uint32_t mBpp; uint32_t mPitch; uint32_t mSize; unsigned char* mData;
};

} // namespace SP
using SP::cRasterFromGimexLoadState;

// ===========================================================================
// @ 0x00762d70  (container teardown for arrays of local-light records)
void __cdecl TeardownLightArrays(int count, void** arrays) {
    (void)count; (void)arrays;
}

// ===========================================================================
// @ 0x00762f00
void __cdecl SetFlag1630180(unsigned char v) { g_flags1630180 = v; }

// @ 0x00762f10
void __cdecl ReleaseViaSlot8(IObj* p) {
    if (p) p->s2(1);
}

// ===========================================================================
// @ 0x00762f30
struct Obj762f30 { int a4, a8; };
void* __stdcall MakeObj762f30(const int* src) {
    Obj762f30* p = (Obj762f30*)EA_New(0x10, "App", 0, 0, 0, 0);
    if (src != 0) {
        if (p != 0) {
            p->a4 = src[0];
            p->a8 = src[1];
            ((LockMap*)((char*)p + 8))->store(0, 0);
            return p;
        }
    } else {
        if (p != 0) {
            ((LockMap*)((char*)p + 8))->store(0, 0);
            return p;
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00762fa0  locked map insert (partial)
struct Map762fa0 {
    void* Insert(void* out, const void* key);
    void Append(int v);
};
void* Map762fa0::Insert(void* out, const void* key) { (void)out; (void)key; return 0; }

// ===========================================================================
// @ 0x00763130  locked map append (partial)
void Map762fa0::Append(int v) { (void)v; }

// ===========================================================================
// @ 0x00763100  ctor: base vptr + zeroed fields, then derived vptr
struct IUnknown32 {
    virtual void u0(); virtual void u1(); virtual void u2();
};
struct AtomicInt {
    int v;
    int operator=(int x) { return _InterlockedExchange((volatile long*)&v, x); }
};
struct Resource : IUnknown32 {
    AtomicInt mRefCount;      // +0x4
    int mKey0, mKey1, mKey2;  // +0x8
    Resource() { mRefCount = 0; mKey0 = 0; mKey1 = 0; mKey2 = 0; }
};
struct cResourceBase : Resource {
    int* mReleaseCallback;    // +0x14
    cResourceBase() { mReleaseCallback = 0; }
};
struct CEditorRes : cResourceBase {
    RefVec mRefs;             // +0x18
    CEditorRes();
    ~CEditorRes() {}
};
CEditorRes::CEditorRes() {}
void DeleteEditorRes(CEditorRes* p) { delete p; }

// ===========================================================================
// @ 0x00763250  interlocked refcount release with deferred deletion
int __fastcall Release763250(void* self) {
    volatile int* rc = (volatile int*)((char*)self + 4);
    int n = _InterlockedExchangeAdd((volatile long*)rc, -2) - 2;
    if (n == 0) {
        _InterlockedExchange((volatile long*)rc, 2);
        if (g_flags1630180 != 0 || g_word160077c != *(int*)__readfsdword(0x18)) {
            void* o = GetGlobal67de80();
            (void)o; (void)self;
        } else if (self != 0) {
            ((IObj*)self)->s2(1);
        }
    } else if (n == 3) {
        void* p = *(void**)((char*)self + 0x14);
        if (p != 0)
            (*(void(__thiscall**)(void*, void*))p)(*(void**)p, self);
    }
    return n;
}

// ===========================================================================
// @ 0x007632f0
void __cdecl SwapRasterMode(char sel, int v) {
    if (GetGlobal67dd60() != 0) {
        void* o = GetGlobal67dd60();
        void** vt = *(void***)o;
        if (sel) {
            void* fn = vt[0x6c / 4];
            ((void(__thiscall*)(void*, int))fn)(o, v);
            void* mm = MaterialManager();
            void** mvt = *(void***)mm;
            void* mfn = mvt[0x50 / 4];
            ((void(__thiscall*)(void*, int))mfn)(mm, v);
        } else {
            void* fn = vt[0x70 / 4];
            ((void(__thiscall*)(void*, int))fn)(o, v);
            void* mm = MaterialManager();
            void** mvt = *(void***)mm;
            void* mfn = mvt[0x54 / 4];
            ((void(__thiscall*)(void*, int))mfn)(mm, v);
        }
    }
}

// ===========================================================================
// @ 0x00763340
bool __cdecl ReadRasterTriplet(void* stream, int* p, int io) {
    return EA_IO_ReadInt32(stream, p, 1, io)
        && EA_IO_ReadInt32(stream, p + 2, 1, io)
        && EA_IO_ReadInt32(stream, p + 1, 1, io);
}

// ===========================================================================
// @ 0x007633a0
void __cdecl ResolveColor(Color3* out, KeyDef* def) {
    void* p = g_sAppProperties;
    if (*(int*)((char*)(*(int*)((char*)p + 0x3c)) + 0x130) != 0) {
        int key = def->key;
        if ((key & 0xc0000000u) == 0x40000000u
            && (key & 0xff00u) == 0x2900u
            && (key & 0xffu) != 0
            && (unsigned)((((unsigned)key >> 16) & 0xff) - 0x61) <= 5u) {
            switch (((unsigned)key >> 16) & 0xff) {
            case 0x61: case 0x62: case 0x66:
                *out = g_colors[2];
                return;
            case 0x63: case 0x64: case 0x65:
                *out = g_colors[key & 0xff];
                return;
            }
        }
    }
    *out = *(Color3*)def;
}

// ===========================================================================
// @ 0x00763490  arena fixup callback
unsigned char __cdecl ArenaWrite(void* buf, int n, unsigned total) {
    unsigned char ok = 1;
    if (g_arena16303f0 == 0)
        return 0;
    if (g_arena16303f4 != 0)
        *(int*)g_arena16303f4 += n + total;
    if (total != 0) {
        while (total != 0) {
            unsigned chunk = total;
            if (total > 0x20)
                chunk = 0x20;
            ok = ((Arena*)g_arena16303f0)->f(g_140e00c, chunk);
            total -= chunk;
            if (!ok)
                return 0;
        }
        if (!ok)
            return 0;
    }
    if (n != 0)
        ok = ((Arena*)g_arena16303f0)->f(buf, n);
    return ok;
}

// ===========================================================================
// @ 0x00763520
bool SP::cGraphicsResourceFactory::Shutdown() {
    RemoveRegistrationCallback(0x2f4e681b, (void*)0x7632f0);
    return true;
}

// @ 0x00763550
unsigned int SP::cGraphicsResourceFactory::GetSupportedTypes(uint32_t* types, unsigned int n) {
    unsigned int count = 8;
    if (types != 0) {
        if (n >= count) {
            memcpy(types, (void*)0x140dfe0, 32);
        } else {
            return 0;
        }
    }
    return count;
}

// @ 0x00763580
bool __stdcall IsRegType(unsigned a, int b) {
    if (b == 0x2f4e681c && a >= 0x2f4e681b) {
        if (a <= 0x2f4e681c || a == 0x2f7d0004)
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x007635b0  destructor: _eh_vector_destructor_iterator_ over two arrays
struct EhItem { void* p; int x; ~EhItem(); };
struct EhHolder { char pad[0x44]; EhItem a[4]; EhItem b[4]; ~EhHolder(); };
EhHolder::~EhHolder() {}

// ===========================================================================
// @ 0x00763620  Gimex raster header load
bool __cdecl LoadRasterHeader(cRasterFromGimexLoadState* s, const char* name, void* unused) {
    (void)s; (void)name; (void)unused; return false;
}

// ===========================================================================
// @ 0x00763770
struct OutRaster { char pad[0x18]; void* mData; };
bool __stdcall CreateRasterFromState(cRasterFromGimexLoadState* s, int unused, OutRaster* out) {
    if (s->mBpp == 0x20 && s->mData != 0) {
        void* r = CreateRasterFn(s->mWidth, s->mHeight, 1, 8, 0x15);
        ((Raster*)r)->D3D9GetStreamedMipLevelSize(s->mData, 0);
        EA_Delete(s->mData);
        s->mData = 0;
        out->mData = r;
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x007637d0
bool __stdcall LoadAndCreateRaster(cRasterFromGimexLoadState* src, int a, int b, int* out3) {
    (void)src; (void)a; (void)b; (void)out3; return false;
}

// ===========================================================================
// @ 0x007638a0
struct V3 { int x, y, z; };
bool __stdcall ReadTriplets(void* stream, int, int, int) {
    int count;
    if (!EA_IO_ReadInt32(stream, &count, 1, 0))
        return false;
    V3 v;
    v.x = 0; v.y = 0; v.z = 0;
    for (unsigned int i = 0; i < (unsigned)count; i++) {
        if (!EA_IO_ReadInt32(stream, &v.x, 1, 0))
            return false;
        if (!EA_IO_ReadInt32(stream, &v.z, 1, 0))
            return false;
        if (!EA_IO_ReadInt32(stream, &v.y, 1, 0))
            return false;
    }
    return true;
}

// ===========================================================================
// @ 0x00763950
bool SP::cGraphicsResourceFactory::ReadResourcePCAWeights(void* a, void* b) {
    (void)a; (void)b; return false;
}

// ===========================================================================
// @ 0x00763a80  arena refix
bool __stdcall WriteResourceArena(void* a, void* b) { (void)a; (void)b; return false; }

// ===========================================================================
// @ 0x00763b80  draw raster
bool __cdecl DrawRaster(void* a, int b, int c, unsigned char d) {
    (void)a; (void)b; (void)c; (void)d; return true;
}

// ===========================================================================
// @ 0x00763c60
struct UniqVec {
    char pad[0x134];
    int mCount;
    int mArr[16];
    void AddUnique(int v);
};
void UniqVec::AddUnique(int v) {
    int n = mCount;
    if (n >= 16)
        return;
    for (int i = 0; i < n; i++) {
        if (v == mArr[i])
            return;
    }
    mArr[n] = v;
    mCount++;
}
