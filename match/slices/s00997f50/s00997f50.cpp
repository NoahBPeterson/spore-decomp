// Slice s00997f50 -- EA::UTFWinTools HitMask/RWTexture/SerCollection.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, int c, int d); // operator new
extern "C" void  FUN_0087cde0(void* a);
extern "C" char  FUN_0087ce00(void* a);
extern "C" char  FUN_0087d0b0(void* a, void* b);
extern "C" void* FUN_0087ced0(int a);
extern "C" char  FUN_0087cf00(void* a, void* b, int c);
extern "C" void  FUN_0087cef0(void* a);
extern "C" void  FUN_0087d070(void);
extern "C" void  FUN_011eff60(void);                                    // thiscall
extern "C" void  FUN_011ef750(void);                                    // thiscall
extern "C" void  FUN_011ef880(void);
extern "C" int   FUN_00928a30(void* a, void* b, int c, int d, int e, int f, int g, int h);
extern "C" void  FUN_00957c20(void* self, int v);
extern "C" void  FUN_00a80dd0(void* a, void* b);
extern "C" void* g_16c8b44;
extern "C" void FUN_011e0744_(void* a, void* b, int c);
extern "C" unsigned g_rwTypes[];      // 0x14469c4

struct Inner { void f11eff60(); };
struct Mgr   { void f276c0(void* p); };

// ---------------------------------------------------------------- 009980d0 bit-smear hash finalizer
// @ 0x009980d0
unsigned __cdecl FUN_009980d0(unsigned x)
{
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return (x >> 1) ^ x;
}

// ---------------------------------------------------------------- 00998100 AsInterface
struct Misc34 {
    int  AsInterface(int iid);     // 0x998100
    void f98140();                 // 0x998140
    void f98f80(int* p);           // 0x998f80
    void f98fc0(void* o);          // 0x998fc0
};

// @ 0x00998100
int Misc34::AsInterface(int iid)
{
    void* self = this;
    if (iid == 0x1be8ca6)
        return (int)self;
    if (iid != (int)0xee3f516e) {
        unsigned d = (iid == (int)0xef7d16e1) ? 0xffffffffu : 0u;
        return (int)self & (int)d;
    }
    if (self)
        return (int)self + 8;
    return 0;
}

// ---------------------------------------------------------------- 00998140
// @ 0x00998140
void Misc34::f98140()
{
    void* self = this;
    void* p = *(void**)((char*)self + 4);
    if (p) {
        ((Inner*)p)->f11eff60();
        ((Mgr*)g_16c8b44)->f276c0(p);
        *(void**)((char*)self + 4) = 0;
    }
}

// ---------------------------------------------------------------- 00998170 RWTextureFactory::GetSupportedTypes
struct RWTexFactory {
    int GetSupportedTypes(unsigned* out, unsigned n);   // 0x998170
    bool CanConvert(int a, int id);                     // 0x9981b0
    int Release();                                      // 0x998200
    bool CreateResource(int param2, void** out, void* p4, void* p5); // 0x998770
};

// @ 0x00998170
int RWTexFactory::GetSupportedTypes(unsigned* out, unsigned n)
{
    unsigned i = 0;
    if (n > 0) {
        do {
            if (i >= 6)
                break;
            out[i] = g_rwTypes[i];
            i++;
        } while (i < n);
    }
    return 6;
}

// @ 0x009981b0
bool RWTexFactory::CanConvert(int a, int id)
{
    (void)a;
    return id == (int)0xef7d16e1;
}

// @ 0x00998200 Release
// @ 0x00998200
int RWTexFactory::Release()
{
    char* t = (char*)this;
    int old = (int)_InterlockedExchangeAdd((volatile long*)(t + 0xc), 0);
    if (old == 1 && *(int*)(t + 4) != 0)
        FUN_00957c20(t, 0);
    char* p = t + 8;
    volatile long* rc = (volatile long*)(p + 4);
    int n = (int)_InterlockedExchangeAdd(rc, -1) - 1;
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        if (p != 0)
            (*(void(__thiscall**)(void*, int))((char*)*(void**)p + 8))(p, 1);
    }
    return n;
}

// ---------------------------------------------------------------- 00997f50 HitMaskResource ctor
struct Obj34 {
    char pad[0x40];
    void ctor();           // 0x997f50
    void* ScalarDtor(unsigned flags);  // 0x998000
};

