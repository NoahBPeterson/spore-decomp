// src/game/SPGonzago/SPUIGlobalUICiv.cpp -- migrated from slice(s) s00e033d0, s00bad7a0, s00bac830, s00baa930, s00ba9810 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIGlobalUICiv.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cStarManager.h"
#include <string.h>

// ---- items of slice s00ba9810 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSortTriple {                                                    // 12-byte sort / run key
    float mX;                                                           // +0x00
    float mY;                                                           // +0x04
    float mZ;                                                           // +0x08
};
// ---- items of slice s00ba9810 end

// ---- items of slice s00baa930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_array(void* p);            // 0x00f47380
extern "C" void* __cdecl RBTreeIncrement(void* node);               // 0x00921580
extern "C" void  __cdecl DoNukeSubtree(void* node);                 // 0x009a9600
#pragma warning(disable: 4100)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct RBNodeBase {
    RBNodeBase* mpNodeLeft;   // +0x00
    RBNodeBase* mpNodeRight;  // +0x04
    RBNodeBase* mpNodeParent; // +0x08
    u8          mColor;       // +0x0c
    u8          pad[3];
};
struct RBNode {
    RBNode* mpNodeLeft;   // +0x00
    RBNode* mpNodeRight;  // +0x04
    RBNode* mpNodeParent; // +0x08
    u8      mColor;       // +0x0c
    u8      pad[3];
    u32     first;        // +0x10  (pair.first)
    void*   second;       // +0x14
};
struct UnsignedVoidMap {
    char        mCompare[4];  // +0x00
    RBNodeBase  mAnchor;      // +0x04
    u32         mnSize;       // +0x14
    char        mAllocator;   // +0x18
};
struct EaWString {
    u32 mpBegin;   // +0x00
    u32 mpEnd;     // +0x04
    u32 mpCap;     // +0x08
};
struct cClassInfo {
    u32 mField00;   // +0x00
    u32 mField04;   // +0x04
    u32 mField08;   // +0x08
    u8  mField0C;   // +0x0c
    u8  mField0D;   // +0x0d
    u8  mField0E;   // +0x0e
    u8  mField0F;   // +0x0f
    u32 mField10;   // +0x10
    u32 mField14;   // +0x14
    u32 mField18;   // +0x18
    u32 mField1C;   // +0x1c

    cClassInfo& operator=(const cClassInfo& other);   // 0x00bab010
};
struct KeyVec {
    u32 mWords[5];  // 0x14 bytes
    KeyVec& operator=(const KeyVec& o);
};
void* __cdecl SP_PropertyManager();                                 // 0x0067de30
void  __cdecl FUN_00bf2c60(void* self);                             // 0x00bf2c60
void  __cdecl FUN_00bf4a60(u32 key, void* value);                   // 0x00bf4a60
int*  __cdecl Property_GetInt(void* prop);                          // 0x0041e990
void  __cdecl FUN_00c35310(void* self);                             // 0x00c35310
u8    __cdecl FUN_00ba9d60(void* a, void* b);                       // 0x00ba9d60
void* __cdecl FUN_006abf00();                                       // 0x006abf00
void  __cdecl FUN_00dd6740(void* a, void* b, u32 c);                // 0x00dd6740
void  __cdecl FUN_00579bd0(void* a, void* b, u32 c);                // 0x00579bd0
void  __cdecl EA_ConvertToString16(void* out, void* in, u32 n);     // 0x0093c5a0
u8    __cdecl FUN_00ba99f0(void* a, int b, void* c, void* d);       // 0x00ba99f0
u8    __cdecl FUN_00acaf80(void* a, int b, void* c, void* d);       // 0x00acaf80
void* __cdecl FUN_00b96130(void* a, void* b, void* c);              // 0x00b96130
void* __cdecl FUN_009360d0();                                       // 0x009360d0
void  __cdecl FUN_00bb9b00(int a, int b);                           // 0x00bb9b00
class cSPUILayoutManager_s00ba_a930 {
public:
    u8   pad_0000[0x64];
    u8   mField64;              // +0x64
    u8   pad_0065[0xc8 - 0x65];
    void* mListBegin;           // +0xc8
    void* mListEnd;             // +0xcc
    u8   pad_00d0[0x104 - 0xd0];
    void* mVecBegin;            // +0x104
    void* mVecEnd;              // +0x108
    u8   pad_010c[0x150 - 0x10c];
    UnsignedVoidMap mWorlds;    // +0x150
    u8   pad_016c[0x1d8 - 0x16c];
    int  mFeedbackID;           // +0x1d8
    u8   pad_01dc[0x224 - 0x1dc];
    void* mSetA;                // +0x224
    void* mSetB;                // +0x228

    void ReadCameraConfig();    // 0x00baa930
    void ShuffleEvents();       // 0x00baac30
    u8   MergeFeedback();       // 0x00baad00
};
struct SerializerVT {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();
    virtual void v24();
    virtual void v28(u32 key, void** out, int b);
};
struct SerReaderVT {
    virtual void r00();
    virtual void r04();
    virtual void r08();
    virtual void r0c();
    virtual void r10();
    virtual void r14();
    virtual void r18(void* out, int n, int b);
};
struct WriterVT {
    virtual void Begin(const wchar_t* name);
    virtual void End(const wchar_t* name);
};
void __cdecl wstr_RangeInitialize(void* self, int n);                // 0x00579a90
void __cdecl wstr_Ctor(void* self, const void* other);               // 0x0056e2d0
// ---- items of slice s00baa930 end

