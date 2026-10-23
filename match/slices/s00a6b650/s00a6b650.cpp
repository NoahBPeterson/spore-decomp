// Slice s00a6b650 -- the unnamed EA::Swarm effect-database class (primary
// vtable 0x01455950): destructor/constructor, wildcard lookup over the
// string-keyed effect table, and the container helpers for its 0x58-byte
// effect record and 0x14-byte slot vectors.  The class has no name in the
// retail PDB, the ModAPI xml, symbols/names.txt or pdb_vtables.json; slice
// s00a6c190 saw the same layout and called it "Ctx2" -- the descriptor its
// 0x00a6c190 Read method serialises -- so the members below follow that layout.
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---- unnamed runtime helpers / globals (address in the comment) ----
void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);  // 0x00f473a0
void  __cdecl operator_delete__(void*);                                       // 0x00f47380
bool  __cdecl WildcardMatch(const char*, const char*, bool);                  // 0x0093d5d0
extern const char kEastlAllocFile[];    // 0x013ebb38
extern const char kEastlTag[];          // 0x013f2150
extern char       gEmptyString[];       // 0x01667bac
extern char       gEmptyBuckets[];      // 0x0154df28
extern float      gRec30;               // 0x01675928
extern float      gRec34;               // 0x0167592c
extern float      gRec38;               // 0x01675930

// ---- out-of-slice helpers (relocations are masked: arg count/order matters) ----
void* __cdecl MoveSlots20(void* first, void* last, void* dest);   // 0x00a6a5d0
void* __cdecl MoveRecs58(void* first, void* last, void* dest);     // 0x00a6bbf0
void  __cdecl Copy84(void* first, void* last, void* dest);         // 0x00a6afa0
void  __cdecl UninitCopy84(void** out, void* first, void* last, void* dest, void* src); // 0x00a6a9c0
void* __cdecl MoveRange(void* first, void* last, void* dest);      // 0x00a6b370
void  __cdecl FreeRange(void* first, void* last, void* out);       // 0x00a6a610
void* __cdecl FillRecs(void* dest, unsigned count, const void* value);   // 0x00a6b620
void* __cdecl ShiftTailUninit(void* out, void* first, void* last, void* dest, void* src); // 0x00a6b330
void  __cdecl FillRange(void* first, void* last, const void* value);     // 0x00a6bcc0
void  __cdecl DestroyRec58(void* self);                            // 0x00a69f40

typedef unsigned int  uint;
typedef unsigned char uint8;

// ---------------------------------------------------------------------------
struct EString {                       // eastl::basic_string<char>, 0x10
    char* mpBegin; char* mpEnd; char* mpCap; void* mpAlloc;
    void assign(const char* first, const char* last);          // 0x00454cb0
};

struct IRefObj {                       // ref-counted object held by a Rec24
    virtual void v00();
    virtual void Release2();           // vtable slot 1
};

struct HTNode {                        // 0x18
    EString  mKey;                     // +0x00
    unsigned mHash;                    // +0x10
    HTNode*  mpNext;                   // +0x14
};

struct HashTableS {                    // 0x20 -- this = class + 0x48
    unsigned  mx00;
    HTNode**  mpBuckets;               // +0x04
    unsigned  muBucketCount;           // +0x08
    unsigned  muSize;                  // +0x0c
    float     mfMaxLoad;               // +0x10
    float     mfGrowth;                // +0x14
    unsigned  muNextResize;            // +0x18
    unsigned  muPolicyCount;           // +0x1c
    void DoFreeNodes(HTNode** buckets, unsigned bucketCount);       // 0x006a85b0
};

struct HashTableK {                    // 0x20 -- this = class + 0x68
    unsigned  mx00;
    HTNode**  mpBuckets;
    unsigned  muBucketCount;
    unsigned  muSize;
    float     mfMaxLoad;
    float     mfGrowth;
    unsigned  muNextResize;
    unsigned  muPolicyCount;
    void DoFreeNodes(HTNode** buckets, unsigned bucketCount);       // 0x007611f0
};

