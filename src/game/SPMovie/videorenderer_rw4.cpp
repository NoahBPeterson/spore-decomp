// src/game/SPMovie/videorenderer_rw4.cpp -- migrated from slice(s) s00fd90c0 by tools/migrate/rewrite.py
// Object file: SPMovie/videorenderer_rw4.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern float DAT_016077c4;
extern float DAT_016077c8;

// ---- items of slice s00fd90c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
extern u32   DAT_01493d20;
extern u32   DAT_01493d80;
extern u32   DAT_01485720;    // 1.0f
extern float DAT_016077c4;
extern float DAT_016077c8;
extern u8    DAT_01493dcc[];  // "VideoRenderable data buffer"
extern char  DAT_01493dc0[];  // "Generic2D"
void* __cdecl  FUN_0067dd70();                       // SP::MaterialManager
void* __cdecl  FUN_0067dd60();                       // 0x0067dd60
void* __cdecl  FUN_011e58c0();                       // 0x011e58c0
char  __cdecl  FUN_006ddcc0(int, int, void*, void*); // 0x006ddcc0
void  __cdecl  FUN_006ddd80(int, void*, void*, void*); // 0x006ddd80
u32   __cdecl  FUN_00932e80(const char*, u32, int);  // FNV1_String8
// planar YUV 4:2:0 -> 32-bit RGB blit (0x00fceb30)
void  __cdecl  FUN_00fceb30(const u8* y, const u8* u, const u8* v, int yPitch, int width, int height,
                            u8* dst, int dstPitch, int flags);
void  __cdecl  FUN_00fcdf40(int, int, int, int, void*); // VideoRenderable::GetDataBufSizes
void* __cdecl  FUN_00d06400();                       // 0x00d06400
struct Ext {
    void* FUN_00fcd940(int);                  // 0x00fcd940 ctor helper
    void* FUN_00fd9680();                     // 0x00fd9680 ctor
    void* FUN_00fc7dd0(void*);                // 0x00fc7dd0 ctor
    void* FUN_00fc8080();                     // 0x00fc8080 ctor
    void* FUN_00fd95e0();                     // 0x00fd95e0 ctor
    void* FUN_00fcde80();                     // 0x00fcde80 ctor
    void* FUN_00fc7f30();                     // 0x00fc7f30 ctor
    void* FUN_011e64a0(int, void*);           // 0x011e64a0
    void  FUN_011ef880(void*);                // 0x011ef880
    void* FUN_00fd8c40(void*);                // 0x00fd8c40 cMovieCheat ctor
    void* FUN_00576650(void*);                // GetImageResource (0x00576650)
    void* FUN_00ae9390();                     // 0x00ae9390 -> char
    void  FUN_00e190c0(int);                  // 0x00e190c0
    void* FUN_00e18c70(void*);                // 0x00e18c70 -> char
    int   FUN_00bb9ae0();                     // 0x00bb9ae0
    void* FUN_00b1fdb0();                     // GetAvatar
    void  FUN_00d00a10(void*, int);           // returns float
    void* FUN_01040820();                     // returns float
    void* FUN_00c8b770();                     // cStar::GetSolarSystem
    void  FUN_00c86c70();                     // cSolarSystem::ActivateGraphics
    void  FUN_01034b90();                     // 0x01034b90
    void  FUN_00d06400();                     // 0x00d06400
    char  FUN_00d09660();                     // 0x00d09660 -> char
    void* FUN_01065e20();                     // 0x01065e20 -> char
    void  FUN_01067b60();                     // 0x01067b60
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }
struct MatMgr_s00fd_9750 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void* Find(u32 id);               // slot 0x28
};
struct RenderPartReset {
    u32 reserved;
    u32 partData[6];
    u32 reserved2[3];
    u32 width;
    u32 height;
    u32 format;
    u32 reserved3;
    u32 partCount;              // +0x38
    u8  reserved3c[0x15];
    u8  mResult;                // +0x51
};

struct RenderPartRelease {
    u32 handle;
    u32 reserved[3];
};

