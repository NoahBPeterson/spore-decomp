// slice s005a6e60 — editor complexity meter / badness calculator ctors+dtors and
// assorted editor helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define PV(n) virtual void pv##n();

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

namespace SP {
class cString {
public:
    cString();
    ~cString();
    char pad[0x14];
};
struct cSPColorRGB { float r, g, b; };
}

// ---- SP::cSPEditorGeneralBadnessCalculator (dtor target) -------------------
namespace SP {
class cBadnessBase1 { public: virtual ~cBadnessBase1() {} virtual int v0(); };
class cBadnessBase2 {
public:
    cBadnessBase2() : m80(0) {}
    virtual ~cBadnessBase2() {}
    virtual int v0();
    int m80;
};
class cSPEditorGeneralBadnessCalculator : public cBadnessBase1, public cBadnessBase2 {
public:
    float mValues[27];   // +0xc .. +0x74
    cSPEditorGeneralBadnessCalculator();
    ~cSPEditorGeneralBadnessCalculator();
};

// @ 0x005a7920
cSPEditorGeneralBadnessCalculator::~cSPEditorGeneralBadnessCalculator() {}

// @ 0x005a7900
cSPEditorGeneralBadnessCalculator::cSPEditorGeneralBadnessCalculator() {}
}  // namespace SP

// ---- generic UI element ctor -----------------------------------------------
class cUIThing {
public:
    char pad[0x10];
    short m10;
    short m12;
    cUIThing(void* arg);
    void Helper(int a, int b, void* c, int d, int e);  // 0x0093dd80
};

// @ 0x005a74a0
cUIThing::cUIThing(void* arg) {
    m10 = 0;
    m12 = 0;
    Helper(0x13, 9, arg, 0x10, 1);
}

// ---- dual-cString data ctor -------------------------------------------------
class cDualString {
public:
    SP::cString mName;    // +0x0
    SP::cString mName2;   // +0x14
    uint32_t m28;         // +0x28
    void* m2c;            // +0x2c
    bool m30;             // +0x30
    cDualString();
};

// @ 0x005a7810
cDualString::cDualString() {
    m2c = 0;
    m30 = false;
    m28 = 0xffff0000;
}

// ---- SP::cSPEditorComplexityMeter ctor -------------------------------------
namespace SP {
class cMeterB1 { public: virtual int v0(); };
class cMeterB2 { public: virtual int v0(); };
class cMeterB3 { public: cMeterB3() : mC(0) {} virtual int v0(); int mC; };
class cSPEditorComplexityMeter : public cMeterB1, public cMeterB2, public cMeterB3 {
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
    cSPEditorComplexityMeter();
};
}

// @ 0x005a6e60
SP::cSPEditorComplexityMeter::cSPEditorComplexityMeter()
    : f10(0), f14(0), f18(0), f1c(0), f20(0), f34(0.0f), f38(0),
      f3c(false), f3d(false), f40(0), f44(0), f48(0), f4c(0), f50(0), f54(0) {}

// @ 0x005a6ee0
void FUN_005a6ee0() {}

// ---- SP::cSPEditorEconomy::SendChangedMessage ------------------------------
extern char g_msgVt1[], g_msgVt2[];
class IMessageServer {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void PostMessage(uint32_t id, void* message, int flags);  // +0x14
};
IMessageServer* MessageServer();  // 0x0067dcc0

struct EconomyChangedMsg {
    void* v0;
    void* v1;
    uint32_t f8;
    uint32_t id;
    void* owner;
};

namespace SP {
class cSPEditorEconomy {
public:
    void SendChangedMessage();
};
}

// @ 0x005a7840
void SP::cSPEditorEconomy::SendChangedMessage() {
    EconomyChangedMsg msg;
    msg.f8 = 0;
    msg.v0 = g_msgVt1;
    msg.v1 = g_msgVt2;
    msg.id = 0x3150c27;
    msg.owner = this;
    MessageServer()->PostMessage(msg.id, &msg, 0);
}

// @ 0x005a6fc0
void FUN_005a6fc0() {}

// @ 0x005a7220
void FUN_005a7220() {}

// @ 0x005a7380
void FUN_005a7380() {}

// @ 0x005a7410
void FUN_005a7410() {}

// @ 0x005a74d0
void FUN_005a74d0() {}

// @ 0x005a7840
void FUN_005a7840() {}

// @ 0x005a7930
void FUN_005a7930() {}
