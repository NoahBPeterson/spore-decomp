// Slice s007acbb0 — DXT block downsampling / matching helpers used by the
// texture manager (0x7acbb0..0x7ad950).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <mmintrin.h>
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// @ 0x007ace40
// 2x2 box filter of byte pixels, averaging two rows of `width` pixels.
void FUN_007ace40(uint8_t* dest, int destStride, uint8_t* src, int srcStride, int width, int height)
{
    uint8_t* d = dest;
    uint8_t* s2 = src + srcStride;
    int step = (srcStride - width) * 2;
    int pad = destStride - width;
    do {
        int n = width;
        do {
            *d = (uint8_t)((src[1] + s2[1] + s2[0] + src[0] + 2) >> 2);
            d++;
            src += 2;
            s2 += 2;
        } while (--n);
        d += pad;
        src += step;
        s2 += step;
    } while (--height);
}

// ---------------------------------------------------------------------------
// @ 0x007aceb0
// Vertical 2-tap average of a single byte column.
void FUN_007aceb0(uint8_t* dest, int destStride, uint8_t* src, int srcStride, int rows)
{
    uint8_t* d = dest;
    uint8_t* s2 = src + srcStride;
    int step = srcStride * 2;
    do {
        *d = (uint8_t)((src[0] + s2[0] + 1) >> 1);
        d += destStride;
        src += step;
        s2 += step;
    } while (--rows);
}

// ---------------------------------------------------------------------------
// @ 0x007acef0
// 2x2 box filter of 32-bit RGBA pixels (SWAR byte average), two rows.
void FUN_007acef0(uint32_t* dest, int destStride, uint32_t* src, int srcStride, int width, int height)
{
    uint32_t* d = dest;
    uint32_t* s2 = (uint32_t*)((char*)src + srcStride);
    int step = (srcStride - width * 4) * 2;
    int pad = destStride - width * 4;
    do {
        int n = width;
        do {
            uint32_t a = (src[1] | src[0]) - (((src[1] ^ src[0]) >> 1) & 0x7f7f7f7f);
            uint32_t b = (s2[1] | s2[0]) - (((s2[1] ^ s2[0]) >> 1) & 0x7f7f7f7f);
            *d = (a | b) - (((a ^ b) >> 1) & 0x7f7f7f7f);
            d++;
            src += 2;
            s2 += 2;
        } while (--n);
        d = (uint32_t*)((char*)d + pad);
        src = (uint32_t*)((char*)src + step);
        s2 = (uint32_t*)((char*)s2 + step);
    } while (--height);
}

// ---------------------------------------------------------------------------
// @ 0x007acfa0
// Vertical 2-tap average of a single 32-bit RGBA column (SWAR).
void FUN_007acfa0(uint32_t* dest, int destStride, uint32_t* src, int srcStride, int rows)
{
    uint32_t* d = dest;
    uint32_t* s2 = (uint32_t*)((char*)src + srcStride);
    int step = srcStride * 2;
    do {
        *d = (*s2 | *src) - (((*s2 ^ *src) >> 1) & 0x7f7f7f7f);
        d = (uint32_t*)((char*)d + destStride);
        src = (uint32_t*)((char*)src + step);
        s2 = (uint32_t*)((char*)s2 + step);
    } while (--rows);
}

// ---------------------------------------------------------------------------
// @ 0x007acfe0
// Dispatch a downsampling of one DXT surface into another.
// fields: +0x1c width/height-scaled, +0x20, +0x24 format, +0x28 data pointer.
struct DXTDesc {
    char     mPad00[0x1c];
    int      mField1c;   // +0x1c
    int      mField20;   // +0x20
    int      mFormat;    // +0x24
    void*    mpData;     // +0x28
};

