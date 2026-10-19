// src/game/SPEditors/SPEditorColorPicker.cpp -- migrated from slice(s) s005a51c0, s005a4250, s005a5ec0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorColorPicker.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPColorSwatch.h"
#include "SP/cSPEditorColorPicker.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cPropertyList.h"
#include "cSPColorRGB.h"
#include "cSPColorRGBA.h"
#include <string.h>
#include <math.h>
#include "EA/UTFWin/IWinProc.h"
#include "EA/Stopwatch.h"
#include "SP/cString.h"
#include "SP/cEditorResource.h"
#include <intrin.h>
#pragma intrinsic(sqrt)

// ---- items of slice s005a5ec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }
struct Property {
    char pad[0x12];
    unsigned short mType;      // +0x12: 1 = bool, 9 = int, 0xd = float
    int* GetInt();             // 0x0041E990
    uint32_t* GetUInt();
    float* GetFloat();         // 0x0041EA70
    bool* GetBool();           // 0x0041E920
};
namespace EA {
template <typename T>
class AutoRefCount_s005a_5ec0 {
public:
    T* mpObject;
    AutoRefCount_s005a_5ec0() : mpObject(0) {}
    AutoRefCount_s005a_5ec0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s005a_5ec0(const AutoRefCount_s005a_5ec0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s005a_5ec0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s005a_5ec0& operator=(T* p) { if (p != mpObject) { T* t = mpObject; if (p) p->AddRef(); mpObject = p; if (t) t->Release(); } return *this; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_5ec0 {
public:
    RefCountVTemplate_s005a_5ec0() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s005a_5ec0() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() { int n = (*(volatile int*)&mnRefCount += -1); if (n == 0) { mnRefCount = 1; delete this; return 0; } return mnRefCount; }
    T mnRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005a_5ec0 {
    public: virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
struct RectT_s005a_5ec0 { float left, top, right, bottom; RectT_s005a_5ec0() {} float Width() const { return right - left; } float Height() const { return bottom - top; } };
}
struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& result);
};
namespace eastl {
struct sp_vector_allocator_s005a_5ec0 {
    uint32_t mData[2];
    sp_vector_allocator_s005a_5ec0() {}
    void deallocate(void* p, size_t) { if (((uint32_t*)p)[-1]) operator delete[]((char*)p); }
};
}
namespace eastl {
template <typename T>
class sp_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s005a_5ec0 mAllocator;
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector();
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](unsigned int i) { return mpBegin[i]; }
    T* erase(T* first, T* last);
    void DoInsertSlow(T* pos, void* value);   // 0x006650C0 / 0x00Exxxx (out of line)
};
}
namespace eastl {
template <typename T>
__declspec(noinline) sp_vector<T>::~sp_vector() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
}
namespace eastl {
template <typename T>
__declspec(noinline) T* sp_vector<T>::erase(T* first, T* last) {
    memmove(first, last, (char*)mpEnd - (char*)last);
    mpEnd -= (last - first);
    return first;
}
}
struct cSPColorRGB_s005a_5ec0 { float r, g, b; cSPColorRGB_s005a_5ec0() {} cSPColorRGB_s005a_5ec0(const cSPColorRGB_s005a_5ec0& c) : r(c.r), g(c.g), b(c.b) {} };
struct IWindow {
    virtual int AddRef();   // slot 0 (+0x0)
    virtual int Release();   // slot 1 (+0x4)
    virtual void v2();   // slot 2 (+0x8)
    virtual void v3();   // slot 3 (+0xc)
    virtual IWindow* GetParent();   // slot 4 (+0x10)
    virtual void v5();   // slot 5 (+0x14)
    virtual void v6();   // slot 6 (+0x18)
    virtual void v7();   // slot 7 (+0x1c)
    virtual void v8();   // slot 8 (+0x20)
    virtual void v9();   // slot 9 (+0x24)
    virtual void v10();   // slot 10 (+0x28)
    virtual void v11();   // slot 11 (+0x2c)
    virtual void v12();   // slot 12 (+0x30)
    virtual const EA::RectT_s005a_5ec0* GetArea();   // slot 13 (+0x34)
    virtual const EA::RectT_s005a_5ec0* GetRealArea();   // slot 14 (+0x38)
    virtual void v15();   // slot 15 (+0x3c)
    virtual void v16();   // slot 16 (+0x40)
    virtual void v17();   // slot 17 (+0x44)
    virtual void v18();   // slot 18 (+0x48)
    virtual void v19();   // slot 19 (+0x4c)
    virtual void v20();   // slot 20 (+0x50)
    virtual void v21();   // slot 21 (+0x54)
    virtual void v22();   // slot 22 (+0x58)
    virtual void SetFillColor(uint32_t c);   // slot 23 (+0x5c)
    virtual void v24();   // slot 24 (+0x60)
    virtual void v25();   // slot 25 (+0x64)
    virtual void v26();   // slot 26 (+0x68)
    virtual void v27();   // slot 27 (+0x6c)
    virtual void v28();   // slot 28 (+0x70)
    virtual void v29();   // slot 29 (+0x74)
    virtual void v30();   // slot 30 (+0x78)
    virtual void SetFlag(int flag, int enable);   // slot 31 (+0x7c)
    virtual void v32();   // slot 32 (+0x80)
    virtual void v33();   // slot 33 (+0x84)
    virtual void v34();   // slot 34 (+0x88)
    virtual void v35();   // slot 35 (+0x8c)
    virtual void v36();   // slot 36 (+0x90)
    virtual void v37();   // slot 37 (+0x94)
    virtual void v38();   // slot 38 (+0x98)
    virtual void v39();   // slot 39 (+0x9c)
    virtual void v40();   // slot 40 (+0xa0)
    virtual void v41();   // slot 41 (+0xa4)
    virtual void v42();   // slot 42 (+0xa8)
    virtual void SetShadeColor(uint32_t c);   // slot 43 (+0xac)
    virtual void v44();   // slot 44 (+0xb0)
    virtual void v45();   // slot 45 (+0xb4)
    virtual void v46();   // slot 46 (+0xb8)
    virtual void v47();   // slot 47 (+0xbc)
    virtual void v48();   // slot 48 (+0xc0)
    virtual void v49();   // slot 49 (+0xc4)
    virtual void v50();   // slot 50 (+0xc8)
    virtual void v51();   // slot 51 (+0xcc)
    virtual void v52();   // slot 52 (+0xd0)
    virtual void v53();   // slot 53 (+0xd4)
    virtual void v54();   // slot 54 (+0xd8)
    virtual void v55();   // slot 55 (+0xdc)
    virtual void v56();   // slot 56 (+0xe0)
    virtual void v57();   // slot 57 (+0xe4)
    virtual void AddWindow(IWindow* w);   // slot 58 (+0xe8)
    virtual void v59();   // slot 59 (+0xec)
    virtual void v60();   // slot 60 (+0xf0)
    virtual void v61();   // slot 61 (+0xf4)
    virtual void v62();   // slot 62 (+0xf8)
    virtual void v63();   // slot 63 (+0xfc)
    virtual void v64();   // slot 64 (+0x100)
    virtual void AddWinProc(void* proc);   // slot 65 (+0x104)
};
struct OwnerObject {                         // swatch owner (AutoRefCount<IUnknown32>)
    virtual int AddRef();
    virtual int Release();
    virtual void* v2();
    virtual void* Cast(uint32_t typeId);     // slot 3 (+0xC)
};
extern cSPColorRGB_s005a_5ec0 gWhiteColor;               // 0x0150F470 {1,1,1}
cSPColorRGB_s005a_5ec0* __cdecl HSLToRGB(cSPColorRGB_s005a_5ec0* out, float h, float s, float l);   // 0x0067FE30
bool __cdecl GetPropertyArray(cPropertyList* list, uint32_t id, int* pCount, cSPColorRGB_s005a_5ec0** pData); // 0x006A0A70
struct PropertyManager {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList** out);  // slot 11 (+0x2C)
};
PropertyManager* __cdecl GetPropertyManager();             // 0x0067DE30
class cSPColorSwatch;
typedef eastl::sp_vector<cSPColorRGB_s005a_5ec0> ColorVector;
struct SwatchRefVector {                       // vector<AutoRefCount<cSPColorSwatch>, sp_vector_allocator>
    cSPColorSwatch** mpBegin;
    cSPColorSwatch** mpEnd;
    cSPColorSwatch** mpCapacity;
    eastl::sp_vector_allocator_s005a_5ec0 mAllocator;
    void erase(cSPColorSwatch** first, cSPColorSwatch** last); // 0x00E25BD0
    void DoInsertSlow(cSPColorSwatch** pos, void* value);                       // 0x006650C0
};
class cSPEditorColorPicker;
class cSPColorSwatch {
public:
    virtual int AddRef();                      // slot 0
    virtual int Release();                     // slot 1
    uint32_t pad4;
    int mnRefCount;                            // +8
    bool mRespondToInput;                      // +0xc
    bool mRolledOver;                          // +0xd
    bool mMouseDown;                           // +0xe
    bool mExpanded;                            // +0xf
    bool mBecomingOwner;                       // +0x10
    bool mCustomColor;                         // +0x11
    bool mIsDefaultColor;                      // +0x12
    char pad13;
    float mRollOverTimer;                      // +0x14
    float mFadeTimer;                          // +0x18
    float mMouseDownTimer;                     // +0x1c
    float mSelectedTimer;                      // +0x20
    cSPColorRGB_s005a_5ec0 mBaseColor;                    // +0x24
    cSPColorRGB_s005a_5ec0 mDisplayColor;                 // +0x30
    EA::RectT_s005a_5ec0 mOriginalArea;                   // +0x3c
    EA::AutoRefCount_s005a_5ec0<IWindow> mWinFrame;       // +0x4c
    EA::AutoRefCount_s005a_5ec0<IWindow> mWinFrameGlow;   // +0x50
    EA::AutoRefCount_s005a_5ec0<IWindow> mWinShine;       // +0x54
    EA::AutoRefCount_s005a_5ec0<IWindow> mWinColor;       // +0x58
    EA::AutoRefCount_s005a_5ec0<IWindow> mWinRoot;        // +0x5c
    EA::AutoRefCount_s005a_5ec0<IWindow> mWinExpansion;   // +0x60
    EA::AutoRefCount_s005a_5ec0<OwnerObject> mOwner;      // +0x64
    SwatchRefVector mExpansionSwatches;        // +0x68
    EA::AutoRefCount_s005a_5ec0<cPropertyList> mColorPickerConfig;  // +0x7c
    char mTimerDoubleClick[0x18];              // +0x80
    unsigned int mCurrMouseDownTime;           // +0x98
    unsigned int mLastMouseDownTime;           // +0x9c
    unsigned int mSwatchIndex;                 // +0xa0
    unsigned int mExpansionIndex;              // +0xa4

