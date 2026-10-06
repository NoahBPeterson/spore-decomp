// Slice s00885ad0 (0x885ad0..0x886b4f) - EA::Text (EAText) font/glyph-cache code.
//
// The bulk of this slice is the original EAWebKit 1.21.00 EAText/EASTL source, which this
// build reproduces byte-for-byte for the functions listed in manifest.txt. Those sources are
// vendored (read-only) under work/ext/EAWebKitSupportPackages and #included below; the compiler
// instantiates the same EASTL containers (rbtree/hashtable/basic_string) and emits the exact
// same code. This is the real upstream implementation, not a transcription.
//
// The remaining VAs in this slice are retail-only variants whose build configuration
// (allocator/layout) differs from the vendored EAWebKit drop; they are represented by the
// upstream sources too, but their bytes differ. See partial.txt for the per-VA accounting.
//
// Byte-exact VAs (upstream):  00885ad0 00885b00 00885b70 00885bd0 00885c20 00885d30
//   00885dd0 00885e20 00885e70 00885f20 00885f60 00886190 008862a0 00886330 00886430
//   00886490 00886560 008865b0 00886690
// Retail-variant VAs (upstream source, non-identical bytes): 00885cb0 00885ce0 00885d60
//   00885fa0 00886000 00886100 00886200 008863a0 00886780 008867e0 00886850 008868b0
//   00886ad0

#include "types.h"

// Build configuration of the vendored EAWebKit drop (equivalent to the /D... flags that
// build_eatext.py passes). Kept in-source so the manifest flags stay short enough for
// run_all.py's object-file naming.
#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

// Retail layout fixups: the retail Font base class is 0x28 bytes larger than the vendored
// EAWebKit one, and retail BmpFont carries an extra hash_map<GlyphId, GlyphMetrics>.
// They are injected into the class bodies by macros that are active only while the
// declaring header is read.
#include <EABase/EABase.h>
#include <EAText/EAText.h>
#include <EAText/EATextStyle.h>
#include <EAText/EATextScript.h>
#include <EASTL/utility.h>
#include <EASTL/hash_map.h>
#include <EASTL/bitset.h>
#include <EASTL/core_allocator_adapter.h>
#include <coreallocator/icoreallocator_interface.h>
#include <EAIO/EAStream.h>
#define mRefCount mRefCount; unsigned mRetailFontExtra[10]
#include <EAText/EATextFont.h>
#undef mRefCount
#define mRefCount mRefCount; unsigned mRetailTexInfoExtra[36]
#include <EAText/EATextCache.h>
#undef mRefCount
#include <EASTL/map.h>
#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/fixed_string.h>
#include <EAIO/EAStreamAdapter.h>
#define mGlyphBitmap mGlyphBitmap; eastl::hash_map<GlyphId, GlyphMetrics, eastl::hash<uint32_t>, eastl::equal_to<GlyphId>, EA::Allocator::EASTLICoreAllocator> mGlyphMetricsMap
#include <EAText/EATextBmpFont.h>
#undef mGlyphBitmap

#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EAText.cpp"
#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextBmpFont.cpp"
#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextPolygonFont.cpp"
#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextOutlineFont.cpp"

// ---------------------------------------------------------------------------
// Retail-only variants not byte-identical to the EAWebKit drop. Kept as
// compile-complete placeholders that mirror the upstream entry points' names;
// they are recorded in partial.txt and are NOT claimed byte-exact.
// ---------------------------------------------------------------------------

// @ 0x00885fa0
void FUN_00885fa0() {}

// @ 0x00886200
void FUN_00886200() {}

// @ 0x00886780
void FUN_00886780() {}


