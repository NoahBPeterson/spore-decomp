// Slice s004956b0 (batch w1g0, slice 92), 0x004956b0..0x004962f1.
// /Od editor-region code: mostly hkArray/hkThreadMemory-style helpers plus a
// vector "save transform" routine, plus 004956b0 (SettleBlock, byte-exact).

#include "types.h"

struct Vector3 {
    float x, y, z;
};

// ---- memory manager stubs ---------------------------------------------------
struct MemMgr {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void Deallocate(void* p, int a, int b);
};

extern MemMgr* g_mem;                         // 0x016e4178

struct HkThreadMemory {
    void DeallocateChunk(void* p, int size, int cls);
};

extern void* g_tls_slot;                      // 0x016e4174
extern void* __stdcall TlsGetValue(uint32_t index);

extern void* g_vtbl_13ef554;
extern void* g_vtbl_13ef534;
extern void* g_vtbl_13ef55c;

// @ 0x00495f90
struct D95 {
    void* vptr;
    void* Del(unsigned flags);
};
void* D95::Del(unsigned flags) {
    this->vptr = &g_vtbl_13ef554;
    this->vptr = &g_vtbl_13ef534;
    if (flags & 1) {
        MemMgr* z = g_mem;
        z->Deallocate(this, 8, 0x1c);
    }
    return this;
}

// @ 0x004960d0
struct D960 {
    void* vptr;
    char pad[0xc];
    void* data;                               // 0x10
    char pad2[4];
    int cap;                                  // 0x18
    void Dtor();
    void* Del(unsigned flags);
};

void D960::Dtor() {
    this->vptr = &g_vtbl_13ef55c;
    int c = *(int*)((char*)this + 0x18);
    if ((c & 0x80000000) == 0) {
        void* mem = TlsGetValue(*(uint32_t*)&g_tls_slot);
        ((HkThreadMemory*)mem)->DeallocateChunk(*(void**)((char*)this + 0x10),
                                                 (c & 0x3fffffff) * 0x30, 0x14);
    }
    this->vptr = &g_vtbl_13ef534;
}

// @ 0x00496090
void* D960::Del(unsigned flags) {
    this->Dtor();
    if (flags & 1) {
        MemMgr* z = g_mem;
        z->Deallocate(this, 8, 0x1c);
    }
    return this;
}

// @ 0x00495fe0
struct D95fe0 {
    void* vptr;
    char pad[0x200];
    void* Ctor();
};
void* D95fe0::Ctor() {
    // reconstructed skeleton: vtable stores + inplace-buffer init
    this->vptr = &g_vtbl_13ef55c;
    *(int*)((char*)this + 4) = 0x7f7fffee;
    void** buf = (void**)((char*)this + 0x10);
    buf[0] = (void*)((char*)this + 0x30);
    buf[1] = 0;
    buf[2] = (void*)0x80000008;
    for (int i = 8; i > 0; --i) {
    }
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 4) = 0x7f7fffee;
    return this;
}

// @ 0x00496140
struct D961 {
    char pad[0x4c];
    void** data;                              // 0x4c
    int count;                                // 0x50
    int* Find(int* out, int key);
};
int* D961::Find(int* out, int key) {
    int i = 0;
    while (true) {
        if (this->count <= i) {
            out[0] = 0;
            out[1] = 0;
            return out;
        }
        if (*(int*)((char*)this->data + i * 0x10) == key)
            break;
        ++i;
    }
    out[0] = *(int*)((char*)this->data + i * 0x10 + 8);
    out[1] = *(int*)((char*)this->data + i * 0x10 + 0xc);
    return out;
}

// @ 0x004961d0
struct Vec {
    void** begin;
    void** end;
};
void FUN_004961d0(char* save, Vec* vec) {
    if (save != 0) {
        *(Vector3*)(save + 0x54) = *(Vector3*)(save + 0x48);
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0x84))[k] = ((float*)(save + 0x60))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0xcc))[k] = ((float*)(save + 0xa8))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0x114))[k] = ((float*)(save + 0xf0))[k];
    }
    int n = (int)(vec->end - vec->begin);
    for (int i = 0; i < n; ++i) {
        char* b = (char*)vec->begin[i];
        *(Vector3*)(b + 0x54) = *(Vector3*)(b + 0x48);
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0x84))[k] = ((float*)(b + 0x60))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0xcc))[k] = ((float*)(b + 0xa8))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0x114))[k] = ((float*)(b + 0xf0))[k];
    }
}

