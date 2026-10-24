// s00d16f40 -- SP::cGameEditInputStrategy: the gameplay-marker editing helpers.
// Reconstructed from the retail disassembly alone (work/match/scratch_s00d16f40_cards.txt).
// The dev-PDB headers under src/game/include/SP do not describe this build, so every member
// offset below comes from the observed code, not from a header.
//
//   0x00d16f40  cGameEditInputStrategy::FUN_00d16f40              thiscall, ret 4
//   0x00d17250  SP::cGameEditInputStrategy::Activate               thiscall, ret 0
//   0x00d172d0  SP::cGameEditInputStrategy::CommitChangesToGameplayMarker  thiscall, ret 8
//   0x00d17550  SP::cGameEditInputStrategy::AddGameplayMarkerValue  thiscall, ret 0x14
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"
#include <math.h>
#include <stdlib.h>
#pragma pack(push, 4)

// ---------------------------------------------------------------- value types
struct Vector3    { float x, y, z; };
struct Quaternion { float x, y, z, w; };

// ---------------------------------------------------------------- UTFWin UI object
// One vptr.  The slots this slice calls are named; every slot is declared so that a named
// slot sits at its retail vtable offset (the slot at byte 4*i is the (i+1)-th declaration).
// A defaulted trailing parameter lets the callers that pass one extra argument share a slot
// with the callers that pass none, without changing the argument-free call sites' code.
class cUiObject {
public:
    virtual void v00();                                       // 0x00
    virtual void v04();                                       // 0x04  Release
    virtual void v08();                                       // 0x08
    virtual cUiObject* v0c(uint32_t id);                      // 0x0c  GetWindowByID
    virtual cUiObject* v10();                                 // 0x10  sub-object getter
    virtual void v14();                                       // 0x14
    virtual void v18(uint32_t text);                          // 0x18
    virtual uint32_t v1c();                                   // 0x1c
    virtual void v20(uint32_t text);                          // 0x20
    virtual void v24(cUiObject* target, uint32_t id);         // 0x24  register message handler
    virtual void v28();                                       // 0x28
    virtual void* v2c();                                      // 0x2c
    virtual void* v30();                                      // 0x30
    virtual void v34();                                       // 0x34
    virtual void v38();                                       // 0x38
    virtual void v3c(void* transform);                        // 0x3c
    virtual void* v40();                                      // 0x40
    virtual void v44(int a, int b);                           // 0x44
    virtual void v48();                                       // 0x48
    virtual void v4c();                                       // 0x4c
    virtual void v50(uint32_t color);                         // 0x50
    virtual const wchar_t* v54();                             // 0x54
    virtual cUiObject* v58();                                 // 0x58
    virtual void v5c();                                       // 0x5c
    virtual void v60(const float* rect);                      // 0x60
    virtual void v64(float a, float b);                       // 0x64
    virtual void v68();                                       // 0x68
    virtual void v6c();                                       // 0x6c
    virtual void v70();                                       // 0x70
    virtual void v74();                                       // 0x74
    virtual void v78();                                       // 0x78
    virtual void v7c(int a, int b);                           // 0x7c
    virtual void v80(const wchar_t* text);                    // 0x80
    virtual void v84();                                       // 0x84
    virtual void v88();                                       // 0x88
    virtual void v8c();                                       // 0x8c
    virtual void v90();                                       // 0x90
    virtual void v94(int a, int b);                           // 0x94
    virtual void v98();                                       // 0x98
    virtual void v9c();                                       // 0x9c
    virtual void va0();                                       // 0xa0
    virtual void va4();                                       // 0xa4
    virtual void va8();                                       // 0xa8
    virtual void vac();                                       // 0xac
    virtual void vb0();                                       // 0xb0
    virtual void vb4();                                       // 0xb4
    virtual cUiObject* vb8(uint32_t id);                      // 0xb8
    virtual void vbc();                                       // 0xbc
    virtual void vc0(int count);                              // 0xc0
    virtual void vc4();                                       // 0xc4
    virtual void vc8();                                       // 0xc8
    virtual void vcc(void* out);                              // 0xcc
    virtual void vd0(void* out);                              // 0xd0
    virtual void vd4();                                       // 0xd4
    virtual void vd8(void* item);                             // 0xd8
    virtual void vdc();                                       // 0xdc
    virtual void ve0();                                       // 0xe0
    virtual void ve4();                                       // 0xe4
};

