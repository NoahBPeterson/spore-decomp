// s00daf820.cpp -- SP tribe behaviour ticks (heal-self, tribe-tool get/destroy).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

#define PV(n) virtual void pv##n();

class IWin;

// --- globals ---------------------------------------------------------------
extern const float kDot01;        // 0x013eb960  0.01f
extern const float kDot001;       // 0x013f9428  0.001f
extern const float kTwoPow32;     // 0x013f4fd0  4294967296.0f
extern const float kTwo;          // 0x01470f1c  2.0f
extern const float kFive;         // 0x01486110  5.0f
extern const float kF1581370;     // 0x01581370
extern IWin*      g_pPropertyMgr; // 0x0158128c
extern const char kTribeRaid[];   // 0x0147c274 "TribeRaid"
extern uint8_t    DAT_01654c02;   // 0x01654c02

// --- free functions --------------------------------------------------------
extern "C" void FUN_00da75e0();                        // 0x00da75e0 (callback)
extern "C" char FUN_00da6270(void* a, int b);          // 0x00da6270 (cdecl)
extern "C" void* FUN_00b3d260();                       // 0x00b3d260 BehaviourManager
extern "C" void* FUN_00b5b800();                       // 0x00b5b800 GetCurrentGameMode
extern "C" void* FUN_00c9d9e0();                       // 0x00c9d9e0
extern "C" void* __stdcall FUN_00cd3440(uint32_t guid); // 0x00cd3440
extern "C" void* __stdcall FUN_00cd40b0(uint32_t guid); // 0x00cd40b0 Instance
extern "C" void* FUN_00bc9b00_3(uint32_t id, void* cb, void* p);        // stdcall
extern "C" void* FUN_00bc9b00_4(uint32_t id, int a, uint32_t b, const char* s); // stdcall
extern "C" void* FUN_00d998d0(void* obj, uint32_t id);  // 0x00d998d0  cdecl
extern "C" void  FUN_00c14750_();                       // placeholder (unused)
extern "C" double GetPropFloat(IWin* mgr, uint32_t id, float def); // 0x004e1c70 cdecl
extern "C" double sqrt_(double x);

struct Vector3 { float x, y, z; };

// --- intrusive-refcount interface -----------------------------------------
class IWin {
 public:
    PV(0)                                      // +0x00 AddRef
    PV(1)                                      // +0x04 Release
};

// --- sub-objects -----------------------------------------------------------
class cLoco : public IWin {                    // creature +0xc0
 public:
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual float* pv11();                     // +0x2c  world position
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual char   pv22();                     // +0x58
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52)
    PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
    virtual void   pv59();                     // +0xec
    PV(60) PV(61)
    virtual char   pv62();                     // +0xf8
    char FUN_00c42e20();                       // 0x00c42e20 IsNearGoal
};

class cM120 : public IWin {                    // object +0x120
 public:
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual float* pv11();                     // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    PV(22) PV(23)
    virtual double pv24();                     // +0x60
};

class cM120F : public IWin {                   // same object; +0x2c takes (float,float)
 public:
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual float* pv11f(float t, float r);
};

class cSpat34 : public IWin {                  // object +0x34
 public:
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual Vector3* pv11();                   // +0x2c
};

class cM5a8 : public IWin {                    // creature +0x5a8
 public:
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21)
    virtual double pv22();                     // +0x58
    void PartialRepair(float f);               // 0x00bfd1a0
};

class cMAnimPlayer {
 public:
    void* Play(int a, int b);                  // 0x00bc96a0
};

class cOrderMgr : public IWin {                // creature +0xb4c
 public:
    uint8_t      pad04[4];                     // +0x04
    cMAnimPlayer mAnim;                        // +0x08
    void FUN_00bcb480(void* node, void* a, int b, int c);    // 0x00bcb480
};

