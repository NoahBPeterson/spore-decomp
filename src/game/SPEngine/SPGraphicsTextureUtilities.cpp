// src/game/SPEngine/SPGraphicsTextureUtilities.cpp -- migrated from slice(s) s007b19c0, s007b0a70, s007af8b0, s007aea30, s007ada40 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsTextureUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"
#include <intrin.h>
#include <xmmintrin.h>
#include "EA/ArgScript/cIParser.h"
#include "SP/cJob.h"
#include "SP/cDXTCompressJobData.h"
#include "SP/cImageDataRaw.h"
#pragma auto_inline(on)

// ---- items of slice s007ada40 begin (TODO(rewrite): local stubs, replace by canonical classes)
class Span {
public:
    void Init(int x, int y, int dx, int dy, int extra);
    int mX;         // +0x00
    int mY;         // +0x04
    int mXEnd;      // +0x08
    int mYEnd;      // +0x0c
    int mExtra;     // +0x10
    int mM1;        // +0x14
    int mM2;        // +0x18
    uint8_t mFlag;  // +0x1c
};
class InnerData {
public:
    char    mPad00[0x1c];
    uint8_t mFlag;      // +0x1c
};
class FlagHolder {
public:
    uint8_t IsSet();
    InnerData* mpData;  // +0x00
};
static inline uint32_t Expand565(uint32_t c)
{
    uint32_t r = ((c >> 11) << 3) & 0xff;
    r |= (c >> 13) & 7;
    uint32_t g = ((c >> 5) << 2) & 0xff;
    uint32_t g2 = (c >> 9) & 3;
    uint32_t b = (c << 3) & 0xff;
    uint32_t b2 = (c >> 2) & 7;
    uint32_t v = (0xffffff00u | r) << 8;
    v |= g2;
    v |= g;
    v <<= 8;
    v |= b2;
    v |= b;
    return v;
}
static inline void BuildPalette(uint32_t* pal, uint32_t c0, uint32_t c1, uint32_t raw0, uint32_t raw1)
{
    pal[0] = c0;
    pal[1] = c1;
    if (raw0 > raw1) {
        uint32_t r0 = (c0 >> 16) & 0xff, g0 = (c0 >> 8) & 0xff, b0 = c0 & 0xff;
        uint32_t r1 = (c1 >> 16) & 0xff, g1 = (c1 >> 8) & 0xff, b1 = c1 & 0xff;
        uint32_t t = (0xffffff00u | ((r1 + r0 * 2) / 3)) << 8;
        t |= ((g1 + g0 * 2) / 3) & 0xff;
        t <<= 8;
        t |= ((b1 + b0 * 2) / 3) & 0xff;
        pal[2] = t;
        uint32_t u = (0xffffff00u | ((r0 + r1 * 2) / 3)) << 8;
        u |= ((g0 + g1 * 2) / 3) & 0xff;
        u <<= 8;
        u |= ((b0 + b1 * 2) / 3) & 0xff;
        pal[3] = u;
    } else {
        pal[2] = ((((c1 & 0xfefefe) + (c0 & 0xfefefe)) >> 1) + (c1 & c0 & 0x10101)) | 0xff000000u;
        pal[3] = 0;
    }
}
void mappixeltransparent(uint32_t pix, int* idx, const uint32_t* pal);   // @ 0x007ad400
void __fastcall mappixel(uint32_t pix, const uint32_t* pal, int* idx);    // @ 0x007ad2e0 (pal in eax in the original)
uint32_t rbmappixel(uint32_t pix, const uint32_t* pal);                  // @ 0x007ad760 (pal in esi, pix in edx)
uint32_t trymapblockfast(const uint32_t* px, uint32_t c0, uint32_t c1, uint32_t limit);  // @ 0x007ad950
// ---- items of slice s007ada40 end

// ---- items of slice s007aea30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Endpoint {
    int      v[7];   // +0x00
    uint8_t  c;      // +0x1c
};
// ---- items of slice s007aea30 end

