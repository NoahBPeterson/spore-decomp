// Slice s00bd70b0 (0x00bd70b0..0x00bd8a06) — the large "civ / cheat mode" simulator
// object (SP::cSPSimPlanetHighLOD and its helpers): cheat-mode command dispatch, a
// quaternion->matrix helper, and a handful of small predicate/accessor stubs.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

#pragma warning(disable: 4100)

typedef unsigned int uint;

// thiscall function-pointer typedefs (avoids C3865 on inline casts)
typedef int   (__thiscall *Fn_i_v)(void*);
typedef int   (__thiscall *Fn_i_vi)(void*, int);
typedef int   (__thiscall *Fn_i_vii)(void*, int, int);
typedef int   (__thiscall *Fn_i_viii)(void*, int, int, int);
typedef char  (__thiscall *Fn_c_v)(void*);
typedef void  (__thiscall *Fn_x_v)(void*);
typedef void* (__thiscall *Fn_p_vi)(void*, int);

// ---------------------------------------------------------------------------
// External callees.  Names/addresses are supplied by the linker relocations and
// masked by the verifier, so the exact spellings do not matter.
// ---------------------------------------------------------------------------
struct EastlString { void assign(const char* p, const char* e); };

struct Obj {
    void* m00b18460(int);
    void* m00bfc380(int);
    void* m00c884f0(int);
    void* m00ac0320(int);
    void  m00ac8d40();
    void  m00bbe5f0();
    void  m00ff03b0(int);
    void  m00ff03c0(float);
};
struct ObjMsgsvr {
    void m_send(void*, int);
};

extern "C" void* __cdecl FUN_00bd6eb0(void*);
extern "C" void* __cdecl FUN_00bd7400();
extern "C" void  __cdecl FUN_00bd69d0(void*);
extern "C" void  __cdecl FUN_00bd6940(void*);
extern "C" void  __cdecl FUN_00bd68c0(void*);
extern "C" void* __stdcall FUN_00b3d480(int);
extern "C" void  __cdecl FUN_00bd571db0(int, int, int, int, int);

// absolute-address data symbols (relocation-masked)
extern char DAT_01a56aba;
extern char DAT_018ea2cc;
extern char DAT_018eb106;
extern int  DAT_0168bcf8;
extern int  DAT_0168bcfc;
extern char DAT_0168bcf4;
extern "C" void __cdecl FUN_00c2e4e0(void*, int);

// ===========================================================================
// @ 0x00bd70b0 — destructor of the cheat/gonzago handler wrapper.
// ===========================================================================
struct cGonzagoSubsystem { void Destroy(); };
void __fastcall FUN_00bd70b0(int* this_)
{
    this_[0] = 0x14683d0;
    this_[1] = 0x1468380;
    this_[2] = 0x146837c;
    int h = this_[9];
    if (h != 0) {
        this_[9] = 0;
        FUN_00bd571db0(h, this_[10], this_[0xb], this_[0xc], this_[0xd]);
    }
    ((cGonzagoSubsystem*)(this_ + 1))->Destroy();
}

// ===========================================================================
// @ 0x00bd7110 — dispatch a cheat message to the "factory" subsystem.
// ===========================================================================
void __cdecl FUN_00bd7110(int param_1, int param_2)
{
    if (param_1 == 0) return;
    void* obj = *(void**)(param_1 + 0x120);
    if (obj == 0) return;
    void** vt = *(void***)obj;
    int* piVar1 = (int*)((Fn_p_vi)vt[0x0c / 4])(obj, 0x4f396a66);
    if (piVar1 == 0) return;
    void** vt2 = *(void***)piVar1;
    int uVar2 = ((Fn_i_vii)vt2[0x90 / 4])(piVar1, param_1, param_2);
    FUN_00bd6eb0((void*)uVar2);
}

// ===========================================================================
// @ 0x00bd7160 — (complex) populate civ model nouns; approximate.
// ===========================================================================
extern "C" void* __cdecl FUN_00b25ca0();
extern "C" void* __cdecl FUN_00bef6c0();
extern "C" int   __cdecl FUN_00c9e6d0(int, int);
void FUN_00bd7160(void)
{
    int* piVar2 = (int*)FUN_00b25ca0();
    int iVar1 = piVar2[1];
    for (int iVar8 = *piVar2; iVar8 != iVar1; iVar8 += 4) {
        piVar2 = (int*)FUN_00bef6c0();
        if (*piVar2 == piVar2[1]) continue;
        for (int iVar3 = 0; iVar3 < 5; ++iVar3) {
            int iVar4 = FUN_00c9e6d0(iVar3, 0);
            (void)iVar4;
        }
    }
}

