// src/game/SPGonzago/_at_00420000.cpp -- migrated from slice(s) s00423110, s00422950, s00421fb0, s004215f0, s00420c70, s004202f0, s0041f940 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00420000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <intrin.h>
#include "EA/Variant.h"
#include <stdarg.h>

// ---- items of slice s0041f940 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct SubIter {
    uint a, b, c, d;
    SubIter() {}
    SubIter(const SubIter& o);
    void Next();                        // 0x004253c0
    bool operator!=(const SubIter& o) const { return a != o.a; }
};
struct Node { ~Node(); };               // 0x00401f20
struct IterOwner {
    uint pad[2];
    SubIter mBegin;                     // +8
    SubIter mEnd;                       // +0x18
    void Finish();                      // 0x00501ef0
    void Destroy();
};
struct Wrapper {
    void Init(int a, int b);            // 0x00425860
    Wrapper(int b);
};
struct Iter {
    uint cur;
    SubIter sub;
    uint x, y;
    Iter(uint c, void* beg, void* end, uint pos);                     // 0x004258b0
    void Normalize();                                                  // 0x004258f0
};
struct ConstIter {                      // converting copy of Iter
    uint cur;
    SubIter sub;
    uint x, y;
    ConstIter(const Iter& i) : cur(i.cur), sub(i.sub), x(i.x), y(i.y) {}
};
struct Bucket {                         // 0x2c bytes
    uint pad[11];
    uint Probe(SubIter* out);                                      // 0x00565740
    uint ProbeEnd(SubIter* out);                                   // 0x00565760
};
struct Ring {
    Bucket mBuckets[8];                 // 0x160 bytes
    Iter IterAt(int idx);               // 0x00420120
    Iter IterAtEnd(int idx);            // 0x00420270
    Iter IterBegin();                   // 0x00420200
    ConstIter IterFirst();              // 0x004201a0
};
// ---- items of slice s0041f940 end

// ---- items of slice s004202f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;    // 0x01485720
extern const float kTwo;    // 0x01470f1c
extern unsigned int g_EmptyBuffer[];   // 0x0154df28
void EASTL_allocator_deallocate(void* p); // 0x00f47380
struct AtomicRefCounted {
    void* vtable;
    int pad;
    long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();   // 0x00402420
};
struct ThreadedObject { void Release(); };  // Resource::ThreadedObject::Release, 0x00404f90
template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr(const intrusive_ptr& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
};
struct Key16 {
    unsigned int w[4];
    Key16(const Key16& o);
};
struct Slot {
    Key16* Lookup(void* pTemp, Key16 key);   // 0x00425600
};
struct SlotIter {
    int p;
    void Advance();                          // 0x004258f0
};
struct RangeIter {
    int mpBucket;
    Key16 mKey;
    int mA;
    int mB;
    RangeIter(const SlotIter& it, const Key16& key, int a, int b) : mpBucket(it.p), mKey(key), mA(a), mB(b) {}
    RangeIter(const void* a, const void* b, const void* c, int n);   // 0x004258b0
};
struct Scratch16 { unsigned int w[4]; int Compute(); };   // 0x00503630
struct HashSet {
    char pad[0x160];
    RangeIter MakeEnd();                     // 0x00420350
    RangeIter MakeIter();                    // 0x004202f0
    RangeIter Build(SlotIter it, Key16 key, int a, int b);  // 0x00420390
};
struct PoolEntry {
    char data[0x2c];
    void Reset();           // 0x004256e0
    int  Size();            // 0x00425450
    void SetA(int v);       // 0x00425530
    void SetB(int v);       // 0x004254c0
    bool IsEmpty();         // 0x00425430
    void Activate();        // 0x004255a0
    int  Process();         // 0x00501e20
};
struct Pool {
    PoolEntry e[8];

    void ResetAll();
    int TotalSize();
    void SetA(int v, int index);
    void SetB(int v, int index);
    bool AllEmpty();
    void ActivateFirstNonEmpty();
    int ProcessFirstNonEmpty();
};
struct RefVector {
    intrusive_ptr<AtomicRefCounted>* mpBegin;
    intrusive_ptr<AtomicRefCounted>* mpEnd;
    intrusive_ptr<AtomicRefCounted>* mpCapacity;
    void Destroy();   // 0x00425990
    void DoPushBack(intrusive_ptr<AtomicRefCounted>* pos, const intrusive_ptr<AtomicRefCounted>* v);  // 0x00425a80
    ~RefVector();
    void push_back(const intrusive_ptr<AtomicRefCounted>& v);
};
struct Triple { int a, b, c; };
struct TripleVector {
    char pad0[4];
    Triple* mpEnd;
    Triple* mpCapacity;
    void DoPushBack(Triple* pos, const Triple* v);  // 0x00425d30
    void push_back(const Triple& v);
};
struct BigElem {
    char data[0x38];
    BigElem(int arg);   // 0x0040ce80
};
struct BigVector {
    char pad0[4];
    BigElem* mpEnd;
    BigElem* mpCapacity;
    void DoPushBack(BigElem* pos, int arg);  // 0x00425f90
    void emplace_back(int arg);
};
inline void UnusedTemp() { unsigned int p[14]; }
void* memcpy(void*, const void*, unsigned int);
void* AllocateAligned(void* allocator, unsigned int size, unsigned int align, unsigned int offset);  // 0x0042dee0
inline void FreeBlock(void* p) { EASTL_allocator_deallocate(p); }
inline void Marker() { const bool b2 = true; }
struct PtrVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    char allocator[4];
    void* mpFixed;
    void reserve(unsigned int n);   // 0x004207e0
    void DoFree(void** p, unsigned int n) { if (p && p != mpFixed) { void* q = p; FreeBlock(q); } }
};
inline void** MovePointers(void** first, void** last, void** dst)
{
    const bool bTrivial = true;
    return (void**)memcpy(dst, first, (char*)last - (char*)first) + (last - first);
}
struct RangeFreeVector {
    char* mpBegin;
    char* mpEnd;
    void DoFreeRange(char* first, char* last);   // 0x004769b0
    void FreeRange();
};
struct ThreadedRefVector {
    ThreadedObject** mpBegin;
    ThreadedObject** mpEnd;
    void Destroy();   // 0x004c0b80
    ~ThreadedRefVector();
    void DestroyNoRelease();
};
struct RangeOpVector {
    char* mpBegin;
    char* mpEnd;
    void DoRange(char* first, char* last);   // 0x00426280
    void Run();
};
struct TrivialVector {
    unsigned int* mpBegin;
    unsigned int* mpEnd;
    void Destroy();   // 0x004c0b80
    ~TrivialVector();
};
struct BufferParams {
    float growth;       // +0x10
    float scale;        // +0x14
    int   offset;       // +0x18
    unsigned int AllocateCapacity(unsigned int n);   // 0x00921360 (thiscall on the params block)
};
inline void InitParams(BufferParams* p) { p->growth = kOne; p->scale = kTwo; p->offset = 0; }
struct Pad24 { unsigned int w[6]; };
struct SmallBuffer {
    unsigned int pad0;
    unsigned int* mpData;     // +4
    unsigned int mnCapacity;  // +8
    unsigned int mnCount;     // +0xc
    BufferParams mParams;     // +0x10
    unsigned int pad1c;       // +0x1c
    SmallBuffer(unsigned int n, Pad24 unused);   // 0x004209f0
    ~SmallBuffer();                              // 0x00420ab0
    SmallBuffer& operator=(const SmallBuffer& o);  // 0x00420b10
    void DestroyRange(unsigned int* p, unsigned int n);   // 0x0042ac80
    void DoFree(unsigned int* p, unsigned int n) { if (n > 1) { void* q = p; FreeBlock(q); } }
    void Swap(SmallBuffer& o);                    // 0x00426430
    SmallBuffer(const SmallBuffer& o);            // 0x00426320
    unsigned int* Allocate(unsigned int n);       // 0x00567260
};
struct HashNode {
    int key;
    int value;
    HashNode* next;
};
struct HashIter {
    HashNode* mpNode;
    HashNode** mpBucket;
    HashIter(HashNode* node, HashNode** bucket) : mpNode(node), mpBucket(bucket) {}
};
struct FieldSetHash { unsigned int operator()(int key) const; };    // 0x00401bf0
struct FieldSetEqualTo { bool operator()(int a, int b) const; };    // 0x00401ca0
struct FieldHashSet {
    char mEmpty0;
    FieldSetEqualTo mEqual;   // +1
    FieldSetHash mHash;       // +2
    HashNode** mpBuckets;     // +4
    unsigned int mnBuckets;   // +8

