// Slice s00c23f80: Simulator::cCreatureBase combat/ability/update helpers (retail).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// The retail layout differs from the 2008 PDB; offsets come from the disassembly.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef unsigned __int64 u64;
typedef float          f32;
typedef double         f64;

#pragma warning(disable: 4100)

#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))

// ---------------------------------------------------------------- globals
extern u8    gB_0167ade8;                        // 0x0167ade8
extern f32   gF_01687a00;                        // 0x01687a00
extern f32   gF_01687a0c;                        // 0x01687a0c
extern f32   gF_01687a10;                        // 0x01687a10
extern f32   gF_0146aa40;                        // 0x0146aa40  (FLT_MAX)
extern f32   gF_0143ee00;                        // 0x0143ee00  (3000.0f)
extern f32   gF_0146aaf0;                        // 0x0146aaf0
extern f32   gF_01470f1c;                        // 0x01470f1c
extern f32   gF_01486110;                        // 0x01486110
extern f32   gF_013ec4d0;                        // 0x013ec4d0
extern f32   gF_013f9428;                        // 0x013f9428
extern f32   gF_013f4fd0;                        // 0x013f4fd0
extern f32   gF_01485720;                        // 0x01485720  (_HK_REAL_ONE)
extern f32   gF_0150c888;                        // 0x0150c888
extern f32   gF_0158121c;                        // 0x0158121c
extern u32   gU_0168dbb0;                        // 0x0168dbb0
extern u32   gU_0168dbb4;                        // 0x0168dbb4
extern u32   gU_0168dbb8;                        // 0x0168dbb8
extern void* gP_0169b41c;                        // 0x0169b41c

// ---------------------------------------------------------------- callees
// freestanding (cdecl) helpers used by this slice.
void  __stdcall FUN_009ff7c0(u32 a1, u32 a2);          // 0x009ff7c0
void  __cdecl FUN_00bca810(u32 a1, u32 a2, void* a3, f32 a4, void* a5, u32 a6); // 0x00bca810
void  __cdecl FUN_00bca040(u32 a1);                  // 0x00bca040
void* __cdecl FUN_00b3d2b0();                        // 0x00b3d2b0
void* __cdecl FUN_00b3d280();                        // 0x00b3d280  GetCameraCtl
void* __cdecl FUN_00b3d2b0b();                       // 0x00b3d2b0 dup
void* __cdecl FUN_00b3d300();                        // 0x00b3d300  NounManager
void* __cdecl FUN_00b3d380();                        // 0x00b3d380  GameTimeManager
void* __cdecl FUN_00b3d3e0();                        // 0x00b3d3e0  EventLog
void* __cdecl FUN_004d9050(void* a1);                // 0x004d9050
void* __cdecl FUN_004d9030(void* a1);                // 0x004d9030
void* __cdecl FUN_00c9cec0(u32 a1);                  // 0x00c9cec0
void* __cdecl FUN_00d1e660();                        // 0x00d1e660
void* __cdecl FUN_00b6f0c0(u32 a1);                  // 0x00b6f0c0
void* __cdecl FUN_00cd40b0();                        // 0x00cd40b0  cTribeModeStrategy::Instance
u32   __cdecl FUN_009b2340(void* a1, u32 a2, u32 a3, void* a4, u32 a5, u32 a6); // 0x009b2340

struct cCreatureBase;
void __cdecl FUN_00c24110(cCreatureBase* param_1);   // 0x00c24110

