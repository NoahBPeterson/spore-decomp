// src/game/SPEditors/SPUIAssetGrid.cpp -- migrated from slice(s) s00656310, s00654730, s006535b0, s0064eb60, s006553b0, s006525d0, s006515a0, s00650630, s0064fa20, s0064dbd0, s00647f40 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIAssetGrid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPUIAssetComments.h"
#include "SP/cSPUIAssetGrid.h"
#include <intrin.h>
#include "SP/cSPUIFeedFilter.h"
#include "cSPUILayout.h"
#include "SP/cSPUISearchBox.h"
#include "EA/Stopwatch.h"
#include "SP/cString.h"
#include <math.h>
#include "cSPUIAnimator.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s00647f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Primary {
    virtual void p0();
    uint8_t pad[0xc];
};
struct IRef2 {
    virtual void AddRef();
    virtual void Release();
};
struct RefObj : Primary, IRef2 {};
struct AutoRefObj {
    RefObj* p;
    AutoRefObj() : p(0) {}
    ~AutoRefObj() { if (p) p->Release(); }
};
struct AutoRef {
    IRef2* p;
    ~AutoRef() { if (p) p->Release(); }
};
struct Entry14 {
    uint32_t f00, f04, f08;
    AutoRef  h0c;   // +0xc  (primary base)
    AutoRefObj h10; // +0x10 (secondary base)
    void Construct(const Entry14& v);
};
struct Key12 { uint32_t a, b, c; };
struct GridVec {
    Entry14* mpBegin;
    Entry14* mpEnd;
    Entry14* mpCapacity;
    uint32_t mFieldC;    // +0xc
    uint32_t mField10;   // +0x10
    uint8_t  mField14;   // +0x14

    Entry14* EraseAt(Entry14* pos);   // 0x648af0
    Entry14* Insert(Entry14* pos, const Entry14& v); // 0x648b40
    void InsertAt(Entry14* pos, const Entry14& v);   // 0x6485e0 (declared)
    Entry14* InsertSorted(Entry14* pos, const Entry14& v); // 0x648c60 (declared)
    Entry14* FindOrInsert(const Key12& k);           // 0x648ce0
};
extern "C" Entry14* __cdecl f646140(Entry14* a, Entry14* b, Entry14* c);   // move range
extern "C" Entry14* __cdecl f646030(Entry14* first, Entry14* last, const Key12* key, uint8_t flag);
Entry14* GridVec::FindOrInsert(const Key12& k) {
    Entry14* const end = mpEnd;
    Entry14* p = f646030(mpBegin, end, &k, mField14);
    if (p != end) {
        bool less;
        if (k.a == p->f00) {
            if (k.c == p->f08)
                less = k.b < p->f04;
            else
                less = k.c < p->f08;
        } else {
            less = k.a < p->f00;
        }
        if (!less)
            return (Entry14*)((char*)p + 0xc);
    }
    Entry14 value;
    value.f00 = k.a;
    value.f04 = k.b;
    value.f08 = k.c;
    value.h0c.p = 0;
    value.h10.p = 0;
    Entry14* r = InsertSorted(p, value);
    return (Entry14*)((char*)r + 0xc);
}
// ---- items of slice s00647f40 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" Entry14* __cdecl f646140(Entry14* a, Entry14* b, Entry14* c);   // move range
extern "C" Entry14* __cdecl f646030(Entry14* first, Entry14* last, const Key12* key, uint8_t flag);

// ---- items of slice s0064dbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl GetElapsedSeconds();       // FUN_00805080
extern "C" void  __cdecl FUN_808230(void*, void*);  // FUN_00808230
extern void* g_data15ee298;            // 0x015ee298 (object, field +0x3c)
extern "C" void          cString_ctor(void*);
extern "C" bool          cString_Load(void*, uint32_t, uint32_t, const wchar_t*);
extern "C" const wchar_t* cString_GetText(void*);
extern "C" void          cString_dtor(void*);
extern float g_fNegTwo;                                // 0x013ef61c
extern float g_fOne;                                   // 0x01485720
static inline void** VT(void* p) { return *(void***)p; }
struct PBase1 {
    virtual void pv();
};
struct PBase2 {
    virtual void pv();
    int mRef;
    PBase2() : mRef(0) {}
};
extern "C" void* __cdecl AppSystem_s0064_dbd0();               // FUN_0067dd00
struct X659340 { void Release(); };
struct CStr14 { uint32_t mData[5]; };
struct Sub168 {
    void method(uint32_t a, uint32_t b);
};
struct Outer168 {
    char pad[0x168];
    Sub168 sub;
    void Do();
};
struct CellCalc {
    char pad0[0x104];
    float f104;   // +0x104
    float f108;   // +0x108
    char pad1[4];
    int   n110;   // +0x110
    char pad2[4];
    float f118;   // +0x118
    float f11c;   // +0x11c
    float f120;   // +0x120
    float f124;   // +0x124
    void Compute(int index, float* out);
};
namespace SP {
class cSPUIAssetGrid_s0064_dbd0 { public:
    char pad0[0x1e2];
    bool f1e2;
    bool f1e3;
    bool HandleMessage(unsigned msg, unsigned arg);  // 0x0064e680 (SP::cSPUIAssetGrid::HandleMessage)
};
}
struct RectF {
    float a, b, c, d;
    bool Equal() const;
};
struct Key3 { int x, y, z; };
struct C_e6e0 {
    Key3 key;          // +0x00
    void* p2;          // +0x0c
    void* p3;          // +0x10
    uint32_t pad[2];   // +0x14
    bool b1;           // +0x1c
    bool b2;           // +0x1d
    C_e6e0(const Key3* src, void* p2, void* p3, bool b1, bool b2);
};
struct C_e740 : PBase1, PBase2 {
    void* p;           // +0x0c
    bool b1;           // +0x10
    char pad1[3];
    int  n;            // +0x14
    bool b2;           // +0x18
    bool b3;           // +0x19
    C_e740(void* p, bool b1, int n, bool b2, bool b3);
};
struct Node7a0 {
    char pad0[0x10];
    void* child;       // +0x10
};
struct R7a0 {
    char pad0[0xfc];
    Node7a0* p;        // +0xfc
    bool b100;         // +0x100
    void Reset();
};
struct R7d0 {
    char pad0[0x18c];
    void* obj18c;      // +0x18c
    bool Test(uint32_t idx);
};
struct R880 {
    char pad0[0x2c];
    void* w2c;   // +0x2c
    void* w30;   // +0x30
    void* w34;   // +0x34
    void* w38;   // +0x38
    void Update(uint32_t visible, uint32_t arg);
};
struct R980 {
    char pad0[0x3c];
    void* a3c;   // +0x3c
    void* a40;   // +0x40
    void* a44;   // +0x44
    void Layout(void* s1, void* s2, void* s3, bool flag);
};
struct Eaf0 {
    char pad0[0x14];
    bool m14;          // +0x14
    char pad1[7];
    void* m1c;         // +0x1c
    void* m20;         // +0x20
    void* m24;         // +0x24
    char pad2[0x10c - 0x28];
    bool m10c;         // +0x10c
    void SetVisible(bool b);
};
// ---- items of slice s0064dbd0 end

// ---- items of slice s0064fa20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct GridEntry {
    uint8_t  pad00[0x10];
    uint32_t mID;        // +0x10
    uint8_t  pad14[0x0c];
};
struct Grid {
    uint8_t    pad00[0xe8];
    GridEntry* mpBegin;  // +0xe8
    GridEntry* mpEnd;    // +0xec
    GridEntry* Find(uint32_t id);
};
// ---- items of slice s0064fa20 end

// ---- items of slice s00650630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned int g_GridWinIDs[24];          // 0x01400420
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);  // 0x00f473a0
struct IWindow;
struct cSPUILayout_s0065_0630;
struct IWindowControl {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5(int arg);
};
struct IWindow {
    virtual void AddRef();
    virtual void Release();
    virtual void vf2();
    virtual IWindowControl* GetControl(unsigned id);
    virtual IWindow* GetParent();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual float* GetArea();
    virtual float* GetRealArea();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void SetPos(float x, float y);
    virtual void vf26();
    virtual void SetArea(float* rect);
    virtual void SetPosition(float x, float y);
    virtual void vf29();
    virtual void vf30();
    virtual void vf31();
    virtual void vf32();
    virtual void vf33();
    virtual void vf34();
    virtual void vf35();
    virtual void vf36();
    virtual void vf37();
    virtual void vf38();
    virtual void vf39();
    virtual void vf40();
    virtual void vf41();
    virtual void vf42();
    virtual void vf43();
    virtual void vf44();
    virtual void vf45();
    virtual void vf46();
    virtual void vf47();
    virtual void vf48();
    virtual void vf49();
    virtual void vf50();
    virtual void vf51();
    virtual void vf52();
    virtual void vf53();
    virtual void AddWindow(IWindow* w);
    virtual void RemoveWindow(IWindow* w);
    virtual void vf56();
    virtual void vf57();
    virtual void vf58();
    virtual void vf59(IWindow* w);
    virtual void vf60();
    virtual void vf61();
    virtual void vf62();
    virtual void vf63();
    virtual void vf64();
    virtual void AddWinProc(void* proc);
    virtual void RemoveWinProc(void* proc);
};
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
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
    T** operator&() {   // out-parameter use: drops the held reference first
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    void AssignFromPtr(T** src);   // 0x00ac9480 (thiscall, 1 arg)
};
struct ResourceKey {
    unsigned int mInstanceID;   // +0
    unsigned int mTypeID;       // +4
    unsigned int mGroupID;      // +8
};
struct cSPUILayout_s0065_0630 {
    char pad[0x18];
    cSPUILayout_s0065_0630();                                          // 0x00810000
    virtual void vf0();
    virtual void AddRef();
    virtual void Release();
    IWindow* FindWindowByID(unsigned int id, bool bRecurse);          // 0x008105b0
    void Init(ResourceKey* key, bool b, unsigned int arg);            // 0x008120d0
};
struct IProperty {
    char pad0[0x10];
    unsigned short flags;       // +0x10 (0x30 = value is behind a pointer)
    unsigned short type;        // +0x12 (1 = bool)
    // Property data pointer lives at +0 (overlaid here for the inline accessor).
};
struct IPropertyList {
    virtual void AddRef();
    virtual void Release();
    virtual void vf2(); virtual void vf3(); virtual void vf4();
    virtual void vf5(); virtual void vf6(); virtual void vf7(); virtual void vf8();
    virtual bool GetProperty(unsigned int id, IProperty** out);       // slot 9
};
struct IPropertyManager {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6(); virtual void vf7();
    virtual void vf8(); virtual void vf9(); virtual void vf10();
    virtual void GetPropertyList(unsigned int group, unsigned int instance, IPropertyList** out);  // slot 11
};
struct IScrollControl {   // object at ScrollFrameVertical+0x20 (slot 7)
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6();
    virtual void vf7(bool a, bool b);
};
struct ScrollFrameVertical {
    virtual void AddRef();
    virtual void Release();
    char pad08[0x0c];
    IWindow* mpScrollWindow;      // +0x10
    char pad14[4];
    IWindow* mpClientParent;      // +0x18
    char pad1c[4];
    IScrollControl* mpControl;    // +0x20
    char pad24[0x24];
    ScrollFrameVertical();                                                   // 0x0082a040
    bool CreateScrollFrameVertical(unsigned int id, int zero, void* handler); // 0x0082a140
    void Shutdown();                                                         // 0x0082a450
};
struct cSPUIFeedFilter {
    virtual void AddRef();
    virtual void Release();
    char pad[0x108];
    cSPUIFeedFilter();                                      // 0x00661020
    void Init(IWindow* win, unsigned int hash);              // 0x006625f0
    void SetVisible(bool b);                                 // 0x0065fa80
    void Shutdown();                                         // 0x0065fa20
};
struct cSPUISearchBox {
    virtual void AddRef();
    virtual void Release();
    char pad[0x60];
    cSPUISearchBox();                                        // 0x00671ec0
    void Init(IWindow* win);                                 // 0x00671da0
    void SetVisible(bool b);                                 // 0x00671c80
    void Shutdown();                                         // 0x00671c00
};
struct GridRow {            // row returned by LookupRow (0x0066a800)
    char pad[8];
    unsigned int mDefaultID;    // +0x08
    char pad2[0x1c];
    unsigned int mInstance;     // +0x28
    unsigned int mUseGroup;     // +0x2c
    unsigned int mGroup;        // +0x30
};
GridRow* LookupRow(int index);                       // 0x0066a800 (cdecl)
IPropertyManager* PropertyManager();                 // 0x0067de30
void SetWindowAreaToParent(IWindow* w);              // 0x00806bf0 (cdecl)
struct cSPUIAssetGrid {
    char pad00[0x18];
    cSPUILayout_s0065_0630* mLayout;                           // +0x18
    AutoRefCount<IWindow> mWinParent;               // +0x1c
    AutoRefCount<IWindow> mWinRoot;                 // +0x20
    AutoRefCount<IWindow> mWinGrid;                 // +0x24
    AutoRefCount<IWindow> mWinMessagePrimary;       // +0x28
    AutoRefCount<IWindow> mWinMessageSecondary;     // +0x2c
    AutoRefCount<IWindow> mWinFeedHeader;           // +0x30
    AutoRefCount<IWindow> mWinFeedFilter;           // +0x34
    AutoRefCount<IWindow> mWinSearch;               // +0x38
    AutoRefCount<IWindow> mWinSortButtonsParent;    // +0x3c
    AutoRefCount<IWindow> mWinBtnMakeNew;           // +0x40
    AutoRefCount<IWindow> mWin44;                   // +0x44
    AutoRefCount<IWindow> mWin48;                   // +0x48
    AutoRefCount<IWindow> mWin4c;                   // +0x4c
    AutoRefCount<IWindow> mWin50;                   // +0x50
    AutoRefCount<IWindow> mWin54;                   // +0x54 (feed filter host)
    AutoRefCount<IWindow> mWin58;                   // +0x58 (search box host)
    AutoRefCount<IWindow> mWin5c;                   // +0x5c
    AutoRefCount<IWindow> mWin60;                   // +0x60
    AutoRefCount<IWindow> mWin64;                   // +0x64
    AutoRefCount<IWindow> mWin68;                   // +0x68
    AutoRefCount<IWindow> mWin6c;                   // +0x6c
    AutoRefCount<IWindow> mWin70;                   // +0x70
    AutoRefCount<IWindow> mWin74;                   // +0x74
    AutoRefCount<IWindow> mWin78;                   // +0x78
    AutoRefCount<IWindow> mWin7c;                   // +0x7c
    AutoRefCount<IWindow> mWinArr[24];              // +0x80
    AutoRefCount<cSPUIFeedFilter> mFeedFilter;      // +0xe0
    AutoRefCount<cSPUISearchBox> mSearchBox;        // +0xe4
    char padE8[0x12c - 0xe8];
    float mCellWidth;                               // +0x12c
    float mCellHeight;                              // +0x130
    float mScrollWidth;                             // +0x134
    char pad138[0x18c - 0x138];
    AutoRefCount<ScrollFrameVertical> mScrollFrame; // +0x18c
};
static inline bool PropBool(IProperty* p) {
    char* data = (char*)p;
    if (p->flags & 0x30)
        data = *(char**)p;
    return *data != 0;
}
struct IRefCountBase {
    virtual void AddRef();
    virtual void Release();
};
struct EntryPrimary { virtual void v(); char pad0[0xc]; };
struct EntryView : EntryPrimary, IRefCountBase {};   // refcount base at +0x10
struct EntryData : IRefCountBase {};
struct GridEntry_s0065_0630 {
    void* m00;
    void* m04;
    void* m08;
    AutoRefCount<EntryView> m0c;     // +0x0c
    AutoRefCount<EntryData> m10;     // +0x10
    float m14;
    float m18;
    bool m1c;
    bool m1d;
    GridEntry_s0065_0630() {}
    GridEntry_s0065_0630& operator=(const GridEntry_s0065_0630&);   // 0x0064f450
};
// ---- items of slice s00650630 end

