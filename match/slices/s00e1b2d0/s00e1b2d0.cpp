// @ 0x00e1b2d0
#include "game/types.h"

// Stand-in for the primary base. The real type is cUIMissionCardPanel; the
// layout here only needs to place the inherited fields at their retail
// offsets (base occupies 0x00..0x3f, so this class's own fields start 0x40).
struct cUIMissionCardPanelStub
{
    void* vf00;            // +0x00 primary vftable
    int   pad04;           // +0x04
    void* vf08;            // +0x08 secondary vftable
    void* vf0c;            // +0x0c secondary vftable
    char  pad10[0x30];     // +0x10 .. +0x3f

    void* Construct();     // 0x00e18bb0
};

struct cMissionPanelDerived : cUIMissionCardPanelStub
{
    void* vf40;            // +0x40 secondary base vftable
    void* m44;             // +0x44
    void* m48;             // +0x48
    void* m4c;             // +0x4c
    void* m50;             // +0x50 (left untouched by Construct)
    void* m54;             // +0x54 (left untouched by Construct)
    void* m58;             // +0x58
    void* m5c;             // +0x5c
    void* m60;             // +0x60
    void* m64;             // +0x64
    void* m68;             // +0x68
    void* m6c;             // +0x6c
    void* m70;             // +0x70
    void* m74;             // +0x74
    void* m78;             // +0x78
    void* m7c;             // +0x7c
    void* m80;             // +0x80
    void* m84;             // +0x84
    void* m88;             // +0x88
    void* m8c;             // +0x8c
    int   m90;             // +0x90
    void* m94;             // +0x94

    cMissionPanelDerived* Construct();
};

cMissionPanelDerived* cMissionPanelDerived::Construct()
{
    cUIMissionCardPanelStub::Construct();

    // Retail stores the four vftable pointers immediately after the base
    // Construct call, ahead of the zero-fill block, with the shared
    // `xor eax,eax` hoisted above them. If all four are plain member stores
    // the scheduler sinks the whole group below the zero fill, so the +0x40
    // slot is written through the member's address (the base-subobject
    // vftable assignment), which keeps the group in place.
    vf00 = (void*)0x1480248;
    vf08 = (void*)0x148022c;
    vf0c = (void*)0x1480224;
    void** const ppVft40 = &vf40;
    *ppVft40 = (void*)0x1480218;

    m44 = 0;
    m48 = 0;
    m4c = 0;

    m58 = 0;
    m5c = 0;
    m60 = 0;
    m64 = 0;
    m68 = 0;
    m6c = 0;
    m70 = 0;
    m74 = 0;
    m78 = 0;
    m7c = 0;
    m80 = 0;
    m84 = 0;
    m88 = 0;

    m94 = 0;
    m8c = (void*)0x67a2ae0;
    m90 = -1;

    return this;
}