// ---- items of slice s007af8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl EAFree(void* p);                                   // 0x00F47380
void  __cdecl eadxt(void* dst, void* src, int stride, int count, int mode, int quality); // 0x007AF490
void  __cdecl FUN_007ad0c0(void* a, void* b);                    // 0x007AD0C0
bool  __cdecl FUN_007ae910();                                    // 0x007AE910
bool  __cdecl FUN_007b0030();                                    // 0x007B0030
void* __cdecl FUN_0067dcc0();                                    // 0x0067DCC0  MessageServer()
struct CJob {
    int pad0[7];
    int   mSlot;              // +0x1c
    void* mpReturn;           // +0x20
    void* mpCleanup;          // +0x24
    bool Continuation(void* fn, void* arg);   // 0x0068F9F0 __thiscall
};
struct VecCore  { void DestroyRange(void* b, void* e); };        // 0x0070F520 __thiscall
struct VecAssignOp { void Assign(void*, void*, void*, void*, void*); }; // 0x004E8EE0
struct VecGrow  { void* Grow(int n, void* a, void* b); };        // 0x007B0370 __thiscall
struct IMsg { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
              virtual void v4(); virtual void v5(); virtual void v6(void*,void*,int,int); };
struct Elem { char pad[0x28]; unsigned char* data; };           // pixel element at +0x28
struct VecObj { char pad[0xc]; Elem** begin; Elem** end; };     // vector at +0xc
struct cImageDataRaw {
    char pad0[0x1c];
    int mWidth;               // +0x1c
    int mHeight;              // +0x20
    int mFormat;              // +0x24
    unsigned char* mData;     // +0x28
};
struct cDXTCompressJobData {
    char pad0[0xc];
    cImageDataRaw* mSource;   // +0xc
    cImageDataRaw* mOutput;   // +0x10
    int mMode;                // +0x14
    int mQuality;             // +0x18
    int mBlockSize;           // +0x1c
    unsigned mMessageID;      // +0x20
    void* mMessage;           // +0x24
    int DXTCompressRow(int row);
    bool RunJob(CJob* job);
};
struct cRowJobData {
    char pad[0xc];
    VecObj* mP;               // +0xc
    int mMsgId;               // +0x10
    int mMsgArg;              // +0x14
    bool mFlag18;             // +0x18
    bool StepDown(CJob* job);
    bool StepUp(CJob* job);
};
// ---- items of slice s007af8b0 end

// ---- items of slice s007b0a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EAAlloc(unsigned n, const char* name, int a, int b, const char* f, int l); // 0x00F473A0
void  __cdecl DestroyElems(void* first, void* last);              // 0x00B007F0
void  __cdecl RemoveIf(void* a, void* b, void* c);                // 0x0076DE80
void* __cdecl MoveNodes(void* a, void* b, void* c);               // 0x007AF5D0
void  __cdecl MoveNodes2(void* a, void* b, void* c);              // 0x007AF6D0
void* __cdecl DoCopy4(void* first, void* last, void* dest);       // 0x006782C0
void** CopyRefRange4(void** first, void** last, void** dest);     // 0x007B0040
struct T20 {
    int a,b,c,d,e,f,g; char h;
    T20& operator=(const T20& o) { a=o.a;b=o.b;c=o.c;d=o.d;e=o.e;f=o.f;g=o.g;h=o.h; return *this; }
};
struct C20;
void C20_InsertTail(C20* self, T20* pos, int count, void* value); // 0x007B0BE0
struct C20 {
    T20* begin;  T20* end;  T20* cap;                             // +0x0
    char pad0[8];                                                 // +0xc
    int* freeBegin;  int* freeEnd;  int* freeCap;                 // +0x14
    void grow(T20* p, const T20& v);                              // 0x007b0a70
    void push_back(const T20& v);                                 // 0x007b0f40
    void resize(int n);                                           // 0x007b1040
    int  Alloc();                                                 // 0x007b10a0
    void clear();                                                 // 0x007b1950
};
struct C4 {
    void** begin; void** end; void** cap;
    void assign(void** first, void** last);                       // 0x007b0da0
};
// ---- items of slice s007b0a70 end

// ---- items of slice s007b19c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_0067dd60();                       // 0x0067DD60 (RTT manager / factory)
struct S3 { int a, b, c; };
struct IFac {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* v7(S3 s, int z);                  // +0x1C
    virtual void* v8(int,int);                      // +0x20 (RTT create)
};
struct W1e70 {
    void helper(int, void*, void*);
    void f(void* a, void* b);
};
struct W1da0 {
    void Handler(void* r);                          // 0x007B1AF0 __thiscall
    void f(S3* p);
};
// ---- items of slice s007b19c0 end

