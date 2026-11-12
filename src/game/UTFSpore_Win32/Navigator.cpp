// src/game/UTFSpore_Win32/Navigator.cpp -- migrated from slice(s) s0097f390 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Navigator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

// ---- items of slice s0097f390 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
namespace EA {
namespace UTFWinControls {
struct IObj;
}
}
namespace EA {
namespace UTFWinControls {
struct IObjNoArg {
    VP VP VP VP                                       // 0x00..0x0c
    virtual IObj* self10();
    virtual IObj* v14();                               // 0x14 (slot 5, no argument)
};
}
}
namespace EA {
namespace UTFWinControls {
struct IObjArg {
    VP VP VP VP                                       // 0x00..0x0c
    virtual void* self10();
    virtual void* v14(int x);                          // 0x14 (slot 5, one argument)
};
}
}
namespace EA {
namespace UTFWinControls {
struct IObj {
    VP VP VP VP                                       // 0x00..0x0c
    virtual IObj* v10();                               // 0x10
    virtual IObj* v14(int x = 0);                      // 0x14
    VP4 VP4 VP4                                       // 0x18..0x44
    virtual IObj* v48(int x);                          // 0x48
    VP4 VP4 VP4 VP4 VP VP VP                          // 0x4c..0x94
    virtual void  v98();                               // 0x98
};
}
}
namespace EA {
namespace UTFWinControls {
struct Arg2;
}
}
namespace EA {
namespace UTFWinControls {
struct IOwner {
    VP VP VP VP VP                                    // 0x00..0x10
    virtual int  v14();                                // 0x14
    VP4 VP4 VP4 VP4 VP4 VP4                           // 0x18..0x78
    VP VP                                             // 0x7c
    virtual void v80(void* p);                         // 0x80 (slot 32)
    char pad04[0xc];                                   // +0x04..0x0f
    int  m10;                                          // +0x10
    int  m14;                                          // +0x14
    bool Process(IObj* arg1, Arg2* arg2);
    bool Process2(IObj* arg1, Arg2* arg2);
};
}
}
namespace EA {
namespace UTFWinControls {
struct Navigator {
    void* m00;
    void* volatile m04;
    void* m08;
    void* volatile m0c;
    Navigator();
    ~Navigator();
};
}
}
namespace EA {
namespace UTFWinControls {
struct ExplicitNavigator : Navigator {
    void* m10;
    void* m14;
    ExplicitNavigator();
};
}
}
namespace EA {
namespace UTFWinControls {
struct Arg2 {
    char  pad0[8];
    int   m08;                     // +0x08
    int   m0c;                     // +0x0c
    int   m10;                     // +0x10
    int   m14;                     // +0x14
    void* m18;                     // +0x18
};
}
}
namespace EA {
namespace UTFWinControls {
Navigator::Navigator()
{
    m04 = (void*)0x13fa72c;
    // Finish installing the base interface before materializing its null state.
    _ReadWriteBarrier();
    m08 = 0;
    m0c = (void*)0x1444434;
}
}
}
// ---- items of slice s0097f390 end

// @ 0x00980360
namespace EA { namespace UTFWinControls {
bool IOwner::Process(IObj* arg1, Arg2* arg2)
{
    switch (arg2->m08) {
    case 1:
        if (arg2->m10 == m10) {
            IObj* r = ((IObjNoArg*)arg1)->v14()->v48(0);
            switch (m14) {
            case 1:
                if (r != arg1)
                    return false;
                break;
            case 2:
                if (r) {
                    if (r->v10() != arg1)
                        return false;
                }
                break;
            case 3:
                if (r == arg1)
                    return false;
                break;
            }
            v80(((IObjArg*)arg1)->v14(0));
        }
        break;
    }
    return false;
}
}}  // namespace EA::UTFWinControls

// @ 0x00980420
namespace EA { namespace UTFWinControls {
Navigator::~Navigator()
{
    m0c = (void*)0x13eb938;
    m04 = (void*)0x13eb938;
    m00 = (void*)0x13eb938;
}
}}  // namespace EA::UTFWinControls

// @ 0x00980430
namespace EA { namespace UTFWinControls {
ExplicitNavigator::ExplicitNavigator()
{
    m00 = (void*)0x1443f78;
    m04 = (void*)0x1443f5c;
    m0c = (void*)0x1443f38;
    m10 = 0;
    m14 = 0;
}
}}  // namespace EA::UTFWinControls
