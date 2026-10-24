// Slice s00d1f650 -- creature ability / camera helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- globals -----------------------------------------------------------------
extern char g_gameModeTribe;     // 0x01654c01
extern char g_gameModeTribe2;    // 0x01654c02
extern const float g_kOne;       // 0x01485720
extern const float g_kZero;      // 0x01485378
extern const float g_kTen;       // 0x01473c70
extern const float g_k1500;      // 0x0147a2fc

// ---- objects the ability tests walk ------------------------------------------
// the game-mode state object returned by 0x00d51660 (its flag word at +0x6c)
struct ModeState {
    char     pad00[0x6c];
    unsigned mBits6C;                          // 0x6c
};

// the script state object returned by 0x00d2e340 (its int at +0x08)
struct ScriptState {
    char pad00[8];
    int  mValue8;                              // 0x08
};

// the animation handle FUN_00bc97f0 returns; only its dword at +0xc is written
struct cAnimHandle {
    char     pad00[0xc];
    unsigned mFieldC;                          // +0x0c
};

// the animation state the creatures carry at model+0x08
struct CreatureAnim {
    void*        PlayIdleAnimation(int a, int b);                    // 0x00bc96a0
    cAnimHandle* FUN_00bc97f0(unsigned f, int a, float t, int b);    // 0x00bc97f0
};

// the inner object the model carries at +0x600
struct CreatureInner {
    char  pad000[0x1a8];
    void* mpField1a8;                          // 0x1a8
};

// the animation/model object the creatures carry at +0xb4c
struct CreatureModel {
    char           pad000[8];
    CreatureAnim   mAnim;                      // 0x08 (the animation state)
    char           pad009[0x1c8 - 0x09];
    unsigned       mFlags1c8;                  // 0x1c8
    unsigned       mFlags1cc;                  // 0x1cc
    unsigned       mTypeId1d8;                 // 0x1d8 (0xb46e8803 / 0x5218bb3 magic ids)
    char           pad1dc[0x600 - 0x1dc];
    CreatureInner* mpInner600;                 // 0x600
};

// the object 0x00d9f530 returns; only its byte at +0x51 is read
struct cAbilityItem {
    char          pad00[0x51];
    unsigned char mByte51;                     // 0x51
};

// the object FUN_00c0ee60 returns
struct cAbilityOwner {
    int GetFileCount();                        // 0x008e7f80
};

// the eastl-style pointer vector the terrain cursor fills from its local buffer
struct SpatialVec {
    void** mpBegin;                            // +0x00
    void** mpEnd;                              // +0x04
    void** mpCap;                              // +0x08
};

// the ability/action record the switch dispatches on (vftable slot 0xb4 result)
struct AbilityInfo {
    char     pad00[8];
    unsigned mType;                            // 0x08 (the 0xd..0x56 dispatch id)
    unsigned mFieldC;                          // 0x0c
    char     pad10[0xac - 0x10];
    float    mFloatAC;                         // 0xac
    char     padb0[0x104 - 0xb0];
    float    mFloat104;                        // 0x104
};

// one 16-byte ability-slot record the creatures carry at +0xc28
struct AbilitySlotRecord {
    char  pad00[4];
    float mFloat4;                             // +0x04
};

// the creature base view the ability is tested against
struct AbilityCreature {
    void**         mpVftable;                  // 0x000
    char           pad04[0x110 - 0x04];
    unsigned       mFlags110;                  // 0x110
    char           pad114[0x137 - 0x114];
    unsigned char  mByte137;                   // 0x137
    char           pad138[0xb4c - 0x138];
    CreatureModel* mpModelBC;                  // 0xb4c
    unsigned       mFlagsB58;                  // 0xb58
    char           padb5c[0xb5e - 0xb5c];
    unsigned char  mByteB5E;                   // 0xb5e (non-zero => ability not usable)
    char           padb5f[0xc28 - 0xb5f];
    AbilitySlotRecord* mpAbilitySlots;         // 0xc28 (the ability-slot records)
    char           padc2c[0xe58 - 0xc2c];
    float          mRangeE58;                  // 0xe58
    void*          GetTargetAsCreature();      // 0x00c0ee70
    void*          FUN_00c0ee60();             // 0x00c0ee60
    unsigned char  FUN_00c0e0c0(int id);       // 0x00c0e0c0
    unsigned char  FUN_00c0c0e0();             // 0x00c0c0e0
    int            FUN_00c22dc0();             // 0x00c22dc0
};