// ===========================================================================
// @ 0x00bd7270 — quaternion (x,y,z,w) -> row-major 4x4 matrix.
// ===========================================================================
void FUN_00bd7270(float* m, float* q)
{
    float x = q[0];
    float y = q[1];
    float z = q[2];
    float w = q[3];
    m[0]  = 1.0f - (z * z + y * y) * 2.0f;
    m[1]  = (w * z + y * x) * 2.0f;
    m[2]  = (z * x - w * y) * 2.0f;
    m[3]  = 0.0f;
    m[4]  = (y * x - w * z) * 2.0f;
    m[5]  = 1.0f - (z * z + x * x) * 2.0f;
    m[7]  = 0.0f;
    m[6]  = (w * x + z * y) * 2.0f;
    m[8]  = (w * y + z * x) * 2.0f;
    m[9]  = (z * y - w * x) * 2.0f;
    m[0xb] = 0.0f;
    m[10] = 1.0f - (y * y + x * x) * 2.0f;
    m[0xc] = 0.0f;
    m[0xd] = 0.0f;
    m[0xe] = 0.0f;
    m[0xf] = 1.0f;
}

// ===========================================================================
// @ 0x00bd7400 — (complex) create+pose a civ "cheat" noun; approximate.
// ===========================================================================
void* __cdecl FUN_00bd7400()
{
    return 0;
}

// ===========================================================================
// @ 0x00bd78e0 — reset the "Cheat Object" scratch string.
// ===========================================================================
void __stdcall FUN_00bd78e0(EastlString* s)
{
    s->assign("Cheat Object", "");
}

// ===========================================================================
// thiscall methods of the simulator object (this in ecx, rest on stack).
// ===========================================================================
struct Sim {
    void  FUN_00bd75f0(int* p2);
    int   FUN_00bd7760(int p2, int* p3);
    void* FUN_00bd7a10(int p2);
    char  FUN_00bd7ad0(int* p2);
    char  FUN_00bd7b90(int* p2);
    int   FUN_00bd7ca0(int p2);
    void  FUN_00bd7d10(int p2, float p3);
    void  FUN_00bd7f70(int* p2, float* p3);
    bool  FUN_00bd7fc0(int p2);
    bool  FUN_00bd7c60(int p1);
};

// ===========================================================================
// @ 0x00bd75f0 — if the message noun is a cheat-handler, respawn the cheat.
// ===========================================================================
void Sim::FUN_00bd75f0(int* param_2)
{
    char* this_ = (char*)this;
    if (*(char*)(this_ + 0x20) != 0 && param_2 != 0) {
        void** vt = *(void***)param_2;
        int* piVar1 = (int*)((Fn_p_vi)vt[0xb8 / 4])(param_2, 0x17f243b);
        void** vt2 = *(void***)piVar1;
        int iVar2 = ((Fn_i_v)vt2[0x38 / 4])(piVar1);
        if (iVar2 == 0x4f396a66 ||
            (iVar2 = ((Fn_i_v)vt2[0x38 / 4])(piVar1)) == (int)0xee9b2232) {
            FUN_00bd7400();
        }
    }
}

