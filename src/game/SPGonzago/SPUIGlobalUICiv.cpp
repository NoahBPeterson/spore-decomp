// src/game/SPGonzago/SPUIGlobalUICiv.cpp -- migrated from slice(s) s00e06220, s00e052d0, s00e043c0, s00e033d0, s00bad7a0, s00bac830, s00baa930, s00ba9810 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIGlobalUICiv.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cStarManager.h"
#include <string.h>
#include "SP/cCivilization.h"
#include "EA/UTFWin/RenderContext.h"
#include "SP/cString.h"
#include "SP/cVehicle.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "cSPUILayout.h"
#include "SP/cSPUINewProgressBar.h"

// ---- items of slice s00ba9810 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSortTriple {                                                    // 12-byte sort / run key
    float mX;                                                           // +0x00
    float mY;                                                           // +0x04
    uint32_t mZ;                                                        // +0x08 (third word copied as an integer)
};
void* FUN_00ba96e0(void* pBegin, void* pEnd);                           // 0x00ba96e0
void FUN_00ba9740(void* pBegin, void* pMiddle, void* pEnd, void* pPred); // 0x00ba9740
struct ISortKey {
    virtual void v00(void* pArg);
    uint8_t mPad04[0x24];                                               // +0x04
    int mnKey;                                                          // +0x28
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
extern float gRandomScale;                      // 0x01471064
extern float gRandomScale2;                     // 0x01470f1c
extern float gRealOne;                          // 0x01485720
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
void* __cdecl cStar_GetSolarSystem(void* pStar);                        // 0x00c8b770
float __cdecl cStar_GetOrbitRadius(void* pSolarSystem, int32_t nIndex,
                                   int32_t nOne);                       // 0x00c84d40
float __cdecl cPlanet_GetOrbitRadius(void* pPlanet, int32_t nIndex,
                                     int32_t nOne);                     // 0x00c84c60
void __cdecl SetVisible(void* pObject, int32_t nOne);                   // 0x00c70f90
float __cdecl VectorLength(const Vector3* pVector);                     // 0x0040ae50
uint32_t __cdecl RandomUint32Uniform(uint32_t nRange);                  // 0x00a68fb0
void* __cdecl ChildGetSomething(uint32_t nPrompt);                      // 0x00401090
void* __cdecl AddRefObject(void* pObject);                              // 0x00801920
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

// ---- items of slice s00e043c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPUINewProgressBar {
    void** mpVptr;                                   // +0x00
    int    mRefCount;                                // +0x04
    u8     mData[0x30];                              // +0x08 (retail allocation is 0x38 bytes)

    void Update(float value, int mode);              // 0x00e29da0
    void SetMode(int mode);                          // 0x00e29c80
    void Shutdown();                                 // 0x00e28a80
    void Release()                                   // inline refcount drop, vtbl[0] at zero
    {
        if (--mRefCount == 0) {
            mRefCount = 1;
            ((void (__thiscall*)(void*, int))mpVptr[0])(this, 1);
        }
    }
};
struct cString {
    char        mData[0x18];
    cString();                                    // 0x006b5060
    void Load(int key, int table, int flags);     // 0x006b54b0
    const char* c_str(int unused, int alloc);     // 0x006b55c0
    ~cString();                                   // 0x006b5240
};
struct cSPUILayout_s00e0_43c0 {
    char          mPad00[0x14];
    void*         mpWindows;                                  // +0x14 (hash table)
    void*         FindWindowByID(int id, int flag);           // 0x008105b0
    bool          Init(void* a, int b, int c, void* d);       // 0x00812160
    void          SetVisibility(int visible);                 // 0x00810590
    void          Shutdown(int flag);                         // 0x00811ad0
};
struct cSPUIGlobalUI_s00e0_43c0 {
    char          mPad00[8];
    cSPUILayout_s00e0_43c0*  mpLayout;                                   // +0x08
    void*         FindWindowByID(int id);                     // 0x00e012b0
};
void __cdecl SPUIHelpers_SetWindowSPMaterial(void* window, int material, int flags); // 0x00808ad0
void __cdecl SPUIHelpers_SetTooltipText(void* window, const char* text);             // 0x00806de0
void* __cdecl SPUIHelpers_ConstructLayout(void* mem);                                // 0x00810000
void __cdecl RemoveHandler(void* a, void* b, void* c, void* d, void* e);             // 0x00571db0
void* __cdecl AppAllocate(unsigned size, const char* name, int a, int b,
                          const char* file, int line);                               // 0x00f473a0
void* __cdecl MessageServer();                                                       // 0x0067dcc0
void* __cdecl NounManagerInstance();                                                 // 0x00b3d300
int   __cdecl GameTime();                                                            // 0x011e0810
void* __cdecl GetActivePlanet();                                                     // 0x01021260
int   __cdecl ProgressLookup(int value);                                             // 0x00b6f0c0
int   __cdecl ProgressToColor(int value);                                            // 0x00458a40
int   __cdecl StateToMode(int index);                                                // 0x00bef920
int   __fastcall GetStateIndex(void* p, int edx);                                    // 0x00bf0f40
float __fastcall GetProgressFloat(void* p, int edx);                                 // 0x00bd80d0
static inline void  WShow(void* w)                        { ((void (__thiscall*)(void*))(*(void***)w)[0])(w); }
static inline void  WSetFloat(void* w, float v)           { ((void (__thiscall*)(void*, float))(*(void***)w)[1])(w, v); }
static inline void  WRelease(void* w)                     { ((void (__thiscall*)(void*))(*(void***)w)[1])(w); }
static inline int   WGetInt(void* w, int id)              { return ((int (__thiscall*)(void*, int))(*(void***)w)[3])(w, id); }
static inline void* WSetText10(void* w, const char* s)    { return ((void* (__thiscall*)(void*, const char*))(*(void***)w)[4])(w, s); }
static inline int   WGetFlags(void* w)                    { return ((int (__thiscall*)(void*))(*(void***)w)[8])(w); }
static inline void* WCall9(void* w, void* self, void* a)  { return ((void* (__thiscall*)(void*, void*, void*))(*(void***)w)[9])(w, self, a); }
static inline void  WSetProp(void* w, int a, int b)       { ((void (__thiscall*)(void*, int, int))(*(void***)w)[0xa])(w, a, b); }
static inline void  WSetMaterial(void* w, int a, int b)   { ((void (__thiscall*)(void*, int, int))(*(void***)w)[0x1f])(w, a, b); }
static inline void  WSetTitle(void* w, const char* s)     { ((void (__thiscall*)(void*, const char*))(*(void***)w)[0x20])(w, s); }
static inline void  WRefresh(void* w)                     { ((void (__thiscall*)(void*))(*(void***)w)[0x24])(w); }
static inline void* WGetChild(void* w)                    { return ((void* (__thiscall*)(void*))(*(void***)w)[0x2a])(w); }
static inline void* WSetCallback(void* w, int id, void* h) { return ((void* (__thiscall*)(void*, int, void*))(*(void***)w)[0x3c])(w, id, h); }
static inline void  WSetText104(void* w, const char* s)   { ((void (__thiscall*)(void*, const char*))(*(void***)w)[0x41])(w, s); }
static inline void  WSetText108(void* w, const char* s)   { ((void (__thiscall*)(void*, const char*))(*(void***)w)[0x42])(w, s); }
void __stdcall FlashCivCommButton(int unused1, void* window, int unused3);  // 0x00e04a50
struct CivButtonEntry {
    int   mIconIndex;            // +0x00
    u8    mbFlash;               // +0x04
    u8    mbVisible;             // +0x05
    u8    mPad06[2];             // +0x06
    void* mpCallback;            // +0x08
};
struct cSPUIGlobalUICiv_s00e0_43c0 : cSPUIGlobalUI_s00e0_43c0 {
    u8                    mPad000C[0x5c];      // +0x0c
    void*                 mvpField68;          // +0x68 vptr of the first embedded sub-object
    u8                    mPad6C[4];           // +0x6c
    void*                 mvpField70;          // +0x70 vptr of the message-handler sub-object
    void*                 mpField74;           // +0x74 message handler holder
    void*                 mpField78;           // +0x78 (handler identity: this)
    void*                 mpField7C;           // +0x7c (handler id table)
    int                   mField80;            // +0x80
    int                   mField84;            // +0x84
    u8                    mbField88;           // +0x88 minimap toggle byte
    u8                    mPad89[3];           // +0x89
    CivButtonEntry        mButtons[4];         // +0x8c .. +0xbb
    u8                    mPadBC[4];           // +0xbc
    cSPUINewProgressBar*  mpProgressBarC0;     // +0xc0
    cSPUILayout_s00e0_43c0*          mpFieldC4;           // +0xc4 panel layout
    int                   mFieldC8;            // +0xc8
    int                   mFieldCC;            // +0xcc
    int                   mFieldD0;            // +0xd0
    int                   mFieldD4;            // +0xd4
    u8                    mbFieldsD8[4];       // +0xd8
    u8                    mPadDC[4];           // +0xdc (rbtree anchor starts here)
    u8                    mFieldE0[0x10];      // +0xe0

