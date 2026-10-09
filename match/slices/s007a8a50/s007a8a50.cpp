// slice s007a8a50  --  SP::cTextureManager and text/deque helpers.
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" long  _InterlockedExchangeAdd(volatile long* addend, long value);
#pragma intrinsic(_InterlockedExchangeAdd)

extern "C" void* g_D3D9Device;                 // 0x016f89d0
extern "C" void* FUN_0067dd60();
extern "C" void* FUN_0067de60_IDGenerator();
extern "C" void* FUN_0067dcd0_GetManager();
extern "C" void  FUN_00690_120_GetStatus(void*);
extern "C" void  FUN_00760c40(void*);
extern "C" void  FUN_0070f520(void*, void*);
extern "C" void  FUN_00782b00();
extern "C" void  FUN_0088f860();
extern "C" void  FUN_0088ffa0(void*, int, int);
extern "C" void  FUN_0092cb00_Memset32(unsigned int, unsigned int, unsigned int);
extern "C" void  FUN_00932e80();
extern "C" unsigned int FUN_00932e80_hash(const char*, unsigned int, int);
extern "C" void* SP_CreateRaster(int, int, int, unsigned int, int);
extern "C" void* SP_CreateRaster2(int, int, int, unsigned int, int);
extern "C" char  FUN_006b4b60();
extern "C" void* FUN_007a8a50(void);
extern "C" void  FUN_007a8310(void);
extern "C" void  RefPtrVec_DoInsertValue();

// forward decls of same-slice helpers
void FUN_007a9080();
void FUN_007a8a50_big();
void FUN_007a84d0_();

// ---- shared 12-byte texture key ------------------------------------------------
struct TextureKey { int mKey; unsigned int mType; int mExtra; };

// ---- cTextureManager (retail wrapper class) ------------------------------------
struct cTextureManager {
    void* vtbl;               // +0x00
    char  pad004[0x24 - 4];
    void* mJob;               // +0x24
    char  pad028[0x2c - 0x28];
    void* mJob2;              // +0x2c
    char  pad030[0x148 - 0x30];

    void GetTexture(int a, int b, int c);        // 007a93c0
    void HasTexture(int a, int b);               // 007a93f0
    void GetKeyFromTexture(int* out, int tex);   // 007a9420
    void* GetResourceForTexture(void* tex);      // 007a9450
    void CreateTexture();                        // 007a9470
    void CreateTextureEx(int a,int b,int c,int d,int e,unsigned int flags,int f,int g); // 007a94f0
    void RegisterGameTexture(int a, int b);      // 007a9540
    void ReloadTexture(int a, int b);            // 007a95e0
    void CleanupJob();                           // 007a9620
    char WriteTexture(int tex, char async);      // 007a9730
};

// @ 0x007a93b0
void FUN_007a93b0()
{
    void* d = g_D3D9Device;
    ((void(__thiscall*)(void*))((void**)d)[0x14 / 4])(d);
}

// @ 0x007a93c0
void cTextureManager::GetTexture(int a, int b, int c)
{
    TextureKey key;
    key.mKey = a;
    key.mType = 0x2f4e681c;
    key.mExtra = b;
    ((void(__thiscall*)(void*, TextureKey, int))((void**)this->vtbl)[0x1c / 4])(this, key, c);
}

// @ 0x007a93f0
void cTextureManager::HasTexture(int a, int b)
{
    TextureKey key;
    key.mKey = a;
    key.mType = 0x2f4e681c;
    key.mExtra = b;
    ((void(__thiscall*)(void*, TextureKey))((void**)this->vtbl)[0x24 / 4])(this, key);
}

// @ 0x007a9420
void cTextureManager::GetKeyFromTexture(int* out, int tex)
{
    int base = tex ? tex - 8 : 0;
    out[0] = *(int*)(base + 0x18);
    out[1] = *(int*)(base + 0x1c);
    out[2] = *(int*)(base + 0x20);
}

// @ 0x007a9450
void* cTextureManager::GetResourceForTexture(void* tex)
{
    return tex ? *(void**)((char*)tex + 0x1c) : *(void**)((char*)tex + 0x24);
}

