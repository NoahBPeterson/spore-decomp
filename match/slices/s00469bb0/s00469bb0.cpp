// s00469bb0

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned __int64 uint64_t;
template <int N> inline void ScratchSlots()
{
    uint32_t s[N];
    (void)s;
}

struct V3 {
    float x, y, z;
    V3(const V3& o) { x = o.x; y = o.y; z = o.z; }
};

struct Vec3i {
    int x, y, z;
};

struct Tail {
    char b[0x3c];
};

struct M18real {
    int a, b;
    Vec3i i8, i14;
    V3 arr[3];
    Tail tail;
};

// Force emission of the compiler-generated M18real copy ctor (target 0046a7c0).
M18real M18_force_copy(const M18real& o)
{
    M18real t(o);
    return t;
}

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

// Atomic reference count used by the ref-counted bases below.
struct Cnt {
    volatile long n;
    Cnt() { _InterlockedExchange(&n, 0); }
    Cnt(const Cnt&) { _InterlockedExchange(&n, 0); }
};

// Opaque 0x80-byte member used by S630 (keeps its copy call out-of-line).
struct M18 {
    char pad[0x80];
    M18(const M18&);
};

// ---------------------------------------------------------------------------
// B750 base chain (0046a750 is B750's copy ctor):
//   GmeEditorResBase <- cILayer <- RefObj <- B750
// RefObj owns the refcount at +4 and the 3-dword resource key at +8;
// B750 adds one dword at +0x14 (total 0x18, S630's m18 follows at +0x18).
// ---------------------------------------------------------------------------
struct GmeEditorResBase { virtual void g0(); };              // vtable 0x13eb938
struct CILayer : GmeEditorResBase { virtual void l0(); };    // vtable 0x13f1ab0
struct RefObj : CILayer {                                    // vtable 0x13ebcdc
    Cnt ref;              // +4
    uint32_t key[3];      // +8/+0xc/+0x10 resource key (instance, type, group)
};
struct B750 : RefObj {                                       // vtable 0x13ebcc8
    uint32_t m14;         // +0x14
    B750(const B750&);
};

struct T50 {
    char pad[0x14];
    T50(const T50&);
};

struct T31 {
    char pad[0x14];
    T31(const T31&);
};

struct T31b {
    char pad[0x14];
    T31b(const T31b&);
};

struct Mat9 {
    float m[9];
};
struct Vec3f {
    float x, y, z;
};
struct CPart {                    // 0x8c-byte creature bone (see 0x00469bb0)
    char pad0[0xc];
    uint16_t capStart;            // +0xc  first index into the capability-code vector
    char padE[2];
    uint8_t capCount;             // +0x10 number of codes for this bone
    char pad11[0x2c - 0x11];
    float scale;                  // +0x2c
    Mat9 rot;                     // +0x30
    Vec3f pos;                    // +0x54
    char pad60[0x8c - 0x60];
};
struct M98 {
    CPart* mpBegin;               // parts vector (begin/end/capacity + allocator)
    CPart* mpEnd;
    char pad[0xc];
    int size() const { return (int)(mpEnd - mpBegin); }
    M98(const M98&);
};
struct IVec {                     // 0x14-byte vector of ints
    int* mpBegin;
    int* mpEnd;
    char pad[0xc];
    IVec(const IVec&);
};

struct S630 : B750 {
    virtual void v();
    M18 m18;                      // +0x18
    M98 m98;                      // +0x98 bones
    IVec mAc;                     // +0xac capability codes
    T31 mC0;                      // +0xc0
    T50 mD4;                      // +0xd4
    T50 mE8;                      // +0xe8
    T50 mFc;                      // +0xfc
    int f110;                     // +0x110
    T31b m114;                    // +0x114
    S630(const S630&);
};

// @ 0x0046a630
S630::S630(const S630& o)
    : B750(o), m18(o.m18), m98(o.m98), mAc(o.mAc), mC0(o.mC0), mD4(o.mD4), mE8(o.mE8),
      mFc(o.mFc), f110(o.f110), m114(o.m114)
{
    ScratchSlots<4>();
}

// ---- 0x00469bb0: build the runtime creature / model resources for an editor creature -------------------
// Cdecl entry: (Editor* ed, ResKeyArg* key, int p3, uint32 p4, uint32 p5, CJob* p6). Allocates the three
// build objects, converts every creature part into a baby-transform list, and submits up to three model
// builds through 0x00467a20.
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