// ---- items of slice s00bac830 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Key { uint32_t a, b, c; };                       // EA::ResourceMan::Key, 12 bytes
void __cdecl FreeBlock(void* p);                        // 0xf47380  operator_delete_array
struct KeyVec_s00ba_c830 {                                         // eastl::vector<Key, sp_vector_allocator>
    Key* mBegin;                                        // +0x00
    Key* mEnd;                                          // +0x04
    Key* mCap;                                          // +0x08
    Key* erase(Key* first, Key* last);                  // 0x50f740
    void DoInsertValue(Key* pos, const Key& v);         // 0x4e3e10
    void push_back(const Key& v) {
        if (mEnd < mCap) { Key* p = mEnd; mEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mEnd, v);
    }
    void clear() { erase(mBegin, mEnd); }
    ~KeyVec_s00ba_c830() { if (mBegin && ((int*)mBegin)[-1] != 0) FreeBlock(mBegin); }
};
struct Species { uint32_t FUN_00b8f860(); };            // 0xb8f860 (this = species)
struct SpeciesManager { Species* FUN_00b90410(const Key& id); };       // 0xb90410
SpeciesManager* FUN_00b3d420();                         // 0xb3d420
struct Random { uint32_t FUN_00a68fb0(uint32_t max); }; // 0xa68fb0
extern Random g_mathRandom;                             // 0x1601760
static inline uint32_t Rnd(uint32_t max) { return g_mathRandom.FUN_00a68fb0(max); }
struct Profile { char pad[0x608]; int m608; };          // cSpeciesProfile, flag at +0x608
struct ProfileMgr { Profile* FUN_004df550(const Key& k); };            // 0x4df550
ProfileMgr* FUN_00401090();                             // 0x401090
struct Obj10a0 { char pad[0x504]; Key mKey; };          // key at +0x504
struct Obj3d450 { Obj10a0* FUN_00ac10a0(); };           // 0xac10a0 (this = b3d450 result)
Obj3d450* FUN_00b3d450(uint32_t k);                     // 0xb3d450
static inline uint32_t DrawIndex(Key* begin, Key* end)
{
    uint32_t n = (uint32_t)(end - begin);
    return (n < 2) ? 0 : Rnd(n);
}
struct IntVec {                                         // eastl::vector<int, sp_vector_allocator>
    int* mBegin;                                        // +0x00
    int* mEnd;                                          // +0x04
    int* mCap;                                          // +0x08
    void DoInsertValue(int* pos, const int& v);         // 0xb96600
    void push_back(const int& v) {
        if (mEnd < mCap) { int* p = mEnd; mEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mEnd, v);
    }
    void erase(int* pos) {
        int* end = mEnd;
        for (int* p = pos; p + 1 != end; ++p) *p = *(p + 1);
        mEnd = end - 1;
    }
    ~IntVec() { if (mBegin && ((int*)mBegin)[-1] != 0) FreeBlock(mBegin); }
};
struct RefCount { virtual void v00(); virtual void Release(); };       // +0x04
struct PropMgr {
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
    virtual bool Lookup(uint32_t a, uint32_t b, RefCount** out);       // slot 0x2c
    virtual void LookupRefs(uint32_t a, uint32_t b, KeyVec_s00ba_c830* out);      // slot (used by bad080)
};
PropMgr* PropertyManager();                             // 0x67de30
struct Obj080 { virtual Key* GetKey(); };               // vtable +0x18 -> Key*
struct RBTree { char pad[4]; void* mHead; void* mRoot; };// +0x04 header, +0x08 root
RBTree* FUN_006b42e0();                                 // 0x6b42e0
Key* FUN_00b8d8e0();                                    // 0xb8d8e0
void FUN_00baa080(KeyVec_s00ba_c830* v);                           // 0xbaa080
int FUN_00ba6ab0(int* p);                               // 0xba6ab0
struct Obj440 {
    char pad0[0x28];
    int  m28;                                           // +0x28 (3/4/5)
    char pad2c[0xbc - 0x2c];
    KeyVec_s00ba_c830 mBc;                                         // +0xbc
    char padC8[0xd0 - 0xc8];
    KeyVec_s00ba_c830 mD0;                                         // +0xd0
};
struct Cfg440 {
    char    pad0c[0x0c];
    uint8_t m0c;                                        // +0x0c
    char    pad0d[3];
    int     m10;                                        // +0x10 bitmask / value
    int     m14;                                        // +0x14
    int     m18;                                        // +0x18
    int     m1c;                                        // +0x1c
    KeyVec_s00ba_c830  m20;                                        // +0x20
    KeyVec_s00ba_c830  m34;                                        // +0x34
};
static inline int ClampHi(int v, int hi) { return (v > hi) ? hi : v; }
struct Self440 {                            // incoming ecx: unused `this` (thiscall)
    void FUN_00bad440(Obj440* param_1, Cfg440* param_2);
};
// ---- items of slice s00bac830 end

// ---- items of slice s00bad7a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int32_t gCheatStarCount;                 // 0x0168964c
#define nullptr 0
class IGameObject {
public:
    virtual void* Slot00();                         // +0x000
    virtual void Release();                         // +0x004
    virtual void Release2();                        // +0x008
    virtual void* Slot0c();
    virtual void* Slot10();                         // +0x010
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
};
class IRefCounted {
public:
    virtual void* Slot00();                         // +0x000
    virtual void Release();                         // +0x004
    virtual void Release2();                        // +0x008
};
class cGonzagoSubsystem {
public:
    cGonzagoSubsystem();                            // 0x00b5b960
    virtual void Slot00();
    virtual void Slot04();
    uint8_t mPad00[0x18];       // +0x004
};
class cCivilization;
class cGameNounManager {
public:
    void RemoveNounsOfType(int32_t nType);          // 0x00b22650
};
class cSPBackgroundSimManager {
public:
    uint8_t mPad00[0x08];       // +0x00
    IRefCounted* mpIdleState;   // +0x08
};
extern cSPBackgroundSimManager* gspBackgroundSimManager;    // 0x016dda8c
struct Vector3 {
    float x;
    float y;
    float z;
};
class WString {
public:
    void Assign(const wchar_t* pFirst, const wchar_t* pLast);   // 0x00423650
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
};
class FeedbackNode {
public:
    FeedbackNode* mpLeft;       // +0x00
    FeedbackNode* mpRight;      // +0x04
    FeedbackNode* mpParent;     // +0x08
    bool mbRed;                 // +0x0c
    uint8_t mPad0d[0x03];       // +0x0d
    uint32_t mnKey;             // +0x10
    IRefCounted* mpValue;       // +0x14
};
struct MapIterator {
    FeedbackNode* mpNode;       // +0x00
};
class RbTree {
public:
    uint8_t mPad00[0x04];       // +0x00  (allocator word)
    FeedbackNode* mpAnchor;     // +0x04  (self-referencing end node)
    uint8_t mPad08[0x04];       // +0x08
    FeedbackNode* mpRoot;       // +0x0c
    uint32_t mnSize;            // +0x10
};
class CivCounterMap {
public:
    uint32_t& GetCounter(cCivilization* pKey);      // 0x00badea0
    void DoInsertValue(FeedbackNode* pParent, const uint32_t* pKey,
                       uint32_t nValue);            // 0x00baa660

    RbTree mTree;               // +0x00
};
class FeedbackMap {
public:
    MapIterator Find(const uint32_t& rKey);         // 0x00e5c780

    RbTree mTree;               // +0x00
};
class cStarAgentRecord {
public:
    uint8_t mPad00[0x3c];       // +0x000
    bool mbActive;              // +0x03c
    IRefCounted* mpEffect;      // +0x040
    uint8_t mPad44[0x1c];       // +0x044
    WString mName;              // +0x060
};
class cBanner {
public:
    uint8_t mPad00[0x40];       // +0x000
    IGameObject* mpOwner;       // +0x040
};
void __cdecl operator_delete(void* pBlock);                             // 0x00f47380
cGameNounManager* __cdecl NounManager();                                // 0x00b3d300
IGameObject* __cdecl SaveLoadManager();                                 // 0x00fd9c60
void* __cdecl ChildGetSomething(uint32_t nPrompt);                      // 0x00401090
void* __cdecl FUN_006b42e0(void* pObject);                              // 0x006b42e0
uint32_t __cdecl FUN_00b8d8f0(void);                                    // 0x00b8d8f0
void* __cdecl FUN_00ba6d80(uint32_t nA);                                // 0x00ba6d80
uint32_t __cdecl GetItemInstanceID(void* pItem);                        // 0x00c87040
int32_t __cdecl FUN_00b8dab0(void);                                     // 0x00b8dab0
void __cdecl FUN_00ba7bd0(void* pCfg);                                  // 0x00ba7bd0
void __cdecl FUN_00bab010(void* pCfg, void* pArg);                      // 0x00bab010
bool __cdecl FUN_00bb9af0(void* pItem, int32_t nFlags);                 // 0x00bb9af0
void __cdecl FUN_00bad440(void* pSelf, void* pObject, void* pCfg);      // 0x00bad440
void __cdecl FUN_00ba8220(void* pCfg);                                  // 0x00ba8220
void __cdecl FUN_00bb9b90(void* pA);                                    // 0x00bb9b90
void __cdecl FUN_00bb9ad0(int32_t nA);                                  // 0x00bb9ad0
void __cdecl FUN_00bb9b00(int32_t nA, int32_t nB);                      // 0x00bb9b00
void* __cdecl FUN_00bbaa60(int32_t nA);                                 // 0x00bbaa60
void __cdecl FUN_00c86e50();                                            // 0x00c86e50
void __cdecl FUN_004df3e0(void* pObject);                               // 0x004df3e0
void __cdecl CopyImpl_0(void* pFirst, void* pLast, void* pOut);         // 0x006782c0
void __cdecl RBTreeErase(FeedbackNode* pNode, void* pAnchor);           // 0x00921880
template <class T>
static int32_t EraseAllPointers(T** pBegin, T** pLast, T** pEnd)
{
    memcpy(pBegin, pLast, (size_t)((char*)pEnd - (char*)pLast));
    return (int32_t)(pBegin - pEnd);
}
class cStarManager : public cGonzagoSubsystem {
public:
    cStarManager();                                         // 0x00bae490
    void EraseFeedback(void* pEvent);                       // 0x00bad7a0
    void Reset();                                           // 0x00bad810
    void Shutdown();                                        // 0x00bad8d0
    void LoadFromObject(void* pObject);                     // 0x00bad940
    void UpdateVisibility(void* pStar, void* pPlanet, float fNear, float fFar,
                          const Vector3* pOffset);          // 0x00badae0
    void UpdateItem(void* pItem, void* pConfig);            // 0x00badd10
    void Cheat(void* pArguments);                           // 0x00bae130