// @ 0x007ada40
void mapblock(const uint32_t* src, uint8_t* dst, uint32_t c0, uint32_t c1, int mode)
{
    uint32_t pal[4];
    pal[0] = Expand565(c0);
    pal[1] = Expand565(c1);
    dst[0] = (uint8_t)c0;
    dst[2] = (uint8_t)c1;
    dst[1] = (uint8_t)(c0 >> 8);
    dst[3] = (uint8_t)(c1 >> 8);
    if (mode == 0) {
        BuildPalette(pal, pal[0], pal[1], c0, c1);
        for (int row = 0; row < 4; row++) {
            int bits = 0;
            for (int k = 0; k < 8; k += 2) {
                int idx = 0;
                mappixeltransparent(*src, &idx, pal);
                bits |= idx << k;
                src++;
            }
            dst[4 + row] = (uint8_t)bits;
        }
    } else {
        for (int row = 0; row < 4; row++) {
            int bits = 0;
            for (int k = 0; k < 8; k += 2) {
                int idx = 0;
                mappixel(*src, pal, &idx);
                bits |= idx << k;
                src++;
            }
            dst[4 + row] = (uint8_t)bits;
        }
    }
}








// @ 0x007ade70
uint32_t rtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1)
{
    uint32_t pal[4];
    pal[0] = Expand565(raw0);
    pal[1] = Expand565(raw1);
    BuildPalette(pal, pal[0], pal[1], raw0, raw1);
    uint32_t p0 = pal[0] & 0xff, p1 = pal[1] & 0xff, p2 = pal[2] & 0xff, p3 = pal[3] & 0xff;
    uint32_t total = 0;
    const uint8_t* p = (const uint8_t*)src + 2;
    for (int i = 0; i < 16; i++) {
        int v = p[0];
        uint32_t best = 0x7fffffff;
        uint32_t e;
        e = (uint32_t)((v - (int)p0) * (v - (int)p0)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p1) * (v - (int)p1)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p2) * (v - (int)p2)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p3) * (v - (int)p3)); if (e < best) best = e;
        total += best;
        p += 4;
    }
    return total;
}








// @ 0x007ae0b0
uint32_t rbtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1)
{
    uint32_t pal[4];
    pal[0] = Expand565(raw0);
    pal[1] = Expand565(raw1);
    BuildPalette(pal, pal[0], pal[1], raw0, raw1);
    uint32_t total = 0;
    for (int i = 0; i < 16; i++)
        total += rbmappixel(src[i], pal);
    return total;
}








// @ 0x007ae2a0
uint32_t RefineMinMaxColors(const uint32_t* px, uint32_t* out)
{
    uint32_t q[5];
    static const int kSample[5] = { 0, 2, 5, 11, 13 };
    for (int i = 0; i < 5; i++) {
        uint32_t v = px[kSample[i]];
        uint32_t c565 = ((((v >> 3) & 0x1f0000) | (v & 0xfc00)) >> 2 | (v & 0xf8)) >> 3;
        uint32_t base = ((((c565 >> 11) << 3) & 0xff) << 8 | (((c565 >> 5) << 2) & 0xff)) << 8 | ((c565 << 3) & 0xff);
        base &= 0xffffff;
        uint32_t rep = (((((c565 >> 13) & 7) << 8) | ((c565 >> 9) & 3)) << 8) | ((c565 >> 2) & 7);
        q[i] = base | rep;
    }
    uint32_t best = trymapblockfast(px, out[0] & 0xffffff, out[1] & 0xffffff, 0x7fffffff);
    if (best > 8) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                uint32_t c0 = q[i], c1 = q[j];
                if (c0 < c1) {
                    uint32_t e = trymapblockfast(px, c0, c1, best);
                    if (e < best) {
                        best = e;
                        out[0] = c0;
                        out[1] = c1;
                        if (best <= 8) return best;
                    }
                }
            }
        }
    }
    return best;
}








// @ 0x007ae5b0
void FUN_007ae5b0(const uint8_t* src, uint8_t* dst, int stride)
{
    const uint8_t* p = src;
    for (int i = 0; i < 4; i++) {
        dst[i * 2] = (p[7] & 0xf0) | (p[3] >> 4);
        dst[i * 2 + 1] = (p[0xf] & 0xf0) | (p[0xb] >> 4);
        p += stride;
    }
}








