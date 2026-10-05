// slice s007a7d50  --  SP::cTextRenderer (retail layout).
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p);
__declspec(dllimport) int wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
__declspec(dllimport) wchar_t* wcsncpy(wchar_t*, const wchar_t*, unsigned int);
extern "C" void  EnterCriticalSection(void*);
extern "C" void  LeaveCriticalSection(void*);

// ---- helpers referenced only by address ---------------------------------------
extern "C" void* FUN_007658f0();               // (unused here)
extern "C" void* FUN_007654f0();
extern "C" void  FUN_00704d80(void*);
extern "C" void* FUN_0067dcd0_GetManager();
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

// 0xa384-byte render backend; members used at +0xa000 (Layout), +0xa37c, +0xa380.
struct TextRenderWare {
    char pad000[0xa384];
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
extern "C" void FUN_007a8390(cTextRenderer*);
extern "C" void FUN_007a8360();
extern "C" void FUN_007a8810();
extern "C" void* FUN_007a88b0(TextRenderWare*, unsigned char);

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
    ((unsigned char*)&this->mTextStyle->mColor)[3] = 0;
    this->mTextStyle->mColor |= (int)(f * 255.0f) << 0x18;
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
extern "C" void FUN_007a8390(cTextRenderer* self)
{
    self->mInitialized = false;
    void* impl = EASTL_allocator_allocate(0xa384, "Graphics", 0, 0, 0, 0);
    if (impl)
        FUN_00890f50(impl);
    self->mRenderImpl = (TextRenderWare*)impl;
    void* layout = EASTL_allocator_allocate(0x37c, "Graphics", 0, 0, 0, 0);
    if (layout)
        FUN_00890f50(layout);
    self->mLayout = (Layout*)layout;
    void* style = EASTL_allocator_allocate(0x278, "Graphics", 0, 0, 0, 0);
    if (style)
        FUN_00894_TextStyle_ctor(style);
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
    this->mTextStyle->mColor |= (int)(rgb[0] * 255.0f) << 0x10;
    this->mTextStyle->mColor |= (int)(rgb[1] * 255.0f) << 0x08;
    this->mTextStyle->mColor |= (int)(rgb[2] * 255.0f);
}

// @ 0x007a8660
bool cTextRenderer::AllocDevice(void* obj)
{
    EnterCriticalSection(this->mCriticalSection);
    if (*(int*)((char*)obj + 0x38) == 0) {
        if (FUN_011ef750(2, 0, (char*)obj + 8)) {
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
        FUN_011ef880((char*)obj + 8);
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
        FUN_00890560_Layout_dtor((char*)this->mRenderImpl + 0xa000);
        EASTL_allocator_deallocate(this->mRenderImpl);
    }
    if (this->mLayout) {
        FUN_00890560_Layout_dtor(this->mLayout);
        EASTL_allocator_deallocate(this->mLayout);
    }
    EASTL_allocator_deallocate(this->mTextStyle);
}

// @ 0x007a8810
void FUN_007a8810()
{
    void* p = EASTL_allocator_allocate(0x1a8, "Graphics", 0, 0, 0, 0);
    if (p) {
        FUN_0088ae10(0);
        *(void**)p = (void*)&VT_TextRenderWareObject;
        *(void**)((char*)p + 0x190) = 0;
        *(void**)((char*)p + 0x194) = 0;
        *(void**)((char*)p + 0x198) = 0;
    }
    else {
        p = 0;
    }
    ((void(__thiscall*)(void*, int))((*(void***)p)[0x10 / 4]))(p, 2);
    ((void(__thiscall*)(void*, int, int))((*(void***)p)[0x08 / 4]))(p, 1, 0);
    FUN_0067dfe0(p);
}

// @ 0x007a88b0  scalar deleting destructor of the 0x1a8-byte render object
extern "C" void* FUN_007a88b0(TextRenderWare* self, unsigned char flags)
{
    FUN_0070f520(*(void**)((char*)self + 0x190), *(void**)((char*)self + 0x194));
    void* p = *(void**)((char*)self + 0x190);
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
    FUN_0088b450(self);
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

// @ 0x007a7d50  large render initialization; body omitted (partial)
extern "C" void FUN_007a7d50(cTextRenderer* self)
{
    self->mInitialized = true;
    self->Init();
}
