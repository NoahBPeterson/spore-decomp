// Slice s00fe8630: space-item / empire relationship scoring (weights table lookups).
// Built /O2 /MD /Gy /TP /arch:SSE2 (no EH frame).
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