    void  SetProgress(float value, int mode);                       // 0x00e04540
    void  SetMinimapStateFromButton(int mode);                      // 0x00e04560
    void  SetStanceButtonsState(int a, int b, int c, int d, int e); // 0x00e046b0
    void  ActivateCommRelPanel(int index);                          // 0x00e04770
    void  UpdateButtonState(int index);                             // 0x00e04960
    void  OnPlayerCivChanged();                                     // 0x00e04aa0
    bool  Initialize();                                             // 0x00e04b40
    void  SetButtonProgress(int index);                             // 0x00e04d10
    cSPUIGlobalUICiv_s00e0_43c0* Destroy();                                    // 0x00e04f10
    bool  CreatePanel(int param);                                   // 0x00e05000
    void  RemovePanel();                                            // 0x00e05120
};
// ---- items of slice s00e043c0 end

// ---- items of slice s00e052d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
void __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380
struct SimpleVectorU32 {
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpCapacity;   // +0x08
    void push_back(const uint32_t& value);   // 0x00454860
};
void VectorAddModels(uint32_t nModel, SimpleVectorU32* pOut);   // 0x00555e80
void FreeSimpleVector(SimpleVectorU32* pVector) {
    if (pVector->mpBegin && ((int32_t*)pVector->mpBegin)[-1] != 0)
        EASTL_allocator_deallocate(pVector->mpBegin);
}
class cCivilization_s00e0_52d0;
class cVehicle;
class cIObject;
class cMessage;
struct sCivilizationList {          // 0x00b25ca0 result
    cCivilization_s00e0_52d0** mpBegin;        // +0x00
    cCivilization_s00e0_52d0** mpEnd;          // +0x04
};
class cCivilization_s00e0_52d0 {
public:
    int32_t GetRwTypeKind(uint32_t nType);          // 0x00bef980 ret 4
    int32_t GetSuperweaponSpeccy();                 // 0x00bf0f40 ret 0
    bool SuperweaponOnCooldown(int32_t nKind);      // 0x00bf1790 ret 4
    float GetSuperweaponCooldown(int32_t nKind);    // 0x00bf17f0 ret 4
    bool CanUseSuperweapon(int32_t nKind);          // 0x00bf8a00 ret 4
    int32_t GetSuperweaponLevel(uint32_t nType);    // 0x00befa50 ret 4
    float InteractionScore(uint32_t nType);         // 0x00bf6cb0 ret 4
    int32_t GetInteractionLevel();                  // 0x00bf01e0 ret 0
    uint8_t mnPad00[0x8a];                          // +0x00
    uint8_t mbHidden;                               // +0x8a
};
struct sTerrainCurrency {           // SP::GetGameTerrainCursor result
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    virtual void GetSelection(SimpleVectorU32* pOut, uint32_t nType);   // +0x60
    VSLOT(25) VSLOT(26) VSLOT(27)
    virtual bool HasSelection();                                        // +0x70
};
sTerrainCurrency* GetGameTerrainCursor();   // 0x00b30d70
class cIObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27)
    VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36)
    VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40) VSLOT(41) VSLOT(42) VSLOT(43) VSLOT(44) VSLOT(45)
    virtual cVehicle* AsVehicle(uint32_t nType);    // +0xb8
    VSLOT(47)
    virtual void Release();                         // +0xc0
};
class cVehicle : public cIObject {
public:
    uint8_t mnPadC4[0xa60];     // +0xc4
    int32_t mnStance;           // +0xb24
    void SetStance(int32_t nStance, bool bInstant);   // 0x00c9fa70 ret 8
};
class cTerrainEditor {
public:
    uint8_t mnPad00[0x10fc];    // +0x00
    uint32_t mnModel0;          // +0x10fc
    uint32_t mnModel1;          // +0x1100
    uint32_t mnModel2;          // +0x1104
};
class cGameNounManager_s00e0_52d0 {
public:
    cCivilization_s00e0_52d0* GetPlayerCivilization();       // 0x00b25fb0 ret 0
    sCivilizationList* GetCivilizationList();     // 0x00b25ca0 ret 0
    cTerrainEditor* GetCurrentTerrainSphere();    // 0x00f67d90 ret 0
};
cGameNounManager_s00e0_52d0* NounManager_s00e0_52d0();   // 0x00b3d300
struct sGameTime {
    uint8_t mnPad00[0x48];      // +0x00
    uint8_t mbPaused;           // +0x48
};
sGameTime* GameTimeManager();   // 0x00b3d380
class cCommScreen {
public:
    bool IsActive();            // 0x00ae9390 ret 0
};
cCommScreen* CommManager();     // 0x00b3d4a0
class cCivModeState;
class cCommRelay {
public:
    void OnMessage(void* pWindow, uint32_t nValue);   // 0x00e35290 ret 8
    void OnEnd();                                     // 0x00e352b0 ret 0
};
class cCivModeState {
public:
    uint8_t mnPad00[0xe4];      // +0x00
    cCommRelay* mpRelay;        // +0xe4
    uint8_t mnPadE8[0x58];      // +0xe8
    int32_t mnSelectedWeapon;   // +0x140
    void EnterWeaponMode(int32_t nKind);   // 0x00cf1be0 ret 4
};
class cCivModeStrategy {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
    virtual void ExecuteMessage(uint32_t nMessage, uint32_t nArg);   // +0x24
    cCivModeState* GetState();                     // 0x00cf74f0 ret 0
    void OnTechLevelUpgradeButtonPress();          // 0x00cf8160 ret 0
};
cCivModeStrategy* GetCivModeStrategy();            // 0x00cf74c0
class cRenderCtx;
class DSub;
class cIWinProc {
public:
    virtual bool DoMessage(void* pWindow, cMessage* pMsg);   // overridden by cSPUIGlobalUICiv
    virtual void Release();
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    virtual uint32_t GetCommandId(uint32_t nArg);            // +0x4c
    uint32_t FireSelectedCommEvent();                        // 0x00bf0810 ret 0
};
class cUIWindow {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual cUIWindow* FindWindowByID(uint32_t nID);         // +0x0c
    VSLOT(4)
    virtual cUIWindow* GetRenderable();                      // +0x14
    VSLOT(6)
    virtual uint32_t GetID();                                // +0x1c
    VSLOT(8) VSLOT(9)
    virtual void SetFlag(uint32_t nFlag, bool bValue);       // +0x28
    VSLOT(11) VSLOT(12) VSLOT(13)
    virtual const float* GetArea();                          // +0x38
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30)
    virtual void SetVisible(uint32_t nVisible, bool bFlag);   // +0x7c
    VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35)
    virtual void Invalidate();                               // +0x90
    VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40) VSLOT(41)
    virtual DSub* GetSub(uint32_t nID);                      // +0xa8
    VSLOT(43) VSLOT(44) VSLOT(45) VSLOT(46) VSLOT(47) VSLOT(48) VSLOT(49) VSLOT(50) VSLOT(51)
    VSLOT(52) VSLOT(53) VSLOT(54) VSLOT(55) VSLOT(56) VSLOT(57) VSLOT(58) VSLOT(59)
    virtual cUIWindow* GetChild(uint32_t nID, uint32_t nArg);   // +0xf0
    cRenderCtx* mpRenderCtx;    // +0xf4
};
class DSub {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual DSub* GetSub(uint32_t nID);                      // +0x0c
    uint8_t mnPad10[0x0c];      // +0x10
    int32_t mnWidth;            // +0x1c
    int32_t mnHeight;           // +0x20
    int32_t GetField10(int32_t nIndex);                      // 0x00830cf0 ret 4
    void GetPair38(float* pOut, int32_t nCount);             // 0x00830d30 ret 8
    void GetPair40(float* pOut, int32_t nCount);             // 0x00830d60 ret 8
};
class cRenderCtx {
public:
    void* Begin2D(void* pRenderMode);    // 0x0095bc10 ret 4
    void End2D();                        // 0x0095bb20 ret 0
};
struct sBatch2D {
    VSLOT(0)
    virtual void SetColor(uint32_t nColor);   // +0x04
};
void DrawArc(void* pBatch, float fA, float fB, float fC, uint32_t nColor0, uint32_t nColor1,
             float fD, float fE, int32_t nArg, float fF);   // 0x00805740