// intrusive pointer over the vtable AddRef (slot 0) / Release (slot 1) convention
template <class T>
struct IPtr {
    T* mp;
    IPtr() : mp(0) {}
    IPtr(T* p) : mp(p)
    {
        if (mp)
            ((IRefCounted*)mp)->AddRef();
    }
    ~IPtr()
    {
        if (mp)
            ((IRefCounted*)mp)->Release();
    }
    IPtr& operator=(T* p)
    {
        if (p != mp) {
            T* old = mp;
            if (p)
                ((IRefCounted*)p)->AddRef();
            mp = p;
            if (old)
                ((IRefCounted*)old)->Release();
        }
        return *this;
    }
    T* get() const { return mp; }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};

struct EBuildObj : IRefCounted {          // 0x004610c0, 0xb0 bytes
    char pad4[0xac - 4];
    uint32_t mId;                         // +0xac
    EBuildObj();
};
struct EBuildObj2 : IRefCounted {         // 0x0046a510, 0xb0 bytes (built from the first object)
    char pad4[0xac];
    EBuildObj2(EBuildObj* src);
};
bool PrepareBuild(void* ed, EBuildObj* obj);                         // 0x0046de70 (cdecl)
void MakeBabyRuntimeCreature(S630* c);                               // 0x0046a8a0 (cdecl)

struct ThreadedObj {                      // 0x1c bytes, ctor 0x0077d1d0, refcount at +4
    char pad0[4];
    volatile long mnRefCount;
    char pad8[0x1c - 8];
    ThreadedObj();
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();                       // 0x00404f90 (Resource::ThreadedObject::Release)
};
struct ThreadedPtr {
    ThreadedObj* mp;
    ThreadedPtr(ThreadedObj* p) : mp(p)
    {
        if (mp)
            mp->AddRef();
    }
    ~ThreadedPtr()
    {
        if (mp)
            mp->Release();
    }
    ThreadedObj* get() const { return mp; }
};
struct JobSlotB8 {
    void Set(ThreadedObj* j);             // 0x0041d8b0
};

struct AtomicObj {
    void Release();                       // 0x00402420 (AtomicRefCounted::Release)
};
struct AtomicPtr {
    AtomicObj* mp;
    AtomicPtr() : mp(0) {}
    ~AtomicPtr()
    {
        if (mp)
            mp->Release();
    }
    AtomicObj** Reset();                  // 0x00472b00
    AtomicObj** operator&() { return Reset(); }
    AtomicObj* get() const { return mp; }
    operator AtomicObj*() const { return mp; }
};

struct CJob {                             // job object (secondary base, this-8 is the owner)
    void Flush();                         // 0x006909b0
    int Release();                        // 0x00690120
};
struct JobPtr {
    CJob* mp;
    JobPtr() : mp(0) {}
    CJob** Reset();                       // 0x0041d940
    CJob** operator&() { return Reset(); }
    CJob* get() const { return mp; }
};

struct EdCtx {
    char pad0[8];
    S630* mpCreature;                     // +8 source creature
    S630* Creature() { return mpCreature; }
    char padc[0xb8 - 0xc];
    JobSlotB8 jobSlot;                    // +0xb8
};
struct KeyArg {
    uint32_t instance;                    // +0
    uint32_t id;                          // +4
    uint32_t flags;                       // +8
};

// bitfield view of the creature-key flags word
union KeyBits {
    uint32_t raw;
    struct {
        uint32_t lo : 16;
        uint32_t kind : 8;                // 0x62 = baby-capable
        uint32_t cls : 5;
        uint32_t hi : 3;
    } f;
};
inline uint32_t KindOf(uint32_t v)
{
    KeyBits k;
    k.raw = v;
    return k.f.kind;
}
inline uint32_t WithClass(uint32_t v, uint32_t c)
{
    KeyBits k;
    k.raw = v;
    k.f.cls = c;
    return k.raw;
}

