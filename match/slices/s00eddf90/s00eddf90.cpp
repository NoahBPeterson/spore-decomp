// Slice s00eddf90 -- scenario edit-mode behavior UI (value/image updates, behavior selection, layout
// build) and the creature-field setters.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);
typedef void  (__thiscall *FV_i)(void*, int);
typedef void* (__thiscall *FV_ip)(void*, int);
typedef void  (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_iip)(void*, int, int, void*);

// unnamed retail callees and globals (address in the comment)
void  __cdecl FUN_00571db0(int, int, int, int, int);   // 0x571db0
void  __fastcall FUN_00f45a80(void* mgr);              // 0xf45a80
void  __fastcall FUN_00f45970(void* mgr);              // 0xf45970
void  __fastcall FUN_00f3c0b0(void* mgr);              // 0xf3c0b0
extern char* g_16c7aa4;                                // 0x16c7aa4 global object table
void* __fastcall FUN_00ed85e0(void*);                  // 0xed85e0
void  __fastcall FUN_00ed8610(void*);                  // 0xed8610
void  __cdecl SetSliderFraction(void*, float);         // 0xedcf60

namespace EA { namespace ResourceMan {
class Key {                                        // 0xc, IWindow image identity
 public:
  uint32_t instanceID;                             // +0x0
  uint32_t typeID;                                 // +0x4
  uint32_t groupID;                                // +0x8
};
} }

namespace Math {
struct Rectangle {                                 // 0x10, returned by IWindow::GetRealArea
  float x1;                                        // +0x0 left
  float y1;                                        // +0x4 top
  float x2;                                        // +0x8 right
  float y2;                                        // +0xc bottom
  float Width() const { return x2 - x1; }
  float Height() const { return y2 - y1; }
};
}

struct IWinProc {                                  // window-procedure base sub-object (vptr only)
    virtual void v00();                            // +0x0
    virtual int  AddRef();                         // +0x4
    virtual int  Release();                        // +0x8
};

struct IWindow {                                   // EA::UTFWin::IWindow
    virtual int AddRef();                                            // +0x000
    virtual int Release();                                           // +0x004
    virtual void v08();
    virtual void* Cast(uint32_t type);                               // +0x00c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual const Math::Rectangle& GetArea();                        // +0x034
    virtual const Math::Rectangle& GetRealArea();                    // +0x038
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetLayoutArea(const Math::Rectangle& area);         // +0x06c
    virtual void SetLayoutLocation(float x, float y);                // +0x070
    virtual void SetLayoutSize(float w, float h);                    // +0x074
    virtual void SetCursorID(uint32_t id);                           // +0x078
    virtual void SetFlag(int flag, bool value);                      // +0x07c
    virtual void SetCaption(const wchar_t* caption);                 // +0x080
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4();
    virtual void AddWindow(IWindow* w);                              // +0x0d8
    virtual void vdc(); virtual void ve0(); virtual void ve4(); virtual void ve8();
    virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);    // +0x0f0
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(IWinProc* proc);                         // +0x104
};

class cSPUILayout {                                // SPEditors layout (0x18)
 public:
    virtual ~cSPUILayout();                        // +0x00
    virtual int AddRef();                          // +0x04
    virtual int Release();                         // +0x08
    virtual int GetRefCount();                     // +0x0c
    bool Init(const EA::ResourceMan::Key& key, bool immediate, uint32_t id);       // 0x8120d0
    bool SetVisibility(bool visible);                                              // 0x810590
    IWindow* FindWindowByID(uint32_t id, bool recursive) const;                    // 0x8105b0
    void Shutdown(bool immediate);                                                 // 0x811ad0
    bool SetParentWin(IWindow* parent, bool immediate, uint32_t id);               // 0x8121b0
    cSPUILayout();                                                                // 0x810000

 public:  // data (retail 0x18)
    uint32_t mField04;                             // +0x04
    EA::ResourceMan::Key mResourceKey;             // +0x08
    void* mpObjectCollection;                      // +0x14
};

class cBehaviorGroupUI {                           // per-group window binder (0x44)
 public:
    virtual void v00();                            // +0x00
    virtual void v04();                            // +0x04
    virtual int  AddRef();                         // +0x08
    virtual int  Release();                        // +0x0c
    virtual void SetWindow(IWindow* window);       // +0x10
    cBehaviorGroupUI();                            // 0xf38c70