bool SetTooltipByKey(cUIWindow* pWindow, uint32_t nValue, const wchar_t* pText, int32_t nArg);
const wchar_t* GetKindName(int32_t nKind);              // 0x00e04330
struct tCommButton {                // base class comm-rel button record
    void* mpObject;                 // +0x00
    uint32_t mnPad04;               // +0x04
    uint32_t mnPad08;               // +0x08
};
class cSPUIGlobalUI_s00e0_52d0 {
public:
    VSLOT(0)
    cSPUIGlobalUI_s00e0_52d0();
    void Construct();                          // 0x00e03ab0
    cUIWindow* FindWindowByID(uint32_t nID);   // 0x00e012b0 ret 4
    uint8_t mnPad04[0x20];                     // +0x04
    tCommButton mCommButtons[4];               // +0x24
    uint8_t mnPad54[0x14];                     // +0x54
};
class cUIRefCount {
public:
    virtual void _v0();
    int32_t mnRefCount;             // +0x04
    cUIRefCount() : mnRefCount(0) {}
};
class cSPUIGlobalUICiv;
struct tCivButton {                 // superweapon button record, 12 bytes
    uint32_t mnObject;              // +0x00
    uint8_t mbFlag04;               // +0x04
    uint8_t mbFlag05;               // +0x05
    uint8_t mnPad06[0x02];          // +0x06
    cIWinProc* mpObject;            // +0x08
};
struct sCivIndexNode {
    sCivIndexNode* mpLeft;          // +0x00
    sCivIndexNode* mpRight;         // +0x04
    sCivIndexNode* mpParent;        // +0x08
    uint32_t mnColor;               // +0x0c
    uint32_t mnKey;                 // +0x10
    uint32_t mnValue;               // +0x14
};
struct cCivIndexMap {
    uint32_t mnPad00;               // +0x00
    sCivIndexNode* mpAnchorLeft;    // +0x04
    sCivIndexNode* mpAnchorRight;   // +0x08
    sCivIndexNode* mpAnchorParent;  // +0x0c
    uint8_t mbAnchorColor;          // +0x10
    uint8_t mnPad11[0x03];          // +0x11
    uint32_t mnSize;                // +0x14
    void find(const uint32_t& key, sCivIndexNode** ppResult);   // 0x00e5c780 ret 8
};
sCivIndexNode* RBTreeIncrement_s00e0_52d0(sCivIndexNode* pNode);                 // 0x00921580
void RBTreeErase(sCivIndexNode* pAnchor, sCivIndexNode* pNode);       // 0x00921880
class cMessage {
public:
    uint8_t mnPad00[0x08];          // +0x00
    uint32_t mnId;                  // +0x08
    uint32_t mnParam;               // +0x0c
    uint8_t mnPad10[0x08];          // +0x10
    cUIWindow* mpWindow;            // +0x18
};
class cSPUIGlobalUICiv : public cSPUIGlobalUI_s00e0_52d0, public cUIRefCount, public cIWinProc {
public:
    cSPUIGlobalUICiv();
    bool DoMessage(void* pWindow, cMessage* pMsg);    // overrides cIWinProc::DoMessage
    void RemoveCivFeedback(cCivilization_s00e0_52d0* pCiv);                 // 0x00e052d0
    void SuperweaponClick(uint32_t nButtonId);                   // 0x00e05530
    void SelectStance(int32_t nStance);                          // 0x00e05870
    void SyncStanceWithSelection(int32_t nStance);               // 0x00e05930
    void SetButtonTooltip(uint32_t nWindowId, uint32_t nTextA, uint32_t nTextB, int32_t nCount);
                                                                 // 0x00e05ab0
    void SyncSuperweaponButton(uint32_t nWindowId, int32_t* pnState, int32_t nIndex);
    void DeactivateCommRelPanel(int32_t nIndex);                 // 0x00e04960
    void SetMinimapStateFromButton(int32_t nState);              // 0x00e04560
    void SetStanceButtonsState(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e);
                                                                 // 0x00e046b0
    uint32_t mnPad74;               // +0x74
    uint32_t mnPad78;               // +0x78
    uint32_t mnPad7c;               // +0x7c
    uint32_t mnPad80;               // +0x80
    uint32_t mnPad84;               // +0x84
    uint8_t mbMinimapVisible;       // +0x88
    uint8_t mbPad89;                // +0x89
    uint8_t mnPad8a[0x02];          // +0x8a
    tCivButton mButtons[4];         // +0x8c
    float mfCooldown;               // +0xbc
    uint32_t mnPadC0;               // +0xc0
    uint32_t mnPadC4;               // +0xc4
    uint8_t mnPadC8[0x10];          // +0xc8
    uint8_t mbCooldownShown[4];     // +0xd8
    cCivIndexMap mCivToIndex;       // +0xdc
};
bool DrawSuperweaponCooldown(cUIWindow* pButton, cMessage* pMsg);   // 0x00e05590
void UpdateSuperweaponTooltip(cUIWindow* pWindow, uint32_t nRwType);   // 0x00e05de0
int32_t GetSuperweaponKind(uint32_t nButtonId);                        // 0x00e053c0
// ---- items of slice s00e052d0 end

// ---- items of slice s00e06220 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
class cCivilization_s00e0_6220;
class cSPUIMeter;
struct ILink {
    virtual void AddRef();                       // +0x00
    virtual void Release();                      // +0x04
    virtual void S08();                          // +0x08
    virtual void* GetObject(uint32_t nKey);      // +0x0c
    PV16 PV8 PV2 PV                              // 0x10 .. 0x78
    virtual bool GetRange(uint8_t nType, float* pOut);   // +0x7c
    PV8 PV4 PV2 PV                               // 0x80 .. 0xb8
    virtual void AddRef2();                      // +0xbc
    virtual void Release2();                     // +0xc0

    int32_t GetValue();                          // 0x00b8de30
};
struct IWindow {
    virtual void AddRef();                       // +0x00
    virtual void S04();                          // +0x04
    virtual void Release();                      // +0x08
    virtual struct ISubWindow* GetSubWindow(uint32_t nKey);   // +0x0c
    virtual IWindow* GetDecorator();             // +0x10
    PV2                                          // 0x14, 0x18
    virtual void Select();                       // +0x1c
    virtual void S20();                          // +0x20
    virtual void S24();                          // +0x24
    virtual bool IsVisible();                    // +0x28
    PV2                                          // 0x2c, 0x30
    virtual float* GetArea();                    // +0x34
    PV8 PV2 PV                                   // 0x38 .. 0x60
    virtual void SetProgress(float fValue, float fRange);   // +0x64
    PV4 PV                                       // 0x68 .. 0x78
    virtual void SetState(int32_t nState, bool bOn);      // +0x7c
    PV4                                          // 0x80 .. 0x8c
    virtual void Refresh();                      // +0x90
    PV16 PV4 PV                                  // 0x94 .. 0xe4
    virtual void BringToFront(IWindow* pWindow); // +0xe8
    virtual void AttachChild(IWindow* pWindow);  // +0xec
    virtual IWindow* CreateChild(void* pOwner, int32_t nFlags);   // +0xf0
    PV4                                          // 0xf4 .. 0x100
    virtual void AttachOwner(cSPUIMeter* pOwner);   // +0x104
};
struct ISubWindow {
    PV16 PV8 PV2 PV                              // 0x00 .. 0x24
    virtual void SetState(int32_t nState, bool bOn);      // +0x28
};
class cSPUILayout_s00e0_6220 {
public:
    bool Init(const wchar_t* pName, uint32_t nID, bool bDeep, uint32_t nFlags);   // 0x00812160
    IWindow* FindWindowByID(uint32_t nID, bool bDeep);          // 0x008105b0
    void Shutdown(uint32_t nFlags);                             // 0x00811ad0
    bool IsVisible();                                           // 0x00810070

    IWindow* m_pRoot;                            // +0x00
};
class cCivilization_s00e0_6220 {
public:
    virtual void AddRef();                       // +0x00
    virtual void Release();                      // +0x04

    uint32_t m_nFlags04;                         // +0x04
    uint8_t m_pad008[0x82];                      // +0x08
    bool m_bNotPlayable;                         // +0x8a
    bool m_bVisible;                             // +0x8b
    uint8_t m_pad08c[0x20c];                     // +0x8c
    int32_t m_nStage;                            // +0x298
    int32_t m_nPanelIndex;                       // +0x29c

    int32_t GetTurn();                           // 0x00bf01e0
};
class cCivilizationList {
public:
    cCivilization_s00e0_6220** m_pBegin;                    // +0x00
    cCivilization_s00e0_6220** m_pEnd;                      // +0x04
    cCivilization_s00e0_6220** m_pCapacity;                 // +0x08
};
class cGameNounManager_s00e0_6220 {
public:
    cCivilization_s00e0_6220* GetPlayerCivilization();      // 0x00b25fb0
    cCivilizationList* GetCivilizationList();    // 0x00b25ca0
};
cGameNounManager_s00e0_6220* __cdecl NounManager_s00e0_6220();         // 0x00b3d300
class cCommManager {
public:
    bool IsActive();                             // 0x00ae9390
};
cCommManager* __cdecl CommManager_s00e0_6220();             // 0x00b3d4a0
class cCivIndexMap_s00e0_6220 {
public:
    struct Node {
        void* m_pLeft;                           // +0x00
        void* m_pRight;                          // +0x04
        void* m_pParent;                         // +0x08
        uint32_t m_nColor;                       // +0x0c
        uint32_t m_nKey;                         // +0x10
        uint32_t m_nValue;                       // +0x14
    };

    Node*& Find(cCivilization_s00e0_6220* const& pCiv);                // 0x00e5c780
    uint32_t& GetCounter(cCivilization_s00e0_6220* const& pCiv);       // 0x00badea0

