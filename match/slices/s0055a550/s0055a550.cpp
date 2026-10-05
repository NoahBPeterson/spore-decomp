// Slice s0055a550: SP::Audio::cCityMusicSummarizer parameter tables / extraction.
// Unoptimized /Od module.
#include "types.h"

namespace SP {
namespace Audio {

// @ 0x0055A550
class cCityMusicSummarizer {
public:
    uint32_t GetParamId(uint32_t index);
    uint32_t GetParamType(uint32_t index);
    bool ExtractParameters(int a, void* b);   // @ 0x0055AA00 (partial)
};
uint32_t cCityMusicSummarizer::GetParamId(uint32_t index) {
    static const uint32_t s_table[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    if (index < 8)
        return s_table[index];
    return 0xffffffff;
}

// @ 0x0055A9D0
uint32_t cCityMusicSummarizer::GetParamType(uint32_t index) {
    static const uint32_t s_table[6] = { 0, 0, 0, 0, 0, 0 };
    if (index < 6)
        return s_table[index];
    return 0xffffffff;
}

// @ 0x0055A580 — partial
class c55a580 {
public:
    uint32_t pad[0x200];
    void sub();
};
void c55a580::sub() {
}

// @ 0x0055AA00 — partial (PDB candidate: SP::Audio::cCityMusicSummarizer::ExtractParameters)
bool cCityMusicSummarizer::ExtractParameters(int a, void* b) {
    return false;
}

}
}