// ---- 0x004956b0: SettleBlock (editor block drop / stacking test) ----
// Casts the block 0.2 up and down against the editor Havok world, collects every rigid body it
// would hit, and for each hit block that carries a block pointer in property 0 (and is not already
// visited, not the block's symmetric/linked partner and not in `ignore`) re-filters collision,
// tests for penetration at the lowered position and, if free of penetrations, adds the block to
// `ignore`, rebuilds its pile list and recurses.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /Oy /GS- (Havok locals are 16-byte aligned).
// Layout notes: PenetrationCollector is 0x18 bytes (vtable 0x13ef554, hkBool at +4, the rest
// uninitialised); AllCdPointCollector is 0x1a0 bytes (hkInplaceArray of 8 hkRootCdPoints at +0x10).
// AutoRefCount temps are named locals (blockA/blockB) because the original copies the pointer first.
// find() takes its value by value so the compared pointer is not address-taken.

template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct AllocTag { AllocTag() {} };

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(float a, float b, float c) { x = a; y = b; z = c; }
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(float a, float b, float c) : Vector3T(a, b, c) {}
    __forceinline cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T operator+(const Vector3T& a, const Vector3T& b);           // @ 0x41dc10

typedef float hkReal;
struct hkBool {
    char m_bool;
    hkBool(bool b) { m_bool = (char)b; }
    hkBool& operator=(bool b) { m_bool = (char)b; return *this; }
    operator bool() const { return m_bool != 0; }
};
struct __declspec(align(16)) hkVector4 {
    hkReal x, y, z, w;
    __forceinline hkVector4() {}
    __forceinline hkVector4(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
    __forceinline hkVector4(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
};

struct hkPropertyValue { uint32_t lo, hi; hkPropertyValue() {} hkPropertyValue(int v) : lo((uint32_t)v), hi(0) {} void* getPtr() const { return (void*)lo; } };
struct hkProperty { uint32_t m_key; uint32_t pad; hkPropertyValue m_value; };

struct hkCollidable {
    char pad[0x10];
    int m_ownerOffset;                          // +0x10
    char pad2[0x24 - 0x14];
    void* getOwner() const { return (char*)this + m_ownerOffset; }
};
struct hkRigidBody {
    char pad00[0x1c];
    hkCollidable m_collidable;                  // +0x1c
    char pad40[0x4c - 0x1c - sizeof(hkCollidable)];
    hkProperty* m_properties;                   // +0x4c
    int m_numProperties;                        // +0x50
    char pad54[0x58 - 0x54];
    const hkCollidable* getCollidable() const { return &m_collidable; }
    void setPosition(const hkVector4& p);       // @ 0x1087820
    hkPropertyValue getProperty(uint32_t key) const;   // @ 0x496140
    int getNumProperties() const { return m_numProperties; }
    hkBool hasProperty(uint32_t key) const
    {
        for (int i = 0; i < getNumProperties(); i++) {
            if (m_properties[i].m_key == key)
                return hkBool(true);
        }
        return hkBool(false);
    }
};
inline hkRigidBody* hkGetRigidBody(const hkCollidable* c) { return (hkRigidBody*)c->getOwner(); }

struct hkRootCdPoint {
    char pad[0x28];
    const hkCollidable* m_rootCollidableB;      // +0x28
    unsigned int m_shapeKeyB;
};
struct hkCollisionInput;
extern hkReal HK_REAL_MAX;                      // @ 0x13ef4f8
extern hkReal HK_REAL_EPSILON;                  // @ 0x13ef4f4

struct hkCdPointCollector {
    hkReal m_earlyOutDistance;
    virtual ~hkCdPointCollector() {}            // vtable 0x13ef534
    virtual void addCdPoint(const void* event) = 0;
    virtual void reset();
};
struct AllCdPointCollector : hkCdPointCollector {   // vtable 0x13ef55c
    char pad08[8];
    hkRootCdPoint* m_data;                      // +0x10
    int m_size;                                 // +0x14
    int m_capAndFlags;                          // +0x18
    char pad1c[4];
    char storage[8 * 0x30];
    AllCdPointCollector();                      // @ 0x495fe0
    ~AllCdPointCollector();                     // @ 0x4960d0
    virtual void addCdPoint(const void* event);
};
struct hkLinearCastInput {
    hkVector4 m_to;
    hkReal m_maxExtraPenetration;
    hkReal m_startPointTolerance;
    hkLinearCastInput() { m_maxExtraPenetration = HK_REAL_EPSILON; m_startPointTolerance = HK_REAL_EPSILON; }
};
struct hkCdBodyPairCollector {
    hkBool m_earlyOut;
    hkCdBodyPairCollector() : m_earlyOut(false) {}
    virtual ~hkCdBodyPairCollector() {}         // vtable 0x13ef534 ?
    virtual void addCdBodyPair(const void* a, const void* b) = 0;
};
struct PenetrationCollector : hkCdBodyPairCollector {   // vtable 0x13ef554
    uint32_t m_extra[4];
    PenetrationCollector() : hkCdBodyPairCollector() { m_earlyOut = false; }
    virtual ~PenetrationCollector() {}
    virtual void addCdBodyPair(const void* a, const void* b);
};
struct hkWorld {
    char pad[0x78];
    hkCollisionInput* m_collisionInput;         // +0x78
    void linearCast(const hkCollidable* collA, const hkLinearCastInput& input,
                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);   // @ 0x1082b90
    void getPenetrations(const hkCollidable* collA, const hkCollisionInput& input, hkCdBodyPairCollector& collector);   // @ 0x10867a0
    void updateCollisionFilterOnWorld(int mode, int fullCheck);                // @ 0x10869e0
    void updateCollisionFilterOnEntity(hkRigidBody* e, int mode, int fullCheck);   // @ 0x1084fa0
};

struct cSPEditorPhysicsWorld { hkWorld* World(); };                // @ 0x4b91c0
struct RefCountTemplate {
    virtual ~RefCountTemplate() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release()                                                        // 0x00453540
    {
        int r = mnRefCount-- - 1;
        if (r)
            return r;
        mnRefCount = 1;
        delete this;
        return 0;
    }
};
struct cSPEditorModel {
    int vt;
    RefCountTemplate rc;                 // +4
    cSPEditorPhysicsWorld* GetPhysicsWorld();   // @ 0x4ad450
    void SetCollisionFilter(int info);          // @ 0x4ad470
    void NumberBlocks();                        // @ 0x4ad4e0
    bool IsSymmetryEnabled();                   // @ 0x4adc40
};
struct ModelRef {
    cSPEditorModel* mp;
    ModelRef(cSPEditorModel* p) : mp(p) { if (mp) mp->rc.AddRef(); }
    ~ModelRef() { if (mp) mp->rc.Release(); }
    cSPEditorModel* operator->() const { return mp; }
};

struct cSPEditorBlock;
template<class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};
struct cSPEditorBlock {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    char pad04[0x28 - 4];
    cSPEditorModel* mEditorModel;                // +0x28
    char pad2c[0x34 - 0x2c];
    bool mFlag34;                                // +0x34
    char pad35[0x48 - 0x35];
    cSPVector3 mPosition;                        // +0x48
    char pad54[0x18c - 0x54];
    hkRigidBody* mpRigidBody;                    // +0x18c
    char pad190[0x33c - 0x190];
    cSPEditorBlock* mSymmetricBlock;             // +0x33c
    char pad340[0x3e0 - 0x340];
    cSPEditorBlock* mLinkedBlock;                // +0x3e0

