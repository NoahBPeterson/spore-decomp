// Slice s00fce1e0 (batch gold3) -- rw::movie video renderable manager (mutex-guarded work lists)
// and the SPMovie YUV conversion helpers.
//
//   0x00FCE1E0  push renderable onto the "sent to renderer" list
//   0x00FCE220  count of the "sent to renderer" list
//   0x00FCE250  push renderable onto the "sent to decoder" list
//   0x00FCE290  count of the "sent to decoder" list
//   0x00FCE2C0  pop the head of the "empty" list
//   0x00FCE320  peek the head of the "filled" list
//   0x00FCE380  pop the head of the "filled" list
//   0x00FCE3E0  pop the head of the "sent to renderer" list
//   0x00FCE440  index into the "sent to decoder" list
//   0x00FCE4C0  remove from the "sent to decoder" list and return its frame number
//   0x00FCE560  rw::movie::VideoRenderableManager::VideoRenderableManager
//   0x00FCE690  pack two Y bytes + U + V into 32-bit pixels
//   0x00FCE6E0  YUV -> BGR555 (MMX)
//   0x00FCE750  YUV -> 16-bit dithered (MMX)
//   0x00FCE800  YUV -> two 16-bit dithered pixels (MMX)
//   0x00FCE8E0  YUV422 -> 16-bit (MMX)
//   0x00FCE970  YUV422 pair -> 16-bit (MMX)
//   0x00FCEA20  setlut
//   0x00FCEAA0  setdepth
//   0x00FCEB30  YUV_convert
//   0x00FCEF00  arithmetic bit decode
//   0x00FCEF80  binary arithmetic bit decode
//   0x00FCEFE0  read n bits
//   0x00FCF080  read bits with an explicit bit count
//   0x00FCF0E0  read one bit
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// rw::movie::VideoRenderableManager::VideoRenderableManager is the only name known from the dev
// symbols; every FUN_ name and struct name is a placeholder derived from the addresses.
#include "types.h"
#include <new>
#include <intrin.h>

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;

// ===========================================================================
// EA::Thread::Mutex (0x30 bytes, EAThread)
// ===========================================================================
namespace EA { namespace Thread {
class Mutex {
public:
    Mutex(const void* pParameters = 0, bool bDefaultParameters = true);  // 0x009222A0
    ~Mutex();                                                            // 0x00922130
    int Lock(const void* pTimeoutAbsolute);                              // 0x009221B0
    int Unlock();                                                        // 0x00922270
    u32 mData[0x30 / 4];
};
} }

struct ICoreAllocator {
    virtual void* s00();                                           // +0x00
    virtual void* Alloc(u32 size, const char* name, int a, int b, int c);  // +0x04 (ret 0x14)
    virtual void  Free(void* p, int a);                            // +0x08
};

// ===========================================================================
// rw::core::SList (intrusive list of 4-byte elements)
// ===========================================================================
namespace rw { class SList {
public:
    virtual void  SetAllocator(ICoreAllocator* alloc);       // +0x00
    virtual void  s04();                                     // +0x04
    virtual void  Init(u32 elementSize);                     // +0x08
    virtual void  s0c();                                     // +0x0c
    virtual void  s10();                                     // +0x10
    virtual void  s14();                                     // +0x14
    virtual void  s18();                                     // +0x18
    virtual void  s1c();                                     // +0x1c
    virtual void  s20();                                     // +0x20
    virtual void  s24();                                     // +0x24
    virtual void* GetHead();                                 // +0x28
    virtual void  s2c();                                     // +0x2c
    virtual void* At(u32 i);                                 // +0x30
    virtual void  s34();                                     // +0x34
    virtual void  s38();                                     // +0x38
    virtual u32   Count();                                   // +0x3c
    virtual void  s40();                                     // +0x40
    virtual void  PushBack(void* node, int a);               // +0x44
    virtual void  s48();                                     // +0x48
    virtual void  s4c();                                     // +0x4c
    virtual void  s50();                                     // +0x50
    virtual void  s54();                                     // +0x54
    virtual void  s58();                                     // +0x58
    virtual void  s5c();                                     // +0x5c
    virtual void  s60();                                     // +0x60
    virtual void  s64();                                     // +0x64
    virtual void  s68();                                     // +0x68
    virtual void  s6c();                                     // +0x6c
    virtual void  s70();                                     // +0x70
    virtual void  Remove(void* node, int a);                 // +0x74
    SList();                                                 // 0x00FCCE10
}; }

