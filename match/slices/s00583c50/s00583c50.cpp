// slice s00583c50 -- SP::cAppModeEditorBase animation-capture helpers and the eastl vector /
// rbtree support code they instantiate.  Retail class layout differs from the 2008 PDB; offsets
// are taken from the disassembly.  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

void __cdecl operator delete[](void* p);                                        // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);

struct cPropList {
    int GetIntProperty(uint32_t id);                                            // 0x006a2660
};
extern cPropList* g_AppProperties;                                              // 0x015fd918

// ---- eastl::vector with an sp_vector_allocator (3 pointers + empty allocator): 0x14 bytes ------
template <class T>
struct SPVector {
    T* mpBegin;                 // +0x00
    T* mpEnd;                   // +0x04
    T* mpCapacity;              // +0x08
    char mAllocator[8];         // +0x0c

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    __forceinline T* erase(T* position)
    {
        T* last = position + 1;
        if (last < mpEnd)
            memcpy(position, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd -= 1;
        return position;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValueI(mpEnd, value);
    }
    void DoInsertValueI(T* position, const T& value);
};

struct sp_byte_vector : SPVector<uint8_t> {
    void reserve(uint32_t n);                                                   // 0x0057cc60
};

// ---- plain int vector used by the editor (same three pointers) --------------------------------
struct cIntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    void Resize(uint32_t n);
    int* Insert(int* at, uint32_t count, const int* value);                     // @ 0x0057f220
    int* Erase(int* first, int* last);                                          // @ 0x005c2170
};

// ---- small math types ------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
inline Vector3 operator+(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline Vector3 operator*(const Vector3& v, float s)
{
    return Vector3(v.x * s, v.y * s, v.z * s);
}

struct Box24 {                      // 24-byte box: two Vector3
    Vector3 mMin;
    Vector3 mMax;
};

extern const float kHalf;                                                       // 0x01471064

// ---- eastl::bitset<64> -----------------------------------------------------------------------
template <int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bitset() { reset(); }
    void reset()
    {
        for (int i = 0; i < (N + 31) / 32; ++i)
            mWord[i] = 0;
    }
    void set(uint32_t i)
    {
        if (i < (uint32_t)N)
            mWord[i >> 5] |= ((uint32_t)1 << (i & 31));
    }
};

// ---- model-world interfaces (only the vtable slots these helpers touch) ----------------------
#define PV(n) virtual void _pv##n();
#define PV4(n) PV(n##0) PV(n##1) PV(n##2) PV(n##3)
#define PV16(n) PV4(n##0) PV4(n##1) PV4(n##2) PV4(n##3)

struct cILightingWorld {
    virtual int AddRef();
    virtual int Release();
};

struct cIModelWorld {
    PV(0) PV(1)
    PV16(0) PV16(1) PV16(2) PV16(3)                  // slots 2..65
    PV4(40) PV(410)                                  // slots 66..70
    virtual void SetModelGroups(bitset<64>* include, bitset<64>* exclude, int flags);   // +0x11c
    PV4(44) PV4(45)                                  // slots 72..79
    virtual void SetLightingWorld(void* lighting);                                       // +0x140
    virtual void* CreateLightingWorld(int a, int b, int c);                              // +0x144
};

struct cIModelManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual uint32_t GetGroupIndex(uint32_t id, int a);                                  // +0x28
};

struct cViewer;

struct cSPEditorModel {
    Box24 GetBoundingBox(bool selectableOnly);                                    // 0x004ad550
    void GetBlockBoundingBoxes(SPVector<Box24>& boxes);                          // 0x004ad6f0
};

struct BoxVector : SPVector<Box24> {
    BoxVector()
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
    }
    ~BoxVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator delete[](mpBegin);
    }
};

struct IThumbnailService {                                                       // 0x0067ddb0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void BeginCapture(cIModelWorld* world, cViewer* viewer, uint32_t index,
                              int count, uint32_t id);                           // +0x30
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void CaptureBoxes(BoxVector* boxes, cViewer* viewer, uint32_t id,
                              const Vector3* center, float inset, float height); // +0x50
};

cIModelManager* ModelManager();                                                  // 0x0067dd80
IThumbnailService* ThumbnailService();                                           // 0x0067ddb0

