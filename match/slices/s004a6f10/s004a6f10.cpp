// Slice s004a6f10: SP::EditorUtils::DeleteInvalidBlocks (single very large /Od function).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// DeleteInvalidBlocks(block): for the editor model that owns `block`, marks every block that is
// invalid (or whose symmetric partner is gone) for deletion, re-pins the children of the blocks
// being deleted onto their symmetric partners, then deletes the marked blocks: each deletion is
// broadcast (message 0x7f18f481), removed from the message manager and from the model. When anything
// was deleted, the summed block cost and the size-weighted centre of the deleted blocks are sent as
// message 0xf058b0f2. The model's symmetry mode is switched off while this runs and restored after.
#include "types.h"

// ---- math -----------------------------------------------------------------
// rw::math::fpu::Vector3Template<float,0>: its copy constructor is out of line.
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                                    // 0x004098a0
    float operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
};
Vector3T operator-(const Vector3T& a, const Vector3T& b);           // 0x0041db10
Vector3T operator*(const float& s, const Vector3T& v);              // 0x0041de40
Vector3T& operator+=(Vector3T& a, const Vector3T& b);               // 0x0041ddb0
Vector3T operator/(const Vector3T& v, const float& s);              // 0x00453880
float VectorLength(const cSPVector3& v);                            // 0x0040ae50

struct BoundingBox {
    Vector3T mMin, mMax;
    Vector3T GetCenter() const;                                     // 0x00409b90
};

extern const Vector3T kZeroVector;                                  // 0x015d64d8

// ---- EASTL / EA -------------------------------------------------------------
struct AllocTag { AllocTag() {} };

