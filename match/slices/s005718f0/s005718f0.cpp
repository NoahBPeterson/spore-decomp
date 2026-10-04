// slice s005718f0
// Mixed module flags: the EASTL vector<Key12> code (0x5718f0-0x571c40) is /Od /Ob1;
// Fabs needs /fp:fast; everything else is /O2.
#include <new>
#include <string.h>
#include <math.h>
#include <intrin.h>
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// ---------------------------------------------------------------------------
// EASTL vector of 12-byte sortable keys (unoptimized module: /Od /Ob1)
// ---------------------------------------------------------------------------
struct Allocator { const char* mpName; };

void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // 0x42dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate

struct Key12 {
    uint32_t mA;
    uint32_t mB;
    uint32_t mC;
    bool operator<(const Key12& rhs) const;      // 0x5715d0
};

Key12* __cdecl UninitializedCopyKey12(Key12* first, Key12* last, Key12* dest);   // 0x50f8b0

inline Key12* copy_backward_impl(Key12* first, Key12* last, Key12* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

inline Key12* copy_backward(Key12* first, Key12* last, Key12* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}

struct KeyVector {
    Key12* mpBegin;
    Key12* mpEnd;
    Key12* mpCapacity;
    Allocator mAllocator;

    inline Key12* DoAllocate(uint32_t n) {
        uint32_t reserved[16];   // unused slots of the inlined allocator layers
        return n ? (Key12*)AllocatorAllocate(&mAllocator, n * sizeof(Key12), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        void* q = p;
        AllocatorDeallocate(q);
    }
    inline void DoFree(Key12* p, uint32_t n) {
        if (p)
            deallocate(p, n * sizeof(Key12));
    }
    ~KeyVector();
    Key12* insert(Key12* position, const Key12& value);
    void DoInsertValue(Key12* position, const Key12& value);
};

// @ 0x005718f0
Key12* KeyVector::insert(Key12* position, const Key12& value)
{
    const int n = position - mpBegin;
    if ((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) Key12(value);
    return mpBegin + n;
}

// @ 0x005719a0
KeyVector::~KeyVector()
{
    if (mpBegin)
        deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin) * sizeof(Key12));
}

// @ 0x005719f0
void KeyVector::DoInsertValue(Key12* position, const Key12& value)
{
    if (mpEnd != mpCapacity) {
        const Key12* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) Key12(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Key12* const pNewData = DoAllocate(nNewSize);
        Key12* pNewEnd = UninitializedCopyKey12(mpBegin, position, pNewData);
        ::new(pNewEnd) Key12(value);
        ++pNewEnd;
        pNewEnd = UninitializedCopyKey12(position, mpEnd, pNewEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

struct less_key {
    inline bool operator()(const Key12& a, const Key12& b) const { return a < b; }
};

inline void advance(Key12*& i, int n) { i += n; }

// @ 0x00571c40
Key12* __cdecl lower_bound(Key12* first, Key12* last, const Key12& value)
{
    int d = last - first;
    while (d > 0) {
        Key12* i = first;
        int d2 = d >> 1;
        advance(i, d2);
        less_key compare;
        if (compare(*i, value)) {
            first = ++i;
            d -= d2 + 1;
        } else
            d = d2;
    }
    return first;
}

// ---------------------------------------------------------------------------
// Math / string helpers (/O2)
// ---------------------------------------------------------------------------

// @ 0x00571cc0
__declspec(naked) float __cdecl Exp(float x)
{
    __asm {
        fld     dword ptr [esp + 4]
        fldl2e
        fmulp   st(1), st
        fld     st(0)
        frndint
        fxch    st(1)
        fsub    st, st(1)
        f2xm1
        fld1
        faddp   st(1), st
        fscale
        fstp    st(1)
        ret
    }
}

// @ 0x00571ce0  (/fp:fast)
float __cdecl Fabs(float x)
{
    return fabsf(x);
}

uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x932e80

// @ 0x00571cf0
uint32_t __cdecl SPIDFromName(const char* name)
{
    return FNVHash(name, 0x811c9dc5, 1);
}

struct ArrayAllocator {
    // @ 0x00571d10
    void deallocate(void* p, uint32_t n);
};

void ArrayAllocator::deallocate(void* p, uint32_t n)
{
    AllocatorDeallocate(p);
}

struct Block36 { uint32_t mData[9]; };

struct DirtyState {
    uint16_t mDirtyFlags;
    uint16_t mRevision;
    Key12 mKey;            // +0x04
    uint32_t mPad10;       // +0x10
    Block36 mBlock;        // +0x14

    void SetBlock(const Block36& b);
    void SetKey(const Key12& k);
};

// @ 0x00571d20
void DirtyState::SetBlock(const Block36& b)
{
    mBlock = b;
    mDirtyFlags |= 2;
    mRevision++;
}

// @ 0x00571d40
void DirtyState::SetKey(const Key12& k)
{
    mKey = k;
    mDirtyFlags |= 4;
    mRevision++;
}

struct Vec3 { float x, y, z; };

struct VecPair {
    Vec3 mA;
    Vec3 mB;
    VecPair& operator=(const VecPair& o);
};

// @ 0x00571d60
VecPair& VecPair::operator=(const VecPair& o)
{
    mB = o.mB;
    mA = o.mA;
    return *this;
}

struct OwnerHandle;
struct OwnerTarget {
    PV16 PV16 PV16 PV16 PV16 PV8 PV2 PV
    virtual void Notify(OwnerHandle* h, int arg);   // +0x16c
};
struct OwnerHandle {
    OwnerTarget* mpTarget;
    void Notify();
};

// @ 0x00571d90
void OwnerHandle::Notify()
{
    mpTarget->Notify(this, 0);
}

namespace EA { namespace Messaging {
struct IHandler;
struct IServer {
    PV8 PV2 PV
    virtual bool RemoveHandler(IHandler* h, uint32_t id, int priority);   // +0x2c
};

// @ 0x00571db0
bool RemoveHandler(IServer* server, IHandler* handler, const uint32_t* ids, uint32_t count, int priority)
{
    bool result = true;
    for (uint32_t i = 0; i < count; ++i)
        if (!server->RemoveHandler(handler, ids[i], priority))
            result = false;
    return result;
}
} }

// @ 0x00571e00
int __cdecl Strlen16(const wchar_t* p)
{
    const wchar_t* s = p;
    while (*s)
        ++s;
    return s - p;
}

// @ 0x00571e20
wchar_t* __cdecl Memset16(wchar_t* p, int n, wchar_t c)
{
    wchar_t* const end = p + n;
    while (p < end)
        *p++ = c;
    return end;
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);

// @ 0x00571e60
uint64_t __cdecl GetStopwatchCycle()
{
    int64_t t;
    QueryPerformanceCounter(&t);
    return (uint64_t)t;
}

namespace EA {
class Stopwatch {
public:
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    void Restart();
};

static inline uint64_t GetStopwatchCycleInline()
{
    int64_t t;
    QueryPerformanceCounter(&t);
    return (uint64_t)t;
}

// @ 0x00571e80
void Stopwatch::Restart()
{
    if (mnUnits == 1)
        mnStartTime = __rdtsc();
    else
        mnStartTime = GetStopwatchCycleInline();
    mnTotalElapsedTime = 0;
}

namespace Random {
class RandomLinearCongruential {
public:
    uint32_t mnSeed;
    uint32_t RandomUint32Uniform(uint32_t n);
};
} }

extern EA::Random::RandomLinearCongruential sMathRandom;

// @ 0x00571ed0
uint32_t __cdecl RandomUint32(uint32_t n)
{
    return sMathRandom.RandomUint32Uniform(n);
}

namespace EA {
struct Variant {
    uint32_t mData[2];
    uint32_t mValue;       // +0x08
    uint32_t mPad;
    uint16_t mFlags;       // +0x10
    uint16_t mTypeId;      // +0x12
    void Destruct(int);
    void Clear();
    uint32_t AsUint32() const;
};

// @ 0x00571ee0
void Variant::Clear()
{
    if (mFlags & 4)
        Destruct(0);
}

// @ 0x00571ef0
uint32_t Variant::AsUint32() const
{
    if (mFlags & 0x30)
        return mValue;
    return mTypeId != 0;
}
}

struct IStream;
IStream* __cdecl WriteBytes(IStream* s, const void* p, uint32_t n);   // 0x93a9a0 (operator<<)

// @ 0x00571f10
IStream* __cdecl WriteBool(IStream* s, bool b)
{
    b = (b != 0);
    return WriteBytes(s, &b, 1);
}

namespace EA { namespace IO {
uint32_t __cdecl WriteUint32(IStream* s, const uint32_t* p, uint32_t n, int endian);
} }

struct IStreamHolder {
    PV4 PV2
    virtual IStream* GetStream();     // +0x18
};
struct ISerializer {
    PV8
    virtual IStreamHolder* GetHolder();   // +0x20
};

inline uint32_t WriteUint32(IStream* st, uint32_t v) { return EA::IO::WriteUint32(st, &v, 1, 0); }

// @ 0x00571f40
ISerializer& __cdecl operator<<(ISerializer& s, const uint32_t& v)
{
    WriteUint32(s.GetHolder()->GetStream(), v);
    return s;
}

// ---------------------------------------------------------------------------
// Audio
// ---------------------------------------------------------------------------
namespace EA { namespace Audio {
struct SystemAT {
    PV8 PV4 PV2
    virtual void BeginMessage(uint32_t id);                 // +0x38
    virtual void SetFloat(uint32_t id, float v);            // +0x3c
    virtual void SetInt(uint32_t id, uint32_t v);           // +0x40
    virtual void pv41();
    virtual void pv42();
    virtual void SetString(uint32_t id, const char* s, uint32_t len);   // +0x4c
    virtual void pv44();
    virtual void pv45();
    virtual void SendMessage();                             // +0x58
};
SystemAT* __cdecl GetSystemAT();
} }

// @ 0x00571f80
void __cdecl Start3dSoundByName(uint32_t soundId, uint32_t objectId, float x, float y, float z)
{
    EA::Audio::SystemAT* sys = EA::Audio::GetSystemAT();
    if (sys) {
        sys->BeginMessage(0x3475365);
        sys->SetInt(0x3475381, soundId);
        sys->SetInt(0x3475385, objectId);
        sys->SetFloat(0x3475391, x);
        sys->SetFloat(0x3475395, y);
        sys->SetFloat(0x3475398, z);
        sys->SendMessage();
    }
}

// @ 0x00572020
void __cdecl PostSoundMessage(uint32_t objectId, uint32_t value)
{
    EA::Audio::SystemAT* sys = EA::Audio::GetSystemAT();
    if (sys) {
        sys->BeginMessage(0x347536b);
        sys->SetInt(0x3475385, objectId);
        sys->SetInt(0x34753a0, value);
        sys->SendMessage();
    }
}

// @ 0x00572070
void __cdecl SetSoundSymbol(uint32_t objectId, uint32_t symbolId, const char* value)
{
    EA::Audio::SystemAT* sys = EA::Audio::GetSystemAT();
    if (sys && value) {
        sys->BeginMessage(0x347537a);
        sys->SetInt(0x3475385, objectId);
        sys->SetInt(0x34753a7, symbolId);
        sys->SetString(0x34753b0, value, strlen(value) + 1);
        sys->SendMessage();
    }
}

// ---------------------------------------------------------------------------
// RenderWare global state
// ---------------------------------------------------------------------------
extern uint32_t g_renderStateDirty;   // rw::graphics::GlobalState::m_renderStateDirty[0]
extern uint32_t g_cullMode;           // 0x16f923c

// @ 0x005720f0
void __cdecl SetCullBackfaces(int enable)
{
    g_renderStateDirty |= 0x10000;
    g_cullMode = enable ? 4 : 8;
}

extern uint32_t g_value74, g_value78, g_value7c, g_value80, g_value84, g_value88;

// @ 0x00572110
uint32_t __cdecl LookupByHash(uint32_t hash)
{
    switch (hash) {
    case 0x3d97a8e4: return g_value74;
    case 0x2399be55: return g_value7c;
    case 0x24682294: return g_value80;
    case 0x476a98c7: return g_value84;
    case 0x438f6347: return g_value88;
    }
    return g_value78;
}

struct Vec4 { float x, y, z, w; };
extern Vec4 g_defaultColor;   // 0x15dac10

struct ColorSource {
    char pad0[0x48];
    Vec4 mColor;     // +0x48
    Vec4 GetDefaultColor() const;
    Vec4 GetColor() const;
};

// @ 0x00572160
Vec4 ColorSource::GetDefaultColor() const
{
    return g_defaultColor;
}

// @ 0x00572190
Vec4 ColorSource::GetColor() const
{
    return mColor;
}

// ---------------------------------------------------------------------------
// SP UI / editor
// ---------------------------------------------------------------------------
struct Rect16 { uint32_t d[4]; };
int __cdecl ClassifyRects(Rect16 a, Rect16 b);    // 0x4f3b40
uint32_t __cdecl RectResultToId(int r);           // 0x4f3c40

struct cUIManager {
    void Show(uint32_t id);                       // 0x67c830
    void SetMode(int a, int b);                   // 0x67c420
};
cUIManager* __cdecl UIManager();                  // 0x67cac0

// @ 0x005721b0
void __stdcall HandleRects(Rect16 a, Rect16 b)
{
    int r = ClassifyRects(a, b);
    if (r != 0x1c)
        UIManager()->Show(RectResultToId(r));
}

struct cItem { void Update(); };                  // 0x436060
struct cItemList {
    int GetCount();                               // 0x4accf0
    cItem* GetAt(int i);                          // 0x4accb0
};

// @ 0x00572220
void __stdcall UpdateAllItems(cItemList* list)
{
    if (list) {
        int i = 0;
        int n = list->GetCount();
        for (; i < n; ++i)
            list->GetAt(i)->Update();
    }
}

namespace SP {
struct cSporeGuide {
    char pad0[0x1c];
    bool mbActive;     // +0x1c
    void Show();       // 0x64ab20
};
struct cSPUIAssetBrowser {
    char pad0[0x1c];
    bool mbVisible;    // +0x1c
    bool CanSporepediaShowSporeGuide();
    void ShowSporeGuide();
    static void LaunchSporeGuide(uint32_t id);
};
struct IWindow;
struct IWindowManager {
    PV
    virtual IWindow* GetMainWindow();             // +0x04
    PV16 PV8 PV4 PV2 PV
    virtual int IsModal();                        // +0x84
};
struct IWindow {
    PV16 PV16 PV16 PV8 PV4 PV2 PV
    virtual bool IsVisible(int);                  // +0xfc
};
struct IMessageServer {
    PV4 PV
    virtual void PostMSG(uint32_t id, void* data, int flags);   // +0x14
};
struct IGameModes {
    PV2 PV
    virtual void Activate(uint32_t id);           // +0x0c
};
struct IGameModeManager {
    PV8 PV4 PV2
    virtual IGameModes* GetModes();               // +0x38
};
struct IApp {
    PV16 PV4
    virtual IGameModeManager* GetModeManager();   // +0x50
};
struct IFX {
    PV4 PV2 PV
    virtual void Fade(uint32_t id, float a, float b, int c);   // +0x1c
};
struct cCursor { void SetState(int); };         // 0x43ea40

cSporeGuide* SporeGuide();
cSPUIAssetBrowser* AssetBrowser();
IWindowManager* WindowManager();
IMessageServer* MessageServer();
IApp* App();
IFX* FXManager();                               // 0x401060

struct cAppModeEditorBase {
    char pad0[0x28];
    float mX;                    // +0x28
    float mY;                    // +0x2c
    char pad30[0x20e - 0x30];
    bool mbPlaySounds;           // +0x20e
    char pad20f[0x214 - 0x20f];
    uint32_t mTutorialPartMode;  // +0x214
    uint32_t mTutorialPlayMode;  // +0x218
    uint32_t mTutorialPaintMode; // +0x21c
    char pad220[0x260 - 0x220];
    uint64_t mRange1;            // +0x260
    uint64_t mRange2;            // +0x268
    uint64_t mRange0;            // +0x270
    char pad278[0x31c - 0x278];
    int mEditorMode;             // +0x31c
    char pad320[0x34c - 0x320];
    uint32_t mCurrentBlockRegion;   // +0x34c
    char pad350[0x385 - 0x350];
    bool mbCursorSet;            // +0x385
    char pad386[0x480 - 0x386];
    float mSavedX;               // +0x480
    float mSavedY;               // +0x484
    char pad488[0x4d4 - 0x488];
    bool mbFading;               // +0x4d4

    void ShowTutorial();
    void InitBrain(uint32_t region);
    void OnCursor(cCursor* c);
    void PostDone(void* data);
    void SetRanges(const uint64_t& r0, const uint64_t& r1, const uint64_t& r2);
    void StopFade();
};

namespace EditorUtils { void PlayEditorSound(uint32_t a, uint32_t b, float v, int c); }

// @ 0x00572260
void cAppModeEditorBase::ShowTutorial()
{
    if (SporeGuide()->mbActive) {
        SporeGuide()->Show();
        return;
    }
    if (AssetBrowser()->CanSporepediaShowSporeGuide()) {
        AssetBrowser()->ShowSporeGuide();
        return;
    }
    if (WindowManager()->IsModal())
        return;
    uint32_t id;
    switch (mEditorMode) {
    case 0: id = mTutorialPartMode; break;
    case 1: id = mTutorialPaintMode; break;
    case 2: id = mTutorialPlayMode; break;
    default: return;
    }
    if (id)
        cSPUIAssetBrowser::LaunchSporeGuide(id);
}

// @ 0x005722f0
void cAppModeEditorBase::InitBrain(uint32_t region)
{
    mCurrentBlockRegion = region;
    if (mbPlaySounds)
        EditorUtils::PlayEditorSound(0x1d6253c0, 0xac23893f, (float)region, 0);
}

// @ 0x00572330
void cAppModeEditorBase::OnCursor(cCursor* c)
{
    if (c) {
        c->SetState(0);
        mbCursorSet = true;
        if (mEditorMode == 0) {
            WindowManager();
            if (WindowManager()->GetMainWindow()->IsVisible(1)) {
                mSavedX = mX;
                mSavedY = mY;
                IFX* fx = FXManager();
                if (fx)
                    fx->Fade(0x1012, 1.0f, 0.2f, 1);
                mbFading = true;
            }
        }
    }
}

// @ 0x00572400
void __cdecl ActivateEditorMode()
{
    App()->GetModeManager()->GetModes()->Activate(0x6771a60);
}

// @ 0x00572430
void cAppModeEditorBase::PostDone(void* data)
{
    MessageServer()->PostMSG(0x73e46f6, data, 0);
}

// @ 0x00572450
void cAppModeEditorBase::SetRanges(const uint64_t& r0, const uint64_t& r1, const uint64_t& r2)
{
    mRange0 = r0;
    mRange1 = r1;
    mRange2 = r2;
}

// @ 0x005724a0
void cAppModeEditorBase::StopFade()
{
    if (mbFading) {
        IFX* fx = FXManager();
        if (fx)
            fx->Fade(0x1002, 0.0f, 0.0f, 1);
        mbFading = false;
    }
}

// @ 0x00572520
bool __cdecl IsSporepediaModal()
{
    if (WindowManager()->IsModal() && !AssetBrowser()->mbVisible)
        return true;
    return false;
}

struct cGameState { bool IsReady(); };       // 0x678ed0
cGameState* __cdecl GameState();             // 0x67caf0
}

// @ 0x00572550
void __cdecl ResetUIIfReady()
{
    if (SP::GameState()->IsReady())
        UIManager()->SetMode(1, 1);
}
