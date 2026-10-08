// Slice s00c80ce0 -- SP::cSimPlanetLowLOD::UpdateFloraAndFauna (0x00c810e0, 1790 bytes).
//
// Recounts the species present on a planet (flora and fauna hash maps), then reports the species that
// just went extinct:
//   * returns at once when the sim is inactive, or when this is the active planet in the
//     space stage with no universe context and the avatar flag (+0x158) is set;
//   * seeds the remembered land-cell count (96 * (1 - water score), floored) on first use
//     and publishes land/3 to two globals;
//   * zeroes the per-species counters of the scratch state (one entry per species of the
//     planet record), lets the cell callback (0x00c81070) refill them, then swaps the scratch
//     maps / cell count with the sim's own (hashtable::swap inlined);
//   * every species whose new count is 0 is queued on a list (flora list, fauna list);
//     on the active planet an extinction message is posted for it (the fauna loop only if the
//     planet record is not flagged 0x800);
//   * the cargo / UI helpers are told about every queued species, the extinction map is
//     cleared, the stage-flag mask of the scratch state is applied, and the lists are freed.
//
// Retail layout of cSimPlanetLowLOD is the 2008 PDB layout + 0x70. Names are Claude-coined
// unless a symbol is known.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc)
#include "types.h"

typedef unsigned int uint;

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);                                   // 0x00f473a0
void operator delete[](void* p);                                                 // 0x00f47380

// float -> int rounding down (the module's asm helper: cvtss2si + cmovb).
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

struct Key {                       // EA::ResourceMan::Key
    uint32_t instance, type, group;
    inline void* operator new(unsigned int, void* p) { return p; }
    inline void operator delete(void*, void*) {}
};

// ---------------------------------------------------------------- hash map (eastl::hash_map<Key,int>)
struct HNode {
    Key    key;                    // +0
    int    val;                    // +0xc
    HNode* next;                   // +0x10
};
struct HIter { HNode* node; HNode** bucket; };
struct HPair { Key key; int val; };
struct Tag {};
struct HRehash { uint maxLoad; uint growth; uint nextResize; };

struct HashMap {
    char     pad0[4];              // hash / equal / extract (empty)
    HNode**  mpBuckets;            // +4
    uint     mnBuckets;            // +8
    uint     mnElements;           // +0xc
    HRehash  mRehash;              // +0x10
    uint     mAllocator;           // +0x1c

    HIter* find(HIter* out, const Key* k);                    // 0x00833840 (ret 8)
    HIter* insert(HIter* out, const HPair* p, Tag t);        // 0x00a26e10 (ret 0xc)
    int*   Index(const Key* k);                               // 0x00c80110 (ret 4): operator[]
    HNode* end() const { return mpBuckets[mnBuckets]; }

    // operator[] inlined
    __forceinline int& at(const Key* k)
    {
        HIter it;
        find(&it, k);
        HNode* n = it.node;
        if (n == end()) {
            HPair p;
            p.key = *k;
            p.val = 0;
            Tag tag;
            HIter r;
            insert(&r, &p, tag);
            n = r.node;
        }
        return n->val;
    }

    __forceinline void swap(HashMap& o)
    {
        HRehash t = mRehash;
        mRehash = o.mRehash;
        o.mRehash = t;
        HNode** b = mpBuckets;  mpBuckets = o.mpBuckets;  o.mpBuckets = b;
        uint c = mnBuckets;  mnBuckets = o.mnBuckets;  o.mnBuckets = c;
        uint e = mnElements;  mnElements = o.mnElements;  o.mnElements = e;
    }
};

