// slice s00598340 -- SP::cCollectableItems helpers: rbtree insert/lower_bound, pool-backed ctor,
// editor base-unlock computation and collectable-item metadata.  All large; skeletons only.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace SP {

class cCollectableItems {
public:
    char pad0[0x4d00 + 0x100];
    void EnsureBaseUnlocksForEditor();                                        // 0x00598540
    void AddCollectableItemInfo(int a, int b, int c, int d, int e, int f, int g); // 0x00598e90
    void FUN_00598340(void* a, void* b, void* c);                             // 0x00598340
    int  FUN_00598470(int a, int b);                                          // 0x00598470
    void* FUN_00598b50(void* a, void* b, void* c, void* d);                   // 0x00598b50
    int  FUN_00598cb0(void* a);                                               // 0x00598cb0
    void FUN_00598db0(int a, int b, int c, int d, int e, int f, int g, int h, int i); // 0x00598db0
};

}  // namespace SP

using namespace SP;

// @ 0x00598340 PARTIAL: EASTL rbtree lower_bound+insert; skeleton only.
void cCollectableItems::FUN_00598340(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }

// @ 0x00598470 PARTIAL: pool-backed construct; skeleton returns this.
int cCollectableItems::FUN_00598470(int a, int b) { (void)b; return (int)(size_t)this; }

// @ 0x00598540 PARTIAL: 1547 B editor base-unlock computation; skeleton only.
void cCollectableItems::EnsureBaseUnlocksForEditor() {}

// @ 0x00598b50 PARTIAL: rbtree node plumbing; skeleton returns 0.
void* cCollectableItems::FUN_00598b50(void* a, void* b, void* c, void* d) { (void)a; (void)b; (void)c; (void)d; return 0; }

// @ 0x00598cb0 PARTIAL: rbtree emplace; skeleton returns 0.
int cCollectableItems::FUN_00598cb0(void* a) { (void)a; return 0; }

// @ 0x00598db0 PARTIAL: 220 B metadata append; skeleton only.
void cCollectableItems::FUN_00598db0(int a, int b, int c, int d, int e, int f, int g, int h, int i) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; }

// @ 0x00598e90 PARTIAL: AddCollectableItemInfo 418 B; skeleton only.
void cCollectableItems::AddCollectableItemInfo(int a, int b, int c, int d, int e, int f, int g) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; }