    void* m_pAllocator;                          // +0x00
    Node m_stHeader;                             // +0x04
    Node* m_pRoot;                               // +0x0c
    uint32_t m_nSize;                            // +0x10
};
struct cCommRelPanel {
    cCivilization_s00e0_6220* m_pData;                      // +0x00
    bool m_bActive;                              // +0x04
    bool m_bShown;                               // +0x05
    uint8_t m_pad006[2];                         // +0x06
    cCivilization_s00e0_6220* m_pCiv;                       // +0x08
};
class cSPUIGlobalUI_s00e0_6220 {
public:
    IWindow* FindWindowByID(uint32_t nID);               // 0x00e012b0
    void HandleMessage(uint32_t nMessage, void* pData);  // 0x00e03f80

    uint8_t m_pad000[0x88];
};
class cSPUIGlobalUICiv_s00e0_6220 : public cSPUIGlobalUI_s00e0_6220 {
public:
    void Update(int32_t nDelta);                                       // 0x00e06220
    void SetCommScreenVisibility(cCivilization_s00e0_6220* pCiv, bool bOn);       // 0x00e063d0
    void AssignCommRelPanel(int32_t nIndex, cCivilization_s00e0_6220* pCiv);      // 0x00e064f0
    void HandleMessage(uint32_t nMessage, void* pData);                // 0x00e06560
    void InitCommRelPanels();                                          // 0x00e065c0
    void AssignFreeCommRelPanel(cCivilization_s00e0_6220* pCiv);                  // 0x00e06630

    void SetMinimapStateFromButton(int32_t nState);                    // 0x00e04560
    void UpdateCommRelPanel(int32_t nDelta, int32_t nIndex);           // 0x00e04d10
    void ActivateCommRelPanel(int32_t nIndex);                         // 0x00e04770
    void BindCommRelData(uint32_t nKey, void** ppData, int32_t nIndex);   // 0x00e060c0
    void RefreshCommRelPanels();                                       // 0x00e04aa0
    void SetCommRelProgress(uint32_t a, uint32_t b, uint32_t c, int32_t nValue);  // 0x00e05ab0

    bool m_bFlag88;                              // +0x88
    bool m_bCommScreenActive;                    // +0x89
    uint8_t m_pad08a[2];                         // +0x8a
    cCommRelPanel m_commRelPanels[4];            // +0x8c
    float m_fCommRelTimer;                       // +0xbc
    uint8_t m_pad0c0[8];                         // +0xc0
    void* m_apCommRelData[4];                    // +0xc8
    uint32_t m_nFlags0d8;                        // +0xd8
    cCivIndexMap_s00e0_6220 mCivToIndex;                    // +0xdc
};
int32_t __cdecl GetCurrentTurn();                              // 0x00922bf0
int32_t __cdecl GetLastTurn();                                 // 0x00befd30
void __stdcall FUN_00e05930(int32_t nMode);                     // 0x00e05930
struct cCivMessage {
    uint8_t m_pad000[8];
    int32_t m_nType;                             // +0x08
    uint8_t m_pad00c[4];                         // +0x0c
    cCivilization_s00e0_6220* m_pCiv;                       // +0x10
};
static const uint32_t kCommWindowIDs[2] = { 0x063bf17c, 0x063bf17d };
static const uint32_t kCommRelDataKeys[4] = { 0x05a55b10, 0x05a55b20, 0x05a55b30, 0x05a55b40 };
static const uint32_t kRelPanelMainWindow = 0x046977ff;
static const uint32_t kRelPanelSubWindow = 0x055d626f;
static const uint32_t kRelPanelChildKey = 0x8ed27e7a;
static const uint32_t kProgressCurrentA = 0x0643d8b3;
static const uint32_t kProgressCurrentB = 0x04cac3c5;
static const uint32_t kProgressCurrentC = 0x0643edb7;
static const uint32_t kProgressLoyaltyA = 0x0643d8da;
static const uint32_t kProgressLoyaltyB = 0xf47c278d;
static const uint32_t kProgressLoyaltyC = 0x0643edbe;
static const uint32_t kMessageCommCivA = 0x03ac86ad;
static const uint32_t kMessageCommCivB = 0x03ac86b5;
static const uint32_t kMessageCommClose = 0x052f1544;
class cSPUIMeterBaseA {
public:
    virtual void V00();                                 // +0x00
    PV8                                                 // 0x04 .. 0x20
    ~cSPUIMeterBaseA() {}
};
class cSPUIMeterBaseB {
public:
    virtual void V00();                                 // +0x00
    ~cSPUIMeterBaseB() {}
};
class cSPUIMeter : public cSPUIMeterBaseA, public cSPUIMeterBaseB {
public:
    cSPUIMeter(int32_t nRootID, uint32_t nFlags, const wchar_t* pName, uint32_t nLayoutFlags);  // 0x00e06790
    ~cSPUIMeter();                                      // 0x00e06870

    void SetStart(uint32_t nStart);                     // 0x00e066d0
    void SetTrackedObject(ILink* pObject);              // 0x00e066e0
    bool Update(int32_t nDelta, void* pMessage);        // 0x00e068e0
    void Shutdown(uint32_t nFlags);                     // 0x00e06940
    bool IsVisible();                                   // 0x00e06970
    void UpdateFromSource();                            // 0x00e06990
    void SetLink(ILink* pLink);                         // 0x00e06c50
    void SetLinkB(ILink* pLink);                        // 0x00e06ca0
    void SetSource(ILink* pSource);                     // 0x00e06cf0

    virtual void OnValueChanged();                      // +0x24
    virtual void OnLayoutChanged();                     // +0x28

    uint32_t m_nFlags08;                                // +0x08
    bool m_bRangeType;                                  // +0x0c
    uint8_t m_pad00d[3];                                // +0x0d
    cSPUILayout_s00e0_6220* mLayout;                               // +0x10
    ILink* m_pSource;                                   // +0x14
    uint32_t m_nRootID;                                 // +0x18
    uint32_t m_nLayoutFlags;                            // +0x1c
    uint32_t m_nStart;                                  // +0x20
    uint32_t m_nNext;                                   // +0x24
    int32_t m_nModel;                                   // +0x28
    int32_t m_nModelExtra;                              // +0x2c
    ILink* m_pTracked;                                  // +0x30
    ILink* m_pLinkA;                                    // +0x34
    ILink* m_pLinkB;                                    // +0x38
};
// ---- items of slice s00e06220 end

// @ 0x00baa730
void SortKeyChain(ISortKey** pBegin, ISortKey** pEnd, int nDepth, void* pArg)
{
    for (;;) {
        if ((int)(((uint32_t)pEnd - (uint32_t)pBegin) & ~3u) <= 0x70 || nDepth < 1) {
            if (nDepth == 0) FUN_00ba9740(pBegin, pEnd, pEnd, pArg);
            return;
        }
        ISortKey** pMid = pBegin + ((pEnd - pBegin) >> 1);
        ISortKey* pFirst = *pBegin;
        ISortKey* pMiddle = *pMid;
        ISortKey* pLast = *(pEnd - 1);
        ISortKey** pPivot;
        if (pFirst->mnKey < pMiddle->mnKey) {
            if (pLast->mnKey <= pMiddle->mnKey) {
                if (pFirst->mnKey < pLast->mnKey) pPivot = pEnd - 1;
                else pPivot = pBegin;
            } else {
                pPivot = pMid;
            }
        } else {
            if (pLast->mnKey <= pFirst->mnKey) {
                if (pMiddle->mnKey < pLast->mnKey) pPivot = pEnd - 1;
                else pPivot = pMid;
            } else {
                pPivot = pBegin;
            }
        }
        ISortKey* pItem = *pPivot;
        if (pItem) pItem->v00(pArg);
        ISortKey** pSplit = (ISortKey**)FUN_00ba96e0(pBegin, pEnd);
        nDepth--;
        SortKeyChain(pSplit, pEnd, nDepth, pArg);
        pEnd = pSplit;
    }
}

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