// ---------------------------------------------------------------- eastl::list<Key>
struct LNode {
    LNode* next;
    LNode* prev;
    Key    key;
};
struct KeyList {
    LNode* next;
    LNode* prev;
    KeyList() { next = prev = (LNode*)this; }
    bool empty() const { return next == (LNode*)this; }
    __forceinline void push_back(const Key* k)
    {
        LNode* n = (LNode*)operator new(0x14, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        new (&n->key) Key(*k);
        n->next = (LNode*)this;
        n->prev = prev;
        prev->next = n;
        prev = n;
    }
    ~KeyList()
    {
        LNode* p = next;
        while (p != (LNode*)this) {
            LNode* q = p;
            p = p->next;
            operator delete[](q);
        }
    }
};

// ---------------------------------------------------------------- extinction map (eastl::map<Key,uint>)
struct RbNode {
    RbNode* right;   // +0
    RbNode* left;    // +4
    RbNode* parent;  // +8
    char    color;   // +0xc
    Key     key;     // +0x10
    uint    value;   // +0x1c
};
struct RbBase {
    RbNode* right;   // +0
    RbNode* left;    // +4
    RbNode* parent;  // +8
    char    color;   // +0xc
};
struct RbTree {
    char   pad0[4];
    RbBase anchorNode;     // +4: right +4, left +8, parent +0xc, color +0x10
    uint   mnSize;         // +0x14
    RbNode** FindExtinct(RbNode** out, const Key* k);   // 0x00a21dc0 (ret 8)
    void DoNukeSubtree(RbNode* n);               // @ 0x009a9600 (ret 4)
};

// ---------------------------------------------------------------- planet / globals
struct PlanetRecord {
    char     pad0[0x2c];
    uint     mFlags;           // +0x2c
    char     pad1[0xbc - 0x30];
    char*    mpABegin;         // +0xbc (12-byte elements: Key)
    char*    mpAEnd;           // +0xc0
    char     pad2[0xd0 - 0xc4];
    char*    mpBBegin;         // +0xd0
    char*    mpBEnd;           // +0xd4
};
struct cPlanet {
    char          pad0[0x13c];
    PlanetRecord* mpRecord;    // +0x13c
    float GetWaterScore();     // 0x00c71d30
};

struct ScratchState {
    char     flags[3];         // +0..2 stage flags
    char     pad3;
    int      landCell;         // +4
    HashMap  flora;            // +8
    HashMap  fauna;            // +0x28
};

struct Avatar { char pad[0x158]; char mFlag; };
struct GameNounManager { Avatar* GetAvatar(); };    // 0x00b1fdb0
GameNounManager* SpaceGameGet();                    // 0x01002bd0
cPlanet* GetActivePlanet();                         // 0x01021260
void*    GetUniverseContext();                      // 0x01021080

struct SpeciesA { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual int GetFeedbackID(); };     // +0x28
struct PlantSpeciesManager { SpeciesA* GetSpeciesFromID(const Key* k); };   // 0x00b90410
PlantSpeciesManager* PlantSpecies();                // 0x00b3d420 (global)
struct SpeciesProfile { char pad[0x51c]; int mFeedbackID; };
struct EditorSpeciesManager { SpeciesProfile* GetProfile(const Key* k); };  // 0x004df550
EditorSpeciesManager* EditorSpecies();              // 0x00401090 (global)

struct SpaceTokenTranslator { char pad[0x34]; int mToken; };
extern SpaceTokenTranslator* gpSpaceTokenTranslator;   // 0x016e0d08

struct cSPUIEventLog {
    void PostFeedbackEvent(uint a, uint b, int c, int d, int e, int f);   // 0x00dd8640 (ret 0x18)
};
cSPUIEventLog* EventLog();                          // 0x00b3d3e0

struct cSPUISpace {
    void UpdateCargoSlots(const Key* k, cPlanet* p);    // @ 0x00bbc540 (ret 8)
    void UpdateCargoSlots2(const Key* k, cPlanet* p);   // 0x00bbcb10 (ret 8)
    void Refresh1(cPlanet* p);                          // 0x00bbf2b0 (ret 4)
    void Refresh2(cPlanet* p);                          // 0x00bbe740 (ret 4)
};
cSPUISpace* TerraformingManager();                  // 0x00b3d430 (global)

struct StageManager { void Apply(uint mask); };     // 0x00b2a750 (ret 4)
StageManager* GetStageManager();                    // 0x00b3d3b0 (global)

// 0x00c81070: per-cell callback (a code label, not a Ghidra function), passed by address
#define CELL_CALLBACK ((void (*)())0x00c81070)

struct cSimPlanetLowLOD {
    char    pad0[0x2058];
    bool    mActive;           // +0x2058
    int     mLandCell;         // +0x205c
    HashMap mFlora;            // +0x2060
    HashMap mFauna;            // +0x2080
    RbTree  mExtinct;          // +0x20a0

