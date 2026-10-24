// Slice s00c14350 -- Simulator locomotion / animation-target helpers on SP::cSPCreatureBase,
// plus a cContentValidationSummarizer singleton, a small free-list, a gamedata reader and
// animation-effect attach/detach helpers.  0x00c14350..0x00c15307.
//
// Retail layout (from the disassembly, all offsets named below):
//   creature+0x2b0  int  mPlanetCorrection / locomotion phase id
//   creature+0x328  bool mbSelfPowered
//   creature+0x5a8  damage-state / combatant sub-object (cCombatant)
//   creature+0xb20  creature profile / definition data
//   creature+0xb38  wide-string definition name
//   creature+0xb54  cAnimatedCreature* mpAnimatedCreature
//   creature+0xb5e  bool mbB5E
//   creature+0xc0   cLocomotiveObject (cSpatialObject) sub-object
//   creature+0xe38  bool mbE38
//   creature+0xf98  int  mLocomotionState
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no EH frame.
#include "types.h"
#include <stdlib.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
};
struct Quaternion {
    float x, y, z, w;
};
struct Matrix3 {
    float m[9];
};

// ---------------------------------------------------------------------------
// EA::Variant (16 bytes) -- value + type tag; cCommandParameterSet's map value.
// ---------------------------------------------------------------------------
struct Variant {
    uint32_t mValue;    // +0x00
    uint32_t mType;     // +0x04
    uint32_t pad08;
    uint32_t pad0c;
};

// ---------------------------------------------------------------------------
// eastl-style intrusive red-black tree base/common layout used by the maps here.
//   RbNodeBase: mpRight@+0, mpLeft@+4, mpParent@+8, mColor@+0xc
//   RbTreeBase: pad0[4], mAnchor@+4, mnSize@+0x14
// ---------------------------------------------------------------------------
struct RbNode {
    RbNode* mpRight;    // +0x00
    RbNode* mpLeft;     // +0x04
    RbNode* mpParent;   // +0x08
    uint8_t mColor;     // +0x0c
    uint8_t pad0d[3];
};
RbNode* RbTreeIncrement(RbNode* node);      // 0x00921580
void    RbTreeErase(RbNode* node, RbNode** itOut);  // 0x00921880

struct RbTreeBase {
    uint32_t pad0;          // +0x00
    RbNode   mAnchor;       // +0x04
    uint32_t mnSize;        // +0x14

    __forceinline void reset()
    {
        mAnchor.mpRight  = &mAnchor;
        mAnchor.mpLeft   = &mAnchor;
        mAnchor.mpParent = 0;
        mAnchor.mColor   = 0;
        mnSize           = 0;
    }
};

// eastl::map<unsigned, EA::Variant> (0x18 bytes) -- VarMap.
struct VarMapNode {
    RbNode   mBase;     // +0x00
    uint32_t mKey;      // +0x10
    Variant  mValue;    // +0x14
};

struct VarMap : public RbTreeBase {
    // map<unsigned,Variant>::operator[] -- insert-or-get; extern (0x0068BF20)
    Variant* GetPos(uint32_t* key);
    // map find -- extern (0x00E5C780)
    void Find(void* out, void* key);
};

// ---------------------------------------------------------------------------
// WStr -- eastl::basic_string<wchar_t>.
// ---------------------------------------------------------------------------
struct WStr {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCap;      // +0x08
    void assign(const wchar_t* s);
};

// ---------------------------------------------------------------------------
// cGameData -- base of the serializable gamedata objects.  Read/PadTo/GetStream.
// ---------------------------------------------------------------------------
struct cGameData {
    PV8 PV8 PV8 PV8 PV8 PV2 PV
    virtual void* GetStream();                       // +0x20  (returns object whose +0x18 is the reader)
    PV8 PV8 PV2 PV2 PV2 PV2 PV4
    virtual uint32_t GetID();                        // +0x3c
};

// ---------------------------------------------------------------------------
// cContentValidationSummarizer -- tiny singleton (0x10 bytes).
// ---------------------------------------------------------------------------
struct cContentValidationSummarizer {
    PV2
    virtual void v08();                              // +0x08
};
cContentValidationSummarizer* GetContentValidationSummarizer();   // 0x00c14350

// ---------------------------------------------------------------------------
// Ref-counted interfaces used through vtables.
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV2
    virtual void Init();                             // +0x10
    virtual void Deinit();                           // +0x14
};