 public:  // data (retail 0x44): opaque here, only reached through the virtual interface
    char mData[0x40];                              // +0x14
};

template <class T> struct AutoRefCount {
    T* mpObject;
    __declspec(noinline) AutoRefCount() : mpObject(0) {}   // out of line: arrays build it by address (0x743b50)
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
};

struct cBehaviorGroupList {                        // 0x1c, one binder per group window
    int mnCount;                                   // +0x00
    AutoRefCount<cBehaviorGroupUI> mGroups[6];     // +0x04
    cBehaviorGroupList() : mnCount(6) {}
};

extern const uint32_t kGroupWinIDs[6];             // 0x148a708 group-window ids
extern const uint32_t kIconWinIDs[3];              // 0x148a694 icon-window ids
extern const int kBehaviorSlotIDs[6];              // 0x148a738 per-slot behaviour id (slot 5 = 0)
extern const char kAllocTagUI[];                   // 0x13f6b3c behaviour-UI allocator tag
extern const char kAllocTagLayout[];               // 0x148a86c cSPUILayout allocator tag
extern const EA::ResourceMan::Key kBehaviorUILayoutKey;   // 0x15ac670 layout resource key

void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);   // 0xf473a0

namespace EA { namespace Locale {
void __cdecl SetNumberString(__int64 value, wchar_t* text, int size);   // 0x881ae0
} }

namespace SPUIHelpers {
bool __cdecl SetWindowImage(IWindow* window, const EA::ResourceMan::Key* key, int index);  // 0x807bb0
}

EA::ResourceMan::Key* __cdecl MakeImageKey(EA::ResourceMan::Key* out, int imageID);   // 0xedd240

// The shared editing manager that publishes the begin/end-edit notifications.
static inline void* EditMgr() { return *(void**)(g_16c7aa4 + 0x74); }

// ================================================================ 0x00eddf90
// @ 0x00eddf90
void __cdecl FUN_00eddf90(IWindow* w, float value, float min, float max)
{
    if (!w)
        return;
    w->SetFlag(1, true);
    wchar_t text[0x20];
    EA::Locale::SetNumberString((__int64)value, text, 0x20);
    IWindow* caption = w->FindWindowByID(0x7918378, true);
    if (caption)
        caption->SetCaption(text);
    SetSliderFraction(w->FindWindowByID(0x742cd10, true), (value - min) / (max - min));
}

// ================================================================ 0x00ede040
// @ 0x00ede040
void __cdecl FUN_00ede040(IWindow* root, bool visible, int imageID)
{
    bool hasImage = imageID != -1;
    if (!root)
        return;
    IWindow* w = root->FindWindowByID(0x742d068, false);
    if (w)
        w->SetFlag(1, visible);
    if (!visible)
        return;
    IWindow* icon = root->FindWindowByID(0x742c8d0, true);
    if (icon)
        icon->SetFlag(1, !hasImage);
    IWindow* frame = root->FindWindowByID(0x742c8f8, true);
    if (frame)
        frame->SetFlag(1, hasImage);
    if (!hasImage)
        return;
    EA::ResourceMan::Key key;
    SPUIHelpers::SetWindowImage(frame, MakeImageKey(&key, imageID), -1);
}

// ================================================================ 0x00ede110
struct BehaviorEntry {                             // 0x4e0, one behaviour of the edited creature
    char   pad0[0x4ac];
    int    mBehaviorID;                            // +0x4ac
    char   pad1[0x4c8 - 0x4b0];
    bool   mSelected;                              // +0x4c8
    char   pad2[0x4e0 - 0x4c9];
};

struct BehaviorList {
    char   pad0[0x20];
    bool   mIsList;                                // +0x20 (entries stored inline from +0x70)
    char   pad1[0x70 - 0x21];
    BehaviorEntry* mpBegin;                        // +0x70
    BehaviorEntry* mpEnd;                          // +0x74
};