// Second flavour of the same layout: the objects reachable through cUiObject::v10 and through
// a marker's handler call these slots with an extra argument (MSVC passes defaulted parameters
// at the call site, so the declaration has to spell out the argument).
class cUiObjectB {
public:
    virtual void v00();                                       // 0x00
    virtual void v04();                                       // 0x04  Release
    virtual void v08();                                       // 0x08
    virtual cUiObjectB* v0c(uint32_t id);                     // 0x0c
    virtual cUiObjectB* v10();                                // 0x10
    virtual void v14();                                       // 0x14
    virtual void v18(uint32_t text);                          // 0x18
    virtual uint32_t v1c();                                   // 0x1c
    virtual void v20(uint32_t index, uint32_t color);         // 0x20
    virtual void v24(cUiObjectB* target, uint32_t id);        // 0x24
    virtual void v28();                                       // 0x28
    virtual void* v2c(void* arg);                             // 0x2c
    virtual void* v30(float value);                           // 0x30
    virtual void v34();                                       // 0x34
    virtual void v38();                                       // 0x38
    virtual void v3c(void* transform);                        // 0x3c
    virtual void* v40(int arg);                               // 0x40
    virtual void v44(int a, int b);                           // 0x44
    virtual void v48();                                       // 0x48
    virtual void v4c();                                       // 0x4c
    virtual void v50(uint32_t color);                         // 0x50
    virtual const wchar_t* v54(uint32_t color);               // 0x54
    virtual cUiObjectB* v58();                                // 0x58
    virtual void v5c();                                       // 0x5c
    virtual void v60(const float* rect);                      // 0x60
    virtual void v64(float a, float b);                       // 0x64
    virtual void v68();                                       // 0x68
    virtual void v6c();                                       // 0x6c
    virtual void v70();                                       // 0x70
    virtual void v74();                                       // 0x74
    virtual void v78();                                       // 0x78
    virtual void v7c(int a, int b);                           // 0x7c
    virtual void v80(const wchar_t* text);                    // 0x80
    virtual void v84();                                       // 0x84
    virtual void v88();                                       // 0x88
    virtual void v8c();                                       // 0x8c
    virtual void v90();                                       // 0x90
    virtual void v94(int a, int b);                           // 0x94
    virtual void v98();                                       // 0x98
    virtual void v9c();                                       // 0x9c
    virtual void va0();                                       // 0xa0
    virtual void va4();                                       // 0xa4
    virtual void va8();                                       // 0xa8
    virtual void vac();                                       // 0xac
    virtual void vb0();                                       // 0xb0
    virtual void vb4();                                       // 0xb4
    virtual cUiObjectB* vb8(uint32_t id);                     // 0xb8
    virtual void vbc();                                       // 0xbc
    virtual void vc0(int count);                              // 0xc0
    virtual void vc4();                                       // 0xc4
    virtual void vc8();                                       // 0xc8
    virtual void vcc(void* out);                              // 0xcc
    virtual void vd0(void* out);                              // 0xd0
    virtual void vd4();                                       // 0xd4
    virtual void vd8(void* item);                             // 0xd8
    virtual void vdc();                                       // 0xdc
    virtual void ve0();                                       // 0xe0
    virtual void ve4();                                       // 0xe4
};

