// Slice s00c5d640 - SP space-combat raid mission event helpers (Spore game code, VS2008 SP1).
//  00c5d640  collect one raid participant's combat records into a vector (3 out-counts)
//  00c5da10  "raid still in combat on the target planet?" predicate
//  00c5dae0  cSPRaidPlunderEvent::Update   (PDB candidate name)
//  00c5df50  a *RaidEvent-family HandleMessage override (this = mission + 0x34)
//  00c5e020  cSPRaidEvent::HandleMessage   (PDB candidate name; same handler layout)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// `this` for the two HandleMessage overrides is the IHandler subobject of the mission
// (mission = this - 0x34); Update's `this` is the cSPMission base directly (offset 0).
// Every callee is declared with the convention/arg-count its own body uses (see the
// address comment).  Stub classes carry only the fields that are read.
#include "types.h"

namespace SP {

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

// eastl::wstring (16 bytes with the 4-byte allocator); empty rep at 0x01667bac.
extern wchar_t gEmptyWString[];   // 0x01667bac
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WStr() { mpBegin = gEmptyWString; mpEnd = gEmptyWString; mpCapacity = gEmptyWString + 1; }
    void DeallocateSelf();        // 0x00933960
    ~WStr() { DeallocateSelf(); }
};

// --- read-only engine globals (float block at 0x01691fc8 is a Vec3, usually zero) ---
extern Vec3  gDefaultVec3;        // 0x01691fc8
extern float gFloat_01473c70;     // 0x01473c70  (10.0f)
extern float gFloat_013ec5b4;     // 0x013ec5b4  (1000.0f)
extern float gFloat_013f9428;     // 0x013f9428  (0.001f)
extern int   gGameDataTag;        // 0x018ebadc

// --- free engine entry points ---
void* __cdecl GetUniverseContext();   // 0x01021080
void* __cdecl GetActivePlanet();      // 0x01021260
void* __cdecl GetPlayerEmpire();      // 0x01021300
void* __cdecl GetSpaceCombatTuning(); // 0x01029940
void* __cdecl GameTimeManager();      // 0x00b3d380
void* __cdecl GetUFOSimulator();      // 0x00ffbe50
void* __cdecl FUN_00401010();         // 0x00401010
void* __cdecl FUN_00ae3370(void* p);  // 0x00ae3370
void* __cdecl FUN_00c5b430(void* p);  // 0x00c5b430  interface_cast<cBuilding*,cCombatant>
void  __cdecl FUN_00c5b450(void* a, void* b, void* c);   // 0x00c5b450  copy records (32B elems)
void  __cdecl FUN_00c5d140(void* m, void* vec, int a, void* b, Vec3 v, int c, int d);  // 0x00c5d140
void  __cdecl FUN_00c5c310(void* a0, void* a1, void* a2, void* a3, int a4, int a5);   // 0x00c5c310
void  __cdecl FUN_00c5c0f0(void* a0, void* a1, void* a2, void* a3, void* a4, int a5); // 0x00c5c0f0
void  __cdecl FUN_00410370(void* prop, uint32_t id, int* out);   // 0x00410370  (GetPropertyAsInt)
void  __cdecl FUN_0040cf10(void* prop, uint32_t id, float* out); // 0x0040cf10  GetPropertyT<int>
void  __cdecl FUN_00c70fd0(void* self, int v);                   // 0x00c70fd0
void* __cdecl FUN_0102c0c0(void* self);                          // 0x0102c0c0
void* __cdecl FUN_00fe3b10(void* self);                          // 0x00fe3b10
void* __cdecl FUN_00b3d4a0(void* a, void* b);                    // 0x00b3d4a0  CommManager
void* __cdecl FUN_00aeb3e0(void*, void*, void*, void*, void*, void*, void*, void*); // 0x00aeb3e0
void* __cdecl FUN_00cd7d10();         // 0x00cd7d10 (game-data descriptor)
void* __cdecl FUN_00d3d420();         // 0x00d3d420
void* __cdecl FUN_00ad48b0();         // 0x00ad48b0
void* __cdecl FUN_00b1e500();         // 0x00b1e500

// --- stub classes for thiscall callees / objects ---
struct GameObject {
    void* FUN_00c37710();   // 0x00c37710  -> [this+0x800]
    char  FUN_00c372b0();   // 0x00c372b0
    void* FUN_00c38b00();   // 0x00c38b00
};

struct GameDataVec { int pad0; void** begin; void** end; };