// the noun-manager / community / tribe views the ability tests read tools from
struct cGameNounManager {
    void* GetPlayerTribe();                    // 0x00bfc5f0
};
struct cCommunity {
    void* GetLeader();                         // 0x00c00650
};
struct cTribe {
    int   GetToolOfType(int type);             // 0x00c8f6e0
};

typedef unsigned     (__thiscall *CreatureTypeVfn)(void*);         // vftable slot 0x20
typedef AbilityInfo* (__thiscall *ResolveAbilityVfn)(void*, int);  // vftable slot 0xb4
typedef void         (__thiscall *TerrainCursorGetObjectsVfn)(void*, SpatialVec*);  // 0x00b30d70 result vftable slot 0x5c
typedef void*        (__thiscall *SpatialCastVfn)(void*, unsigned);                 // cSpatialObject vftable slot 0xb8
typedef int          (__thiscall *GetFieldVfn)(void*);                              // vftable slot 0xb0

// the ability table the caller indexes with its ability slot
extern AbilityInfo* g_abilityTable[];        // 0x0169de64

// ---- external callees --------------------------------------------------------
ModeState*   FUN_00d51660();                 // 0x00d51660
ScriptState* FUN_00d2e340();                 // 0x00d2e340
void*  FUN_00d9f530(void* a);                // 0x00d9f530 cdecl
float  FUN_00d1e7f0(void* a, void* b);       // 0x00d1e7f0 cdecl
void   FUN_00ad92d0(void* vec);              // 0x00ad92d0 eastl::vector<>::~vector
void*  FUN_00d1e830(int a);                  // 0x00d1e830 cdecl
void*  FUN_00d1e610();                       // 0x00d1e610 cdecl
int    FUN_00d1e5c0(void* a, void* b);       // 0x00d1e5c0 cdecl
void*  GetCurrentGameMode();                 // 0x00b5b800
void*  NounManager();                        // 0x00b3d300
void*  GetGameTerrainCursor();               // 0x00b30d70
unsigned char AbilityIsBeingTaughtToBaby(int a); // 0x00d1e6c0 cdecl
unsigned char FUN_00d1f400(void* p);         // 0x00d1f400 cdecl
int    FUN_00d1e530(void* a, void* b, void* c, void* d); // 0x00d1e530 cdecl
unsigned char FUN_00d1e8d0(void* a, void* b); // 0x00d1e8d0 cdecl
void*  CanSocial(void* a, void* b);          // 0x00d1e720 cdecl
void   RemoveHandler(void* a, int b, void* c, void* d, void* e); // 0x00571db0 cdecl
void*  FUN_0067cab0v(int a);                 // 0x0067cab0 cdecl
void   GetFileCount2();
void   FUN_00b5b800_2();

struct InputState {
    void Reset();                              // 0x00697980
    void OnKeyDown(int a, int b);              // 0x00697a50
    void OnKeyUp(int a, int b);                // 0x00697a80
    void OnMouseUp(int a, float b, float c, int d); // 0x00697af0
    void OnMouseWheel(int a, float b, float c, int d); // 0x00697b40
    void GetSpatialObjects(int* v);            // 0x00b30d70? no
};
struct TerrainCursor {
    void GetSpatialObjects(int* v);            // 0x00b30d70 vtable 0x5c
};
void FUN_008d2f30(int a, int b);               // 0x008d2f30 cdecl
void CanvasVisibilitySetter(int* v);           // 0x008013d0
void CursorLayoutIsThing(int* v);              // 0x00801950
void CursorLayoutSetEnabled(int* v);           // 0x00801980
void* FUN_0067cab0(int a);                     // 0x0067cab0 cdecl

struct CanvasObj { void SetVisibility(); };    // 0x008013d0 thiscall
struct CursorLayout { void IsThing(); void SetEnabled(); }; // 0x00801950/80 thiscall

struct Cam {
    unsigned char Init(int a);
    void Deactivate();
    void SetCameraUI(char on);
    unsigned char OnKeyDown(int a, int b);
    unsigned char OnKeyUp(int a, int b);
    unsigned char OnMouseUp(int a, float b, float c, int d);
    unsigned char OnMouseWheel(int a, float b, float c, int d);
};