    void ForEachCell(cPlanet* planet, void (*cb)(), int zero, ScratchState* st);   // 0x00c7e780 (ret 0x10)
    void UpdateFloraAndFauna(cPlanet* planet, ScratchState* st);                   // 0x00c810e0
};

// @ 0x00c810e0
void cSimPlanetLowLOD::UpdateFloraAndFauna(cPlanet* planet, ScratchState* st)
{
    if (!mActive)
        return;

    if (planet == GetActivePlanet() && GetUniverseContext() == 0) {
        if (SpaceGameGet()->GetAvatar()->mFlag)
            return;
    }

    if (mLandCell < 0) {
        float f = (1.0f - planet->GetWaterScore()) * 96.0f;
        mLandCell = FloorToInt(f);
    }
    *(int*)0x01694ba8 = mLandCell / 3;
    *(int*)0x01694ba4 = mLandCell / 3;

    PlanetRecord* rec = planet->mpRecord;
    int nA = (int)(rec->mpAEnd - rec->mpABegin) / 12;
    if (nA > 0) {
        int off = 0;
        int n = nA;
        do {
            int* v = st->flora.Index((Key*)(rec->mpABegin + off));
            off += 12;
            n--;
            *v = 0;
        } while (n != 0);
    }
    int nB = (int)(rec->mpBEnd - rec->mpBBegin) / 12;
    if (nB > 0) {
        int off = 0;
        int n = nB;
        do {
            int& v = st->fauna.at((Key*)(rec->mpBBegin + off));
            off += 12;
            n--;
            v = 0;
        } while (n != 0);
    }

    ForEachCell(planet, CELL_CALLBACK, 0, st);

    mLandCell = st->landCell;
    mFlora.swap(st->flora);
    mFauna.swap(st->fauna);

    KeyList floraList;
    if (nA > 0) {
        int off = 0;
        int n = nA;
        do {
            Key* k = (Key*)(rec->mpABegin + off);
            if (mFlora.at(k) == 0) {
                floraList.push_back(k);
                uint v = 0x540e11a3;
                RbNode* it;
                mExtinct.FindExtinct(&it, k);
                if (it != (RbNode*)&mExtinct.anchorNode)
                    v = it->value;
                if (planet == GetActivePlanet()) {
                    SpeciesA* sp = PlantSpecies()->GetSpeciesFromID(k);
                    int id = sp->GetFeedbackID();
                    if (id != 0) {
                        gpSpaceTokenTranslator->mToken = id;
                        EventLog()->PostFeedbackEvent(v, 0x131a9f54, 0, 0, 1, 0);
                    }
                }
            }
            off += 12;
            n--;
        } while (n != 0);
    }

    KeyList faunaList;
    if (!(rec->mFlags & 0x800) && nB > 0) {
        int off = 0;
        int n = nB;
        do {
            Key* k = (Key*)(rec->mpBBegin + off);
            if (mFauna.at(k) == 0) {
                faunaList.push_back(k);
                RbNode* it;
                mExtinct.FindExtinct(&it, k);
                uint v;
                if (it == (RbNode*)&mExtinct.anchorNode)
                    v = 0x540e11a3;
                else
                    v = it->value;
                if (planet == GetActivePlanet()) {
                    SpeciesProfile* pr = EditorSpecies()->GetProfile(k);
                    if (pr && pr->mFeedbackID != 0) {
                        gpSpaceTokenTranslator->mToken = pr->mFeedbackID;
                        EventLog()->PostFeedbackEvent(v, 0x131a9f54, 0, 0, 1, 0);
                    }
                }
            }
            off += 12;
            n--;
        } while (n != 0);
    }

    cSPUISpace* ui = TerraformingManager();
    for (LNode* p = floraList.next; p != (LNode*)&floraList; p = p->next)
        ui->UpdateCargoSlots(&p->key, planet);
    for (LNode* p = faunaList.next; p != (LNode*)&faunaList; p = p->next)
        ui->UpdateCargoSlots2(&p->key, planet);
    if (!floraList.empty() || !faunaList.empty()) {
        ui->Refresh1(planet);
        ui->Refresh2(planet);
    }

    // mExtinct.clear()
    RbNode* root = mExtinct.anchorNode.parent;
    while (root) {
        mExtinct.DoNukeSubtree(root->right);
        RbNode* nx = root->left;
        operator delete[](root);
        root = nx;
    }
    mExtinct.anchorNode.left = (RbNode*)&mExtinct.anchorNode;
    mExtinct.anchorNode.right = (RbNode*)&mExtinct.anchorNode;
    mExtinct.anchorNode.parent = 0;
    mExtinct.anchorNode.color = 0;
    mExtinct.mnSize = 0;

    uint flags = 0;
    if (st->flags[0]) flags = 1;
    if (st->flags[1]) flags |= 2;
    if (st->flags[2]) flags |= 4;
    if (flags != 0)
        GetStageManager()->Apply(flags);
}
