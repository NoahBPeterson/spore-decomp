// src/game/SPGonzago/SPCreatureDisplayStrategy.cpp -- migrated from slice(s) s00d2dd20, s00d2cea0, s00d2bd00, s00b6b1a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureDisplayStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyManager.h"
#include "cSPUILayout.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cString.h"
#include "SP/cSPTimer.h"
#include "cSPVector2.h"
#include <new>
#include <xmmintrin.h>
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPUINewProgressBar.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern wchar_t       gEmptyString16;    // 0x01667bac eastl::gEmptyString16 (L"")
#pragma warning(disable : 4100)

// ---- items of slice s00b6b1a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;
extern wchar_t       gEmptyString16;    // 0x01667bac eastl::gEmptyString16 (L"")
struct cTextRoot;
cTextRoot* FUN_0067de40();                                                     // 0x0067de40
struct WString {
    const wchar_t* mBegin;   // +0x00
    const wchar_t* mEnd;     // +0x04
    const wchar_t* mCap;     // +0x08

    void assign(const wchar_t* b, const wchar_t* e);   // 0x00423650
    void RangeInitialize(const wchar_t* s);            // 0x00579a90
    ~WString() {
        if ((((u32)((const char*)mCap - (const char*)mBegin)) & 0xfffffffeu) > 2 && mBegin != 0)
            delete[] (wchar_t*)mBegin;
    }
};
struct cString {
    u32 m00;        // +0x00
    u32 m04;        // +0x04
    u32 m08;        // +0x08
    u32 m0c;        // +0x0c
    u16 m10;        // +0x10
    u16 m12;        // +0x12

    cString();                                         // 0x006b5060
    cString(u32 a, u32 b, const wchar_t* text);        // 0x006b5770
    u8  Load(u32 a, u32 b, int c);                     // 0x006b54b0
    const wchar_t* GetText();                          // 0x006b55c0
    ~cString();                                        // 0x006b5240
};
struct EStr {
    wchar_t* mBegin;    // +0x00
    wchar_t* mEnd;      // +0x04
    wchar_t* mCap;      // +0x08
    u32      m0c;       // +0x0c
    wchar_t* m10;       // +0x10
                        // +0x14: 0x40-byte inline buffer

    EStr* Construct(const wchar_t* text);              // 0x006743f0
    EStr* Init(const wchar_t* a, const wchar_t* b);    // 0x00672750
};
struct cTextObj;
struct cTextRoot {
    virtual void      r00();
    virtual void      r04();
    virtual void      r08();
    virtual void      r0c();
    virtual void      r10();
    virtual void      r14();
    virtual void      r18();
    virtual void      r1c();
    virtual cTextObj* r20();                            // +0x20
};
struct cTextObj {
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
    virtual void v30(cString* out, u32* key, int flag); // +0x30
};
struct cObjBase {                                       // anything with slot +0x0c
    virtual void  b00();
    virtual void  b04();
    virtual void  b08();
    virtual void* b0c(u32 key);                         // +0x0c
};
struct cSpeciesProfile {
    void GetUiName(WString* out);                       // 0x004da330
};
struct cSpeciesInfo {
    u8  pad000[0x15c];
    int m15c;                                           // +0x15c
};
struct cCreature {                                      // cSPCreatureCitizen-ish
    virtual void  c00();
    virtual void  c04();
    virtual void  c08();
    virtual void* c0c(u32 key);                         // +0x0c
    u8  pad010[0xb20 - 0x10];
    cSpeciesProfile* mSpecies;                          // +0xb20
    u8  padb24[0xb38 - 0xb24];
    WString mName;                                      // +0xb38
    u8  padb44[0xb58 - 0xb44];
    u8  mFlagsB58;                                      // +0xb58

    u8      FUN_00c0b770();                             // 0x00c0b770
    u8      IsLeader();                                 // 0x00c232d0
    u8      Flag388();                                  // 0x00c0c0e0
    u8      Flag389();                                  // 0x00c0c100
    int     FUN_00c22dc0();                             // 0x00c22dc0
    cSpeciesInfo* FUN_00c04590();                       // 0x00c04590  Get()
};
struct cCtxTag {
    u32 mKey;                                           // +0x00
    void Destroy();                                     // 0x006886e0
};
// ---- items of slice s00b6b1a0 end

// ---- items of slice s00d2bd00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char gsAllocatorFile[];
#define nullptr 0
class cUIWindow {
public:
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
    virtual int32_t IsShown();                  // 0x028
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual float* GetPosition();               // 0x038
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void v5c();
    virtual void SetRect(void* pRect);          // 0x060
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void SetPosition(float fX, float fY);          // 0x070
virtual void v74();
virtual void v78();
    virtual void SetVisible(int32_t nShow, int32_t nFade); // 0x07c
};
class cEventList {
public:
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
virtual void vb8();
virtual void vbc();
    virtual void SetActive(int32_t nActive);    // 0x0c0

