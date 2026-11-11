// Slice s008930c0 -- EA::Text::PolygonFont destructor (retail EAText layout).
// Sets the PolygonFont vtable, calls Clear(), destroys its three containers in reverse
// declaration order (kerning rbtree at +0x174, a hash table at +0x150, the glyph-metrics
// hash table at +0x12c) and tail-calls the Font base destructor.
// Flags: /O2 /MD /Gy /TP
#include "types.h"

struct ICoreAllocator {
    virtual void  a0();
    virtual void  a1();
    virtual void* Allocate(unsigned size, int flags, const char* name);
    virtual void  Deallocate(void* p, unsigned size);        // vtable +0x0c
};

// eastl::hashtable<GlyphId, GlyphMetrics, ..., CoreAllocatorAdapter> (retail layout).
struct GlyphMetricsMap {
    unsigned        mFunctors;        // +0x00
    void**          mpBucketArray;    // +0x04
    unsigned        mnBucketCount;    // +0x08
    unsigned        mnElementCount;   // +0x0c
    char            mRehash[0x0c];    // +0x10
    ICoreAllocator* mpAllocator;      // +0x1c
    char            mRest[4];         // +0x20

    void DoFreeNodes(void** pBucketArray, unsigned n);       // 0x00885e20
    ~GlyphMetricsMap()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            mpAllocator->Deallocate(mpBucketArray, mnBucketCount * 4 + 4);
    }
};

// The generic hash container at +0x150 (HashBase::DoFreeNodes).
struct TextureInfoMap {
    unsigned        mFunctors;        // +0x00
    void**          mpBucketArray;    // +0x04
    unsigned        mnBucketCount;    // +0x08
    unsigned        mnElementCount;   // +0x0c
    char            mRehash[0x0c];    // +0x10
    ICoreAllocator* mpAllocator;      // +0x1c
    char            mRest[4];         // +0x20

    void DoFreeNodes(void** pBucketArray, unsigned n);       // 0x008de7f0
    ~TextureInfoMap()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            mpAllocator->Deallocate(mpBucketArray, mnBucketCount * 4 + 4);
    }
};

// eastl::rbtree<wchar_t, pair<const wchar_t, uint16>, ...> (root node at +0x0c).
struct KerningMap {
    char  pad0[0x0c];
    void* mpNode;                                        // +0x0c

    void DoNukeSubtree(void* node);                      // 0x00885f60
    ~KerningMap() { DoNukeSubtree(mpNode); }
};

struct Font {
    virtual ~Font();                                     // 0x0088b560
    virtual void f1();
    virtual void f2();
};

struct PolygonFont : Font {
    char            pad1[0x128];                         // +0x004
    GlyphMetricsMap mGlyphMetricsMap;                    // +0x12c
    TextureInfoMap  mTextureInfoMap;                     // +0x150
    KerningMap      mKerningMap;                         // +0x174

    void Clear();                                        // 0x00892ac0
    virtual ~PolygonFont();
};

// @ 0x008930c0
PolygonFont::~PolygonFont()
{
    Clear();
}