// ===========================================================================
// @ 0x00bd7640 — cheat-message dispatch (position/state commands).
// ===========================================================================
void __cdecl FUN_00bd7640(int param_1, int param_2)
{
    int iVar1 = 0;
    int iVar2 = 0;
    DAT_0168bcf8 = param_2;
    if (param_1 != 0) {
        int* p = *(int**)(param_1 + 0x120);
        if (p != 0) iVar1 = ((Fn_i_vi)(*(void***)p)[0xc / 4])(p, 0x4f396a66);
        else iVar1 = 0;
        p = *(int**)(param_1 + 0x120);
        if (p != 0) iVar2 = ((Fn_i_vi)(*(void***)p)[0xc / 4])(p, 0xee9b2232);
        else iVar2 = 0;
    }
    switch (param_2) {
    case 8000:
        if (iVar1 != 0) FUN_00bd69d0((void*)param_1);
        if (iVar2 != 0) FUN_00bd6940((void*)param_1);
        break;
    case 0x1f41:
    case 0x1f42:
    case 0x1f43:
        ((void(__cdecl*)(int, int, int))FUN_00bd7110)(param_1, DAT_0168bcfc, param_2);
        return;
    case 0x1f44:
        if (iVar2 != 0) {
            FUN_00c2e4e0((void*)iVar2, 0);
            return;
        }
        break;
    case 0x1f46:
    case 0x1f47:
    case 0x1f48:
    case 0x1f49:
    case 0x1f4a:
    case 0x1f4b:
        DAT_0168bcfc = param_2;
        FUN_00bd68c0((void*)param_1);
        return;
    case 0x1f4c:
        DAT_0168bcf4 = (DAT_0168bcf4 == 0);
        return;
    case 0x1f4d:
        FUN_00bd7160();
        return;
    }
}

// ===========================================================================
// @ 0x00bd7760 — (complex) cheat command handler; approximate.
// ===========================================================================
int Sim::FUN_00bd7760(int param_2, int* param_3)
{
    if (param_2 == 0x1a0219e) {
        if (param_3[2] != 3 && param_3[2] != 4) return 0;
    }
    return 1;
}

// ===========================================================================
// @ 0x00bd7900 — (complex) spawn cheat nouns from two game-data vectors.
// ===========================================================================
extern "C" void* __cdecl FUN_00b3d300();
extern "C" void* __cdecl FUN_00b21340(void*, void*, void*, void*, void*, void*);
extern "C" void* __cdecl FUN_00b20c60(void*, int);
void __fastcall FUN_00bd7900(int* param_1)
{
    ((Fn_x_v)*(void**)(*param_1 + 0x24))(param_1);
    void* nm = FUN_00b3d300();
    int* v = (int*)FUN_00b21340(nm, (void*)FUN_00bd7400, (void*)FUN_00bd7400,
                               (void*)FUN_00bd7400, (void*)FUN_00bd7400, (void*)0);
    int n = (v[2] - v[1]) >> 2;
    for (int i = 0; i < n; ++i) {
        void* noun = FUN_00b20c60(FUN_00b3d300(), 0x2a37e35);
        if (noun)
            ((Fn_i_vi)*(void**)(*(int*)noun + 0x0c))(noun, 0x2a37e34);
        FUN_00bd7400();
    }
}

// ===========================================================================
// @ 0x00bd7a10 — Object::Cast (multi-base lookup).
// ===========================================================================
void* Sim::FUN_00bd7a10(int param_2)
{
    char* this_ = (char*)this;
    if (param_2 == (int)0xee3f516e || param_2 == 0x3d5c477) return this_;
    void* r = ((Obj*)this_)->m00b18460(param_2);
    if (r != 0) return r;
    r = ((Obj*)(this_ + 0x38))->m00bfc380(param_2);
    if (r != 0) return r;
    return ((Obj*)(this_ + 0x100))->m00c884f0(param_2);
}

// ===========================================================================
// @ 0x00bd7a80 — this-adjusting thunk (returns this+0xc8, or 0).
// ===========================================================================
int __fastcall FUN_00bd7a80(int param_1)
{
    if (param_1 - 0x38) return param_1 + 200;
    return 0;
}

// ===========================================================================
// @ 0x00bd7ab0 — this-adjusting virtual tail thunk.
// ===========================================================================
void __fastcall FUN_00bd7ab0(int param_1)
{
    char* adj = (char*)param_1 - 0x38;
    int* o = *(int**)adj;
    int* r = (int*)((Fn_i_v)*(void**)((char*)o + 0x30))(adj);
    ((Fn_x_v)*(void**)(*r + 0x4c))(r);
}

