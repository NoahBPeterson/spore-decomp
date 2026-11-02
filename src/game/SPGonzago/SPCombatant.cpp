// src/game/SPGonzago/SPCombatant.cpp -- migrated from slice(s) s00bfcc80, s00bfbbf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCombatant.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cCombatant.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned GetCurrentGameMode();          // 0xb5b800
extern void  FUN_00b69930(void* obj, float value, int extra);        // 0x00b69930, cdecl, 3 args
extern float FUN_00b685e0(void* obj);                                // 0x00b685e0, cdecl
extern void  EA_IO_WriteUint32(void* s, const void* data, int n, int f);   // 0x0093aa70
extern void  EA_IO_ReadInt32(void* s, void* data, int n, int f);           // 0x0093a780
extern double F_eec5c0(void* obj);                                   // 0x00eec5c0, cdecl
extern bool  F_b673c0(void* obj);                                    // 0x00b673c0, cdecl
extern bool  F_b18850(void* obj);                                    // 0x00b18850, cdecl
extern bool  F_b187b0(void* obj);                                    // 0x00b187b0, cdecl
extern bool  F_b18810(void* obj);                                    // 0x00b18810, cdecl
extern bool  F_b187d0(void* obj);                                    // 0x00b187d0, cdecl
extern bool  F_b18830(void* obj);                                    // 0x00b18830, cdecl
extern bool  F_b18760(void* obj);                                    // 0x00b18760, cdecl
extern bool  F_b18870(void* obj);                                    // 0x00b18870, cdecl
extern void* F_bc96a0(void* self, unsigned a, int b);                // 0x00bc96a0, thiscall, ret 8
extern void* F_d999d0(void* obj);                                    // 0x00d999d0, cdecl
extern int   GetPlayerEmpireID();                                    // 0x01021090
extern void* GetUFOSimulator();                                      // 0x00ffbe50
extern float g_defPoint[3];                                          // 0x0168cb6c, 0x0168cb70, 0x0168cb74
#include <math.h>
#include <stddef.h>

// ---- items of slice s00bfbbf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
extern unsigned GetCurrentGameMode();          // 0xb5b800
extern void  FUN_00b69930(void* obj, float value, int extra);        // 0x00b69930, cdecl, 3 args
extern float FUN_00b685e0(void* obj);                                // 0x00b685e0, cdecl
extern void  EA_IO_WriteUint32(void* s, const void* data, int n, int f);   // 0x0093aa70
extern void  EA_IO_ReadInt32(void* s, void* data, int n, int f);           // 0x0093a780
struct Opaque {                                // __thiscall callees (bodies elsewhere)
    int   F_b18530();                          // 0x00b18530
    bool  F_f25330();                          // 0x00f25330
    int   F_f3f950(void* arg);                 // 0x00f3f950, ret 4
    void* F_bddd10();                          // 0x00bddd10
};
extern double F_eec5c0(void* obj);                                   // 0x00eec5c0, cdecl
extern bool  F_b673c0(void* obj);                                    // 0x00b673c0, cdecl
extern bool  F_b18850(void* obj);                                    // 0x00b18850, cdecl
extern bool  F_b187b0(void* obj);                                    // 0x00b187b0, cdecl
extern bool  F_b18810(void* obj);                                    // 0x00b18810, cdecl
extern bool  F_b187d0(void* obj);                                    // 0x00b187d0, cdecl
extern bool  F_b18830(void* obj);                                    // 0x00b18830, cdecl
extern bool  F_b18760(void* obj);                                    // 0x00b18760, cdecl
extern bool  F_b18870(void* obj);                                    // 0x00b18870, cdecl
extern void* F_bc96a0(void* self, unsigned a, int b);                // 0x00bc96a0, thiscall, ret 8
extern void* F_d999d0(void* obj);                                    // 0x00d999d0, cdecl
extern int   GetPlayerEmpireID();                                    // 0x01021090
extern void* GetUFOSimulator();                                      // 0x00ffbe50
extern float g_defPoint[3];                                          // 0x0168cb6c, 0x0168cb70, 0x0168cb74
struct Timer {
    char body[0x20];                                   // +0x000 (only the head is addressed)
    bool IsRunning();                                  // 0x00feba90
    unsigned long long GetElapsedTime();               // 0x00bc3190, edx:eax
    void Restart();                                    // 0x00bc3130
    void Stop();                                       // 0x00bc3110
};
struct VarListSerializer {
    char body[0xa00];
    void Init(void* owner, void* table, int key);      // 0x00692f90 (ctor), ret 0xc
    void Serialize(void* stream);                      // 0x00692900, ret 4
    void Read(void* stream);                           // 0x00693e10, ret 4
};
struct VtObj {
    void** vt;                                         // +0x000
    bool NodePresent();                                // 0x00bfc3a0
    bool NodePresentArg(int unused);                   // 0x00bfc3d0
    float NodeValue();                                 // 0x00bfc400
    bool GateCheck(VtObj* other);                      // 0x00bfc7a0
    void GameDataCenter(Vec3* out);                    // 0x00bfc8a0
    bool TrikeCheck(int arg);                          // 0x00bfc900
};
static __forceinline void ReleaseSlotPtr(void** slot)
{
    void* p = *slot;
    *slot = 0;
    if (p)
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
}
struct Sim {
    void** vt;                                         // +0x000
    char pad_004[0x028 - 0x004];
    void* p_028;                                       // +0x028
    float m_02c;                                       // +0x02c
    void* p_030;                                       // +0x030
    int   m_034;                                       // +0x034
    float m_038;                                       // +0x038
    int   m_03c;                                       // +0x03c
    char pad_040[0x044 - 0x040];
    void* p_044;                                       // +0x044
    void* p_048;                                       // +0x048
    char pad_04c[0x074 - 0x04c];
    float m_074;                                       // +0x074
    float m_078;                                       // +0x078
    float m_07c;                                       // +0x07c
    char pad_080[0x084 - 0x080];
    char* p_084;                                       // +0x084
    char* p_088;                                       // +0x088
    char pad_08c[0x098 - 0x08c];
    Timer timer_98;                                    // +0x098
    unsigned int m_0b8;                                // +0x0b8
    void* arr_bc[3];                                   // +0x0bc
    void NodeApply(int value);                         // 0x00bfc430
    float NodeRatio();                                 // 0x00bfc490
    void CombatantWrite(VtObj* stream);                // 0x00bfc4a0
    void CombatantRead(VtObj* stream);                 // 0x00bfc540
    int TimedExpired();                                // 0x00bfc600
    void TimedAdd(unsigned int amount);                // 0x00bfc640
    void TimedStop();                                  // 0x00bfc6a0
    void ReleaseSlots();                               // 0x00bfc720
    void DetachSlot();                                 // 0x00bfcac0
    void DetachOther();                                // 0x00bfcae0
    double SimValue();                                 // 0x00bfcb10
    bool TakeDefaultPoint(Vec3* out);                  // 0x00bfcb90
    void TickSlotArray();                              // 0x00bfcc00
    bool EntryAvailable(int id);                       // 0x00bfcc40
};
struct Node0x14 {
    void** vt;                                         // +0x000
    bool  Fn104fff0();                                 // 0x0104fff0, thiscall, no stack args
    float Fn104be30();                                 // 0x0104be30, thiscall, no stack args
};
struct AnimObj {                                       // 0x00bfc900 target object
    char pad_000[0xb4c];
    void* p_b4c;                                       // +0xb4c
    char pad_b50[0x0b58 - 0x0b50];
    unsigned int flags;                                // +0xb58
};
// ---- items of slice s00bfbbf0 end

