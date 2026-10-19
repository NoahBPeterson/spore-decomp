// src/game/UTFSpore_Win32/RWTextureFactory.cpp -- migrated from slice(s) s00997f50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/RWTextureFactory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinTools/RWTextureFactory.h"
#include "EA/Thread/Mutex.h"
#include "EA/UTFWinTools/SerCollection.h"
#include "EA/UTFWinTools/SerScope.h"
#include "EA/ResourceMan/Key.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, int c, int d); // operator new
extern "C" void* g_16c8b44;
extern "C" void* FUN_011f0220(void* out, int w, int h, int a, int b, int fmt);   // cdecl, descriptor builder
extern "C" void* FUN_011efeb0(void* raster, int w, int h, int a, int b, int fmt); // rw::graphics::Raster::Initialize
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---- items of slice s00997f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, int c, int d); // operator new
extern "C" void* g_16c8b44;
struct Inner { void f11eff60(); };
struct Mgr   { void f276c0(void* p); };
struct Misc34 {
    int  AsInterface(int iid);     // 0x998100
    void f98140();                 // 0x998140
    void f98f80(int* p);           // 0x998f80
    void f98fc0(void* o);          // 0x998fc0
};
struct RWTexFactory {
    int GetSupportedTypes(unsigned* out, unsigned n);   // 0x998170
    bool CanConvert(int a, int id);                     // 0x9981b0
    int Release();                                      // 0x998200
    bool CreateResource(int param2, void** out, void* p4, void* p5); // 0x998770
};
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
extern "C" void* FUN_011f0220(void* out, int w, int h, int a, int b, int fmt);   // cdecl, descriptor builder
extern "C" void* FUN_011efeb0(void* raster, int w, int h, int a, int b, int fmt); // rw::graphics::Raster::Initialize
struct ImgInfo { int pad[4]; int w; int h; int bpp; };   // +0x10 w, +0x14 h, +0x18 bpp
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
struct ImgWriter {
    unsigned s[6];
    void   __thiscall ctor();                              // 0x87cf40
    void   __thiscall Open(void* stream);                  // 0x87cf60
    char   __thiscall Init(unsigned base, int a);          // 0x87d2a0
    char   __thiscall Write(void* hdr, void* buf, int n);  // 0x87d030
    void   __thiscall Finish();                            // 0x87cff0
    void   __thiscall Close();                             // 0x87d260
};
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
// ---- items of slice s00997f50 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" unsigned g_rwTypes[];      // 0x14469c4
extern "C" void* FUN_011e073e(void* dst, int v, unsigned n);   // memset
extern "C" void  FUN_00957c20_(void* t, int v);
extern "C" MemPool* g_memPool_16c8b44;

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

// @ 0x00998170
unsigned int EA::UTFWinTools::RWTextureFactory::GetSupportedTypes(unsigned int * out, unsigned int n)
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
bool EA::UTFWinTools::RWTextureFactory::CanConvert(unsigned int a, unsigned int id) const
{
    (void)a;
    return id == (int)0xef7d16e1;
}

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

// @ 0x009983d0
bool EA::UTFWinTools::RWTextureFactory::ReadResource(EA::ResourceMan::Record * reader, EA::ResourceMan::Resource * container, void * a3, unsigned int a4)
{
    int a3_v = (int)a3;
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
                if (mForcePow2Textures) {
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
    (void)keep; (void)a3_v;
    return false;
}

// @ 0x00998530
bool EA::UTFWinTools::RWTextureFactory::WriteResource(EA::ResourceMan::Resource * container, EA::ResourceMan::Record * stream, void * a3, unsigned int base)
{
    int a3_v = (int)a3;
    (void)a3_v;
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

// @ 0x009986e0
void* __fastcall FUN_009986e0(void* self)
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
    return a;
}

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