class cTribe : public IWin {                   // beast / tribe node object
 public:
    PV(2)
    virtual IWin*  pv3(uint32_t id);           // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21)
    virtual IWin*  pv22();                     // +0x58
    PV(23)
    virtual double pv24();                     // +0x60
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    virtual void*  pv43();                     // +0xac
    uint8_t  pad04[0x30];                      // +0x04..+0x34
    cSpat34  m34;                              // +0x34
    uint8_t  pad38[0xe8];                      // +0x38..+0x120
    cM120    m120;                             // +0x120
    void  FUN_00c9d010();                      // 0x00c9d010
    void  FUN_00c9d020();                      // 0x00c9d020
    void* GetToolOfType(int t);                // 0x00c8f6e0
    void  FindSpot(void* a, int b);            // 0x00c98750
};

// node payload reached as (node + 0x1a4)
struct RaidSub {
    uint8_t pad00[0x18];                       // +0x00..+0x18
    int32_t m18;                               // +0x18
    float   m1c;                               // +0x1c
    union { int32_t m20; uint8_t m20b; };      // +0x20
    uint8_t pad24[4];                          // +0x24
    int32_t m28;                               // +0x28
    int32_t m2c;                               // +0x2c
    int32_t m30;                               // +0x30
};

struct RaidNode {
    uint8_t  pad00[0x1a4];                     // +0x00..+0x1a4
    RaidSub  mSub;                             // +0x1a4
    uint8_t  pad1d8[0x60];
};

class cPlanetModel : public IWin {
 public:
    void MakeRandomWorldPosition();            // 0x00b81780
};

extern "C" cPlanetModel* __stdcall PlanetModel(Vector3* out, float* pos, float a, float b); // 0x00b3d350

class cRaidMgr : public IWin {
 public:
    RaidNode* FUN_00bcb0b0();                  // 0x00bcb0b0
};

class cTribeModeStrategy : public IWin {
 public:
    void* FUN_00b6fa60();                      // 0x00b6fa60
    void  FUN_00cd6980();                      // 0x00cd6980
};

struct RefText {
    IWin* mpRef;
    RefText& operator=(IWin* p);               // 0x00b5f950 (out of line)
};

class cCreature : public IWin {                // cSPCreatureCitizen
 public:
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
    PV(31) PV(32)
    virtual void pv33(void* a, int b, int c);  // +0x84
    uint8_t  pad04[0xbc];                      // +0x04..+0xc0
    cLoco    mLoco_c0;                         // +0xc0
    uint8_t  padc4[0x4e4];                     // +0xc4..+0x5a8
    cM5a8    m5a8;                             // +0x5a8
    uint8_t  pad5ac[0x34];                     // +0x5ac..+0x5e0
    float    m5e0;                             // +0x5e0
    uint8_t  pad5e4[0x568];                    // +0x5e4..+0xb4c
    cOrderMgr* mB4c;                           // +0xb4c
    double FUN_00c0b9c0();                     // 0x00c0b9c0
    char   PutAwayToolExceptFor(int t);        // 0x00c22ca0
    void   SetToolOnAnimEvent(int);            // 0x00c263e0
    void   FUN_00c14750(bool v);               // 0x00c14750
    void   FUN_00c17350(uint32_t a, void* b);  // 0x00c17350
    cTribe* GetTribe();                        // 0x00c22f50
    char   FUN_00c123f0(int anim);             // 0x00c123f0 AnimationFinished
    void   FUN_00c12190(int anim, int a, int b);   // 0x00c12190 PlayAnimation
    void   FUN_00c12310(int anim, int a, int b);   // 0x00c12310 InterruptAnimation
    char   FUN_00c0e0c0(int anim);             // 0x00c0e0c0
    void   MoveToPointAtSpeed(int a, const Vector3* p, float f1, float f2); // 0x00c1c1d0
    void*  FUN_00c22dd0();                     // 0x00c22dd0
    void*  FUN_00c22dc0();                     // 0x00c22dc0
    void   FUN_00c24f40(int a, int b);         // 0x00c24f40 SetCurrentToolEffect
    void   FUN_00c0b970(float f);              // 0x00c0b970
    void   FUN_00c26310(int a);                // 0x00c26310
};