// ---- items of slice s006515a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* lpPerformanceCount);
extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  EASTL_allocator_deallocate(void* p);                   // 0xf47380
extern unsigned int g_layoutKeyId;                                      // 0x01525e7c
extern const char g_assetViewName[];                                    // 0x013f6b3c
extern const unsigned int g_msgIds[3];                                  // 0x013ffaec
struct IRefCount { virtual int AddRef(); virtual int Release(); };
struct EntryView_s0065_15a0 : EntryPrimary, IRefCount {};   // IRefCount at +0x10
struct EntryData_s0065_15a0 : IRefCount {};
template <typename T>
struct AutoRefCount_s0065_15a0 {
    T* mpObject;
    AutoRefCount_s0065_15a0() : mpObject(0) {}
    AutoRefCount_s0065_15a0(const AutoRefCount_s0065_15a0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0065_15a0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0065_15a0& operator=(const AutoRefCount_s0065_15a0&);
    void Set(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
    }
};
struct GridEntry_s0065_15a0 {
    void* m00;                       // +0x00
    void* m04;                       // +0x04
    void* m08;                       // +0x08
    AutoRefCount_s0065_15a0<EntryView_s0065_15a0> m0c;     // +0x0c
    AutoRefCount_s0065_15a0<EntryData_s0065_15a0> m10;     // +0x10
    float m14;                       // +0x14
    float m18;                       // +0x18
    bool  m1c;                       // +0x1c
    bool  m1d;                       // +0x1d
    GridEntry_s0065_15a0() {}
    GridEntry_s0065_15a0& operator=(const GridEntry_s0065_15a0&);   // 0x0064f450
};
namespace eastl {
template <typename It, typename Distance, typename T, typename Compare>
void promote_heap_ref(It first, Distance topPosition, Distance position, T value, Compare& compare);
}
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float ax, float ay) : x(ax), y(ay) {}
    Vec2(const Vec2& o) : x(o.x), y(o.y) {}
};
struct Rect {
    float l, t, r, b;
    float Width() const { return r - l; }
};
struct IWin {                                    // generic refcounted UI window
    virtual int AddRef();                        // 0x00
    virtual int Release();                       // 0x04
};
struct IWindow_s0065_15a0 : IWin {
    virtual void v08(); virtual void v0c();
    virtual IWindow_s0065_15a0* GetParent();                // 0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34();
    virtual Rect* GetArea();                     // 0x38
    virtual void v3c();
    virtual int GetAreaBottomInt();              // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68();
    virtual void SetArea(const Rect* r);         // 0x6c
    virtual void v70();
    virtual void SetSize(float w, float h);      // 0x74
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual Vec2* ConvertPoint(Vec2* out, Vec2 pt);   // 0xc4
    virtual void vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void SetParentWin(IWindow_s0065_15a0* w);       // 0xd8
    virtual void SetPoint(IWindow_s0065_15a0* w);           // 0xdc
};
struct ILayout {                                 // AddRef at slot 1 (+4), Release at slot 2 (+8)
    virtual void v00();
    virtual int AddRef();
    virtual int Release();
    void Init(void* key, int a, unsigned int b);                       // @ 0x8120d0
    void SetParentWin(IWindow_s0065_15a0* w, int a, unsigned int b);              // @ 0x8120b0
    void SetReloadCallback(void* cb, void* ctx);                       // @ 0x810090
};
struct AssetView {                               // UI::AssetDiscovery_View (0x108 bytes)
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Attach(IWindow_s0065_15a0* w, int a, int b, int c);              // 0x1c
    virtual void Detach();                                              // 0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void Layout(int a, int b);                                  // 0x30
    float GetHeight();                                                  // @ 0x6578d0
    float GetWidth();                                                   // @ 0x6578f0
};
struct IMsgServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void AddHandler(void* handler, unsigned int id);            // 0x24
};
struct IAppSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual void SetFlag(int v);                                        // 0x40
};
struct IWinScrollbar : IWin {
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual int GetMax();                        // 0x38
    virtual void v3c();
    virtual int GetMin();                        // 0x40
};
struct ScrollFrame : IWin {                      // object held in w18c
    char pad4[0x14];
    IWindow_s0065_15a0* mArea;                              // +0x18
    char pad1c[4];
    IWinScrollbar* mScrollbar;                   // +0x20
    void UpdateVertical(int a);                  // @ 0x82a500 (SPUIHelpers::UpdateScrollFrameVertical)
};
IAppSystem* AppSystem();                                                // @ 0x67dd00
IMsgServer* MessageServer();                                            // @ 0x67dcc0
void RemoveHandler(IMsgServer* server, void* handler, const unsigned int* ids, int count, int x); // @ 0x571db0
void __cdecl GetBoundingScreenRect(Rect* out, IWindow_s0065_15a0* w, int flags);   // @ 0x808d20
AssetView* __fastcall AssetView_ctor(void* mem);                        // @ 0x657f70 (thiscall)
ILayout* __fastcall Layout_ctor(void* mem);                             // @ 0x810000 (thiscall)
struct Stopwatch {
    unsigned long long mStart;      // +0x00
    unsigned long long mElapsed;    // +0x08
    int mMode;                      // +0x10
    int mUnits;                     // +0x14
    Stopwatch(int units, int a);                                         // @ 0x93a560
    void Start() {
        unsigned long long t;
        if (mMode == 1) t = __rdtsc();
        else QueryPerformanceCounter((long long*)&t);
        mStart = t;
        mElapsed = 0;
    }
};
struct GridVec_s0065_15a0 {
    GridEntry_s0065_15a0* mpBegin;
    GridEntry_s0065_15a0* mpEnd;
    GridEntry_s0065_15a0* mpCapacity;
    GridVec_s0065_15a0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroyValues(GridEntry_s0065_15a0* first, GridEntry_s0065_15a0* last);             // @ 0x0064f410
    ~GridVec_s0065_15a0() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};
struct AutoHandler {                 // EA::Messaging::AutoHandler
    IMsgServer* mpServer;
    void* mpHandler;
    const unsigned int* mpIdArray;
    int mCount;
    int mX;
    AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mCount(0), mX(0) {}
    ~AutoHandler() {
        if (mpServer) {
            IMsgServer* s = mpServer;
            void* h = mpHandler; const unsigned int* ids = mpIdArray; int n = mCount; int x = mX;
            mpServer = 0;
            RemoveHandler(s, h, ids, n, x);
        }
    }
};
struct GB0 { virtual ~GB0() {} virtual void b0f1(); };
struct GB1 { virtual ~GB1() {} virtual void b1f1(); };
struct GB2 { virtual void b2f0(); virtual void b2f1(); };
struct GB3 { GB3() : mRefCount(0) {} virtual ~GB3() {} int mRefCount; };
struct cSPUIAssetGrid_s0065_15a0 : GB0, GB1, GB2, GB3 {
    // GB0 @0, GB1 @4, GB2 @8, GB3 @0xc (mRefCount @0x10)
    bool mIsVisible;                              // +0x14
    AutoRefCount_s0065_15a0<ILayout> mLayout;                // +0x18
    AutoRefCount_s0065_15a0<IWin> w1c;
    AutoRefCount_s0065_15a0<IWindow_s0065_15a0> w20;
    AutoRefCount_s0065_15a0<IWindow_s0065_15a0> w24;
    AutoRefCount_s0065_15a0<IWin> w28;
    AutoRefCount_s0065_15a0<IWindow_s0065_15a0> w2c;
    AutoRefCount_s0065_15a0<IWin> w30, w34, w38, w3c, w40, w44;
    AutoRefCount_s0065_15a0<IWindow_s0065_15a0> w48;
    AutoRefCount_s0065_15a0<IWindow_s0065_15a0> w4c;
    AutoRefCount_s0065_15a0<IWin> w50,
                       w54, w58, w5c, w60, w64, w68, w6c, w70, w74, w78, w7c;
    AutoRefCount_s0065_15a0<IWin> mWinArray[24];             // +0x80
    AutoRefCount_s0065_15a0<IWin> we0;                       // +0xe0
    AutoRefCount_s0065_15a0<IWin> we4;                       // +0xe4
    GridVec_s0065_15a0 mGridEntries;                         // +0xe8
    unsigned int padF4[2];                        // +0xf4
    unsigned int mFC;                             // +0xfc
    bool m100;                                    // +0x100
    float m104, m108;                             // +0x104
    bool m10c;                                    // +0x10c
    int m110, m114;                               // +0x110
    float m118, m11c, m120, m124, m128, m12c, m130, m134;   // +0x118
    AutoHandler mHandler;                         // +0x138
    unsigned int pad14c;                          // +0x14c
    Stopwatch mTimerA;                            // +0x150
    Stopwatch mTimerB;                            // +0x168
    float m180, m184, m188;                       // +0x180
    AutoRefCount_s0065_15a0<ScrollFrame> w18c;               // +0x18c
    bool m190;                                    // +0x190
    int m194, m198;                               // +0x194
    AutoRefCount_s0065_15a0<IWin> w19c;                      // +0x19c
    int m1a0, m1a4;                               // +0x1a0
    int m1a8, m1ac, m1b0, m1b4;                   // +0x1a8
    bool m1b8, m1b9, m1ba, m1bb;                  // +0x1b8
    unsigned int pad1bc;                          // +0x1bc
    AutoRefCount_s0065_15a0<IWin> w1c0;                      // +0x1c0
    int m1c4, m1c8, m1cc;                         // +0x1c4
    unsigned int pad1d0[5];                       // +0x1d0
    bool m1e4, m1e5, m1e6, m1e7, m1e8;            // +0x1e4

    cSPUIAssetGrid_s0065_15a0();                             // @ 0x00651990
    ~cSPUIAssetGrid_s0065_15a0();                            // @ 0x00651c80
    void SetupWindows(IWindow_s0065_15a0* a, IWindow_s0065_15a0* b, IWindow_s0065_15a0* c);   // @ 0x00651ff0
    void UpdateScrollRegion();                    // @ 0x006524a0
    static void __cdecl ReloadCallback(cSPUIAssetGrid_s0065_15a0* self, ILayout* l, int flag);   // @ 0x650630
    void ComputeCardLayoutParameters();           // @ 0x650020
    void UpdateScrolling(int a);                  // @ 0x64fa20
    void FUN_650470();                            // @ 0x650470
    void FUN_66bd00();                            // @ 0x66bd00
    void FUN_64e5d0(int rows, float* out);        // @ 0x64e5d0
};
struct GridSub8 {
    char pad0[0x24];
    IWindow_s0065_15a0* w24;                  // full +0x2c
    char pad28[0xe0 - 0x28];
    GridEntry_s0065_15a0* mpBegin;            // full +0xe8
    GridEntry_s0065_15a0* mpEnd;              // full +0xec
    char padE8[0x100 - 0xe8];
    float m100;                    // full +0x108
    char pad104[0x114 - 0x104];
    float m114;                    // full +0x11c
    char pad118[0x120 - 0x118];
    float m120;                    // full +0x128
    char pad124[0x1a4 - 0x124];
    int m1a4;                      // full +0x1ac
    int m1a8;                      // full +0x1b0
    float ContentHeight(float width);
};
// ---- items of slice s006515a0 end

// ---- items of slice s006525d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_uiCtx;                                    // 0x015ee298
extern "C" void* AssetBrowser();                         // 0x00401030
extern "C" void* FUN_00644a70(void*);                    // 0x00644a70
struct EntryView_s0065_25d0 : EntryPrimary, IRefCount {};   // IRefCount at +0x10
struct EntryData_s0065_25d0 : IRefCount {};                  // IRefCount at +0x0
template <typename T>
struct AutoRefCount_s0065_25d0 {
    T* mpObject;
    AutoRefCount_s0065_25d0() : mpObject(0) {}
    AutoRefCount_s0065_25d0(const AutoRefCount_s0065_25d0& x) : mpObject(x.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount_s0065_25d0() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s0065_25d0& operator=(const AutoRefCount_s0065_25d0&);
};
struct GridEntry_s0065_25d0 {
    void* m00;                       // +0x00
    void* m04;                       // +0x04
    void* m08;                       // +0x08
    AutoRefCount_s0065_25d0<EntryView_s0065_25d0> m0c;     // +0x0c  (refcount base at +0x10)
    AutoRefCount_s0065_25d0<EntryData_s0065_25d0> m10;     // +0x10
    float m14;                       // +0x14
    float m18;                       // +0x18
    bool  m1c;                       // +0x1c
    bool  m1d;                       // +0x1d
    GridEntry_s0065_25d0() {}
    GridEntry_s0065_25d0& operator=(const GridEntry_s0065_25d0&);   // 0x0064f450
};
GridEntry_s0065_25d0* CopyRange(GridEntry_s0065_25d0* first, GridEntry_s0065_25d0* last, GridEntry_s0065_25d0* dest);               // 0x64f890
GridEntry_s0065_25d0* UninitializedCopy(GridEntry_s0065_25d0* first, GridEntry_s0065_25d0* last, GridEntry_s0065_25d0* dest);       // 0x64f7c0
GridEntry_s0065_25d0* UninitializedFillN(GridEntry_s0065_25d0* dest, unsigned n, const GridEntry_s0065_25d0& value, GridEntry_s0065_25d0*);  // 0x64f8d0
void       CopyBackward(GridEntry_s0065_25d0* first, GridEntry_s0065_25d0* last, GridEntry_s0065_25d0* destEnd);         // 0x64f950
void       FillRange(GridEntry_s0065_25d0* first, GridEntry_s0065_25d0* last, const GridEntry_s0065_25d0& value);        // 0x651670
struct GridVec_s0065_25d0 {
    GridEntry_s0065_25d0* mpBegin;     // +0
    GridEntry_s0065_25d0* mpEnd;       // +4
    GridEntry_s0065_25d0* mpCapacity;  // +8

    void DoDestroyValues(GridEntry_s0065_25d0* first, GridEntry_s0065_25d0* last);                     // 0x0064f410
    GridEntry_s0065_25d0* ReallocateAndCopy(unsigned n, GridEntry_s0065_25d0* first, GridEntry_s0065_25d0* last); // 0x00651540
    GridVec_s0065_25d0& operator=(const GridVec_s0065_25d0& x);                                        // 0x00652ba0
    void DoInsertValues(GridEntry_s0065_25d0* position, unsigned n, const GridEntry_s0065_25d0& value); // 0x00652c90
    GridEntry_s0065_25d0* erase(GridEntry_s0065_25d0* position);                                       // 0x006534c0
    void swap(GridVec_s0065_25d0& other);                                                    // 0x00653510
};
struct cString {
    wchar_t* mpBegin;      // +0
    wchar_t* mpEnd;        // +4
    wchar_t* mpCapacity;   // +8
    void*    mAllocator;   // +0xc
    cString();
    ~cString();
    void Load(unsigned int hash, int flags, const wchar_t* fmt);
    const wchar_t* c_str() const;
    cString& operator=(const wchar_t* s);
};
extern "C" void  WString_Assign(cString* dst, const wchar_t* first, const wchar_t* last);  // 0x00423650
struct StatsGrid {
    char pad00[0x14];
    bool mIsVisible;                 // +0x14
    char pad15[0x1ac - 0x15];
    unsigned int mA;                 // +0x1ac
    unsigned int mB;                 // +0x1b0
    unsigned int mCount;             // +0x1b4
    void Scrollbar(unsigned a, unsigned b, unsigned c, unsigned d);  // 0x0064e980
    void UpdateStatsText();
};
// ---- items of slice s006525d0 end

// ---- items of slice s006553b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int __cdecl GetTutorialToolPrice(void* tool, unsigned id, int def);   // 0x004e1c30
inline void* operator new(size_t, void* p) { return p; }
struct Key {                           // EA::ResourceMan::Key (instance, type, group)
    int a, b, c;
};
struct Rect_s0065_53b0 { float l, t, r, b; };
template <typename T>
struct AutoRefCount_s0065_53b0 {
    T* mpObject;
    AutoRefCount_s0065_53b0() : mpObject(0) {}
    AutoRefCount_s0065_53b0(const AutoRefCount_s0065_53b0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0065_53b0() { if (mpObject) mpObject->Release(); }
    void Reset()
    {
        T* old = mpObject;
        if (old) {
            mpObject = 0;
            old->Release();
        }
    }
};
struct AssetDataPrimary {              // primary vtable of a cached asset record; IRefCount sub-object at +0x10
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsReady();                    // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual const Key* GetKey();               // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c();
    virtual bool PassesFilterC();              // 0x60
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual bool PassesFilterB();              // 0x74
    virtual bool PassesFilterA();              // 0x78
    virtual void v7c(); virtual void v80();
    virtual bool IsHidden();                   // 0x84
    char pad0[0xc];
};
struct AssetData : AssetDataPrimary, IRefCount {};
struct AssetView_s0065_53b0 {                             // UI::AssetDiscovery_View
    virtual int AddRef();                      // 0x00
    virtual int Release();                     // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Attach(void* win, AssetData* data, int a, int b);   // 0x1c
    virtual void v20();
    virtual void OnUpdate(int arg, bool flag); // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void SetEnabled(bool enabled);     // 0x38
    char pad04[0xf4 - 4];
    bool mSelectable;                          // +0xf4
    void SetPos(Vec2 pos, bool flag);          // 0x00658e00
    void SelectAsset(int a, bool b, const Rect_s0065_53b0* rc, int c, int d);   // 0x00657a30
    void Destroy();                            // 0x00659340
};
struct FcObj {                                 // object pointed to by the grid's +0xfc member
    char pad0[0x10];
    AssetView_s0065_53b0* mpView;                         // +0x10
};
struct IWindow_s0065_53b0 {
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void SetPos(float x, float y);     // 0x64
    virtual void SetSize(float w, float h);    // 0x68
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetVisible(bool a, bool b);   // 0x7c
    virtual void SetText(const wchar_t* text); // 0x80
};
struct IScrollbar {
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual int GetMin();                      // 0x40
};
struct ScrollFrame_s0065_53b0 {
    virtual int AddRef(); virtual int Release();
    char pad4[0x1c];
    IScrollbar* mScrollbar;                    // +0x20
};
struct GridEntry_s0065_53b0 {
    Key                     mKey;      // +0x00
    AutoRefCount_s0065_53b0<AssetData> mData;     // +0x0c
    AutoRefCount_s0065_53b0<AssetView_s0065_53b0> mView;     // +0x10
    float                   mX;        // +0x14
    float                   mY;        // +0x18
    bool                    mEnabled;  // +0x1c
    bool                    mHasData;  // +0x1d
    GridEntry_s0065_53b0(const Key* key, AssetData* data, AssetView_s0065_53b0* view, bool a, bool b);   // 0x0064e6e0
    GridEntry_s0065_53b0(const GridEntry_s0065_53b0& x);                                                  // 0x0064f3b0
};
struct GridVec_s0065_53b0 {
    GridEntry_s0065_53b0* mpBegin;
    GridEntry_s0065_53b0* mpEnd;
    GridEntry_s0065_53b0* mpCapacity;
    void reserve(int n);                                                 // 0x00652b00
    void DoInsertValue(GridEntry_s0065_53b0* pos, const GridEntry_s0065_53b0& v);              // 0x006535b0
    void FUN_654490(int x);                                              // 0x00654490
    void push_back(const GridEntry_s0065_53b0& v)
    {
        if (mpEnd < mpCapacity) {
            GridEntry_s0065_53b0* p = mpEnd;
            mpEnd = p + 1;
            if (p) new (p) GridEntry_s0065_53b0(v);
        } else
            DoInsertValue(mpEnd, v);
    }
};
struct KeyVec {                                // eastl::vector<Key>
    Key* mpBegin;
    Key* mpEnd;
    Key* mpCapacity;
    void reserve(int n);                       // 0x0041e4d0
};
struct KeyIter { void* mpNode; bool operator==(const KeyIter& o) const { return mpNode == o.mpNode; } };
struct KeyMap {                                // eastl::map<Key, AssetData*> embedded at +0x48 of the feed item
    KeyIter* find(KeyIter* out, const Key* key);                         // 0x00a21dc0
};
struct FeedListItem {                          // SP::cSPUIFeedListItem (what the grid shows)
    char   pad0[0x48];
    KeyMap mMap;                               // +0x48
    char   pad4c[0x5c - 0x4c];
    int    mTotal;                             // +0x5c
    bool   FUN_642910();                       // 0x00642910
    int    FUN_643060();                       // 0x00643060
    int    FUN_642900();                       // 0x00642900
    void   FUN_644040(KeyVec* out);            // 0x00644040
    bool   FUN_6442e0(const Key* key);         // 0x006442e0
};
struct FeedFilter {                            // SP::cSPUIFeedFilter (+0xe0)
    char pad0[0x14];
    int  mF14;
    int  mF18;
    bool Check(AssetData* data, int mode);                 // 0x00660880
    void FUN_662750(int a, int b, int c);                  // 0x00662750
    void FUN_10829f0(int arg);                             // 0x010829f0
};
struct SearchBox {                             // SP::cSPUISearchBox (+0xe4)
    bool Match(AssetData* data);               // 0x00672200
    void FUN_6720e0();                         // 0x006720e0
    void Update(int arg);                      // 0x00672040
};
struct AssetContainer {
    char pad0[4];
    void* mpEnd;                               // +4
    struct IterPair { void* first; void* second; };
    void FindEntry(IterPair* out, GridEntry_s0065_53b0* e);                         // 0x00646d10
};
struct AssetBrowser_s0065_53b0 {
    char pad0[0x18];
    void* mpTool;                              // +0x18
    AssetContainer* GetContainer();                                      // 0x00644a70
    AssetView_s0065_53b0* GetViewFor(AssetData* data);                              // 0x006462b0
    AssetView_s0065_53b0* GetDefaultView();                                         // 0x006452c0
};
extern AssetBrowser_s0065_53b0* __cdecl GetAssetBrowser();                          // 0x00401030
extern IAppSystem* __cdecl GetAppSystem();                               // 0x0067dd00
struct Stopwatch_s0065_53b0 {
    unsigned long long mStart;
    unsigned long long mElapsed;
    int mMode;
    int mUnits;
    unsigned long long GetElapsedTime();                                 // 0x0093a5e0
    void Restart();                                                      // 0x00571e80
    void Start()
    {
        unsigned long long t;
        if (mMode == 1) t = __rdtsc();
        else QueryPerformanceCounter((long long*)&t);
        mStart = t;
        mElapsed = 0;
    }
};
struct cSPUIAssetGrid_s0065_53b0 : GB0, GB1, GB2, GB3 {
    bool mIsVisible;                              // +0x14
    char pad18[0x2c - 0x18];
    AutoRefCount_s0065_53b0<IWindow_s0065_53b0> mWinFeedHeader;         // +0x2c
    AutoRefCount_s0065_53b0<IWindow_s0065_53b0> mWinFeedFilter;         // +0x30
    char pad34[0x60 - 0x34];
    AutoRefCount_s0065_53b0<IWindow_s0065_53b0> mWinMessagePrimary;     // +0x60
    AutoRefCount_s0065_53b0<IWindow_s0065_53b0> mWinMessageSecondary;   // +0x64
    char pad68[0xe0 - 0x68];
    FeedFilter* mFeedFilter;                      // +0xe0
    SearchBox*  mSearchBox;                       // +0xe4
    GridVec_s0065_53b0     mGridEntries;                     // +0xe8
    char padF4[0xfc - 0xf4];
    FcObj*      mpFc;                             // +0xfc
    bool        m100;                             // +0x100
    float       mCardWidth;                       // +0x104
    float       mCardHeight;                      // +0x108
    bool        m10c;                             // +0x10c
    char pad110[0x150 - 0x110];
    Stopwatch_s0065_53b0   mTimerA;                          // +0x150
    Stopwatch_s0065_53b0   mTimerB;                          // +0x168
    float       m180, m184;                       // +0x180
    char pad188[0x18c - 0x188];
    ScrollFrame_s0065_53b0* mpScrollFrame;                   // +0x18c
    char pad190[0x194 - 0x190];
    int         m194;                             // +0x194
    int         m198;                             // +0x198
    struct ViewState { char pad[0x16]; bool f16; };
    ViewState*  mpViewState;                      // +0x19c
    char pad1a0[0x1a8 - 0x1a0];
    int         mNumTotal;                        // +0x1a8
    int         mNumShown;                        // +0x1ac
    int         mNumEnabled;                      // +0x1b0
    int         mNumPending;                      // +0x1b4
    bool        m1b8, m1b9, m1ba, m1bb;           // +0x1b8
    char pad1bc[4];
    FeedListItem* mpFeed;                         // +0x1c0
    Key         mPendingKey;                      // +0x1c4
    bool        mPendingA;                        // +0x1d0
    bool        mPendingB;                        // +0x1d1
    char pad1d2[2];
    float       mPendingL, mPendingT, mPendingR, mPendingB2;   // +0x1d4
    bool        mLoadingFeed;                     // +0x1e4
    bool        m1e5;                             // +0x1e5
    bool        mNeedsRefresh;                    // +0x1e6
    bool        mNeedsFocus;                      // +0x1e7
    bool        m1e8;                             // +0x1e8