// ---------------------------------------------------------------- SP::PropertyManager
class cPropertyManager {
public:
    virtual void p00();                                       // 0x00
    virtual void p04();                                       // 0x04
    virtual void p08();                                       // 0x08
    virtual void p0c();                                       // 0x0c
    virtual void p10();                                       // 0x10
    virtual void p14();                                       // 0x14
    virtual void p18();                                       // 0x18
    virtual void p1c();                                       // 0x1c
    virtual void p20();                                       // 0x20
    virtual void p24();                                       // 0x24
    virtual void p28();                                       // 0x28
    virtual void p2c();                                       // 0x2c
    virtual char p30(uint32_t hash, cUiObject** out);         // 0x30
};

// ---------------------------------------------------------------- eastl::basic_string<wchar_t>
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;
    void sprintf(const wchar_t* fmt, ...);                    // 0x0041e050
};

// ---------------------------------------------------------------- ref-counted string holder
// The two IWinText handles the retail keeps for a scene element are AutoRefCount objects whose
// assignment AddRef/Releases through the callee below.
struct AutoRefCount {
    cUiObject* mpObject;
    void Assign(cUiObject* value);                            // 0x00b5f950  operator=
};

// ---------------------------------------------------------------- gameplay marker object
// The object cUiObject::vb8 hands back for a marker id: a sub-object at +0x34 and the
// gameplay handler pointer at +0x1a4.
class cMarkerInfo {
public:
    char      mPad00[0x34];
    cUiObject mSub34;                                         // +0x34
    char      mPad38[0x1a4 - 0x38];
    cUiObject* mpField1a4;                                    // +0x1a4
};

// ---------------------------------------------------------------- engine entry points
namespace SP {
    class cPlanetModel {
    public:
        uint32_t GetPlanetKey();                              // 0x00b7e380
        void*    FUN_00b7f1f0(const void* ctx, void* a2, void* a3);  // 0x00b7f1f0
    };
    cPlanetModel* PlanetModel();                              // 0x00b3d350
    cUiObject*    MessageServer();                            // 0x0067dcc0
    cPropertyManager* PropertyManager();                      // 0x0067de30
    void QuaternionFromDirections(Quaternion* out, const Vector3* a,
                                  const Vector3* b);          // 0x00698180
}

class cSPUILayout {
public:
    cUiObject* FindWindowByID(uint32_t id, int includeChildren);   // 0x008105b0
};

namespace EA { namespace UTFWinControls {
// The factory hands back raw storage; the ctor runs on it in place and returns `this`.
class WinTextEdit {
public:
    char      mPad00[0x20c];
    cUiObjectB mText;                                         // +0x20c
    WinTextEdit* Construct();                                 // 0x0098c110  WinTextEdit::WinTextEdit
};
} }

// ---------------------------------------------------------------- SP::cGameEditModeStrategy
// The scenario the edited gameplay markers belong to.  Its marker description fields sit at
// +0x108..+0x114 and the per-marker value table at +0x11c (indexed by the marker's own id).
class cGameEditModeStrategy {
public:
    char     mPad00[0x108];
    uint32_t mMarkerType;                                     // +0x108
    uint32_t mMarkerClassId;                                  // +0x10c
    uint32_t mField110;                                       // +0x110
    uint32_t mMarkerValue;                                    // +0x114
    char     mPad118[4];
    int      mMarkerValues[32];                               // +0x11c
    static void LoadScenario(cGameEditModeStrategy* self, int a, int b);   // 0x00b931c0
};

// ---------------------------------------------------------------- SP::cGameEditInputStrategy
class cGameEditInputStrategy {
public:
    char        mPad00[0x3c];
    cUiObject   mHandler;                     // +0x3c   message handler target
    char        mPad40[0x54 - 0x40];
    cUiObject*  mpSelectedObjectManipulator;  // +0x54
    char        mPad58[0xa4 - 0x58];
    cUiObject*  mpUIA4;                       // +0xa4
    cUiObject*  mpScrollBarA8;                // +0xa8
    char        mPadAc[0xc4 - 0xac];
    Vector3     mFacing;                      // +0xc4   the marker's current facing
    Vector3     mFrameD0;                     // +0xd0   transform input for FUN_007dcb00
    char        mPadDc[0xe0 - 0xdc];
    cSPUILayout mLayout;                      // +0xe0
    char        mPadE4[0x104 - 0xe4];
    cUiObject*  mpServer;                     // +0x104  handler registration installed on the server
    cUiObject*  mpHandlerTarget;              // +0x108
    void*       mpHandlerTable;               // +0x10c  the id table at 0x01479b60
    int         mHandlerCount;                // +0x110
    uint32_t    mField114;                    // +0x114