bool FUN_007acfe0(DXTDesc* dst, DXTDesc* src)
{
    int s1c = src->mField1c;
    int d1c = dst->mField1c;
    if ((d1c == s1c * 2) || ((d1c == 1) && (s1c == 1))) {
        int s20 = src->mField20;
        if (((dst->mField20 == s20 * 2) || ((dst->mField20 == 1) && (s20 == 1))) &&
            (dst->mFormat == src->mFormat)) {
            int n1c = d1c;
            int n1c2 = s1c;
            if (dst->mFormat == 2) {
                n1c = d1c * 4;
                n1c2 = s1c * 4;
            }
            if (dst->mField20 == 1)
                n1c = 0;
            if (dst->mFormat == 1) {
                if (d1c > 1) {
                    FUN_007ace40((uint8_t*)src->mpData, n1c2, (uint8_t*)dst->mpData, n1c, s1c, s20);
                    return true;
                }
                FUN_007aceb0((uint8_t*)src->mpData, n1c2, (uint8_t*)dst->mpData, n1c, s20);
                return true;
            }
            if (dst->mFormat == 2) {
                if (d1c > 1) {
                    FUN_007acef0((uint32_t*)src->mpData, n1c2, (uint32_t*)dst->mpData, n1c, s1c, s20);
                    return true;
                }
                FUN_007acfa0((uint32_t*)src->mpData, n1c2, (uint32_t*)dst->mpData, n1c, s20);
                return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// cTextureManager front end (texture cache + streamed load queue).
//
// Only the members that the two accessors touch are described; the offsets come
// from the original code:
//   +0x20 Mutex                 +0x58 eastl hash table (Key -> instance)
//   +0xc8 mLoadQueue.mBase      +0xd4 mLoadQueue (StallUntilLoadedUnderLock)
// A cTextureInstanceInternal begins with a Key at +0, an unknown dword at +8 and
// a flag byte at +0xc (bit 0 = "has instance", bit 2 = "load failed").
class cTextureInstanceInternal
{
public:
    int  mKey[2];      // +0x00 ResourceMan::Key
    void* mpInstance;  // +0x08 returned to the caller
    char  mFlags;      // +0x0c
};

class cTextureLoadRequest
{
public:
    int   mKey;                       // +0x00
    int   mInstanceKey;               // +0x04 loaded as an immediate by the original
    void* mpSyncInstance;             // +0x08 released through its second vtable slot
};

extern unsigned int g_LockFlags;   // 0x0140fa10
class TextureMutex
{
public:
    char mData[0x20];
    void Lock(unsigned int* pFlags);   // 0x009221b0
    void Unlock();                     // 0x00922270
};

class ResourceManager
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual bool IsLoaded(const void* pArg1, void* pArg2);  // +0x14
};

__declspec(noinline) void* GetManager();                                  // 0x0067dcd0

// The eastl hashtable used by cTextureManager; only the three fields that the
// original code reads are modelled (bucket pointer, bucket count, element count).
class eastl_hash_table
{
public:
    void* Find(const void* pKey);   // 0x00833840 (base_prime_rehash_policy_0_1_1::find)

    void* mpBuckets;                // +0x00
    int   mnBuckets;                // +0x04
    int   mnElementCount;           // +0x08
};

class ResourceKey
{
public:
    int mKeyA;   // +0x00
    int mKeyB;   // +0x04
    int mKeyC;   // +0x08
};

class cTextureManager
{
public:
    void InitTextureCacheEntry(cTextureInstanceInternal* pEntry)
    {
        pEntry->mpInstance = (void*)((char*)this + 0xc8);   // mLoadQueue.mBase
    }

    cTextureInstanceInternal* GetTextureSync(ResourceKey* pKey, int, int, unsigned int);   // 0x007ac750
    cTextureInstanceInternal* GetTextureAsync(ResourceKey* pKey, int, int, unsigned int);  // 0x007ac850
    bool StallUntilLoadedUnderLock(cTextureInstanceInternal*);                             // 0x007ac8d0

    char* GetTexture(ResourceKey* pKey, unsigned int key, int pad, unsigned int useFlags);
    bool  StallUntilLoaded(cTextureInstanceInternal* pInstance);

private:
    char mPad00[0x20];
    TextureMutex mMutex;                            // +0x20
    char mPad50[8];
    eastl_hash_table mTextureInstanceMap;           // +0x58
    char mPad_00c8[0x0c];
    void* mpLoadQueueBase;                          // +0xc8
    char mPad_00cc[0x08];
    char mLoadQueue[0x100];                         // +0xd4
};

// ---------------------------------------------------------------------------
// @ 0x007acbb0
char* cTextureManager::GetTexture(ResourceKey* pKey, unsigned int key, int pad, unsigned int useFlags)
{
    mMutex.Lock(&g_LockFlags);
    cTextureInstanceInternal* pInstance = (cTextureInstanceInternal*)mTextureInstanceMap.Find(pKey);
    if (pInstance == (cTextureInstanceInternal*)((char*)mTextureInstanceMap.mpBuckets + mTextureInstanceMap.mnBuckets * 4))
    {
        cTextureInstanceInternal* pLoaded = (cTextureInstanceInternal*)((char*)this + 0xc8);
        if (useFlags & 2)
            pLoaded = GetTextureSync(pKey, 0, pad, useFlags);
        else
        {
            cTextureLoadRequest request;
            request.mKey = key;
            request.mInstanceKey = pad;
            ResourceManager* pManager = (ResourceManager*)GetManager();
            bool loaded = pManager->IsLoaded(&request, &pLoaded);
            pLoaded = loaded ? GetTextureSync(pKey, pad, pad, useFlags)
                             : GetTextureAsync(pKey, pad, pad, useFlags);
        }
        mMutex.Unlock();
        return (char*)pLoaded;
    }
    cTextureInstanceInternal* pEntry = *(cTextureInstanceInternal**)((char*)&pInstance->mFlags + 0x2c);
    InitTextureCacheEntry(pEntry);
    if ((useFlags & 2) && !(pEntry->mFlags & 1))
    {
        StallUntilLoadedUnderLock((cTextureInstanceInternal*)((char*)pEntry - 8));
        if (!(pEntry->mFlags & 4))
        {
            mMutex.Unlock();
            return 0;
        }
    }
    mMutex.Unlock();
    return (char*)pEntry->mpInstance;
}

// @ 0x007acd90
bool cTextureManager::StallUntilLoaded(cTextureInstanceInternal* pInstance)
{
    cTextureInstanceInternal* pEntry = pInstance ? (cTextureInstanceInternal*)((char*)pInstance - 8) : 0;
    if (pEntry->mFlags & 1)
        return (pEntry->mFlags & 4) == 0;
    mMutex.Lock(&g_LockFlags);
    StallUntilLoadedUnderLock((cTextureInstanceInternal*)pInstance);
    bool loaded = (pEntry->mFlags & 4) == 0;
    mMutex.Unlock();
    return loaded;
}

// ---------------------------------------------------------------------------
// The DXT surface descriptor DXTDesc (declared above) is reused here.

static __forceinline void AccWeighted(uint8_t& dest, int srcByte, int weight)
{
    int v = srcByte * weight + 0x80;
    uint8_t add = (uint8_t)(((unsigned)(v >> 8) + (unsigned)v) >> 8);
    dest = (uint8_t)(dest + add);
}

// @ 0x007ad0c0
// Blends one RGB source pixel into a 2x2 block of the destination image using the
// destination's own alpha as the inverse weight (the alpha nibbles were written by
// an earlier pass). `params` describes the source surface, `image` the RGBA4444
// destination whose rows are twice as wide.
bool FUN_007ad0c0(DXTDesc* params, DXTDesc* image)
{
    if (params->mFormat != 2)
        return false;
    int nRows = params->mField20;
    int nCols = params->mField1c;
    if (nRows <= 0)
        return true;
    uint8_t* pSrc = (uint8_t*)params->mpData;
    uint8_t* pDst = (uint8_t*)image->mpData;
    int rowBytes = image->mField1c * 4;
    uint8_t* pFirst = pSrc + 2;
    for (int y = 0; y < nRows; ++y)
    {
        uint8_t* pA = pDst + 2 * rowBytes * y;
        uint8_t* pB = pDst + rowBytes + 2 * rowBytes * y;
        uint8_t* pS = pFirst + 4 * nCols * y;
        for (int x = 0; x < nCols; ++x)
        {
            int s0 = pS[-2];
            int s1 = pS[-1];
            int s2 = pS[0];
            uint8_t* pA0 = pA + 8 * x;
            uint8_t* pB0 = pB + 8 * x;
            int w = 0xff - pA0[3];
            AccWeighted(pA0[0], s0, w); AccWeighted(pA0[1], s1, w); AccWeighted(pA0[2], s2, w);
            w = 0xff - pA0[7];
            AccWeighted(pA0[4], s0, w); AccWeighted(pA0[5], s1, w); AccWeighted(pA0[6], s2, w);
            w = 0xff - pB0[3];
            AccWeighted(pB0[0], s0, w); AccWeighted(pB0[1], s1, w); AccWeighted(pB0[2], s2, w);
            w = 0xff - pB0[7];
            AccWeighted(pB0[4], s0, w); AccWeighted(pB0[5], s1, w); AccWeighted(pB0[6], s2, w);
            pS += 4;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007ad2e0
// Selects the index (0 = c0, 1 = c1, 2/3 = the two interpolants) of the DXT1
// colour line that is closest to `pixel` in RGB, and returns the squared error.
// Original LTCG ABI: the candidate array is passed in eax and the pixel in ecx.
uint32_t mappixel(uint32_t* colors, uint32_t pixel, uint32_t* outIndex)
{
    int d0 = (int)(colors[0] & 0xff) - (int)(colors[1] & 0xff);
    int d1 = (int)((colors[0] >> 8) & 0xff) - (int)((colors[1] >> 8) & 0xff);
    int d2 = (int)(colors[0] >> 16 & 0xff) - (int)(colors[1] >> 16 & 0xff);
    int e0 = ((int)(colors[1] & 0xff) - (int)(pixel & 0xff)) * 3;
    int e1 = ((int)((colors[1] >> 8) & 0xff) - (int)((pixel >> 8) & 0xff)) * 3;
    int e2 = ((int)(colors[1] >> 16 & 0xff) - (int)(pixel >> 16 & 0xff)) * 3;
    uint32_t best = (uint32_t)(e0 * e0 + e1 * e1 + e2 * e2);
    uint32_t index = 1;
    e0 += d0;
    e1 += d1;
    e2 += d2;
    uint32_t err = (uint32_t)(e0 * e0 + e1 * e1 + e2 * e2);
    if ((int)err < (int)best) { index = 3; best = err; }
    e0 += d0;
    e1 += d1;
    e2 += d2;
    err = (uint32_t)(e0 * e0 + e1 * e1 + e2 * e2);
    if ((int)err < (int)best) { index = 2; best = err; }
    e0 += d0;
    e1 += d1;
    e2 += d2;
    err = (uint32_t)(e0 * e0 + e1 * e1 + e2 * e2);
    if ((int)err < (int)best) { index = 0; best = err; }
    *outIndex = index;
    return best / 9;
}

// ---------------------------------------------------------------------------
// @ 0x007ad400
// Like mappixel() but compares against the four candidates directly and includes
// the alpha channel in the error metric.
uint32_t mappixeltransparent(uint32_t pixel, uint32_t* outIndex, uint32_t* colors)
{
    uint32_t pa = (pixel >> 24) & 0xff, pr = (pixel >> 16) & 0xff;
    uint32_t pg = (pixel >> 8) & 0xff,  pb = pixel & 0xff;
    uint32_t best = 0x7fffffff;
    uint32_t index = 0;
    for (int i = 0; i < 4; i++)
    {
        uint32_t c = colors[i];
        int da = (int)((c >> 24) & 0xff) - (int)pa;
        int dr = (int)((c >> 16) & 0xff) - (int)pr;
        int dg = (int)((c >> 8) & 0xff) - (int)pg;
        int db = (int)(c & 0xff) - (int)pb;
        uint32_t err = (uint32_t)(da * da + dr * dr + dg * dg + db * db);
        if ((int)err < (int)best) { best = err; index = (uint32_t)i; }
    }
    *outIndex = index;
    return best;
}

// ---------------------------------------------------------------------------
// @ 0x007ad610
// Minimum RGB squared error of `pixel` against the four candidates.
// Original LTCG ABI: the pixel in eax, the candidates on the stack.
uint32_t trymappixel(uint32_t pixel, uint32_t* colors)
{
    uint32_t pr = (pixel >> 16) & 0xff, pg = (pixel >> 8) & 0xff, pb = pixel & 0xff;
    uint32_t best = 0xffffffff;
    for (int i = 0; i < 4; i++)
    {
        uint32_t c = colors[i];
        int dr = (int)((c >> 16) & 0xff) - (int)pr;
        int dg = (int)((c >> 8) & 0xff) - (int)pg;
        int db = (int)(c & 0xff) - (int)pb;
        uint32_t err = (uint32_t)(dr * dr + dg * dg + db * db);
        if ((int)err < (int)best) best = err;
    }
    return best;
}

// ---------------------------------------------------------------------------
// @ 0x007ad760
// Minimum red/blue squared error of `pixel` against the four candidates.
// Original LTCG ABI: the pixel in edx, the candidates in esi.
uint32_t rbmappixel(uint32_t pixel, uint32_t* colors)
{
    uint32_t pr = pixel & 0xff, pb = (pixel >> 16) & 0xff;
    uint32_t best = 0x7fffffff;
    for (int i = 0; i < 4; i++)
    {
        uint32_t c = colors[i];
        int dr = (int)(c & 0xff) - (int)pr;
        int db = (int)((c >> 16) & 0xff) - (int)pb;
        uint32_t err = (uint32_t)(dr * dr + db * db);
        if ((int)err < (int)best) best = err;
    }
    return best;
}

// @ 0x007ad810
// Original: LTCG custom register ABI (c0 in eax, c1 in ecx, three stack args; trymappixel takes the pixel in eax).
// Written here with an all-stack cdecl signature, so the bytes cannot match; behaviour is the same.
struct BlockCache {
    int      mCount;          // +0
    uint32_t mEntries[256];   // +4
};
uint32_t mappixel(uint32_t* colors, uint32_t pixel, uint32_t* outIndex);            // 0x007ad2e0
uint32_t mappixeltransparent(uint32_t pixel, uint32_t* outIndex, uint32_t* colors); // 0x007ad400
uint32_t trymappixel(uint32_t pixel, uint32_t* colors);                             // 0x007ad610
uint32_t rbmappixel(uint32_t pixel, uint32_t* colors);                              // 0x007ad760

static __forceinline uint32_t Expand565(uint32_t c)
{
    uint8_t r5 = (uint8_t)((c >> 11) << 3);
    uint32_t r = (c >> 13 & 7) | r5 | 0xffffff00u;
    uint8_t g6 = (uint8_t)((c >> 5) << 2);
    uint32_t rg = (r << 8) | (c >> 9 & 3) | g6;
    uint8_t b5 = (uint8_t)(c << 3);
    return (rg << 8) | (c >> 2 & 7) | b5;
}

extern "C" uint32_t trymapblock(uint32_t c0, uint32_t c1, BlockCache* cache, uint32_t* pixels, uint32_t threshold)
{
    uint32_t key = c1 << 16 | c0;
    int n = cache->mCount;
    int i = 0;
    if (0 < n) {
        do {
            if (cache->mEntries[i] == key)
                return 0x7fffffff;
            i++;
        } while (i < cache->mCount);
        n = cache->mCount;
    }
    if (n < 0x100) {
        cache->mEntries[n] = key;
        cache->mCount++;
    }
    __declspec(align(8)) uint32_t colors[2];
    colors[0] = Expand565(c1);
    colors[1] = Expand565(c0);
    uint32_t err = 0;
    int a = 0;
    do {
        int b = 0;
        do {
            err += trymappixel(*pixels, colors);
            if (threshold < err)
                return err;
            b++;
            pixels++;
        } while (b < 4);
        a++;
    } while (a < 4);
    return err;
}

// @ 0x007ad950
// MMX fast path of trymapblock: the two 565 endpoint colours are expanded to 888,
// packed four times into 16-bit lanes, and 8 pixels at a time are compared against
// every candidate with pmaddwd; the accumulated squared error is compared with the
// threshold after each group. `cand2`/`cand3` are the two interpolants produced by
// trymapblock's caller (2*c0+c1)/3 and (c0+2*c1)/3.
// Original ABI: c0 in eax, c1 in ecx, four stack arguments.
extern "C" uint32_t trymapblockfast(uint32_t c0, uint32_t c1, uint32_t cand2, uint32_t cand3,
                                    uint32_t* pixels, uint32_t threshold)
{
    __m64 end0 = _mm_cvtsi32_si64((int)Expand565(c0));
    __m64 end1 = _mm_cvtsi32_si64((int)Expand565(c1));
    __m64 weight = _mm_set1_pi16((short)0x5555);
    __m64 zero = _mm_setzero_si64();
    __m64 c2 = _mm_set1_pi16((short)cand2);
    __m64 c3 = _mm_set1_pi16((short)cand3);
    __m64 e02 = _mm_setzero_si64();
    (void)e02;
    __m64 lo0 = _mm_unpacklo_pi8(end0, zero);
    __m64 lo1 = _mm_unpacklo_pi8(end1, zero);
    __m64 m2 = _mm_mulhi_pi16(_mm_add_pi16(_mm_add_pi16(_mm_shuffle_pi16(lo0, 0xe4), lo0), lo1), weight);
    __m64 m3 = _mm_mulhi_pi16(_mm_add_pi16(_mm_add_pi16(_mm_shuffle_pi16(lo1, 0xe4), lo0), lo1), weight);
    uint32_t total = 0;
    int offset = 0x3c;
    for (;;)
    {
        __m64 src = _mm_unpacklo_pi8(_mm_cvtsi32_si64((int)(pixels[offset / 4] & 0xffffff)), zero);
        __m64 v2 = _mm_set1_pi16(_mm_extract_pi16(src, 0));
        __m64 a = _mm_madd_pi16(_mm_sub_pi16(src, lo0), _mm_sub_pi16(src, lo0));
        __m64 b = _mm_madd_pi16(_mm_sub_pi16(v2, lo1), _mm_sub_pi16(v2, lo1));
        __m64 c = _mm_madd_pi16(_mm_sub_pi16(v2, m2), _mm_sub_pi16(v2, m2));
        __m64 d = _mm_madd_pi16(_mm_sub_pi16(v2, m3), _mm_sub_pi16(v2, m3));
        uint32_t ea = (uint32_t)_mm_cvtsi64_si32(a) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(a, a));
        uint32_t eb = (uint32_t)_mm_cvtsi64_si32(b) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(b, b));
        uint32_t ec = (uint32_t)_mm_cvtsi64_si32(c) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(c, c));
        uint32_t ed = (uint32_t)_mm_cvtsi64_si32(d) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d, d));
        uint32_t best = ea < eb ? ea : eb;
        if (ec < best) best = ec;
        if (ed < best) best = ed;
        total += best;
        _mm_empty();
        if ((int)total >= (int)threshold)
            break;
        offset -= 8;
        if (offset < 0)
            break;
    }
    return total;
}