// ---- items of slice s00bfcc80 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 1)
#pragma pack(pop)
struct RcMap    { void* mRoot; void NukeSubtree(void* key); };  // 0x009A9600-style thiscall
struct Combatant {
    void**   vftable;                                           // +0x00
    uint32_t pad04;                                             // +0x04
    unsigned char mIgnoreCombatLineTest;                        // +0x08
    unsigned char mLineTestIgnoresFriendlies;                   // +0x09
    unsigned char pad0a[2];                                     // +0x0a
    RcMap    mMap0c;                                            // +0x0c intrusive hostile tree
    void*    mDamageState10;                                    // +0x10 (intrusive list head, points at itself)
    void*    mList14;                                           // +0x14
    void*    mList18;                                           // +0x18
    unsigned char mByte1c;                                      // +0x1c
    unsigned char pad1d[3];                                     // +0x1d
    uint32_t mField20;                                          // +0x20
    void*    mActiveTarget24;                                   // +0x24
    void*    mNextTarget28;                                     // +0x28
    float    mField2c;                                          // +0x2c
    void*    mField30;                                          // +0x30
    uint32_t mField34;                                          // +0x34
    float    mHealth38;                                         // +0x38
    uint32_t mDamageState3c;                                    // +0x3c
    float    mField40;                                          // +0x40
    void*    mField44;                                          // +0x44
    void*    mField48;                                          // +0x48
    float    mField4c;                                          // +0x4c
    float    mField50;                                          // +0x50
    float    mField54;                                          // +0x54
    void*    mHostileBegin58;                                   // +0x58
    void*    mHostileEnd5c;                                     // +0x5c
    void*    mHostileCap60;                                     // +0x60
    uint32_t pad64[2];                                          // +0x64
    unsigned char mStunFlag6c;                                  // +0x6c
    unsigned char pad6d[3];                                     // +0x6d
    uint32_t mStunTimer70;                                      // +0x70
    float    mField74;                                          // +0x74
    float    mField78;                                          // +0x78
    float    mField7c;                                          // +0x7c
    unsigned char mByte80;                                      // +0x80
    unsigned char mByte81;                                      // +0x81
    unsigned char pad82[2];                                     // +0x82
    void*    mVec84Begin;                                       // +0x84
    void*    mVec84End;                                         // +0x88
    void*    mVec84Cap;                                         // +0x8c
    uint32_t pad90[2];                                          // +0x90
    uint32_t mTimer98[9];                                       // +0x98 (cGonzagoTimer, 0x24 bytes)
    void*    mSlotsBc[3];                                       // +0xbc

