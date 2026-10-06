// Editor creature-model rebuild helpers, 0x0046aac0 / 0x0046b460 / 0x0046b7b0.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
//
//  0x0046aac0  builds a runtime creature description (SP::cSPEditorBlock bounding boxes -> translation offset,
//              property list + model resources) from the editor's block list, filling the output struct.
//  0x0046b460  replaces every model in a list by a freshly created copy (new resource key + property list).
//  0x0046b7b0  recursive "this block or any ancestor has flag 7, 8 or 0x23 set" test.
#include "types.h"

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

template <int N>
inline void ScratchSlots()
{
    uint32_t s[N];
}

struct Tag {
    Tag() {}
};

struct IObject {
    virtual int AddRef();
    virtual int Release();
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct Matrix3 {
    float m[9];
};

// ---- EA::Variant (data, flags at +0x10, type id at +0x12) --------------------------------------------
struct ResKey {
    uint32_t a, b, c;
};
struct Variant {
    char data[0x10];
    uint16_t mFlags;
    uint16_t mTypeId;
    Variant() : mFlags(0), mTypeId(0) {}
    void SetVec12(const ResKey* k);       // 0x00422f40
    void SetChar(const bool* v);          // 0x00422e20
    void Destruct(int);                   // 0x0093db80 (EA::Variant::Destruct)
    Variant(const ResKey& k) : mFlags(0), mTypeId(0)
    {
        mTypeId = 0x20;
        mFlags = 2;
        SetVec12(&k);
    }
    Variant(const bool& v) : mFlags(0), mTypeId(0)
    {
        mTypeId = 1;
        mFlags = 2;
        SetChar(&v);
    }
    ~Variant()
    {
        if (mFlags & 4)
            Destruct(0);
    }
};

struct IPropertyList : IObject {
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void SetProperty(unsigned id, const Variant& v);   // slot 5
};

// ---- ref-counted model (refcount at +0x40, owner interface pointer at +0) ----------------------------
struct Model;
struct IModelOwner {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual Model* CreateModel(uint32_t a, uint32_t b, int mode);                        // slot 3
#define P4(n) virtual void p##n##a(); virtual void p##n##b(); virtual void p##n##c(); virtual void p##n##d();
    P4(0) P4(1) P4(2) P4(3) P4(4) P4(5) P4(6) P4(7) P4(8) P4(9) P4(10) P4(11) P4(12) P4(13) P4(14)
    virtual void s64();
    virtual int LoadModel(Model* m, IObject** outList, ResKey* key);                     // slot 65
};

struct SPTransform {
    char data[0x38];
    SPTransform& operator=(const SPTransform&);   // 0x00537dc0 (cSPTransform::operator=)
};

struct Model {
    IModelOwner* pOwner;              // +0
    char pad4[4];
    SPTransform transform;            // +8
    int mnRefCount;                   // +0x40 (SPTransform ends at 0x40)
    struct Extra { uint32_t a, b; } extra;   // +0x44, +0x48
    char pad4c[0x90 - 0x4c];
    IObject* pParent;                 // +0x90
    IObject* GetParent() { return pParent; }
    void AddRef() { mnRefCount++; }
    void Release();                   // 0x0040f360 (Counted::Release)
};

template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    AutoRef(T* p) : mp(p) { if (mp) mp->AddRef(); }
    AutoRef(const AutoRef& o) : mp(o.mp) { if (mp) mp->AddRef(); }
    ~AutoRef() { if (mp) mp->Release(); }
    AutoRef& operator=(T* p)
    {
        if (p != mp) {
            T* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    T* get() const { return mp; }
    AutoRef& operator=(const AutoRef& o) { return operator=(o.mp); }
    operator T*() const { return mp; }
};

// Property list (0x38 bytes, "Editor" heap).
struct cPropertyList : IPropertyList {
    char pad[0x38 - 4];
    cPropertyList();                           // 0x006a1c40 (Editor::cPropertyList::cPropertyList)
    void SetParent(IObject* parent);           // 0x006a1710 (SP::cPropertyList::SetParent)
};

struct IPropertyManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual void LoadProperties(uint32_t a, uint32_t c, IObject** outList);   // slot 11 (0x2c)
    virtual void m12();
    virtual void RegisterList(IPropertyList* list, uint32_t a, uint32_t c);   // slot 13 (0x34)
};
IPropertyManager* PropertyManager();           // 0x0067de30 (SP::PropertyManager)

// ---- flag-bit helper shared by the editor blocks ------------------------------------------------------
struct Block {
    char pad0[0x10];
    Model* pModel;                    // +0x10
    char pad14[0x33c - 0x14];
    Block* pParent;                   // +0x33c
    char pad340[0xdc8 - 0x340];
    uint32_t flags[2];                // +0xdc8
    void GetBBox(struct BBox* out, int a, int b, int c);   // 0x0044ae00 (SP::cSPEditorBlock::GetBBox)
    Block* GetParent() const { return pParent; }
    bool IsSet(unsigned bit) const
    {
        uint32_t w;
        bool r;
        if (bit < 0x3c) {
            w = flags[bit >> 5];
            r = (w & (1u << (bit % 32))) != 0;
        } else {
            r = false;
        }
        return r;
    }
};

// @ 0x0046b7b0
bool BlockOrAncestorHasFlag(Block* b)
{
    if (!b)
        return false;
    if (b->IsSet(7) || b->IsSet(8) || b->IsSet(0x23))
        return true;
    else
        return BlockOrAncestorHasFlag(b->GetParent());
}

// ---- 0x0046b460 ---------------------------------------------------------------------------------------
struct IHolder {
    IObject* p;
    IHolder() : p(0) {}
    ~IHolder() { if (p) p->Release(); }
    IHolder& Reset();                 // 0x0041d870
    operator IObject**() { return &p; }
};

struct ModelList {
    char pad0[0xc];
    Model** mpBegin;                  // +0xc
    Model** mpEnd;                    // +0x10
};

struct ModelVec {
    AutoRef<Model>* mpBegin;
    AutoRef<Model>* mpEnd;
    int size() const { return mpEnd - mpBegin; }
    AutoRef<Model>& operator[](int i) { return mpBegin[i]; }
};
struct ModelListObj {
    char pad0[0xc];
    ModelVec models;
};

void BuildKeyHelper(ResKey* key, IObject* holder);   // 0x006acfe0

// @ 0x0046b460
void ReplaceModelsWithCopies(ModelListObj* self)
{
    int count = 1;
    int p24 = 0;
    int cap = self->models.size();
    for (; p24 < cap; p24++) {
        AutoRef<Model> pModel(self->models[p24]);
        if (pModel) {
            ResKey v33;
            IModelOwner* n40 = pModel->pOwner;
            v33.a = 0xffffffff;
            v33.b = 0xffffffff;
            v33.c = 0xffffffff;
            IHolder len;
            if (!n40->LoadModel(self->models[p24].get(), len.Reset(), &v33)) {
                ResKey t38;
                t38.a = count;
                t38.b = 0xe6bce5;
                t38.c = 0x5ef992e;
                count++;
                BuildKeyHelper(&t38, len.p);
                AutoRef<cPropertyList> n21(new ("Editor", 0, 0, 0, 0) cPropertyList());
                n21->SetParent(pModel->GetParent());
                n21->SetProperty(0xf9efbb, Variant(t38));
                PropertyManager()->RegisterList(n21, t38.a, t38.c);
                AutoRef<Model> n12(n40->CreateModel(t38.a, t38.c, 2));
                if (n12) {
                    n12->transform = pModel->transform;
                    n12->extra = pModel->extra;
                    self->models[p24] = n12;
                }
                ScratchSlots<4>();
            }
        }
    }
}

// ---- 0x0046aac0 ---------------------------------------------------------------------------------------
struct BBox {
    float v[6];
    void TransformBy(const struct BBoxTransform* t);   // 0x00409dd0
};
struct BBoxTransform {
    uint16_t flags;
    uint16_t count;
    Vector3 pos;
    float scale;
    Matrix3 rot;
    BBoxTransform();                  // 0x00409930
    void SetScale(float s) { scale = s; count++; }
    void SetRotation(const Matrix3& m) { rot = m; flags |= 2; count++; }
    void SetPosition(const Vector3& p) { pos = p; flags |= 4; count++; }
};

struct BBoxVec {
    char buf[1560];
    BBoxVec(const Tag&);              // 0x00540470
    void Init();                      // 0x0041da70
    void reserve(int n);              // 0x0041e770
    void push_back(const BBox& b);    // 0x0041e8b0
    ~BBoxVec();                       // 0x0041e730
};

struct CreaturePart {
    char pad0[0x2c];
    float scale;                      // +0x2c
    Matrix3 rot;                      // +0x30
    Vector3 pos;                      // +0x54
    char pad60[0x8c - 0x60];
};
struct PartVec {
    CreaturePart* mpBegin;
    CreaturePart* mpEnd;
};
struct Creature : IObject {
    Creature(void* ctx);              // 0x0046a630
    char pad4[4];
    Vector3 pos;                      // +8
    char pad14[0x98 - 0x14];
    PartVec parts;                    // +0x98
    char padA0[0x128 - 0xa0];
};

struct AssetView;
struct EditorCtx {
    char pad0[0x18];
    AssetView* pAssetView;            // +0x18
};
struct EditorBlocks {
    Block** mpBegin;
};

struct ThreadedObject {
    ThreadedObject();                 // 0x0077d1d0
    char pad0[4];
    volatile long mnRefCount;         // +4
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();                   // 0x00404f90 (Resource::ThreadedObject::Release)
};
struct JobRef {
    ThreadedObject* mp;
    JobRef() : mp(0) {}
    ~JobRef();                        // 0x00472520
    JobRef& operator=(ThreadedObject* p)
    {
        if (p != mp) {
            ThreadedObject* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct BuildObject : IObject {
    BuildObject();                    // 0x004610c0
    char pad4[0xac - 4];
    uint32_t mId;                     // +0xac
};
struct BuildRef {
    BuildObject* mp;
    BuildRef() : mp(0) {}
    ~BuildRef();                      // 0x004a9b10
};

struct Editor {
    char pad0[8];
    EditorCtx* ctx;                   // +8
    char padc[0xc0 - 0xc];
    Block** blocks;                   // +0xc0
};

struct JobSlot {
    void Set(ThreadedObject* j);      // 0x0041d8b0
};
struct ModelRefVec {
    void resize(int n);               // 0x00473270 (at +0xc), 0x0041ee90 (at +0x20)
};
struct IModelHost {
    virtual void h0(); virtual void h1(); virtual void h2();
    virtual Model* GetModel(uint32_t a, uint32_t c, int flags);                   // slot 3
};
struct IGameModule {
    char pad[0x60];
};
struct ICreator {
#define Q4(n) virtual void q##n##a(); virtual void q##n##b(); virtual void q##n##c(); virtual void q##n##d();
    Q4(0) Q4(1) Q4(2) Q4(3) Q4(4) Q4(5)
    virtual IModelHost* GetHost();                                                // slot 24 (0x60)
};
ICreator* GetCreator();                                                           // 0x00401010

struct IIdGenerator {
    virtual void i0();
    virtual void Generate(ResKey* key, uint32_t type, int a, int b, int c, int d);   // slot 1
};
IIdGenerator* IDGenerator();                                                      // 0x0067de60

struct IModelNotify {
    virtual void n0();
#define N4(n) virtual void vn##n##a(); virtual void vn##n##b(); virtual void vn##n##c(); virtual void vn##n##d();
    N4(1) N4(2) N4(3) N4(4) N4(5) N4(6) N4(7) N4(8) N4(9) N4(10) N4(11) N4(12) N4(13) N4(14) N4(15)
    N4(16) N4(17) N4(18) N4(19) N4(20) N4(21) N4(22)
    virtual void v89(); virtual void v90();
    virtual void Notify(Model* m, int flag);                                    // slot 91 (0x16c)
};

struct CreatureRef {
    Creature* mp;
    Creature* operator->() const { return mp; }
    operator Creature*() const { return mp; }
};

struct MakeOutput {
    CreatureRef creature;             // +0
    Model* model;                     // +4
    JobSlot job;                      // +8 (empty, member functions only)
    char pad9[3];
    Model** modelsBegin;              // +0xc
    char pad10[0x20 - 0x10];
    char refVec[1];                   // +0x20
    char pad21[0x34 - 0x21];
    bool bIsVerbCollection;           // +0x34
};

void MakeBabyRuntimeCreature(Creature* c);                                         // 0x0046a8a0
void GetTranslationOffset(Vector3* out, BBoxVec* boxes, int unused, Creature* c);  // 0x0046c000
unsigned InitVerbCollection(AssetView* v);                                         // 0x004bb860
void PartPosAdd(Vector3* p, const Vector3* d);                                     // 0x0041ddb0
bool PrepareBuild(Editor* ed, BuildObject* obj);                                   // 0x0046de70
void LoadKeyDefault(uint32_t a, uint32_t c, int z);                                // 0x00469920
void BuildModelResource(uint32_t a, uint32_t c, EditorCtx* ctx, BuildObject* obj, int z0, ThreadedObject* job,
                        Vector3* off, int a1, int a2, int a3, int a4);             // 0x00467a20
void ReserveModels(void* vec, int n);                                              // 0x00473270 (thiscall)
void ResizeRefVec(void* vec, int n);                                               // 0x0041ee90 (thiscall)

// @ 0x0046aac0
void BuildRuntimeCreature(Editor* ed, MakeOutput* out, bool baby, ThreadedObject** pJob)
{
    Creature* pCreature = new ("Editor", 0, 0, 0, 0) Creature(ed->ctx);
    if (pCreature != out->creature.mp) {
        Creature* old = out->creature.mp;
        if (pCreature)
            pCreature->AddRef();
        out->creature.mp = pCreature;
        if (old)
            old->Release();
    }
    Vector3 zero;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    out->creature->pos = zero;
    if (baby)
        MakeBabyRuntimeCreature(out->creature);

    CreaturePart* parts = out->creature->parts.mpBegin;
    int n = (int)((char*)out->creature->parts.mpEnd - (char*)out->creature->parts.mpBegin) / 0x8c;
    Tag tag;
    BBoxVec boxes(tag);
    boxes.Init();
    boxes.reserve(n);
    for (int i = 0; i < n; i++) {
        BBox bb;
        ed->blocks[i]->GetBBox(&bb, 2, 1, 0);
        BBoxTransform xf;
        xf.SetScale(parts[i].scale);
        xf.SetRotation(parts[i].rot);
        xf.SetPosition(parts[i].pos);
        bb.TransformBy(&xf);
        boxes.push_back(bb);
    }
    Vector3 offset(0, 0, 0);
    GetTranslationOffset(&offset, &boxes, 0, out->creature);

    ResKey key;
    key.a = 0;
    key.b = 0;
    key.c = 0;
    IDGenerator()->Generate(&key, 0xb1b104, 0x62, 0, 0x72, 0);

    JobRef job;
    if (pJob) {
        job = new ("Editor", 0, 0, 0, 0) ThreadedObject();
    }
    BuildRef obj;
    obj.mp = new ("Editor", 0, 0, 0, 0) BuildObject();
    if (obj.mp)
        obj.mp->AddRef();
    if (!PrepareBuild(ed, obj.mp)) {
        return;
    }
    obj.mp->mId = 0xd7be35f9;
    IHolder list;
    LoadKeyDefault(key.a, key.c, 0);
    PropertyManager()->LoadProperties(key.a, key.c, list.Reset());
    BuildModelResource(key.a, key.c, ed->ctx, obj.mp, 0, job.mp, &offset, 0, 0, 0, 0);
    {
        IPropertyList* props = (IPropertyList*)list.p;
        bool t = true;
        props->SetProperty(0x3704e55, Variant(t));
    }
    Model* m = GetCreator()->GetHost()->GetModel(key.a, key.c, 0);
    {
        Model** slot = &out->model;
        if (m != *slot) {
            Model* old = *slot;
            if (m)
                m->AddRef();
            *slot = m;
            if (old)
                old->Release();
        }
    }
    ((IModelNotify*)out->model->pOwner)->Notify(out->model, 0);
    out->job.Set(job.mp);

    int j = 0;
    int pn = (int)((char*)out->creature->parts.mpEnd - (char*)out->creature->parts.mpBegin) / 0x8c;
    for (; j < pn; j++)
        PartPosAdd(&out->creature->parts.mpBegin[j].pos, &offset);

    if (pJob) {
        ThreadedObject* t = job.mp;
        job.mp = 0;
        *pJob = t;
    }
    ReserveModels((void*)&out->modelsBegin, n);
    ResizeRefVec(out->refVec, n);
    for (int k = 0; k < n; k++) {
        if (!ed->blocks[k]->IsSet(10)) {
            Model* bm = ed->blocks[k]->pModel;
            Model** slot = &out->modelsBegin[k];
            if (bm != *slot) {
                Model* old = *slot;
                if (bm)
                    bm->AddRef();
                *slot = bm;
                if (old)
                    old->Release();
            }
        }
    }
    bool isVerb = InitVerbCollection(ed->ctx->pAssetView) == 0x3d97a8e4;
    out->bIsVerbCollection = isVerb;
}