    uint8_t mPad1c[0x08];           // +0x01c
    cStarManager* mpListSelf;       // +0x024
    int32_t mnState;                // +0x028
    uint32_t mnFlags;               // +0x02c
    bool mbLoaded;                  // +0x030
    uint8_t mPad31[0x03];           // +0x031
    IRefCounted* mpPending;         // +0x034
    uint8_t mPad38[0x04];           // +0x038
    cBanner** mppBanners;           // +0x03c
    cBanner** mppBannersEnd;        // +0x040
    Vector3 mOffset;                // +0x044
    cStarAgentRecord** mppAgents;   // +0x050
    cStarAgentRecord** mppAgentsEnd;// +0x054
    uint8_t mPad58[0x0c];           // +0x058
    bool mbVisible;                 // +0x064
    uint8_t mPad65[0x07];           // +0x065
    WString mWorldName;             // +0x06c
    uint8_t mPad78[0x64];           // +0x078
    IRefCounted** mppThreats;       // +0x0dc
    IRefCounted** mppThreatsEnd;    // +0x0e0
    uint8_t mPadE4[0x68];           // +0x0e4
    uint8_t* mpHandleTable;         // +0x14c
    FeedbackMap mFeedback;          // +0x150
    uint8_t mPad168[0x74];          // +0x168
    IRefCounted* mpCurrentItem;     // +0x1dc
    uint8_t mPad1e0[0x08];          // +0x1e0
    int32_t mnItemCount;            // +0x1e8
    uint8_t mPad1ec[0x30];          // +0x1ec
};
// ---- items of slice s00bad7a0 end

// ---- items of slice s00e033d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void  (__thiscall* TFnVII)(void*, int, int);
#define VT(o, off) (*(void***)(o))[(off) / 4]
struct wstring {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08

    void __thiscall Assign(const wchar_t* first, const wchar_t* last); // 0x423650
    void __thiscall AllocateSelf(int n);                               // 0x429760
    void __thiscall RangeInit(const wchar_t* str);                     // 0x579a90
    void __thiscall Destroy();                                         // 0x5725a0
};
struct BanVec;
struct BanEntry {
    int     miId;      // +0x00
    wstring mName;     // +0x04
    int     miUnk10;   // +0x10
    wstring mText;     // +0x14
    int     miExtra;   // +0x20

    BanEntry* __thiscall CopyFrom(const BanEntry& src);   // 0x00e03830
};
struct BanVec {
    BanEntry* mpBegin;   // +0x00
    BanEntry* mpEnd;     // +0x04
    BanEntry* mpCap;     // +0x08

    BanEntry* __thiscall EraseLast(BanEntry* pos);                    // 0x00e03c30
    BanEntry* __thiscall Insert(BanEntry* pos, const BanEntry& val);  // 0x00e03ca0
};
struct BanTranslator {
    void*    mpVtbl;     // +0x00
    int      miUnk04;    // +0x04
    char     mbActive;   // +0x08 (BanContent+0x0c)
    char     mbHold;     // +0x09 (BanContent+0x0d)
    short    miPad0A;    // +0x0a
    int      miId;       // +0x0c
    wstring  mText;      // +0x10
    int      miUnk1C;    // +0x1c
    wstring  mExtra;     // +0x20
    int      miUnk2C;    // +0x2c
    BanVec   mList;      // +0x30

    bool __thiscall Format(const wchar_t* key, wchar_t* out);      // 0x00e03b80
};
struct BanContent {
    void*         mpVtbl;    // +0x00
    BanTranslator mTokens;   // +0x04

    void __thiscall Dtor();                     // 0x00e03930
    void __thiscall SetText(int id, const wchar_t* text, const void* extras); // 0x00e03590
    void __thiscall OnDeactivate(int a, int b); // 0x00e03e10
    void __thiscall OnToggle(char on);          // 0x00e03f40
    void __thiscall AddRow(int id, const wchar_t* name, const wchar_t* text); // 0x00e03e50
    void __thiscall Reactivate();               // 0x00e02e80 (external)
};
struct UIMessage {
    int miPad00;   // +0x00
    int miPad04;   // +0x04
    int miType;    // +0x08
    int miId;      // +0x0c
    int miSub;     // +0x10
    int miFlag;    // +0x14
};
struct cSPUIGlobalOptions {
    int   miPad00[3];   // +0x00
    int   miType;       // +0x0c
    int   miId;         // +0x10
    int   miSub;        // +0x14

    void __thiscall Reactivate();                        // 0x00e02e80
    void __thiscall Enable(int on);                      // 0x00e018c0
    bool __thiscall HandleMessage(int arg, UIMessage* msg); // 0x00e039d0
};
struct cSPUILayout_s00e0_33d0;
struct cSPUIGlobalUI {
    void*            mpVtbl;        // +0x00
    cSPUIGlobalOptions* mpOptions;  // +0x04
    cSPUILayout_s00e0_33d0*     mpLayout;      // +0x08
    BanContent       mBan;          // +0x0c
    int              miPad4C;       // +0x4c
    int              miPad50;       // +0x50
    void*            mpHandler;     // +0x54
    void*            mpHandlerThis; // +0x58
    int              miHandlerTag;  // +0x5c
    int              miHandlerCount;// +0x60
    int              miHandlerExtra;// +0x64

    bool __thiscall Init(int param);                                // 0x00e03620
    bool __thiscall Shutdown();                                     // 0x00e03740
    void* __thiscall Construct();                                   // 0x00e03ab0
    void __thiscall Destroy();                                      // 0x00e03b20
    void* __thiscall FindWindowByID(unsigned id);                   // 0x00e012b0
    void __thiscall ShowOptionWindows(char on);                     // 0x00e042d0
    bool __thiscall HandleMessage(unsigned msg, int arg);           // 0x00e03f80
    bool __thiscall AnyCivSlotUsed();                               // 0x00e042b0
    void* __thiscall AsInterface(unsigned id);                      // 0x00e04270
};
// ---- items of slice s00e033d0 end

// @ 0x00baa810
cSortTriple* PartitionTriples(cSortTriple* pFirst, cSortTriple* pLast, cSortTriple value, char (*pPredicate)(const cSortTriple*, const cSortTriple*))
{
    for (;;) {
        while (pPredicate(pFirst, &value)) ++pFirst;
        --pLast;
        while (pPredicate(&value, pLast)) --pLast;
        if (pFirst >= pLast) return pFirst;
        cSortTriple saved = *pFirst;
        *pFirst = *pLast;
        *pLast = saved;
        ++pFirst;
    }
}