    unsigned int GetHashCode(int k) const { return mHash(k); }
    int GetKey(const HashNode* n) const { return n->key; }
    bool Compare(int k, int nodeKey) const { return mEqual(k, nodeKey); }
    HashNode* FindNode(HashNode* pNode, const int& k, unsigned int code) const
    {
        for (; pNode; pNode = pNode->next) {
            if (Compare(k, GetKey(pNode)))
                return pNode;
        }
        return 0;
    }
    static HashIter EndIter(HashNode** b) { return HashIter(*b, b); }
    static HashIter CopyIter(const HashIter& r) { return HashIter(r.mpNode, r.mpBucket); }
    HashIter find(const int& key);
};
// ---- items of slice s004202f0 end

// ---- items of slice s00420c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
void __cdecl FreeBlock(void* p);   // EASTL_allocator_deallocate
struct Counted { void Release(); };   // Resource::ThreadedObject::Release (0x00404f90)
void __cdecl MoveBytes(void* first, void* last, void* dest);   // 0x00475bd0
struct ByteVec {
    uint8_t* mBegin;
    uint8_t* mEnd;
    uint8_t* mCap;
    void DoPushBackRealloc(uint8_t* pos, const uint8_t& v);   // 0x00426730
    uint8_t* DoAllocateAndCopy(uint32_t n, const uint8_t* first, const uint8_t* last);  // 0x00426950
    void push_back(const uint8_t& v);
    ByteVec& assign(const ByteVec& x);
    static void DoFree(uint8_t* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    void DestroyFrom(uint8_t* first) { for (; first < mEnd; ++first) { } }
    static uint8_t* DoCopy(const uint8_t* first, const uint8_t* last, uint8_t* dest)
    {
        bool b0, b1, b2;
        b2 = false;
        b0 = false;
        b1 = true;
        return (uint8_t*)memcpy(dest, first, last - first) + (last - first);
    }
};
struct IntNode { int key; int value; };
IntNode* __cdecl LowerBound(IntNode* first, IntNode* last, const int* k, uint8_t flag);   // 0x0042dd00
inline bool IntLess(const int& a, const int& b) { return a < b; }
struct IntMap {
    IntNode* mBegin;
    IntNode* mEnd;
    uint32_t pad[3];
    uint8_t mFlag;
    IntNode* DoInsertValue(IntNode* pos, const IntNode& v);   // 0x00426cc0
    IntNode* lower_bound(const int& k)
    {
        IntNode* last = mEnd;
        IntNode* first = mBegin;
        return LowerBound(first, last, &k, mFlag);
    }
    IntNode* end() { return mEnd; }
    int& operator[](const int& k);
};
struct IPtr {
    Counted* p;
    ~IPtr() { if (p) p->Release(); }
};
struct IdPtr {
    int id;
    IPtr ptr;
};
struct IdPtrVec {
    IdPtr* mBegin;
    IdPtr* mEnd;
    IdPtr* mCap;
    uint32_t mAlloc[2];
    static void DestroyRange(IdPtr* first, IdPtr* last) { for (; first < last; ++first) first->~IdPtr(); }
    static void DoFree(IdPtr* p, uint32_t n) { void* q = p; FreeBlock(q); }
    ~IdPtrVec();
    IdPtrVec& assign(const IdPtrVec& o);   // 0x0042d990
};
struct Elem24 {
    IdPtrVec v;
    uint8_t flag;
    ~Elem24() {}
    __forceinline void SetFlag(uint8_t b) { flag = b; }
    __forceinline Elem24& operator=(const Elem24& o)
    {
        v.assign(o.v);   // 0x0042d990
        SetFlag(o.flag);
        return *this;
    }
};
struct Elem24Vec {
    Elem24* mBegin;
    Elem24* mEnd;
    Elem24* mCap;
    Elem24* DoAllocateAndCopy(uint32_t n, const Elem24* first, const Elem24* last);   // 0x00427100
    static void UninitCopy(const Elem24* first, const Elem24* last, Elem24* dest);    // 0x00427160
    ~Elem24Vec();
    Elem24Vec& assign(const Elem24Vec& x);
    void Free();   // 0x004fd940
    static void DestroyRange(Elem24* first, Elem24* last) { for (; first < last; ++first) first->~Elem24(); }
    static void DoFree(Elem24* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    __forceinline static Elem24* DoCopy(const Elem24* first, const Elem24* last, Elem24* dest)
    {
        bool b0, b1, b2;
        b2 = false;
        b0 = false;
        b1 = false;
        Elem24* d = dest;
        const Elem24* f = first;
        for (; f != last; ++f, ++d)
            *d = *f;
        return d;
    }
};
struct HashNode_s0042_0c70 { uint32_t key; uint32_t value; HashNode_s0042_0c70* next; };
struct RehashResult { uint8_t doRehash; uint32_t newBucketCount; };
struct Iter_s0042_0c70 { HashNode_s0042_0c70* node; HashNode_s0042_0c70** bucket; Iter_s0042_0c70(HashNode_s0042_0c70* n, HashNode_s0042_0c70** b) : node(n), bucket(b) {}  };
struct InsertResult {
    Iter_s0042_0c70 first; uint8_t second;
    InsertResult(Iter_s0042_0c70 i, const bool& b) : first(i), second(b) {}
};
struct FieldHash { uint32_t operator()(uint32_t k) const; };
struct FieldEq { bool operator()(uint32_t a, uint32_t b) const; };
struct TrueTag {};
struct Policy { RehashResult* __thiscall NeedRehash(RehashResult* out, uint32_t bc, uint32_t ec, uint32_t n); };
struct FieldSetHashTable {
    uint8_t pad0;
    FieldEq eq;
    FieldHash hash;
    uint8_t pad1;
    HashNode_s0042_0c70** mBuckets;
    uint32_t mBucketCount;
    uint32_t mElementCount;
    Policy policy;
    HashNode_s0042_0c70* DoAllocateNode(const HashNode_s0042_0c70* v);
    void DoRehash(uint32_t n);
    uint32_t GetHash(uint32_t k) { return hash(k); }
    bool Compare(uint32_t a, uint32_t b) { return eq(a, b); }
    HashNode_s0042_0c70* DoFindNode(HashNode_s0042_0c70* p, const uint32_t& k)
    {
        for (; p; p = p->next) {
            if (Compare(k, p->key)) return p;
        }
        return 0;
    }
    InsertResult DoInsertValue(const HashNode_s0042_0c70* v, const TrueTag&);
};
// ---- items of slice s00420c70 end

// ---- items of slice s004215f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Item24Base {
    uint8_t data[0x14];
    Item24Base(const Item24Base& o) throw();     // 0x0042ad20
};
struct ItemFlag {
    uint8_t v;
    ItemFlag() {}
    ItemFlag(const ItemFlag& o) : v(o.v) {}
};
struct Item24 : Item24Base {
    ItemFlag flag;
    uint8_t pad[3];
    Item24(const Item24& o) throw() : Item24Base(o) { flag = o.flag; }
};
struct Item24Vec {
    Item24* mBegin;
    Item24* mEnd;
    Item24* mCap;
    void DoInsertValue(Item24* pos, const Item24& v);   // 0x00426e30
    void push_back(const Item24& v);
};
struct Quad { uint32_t a, b, c, d; };
struct QuadVec {
    Quad* mBegin;
    Quad* mEnd;
    Quad* mCap;
    Quad* DoAllocateAndCopy(uint32_t n, const Quad* first, const Quad* last);   // 0x00427210
    static void __cdecl UninitCopy(const Quad* first, const Quad* last, Quad* dest);   // 0x00427270

