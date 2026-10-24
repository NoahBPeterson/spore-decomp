// Slice s00bac830: four SP species-selection helpers operating on
// eastl::sp_vector<EA::ResourceMan::Key> (12-byte elements).  Optimized module:
//   /O2 /MD /Gy /TP
//
// FUN_00bac830 / FUN_00baccd0 / FUN_00bad080 / FUN_00bad440 form a family that
// buckets species keys by their hash, then draws random entries out of the
// buckets.  The container helpers (erase 0x50f740, DoInsertValue 0x4e3e10,
// 0xb96600) are real out-of-line instantiations.
#include "types.h"

// ---------------------------------------------------------------------------
// Common EASTL containers / helpers
// ---------------------------------------------------------------------------
struct Key { uint32_t a, b, c; };                       // EA::ResourceMan::Key, 12 bytes

void __cdecl FreeBlock(void* p);                        // 0xf47380  operator_delete_array

struct KeyVec {                                         // eastl::vector<Key, sp_vector_allocator>
    Key* mBegin;                                        // +0x00
    Key* mEnd;                                          // +0x04
    Key* mCap;                                          // +0x08
    Key* erase(Key* first, Key* last);                  // 0x50f740
    void DoInsertValue(Key* pos, const Key& v);         // 0x4e3e10
    void push_back(const Key& v) {
        if (mEnd < mCap) { Key* p = mEnd; mEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mEnd, v);
    }
    void clear() { erase(mBegin, mEnd); }
    ~KeyVec() { if (mBegin && ((int*)mBegin)[-1] != 0) FreeBlock(mBegin); }
};

struct Species { uint32_t FUN_00b8f860(); };            // 0xb8f860 (this = species)
struct SpeciesManager { Species* FUN_00b90410(const Key& id); };       // 0xb90410
SpeciesManager* FUN_00b3d420();                         // 0xb3d420

struct Random { uint32_t FUN_00a68fb0(uint32_t max); }; // 0xa68fb0
extern Random g_mathRandom;                             // 0x1601760
static inline uint32_t Rnd(uint32_t max) { return g_mathRandom.FUN_00a68fb0(max); }

// ---------------------------------------------------------------------------
// @ 0x00bac830
// Buckets the input key vector by species hash into three working vectors,
// then draws a random subset of each bucket (in the order C, B, A) into the
// output vector.  Count selection depends on mode (1..3) and a random roll.
// ---------------------------------------------------------------------------
void __stdcall FUN_00bac830(KeyVec* inList, int param_2, int param_3, int mode, char flag, KeyVec* out)
{
    out->clear();
    SpeciesManager* mgr = FUN_00b3d420();

    KeyVec vA = { 0, 0, 0 };        // hash 0x6d60a1cc
    KeyVec vB = { 0, 0, 0 };        // hash 0x29c388a
    KeyVec vC = { 0, 0, 0 };        // hash 0x3a8be428

    for (Key* it = inList->mBegin; it != inList->mEnd; ++it) {
        Species* sp = mgr->FUN_00b90410(*it);
        if (sp) {
            uint32_t h = sp->FUN_00b8f860();
            if (h == 0x29c388a) vB.push_back(*it);
            else if (h == 0x3a8be428) vC.push_back(*it);
            else if (h == 0x6d60a1cc) vA.push_back(*it);
        }
    }

    uint32_t r = Rnd(3);
    bool b3 = (mode == 3) || (mode == 2 && r != 0) || (mode == 1 && r == 0);
    bool b2 = (mode == 3) || (mode == 2 && r != 1) || (mode == 1 && r == 1);
    bool b1 = (mode == 3) || (mode == 2 && r != 2) || (mode == 1 && r == 2);

    int n1 = param_2;
    if (flag == 0 && !b1 && (b2 || b3)) n1 = param_3;

    int c1 = 0;
    for (; c1 < n1; ++c1) {                     // phase 1: vC
        if (vC.mBegin == vC.mEnd) break;
        Key* chosen = vC.mBegin + Rnd((uint32_t)(int)(vC.mEnd - vC.mBegin));
        out->push_back(*chosen);
        Key* end = vC.mEnd;
        for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
        vC.mEnd = end - 1;
    }

    int n2 = param_2;
    if (flag == 0 && !b2 && (c1 == param_2 || b3)) n2 = param_3;

    int c2 = 0;
    for (; c2 < n2; ++c2) {                     // phase 2: vB
        if (vB.mBegin == vB.mEnd) break;
        Key* chosen = vB.mBegin + Rnd((uint32_t)(int)(vB.mEnd - vB.mBegin));
        out->push_back(*chosen);
        Key* end = vB.mEnd;
        for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
        vB.mEnd = end - 1;
    }

    int n3 = param_2;
    if (flag == 0 && !b3 && (c2 == param_2 || c1 == param_2)) n3 = param_3;

    for (int c3 = 0; c3 < n3; ++c3) {           // phase 3: vA
        if (vA.mBegin == vA.mEnd) break;
        Key* chosen = vA.mBegin + Rnd((uint32_t)(int)(vA.mEnd - vA.mBegin));
        out->push_back(*chosen);
        Key* end = vA.mEnd;
        for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
        vA.mEnd = end - 1;
    }
}

