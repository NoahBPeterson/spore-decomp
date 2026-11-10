// src/game/SPEditors/_at_00ee0000.cpp -- migrated from slice(s) s00eede20, s00eed3f0, s00eeb770, s00eea7c0, s00ee9840, s00ee8860, s00ee7990, s00ee6880, s00ee4390, s00ee3800, s00ee2860, s00ee16f0, s00ee0d70, s00edfed0 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00ee0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cGameNounManager.h"
#include <math.h>
#include <intrin.h>
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPalettePageUI.h"
#include "SP/cSPPaletteUI.h"
#include "cSPUILayoutManager.h"
#include "SP/cSPEditorSpeciesManager.h"
#include "SP/cPlanetModel.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/WindowMgr.h"
#include <math.h>  // sqrtf -> fsqrt under /Oi (implied by /O2)
#include <string.h>
#include "EA/Variant.h"
#include <algorithm>
#include "SP/cHerd.h"
#include "SP/cVehicle.h"

// ---- items of slice s00edfed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem {
    int  v0;                 // +0x000 (byte in f_ee01e0)
    char pad0[0x4a4 - 0x4];
    int  v4a4;               // +0x4a4
    int  v4a8;               // +0x4a8
    int  v4ac;               // +0x4ac
    int  v4b0;               // +0x4b0
    int  v4b4;               // +0x4b4
    int  v4b8;               // +0x4b8
    int  v4bc;               // +0x4bc
    int  v4c0;               // +0x4c0
    char pad1[0x4e0 - 0x4c4];
};
struct Container {
    char  pad0[0x20];
    char  f20;               // +0x20
    char  pad1[0x70 - 0x21];
    char* begin;             // +0x70
    char* end;               // +0x74
};
struct Sub {
    char  pad0[0x84];
    char* f84;               // +0x84 begin
    char* f88;               // +0x88 end
};
struct IntVec { int* begin; int* end; int* cap; };
struct Manager {
    void  Lock();                     // FUN_00f45970
    void  Unlock();                   // FUN_00f45a80
    void  Refresh();                  // FUN_00f427c0
    int   Count();                    // FUN_00f3be30
    Sub*  Get(int i);                 // FUN_00f3be60
    void* Find(int x);                // FUN_00f3e8a0
    void* CollectByNoun(void* a, IntVec* out);   // 0x00f40c20
};
struct GlobalObj {
    char      pad0[0x14];
    void*     f14;           // +0x14  (object with FUN_006c0200 getter)
    char      pad1[0x74 - 0x18];
    Manager*  f74;           // +0x74  (checklist manager)
    char      pad2[0xd4 - 0x78];
    void*     fD4;           // +0xd4  (cScenarioTutorialsChecklistUI*)
};
extern GlobalObj* g_16c7aa4;
bool  __cdecl   FUN_00edfda0(int* dst, int* src);
void  __cdecl   FUN_00edfce0(void* dst, void* src);
void  __cdecl   FUN_00eef170(void* p, int i);
int   __cdecl   FUN_00efc520();
void  __cdecl   operator_delete(void* p);
static const int kTbl4a8[5] = { 1, 2, 3, 4, 5 };
static const int kTbl4b0[3] = { 1, 2, 3 };
static const int kTbl4b4[3] = { 1, 2, 3 };
static const int kTbl4b8[5] = { 1, 3, 4, 5, 6 };
struct VObj {
virtual void  _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void  _v4();
virtual void _v5();
virtual void _v6();
    virtual int   GetTypeId();                          // 7  (0x1c)
virtual void  _v8();
virtual void _v9();
virtual void _v10();
virtual void _v11();
virtual void  _v12();
virtual void _v13();
virtual void _v14();
    virtual void* GetPtr15();                           // 15 (0x3c)
virtual void  _v16();
virtual void _v17();
virtual void _v18();
virtual void _v19();
virtual void  _v20();
virtual void _v21();
virtual void _v22();
virtual void _v23();
virtual void  _v24();
virtual void _v25();
virtual void _v26();
virtual void _v27();
virtual void  _v28();
virtual void _v29();
virtual void _v30();
    virtual void  SetFlag(int a, int b);                // 31 (0x7c)
virtual void  _v32();
virtual void _v33();
virtual void _v34();
virtual void _v35();
virtual void  _v36();
virtual void _v37();
virtual void _v38();
virtual void _v39();
virtual void  _v40();
virtual void _v41();
virtual void _v42();
virtual void _v43();
virtual void  _v44();
virtual void _v45();
virtual void _v46();
virtual void _v47();
virtual void  _v48();
virtual void _v49();
virtual void _v50();
virtual void _v51();
virtual void  _v52();
virtual void _v53();
virtual void _v54();
virtual void _v55();
virtual void  _v56();
virtual void _v57();
virtual void _v58();
virtual void _v59();
    virtual void* FindByHash(int hash, int flag);       // 60 (0xf0)
};
struct HintObj { void ToggleHint(int a, int b); };
struct Obj14 { void SetFlag(int key); };   // f_edff50 as a method of this object
namespace __equiv_ann1 {
struct HintObj {
    void ToggleHint();   // 0x00efbbe0 (equiv t2)
};
}
// ---- items of slice s00edfed0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern GlobalObj* g_16c7aa4;

// ---- items of slice s00ee0d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem_s00ee_0d70 {
    int  v0;
    char pad0[0x4a4 - 0x4];
    int  v4a4, v4a8, v4ac, v4b0, v4b4, v4b8, v4bc, v4c0, v4c4;
    char pad1[0x4e0 - 0x4c8];
};
struct Manager_s00ee_0d70 {
    void Lock();
    void Unlock();
    void FUN_00f40d00(int key, void* out);
};
struct GlobalObj_s00ee_0d70 {
    char pad0[0x14]; void* f14; char pad1[0x74 - 0x18]; Manager_s00ee_0d70* f74;
    char pad2[0xd4 - 0x78]; void* fD4;
};
extern GlobalObj_s00ee_0d70* g_16c7aa4_s00ee_0d70;
typedef void  (__fastcall *VF0)(void*, int);
typedef void  (__fastcall *VFp)(void*, int, void*);
typedef void* (__fastcall *VFQ2)(void*, int, int, int);
static __forceinline void  vc0(void* o, int slot)
{ ((VF0)(((void**)(*(void***)o))[slot]))(o, 0); }
static __forceinline void  vcp(void* o, int slot, void* a)
{ ((VFp)(((void**)(*(void***)o))[slot]))(o, 0, a); }
static __forceinline void* vcq2(void* o, int slot, int a, int b)
{ return ((VFQ2)(((void**)(*(void***)o))[slot]))(o, 0, a, b); }
void  __stdcall FUN_00edfbf0(void* p);
bool  __cdecl   FUN_00eddf30(void* a, void* b, void* c, void* d);
void  __cdecl   FUN_00f40d00(int key, void* out);
void  __fastcall  FUN_00edf410(void*, int);
void  __fastcall  FUN_00edf2c0(void*, int, int);
void* __fastcall  FUN_00e09c80(void*, int);           // count
void* __fastcall  FUN_00e09c90(void*, int, int idx);  // layout by index
void  __fastcall  FUN_00e0a5c0(void*, int);
void  __fastcall  FUN_00edd810(void*, int);
void  __fastcall  FUN_00edbcb0(void*, int);
void  __cdecl   SPUIHelpers_RemoveWindowCallback(void* w, void* cb);
void  __cdecl   SPUIHelpers_EndModal(void* w, int a, int b);
void* __cdecl   Layout_FindWindowByID(void* layout, int id, int flag);
void  __cdecl   EA_Messaging_RemoveHandler(int a, int b, int c, int d, int e);
void  __cdecl   cSPUILayout_SetParentWin(void* layout, int a, int b, int hash);
void  __cdecl   cSPUILayout_Shutdown(void* layout, int a);
void  __fastcall FUN_00bfc470(void*, int, int);
struct IObj {
    virtual void  u0();
    virtual void  Release();            // 1
    virtual void  u2();
    virtual void* Query(int key);       // 3
virtual void  u4();
virtual void u5();
virtual void u6();
virtual void u7();
virtual void  u8();
virtual void u9();
virtual void u10();
virtual void u11();
virtual void  u12();
virtual void u13();
virtual void u14();
virtual void u15();
virtual void  u16();
virtual void u17();
virtual void u18();
virtual void u19();
virtual void  u20();
virtual void u21();
virtual void u22();
virtual void u23();
virtual void  u24();
virtual void u25();
virtual void u26();
virtual void u27();
    virtual void  u28();
    virtual float GetFloat();           // 29
    // non-virtual fixed methods
    bool FUN_00c88940(int key);
    void FUN_00c8b1a0(int key);
    void FUN_00c88a00(int key);
    void FUN_00c8a020(int key, float v);
    void FUN_00c8ad30(int key, int v);
    void FUN_00bfc470(int a);
};
bool __cdecl f_ee0af0(Container* c, Elem_s00ee_0d70* e, int value);
bool __cdecl f_ee0c30(Container* c, Elem_s00ee_0d70* e, int value);
struct CCLarge {
    char  pad0[0x10];
    void* f10;               // +0x10 layout
    void* f14;               // +0x14 window
    void* f18;               // +0x18
    void* f1c;               // +0x1c refcounted array
    char  pad1[0x70 - 0x20];
    int   f70, f74, f78, f7c, f80;
};
struct CCLarge2 {
    char pad0[0x8];
    char f8;                 // +0x8
    char pad1[0x10 - 0x9];
    void* f10;               // +0x10
    void* f14;               // +0x14
    void* f18;               // +0x18
    void* f1c; void* f20; void* f24; void* f28;
    char pad2[0x40 - 0x2c];
    void* f40;               // +0x40
    void* f44;               // +0x44
    void* f48;               // +0x48
    char pad3[0xbc - 0x4c];
    void* fbc;               // +0xbc
    void* fc0;               // +0xc0
    char fc5, fc6;           // +0xc5, +0xc6
};
// ---- items of slice s00ee0d70 end

// ---- items of slice s00ee16f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];                                          // 0x01667bac
extern const uint32_t kCategoryWindowIDs[6];                              // 0x0148a708
extern const uint32_t kTable720[5];                                       // 0x0148a720
extern const uint32_t kTable738[6];                                       // 0x0148a738
extern const uint32_t kTable738Count;                                     // 0x0148a750
extern const uint32_t kTable754[3];                                       // 0x0148a754
extern const uint32_t kTable764[3];                                       // 0x0148a764
extern const uint32_t kTable774[5];                                       // 0x0148a774
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct ResourceKey {
    uint32_t instanceID;   // +0
    uint32_t typeID;       // +4
    uint32_t groupID;      // +8
};
class IWindow {
public:
    PV2 PV
    virtual void* Cast(uint32_t typeID);                                  // +0x0c
    virtual IWindow* GetParent();                                         // +0x10
    PV2
    virtual uint32_t GetControlID();                                      // +0x1c
    PV8 PV4 PV2 PV
    virtual void SetShadeColor(uint32_t color);                           // +0x5c
    PV4 PV2 PV
    virtual void SetFlag(int flag, bool value);                           // +0x7c
    virtual void SetCaption(const wchar_t* caption);                      // +0x80
    PV16 PV8 PV
    virtual void BringToFront(IWindow* w);                                // +0xe8
    PV
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);         // +0xf0
};
class ITextField {
public:
    enum { TYPE = 0xcf428691 };
    PV16 PV8
    virtual void SetText(const wchar_t* text, int flags);                 // +0x60
    PV
    virtual void SetMaxLength(int n);                                     // +0x68
};
class IButton {
public:
    enum { TYPE = 0x8ed27e7a };
    PV8 PV2
    virtual void SetButtonStateFlag(int flag, bool value);                // +0x28
};
template <class T>
inline T* object_cast(IWindow* w)
{
    return w ? (T*)w->Cast(T::TYPE) : 0;
}
inline void SetButtonFlag(IWindow* w, int flag, bool value)
{
    if (IButton* button = object_cast<IButton>(w))
        button->SetButtonStateFlag(flag, value);
}
class CategoryWinBase {
public:
    PV4 PV2 PV
    virtual void SetEnabled(bool b);                                      // +0x1c
};
class CategoryWinProc {          // secondary base at +4 (what messages carry)
public:
    PV
};
class CategoryWin : public CategoryWinBase, public CategoryWinProc {
public:
    void SetValue(int v);                                                 // 0x00f38bc0
};
class IRefreshTarget {            // secondary base at +0x24 of the +0x14 object
public:
    PV4 PV2
    virtual void Refresh(int a);                                          // +0x18
};
class ProgressBase {
public:
    PV4 PV2 PV
    virtual void SetID(uint32_t id);                                      // +0x1c
    uint32_t pad04[3];
    uint32_t mID;                                                         // +0x10
    uint32_t pad14[4];
};
class ProgressObj : public ProgressBase, public IRefreshTarget {
public:
    uint32_t GetID();                                                     // 0x007f54d0
    void Update();                                                        // 0x00ece300
    inline void Sync(uint32_t id)
    {
        if (GetID() != id)
            SetID(id);
    }
};
void __cdecl FreeArray(void* p);                                          // 0x00f47380 (operator delete[])
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(wchar_t* p, uint32_t)
    {
        if (p)
            FreeArray(p);
    }
    const wchar_t* c_str() const { return mpBegin; }
};
namespace SP {
class cString_s00ee_16f0 {
public:
    cString_s00ee_16f0(uint32_t tableID, uint32_t instanceID, int flags);            // 0x006b5770
    ~cString_s00ee_16f0();                                                           // 0x006b5240
    const wchar_t* GetText();                                             // 0x006b55c0
    uint32_t mData[5];                                                    // retail size 0x14 (frame layout; dev PDB says 0x1c)
};
}
struct TutorialStep {                 // 0x4e0-byte record
    bool     mbDone;                  // +0x000
    bool     mbFlag1;                 // +0x001
    bool     mbFlag2;                 // +0x002
    uint8_t  pad003[0x484 - 0x3];
    float    mValue484;               // +0x484
    uint32_t pad488;
    float    mValue48c;               // +0x48c
    float    mValue490;               // +0x490
    float    mValue494;               // +0x494
    float    mValue498;               // +0x498
    float    mValue49c;               // +0x49c
    float    mValue4a0;               // +0x4a0
    int      mIcon;                   // +0x4a4
    uint32_t mType4a8;                // +0x4a8
    uint32_t mType4ac;                // +0x4ac
    uint32_t mType4b0;                // +0x4b0
    uint32_t mType4b4;                // +0x4b4
    uint32_t mType4b8;                // +0x4b8
    int      mValue4bc;               // +0x4bc
    int      mValue4c0;               // +0x4c0
    int      mValue4c4;               // +0x4c4
    bool     mbLocked;                // +0x4c8
    uint8_t  pad4c9[3];
    struct Elem { uint32_t d[8]; };
    Elem*    mpGoalsBegin;            // +0x4cc
    Elem*    mpGoalsEnd;              // +0x4d0
    Elem*    mpGoalsCapacity;         // +0x4d4
    uint8_t  pad4d8[0x4e0 - 0x4d8];
    uint32_t GoalCount() const { return (uint32_t)(mpGoalsEnd - mpGoalsBegin); }
};
class Tutorial {
public:
    ResourceKey mKey;                 // +0x00
    uint32_t pad0c[5];
    uint8_t  mPage;                   // +0x20
    uint8_t  pad21[3];
    int      mMode24;                 // +0x24
    uint32_t pad28[8];
    int      mMode48;                 // +0x48
    uint32_t pad4c[9];
    TutorialStep* mpSteps;            // +0x70

    void GetName(string16& out);                                          // 0x00f28b80
    ResourceKey GetImageA();                                              // 0x00f25160
    ResourceKey GetImageB();                                              // 0x00f251f0
    ResourceKey GetImageC(bool* pDimmed);                                 // 0x00f25240
    int  GetStateA();                                                     // 0x00f252c0
    int  GetStateB();                                                     // 0x00f252f0
    bool HasValue330();                                                   // 0x00f25330
    bool HasValue420();                                                   // 0x00f25420
    bool HasValue430();                                                   // 0x00f25430
    bool HasValue470();                                                   // 0x00f25470
    bool HasValue560();                                                   // 0x00f25560
    bool IsFlag600();                                                     // 0x00f25600
    bool HasValue670();                                                   // 0x00f25670
};
class TutorialManager {
public:
    int       GetCount();                                                 // 0x00f3be30
    uint32_t  GetGoalCount(uint32_t id);                                  // 0x00f3c7f0
    Tutorial* Find(uint32_t id);                                          // 0x00f3e8a0
};
struct GameGlobals {
    uint32_t pad[0x74 / 4];
    TutorialManager* mpTutorials;     // +0x74
};
extern GameGlobals* g_16c7aa4_s00ee_16f0;
inline TutorialManager* GetTutorials() { return g_16c7aa4_s00ee_16f0->mpTutorials; }
class cSPUILayout_s00ee_16f0 {
public:
    bool IsVisible();                                                     // 0x00810070
};
struct StateSync {
    void Set(int v);                                                      // 0x00ed9990
};
struct CountLimits {
    static const uint32_t kMaxCount = 999;                                // 0x0148a94c
};
const uint32_t CountLimits::kMaxCount;
template <class T>
inline const T& min_ref(const T& a, const T& b)
{
    return (b < a) ? b : a;
}
template <int N>
inline int IndexOf(uint32_t value, const uint32_t (&table)[N])
{
    int index = -1;
    for (uint32_t i = 0; i < (uint32_t)N; i++) {
        if (value == table[i]) {
            index = (int)i;
            break;
        }
    }
    return index;
}
int   __cdecl ScenarioTutorials_GetActive();                                         // 0x00efc520
void  __cdecl Tutorial_Prepare(Tutorial* t);                                         // 0x00f0be80
bool  __cdecl Tutorial_IsComplete(Tutorial* t);                                      // 0x00ecb6b0
void  __cdecl SetPageLabel(IWindow* w, int page);                                    // 0x00ed1350
void  __cdecl SetButtonEnabled(IWindow* w, bool enabled);                            // 0x00e12fa0
void  __cdecl SetWindowText(IWindow* w, const wchar_t* text);                        // 0x00e12fc0
int   __cdecl IndexOfCounted(const uint32_t& v, const uint32_t* table, const uint32_t& count); // 0x00edcec0
void  __cdecl SetNumberString(int64_t value, wchar_t* buf, int size);                // 0x00881ae0
void  __cdecl SetNumberStringF(double value, wchar_t* buf, int size, int decimals);  // 0x00881f00
void  __cdecl ShowValue(uint32_t id, float value);                                   // 0x00ee1510
void  __cdecl SetSlider(IWindow* w, float value, float minValue, float maxValue);    // 0x00eddf90
float __cdecl GetStepTarget(ResourceKey key, float value);                           // 0x00eeebd0
void  __cdecl SetValueField(IWindow* w, float value, bool b2, bool b1, uint32_t fmt, const wchar_t* text); // 0x00edf830
void  __cdecl SetModeIcon(IWindow* w, int mode);                                     // 0x00ee1080
void  __cdecl SetWindowImage(IWindow* w, const ResourceKey& key, int frame);         // 0x00807bb0
void* __cdecl GetButtonDrawable(IWindow* w, int a);                                  // 0x00806880
void  __cdecl SetImageIcon(IWindow* w, void* drawable, int a);                       // 0x00806aa0
int   __cdecl GetIconIndex(IWindow* w, int index);                                   // 0x00eddee0
void  __cdecl SetImageIconFrom(IWindow* w, int* index, int a);                       // 0x00806b20
void  __cdecl SetChoiceRow(IWindow* w, bool last, int value);                        // 0x00ede040
void  __cdecl SyncTutorialState(int mode, uint32_t id);                              // 0x00ed8a30
class TutorialPanel {
public:
    uint32_t     pad00[4];
    cSPUILayout_s00ee_16f0* mpLayout;            // +0x10
    ProgressObj* mpProgress;          // +0x14
    IWindow*     mpWindow;            // +0x18
    CategoryWin** mpCategoryWins;     // +0x1c (6 entries)
    uint32_t     mID;                 // +0x20
    uint32_t     pad24[9];
    StateSync    mState;              // +0x48

    void UpdateHeader();                                                  // 0x00edef10
    void UpdateLayout();                                                  // 0x00edf410
    void Refresh();
    bool HandleMessage(uint32_t messageID, void* data);

    inline IWindow* FindWindow(uint32_t id)
    {
        IWindow* window = mpWindow;
        return window ? window->FindWindowByID(id, true) : 0;
    }
};
// ---- items of slice s00ee16f0 end

// ---- items of slice s00ee2860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_016c7aa4;
extern const wchar_t kEmptyStr[];              // 0x013ec468
extern "C" __declspec(dllimport) long __cdecl _wtol(const wchar_t*);   // 0x13cc4ec
extern "C" int wcscmp(const wchar_t*, const wchar_t*);
extern "C" int  FUN_00f0bea0();
extern "C" int   FUN_00ecb730();
extern "C" int  FUN_00ee1630(int);
extern "C" void* SP_MessageServer();
extern "C" void  SPUIHelpers_CreateCallbackWinProc(void*, void*, int, int, void*);
extern "C" void* FUN_00a206f0();                  // EA::Audio::GetSystemAT
extern "C" void  FUN_00ed8a30(int, int);          // cdecl 2
extern "C" int   FUN_00efc910();                  // ScenarioTutorials_GetObjectA
extern "C" int   FUN_00efe5c0();
extern "C" int   FUN_00ece300();                  // thiscall (obj)
extern "C" int   FUN_00dfbb60();                  // thiscall (obj)
extern "C" int   FUN_00f2bd10();                  // thiscall (obj)
extern "C" int   FUN_00f0bc80(int*);
extern "C" int   FUN_00edd310(void*, int, int);           // cdecl 3
extern "C" char  FUN_00edd370(void*, int, int);           // cdecl 3
extern "C" void* FUN_00edca20(void*);                     // cdecl 1
extern "C" void* SP_NounManager();                        // 0x00b3d300
extern "C" int   FUN_00efe930();                          // thiscall (0x15ad328, int)
extern "C" int   FUN_007f54d0();                          // thiscall () -> int
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long, wchar_t*, int) throw();   // msvcr90 import
typedef unsigned int   u32;
struct Mgrs {
    char pad00[0x10];
    int  f10;
    int  F3be60(int);
    int  F45970();
    int  F45a80();
    int  F3e8a0(int);                       // 0x00f3e8a0  TutorialManager::Find
    int* F3bf00(int, int);                  // 0x00f3bf00
    int  F43a10(int, int, int, int);        // 0x00f43a10
    void F427c0();                          // 0x00f427c0
};
#define MGR()  (*(Mgrs**)((char*)DAT_016c7aa4 + 0x74))
#define GD4()  (*(ChecklistUI**)((char*)DAT_016c7aa4 + 0xd4))
#define G7C()  (*(TipObj**)((char*)DAT_016c7aa4 + 0x7c))
#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VC3(p,off,a,b,c)(((int (__thiscall*)(void*,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c)))
struct cString_s00ee_2860 {
    cString_s00ee_2860();                              // 0x006b5060
    ~cString_s00ee_2860();                             // 0x006b5240
    void Load(u32 tableId, u32 instanceId, int def);   // 0x006b54b0
    const wchar_t* GetText();               // 0x006b55c0
    u32 mData[5];                           // retail size 0x14
};
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocator;
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};
struct TipObj {
    char    pad00[0x24];       // +0x00
    WString mHint;             // +0x24
    WString mText;             // +0x34
};
inline int CharStrlen(const wchar_t* p) throw()
{
    const wchar_t* p0 = p;
    while (*p)
        ++p;
    return (int)(p - p0);
}
extern const u32     kTutorialTypeTable[12];   // 0x0148a544
extern const u32     kTooltipIds[26];          // 0x0148a6a0
struct Lay {
    char pad[4];
    bool IsVisible();
    void SetVisibility(int);
    void* FindWindowByID(int, int);
    void* At(int);                         // 0x00e09c90 (ret 4)
};
struct Sub48 {
    char pad[4];
    void F9990(int);
    void FC0E0(int);
};
struct Pie {
    char pad[4];
    void Hide();
};
struct Win16 { char pad[4]; void F16F0(); };
struct Tut { bool F254D0(); };                              // 0x00f254d0 IsLocked
struct ChecklistUI {
    bool HasIndex();                       // 0x00ef72a0
    void ToggleHint(int, int);             // 0x00efbbe0
    void F67C8C0(u32, int);                // 0x0067c8c0 (ret 8)
    void F67C830(u32);                     // 0x0067c830 (ret 8)
};
struct NounMgr { void* GetAvatar(); };                      // 0x00b1fdb0
#define WGETTEXT(p) (((const wchar_t* (__thiscall*)(void*))VTP((p))[0x3c / 4])((void*)(p)))
struct Ed14 { void F6c0200(); };
bool __cdecl f00edf370(int p1, int* p2, int p3);
void __cdecl f00ee2860(int p1, cString_s00ee_2860* p2, cString_s00ee_2860* p3);
struct TextBuf { u32 m[5]; };                             // text container (retail frame 0x19c, object at +0x14)
class IWindow_s00ee_2860;
struct PaletteItem;
void __cdecl f00ee2960(IWindow_s00ee_2860*, PaletteItem*, bool, bool);
struct Beh {
    char pad[0x300];
    void F3020();
    void F30D0();
    void F3140(int);
    void F31D0();
    void F3540(void* item, void* list);
    void F3630(int arg);
    void F3710(int);
    void F3760(int*);
    void FEDD810();
    void FEDDA20();
    void FEDF240();
    void FEDF410();
    void FEDF4C0();
    void FEDF510();
    void FEE16F0();
    void FEDFBF0(int*);
    void FEDF2C0(int, int);
};
class IWindow_s00ee_2860 {
public:
    PV2 PV
    virtual void* Cast(uint32_t typeID) throw();                                  // +0x0c
    PV16 PV2 PV
    virtual void SetShadeColor(uint32_t color) throw();                           // +0x5c
    PV4 PV2 PV
    virtual void SetFlag(int flag, bool value) throw();                           // +0x7c
    virtual void SetCaption(const wchar_t* caption) throw();                      // +0x80
    PV16 PV8 PV2 PV
    virtual IWindow_s00ee_2860* FindWindowByID(uint32_t id, bool recursive) throw();         // +0xf0
};
namespace SP {
class cString_s00ee_2860 {
public:
    cString_s00ee_2860() throw();                                                            // 0x006b5060
    cString_s00ee_2860(uint32_t tableID, uint32_t instanceID, int flags) throw();            // 0x006b5770
    ~cString_s00ee_2860() throw();                                                           // 0x006b5240
    const wchar_t* GetText() throw();                                             // 0x006b55c0
    uint32_t mData[5];                                                    // retail size 0x14
};
}
struct PaletteItem {
    int     mType;          // +0x00 (index into kTypeImageInstance)
    int     mID;            // +0x04 (tutorial id, -1 none)
    int     mImageID;       // +0x08
    int     mCount;         // +0x0c
    uint8_t mFlag10;        // +0x10
    uint8_t pad11[3];
    uint8_t mFlags14;       // +0x14 (bit 0 = highlighted)
};
extern const uint32_t kTypeImageInstance[];                               // 0x0148a544
// ---- items of slice s00ee2860 end

// ---- items of slice s00ee3800 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   DAT_0148a9c8[];
extern "C" int  FUN_00efc8f0();
extern "C" void FUN_00edd810();
extern "C" int  FUN_00efc8c0(int);
extern "C" int   FUN_00eece20(int);                                  // 0x00eece20 (cdecl, 1 arg)
extern "C" void* FUN_0067caa0();                                     // WindowManager
extern "C" void* FUN_0080fee0();                                     // global at 0x0164cf5c
extern "C" void* FUN_00f473a0(int, const char*, int, int, int, int); // operator new
extern "C" void  FUN_00f47380(void*);                                // operator delete[]
extern "C" void  FUN_00ee3230(void);                                 // handler callback address
typedef unsigned char  u8;
extern u32   DAT_0148a960[];                                            // 5 UI column ids
struct Mgrs_s00ee_3800;
struct Ctl;
struct L18;
struct L48;
struct Bee;
struct Hee;
struct Editor {
    char  pad00[0x74];
    Mgrs_s00ee_3800* mpMgr;                                                        // +0x74
    char  pad78[0xd4 - 0x78];
    Ctl*  mpCtl;                                                        // +0xd4
};
extern Editor* DAT_016c7aa4_s00ee_3800;
#define MGR_s00ee_3800()  (DAT_016c7aa4_s00ee_3800->mpMgr)
#define CTL()  (DAT_016c7aa4_s00ee_3800->mpCtl)
struct Ctl {
    bool IsBusy();                                                      // 0x00ef72a0
    void Notify(int, int);                                              // 0x00efbbe0
};
struct Mgrs_s00ee_3800 {
    char pad00[0x10];
    int  f10;
    int  F3be60(int);                                                   // 0x00f3be60
    int  F45970();                                                      // 0x00f45970
    int  F45a80();                                                      // 0x00f45a80
    int  F427c0();                                                      // 0x00f427c0
    int  F3be30();                                                      // 0x00f3be30
    bool F3c750(void*, int);                                            // 0x00f3c750 (ret 8)
    bool F420d0(int, void*, int, int, int);                             // 0x00f420d0 (ret 0x14)
    int  F3e8a0(int);                                                   // 0x00f3e8a0 (ret 4)
    bool F40500(void*, int, int);                                       // 0x00f40500 (ret 0xc)
    bool F3e6d0(int, void*, int, int);                                  // 0x00f3e6d0 (ret 0x10)
};
struct SelObj {
    bool F25490();                                                      // 0x00f25490
    bool F25670();                                                      // 0x00f25670
};
struct SelCtx {
    uint32_t pad[0x188 / 4];                                            // uint32_t pad: no /GS cookie
    SelCtx();                                                           // 0x00f2bd10
    ~SelCtx();                                                          // 0x00dfbb60
};
#define VCP0(p,off)     (((void*(__thiscall*)(void*))             VTP(p)[(off)/4])((void*)(p)))
#define VCP2(p,off,a,b) (((void*(__thiscall*)(void*,int,int))     VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VC5(p,off,a,b,c,d,e) (((int (__thiscall*)(void*,int,int,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c),(int)(d),(int)(e)))
struct L18 {
    char pad[4];
    void F3630(int);                                                    // 0x00ee3630
    void FCD30(int);                                                    // 0x00edcd30
    void F30D0();                                                       // 0x00ee30d0
    void F3710(int);                                                    // 0x00ee3710
};
struct L48 { char pad[4]; void FBDD0(int); void FBD30(int); };
struct LayoutObj {                                                      // 0x18-byte UI layout node
    LayoutObj* Ctor();                                                 // 0x00810000
    void Setup(int, int, int);                                         // 0x008120d0 (ret 0xc)
    LayoutObj* Child(int, int);                                        // 0x008105b0 (ret 8)
};
struct Global164 {
    LayoutObj* Get(int);                                               // 0x00810620 (ret 4)
};
struct Obj84 {                                                          // 0x84-byte script object
    Obj84* Ctor();                                                     // 0x00edeb20
    void Bind(void*);                                                  // 0x00edec50 (ret 4)
};
struct Obj50 {                                                          // 0x50-byte acts-bar object
    Obj50* Ctor();                                                     // 0x00edbe00
    void Bind(void*);                                                  // 0x00edbac0 (ret 4)
};
struct ObjC8 {                                                          // 0xc8-byte behaviour object
    ObjC8* Ctor();                                                     // 0x0081a1f0
    void SetHandlers(int, void*);                                      // 0x00817eb0 (ret 8)
};
struct ObjC0 { void* mpVtbl0; void* mpVtbl1; u32 m8; };
struct VecMgr {                                                         // embedded at Bee+0x4c
    char  pad[0x70];
    void  Init(void*, void*);                                          // 0x00e0a4c0 (ret 8)
    void  AddColumn(int, int);                                         // 0x00e0a780 (ret 8)
    int   Count();                                                     // 0x00e09c80
    void* At(int);                                                     // 0x00e09c90 (ret 4)
};
struct Bee {
    char    pad00[0x18];
    void*   mp18;                                                       // +0x18
    void*   mp1c;                                                       // +0x1c
    void*   mp20;                                                       // +0x20
    void*   mp24;                                                       // +0x24
    void*   mp28;                                                       // +0x28
    char    pad2c[0x40 - 0x2c];
    LayoutObj* mp40;                                                    // +0x40
    LayoutObj* mp44;                                                    // +0x44
    void*   mp48;                                                       // +0x48
    VecMgr  mVec;                                                       // +0x4c
    ObjC8*  mpBC;                                                       // +0xbc
    ObjC0*  mpC0;                                                       // +0xc0
    u8      mC4;                                                        // +0xc4
    u8      mC5;                                                        // +0xc5
    char    padC6[0xf0 - 0xc6];
    int     mF0;                                                        // +0xf0
    int     mF4;                                                        // +0xf4
    int     mF8;                                                        // +0xf8
    int     mFC;                                                        // +0xfc
    int     m100;                                                       // +0x100

    void F3E40(char);
    void F3F20(int);
    bool F3940();
    void F40F0();
    void F12C0();                                                       // 0x00ee12c0
    void F31D0();                                                       // 0x00ee31d0
    void RebuildLists();                                                // 0x00edda20
    void ApplyPick(void*);                                              // 0x00eddc50
};
struct Hee {
    char  pad00[8];
    L18*  mp18;                                                         // this+8  (= Bee+0x18)
    char  pad0c[0xb4 - 0x0c];
    u8    mC4;                                                          // this+0xb4 (= Bee+0xc4)
    char  padB5[0x300];
    bool  F3F60(int, void*);                                            // 0x00ee3f60 (ret 8)
};
template <int NEWIDX, int OLDIDX, class T>
static __forceinline void SpSet(T** slot, T* p)
{
    T* old = *slot;
    if (p == old)
        return;
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[NEWIDX])(p);
    }
    *slot = p;
    if (old) {
        void** vt = *(void***)old;
        ((void(__thiscall*)(void*))vt[OLDIDX])(old);
    }
}
static __forceinline void SpSetC(void** slot, void* p)
{
    void* old = *slot;
    if (p == old)
        return;
    if (p) {
        void** vt = *(void***)((char*)p + 4);
        ((void(__thiscall*)(void*))vt[1])((char*)p + 4);
    }
    *slot = p;
    if (old) {
        void** vt = *(void***)((char*)old + 4);
        ((void(__thiscall*)(void*))vt[2])((char*)old + 4);
    }
}
struct Key3 { u32 mInstance, mType, mGroup; };
struct UintVec {                                                        // eastl::vector<u32>
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCapacity;
    u32  mAllocator[2];
    UintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(u32* pos, const u32& v);                         // 0x004558a0 (ret 8)
    void push_back(const u32& v)
    {
        if (mpEnd < mpCapacity) {
            if (mpEnd)
                *mpEnd = v;
            ++mpEnd;
        } else
            DoInsertValue(mpEnd, v);
    }
};
struct KeyVec {                                                         // eastl::vector<Key3>
    Key3* mpBegin;
    Key3* mpEnd;
    Key3* mpCapacity;
    u32   mAllocator[2];
    KeyVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
struct IdQuery {
    void*   mpVtbl;                                                    // +0x00 (vtable 0x13eb394)
    UintVec mIds;                                                      // +0x04
    u32     mId;                                                       // +0x18
    IdQuery(u32 id, const UintVec& ids);                               // 0x00669360 (ret 8)
};
struct IResourceManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void ResolveQuery(KeyVec*, IdQuery*, int);                 // +0x38
};
IResourceManager* GetManager();                                        // 0x0067dcd0
struct Rng {
    u32 RandomUint32Uniform(u32 n);                                    // 0x00a68fb0 (ret 4)
};
extern Rng sMathRandom;                                                // 0x01601760
static inline void SpFree(void* p)
{
    if (p && ((int*)p)[-1])
        FUN_00f47380(p);
}
// ---- items of slice s00ee3800 end

