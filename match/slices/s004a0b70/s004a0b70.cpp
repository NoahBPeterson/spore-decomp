// Slice s004a0b70: SP editor model-block helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float Dot2(const Vector3T& o) const { return o.x * x + o.y * y + o.z * z; }
    float Dot(const Vector3T& o) const { return x * o.x + y * o.y + z * o.z; }
};
inline float Dot(const Vector3T& u, const Vector3T& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
};
Vector3T operator-(const Vector3T& a, const Vector3T& b);   // @ 0x41db10
float VectorLength(const Vector3T& v);                       // @ 0x40ae50

template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

struct SPAllocTmp { char c; SPAllocTmp() {} };
template<class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    T& operator[](uint32_t n) { return mpBegin[n]; }
    void AllocatorInit(struct SPAllocTmp* tmp);                           // @ 0x429360 (sp_vector_allocator ctor on mAllocator)
    void push_back(const T& v);                              // @ 0x454860
    ~vector();                                               // @ 0x425990
};

// eastl::vector<unsigned int, sp_vector_allocator>: same layout as vector<T>, spelled as a plain
// struct so the equivalence checker can map its members by their '// 0x' annotations.
struct UIntVector {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAllocator[2];
    void AllocatorInit(struct SPAllocTmp* tmp);              // 0x429360
    void push_back(const uint32_t& v);                       // 0x454860
    ~UIntVector();                                           // 0x425990
};

struct cSPEditorBlock;
struct cSPEditorModel {
    bool FUN_4adc40();                                       // 0x4adc40 (returns byte +0x4f)
    cSPEditorBlock* GetBlock(int i);                         // @ 0x4accb0
    int GetBlockCount();                                     // @ 0x4accf0
    float GetScale();                                        // @ 0x4adaa0
    void AddBlock(cSPEditorBlock* b, bool notify);           // @ 0x4abaf0
};

struct cSPEditorHandle {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void _v5();
    virtual void _v6();
    virtual void _v7();
    virtual void _v8();
    virtual void _v9();
    virtual void _v10();
    virtual void _v11();
    virtual void SetActive(bool a, bool b);                  // +0x30
};

struct cSPEditorMessageManager {
    void Post(uint32_t id, int a, cSPEditorBlock* block, int b);   // @ 0x45ae40
};
cSPEditorMessageManager* GetEditorMessageManager();         // @ 0x401050
struct IMessageServer {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void Post(uint32_t id, int a, int b);            // +0x14
};
IMessageServer* MessageServer();                             // @ 0x67dcc0

struct cSPEditorLimbStructure {
    char data[0x58];
    cSPEditorLimbStructure();                                // @ 0x488850
    ~cSPEditorLimbStructure();                               // @ 0x488900
    void Build(cSPEditorBlock* b, int a, int c);             // @ 0x4891a0
    void Apply();                                            // @ 0x48bfa0
    void FixAll();                                           // @ 0x489ae0
    void FixB();                                             // @ 0x48a4c0
    void FixC();                                             // @ 0x488980
};

struct cSPEditorBlock {
    virtual void _v0();
    virtual void AddRef();
    virtual void Release();
    char pad0[0x18 - 4];
    int mModelWorld;                             // +0x18
    char pad1[0x28 - 0x1c];
    cSPEditorModel* mEditorModel;                // +0x28
    char pad2[0x48 - 0x2c];
    Vector3T mPosition;                          // +0x48
    char pad3[0x60 - 0x54];
    Vector3T mAxes[3];                           // +0x60
    char pad4[0x33c - 0x84];
    cSPEditorBlock* mSocketConnector;            // +0x33c
    vector<AutoRefCount<cSPEditorBlock> > mChildren;           // +0x340
    char pad5[0x3e0 - 0x354];
    cSPEditorBlock* mSymmetricBlock;             // +0x3e0
    char pad6[0x3ec - 0x3e4];
    cSPEditorHandle* mHandle;                    // +0x3ec
    cSPEditorBlock* mAttachPoint;                // +0x3f0 (has a position at +0xc)
    char pad7[0xdc8 - 0x3f4];
    bitset<60> mFlags;                           // +0xdc8
    cSPEditorBlock* GetAttach() { return mAttachPoint; }

