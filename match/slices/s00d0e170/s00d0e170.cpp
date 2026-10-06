// Slice s00d0e170 -- SP::cCommunityEditor::Activate (0x00d0e170, ~6980 bytes, /O2 /arch:SSE).
//
// Activates the city/tribe/colony ("community") editor: swaps in the edited
// community, sets up the camera, clears the per-session state, builds the
// economy object, the city-stats rollover, the palette (+ palette UI), the
// collectable-item unlocks, model-type swatches, shopping UI, the budget and the
// naming widget, registers the 26 active message ids and posts the first-use
// behaviour message.
//
// Complete reconstruction from the disassembly (all paths, calls and stores).
// Field offsets are the RETAIL ones (the 2008 PDB layout of cCommunityEditor is
// 0x294 bytes; retail is larger, offsets shift by +0x8..+0x24), names follow the
// PDB where the correspondence is clear. Callees are masked relocations, so the
// stub classes below only need the right calling convention and vtable slots.
//
// Module flags: x87 float args + movss copies, no EH frame although cString /
// vector locals have dtors => /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <stddef.h>

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);           // 0x00f473a0 (EA allocator new)
extern "C" void EASTL_allocator_deallocate(void* p);      // 0x00f47380

uint32_t FNVHash(const char* s, uint32_t seed, int lowercase); // 0x00932e80
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }

