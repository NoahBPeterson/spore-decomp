// src/game/SPEngine/SPString.cpp -- migrated from slice(s) s006b5770, s006b47a0, s0068c330, s00637f80 by tools/migrate/rewrite.py
// Object file: SPEngine/SPString.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorUI.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "SP/cJob.h"

// ---- items of slice s00637f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IWindow {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual IWindow* Cast(uint32_t type);
    virtual IWindow* GetParent();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual uint32_t GetFlags();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual float* GetRealArea();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void SetShadeColor(uint32_t c);
    virtual void v24();
    virtual void SetLocation(float x, float y);
    virtual void v26();
    virtual void SetLayoutArea(const float* rect);
    virtual void SetLayoutLocation(float x, float y);
    virtual void SetLayoutSize(float w, float hgt);
    virtual void v30();
    virtual void SetFlag(int flag, bool v);
    virtual void SetCaption(const wchar_t* s);
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual int Invalidate();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void AddWindow(IWindow* w);
    virtual void RemoveWindow(IWindow* w);
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void AddWinProc(void* p);
};
struct cString_s0063_7f80 {
    cString_s0063_7f80();                                                          // 0x006B5060
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* fallback);   // 0x006B54B0
    const wchar_t* c_str();                                             // 0x006B55C0
    ~cString_s0063_7f80();                                                         // 0x006B5240
    uint32_t pad[5];
};
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void assign(const wchar_t* b, const wchar_t* e);                    // 0x00423650
    void RangeInitialize(const wchar_t* s);                             // 0x00579A90
    int find(const WStr& needle, int pos);                              // 0x00608340
    void erase(int pos, int n);                                         // 0x004228E0
    int size() const { return (int)(mpEnd - mpBegin); }
};
void EASTL_deallocate(void* p);                                         // 0x00F47380
namespace SPUIHelpers {
void AutoSizeWindowForText(IWindow* w, bool a, bool b);                 // 0x00806E40
}
struct Rect4 { float l, t, r, b; };
struct cPaletteStub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void SetEnabled(int a); };
namespace SP {
class cSPEditorUI_s0063_7f80 { public: IWindow* FindWindowByID(uint32_t id); };    // 0x005DC310
}
namespace SP {
class cAppModeEditorBase_s0063_7f80 {
public:
    char pad0[0x78]; cSPEditorUI_s0063_7f80* mpEditorUI;                           // +0x78
    char pad1[0x358 - 0x7c]; cPaletteStub* mpPaletteData;                    // +0x358
};
}
namespace SP {
class cSPPlayModeUI_s0063_7f80 {
public:
    IWindow* FindPlayModeUIWindow(uint32_t id);                         // 0x00634DC0
    void LayoutYouTubeUploadButton();                                   // 0x00637F80
    void ShowMovieSavedDialogCustom();                                  // 0x00638430
    char pad0[0xc]; cAppModeEditorBase_s0063_7f80* mApp;                           // +0xc
    char pad1[0x64 - 0x10]; IWindow* mpDialog;                          // +0x64
};
}
// ---- items of slice s00637f80 end

