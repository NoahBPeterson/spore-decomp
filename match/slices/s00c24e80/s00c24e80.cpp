// Slice s00c24e80 : creature animation / tool-effect helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef          int   s32;

// ------------------------------------------------------------------ callees
// All of these are __thiscall (this in ecx); modelled as methods so cl emits
// `mov ecx,<self>` + stack pushes exactly like retail.
struct cCreatureBaseOps
{
    void  SpawnEffect(int, int, int, int, float, int, int, int, int, int, int); // 0x00c0bf10
    char  TestFlag(int);                                                        // 0x00c0e0c0
    char  InterruptAnimation(int, void*, int);                                  // 0x00c12310
    char  PlayAnimation(int, int, void*);                                       // 0x00c12190
    int   WaitForAnimEventOrEnd(int, u32*, int, int, int);                      // 0x00c14ef0
    bool  AnimationFinished(int);                                               // 0x00c123f0
    void  SetToolEffect(u32, u32);                                              // 0x00c24f40
};

typedef bool (__thiscall* FnBoolThis)(void*);
typedef char (__thiscall* FnCharThis)(void*);

// @ 0x00c24e80
void __fastcall FUN_00c24e80(void* self_, int, float param_3)
{
    char* self = (char*)self_;

    if (*(u32*)(self + 0x1014) == 0)
        return;
    if (*(u32*)(*(char**)(self + 0xb4c)) == 0)
        return;

    void* obj = self + 0xc0;
    char ok = ((FnCharThis)(*(void***)obj)[0x16])(obj);
    if (ok != 0)
    {
        float v = param_3 * 0.5f;
        if (v < 3.0f) v = 3.0f;
        if (v > 5.0f) v = 5.0f;
        param_3 = v;
    }
    ((cCreatureBaseOps*)self_)->SpawnEffect(0, 0x10000, 0, 0x10000, param_3, 0, 0x10, 0, 0, 0, 0);
}

// ------------------------------------------------------------ 00c24f40 model
// cSPCreatureCitizen view at retail offsets.  Callees are __thiscall methods so
// cl emits `mov ecx,<self>` exactly like retail.
struct Citizen48
{
    void*  mVtbl;               // 0x00000
    u8     pad_004[0x00034 - 0x00004];
    u8     mBundleListBase;     // 0x00034  cGameBundleContainer::mBundleList (ecx = this+0x34)
    u8     pad_035[0x000c0 - 0x00035];
    void*  mSubC0Vtbl;          // 0x000c0  sub-object vtable (ecx = this+0xc0)
    u8     pad_c4[0x00b20 - 0x000c4];
    void*  mFieldB20;           // 0x00b20  (float "scale" at +0x590)
    u8     pad_b24[0x00b54 - 0x00b24];
    void*  mFieldB54;           // 0x00b54
    u8     pad_b58[0x00fc4 - 0x00b58];
    void*  mpBehaviorTreeData;  // 0x00fc4
    void*  mpInteractor;        // 0x00fc8  mpWhoIsInteractingWithMe.mpObject
    u8     pad_fcc[0x00ffc - 0x00fcc];
    u32    mFoodValue;          // 0x00ffc
    u8     pad_1000[0x01002 - 0x01000];
    u8     mField1002;          // 0x01002
    u8     pad_1003[0x01010 - 0x01003];
    void*  mField1010;          // 0x01010
    void*  mField1014;          // 0x01014
    u8     pad_1018[0x0102c - 0x01018];
    u32    mField102C;          // 0x0102c

    int   FUN_00c0f4f0();                             // 0x00c0f4f0
    void  SetToolTarget(float, float, float);         // 0x00c234a0
    char  TestFlag(int);                              // 0x00c0e0c0
    char  PlayAnimation(int, int, void*);             // 0x00c12190
    bool  AnimationFinished(int);                     // 0x00c123f0
    int   WaitForAnimEventOrEnd(int, u32*, int, int, int); // 0x00c14ef0

    void  FUN_00c24040(void*);                        // 0x00c24040
    bool  DetachBodyEffectById(void*, void*);         // 0x00c15150
    void  FUN_00c17d60(int, void*, int, void*, int); // 0x00c17d60
    void* FUN_00c0dfb0(void*);                        // 0x00c0dfb0
    void  FUN_00c0de60(void*, void*);                 // 0x00c0de60
    void* FUN_00c23f80(int, int, int, void*);         // 0x00c23f80
    bool  IsLeader();                                 // 0x00c232d0
    char  FUN_00c0b780();                             // 0x00c0b780
};