// ---------------------------------------------------------------------------------------------
// The editor object, only the fields these helpers touch.
class cAppModeEditorBase {
public:
    char pad000[0x84];
    cIModelWorld* mModelWorld;          // +0x84
    char pad088[0x98 - 0x88];
    cSPEditorModel* mpEditorSaveModel;  // +0x98 (cSPEditorModel)
    char pad09c[0x2b8 - 0x9c];
    float mScale;                       // +0x2b8
    char pad2bc[0x2f1 - 0x2bc];
    bool mPaintedSkinSave;              // +0x2f1
    char pad2f2[0x31c - 0x2f2];
    int mAnimCaptureState;              // +0x31c
    char pad320[0x3dc - 0x320];
    cViewer* mpCaptureViewer;           // +0x3dc
    char pad3e0[0x3f0 - 0x3e0];
    uint32_t mCaptureFrame;             // +0x3f0
    uint32_t mCaptureBase;              // +0x3f4
    uint32_t mCaptureSaved;             // +0x3f8
    uint32_t mCaptureTotal;             // +0x3fc
    uint32_t mCaptureGroup;             // +0x400
    uint32_t mCaptureStride;            // +0x404
    SPVector<uint32_t> mFrameOrder;    // +0x408
    SPVector<uint32_t> mPendingFrames; // +0x41c
    bool mCaptureBusy;                  // +0x430

    void FUN_00584070();
    void SetAnimCaptureOn(uint32_t on);
};

// @ 0x00584070
void cAppModeEditorBase::FUN_00584070()
{
    mCaptureFrame = 0;
    mCaptureSaved = 0;
    int n = g_AppProperties->GetIntProperty(0x5893ee8);
    mCaptureTotal = n * n;
    mCaptureGroup = 0;
    mCaptureStride = 1;
    mFrameOrder.clear();
    mPendingFrames.clear();
    mCaptureBase = 0;
    for (uint32_t i = 0; i < mCaptureTotal; ++i)
        mFrameOrder.push_back(i);
}

// @ 0x00584160
void cIntVec::Resize(uint32_t n)
{
    int* begin = mpBegin;
    int* end = mpEnd;
    uint32_t cur = (uint32_t)(end - begin);
    if (n > cur) {
        int zero = 0;
        Insert(end, n - cur, &zero);
        return;
    }
    Erase(begin + n, end);
}

// @ 0x00583c50
// cAppModeEditorBase::SetAnimCaptureOn -- walk the frame-ordering state machine one step, rebuild
// the model-group include set, capture the editor model's boxes into a thumbnail and kick off the
// capture service.
void cAppModeEditorBase::SetAnimCaptureOn(uint32_t on)
{
    if (mCaptureBusy)
        return;

    uint32_t frame = mCaptureFrame;
    bool aligned = ((frame - mCaptureBase) == mCaptureStride) || frame == 0;

    if (aligned || (char)on) {
        uint32_t index;
        if ((char)on && mCaptureGroup > 0) {
            index = mCaptureSaved;
        } else {
            if (mCaptureGroup > 0) {
                uint32_t cur = *mPendingFrames.mpBegin;
                mCaptureSaved = cur;
                mPendingFrames.erase(mPendingFrames.mpBegin);
                uint32_t value = mFrameOrder.mpBegin[cur] + 1;
                uint32_t j = on;
                while (value < mFrameOrder.size()) {
                    for (uint32_t k = 0; k < mFrameOrder.size(); ++k) {
                        if (mFrameOrder.mpBegin[k] == value) {
                            j = k;
                            break;
                        }
                    }
                    --mFrameOrder.mpBegin[j];
                    ++value;
                }
                mFrameOrder.mpBegin[cur] = 0x23;
                index = cur;
            } else {
                index = mCaptureFrame;
            }
        }

        if (!(char)on)
            mCaptureBase = mCaptureFrame;

        cIModelManager* mgr = ModelManager();
        bitset<64> include;
        bitset<64> exclude;
        if (mPaintedSkinSave && mAnimCaptureState == 1) {
            include.set(mgr->GetGroupIndex(0x509991e7, 0));
        } else {
            include.set(mgr->GetGroupIndex(0x9138fd8d, 0));
            include.set(mgr->GetGroupIndex(0x4fe3913, 0));
            include.set(mgr->GetGroupIndex(0xfeb8df2, 0));
        }
        mModelWorld->SetModelGroups(&include, &exclude, 4);
        mModelWorld->SetLightingWorld(mModelWorld->CreateLightingWorld(0, 4, 1));

        Box24 box = mpEditorSaveModel->GetBoundingBox(false);
        BoxVector boxes;
        mpEditorSaveModel->GetBlockBoundingBoxes(boxes);

        IThumbnailService* svc = ThumbnailService();
        Vector3 center = (box.mMax + box.mMin) * kHalf;

        svc->CaptureBoxes(&boxes, mpCaptureViewer, 0x6406f717, &center, mScale, 0.0f);
        mCaptureBusy = true;
        ThumbnailService()->BeginCapture(mModelWorld, mpCaptureViewer, index, 4, 0x62628f0);
    }

    ++mCaptureFrame;
    if (mCaptureTotal < mCaptureFrame) {
        for (uint32_t i = 1; i < mFrameOrder.size(); i += 2) {
            for (uint32_t j = 0; j < mFrameOrder.size(); ++j) {
                if (mFrameOrder.mpBegin[j] == i) {
                    mPendingFrames.push_back(j);
                    break;
                }
            }
        }
        mCaptureGroup = mCaptureTotal;
        mCaptureTotal *= 2;
        mCaptureStride *= 2;
    }
}