    void RefreshAssetStates();                                   // @ 0x006553b0
    bool SelectKey(const Key* key, bool a, bool b, const Rect_s0065_53b0* rc);   // @ 0x00655840
    void AddEntries(KeyVec* keys);                               // @ 0x00655b00
    void Update(int arg);                                        // @ 0x00655ed0
    void UpdateAll();                                            // 0x0064ecc0
    void FUN_654d00();                                           // 0x00654d00
    void UpdateStatsText();                                      // 0x006528f0
    void UpdateScrollRegion();                                   // 0x006524a0
    int  FindFirstVisibleEntry();                                // 0x00653b80
    void FUN_654e20(AssetView_s0065_53b0* v);                               // 0x00654e20
    void FUN_654f50(FeedListItem* feed, ViewState* st);          // 0x00654f50
    bool FUN_64fde0(int* p);                                     // 0x0064fde0
    void FUN_64e880(bool a, unsigned pct);                       // 0x0064e880
    bool FUN_64e7d0(int i);                                      // 0x0064e7d0
    void FUN_650470();                                           // 0x00650470
    void UpdateScrolling(int a);                                 // 0x0064fa20
};
// ---- items of slice s006553b0 end

// ---- items of slice s0064eb60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_0066a800(int);  // AssetViewAt(index)
extern uint32_t g_140042c;
extern "C" void FUN_0066a5e0();
extern "C" int FUN_0066a5c0(uint32_t value);
extern "C" char FUN_00661b10();
extern "C" void* FUN_0065f810();
extern "C" unsigned int FUN_004bb860(unsigned int key);
namespace EA {
template <typename T>
class AutoRefCount_s0064_eb60 { public:
    T* mpObject;
    AutoRefCount_s0064_eb60() : mpObject(0) {}
    AutoRefCount_s0064_eb60(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s0064_eb60(const AutoRefCount_s0064_eb60& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0064_eb60() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0064_eb60& operator=(const AutoRefCount_s0064_eb60& o) {
        T* p = o.mpObject;
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
};  // namespace EA
}
namespace SP {
struct AssetPrimary {
    virtual void slot0();
    virtual void slot1();
    char pad[0x0c];
};
}
namespace SP {
struct AssetDataRef {
    virtual void AddRef();
    virtual void Release();
};
}
namespace SP {
class cSPAssetData_s0064_eb60 : public AssetPrimary, public AssetDataRef { public:};
}
namespace SP {
struct cSPAssetView {
    virtual void AddRef();
    virtual void Release();
};
}
namespace SP {
struct ResourceKey_s0064_eb60 {
    unsigned int mTypeID;       // +0x00
    unsigned int mInstanceID;   // +0x04
    unsigned int mGroupID;      // +0x08
};
}
namespace SP {
struct cSPAssetGridEntry_s0064_eb60 {
    ResourceKey_s0064_eb60 mAssetKey;                                  // +0x00
    EA::AutoRefCount_s0064_eb60<cSPAssetData_s0064_eb60> mAssetData;              // +0x0c
    EA::AutoRefCount_s0064_eb60<cSPAssetView> mAssetView;              // +0x10
    float mPosX;                                            // +0x14
    float mPosY;                                            // +0x18
    bool mFlag1C;                                           // +0x1c
    bool mFlag1D;                                           // +0x1d
};
}
namespace SP {
struct TypeGridEntrySort {
    char pad0[0x0c];
    bool operator()(const cSPAssetGridEntry_s0064_eb60& a, const cSPAssetGridEntry_s0064_eb60& b);
};
}
namespace SP {
class cSPUIAssetGrid_s0064_eb60 { public:
    char pad0[0x74];
    void* m74;                                          // +0x74
    void* m78;                                          // +0x78
    void* m7c;                                          // +0x7c
    void* mWinArray[24];                                // +0x80 .. +0xdf
    void* me0;                                          // +0xe0
    char padE4[4];                                      // +0xe4
    cSPAssetGridEntry_s0064_eb60* mpEntries;                       // +0xe8
    cSPAssetGridEntry_s0064_eb60* mpEntriesEnd;                    // +0xec
    char pad1[0x12c - 0xf0];
    float m12c;                                         // +0x12c
    float m130;                                         // +0x130
    float m134;                                         // +0x134
    char pad2[0x19c - 0x138];
    void* m19c;                                         // +0x19c
    int m1a0;                                           // +0x1a0
    int m1a4;                                           // +0x1a4
    char pad3[0x1b8 - 0x1a8];
    bool m1b8;                                          // +0x1b8
    char pad4[0x1e8 - 0x1b9];
    bool m1e8;                                          // +0x1e8

    cSPAssetGridEntry_s0064_eb60* GetEntry(int i);                 // 0x0064f2c0
    int IndexOfView(cSPAssetView* v);                   // 0x0064f280
    bool CheckFlag();                                   // 0x0064f320
    void SetEntryState(int idx, bool force);            // 0x0064eb60
    void UpdateAll();                                   // 0x0064ecc0
};
}
namespace SP {
struct ViewState {
    // object whose +0x16 is a bool; pointer stored in m19c
    char pad0[0x16];
    bool f16;
};
}
struct FlagKey {
    bool mFlags[0x18];                                // +0x00
    uint32_t mValue;                                  // +0x18
    bool mExtra;                                      // +0x1c
};
namespace SP {
void* AssetBrowser();                                 // 0x00401030
}
namespace SP {
struct cSPUIAnimator {
    void RemoveAnimation(void* win, int id);                              // 0x007f6210
    void AddAnimation(void* target, void* win, unsigned int id);          // 0x007f8d10
};
}
float GetElapsedSeconds(float seconds, int type, void* win, uint32_t id);  // 0x00805080
struct AnimRawTmp {
    void* mVt0;                                       // +0x00
    char pad04[4];
    void* mVt1;                                       // +0x08
    void* mpRef;                                      // +0x0c
};
AnimRawTmp* SPUICreateWindowAnimationTargetPosition(AnimRawTmp* out, void* win,  // 0x007f80d0
                                                    float x, float y, float elapsed);
AnimRawTmp* SPUICreateWindowAnimationTargetScale(AnimRawTmp* out, void* win,     // 0x007f81d0
                                                 float scale, float elapsed);
struct AnimRef {
    virtual void AddRef();
    virtual void Release();                           // +0x04
};
struct AssetBrowserObj {
    char pad0[0x14];
    void* m14;                                        // +0x14 animator
    char pad18[0x1cc - 0x18];
    uint32_t m1cc;                                    // +0x1cc
    char pad1d0[0x1f0 - 0x1d0];
    FlagKey m1f0;                                     // +0x1f0
};
// ---- items of slice s0064eb60 end

// ---- items of slice s006535b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   FUN_00646030(void*, void*, void*, char);  // 0x00646030
extern "C" char  SetAssetData(void*, int);             // 0x004bbe20
extern "C" int*  FUN_00555a20(int*, int*, int*, char); // 0x00555a20
extern "C" uint32_t cSPUIAssetView_InitVerbCollection(uint32_t);  // 0x004bb860
extern "C" void  fixed_vector_DoInsertValue(void*, void*, void*);  // 0x0060a600
extern "C" void  FUN_0065aeb0();                       // 0x0065aeb0
extern "C" void  Messaging_RemoveHandler(void*, void*, void*, void*, void*);  // 0x00571db0
extern "C" void  cSPUIAssetView_SelectAsset(void*, int, int, int, int, int);  // 0x00657a30
extern "C" void  SPUIHelpers_UpdateMouseFocus(int);    // 0x00804f50
struct EntryView_s0065_35b0 : EntryPrimary, IRefCount {};
struct EntryData_s0065_35b0 : IRefCount {};
template <typename T>
struct AutoRefCount_s0065_35b0 {
    T* mpObject;
    AutoRefCount_s0065_35b0() : mpObject(0) {}
    AutoRefCount_s0065_35b0(const AutoRefCount_s0065_35b0& x) : mpObject(x.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount_s0065_35b0() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s0065_35b0& operator=(const AutoRefCount_s0065_35b0&);
};
struct GridEntry_s0065_35b0 {
    void* m00;
    void* m04;
    void* m08;
    AutoRefCount_s0065_35b0<EntryView_s0065_35b0> m0c;
    AutoRefCount_s0065_35b0<EntryData_s0065_35b0> m10;
    float m14;
    float m18;
    bool  m1c;
    bool  m1d;
    GridEntry_s0065_35b0() : m00(0), m04(0), m08(0) {}
    GridEntry_s0065_35b0& operator=(const GridEntry_s0065_35b0&);   // 0x0064f450
};
struct CompareA {                 // 0x0064ff90: by value
    bool operator()(GridEntry_s0065_35b0 a, GridEntry_s0065_35b0 b) const;
};
struct TypeGridEntrySort_s0065_35b0 {        // 0x0066a830: by reference
    bool operator()(const GridEntry_s0065_35b0& a, const GridEntry_s0065_35b0& b) const;
};
GridEntry_s0065_35b0* CopyRange(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, GridEntry_s0065_35b0* dest);              // 0x64f890
GridEntry_s0065_35b0* UninitializedCopy(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, GridEntry_s0065_35b0* dest);      // 0x64f7c0
GridEntry_s0065_35b0* DestroyRange(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, GridEntry_s0065_35b0* dest);           // 0x64f840
void       CopyBackward(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, GridEntry_s0065_35b0* destEnd);        // 0x64f950
GridEntry_s0065_35b0* GetPartitionA(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, GridEntry_s0065_35b0 pivot);          // 0x652e70
GridEntry_s0065_35b0* GetPartitionB(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, GridEntry_s0065_35b0 pivot);          // 0x653110
void       MakeHeapA(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last);                               // 0x6533d0
void       AdjustHeapA(GridEntry_s0065_35b0* first, int top, int heapSize, int pos, GridEntry_s0065_35b0 value);  // 0x6525d0
void       SortHeapA(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last);                               // 0x653470
void       PartialSortB(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* middle, GridEntry_s0065_35b0* last);         // 0x653230
GridEntry_s0065_35b0  MedianA(GridEntry_s0065_35b0 a, GridEntry_s0065_35b0 b, GridEntry_s0065_35b0 c);                             // 0x6515a0
GridEntry_s0065_35b0** FUN_0064f730(GridEntry_s0065_35b0** pOut, GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last,
                         GridEntry_s0065_35b0* initial, unsigned count);                           // 0x0064f730
struct GridVec_s0065_35b0 {
    GridEntry_s0065_35b0* mpBegin;
    GridEntry_s0065_35b0* mpEnd;
    GridEntry_s0065_35b0* mpCapacity;

    void DoDestroyValues(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last);                      // 0x0064f410
    GridEntry_s0065_35b0* ReallocateAndCopy(unsigned n, GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last);  // 0x00651540
    void DoInsertValue(GridEntry_s0065_35b0* position, const GridEntry_s0065_35b0& value);              // 0x006535b0
    void f_00652c90(GridEntry_s0065_35b0* position, unsigned n, const GridEntry_s0065_35b0& value);     // 0x00652c90
    void f_0064f4e0(unsigned n, void* alloc);                                     // 0x0064f4e0 (ecx = the vector)
    void resize(unsigned n);                                                      // 0x00653e40
    void reserve(unsigned n);                                                     // 0x00654490
    void swap(GridVec_s0065_35b0& other);                                                    // 0x00653510

    void* mpAllocator;   // +0xc: allocator identity the rebuild helpers take by address
};
struct LayoutStub {
    void f_00811ad0(unsigned flags);      // 0x00811ad0 (ecx = layout)
};
struct AssetObjStub {
    void f_00659340();                    // 0x00659340 (ecx = object)
    void f_0065fa20();                    // 0x0065fa20 (ecx = object)
};
struct SearchBoxStub {
    void f_00671c00();                    // 0x00671c00 (ecx = search box)
    void OnSearchChanged();               // 0x00671c50 (ecx = search box)
};
static const int kQuickSortLimit = 28;
inline const GridEntry_s0065_35b0& medianRef(const GridEntry_s0065_35b0& a, const GridEntry_s0065_35b0& b, const GridEntry_s0065_35b0& c) {
    TypeGridEntrySort_s0065_35b0 cmp;
    if (cmp(a, b)) {
        if (cmp(b, c)) return b;
        else if (cmp(a, c)) return c;
        else return a;
    } else if (cmp(a, c)) {
        return a;
    } else if (cmp(b, c)) {
        return c;
    }
    return b;
}
void PartialSortA(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* middle, GridEntry_s0065_35b0* last);
extern "C" void* FUN_0065f810_s0065_35b0(int);                    // 0x0065f810
extern "C" void* AppSystem_s0065_35b0();                          // 0x0067dd00
struct cSPUIAssetGrid_s0065_35b0 {
    int GridScanFwd();
    int GridScanRev();
    void GridClear();
    void GridShutdown();
    bool CheckFlag();                     // 0x0064f320 (this = the grid)
    char HandleMessage(int wparam, unsigned lparam);  // 0x0064e680 (cSPUIAssetGrid::HandleMessage)
};
struct cSPUIAssetView {
    void* VerbCollect(unsigned enabled);
};
// ---- items of slice s006535b0 end

// ---- items of slice s00654730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00659340(void*);                  // 0x00659340
extern "C" void  FUN_0066b0c0(void*);                  // 0x0066b0c0
extern "C" void  FUN_00653ee0(void*, void*, void*);    // 0x00653ee0
extern "C" void  FUN_00650470(void*);                  // 0x00650470
extern "C" int   cTribeTool_GetTutorialToolPrice(void*, int, int);  // 0x004e1c30
extern "C" void* RBTreeIncrement(void* node);          // 0x00921580
extern "C" void  FUN_00652b00(void* vecEnd, char* node);  // 0x00652b00 (cdecl)
extern "C" bool  FUN_00668be0(void* item, void* str);     // 0x00668be0 (cdecl)
extern "C" void  FUN_00654490(int n);                     // 0x00654490 (cdecl)
extern "C" void  FUN_0064f3b0(void* out, void* src);      // 0x0064f3b0 (cdecl, ctor-into-slot)
extern "C" void  FUN_006535b0(void* vecEnd, void* src);   // 0x006535b0 (cdecl)
extern "C" void* FUN_006462b0(void* browser, void* item); // 0x006462b0 (thiscall)
void* operator new(unsigned int size);   // 0x00f47380
extern "C" void* FUN_0065f810_s0065_4730(int);                    // 0x0065f810  (vector<0x34-byte item>)
struct AssetGridTail {
    void UpdateScrolling(int flag);   // 0x0064fa20
    void UpdateAll();                 // 0x0064ecc0
    void UpdateScrollRegion();        // 0x006524a0
};
struct U8Vec;
struct GridHelper {
    void Reset0x644040(void* arg);   // 0x00644040
    bool IsEmpty(void);              // 0x00642910
    void Release0x64e7a0();          // 0x0064e7a0
    void Clear();                    // 0x006543a0
    void MergeEntries(void* begin, void* end, void* src);  // 0x006545d0 (cdecl)
    void Update0x650470();           // 0x00650470
    void Collect0x659340();          // 0x00659340
    void* FeedItems(void* flag);     // 0x0065f810
    bool IsKnownID();                // 0x00666420
};
struct EntryVec {
    void* mpBegin;                   // +0
    void* mpEnd;                     // +4
    void  InsertAt(void* pos, void* value, void* out);   // 0x00653de0 (thiscall)
    void* Erase(void* it);                                // 0x006534c0 (thiscall)
};
struct GridEntries {
    void* mpBegin;                   // +0
    void* mpEnd;                     // +4
    void* mpCapacity;                // +8
    void* ConstructInto(void* slot, void* src);   // 0x0064f3b0
    void* DoInsertValue(void* slot, void* src);   // 0x006535b0
    void  InsertEntry(void* pos, int count);      // 0x00652b00
    void  Reserve(int n);                         // 0x00654490
};
struct StopwatchHelper {
    long long GetElapsedTime();      // 0x0093a5e0
    void Restart();                  // 0x00571e80
};
struct U8Vec {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCapacity;
};
struct AssetGrid {
    void UpdateAssets(void* filter, void* feedItem);  // 0x00654730
    void OnSelectCommit(void* item, void* filter);  // 0x00654f50
};
struct GridEntry_s0065_4730 {
    char pad[0x18];
    float mPosition;   // +0x18
};
struct ItemSizeProvider {
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual int GetSize();   // +0x40
};
struct GridSource {
    char pad[0x20];
    ItemSizeProvider* mSizeProvider;   // +0x20
};
struct cSPUIAssetGrid_s0065_4730 {
    char pad108[0x108];
    float mItemWidth;         // +0x108
    char pad10c[0x1c];
    float mViewWidth;         // +0x128
    char pad12c[0x54];
    float mScroll;            // +0x180
    char pad184[4];
    float mMaxScroll;         // +0x188
    GridSource* mGridSource;  // +0x18c
    bool mFocusFlag;          // +0x190
    char pad191[0x55];
    bool mNeedsRebuild;       // +0x1e6
    char pad1e7[1];
    bool mNeedsReset;         // +0x1e8
    void* Find(uint32_t id);  // 0x006505d0
    void Rebuild();           // 0x006553b0
    void Refresh();           // 0x00654d00
    void ScrollTo(void* item); // 0x00654e20
};
// ---- items of slice s00654730 end

// ---- items of slice s00656310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_0(void* p);                           // 0x00f47380
extern "C" void* __cdecl copy_705250(const void* first, const void* last, void* dst);  // 0x00705250
struct cSPUIAssetView_s0065_6310 {
    char  b0[0xc];        // 0x00..0x0b
    float mTargetX;       // 0x0c
    float mTargetY;       // 0x10
    char  b14[0x1];       // 0x14
    char  mFirstUpdate;   // 0x15
    char  b16[0x1];       // 0x16
    bool  mResponds;      // 0x17
    char  b18[0x10];      // 0x18..0x27
    void* mWinShine;      // 0x28
    char  b2c[0x4];       // 0x2c..0x2f
    void* mThumb;         // 0x30
    void* mThumbBack;     // 0x34
    void* mName;          // 0x38
    char  b3c[0xc];       // 0x3c..0x47
    void* mPublished;     // 0x48
    void* mLocked;        // 0x4c
    void* mGameplayCont;  // 0x50
    void* mGameplayName;  // 0x54
    char  b58[0x30];      // 0x58..0x87
    void* mP88;           // 0x88
    void* mP8c;           // 0x8c
    void* mP90;           // 0x90
    char  b94[0x4c];      // 0x94..0xdf
    void* mE0;            // 0xe0
    char  bE4[0x10];      // 0xe4..0xf3
    bool  mBf4;           // 0xf4
    bool  mBf5;           // 0xf5
    bool  mBf6;           // 0xf6
    bool  mBf7;           // 0xf7

    int   IsAnimTargetDifferent();  // 0x006577a0 (cSPUIAssetView::IsAnimTargetDifferent)
    void  Show();  // 0x00657810 (cSPUIAssetView::Show)
    void  Hide();  // 0x00657870 (cSPUIAssetView::Hide)
    float GetHeight();  // 0x006578d0 (cSPUIAssetView::GetHeight)
    float GetWidth();  // 0x006578f0 (cSPUIAssetView::GetWidth)
    void  SetFirstUpdate(int b);  // 0x00657930 (cSPUIAssetView::SetFirstUpdate)
    void  SelectAsset(int a, char b, int c, char d, char e);  // 0x00657a30 (cSPUIAssetView::SelectAsset)
    void  m57460(bool b);  // 0x00657460 (cSPUIAssetView::m57460)
    void  m57640(void* a, void* b, void* c, void* d, void* e, void* f, void* res, void** dst, void* arg9);  // 0x00657640 (cSPUIAssetView::m57640)
    void  m56310(void* range);
};
struct KeyVecBase { void* mpBegin; KeyVecBase() : mpBegin(0) {} };
struct KeyVec_s0065_6310 : KeyVecBase {          // eastl::fixed_vector<unsigned int,30,1>
    void*         mpEnd;              // +0x04
    void*         mpCapacityEnd;      // +0x08
    void*         mAlloc;             // +0x0c
    void*         mAllocBuf;          // +0x10 (allocator's copy of the buffer)
    void*         mAllocSize;         // +0x14
    unsigned int  mStore[30];         // +0x18..0x8f
    unsigned char mFlag;              // +0x90
    KeyVec_s0065_6310();                         // default (inline)
    void Init(void* coll);            // 0x00653cf0 (out-of-line member)
    void Op654050(void* a, void* b, void* c);   // 0x00654050 (thiscall, 3 stack args)
};
inline KeyVec_s0065_6310::KeyVec_s0065_6310() {
    mAllocBuf = mStore;
    mpEnd = mStore;
    mpBegin = mStore;
    mpCapacityEnd = (char*)mStore + sizeof(mStore);
}
__forceinline KeyVec_s0065_6310 MakeKeys(void* first, void* last, void* extra) {
    KeyVec_s0065_6310 k;
    k.Op654050(first, last, extra);
    return k;
}
extern "C" void* __cdecl FUN_00656240(void* first, void* last, KeyVec_s0065_6310 v);
// ---- items of slice s00656310 end

// @ 0x00648aa0
void __cdecl sub_648b40()
{}

// @ 0x00648af0
Entry14* GridVec::EraseAt(Entry14* pos)
{
    if (pos + 1 < mpEnd)
        f646140(pos + 1, mpEnd, pos);
    --mpEnd;
    Entry14* const e = mpEnd;
    RefObj* const p10 = e->h10.p;
    if (p10)
        p10->Release();
    IRef2* const pC = e->h0c.p;
    if (pC)
        pC->Release();
    return pos;
}

// @ 0x00648b40
Entry14* GridVec::Insert(Entry14* pos, const Entry14& v)
{
    const uint32_t idx = (uint32_t)(pos - mpBegin);
    Entry14* const end = mpEnd;
    if ((pos == end) && (end != mpCapacity)) {
        mpEnd = end + 1;
        if (end)
            end->Construct(v);
    } else {
        InsertAt(pos, v);
    }
    return mpBegin + idx;
}

// @ 0x00648bb0
void __cdecl sub_648bb0()
{}

// @ 0x0064e5b0
void Outer168::Do()
{
    sub.method(0x80000000, 0xffffffff);
}

// @ 0x0064e5d0
void CellCalc::Compute(int index, float* out)
{
    int n = n110;
    if (n > 0) {
        float t = (f118 + f104) * (float)(index % n);
        int ti = _mm_cvtss_si32(_mm_set_ss(t));
        out[0] = (float)ti + f120;
        float u = (f11c + f108) * (float)(index / n);
        int ui = _mm_cvtss_si32(_mm_set_ss(u));
        out[1] = (float)ui + f124;
    }
}

// @ 0x0064e680
bool SP::cSPUIAssetGrid_s0064_dbd0::HandleMessage(unsigned msg, unsigned)
{
    switch (msg) {
    case 0xd43aca3c:
    case 0xd4937185:
    case 0xd4937186:
        f1e2 = true;
        f1e3 = true;
    }
    return true;
}

// @ 0x0064e6b0
bool RectF::Equal() const
{
    return a == c || b == d;
}

// @ 0x0064e6e0
C_e6e0::C_e6e0(const Key3* src, void* p2, void* p3, bool b1, bool b2)
{
    key = *src;
    this->p2 = p2;
    if (p2)
        ((void(__thiscall*)(void*))VT((char*)p2 + 0x10)[0])((char*)p2 + 0x10);
    this->p3 = p3;
    if (p3)
        ((void(__thiscall*)(void*))VT(p3)[0])(p3);
    this->b1 = b1;
    this->b2 = b2;
}

// @ 0x0064e740
C_e740::C_e740(void* p, bool b1, int n, bool b2, bool b3)
{
    this->p = p;
    if (p)
        ((void(__thiscall*)(void*))VT(p)[0])(p);
    this->b1 = b1;
    this->b3 = b3;
    this->n = n;
    this->b2 = b2;
}

// @ 0x0064e7a0
void R7a0::Reset()
{
    if (p) {
        if (p->child)
            ((X659340*)p->child)->Release();
        p = 0;
    }
    b100 = false;
}

// @ 0x0064e7d0
bool R7d0::Test(uint32_t idx)
{
    bool ok = false;
    uint32_t count = (uint32_t)((*(int*)((char*)this + 0xec) - *(int*)((char*)this + 0xe8)) >> 5);
    if (idx < count) {
        if (*(int*)((char*)this + 0x2c) != 0) {
            float f1 = *(float*)((char*)this + 0x108);
            float f2 = *(float*)(*(int*)((char*)this + 0xe8) + idx * 0x20 + 0x18);
            float f3 = *(float*)((char*)this + 0x184);
            void* o = *(void**)((char*)obj18c + 0x10);
            void* r = ((void*(__thiscall*)(void*, float, float))VT(o)[0x38 / 4])(o, f1 + f2, f2);
            if (!(f3 > f1 + f2)) {
                float hi = *(float*)((char*)r + 0xc) - *(float*)((char*)r + 4) + f3;
                if (!(f2 > hi))
                    ok = true;
            }
        }
    }
    return ok;
}

// @ 0x0064e880
void R880::Update(uint32_t visible, uint32_t arg)
{
    void* w1 = w30;
    if (w1) {
        ((void(__thiscall*)(void*, int, uint32_t))VT(w1)[0x7c / 4])(w1, 1, visible);
        if ((visible & 0xff) != 0) {
            if (w38) {
                *(uint32_t*)((char*)g_data15ee298 + 0x3c) = arg;
                void* p = w38;
                CStr14 s;
                ((void(__thiscall*)(void*))cString_ctor)(&s);
                ((void(__thiscall*)(void*, uint32_t, uint32_t, const wchar_t*))cString_Load)
                    (&s, 0x21671745, 0x30006, (const wchar_t*)0x13ffa78);
                ((void(__thiscall*)(void*, const wchar_t*))VT(p)[0x80 / 4])
                    (p, ((const wchar_t*(__thiscall*)(void*))cString_GetText)(&s));
                ((void(__thiscall*)(void*))cString_dtor)(&s);
            }
            void* w2 = w34;
            if (w2) {
                float v[4];
                v[3] = GetElapsedSeconds() * g_fNegTwo;
                v[0] = 0.0f;
                v[1] = 0.0f;
                v[2] = g_fOne;
                FUN_808230(w2, v);
            }
        }
    }
    void* w4 = w2c;
    if (w4)
        ((void(__thiscall*)(void*, int, int))VT(w4)[0x7c / 4])(w4, 1, ((visible & 0xff) == 0) ? 1 : 0);
}

// @ 0x0064e980
void R980::Layout(void* s1, void* s2, void* s3, bool flag)
{
    if (a3c) {
        if (!s1) s1 = (void*)0x13ec468;
        ((void(__thiscall*)(void*, void*))VT(a3c)[0x80 / 4])(a3c, s1);
    }
    if (a40) {
        if (!s2) s2 = (void*)0x13ec468;
        ((void(__thiscall*)(void*, void*))VT(a40)[0x80 / 4])(a40, s2);
    }
    if (a44) {
        if (!s3) s3 = (void*)0x13ec468;
        ((void(__thiscall*)(void*, void*))VT(a44)[0x80 / 4])(a44, s3);
    }
    void* p3c = a3c ? ((void*(__thiscall*)(void*, uint32_t))VT(a3c)[0xc / 4])(a3c, 0xf15f4bd) : 0;
    void* p40 = a40 ? ((void*(__thiscall*)(void*, uint32_t))VT(a40)[0xc / 4])(a40, 0xf15f4bd) : 0;
    void* p44 = a44 ? ((void*(__thiscall*)(void*, uint32_t))VT(a44)[0xc / 4])(a44, 0xf15f4bd) : 0;
    float tmp[4];
    ((void(__thiscall*)(void*, float*, int, int))VT(p3c)[0x20 / 4])(p3c, tmp, 0, 1);
    ((void(__thiscall*)(void*, float, float))VT(a44)[0x70 / 4])(a44, tmp[2] + 30.0f, tmp[1]);
    ((void(__thiscall*)(void*, float*, int, int))VT(p44)[0x20 / 4])(p44, tmp, 0, 1);
    ((void(__thiscall*)(void*, float, float))VT(a40)[0x70 / 4])(a40, tmp[2] + 30.0f, tmp[1]);
    ((void(__thiscall*)(void*, void*))VT(p44)[0x28 / 4])(p44,
        flag ? ((void*(__thiscall*)(void*))VT(p40)[0x24 / 4])(p40)
             : ((void*(__thiscall*)(void*))VT(p3c)[0x24 / 4])(p3c));
}

// @ 0x0064eaf0
void Eaf0::SetVisible(bool b)
{
    m14 = b;
    if (m1c)
        ((void(__thiscall*)(void*, int, bool))VT(m1c)[0x7c / 4])(m1c, 1, b);
    if (m20)
        ((void(__thiscall*)(void*, int, bool))VT(m20)[0x7c / 4])(m20, 1, b);
    if (m24)
        ((void(__thiscall*)(void*, int, bool))VT(m24)[0x7c / 4])(m24, 1, b);
    if (!b && m10c) {
        void* a = AppSystem_s0064_dbd0();
        ((void(__thiscall*)(void*, int))VT(a)[0x40 / 4])(a, 0);
        m10c = false;
    }
}

// @ 0x0064eb60
void SP::cSPUIAssetGrid_s0064_eb60::SetEntryState(int idx, bool force)
{
    cSPAssetView* v = (cSPAssetView*)FUN_0066a800(idx);
    if (v)
        ((void(__thiscall*)(void*))VT(v)[1])(v);

    bool b = false;
    if (m1a0 == idx) {
        if (v)
            b = *(char*)((char*)v + 0x20) == 0;
        else
            b = false;
    } else {
        m1a0 = idx;
        b = false;
    }
    if (force)
        b = true;
    if (!v)
        return;

    *(char*)((char*)v + 0x20) = b;
    m1e8 = true;

    if (idx != 0x18) {
        void* p = mWinArray[idx];
        if (p) {
            void* q = ((void*(__thiscall*)(void*, uint32_t))VT(p)[0x0c / 4])(p, 0x8ed27e7a);
            if (q) {
                ((void(__thiscall*)(void*, int, int))VT(q)[0x28 / 4])(q, 4, 1);
                ((void(__thiscall*)(void*, int, int))VT(q)[0x28 / 4])(q, 0x20, 1);
            }
        }
    }

    bool flag = true;
    if (*(void**)((char*)v + 0x0c) != *(void**)((char*)v + 0x10)) {
        // v+0x0c holds a wrapper whose first dword is the real object; the virtual
        // call is made on that inner object (retail dereferences one more level).
        void* w = *(void**)((char*)v + 0x0c);
        void* o = *(void**)w;
        bool c = ((bool(__thiscall*)(void*))VT(o)[0x1c / 4])(o);
        if (c == b)
            flag = false;
    }

    if (idx != 0x18 && mWinArray[idx] && m78 && m7c && m74) {
        // Retail homes the flag in the low byte of the caller-pushed `force` slot and
        // passes that whole dword: the byte is overwritten, the upper 24 bits are stale.
        unsigned int forcedw = *(unsigned int*)&force;
        ((void(__thiscall*)(void*, int, int))VT(m78)[0x7c / 4])(
            m78, 1, (int)((forcedw & 0xffffff00u) | (unsigned int)flag));
        ((void(__thiscall*)(void*, int, int))VT(m7c)[0x7c / 4])(m7c, 1, !flag);
        void* q = ((void*(__thiscall*)(void*))VT(m74)[0x10 / 4])(m74);
        ((void(__thiscall*)(void*, void*))VT(q)[0xdc / 4])(q, m74);
        ((void(__thiscall*)(void*, void*))VT(mWinArray[idx])[0xd8 / 4])(mWinArray[idx], m74);
    }
    ((void(__thiscall*)(void*))VT(v)[2])(v);
}

// @ 0x0064ecc0
void SP::cSPUIAssetGrid_s0064_eb60::UpdateAll()
{
    FlagKey f1, f2, f3, f4;

    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f1, 1, g_140042c);
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f2, 1, g_140042c);
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f3, 1, g_140042c);
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f4, 1, g_140042c);