    cSPColorSwatch();                          // 0x005a5000
    void Cleanup();                            // 0x005a5db0
    void Init(cPropertyList* config, cSPColorRGB_s005a_5ec0 color, EA::RectT_s005a_5ec0 area, IWindow* root,
              void* owner);     // 0x005a51c0
    void SetArea(EA::RectT_s005a_5ec0 area, int flag);    // 0x005a4500
    void SetExpansionArea(int flag);           // 0x005a4990
    void AddTooltip(uint32_t id);              // 0x005a4680
    cSPColorRGB_s005a_5ec0 GetExpansionColor(cSPColorRGB_s005a_5ec0 base, int i, int j);   // 0x005a4250
    void Update(int deltaTime, bool selected); // 0x005a63d0
};
class cSPEditorColorPicker : public EA::RefCountVTemplate_s005a_5ec0<int>, public EA::COM::IUnknown32_s005a_5ec0 {
public:
    EA::AutoRefCount_s005a_5ec0<cSPColorSwatch> mSelectedSwatch;  // +0xc
    IWindow* mWinRoot;          // +0x10
    float mRootWidth;           // +0x14
    float mRootHeight;          // +0x18
    cSPColorRGB_s005a_5ec0 mSelectedColor; // +0x1c
    int mCustomSwatchIndex;     // +0x28
    int mDefaultSwatchIndex;    // +0x2c
    eastl::sp_vector<cSPColorSwatch*> mSwatches;  // +0x30
    int mNumColors;             // +0x44
    EA::AutoRefCount_s005a_5ec0<cPropertyList> mColorPickerConfig;  // +0x48
    int mUserData;              // +0x4c

    bool Init(IWindow* winRoot, uint32_t configId, int userData, const ColorVector* colors); // 0x005a5ec0
    void Clear();                      // 0x005a6390
    void Update(int deltaTime);        // 0x005a6db0
    EA::RectT_s005a_5ec0 GetSwatchArea(int index, int flag);   // 0x005a4750
};
static inline void PushSwatch(eastl::sp_vector<cSPColorSwatch*>& v, cSPColorSwatch* sw,
                              EA::AutoRefCount_s005a_5ec0<cSPColorSwatch>& ref)
{
    cSPColorSwatch** pos = v.mpEnd;
    if (pos < v.mpCapacity) {
        v.mpEnd = pos + 1;
        if (pos) {
            *pos = sw;
            sw->AddRef();
        }
    } else {
        v.DoInsertSlow(pos, &ref);
    }
}
// ---- items of slice s005a5ec0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cSPColorRGB_s005a_5ec0 gWhiteColor;               // 0x0150F470 {1,1,1}