// ---------------------------------------------------------------------------
// Animation effect record / cAnimatedCreature / body parts.  Retail offsets
// copied from the neighbouring slices (see s00c11410).
// ---------------------------------------------------------------------------
struct BodyPart {
    uint32_t pad00[4];
    Vector3 mPosition;          // +0x10
    Quaternion mOrientation;    // +0x1c
    uint32_t pad2C[0x38];
    float mRestDim0;            // +0x10c
    uint32_t pad110[0x0a];
    float mUnk138;              // +0x138
    float mUnk13C;              // +0x13c
    float mUnk140;              // +0x140
};
struct cCreatureInstanceData {
    uint32_t pad00[6];
    Vector3 mPosition;          // +0x18
    Quaternion mOrientation;    // +0x1c
    uint32_t pad2C[0xae];
    BodyPart* mBodyParts;       // +0x2e4
};

struct cAnimatedCreature {
    PV2                                              // +0x00, +0x04 (vptr, slot1)
    virtual void* V08(uint32_t layerID, int b);      // +0x08
    virtual void V0C(void* handle, int b);           // +0x0c
    PV2                                              // +0x10, +0x14
    virtual void V18(void* handle);                  // +0x18
    PV                                               // +0x1c
    virtual void V20(void* handle, int a);           // +0x20
    virtual void V24(void* handle, float f);         // +0x24

    uint32_t pad04[(0x17c - 0x04) / 4];              // 0x04..0x17c
    cCreatureInstanceData* mpInstanceData;           // +0x17c
    uint32_t pad180;
    void* mpField184;                                // +0x184  anim quest handle set
    uint32_t mpField188;                             // +0x188
    uint32_t mpCurrentAnim;                          // +0x18c
};

// 0x00c151b0/0x00c15270 walk the effect hash at instanceData+0x17a4 (buckets ptr),
// +0x17a8 (bucket index); each node: +0x04 -> inner object (+0x8c effect), +0x08 next.

// ---------------------------------------------------------------------------
// Locomotive object sub-object (creature+0xc0).
// ---------------------------------------------------------------------------
struct cSpatialObject {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    PV8 PV
    virtual Vector3* GetSampleDir(Vector3* out);     // +0x5c
    virtual void* GetLocalExtents();                 // +0x68
    PV
    virtual float GetFootprintRadius();              // +0x74

    void FUN_c421b0(void* arg);                      // 0x00c421b0
};

// animation-event quest (at cAnimatedCreature handled by WaitForAnimEventOrEnd).
struct AnimQuest {
    uint32_t pad00[(0x8c / 4)];
    // events at +0x8c stride 0xc; count at +0x14c
};

// XformMsg (0x40 bytes) -- passed to effect SetTransform.
struct XformMsg {
    uint16_t mFlags;         // +0x00
    uint16_t mVersion;       // +0x02
    uint32_t pad04;
    Vector3 mOffset;         // +0x04 (+4)
    Matrix3 mRot;            // +0x10
    float   mScale;          // +0x34
};
void XformMsg_ctor(XformMsg* msg);                   // 0x00434040

// combatant sub-object at creature+0x5a8 (used by DoHitGround/OnJumpLand)
struct cDamageSub {
    int GetDamageState();                            // 0x008e7f80
};

// ---------------------------------------------------------------------------
// cCreatureProfile / definition data at creature+0xb20.
// ---------------------------------------------------------------------------
struct cCreatureProfile {
    uint32_t pad00[0x61c / 4];
    uint32_t mField61C;                              // +0x61c
    uint32_t pad620[(0x698 - 0x620) / 4];
    uint32_t mField698;                              // +0x698
    uint32_t pad69C;
    uint32_t mField6A0;                              // +0x6a0
};

// ---------------------------------------------------------------------------
// The creature, retail offsets.  Also serves as the cLocomotiveObject when we
// are handed `this == creature+0xc0`.
// ---------------------------------------------------------------------------
struct CreatureBase {
    PV8 PV8 PV8 PV8 PV8 PV2 PV
    virtual void* Cast(uint32_t type);               // +0x20
    PV8 PV8
    virtual void V2C(int a);                         // +0x2c
    PV8 PV8 PV8 PV8 PV8 PV8
    virtual void V48(int a);                         // +0x48
    virtual void V4C(int a);                         // +0x4c
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    virtual void V78(int a);                         // +0x78
    PV8 PV8