// ---- items of slice s00ee4390 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gToggleGrid;                                                 // 0x016c77b0
extern float gToggleSnap;                                                 // 0x016c77ac
extern const uint32_t kTimeLimits[6];                                     // 0x0148a4fc
extern const uint32_t kTimeLimitCount;                                    // 0x0148a514
extern const uint32_t kChoiceIDs[11];                                     // 0x0148a518
extern const uint32_t kChoiceIcons[12];                                   // 0x0148a544
struct Point {
    float x, y;
    Point() {}
    Point(float _x, float _y) : x(_x), y(_y) {}
    Point(const Point& o) : x(o.x), y(o.y) {}
};
struct RectT {
    float x1, y1, x2, y2;
    RectT& operator=(const RectT& other);                                 // 0x00572600
};
struct ColorRGB {
    float r, g, b;
    ColorRGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
};
uint32_t __cdecl ColorRGBToU32(const ColorRGB& c);                        // 0x00458a40
class IWindow_s00ee_4390 {
public:
    PV4
    virtual IWindow_s00ee_4390* GetParent();                                         // +0x10
    PV2
    virtual uint32_t GetControlID();                                      // +0x1c
    PV4
    virtual uint32_t GetShadeColor();                                     // +0x30
    PV
    virtual const RectT& GetRealArea();                                   // +0x38
    virtual const wchar_t* GetCaption();                                  // +0x3c
    PV4 PV2 PV
    virtual void SetShadeColor(uint32_t color);                           // +0x5c
    PV4
    virtual void SetLayoutLocation(float x, float y);                     // +0x70
    PV
    virtual void SetCursorID(uint32_t id);                                // +0x78
    PV16 PV
    virtual Point ToGlobalCoordinates(Point local);                       // +0xc0
    PV4 PV
    virtual void AddWindow(IWindow_s00ee_4390* window);                              // +0xd8
    virtual void RemoveWindow(IWindow_s00ee_4390* window);                           // +0xdc
    PV4
    virtual IWindow_s00ee_4390* FindWindowByID(uint32_t id, bool recursive);         // +0xf0
};
struct Message {
    IWindow_s00ee_4390* mSrc;                   // +0x00
    IWindow_s00ee_4390* mWindow;                // +0x04
    uint32_t mType;                  // +0x08
    union {
        struct { float x, y; int state; int button; } mouse;               // +0x0c
        struct { int a0, key, a2, a3; } keys;                              // +0x0c
        struct { int a0, a1, a2; IWindow_s00ee_4390* window; } focus;                 // +0x0c
        struct { int controlID; int value; int a2, a3; } button;           // +0x0c
    };
};
class IWindowManager {
public:
    PV
    virtual IWindow_s00ee_4390* GetMainWindow();                                     // +0x04
    PV2
    virtual void SendMsg(IWindow_s00ee_4390* src, IWindow_s00ee_4390* dst, const Message& msg, bool inheritable); // +0x10
    PV8 PV4 PV
    virtual IWindow_s00ee_4390* GetMainWindowIndex(int index);                       // +0x48
    virtual void SetFocusWindow(int index, IWindow_s00ee_4390* window);              // +0x4c
    PV2
    virtual void SetCaptureWindow(int index, IWindow_s00ee_4390* window);            // +0x58
    PV8 PV2
    virtual IWindow_s00ee_4390* GetModalWindow();                                    // +0x84
};
IWindowManager* __cdecl WindowManager();                                  // 0x0067caa0
IWindowManager* __cdecl GetUTFWinManager();                               // 0x00957f30
class IWinProc {
public:
    PV4 PV2
    virtual bool HandleUIMessage(IWindow_s00ee_4390* window, const Message& msg) = 0;
};
template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p);                                                   // 0x00572660 (out of line)
    AutoRefCount& operator=(T* p);                                        // 0x00b5f950
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
class cHideOnMoveScreenPosition;
struct HideOnMoveRef {
    cHideOnMoveScreenPosition* mpObject;
    HideOnMoveRef(cHideOnMoveScreenPosition* p);                          // 0x00572660
};
class cSPUILayout_s00ee_4390 {
public:
    IWindow_s00ee_4390* FindWindowByID(uint32_t id, bool recursive);                 // 0x008105b0
};
class cLayoutRoot {
public:
    IWindow_s00ee_4390* FindWindow(uint32_t id);                                     // 0x00810620
};
cLayoutRoot* __cdecl LayoutRoot();                                        // 0x0080fee0
namespace SP {
class cString_s00ee_4390 {
public:
    cString_s00ee_4390();                                                            // 0x006b5060
    ~cString_s00ee_4390();                                                           // 0x006b5240
    const wchar_t* GetText();                                             // 0x006b55c0
    uint32_t mData[5];                   // retail size 0x14 (dev PDB says 0x1c)
};
}
struct ChoiceVector {
    uint32_t mHeader[6];
    void*    mpBegin;                // +0x18
    void*    mpEnd;                  // +0x1c
    void*    mpCapacity;             // +0x20
    uint32_t mOverflow[3];           // +0x24
    uint8_t  mBuffer[0x154];         // +0x30
    int      mSelected;              // +0x184
    ChoiceVector();                                                       // 0x00f2bd10
    ~ChoiceVector();                                                      // 0x00dfbb60
};
class cHideOnMoveScreenPosition {
public:
    typedef void (__cdecl* Callback)(void*);
    cHideOnMoveScreenPosition(void* object, Callback callback, void* context); // 0x00edfe10
    virtual int AddRef();
    virtual int Release();
    PV2
    virtual void GetScreenPosition(float* x, float* y);                   // +0x10
    uint32_t mData[7];                   // sizeof 0x20
};
void* operator new(size_t size, const char* name, int, int, int, int);    // 0x00f473a0
class cSPUIPieMenu {
public:
    void Hide();                                                          // 0x00818330
    void RemoveAllItems();                                                // 0x00818c80
    void SetCallback(void (__cdecl* callback)(void*, int), void* context); // 0x008182c0
    void Show(float x, float y, cHideOnMoveScreenPosition* anchor, int flags); // 0x00819ad0
    void AddItem(uint32_t iconID, const wchar_t* text, uint32_t color, bool enabled); // 0x0081a940
};
struct ScenarioItem {                // returned by GetItem (0x00f3bf00)
    int      mKind;                  // +0x00
    int      mBehaviorA;             // +0x04
    int      mBehaviorB;             // +0x08
    uint32_t pad0c;
    bool     mbEnabled;              // +0x10
};
struct GoalEntry {                   // 0x188 bytes
    uint32_t pad00[3];
    int      mCount;                 // +0x0c
    uint8_t  pad10[0x188 - 0x10];
};
struct ActData {                     // returned by GetAct (0x00f3be60)
    uint8_t    mName[0x3c];          // +0x00 (string)
    uint8_t    mDescription[0x3c];   // +0x3c (string)
    int        mTimeLimit;           // +0x78
    bool       mbFlag7c;             // +0x7c
    uint8_t    pad7d[7];
    GoalEntry* mpGoals;              // +0x84
};
class ScenarioData {
public:
    int           GetCount();                                             // 0x00f3be30
    ActData*      GetAct(int act);                                        // 0x00f3be60
    int           GetActIndex(int act);                                   // 0x00f3bec0
    ScenarioItem* GetItem(int act, int index);                            // 0x00f3bf00
    int           GetItemObjectID(int* selected);                         // 0x00f3d780
    void*         IsValidSelection(int id);                               // 0x00f3dc70
    void*         Find(int id);                                           // 0x00f3e8a0
    void          Commit();                                               // 0x00f427c0
    void          MoveItem(int act, int index);                           // 0x00f43830
    void          RemoveAct(int act);                                     // 0x00f44210
    int           InsertAct(int act);                                     // 0x00f44a40
    void          BeginEdit();                                            // 0x00f45970
    void          EndEdit();                                              // 0x00f45a80
};
class cScenarioTutorialsChecklistUI {
public:
    void ToggleHint(int a, int b);                                        // 0x00efbbe0
};
class cScenarioMenu {
public:
    void Refresh();                                                       // 0x00ef7a80
};
class cScenarioUI {
public:
    cScenarioMenu* GetMenu(int index);                                    // 0x00ed4b50
};
struct GameGlobals_s00ee_4390 {
    uint32_t pad00[5];
    cScenarioUI* mpUI;                                                    // +0x14
    uint32_t pad18[0x74 / 4 - 6];
    ScenarioData* mpData;                                                 // +0x74
    uint32_t pad78[(0xd4 - 0x78) / 4];
    cScenarioTutorialsChecklistUI* mpChecklist;                           // +0xd4
};
extern GameGlobals_s00ee_4390* g_16c7aa4_s00ee_4390;
inline ScenarioData* GetScenarioData() { return g_16c7aa4_s00ee_4390->mpData; }
class cAvatarSelection {
public:
    PV2 PV
    virtual int GetSelectedWindow();                                      // +0x0c
};
struct cAvatar {
    uint8_t pad[0x5a8];
    cAvatarSelection mSelection;                                          // +0x5a8
};
class cGameNounManager_s00ee_4390 {
public:
    cAvatar* GetAvatar();                                                 // 0x00b1fdb0
};
cGameNounManager_s00ee_4390* __cdecl NounManager();                                  // 0x00b3d300
class cScenarioTutorials {
public:
    void SetSelectedWindow(int window);                                   // 0x00efe930
    void SurfaceQuery(int behavior);                                      // 0x00f00380
};
extern cScenarioTutorials g_15ad328;
class cPanelPart {
public:
    void Update();                                                        // 0x00ee30d0
};
void  __cdecl ScenarioTutorials_SetActive(int act);                       // 0x00efc8c0
int*  __cdecl GetSelectedBehavior();                                      // 0x00efc8f0
int   __cdecl GetCurrentBehaviorSet();                                    // 0x00efe5b0
bool  __cdecl GetSelectedID(int* out);                                    // 0x00edd2d0
IWindow_s00ee_4390* __cdecl FindSlotWindow(IWindow_s00ee_4390* w);                              // 0x00edca20
int   __cdecl GetSlotIndex(IWindow_s00ee_4390* w);                                   // 0x00edca60
bool  __cdecl IsSlotID(uint32_t id);                                      // 0x00edca90
bool  __cdecl IsButtonChecked(IWindow_s00ee_4390* w);                                // 0x00edcf30
void  __cdecl ListChoices(ChoiceVector* v, uint32_t id, int selected);    // 0x00edd310
bool  __cdecl IsChoiceAvailable(ChoiceVector* v, int set, int index);     // 0x00edd370
void  __cdecl GetChoiceName(ChoiceVector* v, int selected, SP::cString_s00ee_4390* name); // 0x00edd020
bool  __cdecl AssignString(void* dst, const wchar_t** text);              // 0x00edfce0
bool  __cdecl AssignBool(bool* dst, bool* value);                         // 0x00edfd30
bool  __cdecl AssignFromTable(int* dst, int index, const uint32_t* table, const uint32_t* count); // 0x00edfd70
bool  __cdecl AssignInt(int* dst, int* value);                            // 0x00edfda0
void  __cdecl MoveWindowTo(IWindow_s00ee_4390* w, Point p);                          // 0x00806ca0
bool  __cdecl IsSlotCompatible(int selected, int a, int b, int act);      // 0x00ee3800
bool  __cdecl CanPlace(ScenarioItem* item, int selected, uint32_t controlID, int index, bool commit); // 0x00ee41e0
bool  __cdecl IsTextFieldActive(IWindow_s00ee_4390* w, int a, int b);                // 0x00ec7490
bool  __cdecl IsEditing();                                                // 0x008053b0
void  __cdecl SetWindowVisible(IWindow_s00ee_4390* w, bool visible);                 // 0x00e12f80
void  __cdecl SetPageLabel(IWindow_s00ee_4390* w, int page);                         // 0x00ed1350
bool  __cdecl EndModal(IWindow_s00ee_4390* w, int ok, bool b);                      // 0x00809c50
bool  __cdecl BeginModal(IWindow_s00ee_4390* w, void* proc, bool b);                 // 0x008099a0
int   __cdecl GetRecorderState();                                         // 0x00435e90
void  __cdecl PlayUISound(uint32_t id, int state);                        // 0x00435ed0
void  __cdecl SetGlobalProperty(int id, float value);                     // 0x005ca880
void* __cdecl GetObjectByID(int id);                                      // 0x00b18e00
void  __cdecl ClearBehaviorSelection();                                   // 0x00ecb730
void  __cdecl ShowItemPanel(ScenarioItem* item);                          // 0x00f0bc80
void  __cdecl OnPieMenuChoice(void* context, int choice);                 // 0x00ee3430
void  __cdecl OnPieMenuMoved(void* context);                              // 0x00ee3400
class IPanelBase {
public:
    virtual void Destroy();
    uint32_t mRefCount;
};
class IPanelHandler {
public:
    virtual void HandleMessage();
};
namespace SP {
class cScenarioEditModeBehaviorUI : public IPanelBase, public IWinProc, public IPanelHandler {
public:
    uint32_t     pad10[2];
    cPanelPart*  mpPart;                // +0x18
    uint32_t     pad1c;
    IWindow_s00ee_4390*     mpWindow;              // +0x20
    uint32_t     pad24;
    IWindow_s00ee_4390*     mpPieWindow;           // +0x28
    uint32_t     pad2c[5];
    cSPUILayout_s00ee_4390* mpRenameLayout;        // +0x40
    cSPUILayout_s00ee_4390* mpDeleteLayout;        // +0x44
    uint32_t     pad48[0x1d];
    cSPUIPieMenu* mpPieMenu;            // +0xbc
    uint8_t      padc0[5];
    bool         mbNameFocused;         // +0xc5
    bool         mbPieMenuShown;        // +0xc6
    uint8_t      padc7;
    int          mPieSelection;         // +0xc8
    int          mPieSet;               // +0xcc
    int          mPieIndex;             // +0xd0
    AutoRefCount<IWindow_s00ee_4390> mpDragWindow; // +0xd4
    AutoRefCount<IWindow_s00ee_4390> mpDragParent; // +0xd8
    RectT        mDragArea;             // +0xdc
    uint32_t     mDragShade;            // +0xec
    uint32_t     padf0[5];
    int          mSlotA;                // +0x104
    int          mSlotB;                // +0x108

    void CommitName(IWindow_s00ee_4390* w, ActData* act);                            // 0x00ee3540
    void Refresh();                                                       // 0x00ee31d0
    void OnDragEnd();                                                     // 0x00edd810
    void OnNameFocus();                                                   // 0x00eddb00
    void OnNameBlur();                                                    // 0x00edcb10
    void OnButtonDefault();                                               // 0x00edcb40
    void ToggleGridButton();                                              // 0x00eddbe0
    void OnShare();                                                       // 0x00ee40f0
    cSPUIPieMenu* GetPieMenu() { return mpPieMenu; }

    virtual bool HandleUIMessage(IWindow_s00ee_4390* window, const Message& msg);
};
}
// ---- items of slice s00ee4390 end

// ---- items of slice s00ee6880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*    DAT_015fd918;         // 0x15fd918 app property list (also 0x15ac72c key)
extern const char DAT_013f6b3c[];     // 0x13f6b3c allocator name
extern "C" void*  cConnectionDialog_ctor(void* p);                                       // 0x810000
extern "C" bool   cSPUILayout_Init(void* layout, void* key, int a, int b);               // 0x8120d0
extern "C" void*  FUN_00eeab00(void* p);                                                 // 0xeeab00
extern "C" void*  FUN_005a5a50();                                                        // 0x5a5a50 (cX ctor)
extern "C" void*  FUN_00f32330(float* out);                                              // 0xf32330
extern "C" void*  FUN_00f32390(float* out);                                              // 0xf32390
extern "C" void*  FUN_00f32360(float* out);                                              // 0xf32360
extern "C" void*  FUN_00f32300(float* out);                                              // 0xf32300
extern "C" void   FUN_00e12f80(void* win, int a);                                        // 0xe12f80
extern "C" void   FUN_00ed1350(void* win, int a);                                        // 0xed1350
extern "C" void   FUN_00eea860(int a);                                                   // 0xeea860
extern "C" bool   FUN_00f31e50(void* ctx);                                               // 0xf31e50
extern "C" void   FUN_00f343a0(void* ctx, int a);                                        // 0xf343a0
extern "C" void*  FUN_00f0d3e0(void* ctx);                                               // 0xf0d3e0
extern "C" void*  FUN_00f31e40(void* ctx, void* a);                                      // 0xf31e40
extern "C" void   FUN_00eeb580(void* p, void* q);                                        // 0xeeb580
extern "C" void   FUN_00eeb920(void* out, void* ctx, void* p);                           // 0xeeb920
extern "C" void   FUN_00f344e0(void* ctx, void* a, void* b);                             // 0xf344e0
extern "C" void   FUN_00f34560(void* ctx);                                               // 0xf34560
extern "C" void   FUN_00f31ea0(void* ctx);                                               // 0xf31ea0 MsgSend
extern "C" void   FUN_00f33bf0(void* ctx);                                               // 0xf33bf0
extern "C" void   FUN_00f32150(void* ctx, float* v);                                     // 0xf32150
extern "C" void   FUN_00f321a0(void* ctx, float* v);                                     // 0xf321a0
extern "C" void   FUN_00f321f0(void* ctx, float* v);                                     // 0xf321f0
extern "C" void   FUN_00f32100(void* ctx, float* v);                                     // 0xf32100
extern "C" void   FUN_00eea910(void* ctx, void* p, float a, float b, float c);           // 0xeea910
extern "C" void   __fastcall FUN_005a6db0(void* self, int, void* p);                     // 0x5a6db0 Update
extern "C" void   __fastcall FUN_005a4200(void* self, int, int a);                       // 0x5a4200
extern "C" void   __fastcall FUN_005a4e20(void* self, int, const void* color);           // 0x5a4e20
extern "C" void   __fastcall FUN_00b5f950(void* self, int, void* p);                     // 0xb5f950 AutoRefCount assign
extern "C" void   __fastcall FUN_00f47630(void* self, int, void* p);                     // 0xf47630
extern "C" void   __fastcall FUN_00572620(void* self, int, void* p);                     // 0x572620
extern "C" bool   __fastcall FUN_00eea8e0(void* self, int, void* p);                     // 0xeea8e0
extern "C" void*  __fastcall FUN_00eeaa90(void* self, int, void* p, float* out);         // 0xeeaa90
extern u32      DAT_0148aac0[15];     // 0x148aac0
extern u32      DAT_0148aafc[15];     // 0x148aafc
extern u32      DAT_0148aa40[5];      // 0x148aa40 message ids
extern "C" void*  EAAllocate(u32 size, const char* name, int, int, int, int);            // 0xf473a0
extern "C" bool   cSPUILayout_SetParentWin_s00ee_6880(void* layout, void* win, int a, int b);       // 0x8121b0
extern "C" bool   FUN_006a25a0(void* props, u32 id);                                     // 0x6a25a0
extern "C" u32    FUN_00458a40(const float* rgb);                                        // 0x458a40 ColorRGBToU32
extern "C" u32    FUN_00f31c20(void* ctx, int a);                                        // 0xf31c20
extern "C" void   FUN_00435ed0(void* sys, u32 id);                                       // 0x435ed0 KissSetiEffects
extern "C" void*  FUN_00576ab0(void* out, u32 color);                                    // 0x576ab0 ColorToVector3
extern "C" void   FUN_005ca880(u32 id, float v);                                         // 0x5ca880 SetGlobalProperty
extern "C" void   __fastcall FUN_005a5ec0(void* self, int, void* win, u32 a, int b, int c);// 0x5a5ec0
extern "C" void*  __fastcall cSPUILayout_FindWindowByID(void* self, int, u32 id, int a); // 0x8105b0
#define CALL_CSPUILAYOUT_FindWindowByID cSPUILayout_FindWindowByID
static inline void vcall_void(void* o, int slot)
{
    (*(void(__thiscall**)(void*))((char*)*(void**)o + slot))(o);
}
struct IMsgHandler      { virtual void m00(); virtual ~IMsgHandler(); };       // vptr @ +0
struct GmeEditorResBase { virtual void g00(); virtual ~GmeEditorResBase(); };  // vptr @ +4
struct RefCountBlob     { virtual void r00(); virtual ~RefCountBlob(); };      // vptr @ +8
struct PadBase          { u32 m0c; PadBase() : m0c(0) {} };                    // +0x0c
struct Pane : IMsgHandler, GmeEditorResBase, RefCountBlob, PadBase {
    Pane();
    virtual ~Pane();
    u8        mb10;                 // +0x10
    u8        pad11[3];
    void*     mp14;                 // +0x14  window (AutoRefCount)
    void*     mp18;                 // +0x18  layout
    void*     mp1c;                 // +0x1c  sub control
    void*     mp20;                 // +0x20  colour picker
    void*     mp24;                 // +0x24
    void*     mp28;                 // +0x28  handler id
    u32       m2c, m30, m34, m38;   // +0x2c..+0x38
};
// ---- items of slice s00ee6880 end

// ---- items of slice s00ee7990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl GetPlanetRec();                                     // 0x10212a0
extern "C" void* __cdecl GetSpeciesMgr();                                    // 0xb3d420
extern "C" extern void* g_universe;                                          // 0x16c7aa4
struct Rect { float x, y, w, h; };
struct VI                       // generic refcounted object
{
    virtual void v00();          // +0x00 AddRef
    virtual void v01();          // +0x04 Release
    virtual void v02();          // +0x08 Destroy
    virtual void v03(int);       // +0x0c
    virtual void v04(int);       // +0x10
    virtual void v05();          // +0x14
    virtual void v06(int);       // +0x18
    virtual void v07(int);       // +0x1c
    virtual void v08(int);       // +0x20
    virtual void v09();          // +0x24
    virtual void v10();
    virtual void v11();
};
struct VIN                      // same object, every slot takes no arguments
{
    virtual void n00();          // +0x00
    virtual void n01();          // +0x04
    virtual void n02();          // +0x08
    virtual void n03();          // +0x0c
    virtual void n04();          // +0x10
    virtual void n05();          // +0x14
    virtual void n06();          // +0x18
    virtual void n07();          // +0x1c
    virtual void n08();          // +0x20
    virtual void n09();          // +0x24
    virtual void n10();
    virtual void n11();
};
struct XWin                     // UTFWin::IWindow-like window
{
virtual void  w00();
virtual void  w01();
virtual void  w02();
virtual void  w03(int);
virtual void  w04(int);
virtual void  w05();
virtual void  w06(int);
virtual void  w07();
virtual void  w08(int);
virtual void  w09();
virtual void  w10();
virtual void  w11();
virtual void  w12();
virtual void  w13();
virtual Rect* w14();
virtual void  w15();
virtual void  w16();
virtual void  w17();
virtual void* w18(int);
virtual void  w19();
virtual void  w20(int);
virtual void w21();
virtual void  w22();
virtual void  w23();
virtual void  w24();
virtual void  w25();
virtual void  w26();
virtual void  w27(Rect*);
virtual void  w28();
virtual void  w29();
virtual void  w30();
virtual void  w31(int, int);
virtual void  w32();
virtual void  w33();
virtual void  w34();
virtual void  w35();
virtual void  w36();
virtual void  w37();
virtual void  w38();
virtual void  w39();
virtual void  w40();
virtual void  w41();
virtual void  w42();
virtual void  w43();
virtual void  w44();
virtual void  w45();
virtual void  w46();
virtual void  w47();
virtual void  w48();
virtual void  w49();
virtual void  w50();
virtual void  w51();
virtual void  w52();
virtual void  w53();
virtual void  w54();
virtual void  w55();
virtual void  w56();
virtual void  w57();
virtual void  w58();
virtual void  w59();
virtual void* w60(int, int);
virtual void w61();
virtual u8 w62(int);
virtual void w63();
virtual void  w64();
virtual void  w65(void*);
};
struct XW2                     // object stored at +0x170
{
virtual void x00();
virtual void x01();
virtual void x02();
virtual void x03();
virtual void x04();
virtual void x05();
virtual void x06();
virtual int  x07();
};
struct XMsgSrv                 // SP::MessageServer
{
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09(void*, u32);
virtual void m10();
    virtual void m11(void*, u32, int);
};
struct XLayout                  // cSPUILayout
{
    bool  Init(const void* key, bool a, u32 flags);              // 0x8120d0
    void  Shutdown(u32 flags);                                   // 0x811ad0
    void* FindWindowByID(u32 id);                                // 0x8105b0
    void* FindWindowByID(u32 id, bool a);                        // 0x8105b0
    void* FindWindowByID(u32 id, bool a, void* out);             // 0x8105b0
    bool  SetParentWin(void* parent, bool a, u32 flags);         // 0x8121b0
    bool  IsVisible();                                           // 0x810070
    void* GetWin();                                              // 0x810570
};
struct XPaletteUI               // cSPPaletteUI
{
    void UpdateCategories(void* arg);                            // 0x5ca980
    int  FindCategoryIndex();                                    // 0x5ca9c0
    int  FindCategoryIndex(int b);                               // 0x5ca9c0
    void Shutdown();                                             // 0x5cba90
};
struct XSub                     // 0x70-byte sub-object at +0x18/+0x88/+0xf8
{
    void  Ctor();                                                // 0xe0a390
    void  Dtor();                                                // 0xe0a400
    void  Reset();                                               // 0xe0a5c0
    bool  Check(void* w);                                        // 0xe0a4c0
    bool  CheckKey(const void* key, int n);                      // 0xe0a780
    void* Get(int i);                                            // 0xe09c90
};
struct XDialog                  // cConnectionDialog
{
    XDialog* Ctor();                                             // 0x810000
};
struct XObj3c                   // object allocated with size 0x3c
{
    void* Init();                                                // 0xee6e80
};
struct XHint                    // UI::cScenarioTutorialsChecklistUI
{
    void ToggleHint(u32 a, u32 b);                               // 0xefbbe0
};
struct XUniv                    // SP::cSPLivingUniverse
{
    void F33bf0();                                               // 0xf33bf0
    void F352c0(u32 v);                                          // 0xf352c0
    void F34560();                                               // 0xf34560
    void F31ea0();                                               // 0xf31ea0
    void F36380();                                               // 0xf36380
    void F363c0();                                               // 0xf363c0
};
struct XSpecMgr                 // SP::cPlantSpeciesManager
{
    void* GetAt(u32 elem);                                       // 0xb90410
};
struct XSpecies
{
    u32 GetID();                                                 // 0xb8f860
};
struct XCat
{
    u8   FindCategory(u32 id, int* outCat, u8* outFlag);         // 0xee7910
    bool IsInTable(u32 id);                                      // 0xee78c0
    void Refresh(u8 which);                                      // 0xee8240
};
struct XLaunchCtx               // 0x48-byte launch context
{
    u32 v[18];
    void Ctor();                                                 // 0x644b10
    void Dtor();                                                 // 0x644b60
};
struct XGObj                    // object whose address is 0x16c7c08
{
    void Add(u32 v);                                             // 0xf01090
};
struct SpuEd
{
    u32 o000; u32 o004; u32 o008; u32 o00c; u32 o010; u32 o014; u32 o018; u32 o01c;
    u32 o020; u32 o024; u32 o028; u32 o02c; u32 o030; u32 o034; u32 o038; u32 o03c;
    u32 o040;
    u32 pad44[70];
    u32 o15c; u32 o160; u32 o164; u32 o168; u32 o16c; u32 o170;

    void  BaseDtor();                                            // 0x00ee7990
    void  DtorDerived();                                         // 0x00ee7a50
    void  SetMode(int mode, u8 on);                              // 0x00ee7b40
    void  Update(void* arg);                                     // 0x00ee7c60
    SpuEd* Ctor();                                               // 0x00ee7da0
    void  Dtor3();                                               // 0x00ee7e50
    u8    InitLayout(void* parent);                              // 0x00ee7f00
    void  ShutdownLayout();                                      // 0x00ee8110
    u8    OnMsg2(u32 msg, void* p);                              // 0x00ee8180
    void  UpdateCategory(u32 sel);                               // 0x00ee82c0
    void  SetObject(void* obj);                                  // 0x00ee83a0
    void  Select(void* win);                                     // 0x00ee8460
    void  Dtor4();                                               // 0x00ee8570
    void  Enable2(u8 on);                                        // 0x00ee85e0
    u8    OnMsg3(u32 msg, void* p);                              // 0x00ee86c0
    u8    SetSource(void* src);                                  // 0x00ee8720
    void  Close();                                               // 0x00ee87f0
};
int  __cdecl FindPlanetSlot(u32 id, int* outA, int* outB);       // 0x00ee7cb0
void __cdecl Fn1350(void* win, u8 flag);                         // 0x00ed1350
void __cdecl Fn2fa0(void* win, u32 arg);                         // 0x00e12fa0
void __cdecl LaunchCtx(XLaunchCtx* ctx);                         // 0x64a990
extern "C" XMsgSrv* __cdecl MessageServer();                                 // 0x67dcc0
extern "C" XWin* __cdecl WindowManager_s00ee_7990();                                    // 0x67caa0
extern "C" void  __cdecl RemoveHandler(void* server, void* handler, u32 id, int a, int b); // 0x571db0
extern "C" extern u32   g_univ18;                                            // 0x16c7c18
extern "C" extern XGObj g_launchObj;                                         // 0x16c7c08
extern "C" extern const u32 g_catA[];                                        // 0x148aac0
extern "C" extern const u32 g_catB[];                                        // 0x148aafc
// ---- items of slice s00ee7990 end

// ---- items of slice s00ee8860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_013c8a60();                                 // 0x13c8a60 atexit callback
extern void FUN_013c8a50();                                 // 0x13c8a50 atexit callback
extern uint32_t gRegFlags;                                  // 0x16c7820 registration guard
extern float gVec3X;       // 0x16c7894
extern float gVec3Y;       // 0x16c7898
extern float gVec3Z;       // 0x16c789c
extern void* gTableA[15];  // 0x148aac0
extern void* gTableB[15];  // 0x148aafc
extern void* gSelObject;   // 0x16c7824
#pragma intrinsic(_ReadWriteBarrier)
struct IWindow_s00ee_8860;
struct cSPUILayout_s00ee_8860;
struct cSPPalette;
struct OBJ174;
struct OBJ14;
struct LayoutRecord;
struct cSPPaletteInfo;
struct UIEditor;
struct EffectsHandle;
struct TutorialsUI;
#define PV_s00ee_8860(n) virtual void _pv##n();
struct Matrix3 { float m[9]; };
struct VObj_s00ee_8860 { void* mpVtbl; };
struct IWindow_s00ee_8860 {
    virtual void   V00();
    virtual void   V04();
    virtual void   V08();
    virtual void*  AsInterface(uint32_t id);        // 0x0c
    virtual void*  V10();                           // 0x10
    virtual void   V14();
    virtual void   V18();
    virtual void   V1c(int a);                      // 0x1c
    virtual void   V20();
    virtual void   V24();
    virtual void   V28(int a, int b);               // 0x28
    virtual void   V2c();
    virtual int    V30(int a);                      // 0x30
    virtual void   V34();
    virtual float* V38();                           // 0x38
    PV_s00ee_8860(3c) PV_s00ee_8860(40) PV_s00ee_8860(44) PV_s00ee_8860(48) PV_s00ee_8860(4c) PV_s00ee_8860(50) PV_s00ee_8860(54) PV_s00ee_8860(58)
    PV_s00ee_8860(5c) PV_s00ee_8860(60) PV_s00ee_8860(64) PV_s00ee_8860(68) PV_s00ee_8860(6c)
    virtual void   V70(float f);                    // 0x70
    PV_s00ee_8860(74) PV_s00ee_8860(78)
    virtual void   V7c(int a, int b);               // 0x7c
    PV_s00ee_8860(80) PV_s00ee_8860(84) PV_s00ee_8860(88) PV_s00ee_8860(8c) PV_s00ee_8860(90) PV_s00ee_8860(94) PV_s00ee_8860(98) PV_s00ee_8860(9c)
    PV_s00ee_8860(a0) PV_s00ee_8860(a4) PV_s00ee_8860(a8) PV_s00ee_8860(ac) PV_s00ee_8860(b0) PV_s00ee_8860(b4) PV_s00ee_8860(b8) PV_s00ee_8860(bc)
    PV_s00ee_8860(c0) PV_s00ee_8860(c4) PV_s00ee_8860(c8) PV_s00ee_8860(cc) PV_s00ee_8860(d0) PV_s00ee_8860(d4) PV_s00ee_8860(d8) PV_s00ee_8860(dc)
    PV_s00ee_8860(e0) PV_s00ee_8860(e4) PV_s00ee_8860(e8) PV_s00ee_8860(ec)
    virtual void*  Vf0(uint32_t id, int a);         // 0xf0
    PV_s00ee_8860(f4) PV_s00ee_8860(f8) PV_s00ee_8860(fc) PV_s00ee_8860(100)
    virtual void   V104(void* pOwner);              // 0x104
};
namespace EA {
template <class T>
class RefCountVTemplate_s00ee_8860 {
 public:
    RefCountVTemplate_s00ee_8860() : mRefCount(0) {}
    virtual ~RefCountVTemplate_s00ee_8860();                  // 0x00
    virtual int AddRef();                          // 0x04
    virtual int Release();                         // 0x08
    virtual int GetRefCount();                     // 0x0c
    T mRefCount;
};  // namespace EA
}
struct RefCountInt {
    virtual void _dtor(int flag);                  // 0x00
    int mRefCount;                                 // 0x04
    int AddRef() { return ++mRefCount; }
    int Release() {
        int r = --mRefCount;
        if (r == 0) {
            mRefCount = 1;
            (*(void(__thiscall**)(int)) * (void**)this)(1);
        }
        return r;
    }
};
struct RefCount04 {
    virtual void AddRef();
    virtual void Release();
};
struct IMsgHandler_s00ee_8860 {
    virtual uint8_t Msg0(void* sender, void* msg);  // 0x00
    virtual uint8_t Msg1(void* sender, void* msg);  // 0x04
};
struct IMsgServer {
    PV_s00ee_8860(00) PV_s00ee_8860(04) PV_s00ee_8860(08) PV_s00ee_8860(0c) PV_s00ee_8860(10)
    virtual void Send(uint32_t id, void* msg, void* extra);  // 0x14
};
template <class T>
struct AutoRefCount_s00ee_8860 {
    T* mpObject;
    AutoRefCount_s00ee_8860() : mpObject(0) {}
    AutoRefCount_s00ee_8860(T* p) : mpObject(p) {}
    AutoRefCount_s00ee_8860& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
namespace EA {
namespace ResourceMan {
struct Key_s00ee_8860 {
    uint32_t instanceID;  // +0x00
    uint32_t typeID;      // +0x04
    uint32_t groupID;     // +0x08
};  // namespace ResourceMan
}
}
struct cSPUILayout_s00ee_8860 {
    IWindow_s00ee_8860* FindWindowByID(uint32_t id, bool recurse);      // 0x8105b0
    uint8_t  SetVisibility(bool visible);                    // 0x810590
};
struct cSPUILayoutManager_s00ee_8860 {
    IWindow_s00ee_8860* GetWorldMainWindow(uint32_t id);                // 0x810620
};
namespace SPUIHelpers {
cSPUILayoutManager_s00ee_8860* GetLayoutManager();                      // 0x805070
}
namespace SPUIHelpers {
void SetWindowImage(IWindow_s00ee_8860* w, const EA::ResourceMan::Key_s00ee_8860* key, int a);  // 0x807bb0
}
struct cSPPalettePageUI {
    uint8_t pad00[0x10];
    void*   m10;                                             // +0x10
};
struct cSPPaletteCategoryUI {
    cSPPalettePageUI* GetPageUI(int index);                  // 0x5c2e50
};
struct cSPPaletteUI {
    cSPPaletteUI();                                          // 0x5cb3b0
    virtual int  AddRef();                                   // 0x00
    virtual int  Release();                                  // 0x04
    void Init(cSPPalette*, IWindow_s00ee_8860* pOwner, int a, cSPPaletteInfo* pInfo);  // 0x5cb5a0
    void SetVisible(uint8_t visible);                        // 0x5cb180
    void SetCurrentCategoryIndex(int index);                 // 0x5cb240
    void SetFlag(uint8_t v);                                 // 0x5ca900
    int  FindCategoryIndex();                                // 0x5ca9c0
    cSPPaletteCategoryUI* GetSubCategory(int index);         // 0x5cae30
    uint8_t pad04[0x6c - 0x04];                              // sizeof == 0x6c
};
struct cSPPalette : EA::RefCountVTemplate_s00ee_8860<int> {
    cSPPalette();                                            // 0x5c5e30
    bool Init(const EA::ResourceMan::Key_s00ee_8860& key, int modelType, int a, int b,
              int c, int d, int e);                          // 0x5c6340
    uint8_t pad08[0x40 - 0x08];                              // sizeof == 0x40
};
struct cSPPaletteInfo : EA::RefCountVTemplate_s00ee_8860<int> {
    cSPPaletteInfo();                                        // 0x5c64e0
    AutoRefCount_s00ee_8860<RefCountInt> m08;                           // +0x08
    uint32_t     m0c;                                        // +0x0c
    RefCount04*  m10;                                        // +0x10
    AutoRefCount_s00ee_8860<UIEditor> m14;                              // +0x14
    uint16_t     m18;                                        // +0x18
    uint8_t      pad1a[0x34 - 0x1a];                         // sizeof == 0x34
};
struct UIEditor {
    UIEditor();                                              // 0xeccaf0
    virtual void AddRef();                                   // 0x00
    virtual void Release();                                  // 0x04
    PV_s00ee_8860(08) PV_s00ee_8860(0c) PV_s00ee_8860(10) PV_s00ee_8860(14) PV_s00ee_8860(18)
    virtual void F1c();                                      // 0x1c
    uint8_t pad04[0xd0 - 0x04];                              // sizeof == 0xd0
};
struct OBJ64 : EA::RefCountVTemplate_s00ee_8860<int> {
    OBJ64();                                                 // 0xf3a470
    virtual uint8_t F4(void* p);                             // 0x10
    PV_s00ee_8860(14) PV_s00ee_8860(18)
    uint8_t pad08[0x40 - 0x08];                              // sizeof == 0x40
    void Fn3b0c0();                                          // 0xf3b0c0
};
struct OBJ28 : EA::RefCountVTemplate_s00ee_8860<int>, IMsgHandler_s00ee_8860 {
    OBJ28() : m0c(0), m10(0), m14(0), m18(0), m1c(0), m20(0), m24(0) {}
    virtual uint8_t F4();                                    // 0x10 (0xb1fbf0)
    virtual void    F5();                                    // 0x14 (0xc2e4e0)
    virtual void    SetVisible(bool visible);                // 0x18 (0xee85e0)
    virtual void    F7(int a);                               // 0x1c (0xee9350)
    uint8_t Msg0(void* sender, void* msg);
    uint8_t Msg1(void* sender, void* msg);