// work item stored in the lists: vtable + payload, payload[0] is the frame number
struct VideoRenderable {
    virtual u32* GetFrame();                                 // +0x00
};

struct Comparator {
    void* vftable;                                           // +0x00
};

// ===========================================================================
// rw::movie::VideoRenderableManager
// ===========================================================================
struct VideoRenderableManager {
    ICoreAllocator* mAllocator;        // +0x00
    rw::SList*      mEmptyList;        // +0x04
    rw::SList*      mFilledList;       // +0x08
    rw::SList*      mSentToDecoderList;  // +0x0c
    rw::SList*      mSentToRendererList; // +0x10
    u32             mPad14;            // +0x14
    EA::Thread::Mutex mListMutex;      // +0x18
    Comparator      mComparator;       // +0x48

    VideoRenderableManager(ICoreAllocator* alloc);           // 0x00FCE560
    void  AddToRendererList(void* renderable);               // 0x00FCE1E0
    u32   GetRendererListSize();                             // 0x00FCE220
    void  AddToDecoderList(void* renderable);                // 0x00FCE250
    u32   GetDecoderListSize();                              // 0x00FCE290
    u32   PopFromEmptyList();                                // 0x00FCE2C0
    u32   PeekFilledList();                                  // 0x00FCE320
    u32   PopFromFilledList();                               // 0x00FCE380
    u32   PopFromRendererList();                             // 0x00FCE3E0
    u32   GetFromDecoderList(u32 index);                     // 0x00FCE440
    u32   RemoveFromDecoderList(u32 index);                  // 0x00FCE4C0
};

// 0x149219c -- the mutex lock timeout/name token shared by every accessor
extern const char g_listLockToken[];
// 0x14921a0 -- VideoRenderableComparator::vftable
extern const void* g_videoRenderableComparatorVtbl[];

// @ 0x00fce1e0
void VideoRenderableManager::AddToRendererList(void* renderable)
{
    mListMutex.Lock(g_listLockToken);
    int local = (int)renderable;
    mSentToRendererList->PushBack(&local, 0);
    mListMutex.Unlock();
}

// @ 0x00fce220
u32 VideoRenderableManager::GetRendererListSize()
{
    mListMutex.Lock(g_listLockToken);
    u32 n = mSentToRendererList->Count();
    mListMutex.Unlock();
    return n;
}

// @ 0x00fce250
void VideoRenderableManager::AddToDecoderList(void* renderable)
{
    mListMutex.Lock(g_listLockToken);
    int local = (int)renderable;
    mSentToDecoderList->PushBack(&local, 0);
    mListMutex.Unlock();
}

// @ 0x00fce290
u32 VideoRenderableManager::GetDecoderListSize()
{
    mListMutex.Lock(g_listLockToken);
    u32 n = mSentToDecoderList->Count();
    mListMutex.Unlock();
    return n;
}

// @ 0x00fce2c0
u32 VideoRenderableManager::PopFromEmptyList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mEmptyList;
    VideoRenderable* item;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    else
        item = 0;
    u32 frame = 0;
    if (item != 0) {
        frame = item->GetFrame()[0];
        mEmptyList->Remove(item, 0);
    }
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce320
u32 VideoRenderableManager::PeekFilledList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mFilledList;
    VideoRenderable* item = 0;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    if (item != 0) {
        u32 frame = item->GetFrame()[0];
        mListMutex.Unlock();
        return frame;
    }
    mListMutex.Unlock();
    return 0;
}