// @ 0x00badae0
void cStarManager::UpdateVisibility(void* pStar, void* pPlanet, float fNear, float fFar, const Vector3* pOffset)
{
    if ((mnFlags >> 2 & 1) == 0 && mnState != 2)
        return;

    float fOuter;
    float fInner;
    if (pStar != nullptr && pPlanet != nullptr) {
        void* pSystem = cStar_GetSolarSystem(pStar);
        fOuter = cStar_GetOrbitRadius(pSystem, 1, 1);
        fInner = cStar_GetOrbitRadius(pSystem, 2, 1);
        SetVisible(pPlanet, 1);
    } else if (pStar != nullptr && !mbLoaded) {
        IGameObject* pObject = (IGameObject*)AddRefObject(pStar);
        fOuter = cPlanet_GetOrbitRadius(pObject, 1, 1);
        fInner = cPlanet_GetOrbitRadius(pObject, 2, 1);
        float fLength = VectorLength(pOffset != nullptr ? pOffset : &mOffset);
        if (fLength < fOuter) {
            mbVisible = true;
            if (mOffset.x > 0.0f)
                mOffset.x = (float)RandomUint32Uniform(3) * gRandomScale;
            else
                mOffset.x = (float)(int32_t)(mOffset.x * gRandomScale2) * gRandomScale;
        } else if (fLength > fInner) {
            mbVisible = false;
            if (mOffset.x > 0.0f)
                mOffset.x = (float)(int32_t)(mOffset.x * gRandomScale2) * gRandomScale;
            else
                mOffset.x = (float)RandomUint32Uniform(3) * gRandomScale;
        } else if (mnState != 2) {
            return;
        } else {
            mbVisible = gRealOne;
            if (mOffset.x > 0.0f)
                mOffset.x = (float)RandomUint32Uniform(3) * gRandomScale;
            else if (mOffset.x < 0.0f)
                mOffset.x = 0.0f;
            else
                mOffset.x = gRealOne;
        }
        return;
    } else {
        return;
    }

    if (fNear > fOuter) {
        (void)fInner;
    }
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

// @ 0x00e04560
void cSPUIGlobalUICiv_s00e0_43c0::SetMinimapStateFromButton(int mode)
{
    void* a = FindWindowByID(0x562a141);
    void* b = FindWindowByID(0x562a0f7);
    void* c = FindWindowByID(0x55d626f);
    void* d = FindWindowByID(0x46977ff);

    cString text;

    int textId;
    if (mode == 0 && (WGetFlags(a) & 4) == 0) {
        WSetProp(b, 4, 0);
        WSetMaterial(d, 1, 0);
        WSetMaterial(c, 1, mbField88);
        textId = 0x615ffa7;
    } else {
        WSetProp(b, 4, 1);
        int flag = (mode == 0 && mbField88 != 0) ? 1 : 0;
        WSetMaterial(d, 1, flag);
        WSetMaterial(c, 1, 0);
        textId = 0x615ffa8;
    }
    text.Load(0xc0152a6d, textId, 0);
    const char* str = text.c_str(-1, 1);
    void* target = WSetText10(c, str);
    SPUIHelpers_SetTooltipText(target, str);
}

// @ 0x00e046b0
void cSPUIGlobalUICiv_s00e0_43c0::SetStanceButtonsState(int a0, int a1, int a2, int a3, int a4)
{
    if (a0 != 0) {
        a3 = 1;
        a1 = 1;
    }

    void* w1 = FindWindowByID(0x4c61dd8);
    int icon1 = (int)WGetInt(w1, 0x8ed27e7a);
    WSetMaterial(w1, 2, a1);
    WSetProp((void*)icon1, 4, a1);
    WRefresh(w1);

    void* w2 = FindWindowByID(0x4c61b50);
    int icon2 = (int)WGetInt(w2, 0x8ed27e7a);
    WSetMaterial(w2, 2, a3);
    WSetProp((void*)icon2, 4, a3);
    WRefresh(w2);
    (void)a2;
    (void)a4;
}

// @ 0x00e04770
void cSPUIGlobalUICiv_s00e0_43c0::ActivateCommRelPanel(int index)
{
    CivButtonEntry* entry = (CivButtonEntry*)((char*)this + 0x8c + index * 12);
    int   icon    = entry->mIconIndex;
    void* context = entry->mpCallback;

    void* w1 = FindWindowByID(0x46977ff);
    void* child1 = WSetCallback(w1, icon, 0);

    void* w2 = FindWindowByID(0x55d626f);
    void* child2 = WSetCallback(w2, icon, 0);

    void* w3 = FindWindowByID(0x46977ff);
    void* child3 = WSetCallback(w3, icon + 0x323776, 0);

    void* w4 = FindWindowByID(0x55d626f);
    void* child4 = WSetCallback(w4, icon + 0x323776, 0);

    WSetMaterial(child2, 1, 0);
    WSetMaterial(child1, 1, 1);
    WSetMaterial(child4, 1, 1);
    WSetMaterial(child3, 1, 1);

    // Current value for the entry, mapped to a label colour.
    int value = 0;
    if (context != 0)
        value = ProgressToColor(ProgressLookup(*(int*)((char*)context + 0x40)));

    void* label1 = WGetChild(child1);
    int labelId1 = 0;
    if (label1 != 0)
        labelId1 = WGetInt(label1, 0x53eb526);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId1, 0, value);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId1, 2, value);

    void* label2 = WGetChild(child2);
    int labelId2 = 0;
    if (label2 != 0)
        labelId2 = WGetInt(label2, 0x53eb526);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId2, 0, value);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId2, 2, value);

    // Fly-in value: 0 for mode 1, 67.0f for mode 2, otherwise 100.0f.
    int mode = StateToMode(GetStateIndex(context, 0));
    float target = 100.0f;
    if (mode == 1)
        target = 0.0f;
    else if (mode == 2)
        target = 67.0f;

    void* title = WSetCallback(child1, 0x55d5429, (void*)1);
    int titleId = WGetInt(title, 0x10edf11);
    WSetFloat((void*)titleId, target);
}

// @ 0x00e04960
void cSPUIGlobalUICiv_s00e0_43c0::UpdateButtonState(int index)
{
    CivButtonEntry* entry = (CivButtonEntry*)((char*)this + 0x8c + index * 12);
    int icon = entry->mIconIndex;

    void* w1 = FindWindowByID(0x46977ff);
    void* child1 = WSetCallback(w1, icon, 0);

    void* w2 = FindWindowByID(0x55d626f);
    void* child2 = WSetCallback(w2, icon, 0);

    if (entry->mpCallback != 0) {
        void* old = entry->mpCallback;
        entry->mpCallback = 0;
        WRelease(old);
    }

    WSetMaterial(child1, 1, 0);
    WSetMaterial(child2, 1, 0);

    void* w3 = FindWindowByID(0x46977ff);
    void* child3 = WSetCallback(w3, icon + 0x323776, 0);

    void* w4 = FindWindowByID(0x55d626f);
    void* child4 = WSetCallback(w4, icon + 0x323776, 0);

    WSetMaterial(child3, 1, 1);
    WSetMaterial(child4, 1, 1);

    entry->mbVisible = 0;
}

// @ 0x00e04a50
void __stdcall FlashCivCommButton(int unused1, void* window, int unused3)
{
    (void)unused1;
    (void)unused3;
    if (window != 0)
        WGetInt(window, 0x8ed27e7a);
    void* child = ((void* (__thiscall*)(void*))(*(void***)window)[0x13])(window);
    if (child == 0) {
        SPUIHelpers_SetWindowSPMaterial(window, 0x0147f2c8, 0);
    } else if (WGetInt(child, 0x5234b49) == 0) {
        SPUIHelpers_SetWindowSPMaterial(window, 0x0147f2c8, 0);
    }
}

// @ 0x00e04aa0
void cSPUIGlobalUICiv_s00e0_43c0::OnPlayerCivChanged()
{
    void* civ = ((void* (__thiscall*)(void*))0x00b25fb0)(NounManagerInstance());
    if (civ == 0)
        return;

    ((void (__thiscall*)(void*, int))0x00bf6fa0)(civ, 0);
    int id = GameTime();
    if (id == *(int*)0x015a4880)
        return;

    void* w = FindWindowByID(0xabcd1001);
    *(int*)0x015a4880 = id;
    ((void (__thiscall*)(void*, void*))0x00cfe780)(*(void**)0x0169d3c8, civ);

    cString text;
    text.Load(0xc0152a6d, 0x65f79f0, 0);
    SPUIHelpers_SetTooltipText(w, text.c_str(-1, 1));
    WRefresh(w);
}

// @ 0x00e04b40
bool cSPUIGlobalUICiv_s00e0_43c0::Initialize()
{
    void* title = FindWindowByID(-1);
    if (title != 0) {
        WShow(title);
        WSetText104(title, (const char*)this + 0x70);
    }

    static const int kSlotIds[4] = { 0x5a55b10, 0x5a55b20, 0x5a55b30, 0x5a55b40 };
    for (int i = 0; i < 4; ++i) {
        void* w = FindWindowByID(kSlotIds[i]);
        if (w != 0)
            WSetText104(w, (const char*)this + 0x70);
    }

    // Reset the four entry slots and drop their old callbacks.
    for (int i = 0; i < 4; ++i) {
        CivButtonEntry* e = &mButtons[i];
        e->mIconIndex = 0x4655fd5 + i;
        e->mbFlash = 0;
        e->mbVisible = 0;
        void* cb = e->mpCallback;
        e->mpCallback = 0;
        if (cb != 0)
            WRelease(cb);
    }

    // Register the async message holder and its three handlers.
    void* holder = MessageServer();
    mpField74 = holder;
    mpField78 = this;
    mpField7C = (void*)0x15a4884;
    mField80 = 3;
    mField84 = 0;
    if (holder != 0 && this != 0) {
        for (int off = 0; off < 0xc; off += 4) {
            void* arg = *(void**)(off + 0x15a4884);
            WCall9(holder, this, arg);
        }
    }

    for (int i = 0; i < 4; ++i) {
        mButtons[i].mbFlash = 0;
        UpdateButtonState(i);
    }

    void* nameWin = FindWindowByID(0x562a0f7);
    void* nameChild = WSetCallback(nameWin, 0x562a2da, (void*)1);
    void* planet = GetActivePlanet();
    const char* name = (const char*)((void* (__thiscall*)(void*))0x00c707e0)(planet);
    name = *(const char**)name;
    WSetTitle(nameChild, name);

    if (title != 0)
        WRelease(title);
    return true;
}