    bool extra = false;

    if (m19c && me0) {
        f2 = *(FlagKey*)((char*)m19c + 0x158);
        f3 = *(FlagKey*)((char*)me0 + 0x44);
        f4 = ((AssetBrowserObj*)SP::AssetBrowser())->m1f0;

        for (int i = 0; i < 0x18; i += 6) {
            f1.mFlags[i + 0] = f2.mFlags[i + 0] && f3.mFlags[i + 0] && f4.mFlags[i + 0];
            f1.mFlags[i + 1] = f2.mFlags[i + 1] && f3.mFlags[i + 1] && f4.mFlags[i + 1];
            f1.mFlags[i + 2] = f2.mFlags[i + 2] && f3.mFlags[i + 2] && f4.mFlags[i + 2];
            f1.mFlags[i + 3] = f2.mFlags[i + 3] && f3.mFlags[i + 3] && f4.mFlags[i + 3];
            f1.mFlags[i + 4] = f2.mFlags[i + 4] && f3.mFlags[i + 4] && f4.mFlags[i + 4];
            f1.mFlags[i + 5] = f2.mFlags[i + 5] && f3.mFlags[i + 5] && f4.mFlags[i + 5];
        }

        if (f4.mValue != 0) {
            f1.mValue = f4.mValue;
            extra = f4.mExtra;
        } else {
            f1.mValue = f2.mValue;
            extra = f2.mExtra;
        }
    }