    uint8_t mPad004[0xa0];                      // 0x004
    void** mpEntryBegin;                        // 0x0a4
    void** mpEntryEnd;                          // 0x0a8
};
class cSPUILayout_s00d2_bd00 {
public:
    void* FindWindowByID(int32_t nId, int32_t nSearchChildren);   // 0x008105b0
};
class cSPTimer {
public:
    void Start();                               // 0x00bc30f0
    bool IsRunning();                           // 0x00feba90
    uint64_t GetElapsedTime();                  // 0x00bc3190
};
class cSPUIGlobalUI {
public:
    void Construct();                           // 0x00e03ab0
    void SetVisibility(int32_t nVisible);       // 0x00e01350
    void* FindWindowByID(int32_t nId, int32_t nSearchChildren);   // 0x00e012b0
};
class cSPUIEventLog {
public:
    void SetVisibility(int32_t nVisible);       // 0x00dd8da0
};
class cAvatar {
public:
    bool IsDisplayMode();                       // 0x00c0c120
};
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};
class cCreatureTimerBar {
public:
    void Update(cAvatar* pAvatar, void* pCreature);
    void SetBarPosition(float fValue);
    void SetVisibility(int32_t nVisible);       // 0x00d2bc90

    uint8_t mbVisible;                          // 0x000
    uint8_t mPad001[0x03];                      // 0x001
    cSPUILayout_s00d2_bd00* mpLayout;                      // 0x004
    float mafFillRect[4];                       // 0x008
    uint8_t mPad018[0x20];                      // 0x018
    cSPTimer mFadeTimer;                        // 0x038
};
class cCreatureData {
public:
    uint8_t mPad000[0x5c8];                     // 0x000
    int32_t mnHealth;                           // 0x5c8
};
class cCreature_s00d2_bd00 {
public:
    uint8_t mPad000[0xb20];                     // 0x000
    cCreatureData* mpData;                      // 0xb20
    uint8_t mPadB24[0x90];                      // 0xb24
    int32_t mnMaxHealth;                        // 0xbb4
};
class cCreatureDisplayStrategy {
public:
    void UpdateAfterEditor(void* pItem);
    void SetUIVisible(int32_t nVisible);
    void ReloadTuning();
    void AddPosseItem(void* pItem);
    void OnSelectItem(void* pSelection, int32_t nMode);
    void Activate(int32_t nMode, int32_t nFlags);

    uint8_t mPad000[0x04];                      // 0x000
    uint8_t mbField04;                          // 0x004
    uint8_t mPad005[0x50];                      // 0x005
    uint8_t mbField55;                          // 0x055
    uint8_t mPad056[0x02];                      // 0x056
    cSPUIGlobalUI* mpGlobalUI;                  // 0x058
    cEventList* mpEventList;                    // 0x05c
    uint8_t mPad060[0x48];                      // 0x060
    cCreatureTimerBar mTimerBar;                // 0x0a8
};
class cBucketNode {
public:
    uint32_t mnHash;                            // 0x000
    uint8_t mPad004[0x10];                      // 0x004
    cBucketNode* mpNext;                        // 0x014
};
class cBucketTable {
public:
    void Rebuild(uint32_t nBucketCount);

    uint8_t mPad000[0x04];                      // 0x000
    void** volatile mpBuckets;                  // 0x004
    uint32_t mnBucketCount;                     // 0x008
    uint8_t mPad00c[0x10];                      // 0x00c
    void* mpFreeHead;                           // 0x01c
    uint8_t mPad020[0x04];                      // 0x020
    void* mpPoolLo;                             // 0x024
    void* mpPoolHi;                             // 0x028
    uint8_t mPad02c[0x04];                      // 0x02c
    void* mpSentinel;                           // 0x030
};
class cPoolBlock {
public:
    uint8_t mPad000[0x04];                      // 0x000
    void* mpNextBlock;                          // 0x004
};
class cPool {
public:
    void Advance();
    void Allocate(void** ppValue);

    uint8_t mPad000[0x08];                      // 0x000
    uint8_t* mpCurrent;                         // 0x008
    uint8_t* mpBlock;                           // 0x00c
    uint8_t* mpBlockEnd;                        // 0x010
    cPoolBlock** mppBlockCursor;                // 0x014
};
class cAllocPool {
public:
    void Allocate(void** ppValue);

    cPoolBlock** mppBlockBase;                  // 0x000
    int32_t mnCapacity;                         // 0x004
    uint8_t mPad008[0x10];                      // 0x008
    void* mpFreeEntry;                          // 0x018
    uint8_t* mpBlock;                           // 0x01c
    uint8_t* mpBlockEnd;                        // 0x020
    cPoolBlock** mppBlockCursor;                // 0x024
};
class cListNode {
public:
    uint8_t mPad000[0x04];                      // 0x000
    cRefCounted* mpValue;                       // 0x004
    cListNode* mpNext;                          // 0x008
};
class cListIterator {
public:
    cListNode* mpNode;                          // 0x000
    void** mpSlot;                              // 0x004
};
class cNodeList {
public:
    cListIterator* Erase(cListIterator* pOut, cListNode* pNode, cListNode** ppHead);

    uint8_t mPad000[0x0c];                      // 0x000
    int32_t mnCount;                            // 0x00c
    uint8_t mPad010[0x0c];                      // 0x010
    cListNode* mpFreeHead;                      // 0x01c
    uint8_t mPad020[0x04];                      // 0x020
    void* mpPoolLo;                             // 0x024
    void* mpPoolHi;                             // 0x028
    uint8_t mPad02c[0x04];                      // 0x02c
    void* mpSentinel;                           // 0x030
};
void* __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nFlags,
                           int32_t nAlignment, const char* pFile, int32_t nLine);