// --- behaviour-state structs ----------------------------------------------
struct HealState {                     // SP::TRIBE_HEAL_SELF_Tick arg 6
    int32_t  m00;                      // +0x00 state
    uint8_t  m04;                      // +0x04
    uint8_t  pad05[3];
    float    m08;                      // +0x08
    cTribe*  m0c;                      // +0x0c
};

struct ToolState {                     // TRIBE_DESTROY_TOOL_Activate arg 6
    int32_t m00;                       // +0x00
    RefText m04;                       // +0x04
    RefText m08;                       // +0x08
    RefText m0c;                       // +0x0c
    Vector3 m10;                       // +0x10
    int32_t m1c;                       // +0x1c
    uint8_t pad20[0xc];                // +0x20..+0x2c
    float   m2c;                       // +0x2c
    int32_t m30;                       // +0x30
};

struct CharState {                     // FUN_00dafc80 arg 6
    int32_t m00;                       // +0x00
    RefText m04;                       // +0x04
    Vector3 m08;                       // +0x08
    uint8_t m14;                       // +0x14
    uint8_t pad15[3];
    int32_t m18;                       // +0x18
};

struct GetState {                      // FUN_00dafc00 arg 6
    RefText m00;                       // +0x00
    uint8_t pad04[0xc];                // +0x04..+0x10
    void*   m10;                       // +0x10
    uint8_t pad14[4];                  // +0x14..+0x18
    int32_t m18;                       // +0x18
};

struct DeactState {                    // TRIBE_GET_TOOL_Deactivate arg 6
    uint8_t pad00[4];                  // +0x00..+0x04
    RefText m04;                       // +0x04
    uint8_t pad08[0xc];                // +0x08..+0x14
    uint8_t m14;                       // +0x14
    uint8_t pad15[3];
    int32_t m18;                       // +0x18
};

// --- intrusive-pointer helpers --------------------------------------------
static void RefClear(void** pp)
{
    void* p = *pp;
    if (p != 0) { *pp = 0; ((IWin*)p)->pv1(); }
}

static void RefAssign(void** pp, void* p)
{
    void* old = *pp;
    if (p != old)
    {
        if (p != 0) ((IWin*)p)->pv0();
        *pp = p;
        if (old != 0) ((IWin*)old)->pv1();
    }
}

void operator delete[](void* p);    // 0x00f47380

struct A7Obj {                       // owner object passed as arg 7
    uint8_t pad00[8];
    cTribe* m08;                     // +0x08
};

// ===========================================================================
// @ 0x00dafc00
void FUN_00dafc00(cCreature* a1, void* a2, void* a3, void* a4, void* a5, GetState* a6)
{
    a1->FUN_00c14750(a1->mLoco_c0.pv62() == 0);
    a1->pv33(0, 0, 0);
    cTribe* t = a1->GetTribe();
    if (t != 0 && a6->m18 >= 0 && a6->m00.mpRef != 0)
        t->FindSpot(a6->m10, a6->m18);
    if (a6 != 0 && a6->m00.mpRef != 0)
        a6->m00.mpRef->pv1();
}

// @ 0x00dafc80
char FUN_00dafc80(cCreature* a1, void* a2, void* a3, void* a4, void* a5,
                  CharState* a6, A7Obj* a7)
{
    if (a6 != 0)
        a6->m04.mpRef = 0;
    void* play = a1->mB4c->mAnim.Play(0x40, 0);
    a6->m00 = 2;
    RefAssign((void**)&a6->m04.mpRef, FUN_00d998d0(play, 0x116d858));
    a6->m18 = -1;
    if (a7 != 0)
    {
        cTribe* o = a7->m08;
        IWin* nb = o != 0 ? o->pv3(0x116d858) : (IWin*)0;
        RefAssign((void**)&a6->m04.mpRef, nb);
    }
    ((cTribe*)a6->m04.mpRef)->FUN_00c9d010();
    Vector3* p = ((cTribe*)a6->m04.mpRef)->m34.pv11();
    a6->m08 = *p;
    a6->m14 = 0;
    a1->pv33(a6->m04.mpRef != 0 ? (void*)&((cTribe*)a6->m04.mpRef)->m120 : 0, 1, 0);
    a1->FUN_00c14750(1);
    return 1;
}

