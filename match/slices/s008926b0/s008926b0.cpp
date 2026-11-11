// Slice s008926b0: text-substitution pass over a UTF-16 string.
//
// Walk a UTF-16 string [begin, end) two bytes at a time and write each
// character's replacement (after the FEFF / bidi / soft-hyphen overrides) to
// the output every `step` characters.  The substitution table at +0x178 is an
// eastl::rbtree<int16_t, uint16_t>; its header (sentinel) is the member at
// +0x178 and the root node pointer sits at +0x180.  The table lookup is the
// end-iterator form of eastl::rbtree::find (the `found == header ? header :
// found` select after the walk).
//
// NOTE: this is incomplete.  The iteration and the special-character test are
// modelled here, but the retail loop body is the typesetter's own writer
// helper (0x00892c00), which is not reconstructed yet; the output pattern
// below is a placeholder for it.

#include "game/types.h"

typedef unsigned short u16;

// NOTE: the tree offsets are only an estimate (the padding below currently
// places the root at +0x194 where retail reads +0x180; the neighbours in the
// retail image disagree on this layout, so the spans are unverified).
struct SubNode
{
    SubNode* mpLeft;    // +0x0
    SubNode* mpRight;   // +0x4
    SubNode* mpParent;  // +0x8
    char     pad[8];
    u16      mnKey;     // +0x10
    u16      mnValue;   // +0x12
};

struct Typesetter
{
    char      pad[0x14];
    u16       mReplacement;  // +0x14
    char      pad2[0x160];
    SubNode   mHeader;       // rbtree header (mnKey/mnValue unused)
    SubNode*  mpRoot;        // rbtree mAnchor.mpNode
    int GetSubstitutedString(u16* dst, const u16* begin, const u16* end, bool useOverrides, int step);
};

static SubNode* FindSub(SubNode* root, SubNode* header, u16 ch)
{
    SubNode* found = header;
    SubNode* node = root;
    while (node)
    {
        if (node->mnKey < ch)
            node = node->mpRight;
        else
        {
            found = node;
            node = node->mpLeft;
        }
    }
    if (found != header && ch < found->mnKey)
        found = header;
    return found;
}

// @ 0x008926b0
int Typesetter::GetSubstitutedString(u16* dst, const u16* begin, const u16* end, bool useOverrides, int step)
{
    SubNode* header = &mHeader;
    u16* pos = dst;
    const u16* last = begin + (end - begin);
    for (const u16* it = begin; it < last; ++it)
    {
        u16 ch = *it;
        SubNode* n = FindSub(mpRoot, header, ch);
        if (n != header)
        {
            *pos = n->mnValue;
        }
        else
        {
            int cls = ch & 0xff80;
            bool special = false;
            if (cls == 0x2000)
                special = (u16)(ch - 0x200b) <= 4 || (u16)(ch - 0x202a) <= 4 || (u16)(ch - 0x2060) <= 3
                          || ch == 0x2028;
            if (!special)
                special = ch == 0xad || ch == 0x34f || ch == 0xfeff;
            if (special)
                *pos = 0xfffe;
            else if (useOverrides)
                *pos = mReplacement;
        }
        pos += step;
    }
    return (int)(pos - dst);
}
