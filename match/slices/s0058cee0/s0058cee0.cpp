// slice s0058cee0 -- SP::cAppModeEditorBase::LoadModel / NewModel.  Moderately large; skeletons.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
namespace SP {
class cAppModeEditorBase {
public:
    char pad0[0x600];
    int LoadModel(int a, int b, int c, int d, int e, int f);   // 0x0058cee0
    void NewModel(char a);                                     // 0x0058d1c0
};
}
using namespace SP;
// @ 0x0058cee0 PARTIAL: 722 B LoadModel; skeleton returns 0.
int cAppModeEditorBase::LoadModel(int a, int b, int c, int d, int e, int f) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; return 0; }
// @ 0x0058d1c0 PARTIAL: 613 B NewModel; skeleton only.
void cAppModeEditorBase::NewModel(char a) { (void)a; }