    static void DoFree(Quad* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    static Quad* DoCopy(const Quad* first, const Quad* last, Quad* dest)
    {
        bool b2 = false, b0 = false, bPod = false;
        Quad* out = dest;
        const Quad* pSrc = first;
        for (; pSrc != last; ++out, ++pSrc)
            *out = *pSrc;
        return out;
    }
    void DestroyFrom(Quad* q) { for (; q < mEnd; ++q) { } }
    QuadVec& assign(const QuadVec& x);
};
struct HashNode_s0042_15f0 {
    uint32_t key;
    uint32_t value;
    HashNode_s0042_15f0* next;
};
struct HashIter_s0042_15f0 {
    HashNode_s0042_15f0* node;
    HashNode_s0042_15f0** bucket;
    HashIter_s0042_15f0(HashNode_s0042_15f0* n, HashNode_s0042_15f0** b) : node(n), bucket(b) {}
    HashIter_s0042_15f0(const HashIter_s0042_15f0& o) { HashNode_s0042_15f0** b = o.bucket; HashNode_s0042_15f0* nd = o.node; node = nd; bucket = b; }
};
struct HashInsertResult {
    HashIter_s0042_15f0 it;
    bool inserted;
    HashInsertResult(const HashIter_s0042_15f0& a, const bool& b) : it(a), inserted(b) {}
};
struct RehashResult_s0042_15f0 { bool needed; uint32_t newBuckets; };
struct RehashPolicy {
    uint32_t pad;
    void GetRehashRequired(RehashResult_s0042_15f0* out, uint32_t buckets, uint32_t elems, uint32_t add);   // 0x00921440
};
struct HashTable {
    uint32_t pad0;
    HashNode_s0042_15f0** mBuckets;
    uint32_t mBucketCount;
    uint32_t mElementCount;
    RehashPolicy mPolicy;

    HashNode_s0042_15f0* AllocateNode(const uint32_t* key);         // 0x00567200
    void DoRehash(uint32_t n);                           // 0x00427320