    uint32_t m0c, m10, m14, m18, m1c, m20;
    AutoRefCount_s00ee_8860<EffectsHandle> m24;                         // +0x24
};
struct EffectPose {
    uint16_t flags;    // +0x00  ORed 4 then 2 by the caller
    uint16_t refs;     // +0x02  bumped three times
    float    pos[3];   // +0x04
    float    f;        // +0x10
    Matrix3  mat;      // +0x14
};
struct EffectsHandle {
    virtual void V00();
    virtual void Release();                                  // +0x04
    virtual void V08(int a);                                 // +0x08
    virtual void V0c(int a);                                 // +0x0c
    virtual void V10();
    virtual void V14(EffectPose* p);                         // +0x14
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30(bool a);                                // +0x30
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual void V40();
    virtual void V44(int a, float* b, int c);                // +0x44
};
struct EffectsManager {
    PV_s00ee_8860(00) PV_s00ee_8860(04) PV_s00ee_8860(08) PV_s00ee_8860(0c) PV_s00ee_8860(10) PV_s00ee_8860(14) PV_s00ee_8860(18) PV_s00ee_8860(1c) PV_s00ee_8860(20) PV_s00ee_8860(24) PV_s00ee_8860(28)
    virtual void V2c(int a, int b, AutoRefCount_s00ee_8860<EffectsHandle>* pOut);  // 0x2c
};
struct EffectSlot {
    void* mpObject;   // +0x00
    void* mpOwner;    // +0x04
    float Fn1ff0();   // 0xf31ff0
    float Fn1b70();   // 0xf31b70
};
struct Obj10 {
    virtual void V0();                                       // 0x00
    virtual void V4();                                       // 0x04
    virtual void V8();                                       // 0x08
    virtual void Release();                                  // 0x0c
    virtual void V10();                                      // 0x10
    virtual void V14();                                      // 0x14
    virtual void V18();                                      // 0x18
    virtual void SetVisible(uint8_t visible);                // 0x1c
    void Fn6bd0();                                           // 0xee6bd0
};
struct ObjC {
    virtual void AddRef();                                   // 0x00
    virtual void Release();                                  // 0x04
    PV_s00ee_8860(08)
    void* field10;                                           // +0x10
};
struct OBJ14 : EA::RefCountVTemplate_s00ee_8860<int> {
    OBJ14() : mpC(0), mp10(0) {}
    virtual uint8_t F4();                                    // 0x10
    virtual uint8_t F5(void* p);                             // 0x14
    virtual void    F6();                                    // 0x18
    virtual void    F7();                                    // 0x1c
    virtual void    SetVisible(uint8_t visible);             // 0x20 (0xee9130)
    uint32_t m08;                                            // +0x08 (untouched)
    ObjC*    mpC;                                            // +0x0c
    Obj10*   mp10;                                           // +0x10
    OBJ14*   ScalarDeletingDtor(unsigned char flags);        // 0xee90e0
};
struct Vec12 {
    EA::ResourceMan::Key_s00ee_8860* mBegin;   // +0x00
    EA::ResourceMan::Key_s00ee_8860* mEnd;     // +0x04
    EA::ResourceMan::Key_s00ee_8860* mCap;     // +0x08
    void erase(EA::ResourceMan::Key_s00ee_8860* pos);                   // 0xeeee40
    void DoInsertValue(EA::ResourceMan::Key_s00ee_8860* pos, const EA::ResourceMan::Key_s00ee_8860& v);  // 0x4e3e10
    void push_back(const EA::ResourceMan::Key_s00ee_8860& v) {
        if (mEnd < mCap) {
            EA::ResourceMan::Key_s00ee_8860* p = mEnd;
            mEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(mEnd, v);
        }
    }
};
struct VecU32 {
    uint32_t* mBegin;   // +0x00
    uint32_t* mEnd;     // +0x04
    uint32_t* mCap;     // +0x08
    void DoInsertValue(uint32_t* pos, const uint32_t& v);    // 0x4558a0
};
struct VecF32 {
    float* mBegin;      // +0x00
    float* mEnd;        // +0x04
    float* mCap;        // +0x08
    void DoInsertValue(float* pos, const float& v);          // 0x455660
};
struct PlanetRecord {
    uint8_t  pad00[0xbc];
    Vec12    mBc;          // +0xbc  vector<Key>
    uint8_t  padC8[0xf8 - 0xc8];
    VecU32   mF8;          // +0xf8  vector<uint32>
    uint8_t  pad104[0x10c - 0x104];
    float    m10c;         // +0x10c
    VecF32   m110;         // +0x110  vector<float>
};
struct LayoutRecord {
    virtual void V00();                                      // 0x00
    virtual int  Release();                                  // 0x04
    PV_s00ee_8860(08) PV_s00ee_8860(0c) PV_s00ee_8860(10) PV_s00ee_8860(14) PV_s00ee_8860(18)
    virtual uint32_t Fn1c();                                 // 0x1c
};
struct OBJ174Ifc4 {
    virtual void Fn(int* arg);                               // 0xee97f0
    uint8_t pad04[0x160 - 0x04];
    LayoutRecord* m170;                                      // subobject + 0x160
};
struct OBJ174 : EA::RefCountVTemplate_s00ee_8860<int>, IMsgHandler_s00ee_8860 {
    OBJ174();                                                // 0xee7da0
    virtual uint8_t F4(void* p);                             // 0x10 (0xee7f00)
    virtual uint8_t F5(void* p);                             // 0x14 (0xee8110)
    virtual void    SetVisible(bool visible);               // 0x18 (0xee92b0)

    uint32_t mBase3;                                         // +0x0c (3rd base vptr)
    uint32_t mBase4;                                         // +0x10 (4th base vptr)
    uint8_t  pad14[0x160 - 0x14];
    LayoutRecord* mEntry;                                    // +0x160
    uint32_t      m164;                                      // +0x164
    cSPUILayout_s00ee_8860*  mLayout;                                   // +0x168
    uint32_t      m16c;                                      // +0x16c
    LayoutRecord* m170;                                      // +0x170

    uint8_t Msg0(void* sender, void* msg);
    uint8_t Msg1(void* sender, void* msg);

    void Update();                                           // 0xee8d80
    void AddEntry(LayoutRecord* e);                          // 0xee95a0
    void SetEntry(LayoutRecord* e, EA::ResourceMan::Key_s00ee_8860* arg);  // 0xee9690
    void Fn8460(IWindow_s00ee_8860* w);                                 // 0xee8460
    void Fn7910(LayoutRecord* e, int* pIdx, uint8_t* pFlag); // 0xee7910
};
struct Space {
    uint8_t pad00[0x10];
    RefCountInt* m10;                                        // +0x10
    uint8_t pad14[0x160 - 0x14];
    LayoutRecord* m160;                                      // +0x160
    uint8_t pad164[0x168 - 0x164];
    cSPUILayout_s00ee_8860* m168;                                       // +0x168
    uint8_t pad16c[0x1b0 - 0x16c];
    void* m1b0;                                              // +0x1b0
    void  F33BF0();                                          // 0xf33bf0
    void  F34560();                                          // 0xf34560
    void* F32790(void* p);                                   // 0xf32790
    void  FnC2E4E0();                                        // 0xc2e4e0
};
struct C40 : EA::RefCountVTemplate_s00ee_8860<int>, IMsgHandler_s00ee_8860 {
    virtual uint8_t Setup(int a);                            // 0x10 (0xee8860)
    virtual void    F5fn();                                  // 0x14
    virtual void    SetVisible(uint8_t visible);             // 0x18 (0xee8cb0)
    virtual void    F7fn();                                  // 0x1c

    uint8_t Msg0(void* sender, void* msg);
    uint8_t Msg1(void* sender, void* msg);

    AutoRefCount_s00ee_8860<OBJ14>        mObj14;       // +0x0c
    AutoRefCount_s00ee_8860<OBJ28>        mObj28;       // +0x10
    AutoRefCount_s00ee_8860<OBJ64>        mObj64;       // +0x14
    AutoRefCount_s00ee_8860<OBJ174>       mObj174;      // +0x18
    AutoRefCount_s00ee_8860<cSPPalette>   mPalette;     // +0x1c
    AutoRefCount_s00ee_8860<cSPPaletteUI> mPalUI;       // +0x20
    AutoRefCount_s00ee_8860<UIEditor>     mEditor;      // +0x24
    int   mState;                            // +0x28
    void* mC2c;                              // +0x2c
    void* mC30;                              // +0x30
    void* mC34;                              // +0x34
    void* mC38;                              // +0x38
    void* mC3c;                              // +0x3c

    C40();                                                   // 0xee9180
    void Update();                                           // 0xee9260
    void Fn7b40(int idx, uint8_t visible);                   // 0xee7b40
};
void* operator new(unsigned int size, const char* pName, int flags,
                   unsigned debugFlags, const char* file, int line);  // 0xf473a0
void  operator delete(void* p);                             // 0xf47380
void* MessageServer_s00ee_8860();                                      // 0x67dcc0
void* EffectsManagerPtr();                                  // 0x67ddd0
int   FUN_00ee7cb0(uint32_t key, int* a, int* b);           // 0xee7cb0
void* GetActivePlanet();                                    // 0x1021260
void* GetActivePlanetRecord();                              // 0x10212a0
struct EAThunk {
    void* Fn414c0();                                        // 0x8414c0
    void  FnC2f80();                                        // 0xc82f80
    void  Fn2bbe0();                                        // 0xb2bbe0
};
void* FUN_00b3d3b0();                                       // 0xb3d3b0
void* FUN_00efe5b0();                                       // 0xefe5b0
void* FUN_00b18e00(void* p);                                // 0xb18e00
void  eastl_move(void* dst, const void* src, uint32_t n);   // 0x11e0744
void  Matrix3_AssignFrom(void* self, const void* q);        // 0x41cb40
void* Matrix3FromQuaternion(void* out, void* q);            // 0x59c190
int   atexit(void (*fn)());                                 // 0x11e07ef
double floor(double x);                                     // 0x11e0906
struct cRegNode {
    void  Construct(void* arg);                             // 0x692f60
    uint8_t Flag();                                         // 0xab30c0
    void  Fallback();                                       // 0x692850
};
struct TutorialsUI {
    void ToggleHint(int a, int b);      // 0xefbbe0
    void ClearPending();                // 0xef72b0
};
static inline TutorialsUI* GetTutorialsUI() {
    return *(TutorialsUI**)(*(int*)0x16c7aa4 + 0xd4);
}
static inline void* GetSpacePtr() {
    return *(void**)(*(int*)0x16c7aa4 + 0x18);
}
template <class R, class T, int Off>
static inline R vcallR(T* p) {
    typedef R (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; return (p->*f)();
}
// ---- items of slice s00ee8860 end

// ---- items of slice s00ee9840 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Entry;
struct IWindow_s00ee_9840;
class cSPUILayout_s00ee_9840;
struct IHost;
struct IWindow_s00ee_9840 {
    virtual void  AddRef() {}
    virtual void  Release() {}
    virtual void  Shutdown() {}
    virtual void* AsInterface(uint32_t id) { return 0; }       // 0x0c
    virtual IHost* GetHost() { return 0; }                     // 0x10
    virtual void  V5()  {} virtual void V6()  {} virtual void V7()  {} virtual void V8()  {}
    virtual void  V9()  {} virtual void V10() {} virtual void V11() {} virtual void V12() {}
    virtual void  V13() {}
    virtual float* GetBox() { return 0; }                      // 0x38
    virtual void  V15() {} virtual void V16() {} virtual void V17() {} virtual void V18() {}
    virtual void  V19() {} virtual void V20() {} virtual void V21() {} virtual void V22() {}
    virtual void  SetColor(uint32_t) {}                        // 0x5c
    virtual void  V24() {} virtual void V25() {} virtual void V26() {} virtual void V27() {}
    virtual void  SetPos2(float, float) {}                     // 0x70
    virtual void  V29() {}
    virtual void  SetTextId(uint32_t) {}                       // 0x78
    virtual void  Cmd2(int, int) {}                            // 0x7c
    virtual void  V32() {} virtual void V33() {} virtual void V34() {} virtual void V35() {}
    virtual void  V36() {} virtual void V37() {} virtual void V38() {} virtual void V39() {}
    virtual void  V40() {} virtual void V41() {} virtual void V42() {} virtual void V43() {}
    virtual void  V44() {} virtual void V45() {} virtual void V46() {} virtual void V47() {}
    virtual void  V48() {} virtual void V49() {} virtual void V50() {} virtual void V51() {}
    virtual void  V52() {} virtual void V53() {} virtual void V54() {} virtual void V55() {}
    virtual void  V56() {} virtual void V57() {} virtual void V58() {} virtual void V59() {}
    virtual void  V60() {} virtual void V61() {} virtual void V62() {} virtual void V63() {}
    virtual void  V64() {}
    virtual void  Show(void*) {}                               // 0x104
    virtual void  Hide(void*) {}                               // 0x108
};
struct IHost {
    void SetOwner(void* p);
};
struct IWinButton {
    virtual void V00() {} virtual void V04() {} virtual void V08() {} virtual void V0c() {}
    virtual void V10() {} virtual void V14() {} virtual void V18() {} virtual void V1c() {}
    virtual uint32_t GetState() { return 0; }                  // 0x20
};
class cSPUILayout_s00ee_9840 { public:
    virtual void V0() {}
    virtual void AddRef() {}                                   // 0x04
    virtual void Release() {}                                  // 0x08
    cSPUILayout_s00ee_9840* Ctor();                                       // 0x810000
    uint8_t  Init(const void* pKey, uint8_t a, uint32_t id);   // 0x8120d0
    uint8_t  SetParentWin(IWindow_s00ee_9840* pWin, uint8_t a, uint32_t id); // 0x8121b0
    IWindow_s00ee_9840* FindWindowByID(uint32_t id, uint8_t recurse);     // 0x8105b0
    void     Shutdown(uint32_t a);                             // 0x811ad0
};
struct IRefObj {
    virtual void V0() {}
    virtual void V4() {}
    virtual void AddRef() {}                                   // 0x08
    virtual void Release() {}                                  // 0x0c
    uint8_t pad0[0x38];
    void*   mBegin;                                            // +0x3c
    void*   mEnd;                                              // +0x40
};
struct Msg {
    void*    mObj;      // +0x00
    uint32_t mUnk04;    // +0x04
    uint32_t mType;     // +0x08
    uint32_t mId;       // +0x0c
    uint32_t mUnk10;    // +0x10
    uint32_t mUnk14;    // +0x14
};
struct RectF {
    uint8_t pad[0xc];
    float   mX;         // +0x0c
    float   mY;         // +0x10
};
struct ColorRGB_s00ee_9840 { float r, g, b; };
struct IAudioSystem {
    virtual void V00() {} virtual void V04() {} virtual void V08() {} virtual void V0c() {}
    virtual void V10() {} virtual void V14() {} virtual void V18() {} virtual void V1c() {}
    virtual uint32_t GetCounter() { return 0; }                // 0x20
    virtual void V24() {} virtual void V28() {} virtual void V2c() {}
    virtual void V30() {} virtual void V34() {}
    virtual void F38(uint32_t) {}                              // 0x38
    virtual void V3c() {}
    virtual void F40(uint32_t, uint32_t) {}                    // 0x40
    virtual void V44() {} virtual void V48() {} virtual void V4c() {}
    virtual void V50() {} virtual void V54() {}
    virtual void F58() {}                                      // 0x58
};
void*  FUN_00ee7850(void* p);                // 0xee7850
void   FUN_00ee7cb0(void* a, void* b, uint32_t c); // 0xee7cb0
uint32_t FUN_00ee7810(Msg* msg);             // 0xee7810
uint8_t FUN_00c70c00(void* pThis);            // 0xc70c00
void*  FUN_008414c0(void* pThis);            // 0x8414c0
void   FUN_00c82f80(void* pThis);            // 0xc82f80
void   FUN_00b2bbe0(void* pThis);            // 0xb2bbe0
void*  GetRecorderState_s00ee_9840();                   // 0x435e90
void   KillSetiEffects(uint32_t id, void* sys); // 0x435ed0
void   SetGlobalProperty(uint32_t id, float v); // 0x5ca880
IAudioSystem* GetSystemAT();                 // 0xa206f0
void*  MessageServer_s00ee_9840();                      // 0x67dcc0
struct RefMsg {
    void SetIRefCount(int a, void* p);       // 0x5726e0
};
struct TutorialsUI_s00ee_9840 {
    void ToggleHint(int a, int b);              // 0xefbbe0
};
uint32_t ColorRGBToU32(const float* pColor); // 0x458a40
IWinButton* InterfaceCast_IWinButton(IWindow_s00ee_9840* p); // 0x5ca960
void*  GetSpeciesManager();                  // 0x401090
struct SpeciesMgr;
struct ProfileVector {
    void* mBegin;   // +0x00
    void* mEnd;     // +0x04
    void* mCap;     // +0x08
    void  Ctor(int a);                          // 0xb9a5b0
    void  Dtor();                               // 0x7a41a0
};
struct SpeciesMgr {
    int GetMatchingPlantProfiles(ProfileVector* v, int a, uint32_t b); // 0x4dfd50
};
struct Space_s00ee_9840 {
    void F33BF0();                              // 0xf33bf0
    void F32410();                              // 0xf32410
    void F34560();                              // 0xf34560
};
struct Host {
    void Fn8240(int a);                         // 0xee8240
    void Fn82C0(uint32_t a);                    // 0xee82c0
    void Fn83A0(void* p);                       // 0xee83a0
    void Fn8460(void* p);                       // 0xee8460
    void Fn95A0(void* p);                       // 0xee95a0
    void Fn9690(void* a, void* b);              // 0xee9690
};
struct IMsgServer_s00ee_9840 {
    virtual void V00() {} virtual void V04() {} virtual void V08() {} virtual void V0c() {}
    virtual void V10() {}
    virtual void Send(uint32_t id, void* msg, void* extra) {}  // 0x14
};
struct Obj { void* mpVtbl; };
template <class T, int Off, class A>
static inline void vcallA(T* p, A a) {
    typedef void (T::*PMF)(A);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)(a);
}
template <class T, int Off, class A, class B>
static inline void vcallAB(T* p, A a, B b) {
    typedef void (T::*PMF)(A, B);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)(a, b);
}
template <class R, class T, int Off, class A>
static inline R vcallRA(T* p, A a) {
    typedef R (T::*PMF)(A);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; return (p->*f)(a);
}
template <class T, int Off>
static inline void vcallv_vol(T* p) {
    typedef void (T::*PMF)();
    void* fn = ((void**)*(void* volatile**)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)();
}
struct RefCountPart {
    void*  mpVtbl;      // +0x00
    int    mRefCount;   // +0x04
    void*  QueryInterface(uint32_t id);         // 0xeea780
};
struct Entry {
    void**   mpVtbl;      // +0x00 -> 0x148acb8
    void*    mRefVtbl;    // +0x04 -> 0x148aca8
    int      mRefCount;   // +0x08
    IWindow_s00ee_9840* mOwner;      // +0x0c  (parent window passed to Init)
    IWindow_s00ee_9840* mWin0;       // +0x10
    IWindow_s00ee_9840* mWinA;       // +0x14
    IWindow_s00ee_9840* mWinB;       // +0x18
    IWindow_s00ee_9840* mWinSlider;  // +0x1c  (gradient handle)
    IWindow_s00ee_9840* mWinHandle;  // +0x20
    cSPUILayout_s00ee_9840* mLayout; // +0x24
    IRefObj* mPoints;     // +0x28
    uint8_t  mPressed;    // +0x2c
    float    mPos;        // +0x30  (normalized 0..1)
    ColorRGB_s00ee_9840 mColor;      // +0x34
    uint8_t  mUnk40;      // +0x40
    uint8_t  mUnk41;      // +0x41
    float    mGrabX;      // +0x44
    float    mGrabY;      // +0x48
    float    mAnchorX;    // +0x4c
    uint8_t  mDragging;   // +0x50

    void  Ctor();                                        // 0xee9be0
    void  Dtor();                                        // 0xee9c70
    void  SetVisible(uint8_t visible);                   // 0xee9d00
    void  Update(void* a);                               // 0xee9de0
    void  Shutdown();                                    // 0xee9e50
    void  SetRect(int a, RectF* pRect, uint8_t flag);    // 0xee9e90
    void  TrackPoint(void* pWin, RectF* pPoint);         // 0xee9f10
    void  SetColor(ColorRGB_s00ee_9840 color);                     // 0xeea190
    void  NotifyChanged();                               // 0xeea260
    void  OnClick(int a, int b);                         // 0xeea2f0
    uint8_t Init(IWindow_s00ee_9840* pOwner, float pos, float r, float g, float b,
                 IRefObj* pPoints);                      // 0xeea3c0
    uint8_t DoMessage(uint32_t msgId, Msg* msg);         // 0xeea6d0
};
int Entry_PosGreater(Entry* a, Entry* b);                // 0xeea760
struct MsgHandler {
    uint8_t Handle(IWindow_s00ee_9840* sender, Msg* msg);           // 0xee9840
};
// ---- items of slice s00ee9840 end

// ---- items of slice s00eea7c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct View;  struct Entry_s00ee_a7c0;
struct Vec3 { float x, y, z; };
struct IWindow_s00ee_a7c0;
class cSPUILayout_s00ee_a7c0 { public:
    virtual void V0() {}
    virtual void Release() {}
    virtual void Shutdown() {}
    uint8_t  Init(const void* pKey, uint8_t a, uint32_t id);              // 0x8120d0
    uint8_t  SetParentWin(IWindow_s00ee_a7c0* pWin, uint8_t a, uint32_t id);         // 0x8121b0
    IWindow_s00ee_a7c0* FindWindowByID(uint32_t id, uint8_t recurse) const;          // 0x8105b0
    void     Shutdown(uint32_t a);                                       // 0x811ad0 (non-virtual)
};
void*  MessageServer_s00ee_a7c0();                                                          // 0x67dcc0
float*   ColorToVector3(float* out, uint32_t c);        // 0x576ab0
void     FUN_00bbe970(void* b, void* e);                            // 0xbbe970
void     FUN_00b90a40(void* b, void* e);                            // 0xb90a40
void     FUN_00e26410(void* b, void* e, int depth, int cmp);        // 0xe26410
void     FUN_00e25bd0(void* b, void* e);                            // 0xe25bd0 (vector erase)
void     FUN_00aea5d0(void* pEnd, void** pValue);                   // 0xaea5d0 (vector push)
static const float kOne  = 1.0f;      // 0x1485720
static const float kHalf = 0.5f;      // 0x1471064
static const float kZero = 0.0f;      // 0x1485378
static const float kDefR = 0.3254902f; // 0x148ad3c
static const float kDefG = 0.6862745f; // 0x148ad40
static const float kDefB = 0.3254902f; // 0x148ad3c
struct IWindow_s00ee_a7c0 {
    virtual void  AddRef() {}
    virtual void  Release() {}
    virtual void  Shutdown() {}
    virtual void  V3()  {}
    virtual void  V4()  {} virtual void V5()  {} virtual void V6()  {} virtual void V7()  {}
    virtual void  V8()  {} virtual void V9()  {} virtual void V10() {} virtual void V11() {}
    virtual void  V12() {} virtual void V13() {}
    virtual float* GetBox() { return 0; }                     // 0x38
    virtual void  V15() {} virtual void V16() {} virtual void V17() {} virtual void V18() {}
    virtual void  V19() {} virtual void V20() {} virtual void V21() {} virtual void V22() {}
    virtual void  SetColor(uint32_t) {}                       // 0x5c
    virtual void  V24() {} virtual void V25() {} virtual void V26() {} virtual void V27() {}
    virtual void  V28() {} virtual void V29() {}
    virtual void  SetTextId(uint32_t) {}                      // 0x78
    virtual void  V31() {}
    virtual void  SetText(const void*) {}                     // 0x80
    virtual void  V33() {} virtual void V34() {} virtual void V35() {}
    virtual void  V90() {}                                    // 0x90
    virtual void  V37() {} virtual void V38() {} virtual void V39() {} virtual void V40() {}
    virtual void  V41() {} virtual void V42() {} virtual void V43() {} virtual void V44() {}
    virtual void  V45() {} virtual void V46() {} virtual void V47() {} virtual void V48() {}
    virtual void  V49() {} virtual void V50() {} virtual void V51() {} virtual void V52() {}
    virtual void  V53() {} virtual void V54() {} virtual void V55() {} virtual void V56() {}
    virtual void  V57() {} virtual void V58() {} virtual void V59() {} virtual void V60() {}
    virtual void  V61() {} virtual void V62() {} virtual void V63() {} virtual void V64() {}
    virtual void  Show(void*) {}                               // 0x104
    virtual void  Hide(void*) {}                               // 0x108
};
struct IWinObj {
    virtual void  V0() {}
    virtual void  V1() {}
    virtual void  V2() {}
    virtual void* AsInterface(uint32_t id) { return 0; }        // 0x0c
    virtual void  V4() {} virtual void V5() {} virtual void V6() {} virtual void V7() {}
    virtual void  V8() {} virtual void V9() {}
    virtual void  Cmd(uint32_t a, uint32_t b) {}                // 0x28
};
template <class T, int Off>
static inline void vcallv(T* p) {
    typedef void (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    (p->*f)();
}
struct Entry_s00ee_a7c0 {
    void**   mpVtbl;      // +0x00 -> 0x148acb8
    void*    mRefVtbl;    // +0x04 -> 0x148aca8 (RefCountVTemplate<int>)
    int      mRefCount;   // +0x08
    int      mUnk0c;      // +0x0c
    int      mUnk10;      // +0x10
    void*    mWinA;       // +0x14  (IWindow*, matched against an id)
    void*    mWinB;       // +0x18  (IWindow*, matched against an id)
    int      mUnk1c;      // +0x1c
    int      mUnk20;      // +0x20
    void*    mLayout;     // +0x24  (used as the cSPUILayout* for FindWindowByID)
    int      mUnk28;      // +0x28
    uint8_t  mUnk2c;      // +0x2c
    float    mPos;        // +0x30  (sort key, normalized 0..1)
    float    mColorR;     // +0x34
    float    mColorG;     // +0x38
    float    mColorB;     // +0x3c
    uint8_t  mUnk40;      // +0x40
    uint8_t  mUnk41;      // +0x41
    int      mUnk44;      // +0x44
    int      mUnk48;      // +0x48
    float    mUnk4c;      // +0x4c
    uint8_t  mUnk50;      // +0x50

    void SetColor(float r, float g, float b);            // 0xeea190
    Entry_s00ee_a7c0* Ctor();                                       // 0xee9be0 (returns this)
};
typedef Entry_s00ee_a7c0* EntryPtr;
struct View {
    void**   mpVtbl0;        // +0x00 -> 0x148ad1c
    void*    mpVtbl1;        // +0x04 -> 0x148ad00
    void*    mpVtbl2;        // +0x08 -> 0x148acf0
    int      mUnk0c;         // +0x0c
    IWindow_s00ee_a7c0* mWinParent;     // +0x10
    IWindow_s00ee_a7c0* mAssetView;     // +0x14  (ref-counted asset view)
    IWindow_s00ee_a7c0* mWinB;          // +0x18
    IWindow_s00ee_a7c0* mWinRenderWindow;      // +0x1c
    IWindow_s00ee_a7c0* mWinBakingIndicator;   // +0x20
    cSPUILayout_s00ee_a7c0* mLayout;    // +0x24
    void*    mMsgServer;     // +0x28
    void*    mMsgTarget;     // +0x2c
    void*    mMsgIds;        // +0x30 -> 0x148ad44 (3 u32 ids)
    uint32_t mMsgCount;      // +0x34 (=3)
    uint32_t mMsgUser;       // +0x38 (=0)
    Entry_s00ee_a7c0**  mEntriesBegin;  // +0x3c
    Entry_s00ee_a7c0**  mEntriesEnd;    // +0x40
    Entry_s00ee_a7c0**  mEntriesCap;    // +0x44
    uint8_t  mUnk48[8];      // +0x48
    void*    mLayout2;       // +0x50  (ref-counted)
    float    mUnk54;         // +0x54
    float    mUnk58;         // +0x58

    // slice methods
    void     ShowChildren(uint8_t visible);              // 0xeea7c0
    void     OnAssetChanged(void* pChanged);             // 0xeea860
    Entry_s00ee_a7c0*   FindByWinID(void* id);                      // 0xeea8b0
    uint8_t  HasWin(void* id);                           // 0xeea8e0
    void     SetEntryColor(void* id, float r, float g, float b); // 0xeea910
    void     Dtor();                                     // 0xeea960
    uint8_t  DoMessage(uint32_t msgId, void* msg);       // 0xeeaa40
    void     GetEntryColor(float* pOut, void* id);       // 0xeeaa90
    void*    Ctor();                                     // 0xeeab00
    void     SampleColor(float* pOut, float x);          // 0xeeab90
    void     Bake(void* pTarget);                        // 0xeeacc0
    void     ShutdownView();                             // 0xeeae70
    void     Rebuild(uint8_t notify);                    // 0xeeaf00
    uint8_t  Init(IWindow_s00ee_a7c0* pParent);                     // 0xeeb280
    void     SetPoints(int* pPositions, int* pColors);   // 0xeeb580
};
void NotifyEntryChanged(Entry_s00ee_a7c0* p);                              // 0xeea260
// ---- items of slice s00eea7c0 end

// ---- items of slice s00eeb770 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int* g_016c7a24;
extern int  g_016c7a28;
extern void* g_0167ecd0;                 // ray-query context object (value at 0x0167ecd0)
extern float g_13ec478;                  // == 0.05f
extern void* g_016c7a58;                                     // vector allocator
struct Vec3i { int x, y, z; };
struct Manager_s00ee_b770;
struct GlobalObj_s00ee_b770 {
    char  pad0[0x18];
    void* f18;               // +0x18
    char  pad1[0x58];
    Manager_s00ee_b770* f74;            // +0x74
    char  pad2[0x5c];
    void* fd4;               // +0xd4  (scenario tutorial UI singleton)
};
extern GlobalObj_s00ee_b770* g_16c7aa4_s00ee_b770;
struct Manager_s00ee_b770 {
    int   FUN_00f3be30();
    void* FUN_00f3d780(int a);
    void* FUN_00f3bcb0();
    void* FUN_00f3e8a0(int key);
};
struct XGet { int Get18(); };
void* __cdecl FUN_005bf860(void* a, int b);
void  __cdecl FUN_005bf120(void* a, void* b, int c, int d);
struct ListEntry {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24(int);
    char pad[0x28];
    char flag;               // +0x2c
};
struct VtObj32 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78(int);
virtual void v7c(int, bool);
};
struct AudioObj {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual int  v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void v38(unsigned);
    virtual void v3c();
    virtual void v40(unsigned, unsigned);
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void v58();
};
struct MsgObj {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void v14(unsigned, int, int);
};
struct LayoutObj_s00ee_b770 {
    void* FindWindowByID(unsigned int id, bool recursive);   // 0x008105b0
};
AudioObj* __cdecl GetSystemAT_s00ee_b770();                             // 0x00a206f0
MsgObj*   __cdecl GetMsgServer();                            // 0x0067dcc0
ListEntry** __cdecl FUN_00b6f4f0(ListEntry** first, ListEntry** last, ListEntry** out, ListEntry** value);
ListEntry** __cdecl FUN_006782c0(ListEntry** first, ListEntry** last, ListEntry** out);   // do_copy
void __cdecl FUN_00e26de0(void** first, void** last, void* cmp);                          // SortRecordsA
struct CCList {
    char pad0[0x14];
    VtObj32* f14;            // +0x14
    char pad1[0x0c];
    LayoutObj_s00ee_b770* layout;       // +0x24
    char pad2[0x14];
    ListEntry** begin;       // +0x3c
    ListEntry** end;         // +0x40
};
struct FloatVec {
    float* begin;            // +0x00
    float* end;              // +0x04
    float* cap;              // +0x08
};
struct Vec3Vec {
    Vec3* begin;             // +0x00
    Vec3* end;               // +0x04
    Vec3* cap;               // +0x08
};
void* __cdecl FUN_004b5ad0(void* slot, const Vec3* v);       // SpVector<Vector3>::DoInsertValue
void* __cdecl FUN_00455660(void* slot, const float* v);      // SpVector<float>::DoInsertValue
struct PlanetObj {
    void  DirectionToSurfacePosition(float* out, float* dir);     // 0x00b815a0
    float GetRadiusAt(float* dir);                                // 0x00b7ef70
    float FUN_00b7e500();                                         // 0x00b7e500
    float GetWaterHeight();                                       // 0x00b7e390
};
PlanetObj* __cdecl SP_PlanetModel();                              // 0x00b3d350
struct __declspec(align(16)) RayHitResult {
    int   hit;          // 0x00
    int   r04;          // 0x04
    int   r08;          // 0x08
    int   r0c;          // 0x0c
    float px;           // 0x10
    float py;           // 0x14
    float pz;           // 0x18
    int   r1c;          // 0x1c
    int   rz[4];        // 0x20
};
void __cdecl FUN_00b65b10(float* a, void* ctx, int c, int d, int e, RayHitResult* out);
struct PhysObj {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual int  QueryInterface(unsigned id);                    // v0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
    virtual int  vB8(unsigned id);
};
struct BodyObj {
    bool FUN_00f25680();                                       // body validity check
};
struct SurfObj {
    void FUN_00c9ff40(void* v, void* a, void* b);              // surface query -> two floats
};
void* __cdecl SP_normalized_safe(void* out, float* v);
bool __cdecl FUN_006a0ae0(void* param_1, void* alloc, int* outCount, void** outData);
// ---- items of slice s00eeb770 end

// ---- items of slice s00eed3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   DAT_016c7a28;
extern int   DAT_016c7a38;
extern int   DAT_015ac948;
extern int   DAT_015ac94c;
extern char  DAT_015acb40;
extern float g_1485720;     // 1.0f
extern float g_16c7934, g_16c7944, g_16c7954, g_16c7964, g_16c7974, g_16c7984;
extern float g_16c7994, g_16c79a4, g_16c79b4, g_16c79c4, g_16c79d4, g_16c79e4;
extern float g_15ac950;     // planet radius
extern void* g_167ecd0;     // hkWorld
extern "C" bool      FUN_005bf7c0(int*, int);
extern "C" bool      FUN_00eebfc0(int*, int);
extern "C" int       FUN_00eec760(int*, int);
extern "C" unsigned  FUN_00eec870(int);
extern "C" void*     FUN_00eeca60(void* out, const void* in);
extern "C" bool      GetPropertyT(void* list, unsigned hash, void* out);   // 0x0040cf10
extern const char aSimulator_013f09b4[];            // 0x013f09b4 "Simulator"
extern "C" bool FUN_005bf0e0(int, int**);
#define VCF(p,off)      (((float (__thiscall*)(void*))     VTP(p)[(off)/4])((void*)(p)))
#define VCP(p,off)      (((float* (__thiscall*)(void*))    VTP(p)[(off)/4])((void*)(p)))
struct ResourceKey_s00ee_d3f0 {
    unsigned mInstanceID;   // +0x00
    unsigned mTypeID;       // +0x04
    unsigned mGroupID;      // +0x08
};
struct cNoun {
    unsigned mInstanceID;   // +0x00
    unsigned mTypeID;       // +0x04
    unsigned mGroupID;      // +0x08
    void*    mPropList;     // +0x0c
    char     pad10[0x210];
    float    mField220;     // +0x220

