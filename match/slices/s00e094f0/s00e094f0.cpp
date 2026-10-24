// Slice s00e094f0 -- the spyglass/scan UI mode (cursor registration, the spyglass layout with its
// two windows, the planet-grid owner object with its cell layout maths, the name/property accessors
// used by the asset-browser launch, and the grid's message handler).
//
// Subject objects:
//   * the spyglass layout singleton (0x15a4bc0) with two child windows (0x15a4bc4 / 0x15a4bc8) and
//     the "cursors registered" flag (0x15a4bbc);
//   * the grid owner object built by 0x00e0a390: refcounted paint/tracer bases at +0x04/+0x08, the
//     ref-counted element vector at +0x18..+0x20, the row table at +0x30/+0x34, a stride at +0x2c,
//     the cell metrics at +0x44..+0x58 and an EA messaging handler at +0x5c;
//   * the objects queried through slot +0x0c of the caller's object (0x00e09910 / 0x00e09b10).
//
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define PV(n) virtual void pv##n();

// --------------------------------------------------------------------------- opaque services
namespace SP {
    void* GameTimeManager();                                // 0x00b3d380
    void* App();                                            // 0x0067dd10
}
void* __cdecl FUN_0067cab0();                               // 0x0067cab0  cursor table singleton
void* __cdecl FUN_006abeb0(uint32_t size);                   // 0x006abeb0  operator new
void* __cdecl FUN_00bcc330();                                // 0x00bcc330  (callers pass this in ecx)
void  __cdecl FUN_00f47380(void* p);                         // 0x00f47380  operator delete[]
void  __cdecl FUN_00571db0(void*, void*, void*, void*, void*);  // 0x00571db0 EA::Messaging::RemoveHandler
void  __cdecl FUN_00806e40(void* window, int32_t a, int32_t b); // 0x00806e40 AutoSizeWindowForText
int32_t GonzagoHintConditions(int32_t condition);            // 0x00e07e70
struct cAssetLaunchParams;
void  __cdecl FUN_0064a990(cAssetLaunchParams* params);      // 0x0064a990
char  __cdecl FUN_00807690(void* window, int32_t refresh);    // 0x00807690

// 00e07e70 lives in the same module; 0x00e094f0 forwards to it.
extern const float g_FloatOne;                               // 0x01485720  1.0f
extern const float g_FloatTwoPow32;                          // 0x013f4fd0  4294967296.0f (uint->float bias)
extern wchar_t gEmptyString16[];                             // 0x01667bac  eastl::gEmptyString16

// --------------------------------------------------------------------------- globals
struct cSPUIWindow;
struct cSPUILayout;
struct cGrid;
extern cSPUILayout* g_pSpyglassLayout;                       // 0x015a4bc0
extern cSPUIWindow* g_pSpyglassTopWindow;                    // 0x015a4bc4
extern cSPUIWindow* g_pSpyglassTextWindow;                   // 0x015a4bc8
extern bool         g_bSpyglassCursors;                      // 0x015a4bbc
extern bool         g_bSpyglassActive;                       // 0x015a4bd5
extern uint32_t     g_SpyglassMode;                          // 0x015a4bd0
extern uint32_t     g_SpyglassTextTarget;                    // 0x015a4bac

// --------------------------------------------------------------------------- interfaces
struct cRefObject {                                          // refcounted object, release at +0x04
    PV(0)
    virtual void Release();                                  // +0x04
};

struct cRefObject2 {                                         // refcounted object, addref +0x04/release +0x08
    PV(0)
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
};

struct cResourceKey {                                        // EA::ResourceMan::Key
    uint32_t mId;                                            // +0x00
    uint32_t mType;                                          // +0x04
    uint32_t mGroup;                                         // +0x08
};

struct cSPUIWindow {
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
    virtual void v31(int32_t value, int32_t animate);         // +0x7c
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51)
    PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61)
    PV(62) PV(63) PV(64)
    virtual void v65(void* target);                          // +0x104
};

struct cSPUILayout {
    PV(0)
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
    bool Init(const cResourceKey& key, bool b, uint32_t value);   // 0x008120d0
    void SetVisibility(int32_t visible);                     // 0x00810590
    cSPUIWindow* FindWindowByID(uint32_t id, bool searchChildren); // 0x008105b0
    void Shutdown(uint32_t mode);                            // 0x00811ad0
    void* FUN_00810000();                                    // 0x00810000  ctor, returns this
};

