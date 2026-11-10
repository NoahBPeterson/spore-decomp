// Slice s00887510: EA::Text::RPathString16::operator+=(Char) -- the one-character append
// wrapper around the shared growable 16-bit string's push-back (0x00930ed0).  The method is
// spelled `Append` here because the marker matcher cannot bind a mangled `operator+=`.
// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE
#include "types.h"

struct RPathString16 {
    void push_back(unsigned short ch);          // 0x00930ed0
    RPathString16& Append(unsigned int c);
};

// @ 0x00887510
RPathString16& RPathString16::Append(unsigned int c) {
    push_back((unsigned short)c);
    return *this;
}