// @ 0x00dafe60
char SP_TRIBE_DESTROY_TOOL_Activate(cCreature* a1, void* a2, void* a3, void* a4, void* a5,
                                    ToolState* a6)
{
    if (a6 != 0)
    {
        a6->m04.mpRef = 0;
        a6->m08.mpRef = 0;
        a6->m0c.mpRef = 0;
    }
    void* play = a1->mB4c->mAnim.Play(0x200000, 0);
    a6->m00 = 5;
    RefAssign((void**)&a6->m08.mpRef, FUN_00d998d0(play, 0x116d858));
    RefAssign((void**)&a6->m04.mpRef, FUN_00d998d0(play, 0xee02c7));
    void* r = FUN_00d998d0(play, 0x4f396a66);
    if (a6->m08.mpRef == 0 && a6->m04.mpRef == 0 && r != 0)
        a6->m04 = (IWin*)((cTribe*)r)->pv43();
    cTribe* s;
    if (a6->m08.mpRef != 0)
    {
        RefAssign((void**)&a6->m0c.mpRef, FUN_00c9d9e0());
        s = (cTribe*)a6->m08.mpRef;
        a1->pv33(&s->m120, 1, 1);
    }
    else
    {
        if (a6->m04.mpRef == 0)
            return 0;
        s = (cTribe*)a6->m04.mpRef;
        RefAssign((void**)&a6->m0c.mpRef, s->pv22());
        a1->pv33(&s->m120, 1, 1);
    }
    Vector3* p = s->m34.pv11();
    a6->m10.x = p->x;
    a6->m10.y = p->y;
    a6->m10.z = p->z;
    a6->m1c = -1;
    a6->m2c = 0.0f;
    a6->m30 = 1;
    RaidNode* node = (RaidNode*)FUN_00bc9b00_3(0x567cb98, (void*)FUN_00da75e0, a1);
    if (node == 0)
    {
        cRaidMgr* mgr = (cRaidMgr*)FUN_00bc9b00_4(0x567cb98, 0xf, 0x18eb4b7, kTribeRaid);
        node = mgr->FUN_00bcb0b0();
        RaidSub* e = &node->mSub;
        if (e != 0)
        {
            e->m2c = 0;
            e->m30 = 0;
        }
        e->m20 = 0;
        e->m18 = 0;
        e->m1c = kF1581370;
        e->m28 = 0;
    }
    a1->mB4c->FUN_00bcb480(node, a1, 0, 0);
    if (a1->mLoco_c0.pv22() == 0 && node->mSub.m20b == 0)
    {
        if (a1->mB4c->mAnim.Play(0, 0x1000000))
            a6->m00 = 1;
    }
    if (a1->FUN_00c22dd0() != (void*)1 && a1->FUN_00c22dc0() != (void*)9)
    {
        a1->FUN_00c24f40(0, -1);
        a1->FUN_00c0b970(0.0f);
        return 1;
    }
    a1->FUN_00c26310(-1);
    a1->FUN_00c0b970(0.0f);
    return 1;
}