// ---------------------------------------------------------------------------
// Splits the input key vector into two buckets (profile +0x608 == 0 / != 0),
// then draws from each bucket (bounded by counts derived from the arguments),
// falling back to fixed resource keys when a bucket runs dry.
// ---------------------------------------------------------------------------
struct Profile { char pad[0x608]; int m608; };          // cSpeciesProfile, flag at +0x608
struct ProfileMgr { Profile* FUN_004df550(const Key& k); };            // 0x4df550
ProfileMgr* FUN_00401090();                             // 0x401090

struct Obj10a0 { char pad[0x504]; Key mKey; };          // key at +0x504
struct Obj3d450 { Obj10a0* FUN_00ac10a0(); };           // 0xac10a0 (this = b3d450 result)
Obj3d450* FUN_00b3d450(uint32_t k);                     // 0xb3d450

static inline uint32_t DrawIndex(Key* begin, Key* end)
{
    uint32_t n = (uint32_t)(end - begin);
    return (n < 2) ? 0 : Rnd(n);
}

// @ 0x00baccd0
void __stdcall FUN_00baccd0(KeyVec* inList, int p2, int p3, int p4, int p5, KeyVec* out)
{
    out->clear();
    ProfileMgr* mgr = FUN_00401090();

    int bound;
    if (p3 < p2) { bound = p4 + p3 * 2; p2 = (bound / 2 - p3) * p5 + p3; }
    else { bound = p2 * 2; }

    KeyVec vZero = { 0, 0, 0 };     // profile +0x608 == 0
    KeyVec vNon = { 0, 0, 0 };      // profile +0x608 != 0

    for (Key* it = inList->mBegin; it != inList->mEnd; ++it) {
        Profile* pr = mgr->FUN_004df550(*it);
        if (!pr) continue;
        if (pr->m608 == 0) vZero.push_back(*it);
        else vNon.push_back(*it);
    }

    int done1 = 0;
    for (; done1 < bound; ++done1) {
        Key tmp;
        if (vZero.mBegin == vZero.mEnd) {
            Obj10a0* r = FUN_00b3d450(0xef2601ca)->FUN_00ac10a0();
            if (!r) break;
            tmp = r->mKey;
        } else {
            Key* chosen = vZero.mBegin + DrawIndex(vZero.mBegin, vZero.mEnd);
            tmp = *chosen;
            Key* end = vZero.mEnd;
            for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
            vZero.mEnd = end - 1;
        }
        out->push_back(tmp);
    }

    int bound2 = p2;
    if (done1 / 2 < p2) bound2 = done1 / 2;

    int done2 = 0;
    for (; done2 < bound2; ++done2) {
        Key tmp;
        if (vNon.mBegin == vNon.mEnd) {
            Obj10a0* r = FUN_00b3d450(0x5029da65)->FUN_00ac10a0();
            if (!r) break;
            tmp = r->mKey;
        } else {
            Key* chosen = vNon.mBegin + DrawIndex(vNon.mBegin, vNon.mEnd);
            tmp = *chosen;
            Key* end = vNon.mEnd;
            for (Key* p = chosen; p + 1 != end; ++p) *p = *(p + 1);
            vNon.mEnd = end - 1;
        }
        out->push_back(tmp);
    }

    for (Key* it = out->mBegin; it != out->mEnd; ++it) mgr->FUN_004df550(*it);
}