// @ 0x00fce380
u32 VideoRenderableManager::PopFromFilledList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mFilledList;
    VideoRenderable* item;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    else
        item = 0;
    u32 frame = 0;
    if (item != 0) {
        frame = item->GetFrame()[0];
        mFilledList->Remove(item, 0);
    }
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce3e0
u32 VideoRenderableManager::PopFromRendererList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mSentToRendererList;
    VideoRenderable* item;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    else
        item = 0;
    u32 frame = 0;
    if (item != 0) {
        frame = item->GetFrame()[0];
        mSentToRendererList->Remove(item, 0);
    }
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce440
u32 VideoRenderableManager::GetFromDecoderList(u32 index)
{
    mListMutex.Lock(g_listLockToken);
    VideoRenderable* item;
    if (index == 0) {
        if (mSentToDecoderList->Count() == 0)
            goto fail;
        item = (VideoRenderable*)mSentToDecoderList->GetHead();
    } else {
        if (mSentToDecoderList->Count() < index)
            goto fail;
        item = (VideoRenderable*)mSentToDecoderList->At(index);
    }
    if (item == 0)
        goto fail;
    {
        u32 frame = item->GetFrame()[0];
        mSentToDecoderList->Remove(item, 0);
        mListMutex.Unlock();
        return frame;
    }
fail:
    mListMutex.Unlock();
    return 0;
}

