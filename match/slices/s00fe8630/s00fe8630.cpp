// Slice s00fe8630: space-item / empire relationship scoring (weights table lookups).
// Built /O2 /MD /Gy /TP /arch:SSE2 (no EH frame).
#include <math.h>
#define NOINLINE __declspec(noinline)
typedef unsigned char  u8;
typedef unsigned int   u32;

struct RefObj { virtual void AddRef(); virtual void Release(); };

struct StarRecord : RefObj {
    int __thiscall GetAvatar();                  // 0xb1fdb0
};

struct Noun {
    int  __thiscall F801920();                   // 0x801920
    void* __thiscall GetCities();                // 0x5c65e0
    int  __thiscall GetAvatar();                 // 0xb1fdb0
    int  __thiscall GetType();                   // 0xbb9ae0
    u32  __thiscall GetItemInstanceID();         // 0xc87040
};
int __cdecl F_c6fe00(int v);                     // 0xc6fe00

struct Filter {                                  // argument of GetStarRecords
    u32 mask, kind, a, b;
    float two, minusOne;
    u32 z;
};
struct PtrVec {
    StarRecord** b; StarRecord** e; StarRecord** cap;
    PtrVec() : b(0), e(0), cap(0) {}
};
void __cdecl OperatorDeleteArray(void* p);       // 0xf47380 (operator delete[])

struct StarMgr {
    void __thiscall GetStarRecords(void* cities, Filter* f, PtrVec* out);   // 0xbb1080
};
StarMgr* __cdecl StarManager();                  // 0xb3d2a0

struct RelMgr {
    bool  __thiscall Rel1(int a, int b);         // 0xd01f20
    bool  __thiscall Rel2(int a, int b);         // 0xd01fb0
    float __thiscall Rel3(int a, int b, int c);  // 0xd00a10
};
RelMgr* __cdecl RelationshipManager();           // 0xb3d2c0

struct TerrainSphere {
    bool __thiscall Check();                     // 0xc77410
};
struct NounMgr {
    int __thiscall GetPlayerEmpireOrMinus1();    // 0xb1f9d0
    TerrainSphere* __thiscall GetCurrentTerrainSphere();   // 0xf67d90
};
NounMgr* __cdecl NounManager();                  // 0xb3d300

struct SimUniverse {
    int __thiscall EmpireKind(int empire);       // 0x10107b0
};
extern SimUniverse* gSimUniverse;                // 0x16dc798
extern int gTypeTable[];                         // 0x15b46d0

struct Planet { char pad0[0x58]; int typeIdx; char pad1[0x84 - 0x5c]; int empire; };

struct Wt { float v[11]; };
struct Ent { char pad[0x98]; Wt* w; char pad2[0x330 - 0x9c]; };

static inline const float& MinRef(const float& a, const float& b) { return (b < a) ? b : a; }

static __forceinline float Score(const Wt* w, const float* f, float p4, float p5)
{
    return w->v[7] * f[6] + w->v[8] * f[7] + w->v[6] * f[5] + w->v[5] * f[4] + w->v[4] * f[3]
         + w->v[3] * f[2] + w->v[2] * f[1] + w->v[1] * f[0] + w->v[10] * p5 + w->v[9] * p4 + w->v[0];
}

struct Scorer {
    char pad[0];
    Ent* ents() { return (Ent*)this; }
    void __thiscall Contribute(int idx, int m, int k, float* feats, float* out, int* typeOut);   // 0xfe8cb0
    float __thiscall Evaluate(Noun* item, Planet* pl, int* typeOut, int arg4, int arg5);          // 0xfe8f70
};

