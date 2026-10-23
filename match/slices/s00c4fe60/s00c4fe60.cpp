// Slice s00c4fe60 -- SPGonzago/SPMission.obj (SP::cSPMissionEradicate / cSPMissionExplore
// message handlers, tag strings, herd helpers, serialize/deserialize helpers and small
// predicate/accessor thunks).
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail offsets of these
// classes are shifted, so offsets below come from the disassembly and are reached through
// byte-offset access on the object pointer and raw vtable calls.
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// retail callees with a plain __cdecl convention (self passed on the stack)
// ---------------------------------------------------------------------------------------------
extern "C" {
int   __cdecl FUN_00f47380(void* p);                 // operator delete
void* __cdecl FUN_01021260();                        // current active planet
void* __cdecl FUN_01021080();                        // universe context
void* __cdecl FUN_010666a0();                        // get minimap provider
void* __cdecl FUN_00b3d300();                        // SP_NounManager
void* __cdecl FUN_00b3d3e0();                        // SP::EventLog getter
void  __cdecl FUN_00aca360(void* p);
int   __cdecl FUN_00c03180(void* p);
void  __cdecl FUN_00c17350d(void* a, int b);         // 0x00c1735d raw 2-arg helper
void* __cdecl FUN_00c4e0f0v(void* a, int b, void* c);
void  __cdecl FUN_00b93c60(int n, void* p);
void* __cdecl FUN_00b21340(void* self, void* a, void* b, void* c, void* d, void* e);
void  __cdecl FUN_00fefbb0(void* ctx, void* animal, int n, void* herd, int eff);
void  __cdecl FUN_00e25bd0(void* begin, void* end);  // vector erase
void* __cdecl FUN_00dd8640(void* log, int a, int b, int c, int d, int e, int f);
int   __cdecl FUN_00fefe90();
void  __cdecl FUN_0093ac80(void* stream, void* p);   // 0x0093ac80 ReadBool
void  __cdecl FUN_0093a780(void* stream, void* p, int n, int f);   // 0x0093a780
void  __cdecl FUN_0093a9a0(void* stream, void* p, int n);          // 0x0093a9a0
void  __cdecl FUN_0093aa70(void* stream, void* p, int n, int f);   // 0x0093aa70
void  __cdecl FUN_00933960(void* ws);                              // 0x00933960
int   __cdecl FUN_0041e050(void* out, void* fmt, int v);          // 0x0041e050 WStr_Format
void  __cdecl FUN_006a1250(void* a, int key, void* out);           // 0x006a1250 SP::GetPropertyAsKey
void  __cdecl FUN_004b5ad0(void* pos, void* val);    // 0x004b5ad0 SpVector<Vector3>::DoInsertValue
void  __cdecl FUN_00829110(void* out, void* a, void* b, void* c, void* d);  // 0x00829110
void* __cdecl FUN_00c23e40d(void* p);                // 0x00c23e40 cSPCreatureCitizen::GetCity
void* __cdecl FUN_00c0bbd0d(void* p);                // 0x00c0bbd0 cSPCreatureBase::GetSpeciesProfile
int   __cdecl FUN_00bd8160d(void* p);                // 0x00bd8160
void  __cdecl FUN_00bd8140d(void* p, int a);         // 0x00bd8140
void* __cdecl FUN_00b3d480d(void* p);                // 0x00b3d480
void* __cdecl FUN_00ae33b0d(void* p);                // 0x00ae33b0 cSPMissionBiosphere::OnAbduction
void* __cdecl FUN_00c04590d(void* p);                // 0x00c04590 Get()
int   __cdecl FUN_00e31100d();                       // 0x00e31100 UTFWin::IWinProc::GetPriority
void* __cdecl FUN_00c4bdc0v(void* out, void* vec, int v);   // 0x00c4bdc0
}