// ---------------------------------------------------------------------------
// Retail-layout BmpFont members. The retail Font base and BmpFont differ from the vendored
// EAWebKit drop (extra Font members, an extra GlyphMetrics hash_map at +0x128 that
// GetGlyphMetrics reads), so these are written against retail offsets, using the vendored
// container/value types.
// ---------------------------------------------------------------------------
namespace RT {
using namespace EA::Text;

typedef eastl::hash_map<GlyphId, GlyphMetrics, eastl::hash<uint32_t>, eastl::equal_to<GlyphId>,
                        EA::Allocator::EASTLICoreAllocator> GMap;
struct RBmpGM { int mnTextureIndex : 8; int mnPositionX : 12; int mnPositionY : 12; };   // retail: bitfield word only
typedef eastl::hash_map<GlyphId, RBmpGM, eastl::hash<uint32_t>, eastl::equal_to<GlyphId>,
                        EA::Allocator::EASTLICoreAllocator> BMap;
typedef eastl::pair<GlyphId, GlyphId> GPair;
typedef eastl::map<GPair, Kerning, eastl::less<GPair>, EA::Allocator::EASTLICoreAllocator> KMap;
typedef eastl::map<Char, GlyphId, eastl::less<Char>, EA::Allocator::EASTLICoreAllocator> CMap;
typedef Font::GlyphBitmap GBitmap;

struct RTexInfo {                                         // retail TextureInfo, 0x1a0 bytes
    virtual ~RTexInfo();
    virtual int AddRef();
    virtual int Release();
    uint32_t    pad04;
    uint8_t     mLockInformation[40];                     // +0x08
    const char16_t* mpSource;                             // +0x30
    uint32_t    pad34[4];
    uint32_t    mFormat;                                  // +0x44
    uint32_t    mnSize;                                   // +0x48
    uint8_t     pad4c[0x19f - 0x4c];
    bool        mbWritable;                               // +0x19f
    RTexInfo();                                           // 0x889f10
};

struct RBmpTexInfo : RTexInfo {                           // 0x2d8 bytes
    PathString16 mTextureFilePath;                        // +0x1a0
    uint32_t     mnTextureFileSize;                       // +0x2b8
    PixelData    mPixelData;                              // +0x2bc
    RBmpTexInfo();
};

struct RBmpFont {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual bool GetGlyphMetricsV(GlyphId g, GlyphMetrics& m);       // vtable +0x34

    void FontSetAllocator(void* a);                                  // 0xfcc140 (Font::SetAllocator)
    void __thiscall SetAllocator(void* a);
    bool __thiscall GetGlyphMetrics(GlyphId g, GlyphMetrics& m);
    bool __thiscall GetKerning(GlyphId g1, GlyphId g2, Kerning& k, int direction, bool h);
    bool __thiscall IsCharSupported(Char c, unsigned script);
    int __thiscall GetGlyphIds(const Char* chars, uint32_t n, GlyphId* out, bool useRepl, int stride);
    bool __thiscall RenderGlyphBitmap(const GBitmap** pp, GlyphId g, uint32_t flags, float fx, float fy);
};

#define RF(T, off) (*(T*)((char*)this + (off)))
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);

// @ 0x00885d60
void __thiscall RBmpFont::SetAllocator(void* a)
{
    FontSetAllocator(a);
    RF(void*, 0x144) = a;
    RF(void*, 0x168) = a;
    RF(void*, 0x188) = a;
    RF(void*, 0x1d0) = a;
}

// @ 0x00886850
bool RBmpFont::GetGlyphMetrics(GlyphId g, GlyphMetrics& m)
{
    GMap& map = RF(GMap, 0x128);
    GMap::const_iterator it = map.find(g);
    if (it != map.end()) {
        m = (*it).second;
        return true;
    }
    return false;
}

// @ 0x008863a0
bool RBmpFont::GetKerning(GlyphId g1, GlyphId g2, Kerning& kerning, int direction, bool)
{
    bool r = false;
    if (direction % 2)
        eastl::swap(g1, g2);
    const GPair pair(g1, g2);
    const KMap::const_iterator it = RF(KMap, 0x170).find(pair);
    if (it != RF(KMap, 0x170).end()) {
        r = true;
        kerning = (*it).second;
    }
    if (!r) {
        kerning.mfKernX = 0.f;
        kerning.mfKernY = 0.f;
    }
    return r;
}