    static uint32_t HashInner(uint32_t v) { return v; }
    static uint32_t HashCode(const uint32_t& v) { return HashInner(v); }
    static bool Equal(uint32_t a, uint32_t b) { return a == b; }
    HashIter_s0042_15f0 end() { HashNode_s0042_15f0** b = mBuckets + mBucketCount; HashNode_s0042_15f0* nd = *b; return HashIter_s0042_15f0(nd, b); }
    HashNode_s0042_15f0* DoFindNode(HashNode_s0042_15f0* n, const uint32_t* key)
    {
        for (; n; n = n->next)
            if (Equal(*key, n->key))
                return n;
        return 0;
    }
    HashIter_s0042_15f0 find(const uint32_t* key);
    HashInsertResult insert(const uint32_t* key, uint32_t unused);
};
struct Counted_s0042_15f0 {
    virtual void AddRef();
    virtual void Release();  // 0x0040f360 (Counted::Release)
};
struct IPtr_s0042_15f0 {
    Counted_s0042_15f0* p;
    IPtr_s0042_15f0() : p(0) {}
    ~IPtr_s0042_15f0() { if (p) p->Release(); }
};
struct IPtrVec {
    IPtr_s0042_15f0* mBegin;
    IPtr_s0042_15f0* mEnd;
    IPtr_s0042_15f0* mCap;
    void InsertFill(IPtr_s0042_15f0* pos, uint32_t n, const IPtr_s0042_15f0& v) throw();   // 0x0042aeb0
    void erase(IPtr_s0042_15f0* first, IPtr_s0042_15f0* last);                             // 0x00533500
    void insertN(IPtr_s0042_15f0* pos, uint32_t c, const IPtr_s0042_15f0& v) { InsertFill(pos, c, v); }
    void resize(uint32_t n);
};
struct Unknown { virtual void v0(); virtual void v1(); virtual void v2(); virtual void* Query(uint32_t iid); };
struct Tmp16 { uint32_t w[4]; };
struct SubObj { void Erase(Tmp16* out, int a); };       // 0x00425380
struct Resetter {
    uint32_t mFirst;
    SubObj mSub;
    uint32_t pad[4];
    uint32_t mLast;
    void Finish();                                       // 0x004258f0
    Resetter* Reset();
};
void __cdecl ThunkTarget();                              // 0x00427600
struct Thunk {
    void (__cdecl *mFn)();
    uint32_t mArg;
    void Init(uint32_t arg);
};
// ---- items of slice s004215f0 end

// ---- items of slice s00421fb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) { x = a; y = b; z = c; }
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
Vector3 operator+(const Vector3& a, const Vector3& b);   // 0x0041dc10
Vector3 operator-(const Vector3& a, const Vector3& b);   // 0x0041db10
Vector3 operator*(const float& s, const Vector3& v);     // 0x0041de40
Vector3 operator*(const Vector3& v, const float& s);     // 0x0041dca0
struct Item24_s0042_1fb0 {  // copy ctor at 0x00511140
    uint32_t d[6];
    Item24_s0042_1fb0(const Item24_s0042_1fb0& o) throw();
};
struct Item12 { float x, y, z; Item12(const Item12& o) throw() : x(o.x), y(o.y), z(o.z) {} };
struct Item20 { uint32_t d[5]; };
struct Item24Vec_s0042_1fb0 {
    Item24_s0042_1fb0* mpBegin; Item24_s0042_1fb0* mpEnd; Item24_s0042_1fb0* mpCapacity;
    void DoPushBackAux(Item24_s0042_1fb0* pos, const Item24_s0042_1fb0& v);        // 0x00427640
    void ReleaseScratch() { int unused0, unused1; }
    void push_back(const Item24_s0042_1fb0& v);  // 0x004215f0 (Item24Vec::push_back)
};
struct Item12Vec {
    Item12* mpBegin; Item12* mpEnd; Item12* mpCapacity;
    void DoPushBackAux(Item12* pos, const Item12& v);        // 0x00427c70
    void push_back(const Item12& v);
};
struct IntVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity;
    void DoPushBackAux(uint32_t* pos, const uint32_t& v);    // 0x004281d0
    void push_back(const uint32_t& v);
};
struct Item20Vec {
    Item20* mpBegin; Item20* mpEnd; Item20* mpCapacity;
    void DoPushBackAux(Item20* pos, const Item20& v);        // 0x00428900
    void push_back(const Item20& v);
};
struct Item48 { uint32_t d[12]; Item48() {} };
struct Dummy12 { uint32_t a, b, c; };
struct Item48Vec {
    Item48* mpBegin; Item48* mpEnd; Item48* mpCapacity;
    void DestroyRange();
    void DoFree();                                           // 0x00428130
    void DoInsert(Item48* pos, uint32_t n, const Item48& v); // 0x0042b600
    void EraseRange(Item48* first, Item48* last);            // 0x00501d70
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void insert(Item48* pos, uint32_t n, const Item48& v) { DoInsert(pos, n, v); }
    void ReleaseScratch() { int u0, u1, u2, u3, u4, u5; }
    void resize(uint32_t n);
};
void Callback_004280f0();
void Callback_00428190();
struct Registry {
    void Register(void (*fn)(), int arg);                    // 0x0068f9f0
    void AddA(int arg);
    void AddB(int arg);
};
void Handler_00428410();
void Handler_00428490();
void Handler_004288c0();
struct HolderA { void (*mpHandler)(); int m; void Init(int v); };
struct HolderB { void (*mpHandler)(); int m; void Init(int v); };
struct HolderC { void (*mpHandler)(); int m; void Init(int v); };
struct KeyRec { uint32_t key, a, b; };
inline bool KeyLess(uint32_t a, uint32_t b) { return a < b; }
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd;
    void DoAssign(wchar_t* dst, const wchar_t* b, const wchar_t* e);   // 0x00428b90
    void DoErase(wchar_t* b, wchar_t* e);                              // 0x0042e2f0
    WString& Replace(uint32_t pos, const wchar_t* s);
    WString& Erase(uint32_t pos, uint32_t n);
};
struct FixedAllocator {
    uint32_t mFlags;
    void* mpPool;
    uint32_t mReserved;
    FixedAllocator(void* const& pool) { mpPool = pool; }
};
inline uint32_t* NullPtr() { int unused0, unused1; return 0; }
struct FixedVecBase {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    FixedAllocator mAllocator;
    FixedVecBase(void* const& pool)
        : mpBegin(NullPtr()), mpEnd(0), mpCapacity(0), mAllocator(pool) {}
    void DoInit(uint32_t n, const uint32_t& value);          // 0x0042bfa0
    void Init(uint32_t n, int value) { DoInit(n, value); }
};
struct FixedVec64 : FixedVecBase {
    uint32_t mBuffer[64];
    FixedVec64(uint32_t n, int value);
};
struct Key3 { uint32_t x, y, z; };
struct Rec {
    Key3 key;            // +0x00
    uint32_t id;         // +0x0c
    uint16_t pad;        // +0x10
    uint16_t tag;        // +0x12
};
struct Head {            // identity block compared against Rec::id / Rec::tag
    uint32_t id;         // +0x00
    uint16_t pad;        // +0x04
    uint16_t tag;        // +0x06
};
inline bool KeyEqual(const Key3& a, const Key3& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
struct RecMatcher {
    const Head* mpHead;
    const Key3* mpKey;
    bool operator()(const Rec* r) const;
};
struct Cursor {
    Rec* cur;
    uint32_t a, b, c;
    Cursor(const Cursor& o);                                  // 0x00420050
    Rec* Deref() const;                                       // 0x005658b0
    bool operator==(const Cursor& o) const { return cur == o.cur; }
};
struct RecIter {
    Rec* node;
    Cursor cursor;
    Rec* mpEnd0;
    Rec* mpEnd1;
    RecIter(const RecIter& o) : node(o.node), cursor(o.cursor), mpEnd0(o.mpEnd0), mpEnd1(o.mpEnd1) {}
    RecIter& operator++();                                    // 0x00421f00
    Rec* operator*() const { return cursor.Deref(); }
};
inline bool IterEqual(const RecIter& a, const RecIter& b)
{
    return a.node == b.node && (a.node == a.mpEnd1 || a.cursor == b.cursor);
}
inline bool IterNotEqual(const RecIter& a, const RecIter& b) { return !IterEqual(a, b); }
inline void Advance(RecIter& it) { int unused; ++it; }
// ---- items of slice s00421fb0 end

// ---- items of slice s00422950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* kVtableA[];  // 0x00428EC0
extern void* kVtableB[];  // 0x00428F00
extern void* kVtableC[];  // 0x00428F40
extern char gEmptyStringStorage;  // 0x01667BAC
struct IQueryable {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual int QueryInterface(uint32_t id);
};
struct QueryHolder {
    uint32_t pad;
    IQueryable iface;
};
static inline int QueryThrough(IQueryable** pp) {
    IQueryable* obj = *pp;
    if (obj) {
        IQueryable* a;
        IQueryable* b = a;
        b = *pp;
        return b->QueryInterface(0xE6BCE5);
    }
    return 0;
}
struct FunctorA {
    void** vtbl;
    uint32_t owner;
    void Init(uint32_t o);
};
struct FunctorB {
    void** vtbl;
    uint32_t owner;
    void Init(uint32_t o);
};
struct FunctorC {
    void** vtbl;
    uint32_t owner;
    void Init(uint32_t o);
};
void CallbackA();  // 0x00428F80
void CallbackB();  // 0x00428FC0
void CallbackC();  // 0x00428F40
void CallbackD();  // 0x00429000
void CallbackE();  // 0x00429040
void CallbackF();  // 0x00429080
struct CallbackRegistry {
    void Register(void (*fn)(), uint32_t arg);  // 0x0068F9F0
    void RegisterA(uint32_t arg);
    void RegisterB(uint32_t arg);
    void RegisterC(uint32_t arg);
    void RegisterD(uint32_t arg);
    void RegisterE(uint32_t arg);
    void RegisterF(uint32_t arg);
};
struct TreeKey {
    uint32_t a, b, c;
};
struct TreeNode {
    TreeNode* child0;  // followed when node.key < key
    TreeNode* child1;
    TreeNode* root;    // only meaningful on the header node
    uint32_t pad;
    TreeKey key;
};
struct TreeIterator {
    TreeNode* node;
    TreeIterator(TreeNode* n);  // 0x00566C50
};
static inline bool KeyLess_s0042_2950(const TreeKey& l, const TreeKey& r) {
    bool res;
    if (l.a != r.a)
        res = l.a < r.a;
    else if (l.c != r.c)
        res = l.c < r.c;
    else
        res = l.b < r.b;
    return res;
}
struct KeyTree {
    uint32_t pad;
    TreeNode header;
    TreeIterator Find(const TreeKey* key);
};
void* NextNode(void* p);  // 0x00921580
struct NodeCursor {
    void* node;
    NodeCursor* Advance();
};
struct Allocator {
    uint32_t pad;
    uint32_t name;
    Allocator(const Allocator& o) { name = o.name; }
};
struct EmptyString2 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    Allocator mAllocator;
    EmptyString2(const Allocator& alloc);
};
struct EmptyString1 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    Allocator mAllocator;
    EmptyString1(const Allocator& alloc);
};
struct Forwarder {
    void Do1(uint32_t a, uint32_t b, unsigned char flag);  // 0x0042C2A0
    void Do2(uint32_t a, uint32_t b, unsigned char flag);  // 0x0042C500
    void Do3(uint32_t a, uint32_t b, unsigned char flag);  // 0x0042C750
    void Do4(uint32_t a, uint32_t b, unsigned char flag);  // 0x0042C950
    void Fwd1(uint32_t a, uint32_t b);
    void Fwd2(uint32_t a, uint32_t b);
    void Fwd3(uint32_t a, uint32_t b);
    void Fwd4(uint32_t a, uint32_t b);
};
struct RefObj {
    virtual void AddRef();
    int refCount;
};
struct SubObject {
    uint32_t pad[14];
    void Assign(const SubObject* o);  // 0x0040CE80
};
struct CopyTarget {
    SubObject first;       // 0x00
    SubObject second;      // 0x38
    uint32_t value;        // 0x70
    RefObj* refA;          // 0x74 (virtual AddRef)
    RefObj* refB;          // 0x78 (count at +4)
    CopyTarget* Assign(const CopyTarget* o);
};
struct PropertyRecord {
    uint32_t pad[4];
    PropertyRecord(const PropertyRecord& o);  // 0x00401B80
};
struct RecordEntry {
    uint32_t w0, w1, w2, w3;
    PropertyRecord record;
    RecordEntry(const RecordEntry& o);
};
void DeallocateObject(void* p);  // 0x00F47380 (EASTL allocator deallocate)
struct Deletable {
    void DestroyBody();  // 0x00421CF0
    Deletable* Destroy(uint32_t flags);
};
// ---- items of slice s00422950 end