// ---------------------------------------------------------------------------------------------
// ecx-receiver stubs (thiscall): modeled as members so calls emit `mov ecx,obj; push args; call`
// ---------------------------------------------------------------------------------------------
class Mob
{
  public:
    void* GetTargetPlanet();              // 0x00970b30 SP::cSPMission::GetTargetPlanet
    void  OnCombatantKilled(void* p);     // 0x00c4fe60
    void  OnCityDestroyed(void* p);       // 0x00c50190
    void  DestroyHerds();                 // 0x00c504a0
    void  OnPlanetDeactivate();           // 0x00c505a0
    void  OnPlanetActivate();             // 0x00c50600
    void  HandleMessage(u32 msg, void* arg);  // 0x00c4a6b0 cSPMission::HandleMessage
    int   GetTagStringBase(int tag, void* o); // 0x00c491c0 cSPMission::GetTagString
    int   GetDiseaseEffectID(int a);      // 0x00c4bd60
    void  GetText(int key, void* out);    // 0x00c487d0 SP::cSPMission::GetText
    void  TriggerUIUpdate();              // 0x00c47d80
    void  PostWarningEvent();             // 0x00c4f9d0
    void  UnkEin();                       // 0x00c4ed20
    void  UnkFfa();                       // 0x00c4fa40
    void  UnkF160();                      // 0x00c4f160
    void  UnkF320();                      // 0x00c4f320
    void  UnkFC00(void* a);               // 0x00c4fc00
    void  Unk471c0();                     // 0x00c471c0
    void  Unk472e0();                     // 0x00c472e0
    void  Unk47a10();                     // 0x00c47a10
    void  Unk48e50(int id);               // 0x00c48e50
    void  SetState(int v);                // 0x00c4eec0
    int   UnkC2b0();                      // 0x00c4c2b0
    void  BaseGetProp(void* out);          // 0x00c4bda0
    void  SerializeRecord(void* rec);     // 0x00c50ba0
    int   GetClosestDiseasedAnimalInner(void* a, void* out); // 0x00c4bdc0
    int   GetUIntField();                 // 0x008e7f80
};

class Win
{
  public:
    void  RemoveIcon(void* city, int a, int b);            // 0x00e0f9c0
    void  AddIcon(void* city, void* local, int a, int b);  // 0x00e10580
    Win*  GetWin();                                        // 0x01067e60
};

class Prop
{
  public:
    char GetKey(int key, void* out);      // vtable slot 0x24
    int* GetUInt();                       // 0x0041ea00
};

class Ref
{
  public:
    void* Assign(void* p);                // 0x00b5f950 AutoRefCount<IWinText>::operator=
};

// serialization stream interfaces (vtable slots named by role)
class IOutStream
{
  public:
    virtual void* s0(); virtual void* s1(); virtual void* s2(); virtual void* s3();
    virtual void* s4(); virtual void* s5(); virtual void* s6();
    virtual void  Finish_1c();      // slot 7 (0x1c)
    virtual void* GetWriter_20();   // slot 8 (0x20)
    virtual void* s9(); virtual void* s10(); virtual void* s11(); virtual void* s12();
    virtual void* s13(); virtual void* s14();
    virtual u32   GetVersion_3c();  // slot 15 (0x3c)
};

class IWriter
{
  public:
    virtual void* w0(); virtual void* w1(); virtual void* w2(); virtual void* w3();
    virtual void* w4(); virtual void* w5();
    virtual void* GetStream_18();   // slot 6 (0x18)
};

// SP::cSPUIEventLog (thiscall members; ret N gives the argument count)
class EventLog
{
  public:
    bool RegisterCallback(int id);                   // 0x00dd6b20  ret 4
    void RemoveEvent(int id, int b);                 // 0x00dd6d10  ret 8
    void ModifyEventText(int id, void* ws);          // 0x00dd6df0  ret 8
    int  AddEvent(int a, int b, int c, int d, int e, int f);  // 0x00dd8640 PostFeedbackEvent ret 0x18
};

// ---------------------------------------------------------------------------------------------
// byte-offset access against the retail layout
// ---------------------------------------------------------------------------------------------
static inline int  ld32(void* p, int off) { return *(int*)((char*)p + off); }
static inline void st32(void* p, int off, int v) { *(int*)((char*)p + off) = v; }
static inline u8   ldb(void* p, int off) { return *(u8*)((char*)p + off); }
static inline void stb(void* p, int off, u8 v) { *(u8*)((char*)p + off) = v; }
static inline void** vtbl(void* p) { return *(void***)p; }

extern float gFloatHundred_14d0;   // 0x013ec4d0
extern float gNegOneF_1bc;         // 0x013eb1bc
extern void* gEmptyA;              // 0x01667bac
extern void* gEmptyB;              // 0x01667bae