struct ResourceKey {                                      // EA::ResourceMan::Key
    uint32_t instanceID, typeID, groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct Vector3 { float x, y, z; };
extern Vector3 g_Vector3Zero;                             // 0x0169d58c
bool Vector3Equal(const Vector3* a, const Vector3* b);    // 0x004232c0 (cdecl)

// ---- minimal EASTL-shaped containers -------------------------------------
template <class T> struct sp_vector {                     // vector<T, sp_vector_allocator>
    T* mpBegin; T* mpEnd; T* mpCapacity; const char* mAllocName;
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector() {                                        // sp_vector_allocator::deallocate
        if (mpBegin && reinterpret_cast<int*>(mpBegin)[-1] != 0)
            EASTL_allocator_deallocate(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);      // 0x004558a0 (uint32 instance)
    void push_back(const T& value) {                      // 0x00454860 when not inlined
        if (mpEnd < mpCapacity) { T* p = mpEnd++; if (p) *p = value; }
        else DoInsertValue(mpEnd, value);
    }
    sp_vector& operator=(const sp_vector& x);             // 0x01011cc0
};

struct rbtree_node;
struct rbtree_map {                                       // eastl::map<K,V> (0x1c bytes)
    struct anchor_t { void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; char mColor; };
    uint32_t mCompare;
    anchor_t mAnchor;
    uint32_t mnSize;
    const char* mAllocName;
    void DoNukeSubtree(void* node);                       // 0x009a9600
    void clear() {
        DoNukeSubtree(mAnchor.mpNodeParent);
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
};

// Smart pointer whose pointee has AddRef/Release virtuals.
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
#define SIZE_CHECK(T, n) typedef char size_check_##T[(sizeof(T) == (n)) ? 1 : -1]

// ---- UI ------------------------------------------------------------------
namespace UTFWin {
struct IWindow {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual const float* GetRealArea();                   // 0x38
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void SetShadeColor(uint32_t color);           // 0x5c
    virtual void v24();
    virtual void SetLocation(float x, float y);           // 0x64
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30();
    virtual void SetFlag(int flag, bool value);           // 0x7c
    virtual void SetCaption(const wchar_t* caption);      // 0x80
};
}
using UTFWin::IWindow;
enum { kWinFlagVisible = 1 };

struct cSPUILayout {                                      // 0xc bytes
    uint32_t pad[3];
    void SetVisibility(bool visible);                     // 0x00810590
    IWindow* FindWindowByID(uint32_t controlID, bool recursive); // 0x008105b0
};

struct CursorAttachmentLayout { void SetWindow(IWindow* w); };   // 0x008017f0
CursorAttachmentLayout* FUN_0067cab0();

struct cUIHints { uint32_t pad[0x12]; int mState; void UpdateHints(int a, bool b); }; // 0x0067c350
cUIHints* FUN_0067cac0();

struct cSwatchManager {
    IWindow* FUN_0080dc90();
    void     FUN_0080dc50(uint32_t swatchID);
};
cSwatchManager* FUN_0067cad0();

struct cUnknownCF74 { void FUN_00cf7a30(); };
cUnknownCF74* FUN_00cf74c0();

struct cSPUIPropertyLayout {                              // city-stats rollover (0xb0 bytes)
    virtual void AddRef(); virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void SetProperty(uint32_t id);                // 0x28
    uint32_t data[(0xb0 - 4) / 4];
    cSPUIPropertyLayout();                                // 0x00e2b8e0
    void SetKey(const wchar_t* name, uint32_t group);     // 0x00827fc0
    void FUN_00e2ad50(bool b);
    void FUN_00e2abc0();
    IWindow* GetRootWindow();                             // 0x00828100
};

// ---- messaging -----------------------------------------------------------
struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void PostMSG(uint32_t msgID, void* msg, int flags);     // 0x14
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual void AddHandler(void* handler, uint32_t msgID);         // 0x24
};
IMessageServer* MessageServer();                          // 0x0067dcc0

struct AutoHandler {                                      // EA::Messaging::AutoHandler
    IMessageServer* mpServer;
    void*           mpHandler;
    const uint32_t* mpIdArray;
    uint32_t        mnIdCount;
    uint32_t        mbPassive;
    void Register(IMessageServer* server, void* handler, const uint32_t* ids, uint32_t count) {
        mpServer = server; mpHandler = handler; mpIdArray = ids; mnIdCount = count; mbPassive = 0;
        if (server)
            for (uint32_t i = 0; i < count; ++i)
                server->AddHandler(handler, ids[i]);
    }
};
extern const uint32_t kCommunityEditorMessageIDs[26];     // 0x01479158

// kMsgSetCreation message (two vptrs: 0x013ff7f0 / 0x013f6c9c)
struct cMsgBase { virtual void Base0(); };
struct cMsgData { virtual void Data0(); int mField8; int mFieldC; cMsgData() : mField8(0) {} };
struct cSetCreationMsg : cMsgBase, cMsgData {
    ResourceKey mKey;
    int         mToolType;
    explicit cSetCreationMsg(int toolType) : mToolType(toolType) {}
    virtual void Base0();
};
enum { kMsgSetCreation = 0x53850baf };

// UI::BehaviorMessage-derived refcounted message (vtbl 0x013eb844, 0x40 bytes)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
struct cBehaviorMessage {
    virtual void Dtor();
    virtual void AddRef();
    virtual void Release();
    volatile long mnRefCount;
    int      mField8;
    uint32_t pad0c[9];
    uint32_t mMessageID;
    uint32_t pad34;
    cBehaviorMessage() : mMessageID(0) { _InterlockedExchange(&mnRefCount, 0); }
};
struct cActivateBehaviorMessage : cBehaviorMessage {
    int mField38;
    uint32_t pad3c;
    cActivateBehaviorMessage() : mField38(0) {}
    virtual void Dtor();
};
template <class T> struct intrusive_ptr {
    T* mp;
    intrusive_ptr(T* p) : mp(p) { if (p) p->AddRef(); }
    ~intrusive_ptr() { if (mp) mp->Release(); }
    T* operator->() const { return mp; }
    T* get() const { return mp; }
};
SIZE_CHECK(cSPUIPropertyLayout, 0xb0); SIZE_CHECK(cActivateBehaviorMessage, 0x40);
SIZE_CHECK(cSetCreationMsg, 0x20);
extern bool g_bCommunityEditorFirstActivate;              // 0x0158236c

// ---- game objects ---------------------------------------------------------
namespace SP {

struct cDirectPropertyList { void SetBoolProperty(uint32_t id, bool value); };  // 0x006a17e0
extern cDirectPropertyList* g_pDirectProps;               // 0x015fd918

struct cGameTimeManager { void IncPauseGate(uint32_t gate); };                 // 0x00b32220
cGameTimeManager* GameTimeManager();                      // 0x00b3d380

struct cCommunityCamera {                                 // 0x00b3d280 accessor
    uint32_t pad00[4];
    bool     mb10;
    uint8_t  pad11[0x308 - 0x11];
    uint32_t mZoomState;                                  // +0x308
    const uint32_t* GetAnchorDirection();                 // 0x00b10260 (3 dwords)
    void GetAngles(uint32_t* a, uint32_t* b, uint32_t* c);// 0x00b0f210
    void SetZoomProgram(uint32_t id);                     // 0x00b11870
    void SetPreRotate(float x, float z);                  // 0x00b0f700
    void FUN_00b13bb0(const Vector3* target, bool snap);
    void FUN_00b13b50();
};
cCommunityCamera* FUN_00b3d280();

struct cIVisualEffect { virtual void v0(); virtual void v1(); virtual void Stop(int flags); };
struct cEffectsManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool GetEffect(uint32_t id, int group, cIVisualEffect** out);       // 0x2c
};
cEffectsManager* EffectsManager();                        // 0x0067ddd0

struct cGameNoun;
struct cCivilization;
struct cGameNounManager {
    void RemoveNoun(cGameNoun* noun);                     // 0x00b225d0
    cCivilization* GetPlayerCivilization();               // 0x00b25fb0
    void* GetCurrentTerrainSphere();                      // 0x00f67d90
};
cGameNounManager* NounManager();                          // 0x00b3d300

struct INameable {                                        // the +0x34 subobject
    virtual void v0();
    virtual const wchar_t* GetName();                     // slot 1
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual const Vector3* GetPosition();                 // 0x2c
};

struct cToolTemplate { uint8_t pad[0x504]; ResourceKey mKey; };   // +0x504

struct cCivilization {
    uint8_t   pad00[0x34];
    INameable mNameable;                                  // +0x34
    uint8_t   pad38[0x40 - 0x38];
    int       mPoliticalID;                               // +0x40
    sp_vector<void*>* FUN_00bef6c0();                     // list of cities
    cToolTemplate*    FUN_00bef950();
    const ResourceKey* GetModelTypeKey(uint32_t modelType);         // 0x00bf9770
};

struct cEmpireName { const wchar_t* mpBegin; };
struct cEmpire {
    const cEmpireName* GetName();                         // 0x005c65e0
    const ResourceKey* GetUFOKey();                       // 0x00c326b0
};
cEmpire* GetPlayerEmpire();                               // 0x01021300 (cSPLivingUniverse)

struct cCommunityMode {                                   // community vfunc 0x6c result
    bool FUN_00bec860();                                  // colony?
    const ResourceKey* FUN_00bebe10();
    uint32_t FUN_00bebe20();
};

struct cHallNoun { uint8_t pad[0x34]; INameable mSpatial; };

struct cCommunity {
    virtual void AddRef();                                // 0x00
    virtual void Release();                               // 0x04
    virtual void v02();
    virtual void* Cast(uint32_t typeID);                  // 0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    virtual const Vector3* GetPosition();                 // 0x64
    virtual void v26();
    virtual cCommunityMode* GetMode();                    // 0x6c
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46();
    virtual void* GetToolList();                          // 0xbc (cTribe)
    uint32_t  pad04[(0x34 - 4) / 4];
    INameable mNameable;                                  // +0x34
    uint8_t   pad38[0x192 - 0x38];
    bool      mbBeingEdited;                              // +0x192
};

struct cSpatialNoun {                                     // element of mPreExistingNouns
    uint8_t pad[0x34]; INameable mSpatial;
    struct cModel { void FUN_00c3f160(const Vector3* p, float radius); };
    cModel* FUN_00bce470();
};

struct cCity : cCommunity {
    cCivilization* GetCivilization();                     // 0x00bd9bf0
    void FUN_00bdc4a0(int);
    void* GetBuildings();                                 // 0x00c8e810 (vector)
    void FUN_00be5700(sp_vector<cSpatialNoun*>* out);
    void FUN_00bdde70(cSPUIPropertyLayout* stats);
    void FUN_00bd7f30();
    int  GetVehicleSpecialty();                           // 0x00bd81d0
    int  GetCreatureCount();                              // 0x00bd8120
    bool FUN_00bdb930(int specialty, int slot);
    const Vector3* FUN_00fa0e00();
    cHallNoun* GetCityHall();                             // 0x00bd9b40
};
enum { TYPE_cCity = 0xee9b2232, TYPE_cTribe = 0x4f396a66 };

struct cTribe : cCommunity {
    uint16_t FUN_00c8e9f0();
    bool     IsHerbivore();                               // 0x00c8e850
    cToolTemplate* FUN_00c8e820(int toolType);
    void*    GetToolOfType(int toolType);                 // 0x00c8f6e0
};
inline uint32_t TribeChief(cTribe* t) { return *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(t) + 0x234); }

template <class T> inline T* object_cast(cCommunity* p, uint32_t typeID)
{
    return p ? static_cast<T*>(p->Cast(typeID)) : 0;
}

// -- editor sub-objects --
struct cEditorEconomy {                                   // vtbl 0x1479484/0x14794a4/0x1479468
    virtual ~cEditorEconomy();
    int mnRefCount;
    cEditorEconomy() : mnRefCount(0) {}
    void AddRef() { ++mnRefCount; }
    void Release() { if (--mnRefCount == 0) { mnRefCount = 1; delete this; } }
};
struct cSpaceColonyEconomy : cEditorEconomy {
    cEmpire* mpEmpire; cCity* mpCity;
    cSpaceColonyEconomy(cEmpire* e, cCity* c) : mpEmpire(e), mpCity(c) {}
    virtual ~cSpaceColonyEconomy();
};
struct cCivCityEconomy : cEditorEconomy {
    cCity* mpCity;
    explicit cCivCityEconomy(cCity* c) : mpCity(c) {}
    virtual ~cCivCityEconomy();
};
struct cTribeEconomy : cEditorEconomy {
    cTribe* mpTribe;
    explicit cTribeEconomy(cTribe* t) : mpTribe(t) {}
    virtual ~cTribeEconomy();
};
template <> struct AutoRefCount<cEditorEconomy> {
    cEditorEconomy* mpObject;
    AutoRefCount& operator=(cEditorEconomy* p);           // 0x00572680 (out of line)
    void Assign(cEditorEconomy* p) {                      // inlined form (tribe path)
        cEditorEconomy* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
    }
    operator cEditorEconomy*() const { return mpObject; }
};

struct cCityMusicEditor {                                 // SP::Audio (0x114 bytes)
    virtual void AddRef(); virtual void Release();
    uint32_t data[(0x114 - 4) / 4];
    cCityMusicEditor();                                   // 0x00ea0ea0
    void Init();                                          // 0x00ea17b0
};

struct cCollectableItems {                                // 0x6dac bytes
    virtual void AddRef(); virtual void Release();
    struct Key { uint32_t a, b; };
    uint32_t data[(0x6dac - 4) / 4];
    cCollectableItems();                                  // 0x00597e00
    void FUN_00597a20();
    void AddUnlock(Key k, int, int, int, int, int, float, int);   // 0x00598db0
    void Unlock(Key k);                                   // 0x00596e10
};
cCollectableItems::Key FUN_00593980(uint32_t listID, uint32_t itemID);  // cdecl

struct cSPPalette {                                       // 0x40 bytes
    virtual void v0(); virtual void AddRef(); virtual void Release();
    uint32_t data[(0x40 - 4) / 4];
    cSPPalette();                                         // 0x005c5e30
    bool Init(const ResourceKey* key, int, int, int, int, int, int);   // 0x005c6340
};

struct cPaletteInfo {                                     // 0x34 bytes
    virtual void v0(); virtual void AddRef(); virtual void Release();
    uint32_t pad04;
    AutoRefCount<cEditorEconomy>     mEconomy;            // +0x08 (inline refcount)
    uint32_t pad0c;
    AutoRefCount<cCollectableItems>  mCollectables;       // +0x10
    uint32_t pad14;
    uint16_t mLimitType;                                  // +0x18
    uint16_t pad1a;
    uint32_t pad1c[(0x34 - 0x1c) / 4];
    cPaletteInfo();                                       // 0x005c64e0
};

struct cSPPaletteUI {                                     // 0x6c bytes
    virtual void AddRef(); virtual void Release();
    uint32_t data[(0x6c - 4) / 4];
    cSPPaletteUI();                                       // 0x005cb3b0
    void Init(cSPPalette* palette, IWindow* window, int, cPaletteInfo* info);   // 0x005cb5a0
    int  FindCategoryIndex();                             // 0x005ca9c0
};

struct cSPEditorBudget {                                  // 0x74 bytes
    virtual void v0(); virtual void v1(); virtual void AddRef(); virtual void Release();
    uint32_t data[(0x74 - 4) / 4];
    cSPEditorBudget();                                    // 0x004575d0
    void Init(const ResourceKey* layout, cEditorEconomy* economy, int limitType,
              IWindow* window, const wchar_t* title);     // 0x00457af0
};

struct cSPEditorNaming {                                  // 0x38 bytes
    virtual void AddRef(); virtual void Release();
    uint32_t data[(0x38 - 4) / 4];
    cSPEditorNaming();                                    // 0x005bfff0
    void Init(INameable* nameable, IWindow* window, uint32_t a, bool b, uint32_t c);   // 0x005bfd40
    void SetPrompt(const wchar_t* prompt);                // 0x005c0320
};

SIZE_CHECK(cSpaceColonyEconomy, 0x10); SIZE_CHECK(cCivCityEconomy, 0xc);
SIZE_CHECK(cTribeEconomy, 0xc); SIZE_CHECK(cCityMusicEditor, 0x114);
SIZE_CHECK(cCollectableItems, 0x6dac); SIZE_CHECK(cSPPalette, 0x40);
SIZE_CHECK(cPaletteInfo, 0x34); SIZE_CHECK(cSPPaletteUI, 0x6c);
SIZE_CHECK(cSPEditorBudget, 0x74); SIZE_CHECK(cSPEditorNaming, 0x38);

struct cLimitMeter {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void SetLimitType(int type);                  // 0x28
};

struct cString {
    uint32_t data[4];
    cString();                                            // 0x006b5060
    ~cString();                                           // 0x006b5240
    void Load(uint32_t tableID, uint32_t instanceID, int);// 0x006b54b0
    const wchar_t* GetText();                             // 0x006b55c0
};
struct cPropertyList;
bool GetPropertyAsText(cPropertyList* props, uint32_t id, cString* out);   // 0x006a1360
float GetPropertyF(uint32_t group, int, uint32_t prop, float def);         // 0x00bcea30
int   GetPropertyInt(uint32_t group, int, uint32_t prop, int def);         // 0x00bda3b0

uint32_t ColorRGBToU32(const void* rgb);                  // 0x00458a40
const void* FUN_00b6f0c0(uint32_t colorID);
uint32_t GetCurrentGameMode();                            // 0x00b5b800
enum { kGameModeCiv = 0x1654c04, kGameModeSpace = 0x1654c05 };

void FUN_00be2440(cCity* city, int, int);
struct cUnkB3D3F0 { void FUN_00e19010(); };
cUnkB3D3F0* FUN_00b3d3f0();
struct cUnkB3D400 { void FUN_00e14c10(int); };
cUnkB3D400* FUN_00b3d400();
struct cUnkB3D230 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void FUN_slot14(uint32_t id, bool b);         // 0x38
};
cUnkB3D230* FUN_00b3d230();
struct cUnk401090 { const ResourceKey* FUN_004df400(); };
cUnk401090* FUN_00401090();