    Combatant();                                                // 0x00BFD4E0
    ~Combatant();                                               // 0x00BFCD00
    void  TakeHit(float amount, void* pos, int type, void* flags, void* source); // 0x00BFCDD0
    void  PartialRepair(float amount);                          // 0x00BFD1A0
};
struct Vector3 { float x, y, z; };                              // 0x0c
struct Matrix3 { float m[9]; };                                 // 0x24 (column-major rows)
struct Placement {
    unsigned short flags;                                       // +0x00
    short          count;                                       // +0x02
    Vector3        pos;                                         // +0x04
    float          scale;                                       // +0x10
    Matrix3        basis;                                       // +0x14
};
struct OrientObject {
    void** vftable;                                             // +0x00
    unsigned char pad04[0x2c];                                  // +0x04..+0x30
    void*  mEffectHandle30;                                     // +0x30
};
struct RcHandle {                                               // effect handle, Apply at vtable +0x18
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
    virtual void Apply(Placement* p);                           // vtable +0x18
};
struct HostileEntry {
    void*    vftable;                                           // +0x00
    uint32_t mRefCount4;                                        // +0x04
    uint32_t mField08;                                          // +0x08
    uint32_t mField0c;                                          // +0x0c
    uint32_t mField10;                                          // +0x10
    uint32_t mField14;                                          // +0x14
    unsigned char mByte18;                                      // +0x18
    uint32_t mField1c;                                          // +0x1c
    uint32_t mField20;                                          // +0x20
    uint32_t pad24;                                             // +0x24
};
void*  EffectsManagerPtr();                                     // 0x0067DDD0
void*  MessageServer();                                         // 0x0067DCC0
char   FUN_00bfc900(void* a);                                   // 0x00BFC900
char   FUN_00b673c0(void* a);                                   // 0x00B673C0
void   FUN_00b69930(void* a, float f);                          // 0x00B69930
void   operator_delete__(void* p);                              // 0x00F47380
void*  GetCurrentGameMode_s00bf_cc80();                                    // 0x00B5B800
void*  SpaceGameGet();                                          // 0x01002BD0
void*  GetPlayerInventory(void* game);                          // 0x00A1AD60
int    GetToolFromToolID(void* inv, void* id);                  // 0x00FF3D40
char   FUN_0104bde0(void* tool);                                // 0x0104BDE0
float  FUN_0104bdc0(void* tool);                                // 0x0104BDC0
char   TimerIsRunning(void* t);                                 // 0x00FEBA90
int    TimerGetElapsedTime(void* t);                            // 0x00BC3190
void*  FUN_0108db30(void* sim);                                 // 0x0108DB30
void*  FUN_00d61ce0(void* out, unsigned a, void* b, void* c);   // 0x00D61CE0
void   FUN_00bfca80(void* o);                                   // 0x00BFCA80
void*  FUN_00b18530(void* gd);                                  // 0x00B18530
char   FUN_00f25370(void* gd);                                  // 0x00F25370
void   FUN_00f24b30(void* o);                                   // 0x00F24B30
void   SlotMessage_Construct(void* m, int z);                   // 0x00421C80
void   SlotMessage_Destruct(void* m);                           // 0x00421CF0
void*  PlanetModelGet(void* out, void* model);                  // 0x00B3D350
void   OrthogonalVector(Vector3* out, const Vector3* in);       // 0x006985B0
Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up); // 0x0069B440
void   Matrix3_Assign(void* self, const void* src);             // 0x0041CB40
struct RcSlot {                                                 // a released effect handle
    virtual void _v0();
    virtual void Release4();                                    // vtable +0x04
virtual void _v2();
virtual void _v3();
    virtual char IsActive();                                    // vtable +0x10
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
virtual void _v9();
virtual void _v10();
virtual void _v11();
virtual void _v12();
virtual void _v13();
virtual void _v14();
virtual void _v15();
virtual void _v16();
virtual void _v17();
virtual void _v18();
virtual void _v19();
virtual void _v20();
virtual void _v21();
virtual void _v22();
virtual void _v23();
virtual void _v24();
    virtual void Release64();                                   // vtable +0x64
};
struct RcEffectMgr {                                            // effect manager (SP::EffectsManager)
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
virtual void _v9();
virtual void _v10();
    virtual char AddSlot(unsigned id, int zero, void** slot);   // vtable +0x2c
};
struct RcTimer {                                                // SP::cGonzagoTimer
    void Dtor();                                                // 0x00B638B0
    void Ctor();                                                // 0x00B63890
};
struct RcVecStore { uint32_t mElemCount; };                     // SGI vector header word before begin
struct CombatantListHead {                                      // the intrusive list head embedded at cCombatant+0x10
    void*    mNext;                                             // +0x00
    void*    mPrev;                                             // +0x04
    void*    mLive;                                             // +0x08
    uint32_t mField0c;                                          // +0x0c (mByte1c plus padding, written as a dword)
};
struct RcMsg {                                                  // MessageServer
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
    virtual void _v4();
    virtual void Send(unsigned id, void* msg, unsigned flags);   // vtable +0x14
};
struct Msg5 {                                               // MessageBasicRC<5>-shaped message
    void** vftable;                                         // +0x00
    uint32_t mField04;                                      // +0x04
    void*  mData08;                                         // +0x08
    uint32_t mField0c;                                      // +0x0c
    uint32_t mField10;                                      // +0x10
};
struct SubFlagsView {                                       // opaque sub-object; its state flags word sits at +0xb58
    uint32_t padB58[0x2d6];                                 // +0x00..+0xb58
    uint32_t mFlagsB58;                                     // +0xb58
};
typedef void* (*GetAccessor)(void*);
typedef void* (*GetAccessor2)(void*, void*);
typedef void* (*GetAccessor3)(void*, void*, void*);
typedef void  (*GetHandle)(void*);
typedef char  (*GetChar)(void*);
typedef float (*GetFloat)(void*);
typedef void* (*GetVector)(void*);
// ---- items of slice s00bfcc80 end