// @ 0x00997f50
void Obj34::ctor()
{
    char* a = (char*)this;
    *(void**)(a + 4) = (void*)0x13ef094;
    *(unsigned*)(a + 8) = 0;
    *(void**)(a + 0) = (void*)0x141a380;
    *(void**)(a + 4) = (void*)0x141a37c;
    *(unsigned*)(a + 0x14) = 0;
    *(unsigned*)(a + 0x18) = 0;
    *(unsigned*)(a + 0x1c) = 0;
    *(void**)(a + 0x28) = (void*)0x13ebcdc;
    _InterlockedExchange((volatile long*)(a + 0x2c), 0);
    *(unsigned*)(a + 0x30) = 0;
    *(unsigned*)(a + 0x34) = 0;
    *(unsigned*)(a + 0x38) = 0;
    *(void**)(a + 0) = (void*)0x14468e0;
    *(void**)(a + 4) = (void*)0x14468dc;
    *(void**)(a + 0x28) = (void*)0x14468c8;
}

// @ 0x00998000
void* Obj34::ScalarDtor(unsigned flags)
{
    char* a = (char*)this;
    *(void**)(a + 0x28) = (void*)0x13eb938;
    int p = *(int*)(a + 0x14);
    if (p != 0 && *(int*)(p - 4) != 0)
        FUN_00f47380((void*)p);
    *(void**)(a + 4) = (void*)0x13ef094;
    *(void**)(a + 0) = (void*)0x13eb938;
    if (flags & 1)
        FUN_00f47380(a);
    return a;
}

struct HMFactory { bool CreateResource(int param2, void** out, void* p4, void* p5); };

// ---------------------------------------------------------------- 00998050 HitMaskFactory::CreateResource
// @ 0x00998050
bool HMFactory::CreateResource(int param2, void** out, void* p4, void* p5)
{
    char* self = (char*)this;
    char* obj = (char*)FUN_00f473a0(0x3c, "UTFWin/HitMaskResource", 0, 0, 0, 0);
    if (obj == 0) {
        // fall through as 0
    } else {
        ((Obj34*)obj)->ctor();
    }
    (*(void(__thiscall**)(char*))*(void**)obj)(obj);
    char* res = obj + 0x28;
    if (param2 != 0) {
        char ok = (*(char(__thiscall**)(char*, int, char*, void*, void*))((char*)*(void**)self + 0x24))(
            self, param2, res, p4, p5);
        if (!ok) {
            (*(void(__thiscall**)(char*))((char*)*(void**)obj + 4))(obj);
            return false;
        }
    }
    *out = res;
    return true;
}

// ---------------------------------------------------------------- 009986e0 ctor
// @ 0x009986e0
void __fastcall FUN_009986e0(void* self)
{
    char* a = (char*)self;
    *(void**)(a + 0) = (void*)0x141aa84;
    *(void**)(a + 8) = (void*)0x13ebcdc;
    _InterlockedExchange((volatile long*)(a + 0xc), 0);
    *(unsigned*)(a + 0x10) = 0;
    *(unsigned*)(a + 0x14) = 0;
    *(unsigned*)(a + 0x18) = 0;
    *(void**)(a + 0) = (void*)0x14469f0;
    *(void**)(a + 8) = (void*)0x14469dc;
    *(unsigned*)(a + 0x1c) = 0;
    *(unsigned*)(a + 4) = 0;
}

// ---------------------------------------------------------------- 00998770 RWTextureFactory::CreateResource
// @ 0x00998770
bool RWTexFactory::CreateResource(int param2, void** out, void* p4, void* p5)
{
    char* self = (char*)this;
    char* obj = (char*)FUN_00f473a0(0x30, "UTFWin/RWTextureResource", 0, 0, 0, 0);
    if (obj != 0) {
        FUN_009986e0(obj);
    }
    (*(void(__thiscall**)(char*))*(void**)obj)(obj);
    char* res = obj + 8;
    if (param2 != 0) {
        char ok = (*(char(__thiscall**)(char*, int, char*, void*, void*))((char*)*(void**)self + 0x24))(
            self, param2, res, p4, p5);
        if (!ok) {
            (*(void(__thiscall**)(char*))((char*)*(void**)obj + 4))(obj);
            return false;
        }
    }
    *out = res;
    return true;
}

// ---------------------------------------------------------------- 00998820 ctor
// @ 0x00998820
void __fastcall FUN_00998820(void* self)
{
    char* a = (char*)self;
    *(void**)(a + 0) = (void*)0x13effa8;
    _InterlockedExchange((volatile long*)(a + 4), 0);
    *(void**)(a + 0) = (void*)0x1446a3c;
    *(unsigned char*)(a + 8) = 1;
}

