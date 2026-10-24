// s00d2dd20 -- SP creature-mode display / input strategy (DrawLayer plus the small
// creature-mode helpers).  Reconstructed from the retail disassembly alone
// (work/match/scratch_s00d2dd20_cards.txt).  The dev-PDB headers under
// src/game/include/SP do NOT describe this build, so every member offset below comes
// from the observed code, not from a header.
//
//   0x00d2dd20  cCreatureDisplayStrategy::DrawLayer     thiscall, ret 8
//   0x00d2e2e0  cCreatureModeEventSink::Update          thiscall, ret 4
//   0x00d2e360  GetTerrainHeight                        cdecl, double result (st0)
//   0x00d2e380  GetTierHeight                           cdecl, double result (st0)
//   0x00d2e410  GetTierBaseHeight                       cdecl, double result (st0)
//   0x00d2e480  SetClampedValue                         cdecl
//   0x00d2e4a0  SetCreatureDisplayMode                  cdecl
//   0x00d2e580  RefreshViewScale                        cdecl
//   0x00d2e720  RecomputeZoom                           cdecl
//   0x00d2e800  GetRecomputedZoom                       cdecl, double result (st0)
//   0x00d2e830  GetTierForTerrain                       cdecl
//   0x00d2e8a0  cCreatureModeStrategy::NotifyEvent      static, 1 float
//   0x00d2e980  ResetCreatureModeState                  cdecl
//   0x00d2e9b0  cVarListSerializer::Load                thiscall, ret 4
//   0x00d2ea80  cCreatureModeInputStrategy::AsInterface thiscall, ret 4
//   0x00d2eab0  cCreatureModeInputStrategy::IsStrafeLeftDown   thiscall (ecx unused)
//   0x00d2eaf0  cCreatureModeInputStrategy::IsStrafeRightDown  thiscall (ecx unused)
//   0x00d2eb30  OnDisplayStrategyModal                  cdecl, ret 8
//   0x00d2eb70  ToggleBanningMode                       cdecl
//   0x00d2ebc0  ToggleBuildMode                         cdecl

#include <math.h>
#include <string.h>

// ---------------------------------------------------------------------------
// value types and the .rdata / .data constants (all plain addressed globals)
// ---------------------------------------------------------------------------

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Matrix3Rows { float m[9]; };

extern float kTwoPow32;        // 0x013f4fd0  4.2949673e+09f (int -> float, negative)
extern float kInv10000;        // 0x013ebca0  0.0001f
extern float kHundred;         // 0x013ec4d0  100.0f
extern float kInv100;          // 0x013eb960  0.01f
extern float kFloatMax;        // 0x0147a528  3.402823466e+38F
extern float kRealOne;         // 0x01485720  _HK_REAL_ONE
extern float kRealZero;        // 0x01485378  _HK_REAL_ZERO

extern float kTier0Height;     // 0x01582e38
extern float kTier1Height;     // 0x01582e3c
extern float kTier2Height;     // 0x01582e40
extern float kTier3Height;     // 0x01582e44
extern float kTierMaxHeight;   // 0x01582e54  clamp ceiling for mClampedValue
extern float kViewScale1;      // 0x01582fc4
extern float kViewScale2;      // 0x01582fc8
extern float kViewScale3;      // 0x01582fcc
extern float kViewScale4;      // 0x01582fd0
extern float kViewScale5;      // 0x01582fd4
extern float kHintThresholdLo; // 0x01582ff0
extern float kHintThresholdHi; // 0x01582ff4
extern float kMadMax;          // 0x01687a0c

extern unsigned int g_0145f8d4;    // 0x0145f8d4  serialized blob version
extern unsigned int g_0145f8d8;    // 0x0145f8d8  serialized blob sub-version
extern unsigned char g_015829b8;   // 0x015829b8  var-list descriptor table
extern unsigned short g_018ac46e;  // 0x018ac46e  hint-bar label id
extern unsigned short g_018ac464;  // 0x018ac464  hint-bar label id
extern char g_01654c10;            // 0x01654c10  "space" game-mode record
extern char g_01654c01;            // 0x01654c01  "creature" game-mode record