// @ 0x00e04d10
void cSPUIGlobalUICiv_s00e0_43c0::SetButtonProgress(int index)
{
    CivButtonEntry* entry = (CivButtonEntry*)((char*)this + 0x8c + index * 12);
    int   icon    = entry->mIconIndex;
    void* context = entry->mpCallback;

    void* w1 = FindWindowByID(0x46977ff);
    void* child1 = WSetCallback(w1, icon, 0);

    void* w2 = FindWindowByID(0x55d626f);
    void* child2 = WSetCallback(w2, entry->mIconIndex, 0);

    if (context != 0 && *(int*)((char*)context + 0x2a0) != -1) {
        bool visible = ((bool (__thiscall*)(void*))0x00ae9f10)(
            ((void* (__thiscall*)(void*))0x00b3d4a0)(context));
        if (!visible) {
            entry->mbVisible = 1;
            FlashCivCommButton(0, child1, 0);
            FlashCivCommButton(0, child2, 0);
            goto clamp;
        }
    }

    if (entry->mbVisible != 0) {
        int c1 = (int)WGetInt(child1, 0x8ed27e7a);
        int c2 = (int)WGetInt(child2, 0x8ed27e7a);
        WSetProp((void*)c1, 8, 0);
        SPUIHelpers_SetWindowSPMaterial((void*)c1, 0x13f9c70, 0);
        WSetProp((void*)c2, 8, 0);
        SPUIHelpers_SetWindowSPMaterial((void*)c2, 0x13f9c70, 0);
        entry->mbVisible = 0;
    }

clamp:
    void* label1 = WSetCallback(child1, 0x46adf86, (void*)1);
    void* label2 = WSetCallback(child2, 0x46adf86, (void*)1);

    float value = GetProgressFloat(context, 0);
    if (value < 0.0f)
        value = 0.0f;
    if (value > 100.0f)
        value = 100.0f;

    WSetFloat(label1, value);
    WSetFloat(label2, value);
}

// @ 0x00e04f10
cSPUIGlobalUICiv_s00e0_43c0* cSPUIGlobalUICiv_s00e0_43c0::Destroy()
{
    *(void**)this = (void*)0x147f394;
    mvpField68 = (void*)0x147f384;
    mvpField70 = (void*)0x147f368;

    void* anchor = (char*)this + 0xdc;
    ((void (__thiscall*)(void*, void*))0x009a9600)(anchor, *(void**)((char*)anchor + 0xc));

    if (mpFieldC4 != 0)
        ((void (__thiscall*)(void*))(*(void***)mpFieldC4)[2])(mpFieldC4);
    if (mpProgressBarC0 != 0)
        mpProgressBarC0->Release();

    for (int i = 3; i >= 0; --i) {
        void* cb = mButtons[i].mpCallback;
        if (cb != 0)
            WRelease(cb);
    }

    if (mpField74 != 0) {
        void* handler = mpField74;
        mpField74 = 0;
        RemoveHandler(handler, mpField78, mpField7C, (void*)mField80, (void*)mField84);
    }

    mvpField70 = (void*)0x13eb938;
    mvpField68 = (void*)0x13ec458;
    // Retail tails into the base-class destructor, so its result is this function's result.
    return ((cSPUIGlobalUICiv_s00e0_43c0* (__thiscall*)(void*))0x00e03b20)(this);
}

// @ 0x00e05000
bool cSPUIGlobalUICiv_s00e0_43c0::CreatePanel(int param)
{
    if (!((bool (__thiscall*)(void*, int, void*))0x00e03620)(this, param, this))
        return false;
    if (!Initialize())
        return false;

    void* mem = AppAllocate(0x38, (const char*)0x147f400, 0, 0, 0, 0);
    cSPUINewProgressBar* bar;
    if (mem != 0) {
        void* arg = ((void* (__thiscall*)(void*, void*))0x0093b6c0)(this, (void*)0x147f3ec);
        bar = (cSPUINewProgressBar*)((void* (__thiscall*)(void*, void*))0x00e28a10)(mem, arg);
    } else {
        bar = 0;
    }
    ((void (__thiscall*)(void**, void*))0x00572680)((void**)&mpProgressBarC0, bar);
    if (mpProgressBarC0 != 0)
        mpProgressBarC0->SetMode(0);

    void* mem2 = AppAllocate(0x18, (const char*)0x147f3cc, 0, 0, 0, 0);
    cSPUILayout_s00e0_43c0* layout;
    if (mem2 != 0)
        layout = (cSPUILayout_s00e0_43c0*)SPUIHelpers_ConstructLayout(mem2);
    else
        layout = 0;

    if (layout != mpFieldC4) {
        if (layout != 0)
            ((void (__thiscall*)(void*))(*(void***)layout)[1])(layout);
        cSPUILayout_s00e0_43c0* old = mpFieldC4;
        mpFieldC4 = layout;
        if (old != 0)
            ((void (__thiscall*)(void*))(*(void***)old)[2])(old);
    }

    bool ok = mpFieldC4->Init((void*)0x147f3a4, 0x40464100, 1, (void*)0x5b598fa);
    if (ok)
        mpFieldC4->SetVisibility(0);

    for (int i = 0; i < 4; ++i) {
        (&mFieldC8)[i] = 0xc;
        mbFieldsD8[i] = 0;
    }
    return true;
}

// @ 0x00e05120
void cSPUIGlobalUICiv_s00e0_43c0::RemovePanel()
{
    if (mpField74 != 0) {
        void* handler = mpField74;
        mpField74 = 0;
        RemoveHandler(handler, mpField78, mpField7C, (void*)mField80, (void*)mField84);
    }

    void* w0 = FindWindowByID(-1);
    if (w0 != 0) {
        WShow(w0);
        WSetText108(w0, (const char*)this + 0x70);
    }

    static const int kSlotIds[4] = { 0x5a55b10, 0x5a55b20, 0x5a55b30, 0x5a55b40 };
    for (int i = 0; i < 4; ++i) {
        void* w = FindWindowByID(kSlotIds[i]);
        if (w != 0)
            WSetText108(w, (const char*)this + 0x70);
    }

    void* anchor = (char*)this + 0xdc;
    ((void (__thiscall*)(void*, void*))0x009a9600)(anchor, *(void**)((char*)anchor + 0xc));
    *(void**)((char*)anchor + 8) = (char*)anchor + 4;
    *(void**)((char*)anchor + 0xc) = 0;
    *(u8*)((char*)anchor + 0x10) = 0;
    *(void**)((char*)anchor + 0x14) = 0;
    *(void**)((char*)anchor + 4) = (char*)anchor + 4;

    if (mpProgressBarC0 != 0) {
        mpProgressBarC0->Shutdown();
        if (mpProgressBarC0 != 0) {
            cSPUINewProgressBar* bar = mpProgressBarC0;
            mpProgressBarC0 = 0;
            bar->Release();
        }
    }

    if (mpFieldC4 != 0) {
        mpFieldC4->Shutdown(1);
        if (mpFieldC4 != 0) {
            cSPUILayout_s00e0_43c0* p = mpFieldC4;
            mpFieldC4 = 0;
            ((void (__thiscall*)(void*))(*(void***)p)[2])(p);
        }
    }

    ((void (__thiscall*)(void*))0x00e03740)(this);
}

// @ 0x00e052d0
void cSPUIGlobalUICiv::RemoveCivFeedback(cCivilization_s00e0_52d0* pCiv)
{
    sCivIndexNode* pNode;
    mCivToIndex.find((const uint32_t&)pCiv, &pNode);
    sCivIndexNode* pAnchor = (sCivIndexNode*)&mCivToIndex.mpAnchorLeft;
    if (pNode != pAnchor) {
        uint32_t nIndex = pNode->mnValue;
        DeactivateCommRelPanel((int32_t)nIndex);
        cIWinProc** ppObject = &mButtons[nIndex].mpObject;
        cIWinProc* pObject = *ppObject;
        if (pObject) {
            *ppObject = 0;
            pObject->Release();
        }
        --mCivToIndex.mnSize;
        RBTreeIncrement_s00e0_52d0(pNode);
        RBTreeErase(pAnchor, pNode);
        EASTL_allocator_deallocate(pNode);
    }

    bool bHasOther = false;
    cCivilization_s00e0_52d0* pPlayer = NounManager_s00e0_52d0()->GetPlayerCivilization();
    sCivilizationList* pCivs = NounManager_s00e0_52d0()->GetCivilizationList();
    cCivilization_s00e0_52d0** it = pCivs->mpBegin;
    while (it != pCivs->mpEnd && !bHasOther) {
        cCivilization_s00e0_52d0* pIter = *it;
        if (pIter != pPlayer && pIter != pCiv && !pIter->mbHidden)
            bHasOther = true;
        ++it;
    }
    mbMinimapVisible = mbMinimapVisible && bHasOther;
    SetMinimapStateFromButton(0);
}