// ---------------------------------------------------------------- 00998f80
// @ 0x00998f80
void Misc34::f98f80(int* p)
{
    char* self = (char*)this;
    *(int*)(self + 0xc) = p[0];
    *(int*)(self + 0x10) = p[1];
    *(int*)(self + 0x14) = p[2];
    (*(void(__thiscall**)(char*))((char*)*(void**)self + 0x14))(self);
}

// ---------------------------------------------------------------- 00998fc0
// @ 0x00998fc0
void Misc34::f98fc0(void* o)
{
    char* self = (char*)this;
    (*(void(__thiscall**)(void*))*(void**)o)(o);
    void** p = *(void***)(self + 0x60);
    if (p < *(void***)(self + 0x64)) {
        *(void***)(self + 0x60) = p + 1;
        if (p != 0)
            *p = o;
        return;
    }
    FUN_00a80dd0(p, &o);
}

// ---------------------------------------------------------------- 00999000 SerCollection::RemoveAll
// @ 0x00999000
void __fastcall SerCollection_RemoveAll(char* self)
{
    char* end = *(char**)(self + 0x60);
    for (char* p = *(char**)(self + 0x5c); p != end; p += 4) {
        void* o = *(void**)p;
        (*(void(__thiscall**)(void*))((char*)*(void**)o + 4))(o);
    }
    char* a = *(char**)(self + 0x5c);
    char* b = *(char**)(self + 0x60);
    FUN_011e0744_(a, b, (int)b - (int)b);
    int n = (int)(b - a) >> 2;
    n = -n;
    n = n + n;
    n = n + n;
    *(int*)(self + 0x60) = (int)b + n;
}

// ---------------------------------------------------------------- 00999050
// @ 0x00999050
void __fastcall FUN_00999050(char* self)
{
    char* au = *(char**)(self + 8);
    if (au) {
        (*(void(__thiscall**)(char*, char*, char*))((char*)*(void**)au + 0x14))(au, self + 0xc, self);
        *(unsigned*)(self + 8) = 0;
    }
    (*(void(__thiscall**)(char*))((char*)*(void**)self + 0x10))(self);
    SerCollection_RemoveAll(self);
}

// ---------------------------------------------------------------- 00999080 SerCollection ctor
extern void* g_SerCollection_vftable[];       // 0x1446abc
extern void* g_hashEmptyBucketArray[];        // 0x154df28 (eastl gpEmptyBucketArray)
extern const wchar_t g_emptyWString[];        // 0x13fe144
struct WString16b {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void FUN_00579a90(const wchar_t* s);      // basic_string<wchar_t>::RangeInitialize, thiscall
};

struct SerRehashPolicy {                       // eastl::prime_rehash_policy
    float    mfMaxLoadFactor;
    float    mfGrowthFactor;
    unsigned mnNextResize;
    SerRehashPolicy() : mfMaxLoadFactor(1.0f), mfGrowthFactor(2.0f), mnNextResize(0) {}
};
struct SerHashtable {                         // eastl::hashtable<uint, AutoRefCount<...>> (0x20 bytes)
    int             mHashObj;                 // +0 (empty functor slot)
    void**          mpBucketArray;            // +4
    unsigned        mnBucketCount;            // +8
    unsigned        mnElementCount;           // +0xc
    SerRehashPolicy mRehashPolicy;            // +0x10
    int             mAllocator;               // +0x1c
    SerHashtable() : mnBucketCount(0), mnElementCount(0) { reset_lose_memory(); }
    void reset_lose_memory() {
        mnBucketCount = 1;
        mpBucketArray = g_hashEmptyBucketArray;
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
};
struct SerPtrVector {                         // eastl::vector<T*> (0x10 bytes)
    void** mpBegin; void** mpEnd; void** mpCapacity; int mAllocator;
    SerPtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
struct SerWString : WString16b {
    SerWString() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; FUN_00579a90(g_emptyWString); }
};
struct SerKey {
    unsigned mInstance, mType, mGroup;
    SerKey() : mInstance(0), mType(0), mGroup(0) {}
};
struct SerCollection {
    void**       mpVtbl;                      // +0
    void*        mService;                    // +4
    void*        mAutoUpdate;                 // +8
    SerKey       mKey;                        // +0xc
    unsigned     mSerFlags;                   // +0x18
    SerHashtable mImports;                    // +0x1c
    SerHashtable mExports;                    // +0x3c
    SerPtrVector mList;                       // +0x5c
    int          mPad6c;                      // +0x6c
    SerWString   mName;                       // +0x70
    SerCollection();
};

// @ 0x00999080
SerCollection::SerCollection()
    : mpVtbl(g_SerCollection_vftable), mService(0), mAutoUpdate(0), mSerFlags(0)
{
}

// ================================================================ image reader/writer helpers
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])