void __cdecl operator_delete_array(void* pBlock);
void* __stdcall AllocHashBuckets(uint32_t nBucketCount);  // 0x00c765a0
void __stdcall RaisePoolOverflow(int32_t nA, int32_t nB); // 0x01044f80
void ResetBarFade();                            // 0x00bc3170
void OnCreatureModeOff();                       // 0x00b6c280
cSPUIEventLog* EventLog();                      // 0x00b3d3e0
void* NounManager();                            // 0x00b3d300
void* GetAvatarNoun(void* pManager);            // 0x00b1fdb0
void* GetItemID(void* pNoun);                   // 0x00b1f9c0
void* FindPosseItem(void* pPosse, int32_t nIndex);      // 0x00e24c90
void SetWindowImage(void* pWindow, int32_t nImage);     // 0x00807bb0
int32_t CreateImageFromResource2(void* pRes, void** ppImage, int32_t nA, int32_t nB, int32_t nC); // 0x00806230
void FUN_00c0b780(void* pA, int32_t nB);
void FUN_00c0b7a0(void* pA, int32_t nB);
void FUN_00c0b950();
void FUN_00d49450(void* pA);
void FUN_00d2e4a0();
void FUN_00d2b8f0(void* pA, void* pB);
void FUN_00d2b5f0(void* pA);
void FUN_00d20950(void* pA, int32_t nB);
void FUN_00d49820(void* pA, int32_t nB);
void FUN_00d38780(void* pA, int32_t nB);
void FUN_00d4a570();
void FUN_00f924e0(void* pA);
void FUN_00c0bc00();
void FUN_00e39710(void* pA);
void FUN_00d38840();
void KillSetiEffects(uint32_t nId);             // 0x00435ed0
void* GetRecorderState();                       // 0x00435e90
void* App();                                    // 0x0067dd10
void FUN_00e25710(void* pA, void* pB);
void FUN_009512c0();
void* FUN_009512d0(void* pA, int32_t nLine);
void FUN_00ac8f00(void* pOut, uint32_t nId, int32_t nTag, float fA, float fB);
void FUN_00dd5a10(float fA, float fB);
void* GetTuningValue(void* pA);                 // 0x00c04590
class cSPVector2_s00d2_bd00 {
public:
    float x;
    float y;
};
float g_fTuningDefault = 0.0f;
float g_fOne = 1.0f;
// ---- items of slice s00d2bd00 end

// ---- items of slice s00d2cea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cRoundedQueuePool {
    uint32_t   mPad00[6];                                    // +0x00 .. +0x17
    long long* mpEnd;                                        // +0x18
    uint32_t   mPad1c;                                       // +0x1c
    long long* mpCapacity;                                   // +0x20
    void Allocate(void** slot);                              // 0x00d2ca90
};
}
namespace SP {
struct cRoundedQueue {
    uint32_t         mPad00;                                 // +0x00
    cRoundedQueuePool mPool;                                 // +0x04
    void Append(float value);
};
}
// ---- items of slice s00d2cea0 end