    char fn255d0();         // 0x00f255d0
    char fn25680();         // 0x00f25680
    char fn256e0();         // 0x00f256e0
    char fn256a0();         // 0x00f256a0
};
struct cPropertyOwner {
    char pad00[0x0c];
    void* mPropList;        // +0x0c
};
struct Mgr {
    cNoun* fn3f00();            // 0x00ff3f00
    cNoun* fn3e8a0(int key);    // 0x00f3e8a0
    void*  fn3d780(void* a);    // 0x00f3d780
};
struct GlobalObj_s00ee_d3f0 {
    char pad00[0x74];
    Mgr* mManager;              // +0x74
};
extern GlobalObj_s00ee_d3f0* DAT_016c7aa4_s00ee_d3f0;
namespace EA {
struct Variant_s00ee_d3f0 {
    unsigned       mData[4];    // +0x00
    unsigned short mFlags;      // +0x10
    unsigned short mTypeId;     // +0x12
    Variant_s00ee_d3f0() : mFlags(0), mTypeId(0) {}
    void SetU32(const unsigned& v);     // 0x00427fd0
    void SetInt(const int& v);          // 0x00422eb0
    void Destruct(bool b);              // 0x0093db80
};
}
struct IPropList {
    virtual int  AddRef();                          // +0x00
    virtual int  Release();                         // +0x04
    virtual void s2();                              // +0x08
    virtual void s3();                              // +0x0c
    virtual void s4();                              // +0x10
    virtual void SetProperty(unsigned hash, EA::Variant_s00ee_d3f0* value);   // +0x14
};
namespace SP {
struct cPropertyList_s00ee_d3f0 : IPropList {
    char pad04[0x34];
    cPropertyList_s00ee_d3f0();                                // 0x006a1c40
};
}
struct PropMgr {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
    virtual bool GetPropertyList(unsigned instance, unsigned group, IPropList** out);  // +0x2c
};
struct PropRef38 {
    char pad00[0x38];
    int  mType;                 // +0x38
};
template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    IntrusivePtr& operator=(T* pNew) {
        if (pNew != mpObject) {
            T* const pOld = mpObject;
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct IRefObj_s00ee_d3f0 {
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
};
struct cPropertyBag : IRefObj_s00ee_d3f0 {
    bool GetInt32(unsigned key, int* out);          // 0x00613660
};
struct cPollinatorLookup {
    bool LookupByKey(const ResourceKey_s00ee_d3f0* key, IRefObj_s00ee_d3f0** out, bool touch);   // 0x006138b0
};
struct PollinatorHolder {
    char pad00[0x5c];
    cPollinatorLookup* mLookup; // +0x5c
};
class __declspec(align(16)) hkVector4_s00ee_d3f0 {
public:
    float x, y, z, w;
    hkVector4_s00ee_d3f0() {}
};
struct RadialRay {
    hkVector4_s00ee_d3f0 mPos;             // +0x00
    float     mH0;              // +0x10
    float     mH1;              // +0x14
};
struct RayHitResult_s00ee_d3f0 {
    int       mStatus;          // +0x00
    unsigned  mPad04[3];
    hkVector4_s00ee_d3f0 mPos;             // +0x10
    hkVector4_s00ee_d3f0* mNormalOut;      // +0x20
    float*    mDistOut;         // +0x24
    void*     mUserData;        // +0x28
    void*     mEntity;          // +0x2c
};
class hkWorld_s00ee_d3f0;
struct cPlanetModel_s00ee_d3f0;
struct RayObj;
struct NounMgr_s00ee_d3f0 {
    void* FUN_00b21000(unsigned type, unsigned inst);   // 0x00b21000
};
extern "C" bool      FUN_005bf120_s00ee_d3f0(const void* key, IPropList* list, int a, void* b);
extern "C" unsigned  FUN_00eece20_s00ee_d3f0(const void* p);
extern "C" float     FUN_00eed280(cNoun* key, int extra);
extern "C" NounMgr_s00ee_d3f0*  FUN_00b3d300();
extern "C" PropMgr*  FUN_0067de30();
extern "C" PollinatorHolder* FUN_0067cb30();
extern "C" cPlanetModel_s00ee_d3f0* FUN_00b3d350();
extern "C" void      FUN_00b668c0(RadialRay* r, cPlanetModel_s00ee_d3f0* planet, hkWorld_s00ee_d3f0* world,
                                  RayObj* obj, bool useWorld, RayHitResult_s00ee_d3f0* out, bool adjust);
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);     // 0x00f473a0
struct Prop { char pad[4]; int* GetInt(); };
struct RefObj { virtual void v0(); virtual void Release(); };
struct SpinOwner {
    void** mVtable;             // +0x00
    char   pad04[0x6d];
    char   mField71;            // +0x71
};
struct SpinOut {
    unsigned mFlags;            // +0x00
    int      mField04;          // +0x04
    int      mState;            // +0x08
    float    mValue;            // +0x0c
    unsigned mFlags2;           // +0x10
};
struct cSpinPoint {
    int   mField00;             // +0x00
    float mX;                   // +0x04
    float mY;                   // +0x08
    float mZ;                   // +0x0c
};
// ---- items of slice s00eed3f0 end

// ---- items of slice s00eede20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gQuatRef[];              // 0x015ac960
struct ResourceKey_s00ee_de20 {
    uint32_t instanceID, typeID, groupID;
    ResourceKey_s00ee_de20() {}
    ResourceKey_s00ee_de20(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct Vector3 { float x, y, z; };
struct Quaternion;
#define SLOT(n) virtual void s##n();
struct Spatial {
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    virtual int GetV2c();                                      // +0x2c
    virtual int GetV30();                                      // +0x30
    SLOT(13)
    virtual void SetPosition(const Vector3* p);                // +0x38
    virtual void SetOrientation(const Quaternion* q);          // +0x3c
    virtual void SetScale(float f);                            // +0x40
    SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26)
    SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36)
    virtual void SetModelKey(const ResourceKey_s00ee_de20* k);            // +0x94
    virtual const ResourceKey_s00ee_de20* GetModelKey();                  // +0x98
    uint32_t pad4[0x4c / 4 - 0];                               // +0x04..+0x50
    uint32_t mFlags;                                           // +0x50
    uint32_t pad54[(0xa4 - 0x54) / 4];                         // to +0xa4
    uint8_t mPadA4[3];
    uint8_t mbFlagA7;                                          // +0xa7
    uint8_t mDataA8[4];                                        // +0xa8
};
struct Noun {
    virtual int AddRef();                                      // +0
    virtual int Release();                                     // +4
    SLOT(2)
    virtual void* Cast(uint32_t typeId);                       // +0xc
    SLOT(4) SLOT(5) SLOT(6) SLOT(7)
    virtual uint32_t GetNounID();                              // +0x20
    SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
    virtual void SetFlag54(int v);                             // +0x54
    uint32_t pad4[(0x18 - 4) / 4];
    int mField18;                                              // +0x18
    int mField1c;                                              // +0x1c
    uint32_t pad20[(0x34 - 0x20) / 4];
    Spatial mSpatial;                                          // +0x34
    void* FUN_00b18530();                                      // cGameData helper (model/world lookup)
    void FUN_00c6f770(int a, int b, int c);                    // ret 0xc
    void FUN_00eab830(const ResourceKey_s00ee_de20* k);                   // copies key to +0x108 (ret 4)
    void FUN_00eac530();
    void FUN_00f0d8b0();
};
struct Vehicle : public Noun {
    void Init(int purpose, int locomotion, ResourceKey_s00ee_de20 key);   // 0x00ca6630 (ret 0x14)
};
struct Herd {
    uint32_t pad0[0x88 / 4];
    uint32_t mField88;                                         // +0x88
    uint32_t pad8c[(0xf0 - 0x8c) / 4];
    uint32_t mFieldF0;                                         // +0xf0
    uint32_t padf4[(0x108 - 0xf4) / 4];
    float mField108;                                           // +0x108
    void FUN_00c6ace0(int b);                                  // ret 4
};
struct HerdPos {
    void SetPosition(const Vector3* p);                        // 0x00c6ba20 (ret 4)
};
struct Creature {
    HerdPos* FUN_00c04590();                                   // plain thiscall
};
struct Ufo {
    void FUN_00c3aa40(int a, int b);                           // ret 8
};
struct SpeciesProfile;
struct SpeciesMgr_s00ee_de20 {
    SpeciesProfile* GetProfile(const ResourceKey_s00ee_de20* k);          // 0x004df550 (ret 4)
};
struct NounMgr_s00ee_de20 {
    Noun* CreateInstance(uint32_t nounId);                                                    // 0x00b20c60
    Noun* FUN_00b23650(uint32_t type, uint32_t inst, int z, const Vector3* p, const Quaternion* q);  // ret 0x14
    Herd* CreateHerd(const Vector3* p, SpeciesProfile* prof, int size, bool owned, int pers, int nest);  // ret 0x18
    void* GetAvatar();                                                                        // 0x00b1fdb0
    Noun* FUN_00bbd160();
    void FUN_00b22960();
};
struct IPropList_s00ee_de20 {
    virtual void v0();
    virtual int Release();
};
template<typename T>
struct IntrusivePtr_s00ee_de20 {
    T* mpObject;
    IntrusivePtr_s00ee_de20() : mpObject(0) {}
    ~IntrusivePtr_s00ee_de20() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct PropMgr_s00ee_de20 {
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    virtual void GetPropertyList(uint32_t instance, uint32_t group, IPropList_s00ee_de20** out);  // +0x2c
};
struct GameState { char pad[0xcc]; int mMode; };
NounMgr_s00ee_de20* __cdecl NounManager_s00ee_de20();                                  // 0x00b3d300
SpeciesMgr_s00ee_de20* __cdecl FUN_00401090();                              // species manager
PropMgr_s00ee_de20* __cdecl FUN_0067de30_s00ee_de20();                                 // PropertyManager
Spatial* __cdecl FUN_00b18e00_s00ee_de20(void* noun);                       // Cast(0x1186577) or 0
Noun* __cdecl FUN_00c9f060(void* obj);
Noun* __cdecl FUN_00eec0b0(void* noun);                          // Cast(0x74e0069) or 0
void* __cdecl FUN_00eecba0(ResourceKey_s00ee_de20* k);
int __cdecl FUN_00c9ed00(void* p);
int __cdecl FUN_00c9ed80(void* p);
void __cdecl FUN_00d996b0(int a9, int a7, const Vector3* pos, void* where);
void* __cdecl FUN_00c099e0(const Vector3* p, SpeciesProfile* prof, int n, Herd* herd, int a, int b);
void __cdecl FUN_00d2e580();
Noun* __cdecl FUN_00f213f0(IPropList_s00ee_de20* list, int a7, int a6);
void __cdecl FUN_00eeccb0(void* herdish);
char __cdecl FUN_005b1c80(const Quaternion* q, const void* ref);
void __cdecl FUN_00eed720(int a7, Spatial* sp, void* dst);
float __cdecl FUN_00eec5c0(Noun* n);
struct FlagHolder { char FUN_00f254d0(); };
struct ObjTail {
    char FUN_00f25330();
    void FUN_00f924e0(float f);                                  // ret 4
};
extern GameState* gpGameState;       // 0x016c7aa4
extern Vector3 gVec3Zero;            // 0x016c78cc
float* __cdecl FUN_0059aed0(float* out, const float* a, const float* b);        // 0x0059aed0
void*  __stdcall FUN_00f3d780(void* p);                                          // 0x00f3d780
void   __cdecl FUN_00f3da90(void* obj, int z);                                   // 0x00f3da90
struct ListEntry_s00ee_de20 { void* pObj; float p[3]; float q[4]; };
struct ListRange { ListEntry_s00ee_de20* pBegin; ListEntry_s00ee_de20* pEnd; };
struct AssetRef { void* p0; void* type; void* p2; };
struct ResKey3 { void* a; uint32_t b; void* c; };
struct CSString { char pad[8]; };                       // opaque cString
struct ExtCall {
    void FUN_00423650(const wchar_t* first, const wchar_t* last);  // 0x00423650 basic_string::assign
    void FUN_005c3d90(const wchar_t* s);                           // 0x005c3d90 basic_string::append
    const wchar_t* FUN_00414e10();                                 // 0x00414e10 cAssetMetadata::GetName
    void FUN_006b5060();                                           // 0x006b5060 cString ctor
    void FUN_006b5240();                                           // 0x006b5240 cString dtor
    const wchar_t* FUN_006b55c0();                                 // 0x006b55c0 cString::GetText
};
struct ResMgr {
    SLOT(0) SLOT(1) SLOT(2)
    virtual void Slot3(void* key, void** out, int, int, int, int);  // +0xc
};
bool __cdecl FUN_004bbe20(void* p, int one);                     // 0x004bbe20 SetAssetData
void* __cdecl FUN_0067dcd0();                                    // 0x0067dcd0 GetManager
bool __cdecl FUN_006a1360(void* prop, int id, void* cs);         // 0x006a1360 GetPropertyAsText
// ---- items of slice s00eede20 end

// @ 0x00ee0080
void __stdcall f_ee0080(void* p_, int mode)
{
    VObj* p = (VObj*)p_;
    if (p != 0) {
        p->SetFlag(1, 0);
    }
    if (mode == 0)
        return;
    int type = p->GetTypeId();
    if (type == 0x71725b0) {
        VObj* v = (VObj*)p->FindByHash(0x7172970, 1);
        void* r = (v != 0) ? v->GetPtr15() : 0;
        FUN_00edfce0(*(char**)((char*)g_16c7aa4->f74 + 0x10) + 0x7c, &r);
        ((HintObj*)g_16c7aa4->fD4)->ToggleHint(0x81, 0x82);
        return;
    }
    if (type == 0x7172600) {
        VObj* v = (VObj*)p->FindByHash(0x7172950, 1);
        void* r = (v != 0) ? v->GetPtr15() : 0;
        FUN_00edfce0(*(char**)((char*)g_16c7aa4->f74 + 0x10) + 0xb8, &r);
        VObj* w = (VObj*)p->FindByHash(0x7172960, 1);
        void* s = (w != 0) ? w->GetPtr15() : 0;
        FUN_00edfce0(*(char**)((char*)g_16c7aa4->f74 + 0x10) + 0xf4, &s);
        ((HintObj*)g_16c7aa4->fD4)->ToggleHint(0x83, 0x84);
    }
}

// @ 0x00ee01e0
bool __cdecl f_ee01e0(Container* c, char* p, char value)
{
    bool changed = false;
    if (c->f20 == 0) {
        if (*p != value) {
            g_16c7aa4->f74->Lock();
            *p = value;
            g_16c7aa4->f74->Unlock();
            return true;
        }
        return false;
    }
    char cur = *p;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if ((char)c->begin[i * 0x4e0] != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != value);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        (char)c->begin[i * 0x4e0] = value;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// @ 0x00ee0310
bool __cdecl f_ee0310(Container* c, Elem* e, unsigned idx)
{
    bool changed = false;
    if ((int)idx < 0 || idx >= 5)
        return false;
    idx = (unsigned)kTbl4a8[idx];
    if (c->f20 == 0)
        return FUN_00edfda0(&e->v4a8, (int*)&idx);
    int cur = e->v4a8;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4a8) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != (int)idx);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4a8) = (int)idx;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// @ 0x00ee0450
bool __cdecl f_ee0450(Container* c, Elem* e, unsigned idx)
{
    bool changed = false;
    if ((int)idx < 0 || idx >= 3)
        return false;
    idx = (unsigned)kTbl4b0[idx];
    if (c->f20 == 0)
        return FUN_00edfda0(&e->v4b0, (int*)&idx);
    int cur = e->v4b0;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4b0) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != (int)idx);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4b0) = (int)idx;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// @ 0x00ee0590
bool __cdecl f_ee0590(Container* c, Elem* e, unsigned idx)
{
    bool changed = false;
    if ((int)idx < 0 || idx >= 3)
        return false;
    idx = (unsigned)kTbl4b4[idx];
    if (c->f20 == 0)
        return FUN_00edfda0(&e->v4b4, (int*)&idx);
    int cur = e->v4b4;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4b4) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != (int)idx);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4b4) = (int)idx;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// @ 0x00ee06d0
bool __cdecl f_ee06d0(Container* c, Elem* e, int idx, void* arg4)
{
    if (idx < 0 || idx >= 5)
        return false;
    int newval = kTbl4b8[idx];
    int cur = e->v4b8;
    bool changed;

    if (c->f20 == 0) {
        if (cur == newval)
            return false;
        g_16c7aa4->f74->Lock();
        e->v4b8 = newval;
        if (!((cur == 4 && newval == 6) || (cur == 6 && newval == 4))) {
            IntVec vec = { 0, 0, 0 };
            g_16c7aa4->f74->CollectByNoun(arg4, &vec);
            int n = (int)(vec.end - vec.begin);
            if (n > 0) {
                for (int i = 0; i < n; ++i)
                    FUN_00eef170((void*)vec.begin[i], FUN_00efc520());
            }
            if (vec.begin != 0 && *(int*)(vec.begin - 1) != 0)
                operator_delete(vec.begin);
        }
        g_16c7aa4->f74->Unlock();
        return true;
    }

    changed = false;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4b8) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != newval);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        int* slot = (int*)(c->begin + i * 0x4e0 + 0x4b8);
        if (*slot != newval) {
            int old = *slot;
            *slot = newval;
            if (!((old == 4 && newval == 6) || (old == 6 && newval == 4))) {
                IntVec vec = { 0, 0, 0 };
                g_16c7aa4->f74->CollectByNoun(arg4, &vec);
                int n = (int)(vec.end - vec.begin);
                if (n > 0) {
                    for (int k = 0; k < n; ++k)
                        FUN_00eef170((void*)vec.begin[k], i);
                }
                if (vec.begin != 0 && *(int*)(vec.begin - 1) != 0)
                    operator_delete(vec.begin);
            }
        }
    }
    g_16c7aa4->f74->Unlock();
    return changed;
}

// @ 0x00ee0960
bool __cdecl f_ee0960(int key, int index, int value)
{
    Container* c = (Container*)g_16c7aa4->f74->Find(key);
    char* base = c->begin;
    Elem* e = (Elem*)(base + index * 0x4e0);
    bool changed;

    if (c->f20 == 0) {
        changed = (e->v4a4 != value);
        if (!changed)
            return changed;
        g_16c7aa4->f74->Lock();
        e->v4a4 = value;
        g_16c7aa4->f74->Unlock();
    }
    else {
        int cur = e->v4a4;
        changed = false;
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
            if (*(int*)(c->begin + i * 0x4e0 + 0x4a4) != cur) {
                changed = true;
                goto save;
            }
        }
        changed = (cur != value);
        if (!changed)
            return changed;
    save:
        g_16c7aa4->f74->Lock();
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
            *(int*)(c->begin + i * 0x4e0 + 0x4a4) = value;
        g_16c7aa4->f74->Unlock();
    }

    if (changed) {
        void* p = (void*)(*(void**)((char*)g_16c7aa4->f14 + 0x18));
        ((Obj14*)p)->SetFlag(key);
        g_16c7aa4->f74->Refresh();
    }
    return changed;
}

// @ 0x00ee0af0
bool __cdecl f_ee0af0(Container* c, Elem* e, int value)
{
    bool changed = false;
    if (c->f20 != 0) {
        int cur = e->v4bc;
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
            if (*(int*)(c->begin + i * 0x4e0 + 0x4bc) != cur) {
                changed = true;
                goto save;
            }
        }
        changed = (cur != value);
        if (!changed)
            return changed;
    save:
        g_16c7aa4->f74->Lock();
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
            *(int*)(c->begin + i * 0x4e0 + 0x4bc) = value;
        g_16c7aa4->f74->Unlock();
        return changed;
    }
    if (e->v4bc == value)
        return false;
    g_16c7aa4->f74->Lock();
    e->v4bc = value;
    g_16c7aa4->f74->Unlock();
    return true;
}

// @ 0x00ee0c30
bool __cdecl f_ee0c30(Container* c, Elem* e, int value)
{
    bool changed = false;
    if (c->f20 == 0) {
        if (e->v4c0 == value)
            return false;
        g_16c7aa4->f74->Lock();
        e->v4c0 = value;
        g_16c7aa4->f74->Unlock();
        return true;
    }
    int cur = e->v4c0;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4c0) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != value);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4c0) = value;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// @ 0x00ee0d70
bool __cdecl f_ee0d70(Container* c, Elem_s00ee_0d70* e, int value)
{
    bool changed = false;
    if (c->f20 != 0) {
        int cur = e->v4c4;
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
            if (*(int*)(c->begin + i * 0x4e0 + 0x4c4) != cur) {
                changed = true;
                goto save;
            }
        }
        changed = (cur != value);
        if (!changed)
            return changed;
    save:
        g_16c7aa4_s00ee_0d70->f74->Lock();
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
            *(int*)(c->begin + i * 0x4e0 + 0x4c4) = value;
        g_16c7aa4_s00ee_0d70->f74->Unlock();
        return changed;
    }
    if (e->v4c4 == value)
        return false;
    g_16c7aa4_s00ee_0d70->f74->Lock();
    e->v4c4 = value;
    g_16c7aa4_s00ee_0d70->f74->Unlock();
    return true;
}

// @ 0x00ee0eb0
bool __cdecl f_ee0eb0(Container* c, Elem_s00ee_0d70* e, void* p3, int arg4, unsigned id)
{
    bool r = false;
    if (FUN_00eddf30(e, p3, (void*)arg4, (void*)id)) {
        switch (id) {
        case 0x742bdb0: r = f_ee0d70(c, e, arg4); break;
        case 0x742bdc0: r = f_ee0c30(c, e, arg4); break;
        case 0x742bdd0: r = f_ee0af0(c, e, arg4); break;
        }
    }
    return r;
}

// @ 0x00ee0f50
void __fastcall f_ee0f50(CCLarge* c)
{
    FUN_00edf410(c, 0);
    if (c->f14 != 0) {
        void* w = c->f18;
        FUN_00edf2c0(w, 0, 1);
        SPUIHelpers_RemoveWindowCallback(w, (void*)FUN_00edf410);
        vc0(*(void**)((char*)c->f14 + 0x24), 2);
        vc0(*(void**)c->f14, 2);
        c->f14 = 0;
    }
    if (c->f1c != 0) {
        unsigned u = 0;
        do {
            void* p = *(void**)((char*)c->f1c + u);
            if (p != 0) {
                vc0(p, 5);
                p = *(void**)((char*)c->f1c + u);
                if (p != 0) {
                    *(void**)((char*)c->f1c + u) = 0;
                    vc0(p, 3);
                }
            }
            u += 4;
        } while (u < 0x18);
        int* base = (int*)c->f1c;
        if (base != 0) {
            int n = base[-1];
            int* end = (int*)((char*)base + n * 4);
            while (--n >= 0) {
                int* slot = end - 1;
                --end;
                if (*slot != 0)
                    vc0((void*)*slot, 3);
            }
            operator_delete(base - 1);
        }
    }
    if (c->f10 != 0) {
        cSPUILayout_SetParentWin(c->f10, 0, 1, 0x5b598fa);
        cSPUILayout_Shutdown(c->f10, 1);
        void* p = c->f10;
        if (p != 0) {
            c->f10 = 0;
            vc0(p, 2);
        }
    }
    if (c->f70 != 0) {
        int a = c->f70;
        c->f70 = 0;
        EA_Messaging_RemoveHandler(a, c->f74, c->f78, c->f7c, c->f80);
    }
}

// @ 0x00ee1060
void __stdcall f_ee1060(int* p)
{
    if (*p != 0)
        FUN_00edfbf0(p);
}

// @ 0x00ee1140
void __cdecl f_ee1140(int key, char value)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4_s00ee_0d70->f74->FUN_00f40d00(key, &v);
    for (IObj** it = (IObj**)v.begin; it != (IObj**)v.end; ++it) {
        IObj* o = *it;
        if (o != 0) {
            void* r = o->Query(0x1186577);
            if (r != 0)
                *(char*)((char*)r + 0x78) = (value == 0);
        }
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}

// @ 0x00ee1200
void __cdecl f_ee1200(int key, int arg2)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4_s00ee_0d70->f74->FUN_00f40d00(key, &v);
    for (IObj** it = (IObj**)v.begin; it != (IObj**)v.end; ++it) {
        if (*it != 0) {
            IObj* r = (IObj*)(*it)->Query(0x13f94d4);
            if (r != 0)
                r->FUN_00bfc470(arg2);
        }
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}

// @ 0x00ee12c0
void __fastcall f_ee12c0(CCLarge2* c)
{
    char* s = (char*)c;
    void* mgr = s + 0x4c;
    unsigned n = 0;
    if (FUN_00e09c80(mgr, 0) != 0) {
        do {
            void* layout = FUN_00e09c90(mgr, 0, (int)n);
            void* w = Layout_FindWindowByID(layout, 0x715cde0, 1);
            if (w != 0) {
                void* sub = vcq2(w, 60, 0x7df4c98, 1);
                if (sub != 0)
                    vcp(sub, 66, c->fc0);
            }
            ++n;
        } while (n < (unsigned)FUN_00e09c80(mgr, 0));
    }
    void* idbase = (c != 0) ? (void*)(s + 8) : 0;
    void* w = Layout_FindWindowByID(c->f40, 0x71725b0, 1);
    if (w != 0) vcp(w, 66, idbase);
    idbase = s + 8;
    w = Layout_FindWindowByID(c->f44, 0x7172600, 1);
    if (w != 0) vcp(w, 66, idbase);
    if (c->f20 != 0) vcp(c->f20, 66, idbase);
    if (c->f24 != 0) vcp(c->f24, 66, idbase);
    FUN_00e0a5c0(mgr, 0);
    if (c->f28 != 0) vcp(c->f28, 66, idbase);
    w = Layout_FindWindowByID(c->f40, 0x71725b0, 1);
    if (w != 0) SPUIHelpers_EndModal(w, 0, 1);
    w = Layout_FindWindowByID(c->f44, 0x7172600, 1);
    if (w != 0) SPUIHelpers_EndModal(w, 0, 1);
    c->fc5 = 0;
    c->fc6 = 0;
    FUN_00edd810(c, 0);
    if (c->f40 != 0) {
        cSPUILayout_Shutdown(c->f40, 1);
        void* p = c->f40;
        if (p != 0) { c->f40 = 0; vc0(p, 2); }
    }
    if (c->f44 != 0) {
        cSPUILayout_Shutdown(c->f44, 1);
        void* p = c->f44;
        if (p != 0) { c->f44 = 0; vc0(p, 2); }
    }
    if (c->f18 != 0) {
        f_ee0f50((CCLarge*)c->f18);
        if (c->f18 != 0) {
            void* p = c->f18;
            c->f18 = 0;
            vc0(p, 2);
        }
    }
    if (c->f48 != 0) {
        FUN_00edbcb0(c->f48, 0);
        void* p = c->f48;
        if (p != 0) { c->f48 = 0; vc0(p, 2); }
    }
    if (c->fbc != 0) {
        vc0(c->fbc, 9);
        void* p = c->fbc;
        if (p != 0) { c->fbc = 0; vc0(p, 1); }
    }
    if (c->fc0 != 0) { void* p = c->fc0; c->fc0 = 0; vc0(p, 1); }
    if (c->f1c != 0) { void* p = c->f1c; c->f1c = 0; vc0(p, 1); }
    if (c->f20 != 0) { void* p = c->f20; c->f20 = 0; vc0(p, 1); }
    if (c->f24 != 0) { void* p = c->f24; c->f24 = 0; vc0(p, 1); }
    if (c->f28 != 0) { void* p = c->f28; c->f28 = 0; vc0(p, 1); }
}

// @ 0x00ee1510
void __cdecl f_ee1510(int key, float param_2)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4_s00ee_0d70->f74->FUN_00f40d00(key, &v);
    static const float kMin = 1.5258789e-05f;
    if (param_2 < kMin)
        param_2 = kMin;
    for (IObj** it = (IObj**)v.begin; it != (IObj**)v.end; ++it) {
        IObj* obj = (*it == 0) ? 0 : (IObj*)(*it)->Query(0x1186577);
        if (!obj->FUN_00c88940(0xb78987ff)) {
            obj->FUN_00c8b1a0(0xb78987ff);
            obj->FUN_00c88a00(0xb78987ff);
        }
        float f = obj->GetFloat();
        obj->FUN_00c8a020(0xb78987ff, f + param_2);
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}

// @ 0x00ee1630
void __cdecl f_ee1630(int key)
{
    IntVec v;
    v.begin = 0; v.end = 0; v.cap = 0;
    g_16c7aa4_s00ee_0d70->f74->FUN_00f40d00(key, &v);
    IObj** end = (IObj**)v.end;
    for (IObj** it = (IObj**)v.begin; it != end; ++it) {
        IObj* obj = *it;
        IObj* r = (obj != 0) ? (IObj*)obj->Query(0x1186577) : 0;
        r->FUN_00c8ad30(0xb78987ff, 0);
    }
    for (IObj** q = (IObj**)v.begin; q < (IObj**)v.end; ++q) {
        if (*q != 0)
            (*q)->Release();
    }
    if (v.begin != 0 && v.begin[-1] != 0)
        operator_delete(v.begin);
}

// @ 0x00ee16f0
void TutorialPanel::Refresh()
{
    int mode = ScenarioTutorials_GetActive();
    int count = 1;
    TutorialManager* mgr = g_16c7aa4_s00ee_16f0->mpTutorials;
    if (mgr)
        count = mgr->GetCount();
    Tutorial* tut = GetTutorials()->Find(mID);

    if (mpLayout->IsVisible() && tut) {
        UpdateHeader();
        Tutorial_Prepare(tut);
        bool complete = Tutorial_IsComplete(tut);
        TutorialStep* step = &tut->mpSteps[mode];
        UpdateLayout();

        string16 name;
        tut->GetName(name);
        const wchar_t* pName = name.c_str();

        if (IWindow* w = FindWindow(0x7957ba8)) {
            if (ITextField* text = (ITextField*)w->Cast(ITextField::TYPE)) {
                text->SetMaxLength(0x20);
                text->SetText(pName, 0);
            }
        }

        if (IWindow* w = FindWindow(0x76a93c54)) {
            w->SetFlag(1, count > 1);
            IWindow* pageLabel = FindWindow(0x76a93c53);
            IWindow* nextButton = FindWindow(0x76a93c51);
            IWindow* prevButton = FindWindow(0x76a93c50);
            IWindow* titleText = FindWindow(0x76a93c52);
            if (pageLabel && nextButton && prevButton && titleText) {
                SetPageLabel(pageLabel, tut->mPage);
                SetButtonEnabled(prevButton, mode > 0);
                SetButtonEnabled(nextButton, mode < count - 1);
                SP::cString_s00ee_16f0 title(0xefdb68ec, 0x96a94d76, 0);
                SetWindowText(titleText, title.GetText());
            }
        }

        if (IWindow* w = FindWindow(0x7a41548)) {
            bool flag = tut->IsFlag600();
            w->SetFlag(1, flag);
        }

        for (uint32_t i = 0; i < 6; i++) {
            CategoryWin* win;
            if (mpWindow->GetControlID() == kCategoryWindowIDs[i] && (win = mpCategoryWins[i]) != 0) {
                bool hasIcon = step->mIcon != -1;
                win->SetEnabled(hasIcon);
                mpCategoryWins[i]->SetValue(hasIcon ? step->mIcon : 0);
                mpWindow->FindWindowByID(0x7ec6a40, true)->SetFlag(1, hasIcon);
                object_cast<IButton>(mpWindow->FindWindowByID(0x7ec82c0, true))->SetButtonStateFlag(4, hasIcon);
            }
        }

        SetButtonFlag(FindWindow(0x742bde0), 4, step->mbDone);

        if (mpProgress) {
            uint32_t id = mID;
            if (id != mpProgress->GetID())
                mpProgress->SetID(id);
            mpProgress->Refresh(0);
            mpProgress->Update();
        }

        uint32_t goalCount = GetTutorials()->GetGoalCount(mID);
        wchar_t countText[32];
        SetNumberString(min_ref(goalCount, CountLimits::kMaxCount), countText, 0x20);
        if (IWindow* w = FindWindow(0x792e8a0))
            w->SetCaption(countText);

        if (tut->HasValue470()) {
            IWindow* group = FindWindow(0x742bd88);
            IWindow* lockedRow = group->FindWindowByID(0x742be59, false);
            IWindow* openRow = group->FindWindowByID(0x742be58, false);
            if (step->mbLocked || step->GoalCount() > 0) {
                uint32_t id = IndexOf(step->mType4ac, kTable738) + 0x742cbe0;
                if (step->mbLocked)
                    id = 0x742cbe5;
                if (IWindow* w = lockedRow->FindWindowByID(id, true)) {
                    if (IButton* button = (IButton*)w->Cast(IButton::TYPE))
                        button->SetButtonStateFlag(4, true);
                }
                lockedRow->SetFlag(1, true);
                openRow->SetFlag(1, false);
            } else {
                IWindow* row = group->FindWindowByID(0x742be58, false);
                int index = IndexOfCounted(step->mType4ac, kTable738, kTable738Count);
                if (IWindow* w = row->FindWindowByID(index + 0x742cbe0, true)) {
                    if (IButton* button = (IButton*)w->Cast(IButton::TYPE))
                        button->SetButtonStateFlag(4, true);
                }
                lockedRow->SetFlag(1, false);
                row->SetFlag(1, true);
            }
        }

        if (tut->HasValue470()) {
            ShowValue(mID, step->mValue484);
            SetSlider(FindWindow(0x792bf78), step->mValue484, 0.0f, 175.0f);
        }

        wchar_t text[32];
        if (tut->HasValue330()) {
            float target = GetStepTarget(tut->mKey, step->mValue48c);
            SetNumberString((int64_t)target, text, 0x20);
            SetValueField(FindWindow(0x7918320), step->mValue48c, step->mbFlag2, step->mbFlag1,
                          0xf69d44ec, text);
        }

        IWindow* modeA = FindWindow(0x76c61c8);
        IWindow* modeB = FindWindow(0x2791ba0);
        if (modeA && modeB) {
            if (tut->GetStateA()) {
                modeA->SetFlag(1, true);
                IWindow* shown;
                IWindow* hidden;
                if (tut->GetStateA() == 3) {
                    shown = modeA->FindWindowByID(0x2791ca0, true);
                    hidden = modeA->FindWindowByID(0x2791ca1, true);
                } else {
                    hidden = modeA->FindWindowByID(0x2791ca0, true);
                    shown = modeA->FindWindowByID(0x2791ca1, true);
                }
                shown->SetFlag(1, true);
                hidden->SetFlag(1, false);
                IWindow* modeIcon = shown->FindWindowByID(0x6849100, true);
                SetModeIcon(modeIcon, tut->mMode24);
                IWindow* icon = shown->FindWindowByID(0x3791003, true);
                if (tut->mMode24 == 2) {
                    IWindow* image = icon->FindWindowByID(0x3791001, true);
                    icon->SetFlag(1, true);
                    ResourceKey key = tut->GetImageA();
                    SetWindowImage(image, key, -1);
                } else if (tut->GetStateA() == 3) {
                    icon->SetFlag(1, false);
                }
            } else {
                modeA->SetFlag(1, false);
            }

            if (tut->GetStateB()) {
                modeB->SetFlag(1, true);
                IWindow* shown;
                IWindow* hidden;
                if (tut->GetStateB() == 3) {
                    shown = modeB->FindWindowByID(0x2791ba1, true);
                    hidden = modeB->FindWindowByID(0x2791ba2, true);
                } else {
                    hidden = modeB->FindWindowByID(0x2791ba1, true);
                    shown = modeB->FindWindowByID(0x2791ba2, true);
                }
                hidden->SetFlag(1, false);
                shown->SetFlag(1, true);
                IWindow* modeIcon = shown->FindWindowByID(0x6849100, true);
                SetModeIcon(modeIcon, tut->mMode48);
                IWindow* icon = shown->FindWindowByID(0x3791003, true);
                if (tut->mMode48 == 2) {
                    IWindow* image = icon->FindWindowByID(0x3791001, true);
                    icon->SetFlag(1, true);
                    ResourceKey key = tut->GetImageB();
                    SetWindowImage(image, key, -1);
                } else if (tut->GetStateB() == 3) {
                    icon->SetFlag(1, false);
                }
                bool dimmed;
                ResourceKey key = tut->GetImageC(&dimmed);
                IWindow* image = modeB->FindWindowByID(0x3791002, true);
                SetWindowImage(image, key, -1);
                if (dimmed)
                    image->SetShadeColor(0x77ffffff);
                else
                    image->SetShadeColor(0xffffffff);
            } else {
                modeB->SetFlag(1, false);
            }
        }

        if (tut->HasValue420() && FindWindow(0x9918320))
            SetSlider(FindWindow(0x9918320), step->mValue4a0, 1.0f, 50.0f);
        else if (FindWindow(0x9918320))
            FindWindow(0x9918320)->SetFlag(1, false);

        if (tut->HasValue560() && FindWindow(0x742bed0))
            FindWindow(0x742bed0)->SetFlag(1, true);
        else if (!tut->HasValue560() && FindWindow(0x742bed0))
            FindWindow(0x742bed0)->SetFlag(1, false);

        if (tut->HasValue430() && FindWindow(0x8918320))
            SetSlider(FindWindow(0x8918320), step->mValue49c, 0.0f, 2000.0f);
        else if (!tut->HasValue330() && FindWindow(0x8918320))
            FindWindow(0x8918320)->SetFlag(1, false);

        if (tut->HasValue430() && FindWindow(0x892bf78)) {
            ShowValue(mID, step->mValue498);
            SetSlider(FindWindow(0x892bf78), step->mValue498, 0.0f, 50.0f);
        } else if (!tut->HasValue470() && FindWindow(0x892bf78)) {
            FindWindow(0x892bf78)->SetFlag(1, false);
        }

        if (tut->HasValue470()) {
            SetNumberStringF((int)(step->mValue494 * 100.0f), text, 0x20, 0);
            SetValueField(FindWindow(0x7c8a7d0), step->mValue494, false, false, 0x7cc8a44, text);
        }

        if (tut->HasValue470()) {
            uint32_t fmt = 0;
            switch (tut->mKey.typeID) {
            case 0x24682294:
            case 0x476a98c7:
                fmt = 0x7cc8a4b;
                SetNumberStringF((int)(step->mValue490 * 100.0f), text, 0x20, 0);
                break;
            case 0x2b978c46:
                fmt = 0x7cc8a48;
                SetNumberString((int64_t)step->mValue490, text, 0x20);
                break;
            }
            SetValueField(FindWindow(0x7c8a7a8), step->mValue490, false, false, fmt, text);
        }

        if (tut->HasValue330()) {
            IWindow* w = FindWindow(0x742bd98);
            int index = IndexOf(step->mType4a8, kTable720);
            void* drawable;
            if (w) {
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                drawable = GetButtonDrawable(button, 0);
            } else {
                drawable = 0;
            }
            SetImageIcon(w, drawable, 0);
            int iconIndex = GetIconIndex(w, index);
            SetImageIconFrom(w, &iconIndex, 1);
        }

        if (tut->HasValue670()) {
            IWindow* w = FindWindow(0x742bdb0);
            if (complete) {
                w->SetFlag(1, false);
            } else {
                w->SetFlag(1, true);
                int index = IndexOf(step->mType4b0, kTable754);
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                void* drawable = GetButtonDrawable(button, 0);
                SetImageIcon(w, drawable, 0);
                SetChoiceRow(w, step->mType4b0 == 3, step->mValue4bc);
            }
        }

        if (tut->HasValue670()) {
            IWindow* w = FindWindow(0x742bdc0);
            if (complete) {
                w->SetFlag(1, false);
            } else {
                w->SetFlag(1, true);
                int index = IndexOf(step->mType4b4, kTable764);
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                void* drawable = GetButtonDrawable(button, 0);
                SetImageIcon(w, drawable, 0);
                SetChoiceRow(w, step->mType4b4 == 3, step->mValue4c0);
            }
        }

        if (tut->HasValue470()) {
            IWindow* w = FindWindow(0x742bdd0);
            if (complete) {
                w->SetFlag(1, false);
            } else {
                w->SetFlag(1, true);
                int index = IndexOf(step->mType4b8, kTable774);
                IWindow* button = w->FindWindowByID(index + 0x742cbe0, true);
                void* drawable = GetButtonDrawable(button, 0);
                SetImageIcon(w, drawable, 0);
                SetChoiceRow(w, step->mType4b8 == 5, step->mValue4c4);
            }
        }
    }

    SyncTutorialState(mode, mID);
    mState.Set(1);
}