// ---------------------------------------------------------------- placeholder ops
struct COps
{
    void* FUN_00c00650();                            // 0x00c00650 (GetMember)
    u32   FUN_00c0e040(u32* out);                    // 0x00c0e040
    void* FUN_00c0f9b0(u32 a, u32* b);               // 0x00c0f9b0 (FindSlotByKey)
    void* FUN_00c0f4f0();                            // 0x00c0f4f0
    u8    FUN_00c0b770();                            // 0x00c0b770
    void  FUN_00c1c9f0(u32 a);                       // 0x00c1c9f0
    void* FUN_00c0bf10(u32 a1, u32 a2, u32 a3, u32 a4, f32 a5, u32 a6, u32 a7, u32 a8, u32 a9, u32 a10, u32 a11); // 0x00c0bf10
    void* FUN_00bc96a0(u32 a, u32 b);                // 0x00bc96a0
    void* FUN_00bc97f0(u32 a, u32 b, f32 c, u32 d);  // 0x00bc97f0
    void* FUN_00bc9980(f32 a);                       // 0x00bc9980
    void  FUN_00c15bd0(u32 a, u32 b, u32 c);         // 0x00c15bd0
    void  FUN_00ac79d0();                            // 0x00ac79d0
    void  FUN_00ac7de0(void* a);                     // 0x00ac7de0
    void  FUN_00b137d0(void* a);                     // 0x00b137d0 (GetTargetOrientation)
    void  FUN_00c3f160(u32 a);                       // 0x00c3f160 (SetEffectId)
    void  FUN_00b225d0(void* a);                     // 0x00b225d0 (RemoveNoun)
    void* FUN_00c23300(u32 a, u32 b);                // 0x00c23300
    void  FUN_00d995f0(f32 a1, f64 a2, u32 a3, void* a4, void* a5, u32 a6, u32 a7, u32 a8); // 0x00d995f0
    void  FUN_00dd8640(u32 a1, u32 a2, void* a3); // 0x00dd8640
    void  FUN_00ccc400();                            // 0x00ccc400
    void* FUN_00bca2c0();                            // 0x00bca2c0 (FirstPending)
    u8    FUN_00c232d0();                            // 0x00c232d0 (IsLeader)
    void  FUN_00c1d400(u32 a, u32 b);                // 0x00c1d400
    void  FUN_00c213d0(u32 a);                       // 0x00c213d0
    u32   FUN_00cee330();                            // 0x00cee330
    void  FUN_00c14750(u32 a);                       // 0x00c14750
    u8    FUN_00c0c130();                            // 0x00c0c130
    f32   FUN_00c0c070();                            // 0x00c0c070
    void  FUN_00c0ba10();                            // 0x00c0ba10
    u8    FUN_00c0ba70();                            // 0x00c0ba70
    void  FUN_00c95cc0(void* a);                     // 0x00c95cc0
    u32   FUN_00abf760(u32 a, void* b, u32 c);       // 0x00abf760
    void  FUN_00c22240();                            // 0x00c22240
    u32   FUN_00c8f370();                            // 0x00c8f370 (GetAdultPopulation)
    u8    FUN_00c0e420();                            // 0x00c0e420
    u32   FUN_00a02ba0();                            // 0x00a02ba0
    void  FUN_00bc3110();                            // 0x00bc3110 (cSPTimer::Stop)
    u64   FUN_00b316c0();                            // 0x00b316c0
    u32   FUN_00c17de0(f32 a);                       // 0x00c17de0
    void* FUN_00c0b670(u32 a);                        // 0x00c0b670
    void  FUN_00c0d340(u32 a);                        // 0x00c0d340
    f64   FUN_00bfc490();                             // 0x00bfc490
    void  FUN_00bca810(u32 a1, u32 a2, void* a3, f32 a4, void* a5, u32 a6); // 0x00bca810
};

// ---------------------------------------------------------------- types
struct Vec3 { f32 x, y, z; };