// ---------------------------------------------------------------------------------------------
// 0x00c4fe60 -- SP::cSPMissionEradicate::OnCombatantKilled (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4fe60
void __fastcall FUN_00c4fe60(void* ecx_this, void* edx, void* combatant)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    void* tp = self->GetTargetPlanet();
    void* ap = FUN_01021260();
    if (ap != tp)
        return;
    if (ld32(ecx_this, 0x1f4) != 0)
        return;
    int owner = ld32(ecx_this, 0x1f0);
    if (owner == 0x1e8763) {
        if (!combatant)
            return;
        void* pA = (*(void* (__thiscall**)(void*, u32))((char*)vtbl(combatant) + 0x5c))(combatant, 0x4f176642u);
        if (!pA)
            return;
        void* city = FUN_00c23e40d(pA);
        if (!city)
            return;
        if (ldb(pA, 0xb62) != 0) {
            stb(pA, 0xb62, 0);
            int n = FUN_00bd8160d(city) - 1;
            FUN_00bd8140d(city, (n > 0) ? n : 0);
            int c = ld32(ecx_this, 0x208) + 1;
            st32(ecx_this, 0x208, c);
            if (c < ld32(ecx_this, 0x204)) {
                self->TriggerUIUpdate();
                self->UnkFfa();
                return;
            }
            self->UnkF160();
            self->UnkFfa();
            return;
        }
        if (ldb(ecx_this, 0x214) != 0) {
            int c = ld32(ecx_this, 0x210) + 1;
            st32(ecx_this, 0x210, c);
            if (c < ld32(ecx_this, 0x20c)) {
                int id = ld32(ecx_this, 0x21c);
                char ok = ((EventLog*)FUN_00b3d3e0())->RegisterCallback(id);
                if (!ok)
                    st32(ecx_this, 0x21c, -1);
                if (ld32(ecx_this, 0x21c) == -1) {
                    gEmptyA = (void*)0x1667bac;
                    gEmptyB = (void*)0x1667bae;
                    self->GetText(0xed4727a9, &gEmptyA);
                    int eid = ((EventLog*)FUN_00b3d3e0())->AddEvent(
                        0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
                    st32(ecx_this, 0x21c, eid);
                    ((EventLog*)FUN_00b3d3e0())->ModifyEventText(eid, gEmptyA);
                    self->Unk48e50(eid);
                    FUN_00933960(&gEmptyA);
                    self->UnkFfa();
                    return;
                }
            } else {
                (*(void (__thiscall**)(void*))((char*)vtbl(ecx_this) + 0x70))(ecx_this);
                self->SetState(2);
                self->Unk472e0();
            }
        }
        self->UnkFfa();
        return;
    }
    if (owner == 0x389683f8) {
        if (!combatant)
            return;
        void* sp = (*(void* (__thiscall**)(void*, u32))((char*)vtbl(combatant) + 0x5c))(combatant, 0xd0036e08u);
        if (!sp)
            return;
        void* profile = FUN_00c0bbd0d(sp);
        if (profile != (void*)ld32(ecx_this, 0x16c))
            return;
        if (ldb(sp, 0xb62) != 0) {
            int eff = self->GetDiseaseEffectID(0);
            FUN_00c17350d(sp, eff);
            int c = ld32(ecx_this, 0x208) + 1;
            st32(ecx_this, 0x208, c);
            if (c < ld32(ecx_this, 0x204)) {
                self->TriggerUIUpdate();
                self->UnkFfa();
                return;
            }
            self->UnkF160();
            self->UnkFfa();
            return;
        }
        if (ldb(ecx_this, 0x214) != 0) {
            int c = ld32(ecx_this, 0x210) + 1;
            st32(ecx_this, 0x210, c);
            if (c >= ld32(ecx_this, 0x20c)) {
                (*(void (__thiscall**)(void*))((char*)vtbl(ecx_this) + 0x70))(ecx_this);
                self->SetState(2);
                self->Unk472e0();
                self->UnkFfa();
                return;
            }
            self->UnkEin();
            self->PostWarningEvent();
            gEmptyA = (void*)0x1667bac;
            gEmptyB = (void*)0x1667bae;
            self->GetText(0xed4727a9, &gEmptyA);
            int id = ld32(ecx_this, 0x21c);
            ((EventLog*)FUN_00b3d3e0())->ModifyEventText(id, gEmptyA);
            self->UnkFfa();
            return;
        }
        self->UnkFfa();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c50190 -- SP::cSPMissionEradicate::OnCityDestroyed (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50190
void __fastcall FUN_00c50190(void* ecx_this, void* edx, void* arg)
{
    (void)edx; (void)arg;
    Mob* self = (Mob*)ecx_this;
    if (ldb(ecx_this, 0x214) == 0)
        return;
    int v = ld32(ecx_this, 0x20c);
    void** vtp = vtbl(ecx_this);
    st32(ecx_this, 0x210, v);
    (*(void (__thiscall**)(void*))((char*)vtp + 0x70))(ecx_this);
    if (ld32(ecx_this, 0x1f4) != 2) {
        st32(ecx_this, 0x1f4, 2);
        self->TriggerUIUpdate();
    }
    self->Unk472e0();
    self->UnkFfa();
}

// ---------------------------------------------------------------------------------------------
// 0x00c501e0 -- SP::cSPMissionEradicate::GetTagString (ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c501e0
char __fastcall FUN_00c501e0(void* ecx_this, void* edx, int tag, void* out)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (tag == 0x3f80b6b3) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x1f8));
        return 1;
    }
    if (tag == (int)0xcd3e21a2) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x208));
        return 1;
    }
    if (tag == (int)0xc1a31746) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x1f8) - ld32(ecx_this, 0x208));
        return 1;
    }
    if (tag == (int)0xd34ef208) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x210));
        return 1;
    }
    if (tag == (int)0xbd31ee03) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x20c) - ld32(ecx_this, 0x210));
        return 1;
    }
    if (tag == 0x218e9bda) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x204) - ld32(ecx_this, 0x208));
        return 1;
    }
    if (tag == (int)0x85df68ab) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x204));
    }
    return (char)self->GetTagStringBase(tag, out);
}