// @ 0x007ae840
void FUN_007ae840(const uint8_t* src, int stride, __m64* copy, uint32_t* out)
{
    const uint8_t* p = src;
    __m64 r0 = *(const __m64*)p;
    __m64 r1 = *(const __m64*)(p + 8);
    p += stride;
    __m64 r2 = *(const __m64*)p;
    __m64 r3 = *(const __m64*)(p + 8);
    p += stride;
    __m64 r4 = *(const __m64*)p;
    __m64 r5 = *(const __m64*)(p + 8);
    __m64 r6 = *(const __m64*)(p + stride);
    __m64 r7 = *(const __m64*)(p + stride + 8);
    copy[0] = r0; copy[1] = r1; copy[2] = r2; copy[3] = r3;
    copy[4] = r4; copy[5] = r5; copy[6] = r6; copy[7] = r7;
    __m64 mn = _mm_min_pu8(r0, r1);
    __m64 mx = _mm_max_pu8(r1, copy[0]);
    mn = _mm_min_pu8(mn, r2); mx = _mm_max_pu8(mx, r2);
    mn = _mm_min_pu8(mn, r3); mx = _mm_max_pu8(mx, r3);
    mn = _mm_min_pu8(mn, r4); mx = _mm_max_pu8(mx, r4);
    mn = _mm_min_pu8(mn, r5); mx = _mm_max_pu8(mx, r5);
    mn = _mm_min_pu8(mn, r6); mx = _mm_max_pu8(mx, r6);
    mn = _mm_min_pu8(mn, r7); mx = _mm_max_pu8(mx, r7);
    __m64 mn2 = _mm_srli_si64(mn, 32);
    __m64 mx2 = _mm_srli_si64(mx, 32);
    mn = _mm_min_pu8(mn, mn2);
    mx = _mm_max_pu8(mx, mx2);
    out[0] = (uint32_t)_mm_cvtsi64_si32(mn);
    out[1] = (uint32_t)_mm_cvtsi64_si32(mx);
}








// @ 0x007ae920
void Span::Init(int x, int y, int dx, int dy, int extra)
{
    int* p = (int*)this;
    p[0] = x;
    p[2] = x + dx;
    p[1] = y;
    p[3] = y + dy;
    p[4] = extra;
    p[5] = -1;
    p[6] = -1;
    ((uint8_t*)this)[0x1c] = 0;
}








// @ 0x007ae960
uint8_t FlagHolder::IsSet()
{
    return mpData->mFlag;
}







// @ 0x007af5d0
void FUN_007af5d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    for (; first != last; ++first) {
        if (dest != 0) {
            dest->v[0] = first->v[0];
            dest->v[1] = first->v[1];
            dest->v[2] = first->v[2];
            dest->v[3] = first->v[3];
            dest->v[4] = first->v[4];
            dest->v[5] = first->v[5];
            dest->v[6] = first->v[6];
            dest->c    = first->c;
        }
        ++dest;
    }
}






// @ 0x007af620
void FUN_007af620(Endpoint* first, Endpoint* last, const Endpoint* src)
{
    for (; first != last; ++first) {
        first->v[0] = src->v[0];
        first->v[1] = src->v[1];
        first->v[2] = src->v[2];
        first->v[3] = src->v[3];
        first->v[4] = src->v[4];
        first->v[5] = src->v[5];
        first->v[6] = src->v[6];
        first->c    = src->c;
    }
}






// @ 0x007af670
void FUN_007af670(Endpoint* dest, uint32_t n, const Endpoint* src)
{
    Endpoint* d = dest;
    while (n > 0) {
        if (d != 0) {
            d->v[0] = src->v[0];
            d->v[1] = src->v[1];
            d->v[2] = src->v[2];
            d->v[3] = src->v[3];
            d->v[4] = src->v[4];
            d->v[5] = src->v[5];
            d->v[6] = src->v[6];
            d->c    = src->c;
        }
        --n;
        d = (Endpoint*)((char*)d + 0x20);
    }
}






// @ 0x007af6d0
void FUN_007af6d0(Endpoint* first, Endpoint* last, Endpoint* dest)
{
    while (last != first) {
        last = (Endpoint*)((char*)last - 0x20);
        dest = (Endpoint*)((char*)dest - 0x20);
        dest->v[0] = last->v[0];
        dest->v[1] = last->v[1];
        dest->v[2] = last->v[2];
        dest->v[3] = last->v[3];
        dest->v[4] = last->v[4];
        dest->v[5] = last->v[5];
        dest->v[6] = last->v[6];
        dest->c    = last->c;
    }
}





