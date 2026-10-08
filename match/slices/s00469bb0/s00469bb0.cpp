// s00469bb0

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
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

// Opaque 0x80-byte member used by S630 (keeps its copy call out-of-line).
struct M18 {
    char pad[0x80];
    M18(const M18&);
};

struct B750 {
    virtual void bv();
    uint32_t key[3];              // +8 resource key (instance, type, group)
    char pad[8];
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
struct CPart {                    // 0x8c-byte creature part (see 0x00469bb0)
    char pad0[0x2c];
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

struct S630 : B750 {
    virtual void v();
    M18 m18;
    M98 m98;
    T50 mAc;
    T31 mC0;
    T50 mD4;
    T50 mE8;
    T50 mFc;
    int f110;
    T31b m114;
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

// ---- not yet reproduced -----------------------------------------------------

// @ 0x0046a510
void F_0046a510() {}

// @ 0x0046a750
void F_0046a750() {}

// @ 0x0046a7c0
void F_0046a7c0() {}

// @ 0x0046a8a0
void F_0046a8a0() {}