// ---- items of slice s005a4250 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Property_s005a_4250 {
    char pad[0x10];
    uint32_t mFlags;             // +0x10
    unsigned short mType;        // +0x12
    int* GetInt();               // 0x0041e990
    uint32_t* GetUInt();         // 0x0041ea00
    float* GetFloat();           // 0x0041ea70
    bool* GetBool();             // 0x0041e920
};
namespace EA {
template <typename T>
class AutoRefCount_s005a_4250 {
public:
    T* mpObject;
    AutoRefCount_s005a_4250() : mpObject(0) {}
    AutoRefCount_s005a_4250(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s005a_4250(const AutoRefCount_s005a_4250& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s005a_4250() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s005a_4250& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount_s005a_4250& operator=(const AutoRefCount_s005a_4250& x) { return operator=(x.mpObject); }
    T*& AsOutParam() {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_4250 {
public:
    RefCountVTemplate_s005a_4250() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s005a_4250() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) { mnRefCount = 1; delete this; return 0; }
        return mnRefCount;
    }
    T mnRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005a_4250 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};  // namespace COM
}
}
namespace EA {
struct RectT_s005a_4250 {
    float left, top, right, bottom;
    RectT_s005a_4250() {}
    RectT_s005a_4250(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
    float Width() const { return right - left; }
    float Height() const { return bottom - top; }
};
}
namespace EA {
struct Point { float x, y; };
}
namespace EA {
class Stopwatch_s005a_4250 {
public:
    Stopwatch_s005a_4250(int, int);
    char pad[0x18];
};
}
namespace EA {
namespace UTFWin {
class IWindow_s005a_4250 {
public:
    virtual int AddRef();                         // +0x00
    virtual int Release();                        // +0x04
    PV(2) PV(3)
    virtual IWindow_s005a_4250* GetParent();                 // +0x10
    PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual uint32_t GetFlags();                  // +0x28
    PV(11) PV(12)
    virtual const EA::RectT_s005a_4250& GetRealArea();       // +0x34
    virtual const EA::RectT_s005a_4250& GetArea();           // +0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual void pv23(uint32_t color);            // +0x5c
    virtual void SetArea(EA::RectT_s005a_4250 area);         // +0x60
    PV(25) PV(26)
    virtual void pv27(const EA::RectT_s005a_4250* area);     // +0x6c
    PV(28) PV(29) PV(30)
    virtual void SetFlag(int flag, bool value);   // +0x7c
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
    virtual EA::Point ToClient(float, float);     // +0xc0
    virtual EA::Point ToScreen(float, float);     // +0xc4
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
    PV(60) PV(61) PV(62) PV(63) PV(64)
    virtual void pv65(void*);                     // +0x104
    virtual void pv66(void*);                     // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005a_4250 : public EA::COM::IUnknown32_s005a_4250 {
public:
    virtual ~IWinProc_s005a_4250() {}
};
}
}
using EA::UTFWin::IWindow_s005a_4250;
namespace eastl {
struct sp_vector_allocator_s005a_4250 {
    uint32_t mData[2];
    sp_vector_allocator_s005a_4250() {}
    void deallocate(void* p, size_t) { if (((uint32_t*)p)[-1]) operator delete[]((char*)p); }
};
}
namespace eastl {
template <typename T>
class sp_vector_s005a_4250 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s005a_4250 mAllocator;
    sp_vector_s005a_4250() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector_s005a_4250();
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](unsigned int i) { return mpBegin[i]; }
};
}
namespace eastl {
template <typename T>
__declspec(noinline) sp_vector_s005a_4250<T>::~sp_vector_s005a_4250() {
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
}
struct cPropertyList_s005a_4250 {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property_s005a_4250*& result);  // +0x24
};
namespace SP {
struct cSPColorRGB_s005a_4250 {
    float r, g, b;
    cSPColorRGB_s005a_4250() {}
    cSPColorRGB_s005a_4250(const cSPColorRGB_s005a_4250& c) : r(c.r), g(c.g), b(c.b) {}
    bool operator!=(const cSPColorRGB_s005a_4250& c) const { return r != c.r || g != c.g || b != c.b; }
};
}
namespace SP {
extern cSPColorRGB_s005a_4250 gDefaultPaintColor;  // 0x0150f470 (12 bytes)
}
using SP::cSPColorRGB_s005a_4250;
class cSPColorSwatch_s005a_4250 : public EA::UTFWin::IWinProc_s005a_4250, public EA::RefCountVTemplate_s005a_4250<int> {
public:
    bool mRespondToInput;   // +0xc
    bool mRolledOver;       // +0xd
    bool mMouseDown;        // +0xe
    bool mExpanded;         // +0xf
    bool mBecomingOwner;    // +0x10
    bool mCustomColor;      // +0x11
    bool mIsDefaultColor;   // +0x12
    char pad13[1];
    float mRollOverTimer;   // +0x14
    float mFadeTimer;       // +0x18
    float mMouseDownTimer;  // +0x1c
    float mSelectedTimer;   // +0x20
    cSPColorRGB_s005a_4250 mBaseColor;     // +0x24
    cSPColorRGB_s005a_4250 mDisplayColor;  // +0x30
    EA::RectT_s005a_4250 mOriginalArea;    // +0x3c
    EA::AutoRefCount_s005a_4250<IWindow_s005a_4250> mWinFrame;      // +0x4c
    EA::AutoRefCount_s005a_4250<IWindow_s005a_4250> mWinFrameGlow;  // +0x50
    EA::AutoRefCount_s005a_4250<IWindow_s005a_4250> mWinShine;      // +0x54
    EA::AutoRefCount_s005a_4250<IWindow_s005a_4250> mWinColor;      // +0x58
    EA::AutoRefCount_s005a_4250<IWindow_s005a_4250> mWinRoot;       // +0x5c
    EA::AutoRefCount_s005a_4250<IWindow_s005a_4250> mWinExpansion;  // +0x60
    EA::AutoRefCount_s005a_4250<EA::COM::IUnknown32_s005a_4250> mOwner;  // +0x64
    eastl::sp_vector_s005a_4250<EA::AutoRefCount_s005a_4250<cSPColorSwatch_s005a_4250> > mExpansionSwatches;  // +0x68
    EA::AutoRefCount_s005a_4250<cPropertyList_s005a_4250> mColorPickerConfig;  // +0x7c
    EA::Stopwatch_s005a_4250 mTimerDoubleClick;  // +0x80
    uint32_t mCurrMouseDownTime;      // +0x98
    uint32_t mLastMouseDownTime;      // +0x9c
    uint32_t mSwatchIndex;            // +0xa0
    uint32_t mExpansionIndex;         // +0xa4

    virtual int AddRef() { return EA::RefCountVTemplate_s005a_4250<int>::AddRef(); }
    virtual int Release() { return EA::RefCountVTemplate_s005a_4250<int>::Release(); }
    cSPColorSwatch_s005a_4250();
    ~cSPColorSwatch_s005a_4250();

