// slice s007a7d50  --  SP::cTextRenderer (retail layout).
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
#include "types.h"
#include <xmmintrin.h>

// retail inlined the CRT ftol helper (`_ftol2_sse`), which converts with the SSE1 rounding
// `cvtss2si` instead of the truncating `cvttss2si` cl emits for a plain cast; round the same way.
static const float kScale255 = 255.0f;
static __forceinline int Scale255(const float* p)
{
    __m128 v = _mm_mul_ss(_mm_load_ss(p), _mm_load_ss(&kScale255));
    return _mm_cvtss_si32(v);
}

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
__declspec(dllimport) int wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
__declspec(dllimport) wchar_t* wcsncpy(wchar_t*, const wchar_t*, unsigned int);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);

// ---- helpers referenced only by address ---------------------------------------
extern "C" void* FUN_007658f0();               // (unused here)
extern "C" void* FUN_007654f0();
extern "C" void  FUN_00704d80(void*);
struct IResManager;
extern "C" IResManager* FUN_0067dcd0_GetManager();
extern "C" void* FUN_0067de10();
extern "C" void  FUN_0067dfe0(void*);
extern "C" void* FUN_0067dd70_MaterialManager();
extern "C" unsigned int FUN_00932e80(const char*, unsigned int, int);
extern "C" void* FUN_00885ad0(int);
extern "C" char FUN_0089d300[];                // __thiscall LayoutSettings::operator=(void*)
extern "C" void  FUN_00890f50(void*);
extern "C" void  FUN_00894_TextStyle_ctor(void*);
extern "C" void  FUN_00890560_Layout_dtor(void*);
extern "C" void  FUN_0088b450(void*);
extern "C" void  FUN_0070f520(void*, void*);
extern "C" void  FUN_00c50ad0(void*, void*, void*);
extern "C" void* FUN_00951bb0(unsigned int, unsigned int, void*);
extern "C" int   FUN_011ef750(int, int, void*);
extern "C" int   FUN_011ef880(void*);
extern "C" void* FUN_00885bd0_GetStyleManager(int);
struct StyleManagerStub { void GetStyle(int style, void* out); };
struct LayoutSettingsStub { void SetAll(void* other); };
extern "C" void* FUN_0088ae10(void*);
extern "C" void  FUN_00926020_zone_new();      // (unused)

// ---- stub types ---------------------------------------------------------------
struct Layout; struct TextStyle; struct TextRenderWare;

// thiscall callees (this in ecx, `ret N`); the name carries the VA for the harness.
struct LayoutObj {                              // Layout / cLayout (0x37c) and the +0xa000 sub-object
    void init_00890f50();                       // ctor body
    void dtor_00890560();                       // dtor
};
struct TextStyleObj {                           // TextStyle (0x278)
    void ctor_008941d0();
};
struct ObjDevice {                              // the object behind obj+0x34
    bool acquire_011ef750(int mode, int unused, void* data);
    bool release_011ef880(void* data);
};
struct PtrPair {                                // 0x190/0x194 pair owner (eastl vector-like)
    void free_0070f520(void* begin, void* end);
};
struct GlyphCacheObj {                          // the 0x1a8-byte object the factory allocates
    void init_0088ae10(void* arg);
    void dtor_0088b450();
};

// 0xa384-byte render backend; members used at +0xa000 (Layout), +0xa37c, +0xa380.
struct TextRenderWare {
    char pad000[0xa384];
    void* ScalarDelete(unsigned char flags); // 007a88b0
};

extern "C" char VT_TextRenderWareObject[];

// 0x278-byte text style; first member is a 32-char font name.
struct TextStyleStub {
    wchar_t mFontName[32];     // +0x00 (terminator at +0x3e = index 31)
    char pad040[0x200 - 0x40];
    float mFontSize;           // +0x200
    char pad204[0x214 - 0x204];
    int   mField214;           // +0x214
    char pad218[0x224 - 0x218];
    unsigned int mColor;       // +0x224
};

