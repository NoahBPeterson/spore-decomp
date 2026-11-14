// src/game/UTFSpore_Win32/Navigator.cpp
// Object file: UTFSpore_Win32/Navigator.obj.

#include "game/types.h"
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)

// Interface classes with the vtable layout the original calls through.
//
// The constructor and destructor write interface/vtable pointers into their
// members.  Those addresses are named after the interface they identify; the
// names are guesses from usage, the values are exact.
enum {
    kNavigatorBaseVtbl   = 0x013fa72c,  // Navigator +0x04 while constructing
    kNavigatorVtbl       = 0x01444434,  // Navigator +0x0c while constructing
    kNavigatorDtorVtbl   = 0x013eb938,  // all members once destroyed
    kExplicitNavSelfVtbl = 0x01443f78,  // ExplicitNavigator +0x00
    kExplicitNavVtbl04   = 0x01443f5c,  // ExplicitNavigator +0x04
    kExplicitNavVtbl0c   = 0x01443f38,  // ExplicitNavigator +0x0c
};
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP

namespace EA {
namespace UTFWinControls {

struct IObj;

// arg1 seen only as the interface that returns an IObj* from slot 5.
struct IObjNoArg {
    VP VP VP VP                                        // 0x00..0x0c
    virtual IObj* self10();
    virtual IObj* v14();                               // 0x14 (slot 5, no argument)
};

// arg1 seen only as the interface that takes one argument at slot 5.
struct IObjArg {
    VP VP VP VP                                        // 0x00..0x0c
    virtual void* self10();
    virtual void* v14(int x);                          // 0x14 (slot 5, one argument)
};

struct IObj {
    VP VP VP VP                                        // 0x00..0x0c
    virtual IObj* v10();                               // 0x10
    virtual IObj* v14(int x = 0);                      // 0x14
    VP4 VP4 VP4                                        // 0x18..0x44
    virtual IObj* v48(int x);                          // 0x48
    VP4 VP4 VP4 VP4 VP VP VP                           // 0x4c..0x94
    virtual void  v98();                               // 0x98
};

struct Arg2;

struct IOwner {
    VP VP VP VP VP                                     // 0x00..0x10
    virtual int  v14();                                // 0x14
    VP4 VP4 VP4 VP4 VP4 VP4                            // 0x18..0x78
    VP VP                                              // 0x7c
    virtual void v80(void* p);                         // 0x80 (slot 32)
    char pad04[0xc];                                   // +0x04..0x0f
    int  m10;                                          // +0x10
    int  m14;                                          // +0x14
    bool Process(IObj* arg1, Arg2* arg2);
    bool Process2(IObj* arg1, Arg2* arg2);
};

struct Navigator {
    void* m00;
    void* volatile m04;
    void* m08;
    void* volatile m0c;
    Navigator();
    ~Navigator();
};

struct ExplicitNavigator : Navigator {
    void* m10;
    void* m14;
    ExplicitNavigator();
};

struct Arg2 {
    char  pad0[8];
    int   m08;                     // +0x08
    int   m0c;                     // +0x0c
    int   m10;                     // +0x10
    int   m14;                     // +0x14
    void* m18;                     // +0x18
};

Navigator::Navigator()
{
    m04 = (void*)kNavigatorBaseVtbl;
    // Finish installing the base interface before materializing its null state.
    _ReadWriteBarrier();
    m08 = 0;
    m0c = (void*)kNavigatorVtbl;
}

// @ 0x00980360
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

// @ 0x00980420
Navigator::~Navigator()
{
    m0c = (void*)kNavigatorDtorVtbl;
    m04 = (void*)kNavigatorDtorVtbl;
    m00 = (void*)kNavigatorDtorVtbl;
}

// @ 0x00980430
ExplicitNavigator::ExplicitNavigator()
{
    m00 = (void*)kExplicitNavSelfVtbl;
    m04 = (void*)kExplicitNavVtbl04;
    m0c = (void*)kExplicitNavVtbl0c;
    m10 = 0;
    m14 = 0;
}
}}  // namespace EA::UTFWinControls