    void SetArea(EA::RectT_s005a_4250 area, bool bStoreOriginal);   // 0x005a4500
    void SetColor(const cSPColorRGB_s005a_4250& color);             // 0x005a45d0
    void CollapseExpansion();                            // 0x005a4630
    void AddTooltip(uint32_t id);                        // 0x005a4680
    void SetExpansionArea(bool b);                       // 0x005a4990
    void Init(cPropertyList_s005a_4250* config, float r, float g, float b,
              float l, float t, float rr, float bb, uint32_t index,
              EA::COM::IUnknown32_s005a_4250* owner);
    void MainColorSelected();                            // 0x005a5960
    void SetSelectedColor(EA::COM::IUnknown32_s005a_4250* param);   // 0x005a4b80 (guessed)
    void GetExpansionColor(float* out, float a, float b, float c, int d, int e);  // 0x005a4250 (cSPColorSwatch::GetExpansionColor)
    void SubSelect(uint32_t param);                      // 0x005a5ae0
};
uint32_t ColorRGBToU32(const cSPColorRGB_s005a_4250* c);  // 0x00458a40
class cSPEditorColorPicker_s005a_4250 : public EA::RefCountVTemplate_s005a_4250<int>, public EA::COM::IUnknown32_s005a_4250 {
public:
    EA::AutoRefCount_s005a_4250<cSPColorSwatch_s005a_4250> mSelectedSwatch;  // +0xc
    IWindow_s005a_4250* mWinRoot;          // +0x10
    float mRootWidth;           // +0x14
    float mRootHeight;          // +0x18
    cSPColorRGB_s005a_4250 mSelectedColor; // +0x1c
    int mUnknown28;             // +0x28
    int mSelectedIndex;         // +0x2c
    eastl::sp_vector_s005a_4250<cSPColorSwatch_s005a_4250*> mSwatches;  // +0x30
    int mNumColors;             // +0x44
    EA::AutoRefCount_s005a_4250<cPropertyList_s005a_4250> mColorPickerConfig;  // +0x48

    void GetSwatchArea(cSPColorRGB_s005a_4250* out, int index, int unused);  // 0x005a4750
    void SetArea(EA::RectT_s005a_4250 area);                                 // 0x005a4800
    void SetPaletteColor(const cSPColorRGB_s005a_4250& color);               // 0x005a4920
    void SetColor(const cSPColorRGB_s005a_4250& color);                      // 0x005a4e20
    void SetDefault();                                            // 0x005a4fb0
    void SetSwatchIndex(int index);                               // 0x005a4fb0 alt
};
// ---- items of slice s005a4250 end