// @ 0x00ee2860
void __cdecl f00ee2860(int p1, cString_s00ee_2860* p2, cString_s00ee_2860* p3)
{
    TipObj* tip = G7C();
    if (tip == 0)
        return;

    cString_s00ee_2860 s;
    s.Load(0x21851ebe, 0x7d91076, 0);

    u32 k = *(u32*)((char*)p1 + 0x184);
    if ((int)k > -1 && k < 0x1a)
    {
        if (k == 0x15)
            s.Load(0xf3108302, 0x7ec7659, 0);
        else
            s.Load(0x21851ebe, kTooltipIds[k], 0);
    }

    const wchar_t* a = s.GetText();
    tip->mText.assign(a, a + CharStrlen(a));

    u32 id;
    if (p2 != 0)
    {
        const wchar_t* c = p2->GetText();
        tip->mHint.assign(c, c + CharStrlen(c));
        id = 0x7d91137;
    }
    else
        id = 0x7d91139;

    p3->Load(0x21851ebe, id, 0);
}

// @ 0x00ee3020
void Beh::F3020()
{
    Mgrs* m = MGR();
    char* t = (char*)this;
    if (m == 0)
        return;

    int o = m->F3be60(FUN_00efc520());
    int count = (*(int*)(o + 0x88) - *(int*)(o + 0x84)) / 0x188;

    int i = 0, off = 0;
    do
    {
        int p = (i < count) ? (*(int*)(o + 0x84) + off) : 0;
        f00ee2960(
            (IWindow_s00ee_2860*)((Lay*)((Lay*)(t + 0x4c))->At(i))->FindWindowByID(i + 0x715cde0, 1),
            (PaletteItem*)p, i == count, *(bool*)(t + 0xc6));
        off += 0x188;
        ++i;
    } while (off < 0x498);
}

// @ 0x00ee30d0
void Beh::F30D0()
{
    char* t = (char*)this;
    if (!((Lay*)*(void**)(t + 0x10))->IsVisible())
        return;
    FUN_00f0bea0();
    FUN_00ecb730();
    FUN_00ee1630(*(int*)(t + 0x20));
    FEDF240();
    FEDF410();
    *(int*)(t + 0x28) = 0;
    ((Lay*)*(void**)(t + 0x10))->SetVisibility(0);
    void* w = *(void**)(t + 0x18);
    if (w != 0)
        VC2(w, 0x7c, 1, 0);
    FEE16F0();
    FEDF4C0();
}

// @ 0x00ee3140
void Beh::F3140(int param)
{
    char* t = (char*)this;
    if (*(int*)(t + 0x20) == param)
        return;
    if (((Lay*)*(void**)(t + 0x10))->IsVisible()) {
        if (param == -1) {
            ((Sub48*)(t + 0x48))->F9990(0);
            FUN_00ed8a30(FUN_00efc520(), *(int*)(t + 0x20));
            return;
        }
        if (param == -2) {
            F30D0();
            return;
        }
        FUN_00ee1630(*(int*)(t + 0x20));
        *(int*)(t + 0x20) = param;
        *(int*)(t + 0x28) = 0;
        FEDF4C0();
        FEE16F0();
        FEDF510();
        return;
    }
    *(int*)(t + 0x20) = param;
    FEE16F0();
}

// @ 0x00ee31d0
void Beh::F31D0()
{
    char* t = (char*)this;
    Mgrs* m = MGR();
    if (m == 0)
        return;
    int u = FUN_00efc520();
    FEDD810();
    ((Win16*)*(void**)(t + 0x18))->F16F0();
    ((Sub48*)*(void**)(t + 0x48))->FC0E0(u);
    F3020();
    int o = m->F3be60(u);
    if (o != 0) {
        *(int*)(t + 0x2c) = *(int*)(o + 0x80);
        FEDDA20();
    }
}

// @ 0x00ee3230
void __cdecl f00ee3230(int key, void* self)
{
    char* t = (char*)self;
    MGR()->F45970();
    int active = FUN_00efc520();

    int idx = -1;
    for (int i = 0; i < 0xc; ++i)
    {
        if (key == (int)kTutorialTypeTable[i])
        {
            idx = i;
            break;
        }
    }

    int pid = *(int*)(t + 0xc8);
    int other = -1;
    int found = MGR()->F3e8a0(pid);
    int keep = pid;
    if (idx == 9 && found != 0 && !((Tut*)found)->F254D0())
    {
        keep = -1;
        other = pid;
    }

    int res = MGR()->F43a10(active, idx, keep, other);
    MGR()->F45a80();

    int vol = 0;
    void* au = FUN_00a206f0();
    if (au != 0)
        vol = VC0(au, 0x20);
    void* au2 = FUN_00a206f0();
    if (au2 != 0)
    {
        VC1(au2, 0x38, 0x3475365);
        VC2(au2, 0x40, 0x3475381, 0xcfe8f73d);
        VC2(au2, 0x40, 0x3475385, vol);
        VC0(au2, 0x58);
    }

    int* r = MGR()->F3bf00(active, res);
    if (*r == 2)
        GD4()->ToggleHint(0x6a, 0x6b);
    if (*r == 6)
    {
        if (MGR()->F3e8a0(r[1]) != 0)
            GD4()->ToggleHint(0x7b, 0x7c);
    }

    ((Pie*)*(void**)(t + 0xbc))->Hide();
    t[0xc6] = 0;
    *(int*)(t + 0xc8) = -1;
    ((Beh*)self)->F31D0();
    MGR()->F427c0();

    if (*r == 2)
    {
        FUN_00ecb730();
        FUN_00f0bc80(r);
    }

    void* av = ((NounMgr*)SP_NounManager())->GetAvatar();
    if (av != 0)
    {
        void* q = (char*)av + 0x5a8;
        void* sel = (void*)((int (__thiscall*)(void*))VTP(q)[3])(q);
        ((void (__thiscall*)(void*, int))FUN_00efe930)((void*)0x15ad328, (int)sel);
    }
}

// @ 0x00ee3400
void __cdecl f00ee3400(void* self)
{
    char* t = (char*)self;
    ((Pie*)*(void**)(t + 0xbc))->Hide();
    *(char*)(t + 0xc6) = 0;
    *(int*)(t + 0xc8) = -1;
    ((Beh*)self)->F31D0();
}

// @ 0x00ee3430
void __cdecl f00ee3430(int key, void* self, char flag)
{
    char* t = (char*)self;
    if (((ChecklistUI*)GD4())->HasIndex())
        return;

    if (!flag)
    {
        GD4()->F67C8C0(0xf81dec23, 0);
        return;
    }

    int pid = *(int*)(t + 0xc8);

    TextBuf s;
    ((void (__thiscall*)(void*))FUN_00f2bd10)(&s);

    int idx = -1;
    for (int i = 0; i < 0xc; ++i)
    {
        if (key == (int)kTutorialTypeTable[i])
        {
            idx = i;
            break;
        }
    }

    FUN_00edd310(&s, idx, pid);
    char ok = FUN_00edd370(&s, *(int*)(t + 0xcc), *(int*)(t + 0xd0));

    GD4()->F67C8C0(0xf81dec23, 0);

    if (!ok)
    {
        cString_s00ee_2860 s2;
        f00ee2860((int)&s, 0, &s2);
        GD4()->F67C830(0xf81dec23);
        s2.~cString_s00ee_2860();
    }

    ((void (__thiscall*)(void*))FUN_00dfbb60)(&s);
}

// @ 0x00ee3540
void Beh::F3540(void* item, void* list)
{
    char* t = (char*)this;
    if (list == 0)
        return;

    int n = (int)_wtol(WGETTEXT(item));
    if (wcscmp(WGETTEXT(item), kEmptyStr) == 0 || n == 0)
        n = 1;

    void* pv = FUN_00edca20(item);
    int slot;
    if (pv != 0)
        slot = ((int (__thiscall*)(void*))VTP(pv)[0x1c / 4])(pv) - 0x715cde0;
    else
        slot = 0;

    int* cell = (int*)(slot * 0x188 + 0xc + *(int*)((char*)list + 0x84));
    if (*cell != n)
    {
        MGR()->F45970();
        *cell = n;
        MGR()->F45a80();
    }

    F31D0();
    MGR()->F427c0();
}

// @ 0x00ee3630
void Beh::F3630(int arg)
{
    char* t = (char*)this;
    int* o = (int*)FUN_00efc910();
    if (o != 0)
    {
        F3140(*o);
    }
    else if (*(int*)(t + 0x20) != -1)
    {
        if (((Lay*)*(void**)(t + 0x10))->IsVisible())
        {
            ((Sub48*)(t + 0x48))->F9990(0);
            FUN_00ed8a30(FUN_00efc520(), *(int*)(t + 0x20));
        }
        else
        {
            *(int*)(t + 0x20) = -1;
            FEE16F0();
        }
    }

    if (FUN_00efe5c0() != 0)
    {
        FUN_00ed8a30(FUN_00efc520(), *(int*)(t + 0x20));
        ((Sub48*)(t + 0x48))->F9990(1);
    }

    if (*(int*)(t + 0x14) != 0)
    {
        if (*(int*)(t + 0x20) != ((int (__thiscall*)(void*))FUN_007f54d0)(*(void**)(t + 0x14)))
            ((void (__thiscall*)(void*, int))VTP(*(void**)(t + 0x14))[0x1c / 4])(*(void**)(t + 0x14), *(int*)(t + 0x20));
        void* inner = *(void**)((char*)*(void**)(t + 0x14) + 0x24);
        ((void (__thiscall*)(void*, int))VTP(inner)[0x18 / 4])(inner, arg);
        ((void (__thiscall*)(void*))FUN_00ece300)(*(void**)(t + 0x14));
    }

    for (u32 i = 0; i < 6; ++i)
    {
        void* p = ((void**)*(void***)(t + 0x1c))[i];
        if (p != 0)
            ((void (__thiscall*)(void*, int))VTP(p)[0x18 / 4])(p, arg);
    }
}

// @ 0x00ee3710
void Beh::F3710(int param)
{
    char* t = (char*)this;
    if (!((Lay*)*(void**)(t + 0x10))->IsVisible()) {
        *(int*)(t + 0x20) = param;
        ((Lay*)*(void**)(t + 0x10))->SetVisibility(1);
        FEE16F0();
        FEDF510();
        return;
    }
    F3140(param);
}

// @ 0x00ee3760
void Beh::F3760(int* arg)
{
    char* t = (char*)this;
    void* edi = (this != 0) ? (void*)(t + 4) : 0;
    void* ms = SP_MessageServer();
    VC3(ms, 0x2c, (int)edi, 0x30c11c7, 0xffffd8f1);
    if (*arg == 0) {
        void* g = *(void**)((char*)DAT_016c7aa4 + 0x14);
        ((Ed14*)g)->F6c0200();
        if ((void*)g == 0)
            return;
        ((Beh*)g)->F31D0();
        return;
    }
    FEDFBF0(arg);
    void* c = *(void**)(t + 0xc);
    VC1(c, 0x1c, *(int*)(t + 8));
    int ebx = *(int*)(t + 0x10);
    if (ebx == 0)
        return;
    int esi2 = *(int*)(t + 0xc);
    FEDF2C0(ebx, 0);
    SPUIHelpers_CreateCallbackWinProc((void*)ebx, (void*)&f00edf370, 2, 0, (void*)esi2);
}

// @ 0x00ee3800
bool __cdecl f00ee3800(int a1, int a2, int a3, int a4)
{
    bool ok = false;

    int* state = (int*)FUN_00efc8f0();
    if (state != 0) {
        uint32_t flags = (uint32_t)state[0x224 / 4];
        if ((flags & 0x10) != 0 || (flags & 0x2) != 0 || (flags & 0x4) != 0)
            return false;
    }

    Mgrs_s00ee_3800* mgr = MGR_s00ee_3800();

    if (a3 != 0) {
        SelCtx ctx;
        FUN_00edd310(&ctx, a3, a1);
        if (mgr->F3c750(&ctx, -1))
            return false;
        if (mgr->F420d0(FUN_00efc520(), &ctx, a4, 0, 0))
            return false;
    }

    SelObj* obj = (SelObj*)mgr->F3e8a0(a1);
    if (a2 != 0x867a9ee9) {
        if (obj == 0)
            goto done;
        if (FUN_00eece20((int)obj) != a2)
            goto done;
    }
    if (obj != 0 && !obj->F25490())
        return false;
    ok = true;
    if (obj == 0)
        goto done;
    uint8_t* entry = (uint8_t*)(*(int*)((char*)obj + 0x70) + FUN_00efc520() * 0x4e0);
    if (entry[0] == 0)
        return false;
    if (entry[2] == 0)
        goto done;
    if (obj->F25670())
        goto done;
    return false;

done:
    return ok;
}

// @ 0x00ee3940
bool Bee::F3940()
{
    void* active = VCP0(FUN_0067caa0(), 0x04);
    void* target = (char*)this + 8;

    {
        void* raw = FUN_00f473a0(0x18, "UI/cSPUILayout", 0, 0, 0, 0);
        LayoutObj* p = raw ? ((LayoutObj*)raw)->Ctor() : 0;
        SpSet<1, 2>(&mp40, p);
        if (p)
            p->Setup(0x15ac658, 0, 0x5b598fa);
        LayoutObj* w = p ? p->Child(0x71725b0, 1) : 0;
        if (w)
            VC1(w, 0x104, target);
    }
    {
        void* raw = FUN_00f473a0(0x18, "UI/cSPUILayout", 0, 0, 0, 0);
        LayoutObj* p = raw ? ((LayoutObj*)raw)->Ctor() : 0;
        SpSet<1, 2>(&mp44, p);
        if (p)
            p->Setup(0x15ac664, 0, 0x5b598fa);
        LayoutObj* w = p ? p->Child(0x7172600, 1) : 0;
        if (w)
            VC1(w, 0x104, target);
    }

    SpSet<0, 1>((void**)&mp1c, (void*)((Global164*)FUN_0080fee0())->Get(0x2edd95ca));

    {
        void* raw = FUN_00f473a0(0x84, "Simulator/cScenarioEditModeBehaviorUI", 0, 0, 0, 0);
        Obj84* p = raw ? ((Obj84*)raw)->Ctor() : 0;
        SpSetC(&mp18, p);
        if (p)
            p->Bind(mp1c);
    }

    SpSet<0, 1>(&mp20, VCP2(active, 0xf0, 0x7466e50, 1));

    {
        void* raw = FUN_00f473a0(0x50, "Simulator/cScenarioEditModeScriptActsBarUI", 0, 0, 0, 0);
        Obj50* p = raw ? ((Obj50*)raw)->Ctor() : 0;
        SpSet<1, 2>((void**)&mp48, (void*)p);
        if (p)
            p->Bind(mp20);
    }
    if (mp20)
        VC1(mp20, 0x104, target);

    RebuildLists();

    SpSet<0, 1>(&mp24, VCP2(active, 0xf0, 0x757acb8, 1));

    {
        struct { int a, b, c; } tmp;
        tmp.a = 0; tmp.b = 0; tmp.c = 0;
        mVec.Init(mp24, &tmp);
        mVec.AddColumn(0x15ac688, 3);
    }
    if (mp24)
        VC1(mp24, 0x104, target);

    {
        void* raw = FUN_00f473a0(0xc, "Editor", 0, 0, 0, 0);
        ObjC0* p = raw ? (ObjC0*)raw : 0;
        if (p) {
            p->mpVtbl0 = (void*)0x13ec458;
            p->m8 = 0;
            p->mpVtbl0 = (void*)0x148a81c;
            p->mpVtbl1 = (void*)0x149bad8;
        }
        SpSet<0, 1>(&mpC0, p);
    }

    for (unsigned i = 0; i < (unsigned)mVec.Count(); ++i) {
        LayoutObj* w = ((LayoutObj*)mVec.At((int)i))->Child(0x715cde0, 1);
        if (!w)
            continue;
        VC1(w, 0x50, 0x715cde0 + i);
        for (unsigned j = 0; j < 5; ++j) {
            void* x = VCP2(w, 0xf0, DAT_0148a960[j], 1);
            VC1(x, 0x104, target);
            if (j < 3)
                VC1(x, 0x78, 0x747d67b);
        }
        void* y = VCP2(w, 0xf0, 0x7df4c98, 1);
        if (y)
            VC1(y, 0x104, mpC0);
    }

    SpSet<0, 1>(&mp28, VCP2(active, 0xf0, 0x7625680, 1));

    {
        void* raw = FUN_00f473a0(0xc8, "UI/cSPUIPieMenu", 0, 0, 0, 0);
        ObjC8* p = raw ? ((ObjC8*)raw)->Ctor() : 0;
        SpSet<0, 1>(&mpBC, p);
        if (p) {
            VC5(p, 0x20, 0x15ac694, 0x15ac6a0, 1, mp28, 1);
            p->SetHandlers((int)&FUN_00ee3230, this);
        }
    }
    if (mp28)
        VC1(mp28, 0x104, target);

    return true;
}

// @ 0x00ee3e40
void Bee::F3E40(char param)
{
    char* t = (char*)this;
    int ebx = (int)param;
    if (param == 0) {
        FUN_00edd810();
        int h = *(int*)(t + 0xf0);
        if (h != 0) {
            *(int*)(t + 0xf0) = 0;
            EA_Messaging_RemoveHandler(h, *(int*)(t + 0xf4), *(int*)(t + 0xf8), *(int*)(t + 0xfc), *(int*)(t + 0x100));
        }
        ((L18*)*(void**)(t + 0x18))->F30D0();
    } else {
        int b2 = (this != 0) ? (int)(t + 0x10) : 0;
        void* ms = SP_MessageServer();
        *(void**)(t + 0xf0) = ms;
        *(int*)(t + 0xf4) = b2;
        *(void**)(t + 0xf8) = (void*)DAT_0148a9c8;
        *(int*)(t + 0xfc) = 10;
        *(int*)(t + 0x100) = 0;
        if (ms != 0 && b2 != 0) {
            for (unsigned u = 0; u < 0x28; u += 4)
                VC2(ms, 0x24, b2, *(int*)((char*)DAT_0148a9c8 + u));
        }
        F31D0();
    }
    ((L18*)*(void**)(t + 0x18))->FCD30(ebx);
    ((L48*)*(void**)(t + 0x48))->FBD30(ebx);
    *(char*)(t + 0xc4) = param;
}

// @ 0x00ee3f20
void Bee::F3F20(int param)
{
    char* t = (char*)this;
    ((L18*)*(void**)(t + 0x18))->F3630(param);
    ((L48*)*(void**)(t + 0x48))->FBDD0(param);
    void* p24 = *(void**)(t + 0x24);
    if (p24 != 0)
        ((int(__thiscall*)(void*,int,bool))VTP(p24)[0x7c/4])(p24, 2, *(char*)(t + 0xc5) == 0);
}

// @ 0x00ee3f60
bool Hee::F3F60(int msg, void* param)
{
    switch (msg) {
    case 0x44ef2b8:
    case 0x7d11fe0:
    case (int)0xc9d86390:
    case (int)0xc9d86391:
        ((L18*)mp18)->F30D0();
        break;

    case 0x7465518:
        if (param) {
            int v = *(int*)param;
            ((L18*)mp18)->F3710(v);
            CTL()->Notify(0x46, 0x47);
            CTL()->Notify(0x5c, 0x5d);
        }
        break;

    case 0x65ff54a:
        {
            int* d = (int*)param;
            u32 k = (u32)d[6];
            if (d[4] == 0x40464100 &&
                (k == 0xd492676d || k == 0x8ddc5dac ||
                 k == 0x7250e3a1 || k == 0xd130efa6)) {
                u8 was = mC4;
                if (was)
                    ((Bee*)((char*)this - 0x10))->F3E40(0);
                Bee* b = (Bee*)((char*)this - 0x10);
                b->F12C0();
                b->F3940();
                if (was)
                    b->F3E40(1);
            }
        }
        break;

    case 0x72bdb11:
        {
            int n = MGR_s00ee_3800()->F3be30();
            if (FUN_00efc520() >= n)
                FUN_00efc8c0(MGR_s00ee_3800()->F3be30() - 1);
        }
        ((Bee*)((char*)this - 0x10))->F31D0();
        MGR_s00ee_3800()->F427c0();
        break;

    case 0x7311ff7:
    case 0x7311fe9:
    case 0x796d3a0:
        ((Bee*)((char*)this - 0x10))->F31D0();
        MGR_s00ee_3800()->F427c0();
        break;

    default:
        break;
    }
    return false;
}

// @ 0x00ee40f0
void Bee::F40F0()
{
    UintVec ids;
    u32 tag = 0x96b21af3;
    ids.push_back(tag);

    IdQuery query(0xd87454e6, ids);
    KeyVec found;
    GetManager()->ResolveQuery(&found, &query, 0);

    u32 idx = sMathRandom.RandomUint32Uniform((u32)(found.mpEnd - found.mpBegin));
    ApplyPick(found.mpBegin + idx);

    // inlined destructors, in reverse construction order
    SpFree(found.mpBegin);
    SpFree(query.mIds.mpBegin);
    query.mpVtbl = (void*)0x13eb394;
    SpFree(ids.mpBegin);
}

// @ 0x00ee4390
bool SP::cScenarioEditModeBehaviorUI::HandleUIMessage(IWindow_s00ee_4390* window, const Message& msg)
{
    ScenarioData* data = g_16c7aa4_s00ee_4390->mpData;
    if (data) {
    int act = ScenarioTutorials_GetActive();
    ActData* actData = data->GetAct(act);
    if (actData) {
    switch (msg.mType) {
    case 1: {
        IWindow_s00ee_4390* main = WindowManager()->GetMainWindowIndex(0);
        if (main->GetControlID() == 0x7df4c98) {
            int key = msg.keys.key;
            if (key == 0xd || key == 0xe) {
                CommitName(main, actData);
                WindowManager()->SetFocusWindow(0, main->GetParent());
                return false;
            }
        }
        break;
    }

    case 8: {
        if (mpDragWindow != msg.mWindow)
            break;
        const RectT& area = msg.mWindow->GetRealArea();
        Point pos;
        pos.x = msg.mouse.x + area.x1;
        pos.y = area.y1 + msg.mouse.y;
        MoveWindowTo(msg.mWindow, pos);
        uint32_t color = 0xffffffff;
        int selected;
        if (GetSelectedID(&selected)) {
            bool ok;
            if (msg.mWindow->GetControlID() == 0x715cdc0) {
                ok = IsSlotCompatible(selected, mSlotA, mSlotB,
                                      GetScenarioData()->GetActIndex(ScenarioTutorials_GetActive()));
            } else {
                int index = GetSlotIndex(mpDragParent);
                ScenarioItem* item = data->GetItem(act, index);
                ok = CanPlace(item, selected, msg.mWindow->GetControlID(), index, false);
            }
            color = ok ? 0xff00ff00 : 0xffff0000;
        }
        msg.mWindow->SetShadeColor(color);
        Point global = msg.mWindow->ToGlobalCoordinates(Point(msg.mouse.x, msg.mouse.y));
        Message copy = msg;
        copy.mouse.x = global.x;
        copy.mouse.y = global.y;
        WindowManager()->SendMsg(0, WindowManager()->GetMainWindow(), copy, false);
        return false;
    }

    case 7: {
        if (mpDragWindow != msg.mWindow)
            break;
        OnDragEnd();
        int* selected = GetSelectedBehavior();
        if (!selected)
            break;
        switch (msg.mWindow->GetControlID()) {
        case 0x715cdc0: {
            if (!GetScenarioData()->IsValidSelection(GetCurrentBehaviorSet()))
                break;
            if (!IsSlotCompatible(*selected, mSlotA, mSlotB,
                                  GetScenarioData()->GetActIndex(ScenarioTutorials_GetActive())))
                break;
            mpPieMenu->RemoveAllItems();
            SP::cString_s00ee_4390 name;
            ChoiceVector choices;
            int set = GetCurrentBehaviorSet();
            mPieSet = set;
            data->Find(*selected);
            int index = GetSlotIndex(FindSlotWindow(msg.mWindow));
            for (uint32_t i = 0; i < 11; i++) {
                uint32_t id = kChoiceIDs[i];
                ListChoices(&choices, id, *selected);
                bool enabled = IsChoiceAvailable(&choices, set, index);
                GetChoiceName(&choices, *selected, &name);
                if (mSlotB)
                    enabled = mSlotB == id;
                uint32_t color;
                if (enabled)
                    color = ColorRGBToU32(ColorRGB(1.0f, 1.0f, 1.0f));
                else
                    color = ColorRGBToU32(ColorRGB(1.0f, 0.0f, 0.0f));
                mpPieMenu->AddItem(kChoiceIcons[id], name.GetText(), color, enabled);
            }
            mpPieMenu->SetCallback(OnPieMenuChoice, this);
            void* object = GetObjectByID(data->GetItemObjectID(selected));
            HideOnMoveRef anchor(
                new ("Simulator/cHideOnMoveScreenPosition", 0, 0, 0, 0)
                    cHideOnMoveScreenPosition(object, OnPieMenuMoved, this));
            cHideOnMoveScreenPosition* pAnchor = anchor.mpObject;
            float x, y;
            pAnchor->GetScreenPosition(&x, &y);
            mpPieMenu->Show(x, y, pAnchor, 0xb);
            mPieSelection = *selected;
            mPieIndex = index;
            mbPieMenuShown = true;
            PlayUISound(0xb8a2c0b6, GetRecorderState());
            WindowManager()->SetFocusWindow(0, mpPieWindow);
            Refresh();
            g_16c7aa4_s00ee_4390->mpChecklist->ToggleHint(0x68, 0x69);
            g_16c7aa4_s00ee_4390->mpChecklist->ToggleHint(0x79, 0x7a);
            pAnchor->Release();
            return false;
        }
        case 0x7394420:
        case 0x75e1200: {
            if (!GetScenarioData()->IsValidSelection(GetCurrentBehaviorSet()))
                break;
            int index = GetSlotIndex(FindSlotWindow(msg.mWindow));
            ScenarioItem* item = data->GetItem(act, index);
            if (!CanPlace(item, *selected, msg.mWindow->GetControlID(), index, true))
                break;
            if (!AssignInt(msg.mWindow->GetControlID() == 0x7394420 ? &item->mBehaviorA : &item->mBehaviorB,
                           selected))
                break;
            GetScenarioData()->Commit();
            Refresh();
            if (cAvatar* avatar = NounManager()->GetAvatar())
                g_15ad328.SetSelectedWindow(avatar->mSelection.GetSelectedWindow());
            if (item->mKind == 6)
                g_16c7aa4_s00ee_4390->mpChecklist->ToggleHint(0x7e, 0x7f);
            return false;
        }
        }
        break;
    }

    case 0x17:
        if (msg.mSrc->GetControlID() == 0x743b978) {
            GetUTFWinManager()->SetFocusWindow(0, GetUTFWinManager()->GetMainWindow());
            return false;
        }
        break;

    case 0x1c: {
        switch (msg.focus.window->GetControlID()) {
        case 0x5ca82b7:
        case 0x7ccbd48:
            OnNameBlur();
            break;
        case 0x7df4c98:
            if (msg.focus.a0 != 0)
                return false;
            CommitName(msg.focus.window, actData);
            break;
        }
        if (msg.focus.a0 != 0)
            break;
        if (mbNameFocused && !IsEditing() && !IsTextFieldActive(mpWindow, 0, 1)) {
            PlayUISound(0x1db24d95, GetRecorderState());
            SetWindowVisible(mpWindow->FindWindowByID(0x75f60b0, true), false);
            mbNameFocused = false;
        }
        if (mbPieMenuShown && !IsTextFieldActive(mpPieWindow, 0, 1)) {
            mpPieMenu->Hide();
            mbPieMenuShown = false;
            mPieSelection = -1;
            Refresh();
        }
        IWindow_s00ee_4390* field = msg.focus.window;
        switch (field->GetControlID()) {
        case 0x710a140: {
            const wchar_t* text = field->GetCaption();
            AssignString(actData->mDescription, &text);
            return false;
        }
        case 0x743b978: {
            const wchar_t* text = field->GetCaption();
            AssignString(actData->mName, &text);
            return false;
        }
        }
        break;
    }

    case 0x1b: {
        switch (msg.focus.window->GetControlID()) {
        case 0x5ca82b7:
        case 0x7ccbd48:
            OnNameFocus();
            break;
        }
        if (msg.focus.a0 != 0)
            break;
        if (msg.focus.window->GetControlID() != 0x743b978)
            break;
        SetWindowVisible(mpWindow->FindWindowByID(0x75f60b0, true), true);
        SetPageLabel(mpWindow->FindWindowByID(0x453ef531, true), 1);
        PlayUISound(0x72d342a9, GetRecorderState());
        mbNameFocused = true;
        mpPart->Update();
        return false;
    }

    case 0x287259f6:
        switch (msg.button.controlID) {
        case 0x447c040:
            PlayUISound(0x956eae88, GetRecorderState());
            ToggleGridButton();
            return false;

        case -15:
        case -14:
            EndModal(WindowManager()->GetModalWindow(), msg.button.controlID == -15, true);
            PlayUISound(0x1db24d95, GetRecorderState());
            return false;

        case 0x59434c0:
            PlayUISound(0x13bed0aa, GetRecorderState());
            OnShare();
            return false;

        case 0x7461828: {
            ScenarioItem* item = data->GetItem(act, GetSlotIndex(msg.mSrc));
            bool checked = IsButtonChecked(msg.mSrc);
            AssignBool(&item->mbEnabled, &checked);
            PlayUISound(0x7b802df5, GetRecorderState());
            return false;
        }

        case 0x743bc38:
            PlayUISound(0xc433d97a, GetRecorderState());
            gToggleGrid = (float)(gToggleGrid == 0.0f);
            SetGlobalProperty(0x2f77e2a9, gToggleGrid);
            ToggleGridButton();
            data->BeginEdit();
            if (act == data->GetCount() - 1)
                ScenarioTutorials_SetActive(act - 1);
            data->RemoveAct(act);
            data->EndEdit();
            Refresh();
            return false;

        case 0x73bbc38: {
            int index = GetSlotIndex(msg.mSrc);
            data->BeginEdit();
            data->MoveItem(act, index);
            data->EndEdit();
            PlayUISound(0x29a5412f, GetRecorderState());
            Refresh();
            data->Commit();
            return false;
        }

        case 0x7462210: {
            int limit = IsButtonChecked(msg.mSrc) ? 0x3c : -1;
            AssignInt(&actData->mTimeLimit, &limit);
            PlayUISound(0xe76c9b4f, GetRecorderState());
            Refresh();
            return false;
        }

        case 0x7bd2d40:
            BeginModal(mpRenameLayout->FindWindowByID(0x71725b0, true), static_cast<IPanelHandler*>(this), true);
            PlayUISound(0x72d342a9, GetRecorderState());
            return false;

        case 0x74656a0: {
            ScenarioItem* item = data->GetItem(act, GetSlotIndex(msg.mSrc));
            ClearBehaviorSelection();
            ShowItemPanel(item);
            PlayUISound(0x72d342a9, GetRecorderState());
            return false;
        }

        case 0x7bd2db8:
            BeginModal(mpDeleteLayout->FindWindowByID(0x7172600, true), static_cast<IPanelHandler*>(this), true);
            PlayUISound(0x72d342a9, GetRecorderState());
            return false;

        case 0x7bd2dd0: {
            data->BeginEdit();
            int newAct = data->InsertAct(ScenarioTutorials_GetActive() + 1);
            if (newAct > 0)
                ScenarioTutorials_SetActive(newAct);
            data->EndEdit();
            Refresh();
            PlayUISound(0x7858f486, GetRecorderState());
            gToggleSnap = (float)(gToggleSnap == 0.0f);
            SetGlobalProperty(0xbd6db48, gToggleSnap);
            ToggleGridButton();
            return false;
        }

        case 0x5ca82b7:
        case 0x4a1cb6d:
        case 0x7ccbd48:
            OnButtonDefault();
            return false;

        default:
            if (msg.button.controlID >= 0x743b8e1 && msg.button.controlID < 0x743b8e9) {
                ScenarioTutorials_SetActive(msg.button.controlID - 0x743b8e1);
                PlayUISound(0xe10deda0, GetRecorderState());
                Refresh();
                return false;
            }
            break;

        case 0x453ef531:
            SetWindowVisible(mpWindow->FindWindowByID(0x75f60b0, true), false);
            PlayUISound(0x1db24d95, GetRecorderState());
            mbNameFocused = false;
            return false;

        case 0x7e1fe70: {
            bool checked = IsButtonChecked(msg.mSrc);
            AssignBool(&actData->mbFlag7c, &checked);
            PlayUISound(0xe76c9b4f, GetRecorderState());
            Refresh();
            return false;
        }

        case 0x7e1f2f8: {
            int index = GetSlotIndex(msg.mSrc);
            if (actData->mpGoals[index].mCount == 0) {
                IWindow_s00ee_4390* field = msg.mSrc->GetParent()->FindWindowByID(0x7df4c98, false);
                int count = _wtol(field->GetCaption());
                AssignInt(&actData->mpGoals[index].mCount, &count);
            } else {
                int count = 0;
                AssignInt(&actData->mpGoals[index].mCount, &count);
            }
            Refresh();
            GetScenarioData()->Commit();
            PlayUISound(0xe76c9b4f, GetRecorderState());
            return false;
        }
        }
        break;

    case 0x4f5527e8:
        if (msg.button.controlID == 0x721a150) {
            AssignFromTable(&actData->mTimeLimit, msg.button.value, kTimeLimits, &kTimeLimitCount);
            PlayUISound(0xe76c9b4f, GetRecorderState());
        }
        // fall through
    case 6:
        if (IsSlotID(msg.mWindow->GetControlID()) && !mpDragWindow) {
            mpDragWindow = msg.mWindow;
            mDragArea = msg.mWindow->GetRealArea();
            mpDragParent = msg.mWindow->GetParent();
            Point global = msg.mWindow->ToGlobalCoordinates(Point(mDragArea.x1, mDragArea.y1));
            mpDragParent->RemoveWindow(msg.mWindow);
            mDragShade = mpDragWindow->GetShadeColor();
            LayoutRoot()->FindWindow(0x5b598fa)->AddWindow(msg.mWindow);
            msg.mWindow->SetLayoutLocation(global.x, global.y);
            WindowManager()->SetCaptureWindow(1, msg.mWindow);
            mpDragWindow->SetCursorID(0x747d67c);
            PlayUISound(0xc29e2486, GetRecorderState());
            g_15ad328.SetSelectedWindow(0);
            g_16c7aa4_s00ee_4390->mpUI->GetMenu(0)->Refresh();
            return false;
        }
        if (msg.mouse.button == 0x3ea &&
            (msg.mWindow->GetControlID() == 0x715cdd0 || msg.mWindow->GetControlID() == 0x75e1208)) {
            ScenarioItem* item = data->GetItem(act, GetSlotIndex(FindSlotWindow(msg.mWindow)));
            int behavior = item->mBehaviorA;
            if (msg.mWindow->GetControlID() == 0x75e1208)
                behavior = item->mBehaviorB;
            g_15ad328.SurfaceQuery(behavior);
        }
        break;
    }
    }
    }
    return false;
}

