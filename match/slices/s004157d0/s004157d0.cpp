// Slice s004157d0: SP editor behavior-message handler FUN_004157d0 (Handler::HandleMessage).
// Built unoptimized, no EH: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS-
// Behavioral reconstruction, NOT byte-exact (see nonmatching.txt).
#include "types.h"

// ------------------------------------------------------------------ message data
struct MsgKey {                 // the incoming message key triple
    uint32_t mKey0;             // +0x00
    uint32_t mKey1;             // +0x04
    uint32_t mKey2;             // +0x08
};

struct MsgArgs {                // the incoming message args
    uint32_t mId;               // +0x00
    uint16_t mFlags;            // +0x04
    uint16_t mValue;            // +0x06
};

// ------------------------------------------------------------------ 0x40-byte editor message (vtable 0x13eb844)
struct Slot { uint32_t v, pad; };
struct Slots {
    Slot slot[5];               // +0x00
    uint32_t id30;              // +0x28 (object+0x30)
    uint32_t pad34;             // +0x2c
    void Set(int i, uint32_t v) { slot[i].v = v; }
};

struct Msg {
    void* vtbl;                 // +0x00
    uint32_t pad4;              // +0x04
    Slots s;                    // +0x08
    uint32_t f38;               // +0x38
    uint32_t pad3c;             // +0x3c
    Msg(uint32_t id);           // 0x423110
    void Base2Init();           // 0x40fd50
    void Set(int i, uint32_t v) { s.Set(i, v); }
    static void* operator new(unsigned size, const char* name);
};
struct BMsg : Msg {
    BMsg(uint32_t id) : Msg(id) { vtbl = (void*)0x13eb844; f38 = 0; }
};

struct MsgMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void Post(uint32_t id, Msg* m, uint32_t a, uint32_t b);     // +0x18
};

// ------------------------------------------------------------------ refcounted editor objects
struct Target {
    virtual int  AddRef();                                  // +0x00
    virtual int  Release();                                 // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11();
    virtual void F2c(void* a);                              // +0x2c
};

struct TRef {
    Target* p;                                              // +0x00
    Target** Out();                                         // 0x41d870
};

// ------------------------------------------------------------------ keyed record (0x34 bytes)
struct KeyedRecord {
    uint32_t mKey00;            // +0x00
    uint32_t mKey04;            // +0x04
    uint32_t mKey08;            // +0x08
    uint32_t mField0C;          // +0x0c
    uint16_t mFlags10;          // +0x10
    uint16_t mValue12;          // +0x12
    void*    mField14;          // +0x14
    void*    mField18;          // +0x18
    TRef     mJob1C;            // +0x1c
    void*    mField20;          // +0x20
    TRef     mSlots24[4];       // +0x24
    KeyedRecord();              // 0x4036e0
    void Destroy();             // 0x401f20
};

