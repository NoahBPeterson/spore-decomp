// Shared declarations for slice s00a52ff0 (EA::Audio::Eapd fracplay: fixed pool, voices, params).
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------------------
// Allocator / FixedPool (PDB: EA::Audio::Eapd::FixedPool, size 0x30)
// vtable: +0 dtor, +4 ?, +8 Alloc, +0xc Free
// ---------------------------------------------------------------------------
class Allocator { public:
    virtual ~Allocator() {}                       // +0x00
    virtual void  v04();                          // +0x04
    virtual void* v08(uint32_t n);                // +0x08
    virtual void  v0c(void* p);                   // +0x0c
    void* mpCoreAllocator;                        // +0x04
    void* mpNamePtr;                              // +0x08
};

class FixedPool { public:
    Allocator mInitAllocator;                     // +0x00
    Allocator mOverflowAllocator;                 // +0x0c
    uint32_t  mnNodeSize;                         // +0x18
    void*     mpPoolBegin;                        // +0x1c
    void*     mpPoolEnd;                          // +0x20
    void*     mpHead;                             // +0x24
    uint32_t  mnCurrentSize;                      // +0x28
    uint32_t  mnPeakSize;                         // +0x2c
    // +0x30

    ~FixedPool();
    bool Init(uint32_t nodeSize, int count, struct InitAllocator* a1, struct InitAllocator* a2);
    void* Alloc();
};

class FixedHashtableAllocator : public FixedPool { public:
    uint32_t  mnBucketCount;                      // +0x30
    void*     mpBucketBuffer;                     // +0x34
    // +0x38

    ~FixedHashtableAllocator();
    bool InitBuckets(unsigned count, struct InitAllocator* a1, struct InitAllocator* a2);
};

// ---------------------------------------------------------------------------
// fixed_list / list nodes
// ---------------------------------------------------------------------------
struct ListLink {
    ListLink* mpNext;      // +0x00
    ListLink* mpPrev;      // +0x04
};
struct VoiceNode : ListLink {
    unsigned  mValue;      // +0x08
};

struct VoiceList {
    ListLink  mNode;       // +0x00 sentinel (8 bytes)
    FixedPool mPool;       // +0x08
    // +0x38

    ~VoiceList();
    void Clear();
    void PopFront();
    void PushBack(ListLink* anchor, const unsigned* value2);
};
// ---------------------------------------------------------------------------
// Parameter hash map
// ---------------------------------------------------------------------------
class Symbol { public:                 // 8 bytes
    unsigned    mHash;          // +0x00
    const char* mpName;         // +0x04
};

struct ParamPair {              // pair<Symbol const, _atom> = 0x14
    Symbol   first;             // +0x00
    unsigned a_type;            // +0x08
    union {
        float          a_float;   // +0x0c
        const char*    a_sym;     // +0x0c
    };
    const char* a_sym2;         // +0x10
};

struct ParamNode {
    ParamPair   mValue;         // +0x00
    ParamNode*  mpNext;         // +0x14
};

struct ParamTable {
    void*        mpVftable;       // +0x00
    ParamNode**  mpBucketArray;   // +0x04
    unsigned     mnBucketCount;   // +0x08
    unsigned     mnElementCount;  // +0x0c
    unsigned     pad10[3];        // +0x10 rehash policy
    FixedHashtableAllocator mAllocator;   // +0x1c (FixedPool at +0x1c)
    // +0x54

    ~ParamTable();
    void FreeBuckets(ParamNode** buckets, unsigned n);
    ParamNode* AllocNode(const ParamPair* v);
    void Bucket(void** out, const Symbol* key, void* a3, void* a4);
    unsigned Find(Symbol* key, ParamPair* out);
    ParamPair* LocateOrInsert(const Symbol* key);
};

struct ParamIter {
    void*        mpVftable;      // +0x00
    ParamNode*   mpNode;         // +0x04
    ParamNode**  mpBucket;       // +0x08
    ParamNode*   mpLast;         // +0x0c
    ParamNode**  mpBucketEnd;    // +0x10
    ParamTable*  mpTable;        // +0x14
    // +0x18

