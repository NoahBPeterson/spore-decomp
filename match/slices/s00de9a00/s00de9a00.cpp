// Slice s00de9a00: the galaxy game-entry UI - the asset-browser message dispatcher, the saved-game
// vector helpers, the galaxy entry's activation/deactivation and the small property-list watchers
// around them.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------------------------
// the bound helper the saved-game walk is clamped with; it yields a reference, which is why the
// original keeps the chosen bound on the stack and re-reads it
template <class T> const T& MinRef(const T& a, const T& b)
{
    return a < b ? a : b;
}

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; call targets are masked during comparison)
// ---------------------------------------------------------------------------------------------
extern "C" void __cdecl operator_delete_array(void* pBlock);                            // 0x00f47380

extern uint32_t g_nSavedGameLimit;      // 0x016a1088 number of games to keep
extern uint32_t g_gameFlags[8];         // 0x016a1848 bit set of live game entries
extern uint8_t* g_pPanelIDs;            // 0x016a1344 the global UI panel block
extern void*    g_pAppPreferences;      // 0x015fd91c the app's preference list
extern uint8_t  g_cDefaultChar;         // 0x015d9c70 fallback byte for unknown value types
extern uint8_t  g_bGalaxyIntroA;        // 0x016a0e08
extern uint8_t  g_bGalaxyIntroB;        // 0x016a0e18
extern void*    g_pGameGlobals;         // 0x016c7aa4

extern void*    g_paintVtablePrimary[];    // 0x0147e288 PaintSystem
extern void*    g_paintVtableSecondary[];  // 0x0147e280 PaintSystem secondary base
extern void*    g_paintVtableBase[];       // 0x013eb394 PaintSystem base

// free functions of the UI / engine singletons
void*    __cdecl MessageServer();                                   // 0x0067dcc0
void*    __cdecl AppSystem();                                       // 0x0067dd00
void*    __cdecl MovieSystem();                                     // 0x0067cb10
void*    __cdecl CheatManager();                                    // 0x0067de20
void*    __stdcall StarManager(uint32_t nKey);                      // 0x00b3d2a0
void*    __cdecl ObjectTemplateDB();                                // 0x0067cb40
void*    __cdecl AuthManager();                                     // 0x00607a60
void*    __cdecl GameTimeManager();                                 // 0x00b3d380
void*    __cdecl GameInputManager();                                // 0x00b3d250
void*    __cdecl FUN_00b3d360();                                    // 0x00b3d360
void*    __stdcall FUN_00b3d410(uint32_t nA, uint32_t nB, uint32_t nC); // 0x00b3d410
void*    __cdecl FUN_00df5f40();                                    // 0x00df5f40
void*    __cdecl FUN_0067dd20();                                    // 0x0067dd20
void*    __stdcall FUN_00dd9190(uint32_t nKind);                    // 0x00dd9190
uint32_t __cdecl GetRecorderState();                                // 0x00435e90
void     __cdecl FUN_00de3e40(uint32_t nId);                        // 0x00de3e40
void     __cdecl FUN_00dde570(void* pObject);                       // 0x00dde570
bool     __cdecl IsWorldLayoutFlagSet(uint32_t nFlag);              // 0x00685520
uint8_t* __cdecl FUN_004e42a0(void** ppValue);                      // 0x004e42a0

// KillSetiEffects takes the recorder state first and the effect id second
void __cdecl KillSetiEffects(uint32_t nRecorderState, uint32_t nEffectID);  // 0x00435ed0
// the asset-browser launcher
void __cdecl Launch(uint32_t nId, uint32_t nA, uint32_t nB);                // 0x0064bc50
// property-list helpers that take the list as an explicit argument
bool __cdecl GetBoolProperty(void* pList, uint32_t nKey, uint8_t* pValue);  // 0x00407190
void __cdecl SP_SaveResource(void* pList, void* pSaveArea);                 // 0x006b1d50
void* __cdecl SP_GetSaveArea(uint32_t nId, int32_t nFlag);                  // 0x006b1f90
void* __cdecl RBTreeIncrement(void* pNode);                                 // 0x00921580

// ---------------------------------------------------------------------------------------------
// the UTFWin window interface
// ---------------------------------------------------------------------------------------------
class tIWindow {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c(uint32_t nKey);           // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
    virtual void* v44();                        // +0x44
    virtual void* v48();                        // +0x48
    virtual void* v4c();                        // +0x4c
    virtual void* v50();                        // +0x50
    virtual void* v54();                        // +0x54
    virtual void* v58();                        // +0x58
    virtual void* v5c();                        // +0x5c
    virtual void* v60();                        // +0x60
    virtual void* v64();                        // +0x64
    virtual void* v68();                        // +0x68
    virtual void* v6c();                        // +0x6c
    virtual void* v70();                        // +0x70
    virtual void* v74();                        // +0x74
    virtual void* v78();                        // +0x78
    virtual void  v7c(int32_t nA, int32_t nB);  // +0x7c visible/state pair
};