// ---- items of slice s00d2dd20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kTwoPow32;        // 0x013f4fd0  4.2949673e+09f (int -> float, negative)
extern float kInv10000;        // 0x013ebca0  0.0001f
extern float kHundred;         // 0x013ec4d0  100.0f
extern float kInv100;          // 0x013eb960  0.01f
extern float kHintThresholdLo; // 0x01582ff0
extern float kHintThresholdHi; // 0x01582ff4
extern float kMadMax;          // 0x01687a0c
extern unsigned short g_018ac46e;  // 0x018ac46e  hint-bar label id
extern unsigned short g_018ac464;  // 0x018ac464  hint-bar label id
#pragma pack(push, 4)
#pragma pack(pop)
struct Vector3 { float x, y, z; };
struct Matrix3Rows { float m[9]; };
class cAvatar_s00d2_dd20;
class cTerrainSphere {
public:
    unsigned char mPad00[0x10f0];
    float         mHeight;      // +0x10f0
    float         mHeightMax;   // +0x10f4
};
class cGameNounManager {
public:
    cAvatar_s00d2_dd20*        GetAvatar();                     // 0x00b1fdb0
    cTerrainSphere* GetCurrentTerrainSphere();       // 0x00f67d90
};
cGameNounManager* NounManager_s00d2_dd20();                     // 0x00b3d300
class cAvatarMood {
public:
    double FUN_00bfc490();                           // 0x00bfc490  st0 result
    unsigned char mPad00[4];
};
struct AvatarFlagsB58 {
    unsigned int mFlag0  : 1;
    unsigned int mFlag1  : 1;
    unsigned int mFlag2  : 1;
    unsigned int mFlag3  : 1;
    unsigned int mFlag4  : 1;
    unsigned int mFlag5  : 1;
    unsigned int mFlag6  : 1;
    unsigned int mFlag7  : 1;
    unsigned int mFlag8  : 1;
    unsigned int mFlag9  : 1;
    unsigned int mFlag10 : 1;
    unsigned int mFlag11 : 1;
};
class cLocomotive {
public:
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
    virtual const Vector3* GetPosition();            // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual bool FUN_0048();                         // +0x48
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
    virtual double FUN_0074();                       // +0x74  st0 result
};
class cSpeciesData {
public:
    unsigned char mPad00[0x61c];
    int           mMode;         // +0x61c
};
class cAvatar_s00d2_dd20 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cAvatar_s00d2_dd20* FUN_000C(unsigned int id);                                  // 0x0c
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
    virtual void v80();                                                              // 0x80
    virtual void FUN_0084(void* arg);                                                // 0x84
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAC();
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
    virtual int  FUN_00D8();                                                         // 0xd8

    void*  FUN_00c04590();                            // 0x00c04590
    double FUN_00c0b9c0();                            // 0x00c0b9c0  st0 result
    void*  FUN_00c0ee60(unsigned char slot, int flag);   // 0x00c0ee60
    cAvatar_s00d2_dd20* FUN_00c0ee70();                          // 0x00c0ee70  GetTargetAsCreature
    cAvatar_s00d2_dd20* FUN_00c0ee90();                          // 0x00c0ee90  ApplyCombatTarget
    bool   FUN_00c0b770();                            // 0x00c0b770
    void   FUN_00c1d400(unsigned int id, unsigned int guid);  // 0x00c1d400
    void*  FUN_00c14e70(unsigned int guid);           // 0x00c14e70

    unsigned char  mPad04[0xc0 - 0x04];
    cLocomotive    mLocomotive;  // +0xc0
    unsigned char  mPadC4[0x137 - 0xc4];
    unsigned char  mField137;    // +0x137
    unsigned char  mPad138[0x5a8 - 0x138];
    cAvatarMood    mMood;        // +0x5a8
    unsigned char  mPad5ac[0x5e0 - 0x5ac];
    float          mMadTimer;    // +0x5e0
    unsigned char  mPad5e4[0xb20 - 0x5e4];
    cSpeciesData*  mpSpecies;    // +0xb20
    unsigned char  mPadB24[0xb28 - 0xb24];
    unsigned char  mCombatDataB28[0xb4c - 0xb28];  // +0xb28  handed to the mode helpers
    void*          mpOwnerB4c;   // +0xb4c  object whose +8 owns the avatar
    unsigned char  mPadB50[0xb58 - 0xb50];
    AvatarFlagsB58 mFlagsB58;    // +0xb58
    unsigned char  mSlotB5c;     // +0xb5c
    unsigned char  mFieldB5e;    // +0xb5e
};
class cUIWindow_s00d2_dd20 {
public:
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
virtual void v78();
    virtual void SetState(int kind, bool flag);   // +0x7c
    virtual void SetText(const void* text);       // +0x80
};
class cSPUILayout_s00d2_dd20 {
public:
    cUIWindow_s00d2_dd20* FindWindowByID(unsigned int id, int flag);   // 0x008105b0
};
class cPosseUI {
public:
    cSPUILayout_s00d2_dd20* GetBuffer(unsigned int id, int flag);        // 0x0093b6c0
    void         FUN_00e012d0(const void* label, float value); // 0x00e012d0
};
class cSPUINewProgressBar {
public:
    void Update(float ratio, int value);         // 0x00e29da0
};
class cHintObject {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cAvatar_s00d2_dd20* FUN_000C(unsigned int id);  // +0x0c
};
class cHintProvider {
public:
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
    virtual cHintObject* FUN_0034();             // +0x34
};
cHintProvider* GetHintProvider();                // 0x00b3d240
class cSub128 {
public:
    void FUN_00d2d560(float value);              // 0x00d2d560
    void FUN_00d2d0b0(int tick);                 // 0x00d2d0b0
};
class cPlanetModel {
public:
    Vector3* GetNormalAt(Vector3* pOut, const Vector3* pPos);    // 0x00b7e3b0
};
cPlanetModel* PlanetModel();                                     // 0x00b3d350
void  OrthogonalVector(Vector3* pOut, const Vector3* pIn);       // 0x006985b0
void* Matrix3FromFacingAndUp(Matrix3Rows* pOut, const Vector3* pFacing,
                             const Vector3* pUp);                // 0x0069b440
class cXformMsg {
public:
    cXformMsg();                                 // 0x00434040
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void FUN_0018(void* p);              // +0x18
    virtual void v1c();
    virtual void FUN_0020(void* p);              // +0x20

    unsigned short mFlags;    // +0x04
    unsigned short mSeq;      // +0x06
    Vector3        mPos;      // +0x08
    unsigned char  mPad14[0x18 - 0x14];
    float          mDist;     // +0x18
    unsigned char  mPad1c[0x24 - 0x1c];
    Matrix3Rows    mMatrix;   // +0x24
};
void  VerbTray_Update(float value);                      // 0x00d4a930
void  FUN_00c17350(unsigned int guid, int arg);          // 0x00c17350
void  EA_Locale_SetNumberString(int value, int hi, void* out, unsigned int radix); // 0x00881ae0
void  FUN_00b69990(void* p);                             // 0x00b69990
void* FUN_00d99500(void* p);                             // 0x00d99500
int   FUN_00c0c1b0(cAvatar_s00d2_dd20* p);                          // 0x00c0c1b0
double FUN_00d2e350();                                   // 0x00d2e350
int   FUN_00d2e490();                                    // 0x00d2e490
class cCreatureTimerBar_s00d2_dd20 {
public:
    void Update(int tick, cAvatar_s00d2_dd20* avatar);      // 0x00d2bd00
};
class cCreatureDisplayStrategy_s00d2_dd20 {
public:
    void DrawLayer(unsigned int param_2, int tick);   // 0x00d2dd20  (this file)

    void FUN_00d2b720(cAvatar_s00d2_dd20* avatar);               // 0x00d2b720
    void FUN_00d2b950();                              // 0x00d2b950
    void FUN_00d2b6b0(cAvatar_s00d2_dd20* target);               // 0x00d2b6b0
    void FUN_00d2d7d0(void* sub, float value);        // 0x00d2d7d0
    void FUN_010829f0(void* param);                   // 0x010829f0