    if (me0) {
        char ok = ((char(__thiscall*)(void*, uint32_t))FUN_00661b10)(
            me0, *(uint32_t*)((char*)me0 + 0x18));
        if (!ok)
            f1.mFlags[5] = 0;
    }

    if (me0) {
        AssetBrowserObj* ab = (AssetBrowserObj*)SP::AssetBrowser();
        if (ab && ab->m1cc != 0 &&
            (ab->m1cc == 0x9ea3031au || ab->m1cc == 0x4178b8e8u)) {
            void* pv = ((void*(__thiscall*)(void*, int))FUN_0065f810)(me0, 0);
            char* pBegin = *(char**)pv;
            char* pEnd = *((char**)pv + 1);
            if (pBegin != pEnd) {
                bool all = true;
                int n = (int)(pEnd - pBegin) / 0x34;
                for (int i = 0; i < n; ++i) {
                    if (FUN_004bb860(*(uint32_t*)(pBegin + i * 0x34)) != 0x2b978c46u)
                        all = false;
                }
                if (!all)
                    goto AFTER;
            }
            f1.mFlags[13] = 1;
            f1.mFlags[14] = 1;
            f1.mFlags[15] = 1;
            f1.mFlags[16] = 1;
            f1.mFlags[17] = 1;
        }
    }

AFTER:
    int idx = FUN_0066a5c0(f1.mValue);
    if (idx == 0x18 || !f1.mFlags[idx]) {
        idx = FUN_0066a5c0(f2.mValue);
        extra = f2.mExtra;
    }
    if (idx == 0x18 || !f1.mFlags[idx]) {
        idx = FUN_0066a5c0(f3.mValue);
        extra = f3.mExtra;
    }
    if (m1a4 != idx || m1a0 == 0x18 || !f1.mFlags[m1a0])
        SetEntryState(idx, extra);
    m1a4 = idx;

    AssetBrowserObj* ab2 = (AssetBrowserObj*)SP::AssetBrowser();
    SP::cSPUIAnimator* animator = ab2 ? (SP::cSPUIAnimator*)ab2->m14 : 0;