struct CursorTable {
    uint32_t AddCursor(uint32_t id, const wchar_t* name, int32_t a, int32_t b, int32_t c); // 0x00802050
    bool FindLocal(uint32_t id);                             // 0x00801bb0
};

struct cAppObject {                                          // SP::App() result
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13)
    virtual void* v14();                                      // +0x38
};

struct MessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void v5(uint32_t id, void* a, void* b);           // +0x14
    virtual void v6(uint32_t id, void* a, void* b, void* c);  // +0x18
    PV(7) PV(8) PV(9) PV(10)
    virtual void v11(void* value, uint32_t id, int32_t code); // +0x2c
};

struct MessageServer* GetMessageServer();                    // 0x0067dcc0

struct cGameTimeManager {
    void IncPauseGate(uint32_t gate);                         // 0x00b32220
    void DecPauseGate(uint32_t gate);                         // 0x00b32250
};

struct cGameObject {                                          // the caller's object (slot +0x0c query)
    PV(0) PV(1) PV(2)
    virtual void* v3(uint32_t kind);                          // +0x0c
};

struct cSpeciesProfile;                                       // name holder (+0x504 = identity)
struct cSPCreatureBase {
    void* GetSpeciesProfile();                                // 0x00c0bbd0
};
struct cCreatureOrWhatever {                                  // second kind queried by 0x00e09910
    void* FUN_00bcc330();                                     // 0x00bcc330 (thiscall, returns pointer)
};
struct cThirdKind {                                           // queried with 0x137e8e0
    uint32_t mPad34[13];
};
struct cThirdKindBase {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual void* v38();                                      // +0x98
};
struct cNameProvider {                                        // queried with 0xe9cb8ba
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual void* v29();                                      // +0x74
};
struct WString;                                               // eastl::basic_string<wchar_t>
struct cSpeciesName {
    void GetUiName(WString* out);                             // 0x004da330
};

struct WString {                                              // eastl::basic_string<wchar_t>
    wchar_t* mBegin;                                          // +0x00
    wchar_t* mEnd;                                            // +0x04
    wchar_t* mCapacity;                                       // +0x08
    WString() : mBegin(gEmptyString16), mEnd(gEmptyString16), mCapacity(gEmptyString16 + 1) {}
    ~WString();
};

struct cStaticOwner {                                         // 12-byte function-local static in 0x00e09910
    void* mField00;                                           // +0x00
    void* mField04;                                           // +0x04
    void* mField08;                                           // +0x08
    cStaticOwner() : mField00(0), mField04(0), mField08(0) {}
};

struct cAssetLaunchParams {                                   // 0x48-byte launch descriptor
    uint32_t mId;                                             // +0x00
    void*    mApp;                                            // +0x04
    uint8_t  mPad08[0x0b];                                    // +0x08
    uint8_t  mFlag13;                                         // +0x13
    uint32_t mPad14;                                          // +0x14
    void*    mOwner0;                                         // +0x18
    void*    mOwner1;                                         // +0x1c
    void*    mOwner2;                                         // +0x20
    uint8_t  mFlag24;                                         // +0x24
    uint8_t  mPad25[0x23];                                    // +0x25
    void Construct();                                         // 0x00644b10
    void Destroy();                                           // 0x00644b60
};

struct cGridMessage {                                        // grid refresh message
    uint32_t mPad00;                                          // +0x00
    uint32_t mPad04;                                          // +0x04
    uint32_t mPad08;                                          // +0x08
    uint32_t mPad0C;                                          // +0x0c
    uint32_t mType;                                           // +0x10
    uint32_t mPad14;                                          // +0x14
    void*    mTarget;                                         // +0x18
};

struct cVector18 {                                            // eastl vector living at +0x18
    void* mBegin;                                             // +0x00
    void* mEnd;                                               // +0x04
    void* mCapacity;                                          // +0x08
    void Destroy();                                           // 0x005c7f10
};

