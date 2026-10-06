// Slice s004a3dc0: SP editor pick/block lookup helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Plane { float a, b, c, d; Plane() {} Plane(float x, float y, float z, float w); };

// 64-bit flag set (two dwords); test/set return false/no-op past the valid range.
struct Bits64 {
    uint32_t w[2];
    Bits64() { w[0] = 0; w[1] = 0; if (0) w[1] &= 0; }
    __forceinline void set(uint32_t pos, bool v)
    {
        if (pos < 0x40) {
            if (v) { uint32_t* p = &w[pos >> 5]; *p = (1u << (pos % 32)) | *p; }
            else   { uint32_t* p = &w[pos >> 5]; *p = ~(1u << (pos % 32)) & *p; }
        }
    }
};
struct Bits60 {
    uint32_t w[2];
    __forceinline bool test(uint32_t pos) const
    {
        if (pos < 0x3c) { uint32_t word = w[pos >> 5]; return (word & (1u << (pos % 32))) != 0; }
        return false;
    }
};

// Cross-module helpers (callees are masked relocations)
Vec3* __cdecl Vector3_Normalize(Vec3* out, const Vec3* in);          // @ 0x436ce0
float __cdecl Dot3(const Vec3* a, const Vec3* b);                    // @ 0x455cc0
bool  __cdecl IntersectRayPlane(const Vec3* o, const Vec3* d, const Plane* p, float* t); // @ 0x44e640
Vec3* __cdecl Vector3_Scale(Vec3* out, const float* s, const Vec3* v); // @ 0x41de40
Vec3* __cdecl FUN_0041dc10(Vec3* out, const Vec3* a, const Vec3* b); // @ 0x41dc10 (a + b)
Vec3* __cdecl FUN_0041db10(Vec3* out, const Vec3* a, const Vec3* b); // @ 0x41db10 (a - b)
float __cdecl VectorLength(const Vec3* v);                           // @ 0x40ae50
bool __cdecl GetResourceTypeFromModelType(void* ecxArg);             // @ 0x526430 (ecx-taking)
bool __fastcall FUN_0044c030(void* block);                           // @ 0x44c030

// Reference-counted model (cMWModel): refcount at +0x40.
struct cMWModel {
    char pad0[0xc];
    Vec3 mPos;                      // +0xc
    char pad18[0x40 - 0x18];
    int mRefCount;                  // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
    Vec3* GetPos() { return &mPos; }
};
void __fastcall CountedRelease(void* p);                             // @ 0x40f360
struct RefPtr {
    cMWModel* p;
    RefPtr(cMWModel* q) : p(q) { if (p) p->AddRef(); }
    ~RefPtr() { if (p) CountedRelease(p); }
    cMWModel* get() const { return p; }
};

struct cSPEditorBlock;
struct BlockVec { cSPEditorBlock** mpBegin; cSPEditorBlock** mpEnd; cSPEditorBlock*& operator[](int i) { cSPEditorBlock** p = mpBegin + i; return *p; } };

struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
    float GetScale();                            // @ 0x4adaa0
    bool  FUN_4adc40();                          // @ 0x4adc40
};

struct cSPEditorBlock {
    virtual void _v0();
    char pad04[0x28 - 4];
    cSPEditorModel* mEditorModel;                // +0x28
    char pad2c[0x48 - 0x2c];
    Vec3 mPos48;                                 // +0x48
    char pad54[0x33c - 0x54];
    cSPEditorBlock* mField33c;                   // +0x33c
    BlockVec mChildren;                          // +0x340
    char pad348[0x3e0 - 0x348];
    cSPEditorBlock* mParent;                     // +0x3e0
    char pad3e4[0x3f0 - 0x3e4];
    cMWModel* mModel;                            // +0x3f0
    cMWModel* GetModel() { return mModel; }
    char pad3f4[0xdc8 - 0x3f4];
    Bits60 mFlags;                               // +0xdc8
    cSPEditorBlock* GetField33c() { return mField33c; }
    void SetNodeStateChecked(int state, bool b); // @ 0x437a60
    void ClearNodeState();                       // @ 0x437890
};