template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const
    {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

// EA::RefCountTemplate<int>: Release contains `delete this`, so it stays out of line.
struct RefCountTemplate {
    virtual ~RefCountTemplate();
    int mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                                  // 0x00453540
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct cSPEditorBlock;
typedef AutoRefCount<cSPEditorBlock> BlockRef;

// eastl::vector<AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
struct BlockVector {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    uint32_t  mAllocator[2];
    BlockVector(const AllocTag& a = AllocTag());                    // 0x00540470
    ~BlockVector();                                                 // 0x00453eb0
    void push_back(const BlockRef& v);                              // 0x004541f0
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef& operator[](int i) { return mpBegin[i]; }
    BlockRef* begin() { return mpBegin; }
    BlockRef* end() { return mpEnd; }
};

// eastl::fixed_vector<AutoRefCount<cSPEditorBlock>, 8>
struct FixedBlockVector : BlockVector {
    uint32_t mOverflow;
    void*    mBuffer[8];
    FixedBlockVector() { FixedInit(); }
    void FixedInit();                                               // 0x00453770
    FixedBlockVector& operator=(const BlockVector& x);              // 0x00453f20
};

template <class It, class T>
inline It find(It first, It last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

// ---- editor -----------------------------------------------------------------
struct cSPEditorModel;

struct cSPEditorBlock {
    virtual void _v0();
    virtual int AddRef();                                           // +0x04
    virtual int Release();                                          // +0x08
    uint32_t pad04[(0x28 - 0x04) / 4];
    cSPEditorModel* mpModel;                                        // +0x028
    uint32_t pad2c[(0x340 - 0x2c) / 4];
    BlockVector mChildren;                                          // +0x340
    uint32_t pad354[(0x3e0 - 0x354) / 4];
    BlockRef mSymmetricBlock;                                       // +0x3e0
    BlockRef mPairedBlock;                                          // +0x3e4
    uint32_t pad3e8[(0x3f0 - 0x3e8) / 4];
    void*    mpSymmetryHandle;                                      // +0x3f0
    uint32_t pad3f4[(0x5e4 - 0x3f4) / 4];
    int      mCost;                                                 // +0x5e4
    uint32_t pad5e8[(0xdc8 - 0x5e8) / 4];
    bitset<60> mFlags;                                              // +0xdc8

    cSPEditorModel* GetEditorModel() { return mpModel; }
    cSPEditorBlock* GetSymmetricBlock() { return mSymmetricBlock; }
    cSPEditorBlock* GetPairedBlock() { return mPairedBlock; }
    void* GetSymmetryHandle() { return mpSymmetryHandle; }
    int GetCost() { return mCost; }
    bool IsValid();                                                 // 0x0044c030
    void SetBooleanAttribute(int id, bool value);                   // 0x00435a10
    int GetSymmetryIndex();                                         // 0x0044f220
    bool IsSymmetryLocked();                                        // 0x00435c80
    void AttachChild(cSPEditorBlock* child);                        // 0x00438700
    Vector3T GetOffsetA(bool b);                                    // 0x00438120
    Vector3T GetOffsetB(bool b);                                    // 0x004381e0
    void Place(Vector3T a, Vector3T b);                             // 0x00437b00
    BoundingBox GetBBox(int a, int b, int c);                       // 0x0044ae00
};

struct cSPEditorModelBase {
    virtual ~cSPEditorModelBase();
};
struct cSPEditorModel : cSPEditorModelBase, RefCountTemplate {     // RefCountTemplate at +4
    int GetBlockCount();                                            // 0x004accf0
    cSPEditorBlock* GetBlock(int index);                            // 0x004accb0
    void SetUsingSymmetry(bool b);                                  // 0x004adc20
    bool IsUsingSymmetry();                                         // 0x004adc40
    void RemoveBlock(cSPEditorBlock* block, bool b);                // 0x004acab0
};

// Message parameters are 8-byte slots.
union MessageParam {
    int   i;
    float f;
    void* p;
    uint32_t pad[2];
};
struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SendMessage(uint32_t id, void* data, int flags);  // +0x14
};
struct cMessageManager {
    void RemoveListener(cSPEditorBlock* block);                     // 0x0045b150
};
IMessageServer* MessageServer();                                    // 0x0067dcc0
cMessageManager* MessageManager();                                  // 0x00401050

namespace SP { namespace EditorUtils {

// @ 0x004a6f10
void DeleteInvalidBlocks(cSPEditorBlock* block)
{
    AutoRefCount<cSPEditorModel> model(block->GetEditorModel());
    if (model) {
        bool usingSymmetry = model->IsUsingSymmetry();
        model.mpObject->SetUsingSymmetry(false);

        // 1. Mark invalid blocks, and the partners of symmetric blocks, for deletion.
        int numBlocks = model->GetBlockCount();
        bool partnerOfBlock = false;
        for (int i = 0; i < numBlocks; i++) {
            cSPEditorBlock* b = model->GetBlock(i);
            if (!b->IsValid())
                b->SetBooleanAttribute(1, true);
            if (b->mFlags.test(11) && !b->mFlags.test(1) && b->GetSymmetryHandle() &&
                b->GetSymmetryIndex() == 0.0 && b->GetSymmetricBlock()) {
                b->GetSymmetricBlock()->SetBooleanAttribute(1, true);
                if (b->GetSymmetricBlock() == block)
                    partnerOfBlock = true;
            }
        }

        // 2. Collect the marked blocks; move the children of a deleted block to its partner.
        bool deletedAny = false;
        int totalCost = 0;
        BlockVector kept;
        BlockVector doomed;
        numBlocks = model->GetBlockCount();
        for (int i = 0; i < numBlocks; i++) {
            cSPEditorBlock* b = model->GetBlock(i);
            if (b->mFlags.test(1)) {
                doomed.push_back(BlockRef(b));
                if (b->GetSymmetryIndex() == 0.0f && b->GetSymmetricBlock() &&
                    !b->GetSymmetricBlock()->mFlags.test(1)) {
                    FixedBlockVector children;
                    children = b->mChildren;
                    for (int j = 0, numChildren = children.size(); j < numChildren; j++) {
                        b->GetSymmetricBlock()->AttachChild(children[j]);
                        if (!b->GetSymmetricBlock()->mFlags.test(10)) {
                            Vector3T offsetA = children[j]->GetOffsetA(true);
                            Vector3T offsetB = children[j]->GetOffsetB(true);
                            children[j]->Place(offsetA, offsetB);
                        }
                    }
                }
            }
        }

        // 3. Delete them.
        numBlocks = doomed.size();
        model.mpObject->SetUsingSymmetry(false);
        Vector3T centerSum(kZeroVector);
        float sizeSum = 0.0f;
        for (int k = 0; k < numBlocks; k++) {
            cSPEditorBlock* b = doomed[k];
            bool counted = true;
            if (b->mFlags.test(20) || find(kept.begin(), kept.end(), b) != kept.end() ||
                (b->GetSymmetricBlock() && !b->GetSymmetricBlock()->mFlags.test(1)))
                counted = false;
            if (counted) {
                int cost = 0;
                if (b->IsSymmetryLocked()) {
                    if (b->GetPairedBlock()) {
                        if (find(doomed.begin(), doomed.end(), b->GetPairedBlock()) != doomed.end()) {
                            kept.push_back(BlockRef(b->GetPairedBlock()));
                            cost = b->GetCost();
                        }
                    } else {
                        cost = b->GetCost();
                    }
                } else {
                    cost = b->GetCost();
                }
                totalCost += cost;
                deletedAny = true;
                if (b->GetSymmetricBlock())
                    kept.push_back(BlockRef(b->GetSymmetricBlock()));

                BoundingBox bbox = b->GetBBox(0, 0, 0);
                cSPVector3 diagonal = bbox.mMax - bbox.mMin;
                float size = VectorLength(diagonal);
                centerSum += size * bbox.GetCenter();
                sizeSum += size;
            }
            uint32_t messageId = 0x7f18f481;
            MessageParam params[1];
            params[0].p = b;
            MessageServer()->SendMessage(messageId, params, 0);
            MessageManager()->RemoveListener(b);
            model.mpObject->RemoveBlock(b, false);
        }

        if (deletedAny) {
            cSPVector3 center = centerSum / sizeSum;
            MessageParam params[4];
            int unused = 0;
            params[0].i = totalCost;
            params[1].f = center[0];
            params[2].f = center[1];
            params[3].f = center[2];
            MessageServer()->SendMessage(0xf058b0f2, params, 0);
        }
        model.mpObject->SetUsingSymmetry(usingSymmetry);
    }
}

}} // namespace SP::EditorUtils