// @ 0x00dafd90
void FUN_00dafd90(cCreature* a1, void* a2, void* a3, void* a4, void* a5, DeactState* a6)
{
    a1->FUN_00c14750(0);
    a1->FUN_00c17350(0x55559ef, 0);
    a1->pv33(0, 0, 0);
    if (a6->m04.mpRef != 0)
        ((cTribe*)a6->m04.mpRef)->FUN_00c9d020();
    if (a6->m14 != 0 && FUN_00b5b800() == &DAT_01654c02 && a1->mLoco_c0.pv22() != 0)
    {
        if (((cTribeModeStrategy*)FUN_00cd3440(0x7d7315c8))->FUN_00b6fa60() != 0)
            ((cTribeModeStrategy*)FUN_00cd40b0(0x7d7315c8))->FUN_00cd6980();
    }
    cTribe* t = a1->GetTribe();
    if (t != 0 && a6->m18 >= 0)
        t->FindSpot(((cTribe*)a6->m04.mpRef)->pv22(), a6->m18);
    cTribe* s = (cTribe*)a6->m04.mpRef;
    if (s != 0)
        s->pv1();
}

class cBehaviorMgr : public IWin {             // SP::BehaviorManager()
 public:
    PV(2) PV(3)
    virtual uint32_t pv4();                    // +0x10
};

// @ 0x00daf820
char SP_TRIBE_HEAL_SELF_Tick(cCreature* a1, void* a2, void* a3, void* a4, void* a5, HealState* a6)
{
    if (a1->FUN_00c0b9c0() == 0.0)
        return FUN_00da6270(a1, 5);
    switch (a6->m00)
    {
    case 0:
        if (a1->PutAwayToolExceptFor(0) != 0)
        {
            a1->SetToolOnAnimEvent(0);
            return 1;
        }
        {
            cTribe* t = a6->m0c;
            Vector3 v;
            float* ps = t->m120.pv11();
            float* pw = a1->mLoco_c0.pv11();
            v.x = pw[0] - ps[0];
            v.y = pw[1] - ps[1];
            v.z = pw[2] - ps[2];
            float r = (float)t->pv24();
            if ((v.z * v.z + v.y * v.y) + v.x * v.x <= r * r)
            {
                a1->mLoco_c0.pv59();
                a6->m00 = 1;
                return 1;
            }
            PlanetModel(&v, t->m120.pv11(), kTwo,
                        (float)t->pv24())->MakeRandomWorldPosition();
            a1->MoveToPointAtSpeed(2, &v, 1.0f, kTwo);
            a6->m00 = 1;
            return 1;
        }
    case 1:
        if (a1->mLoco_c0.FUN_00c42e20() == 0)
            return 1;
        {
            float t1 = (float)(a1->m5a8.pv22() * kDot01);
            void* tool = a6->m0c->GetToolOfType(9);
            float    def;
            uint32_t id;
            if (tool != 0) { def = kFive; id = 0xf3faac05u; }
            else           { def = kTwo;  id = 0xa1b01538u; }
            a6->m08 = (float)(GetPropFloat(g_pPropertyMgr, id, def) * t1 * kDot001);
        }
        a1->FUN_00c12310(0x2796b22, -1, 0);
        a1->FUN_00c12190(0x2796b25, 1, -1);
        a6->m00 = 2;
        a6->m04 = 1;
        return 1;
    case 2:
        if (a1->FUN_00c123f0(0x2796b22) == 0)
            return 1;
        if (a1->FUN_00c0e0c0(0x2796b25) == 0)
            a1->FUN_00c12190(0x2796b25, 1, -1);
        a6->m00 = 3;
        return 1;
    case 3:
        {
            uint32_t sv = ((cBehaviorMgr*)FUN_00b3d260())->pv4();
            a1->m5a8.PartialRepair((float)((double)sv * a6->m08));
            float  hp = a1->m5e0;
            double mx = a1->m5a8.pv22();
            if (hp >= mx)
            {
                a1->FUN_00c12190(0x2796b28, 1, -1);
                a6->m00 = 4;
                a6->m04 = 0;
            }
        }
        return 1;
    case 4:
        if (a1->FUN_00c123f0(0x2796b28) == 0)
            return 1;
        return FUN_00da6270(a1, 5);
    }
    return 1;
}