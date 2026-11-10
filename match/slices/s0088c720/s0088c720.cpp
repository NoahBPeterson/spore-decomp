// 0x0088c720 -- general-allocator lookup: find the block whose character buffer
// equals `view`.
//
// Walk the allocation-header chain (headers are linked through +0x4cc and hold
// their buffer's (begin, end) view at +0), comparing every candidate with
// 0x0087d9a0 (`LocViewEqual`, a wide-string equality on two (begin, end) pairs)
// and return the first match, else null.  Retail cleans 0xc stack bytes, so the
// helper takes three arguments; the third is the caller's implicit one and is
// never read.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE.

#include "types.h"

// string view: begin/end of the wchar_t data (see 0x0087d9a0)
struct LocView {
    wchar_t* mpBegin;               // +0x00
    wchar_t* mpEnd;                 // +0x04
};

// 0x0087d9a0: 1 when both views hold the same characters
bool LocViewEqual(const LocView* a, const LocView* b);

struct AllocHeader {
    LocView mView;                  // +0x00  the block's character buffer, if it holds text
    char    mPad[0x4cc - 0x08];     // +0x08
    AllocHeader* mpNext;            // +0x4cc  next allocation header in the list
};

// @ 0x0088c720
AllocHeader* __stdcall FindCharsBlock(AllocHeader* head, const LocView* view, int unused)
{
    (void)unused;
    AllocHeader* p = head;
    if (p != 0) {
        do {
            if (LocViewEqual(view, &p->mView))
                return p;
            p = p->mpNext;
        } while (p != 0);
    }
    return 0;
}