extern "C" void* FUN_011e073e(void* dst, int v, unsigned n);   // memset
extern "C" void* FUN_011f0220(void* out, int w, int h, int a, int b, int fmt);   // cdecl, descriptor builder
extern "C" void* FUN_011efeb0(void* raster, int w, int h, int a, int b, int fmt); // rw::graphics::Raster::Initialize
extern "C" void  FUN_00957c20_(void* t, int v);
extern "C" void  FUN_011f0440(void);                                              // FillSpriteTexture (thiscall)

struct ImgInfo { int pad[4]; int w; int h; int bpp; };   // +0x10 w, +0x14 h, +0x18 bpp

// image reader object on the stack (EA::UTFWinTools image codec reader)
struct ImgReader {
    unsigned s[6];
    void   __thiscall ctor();                              // 0x87cde0
    char   __thiscall Open(void* stream);                  // 0x87ce00
    char   __thiscall Init(unsigned base, void* info);     // 0x87d0b0
    ImgInfo* __thiscall GetImage(int idx);                 // 0x87ced0
    char   __thiscall Copy(ImgInfo* img, void* buf, int n);// 0x87cf00
    void   __thiscall Free(ImgInfo* img);                  // 0x87cef0
    void   __thiscall Close();                             // 0x87d070
};

// image writer object on the stack
struct ImgWriter {
    unsigned s[6];
    void   __thiscall ctor();                              // 0x87cf40
    void   __thiscall Open(void* stream);                  // 0x87cf60
    char   __thiscall Init(unsigned base, int a);          // 0x87d2a0
    char   __thiscall Write(void* hdr, void* buf, int n);  // 0x87d030
    void   __thiscall Finish();                            // 0x87cff0
    void   __thiscall Close();                             // 0x87d260
};

// ---------------------------------------------------------------- RWTextureResource (container half)
struct RWTexResource {
    char pad0[4];
    void* mRaster;       // +4
    char pad1[0x14];
    void* mReader;       // +0x1c
    char pad2[8];
    unsigned short mW;   // +0x28
    unsigned short pad3;
    unsigned short mH;   // +0x2c
    void InitTextureResources();   // 0x998250
};

struct MemPool { void* __thiscall LockedAligned(int a, int b, int c, int d, int e, int f, int g, int h); };  // 0x928a30
extern "C" MemPool* g_memPool_16c8b44;
struct RasterObj {
    char   __thiscall Lock(int mode, int a, void* info);   // 0x11ef750 (bool)
    void   __thiscall Unlock(void* info);                  // 0x11ef880
    void   __thiscall Destroy();                           // 0x11eff60
};
struct PoolMgr { void __thiscall Free(void* p); };         // 0x9276c0

// @ 0x00998250
void RWTexResource::InitTextureResources()
{
    if (mReader == 0)
        return;
    ImgReader rd;
    rd.ctor();
    char ok = 0;
    unsigned base = ((unsigned)VF(mReader, 0x10, int*(__thiscall*)(void*))(mReader)[1]) - 0x2f7d0000;
    if (rd.Open(VF(mReader, 0x18, void*(__thiscall*)(void*))(mReader))) {
        int info[4];
        if (rd.Init(base, info)) {
            ImgInfo* img = rd.GetImage(0);
            if (img) {
                int desc[3];
                FUN_011f0220(desc, mW, mH, 1, 8, 0x15);
                void* mem = g_memPool_16c8b44->LockedAligned(desc[1], desc[2], 0, 0, 0, 0, 0, 0);
                if (mem) {
                    int raster[4];
                    raster[0] = (int)mem; raster[1] = 0; raster[2] = 0; raster[3] = 0;
                    RasterObj* r = (RasterObj*)FUN_011efeb0(raster, mW, mH, 1, 8, 0x15);
                    if (r) {
                        int lk[5];
                        if (r->Lock(2, 0, lk)) {
                            if (rd.Copy(img, (void*)lk[0], lk[3])) {
                                mRaster = r;
                                ok = 1;
                            }
                            r->Unlock(lk);
                            if (ok)
                                goto done_img;
                        }
                        r->Destroy();
                        ((PoolMgr*)g_memPool_16c8b44)->Free(r);
                    }
                }
            done_img:
                rd.Free(img);
            }
        }
        VF(mReader, 0x24, void(__thiscall*)(void*))(mReader);
        void* old = mReader;
        if (old) {
            mReader = 0;
            VF(old, 8, void(__thiscall*)(void*))(old);
        }
    }
    rd.Close();
}