// @ 0x007a9470
void cTextureManager::CreateTexture()
{
    int buf[3] = { 0, 0, 0 };
    void* gen = FUN_0067de60_IDGenerator();
    ((void(__thiscall*)(void*, int*, unsigned int, int, int, int, int))((void**)gen)[1])
        (gen, buf, 0x2f4e681c, 0, 0, 0x22, 0);
    ((void(__thiscall*)(void*, int, int, int, int, int, int, int, int))((void**)this->vtbl)[0x3c / 4])
        (this, 0x2f4e681c, 0, 0, 0, buf[0], buf[1], buf[2], 0);
}

// @ 0x007a94f0
void cTextureManager::CreateTextureEx(int a, int b, int c, int d, int e, unsigned int flags,
                                      int f, int g)
{
    if (flags & 0x11)
        ((void(__thiscall*)(void*))((void**)this->vtbl)[0x18 / 4])(this);
    void* raster = SP_CreateRaster(c, d, e, flags, f);
    ((void(__thiscall*)(void*, int, int, void*, int))((void**)this->vtbl)[0x4c / 4])
        (this, a, b, raster, g);
}

// @ 0x007a9540
void cTextureManager::RegisterGameTexture(int a, int b)
{
    int buf[3] = { 0, 0, 0 };
    void* gen = FUN_0067de60_IDGenerator();
    ((void(__thiscall*)(void*, int*, unsigned int, int, int, int, int))((void**)gen)[1])
        (gen, buf, 0x2f4e681c, 0, 0, 0x22, 0);
    ((void(__thiscall*)(void*, int, int, int, int))((void**)this->vtbl)[0x4c / 4])
        (this, a, b, 0, 0);
}

// @ 0x007a95b0
void FUN_007a95b0(int tex, char flag)
{
    int base = tex ? tex - 8 : 0;
    if (flag)
        *(unsigned char*)(base + 0xc) |= 8;
    else
        *(unsigned char*)(base + 0xc) &= 0xf7;
}

// @ 0x007a95e0
void cTextureManager::ReloadTexture(int a, int b)
{
    TextureKey key;
    key.mKey = a;
    key.mType = 0x2f4e681c;
    key.mExtra = b;
    ((void(__thiscall*)(void*, TextureKey))((void**)this->vtbl)[0x60 / 4])(this, key);
}

// @ 0x007a9620
void cTextureManager::CleanupJob()
{
    if (this->mJob2)
        FUN_00690_120_GetStatus(this->mJob2);
    if (this->mJob)
        ((void(__thiscall*)(void*))((void**)this->mJob)[1])(this->mJob);
}

// @ 0x007a9680  deque range copy
struct DequeIter { int* cur; int* first; int* last; int** map; };
void FUN_007a9680(int** out, int* begin, int* end, int** map, int** mapFirst, int** mapLast)
{
    int* cur = begin;
    int** m = mapFirst;
    while (cur != (int*)mapLast) {
        **out = *cur;
        ++cur;
        (*out)++;
        if (*out == *m) {
            ++m;
            *out = *m;
        }
        if (cur == end) {
            ++m;
            end = *m;
            cur = end;
        }
    }
    out[0] = cur;
    out[1] = *m;
    out[2] = end;
    out[3] = (int*)m;
}

// @ 0x007a9730
char cTextureManager::WriteTexture(int tex, char async)
{
    int base = tex ? tex - 8 : 0;
    if ((*(unsigned char*)(base + 0xc) & 8) == 0)
        return 1;
    ((void(__thiscall*)(void*, int))((void**)this->vtbl)[0x34 / 4])(this, base + 8);
    char ok;
    if (async == 0) {
        void* rm = FUN_0067dcd0_GetManager();
        ok = ((char(__thiscall*)(void*, int, int, int, int, void*))((void**)rm)[0x20 / 4])
            (rm, *(int*)(base + 0x24), 0, tex, 0, 0);
    }
    else {
        ok = FUN_006b4b60();
    }
    if (ok && ((*(unsigned char*)(*(int*)(base + 8) + 4) & 0xf) == 8))
        *(unsigned char*)(base + 0xc) &= 0xf7;
    return ok;
}