// ---------------------------------------------------------------------------
// Collects model keys for the current game mode; if the property-manager
// lookup returns nothing, scans the model RB-tree and buckets the entries by
// species hash, then (three rounds) draws one random entry from each bucket.
// ---------------------------------------------------------------------------
struct IntVec {                                         // eastl::vector<int, sp_vector_allocator>
    int* mBegin;                                        // +0x00
    int* mEnd;                                          // +0x04
    int* mCap;                                          // +0x08
    void DoInsertValue(int* pos, const int& v);         // 0xb96600
    void push_back(const int& v) {
        if (mEnd < mCap) { int* p = mEnd; mEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mEnd, v);
    }
    void erase(int* pos) {
        int* end = mEnd;
        for (int* p = pos; p + 1 != end; ++p) *p = *(p + 1);
        mEnd = end - 1;
    }
    ~IntVec() { if (mBegin && ((int*)mBegin)[-1] != 0) FreeBlock(mBegin); }
};

struct RefCount { virtual void v00(); virtual void Release(); };       // +0x04
struct PropMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool Lookup(uint32_t a, uint32_t b, RefCount** out);       // slot 0x2c
    virtual void LookupRefs(uint32_t a, uint32_t b, KeyVec* out);      // slot (used by bad080)
};
PropMgr* PropertyManager();                             // 0x67de30

struct Obj080 { virtual Key* GetKey(); };               // vtable +0x18 -> Key*
struct RBTree { char pad[4]; void* mHead; void* mRoot; };// +0x04 header, +0x08 root
RBTree* FUN_006b42e0();                                 // 0x6b42e0
void* RBTreeIncrement(void* node);                      // 0x921580
Key* FUN_00b8d8e0();                                    // 0xb8d8e0
void FUN_00baa080(KeyVec* v);                           // 0xbaa080
int FUN_00ba6ab0(int* p);                               // 0xba6ab0

// @ 0x00bad080
void __stdcall FUN_00bad080(Key* base, KeyVec* out)
{
    PropMgr* pm = PropertyManager();
    RefCount* local = 0;
    if (local) { RefCount* t = local; local = 0; t->Release(); }

    KeyVec ml = { 0, 0, 0 };
    pm->LookupRefs(base->a, base->c, &ml);

    if ((int)(ml.mEnd - ml.mBegin) > 0) {
        for (Key* p = ml.mBegin; p != ml.mEnd; ++p) out->push_back(*p);
        if (ml.mBegin && ((int*)ml.mBegin)[-1] != 0) FreeBlock(ml.mBegin);
        return;
    }

    IntVec vZ = { 0, 0, 0 };        // hash 0x6d60a1cc
    IntVec vX = { 0, 0, 0 };        // hash 0x29c388a
    IntVec vY = { 0, 0, 0 };        // hash 0x3a8be428

    RBTree* tree = FUN_006b42e0();
    void* head = (char*)tree + 4;
    for (void* n = *(void**)((char*)tree + 8); n != head; n = RBTreeIncrement(n)) {
        uint32_t id = *(uint32_t*)((char*)n + 0x1c);
        uint32_t h = ((Species*)id)->FUN_00b8f860();
        if (h == 0x29c388a) vX.push_back((int)id);
        else if (h == 0x3a8be428) vY.push_back((int)id);
        else if (h == 0x6d60a1cc) vZ.push_back((int)id);
    }

    for (int round = 0; round < 3; ++round) {
        if (vZ.mBegin != vZ.mEnd) {
            int* chosen = vZ.mBegin + Rnd((uint32_t)(vZ.mEnd - vZ.mBegin));
            Obj080* o = (Obj080*)*chosen;
            Key* k = o->GetKey();
            out->push_back(*k);
            vZ.erase(chosen);
        }
        if (vX.mBegin != vX.mEnd) {
            int* chosen = vX.mBegin + Rnd((uint32_t)(vX.mEnd - vX.mBegin));
            Obj080* o = (Obj080*)*chosen;
            Key* k = o->GetKey();
            out->push_back(*k);
            vX.erase(chosen);
        }
        if (vY.mBegin != vY.mEnd) {
            int* chosen = vY.mBegin + Rnd((uint32_t)(vY.mEnd - vY.mBegin));
            Obj080* o = (Obj080*)*chosen;
            Key* k = o->GetKey();
            out->push_back(*k);
            vY.erase(chosen);
        }
    }
    if (ml.mBegin && ((int*)ml.mBegin)[-1] != 0) FreeBlock(ml.mBegin);
}