// the UI layout object embedded in the panels and the global UI block
class cSPUILayout {
public:
    uint32_t  mPad00[13];                                           // +0x000
    tIWindow* FindWindowByID(uint32_t nID, int32_t nFlag);          // 0x008105b0
    void      SetVisibility(int32_t nFlag);                         // 0x00810590
    void      Shutdown(uint32_t nFlag);                             // 0x00811ad0
};

// a ref-counted object
class tRefObj {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08 Release
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
};

// the app-side effect world the galaxy entry forwards its state to
class cIEffectsWorld {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
    virtual void* v44();                        // +0x44
    virtual void  v48(void* pEffect);           // +0x48
    virtual void  v4c();                        // +0x4c
};

// a message body: only the key getter at +0x1c is used
class cMessageBody {
public:
    virtual void*    v00();                     // +0x00
    virtual void*    v04();                     // +0x04
    virtual void*    v08();                     // +0x08
    virtual void*    v0c();                     // +0x0c
    virtual void*    v10();                     // +0x10
    virtual void*    v14();                     // +0x14
    virtual void*    v18();                     // +0x18
    virtual uint32_t v1c();                     // +0x1c the message key
};

class cUIMessage {
public:
    cMessageBody* mp00;                         // +0x00
    uint32_t      mn04;                         // +0x04
    uint32_t      mn08;                         // +0x08 message id
};

// the router the asset browser forwards every message to (declared below cUIObject)

// the UI object behind the FUN_00df5f40 singleton
class cUIObject {
public:
    virtual void*    v00();                                 // +0x00
    virtual void*    v04();                                 // +0x04
    virtual void*    v08();                                 // +0x08
    virtual void*    v0c();                                 // +0x0c
    virtual void*    v10();                                 // +0x10
    virtual void*    v14(uint32_t nKey, void* pValue);      // +0x14
    virtual void*    v18(uint32_t nA, uint32_t nB, uint32_t nC, uint32_t nD); // +0x18
    virtual void*    v1c();                                 // +0x1c
    virtual void*    v20(void* pListener, uint32_t nTag);   // +0x20
    virtual void*    v24();                                 // +0x24
    virtual void*    v28(int32_t nState);                   // +0x28
    virtual void*    v2c(void* pSender, uint32_t nTag, int32_t nData); // +0x2c
    virtual void*    v30();                                 // +0x30
    virtual void*    v34();                                 // +0x34
    virtual void*    v38(void* pOut, void* pIn);            // +0x38
    virtual void*    v3c();                                 // +0x3c
    virtual void*    v40();                                 // +0x40
    virtual void*    v44();                                 // +0x44
    virtual void*    v48();                                 // +0x48
    virtual void*    v4c(int32_t nFlag);                    // +0x4c
    virtual void*    v50();                                 // +0x50
    virtual bool     v54();                                 // +0x54
    virtual void*    v58();                                 // +0x58
    virtual void*    v5c();                                 // +0x5c
    virtual void     v60(uint32_t nA, uint32_t nB);         // +0x60

    bool FUN_00ec4320();                                    // 0x00ec4320
};

// the router the asset browser forwards every message to
class cUIMessageRouter {
public:
    virtual void*    v00();                                 // +0x00
    virtual void*    v04();                                 // +0x04
    virtual void*    v08();                                 // +0x08
    virtual void*    v0c();                                 // +0x0c
    virtual void*    v10();                                 // +0x10
    virtual void*    v14(uint32_t nKey, void* pValue);      // +0x14
    virtual void*    v18(uint32_t nA, uint32_t nB, uint32_t nC, uint32_t nD); // +0x18
    virtual void*    v1c();                                 // +0x1c
    virtual void*    v20(void* pListener, uint32_t nTag);   // +0x20
    virtual void*    v24();                                 // +0x24
    virtual void*    v28(int32_t nState);                   // +0x28
    virtual void*    v2c(void* pSender, uint32_t nTag, int32_t nData); // +0x2c
    virtual void*    v30();                                 // +0x30
    virtual void*    v34();                                 // +0x34
    virtual void*    v38(void* pOut, void* pIn);            // +0x38
    virtual void*    v3c();                                 // +0x3c
    virtual void*    v40();                                 // +0x40
    virtual void*    v44();                                 // +0x44
    virtual void*    v48();                                 // +0x48
    virtual void*    v4c(int32_t nFlag);                    // +0x4c
    virtual void*    v50();                                 // +0x50
    virtual bool     v54();                                 // +0x54
    virtual void     v58(uint32_t nArg, cUIMessage* pMsg);  // +0x58
    void FUN_00e00670(uint32_t nA, uint32_t nB);            // 0x00e00670
};

class cSaveGameUI : public cUIObject {
public:
    void GetSavedGames(void* pBegin, uint32_t nCount);      // 0x00df7f60
};

class cRecorderUI : public cUIObject {
public:
    uint32_t FUN_00df66e0();                                // 0x00df66e0
};

class cEffectHandle {
public:
    void FUN_00e3e350();                                    // 0x00e3e350
};