// @ 0x00d203d0
unsigned char Cam::Init(int a)
{
    (void)a;
    ((InputState*)((char*)this + 0x2bc))->Reset();
    return 1;
}

// @ 0x00d203e0
void Cam::Deactivate()
{
    if (*(unsigned char*)((char*)this + 0x304) != 0) {
        int p0 = *(int*)((char*)this + 0x29c);
        if (p0 != 0) {
            int p1 = *(int*)((char*)this + 0x2a0);
            int p2 = *(int*)((char*)this + 0x2a4);
            int p3 = *(int*)((char*)this + 0x2a8);
            int p4 = *(int*)((char*)this + 0x2ac);
            *(int*)((char*)this + 0x29c) = 0;
            RemoveHandler((void*)p0, p1, (void*)p2, (void*)p3, (void*)p4);
        }
        *(unsigned char*)((char*)this + 0x304) = 0;
    }
}

// @ 0x00d20430
void Cam::SetCameraUI(char on)
{
    if (on != 0) {
        FUN_008d2f30((int)((char*)this + 0x30c), (int)((char*)this + 0x310));
        ((CanvasObj*)FUN_0067cab0(0))->SetVisibility();
        ((CursorLayout*)FUN_0067cab0(0x67f5c34))->IsThing();
        ((CursorLayout*)FUN_0067cab0(1))->SetEnabled();
        *(unsigned char*)((char*)this + 0x314) = 1;
    } else {
        ((CanvasObj*)FUN_0067cab0(1))->SetVisibility();
        ((CursorLayout*)FUN_0067cab0(0))->SetEnabled();
        *(unsigned char*)((char*)this + 0x314) = 0;
    }
}

// @ 0x00d204c0
unsigned char Cam::OnKeyDown(int a, int b)
{
    ((InputState*)((char*)this + 0x2bc))->OnKeyDown(a, b);
    return 0;
}

// @ 0x00d204e0
unsigned char Cam::OnKeyUp(int a, int b)
{
    ((InputState*)((char*)this + 0x2bc))->OnKeyUp(a, b);
    return 0;
}

// @ 0x00d20500
unsigned char Cam::OnMouseUp(int a, float b, float c, int d)
{
    ((InputState*)((char*)this + 0x2bc))->OnMouseUp(a, b, c, d);
    return 0;
}

// @ 0x00d20530
unsigned char Cam::OnMouseWheel(int a, float b, float c, int d)
{
    ((InputState*)((char*)this + 0x2bc))->OnMouseWheel(a, b, c, d);
    float f = 1.0f - (float)a * *(float*)((char*)this + 0x200);
    if (*(int*)((char*)this + 0x1ec) == 2) {
        float v = f * *(float*)((char*)this + 0x188);
        float lo = *(float*)((char*)this + 0x210);
        v = (v < lo) ? lo : v;
        v = (v > 1500.0f) ? 1500.0f : v;
        *(float*)((char*)this + 0x188) = v;
    } else {
        *(float*)((char*)this + 0x17c) = f * *(float*)((char*)this + 0x17c);
    }
    return 0;
}

// @ 0x00d1fa20
unsigned char F_d1fa20(int* p)
{
    if (p[3] == 4)
        return FUN_00d1f400(p);
    if (GetCurrentGameMode() == (void*)&g_gameModeTribe2) {
        cTribe* tribe = (cTribe*)((cGameNounManager*)NounManager())->GetPlayerTribe();
        switch (p[2]) {
        case 5:  return tribe->GetToolOfType(4) != 0;
        case 6:  return tribe->GetToolOfType(5) != 0;
        case 7:  return tribe->GetToolOfType(6) != 0;
        case 0x2b: return tribe->GetToolOfType(3) != 0;
        case 0x3a: return tribe->GetToolOfType(1) != 0;
        case 0x3b: return tribe->GetToolOfType(2) != 0;
        default: return 0;
        }
    }
    return 1;
}