    ParamIter(ParamTable* t);
    unsigned Next(Symbol* out, ParamPair* value);
};

// ---------------------------------------------------------------------------
// Play (PDB: EA::Audio::Eapd::Play, 0xb8)
// ---------------------------------------------------------------------------
class Play { public:
    VoiceList   mVoices;         // +0x00
    ParamTable  mParameters;     // +0x38
    unsigned    mnBusyVoices;    // +0x8c
    unsigned    mnMaxVoices;     // +0x90
    unsigned    mnMaxParameters; // +0x94
    void*       mVoiceManager;   // +0x98
    void*       mInstance;       // +0x9c
    Symbol      mName;           // +0xa0
    bool        mbSteal;         // +0xa8
    bool        mbUpdatePlaying; // +0xa9
    bool        mbPaused;        // +0xaa
    int         mnStepRule;      // +0xac
    unsigned    mnLastGroupID;   // +0xb0
    void*       mpObject;        // +0xb4

    ~Play();
    bool Init(unsigned maxVoices, unsigned maxParams, void* a3, void* a4);
    void UpdatePlaying();
    void SetPlaying();
    void SetPaused(bool b);
    void StartVoice(void* a1, void* a2, float t);
    void ParamEvent(Symbol key, ParamPair* atom);
    unsigned GetParam(void* outAtom, Symbol key);
};

struct t_play {                 // PDB size 0xec
    unsigned  object[0x28 / 4]; // +0x00
    Play      play;             // +0x28
    void*     pUpdateCallback;  // +0xe0
    void*     pDoneOutlet;      // +0xe4
    bool      bIsDynamic;       // +0xe8
};

// Group (PDB 0x20): vector<Symbol> {begin,end,alloc} + Symbol location.
struct VectorOfSymbol {
    Symbol*   mpBegin;     // +0x00
    Symbol*   mpEnd;       // +0x04
    void*     mpAlloc;     // +0x08
};
class Group { public:
    VectorOfSymbol mSamples;   // +0x00
    Symbol         mLocation;  // +0x18
    bool Init(void* a2, void* a3, int nAtoms, void* argv);
};

// Construction of one VoiceList by copying a source FixedPool (0xa53970);
// the two embedded allocators get the allocator vftable installed.
struct VoiceListCopy {
    virtual ~VoiceListCopy();       // +0x00
    VoiceListCopy(FixedPool* src);  // ecx = destination pool
};

// Record passed to FixedPool::Init (a stack "allocator" edge).
struct InitAllocator {
    void* vftable;         // +0x00
    void* field4;          // +0x04
    void* name;            // +0x08
};

struct EapdSystem {
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual bool  Load(Symbol* location, void* a, void* b, void* c, int* outCount, void* e);
    virtual void  Destroy(void* a);
};

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void   outlet_bang(void* outlet);
extern "C" void* g_eapdAlloc;

Symbol* atom_gensym(Symbol* out, void* atom);
Symbol* gensym(Symbol* out, const char* s);
void    getSymbol(Symbol* out);                 // 0xa635d0 fills *out
void*   getEapdSystemData();                    // 0xa67d20
void    vectorSymbolResize(VectorOfSymbol* vec, int n);   // 0xa52fa0
int     roundLog2(unsigned n);                  // 0x921340
void    FixedHashtableAllocator_DestroyAllocator(void* a);  // 0xa67d30
int     FUN_00a65e40(void* a, void* b, void* c);
void    FUN_00a3b2c0(void* out, const void* key);
void    FUN_00a65bb0(void* table, void* key, void* a3);
void    atom_string(void* a, char* buf, int n);
float   GetVoiceStartTime(float t);
void    FUN_00a649b0(void* out);
void*   FUN_00a649a0();

void artists_play_setname(t_play* x, unsigned hash, const char* name);
void artists_play_setpausedf(t_play* x, float f);
void artists_play_updateplaying(t_play* x);
int  artists_play_step(void* self);

}}}  // namespace