// the movie system, queried for its playback state
class cMovieSystem {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual bool v14();                         // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual bool v24();                         // +0x24
};

class cGameTime : public cUIObject {
public:
    void FUN_00b32110();                                    // 0x00b32110
};

class cGameInput {
public:
    uint32_t mPad00[0x110 / 4];                             // +0x000
    uint32_t mn110;                                         // +0x110
};

// the global game globals root
class cGameGlobalsRoot {
public:
    uint32_t   mPad00[7];                       // +0x00
    cUIObject* mp1c;                            // +0x1c
};

// an object holding a message handler at +8
class cMsgHandler {
public:
    uint32_t mPad00[2];                         // +0x00
};

// ---------------------------------------------------------------------------------------------
// saved-game vectors: the game info entries have a 0xbc stride
// ---------------------------------------------------------------------------------------------
class cGameInfoVector;

struct tScratchQuad {
    uint32_t mn00;                              // +0x00
    uint32_t mn04;                              // +0x04
    uint32_t mn08;                              // +0x08
    uint32_t mn0c;                              // +0x0c
};

// a scratch container with an inline buffer (0xac bytes, kept whole so the temporary
// the growth helper copies out of has the same footprint as in the original)
class cByteVector {
public:
    tScratchQuad mPad000;                       // +0x000 .. +0x00f
    tScratchQuad mPad010;                       // +0x010 .. +0x01f
    tScratchQuad mPad020;                       // +0x020 .. +0x02f
    tScratchQuad mPad030;                       // +0x030 .. +0x03f
    tScratchQuad mPad040;                       // +0x040 .. +0x04f
    tScratchQuad mPad050;                       // +0x050 .. +0x05f
    tScratchQuad mPad060;                       // +0x060 .. +0x06f
    tScratchQuad mPad070;                       // +0x070 .. +0x07f
    tScratchQuad mPad080;                       // +0x080 .. +0x08f
    tScratchQuad mPad090;                       // +0x090 .. +0x09f
    tScratchQuad mPad0a0;                       // +0x0a0 .. +0x0af
    uint32_t     mPad0b0;                       // +0x0b0
    uint32_t     mPad0b4;                       // +0x0b4
    uint32_t     mPad0b8;                       // +0x0b8

    cByteVector();                              // 0x00b26d00
    ~cByteVector();                             // 0x00b26db0
};

class cGameInfoVector {
public:
    uint8_t* mpBegin;                           // +0x00
    uint8_t* mpEnd;                             // +0x04
    uint8_t* mpCapacity;                        // +0x08

    void FUN_00de97a0(void* pBegin, void* pEnd);                            // 0x00de97a0
    void FUN_00de97f0(void* pEnd, uint32_t nCount, const cByteVector& scratch); // 0x00de97f0
    void FUN_00de5ee0(void* pBegin, void* pEnd);                            // 0x00de5ee0
    void FUN_00de9e20(uint32_t nCount);                                     // 0x00de9e20
};

// the saved-game bookkeeping object behind FUN_00dd9190
class cSavedGameEntry {
public:
    void FUN_00ddc820();                        // 0x00ddc820
    void FUN_00ddb9f0();                        // 0x00ddb9f0
};

// the star manager object that resolves a banner id
class cStarManager {
public:
    uint32_t FUN_00ba6d80();                    // 0x00ba6d80
};

// the per-entry header that starts at +0x7c of a recorded game-info entry
class cGameInfoKey {
public:
    uint32_t mn00;                              // +0x00 the star-system id
    uint32_t mPad04[10];                        // +0x04 .. +0x2b
    uint32_t mn2c;                              // +0x2c non-zero when the system has content
};

// a recorded game-info entry inside the 0xbc-strided vector
class cGameInfo {
public:
    uint32_t     mn00;                          // +0x000
    uint32_t     mPad04[0x78 / 4];              // +0x004
    cGameInfoKey mKey7c;                        // +0x07c (0x30 bytes)
    uint32_t     mPadAc[4];                     // +0x0ac
};

// ---------------------------------------------------------------------------------------------
// the asset browser the message dispatcher belongs to
// ---------------------------------------------------------------------------------------------
class cAssetBrowser;
class cPosseWatcher;

class cAssetBrowser {
public:
    uint32_t          mPad00[13];               // +0x000
    cUIMessageRouter* mp34;                     // +0x034
    uint32_t          mPad38[51];               // +0x038 .. +0x103
    int32_t           mn104;                    // +0x104
    int32_t           mn108;                    // +0x108
    uint32_t          mPad10c[13];              // +0x10c .. +0x13f
    cSPUILayout       mLayout140;               // +0x140
    void*             mp174;                    // +0x174
    uint32_t          mPad178[7];               // +0x178 .. +0x193
    cPosseWatcher*    mp194;                    // +0x194

    bool FUN_00de9a00(uint32_t nArg, cUIMessage* pMsg);         // 0x00de9a00
};

class cPosseWatcher {
public:
    void FUN_00dde570();                        // 0x00dde570
};