// The 0x0169e370 block: the global creature-mode display state, zeroed as one unit
// (memset 0x50) by ResetCreatureModeState / cVarListSerializer::Load.
struct CreatureModeState {
    int           mSelectedIndex;   // +0x00
    float         mZoom;            // +0x04
    float         mViewScale;       // +0x08
    unsigned char mPad0c[0x24 - 0x0c];
    int           mMode;            // +0x24  (set to 1 by the reset)
    float         mClampedValue;    // +0x28
    unsigned char mPad2c[0x38 - 0x2c];
    unsigned int  mFlags38;         // +0x38
    unsigned int  mFlags3c;         // +0x3c
    float         mPrevX;           // +0x44
    float         mPrevY;           // +0x48
    float         mPrevZ;           // +0x4c
};
extern CreatureModeState g_0169e370;   // 0x0169e370
extern float g_0169e13c;   // 0x0169e13c  last-seen avatar x
extern float g_0169e140;   // 0x0169e140  last-seen avatar y
extern float g_0169e144;   // 0x0169e144  last-seen avatar z

// ---------------------------------------------------------------------------
// the noun manager, the terrain sphere and the editor species manager
// ---------------------------------------------------------------------------

class cAvatar;

class cTerrainSphere {
public:
    unsigned char mPad00[0x10f0];
    float         mHeight;      // +0x10f0
    float         mHeightMax;   // +0x10f4
};

class cGameNounManager {
public:
    cAvatar*        GetAvatar();                     // 0x00b1fdb0
    cTerrainSphere* GetCurrentTerrainSphere();       // 0x00f67d90
};
cGameNounManager* NounManager();                     // 0x00b3d300

class cAvatarProfile {
public:
    unsigned char mPad00[0x55c];
    float         mZoomSpan;    // +0x55c
};
class cEditorSpeciesManager {
public:
    cAvatarProfile* GetAvatarProfile();              // 0x004df420
};
cEditorSpeciesManager* GetEditorSpeciesManager();    // 0x00401090

// ---------------------------------------------------------------------------
// the avatar (the player's creature); vtable slots +0x0c, +0x84 and +0xd8 are used
// ---------------------------------------------------------------------------

class cAvatarMood {
public:
    double FUN_00bfc490();                           // 0x00bfc490  st0 result
    unsigned char mPad00[4];
};

// The +0xb58 flag word is read as individual bits (a 32-bit bitfield unit).
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

// The object the avatar embeds at +0xc0 (its spatial / locomotive half).
class cLocomotive {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();
    virtual const Vector3* GetPosition();            // +0x2c
    virtual void v30();  virtual void v34();  virtual void v38();  virtual void v3c();
    virtual void v40();  virtual void v44();
    virtual bool FUN_0048();                         // +0x48
    virtual void v4c();  virtual void v50();  virtual void v54();  virtual void v58();
    virtual void v5c();  virtual void v60();  virtual void v64();  virtual void v68();
    virtual void v6c();  virtual void v70();
    virtual double FUN_0074();                       // +0x74  st0 result
};

class cSpeciesData {
public:
    unsigned char mPad00[0x61c];
    int           mMode;         // +0x61c
};

class cAvatar {
public:
    virtual void v00();  virtual void v04();  virtual void v08();               // 0x00
    virtual cAvatar* FUN_000C(unsigned int id);                                  // 0x0c
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();  // 0x10
    virtual void v20();  virtual void v24();  virtual void v28();  virtual void v2c();  // 0x20
    virtual void v30();  virtual void v34();  virtual void v38();  virtual void v3c();  // 0x30
    virtual void v40();  virtual void v44();  virtual void v48();  virtual void v4c();  // 0x40
    virtual void v50();  virtual void v54();  virtual void v58();  virtual void v5c();  // 0x50
    virtual void v60();  virtual void v64();  virtual void v68();  virtual void v6c();  // 0x60
    virtual void v70();  virtual void v74();  virtual void v78();  virtual void v7c();  // 0x70
    virtual void v80();                                                              // 0x80
    virtual void FUN_0084(void* arg);                                                // 0x84
    virtual void v88();  virtual void v8c();  virtual void v90();  virtual void v94();  // 0x88
    virtual void v98();  virtual void v9c();  virtual void vA0();  virtual void vA4();  // 0x98
    virtual void vA8();  virtual void vAC();  virtual void vB0();  virtual void vB4();  // 0xa8
    virtual void vB8();  virtual void vBC();  virtual void vC0();  virtual void vC4();  // 0xb8
    virtual void vC8();  virtual void vCC();  virtual void vD0();  virtual void vD4();  // 0xc8
    virtual int  FUN_00D8();                                                         // 0xd8