    unsigned char  mPad00[0x4c];
    cAvatar_s00d2_dd20*       mpAvatarTarget;    // +0x4c
    int            mPrevHint;         // +0x50
    unsigned char  mPrevFlag;         // +0x54
    unsigned char  mbDisplayEnabled;  // +0x55
    unsigned char  mPad56[0x58 - 0x56];
    cPosseUI*      mpPosseUI;         // +0x58
    unsigned char  mPad5c[0xa8 - 0x5c];
    cCreatureTimerBar_s00d2_dd20 mTimerBar;      // +0xa8
    unsigned char  mPadB0[0x124 - 0xb0];
    cSPUINewProgressBar* mpProgressBar;   // +0x124
    cSub128        mSub128;           // +0x128
    unsigned char  mPad12c[0x190 - 0x12c];
    unsigned char  mSub190;           // +0x190
};
// ---- items of slice s00d2dd20 end

// @ 0x00b6b4c0
EStr* FUN_00b6b4c0(EStr* result, void* obj)
{
    cCreature* creature = 0;
    if (obj != 0)
        creature = (cCreature*)((cObjBase*)obj)->b0c(0xd0036e08);

    cCtxTag ctx;
    ctx.mKey = 0xcaa303ac;

    WString name;
    name.mBegin = &gEmptyString16;
    name.mEnd   = &gEmptyString16;
    name.mCap   = &gEmptyString16 + 1;

    creature->mSpecies->GetUiName(&name);

    if (creature->FUN_00c04590() != 0 && creature->FUN_00c04590()->m15c == 7) {
        cString s(0xad56080c, 0x564e650, L"~Pet");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if (creature->FUN_00c0b770() == 0) {
        cString s(0xad56080c, 0xb32fe522, L"~Baby");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if (creature->Flag388()) {
        cString s(0xad56080c, 0x595b72b, L"~Epic");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if (creature->Flag389()) {
        cString s(0xad56080c, 0x94acb6f7, L"~MiniBoss");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if ((creature->mFlagsB58 & 1) != 0) {
        cString s(0xad56080c, 0xf32fe51b, L"~Alpha");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        ctx.Destroy();
        return result;
    }

    result->Construct(name.mBegin);
    ctx.Destroy();
    return result;
}

// @ 0x00d2bd00
void cCreatureTimerBar::Update(cAvatar* pAvatar, void* pCreature)
{
    struct cSPFillRect {
        float x;
        float y;
        float x2;
        float y2;
    };

    cUIWindow* pBar;

    if (!mbVisible || (!pAvatar->IsDisplayMode() && !mFadeTimer.IsRunning())) {
        pBar = (cUIWindow*)mpLayout->FindWindowByID(0x738ff863, 1);
        if ((pBar->IsShown() & 1) != 0) {
            mFadeTimer.Start();
            return;
        }
    }
    else {
        pBar = (cUIWindow*)mpLayout->FindWindowByID(0x738ff863, 1);
        pBar->SetVisible(1, 1);

        cCreature_s00d2_bd00* pCreatureData = (cCreature_s00d2_bd00*)pCreature;
        cCreatureData* pData = pCreatureData->mpData;

        float fFraction;
        if (pData->mnHealth > 0) {
            fFraction = (float)pCreatureData->mnMaxHealth - (float)pData->mnHealth;
            fFraction = fFraction / (float)pCreatureData->mnMaxHealth;
            if (fFraction < 0.0f)
                fFraction = 0.0f;
            if (fFraction > g_fOne)
                fFraction = g_fOne;
        }
        else {
            fFraction = 0.0f;
        }

        cUIWindow* pFill = (cUIWindow*)mpLayout->FindWindowByID(0x938ff6d1, 1);

        cSPFillRect rect;
        rect.x = mafFillRect[0];
        rect.y = mafFillRect[1];
        rect.x2 = (mafFillRect[2] - mafFillRect[0]) * fFraction + mafFillRect[0];
        rect.y2 = mafFillRect[3];
        pFill->SetRect(&rect);

        if (!mFadeTimer.IsRunning())
            return;

        if (pAvatar->IsDisplayMode()) {
            mFadeTimer.Start();
            return;
        }

        if (mFadeTimer.GetElapsedTime() <= 2000)
            return;

        ResetBarFade();
    }

    pBar->SetVisible(1, 0);
}

// @ 0x00d2beb0
void cCreatureTimerBar::SetBarPosition(float fValue)
{
    cUIWindow* pWindow = (cUIWindow*)mpLayout->FindWindowByID(0x738ff863, 1);
    float* pPosition = pWindow->GetPosition();
    pWindow->SetPosition(pPosition[0], fValue);
}

// @ 0x00d2bf60
void cBucketTable::Rebuild(uint32_t nBucketCount)
{
    void** pNewBuckets = (void**)AllocHashBuckets(nBucketCount);

    for (uint32_t nBucket = 0; nBucket < mnBucketCount; nBucket++) {
        cBucketNode* pNode = (cBucketNode*)mpBuckets[nBucket];
        while (pNode != nullptr) {
            uint32_t nHash = pNode->mnHash;
            mpBuckets[nBucket] = pNode->mpNext;
            pNode->mpNext = (cBucketNode*)pNewBuckets[nHash % nBucketCount];
            pNewBuckets[nHash % nBucketCount] = pNode;
            pNode = (cBucketNode*)mpBuckets[nBucket];
        }
    }

    void* pOldBuckets = mpBuckets;
    if (mnBucketCount > 1 && pOldBuckets != mpSentinel) {
        if (pOldBuckets >= mpPoolLo && pOldBuckets < mpPoolHi) {
            *(void**)pOldBuckets = mpFreeHead;
            mpFreeHead = pOldBuckets;
        }
        else {
            operator_delete_array(pOldBuckets);
        }
    }

    mpBuckets = pNewBuckets;
    mnBucketCount = nBucketCount;
}

// @ 0x00d2c000
void cCreatureDisplayStrategy::UpdateAfterEditor(void* pItem)
{
    cUIWindow* pWindow;
    void* pAvatar = GetAvatarNoun(NounManager());
    void* pItemId = GetItemID(pItem);

    pWindow = (cUIWindow*)mpGlobalUI->FindWindowByID(0x3d99151, 1);
    SetWindowImage(pWindow, 1);

    void* pImage = nullptr;
    if (CreateImageFromResource2(pItemId, &pImage, 0, 0, 0) != 0)
        SetWindowImage(pWindow, (int32_t)pImage);

    FUN_00c0b780(pAvatar, 1);
    FUN_00c0b7a0(pWindow, 1);
    FUN_00c0b7a0(pWindow, 2);

    pWindow = (cUIWindow*)mpGlobalUI->FindWindowByID(0x578f7f8, 1);
    pWindow->SetVisible(1, 0);
    FUN_00d49450(pWindow);
    FUN_00c0b7a0(pWindow, 0);
    FUN_00d2e4a0();
}

// @ 0x00d2c200
void cCreatureDisplayStrategy::SetUIVisible(int32_t nVisible)
{
    if (mpGlobalUI != nullptr)
        mpGlobalUI->SetVisibility(nVisible);

    if (mpEventList != nullptr) {
        int32_t nEntryCount = (int32_t)(((uint8_t*)mpEventList->mpEntryEnd -
                                        (uint8_t*)mpEventList->mpEntryBegin) >> 3);
        mpEventList->SetActive((nVisible != 0 && (uint32_t)nEntryCount > 0) ? 1 : 0);
    }

    cSPUIEventLog* pEventLog = EventLog();
    if (pEventLog != nullptr)
        pEventLog->SetVisibility(nVisible);

    if (nVisible == 0)
        OnCreatureModeOff();

    mTimerBar.SetVisibility(nVisible);
    mbField55 = (uint8_t)nVisible;
}

// @ 0x00d2c280
void cCreatureDisplayStrategy::ReloadTuning()
{
    cSPVector2_s00d2_bd00 values;
    values.x = 0.0f;
    values.y = g_fTuningDefault;

    FUN_00ac8f00(&values, 0xff259ba2, 0, 0.0f, -100.0f);
    FUN_00dd5a10(values.y, values.x);
    FUN_00dd5a10(values.x, values.y);
}

// @ 0x00d2c2e0
void cCreatureDisplayStrategy::AddPosseItem(void* pItem)
{
    void* pPosse = FindPosseItem(mpGlobalUI, (int32_t)pItem);
    if (pPosse != nullptr) {
        FUN_00d2b8f0(this, pPosse);
        FUN_009512c0();
        void* pItemUI = FUN_009512d0((void*)"UI/PosseItem", 0x14c);
        FUN_00e25710(pItemUI, pItem);
        FUN_00d2b5f0(pItemUI);
        SetWindowImage(pItemUI, 1);
        FUN_00c0b7a0(pItemUI, 1);
    }
}

// @ 0x00d2c570
void cCreatureDisplayStrategy::OnSelectItem(void* pSelection, int32_t nMode)
{
    if (nMode == 0) {
        FUN_00c0bc00();
        FUN_00e39710(pSelection);
        FUN_00d20950(this, 1);
        return;
    }

    if (nMode == 1) {
        void* pApp = App();
        FUN_00c0b950();
        KillSetiEffects(0x9203d717);
        FUN_00d38780(GetRecorderState(), 1);
        FUN_00d49820(this, 1);
        FUN_00d20950(this, 2);
        return;
    }

    if (nMode == 2) {
        void* pApp = App();
        FUN_00c0b950();
        FUN_00d4a570();
        FUN_00f924e0(pApp);
        KillSetiEffects(0xb7233c0e);
        FUN_00d38840();
        FUN_00d38780(this, 1);
        FUN_00d20950(this, 1);
        return;
    }

    GetRecorderState();
    KillSetiEffects(0x9203d717);
    FUN_00d20950(this, 3);
}

// @ 0x00d2c9b0
void cPool::Advance()
{
    uint8_t* pNext = mpCurrent + 8;
    if (pNext == mpBlockEnd) {
        if (mpBlock != nullptr)
            operator_delete_array(mpBlock);

        cPoolBlock** ppCursor = mppBlockCursor + 1;
        mppBlockCursor = ppCursor;
        mpBlock = (uint8_t*)*ppCursor;
        mpBlockEnd = mpBlock + 0x100;
        pNext = mpBlock;
    }
    mpCurrent = pNext;
}

// @ 0x00d2c9f0
cListIterator* cNodeList::Erase(cListIterator* pOut, cListNode* pNode, cListNode** ppHead)
{
    cListNode* pNext = pNode->mpNext;
    pOut->mpNode = pNext;
    pOut->mpSlot = (void**)ppHead;

    while (pOut->mpNode == nullptr) {
        pOut->mpSlot = (void**)((uint8_t*)pOut->mpSlot + 4);
        pOut->mpNode = (cListNode*)*pOut->mpSlot;
    }

    cListNode* pCur = *ppHead;
    if (pCur == pNode) {
        *ppHead = pCur->mpNext;
    }
    else {
        cListNode* pScan = pCur->mpNext;
        while (pScan != pNode) {
            pCur = pScan;
            pScan = pScan->mpNext;
        }
        pCur->mpNext = pScan->mpNext;
    }

    if (pNode->mpValue != nullptr)
        pNode->mpValue->Release();

    if (pNode != mpSentinel) {
        if ((void*)pNode >= mpPoolLo && (void*)pNode < mpPoolHi) {
            *(void**)pNode = mpFreeHead;
            mpFreeHead = pNode;
            mnCount--;
            return pOut;
        }
        operator_delete_array(pNode);
    }

    mnCount--;
    return pOut;
}

// @ 0x00d2ca90
void cAllocPool::Allocate(void** ppValue)
{
    void* pFirst = ppValue[0];
    void* pSecond = ppValue[1];

    if ((int32_t)(mppBlockCursor - mppBlockBase) + 1 >= mnCapacity)
        RaisePoolOverflow(1, 1);

    void* pNewBlock = operator_new(0x100, "Simulator", 0, 0, gsAllocatorFile, 0xd1);
    mppBlockCursor[1] = (cPoolBlock*)pNewBlock;

    if (mpFreeEntry != nullptr) {
        void** pEntry = (void**)mpFreeEntry;
        pEntry[0] = pFirst;
        pEntry[1] = pSecond;
    }

    cPoolBlock** ppCursor = mppBlockCursor + 1;
    mppBlockCursor = ppCursor;
    mpBlock = (uint8_t*)*ppCursor;
    mpBlockEnd = mpBlock + 0x100;
    mpFreeEntry = mpBlock;
}

// @ 0x00d2cb10
void cCreatureDisplayStrategy::Activate(int32_t nMode, int32_t nFlags)
{
    ReloadTuning();
    FUN_009512c0();
    void* pPosse = FUN_009512d0((void*)"UI/Posse", 0x20c);
    FUN_00e25710(pPosse, this);

    void* pNoun = GetAvatarNoun(NounManager());
    void* pItemId = GetItemID(pNoun);
    void* pValueA = GetTuningValue(pItemId);
    void* pValueB = GetTuningValue(pItemId);
    AddPosseItem(pValueA);
    AddPosseItem(pValueB);

    AddPosseItem(pValueB);

    cSPUIGlobalUI* pGlobal = (cSPUIGlobalUI*)operator_new(0x68, "Simulator", 0, 0, gsAllocatorFile, 0xd1);
    pGlobal->Construct();
    mpGlobalUI = pGlobal;

    if (nFlags != 0)
        KillSetiEffects(0xad56080c);

    mbField04 = (uint8_t)nMode;
}

// @ 0x00d2d560
namespace SP {
void cRoundedQueue::Append(float value)
{
    long long rounded = (int)value;
    if (rounded > 0) {
        cRoundedQueuePool* pool = &mPool;
        long long* slot = pool->mpEnd;
        long long* next = slot + 1;
        if (next != pool->mpCapacity) {
            pool->mpEnd = next;
            if (slot)
                *slot = rounded;
        } else {
            pool->Allocate((void**)&rounded);
        }
    }
}
}  // namespace SP

// @ 0x00d2dd20
void cCreatureDisplayStrategy_s00d2_dd20::DrawLayer(unsigned int param_2, int tick)
{
    cAvatar_s00d2_dd20* avatar = NounManager_s00d2_dd20()->GetAvatar();
    FUN_00d2b720(avatar);

    float elapsed = (float)tick;
    if (tick < 0)
        elapsed = elapsed + kTwoPow32;
    elapsed = elapsed * kInv10000;
    FUN_00d2d7d0(&mSub190, elapsed);

    if (!mbDisplayEnabled)
        return;

    avatar->FUN_00c04590();
    VerbTray_Update(elapsed);

    if (mpProgressBar != 0) {
        cTerrainSphere* sphere = NounManager_s00d2_dd20()->GetCurrentTerrainSphere();
        float height = sphere->mHeight;
        float maxHeight = sphere->mHeightMax;
        float ratio = (height < maxHeight ? height : maxHeight) / maxHeight;
        float steps = (float)FUN_00d2e350();
        mpProgressBar->Update(ratio, (int)floor(steps));
    }

    float hintAlpha = (float)avatar->mMood.FUN_00bfc490();
    mpPosseUI->FUN_00e012d0(&g_018ac46e, hintAlpha);
    {
        cUIWindow_s00d2_dd20* win = mpPosseUI->GetBuffer(0x685a85e, 1)->FindWindowByID(0x685a85e, 1);
        if (win != 0)
            win->SetState(2, hintAlpha * kHundred < kMadMax);
    }

    {
        float mad = (float)avatar->FUN_00c0b9c0();
        mpPosseUI->FUN_00e012d0(&g_018ac464, mad * kInv100);
        cUIWindow_s00d2_dd20* win = mpPosseUI->GetBuffer(0x685a85f, 1)->FindWindowByID(0x685a85f, 1);
        if (win != 0)
            win->SetState(2, (float)avatar->FUN_00c0b9c0() < kMadMax);
    }

    {
        int value = (int)ceil((double)avatar->mMadTimer);
        cUIWindow_s00d2_dd20* win = mpPosseUI->GetBuffer(0x4d039a8, 1)->FindWindowByID(0x4d039a8, 1);
        if (win != 0) {
            char text[0x20];
            EA_Locale_SetNumberString(value, value >> 31, text, 0x20);
            win->SetText(text);
        }
    }

    FUN_00d2b950();

    cAvatar_s00d2_dd20* target = 0;
    if (mbDisplayEnabled) {
        if (avatar->FUN_00c0ee70() != 0) {
            cAvatar_s00d2_dd20* cand = avatar->FUN_00c0ee90();
            if (cand != 0) {
                if (!(cand->mFlagsB58.mFlag4 != 0
                      || cand->mFieldB5e != 0
                      || (cand->mpSpecies == avatar->mpSpecies && !avatar->FUN_00c0b770())))
                    target = cand;
            }
        }
    }

    if (mbDisplayEnabled) {
        mTimerBar.Update(tick, avatar);
        mSub128.FUN_00d2d0b0(tick);

        cHintObject* probe = GetHintProvider()->FUN_0034();
        if (probe != 0)
            probe = (cHintObject*)probe->FUN_000C(0xd0036e08);

        if (target == 0) {
            if (probe != 0 && probe != (cHintObject*)avatar
                && ((cAvatar_s00d2_dd20*)probe)->mFieldB5e == 0)
                FUN_00b69990(probe);
        } else if (target != (cAvatar_s00d2_dd20*)probe) {
            if (target->mLocomotive.FUN_0048() && FUN_00d2e490() == 1)
                FUN_00d2b6b0(target);
        } else {
            if (probe != 0 && probe != (cHintObject*)avatar
                && ((cAvatar_s00d2_dd20*)probe)->mFieldB5e == 0)
                FUN_00b69990(probe);
        }
    }

    cAvatar_s00d2_dd20* newTarget = (cAvatar_s00d2_dd20*)FUN_00d99500(avatar->FUN_00c0ee90());
    int hint = FUN_00c0c1b0(avatar);
    unsigned char newFlag = (newTarget != 0) ? newTarget->mField137 : 1;

    if (newTarget == mpAvatarTarget && hint == mPrevHint && newFlag == mPrevFlag)
        goto afterTarget;

    if (mpAvatarTarget != 0)
        FUN_00c17350(0x5418c78, 0);

    if (newTarget != 0) {
        float d = (float)newTarget->mLocomotive.FUN_0074();
        bool bLow = true;
        bool bHigh = false;
        if (kHintThresholdLo < d) {
            bLow = false;
            bHigh = !(kHintThresholdHi < d);
        }

        unsigned int id;
        if (newFlag != 0) {
            if (hint == 0)
                id = bLow ? 0xb490e2ecu : (bHigh ? 0x8297e64au : 0x59861ae4u);
            else if (hint == 1)
                id = bLow ? 0xa231da2fu : (bHigh ? 0x56191f17u : 0x7d2bf7a3u);
            else
                id = bLow ? 0x3751cceu : (bHigh ? 0x51831fe0u : 0x2f2e0a4eu);
        } else {
            if (hint == 0)
                id = bLow ? 0x4ccc8e63u : (bHigh ? 0xf09da0b3u : 0x8fbc1ed7u);
            else if (hint == 1)
                id = bLow ? 0xb69dc16au : (bHigh ? 0x36150560u : 0xae79feceu);
            else
                id = bLow ? 0x3751cceu : (bHigh ? 0x51831fe0u : 0x2f2e0a4eu);
        }

        if (id != 0)
            newTarget->FUN_00c1d400(id, 0x5418c78);

        void* msg = newTarget->FUN_00c14e70(0x5418c78);
        if (msg != 0) {
            cXformMsg xmsg;
            ((cXformMsg*)msg)->FUN_0020(&xmsg);
            xmsg.mSeq = (unsigned short)(xmsg.mSeq + 1);
            xmsg.mDist = d;
            ((cXformMsg*)msg)->FUN_0018(&xmsg);
        }
    }

    {
        cAvatar_s00d2_dd20* old = mpAvatarTarget;
        if (newTarget != old) {
            if (newTarget != 0)
                newTarget->v00();
            mpAvatarTarget = newTarget;
            if (old != 0)
                old->v04();
        }
        mPrevHint = hint;
        mPrevFlag = newFlag;
    }

afterTarget:
    if (mpAvatarTarget != 0) {
        void* msg = mpAvatarTarget->FUN_00c14e70(0x5418c78);
        if (msg != 0) {
            cXformMsg xmsg;
            ((cXformMsg*)msg)->FUN_0020(&xmsg);
            Vector3 pos = xmsg.mPos;
            Vector3 normal;
            Vector3 tangent;
            Matrix3Rows matrix;
            PlanetModel()->GetNormalAt(&normal, &pos);
            OrthogonalVector(&tangent, &normal);
            Matrix3FromFacingAndUp(&matrix, &tangent, &normal);
            xmsg.mMatrix = matrix;
            xmsg.mFlags |= 2;
            xmsg.mSeq = (unsigned short)(xmsg.mSeq + 1);
            ((cXformMsg*)msg)->FUN_0018(&xmsg);
        }
    }

    FUN_010829f0((void*)param_2);
}
