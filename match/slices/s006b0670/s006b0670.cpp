// Slice s006b0670: three more instances of the hole-table rbtree's unique insert
// (eastl::rbtree::DoInsertValue(value, true_type), keyed by a 64-bit offset); the same code as
// HoleTree::DoInsertValue 0x006bf2c0 (slice s006bede0), each tree with its own DoInsertValueImpl.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

typedef unsigned int uint32;
typedef unsigned __int64 uint64;

struct HoleValue {
    uint64 mOffset;   // +0x00 (sorted key)
    uint32 mA;        // +0x08
    uint32 mB;        // +0x0c
};

struct HoleNodeBase {
    HoleNodeBase* mpNodeRight;   // +0x00
    HoleNodeBase* mpNodeLeft;    // +0x04
    HoleNodeBase* mpNodeParent;  // +0x08
    unsigned char mColor;        // +0x0c
};

struct HoleNode : HoleNodeBase {
    HoleValue mValue;            // +0x10
};

struct HoleIter {
    HoleNode* mpNode;
    HoleIter() : mpNode(0) {}
    HoleIter(HoleNode* p) : mpNode(p) {}
};

struct HolePairIB {
    HoleIter first;
    bool     second;
    HolePairIB(const HoleIter& f, bool s) : first(f), second(s) {}
};

struct true_type {};

void* __cdecl RBTreeDecrement(const void* pNode);  // 0x009215c0

// Owner tags: which tree the instance belongs to.
struct ResourceCacheTree;   // DoInsertValueImpl 0x006b04a0
struct CreatureAnimTree;    // DoInsertValueImpl 0x00a08b00
struct CreatureModeTree;    // DoInsertValueImpl 0x00d3b880

template <typename Owner>
struct HoleTreeT {
    int          mCompare;      // +0x00
    HoleNodeBase mAnchor;       // +0x04
    uint32       mnSize;        // +0x14
    void*        mAllocator;    // +0x18

    HoleIter DoInsertValueImpl(HoleNodeBase* pNodeParent, const HoleValue& value, bool bForceToLeft);
    HolePairIB DoInsertValue(const HoleValue& value, true_type);
};

template <typename Owner>
HolePairIB HoleTreeT<Owner>::DoInsertValue(const HoleValue& value, true_type)
{
    HoleNode* pCurrent    = (HoleNode*)mAnchor.mpNodeParent;
    HoleNode* pLowerBound = (HoleNode*)&mAnchor;
    HoleNode* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = (value.mOffset < pCurrent->mValue.mOffset);
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (HoleNode*)pCurrent->mpNodeLeft;
        else
            pCurrent = (HoleNode*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (HoleNode*)mAnchor.mpNodeLeft) {
            pLowerBound = (HoleNode*)RBTreeDecrement(pLowerBound);
        } else {
            const HoleIter itResult(DoInsertValueImpl(pLowerBound, value, false));
            return HolePairIB(itResult, true);
        }
    }

    if (pLowerBound->mValue.mOffset < value.mOffset) {
        const HoleIter itResult(DoInsertValueImpl(pParent, value, false));
        return HolePairIB(itResult, true);
    }

    return HolePairIB(HoleIter(pLowerBound), false);
}

// 0x006b0670, 0x00a09420, 0x00d3bcc0 (manifest rows name each instance)
template struct HoleTreeT<ResourceCacheTree>;
template struct HoleTreeT<CreatureAnimTree>;
template struct HoleTreeT<CreatureModeTree>;