// ------------------------------------------------------------------ engine interfaces
extern void*   __cdecl FUN_00f473a0(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00f473a0
extern void*   __cdecl GetManager();                    // 0x0067dcd0
extern MsgMgr* __cdecl GetMsgMgr();                     // 0x0067dcc0
extern char    __cdecl FUN_006a25a0();                  // 0x006a25a0
extern char    __cdecl FUN_00469920(uint32_t key, uint32_t id, Target** out);   // 0x00469920
extern void    __cdecl FUN_00471830(void* a, void* b);  // 0x00471830
extern char    __cdecl FUN_004bafc0(void* msg, Target** out);                   // 0x004bafc0
extern void*   __cdecl FUN_004186c0(void* a, void* b, Target** out);            // 0x004186c0
extern char    __cdecl FUN_004204f0();                  // 0x004204f0
extern char    __cdecl FUN_004204d0();                  // 0x004204d0
extern int     __cdecl FUN_0068f950();                  // 0x0068f950
extern int     __cdecl FUN_00690120();                  // 0x00690120
extern void*   g_AppProperties;                         // 0x015fd918
extern const char kEditorAllocName[];                   // 0x013eb430

inline void* Msg::operator new(unsigned size, const char* name)
{
    return FUN_00f473a0(size, name, 0, 0, 0, 0);
}

// smart-pointer templates the original inlined
#define ASSIGN_REF(dst, src) \
    do { \
        if ((src) != (dst).p) { \
            Target* old_ = (dst).p; \
            if (src) (src)->AddRef(); \
            (dst).p = (src); \
            if (old_) old_->Release(); \
        } \
    } while (0)
#define ASSIGN_JOB(dst, src) \
    do { \
        if ((src) != (dst).p) { \
            Target* old_ = (dst).p; \
            if (src) ((int(__thiscall*)(void*))FUN_0068f950)(src); \
            (dst).p = (src); \
            if (old_) ((int(__thiscall*)(void*))FUN_00690120)(old_); \
        } \
    } while (0)
#define RELEASE_REF(t) do { if ((t).p) (t).p->Release(); } while (0)
#define RELEASE_JOB(t) do { if (t) ((int(__thiscall*)(void*))FUN_00690120)(t); } while (0)

#define NEW_HMSG(var, idv) \
    Msg* tmp##var; \
    void* raw##var = FUN_00f473a0(0x40, kEditorAllocName, 0, 0, 0, 0); \
    if (raw##var) { \
        ((Msg*)raw##var)->s.id30 = (idv); \
        ((Msg*)raw##var)->Base2Init(); \
        ((Msg*)raw##var)->vtbl = (void*)0x13eb90c; \
        ((Msg*)raw##var)->vtbl = (void*)0x13eb844; \
        ((Msg*)raw##var)->f38 = 0; \
        tmp##var = (Msg*)raw##var; \
    } else tmp##var = 0; \
    var = tmp##var;

struct Handler {
    void**  mpVtbl;                     // +0x00
    uint8_t mPad04[0x0c8 - 0x04];
    uint8_t mRecordSet[0x2c * 0x40];    // +0x0c8
    bool HandleMessage(const MsgKey* msg, const MsgArgs* args);   // 0x004157d0
};

// @ 0x004157d0
bool Handler::HandleMessage(const MsgKey* msg, const MsgArgs* args)
{
    uint32_t key2   = msg->mKey2;
    uint32_t id71   = (key2 & 0xffff00ff) | (0x71 << 8);
    uint32_t id62   = (key2 & 0xffff00ff) | (0x62 << 8);
    uint32_t packed = 0;
    if (((key2 >> 16) & 0xff) == 0x62)
        packed = (id62 & 0xe0ffffff) | 0x01000000;

    GetManager();

    bool ok = true;
    if ((args->mFlags & 0x20) == 0 &&
        ((char(__thiscall*)(void*, uint32_t))FUN_006a25a0)(g_AppProperties, 0x26cd3a5) != 0) {
        bool handled = ((char(__thiscall*)(void*, const MsgKey*, uint32_t))mpVtbl[0x1c / 4])(this, msg, 0) != 0;
        if (!handled)
            handled = ((char(__thiscall*)(void*, const MsgKey*, uint32_t))mpVtbl[0x38 / 4])(this, msg, args->mId) != 0;
        ok = !handled;
    }

    if (!ok) {
        Msg* m;
        NEW_HMSG(m, 0x695e243)
        m->Set(0, msg->mKey0);
        m->Set(1, msg->mKey2);
        m->Set(2, msg->mKey1);
        m->Set(3, args->mId);
        m->Set(4, 0);
        GetMsgMgr()->Post(0x695e243, m, 0, 0);
        return true;
    }

    TRef a50, a4c, a54, a5c;
    a50.p = 0;
    a4c.p = 0;
    a54.p = 0;
    a5c.p = 0;
    Target* job = 0;

    if (FUN_004bafc0((void*)msg, a50.Out()) == 0) {
        Msg* m = new (kEditorAllocName) BMsg(0x695e243);
        m->Set(0, msg->mKey0);
        m->Set(1, msg->mKey2);
        m->Set(2, msg->mKey1);
        m->Set(3, args->mId);
        m->Set(4, 1);
        GetMsgMgr()->Post(0x695e243, m, 0, 0);
        RELEASE_REF(a5c);
        RELEASE_REF(a54);
        RELEASE_REF(a4c);
        RELEASE_REF(a50);
        return false;
    }

    FUN_00469920(msg->mKey0, id71, a4c.Out());

    if (FUN_00469920(msg->mKey0, id62, a54.Out()) != 0)
        FUN_00471830(a50.p, a54.p);

    if (packed != 0) {
        if (FUN_00469920(msg->mKey0, packed, a5c.Out()) != 0)
            a5c.p->F2c(a54.p);
    }

    job = 0;
    if (FUN_004186c0(a50.p, (void*)args, &job) == 0) {
        Msg* m = new (kEditorAllocName) BMsg(0x695e243);
        m->Set(0, msg->mKey0);
        m->Set(1, msg->mKey2);
        m->Set(2, msg->mKey1);
        m->Set(3, args->mId);
        m->Set(4, 1);
        GetMsgMgr()->Post(0x695e243, m, 0, 0);
        RELEASE_JOB(job);
        RELEASE_REF(a5c);
        RELEASE_REF(a54);
        RELEASE_REF(a4c);
        RELEASE_REF(a50);
        return false;
    }

    KeyedRecord rec;
    ASSIGN_JOB(rec.mJob1C, job);
    rec.mField0C = args->mId;
    rec.mFlags10 = args->mFlags;
    rec.mValue12 = args->mValue;
    rec.mKey00 = msg->mKey0;
    rec.mKey04 = msg->mKey1;
    rec.mKey08 = msg->mKey2;
    ASSIGN_REF(rec.mSlots24[0], a4c.p);
    ASSIGN_REF(rec.mSlots24[1], a54.p);
    ASSIGN_REF(rec.mSlots24[2], a5c.p);
    if (args->mFlags & 1)
        ((char(__thiscall*)(void*, void*, uint32_t))FUN_004204f0)(mRecordSet, &rec, args->mValue);
    else
        ((char(__thiscall*)(void*, void*, uint32_t))FUN_004204d0)(mRecordSet, &rec, args->mValue);
    rec.Destroy();
    RELEASE_JOB(job);
    RELEASE_REF(a5c);
    RELEASE_REF(a54);
    RELEASE_REF(a4c);
    RELEASE_REF(a50);
    return true;
}