// Events (cdecl, 7 args)
void FUN_00e3c7c0(uint32_t eventID, const ResourceKey* key, ResourceKey* a, ResourceKey* b,
                  int politicalID, int, int);
void FUN_00e398e0(uint32_t eventID, const ResourceKey* key, ResourceKey* a, ResourceKey* b,
                  uint32_t chief, int, int);
void FUN_00ba58e0(cTribe* tribe, int);
void FUN_00ba5a60(cCivilization* civ, int);

struct cCommunityEditor;
extern cCommunityEditor* g_pCommunityEditor;              // 0x0169d580

struct cCommunityEditor {
    virtual void HandleMessage();                         // IHandlerRC primary base (vptr +0)
    uint32_t pad04[4];
    AutoHandler   mActiveAutoHandler;                     // +0x14
    uint32_t      mPassiveAutoHandler[5];                 // +0x28
    cPropertyList* mConfigProps;                          // +0x3c
    AutoRefCount<cCommunity> mpCommunity;                 // +0x40
    uint32_t      mSelectedCategoryID;                    // +0x44
    uint32_t      mShoppingModelType;                     // +0x48
    uint32_t      mLastShoppingModelType;                 // +0x4c
    ResourceKey   mRecentlyEditedModelKey;                // +0x50
    bool          mbFromShopping;                         // +0x5c
    uint8_t       pad5d[3];
    int           mEconomyState;                          // +0x60
    uint32_t      mPaletteInstance;                       // +0x64
    AutoRefCount<cEditorEconomy>  mEconomy;               // +0x68
    AutoRefCount<cSPEditorBudget> mBudget;                // +0x6c
    IWindow*      mpWinBudget;                            // +0x70
    uint32_t      pad74;
    AutoRefCount<cCollectableItems> mCollectableItems;    // +0x78
    uint32_t      pad7c[2];
    cLimitMeter*  mpLimitMeter;                           // +0x84
    cSPUILayout   mEditorUI;                              // +0x88
    uint32_t      pad94[3];
    AutoRefCount<cSPUIPropertyLayout> mCityStats;         // +0xa0
    AutoRefCount<cSPEditorNaming>     mNaming;            // +0xa4
    IWindow*      mpWinSwatchRoot;                        // +0xa8
    AutoRefCount<cCityMusicEditor>    mCityMusicEditor;   // +0xac
    AutoRefCount<cSPPalette>          mPaletteData;       // +0xb0
    AutoRefCount<cSPPaletteUI>        mPaletteUI;         // +0xb4
    IWindow*      mWinPaletteRoot;                        // +0xb8
    cGameNoun*    mpRotationRing;                         // +0xbc
    uint32_t      padc0;
    void*         mpSelectedObject;                       // +0xc4
    uint8_t       padc8[0x114 - 0xc8];
    rbtree_map    mAnimatedObjectMap;                     // +0x114
    sp_vector<void*>         mPreExistingBuildings;       // +0x130
    uint32_t      pad140;
    sp_vector<cSpatialNoun*> mPreExistingNouns;           // +0x144
    uint8_t       pad154[0x1dc - 0x154];
    sp_vector<void*>         mPreExistingTools;           // +0x1dc
    uint8_t       pad1ec[0x204 - 0x1ec];
    int           mActivationMode;                        // +0x204
    bool          mbEffectsDirty;                         // +0x208
    bool          mbHintsIdle;                            // +0x209
    uint8_t       pad20a[0x2c4 - 0x20a];
    uint32_t      mSavedCameraZoomState;                  // +0x2c4
    uint8_t       pad2c8[0x2d8 - 0x2c8];
    uint32_t      mSavedAnchorDir[3];                     // +0x2d8
    uint32_t      mSavedAngles[3];                        // +0x2e4
    cCommunity*   mpSavedCameraCommunity;                 // +0x2f0