// @ 0x00886100
bool RBmpFont::IsCharSupported(Char c, unsigned script)
{
    if (c < 0x0080)
        return true;
    if (script < 0x1f) {
        if (script != 0x1e && script != 0 && script != 0x15)
            goto bits;
    } else {
        if (script != (unsigned)-1)
            goto bits;
        if (c == 0xffff)
            return true;
    }
    {
        CMap& cm = RF(CMap, 0x1b8);
        return cm.find(c) != cm.end();
    }
bits:
    return RF(eastl::bitset<64>, 0x18).test(script);
}

struct RCharNode { RCharNode* mpRight; RCharNode* mpLeft; RCharNode* mpParent; int color; uint16_t key; GlyphId glyph; };

// @ 0x00886000
int RBmpFont::GetGlyphIds(const Char* pCharArray, uint32_t nCharArrayCount, GlyphId* pGlyphIdArray,
                          bool bUseReplacementGlyph, int nGlyphIdStride)
{
    const Char* pChar    = pCharArray;
    const Char* pCharEnd = pCharArray + nCharArrayCount;
    GlyphId*    pGlyphId = pGlyphIdArray;
    while (pChar < pCharEnd) {
        RCharNode* pEnd = &RF(RCharNode, 0x1bc);
        RCharNode* pCurrent = RF(RCharNode*, 0x1c4);
        RCharNode* pRangeEnd = pEnd;
        while (pCurrent) {
            if (!(pCurrent->key < *pChar)) {
                pRangeEnd = pCurrent;
                pCurrent = pCurrent->mpLeft;
            } else
                pCurrent = pCurrent->mpRight;
        }
        if (pRangeEnd == pEnd || *pChar < pRangeEnd->key)
            pRangeEnd = pEnd;
        if (pRangeEnd != &RF(RCharNode, 0x1bc))
            *pGlyphId = pRangeEnd->glyph;
        else if (IsCharZeroWidth(*pChar))
            *pGlyphId = kGlyphIdZeroWidth;
        else if (bUseReplacementGlyph)
            *pGlyphId = RF(GlyphId, 0x14);
        pGlyphId = (GlyphId*)((char*)pGlyphId + nGlyphIdStride);
        pChar++;
    }
    return pGlyphId - pGlyphIdArray;
}

// @ 0x008868b0
bool RBmpFont::RenderGlyphBitmap(const GBitmap** pGlyphBitmap, GlyphId glyphId, uint32_t, float, float)
{
    void* cs = (char*)this + 0x28;
    EnterCriticalSection(cs);
    BMap& bm = RF(BMap, 0x14c);
    BMap::const_iterator it = bm.find(glyphId);
    if (it != bm.end()) {
        const RBmpGM& bgm = (*it).second;
        RBmpTexInfo* tex = RF(RBmpTexInfo**, 0x190)[bgm.mnTextureIndex];
#define gb RF(GBitmap, 0x100)
        GetGlyphMetricsV(glyphId, gb.mGlyphMetrics);
        gb.mnWidth       = (uint32_t)gb.mGlyphMetrics.mfSizeX;
        gb.mnHeight      = (uint32_t)gb.mGlyphMetrics.mfSizeY;
        gb.mnStride      = tex->mnSize * sizeof(uint32_t);
        gb.mBitmapFormat = (Font::BitmapFormat)0x20;
        gb.mpData        = (uint32_t*)tex->mPixelData.data()
                         + ((bgm.mnPositionY - (int)gb.mGlyphMetrics.mfHBearingY) * tex->mnSize)
                         + (bgm.mnPositionX + (int)gb.mGlyphMetrics.mfHBearingX);
        *pGlyphBitmap = &gb;
#undef gb
        LeaveCriticalSection(cs);
        return true;
    }
    LeaveCriticalSection(cs);
    return false;
}

// @ 0x00886ad0
RBmpTexInfo::RBmpTexInfo()
  : mTextureFilePath(),
    mnTextureFileSize(0),
    mPixelData(EA::Allocator::EASTLICoreAllocator(EASTL_NAME(EATEXT_ALLOC_PREFIX "BmpFont/BmpTextureInfo")))
{
    mpSource   = mTextureFilePath.c_str();
    mbWritable = false;
}

} // namespace RT
