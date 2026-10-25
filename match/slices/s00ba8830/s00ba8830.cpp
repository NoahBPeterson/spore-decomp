// Slice s00ba8830 (0x00ba8830..0x00ba980a) — cStarManager / star-generation helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE
// (frame-omitted prologues, SSE scalar float copies; no EH prolog although
//  locals with destructors exist, so no /EHsc.)

#include "types.h"
#include <math.h>

#pragma warning(disable: 4100)
// Retail evaluates every transcendental with x87 fsin/fcos/fsqrt on the extended-precision
// operands; intrinsic sin/cos/sqrt keep those instructions inline instead of CRT imports.
#pragma intrinsic(sin, cos, sqrt)

// ---------------------------------------------------------------------------
// Minimal EASTL map layout (matches EASTL 3.02.01: rb_base::mCompare at +0,
// rbtree::mAnchor at +4, mnSize at +0x14, empty allocator at +0x18; size 0x1c).
// The tree node is value_type pair at +0x10, so `second` sits at +0x14.
// `find` is an out-of-line template instantiation in the original (an external
// relocation, so its address is masked by the verifier).
// ---------------------------------------------------------------------------
struct RBNodeBase {
    RBNodeBase* mpNodeLeft;   // +0x00
    RBNodeBase* mpNodeRight;  // +0x04
    RBNodeBase* mpNodeParent; // +0x08
    uint8_t     mColor;       // +0x0c
    uint8_t     pad[3];
};

struct RBNode {
    RBNode* mpNodeLeft;   // +0x00
    RBNode* mpNodeRight;  // +0x04
    RBNode* mpNodeParent; // +0x08
    uint8_t mColor;       // +0x0c
    uint8_t pad[3];
    uint32_t first;       // +0x10  (pair.first)
    void*    second;      // +0x14  (pair.second, first dword of value)
};

// iterator: non-trivial (user ctor) so `find` returns it through a hidden sret.
struct TreeIterator {
    RBNode* mpNode;
    TreeIterator(RBNode* p = 0) : mpNode(p) {}
    TreeIterator(const TreeIterator& o);
    RBNode* operator->() const { return mpNode; }
    bool operator!=(const TreeIterator& o) const { return mpNode != o.mpNode; }
};

struct UnsignedVoidMap {
    char mCompare[4];       // +0x00
    RBNodeBase mAnchor;     // +0x04
    uint32_t mnSize;        // +0x14
    char mAllocator;        // +0x18
    TreeIterator find(const uint32_t& key) const;       // out-of-line
    TreeIterator end() const { return TreeIterator((RBNode*)&mAnchor); }
};

// ---------------------------------------------------------------------------
// cStarManager: retail offsets read from the disassembly.  The dev PDB layout
// differs from retail, so the fields used here are placed explicitly.
// ---------------------------------------------------------------------------
struct cStarManager {
    char pad_0000[0x150];
    UnsignedVoidMap mEmpires;  // +0x150
    char pad_016c[0x1a4 - 0x16c];
    void* mpProperties;        // +0x1a4  (property table)
    char pad_01a8[0x1d8 - 0x1a8];
    int mEmpireID;             // +0x1d8

    int   GetEmpireByID(unsigned int empireID);
    void* GetByFieldID();
    void  GenerateStarField(void* star);
    void  BuildPlanet(void* system, void* out, float p4, float p5, void* p6);
};