// ---- items of slice s005a51c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  operator delete[](void* p);
struct Property_s005a_51c0 {
    char pad[0x10];
    uint32_t mFlags;             // +0x10
    unsigned short mType;        // +0x12
    int* GetInt();               // 0x0041e990
    uint32_t* GetUInt();         // 0x0041ea00
    float* GetFloat();           // 0x0041ea70
    bool* GetBool();             // 0x0041e920
};
union LARGE_INTEGER_ { struct { unsigned long LowPart; long HighPart; }; __int64 QuadPart; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER_*);
struct IDrawable_s005a_51c0;
namespace EA {
template <typename T>
class AutoRefCount_s005a_51c0 {
public:
    T* mpObject;
    AutoRefCount_s005a_51c0() : mpObject(0) {}
    AutoRefCount_s005a_51c0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s005a_51c0(const AutoRefCount_s005a_51c0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s005a_51c0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s005a_51c0& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount_s005a_51c0& operator=(const AutoRefCount_s005a_51c0& x) { return operator=(x.mpObject); }
    T*& AsOutParam() {
        if (mpObject) { T* const p = mpObject; mpObject = 0; p->Release(); }
        return mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class AutoRefCountOOL : public AutoRefCount_s005a_51c0<T> {
public:
    __declspec(noinline) AutoRefCountOOL& operator=(T* pObject);
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_51c0 {
public:
    RefCountVTemplate_s005a_51c0() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s005a_51c0() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) { mnRefCount = 1; delete this; return 0; }
        return mnRefCount;
    }
    T mnRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005a_51c0 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
struct RectT_s005a_51c0 {
    float left, top, right, bottom;
    RectT_s005a_51c0() {}
    RectT_s005a_51c0(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
    float Width() const { return right - left; }
    float Height() const { return bottom - top; }
};
}
namespace EA {
class Stopwatch_s005a_51c0 {
public:
    Stopwatch_s005a_51c0(int, int);
    uint32_t GetElapsedTime();  // 0x0093a5e0 (EA::Stopwatch::GetElapsedTime)
    void Start() {
        if (mStartTime == 0) {
            if (mUnits == 1) {
                mStartTime = __rdtsc();
            } else {
                LARGE_INTEGER_ t;
                QueryPerformanceCounter(&t);
                mStartTime = t.QuadPart;
            }
        }
    }
    unsigned __int64 mStartTime;   // +0x00
    uint32_t pad8[2];
    uint32_t mUnits;               // +0x10
    uint32_t pad14;
};
}
namespace EA {
namespace UTFWin {
class IWindow_s005a_51c0 {
public:
    virtual int AddRef();                         // +0x00
    virtual int Release();                        // +0x04
    PV(2) PV(3)
    virtual IWindow_s005a_51c0* GetParent();                 // +0x10
    PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual uint32_t GetFlags();                  // +0x28
    PV(11) PV(12)
    virtual const EA::RectT_s005a_51c0& GetRealArea();       // +0x34
    virtual const EA::RectT_s005a_51c0& GetArea();           // +0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual void pv23(uint32_t color);            // +0x5c
    virtual void SetArea(EA::RectT_s005a_51c0 area);         // +0x60
    PV(25) PV(26)
    virtual void pv27(const EA::RectT_s005a_51c0* area);     // +0x6c
    PV(28) PV(29) PV(30)
    virtual void SetFlag(int flag, bool value);   // +0x7c
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41)
    virtual ::IDrawable_s005a_51c0* GetDrawable();           // +0xa8
    virtual void SetFillColor(uint32_t color);    // +0xac
    PV(44) PV(45) PV(46) PV(47)
    virtual EA::Point ToClient(float, float);     // +0xc0
    virtual EA::Point ToScreen(float, float);     // +0xc4
    PV(50) PV(51) PV(52) PV(53)
    virtual void AddWindow(IWindow_s005a_51c0*);             // +0xd8
    PV(55) PV(56) PV(57)
    virtual void pv58(void*);                     // +0xe8
    PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
    virtual void AddWinProc(struct IWinProc_s005a_51c0*);    // +0x104
    virtual void pv66(void*);                     // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005a_51c0 : public EA::COM::IUnknown32_s005a_51c0 {
public:
    virtual ~IWinProc_s005a_51c0() {}
};
}
}
using EA::UTFWin::IWindow_s005a_51c0;
using EA::UTFWin::IWinProc_s005a_51c0;
struct IDrawableCast {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual void SetMode(int mode);               // +0x28
};
struct IDrawable_s005a_51c0 {
    virtual int AddRef();
    virtual int Release();
    PV(2)
    virtual IDrawableCast* Cast(uint32_t id);     // +0x0c
};
struct Key3 {
    uint32_t mInstance, mType, mGroup;
    Key3() {}
    Key3(uint32_t instance, uint32_t type, uint32_t group) { mType = type; mGroup = group; mInstance = instance; }
};
struct Pt2 { float x, y; Pt2(float a, float b) : x(a), y(b) {} };
namespace SPUIHelpers {
IWindow_s005a_51c0* CreateImageWindow(const Key3& image, Pt2 pos, IWindow_s005a_51c0* parent);   // 0x00807880 (cdecl)
}
struct cPropertyList_s005a_51c0;
bool GetPropertyAsKeyInstance(const cPropertyList_s005a_51c0* list, uint32_t id, uint32_t* out);   // 0x006a12a0 (cdecl)
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(unsigned size, unsigned align, const char* name, void* alloc);
struct WindowRaw { WindowRaw* Ctor(); };            // 0x00962a10 EA::UTFWin::Window::Window
struct LayoutMgr { IWindow_s005a_51c0* GetWorldMainWindow(); };   // 0x00810620
LayoutMgr* __stdcall GetLayoutManager(unsigned id);   // 0x00805070
struct EffectSub {
    PV(0) PV(1) PV(2) PV(3)
    virtual IWinProc_s005a_51c0* GetWinProc();               // +0x10
    PV(5)
    virtual void SetDuration(float);              // +0x18
    PV(7)
    virtual void SetFlagA(bool);                  // +0x20
    PV(9)
    virtual void SetRange(float, float);          // +0x28
    PV(11)
    virtual void SetFlagB(bool);                  // +0x30
};
struct InflateEffect {
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[1];
    EffectSub mCtl;                               // +0x0c
    uint32_t pad2[(0x60 - 0x10) / 4];
    EffectSub mCtl2;                              // +0x60
    InflateEffect* Ctor();                        // 0x0097e690
};
struct FadeEffect {
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[1];
    EffectSub mCtl;                               // +0x0c
    FadeEffect* Ctor();                           // 0x0096f060
};
struct UnkCast { virtual int AddRef(); virtual int Release(); PV(2) virtual void* Cast(uint32_t id); };
namespace eastl {
struct sp_vector_allocator_s005a_51c0 {
    uint32_t mData[2];
    sp_vector_allocator_s005a_51c0() {}
    void deallocate(void* p, size_t) { if (((uint32_t*)p)[-1]) operator delete[]((char*)p); }
};
}
namespace eastl {
template <typename T>
class sp_vector_s005a_51c0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s005a_51c0 mAllocator;
    sp_vector_s005a_51c0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector_s005a_51c0();
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](unsigned int i) { return mpBegin[i]; }
};
}
namespace eastl {
template <typename T>
__declspec(noinline) sp_vector_s005a_51c0<T>::~sp_vector_s005a_51c0() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
}
struct cPropertyList_s005a_51c0 {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property_s005a_51c0*& result);  // +0x24
};
namespace SP {
struct cSPColorRGB_s005a_51c0 {
    float r, g, b;
    cSPColorRGB_s005a_51c0() {}
    cSPColorRGB_s005a_51c0(const cSPColorRGB_s005a_51c0& c) : r(c.r), g(c.g), b(c.b) {}
    bool operator!=(const cSPColorRGB_s005a_51c0& c) const { return r != c.r || g != c.g || b != c.b; }
};
}
namespace SP {
extern cSPColorRGB_s005a_51c0 gDefaultPaintColor_s005a_51c0;  // 0x0150f470
}
using SP::cSPColorRGB_s005a_51c0;
struct ColorPOD { float r, g, b; };
uint32_t ColorRGBToU32(const cSPColorRGB_s005a_51c0* c);  // 0x00458a40
class cSPColorSwatch_s005a_51c0 : public EA::UTFWin::IWinProc_s005a_51c0, public EA::RefCountVTemplate_s005a_51c0<int> {
public:
    bool mRespondToInput;   // +0xc
    bool mRolledOver;       // +0xd
    bool mMouseDown;        // +0xe
    bool mExpanded;         // +0xf
    bool mBecomingOwner;    // +0x10
    bool mCustomColor;      // +0x11
    bool mIsDefaultColor;   // +0x12
    char pad13[1];
    float mRollOverTimer;   // +0x14
    float mFadeTimer;       // +0x18
    float mMouseDownTimer;  // +0x1c
    float mSelectedTimer;   // +0x20
    ColorPOD mBaseColor;     // +0x24
    ColorPOD mDisplayColor;  // +0x30
    EA::RectT_s005a_51c0 mOriginalArea;    // +0x3c
    EA::AutoRefCount_s005a_51c0<IWindow_s005a_51c0> mWinFrame;      // +0x4c
    EA::AutoRefCount_s005a_51c0<IWindow_s005a_51c0> mWinFrameGlow;  // +0x50
    EA::AutoRefCount_s005a_51c0<IWindow_s005a_51c0> mWinShine;      // +0x54
    EA::AutoRefCount_s005a_51c0<IWindow_s005a_51c0> mWinColor;      // +0x58
    EA::AutoRefCount_s005a_51c0<IWindow_s005a_51c0> mWinRoot;       // +0x5c
    EA::AutoRefCountOOL<IWindow_s005a_51c0> mWinExpansion;  // +0x60
    EA::AutoRefCount_s005a_51c0<EA::COM::IUnknown32_s005a_51c0> mOwner;  // +0x64
    eastl::sp_vector_s005a_51c0<EA::AutoRefCount_s005a_51c0<cSPColorSwatch_s005a_51c0> > mExpansionSwatches;  // +0x68
    EA::AutoRefCount_s005a_51c0<cPropertyList_s005a_51c0> mColorPickerConfig;  // +0x7c
    EA::Stopwatch_s005a_51c0 mTimerDoubleClick;  // +0x80
    uint32_t mCurrMouseDownTime;      // +0x98
    uint32_t mLastMouseDownTime;      // +0x9c
    uint32_t mSwatchIndex;            // +0xa0
    uint32_t mExpansionIndex;         // +0xa4

    virtual int AddRef() { return EA::RefCountVTemplate_s005a_51c0<int>::AddRef(); }
    virtual int Release() { return EA::RefCountVTemplate_s005a_51c0<int>::Release(); }

    void SetColor(const ColorPOD& color);        // 0x005a45d0
    void CollapseExpansion();                       // 0x005a4630
    void SetExpansionArea(bool b);                  // 0x005a4990
    void SetSelectedColor(void* param);             // 0x005a4b80
    __declspec(noinline) void MainColorSelected();  // 0x005a5960
    void SetFromSwatch(cSPColorSwatch_s005a_51c0* other);      // 0x005a5ae0
    int  DoMessage(uint32_t wParam, void* message); // 0x005a5b70
    void Cleanup();                                 // 0x005a5db0
    void SetArea(EA::RectT_s005a_51c0 area, bool b);          // 0x005a4500
    void Init(cPropertyList_s005a_51c0* config, ColorPOD color,
              float l, float t, float rr, float bb,
              IWindow_s005a_51c0* parent, EA::COM::IUnknown32_s005a_51c0* owner);
};
namespace SP {
class cContentValidationSummarizer {
public:
    virtual int v0();
    virtual int v1();
};
}
namespace SP {
class cEditorResource_s005a_51c0 : public cContentValidationSummarizer {
public:
    cEditorResource_s005a_51c0() : mField4(0) {}
    virtual int v0();
    virtual int v1();
    int mField4;   // +0x4
};
}
class cXBase { public: virtual int v0(); };
class cX : public SP::cEditorResource_s005a_51c0, public cXBase {
public:
    EA::AutoRefCount_s005a_51c0<EA::COM::IUnknown32_s005a_51c0> mPtrC;  // +0xc
    void* mPtr10;     // +0x10
    float mFloat14;   // +0x14
    float mFloat18;   // +0x18
    cSPColorRGB_s005a_51c0 mColor1c;  // +0x1c
    uint32_t mInt28;  // +0x28
    uint32_t mInt2c;  // +0x2c
    eastl::sp_vector_s005a_51c0<void*> mVec30;  // +0x30
    void* mPtr44;     // +0x44
    EA::AutoRefCount_s005a_51c0<EA::COM::IUnknown32_s005a_51c0> mPtr48;  // +0x48
    void* mPtr4c;     // +0x4c
    cX();
    virtual ~cX();
};
// ---- items of slice s005a51c0 end