// ---------------------------------------------------------------- 009983d0 RWTextureFactory::ReadResource
struct RWTexFactory2 {
    char pad[8];
    char mPow2;     // +8
    bool ReadResource(void* reader, void* container, int a3, int a4);   // 0x9983d0
    bool WriteResource(void* container, void* stream, int a3, unsigned base); // 0x998530
};

// @ 0x009983d0
bool RWTexFactory2::ReadResource(void* reader, void* container, int a3, int a4)
{
    int* i1 = VF(reader, 0x10, int*(__thiscall*)(void*))(reader);
    unsigned base = (unsigned)i1[1] - 0x2f7d0000;
    if (container == 0)
        return false;
    char* t = (char*)VF(container, 0xc, void*(__thiscall*)(void*, unsigned))(container, 0xef7d16e1);
    if (t == 0)
        return false;
    int* i2 = VF(reader, 0x10, int*(__thiscall*)(void*))(reader);
    int keep = i2[1];
    *(int*)(t + 0x10) = i2[0];
    *(int*)(t + 0x14) = a4;
    *(int*)(t + 0x18) = i2[2];
    void* old = *(void**)(t + 0x1c);
    if (reader != old) {
        VF(reader, 4, void(__thiscall*)(void*))(reader);
        *(void**)(t + 0x1c) = reader;
        if (old)
            VF(old, 8, void(__thiscall*)(void*))(old);
    }
    VF(reader, 0x20, void(__thiscall*)(void*))(reader);
    ImgReader rd;
    rd.ctor();
    if (rd.Open(VF(reader, 0x18, void*(__thiscall*)(void*))(reader))) {
        int info[4];
        if (rd.Init(base, info)) {
            ImgInfo* img = rd.GetImage(0);
            if (img) {
                *(int*)(t + 0x20) = img->w;
                *(int*)(t + 0x24) = img->h;
                unsigned hw, hh;
                if (mPow2) {
                    hw = FUN_009980d0(img->w * 2 - 1);
                    *(unsigned*)(t + 0x28) = hw;
                    hh = FUN_009980d0(img->h * 2 - 1);
                } else {
                    *(int*)(t + 0x28) = img->w;
                    hh = img->h;
                }
                *(unsigned*)(t + 0x2c) = hh;
                rd.Free(img);
            }
            FUN_00957c20_(t, 1);
            rd.Close();
            return true;
        }
    }
    rd.Close();
    (void)keep; (void)a3;
    return false;
}

// ---------------------------------------------------------------- 00998530 RWTextureFactory::WriteResource
struct WriteHdr {
    unsigned a[4];
    unsigned w;        // +0x10
    unsigned h;        // +0x14
    unsigned bpp;      // +0x18
    char pad[0x438 - 0x1c];
    unsigned fmtFlag;  // +0x438
    char pad2[0x2a70 - 0x43c];
};
struct TexDesc { int fmt; int pad; unsigned short w; unsigned short h; unsigned char bpp; };
struct SpriteTex { void __thiscall Fill(void* buf, unsigned size, int a); };   // 0x11f0440