    int position = 0;
    for (int i = 0; i < 0x18; ++i) {
        void* p = mWinArray[i];
        if (!p)
            continue;

        unsigned int uVar9;

        if (!f1.mFlags[i]) {
            // hide the window
            if (!animator) {
                ((void(__thiscall*)(void*, float, float))VT(p)[0x68 / 4])(p, 0.0f, 0.0f);
            } else {
                animator->RemoveAnimation(p, -1);
                AnimRawTmp tmp;
                float elapsed = GetElapsedSeconds(0.2f, 1, p, 0x9c1cab90u);
                AnimRawTmp* r = SPUICreateWindowAnimationTargetScale(
                    &tmp, p, 1.52587890625e-05f, elapsed);
                animator->AddAnimation(r, p, 0x9c1cab90u);
                if (tmp.mpRef)
                    ((AnimRef*)tmp.mpRef)->Release();
            }
            uVar9 = 1;
        } else {
            float fPos = (float)position * m134;
            ++position;
            if (!animator) {
                ((void(__thiscall*)(void*, float, float))VT(p)[0x64 / 4])(p, fPos, 0.0f);
                ((void(__thiscall*)(void*, float, float))VT(p)[0x68 / 4])(p, m12c, m130);
            } else {
                animator->RemoveAnimation(p, -1);
                if (!(((unsigned int(__thiscall*)(void*))VT(p)[0x28 / 4])(p) & 0x10)) {
                    AnimRawTmp tmp;
                    float elapsed = GetElapsedSeconds(0.2f, 2, p, 0x4b0531a7u);
                    AnimRawTmp* r = SPUICreateWindowAnimationTargetPosition(
                        &tmp, p, fPos, 0.0f, elapsed);
                    animator->AddAnimation(r, p, 0x4b0531a7u);
                    if (tmp.mpRef)
                        ((AnimRef*)tmp.mpRef)->Release();
                } else {
                    ((void(__thiscall*)(void*, float, float))VT(p)[0x64 / 4])(p, fPos, 0.0f);
                }
                AnimRawTmp tmp2;
                float elapsed2 = GetElapsedSeconds(0.2f, 2, p, 0x9c1cab90u);
                AnimRawTmp* r2 = SPUICreateWindowAnimationTargetScale(
                    &tmp2, p, 1.0f, elapsed2);
                animator->AddAnimation(r2, p, 0x9c1cab90u);
                if (tmp2.mpRef)
                    ((AnimRef*)tmp2.mpRef)->Release();
            }
            uVar9 = 0;
        }

        ((void(__thiscall*)(void*, int, unsigned int))VT(p)[0x7c / 4])(p, 0x10, uVar9);
    }
}

// @ 0x0064f280
int SP::cSPUIAssetGrid_s0064_eb60::IndexOfView(cSPAssetView* v)
{
    int i = 0;
    if (v) {
        int n = (int)(mpEntriesEnd - mpEntries);
        if (n > 0) {
            cSPAssetView** pv = (cSPAssetView**)((char*)mpEntries + 0x10);
            for (; i < n; ++i) {
                if (pv[0] == v)
                    return i;
                pv = (cSPAssetView**)((char*)pv + 0x20);
            }
        }
        i = -1;
    }
    return i;
}

// @ 0x0064f2c0
SP::cSPAssetGridEntry_s0064_eb60* SP::cSPUIAssetGrid_s0064_eb60::GetEntry(int i)
{
    return &mpEntries[i];
}

// @ 0x0064f320
bool SP::cSPUIAssetGrid_s0064_eb60::CheckFlag()
{
    if (!m19c)
        return m1b8;
    return m1b8 && ((ViewState*)m19c)->f16;
}

// @ 0x0064f350
unsigned char ParseHelper(void* obj, int a, unsigned char def)
{
    if (obj) {
        bool ok = ((bool(__thiscall*)(void*, int, void**))VT(obj)[0x24 / 4])(obj, a, &obj);
        if (ok) {
            unsigned short w = *(unsigned short*)((char*)obj + 0x12);
            if (w == 1 || w == 0x10) {
                // Retail's byte return keeps the high bits of the pointer it read through
                // in eax (the caller-visible return value is 16-bit compared by the
                // harness), so each arm reproduces that leftover explicitly.
                if (*(unsigned char*)((char*)obj + 0x10) & 0x30) {
                    unsigned int p = *(unsigned int*)obj;
                    return (unsigned char)((p & 0xffffff00u) | *(unsigned char*)p);
                }
                unsigned int q = w ? (unsigned int)obj : 0;
                return (unsigned char)((q & 0xffffff00u) | *(unsigned char*)q);
            }
            return (unsigned char)(0x15d9c00u | *(unsigned char*)0x15d9c70);
        }
    }
    return def;
}

// @ 0x0064f540
void InsertionSortEntries(SP::cSPAssetGridEntry_s0064_eb60* first, SP::cSPAssetGridEntry_s0064_eb60* last, SP::TypeGridEntrySort* compare)
{
    if (first != last) {
        SP::cSPAssetGridEntry_s0064_eb60* iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const SP::cSPAssetGridEntry_s0064_eb60 temp(*iSorted);
            SP::cSPAssetGridEntry_s0064_eb60* iNext = iSorted;
            SP::cSPAssetGridEntry_s0064_eb60* iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && (*compare)(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x0064f630
void InsertionSortSimpleEntries(SP::cSPAssetGridEntry_s0064_eb60* first, SP::cSPAssetGridEntry_s0064_eb60* last, SP::TypeGridEntrySort* compare)
{
    if (first == last)
        return;
    for (SP::cSPAssetGridEntry_s0064_eb60* p = first; p != last; ++p) {
        const SP::cSPAssetGridEntry_s0064_eb60 temp(*p);
        SP::cSPAssetGridEntry_s0064_eb60* dest = p;
        SP::cSPAssetGridEntry_s0064_eb60* prev = p - 1;
        while ((*compare)(temp, *prev)) {
            *dest = *prev;
            --dest;
            --prev;
        }
        *dest = temp;
    }
}

// @ 0x0064f730
SP::cSPAssetGridEntry_s0064_eb60** UninitCopyOut(SP::cSPAssetGridEntry_s0064_eb60** pOut, SP::cSPAssetGridEntry_s0064_eb60* first, SP::cSPAssetGridEntry_s0064_eb60* last, SP::cSPAssetGridEntry_s0064_eb60* initial)
{
    *pOut = initial;
    if (first != last) {
        do {
            SP::cSPAssetGridEntry_s0064_eb60* d = *pOut;
            if (d)
                ::new (d) SP::cSPAssetGridEntry_s0064_eb60(*first);
            *pOut = d + 1;
            ++first;
        } while (first != last);
    }
    return pOut;
}

// @ 0x0064f7c0
SP::cSPAssetGridEntry_s0064_eb60* UninitCopyEntries(SP::cSPAssetGridEntry_s0064_eb60* first, SP::cSPAssetGridEntry_s0064_eb60* last, SP::cSPAssetGridEntry_s0064_eb60* result)
{
    if (first != last) {
        do {
            if (result)
                ::new (result) SP::cSPAssetGridEntry_s0064_eb60(*first);
            ++first;
            ++result;
        } while (first != last);
    }
    return result;
}

// @ 0x0064f840
SP::cSPAssetGridEntry_s0064_eb60* DestroyEntries(SP::cSPAssetGridEntry_s0064_eb60* first, SP::cSPAssetGridEntry_s0064_eb60* last, SP::cSPAssetGridEntry_s0064_eb60* result)
{
    if (first != last) {
        do {
            first->~cSPAssetGridEntry_s0064_eb60();
            ++first;
            ++result;
        } while (first != last);
    }
    return result;
}

// @ 0x0064f8d0
void UninitFillNEntries(SP::cSPAssetGridEntry_s0064_eb60* dest, unsigned int n, const SP::cSPAssetGridEntry_s0064_eb60* value)
{
    while (n--) {
        if (dest)
            ::new (dest) SP::cSPAssetGridEntry_s0064_eb60(*value);
        ++dest;
    }
}

// @ 0x0064f990
void PromoteHeapEntries(SP::cSPAssetGridEntry_s0064_eb60* first, int topPosition, int position, SP::cSPAssetGridEntry_s0064_eb60 value, SP::TypeGridEntrySort* compare)
{
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && (*compare)(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// @ 0x0064fa20
void __fastcall sub_64fa20(void*)
{}

// @ 0x0064fc40
void __fastcall sub_64fc40(void*)
{}

// @ 0x0064fd00
void __fastcall sub_64fd00(void*)
{}

// @ 0x0064fde0
void __fastcall sub_64fde0(void*)
{}

// @ 0x0064ff90
void __fastcall sub_64ff90(void*)
{}

// @ 0x00650020
void __fastcall sub_650020(void*)
{}

// @ 0x00650190
void __fastcall sub_650190(void*)
{}

// @ 0x00650470
void __fastcall sub_650470(void*)
{}

// @ 0x006505d0
GridEntry* Grid::Find(uint32_t id)
{
    int index = -1;
    if (id == 0) {
        index = 0;
    } else {
        const int n = (int)(mpEnd - mpBegin);
        for (int i = 0; i < n; ++i) {
            if (mpBegin[i].mID == id) {
                index = i;
                break;
            }
        }
    }
    if (index == -1)
        return 0;
    return &mpBegin[index];
}

// @ 0x00650630
void ReloadCallback(cSPUIAssetGrid* self, void* unused, bool bLoad)
{
    if (!bLoad) {
        if (self->mWin48.mpObject && self->mWinRoot.mpObject && self->mWinParent.mpObject) {
            self->mWinRoot.mpObject->RemoveWindow(self->mWin48.mpObject);
            self->mWinParent.mpObject->AddWindow(self->mWin48.mpObject);
        }
        if (self->mWin4c.mpObject && self->mWinGrid.mpObject && self->mWinParent.mpObject) {
            self->mWinGrid.mpObject->RemoveWindow(self->mWin4c.mpObject);
            self->mWinParent.mpObject->AddWindow(self->mWin4c.mpObject);
        }
        if (self->mFeedFilter.mpObject) {
            self->mFeedFilter.mpObject->Shutdown();
            self->mFeedFilter = 0;
        }
        if (self->mSearchBox.mpObject) {
            self->mSearchBox.mpObject->Shutdown();
            self->mSearchBox = 0;
        }
        if (self->mWinMessagePrimary.mpObject)
            self->mWinMessagePrimary.mpObject->RemoveWinProc(self);
        if (self->mWin48.mpObject)
            self->mWin48.mpObject->RemoveWinProc(self);
        if (self->mWinMessageSecondary.mpObject)
            self->mWinMessageSecondary.mpObject->RemoveWinProc(self);
        if (self->mWin5c.mpObject)
            self->mWin5c.mpObject->RemoveWinProc(self);
        if (self->mScrollFrame.mpObject) {
            self->mScrollFrame.mpObject->mpClientParent->GetParent()->RemoveWinProc(self);
            self->mScrollFrame.mpObject->Shutdown();
            self->mScrollFrame = 0;
        }
        return;
    }

    self->mWinMessagePrimary = self->mLayout->FindWindowByID(0xf3c6dc19, true);
    if (self->mWinMessagePrimary.mpObject)
        self->mWinMessagePrimary.mpObject->AddWinProc(self);
    self->mWin48 = self->mLayout->FindWindowByID(0x06737ba8, true);
    if (self->mWin48.mpObject)
        self->mWin48.mpObject->AddWinProc(self);
    self->mWin4c = self->mLayout->FindWindowByID(0x07d13d20, true);
    self->mWinMessageSecondary = self->mLayout->FindWindowByID(0xf3c6d819, true);
    if (self->mWinMessageSecondary.mpObject)
        self->mWinMessageSecondary.mpObject->AddWinProc(self);
    self->mWin50 = self->mLayout->FindWindowByID(0x14248528, true);
    self->mWin54 = self->mLayout->FindWindowByID(0x34346c9e, true);
    self->mWin58 = self->mLayout->FindWindowByID(0x14936ecb, true);
    self->mWin68 = self->mLayout->FindWindowByID(0x05949e98, true);
    self->mWin6c = self->mLayout->FindWindowByID(0x07e31d60, true);
    self->mWin70 = self->mLayout->FindWindowByID(0x2218130a, true);

    for (int i = 0; i < 24; ++i) {
        self->mWinArr[i] = self->mLayout->FindWindowByID(g_GridWinIDs[i], true);
        if (!self->mWinArr[i].mpObject) {
            GridRow* row = LookupRow(i);
            if (row) {
                unsigned int instance = row->mInstance;
                unsigned int useGroup = row->mUseGroup;
                unsigned int group = row->mGroup;
                if (instance) {
                    cSPUILayout_s0065_0630* dlg = new ("Sporepedia", 0, 0, 0, 0) cSPUILayout_s0065_0630();
                    if (dlg)
                        dlg->AddRef();
                    ResourceKey key;
                    key.mInstanceID = instance;
                    key.mGroupID = group;
                    key.mTypeID = 0x0510a95b;
                    dlg->Init(&key, true, 0x05b598fa);
                    unsigned int id = row->mDefaultID;
                    if (useGroup)
                        id = group;
                    IWindow* win = dlg->FindWindowByID(id, true);
                    if (win) {
                        win->AddRef();
                        if (self->mWin70.mpObject) {
                            win->GetParent()->RemoveWindow(win);
                            self->mWin70.mpObject->AddWindow(win);
                            self->mWinArr[i].AssignFromPtr(&win);
                        }
                        win->Release();
                    }
                    if (dlg)
                        dlg->Release();
                }
            }
        }
    }

    self->mWin74 = self->mLayout->FindWindowByID(0x07ce5010, true);
    self->mWin78 = self->mLayout->FindWindowByID(0x07ce2701, true);
    self->mWin7c = self->mLayout->FindWindowByID(0x07ce2700, true);

    {
        float* a = self->mWinArr[0].mpObject->GetArea();
        self->mCellWidth = a[2] - a[0];
    }
    {
        float* a = self->mWinArr[0].mpObject->GetArea();
        self->mCellHeight = a[3] - a[1];
    }
    {
        float* a = self->mWin70.mpObject->GetArea();
        self->mScrollWidth = a[2] - a[0];
    }

    if (self->mWin6c.mpObject && self->mWin70.mpObject) {
        IWindow* w = self->mWin6c.mpObject;
        if (w) {
            IWindowControl* ctl = w->GetControl(0x0f15f4bd);
            if (ctl) {
                float* r1 = self->mWin6c.mpObject->GetRealArea();
                float left1 = r1[0];
                float right1 = r1[2];
                ctl->vf5(0);
                float* r2 = self->mWin6c.mpObject->GetRealArea();
                float left2 = r2[0];
                float right2 = r2[2];
                float* r3 = self->mWin70.mpObject->GetRealArea();
                float dx = (right2 - left2) - (right1 - left1);
                self->mWin70.mpObject->SetPosition(dx + r3[0], r3[1]);
            }
        }
    }

    self->mWin5c = self->mLayout->FindWindowByID(0x14580f81, true);
    if (self->mWin5c.mpObject)
        self->mWin5c.mpObject->AddWinProc(self);
    self->mWin60 = self->mLayout->FindWindowByID(0x065666c8, true);
    self->mWin64 = self->mLayout->FindWindowByID(0x065666c0, true);

    bool bUseFeedFilter = false;
    AutoRefCount<IPropertyList> props;
    IPropertyManager* pm = PropertyManager();
    pm->GetPropertyList(0xb55619c2, 0x851d4139, &props);
    if (props.mpObject) {
        IProperty* prop;
        if (props.mpObject->GetProperty(0x6dcfc1b5, &prop)) {
            if (prop->type == 1)
                bUseFeedFilter = PropBool(prop);
        }
    }

    if (self->mWin54.mpObject && bUseFeedFilter) {
        cSPUIFeedFilter* ff = new ("UI", 0, 0, 0, 0) cSPUIFeedFilter();
        self->mFeedFilter = ff;
        self->mFeedFilter.mpObject->Init(self->mWin54.mpObject, 0xbda06a7c);
        self->mFeedFilter.mpObject->SetVisible(true);
    }
    if (self->mWin58.mpObject) {
        cSPUISearchBox* sb = new ("UI", 0, 0, 0, 0) cSPUISearchBox();
        self->mSearchBox = sb;
        self->mSearchBox.mpObject->Init(self->mWin58.mpObject);
        self->mSearchBox.mpObject->SetVisible(true);
    }

    self->mWinFeedHeader = self->mLayout->FindWindowByID(0x0654fce8, true);
    self->mWinFeedFilter = self->mLayout->FindWindowByID(0x0654fdd0, true);
    self->mWinSearch = self->mLayout->FindWindowByID(0x065402b0, true);
    self->mWinSortButtonsParent = self->mLayout->FindWindowByID(0x13d704e1, true);
    self->mWinBtnMakeNew = self->mLayout->FindWindowByID(0x53da7eec, true);
    self->mWin44 = self->mLayout->FindWindowByID(0x07aa9f70, true);

    if (self->mWinMessagePrimary.mpObject)
        SetWindowAreaToParent(self->mWinMessagePrimary.mpObject);

    ScrollFrameVertical* sf = new ("UI/ScrollFrameVertical", 0, 0, 0, 0) ScrollFrameVertical();
    self->mScrollFrame = sf;
    if (self->mScrollFrame.mpObject->CreateScrollFrameVertical(0xaef7d6ba, 0, (char*)self + 8)) {
        IWindow* host = self->mLayout->FindWindowByID(0x5460f69c, true);
        IWindow* scrollWin = self->mScrollFrame.mpObject->mpScrollWindow;
        IWindow* client = self->mScrollFrame.mpObject->mpClientParent;
        host->AddWindow(scrollWin);
        host->vf59(scrollWin);
        scrollWin->SetArea(self->mWinMessageSecondary.mpObject->GetRealArea());
        self->mWinMessageSecondary.mpObject->GetParent()->RemoveWindow(self->mWinMessageSecondary.mpObject);
        client->AddWindow(self->mWinMessageSecondary.mpObject);
        self->mWinMessageSecondary.mpObject->SetPos(0.0f, 0.0f);
        IWindow* clientParent = client->GetParent();
        if (clientParent)
            clientParent->AddWinProc(self);
        self->mScrollFrame.mpObject->mpControl->vf7(true, true);
    } else {
        self->mScrollFrame = 0;
    }
}

// @ 0x006511b0
namespace eastl {
template <typename It, typename Compare> void insertion_sort(It first, It last, Compare compare)
{
    if (first != last) {
        It iCurrent, iNext, iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const GridEntry_s0065_0630 temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}
}  // namespace eastl

// @ 0x00651390
namespace eastl {
template <typename It, typename Compare> void insertion_sort_unguarded(It first, It last, Compare compare)
{
    for (It i = first; i != last; ++i) {
        const GridEntry_s0065_0630 temp(*i);
        It iNext = i;
        It iCurrent = i - 1;
        while (compare(temp, *iCurrent)) {
            *iNext = *iCurrent;
            --iNext;
            --iCurrent;
        }
        *iNext = temp;
    }
}
}  // namespace eastl

// @ 0x006515a0
namespace eastl {
template <typename T, typename Compare> __declspec(noinline) const T& median(const T& a, const T& b, const T& c, Compare compare)
{
    if (compare(a, b)) {
        if (compare(b, c)) return b;
        else if (compare(a, c)) return c;
        else return a;
    } else if (compare(a, c)) return a;
    else if (compare(b, c)) return c;
    return b;
}
}  // namespace eastl

// @ 0x006516a0
namespace eastl {
template <typename It, typename Distance, typename T, typename Compare> __declspec(noinline) void adjust_heap_ref(It first, Distance topPosition, Distance heapSize, Distance position, T value, Compare& compare)
{
    Distance childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    eastl::promote_heap_ref<It, Distance, T, Compare>(first, topPosition, position, value, compare);
}
}  // namespace eastl

// @ 0x006517c0
namespace eastl {
template <typename It, typename Distance, typename T, typename Compare> __declspec(noinline) void promote_heap(It first, Distance topPosition, Distance position, T value, Compare compare)
{
    for (Distance parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}
}  // namespace eastl

// @ 0x00651910
namespace eastl {
template <typename It, typename Compare> __declspec(noinline) void pop_heap_ref(It first, It last, Compare& compare)
{
    const GridEntry_s0065_15a0 tempBottom(*(last - 1));
    *(last - 1) = *first;
    eastl::adjust_heap_ref<It, int, GridEntry_s0065_15a0, Compare>(first, 0, (int)(last - first - 1), 0,
                                                        tempBottom, compare);
}
}  // namespace eastl

// @ 0x00651990
cSPUIAssetGrid_s0065_15a0::cSPUIAssetGrid_s0065_15a0()
: mIsVisible(false),
      mFC(0), m100(false), m104(0.0f), m108(0.0f), m10c(false), m110(0), m114(0),
      m118(0.0f), m11c(0.0f), m120(0.0f), m124(0.0f), m128(0.0f), m12c(0.0f), m130(0.0f), m134(0.0f),
      mTimerA(4, 0), mTimerB(4, 0),
      m180(0.0f), m184(0.0f), m188(0.0f), m190(false), m194(1), m198(1),
      m1a0(0x18), m1a4(1), m1a8(0), m1ac(0), m1b0(0), m1b4(0),
      m1b8(false), m1b9(false), m1ba(false), m1bb(false),
      m1c4(0), m1c8(0), m1cc(0),
      m1e4(false), m1e5(false), m1e6(false), m1e7(false), m1e8(false)
{
}

// @ 0x00651c80
cSPUIAssetGrid_s0065_15a0::~cSPUIAssetGrid_s0065_15a0()
{
    if (m10c) {
        AppSystem()->SetFlag(0);
        m10c = false;
    }
}

// @ 0x00651f30
float GridSub8::ContentHeight(float width)
{
    if (mpBegin == mpEnd)
        return 0.0f;
    Rect* r = w24->GetArea();
    float top = r->t;
    float bottom = r->b;
    w24->SetSize(width, bottom - top);
    cSPUIAssetGrid_s0065_15a0* g = (cSPUIAssetGrid_s0065_15a0*)((char*)this - 8);
    g->ComputeCardLayoutParameters();
    int across = m1a8;
    int rows = across - 1;
    ScrollFrame* f = (ScrollFrame*)g->w19c.mpObject;
    bool cond;
    if (f == 0)
        cond = g->m1b8;
    else
        cond = g->m1b8 && *((char*)f + 0x16);
    if (cond) rows++;
    if (across != m1a4) rows++;
    float t[2];
    g->FUN_64e5d0(rows, t);
    return m120 + m114 + m100 + t[1];
}

// @ 0x00651ff0
void cSPUIAssetGrid_s0065_15a0::SetupWindows(IWindow_s0065_15a0* a, IWindow_s0065_15a0* b, IWindow_s0065_15a0* c)
{
    FUN_66bd00();
    w1c.Set((IWin*)a);
    w20.Set(b);
    w24.Set(c);

    void* mem = EASTL_allocator_allocate(0x108, g_assetViewName, 0, 0, 0, 0);
    AssetView* view = mem ? AssetView_ctor(mem) : 0;
    if (view) view->AddRef();
    view->Attach((IWindow_s0065_15a0*)w1c.mpObject, 0, 0, 0);
    view->Layout(0, 0);
    m108 = view->GetHeight();
    m104 = view->GetWidth();
    view->Detach();
    view->Release();

    void* lmem = EASTL_allocator_allocate(0x18, "Sporepedia", 0, 0, 0, 0);
    ILayout* layout = lmem ? Layout_ctor(lmem) : 0;
    mLayout.Set(layout);
    unsigned int key[3];
    key[0] = g_layoutKeyId;
    key[1] = 0xd525562b;
    key[2] = 0x510a95b;
    mLayout.mpObject->Init(key, 1, 0x5b598fa);
    mLayout.mpObject->SetParentWin((IWindow_s0065_15a0*)w1c.mpObject, 1, 0x5b598fa);
    mLayout.mpObject->SetReloadCallback((void*)ReloadCallback, this);
    ReloadCallback(this, mLayout.mpObject, 1);

    if (w48.mpObject && w20.mpObject) {
        Rect rc;
        GetBoundingScreenRect(&rc, w48.mpObject, 0);
        w48.mpObject->GetParent()->SetPoint(w48.mpObject);
        w20.mpObject->SetParentWin(w48.mpObject);
        Vec2 o1, o2;
        Vec2 p2(rc.r, rc.b);
        Vec2* r1 = w20.mpObject->ConvertPoint(&o1, Vec2(rc.l, rc.t));
        float x1 = r1->x, y1 = r1->y;
        Vec2* r2 = w20.mpObject->ConvertPoint(&o2, p2);
        rc.l = x1; rc.t = y1; rc.r = r2->x; rc.b = r2->y;
        w48.mpObject->SetArea(&rc);
    }
    if (w4c.mpObject && w24.mpObject) {
        Rect rc;
        GetBoundingScreenRect(&rc, w4c.mpObject, 0);
        w4c.mpObject->GetParent()->SetPoint(w4c.mpObject);
        w24.mpObject->SetParentWin(w4c.mpObject);
        Vec2 o1, o2;
        Vec2 p2(rc.r, rc.b);
        Vec2* r1 = w24.mpObject->ConvertPoint(&o1, Vec2(rc.l, rc.t));
        float x1 = r1->x, y1 = r1->y;
        Vec2* r2 = w24.mpObject->ConvertPoint(&o2, p2);
        rc.l = x1; rc.t = y1; rc.r = r2->x; rc.b = r2->y;
        w4c.mpObject->SetArea(&rc);
    }

    mTimerA.Start();
    mTimerB.Start();

    void* handler = (char*)this + 4;
    IMsgServer* server = MessageServer();
    mHandler.mpServer = server;
    mHandler.mpHandler = handler;
    mHandler.mpIdArray = g_msgIds;
    mHandler.mCount = 3;
    mHandler.mX = 0;
    if (server && handler) {
        for (unsigned int i = 0; i < 0xc; i += 4)
            server->AddHandler(handler, *(const unsigned int*)((const char*)g_msgIds + i));
    }
}

// @ 0x006524a0
void cSPUIAssetGrid_s0065_15a0::UpdateScrollRegion()
{
    if (w18c.mpObject && w2c.mpObject) {
        Rect* p = w2c.mpObject->GetArea();
        Rect rc;
        rc.l = p->l; rc.t = p->t; rc.r = p->r; rc.b = p->b;
        w18c.mpObject->UpdateVertical(0);
        IWinScrollbar* sb = w18c.mpObject->mScrollbar;
        int hi = sb->GetMax();
        int lo = sb->GetMin();
        m188 = (float)(hi - lo);
        Rect* q = w18c.mpObject->mArea->GetArea();
        rc.r = q->Width() + q->l;
        w2c.mpObject->SetArea(&rc);
    }
    UpdateScrolling(0);
    FUN_650470();
}

// @ 0x006528f0
void StatsGrid::UpdateStatsText()
{
    if (!mIsVisible)
        return;
    if (!AssetBrowser())
        return;

    cString msg;
    *(unsigned int*)((char*)g_uiCtx + 0x28) = mA;
    *(unsigned int*)((char*)g_uiCtx + 0x2c) = mB;
    if (mA == mB)
        msg.Load(0x21671745, 0x30003, L"*Displaying n items.*");
    else
        msg.Load(0x21671745, 0x30005, L"*Displaying n of n items.*");

    const wchar_t* p = msg.c_str();
    const wchar_t* e = p;
    while (*e)
        ++e;
    WString_Assign(&msg, p, e);

    if (mCount == 0) {
        msg = L"";
    }

    unsigned int selected = 0;
    void* browser = AssetBrowser();
    unsigned int browserFlags = *(unsigned int*)((char*)browser + 0x20);
    void* items = FUN_00644a70(browser);
    int num = (*(int*)((char*)items + 4) - *(int*)items) / 0x14;  // element size 0x14
    if (browserFlags != 1 && num > 0) {
        *(unsigned int*)((char*)g_uiCtx + 0x34) = (unsigned int)num;
        cString sel;
        sel.Load(0x6f5943eb, 0x2000002, L"*Selected n items.*");
        msg = sel.c_str();
        if (browserFlags > 1 && (unsigned int)num > browserFlags)
            selected = 1;
        else
            selected = 0;
    }
    Scrollbar(mA, mB, selected, 0);
    msg.c_str();
}

// @ 0x00652ba0
GridVec_s0065_25d0& GridVec_s0065_25d0::operator=(const GridVec_s0065_25d0& x)
{
    if (this != &x) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCapacity - mpBegin)) {
            GridEntry_s0065_25d0* pNewData = ReallocateAndCopy(n, x.mpBegin, x.mpEnd);
            DoDestroyValues(mpBegin, mpEnd);
            if (mpBegin && ((unsigned*)mpBegin)[-1])
                EASTL_allocator_deallocate(mpBegin);
            mpBegin = pNewData;
            mpEnd = pNewData + n;
            mpCapacity = pNewData + n;
        } else if ((unsigned)(mpEnd - mpBegin) < n) {
            CopyRange(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitializedCopy(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            mpEnd = mpBegin + n;
        } else {
            CopyRange(x.mpBegin, x.mpEnd, mpBegin);
            DoDestroyValues(mpBegin + n, mpEnd);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// @ 0x00652c90
void GridVec_s0065_25d0::DoInsertValues(GridEntry_s0065_25d0* position, unsigned n, const GridEntry_s0065_25d0& value)
{
    if (n == 0)
        return;
    if ((unsigned)(mpCapacity - mpEnd) < n) {
        const unsigned nSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNew = nSize + n;
        unsigned grow = nSize * 2;
        if (nSize == 0)
            grow = 1;
        if (nNew < grow)
            nNew = grow;
        GridEntry_s0065_25d0* pNewData =
            (GridEntry_s0065_25d0*)EASTL_allocator_allocate(nNew * sizeof(GridEntry_s0065_25d0), "Editor", 0, 0,
                                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                                 "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                                 "EASTL/allocator.h",
                                                 0xd1);
        GridEntry_s0065_25d0* pNewEnd = UninitializedCopy(mpBegin, position, pNewData);
        UninitializedFillN(pNewEnd, n, value, 0);
        pNewEnd += n;
        UninitializedCopy(position, mpEnd, pNewEnd);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nSize + n;
        mpCapacity = pNewData + nNew;
    } else {
        GridEntry_s0065_25d0 temp(value);
        const unsigned nEnd = (unsigned)(mpEnd - position);
        if (n < nEnd) {
            UninitializedCopy(mpEnd - n, mpEnd, mpEnd);
            CopyBackward(position, mpEnd - n, mpEnd);
            mpEnd += n;
            FillRange(position, position + n, temp);
        } else {
            UninitializedFillN(mpEnd, n - nEnd, temp, 0);
            mpEnd += n - nEnd;
            UninitializedCopy(position, mpEnd - n, mpEnd);
            mpEnd += nEnd;
            FillRange(position, mpEnd - n, temp);
        }
    }
}

// @ 0x006534c0
GridEntry_s0065_25d0* GridVec_s0065_25d0::erase(GridEntry_s0065_25d0* position)
{
    if ((position + 1) < mpEnd)
        CopyRange(position + 1, mpEnd, position);
    mpEnd -= 1;
    mpEnd->~GridEntry_s0065_25d0();
    return position;
}

// @ 0x00653510
void GridVec_s0065_25d0::swap(GridVec_s0065_25d0& other)
{
    if (mpBegin == 0 || ((unsigned*)mpBegin)[-1] != 0 ||
        other.mpBegin == 0 || ((unsigned*)other.mpBegin)[-1] != 0) {
        GridEntry_s0065_25d0* t0 = mpBegin; mpBegin = other.mpBegin; other.mpBegin = t0;
        GridEntry_s0065_25d0* t1 = mpEnd; mpEnd = other.mpEnd; other.mpEnd = t1;
        GridEntry_s0065_25d0* t2 = mpCapacity; mpCapacity = other.mpCapacity; other.mpCapacity = t2;
    } else {
        GridVec_s0065_25d0 temp;
        temp = *this;
        *this = other;
        other = temp;
        temp.DoDestroyValues(temp.mpBegin, temp.mpEnd);
        if (temp.mpBegin && ((unsigned*)temp.mpBegin)[-1])
            EASTL_allocator_deallocate(temp.mpBegin);
    }
}

// @ 0x006535b0
void GridVec_s0065_35b0::DoInsertValue(GridEntry_s0065_35b0* position, const GridEntry_s0065_35b0& value)
{
    if (mpEnd != mpCapacity) {
        const GridEntry_s0065_35b0* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new ((void*)mpEnd) GridEntry_s0065_35b0(*(mpEnd - 1));
        CopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = (nPrevSize == 0) ? 1 : nPrevSize * 2;
        GridEntry_s0065_35b0* pNewData = nNewSize
            ? (GridEntry_s0065_35b0*)EASTL_allocator_allocate(nNewSize * sizeof(GridEntry_s0065_35b0), "Editor", 0, 0,
                                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                                   "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                                   "EASTL/allocator.h",
                                                   0xd1)
            : 0;
        GridEntry_s0065_35b0* pNewEnd = UninitializedCopy(mpBegin, position, pNewData);
        DestroyRange(mpBegin, position, pNewData);
        if (pNewEnd)
            ::new ((void*)pNewEnd) GridEntry_s0065_35b0(value);
        pNewEnd += 1;
        GridEntry_s0065_35b0* pEnd = UninitializedCopy(position, mpEnd, pNewEnd);
        DestroyRange(position, mpEnd, pNewEnd);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x006536e0
int* Filter16(int* p, int* end, int* keysBegin, int* keysEnd, int* unused5, int* unused6, char* attr)
{
    for (; p != end; p += 4) {
        if (SetAssetData((void*)p[1], 0)) {
            int* lo = keysBegin;
            int n = (int)(keysEnd - keysBegin);
            while (n > 0) {
                int half = n >> 1;
                if (lo[half] < (unsigned)p[1]) {
                    lo = lo + half + 1;
                    n = n - 1 - half;
                } else {
                    n = half;
                }
            }
            if ((lo == keysEnd) || ((unsigned)p[1] < (unsigned)*lo) || (lo == lo + 1))
                break;
        }
    }
    if (keysBegin && keysBegin != (int*)attr)
        EASTL_allocator_deallocate(keysBegin);
    return p;
}

// @ 0x00653780
void* Filter16Copy(int* p, int* end, int* out, int* keysBegin, int* keysEnd, char* attr)
{
    for (; p != end; p += 4) {
        if (!SetAssetData((void*)p[1], 0)) {
            // keep predicate false -> skip
        } else {
            int* lo = FUN_00555a20(keysBegin, keysEnd, p + 1, *attr);
            if (!((lo != keysEnd && *lo <= (unsigned)p[1]) && (lo != lo + 1)))
                continue;
        }
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2]; out[3] = p[3];
        out += 4;
    }
    if (keysBegin && (char*)keysBegin != attr)
        EASTL_allocator_deallocate(keysBegin);
    return out;
}

// @ 0x00653820
void QuickSortImplB(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, int kRecursionCount)
{
    while (((last - first) > kQuickSortLimit) && (kRecursionCount > 0)) {
        GridEntry_s0065_35b0* mid = first + (last - first) / 2;
        const GridEntry_s0065_35b0* p = &medianRef(*first, *mid, *(last - 1));
        GridEntry_s0065_35b0* position = GetPartitionB(first, last, *p);
        QuickSortImplB(position, last, --kRecursionCount);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortB(first, last, last);
}

// @ 0x00653960
void PartialSortA(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* middle, GridEntry_s0065_35b0* last)
{
    MakeHeapA(first, middle);
    for (GridEntry_s0065_35b0* i = middle; i < last; ++i) {
        if (CompareA()(*i, *first)) {
            GridEntry_s0065_35b0 temp(*i);
            *i = *first;
            AdjustHeapA(first, 0, (int)(middle - first), 0, temp);
        }
    }
    SortHeapA(first, middle);
}

// @ 0x00653b80
int cSPUIAssetGrid_s0065_35b0::GridScanFwd()
{
    void* self = this;
    AssetBrowser();
    int* info = (int*)FUN_00644a70(0);
    int* b = (int*)info[0];
    int* e = (int*)info[1];
    if (b == e)
        return -1;
    char* gridBegin = (char*)*(void**)((char*)self + 0xe8);
    char* gridEnd = (char*)*(void**)((char*)self + 0xec);
    unsigned count = (unsigned)((gridEnd - gridBegin) >> 5);
    for (unsigned i = 0; i < count; ++i) {
        int* found = (int*)FUN_00646030(b, e, gridBegin + i * 0x20, (char)info[5]);
        if (found != e) {
            int* g = (int*)(gridBegin + i * 0x20);
            bool lt;
            if (*g != *found) lt = *g < (unsigned)*found;
            else if (g[2] != found[2]) lt = g[2] < (unsigned)found[2];
            else lt = g[1] < (unsigned)found[1];
            if (!lt && found != found + 5)
                return (int)i;
        }
    }
    return -1;
}

// @ 0x00653c40
int cSPUIAssetGrid_s0065_35b0::GridScanRev()
{
    void* self = this;
    AssetBrowser();
    int* info = (int*)FUN_00644a70(0);
    int* b = (int*)info[0];
    int* e = (int*)info[1];
    if (b == e)
        return -1;
    char* gridBegin = (char*)*(void**)((char*)self + 0xe8);
    char* gridEnd = (char*)*(void**)((char*)self + 0xec);
    int i = (int)((gridEnd - gridBegin) >> 5) - 1;
    for (;;) {
        int* g = (int*)(gridBegin + i * 0x20);
        int* found = (int*)FUN_00646030(b, e, g, (char)info[5]);
        if (found != e) {
            bool lt;
            if (*g != *found) lt = *g < (unsigned)*found;
            else if (g[2] != found[2]) lt = g[2] < (unsigned)found[2];
            else lt = g[1] < (unsigned)found[1];
            if (!lt && found != found + 5)
                return i;
        }
        --i;
    }
}

// @ 0x00653cf0
void* cSPUIAssetView::VerbCollect(unsigned enabled)
{
    void* self = this;
    char* s = (char*)self;
    *(void**)(s + 0x10) = s + 0x18;
    *(void**)(s + 4) = s + 0x18;
    *(void**)(s + 0) = s + 0x18;
    *(void**)(s + 8) = s + 0x18 + 0x78;
    if (!enabled)
        return self;
    void* v = FUN_0065f810_s0065_35b0(1);
    char* begin = *(char**)v;
    for (unsigned i = 0; i < (unsigned)((*(char**)((char*)v + 4) - begin) / 0x34); ++i) {
        uint32_t verb = cSPUIAssetView_InitVerbCollection(*(uint32_t*)(begin + i * 0x34));
        if (verb) {
            char* end = *(char**)(s + 4);
            int* lo = FUN_00555a20((int*)*(void**)s, (int*)end, (int*)&verb, s[0x90]);
            if (lo == (int*)end) {
                if (end == *(char**)(s + 8)) {
                    fixed_vector_DoInsertValue((void*)s, lo, &verb);
                } else {
                    *(char**)(s + 4) = end + 4;
                    if (end)
                        *(uint32_t*)end = verb;
                }
            } else if (verb < (uint32_t)*lo) {
                fixed_vector_DoInsertValue((void*)s, lo, &verb);
            }
        }
    }
    return self;
}

// @ 0x00653e40
void GridVec_s0065_35b0::resize(unsigned n)
{
    const unsigned cur = (unsigned)(mpEnd - mpBegin);
    if (cur < n) {
        GridEntry_s0065_35b0 empty;
        f_00652c90(mpEnd, n - cur, empty);
    } else {
        GridEntry_s0065_35b0* pos = mpBegin + n;
        DoDestroyValues(CopyRange(mpEnd, mpEnd, pos), mpEnd);
        mpEnd -= (unsigned)(mpEnd - pos);
    }
}

// @ 0x00653f50
void QuickSortImplA(GridEntry_s0065_35b0* first, GridEntry_s0065_35b0* last, int kRecursionCount)
{
    while (((last - first) > kQuickSortLimit) && (kRecursionCount > 0)) {
        GridEntry_s0065_35b0 pivot = MedianA(*first, *(first + (last - first) / 2), *(last - 1));
        GridEntry_s0065_35b0* position = GetPartitionA(first, last, pivot);
        QuickSortImplA(position, last, --kRecursionCount);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortA(first, last, last);
}

// @ 0x00654100
char cSPUIAssetGrid_s0065_35b0::HandleMessage(int wparam, unsigned lparam)
{
    char* s = (char*)this;
    if (s[0x1e4] != 0)
        return 0;
    if (lparam == 2 && wparam == 0x46) {
        if (*(void**)(s + 0xe4) != 0)
            ((SearchBoxStub*)*(void**)(s + 0xe4))->OnSearchChanged();
        return 1;
    }

    if ((lparam & 0xffffffbf) == 0) {
        if (wparam == 0x21 || wparam == 0x22) {
            void* window = *(void**)((char*)*(void**)(s + 0x18c) + 0x20);
            int visible = (*(int(__thiscall**)(void*))((char*)*(void**)window + 0x40))(window);
            int total = (*(int(__thiscall**)(void*))((char*)*(void**)window + 0x48))(window);
            int step;
            if (total < visible)
                step = visible - total;
            else
                step = 1;
            if (wparam == 0x21)
                step = -step;
            float offset = (float)step + *(float*)(s + 0x180);
            if (!(offset > 0.0f))
                offset = 0.0f;
            if (*(float*)(s + 0x188) <= offset)
                offset = *(float*)(s + 0x188);
            *(float*)(s + 0x180) = offset;
            s[0x190] = 1;
            SPUIHelpers_UpdateMouseFocus(1);
            return 1;
        }
        if (wparam == 0x25 || wparam == 0x26 || wparam == 0x27 || wparam == 0x28) {
            int index = (wparam == 0x25 || wparam == 0x26) ? GridScanFwd() : GridScanRev();
            char* grid = *(char**)(s + 0xe8);
            if (index != -1 && *(void**)(grid + index * 0x20 + 0x10) != 0) {
                const int columns = *(int*)(s + 0x110);
                const int count = (int)((*(char**)(s + 0xec) - grid) >> 5);
                int next = index;
                switch (wparam) {
                case 0x25:
                    if (index % columns != 0)
                        next = index - 1;
                    break;
                case 0x26:
                    if (columns <= index)
                        next = index - columns;
                    break;
                case 0x27:
                    if (index != count - 1 && index % columns != columns - 1)
                        next = index + 1;
                    break;
                case 0x28:
                    if (index < count - columns)
                        next = columns + index;
                    break;
                }
                void* entry = *(void**)(grid + next * 0x20 + 0x10);
                if (next != index && entry != 0 && *(char*)((char*)entry + 0xf4) != 0)
                    cSPUIAssetView_SelectAsset(entry, 0, 1, 0, 0, 0);
            }
            return 1;
        }
    }

    if (lparam != 0)
        return 0;
    int index;
    if (wparam == 0x24) {
        if (*(int*)(s + 0x1b0) <= 0)
            return 0;
        index = CheckFlag() ? 1 : 0;
    } else if (wparam == 0x23) {
        const int count = *(int*)(s + 0x1b0);
        if (count <= 0)
            return 0;
        index = CheckFlag() ? count : count - 1;
    } else {
        return 0;
    }
    if (index < 0)
        return 0;
    void* entry = *(void**)(*(char**)(s + 0xe8) + index * 0x20 + 0x10);

    if (entry == 0)
        return 1;
    if (*(char*)((char*)entry + 0xf4) == 0)
        return 1;
    cSPUIAssetView_SelectAsset(entry, 0, 1, 0, 0, 0);
    return 1;
}

// @ 0x006543a0
void cSPUIAssetGrid_s0065_35b0::GridClear()
{
    void* self = this;
    char* s = (char*)self;
    void* p = *(void**)(s + 0xfc);
    if (p) {
        void* q = *(void**)((char*)p + 0x10);
        if (q)
            ((AssetObjStub*)q)->f_00659340();
        *(void**)(s + 0xfc) = 0;
    }
    s[0x100] = 0;
    GridVec_s0065_35b0* v = (GridVec_s0065_35b0*)(s + 0xe8);
    int count = (int)(v->mpEnd - v->mpBegin);
    for (int i = 0; i < count; ++i) {
        void* obj = *(void**)((char*)v->mpBegin + i * 0x20 + 0x10);
        if (obj)
            (*(void(__thiscall**)(void*))((char*)*(void**)obj + 0x20))(obj);
    }
    const unsigned n = (unsigned)(v->mpEnd - v->mpBegin);
    v->DoDestroyValues(v->mpBegin, v->mpEnd);
    v->mpEnd -= n;
    *(float*)(s + 0x180) = 0.0f;
    *(float*)(s + 0x184) = 0.0f;
    *(int*)(s + 0x198) = 1;
    void* mgr = *(void**)(s + 0x18c);
    if (mgr) {
        void* w = *(void**)((char*)mgr + 0x20);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x24))(w, 0, 1);
    }
}

// @ 0x00654490
void GridVec_s0065_35b0::reserve(unsigned n)
{
    if (n == (unsigned)-1)
        return;
    const unsigned cur = (unsigned)(mpEnd - mpBegin);
    if (n > cur) {
        GridEntry_s0065_35b0* pNewData = n
            ? (GridEntry_s0065_35b0*)EASTL_allocator_allocate(n * sizeof(GridEntry_s0065_35b0), "Editor", 0, 0,
                                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                                   "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                                   "EASTL/allocator.h",
                                                   0xd1)
            : 0;
        UninitializedCopy(mpBegin, mpEnd, pNewData);
        DestroyRange(mpBegin, mpEnd, pNewData);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        GridEntry_s0065_35b0* pEnd = pNewData + (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpCapacity = pNewData + n;
        mpEnd = pEnd;
    } else {
        if (n < cur)
            resize(n);
        GridVec_s0065_35b0 temp;
        temp.f_0064f4e0((unsigned)(mpEnd - mpBegin), &mpAllocator);
        GridEntry_s0065_35b0* pWritten;
        FUN_0064f730(&pWritten, mpBegin, mpEnd, temp.mpBegin, n);
        temp.mpEnd = pWritten;
        swap(temp);
        temp.DoDestroyValues(temp.mpBegin, temp.mpEnd);
        if (temp.mpBegin && ((unsigned*)temp.mpBegin)[-1])
            EASTL_allocator_deallocate(temp.mpBegin);
    }
}

// @ 0x00654650
void cSPUIAssetGrid_s0065_35b0::GridShutdown()
{
    void* self = this;
    char* s = (char*)self;
    if (s[0x10c]) {
        void* app = AppSystem_s0065_35b0();
        (*(void(__thiscall**)(void*, int))((char*)*(void**)app + 0x40))(app, 0);
        s[0x10c] = 0;
    }
    GridClear();
    FUN_0065aeb0();
    void* layout = *(void**)(s + 0x18);
    if (layout) {
        ((LayoutStub*)layout)->f_00811ad0(1);
        void* p = *(void**)(s + 0x18);
        if (p) {
            *(void**)(s + 0x18) = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 8))(p);
        }
    }
    void* e0 = *(void**)(s + 0xe0);
    if (e0) {
        ((AssetObjStub*)e0)->f_0065fa20();
        void* p = *(void**)(s + 0xe0);
        if (p) {
            *(void**)(s + 0xe0) = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
        }
    }
    void* e4 = *(void**)(s + 0xe4);
    if (e4) {
        ((SearchBoxStub*)e4)->f_00671c00();
        void* p = *(void**)(s + 0xe4);
        if (p) {
            *(void**)(s + 0xe4) = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
        }
    }
    void* h = *(void**)(s + 0x138);
    if (h) {
        *(void**)(s + 0x138) = 0;
        Messaging_RemoveHandler(h, *(void**)(s + 0x13c), *(void**)(s + 0x140),
                                *(void**)(s + 0x144), *(void**)(s + 0x148));
    }
}

// @ 0x00654730
void AssetGrid::UpdateAssets(void* filter, void* feedItem)
{
    void* self = this;
    char* s = (char*)self;

    // 0x1b4 = load counter
    *(int*)(s + 0x1b4) = 0;

    // --- swap the active filter (+0x19c) with AddRef/Release ---
    void* old = *(void**)(s + 0x19c);
    if (filter != old) {
        if (filter)
            (*(void(__thiscall**)(void*))((char*)*(void**)filter))(filter);
        *(void**)(s + 0x19c) = filter;
        if (old)
            (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }

    // --- clear pending-selection state ---
    s[0x1e4] = 0;
    s[0x1e5] = 0;
    void* pend = *(void**)(s + 0x1c0);
    if (pend) {
        *(void**)(s + 0x1c0) = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)pend + 4))(pend);
    }
    *(int*)(s + 0x1c4) = 0;
    *(int*)(s + 0x1c8) = 0;
    *(int*)(s + 0x1cc) = 0;

    // --- primary widget (+0x28) and secondary (+0x48) visibility; header bar (+0x4c) ---
    void* curFilter = *(void**)(s + 0x19c);
    bool known = curFilter != 0 && ((GridHelper*)curFilter)->IsKnownID();
    if (known) {
        void* w0 = *(void**)(s + 0x28);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w0 + 0x7c))(w0, 1, 1);
        void* w1 = *(void**)(s + 0x48);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w1 + 0x7c))(w1, 1, 1);
    } else {
        void* w0 = *(void**)(s + 0x28);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w0 + 0x7c))(w0, 1, 0);
        void* w1 = *(void**)(s + 0x48);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w1 + 0x7c))(w1, 1, 0);
    }
    {
        void* w2 = *(void**)(s + 0x4c);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w2 + 0x7c))(w2, 1, known ? 1 : 0);
    }

    // --- feed-header widget (+0x5c): visible only when the stored filter + item are both live ---
    {
        void* w3 = *(void**)(s + 0x5c);
        if (w3) {
            int vis;
            if (curFilter == 0)
                vis = s[0x1b8];
            else
                vis = (s[0x1b8] && *((char*)curFilter + 0x16)) ? 1 : 0;
            (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w3 + 0x7c))(w3, 1, vis);
        }
    }

    // --- release the previous feed item (+0xfc) and its sub-object at +0x10 ---
    {
        void* it = *(void**)(s + 0xfc);
        if (it) {
            void* sub = *(void**)((char*)it + 0x10);
            if (sub)
                ((GridHelper*)sub)->Collect0x659340();
            *(void**)(s + 0xfc) = 0;
        }
    }
    s[0x100] = 0;

    // --- if the header widget (+0x2c) and feedItem are both live, rebuild the entry vector ---
    if (*(void**)(s + 0x2c) != 0 && feedItem != 0) {
        ((GridHelper*)self)->Clear();
        void* f2 = *(void**)(s + 0x19c);
        bool want = (f2 == 0) ? (s[0x1b8] != 0)
                              : (s[0x1b8] != 0 && *((char*)f2 + 0x16) != 0);
        if (want) {
            GridEntries* vec = (GridEntries*)(s + 0xe8);
            if (vec->mpEnd < vec->mpCapacity) {
                void* slot = vec->mpEnd;
                vec->mpEnd = (char*)slot + 0x20;
                FUN_0064f3b0(slot, /*placeholder entry*/ 0);
            } else {
                FUN_006535b0(vec->mpEnd, 0);
            }
        }
        // second (empty) placeholder entry
        {
            GridEntries* vec = (GridEntries*)(s + 0xe8);
            if (vec->mpEnd < vec->mpCapacity) {
                void* slot = vec->mpEnd;
                vec->mpEnd = (char*)slot + 0x20;
                FUN_0064f3b0(slot, 0);
            } else {
                FUN_006535b0(vec->mpEnd, 0);
            }
        }
        {
            GridEntries* vec = (GridEntries*)(s + 0xe8);
            int count = (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) >> 5);
            FUN_00652b00(vec->mpEnd, (char*)feedItem + 0x5c + count);
        }

        // --- merge the feed item's sorted sub-item list (+0x4c) into the entry vector ---
        char* subEnd = (char*)feedItem + 0x4c;
        char* node = *(char**)((char*)feedItem + 0x50);
        if (node != subEnd) {
            do {
                char* sub = *(char**)(node + 0x1c);   // the sub-object
                if ((*(char(__thiscall**)(char*))((char*)*(void**)sub + 0x2c))(sub)) {
                    void* browser = AssetBrowser();
                    void* entry = FUN_006462b0(browser, sub);
                    (*(void(__thiscall**)(void*))((char*)*(void**)entry))(entry);   // AddRef
                    {
                        // build a cSPAssetGridEntry from {sub keys, sub, entry} then insert
                        GridEntries* vec = (GridEntries*)(s + 0xe8);
                        if (vec->mpEnd < vec->mpCapacity) {
                            void* slot = vec->mpEnd;
                            vec->mpEnd = (char*)slot + 0x20;
                            FUN_0064f3b0(slot, 0);
                        } else {
                            FUN_006535b0(vec->mpEnd, 0);
                        }
                    }
                } else {
                    *(int*)(s + 0x1b4) += 1;
                }
                {
                    char* next = (char*)RBTreeIncrement(node);
                    char* stop = (char*)feedItem + 0x4c + 0x4c;
                    node = next;
                    if (node == stop) break;
                }
            } while (true);
        }

        // --- after the walk: reserve or arm the pending selection ---
        if (((GridHelper*)feedItem)->IsEmpty()) {
            FUN_00654490(-1);
        } else {
            s[0x1e4] = 1;
            void* oldPend = *(void**)(s + 0x1c0);
            if (feedItem != oldPend) {
                (*(void(__thiscall**)(void*))((char*)*(void**)feedItem))(feedItem);
                *(void**)(s + 0x1c0) = feedItem;
                if (oldPend)
                    (*(void(__thiscall**)(void*))((char*)*(void**)oldPend + 4))(oldPend);
            }
        }
    }

    // --- header message string (eastl::gEmptyString16 ...) then show on the feed-header sub-widget
    {
        void* headerWidget = *(void**)(s + 0x50);
        if (headerWidget && *(void**)(s + 0x19c) != 0) {
            if (FUN_00668be0(headerWidget, (void*)/*16-byte key*/ 0)) {
                void* w = *(void**)(s + 0x50);
                (*(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x80))(w, 0);
            }
        }
    }

    // --- tail updates ---
    s[0x1e6] = 1;
    s[0x1e7] = 1;
    ((AssetGridTail*)self)->UpdateScrolling(0);
    ((AssetGridTail*)self)->UpdateAll();
    ((GridHelper*)self)->Update0x650470();
    ((AssetGridTail*)self)->UpdateScrollRegion();

    *(int*)(s + 0x194) = 1;
    void* f = *(void**)(s + 0x19c);
    bool render;
    if (f == 0)
        render = (s[0x1b8] != 0) && (*(void**)(s + 0xe8) != *(void**)(s + 0xec));
    else
        render = (s[0x1b8] != 0) && (*((char*)f + 0x16) != 0);
    if (render && *(void**)(s + 0xe8) != *(void**)(s + 0xec) &&
        *(char*)(*(char**)(s + 0xe8) + 0x1c) != 0) {
        int pad = 5;
        void* ab = AssetBrowser();
        if (ab && ((int*)AssetBrowser())[6] != 0) {
            void* ab2 = AssetBrowser();
            pad = cTribeTool_GetTutorialToolPrice((void*)((int*)ab2)[6], 0x86cf5fc5, 5);
        }
        void* w = *(void**)(s + 0x5c);
        if (w) {
            char* e0 = *(char**)(s + 0xe8);
            (*(void(__thiscall**)(void*, float, float))((char*)*(void**)w + 0x64))(
                w, *(float*)(e0 + 0x14) + (float)pad, *(float*)(e0 + 0x18) + (float)pad);
            (*(void(__thiscall**)(void*, float, float))((char*)*(void**)w + 0x68))(
                w, *(float*)(s + 0x104) - (float)(pad * 2),
                   *(float*)(s + 0x108) - (float)(pad * 2));
        }
    }

    // --- frame timer stamp (+0x160 gate) ---
    {
        unsigned long long stamp;
        if (*(int*)(s + 0x160) == 1) {
            stamp = __rdtsc();
        } else {
            long long pc = 0;
            QueryPerformanceCounter(&pc);
            stamp = (unsigned long long)pc;
        }
        *(int*)(s + 0x150) = (int)(stamp & 0xffffffffu);
        *(int*)(s + 0x154) = (int)(stamp >> 32);
    }
    *(int*)(s + 0x158) = 0;
    *(int*)(s + 0x15c) = 0;
}

