// Module 0x00422950..0x004230EB (unoptimized: /Od /Ob1 /MD /Gy /TP /arch:SSE).
// Small helpers: interface-query thunks, callback-registration thunks, a key-ordered tree
// lower_bound lookup, EASTL-style empty-string constructors and variant-style value setters.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// ---------------------------------------------------------------------------
// Interface query helpers
// ---------------------------------------------------------------------------
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

// @ 0x00422950
int QueryByHolder(QueryHolder* holder) {
    int result;
    if (holder)
        result = holder->iface.QueryInterface(0x226A1DE);
    else
        result = 0;
    return result;
}

// Inlined accessor: the original helper has dead locals (matched by search).
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

// @ 0x00422AB0
int QueryByHolderPtr(IQueryable** pp) { return QueryThrough(pp); }

// ---------------------------------------------------------------------------
// Vtable-owning functor objects: { vtable, owner }
// ---------------------------------------------------------------------------
extern void* kVtableA[];  // 0x00428EC0
extern void* kVtableB[];  // 0x00428F00
extern void* kVtableC[];  // 0x00428F40

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

// @ 0x00422990
void FunctorA::Init(uint32_t o) { vtbl = kVtableA; owner = o; }
// @ 0x004229B0
void FunctorB::Init(uint32_t o) { vtbl = kVtableB; owner = o; }
// @ 0x004229D0
void FunctorC::Init(uint32_t o) { vtbl = kVtableC; owner = o; }

// ---------------------------------------------------------------------------
// Callback registration thunks
// ---------------------------------------------------------------------------
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

// @ 0x004229F0
void CallbackRegistry::RegisterA(uint32_t arg) { Register(CallbackA, arg); }
// @ 0x00422A10
void CallbackRegistry::RegisterB(uint32_t arg) { Register(CallbackB, arg); }
// @ 0x00422A30
void CallbackRegistry::RegisterC(uint32_t arg) { Register(CallbackC, arg); }
// @ 0x00422A50
void CallbackRegistry::RegisterD(uint32_t arg) { Register(CallbackD, arg); }
// @ 0x00422A70
void CallbackRegistry::RegisterE(uint32_t arg) { Register(CallbackE, arg); }
// @ 0x00422A90
void CallbackRegistry::RegisterF(uint32_t arg) { Register(CallbackF, arg); }

// ---------------------------------------------------------------------------
// Key-ordered tree lookup (lower_bound / find style)
// ---------------------------------------------------------------------------
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

static inline bool KeyLess(const TreeKey& l, const TreeKey& r) {
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

// @ 0x00422B00
TreeIterator KeyTree::Find(const TreeKey* key) {
    TreeNode* pCurrent = header.root;
    uint32_t best;  // dead local; name/order found by search to reproduce the frame layout
    TreeNode* res = &header;
    while (pCurrent) {
        if (!KeyLess(pCurrent->key, *key)) {
            res = pCurrent;
            pCurrent = pCurrent->child1;
        } else {
            pCurrent = pCurrent->child0;
        }
    }
    if (res != &header && !KeyLess(*key, res->key))
        return TreeIterator(res);
    return TreeIterator(&header);
}

// ---------------------------------------------------------------------------
// Iterator advance
// ---------------------------------------------------------------------------
void* NextNode(void* p);  // 0x00921580

struct NodeCursor {
    void* node;
    NodeCursor* Advance();
};

// @ 0x00422C50
NodeCursor* NodeCursor::Advance() {
    node = NextNode(node);
    return this;
}

// ---------------------------------------------------------------------------
// Empty-string constructors (begin, end, capacity, allocator)
// ---------------------------------------------------------------------------
extern char gEmptyStringStorage;  // 0x01667BAC

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

// @ 0x00422C80
EmptyString2::EmptyString2(const Allocator& alloc) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(alloc) {
    mpBegin = &gEmptyStringStorage;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 2;
}

struct EmptyString1 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    Allocator mAllocator;
    EmptyString1(const Allocator& alloc);
};

// @ 0x00422CF0
EmptyString1::EmptyString1(const Allocator& alloc) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(alloc) {
    mpBegin = &gEmptyStringStorage;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
}