struct cTextRenderer {
    void* mBuffer0;            // +0x000
    void* mBuffer1;            // +0x004
    int   mField08;            // +0x008
    bool  mInitialized;        // +0x00c
    char  pad00d[3];
    TextRenderWare* mRenderImpl; // +0x010
    Layout* mLayout;           // +0x014
    TextStyleStub* mTextStyle; // +0x018
    bool  mStyleChanged;       // +0x01c
    char  pad01d[0x168 - 0x01d];
    char  mCriticalSection[24];// +0x168

    void Init();               // 007a84d0
    void CtorBody();           // 007a8390
    void Release();            // 007a8530
    void EnsureBuffers();      // 007a8310
    void SetStyle(int style);  // 007a82a0
    void SetStyleScale(float f);          // 007a82d0
    void SetFontName(const wchar_t* name); // 007a8550
    void SetFontSize(float size);          // 007a85a0
    void SetColor(const float* rgb);       // 007a85e0
    bool AllocDevice(void* obj);           // 007a8660
    bool FreeDevice(void* obj);            // 007a8700
    ~cTextRenderer();                      // 007a8790
    void* InsertGlyph(void* position, void* value); // 007a8910
};

extern "C" void cTextRenderer_ctor(cTextRenderer*);      // 007a7210-ish init
extern "C" void FUN_007a7d50(cTextRenderer*);
extern "C" void FUN_007a8360();

// @ 0x007a82a0
void cTextRenderer::SetStyle(int style)
{
    void* mgr = FUN_00885bd0_GetStyleManager(1);
    if (mgr != 0) {
        ((StyleManagerStub*)mgr)->GetStyle(style, this->mTextStyle);
        this->mStyleChanged = true;
    }
}

// @ 0x007a82d0
void cTextRenderer::SetStyleScale(float f)
{
    volatile float t = f * kScale255;
    unsigned int alpha = (unsigned int)_mm_cvtss_si32(_mm_load_ss((const float*)&t)) << 0x18;
    TextStyleStub* s = this->mTextStyle;
    ((unsigned char*)&s->mColor)[3] = 0;
    s->mColor |= alpha;
}

// @ 0x007a8310
void cTextRenderer::EnsureBuffers()
{
    this->mField08 = 0;
    if (this->mBuffer0 == 0) {
        this->mBuffer0 = EASTL_allocator_allocate(0x14000, "Graphics", 0, 0, 0, 0);
        this->mBuffer1 = EASTL_allocator_allocate(0x2000, "Graphics", 0, 0, 0, 0);
    }
}

// @ 0x007a8360
void FUN_007a8360()
{
    void* p = FUN_0067de10();
    if (p) {
        FUN_0067dfe0(0);
        ((void(__thiscall*)(void*))((*(void***)p)[0x0c / 4]))(p);
    }
}

// @ 0x007a8390  SP::cTextRenderer::cTextRenderer
void cTextRenderer::CtorBody()
{
    cTextRenderer* self = this;
    self->mInitialized = false;
    void* impl = EASTL_allocator_allocate(0xa384, "Graphics", 0, 0, 0, 0);
    if (impl)
        ((LayoutObj*)((char*)impl + 0xa000))->init_00890f50();
    self->mRenderImpl = (TextRenderWare*)impl;
    void* layout = EASTL_allocator_allocate(0x37c, "Graphics", 0, 0, 0, 0);
    if (layout)
        ((LayoutObj*)layout)->init_00890f50();
    self->mLayout = (Layout*)layout;
    void* style = EASTL_allocator_allocate(0x278, "Graphics", 0, 0, 0, 0);
    if (style)
        ((TextStyleObj*)style)->ctor_008941d0();
    self->mTextStyle = (TextStyleStub*)style;
    self->mStyleChanged = true;

    const wchar_t* src = L"Arial";
    wchar_t* dst = self->mTextStyle->mFontName;
    while ((*dst++ = *src++) != 0) { }

    self->mTextStyle->mFontSize = 12.0f;
    self->mTextStyle->mField214 = 1;
    self->mTextStyle->mColor = 0xffffffff;
    self->mField08 = -1;
    self->mBuffer0 = 0;
    self->mBuffer1 = 0;
}