struct RenderPartAllocator {
    virtual void Reserved0();
    virtual void Reserved1();
    virtual void ReleasePart(RenderPartRelease*);
    u32 mReserved04;
    volatile long mRefCount;   // +0x08
};

struct RasterLockInfo {
    u8* pixels;                 // +0x00
    int reserved04;
    int reserved08;
    int pitch;                  // +0x0c
    int reserved10;
    int reserved14;
    int reserved18;
};
// rw::graphics::Raster
struct RwRaster {
    int  Lock(int mode, int zero, RasterLockInfo* out);   // 0x011ef750
    void Unlock(RasterLockInfo* info);                     // 0x011ef880
};
struct RasterTarget {
    RwRaster* mpRaster;         // +0x00
    u8        mFlags;           // +0x04  bit 0: registered
};
struct RasterTargetRegistry {   // returned by FUN_0067dd60
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual void Register(RasterTarget* target);            // +0x34
};

struct Vid {
    u32 x;
    void* mManager;
    union {
        RenderPartAllocator* mPartAllocator;
        RasterTarget*        mTarget;
    };
    u32  mPad0c[8];
    int  mWidth;                // +0x2c
    int  mHeight;               // +0x30
    int  mPitch;                // +0x34
    void  f9460(void* p);
    u8    f9480(RenderPartReset* frame);
    void  f9610(RenderPartReset* parts);
    Vid*  f9680();
void  f96d0();
void  f9750(int, int, int);
    void  f97c0(void* param_2);
    void  f9b70(int, int, int, int, u32);
};
// ---- items of slice s00fd90c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   DAT_01493d20;
extern u32   DAT_01493d80;
extern u32   DAT_01485720;    // 1.0f
extern u8    DAT_01493dcc[];  // "VideoRenderable data buffer"

// @ 0x00fd9460
void Vid::f9460(void* p)
{
    *(void**)((char*)this + 4) = p;
    *(void**)((char*)this + 8) = FUN_011e58c0();
}

static inline void RegisterTarget(RasterTarget* target)
{
    if ((target->mFlags & 1) == 0)
        ((RasterTargetRegistry*)FUN_0067dd60())->Register(target);
}

// @ 0x00fd9480
u8 Vid::f9480(RenderPartReset* frame)
{
    u8 result = 0;
    switch (frame->format) {
    case 0: {
        RasterTarget* target = mTarget;
        result = frame->mResult;
        RegisterTarget(target);
        RasterLockInfo lock;
        RwRaster* raster = target->mpRaster;
        if (raster->Lock(2, 0, &lock) != 0) {
            const u8* y = (const u8*)frame->partData[0];
            const u8* u = y + mWidth * mHeight;
            const u8* v = u + (mWidth >> 1) * (mHeight >> 1);
            FUN_00fceb30(y, u, v, mWidth, mWidth, mHeight, lock.pixels, mPitch * 4, 1);
            target = mTarget;
            RegisterTarget(target);
            target->mpRaster->Unlock(&lock);
        }
        break;
    }
    case 3: {
        RasterTarget* target = mTarget;
        RegisterTarget(target);
        RasterLockInfo lock;
        RwRaster* raster = target->mpRaster;
        if (raster->Lock(2, 0, &lock) != 0) {
            const u8* src = (const u8*)frame->partData[0];
            int rowBytes = mWidth * 4;
            int pitch = lock.pitch;
            u8* dst = lock.pixels;
            for (int row = 0; row < mHeight; ++row) {
                memcpy(dst, src, rowBytes);
                src += rowBytes;
                dst += pitch;
            }
            target = mTarget;
            RegisterTarget(target);
            target->mpRaster->Unlock(&lock);
            return 0;
        }
        break;
    }
    }
    return result;
}