// @ 0x005a4250
void cSPColorSwatch_s005a_4250::GetExpansionColor(float* out, float a, float b, float c, int d, int e)
{
    int num = 5;
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        if (mColorPickerConfig->GetProperty(0xd29675eb, prop) && prop->mType == 9) {
            int* p = prop->GetInt();
            num = *p;
        }
    }
    float col2 = 0.0f, col3 = 0.0f, col4 = 0.0f;
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        if (mColorPickerConfig->GetProperty(0x92fa6b4b, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            col2 = *p;
        }
    }
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        if (mColorPickerConfig->GetProperty(0xd29675ee, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            col3 = *p;
        }
    }
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        if (mColorPickerConfig->GetProperty(0xb2fa6d7b, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            col4 = *p;
        }
    }
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        if (mColorPickerConfig->GetProperty(0xd29675ed, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            /* stored to 0x1c slot; unused below */
            (void)p;
        }
    }
    if (a == b && a == c && b == c) {
        float t = (float)(num * d + e) / (float)(num * num - 1);
        out[0] = t;
        out[1] = t;
        out[2] = t;
        return;
    }
    (void)col2; (void)col3; (void)col4;
    out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f;
}

// @ 0x005a4500
void cSPColorSwatch_s005a_4250::SetArea(EA::RectT_s005a_4250 area, bool bStoreOriginal)
{
    if (!mWinRoot)
        return;
    if (bStoreOriginal)
        mOriginalArea = area;
    EA::RectT_s005a_4250 child;
    child.left = 0.0f;
    child.top = 0.0f;
    child.right = area.Width();
    child.bottom = area.Height();
    mWinRoot->SetArea(area);
    if (mWinColor)
        mWinColor->SetArea(child);
    if (mWinFrame)
        mWinFrame->SetArea(child);
    if (mWinFrameGlow)
        mWinFrameGlow->SetArea(child);
    if (mWinShine)
        mWinShine->SetArea(child);
}

// @ 0x005a45d0
void cSPColorSwatch_s005a_4250::SetColor(const cSPColorRGB_s005a_4250& color)
{
    mDisplayColor = color;
    if (mCustomColor)
        mBaseColor = color;
    if (mWinColor)
        mWinColor->pv23(ColorRGBToU32(&mDisplayColor));
}

// @ 0x005a4630
void cSPColorSwatch_s005a_4250::CollapseExpansion()
{
    int n = (int)(mExpansionSwatches.mpEnd - mExpansionSwatches.mpBegin);
    for (int i = 0; i < n; i++)
        mExpansionSwatches.mpBegin[i]->mRespondToInput = false;
    if (mWinExpansion)
        mWinExpansion->pv66((void*)this);
    if (mWinExpansion)
        mWinExpansion->SetFlag(1, false);
    mExpanded = false;
}

// @ 0x005a4680
void SP::cSPColorSwatch::AddTooltip(unsigned int id)
{
    EA::UTFWin::IWindow* w = mWinRoot.mpObject;
    if (!w)
        return;
    SP::cString str;
    str.Load(0x496bfb26, id, L"Color swatch Placeholder");
    /* Tooltip creation path elided for reading; behaviour: attach tooltip window. */
    (void)str;
}

// @ 0x005a4750
void cSPEditorColorPicker_s005a_4250::GetSwatchArea(cSPColorRGB_s005a_4250* out, int index, int)
{
    float scale = 0.1f;
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        if (mColorPickerConfig->GetProperty(0x4120847, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            scale = *p;
        }
    }
    float n = (float)mNumColors;
    float step = (mRootWidth / n) * scale;
    float w = (mRootWidth - (float)(mNumColors - 1) * step) / n;
    float x = (float)index * (w + step);
    out->r = x;
    out->g = 0.0f;
    out->b = x + w;
    /* 4th float written by caller convention: mRootHeight */
}

// @ 0x005a4800
void cSPEditorColorPicker_s005a_4250::SetArea(EA::RectT_s005a_4250 area)
{
    if (!mWinRoot)
        return;
    mWinRoot->pv27(&area);
    mRootWidth = area.Width();
    mRootHeight = area.Height();
    int n = (int)(mSwatches.mpEnd - mSwatches.mpBegin);
    for (int i = 0; i < n; i++) {
        float scale = 0.1f;
        bool flag = true;
        if (mColorPickerConfig) {
            Property_s005a_4250* prop;
            if (mColorPickerConfig->GetProperty(0x4120847, prop) && prop->mType == 0xd) {
                float* p = prop->GetFloat();
                scale = *p;
            }
        }
        float fn = (float)mNumColors;
        float w = (mRootWidth / fn) * scale;
        float h = (mRootWidth - (float)(mNumColors - 1) * w) / fn;
        float x = (float)i * (h + w);
        mSwatches.mpBegin[i]->SetArea(EA::RectT_s005a_4250(x, 0.0f, x + h, mRootHeight), flag);
    }
}

// @ 0x005a4920
void cSPEditorColorPicker_s005a_4250::SetPaletteColor(const cSPColorRGB_s005a_4250& color)
{
    int i = mSelectedIndex;
    if (i > 0) {
        if (i < (int)mSwatches.size())
            mSwatches[i]->SetColor(color);
    }
}

// @ 0x005a4990
void cSPColorSwatch_s005a_4250::SetExpansionArea(bool b)
{
    float scale = 0.0f;
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        if (mColorPickerConfig->GetProperty(0xd29675ea, prop) && prop->mType == 0xd) {
            float* p = prop->GetFloat();
            scale = *p;
        }
    }
    (void)b; (void)scale;
}

// @ 0x005a4b80
void cSPColorSwatch_s005a_4250::SetSelectedColor(EA::COM::IUnknown32_s005a_4250*)
{
    mBecomingOwner = true;
}