// cXformMessage (0x38 bytes).  Named members rather than a byte array so cl does
// not emit a /GS stack cookie (retail has none here).
struct XformMsg48
{
    u16   mField00;
    u16   mField02;                                   // incremented by 1 before SetXform
    u32   mField04;
    u16   mField08;
    u16   mField0A;
    u32   mField0C;
    float mField10;                                   // the distance
    u32   mField14;
    u32   mField18;
    u32   mField1C;
    u32   mField20;
    u32   mField24;
    u32   mField28;
    u32   mField2C;
    u32   mField30;
    u32   mField34;

    void  FUN_00434040();                             // 0x00434040 ctor
};

void* __cdecl FUN_00c9cec0(int);                      // 0x00c9cec0
struct Community48 { void* FUN_00c00650(); };         // 0x00c00650 (ecx = cCommunity*)

struct Effect150 { bool FUN_009b3050(u32, u32); };    // 0x009b3050 (ecx = effect+0x150)

struct BundleList48 { u32 FUN_00cee330(); };          // 0x00cee330 (ecx = self+0x34)
struct Pair48 { void* a; void* b; };                  // 8-byte {bt, interactor} pair
struct ObjTiny48 { u32 FUN_00ac7ab0(); };             // 0x00ac7ab0 (ecx = object)

void  __cdecl FUN_00c10330_c(void*, u32, void*, int, void*, int);  // 0x00c10330
void* __stdcall FUN_00b3d2b0_c(float, void*, u32);                 // 0x00b3d2b0

typedef void  (__thiscall* FnVoidThis)(void*);
typedef void* (__thiscall* FnPtrThis)(void*);
typedef void  (__thiscall* FnMsgThis)(void*, void*);
typedef void  (__thiscall* Fn3This)(void*, int, void*, int);

// Retail float globals (values in the analysis image) - read in place so both the
// register usage and the memory read match the original.
#define G146aaf4  (*(const float*)0x0146aaf4)   // -0.866025388
#define G1471064  (*(const float*)0x01471064)   //  0.5
#define G1485378  (*(const float*)0x01485378)   //  _HK_REAL_ZERO
#define G1485720  (*(const float*)0x01485720)   //  _HK_REAL_ONE
#define G1581334  (*(const float*)0x01581334)   //  dist multiplier (0.0)
#define G1581338  (*(const float*)0x01581338)   //  dist reset value (0.0)
#define G168dcc8  (*(const float*)0x0168dcc8)
#define G168dccc  (*(const float*)0x0168dccc)
#define G168dcd0  (*(const float*)0x0168dcd0)

// Shared tail used by the two animation-event blocks of 00c25530 (retail duplicates it).
__forceinline static void SpawnTail48(Citizen48* self, u32 d)
{
    void* btv = self->mpBehaviorTreeData;
    char* eff = (char*)btv + 0x2735300;
    self->FUN_00c24040(btv);
    self->DetachBodyEffectById(eff, (void*)d);
    if (btv == self->mpBehaviorTreeData)
        self->mFoodValue = 0;

    void* rr = ((FnPtrThis)((void**)self->mSubC0Vtbl)[0x68 / 4])((char*)self + 0xc0);
    float dist = (*(float*)((char*)rr + 0x14) - *(float*)((char*)rr + 8)) * G1581334;
    self->FUN_00c17d60(0, btv, 0, eff, 1);

    void* found = self->FUN_00c0dfb0(eff);
    if (found == 0)
        return;
    if (self->mField1014 == 0)
        return;

    int   a   = *(int*)((char*)found + 8);
    char* t   = (char*)self->mFieldB54;
    char* u   = *(char**)(t + 0x17c);
    char* v   = *(char**)(u + 0x2e4);
    void* val = *(void**)(v + a * 0x2bc);
    self->FUN_00c0de60(val, found);
    self->FUN_00c23f80(0, 0, a, 0);

    void* o8c = *(void**)((char*)found + 0x8c);
    if (o8c == 0)
        return;
    XformMsg48 msg;
    msg.FUN_00434040();
    o8c = *(void**)((char*)found + 0x8c);
    ((FnMsgThis)((void**)o8c)[0x20 / 4])(o8c, &msg);
    *(u16*)&msg.mField02 += 1;
    msg.mField10 = dist;
    o8c = *(void**)((char*)found + 0x8c);
    ((FnMsgThis)((void**)o8c)[0x18 / 4])(o8c, &msg);
}

