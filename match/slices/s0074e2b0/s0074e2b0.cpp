// Slice s0074e2b0: Editor/UI resource helpers (~0x0074e2b0-0x0074f1a0).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"


// ---------------------------------------------------------------------------
// 0x0074F1A0  add-unique to vector<int> (begin +0x4c)
// ---------------------------------------------------------------------------
struct IntVec {
    int* mpBegin; int* mpEnd; int* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    int& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(int* pos, const int& v);   // 0x006ec4a0 (eastl::vector<int>::DoInsertValue, grow path)
    void push_back(const int& x)
    {
        if (mpEnd < mpCapacity) {
            int* e = mpEnd++;
            if (e)
                *e = x;
        } else
            DoInsertValue(mpEnd, x);
    }
};

struct VecIntAdd {
    char pad0[0x4c];
    IntVec v;     // +0x4c
    bool add_unique(int x);
};

// @ 0x0074f1a0
bool VecIntAdd::add_unique(int x)
{
    IntVec& vec = v;
    int n = vec.size();
    for (int i = 0; i < n; ++i)
        if (vec[i] == x)
            return false;
    vec.push_back(x);
    return true;
}

// ===========================================================================
// 0x0074ED00 / 0x0074EE80 / 0x0074EB70  SP::cModelWorld::FindModelsIn*
//   Collect the models of the world that pass a filter into an output vector. With a populated
//   hier-grid (and the app property at gAppProperties->list->+0x2c > 1) the grid is queried (up to
//   0x400 hits); otherwise the whole group list is walked.
// ===========================================================================
#include <string.h>
#include <math.h>

struct Node { Node* next; Node* prev; };       // eastl::intrusive_list_node