// @ 0x007a84d0
void cTextRenderer::Init()
{
    if (!this->mInitialized) {
        TextRenderWare* r = this->mRenderImpl;
        this->mInitialized = true;
        void* mat = FUN_0067dd70_MaterialManager();
        unsigned int h = FUN_00932e80("generic2D", 0x811c9dc5, 1);
        void* tex = ((void* (__thiscall*)(void*, unsigned int))((*(void***)mat)[0x28 / 4]))(mat, h);
        *(void**)((char*)r + 0xa380) = tex;
        *(void**)((char*)r + 0xa37c) = FUN_0067de10();
        void* ls = FUN_00885ad0(1);
        ((LayoutSettingsStub*)this->mLayout)->SetAll(ls);
    }
}

// @ 0x007a8530
void cTextRenderer::Release()
{
    if (this->mInitialized) {
        this->mInitialized = false;
        TextRenderWare* r = this->mRenderImpl;
        *(void**)((char*)r + 0xa380) = 0;
        *(void**)((char*)r + 0xa37c) = 0;
    }
}

// @ 0x007a8550
void cTextRenderer::SetFontName(const wchar_t* name)
{
    if (!this->mInitialized)
        Init();
    if (wcsncmp(this->mTextStyle->mFontName, name, 0x1f) != 0) {
        wcsncpy(this->mTextStyle->mFontName, name, 0x1f);
        this->mTextStyle->mFontName[0x1f] = 0;
        this->mStyleChanged = true;
    }
}

// @ 0x007a85a0
void cTextRenderer::SetFontSize(float size)
{
    if (!this->mInitialized)
        Init();
    if (this->mTextStyle->mFontSize != size) {
        this->mStyleChanged = true;
        this->mTextStyle->mFontSize = size;
    }
}

// @ 0x007a85e0
void cTextRenderer::SetColor(const float* rgb)
{
    this->mTextStyle->mColor &= 0xff000000;
    this->mTextStyle->mColor |= Scale255(rgb + 0) << 0x10;
    this->mTextStyle->mColor |= Scale255(rgb + 1) << 0x08;
    this->mTextStyle->mColor |= Scale255(rgb + 2);
}

// @ 0x007a8660
bool cTextRenderer::AllocDevice(void* obj)
{
    EnterCriticalSection(this->mCriticalSection);
    if (*(int*)((char*)obj + 0x38) == 0) {
        if (((ObjDevice*)*(void**)((char*)obj + 0x34))->acquire_011ef750(2, 0, (char*)obj + 8)) {
            *(void**)((char*)obj + 0x38) = *(void**)((char*)obj + 8);
            *(void**)((char*)obj + 0x3c) = *(void**)((char*)obj + 0x14);
            EnterCriticalSection(this->mCriticalSection);
            LeaveCriticalSection(this->mCriticalSection);
            return true;
        }
    }
    LeaveCriticalSection(this->mCriticalSection);
    return false;
}

// @ 0x007a8700
bool cTextRenderer::FreeDevice(void* obj)
{
    EnterCriticalSection(this->mCriticalSection);
    if (*(int*)((char*)obj + 0x38) != 0) {
        ((ObjDevice*)*(void**)((char*)obj + 0x34))->release_011ef880((char*)obj + 8);
        *(void**)((char*)obj + 0x38) = 0;
        LeaveCriticalSection(this->mCriticalSection);
        LeaveCriticalSection(this->mCriticalSection);
        return true;
    }
    LeaveCriticalSection(this->mCriticalSection);
    return false;
}

// @ 0x007a8790
cTextRenderer::~cTextRenderer()
{
    if (this->mInitialized) {
        TextRenderWare* r = this->mRenderImpl;
        *(void**)((char*)r + 0xa380) = 0;
        *(void**)((char*)r + 0xa37c) = 0;
    }
    EASTL_allocator_deallocate(this->mBuffer0);
    EASTL_allocator_deallocate(this->mBuffer1);
    if (this->mRenderImpl) {
        ((LayoutObj*)((char*)this->mRenderImpl + 0xa000))->dtor_00890560();
        EASTL_allocator_deallocate(this->mRenderImpl);
    }
    if (this->mLayout) {
        ((LayoutObj*)this->mLayout)->dtor_00890560();
        EASTL_allocator_deallocate(this->mLayout);
    }
    EASTL_allocator_deallocate(this->mTextStyle);
}