// @ 0x00fd9610
void Vid::f9610(RenderPartReset* parts)
{
    u32 count = parts->partCount;
    if (count > 0) {
        u32* handle = parts->partData;
        do {
            const u32 savedHandle = *handle;
            _ReadWriteBarrier();
            RenderPartRelease release = {};
            release.handle = savedHandle;
            mPartAllocator->ReleasePart(&release);
            handle[0] = 0;
            handle[3] = 0;
            ++handle;
        } while (--count);
    }
    parts->width = 0;
    parts->height = 0;
    parts->format = 4;
}

// @ 0x00fd9680
Vid* Vid::f9680()
{
    char* a = (char*)this;
    *(void**)a = &DAT_01493d80;
    *(int*)(a + 4) = 0;
    *(int*)(a + 8) = 0;
    *(float*)(a + 0x18) = 0.0f;
    *(float*)(a + 0x1c) = 0.0f;
    *(float*)(a + 0x20) = 0.0f;
    float one = *(float*)&DAT_01485720;
    *(int*)(a + 0x0c) = 0;
    *(int*)(a + 0x10) = 0;
    *(int*)(a + 0x14) = 0;
    *(float*)(a + 0x24) = one;
    *(float*)(a + 0x28) = one;
    *(int*)(a + 0x2c) = 0;
    *(int*)(a + 0x30) = 0;
    *(int*)(a + 0x34) = 0;
    *(int*)(a + 0x38) = 0;
    return this;
}

// @ 0x00fd96d0
// Releases the part allocator reference twice: once explicitly (clearing the member),
// then again from the reference member's own destructor.
static inline void ReleaseRef(volatile long* count)
{
    _InterlockedDecrement(count);
    if (_InterlockedExchangeAdd(count, 0) < 1)
        _InterlockedIncrement(count);
    else
        _InterlockedExchangeAdd(count, 0);
}

void Vid::f96d0()
{
    *(void* volatile*)this = &DAT_01493d80;
    RenderPartAllocator* part = *(RenderPartAllocator* volatile*)&mPartAllocator;
    if (part) {
        mPartAllocator = 0;
        ReleaseRef(&part->mRefCount);
    }
    if (mPartAllocator)
        ReleaseRef(&mPartAllocator->mRefCount);
    *(void**)this = &DAT_01493d20;
}

// @ 0x00fd9750
void Vid::f9750(int param_2, int param_3, int param_4)
{
    char* s = (char*)this;
    *(int*)(s + 0x2c) = param_3;
    *(int*)(s + 0x30) = param_4;
    void* mm = FUN_0067dd60();
    void* img = ((void*(__thiscall*)(void*, int, int, int, int, int, int))VTP(mm)[0x40 / 4])(
        mm, param_3, param_4, 1, 8, 0x15, 0);
    E(s + 8)->FUN_00576650(img);
    *(int*)(s + 0x34) = param_3;
    *(int*)(s + 0x38) = param_4;
    MatMgr_s00fd_9750* mat = (MatMgr_s00fd_9750*)FUN_0067dd70();
    u32 h = FUN_00932e80(DAT_01493dc0, 0x811c9dc5, 1);
    void* r = mat->Find(h);
    *(void**)(s + 4) = r;
}