// @ 0x00c25530
// Returns a bool: retail hands eax straight back from AnimationFinished/PlayAnimation
// (only al is defined; every test on the result is a byte test).
bool __fastcall FUN_00c25530(void* self_, int, u32 param_2)
{
    Citizen48*    self    = (Citizen48*)self_;
    BundleList48* bundles = (BundleList48*)&self->mBundleListBase;
    u32 local44 = 0xffffffff;
    Pair48 pair;
    int iVar4 = self->FUN_00c0f4f0();        // signed in retail (jg/jl on ebx)

    if (*(float*)(*(char**)&self->mFieldB20 + 0x590) == G1485378)   // _HK_REAL_ZERO
        iVar4 = 1;

    if (bundles->FUN_00cee330() != 0)
    {
        if (iVar4 > 2)
            goto L_558d;
        if (self->mFoodValue != 0)
            goto L_567d;
        if (iVar4 < 2)
            goto L_55c8;
    L_558d:
        if (self->AnimationFinished(0x2c39200) != 0 && self->AnimationFinished(0x66e50fc) != 0)
            return 1;
        return 0;
    L_55c8:
        if (self->mField1002 != 1)
            return self->AnimationFinished(0x4ffb325);   // bool: raw eax, not zero-extended
        if (self->TestFlag(0x4ffb325) == 0)
        {
            self->PlayAnimation(0x4ffb325, 1, self->mpInteractor);
            return 0;
        }
        param_2 = 0xffffffff;
        if (self->WaitForAnimEventOrEnd(0xbfa50b5a, &param_2, 0x4ffb325, 0, 1) == 0)
            return 0;
        self->SetToolTarget(G168dcc8, G168dccc, G168dcd0);
        return 0;
    }

L_567d:
    if (self->TestFlag(0x66e50fc) != 0 || self->TestFlag(0x2c39200) != 0)
        goto L_5782;
    if (bundles->FUN_00cee330() != 0)
        goto L_574b;
    if (iVar4 == 2)
    {
        if (self->mFoodValue != 0)
        {
            u32 pa = (u32)self->PlayAnimation(0x66e50fc, 1, (void*)0xffffffff);
            pair.a = self->mpBehaviorTreeData;
            pair.b = self->mpInteractor;
            FUN_00c10330_c(self_, pa, &pair, 2, &pair, 2);
            return 0;
        }
    }
    else if (iVar4 == 1)
    {
        self->PlayAnimation(0x2c39200, 1, self->mpBehaviorTreeData);
        return 0;
    }
    self->PlayAnimation(0x2c39200, 1, self->mpInteractor);
    return 0;

L_574b:
    if (iVar4 > 2)
        goto L_5a38;
    if (self->mFoodValue == 0)
        goto L_5a38;
    self->PlayAnimation(0x2c39200, 1, self->mpBehaviorTreeData);
    return 0;

L_5782:
    local44 = 0xffffffff;
    if (self->mFoodValue == 0)
        goto L_58e5;
    if (iVar4 == 2)
        goto L_57a9;
    if (self->mField1002 != 0)
        goto L_58e5;
L_57a9:
    {
        u32 sig = (bundles->FUN_00cee330() != 0) ? 0x7d7502fc : 0xe95450e;
        if (self->WaitForAnimEventOrEnd(sig, &local44, 0xffffffff, 0, 1) == 0)
            goto L_58e5;
        SpawnTail48(self, 1);
    }
L_58e5:
    if (bundles->FUN_00cee330() != 0)
        goto L_5a38;
    if (self->WaitForAnimEventOrEnd(0x7d7502fc, &local44, 0xffffffff, 0, 1) == 0)
        goto L_5a38;
    if (iVar4 != 1)
        goto L_5a20;
    SpawnTail48(self, iVar4);

L_5a20:
    {
        void* obj = FUN_00b3d2b0_c(G1581334, bundles, param_2);
        ((ObjTiny48*)obj)->FUN_00ac7ab0();
    }

L_5a38:
    return 0;
}