// The creature object.  Only the offsets touched in this slice are named.
struct cCreatureBase
{
    u8     pad0[0x24];                               // 0x0000
    u32    mField24;                                 // 0x0024
    u8     pad28[0x34 - 0x28];
    void*  mpObj34;                                  // 0x0034
    u8     pad38[0x58 - 0x38];
    void*  mpObj58;                                  // 0x0058
    u8     pad5c[0xc0 - 0x5c];
    void*  mpObjc0;                                  // 0x00c0
    u8     padc4[0x110 - 0xc4];
    u32    mFlags110;                                // 0x0110
    u8     pad114[0x135 - 0x114];
    u8     mField135;                                // 0x0135
    u8     mField136;                                // 0x0136
    u8     mField137;                                // 0x0137
    u8     pad138[0x1e4 - 0x138];
    f32    mField1e4;                                // 0x01e4
    u8     pad1e8[0x2b0 - 0x1e8];
    u32    mField2b0;                                // 0x02b0
    u8     pad2b4[0x5a8 - 0x2b4];
    f32    mNoAttackTimer;                           // 0x05a8
    u8     pad5ac[0xa68 - 0x5ac];
    u32    mFielda68;                                // 0x0a68
    u32    mFielda6c;                                // 0x0a6c
    u8     padb14a[0xaf4 - 0xa70];
    void*  mpFieldaf4;                               // 0x0af4
    u8     padb14b[0xb14 - 0xaf8];
    void*  mpFieldb14;                               // 0x0b14
    u8     padb18[0xb20 - 0xb18];
    void*  mpFieldb20;                               // 0x0b20
    u8     padb24[0xb48 - 0xb24];
    void*  mpOrderMgr_b48;                           // 0x0b48
    void*  mpFieldb4c;                               // 0x0b4c
    u8     padb50[0xb54 - 0xb50];
    void*  mpAnimWorld_b54;                          // 0x0b54
    u8     padb58[0xb5e - 0xb58];
    u8     mFieldb5e;                                // 0x0b5e
    u8     padb5f[0xb61 - 0xb5f];
    u8     mFieldb61;                                // 0x0b61
    u8     padb62[0xb80 - 0xb62];
    f32    mFieldb80;                                // 0x0b80
    u8     padb84[0xbbc - 0xb84];
    f32    mFieldbbc;                                // 0x0bbc
    u8     padbc0[0xc00 - 0xbc0];
    u32    mFieldc00;                                // 0x0c00
    u8     padc04[0xcc0 - 0xc04];
    i32    mLastMotiveState;                         // 0x0cc0
    u8     padcc4[0xe40 - 0xcc4];
    void*  mpNeighbor_e40;                           // 0x0e40
    u8     pade44[0xeac - 0xe44];
    i32    mFieldeac;                                // 0x0eac
    u8     padeb0[0xf50 - 0xeb0];
    void*  mpFieldf50;                               // 0x0f50
    void*  mpFieldf54;                               // 0x0f54
    u8     padf58[0xfbc - 0xf58];
    u32    mFieldfbc;                                // 0x0fbc
    i32    mFieldfc0;                                // 0x0fc0
    u32    mFieldfc4;                                // 0x0fc4
    u32    mFieldfc8;                                // 0x0fc8
    u8     padfcc[0xff0 - 0xfcc];
    u32    mFieldff0;                                // 0x0ff0
    u32    mFieldff4;                                // 0x0ff4
    u32    mFieldff8;                                // 0x0ff8
    u32    mFieldffc;                                // 0x0ffc
    u8     mField1000;                               // 0x1000
    u8     mField1001;                               // 0x1001
    u8     mField1002;                               // 0x1002
    u8     pad1003[0x1004 - 0x1003];
    u32    mField1004;                               // 0x1004
    u32    mField1008;                               // 0x1008
    u32    mField100c;                               // 0x100c
    void*  mField1010;                               // 0x1010
    void*  mpField1014;                              // 0x1014
    u8     pad1018[0x102c - 0x1018];
    i32    mField102c;                               // 0x102c
    void*  mpField1030;                              // 0x1030

    // methods defined in this slice
    u32  FUN_00c23f80(u32 a, u32 b, u32 c, u32 d);
    void FUN_00c24040(u32 a);
    void FUN_00c242b0(u32 a);
    i32  FUN_00c24480();
    void* FUN_00c24400(u32 a);
    u8   FUN_00c24430();
    bool FUN_00c24560();
    u32  FUN_00c245e0(u32 a1, u32 a2, f32 a3, u32 a4, u32 a5, u32 a6);
    u32  FUN_00c24680(u32 a1, u32 a2, f32 a3, u32 a4, void* a5, u32 a6);
    void FUN_00c24700(u32 a1, u32 a2, u32 a3);
    void FUN_00c24760();
    void FUN_00c248d0(i32 a);
    i32  FUN_00c24750();
    i32  FUN_00c24c50();
    void* FUN_00c24ce0(u32 a);
    f64  FUN_00c24df0();
};

// a generic vtable bearing object
struct ObjVtbl
{
    virtual void  Slot00();
    virtual void  Slot04();
    virtual void  Slot08();
    virtual void* Slot0c(u32);
    virtual void  Slot10();
    virtual void* Slot14(u32, u32, u32);
    virtual void  Slot18();
    virtual void  Slot1c();
    virtual void* Slot20();
    virtual void  Slot24();
    virtual void  Slot28();
    virtual void  Slot2c();
    virtual void  Slot30();
    virtual void  Slot34();
    virtual void  Slot38();
    virtual void  Slot3c();
    virtual void  Slot40();
    virtual void  Slot44();
    virtual void  Slot48();
    virtual void  Slot4c();
    virtual void  Slot50();
    virtual void  Slot54();
    virtual void  Slot58();
    virtual void  Slot5c();
    virtual void  Slot60();
    virtual void  Slot64();
    virtual void  Slot68();
    virtual void  Slot6c();
    virtual void* Slot70();
    virtual void  Slot74();
    virtual void  Slot78();
    virtual void  Slot7c();
    virtual void  Slot80();
    virtual void  Slot84();
    virtual void  Slot88();
    virtual void  Slot8c();
    virtual void  Slot90();
    virtual void  Slot94();
    virtual void  Slot98();
    virtual void  Slot9c();
    virtual void  SlotA0();
    virtual void  SlotA4();
    virtual void  SlotA8();
    virtual void  SlotAc();
    virtual void  SlotB0();
    virtual void  SlotB4();
    virtual void* SlotB8(u32);
    virtual void  SlotBc();
    virtual void  SlotC0();
};