// @ 0x00baa930
void cSPUILayoutManager_s00ba_a930::ReadCameraConfig()
{
    u8* p = (u8*)this;
    void* mgr = SP_PropertyManager();
    mgr = mgr;                             // PropertyManager() result kept for the vtbl call
    (*(void(__thiscall*)(void*, u32, u32))((void**)*(void**)mgr)[0x2c / 4])(mgr, 0x280852f1u, 0x2ae0c7eu);

    int   val = 0;
    void* propMap = p;                     // no-op guard mirroring the original's local
    propMap = propMap;
    FUN_00bf2c60((char*)p);                // build the local property map

    void* ctx = p;                         // this property-manager interface (reloaded)
    int v1 = 0;
    if (ctx != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx)[0x24 / 4])(ctx, &propMap, 0x4ea8f1au)) {
            // value kind check: word at prop+0x12 == 9
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v1 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple1[3];
    triple1[0] = (u32)v1;
    triple1[1] = 0x2399be55u;
    triple1[2] = 0x40636200u;
    FUN_00bf4a60(0x99e92f05u, triple1);

    void* ctx2 = p;
    int v2 = 0;
    if (ctx2 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx2)[0x24 / 4])(ctx2, &propMap, 0x65cce6du)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v2 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple2[3];
    triple2[0] = (u32)v2;
    triple2[1] = 0x2399be55u;
    triple2[2] = 0x40636200u;
    FUN_00bf4a60(0x4e3f7777u, triple2);

    void* ctx3 = p;
    int v3 = 0;
    if (ctx3 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx3)[0x24 / 4])(ctx3, &propMap, 0x65cce70u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v3 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple3[3];
    triple3[0] = (u32)v3;
    triple3[1] = 0x2399be55u;
    triple3[2] = 0x40636200u;
    FUN_00bf4a60(0x47c10953u, triple3);

    void* ctx4 = p;
    int v4 = 0;
    if (ctx4 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx4)[0x24 / 4])(ctx4, &propMap, 0x65cce73u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v4 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple4[3];
    triple4[0] = (u32)v4;
    triple4[1] = 0x2399be55u;
    triple4[2] = 0x40636200u;
    FUN_00bf4a60(0x72c49181u, triple4);

    void* ctx5 = p;
    int v5 = 0;
    if (ctx5 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx5)[0x24 / 4])(ctx5, &propMap, 0x65cf1b6u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v5 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple5[3];
    triple5[0] = (u32)v5;
    triple5[1] = 0x24682294u;
    triple5[2] = 0x40646200u;
    FUN_00bf4a60(0xbc1041e6u, triple5);

    void* ctx6 = p;
    int v6 = 0;
    if (ctx6 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx6)[0x24 / 4])(ctx6, &propMap, 0x65e3a82u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v6 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple6[3];
    triple6[0] = (u32)v6;
    triple6[1] = 0x24682294u;
    triple6[2] = 0x40646200u;
    FUN_00bf4a60(0x2090a11bu, triple6);

    void* ctx7 = p;
    int v7 = 0;
    if (ctx7 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx7)[0x24 / 4])(ctx7, &propMap, 0x65e3a85u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v7 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple7[3];
    triple7[0] = (u32)v7;
    triple7[1] = 0x24682294u;
    triple7[2] = 0x40646200u;
    FUN_00bf4a60(0xc15695dau, triple7);

    if (*(int*)((char*)p + 0x1d8) != -1) {
        // eastl map find at this+0x150 with the key just read
        RBNode* n = (RBNode*)((UnsignedVoidMap*)((char*)p + 0x150))->mAnchor.mpNodeLeft;
        (void)n;
    }
    FUN_00c35310((char*)p + 0x68);
    DoNukeSubtree(*(void**)((char*)p + 0x74));
    if (ctx != 0) {
        (*(void(__thiscall*)(void*))((void**)*(void**)ctx)[4 / 4])(ctx);
    }
}

// @ 0x00baac30
void cSPUILayoutManager_s00ba_a930::ShuffleEvents()
{
    u8* p = (u8*)this;
    FUN_00b96130(*(void**)((char*)p + 0x104), *(void**)((char*)p + 0x108), (void*)0x1601760);
    int n = (int)(*(int*)((char*)p + 0x108) - *(int*)((char*)p + 0x104)) >> 2;
    for (int i = 0; i < n; i++) {
        u32 r = (u32)(size_t)FUN_009360d0();
        u32 idx = r % (u32)n;
        u32 tmp = *(u32*)(*(int*)((char*)p + 0x104) + i * 4);
        *(u32*)(*(int*)((char*)p + 0x104) + i * 4) = *(u32*)(*(int*)((char*)p + 0x104) + idx * 4);
        *(u32*)(*(int*)((char*)p + 0x104) + idx * 4) = tmp;
    }
    int m = (int)(*(int*)((char*)p + 0x110) - *(int*)((char*)p + 0x10c)) >> 2;
    FUN_00bb9b00(0x400, m);
}

// @ 0x00baad00
u8 cSPUILayoutManager_s00ba_a930::MergeFeedback()
{
    u8* p = (u8*)this;
    if (*(char*)((char*)p + 0x64) != 0) {
        return 1;
    }
    if (*(int*)((char*)p + 0x228) == 0) {
        return 1;
    }

    // local raster/scratch list built around +0x2c
    u32 listHead[2];
    listHead[0] = 0x13eb428u;        // ~list anchor sentinel
    listHead[1] = 0x5220cb8u;
    void* self2 = listHead;
    (void)self2;
    FUN_00c35310(listHead);

    void* generator = FUN_006abf00();
    (*(void(__thiscall*)(void*, void*, void*))((void**)*(void**)generator)[0x24 / 4])(generator, listHead, listHead);

    // gather the "read" set from this+0x224
    u32 setA[3];
    setA[0] = 0; setA[1] = 0; setA[2] = 0;
    (*(void(__thiscall*)(void*, u32*, int))((void**)*(void**)*(void**)((char*)p + 0x224))[0x30 / 4])
        (*(void**)((char*)p + 0x224), setA, 0);

    // gather the "write" set from this+0x228
    u32 setB[3];
    setB[0] = 0; setB[1] = 0; setB[2] = 0;
    (*(void(__thiscall*)(void*, u32*, int))((void**)*(void**)*(void**)((char*)p + 0x228))[0x30 / 4])
        (*(void**)((char*)p + 0x228), setB, 0);

    int count = (*(int*)((char*)p + 0xcc) - *(int*)((char*)p + 0xc8)) / 0x14;
    for (int row = 0; row < count; row++) {
        u8* entry = (u8*)(*(int*)((char*)p + 0xc8) + row * 0x14);
        int* v0 = *(int**)entry;
        int  n0 = (*(int*)(entry + 4) - (int)v0) >> 2;
        for (int j = 0; j < n0; j++) {
            int* item = *(int**)((char*)v0 + j * 4);
            u32 name = *(u32*)((char*)item + 0xac);
            for (u32 k = 0; k < name; k++) {
                int key = *(int*)((char*)item + 0x70) + k * 0x1000000;
                if (FUN_00ba9d60(*(void**)((char*)p + 0x224), &key)) {
                    break;
                }
                if (FUN_00ba9d60(*(void**)((char*)p + 0x228), &key)) {
                    break;
                }
            }
        }
    }

    if (setA[0]) {
        // release
        void* v = (void*)setA[0];
        if (v) (*(void(__thiscall*)(void*))((void**)*(void**)v)[4 / 4])(v);
    }
    if (setB[0]) {
        void* v = (void*)setB[0];
        if (v) (*(void(__thiscall*)(void*))((void**)*(void**)v)[4 / 4])(v);
    }
    // erase the scratch list
    (*(void(__thiscall*)(void*, void*))0x75f3f0)(listHead, listHead);
    return 1;
}