// ---------------------------------------------------------------------------
// @ 0x00ba9370  cStarManager::GetEmpireByID(unsigned int) : __thiscall, ret 4
// ---------------------------------------------------------------------------
int cStarManager::GetEmpireByID(unsigned int empireID)
{
    if (empireID != 0xffffffffu) {
        RBNode* n = mEmpires.find(empireID).mpNode;
        if (n != mEmpires.end().mpNode)
            return (int)n->second;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// out-of-line EASTL tree helpers (external relocations, addresses masked)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl RBTreeIncrement(void* node);                  // 0x921580
extern "C" void  __cdecl RBTreeErase(void* node, void* anchor);        // 0x921880
extern "C" void  __cdecl operator_delete(void* p);                     // 0xf47380

struct VecOfPtrs {
    void** mpBegin;   // +0x00
    void** mpEnd;     // +0x04
    void** mpCap;     // +0x08
};

// Object with a feedback-event map at +0x20 and a pointer vector at +0x3c.
struct FeedbackMgr {
    char pad_0000[0x20];
    UnsignedVoidMap mMap;   // +0x20
    VecOfPtrs       mVec;   // +0x3c
    void RemoveEvent(struct EventSource* src);
};

struct EventSource {
    char pad_0000[0x70];
    uint32_t mEventID;      // +0x70
};

// ---------------------------------------------------------------------------
// @ 0x00ba92e0  FeedbackMgr::RemoveEvent(EventSource*) : __thiscall, ret 4
// ---------------------------------------------------------------------------
void FeedbackMgr::RemoveEvent(EventSource* src)
{
    uint32_t key = src->mEventID;
    TreeIterator it = mMap.find(key);
    if (it.mpNode != mMap.end().mpNode) {
        void* val = it.mpNode->second;
        mMap.mnSize--;
        RBTreeIncrement(it.mpNode);
        RBTreeErase(it.mpNode, &mMap.mAnchor);
        operator_delete(it.mpNode);
        (*(void (__thiscall**)(void*))((char*)*(void**)val + 0x44))(val);
        void** p = mVec.mpBegin;
        void** e = mVec.mpEnd;
        while (p != e) {
            if (*p == val) {
                *p = e[-1];
                mVec.mpEnd = e - 1;
                break;
            }
            ++p;
        }
    }
}

// ---------------------------------------------------------------------------
// wstring / lazy static string helpers
// ---------------------------------------------------------------------------
struct WStr {
    wchar_t* mpBegin;     // +0x00
    wchar_t* mpEnd;       // +0x04
    wchar_t* mpCapacity;  // +0x08
    void Assign(const wchar_t* b, const wchar_t* e);   // 0x423650
};

extern wchar_t g_emptyWString[];    // 0x1667bac
extern WStr    g_WStrA;             // 0x1689dfc
extern uint32_t g_initA;            // 0x1689e0c
extern WStr    g_WStrB;             // 0x1689e10
extern uint32_t g_initB;            // 0x1689e20
extern WStr    g_CachedName;        // 0x156c63c
extern "C" int __cdecl atexit(void (__cdecl*)(void));

// ---------------------------------------------------------------------------
// Input solar-system star record (the argument of GenerateStarField) and the
// generated star body record returned by 0xba61b0.
// ---------------------------------------------------------------------------
struct StarSystem {
    char     pad_0000[0x70];
    uint32_t mnBaseKey;                       // +0x70
    char     pad_0074[0xac - 0x74];
    uint8_t  mnBodyIndex;                     // +0xac
};

struct StarBody {
    char     pad_0000[0x18];
    WStr     mName;                           // +0x18
    char     pad_0024[0x28 - 0x24];
    int      mnKind;                          // +0x28
    int      mnSubKind;                       // +0x2c
    char     pad_0030[0x4c - 0x30];
    uint8_t  mb4c;                            // +0x4c
    char     pad_004d[0xb0 - 0x4d];
    float    mfB0;                            // +0xb0
    float    mfB4;                            // +0xb4
    char     pad_00b8[0x130 - 0xb8];
    uint8_t  mb130;                           // +0x130
    char     pad_0131[0x194 - 0x131];
    int      mn194;                           // +0x194
};

typedef WStr* (__cdecl* GetWStrFn)(void*);

// ---------------------------------------------------------------------------
// @ 0x00ba9400  cdecl(void*) : lazy-init of a static empty wstring, then
//              copy it into the string returned by p->fn at [p+0x20].
// ---------------------------------------------------------------------------
void FUN_00ba9400(void* p)
{
    WStr* r = ((GetWStrFn)*(void**)((char*)p + 0x20))(p);
    if ((g_initA & 1) == 0) {
        g_initA |= 1;
        g_WStrA.mpBegin = g_emptyWString;
        g_WStrA.mpEnd = g_emptyWString;
        g_WStrA.mpCapacity = g_emptyWString + 1;
        atexit((void (__cdecl*)(void))0x13c2f90);
    }
    if (r != &g_WStrA)
        r->Assign(g_WStrA.mpBegin, g_WStrA.mpEnd);
}

// ---------------------------------------------------------------------------
// @ 0x00ba9470  cdecl(void*) : same shape as FUN_00ba9400, second static.
// ---------------------------------------------------------------------------
void FUN_00ba9470(void* p)
{
    WStr* r = ((GetWStrFn)*(void**)((char*)p + 0x20))(p);
    if ((g_initB & 1) == 0) {
        g_initB |= 1;
        g_WStrB.mpBegin = g_emptyWString;
        g_WStrB.mpEnd = g_emptyWString;
        g_WStrB.mpCapacity = g_emptyWString + 1;
        atexit((void (__cdecl*)(void))0x13c2f60);
    }
    if (r != &g_WStrB)
        r->Assign(g_WStrB.mpBegin, g_WStrB.mpEnd);
}

// ---------------------------------------------------------------------------
// @ 0x00ba93b0  cStarManager::GetByFieldID() : __thiscall, plain ret
// ---------------------------------------------------------------------------
void* cStarManager::GetByFieldID()
{
    uint32_t key = (uint32_t)mEmpireID;
    if (key != 0xffffffffu) {
        RBNode* n = mEmpires.find(key).mpNode;
        if (n != mEmpires.end().mpNode)
            return n->second;
    }
    return 0;
}

// ===========================================================================
// Remainder of the slice — star generation / planet setup / EASTL sort helpers.
//
// These are behaviourally faithful transcriptions of the original control
// flow (all calls, stores and tree/vector updates are present).  They are NOT
// byte-exact: the retail build interleaves x87 transcendentals, pooled
// temporary strings and AutoRefCount temporaries in an order that is not
// reproduced here.  Helper signatures are declared from the 2008 dev PDB and
// from what the callee does; field offsets are the retail ones.
// ===========================================================================

// --- external callees (all original relocations) ---------------------------
// The __fastcall forms put the first argument in ecx (thiscall layout) with a
// throw-away edx slot, matching the retail thiscall callees.
extern "C" void* __cdecl FUN_004010a0();                              // 0x4010a0
extern "C" void  __cdecl FUN_00ba61b0(uint32_t key, void** out);       // 0xba61b0
extern "C" void* __fastcall FUN_005ecf80(void* self, int, void* out, int hash);          // 0x5ecf80
extern "C" void  __fastcall FUN_00ba64a0(void* self, int, void* o, void* star, int x);   // 0xba64a0
extern "C" void  __fastcall FUN_00ba6310(void* self, int, void* o, int a, int b);         // 0xba6310
extern "C" int   __fastcall FUN_00989360(void* self, int);              // 0x989360
extern "C" void* __fastcall FUN_00ba8010(void* self, int, void* out, int x);              // 0xba8010
extern "C" void  __fastcall FUN_00b8dde0(void* self, int, void* x, int y); // 0xb8dde0
extern "C" void* __cdecl FUN_00f48a80();                               // 0xf48a80
extern "C" void* __fastcall FUN_00b8d8e0(void* self, int, void* out);  // 0xb8d8e0
extern "C" void* __cdecl FUN_00b3d3d0(void* o, int x);                 // 0xb3d3d0
extern "C" void  __fastcall FUN_0103ca40(void* self, int);             // 0x103ca40
extern "C" bool  __fastcall FUN_00bb9af0(void* self, int, int x);      // 0xbb9af0
extern "C" void  __fastcall FUN_00bb9b00(void* self, int, int a, int b); // 0xbb9b00
extern "C" void  __cdecl FUN_00b2af00(int* a, int* b);                 // 0xb2af00
extern "C" void  __cdecl FUN_00ba79a0(void* a, int b, int c, int d);   // 0xba79a0
extern "C" void  __cdecl FUN_00ba84b0(void* a, void* b, void* c);      // 0xba84b0
extern "C" void  __cdecl FUN_00ba8500(void* a, void* b, void* c);      // 0xba8500
extern "C" float __cdecl FUN_010431e0(void* props, int id);            // 0x10431e0
extern "C" void* __cdecl FUN_00ba8650(void* out, float angle);         // 0xba8650
extern "C" void* __cdecl FUN_0059aed0(void* out, void* vec, void* quat); // 0x59aed0
extern "C" void* __fastcall FUN_00801920(void* self, int);             // 0x801920
extern "C" float __cdecl FUN_00c841a0(void* star);                     // 0xc841a0 (GetStarMass)
extern "C" float* __fastcall FUN_0041ea70(void* prop, int);            // 0x41ea70 (Property::GetFloat)
extern "C" void  __fastcall FUN_00fe8450(void* out, int);              // 0xfe8450
extern "C" int   __cdecl EA_IO_WriteUint32(void* w, void* p, int n, int x); // EA::IO::WriteUint32 (reloc)

// Random number singleton: SP::sMathRandom is an EA::Random::RandomLinearCongruential
// living at 0x01601760.  The namespaced spelling mangles to the retail global/method,
// so both the data reference and the RandomDoubleUniform call bind to the originals.
namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    double RandomDoubleUniform();   // 0x009360d0
};
} }
namespace SP { extern EA::Random::RandomLinearCongruential sMathRandom; }