// @ 0x007a8810
extern "C" void* FUN_007a8810()
{
    void* p = EASTL_allocator_allocate(0x1a8, "Graphics", 0, 0, 0, 0);
    if (p) {
        ((GlyphCacheObj*)p)->init_0088ae10(0);
        *(void**)p = (void*)&VT_TextRenderWareObject;
        *(void**)((char*)p + 0x190) = 0;
        *(void**)((char*)p + 0x194) = 0;
        *(void**)((char*)p + 0x198) = 0;
    }
    else {
        p = 0;
    }
    ((void(__thiscall*)(void*, int, int))((*(void***)p)[0x10 / 4]))(p, 2, 1);
    ((void(__thiscall*)(void*, int, int))((*(void***)p)[0x08 / 4]))(p, 1, 0);
    FUN_0067dfe0(p);
    return p;
}

// @ 0x007a88b0  scalar deleting destructor of the 0x1a8-byte render object
void* TextRenderWare::ScalarDelete(unsigned char flags)
{
    TextRenderWare* self = this;
    PtrPair* pair = (PtrPair*)((char*)self + 0x190);
    pair->free_0070f520(*(void**)((char*)self + 0x190), *(void**)((char*)self + 0x194));
    void* p = *(void**)((char*)self + 0x190);
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
    ((GlyphCacheObj*)self)->dtor_0088b450();
    if (flags & 1)
        EASTL_allocator_deallocate(self);
    return self;
}

// @ 0x007a8910  eastl vector insert (stride 0x14)
struct GlyphVec {
    void* begin;    // +0
    void* end;      // +4
    void* cap;      // +8
    void* InsertAt(void* position, void* value);
};

