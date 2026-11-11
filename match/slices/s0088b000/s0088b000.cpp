// Slice s0088b000 -- EA::Text::RT::GlyphCache::Shutdown: the last reference releases the
// glyph-texture hash table's nodes and empties the texture-info array in place.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE
#include "types.h"

void operator delete[](void* p);
void* memmove(void* dst, const void* src, unsigned n);

extern "C" long __cdecl _InterlockedDecrement(long volatile* p);
#pragma intrinsic(_InterlockedDecrement)

namespace RT {

class TextureInfo {                        // node stored by pointer in the texture-info array
 public:
    virtual ~TextureInfo();
    virtual int AddRef();                  // slot 1
    virtual int Release();                 // slot 2
};

class ICoreAllocator {
 public:
    virtual ~ICoreAllocator();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags) = 0;
    virtual void* Alloc(unsigned size, const char* name, unsigned flags, unsigned align, unsigned offset) = 0;
    virtual void  Free(void* p, unsigned size) = 0;
};

// eastl::hashtable<..., CoreAllocatorAdapter> (GlyphCache::mGlyphTextureMap, +0x0c).
class GlyphTextureMap {
 public:
    void DoFreeNodes(void** pBucketArray, unsigned n);   // 0x008dac90

    unsigned        mFunctors;        // +0x00
    void**          mpBucketArray;    // +0x04
    unsigned        mnBucketCount;    // +0x08
    unsigned        mnElementCount;   // +0x0c
    float           mfMaxLoadFactor;  // +0x10
    float           mfGrowthFactor;   // +0x14
    unsigned        mnNextResize;     // +0x18
    ICoreAllocator* mpCoreAllocator;  // +0x1c
    unsigned        mAllocFlags;      // +0x20
};

// eastl::fixed_vector<TextureInfo*, 4, true> (GlyphCache::mTextureInfoArray, +0x30).
class TextureInfoArray {
 public:
    TextureInfo** mpBegin;        // +0x00
    TextureInfo** mpEnd;          // +0x04
    TextureInfo** mpCapacity;     // +0x08
    unsigned      mAllocatorName; // +0x0c
    TextureInfo** mpPoolBegin;    // +0x10
    TextureInfo*  mBuffer[3];     // +0x14
};

class GlyphCache {
 public:
    virtual ~GlyphCache();                                    // slot 0
    virtual void v01() = 0; virtual void v02() = 0; virtual void v03() = 0;
    virtual void v04() = 0; virtual void v05() = 0; virtual void v06() = 0;
    virtual void v07() = 0; virtual void v08() = 0;
    virtual bool ClearTextureInternal(TextureInfo* pTextureInfo) = 0; // slot 9 (+0x24)

    int Shutdown();                                           // 0x0088b000

    unsigned            mPad04[2];                // +0x04
    GlyphTextureMap     mGlyphTextureMap;         // +0x0c
    TextureInfoArray    mTextureInfoArray;        // +0x30
    unsigned            mnTextureInfoCountMax;    // +0x50
    unsigned            mnTextureSizeDefault;     // +0x54
    unsigned            mnTextureFormatDefault;   // +0x58
    unsigned            mnColumnCountDefault;     // +0x5c
    unsigned            mnColumnWidthsDefault[66];// +0x60
    unsigned char       mMutex[24];               // +0x168 (CRITICAL_SECTION)
    unsigned            mPad180[2];               // +0x180
    volatile long       mnInitCount;              // +0x188
};

// @ 0x0088b000
int GlyphCache::Shutdown()
{
    const long refCount = _InterlockedDecrement(&mnInitCount);
    if (refCount == 0)
    {
        GlyphTextureMap* const pMap = &mGlyphTextureMap;
        pMap->DoFreeNodes(pMap->mpBucketArray, pMap->mnBucketCount);
        pMap->mnElementCount = 0;

        // Destroy every texture info in place, then restore the buffer with a self-copy.
        for (unsigned i = 0; i < (unsigned)(mTextureInfoArray.mpEnd - mTextureInfoArray.mpBegin); ++i)
        {
            TextureInfo* pTextureInfo = mTextureInfoArray.mpBegin[i];
            ClearTextureInternal(pTextureInfo);
            pTextureInfo->Release();
        }
        mTextureInfoArray.mpEnd -= (unsigned)(mTextureInfoArray.mpEnd - mTextureInfoArray.mpBegin);
        memmove((void*)mTextureInfoArray.mpBegin, (const void*)mTextureInfoArray.mpBegin, 0);
    }
    return refCount;
}

}  // namespace RT