    void*  FUN_00c04590();                            // 0x00c04590
    double FUN_00c0b9c0();                            // 0x00c0b9c0  st0 result
    void*  FUN_00c0ee60(unsigned char slot, int flag);   // 0x00c0ee60
    cAvatar* FUN_00c0ee70();                          // 0x00c0ee70  GetTargetAsCreature
    cAvatar* FUN_00c0ee90();                          // 0x00c0ee90  ApplyCombatTarget
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

// ---------------------------------------------------------------------------
// input manager, UI windows, hint providers, achievements
// ---------------------------------------------------------------------------

class cGameInputManager {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();  // 0x00
    virtual void v10();  virtual void v14();
    virtual bool IsKeyDown(int key);             // +0x18
    virtual void v1c();  virtual void v20();  virtual void v24();  virtual void v28();
    virtual void v2c();  virtual void v30();
    virtual int  FUN_0034();                     // +0x34
    virtual void FUN_0038(int mode);             // +0x38
};
cGameInputManager* GameInputManager();           // 0x00b3d250
bool IsModifierKeyDown(int key);                 // 0x008d2fb0

class cUIWindow {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();  // 0x00
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();  virtual void v2c();
    virtual void v30();  virtual void v34();  virtual void v38();  virtual void v3c();
    virtual void v40();  virtual void v44();  virtual void v48();  virtual void v4c();
    virtual void v50();  virtual void v54();  virtual void v58();  virtual void v5c();
    virtual void v60();  virtual void v64();  virtual void v68();  virtual void v6c();
    virtual void v70();  virtual void v74();  virtual void v78();
    virtual void SetState(int kind, bool flag);   // +0x7c
    virtual void SetText(const void* text);       // +0x80
};

class cSPUILayout {
public:
    cUIWindow* FindWindowByID(unsigned int id, int flag);   // 0x008105b0
};

// the object the display strategy keeps at +0x58 (a UI buffer / writer)
class cPosseUI {
public:
    cSPUILayout* GetBuffer(unsigned int id, int flag);        // 0x0093b6c0
    void         FUN_00e012d0(const void* label, float value); // 0x00e012d0
};

class cSPUINewProgressBar {
public:
    void Update(float ratio, int value);         // 0x00e29da0
};

class cHintObject {
public:
    virtual void v00();  virtual void v04();  virtual void v08();
    virtual cAvatar* FUN_000C(unsigned int id);  // +0x0c
};
class cHintProvider {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();  virtual void v2c();
    virtual void v30();
    virtual cHintObject* FUN_0034();             // +0x34
};
cHintProvider* GetHintProvider();                // 0x00b3d240

class cAchievements {
public:
    bool FUN_00675e80();                         // 0x00675e80
    int  FUN_006766e0();                         // 0x006766e0
    void Award();                                // 0x00676710
};
cAchievements* GetAchievements(unsigned int id); // 0x00675250

class cModeUi {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();
    virtual void FUN_0028(int arg);              // +0x28
};
cModeUi* GetBanningModeUi();                     // 0x00d37cb0

// ---------------------------------------------------------------------------
// the creature-mode strategy, its event sink and the var-list serializer
// ---------------------------------------------------------------------------

class cSub128 {
public:
    void FUN_00d2d560(float value);              // 0x00d2d560
    void FUN_00d2d0b0(int tick);                 // 0x00d2d0b0
};

class cCreatureModeEventSink {
public:
    __declspec(noinline) void Update(float value);   // 0x00d2e2e0  (this file)