// ===========================================================================
// @ 0x00bd7ad0 — Simulator::ISimulatorSerializable::Write.
// ===========================================================================
extern "C" char __cdecl FUN_00b18590(void*, void*);
extern "C" char __cdecl FUN_00bfc4a0(void*, void*);
extern "C" char __cdecl FUN_00c88a90(void*, void*);
extern "C" void __cdecl FUN_00692f90(void*, void*, void*, int);
extern "C" char __cdecl FUN_00692900(void*, void*);
extern "C" void __cdecl WriteUint32(void*, void*, int, int);
char Sim::FUN_00bd7ad0(int* param_2)
{
    char* this_ = (char*)this;
    int* piVar4 = (int*)((Fn_i_v)*(void**)(*param_2 + 0x20))(param_2);
    unsigned int tag = 0x3d5c477;
    void* uVar5 = (void*)((Fn_i_v)*(void**)(*piVar4 + 0x18))(piVar4);
    WriteUint32(uVar5, &tag, 1, 0);
    char cVar2 = FUN_00b18590(this_, param_2);
    char cVar3 = FUN_00bfc4a0(this_ + 0x38, param_2);
    bool bVar1 = (cVar3 != 0 && cVar2 != 0);
    cVar2 = FUN_00c88a90(this_ + 0x100, param_2);
    bVar1 = (cVar2 != 0 && bVar1);
    char cStack_a14[0x9dc];
    FUN_00692f90(cStack_a14, this_, (void*)0x156e2a0, 0x1a80d26);
    cVar2 = FUN_00692900(cStack_a14, param_2);
    return (cVar2 != 0 && bVar1) ? 1 : 0;
}

// ===========================================================================
// @ 0x00bd7b90 — Simulator::ISimulatorSerializable::Read.
// ===========================================================================
extern "C" char __cdecl FUN_00b18600(void*, void*);
extern "C" char __cdecl FUN_00bfc540(void*, void*);
extern "C" char __cdecl FUN_00c88b00(void*, void*);
extern "C" char __cdecl FUN_00693e10(void*, void*);
extern "C" void __cdecl ReadInt32(void*, void*, int, int);
char Sim::FUN_00bd7b90(int* param_2)
{
    char* this_ = (char*)this;
    int* piVar3 = (int*)((Fn_i_v)*(void**)(*param_2 + 0x20))(param_2);
    void* uVar4 = (void*)((Fn_i_v)*(void**)(*piVar3 + 0x18))(piVar3);
    int tag = 0;
    ReadInt32(uVar4, &tag, 1, 0);
    char cVar2 = FUN_00b18600(this_, param_2);
    bool bVar1 = (cVar2 != 0 && tag == 0x3d5c477);
    cVar2 = FUN_00bfc540(this_ + 0x38, param_2);
    bVar1 = (cVar2 != 0 && bVar1);
    cVar2 = FUN_00c88b00(this_ + 0x100, param_2);
    bVar1 = (cVar2 != 0 && bVar1);
    char cStack_a14[0x9dc];
    FUN_00692f90(cStack_a14, this_, (void*)0x156e2a0, 0x1a80d26);
    cVar2 = FUN_00693e10(cStack_a14, param_2);
    return (cVar2 != 0 && bVar1) ? 1 : 0;
}

// ===========================================================================
// @ 0x00bd7c60 — predicate: this->[0x1dc] == id.
// ===========================================================================
bool Sim::FUN_00bd7c60(int param_1)
{
    return *(int*)((char*)this + 0x1dc) == param_1;
}

// ===========================================================================
// @ 0x00bd7c80 — advance a small counter (0 -> 0+1, else +5).
// ===========================================================================
void __fastcall FUN_00bd7c80(char* this_)
{
    int* p = (int*)(this_ + 0x214);
    int v = *p;
    *p = (v == 0 ? 5 : 1) + v;
}

// ===========================================================================
// @ 0x00bd7ca0 — Object cast on the +0x1f4 base.
// ===========================================================================
int Sim::FUN_00bd7ca0(int param_2)
{
    char* this_ = (char*)this;
    if (param_2 == (int)0xee3f516e) return (int)this_;
    if (param_2 == (int)0xee9b2232) return (int)this_;
    int r = (int)((Obj*)(this_ + 0x1f4))->m00ac0320(param_2);
    if (r != 0) return r;
    r = (int)((Obj*)this_)->m00b18460(param_2);
    if (r != 0) return r;
    return (int)((Obj*)(this_ + 0x120))->m00c884f0(param_2);
}