// --------------------------------------------------------------------------- grid owner object
struct cGrid {
    void*    mField00;                                        // +0x00
    void*    mField04;                                        // +0x04
    void*    mField08;                                        // +0x08
    void*    mField0C;                                        // +0x0c
    uint32_t mField10;                                        // +0x10
    uint32_t mField14;                                        // +0x14
    int32_t* mData;                                           // +0x18
    int32_t* mDataEnd;                                        // +0x1c
    int32_t* mDataCap;                                        // +0x20
    uint32_t mField24;                                        // +0x24
    uint32_t mField28;                                        // +0x28
    int32_t  mStride;                                         // +0x2c
    int32_t* mRowBegin;                                       // +0x30
    int32_t* mRowEnd;                                         // +0x34
    uint32_t mRowCap;                                         // +0x38
    uint32_t mPad3C[2];                                       // +0x3c
    float    mField44;                                        // +0x44
    float    mField48;                                        // +0x48
    float    mField4C;                                        // +0x4c
    float    mField50;                                        // +0x50
    float    mField54;                                        // +0x54
    float    mField58;                                        // +0x58
    void*    mHandler;                                        // +0x5c
    void*    mHandlerArg0;                                    // +0x60
    void*    mHandlerArg1;                                    // +0x64
    void*    mHandlerArg2;                                    // +0x68
    void*    mHandlerArg3;                                    // +0x6c

    void* Init();                                             // 0x00e0a390
    void  Destroy();                                          // 0x00e0a400
    void  LayoutCells();                                      // 0x00e0a270
    bool  HandleMessage(uint32_t id, void* msg);              // 0x00e0a480
    int32_t CellStart(int32_t row, int32_t col);              // 0x00e09ca0
    void  FUN_00e09d10();                                     // 0x00e09d10
    void* FUN_01077ae0(int32_t element);                      // 0x01077ae0
};

struct cCell {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual void v27(float* rect);                            // +0x6c
};

// --------------------------------------------------------------------------- ref assignment
template <class T>
inline void AssignRef(T*& dst, T* src)
{
    if (src != dst) {
        T* old = dst;
        if (src != 0) {
            src->AddRef();
        }
        dst = src;
        if (old != 0) {
            old->Release();
        }
    }
}

// --------------------------------------------------------------------------- 0x00e094f0
// Forward a Gonzago hint condition test to the shared condition dispatcher.
// @ 0x00e094f0
int32_t __stdcall FUN_00e094f0(int32_t condition)
{
    return GonzagoHintConditions(condition);
}

// --------------------------------------------------------------------------- 0x00e09560
// Accept the "spyglass entered" message: only the spyglass mode message type (payload +0x0c)
// triggers the mode change.
// @ 0x00e09560
struct cSpyglassMsgFilter {
    uint32_t mPad00;
    uint32_t mPad04;
    uint32_t mPad08;
    uint32_t mType;                                           // +0x0c
};

bool __stdcall FUN_00e09560(void* unused, cSpyglassMsgFilter* msg)
{
    if (msg->mType != 0x452c168) {
        return false;
    }
    GetMessageServer()->v5(0x0620271c, 0, 0);
    return true;
}

// --------------------------------------------------------------------------- 0x00e09590
// Enter/leave the spyglass mode: the mode value 8 selects the plain notify path, everything else
// posts the mode-change message with the clamped value.
// @ 0x00e09590
bool __fastcall FUN_00e09590(void* modeValue, void* unused, uint32_t msgType, int32_t code)
{
    if (msgType == 0x044dae7f) {
        if (g_SpyglassMode == 0x01510d07) {
            GetMessageServer()->v6(0x044dae7f, 0, 0, 0);
            return true;
        }
        GetMessageServer()->v11(modeValue == (void*)8 ? modeValue : 0, 0x044dae7f, 0xffffd8f1);
        return true;
    }
    return false;
}

// --------------------------------------------------------------------------- 0x00e09910
// Resolve the "identity" object of the caller's object: species identity, the creature object,
// the third kind's embedded base (+0x34) or the fourth kind's record (+0x780); falls back to the
// shared zero object.
// @ 0x00e09910
cStaticOwner* __cdecl FUN_00e09910(cGameObject* obj)
{
    if (obj != 0) {
        void* creature = obj->v3(0xce9f6639);
        if (creature != 0) {
            void* profile = ((cSPCreatureBase*)creature)->GetSpeciesProfile();
            if (profile != 0) {
                return (cStaticOwner*)((char*)profile + 0x504);
            }
        }
        void* plain = obj->v3(0xe9cb8ba);
        if (plain != 0) {
            return (cStaticOwner*)((cCreatureOrWhatever*)plain)->FUN_00bcc330();
        }
        void* third = obj->v3(0x137e8e0);
        if (third != 0) {
            return (cStaticOwner*)((cThirdKindBase*)((char*)third + 0x34))->v38();
        }
        void* fourth = obj->v3(0xb033b403);
        if (fourth != 0) {
            return (cStaticOwner*)((char*)fourth + 0x780);
        }
    }
    static cStaticOwner s_Default;
    return &s_Default;
}