// ---------------------------------------------------------------------------
// Forwarding thunks that pass an uninitialized byte flag
// ---------------------------------------------------------------------------
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

// @ 0x00422D60
void Forwarder::Fwd1(uint32_t a, uint32_t b) {
    unsigned char x, y, z, flag;  // frame layout: flag lands at [ebp-3]
    Do1(a, b, z);
}
// @ 0x00422D90
void Forwarder::Fwd2(uint32_t a, uint32_t b) {
    unsigned char x, y, z, flag;
    Do2(a, b, z);
}
// @ 0x00422DC0
void Forwarder::Fwd3(uint32_t a, uint32_t b) {
    unsigned char x, y, z, flag;
    Do3(a, b, z);
}
// @ 0x00422DF0
void Forwarder::Fwd4(uint32_t a, uint32_t b) {
    unsigned char x, y, z, flag;
    Do4(a, b, z);
}

// ---------------------------------------------------------------------------
// Variant-style typed value setters
// ---------------------------------------------------------------------------
struct Vec12 {
    uint32_t x, y, z;
};

struct Variant {
    uint32_t data[4];
    uint16_t flags;  // bit1: locked to type, bit2: needs reset
    uint16_t type;
    void Reset(int);                                                            // 0x0093DB80
    void SetSlow(int type, int, const void* v, int size, int);                   // 0x0093DD80
    Variant* SetChar(const char* v);
    Variant* SetU32(const uint32_t* v);
    Variant* SetVec12(const Vec12* v);
};

// @ 0x00422E20
Variant* Variant::SetChar(const char* v) {
    if (flags & 4)
        Reset(1);
    if (1 && (!(flags & 2) || type == 1)) {
        *(char*)this = *v;
        type = 1;
        flags = flags & 2;
    } else {
        SetSlow(1, 0, v, 1, 1);
    }
    return this;
}

// @ 0x00422EB0
Variant* Variant::SetU32(const uint32_t* v) {
    if (flags & 4)
        Reset(1);
    if (1 && (!(flags & 2) || type == 9)) {
        *(uint32_t*)this = *v;
        type = 9;
        flags = flags & 2;
    } else {
        SetSlow(9, 0, v, 4, 1);
    }
    return this;
}

// @ 0x00422F40
Variant* Variant::SetVec12(const Vec12* v) {
    if (flags & 4)
        Reset(1);
    if (1 && (!(flags & 2) || type == 0x20)) {
        *(Vec12*)this = *v;
        type = 0x20;
        flags = flags & 2;
    } else {
        SetSlow(0x20, 0, v, 12, 1);
    }
    return this;
}

// ---------------------------------------------------------------------------
// Object copy with intrusive references
// ---------------------------------------------------------------------------
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

// @ 0x00422FD0
CopyTarget* CopyTarget::Assign(const CopyTarget* o) {
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

// ---------------------------------------------------------------------------
// Record copy-constructor
// ---------------------------------------------------------------------------
struct PropertyRecord {
    uint32_t pad[4];
    PropertyRecord(const PropertyRecord& o);  // 0x00401B80
};

struct RecordEntry {
    uint32_t w0, w1, w2, w3;
    PropertyRecord record;
    RecordEntry(const RecordEntry& o);
};

// @ 0x00423080
RecordEntry::RecordEntry(const RecordEntry& o) : w0(o.w0), w1(o.w1), w2(o.w2), w3(o.w3), record(o.record) {
    uint32_t dead;
}

// ---------------------------------------------------------------------------
// Scalar-deleting-destructor style helper
// ---------------------------------------------------------------------------
void DeallocateObject(void* p);  // 0x00F47380 (EASTL allocator deallocate)

struct Deletable {
    void DestroyBody();  // 0x00421CF0
    Deletable* Destroy(uint32_t flags);
};

// @ 0x004230E0
Deletable* Deletable::Destroy(uint32_t flags) {
    uint32_t dead;
    DestroyBody();
    if (flags & 1)
        DeallocateObject(this);
    return this;
}