struct XformVec {                         // inline-storage vector of 0x38-byte cSPTransform (0xe18 bytes)
    char* mpBegin;
    char buf[0xe18 - 4];
    struct Tag {};
    XformVec(const Tag&);                 // 0x00540470
    void Init();                          // 0x00472b40
    void resize(int n);                   // 0x0041e3b0
    void Free();                          // 0x0041e090
};
struct XformTmp {                         // 0x38-byte transform builder (BBoxTransform)
    uint16_t flags;
    uint16_t count;
    Vec3f pos;
    float scale;
    Mat9 rot;
    XformTmp();                           // 0x00409930
    void Invert();                        // 0x0040efa0
    void ScaleBy(float s);                // 0x00409b30
    void ApplyRot(const Mat9* m);         // 0x006ba870
    void SetScale(float s)
    {
        scale = s;
        count++;
    }
    void SetRotation(const Mat9& m)
    {
        rot = m;
        flags |= 2;
        count++;
    }
    void SetPosition(const Vec3f& p)
    {
        pos = p;
        flags |= 4;
        count++;
    }
    void MarkPos()
    {
        flags |= 4;
        count++;
    }
    void Assign(void* dst);               // 0x00537dc0 (cSPTransform::operator=, on dst)
};
void AddPos(Vec3f* a, const Vec3f* b);    // 0x0041ddb0 (cdecl)

void RegisterModels(uint32_t instance, uint32_t flags, AtomicObj** a, AtomicObj** b, void* c);   // 0x004615e0 (cdecl)
void BuildMaterialInfo(ThreadedObj* job, uint32_t id, AtomicObj* a, AtomicObj* b, float f, char c);   // 0x004604f0 (cdecl)
void BuildModel(uint32_t instance, uint32_t flags, void* a, void* b, int p5, ThreadedObj* job, const void* tag,
                int mode, void* xforms, CJob** outJob, CJob* inJob);                                  // 0x00467a20 (cdecl)
extern const char kBuildTag[];            // 0x015d4034
extern float gMatParam;                   // 0x013eeda0

// @ 0x00469bb0
void BuildEditorCreature(EdCtx* ed, KeyArg* key, int p3, uint32_t p4, uint32_t p5, CJob* p6)
{
    bool isBaby = false;
    if (p4 != 0 && p5 != 0 && KindOf(p5) == 0x62)
        isBaby = true;
    CPart* srcParts = ed->Creature()->m98.mpBegin;
    int nParts = ed->Creature()->m98.size();
    IPtr<EBuildObj> pMain(new ("Editor", 0, 0, 0, 0) EBuildObj());
    if (!PrepareBuild(ed, pMain))
        return;
    pMain.mp->mId = 0xd7be35f9;
    IPtr<EBuildObj2> pAux;
    if (p4 != 0)
        pAux = new ("Editor", 0, 0, 0, 0) EBuildObj2(pMain);
    ThreadedPtr job(new ("Editor", 0, 0, 0, 0) ThreadedObj());
    AtomicPtr ref1;
    AtomicPtr ref2;
    RegisterModels(key->instance, key->flags, &ref2, &ref1, (char*)ed->mpCreature + 0x38);
    BuildMaterialInfo(job.mp, key->id, ref1, ref2, gMatParam, 0);
    ed->jobSlot.Set(job.mp);
    JobPtr job3;
    JobPtr job2;
    JobPtr job1;
    if (isBaby) {
        uint32_t flags = WithClass(p5, 1);
        IPtr<S630> pBaby(new ("Editor", 0, 0, 0, 0) S630(*ed->mpCreature));
        IPtr<EBuildObj2> pBabyAux(new ("Editor", 0, 0, 0, 0) EBuildObj2(pMain));
        uint64_t inst = key->instance;
        pBaby.mp->key[0] = (uint32_t)inst;
        pBaby.mp->key[1] = 0x2b978c46;
        pBaby.mp->key[2] = flags;
        MakeBabyRuntimeCreature(pBaby);
        XformVec::Tag tag;
        XformVec xf(tag);
        xf.Init();
        xf.resize(nParts);
        for (int i = 0; i < nParts; i++) {
            XformTmp t;
            t.SetScale(srcParts[i].scale);
            t.SetRotation(srcParts[i].rot);
            t.SetPosition(srcParts[i].pos);
            t.Invert();
            t.ScaleBy(pBaby->m98.mpBegin[i].scale);
            t.ApplyRot(&pBaby->m98.mpBegin[i].rot);
            AddPos(&t.pos, &pBaby->m98.mpBegin[i].pos);
            t.MarkPos();
            t.Assign(xf.mpBegin + i * 0x38);
        }
        BuildModel(key->instance, flags, pBaby, pBabyAux, p3, job.get(), kBuildTag, 1, xf.mpBegin, &job1, p6);
        p6 = job1.mp;
        xf.Free();
    }
    if (p4 != 0)
        BuildModel(key->instance, p4, ed->mpCreature, pAux, p3, job.get(), kBuildTag, 0, 0, &job2, p6);
    BuildModel(key->instance, p5, ed->mpCreature, pMain, p3, job.get(), kBuildTag, 1, 0, &job3, job2.mp);
    if (job1.mp)
        job1.mp->Flush();
    if (job2.mp)
        job2.mp->Flush();
    if (job3.mp)
        job3.mp->Flush();
    if (job1.mp)
        job1.mp->Release();
    if (job2.mp)
        job2.mp->Release();
    if (job3.mp)
        job3.mp->Release();
}

