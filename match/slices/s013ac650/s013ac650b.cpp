// Unoptimized (/Od /Ob1) functions of slice s013ac650: global virtual cleanups and rbtree destructors.

#include "game/types.h"
#include "cSPUILayout.h"

// ---- virtual cleanups
// The existing initializer at 0x01226f30 owns this global and registers the
// cleanup below. Keep the release in the global holder's inline boundary.
template <class T> class AutoRefCount {
public:
    T* mpObject;
    void ReleaseForDestruction() {
        if (mpObject)
            mpObject->Release();
    }
};
extern AutoRefCount<cSPUILayout> g_layout; // 0x015d2dbc
// @ 0x013BCA50
void FUN_013bca50() { g_layout.ReleaseForDestruction(); }

struct VI { virtual void s0(); virtual void s1(); virtual void s2(); };
extern VI* g_015de138;
// @ 0x013BCD30
void FUN_013bcd30() { if (g_015de138) g_015de138->s1(); }

// ---- rbtree global destructors
struct RBTree { void DoNuke(void*); };
extern RBTree g_015da960, g_015da884;
extern void *g_015da96c, *g_015da890;
// @ 0x013BCC50
void FUN_013bcc50() { g_015da960.DoNuke(g_015da96c); }
// @ 0x013BCC70
void FUN_013bcc70() { g_015da884.DoNuke(g_015da890); }