// @ 0x00bab010
cClassInfo& cClassInfo::operator=(const cClassInfo& other)
{
    mField00 = other.mField00;
    mField04 = other.mField04;
    mField08 = other.mField08;
    mField0C = other.mField0C;
    mField0D = other.mField0D;
    mField0E = other.mField0E;
    mField0F = other.mField0F;
    mField10 = other.mField10;
    mField14 = other.mField14;
    mField18 = other.mField18;
    mField1C = other.mField1C;
    *(KeyVec*)((char*)this + 0x20) = *(const KeyVec*)((const char*)&other + 0x20);
    *(KeyVec*)((char*)this + 0x34) = *(const KeyVec*)((const char*)&other + 0x34);
    return *this;
}

// @ 0x00bab080
void FUN_00bab080(SerializerVT* ser, void* tree)
{
    u8* t = (u8*)tree;
    DoNukeSubtree(*(void**)((char*)t + 0xc));
    u32 anchor = (u32)((char*)t + 4);
    *(u32*)((char*)t + 4)  = anchor;
    *(u32*)((char*)t + 8)  = anchor;
    *(u32*)((char*)t + 0xc)  = 0;
    *(u8*)((char*)t + 0x10)  = 0;
    *(u32*)((char*)t + 0x14) = 0;

    u32 count = 0;
    {
        void* a = ser->v20();
        ((SerReaderVT*)a)->r18(&count, 1, 0);
    }
    for (u32 i = 0; i < count; i++) {
        void* ref = 0;
        u32 key = 0;
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&key, 1, 0);
        }
        ser->v1c();
        if (ref != 0) {
            ref = 0;
        }
        ser->v28(0x3e4353bu, &ref, 0);
        ser->v1c();
        u32 packed = 0;
        FUN_00dd6740(&tree, &key, packed);
    }
    ser->v1c();
}

// @ 0x00bab200
void FUN_00bab200(SerializerVT* ser, void* tree)
{
    u8* t = (u8*)tree;
    DoNukeSubtree(*(void**)((char*)t + 0xc));
    u32 anchor = (u32)((char*)t + 4);
    *(u32*)((char*)t + 4)  = anchor;
    *(u32*)((char*)t + 8)  = anchor;
    *(u32*)((char*)t + 0xc)  = 0;
    *(u8*)((char*)t + 0x10)  = 0;
    *(u32*)((char*)t + 0x14) = 0;

    u32 count = 0;
    {
        void* a = ser->v20();
        ((SerReaderVT*)a)->r18(&count, 1, 0);
    }
    for (u32 i = 0; i < count; i++) {
        void* ref = 0;
        u32 key = 0;
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&key, 1, 0);
        }
        ser->v1c();
        if (ref != 0) {
            ref = 0;
        }
        ser->v28(0x1805e75u, &ref, 0);
        ser->v1c();
        u32 packed = 0;
        FUN_00dd6740(&tree, &key, packed);
    }
    ser->v1c();
}