// ---- remaining functions ----------------------------------------------------

// 0046a510 is the copy constructor of the 0xb0-byte editor-resource object whose
// clear-state ctor/dtor are 0x4610c0/0x4612e0: two polymorphic bases (vptrs at
// +0/+4, refcount at +8) followed by eight 0x14-byte containers and an int.
struct ErBase { virtual void e0(); };
struct AbBase { virtual void a0(); Cnt cnt; };   // vptr at +4, refcount at +8
struct V0c { char pad[0x14]; V0c(const V0c&); };
struct V20 { char pad[0x14]; V20(const V20&); };
struct V34 { char pad[0x14]; V34(const V34&); };
struct V48 { char pad[0x14]; V48(const V48&); };
struct V5c { char pad[0x14]; V5c(const V5c&); };
struct V70 { char pad[0x14]; V70(const V70&); };
struct V84 { char pad[0x14]; V84(const V84&); };
struct V98 { char pad[0x14]; V98(const V98&); };
struct C4610c0 : ErBase, AbBase {
    V0c v0c;                      // +0x0c
    V20 v20;                      // +0x20
    V34 v34;                      // +0x34
    V48 v48;                      // +0x48
    V5c v5c;                      // +0x5c
    V70 v70;                      // +0x70
    V84 v84;                      // +0x84
    V98 v98;                      // +0x98
    int mAC;                      // +0xac
    C4610c0(const C4610c0&);
};

// @ 0x0046a510
C4610c0::C4610c0(const C4610c0& o)
    : ErBase(), AbBase(o), v0c(o.v0c), v20(o.v20), v34(o.v34), v48(o.v48),
      v5c(o.v5c), v70(o.v70), v84(o.v84), v98(o.v98), mAC(o.mAC)
{
}

// B750 copy constructor (the S630 base at +0): the inlined base copy ctors emit
// the base-phase vtables, reset the refcount and copy the resource key.
// @ 0x0046a750
B750::B750(const B750& o)
    : RefObj(o), m14(o.m14)
{
}

// @ 0x0046a7c0
void F_0046a7c0() {}

int GetCapabilityCode(int key);                                        // 0x4615b0
void FUN_00460bf0(CPart* bones, int count, int index, float t);        // 0x460bf0

struct CapEntry {
    int code;
    float value;
};

// @ 0x0046a8a0
void MakeBabyRuntimeCreature(S630* c)
{
    CapEntry entries[6];
    {
        float v = 2.0f;
        int c = GetCapabilityCode(0xb00f0fe9);
        entries[0].code = c;
        entries[0].value = v;
    }
    {
        float v = 1.2f;
        int c = GetCapabilityCode(0xb00f0fe5);
        entries[1].code = c;
        entries[1].value = v;
    }
    {
        float v = 1.4f;
        int c = GetCapabilityCode(0xb00f0fec);
        entries[2].code = c;
        entries[2].value = v;
    }
    {
        float v = 1.6f;
        int c = GetCapabilityCode(0xb00f0fe2);
        entries[3].code = c;
        entries[3].value = v;
    }
    {
        float v = 1.5f;
        int c = GetCapabilityCode(0xb00f0fef);
        entries[4].code = c;
        entries[4].value = v;
    }
    {
        float v = 0.0f;
        int c = 0;
        entries[5].code = c;
        entries[5].value = v;
    }

    CPart* bones = c->m98.mpBegin;
    int nBones = c->m98.size();
    int* caps = c->mAc.mpBegin;

    for (int i = 0; i < nBones; i++) {
        int* first = caps + bones[i].capStart;
        int* last = first + bones[i].capCount;
        for (CapEntry* e = entries; e->code != 0; e++) {
            int* p = first;
            while (p != last && *p != e->code)
                p++;
            if (p != last) {
                FUN_00460bf0(bones, nBones, i, e->value);
                break;
            }
        }
    }
}
