// @ 0x0088e620
#include "game/types.h"
#include "EA/Text/FontServer.h"

// Only the links and the beginning of the value are used here; the external
// node builder owns allocation and the complete FaceSource copy.
struct FaceSourceNode {
    FaceSourceNode* mpNext;
    FaceSourceNode* mpPrev;
    EA::Text::FontServer::FaceSource mValue;
};

// The cursor the caller hands in (eastl::ListIterator): one node pointer, and the
// operators take the iterator itself by reference.
template <typename T>
struct ListIterator {
    T* mpNode;

    ListIterator() : mpNode(0) {}
    explicit ListIterator(T* pNode) : mpNode(pNode) {}

    ListIterator& operator++() {
        mpNode = (T*)mpNode->mpNext;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator saved(*this);
        mpNode = (T*)mpNode->mpNext;
        return saved;
    }

    bool operator==(const ListIterator& rhs) const { return mpNode == rhs.mpNode; }
    bool operator!=(const ListIterator& rhs) const { return mpNode != rhs.mpNode; }

    EA::Text::FontServer::FaceSource& operator*() const { return mpNode->mValue; }
    EA::Text::FontServer::FaceSource* operator->() const { return &mpNode->mValue; }
};

struct FaceSourceList {
    typedef ListIterator<FaceSourceNode> iterator;

    FaceSourceNode* DoCreateNode(const EA::Text::FontServer::FaceSource& value); // 0x0088e5a0
    void DoInsert(FaceSourceNode* position, iterator first, iterator last,
                  int integerTag);
};

// @ 0x0088e620
void FaceSourceList::DoInsert(FaceSourceNode* position, iterator first,
                              iterator last, int integerTag) {
    for (; first != last; ++first) {
        FaceSourceNode* node = DoCreateNode(*first);
        node->mpNext = position;
        node->mpPrev = position->mpPrev;
        position->mpPrev->mpNext = node;
        position->mpPrev = node;
    }
}