struct Slot20 {                        // 0x14
    int*     mpBegin; int* mpEnd; int* mpCap;
    unsigned m10, m14;
    void DestroyRange(int* first, int* last);    // 0x00a693f0
};

struct SlotVec {                       // 0x14
    Slot20* mpBegin; Slot20* mpEnd; Slot20* mpCap; void* mAlloc[2];
    SlotVec* init(unsigned n, void* alloc);                              // 0x00a6afe0
    void     insert_n(Slot20* pos, unsigned count, const Slot20* value); // 0x00a6b400
    void     erase(Slot20* first, Slot20* last);                         // 0x00a6b3b0
    void     DestroySlots(Slot20* first, Slot20* last);                  // 0x00a6a0e0
    void     resize(unsigned n);                                         // 0x00a6baf0 (this slice)
};

struct Rec84 {                         // 0x84 record stored inside the effect record
    char mData[0x84];
};

struct Rec84Vec {                      // 0x14 -- the effect record's +0x44 vector
    Rec84* mpBegin; Rec84* mpEnd; Rec84* mpCap; void* mAlloc[2];
    Rec84Vec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    Rec84* AllocCopy84(unsigned n, Rec84* first, Rec84* last);   // 0x00a6b0f0
    Rec84Vec& operator=(const Rec84Vec& o);                      // 0x00a6b9a0 (this slice)
    void DestroyRange(Rec84* first, Rec84* last);                // 0x00a69be0
};

struct FloatVec {                      // 0x14 -- the effect record's +0x1c vector
    float* mpBegin; float* mpEnd; float* mpCap; void* mAlloc[2];
    FloatVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    FloatVec& operator=(const FloatVec& o);                      // 0x0050d4e0
};

// Word views used by the record copy: the retail build copies the leading
// five dwords (+0x00) and the three at +0x30 as raw 32-bit words and only
// sends +0x14 / +0x3c through the FPU.
struct Word5 { unsigned m0, m1, m2, m3, m4; };   // +0x00 m00 m04 m08 m0c m10
struct Word3 { unsigned m0, m1, m2; };           // +0x30 m30 m34 m38

struct BigRec {                        // 0x58 effect record (vector element of +0x34)
    int      m00, m04, m08;            // +0x00
    float    m0c, m10, m14;            // +0x0c
    uint8    m18;                      // +0x18
    char     mPad19[3];
    FloatVec mV1;                      // +0x1c
    float    m30, m34, m38;            // +0x30
    float    m3c;                      // +0x3c
    int      m40;                      // +0x40
    Rec84Vec mV2;                      // +0x44

    BigRec()
      : m00(0), m04(0), m08(0), m0c(0.0f), m10(0.0f), m14(0.0f), m18(0),
        m30(gRec30), m34(gRec34), m38(gRec38), m3c(0.0f), m40(0) {}

    BigRec(const BigRec& o);                                     // 0x00a6b290
    BigRec& operator=(const BigRec& o);                          // 0x00a6bb80 (this slice)
};

struct Rec58Vec {                      // 0x14 -- class member at +0x34
    BigRec* mpBegin; BigRec* mpEnd; BigRec* mpCap; void* mAlloc[2];
    void insert_n(BigRec* pos, unsigned count, const BigRec* value);  // 0x00a6bd40 (this slice)
    void resize(unsigned n);                                          // 0x00a6c030 (this slice)
    void erase(BigRec* first, BigRec* last);                          // 0x00a6bcf0
    void FreeRecs58Std(BigRec* first, BigRec* last);                  // 0x00a6a940
    unsigned Append(const BigRec& value);                             // 0x00a6c150 (this slice)
};

struct Rec24 {                         // 0x24 -- (name, value, object) lookup result
    EString  mS1; EString mS2; IRefObj* mp;
    void InitCopy(const Rec24* o);     // 0x00a69b20
};

struct Rec24Vec {                      // 0x14
    Rec24* mpBegin; Rec24* mpEnd; Rec24* mpCap; void* mAlloc[2];
    void Grow(Rec24* pos, const Rec24* value);        // 0x00a6b150
};