// @ 0x00998530
bool RWTexFactory2::WriteResource(void* container, void* stream, int a3, unsigned base)
{
    (void)a3;
    if (container == 0)
        return false;
    int* c = (int*)VF(container, 0xc, void*(__thiscall*)(void*, unsigned))(container, 0xef7d16e1);
    if (c == 0)
        return false;
    unsigned b = base + 0xd0830000;
    char closeIt = 0;
    if (c[1] == 0) {
        VF(c, 0x10, void(__thiscall*)(void*))(c);
        closeIt = 1;
    }
    TexDesc* d = (TexDesc*)c[1];
    ImgWriter wr;
    wr.ctor();
    WriteHdr hdr;
    FUN_011e073e(&hdr, 0, sizeof(hdr));
    hdr.w = d->w;
    hdr.h = d->h;
    hdr.bpp = d->bpp;
    if (d->fmt == 0x15)
        hdr.fmtFlag = 8;
    wr.Open(VF(stream, 0x18, void*(__thiscall*)(void*))(stream));
    if (wr.Init(b, 1)) {
        int bits = hdr.bpp * hdr.h * hdr.w;
        unsigned size = (unsigned)(bits + ((bits >> 31) & 7)) >> 3;
        void* buf = FUN_00f473a0(size, "UTFWin/RWTextureFactory", 0, 0, 0, 0);
        FUN_011e073e(buf, 0, size);
        ((SpriteTex*)d)->Fill(buf, size, 0);
        int rb = hdr.bpp * hdr.w;
        char r = wr.Write(&hdr, buf, (rb + ((rb >> 31) & 7)) >> 3);
        FUN_00f47380(buf);
        wr.Finish();
        if (closeIt)
            VF(c, 0x14, void(__thiscall*)(void*))(c);
        wr.Close();
        return r != 0;
    }
    if (closeIt)
        VF(c, 0x14, void(__thiscall*)(void*))(c);
    wr.Close();
    return false;
}

// ================================================================ SerAutoUpdate (hash maps + mutex)
extern "C" const char g_mutexName_1446a78[];

struct Key3 { unsigned a, b, c; };
struct KV   { Key3 k; unsigned v; };
struct HNode { KV kv; HNode* next; };            // 0x14
struct HIter { HNode* node; HNode** bucket; };
struct false_type {};   // eastl::false_type (has_unique_keys_type of a multi-hashtable), passed by value as 1 byte
struct HRange { HNode* first; HNode** fb; HNode* last; HNode** lb; };
struct RehashRes { char need; unsigned n; };

struct HashPolicy {
    float maxLoad, growth; unsigned nextResize;
    void __thiscall GetRehash(RehashRes* out, unsigned bcount, unsigned ecount, int n);  // 0x921440
};

struct KeyHT {            // eastl::hashtable<Key, pair<Key,int>> (multi); member at SerAutoUpdate+0xc
    char alloc[4];
    HNode** buckets;      // +4
    unsigned bcount;      // +8
    unsigned count;       // +0xc
    HashPolicy policy;    // +0x10
    void equal_range(HRange* out, const Key3* k);          // 0x998920
    HIter* insert(HIter* out, const KV* v, false_type);    // 0x9989d0 DoInsertValue(value, false_type)
    void __thiscall DoRehash(unsigned n);                  // 0x998870
    HIter* __thiscall find(HIter* out, const Key3* k);     // 0x833840
    void __thiscall erase(HIter* out, HIter pos);          // 0xb4f930
    void __thiscall DoFreeNodes(HNode** b, unsigned n);    // 0x7611f0
};

struct KeySet {           // eastl::hashtable<Key, ...> member at SerAutoUpdate+0x2c
    char alloc[4];
    HNode** buckets;
    unsigned bcount;
    unsigned count;
    HashPolicy policy;
    HIter* __thiscall insert(HIter* out, const Key3* k, char flag);   // 0x8dfcd0
    void __thiscall DoFreeNodes(HNode** b, unsigned n);               // 0x93dc70
};

struct Mutex {
    char s[0x20];
    void __thiscall Lock(const char* name);        // 0x9221b0
    void __thiscall Unlock();                      // 0x922270
    void __thiscall ctor(int a, int b);            // 0x9222a0
    void __thiscall dtor();                        // 0x922130
};

struct PtrVec {
    void** b; void** e; void** c;
    void __thiscall DoInsertValue(void** pos, void** v);   // 0xa80dd0
    void push_back(void* v)
    {
        void** p = e;
        if (p < c) {
            e = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(p, &v);
        }
    }
};

extern "C" void __cdecl FUN_00921df0(unsigned* ms);    // EA::Thread::ThreadSleep
extern "C" void* __cdecl FUN_008de1a0_(void);          // singleton accessor

struct SerAutoUpdate {
    void*  vt0;            // +0
    void*  vt4;            // +4
    long   mRefCount;      // +8
    KeyHT  mFiles;         // +0xc
    char   pad0[0x2c - 0x0c - sizeof(KeyHT)];
    KeySet mChanged;       // +0x2c
    char   pad1[0x4c - 0x2c - sizeof(KeySet)];
    PtrVec mListeners;     // +0x4c
    char   pad2[0x60 - 0x4c - sizeof(PtrVec)];
    void*  mOwner;         // +0x60
    char   pad3[4];
    Mutex  mMutex;         // +0x68