struct ModelVec {                              // eastl::vector<cMWModelInternal*, sp_vector_allocator>
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void DoInsertValue(void** position, void* const& value);   // 0x006c1570
    void erase(void** first, void** last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(void* const& value)
    {
        if (mpEnd < mpCapacity) {
            void** p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

struct PropValues { char pad[0x2c]; int mValue; };
struct AppProperties { char pad[0x3c]; PropValues* mpValues; };
extern AppProperties* gAppProperties;          // 0x015fd918

struct HierGrid {
    char pad0[0x24];
    void** mGridsBegin;                        // +0x24 (retail grid at world+0x118)
    void** mGridsEnd;
    char pad1[0x78 - 0x2c];
    int QuerySphere(const void* center, const void* radius, int max, Node** out);   // 0x007027e0
    int QueryFrustum(const void* frustum, int max, Node** out);                      // 0x007026d0
    int QueryShape(float f, const void* p, int max, Node** out);                     // 0x00702760
    int QueryRay(const void* start, const void* end, float radius, int max, Node** out);  // 0x00702860
};

bool __cdecl FilterModelSphere(Node* item, const void* sphere, void* ctx);    // 0x00748800 (anonymous ns)
bool __cdecl FilterModelFrustum(Node* item, const void* frustum, void* ctx);  // 0x007460b0 (anonymous ns)
bool __cdecl FilterModelShape(Node* item, const void* p, float f, void* ctx); // 0x00748530

struct cModelWorld {
    char pad0[0x118];
    HierGrid mHierGrid;        // +0x118
    char pad1[0x19c - 0x118 - 0x78];
    Node mGroupList;           // +0x19c
    bool FindModelsInSphere(const void* sphere, ModelVec* out, void* ctx);                    // 0x0074ed00
    bool FindModelsInBox(const void* frustum, ModelVec* out, void* ctx);                      // 0x0074ee80
    bool FindModelsInShape(const void* p, float f, ModelVec* out, void* ctx);                 // 0x0074eb70
    bool RayCastModels(const struct Vec3* start, const struct Vec3* end, struct HitVec* out, const struct ModelFilter* filter, float radius);  // 0x0074e2b0
};

// @ 0x0074ED00  SP::cModelWorld::FindModelsInSphere
bool cModelWorld::FindModelsInSphere(const void* sphere, ModelVec* out, void* ctx)
{
    Node* items[0x400];
    bool bGrid;
    if (mHierGrid.mGridsBegin != mHierGrid.mGridsEnd && gAppProperties->mpValues->mValue > 1)
        bGrid = true;
    else
        bGrid = false;
    out->clear();
    if (bGrid) {
        int n = mHierGrid.QuerySphere(sphere, (const char*)sphere + 0xc, 0x400, items);
        for (int i = 0; i < n; ++i) {
            Node* item = items[i];
            if (!FilterModelSphere(item, sphere, ctx)) {
                void* model = item ? (void*)(item + 1) : 0;
                out->push_back(model);
            }
        }
    } else {
        for (Node* it = mGroupList.next; it != &mGroupList; it = it->next) {
            if (!FilterModelSphere(it, sphere, ctx)) {
                void* model = it ? (void*)(it + 1) : 0;
                out->push_back(model);
            }
        }
    }
    return out->mpBegin != out->mpEnd;
}

// @ 0x0074EE80  SP::cModelWorld::FindModelsInBox
bool cModelWorld::FindModelsInBox(const void* frustum, ModelVec* out, void* ctx)
{
    Node* items[0x400];
    bool bGrid;
    if (mHierGrid.mGridsBegin != mHierGrid.mGridsEnd && gAppProperties->mpValues->mValue > 1)
        bGrid = true;
    else
        bGrid = false;
    out->clear();
    if (bGrid) {
        int n = mHierGrid.QueryFrustum(frustum, 0x400, items);
        for (int i = 0; i < n; ++i) {
            Node* item = items[i];
            if (!FilterModelFrustum(item, frustum, ctx)) {
                void* model = item ? (void*)(item + 1) : 0;
                out->push_back(model);
            }
        }
    } else {
        for (Node* it = mGroupList.next; it != &mGroupList; it = it->next) {
            if (!FilterModelFrustum(it, frustum, ctx)) {
                void* model = it ? (void*)(it + 1) : 0;
                out->push_back(model);
            }
        }
    }
    return out->mpBegin != out->mpEnd;
}

// @ 0x0074EB70  cModelWorld::FindModelsIn<shape> (float + pointer variant)
bool cModelWorld::FindModelsInShape(const void* p, float f, ModelVec* out, void* ctx)
{
    Node* items[0x400];
    bool bGrid;
    if (mHierGrid.mGridsBegin != mHierGrid.mGridsEnd && gAppProperties->mpValues->mValue > 1)
        bGrid = true;
    else
        bGrid = false;
    out->clear();
    if (bGrid) {
        int n = mHierGrid.QueryShape(f, p, 0x400, items);
        for (int i = 0; i < n; ++i) {
            Node* item = items[i];
            if (!FilterModelShape(item, p, f, ctx)) {
                void* model = item ? (void*)(item + 1) : 0;
                out->push_back(model);
            }
        }
    } else {
        for (Node* it = mGroupList.next; it != &mGroupList; it = it->next) {
            if (!FilterModelShape(it, p, f, ctx)) {
                void* model = it ? (void*)(it + 1) : 0;
                out->push_back(model);
            }
        }
    }
    return out->mpBegin != out->mpEnd;
}

// ===========================================================================
// Editor resource (two-base class, vtables 0x0140d720 / 0x0140d71c): rbtree maps, AutoRefCount, vector<int>
// ===========================================================================
void __cdecl EASTL_allocator_deallocate(void* p);                   // 0x00f47380
struct RBNodeBase { RBNodeBase* mpNodeRight; RBNodeBase* mpNodeLeft; RBNodeBase* mpNodeParent; char mColor; };
RBNodeBase* __cdecl RBTreeIncrement(const RBNodeBase* pNode);       // 0x00921580
void __cdecl RBTreeErase(RBNodeBase* pNode, RBNodeBase* pNodeAnchor); // 0x00921880

struct IListener {            // value held by the first map (slot 94 = vtable +0x178)
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    char pad[0x178 - 0x10];   // overridden below
};
struct IListenerV {           // vtable with slot 94
    virtual int AddRef();
    virtual int Release();
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
    virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
    virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
    virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73();
    virtual void s74(); virtual void s75(); virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
    virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84(); virtual void s85();
    virtual void s86(); virtual void s87(); virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
    virtual void s92(); virtual void s93();
    virtual void Notify();    // slot 94 (+0x178)
};

struct MapNode {              // rbtree_node<pair<unsigned, AutoRefCount<IListenerV>>>
    RBNodeBase base;
    unsigned mKey;            // +0x10
    IListenerV* mpValue;      // +0x14
};

struct ListenerMap {          // eastl::map<unsigned, AutoRefCount<IListenerV>> at resource +0xc
    int mCompare;             // +0x0 (empty compare + allocator)
    RBNodeBase mAnchor;       // +0x4
    unsigned mnSize;          // +0x14
    void DoNukeSubtree(RBNodeBase* pNode);   // 0x00d0c930
    ~ListenerMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
    ListenerMap() {}
    struct iterator { RBNodeBase* mpNode; iterator() {} };
    iterator find(const unsigned& key);      // 0x00e5c780
    void clear()
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    iterator end() { iterator e; e.mpNode = &mAnchor; return e; }
    __forceinline void erase(iterator position)
    {
        ((MapNode*)position.mpNode)->mpValue->Notify();
        --mnSize;
        RBTreeIncrement(position.mpNode);
        RBTreeErase(position.mpNode, &mAnchor);
        IListenerV* pValue = *(IListenerV* volatile*)&((MapNode*)position.mpNode)->mpValue;
        if (pValue) pValue->Release();
        EASTL_allocator_deallocate(position.mpNode);
    }
};
struct TableMap {             // second map at resource +0x28 (node nuke at 0x009a9600)
    int mCompare;
    RBNodeBase mAnchor;
    unsigned mnSize;
    void DoNukeSubtree(RBNodeBase* pNode);   // 0x009a9600
    ~TableMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
};
struct IntVecSp {             // eastl::vector<int, sp_vector_allocator>
    int* mpBegin; int* mpEnd; int* mpCapacity;
    ~IntVecSp() throw() {
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
    }
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct ResBase0 { virtual ~ResBase0() {} };
struct ResBase1 { virtual ~ResBase1() {} };

struct EditorResource : ResBase0, ResBase1 {
    int mnRefCount;                // +0x8
    ListenerMap mListeners;        // +0xc
    int mPad24;                    // +0x24
    TableMap mTable;               // +0x28
    int mPad40[2];                 // +0x40
    AutoRef<IListenerV> mpOwner;   // +0x48
    IntVecSp mIds;                 // +0x4c
    ~EditorResource();             // 0x0074f010
    bool Shutdown();               // 0x0074f0c0
    void RemoveListener(unsigned key);   // 0x0074f130
};

// @ 0x0074F010  Editor resource destructor
EditorResource::~EditorResource() {}

// @ 0x0074F0C0  release owner, notify + clear listener map
bool EditorResource::Shutdown()
{
    mpOwner = 0;
    for (RBNodeBase* n = mListeners.mAnchor.mpNodeLeft; n != &mListeners.mAnchor; n = RBTreeIncrement(n))
        ((MapNode*)n)->mpValue->Notify();
    mListeners.clear();
    return true;
}

// @ 0x0074F130  find listener by key, notify, erase
void EditorResource::RemoveListener(unsigned key)
{
    ListenerMap::iterator it = mListeners.find(key);
    if (it.mpNode != mListeners.end().mpNode)
        mListeners.erase(it);
}

// ===========================================================================
// 0x0074E2B0  SP::cModelWorld ray/capsule cast against the models
//   Collects every enabled model that passes the filter masks and whose bounds are hit by the
//   segment start->end swept by `radius`, as (model, distance) pairs sorted by distance.
// ===========================================================================
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33 {
    float m[9];
    Matrix33() {}
    Matrix33(const Matrix33& o);                  // 0x0041cb40
};
struct cSPTransform {
    unsigned short mFlags;
    unsigned short mModificationCount;
    Vec3 mTranslation;
    float mScale;
    Matrix33 mRotation;
    cSPTransform& operator=(const cSPTransform& x);   // 0x00537dc0
    cSPTransform(const Vec3& t, const Matrix33& r) : mTranslation(t), mRotation(r)
    {
        mModificationCount = 0;
        mFlags = 0;
        mScale = 1.0f;
    }
};
extern const Vec3 gVec3Zero;          // 0x0162eb0c
extern const Matrix33 gMatrix33Identity;  // 0x0162ec4c
extern const float gFltMax;           // 0x0140d674
extern const float gNegFltMax;        // 0x013f51ac

struct HitPair { void* mpModel; float mDistance; };
struct HitVec {                       // eastl::vector<pair<cMWModel*, float>, sp_vector_allocator>
    HitPair* mpBegin; HitPair* mpEnd; HitPair* mpCapacity;
    void erase(HitPair* first, HitPair* last);                       // 0x00d018d0
    void insert(HitPair* position, const HitPair& value);            // 0x0074cd70
};
struct ModelFilter {
    unsigned __int64 mInclude;            // +0x0
    unsigned __int64 mExclude;            // +0x8
    bool (__cdecl *mpCallback)(void* model);   // +0x10
    unsigned char mDefaultLOD;            // +0x14
    unsigned char mFlags;                 // +0x15 (1: use model LOD, 2: ignore model scale)
};
struct LODData { char pad[0xcc]; int mValid; };
struct ModelItem : Node {             // cMWModelInternal (intrusive list node first)
    unsigned mFlags;                  // +0x08 is the model; flags at +0xc
    char pad0[0x10 - 0x0c];
    cSPTransform mTransform;          // +0x10
    char pad1[0x4c - 0x10 - sizeof(cSPTransform)];
    unsigned __int64 mMask;           // +0x4c
    char pad2[0x65 - 0x54];
    unsigned char mLOD;               // +0x65
    char pad3[0x74 - 0x66];
    float mBoundRadius;               // +0x74
    float mBox[6];                    // +0x78
    char pad4[0x9c - 0x90];
    LODData* mpLOD3;                  // +0x9c
    char pad5[0xac - 0xa0];
    LODData* mpLOD2;                  // +0xac
};

bool __cdecl RaySphereHit(const Vec3* start, const Vec3* end, const Vec3* center, float radius, float* pDist);  // 0x00700c80
bool __cdecl RayModelLOD(const Vec3* start, const Vec3* end, const cSPTransform* xf, const float* bounds, const Matrix33* basis,
                         ModelItem* item, int variant, float* pDist, float radius);   // 0x00748ad0
bool __cdecl RayBox(const Vec3* start, const Vec3* end, const cSPTransform* xf, float x0, float y0, float z0, float x1, float y1, float z1,
                    float* pDist, float radius);                                      // 0x007442c0
Matrix33* __cdecl BuildBasis(Matrix33* out, const Vec3* dir, const Vec3* up);         // 0x0069b1c0

// @ 0x0074E2B0
bool cModelWorld::RayCastModels(const Vec3* start, const Vec3* end, HitVec* out, const ModelFilter* filter, float radius)
{
    out->erase(out->mpBegin, out->mpEnd);
    cSPTransform xform(gVec3Zero, gMatrix33Identity);
    int count = 0;
    float bounds[6];
    Matrix33 basis;
    Vec3 bmin(gFltMax, gFltMax, gFltMax);
    Vec3 bmax(gNegFltMax, gNegFltMax, gNegFltMax);
    bounds[0] = bmin.x; bounds[1] = bmin.y; bounds[2] = bmin.z;
    bounds[3] = bmax.x; bounds[4] = bmax.y; bounds[5] = bmax.z;
    if (0.0f < radius) {
        Vec3 d(end->x - start->x, end->y - start->y, end->z - start->z);
        float len = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
        Vec3 up(0.0f, 0.0f, 1.0f);
        float inv = 1.0f / (len + 1e-10f);
        Vec3 dir(inv * d.x, inv * d.y, inv * d.z);
        Matrix33 tmp;
        basis = *BuildBasis(&tmp, &dir, &up);
        bounds[0] = -radius; bounds[1] = -radius; bounds[2] = -radius;
        bounds[3] = radius; bounds[4] = radius; bounds[5] = len + radius;
    }
    HitPair hit;
    float dist;
    if (mHierGrid.mGridsBegin != mHierGrid.mGridsEnd && gAppProperties->mpValues->mValue > 1) {
        Node* items[0x400];
        int n = mHierGrid.QueryRay(start, end, radius, 0x400, items);
        for (int i = 0; i < n; ++i) {
            ModelItem* item = (ModelItem*)items[i];
            if (!(item->mFlags & 1)) continue;
            if (!((filter->mInclude == 0 || (item->mMask & filter->mInclude) != 0) && (item->mMask & filter->mExclude) == 0))
                continue;
            if (filter->mpCallback && !filter->mpCallback((char*)item + 8)) continue;
            int lod;
            if ((filter->mFlags & 1) && ((item->mFlags >> 8) & 1)) lod = item->mLOD; else lod = filter->mDefaultLOD;
            xform = item->mTransform;
            if (((item->mFlags >> 7) & 1) || (filter->mFlags & 2)) {
                ++xform.mModificationCount;
                xform.mScale = 1.0f;
            }
            Vec3 center(xform.mTranslation.x, xform.mTranslation.y, xform.mTranslation.z);
            if (!RaySphereHit(start, end, &center, item->mBoundRadius * xform.mScale + radius, &dist)) continue;
            if (lod >= 3 && item->mpLOD3 && item->mpLOD3->mValid) {
                if (!RayModelLOD(start, end, &xform, bounds, &basis, item, 0, &dist, radius)) continue;
            } else if (lod >= 2 && item->mpLOD2 && item->mpLOD2->mValid) {
                if (!RayModelLOD(start, end, &xform, bounds, &basis, item, 4, &dist, radius)) continue;
            } else if (lod >= 1 && item->mBox[0] <= item->mBox[3]) {
                if (!RayBox(start, end, &xform, item->mBox[0], item->mBox[1], item->mBox[2], item->mBox[3], item->mBox[4], item->mBox[5], &dist, radius)) continue;
            }
            hit.mpModel = (char*)item + 8;
            hit.mDistance = dist;
            int idx = 0;
            while (idx < count && !(dist <= out->mpBegin[idx].mDistance)) ++idx;
            out->insert(out->mpBegin + idx, hit);
            ++count;
        }
    } else {
        for (ModelItem* item = (ModelItem*)mGroupList.next; item != (ModelItem*)&mGroupList; item = (ModelItem*)item->next) {
            if (!(item->mFlags & 1)) continue;
            if (!((filter->mInclude == 0 || (item->mMask & filter->mInclude) != 0) && (item->mMask & filter->mExclude) == 0))
                continue;
            if (filter->mpCallback && !filter->mpCallback((char*)item + 8)) continue;
            int lod;
            if ((filter->mFlags & 1) && ((item->mFlags >> 8) & 1)) lod = item->mLOD; else lod = filter->mDefaultLOD;
            xform = item->mTransform;
            if (((item->mFlags >> 7) & 1) || (filter->mFlags & 2)) {
                ++xform.mModificationCount;
                xform.mScale = 1.0f;
            }
            Vec3 center(xform.mTranslation.x, xform.mTranslation.y, xform.mTranslation.z);
            if (!RaySphereHit(start, end, &center, item->mBoundRadius * xform.mScale + radius, &dist)) continue;
            if (lod >= 3 && item->mpLOD3 && item->mpLOD3->mValid) {
                if (!RayModelLOD(start, end, &xform, bounds, &basis, item, 0, &dist, radius)) continue;
            } else if (lod >= 2 && item->mpLOD2 && item->mpLOD2->mValid) {
                if (!RayModelLOD(start, end, &xform, bounds, &basis, item, 4, &dist, radius)) continue;
            } else if (lod >= 1 && item->mBox[0] <= item->mBox[3]) {
                if (!RayBox(start, end, &xform, item->mBox[0], item->mBox[1], item->mBox[2], item->mBox[3], item->mBox[4], item->mBox[5], &dist, radius)) continue;
            }
            hit.mpModel = (char*)item + 8;
            hit.mDistance = dist;
            int idx = 0;
            while (idx < count && !(dist <= out->mpBegin[idx].mDistance)) ++idx;
            out->insert(out->mpBegin + idx, hit);
            ++count;
        }
    }
    return count != 0;
}