// @ 0x00fce4c0
u32 VideoRenderableManager::RemoveFromDecoderList(u32 index)
{
    mListMutex.Lock(g_listLockToken);
    VideoRenderable* item;
    u32 frame = 0;
    if (index == 0) {
        if (mSentToDecoderList->Count() == 0)
            goto done;
        item = (VideoRenderable*)mSentToDecoderList->GetHead();
        if (item == 0)
            goto done;
    } else {
        if (mSentToDecoderList->Count() < index)
            goto done;
        item = (VideoRenderable*)mSentToDecoderList->At(index);
        if (item == 0)
            goto done;
    }
    frame = item->GetFrame()[0];
    mSentToDecoderList->Remove(item, 0);
done:
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce560
VideoRenderableManager::VideoRenderableManager(ICoreAllocator* alloc)
{
    mComparator.vftable = (void*)g_videoRenderableComparatorVtbl;
    mAllocator = alloc;
    mEmptyList = (rw::SList*)mAllocator->Alloc(0x1c, "Empty List", 0, 4, 0);
    if (mEmptyList != 0)
        mEmptyList = new (mEmptyList) rw::SList;
    mEmptyList->Init(4);
    mEmptyList->SetAllocator(mAllocator);
    mFilledList = (rw::SList*)mAllocator->Alloc(0x1c, "Filled List", 0, 4, 0);
    if (mFilledList != 0)
        mFilledList = new (mFilledList) rw::SList;
    mFilledList->Init(4);
    mFilledList->SetAllocator(mAllocator);
    mSentToRendererList =
        (rw::SList*)mAllocator->Alloc(0x1c, "Sent To Renderer List", 0, 4, 0);
    if (mSentToRendererList != 0)
        mSentToRendererList = new (mSentToRendererList) rw::SList;
    mSentToRendererList->Init(4);
    mSentToRendererList->SetAllocator(mAllocator);
    mSentToDecoderList =
        (rw::SList*)mAllocator->Alloc(0x1c, "Sent To Decoder List", 0, 4, 0);
    if (mSentToDecoderList != 0)
        mSentToDecoderList = new (mSentToDecoderList) rw::SList;
    mSentToDecoderList->Init(4);
    mSentToDecoderList->SetAllocator(mAllocator);
}

// ===========================================================================
// YUV helpers (SPMovie/yuvconv.obj)
// ===========================================================================
// 0x15b1818 / 0x15b2018 / 0x15b2818: 256-entry MMX LUTs (8 bytes per entry), swapped in place
// by setlut between the R and B orderings.
extern u16 g_tblY[];        // 0x15b1818
extern u16 g_tblU[];        // 0x15b2018
extern u16 g_tblV[];        // 0x15b2818
extern unsigned long long g_mask7f7f;      // 0x15b3018
extern u32 g_rgMask0[2];    // 0x16d7160
extern u32 g_rgMask1[2];    // 0x16d7168
extern u32 g_ditherSwitch[2];  // 0x16d8178
extern u32 g_chanMask[2];   // 0x16d8180
extern u32 g_dither[2];     // 0x16d8188
extern u32 g_lutCurrent;    // 0x16d9198
extern u8  g_convertScratch[];   // 0x16d8190
extern u8  g_convertScratch2[];  // 0x16d7170

// @ 0x00fce690
void PackYuvPixels(const u8* y, const u8* u, const u8* v, u32* dst, const u32* end)
{
    do {
        *dst++ = ((u32)*v++ << 24) | ((u32)y[1] << 16) | ((u32)*u++ << 8) | (u32)y[0];
        y += 2;
    } while (dst != end);
}

// @ 0x00fce6e0
void ConvertYuvToRgb555(const u8* y, const u8* u, const u8* v, void* dst_, const void* end_)
{
    __m64* dst = (__m64*)dst_;
    const __m64* end = (const __m64*)end_;
    do {
        __m64 uv = _mm_add_pi16(*(const __m64*)((const u8*)g_tblU + *u++ * 8),
                                *(const __m64*)((const u8*)g_tblV + *v++ * 8));
        *dst++ = _mm_packs_pu16(
            _mm_add_pi16(*(const __m64*)((const u8*)g_tblY + y[0] * 8), uv),
            _mm_add_pi16(*(const __m64*)((const u8*)g_tblY + y[1] * 8), uv));
        y += 2;
    } while (dst != end);
}

// @ 0x00fce750
void ConvertYuvDither(const u8* y, const u8* u, const u8* v, u32* dst, const u32* end)
{
    __m64 dith = *(const __m64*)g_dither;
    __m64 mask0 = *(const __m64*)g_rgMask0;
    __m64 mask1 = *(const __m64*)g_rgMask1;
    __m64 chan = *(const __m64*)g_chanMask;
    do {
        __m64 uv = _mm_add_pi16(*(const __m64*)((const u8*)g_tblU + *u++ * 8),
                                *(const __m64*)((const u8*)g_tblV + *v++ * 8));
        __m64 p0 = _mm_add_pi16(*(const __m64*)((const u8*)g_tblY + y[0] * 8), uv);
        __m64 p1 = _mm_add_pi16(*(const __m64*)((const u8*)g_tblY + y[1] * 8), uv);
        y += 2;
        __m64 px = _mm_packs_pu16(p0, p1);
        px = _mm_adds_pu8(px, dith);
        __m64 lo = _mm_and_si64(px, mask0);
        __m64 hi = _mm_and_si64(px, chan);
        lo = _mm_madd_pi16(lo, mask1);
        hi = _mm_srli_pi32(hi, 0xb);
        __m64 res = _mm_or_si64(lo, hi);
        res = _mm_or_si64(res, _mm_srli_si64(res, 0x10));
        *dst++ = (u32)_mm_cvtsi64_si32(res);
    } while (dst != end);
}

// @ 0x00fce800
void ConvertYuvDither2(const u8* y, const u8* u, const u8* v, u32* dst, const u32* end)
{
    __m64 dith = *(const __m64*)g_dither;
    __m64 mask0 = *(const __m64*)g_rgMask0;
    __m64 mask1 = *(const __m64*)g_rgMask1;
    __m64 chan = *(const __m64*)g_chanMask;
    do {
        __m64 uv = _mm_add_pi16(*(const __m64*)((const u8*)g_tblU + *u++ * 8),
                                *(const __m64*)((const u8*)g_tblV + *v++ * 8));
        __m64 p0 = _mm_add_pi16(*(const __m64*)((const u8*)g_tblY + y[0] * 8), uv);
        __m64 p1 = _mm_add_pi16(*(const __m64*)((const u8*)g_tblY + y[1] * 8), uv);
        y += 2;
        __m64 px0 = _mm_adds_pu8(_mm_packs_pu16(p0, p0), dith);
        __m64 px1 = _mm_adds_pu8(_mm_packs_pu16(p1, p1), dith);
        __m64 lo0 = _mm_madd_pi16(_mm_and_si64(px0, mask0), mask1);
        __m64 lo1 = _mm_madd_pi16(_mm_and_si64(px1, mask0), mask1);
        __m64 hi0 = _mm_srli_pi32(_mm_and_si64(px0, chan), 0xb);
        __m64 hi1 = _mm_srli_pi32(_mm_and_si64(px1, chan), 0xb);
        __m64 res0 = _mm_or_si64(lo0, hi0);
        __m64 res1 = _mm_or_si64(lo1, hi1);
        res0 = _mm_or_si64(res0, _mm_srli_si64(res0, 0x10));
        res1 = _mm_or_si64(res1, _mm_srli_si64(res1, 0x10));
        dst[0] = (u32)_mm_cvtsi64_si32(res0);
        dst[1] = (u32)_mm_cvtsi64_si32(res1);
        dst += 2;
    } while (dst != end);
}

// @ 0x00fce8e0
void ConvertYuv422To16(const u32* src, u32* dst, const u32* end)
{
    __m64 mask7f = *(__m64*)&g_mask7f7f;
    __m64 dith = *(const __m64*)g_dither;
    __m64 mask0 = *(const __m64*)g_rgMask0;
    __m64 mask1 = *(const __m64*)g_rgMask1;
    __m64 chan = *(const __m64*)g_chanMask;
    u32 prev = *src >> 1 & 0x7f7f7f7f;
    do {
        u32 cur = *src++;
        u32 half = cur >> 1 & 0x7f7f7f7f;
        __m64 acc = _mm_add_pi8(_mm_cvtsi32_si64(prev), _mm_cvtsi32_si64(half));
        acc = _mm_add_pi32(acc, _mm_slli_si64(_mm_cvtsi32_si64(cur), 0x20));
        acc = _mm_adds_pu8(acc, dith);
        __m64 lo = _mm_madd_pi16(_mm_and_si64(acc, mask0), mask1);
        __m64 hi = _mm_srli_pi32(_mm_and_si64(acc, chan), 0xb);
        __m64 res = _mm_or_si64(lo, hi);
        res = _mm_or_si64(res, _mm_srli_si64(res, 0x10));
        *dst++ = (u32)_mm_cvtsi64_si32(res);
        prev = half;
    } while (dst != end);
}

// @ 0x00fce970
void ConvertYuv422PairTo16(const u32* a, const u32* b, u32* dst, const u32* end)
{
    __m64 mask7f = *(__m64*)&g_mask7f7f;
    __m64 dith = *(const __m64*)g_dither;
    __m64 mask0 = *(const __m64*)g_rgMask0;
    __m64 mask1 = *(const __m64*)g_rgMask1;
    __m64 chan = *(const __m64*)g_chanMask;
    u32 pa = *a >> 1 & 0x7f7f7f7f;
    u32 pb = *b >> 1 & 0x7f7f7f7f;
    u32 prev = (u32)_mm_cvtsi64_si32(
        _mm_add_pi8(_mm_cvtsi32_si64(pa), _mm_cvtsi32_si64(pb)));
    do {
        u32 ca = *a++ >> 1 & 0x7f7f7f7f;
        u32 cb = *b++ >> 1 & 0x7f7f7f7f;
        u32 sum = (u32)_mm_cvtsi64_si32(
            _mm_add_pi8(_mm_cvtsi32_si64(ca), _mm_cvtsi32_si64(cb)));
        u32 half = sum >> 1 & 0x7f7f7f7f;
        __m64 acc = _mm_add_pi8(_mm_cvtsi32_si64(prev), _mm_cvtsi32_si64(half));
        acc = _mm_add_pi32(acc, _mm_slli_si64(_mm_cvtsi32_si64(sum), 0x20));
        acc = _mm_adds_pu8(acc, dith);
        __m64 lo = _mm_madd_pi16(_mm_and_si64(acc, mask0), mask1);
        __m64 hi = _mm_srli_pi32(_mm_and_si64(acc, chan), 0xb);
        __m64 res = _mm_or_si64(lo, hi);
        res = _mm_or_si64(res, _mm_srli_si64(res, 0x10));
        *dst++ = (u32)_mm_cvtsi64_si32(res);
        prev = half;
    } while (dst != end);
}

// @ 0x00fcea20
void __fastcall setlut(int unused, int lut)
{
    if (g_lutCurrent == (u32)lut)
        return;
    int i = 0;
    do {
        u16 a = *(u16*)((u8*)g_tblY + i);
        u16 b = *(u16*)((u8*)g_tblY + i + 2);
        *(u16*)((u8*)g_tblY + i) = b;
        u16 c = *(u16*)((u8*)g_tblU + i + 2);
        *(u16*)((u8*)g_tblY + i + 2) = a;
        u16 d = *(u16*)((u8*)g_tblU + i);
        *(u16*)((u8*)g_tblU + i) = c;
        u16 e = *(u16*)((u8*)g_tblV + i + 2);
        *(u16*)((u8*)g_tblU + i + 2) = d;
        u16 f = *(u16*)((u8*)g_tblV + i);
        *(u16*)((u8*)g_tblV + i) = e;
        *(u16*)((u8*)g_tblV + i + 2) = f;
        i += 8;
    } while (i < 0x7f8);
    g_lutCurrent = (u32)lut;
}

// @ 0x00fceaa0
void setdepth(int depth)
{
    setlut(0, 1);
    g_dither[1] = 0;
    u32 mask;
    if (depth == 0) {
        g_ditherSwitch[0] = 0x60606;
        g_ditherSwitch[1] = 0x60606;
        g_rgMask0[0] = 0x1f800f8;
        g_rgMask0[1] = 0x1f800f8;
        g_dither[0] = 0x40404;
        mask = 0x800004;
    } else {
        g_ditherSwitch[0] = 0x60603;
        g_ditherSwitch[1] = 0x60603;
        g_rgMask0[0] = 0xf800fc;
        g_rgMask0[1] = 0xf800fc;
        g_dither[0] = 0x40402;
        mask = 0x1000008;
    }
    g_rgMask1[0] = mask;
    g_rgMask1[1] = mask;
    g_chanMask[1] = 0xf800;
    g_chanMask[0] = 0xf800;
}

// @ 0x00fceb30
int YUV_convert(const u8* y, const u8* u, const u8* v, int yStride, int width,
                int height, u8* dst, int dstStride, int format)
{
    if ((u32)format > 7)
        return 1;
    if (yStride & 1)
        return 2;
    if (format == 1) {
        if (dstStride & 7)
            return 3;
        if ((int)dst & 7) {
            if ((int)dst & 3)
                return 4;
            dst += 4;
        }
    } else {
        if (dstStride & 3)
            return 3;
        if ((int)dst & 3) {
            if ((int)dst & 1)
                return 4;
            dst += 2;
        }
    }
    int w = width & ~1;
    if (format == 7 && w > 0x400)
        return 5;
    if (w < 2 || height < 1)
        return 0;
    const u8* vrow = v;
    int bytesPerRow = (format == 0 || format == 2 || format == 3) ? w * 2 : w * 4;
    int uStep = yStride >> 1;
    int row;
    switch (format) {
    case 0:
        for (row = 0; row < height; row++) {
            PackYuvPixels(y, u, vrow, (u32*)dst, (u32*)(dst + bytesPerRow));
            y += yStride;
            if (row & 1)
                u += uStep;
            vrow += yStride;
            dst += dstStride;
        }
        return 0;
    case 1:
        setlut(0, 0);
        for (row = 0; row < height; row++) {
            ConvertYuvToRgb555(y, u, vrow, (__m64*)dst, (__m64*)(dst + bytesPerRow));
            y += yStride;
            if (row & 1)
                u += uStep;
            vrow += yStride;
            dst += dstStride;
        }
        _mm_empty();
        return 0;
    case 2:
    case 3:
        setdepth(format & 1);
        for (row = 0; row < height; row++) {
            ConvertYuvDither(y, u, vrow, (u32*)dst, (u32*)(dst + bytesPerRow));
            y += yStride;
            if (row & 1)
                u += uStep;
            g_dither[0] ^= g_ditherSwitch[0];
            g_dither[1] ^= g_ditherSwitch[1];
            vrow += yStride;
            dst += dstStride;
        }
        _mm_empty();
        return 0;
    case 4:
    case 5:
        setdepth(format & 1);
        for (row = 0; row < height; row++) {
            ConvertYuvDither2(y, u, vrow, (u32*)dst, (u32*)(dst + bytesPerRow));
            y += yStride;
            if (row & 1)
                u += uStep;
            g_dither[0] ^= g_ditherSwitch[0];
            g_dither[1] ^= g_ditherSwitch[1];
            vrow += yStride;
            dst += dstStride;
        }
        _mm_empty();
        return 0;
    case 6:
    case 7: {
        setdepth(format & 1);
        ConvertYuvToRgb555(y, u, vrow, (__m64*)g_convertScratch2,
                           (__m64*)(g_convertScratch2 + bytesPerRow));
        for (row = 0; row < height; row++) {
            ConvertYuvToRgb555(y, u, vrow, (__m64*)g_convertScratch,
                               (__m64*)(g_convertScratch + bytesPerRow));
            ConvertYuv422To16((u32*)g_convertScratch, (u32*)dst, (u32*)(dst + bytesPerRow));
            g_dither[0] ^= g_ditherSwitch[0];
            ConvertYuv422PairTo16((u32*)g_convertScratch, (u32*)g_convertScratch2, (u32*)dst,
                                  (u32*)(dst + bytesPerRow));
            g_dither[1] ^= g_ditherSwitch[1];
            g_dither[0] ^= g_ditherSwitch[0];
            y += yStride;
            if (row & 1)
                u += uStep;
            vrow += yStride;
            dst += dstStride;
        }
        _mm_empty();
        return 0;
    }
    }
    return 0;
}

// ===========================================================================
// Arithmetic bit-stream reader (SPMovie)
// ===========================================================================
struct BitState {
    u32 pad00;      // +0x00
    u32 range;      // +0x04
    u32 value;      // +0x08
    int bits;       // +0x0c
    int pos;        // +0x10
    u8* buf;        // +0x14
};

// @ 0x00fcef00
int DecodeBit(BitState* s, int prob)
{
    u32 range = s->range;
    u32 low = ((range - 1) * (u32)prob >> 8) + 1;
    int bits = s->bits;
    u32 value = s->value;
    u32 cmp = low << 24;
    int high = 0;
    if (value >= cmp) {
        low = range - low;
        value -= cmp;
        high = 1;
    }
    if (low < 0x80) {
        do {
            low += low;
            value += value;
            if (--bits == 0) {
                value |= s->buf[s->pos];
                bits = 8;
                s->pos++;
            }
        } while (low < 0x80);
        s->bits = bits;
    }
    s->value = value;
    s->range = low;
    return high;
}

// @ 0x00fcef80
int DecodeBitProb(BitState* s)
{
    u32 range = s->range;
    u32 value = s->value;
    int bits = s->bits;
    u32 half = (range + 1) >> 1;
    int high;
    if (value >= (half << 24)) {
        value -= half << 24;
        range -= half;
        high = 1;
    } else {
        range = half;
        high = 0;
    }
    range += range;
    value += value;
    if (--bits == 0) {
        value |= s->buf[s->pos];
        s->pos++;
        bits = 8;
    }
    s->range = range;
    s->bits = bits;
    s->value = value;
    return high;
}

// @ 0x00fcefe0
u32 ReadBits(BitState* s, int count)
{
    count--;
    u32 out = 0;
    if (count < 0)
        return 0;
    do {
        u32 range = s->range;
        u32 value = s->value;
        int bits = s->bits;
        u32 half = (range + 1) >> 1;
        u32 bit;
        if (value >= (half << 24)) {
            range -= half;
            value -= half << 24;
            bit = 1;
        } else {
            range = half;
            bit = 0;
        }
        range += range;
        value += value;
        if (--bits == 0) {
            value |= s->buf[s->pos];
            s->pos++;
            bits = 8;
        }
        s->bits = bits;
        out |= bit << count;
        s->range = range;
        s->value = value;
        count--;
    } while (count >= 0);
    return out;
}

// ===========================================================================
// 64-bit bit-cache reader; the original receives its state in EAX and the bit count in ECX,
// which C++ cannot express, so the state is an explicit first parameter here.
// ===========================================================================
struct BitCache {
    int count;      // +0x00
    u32 cache;      // +0x04
    const u8* p;    // +0x08
};

// 0x14923e8 -- the masks used to drop the already-consumed high bits of the cache
extern u32 g_bitMask[];    // 0x14923e8

// @ 0x00fcf080
u32 ReadCachedBits(BitCache* s, int count)
{
    u32 keep = g_bitMask[s->count];
    s->cache &= keep;
    int shift = count - s->count;
    u32 out = 0;
    if (shift > 0) {
        out = s->cache << shift;
        const u8* p = s->p;
        s->cache = ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
        s->p = p + 4;
        shift -= 0x20;
    }
    s->count = -shift;
    return s->cache >> (-shift) | out;
}

// @ 0x00fcf0e0
u32 ReadCachedBit(BitCache* s)
{
    if (s->count != 0) {
        int n = --s->count;
        return (s->cache >> n) & 1;
    }
    const u8* p = s->p;
    s->cache = ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
    s->p = p + 4;
    s->count = 0x1f;
    return s->cache >> 31;
}