struct cGameNounManager {
    GameDataVec* GetGameDataVector(void* a, void* b, void* c, void* d, int* e);  // 0x00b21340 ret 0x14
};
cGameNounManager* __cdecl SP_NounManager();   // 0x00b3d300

struct Rec {                 // 0x20-byte combat record appended to the output vector
    uint32_t f00;
    uint32_t f04;
    float    f08, f0c, f10;
    float    f14;
    float    f18;
    int      f1c;
};
struct RecVec {              // {begin,end,cap}
    Rec* begin;
    Rec* end;
    Rec* cap;
    void AppendDefault();    // 0x00c5c240  (grows by one, constructs a default Rec)
};
struct ObjVec {              // {begin,end,cap} of ref-counted object pointers
    void** begin;
    void** end;
    void** cap;
    void  PushBack(void* const* src);   // 0x00e1c7f0 ret 4
};

struct Mission {
    void* GetTargetPlanet();                 // 0x00970b30
    void* GetOwnerEmpire();                  // 0x00c451e0
    void  GetText(uint32_t key, WStr* out);  // 0x00c487d0
    int   Update(int dt);                    // 0x00c478b0 ret 4
    void  FUN_00c485e0();                    // 0x00c485e0
};

struct EventLog {
    void* PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f); // 0x00dd8640 ret 0x18
    void  ModifyEventText(void* ev, wchar_t* text);                             // 0x00dd6df0 ret 8
    void  EventDoNotAddToHistory(void* ev, int flag);                           // 0x00dd67d0 ret 8
};
EventLog* __cdecl GetEventLog();        // 0x00b3d3e0  (0 args)

struct Empire   { char FUN_00c31bc0(void* other); };                 // 0x00c31bc0
struct StarRec  { void* GetCommContext(void* a); };                  // 0x00ce6950
struct ThrB8    { void* FUN_00b8de30(void* a); };                    // 0x00b8de30
struct Tuning   { float FUN_0102a590(); };                           // 0x0102a590
struct AutoRef  { void operator=(void* p); };                        // 0x00b5f950
struct UFOSim   { void* GetPlayerInventory(); };                     // 0x00a1ad60
struct Combatant{ int GetDamageState(); };                           // 0x008e7f80

// vtable-call helpers
typedef void* (__thiscall *ThunkV0)(void*);
typedef char  (__thiscall *ThunkV0c)(void*);
typedef float (__thiscall *ThunkV0f)(void*);

static inline void* vcall0(void* o, int slot) { return ((ThunkV0)(*(void***)o)[slot])(o); }
static inline char   vcallc(void* o, int slot) { return ((ThunkV0c)(*(void***)o)[slot])(o); }