// ---- items of slice s00423110 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0042_3110 {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct Matrix3 {
    union { float m[3][3]; Vector3_s0042_3110 rows[3]; };
    Vector3_s0042_3110& operator[](int i) { return rows[i]; }
    Matrix3& Assign(const Matrix3& m);   // @ 0x0041CB40 (other slice)
};
struct MessageBase {
    virtual void Dummy0();
    long mRefCount;     // +4
    int mUnk8[8];       // +8..+0x28
    int mUserData;      // +0x28
};
struct LocaleMessage : MessageBase {
    LocaleMessage(int userData);
    virtual void Dummy1();
};
// ---- items of slice s00423110 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
uint8_t Vector3Equal(const Vector3_s0042_3110* a, const Vector3_s0042_3110* b);   // defined at 0x004232c0, called earlier in the TU

// @ 0x00420050
SubIter::SubIter(const SubIter& o)
{
    a = o.a;
    b = o.b;
    c = o.c;
    d = o.d;
}

// @ 0x00420090
Wrapper::Wrapper(int b)
{ Init(0, b); }

// @ 0x004200b0
void IterOwner::Destroy()
{
    SubIter it(mBegin);
    for (; it != mEnd; it.Next()) {
        Node* n = (Node*)it.a;
        n->~Node();
    }
    Finish();
}

// @ 0x00420120
Iter Ring::IterAt(int idx)
{
    SubIter tmp;
    uint r = mBuckets[idx].Probe(&tmp);
    Iter it((uint)&mBuckets[idx], this, (char*)this + 0x160, r);
    it.Normalize();
    return it;
}

// @ 0x004201a0
ConstIter Ring::IterFirst()
{
    return IterBegin();
}

// @ 0x00420200
Iter Ring::IterBegin()
{
    SubIter tmp;
    uint r = mBuckets[0].Probe(&tmp);
    Iter it((uint)this, this, (char*)this + 0x160, r);
    it.Normalize();
    return it;
}

// @ 0x00420270
Iter Ring::IterAtEnd(int idx)
{
    SubIter tmp;
    uint r = mBuckets[idx].ProbeEnd(&tmp);
    Iter it((uint)&mBuckets[idx], this, (char*)this + 0x160, r);
    it.Normalize();
    return it;
}

// @ 0x004202f0
RangeIter HashSet::MakeIter()
{
    return RangeIter(MakeEnd());
}

// @ 0x00420350
RangeIter HashSet::MakeEnd()
{
    Scratch16 tmp;
    int size = tmp.Compute();
    return RangeIter(pad + 0x160, this, pad + 0x160, size);
}

// @ 0x00420390
RangeIter HashSet::Build(SlotIter it, Key16 key, int a, int b)
{
    if (it.p == b)
        return RangeIter(it, key, a, b);
    unsigned int tmp[5];
    key = *((Slot*)it.p)->Lookup(tmp, key);
    it.Advance();
    return RangeIter(it, key, a, b);
}

// @ 0x00420440
void Pool::ResetAll()
{
    for (int i = 0; i < 8; i++)
        e[i].Reset();
}

// @ 0x00420480
int Pool::TotalSize()
{
    int total = 0;
    for (int i = 0; i < 8; i++)
        total += e[i].Size();
    return total;
}

// @ 0x004204d0
void Pool::SetA(int v, int index)
{
    e[index].SetA(v);
}

// @ 0x004204f0
void Pool::SetB(int v, int index)
{
    e[index].SetB(v);
}

// @ 0x00420510
bool Pool::AllEmpty()
{
    for (int i = 0; i < 8; i++) {
        if (!e[i].IsEmpty())
            return false;
    }
    return true;
}

// @ 0x00420560
void Pool::ActivateFirstNonEmpty()
{
    for (int i = 0; i < 8; i++) {
        if (!e[i].IsEmpty()) {
            e[i].Activate();
            return;
        }
    }
}

// @ 0x004205b0
int Pool::ProcessFirstNonEmpty()
{
    for (int i = 0; i < 8; i++) {
        if (!e[i].IsEmpty())
            return e[i].Process();
    }
    return 0;
}

// @ 0x00420600
RefVector::~RefVector()
{
    typedef intrusive_ptr<AtomicRefCounted> Ref;
    Ref* last = mpEnd;
    Ref* first;
    int unusedTemp[3];   // reproduces the original frame size (inlined helper temporaries)
    for (first = mpBegin; first < last; ++first)
        first->~Ref();
    Destroy();
}