    void Activate(cCommunity* community, bool bSpaceGame);
    uint32_t GetCameraZoomProgramID();                    // 0x00d098b0
    void SetDefaultCamera(bool b);                        // 0x00d0b3b0
    void SetManipulatedObject(void* obj);                 // 0x00d09f60
    void FUN_00d0aa70();
    void SetKeyForModelType(uint32_t modelType, ResourceKey* key);         // 0x00d09560
    void UpdateSwatchForModelType(uint32_t modelType, const ResourceKey* key, uint32_t extra); // 0x00d0c820
    void SetupShoppingUI(uint32_t modelType, ResourceKey key, bool b);     // 0x00d08b50
    void UpdateLimitMeter(int category);                  // 0x00d0a1e0
};

#define OFFSET_CHECK(T, m, n) typedef char off_check_##T##_##m[(offsetof(T, m) == (n)) ? 1 : -1]
OFFSET_CHECK(cCommunityEditor, mActiveAutoHandler, 0x14);
OFFSET_CHECK(cCommunityEditor, mConfigProps, 0x3c);
OFFSET_CHECK(cCommunityEditor, mpCommunity, 0x40);
OFFSET_CHECK(cCommunityEditor, mRecentlyEditedModelKey, 0x50);
OFFSET_CHECK(cCommunityEditor, mbFromShopping, 0x5c);
OFFSET_CHECK(cCommunityEditor, mEconomy, 0x68);
OFFSET_CHECK(cCommunityEditor, mpWinBudget, 0x70);
OFFSET_CHECK(cCommunityEditor, mCollectableItems, 0x78);
OFFSET_CHECK(cCommunityEditor, mpLimitMeter, 0x84);
OFFSET_CHECK(cCommunityEditor, mEditorUI, 0x88);
OFFSET_CHECK(cCommunityEditor, mCityStats, 0xa0);
OFFSET_CHECK(cCommunityEditor, mWinPaletteRoot, 0xb8);
OFFSET_CHECK(cCommunityEditor, mpRotationRing, 0xbc);
OFFSET_CHECK(cCommunityEditor, mpSelectedObject, 0xc4);
OFFSET_CHECK(cCommunityEditor, mAnimatedObjectMap, 0x114);
OFFSET_CHECK(cCommunityEditor, mPreExistingBuildings, 0x130);
OFFSET_CHECK(cCommunityEditor, mPreExistingNouns, 0x144);
OFFSET_CHECK(cCommunityEditor, mPreExistingTools, 0x1dc);
OFFSET_CHECK(cCommunityEditor, mActivationMode, 0x204);
OFFSET_CHECK(cCommunityEditor, mbHintsIdle, 0x209);
OFFSET_CHECK(cCommunityEditor, mSavedCameraZoomState, 0x2c4);
OFFSET_CHECK(cCommunityEditor, mSavedAnchorDir, 0x2d8);
OFFSET_CHECK(cCommunityEditor, mpSavedCameraCommunity, 0x2f0);
OFFSET_CHECK(cCommunity, mNameable, 0x34);
OFFSET_CHECK(cCommunity, mbBeingEdited, 0x192);
OFFSET_CHECK(cCommunityCamera, mZoomState, 0x308);
OFFSET_CHECK(cCommunityCamera, mb10, 0x10);
OFFSET_CHECK(cCivilization, mNameable, 0x34);
OFFSET_CHECK(cCivilization, mPoliticalID, 0x40);
OFFSET_CHECK(cUIHints, mState, 0x48);
OFFSET_CHECK(cPaletteInfo, mEconomy, 0x8);
OFFSET_CHECK(cPaletteInfo, mCollectables, 0x10);
OFFSET_CHECK(cPaletteInfo, mLimitType, 0x18);
OFFSET_CHECK(cSetCreationMsg, mKey, 0x10);
OFFSET_CHECK(cSetCreationMsg, mToolType, 0x1c);
OFFSET_CHECK(cBehaviorMessage, mMessageID, 0x30);
OFFSET_CHECK(cActivateBehaviorMessage, mField38, 0x38);
OFFSET_CHECK(cToolTemplate, mKey, 0x504);
OFFSET_CHECK(cSpatialNoun, mSpatial, 0x34);
OFFSET_CHECK(cHallNoun, mSpatial, 0x34);