extern "C" void* FUN_007a8910(GlyphVec* self, void* position, void* value)
{
    if (self->end != self->cap) {
        if (position <= value && value < self->end)
            value = (char*)value + 0x14;
        void* end = self->end;
        if (end) {
            *(uint32_t*)((char*)end + 0x00) = *(uint32_t*)((char*)end - 0x14);
            *(uint32_t*)((char*)end + 0x04) = *(uint32_t*)((char*)end - 0x10);
            *(uint32_t*)((char*)end + 0x08) = *(uint32_t*)((char*)end - 0x0c);
            *(uint32_t*)((char*)end + 0x0c) = *(uint32_t*)((char*)end - 0x08);
            *(uint32_t*)((char*)end + 0x10) = *(uint32_t*)((char*)end - 0x04);
        }
        FUN_00c50ad0((char*)self->end - 0x14, position, self->end);
        *(uint32_t*)((char*)position + 0x00) = *(uint32_t*)((char*)value + 0x00);
        *(uint32_t*)((char*)position + 0x04) = *(uint32_t*)((char*)value + 0x04);
        *(uint32_t*)((char*)position + 0x08) = *(uint32_t*)((char*)value + 0x08);
        *(uint32_t*)((char*)position + 0x0c) = *(uint32_t*)((char*)value + 0x0c);
        *(uint32_t*)((char*)position + 0x10) = *(uint32_t*)((char*)value + 0x10);
        self->end = (char*)self->end + 0x14;
        return 0;
    }

    int count = (int)((char*)self->end - (char*)self->begin) / 0x14;
    int newCap;
    void* newBegin;
    if (count == 0) {
        newCap = 1;
        newBegin = EASTL_allocator_allocate((unsigned)(newCap * 0x14 * 4), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    else {
        newCap = count * 2;
        if (newCap != 0) {
            newBegin = EASTL_allocator_allocate((unsigned)(newCap * 0x14 * 4), "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        } else {
            newBegin = 0;
        }
    }
    void* newEnd = (void*)FUN_00951bb0((unsigned)newBegin, (unsigned)self->begin,
                                       (void*)((char*)position - (char*)self->begin));
    if (newEnd) {
        *(uint32_t*)((char*)newEnd + 0x00) = *(uint32_t*)((char*)value + 0x00);
        *(uint32_t*)((char*)newEnd + 0x04) = *(uint32_t*)((char*)value + 0x04);
        *(uint32_t*)((char*)newEnd + 0x08) = *(uint32_t*)((char*)value + 0x08);
        *(uint32_t*)((char*)newEnd + 0x0c) = *(uint32_t*)((char*)value + 0x0c);
        *(uint32_t*)((char*)newEnd + 0x10) = *(uint32_t*)((char*)value + 0x10);
    }
    void* r = FUN_00951bb0((unsigned)((char*)newEnd + 0x14), (unsigned)position,
                           (void*)((char*)self->end - (char*)position));
    if (self->begin && *(int*)((char*)self->begin - 4) != 0)
        EASTL_allocator_deallocate(self->begin);
    self->begin = newBegin;
    self->end = r;
    self->cap = (char*)newBegin + newCap * 0x14;
    return self->begin;
}

// ===========================================================================
// SP::cGraphicsSystem::Init  (0x007a7d50)
// ===========================================================================
extern "C" long _InterlockedExchangeAdd(volatile long* addend, long value);
#pragma intrinsic(_InterlockedExchangeAdd)

// unnamed retail entry points
struct IManager;
extern "C" void  FUN_007c3a80();                 // thunk_FUN_007c3910
extern "C" void  FUN_006ddf80();
extern "C" void  FUN_007a41c0();
extern "C" void  FUN_006e10a0();                 // CreateBufferCheats
extern "C" void  FUN_006efb90();                 // CreateEffectsRendererSystem
extern "C" void  FUN_0067df70(void*);
extern "C" void  FUN_0067df80(void*);
extern "C" void  FUN_0067df90(void*);
extern "C" void  FUN_0067dfa0(void*);
extern "C" void  FUN_0067dfb0(void*);
extern "C" void  FUN_0067dfc0(void*);
extern "C" void  FUN_0067dfd0(void*);
extern "C" void  FUN_0067e010(void*);
extern "C" void  FUN_0067e020(void*);
extern "C" IManager* FUN_007ac410();
extern "C" void* FUN_007a8810();                 // CreateTextRenderWareObject
struct Obj2c;
extern "C" Obj2c* CreateObj2c_76e610();          // 0x0076e610
extern "C" IManager* FUN_00713c40();
extern "C" IManager* FUN_0070a040();
extern "C" IManager* FUN_0074fe70();
extern "C" IManager* FUN_007b6af0();
extern "C" char  FUN_007a49e0(int format);       // D3D format-support probe
extern "C" int   sCameraFormats_153b69c[4];      // 0x0153b69c

// six-argument placement allocation used by the "App" zone.  The `long` line parameter (vs `int` on
// the Graphics-zone operator) keeps the two address annotations distinguishable for resolve.py.
void* operator new(unsigned int size, const char* name, int flags, int debugFlags,
                   const char* file, long line);   // 0x00f473a0
void  operator delete(void* p, const char* name, int flags, int debugFlags,
                      const char* file, long line);

struct IRefCounted {
    virtual int AddRef();                  // +0x00
    virtual int Release();                 // +0x04
};

// manager interface: slot 0x08/0x0c/0x10 are the init/shutdown entry points used here
struct IManager : IRefCounted {
    virtual void v02();                    // +0x08
    virtual void v03();                    // +0x0c
    virtual void v04();                    // +0x10
};

// resource-manager singleton: slot 0x44 registers a resource
struct IResManager {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
    virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
    virtual void r08(); virtual void r09(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15();
    virtual void r16();
    virtual void Register(int kind, void* resource, int flags);   // +0x44
};

// renderer interface: slot 0x4c takes an effect object
struct cIRenderer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual void AddEffectObject(void* object, int a, int b);     // +0x4c
};

// objects registered with the resource manager at startup (both zone "Graphics")
struct GraphicsZoneObject {
    static void* operator new(unsigned int size, const char* name, int flags, int debugFlags,
                              const char* file, int line);    // 0x00926020
    static void  operator delete(void* p, const char* name, int flags, int debugFlags,
                                 const char* file, int line);
};
struct cRenderDeviceKey : GraphicsZoneObject {
    char mData[0x0c];
    cRenderDeviceKey();                    // 0x007654f0
};
struct cRenderInfoKey : GraphicsZoneObject {
    char mData[0x08];
    cRenderInfoKey();                      // 0x00704d80
};

struct cFilterChain : IRefCounted {
    virtual void v02();
    virtual void v03();
    virtual void Initialize();             // +0x10
    cFilterChain();
    char mData[0x228 - 0x04];
};

struct cEffectsResources : IRefCounted {
    void ResourceInit();                   // 0x006f1860
    cEffectsResources();
    char mData[0xc8 - 0x04];
};

struct cEffectsRenderer : IRefCounted {
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void SetRenderLevel(int level);                     // +0x78
    cEffectsRenderer();
    char mData[0x388 - 0x04];
};

// first base carries its own vtable so the ref-count vtable lands at +0x08
struct ShadowPrimary { virtual void v00(); int mPad; };
struct cShadowWorld : ShadowPrimary, IRefCounted {   // ref-count vtable at +0x08
    void Update();                               // 0x00780ab0
    cShadowWorld();
    char mData[0x228 - 0x0c];
};

// small two-vtable Havok object handed to the renderer
extern char VT_hkReferencedObject_13ef094[];
extern char VT_cFinalObj_140b778[];
extern char VT_cFinalObj_14188c0[];
struct cFinalObj {
    void* mVtbl0;          // +0x00
    void* volatile mVtbl4; // +0x04 (retail keeps the first vtable store)
    int   mRefCount;       // +0x08
    cFinalObj()
    {
        mVtbl4 = (void*)&VT_hkReferencedObject_13ef094;
        mRefCount = 0;
        mVtbl0 = (void*)&VT_cFinalObj_140b778;
        mVtbl4 = (void*)&VT_cFinalObj_14188c0;
    }
};

// AutoRefCount-style release used for the plain texture pointers: fetch-add -1, read back,
// saturate at 1.  Mirrors the retail helper's shape (pointer kept in eax).
inline void ReleaseRefCount(void* p, int rcOffset = 8)
{
    if (p) {
        volatile long* rc = (volatile long*)((char*)p + rcOffset);
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

template <typename T>
struct AutoRef {
    T* mpObject;
    T* operator->() const { return mpObject; }
    // volatile-qualified read: retail reloads the handle with a volatile access before
    // handing it to the manager-registration helpers
    T* GetRaw() const volatile { return mpObject; }
    AutoRef& operator=(T* p)
    {
        T* old = mpObject;
        if (p != old) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};

struct AppPropsInner {
    char pad000[0x130];
    int  mFlag;                            // +0x130
};
struct AppProps {
    char pad000[0x3c];
    AppPropsInner* mpInner;                // +0x03c
};
extern "C" AppProps* _sAppProperties;      // 0x015fd918

struct cGraphicsSystem {
    void* vtbl0;                                   // +0x000
    void* vtbl1;                                   // +0x004
    int   pad008;                                  // +0x008
    bool  mInitialized;                            // +0x00c
    char  pad00d[3];
    cIRenderer* mRenderer;                         // +0x010
    AutoRef<IManager> mTextureManager;             // +0x014
    AutoRef<IManager> mRTTManager;                 // +0x018
    AutoRef<IManager> mThumbnailManager;           // +0x01c
    AutoRef<IManager> mMaterialManager;            // +0x020
    AutoRef<IManager> mLightingManager;            // +0x024
    AutoRef<IManager> mModelManager;               // +0x028
    void* mDebugDraw;                              // +0x02c
    AutoRef<cFilterChain> mFilterChainRenderer;    // +0x030
    AutoRef<cEffectsResources> mEffectsResources;  // +0x034
    AutoRef<cEffectsRenderer> mEffectsRenderer;    // +0x038
    AutoRef<cShadowWorld> mShadowWorld;            // +0x03c
    char pad040[0x80 - 0x40];
    void* mCameraSnapshotZTexture;                 // +0x080
    char pad084[0x8c - 0x84];
    void* mBakeBuffers[2];                         // +0x08c
    char pad094[0x9c - 0x94];
    void* mBufferTextures[4];                      // +0x09c
    char pad0ac[0x16c - 0xac];
    int   mCameraSnapshotFormat;                   // +0x16c
    char pad170[0x190 - 0x170];
    bool  mDebugFlushState;                        // +0x190

    bool Init();
    void CreateBuiltinModels();                    // 0x007a7210
    void InitShadowTexture();                      // 0x007a57d0
    void InitSnapshotTexture();                    // 0x007a5900
    void InitBufferTexture(int index);             // 0x007a66c0
};

// @ 0x007a7d50
bool cGraphicsSystem::Init()
{
    mInitialized = true;

    FUN_0067dcd0_GetManager()->Register(1, new ("Graphics", 0, 0, 0, 0) cRenderDeviceKey(), 0);
    FUN_0067dcd0_GetManager()->Register(1, new ("Graphics", 0, 0, 0, 0) cRenderInfoKey(), 0);

    FUN_007c3a80();
    FUN_006ddf80();
    FUN_007a41c0();
    FUN_006e10a0();

    mTextureManager = FUN_007ac410();
    mTextureManager->v03();
    FUN_0067df80(mTextureManager.GetRaw());

    FUN_007a8810();
    mRTTManager = (IManager*)CreateObj2c_76e610();
    mRTTManager->v02();
    FUN_0067dfb0(mRTTManager.GetRaw());

    mMaterialManager = FUN_00713c40();
    mMaterialManager->v03();
    FUN_0067df70(mMaterialManager.GetRaw());

    mLightingManager = FUN_0070a040();
    mLightingManager->v03();
    FUN_0067dfa0(mLightingManager.GetRaw());

    mModelManager = FUN_0074fe70();
    mModelManager->v03();
    FUN_0067df90(mModelManager.GetRaw());

    CreateBuiltinModels();

    mThumbnailManager = FUN_007b6af0();
    mThumbnailManager->v03();
    FUN_0067dfc0(mThumbnailManager.GetRaw());

    mFilterChainRenderer = new ("App", 0, 0, 0, 0) cFilterChain();
    mFilterChainRenderer->Initialize();

    mEffectsResources = new ("App", 0, 0, 0, 0) cEffectsResources();
    mEffectsResources->ResourceInit();
    FUN_0067e010(mEffectsResources.GetRaw());

    FUN_006efb90();

    mEffectsRenderer = new ("App", 0, 0, 0, 0) cEffectsRenderer();
    mEffectsRenderer->SetRenderLevel(0x1f);
    FUN_0067e020(mEffectsRenderer.GetRaw());

    mShadowWorld = new ("App", 0, 0, 0, 0) cShadowWorld();
    mShadowWorld->Update();
    FUN_0067dfd0(mShadowWorld.mpObject ? (char*)mShadowWorld.mpObject + 8 : 0);

    mRenderer->AddEffectObject(new ("App", 0, 0, 0, 0) cFinalObj(), 0, 0);

    mBufferTextures[0] = 0;
    mBufferTextures[1] = 0;
    mBufferTextures[2] = 0;
    mBufferTextures[3] = 0;

    InitShadowTexture();
    InitSnapshotTexture();
    for (unsigned int i = 0; i < 4; ++i)
        InitBufferTexture((int)i);

    mCameraSnapshotZTexture = 0;
    for (int i = 0; i < 2; ++i) {
        if (mBakeBuffers[i]) {
            void* p = mBakeBuffers[i];
            mBakeBuffers[i] = 0;
            ReleaseRefCount(p);
        }
    }

    mCameraSnapshotFormat = -1;
    for (unsigned int i = 0; i < 4; ++i) {
        if (FUN_007a49e0(sCameraFormats_153b69c[i])) {
            mCameraSnapshotFormat = sCameraFormats_153b69c[i];
            break;
        }
    }

    mDebugFlushState = _sAppProperties->mpInner->mFlag != 0;
    return true;
}