// @ 0x00420660
void RefVector::push_back(const intrusive_ptr<AtomicRefCounted>& v)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) intrusive_ptr<AtomicRefCounted>(v);
    else
        DoPushBack(mpEnd, &v);
}

// @ 0x004206f0
void TripleVector::push_back(const Triple& v)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) Triple(v);
    else
        DoPushBack(mpEnd, &v);
}

// @ 0x00420770
void BigVector::emplace_back(int arg)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) BigElem(arg);
    else
        DoPushBack(mpEnd, arg);
    UnusedTemp();
}

// @ 0x004207e0
void PtrVector::reserve(unsigned int n)
{
    if (n > (unsigned int)(mpCapacity - mpBegin)) {
        void** pNew = n ? (void**)AllocateAligned(allocator, n * 4, 4, 0) : 0;
        void** result = MovePointers(mpBegin, mpEnd, pNew);
        Marker();
        DoFree(mpBegin, mpCapacity - mpBegin);
        unsigned int count = mpEnd - mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + count;
        mpCapacity = mpBegin + n;
    }
}

// @ 0x004208f0
void RangeFreeVector::FreeRange()
{
    int unusedTemp[4];   // reproduces the original frame size
    DoFreeRange(mpBegin, mpEnd);
}

// @ 0x00420920
ThreadedRefVector::~ThreadedRefVector()
{
    typedef intrusive_ptr<ThreadedObject> Ref;
    int unusedTemp[3];   // reproduces the original frame size
    Ref* last = (Ref*)mpEnd;
    Ref* first;
    int unusedTemp2[3];
    for (first = (Ref*)mpBegin; first < last; ++first)
        first->~Ref();
    Destroy();
}

// @ 0x00420980
void RangeOpVector::Run()
{
    int unusedTemp[15];   // reproduces the original frame size
    DoRange(mpBegin, mpEnd);
}

// @ 0x004209b0
TrivialVector::~TrivialVector()
{
    unsigned int* p;
    int unusedTemp[3];   // reproduces the original frame size
    for (p = mpBegin; p < mpEnd; ++p) {
    }
    Destroy();
}

// @ 0x004209f0
SmallBuffer::SmallBuffer(unsigned int n, Pad24 unused)
: mnCapacity(0), mnCount(0)
{
    InitParams(&mParams);
    if (n < 2) {
        mnCapacity = 1;
        mpData = g_EmptyBuffer;
        mnCount = 0;
        mParams.offset = 0;
    } else {
        mnCapacity = mParams.AllocateCapacity(n);
        mpData = Allocate(mnCapacity);
    }
}

// @ 0x00420ab0
SmallBuffer::~SmallBuffer()
{
    DestroyRange(mpData, mnCapacity);
    mnCount = 0;
    DoFree(mpData, mnCapacity);
}

// @ 0x00420b10
SmallBuffer& SmallBuffer::operator=(const SmallBuffer& o)
{
    if (this != &o) {
        SmallBuffer tmp(o);
        int pad[3];   // unused; reproduces the original frame size
        Swap(tmp);
    }
    return *this;
}

// @ 0x00420b50
HashIter FieldHashSet::find(const int& key)
{
    unsigned int hash = GetHashCode(key);
    unsigned int idx = hash % mnBuckets;
    HashNode* pFound = FindNode(mpBuckets[idx], key, hash);
    return CopyIter(pFound ? HashIter(pFound, mpBuckets + idx) : EndIter(mpBuckets + mnBuckets));
}

// @ 0x00420c70
InsertResult FieldSetHashTable::DoInsertValue(const HashNode_s0042_0c70* v, const TrueTag&)
{
    const uint32_t& k = v->key;
    uint32_t c = GetHash(k);
    uint32_t n = c % mBucketCount;
    HashNode_s0042_0c70* pNode = DoFindNode(mBuckets[n], k);
    if (pNode == 0) {
        RehashResult rr;
        policy.NeedRehash(&rr, mBucketCount, mElementCount, 1);
        HashNode_s0042_0c70* pNodeNew = DoAllocateNode(v);
        if (rr.doRehash) {
            n = c % rr.newBucketCount;
            DoRehash(rr.newBucketCount);
        }
        pNodeNew->next = mBuckets[n];
        mBuckets[n] = pNodeNew;
        ++mElementCount;
        return InsertResult(Iter_s0042_0c70(pNodeNew, mBuckets + n), true);
    }
    return InsertResult(Iter_s0042_0c70(pNode, mBuckets + n), false);
}