// @ 0x00ee6880
u32 __fastcall FUN_00ee6880(u32 this_, int, u32 id)
{
    u32 r;
    if (id == 0xb68dce27)
        r = this_ - 4;
    else if (id == 0xee3f516e || id == 0x2f009dd0)
        r = (this_ != 4) ? this_ : 0;
    else
        r = 0;
    return r;
}

// @ 0x00ee68b0
u32 __fastcall FUN_00ee68b0(Pane* this_, int, void* param)
{
    void* old = this_->mp14;
    if (param != old) {
        if (param != 0)
            vcall_void(param, 0);
        this_->mp14 = param;
        if (old != 0)
            vcall_void(old, 4);
    }

    if (this_->mp14 != 0) {
        void* layout = EAAllocate(0x18, DAT_013f6b3c, 0, 0, 0, 0);
        layout = layout ? cConnectionDialog_ctor(layout) : 0;

        void* prev = this_->mp18;
        if (layout != prev) {
            if (layout != 0)
                vcall_void(layout, 4);
            this_->mp18 = layout;
            if (prev != 0)
                vcall_void(prev, 8);
        }

        if (!cSPUILayout_Init(this_->mp18, (void*)0x15ac72c, 0, 0x5b598fa)) {
            cSPUILayout_Shutdown(this_->mp18, 1);
            void* p = this_->mp18;
            if (p != 0) {
                this_->mp18 = 0;
                vcall_void(p, 8);
            }
            return 0;
        }

        cSPUILayout_SetParentWin_s00ee_6880(this_->mp18, this_->mp14, 1, 0x5b598fa);

        if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xf68dd360, 0, 1) != 0) {
            void* ctl = EAAllocate(0x5c, DAT_013f6b3c, 0, 0, 0, 0);
            ctl = ctl ? FUN_00eeab00(ctl) : 0;
            FUN_00f47630((char*)this_ + 0x1c, 0, ctl);
            void* sub = *(void**)this_->mp1c;
            void* win = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xf68dd360, 0, 1);
            (*(void(__thiscall**)(void*, void*))(*((void**)((char*)sub + 0x10))))(this_->mp1c, win);
        }

        if (FUN_006a25a0(DAT_015fd918, 0x7defc36)) {
            if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0x7defcdf, 0, 1) != 0) {
                void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0x7defcdf, 0, 1);
                if (w != 0)
                    (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 1);
            }
        }

        if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1) != 0) {
            void* pick = EAAllocate(0x50, DAT_013f6b3c, 0, 0, 0, 0);
            pick = pick ? FUN_005a5a50() : 0;
            FUN_00572620((char*)this_ + 0x20, 0, pick);
            void* win = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
            FUN_005a5ec0(this_->mp20, 0, win, 0x2b8745d6, 1, 0);
            FUN_005a4200((char*)this_ + 0x20, 0, 1);
            if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1) != 0) {
                void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
                if (w != 0)
                    (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 0);
            }
        }
    }

    void* srv = SP_MessageServer();
    this_->mp28 = srv;
    this_->m2c = (u32)this_;
    this_->m30 = (u32)DAT_0148aa40;
    this_->m34 = 5;
    this_->m38 = 0;
    if (srv != 0) {
        for (u32 i = 0; i < 0x14; i += 4) {
            u32 ev = *(u32*)((char*)DAT_0148aa40 + i);
            (*(void(__thiscall**)(void*, Pane*, u32))(*((void**)((char*)srv + 0x24))))(srv, this_, ev);
        }
    }
    return 1;
}

// @ 0x00ee6b10
void __fastcall FUN_00ee6b10(Pane* this_, int, void* p)
{
    void* ctl = this_->mp1c;
    if (ctl != 0) {
        void* vt = *(void**)ctl;
        (*(void(__thiscall**)(void*, void*, int))((char*)vt + 0x18))(ctl, p, 1);
    }
    void* pick = this_->mp20;
    if (pick != 0)
        FUN_005a6db0(pick, 0, p);
}

// @ 0x00ee6bd0
void __fastcall FUN_00ee6bd0(Pane* this_)
{
    if (*(void**)((char*)DAT_016c7aa4 + 0x18) == 0)
        return;

    void* ctx = *(void**)((char*)DAT_016c7aa4 + 0x18);
    static const u32 kIds[4] = { 0x7e078b0, 0x7e078b1, 0x7e078b2, 0x7e078b3 };

    for (int i = 0; i < 4; i++) {
        float rgb[3];
        float tmp[3];
        void* r;
        if (i == 0)      r = FUN_00f32330(tmp);
        else if (i == 1) r = FUN_00f32390(tmp);
        else if (i == 2) r = FUN_00f32360(tmp);
        else             r = FUN_00f32300(tmp);
        rgb[0] = ((float*)r)[0];
        rgb[1] = ((float*)r)[1];
        rgb[2] = ((float*)r)[2];
        u32 c = FUN_00458a40(rgb);
        void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kIds[i], 0, 1);
        if (w != 0)
            (*(void(__thiscall**)(void*, u32))(*((void**)((char*)w + 0x5c))))(w, c);
    }

    if (this_->mp24 != 0) {
        void* p = this_->mp24;
        this_->mp24 = 0;
        vcall_void(p, 4);
    }

    static const u32 kCtl[4] = { 0x7e07cc0, 0x7e07cc1, 0x7e07cc2, 0x7e07cc3 };
    for (int i = 0; i < 4; i++) {
        void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kCtl[i], 0, 1);
        if (w != 0) {
            void* o = (*(void*(__thiscall**)(void*, u32))(*((void**)((char*)w + 0xc))))(w, 0x8ed27e7a);
            if (o != 0)
                (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)o + 0x28))))(o, 4, 0);
        }
    }

    if (this_->mp20 != 0) {
        void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
        if (w != 0)
            (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 0);
    }

    if (this_->mp1c != 0) {
        void* a = FUN_00f0d3e0(ctx);
        void* b = FUN_00f31e40(ctx, a);
        FUN_00eeb580(this_->mp1c, b);
    }
}

// @ 0x00ee6e80
Pane::Pane()
: mb10(0), mp14(0), mp18(0), mp1c(0), mp20(0), mp24(0), mp28(0),
               m2c(0), m30(0), m34(0), m38(0)
{
}

// @ 0x00ee6f90
void __fastcall FUN_00ee6f90(Pane* this_, int, char b)
{
    if (b)
        FUN_00ee6bd0(this_);

    if (this_->mp18 != 0) {
        static const u32 kIds[6] = { 0x9694210d, 0x7defcdf, 0x7e07cc0, 0x7e07cc1, 0x7e07cc2, 0x7e07cc3 };
        for (int i = 0; i < 6; i++) {
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kIds[i], 0, 1);
            if (w != 0) {
                int slot = b ? 0x104 : 0x108;
                (*(void(__thiscall**)(void*, void*))(*((void**)((char*)w + slot))))(w, (char*)this_ + 4);
            }
        }
    }
    if (this_->mp1c != 0)
        (*(void(__thiscall**)(void*, char))(*((void**)((char*)this_->mp1c + 0x1c))))(this_->mp1c, b);
}

// @ 0x00ee70e0
u32 __fastcall FUN_00ee70e0(Pane* this_, int, void* ev, void* arg)
{
    u32 ret = (u32)DAT_016c7aa4;
    void* ctx = *(void**)((char*)DAT_016c7aa4 + 0x18);

    u32* pev = (u32*)ev;
    if (pev[2] == 0x287259f6) {
        u32 msg = pev[3];
        if (msg == 0x9694210d) {
            if (ctx != 0) {
                if (FUN_00f31e50(ctx)) {
                    return FUN_00f31c20(ctx, (int)arg) & 0xffffff00;
                }
                FUN_00f343a0(ctx, 1);
                FUN_00f31c20(ctx, 1);
                FUN_00ee6bd0(this_);
                ret = 0;
            }
        }
        else if (msg + 0xf81f8340 < 4) {
            void* sys = FUN_00a206f0();
            void* at = sys ? (*(void*(__thiscall**)(void*))(*((void**)((char*)sys + 0x20))))(sys) : 0;
            FUN_00435ed0(at, 0xe76c9b4f);
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp14, msg, 0, 1);
            FUN_00b5f950((char*)this_ + 0x20, 0, w);
            if (this_->mp1c != 0 && this_->mp20 != 0) {
                void* dlg = CALL_CSPUILAYOUT_FindWindowByID(this_->mp14, 0xd68f3fd2, 0, 1);
                FUN_00e12f80(dlg, 1);
                void* o = CALL_CSPUILAYOUT_FindWindowByID(this_->mp14, msg - 0x410, 0, 1);
                u32 col = (*(u32(__thiscall**)(void*))(*((void**)((char*)o + 0x30))))(o);
                float v[3];
                FUN_00576ab0(v, col);
                FUN_005a4e20(this_->mp20, 0, v);
            }
            if (this_->mp18 != 0) {
                FUN_00eea860(0);
                ret = 0;
            }
        }
    }
    return ret & 0xffffff00;
}