    uint8_t  pad04[(0xb0 - 0x04)];                   // 0x04..0xb0
    int32_t  mAttackTimer;                           // +0xb0
    uint8_t  padB4[(0xc0 - 0xb4)];
    uint8_t  mSpatial[(0x2b0 - 0xc0)];               // +0xc0 cSpatialObject sub-object (opaque here)
    int32_t  mLocomotionState;                       // +0x2b0
    uint8_t  pad2B4[(0x328 - 0x2b4)];
    uint8_t  mbSelfPowered;                          // +0x328
    uint8_t  pad329[(0x5a8 - 0x329)];
    uint32_t mCombatantVptr;                         // +0x5a8  (damage-state sub-object at (char*)self+0x5a8)
    uint8_t  pad5AC[(0xb20 - 0x5ac)];
    cCreatureProfile* mpSpeciesProfile;              // +0xb20
    uint8_t  padB24[(0xb38 - 0xb24)];
    wchar_t* mpDefinitionName;                       // +0xb38
    uint8_t  padB3C[(0xb54 - 0xb3c)];
    cAnimatedCreature* mpAnimatedCreature;           // +0xb54
    uint16_t padB58;
    uint8_t  padB5A[(0xb5e - 0xb5a)];
    uint8_t  mbB5E;                                  // +0xb5e
    uint8_t  padB5F[(0xe38 - 0xb5f)];
    uint8_t  mbE38;                                  // +0xe38
    uint8_t  padE39[(0xf98 - 0xe39)];
    int32_t  mLocomotionStateF98;                    // +0xf98

    cAnimatedCreature* Anim() { return mpAnimatedCreature; }
    void* FUN_b3d310();                              // 0x00b3d310
    int   FUN_b3d240();                              // 0x00b3d240

    // 00c14590..00c15270
    int  AnimationAction(uint32_t id, int mode);
    void UpdateLocomotionAnimation();
    void UpdateLocomotion(int param2);
    int  PlayAnimationWithTarget(uint32_t id, void* target, int arg4);
    int  PlayAnimationWithTargetObj(uint32_t id, void* target, int arg5);
    int  InterruptAnimationWithTarget(uint32_t id, void* target, int arg4);
    int  InterruptAnimationWithTargetObj(uint32_t id, void* target, int arg5);
    void DoHitGround();
    void OnStartSwimming();
    void NotifySummarizer();
    int  WaitForAnimEventOrEnd(int event, uint32_t* out, int arg4, int arg5);
    void* CreateBodyEffectByIndex(int partIdx, uint32_t visualEffectId, uint32_t id);
    bool DetachBodyEffectById(void* handle, void* arg3);
    void DetachAllBodyEffects();
    void SetBodyEffectParam(uint32_t param);

    // external callees that are thiscall on the creature
    int  PlayAnimation(uint32_t id, int arg2, int arg3);        // 0x00c12190
    int  InterruptAnimation(uint32_t id, int arg2, int arg3);   // 0x00c12310
    int  FUN_00c0e040();                                        // 0x00c0e040
    void FUN_00c0c630(int a, int* b, int* c, int* d);           // 0x00c0c630
    int  FUN_00c0e2c0(int a);                                   // 0x00c0e2c0
    int  FUN_00c0e170(int a);                                   // 0x00c0e170
    void FUN_00c0cff0(int a);                                   // 0x00c0cff0
};

// cLocomotiveObject == the mSpatial sub-object; recover the creature from it.
static inline CreatureBase* Owner(cSpatialObject* spatial)
{
    return (CreatureBase*)((char*)spatial - 0xc0);
}