// @ 0x4a4cf0
cSPEditorBlock* FUN_4a4cf0(cSPEditorModel* model, int id)
{
    if (model && (unsigned)model->GetBlockCount() > 0) {
        int tmp = 0;
        int t14 = model->GetBlockCount();
        cSPEditorBlock* block;
        for (; tmp < t14; tmp++) {
            block = model->GetBlock(tmp);
            int field = *(int*)((char*)block + 0x18c);
            if (field == id) return block;
        }
    }
    return 0;
}

struct cSPEditorPickInfo {
    Bits64 m0;
    Bits64 m8;
    int m10;
    bool m14;
    bool m15;
    cSPEditorPickInfo();                         // @ 0x4a4c70
};

// @ 0x4a4c70
cSPEditorPickInfo::cSPEditorPickInfo()
{
    m10 = 0;
    m14 = 0;
    m15 = 0;
}

// @ 0x4a3dc0
cSPEditorBlock* FUN_4a3dc0(cSPEditorBlock* block, BlockVec* exclude, Vec3 origin, Vec3 dir, Vec3* outPos)
{
    cSPEditorModel* model = block->mEditorModel;
    bool unusedFlag = false;
    if (block->mFlags.test(0x1f)) {
        if (block->mFlags.test(0xc)) {
            *outPos = block->mPos48;
            Vec3 nrm;
            Vec3* n = Vector3_Normalize(&nrm, &dir);
            Plane plane;
            Plane ptmp(n->operator[](0), n->operator[](1), n->operator[](2), -Dot3(&block->mPos48, n));
            plane = ptmp;
            float t;
            if (!IntersectRayPlane(&origin, &dir, &plane, &t))
                return block->GetField33c();
            Vec3 s1, s2, s3;
            Vec3 hit = *FUN_0041dc10(&s2, &origin, Vector3_Scale(&s1, &t, &dir));
            Vec3 diff = *FUN_0041db10(&s3, &hit, &block->mPos48);
            if (VectorLength(&diff) > model->GetScale() * 0.067f)
                return 0;
            else
                return block->GetField33c();
        } else {
        cSPEditorBlock* best = 0;
        float bestDist = 0.0f;
        int count = model->GetBlockCount();
        for (int i = 0; i < count; i++) {
            cSPEditorBlock* other = model->GetBlock(i);
            RefPtr mdl(other->GetModel());
            bool ok = true;
            BlockVec* kids = &other->mChildren;
            int nKids = (int)(kids->mpEnd - kids->mpBegin);
            for (int j = 0; j < nKids; j++) {
                if ((*kids)[j]->mFlags.test(0xb)) {
                    if (block->mFlags.test(0x2c) || block->mFlags.test(0x2d))
                        ok = false;
                }
            }
            bool ok2 = true;
            if (block->mFlags.test(0xa)) {
                if (!other->mFlags.test(0xa) && !other->mFlags.test(8))
                    ok2 = false;
            }
            if (ok2 && other != block && mdl.p && FUN_0044c030(other) && ok) {
                cSPEditorBlock** it = exclude->mpBegin;
                while (it != exclude->mpEnd && *it != other) it++;
                if (it == exclude->mpEnd) {
                    cSPEditorBlock* parent = other->mParent;
                    bool proceed = false;
                    if (!model->FUN_4adc40() || !parent) {
                        proceed = true;
                    } else {
                        cSPEditorBlock** it2 = exclude->mpBegin;
                        while (it2 != exclude->mpEnd && *it2 != parent) it2++;
                        if (it2 == exclude->mpEnd && parent != block) proceed = true;
                    }
                    if (proceed) {
                        Vec3 nrm;
                        Vec3* n = Vector3_Normalize(&nrm, &dir);
                        Plane plane;
                        Plane ptmp(n->operator[](0), n->operator[](1), n->operator[](2), -Dot3(mdl.p->GetPos(), n));
                        plane = ptmp;
                        float t;
                        if (IntersectRayPlane(&origin, &dir, &plane, &t)) {
                            Vec3 s1, s2, s3, s4;
                            Vec3 hit = *FUN_0041dc10(&s2, &origin, Vector3_Scale(&s1, &t, &dir));
                            Vec3 diff = *FUN_0041db10(&s3, &hit, mdl.p->GetPos());
                            if (VectorLength(&diff) < model->GetScale() * 0.043f) {
                                Vec3 diff2 = *FUN_0041db10(&s4, &hit, &origin);
                                float dist = VectorLength(&diff2);
                                if (!best || dist < bestDist) {
                                    best = other;
                                    bestDist = dist;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (best) {
            RefPtr m(best->GetModel());
            *outPos = *m.p->GetPos();
            return best;
        }
        }
    }
    return 0;
}

// PickBlocks view of a block: model at +0x10, world at +0x18, node-state calls.
struct BitsBase;
struct PickModel { char pad[0x44]; uint32_t mBits[2]; };
struct PickBlock {
    char pad[0x10];
    PickModel* mModel;
    PickModel* GetModel() { return mModel; }
    char pad14[4];
    struct IModelWorld* mWorld;   // +0x18
    struct IModelWorld* GetWorld() { return mWorld; }
    void SetNodeStateChecked(int state, bool checked);   // @ 0x437a60
    void ClearNodeState();                                // @ 0x437890
};
struct PickVec { PickBlock** mpBegin; PickBlock** mpEnd; PickBlock*& operator[](int i) { PickBlock** p = mpBegin + i; return *p; } };
struct IModelManager { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual uint32_t GetTypeBit(uint32_t key, int zero); };   // slot 0x28
struct IModelWorld { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual struct PickHit* Raycast(const Vec3* o, const Vec3* e, int zero, int a, int b, cSPEditorPickInfo* filter, char* extra, int c); }; // slot 0x24
struct PickHit { char pad[0x5d]; unsigned char mKind; char pad2[6]; void* mPtr64; };   // +0x5d kind, +0x64 ptr
struct BitsBase { uint32_t w[2]; __forceinline void set(uint32_t pos, bool v) {
    if (pos < 0x40) { if (v) { uint32_t* p = &w[pos >> 5]; *p = (1u << (pos % 32)) | *p; }
                      else   { uint32_t* p = &w[pos >> 5]; *p = ~(1u << (pos % 32)) & *p; } } } };
IModelManager* __cdecl ModelManager();                                   // @ 0x67dd80
void* __cdecl InterfaceCast(void* p);                                    // @ 0x4aa2a0
bool __fastcall GetResourceTypeFromModelType_(PickVec* v);               // @ 0x526430

// @ 0x4a4840
void* PickBlocks(PickVec* blocks, Vec3 origin, Vec3 dir, int a24, int a28, int a2c, bool* outFlag, int* pState)
{
    if (!GetResourceTypeFromModelType_(blocks)) {
        *outFlag = false;
        PickBlock* first = (*blocks)[0];
        IModelWorld* world = first->GetWorld();
        IModelManager* mm = ModelManager();
        if (mm && world) {
            bool hasState = false;
            int state = 4;
            if (pState) { hasState = true; state = *pState; }
            uint32_t id = mm->GetTypeBit(0x2cdfcbd, 0);
            int count = (int)(blocks->mpEnd - blocks->mpBegin);
            for (int i = 0; i < count; i++) {
                PickBlock* b = (*blocks)[i];
                if (b->GetModel()) {
                    ((BitsBase*)(b->GetModel()->mBits))->set(id, true);
                }
                b->SetNodeStateChecked(state, hasState);
            }
            cSPEditorPickInfo filter;
            filter.m0.set(id, true);
            filter.m15 |= 1;
            float scale = 1000.0f;
            Vec3 end = *FUN_0041dc10(&end, &origin, Vector3_Scale(&end, &scale, &dir));
            uint32_t extra[1];
            PickHit* hit = world->Raycast(&origin, &end, 0, a24, a28, &filter, (char*)extra, a2c);
            void* result = 0;
            if (hit && hit->mPtr64) {
                result = InterfaceCast(&hit->mPtr64);
                if (result && hit->mKind == 2) *outFlag = true;
            }
            for (int i = 0; i < count; i++) {
                PickBlock* b = (*blocks)[i];
                if (b->GetModel()) {
                    ((BitsBase*)(b->GetModel()->mBits))->set(id, false);
                }
                b->ClearNodeState();
            }
            return result;
        }
    }
    return 0;
}