// @ 0x00bfc3a0
bool VtObj::NodePresent()
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return false;
    return ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104fff0();
}

// @ 0x00bfc3d0
bool VtObj::NodePresentArg(int unused)
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return false;
    return ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104fff0();
}

// @ 0x00bfc400
float VtObj::NodeValue()
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return 0.0f;
    return ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104be30();
}

// @ 0x00bfc430
void Sim::NodeApply(int value)
{
    void* p = ((void* (__thiscall*)(void*, int))this->vt[3])(this, value);
    float f = FUN_00b685e0(p);
    FUN_00b69930(((void* (__thiscall*)(void*, float))this->vt[3])(this, f), f, value);
}

// @ 0x00bfc490
float Sim::NodeRatio()
{
    return this->m_038 / ((float (__thiscall*)(void*))this->vt[22])(this);
}

// @ 0x00bfc4a0
void Sim::CombatantWrite(VtObj* stream)
{
    unsigned int value = 0x013f94d4;
    void* sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    void* writer = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_WriteUint32(writer, &value, 1, 0);
    value = (unsigned int)this->m_034;
    sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    writer = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_WriteUint32(writer, &value, 1, 0);
    VarListSerializer s;
    s.Init(this, (void*)0x01570858, 0x01a80d26);
    s.Serialize(stream);
}

// @ 0x00bfc540
void Sim::CombatantRead(VtObj* stream)
{
    int first = 0;
    int second = 0;
    void* sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    void* reader = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_ReadInt32(reader, &first, 1, 0);
    sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    reader = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_ReadInt32(reader, &second, 1, 0);
    this->m_034 = second;
    VarListSerializer s;
    s.Init(this, (void*)0x01570858, 0x01a80d26);
    s.Read(stream);
}

// @ 0x00bfc600
int Sim::TimedExpired()
{
    if (this->timer_98.IsRunning()) {
        unsigned long long elapsed = this->timer_98.GetElapsedTime();
        if (elapsed < (unsigned long long)this->m_0b8)
            return 1;
    }
    return 0;
}

// @ 0x00bfc640
void Sim::TimedAdd(unsigned int amount)
{
    if (this->timer_98.IsRunning()) {
        unsigned int cap = this->m_0b8;
        unsigned long long elapsed = this->timer_98.GetElapsedTime();
        if (elapsed < (unsigned long long)cap) {
            this->m_0b8 = cap + amount;
            return;
        }
    }
    this->m_0b8 = amount;
    this->timer_98.Restart();
}

// @ 0x00bfc6a0
void Sim::TimedStop()
{
    this->m_0b8 = 0;
    this->timer_98.Stop();
}