// ===========================================================================
// definitions
// ===========================================================================

// ---------------------------------------------------------------------------
// 0x00c23f80
// ---------------------------------------------------------------------------
// @ 0x00c23f80
u32 cCreatureBase::FUN_00c23f80(u32 param_2, u32 param_3, u32 param_4, u32 param_5)
{
    u32 slot = 0;
    void* s = MOPS(this)->FUN_00c0f9b0(param_4, &slot);
    if (s)
    {
        *(u32*)((u8*)s + 0x10) = param_3;
        *(u32*)((u8*)s + 0x04) = param_2;
        if (param_5)
        {
            *(u32*)((u8*)s + 0x08) = param_5;
            void* animWorld = mpAnimWorld_b54;
            u32 guid = 0;
            u32 ret = MOPS(this)->FUN_00c0e040(&guid);
            FUN_009ff7c0(*(u32*)((u8*)animWorld + 0x184), ret);
            struct { u32 a, b, c; u32 pad[5]; } msg;
            msg.a = slot;
            msg.b = guid;
            msg.c = 0;
            MOPS(mpOrderMgr_b48)->FUN_00bca810(5, 0, this, gF_0146aa40, &msg, 0);
        }
    }
    return (u32)s;
}

// ---------------------------------------------------------------------------
// 0x00c24040
// ---------------------------------------------------------------------------
// @ 0x00c24040
void cCreatureBase::FUN_00c24040(u32 param_2)
{
    u32 slot = 0;
    void* s = MOPS(this)->FUN_00c0f9b0(param_2, &slot);
    if (!s)
        return;
    u8* base = (u8*)mpOrderMgr_b48;
    u32 i = 0;
    while (i < 8)
    {
        u8* e = base + i * 0x44;
        if (*(u32*)(e + 0x24) == 5 && *(u32*)(e + 0x28) == 0 && *(u32*)e == slot)
        {
            FUN_00bca040(*(u16*)(e + 0x20) | (i << 0x10));
            break;
        }
        i++;
    }
    void* obj = *(void**)((u8*)s + 0x20);
    u32 r = 0;
    if (obj)
    {
        r = (u32)((void* (__thiscall*)(void*, u32))VT(obj)[0xb8 / 4])(obj, 0x4ffcdeda);
        if (r)
            ((void (__thiscall*)(void*))VT(r)[0])((void*)r);
    }
    MOPS(this)->FUN_00c15bd0(slot, 0, 0);
    if (r)
    {
        void* out = FUN_00b3d2b0();
        MOPS(out)->FUN_00ac79d0();
        MOPS(FUN_00b3d2b0())->FUN_00ac7de0((void*)r);
        ((void (__thiscall*)(void*))VT(r)[1])((void*)r);
    }
}