// @ 0x00c24f40
void __fastcall FUN_00c24f40(void* self_, int, u32 param_2, void* param_3)
{
    Citizen48* self = (Citizen48*)self_;
    void* bt = param_3;
    if ((int)param_3 == -1)
        bt = self->mpBehaviorTreeData;

    self->FUN_00c24040(bt);

    char* effect = (char*)bt + 0x2735300;             // local_3c
    self->DetachBodyEffectById(effect, (void*)1);

    if (bt == self->mpBehaviorTreeData)
        self->mFoodValue = param_2;

    void* r = ((FnPtrThis)((void**)self->mSubC0Vtbl)[0x68 / 4])((char*)self_ + 0xc0);
    float dist = (*(float*)((char*)r + 0x14) - *(float*)((char*)r + 8)) * G1581334;

    int  iVar7   = 0;
    bool bVar2   = false;
    void* local58 = 0;

    switch (param_2)
    {
    case 1:
        bVar2 = true;  iVar7 = (int)0xdbfd6844;
        local58 = *(void**)((char*)FUN_00c9cec0(1) + 0x30);   break;
    case 2:
        bVar2 = true;  iVar7 = (int)0xdbfd6847;
        local58 = *(void**)((char*)FUN_00c9cec0(2) + 0x30);   break;
    case 3:
        bVar2 = true;  iVar7 = (int)0xdbfd6846;
        local58 = *(void**)((char*)FUN_00c9cec0(3) + 0x30);   break;
    case 4:
    {
        void* cm = self->mField1010 ? self->mField1010 : self->mField1014;
        if ((cm != 0 && ((Community48*)cm)->FUN_00c00650() == self_) || self->mField102C == 8)
        {
            bVar2 = true;
            iVar7 = (self->IsLeader() ? 0x694b4df0 : 0) + 0x1cf84d57;
            local58 = *(void**)((char*)FUN_00c9cec0(8) + 0x30);
        }
        break;
    }
    case 5:
    {
        void* cm = self->mField1010 ? self->mField1010 : self->mField1014;
        if ((cm == 0 || ((Community48*)cm)->FUN_00c00650() != self_) && self->mField102C != 8)
        {
            bVar2 = false; iVar7 = (int)0x3a887470;
        }
        else
        {
            bVar2 = true;
            iVar7 = (self->IsLeader() ? 0x48e62a90 : 0) + 0xce7cd1c8;
        }
        break;
    }
    case 6:
    {
        void* cm = self->mField1010 ? self->mField1010 : self->mField1014;
        if ((cm == 0 || ((Community48*)cm)->FUN_00c00650() != self_) && self->mField102C != 8)
        {
            bVar2 = false; iVar7 = (int)0x1192b368;
        }
        else
        {
            bVar2 = true;
            iVar7 = (self->IsLeader() ? 0x7e324150 : 0) + 0x51fe9fb0;
        }
        break;
    }
    case 7:  iVar7 = (int)0xae024c94; dist = G1581338; break;
    case 8:  iVar7 = (self->FUN_00c0b780() ? 0x28f5c108 : 0) + 0x1192b368;
             dist = G1581338; break;
    case 9:  iVar7 = (int)0xdc87ff23; dist = G1581338; break;
    case 10: iVar7 = (int)0x1192b368; dist = G1581338; break;
    case 11: iVar7 = (int)0xb4dd0222; break;
    case 12: bVar2 = true; iVar7 = (int)0x5223cf1e; break;
    case 13:
        bVar2 = true;  iVar7 = (int)0xb9319ac6;
        local58 = *(void**)((char*)FUN_00c9cec0(5) + 0x30);   break;
    case 14:
        bVar2 = true;  iVar7 = (int)0x59867820;
        local58 = *(void**)((char*)FUN_00c9cec0(4) + 0x30);   break;
    case 15:
        bVar2 = true;  iVar7 = (int)0xf8122731;
        local58 = *(void**)((char*)FUN_00c9cec0(6) + 0x30);   break;
    case 16:
        bVar2 = true;  iVar7 = (int)0x759b0e13;
        local58 = *(void**)((char*)FUN_00c9cec0(7) + 0x30);   break;
    case 17:
        bVar2 = true;  iVar7 = (int)0x86439b47;
        local58 = *(void**)((char*)FUN_00c9cec0(0xb) + 0x30); break;
    case 18:
        bVar2 = true;  iVar7 = (int)0x792e9926;
        local58 = *(void**)((char*)FUN_00c9cec0(9) + 0x30);   break;
    case 19: iVar7 = (int)0xd72f5830; break;
    case 20: iVar7 = (int)0xc4717433; break;
    case 21: iVar7 = (int)0xa8f747ae; break;
    case 22: iVar7 = (int)0x2b4d0331; break;
    case 23: iVar7 = (int)0x541b4a0d; dist = G1581338; break;
    }

    self->FUN_00c17d60(iVar7 != 0, bt, iVar7, effect, 1);

    void* found = self->FUN_00c0dfb0(effect);
    if (found == 0)
        return;
    if (self->mField1014 == 0)
        return;

    int   a   = *(int*)((char*)found + 8);
    char* t   = (char*)self->mFieldB54;
    char* u   = *(char**)(t + 0x17c);
    char* v   = *(char**)(u + 0x2e4);
    void* val = *(void**)(v + a * 0x2bc);
    self->FUN_00c0de60(val, found);

    void* rr = self->FUN_00c23f80((int)param_2, iVar7, a, local58);
    if (param_2 == 0x14 && rr != 0)
    {
        char* e = (char*)found;
        if (*(u8*)((char*)rr + 0x18) == 0 && ((Effect150*)(effect + 0x150))->FUN_009b3050(0x70737267, 0) != 0)
        {
            *(float*)(e + 0x18) = 0.0f;
            *(float*)(e + 0x1c) = 0.0f;
            *(float*)(e + 0x20) = 0.0f;
            *(float*)(e + 0x24) = 1.0f;              // 0x1485720 (_HK_REAL_ONE)
        }
        else if (((Effect150*)(effect + 0x150))->FUN_009b3050(0x74756f6d, 0) != 0)
        {
            *(float*)(e + 0x18) = -0.866025388f;     // 0x146aaf4
            *(float*)(e + 0x1c) = 0.0f;
            *(float*)(e + 0x20) = 0.0f;
            *(float*)(e + 0x24) = 0.5f;              // 0x1471064
        }
    }

    void* obj8c = *(void**)((char*)found + 0x8c);
    if (obj8c == 0)
        return;

    if (bVar2)
    {
        void* res = ((FnPtrThis)((void**)self->mVtbl)[0xe0 / 4])(self_);
        ((Fn3This)((void**)obj8c)[0x44 / 4])(obj8c, 5, res, 3);
    }

    XformMsg48 msg;
    msg.FUN_00434040();
    void* obj8c2 = *(void**)((char*)found + 0x8c);
    ((FnMsgThis)((void**)obj8c2)[0x20 / 4])(obj8c2, &msg);

    void* obj8c3 = *(void**)((char*)found + 0x8c);
    msg.mField02 += 1;
    msg.mField10 = dist;
    ((FnMsgThis)((void**)obj8c3)[0x18 / 4])(obj8c3, &msg);
}

// @ 0x00c25480
bool __fastcall FUN_00c25480(void* self_, int, u32 arg1, u32 arg2)
{
    char* self = (char*)self_;

    if (*(u32*)(self + 0xffc) == arg1)
        return ((cCreatureBaseOps*)self_)->AnimationFinished(0x2c39200);

    if (((cCreatureBaseOps*)self_)->TestFlag(0x2c39200) != 0)
    {
        u32 evt = 0xffffffff;
        if (((cCreatureBaseOps*)self_)->WaitForAnimEventOrEnd(0x7d7502fc, &evt, 0x2c39200, 0, 1) != 0)
            ((cCreatureBaseOps*)self_)->SetToolEffect(arg1, evt);
        return false;
    }

    if ((u8)arg2 != 0)
    {
        ((cCreatureBaseOps*)self_)->InterruptAnimation(0x2c39200, *(void**)(self + 0xfc4), 0);
        return false;
    }
    ((cCreatureBaseOps*)self_)->PlayAnimation(0x2c39200, 1, *(void**)(self + 0xfc4));
    return false;
}