    cSPEditorModel* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock* GetLinkedBlock() { return mLinkedBlock; }
    cSPEditorBlock* GetSymmetricBlock() { return mSymmetricBlock; }
    bool FUN_44c030();                           // @ 0x44c030
    int GetCollisionFilterInfo();                // @ 0x451e90
    void SetCollisionFilterInfo(int info);       // @ 0x451e50
    void SetPosition(const Vector3T& p, bool b); // @ 0x448e90
};
struct BlockVec {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCap;
    uint32_t mAlloc[2];
    BlockVec(const AllocTag&);                              // @ 0x540470
    ~BlockVec();                                            // @ 0x453eb0
    void push_back(const AutoRefCount<cSPEditorBlock>& v);  // @ 0x4541f0
    bool empty() const;                                     // @ 0x526430
    AutoRefCount<cSPEditorBlock>& operator[](uint32_t i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
    AutoRefCount<cSPEditorBlock>* begin() { return mpBegin; }
    AutoRefCount<cSPEditorBlock>* end() { return mpEnd; }
};
void BuildPileList(cSPEditorBlock* block, BlockVec* list, bool b);   // @ 0x48c790

template<class I, class T> inline I find(I first, I last, T value)
{
    while (first != last && !(*first == value))
        ++first;
    return first;
}

__forceinline hkVector4 ToHkVector4(const cSPVector3& v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];
    return hkVector4(x, y, z, 0.0f);
}
// @ 0x004956b0
void SettleBlock(cSPEditorBlock* block, BlockVec* ignore)
{
    ModelRef model(block->GetEditorModel());
    hkWorld* world = model->GetPhysicsWorld()->World();
    model->SetCollisionFilter(0);
    world->updateCollisionFilterOnWorld(0, 1);
    cSPVector3 start = block->mPosition + Vector3T(0.0f, 0.0f, 0.2f);
    AllCdPointCollector collector;
    hkLinearCastInput input;
    input.m_to = ToHkVector4(start);
    hkRigidBody* rb = block->mpRigidBody;
    world->linearCast(rb->getCollidable(), input, collector, 0);
    BlockVec visited((AllocTag()));
    int n = collector.m_size;
    for (int i = 0; i < n; ++i) {
        hkRootCdPoint* hit = &collector.m_data[i];
        const hkCollidable* hc = hit->m_rootCollidableB;
        hkRigidBody* body = hkGetRigidBody(hc);
        if (body->hasProperty(0)) {
            cSPEditorBlock* hitBlock = (cSPEditorBlock*)body->getProperty(0).getPtr();
            if (hitBlock->FUN_44c030()) {
                if (find(visited.begin(), visited.end(), hitBlock) == visited.end()) {
                    bool skip = false;
                    if (model->IsSymmetryEnabled()) {
                        if (block->GetLinkedBlock() == hitBlock) {
                            skip = true;
                        } else if (!ignore->empty()) {
                            for (int j = 0, cnt = ignore->size(); j < cnt; ++j) {
                                if ((*ignore)[j]->GetLinkedBlock() == hitBlock)
                                    skip = true;
                            }
                        }
                    }
                    if (!skip) {
                        cSPEditorBlock* blockA = hitBlock;
                        visited.push_back(blockA);
                        if (hitBlock->GetSymmetricBlock() != block) {
                            if (find(ignore->begin(), ignore->end(), hitBlock) == ignore->end()) {
                                model->NumberBlocks();
                                int prevFilter = block->GetCollisionFilterInfo();
                                int hitFilter = hitBlock->GetCollisionFilterInfo();
                                block->SetCollisionFilterInfo(hitFilter);
                                hkRigidBody* rb2 = block->mpRigidBody;
                                world->updateCollisionFilterOnEntity(rb2, 0, 1);
                                float px = block->mPosition[0];
                                float py = block->mPosition[1];
                                float pz = block->mPosition[2] - 0.2f;
                                hkVector4 lowPos(px, py, pz, 0.0f);
                                hkRigidBody* rb3 = block->mpRigidBody;
                                rb3->setPosition(lowPos);
                                PenetrationCollector pc;
                                hkCollisionInput* ci = world->m_collisionInput;
                                hkRigidBody* rb4 = block->mpRigidBody;
                                world->getPenetrations(rb4->getCollidable(), *ci, pc);
                                block->SetPosition(block->mPosition, true);
                                hkBool hitSomething = pc.m_earlyOut;
                                if (!hitSomething) {
                                    cSPEditorBlock* blockB = hitBlock;
                                    ignore->push_back(blockB);
                                    BuildPileList(hitBlock, ignore, false);
                                    SettleBlock(hitBlock, ignore);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