// ---------------------------------------------------------------------------
// 0x00c24110
// ---------------------------------------------------------------------------
// @ 0x00c24110
void FUN_00c24110(cCreatureBase* param_1)
{
    if (param_1->mpField1014 != 0)
    {
        u32 n = (u32)MOPS(param_1)->FUN_00c0f4f0();
        if (n == 0)
            return;
        u32 idx = param_1->mField24 % n;
        u8* tbl = (u8*)param_1->mpNeighbor_e40;
        u32 e0 = *(u32*)(tbl + idx * 0x24);
        u8 key = *(u8*)(tbl + idx * 0x24 + 0x18);
        param_1->mFieldfc4 = e0;
        u32 j = (idx + 1) % n;
        param_1->mFieldfc8 = *(u32*)(tbl + j * 0x24);
        while (j != idx)
        {
            if (key != *(u8*)(tbl + j * 0x24 + 0x18))
            {
                param_1->mFieldfc8 = *(u32*)(tbl + j * 0x24);
                return;
            }
            j = (j + 1) % n;
        }
        return;
    }
    {
        u32* v = (u32*)FUN_004d9050(param_1->mpAnimWorld_b54);
        if (((v[1] - v[0]) >> 2) > 0)
        {
            struct { u32 len, key, b, c; } local;
            local.len = 8;
            local.key = 0x70737267;
            local.b = 0;
            local.c = 0;
            u32 out = 0xffffffff;
            u32* p = (u32*)((u8*)param_1->mpAnimWorld_b54 + 0x17c);
            u32 r = FUN_009b2340(&out, 1, *(u32*)*p, &local.key, 0, 0);
            if (r && out != 0xffffffff)
                param_1->mFieldfc4 = out;
            return;
        }
        u32* w = (u32*)FUN_004d9030(param_1->mpAnimWorld_b54);
        if (((w[1] - w[0]) >> 2) > 0)
        {
            u32* p = (u32*)FUN_004d9030(param_1->mpAnimWorld_b54);
            u32 val = *(u32*)*p;
            if (val != 0xffffffff)
                param_1->mFieldfc4 = val;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c24280
// ---------------------------------------------------------------------------
// @ 0x00c24280
void FUN_00c24280(cCreatureBase* self)
{
    if (!self)
        return;
    u32 id = (u32)((void* (__thiscall*)(void*))VT(self)[0x20 / 4])(self);
    if (id == 0x18eb4b7)
        FUN_00c24110(self);
}

// ---------------------------------------------------------------------------
// 0x00c242b0
// ---------------------------------------------------------------------------
// @ 0x00c242b0
void cCreatureBase::FUN_00c242b0(u32 param_2)
{
    MOPS(this)->FUN_00c1c9f0(param_2);
    if ((u8)param_2 != 0)
        return;
    mFieldff0 = 0;
    mField102c = 0;
    mFieldfc0 = 3;
    mFieldff4 = 0xffffffff;
    mFieldff8 = 0xffffffff;
    mFieldffc = 0;
    mField1000 = 0;
    mField1002 = 1;
    mField1004 = gU_0168dbb0;
    mField1008 = gU_0168dbb4;
    mField100c = gU_0168dbb8;
    MOPS((u8*)this + 0xfd0)->FUN_00bc3110();
    u32 noun = *(u32*)((u8*)this + 0x1030);
    if (noun)
        MOPS(FUN_00b3d300())->FUN_00b225d0((void*)noun);
    u32 noun2 = *(u32*)((u8*)this + 0x1030);
    if (noun2)
    {
        *(u32*)((u8*)this + 0x1030) = 0;
        ((void (__thiscall*)(void*))VT((void*)noun2)[1])((void*)noun2);
    }
    mFieldbbc = gF_01687a00;
    MOPS(this)->FUN_00c0ba10();
}

// ---------------------------------------------------------------------------
// 0x00c24380
// ---------------------------------------------------------------------------
// @ 0x00c24380
void FUN_00c24380(cCreatureBase* self, void* item)
{
    MOPS(self)->FUN_00c0d340((u32)item);
    void* sub = (u8*)self - 0x34;
    void* cur = (void*)((void* (__thiscall*)(void*))VT(sub)[0x30 / 4])(sub);
    void* old = self->mpObj58;
    if (cur != old)
    {
        if (cur)
            ((void (__thiscall*)(void*))VT(cur)[0])(cur);
        self->mpObj58 = cur;
        if (old)
            ((void (__thiscall*)(void*))VT(old)[1])(old);
    }
    MOPS(sub)->FUN_00c23300((u32)item, 0xffffffff);
    if (*(u32*)((u8*)item + 0x12c) == 5)
        MOPS(self->mpFieldb14)->FUN_00bca810(0, 2, sub, gF_0146aa40, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x00c24400
// ---------------------------------------------------------------------------
// @ 0x00c24400
void* cCreatureBase::FUN_00c24400(u32 id)
{
    if (id == 0x4f176642)
        return this;
    if (id == 0xef3da0d7 && mpField1014)
        return this;
    return (void*)MOPS(this)->FUN_00c0b670(id);
}

// ---------------------------------------------------------------------------
// 0x00c24430
// ---------------------------------------------------------------------------
// @ 0x00c24430
u8 cCreatureBase::FUN_00c24430()
{
    if (mpFieldf50)
    {
        void* p = (u8*)mpFieldf50 + 0x120;
        return ((u8 (__thiscall*)(void*))VT(p)[0x58 / 4])(p) ? 1 : 0;
    }
    if (mpFieldf54)
    {
        void* p = (u8*)mpFieldf54 + 0x120;
        if (((u8 (__thiscall*)(void*))VT(p)[0x58 / 4])(p))
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c248d0 etc. follow
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// 0x00c24480
// ---------------------------------------------------------------------------
// @ 0x00c24480
i32 cCreatureBase::FUN_00c24480()
{
    if (!mpField1014)
        return 0;
    f32 t = (f32)(MOPS((u8*)this + 0x5a8)->FUN_00bfc490() * (f64)gF_013ec4d0);
    f32* cmp;
    if (t <= mNoAttackTimer)
        cmp = &mNoAttackTimer;
    else
        cmp = &t;
    f32 v = *cmp;
    i32 id = *(i32*)((u8*)mpFieldb4c + 0x1d8);
    u8 b = (u8)(id == 0x5218bb3 || id == 0x462854e);
    i32 state;
    if (mFieldb5e != 0 || b)
        state = 0;
    else if (v > gF_01687a0c)
        state = 1;
    else if (v > gF_01687a10)
        state = (mNoAttackTimer <= t) ? 2 : 4;
    else
        state = (mNoAttackTimer <= t) ? 3 : 5;
    if (state != mLastMotiveState)
    {
        mLastMotiveState = state;
        mFieldb61 = 1;
    }
    return mLastMotiveState;
}

// ---------------------------------------------------------------------------
// 0x00c24df0
// ---------------------------------------------------------------------------
// @ 0x00c24df0
f64 cCreatureBase::FUN_00c24df0()
{
    f32 scale = gF_01485720;
    cCreatureBase* self = (cCreatureBase*)((u8*)this - 0x5a8);
    if (!MOPS(self)->FUN_00c0b770())
        scale = gF_0150c888;
    if (mFielda6c != 0)
    {
        void* community = self->mField1010;
        if (!community)
            community = self->mpField1014;
        if (community)
        {
            bool leader = (MOPS(community)->FUN_00c00650() == (void*)self);
            if (leader)
                scale = gF_0158121c * scale;
        }
    }
    f32 base = (f32)((f64 (__thiscall*)(void*))VT(self)[0x7c / 4])(self);
    return (f64)base * (f64)scale;
}

// ---------------------------------------------------------------------------
// 0x00c24560
// ---------------------------------------------------------------------------
// @ 0x00c24560
bool cCreatureBase::FUN_00c24560()
{
    if (mpField1014 && mpFieldb4c && *(u32*)mpFieldb4c)
    {
        if (!MOPS(this)->FUN_00c0b770())
            return true;
        void* a = MOPS(mpFieldb4c)->FUN_00bca2c0();
        void* b = (void*)((void* (__thiscall*)(void*))VT((u8*)this + 0x58)[0x20 / 4])((u8*)this + 0x58);
        if (a || b)
            return false;
        return true;
    }
    bool r = false;
    void* p = (void*)((void* (__thiscall*)(void*))VT((u8*)this + 0x58)[0x20 / 4])((u8*)this + 0x58);
    if (p == 0)
        r = true;
    else if (*(u32*)((u8*)p + 0x68) == 1)
    {
        if (!MOPS(this)->FUN_00c0ba70())
            r = true;
    }
    return r;
}

// ---------------------------------------------------------------------------
// 0x00c245e0
// ---------------------------------------------------------------------------
// @ 0x00c245e0
u32 cCreatureBase::FUN_00c245e0(u32 a1, u32 a2, f32 a3, u32 a4, u32 a5, u32 a6)
{
    if (!mpField1014 || !mpFieldb4c || !*(u32*)mpFieldb4c)
        return 0;
    MOPS(this)->FUN_00c0bf10(a1, a2, 0x1d3fbffa, 0x81240a0, a3, 1, 0, a4, a5, a6, 1);
    void* p = MOPS((u8*)mpFieldb4c + 8)->FUN_00bc96a0(1, 0);
    if (p)
        *(u32*)((u8*)p + 0xc) = 1;
    void* q = MOPS((u8*)mpFieldb4c + 8)->FUN_00bc96a0(a1, a2);
    *(u32*)((u8*)q + 0x14) = 0;
    return (u32)q;
}

// ---------------------------------------------------------------------------
// 0x00c24680
// ---------------------------------------------------------------------------
// @ 0x00c24680
u32 cCreatureBase::FUN_00c24680(u32 a1, u32 a2, f32 a3, u32 a4, void* a5, u32 a6)
{
    if (mpField1014 && mpFieldb4c && *(u32*)mpFieldb4c)
    {
        u32 v;
        if (a5)
            v = (u32)((void* (__thiscall*)(void*, u32))VT(a5)[4 / 4])(a5, 0xee3f516e);
        else
            v = 0;
        FUN_00c245e0(a1, a2, a3, a6, a4, v);
        return 0;
    }
    return MOPS((u8*)this + 0x58)->FUN_00abf760(a4, a5, a6);
}

// ---------------------------------------------------------------------------
// 0x00c24700
// ---------------------------------------------------------------------------
// @ 0x00c24700
void cCreatureBase::FUN_00c24700(u32 a1, u32 a2, u32 a3)
{
    if (mFieldfbc && mpFieldaf4 && *(u32*)mpFieldaf4)
    {
        ((cCreatureBase*)((u8*)this - 0x58))->FUN_00c24680(2, 0, gF_0146aa40, a1, (void*)a2, a3);
        return;
    }
    MOPS(this)->FUN_00abf760(a1, (void*)a2, a3);
}

// ---------------------------------------------------------------------------
// 0x00c24750
// ---------------------------------------------------------------------------
// @ 0x00c24750
i32 cCreatureBase::FUN_00c24750()
{
    return (mField1010 != 0) + 5;
}

// ---------------------------------------------------------------------------
// 0x00c24c50
// ---------------------------------------------------------------------------
// @ 0x00c24c50
i32 cCreatureBase::FUN_00c24c50()
{
    i32 n = mField102c - 1;
    i32 c = 0;
    switch (n)
    {
    case 0: case 1: case 2: case 3: case 4: case 5:
        c = 2; break;
    case 8: case 10:
        c = 1; break;
    default: break;
    }
    void* community = mField1010;
    if (!community)
        community = mpField1014;
    if (community)
    {
        bool leader = (MOPS(community)->FUN_00c00650() == (void*)this);
        if (leader)
            c += 6;
    }
    void* prof = mpFieldb20;
    u32* v = (u32*)((u8*)prof + 0x6d4);
    i32 vec = ((i32)v[1] - (i32)v[0]) >> 2;
    return vec + c;
}

// ---------------------------------------------------------------------------
// 0x00c24ce0
// ---------------------------------------------------------------------------
// @ 0x00c24ce0
void* cCreatureBase::FUN_00c24ce0(u32 param_2)
{
    if (param_2 == 0xffffffff)
        return 0;
    void* prof = mpFieldb20;
    u32 n = (u32)((*(u32*)((u8*)prof + 0x6d8) - *(u32*)((u8*)prof + 0x6d4)) >> 2);
    if (param_2 < n)
        return *(void**)(*(u32*)((u8*)prof + 0x6d4) + param_2 * 4);
    u32 i = param_2 - n;
    if (i == 0)
    {
        void* r = FUN_00c9cec0(mField102c);
        return *(void**)((u8*)r + 0x24);
    }
    if (MOPS(this)->FUN_00c232d0())
    {
        if (i - 1 < 6)
        {
            void* r = FUN_00d1e660();
            return *(void**)((u8*)r + 0x1c + (i - 1) * 4);
        }
        return 0;
    }
    if (i != 1)
        return 0;
    switch (mField102c - 1)
    {
    case 0: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x34); }
    case 1: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x38); }
    case 2: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x3c); }
    case 3: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x40); }
    case 4: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x44); }
    case 5: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x48); }
    default: return 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00c24760