    SerAutoUpdate* ctor(void* owner);                       // 0x998df0
    void dtor();                                            // 0x998eb0
    void RemoveEntry(Key3* k, int value);                   // 0x998ac0
    void AddEntry(Key3* k, int value);                      // 0x998b60
    void ProcessChanges();                                  // 0x998bd0
};

// @ 0x00998920
void KeyHT::equal_range(HRange* out, const Key3* k)
{
    unsigned a = k->a;
    unsigned c = k->c;
    HNode** bk = buckets + (a ^ c) % bcount;
    HNode* p = *bk;
    for (;;) {
        if (p == 0) {
            HNode** e = buckets + bcount;
            HNode* en = *e;
            out->first = en; out->fb = e; out->last = en; out->lb = e;
            return;
        }
        if (a == p->kv.k.a && k->b == p->kv.k.b && c == p->kv.k.c)
            break;
        p = p->next;
    }
    HNode* q = p->next;
    if (q != 0) {
        while (a == q->kv.k.a && k->b == q->kv.k.b) {
            if (c != q->kv.k.c)
                break;
            q = q->next;
            if (q == 0)
                break;
        }
    }
    HNode** qb = bk;
    if (q == 0) {
        qb = bk + 1;
        while (*qb == 0)
            qb++;
        q = *qb;
    }
    out->fb = bk;
    out->first = p;
    out->last = q;
    out->lb = qb;
}

