// Editor UI message handler: builds a packed message id from the incoming message,
// checks whether it is allowed, then allocates "Editor" BehaviorMessage objects and
// dispatches them through the global message server.
// Original is built /Od /Ob1 (frame pointer, all locals in memory, heavy inlining of
// smart-pointer / EASTL helpers). This source is behaviorally approximate and NOT byte-exact.
#include "types.h"

struct MsgKey { uint32_t a, b, c; };            // incoming message (id parts at +0,+4,+8)
struct MsgArgs { uint32_t id; uint16_t flags; uint16_t value; };

struct BehaviorMessage {
    virtual void Release();                     // slot 0 (placeholder)
    uint32_t fields[12];
    uint32_t pad;
};

struct MessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Post(uint32_t channel, BehaviorMessage* msg, int, int); // slot 6 (+0x18)
};

extern void* EASTL_allocator_allocate(uint32_t size, const char* name, int, int, int, int);
extern MessageServer* GetMessageServer();       // FUN_0067dcc0
extern bool IsFeatureEnabled(void* mgr, uint32_t id);   // FUN_006a25a0
extern void* g_FeatureMgr;                      // 0x015fd918

struct EditorHandler {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool CanHandle(const MsgKey* msg, int);         // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13();
    virtual bool Accepts(const MsgKey* msg, uint32_t extra); // +0x38

    bool HandleMessage(const MsgKey* msg, const MsgArgs* args);
};

static void FillAndPost(const MsgKey* msg, const MsgArgs* args, uint32_t tag)
{
    BehaviorMessage* bm = (BehaviorMessage*)EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0);
    if (bm) {
        bm->fields[0] = msg->a;
        bm->fields[1] = msg->c;
        bm->fields[2] = msg->b;
        bm->fields[3] = args->id;
        bm->fields[4] = tag;
    }
    GetMessageServer()->Post(0x695e243, bm, 0, 0);
}

// @ 0x004157d0
bool EditorHandler::HandleMessage(const MsgKey* msg, const MsgArgs* args)
{
    uint32_t idLo = (msg->c & 0xffff00ff) | (0x71 << 8);
    uint32_t idHi = (msg->c & 0xffff00ff) | (0x62 << 8);
    uint32_t packed = 0;
    if (((idHi >> 16) & 0xff) == 0x62)
        packed = (idHi & 0xe0ffffff) | (1u << 24);

    bool ok = true;
    if (!(args->flags & 0x20) && IsFeatureEnabled(g_FeatureMgr, 0x26cd3a5)) {
        ok = true;
    } else {
        ok = false;
    }
    if (ok) {
        ok = CanHandle(msg, 0) || Accepts(msg, args->id);
    }

    if (ok) {
        FillAndPost(msg, args, 1);
        (void)idLo; (void)packed;
    } else {
        FillAndPost(msg, args, 0);
    }
    return true;
}