// @ 0x007afae0
bool cRowJobData::StepDown(CJob* job)
{
    int slot = job->mSlot;
    FUN_007ad0c0((void*)mP->begin[slot], (void*)mP->begin[slot-1]);
    if (--slot == 0) {
        void* oldCln = job->mpCleanup;
        void* oldRet = job->mpReturn;
        job->mpReturn = mP;
        job->mpCleanup = (void*)slot;
        if (oldCln)
            ((void (__cdecl*)(void*))oldCln)(oldRet);
        if (mMsgId) {
            IMsg* s = (IMsg*)FUN_0067dcc0();
            s->v6((void*)mMsgId, (void*)mMsgArg, 0, 0);
        }
        return true;
    }
    job->mSlot = slot;
    return job->Continuation((void*)&FUN_007ae910, this);
}



// @ 0x007afb70
int cDXTCompressJobData::DXTCompressRow(int row)
{
    cImageDataRaw* src = mSource;
    cImageDataRaw* out = mOutput;
    int blocksW = (src->mWidth + 3) >> 2;
    int blockRow = row >> 2;
    if (row + 3 < src->mHeight) {
        unsigned rem = (unsigned)src->mWidth & 3;
        int nBlocks = blocksW;
        if (rem != 0)
            nBlocks = blocksW - 1;
        if (nBlocks > 0) {
            eadxt(out->mData + blockRow * mBlockSize * blocksW,
                  src->mData + src->mWidth * row * 4,
                  src->mWidth * 4, nBlocks, mMode, mQuality);
        }
        if (rem != 0) {
            int stride = src->mWidth;
            int off = nBlocks * 4;
            unsigned char* rowp = src->mData + stride * row * 4;
            int block[16];
            int k = 4;
            do {
                block[0] = (off < stride) ? *(int*)(rowp + nBlocks*0x10)
                                          : *(int*)(rowp + stride*4 - 4);
                block[1] = (off+1 < src->mWidth) ? *(int*)(rowp + 4 + nBlocks*0x10)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                block[2] = (off+2 < src->mWidth) ? *(int*)(rowp + (off+2)*4)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                block[3] = (off+3 < src->mWidth) ? *(int*)(rowp + (off+3)*4)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                stride = src->mWidth;
                rowp += stride * 4;
                k--;
            } while (k);
            eadxt(out->mData + (blockRow * blocksW + nBlocks) * mBlockSize,
                  block, 0x10, 1, mMode, mQuality);
        }
        return 4;
    }
    if (src->mHeight <= row)
        return 0;
    if (blocksW > 0) {
        int dstOff = blockRow * blocksW;
        int srcOff = 0xc;
        int n = blocksW;
        do {
            int* rowp = (int*)(src->mData + src->mWidth * row * 4);
            int col = 2;
            int block[16];
            int m = 0;
            do {
                block[0] = (col-2 < src->mWidth) ? *(int*)((char*)rowp + srcOff-0xc)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[1] = (col-1 < src->mWidth) ? *(int*)((char*)rowp + srcOff-8)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[2] = (col   < src->mWidth) ? *(int*)((char*)rowp + srcOff-4)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[3] = (col+1 < src->mWidth) ? *(int*)((char*)rowp + srcOff)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                if (++m < 4)
                    rowp = (int*)((char*)rowp + src->mWidth*4);
                col += 4;
            } while (m < 4);
            eadxt(out->mData + mBlockSize * dstOff, block, 0x10, 1, mMode, mQuality);
            srcOff += 0x10;
            dstOff++;
            n--;
        } while (n);
    }
    return src->mHeight - row;
}



// @ 0x007afe10
bool cDXTCompressJobData::RunJob(CJob* job)
{
    int row = job->mSlot;
    int work = 0;
    unsigned limit = (9 < mQuality) ? 0x100 : 0x600;
    do {
        int n = DXTCompressRow(row);
        row += n;
        if (mSource->mHeight <= row) {
            void* oldCln = job->mpCleanup;
            void* oldRet = job->mpReturn;
            job->mpReturn = mOutput;
            job->mpCleanup = 0;
            if (oldCln)
                ((void (__cdecl*)(void*))oldCln)(oldRet);
            if (mMessageID) {
                IMsg* s = (IMsg*)FUN_0067dcc0();
                s->v6((void*)mMessageID, mMessage, 0, 0);
            }
            return true;
        }
        work += mSource->mWidth >> 2;
    } while (work < (int)limit);
    job->mSlot = row;
    return job->Continuation((void*)&FUN_007b0030, this);
}