// ===========================================================================
// @ 0x00bd7d10 — set the two "hover/target" values and forward to the gadget.
// ===========================================================================
void Sim::FUN_00bd7d10(int param_2, float param_3)
{
    char* this_ = (char*)this;
    *(int*)(this_ + 0x74c) = param_2;
    *(float*)(this_ + 0x748) = param_3;
    Obj* o = *(Obj**)(this_ + 0x2f0);
    if (o != 0) {
        o->m00ff03b0(param_2);
        o->m00ff03c0(param_3);
    }
}

// ===========================================================================
// @ 0x00bd7d60 — predicate: flag set and timer > 50.
// ===========================================================================
int __fastcall FUN_00bd7d60(char* this_)
{
    if (*(char*)(this_ + 0x698) != 0 && *(float*)(this_ + 0x304) > 50.0f) return 1;
    return 0;
}

// ===========================================================================
// @ 0x00bd7d90 — (complex) civ-mode strategy start; approximate.
// ===========================================================================
extern "C" void* __cdecl FUN_00cf74c0(int, int, int, int);
extern "C" void  __cdecl FUN_00cf9040(int, int, int, int, int, int, int);
extern "C" void  __cdecl SP_cSPTimer_Restart(void*);
void __fastcall FUN_00bd7d90(char* this_)
{
    void* obj = *(void**)(this_ + 0x120);
    char cVar1 = ((Fn_c_v)*(void**)(*(int*)(this_ + 0x120) + 0x58))(obj);
    if (cVar1 != 0 && *(char*)(this_ + 0x698) == 0) {
        int uVar2 = ((Fn_i_viii)*(void**)(*(int*)(this_ + 0x120) + 0x2c))(obj, 0, 1, 0);
        FUN_00cf74c0((int)this_, 0x864de15c, 0xaa9a8ed7, uVar2);
        FUN_00cf9040((int)this_, 0x864de15c, 0xaa9a8ed7, uVar2, 0, 1, 0);
    }
    *(char*)(this_ + 0x698) = 1;
    SP_cSPTimer_Restart(this_ + 0x6a0);
}

// ===========================================================================
// @ 0x00bd7df0 — predicate: flag set and timer < 50.
// ===========================================================================
int __fastcall FUN_00bd7df0(char* this_)
{
    if (*(char*)(this_ + 0x6c0) != 0 && 50.0f > *(float*)(this_ + 0x304)) return 1;
    return 0;
}

// ===========================================================================
// @ 0x00bd7e20 — predicate: timer <= 50.
// ===========================================================================
int __fastcall FUN_00bd7e20(char* this_)
{
    if (*(float*)(this_ + 0x304) <= 50.0f) return 1;
    return 0;
}

// ===========================================================================
// @ 0x00bd7e40 — trigger-manager gate then re-arm.
// ===========================================================================
extern "C" void* __cdecl FUN_00b3d4d0();
extern "C" void* __cdecl FUN_00b3d480p(int);
extern "C" char  __cdecl FUN_00ac8d60p(void*);
void __fastcall FUN_00bd7e40(char* this_)
{
    *(char*)(this_ + 0x2e1) = 0;
    int v = *(int*)(this_ + 0x29c);
    if (v >= 0 && v < 3) {
        void* t = FUN_00b3d4d0();
        if (*(int*)((char*)t + 0x2c) != 1 && *(int*)((char*)t + 0x2c) != 2) {
            void* r = FUN_00b3d480p((int)this_);
            if (FUN_00ac8d60p(r) == 0) return;
        }
        *(char*)(this_ + 0x6c0) = 0;
        SP_cSPTimer_Restart(this_ + 0x6c8);
        *(char*)(this_ + 0x2a0) = 1;
    }
}

// ===========================================================================
// @ 0x00bd7ea0 — forward the player civ into the trigger/audio systems.
// ===========================================================================
extern "C" void* __cdecl FUN_00b3d300p();
extern "C" void* __fastcall FUN_00b25fb0(void*);
extern "C" void* __stdcall FUN_00b3d480p2(int, int);
extern "C" void  __fastcall FUN_00ac8d00p(void*);
struct Fwd { void a(); void b(); void c(); };
void __fastcall FUN_00bd7ea0(char* this_)
{
    *(char*)(this_ + 0x2e4) = 0;
    void* civ = FUN_00b25fb0(FUN_00b3d300p());
    void* r = FUN_00b3d480p2((int)this_, (int)civ);
    FUN_00ac8d00p(r);
}