// ---------------------------------------------------------------------------------------------
// 0x00c50300 -- SP::cSPMissionEradicate::GetClosestDiseasedAnimal (ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50300
char __fastcall FUN_00c50300(void* ecx_this, void* edx, void* param_2, void* outVec)
{
    (void)edx;
    int* pList;
    void* p = (void*)ld32(ecx_this, 0x17c);
    if (p && (pList = (int*)(*(void* (__thiscall**)(void*, u32))((char*)vtbl(p) + 0xc))(p, 0x4222277u)) != 0)
        pList = (int*)((char*)pList + 0x240);
    else
        pList = (int*)((char*)ecx_this + 0x220);
    int count = (int)(((char*)pList[1] - (char*)pList[0]) >> 2);
    void* v_begin = 0;
    void* v_end = 0;
    void* v_cap = 0;
    int i = 0;
    if (count > 0) {
        do {
            int sub = *(int*)(pList[0] + i * 4);
            int n = (int)((*(int*)(sub + 0x44) - *(int*)(sub + 0x40)) >> 2);
            int j = 0;
            if (n > 0) {
                do {
                    void* a = *(void**)(*(int*)(sub + 0x40) + j * 4);
                    if (ldb(a, 0xb62) != 0 && ldb(a, 0xb5e) == 0) {
                        void* pos = (*(void* (__thiscall**)(void*))((char*)vtbl((void*)((char*)a + 0xc0)) + 0x2c))((char*)a + 0xc0);
                        if (v_begin < v_cap) {
                            v_end = (char*)v_end + 12;
                            if (v_begin) {
                                *(int*)v_begin = *(int*)pos;
                                *((int*)v_begin + 1) = *((int*)pos + 1);
                                *((int*)v_begin + 2) = *((int*)pos + 2);
                            }
                        } else {
                            FUN_004b5ad0(v_end, pos);
                        }
                    }
                    j++;
                } while (j < n);
            }
            i++;
        } while (i < count);
    }
    char b = (v_begin != v_end);
    if (b) {
        int* r = (int*)FUN_00c4bdc0v((char*)outVec - 12, &v_begin, (int)param_2);
        *(int*)outVec = r[0];
        *((int*)outVec + 1) = r[1];
        *((int*)outVec + 2) = r[2];
    }
    if (v_begin && *(int*)((char*)v_begin - 4) != 0)
        FUN_00f47380(v_begin);
    return b;
}

