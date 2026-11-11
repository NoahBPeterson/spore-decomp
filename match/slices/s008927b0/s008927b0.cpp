// Slice s008927b0: EA::Text font IsCharSupported (retail layout variant).
//
// Same upstream EAText logic as RBmpFont::IsCharSupported (0x00886100), but the
// character map is an eastl::rbtree<uint16_t> at +0x174 and the supported-script
// bitset is at +0x18.  The retail build of this variant lowers the script test to
// a jump table, so it is written as a switch.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast
#include "types.h"

struct CharIterator {
    void* mpNode;
    bool operator!=(const CharIterator& o) const { return mpNode != o.mpNode; }
};

// eastl::rbtree<uint16_t> stand-in: sentinel at +0x04, root at +0x0c.
class CharMap {
public:
    char    pad0[4];
    void*   mEnd;      // +0x04  (sentinel node)
    char    pad8[4];
    void*   mRoot;     // +0x0c
    CharIterator find(const uint16_t& key);   // 0x005e90a0, thiscall, sret, ret 8
    CharIterator end() { CharIterator it; it.mpNode = &mEnd; return it; }
};

struct Bitset64 {
    uint32_t mWord[2];
    bool test(unsigned i) const {
        if (i < 0x40)
            return (mWord[i >> 5] & (1u << (i & 0x1f))) != 0;
        return false;
    }
};

class CQuery {
public:
    char     pad0[0x18];
    Bitset64 mSupportedScriptSet;   // +0x18
    char     pad20[0x174 - 0x20];
    CharMap  mCharMap;              // +0x174
    bool IsCharSupported(uint16_t c, int script);
};

// @ 0x008927b0
bool CQuery::IsCharSupported(uint16_t c, int script)
{
    if (c < 0x0080)
        return true;
    switch (script) {
        case -1:
            if (c == 0xffff)
                return true;
            // fall through
        case 0:
        case 0x15:
        case 0x1e:
            return mCharMap.find(c) != mCharMap.end();
        default:
            return mSupportedScriptSet.test(script);
    }
}
