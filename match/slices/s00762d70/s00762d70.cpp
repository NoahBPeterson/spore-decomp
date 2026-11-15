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
static inline void VCall3(void* self, int off, int a, int b, int c) {
    ((void(__thiscall*)(void*, int, int, int))(*(void***)self)[off / 4])(self, a, b, c);
}
static inline void VCallA(void* self, int off, int a, int b, int c, int d, int e) {
    ((void(__thiscall*)(void*, int, int, int, int, int))(*(void***)self)[off / 4])(self, a, b, c, d, e);
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
    bool ReadResourcePCAWeights(void* stream, void* resource, const void* key);  // 00763950
};

struct cRasterFromGimexLoadState {
    uint32_t mFormat; uint32_t mWidth; uint32_t mHeight;
    uint32_t mBpp; uint32_t mPitch; uint32_t mSize; unsigned char* mData;
};

} // namespace SP
using SP::cRasterFromGimexLoadState;

// ===========================================================================
// @ 0x00762d70  container teardown for arrays of local-light records (SEH)
extern "C" void* __cdecl F_11f3130(void* vtable);   // 0x011f3130 add-ref vtable
extern "C" void* __cdecl F_11f3580(void* item);     // 0x011f3580 release
extern "C" void* __cdecl F_11f4e90(void* obj);      // 0x011f4e90 release
extern "C" void  __cdecl F_9276c0(void* mgr, void* p); // 0x009276c0
extern "C" void  __cdecl F_762890(void* slot, void* out); // 0x00762890
extern "C" void  __cdecl F_6c1570(void* vec, void* pos, void* val); // 0x006c1570 vector push
extern void* g_mgr16c8b44;                          // 0x016c8b44

