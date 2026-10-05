// slice s00579e20
// Editor destructor + effects-mask helpers, optimized module.
#include "types.h"

namespace SP {
class cAppModeEditorBase {
public:
    char pad[0x458];
    ~cAppModeEditorBase();                       // 0x579e20
    void AddTorsoToEffectsMask();                // 0x57a610
    void SendBehaviorMessage(void*);             // 0x57a710
    void GetMask(unsigned* out);                 // 0x57a960
    unsigned* GetDefaultMask(unsigned* out);     // 0x57a9e0
    int GetEditorSaveability();                  // 0x57aaa0
    void SomeSetup();                            // 0x57ac00
};
}

using SP::cAppModeEditorBase;

extern unsigned g_mec, g_mf0, g_mf4, g_mf8;      // 0x15da7ec..0x15da7f8

// @ 0x0057a960
void cAppModeEditorBase::GetMask(unsigned* out)
{
    int p = *(int*)((char*)this + 0x1cc);
    if (p != 0) {
        out[0] = *(unsigned*)((char*)p + 0x24) & ~g_mec;
        out[1] = *(unsigned*)((char*)p + 0x28) & ~g_mf0;
        out[2] = *(unsigned*)((char*)p + 0x2c) & ~g_mf4;
        out[3] = *(unsigned*)((char*)p + 0x30) & ~g_mf8;
    } else {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        out[3] = 0;
    }
}

// @ 0x0057a6d0 -- small MI object ctor (stub, see partial.txt)
struct CheatObject2 {
    CheatObject2();
};
CheatObject2::CheatObject2() {}

// ---------------------------------------------------------------------------
// Placeholders (see partial.txt)
// ---------------------------------------------------------------------------
cAppModeEditorBase::~cAppModeEditorBase() {}
void cAppModeEditorBase::AddTorsoToEffectsMask() {}
void cAppModeEditorBase::SendBehaviorMessage(void*) {}
unsigned* cAppModeEditorBase::GetDefaultMask(unsigned* out) { out[0]=out[1]=out[2]=out[3]=0; return out; }
int cAppModeEditorBase::GetEditorSaveability() { return 0; }
void cAppModeEditorBase::SomeSetup() {}
