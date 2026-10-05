// Slice s005567e0: SP model-summarizer resource setup. Unoptimized /Od module.
#include "types.h"

namespace SP {

// @ 0x00556E10
class cBuildingModelSummarizer {
public:
    uint32_t GetResType(int arg);
};
uint32_t cBuildingModelSummarizer::GetResType(int arg) {
    if (arg == 0)
        return 0x2399be55;
    return 0xffffffff;
}

namespace W1G2_56 {

// @ 0x005567E0 — partial: builds the vehicle summarizer's FunctionalMatch params
// (GetManager, SP::FunctionalMatch::DeclareParam, string/resource setup).
class c567e0 {
public:
    uint32_t pad[0x80];
    void sub(int a, int b);   // @ 0x005567E0
};
void c567e0::sub(int a, int b) {
}

// @ 0x00556E30 — partial: building summarizer parameter setup.
class c56e30 {
public:
    uint32_t pad[0x80];
    void sub(int a, int b);   // @ 0x00556E30
};
void c56e30::sub(int a, int b) {
}

}
}
