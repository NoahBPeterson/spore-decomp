// slice s0089b250 - EA::Text::Typesetter::AddLineBreak.
//
//   0x0089b250  Typesetter::AddLineBreak(const wchar_t* s, unsigned n, bool a, bool b)
//
// Appends one 0x2c-byte record to the item vector at +0x3d0 (push_back default,
// then filled in place through the fresh end pointer) and advances the running
// length bookkeeping the typesetter keeps at +0x408/+0x40c.  The two trailing
// flags are normalised into the word count at +0x08 and kept raw in the two
// one-byte tails.
//
// Flags: /O2 /MD /Gy /GS- /GR- /TP
#include "types.h"
#include <string.h>

struct ICoreAllocator {
    virtual void  Slot0();
    virtual void  Slot4();
    virtual void* Alloc(unsigned int size, unsigned int alignment, unsigned int flags);
    virtual void  Free(void* p, unsigned int size);
};

namespace EA {
namespace Text {

struct LongRect {                                  // 0x14 bytes, copied into the record
    int mLeft;                                     // +0x00
    int mTop;                                      // +0x04
    int mRight;                                    // +0x08
    int mBottom;                                   // +0x0c
    int mExtra;                                    // +0x10
};

struct TypesetterItem {                            // 0x2c bytes
    unsigned    mKind;                             // +0x00
    unsigned    mLength;                           // +0x04
    unsigned    mCount;                            // +0x08
    unsigned    mFlags;                            // +0x0c
    const wchar_t* mpString;                       // +0x10
    LongRect    mRect;                             // +0x14
    unsigned char mBreakBefore;                    // +0x28
    unsigned char mBreakAfter;                     // +0x29
    unsigned char mPad[2];                         // +0x2a
};

struct ItemVec {
    TypesetterItem* mpBegin;                       // +0x00
    TypesetterItem* mpEnd;                         // +0x04
    TypesetterItem* mpCapacity;                    // +0x08
    ICoreAllocator* mpAllocator;                   // +0x0c
    unsigned int    mFlags;                        // +0x10

    void DoInsertValue(TypesetterItem* position, const TypesetterItem& value);   // 0x00899590
    void PushBackDefault();                                                    // 0x0089a5d0
};

struct TripleFloat {                               // base, 0x0c bytes
    float mX, mY, mZ;
};

class Typesetter : public TripleFloat {
public:
    char mState[0x3bc - 0x0c];                     // +0x0c
    unsigned mField3bc;                            // +0x3bc
    char mPad[0x3d0 - 0x3c0];                      // +0x3c0
    ItemVec mItems;                                // +0x3d0
    char mPad2[0x408 - 0x3e4];                     // +0x3e4
    unsigned mnItems;                              // +0x408
    unsigned mnLength;                             // +0x40c
    char mPad3[0x414 - 0x410];                     // +0x410
    unsigned mType;                                // +0x414

    void AddLineBreak(const wchar_t* s, unsigned n, bool a, bool b);   // 0x0089b250
};

}}   // namespace EA::Text

// @ 0x0089b250
void EA::Text::Typesetter::AddLineBreak(const wchar_t* s, unsigned n, bool a, bool b)
{
    mItems.PushBackDefault();

    TypesetterItem* pItem = mItems.mpEnd - 1;
    pItem->mKind = 1;
    pItem->mLength = mnLength;
    pItem->mCount = a + b + 1;
    pItem->mFlags = mField3bc;
    pItem->mpString = s;
    pItem->mRect = *(const LongRect*)&n;
    pItem->mBreakBefore = a;
    pItem->mBreakAfter = b;

    mnItems = mnItems + 1;
    mnLength = mnLength + pItem->mCount;
    if (mType == 2)
        mType = 0;
}