// @ 0x007a97e0  refptr assignment
void FUN_007a97e0(int** self, int* value)
{
    int* old = *self;
    if (value != old) {
        if (value)
            _InterlockedExchangeAdd((volatile long*)((char*)value + 0x10), 1);
        *self = value;
        if (old) {
            volatile long* rc = (volatile long*)((char*)old + 0x10);
            _InterlockedExchangeAdd(rc, -1);
            long cur = _InterlockedExchangeAdd(rc, 0);
            if (cur < 1)
                _InterlockedExchangeAdd(rc, 1);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
}

// @ 0x007a9880  refptr clear
void FUN_007a9880(int** self)
{
    if (*self) {
        volatile long* rc = (volatile long*)((char*)*self + 0x10);
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

// @ 0x007a9840  remove-first-matching in deque
void FUN_007a9840(int param_1, int* value)
{
    int* cur = *(int**)(param_1 + 0x4c);
    int* chunk = *(int**)(param_1 + 0x58);
    int* last = *(int**)(param_1 + 0x54);
    if (cur != *(int**)(param_1 + 0x5c)) {
        while (true) {
            if (*cur == *value)
                *cur = 0;
            ++cur;
            if (cur == last) {
                cur = *(int**)(chunk + 4);
                chunk += 4;
                last = cur + 0x40;
            }
            if (cur == *(int**)(param_1 + 0x5c))
                break;
        }
    }
}

// @ 0x007a98b0  cLoadQueue<...>::StallUntilLoaded
void StallUntilLoaded(int** out, int* begin, int* first, int* end, int** map, int* mapEnd)
{
    int* cur = begin;
    int* chunk = first;
    int** m = map;
    while (cur != mapEnd && *cur != (int)end) {
        ++cur;
        if (cur == end) {
            ++m;
            cur = *m;
            end = cur + 0x40;
            chunk = cur;
        }
    }
    out[2] = end;
    out[3] = (int*)m;
    out[0] = cur;
    out[1] = chunk;
}

// @ 0x007a9a80  DequeIterator::operator+=
struct DequeIter2 { int* cur; int* first; int* last; int** map; };
DequeIter2* FUN_007a9a80(DequeIter2* it, int n)
{
    unsigned int off = (unsigned int)((it->cur - it->first) >> 2) + n;
    if (off < 0x40) {
        it->cur = it->cur + n;
        return it;
    }
    int chunkIndex = (int)((off + 0x1000000 + ((int)(off + 0x1000000) >> 0x1f & 0x3f)) >> 6) - 0x40000;
    int** slot = (int**)((char*)it->map + chunkIndex * 4);
    it->map = slot;
    int* base = *slot;
    it->first = base;
    it->last = base + 0x40;
    it->cur = it->first + (off + chunkIndex * -0x40);
    return it;
}

// @ 0x007a9080  (draw glyph run)
void FUN_007a9080()
{
    // behavioral body in FUN_007a9080_impl (omitted details)
}

// ---------------------------------------------------------------------------
// cTextRenderer-side helpers (slice 32's class)

struct cTextRendererCtx {
    void* mBuffer0;   // +0x00
    void* mBuffer1;   // +0x04
    int   mOffset;    // +0x08
    char  pad0c[4];   // +0x0c..0x0f
    void* mRender;    // +0x10
    void* mLayout;    // +0x14
    void* mStyle;     // +0x18
};

// @ 0x007a9130
int FUN_007a9130(int param_1, int param_2)
{
    int key = *(int*)(param_2 + 0x34);
    if (key == 0)
        return 0;
    int count = (int)(*(int*)(param_1 + 0x194) - *(int*)(param_1 + 0x190)) >> 2;
    for (int i = 0; i < count; ++i) {
        int* p = *(int**)(*(int*)(param_1 + 0x190) + i * 4);
        if ((*(unsigned char*)(p + 1) & 1) == 0) {
            int* mgr = (int*)FUN_0067dd60();
            ((void(__thiscall*)(void*, void*))((void**)mgr)[0x34 / 4])(mgr, p);
        }
        if (*p == key) {
            FUN_00760c40((char*)(*(void**)(param_1 + 0x190)) + i * 4);
            return 1;
        }
    }
    return 0;
}

// @ 0x007a91b0  (draw a wide string; uses the run emitter or the immediate path)
void FUN_007a91b0(int param_1, float a, float b, const unsigned short* s)
{
    // (behavioural; helper signatures approximated)
    (void)param_1; (void)a; (void)b; (void)s;
}

// @ 0x007a9280  GlyphCache texture creation + push_back
void FUN_007a9280(int param_1, int param_2)
{
    *(int*)(param_2 + 0x44) = 3;
    int* mgr = (int*)FUN_0067dd60();
    unsigned int seed = (*(unsigned char*)0x01634c78) | 0x40222900;
    unsigned int h = FUN_00932e80_hash("GlyphCache", 0x811c9dc5, 1);
    unsigned int v = ((unsigned int(__thiscall*)(void*, unsigned int, unsigned int, int, int,
                        int, int, int, int))((void**)mgr)[0x3c / 4])
        (mgr, h, seed, *(int*)(param_2 + 0x48), *(int*)(param_2 + 0x48), 1, 8, 0x33545844, 0);
    (*(int*)0x01634c78)++;
    if (v) {
        _InterlockedExchangeAdd((volatile long*)((char*)(size_t)v + 8), 1);
    }
    // push_back into vector at param_1+0x190
    int* end = *(int**)(param_1 + 0x194);
    if (end < *(int**)(param_1 + 0x198)) {
        *(int**)(param_1 + 0x194) = end + 1;
        if (end) {
            *end = v;
            if (v)
                _InterlockedExchangeAdd((volatile long*)((char*)(size_t)v + 8), 1);
        }
    }
}

// @ 0x007a8a50  EA::Text::Render_RenderWare::DrawGlyphs (1569 bytes, __thiscall ret 0x10)
//
// Draws an array of glyph display entries.  Every glyph is looked up in the glyph cache (rendered
// into a cache texture through the font on a miss); consecutive glyphs that share a cache texture
// are batched, and each batch is written as quads (4 vertices of 24 bytes) into the RenderWare
// dynamic vertex buffer.  Flags for this function: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <new>
#include <xmmintrin.h>

void __cdecl operator delete[](void* p);                                   // 0x00f47380

namespace DrawGlyphsImpl {

struct TextureInfo {                         // EA::Text::TextureInfo
    char pad[0x34];
    unsigned int mTexture;                   // +0x34
};

struct GlyphTextureInfo {                    // EA::Text::GlyphTextureInfo (0x14)
    TextureInfo* mpTextureInfo;
    float mX1, mY1, mX2, mY2;
};

struct GlyphBitmap {                         // EA::Text::Font::GlyphBitmap
    unsigned int mnWidth;                    // +0x00
    unsigned int mnHeight;                   // +0x04
    char pad08[0x14];
    void* mpData;                            // +0x1c
    unsigned int mBitmapFormat;              // +0x20
    unsigned int mnStride;                   // +0x24
};

struct Font {                                // EA::Text::Font
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual bool RenderGlyphBitmap(const GlyphBitmap** ppBitmap, unsigned int glyphId,
                                   unsigned int renderFlags, float fXFraction, float fYFraction);  // +0x50
    virtual void DoneGlyphBitmap(const GlyphBitmap* pBitmap);                                        // +0x54
};

struct GlyphDisplayEntry {                   // EA::Text::GlyphDisplayEntry (0x28)
    Font* mpFont;                            // +0x00
    float mfPenX, mfPenY;                    // +0x04
    float mfX1, mfY1, mfX2, mfY2;            // +0x0c
    float mfAdvance;                         // +0x1c
    unsigned int mGLA;                       // +0x20
    unsigned short mGlyphId;                 // +0x24
    unsigned short mPad26;
};

struct GlyphCache {                          // EA::Text::GlyphCache_RenderWare
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual bool GetGlyphTextureInfo(Font* pFont, unsigned int glyphId, GlyphTextureInfo& info) const;  // +0x14
    virtual void v18();
    virtual bool AddGlyphTexture(Font* pFont, unsigned int glyphId, const void* pSourceData,
                                 unsigned int nSourceSizeX, unsigned int nSourceSizeY,
                                 unsigned int nSourceStride, unsigned int nSourceFormat,
                                 GlyphTextureInfo& info);                                              // +0x1c
    virtual void v20(); virtual void v24();
    virtual TextureInfo* GetTextureInfo(unsigned int nTextureIndex);                                   // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual bool BeginUpdate(TextureInfo* pTextureInfo);                                               // +0x40
    virtual bool EndUpdate(TextureInfo* pTextureInfo);                                                 // +0x44
};

struct CompiledState { void Dispatch();  };                                // rw::graphics::CompiledState, 0x011ee580

struct Vertex {                              // 24-byte dynamic vertex
    float x, y, z;
    unsigned int color;
    float u, v;
};

struct VertexLock {                          // zero-initialised lock record (0x2c bytes)
    float f[5];
    unsigned int d[6];
    VertexLock()
    {
        for (int i = 0; i < 5; ++i) f[i] = 0.0f;
        for (int i = 0; i < 6; ++i) d[i] = 0;
    }
};

// eastl::fixed_vector<GlyphTextureInfo, 256, true> (overflow allowed)
struct GlyphVector {
    GlyphTextureInfo* mpBegin;
    GlyphTextureInfo* mpEnd;
    GlyphTextureInfo* mpCapacity;
    unsigned int mAllocator;
    GlyphTextureInfo* mpPoolBegin;           // +0x10
    unsigned int mPad14;
    GlyphTextureInfo mBuffer[256];           // +0x18

    GlyphVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 256), mpPoolBegin(mBuffer) {}
    ~GlyphVector() { if (mpBegin && mpBegin != mpPoolBegin) operator delete[](mpBegin); }
    void DoInsertValue(GlyphTextureInfo* position, const GlyphTextureInfo& value);   // 0x007a8910
    GlyphTextureInfo& push_back()
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) GlyphTextureInfo();
        } else {
            DoInsertValue(mpEnd, GlyphTextureInfo());
        }
        return *(mpEnd - 1);
    }
    __forceinline void erase_front(GlyphTextureInfo* last)
    {
        GlyphTextureInfo* first = mpBegin;
        if (first != last) {
            GlyphTextureInfo* dst = first;
            for (GlyphTextureInfo* src = last; src != mpEnd; ++src, ++dst)
                *dst = *src;
            mpEnd -= (last - first);
        }
    }
};

struct AppPropertiesInner { char pad[0x110]; int mField110; };
struct AppProperties { char pad[0x3c]; AppPropertiesInner* mpInner; };
extern AppProperties* sAppProperties;                                      // 0x015fd918

void SetTransform(const __m128* pRows, int nRows);                          // 0x005291f0 (cdecl)
void SetTexture(int stage, unsigned int texture);                           // 0x011f1280 (cdecl)
void SetPrimitive(int a, int b);                                            // 0x006ddde0 (cdecl)
int  LockVertices(int nBytes, Vertex** ppVertices, int* pStride, VertexLock* pLock);   // 0x006dde90 (cdecl)
void CommitVertices();                                                      // 0x006ddee0 (cdecl)
void UnlockVertices(VertexLock* pLock);                                     // 0x006ddef0 (cdecl)
extern unsigned int gRasterDelta;                                           // 0x016f8b00

struct Render_RenderWare {
    char pad000[0xa37c];
    GlyphCache* mpGlyphCache;                // +0xa37c
    CompiledState** mppCompiledState;        // +0xa380
    int DrawGlyphs(const GlyphDisplayEntry* pGDEArray, unsigned int nGDECount, const unsigned int* pColorArray, bool bPerGlyphColor);   // 0x007a8a50
};

int Render_RenderWare::DrawGlyphs(const GlyphDisplayEntry* pGDEArray, unsigned int nGDECount, const unsigned int* pColorArray, bool bPerGlyphColor)
{
    if (nGDECount) {
        GlyphVector glyphArray;
        unsigned int color = pColorArray[0];
        unsigned int nColorIndex = 0;
        TextureInfo* pCurrentTexture = 0;
        float fOffset = (sAppProperties->mpInner->mField110 != 0) ? 0.5f : 0.0f;

        VertexLock lock;
        __m128 rows[4];
        rows[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
        rows[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
        rows[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
        rows[3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
        SetTransform(rows, 4);

        const GlyphDisplayEntry* pEnd = pGDEArray + nGDECount;
        const GlyphDisplayEntry* pBatchBegin = pGDEArray;
        for (const GlyphDisplayEntry* pGDE = pGDEArray; pGDE < pEnd; ++pGDE) {
            const GlyphDisplayEntry* pNext = pGDE + 1;
            GlyphTextureInfo* pInfo = &glyphArray.push_back();

            if (!mpGlyphCache->GetGlyphTextureInfo(pGDE->mpFont, pGDE->mGlyphId, *pInfo)) {
                const GlyphBitmap* pBitmap;
                if (pGDE->mpFont->RenderGlyphBitmap(&pBitmap, pGDE->mGlyphId, 0, 0.0f, 0.0f)) {
                    GlyphCache* pCache = mpGlyphCache;
                    pCache->BeginUpdate(pCache->GetTextureInfo(0));
                    mpGlyphCache->AddGlyphTexture(pGDE->mpFont, pGDE->mGlyphId, pBitmap->mpData,
                                                  pBitmap->mnWidth, pBitmap->mnHeight, pBitmap->mnStride,
                                                  pBitmap->mBitmapFormat, *pInfo);
                    pCache = mpGlyphCache;
                    pCache->EndUpdate(pCache->GetTextureInfo(0));
                    pGDE->mpFont->DoneGlyphBitmap(pBitmap);
                }
            }

            TextureInfo* pTexture = pInfo->mpTextureInfo;
            bool bNewTexture = (pCurrentTexture != 0 && pCurrentTexture != pTexture);
            const GlyphDisplayEntry* pBatchEnd = pGDE;
            bool bLast = (pNext == pEnd);
            if (bLast)
                pBatchEnd = pNext;

            if (bNewTexture || bLast) {
                int nGlyphs = (int)(pBatchEnd - pBatchBegin);
                pCurrentTexture = pTexture;
                (*mppCompiledState)->Dispatch();
                SetTexture(0, pTexture->mTexture);
                gRasterDelta |= 1;
                SetPrimitive(3, 2);

                int nDone = 0;
                const GlyphTextureInfo* pCached = glyphArray.mpBegin;
                while (nDone < nGlyphs) {
                    Vertex* pVertex;
                    int nStride;
                    int nVerts = LockVertices((nGlyphs - nDone) * 4, (Vertex**)&pVertex, &nStride, &lock);
                    int nQuads = nVerts / 4;
                    if (nQuads == 0 || nStride != 0x18)
                        break;
                    const GlyphDisplayEntry* pQuadEnd = pBatchBegin + nQuads;
                    for (; pBatchBegin != pQuadEnd; ++pBatchBegin, ++pCached) {
                        if (bPerGlyphColor)
                            color = pColorArray[nColorIndex++];
                        pVertex[0].x = (float)(int)pBatchBegin->mfX1 - fOffset;
                        pVertex[0].y = (float)(int)pBatchBegin->mfY1 - fOffset;
                        pVertex[0].z = 0.0f;
                        pVertex[0].color = color;
                        pVertex[0].u = pCached->mX1;
                        pVertex[0].v = pCached->mY1;
                        pVertex[1].x = (float)(int)pBatchBegin->mfX2 - fOffset;
                        pVertex[1].y = (float)(int)pBatchBegin->mfY1 - fOffset;
                        pVertex[1].z = 0.0f;
                        pVertex[1].color = color;
                        pVertex[1].u = pCached->mX2;
                        pVertex[1].v = pCached->mY1;
                        pVertex[2].x = (float)(int)pBatchBegin->mfX2 - fOffset;
                        pVertex[2].y = (float)(int)pBatchBegin->mfY2 - fOffset;
                        pVertex[2].z = 0.0f;
                        pVertex[2].color = color;
                        pVertex[2].u = pCached->mX2;
                        pVertex[2].v = pCached->mY2;
                        pVertex[3].x = (float)(int)pBatchBegin->mfX1 - fOffset;
                        pVertex[3].y = (float)(int)pBatchBegin->mfY2 - fOffset;
                        pVertex[3].z = 0.0f;
                        pVertex[3].color = color;
                        pVertex[3].u = pCached->mX1;
                        pVertex[3].v = pCached->mY2;
                        pVertex += 4;
                    }
                    CommitVertices();
                    nDone += nQuads;
                }
                UnlockVertices(&lock);
                glyphArray.erase_front(glyphArray.mpBegin + nDone);
            }
        }
    }
    return 0;
}

}  // namespace DrawGlyphsImpl