// ---------------------------------------------------------------------------------------------
// The save stream reader side: reads a frame count, reserves it in an argument vector, then reads
// that many flags into it.
struct cFrameReader {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* GetStream();                  // +0x20
};
struct cSaveStream {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void* GetIO();                      // +0x18
};
bool __cdecl ReadInt32(void* io, uint32_t* out, int count, int endian);         // 0x0093a780
bool __cdecl ReadBool(void* io, uint8_t* out);                                  // 0x0093ac80

// @ 0x00584230
void FUN_00584230(cFrameReader* reader, sp_byte_vector* flags)
{
    flags->clear();

    uint32_t count = 0;
    void* io = (void*)((cSaveStream*)reader->GetStream())->GetIO();
    ReadInt32(io, &count, 1, 0);
    flags->reserve(count);

    for (uint32_t i = 0; i < count; ++i) {
        uint8_t flag;
        ReadBool((void*)((cSaveStream*)reader->GetStream())->GetIO(), &flag);
        flags->push_back(flag);
    }
    reader->v1c();
}

// ---------------------------------------------------------------------------------------------
// eastl::rbtree<unsigned int, eastl::pair<unsigned int const, bool>, ...> as laid out in this
// build: a 4-byte comparator, the anchor node at +4 (root at anchor.mpNodeParent = +0xc), the
// element count at +0x14 and the empty allocator at +0x18.
struct RBNodeBase {
    RBNodeBase* mpNodeRight;    // +0
    RBNodeBase* mpNodeLeft;     // +4
    RBNodeBase* mpNodeParent;   // +8
    char mColor;                // +0xc
};

struct PairU32Bool {
    const uint32_t first;       // +0
    bool second;                // +4
    PairU32Bool(const uint32_t& k, bool v) : first(k), second(v) {}
};

struct NodeU32Bool : RBNodeBase {
    PairU32Bool mValue;         // +0x10
};

struct IteratorU32Bool {
    NodeU32Bool* mpNode;
    IteratorU32Bool(NodeU32Bool* p) : mpNode(p) {}
};

struct PairIteratorBool {
    IteratorU32Bool first;
    bool second;
};

struct true_type {};

struct RBTreeU32Bool {
    uint32_t mCompare;          // +0
    RBNodeBase mAnchor;         // +4
    uint32_t mnSize;            // +0x14
    char mAllocator[8];         // +0x18
    PairIteratorBool DoInsertValue(IteratorU32Bool position, const PairU32Bool& value, true_type tag);   // @ 0x006432d0
    bool& FindOrAdd(const uint32_t& key);
};

// @ 0x005841b0
bool& RBTreeU32Bool::FindOrAdd(const uint32_t& key)
{
    NodeU32Bool* node = (NodeU32Bool*)mAnchor.mpNodeParent;
    NodeU32Bool* hint = (NodeU32Bool*)&mAnchor;
    while (node != 0) {
        if (!(node->mValue.first < key)) {
            hint = node;
            node = (NodeU32Bool*)node->mpNodeLeft;
        } else {
            node = (NodeU32Bool*)node->mpNodeRight;
        }
    }
    if (hint == (NodeU32Bool*)&mAnchor || key < hint->mValue.first) {
        PairIteratorBool result = DoInsertValue(IteratorU32Bool(hint), PairU32Bool(key, false), true_type());
        return result.first.mpNode->mValue.second;
    }
    return hint->mValue.second;
}