    unsigned char mPad00[0x128];
    cSub128       mSub;      // +0x128
};

class cPropertyList;

class cCreatureModeStrategy {
public:
    static cCreatureModeStrategy* Instance();                 // 0x00d38840
    static void NotifyEvent(float amount);                    // 0x00d2e8a0  (this file)
    void FUN_00d39360(unsigned int id, void* data);           // 0x00d39360

    unsigned char           mPad00[0x68];
    cCreatureModeEventSink* mpSink;       // +0x68
    unsigned char           mPad6c[0xb4 - 0x6c];
    cPropertyList*          mpPropList;   // +0xb4
};

bool GetPropertyAsVector2Array(const cPropertyList* list, unsigned int id,
                               int* pCount, Vector2** pArray);   // 0x006a0920

// The input strategy lives at +0x3c inside the enclosing strategy object; the two
// strafe helpers never touch ecx, so they compile exactly like plain members.
class cCreatureModeInputStrategy {
public:
    void* AsInterface(unsigned int iid);   // 0x00d2ea80  (this file)
    bool  IsStrafeLeftDown();              // 0x00d2eab0  (this file)
    bool  IsStrafeRightDown();             // 0x00d2eaf0  (this file)

    unsigned char mPad00[8];
    unsigned char mIface8;                 // +0x08
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
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();
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

// The serializer layout is only ever used as a stack object (0xa14 bytes); pack it
// so the frame is exactly the retail size.
#pragma pack(push, 4)
class cVarListSerializer {
public:
    cVarListSerializer(void* source, const void* desc, unsigned int id);  // 0x00692f90
    bool Serialize(unsigned int version);                                 // 0x00693e10
    bool Load(unsigned int version);                                      // 0x00d2e9b0

    unsigned char    mPad00[0x30];
    unsigned __int64 mMask30;      // +0x30
    unsigned int     mBits38[3];   // +0x38  (0x58-bit result mask)
    unsigned char    mTail[0xa14 - 0x44];
};
#pragma pack(pop)

// ---------------------------------------------------------------------------
// remaining helpers
// ---------------------------------------------------------------------------

void  SetGlobalProperty(unsigned int id, float value);   // 0x005ca880
void  VerbTray_Update(float value);                      // 0x00d4a930
void* GetCurrentGameMode();                              // 0x00b5b800
void  FUN_00c17350(unsigned int guid, int arg);          // 0x00c17350
void  ToggleBanningContent(void* arg);                   // 0x00dd17f0
void  EndBanMode(int arg);                               // 0x00dd1840
void  FUN_00e099d0(void* arg);                           // 0x00e099d0
void  FUN_00e09a50(void* arg);                           // 0x00e09a50
void  SPUIHelpers_EndModal(void* window, int a, int b);  // 0x00809c50
void  EA_Locale_SetNumberString(int value, int hi, void* out, unsigned int radix); // 0x00881ae0
void  FUN_00bc97f0(unsigned int a, int b, float c, int d); // 0x00bc97f0
void* FUN_00b3d4c0(void* p, int mode);                   // 0x00b3d4c0
void  FUN_00ba4350(void* p, int mode);                   // 0x00ba4350
void  FUN_00b69990(void* p);                             // 0x00b69990
void* FUN_00d99500(void* p);                             // 0x00d99500
int   FUN_00c0c1b0(cAvatar* p);                          // 0x00c0c1b0
double FUN_00d2e350();                                   // 0x00d2e350
int   FUN_00d2e490();                                    // 0x00d2e490

double GetTerrainHeight();                               // 0x00d2e360  (this file)
__declspec(noinline) double GetTierHeight(int tier);     // 0x00d2e380  (this file)
void   RecomputeZoom();                                  // 0x00d2e720  (this file)

class cCreatureTimerBar {
public:
    void Update(int tick, cAvatar* avatar);      // 0x00d2bd00
};

// ---------------------------------------------------------------------------
// the display strategy itself -- member offsets observed in DrawLayer
// ---------------------------------------------------------------------------

class cCreatureDisplayStrategy {
public:
    void DrawLayer(unsigned int param_2, int tick);   // 0x00d2dd20  (this file)