    void FUN_00d16f40(Vector3* target);                       // 0x00d16f40
    void Activate();                                          // 0x00d17250
    void CommitChangesToGameplayMarker(cGameEditModeStrategy* scenario, char apply);  // 0x00d172d0
    void AddGameplayMarkerValue(int type, uint32_t color, int* value,
                                float* posX, float* posY);     // 0x00d17550
    uint32_t GetGameplayMarkerTypeFromUI();                   // 0x00d15fb0
    uint32_t FUN_00d16820();                                  // 0x00d16820
    void SetPlanet(uint32_t key);                             // 0x00d16b90
    void FUN_00d15780(int type, void* a3, void* a4);          // 0x00d15780
};

// ---------------------------------------------------------------- externals
extern uint32_t g_01479b60[];                 // 0x01479b60  handler id table (0x23 entries)
extern wchar_t  g_01667bac[];                 // 0x01667bac  eastl::gEmptyString16 (+2: terminator)
extern void*    g_01440aec;                   // 0x01440aec  element container base
extern void     operator_delete__(void* p);   // 0x00f47380

extern uint32_t FNV1_String16(const wchar_t* text, uint32_t seed, int mode);  // 0x00932f30
extern uint32_t FUN_00d15b30(uint32_t markerType);            // 0x00d15b30 GetGameplayMarkerClassId
extern char     FUN_00d16620(uint32_t markerType, int* out);  // 0x00d16620 GetGameplayMarkerTypes
extern void     FUN_00d15350(cGameEditModeStrategy* scenario, uint32_t index, int value,
                             const wchar_t* text);            // 0x00d15350
extern void*    FUN_007dcb00(void* out, const void* frame, const Quaternion* q);  // 0x007dcb00
extern void*    FUN_009512c0();                               // 0x009512c0
extern void*    FUN_009512d0(uint32_t id, uint32_t size, const char* name, void* factory);  // 0x009512d0

// ---------------------------------------------------------------- constants
// The axis the rebuilt marker quaternion turns around, stored at 0x0169dc7c/80/84.
const float kMarkerAxisX  = 1.0f;
const float kMarkerAxisY  = 0.0f;
const float kMarkerAxisZ  = 0.0f;
const float kDotThreshold = 0.99f;            // 0x013ef480