// @ 0x009989d0
HIter* KeyHT::insert(HIter* out, const KV* v, false_type)
{
    RehashRes rr;
    policy.GetRehash(&rr, bcount, count, 1);
    if (rr.need)
        DoRehash(rr.n);
    unsigned idx = (v->k.a ^ v->k.c) % bcount;
    HNode* n = (HNode*)FUN_00f473a0(0x14, "EASTL", 0, 0, (int)
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (n)
        n->kv = *v;
    n->next = 0;
    HNode* head = buckets[idx];
    for (HNode* p = head; ; p = p->next) {
        if (p == 0) {
            n->next = head;
            buckets[idx] = n;
            break;
        }
        if (v->k.a == p->kv.k.a && v->k.b == p->kv.k.b && v->k.c == p->kv.k.c) {
            n->next = p->next;
            p->next = n;
            break;
        }
    }
    count++;
    out->node = n;
    out->bucket = buckets + idx;
    return out;
}

// @ 0x00998ac0
void SerAutoUpdate::RemoveEntry(Key3* k, int value)
{
    mMutex.Lock(g_mutexName_1446a78);
    HRange r;
    mFiles.equal_range(&r, k);
    HNode* n = r.first;
    HNode** bk = r.fb;
    HNode* end = r.last;
    if (n != end) {
        while (n->kv.v != (unsigned)value) {
            n = n->next;
            while (n == 0) {
                n = *++bk;
            }
            if (n == end) {
                mMutex.Unlock();
                return;
            }
        }
        HIter pos;
        pos.node = n; pos.bucket = bk;
        HIter res;
        mFiles.erase(&res, pos);
    }
    mMutex.Unlock();
}

// @ 0x00998b60
void SerAutoUpdate::AddEntry(Key3* k, int value)
{
    mMutex.Lock(g_mutexName_1446a78);
    KV kv;
    kv.k = *k;
    kv.v = (unsigned)value;
    HIter out;
    mFiles.insert(&out, &kv, false_type());
    mMutex.Unlock();
}

// @ 0x00998bd0
void SerAutoUpdate::ProcessChanges()
{
    void** first = mListeners.b;
    void** last = mListeners.e;
    FUN_011e0744_(first, last, (int)((char*)mListeners.e - (char*)last));
    mListeners.e = mListeners.e - (last - first);

    if (mChanged.count != 0) {
        mMutex.Lock(g_mutexName_1446a78);
        HNode** bk = mChanged.buckets;
        HNode* end = bk[mChanged.bcount];
        HNode* n = *bk;
        HNode** nb = bk;
        if (n == 0) {
            nb = bk + 1;
            while (*nb == 0)
                nb++;
            n = *nb;
        }
        while (n != end) {
            HRange r;
            mFiles.equal_range(&r, (const Key3*)n);
            HNode* m = r.first;
            HNode** mb = r.fb;
            if (m != r.last) {
                do {
                    mListeners.push_back((void*)m->kv.v);
                    m = m->next;
                    if (m == 0) {
                        do { m = *++mb; } while (m == 0);
                    }
                } while (m != r.last);
            }
            n = (HNode*)n->kv.v;     // set-node next link at +0xc
            while (n == 0) {
                nb++;
                n = *nb;
            }
        }
        mChanged.DoFreeNodes(mChanged.buckets, mChanged.bcount);
        mChanged.count = 0;
        mMutex.Unlock();
    }
    void** p = mListeners.b;
    if (p != mListeners.e) {
        void** q = mListeners.e;
        for (; p != q; p++) {
            void* o = *p;
            VF(o, 0, void(__thiscall*)(void*))(o);
        }
    }
}

// ---------------------------------------------------------------- 00998d30 reload-changed-layouts callback
// @ 0x00998d30
void __cdecl ReloadChangedLayouts(void* iface)
{
    unsigned ms = 100;
    FUN_00921df0(&ms);
    SerAutoUpdate* s = 0;
    if (iface)
        s = (SerAutoUpdate*)VF(iface, 0xc, void*(__thiscall*)(void*, unsigned))(iface, 0x2fbf2058);
    s->ProcessChanges();
}

// ---------------------------------------------------------------- 00998d70 resource-changed callback
// @ 0x00998d70
void __cdecl OnResourceChanged(int a, Key3* key, SerAutoUpdate* self)
{
    (void)a;
    self->mMutex.Lock(g_mutexName_1446a78);
    HNode* endNode = self->mFiles.buckets[self->mFiles.bcount];
    HIter tmp;
    HIter* f = self->mFiles.find(&tmp, key);
    if (f->node != endNode) {
        if (self->mChanged.count == 0) {
            void* o = self->mOwner;
            VF(o, 0x1c, void(__thiscall*)(void*, void*, void*))(o, (void*)ReloadChangedLayouts, self);
        }
        char flag = 0;
        self->mChanged.insert(&tmp, key, flag);
    }
    self->mMutex.Unlock();
}

// ---------------------------------------------------------------- 00998df0 SerAutoUpdate ctor
struct AsyncMgr { void __thiscall Register(int a, void* cb, void* self, int b, int c); };  // vt+0x40

// @ 0x00998df0
SerAutoUpdate* SerAutoUpdate::ctor(void* owner)
{
    *(void**)((char*)this + 0) = (void*)0x13fa72c;
    *(void**)((char*)this + 4) = (void*)0x13ef094;
    _InterlockedExchange((volatile long*)&mRefCount, 0);
    *(void**)((char*)this + 0) = (void*)0x1446a90;
    *(void**)((char*)this + 4) = (void*)0x1446a8c;
    mFiles.policy.maxLoad = 1.0f;
    mFiles.policy.growth = 2.0f;
    mFiles.bcount = 1;
    mFiles.count = 0;
    mFiles.policy.nextResize = 0;
    mFiles.buckets = (HNode**)0x154df28;
    mChanged.policy.maxLoad = 1.0f;
    mChanged.policy.growth = 2.0f;
    mChanged.bcount = 1;
    mChanged.buckets = (HNode**)0x154df28;
    mChanged.count = 0;
    mChanged.policy.nextResize = 0;
    mListeners.b = 0;
    mListeners.e = 0;
    mListeners.c = 0;
    mOwner = owner;
    mMutex.ctor(0, 1);
    void* mgr = FUN_008de1a0_();
    if (mgr)
        VF(mgr, 0x40, void(__thiscall*)(void*, int, void*, void*, int, int))(mgr, 1, (void*)OnResourceChanged, this, 0, 0);
    return this;
}

// ---------------------------------------------------------------- 00998eb0 SerAutoUpdate dtor
// @ 0x00998eb0
void SerAutoUpdate::dtor()
{
    mMutex.dtor();
    void** p = mListeners.b;
    if (p && ((int*)p)[-1])
        FUN_00f47380(p);
    mChanged.DoFreeNodes(mChanged.buckets, mChanged.bcount);
    mChanged.count = 0;
    if (mChanged.bcount > 1)
        FUN_00f47380(mChanged.buckets);
    mFiles.DoFreeNodes(mFiles.buckets, mFiles.bcount);
    mFiles.count = 0;
    if (mFiles.bcount > 1)
        FUN_00f47380(mFiles.buckets);
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    *(void**)((char*)this + 4) = (void*)0x13ef094;
}