// ---------------------------------------------------------------------------------------------
// 0x00c50460 -- FUN_00c50460 (SP::cSPMissionEradicate::OnTimerExpire)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50460
void __fastcall FUN_00c50460(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (ldb(ecx_this, 0x214) == 0)
        return;
    if (ld32(ecx_this, 0x1f4) != 0)
        return;
    st32(ecx_this, 0x1f4, 3);
    self->TriggerUIUpdate();
    self->Unk472e0();
    self->UnkFfa();
    self->Unk471c0();
}

// ---------------------------------------------------------------------------------------------
// 0x00c504a0 -- SP::cSPMissionEradicate::DestroyHerds
// ---------------------------------------------------------------------------------------------
// @ 0x00c504a0
void __fastcall FUN_00c504a0(void* ecx_this, void* edx)
{
    (void)edx;
    FUN_00b3d300();
    int eff;
    if (ld32(ecx_this, 0x180)) {
        int local = 0;
        FUN_006a1250((void*)ld32(ecx_this, 0x180), 0x7a2db2dd, &local);
        eff = local;
    } else {
        eff = -1;
    }
    int* begin = (int*)*(int*)((char*)ecx_this + 0x220);
    int* end = (int*)*(int*)((char*)ecx_this + 0x224);
    if (begin != end) {
        do {
            int sub = *begin;
            int n = (int)((*(int*)(sub + 0x44) - *(int*)(sub + 0x40)) >> 2);
            int j = 0;
            if (n > 0) {
                do {
                    void* a = *(void**)(*(int*)(sub + 0x40) + j * 4);
                    if (a && FUN_00c03180(a) == ld32(ecx_this, 0x204)) {
                        FUN_00c17350d(a, eff + 1);
                        FUN_00aca360(FUN_00b3d480d(a));
                    }
                    j++;
                } while (j < n);
            }
            begin++;
        } while (begin != end);
    }
    FUN_00e25bd0((void*)*(int*)((char*)ecx_this + 0x220), (void*)*(int*)((char*)ecx_this + 0x224));
}