// ---------------------------------------------------------------- SP::cGameEditInputStrategy
// @ 0x00D16F40  cGameEditInputStrategy::FUN_00d16f40
void cGameEditInputStrategy::FUN_00d16f40(Vector3* target)
{
    if (mpSelectedObjectManipulator->v58() == 0)
        return;

    Vector3* ringPos = (Vector3*)mpSelectedObjectManipulator->v58()->v2c();
    Vector3 delta;
    delta.x = target->x - ringPos->x;
    delta.y = target->y - ringPos->y;
    delta.z = target->z - ringPos->z;
    float lenInv = 1.0f / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    Vector3 dir;
    dir.x = delta.x * lenInv;
    dir.y = delta.y * lenInv;
    dir.z = delta.z * lenInv;
    if (mFacing.x * dir.x + mFacing.y * dir.y + mFacing.z * dir.z < kDotThreshold) {
        Quaternion fromDir;
        SP::QuaternionFromDirections(&fromDir, &mFacing, &dir);
        float angle = (float)acos(fromDir.w);
        angle = angle + angle;
        Vector3* ringDir = (Vector3*)mpSelectedObjectManipulator->v58()->v2c();
        float turn = ringDir->x * fromDir.x + ringDir->y * fromDir.y + ringDir->z * fromDir.z;
        float half = angle * (turn > 0.0f ? 0.5f : -0.5f);
        float sn = sinf(half);
        float cs = cosf(half);
        Quaternion orient;
        orient.x = sn * kMarkerAxisX;
        orient.y = sn * kMarkerAxisY;
        orient.z = sn * kMarkerAxisZ;
        orient.w = cs;

        cUiObject* marker = mpSelectedObjectManipulator->v58();
        float frame[4];
        marker->v3c(FUN_007dcb00(frame, &mFrameD0, &orient));

        cUiObject* info = marker->vb8(0x36be278);
        if (info == 0)
            return;
        cMarkerInfo* markerInfo = (cMarkerInfo*)info;
        cUiObject* handler = markerInfo->mpField1a4;
        if (handler == 0)
            return;
        cUiObjectB* sub = (cUiObjectB*)handler->v0c(0x1186577);
        if (sub == 0)
            return;
        void* a2 = markerInfo->mSub34.v30();
        void* a3 = sub->v2c(a2);
        SP::cPlanetModel* pm = SP::PlanetModel();
        float ctx[4];
        sub->v3c(pm->FUN_00b7f1f0(ctx, a3, a2));
    }
}

// @ 0x00D17250  SP::cGameEditInputStrategy::Activate
void cGameEditInputStrategy::Activate()
{
    mpSelectedObjectManipulator = 0;
    SP::cPlanetModel* pm = SP::PlanetModel();
    SetPlanet(pm->GetPlanetKey());

    cUiObject* handlerTarget = &mHandler;
    cUiObject* server = SP::MessageServer();
    mpServer = server;
    mpHandlerTarget = handlerTarget;
    mpHandlerTable = g_01479b60;
    mHandlerCount = 0x23;
    mField114 = 0;
    if (server != 0 && handlerTarget != 0) {
        for (uint32_t i = 0; i < 0x23; i++)
            server->v24(handlerTarget, g_01479b60[i]);
    }
}

// @ 0x00D172D0  SP::cGameEditInputStrategy::CommitChangesToGameplayMarker
void cGameEditInputStrategy::CommitChangesToGameplayMarker(cGameEditModeStrategy* scenario, char apply)
{
    AutoRefCount selectedText;
    AutoRefCount valueText;
    selectedText.mpObject = 0;
    valueText.mpObject = 0;

    if (scenario != 0) {
        cPropertyManager* pm = SP::PropertyManager();
        if (selectedText.mpObject != 0) {
            selectedText.mpObject = 0;
            selectedText.mpObject->v04();
        }
        uint32_t editorHash = FNV1_String16(L"LevelEditor", 0x811c9dc5, 1);
        if (pm->p30(editorHash, &selectedText.mpObject)) {
            scenario->mMarkerType    = GetGameplayMarkerTypeFromUI();
            scenario->mMarkerClassId = FUN_00d15b30(scenario->mMarkerType);
            scenario->mField110      = FUN_00d16820();

            cUiObject* win = mLayout.FindWindowByID(0xabc0fffa, 1);
            if (win != 0) {
                cUiObject* text = win->v0c(0xcf428691);
                if (text != 0) {
                    text->v00();
                    valueText.mpObject = text;
                    scenario->mMarkerValue = (uint32_t)wcstoul(text->v54(), 0, 10);
                }
            }

            int types[32];
            if (FUN_00d16620(scenario->mMarkerType, types)) {
                void* it = 0;
                void* itEnd = 0;
                mpScrollBarA8->vcc(&it);
                mpScrollBarA8->vd0(&itEnd);
                while (it != itEnd) {
                    // the scrollbar hands back the element address itself; the container base
                    // 0x01440aec is added to it
                    cUiObject* elem = *(cUiObject**)((char*)g_01440aec + (int)it);
                    uint32_t v = elem->v1c();
                    if ((v & 0xfff0) != 0xfff0 && (v & 0xabc00000) == 0xabc00000) {
                        uint32_t index = v & 0x543fffff;
                        valueText.Assign(elem->v0c(0xcf428691));
                        selectedText.Assign(elem->v0c(0x2f5528d9));
                        if (valueText.mpObject != 0) {
                            FUN_00d15350(scenario, index, types[index], valueText.mpObject->v54());
                        } else if (selectedText.mpObject != 0) {
                            scenario->mMarkerValues[index] = (int)selectedText.mpObject->v40();
                        }
                    }
                    it = *(void**)it;
                }
            }
        }
    }

    if (apply != 0 && scenario != 0) {
        cGameEditModeStrategy::LoadScenario(scenario, -1, -1);
        mpUIA4->v7c(1, 0);
        mpScrollBarA8->ve4();
    }
    if (valueText.mpObject != 0)
        valueText.mpObject->v04();
    if (selectedText.mpObject != 0)
        selectedText.mpObject->v04();
}