// @ 0x00e053c0
int32_t GetSuperweaponKind(uint32_t nButtonId)
{
    int32_t nKind = -1;
    cCivilization_s00e0_52d0* pPlayer = NounManager_s00e0_52d0()->GetPlayerCivilization();
    if (!pPlayer)
        return nKind;
    if (nButtonId == 0x5a55b40) {
        switch (pPlayer->GetSuperweaponSpeccy()) {
        case 0: nKind = 2; break;
        case 1: nKind = 8; break;
        case 2: nKind = 5; break;
        }
    } else {
        SimpleVectorU32 models = {0, 0, 0};
        cTerrainEditor* pTerrain = NounManager_s00e0_52d0()->GetCurrentTerrainSphere();
        if (pTerrain) {
            VectorAddModels(pTerrain->mnModel0, &models);
            VectorAddModels(pTerrain->mnModel1, &models);
            VectorAddModels(pTerrain->mnModel2, &models);
        }
        uint32_t nCount = (uint32_t)(models.mpEnd - models.mpBegin);
        for (uint32_t i = 0; i < nCount; ++i) {
            int32_t nModelKind = pPlayer->GetRwTypeKind(models.mpBegin[i]);
            bool bMatch;
            switch (nModelKind) {
            case 0: case 6: case 11: bMatch = (nButtonId == 0x5a55b20); break;
            case 1: case 4: case 7: bMatch = (nButtonId == 0x5a55b30); break;
            case 3: case 9: case 10: bMatch = (nButtonId == 0x5a55b10); break;
            default: bMatch = false; break;
            }
            if (bMatch) {
                nKind = nModelKind;
                if (nKind != -1)
                    break;
            }
        }
        FreeSimpleVector(&models);
    }
    return nKind;
}

// @ 0x00e05530
void cSPUIGlobalUICiv::SuperweaponClick(uint32_t nButtonId)
{
    int32_t nKind = GetSuperweaponKind(nButtonId);
    if (nKind == -1)
        return;
    cCivModeState* pState = GetCivModeStrategy()->GetState();
    if (pState->mnSelectedWeapon != nKind) {
        GetCivModeStrategy()->GetState()->EnterWeaponMode(nKind);
        return;
    }
    GetCivModeStrategy()->ExecuteMessage(0x1b, 0);
}

// @ 0x00e05590
bool DrawSuperweaponCooldown(cUIWindow* pButton, cMessage* pMsg)
{
    uint32_t nButtonId = pButton->GetID();
    cCivilization_s00e0_52d0* pPlayer = NounManager_s00e0_52d0()->GetPlayerCivilization();
    if (!pPlayer)
        return false;
    int32_t nKind = GetSuperweaponKind(nButtonId);
    if (nKind == -1)
        return false;
    if (!pPlayer->SuperweaponOnCooldown(nKind))
        return false;
    cUIWindow* pRenderable = pButton->GetRenderable();
    pRenderable->GetRenderable()->SetFlag(0, pButton != 0);
    pButton->GetRenderable()->SetFlag(0, true);

    cRenderCtx* pCtx = (cRenderCtx*)pMsg->mpWindow;
    DSub* pSub = pButton->GetSub(0x53eb526);
    float* pArea = (float*)pButton->GetArea();
    int32_t nWidth = pSub->mnWidth;
    int32_t nHeight = pSub->mnHeight;
    float mfHalfW = (pArea[2] - pArea[0]) * 0.5f;
    float mfHalfH = (pArea[3] - pArea[1]) * 0.5f;
    float mfW = (float)nWidth;
    float mfH = (float)nHeight;
    float pair38[4];
    float pair40[4];
    pSub->GetPair38(pair38, 4);
    pSub->GetPair40(pair40, 4);
    float mfA = pair38[0] * mfW * 0.5f;
    float mfB = pair38[1] * mfH * 0.5f;
    float mfRadius = mfA < mfB ? mfA : mfB;
    sBatch2D* pBatch = (sBatch2D*)pCtx->Begin2D(0);
    pBatch->SetColor(0xbf0000ff);
    float mfRatio = pPlayer->GetSuperweaponCooldown(nKind) * 0.0f;
    DrawArc(pBatch, pArea[0] + mfHalfW, pArea[1] + mfHalfH, mfRadius, 0xbf0000ff, 0xbf0000ff,
            mfRatio, mfRatio, 0, 0.0f);
    pCtx->End2D();
    return true;
}

// @ 0x00e057a0
cSPUIGlobalUICiv::cSPUIGlobalUICiv()
: mnPad74(0)
    , mnPad78(0)
    , mnPad7c(0)
    , mnPad80(0)
    , mnPad84(0)
    , mbMinimapVisible(0)
    , mbPad89(0) {
    for (int i = 0; i < 4; ++i)
        mButtons[i].mpObject = 0;
    mfCooldown = 0.0f;
    mnPadC0 = 0;
    mnPadC4 = 0;
    mCivToIndex.mpAnchorRight = 0;
    mCivToIndex.mpAnchorParent = 0;
    mCivToIndex.mbAnchorColor = 0;
    mCivToIndex.mpAnchorParent = 0;
    mCivToIndex.mbAnchorColor = 0;
    mCivToIndex.mnSize = 0;
    mCivToIndex.mpAnchorRight = (sCivIndexNode*)&mCivToIndex.mpAnchorLeft;
    mCivToIndex.mpAnchorLeft = (sCivIndexNode*)&mCivToIndex.mpAnchorLeft;
}

// @ 0x00e05870
void cSPUIGlobalUICiv::SelectStance(int32_t nStance)
{
    SimpleVectorU32 selection = {0, 0, 0};
    GetGameTerrainCursor()->GetSelection(&selection, 0x137e8e0);
    for (uint32_t* it = selection.mpBegin; it != selection.mpEnd; ++it) {
        cVehicle* pVehicle = 0;
        if (*it)
            pVehicle = ((cIObject*)*it)->AsVehicle(0x137e8e0);
        pVehicle->SetStance(nStance, false);
    }
    for (uint32_t* it = selection.mpBegin; it < selection.mpEnd; ++it) {
        if (*it)
            ((cIObject*)*it)->Release();
    }
    FreeSimpleVector(&selection);
}

// @ 0x00e05930
void cSPUIGlobalUICiv::SyncStanceWithSelection(int32_t nStance)
{
    if (!GetGameTerrainCursor()->HasSelection()) {
        SetStanceButtonsState(0, 0, 0, 0, 0);
        return;
    }
    SimpleVectorU32 selection = {0, 0, 0};
    GetGameTerrainCursor()->GetSelection(&selection, 0x137e8e0);
    bool bSetStance = false;
    bool bHasStance1 = false;
    bool bHasStance0 = false;
    if (nStance != -1) {
        bSetStance = true;
        if (nStance == 0)
            bHasStance0 = true;
        else if (nStance == 1)
            bHasStance1 = true;
    }
    for (uint32_t* it = selection.mpBegin; it != selection.mpEnd; ++it) {
        if (bHasStance0 && bHasStance1)
            break;
        cVehicle* pVehicle = 0;
        if (*it)
            pVehicle = ((cIObject*)*it)->AsVehicle(0x137e8e0);
        if (bSetStance) {
            pVehicle->SetStance(nStance, false);
        } else {
            switch (pVehicle->mnStance) {
            case 0: bHasStance0 = true; break;
            case 1: bHasStance1 = true; break;
            }
        }
    }
    bool bBoth = bHasStance0 && bHasStance1;
    SetStanceButtonsState(bHasStance0, 1, bHasStance1, 1, bBoth);
    for (uint32_t* it = selection.mpBegin; it < selection.mpEnd; ++it) {
        if (*it)
            ((cIObject*)*it)->Release();
    }
    FreeSimpleVector(&selection);
}