// @ 0x00bfc720
void Sim::ReleaseSlots()
{
    if (this->p_028) {
        void* p = this->p_028;
        this->p_028 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
    if (this->p_030) {
        void* p = this->p_030;
        this->p_030 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
    }
    if (this->p_044) {
        void* p = this->p_044;
        this->p_044 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
    if (this->p_048) {
        void* p = this->p_048;
        this->p_048 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
    for (int i = 0; i < 3; i++) {
        if (this->arr_bc[i])
            ReleaseSlotPtr(&this->arr_bc[i]);
    }
}

// @ 0x00bfc7a0
bool VtObj::GateCheck(VtObj* other)
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return false;
    float reach = ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104be30();
    if (reach != -1.0f) {
        VtObj* mine = ((VtObj* (__thiscall*)(void*))this->vt[2])(this);
        VtObj* theirs = ((VtObj* (__thiscall*)(void*))other->vt[2])(other);
        Vec3* pa = ((Vec3* (__thiscall*)(void*))mine->vt[11])(mine);
        Vec3* pb = ((Vec3* (__thiscall*)(void*))theirs->vt[11])(theirs);
        float dx = pb->x - pa->x;
        float dy = pb->y - pa->y;
        float dz = pb->z - pa->z;
        float dist = sqrtf(dx * dx + dz * dz + dy * dy);
        float limit = ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104be30();
        return dist <= limit;
    }
    return true;
}

// @ 0x00bfc8a0
void VtObj::GameDataCenter(Vec3* out)
{
    float bounds[6];
    VtObj* owner = ((VtObj* (__thiscall*)(void*))this->vt[2])(this);
    const float* src = (const float*)((float* (__thiscall*)(void*, float*))owner->vt[27])(owner, bounds);
    float x = (src[0] + src[3]) * 0.5f;
    float y = (src[4] + src[1]) * 0.5f;
    float z = (src[5] + src[2]) * 0.5f;
    out->x = x;
    out->y = y;
    out->z = z;
}

// @ 0x00bfc900
bool VtObj::TrikeCheck(int arg)
{
    switch (GetCurrentGameMode()) {
    case 0x1654c01:
    case 0x1654c10: {
        if (this == 0)
            return false;
        AnimObj* o = (AnimObj*)((void* (__thiscall*)(void*, int))this->vt[3])(this, 0xce9f6639);
        if (o == 0)
            return false;
        if (o->flags & 0x200)
            return true;
        if (o->flags & 0x100)
            return true;
        void* anim = F_bc96a0((char*)o->p_b4c + 8, 0x400, 0);
        if (anim == 0)
            return false;
        AnimObj* w = (AnimObj*)F_d999d0(anim);
        if (w == 0)
            return false;
        if (w->flags & 0x100)
            return true;
        if (w->flags & 0x200)
            return true;
        return false;
    }
    case 0x1654c02:
        if (F_b18850(this))
            return true;
        if (F_b187b0(this))
            return true;
        return false;
    case 0x1654c04:
        if (F_b18810(this))
            return true;
        if (F_b187d0(this))
            return true;
        if (F_b18830(this))
            return true;
        if (F_b18760(this))
            return true;
        return false;
    case 0x1654c05: {
        if (this == 0)
            return false;
        AnimObj* o = (AnimObj*)((void* (__thiscall*)(void*, void*))this->vt[3])(this, (void*)0x013f94d4);
        if (o == 0)
            return false;
        if (!F_b187d0(this) && !F_b18870(this) && !F_b18760(this))
            return false;
        int empire = GetPlayerEmpireID();
        if (arg != empire) {
            if (o != (AnimObj*)((Opaque*)GetUFOSimulator())->F_bddd10())
                return false;
        }
        return true;
    }
    }
    return false;
}

// @ 0x00bfca80
void TrikeNotify(void* obj, void* owner, int extra)
{
    if (((VtObj*)obj)->TrikeCheck((int)owner) && F_b673c0(obj))
        FUN_00b69930(obj, FUN_00b685e0(obj), extra);
}

// @ 0x00bfcac0
void Sim::DetachSlot()
{
    void* p = this->p_028;
    this->m_03c = -1;
    if (p) {
        this->p_028 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
}

// @ 0x00bfcae0
void Sim::DetachOther()
{
    if (this->p_030) {
        void* p = this->p_030;
        ((void (__thiscall*)(void*, int))((VtObj*)p)->vt[3])(p, 0);
        p = this->p_030;
        if (p) {
            this->p_030 = 0;
            ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
        }
    }
}

// @ 0x00bfcb10
double Sim::SimValue()
{
    float saved = this->m_02c;
    if (GetCurrentGameMode() == 0x1654c10) {
        int mode = *(int*)(*(char**)0x016c7aa4 + 0xcc);
        if (mode == 2) {
            void* o = ((void* (__thiscall*)(void*))this->vt[3])(this);
            int g = ((Opaque*)o)->F_b18530();
            if (!g)
                return saved;
            if (!((Opaque*)g)->F_f25330())
                return saved;
            if (!((Opaque*)*(void**)(*(char**)0x016c7aa4 + 0x74))->F_f3f950(o))
                return saved;
            return F_eec5c0(o);
        }
        if (mode == 1)
            return this->m_038;
    }
    return saved;
}

// @ 0x00bfcb90
bool Sim::TakeDefaultPoint(Vec3* out)
{
    if (this->m_074 != g_defPoint[0] || this->m_078 != g_defPoint[1] || this->m_07c != g_defPoint[2]) {
        out->x = this->m_074;
        out->y = this->m_078;
        out->z = this->m_07c;
        this->m_074 = g_defPoint[0];
        this->m_078 = g_defPoint[1];
        this->m_07c = g_defPoint[2];
        return true;
    }
    return false;
}

// @ 0x00bfcc00
void Sim::TickSlotArray()
{
    for (int i = 0; i < 3; i++) {
        void* p = this->arr_bc[i];
        if (p) {
            if (!((bool (__thiscall*)(void*))((VtObj*)p)->vt[4])(p)) {
                p = this->arr_bc[i];
                this->arr_bc[i] = 0;
                if (p)
                    ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
            }
        }
    }
}

// @ 0x00bfcc40
bool Sim::EntryAvailable(int id)
{
    for (char* p = this->p_084; p != this->p_088; p += 0x28) {
        if (*(int*)(p + 0x20) == id) {
            unsigned long long elapsed = ((Timer*)p)->GetElapsedTime();
            if (elapsed < 0x4e20)
                return true;
            return false;
        }
    }
    return false;
}

// @ 0x00bfcc80
void* __fastcall FUN_00bfcc80(Combatant* self, int, unsigned param_2)
{
    unsigned i = 0;
    void** slot = self->mSlotsBc;
    while (*slot != 0 && ((RcSlot*)*slot)->IsActive()) {
        ++i;
        ++slot;
        if (i > 2)
            return 0;
    }
    if (i > 2)
        return 0;
    RcEffectMgr* mgr = (RcEffectMgr*)EffectsManagerPtr();
    void** cur = self->mSlotsBc + i;
    RcSlot* old = (RcSlot*)*cur;
    if (old != 0) {
        *cur = 0;
        old->Release4();
    }
    if (mgr->AddSlot(param_2, 0, cur) == 0)
        return 0;
    return *cur;
}

// @ 0x00bfcd00
void __fastcall Combatant_dtor(Combatant* self)
{
    self->vftable = (void**)0x14698f0;
    // The three effect handles at +0xbc..+0xc8, released back-to-front.
    void** slot = self->mSlotsBc + 3;
    int n = 2;
    do {
        --slot;
        void* h = *slot;
        if (h != 0)
            ((RcSlot*)h)->Release4();
        --n;
    } while (n >= 0);
    ((RcTimer*)((char*)self + 0x98))->Dtor();
    // The mVec84 vector of 0x28-byte cGonzagoTimer elements.
    char* end = (char*)self->mVec84End;
    char* begin = (char*)self->mVec84Begin;
    while (begin < end) {
        ((RcTimer*)begin)->Dtor();
        begin += 0x28;
    }
    if (self->mVec84Begin != 0 && ((RcVecStore*)self->mVec84Begin)[-1].mElemCount != 0)
        operator_delete__(self->mVec84Begin);
    if (self->mHostileBegin58 != 0 && ((RcVecStore*)self->mHostileBegin58)[-1].mElemCount != 0)
        operator_delete__(self->mHostileBegin58);
    void* p;
    if ((p = self->mField48) != 0)
        ((RcSlot*)p)->Release64();
    if ((p = self->mField44) != 0)
        ((RcSlot*)p)->Release64();
    if ((p = self->mField30) != 0)
        ((RcSlot*)p)->Release4();
    if ((p = self->mNextTarget28) != 0)
        ((RcSlot*)p)->Release64();
    self->mMap0c.NukeSubtree(self->mList18);
}

// @ 0x00bfcdd0
void __fastcall Combatant_TakeHit(Combatant* self, int, float amount, void* source, int type, Vector3* dir, void* flags)
{
    void* prev = self->mNextTarget28;
    if (source != prev) {
        if (source != 0)
            ((GetHandle)(*(void***)source)[0x18])(source);          // vtable +0x60
        self->mNextTarget28 = source;
        if (prev != 0)
            ((GetHandle)(*(void***)prev)[0x19])(prev);              // vtable +0x64
    }
    if (source != 0) {
        void* o = ((GetAccessor)(*(void***)source)[3])(source);     // vtable +0x0c
        char destroyed = ((GetChar)(*(void***)o)[0xb])(o);          // +0x2c
        if (destroyed == 0) {
            if (GetCurrentGameMode_s00bf_cc80() == (void*)0x1654c05) {
                void* inv = GetPlayerInventory(SpaceGameGet());
                if (((char (*)(void*, void*))(*(void***)inv)[0x1d])(inv, (void*)0x168d064)) {
                    int tool = GetToolFromToolID(GetPlayerInventory(SpaceGameGet()), (void*)0x168d064);
                    int id = FUN_0104bde0((void*)(char*)tool);
                    if (id != -1 && TimerIsRunning((void*)((char*)tool + 0x88))) {
                        int elapsed = TimerGetElapsedTime((void*)((char*)tool + 0x88));
                        if (id != elapsed && id - elapsed > 0) {
                            void* sim = FUN_0108db30(GetUFOSimulator());
                            int emp = ((int (*)(void*))(*(void***)source)[4])(source);  // +0x10
                            if (emp != GetPlayerEmpireID()) {
                                void* key = ((GetAccessor)(*(void***)source)[4])(source);
                                void* hit = FUN_00d61ce0(&key, (unsigned)(uintptr_t)sim, sim, &key);
                                if (*(void**)hit == sim)
                                    goto after_source;
                            }
                            amount = FUN_0104bdc0((void*)(char*)tool) * amount;
                        }
                    }
                }
            }
        } else {
            source = 0;
        }
    }
after_source:
    if (self->mByte80 != 0)
        return;
    if (GetCurrentGameMode_s00bf_cc80() == (void*)0x1654c10) {
        void* gd = ((GetAccessor2)(*(void***)self)[0x17])(self, (void*)0x17f243b);   // +0x5c
        if (gd != 0) {
            void* d = FUN_00b18530(gd);
            if (d != 0 && !FUN_00f25370(d))
                return;
        }
    }
    if (self->mField34 == 2)
        return;

    if (GetCurrentGameMode_s00bf_cc80() != (void*)0x1654c05 || type != 10) {
        self->mDamageState3c = (uint32_t)(uintptr_t)source;
        self->mField74 = dir->x;
        self->mField78 = dir->y;
        self->mField7c = dir->z;
    }

    switch (type) {
    case 3: case 4: case 0xc: case 0xe: case 0xf: case 0x10:
        return;
    }

    int active = 0;
    {
        void* o = ((GetAccessor)(*(void***)self)[3])(self);
        if (o != 0) {
            void* sub = ((GetAccessor2)(*(void***)o)[3])(o, (void*)0xd0036e08);
            if (sub != 0) {
                unsigned v = ((SubFlagsView*)sub)->mFlagsB58;
                if ((v >> 9) & 1)
                    active = (v & 0x2000) ? 1 : 0;
            }
        }
    }
    FUN_00bfca80(((GetAccessor3)(*(void***)self)[3])(self, source, (void*)(uintptr_t)active));
    if (type == 10) {
        if (self->mField34 != 2)
            self->mHealth38 += amount;
        float mx = ((GetFloat)(*(void***)self)[0x16])(self);         // +0x58
        if (self->mHealth38 <= mx)
            return;
        self->mHealth38 = ((GetFloat)(*(void***)self)[0x16])(self);
        return;
    }
    if (type == 0xb)
        return;
    float h = self->mHealth38 - amount;
    self->mHealth38 = h;
    if (h < *(float*)0x14698e8) {
        self->mHealth38 = 0.0f;
        self->mField34 = 2;
        Msg5 msg;
        SlotMessage_Construct(&msg, 0);
        msg.mData08 = self;
        msg.mField10 = (uint32_t)(uintptr_t)source;
        ((RcMsg*)MessageServer())->Send(0x1622184, &msg, 0);
        FUN_00f24b30(((GetAccessor2)(*(void***)self)[3])(self, (void*)(uintptr_t)type));
        SlotMessage_Destruct(&msg);
    }
}

// @ 0x00bfd1a0
void __fastcall Combatant_PartialRepair(Combatant* self, int, float amount)
{
    if (!(0.0f < amount))
        return;
    if (self->mHealth38 < ((GetFloat)(*(void***)self)[0x16])(self)) {
        void* a = ((GetAccessor)(*(void***)self)[3])(self);
        void* b = ((GetAccessor)(*(void***)a)[0x13])(a);            // +0x4c
        void* c = ((GetAccessor)(*(void***)self)[3])(self);
        if (FUN_00bfc900(b) && FUN_00b673c0(c)) {
            float f = FUN_00b685e0(c);
            FUN_00b69930(c, f);
        }
    }
    int oldState = self->mField34;
    self->mField34 = 0;
    self->mHealth38 += amount;
    float mx = ((GetFloat)(*(void***)self)[0x16])(self);
    if (self->mHealth38 > mx)
        self->mHealth38 = mx;
    if (oldState != self->mField34) {
        Msg5 msg;
        msg.vftable = (void**)0x13eb90c;
        msg.mField04 = 0;
        msg.mData08 = self;
        msg.vftable = (void**)0x13eb844;
        msg.mField0c = 0;
        ((RcMsg*)MessageServer())->Send(0x1622184, &msg, 0);
        SlotMessage_Destruct(&msg);
    }
}

// @ 0x00bfd2b0
void __fastcall FUN_00bfd2b0(OrientObject* self)
{
    if (self->mEffectHandle30 == 0)
        return;
    Placement p;
    p.flags = 0;
    p.count = 0;
    p.pos.x = *(float*)0x168d174;
    p.pos.y = *(float*)0x168d178;
    p.pos.z = *(float*)0x168d17c;
    p.scale = 1.0f;
    Matrix3_Assign(&p.basis, (const void*)0x168d150);

    void* a = ((GetAccessor)(*(void***)self)[2])(self);
    p.pos = *((Vector3*)((GetVector)(*(void***)a)[0xb])(a));
    p.flags |= 4;
    ++p.count;

    a = ((GetAccessor)(*(void***)self)[2])(self);
    Vector3* dir = (Vector3*)((GetVector)(*(void***)a)[0xb])(a);
    Vector3 normal;
    PlanetModelGet(&normal, dir);
    Vector3 side;
    OrthogonalVector(&side, &normal);
    Matrix3 basis;
    Matrix3FromFacingAndUp(&basis, &side, &normal);
    for (int i = 0; i < 9; ++i)
        p.basis.m[i] = basis.m[i];
    p.flags |= 2;
    ++p.count;

    a = ((GetAccessor)(*(void***)self)[2])(self);
    p.scale = ((GetFloat)(*(void***)a)[0x1d])(a);
    ++p.count;

    ((RcHandle*)self->mEffectHandle30)->Apply(&p);
}

// @ 0x00bfd3e0
HostileEntry* __fastcall FUN_00bfd3e0(HostileEntry* self, int, const HostileEntry* src)
{
    self->vftable = (void*)0x1465d54;
    self->mRefCount4 = 0;
    self->mField08 = src->mField08;
    self->mField0c = src->mField0c;
    self->mField10 = src->mField10;
    self->mField14 = src->mField14;
    self->mByte18 = src->mByte18;
    self->mField1c = src->mField1c;
    self->vftable = (void*)0x1464450;
    self->mField20 = src->mField20;
    return self;
}

// @ 0x00bfd430
void FUN_00bfd430(const HostileEntry* first, const HostileEntry* last, HostileEntry* out)
{
    if (out != 0 || first != last) {
        for (; first != last; first += 1, out += 1) {
            if (out != 0) {
                out->vftable = (void*)0x1465d54;
                out->mRefCount4 = 0;
                out->mField08 = first->mField08;
                out->mField0c = first->mField0c;
                out->mField10 = first->mField10;
                out->mField14 = first->mField14;
                out->mByte18 = first->mByte18;
                out->mField1c = first->mField1c;
                out->vftable = (void*)0x1464450;
                out->mField20 = first->mField20;
            }
        }
    }
}

// @ 0x00bfd490
void FUN_00bfd490(HostileEntry* first, HostileEntry* last, HostileEntry* out)
{
    while (last != first) {
        last -= 1;
        out -= 1;
        out->mField08 = last->mField08;
        out->mField0c = last->mField0c;
        out->mField10 = last->mField10;
        out->mField14 = last->mField14;
        out->mByte18 = last->mByte18;
        out->mField1c = last->mField1c;
        out->mField20 = last->mField20;
    }
}

// @ 0x00bfd4e0
Combatant* __fastcall Combatant_ctor(Combatant* self)
{
    self->vftable = (void**)0x14698f0;
    self->mIgnoreCombatLineTest = 0;
    self->mLineTestIgnoresFriendlies = 0;
    CombatantListHead* head = (CombatantListHead*)((char*)self + 0x10);
    head->mPrev = 0;
    head->mLive = 0;
    head->mField0c = 0;
    head->mNext = head;
    self->mList14 = head;
    self->mList18 = 0;
    self->mByte1c = 0;
    self->mField20 = 0;
    self->mNextTarget28 = 0;
    self->mField2c = 10.0f;
    self->mField30 = 0;
    self->mHealth38 = 10.0f;
    self->mField34 = 0;
    self->mDamageState3c = 0xffffffff;
    self->mField40 = 0.5f;
    self->mField44 = 0;
    self->mField48 = 0;
    self->mField4c = *(float*)0x168cb6c;
    self->mField50 = *(float*)0x168cb70;
    self->mField54 = *(float*)0x168cb74;
    self->mHostileBegin58 = 0;
    self->mHostileEnd5c = 0;
    self->mHostileCap60 = 0;
    self->mStunFlag6c = 1;
    self->mStunTimer70 = 0;
    self->mField74 = *(float*)0x168cb6c;
    self->mField78 = *(float*)0x168cb70;
    self->mField7c = *(float*)0x168cb74;
    self->mByte80 = 0;
    self->mByte81 = 0;
    self->mVec84Begin = 0;
    self->mVec84End = 0;
    self->mVec84Cap = 0;
    ((RcTimer*)((char*)self + 0x98))->Ctor();
    self->mSlotsBc[0] = 0;
    self->mSlotsBc[1] = 0;
    self->mSlotsBc[2] = 0;
    return self;
}