void __cdecl TeardownLightArrays(int count, void** arrays) {
    void*  vec[3] = { 0, 0, 0 };   // scratch set of already-seen items
    for (int i = 0; i < count; i++) {
        int* arr = (int*)arrays[i];
        int  n   = arr[4];
        for (int j = 0; j < n; j++) {
            void* item = *(void**)((char*)arr + 0x24 + j * 4);
            bool found = false;
            for (void** it = (void**)vec[0]; it != (void**)vec[1]; ++it)
                if (*it == item) { found = true; break; }
            if (found)
                continue;
            F_11f3130(*(void**)item);                     // add-ref
            F_9276c0(g_mgr16c8b44, *(void**)item);
            void* tmp = item;
            F_762890((void*)0x1538ff0, &tmp);
            F_11f3580(item);                              // release
            F_9276c0(g_mgr16c8b44, item);
            if (vec[1] == vec[2]) {
                F_6c1570(vec, vec[1], &item);
            } else {
                *(void**)vec[1] = item;
                vec[1] = (char*)vec[1] + 4;
            }
        }
        void* obj8 = *(void**)((char*)arr + 8);
        void* tmp8 = obj8;
        F_762890((void*)0x1539010, &tmp8);
        F_11f4e90(obj8);
        F_9276c0(g_mgr16c8b44, obj8);
        F_9276c0(g_mgr16c8b44, arr);
    }
    if (vec[0] != 0 && vec[0] != (void*)0)
        EA_Delete(vec[0]);
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
// @ 0x00762fa0  locked map insert (thiscall, ret 8); 64-bit lock-free counter
struct Map762fa0 {
    int field0; int field4; int field8; int fieldC;
    void* Insert(void* out, const void* key);   // 0x00762fa0
    void  Append(const void* key);              // 0x00763130
};
extern "C" void* __fastcall F_68c140(const void* key8);                       // 0x0068c140 AtomicRead64
extern "C" void  __fastcall F_68c1b0(const void* key8, unsigned __int64 val); // 0x0068c1b0 AtomicExchange64

void* Map762fa0::Insert(void* out, const void* key) {
    unsigned __int64 node8 = *(const unsigned __int64*)((char*)this + 0);
    void* slot = F_68c140(&node8);
    if (slot == 0) {
        void* obj = MakeObj762f30((const int*)key);
        F_68c1b0(out, (unsigned __int64)(size_t)obj);
        return out;
    }
    for (;;) {
        void* e = F_68c140(&node8);
        unsigned __int64 inner = *(unsigned __int64*)((char*)e + 8);
        void* cur = F_68c140(&inner);
        unsigned __int64 oldv = *(unsigned __int64*)&node8;
        (void)cur; (void)oldv;
        unsigned __int64 nw = node8 + 1;
        unsigned __int64 prev = *(volatile unsigned __int64*)((char*)this + 0);
        if (_InterlockedCompareExchange64((volatile __int64*)((char*)this + 0),
                (__int64)nw, (__int64)prev) == (__int64)prev) {
            unsigned __int64 z = 0;
            F_68c1b0(&z, 0);
            void* e3 = F_68c140(&node8);
            *(int*)((char*)e3 + 8)  = (int)(nw & 0xffffffffu);
            *(int*)((char*)e3 + 0xc) = (int)(nw >> 32);
            if (key) {
                *(int*)((char*)e3 + 0) = *(const int*)key;
                *(int*)((char*)e3 + 4) = *((const int*)key + 1);
            }
            *(unsigned __int64*)out = node8;
            return out;
        }
    }
}

// ===========================================================================
// @ 0x00763130  locked map append (thiscall, ret 4)
void Map762fa0::Append(const void* key) {
    int out[2];
    Insert(out, key);
    const int* k = (const int*)key;
    unsigned __int64 node8 = *(const unsigned __int64*)k;
    for (;;) {
        void* e = F_68c140(&node8);
        unsigned __int64 inner = *(unsigned __int64*)((char*)e + 8);
        void* e2 = F_68c140(&inner);
        *(int*)((char*)e2 + 8) = k[0];
        *(int*)((char*)e2 + 0xc) = k[1];
        unsigned __int64 nw = node8 + 1;
        unsigned __int64 prev = *(volatile unsigned __int64*)((char*)this + 8);
        if (_InterlockedCompareExchange64((volatile __int64*)((char*)this + 8),
                (__int64)nw, (__int64)prev) == (__int64)prev)
            return;
    }
}

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
    void* p = self;
    volatile int* rc = (volatile int*)((char*)p + 4);
    int n = _InterlockedExchangeAdd((volatile long*)rc, -2) - 2;
    if (n == 0) {
        _InterlockedExchange((volatile long*)rc, 2);
        int tid = (int)__readfsdword(0x18);
        if (g_flags1630180 != 0 || g_word160077c != tid) {
            Map762fa0* map = (Map762fa0*)GetGlobal67de80();
            int key[2];
            key[0] = (int)p;
            key[1] = 0x762f10;
            map->Append(key);
        } else if (p != 0) {
            ((IObj*)p)->s2(1);
        }
    } else if (n == 3) {
        char* slot = (char*)p + 0x14;
        if (*(void**)slot != 0) {
            void* cb = *(void**)slot;
            void* fn = *(void**)*(void**)cb;
            ((void(__thiscall*)(void*, void*))fn)(cb, p);
        }
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
// @ 0x00763620  Gimex raster header load (thiscall, ret 0xc)
extern "C" void  __cdecl F_87cde0(void* stream);                                  // 0x0087cde0 stream ctor
extern "C" bool  __cdecl F_87ce00(void* stream, const char* name);                // 0x0087ce00 open
extern "C" bool  __cdecl F_87d0b0(void* stream, void* a, void* b);                // 0x0087d0b0 read header
extern "C" void* __cdecl F_87ced0(void* stream, int flags);                       // 0x0087ced0 get record
extern "C" bool  __cdecl F_87cf00(void* stream, void* rec, void* dst, int size);  // 0x0087cf00 decompress
extern "C" void  __cdecl F_87cef0(void* stream, void* rec);                       // 0x0087cef0 release record
extern "C" void  __cdecl F_87ce90(void* stream);                                  // 0x0087ce90
extern "C" void  __cdecl F_87d070(void* stream);                                  // 0x0087d070 dtor/closer

struct GimexRecord { char pad[0x10]; int mWidth; int mHeight; int mBpp; };
struct StreamObj { char pad[0x20]; };

bool __stdcall LoadRasterHeader(cRasterFromGimexLoadState* s, const char* name, void* unused) {
    StreamObj stream;
    F_87cde0(&stream);
    if (!F_87ce00(&stream, name)) {
        F_87d070(&stream);
        return false;
    }
    char inner[4];
    if (!F_87d0b0(&stream, (void*)name, inner)) {
        F_87d070(&stream);
        return false;
    }
    GimexRecord* rec = (GimexRecord*)F_87ced0(&stream, 0);
    bool ok = false;
    if (rec != 0 && rec->mBpp == 0x20) {
        s->mWidth  = rec->mWidth;
        s->mHeight = rec->mHeight;
        s->mBpp    = 0x20;
        s->mPitch  = rec->mWidth * 4;
        s->mSize   = s->mPitch * s->mHeight;
        s->mData   = (unsigned char*)EA_New(s->mSize, (const char*)0x140e02c, 0, 0, 0, 0);
        ok = F_87cf00(&stream, rec, s->mData, s->mSize);
        F_87cef0(&stream, rec);
    }
    F_87ce90(&stream);
    F_87d070(&stream);
    (void)unused;
    return ok;
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
// @ 0x007637d0  load header + create raster (thiscall, ret 0x10)
struct RasterFactory {
    bool LoadAndCreateRaster(cRasterFromGimexLoadState* state, int a, int b, void* out3);
};

bool RasterFactory::LoadAndCreateRaster(cRasterFromGimexLoadState* state, int a, int b, void* out3) {
    char  buf[0x1c];
    *(int*)(buf + 0x10) = 0;
    if (!LoadRasterHeader((cRasterFromGimexLoadState*)buf, 0, 0))
        return false;
    // NB: the original allocates a small scratch vector at [esp+0x24] here
    if (!CreateRasterFromState((cRasterFromGimexLoadState*)buf, 0, 0))
        return false;
    int* src = (int*)out3;
    ((int*)b)[2] = src[0];
    ((int*)b)[3] = src[1];
    ((int*)b)[4] = src[2];
    (void)state; (void)a;
    return true;
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
// @ 0x00763950  read the Gimex PCA-weight header (thiscall, ret 0xc)
bool SP::cGraphicsResourceFactory::ReadResourcePCAWeights(void* stream, void* resource, const void* key) {
    (void)key;
    char* res = (char*)resource;
    int   hdr[6];
    int   flag = 0;
    int   tag;
    if (!EA_IO_ReadInt32(stream, &tag, 1, flag))
        return false;
    if (tag == (int)0xeeffeeff)      flag = 1;
    else if (tag == (int)0xffeeffee) flag = 0;
    else return false;
    if (!EA_IO_ReadInt32(stream, &hdr[1], 1, flag)) return false;
    if (hdr[1] != 2) return false;
    if (!EA_IO_ReadInt32(stream, &hdr[0], 1, flag)) return false;
    if (hdr[0] > 4) return false;
    int* pGroup = (int*)(res + 0x18);
    if (!EA_IO_ReadInt32(stream, pGroup, 1, flag)) return false;
    if (*pGroup > 0x3c) return false;
    if (!EA_IO_ReadInt32(stream, &hdr[2], 1, flag)) return false;
    if (hdr[2] != 0x10) return false;
    if (!EA_IO_ReadInt32(stream, &hdr[3], 1, flag)) return false;
    if (hdr[3] != 2) return false;
    int count = (*pGroup * 0x110) >> 2;
    if (!EA_IO_ReadInt32(stream, res + 0x24, count, flag)) return false;
    *(float*)(res + 4) = *(float*)0x14853e0;
    *(unsigned char*)(res + 8) = 1;
    return true;
}

// ===========================================================================
// @ 0x00763a80  resource arena write (stdcall-ish; thiscall in ecx folds the resource)
extern "C" void* __cdecl F_11e2fe0(void* scope);                       // 0x011e2fe0 scope ctor
extern "C" bool  __cdecl F_11e3350(void* stream, void* out, int flags);// 0x011e3350 begin
extern "C" bool  __cdecl F_11e34d0(void* scope);                       // 0x011e34d0 advance
extern "C" bool  __cdecl F_11e3c50(void* scope, void* cb);             // 0x011e3c50 set callback
extern "C" bool  __cdecl F_11e3940(void* scope);                       // 0x011e3940 advance
extern "C" void  __cdecl F_11e2690(void* scope);                       // 0x011e2690 scope dtor

bool __stdcall WriteResourceArena(int* res, int flags) {
    void* stream = *(void**)((char*)res + 0x18);
    char  scope[0x130];
    F_11e2fe0(scope);
    void* arena = 0;
    if (!F_11e3350(stream, &arena, 0)) {
        F_11e2690(scope);
        return false;
    }
    while (F_11e34d0(scope)) { }
    g_arena16303f0 = arena;
    if (!F_11e3c50(scope, (void*)0x763490)) {
        F_11e2690(scope);
        return false;
    }
    while (F_11e3940(scope)) { }
    g_arena16303f0 = 0;
    F_11e2690(scope);
    (void)flags;
    return true;
}

// ===========================================================================
// @ 0x00763b80  draw/upload raster (cdecl, 4 args)
extern "C" void* __cdecl F_11e0744(void* dst, void* src, int n);       // 0x011e0744 memcpy-ish
extern void* g_dev16f89d0;                                            // 0x016f89d0 device singleton

bool __cdecl DrawRaster(void* a, int b, int c, unsigned char d) {
    char* p = (char*)a;
    void* tex = *(void**)(p + 8);
    int   v0  = 0;
    ((void(__thiscall*)(void*, int, int, int))((*(void***)tex)[0x48 / 4]))(
        tex, *(unsigned char*)(p + 0x12), (int)d, (int)&v0);
    void* obj = (void*)v0;
    int   width  = *(unsigned short*)(p + 0xc);
    int   height = *(unsigned short*)(p + 0xe);
    char  local[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    ((void(__thiscall*)(void*, void*))((*(void***)obj)[0x30 / 4]))(obj, local);
    void* dev = *(void**)g_dev16f89d0;
    ((void(__thiscall*)(void*, int, int, int, int, int))((*(void***)dev)[0x90 / 4]))(
        dev, width, height, *(int*)local, 2, (int)local);
    ((void(__thiscall*)(void*, int))((*(void***)dev)[0x80 / 4]))(dev, v0);
    ((void(__thiscall*)(void*, void*, int, int))((*(void***)obj)[0x34 / 4]))(obj, local, 0, 0x10);
    F_11e0744((void*)b, (void*)*(int*)(local + 4), *(int*)local * height);
    ((void(__thiscall*)(void*))((*(void***)obj)[0x38 / 4]))(obj);
    ((void(__thiscall*)(void*))((*(void***)obj)[8 / 4]))((void*)v0);
    ((void(__thiscall*)(void*))((*(void***)tex)[8 / 4]))(tex);
    (void)c;
    return true;
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