    cSPEditorBlock();                                        // @ 0x4346b0
    char pad8[0xe08 - 0xdd0];
    void FUN_451360();                                       // @ 0x451360
    void BuildBlock(uint32_t type, int world, int a, int b, float c, int d, int e, int f);   // @ 0x441440
    void SetBooleanAttribute(int attr, bool value);          // @ 0x435a10
    void Split(int n);                                       // @ 0x44f420
    bool IsPaintable();                                      // @ 0x44c030
    void OnRemoved(bool a, bool b);                          // @ 0x44ba20
    void SetUIState(bool a, bool b);                         // @ 0x44bcf0
    void FUN_438a40(cSPEditorBlock* b);                      // @ 0x438a40
    void RecursiveFlag();                                    // @ 0x44ede0
    float GetScaleF();                                       // @ 0x435c00
    int GetSomeId();                                         // @ 0x4511d0
    void Attach(cSPEditorBlock* b);                          // @ 0x438700
    void SetOrientation(Vector3T* p, int a);                 // @ 0x449420
    void SetPosition(Vector3T* p, int a);                    // @ 0x448e90
    float GetAnim();                                         // @ 0x43eed0
    void SetAnim(float f);                                   // @ 0x43eb50
    bool Near(float a, float b);                             // @ 0x43bcf0
    bool CanConnect(cSPEditorBlock* o, int n);               // @ 0x438440
    void GetAxisIndices(int* a, int* b, int* c);             // @ 0x44c0e0
};

void* __cdecl operator new(unsigned sz, const char* name, int a, int b, int c, int d);  // @ 0xf473a0

extern int g_ModelWorld;                                     // @ 0x15d60f4

void __cdecl SetSymmetricBlocksUIState(cSPEditorBlock* b, int a, int c);   // @ 0x4a7f30
void __cdecl DeleteInvalidBlocks(cSPEditorBlock* b, int a);                // @ 0x4a6f10
bool __cdecl FUN_4a7e60(cSPEditorBlock* b);
bool __cdecl FUN_4a7dd0(cSPEditorBlock* b);

// @ 0x4a1020
void FUN_4a1020(cSPEditorModel* model)
{
    int tmp = 0;
    int t14 = model->GetBlockCount();
    for (; tmp < t14; tmp++) {
        model->GetBlock(tmp)->FUN_451360();
    }
}

// @ 0x4a0b70
cSPEditorBlock* FUN_4a0b70(int world, int idx, float scale)
{
    cSPEditorBlock* block = new("Editor", 0, 0, 0, 0) cSPEditorBlock();
    block->BuildBlock(0xa077208c, g_ModelWorld, world, idx, scale, 1, 1, 1);
    block->SetBooleanAttribute(0x14, true);
    return block;
}

// @ 0x4a0bf0
void FUN_4a0bf0(cSPEditorBlock* block)
{
    cSPEditorModel* model = block->mEditorModel;
    if (block && model && block->GetAttach()) {
        cSPEditorBlock* nb;
        int j;
        int m;
        int i;
        int n;
        vector<AutoRefCount<cSPEditorBlock> >* children;
        cSPEditorBlock* self;
        bool unplaceable;
        unplaceable = false;
        children = &block->mChildren;
        i = 0;
        n = (int)(children->mpEnd - children->mpBegin);
        for (; i < n; i++) {
            FUN_4a0bf0((*children)[i]);
        }
        j = 0;
        m = (int)(children->mpEnd - children->mpBegin);
        for (; j < m; j++) {
            if ((*children)[j]->mFlags.test(0x14) && (*children)[j]->mFlags.test(0x2d)) {
                (*children)[j]->OnRemoved(false, false);
                continue;
            }
            if ((*children)[j]->mFlags.test(0xc)) {
                unplaceable = true;
                break;
            }
            cSPVector3 v = (*children)[j]->mPosition - block->mAttachPoint->mPosition;
            if (model->GetScale() * 0.067f < VectorLength(v)) {
                unplaceable = true;
                break;
            }
        }
        self = block;
        if (self) self->AddRef();
        DeleteInvalidBlocks(self, 0);
        if (!unplaceable) {
            int world = block->mModelWorld;
            float scale = block->GetScaleF();
            int id = block->GetSomeId();
            nb = FUN_4a0b70(world, id, scale);
            model->AddBlock(nb, true);
            nb->SetBooleanAttribute(0xc, true);
            if (block->mSymmetricBlock) nb->Split(3);
            block->Attach(nb);
            nb->SetOrientation(&block->mAxes[0], 0);
            nb->SetPosition(&block->mAttachPoint->mPosition, 0);
            nb->SetAnim(nb->GetAnim());
            if (block->IsPaintable()) nb->SetUIState(false, false);
            SetSymmetricBlocksUIState(nb, 0, 0);
        }
        if (self) self->Release();
    }
}

