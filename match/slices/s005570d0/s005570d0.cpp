// Slice s005570d0: SP/Simulator content-validation summarizer. Unoptimized /Od module.
#include "types.h"

namespace SP {

// @ 0x00558080
class cContentValidationSummarizer {
public:
    uint32_t GetResType(int arg);
};
uint32_t cContentValidationSummarizer::GetResType(int arg) {
    switch (arg) {
    case 0: return 0x3d97a8e4;
    case 1: return 0x2b978c46;
    case 2: return 0x2399be55;
    case 3: return 0x24682294;
    case 4: return 0x476a98c7;
    }
    return 0xffffffff;
}

namespace W1G2_57 {

// @ 0x00557C90
class c557c90 {
public:
    uint32_t GetResType(int arg);
};
uint32_t c557c90::GetResType(int arg) {
    switch (arg) {
    case 0: return 0x476a98c7;
    case 1: return 0x2399be55;
    case 2: return 0x2b978c46;
    case 3: return 0x24682294;
    }
    return 0xffffffff;
}

// @ 0x005570D0 — partial: large content-validation summarizer routine.
class c570d0 {
public:
    uint32_t pad[0x200];
    void sub(int a, int b);   // @ 0x005570D0
};
void c570d0::sub(int a, int b) {
}

// @ 0x00557CF0 — partial.
class c57cf0 {
public:
    uint32_t pad[0x200];
    void sub(int a, int b);   // @ 0x00557CF0
};
void c57cf0::sub(int a, int b) {
}

// @ 0x00557FC0 — partial: constructor stores vtable pointers (MI hierarchy).
class c57fc0 {
public:
    c57fc0();
    uint32_t mField;
};
c57fc0::c57fc0() {
    mField = 0;
}

}
}