// ---- callees (cdecl unless noted; address in the comment) ----
void*  EAAllocate(uint32_t size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void   EAFree(void* p);                                                                       // 0x00f47380
void   DeleteObject(void* p);                                                                 // 0x00f47380
void*  operator_new(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
bool   FUN_00c04750(void* self);                                                              // 0x00c04750
void*  FUN_00b18600(void* self, void* stream);                                                // 0x00b18600  cGameData::Read
bool   FUN_00cee440(void* self, void* stream);                                                // 0x00cee440
bool   FUN_00c43c10(void* self, void* stream);                                                // 0x00c43c10
bool   FUN_00bfc540(void* self, void* stream);                                                // 0x00bfc540
void   FUN_00bc9ac0(void* stream);                                                            // 0x00bc9ac0
void   FUN_00c14070(void* node);                                                              // 0x00c14070
void   FUN_00c0c4b0(void* self, float f);                                                     // 0x00c0c4b0  QuatHalf
bool   FUN_00a02b40(void* self, int a);                                                       // 0x00a02b40
int    FUN_00a01f10(void* a, int b);                                                          // 0x00a01f10
int    FUN_009ff6f0(void* a, void* b);                                                        // 0x009ff6f0
void*  FUN_009cab60(void* a);                                                                 // 0x009cab60
void   FUN_009cb460(void* effect);                                                            // 0x009cb460
void*  FUN_009cb300(void* instanceData, int id, int a, int b);                                // 0x009cb300
void   FUN_009caa40(void* effect, int partIdx, int a, int b);                                 // 0x009caa40
int    FUN_00a02bd0(void* self);                                                              // 0x00a02bd0
void   FUN_00434040(void* msg);                                                              // 0x00434040
void   Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);                              // 0x0059c190
int    FUN_00454cb0(void* a, void* b, void* c);                                               // 0x00454cb0
void*  FUN_004010a0(void* self, int id);                                                      // 0x004010a0
void*  FUN_005ecf80(void* self, int id);                                                      // 0x005ecf80
void   StrAssign(WStr* self, const wchar_t* begin, const wchar_t* end);                       // 0x00423650
void*  GetCurrentGameMode();                                                                  // 0x00b5b800
void*  InterfaceCast(void* obj);                                                              // 0x00ac8960
int    ReadInt32(void* stream, void* out, int count, int a);                                  // 0x0093a780
void   VtFind(void* self, void* out, uint32_t* key);                                          // 0x00645ed0
int    FUN_00cee330(void* self);                                                              // 0x00cee330
void   FUN_00c3c10Serializer(void* self, void* stream);                                       // 0x00692f90 (cVarListSerializer + Read)
void   ExitHandler(void);                                                                     // 0x013c3590

// animation side callees
void   AddSetAnimationTargetModifier3(CreatureBase* self, int handle, void* target);          // 0x00c0b570
void   AddSetAnimationTargetModifier4(CreatureBase* self, int handle, void* target, void* obj); // 0x00c0b510
void   DetachBodyEffect(void* rec, bool release);                                             // 0x00c12080
void   FUN_00c0cff0(CreatureBase* self, int a);                                               // 0x00c0cff0
int    FUN_00c14590(CreatureBase* self, uint32_t id, int mode);                               // 0x00c14590

struct cEffectsManager {
    PV8 PV2 PV
    virtual bool CreateVisualEffect(uint32_t id, int flags, void** ppEffect);  // +0x2c
};
cEffectsManager* EffectsManager();                   // 0x0067ddd0

// ---- globals ----
extern float gF_13eb1bc;         // 0x13eb1bc  duration for animation-mode 2
extern float gF_13ef74c;         // 0x13ef74c  body-effect part scale
extern float gF_157174c;         // 0x157174c  half-turn angle
extern uint32_t gSingleton168d900;  // 0x168d900

// ===========================================================================
// @ 0x00c14350
// ===========================================================================
cContentValidationSummarizer* GetContentValidationSummarizer()
{
    static cContentValidationSummarizer* sSingleton;
    if (sSingleton != 0)
        return sSingleton;
    cContentValidationSummarizer* p =
        (cContentValidationSummarizer*)EAAllocate(0x10, "Simulator/LocomotionStrategy_Template", 0, 0, 0, 0);
    sSingleton = p;
    if (p != 0) {
        *(void**)((char*)p + 8)  = 0;
        *(uint32_t*)((char*)p + 12) = 0;
    }
    return sSingleton;
}

// ===========================================================================
// @ 0x00c144e0  PoolAlloc  (__thiscall: ecx = pool, one stack arg -> out[2])
// ===========================================================================
struct PoolNode {
    uint32_t mNext;     // +0x00  (free-list link, = node[0] when free)
    uint32_t mValue1;   // +0x04
    uint32_t mValue2;   // +0x08
};
struct Pool {
    uint32_t pad00[0x1c / 4];
    PoolNode* mpFree;        // +0x1c
    uint32_t pad20[3];       // 0x20..0x2c
    uint32_t mnAllocSize;    // +0x2c

    void* Alloc(uint32_t* out);
};
void* Pool::Alloc(uint32_t* out)
{
    PoolNode* node = mpFree;
    if (node == 0) {
        node = (PoolNode*)EAAllocate(
            mnAllocSize, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    } else {
        mpFree = (PoolNode*)node->mNext;
    }
    if (node != 0) {
        node->mNext = out[0];
        node->mValue1 = out[1];
    }
    node->mValue2 = 0;
    return node;
}

// ===========================================================================
// @ 0x00c14530  DestroyPool
// ===========================================================================
void DestroyPool()
{
    uint8_t* p = (uint8_t*)gSingleton168d900;
    if (gSingleton168d900 != 0) {
        uint8_t* slot = p + 0x1c;
        if (*(IRefCounted**)(p + 0x1c) != 0)
            (*(IRefCounted**)(p + 0x1c))->Release();
        int n = 6;
        do {
            slot -= 4;
            if (*(IRefCounted**)slot != 0)
                (*(IRefCounted**)slot)->Release();
            n--;
        } while (n >= 0);
        EAFree(p);
    }
    gSingleton168d900 = 0;
}

// ===========================================================================
// @ 0x00c14590
// ===========================================================================
int CreatureBase::AnimationAction(uint32_t id, int mode)
{
    if (mode == 0)
        return PlayAnimation(id, 1, -1);
    if (mode == 1)
        return InterruptAnimation(id, -1, 0);
    if (mode == 2) {
        cAnimatedCreature* anim = mpAnimatedCreature;
        int h = (int)anim->V08(id, 0);
        anim->V0C((void*)h, 2);
        anim->V18((void*)h);
        anim->V20((void*)h, 1);
        anim->V24((void*)h, gF_13eb1bc);
        return h;
    }
    return 0;
}

// ===========================================================================
// @ 0x00c14640
// ===========================================================================
void CreatureBase::UpdateLocomotionAnimation()
{
    cAnimatedCreature* pi = 0;
    if (this != 0 && Cast(0x18eb4b7) != 0)
        pi = mpAnimatedCreature;

    uint32_t anim;
    if (mLocomotionStateF98 == 1)
        anim = 0x2481de6;
    else if (mLocomotionStateF98 == 3)
        anim = 0x35455a4;
    else
        anim = 0x354559b;
    if (mbB5E)
        anim = 0x35455a4;

    cAnimatedCreature* anim2 = mpAnimatedCreature;
    if (pi != 0 && FUN_00cee330((char*)pi + 0x34) != 0) {
        FUN_00a01f10((void*)anim2->mpCurrentAnim, 0);
        anim2->mpCurrentAnim = 0;
        return;
    }
    int rec = FUN_009ff6f0((void*)anim2->mpField184, (void*)anim2->mpCurrentAnim);
    if (rec != 0 && *(uint32_t*)rec != 0 && *(uint32_t*)(*(uint32_t*)rec) != 0) {
        if (*(uint32_t*)(rec + 0xd8) == anim)
            return;
        uint32_t old = anim2->mpCurrentAnim;
        uint32_t nh = (uint32_t)AnimationAction(anim, 2);
        anim2->mpCurrentAnim = nh;
        FUN_00a01f10((void*)old, 0);
        return;
    }
    cAnimatedCreature* a3 = mpAnimatedCreature;
    a3->mpCurrentAnim = (uint32_t)AnimationAction(anim, 2);
}

// ===========================================================================
// @ 0x00c14750
// ===========================================================================
void CreatureBase::UpdateLocomotion(int param2)
{
    if (mbB5E)                     // +0xb5e
        return;
    if (mbE38)                     // +0xe38
        return;
    cAnimatedCreature* anim = mpAnimatedCreature;
    if (anim == 0)
        return;
    if (anim->mpField184 == 0)
        return;

    if (GetCurrentGameMode() == (void*)0x1654c10 && *(uint32_t*)((char*)0x16c7aa4 + 0xcc) == 1) {
        bool dead = FUN_00c04750(InterfaceCast(this));
        if (dead && *(uint8_t*)((char*)dead + 2) != 0)
            return;
    }

    int cur = FUN_00c0e040();        // GetCurrentAnimationGUID
    int local4 = cur;
    int localC = cur;
    int local8 = -1;
    FUN_00c0c630(param2, &local4, &localC, &local8);

    int got = localC;
    if (cur == got)
        return;

    bool q = FUN_00a02b40(mpAnimatedCreature, got);
    char mode = (char)param2;
    if (!q || mode != 0) {
        AnimationAction(got, mode != 0 ? 1 : 0);
        if (local8 != -1) {
            AnimationAction(local8, mode != 0 ? 1 : 0);
            UpdateLocomotionAnimation();
            return;
        }
        cAnimatedCreature* a = mpAnimatedCreature;
        FUN_00a01f10((void*)a->mpField188, 0);
        FUN_00a01f10((void*)a->mpCurrentAnim, 0);
        a->mpCurrentAnim = 0;
    }
}

// ===========================================================================
// @ 0x00c148a0
// ===========================================================================
struct cEffectMgr {
    int DecrementNode(void* node);                   // 0x00c14070
};
bool ReleaseEffectRef(uint32_t* self)
{
    if (self[0xf] != 0) {
        void* obj = (void*)self[0xf];
        uint32_t r = (*(uint32_t(**)(void*, uint32_t))(*(uint32_t*)obj + 0xc))(obj, 0xce9f6639);
        if (r != 0 && self != 0) {
            if (self[2] != 0) {
                uint32_t base = *(uint32_t*)(r + 0xe40);
                uint32_t idx = *self * 0x24;
                uint32_t cnt = *(uint32_t*)(base + idx + 0xc);
                uint8_t* ent = (uint8_t*)(base + idx);
                if (cnt > 0)
                    *(uint32_t*)(ent + 0xc) = cnt - 1;
                if (*(uint32_t*)(ent + 0xc) == 0 && *(uint32_t*)(ent + 8) != 0)
                    ((cEffectMgr*)base)->DecrementNode(ent);
            }
            return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00c14910
// ===========================================================================
int CreatureBase::PlayAnimationWithTarget(uint32_t id, void* target, int arg4)
{
    int h = PlayAnimation(id, 1, arg4);
    AddSetAnimationTargetModifier3(this, h, target);
    return h;
}

// ===========================================================================
// @ 0x00c14940
// ===========================================================================
int CreatureBase::PlayAnimationWithTargetObj(uint32_t id, void* target, int arg5)
{
    int h = PlayAnimation(id, 1, arg5);
    if (target != 0) {
        void* r = (*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t*)target + 0xb8))(target, 0xee3f516e);
        if (r != 0)
            AddSetAnimationTargetModifier4(this, h, r, target);
    }
    return h;
}

// ===========================================================================
// @ 0x00c14990
// ===========================================================================
int CreatureBase::InterruptAnimationWithTarget(uint32_t id, void* target, int arg4)
{
    int h = InterruptAnimation(id, arg4, 0);
    AddSetAnimationTargetModifier3(this, h, target);
    return h;
}

// ===========================================================================
// @ 0x00c149c0
// ===========================================================================
int CreatureBase::InterruptAnimationWithTargetObj(uint32_t id, void* target, int arg5)
{
    int h = InterruptAnimation(id, arg5, 0);
    if (target != 0) {
        void* r = (*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t*)target + 0xb8))(target, 0xee3f516e);
        if (r != 0)
            AddSetAnimationTargetModifier4(this, h, r, target);
    }
    return h;
}

// ===========================================================================
// @ 0x00c14a10
// ===========================================================================
struct Str {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    char* mpCap;     // +0x08
    void assign(const char* first, const char* last);   // 0x00423650 (basic_string<char>)
};
void __fastcall AssignDefinitionName(void* self, void* /*edx*/, Str* out)
{
    intptr_t holder = (intptr_t)self - 0x68;
    void* a = (*(void*(**)(void*))(*(uint32_t*)holder + 0x20))((void*)holder);
    if (a == 0)
        return;
    void* b = (*(void*(**)(void*))(*(uint32_t*)holder + 0x20))((void*)holder);
    const char* s = (const char*)(*(const char*(**)(void*))(*(uint32_t*)b + 0x14))(b);
    const char* end = s;
    while (*end)
        end++;
    out->assign(s, end);
}

// ===========================================================================
// @ 0x00c14a60  GetGlobalNameList
// ===========================================================================
void* GetGlobalNameList()
{
    static void* sList[3];
    static uint32_t sInit;
    if ((sInit & 1) == 0) {
        sInit |= 1;
        sList[0] = 0;
        sList[1] = 0;
        sList[2] = 0;
        atexit(ExitHandler);
    }
    return sList;
}

// ===========================================================================
// @ 0x00c14aa0  ReadGameData
// ===========================================================================
bool ReadGameData(cGameData* self, void* stream)
{
    // stream->vt[0x20]() then result->vt[0x18]() -> reader; read one int32.
    void* a = (*(void*(**)(void*))stream)(stream);
    void* reader = (*(void*(**)(void*))a)(a);
    int v0 = 0;
    ReadInt32(reader, &v0, 1, 0);

    bool ok;
    if (!FUN_00b18600(self, stream))
        ok = false;
    else if (!FUN_00cee440((char*)self + 0x34, stream))
        ok = false;
    else if (!FUN_00c43c10((char*)self + 0xc0, stream))
        ok = false;
    else if (!FUN_00bfc540((char*)self + 0x5a8, stream))
        ok = false;
    else
        ok = true;

    void* b = (*(void*(**)(void*))stream)(stream);
    void* reader2 = (*(void*(**)(void*))b)(b);
    int v1 = 0;
    ReadInt32(reader2, &v1, 1, 0);
    *(uint8_t*)((char*)self + 0xbd) = v1 != 0;

    FUN_00bc9ac0(stream);
    FUN_00c3c10Serializer((char*)self, stream);
    uint32_t ver = self->GetID();
    (void)ver;
    return ok;
}

// ===========================================================================
// @ 0x00c14cb0
// ===========================================================================
void CreatureBase::DoHitGround()
{
    uint32_t local10 = 0;
    cAnimatedCreature* anim = mpAnimatedCreature;
    bool matched = false;
    if (anim != 0) {
        // anim->vt[0x58](&local10, 0, 0, 0)
        (*(void(__thiscall*)(void*, uint32_t*, int, int, int))(*(uint32_t*)anim + 0x58))(anim, &local10, 0, 0, 0);
        switch (local10) {
        case 0x25b3bc0: case 0x772ff58: case 0x7995fdc:
        case 0x7982fb2: case 0x7b5063e:
            matched = true; break;
        default: break;
        }
    }
    if (!matched) {
        switch (local10) {
        case 0x5261d56: case 0x5261d78: case 0x692e5bf:
        case 0x5485a4c: case 0x77300f2: case 0x77300fb: case 0x77300ff:
            matched = true; break;
        default: break;
        }
    }
    if (matched) {
        if (mbB5E == 0) {
            cCreatureProfile* prof = mpSpeciesProfile;
            if (prof->mField61C == 0) {
                UpdateLocomotion(1);
                prof = mpSpeciesProfile;
                uint32_t a = (prof->mField6A0 == 0) ? 0x25b3bc2 : 0x773009a;
                InterruptAnimation(a, -1, 0);
            } else {
                uint32_t a = (prof->mField698 == 0) ? 0x5261d57 : 0x7730105;
                InterruptAnimation(a, -1, 0);
            }
        }
    }

    mLocomotionState = 0;

    if (((cDamageSub*)((char*)this + 0x5a8))->GetDamageState() == 2) {
        void* mgr = (void*)FUN_b3d240();
        cSpatialObject* sp = (cSpatialObject*)((char*)this + 0xc0);
        Vector3 buffer;
        Vector3* sd = sp->GetSampleDir(&buffer);
        Vector3* pos = (Vector3*)(*(void*(**)(void*))(*(uint32_t*)sd + 0x2c))(sd);
        void* mgrVt = *(void**)mgr;
        (*(void(**)(void*, uint32_t, void*))((char*)mgrVt + 0x60))(mgr, 0x1b55d9a, pos);
        FUN_00c0cff0(0);
    }
    if (mbSelfPowered == 0)
        mbSelfPowered = 1;
}

// ===========================================================================
// @ 0x00c14e10
// ===========================================================================
void CreatureBase::OnStartSwimming()
{
    if (mpSpeciesProfile->mField61C == 0)
        UpdateLocomotion(1);
    mLocomotionState = 3;
    if (mbSelfPowered == 0)
        mbSelfPowered = 1;
}

// ===========================================================================
// @ 0x00c14e50
// ===========================================================================
void CreatureBase::NotifySummarizer()
{
    FUN_b3d310();
    void* c = (void*)GetContentValidationSummarizer();
    ((cSpatialObject*)((char*)this + 0xc0))->FUN_c421b0(c);
}

// ===========================================================================
// @ 0x00c14e70
// ===========================================================================
void* __fastcall LookupTextStyle(void* self, void* /*edx*/, uint32_t* key)
{
    struct Hash {
        uint32_t pad0;       // +0x00
        void** mpBuckets;    // +0x04
        uint32_t mnIndex;    // +0x08
    };
    Hash* h1 = (Hash*)((uint8_t*)self + 0xcc8);
    void* it1 = 0;
    VtFind(h1, &it1, key);
    if (it1 != (void*)h1->mpBuckets[h1->mnIndex])
        return *(void**)((char*)it1 + 4);

    Hash* h2 = (Hash*)((uint8_t*)self + 0xd68);
    void* it2 = 0;
    VtFind(h2, &it2, key);
    if (it2 != (void*)h2->mpBuckets[h2->mnIndex])
        return *(void**)((char*)it2 + 4);
    return 0;
}

// ===========================================================================
// @ 0x00c14ef0
// ===========================================================================
int CreatureBase::WaitForAnimEventOrEnd(int event, uint32_t* out, int arg4, int arg5)
{
    *out = 0xffffffff;
    int ret;
    if (arg5 != 0) {
        ret = FUN_00c0e2c0(arg5);
    } else {
        int a = (arg4 == -1) ? 0 : arg4;
        ret = FUN_00c0e170(a);
    }
    cAnimatedCreature* anim = mpAnimatedCreature;
    uint32_t count = *(uint32_t*)((char*)anim + 0x14c);
    uint32_t i = 0;
    if (count != 0) {
        uint8_t* p = (uint8_t*)anim + 0x8c;
        while (*(int*)p != event) {
            i++;
            p += 0xc;
            if (i >= count)
                return ret;
        }
        *out = *(uint32_t*)((char*)anim + (i * 3 + 0x24) * 4);
        return 1;
    }
    return ret;
}

// ===========================================================================
// @ 0x00c14f70
// ===========================================================================
struct cEffectRec {
    uint32_t pad00[(0xa4 / 4)];
    void* mpUnkA4;           // +0xa4  refcounted; released
};
void* CreatureBase::CreateBodyEffectByIndex(int partIdx, uint32_t visualEffectId, uint32_t id)
{
    if (partIdx == -1)
        return 0;

    void* ref = 0;
    if (ref != 0)
        (*(void(**)(void*))(*(uint32_t*)ref + 4))(ref);

    cEffectsManager* mgr = EffectsManager();
    if (!mgr->CreateVisualEffect(id, 0, &ref)) {
        if (ref != 0)
            (*(void(**)(void*))(*(uint32_t*)ref + 4))(ref);
        return 0;
    }

    cAnimatedCreature* anim = mpAnimatedCreature;
    if (anim != 0 && FUN_00a02bd0(anim) == 0) {
        XformMsg msg;
        XformMsg_ctor(&msg);
        cSpatialObject* sp = (cSpatialObject*)((char*)this + 0xc0);
        Vector3* p = (Vector3*)&sp->GetPosition();
        msg.mOffset = *p;
        msg.mFlags |= 4;
        msg.mVersion++;
        const Quaternion* q = &sp->GetOrientation();
        Matrix3FromQuaternion(&msg.mRot, q);
        msg.mFlags |= 2;
        msg.mVersion++;
        (*(void(**)(void*, XformMsg*))(*(uint32_t*)ref + 0x18))(ref, &msg);
    }
    (*(void(**)(void*, int))(*(uint32_t*)ref + 8))(ref, 0);

    void* out = ref;
    if (ref != 0) {
        cAnimatedCreature* a2 = mpAnimatedCreature;
        cCreatureInstanceData* inst = a2->mpInstanceData;
        void* rec = FUN_009cb300(inst, id, 0, 0);
        if (rec != 0) {
            FUN_009caa40(rec, partIdx, 0, 0);
            BodyPart* bp = &inst->mBodyParts[partIdx];
            if ((bp->mUnk138 + bp->mUnk13C + bp->mUnk140) * gF_13ef74c < bp->mRestDim0)
                FUN_00c0c4b0((char*)rec + 0x18, gF_157174c);
            void* old = *(void**)((char*)rec + 0xa4);
            if (old != 0) {
                *(void**)((char*)rec + 0xa4) = 0;
                (*(void(**)(void*))(*(uint32_t*)old + 4))(old);
            }
        }
    }
    if (ref != 0)
        (*(void(**)(void*))(*(uint32_t*)ref + 4))(ref);
    return out;
}

// ===========================================================================
// @ 0x00c15150
// ===========================================================================
bool CreatureBase::DetachBodyEffectById(void* handle, void* arg3)
{
    if (mpAnimatedCreature == 0)
        return false;
    void* rec = FUN_009cab60(handle);
    if (rec == 0)
        return false;
    DetachBodyEffect(rec, arg3 != 0);
    FUN_009cb460(rec);
    return true;
}

// ===========================================================================
// @ 0x00c151b0
// ===========================================================================
void CreatureBase::DetachAllBodyEffects()
{
    if (mpAnimatedCreature == 0)
        return;
    if (mpAnimatedCreature->mpInstanceData == 0)
        return;
    for (;;) {
        uint8_t* inst = (uint8_t*)mpAnimatedCreature->mpInstanceData;
        void** buckets = *(void***)(inst + 0x17a4);
        uint32_t index = *(uint32_t*)(inst + 0x17a8);
        void* cur = buckets[0];
        if (cur == 0) {
            void** p = buckets + 1;
            while (*p == 0)
                p++;
            cur = *p;
        }
        if (cur == buckets[index])
            break;
        uint8_t* inst2 = (uint8_t*)mpAnimatedCreature->mpInstanceData;
        void** b2 = *(void***)(inst2 + 0x17a4);
        void* c2 = b2[0];
        if (c2 == 0) {
            void** p = b2 + 1;
            while (*p == 0)
                p++;
            c2 = *p;
        }
        if (mpAnimatedCreature != 0) {
            void* rec = FUN_009cab60(*(void**)c2);
            if (rec != 0) {
                DetachBodyEffect(rec, true);
                FUN_009cb460(rec);
            }
        }
    }
}

// ===========================================================================
// @ 0x00c15270
// ===========================================================================
void CreatureBase::SetBodyEffectParam(uint32_t param)
{
    uint8_t* inst = (uint8_t*)mpAnimatedCreature->mpInstanceData;
    void** buckets = *(void***)(inst + 0x17a4);
    uint32_t index = *(uint32_t*)(inst + 0x17a8);
    void* cur = buckets[0];
    if (cur == 0) {
        void** p = buckets + 1;
        while (*p == 0)
            p++;
        cur = *p;
    }
    void* end = buckets[index];
    while (cur != end) {
        void* inner = *(void**)((char*)*(void**)((char*)cur + 4) + 0x8c);
        if (inner != 0) {
            if ((*(bool(**)(void*))(*(uint32_t*)inner + 0x10))(inner))
                (*(void(**)(void*, int, uint32_t, int))(*(uint32_t*)inner + 0x44))(inner, 5, param, 3);
        }
        cur = *(void**)((char*)cur + 8);
        while (cur == 0) {
            buckets++;
            cur = *buckets;
        }
    }
}