// Older spelling kept for InitStarOrbit (its row is already finalized).
struct VRandom { double RandomDoubleUniform(); };
extern VRandom sMathRandom;   // 0x16... _sMathRandom

// Rotation axes used by BuildPlanet (0x156c52c / 0x156c538) and the retail float
// constants it loads from .rdata/.data.
static const float kAxisX[3] = { 1.0f, 0.0f, 0.0f };   // 0x156c52c
static const float kAxisZ[3] = { 0.0f, 0.0f, 1.0f };   // 0x156c538
static const float kfDegToRad = 0.017453292f;   // 0x1465eb0
// Full-turn angle; retail initializes this global to 2*pi from 0x156c528 at startup, so
// reference it rather than folding in the literal.
extern float g_RandomTurns;                     // 0x1689c4c
static const float kfHalf = 0.5f;               // 0x1471064
static const float kfMaxInclination = 89.0f;    // 0x1466024
static const float kfWeightMax = 0.99f;         // 0x13ef480
static const float kfEpsilon = 1e-8f;           // 0x13ec4b8
static const float kfDensityDefault = 100.0f;   // 0x13ec4d0
static const float kfDensityGas = 10.0f;        // 0x1473c70
static const float kfVolumeScaleRocky = 0.001f; // 0x13f9428
static const float kfVolumeScaleStar = 1e-6f;   // 0x13f11c8

