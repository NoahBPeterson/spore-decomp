// src/game/SPEditors/SPEditorComplexityMeter.cpp -- migrated from slice(s) s005a6e60 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorComplexityMeter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s005a6e60 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cMeterB1 { public: virtual int v0(); };
}
namespace SP {
class cMeterB2 { public: virtual int v0(); };
}
namespace SP {
class cMeterB3 { public: cMeterB3() : mC(0) {} virtual int v0(); int mC; };
}
namespace SP {
class cSPEditorComplexityMeter_s005a_6e60 : public cMeterB1, public cMeterB2, public cMeterB3 {
public:
    void* f10;
    void* f14;
    void* f18;
    void* f1c;
    void* f20;
    char  gap24[0x10];
    float f34;
    void* f38;
    bool  f3c;
    bool  f3d;
    char  pad3e[2];
    void* f40;
    void* f44;
    void* f48;
    void* f4c;
    void* f50;
    void* f54;
    cSPEditorComplexityMeter_s005a_6e60();
};
}
// ---- items of slice s005a6e60 end

// @ 0x005a6e60
SP::cSPEditorComplexityMeter_s005a_6e60::cSPEditorComplexityMeter_s005a_6e60()
: f10(0), f14(0), f18(0), f1c(0), f20(0), f34(0.0f), f38(0),
      f3c(false), f3d(false), f40(0), f44(0), f48(0), f4c(0), f50(0), f54(0) {}

// @ 0x005a6ee0
void FUN_005a6ee0()
{}

// @ 0x005a6fc0
void FUN_005a6fc0()
{}

// @ 0x005a7380
void FUN_005a7380()
{}

// @ 0x005a74d0
void FUN_005a7840()
{}