// @ 0x00bab380
u8 FUN_00bab380(char* self, int arg1, int* list)
{
    // self is the serializer interface at caller's param_1 (a char* whose vtbl[0]/[4] are used)
    WriterVT* w = (WriterVT*)self;
    u8 result = 1;
    if (*list == list[1]) {
        return result;
    }

    // Build the field-name wstring from arg1.
    EaWString tmpA;
    EaWString tmpB;
    int flag = 0;
    u8  ok = 1;
    if (arg1 != 0) {
        EA_ConvertToString16(&tmpA, (void*)arg1, 0xffffffffu);
        flag = 1;
    } else {
        tmpA.mpBegin = 0; tmpA.mpEnd = 0; tmpA.mpCap = 0;
        wstr_RangeInitialize(&tmpA, 0);
        flag = 2;
    }
    wstr_Ctor(&tmpB, &tmpA);
    if ((flag & 2) && (((int)((tmpA.mpEnd - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
        flag &= ~2;
    }
    if ((flag & 1) && (((int)((tmpA.mpCap - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
    }

    const wchar_t* name = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->Begin(name);

    int end = *(int*)((char*)&list + 4);
    ok = 1;
    for (int it = *list; it != end; it += 0x10) {
        if (ok) {
            u8 r = FUN_00ba99f0((void*)self, 0, (void*)it, (void*)L"EA::String8");
            ok = r ? 1 : 0;
        }
    }

    const wchar_t* name2 = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->End(name2);
    if (((int)((tmpB.mpCap - tmpB.mpBegin) & 0xfffffffeu)) > 2 && tmpB.mpBegin != 0) {
        operator_delete_array((void*)tmpB.mpBegin);
    }
    return ok;
}

// @ 0x00bab4d0
u8 FUN_00bab4d0(char* self, int arg1, int* list)
{
    WriterVT* w = (WriterVT*)self;
    u8 result = 1;
    if (*list == list[1]) {
        return result;
    }

    EaWString tmpA;
    EaWString tmpB;
    int flag = 0;
    u8  ok = 1;
    if (arg1 != 0) {
        EA_ConvertToString16(&tmpA, (void*)arg1, 0xffffffffu);
        flag = 1;
    } else {
        tmpA.mpBegin = 0; tmpA.mpEnd = 0; tmpA.mpCap = 0;
        wstr_RangeInitialize(&tmpA, 0);
        flag = 2;
    }
    wstr_Ctor(&tmpB, &tmpA);
    if ((flag & 2) && (((int)((tmpA.mpEnd - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
        flag &= ~2;
    }
    if ((flag & 1) && (((int)((tmpA.mpCap - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
    }

    const wchar_t* name = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->Begin(name);

    int end = *(int*)((char*)&list + 4);
    ok = 1;
    for (int it = *list; it != end; it += 0x10) {
        if (ok) {
            u8 r = FUN_00acaf80((void*)self, 0, (void*)it, (void*)L"EA::String16");
            ok = r ? 1 : 0;
        }
    }

    const wchar_t* name2 = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->End(name2);
    if (((int)((tmpB.mpCap - tmpB.mpBegin) & 0xfffffffeu)) > 2 && tmpB.mpBegin != 0) {
        operator_delete_array((void*)tmpB.mpBegin);
    }
    return ok;
}

// @ 0x00bab620
void FUN_00bab620(SerializerVT* ser, void* tree)
{
    u8* t = (u8*)tree;
    DoNukeSubtree(*(void**)((char*)t + 0xc));
    u32 anchor = (u32)((char*)t + 4);
    *(u32*)((char*)t + 4)  = anchor;
    *(u32*)((char*)t + 8)  = anchor;
    *(u32*)((char*)t + 0xc)  = 0;
    *(u8*)((char*)t + 0x10)  = 0;
    *(u32*)((char*)t + 0x14) = 0;

    u32 count = 0;
    {
        void* a = ser->v20();
        ((SerReaderVT*)a)->r18(&count, 1, 0);
    }
    for (u32 i = 0; i < count; i++) {
        u32 key = 0, val = 0;
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&key, 1, 0);
        }
        ser->v1c();
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&val, 1, 0);
        }
        ser->v1c();
        u32 kv[2];
        kv[0] = key;
        kv[1] = val;
        FUN_00579bd0(&tree, kv, 0);
        *(u32*)((char*)tree + 0x14) = val;
    }
    ser->v1c();
}

// @ 0x00bab740
u8 FUN_00bab740(char* self, int* tree)
{
    WriterVT* w = (WriterVT*)self;
    u8 result = 1;
    if (tree[5] == 0) {           // +0x14 size
        return result;
    }

    EaWString tmpA;
    EaWString tmpB;
    int flag = 0;
    if (tree != 0) {
        EA_ConvertToString16(&tmpA, (void*)tree, 0xffffffffu);
        flag = 1;
    } else {
        tmpA.mpBegin = 0; tmpA.mpEnd = 0; tmpA.mpCap = 0;
        wstr_RangeInitialize(&tmpA, 0);
        flag = 2;
    }
    wstr_Ctor(&tmpB, &tmpA);
    if ((flag & 2) && (((int)((tmpA.mpEnd - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
        flag &= ~2;
    }
    if ((flag & 1) && (((int)((tmpA.mpCap - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
    }

    const wchar_t* name = (tmpB.mpBegin == tmpB.mpEnd) ? L"map" : (const wchar_t*)tmpB.mpBegin;
    w->Begin(name);

    u8 ok = 1;
    void* anchor = (char*)tree + 4;
    void* node = *(void**)((char*)tree + 8);
    if (node != anchor) {
        do {
            if (ok) {
                u8 r = FUN_00ba99f0((void*)self, 0, (char*)node + 0x14, (void*)L"uint32_t");
                ok = r ? 1 : 0;
            }
            node = RBTreeIncrement(node);
        } while (node != anchor);
    }

    const wchar_t* name2 = (tmpB.mpBegin == tmpB.mpEnd) ? L"map" : (const wchar_t*)tmpB.mpBegin;
    w->End(name2);
    if (((int)((tmpB.mpCap - tmpB.mpBegin) & 0xfffffffeu)) > 2 && tmpB.mpBegin != 0) {
        operator_delete_array((void*)tmpB.mpBegin);
    }
    return ok;
}

// @ 0x00bac830
void __stdcall FUN_00bac830(KeyVec_s00ba_c830* inList, int param_2, int param_3, int mode, char flag, KeyVec_s00ba_c830* out)
{
    out->clear();
    SpeciesManager* mgr = FUN_00b3d420();

    KeyVec_s00ba_c830 vA = { 0, 0, 0 };        // hash 0x6d60a1cc
    KeyVec_s00ba_c830 vB = { 0, 0, 0 };        // hash 0x29c388a
    KeyVec_s00ba_c830 vC = { 0, 0, 0 };        // hash 0x3a8be428

    for (Key* it = inList->mBegin; it != inList->mEnd; ++it) {
        Species* sp = mgr->FUN_00b90410(*it);
        if (sp) {
            uint32_t h = sp->FUN_00b8f860();
            if (h == 0x29c388a) vB.push_back(*it);
            else if (h == 0x3a8be428) vC.push_back(*it);
            else if (h == 0x6d60a1cc) vA.push_back(*it);
        }
    }

    uint32_t r = Rnd(3);
    bool b3 = (mode == 3) || (mode == 2 && r != 0) || (mode == 1 && r == 0);
    bool b2 = (mode == 3) || (mode == 2 && r != 1) || (mode == 1 && r == 1);
    bool b1 = (mode == 3) || (mode == 2 && r != 2) || (mode == 1 && r == 2);

    int n1 = param_2;
    if (flag == 0 && !b1 && (b2 || b3)) n1 = param_3;

    int c1 = 0;
    for (; c1 < n1; ++c1) {                     // phase 1: vC
        if (vC.mBegin == vC.mEnd) break;
        Key* chosen = vC.mBegin + Rnd((uint32_t)(int)(vC.mEnd - vC.mBegin));
        out->push_back(*chosen);
        Key* end = vC.mEnd;
        for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
        vC.mEnd = end - 1;
    }

    int n2 = param_2;
    if (flag == 0 && !b2 && (c1 == param_2 || b3)) n2 = param_3;

    int c2 = 0;
    for (; c2 < n2; ++c2) {                     // phase 2: vB
        if (vB.mBegin == vB.mEnd) break;
        Key* chosen = vB.mBegin + Rnd((uint32_t)(int)(vB.mEnd - vB.mBegin));
        out->push_back(*chosen);
        Key* end = vB.mEnd;
        for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
        vB.mEnd = end - 1;
    }

    int n3 = param_2;
    if (flag == 0 && !b3 && (c2 == param_2 || c1 == param_2)) n3 = param_3;

    for (int c3 = 0; c3 < n3; ++c3) {           // phase 3: vA
        if (vA.mBegin == vA.mEnd) break;
        Key* chosen = vA.mBegin + Rnd((uint32_t)(int)(vA.mEnd - vA.mBegin));
        out->push_back(*chosen);
        Key* end = vA.mEnd;
        for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
        vA.mEnd = end - 1;
    }
}

// @ 0x00baccd0
void __stdcall FUN_00baccd0(KeyVec_s00ba_c830* inList, int p2, int p3, int p4, int p5, KeyVec_s00ba_c830* out)
{
    out->clear();
    ProfileMgr* mgr = FUN_00401090();

    int bound;
    if (p3 < p2) { bound = p4 + p3 * 2; p2 = (bound / 2 - p3) * p5 + p3; }
    else { bound = p2 * 2; }

    KeyVec_s00ba_c830 vZero = { 0, 0, 0 };     // profile +0x608 == 0
    KeyVec_s00ba_c830 vNon = { 0, 0, 0 };      // profile +0x608 != 0

    for (Key* it = inList->mBegin; it != inList->mEnd; ++it) {
        Profile* pr = mgr->FUN_004df550(*it);
        if (!pr) continue;
        if (pr->m608 == 0) vZero.push_back(*it);
        else vNon.push_back(*it);
    }

    int done1 = 0;
    for (; done1 < bound; ++done1) {
        Key tmp;
        if (vZero.mBegin == vZero.mEnd) {
            Obj10a0* r = FUN_00b3d450(0xef2601ca)->FUN_00ac10a0();
            if (!r) break;
            tmp = r->mKey;
        } else {
            Key* chosen = vZero.mBegin + DrawIndex(vZero.mBegin, vZero.mEnd);
            tmp = *chosen;
            Key* end = vZero.mEnd;
            for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
            vZero.mEnd = end - 1;
        }
        out->push_back(tmp);
    }

    int bound2 = p2;
    if (done1 / 2 < p2) bound2 = done1 / 2;

    int done2 = 0;
    for (; done2 < bound2; ++done2) {
        Key tmp;
        if (vNon.mBegin == vNon.mEnd) {
            Obj10a0* r = FUN_00b3d450(0x5029da65)->FUN_00ac10a0();
            if (!r) break;
            tmp = r->mKey;
        } else {
            Key* chosen = vNon.mBegin + DrawIndex(vNon.mBegin, vNon.mEnd);
            tmp = *chosen;
            Key* end = vNon.mEnd;
            for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
            vNon.mEnd = end - 1;
        }
        out->push_back(tmp);
    }

    for (Key* it = out->mBegin; it != out->mEnd; ++it) mgr->FUN_004df550(*it);
}

// @ 0x00bad080
void __stdcall FUN_00bad080(Key* base, KeyVec_s00ba_c830* out)
{
    PropMgr* pm = PropertyManager();
    RefCount* local = 0;
    if (local) { RefCount* t = local; local = 0; t->Release(); }

    KeyVec_s00ba_c830 ml = { 0, 0, 0 };
    pm->LookupRefs(base->a, base->c, &ml);

    if ((int)(ml.mEnd - ml.mBegin) > 0) {
        for (Key* p = ml.mBegin; p != ml.mEnd; ++p) out->push_back(*p);
        if (ml.mBegin && ((int*)ml.mBegin)[-1] != 0) FreeBlock(ml.mBegin);
        return;
    }

    IntVec vZ = { 0, 0, 0 };        // hash 0x6d60a1cc
    IntVec vX = { 0, 0, 0 };        // hash 0x29c388a
    IntVec vY = { 0, 0, 0 };        // hash 0x3a8be428

    RBTree* tree = FUN_006b42e0();
    void* head = (char*)tree + 4;
    for (void* n = *(void**)((char*)tree + 8); n != head; n = RBTreeIncrement(n)) {
        uint32_t id = *(uint32_t*)((char*)n + 0x1c);
        uint32_t h = ((Species*)id)->FUN_00b8f860();
        if (h == 0x29c388a) vX.push_back((int)id);
        else if (h == 0x3a8be428) vY.push_back((int)id);
        else if (h == 0x6d60a1cc) vZ.push_back((int)id);
    }

    for (int round = 0; round < 3; ++round) {
        if (vZ.mBegin != vZ.mEnd) {
            int* chosen = vZ.mBegin + Rnd((uint32_t)(vZ.mEnd - vZ.mBegin));
            Obj080* o = (Obj080*)*chosen;
            Key* k = o->GetKey();
            out->push_back(*k);
            vZ.erase(chosen);
        }
        if (vX.mBegin != vX.mEnd) {
            int* chosen = vX.mBegin + Rnd((uint32_t)(vX.mEnd - vX.mBegin));
            Obj080* o = (Obj080*)*chosen;
            Key* k = o->GetKey();
            out->push_back(*k);
            vX.erase(chosen);
        }
        if (vY.mBegin != vY.mEnd) {
            int* chosen = vY.mBegin + Rnd((uint32_t)(vY.mEnd - vY.mBegin));
            Obj080* o = (Obj080*)*chosen;
            Key* k = o->GetKey();
            out->push_back(*k);
            vY.erase(chosen);
        }
    }
    if (ml.mBegin && ((int*)ml.mBegin)[-1] != 0) FreeBlock(ml.mBegin);
}

// @ 0x00bad440
void Self440::FUN_00bad440(Obj440* param_1, Cfg440* param_2)
{
    int m28 = param_1->m28;
    int mode;
    if (m28 == 3) mode = 1;
    else if (m28 == 4) mode = 2;
    else if (m28 == 5) mode = 3;
    else return;

    if (param_2) {
        if (mode < 3) param_2->m10 &= 0xfffffff7;
        if (mode < 2) param_2->m10 &= 0xfffffffb;
        if (mode < 1) param_2->m10 &= 0xfffffffd;
        if (mode > 1) param_2->m10 &= 0xfffffffe;
        if (mode > 2) param_2->m10 &= 0xfffffffd;
        if (param_2->m10 == 0) {
            if (mode == 1) param_2->m10 |= 1;
            else if (mode == 2) param_2->m10 |= 2;
            else if (mode == 3) param_2->m10 |= 4;
        }
    }

    KeyVec_s00ba_c830 vout = { 0, 0, 0 };
    if (!param_2 || param_2->m20.mBegin == param_2->m20.mEnd) {
        Key base = *FUN_00b8d8e0();
        Key tmp = base;
        PropMgr* pm = PropertyManager();
        RefCount* ref = 0;
        bool ok = pm->Lookup(base.a, base.c, &ref);
        if (!ok) {
            tmp.c = 0x4184a100;
            if (ref) { RefCount* r = ref; ref = 0; r->Release(); }
            ok = pm->Lookup(base.a, 0x4184a100, &ref);
            if (!ok) tmp.c = 0x4184ac00;
        }
        FUN_00bad080(&tmp, &vout);
        if (ref) ref->Release();
    } else {
        FUN_00baa080(&param_2->m20);
    }

    int flagVar;
    int arg3;
    int iVar10;
    int roll = 6;
    bool haveRoll = false;

    if (param_2 == 0) {
        flagVar = 0;
        arg3 = (mode == 0) ? 0 : mode - 1;
    } else {
        flagVar = param_2->m0c;
        if (flagVar != 0) {
            iVar10 = 3;
            arg3 = mode;
            haveRoll = true;
        } else {
            arg3 = FUN_00ba6ab0(&param_2->m10);
        }
    }

    if (!haveRoll) {
        roll = (int)Rnd(6) + 1;
        if (param_2 == 0) iVar10 = (2 < roll) ? 3 : roll;
        else iVar10 = FUN_00ba6ab0(&param_2->m14);
    }

    FUN_00bac830(&vout, mode, arg3, iVar10, (char)flagVar, &param_1->mBc);

    KeyVec_s00ba_c830 v2 = { 0, 0, 0 };
    if (param_2 && param_2->m34.mBegin != param_2->m34.mEnd) FUN_00baa080(&param_2->m34);

    int iv9 = 0;
    if (2 < iVar10) {
        if (flagVar == 0) {
            if (param_2 == 0) {
                int a = roll - 3;
                int v = (1 < a) ? 2 : a;
                if (v < 1) v = 0;
                iv9 = v;
            } else iv9 = FUN_00ba6ab0(&param_2->m18);
        } else iv9 = 2;
    }

    if (iVar10 < 3) iVar10 = 0;
    else if (flagVar == 0) {
        if (param_2 == 0) {
            int c = roll - 5;
            int v = ClampHi(c, 1);
            if (v < 1) v = 0;
            iVar10 = v;
        } else iVar10 = FUN_00ba6ab0(&param_2->m1c);
    } else iVar10 = 1;

    FUN_00baccd0(&v2, mode, arg3, iv9, iVar10, &param_1->mD0);
}

// @ 0x00bad7a0
void cStarManager::EraseFeedback(void* pEvent)
{
    uint32_t nKey = *(uint32_t*)((uint8_t*)pEvent + 0x84);
    MapIterator it = mFeedback.Find(nKey);
    if (it.mpNode != mFeedback.mTree.mpAnchor) {
        --mFeedback.mTree.mnSize;
        RBTreeIncrement(it.mpNode);
        RBTreeErase(it.mpNode, mFeedback.mTree.mpAnchor);
        if (it.mpNode->mpValue != nullptr)
            it.mpNode->mpValue->Release();
        operator_delete(it.mpNode);
    }
}

// @ 0x00bad810
void cStarManager::Reset()
{
    for (int32_t i = 0; i < (int32_t)(mppBannersEnd - mppBanners); ++i)
        mppBanners[i]->mpOwner->Slot10();

    for (int32_t i = 0; i < (int32_t)(mppAgentsEnd - mppAgents); ++i) {
        cStarAgentRecord* pAgent = mppAgents[i];
        pAgent->mbActive = false;
        if (pAgent->mpEffect != nullptr) {
            FUN_00c86e50();
            if (pAgent->mpEffect != nullptr) {
                IRefCounted* pOld = pAgent->mpEffect;
                pAgent->mpEffect = nullptr;
                pOld->Release2();
            }
        }
    }

    if (mpCurrentItem != nullptr) {
        IRefCounted* pOld = mpCurrentItem;
        mpCurrentItem = nullptr;
        pOld->Release();
    }

    mppAgentsEnd += EraseAllPointers(mppAgents, mppAgentsEnd, mppAgentsEnd);
}

// @ 0x00bad8d0
void cStarManager::Shutdown()
{
    IRefCounted* pOld = gspBackgroundSimManager->mpIdleState;
    if (pOld != nullptr) {
        gspBackgroundSimManager->mpIdleState = nullptr;
        pOld->Release();
    }

    mppAgentsEnd += EraseAllPointers(mppAgents, mppAgentsEnd, mppAgentsEnd);

    NounManager()->RemoveNounsOfType(0x18eb9d2);
    gCheatStarCount = 0;
}

// @ 0x00bad940
void cStarManager::LoadFromObject(void* pObject)
{
    uint32_t nHandle = *(uint32_t*)((uint8_t*)pObject + 0x7c);
    cStarAgentRecord* pAgent;
    if (nHandle == 0) {
        pAgent = (cStarAgentRecord*)mpPending;
    } else if (nHandle == 0xffffffff) {
        pAgent = nullptr;
    } else {
        uint8_t* pBlock = *(uint8_t**)(mpHandleTable + (nHandle >> 12) * 0x14);
        pAgent = *(cStarAgentRecord**)(pBlock + (nHandle & 0xfff) * 4);
    }

    WString* pName = (WString*)((uint8_t*)pObject + 0x10);
    if (pName != &pAgent->mName)
        pAgent->mName.Assign(pName->mpBegin, pName->mpEnd);

    void* pConfig = *(void**)((uint8_t*)pObject + 0x48);
    if (pConfig != nullptr) {
        FUN_00bb9b90((uint8_t*)pConfig + 0x504);
        FUN_004df3e0(ChildGetSomething((uint32_t)(size_t)pConfig));
    }

    FUN_00bb9ad0(*(int32_t*)((uint8_t*)pObject + 0xa4));
    FUN_00bb9b00(2, 0);
    uint8_t* pSlot = (uint8_t*)FUN_00bbaa60(0);
    *(int32_t*)(pSlot + 0x194) = *(int32_t*)((uint8_t*)pObject + 0xa4);

    IRefCounted** ppThreats = mppThreats;
    IRefCounted** ppThreatsEnd = mppThreatsEnd;
    IRefCounted* pExisting = (IRefCounted*)pAgent;
    if (ppThreats != ppThreatsEnd) {
        while (*ppThreats != pExisting) {
            ++ppThreats;
            if (ppThreats == ppThreatsEnd)
                break;
        }
        if (ppThreats != ppThreatsEnd) {
            if (ppThreats + 1 < ppThreatsEnd)
                CopyImpl_0(ppThreats + 1, ppThreatsEnd, ppThreats);
            IRefCounted** ppNewEnd = ppThreatsEnd - 1;
            mppThreatsEnd = ppNewEnd;
            if (*ppNewEnd != nullptr)
                (*ppNewEnd)->Release();
        }
    }

    IRefCounted* pOld = mpCurrentItem;
    if (pExisting != pOld) {
        if (pExisting != nullptr)
            pExisting->Slot00();
        mpCurrentItem = pExisting;
        if (pOld != nullptr)
            pOld->Release();
    }

    WString* pWorld = (WString*)pObject;
    if (pWorld != &mWorldName)
        mWorldName.Assign(pWorld->mpBegin, pWorld->mpEnd);

    IGameObject* pSave = SaveLoadManager();
    IGameObject* pStar = *(IGameObject**)((uint8_t*)pSave + 0x188);
    *(float*)((uint8_t*)pStar + 0x58) = *(float*)((uint8_t*)pStar + 0x54);

    pSave = SaveLoadManager();
    pStar = *(IGameObject**)((uint8_t*)pSave + 0x188);
    *(bool*)((uint8_t*)pStar + 0x48) = true;

    pSave = SaveLoadManager();
    pStar = *(IGameObject**)((uint8_t*)pSave + 0x188);
    *(bool*)((uint8_t*)pStar + 0x49) = true;
}

// @ 0x00badd10
void cStarManager::UpdateItem(void* pItem, void* pConfig)
{
    FUN_00b3d420();
    if (FUN_00b3d420(), *(int32_t*)((uint8_t*)FUN_006b42e0(nullptr) + 0x14) == 0)
        return;

    uint32_t nFlags = mnFlags;
    if ((nFlags & 8) != 0)
        return;
    mnFlags = nFlags | 8;

    uint8_t* pObject = (uint8_t*)pItem;
    void* pSlot = FUN_00ba6d80(FUN_00b8d8f0());
    uint32_t nId = GetItemInstanceID(pSlot);

    if ((nId & 1) != 0) {
        FUN_00ba7bd0(pObject);
        if (pConfig != nullptr)
            FUN_00bab010(pObject, pConfig);
        switch (mnState) {
        case 3:
            pObject[0x0c] = 0;
            pObject[0x10] = 1;
            pObject[0x14] = 4;
            pObject[0x18] = 1;
            break;
        case 4:
            pObject[0x0c] = 0;
            pObject[0x10] = 2;
            pObject[0x14] = 8;
            pObject[0x18] = 4;
            break;
        case 5:
            pObject[0x0c] = 1;
            pObject[0x10] = 8;
            pObject[0x14] = 8;
            pObject[0x18] = 4;
            pObject[0x1c] = 2;
            break;
        }
    } else {
        if (FUN_00b8dab0() < 2) {
            FUN_00bad440(this, pItem, pConfig);
            return;
        }
        FUN_00ba7bd0(pObject);
        if (pConfig != nullptr)
            FUN_00bab010(pObject, pConfig);
        if (FUN_00b8dab0() < 5) {
            pObject[0x0c] = 1;
        } else {
            uint32_t nValue = *(uint32_t*)(pObject + 0x10) & 0xfffffffe;
            if (nValue == 0)
                nValue |= 2;
            *(uint32_t*)(pObject + 0x10) = nValue;
            if (!FUN_00bb9af0(pSlot, 0x100))
                pObject[0x0c] = 1;
        }
    }

    FUN_00bad440(this, pItem, pObject);
    FUN_00ba8220(pObject);
}

// @ 0x00badea0
uint32_t& CivCounterMap::GetCounter(cCivilization* pKey)
{
    FeedbackNode* pAnchor = mTree.mpAnchor;
    FeedbackNode* pParent = pAnchor;
    FeedbackNode* pNode = mTree.mpRoot;
    while (pNode != nullptr) {
        if (pNode->mnKey < (uint32_t)(size_t)pKey) {
            pNode = pNode->mpLeft;
        } else {
            pParent = pNode;
            pNode = pNode->mpRight;
        }
    }
    if (pParent != pAnchor && (uint32_t)(size_t)pParent->mnKey >= (uint32_t)(size_t)pKey)
        return *(uint32_t*)&pParent->mpValue;

    DoInsertValue(pParent, (const uint32_t*)&pKey, 0);
    return *(uint32_t*)&pParent->mpValue;
}

// @ 0x00e04270
void* cSPUIGlobalUI::AsInterface(unsigned id)
{
    void* pRet = 0;
    if (id != 0xee3f516e) {
        if (id == 0x0469a812)
            return (void*)((char*)this - 0x70);
        if (id != 0x2f009dd0)
            return pRet;
    }
    char* p = (char*)this - 0x70;
    return (void*)(p ? this : 0);
}

// @ 0x00e042b0
bool cSPUIGlobalUI::AnyCivSlotUsed()
{
    for (int i = 0; i < 4; ++i) {
        if (*(char*)((char*)this + 0x91 + i * 0xc) != 0)
            return true;
    }
    return false;
}

// @ 0x00e042d0
void cSPUIGlobalUI::ShowOptionWindows(char on)
{
    void* w = this->FindWindowByID(0x6453746);
    ((TFnVII)VT(w, 0x7c))(w, 1, (int)on);

    w = this->FindWindowByID(0x652a628);
    ((TFnVII)VT(w, 0x7c))(w, 1, (int)on);

    w = this->FindWindowByID(0x44827b8);
    ((TFnVII)VT(w, 0x7c))(w, 1, (on == 0) ? 1 : 0);
}

// @ 0x00e04330
int __cdecl FUN_00e04330(int type)
{
    switch (type) {
    case 3:  return 0x64bd00a;
    case 10: return 0x64bd00b;
    case 9:  return 0x64bd00c;
    case 11: return 0x64bd00d;
    case 6:  return 0x64bd00e;
    case 0:  return 0x64bd00f;
    case 4:  return 0x64bd010;
    case 7:  return 0x64bd011;
    case 1:  return 0x64bd012;
    case 5:  return 0x64bd013;
    case 8:  return 0x64bd014;
    case 2:  return 0x64bd015;
    default: return 0x64bd016;
    }
}