// @ 0x005a4e20
void cSPEditorColorPicker_s005a_4250::SetColor(const cSPColorRGB_s005a_4250& color)
{
    mSelectedColor = color;
    if (mColorPickerConfig) {
        Property_s005a_4250* prop;
        mColorPickerConfig->GetProperty(0xd29675eb, prop);
    }
    int n = (int)(mSwatches.mpEnd - mSwatches.mpBegin);
    for (int i = 0; i < n; i++) {
        cSPColorSwatch_s005a_4250* s = mSwatches.mpBegin[i];
        float dz = s->mDisplayColor.b - color.b;
        float dy = s->mDisplayColor.g - color.g;
        float dx = s->mDisplayColor.r - color.r;
        if (sqrtf(dx * dx + (dy * dy + dz * dz)) < 0.01f) {
            mSelectedSwatch = s;
            return;
        }
    }
    int i = mUnknown28;
    if (i > 0 && i < n) {
        mSelectedSwatch = mSwatches.mpBegin[i];
        cSPColorSwatch_s005a_4250* s = mSelectedSwatch;
        s->mDisplayColor = mSelectedColor;
        if (s->mCustomColor)
            s->mBaseColor = mSelectedColor;
        if (s->mWinColor)
            s->mWinColor->pv23(ColorRGBToU32(&s->mDisplayColor));
    }
}

// @ 0x005a4fb0
void cSPEditorColorPicker_s005a_4250::SetDefault()
{
    int i = mSelectedIndex;
    if (i > 0) {
        if (i < (int)mSwatches.size())
            mSelectedSwatch = mSwatches[i];
    }
}

// @ 0x005a5000
cSPColorSwatch_s005a_4250::cSPColorSwatch_s005a_4250()
: mRespondToInput(false), mRolledOver(false), mMouseDown(false), mExpanded(false),
      mBecomingOwner(false), mCustomColor(false), mIsDefaultColor(false),
      mRollOverTimer(0.0f), mFadeTimer(0.0f), mMouseDownTimer(0.0f), mSelectedTimer(0.0f),
      mBaseColor(SP::gDefaultPaintColor), mDisplayColor(SP::gDefaultPaintColor),
      mTimerDoubleClick(4, 0),
      mCurrMouseDownTime(0), mLastMouseDownTime(0), mSwatchIndex(0xffffffff) {
}

// @ 0x005a5100
cSPColorSwatch_s005a_4250::~cSPColorSwatch_s005a_4250()
{
}

