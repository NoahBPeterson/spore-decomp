// Slice s0088aef0 -- 0x0088aef0: GlyphCache::GetGlyphTextureInfo (EA::Text::GlyphCache, EATextCache.obj).
//
// Looks the glyph up in the cache's hashtable (under the cache critical section) and, when the
// glyph is cached, copies its 20-byte GlyphTextureInfo record out to the caller.
//
// The hashtable sub-object sits at this+0xc (buckets +0x10, bucket count +0x14) and the cache's
// CRITICAL_SECTION at this+0x168.
//
// Local stand-in layout (retail offsets).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);

// The glyph the cache is keyed by.  Retail takes it BY VALUE: the callee copies the 6 live bytes
// (a dword and a word) into the two stack slots the hashtable's find reads.
#pragma pack(push, 2)
struct GlyphInfoKey {
    int            mValue;       // +0x00 (the flags word)
    unsigned short mChar;        // +0x04
};
#pragma pack(pop)

// The cached texture record (0x14 bytes: four rect ints and the texture object).
struct GlyphTextureInfo {
    int    mX0;                  // +0x00
    int    mY0;                  // +0x04
    int    mX1;                  // +0x08
    int    mY1;                  // +0x0c
    void*  mpTexture;            // +0x10
};

// eastl hashtable node: the key/value pair first, then the bucket-chain link.
struct GlyphNode {
    GlyphInfoKey     mKey;       // +0x00
    GlyphTextureInfo mValue;     // +0x08
    GlyphNode*       mpNext;     // +0x1c
};

// {node, bucket slot}: the iterator eastl's hashtable::find returns through a hidden slot.
struct HashIter {
    GlyphNode*  mpNode;          // +0x00
    GlyphNode** mpSlot;          // +0x04
};

// eastl hashtable sub-object.
struct HashTable {
    char        pad0[4];         // +0x00
    GlyphNode** mpBuckets;       // +0x04
    int         mnBuckets;       // +0x08

    HashIter find(const GlyphInfoKey& key) const;   // 0x0088ac90
};

struct GlyphCache {
    char pad00[0x0c];
    HashTable mTable;            // +0x0c
    char pad18[0x168 - 0x18];
    unsigned int mCS[6];         // +0x168 (CRITICAL_SECTION, 0x18 bytes)

    bool GetGlyphTextureInfo(GlyphInfoKey key, GlyphTextureInfo* out);
};

// @ 0x0088aef0
bool GlyphCache::GetGlyphTextureInfo(GlyphInfoKey key, GlyphTextureInfo* out)
{
    void* cs = mCS;
    EnterCriticalSection(cs);

    GlyphInfoKey k = key;
    HashTable* table = &mTable;
    HashIter it = table->find(k);
    GlyphNode* node = it.mpNode;
    if (node != table->mpBuckets[table->mnBuckets]) {
        *out = node->mValue;
        LeaveCriticalSection(cs);
        return true;
    }
    LeaveCriticalSection(cs);
    return false;
}