// ---------------------------------------------------------------------------
// The two polymorphic bases carry no destructor.  Retail's ~EffectDb closes by
// re-storing the secondary vtable (0x013ef094) -- what an inlined empty
// ~GmeRefCount would emit -- but ANY user-provided base destructor (empty,
// virtual, throw()) makes MSVC give both the ctor and the dtor an SEH prolog
// plus a /GS cookie (+56/+67 bytes); the real pair has neither frame, so the
// bases must stay destructor-free and the restore is left out (see
// nonmatching.txt).
struct RefCounted {                    // primary base, vtable 0x01455950
    virtual int  AddRef();             // 0x00c6a960
    virtual int  Release();            // 0x007b86e0
};

struct GmeRefCount {                   // secondary base at +0x04, vtable 0x013ef094
    virtual int  AddRef();
    virtual int  Release();
};

// The effect database: two 0x14-byte-slot vectors, a vector of 0x58-byte
// effect records, a string->unsigned name table and a resource-key->int table.
class EffectDb : public RefCounted, public GmeRefCount {
public:
    EffectDb();                                                          // 0x00a6b8a0
    virtual ~EffectDb();                                                 // 0x00a6b650
    virtual void Clear();                                                // 0x00a6bf30
    virtual void FindByWildcard(Rec24Vec* pOut, const char* pattern);    // 0x00a6b760
    virtual unsigned AppendEffect(const BigRec& value);                  // 0x00a6c150
    int       m08;             // +0x08
    SlotVec   mSlots0c;        // +0x0c
    SlotVec   mSlots20;        // +0x20
    Rec58Vec  mRecs;           // +0x34
    HashTableS mHt48;          // +0x48
    HashTableK mHt68;          // +0x68
    void*     mp88;            // +0x88
    int       m8c;             // +0x8c
    int       m90;             // +0x90
};

// ===========================================================================
// @ 0x00a6b650
EffectDb::~EffectDb()
{
    if (mp88 != 0 && ((int*)mp88)[-1] != 0)
        operator_delete__(mp88);

    mHt68.DoFreeNodes(mHt68.mpBuckets, mHt68.muBucketCount);
    mHt68.muSize = 0;
    if (mHt68.muBucketCount > 1)
        operator_delete__(mHt68.mpBuckets);

    mHt48.DoFreeNodes(mHt48.mpBuckets, mHt48.muBucketCount);
    mHt48.muSize = 0;
    if (mHt48.muBucketCount > 1)
        operator_delete__(mHt48.mpBuckets);

    mRecs.FreeRecs58Std(mRecs.mpBegin, mRecs.mpEnd);
    if (mRecs.mpBegin != 0 && ((int*)mRecs.mpBegin)[-1] != 0)
        operator_delete__(mRecs.mpBegin);

    mSlots20.DestroySlots(mSlots20.mpBegin, mSlots20.mpEnd);
    if (mSlots20.mpBegin != 0 && ((int*)mSlots20.mpBegin)[-1] != 0)
        operator_delete__(mSlots20.mpBegin);

    mSlots0c.DestroySlots(mSlots0c.mpBegin, mSlots0c.mpEnd);
    if (mSlots0c.mpBegin != 0 && ((int*)mSlots0c.mpBegin)[-1] != 0)
        operator_delete__(mSlots0c.mpBegin);
}

