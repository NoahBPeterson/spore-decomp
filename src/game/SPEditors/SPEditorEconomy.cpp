// src/game/SPEditors/SPEditorEconomy.cpp -- migrated from slice(s) s005a6e60 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorEconomy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorEconomy.h"
#include "SP/cSPEditorComplexityMeter.h"
#include "SP/cString.h"

// ---- items of slice s005a6e60 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
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
// ---- items of slice s005a6e60 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern char g_msgVt1[], g_msgVt2[];

// @ 0x005a7840
void SP::cSPEditorEconomy::SendChangedMessage()
{
    EconomyChangedMsg msg;
    msg.f8 = 0;
    msg.v0 = g_msgVt1;
    msg.v1 = g_msgVt2;
    msg.id = 0x3150c27;
    msg.owner = this;
    MessageServer()->PostMessage(msg.id, &msg, 0);
}