// @ 0x005a51c0
void cSPColorSwatch_s005a_51c0::Init(cPropertyList_s005a_51c0* config, ColorPOD color, float l, float t, float rr, float bb, IWindow_s005a_51c0* parent, EA::COM::IUnknown32_s005a_51c0* owner)
{
    mTimerDoubleClick.Start();
    mOriginalArea.left = l; mOriginalArea.top = t; mOriginalArea.right = rr; mOriginalArea.bottom = bb;
    mBaseColor = color;
    mDisplayColor = color;
    mOwner = owner;
    mColorPickerConfig = config;
    mSwatchIndex = 0xffffffff;
    mExpansionIndex = 0xffffffff;

    uint32_t keyGroup = 0, key1 = 0, key2 = 0, key3 = 0, key4 = 0, key5 = 0;
    bool hasExpansion = true;
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e0, &keyGroup);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e1, &key1);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e2, &key2);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e3, &key3);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e4, &key4);
    GetPropertyAsKeyInstance(mColorPickerConfig, 0xd29675e5, &key5);
    if (mIsDefaultColor) {
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd71, &key1);
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd72, &key2);
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd73, &key3);
        GetPropertyAsKeyInstance(mColorPickerConfig, 0x5adcd6f, &key5);
    }
    {
        Property_s005a_51c0* prop;
        if (mColorPickerConfig && mColorPickerConfig->GetProperty(0x55aa173, prop) && prop->mType == 1)
            hasExpansion = *prop->GetBool();
    }

    WindowRaw* wr = 0;
    void* mem = FUN_009512d0(0x20c, 4, "UI/Window", FUN_009512c0());
    IWindow_s005a_51c0* root = 0;
    if (mem) {
        wr = ((WindowRaw*)mem)->Ctor();
        if (wr) root = (IWindow_s005a_51c0*)((char*)wr + 4);
    }
    mWinRoot = root;
    if (mWinRoot) {
        parent->AddWindow(mWinRoot);
        parent->pv58(mWinRoot);
        mWinRoot->pv23(0xffffffff);
        mWinRoot->SetFillColor(0xffffff);
        mWinRoot->AddWinProc(this);

        mWinColor = SPUIHelpers::CreateImageWindow(Key3(key5, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinColor) {
            mWinColor->pv23(ColorRGBToU32((const cSPColorRGB_s005a_51c0*)&mBaseColor));
            IDrawableCast* d = mWinColor->GetDrawable()->Cast(0xef3c47cf);
            if (d) d->SetMode(2);
            mWinColor->SetFlag(2, false);
            mWinColor->SetFlag(0x10, true);
        }
        mWinFrame = SPUIHelpers::CreateImageWindow(Key3(key1, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinFrame) {
            IDrawableCast* d = mWinFrame->GetDrawable()->Cast(0xef3c47cf);
            if (d) d->SetMode(2);
            mWinFrame->SetFlag(2, false);
            mWinFrame->SetFlag(0x10, true);
        }
        mWinFrameGlow = SPUIHelpers::CreateImageWindow(Key3(key2, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinFrameGlow) {
            IDrawableCast* d = mWinFrameGlow->GetDrawable()->Cast(0xef3c47cf);
            if (d) d->SetMode(2);
            mWinFrameGlow->pv23(0);
            mWinFrameGlow->SetFlag(2, false);
            mWinFrameGlow->SetFlag(0x10, true);
        }
        mWinShine = SPUIHelpers::CreateImageWindow(Key3(key3, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), mWinRoot);
        if (mWinShine) {
            mWinShine->SetFlag(2, false);
            mWinShine->SetFlag(0x10, true);
        }
        SetArea(mOriginalArea, false);

        if (hasExpansion && mOwner && ((UnkCast*)(EA::COM::IUnknown32_s005a_51c0*)mOwner)->Cast(0xd0d22119)) {
            IWindow_s005a_51c0* world = GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
            mWinExpansion = SPUIHelpers::CreateImageWindow(Key3(key4, 0x2f7d0004, keyGroup), Pt2(0.0f, 0.0f), world);
            if (mWinExpansion) {
                SetExpansionArea(false);
                InflateEffect* inflate = 0;
                {
                    void* m = FUN_009512d0(0xb8, 8, "UI/InflateEffect", FUN_009512c0());
                    if (m) inflate = ((InflateEffect*)m)->Ctor();
                }
                if (inflate) {
                    inflate->AddRef();
                    inflate->mCtl.SetDuration(0.3f);
                    inflate->mCtl.SetRange(0.5f, 0.5f);
                    inflate->mCtl.SetFlagB(true);
                    inflate->mCtl.SetFlagA(true);
                    inflate->mCtl2.SetDuration(0.0001f);
                    mWinExpansion->AddWinProc(inflate->mCtl.GetWinProc());
                }
                FadeEffect* fade = 0;
                {
                    void* m = FUN_009512d0(0x60, 8, "UI/FadeEffect", FUN_009512c0());
                    if (m) fade = ((FadeEffect*)m)->Ctor();
                }
                if (fade) {
                    fade->AddRef();
                    fade->mCtl.SetDuration(0.3f);
                    fade->mCtl.SetRange(0.0f, 0.0f);
                    fade->mCtl.SetFlagB(false);
                    fade->mCtl.SetFlagA(true);
                    mWinExpansion->AddWinProc(fade->mCtl.GetWinProc());
                    fade->Release();
                }
                if (inflate) inflate->Release();
            }
        }
    }
    mRespondToInput = true;
}

// @ 0x005a5a50
cX::cX()
: mPtr10(0), mFloat14(0.0f), mFloat18(0.0f),
           mColor1c(SP::gDefaultPaintColor_s005a_51c0), mInt28(0xffffffff), mInt2c(0xffffffff),
           mPtr44(0), mPtr4c(0) {}

// @ 0x005a5ae0
void cSPColorSwatch_s005a_51c0::SetFromSwatch(cSPColorSwatch_s005a_51c0* other)
{
    if (other) {
        SetColor(other->mBaseColor);
        CollapseExpansion();
        MainColorSelected();
    }
}

// @ 0x005a5b10
cX::~cX()
{}

// @ 0x005a5b70
bool SP::cSPColorSwatch::DoMessage(EA::UTFWin::IWindow * a0, EA::UTFWin::Message const & a1)
{
    return 0;
}

// @ 0x005a5db0
void cSPColorSwatch_s005a_51c0::Cleanup()
{
    int n = (int)(mExpansionSwatches.mpEnd - mExpansionSwatches.mpBegin);
    for (int i = 0; i < n; i++)
        mExpansionSwatches.mpBegin[i]->Cleanup();
    if (mWinRoot) {
        mWinRoot->pv58(0);
        IWindow_s005a_51c0* p = mWinRoot->GetParent();
        if (p) {
            if (mWinExpansion)
                mWinExpansion->GetParent()->pv58(mWinExpansion);
            mWinRoot->GetParent()->pv58(mWinRoot);
        }
    }
    mWinRoot = (IWindow_s005a_51c0*)0;
    mWinShine = (IWindow_s005a_51c0*)0;
    mWinFrame = (IWindow_s005a_51c0*)0;
    mWinFrameGlow = (IWindow_s005a_51c0*)0;
    mWinExpansion = (IWindow_s005a_51c0*)0;
    mExpansionSwatches.mpEnd = mExpansionSwatches.mpBegin;
}

// @ 0x005a5ec0
bool cSPEditorColorPicker::Init(IWindow* winRoot, uint32_t configId, int userData, const ColorVector* colors)
{
    mUserData = userData;
    mWinRoot = winRoot;
    mSelectedSwatch = 0;
    PropertyManager* pm = GetPropertyManager();
    mColorPickerConfig = 0;
    pm->GetPropertyList(configId, 0x97097e36, &mColorPickerConfig.mpObject);

    if (mWinRoot && mColorPickerConfig) {
        mWinRoot->SetFillColor(0xffffffff);
        mWinRoot->SetShadeColor(0xffffff);
        mWinRoot->SetFlag(1, 0);
        const EA::RectT_s005a_5ec0* area = mWinRoot->GetRealArea();
        mRootWidth = area->right - area->left;
        mRootHeight = area->bottom - area->top;

        mNumColors = 10;
        cSPColorRGB_s005a_5ec0* colorData = 0;
        if (colors) {
            mNumColors = colors->size();
            colorData = colors->mpBegin;
        } else {
            GetPropertyArray(mColorPickerConfig, 0xd29675ec, &mNumColors, &colorData);
        }

        bool hasCustom = true;
        bool hasDefault = true;
        Property* prop;
        if (mColorPickerConfig && mColorPickerConfig->GetProperty(0x55a847e, prop) && prop->mType == 1)
            hasCustom = *prop->GetBool();
        if (mColorPickerConfig && mColorPickerConfig->GetProperty(0x55a847f, prop) && prop->mType == 1)
            hasDefault = *prop->GetBool();

        int n = mNumColors;
        if (hasCustom) {
            mCustomSwatchIndex = mNumColors;
            mNumColors++;
        }
        if (hasDefault) {
            mDefaultSwatchIndex = mNumColors;
            mNumColors++;
        }

        for (int i = 0; i < n; i++) {
            cSPColorSwatch* sw = new("UI", 0, 0, 0, 0) cSPColorSwatch();
            EA::AutoRefCount_s005a_5ec0<cSPColorSwatch> ref(sw);
            if (sw) {
                const cSPColorRGB_s005a_5ec0* c;
                cSPColorRGB_s005a_5ec0 tmp;
                if (colorData)
                    c = &colorData[i];
                else if (i == 0)
                    c = &gWhiteColor;
                else
                    c = HSLToRGB(&tmp, (float)i / (float)(mNumColors - 1) * 360.0f, 1.0f, 1.0f);
                cSPColorRGB_s005a_5ec0 color = *c;
                sw->Init(mColorPickerConfig, color, GetSwatchArea(i, 0), mWinRoot,
                         (EA::COM::IUnknown32_s005a_5ec0*)this);
                sw->mSwatchIndex = i;
                sw->AddTooltip(0x5bf125f);
                PushSwatch(mSwatches, sw, ref);
            }
        }

        if (hasCustom) {
            cSPColorSwatch* sw = new("UI", 0, 0, 0, 0) cSPColorSwatch();
            EA::AutoRefCount_s005a_5ec0<cSPColorSwatch> ref(sw);
            if (sw) {
                sw->mCustomColor = true;
                cSPColorRGB_s005a_5ec0 color;
                color.r = 0.5f;
                color.g = 0.5f;
                color.b = 0.5f;
                sw->Init(mColorPickerConfig, color, GetSwatchArea(mCustomSwatchIndex, 0), mWinRoot,
                         (EA::COM::IUnknown32_s005a_5ec0*)this);
                sw->mSwatchIndex = mCustomSwatchIndex;
                sw->AddTooltip(0x5bf125f);
                PushSwatch(mSwatches, sw, ref);
            }
        }

        if (hasDefault) {
            cSPColorSwatch* sw = new("UI", 0, 0, 0, 0) cSPColorSwatch();
            EA::AutoRefCount_s005a_5ec0<cSPColorSwatch> ref(sw);
            if (sw) {
                sw->mIsDefaultColor = true;
                cSPColorRGB_s005a_5ec0 color;
                color.r = 1.0f;
                color.g = 0.94f;
                color.b = 0.83f;
                sw->Init(mColorPickerConfig, color, GetSwatchArea(mDefaultSwatchIndex, 1), mWinRoot,
                         (EA::COM::IUnknown32_s005a_5ec0*)this);
                sw->mSwatchIndex = mDefaultSwatchIndex;
                PushSwatch(mSwatches, sw, ref);
            }
        }
    }
    return true;
}

// @ 0x005a6390
void cSPEditorColorPicker::Clear()
{
    eastl::sp_vector<cSPColorSwatch*>& v = mSwatches;
    int n = (int)(v.mpEnd - v.mpBegin);
    for (int i = 0; i < n; i++)
        v.mpBegin[i]->Cleanup();
    v.erase(v.mpBegin, v.mpEnd);
}