    void FUN_00d2b720(cAvatar* avatar);               // 0x00d2b720
    void FUN_00d2b950();                              // 0x00d2b950
    void FUN_00d2b6b0(cAvatar* target);               // 0x00d2b6b0
    void FUN_00d2d7d0(void* sub, float value);        // 0x00d2d7d0
    void FUN_010829f0(void* param);                   // 0x010829f0

    unsigned char  mPad00[0x4c];
    cAvatar*       mpAvatarTarget;    // +0x4c
    int            mPrevHint;         // +0x50
    unsigned char  mPrevFlag;         // +0x54
    unsigned char  mbDisplayEnabled;  // +0x55
    unsigned char  mPad56[0x58 - 0x56];
    cPosseUI*      mpPosseUI;         // +0x58
    unsigned char  mPad5c[0xa8 - 0x5c];
    cCreatureTimerBar mTimerBar;      // +0xa8
    unsigned char  mPadB0[0x124 - 0xb0];
    cSPUINewProgressBar* mpProgressBar;   // +0x124
    cSub128        mSub128;           // +0x128
    unsigned char  mPad12c[0x190 - 0x12c];
    unsigned char  mSub190;           // +0x190
};

// ---------------------------------------------------------------------------
// 0x00d2dd20  SP::cCreatureDisplayStrategy::DrawLayer
// ---------------------------------------------------------------------------
// @ 0x00d2dd20
void cCreatureDisplayStrategy::DrawLayer(unsigned int param_2, int tick)
{
    cAvatar* avatar = NounManager()->GetAvatar();
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
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        float height = sphere->mHeight;
        float maxHeight = sphere->mHeightMax;
        float ratio = (height < maxHeight ? height : maxHeight) / maxHeight;
        float steps = (float)FUN_00d2e350();
        mpProgressBar->Update(ratio, (int)floor(steps));
    }

    float hintAlpha = (float)avatar->mMood.FUN_00bfc490();
    mpPosseUI->FUN_00e012d0(&g_018ac46e, hintAlpha);
    {
        cUIWindow* win = mpPosseUI->GetBuffer(0x685a85e, 1)->FindWindowByID(0x685a85e, 1);
        if (win != 0)
            win->SetState(2, hintAlpha * kHundred < kMadMax);
    }

    {
        float mad = (float)avatar->FUN_00c0b9c0();
        mpPosseUI->FUN_00e012d0(&g_018ac464, mad * kInv100);
        cUIWindow* win = mpPosseUI->GetBuffer(0x685a85f, 1)->FindWindowByID(0x685a85f, 1);
        if (win != 0)
            win->SetState(2, (float)avatar->FUN_00c0b9c0() < kMadMax);
    }

    {
        int value = (int)ceil((double)avatar->mMadTimer);
        cUIWindow* win = mpPosseUI->GetBuffer(0x4d039a8, 1)->FindWindowByID(0x4d039a8, 1);
        if (win != 0) {
            char text[0x20];
            EA_Locale_SetNumberString(value, value >> 31, text, 0x20);
            win->SetText(text);
        }
    }

    FUN_00d2b950();

    cAvatar* target = 0;
    if (mbDisplayEnabled) {
        if (avatar->FUN_00c0ee70() != 0) {
            cAvatar* cand = avatar->FUN_00c0ee90();
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
                && ((cAvatar*)probe)->mFieldB5e == 0)
                FUN_00b69990(probe);
        } else if (target != (cAvatar*)probe) {
            if (target->mLocomotive.FUN_0048() && FUN_00d2e490() == 1)
                FUN_00d2b6b0(target);
        } else {
            if (probe != 0 && probe != (cHintObject*)avatar
                && ((cAvatar*)probe)->mFieldB5e == 0)
                FUN_00b69990(probe);
        }
    }