// ---------------------------------------------------------------------------
// Entry point: derives a mode count from param_1 +0x28, adjusts the config
// bitmask, then drives the two selection passes (bad080 / baccd0).
// ---------------------------------------------------------------------------
struct Obj440 {
    char pad0[0x28];
    int  m28;                                           // +0x28 (3/4/5)
    char pad2c[0xbc - 0x2c];
    KeyVec mBc;                                         // +0xbc
    char padC8[0xd0 - 0xc8];
    KeyVec mD0;                                         // +0xd0
};
struct Cfg440 {
    char    pad0c[0x0c];
    uint8_t m0c;                                        // +0x0c
    char    pad0d[3];
    int     m10;                                        // +0x10 bitmask / value
    int     m14;                                        // +0x14
    int     m18;                                        // +0x18
    int     m1c;                                        // +0x1c
    KeyVec  m20;                                        // +0x20
    KeyVec  m34;                                        // +0x34
};

static inline int ClampHi(int v, int hi) { return (v > hi) ? hi : v; }

struct Self440 {                            // incoming ecx: unused `this` (thiscall)
    void FUN_00bad440(Obj440* param_1, Cfg440* param_2);
};

// @ 0x00bad440
void Self440::FUN_00bad440(Obj440* param_1, Cfg440* param_2)
{
    int m28 = param_1->m28;
    int mode;
    if (m28 == 3) mode = 1;
    else if (m28 == 4) mode = 2;
    else if (m28 == 5) mode = 3;
    else return;

    if (param_2) {
        if (mode < 3) param_2->m10 &= 0xfffffff7;
        if (mode < 2) param_2->m10 &= 0xfffffffb;
        if (mode < 1) param_2->m10 &= 0xfffffffd;
        if (mode > 1) param_2->m10 &= 0xfffffffe;
        if (mode > 2) param_2->m10 &= 0xfffffffd;
        if (param_2->m10 == 0) {
            if (mode == 1) param_2->m10 |= 1;
            else if (mode == 2) param_2->m10 |= 2;
            else if (mode == 3) param_2->m10 |= 4;
        }
    }

    KeyVec vout = { 0, 0, 0 };
    if (!param_2 || param_2->m20.mBegin == param_2->m20.mEnd) {
        Key base = *FUN_00b8d8e0();
        Key tmp = base;
        PropMgr* pm = PropertyManager();
        RefCount* ref = 0;
        bool ok = pm->Lookup(base.a, base.c, &ref);
        if (!ok) {
            tmp.c = 0x4184a100;
            if (ref) { RefCount* r = ref; ref = 0; r->Release(); }
            ok = pm->Lookup(base.a, 0x4184a100, &ref);
            if (!ok) tmp.c = 0x4184ac00;
        }
        FUN_00bad080(&tmp, &vout);
        if (ref) ref->Release();
    } else {
        FUN_00baa080(&param_2->m20);
    }

    int flagVar;
    int arg3;
    int iVar10;
    int roll = 6;
    bool haveRoll = false;

    if (param_2 == 0) {
        flagVar = 0;
        arg3 = (mode == 0) ? 0 : mode - 1;
    } else {
        flagVar = param_2->m0c;
        if (flagVar != 0) {
            iVar10 = 3;
            arg3 = mode;
            haveRoll = true;
        } else {
            arg3 = FUN_00ba6ab0(&param_2->m10);
        }
    }

    if (!haveRoll) {
        roll = (int)Rnd(6) + 1;
        if (param_2 == 0) iVar10 = (2 < roll) ? 3 : roll;
        else iVar10 = FUN_00ba6ab0(&param_2->m14);
    }

    FUN_00bac830(&vout, mode, arg3, iVar10, (char)flagVar, &param_1->mBc);

    KeyVec v2 = { 0, 0, 0 };
    if (param_2 && param_2->m34.mBegin != param_2->m34.mEnd) FUN_00baa080(&param_2->m34);

    int iv9 = 0;
    if (2 < iVar10) {
        if (flagVar == 0) {
            if (param_2 == 0) {
                int a = roll - 3;
                int v = (1 < a) ? 2 : a;
                if (v < 1) v = 0;
                iv9 = v;
            } else iv9 = FUN_00ba6ab0(&param_2->m18);
        } else iv9 = 2;
    }

    if (iVar10 < 3) iVar10 = 0;
    else if (flagVar == 0) {
        if (param_2 == 0) {
            int c = roll - 5;
            int v = ClampHi(c, 1);
            if (v < 1) v = 0;
            iVar10 = v;
        } else iVar10 = FUN_00ba6ab0(&param_2->m1c);
    } else iVar10 = 1;

    FUN_00baccd0(&v2, mode, arg3, iv9, iVar10, &param_1->mD0);
}