// ---- items of slice s006b47a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool g_ColorLocalized;
typedef unsigned short wchar16;
void __cdecl EA_Free(void* p);
void* __cdecl FUN_0067de50();   // returns cStringManager* (global 0x15fd8fc)
void* __cdecl FUN_0067de40();   // returns resource manager (global 0x15fd8f8)
namespace SP {
struct cString_s006b_47a0;
}
namespace SP {
struct cStringDetokenizer;
}
namespace SP {
struct cStringManager;
}
namespace SP {
struct IRefCounted;
}
namespace SP {
struct string16 {
    wchar16* mpBegin;      // +0
    wchar16* mpEnd;        // +4
    wchar16* mpCapacity;   // +8
    int      mAllocator;   // +0xc
};
}
namespace SP {
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
};
}
namespace SP {
struct AutoRefCount {
    IRefCounted* mpObject;   // +0
    explicit AutoRefCount(IRefCounted* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Release() { IRefCounted* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
};
}
namespace SP {
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
}
namespace SP {
struct cStringDetokenizer {
    virtual void v0();                                          // +0x00
    virtual void v1();                                          // +0x04
    virtual void v2();                                          // +0x08
    virtual void v3();                                          // +0x0c
    virtual bool TranslateToken(const wchar16*, string16&);     // +0x10
    virtual void func14h(int);                                  // +0x14
    virtual void func18h();                                     // +0x18
    virtual void AddTranslator(void*);                          // +0x1c
    virtual void RemoveTranslator(void*);                       // +0x20
    virtual bool HasTokens(const wchar16*);                     // +0x24
    virtual bool func28h(int, void*);                           // +0x28
    virtual bool ProcessString(const wchar16*, string16&);      // +0x2c
    virtual bool func30h(void*, void*, void*);                  // +0x30
    virtual void func34h(const wchar16*, int);                  // +0x34
    virtual bool ProcessStringEx(const wchar16*, string16&);    // +0x38
    virtual bool FindTokenTranslation(const wchar16*, string16&);// +0x3c
};
}
namespace SP {
struct cStringManager {
    virtual ~cStringManager();                                  // +0x00
    virtual void AddString(cString_s006b_47a0*);                           // +0x04
    virtual void RemoveString(cString_s006b_47a0*);                        // +0x08
    virtual void v3();                                          // +0x0c
    virtual cStringDetokenizer* GetStringDetokenizer();         // +0x10
};
}
namespace SP {
extern wchar16 sDefaultCStr[];
}
namespace SP {
extern char g_placeholderMap[];   // eastl hash_map<uint32_t, string16> @ 0x15308a8
}
namespace SP {
struct HashMap {
    void erase_key(uint32_t* key);
};
}
namespace SP {
struct cString_s006b_47a0 {
    AutoRefCount mpTableResource; // +0x0
    string16* mpLocalString;      // +0x4
    const wchar16* mpSourceCStr;  // +0x8
    uint32_t mPlaceholderId;      // +0xc
    bool mbHasTokens;             // +0x10
    bool mField11;                // +0x11
    cString_s006b_47a0* Self() { return this; }