// @ 0x00654d00
void FUN_00654d00(void* self)
{
    char* s = (char*)self;
    s[0x1e8] = 0;
    void* p = *(void**)(s + 0xfc);
    if (p) {
        void* q = *(void**)((char*)p + 0x10);
        if (q)
            FUN_00659340(q);
        *(void**)(s + 0xfc) = 0;
    }
    void* item = FUN_0066a800(*(int*)(s + 0x1a0));
    s[0x100] = 0;
    if (item) {
        (*(void(__thiscall**)(void*))((char*)*(void**)item + 4))(item);
        U8Vec vec;
        vec.mpBegin = 0; vec.mpEnd = 0; vec.mpCapacity = 0;
        if (*(void**)(s + 0xe0)) {
            void* list = FUN_0065f810_s0065_4730(0);
            char* begin = *(char**)list;
            char* end = *(char**)((char*)list + 4);
            while (begin != end) {
                unsigned v = *(unsigned*)begin;
                if (vec.mpEnd < vec.mpCapacity) {
                    *vec.mpEnd++ = v;
                } else {
                    // vector<unsigned>::DoInsertValue(&vec, &v): grow
                    unsigned n = (unsigned)(vec.mpEnd - vec.mpBegin);
                    unsigned cap = n ? n * 2 : 1;
                    unsigned* nd = (unsigned*)::operator new(cap * 4);
                    for (unsigned i = 0; i < n; ++i) nd[i] = vec.mpBegin[i];
                    nd[n] = v;
                    if (vec.mpBegin) ::operator delete(vec.mpBegin);
                    vec.mpBegin = nd;
                    vec.mpEnd = nd + n + 1;
                    vec.mpCapacity = nd + cap;
                }
                begin += 0x34;
            }
        }
        FUN_0066b0c0(&vec);
        FUN_00653ee0(*(void**)(s + 0xe8), *(void**)(s + 0xec), item);
        if (vec.mpBegin && ((unsigned*)vec.mpBegin)[-1])
            ::operator delete(vec.mpBegin);
    }
    FUN_00650470(self);
    *(int*)(s + 0x198) = 1;
    if (item)
        (*(void(__thiscall**)(void*))((char*)*(void**)item + 8))(item);
}