// @ 0x00ede110
bool __cdecl FUN_00ede110(BehaviorList* list, BehaviorEntry* entry, int index)
{
    volatile bool changed = false;                 // the status byte stays in the frame across the notify calls
    if (index < 0)
        return false;
    if (index >= 6)
        return false;
    int id = kBehaviorSlotIDs[index];
    if (list->mIsList) {
        for (int i = 0; i < list->mpEnd - list->mpBegin; i++) {
            if (list->mpBegin[i].mBehaviorID != id || (list->mpBegin[i].mSelected == true && id != 0)) {
                changed = true;
                FUN_00f45970(EditMgr());
                for (int j = 0; j < list->mpEnd - list->mpBegin; j++) {
                    list->mpBegin[j].mSelected = (index == 5);
                    list->mpBegin[j].mBehaviorID = id;
                }
                goto finish;
            }
        }
        return changed;
    }
    if (entry->mBehaviorID == id && (entry->mSelected != true || id == 0)) {
        changed = false;
        return changed;
    }
    changed = true;
    FUN_00f45970(EditMgr());
    entry->mSelected = (index == 5);
    entry->mBehaviorID = id;
finish:
    FUN_00f45a80(EditMgr());
    return changed;
}

// ================================================================ creature-field setters
// Six copies of the same setter (one float field at a fixed offset inside each 0x4e0-byte fragment);
// FUN_00ede2b0 (0x48c) additionally copies two flag bytes out of the incoming struct.
// Shape notes (0xede400 family): the original keeps its status byte in bl, sets it right before the
// notify/kill call of each arm and shares one kill block between the short and the main arm; every
// count expression is recomputed per iteration.
#define MGR (*(void**)(g_16c7aa4 + 0x74))
#define FIELD_COUNT(s) ((*(volatile int*)((s) + 0x74) - *(volatile int*)((s) + 0x70)) / 0x4e0)
#define DEF_FRAG(NAME, OFF) \
    struct NAME { char pad0[OFF]; float f; char pad1[0x4e0 - OFF - 4]; };

DEF_FRAG(Frag484, 0x484)
DEF_FRAG(Frag4a0, 0x4a0)
DEF_FRAG(Frag49c, 0x49c)
DEF_FRAG(Frag498, 0x498)
DEF_FRAG(Frag490, 0x490)
DEF_FRAG(Frag494, 0x494)
DEF_FRAG(Frag48c, 0x48c)

// @ 0x00ede400
bool __cdecl FUN_00ede400(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x484);
    char r;
    int i;
    Frag484* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag484*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag484*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede530
bool __cdecl FUN_00ede530(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x4a0);
    char r;
    int i;
    Frag4a0* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag4a0*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag4a0*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede660
bool __cdecl FUN_00ede660(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x49c);
    char r;
    int i;
    Frag49c* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag49c*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag49c*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede790
bool __cdecl FUN_00ede790(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x498);
    char r;
    int i;
    Frag498* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag498*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag498*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede8c0
bool __cdecl FUN_00ede8c0(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x490);
    char r;
    int i;
    Frag490* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag490*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag490*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede9f0
bool __cdecl FUN_00ede9f0(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x494);
    char r;
    int i;
    Frag494* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag494*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag494*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede2b0
bool __cdecl FUN_00ede2b0(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x48c);
    char r;
    int i;
    Frag48c* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag48c*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) {
                ((Frag48c*)*(int*)(s + 0x70))[i].f = fv;
                ((char*)*(int*)(s + 0x70))[i * 0x4e0 + 2] = ((char*)p2)[2];
                ((char*)*(int*)(s + 0x70))[i * 0x4e0 + 1] = ((char*)p2)[1];
            }
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// ================================================================ 0x00edeb20
struct ObjEB20 { void* f(); };
// @ 0x00edeb20
void* ObjEB20::f()
{
    char* s = (char*)this;
    // The two base sub-objects install their own vftables first and the derived vftables then replace
    // them; volatile keeps those stores in order (they are the only writes of the object's vftables).
    *(volatile int*)(s + 4) = 0x13ec458;
    *(int*)(s + 8) = 0;
    *(volatile int*)(s + 0xc) = 0x14426a0;
    *(volatile int*)s = 0x148a864;
    *(volatile int*)(s + 4) = 0x148a854;
    *(volatile int*)(s + 0xc) = 0x148a838;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x20) = -1;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x30) = 0;
    *(int*)(s + 0x34) = 0;
    FUN_00ed85e0(s + 0x48);
    *(int*)(s + 0x70) = 0;
    *(int*)(s + 0x74) = 0;
    *(int*)(s + 0x78) = 0;
    *(int*)(s + 0x7c) = 0;
    *(int*)(s + 0x80) = 0;
    return s;
}