// @ 0x4a1070
void FUN_4a1070(cSPEditorBlock* block)
{
    cSPEditorModel* model = block->mEditorModel;
    cSPEditorHandle* handle = block->mHandle;
    block->SetBooleanAttribute(0xc, false);
    handle->SetActive(true, false);
    if (model->FUN_4adc40()) {
        cSPEditorBlock* sym = block->mSymmetricBlock;
        if (sym && sym->mHandle) {
            sym->mHandle->SetActive(true, false);
        }
    }
    cSPEditorBlock* socket = block->mSocketConnector;
    if (socket) {
        socket->FUN_438a40(block);
        GetEditorMessageManager()->Post(0x3f1bf59, 0, block, 0);
    }
    block->RecursiveFlag();
    bool anyUnsnapped = false;
    cSPEditorBlock* liveBlock = 0;
    cSPEditorHandle* firstHandle = 0;
    UIntVector selected;
    selected.mpBegin = 0; selected.mpEnd = 0; selected.mpCapacity = 0;
    SPAllocTmp allocTmp;
    selected.AllocatorInit(&allocTmp);
    vector<AutoRefCount<cSPEditorBlock> >* children = &socket->mChildren;
    int i = 0;
    int n = (int)(children->mpEnd - children->mpBegin);
    for (; i < n; i++) {
        if ((*children)[i]->mFlags.test(0xc)) {
            (*children)[i]->SetUIState(true, true);
            SetSymmetricBlocksUIState((*children)[i], 0, 0);
            uint32_t b = (uint32_t)(cSPEditorBlock*)(*children)[i];
            selected.push_back(b);
            if ((*children)[i]->mHandle) {
                firstHandle = (*children)[i]->mHandle;
            }
            anyUnsnapped = true;
            if ((*children)[i]->mFlags.test(0x14) && (*children)[i]->mFlags.test(0x2d)) {
                liveBlock = (*children)[i];
            }
        }
    }
    if (firstHandle) {
        firstHandle->SetActive(true, false);
    }
    if (!anyUnsnapped && socket && socket->mFlags.test(5)) {
        int world = block->mModelWorld;
        float scale = block->GetScaleF();
        int id = block->GetSomeId();
        cSPEditorBlock* nb = FUN_4a0b70(world, id, scale);
        if (nb) {
            model->AddBlock(nb, true);
            nb->SetBooleanAttribute(0xc, true);
            if (socket->mSymmetricBlock) nb->Split(3);
            block->Attach(nb);
            nb->SetOrientation(&block->mAxes[0], 0);
            nb->SetPosition(&block->mPosition, 0);
            nb->SetAnim(nb->GetAnim());
            nb->SetBooleanAttribute(0x39, socket->mFlags.test(0x39));
            nb->SetBooleanAttribute(0x3a, socket->mFlags.test(0x3a));
            SetSymmetricBlocksUIState(nb, 0, 0);
        }
    }
    if (socket && socket->mFlags.test(0xb) && FUN_4a7e60(socket) && !FUN_4a7dd0(socket)) {
        cSPEditorLimbStructure limbA;
        cSPEditorLimbStructure limbB;
        limbA.Build(socket, 0, 1);
        limbA.Apply();
        if (socket->mSymmetricBlock) {
            limbB.Build(socket->mSymmetricBlock, 0, 1);
            limbB.Apply();
        }
        limbA.FixAll();
        if (socket->mSymmetricBlock) {
            limbB.FixAll();
            limbB.FixB();
            limbB.FixC();
        }
        limbA.FixB();
        limbA.FixC();
    }
    MessageServer()->Post(0x48e5912, 0, 0);
    (void)liveBlock;
}

// @ 0x4a18b0
bool FUN_4a18b0(cSPEditorBlock* a, cSPEditorBlock* b, float f)
{
    int obj; float v28; int n37; int t24; int u; int v33; int p30;
    if (a->CanConnect(b, 0x2b)) {
        if (!b->IsPaintable()) {
            if (!b->mFlags.test(0x2a)) {
                return false;
            }
        }
        if (a->Near(f, 1.0f) || b->Near(f, 1.0f)) {
            if (a->Near(f / 2.0f, 1.0f) || b->Near(f / 2.0f, 1.0f)) {
                return true;
            } else {
                a->GetAxisIndices(&v33, &n37, &p30);
                b->GetAxisIndices(&obj, &u, &t24);
                v28 = b->mAxes[u].Dot2(a->mAxes[n37]);
                if (v28 > 0.5f) {
                    return true;
                }
            }
        }
    }
    return false;
}