// @ 0x00654e20
void cSPUIAssetGrid_s0065_4730::ScrollTo(void* item)
{
    if (!item)
        return;
    if (mNeedsRebuild)
        Rebuild();
    if (mNeedsReset)
        Refresh();
    GridEntry_s0065_4730* found = (GridEntry_s0065_4730*)Find((uint32_t)(uintptr_t)item);
    if (!found)
        return;
    float itemPos = found->mPosition;
    float cur = mScroll;
    int size = mGridSource->mSizeProvider->GetSize();
    float limit = ((float)size + cur) - mViewWidth;
    if (limit < cur)
        limit = cur;
    if (cur <= itemPos) {
        if (limit < mItemWidth + itemPos)
            mScroll = (mItemWidth + itemPos - (float)size) + mViewWidth;
    } else {
        mScroll = itemPos;
    }
    float v = mScroll;
    if (v <= 0.0f)
        v = 0.0f;
    if (mMaxScroll <= v)
        v = mMaxScroll;
    mScroll = v;
    mFocusFlag = true;
    SPUIHelpers_UpdateMouseFocus(1);
}

// @ 0x00654f50
void AssetGrid::OnSelectCommit(void* item, void* filter)
{
    void* self = this;
    char* s = (char*)self;

    if (s[0x1e4]) {
        s[0x1e5] = 0;
        void* old = *(void**)(s + 0x1c0);
        if (item != old) {
            if (item)
                (*(void(__thiscall**)(void*))((char*)*(void**)item))(item);
            *(void**)(s + 0x1c0) = item;
            if (old)
                (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        return;
    }

    long long price = 2000;
    void* ab = AssetBrowser();
    if (ab && ((int*)AssetBrowser())[6] != 0) {
        void* ab2 = AssetBrowser();
        price = (long long)(int)(uintptr_t)cTribeTool_GetTutorialToolPrice((void*)((int*)ab2)[6], 0x1df98401, 2000);
    }
    unsigned long long elapsed = (unsigned long long)((StopwatchHelper*)(s + 0x168))->GetElapsedTime();
    if ((unsigned long long)price >= elapsed) {
        // stopwatch has NOT out-run the price: arm the pending swap and leave.
        s[0x1e5] = 1;
        void* old = *(void**)(s + 0x1c0);
        if (item != old) {
            if (item)
                (*(void(__thiscall**)(void*))((char*)*(void**)item))(item);
            *(void**)(s + 0x1c0) = item;
            if (old)
                (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        return;
    }

    // Commit body.
    s[0x1e5] = 0;
    ((GridHelper*)self)->Release0x64e7a0();
    ((GridHelper*)item)->Reset0x644040(0);
    if (!((GridHelper*)item)->IsEmpty()) {
        s[0x1e5] = 1;
        *(void**)(s + 0x1c0) = item;   // AutoRefCount<IWinText>::operator=
    }
    if (filter == *(void**)(s + 0x19c) && item) {
        ((GridHelper*)self)->Release0x64e7a0();
        ((GridHelper*)self)->MergeEntries(*(void**)(s + 0xe8), *(void**)(s + 0xec), item);
        // Merge the item's sorted list (rbtree anchored at item+0x4c) into the grid's
        // entry vector at +0xe8. Each entry is 0x20 bytes; ordering compares the
        // 64-bit pair {[+0x10],[+0x14]} (then a third key at the tail).
        char* itemEnd = (char*)item + 0x4c;
        void* node = *(void**)((char*)item + 0x50);   // first node
        char* out = *(char**)(s + 0xe8);
        while (node != itemEnd) {
            void* cur = node;
            if (out == *(char**)(s + 0xec)) {
                // append: build a temporary entry then insert at end
                EntryVec* vec = (EntryVec*)(s + 0xe8);
                vec->InsertAt(out, cur, &out);
                node = RBTreeIncrement(node);
                continue;
            }
            // compare {cur[0x10],cur[0x14],cur[0x18]} against the queued out entry
            unsigned k0 = *(unsigned*)((char*)cur + 0x10);
            unsigned k1 = *(unsigned*)((char*)cur + 0x14);
            unsigned k2 = *(unsigned*)((char*)cur + 0x18);
            unsigned c0 = *(unsigned*)(out + 0);
            unsigned c1 = *(unsigned*)(out + 4);
            unsigned c2 = *(unsigned*)(out + 8);
            bool curLess = (k0 < c0) || (k0 == c0 && (k2 < c2 || (k2 == c2 && k1 < c1)));
            if (!curLess) {
                bool curMore = (k0 > c0) || (k0 == c0 && (k2 > c2 || (k2 == c2 && k1 > c1)));
                if (curMore) {
                    out += 0x20;
                    node = RBTreeIncrement(node);
                }
            } else {
                out += 0x20;
                node = RBTreeIncrement(node);
            }
        }
        // Drop trailing grid entries that no longer sort before the item's end.
        while (out != *(char**)(s + 0xec)) {
            EntryVec* vec = (EntryVec*)(s + 0xe8);
            out = (char*)vec->Erase(out);
            *(int*)(s + 0x198) = 1;
        }
    }

    s[0x1e6] = 1;
    s[0x1e7] = 0;
    ((GridHelper*)self)->Update0x650470();
    {
        float v = *(float*)(s + 0x180);
        if (v < 0.0f) v = 0.0f;
        if (*(float*)(s + 0x188) < v) v = *(float*)(s + 0x188);
        *(float*)(s + 0x180) = v;
    }
    ((StopwatchHelper*)(s + 0x168))->Restart();
}

// @ 0x00655ed0
void cSPUIAssetGrid_s0065_53b0::Update(int arg)
{
    if (!m10c) {
        if (mLoadingFeed) {
            m10c = true;
            GetAppSystem()->SetFlag(1);
        }
    } else if (!mLoadingFeed) {
        m10c = false;
        GetAppSystem()->SetFlag(0);
    }
    if (m1e5) {
        int t = 2000;
        if (GetAssetBrowser() && GetAssetBrowser()->mpTool)
            t = GetTutorialToolPrice(GetAssetBrowser()->mpTool, 0x1df98401, 2000);
        if ((unsigned long long)(long long)t < mTimerB.GetElapsedTime()) {
            FUN_654f50(mpFeed, mpViewState);
            mTimerB.Restart();
        }
    }
    if (mLoadingFeed && mpFeed) {
        KeyVec keys;
        keys.mpBegin = 0;
        keys.mpEnd = 0;
        keys.mpCapacity = 0;
        if (!mpFeed->FUN_642910()) {
            FeedListItem* f = mpFeed;
            int n = f->FUN_643060();
            n += f->FUN_642900();
            keys.reserve(n);
            mpFeed->FUN_644040(&keys);
        }
        AddEntries(&keys);
        if (mLoadingFeed) {
            FeedListItem* f = mpFeed;
            int n = f->FUN_643060();
            n += f->FUN_642900();
            int done = mpFeed->mTotal;
            FUN_64e880(true, (unsigned)(done * 100) / (unsigned)(done + n));
        } else {
            if (mWinFeedFilter.mpObject)
                mWinFeedFilter.mpObject->SetVisible(true, false);
            if (mWinFeedHeader.mpObject)
                mWinFeedHeader.mpObject->SetVisible(true, true);
        }
        if (keys.mpBegin && ((int*)keys.mpBegin)[-1] != 0)
            EASTL_allocator_deallocate(keys.mpBegin);
    } else {
        if (mWinFeedFilter.mpObject)
            mWinFeedFilter.mpObject->SetVisible(true, false);
        if (mWinFeedHeader.mpObject)
            mWinFeedHeader.mpObject->SetVisible(true, true);
    }
    if (!mLoadingFeed) {
        if (mNeedsRefresh)
            RefreshAssetStates();
        if (m1e8)
            FUN_654d00();
        int t = 0x4b;
        if (GetAssetBrowser() && GetAssetBrowser()->mpTool)
            t = GetTutorialToolPrice(GetAssetBrowser()->mpTool, 0xb6c69eb8, 0x4b);
        if ((unsigned long long)(long long)t < mTimerA.GetElapsedTime() && m198 != 0
            && fabsf(m180 - m184) <= (float)mpScrollFrame->mScrollbar->GetMin()
            && FUN_64fde0(&m198))
            mTimerA.Restart();
        int count = (int)(mGridEntries.mpEnd - mGridEntries.mpBegin);
        for (int i = 0; i < count; ++i) {
            GridEntry_s0065_53b0* e = mGridEntries.mpBegin + i;
            AssetView_s0065_53b0* v = e->mView.mpObject;
            if (v && v->mSelectable) {
                Vec2 pos(e->mX, e->mY);
                mGridEntries.mpBegin[i].mView.mpObject->SetPos(pos, true);
                AssetView_s0065_53b0* v2 = mGridEntries.mpBegin[i].mView.mpObject;
                v2->OnUpdate(arg, FUN_64e7d0(i));
            }
        }
        if (mFeedFilter)
            mFeedFilter->FUN_10829f0(arg);
        if (mSearchBox)
            mSearchBox->Update(arg);
        UpdateScrolling(arg);
    }
}

// @ 0x00656310
void cSPUIAssetView_s0065_6310::m56310(void* range)
{
    KeyVec_s0065_6310 keys;
    unsigned int extra;
    char* base = (char*)range;
    char* oldEnd = *(char**)(base + 4);
    keys.Init(mE0);
    char* p = (char*)FUN_00656240(*(void**)base, *(char**)(base + 4),
                                  MakeKeys(keys.mpBegin, keys.mpEnd, (void*)extra));
    copy_705250(oldEnd, *(void**)(base + 4), p);
    int n = (int)((oldEnd - p) >> 4);
    *(char**)(base + 4) += -(n << 4);
    if (keys.mpBegin && keys.mpBegin != keys.mAllocBuf) operator_delete_0(keys.mpBegin);
}