// @ 0x007b0980
void** VecAssign(void** self, void** other)
{
    if (other != self) {
        int n = (int)((char*)other[1] - (char*)other[0]) >> 2;
        if ((int)((char*)self[2] - (char*)self[0]) >> 2 < n) {
            void* p = ((VecGrow*)self)->Grow(n, other[0], other[1]);
            if (self[0] && *((int*)self[0] - 1))
                EAFree(self[0]);
            self[2] = (char*)p + n*4;
            self[1] = (char*)p + n*4;
            self[0] = p;
        } else {
            int cur = (int)((char*)self[1] - (char*)self[0]) >> 2;
            if (cur < n) {
                ((VecCore*)self)->DestroyRange(other[0], (char*)other[0] + cur*4);
                ((VecAssignOp*)self)->Assign(0, (char*)other[0] + cur*4, other[1], self[1], 0);
                self[1] = (char*)self[0] + n*4;
            } else {
                ((VecCore*)other)->DestroyRange(other[0], other[1]);
                ((VecCore*)self)->DestroyRange(self[0], self[1]);
                self[1] = (char*)self[0] + n*4;
            }
        }
    }
    return self;
}


// @ 0x007b0a70
void C20::grow(T20* pos, const T20& v)
{
    T20* e = end;
    if (e != cap) {
        T20* src = pos;
        if (pos <= &v && &v < e)
            src = (T20*)((char*)&v + 0x20);
        if (e) {
            e->a = e[-1].a; e->b = e[-1].b; e->c = e[-1].c; e->d = e[-1].d;
            e->e = e[-1].e; e->f = e[-1].f; e->g = e[-1].g; e->h = e[-1].h;
        }
        MoveNodes2(pos, (char*)e - 0x20, e);
        *pos = v;
        end = (T20*)((char*)e + 0x20);
        return;
    }
    int n = (int)(e - begin);
    n = (n == 0) ? 1 : n * 2;
    T20* p = n ? (T20*)EAAlloc(n << 5, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    T20* q = (T20*)MoveNodes(begin, pos, p);
    if (q)
        *q = v;
    T20* ne = (T20*)MoveNodes(pos, e, (char*)q + 0x20);
    if (begin && *((int*)begin - 1))
        EAFree(begin);
    end = ne;
    cap = (T20*)((char*)p + n*0x20);
    begin = p;
}


// @ 0x007b0da0
void C4::assign(void** first, void** last)
{
    int n = (int)((char*)last - (char*)first) >> 2;
    if ((int)((char*)cap - (char*)begin) >> 2 < n) {
        void** p = (void**)DoCopy4(first, last, 0);   // reuse as grow helper FUN_007b0920
        DestroyElems(begin, end);
        if (begin && *((int*)begin - 1))
            EAFree(begin);
        void** ne = (void**)((char*)p + n*4);
        begin = p; end = ne; cap = ne;
        return;
    }
    int cur = (int)((char*)end - (char*)begin) >> 2;
    if (n <= cur) {
        void** ne = (void**)DoCopy4(first, last, begin);
        DestroyElems(ne, end);
        end = ne;
        return;
    }
    void** mid = (void**)((char*)first + cur*4);
    DoCopy4(first, mid, begin);
    CopyRefRange4(mid, last, end);
    end = (void**)((char*)end + (n - cur)*4);
}


// @ 0x007b0f40
void C20::push_back(const T20& v)
{
    T20* p = end;
    if (p < cap) {
        end = p + 1;
        if (p)
            *p = v;
    } else {
        grow(p, v);
    }
}


// @ 0x007b1040
void C20::resize(int n)
{
    int cnt = (int)(end - begin);
    if (n > cnt) {
        char tmp[0x20];
        C20_InsertTail(this, end, n - cnt, tmp);
    } else {
        T20* ne = begin + n;
        RemoveIf(end, end, ne);
        end = (T20*)((char*)end - ((char*)end - (char*)ne));
    }
}


// @ 0x007b10a0
int C20::Alloc()
{
    if (freeBegin != freeEnd) {
        int v = freeEnd[-1];
        freeEnd--;
        return v;
    }
    int n = (int)(end - begin);
    resize(n + 1);
    return n;
}

// @ 0x007b1da0
void W1da0::f(S3* p)
{
    IFac* fac = (IFac*)FUN_0067dd60();
    Handler(fac->v7(*p, 0));
}

// @ 0x007b1e70
void W1e70::f(void* a, void* b)
{ helper(0, a, b); }