// ---------------------------------------------------------------------------
// 0x00c5d640
// ---------------------------------------------------------------------------
// @ 0x00c5d640
void FUN_00c5d640(void* mission, RecVec* vec, int* outA, int* outB, int* outC)
{
    // clear the output vector: destroy the range then reset end to begin
    FUN_00c5b450(vec->end, vec->end, vec->begin);
    vec->end = (Rec*)((char*)vec->end - ((((char*)vec->end - (char*)vec->begin) >> 5) << 5));

    ObjVec va = {0, 0, 0};   // kind 4
    ObjVec vb = {0, 0, 0};   // kind 2
    ObjVec vc = {0, 0, 0};   // kind 5

    GameDataVec* gd = SP_NounManager()->GetGameDataVector(
        (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420, (void*)&FUN_00ad48b0, (void*)&FUN_00b1e500, &gGameDataTag);
    int n = (int)((char*)gd->end - (char*)gd->begin) >> 2;
    for (int i = 0; i < n; ++i) {
        void* o = gd->begin[i];
        if (((GameObject*)o)->FUN_00c37710() == mission) {
            char b0 = ((GameObject*)o)->FUN_00c372b0();
            char b1 = vcallc(o, 0x2c / 4);
            if (!b0 && !b1 && 0.0f < *(float*)((char*)o + 0x540)) {
                int kind = *(int*)((char*)o + 0x714);
                ObjVec* dst = 0;
                if (kind == 2) dst = &vb;
                else if (kind == 4) dst = &va;
                else if (kind == 5) dst = &vc;
                if (dst) {
                    void* tmp = o;
                    vcall0(o, 0);                       // AddRef
                    dst->PushBack(&tmp);
                    if (tmp) ((ThunkV0)(*(void***)tmp)[1])(tmp);   // Release
                }
            }
        }
    }

    // records for kind-4 objects (they also carry the "index within kind-4" field)
    *outA = (int)((char*)va.end - (char*)va.begin) >> 2;
    for (int i = 0; i < *outA; ++i) {
        void* o = va.begin[i];
        vec->AppendDefault();
        Rec* r = vec->end - 1;
        r->f14 = *(float*)((char*)o + 0x540);
        r->f18 = ((ThunkV0f)(*(void***)((char*)o + 0x508))[0x58 / 4])((char*)o + 0x508);
        r->f04 = *(uint32_t*)((char*)o + 0x714);
        float* q = (float*)((ThunkV0)(*(void***)((char*)o + 0x34))[0x2c / 4])((char*)o + 0x34);
        r->f08 = q[0];
        r->f0c = q[1];
        r->f10 = q[2];
        void* x = ((GameObject*)o)->FUN_00c38b00();
        if (x) {
            void* y = ((void*(__thiscall*)(void*, void*))(*(void***)x)[0xc / 4])(x, (void*)0xb033b403);
            if (y) {
                for (int k = 0; k < *outA; ++k) {
                    if (va.begin[k] == y) { r->f1c = k; break; }
                }
            }
        }
    }

    // records for kind-2 objects
    *outB = (int)((char*)vb.end - (char*)vb.begin) >> 2;
    for (int i = 0; i < *outB; ++i) {
        void* o = vb.begin[i];
        vec->AppendDefault();
        Rec* r = vec->end - 1;
        r->f14 = *(float*)((char*)o + 0x540);
        r->f18 = ((ThunkV0f)(*(void***)((char*)o + 0x508))[0x58 / 4])((char*)o + 0x508);
        r->f04 = *(uint32_t*)((char*)o + 0x714);
        float* q = (float*)((ThunkV0)(*(void***)((char*)o + 0x34))[0x2c / 4])((char*)o + 0x34);
        r->f08 = q[0];
        r->f0c = q[1];
        r->f10 = q[2];
    }

    // records for kind-5 objects
    *outC = (int)((char*)vc.end - (char*)vc.begin) >> 2;
    for (int i = 0; i < *outC; ++i) {
        void* o = vc.begin[i];
        vec->AppendDefault();
        Rec* r = vec->end - 1;
        r->f14 = *(float*)((char*)o + 0x540);
        r->f18 = ((ThunkV0f)(*(void***)((char*)o + 0x508))[0x58 / 4])((char*)o + 0x508);
        r->f04 = *(uint32_t*)((char*)o + 0x714);
        float* q = (float*)((ThunkV0)(*(void***)((char*)o + 0x34))[0x2c / 4])((char*)o + 0x34);
        r->f08 = q[0];
        r->f0c = q[1];
        r->f10 = q[2];
    }

    // release the three scratch vectors (C, B, A order in retail)
    ObjVec* order[3] = { &vc, &vb, &va };
    for (int v = 0; v < 3; ++v) {
        ObjVec* p = order[v];
        for (void** it = p->begin; it != p->end; ++it) {
            void* o = *it;
            if (o) ((ThunkV0)(*(void***)o)[1])(o);
        }
        if (p->begin && ((int*)p->begin)[-1] != 0) ::operator delete(p->begin);
    }
}

// ---------------------------------------------------------------------------
// 0x00c5da10
// ---------------------------------------------------------------------------
// @ 0x00c5da10
bool FUN_00c5da10(Mission* mission, int* pvec)
{
    if (GetUniverseContext() == 0) {
        void* tp = mission->GetTargetPlanet();
        if (GetActivePlanet() == tp) {
            GameDataVec* gd = SP_NounManager()->GetGameDataVector(
                (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420, (void*)&FUN_00ad48b0, (void*)&FUN_00b1e500, &gGameDataTag);
            int n = (int)((char*)gd->end - (char*)gd->begin) >> 2;
            for (int i = 0; i < n; ++i) {
                void* o = gd->begin[i];
                if (((GameObject*)o)->FUN_00c37710() == mission) {
                    char b0 = ((GameObject*)o)->FUN_00c372b0();
                    char b1 = vcallc(o, 0x2c / 4);
                    if (!b0 && !b1 && 0.0f < *(float*)((char*)o + 0x540)) return true;
                }
            }
            return false;
        }
    }
    return *pvec != pvec[1];
}

// ---------------------------------------------------------------------------
// 0x00c5df50 - RaidPlunderEvent HandleMessage override (this = mission + 0x34)
// ---------------------------------------------------------------------------
struct RaidHandler {
    char BaseHandleMessage(uint32_t msg, void* m);   // 0x00c4a6b0 (cSPMission::HandleMessage)
    bool HandleMessage_F50(uint32_t msg, void* m);   // 0x00c5df50
    bool HandleMessage_020(uint32_t msg, void* m);   // 0x00c5e020

    template<class T> T& F(int off) { return *(T*)((char*)this + off); }
    Mission* Mis() { return (Mission*)((char*)this - 0x34); }
};

// @ 0x00c5df50
bool RaidHandler::HandleMessage_F50(uint32_t msg, void* m)
{
    if (msg == 0x2489760) {
        if (*(int*)((char*)m + 8) == (int)Mis()->GetTargetPlanet()) {
            FUN_00c5d640(Mis(), (RecVec*)&F<void*>(0x1e0), (int*)&F<void*>(0x1d0),
                         (int*)&F<void*>(0x1d4), (int*)&F<void*>(0x1cc));
        }
    } else if (msg == 0x248975f) {
        if (*(int*)((char*)m + 0x10) == (int)Mis()->GetTargetPlanet()) {
            FUN_00c5d140(Mis(), &F<void*>(0x1e0), -1, &F<void*>(0x1bc), gDefaultVec3, 0, 0);
        }
    }
    return BaseHandleMessage(msg, m) != 0;
}

// ---------------------------------------------------------------------------
// 0x00c5e020 - cSPRaidEvent::HandleMessage (this = mission + 0x34)
// ---------------------------------------------------------------------------
// @ 0x00c5e020
bool RaidHandler::HandleMessage_020(uint32_t msg, void* m)
{
    if (msg == 0x2489760) {
        if (*(int*)((char*)m + 8) == (int)Mis()->GetTargetPlanet()) {
            if (F<uint8_t>(0x200) == 0) {
                int local = 0;
                FUN_00c5d640(Mis(), (RecVec*)&F<void*>(0x204), (int*)&F<void*>(0x1c4),
                             (int*)&F<void*>(0x1c8), &local);
            } else {
                Mis()->FUN_00c485e0();
            }
        }
    } else if (msg == 0x248975f) {
        if (*(int*)((char*)m + 0x10) == (int)Mis()->GetTargetPlanet()) {
            FUN_00c5d140(Mis(), &F<void*>(0x204), F<int>(0x1fc), &F<void*>(0x1cc),
                         gDefaultVec3, 0, (int)F<uint8_t>(0x1e8));
        }
    }

    if (BaseHandleMessage(msg, m) != 0) return false;
    if (F<uint32_t>(0x44) != 0xd646c543) return false;
    if (Mis()->GetTargetPlanet() != GetActivePlanet()) return false;
    if (GetUniverseContext() != 0) return false;
    if (msg != 0x1622184) return false;

    void* c = *(void**)((char*)m + 8);
    int   x = *(int*)((char*)m + 0x10);
    void* inv = ((UFOSim*)GetUFOSimulator())->GetPlayerInventory();
    if (inv) inv = (char*)inv + 0x508; else inv = 0;
    if (x == (int)inv) {
        if (((Combatant*)c)->GetDamageState() == 2) {
            bool b = FUN_00c5b430(c) != 0;
            void* r = FUN_00ae3370(c);
            if (((r != 0) && (*(int*)((char*)r + 0x714) == 6)) || b) {
                if (++F<int>(0x1e4) == 3) {
                    WStr text;
                    Mis()->GetText(0xdb458701, &text);
                    void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
                    GetEventLog()->ModifyEventText(ev, text.mpBegin);
                    GetEventLog()->EventDoNotAddToHistory(ev, 1);
                    text.DeallocateSelf();
                }
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00c5dae0 - cSPRaidPlunderEvent::Update (this = cSPMission base)
// ---------------------------------------------------------------------------
struct RaidPlunderEvent {
    template<class T> T& F(int off) { return *(T*)((char*)this + off); }
    void  BackgroundUpdate(int a);      // 0x00c5b550
    int   Update(int dt);               // 0x00c5dae0
};

// @ 0x00c5dae0
int RaidPlunderEvent::Update(int dt)
{
    Mission* mi = (Mission*)this;
    int r = mi->Update(dt);
    if (r != 3) return r;

    if ((*(uint32_t*)((char*)GameTimeManager() + 0x48) & 1) != 0) dt = 0;

    if (F<uint8_t>(0x1fc) == 0) {
        void* p = FUN_00401010();
        char ok = ((char(__thiscall*)(void*, void*, int))(*(void***)p)[0x1c / 4])(
                      p, (char*)this + 0x1f0, 0);
        if (ok != 0) {
            int v14 = 1, v10 = 1;
            void* prop = *(void**)((char*)this + 0x180);
            F<uint8_t>(0x1fc) = 1;
            if (prop != 0) {
                FUN_00410370(prop, 0x339bbc1, &v14);
                FUN_00410370(prop, 0x339bbc5, &v10);
            }
            FUN_00c5c310((char*)this + 0x214, (char*)this + 0x204, (char*)this + 0x208,
                         (char*)this + 0x200, v14, v10);

            if (GetUniverseContext() == 0) {
                if (GetActivePlanet() == mi->GetTargetPlanet()) {
                    FUN_00c5d140(this, (char*)this + 0x214, -1, (char*)this + 0x1f0, gDefaultVec3, 0, 0);
                }
            }

            void* owner  = mi->GetOwnerEmpire();
            void* player = GetPlayerEmpire();
            if (owner != 0 && (owner == player || ((Empire*)owner)->FUN_00c31bc0(player))) {
                void* tp1 = mi->GetTargetPlanet();
                int   recA = *(int*)((char*)tp1 + 0x13c);
                void* tp2 = mi->GetTargetPlanet();
                int   recB = *(int*)((char*)tp2 + 0x13c);
                int   owner84 = *(int*)((char*)owner + 0x84);
                int   eq = (owner == player) ? 1 : 0;
                void* tree = ((void*(__thiscall*)(void*, uint32_t, int, void*, int))
                              (*(void***)this)[0xa4 / 4])(this, 0x8b756f4b, 2, this, eq);
                void* ctx  = ((StarRec*)recA)->GetCommContext(tree);
                void* ctx2 = ((ThrB8*)recB)->FUN_00b8de30(ctx);
                void* cm   = FUN_00b3d4a0((void*)owner84, ctx2);
                void* res  = FUN_00aeb3e0(cm, ctx2, ctx, tree, (void*)0x8b756f4b, (void*)2, this, (void*)eq);
                ((AutoRef*)((char*)this + 0x1e4))->operator=(res);
            }
        }
        if (F<uint8_t>(0x1fc) == 0) return 3;
    }

    if (!FUN_00c5da10(mi, (int*)((char*)this + 0x214))) {
        WStr text;
        mi->GetText(0x25594ea8, &text);
        void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
        GetEventLog()->ModifyEventText(ev, text.mpBegin);
        GetEventLog()->EventDoNotAddToHistory(ev, 1);
        if ((2 < (int)(((char*)text.mpEnd - (char*)text.mpBegin) & 0xfffffffe)) && text.mpBegin != 0)
            ::operator delete(text.mpBegin);
        return 5;
    }

    float f = gFloat_01473c70;
    if (*(void**)((char*)this + 0x180) != 0)
        FUN_0040cf10(*(void**)((char*)this + 0x180), 0x2b9e524, &f);
    f = (float)(long long)(f * gFloat_013ec5b4);

    if (*(uint32_t*)((char*)this + 0x7c) < (uint32_t)(int)f) {
        void* tp = mi->GetTargetPlanet();
        if (FUN_00fe3b10(tp) == 0) {
            float tuning = ((Tuning*)GetSpaceCombatTuning())->FUN_0102a590();
            float acc = (float)dt * gFloat_013f9428 * (float)*(int*)((char*)this + 0x200) * tuning
                      + *(float*)((char*)this + 0x210);
            *(float*)((char*)this + 0x210) = acc;
            int rounded = (int)(long long)acc;
            if (rounded != 0) {
                *(float*)((char*)this + 0x210) = acc - (float)rounded;
                FUN_00c70fd0(mi->GetTargetPlanet(), rounded);
            }
        }
        FUN_00c5c0f0((char*)this + 0x214, mi->GetTargetPlanet(), (char*)this + 0x200,
                     *(void**)((char*)this + 0x180), (char*)this + 0x20c, dt);
        return 3;
    }

    FUN_0102c0c0(mi->GetTargetPlanet());
    BackgroundUpdate(0);
    WStr text;
    mi->GetText(0xb681fba2, &text);
    void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
    GetEventLog()->ModifyEventText(ev, text.mpBegin);
    GetEventLog()->EventDoNotAddToHistory(ev, 1);
    if ((2 < (int)(((char*)text.mpEnd - (char*)text.mpBegin) & 0xfffffffe)) && text.mpBegin != 0)
        ::operator delete(text.mpBegin);
    return 6;
}

} // namespace SP
