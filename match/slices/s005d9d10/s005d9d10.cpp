// Slice s005d9d10: SP::cSPEditorTactilityManager::Update (0x005d9d10).
// Advances every tactile (animated) component by the frame time: components attached to editor blocks,
// to models, to UI windows and to raw floats, then the cursor animation. Finished components are removed
// from their vector, and a key whose vector became empty is erased from its map.
// Member names come from the 2008 dev PDB (cSPEditorTactilityManager, cSPEditorTactileComponent);
// retail renumbered eEditorTactileType (0xb/0xc cursor, 0xd transform). Helper names are Claude-coined.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-.
#include "types.h"

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);    // 0x011e0744
#pragma function(memcpy)
void operator delete(void* p);                                                   // 0x00f47380
void operator delete[](void* p);                                                 // 0x00f47380

// cvtss2si helper (rounds with the current mode)
inline int FloatToInt(float f)
{
    int i;
    __asm cvtss2si eax, f
    __asm mov i, eax
    return i;
}

// ---- math ----
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPMatrix3 {
    cSPVector3 xAxis, yAxis, zAxis;
};
extern const cSPVector3 kZeroVector;                                             // 0x015ef03c
extern const cSPMatrix3 kIdentityMatrix;                                         // 0x015ef16c

struct cSPTransform {                       // 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3 mTranslation;                // +0x04
    float mScale;                           // +0x10
    cSPMatrix3 mRotation;                   // +0x14
    cSPTransform() : mFlags(0), mModificationCount(0), mTranslation(kZeroVector), mScale(1.0f),
                     mRotation(kIdentityMatrix) {}
    cSPTransform& operator=(const cSPTransform& t);                              // 0x00537dc0
    const cSPVector3& GetTranslation() const { return mTranslation; }
    void SetTranslation(const cSPVector3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};

// ---- EASTL ----
struct sp_vector_allocator {
    uint32_t mFlags;
    void deallocate(void* p) { if (((int*)p)[-1] != 0) operator delete[](p); }
};
template<class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    ~sp_vector() { if (mpBegin) mAllocator.deallocate(mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* erase(T* position) {
        if ((position + 1) < mpEnd)
            memcpy(position, position + 1, (unsigned int)((char*)mpEnd - (char*)(position + 1)));
        --mpEnd;
        return position;
    }
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
rbtree_node_base* __cdecl RBTreeIncrement(const rbtree_node_base* pNode);       // 0x00921580
void __cdecl RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pNodeAnchor); // 0x00921880

template<class K, class V> struct rbtree_node : rbtree_node_base {
    K first;                                // +0x10
    V second;                               // +0x14
};
template<class K, class V> struct rbtree_iterator {
    rbtree_node<K, V>* mpNode;
    rbtree_iterator(rbtree_node<K, V>* p) : mpNode(p) {}
    rbtree_iterator(rbtree_node_base* p) : mpNode((rbtree_node<K, V>*)p) {}
    rbtree_iterator& operator++() { mpNode = (rbtree_node<K, V>*)RBTreeIncrement(mpNode); return *this; }
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
    bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
    rbtree_node<K, V>* operator->() const { return mpNode; }
};

// eastl::map<K, V> (less<K>, eastl::allocator)
template<class K, class V> struct map {
    typedef rbtree_node<K, V> node_type;
    typedef rbtree_iterator<K, V> iterator;
    uint32_t mCompare;                      // +0x00 (empty less<>)
    rbtree_node_base mAnchor;               // +0x04
    uint32_t mnSize;                        // +0x14
    uint32_t mAllocator;                    // +0x18

    iterator begin() { return iterator(mAnchor.mpNodeLeft); }
    iterator end() { return iterator(&mAnchor); }
    iterator find(const K& key) {
        node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
        rbtree_node_base* pRangeEnd = &mAnchor;
        while (pCurrent) {
            if (!(pCurrent->first < key)) {
                pRangeEnd = pCurrent;
                pCurrent = (node_type*)pCurrent->mpNodeLeft;
            } else
                pCurrent = (node_type*)pCurrent->mpNodeRight;
        }
        if ((pRangeEnd != &mAnchor) && !(key < ((node_type*)pRangeEnd)->first))
            return iterator(pRangeEnd);
        return iterator(&mAnchor);
    }
    void DoFreeNode(node_type* pNode) {
        pNode->~node_type();
        operator delete[](pNode);
    }
    iterator erase(iterator position) {
        const iterator iErase(position);
        --mnSize;
        ++position;
        RBTreeErase(iErase.mpNode, &mAnchor);
        DoFreeNode(iErase.mpNode);
        return position;
    }
    uint32_t erase(const K& key) {
        const iterator it(find(key));
        if (it != end()) {
            erase(it);
            return 1;
        }
        return 0;
    }
    V& operator[](const K& key);
};

// ---- ref-counted keys ----
struct cMWModel;
struct cMWWorldVt {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
    virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
    virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
    virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
    virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
    virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
    virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84();
    virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88(); virtual void v89();
    virtual void v90(); virtual void v91();
    virtual void DestroyModel(cMWModel* model, bool flag);                       // +0x170
};

struct bitset32 {                           // eastl::bitset<32>
    uint32_t mWord;
    void set(uint32_t i, bool value) {
        if (value)
            mWord |= (1u << (i & 31));
        else
            mWord &= ~(1u << (i & 31));
    }
};
struct cMWModel {                           // retail SP::cMWModel (cMWObject base)
    cMWWorldVt* mpWorld;                    // +0x00
    bitset32 mFlags;                        // +0x04
    cSPTransform mTransform;                // +0x08
    int mnRefCount;                         // +0x40
    char pad44[0x4c - 0x44];
    float mColor[3];                        // +0x4c
    float mAlpha;                           // +0x58
    bool IsFlag31() const { return (mFlags.mWord >> 31) & 1; }
    void AddRef() { ++mnRefCount; }
    void Release() {
        if (mnRefCount < 2)
            mpWorld->DestroyModel(this, IsFlag31());
        else
            --mnRefCount;
    }
    void SetVisible(bool b) { mFlags.set(0, b); }
};

struct cSPEditorBlock {
    virtual void v0();
    virtual int AddRef();                                                        // +0x04
    virtual int Release();                                                       // +0x08
    char pad4[0x10 - 4];
    cMWModel* mModel;                       // +0x10
    char pad14[0x48 - 0x14];
    cSPVector3 mPosition;                   // +0x48
    char pad54[0x1d8 - 0x54];
    float mScale;                           // +0x1d8
    void SetPosition(const cSPVector3& pos, bool b);                             // 0x00448e90
};

namespace UTFWin {
struct IWindow {
    virtual int AddRef();                                                        // +0x00
    virtual int Release();                                                       // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual uint32_t GetFillColor();                                             // +0x30
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void SetFillColor(uint32_t color);                                   // +0x5c
};
}

struct cIModelWorld {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void SetAnimation(cMWModel* model, uint32_t animID, float value, int flags);   // +0x74
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> inline bool operator<(const AutoRefCount<T>& a, const AutoRefCount<T>& b)
{
    return a.mpObject < b.mpObject;
}

// ---- components ----
struct cSPEditorTactileComponent {          // 0x28
    int mType;
    int mLerp;
    float mHistoryValue;
    float mFinalValue;                      // +0x0c
    float mTimeRemaining;                   // +0x10
    float mTimeTotal;
    float mVelocity;
    float mOverShootX;
    float mOverShootScale;
    uint32_t mAnimationID;                  // +0x24
};
struct cSPEditorTactileTransformComponent : cSPEditorTactileComponent {   // 0xd0
    char pad28[0x70 - 0x28];
    cSPTransform mFinalTransformValue;      // +0x70
    char padA8[0xc0 - 0xa8];
    sp_vector<AutoRefCount<cSPEditorBlock> > mPileList;                         // +0xc0
};

typedef sp_vector<cSPEditorTactileComponent*> ComponentVector;
typedef map<AutoRefCount<cSPEditorBlock>, ComponentVector> BlockComponentMap;
typedef map<AutoRefCount<cMWModel>, ComponentVector> ModelComponentMap;
typedef map<AutoRefCount<UTFWin::IWindow>, ComponentVector> WindowComponentMap;
typedef map<AutoRefCount<cMWModel>, AutoRefCount<cIModelWorld> > ModelWorldMap;
typedef map<float*, ComponentVector> FloatComponentMap;

// The model map frees its nodes out of line.
template<> void ModelComponentMap::DoFreeNode(node_type* pNode);                  // 0x005d8d80
template<> AutoRefCount<cIModelWorld>& ModelWorldMap::operator[](const AutoRefCount<cMWModel>& key);   // 0x005d9800

void __cdecl SetBlockPileTransform(cSPEditorBlock* block, sp_vector<AutoRefCount<cSPEditorBlock> >* piles,
                                   cSPVector3 translation, cSPMatrix3 rotation);          // 0x0049ecf0
void __cdecl SetBlockScale(cSPEditorBlock* block, float scale, int a, int b);             // 0x0049e6a0

struct cSPUICursorManager {
    void SetLocalCursor(uint32_t id);                                            // 0x00801bb0
};
cSPUICursorManager* __cdecl CursorManager();                                    // 0x0067cab0
__forceinline void SetCursor(uint32_t id) { CursorManager()->SetLocalCursor(id); }

namespace SP {
class cSPEditorTactilityManager {
public:
    virtual void v0();
    void Update(uint32_t deltaTime);
    bool UpdateComponent(cSPEditorTactileComponent* c, cSPTransform* out, float dt);          // 0x005d8f10
    bool UpdateComponent(cSPEditorTactileComponent* c, float* out, float initial, float dt);  // 0x005d87b0

    BlockComponentMap mBlockComponentList;  // +0x04
    ModelComponentMap mModelComponentList;  // +0x20
    WindowComponentMap mWindowComponentList;// +0x3c
    ModelWorldMap mModelWorldList;          // +0x58
    FloatComponentMap mFloatComponentList;  // +0x74
    cSPEditorTactileComponent mCursorAnimation;   // +0x90
};

// @ 0x005d9d10
void cSPEditorTactilityManager::Update(uint32_t deltaTime)
{
    float dt = (float)deltaTime * 0.001f;

    // components on editor blocks
    for (BlockComponentMap::iterator it = mBlockComponentList.begin(); it != mBlockComponentList.end(); ) {
        AutoRefCount<cSPEditorBlock> block(it->first);
        ComponentVector& comps = it->second;
        for (cSPEditorTactileComponent** ci = comps.begin(); ci != comps.end(); ) {
            cSPEditorTactileComponent* c = *ci;
            c->mTimeRemaining -= dt;
            bool done;
            if (c->mType == 0xd) {
                cSPEditorTactileTransformComponent* tc = (cSPEditorTactileTransformComponent*)c;
                cSPTransform transform;
                done = UpdateComponent(c, &transform, dt);
                if (done)
                    transform = tc->mFinalTransformValue;
                SetBlockPileTransform(block, &tc->mPileList, transform.mTranslation, transform.mRotation);
            } else {
                float initial = (c->mType == 8) ? block->mScale : 0.0f;
                float value;
                done = UpdateComponent(c, &value, initial, dt);
                if (done)
                    value = c->mFinalValue;
                cSPVector3 pos(block->mPosition);
                switch (c->mType) {
                case 4:
                    block->mModel->mAlpha = value;
                    block->mModel->SetVisible(value != 0.0f);
                    break;
                case 5:
                    pos.x = value;
                    block->SetPosition(pos, false);
                    break;
                case 6:
                    pos.y = value;
                    block->SetPosition(pos, false);
                    break;
                case 7:
                    pos.z = value;
                    block->SetPosition(pos, false);
                    break;
                case 10:
                    pos.z = initial;
                    block->SetPosition(pos, false);
                    break;
                case 8:
                    SetBlockScale(block, value, 1, 1);
                    break;
                }
            }
            if (done)
                ci = comps.erase(ci);
            else
                ++ci;
        }
        if (comps.size() == 0) {
            ++it;
            mBlockComponentList.erase(block);
        } else
            ++it;
    }

    // components on models
    for (ModelComponentMap::iterator it = mModelComponentList.begin(); it != mModelComponentList.end(); ) {
        cMWModel* model = it->first;
        ComponentVector& comps = it->second;
        for (cSPEditorTactileComponent** ci = comps.begin(); ci != comps.end(); ) {
            cSPEditorTactileComponent* c = *ci;
            c->mTimeRemaining -= dt;
            float value = 0.0f;
            bool done = UpdateComponent(c, &value, 0.0f, dt);
            switch (c->mType) {
            case 1:
                model->mColor[0] = value;
                break;
            case 2:
                model->mColor[1] = value;
                break;
            case 3:
                model->mColor[2] = value;
                break;
            case 4:
                model->mAlpha = value;
                model->SetVisible(value != 0.0f);
                break;
            case 5: {
                const cSPVector3& t = model->mTransform.GetTranslation();
                model->mTransform.SetTranslation(cSPVector3(value, t.y, t.z));
                break;
            }
            case 6: {
                const cSPVector3& t = model->mTransform.GetTranslation();
                model->mTransform.SetTranslation(cSPVector3(t.x, value, t.z));
                break;
            }
            case 7: {
                const cSPVector3& t = model->mTransform.GetTranslation();
                model->mTransform.SetTranslation(cSPVector3(t.x, t.y, value));
                break;
            }
            case 9:
                if (mModelWorldList.find(model) != mModelWorldList.end())
                    mModelWorldList[model]->SetAnimation(model, c->mAnimationID, value, 0);
                break;
            }
            if (done) {
                delete c;
                ci = comps.erase(ci);
            } else
                ++ci;
        }
        if (comps.size() == 0) {
            ++it;
            mModelComponentList.erase(model);
        } else
            ++it;
    }

    // components on UI windows (fill color channels)
    for (WindowComponentMap::iterator it = mWindowComponentList.begin(); it != mWindowComponentList.end(); ) {
        UTFWin::IWindow* window = it->first;
        ComponentVector& comps = it->second;
        for (cSPEditorTactileComponent** ci = comps.begin(); ci != comps.end(); ) {
            uint32_t color = window->GetFillColor();
            cSPEditorTactileComponent* c = *ci;
            c->mTimeRemaining -= dt;
            float value;
            bool done = UpdateComponent(c, &value, 0.0f, dt);
            char channel = (char)FloatToInt(value);
            switch (c->mType) {
            case 1:
                window->SetFillColor(((int)channel << 16) | (color & 0xff00ffff));
                break;
            case 2:
                window->SetFillColor(((int)channel << 8) | (color & 0xffff00ff));
                break;
            case 3:
                window->SetFillColor((color & 0xffffff00) | (int)channel);
                break;
            case 4:
                window->SetFillColor(((int)channel << 24) | (color & 0x00ffffff));
                break;
            }
            if (done) {
                delete c;
                ci = comps.erase(ci);
            } else
                ++ci;
        }
        if (comps.size() == 0) {
            ++it;
            mWindowComponentList.erase(window);
        } else
            ++it;
    }

    // components driving raw floats
    for (FloatComponentMap::iterator it = mFloatComponentList.begin(); it != mFloatComponentList.end(); ) {
        float* target = it->first;
        ComponentVector& comps = it->second;
        for (cSPEditorTactileComponent** ci = comps.begin(); ci != comps.end(); ) {
            float initial = *target;
            cSPEditorTactileComponent* c = *ci;
            c->mTimeRemaining -= dt;
            float value;
            bool done = UpdateComponent(c, &value, initial, dt);
            *target = value;
            if (done) {
                delete c;
                ci = comps.erase(ci);
            } else
                ++ci;
        }
        if (comps.size() == 0) {
            ++it;
            mFloatComponentList.erase(target);
        } else
            ++it;
    }

    // cursor animation
    if (mCursorAnimation.mType != 0) {
        mCursorAnimation.mTimeRemaining -= dt;
        float value;
        bool done = UpdateComponent(&mCursorAnimation, &value, 0.0f, dt);
        if (mCursorAnimation.mType == 0xb) {
            switch ((int)(value * 10.0f)) {
            case 0: SetCursor(0x1002); break;
            case 1: SetCursor(0x1012); break;
            case 2: SetCursor(0x1013); break;
            case 3: SetCursor(0x1014); break;
            case 4: SetCursor(0x1015); break;
            case 5: SetCursor(0x1016); break;
            case 6: SetCursor(0x1017); break;
            case 7: SetCursor(0x1018); break;
            case 8: SetCursor(0x1019); break;
            case 9: SetCursor(0x101a); break;
            case 10: SetCursor(0x1001); break;
            }
        } else if (mCursorAnimation.mType == 0xc) {
            switch ((int)(value * 10.0f)) {
            case 0: SetCursor(0x1005); break;
            case 1: SetCursor(0x101b); break;
            case 2: SetCursor(0x101c); break;
            case 3: SetCursor(0x101d); break;
            case 4: SetCursor(0x101e); break;
            case 5: SetCursor(0x101f); break;
            case 6: SetCursor(0x1020); break;
            case 7: SetCursor(0x1021); break;
            case 8: SetCursor(0x1022); break;
            case 9: SetCursor(0x1023); break;
            case 10: SetCursor(0x1001); break;
            }
        }
        if (done)
            mCursorAnimation.mType = 0;
    }
}
}