// the object that owns the browser four bytes before it
class cAssetBrowserHost {
public:
    uint32_t      mPad00;                       // +0x00
    cAssetBrowser mBrowser;                     // +0x04

    void FUN_00de52d0();                        // 0x00de52d0
};

// ---------------------------------------------------------------------------------------------
// the record map: a key tree at +0x38 and its node helpers
// ---------------------------------------------------------------------------------------------
class cKeyTree {
public:
    void*   mp00;                               // +0x00
    void*   mp04;                               // +0x04 end node
    void**  Find(void** ppOut, const void* pKey);   // 0x00a21dc0
};

class cRecordMap {
public:
    uint32_t mPad00[14];                        // +0x00 .. +0x37
    cKeyTree mTree38;                           // +0x38

    void FUN_00de9600(const void* pKey);                        // 0x00de9600
    void FUN_00de9dc0(const void* nKey);                        // 0x00de9dc0
    void FUN_00de6f20(uint32_t nKey, void* pValue);             // 0x00de6f20
    void FUN_00de7010();                                        // 0x00de7010
    void FUN_00de9fc0();                                        // 0x00de9fc0
};

// the visitor tree helpers
class cVisitNode {
public:
    uint32_t  mPad00[5];                        // +0x00
    tRefObj*  mp14;                             // +0x14
};

// ---------------------------------------------------------------------------------------------
// the galaxy game entry
// ---------------------------------------------------------------------------------------------
class cGalaxyGameEntryImpl {
public:
    uint32_t    mPad00[2];                      // +0x000
    cMsgHandler mHandler08;                     // +0x008 the handler registered with the message server
    uint32_t    mPad10[10];                     // +0x010 .. +0x037
    cIEffectsWorld* mp38;                       // +0x038
    cRecordMap  mRecords3c;                     // +0x03c (0x40 bytes)
    uint8_t     mPad7c[0x4d];                   // +0x07c .. +0x0c8
    uint8_t     mb0c9;                          // +0x0c9
    uint8_t     mPad0ca[0x3e];                  // +0x0ca .. +0x107
    int32_t     mn108;                          // +0x108
    int32_t     mn10c;                          // +0x10c
    uint32_t    mPad110[6];                     // +0x110 .. +0x127
    void*       mp128;                          // +0x128 the tree's root node
    void*       mp12c;                          // +0x12c the tree's first node
    uint32_t    mPad130[4];                     // +0x130 .. +0x13f
    uint8_t     mb140;                          // +0x140
    uint8_t     mPad141[0xb5];                  // +0x141 .. +0x1f5
    uint8_t     mb1f6;                          // +0x1f6
    uint8_t     mPad1f7[0x55];                  // +0x1f7 .. +0x24b
    uint8_t     mb24c;                          // +0x24c
    uint8_t     mb24d;                          // +0x24d
    uint8_t     mPad24e[2];                     // +0x24e .. +0x24f
    tRefObj*    mp250;                          // +0x250

    void OnActivate();                          // 0x00de4720
    void FUN_00de5950();                        // 0x00de5950
    void ShowGalaxy(int32_t nFlag);             // 0x00de5470
    bool FUN_00dea200();                        // 0x00dea200
    void FUN_00dea420();                        // 0x00dea420
};

// ---------------------------------------------------------------------------------------------
// functional-match constraints used by the asset browser
// ---------------------------------------------------------------------------------------------
class cConstraint {
public:
    uint32_t mPad00[9];                         // +0x00 (0x24 bytes)

    cConstraint(uint32_t nId, int32_t nKind, int32_t nValue);   // 0x00558960
    void FUN_00606880(const cConstraint* pOther);               // 0x00606880
};

class cConstraintList {
public:
    cConstraint* mpBegin;                       // +0x00
    cConstraint* mpEnd;                         // +0x04
    cConstraint* mpCapacity;                    // +0x08

    void DoInsertValue(cConstraint* pEnd, cConstraint* pValue);     // 0x004e39d0
    void DoDestroyValues(cConstraint* pBegin, cConstraint* pEnd);  // 0x004e39a0
};

class cKeyList {
public:
    void* mpBegin;                              // +0x00
    void* mpEnd;                                // +0x04
    void* mpCapacity;                           // +0x08

    void DoDestroyValues(void* pBegin, void* pEnd);             // 0x004e39a0
};

struct tResourceKey {
    uint32_t mn00;                              // +0x00
    uint32_t mn04;                              // +0x04
    uint32_t mn08;                              // +0x08
};

class cVariant {
public:
    uint32_t mPad00[4];                         // +0x00
    uint32_t mnFlags10;                         // +0x10

    void FUN_005dd750(uint32_t* pOut);          // 0x005dd750
    void Destruct(int32_t nFlag);               // 0x0093db80
};

class cPropertyList {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14(uint32_t nKey, cVariant* pValue);  // +0x14
    int32_t GetModificationCount();                       // 0x006237a0
};