// @ 0x00D17550  SP::cGameEditInputStrategy::AddGameplayMarkerValue
void cGameEditInputStrategy::AddGameplayMarkerValue(int type, uint32_t color, int* value,
                                                    float* posX, float* posY)
{
    if (type == 1) {
        FUN_00d15780(type, posX, posY);

        cUiObject* win = mLayout.FindWindowByID((uint32_t)type, 1);
        if (win == 0)
            return;
        cUiObject* text = win->v0c(0x2f5528d9);
        if (text == 0)
            return;
        text->v00();
        text->v20(0x13f0270);                      // L"false"
        text->v20(0x13f023c);                      // L"true"
        text->v44(*value == 1, 0);
        text->v04();
        return;
    }

    EA::UTFWinControls::WinTextEdit* edit =
        (EA::UTFWinControls::WinTextEdit*)FUN_009512d0(0x658, 8, "UI/WinTextEdit", FUN_009512c0());
    cUiObjectB* text = 0;
    if (edit != 0) {
        if (edit->Construct() != 0) {
            text = &edit->mText;
            if (text != 0)
                text->v00();
        }
    }

    float rect[4];
    rect[0] = 0.0f;
    rect[1] = 0.0f;
    rect[2] = 60.0f;                               // 0x013ebc4c
    rect[3] = 20.0f;                               // 0x013eecd8
    text->v10()->v60(rect);
    text->v20(0, 0xff000000);
    text->v20(1, 0xffffffff);
    text->v20(2, 0xff777777);
    text->v20(3, 0xffffffff);
    text->v20(4, 0xffffffff);
    text->v20(5, 0xff43a2ff);
    text->v20(6, 0xff000000);
    text->v20(7, 0xff000000);
    text->v18(0x15a4361);

    WString label;
    label.mpBegin = g_01667bac;
    label.mpEnd = g_01667bac;
    label.mpCapacity = g_01667bac + 1;
    if (type == 9 || type == 10)
        label.sprintf(L"%d", *value);
    else if (type == 13)
        label.sprintf(L"%f", (double)*(float*)value);
    else
        label.sprintf(L"%d", *value);

    text->v10()->v80(label.mpBegin);
    text->v30(0.25f);                              // 0x013eb8a0
    text->v94(0, 0);
    text->v44(0x54, 1);
    text->v40(0);
    text->vc0(10);
    text->v10()->v64(*posX, *posY);
    text->v10()->v54(color);
    text->v10()->v90();
    text->v10()->v50(color);
    *posX += 80.0f;                                // 0x014763c4
    mpScrollBarA8->vd8(text->v10());
    if (label.mpCapacity - label.mpBegin > 1 && label.mpBegin != 0)
        operator_delete__(label.mpBegin);
    text->v04();
}

#pragma pack(pop)