// @ 0x00fe8f70
float __thiscall Scorer::Evaluate(Noun* item, Planet* pl, int* typeOut, int arg4, int arg5)
{
    *typeOut = 5;
    int idx = gTypeTable[pl->typeIdx];
    int m = F_c6fe00(item->F801920());
    int emp = pl->empire;
    void* cities = item->GetCities();
    float p4 = (float)arg4;
    float p5 = (float)arg5;
    float acc[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    Filter flt;
    flt.mask = 0x1fff; flt.kind = 0x20; flt.a = 0; flt.b = 0; flt.two = 2.0f; flt.minusOne = -1.0f; flt.z = 0;
    PtrVec recs;
    StarManager()->GetStarRecords(cities, &flt, &recs);
    int n = (int)(recs.e - recs.b);
    for (int i = 0; i < n; i++) {
        StarRecord* r = recs.b[i];
        if (r->GetAvatar() == emp) {
            acc[0] += 0.5f;
        } else if (RelationshipManager()->Rel1(emp, r->GetAvatar())) {
            acc[1] += 0.5f;
        } else if (RelationshipManager()->Rel2(emp, r->GetAvatar())) {
            acc[3] += 0.5f;
        } else {
            acc[2] += 0.5f;
        }
    }
    float f[10];
    float one = 1.0f;
    one = 1.0f; f[0] = MinRef(acc[0], one);
    one = 1.0f; f[1] = MinRef(acc[1], one);
    one = 1.0f; f[2] = MinRef(acc[2], one);
    one = 1.0f; f[3] = MinRef(acc[3], one);
    int owner = item->GetAvatar();
    int player = NounManager()->GetPlayerEmpireOrMinus1();
    bool isPlayer = (owner == player);
    if (owner == -1 || owner == emp) {
        f[4] = 0.0f;
        f[5] = 0.0f;
        f[7] = 0.0f;
    } else {
        f[4] = RelationshipManager()->Rel2(emp, owner) ? 1.0f : 0.0f;
        f[5] = RelationshipManager()->Rel1(emp, owner) ? 1.0f : 0.0f;
        f[7] = RelationshipManager()->Rel3(emp, owner, 0);
    }
    f[6] = isPlayer ? 1.0f : 0.0f;
    f[8] = p4;
    f[9] = p5;
    float result = 1.0f;
    int t = item->GetType();
    if (t == 1) {
        const Wt* w = ents()[idx].w + m;
        float s = Score(w, f, p4, p5);
        if (s > 1.0f) { *typeOut = 0; result = s; }
    } else if (item->GetType() == 5) {
        if (owner == emp) {
            if (item->GetItemInstanceID() & 0x100) {
                const Wt* w = ents()[idx].w + (m + 3);
                float s = Score(w, f, p4, p5);
                if (s > 1.0f) { *typeOut = 1; result = s; }
            }
        } else {
            bool go = true;
            if (isPlayer) {
                if (!NounManager()->GetCurrentTerrainSphere()->Check()) go = false;
                else {
                    int kind = gSimUniverse->EmpireKind(pl->empire);
                    if (kind < 2 || kind > 3) go = false;
                }
            }
            if (go) {
                u32 flags = item->GetItemInstanceID();
                if (!(flags & 0x200)) Contribute(idx, m, 2, f, &result, typeOut);
                Contribute(idx, m, 3, f, &result, typeOut);
                Contribute(idx, m, 4, f, &result, typeOut);
            }
        }
    }
    for (StarRecord** p = recs.b; p < recs.e; ++p)
        if (*p) (*p)->Release();
    if (recs.b && ((int*)recs.b)[-1] != 0) OperatorDeleteArray(recs.b);
    return result;
}

// ==========================================================================
// The empire-growth rule-set object (cEmpireGrowthSim).  Retail offsets:
//   +0x10 / +0x24 / +0x60 / +0x78  heap blocks (intrusive-refcounted at +0x24
//                                   and +0x10: freed only when the count word
//                                   at [p-4] is non-zero)
//   +0x90                           refcounted object released through its
//                                   vtable slot +4
//   +0x98                           per-empire rule-set array, stride 0x330
//   +0xa28                          two 0x330-byte rule blocks, freed in reverse
// ==========================================================================
struct Brush;                       // fwd (the rule-set is shared with the brush code)
extern "C" void operator_delete__(void* p);          // 0x00f47380
extern "C" unsigned FNVHash(const char* s, unsigned seed, int init);  // 0x00932e80

struct RefCounted { virtual void rc00(); virtual void rc04(); };

struct RuleSet {                     // one 0x330-byte per-empire rule set
    char  pad00[0x98];
    void* mpRuleArray;               // +0x98
};
struct Ent330 {                      // a 0x330-byte rule block
    void* mpBuffer;                  // +0x00
    char  pad04[0x10 - 0x04];
    void* mpCap;                     // +0x10
    char  pad14[0x330 - 0x14];
};

struct cEmpireGrowthSim {
    void*       mpVtbl0;             // +0x00   primary vtable
    u32         pad04[1];
    void*       mpVtbl8;             // +0x08   secondary vtable
    u32         pad0c[1];
    void*       mpBlock10;           // +0x10   refcounted block (count at [p-4])
    char        pad14[0x24 - 0x14];
    void*       mpBlock24;           // +0x24   refcounted block (count at [p-4])
    char        pad28[0x60 - 0x28];
    void*       mpBlock60;           // +0x60
    char        pad64[0x78 - 0x64];
    void*       mpBlock78;           // +0x78
    char        pad7c[0x90 - 0x7c];
    RefCounted* mpRef90;             // +0x90
    char        pad94[0x98 - 0x94];
    Ent330      mBlocks[3];          // +0x98   three rule blocks, stride 0x330

    void  SetWeightsForAction(int rule, int row, int index, const Brush* src);   // 0x00fe8b00
    void  ExpandRules(int row, char* action);                                    // 0x00fe8b90
    ~cEmpireGrowthSim();                                                         // 0x00fe8e20
};

// @ 0x00fe8b00
void cEmpireGrowthSim::SetWeightsForAction(int rule, int row, int index, const Brush* src)
{
    float* dst = (float*)((char*)mBlocks[rule].mpBuffer + (index + row * 3) * 0x2c);
    dst[0]  = ((const float*)src)[0xd8 / 4];
    dst[1]  = ((const float*)src)[0xdc / 4];
    dst[2]  = ((const float*)src)[0xe0 / 4];
    dst[3]  = ((const float*)src)[0xe4 / 4];
    dst[4]  = ((const float*)src)[0xe8 / 4];
    dst[5]  = ((const float*)src)[0xf4 / 4];
    dst[6]  = ((const float*)src)[0xf8 / 4];
    dst[7]  = ((const float*)src)[0x100 / 4];
    dst[8]  = ((const float*)src)[0xfc / 4];
    dst[9]  = ((const float*)src)[0xec / 4];
    dst[10] = ((const float*)src)[0xf0 / 4];
}

// @ 0x00fe8aa0
unsigned sIndexFromAction(unsigned id)
{
    unsigned h = FNVHash((const char*)id, 0x811c9dc5u, 1);
    switch (h) {
    case 0x599f0502u: return 3;
    case 0x0ac4aeedu: return 2;
    case 0x4edcc2bfu: return 1;
    case 0x92d53411u: return 0;
    case 0xd1476d98u: return 4;
    default:          return 0;
    }
}

struct ActionData {
    char pad00[0x104];
    unsigned int id;                     // +0x104
    char* mode;                          // +0x108
};

// @ 0x00fe8b90
void cEmpireGrowthSim::ExpandRules(int row, char* action)
{
    ActionData* a = (ActionData*)action;
    unsigned index = sIndexFromAction(a->id);
    char* mode = a->mode;
    if (*mode == 0) {
        SetWeightsForAction(row, (int)index, 1, (const Brush*)action);
        SetWeightsForAction(row, (int)index, 0, (const Brush*)action);
        SetWeightsForAction(row, (int)index, 2, (const Brush*)action);
        return;
    }
    unsigned h = FNVHash(mode, 0x811c9dc5u, 1);
    switch (h) {
    case 0x3a72d292u:
        SetWeightsForAction(row, (int)index, 0, (const Brush*)action);
        break;
    case 0x4f068569u:
        SetWeightsForAction(row, (int)index, 2, (const Brush*)action);
        break;
    default:
        SetWeightsForAction(row, (int)index, 1, (const Brush*)action);
        break;
    }
}

// ==========================================================================
// ScoreStar's per-candidate "contribute" step (0x00fe8cb0) - dot of one
// rule weight row with the ten feature values, keeping the best.
// ==========================================================================
// @ 0x00fe8cb0
void Scorer::Contribute(int row, int index, int kind, float* feats, float* best, int* typeOut)
{
    const float* w = (const float*)((char*)((cEmpireGrowthSim*)this)->mBlocks[row].mpBuffer
                                     + (index + kind * 3) * 0x2c);
    float s = (((((((((w[10] * feats[9] + w[9] * feats[8]) + w[8] * feats[7]) + w[7] * feats[6])
                   + w[6] * feats[5]) + w[5] * feats[4]) + w[4] * feats[3]) + w[3] * feats[2])
                 + w[2] * feats[1]) + w[1] * feats[0]) + w[0];
    if (*best < s) {
        *best = s;
        *typeOut = kind;
    }
}

// ==========================================================================
// The star walk (0x00fe8c50): cEmpire::ForEachStar(scale, extra).
//   stars  = this->GetStars()          (cEmpire member, this in ECX)
//   for each star record: cities = star->GetCities(scale, extra);
//                         StarManager(cities)->FUN_00bb1200();
// ==========================================================================
extern "C" void* __stdcall StarManagerTake(void* cities);        // 0x00b3d2a0
struct StarMgr2 { void __thiscall FUN_00bb1200(); };             // 0x00bb1200
struct CivData { void* __thiscall GetCities(float a, void* b); };// 0x005c65e0
struct StarList { char* mBegin; char* mEnd; };
struct cEmpire {
    StarList* __thiscall GetStars();                             // 0x00c308d0
};
void __cdecl FUN_00fe8c50(void* self, int extra, int scale);      // 0x00fe8c50

// @ 0x00fe8c50
void __cdecl FUN_00fe8c50(void* self, int extra, int scale)
{
    StarList* stars = ((cEmpire*)self)->GetStars();
    int n = (int)(stars->mEnd - stars->mBegin) >> 2;
    for (unsigned i = 0; i < (unsigned)n; i++) {
        CivData* item = (CivData*)((void**)stars->mBegin)[i];
        void* cities = item->GetCities((float)scale, (void*)extra);
        StarMgr2* mgr = (StarMgr2*)StarManagerTake(cities);
        mgr->FUN_00bb1200();
    }
}

// ==========================================================================
// cEmpireGrowthSim destructor (0x00fe8e20).  Frees the two rule blocks, the
// refcounted +0x90 object and the four refcounted buffers, then resets the
// two vtable pointers to their base-class tables.
// ==========================================================================
// @ 0x00fe8e20
cEmpireGrowthSim::~cEmpireGrowthSim()
{
    mpVtbl0 = (void*)0x01494498;
    mpVtbl8 = (void*)0x01494474;

    Ent330* p = mBlocks + 3;
    for (int i = 2; i >= 0; --i) {
        --p;
        void* buf = p->mpBuffer;
        if (buf != 0 && buf != p->mpCap)
            operator_delete__(buf);
    }

    if (mpRef90 != 0)
        mpRef90->rc04();

    if (mpBlock78 != 0)
        operator_delete__(mpBlock78);
    if (mpBlock60 != 0)
        operator_delete__(mpBlock60);

    if (mpBlock24 != 0 && *((int*)mpBlock24 - 1) != 0)
        operator_delete__(mpBlock24);
    if (mpBlock10 != 0 && *((int*)mpBlock10 - 1) != 0)
        operator_delete__(mpBlock10);

    mpVtbl8 = (void*)0x013eb938;
    mpVtbl0 = (void*)0x013ec458;
}

// ==========================================================================
// The brush / crater geometry helpers (0x00fe8630, 0x00fe86d0, 0x00fe8780,
// 0x00fe8880, 0x00fe88d0, 0x00fe8990).  Layout from slice s00fe76d0: the
// sphere parameters live at +0x04..+0x64, a direction/offset at +0x44.
// ==========================================================================
struct Brush {
    unsigned char b00;                  // +0x00
    char  pad01[3];
    float f04, f08, f0c, f10, f14, f18, f1c, f20;
    float f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;

    bool __thiscall ShouldGrow();        // 0x00fe8990
    char __thiscall ReadBrush(void* stream);   // 0x00fe8880
    void __thiscall DeriveFields();            // 0x00fe8450
};

struct Vector3 { float x, y, z; };

extern "C" float RaySphereIntersect(const float* a, const float* b, const float* c);  // 0x006994a0
int f8380(float* value, const Brush* p, float p1, float p2);   // 0x00fe8380

// @ 0x00fe8630
static NOINLINE float Brush_f8630(Brush* self, const float* addend)
{
    float d[3];
    d[0] = self->f5c + addend[0];
    d[1] = self->f60 + addend[1];
    d[2] = self->f64 + addend[2];
    float inv = 1.0f / sqrtf(d[0] * d[0] + (d[1] * d[1] + d[2] * d[2]));
    d[0] = d[0] * inv;
    d[1] = d[1] * inv;
    d[2] = d[2] * inv;
    return RaySphereIntersect(&self->f44, d, &self->f04);
}

// @ 0x00fe86d0
static NOINLINE float* Brush_f86d0(Brush* self, float angle, float* out)
{
    float ca = cosf(angle);
    float t = sqrtf((1.0f - self->f3c) /
                    (1.0f - (self->f3c * ca) * ca)) * self->f24;
    float sa = sinf(angle);
    float a = t * ca;
    float b = t * sa;
    out[0] = (self->f50 * b + self->f44 * a) - self->f5c;
    out[1] = (self->f54 * b + self->f48 * a) - self->f60;
    out[2] = (self->f58 * b + self->f4c * a) - self->f64;
    return out;
}

// @ 0x00fe8780
float* Brush_f8780(float* out, const float* src, const float* add, Brush* self, float angle)
{
    if (self->b00 != 0) {
        out[0] = src[0];
        out[1] = src[1];
        out[2] = src[2];
        return out;
    }
    float diff[3];
    diff[0] = src[0] - add[0];
    diff[1] = src[1] - add[1];
    diff[2] = src[2] - add[2];
    float t = Brush_f8630(self, diff);
    if (f8380(&t, self, angle, 0)) {
        float tmp[3];
        Brush_f86d0(self, t, tmp);
        out[0] = tmp[0] + add[0];
        out[1] = tmp[1] + add[1];
        out[2] = tmp[2] + add[2];
        return out;
    }
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    return out;
}

// ==========================================================================
// 0x00fe8880  char ReadBrush(Brush* self, void* stream)
// Constructs a cVarListSerializer over the caller's buffer, reads the stream
// and, on success, refreshes the derived fields (0x00fe8450).
// ==========================================================================
extern "C" void FUN_015b4568();          // 0x015b4568  (var-list id string)
extern "C" int  FUN_01a80d26();          // 0x01a80d26  (serializer tag)
extern "C" void FUN_00fe8450();          // 0x00fe8450

struct VarListSerializer {               // 0x00a14 bytes
    char mData[0xa14];
    void __thiscall ctor(void* owner, int id, int tag);   // 0x00692f90
    char __thiscall Read(void* stream);                   // 0x00693e10
};

// @ 0x00fe8880
char Brush::ReadBrush(void* stream)
{
    VarListSerializer ser;
    ser.ctor(this, 0x015b4568, 0x01a80d26);
    char ok = ser.Read(stream);
    if (ok != 0)
        DeriveFields();
    return ok;
}

// ==========================================================================
// 0x00fe88d0  void BuildSpiral(Brush* self, Brush** out, int count)
// Resizes the output SpVector<Vector3> to count elements and fills it with the
// spiral positions from +0x14/+0x18/+0x1c, stepping the angle each iteration.
// ==========================================================================
struct SpVectorV3 {
    void __thiscall resize(int n);       // 0x00473810
    char* mpBegin;                       // +0x00
    char* mpEnd;                         // +0x04
    char* mpCap;                         // +0x08
};

// @ 0x00fe88d0
void Brush_f88d0(Brush* self, SpVectorV3* out, int count)
{
    out->resize(count);
    float step = self->f20 / (float)count;
    u32 v[3];
    v[0] = *(u32*)&self->f14;
    v[1] = *(u32*)&self->f18;
    v[2] = *(u32*)&self->f1c;
    if (count > 0) {
        int off = 0;
        int remaining = count;
        do {
            u32* dst = (u32*)(out->mpBegin + off);
            dst[0] = v[0];
            dst[1] = v[1];
            dst[2] = v[2];
            u32 scratch[3];
            u32* r = (u32*)Brush_f8780((float*)scratch, (const float*)v,
                                       (const float*)0x016dab58, self, step);
            v[0] = r[0];
            v[1] = r[1];
            v[2] = r[2];
            off += 0xc;
            remaining--;
        } while (remaining != 0);
    }
}

// ==========================================================================
// 0x00fe8990  bool ShouldGrow(int self)
// True when the trigger manager is in a growth mode, or when one of the two
// flags at +0x48/+0x49 is set and the player's tribe stage is below 2 (which
// also clears the flags).
// ==========================================================================
extern "C" void* GetTriggerMgr();                    // 0x00b3d4d0
extern "C" void* SP_SpaceGameGet();                  // 0x01002bd0
struct TriggerMgr { char pad00[0x2c]; int mode; };   // mode at +0x2c
struct GameNounMgr {
    void* __thiscall GetPlayerTribe();               // 0x00bfc5f0
};
struct TribeState {
    unsigned int __thiscall GetStage();              // 0x00fe42a0
};

// The flag byte pair lives at +0x48/+0x49 of a different retail object than
// Brush (Brush keeps floats there), so name it by role.
struct GrowthState {
    char pad00[0x48];
    unsigned char b48;                               // +0x48
    unsigned char b49;                               // +0x49

    bool __thiscall ShouldGrow();
};

// @ 0x00fe8990
bool GrowthState::ShouldGrow()
{
    TriggerMgr* mgr = (TriggerMgr*)GetTriggerMgr();
    int mode = mgr->mode;
    if (mode == 1)
        return true;
    if (mode == 2)
        return true;
    bool result;
    if (b48 != 0 || b49 != 0) {
        result = true;
        void* game = SP_SpaceGameGet();
        if (game != 0) {
            void* tribe = ((GameNounMgr*)game)->GetPlayerTribe();
            result = ((TribeState*)tribe)->GetStage() < 2u;
            if (!result) {
                b48 = 0;
                b49 = 0;
            }
        }
    } else {
        result = false;
    }
    return result;
}