// @ 0x00a6b760
void EffectDb::FindByWildcard(Rec24Vec* pOut, const char* pattern)
{
    HTNode** bucket = mHt48.mpBuckets;
    HTNode*  node   = *bucket;
    while (node == 0) {
        ++bucket;
        node = *bucket;
    }

    HTNode* end = mHt48.mpBuckets[mHt48.muBucketCount];
    while (node != end) {
        if (pattern == 0 || WildcardMatch(node->mKey.mpBegin, pattern, false)) {
            Rec24 rec;
            rec.mS1.mpBegin = gEmptyString;
            rec.mS1.mpEnd   = gEmptyString;
            rec.mS1.mpCap   = gEmptyString + 1;
            rec.mS2.mpBegin = gEmptyString;
            rec.mS2.mpEnd   = gEmptyString;
            rec.mS2.mpCap   = gEmptyString + 1;
            rec.mp          = 0;
            rec.mS1.assign(node->mKey.mpBegin, node->mKey.mpEnd);

            if (pOut->mpEnd < pOut->mpCap) {
                Rec24* slot = pOut->mpEnd;
                pOut->mpEnd = slot + 1;
                if (slot != 0)
                    slot->InitCopy(&rec);
            } else {
                pOut->Grow(pOut->mpEnd, &rec);
            }

            if (rec.mp != 0)
                rec.mp->Release2();
            if (rec.mS2.mpCap - rec.mS2.mpBegin > 1 && rec.mS2.mpBegin != 0)
                operator_delete__(rec.mS2.mpBegin);
            if (rec.mS1.mpCap - rec.mS1.mpBegin > 1 && rec.mS1.mpBegin != 0)
                operator_delete__(rec.mS1.mpBegin);
        }
        node = node->mpNext;
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
}

// @ 0x00a6b8a0
EffectDb::EffectDb()
{
    char allocStorage;

    m08 = 0;
    mSlots0c.init(0x40, &allocStorage);
    mSlots20.init(0x20, &allocStorage);

    mRecs.mpBegin = 0;
    mRecs.mpEnd   = 0;
    mRecs.mpCap   = 0;

    mHt48.mpBuckets     = (HTNode**)gEmptyBuckets;
    mHt48.muBucketCount = 1;
    mHt48.muSize        = 0;
    mHt48.mfMaxLoad     = 1.0f;
    mHt48.mfGrowth      = 2.0f;
    mHt48.muNextResize  = 0;

    mHt68.mpBuckets     = (HTNode**)gEmptyBuckets;
    mHt68.muBucketCount = 1;
    mHt68.muSize        = 0;
    mHt68.mfMaxLoad     = 1.0f;
    mHt68.mfGrowth      = 2.0f;
    mHt68.muNextResize  = 0;

    mp88 = 0;
    m8c  = 0;
    m90  = 0;
}

// @ 0x00a6b9a0
Rec84Vec& Rec84Vec::operator=(const Rec84Vec& o)
{
    if (this != &o) {
        unsigned n = (unsigned)(o.mpEnd - o.mpBegin);
        if (n > (unsigned)(mpCap - mpBegin)) {
            Rec84* buf = AllocCopy84(n, o.mpBegin, o.mpEnd);
            DestroyRange(mpBegin, mpEnd);
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                operator_delete__(mpBegin);
            mpEnd   = buf + n;
            mpBegin = buf;
            mpCap   = buf + n;
        } else {
            unsigned have = (unsigned)(mpEnd - mpBegin);
            if (have < n) {
                void* tmp;
                Copy84(o.mpBegin, o.mpBegin + have, mpBegin);
                UninitCopy84(&tmp, o.mpBegin + have, o.mpEnd, mpEnd, o.mpEnd);
                mpEnd = mpBegin + n;
            } else {
                Copy84(o.mpBegin, o.mpEnd, mpBegin);
                DestroyRange(mpBegin + n, mpEnd);
                mpEnd = mpBegin + n;
            }
        }
    }
    return *this;
}

// @ 0x00a6baf0
void SlotVec::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        Slot20 value;
        value.mpBegin = 0;
        value.mpEnd   = 0;
        value.mpCap   = 0;
        insert_n(mpEnd, n - (unsigned)(mpEnd - mpBegin), &value);
        value.DestroyRange(0, 0);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00a6bb80
BigRec& BigRec::operator=(const BigRec& o)
{
    *(Word5*)&m00 = *(const Word5*)&o.m00;
    m14 = o.m14;
    m18 = o.m18;
    mV1 = o.mV1;
    *(Word3*)&m30 = *(const Word3*)&o.m30;
    m3c = o.m3c;
    m40 = o.m40;
    mV2 = o.mV2;
    return *this;
}

// @ 0x00a6bc30
void* __cdecl MoveBackward58(BigRec* first, BigRec* last, BigRec* dest)
{
    // the retail build has the record assignment inlined into this loop
    if (last != first) {
        do {
            --last;
            --dest;
            *(Word5*)&dest->m00 = *(const Word5*)&last->m00;
            dest->m14 = last->m14;
            dest->m18 = last->m18;
            dest->mV1 = last->mV1;
            *(Word3*)&dest->m30 = *(const Word3*)&last->m30;
            dest->m3c = last->m3c;
            dest->m40 = last->m40;
            dest->mV2 = last->mV2;
        } while (last != first);
    }
    return dest;
}

// @ 0x00a6bd40
void Rec58Vec::insert_n(BigRec* pos, unsigned count, const BigRec* value)
{
    if (count == 0)
        return;

    if ((unsigned)(mpCap - mpEnd) < count) {
        // no room: reallocate, move the two halves across and flood-fill the hole
        unsigned oldSize = (unsigned)(mpEnd - mpBegin);
        unsigned newCap  = oldSize * 2;
        if (newCap == 0)
            newCap = 1;
        if (newCap < oldSize + count)
            newCap = oldSize + count;

        BigRec* newBuf = (BigRec*)operator_new(newCap * sizeof(BigRec), kEastlTag, 0, 0,
                                               kEastlAllocFile, 0xd1);
        BigRec* mid = (BigRec*)MoveRange(mpBegin, pos, newBuf);
        FreeRange(mpBegin, pos, mid);
        BigRec* tail = (BigRec*)FillRecs(mid, count, value);
        BigRec* end  = (BigRec*)MoveRange(pos, mpEnd, tail);
        FreeRange(pos, mpEnd, end);

        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpBegin = newBuf;
        mpEnd   = end;
        mpCap   = newBuf + newCap;
    } else {
        // room already: shift the tail apart and overwrite the hole with copies
        BigRec tmp(*value);
        unsigned elemsAfter = (unsigned)(mpEnd - pos);
        if (count < elemsAfter) {
            BigRec* split = mpEnd - count;
            BigRec* dst   = mpEnd;
            ShiftTailUninit(split, mpEnd, dst, mpEnd, pos);
            mpEnd += count;
            MoveBackward58(pos, split, mpEnd);
            FillRange(dst, pos, &tmp);
        } else {
            BigRec* dst = mpEnd;
            FillRecs(dst, count - elemsAfter, &tmp);
            mpEnd += count - elemsAfter;
            ShiftTailUninit(pos, mpEnd - count, dst, mpEnd, pos);
            mpEnd += elemsAfter;
            FillRange(dst, pos, &tmp);
        }
        DestroyRec58(&tmp);
    }
}

// @ 0x00a6bf30
void EffectDb::Clear()
{
    mHt48.DoFreeNodes(mHt48.mpBuckets, mHt48.muBucketCount);
    mHt48.muSize = 0;

    mHt68.DoFreeNodes(mHt68.mpBuckets, mHt68.muBucketCount);
    mHt68.muSize = 0;

    {
        BigRec* first = mRecs.mpBegin;
        BigRec* last  = mRecs.mpEnd;
        mRecs.FreeRecs58Std((BigRec*)MoveRecs58(last, last, first), last);
        mRecs.mpEnd -= (last - first);
    }
    {
        Slot20* first = mSlots0c.mpBegin;
        Slot20* last  = mSlots0c.mpEnd;
        mSlots0c.DestroySlots((Slot20*)MoveSlots20(last, last, first), last);
        mSlots0c.mpEnd -= (last - first);
        mSlots0c.resize(0x40);
    }
    {
        Slot20* first = mSlots20.mpBegin;
        Slot20* last  = mSlots20.mpEnd;
        mSlots20.DestroySlots((Slot20*)MoveSlots20(last, last, first), last);
        mSlots20.mpEnd -= (last - first);
        mSlots20.resize(0x20);
    }
}

// @ 0x00a6c030
void Rec58Vec::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        BigRec value;
        insert_n(mpEnd, n - (unsigned)(mpEnd - mpBegin), &value);
        DestroyRec58(&value);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00a6c150
unsigned EffectDb::AppendEffect(const BigRec& value)
{
    Rec58Vec* vec = &mRecs;
    unsigned idx = (unsigned)(vec->mpEnd - vec->mpBegin);
    vec->resize(idx + 1);
    vec->mpBegin[idx] = value;
    return idx;
}

// __END__