// --------------------------------------------------------------------------- 0x00e09ad0
// True when the resolved identity object carries a record.
// @ 0x00e09ad0
bool __cdecl FUN_00e09ad0(cGameObject* obj)
{
    cStaticOwner* owner = FUN_00e09910(obj);
    return owner->mField00 != 0;
}

// --------------------------------------------------------------------------- 0x00e09b10
// Resolve the display name of the caller's object.
// @ 0x00e09b10
const wchar_t* __cdecl FUN_00e09b10(cGameObject* obj)
{
    if (obj != 0) {
        void* creature = obj->v3(0xce9f6639);
        if (creature != 0) {
            void* profile = ((cSPCreatureBase*)creature)->GetSpeciesProfile();
            if (profile != 0) {
                static WString s_Name;
                ((cSpeciesName*)profile)->GetUiName(&s_Name);
                return s_Name.mBegin;
            }
        }
        void* plain = obj->v3(0xe9cb8ba);
        if (plain != 0) {
            return (const wchar_t*)((cNameProvider*)plain)->v29();
        }
        void* third = obj->v3(0x137e8e0);
        if (third != 0) {
            return *(const wchar_t**)((char*)third + 0xcc8);
        }
        void* fourth = obj->v3(0xb033b403);
        if (fourth != 0) {
            return *(const wchar_t**)((char*)fourth + 0x7e0);
        }
    }
    return 0;
}

// --------------------------------------------------------------------------- 0x00e09bf0
// Launch the asset browser on the caller's object when both its name and its record exist.
// @ 0x00e09bf0
void __cdecl FUN_00e09bf0(cGameObject* obj)
{
    const wchar_t* name = FUN_00e09b10(obj);
    cStaticOwner* owner = FUN_00e09910(obj);
    if (name != 0 && owner->mField00 != 0) {
        cAssetLaunchParams params;
        params.Construct();
        void* app = ((cAppObject*)SP::App())->v14();
        params.mOwner0 = owner->mField00;
        params.mApp = app;
        params.mId = 0x578c04fa;
        params.mOwner1 = owner->mField04;
        params.mOwner2 = owner->mField08;
        params.mFlag24 = 1;
        params.mFlag13 = 0;
        FUN_0064a990(&params);
        params.Destroy();
    }
}

// --------------------------------------------------------------------------- 0x00e09ca0
// Cell index for (row, col): a plain stride*row+col walk for the uniform grid, and the merged-row
// walk (two row-table entries per merged row) when the grid has a row table.
// @ 0x00e09ca0
int32_t cGrid::CellStart(int32_t row, int32_t col)
{
    if (mRowBegin == mRowEnd) {
        return mData[mStride * row + col];
    }
    int32_t sum = 0;
    int32_t extra = 0;
    uint32_t twice = 0;
    if (row >= 2) {
        uint32_t n = ((uint32_t)(row - 2) >> 1) + 1;
        sum = mRowBegin[row] * (int32_t)n;
        twice = n + n;
    }
    if (twice < row) {
        extra = mRowBegin[row];
    }
    int32_t index = sum;
    index += sum;
    index += extra;
    index += col;
    return mData[index];
}

// --------------------------------------------------------------------------- 0x00e0a390
// Build the grid owner: reset the vtable, the element vector, the row table, the cell metrics and
// the message handler slot.
// @ 0x00e0a390
void* cGrid::Init()
{
    mField00 = (void*)0x0147f604;
    mField04 = 0;
    mField08 = 0;
    mField0C = 0;
    mField10 = 0;
    mField14 = 0;
    mData = 0;
    mDataEnd = 0;
    mDataCap = 0;
    mStride = 1;
    mRowBegin = 0;
    mRowEnd = 0;
    mRowCap = 0;
    mField44 = 0.0f;
    mField48 = 0.0f;
    mField4C = 0.0f;
    mField50 = 0.0f;
    float one = g_FloatOne;
    mField54 = one;
    mField58 = one;
    mHandler = 0;
    mHandlerArg0 = 0;
    mHandlerArg1 = 0;
    mHandlerArg2 = 0;
    mHandlerArg3 = 0;
    return this;
}