    cAvatar* newTarget = (cAvatar*)FUN_00d99500(avatar->FUN_00c0ee90());
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
        cAvatar* old = mpAvatarTarget;
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

// ---------------------------------------------------------------------------
// 0x00d2e2e0  cCreatureModeEventSink::Update
// ---------------------------------------------------------------------------
// @ 0x00d2e2e0
void cCreatureModeEventSink::Update(float value)
{
    mSub.FUN_00d2d560(value);
}

// ---------------------------------------------------------------------------
// 0x00d2e360  GetTerrainHeight
// ---------------------------------------------------------------------------
// @ 0x00d2e360
double GetTerrainHeight()
{
    return NounManager()->GetCurrentTerrainSphere()->mHeight;
}

// ---------------------------------------------------------------------------
// 0x00d2e380  GetTierHeight
// ---------------------------------------------------------------------------
// @ 0x00d2e380
__declspec(noinline) double GetTierHeight(int tier)
{
    float v = 0.0f;
    if (tier == -1)
        tier = NounManager()->GetAvatar()->FUN_00D8();
    switch (tier) {
    case 0: v = kTier0Height; break;
    case 1: v = kTier1Height; break;
    case 2: v = kTier2Height; break;
    case 3: v = kTier3Height; break;
    }
    return v;
}

// ---------------------------------------------------------------------------
// 0x00d2e410  GetTierBaseHeight
// ---------------------------------------------------------------------------
// @ 0x00d2e410
double GetTierBaseHeight(int tier)
{
    float base = NounManager()->GetCurrentTerrainSphere()->mHeight;
    switch (tier) {
    case 1:
        base = base - kTier0Height;
        break;
    case 2:
        base = base - (kTier1Height + kTier0Height);
        break;
    case 3:
        base = base - ((kTier2Height + kTier1Height) + kTier0Height);
        break;
    }
    return base;
}

// ---------------------------------------------------------------------------
// 0x00d2e480  SetClampedValue
// ---------------------------------------------------------------------------
// @ 0x00d2e480
void SetClampedValue(float value)
{
    g_0169e370.mClampedValue = value;
}

// ---------------------------------------------------------------------------
// 0x00d2e4a0  SetCreatureDisplayMode
// ---------------------------------------------------------------------------
// @ 0x00d2e4a0
void SetCreatureDisplayMode(int mode, char apply)
{
    int prev = g_0169e370.mMode;
    g_0169e370.mMode = mode;
    if (prev != mode) {
        cAvatar* avatar = NounManager()->GetAvatar();
        FUN_00bc97f0(0x100000, 0, kFloatMax, 0);
        avatar->FUN_0084(avatar->FUN_00c0ee60(avatar->mSlotB5c, 0));
        cAvatar* target = avatar->FUN_00c0ee90();
        if (target != 0) {
            FUN_00b3d4c0(target->mCombatDataB28, mode);
            FUN_00ba4350(target->mCombatDataB28, mode);
        }
        if (GetCurrentGameMode() == &g_01654c01)
            GetBanningModeUi()->FUN_0028(0);
    }
    if (apply) {
        if (mode == 0)
            SetGlobalProperty(0x843467a7, 1.0f);
        else
            SetGlobalProperty(0x16ba4108, 1.0f);
    }
}

// ---------------------------------------------------------------------------
// 0x00d2e580  RefreshViewScale
// ---------------------------------------------------------------------------
// @ 0x00d2e580
void RefreshViewScale()
{
    cAvatar* avatar = NounManager()->GetAvatar();
    switch (avatar->mpSpecies->mMode) {
    case 1: g_0169e370.mViewScale = kViewScale1; break;
    case 2: g_0169e370.mViewScale = kViewScale2; break;
    case 3: g_0169e370.mViewScale = kViewScale3; break;
    case 4: g_0169e370.mViewScale = kViewScale4; break;
    case 5: g_0169e370.mViewScale = kViewScale5; break;
    default: g_0169e370.mViewScale = 0.0f; break;
    }

    if (g_0169e370.mPrevX != g_0169e13c || g_0169e370.mPrevY != g_0169e140
        || g_0169e370.mPrevZ != g_0169e144) {
        if (!GetAchievements(0x4913ee1)->FUN_00675e80()
            && GetCurrentGameMode() != &g_01654c10) {
            const Vector3* pos = avatar->mLocomotive.GetPosition();
            double dx = (double)g_0169e370.mPrevX - (double)pos->x;
            double dy = (double)g_0169e370.mPrevY - (double)pos->y;
            double dz = (double)g_0169e370.mPrevZ - (double)pos->z;
            float dist = (float)sqrt(dz * dz + (dy * dy + dx * dx));
            int radius = GetAchievements(0x4913ee1)->FUN_006766e0();
            float fr = (float)radius;
            if (radius < 0)
                fr = fr + kTwoPow32;
            if (fr <= dist)
                GetAchievements(0x4913ee1)->Award();
        }
    }
    g_0169e370.mPrevX = g_0169e13c;
    g_0169e370.mPrevY = g_0169e140;
    g_0169e370.mPrevZ = g_0169e144;
}

// ---------------------------------------------------------------------------
// 0x00d2e720  RecomputeZoom
// ---------------------------------------------------------------------------
// @ 0x00d2e720
void RecomputeZoom()
{
    g_0169e370.mZoom = kRealOne;

    cAvatarProfile* profile = GetEditorSpeciesManager()->GetAvatarProfile();
    if (profile == 0)
        return;

    NounManager()->GetAvatar();
    float span = profile->mZoomSpan;
    int count = 0;
    Vector2* array = 0;
    if (!GetPropertyAsVector2Array(cCreatureModeStrategy::Instance()->mpPropList,
                                   0xb561b9eb, &count, &array))
        return;
    if (count == 0)
        return;

    int index = (count <= g_0169e370.mSelectedIndex) ? count : g_0169e370.mSelectedIndex;
    if (span < array[index].x)
        g_0169e370.mZoom = array[index].x / span;
    else if (array[index].y < span)
        g_0169e370.mZoom = array[index].y / span;
}

// ---------------------------------------------------------------------------
// 0x00d2e800  GetRecomputedZoom
// ---------------------------------------------------------------------------
// @ 0x00d2e800
double GetRecomputedZoom(cAvatar* avatar)
{
    if (avatar != 0 && ((unsigned char)(avatar->mFlagsB58.mFlag9) & 1))
        RecomputeZoom();
    return g_0169e370.mZoom;
}

// ---------------------------------------------------------------------------
// 0x00d2e830  GetTierForTerrain
// ---------------------------------------------------------------------------
// @ 0x00d2e830
int GetTierForTerrain()
{
    float height = NounManager()->GetCurrentTerrainSphere()->mHeight;
    float acc = 0.0f;
    int i = 0;
    do {
        acc = (float)GetTierHeight(i) + acc;
        if (acc > height)
            return i;
        ++i;
    } while (i < 4);
    return 4;
}

// ---------------------------------------------------------------------------
// 0x00d2e8a0  SP::cCreatureModeStrategy::NotifyEvent
// ---------------------------------------------------------------------------
// @ 0x00d2e8a0
void cCreatureModeStrategy::NotifyEvent(float amount)
{
    if (amount != kRealZero) {
        float v = g_0169e370.mClampedValue + amount;
        float hi = kTierMaxHeight;
        float* pf = &v;
        if (hi <= v)
            pf = &kTierMaxHeight;
        g_0169e370.mClampedValue = *pf;

        NounManager()->GetCurrentTerrainSphere()->mHeight += amount;

        if (GetCurrentGameMode() != &g_01654c10) {
            cCreatureModeStrategy* inst = Instance();
            if (inst != 0) {
                inst->mpSink->Update(amount);
                struct EventCtx {
                    cAvatar* avatar;    // +0x00
                    int      pad04;     // +0x04
                    int      zero;      // +0x08
                    float    amount;    // +0x0c
                    int      pad10;     // +0x10
                    int      pad14;     // +0x14
                } ctx;
                ctx.avatar = NounManager()->GetAvatar();
                ctx.zero = 0;
                ctx.amount = amount;
                inst->FUN_00d39360(0x45ab96e, &ctx);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00d2e980  ResetCreatureModeState
// ---------------------------------------------------------------------------
// @ 0x00d2e980
void ResetCreatureModeState()
{
    memset(&g_0169e370, 0, 0x50);
    g_0169e370.mFlags38 |= 0x40000000;
    g_0169e370.mFlags3c |= 0x20;
    g_0169e370.mMode = 1;
}

// ---------------------------------------------------------------------------
// 0x00d2e9b0  cVarListSerializer::Load
// ---------------------------------------------------------------------------
// @ 0x00d2e9b0
bool cVarListSerializer::Load(unsigned int version)
{
    mBits38[0] = 0;
    mBits38[1] = 0;
    mBits38[2] = 0;
    memset(&g_0169e370, 0, 0x50);
    g_0169e370.mFlags38 |= 0x40000000;
    g_0169e370.mFlags3c |= 0x20;
    g_0169e370.mMode = 1;

    cVarListSerializer s(this, &g_015829b8, 0x1a80d26);
    bool ok = s.Serialize(version);

    if (g_0145f8d4 < 0x25 || (g_0145f8d4 == 0x25 && g_0145f8d8 < 1)) {
        for (int i = 0; i < 0x40; ++i) {
            if ((mMask30 & ((unsigned __int64)1 << i)) != 0) {
                if (i < 0x58)
                    mBits38[i >> 5] |= 1u << (i & 0x1f);
            }
        }
    }
    return ok;
}

// ---------------------------------------------------------------------------
// 0x00d2ea80  SP::cCreatureModeInputStrategy::AsInterface
// ---------------------------------------------------------------------------
// @ 0x00d2ea80
void* cCreatureModeInputStrategy::AsInterface(unsigned int iid)
{
    if (iid != 0x2f009dd0u) {
        if (iid == 0x305a9f63u)
            return (cCreatureModeStrategy*)((char*)this - 0x3c);
    } else {
        if ((cCreatureModeStrategy*)((char*)this - 0x3c) != 0)
            return &mIface8;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00d2eab0  cCreatureModeInputStrategy::IsStrafeLeftDown
// ---------------------------------------------------------------------------
// @ 0x00d2eab0
bool cCreatureModeInputStrategy::IsStrafeLeftDown()
{
    cGameInputManager* mgr = GameInputManager();
    if (mgr->IsKeyDown(5))
        return true;
    if (!IsModifierKeyDown(0x3ea))
        return false;
    return mgr->IsKeyDown(3);
}

// ---------------------------------------------------------------------------
// 0x00d2eaf0  cCreatureModeInputStrategy::IsStrafeRightDown
// ---------------------------------------------------------------------------
// @ 0x00d2eaf0
bool cCreatureModeInputStrategy::IsStrafeRightDown()
{
    cGameInputManager* mgr = GameInputManager();
    if (mgr->IsKeyDown(6))
        return true;
    if (!IsModifierKeyDown(0x3ea))
        return false;
    return mgr->IsKeyDown(4);
}

// ---------------------------------------------------------------------------
// 0x00d2eb30  OnDisplayStrategyModal
// ---------------------------------------------------------------------------
// @ 0x00d2eb30
bool __stdcall OnDisplayStrategyModal(void* window, unsigned int* msg)
{
    if (msg[2] == 0x287259f6u && msg[3] == 0x01788526u) {
        SPUIHelpers_EndModal(window, 0, 1);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00d2eb70  ToggleBanningMode
// ---------------------------------------------------------------------------
// @ 0x00d2eb70
void ToggleBanningMode()
{
    switch (GameInputManager()->FUN_0034()) {
    case 2:
        EndBanMode(1);
        GameInputManager()->FUN_0038(0);
        break;
    default:
        ToggleBanningContent((void*)1);
        GameInputManager()->FUN_0038(2);
        break;
    }
}

// ---------------------------------------------------------------------------
// 0x00d2ebc0  ToggleBuildMode
// ---------------------------------------------------------------------------
// @ 0x00d2ebc0
void ToggleBuildMode()
{
    cGameInputManager* mgr = GameInputManager();
    if (mgr->FUN_0034() != 3) {
        FUN_00e099d0((void*)0);
        GameInputManager()->FUN_0038(3);
    } else {
        FUN_00e09a50((void*)0);
        GameInputManager()->FUN_0038(0);
    }
}