// ---------------------------------------------------------------------------------------------
// 0x00c505a0 -- SP::cSPMissionEradicate::OnPlanetDeactivate
// ---------------------------------------------------------------------------------------------
// @ 0x00c505a0
void __fastcall FUN_00c505a0(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (ld32(ecx_this, 0x78) != 0x509cc23f)
        self->DestroyHerds();
    int id = ld32(ecx_this, 0x218);
    if (id != -1) {
        ((EventLog*)FUN_00b3d3e0())->RemoveEvent(id, 0);
        st32(ecx_this, 0x218, -1);
    }
    int id2 = ld32(ecx_this, 0x21c);
    if (id2 != -1) {
        ((EventLog*)FUN_00b3d3e0())->RemoveEvent(id2, 0);
        st32(ecx_this, 0x21c, -1);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c50600 -- SP::cSPMissionEradicate::OnPlanetActivate
// ---------------------------------------------------------------------------------------------
// @ 0x00c50600
void __fastcall FUN_00c50600(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    int owner = ld32(ecx_this, 0x1f0);
    if (owner == 0x1e8763) {
        void* mgr = FUN_00b3d300();
        void* vec = (void*)FUN_00b21340(mgr, (void*)0xcd7d10, (void*)0xd3d420,
                                        (void*)0xacdff0, (void*)0xb1e500, (void*)0x18c43e8);
        int cnt = (int)((*(int*)((char*)vec + 8) - *(int*)((char*)vec + 4)) >> 2);
        FUN_00b93c60(cnt, (char*)vec + 0x10);
        int local[3] = {0, 0, 0};
        FUN_00829110(local, *(void**)((char*)vec + 4), *(void**)((char*)vec + 8), 0, 0);
        int n = (int)(((char*)local[1] - (char*)local[0]) >> 2);
        int avail = ld32(ecx_this, 0x1f8) - ld32(ecx_this, 0x208);
        if (n > 0 && avail > 0) {
            int cnt2 = 0;
            do {
                int j = 0;
                if (n > 0) {
                    cnt2 += n;
                    do {
                        void* a = ((void**)local[0])[j];
                        FUN_00bd8140d(a, FUN_00bd8160d(a) + 1);
                        j++;
                    } while (j < n);
                }
            } while (cnt2 < avail);
            self->UnkFfa();
        }
        int* pi = (int*)local[0];
        int* pe = (int*)local[1];
        for (; pi < pe; pi++)
            if (*pi)
                (*(void (__thiscall**)(int))((char*)vtbl((void*)*pi) + 4))(*pi);
        if (local[0] && *(int*)((char*)local[0] - 4) != 0)
            FUN_00f47380((void*)local[0]);
    } else if (owner == 0x389683f8) {
        if (ld32(ecx_this, 0x78) != 0x509cc23f)
            self->UnkF320();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c50740 -- SP::cSPMissionEradicate::HandleMessage (ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50740
void __fastcall FUN_00c50740(void* ecx_this, void* edx, u32 msg, void* arg)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (msg <= 0x3029f11u) {
        if (msg == 0x3029f11u) {
            void* tp = self->GetTargetPlanet();
            void* ap = FUN_01021260();
            if (ap == tp) {
                void* p = *(void**)((char*)arg + 8);
                if (!p)
                    self->UnkFC00(0);
                else {
                    void* v = (*(void* (__thiscall**)(void*, u32))((char*)vtbl(p) + 8))(p, 0xce9f6639u);
                    self->UnkFC00(v);
                }
            }
        } else if (msg == 0x1622184u) {
            void* tp = self->GetTargetPlanet();
            void* ap = FUN_01021260();
            if (ap == tp) {
                void* p = *(void**)((char*)arg + 8);
                void* q = *(void**)((char*)arg + 0x10);
                if (((Mob*)p)->GetUIntField() == 2) {
                    int o = ld32(ecx_this, 0x1bc);
                    if (o == 0x1e8763) {
                        self->OnCombatantKilled(p);
                    } else if (o == 0x389683f8) {
                        if (q && (*(void* (__thiscall**)(void*, u32))((char*)vtbl(q) + 0x5c))(q, 0xd0036e08u)) {
                            void* ani = FUN_00ae33b0d(p);
                            if (ani && ldb(ani, 0xb62) != 0) {
                                if (FUN_00c03180(ani) == ld32(ecx_this, 0x1e0)) {
                                    void* herd = FUN_00c04590d(ani);
                                    if (herd) {
                                        int eff = self->GetDiseaseEffectID(0);
                                        FUN_00fefbb0((void*)ld32(ecx_this, 0x138), herd, 1,
                                                     (void*)ld32(ecx_this, 0x1e0), eff);
                                    }
                                }
                            }
                        } else {
                            self->OnCombatantKilled(p);
                        }
                    }
                }
            }
        } else if (msg == 0x2489760u) {
            void* tp = self->GetTargetPlanet();
            if (*(int*)((char*)arg + 8) == (int)tp)
                self->OnPlanetDeactivate();
        }
    } else if (msg == 0x3337cbbu) {
        if (ld32(ecx_this, 0x1c0) == 0) {
            void* tp = self->GetTargetPlanet();
            void* ap = FUN_01021260();
            if (ap == tp) {
                void* p = *(void**)((char*)arg + 8);
                if (p) {
                    void* v = (*(void* (__thiscall**)(void*, u32))((char*)vtbl(p) + 0xc))(p, 0xee9b2232u);
                    if (v)
                        self->OnCityDestroyed(v);
                }
            }
        }
    } else if (msg == 0x5e37a53u) {
        void* ap = FUN_01021260();
        void* tp = self->GetTargetPlanet();
        if (ap == tp)
            self->OnPlanetActivate();
    }
    self->HandleMessage(msg, arg);
}

// ---------------------------------------------------------------------------------------------
// 0x00c50940 -- FUN_00c50940
// ---------------------------------------------------------------------------------------------
// @ 0x00c50940
void __fastcall FUN_00c50940(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    self->Unk47a10();
    void* tp = self->GetTargetPlanet();
    void* ap = FUN_01021260();
    if (ap == tp) {
        if (FUN_01021080() == 0)
            self->OnPlanetActivate();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c50a80 -- FUN_00c50a80 (m208 or IWinProc::GetPriority)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50a80
int __fastcall FUN_00c50a80(void* ecx_this, void* edx)
{
    (void)edx;
    if (ldb(ecx_this, 0x1f4) != 0)
        return ld32(ecx_this, 0x208);
    return FUN_00e31100d();
}

// ---------------------------------------------------------------------------------------------
// 0x00c50aa0 -- FUN_00c50aa0 (m204 or IWinProc::GetPriority)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50aa0
int __fastcall FUN_00c50aa0(void* ecx_this, void* edx)
{
    (void)edx;
    if (ldb(ecx_this, 0x1f4) != 0)
        return ld32(ecx_this, 0x204);
    return FUN_00e31100d();
}

// ---------------------------------------------------------------------------------------------
// 0x00c50ac0 -- FUN_00c50ac0
// ---------------------------------------------------------------------------------------------
// @ 0x00c50ac0
bool __fastcall FUN_00c50ac0(void* ecx_this, void* edx)
{
    (void)edx;
    if (*(char*)((char*)ecx_this + 0x1f4)) return true;
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x00c50ad0 -- FUN_00c50ad0 (backwards copy of 0x14-byte elements)
// ---------------------------------------------------------------------------------------------
struct Rec20 { u32 a, b, c, d, e; };

// @ 0x00c50ad0
void __cdecl FUN_00c50ad0(Rec20* first, Rec20* last, Rec20* dstEnd)
{
    while (last != first) {
        --last;
        --dstEnd;
        *dstEnd = *last;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c50b10 -- FUN_00c50b10 (deserialize)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50b10
void* __cdecl FUN_00c50b10(IOutStream* stream, char* rec)
{
    IWriter* w = (IWriter*)stream->GetWriter_20();
    FUN_0093ac80(w->GetStream_18(), rec + 0xc);
    IWriter* w2 = (IWriter*)stream->GetWriter_20();
    void* s2 = w2->GetStream_18();
    FUN_0093a780(s2, rec + 0x10, 1, 0);
    if (stream->GetVersion_3c() >= 0x21000eu) {
        IWriter* w3 = (IWriter*)stream->GetWriter_20();
        void* s3 = w3->GetStream_18();
        FUN_0093a780(s3, rec, 3, 0);
    }
    return stream;
}

// ---------------------------------------------------------------------------------------------
// 0x00c50ba0 -- FUN_00c50ba0 (serialize one 0x14-byte record: bool at +0xc, float at +0x10,
//              then the record's first 0xc bytes)
// ---------------------------------------------------------------------------------------------
extern "C" {
char  __cdecl FUN_0093a9a0v(void* s, void* p, int n);          // 0x0093a9a0 WriteBool-ish
void  __cdecl FUN_0093aa70v(void* s, void* p, int n, int f);    // 0x0093aa70 WriteUint32
}

// @ 0x00c50ba0
void* __cdecl FUN_00c50ba0(IOutStream* self, char* rec)
{
    bool b = rec[0xc] != 0;
    IWriter* w = (IWriter*)self->GetWriter_20();
    FUN_0093a9a0v(w->GetStream_18(), &b, 1);
    IWriter* w2 = (IWriter*)self->GetWriter_20();
    float f = *(float*)(rec + 0x10);
    FUN_0093aa70v(w2->GetStream_18(), &f, 1, 0);
    IWriter* w3 = (IWriter*)self->GetWriter_20();
    FUN_0093aa70v(w3->GetStream_18(), rec, 3, 0);
    return self;
}

// ---------------------------------------------------------------------------------------------
// 0x00c50c30 -- SP::cSPMissionExplore::MarkCityVisitedInMiniMap (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50c30
void __fastcall FUN_00c50c30(void* ecx_this, void* edx, void* city)
{
    (void)ecx_this; (void)edx;
    if (!city)
        return;
    void* provider = FUN_010666a0();
    if (!provider)
        return;
    if (!((Win*)provider)->GetWin())
        return;
    // local 0x24-byte city icon descriptor: { color, pos.x, pos.y, pos.z, flags,
    //   mpText, zero, zero, zero }
    struct CityIcon {
        int   color;        // +0x00
        float x;            // +0x04
        float y;            // +0x08
        float z;            // +0x0c
        int   flags;        // +0x10
        void* mpText;       // +0x14
        int   pad[3];       // +0x18
    };
    CityIcon d;
    d.color = 0;
    d.x = 0.0f;
    d.y = 0.0f;
    d.z = -1.0f;                 // 0x13eb1bc = -1.0f
    d.flags = 0x20000;
    d.mpText = 0;
    d.pad[0] = 0;
    d.pad[1] = 0;
    d.pad[2] = 0;
    // city +0x120 vtable slot 0x2c -> returns const Vector3*
    float* pos = (float*)(*(void* (__thiscall**)(void*))((char*)vtbl((char*)city + 0x120) + 0x2c))((char*)city + 0x120);
    d.x = pos[0];
    d.y = pos[1];
    d.z = pos[2];
    d.color = (int)0xff000000;
    ((Ref*)&d.mpText)->Assign(0);
    ((Win*)FUN_010666a0())->GetWin()->RemoveIcon(city, 1, 0);
    ((Win*)FUN_010666a0())->GetWin()->AddIcon(city, &d, 0, 0);
    if (d.mpText)
        (*(void (__thiscall**)(void*))((char*)vtbl(d.mpText) + 4))(d.mpText);
}

// ---------------------------------------------------------------------------------------------
// 0x00c50d20 -- FUN_00c50d20 (find the visited-city record within 100 units of a city) (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50d20
float* __fastcall FUN_00c50d20(void* ecx_this, void* edx, void* city)
{
    (void)edx;
    float* pos = (float*)(*(void* (__thiscall**)(void*))((char*)vtbl((char*)city + 0x120) + 0x2c))((char*)city + 0x120);
    struct CityRec { float x, y, z; unsigned char b; float w; };  // 0x14 bytes
    char* begin = (char*)ld32(ecx_this, 0x214);
    int count = (ld32(ecx_this, 0x218) - (int)begin) / 0x14;
    if (count <= 0)
        return 0;
    CityRec* rec = (CityRec*)begin;
    for (int i = 0; i < count; i++, rec++) {
        float dx = rec->x - pos[0];
        float dz = rec->z - pos[2];
        float dy = rec->y - pos[1];
        float dist = dx * dx + dz * dz + dy * dy;
        if (100.0f > dist)
            return (float*)rec;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c50dd0 -- FUN_00c50dd0 (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50dd0
void __fastcall FUN_00c50dd0(void* ecx_this, void* edx, void* out)
{
    (void)edx;
    if (ldb(ecx_this, 0x1f4) != 0) {
        FUN_006a1250((void*)ld32(ecx_this, 0x180), (int)0xff60c676, out);
        return;
    }
    ((Mob*)ecx_this)->BaseGetProp(out);
}

// ---------------------------------------------------------------------------------------------
// 0x00c50e00 -- FUN_00c50e00 (serialize a vector of 0x14-byte records)
// ---------------------------------------------------------------------------------------------
// @ 0x00c50e00
void __cdecl FUN_00c50e00(IOutStream* self, void* vec)
{
    int n = (ld32(vec, 4) - ld32(vec, 0)) / 0x14;
    IWriter* w = (IWriter*)self->GetWriter_20();
    FUN_0093aa70v(w->GetStream_18(), &n, 1, 0);
    char* p = (char*)ld32(vec, 0);
    char* e = (char*)ld32(vec, 4);
    while (p != e) {
        FUN_00c50ba0(self, p);
        p += 0x14;
    }
    self->Finish_1c();
}

// ---------------------------------------------------------------------------------------------
// 0x00c50e70 -- FUN_00c50e70 (copy 0x14-byte records forwards)
// ---------------------------------------------------------------------------------------------
struct Rec20f { float x, y, z; u8 b; float w; };

// @ 0x00c50e70
void __cdecl FUN_00c50e70(Rec20f* s, Rec20f* srcEnd, Rec20f* d)
{
    while (s != srcEnd) {
        if (d) {
            d->x = s->x;
            d->y = s->y;
            d->z = s->z;
            d->b = s->b;
            d->w = s->w;
        }
        s++;
        d++;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c50eb0 -- FUN_00c50eb0
// ---------------------------------------------------------------------------------------------
// @ 0x00c50eb0
int __fastcall FUN_00c50eb0(void* ecx_this, void* edx)
{
    (void)edx;
    void* key;
    if (ldb(ecx_this, 0x1f4) != 0) {
        int result = 0;
        void* prop = (void*)ld32(ecx_this, 0x180);
        if (prop) {
            if ((*(char (__thiscall**)(void*, int, void**))((char*)vtbl(prop) + 0x24))(prop, 0x5d6796fd, &key)) {
                if (*(short*)((char*)key + 0x12) == 10)
                    result = *((Prop*)key)->GetUInt();
            }
        }
        return result;
    }
    return ((Mob*)ecx_this)->UnkC2b0();
}