// Non-trivial reference-counted object held inside the generated containers.
typedef void (__thiscall* VCall1)(void*);
static inline void RefAddRef(void* o) { if (o) ((VCall1)(*(void***)o)[0])(o); }
static inline void RefRelease(void* o) { if (o) ((VCall1)(*(void***)o)[1])(o); }
static inline void StarBody_Release(void* o)
{
    (*(void (__thiscall**)(void*))((char*)*(void**)o + 4))(o);
}

// Build one star body record: allocate via the key, copy its localized name,
// then store the type/subtype/flag triple.  The caller advances the index.
static void* MakeStarBody(cStarManager* self, StarSystem* star, void* nameGen,
                          int kind, int subKind, int flag194, bool useCached)
{
    void* obj = 0;
    FUN_00ba61b0((uint32_t)star->mnBodyIndex * 0x1000000u + star->mnBaseKey, &obj);

    WStr  tmp = { 0, 0, 0 };
    WStr* name;
    bool  usedTemp = false;
    if (useCached && g_CachedName.mpBegin != g_CachedName.mpEnd) {
        name = &g_CachedName;
    } else {
        name = (WStr*)FUN_005ecf80(nameGen, 0, &tmp, 0x7e1310a);
        usedTemp = true;
    }

    StarBody* body = (StarBody*)obj;
    if (name != &body->mName)
        body->mName.Assign(name->mpBegin, name->mpEnd);
    if (usedTemp && (((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & 0xfffffffe) > 2 &&
        tmp.mpBegin != 0)
        operator_delete(tmp.mpBegin);

    body->mnKind   = kind;      // +0x28
    body->mnSubKind = subKind;  // +0x2c
    body->mn194    = flag194;   // +0x194
    return obj;
}

// ---------------------------------------------------------------------------
// @ 0x00ba8830  cStarManager::GenerateStarField(star*) : __thiscall (ret 4)
// ---------------------------------------------------------------------------
void cStarManager::GenerateStarField(void* starPtr)
{
    StarSystem* star = (StarSystem*)starPtr;
    if (FUN_00bb9af0(star, 0, 0x8000))
        star->mnBodyIndex = 0;
    if (star->mnBodyIndex != 0)
        return;

    FUN_00bb9b00(star, 0, 0x100, 0);

    void* nameGen = FUN_004010a0();

    // Body 0: kind 2/5/1 plus the orbit / spin / size setup.
    {
        void* obj = MakeStarBody(this, star, nameGen, 5, 2, 1, true);
        StarBody* body = (StarBody*)obj;

        void* dummy = 0;
        void* m = FUN_00ba8010(this, 0, &dummy, FUN_00989360(star, 0));
        FUN_00b8dde0(body, 0, m, 0);
        body->mb130 = 1;

        void* g = FUN_00f48a80();
        float orbit[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        void* v = FUN_00b8d8e0(body, 0, orbit);
        (*(void (__thiscall**)(void*, void*))((char*)*(void**)g + 8))(g, v);
        body->mfB0 = orbit[3];   // +0xb0
        body->mfB4 = orbit[2];   // +0xb4

        void* r = FUN_00b3d3d0(body, 1);
        FUN_0103ca40(r, 0);

        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 1: kind 2/4/1.
    {
        void* obj = MakeStarBody(this, star, nameGen, 2, 4, 1, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 2: kind 3/0/1 plus the special satellite descriptor.
    {
        void* obj = MakeStarBody(this, star, nameGen, 3, 0, 1, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        FUN_00ba6310(this, 0, obj, 0x6334d0ad, 0xaf);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 3: kind 2/0/1.
    {
        void* obj = MakeStarBody(this, star, nameGen, 2, 0, 1, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }

    // Body 4: kind 1/2/0.
    {
        void* obj = MakeStarBody(this, star, nameGen, 1, 2, 0, false);
        FUN_00ba64a0(this, 0, obj, star, 0);
        star->mnBodyIndex++;
        StarBody_Release(obj);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ba91b0  cStarManager::InitStarOrbit(star*) : __thiscall (ret 4)
// ---------------------------------------------------------------------------
void FUN_00ba91b0(void* self, void* star)
{
    char* p = (char*)star;
    p[0x98] = 0;
    void* props = *(void**)((char*)self + 0x1a4);

    float f = FUN_010431e0(props, 0x1960010);
    float a = f; if (a <= 0.0f) a = 0.0f; if (a >= 89.0f) a = 89.0f;

    double d = 0.0;
    float* v = (float*)FUN_00ba8650(&d, a * 0.017453292f);
    *(float*)(p + 0x9c) = v[0];
    *(float*)(p + 0xa0) = v[1];
    *(float*)(p + 0xa4) = v[2];

    float g = FUN_010431e0(props, 0x1960011);
    float base = g <= 1.0f ? 1.0f : g;
    float lo = base * 0.9f;
    float hi = base * 1.1f;
    float r = (float)(sMathRandom.RandomDoubleUniform() * (hi - lo) + lo);
    *(float*)(p + 0xa8) = r < hi ? (r < lo ? lo : r) : hi;
}

// ---------------------------------------------------------------------------
// Property table lookup used by the BuildPlanet radius tail.
// ---------------------------------------------------------------------------
struct PropertyObject {
    char     pad_0000[0x12];
    uint16_t mnType;   // +0x12  (0xd == float)
};
typedef bool (__thiscall* GetPropertyFn)(void* self, uint32_t id, void** out);

// Property-table lookup: the original calls the virtual at vtable +0x24 and only
// accepts a float property.  mpProperties == 0 leaves the caller's default.
static float GetPropertyFloat(void* props, uint32_t id, float fallback)
{
    if (props != 0) {
        void* prop = 0;
        GetPropertyFn fn = (GetPropertyFn)(*(void***)props)[9];
        if (fn(props, id, &prop) && ((PropertyObject*)prop)->mnType == 0xd)
            return *FUN_0041ea70(prop, 0);
    }
    return fallback;
}

// ---------------------------------------------------------------------------
// @ 0x00ba8c40  cStarManager::BuildPlanet(system*, out*, p4, p5, p6)
//              __thiscall, ret 0x14
//
// Splits the feature amount across p4/p5, builds the surface orientation
// quaternion from an inclination and a random spin, rotates the Z/X unit axes
// through it, stores the two orthogonal vectors, derives the density weight and
// finally the radius from the star mass (p6 == 0) or the body's own density.
// ---------------------------------------------------------------------------
void cStarManager::BuildPlanet(void* system, void* out, float p4, float p5, void* p6)
{
    unsigned char* o = (unsigned char*)out;
    *o = 0;

    // Split the requested feature amount between p4 and p5.
    float feat = p5 - p4;
    if (feat > 0.0f) {
        float t = (float)(SP::sMathRandom.RandomDoubleUniform() * (double)feat);
        if (t > feat) t = feat;
        if (t < 0.0f) t = 0.0f;
        float rem = feat - t;
        if (rem > 0.0f) {
            float t2 = (float)(SP::sMathRandom.RandomDoubleUniform() * (double)rem);
            if (t2 >= rem) t2 = rem;
            if (t2 < 0.0f) t2 = 0.0f;
            p4 += t2;
        }
        p5 = p4 + t;
    }

    // Inclination (degrees, clamped) converted to radians.
    float incl = FUN_010431e0(mpProperties, 0x1960001);
    if (incl < 0.0f) incl = 0.0f;
    if (incl > kfMaxInclination) incl = kfMaxInclination;
    incl *= kfDegToRad;

    // Random full turn, then a spin angle uniformly inside [-incl, incl].
    float turn = (float)(SP::sMathRandom.RandomDoubleUniform() * (double)g_RandomTurns);
    float lo = -incl;
    float hi = incl;
    float spin = (float)(SP::sMathRandom.RandomDoubleUniform() * ((double)hi - (double)lo) + (double)lo);
    if (spin >= hi) spin = hi;
    else if (spin < lo) spin = lo;
    float half1 = spin * kfHalf;
    float half2 = turn * kfHalf;

    float s1 = (float)sin((double)half1), c1 = (float)cos((double)half1);
    float s2 = (float)sin((double)half2), c2 = (float)cos((double)half2);

    // q = (axisZ * sin2, cos2) * (axisX * sin1, cos1)
    float x0 = kAxisX[0] * s1, x1 = kAxisX[1] * s1, x2 = kAxisX[2] * s1;
    float z0 = kAxisZ[0] * s2, z1 = kAxisZ[1] * s2, z2 = kAxisZ[2] * s2;
    float q[4];
    q[0] = (c2 * x0 + c1 * z0) + (z1 * x2 - z2 * x1);
    q[1] = (c2 * x1 + c1 * z1) + (z2 * x0 - z0 * x2);
    q[2] = (c2 * x2 + c1 * z2) + (z0 * x1 - z1 * x0);
    q[3] = c2 * c1 - ((z0 * x0 + z2 * x2) + z1 * x1);

    // Surface normal: rotate the Z axis; tangent frame: rotate the X axis.
    float up[3];
    FUN_0059aed0(up, (void*)kAxisZ, q);
    *(float*)(o + 4)  = up[0];
    *(float*)(o + 8)  = up[1];
    *(float*)(o + 12) = up[2];

    float side[3];
    FUN_0059aed0(side, (void*)kAxisX, q);
    float lenSq = (side[0] * side[0] + side[2] * side[2]) + side[1] * side[1];
    float inv = (float)(1.0 / sqrt((double)(lenSq + kfEpsilon)));
    *(float*)(o + 0x14) = (inv * side[0]) * p4;
    *(float*)(o + 0x18) = (inv * side[1]) * p4;
    *(float*)(o + 0x1c) = (inv * side[2]) * p4;

    // Density weight: the smaller of the property and the radius ratio.
    float w1 = FUN_010431e0(mpProperties, 0x1960000);
    if (w1 < 0.0f) w1 = 0.0f;
    if (w1 > kfWeightMax) w1 = kfWeightMax;
    float ratio = (p5 - p4) / (p4 + p5);
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > kfWeightMax) ratio = kfWeightMax;
    *(float*)(o + 0x10) = (w1 <= ratio) ? w1 : ratio;

    if (p6 == 0) {
        float mass = FUN_00c841a0(FUN_00801920(system, 0));
        float density = GetPropertyFloat(mpProperties, 0x1960021, kfDensityDefault);
        float dm = density / mass;
        *(float*)(o + 0x20) = (float)sqrt((double)(((p4 * p4) * p4) * (dm * dm) * kfVolumeScaleStar));
    } else {
        int kind = *(int*)((char*)p6 + 0x28);
        uint32_t key = 0x1960020u + (kind != 1 ? 0x3bb977bu : 0u);
        float density = GetPropertyFloat(mpProperties, key, kfDensityGas);
        *(float*)(o + 0x20) = (float)sqrt((double)((density * density) * ((p4 * p4) * p4) * kfVolumeScaleRocky));
    }
    FUN_00fe8450(out, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00ba94e0  cdecl(int* writer, int* data) : serialize an eastl map.
// ---------------------------------------------------------------------------
void FUN_00ba94e0(int* writer, int* data)
{
    uint32_t v = *(uint32_t*)((char*)data + 0x14);
    void* s0 = (*(void* (__cdecl**)(int*))((char*)*(void**)writer + 0x20))(writer);
    void* w0 = (*(void* (__cdecl**)(void*))((char*)*(void**)s0 + 0x18))(s0);
    EA_IO_WriteUint32(w0, &v, 1, 0);

    int* it = *(int**)((char*)data + 8);
    for (int* end = (int*)((char*)data + 4); it != end;
         it = (int*)RBTreeIncrement(it)) {
        v = *(uint32_t*)((char*)it + 0x10);
        void* s1 = (*(void* (__cdecl**)(int*))((char*)*(void**)writer + 0x20))(writer);
        void* w1 = (*(void* (__cdecl**)(void*))((char*)*(void**)s1 + 0x18))(s1);
        EA_IO_WriteUint32(w1, &v, 1, 0);
        (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x1c))(writer);
        uint32_t tag = 0;
        void* val = *(void**)((char*)it + 0x14);
        if (val)
            tag = (*(uint32_t (__cdecl**)(int))((char*)*(void**)val + 0xc))(0x179c807);
        (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x2c))(writer);
        (void)tag;
    }
    (*(void (__cdecl**)(int*))((char*)*(void**)writer + 0x1c))(writer);
}

// ---------------------------------------------------------------------------
// eastl::lower_bound over 16-byte wstring records: cdecl(begin, end, value).
// The compare is "shorter length first, then lexicographic on wchar_t" and the
// original inlines it at every step.
// ---------------------------------------------------------------------------
static __forceinline int CompareWStrRec(int* rec, int* value)
{
    const uint16_t* a = (const uint16_t*)rec[0];
    const uint16_t* b = (const uint16_t*)value[0];
    int alen = (rec[1] - rec[0]) >> 1;
    int blen = (value[1] - value[0]) >> 1;
    int n = alen <= blen ? alen : blen;
    for (; n != 0; --n, ++a, ++b) {
        if (*a != *b)
            return *a < *b ? -1 : 1;
    }
    if (alen < blen) return -1;
    if (alen > blen) return 1;
    return 0;
}

// @ 0x00ba95f0
int* FUN_00ba95f0(int* begin, int* end, int* value)
{
    int count = (int)((char*)end - (char*)begin) >> 4;
    while (count > 0) {
        int half = count >> 1;
        int* mid = begin + half * 4;
        if (CompareWStrRec(mid, value) < 0) {
            begin = mid + 4;
            count -= half + 1;
        } else {
            count = half;
        }
    }
    return begin;
}

// ---------------------------------------------------------------------------
// @ 0x00ba96e0  cdecl(int* first, int* last, threshold*) : partition
//              (eastl::partition) returning the partition point.
// ---------------------------------------------------------------------------
static inline int RecKey(int* rec) { return *(int*)((char*)rec + 0x28); }
int* FUN_00ba96e0(int* first, int* last, int* thresh)
{
    int pivot = *(int*)((char*)thresh + 0x28);
    for (;;) {
        while (RecKey(*(int**)first) < pivot) ++first;
        while (pivot < RecKey(*(int**)(last - 1))) --last;
        if (first >= last) break;
        FUN_00b2af00(first, last - 1);
        ++first;
    }
    RefRelease(thresh);
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00ba9740  cdecl(int* a, int* b, int* c, void* d) : insertion/rotate
//              fix-up over an array of AutoRefCount pointers.
// ---------------------------------------------------------------------------
void FUN_00ba9740(int* a, int* b, int* c, void* d)
{
    FUN_00ba84b0(a, b, d);
    for (int* p = b; p < c; ++p) {
        int* v = (int*)*p;
        if (*(int*)((char*)v + 0x28) < *(int*)((char*)*a + 0x28)) {
            if (v) ((VCall1)(*(void***)v)[0])(v);
            int* cur = (int*)*a;
            if (cur != v) {
                if (cur) ((VCall1)(*(void***)cur)[0])(cur);
                *p = (int)cur;
                if (v) ((VCall1)(*(void***)v)[1])(v);
            }
            if (v) ((VCall1)(*(void***)v)[0])(v);
            FUN_00ba79a0(a, 0, (int)(b - a) / 4, 0);
            if (v) ((VCall1)(*(void***)v)[1])(v);
        }
    }
    FUN_00ba8500(a, b, d);
}