// @ 0x00d201f0
// SP::cTribeGameBehaviorFish::Score -- true when the tribe owns the tool this behavior wants.
unsigned char F_d201f0(AbilityInfo* ability)
{
    if (GetCurrentGameMode() != (void*)&g_gameModeTribe2)
        return 1;
    if (ability->mFieldC == 4)
        return 1;

    cTribe* tribe = (cTribe*)((cGameNounManager*)NounManager())->GetPlayerTribe();
    int tool;
    switch (ability->mType - 5) {
    case 0:  if (tribe->GetToolOfType(4) == 0) return 0; tool = 4; break;
    case 1:  if (tribe->GetToolOfType(5) == 0) return 0; tool = 5; break;
    case 2:  if (tribe->GetToolOfType(6) == 0) return 0; tool = 6; break;
    case 38: if (tribe->GetToolOfType(1) == 0) return 0; tool = 1; break;
    case 53: if (tribe->GetToolOfType(2) == 0) return 0; tool = 2; break;
    case 54: if (tribe->GetToolOfType(3) == 0) return 0; tool = 3; break;
    default: return 0;
    }

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** tvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)tvt[0x5c / 4])(terrain, &vec);

    int           count = (int)(vec.mpEnd - vec.mpBegin);
    unsigned char found = 0;
    for (int i = 0; i < count; i++) {
        void* so = vec.mpBegin[i];
        if (so == 0)
            continue;
        void** svt = *(void***)so;
        void*  obj = ((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
        if (obj == 0)
            continue;
        if (((AbilityCreature*)obj)->FUN_00c22dc0() == tool) {
            found = 1;
            break;
        }
    }
    FUN_00ad92d0(&vec);
    return found;
}

// ---- big ability-scoring functions (partial) ---------------------------------
// @ 0x00d1f650
// SP::CanUseAbility -- which ability this creature may use on its current target.
unsigned int F_d1f650(AbilityCreature* self, int abilityId)
{
    if (self->mpModelBC->mAnim.PlayIdleAnimation(0, 0x20000) != 0)
        return 1;

    if (((FUN_00d51660()->mBits6C >> 4) & 1) != 0 && ((self->mFlagsB58 >> 9) & 1) != 0)
        return AbilityIsBeingTaughtToBaby(abilityId) == 0;

    if (self->mByteB5E != 0)
        return 1;

    void** vt = self->mpVftable;
    if (((CreatureTypeVfn)vt[0x20 / 4])(self) == 0x18eb45e
        && (self->mpModelBC->mFlags1c8 & 0x1000) != 0)
        return 1;

    AbilityInfo* info = ((ResolveAbilityVfn)vt[0xb4 / 4])(self, abilityId);

    float range = info->mFloat104;
    if (range > 0.0f && range > self->mRangeE58)
        return 1;

    void* target = self->GetTargetAsCreature();
    void* other = self->FUN_00c0ee60();

    switch (info->mType) {
    case 0x11:
        if (self->mByte137 != 0)
            return 0;
        return 9;

    case 0x12:
        if (self->mByte137 == 1)
            return 1;
        if (FUN_00d2e340()->mValue8 == 0)
            return 1;
        if (self->FUN_00c0e0c0(0x5485a4c) != 0)
            return 1;
        if (self->FUN_00c0e0c0(0x77300ff) == 0)
            return 0;
        return 1;

    case 0x1e: case 0x1f: case 0x20: case 0x21:
    case 0x3d: case 0x3e: case 0x41: case 0x42: case 0x48: case 0x4a:
        {
            unsigned r = FUN_00d1e530(info, self, target, other);
            if (r != 0)
                return r;
        }
        // falls through to the shared tail of the plain "use" cases
    case 0xd: case 0x27: case 0x50: case 0x52:
        if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
            return 8;
        return 0;

    case 0x22: case 0x23: case 0x24: case 0x25:
    case 0x40: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
    case 0x54: case 0x55: case 0x56:
        {
            float r = info->mFloat104;
            if (r > 0.0f && r > self->mRangeE58)
                return 1;
            unsigned s = (unsigned)CanSocial(self, target);
            if (s != 0)
                return s;
        }
        return 0;

    case 0x31: case 0x32: case 0x33:
        if (GetCurrentGameMode() != (void*)&g_gameModeTribe)
            return 1;
        if (FUN_00d1f400(info) == 0)
            return 10;
        if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
            return 8;
        return 0;

    case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
        if (GetCurrentGameMode() != (void*)&g_gameModeTribe2)
            return 1;
        if (FUN_00d1f400(info) == 0)
            return 10;
        {
            AbilityCreature* leader = (AbilityCreature*)
                ((cCommunity*)((cGameNounManager*)NounManager())->GetPlayerTribe())->GetLeader();
            if (leader == 0 || leader->mByteB5E != 0
                || (leader->mpModelBC->mFlags1cc & 0x10000) != 0)
                return 0xb;
            if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
                return 0xf;
        }
        return 0;

    case 0x49:
        if (target == 0) {
            if (other != 0)
                return 7;
        } else if (((AbilityCreature*)target)->FUN_00c0c0e0() != 0) {
            return 7;
        }
        {
            unsigned r = FUN_00d1e530(info, self, target, other);
            if (r != 0)
                return r;
            if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
                return 8;
        }
        return 0;

    case 0x4b:
        if (target == 0 && other != 0)
            return 7;
        {
            unsigned r = FUN_00d1e530(info, self, target, other);
            if (r != 0)
                return r;
            if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
                return 8;
        }
        return 0;

    case 0x51:
        if (self->mByte137 == 1)
            return 1;
        if ((self->mFlags110 & 0x1000) != 0)
            return 1;
        if (FUN_00d2e340()->mValue8 == 0)
            return 1;
        if (self->FUN_00c0e0c0(0x5485a4c) != 0)
            return 1;
        if (self->FUN_00c0e0c0(0x77300ff) != 0)
            return 1;
        if (info->mFloatAC > self->mRangeE58)
            return 1;
        return 0;

    case 0x53:
        if (self->mByte137 == 0 && (self->mFlags110 & 0x1000) == 0)
            return 9;
        if (!(info->mFloatAC > self->mRangeE58))
            return 0;
        return 9;
    }
    return 0;
}
// @ 0x00d1fb30
// SP::ValidateAbilityTarget -- the tribe the ability is used on must own the tool it needs.
unsigned int F_d1fb30(unsigned int abilitySlot)
{
    if (abilitySlot > 5)
        return 1;

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** cvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)cvt[0x5c / 4])(terrain, &vec);

    AbilityInfo* ability = g_abilityTable[abilitySlot];
    unsigned     group = ability->mType - 5;
    if (group > 0x36) {
        FUN_00ad92d0(&vec);
        return 1;
    }

    switch (group) {
    case 0: case 1: case 2:                     // ability types 5/6/7 need tools 4/5/6
        {
            int  count = (int)(vec.mpEnd - vec.mpBegin);
            char any = 0;
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return 14;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                void*  found = ((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                CreatureModel* model = ((AbilityCreature*)found)->mpModelBC;
                if (model->mTypeId1d8 != 0xb46e8803u)
                    continue;
                cAbilityItem* item = (cAbilityItem*)FUN_00d9f530(
                    ((CreatureInner*)model->mpInner600)->mpField1a8);
                if (item->mByte51 == 0) {
                    FUN_00ad92d0(&vec);
                    return 15;
                }
                int      tool = ((AbilityCreature*)found)->FUN_00c22dc0();
                unsigned want;
                if (tool == 4)
                    want = 3;
                else if (tool == 5)
                    want = 4;
                else if (tool == 6)
                    want = 5;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                float r = FUN_00d1e7f0(found, ability);
                if (r <= 1.0f) {
                    FUN_00ad92d0(&vec);
                    return 0;
                }
                any = 1;
            }
            FUN_00ad92d0(&vec);
            return any ? 15 : 14;
        }

    case 38: case 53: case 54:                  // ability types 0x2b/0x3a/0x3b need tools 3/1/2
        {
            int  count = (int)(vec.mpEnd - vec.mpBegin);
            char any = 0;
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return 13;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                void*  found = ((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                void* other = ((AbilityCreature*)found)->FUN_00c0ee60();
                if (other == 0)
                    continue;
                if (((cAbilityOwner*)other)->GetFileCount() == 2)
                    continue;
                CreatureModel* model = ((AbilityCreature*)found)->mpModelBC;
                if (model->mTypeId1d8 != 0x5218bb3u)
                    continue;
                int      tool = ((AbilityCreature*)found)->FUN_00c22dc0();
                unsigned want;
                if (tool == 1)
                    want = 0;
                else if (tool == 2)
                    want = 1;
                else if (tool == 3)
                    want = 2;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                float r = FUN_00d1e7f0(found, ability);
                if (r <= 1.0f) {
                    FUN_00ad92d0(&vec);
                    return 0;
                }
                any = 1;
            }
            FUN_00ad92d0(&vec);
            return any ? 15 : 13;
        }

    default:                                    // every other ability type
        FUN_00ad92d0(&vec);
        return 1;
    }
}
// @ 0x00d1fe00
// SP::ActivateAbilityTarget -- plays the activate animation on every creature that wields the tool.
void F_d1fe00(unsigned int abilitySlot)
{
    if (abilitySlot > 5)
        return;

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** tvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)tvt[0x5c / 4])(terrain, &vec);

    AbilityInfo* ability = g_abilityTable[abilitySlot];
    unsigned     group = ability->mType - 5;
    if (group > 0x36) {
        FUN_00ad92d0(&vec);
        return;
    }

    switch (group) {
    case 0: case 1: case 2:                     // ability types 5/6/7 need tools 4/5/6
        {
            int count = (int)(vec.mpEnd - vec.mpBegin);
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                AbilityCreature* found = (AbilityCreature*)((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                if (found->mpModelBC->mTypeId1d8 != 0xb46e8803u)
                    continue;
                int      tool = found->FUN_00c22dc0();
                unsigned want;
                if (tool == 4)
                    want = 3;
                else if (tool == 5)
                    want = 4;
                else if (tool == 6)
                    want = 5;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                int idx = FUN_00d1e5c0(found, ability);
                if (idx == -1)
                    continue;
                if (found->mpAbilitySlots[idx].mFloat4 < g_kOne)
                    continue;
                cAnimHandle* h = found->mpModelBC->mAnim.FUN_00bc97f0(0x10000000, 0, g_kTen, 0);
                h->mFieldC = (unsigned)idx;
            }
            FUN_00ad92d0(&vec);
        }
        break;

    case 38: case 53: case 54:                  // ability types 0x2b/0x3a/0x3b need tools 3/1/2
        {
            int count = (int)(vec.mpEnd - vec.mpBegin);
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                AbilityCreature* found = (AbilityCreature*)((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                void* other = found->FUN_00c0ee60();
                if (other == 0)
                    continue;
                if (((cAbilityOwner*)other)->GetFileCount() == 2)
                    continue;
                if (found->mpModelBC->mTypeId1d8 != 0x5218bb3u)
                    continue;
                int      tool = found->FUN_00c22dc0();
                unsigned want;
                if (tool == 1)
                    want = 0;
                else if (tool == 2)
                    want = 1;
                else if (tool == 3)
                    want = 2;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                int idx = FUN_00d1e5c0(found, ability);
                if (idx == -1)
                    continue;
                if (found->mpAbilitySlots[idx].mFloat4 < g_kOne)
                    continue;
                cAnimHandle* h = found->mpModelBC->mAnim.FUN_00bc97f0(0x10000000, 0, g_kTen, 0);
                h->mFieldC = (unsigned)idx;
            }
            FUN_00ad92d0(&vec);
        }
        break;

    default:                                    // every other ability type does nothing
        FUN_00ad92d0(&vec);
        return;
    }
}

// @ 0x00d200a0
// SP::ScoreAbilityRange -- best interaction score among the tool wielders within range.
float F_d200a0(int range)
{
    float acc = 0.0f;

    void* ability = FUN_00d1e830(range);
    if (ability == 0)
        return acc;

    void* caster = FUN_00d1e610();
    if (caster == 0)
        return 0.0f;

    void** cvt = *(void***)caster;
    int    target = range - ((GetFieldVfn)cvt[0xb0 / 4])(caster);

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** tvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)tvt[0x5c / 4])(terrain, &vec);

    int count = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < count; i++) {
        void* so = vec.mpBegin[i];
        if (so == 0)
            continue;
        void** svt = *(void***)so;
        AbilityCreature* found = (AbilityCreature*)((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
        if (found == 0)
            continue;
        int tool = found->FUN_00c22dc0() - 1;
        if ((unsigned)tool > 5)
            continue;
        if (target != tool)
            continue;
        float score = FUN_00d1e7f0(found, ability);
        acc = (acc > score) ? acc : score;
    }
    FUN_00ad92d0(&vec);
    return acc;
}
