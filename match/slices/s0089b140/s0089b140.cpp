// Slice s0089b140 -- EA::Text Typesetter::find-or-append text style.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"

struct TextStyle;

bool TextStyleEqual(const TextStyle* a, const TextStyle* b);   // 0x008942a0

struct StyleVec {
    TextStyle** mpBegin;
    TextStyle** mpEnd;
    TextStyle** mpCapacity;
    void DoInsertValue(TextStyle** pos, TextStyle*& v);   // 0x00899480
};

struct Typesetter {
    char pad_000[0x384];
    StyleVec mTextStyleArray;   // +0x384
    TextStyle* F_0089b140(TextStyle* arg);
};

// @ 0x0089b140
TextStyle* Typesetter::F_0089b140(TextStyle* arg)
{
    StyleVec& v = mTextStyleArray;
    unsigned n = (unsigned)(v.mpEnd - v.mpBegin);
    for (unsigned i = 0; i < n; ++i) {
        if (v.mpBegin[i] && TextStyleEqual(arg, v.mpBegin[i]))
            return v.mpBegin[i];
    }
    if (v.mpEnd < v.mpCapacity) {
        TextStyle** slot = v.mpEnd++;
        if (slot) *slot = arg;
    } else {
        v.DoInsertValue(v.mpEnd, arg);
    }
    return mTextStyleArray.mpEnd[-1];
}
