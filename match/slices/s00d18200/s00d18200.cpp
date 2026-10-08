// Slice s00d18200: SP::cGameEditInputStrategy::Init (0x00d18200, 1630 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as HandleMessage / ShowGameplayMarkerProperties).
//
// Level-editor input strategy start-up: loads the "LevelEditorUI" layout, stretches its root
// window over the screen and installs this object as its window procedure, registers the
// editor input commands, then binds every UI control the strategy uses (level/planet name
// edit boxes, load dialogs and their grids, the gameplay marker area, scrollbar and
// visibility box), sizes the scrollbar and finally hot-loads the level editor prop.
//
// Retail layout of cGameEditInputStrategy is the 2008 PDB's shifted by +4 from 0xa4 on.
#include "types.h"
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

// float->int with the current MXCSR rounding (asm helper in the original).
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

void operator delete(void* p);   // 0x00f47380 (operator delete[])
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);   // 0x00f473a0

namespace eastl {
extern char gEmptyString[];   // 0x01667bac

struct allocator {
    void* allocate(unsigned int n) {
        return operator new[](n, "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    void deallocate(void* p, unsigned int) { operator delete(p); }
};

template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    __forceinline basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    ~basic_string() { DeallocateSelf(); }

    void AllocateSelf() {
        mpBegin = (T*)gEmptyString;
        mpEnd = (T*)gEmptyString;
        mpCapacity = (T*)gEmptyString + 1;
    }
    T* DoAllocate(unsigned int n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
    // Out of line (0x00429760), but defined in this TU: cl sees that it only writes *this.
    __declspec(noinline) void AllocateSelf(unsigned int n) {
        if (n > 1) {
            mpBegin = DoAllocate(n);
            mpEnd = mpBegin;
            mpCapacity = mpBegin + n;
        } else
            AllocateSelf();
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void RangeInitialize(const T* pBegin);       // 0x00579a90 (zero-terminated)
    void RangeInitialize(const T* pBegin, const T* pEnd) {
        const unsigned int n = (unsigned int)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
        memcpy(pDestination, pSource, (unsigned int)(pSourceEnd - pSource) * sizeof(T));
        return pDestination + (pSourceEnd - pSource);
    }
    const T* c_str() const { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
typedef basic_string<wchar_t> string16;
}  // namespace eastl

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};

// ------------------------------------------------------------------ UTFWin
struct IObject {
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                       // +0x04
    PV
    virtual IObject* Cast(uint32_t typeID);                       // +0x0c
};

struct IWinProc;

struct IWindowManager {
    PV
    virtual struct IWindow* GetMainWindow();                      // +0x04
};

struct IWindow : IObject {
    virtual IWindow* GetParent();                                 // +0x10
    virtual IWindowManager* GetWindowManager();                   // +0x14
    PV4 PV2 PV                                                    // +0x18..+0x30
    virtual const Rectangle& GetArea();                           // +0x34
    virtual const Rectangle& GetRealArea();                       // +0x38
    PV8 PV                                                        // +0x3c..+0x5c
    virtual void SetArea(const Rectangle& area);                  // +0x60
    PV4 PV2                                                       // +0x64..+0x78
    virtual void SetFlag(int flag, bool value);                   // +0x7c
    PV16 PV16 PV                                                  // +0x80..+0x100
    virtual void AddWinProc(IWinProc* pWinProc);                  // +0x104
};

struct IWinTextEdit : IObject {
    PV4 PV4 PV4 PV4 PV4                                           // +0x10..+0x5c
    virtual int SetText(const wchar_t* pText, int arg);           // +0x60
};

struct IWinGrid : IObject {
    PV16 PV8 PV                                                   // +0x10..+0x70
    virtual void SetGridSize(int a, int b, int c);                // +0x74
    PV16 PV                                                       // +0x78..+0xb8
    virtual void SetCellSize(int a, int b);                       // +0xbc
};

struct IWinScrollbar : IObject {
    PV8 PV                                                         // +0x10..+0x30
    virtual void SetPageSize(int value, int arg);                 // +0x34
    PV
    virtual void SetMaxValue(int value, int arg);                 // +0x3c
};

struct IWinProc {
    PV
};

struct cSPUILayout {
    void Init(const wchar_t* pName, uint32_t typeID, int a, uint32_t instanceID);   // 0x00812160
    IWindow* FindWindowByID(uint32_t controlID, bool recursive);                    // 0x008105b0
};

struct IGameInputManager {
    PV16
    virtual void RegisterCommand(uint32_t commandID, const char* pName);            // +0x40
};
IGameInputManager* GameInputManager();                                              // 0x00b3d250

namespace SP {
struct cGameEditModeStrategy {
    static eastl::string16* GetLastLoadedScenario();                                // 0x00d1bee0
};
}

template <class T> inline T* object_cast(IObject* p, uint32_t typeID)
{
    return p ? (T*)p->Cast(typeID) : 0;
}

// ------------------------------------------------------------------ cGameEditInputStrategy
struct cInputStrategyBase {
    virtual void v00();
    uint32_t pad04[(0x3c - 4) / 4];
};
struct IMessageHandler {
    virtual void h00();
};
struct IRefCountBase {
    virtual void r00();
    int mRefCount;
};

class cGameEditInputStrategy : public cInputStrategyBase, public IMessageHandler, public IWinProc, public IRefCountBase {
public:
    uint32_t pad4c[(0x78 - 0x4c) / 4];
    AutoRefCount<IWinTextEdit> mLevelNameTextEdit;       // +0x78
    AutoRefCount<IWinTextEdit> mPlanetNameTextEdit;      // +0x7c
    AutoRefCount<IWindow> mLoadDialogWindow;             // +0x80
    AutoRefCount<IWindow> mLoadPlanetDialogWindow;       // +0x84
    AutoRefCount<IWinGrid> mGridFileList;                // +0x88
    AutoRefCount<IWinGrid> mPlanetGridFileList;          // +0x8c
    uint32_t pad90[(0xa4 - 0x90) / 4];
    AutoRefCount<IWindow> mGameplayMarkerRoot;           // +0xa4
    AutoRefCount<IWindow> mGameplayMarkerArea;           // +0xa8
    AutoRefCount<IWinScrollbar> mGameplayMarkerScrollbar;  // +0xac
    uint32_t padb0[(0xe0 - 0xb0) / 4];
    cSPUILayout mLayout;                                 // +0xe0

    void Init();
    void HotloadLevelEditorProp();                       // 0x00d160c0
};

// @ 0x00d18200
void cGameEditInputStrategy::Init()
{
    eastl::string16 layoutName;
    layoutName.RangeInitialize(L"LevelEditorUI");
    mLayout.Init(layoutName.c_str(), 0x40464100, 1, 0x5b598fa);

    AutoRefCount<IWindow> pRoot(mLayout.FindWindowByID(0x30170d2c, true));
    if (pRoot) {
        pRoot->SetArea(pRoot->GetWindowManager()->GetMainWindow()->GetArea());
        pRoot->AddWinProc(this);
        pRoot->SetFlag(1, true);
    }

    IGameInputManager* pInput = GameInputManager();
    pInput->RegisterCommand(0x137d8fe, "ManipulateObject");
    pInput->RegisterCommand(0x2afab18, "AddNoun");
    pInput->RegisterCommand(0x3a86a56, "AddTemplate");
    pInput->RegisterCommand(0x3a86a57, "AddRule");
    pInput->RegisterCommand(0x137c407, "DeleteObject");
    pInput->RegisterCommand(0xb2ba6adb, "Copy");
    pInput->RegisterCommand(0x12ba6ae8, "Paste");
    pInput->RegisterCommand(0x4f64c5d, "DrawPath");

    AutoRefCount<IObject> pTemp;
    pTemp = mLayout.FindWindowByID(0x1412d5c, true);
    mLevelNameTextEdit = object_cast<IWinTextEdit>(pTemp, 0xcf428691);

    eastl::string16* pScenario = SP::cGameEditModeStrategy::GetLastLoadedScenario();
    eastl::string16 scenarioName(*pScenario);
    if (scenarioName.size() != 0)
        mLevelNameTextEdit->SetText(scenarioName.c_str(), 0);

    pTemp = mLayout.FindWindowByID(0x15cc9fc, true);
    mPlanetNameTextEdit = object_cast<IWinTextEdit>(pTemp, 0xcf428691);

    mLoadDialogWindow = mLayout.FindWindowByID(0x14143aa, true);
    mLoadDialogWindow->SetFlag(1, false);

    mLoadPlanetDialogWindow = mLayout.FindWindowByID(0x147ccda, true);
    mLoadPlanetDialogWindow->SetFlag(1, false);

    pTemp = mLayout.FindWindowByID(0x14143c6, true);
    mGridFileList = object_cast<IWinGrid>(pTemp, 0xaf1ee902);
    mGridFileList->SetGridSize(1, 1, 0);
    mGridFileList->SetCellSize(1, 100);

    pTemp = mLayout.FindWindowByID(0x147cce4, true);
    mPlanetGridFileList = object_cast<IWinGrid>(pTemp, 0xaf1ee902);
    mPlanetGridFileList->SetGridSize(1, 1, 0);
    mPlanetGridFileList->SetCellSize(1, 100);

    mGameplayMarkerRoot = mLayout.FindWindowByID(0x36c3e68, true);
    mGameplayMarkerArea = mLayout.FindWindowByID(0x36c3e70, true);
    mGameplayMarkerArea->SetFlag(0x400, true);
    IWindow* pParent = mGameplayMarkerArea->GetParent();
    pParent->SetFlag(0x400, true);
    const Rectangle& area = pParent->GetRealArea();
    float height = area.y2 - area.y1;
    float width = area.x2 - area.x1;
    Rectangle bounds(0.0f, 0.0f, width, height);
    mGameplayMarkerArea->SetArea(bounds);

    mGameplayMarkerScrollbar = object_cast<IWinScrollbar>(mLayout.FindWindowByID(0x36c3e74, true), 0x2ef0c885);
    mGameplayMarkerScrollbar->SetPageSize(RoundToInt(area.y2 - area.y1), 1);
    mGameplayMarkerScrollbar->SetMaxValue(RoundToInt(area.y2 - area.y1), 1);

    HotloadLevelEditorProp();
}