// --------------------------------------------------------------------------- 0x00e0a400
// Tear the grid owner down: detach the message handler, free the row table, destroy the element
// vector, release the two refcounted bases and fall back to the paint-system vtable.
// @ 0x00e0a400
void cGrid::Destroy()
{
    *(void* volatile*)&mField00 = (void*)0x0147f604;
    if (mHandler != 0) {
        void* handler = mHandler;
        mHandler = 0;
        FUN_00571db0(handler, mHandlerArg0, mHandlerArg1, mHandlerArg2, mHandlerArg3);
    }
    if (mRowBegin != 0 && ((int32_t*)mRowBegin)[-1] != 0) {
        FUN_00f47380(mRowBegin);
    }
    ((cVector18*)((char*)this + 0x18))->Destroy();
    if (mField08 != 0) {
        ((cRefObject*)mField08)->Release();
    }
    if (mField04 != 0) {
        ((cRefObject*)mField04)->Release();
    }
    mField00 = (void*)0x013eb394;
}

// --------------------------------------------------------------------------- 0x00e0a480
// Message handler: a grid refresh request carrying our target handle rebuilds the property grid and
// relays the cell rectangles.
// @ 0x00e0a480
bool cGrid::HandleMessage(uint32_t id, void* msgPtr)
{
    cGridMessage* msg = (cGridMessage*)msgPtr;
    if (id == 0x00f62def && mData != mDataEnd && msg->mType == 0x068328d6
        && msg->mTarget == mField0C) {
        FUN_00e09d10();
        LayoutCells();
    }
    return true;
}

// --------------------------------------------------------------------------- 0x00e0a270
// Rebuild every cell rectangle: walk the element vector row by row, place each cell from the cell
// metrics (column width + gap, row height + gap) and push the rectangle to the cell object.
// @ 0x00e0a270
void cGrid::LayoutCells()
{
    bool merged = mRowBegin != mRowEnd;
    uint32_t row = 0;
    uint32_t col = 0;
    uint32_t off = 0;
    int32_t count = (int32_t)(mDataEnd - mData);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        float x1 = (float)col * (mField4C + mField54) + mField44;
        float y1 = (float)row * (mField50 + mField58) + mField48;
        float rect[4];
        rect[0] = x1;
        rect[1] = y1;
        rect[2] = x1 + mField54;
        rect[3] = y1 + mField58;
        ((cCell*)FUN_01077ae0(mData[i]))->v27(rect);
        ++col;
        if (col == (uint32_t)mStride) {
            col = 0;
            ++row;
        } else if (merged && col == *(int32_t*)((char*)mRowBegin + off)) {
            col = 0;
            ++row;
            off += 4;
        }
    }
    FUN_00807690(mField04, 1);
}

// --------------------------------------------------------------------------- 0x00e09600
// Create (once) the spyglass UI: register the two cursors, build the layout, hook up the two child
// windows and autosize the text window.
// @ 0x00e09600
void __cdecl FUN_00e09600()
{
    if (!g_bSpyglassCursors) {
        g_bSpyglassCursors = true;
        ((CursorTable*)FUN_0067cab0())->AddCursor(0x5ecbdffd, L"cursor-ban-mode", 1, 0, 0);
        ((CursorTable*)FUN_0067cab0())->AddCursor(0xf6879190, L"cursor_spyglass", 1, 0, 0);
    }
    if (g_pSpyglassLayout == 0) {
        void* mem = FUN_006abeb0(0x18);
        cSPUILayout* created = (mem != 0)
                                   ? (cSPUILayout*)((cSPUILayout*)mem)->FUN_00810000()
                                   : 0;
        AssignRef(g_pSpyglassLayout, created);
        if (g_pSpyglassLayout == 0) {
            return;
        }
    }
    cResourceKey key;
    key.mId = 0x7edb17fd;
    key.mType = 0x0510a95b;
    key.mGroup = 0x40464100;
    g_pSpyglassLayout->Init(key, true, 0x5f1bfc10);
    g_pSpyglassLayout->SetVisibility(0);

    cSPUIWindow* top = g_pSpyglassLayout->FindWindowByID(0x0452bd20, true);
    AssignRef(g_pSpyglassTopWindow, top);
    if (g_pSpyglassTopWindow != 0) {
        g_pSpyglassTopWindow->v65(&g_SpyglassTextTarget);
    }

    cSPUIWindow* text = g_pSpyglassLayout->FindWindowByID(0xffffffff, true);
    AssignRef(g_pSpyglassTextWindow, text);
    if (g_pSpyglassTextWindow != 0) {
        g_pSpyglassTextWindow->v31(0x10, 1);
    }

    cSPUIWindow* label = g_pSpyglassLayout->FindWindowByID(0x0452c168, true);
    if (label != 0) {
        FUN_00806e40(label, 1, 0);
    }
}