// Unlocks every item of `items` in collectable list `listID`.
static __forceinline void UnlockItems(cCollectableItems* items, uint32_t listID, sp_vector<uint32_t>& ids)
{
    int n = ids.size();
    for (int i = 0; i < n; ++i) {
        cCollectableItems::Key k = FUN_00593980(listID, ids[i]);
        items->AddUnlock(k, 0, 0, 0, 0, 0, 0.0f, 0);
        items->Unlock(k);
    }
}

// Fires the "model type selected" event for the player civilization.
static __forceinline void FireModelTypeEvent(uint32_t eventID, ResourceKey* modelKey)
{
    ResourceKey none;
    FUN_00e3c7c0(eventID, &NounManager()->GetPlayerCivilization()->FUN_00bef950()->mKey,
                 modelKey, &none, NounManager()->GetPlayerCivilization()->mPoliticalID, 0, 0);
}

} // namespace SP

using namespace SP;

// @ 0x00d0e170
void SP::cCommunityEditor::Activate(cCommunity* community, bool bSpaceGame)
{
    g_pCommunityEditor = this;
    mpWinSwatchRoot = FUN_0067cad0()->FUN_0080dc90();
    FUN_0067cad0()->FUN_0080dc50(id("SwatchDefault"));

    mbEffectsDirty = false;
    if (mActivationMode != 1)
        mEconomyState = -1;

    mpCommunity = community;

    if (mpCommunity) {
        if (mActivationMode != 1) {
            g_pDirectProps->SetBoolProperty(0x387d0a8, false);
            GameTimeManager()->IncPauseGate(0x4bf38a6);
        }

        // ---- camera ----
        if (cCommunityCamera* camera = FUN_00b3d280()) {
            if (!bSpaceGame) {
                const uint32_t* dir = camera->GetAnchorDirection();
                mSavedAnchorDir[0] = dir[0];
                mSavedAnchorDir[1] = dir[1];
                mSavedAnchorDir[2] = dir[2];
                camera->GetAngles(&mSavedAngles[0], &mSavedAngles[1], &mSavedAngles[2]);
                mpSavedCameraCommunity = mpCommunity;
            }
            mSavedCameraZoomState = camera->mZoomState;
            camera->SetZoomProgram(GetCameraZoomProgramID());
            camera->mb10 = false;
            camera->SetPreRotate(
                GetPropertyF(id("CommunityEditor"), 0, id("CameraPreRotateX"), 0.07f),
                GetPropertyF(id("CommunityEditor"), 0, id("CameraPreRotateZ"), 0.15f));
        }
        SetDefaultCamera(bSpaceGame);

        cIVisualEffect* effect = 0;
        if (EffectsManager()->GetEffect(0xb2540a24, 0, &effect))
            effect->Stop(0);

        FUN_0067cab0()->SetWindow(0);
        mEditorUI.SetVisibility(true);
        SetManipulatedObject(0);

        mpSelectedObject = 0;
        if (mpRotationRing) {
            NounManager()->RemoveNoun(mpRotationRing);
            mpRotationRing = 0;
        }
        int hintState = FUN_0067cac0()->mState;
        mbHintsIdle = hintState == 0 || hintState == 1;
        FUN_0067cac0()->UpdateHints(0, true);
        FUN_00cf74c0()->FUN_00cf7a30();

        // ---- community-specific setup ----
        uint16_t limitType = 0;
        cTribe* tribe = object_cast<cTribe>(mpCommunity, TYPE_cTribe);
        cCity*  city  = object_cast<cCity>(mpCommunity, TYPE_cCity);
        bool inSpace = GetCurrentGameMode() == kGameModeSpace;

        mAnimatedObjectMap.clear();

        const wchar_t* communityName = 0;
        uint32_t budgetTitleID = 0;

        if (city) {
            city->mbBeingEdited = true;
            city->GetCivilization();
            limitType = 0x268a;
            if (inSpace) {
                mEconomy = new ("Editor", 0, 0, 0, 0) cSpaceColonyEconomy(GetPlayerEmpire(), city);
                communityName = GetPlayerEmpire()->GetName()->mpBegin;
                budgetTitleID = 0x65f79f1;
            } else {
                mEconomy = new ("Editor", 0, 0, 0, 0) cCivCityEconomy(city);
                communityName = city->GetCivilization()->mNameable.GetName();
                budgetTitleID = 0x65f79f0;
                city->FUN_00bdc4a0(0);
            }

            uint32_t color = ColorRGBToU32(FUN_00b6f0c0(0x53dbcf1));
            if (IWindow* w = mEditorUI.FindWindowByID(0x643aebb, true))
                w->SetShadeColor(color);

            mPreExistingBuildings = *static_cast<sp_vector<void*>*>(city->GetBuildings());
            city->FUN_00be5700(&mPreExistingNouns);
            int count = mPreExistingNouns.size();
            for (int i = 0; i < count; ++i) {
                if (mPreExistingNouns[i] && mPreExistingNouns[i]->FUN_00bce470()) {
                    cSpatialNoun* noun = mPreExistingNouns[i];
                    noun->FUN_00bce470()->FUN_00c3f160(noun->mSpatial.GetPosition(), 4.0f);
                }
            }

            mCityStats = new ("Editor", 0, 0, 0, 0) cSPUIPropertyLayout();
            mCityStats->SetKey(L"CityPlannerCityStats", 0x40464100);
            mCityStats->SetProperty(0x2edd95ca);
            mCityStats->FUN_00e2ad50(true);
            if (inSpace)
                mCityStats->FUN_00e2abc0();
            if (IWindow* w = mEditorUI.FindWindowByID(0xa7c5c4a6, true)) {
                const float* area = w->GetRealArea();
                mCityStats->GetRootWindow()->SetLocation(area[0], area[1]);
            }
            city->FUN_00bdde70(mCityStats);

            if (IWindow* w = mEditorUI.FindWindowByID(0x34bbede9, true)) {
                cCivilization* civ = NounManager()->GetPlayerCivilization();
                w->SetFlag(kWinFlagVisible, civ && civ->FUN_00bef6c0()->size() > 1);
            }
            city->FUN_00bd7f30();
            FUN_00be2440(city, 0, 0);
            FUN_00b3d3f0()->FUN_00e19010();
            if (FUN_00b3d400())
                FUN_00b3d400()->FUN_00e14c10(0);

            if (!mCityMusicEditor) {
                mCityMusicEditor = new ("Editor", 0, 0, 0, 0) cCityMusicEditor();
                mCityMusicEditor->Init();
            }
        }

        if (tribe) {
            tribe->mbBeingEdited = true;
            limitType = tribe->FUN_00c8e9f0();
            mEconomy.Assign(new ("Editor", 0, 0, 0, 0) cTribeEconomy(tribe));
            communityName = tribe->mNameable.GetName();
            budgetTitleID = 0xf87c278d;
            mPreExistingTools = *static_cast<sp_vector<void*>*>(tribe->GetToolList());
            if (IWindow* w = mEditorUI.FindWindowByID(0x34bbede9, true))
                w->SetFlag(kWinFlagVisible, false);
            if (IWindow* w = mEditorUI.FindWindowByID(0x643aebb, true))
                w->SetFlag(kWinFlagVisible, false);
        }

        if (communityName)
            if (IWindow* w = mEditorUI.FindWindowByID(0x53d5a68, true))
                w->SetCaption(communityName);

        if (mpLimitMeter)
            mpLimitMeter->SetLimitType(limitType);

        // ---- palette ----
        if (mWinPaletteRoot) {
            ResourceKey paletteKey(0, 0xb1b104, 0x406b6a00);
            if (city) {
                int specialty = city->GetVehicleSpecialty();
                if (GetCurrentGameMode() == kGameModeSpace)
                    paletteKey.instanceID = GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDColony"), 0x44);
                else if (specialty == 0)
                    paletteKey.instanceID = GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDCityMilitary"), 0x41);
                else if (specialty == 1)
                    paletteKey.instanceID = GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDCityCultural"), 0x42);
                else if (specialty == 2)
                    paletteKey.instanceID = GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDCityEconomic"), 0x43);
            } else if (tribe) {
                if (mPaletteInstance != 0)
                    paletteKey.instanceID = mPaletteInstance;
                else if (tribe->IsHerbivore())
                    paletteKey.instanceID = GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDTribeHerbivore"), 0x41);
                else
                    paletteKey.instanceID = GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDTribeCarnivore"), 0x41);
            }

            mPaletteData = new ("Editor", 0, 0, 0, 0) cSPPalette();
            if (mPaletteData->Init(&paletteKey, -1, 0, 0, 0, 0, 0)) {
                mCollectableItems = new ("Editor", 0, 0, 0, 0) cCollectableItems();
                mCollectableItems->FUN_00597a20();
                FUN_00d0aa70();

                if (city) {
                    if (inSpace) {
                        sp_vector<uint32_t> buildings;
                        if (city->GetMode()->FUN_00bec860()) {
                            buildings.push_back(0x3e2af274);
                            buildings.push_back(id("ColonyLand"));
                            buildings.push_back(id("ColonyAir"));
                        } else if (Vector3Equal(city->FUN_00fa0e00(), &g_Vector3Zero)) {
                            buildings.push_back(0x3e2af274);
                        }
                        UnlockItems(mCollectableItems, 0xccb453cf, buildings);

                        sp_vector<uint32_t> buildings2;
                        if (city->GetMode()->FUN_00bec860()) {
                            buildings2.push_back(id("House"));
                            buildings2.push_back(0x51fbb249);
                            buildings2.push_back(0x36f60725);
                            buildings2.push_back(id("Space_Turret"));
                            buildings2.push_back(id("Turret"));
                        }
                        UnlockItems(mCollectableItems, 0xb79acba1, buildings2);
                    } else {
                        sp_vector<uint32_t> buildings;
                        int population = city->GetCreatureCount();
                        if (population < GetPropertyInt(id("CommunityEditor"), 0, id("RequiredPopulationForFactory"), 30))
                            buildings.push_back(0x51fbb249);
                        if (population < GetPropertyInt(id("CommunityEditor"), 0, id("RequiredPopulationForTurret"), 40))
                            buildings.push_back(0x9f6db313);
                        if (population < GetPropertyInt(id("CommunityEditor"), 0, id("RequiredPopulationForEntertainment"), 50))
                            buildings.push_back(0x36f60725);
                        UnlockItems(mCollectableItems, 0xdcc387f5, buildings);

                        sp_vector<uint32_t> vehicles;
                        int specialty = city->GetVehicleSpecialty();
                        NounManager()->GetCurrentTerrainSphere();
                        if (!city->FUN_00bdb930(specialty, 0)) {
                            vehicles.push_back(0xdf036863);
                            vehicles.push_back(0x222ded4);
                            vehicles.push_back(0x13d90629);
                        }
                        if (!city->FUN_00bdb930(specialty, 1)) {
                            vehicles.push_back(0x69529449);
                            vehicles.push_back(0x63608190);
                            vehicles.push_back(0xc958c1bf);
                        }
                        if (!city->FUN_00bdb930(specialty, 2)) {
                            vehicles.push_back(0xfa167da8);
                            vehicles.push_back(0xad76c2cd);
                            vehicles.push_back(0x85e38d82);
                        }
                        vehicles.push_back(0x476a98c7);
                        UnlockItems(mCollectableItems, 0x96beff33, vehicles);
                    }
                }

                {
                    intrusive_ptr<cPaletteInfo> info(new ("Editor", 0, 0, 0, 0) cPaletteInfo());
                    info->mEconomy.Assign(mEconomy);
                    info->mCollectables = mCollectableItems;
                    info->mLimitType = limitType;
                    mPaletteUI = new ("Editor", 0, 0, 0, 0) cSPPaletteUI();
                    mPaletteUI->Init(mPaletteData, mWinPaletteRoot, 0, info.get());
                }
            }
        }

        // ---- tribe tools ----
        if (tribe) {
            if (mLastShoppingModelType == 0x372e2c04) {
                if (!mbFromShopping) {
                    ResourceKey a, b;
                    FUN_00e398e0(0x4e54b73d, &tribe->FUN_00c8e820(0)->mKey, &b, &a,
                                 TribeChief(tribe), 0, 0);
                    FUN_00ba58e0(tribe, 7);
                }
                mLastShoppingModelType = 0xffffffff;
            }
            for (int toolType = 0; toolType < 14; ++toolType) {
                if (tribe->GetToolOfType(toolType) || toolType == 0) {
                    cSetCreationMsg msg(toolType);
                    msg.mKey = tribe->FUN_00c8e820(tribe->FUN_00c8e820(toolType) ? toolType : 0)->mKey;
                    MessageServer()->PostMSG(kMsgSetCreation, &msg, 0);
                }
            }
            if (IWindow* w = mEditorUI.FindWindowByID(0x563fa08, true))
                w->SetFlag(kWinFlagVisible, true);
        }

        // ---- city swatches / shopping ----
        if (city) {
            cCivilization* civ = city->GetCivilization();
            uint32_t last = mLastShoppingModelType;
            if (last != 0xffffffff && mActivationMode != 0 && mRecentlyEditedModelKey.instanceID != 0 &&
                last != 0x372e2c04 && last != 0xccc35c46 && last != 0x65672ade && last != 0x4178b8e8)
                SetKeyForModelType(last, &mRecentlyEditedModelKey);

            if (!mbFromShopping) {
                switch (mLastShoppingModelType) {
                case 0x99e92f05: case 0xbdd15f3d: case 0x47c10953:
                case 0x4e3f7777: case 0x72c49181:
                    if (GetCurrentGameMode() == kGameModeCiv)
                        FireModelTypeEvent(0xef6d08a3, &mRecentlyEditedModelKey);
                    break;
                case 0xccc35c46:
                    FireModelTypeEvent(0xad076d90, &mRecentlyEditedModelKey);
                    if (civ)
                        FUN_00ba5a60(NounManager()->GetPlayerCivilization(), 7);
                    break;
                case 0x1f2a25b6: case 0xc0b74287: case 0x9ad7d4aa: case 0x8f963dcb:
                case 0xf670aa43: case 0x1a4e0708: case 0x2a5147a9: case 0x441cd3e6:
                case 0x449c040f: case 0x7d433fad:
                    FireModelTypeEvent(0x7b27dbd1, &mRecentlyEditedModelKey);
                    break;
                }
            }
            mLastShoppingModelType = 0xffffffff;

            UpdateSwatchForModelType(0x99e92f05, civ->GetModelTypeKey(0x99e92f05), 0);
            UpdateSwatchForModelType(0x4e3f7777, civ->GetModelTypeKey(0x4e3f7777), 0);
            UpdateSwatchForModelType(0x47c10953, civ->GetModelTypeKey(0x47c10953), 0);
            UpdateSwatchForModelType(0x72c49181, civ->GetModelTypeKey(0x72c49181), 0);
            UpdateSwatchForModelType(0x7d433fad, civ->GetModelTypeKey(0x7d433fad), 0);
            UpdateSwatchForModelType(0x441cd3e6, civ->GetModelTypeKey(0x441cd3e6), 0);
            UpdateSwatchForModelType(0x8f963dcb, civ->GetModelTypeKey(0x8f963dcb), 0);
            UpdateSwatchForModelType(0x9ad7d4aa, civ->GetModelTypeKey(0x9ad7d4aa), 0);
            UpdateSwatchForModelType(0x449c040f, civ->GetModelTypeKey(0x449c040f), 0);
            UpdateSwatchForModelType(0x1f2a25b6, civ->GetModelTypeKey(0x1f2a25b6), 0);
            UpdateSwatchForModelType(0xbc1041e6, civ->GetModelTypeKey(0xbc1041e6), 0);
            UpdateSwatchForModelType(0x2090a11b, civ->GetModelTypeKey(0x2090a11b), 0);
            UpdateSwatchForModelType(0xc15695da, civ->GetModelTypeKey(0xc15695da), 0);
            UpdateSwatchForModelType(0xf670aa43, civ->GetModelTypeKey(0xf670aa43), 0);
            UpdateSwatchForModelType(0x1a4e0708, civ->GetModelTypeKey(0x1a4e0708), 0);
            UpdateSwatchForModelType(0x2a5147a9, civ->GetModelTypeKey(0x2a5147a9), 0);
            if (inSpace)
                UpdateSwatchForModelType(0x98e03c0d, GetPlayerEmpire()->GetUFOKey(), 0);
            {
                const ResourceKey* key = city->GetMode()->FUN_00bebe10();
                UpdateSwatchForModelType(0x737d90f7, key, city->GetMode()->FUN_00bebe20());
            }

            if (mShoppingModelType != 0xffffffff) {
                bool notFromShopping = true;
                if (mbFromShopping)
                    notFromShopping = false;

                const Vector3* pos;
                if (mpCommunity) {
                    cCity* c;
                    if (GetCurrentGameMode() == kGameModeSpace &&
                        (c = object_cast<cCity>(mpCommunity, TYPE_cCity)) != 0 && c->GetCityHall())
                        pos = c->GetCityHall()->mSpatial.GetPosition();
                    else
                        pos = mpCommunity->GetPosition();
                } else {
                    pos = &g_Vector3Zero;
                }
                Vector3 target = *pos;
                if (FUN_00b3d280())
                    FUN_00b3d280()->FUN_00b13bb0(&target, true);
                FUN_00b3d280()->FUN_00b13b50();
                SetupShoppingUI(mShoppingModelType, *civ->GetModelTypeKey(mShoppingModelType), notFromShopping);
            }

            cSetCreationMsg msg(0);
            msg.mKey = *FUN_00401090()->FUN_004df400();
            MessageServer()->PostMSG(kMsgSetCreation, &msg, 0);
        }

        // ---- budget ----
        if (mpWinBudget) {
            mBudget = new ("Editor", 0, 0, 0, 0) cSPEditorBudget();
            if (mBudget) {
                ResourceKey layout(city ? 0x08a14cc8 : 0x734d3ba1, 0x510a95b, 0x40464100);
                cString title;
                const wchar_t* text = 0;
                if (budgetTitleID) {
                    title.Load(0xc0152a6d, budgetTitleID, 0);
                    text = title.GetText();
                }
                mBudget->Init(&layout, mEconomy, limitType, mpWinBudget, text);
            }
        }

        // ---- naming ----
        if (city) {
            mNaming = new ("Editor", 0, 0, 0, 0) cSPEditorNaming();
            mNaming->Init(community ? &community->mNameable : 0,
                          mEditorUI.FindWindowByID(0x272eb68e, true), 0x81c67b30, true, 0x58f4c251);
            cString prompt;
            if (GetPropertyAsText(mConfigProps, 0x53efdea, &prompt))
                mNaming->SetPrompt(prompt.GetText());
        }

        if (mSelectedCategoryID)
            FUN_00b3d230()->FUN_slot14(mSelectedCategoryID, true);
        MessageServer()->PostMSG(0x3e9a620, this, 0);
    }

    UpdateLimitMeter(mPaletteUI->FindCategoryIndex());
    mActiveAutoHandler.Register(MessageServer(), this, kCommunityEditorMessageIDs, 26);

    if (mpCommunity && object_cast<cTribe>(mpCommunity, TYPE_cTribe) && g_bCommunityEditorFirstActivate) {
        g_bCommunityEditorFirstActivate = false;
        intrusive_ptr<cActivateBehaviorMessage> msg(new ("App", 0, 0, 0, 0) cActivateBehaviorMessage());
        msg->mMessageID = 0x63bdfbe;
        msg->mField8 = -15;
        MessageServer()->PostMSG(msg->mMessageID, msg.get(), 0);
    }
}
