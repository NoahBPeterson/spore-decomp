// src/game/SPBake/SPEditorBudget.cpp -- migrated from slice(s) s004575d0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorBudget.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorBudget.h"
#include "EA/COM/IUnknown32.h"
#include <xmmintrin.h>

// ---- items of slice s004575d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct MessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Send(void* self, unsigned int msg, int flags);   // slot 11 (+0x2c)
};
// ---- items of slice s004575d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void  FUN_00811ad0(void* layout, int one);   // cSPUILayout::Shutdown
extern void* SP_MessageServer();                    // 0x0067dcc0

// @ 0x00457950
void * SP::cSPEditorBudget::AsInterface(EA::COM::InterfaceId id)
{
    unsigned int iid = id;
    void* result;
    if (iid == 0xee3f516e) {
        if (this == 0)
            result = 0;
        else
            result = static_cast<EA::COM::IUnknown32 *>(this);
    } else if (iid == 0x726ecf35) {
        result = this;
    } else {
        result = 0;
    }
    return result;
}

// @ 0x004579a0
void FUN_004579a0(int* self)
{
    (void)self;
}

// @ 0x004581d0
void SP::cSPEditorBudget::Shutdown()
{
    if (mLayout.mpObject != 0) {
        FUN_00811ad0(mLayout.mpObject, 1);
        if (mLayout.mpObject != 0) {
            void* old = mLayout.mpObject;
            mLayout.mpObject = 0;
            ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
        }
    }
    MessageServer* ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x522f9ce, 0xffffd8f1);
    ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x522f9cd, 0xffffd8f1);
    ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x3150c27, 0xffffd8f1);
}