// ---------------------------------------------------------------------------------------------
// property-list watchers
// ---------------------------------------------------------------------------------------------
class cProperty {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual bool  v24(uint32_t nKey, void** ppValue);       // +0x24
};

class cVariantValue {
public:
    uint8_t* mp00;                              // +0x00
    uint32_t mPad04[3];                         // +0x004
    uint8_t  mb10;                              // +0x010
    uint8_t  mPad11;                            // +0x011
    uint16_t mn12;                              // +0x012
};

// a saved-game record
class cSavedGameRecord {
public:
    uint32_t        mp00;                       // +0x000
    uint32_t        mPad04[0x2c / 4];           // +0x004
    cPropertyList*  mp30;                       // +0x030
    uint32_t        mn34;                       // +0x034
};

// the value handle FUN_004e42a0 is called on
class cValueObject {
public:
    uint8_t* FUN_004e42a0();                    // 0x004e42a0
};

class cWatcherBase {
public:
    uint8_t     mb00;                           // +0x000
    uint8_t     mPad01[3];                      // +0x001
    void*       mp04;                           // +0x004 the watched record
    uint32_t    mn08;                           // +0x008
    int32_t     mn0c;                           // +0x00c last observed modification count

    bool FUN_00dea730();                        // 0x00dea730
    void FUN_00dea7b0(cProperty* pProperty);    // 0x00dea7b0
};

// ---------------------------------------------------------------------------------------------
// the paint-system helpers
// ---------------------------------------------------------------------------------------------
// the paint-system's first base: only `this` and the dword at +4, its constructor is out of line
class cPaintBaseA {
public:
    virtual void* v00();                        // +0x000
    uint32_t      mn04;                         // +0x004

    cPaintBaseA();                              // 0x00e00630
};

// the second base: it carries the vtable slot at +0x008 and the state bytes the paint system
// clears on construction
class cPaintBaseB {
public:
    virtual void* v08();                        // +0x008
    uint8_t  mb0c;                              // +0x00c
    uint8_t  mb0d;                              // +0x00d
    uint8_t  mb0e;                              // +0x00e
    uint8_t  mb0f;                              // +0x00f
    uint8_t  mb10;                              // +0x010
    uint8_t  mb11;                              // +0x011
    uint8_t  mb12;                              // +0x012
    uint8_t  mPad13;                            // +0x013

    cPaintBaseB() {}
    void ClearState()
    {
        mb0d = 0;
        mb0e = 0;
        mb0f = 0;
        mb10 = 0;
        mb11 = 0;
        mb12 = 0;
    }
};

class cPaintSystem : public cPaintBaseA, public cPaintBaseB {
public:
    virtual void* v14();                        // the paint system's own vtable entry
    void*    mp14;                              // +0x014
    float    mf18;                              // +0x018
    float    mf1c;                              // +0x01c
    float    mf20;                              // +0x020
    uint8_t  mb24;                              // +0x024
    uint8_t  mPad25[3];                         // +0x025
    int32_t  mn28;                              // +0x028

    cPaintSystem();                             // 0x00dea500
    void FUN_00e00650(uint32_t nId, uint32_t nData);            // 0x00e00650
    void FUN_00dea560();                                        // 0x00dea560
    void FUN_00dea600(uint32_t nId, uint32_t nData);            // 0x00dea600
};

// the global panel block (the kGUI_PanelIDs table behind 0x016a1344)
class cPanelIDs {
public:
    uint8_t     mPad000[0x144];                 // +0x000
    cSPUILayout mLayout144;                     // +0x144 (0x34 bytes)
    uint32_t    mPad178[0x74 / 4];              // +0x178 .. +0x1eb
    int32_t     mn1ec;                          // +0x1ec
    uint8_t     mPad1f0[2];                     // +0x1f0 .. +0x1f1
    uint8_t     mb1f2;                          // +0x1f2
    uint8_t     mb1f3;                          // +0x1f3
    uint8_t     mb1f4;                          // +0x1f4
    uint8_t     mPad1f5[3];                     // +0x1f5
    uint32_t    mPad1f8[4];                     // +0x1f8 .. +0x207
    float       mf208;                          // +0x208
    float       mf20c;                          // +0x20c
};