// @ 0x00e05bb0
bool cSPUIGlobalUICiv::DoMessage(void* pWindow, cMessage* pMsg)
{
    bool bResult = false;
    if (pMsg->mnId == 0x1b) {
        cUIWindow* pSource = pMsg->mpWindow;
        if ((uint32_t)(pSource->GetID() - 0x4655fd5) <= 3) {
            cIWinProc* pButton = mButtons[pSource->GetID() - 0x4655fd5].mpObject;
            cCivModeState* pState = GetCivModeStrategy()->GetState();
            ((cCommRelay*)pState->mpRelay)->OnMessage(pSource, pButton->GetCommandId(1));
            return bResult;
        }
    } else if (pMsg->mnId == 0x1c) {
        cUIWindow* pSource = pMsg->mpWindow;
        if ((uint32_t)(pSource->GetID() - 0x4655fd5) <= 3) {
            cCivModeState* pState = GetCivModeStrategy()->GetState();
            ((cCommRelay*)pState->mpRelay)->OnEnd();
            return bResult;
        }
    } else if (pMsg->mnId == 0x287259f6) {
        if (CommManager()->IsActive())
            return bResult;
        uint32_t nCommand = pMsg->mnParam;
        bool bStance1 = false;
        bool bStance0 = false;
        switch (nCommand) {
        case 0x5a55b10:
        case 0x5a55b20:
        case 0x5a55b30:
        case 0x5a55b40:
            SuperweaponClick(nCommand);
            bResult = true;
            break;
        case 0x4655fd5:
        case 0x4655fd6:
        case 0x4655fd7:
        case 0x4655fd8:
            if (!(GameTimeManager()->mbPaused & 1)) {
                mButtons[nCommand - 0x4655fd5].mpObject->FireSelectedCommEvent();
                bResult = true;
            }
            break;
        case 0x4c61b50:
            bStance0 = true;
            bStance1 = true;
            SetStanceButtonsState(bStance1, 1, bStance0, 1, 0);
            SelectStance(bStance0 ? 1 : 0);
            break;
        case 0x4c61dd8:
            bStance1 = true;
            SetStanceButtonsState(bStance1, 1, bStance0, 1, 0);
            SelectStance(bStance0 ? 1 : 0);
            break;
        case 0x562a141:
            SetMinimapStateFromButton(0);
            bResult = true;
            break;
        case 0x6453746:
            GetCivModeStrategy()->OnTechLevelUpgradeButtonPress();
            break;
        }
        return bResult;
    } else if (pMsg->mnId == 0xd) {
        return DrawSuperweaponCooldown((cUIWindow*)pWindow, pMsg);
    }
    return bResult;
}

// @ 0x00e060c0
void cSPUIGlobalUICiv::SyncSuperweaponButton(uint32_t nWindowId, int32_t* pnState, int32_t nIndex)
{
    cCivilization_s00e0_52d0* pPlayer = NounManager_s00e0_52d0()->GetPlayerCivilization();
    if (!pPlayer)
        return;
    cUIWindow* pWindow = FindWindowByID(nWindowId);
    int32_t nSelected = GetCivModeStrategy()->GetState()->mnSelectedWeapon;
    int32_t nKind = GetSuperweaponKind(nWindowId);
    if (nKind != *pnState) {
        *pnState = nKind;
        SetTooltipByKey(pWindow, mnPadC4, GetKindName(nKind), -1);
    }
    UpdateSuperweaponTooltip(pWindow, (uint32_t)nKind);
    bool bVisible = (nKind != -1);
    pWindow->SetVisible(1, bVisible);
    pWindow->SetVisible(2, pPlayer->CanUseSuperweapon(nKind));
    cUIWindow* pInner = pWindow->FindWindowByID(0x8ed27e7a);
    pInner->SetFlag(4, nSelected == nKind);
    cUIWindow* pNext = FindWindowByID(nWindowId + 1);
    if (pNext)
        pNext->SetVisible(1, !bVisible);
    if (nKind != -1) {
        if (pPlayer->SuperweaponOnCooldown(nKind)) {
            pWindow->Invalidate();
            mbCooldownShown[nIndex] = 1;
        } else if (mbCooldownShown[nIndex]) {
            pWindow->Invalidate();
            mbCooldownShown[nIndex] = 0;
        }
    }
}

// @ 0x00e06220
void cSPUIGlobalUICiv_s00e0_6220::Update(int32_t nDelta)
{
    m_fCommRelTimer += (float)(uint32_t)nDelta;

    bool bCommActive = CommManager_s00e0_6220()->IsActive();
    const uint32_t aWindowIDs[2] = { kCommWindowIDs[0], kCommWindowIDs[1] };
    for (int32_t i = 0; i < 2; ++i) {
        IWindow* pWindow = FindWindowByID(aWindowIDs[i]);
        if (pWindow == nullptr)
            continue;
        bool bVisible = pWindow->IsVisible();
        if (bVisible != bCommActive)
            pWindow->SetState(1, bVisible == 0);
    }

    if (bCommActive != m_bCommScreenActive)
        SetMinimapStateFromButton(bCommActive);
    m_bCommScreenActive = bCommActive;

    for (int32_t i = 0; i < 4; ++i) {
        if (m_commRelPanels[i].m_bActive && m_commRelPanels[i].m_pCiv != nullptr)
            UpdateCommRelPanel(nDelta, i);
    }

    BindCommRelData(kCommRelDataKeys[0], &m_apCommRelData[0], 0);
    BindCommRelData(kCommRelDataKeys[1], &m_apCommRelData[1], 1);
    BindCommRelData(kCommRelDataKeys[2], &m_apCommRelData[2], 2);
    BindCommRelData(kCommRelDataKeys[3], &m_apCommRelData[3], 3);

    RefreshCommRelPanels();

    cCivilization_s00e0_6220* pCiv = NounManager_s00e0_6220()->GetPlayerCivilization();
    if (pCiv != nullptr) {
        int32_t nTurn = pCiv->GetTurn();
        SetCommRelProgress(kProgressCurrentA, kProgressCurrentB, kProgressCurrentC,
                           pCiv->m_nStage < 3 ? GetCurrentTurn() - nTurn : 0);
        SetCommRelProgress(kProgressLoyaltyA, kProgressLoyaltyB, kProgressLoyaltyC,
                           pCiv->m_nStage < 4 ? GetLastTurn() - nTurn : 0);
    }
}

// @ 0x00e063d0
void cSPUIGlobalUICiv_s00e0_6220::SetCommScreenVisibility(cCivilization_s00e0_6220* pCiv, bool bOn)
{
    if (pCiv == NounManager_s00e0_6220()->GetPlayerCivilization())
        return;
    if (mCivToIndex.Find(pCiv) == &mCivToIndex.m_stHeader)
        return;

    uint32_t nIndex = mCivToIndex.GetCounter(pCiv);
    cCommRelPanel* pPanel = &m_commRelPanels[nIndex];

    IWindow* pMain = FindWindowByID(kRelPanelMainWindow)->CreateChild(pPanel->m_pData, 0);
    IWindow* pSub = FindWindowByID(kRelPanelSubWindow)->CreateChild(pPanel->m_pData, 0);

    pMain->Select();
    pMain->SetState(0x10, bOn);
    pSub->SetState(0x10, bOn);

    ISubWindow* pMainChild = pMain->GetSubWindow(kRelPanelChildKey);
    ISubWindow* pSubChild = pSub->GetSubWindow(kRelPanelChildKey);

    pMainChild->SetState(4, bOn);
    pSubChild->SetState(4, bOn);

    pMain->Refresh();
    pSub->Refresh();
}

// @ 0x00e064f0
void cSPUIGlobalUICiv_s00e0_6220::AssignCommRelPanel(int32_t nIndex, cCivilization_s00e0_6220* pCiv)
{
    mCivToIndex.GetCounter(pCiv) = nIndex;

    cCommRelPanel* pPanel = &m_commRelPanels[nIndex];
    pPanel->m_bActive = true;
    pPanel->m_bShown = false;

    cCivilization_s00e0_6220* pOld = pPanel->m_pCiv;
    if (pCiv != pOld) {
        if (pCiv != nullptr)
            pCiv->AddRef();
        pPanel->m_pCiv = pCiv;
        if (pOld != nullptr)
            pOld->Release();
    }

    ActivateCommRelPanel(nIndex);
}

// @ 0x00e06560
void cSPUIGlobalUICiv_s00e0_6220::HandleMessage(uint32_t nMessage, void* pData)
{
    switch (nMessage) {
    case kMessageCommCivA:
    case kMessageCommCivB:
        SetCommScreenVisibility(((cCivMessage*)pData)->m_pCiv, nMessage == kMessageCommCivA);
        break;
    case kMessageCommClose:
        FUN_00e05930(-1);
        break;
    }
    cSPUIGlobalUI_s00e0_6220::HandleMessage(nMessage, pData);
}

// @ 0x00e065c0
void cSPUIGlobalUICiv_s00e0_6220::InitCommRelPanels()
{
    bool bAny = false;
    cCivilizationList* pList = NounManager_s00e0_6220()->GetCivilizationList();
    cCivilization_s00e0_6220** pCiv = pList->m_pBegin;
    cCivilization_s00e0_6220** pCivEnd = pList->m_pEnd;
    if (pCiv != pCivEnd) {
        do {
            cCivilization_s00e0_6220* pCur = *pCiv;
            if (!pCur->m_bNotPlayable && pCur->m_bVisible) {
                AssignCommRelPanel(pCur->m_nPanelIndex, pCur);
                bAny = true;
            }
            ++pCiv;
        } while (pCiv != pCivEnd);

        if (bAny) {
            m_bFlag88 = true;
            SetMinimapStateFromButton(0);
        }
    }
}

// @ 0x00e06630
void cSPUIGlobalUICiv_s00e0_6220::AssignFreeCommRelPanel(cCivilization_s00e0_6220* pCiv)
{
    if (mCivToIndex.Find(pCiv) != &mCivToIndex.m_stHeader)
        return;

    uint32_t nIndex = 0;
    while (nIndex < 4 && m_commRelPanels[nIndex].m_bActive)
        ++nIndex;

    AssignCommRelPanel(nIndex, pCiv);
    pCiv->m_nPanelIndex = nIndex;

    if (nIndex == 0) {
        m_bFlag88 = true;
        SetMinimapStateFromButton(0);
    }
}