// ===========================================================================
// @ 0x00bd7ed0 — decrement a counter, clamped above 20.
// ===========================================================================
void __fastcall FUN_00bd7ed0(char* this_)
{
    int* p = (int*)(this_ + 0x64c);
    if (*p > 20) *p = *p - 1;
}

// ===========================================================================
// @ 0x00bd7ef0 — string-key selector.
// ===========================================================================
void* __stdcall FUN_00bd7ef0(int param_1)
{
    switch (param_1) {
    case 0x1a55e4d: return &DAT_01a56aba;
    case 0xecade42: return &DAT_018ea2cc;
    default:        return &DAT_018eb106;
    }
}

// ===========================================================================
// @ 0x00bd7f30 — forward (this) into trigger/audio.
// ===========================================================================
void __fastcall FUN_00bd7f30(int param_1)
{
    void* r = FUN_00b3d480(param_1);
    ((Obj*)r)->m00ac8d40();
}

// ===========================================================================
// @ 0x00bd7f70 — read the "highlight" position + radius.
// ===========================================================================
void Sim::FUN_00bd7f70(int* param_2, float* param_3)
{
    char* this_ = (char*)this;
    param_2[0] = *(int*)(this_ + 0x51c);
    param_2[1] = *(int*)(this_ + 0x520);
    param_2[2] = *(int*)(this_ + 0x524);
    *param_3 = 8.0f;
}

// ===========================================================================
// @ 0x00bd7fc0 — predicate: selection matches and "needs upgrade" meter >= 100.
// ===========================================================================
bool Sim::FUN_00bd7fc0(int param_2)
{
    int* param_1 = (int*)this;
    int v = ((Fn_i_v)*(void**)(*param_1 + 0x4c))((void*)param_1);
    if (((param_2 != v) && (param_2 == param_1[0x1d7])) &&
        (*(float*)((char*)param_1 + 0x758) >= 100.0f)) {
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00bd8000 — register this object with the message server for 5 topics.
// ===========================================================================
extern "C" void* __cdecl FUN_00bd7dcc0();
void __fastcall FUN_00bd8000(int param_1)
{
    int iVar2 = (param_1 != 0) ? param_1 + 0x20c : 0;
    ((ObjMsgsvr*)FUN_00bd7dcc0())->m_send((void*)iVar2, 0x5416d55);
    iVar2 = (param_1 != 0) ? param_1 + 0x20c : 0;
    ((ObjMsgsvr*)FUN_00bd7dcc0())->m_send((void*)iVar2, 0x56e50f1);
    iVar2 = (param_1 != 0) ? param_1 + 0x20c : 0;
    ((ObjMsgsvr*)FUN_00bd7dcc0())->m_send((void*)iVar2, 0x40fafdf);
    iVar2 = (param_1 != 0) ? param_1 + 0x20c : 0;
    ((ObjMsgsvr*)FUN_00bd7dcc0())->m_send((void*)iVar2, 0x5f74817);
    int p = (param_1 != 0) ? param_1 + 0x20c : 0;
    ((ObjMsgsvr*)FUN_00bd7dcc0())->m_send((void*)p, 0x6787056);
}

// ===========================================================================
// @ 0x00bd80d0 — return the "level" of a noun (50 for the player civ).
// ===========================================================================
extern "C" void* __cdecl FUN_00b1f9d0p();
extern "C" float __cdecl FUN_00d00d00p(int);
float __cdecl FUN_00bd80d0(int* param_1)
{
    void* civ = FUN_00b25fb0(FUN_00b3d300p());
    if ((void*)param_1 == civ) return 50.0f;
    int uVar3 = (int)FUN_00b1f9d0p();
    uVar3 = ((Fn_i_vi)*(void**)(*param_1 + 0x4c))((void*)param_1, uVar3);
    return FUN_00d00d00p(uVar3);
}

// ===========================================================================
// @ 0x00bd8110 — reset the terraforming manager.
// ===========================================================================
extern "C" void* __stdcall SP_TerraformingManager(int);
void __cdecl FUN_00bd8110(void)
{
    void* r = SP_TerraformingManager(0);
    ((Obj*)r)->m00bbe5f0();
}