// ---------------------------------------------------------------------------------------------
// @ 0x00de9a00
// ---------------------------------------------------------------------------------------------
bool cAssetBrowser::FUN_00de9a00(uint32_t nArg, cUIMessage* pMsg)
{
    if (this->mp174 != 0)
        return false;
    if (((cGameGlobalsRoot*)g_pGameGlobals)->mp1c->FUN_00ec4320() != 0)
        return false;
    if (this->mp34 != 0)
        this->mp34->v58(nArg, pMsg);
    if (pMsg->mn08 == 0x287259f6)
    {
    uint32_t nKey = pMsg->mp00->v1c();
    switch (nKey)
    {
    case 0x36c4a10:
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        ((cUIObject*)FUN_0067dd20())->v28(1);
        return false;

    case 0x36850d4:
    case 0x43b72d0:
    case 0x447060a:
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        return false;

    case 0x48102ca:
        KillSetiEffects(GetRecorderState(), 0x8cbe8393);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        if (AuthManager() != 0)
            ((cUIObject*)AuthManager())->v44();
        return false;

    case 0x4699799:
        KillSetiEffects(GetRecorderState(), 0xd094b811);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        Launch(0x55bdb30f, 0, 0);
        return false;

    case 0x469975e:
        KillSetiEffects(GetRecorderState(), 0x66be5739);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        FUN_00de3e40(0x509cf4cb);
        return false;

    case 0x595e0a8:
        ((cAssetBrowserHost*)((uint8_t*)this - 4))->FUN_00de52d0();
        return false;

    case 0x61dd69b:
    case 0x62d88e9:
        this->mn104 = 2;
        this->mn108 = 2;
        return false;

    case 0x615b966:
        KillSetiEffects(GetRecorderState(), 0x2ccf3a4d);
        this->mn104 = 5;
        this->mn108 = 5;
        return false;

    case 0x2f1cd64:
    case 0x615b616:
        if (this->mp34 != 0)
            this->mp34->FUN_00e00670(0x42, 0);
        return false;

    case 0x6709a13:
        KillSetiEffects(GetRecorderState(), 0xb7a63c50);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        this->mp194->FUN_00dde570();
        break;

    case 0x7bfb76e:
        KillSetiEffects(GetRecorderState(), 0xebadb118);
        this->mn108 = 2;
        return false;

    case 0x70d74e7:
        {
            if (!IsWorldLayoutFlagSet(2))
                return false;

            cPropertyList* pPrefs = (cPropertyList*)g_pAppPreferences;
            uint8_t bEnabled = 0;
            GetBoolProperty(pPrefs, 0x80d7de1, &bEnabled);
            if (bEnabled == 0)
            {
                tIWindow* pWindow = this->mLayout140.FindWindowByID(0x806a310, 1);
                if (pWindow != 0)
                    pWindow->v7c(1, 0);

                uint32_t nResource = 1;
                cVariant variant;
                variant.FUN_005dd750(&nResource);
                pPrefs->v14(0x80d7de1, &variant);
                if ((variant.mnFlags10 & 4) != 0)
                    variant.Destruct(0);
                SP_SaveResource(pPrefs, SP_GetSaveArea(0x11ac192, 0));
            }
            KillSetiEffects(GetRecorderState(), 0x6cd343dc);
            this->mn108 = 0xd;
            this->mn104 = 0xd;
        }
        return false;
    }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00de9dc0
// ---------------------------------------------------------------------------------------------
void cRecordMap::FUN_00de9dc0(const void* pKey)
{
    void* pFound;
    this->mTree38.Find(&pFound, pKey);
    void* pNode = pFound;
    if (pNode == (void*)&this->mTree38.mp04)
    {
        this->FUN_00de9600(pKey);
        pNode = *this->mTree38.Find(&pFound, pKey);
        if (pNode == (void*)&this->mTree38.mp04)
            return;
    }
    this->FUN_00de6f20((uint32_t)pKey, (uint8_t*)pNode + 0x1c);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00de9e20
// ---------------------------------------------------------------------------------------------
void cGameInfoVector::FUN_00de9e20(uint32_t nCount)
{
    int32_t nHave = (int32_t)(mpEnd - mpBegin) / 0xbc;
    if (nCount > nHave)
    {
        FUN_00de97f0(this->mpEnd, nCount - (int32_t)(this->mpEnd - this->mpBegin) / 0xbc,
                     cByteVector());
    }
    else
    {
        FUN_00de97a0(mpBegin + nCount * 0xbc, mpEnd);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00de9ec0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00de9ec0()
{
    if (g_nSavedGameLimit == 0)
        return;

    ((cSavedGameEntry*)FUN_00dd9190(2))->FUN_00ddc820();
    uint32_t nCount = ((cRecorderUI*)FUN_00df5f40())->FUN_00df66e0();

    cGameInfoVector games;
    games.mpBegin = 0;
    games.mpEnd = 0;
    games.mpCapacity = 0;
    games.FUN_00de9e20(nCount);

    uint8_t* pBegin = games.mpBegin;
    ((cSaveGameUI*)FUN_00df5f40())->GetSavedGames(pBegin, nCount);

    uint32_t nLoaded = (uint32_t)((int32_t)(games.mpEnd - pBegin) / 0xbc);
    uint32_t nWalk = MinRef(nLoaded, g_nSavedGameLimit);
    cGameInfoKey* pKey = &((cGameInfo*)pBegin)->mKey7c;
    for (uint32_t i = 0; i < nWalk; ++i)
    {
        if (pKey->mn2c != 0)
        {
            cStarManager* pStars = (cStarManager*)StarManager(pKey->mn00);
            ((cSavedGameEntry*)FUN_00dd9190(pStars->FUN_00ba6d80()))->FUN_00ddb9f0();
        }
        pKey = (cGameInfoKey*)((uint8_t*)pKey + 0xbc);
    }

    games.FUN_00de5ee0(pBegin, games.mpEnd);
    if (pBegin != 0 && *(int32_t*)(pBegin - 4) != 0)
        operator_delete_array(pBegin);
}

// appends one constraint to the browser's filter list (inlined at each of the three call sites)
static void AddConstraint(cConstraintList* pList, uint32_t nId, int32_t nValue)
{
    cConstraint c(nId, 0, nValue);
    if (pList->mpEnd < pList->mpCapacity)
    {
        cConstraint* pSlot = pList->mpEnd;
        pList->mpEnd = pList->mpEnd + 1;
        if (pSlot != 0)
            pSlot->FUN_00606880(&c);
    }
    else
    {
        pList->DoInsertValue(pList->mpEnd, &c);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00de9fc0
// ---------------------------------------------------------------------------------------------
void cRecordMap::FUN_00de9fc0()
{
    cConstraintList list;
    list.mpBegin = 0;
    list.mpEnd = 0;
    list.mpCapacity = 0;

    AddConstraint(&list, 0x2dd90af, 0x366a930d);
    AddConstraint(&list, 0x3cc89b1, 0x913b23be);
    AddConstraint(&list, 0x54a32960, 1);

    cKeyList keys;
    keys.mpBegin = 0;
    keys.mpEnd = 0;
    keys.mpCapacity = 0;
    ((cUIObject*)ObjectTemplateDB())->v38(&keys, &list);

    uint8_t* pKey = (uint8_t*)keys.mpBegin;
    int32_t nCount = (int32_t)((uint8_t*)keys.mpEnd - (uint8_t*)keys.mpBegin) / 0xc;
    for (int32_t i = 0; i < nCount; ++i)
    {
        tResourceKey key;
        key.mn00 = *(uint32_t*)(pKey + 0);
        key.mn04 = *(uint32_t*)(pKey + 4);
        key.mn08 = *(uint32_t*)(pKey + 8);

        void* pFound;
        void** ppSlot = this->mTree38.Find(&pFound, &key);
        if (*ppSlot == (void*)&this->mTree38.mp04)
        {
            this->FUN_00de9600(&key);
            nCount = (int32_t)((uint8_t*)keys.mpEnd - (uint8_t*)keys.mpBegin) / 0xc;
        }
        pKey += 0xc;
    }

    this->FUN_00de7010();

    if (keys.mpBegin != 0 && *(int32_t*)((uint8_t*)keys.mpBegin - 4) != 0)
        operator_delete_array(keys.mpBegin);
    list.DoDestroyValues(list.mpBegin, list.mpEnd);
    if (list.mpBegin != 0 && *(int32_t*)((uint8_t*)list.mpBegin - 4) != 0)
        operator_delete_array(list.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00dea200
// ---------------------------------------------------------------------------------------------
bool cGalaxyGameEntryImpl::FUN_00dea200()
{
    this->mb0c9 = 1;
    this->OnActivate();
    this->FUN_00de5950();
    this->ShowGalaxy(1);
    this->mb140 = 0;
    this->mb1f6 = 1;

    uint8_t* pStars = (uint8_t*)FUN_00b3d360();
    uint8_t* pRoot = pStars + 0x20;
    if ((*(uint32_t*)pRoot != (uint32_t)pRoot || *(uint32_t*)(pStars + 0x34) != 0) &&
        g_bGalaxyIntroA != 0 && g_bGalaxyIntroB != 0)
    {
        ((cEffectHandle*)FUN_00b3d410(1, 0x2ccd1d2, 0))->FUN_00e3e350();
    }

    ((cGameTime*)GameTimeManager())->FUN_00b32110();
    ((cGameInput*)GameInputManager())->mn110 = 0;
    this->mRecords3c.FUN_00de9fc0();

    if (this->mn108 == 1)
        this->mn10c = 2;

    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x4360e14);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x56bbd7f);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x44db12e);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x5bd6378);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x5dd52c7);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x6203fdc);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x4519b5f);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x625d27d);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x67c75bd6);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x634297ad);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x275a9c8c);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0xeda117de);
    ((cUIObject*)MessageServer())->v20(&this->mHandler08, 0x8085c4c);

    cIEffectsWorld* pWorld = this->mp38;
    if (this->mb24c != 0)
    {
        if (pWorld != 0)
            pWorld->v48(this->mp250);
        this->mb24c = 0;
        tRefObj* pEffect = this->mp250;
        if (pEffect != 0)
        {
            this->mp250 = 0;
            pEffect->v08();
        }
        this->mb24d = 0;
    }
    else
    {
        if (pWorld != 0)
            pWorld->v4c();
    }

    uint8_t* pEnd = (uint8_t*)&this->mp128;
    uint8_t* pCur = (uint8_t*)this->mp12c;
    for (; pCur != pEnd; pCur = (uint8_t*)RBTreeIncrement(pCur))
        ((cVisitNode*)pCur)->mp14->v38();

    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00dea420