// @ 0x00420e30
ByteVec& ByteVec::assign(const ByteVec& x)
{
    if (&x != this) {
        uint32_t n = x.mEnd - x.mBegin;
        if (n > (uint32_t)(mCap - mBegin)) {
            uint8_t* pNew = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            ScratchSlots<13>();
            DestroyFrom(mBegin);
            DoFree(mBegin, mCap - mBegin);
            mBegin = pNew;
            mCap = mBegin + n;
        } else if (n > (uint32_t)(mEnd - mBegin)) {
            DoCopy(x.mBegin, x.mBegin + (mEnd - mBegin), mBegin);
            ScratchSlots<17>();
            MoveBytes(x.mBegin + (mEnd - mBegin), x.mEnd, mEnd);
        } else {
            uint8_t* r = DoCopy(x.mBegin, x.mEnd, mBegin);
            DestroyFrom(r);
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// @ 0x00421080
void ByteVec::push_back(const uint8_t& v)
{
    if (mEnd < mCap) {
        ::new(mEnd++) uint8_t(v);
    } else {
        DoPushBackRealloc(mEnd, v);
    }
}

// @ 0x004210f0
int& IntMap::operator[](const int& k)
{
    IntNode* it = lower_bound(k);
    int unused1;
    if (it == end() || IntLess(k, it->key)) {
        int zero = 0;
        IntNode v;
        v.key = k;
        v.value = zero;
        it = DoInsertValue(it, v);
    }
    return it->value;
}

// @ 0x00421190
IdPtrVec::~IdPtrVec()
{
    ScratchSlots<3>();
    DestroyRange(mBegin, mEnd);
    if (mBegin)
        DoFree(mBegin, (mCap - mBegin) * sizeof(IdPtr));
}

// @ 0x00421230
Elem24Vec::~Elem24Vec()
{
    ScratchSlots<9>();
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

// @ 0x00421290
Elem24Vec& Elem24Vec::assign(const Elem24Vec& x)
{
    if (&x != this) {
        uint32_t n = x.mEnd - x.mBegin;
        if (n > (uint32_t)(mCap - mBegin)) {
            Elem24* pNew = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            ScratchSlots<14>();
            DestroyRange(mBegin, mEnd);
            DoFree(mBegin, mCap - mBegin);
            mBegin = pNew;
            mCap = mBegin + n;
        } else if (n > (uint32_t)(mEnd - mBegin)) {
            DoCopy(x.mBegin, x.mBegin + (mEnd - mBegin), mBegin);
            ScratchSlots<12>();
            UninitCopy(x.mBegin + (mEnd - mBegin), x.mEnd, mEnd);
        } else {
            Elem24* pEnd = DoCopy(x.mBegin, x.mEnd, mBegin);
            DestroyRange(pEnd, mEnd);
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// @ 0x004215f0
void Item24Vec::push_back(const Item24& v)
{
    if (mEnd < mCap) {
        ::new(mEnd++) Item24(v);
        ScratchSlots<15>();
    } else {
        DoInsertValue(mEnd, v);
    }
}

// @ 0x00421670
QuadVec& QuadVec::assign(const QuadVec& x)
{
    if (&x != this) {
        uint32_t n = x.mEnd - x.mBegin;
        Quad* pNew;
        Quad* result;
        uint32_t spare[9];
        if (n > (uint32_t)(mCap - mBegin)) {
            pNew = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            for (Quad* it2 = mBegin; it2 < mEnd; ++it2) { }
            DoFree(mBegin, mCap - mBegin);
            mBegin = pNew;
            mCap = mBegin + n;
        } else if (n > (uint32_t)(mEnd - mBegin)) {
            DoCopy(x.mBegin, x.mBegin + (mEnd - mBegin), mBegin);
            UninitCopy(x.mBegin + (mEnd - mBegin), x.mEnd, mEnd);
            ScratchSlots<11>();
        } else {
            result = DoCopy(x.mBegin, x.mEnd, mBegin);
            DestroyFrom(result);
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// @ 0x00421950
HashIter_s0042_15f0 HashTable::find(const uint32_t* key)
{
    uint32_t hash = HashCode(*key);
    uint32_t n = hash % mBucketCount;
    HashNode_s0042_15f0* pNode = DoFindNode(mBuckets[n], key);
    return pNode ? HashIter_s0042_15f0(pNode, mBuckets + n) : end();
}

// @ 0x00421a50
HashInsertResult HashTable::insert(const uint32_t* key, uint32_t unused)
{
    const uint32_t* k = key;
    uint32_t hash = HashCode(*k);
    uint32_t n = hash % mBucketCount;
    HashNode_s0042_15f0* pNode = DoFindNode(mBuckets[n], k);
    if (!pNode) {
        RehashResult_s0042_15f0 r;
        mPolicy.GetRehashRequired(&r, mBucketCount, mElementCount, 1);
        HashNode_s0042_15f0* nn = AllocateNode(key);
        if (r.needed) {
            n = hash % r.newBuckets;
            DoRehash(r.newBuckets);
        }
        nn->next = mBuckets[n];
        mBuckets[n] = nn;
        mElementCount += 1;
        return HashInsertResult(HashIter_s0042_15f0(nn, mBuckets + n), true);
    }
    return HashInsertResult(HashIter_s0042_15f0(pNode, mBuckets + n), false);
}

// @ 0x00421bf0
void IPtrVec::resize(uint32_t n)
{
    if (n > (uint32_t)(mEnd - mBegin)) {
        IPtr_s0042_15f0 hold;
        insertN(mEnd, n - (mEnd - mBegin), hold);
        ScratchSlots<7>();
    } else {
        erase(mBegin + n, mEnd);
    }
}

// @ 0x00421f00
Resetter* Resetter::Reset()
{
    if (mFirst == mLast)
        return this;
    Tmp16 t;
    mSub.Erase(&t, 0);
    Finish();
    return this;
}

// @ 0x00421f40
void Thunk::Init(uint32_t arg)
{
    mFn = ThunkTarget;
    mArg = arg;
}

// @ 0x00421f60
void* __cdecl QueryB(Unknown** ref)
{
    void* result;
    Unknown* p = *ref;
    Unknown* pTmp;
    Unknown* pCast;
    if (p) {
        pCast = pTmp;
        pCast = *ref;
        result = pCast->Query(0x30bdee3);
    } else {
        result = 0;
    }
    return result;
}

// @ 0x00421fb0
void Item24Vec_s0042_1fb0::push_back(const Item24_s0042_1fb0& v)
{
    if (mpEnd < mpCapacity) {
        ::new(mpEnd++) Item24_s0042_1fb0(v);
        ReleaseScratch();
    } else
        DoPushBackAux(mpEnd, v);
}

// @ 0x00422020
Vector3 operator-(const Vector3& v)
{
    Vector3 r(-v.x, -v.y, -v.z);
    return r;
}

// @ 0x004220b0
void Item12Vec::push_back(const Item12& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) Item12(v);
    else
        DoPushBackAux(mpEnd, v);
}

// @ 0x00422140
RecIter FindIf(RecIter first, RecIter last, RecMatcher pred)
{
    while (IterNotEqual(first, last) && !pred(*first))
        Advance(first);
    return first;
}

// @ 0x004221f0
bool RecMatcher::operator()(const Rec* r) const
{
    return r->id == mpHead->id && r->tag == mpHead->tag && KeyEqual(r->key, *mpKey);
}

// @ 0x00422280
void Registry::AddA(int arg)
{ Register(Callback_004280f0, arg); }

// @ 0x004222a0
void Item48Vec::DestroyRange()
{
    for (Item48* p = mpBegin; p < mpEnd; ++p) { Dummy12 d; }
    DoFree();
}

// @ 0x004222e0
void Item48Vec::resize(uint32_t n)
{
    if (n > size()) {
        insert(mpEnd, n - size(), Item48());
        ReleaseScratch();
    } else
        EraseRange(mpBegin + n, mpEnd);
}

// @ 0x00422360
void Registry::AddB(int arg)
{ Register(Callback_00428190, arg); }

// @ 0x00422380
void IntVec::push_back(const uint32_t& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) uint32_t(v);
    else
        DoPushBackAux(mpEnd, v);
}

// @ 0x004223f0
void HolderA::Init(int v)
{ mpHandler = Handler_00428410; m = v; }

// @ 0x00422410
void HolderB::Init(int v)
{ mpHandler = Handler_00428490; m = v; }

// @ 0x00422430
KeyRec* LowerBound(KeyRec* first, KeyRec* last, const KeyRec& value)
{
    int n = (int)(last - first);
    while (n > 0) {
        KeyRec* mid = first;
        int half = n >> 1;
        mid += half;
        int unused;
        if (KeyLess(mid->key, value.key)) {
            ++mid;
            first = mid;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x004224b0
Vector3 CatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t)
{
    return Vector3(0.5f * (2.0f * p1
                   + (-p0 + p2) * t
                   + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t
                   + (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t));
}

// @ 0x00422740
FixedVec64::FixedVec64(uint32_t n, int value)
: FixedVecBase(mBuffer)
{
    mpBegin = mpEnd = mBuffer;
    mpCapacity = mpBegin + 64;
    Init(n, value);
}

// @ 0x004227d0
void HolderC::Init(int v)
{ mpHandler = Handler_004288c0; m = v; }

// @ 0x004227f0
void Item20Vec::push_back(const Item20& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) Item20(v);
    else
        DoPushBackAux(mpEnd, v);
}

// @ 0x00422880
WString& WString::Replace(uint32_t pos, const wchar_t* s)
{
    const wchar_t* e = s;
    while (*e) ++e;
    int len = (int)(e - s);
    DoAssign(mpBegin + pos, s, s + len);
    return *this;
}

// @ 0x004228e0
WString& WString::Erase(uint32_t pos, uint32_t n)
{
    uint32_t rem = (uint32_t)(mpEnd - mpBegin) - pos;
    const uint32_t* m = (rem < n) ? &rem : &n;
    DoErase(mpBegin + pos, mpBegin + pos + *m);
    return *this;
}

// @ 0x00422950
int QueryByHolder(QueryHolder* holder)
{
    int result;
    if (holder)
        result = holder->iface.QueryInterface(0x226A1DE);
    else
        result = 0;
    return result;
}

// @ 0x00422990
void FunctorA::Init(uint32_t o)
{ vtbl = kVtableA; owner = o; }

// @ 0x004229b0
void FunctorB::Init(uint32_t o)
{ vtbl = kVtableB; owner = o; }

// @ 0x004229d0
void FunctorC::Init(uint32_t o)
{ vtbl = kVtableC; owner = o; }

// @ 0x004229f0
void CallbackRegistry::RegisterA(uint32_t arg)
{ Register(CallbackA, arg); }

// @ 0x00422a10
void CallbackRegistry::RegisterB(uint32_t arg)
{ Register(CallbackB, arg); }

// @ 0x00422a30
void CallbackRegistry::RegisterC(uint32_t arg)
{ Register(CallbackC, arg); }

// @ 0x00422a50
void CallbackRegistry::RegisterD(uint32_t arg)
{ Register(CallbackD, arg); }

// @ 0x00422a70
void CallbackRegistry::RegisterE(uint32_t arg)
{ Register(CallbackE, arg); }

// @ 0x00422a90
void CallbackRegistry::RegisterF(uint32_t arg)
{ Register(CallbackF, arg); }

// @ 0x00422ab0
int QueryByHolderPtr(IQueryable** pp)
{ return QueryThrough(pp); }

// @ 0x00422b00
TreeIterator KeyTree::Find(const TreeKey* key)
{
    TreeNode* pCurrent = header.root;
    uint32_t best;  // dead local; name/order found by search to reproduce the frame layout
    TreeNode* res = &header;
    while (pCurrent) {
        if (!KeyLess_s0042_2950(pCurrent->key, *key)) {
            res = pCurrent;
            pCurrent = pCurrent->child1;
        } else {
            pCurrent = pCurrent->child0;
        }
    }
    if (res != &header && !KeyLess_s0042_2950(*key, res->key))
        return TreeIterator(res);
    return TreeIterator(&header);
}

// @ 0x00422c50
NodeCursor* NodeCursor::Advance()
{
    node = NextNode(node);
    return this;
}

// @ 0x00422c80
EmptyString2::EmptyString2(const Allocator& alloc)
: mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(alloc) {
    mpBegin = &gEmptyStringStorage;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 2;
}

// @ 0x00422cf0
EmptyString1::EmptyString1(const Allocator& alloc)
: mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(alloc) {
    mpBegin = &gEmptyStringStorage;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
}

// @ 0x00422d60
void Forwarder::Fwd1(uint32_t a, uint32_t b)
{
    unsigned char x, y, z, flag;  // frame layout: flag lands at [ebp-3]
    Do1(a, b, z);
}

// @ 0x00422d90
void Forwarder::Fwd2(uint32_t a, uint32_t b)
{
    unsigned char x, y, z, flag;
    Do2(a, b, z);
}

// @ 0x00422dc0
void Forwarder::Fwd3(uint32_t a, uint32_t b)
{
    unsigned char x, y, z, flag;
    Do3(a, b, z);
}

// @ 0x00422df0
void Forwarder::Fwd4(uint32_t a, uint32_t b)
{
    unsigned char x, y, z, flag;
    Do4(a, b, z);
}

// @ 0x00422fd0
CopyTarget* CopyTarget::Assign(const CopyTarget* o)
{
    first.Assign(&o->first);
    second.Assign(&o->second);
    value = o->value;
    {
        RefObj** p = &refA;
        *p = o->refA;
        if (*p) {
            (*p)->AddRef();
        }
    }
    {
        RefObj** p = &refB;
        *p = o->refB;
        if (*p) {
            RefObj* obj = *p;
            int dead = obj->refCount + 1;
            obj->refCount = obj->refCount + 1;
        }
    }
    return this;
}

// @ 0x00423080
RecordEntry::RecordEntry(const RecordEntry& o)
: w0(o.w0), w1(o.w1), w2(o.w2), w3(o.w3), record(o.record) {
    uint32_t dead;
}

// @ 0x004230e0
Deletable* Deletable::Destroy(uint32_t flags)
{
    uint32_t dead;
    DestroyBody();
    if (flags & 1)
        DeallocateObject(this);
    return this;
}

// @ 0x00423110
LocaleMessage::LocaleMessage(int userData)
{
    mUserData = userData;
    _InterlockedExchange(&mRefCount, 0);
}

// @ 0x00423160
Vector3_s0042_3110* TransformVector3(Vector3_s0042_3110* out, const Vector3_s0042_3110* v, const float* m)
{
    Vector3_s0042_3110 tmp;
    tmp.x = m[6] * v->z + (m[3] * v->y + m[0] * v->x);
    tmp.y = m[7] * v->z + (m[4] * v->y + m[1] * v->x);
    tmp.z = m[8] * v->z + (m[5] * v->y + m[2] * v->x);
    out->x = tmp.x;
    out->y = tmp.y;
    out->z = tmp.z;
    return out;
}

// @ 0x00423250
uint8_t Matrix3Equal(const Matrix3* a, const Matrix3* b)
{
    int eq;
    if (Vector3Equal((const Vector3_s0042_3110*)a->m[0], (const Vector3_s0042_3110*)b->m[0]) && Vector3Equal((const Vector3_s0042_3110*)a->m[1], (const Vector3_s0042_3110*)b->m[1]) &&
        Vector3Equal((const Vector3_s0042_3110*)a->m[2], (const Vector3_s0042_3110*)b->m[2]))
        eq = true;
    else
        eq = false;
    return eq;
}

// @ 0x004232c0
uint8_t Vector3Equal(const Vector3_s0042_3110* a, const Vector3_s0042_3110* b)
{
    int eq;
    if (a->x == b->x && a->y == b->y && a->z == b->z)
        eq = true;
    else
        eq = false;
    return eq;
}

// @ 0x00423320
Matrix3* Matrix3Multiply(Matrix3* out, const Matrix3* a, const Matrix3* b)
{
    Matrix3 vx;
    for (int i = 0; i < 3; ++i) {
        float fX = a->m[i][2] * b->m[2][0] + (a->m[i][1] * b->m[1][0] + a->m[i][0] * b->m[0][0]);
        Vector3_s0042_3110& rowZ = vx[i];
        rowZ[0] = fX;
        float fY = a->m[i][2] * b->m[2][1] + (a->m[i][1] * b->m[1][1] + a->m[i][0] * b->m[0][1]);
        Vector3_s0042_3110& s1 = vx[i];
        s1[1] = fY;
        float fZ = a->m[i][2] * b->m[2][2] + (a->m[i][1] * b->m[1][2] + a->m[i][0] * b->m[0][2]);
        Vector3_s0042_3110& e1 = vx[i];
        e1[2] = fZ;
    }
    out->Assign(vx);
    return out;
}