// --------------------------------------------------------------------------- 0x00e097c0
// Tear the spyglass UI down: drop both child windows, shut the layout down and drop it too.
// @ 0x00e097c0
void __cdecl FUN_00e097c0()
{
    cSPUIWindow* top = g_pSpyglassTopWindow;
    if (top != 0) {
        g_pSpyglassTopWindow = 0;
        top->Release();
    }
    cSPUIWindow* text = g_pSpyglassTextWindow;
    if (text != 0) {
        g_pSpyglassTextWindow = 0;
        text->Release();
    }
    if (g_pSpyglassLayout != 0) {
        g_pSpyglassLayout->Shutdown(1);
        if (g_pSpyglassLayout != 0) {
            cSPUILayout* layout = g_pSpyglassLayout;
            g_pSpyglassLayout = 0;
            layout->Release();
        }
    }
}

// --------------------------------------------------------------------------- 0x00e09830
// Destroy the four-base object: reset its four vtable pointers, clear the three-pointer range at
// +0x18 and release the four refcounted members in reverse declaration order.
// @ 0x00e09830
struct cFourBaseObject {
    void* mField00;                                           // +0x00
    void* mField04;                                           // +0x04
    void* mField08;                                           // +0x08
    void* mField0C;                                           // +0x0c
    uint32_t mPad10[2];                                       // +0x10
    void* mField18;                                           // +0x18
    void* mField1C;                                           // +0x1c
    void* mField20;                                           // +0x20
    void* mField24;                                           // +0x24
    void Destroy();                                           // 0x00e09830
};

void cFourBaseObject::Destroy()
{
    mField00 = (void*)0x0147f5f4;
    mField04 = (void*)0x0147f5d8;
    mField08 = (void*)0x0147f5c8;
    mField0C = (void*)0x0147f5c4;
    if (mField18 != 0) {
        mField18 = 0;
        mField1C = 0;
        mField20 = 0;
    }
    if (mField24 != 0) {
        ((cRefObject*)mField24)->Release();
    }
    if (mField20 != 0) {
        ((cRefObject*)mField20)->Release();
    }
    if (mField1C != 0) {
        ((cRefObject*)mField1C)->Release();
    }
    if (mField18 != 0) {
        ((cRefObject2*)mField18)->Release();
    }
    mField0C = (void*)0x013ef094;
    mField08 = (void*)0x013eb394;
    mField04 = (void*)0x013eb938;
}

// --------------------------------------------------------------------------- 0x00e099d0
// Enter the spyglass mode overlay: switch the local cursor, show both windows, hold the pause gate
// and post the mode message.
// @ 0x00e099d0
void __cdecl FUN_00e099d0(int8_t refreshCursor)
{
    g_bSpyglassActive = true;
    if (refreshCursor != 0) {
        ((CursorTable*)FUN_0067cab0())->FindLocal(0x5ecbdffd);
    }
    if (g_pSpyglassTopWindow != 0) {
        g_pSpyglassTopWindow->v31(1, 1);
    }
    if (g_pSpyglassTextWindow != 0) {
        g_pSpyglassTextWindow->v31(1, 1);
    }
    cGameTimeManager* timeManager = (cGameTimeManager*)SP::GameTimeManager();
    timeManager->IncPauseGate(0x04bf38a7);
    GetMessageServer()->v5(0x0691a1c3, 0, 0);
}

// --------------------------------------------------------------------------- 0x00e09a50
// Leave the spyglass mode overlay: restore the cursor, hide both windows, release the pause gate and
// post the completion message.
// @ 0x00e09a50
void __cdecl FUN_00e09a50(int8_t refreshCursor)
{
    if (refreshCursor != 0) {
        ((CursorTable*)FUN_0067cab0())->FindLocal(0x1002);
    }
    if (g_pSpyglassTopWindow != 0) {
        g_pSpyglassTopWindow->v31(1, 0);
    }
    if (g_pSpyglassTextWindow != 0) {
        g_pSpyglassTextWindow->v31(1, 0);
    }
    cGameTimeManager* timeManager = (cGameTimeManager*)SP::GameTimeManager();
    timeManager->DecPauseGate(0x04bf38a7);
    g_bSpyglassActive = false;
    GetMessageServer()->v5(0x06202731, 0, 0);
}