// ---------------------------------------------------------------------------------------------
void cGalaxyGameEntryImpl::FUN_00dea420()
{
    cUIObject* pCheats = (cUIObject*)CheatManager();
    if (pCheats != 0)
        pCheats->v4c(1);

    cUIObject* pServer = (cUIObject*)MessageServer();
    if (pServer != 0)
    {
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x67c75bd6, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x634297ad, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x275a9c8c, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0xeda117de, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x8085c4c, -9999);
    }

    ((cPanelIDs*)g_pPanelIDs)->mLayout144.SetVisibility(1);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00dea500
// ---------------------------------------------------------------------------------------------
cPaintSystem::cPaintSystem()
{
    this->ClearState();
    this->mp14 = 0;
    this->mn28 = -1;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00dea560
// ---------------------------------------------------------------------------------------------
void cPaintSystem::FUN_00dea560()
{
    this->mb24 = 6;
    this->mf18 = 0.0f;

    cPanelIDs* pPanels = (cPanelIDs*)g_pPanelIDs;
    if (pPanels->mb1f3 != 0)
    {
        pPanels->mb1f3 = 0;
        ((cUIObject*)MessageServer())->v18(0x66f6b6f, 0, 0, 0);
    }

    if (this->mp14 != 0)
    {
        tIWindow* pA = ((cSPUILayout*)this->mp14)->FindWindowByID(0x6776fe0, 1);
        pA->v7c(1, 0);
        tIWindow* pB = ((cSPUILayout*)this->mp14)->FindWindowByID(0x6776fe1, 1);
        pB->v7c(1, 0);
        ((cSPUILayout*)this->mp14)->Shutdown(1);

        tRefObj* pOld = (tRefObj*)this->mp14;
        if (pOld != 0)
        {
            this->mp14 = 0;
            pOld->v08();
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00dea600
// ---------------------------------------------------------------------------------------------
void cPaintSystem::FUN_00dea600(uint32_t nId, uint32_t nData)
{
    if ((g_gameFlags[nId >> 5] >> (nId & 0x1f) & 1) != 0)
        return;

    if (nId == 0x1b)
    {
        if (((cUIObject*)AppSystem())->v54() == 0 && ((cPanelIDs*)g_pPanelIDs)->mb1f4 != 0)
        {
            this->FUN_00e00650(nId, nData);
            return;
        }
        if (((cMovieSystem*)MovieSystem())->v24() != 0)
        {
            if (((cMovieSystem*)MovieSystem())->v14() == 0)
            {
                if (((cUIObject*)AppSystem())->v54() != 0)
                {
                    this->FUN_00dea560();
                    ((cPanelIDs*)g_pPanelIDs)->mn1ec = 6;
                    ((cUIObject*)MessageServer())->v18(0x66f8f25, 0, 0, 0);
                    this->FUN_00e00650(nId, nData);
                    return;
                }
                this->mb24 = 0;
                this->mf18 = ((cPanelIDs*)g_pPanelIDs)->mf20c;
                this->mf1c = ((cPanelIDs*)g_pPanelIDs)->mf208;
                this->mf20 = 0.0f;
                ((cPanelIDs*)g_pPanelIDs)->mb1f2 = 1;
            }
        }
    }
    this->FUN_00e00650(nId, nData);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00dea730
// ---------------------------------------------------------------------------------------------
bool cWatcherBase::FUN_00dea730()
{
    cSavedGameRecord* pRecord = (cSavedGameRecord*)this->mp04;
    if (pRecord != 0)
    {
        int32_t nStamp = pRecord->mp30 != 0 ? pRecord->mp30->GetModificationCount() : 0;
        if (this->mn0c != (int32_t)(pRecord->mn34 + nStamp))
        {
            int32_t nNew = pRecord->mp30 != 0 ? pRecord->mp30->GetModificationCount() : 0;
            this->mn0c = pRecord->mn34 + nNew;

            void* pValue;
            if (((cProperty*)pRecord)->v24(this->mn08, &pValue))
            {
                uint8_t cValue = *((cValueObject*)pValue)->FUN_004e42a0();
                if (this->mb00 != cValue)
                {
                    this->mb00 = cValue;
                    return true;
                }
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00dea7b0
// ---------------------------------------------------------------------------------------------
void cWatcherBase::FUN_00dea7b0(cProperty* pProperty)
{
    cVariantValue* pValue;
    if (pProperty->v24(this->mn08, (void**)&pValue))
    {
        uint16_t nType = pValue->mn12;
        uint8_t* pByte;
        if (nType == 1 || nType == 0x10)
        {
            if ((pValue->mb10 & 0x30) != 0)
                pByte = pValue->mp00;
            else
                pByte = nType != 0 ? (uint8_t*)pValue : (uint8_t*)0;
        }
        else
        {
            pByte = &g_cDefaultChar;
        }
        this->mb00 = *pByte;
    }

    cSavedGameRecord* pRecord = (cSavedGameRecord*)this->mp04;
    this->mn0c = pRecord->mn34 + (pRecord->mp30 != 0 ? pRecord->mp30->GetModificationCount() : 0);
}