// ---------------------------------------------------------------------------
// @ 0x00c24760
void cCreatureBase::FUN_00c24760()
{
    MOPS(this)->FUN_00c22240();
    void* tribe = mpField1014;
    if (!tribe)
        goto END;
    {
        MOPS(tribe)->FUN_00c95cc0(this);
        void* sub = (u8*)this + 0xc0;
        if (((u8 (__thiscall*)(void*))VT(sub)[0x58 / 4])(sub))
        {
            ((void (__thiscall*)(void*, u32))VT(this)[0xe4 / 4])(this, 0x1572074);
        }
        else
        {
            u32 v = (u32)FUN_00b6f0c0(*(u32*)((u8*)tribe + 0x234));
            ((void (__thiscall*)(void*, u32))VT(this)[0xe4 / 4])(this, v);
        }
        void* strat = FUN_00cd40b0();
        void* r = (void*)((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
        if (r)
        {
            strat = FUN_00cd40b0();
            r = (void*)((void* (__thiscall*)(void*, void*))VT(strat)[0x6c / 4])(strat, this);
            MOPS(r)->FUN_00ccc400();
        }
        sub = (u8*)this + 0xc0;
        if (((u8 (__thiscall*)(void*))VT(sub)[0x58 / 4])(sub))
        {
            *(void**)((u8*)gP_0169b41c + 0x14) = this;
            u32 pop = MOPS(tribe)->FUN_00c8f370();
            *(u32*)((u8*)gP_0169b41c + 0xc) = pop;
            void* r3 = (void*)((void* (__thiscall*)(void*, u32, u32))VT((u8*)tribe + 0x120)[0x2c / 4])((u8*)tribe + 0x120, 0, 1);
            MOPS(FUN_00b3d3e0())->FUN_00dd8640(0x11c9ad29, 0x182cd6ce, r3);
        }
        MOPS((u8*)mpFieldb4c + 8)->FUN_00bc97f0(0, 0x200, gF_01486110, 0);
    }
END:
    {
        void* sub = (u8*)this + 0x58;
        ((void (__thiscall*)(void*))VT(sub)[0x34 / 4])(sub);
    }
    *(u32*)((u8*)mpFieldb4c + 0x5fc) |= 2;
    u32 noun = *(u32*)((u8*)this + 0x1030);
    if (noun)
        MOPS(FUN_00b3d300())->FUN_00b225d0((void*)noun);
    u32 noun2 = *(u32*)((u8*)this + 0x1030);
    if (noun2)
    {
        *(u32*)((u8*)this + 0x1030) = 0;
        ((void (__thiscall*)(void*))VT((void*)noun2)[1])((void*)noun2);
    }
    MOPS(this)->FUN_00c1d400(0x3a616fee, 0x715fb4a7);
}

// ---------------------------------------------------------------------------
// 0x00c248d0
// ---------------------------------------------------------------------------
// @ 0x00c248d0
void cCreatureBase::FUN_00c248d0(i32 param_2)
{
    if (!mField135)
        return;
    if (((u8 (__thiscall*)(void*))VT(this)[0x2c / 4])(this))
        return;
    f32 fdt = (f32)param_2;
    if (param_2 < 0)
        fdt = fdt + gF_013f4fd0;
    fdt = fdt * gF_013f9428;
    f32 saved = fdt;
    ((void (__thiscall*)(void*, f32))VT(this)[0x70 / 4])(this, fdt);
    f32 fvar;
    if (MOPS(this)->FUN_00c0c130())
        fvar = 0.0f;
    else
        fvar = MOPS(this)->FUN_00c0c070();
    mFieldb80 = fvar;
    if (mpFieldb4c && *(u32*)mpFieldb4c && !mField1010)
    {
        if (!mFieldb5e)
            MOPS(this)->FUN_00c17de0(saved);
        u32 flags = *(u32*)((u8*)mpFieldb4c + 0x5fc);
        u32 a = (u32)MOPS(this)->FUN_00cee330();
        u32 b = (u32)MOPS(mpFieldb4c)->FUN_00bca2c0();
        flags |= (a ? 4 : 0);
        flags |= ((mFlags110 & 0x100) ? 0 : 8);
        flags |= (b ? 0x40 : 0);
        if (mFieldeac == 0) flags |= 0x400;
        else if (mFieldeac == 1) flags |= 0x800;
        else if (mFieldeac == 2) flags |= 0x1000;
        u32 v = (u32)MOPS((u8*)mpFieldb4c + 8)->FUN_00bc9980(saved);
        MOPS(FUN_00b3d380())->FUN_00b316c0();
        void* pw = (u8*)mpFieldb4c;
        MOPS(this)->FUN_00d995f0(saved, 0.0, *(u32*)pw, this, (void*)((u8*)pw + 0x1d0),
                                 *(u32*)((u8*)pw + 0x5e8), flags, v);
        if (!mFieldb5e)
        {
            if (MOPS(this)->FUN_00c0e420())
            {
                if (mpAnimWorld_b54)
                {
                    if (MOPS(mpAnimWorld_b54)->FUN_00a02ba0() <= 0)
                        MOPS(this)->FUN_00c14750(0);
                }
            }
        }
    }
    if (!mFieldb5e)
    {
        ((void (__thiscall*)(void*, f32))VT(this)[0x64 / 4])(this, fdt);
        ((void (__thiscall*)(void*, f32))VT(this)[0x68 / 4])(this, fdt);
    }
    if (mField2b0 == 3 && !(mFlags110 & 0x1000) && mField137)
        ((void (__thiscall*)(void*))VT(this)[0x58 / 4])(this);
    if (mpField1030)
    {
        f32 d = gF_0143ee00;
        if (FUN_00b3d280())
        {
            struct { f32 a, b, c, d; } q;
            MOPS(FUN_00b3d280())->FUN_00b137d0(&q);
            f32* p = (f32*)((void* (__thiscall*)(void*))VT((u8*)mpField1030 + 0x70)[0x2c / 4])((u8*)mpField1030 + 0x70);
            f32 dx = p[0] - q.a;
            f32 dy = p[1] - q.b;
            f32 dz = p[2] - q.c;
            f32 dist = dx*dx + dy*dy + dz*dz;
            f32 sel = (dist > gF_0143ee00) ? d : dist;
            f32 cur = (f32)((f64 (__thiscall*)(void*))VT((u8*)this + 0xc0)[0x70 / 4])((u8*)this + 0xc0);
            f32 v2 = (sel * gF_0146aaf0) * (gF_01470f1c - cur) + cur;
            u32 e = (u32)((void* (__thiscall*)(void*, f32))VT((u8*)this + 0xc0)[0x2c / 4])((u8*)this + 0xc0, v2);
            MOPS(mpField1030)->FUN_00c3f160(e);
        }
    }
    MOPS(this)->FUN_00c213d0((u32)param_2);
    if (!mField1010 && mpAnimWorld_b54)
        *(u32*)((u8*)mpAnimWorld_b54 + 0x14c) = 0;
}