// ================================================================ 0x00edebb0
struct ObjEBB0 { void f(); };
void ObjEBB0::f()
{
    char* s = (char*)this;
    *(int*)s = 0x148a864;
    *(int*)(s + 4) = 0x148a854;
    *(int*)(s + 0xc) = 0x148a838;
    if (*(int*)(s + 0x70) != 0) {
        int h = *(int*)(s + 0x70);
        *(int*)(s + 0x70) = 0;
        FUN_00571db0(h, *(int*)(s + 0x74), *(int*)(s + 0x78), *(int*)(s + 0x7c), *(int*)(s + 0x80));
    }
    FUN_00ed8610(s + 0x48);
    if (*(int**)(s + 0x34)) ((FV_v)(*(void***)*(int**)(s + 0x34))[4 / 4])(*(int**)(s + 0x34));
    if (*(int**)(s + 0x30)) ((FV_v)(*(void***)*(int**)(s + 0x30))[4 / 4])(*(int**)(s + 0x30));
    if (*(int**)(s + 0x18)) ((FV_v)(*(void***)*(int**)(s + 0x18))[4 / 4])(*(int**)(s + 0x18));
    if (*(int**)(s + 0x10)) ((FV_v)(*(void***)*(int**)(s + 0x10))[8 / 4])(*(int**)(s + 0x10));
    *(int*)(s + 0xc) = 0x13eb938;
    *(int*)(s + 4) = 0x13ec458;
    *(int*)s = 0x13eb394;
}

// ================================================================ 0x00edec50
namespace Simulator {
class cScenarioEditModeBehaviorUI {
 public:
    void*  mpVtblPrimary;                          // +0x00
    void*  mpVtblNotify;                           // +0x04
    int    mNotifyState;                           // +0x08
    IWinProc mWinProc;                             // +0x0c (added to every icon and frame window)
    AutoRefCount<cSPUILayout> mLayout;             // +0x10
    int    mField14;                               // +0x14
    int    mField18;                               // +0x18
    cBehaviorGroupList* mpGroups;                  // +0x1c
    bool Initialize(IWindow* parent);
};
}

// @ 0x00edec50
bool Simulator::cScenarioEditModeBehaviorUI::Initialize(IWindow* parent)
{
    bool result = false;
    mpGroups = new (kAllocTagUI, 0, 0, 0, 0) cBehaviorGroupList();
    if (!parent)
        return result;
    mLayout = new (kAllocTagLayout, 0, 0, 0, 0) cSPUILayout();
    if (!mLayout->Init(kBehaviorUILayoutKey, false, 0x5b598fa)) {
        mLayout->Shutdown(true);
        mLayout = 0;
        return false;
    }
    mLayout->SetVisibility(false);
    mLayout->SetParentWin(parent, true, 0x5b598fa);
    IWindow* root = mLayout->FindWindowByID(0x73e6ba0, true);
    if (!root)
        return false;
    root->SetLayoutLocation(0.0f, 0.0f);
    root->SetLayoutSize(parent->GetRealArea().Width(), parent->GetRealArea().Height());
    root->AddWinProc(&mWinProc);
    for (int g = 0; g < 6; g++) {
        IWindow* group = mLayout->FindWindowByID(kGroupWinIDs[g], true);
        for (int j = 0; j < 3; j++) {
            IWindow* inner = group->FindWindowByID(kIconWinIDs[j], true);
            if (inner) {
                IWindow* frame = inner->FindWindowByID(0x742c8f8, true);
                if (frame)
                    frame->AddWinProc(&mWinProc);
                IWindow* image = inner->FindWindowByID(0x742c8d0, true);
                image->AddWinProc(&mWinProc);
                image->SetCursorID(0x747d67b);
            }
        }
        mpGroups->mGroups[g] = new (kAllocTagUI, 0, 0, 0, 0) cBehaviorGroupUI();
        mpGroups->mGroups[g]->SetWindow(group->FindWindowByID(0x7ec6a40, true));
    }
    return true;
}