// @ 0x00ee7240
u32 __fastcall FUN_00ee7240(Pane* this_, int, u32 code, void* param)
{
    void* ctx = *(void**)((char*)DAT_016c7aa4 + 0x18);
    u32* pp = (u32*)param;

    if (code <= 0x7e1ea71) {
        if (code == 0x7e1ea71) {
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
            if (w != 0)
                (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 0);
            return 0;
        }
        if (code == 0x7e19b84) {
            void* p = (void*)pp[2];
            if (p == 0)
                return 0;
            if (!FUN_00eea8e0(this_->mp1c, 0, p))
                return 0;
            if (this_->mp18 == 0)
                return 0;
            FUN_00b5f950((char*)this_ + 0x24, 0, p);

            static const u32 kCtl[4] = { 0x7e07cc0, 0x7e07cc1, 0x7e07cc2, 0x7e07cc3 };
            for (int i = 0; i < 4; i++) {
                void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kCtl[i], 0, 1);
                FUN_00ed1350(w, 0);
            }
            if (this_->mp20 != 0) {
                void* dlg = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
                FUN_00e12f80(dlg, 1);
                float col[3];
                FUN_00eeaa90(this_->mp1c, 0, p, col);
                FUN_005a4e20(this_->mp20, 0, col);
            }
            return 0;
        }
        return 0;
    }

    if (code == 0x90e08f60) {
        u32 raw = pp[4];
        if (raw == 0 || ctx == 0)
            return 0;
        if ((void*)(raw - 8) != this_->mp20)
            return 0;
        u32 c = pp[2];
        float rgb[3];
        FUN_00576ab0(rgb, c);
        if (this_->mp24 != 0) {
            void* mo = this_->mp24;
            u32 id = (*(u32(__thiscall**)(void*, int))(*((void**)((char*)mo + 0x1c))))(mo, 1);
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, id - 0x410, 0, 1);
            if (w != 0) {
                void* w2 = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, id - 0x410, 0, 1);
                (*(void(__thiscall**)(void*, u32))(*((void**)((char*)w2 + 0x5c))))(w2, c);
            }
        }
        u32 cls = (*(u32(__thiscall**)(void*, int))(*((void**)((char*)this_->mp24 + 0x1c))))(this_->mp24, 1);
        if (cls <= 0x7e099a3) {
            switch (cls - 0x7e07cc0) {
            case 0:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f32150(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x7b1794db, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            case 1:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f321a0(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x7b1794db, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            case 2:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f321f0(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x9b06d0eb, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            case 3:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f32100(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x9b06d0eb, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            default:
                break;
            }
        }
        else if (cls == 0x7e099a3) {
            if (FUN_00eea8e0(this_->mp1c, 0, this_->mp24))
                FUN_00eea910(this_->mp1c, this_->mp24, rgb[0], rgb[1], rgb[2]);
        }
        return 0;
    }

    if (code == 0xd69290d7) {
        FUN_00f33bf0(ctx);
        void* a = 0;
        void* b = 0;
        FUN_00eeb920(&a, ctx, 0);
        FUN_00f344e0(ctx, &a, &b);
        FUN_00f34560(ctx);
        FUN_00f31ea0(ctx);
        return 0;
    }
    if (code == 0xd69290d8) {
        void* a = 0;
        void* b = 0;
        FUN_00eeb920(&a, ctx, 0);
        FUN_00f344e0(ctx, &a, &b);
        return 0;
    }
    return 0;
}

// @ 0x00ee7810
int __cdecl FUN_00ee7810(u32 id)
{
    if (id == 0x29c388a)
        return (int)0xb8669ec9;
    if (id == 0x3a8be428)
        return 0x37148141;
    return (id != 0x6d60a1cc ? (int)0x7a3d42b8 : 0) + (int)0xbcd73e89;
}

// @ 0x00ee7850
int* __cdecl FUN_00ee7850(int* p)
{
    while (p != 0) {
        int n = (*(int(__thiscall**)(int*))((char*)*(void**)p + 0x1c))(p);
        if (!(8 < (u32)n + 0xf8d3d7e0u))
            break;
        p = (int*)(*(void*(__thiscall**)(int*))((char*)*(void**)p + 0x10))(p);
    }
    return p;
}

// @ 0x00ee78c0
bool __stdcall FUN_00ee78c0(int id)
{
    int found1 = -1;
    int found2 = found1 - 1;
    for (u32 i = 0; i < 0xf; i++) {
        if (DAT_0148aafc[i] == (u32)id) {
            found1 = (int)i;
            break;
        }
    }
    for (u32 j = 0; j < 0xf; j++) {
        if (DAT_0148aac0[j] == (u32)id) {
            found2 = (int)j;
            break;
        }
    }
    return found2 != found1;
}

// @ 0x00ee7910
char __stdcall FUN_00ee7910(int id, u32* out, u8* flag)
{
    if (out != 0 && flag != 0) {
        u32 i = 0;
        do {
            if (DAT_0148aafc[i] == (u32)id) {
                *out = i;
                *flag = 0;
                return 1;
            }
            i++;
        } while (i < 0xf);
        i = 0;
        do {
            if (DAT_0148aac0[i] == (u32)id) {
                *out = i;
                *flag = 1;
                return 1;
            }
            i++;
        } while (i < 0xf);
    }
    return 0;
}

// @ 0x00ee7990
void __thiscall SpuEd::BaseDtor()
{
    o000 = 0x148abd0;
    o008 = 0x148abc8;
    _ReadWriteBarrier();
    if (o02c)
    {
        u32 h = o02c;
        o02c = 0;
        RemoveHandler((void*)h, (void*)o030, o034, (int)o038, (int)o03c);
    }
    if (o024) ((VI*)o024)->v01();
    if (o020) ((VI*)o020)->v01();
    if (o01c) ((VI*)o01c)->v02();
    if (o018) ((VI*)o018)->v02();
    if (o014) ((VI*)o014)->v02();
    if (o010) ((VI*)o010)->v02();
    if (o00c) ((VI*)o00c)->v02();
    o008 = 0x13eb394;
    o000 = 0x13ec458;
}

// @ 0x00ee7a50
void __thiscall SpuEd::DtorDerived()
{
    void* h = this ? (void*)((char*)this + 8) : 0;
    ((XMsgSrv*)MessageServer())->m11(h, 0x44ef2b8, 0xffffd8f1);
    if (o024)
    {
        ((VI*)o024)->v09();
        if (o024) { VI* p = (VI*)o024; o024 = 0; p->v01(); }
    }
    if (o020)
    {
        ((XPaletteUI*)o020)->Shutdown();
        if (o020) { VI* p = (VI*)o020; o020 = 0; p->v01(); }
    }
    if (o00c)
    {
        ((VIN*)o00c)->n06();
        if (o00c) { VI* p = (VI*)o00c; o00c = 0; p->v02(); }
    }
    if (o014)
    {
        ((VI*)o014)->v05();
        if (o014) { VI* p = (VI*)o014; o014 = 0; p->v02(); }
    }
    if (o018)
    {
        ((VI*)o018)->v05();
        if (o018) { VI* p = (VI*)o018; o018 = 0; p->v02(); }
    }
    if (o010)
    {
        ((VI*)o010)->v05();
        if (o010) { VI* p = (VI*)o010; o010 = 0; p->v02(); }
    }
}

// @ 0x00ee7b40
void __thiscall SpuEd::SetMode(int mode, u8 on)
{
    if (mode == -1) return;
    switch (mode)
    {
    case 0:
        if (on)
        {
            char* u = (char*)g_universe;
            ((XHint*)*(u32*)(u + 0xd4))->ToggleHint(0x89, 0x8a);
        }
        break;
    case 1: ((VI*)o00c)->v08(on); break;
    case 2: ((VI*)o018)->v06(on); break;
    case 3: ((VI*)o014)->v06(on); break;
    case 4: ((VI*)o010)->v06(on); break;
    }
    if (on) o028 = (u32)mode;
    else o028 = 0xffffffff;
}

// @ 0x00ee7c60
void __thiscall SpuEd::Update(void* arg)
{
    VI* p = (VI*)o00c;
    if (p) p->v07((int)arg);
    if (o020) ((XPaletteUI*)o020)->UpdateCategories(arg);
    if (o010)
    {
        if (((XPaletteUI*)o020)->FindCategoryIndex() == 4)
            ((VI*)o010)->v07((int)arg);
    }
}

// @ 0x00ee7cb0
int __cdecl FindPlanetSlot(u32 id, int* outA, int* outB)
{
    u32 key, off;
    if (id >= 0x72c2826u) { key = 0x3a8be428; off = id + 0xf8d3d7da; }
    else if (id >= 0x72c2823u) { key = 0x29c388a; off = id + 0xf8d3d7dd; }
    else { key = 0x6d60a1cc; off = id + 0xf8d3d7e0; }

    char* rec = (char*)GetPlanetRec();
    void* mgr = GetSpeciesMgr();
    int count = (*(int*)(rec + 0xc0) - *(int*)(rec + 0xbc)) / 0xc;
    int found = -1;
    int i = 0;
    if (count > 0)
    {
        int walk = 0;
        do
        {
            XSpecies* sp = (XSpecies*)((XSpecMgr*)mgr)->GetAt(*(u32*)(rec + 0xbc) + walk);
            if (sp->GetID() == key && *(int*)(*(int*)(rec + 0xf8) + i * 4) == (int)off)
            {
                found = i;
                break;
            }
            i++;
            walk += 0xc;
        } while (i < count);
    }
    if (outA) *outA = (int)key;
    if (outB) *outB = (int)off;
    return found;
}

// @ 0x00ee7da0
SpuEd* __thiscall SpuEd::Ctor()
{
    o004 = 0;
    o008 = 0x14426a0;
    o00c = 0x13eb394;
    o010 = 0x140b5a0;
    _ReadWriteBarrier();
    o000 = 0x148ac18;
    o008 = 0x148abfc;
    o00c = 0x148abf4;
    o010 = 0x148abf0;
    char* p = (char*)this + 0x18;
    int n = 2;
    do { ((XSub*)p)->Ctor(); p += 0x70; } while (--n >= 0);
    o168 = 0;
    o16c = 0;
    o170 = 0;
    if (MessageServer())
        ((XMsgSrv*)MessageServer())->m09((void*)((char*)this + 0xc), 0x65ff54a);
    return this;
}

// @ 0x00ee7e50
void __thiscall SpuEd::Dtor3()
{
    o000 = 0x148ac18;
    o008 = 0x148abfc;
    o00c = 0x148abf4;
    o010 = 0x148abf0;
    if (MessageServer())
        ((XMsgSrv*)MessageServer())->m11((void*)((char*)this + 0xc), 0x65ff54a, 0xffffd8f1);
    if (o170) ((VI*)o170)->v01();
    if (o16c) ((VI*)o16c)->v01();
    if (o168) ((VI*)o168)->v02();
    char* p = (char*)this + 0x168;
    int n = 2;
    do { p -= 0x70; ((XSub*)p)->Dtor(); } while (--n >= 0);
    o008 = 0x13eb938;
    o000 = 0x13ec458;
    o00c = 0x13eb394;
}

// @ 0x00ee7f00
u8 __thiscall SpuEd::InitLayout(void* parent)
{
    u8 ret = 0;
    void* mem = EAAllocate(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
    XDialog* dlg = mem ? ((XDialog*)mem)->Ctor() : 0;
    XDialog* old = (XDialog*)o168;
    if (dlg != old)
    {
        if (dlg) ((VI*)dlg)->v00();
        o168 = (u32)dlg;
        if (old) ((VI*)old)->v02();
    }
    if (!((XLayout*)o168)->Init((const void*)0x15ac800, 0, 0x5b598fa))
    {
        ((XLayout*)o168)->Shutdown(1);
        if (o168)
        {
            VI* p = (VI*)o168;
            o168 = 0;
            p->v02();
        }
        return 0;
    }
    XWin* w = (XWin*)((XLayout*)o168)->FindWindowByID(0x7355a68, 1);
    if (parent && w)
    {
        ((XLayout*)o168)->SetParentWin(parent, 1, 0x5b598fa);
        Rect* rf = ((XWin*)parent)->w14();
        Rect rc;
        rc.x = 0.0f;
        rc.y = 0.0f;
        rc.w = rf->w - rf->x;
        rc.h = rf->h - rf->y;
        ((XWin*)w)->w27(&rc);
        ((XWin*)w)->w65((void*)((char*)this + 8));
        ret = 1;
    }
    int tag = 0x72c2820;
    char* kp = (char*)0x15ac80c;
    char* sub = (char*)this + 0x18;
    int n = 3;
    int k = 0;
    do
    {
        Rect r2;
        r2.x = 0.0f; r2.y = 0.0f; r2.w = 0.0f; r2.h = 0.0f;
        void* win = ((XLayout*)o168)->FindWindowByID((u32)(k + 0x78fea00), 1, &r2);
        if (((XSub*)sub)->Check(win))
        {
            if (((XSub*)sub)->CheckKey(kp, 3))
            {
                for (int i = 0; i < 3; i++)
                {
                    XLayout* l2 = (XLayout*)((XSub*)sub)->Get(i);
                    XWin* ww = (XWin*)l2->FindWindowByID(0x4a1cb70, 1);
                    if (ww) ((XWin*)ww)->w20(tag);
                    tag++;
                }
            }
        }
        kp += 0xc;
        sub += 0x70;
        k++;
    } while (--n);
    return ret;
}

// @ 0x00ee8110
void __thiscall SpuEd::ShutdownLayout()
{
    char* p = (char*)this + 0x18;
    int n = 3;
    do { ((XSub*)p)->Reset(); p += 0x70; } while (--n);
    if (o168)
    {
        ((XLayout*)o168)->SetParentWin((void*)n, 1, 0x5b598fa);
        ((XLayout*)o168)->Shutdown(1);
        if (o168)
        {
            VI* p2 = (VI*)o168;
            o168 = (u32)n;
            p2->v02();
        }
    }
}

// @ 0x00ee8180
u8 __thiscall SpuEd::OnMsg2(u32 msg, void* p)
{
    if (msg == 0x65ff54a && *(u32*)((char*)p + 0x10) == 0x40464100)
    {
        u32 v = *(u32*)((char*)p + 0x18);
        switch (v)
        {
        case 0x7ec9d82e:
        case 0x556c486:
        case 0x3b0ac2c4:
        case 0xd5521361:
            break;
        default:
            return 1;
        }
        XLayout* lay = (XLayout*)o15c;
        u8 vis = lay->IsVisible();
        XWin* w = (XWin*)lay->GetWin();
        if (w) ((VIN*)w)->n00();
        if (vis) ((VI*)((char*)this - 0xc))->v06(0);
        ((VI*)((char*)this - 0xc))->v05();
        ((VI*)((char*)this - 0xc))->v04((int)w);
        if (vis) ((VI*)((char*)this - 0xc))->v06(1);
        if (w) ((VIN*)w)->n01();
    }
    return 1;
}

// @ 0x00ee8240
void __thiscall XCat::Refresh(u8 which)
{
    char* rec = *(char**)((char*)g_universe + 0x18);
    if (!rec) return;
    u32 id = *(u32*)(rec + 0x160);
    int outCat = -1;
    u8 flag;
    FindCategory(id, &outCat, &flag);
    if (outCat < 0) return;
    if ((u32)outCat >= 0xf) return;
    u32 chosen = which ? g_catA[outCat] : g_catB[outCat];
    if (chosen == id) return;
    XUniv* u = (XUniv*)rec;
    u->F33bf0();
    u->F352c0(chosen);
    u->F34560();
    u->F31ea0();
}

// @ 0x00ee82c0
void __thiscall SpuEd::UpdateCategory(u32 sel)
{
    char* rec = *(char**)((char*)g_universe + 0x18);
    if (!rec) return;
    u32 id = *(u32*)(rec + 0x160);
    int outCat;
    u8 flag = 0;
    ((XCat*)this)->FindCategory(id, &outCat, &flag);
    u32 idx = sel + 0xe94e7f70;
    if ((int)idx < 0 || idx >= 0xf) return;
    u32 chosen = flag ? g_catA[idx] : g_catB[idx];
    if (chosen == id) return;
    XUniv* u = (XUniv*)rec;
    u->F33bf0();
    u->F352c0(chosen);
    u->F34560();
    u->F31ea0();
    XWin* w = (XWin*)((XLayout*)o168)->FindWindowByID(0x16b1858d, 1);
    if (!w) return;
    u8 inTable = ((XCat*)this)->IsInTable(chosen);
    Fn1350(w, flag && inTable);
    Fn2fa0(w, sel);
}

// @ 0x00ee83a0
void __thiscall SpuEd::SetObject(void* obj)
{
    void* old = (void*)o170;
    if (obj != old)
    {
        if (obj) ((VI*)obj)->v00();
        o170 = (u32)obj;
        if (old) ((VI*)old)->v01();
    }
    FindPlanetSlot((u32)((XW2*)(void*)o170)->x07(), (int*)&obj, 0);
    u32 tag;
    switch ((u32)obj)
    {
    default:         tag = (u32)obj;   break;
    case 0x29c388a:  tag = 0xdc1ff56b; break;
    case 0x3a8be428: tag = 0xc86f310d; break;
    case 0x6d60a1cc: tag = 0xcece845;  break;
    }
    XLaunchCtx ctx;
    ctx.Ctor();
    ctx.v[0] = tag;
    ctx.v[14] = (u32)((char*)this + 0x10);
    LaunchCtx(&ctx);
    ctx.Dtor();
}

// @ 0x00ee8460
void __thiscall SpuEd::Select(void* win)
{
    u8 x = (FindPlanetSlot((u32)((XW2*)win)->x07(), 0, 0) != -1);
    void* cur = WindowManager_s00ee_7990()->w18(1);
    u8 b;
    if (win == cur) b = 1;
    else b = ((XWin*)win)->w62((int)cur);
    u8 y = b;
    XWin* wa = (XWin*)((XWin*)win)->w60(0x73272b0, 0);
    if (wa) wa->w31(1, y);
    if (b) y = x ? 1 : 0; else y = 0;
    XWin* wb = (XWin*)((XWin*)win)->w60(0x4a1cb6d, 0);
    if (wb) wb->w31(1, y);
    if (b) x = y ? 1 : 0; else x = 0;
    XWin* wc = (XWin*)((XWin*)win)->w60(0x7b6b2cd, 0);
    if (wc) wc->w31(1, x);
}

// @ 0x00ee8570
void __thiscall SpuEd::Dtor4()
{
    o000 = 0x148ac3c;
    o008 = 0x148ac34;
    _ReadWriteBarrier();
    if (o024) ((VI*)o024)->v01();
    if (o020) ((VI*)(o020 + 0xc))->v01();
    if (o00c)
    {
        u32 h = o00c;
        o00c = 0;
        RemoveHandler((void*)h, (void*)o010, o014, (int)o018, (int)o01c);
    }
    o008 = 0x13eb394;
    o000 = 0x13ec458;
}

// @ 0x00ee85e0
void __thiscall SpuEd::Enable2(u8 on)
{
    char* rec = *(char**)((char*)g_universe + 0x18);
    if (on)
    {
        if (o00c == 0)
        {
            void* p = (void*)((char*)this + 8);
            o00c = (u32)MessageServer();
            o010 = (u32)p;
            o014 = 0x15ac738;
            o018 = 1;
            o01c = 0;
            if (o00c && p)
                ((XMsgSrv*)o00c)->m09(p, *(u32*)0x15ac738);
            ((XUniv*)rec)->F36380();
        }
        char* u = (char*)g_universe;
        ((XHint*)*(u32*)(u + 0xd4))->ToggleHint(0xa5, 0xa6);
        return;
    }
    ((XUniv*)rec)->F363c0();
    if (o024)
    {
        ((VI*)o024)->v03(0);
        if (o024) { VI* p = (VI*)o024; o024 = 0; p->v01(); }
    }
    if (o00c)
    {
        u32 h = o00c;
        o00c = 0;
        RemoveHandler((void*)h, (void*)o010, o014, (int)o018, (int)o01c);
    }
}

// @ 0x00ee86c0
u8 __thiscall SpuEd::OnMsg3(u32 msg, void* p)
{
    if (msg == 0x73e7eb7)
    {
        void* old = (void*)o018;
        if (p != old)
        {
            if (p) ((VI*)((char*)p + 0xc))->v00();
            o018 = (u32)p;
            if (old) ((VI*)((char*)old + 0xc))->v01();
        }
        g_univ18 = o018;
        g_launchObj.Add(0);
    }
    return 0;
}

// @ 0x00ee8720
u8 __thiscall SpuEd::SetSource(void* src)
{
    void* old = (void*)o00c;
    if (src != old)
    {
        if (src) ((VI*)src)->v00();
        o00c = (u32)src;
        if (old) ((VI*)old)->v01();
    }
    if (o00c)
    {
        void* mem = EAAllocate(0x3c, (const char*)0x13eb430, 0, 0, 0, 0);
        void* obj = mem ? ((XObj3c*)mem)->Init() : 0;
        void* old2 = (void*)o010;
        if (obj != old2)
        {
            if (obj) ((VI*)obj)->v02();
            o010 = (u32)obj;
            if (old2) ((VIN*)old2)->n03();
        }
        void* a = (void*)o00c;
        VI* pb = (VI*)o010;
        void* r = ((XWin*)a)->w60(0xd68dd230, 1);
        pb->v04((int)r);
    }
    return 1;
}

// @ 0x00ee87f0
void __thiscall SpuEd::Close()
{
    ((VI*)this)->v08(0);
    if (o010)
    {
        ((VI*)o010)->v05();
        if (o010) { VI* p = (VI*)o010; o010 = 0; ((VIN*)p)->n03(); }
    }
    if (o00c) { VI* q = (VI*)o00c; o00c = 0; q->v01(); }
}

// @ 0x00ee8860
uint8_t C40::Setup(int a)
{
    (void)a;
    mState = -1;

    cSPPalette* pal = new ("Simulator/Scenario/SculptUI", 0, 0, 0, 0) cSPPalette();
    mPalette = pal;

    cSPPaletteUI* palUI = new ("Simulator/Scenario/SculptUI", 0, 0, 0, 0) cSPPaletteUI();
    mPalUI = palUI;

    UIEditor* ed = new ("Editor", 0, 0, 0, 0) UIEditor();
    mEditor = ed;
    mEditor->F1c();

    EA::ResourceMan::Key_s00ee_8860 key;
    key.instanceID = 0xdc;
    key.typeID = 0xb1b104;
    key.groupID = 0x406b6a00;
    if (mPalette->Init(key, -1, 0, 0, 0, 0, 0)) {
        AutoRefCount_s00ee_8860<cSPPaletteInfo> info =
            new ("Editor", 0, 0, 0, 0) cSPPaletteInfo();
        info->m08 = (RefCountInt*)((Space*)GetSpacePtr())->m10;
        info->m14 = mEditor.mpObject;
        if (info->m10) {
            RefCount04* p = info->m10;
            info->m10 = 0;
            p->Release();
        }
        info->m18 = 0x268a;
        mPalUI->Init(mPalette.mpObject,
                     SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x8d0f4fb),
                     0, info);
        mPalUI->SetCurrentCategoryIndex(0);
        mPalUI->SetFlag(1);
    }

    OBJ64* o64 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ64();
    mObj64 = o64;
    if (!mObj64->F4(mPalUI->GetSubCategory(3)->GetPageUI(0)->m10)) {
        mObj64 = 0;
    }

    OBJ174* o174 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ174();
    mObj174 = o174;
    if (!mObj174->F4(mPalUI->GetSubCategory(2)->GetPageUI(0)->m10)) {
        mObj174 = 0;
    }

    OBJ28* o28 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ28();
    mObj28 = o28;
    if (!mObj28->F4()) {
        mObj28 = 0;
    }

    OBJ14* o14 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ14();
    mObj14 = o14;
    if (!mObj14->F5(mPalUI->GetSubCategory(1)->GetPageUI(0)->m10)) {
        mObj14 = 0;
    }
    return 1;
}

// @ 0x00ee8d80
void OBJ174::Update()
{
    PlanetRecord* rec = (PlanetRecord*)GetActivePlanetRecord();

    {
        IWindow_s00ee_8860* w = mLayout->FindWindowByID(0x72bfdfd, 1);
        if (w) {
            IWindow_s00ee_8860* c = (IWindow_s00ee_8860*)w->AsInterface(0xf00a8a0);
            if (c) {
                int n = c->V30(0);
                c->V1c((int)((float)n * rec->m10c));
            }
        }
    }

    uint32_t id = 0x72c2820;
    for (int k = 9; k != 0; --k) {
        IWindow_s00ee_8860* w = mLayout->FindWindowByID(id, 1);
        if (w) {
            int idx = FUN_00ee7cb0(id, 0, 0);
            bool found = (idx != -1);
            IWindow_s00ee_8860* c = (IWindow_s00ee_8860*)w->Vf0(0x73d54a0, 1);
            if (c) c->V7c(1, found ? 0 : 1);
            IWindow_s00ee_8860* c2 = (IWindow_s00ee_8860*)w->Vf0(0x4a1cb6e, 1);
            if (c2) c2->V7c(1, *(uint32_t*)&rec->m10c);
            if (found) {
                EA::ResourceMan::Key_s00ee_8860 k;
                k.instanceID = rec->mBc.mBegin[idx].instanceID;
                k.typeID = 0x2f7d0004;
                k.groupID = rec->mBc.mBegin[idx].groupID;
                SPUIHelpers::SetWindowImage(w, &k, -1);
            }
            Fn8460(w);
        }
        ++id;
    }

    if (!mLayout) return;
    void* space = GetSpacePtr();
    if (!space) return;
    LayoutRecord* e = ((Space*)space)->m160;
    int idx = -1;
    uint8_t flag = 0;
    Fn7910(e, &idx, &flag);

    for (uint32_t i = 0; i < 0xf; i++) {
        IWindow_s00ee_8860* w = mLayout->FindWindowByID(0x16b18090 + i, 1);
        if (w) {
            IWindow_s00ee_8860* q = (IWindow_s00ee_8860*)w->AsInterface(0x8ed27e7a);
            if (q) q->V28(4, i == (uint32_t)idx);
        }
    }

    IWindow_s00ee_8860* last = mLayout->FindWindowByID(0x16b1858d, 1);
    if (last) {
        int i1 = -1;
        int i2 = i1 - 1;
        for (int i = 0; i < 0xf; i++) { if (gTableB[i] == e) { i1 = i; break; } }
        for (int i = 0; i < 0xf; i++) { if (gTableA[i] == e) { i2 = i; break; } }
        bool diff = (i2 != i1);
        bool on = flag ? diff : false;
        IWindow_s00ee_8860* q = (IWindow_s00ee_8860*)last->AsInterface(0x8ed27e7a);
        if (q) q->V28(4, on);
        last->V7c(2, diff);
    }

    IWindow_s00ee_8860* tw = mLayout->FindWindowByID(0x7d61ff2, 1);
    if (tw && tw->V10()) {
        float* hp = ((IWindow_s00ee_8860*)tw->V10())->V38();
        float a0 = hp[0];
        float a2 = hp[2];
        float* tp = tw->V38();
        float c0 = tp[0];
        float c2 = tp[2];
        tw->V70((float)floor((double)(a0 + ((a2 - a0) - (c2 - c0)) * 0.5f)));
    }
}

// @ 0x00ee90e0
OBJ14* OBJ14::ScalarDeletingDtor(unsigned char flags)
{
    *(void**)this = (void*)0x148ac5c;
    _ReadWriteBarrier();
    if (mp10) mp10->Release();
    if (mpC) mpC->Release();
    *(void**)this = (void*)0x13ec458;
    if (flags & 1) operator delete(this);
    return this;
}

// @ 0x00ee9130
void OBJ14::SetVisible(uint8_t visible)
{
    if (visible) {
        GetTutorialsUI()->ToggleHint(0x8f, 0x90);
        Obj10* p = mp10;
        if (p) p->Fn6bd0();
    }
    Obj10* p10 = mp10;
    if (p10) p10->SetVisible(visible);
}

// @ 0x00ee9180
C40::C40()
: mObj14(0), mObj28(0), mObj64(0), mObj174(0), mPalette(0), mPalUI(0), mEditor(0)
{
    mC2c = 0;
    mC30 = 0;
    mC34 = 0;
    mC38 = 0;
    mC3c = 0;
    if ((gRegFlags & 1) == 0) {
        gRegFlags |= 1;
        ((cRegNode*)0x16c780c)->Construct(0);
        *(void**)0x16c780c = (void*)0x148aba8;
        atexit(FUN_013c8a60);
    }
    if (((cRegNode*)0x16c780c)->Flag() == 0)
        ((cRegNode*)0x16c780c)->Fallback();
    if ((gRegFlags & 2) == 0) {
        gRegFlags |= 2;
        ((cRegNode*)0x16c77f8)->Construct(0);
        *(void**)0x16c77f8 = (void*)0x148abb8;
        atexit(FUN_013c8a50);
    }
    if (((cRegNode*)0x16c77f8)->Flag() == 0)
        ((cRegNode*)0x16c77f8)->Fallback();
}

// @ 0x00ee9260
void C40::Update()
{
    switch (mState) {
        case 1:
            {
                OBJ14* p = mObj14.mpObject;
                if (p->mp10) p->mp10->Fn6bd0();
            }
            break;
        case 2:
            mObj174->Update();
            break;
        case 3:
            mObj64->Fn3b0c0();
            break;
    }
    ((IMsgServer*)MessageServer_s00ee_8860())->Send(0x743b6fa, 0, 0);
}

// @ 0x00ee92b0
void OBJ174::SetVisible(bool visible)
{
    if (mLayout) mLayout->SetVisibility(visible);
    if (visible) {
        uint32_t i = 0;
        do {
            IWindow_s00ee_8860* w = mLayout->FindWindowByID(0x16b18090 + i, 1);
            if (w) {
                uint8_t* p = (uint8_t*)this + 8;
                w->V104(p);
            }
            ++i;
        } while (i < 0xf);
        IWindow_s00ee_8860* w = mLayout->FindWindowByID(0x16b1858d, 1);
        if (w) {
            uint8_t* p = (uint8_t*)this + 8;
            w->V104(p);
        }
        Update();
        GetTutorialsUI()->ToggleHint(0x9b, 0x9c);
    }
}

// @ 0x00ee9350
void OBJ28::F7(int a)
{
    (void)a;
    Space* space = (Space*)GetSpacePtr();
    EffectSlot* slot = (EffectSlot*)space->F32790(FUN_00efe5b0());
    EffectSlot* cur = (EffectSlot*)space->m1b0;
    bool created;
    if (cur == slot || slot == 0) {
        created = true;
    } else {
        created = false;
        cur = slot;
    }
    void* obj = cur ? cur->mpObject : 0;
    void* owner = cur ? cur->mpOwner : 0;

    if (gSelObject != obj) {
        if (m24.mpObject) {
            m24.mpObject->V0c(0);
            if (m24.mpObject) {
                EffectsHandle* p = m24.mpObject;
                m24.mpObject = 0;
                p->Release();
            }
        }
        gSelObject = obj;
        if (obj) {
            EffectsManager* em = (EffectsManager*)EffectsManagerPtr();
            if (m24.mpObject) {
                EffectsHandle* p = m24.mpObject;
                m24.mpObject = 0;
                p->Release();
            }
            em->V2c(*(int*)((uint8_t*)owner + 0x3c), 0, &m24);
            if (m24.mpObject) m24.mpObject->V08(0);
        }
    }

    if (m24.mpObject) {
        uint8_t* t = (uint8_t*)FUN_00b18e00(obj);
        uint8_t c = t[0x6e];

        EffectPose pose;
        pose.flags = 0;
        pose.refs = 0;
        pose.pos[0] = gVec3X;
        pose.pos[1] = gVec3Y;
        pose.pos[2] = gVec3Z;
        pose.f = 1.0f;
        Matrix3_AssignFrom(&pose.mat, (const void*)0x16c7870);

        float* v = vcallR<float*, VObj_s00ee_8860, 0x2c>((VObj_s00ee_8860*)t);
        pose.pos[0] = v[0];
        pose.pos[1] = v[1];
        pose.pos[2] = v[2];
        pose.flags |= 4;
        ++pose.refs;

        void* qq = vcallR<void*, VObj_s00ee_8860, 0x30>((VObj_s00ee_8860*)t);
        Matrix3 tmp;
        float* r = (float*)Matrix3FromQuaternion(&tmp, qq);
        for (int i = 0; i < 9; ++i) pose.mat.m[i] = r[i];
        pose.flags |= 2;
        ++pose.refs;

        pose.f = cur->Fn1ff0();
        ++pose.refs;
        m24.mpObject->V14(&pose);

        float f = cur->Fn1b70();
        if (!created) f *= 0.25f;
        m24.mpObject->V44(4, &f, 1);
        m24.mpObject->V30(c != 0);
    }
    space->FnC2E4E0();
}

// @ 0x00ee95a0
void OBJ174::AddEntry(LayoutRecord* e)
{
    void* planet = GetActivePlanet();
    PlanetRecord* rec = (PlanetRecord*)GetActivePlanetRecord();
    int idx = FUN_00ee7cb0(e->Fn1c(), 0, 0);
    if (idx == -1) return;

    Space* space = (Space*)GetSpacePtr();
    space->F33BF0();

    rec->mBc.erase(rec->mBc.mBegin + idx);
    {
        uint32_t* p = rec->mF8.mBegin + idx;
        uint32_t* q = p + 1;
        if (q < rec->mF8.mEnd) {
            eastl_move(p, q, (uint32_t)((uint8_t*)rec->mF8.mEnd - (uint8_t*)q));
        }
        rec->mF8.mEnd--;
    }
    {
        float* p = rec->m110.mBegin + idx;
        float* q = p + 1;
        if (q < rec->m110.mEnd) {
            eastl_move(p, q, (uint32_t)((uint8_t*)rec->m110.mEnd - (uint8_t*)q));
        }
        rec->m110.mEnd--;
    }
    ((EAThunk*)((EAThunk*)planet)->Fn414c0())->FnC2f80();
    ((EAThunk*)FUN_00b3d3b0())->Fn2bbe0();
    space->F34560();
    Update();
}

// @ 0x00ee9690
void OBJ174::SetEntry(LayoutRecord* e, EA::ResourceMan::Key_s00ee_8860* arg)
{
    void* planet = GetActivePlanet();
    PlanetRecord* rec = (PlanetRecord*)GetActivePlanetRecord();
    int a, b;
    int idx = FUN_00ee7cb0(e->Fn1c(), &a, &b);

    Space* space = (Space*)GetSpacePtr();
    space->F33BF0();

    if (idx == -1) {
        rec->mBc.push_back(*arg);
        if (rec->mF8.mEnd < rec->mF8.mCap) {
            *rec->mF8.mEnd++ = b;
        } else {
            rec->mF8.DoInsertValue(rec->mF8.mEnd, b);
        }
        if (rec->m110.mEnd < rec->m110.mCap) {
            *rec->m110.mEnd++ = 1.0f;
        } else {
            rec->m110.DoInsertValue(rec->m110.mEnd, 1.0f);
        }
    } else {
        rec->mBc.mBegin[idx] = *arg;
    }
    ((EAThunk*)((EAThunk*)planet)->Fn414c0())->FnC2f80();
    ((EAThunk*)FUN_00b3d3b0())->Fn2bbe0();
    space->F34560();
    Update();
}

// @ 0x00ee97f0
void OBJ174Ifc4::Fn(int* arg)
{
    if (*arg) {
        ((OBJ174*)((uint8_t*)this - 0x10))->SetEntry(m170, (EA::ResourceMan::Key_s00ee_8860*)arg);
    }
    if (m170) {
        LayoutRecord* e = m170;
        m170 = 0;
        e->Release();
    }
    GetTutorialsUI()->ClearPending();
}

// @ 0x00ee9840
uint8_t MsgHandler::Handle(IWindow_s00ee_9840* sender, Msg* msg)
{
    void* planet = GetActivePlanet();
    void* record = GetActivePlanetRecord();
    void* ctx = FUN_00b3d3b0();
    Space_s00ee_9840* space = *(Space_s00ee_9840**)(*(int*)0x16c7aa4 + 0x18);
    uint32_t type = msg->mType;
    uint8_t result = 0;

    switch (type) {
    case 0x1b:
    case 0x1c: {
        void* p = FUN_00ee7850(msg->mObj);
        if (p != 0) {
            ((Host*)((uint8_t*)this - 8))->Fn8460(p);
            return result;
        }
        break;
    }
    case 0x7a44749:
        if (msg->mId == 0x72bfdfd) {
            if (msg->mUnk14 != msg->mUnk10) {
                space->F34560();
                return 1;
            }
            space->F32410();
            return 1;
        }
        break;
    case 0x7a4489c:
        if (msg->mId == 0x72bfdfd) {
            space->F33BF0();
            return 1;
        }
        break;
    case 0x287259f6:
        switch (msg->mId) {
        case 0x73d54a0:
        case 0x4a1cb6d: {
            void* p = FUN_00ee7850(msg->mObj);
            ((Host*)((uint8_t*)this - 8))->Fn83A0(p);
            return result;
        }
        case 0x73272b0: {
            KillSetiEffects(0x13bed0aa, GetRecorderState_s00ee_9840());
            void* p = FUN_00ee7850(msg->mObj);
            ProfileVector vec;
            vec.Ctor(1);
            uint32_t a, b;
            uint32_t r = vcallRA<uint32_t, Obj, 0x1c>((Obj*)p, &b);
            (void)a;
            FUN_00ee7cb0(&a, &b, r);
            int n = ((SpeciesMgr*)GetSpeciesManager())
                        ->GetMatchingPlantProfiles(&vec, 1, FUN_00ee7810(msg));
            if (n == 1) {
                ((Host*)((uint8_t*)this - 8))->Fn9690(p, (char*)vec.mBegin + 0x504);
            }
            vec.Dtor();
            return result;
        }
        case 0x7b6b2cd: {
            IAudioSystem* at = GetSystemAT();
            uint32_t v = at ? at->GetCounter() : 0;
            KillSetiEffects(0x956eae88, (void*)v);
            void* p = FUN_00ee7850(msg->mObj);
            ((Host*)((uint8_t*)this - 8))->Fn95A0(p);
            return result;
        }
        case 0x16b1858d: {
            IWinButton* btn = InterfaceCast_IWinButton(sender);
            if (btn != 0) {
                KillSetiEffects(0xe76c9b4f, GetRecorderState_s00ee_9840());
                uint32_t v = btn->GetState();
                ((Host*)((uint8_t*)this - 8))->Fn8240((v >> 2) & 1);
            }
            break;
        }
        default:
            break;
        }
        {
            IAudioSystem* at = GetSystemAT();
            uint32_t v = at ? at->GetCounter() : 0;
            KillSetiEffects(0xe76c9b4f, (void*)v);
            ((Host*)((uint8_t*)this - 8))->Fn82C0(msg->mId);
            return result;
        }
    case 0xef00a884:
        if (msg->mId != 0x72bfdfd) break;
        if (msg->mObj != 0) {
            void* q = vcallRA<void*, Obj, 0x0c>((Obj*)msg->mObj, 0xf00a8a0);
            if (q != 0) {
                uint32_t n1 = vcallR<uint32_t, Obj, 0x20>((Obj*)q);
                uint32_t n2 = vcallR<uint32_t, Obj, 0x30>((Obj*)q);
                float f = (float)n1 / (float)n2;
                *(float*)((uint8_t*)record + 0x10c) = f;
                SetGlobalProperty(0xf04ff0cd, f);
                if ((uint8_t)FUN_00c70c00(planet)) {
                    void* x = FUN_008414c0(planet);
                    FUN_00c82f80(x);
                    FUN_00b2bbe0(ctx);
                }
            }
        }
        return 1;
    default:
        break;
    }
    return result;
}

// @ 0x00ee9be0
void Entry::Ctor()
{
    *(void* volatile*)((uint8_t*)this + 4) = (void*)0x13ec458;
    this->mRefCount = 0;
    this->mpVtbl = (void**)0x148acb8;
    this->mRefVtbl = (void*)0x148aca8;
    this->mOwner = 0;
    this->mWin0 = 0;
    this->mWinA = 0;
    this->mWinB = 0;
    this->mWinSlider = 0;
    this->mWinHandle = 0;
    this->mLayout = 0;
    this->mPoints = 0;
    this->mPressed = 0;
    this->mPos = 0.0f;
    _mm_store_ss(&this->mColor.r, _mm_load_ss((const float*)0x15ac834));
    _mm_store_ss(&this->mColor.g, _mm_load_ss((const float*)0x15ac838));
    _mm_store_ss(&this->mColor.b, _mm_load_ss((const float*)0x15ac83c));
    this->mUnk40 = 0;
    this->mUnk41 = 0;
    this->mAnchorX = 0.0f;
    this->mDragging = 0;
}

// @ 0x00ee9c70
void Entry::Dtor()
{
    *(void* volatile*)this = (void*)0x148acb8;
    *(void* volatile*)((uint8_t*)this + 4) = (void*)0x148aca8;
    IRefObj* pts = *(IRefObj* volatile*)&this->mPoints;
    if (pts != 0)  pts->Release();
    if (this->mLayout != 0)  ((cSPUILayout_s00ee_9840*)this->mLayout)->Release();
    if (this->mWinHandle != 0) ((IWindow_s00ee_9840*)this->mWinHandle)->Release();
    if (this->mWinSlider != 0) ((IWindow_s00ee_9840*)this->mWinSlider)->Release();
    if (this->mWinB != 0)      ((IWindow_s00ee_9840*)this->mWinB)->Release();
    if (this->mWinA != 0)      ((IWindow_s00ee_9840*)this->mWinA)->Release();
    if (this->mWin0 != 0)      ((IWindow_s00ee_9840*)this->mWin0)->Release();
    if (this->mOwner != 0)     ((IWindow_s00ee_9840*)this->mOwner)->Release();
    *(void* volatile*)this = (void*)0x13eb938;
    *(void* volatile*)((uint8_t*)this + 4) = (void*)0x13ec458;
}

// @ 0x00ee9d00
void Entry::SetVisible(uint8_t visible)
{
    if (this->mLayout == 0) return;
    IWindow_s00ee_9840* w0 = this->mWin0;
    if (w0 != 0) {
        if (visible) w0->Show(this);
        else         w0->Hide(this);
    }
    IWindow_s00ee_9840* wa = this->mWinA;
    if (wa != 0) {
        if (visible) {
            wa->Show(this);
            this->mWinA->Show(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
        } else {
            wa->Hide(this);
            this->mWinA->Hide(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
        }
    }
    IWindow_s00ee_9840* wb = this->mWinB;
    if (wb != 0) {
        if (visible) wb->Show(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
        else         wb->Hide(this->mPoints ? (uint8_t*)this->mPoints + 4 : 0);
    }
}

// @ 0x00ee9de0
void Entry::Update(void* a)
{
    (void)a;
    IRefObj* pts = this->mPoints;
    if (pts != 0) {
        IWindow_s00ee_9840* win0 = this->mWin0;
        if (win0 != 0) {
            int n = (int)((uint8_t*)pts->mEnd - (uint8_t*)pts->mBegin) & ~3;
            vcallAB<IWindow_s00ee_9840, 0x7c>(win0, 1, n > 4);
        }
    }
    IWindow_s00ee_9840* slider = this->mWinSlider;
    if (slider != 0) {
        slider->SetColor(this->mDragging ? 0x99ffffffu : 0xffffffffu);
    }
    IWindow_s00ee_9840* handle = this->mWinHandle;
    if (handle != 0) {
        vcallAB<IWindow_s00ee_9840, 0x7c>(handle, 1, this->mDragging == 0);
    }
}

// @ 0x00ee9e50
void Entry::Shutdown()
{
    vcallA<Entry, 0x28>(this, 0);
    if (this->mOwner != 0) {
        IWindow_s00ee_9840* p = this->mOwner;
        this->mOwner = 0;
        p->Release();
    }
    if (this->mLayout != 0) this->mLayout->Shutdown(1u);
}

// @ 0x00ee9e90
void Entry::SetRect(int a, RectF* pRect, uint8_t flag)
{
    (void)a;
    this->mGrabX = 0.0f;
    this->mGrabY = 0.0f;
    if (flag) {
        this->mGrabX = pRect->mX;
        this->mGrabY = pRect->mY;
    }
    if (this->mWinB != 0) this->mWinB->SetTextId(0x747d67c);
    if (this->mWinA != 0) this->mWinA->SetTextId(0x747d67c);
    if (this->mWinSlider != 0) {
        if (this->mWinSlider->GetHost() != 0) {
            IHost* h = this->mWinSlider->GetHost();
            vcallA<IHost, 0xe8>(h, this->mWinSlider);
        }
    }
}

// @ 0x00eea190
void Entry::SetColor(ColorRGB_s00ee_9840 color)
{
    ColorRGB_s00ee_9840* mc = &this->mColor;
    if (color.r != mc->r || color.g != mc->g || color.b != mc->b) {
        *mc = color;
        IMsgServer_s00ee_9840* ms = (IMsgServer_s00ee_9840*)MessageServer_s00ee_9840();
        ms->Send(0xd69290d7, 0, 0);
    }
    TutorialsUI_s00ee_9840* ui = *(TutorialsUI_s00ee_9840**)(*(int*)0x16c7aa4 + 0xd4);
    ui->ToggleHint(0x96, 0x97);
    cSPUILayout_s00ee_9840* lay = this->mLayout;
    uint32_t c = ColorRGBToU32(&this->mColor.r);
    IWindow_s00ee_9840* w = lay->FindWindowByID(0x7e099a4, 1);
    if (w != 0) w->SetColor(c);
}

// @ 0x00eea260
void Entry::NotifyChanged()
{
    if (this->mWinA == 0) return;
    void* p = EAAllocate(0x40, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (p == 0) return;
    void* msg = p;
    *(int*)((uint8_t*)msg + 0x30) = 0;
    *(void**)msg = (void*)0x13eb90c;
    _InterlockedExchange((volatile long*)((uint8_t*)msg + 4), 0);
    *(void* volatile*)msg = (void*)0x13eb844;
    *(int* volatile*)((uint8_t*)msg + 0x38) = 0;
    _ReadWriteBarrier();
    vcallv_vol<Obj, 4>((Obj*)msg);
    *(int*)((uint8_t*)msg + 0x30) = 0x7e19b84;
    ((RefMsg*)msg)->SetIRefCount(0, this->mWinA);
    IMsgServer_s00ee_9840* ms = (IMsgServer_s00ee_9840*)MessageServer_s00ee_9840();
    ms->Send((uint32_t)*(int*)((uint8_t*)msg + 0x30), msg, 0);
    vcallv_vol<Obj, 8>((Obj*)msg);
}

// @ 0x00eea2f0
void Entry::OnClick(int a, int b)
{
    (void)a; (void)b;
    if (this->mWinB != 0) this->mWinB->SetTextId(0x747d67b);
    if (this->mWinA != 0) this->mWinA->SetTextId(0x747d67b);
    if (this->mDragging != 0) {
        this->mPressed = 1;
    } else {
        NotifyChanged();
        if (this->mWinA != 0) {
            void* q = this->mWinA->AsInterface(0x8ed27e7a);
            if (q != 0) vcallAB<Obj, 0x28>((Obj*)q, 4, 1);
        }
    }
    IAudioSystem* at = GetSystemAT();
    uint32_t v = at ? at->GetCounter() : 0;
    IAudioSystem* at2 = GetSystemAT();
    if (at2 != 0) {
        at2->F38(0x3475365);
        at2->F40(0x3475381, 0xe76c9b4f);
        at2->F40(0x3475385, v);
        at2->F58();
    }
}

// @ 0x00eea3c0
uint8_t Entry::Init(IWindow_s00ee_9840* pOwner, float pos, float r, float g, float b, IRefObj* pPoints)
{
    if (pOwner != this->mOwner) {
        if (pOwner != 0) pOwner->AddRef();
        IWindow_s00ee_9840* old = this->mOwner;
        this->mOwner = pOwner;
        if (old != 0) old->Release();
    }
    if (pPoints != this->mPoints) {
        if (pPoints != 0) pPoints->AddRef();
        IRefObj* oldp = this->mPoints;
        this->mPoints = pPoints;
        if (oldp != 0) oldp->Release();
    }
    this->mColor.r = r;
    this->mColor.g = g;
    this->mPressed = 0;
    this->mPos = pos;
    this->mColor.b = b;

    if (this->mOwner != 0) {
        void* p = EAAllocate(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
        cSPUILayout_s00ee_9840* lay = p ? ((cSPUILayout_s00ee_9840*)p)->Ctor() : 0;
        if (lay != this->mLayout) {
            if (lay != 0) lay->AddRef();
            cSPUILayout_s00ee_9840* oldl = this->mLayout;
            this->mLayout = lay;
            if (oldl != 0) oldl->Release();
        }
        if (!this->mLayout->Init((const void*)0x15ac864, 0, 0x5b598fa)) {
            this->mLayout->Shutdown(1u);
            if (this->mLayout != 0) {
                cSPUILayout_s00ee_9840* q = this->mLayout;
                this->mLayout = 0;
                q->Release();
            }
            return 0;
        }
        this->mLayout->SetParentWin(this->mOwner, 1, 0x5b598fa);

        IWindow_s00ee_9840* t;
        t = this->mLayout->FindWindowByID(0x568ed1c3, 1);
        if (t != this->mWinSlider) {
            if (t != 0) t->AddRef();
            IWindow_s00ee_9840* old = this->mWinSlider;
            this->mWinSlider = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0xf68ed165, 1);
        if (t != this->mWin0) {
            if (t != 0) t->AddRef();
            IWindow_s00ee_9840* old = this->mWin0;
            this->mWin0 = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0x7e099a3, 1);
        if (t != this->mWinA) {
            if (t != 0) t->AddRef();
            IWindow_s00ee_9840* old = this->mWinA;
            this->mWinA = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0xf68ed164, 1);
        if (t != this->mWinB) {
            if (t != 0) t->AddRef();
            IWindow_s00ee_9840* old = this->mWinB;
            this->mWinB = t;
            if (old != 0) old->Release();
        }
        t = this->mLayout->FindWindowByID(0x7e1e057, 1);
        if (t != this->mWinHandle) {
            if (t != 0) t->AddRef();
            IWindow_s00ee_9840* old = this->mWinHandle;
            this->mWinHandle = t;
            if (old != 0) old->Release();
        }

        if (this->mWinB != 0) this->mWinB->SetTextId(0x747d67b);
        if (this->mWinA != 0) this->mWinA->SetTextId(0x747d67b);

        uint32_t c = ColorRGBToU32(&this->mColor.r);
        IWindow_s00ee_9840* w = this->mLayout->FindWindowByID(0x7e099a4, 1);
        if (w != 0) w->SetColor(c);
    }

    if (this->mOwner != 0 && this->mWinSlider != 0) {
        float* sb = this->mWinSlider->GetBox();
        float hSlider = sb[3] - sb[1];
        float* ob = this->mOwner->GetBox();
        float hOwner = ob[3] - ob[1];
        float* sb2 = this->mWinSlider->GetBox();
        this->mWinSlider->SetPos2(sb2[0], (hOwner - hSlider) * this->mPos);
        this->mAnchorX = this->mWinSlider->GetBox()[0];
    }
    NotifyChanged();
    return 1;
}

// @ 0x00eea6d0
uint8_t Entry::DoMessage(uint32_t msgId, Msg* msg)
{
    (void)msgId;
    if (msg->mType != 0x287259f6) return 0;
    if (msg->mId == 0xf68ed165) {
        int n = (int)((uint8_t*)((IRefObj*)this->mPoints)->mEnd -
                      (uint8_t*)((IRefObj*)this->mPoints)->mBegin) & ~3;
        if (n > 4) {
            IAudioSystem* at = GetSystemAT();
            uint32_t v = at ? at->GetCounter() : 0;
            KillSetiEffects(0xe76c9b4f, (void*)v);
            IMsgServer_s00ee_9840* ms = (IMsgServer_s00ee_9840*)MessageServer_s00ee_9840();
            ms->Send(0x7e1ea71, 0, 0);
            this->mPressed = 1;
        }
        return 1;
    }
    if (msg->mId == 0x7e099a3) {
        NotifyChanged();
    }
    return 0;
}

// @ 0x00eea760
int Entry_PosGreater(Entry* a, Entry* b)
{
    return b->mPos > a->mPos;
}

// @ 0x00eea780
void* RefCountPart::QueryInterface(uint32_t id)
{
    switch (id) {
    case 0x968dcff4:
        return (uint8_t*)this - 4;
    case 0xee3f516e:
    case 0x2f009dd0:
        return ((uint8_t*)this - 4) != 0 ? (void*)this : 0;
    default:
        return 0;
    }
}

// @ 0x00eea7c0
void View::ShowChildren(uint8_t visible)
{
    if (this->mLayout != 0) {
        IWindow_s00ee_a7c0* w = this->mLayout->FindWindowByID(0xf68ddb49, 1);
        if (w != 0) {
            if (visible) w->Show((uint8_t*)this + 4);
            else         w->Hide((uint8_t*)this + 4);
        }
        IWindow_s00ee_a7c0* wb = this->mWinB;
        if (wb != 0) {
            if (visible) wb->Show((uint8_t*)this + 4);
            else         wb->Hide((uint8_t*)this + 4);
        }
        IWindow_s00ee_a7c0* av = (IWindow_s00ee_a7c0*)this->mAssetView;
        if (av != 0) {
            if (visible) av->Show((uint8_t*)this + 4);
            else         av->Hide((uint8_t*)this + 4);
        }
    }
    Entry_s00ee_a7c0** it = this->mEntriesBegin;
    while (it != this->mEntriesEnd) {
        Entry_s00ee_a7c0* e = *it;
        vcallA<Entry_s00ee_a7c0, 0x28>(e, visible);
        ++it;
    }
}

// @ 0x00eea860
void View::OnAssetChanged(void* pChanged)
{
    Entry_s00ee_a7c0** it = this->mEntriesBegin;
    if (it != this->mEntriesEnd) {
        do {
            IWinObj* v = (IWinObj*)(*it)->mWinA;
            if (v != 0 && (void*)v != pChanged) {
                IWinObj* q = (IWinObj*)v->AsInterface(0x8ed27e7a);
                if (q != 0) {
                    q->Cmd(4, 0);
                }
            }
            ++it;
        } while (it != this->mEntriesEnd);
    }
}

// @ 0x00eea8b0
Entry_s00ee_a7c0* View::FindByWinID(void* id)
{
    Entry_s00ee_a7c0** it = this->mEntriesBegin;
    Entry_s00ee_a7c0** end = this->mEntriesEnd;
    while (it != end) {
        Entry_s00ee_a7c0* e = *it;
        if (e->mWinB == id) return e;
        if (e->mWinA == id) return e;
        ++it;
    }
    return 0;
}

// @ 0x00eea8e0
uint8_t View::HasWin(void* id)
{
    Entry_s00ee_a7c0** it = this->mEntriesBegin;
    Entry_s00ee_a7c0** end = this->mEntriesEnd;
    while (it != end) {
        if ((*it)->mWinA == id) return 1;
        ++it;
    }
    return 0;
}

// @ 0x00eea910
void View::SetEntryColor(void* id, float r, float g, float b)
{
    Entry_s00ee_a7c0** it = this->mEntriesBegin;
    Entry_s00ee_a7c0** end = this->mEntriesEnd;
    while (it != end) {
        Entry_s00ee_a7c0* e = *it;
        if (e->mWinA == id) {
            e->SetColor(r, g, b);
            return;
        }
        ++it;
    }
}

// @ 0x00eeaa40
uint8_t View::DoMessage(uint32_t msgId, void* msg)
{
    switch (msgId) {
    case 0x7e19b84: {
        void* p = *(void**)((uint8_t*)msg + 8);
        if (p != 0) {
            OnAssetChanged(p);
        }
        break;
    }
    case 0xd69290d7:
    case 0xd69290d8:
        {
            IWindow_s00ee_a7c0* w = this->mWinB;
            if (w != 0) {
                w->V90();
            }
        }
        break;
    }
    return 0;
}

// @ 0x00eeaa90
void View::GetEntryColor(float* pOut, void* id)
{
    Entry_s00ee_a7c0** it = this->mEntriesBegin;
    Entry_s00ee_a7c0** end = this->mEntriesEnd;
    while (it != end) {
        Entry_s00ee_a7c0* e = *it;
        if (e->mWinA == id) {
            pOut[0] = e->mColorR;
            pOut[1] = e->mColorG;
            pOut[2] = e->mColorB;
            return;
        }
        ++it;
    }
    *(Vec3*)pOut = *(Vec3*)0x15ac870;
}

// @ 0x00eeab00
void* View::Ctor()
{
    View* p = this;
    p->mpVtbl1 = (void*)0x14426a0;   // base cSPScenarioModeSporepediaLargeAssetView
    p->mpVtbl2 = (void*)0x13ec458;   // RefCountVTemplate<int>
    p->mUnk0c = 0;
    p->mpVtbl0 = (void**)0x148ad1c;
    p->mpVtbl1 = (void*)0x148ad00;
    p->mpVtbl2 = (void*)0x148acf0;
    p->mWinParent = 0;
    p->mAssetView = 0;
    p->mWinB = 0;
    p->mWinRenderWindow = 0;
    p->mWinBakingIndicator = 0;
    p->mLayout = 0;
    p->mMsgServer = 0;
    p->mMsgTarget = 0;
    p->mMsgIds = 0;
    p->mMsgCount = 0;
    p->mMsgUser = 0;
    p->mEntriesBegin = 0;
    p->mEntriesEnd = 0;
    p->mEntriesCap = 0;
    p->mLayout2 = 0;
    p->mUnk54 = 0.0f;
    p->mUnk58 = 0.0f;
    return p;
}

// @ 0x00eeab90
void View::SampleColor(float* pOut, float x)
{
    if ((((int)this->mEntriesEnd - (int)this->mEntriesBegin) >> 2) == 0) {
        pOut[0] = *(float*)0x16c78a8;
        pOut[1] = *(float*)0x16c78ac;
        pOut[2] = *(float*)0x16c78b0;
        return;
    }
    Entry_s00ee_a7c0** begin = this->mEntriesBegin;
    int nbytes = (int)this->mEntriesEnd - (int)begin;
    int i = 0;
    if ((int)(nbytes & 0xfffffffc) > 0) {
        do {
            Entry_s00ee_a7c0* e = begin[i];
            if (e->mPos > x) {
                if (i == 0) {
                    Entry_s00ee_a7c0* f = begin[0];
                    pOut[0] = f->mColorR;
                    pOut[1] = f->mColorG;
                    pOut[2] = f->mColorB;
                    return;
                }
                Entry_s00ee_a7c0* lo = begin[i - 1];
                Entry_s00ee_a7c0* hi = begin[i];
                float t = (x - lo->mPos) / (hi->mPos - lo->mPos);
                pOut[0] = (hi->mColorR - lo->mColorR) * t + lo->mColorR;
                pOut[1] = (hi->mColorG - lo->mColorG) * t + lo->mColorG;
                pOut[2] = (hi->mColorB - lo->mColorB) * t + lo->mColorB;
                return;
            }
            ++i;
        } while (i < (((int)this->mEntriesEnd - (int)begin) >> 2));
    }
    Entry_s00ee_a7c0* e = begin[(((int)this->mEntriesEnd - (int)begin) >> 2) - 1];
    pOut[0] = e->mColorR;
    pOut[1] = e->mColorG;
    pOut[2] = e->mColorB;
}

// @ 0x00eeaf00
void View::Rebuild(uint8_t notify)
{
    bool added = false;
    Entry_s00ee_a7c0** begin = this->mEntriesBegin;
    Entry_s00ee_a7c0** end = this->mEntriesEnd;
    int nbytes = (int)end - (int)begin;
    float x = 0.0f;
    float colR, colG, colB;

    if ((nbytes & 0xfffffffc) == 0) {
        colR = kDefR; colG = kDefG; colB = kDefB;
    } else if ((nbytes & 0xfffffffc) == 4) {
        Entry_s00ee_a7c0* e = begin[0];
        x = (e->mPos < kHalf) ? kOne : kZero;
        if (notify) {
            colR = e->mColorR; colG = e->mColorG; colB = e->mColorB;
        } else {
            uint32_t c = 0xffebd870;
            float* v = ColorToVector3(&colR, c);
            colR = v[0]; colG = v[1]; colB = v[2];
        }
        added = true;
    } else {
        float best = 0.0f;
        int bestIdx = 0;
        int cnt = (((int)this->mEntriesEnd - (int)begin) >> 2);
        for (int i = 0; i <= cnt; ++i) {
            float hi = (i < cnt) ? begin[i]->mPos : kOne;
            float lo = (i > 0) ? begin[i - 1]->mPos : 0.0f;
            float d = hi - lo;
            if (d > best) { best = d; bestIdx = i; }
        }
        if (bestIdx == 0) {
            Entry_s00ee_a7c0* e = begin[1];
            colR = e->mColorR; colG = e->mColorG; colB = e->mColorB;
        } else if (bestIdx == cnt) {
            Entry_s00ee_a7c0* e = begin[cnt - 1];
            x = kOne;
            colR = e->mColorR; colG = e->mColorG; colB = e->mColorB;
        } else {
            Entry_s00ee_a7c0* lo = begin[bestIdx - 1];
            Entry_s00ee_a7c0* hi = begin[bestIdx];
            x = best * kHalf + lo->mPos;
            colR = (hi->mColorR - lo->mColorR) * kHalf + lo->mColorR;
            colG = (hi->mColorG - lo->mColorG) * kHalf + lo->mColorG;
            colB = (hi->mColorB - lo->mColorB) * kHalf + lo->mColorB;
        }
        added = true;
    }

    if (x < kZero || x > kOne) return;

    Entry_s00ee_a7c0* pEntry = 0;
    void* p = EAAllocate(0x54, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (p != 0) pEntry = ((Entry_s00ee_a7c0*)p)->Ctor();

    ((void (__thiscall *)(Entry_s00ee_a7c0*, void*, float, float, float, float, View*))((*(void***)pEntry)[0x1c / 4]))
        (pEntry, this->mAssetView, x, colR, colG, colB, this);
    ((void (__thiscall *)(Entry_s00ee_a7c0*, int))((*(void***)pEntry)[0x28 / 4]))(pEntry, 1);
    EntryPtr tmp = pEntry;
    ((void (__thiscall *)(Entry_s00ee_a7c0*))((*(void***)pEntry)[0]))(pEntry);

    if (this->mEntriesEnd < this->mEntriesCap) {
        Entry_s00ee_a7c0** slot = this->mEntriesEnd;
        this->mEntriesEnd = slot + 1;
        if (slot != 0) {
            *slot = pEntry;
            ((void (__thiscall *)(Entry_s00ee_a7c0*))((*(void***)pEntry)[0]))(pEntry);
        }
    } else {
        ((void (__thiscall *)(void*, void*, void**))FUN_00aea5d0)
            ((void*)&this->mEntriesBegin, this->mEntriesEnd, (void**)&tmp);
        pEntry = tmp;
    }
    ((void (__thiscall *)(Entry_s00ee_a7c0*))((*(void***)pEntry)[4 / 4]))(pEntry);

    if (added) {
        ((void (__thiscall *)(Entry_s00ee_a7c0*))NotifyEntryChanged)(pEntry);
    }
    if (notify) {
        void* ms = MessageServer_s00ee_a7c0();
        ((void (__thiscall *)(void*, uint32_t, void*, void*))(((void**)*(void***)ms)[0x14 / 4]))(ms, 0xd69290d7, 0, 0);
    }
}

// @ 0x00eeb580
void View::SetPoints(int* pPositions, int* pColors)
{
    int n = (pPositions[1] - pPositions[0]) >> 2;
    int m = (pColors[1] - pColors[0]) / 0xc;
    if (n != m || n == 0) return;

    Entry_s00ee_a7c0** it = this->mEntriesBegin;
    Entry_s00ee_a7c0** end = this->mEntriesEnd;
    while (it != end) {
        vcallv<Entry_s00ee_a7c0, 0x20>(*it);
        ++it;
    }
    ((void (__thiscall *)(void*, void*, void*))FUN_00e25bd0)
        ((void*)&this->mEntriesBegin, this->mEntriesBegin, this->mEntriesEnd);

    for (int i = 0; i < n; ++i) {
        Entry_s00ee_a7c0* pEntry;
        void* p = EAAllocate(0x54, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (p != 0) pEntry = ((Entry_s00ee_a7c0*)p)->Ctor(); else pEntry = 0;

        float* col = (float*)(pColors[0] + i * 0xc);
        float x = ((float*)pPositions[0])[i];
        ((void (__thiscall *)(Entry_s00ee_a7c0*, void*, float, float, float, float, View*))((*(void***)pEntry)[0x1c / 4]))
            (pEntry, this->mAssetView, x, col[0], col[1], col[2], this);
        ((void (__thiscall *)(Entry_s00ee_a7c0*, int))((*(void***)pEntry)[0x28 / 4]))(pEntry, 1);
        ((void (__thiscall *)(Entry_s00ee_a7c0*))((*(void***)pEntry)[0]))(pEntry);

        if (this->mEntriesEnd < this->mEntriesCap) {
            *this->mEntriesEnd = pEntry;
            ++this->mEntriesEnd;
            ((void (__thiscall *)(Entry_s00ee_a7c0*))((*(void***)pEntry)[0]))(pEntry);
        } else {
            EntryPtr tmp = pEntry;
            ((void (__thiscall *)(void*, void*, void**))FUN_00aea5d0)
                ((void*)&this->mEntriesBegin, this->mEntriesEnd, (void**)&tmp);
            pEntry = tmp;
        }
        ((void (__thiscall *)(Entry_s00ee_a7c0*))((*(void***)pEntry)[4 / 4]))(pEntry);
    }

    Entry_s00ee_a7c0** b = this->mEntriesBegin;
    Entry_s00ee_a7c0** e = this->mEntriesEnd;
    if (b != e) {
        int cnt = (int)(e - b);
        int depth = 0;
        for (int k = cnt; k != 0; k >>= 1) ++depth;
        FUN_00e26410(b, e, depth * 2 - 2, 0xeea760);
        if (cnt <= 0x1c) {
            FUN_00bbe970(b, e);
        } else {
            FUN_00bbe970(b, (void*)((uint8_t*)b + 0x70));
            FUN_00b90a40((void*)((uint8_t*)b + 0x70), e);
        }
    }

    if (this->mWinB != 0) {
        this->mWinB->V90();
    }
}

// @ 0x00eeb770
void __fastcall f_00eeb770(CCList* c, int dummy, int param_2, char param_3)
{
    (void)dummy;
    if (c->begin != c->end) {
        ListEntry** it = c->begin;
        do {
            ListEntry* e = *it;
            ListEntry* tmp = e;
            e->v24(param_2);
            if (e->flag == 0) {
                ++it;
            } else {
                e->v20();
                ListEntry** p = c->begin;
                while (p != c->end) {
                    if (*p == e) {
                        p = FUN_00b6f4f0(p + 1, c->end, p, &tmp);
                        break;
                    }
                    ++p;
                }
                if (p + 1 < c->end)
                    FUN_006782c0(p + 1, c->end, p);
                c->end = c->end - 1;
                ListEntry* last = *c->end;
                if (last != 0)
                    last->v04();
                AudioObj* a = GetSystemAT_s00ee_b770();
                int u = 0;
                if (a != 0)
                    u = a->v20();
                AudioObj* b = GetSystemAT_s00ee_b770();
                if (b != 0) {
                    b->v38(0x03475365);
                    b->v40(0x03475381, 0x956eae88);
                    b->v40(0x03475385, (unsigned)u);
                    b->v58();
                }
                if (param_3 != 0) {
                    MsgObj* m = GetMsgServer();
                    m->v14(0xd69290d7, 0, 0);
                }
            }
        } while (it != c->end);
    }
    FUN_00e26de0((void**)c->begin, (void**)c->end, (void*)0x00eea760);
    if (c->layout != 0 && c->layout->FindWindowByID(0xf68ddb49u, 1) != 0) {
        unsigned n = (unsigned)(c->end - c->begin);
        VtObj32* w = (VtObj32*)c->layout->FindWindowByID(0xf68ddb49u, 1);
        if (w != 0)
            w->v7c(2, n < 0x19);
    }
    if (c->f14 != 0) {
        unsigned n = (unsigned)(c->end - c->begin);
        c->f14->v78(n < 0x19 ? 0x07e4330b : 0x07e4330c);
    }
}

// @ 0x00eeb920
void __fastcall f_00eeb920(CCList* c, int dummy, FloatVec* out1, Vec3Vec* out2)
{
    (void)dummy;
    if (out1 == 0 || out2 == 0)
        return;

    FUN_00e26de0((void**)c->begin, (void**)c->end, (void*)0x00eea760);

    {
        float* b = out1->begin;
        float* e = out1->end;
        volatile int zero = 0;
        memcpy(b, e, (size_t)zero);                    // inlined erase keeps the zero-size copy
        int d = ((int)((char*)e - (char*)b) >> 2) << 2;
        out1->end = (float*)((char*)e - d);            // erase(begin, end)
    }
    {
        char* b = (char*)out2->begin;
        char* e = (char*)out2->end;
        int d = (int)(e - b) / 12 * 12;
        out2->end = (Vec3*)(e - d);                   // erase(begin, end)
    }

    ListEntry** it = c->begin;
    while (it != c->end) {
        ListEntry* e = *it;
        float v = *(float*)((char*)e + 0x30);
        if (out1->end < out1->cap) {
            float* d = out1->end;
            out1->end = d + 1;
            if (d != 0)
                *d = v;
        } else {
            FUN_00455660(out1->end, &v);
        }
        Vec3 v3;
        v3.x = *(float*)((char*)e + 0x34);
        v3.y = *(float*)((char*)e + 0x38);
        v3.z = *(float*)((char*)e + 0x3c);
        if (out2->end < out2->cap) {
            Vec3* d = out2->end;
            out2->end = d + 1;
            if (d != 0) {
                d->x = v3.x; d->y = v3.y; d->z = v3.z;
            }
        } else {
            FUN_004b5ad0(out2->end, &v3);
        }
        ++it;
    }
}

// @ 0x00eebf80
int __cdecl f_00eebf80(XGet* p)
{
    if (p == 0)
        return 0;
    return p->Get18();
}

// @ 0x00eebf90
void __cdecl f_00eebf90(int p1, int p2)
{
    FUN_005bf860((void*)p1, p2);
    FUN_005bf120((void*)(p1 + 8), (void*)p1, 0, 0);
}

// @ 0x00eebfc0
bool __cdecl f_00eebfc0(int param_1, int* param_2)
{
    bool found = false;
    int cnt;
    void* data;
    if (FUN_006a0ae0((void*)param_1, g_016c7a58, &cnt, &data)) {
        int n = cnt;
        int* p = (int*)data;
        for (int i = 0; i < n; i++) {
            if (found)
                break;
            if (p[0] == param_2[0] && p[1] == param_2[1] && p[2] == param_2[2])
                found = true;
            else
                found = false;
            p += 3;
        }
    }
    return found;
}

// @ 0x00eec0d0
void __cdecl f_00eec0d0(int p)
{
    Manager_s00ee_b770* m = g_16c7aa4_s00ee_b770->f74;
    m->FUN_00f3d780(p);
}

// @ 0x00eec0f0
#pragma float_control(precise, off)
float __cdecl f_00eec0f0(float* dir, char a2, int* out, char a4)
{
    PlanetObj* pm = SP_PlanetModel();

    if (a2 == 0) {
        *out = 2;
        return pm->GetRadiusAt(dir);
    }

    Vec3 pos;
    pm->DirectionToSurfacePosition(&pos.x, dir);

    float dist = 0.0f;
    float flag = 0.0f;
    float f1 = pos.z * pos.z + (pos.x * pos.x + pos.y * pos.y);
    float f2 = (float)sqrt((double)f1);

    Vec3 v;
    if (a4 == 0) {
        v.x = dir[0];
        v.y = dir[1];
        v.z = dir[2];
        flag = g_13ec478;
        dist = f2 - (float)sqrt((double)(v.x * v.x + (dir[1] * dir[1] + dir[2] * dir[2])));
    } else {
        v.x = pos.x;
        v.y = pos.y;
        v.z = pos.z;
        float r = pm->FUN_00b7e500();
        dist = 0.0f;
        flag = r - f2;
    }

    RayHitResult res;
    res.rz[0] = res.rz[1] = res.rz[2] = res.rz[3] = 0;
    FUN_00b65b10(&v.x, g_0167ecd0, 0, 1, 6, &res);
    if (res.hit != 0) {
        float f3 = (res.py * res.py + res.pz * res.pz) + res.px * res.px;
        if (f1 < f3) {
            *out = res.hit;
            return (float)sqrt((double)f3);
        }
    }
    *out = 2;
    return f2;
}

// @ 0x00eec2b0
void __cdecl f_00eec2b0(float* out, float* dir, int a3, int* flag, int a5)
{
    float h = f_00eec0f0(dir, (char)a3, flag, (char)a5);
    PlanetObj* pm = SP_PlanetModel();
    float wh = pm->GetWaterHeight();
    float hh;
    if (wh > h) {
        *flag = 4;
        hh = wh;
    } else {
        hh = h;
    }
    float x = dir[0];
    float inv = (float)(1.0 / sqrt((double)x * x + (double)dir[1] * dir[1] + (double)dir[2] * dir[2]));
    float xi = (float)(x * inv);
    float yi = (float)(dir[1] * inv);
    float zi = (float)(dir[2] * inv);
    out[0] = (float)(xi * hh);
    out[1] = (float)(yi * hh);
    out[2] = (float)(zi * hh);
}

// @ 0x00eec370
#pragma float_control(precise, off)
float __cdecl f_00eec370(float* dir, int a2, int a3)
{
    float local[3];
    f_00eec2b0(local, dir, a2, (int*)a3, 1);
    float d1 = (float)sqrt((double)(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]));
    float s = (local[0] * local[0] + local[1] * local[1]) + local[2] * local[2];
    return d1 - (float)sqrt((double)s);
}

// @ 0x00eec3d0
Vec3i __cdecl f_00eec3d0(int* in)
{
    Vec3i out;
    out.x = 0; out.y = 0; out.z = 0;
    if (in != 0) {
        if (*in == -2) {
            Vec3i* p = (Vec3i*)g_16c7aa4_s00ee_b770->f74->FUN_00f3bcb0();
            out.x = p->x; out.y = p->y; out.z = p->z;
            return out;
        }
        Vec3i* p = (Vec3i*)g_16c7aa4_s00ee_b770->f74->FUN_00f3e8a0(*in);
        if (p != 0) {
            out.x = p->x; out.y = p->y; out.z = p->z;
        }
    }
    return out;
}

// @ 0x00eec440
void __cdecl f_00eec440(int* param_1)
{
    void* a = g_16c7aa4_s00ee_b770->f74->FUN_00f3d780((int)param_1);
    if (a == 0)
        return;
    PhysObj* obj = (PhysObj*)a;
    if (obj->QueryInterface(0x01186577) == 0)
        return;
    void* body = g_16c7aa4_s00ee_b770->f74->FUN_00f3e8a0(*param_1);
    if (body == 0)
        return;
    if (!((BodyObj*)body)->FUN_00f25680())
        return;
    int r = obj->vB8(0x0137e8e0);
    if (r == 0)
        return;

    float tmp[2];
    ((SurfObj*)(void*)r)->FUN_00c9ff40((float*)param_1 + 1, &tmp[0], &tmp[1]);
    float norm[3];
    float* dir = (float*)SP_normalized_safe(norm, (float*)param_1 + 1);
    float scale = tmp[0];
    float sx = dir[0] * scale;
    float sy = dir[1] * scale;
    float sz = dir[2] * scale;
    ((float*)param_1)[1] = sx;
    ((float*)param_1)[2] = sy;
    ((float*)param_1)[3] = sz;
    ((float*)param_1)[0x88] = tmp[1];
}

// @ 0x00eec540
void __cdecl f_00eec540(int p)
{
    int n = g_016c7a28;
    for (int i = 0; i < n; ++i) {
        if (g_016c7a24[i] > p)
            break;
    }
}

// @ 0x00eec580
int __cdecl f_00eec580(int p)
{
    if (p <= 0)
        return 0;
    int n = g_016c7a28;
    while (p > n) {
        p = n;
        if (p <= 0)
            return 0;
    }
    return g_016c7a24[p - 1];
}

// @ 0x00eed3f0
float __cdecl f00eed3f0(cNoun* key, float value, char flagA, char flagB, float* out)
{
    float lo = g_1485720;
    float hi = g_1485720;

    switch (key->mTypeID) {
    case 0x24682294:
    case 0x476a98c7:
        lo = g_16c79a4;
        hi = g_16c79b4;
        break;
    case 0x2399be55:
        lo = g_16c79d4;
        hi = g_16c79e4;
        break;
    case 0xb1b104: {
        ResourceKey_s00ee_d3f0 k;
        FUN_00eeca60(&k, key);
        switch (k.mTypeID) {
        case 0x2a8fb3f:
        case 0x3a2511e: {
            cPropertyOwner* n = (cPropertyOwner*)FUN_00b3d300()->FUN_00b21000(k.mTypeID, k.mInstanceID);
            if (n != 0) {
                GetPropertyT(n->mPropList, 0x7611549, &lo);
                GetPropertyT(n->mPropList, 0x761154f, &hi);
            }
            break;
        }
        case 0x74e0069:
        case 0x7b38ba7: {
            IntrusivePtr<IPropList> list;
            PropMgr* pm = FUN_0067de30();
            if (pm->GetPropertyList(key->mInstanceID, key->mGroupID, &list)) {
                GetPropertyT(list, 0x7611549, &lo);
                GetPropertyT(list, 0x761154f, &hi);
            }
            break;
        }
        }
        break;
    }
    case 0x2b978c46:
        if (flagB) {
            lo = g_16c7954;
            hi = g_16c7964;
        } else if (flagA) {
            if (value < g_16c7944) {
                lo = g_16c7934;
                hi = g_16c7944;
            } else if (value < g_16c7964) {
                lo = g_16c7954;
                hi = g_16c7964;
            } else {
                lo = g_16c7974;
                hi = g_16c7984;
            }
        } else {
            if (value > g_16c7974) {
                lo = g_16c7974;
                hi = g_16c7984;
            } else if (value > g_16c7954) {
                lo = g_16c7954;
                hi = g_16c7964;
            } else {
                lo = g_16c7934;
                hi = g_16c7944;
            }
        }
        break;
    }

    float clamped = value;
    clamped = std::min(std::max(clamped, lo), hi);

    float v = FUN_00eed280(key, 0);
    if (out != 0) {
        if (clamped < v) {
            *out = ((value - lo) / ((v - lo) + 1.5258789e-05f)) * 0.5f;
            return clamped;
        }
        *out = ((value - v) / ((hi - v) + 1.5258789e-05f)) * 0.5f + 0.5f;
    }
    return clamped;
}

// @ 0x00eed720
void __cdecl f00eed720(cNoun* noun, SpinOwner* owner, SpinOut* out)
{
    char cVar1 = DAT_015acb40;
    Mgr* mgr = DAT_016c7aa4_s00ee_d3f0->mManager;
    int  uVar8;
    bool bVar9;
    int  state = 1;

    if (noun != mgr->fn3f00()) {
        cNoun* asset = mgr->fn3e8a0(noun->mInstanceID);
        if (FUN_00eece20_s00ee_d3f0(asset) != 0xe34e8a60) {
            if (owner->mField71 == 0) {
                uVar8 = 1;
                bVar9 = true;
            } else {
                uVar8 = 0;
                bVar9 = false;
            }
            PropRef38* prop = (PropRef38*)VC1(owner, 0xb8, 0x175cdc9);
            if (prop != 0 && prop->mType == 9)
                bVar9 = true;
            state = asset->fn255d0() == 0;
            if (asset != 0 && asset->fn25680()) {
                uVar8 = 0;
                bVar9 = false;
                if (asset->fn256e0())
                    state = 0;
                else if (asset->fn256a0())
                    state = 3;
            }
        } else {
            uVar8 = 0;
            bVar9 = true;
        }
    } else {
        uVar8 = 0;
        bVar9 = true;
    }

    out->mFlags |= 2;
    if (cVar1)
        out->mFlags |= 0x10;
    else
        out->mFlags &= ~0x10u;
    out->mField04 = uVar8;
    out->mState = state;
    out->mValue = noun->mField220;
    out->mFlags2 = 0;
    if (bVar9)
        out->mFlags2 |= 0x10;
    else
        out->mFlags2 &= ~0x10u;
    out->mFlags2 &= ~4u;
    out->mFlags2 |= 2;
}

// @ 0x00eed840
bool __cdecl f00eed840(int param)
{
    int* local = 0;
    int out;
    bool ok;
    if (!FUN_005bf0e0(param, &local))
        goto fail;
    if (local == 0)
        goto fail;
    if (!((char(__thiscall*)(void*,int,int*))VTP(local)[0x24 / 4])(local, 0x5888ef41, &out))
        goto fail;
    if (*(short*)(out + 0x12) != 9)
        goto fail;
    if (*((Prop*)out)->GetInt() == DAT_016c7a28)
        ok = true;
    else
        goto fail;
    goto done;
fail:
    ok = false;
done:
    if (local != 0)
        ((RefObj*)local)->Release();
    return ok;
}

// @ 0x00eed8c0
int __cdecl f00eed8c0(const ResourceKey_s00ee_d3f0* key)
{
    int result = DAT_016c7a38;
    IRefObj_s00ee_d3f0* bag = 0;
    cPollinatorLookup* lookup = FUN_0067cb30()->mLookup;
    if (lookup->LookupByKey(key, &bag, false))
        ((cPropertyBag*)bag)->GetInt32(0x5bd7a6a4, &result);
    int value = result;
    if (bag != 0)
        bag->Release();
    return value;
}

// @ 0x00eed920
bool __cdecl f00eed920(int param1, int param2)
{
    int* local = 0;
    bool ok = FUN_005bf0e0(param1, &local) && FUN_005bf7c0(local, param2);
    if (local != 0)
        VC0(local, 4);
    return ok;
}

// @ 0x00eed970
bool __cdecl f00eed970(int param1, int param2)
{
    int* local = 0;
    bool ok = FUN_005bf0e0(param1, &local) && FUN_00eebfc0(local, param2);
    if (local != 0)
        VC0(local, 4);
    return ok;
}

// @ 0x00eed9c0
bool __cdecl f00eed9c0(int param1, int param2)
{
    int* local = 0;
    if (FUN_005bf0e0(param1, &local)) {
        FUN_00eec760(local, param2);
        if (local != 0)
            VC0(local, 4);
        return true;
    }
    if (local != 0)
        VC0(local, 4);
    return false;
}

// @ 0x00eeda20
void __cdecl f00eeda20(const void* key, int* props)
{
    IntrusivePtr<IPropList> list;
    if (!FUN_005bf0e0((int)key, (int**)&list))
        list = new (aSimulator_013f09b4, 0, 0, 0, 0) SP::cPropertyList_s00ee_d3f0();

    if (list) {
        if (props[0] != -1) {
            EA::Variant_s00ee_d3f0 v;
            v.SetU32(*(const unsigned*)&props[0]);
            list->SetProperty(0x1f0372ed, &v);
            if (v.mFlags & 4)
                v.Destruct(false);
        }
        if (props[1] != 0x7fffffff) {
            EA::Variant_s00ee_d3f0 v;
            v.SetInt(props[1]);
            list->SetProperty(0xd6a4ff43, &v);
            if (v.mFlags & 4)
                v.Destruct(false);
        }
        if (props[2] != 0x7fffffff) {
            EA::Variant_s00ee_d3f0 v;
            v.SetInt(props[2]);
            list->SetProperty(0xb55857d7, &v);
            if (v.mFlags & 4)
                v.Destruct(false);
        }
        FUN_005bf120_s00ee_d3f0(key, list, 0, 0);
    }
}

// @ 0x00eedba0
void __cdecl f00eedba0(float* out, unsigned key)
{
    unsigned c = FUN_00eec870(key);
    c = (c == (unsigned)DAT_015ac948) ? (unsigned)DAT_015ac94c : c;
    out[0] = (float)((c >> 16) & 0xff) * 0.003921569f;
    out[1] = (float)((c >> 8) & 0xff) * 0.003921569f;
    out[2] = (float)(c & 0xff) * 0.003921569f;
}

// @ 0x00eedc10
bool __cdecl f00eedc10(cSpinPoint* point, void* view)
{
    Mgr* mgr = DAT_016c7aa4_s00ee_d3f0->mManager;
    void* obj = mgr->fn3d780(point);
    if (obj == 0)
        return false;
    int* hit = (int*)VC1(obj, 0x0c, 0x1186577);
    if (hit == 0)
        return false;

    float* pos = VCP(view, 0x2c);
    float dx = point->mX - pos[0];
    float dy = point->mY - pos[1];
    float dz = point->mZ - pos[2];
    float radius = g_15ac950;
    float rsum = VCF(view, 0x70) + radius;

    if (dx * dx + dy * dy + dz * dz <= rsum * rsum &&
        (void*)hit != view &&
        (((unsigned)hit[0xa8] >> 1) & 1) &&
        fabs(*(float*)((char*)hit + 0xb4)) <= radius) {
        hkVector4_s00ee_d3f0 normal;
        RadialRay ray;
        ray.mPos.x = point->mX;
        ray.mPos.y = point->mY;
        ray.mPos.z = point->mZ;
        ray.mPos.w = 0.0f;
        ray.mH0 = 0.05f;
        ray.mH1 = -radius;
        RayHitResult_s00ee_d3f0 res;
        res.mNormalOut = &normal;
        res.mDistOut = 0;
        res.mUserData = 0;
        res.mEntity = 0;
        FUN_00b668c0(&ray, FUN_00b3d350(), (hkWorld_s00ee_d3f0*)g_167ecd0, 0, true, &res, false);
        return view == FUN_00b18e00(res.mUserData);
    }
    return false;
}

// @ 0x00eede20
Noun* __cdecl FUN_00eede20(const ResourceKey_s00ee_de20* key, const Vector3* pos, const Quaternion* ori, float scale, bool bOwned, int a6, int a7, int a8, int a9)
{
    ResourceKey_s00ee_de20 out;
    ResourceKey_s00ee_de20 k;
    Noun* result = 0;
    Spatial* sp;
    FUN_00eeca60(&out, key);
    bool bFlag = true;

    switch (out.typeID) {
    case 0x3a2511e:
    case 0x2a8fb3f:
        result = NounManager_s00ee_de20()->FUN_00b23650(out.typeID, out.instanceID, 0, pos, ori);
        result->mField1c = a6;
        if (result->FUN_00b18530()) {
            if (!((FlagHolder*)result->FUN_00b18530())->FUN_00f254d0()) {
                Spatial* const fs = FUN_00b18e00_s00ee_de20(result);
                fs->mFlags = fs->mFlags & 0xfffffdff;
            }
        }
        break;
    case 0x18c88e4:
        {
            Noun* obj = NounManager_s00ee_de20()->CreateInstance(0x18c88e4);
            obj->FUN_00c6f770(0x2ae5ba7, 0, out.instanceID);
            result = FUN_00c9f060(obj);
        }
        break;
    case 0x403df5c:
        {
            Noun* obj = NounManager_s00ee_de20()->FUN_00bbd160();
            if (obj) obj->AddRef();
            k.instanceID = out.instanceID;
            k.groupID = out.groupID;
            k.typeID = 0x2f4e681b;
            obj->mSpatial.SetModelKey(&k);
            result = (Noun*)obj->Cast(0x17f243b);
            obj->Release();
        }
        break;
    case 0x74e0069:
        {
            Noun* obj = NounManager_s00ee_de20()->CreateInstance(0x74e0069);
            if (obj) {
                obj->FUN_00eab830(key);
                obj->FUN_00eac530();
                sp = FUN_00b18e00_s00ee_de20(obj);
                if (sp) {
                                    k.instanceID = out.instanceID;
                    k.groupID = out.groupID;
                    k.typeID = 0x2f4e681b;
                    sp->SetModelKey(&k);
                }
                result = FUN_00eec0b0(obj);
            }
            bFlag = false;
        }
        break;
    case 0x7b38ba7:
        {
            Noun* obj = NounManager_s00ee_de20()->CreateInstance(0x7b38ba7);
            if (obj) {
                obj->FUN_00eab830(key);
                obj->FUN_00f0d8b0();
                sp = (Spatial*)obj->Cast(0x1186577);
                        k.instanceID = out.instanceID;
                k.groupID = out.groupID;
                k.typeID = 0x2f4e681b;
                sp->SetModelKey(&k);
                result = (Noun*)obj->Cast(0x7b38ba7);
            }
            bFlag = false;
        }
        break;
    case 0x2b978c46:
        {
            SpeciesProfile* prof = FUN_00401090()->GetProfile(&out);
            if (prof) {
                Herd* herd = NounManager_s00ee_de20()->CreateHerd(pos, prof, 1, bOwned, 0xb, 0);
                if (herd) {
                    herd->FUN_00c6ace0(1);
                    herd->mField88 = 0xdada0591;
                    herd->mFieldF0 = 0;
                    herd->mField108 = 128.0f;
                    void* who = NounManager_s00ee_de20()->GetAvatar();
                    if (!bOwned) {
                        who = FUN_00c099e0(pos, prof, 1, herd, 0, 0);
                        if (a7 != 0 && gpGameState->mMode == 2)
                            FUN_00d996b0(a9, a7, pos, (char*)who + 0x1648);
                    }
                    result = FUN_00c9f060(who);
                    if (bOwned) FUN_00d2e580();
                }
            }
            bFlag = false;
        }
        break;
    case 0x2399be55:
        {
            result = NounManager_s00ee_de20()->CreateInstance(0x70703b3);
            result->SetFlag54(0);
            result->mSpatial.SetModelKey(&out);
            result = (Noun*)result->Cast(0x17f243b);
        }
        break;
    case 0x24682294:
        {
            Vehicle* veh = (Vehicle*)NounManager_s00ee_de20()->CreateInstance(0x18c6de8);
            result = FUN_00c9f060(veh);
            Spatial* const vs = &veh->mSpatial;
            vs->SetModelKey(&out);
            void* const pDef = FUN_00eecba0(&out);
            int const purpose = FUN_00c9ed00(pDef);
            int const locomotion = FUN_00c9ed80(pDef);
            result->mField1c = a6;
            veh->Init(purpose, locomotion, *vs->GetModelKey());
            if (a7 != 0 && gpGameState->mMode == 2)
                FUN_00d996b0(a9, a7, pos, (char*)veh + 0xb00);
        }
        break;
    case 0x476a98c7:
        {
            Vehicle* veh = (Vehicle*)NounManager_s00ee_de20()->CreateInstance(0x18c6de8);
            if (veh)
                result = (Noun*)veh->Cast(0x17f243b);
            else
                result = 0;
            result->mField1c = a6;
            veh->Init(2, 0, out);
        }
        break;
    case 0xf0000001:
        {
            IntrusivePtr_s00ee_de20<IPropList_s00ee_de20> plist;
            PropMgr_s00ee_de20* pm = FUN_0067de30_s00ee_de20();
            pm->GetPropertyList(key->instanceID, key->groupID, &plist);
            result = FUN_00f213f0(plist, a7, a6);
        }
        break;
    default:
        {
            result = NounManager_s00ee_de20()->CreateInstance(0x18c88e4);
            result->FUN_00c6f770(0x750f022, -1, 0);
        }
        break;
    }

    if (result) {
        sp = (Spatial*)result->Cast(0x1186577);
        if (bFlag) sp->mFlags |= 0x8000;
        sp->SetPosition(pos);
        sp->SetOrientation(ori);
        sp->SetScale(scale);
        uint32_t nounId = result->GetNounID();
        switch (nounId) {
        case 0x18eb45e:
            {
                Creature* cr = (Creature*)result->Cast(0xd0036e08);
                cr->FUN_00c04590()->SetPosition(pos);
                FUN_00eeccb0(cr);
            }
            break;
        case 0x18ebadc:
            {
                Ufo* ufo = (Ufo*)result->Cast(0xb033b403);
                if ((pos->x != gVec3Zero.x || pos->y != gVec3Zero.y || pos->z != gVec3Zero.z) &&
                    FUN_005b1c80(ori, gQuatRef)) {
                    Spatial* const us = (Spatial*)((char*)ufo + 0x34);
                    ufo->FUN_00c3aa40(us->GetV2c(), us->GetV30());
                }
            }
            break;
        case 0x403df5c:
            {
                Noun* cn = (Noun*)result->Cast(0x403df5f);
                cn->mSpatial.SetScale(5.0f);
            }
            break;
        }
        result->mField1c = a6;
        result->mField18 = a7;
        if (a7) {
            FUN_00eed720(a7, sp, sp->mDataA8);
            sp->mbFlagA7 = 1;
        }
        ObjTail* tail = (ObjTail*)result->Cast(0x13f94d4);
        if (tail && result->FUN_00b18530() && ((ObjTail*)result->FUN_00b18530())->FUN_00f25330())
            tail->FUN_00f924e0(FUN_00eec5c0(result));
    }
    NounManager_s00ee_de20()->FUN_00b22960();
    return result;
}

// @ 0x00eee530
void __cdecl FUN_00eee530(float* p1, float* p2, float* p3, float* p4, float* out5, float* out6)
{
    float nq[4];
    float d[3];
    float aux[3];
    float* r;
    nq[0] = -p2[0];
    nq[1] = -p2[1];
    nq[2] = -p2[2];
    nq[3] = p2[3];
    d[0] = p3[0] - p1[0];
    d[1] = p3[1] - p1[1];
    d[2] = p3[2] - p1[2];
    r = FUN_0059aed0(aux, d, nq);
    out5[0] = r[0];
    out5[1] = r[1];
    out5[2] = r[2];
    {
        float a0 = p4[0];
        float a1 = p4[1];
        float a2 = p4[2];
        float a3 = p4[3];
        float b0 = nq[0];
        float b1 = nq[1];
        float b2 = nq[2];
        float b3 = nq[3];
        float t0 = a2 * b1 - a1 * b2;
        float t1 = b2 * a0 - a2 * b0;
        float t2 = a1 * b0 - a0 * b1;
        out6[0] = (b3 * a0 + a3 * b0) + t0;
        out6[1] = (a1 * b3 + a3 * b1) + t1;
        out6[2] = (a2 * b3 + a3 * b2) + t2;
        out6[3] = a3 * b3 - ((a2 * b2 + a1 * b1) + a0 * b0);
    }
}

// @ 0x00eee760
void __cdecl FUN_00eee760(void* arg1, ListRange* list)
{
    {
        void* gsv = *(void**)((char*)gpGameState + 0x74);   // loaded into a dead local by the original
        (void)gsv;
    }
    if (!arg1)
        return;
    if (list->pBegin == list->pEnd)
        return;
    void* pv = FUN_00f3d780(arg1);
    void* edi;
    if (pv)
        edi = (void*)((Noun*)pv)->Cast(0x1186577);
    else
        edi = 0;
    ListEntry_s00ee_de20* it = list->pBegin;
    ListEntry_s00ee_de20* end = list->pEnd;
    if (it == end)
        return;
    do {
        float aux[3];
        float* m = (float*)((void*(__thiscall*)(void*))(*(void***)edi)[0x30 / 4])(edi);
        float* rr = FUN_0059aed0(aux, it->p, m);
        float* sp = (float*)((void*(__thiscall*)(void*))(*(void***)edi)[0x2c / 4])(edi);
        float* pos = (float*)((char*)it->pObj + 4);
        pos[0] = sp[0] + rr[0];
        pos[1] = sp[1] + rr[1];
        pos[2] = sp[2] + rr[2];
        float* a = (float*)((void*(__thiscall*)(void*))(*(void***)edi)[0x30 / 4])(edi);
        float a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
        float e0 = it->q[0], e1 = it->q[1], e2 = it->q[2], e3 = it->q[3];
        float t0 = e3 * a1 - e1 * a2;
        float t1 = a2 * e0 - e3 * a0;
        float t2 = e1 * a0 - e0 * a1;
        float* oq = (float*)((char*)it->pObj + 0x10);
        oq[0] = (a3 * e0 + e3 * a0) + t0;
        oq[1] = (a3 * e1 + e3 * a1) + t1;
        oq[2] = (a3 * e2 + e3 * a2) + t2;
        oq[3] = e3 * a3 - ((e2 * a2 + e0 * a0) + e1 * a1);
        FUN_00f3da90(it->pObj, 0);
        ++it;
    } while (it != end);
}

// @ 0x00eeea50
bool __cdecl FUN_00eeea50(AssetRef* arg1, ExtCall* outStr)
{
    bool bl = false;
    if (FUN_004bbe20((void*)arg1->type, 1)) {
        ResKey3 key;
        key.a = arg1->p0;
        key.b = 0x30bdee3;
        key.c = arg1->p2;
        void* slot = 0;
        ResMgr* mgr = (ResMgr*)FUN_0067dcd0();
        mgr->Slot3(&key, &slot, 0, 0, 0, 0);
        if (slot) {
            void* p = ((void*(__thiscall*)(void*, int))(*(void***)slot)[0xc / 4])(slot, 0x30bdee3);
            if (p) {
                ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
                const wchar_t* name = ((ExtCall*)p)->FUN_00414e10();
                const wchar_t* end = name;
                while (*end)
                    ++end;
                outStr->FUN_00423650(name, end);
                bl = true;
                ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
            }
            ((void(__thiscall*)(void*))(*(void***)slot)[4 / 4])(slot);
        }
        return bl;
    }
    if (arg1->type != (void*)0xb1b104)
        return bl;
    CSString cs;
    ((ExtCall*)&cs)->FUN_006b5060();
    {
        void* slot = 0;
        PropMgr_s00ee_de20* pm = FUN_0067de30_s00ee_de20();
        bool ok = ((bool(__thiscall*)(void*, uint32_t, uint32_t, IPropList_s00ee_de20**))(*(void***)pm)[0x2c / 4])
            (pm, (uint32_t)arg1->p0, (uint32_t)arg1->p2, (IPropList_s00ee_de20**)&slot);
        if (ok) {
            if (FUN_006a1360(slot, 0x71e9bd1, &cs)) {
                outStr->FUN_005c3d90(((ExtCall*)&cs)->FUN_006b55c0());
                bl = true;
            }
        }
        ((ExtCall*)&cs)->FUN_006b5240();
        if (slot)
            ((void(__thiscall*)(void*))(*(void***)slot)[4 / 4])(slot);
    }
    return bl;
}