    cString_s006b_47a0();  // 0x006b56f0 (SP::cString::cString_s006b_47a0)
    cString_s006b_47a0(const cString_s006b_47a0& other);  // 0x006b56f0 (SP::cString::cString_s006b_47a0)
    ~cString_s006b_47a0();  // 0x006b56f0 (SP::cString::cString_s006b_47a0)
    bool Load(uint32_t tableID, uint32_t instanceID, int group);  // 0x006b54b0 (SP::cString::Load)
    cString_s006b_47a0& operator=(const cString_s006b_47a0& other);
    void set_source_string(const wchar16* src, bool alloc);
    const wchar16* GetText();
};
}
namespace SP {
struct IResourceMgr {
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual void r3();
    virtual void r4();
    virtual void r5();
    virtual void r6();
    virtual void r7();
    virtual void r8();
    virtual void r9(ResourceKey*, cString_s006b_47a0*);   // +0x24
};
}
namespace SP {
struct IResource {
    virtual void q0();
    virtual void q1();
    virtual void q2();
    virtual void q3();
    virtual void q4();
    virtual const wchar16* q5(int group);      // +0x14
};
}
// ---- items of slice s006b47a0 end

// ---- items of slice s006b47a0_b begin (TODO(rewrite): local stubs, replace by canonical classes)
volatile int g_opaqueGlobalB;
// ---- items of slice s006b47a0_b end

// @ 0x00637f80
void SP::cSPPlayModeUI_s0063_7f80::LayoutYouTubeUploadButton()
{
    cString_s0063_7f80 title;
    title.Load(0x7518573e, 0x5e501eb, L"YouTube Upload (PLACEHOLDER)");
    WStr text = {0, 0, 0};
    bool iconFirst = true;
    const wchar_t* t = title.c_str();
    const wchar_t* te = t;
    while (*te) te++;
    text.assign(t, t + (te - t));
    IWindow* wa = mApp->mpEditorUI->FindWindowByID(0x5e51108);
    IWindow* wb = mApp->mpEditorUI->FindWindowByID(0x5daa660);
    WStr marker = {0, 0, 0};
    marker.RangeInitialize(L"<youtubeicon>");
    WStr before = {0, 0, 0};
    WStr after = {0, 0, 0};
    int pos = text.find(marker, 0);
    if (pos != -1) {
        before.assign(text.mpBegin, text.mpEnd);
        text.erase(pos, before.size());
        after.assign(before.mpBegin, before.mpEnd);
        // text now holds the part before the marker, 'before' the full string
        before.erase(0, pos + marker.size());
        if (((text.mpEnd - text.mpBegin) & ~1) == 0) {
            after.assign(before.mpBegin, before.mpEnd);
        } else {
            after.assign(text.mpBegin, text.mpEnd);
            iconFirst = false;
        }
    }
    if (wb) {
        wb->SetCaption(after.mpBegin);
        SPUIHelpers::AutoSizeWindowForText(wb, false, false);
    }
    float* ra = wa->GetRealArea();
    float baseX = ra[0];
    IWindow* spanWin;
    if (!iconFirst) {
        Rect4 aR = {ra[0], ra[1], ra[2], ra[3]};
        float* rb = wb->GetRealArea();
        Rect4 bR = {rb[0], rb[1], rb[2], rb[3]};
        Rect4 nb = {aR.l, bR.t, (bR.r - bR.l) + aR.l, (bR.b - bR.t) + bR.t};
        wb->SetLayoutArea(&nb.l);
        float right = wb->GetRealArea()[2] + 3.0f;
        Rect4 na = {right, aR.t, (aR.r - aR.l) + right, (aR.b - aR.t) + aR.t};
        wa->SetLayoutArea(&na.l);
        baseX = wb->GetRealArea()[0];
        spanWin = wa;
    } else {
        spanWin = wb;
    }
    float spanRight = spanWin->GetRealArea()[2];
    IWindow* container = mApp->mpEditorUI->FindWindowByID(0x5b5ef50);
    float* rc = container->GetRealArea();
    float shift = (spanRight + baseX) * 0.5f - (rc[2] - rc[0]) * 0.5f;
    float* r1 = wa->GetRealArea();
    Rect4 ra2 = {r1[0], r1[1], r1[2], r1[3]};
    float* r2 = wb->GetRealArea();
    Rect4 rb2 = {r2[0], r2[1], r2[2], r2[3]};
    Rect4 sa = {ra2.l - shift, ra2.t, (ra2.r - ra2.l) + (ra2.l - shift), (ra2.b - ra2.t) + ra2.t};
    wa->SetLayoutArea(&sa.l);
    Rect4 sb = {rb2.l - shift, rb2.t, (rb2.r - rb2.l) + (rb2.l - shift), (rb2.b - rb2.t) + rb2.t};
    wb->SetLayoutArea(&sb.l);
    if (((text.mpCapacity - text.mpBegin) & ~1) > 2 && text.mpBegin) EASTL_deallocate(text.mpBegin);
    (void)marker; (void)before;
}

// @ 0x0068d340
void* HashMapOp(void* self, unsigned key, void* out)
{
    (void)self;
    (void)key;
    (void)out;
    return 0;
}

// @ 0x006b5030
void __cdecl SP_cString_SetColorLocalized(bool b)
{
    g_ColorLocalized = b;
}

// @ 0x006b5040
void __cdecl FUN_006b5040(uint32_t a, uint32_t b, uint32_t c, uint32_t* out)
{
    out[0] = a;
    out[1] = b;
}

// @ 0x006b5060
namespace SP {
cString_s006b_47a0::cString_s006b_47a0()
: mpTableResource(0), mpLocalString(0), mpSourceCStr(sDefaultCStr),
      mPlaceholderId(0), mbHasTokens(false), mField11(false)
{
    if (FUN_0067de50() != 0)
        ((cStringManager*)FUN_0067de50())->AddString(this);
}
}  // namespace SP

// @ 0x006b50d0
uint32_t* __cdecl FUN_006b50d0(uint32_t key)
{
    // `anonymous namespace'::find_placeholder -- eastl hash_map find; PARTIAL.
    g_opaqueGlobalB = key;
    return (uint32_t*)(size_t)g_opaqueGlobalB;
}

// @ 0x006b5110
void SP::HashMap::erase_key(uint32_t* key)
{
    // eastl hash_map<uint32_t,string16>::erase(key); PARTIAL.
    g_opaqueGlobalB = *key;
}

// @ 0x006b51a0
uint32_t __cdecl FUN_006b51a0(const wchar16* src)
{
    // `anonymous namespace'::alloc_placeholder; PARTIAL.
    g_opaqueGlobalB = (int)(size_t)src;
    return g_opaqueGlobalB;
}

// @ 0x006b5240
namespace SP {
cString_s006b_47a0::~cString_s006b_47a0()
{
    if (FUN_0067de50() != 0)
        ((cStringManager*)FUN_0067de50())->RemoveString(this);
    if (mpLocalString != 0) {
        string16* s = mpLocalString;
        wchar16* p = s->mpBegin;
        int n = ((int)(size_t)s->mpCapacity - (int)(size_t)p) & 0xfffffffe;
        if (n > 2 && p != 0)
            EA_Free(p);
        EA_Free(s);
        mpLocalString = 0;
    }
    if (mPlaceholderId != 0) {
        uint32_t id = mPlaceholderId;
        ((HashMap*)g_placeholderMap)->erase_key(&id);
        mPlaceholderId = 0;
    }
    mpTableResource.Release();
}
}  // namespace SP

// @ 0x006b53a0
void* __cdecl FUN_006b53a0(void* out, wchar16 ch, const void* other)
{
    // eastl basic_string<wchar_t>::operator+ helper; PARTIAL.
    g_opaqueGlobalB = ch + (int)(size_t)other;
    return out;
}

// @ 0x006b5430
namespace SP {
cString_s006b_47a0& cString_s006b_47a0::operator=(const cString_s006b_47a0& other)
{
    if (this != &other) {
        IRefCounted* old = mpTableResource.mpObject;
        IRefCounted* nw = other.mpTableResource.mpObject;
        if (nw != old) {
            if (nw != 0)
                nw->AddRef();
            mpTableResource.mpObject = nw;
            if (old != 0)
                old->Release();
        }
        mpSourceCStr = other.mpSourceCStr;
        mbHasTokens = other.mbHasTokens;
        mField11 = false;
        if (other.mPlaceholderId != 0) {
            uint32_t* __cdecl FUN_006b50d0(uint32_t);
            uint32_t* p = FUN_006b50d0(other.mPlaceholderId);
            if (p != 0) {
                set_source_string((const wchar16*)*p, true);
                return *this;
            }
            set_source_string(sDefaultCStr, false);
        }
    }
    return *this;
}
}  // namespace SP

// @ 0x006b54b0
namespace SP {
bool cString_s006b_47a0::Load(uint32_t tableID, uint32_t instanceID, int group)
{
    mField11 = false;
    if (mpLocalString != 0) {
        wchar16* p = mpLocalString->mpBegin;
        int n = ((int)(size_t)mpLocalString->mpCapacity - (int)(size_t)p) & 0xfffffffe;
        if (n > 2 && p != 0)
            EA_Free(p);
        EA_Free(mpLocalString);
    }
    IRefCounted* t = mpTableResource.mpObject;
    mpLocalString = 0;
    if (t == 0) {
        if (tableID == 0xffffffff || instanceID == 0xffffffff)
            goto after_load;
    } else if (*(uint32_t*)((char*)t + 8) == tableID) {
        goto after_load;
    }
    {
        IResourceMgr* mgr = (IResourceMgr*)FUN_0067de40();
        if (mpTableResource.mpObject != 0) {
            IRefCounted* r = mpTableResource.mpObject;
            mpTableResource.mpObject = 0;
            r->Release();
        }
        ResourceKey key;
        key.instanceID = tableID;
        key.typeID = 0x2fac0b6;
        key.groupID = 0x2fabf01;
        mgr->r9(&key, this);
    }
after_load:
    if (mPlaceholderId != 0) {
        uint32_t id = mPlaceholderId;
        ((HashMap*)g_placeholderMap)->erase_key(&id);
        mPlaceholderId = 0;
    }
    IRefCounted* res = mpTableResource.mpObject;
    mbHasTokens = false;
    mpSourceCStr = sDefaultCStr;
    if (res != 0) {
        const wchar16* s = ((IResource*)res)->q5(group);
        if (s == 0 || s[0] == 0)
            s = 0;
        else
            set_source_string(s, false);
        if (mpTableResource.mpObject != 0 && s != 0)
            return true;
    }
    return false;
}
}  // namespace SP

// @ 0x006b55c0
namespace SP {
const wchar16* cString_s006b_47a0::GetText()
{
    if (mField11) {
        string16* s0 = mpLocalString;
        if (s0 == 0)
            return 0;
        return s0->mpBegin;
    }
    if (!mbHasTokens && !g_ColorLocalized)
        return mpLocalString->mpBegin;
    cStringDetokenizer* d = ((cStringManager*)FUN_0067de50())->GetStringDetokenizer();
    d->ProcessString(mpSourceCStr, *mpLocalString);
    return mpLocalString->mpBegin;
}
}  // namespace SP

// @ 0x006b56d0
void __cdecl FUN_006b56d0(SP::ResourceKey* key, SP::cString_s006b_47a0* out)
{
    out->Load(key->instanceID, key->typeID, 0);
}

// @ 0x006b56f0
SP::cString_s006b_47a0::cString_s006b_47a0(const cString_s006b_47a0& other)
: mpTableResource(other.mpTableResource.mpObject), mpLocalString(0),
      mpSourceCStr(other.mpSourceCStr), mPlaceholderId(0),
      mbHasTokens(false), mField11(false)
{
    if (FUN_0067de50() != 0)
        ((cStringManager*)FUN_0067de50())->AddString(this);
    *this = other;
}

// @ 0x006b5770
SP::cString::cString(unsigned int a1, unsigned int a2, wchar_t const * a3)
{}