// @ 0x00fd97c0
void Vid::f97c0(void* param_2)
{
    char* s = (char*)this;
    float* p = (float*)param_2;
    char c = (char)f9480((RenderPartReset*)param_2);
    if (*(void**)(s + 0x10)) {
        ((void(__cdecl*)(void*, void*))*(void**)(s + 0x10))(param_2, *(void**)(s + 0x14));
    }
    void* pv = param_2;
    void* local_38[4];
    char c3 = FUN_006ddcc0(1, 4, &pv, local_38);
    if (c3 == 0) return;

    float fStack_24 = (float)(int)p[10];
    float fVar4 = (float)((int)*(float*)(s + 0x18) & 0xffff);
    float fVar5 = (float)((int)*(float*)(s + 0x1c) & 0xffff);
    float fStack_10 = (float)((int)((float)*(int*)(s + 0x30) * *(float*)(s + 0x28) + *(float*)(s + 0x1c)) & 0xffff);
    float fStack_c = (float)((int)((float)*(int*)(s + 0x2c) * *(float*)(s + 0x24) + *(float*)(s + 0x18)) & 0xffff);
    if ((int)p[10] < 0) fStack_24 = fStack_24 + 4294967296.0f;
    fStack_24 = fStack_24 / (float)*(int*)(s + 0x34);
    float fStack_28 = (float)(int)p[0xb];
    if ((int)p[0xb] < 0) fStack_28 = fStack_28 + 4294967296.0f;
    fStack_28 = fStack_28 / (float)*(int*)(s + 0x38);

    float fVar6 = fVar5 + DAT_016077c8;
    if (c == 0) {
        p[0] = fVar4 + DAT_016077c4;
        p[1] = fVar6;
        p[2] = 0.0f; p[3] = 0.0f; p[4] = 0.0f;
        fVar6 = fStack_10 + DAT_016077c8;
        p[5] = fVar4 + DAT_016077c4;
        p[6] = fVar6;
        p[7] = 0.0f; p[8] = 0.0f; p[9] = fStack_28;
        fVar5 = fVar5 + DAT_016077c8;
        p[10] = fStack_c + DAT_016077c4;
        p[0xb] = fVar5;
        p[0xc] = 0.0f; p[0xd] = fStack_24; p[0xe] = 0.0f;
        fStack_c = fStack_c + DAT_016077c4;
        float fStack_8 = fStack_10 + DAT_016077c8;
        p[0xf] = fStack_c;
        p[0x10] = fStack_8;
        p[0x11] = 0.0f;
        fVar4 = fStack_28;
    } else {
        p[0] = fVar4 + DAT_016077c4;
        p[1] = fVar6;
        p[2] = 0.0f; p[3] = 0.0f; p[4] = fStack_28;
        fVar6 = fStack_10 + DAT_016077c8;
        p[5] = fVar4 + DAT_016077c4;
        p[6] = fVar6;
        p[7] = 0.0f; p[8] = 0.0f; p[9] = 0.0f;
        fVar5 = fVar5 + DAT_016077c8;
        p[10] = fStack_c + DAT_016077c4;
        p[0xb] = fVar5;
        p[0xc] = 0.0f; p[0xd] = fStack_24; p[0xe] = fStack_28;
        fStack_c = fStack_c + DAT_016077c4;
        float fStack_8 = fStack_10 + DAT_016077c8;
        p[0xf] = fStack_c;
        p[0x10] = fStack_8;
        p[0x11] = 0.0f;
        fVar4 = 0.0f;
    }
    p[0x12] = fStack_24;
    p[0x13] = fVar4;
    FUN_006ddd80(4, *(void**)(s + 4), *(void**)(s + 8), *(void**)(s + 0xc));
}

// @ 0x00fd9b70
void Vid::f9b70(int param_2, int param_3, int param_4, int param_5, u32 param_6)
{
    char* s = (char*)this;
    *(u32*)(param_2 + 0x38) = param_6;
    u32 stack[8];
    FUN_00fcdf40(param_3, param_4, param_5, param_6, stack);
    if (param_6 != 0) {
        int* pu = (int*)(param_2 + 0x10);
        for (u32 i = 0; i < param_6; ++i) {
            u32 buf[8];
            buf[0] = stack[i];
            buf[1] = 0; buf[2] = 0; buf[3] = 0;
            buf[4] = 4; buf[5] = 1; buf[6] = 1; buf[7] = 1;
            void* alloc = *(void**)(s + 8);
            void* vt2 = *(void**)(alloc);
            ((void(__thiscall*)(void*, u32*, u32*, const char*))VTP(alloc)[1])(
                alloc, &buf[1], buf, (const char*)DAT_01493dcc);
            (void)vt2;
            pu[-3] = buf[1];
            *pu = stack[i];
            pu++;
        }
    }
    *(int*)(param_2 + 0x28) = param_3;
    *(int*)(param_2 + 0x2c) = param_4;
    *(int*)(param_2 + 0x30) = param_5;
}
