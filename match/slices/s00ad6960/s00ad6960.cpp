// Slice s00ad6960 - Spore Simulator ArgScript commands + UI layout/subsystem
// helpers (show/hide widget groups, subtitles, modal, action target ctor).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned char  byte;

// UI element with vtable slot +0x7c(show,int) used by many helpers
struct CUIElem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void v7c(int a, int b);        // +0x7c
};
struct RCObj { virtual void AddRef(); virtual void Release(); virtual void v08(); };
struct CGUI {
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    virtual void g20(); virtual void g24(); virtual void g28(); virtual void g2c();
    virtual void g30(); virtual void g34(); virtual void g38(); virtual void g3c();
    virtual void g40(); virtual void g44(); virtual void g48(); virtual void g4c(int, int); // +0x4c
};

extern "C" void* operator_new6(int size, const char* tag, int a, int b, int c, int d); // 0xf473a0
extern "C" void  operator_delete(void* p);                              // 0xf47380
extern "C" uint32 EA_Hash_FNV1_String8(const char* s, uint32 seed, int flag); // 0x932e80

extern float DAT_0167a548, DAT_0167a54c, DAT_0167a550;
extern float DAT_0167a4bc, DAT_0167a4c0, DAT_0167a4c4;

struct CSub { virtual void AddRef(); virtual void Release(); };
struct PtrSlot {
    void* mp;                    // +0x00
    void* FUN_00ad72e0(PtrSlot* p);
    void* FUN_00ad7300(PtrSlot* p);
    void* FUN_00ad7320(PtrSlot* p);
};
struct CUID {
    char  pad0[0x10];
    void* m10; void* m14; void* m18; void* m1c;
    void* m20; void* m24; void* m28; void* m2c;
    void* m30; void* m34; void* m38; void* m3c;
    void* m40; void* m44; void* m48; void* m4c;
    void* m50; byte  m54;
    void FUN_00ad7470();
    void FUN_00ad75c0();
    void FUN_00ad7610(int r);
    void FUN_00ad7640(int a);
    void FUN_00ad7670(int a, float b, int c, int d, float e);
    void FUN_00ad76c0();
    void FUN_00ad76f0(int show);
    void FUN_00ad7740(int show);
    void FUN_00ad7790(int show);
    void FUN_00ad77c0(int show);
    void FUN_00ad7810(int show);
    void FUN_00ad7860(int show);
    void FUN_00ad78b0(int show);
    void FUN_00ad7900(char on);
};
struct CArgCmd2 {
    void FUN_00ad6960(void* a);
    void FUN_00ad6bc0(void* a);
    void* FUN_00ad6ec0(byte flags);
    void* FUN_00ad6f10(byte flags);
};

// ===========================================================================
// @ 0x00ad6960
// ===========================================================================
extern "C" char FUN_0083b9d0(void* self, void* a, void* b);           // 0x83b9d0
// source-command payload at +0xd8..+0x103 (see the ArgScript spec in 00ad6b00)
struct SimCmd {
    char  pad0[0x80];
    int   mFlags;                      // +0x80 (option bits set by Parse)
    char  pad84[0x54];
    char* mObjectName;                 // +0xd8
    int   mObjectPosType;              // +0xdc
    char* mInitialPosName;             // +0xe0
    float mInitialPos[3];              // +0xe4
    int   mFaceState;                  // +0xf0
    char* mFaceName;                   // +0xf4
    float mFaceOffset[3];              // +0xf8
    void* init();                      // 0xad6b00 (ArgScript spec registration ctor)
};
// (constructs the refcounted command payload + BehaviorMessage and posts it)
struct CRefVtbl { virtual void v00(); virtual void v04(); virtual void v08(); };
struct CSummObj {                     // 0x14-byte content-validation summarizer
    void* mVtbl0;                     // +0x00
    void* mVtbl1;                     // +0x04
    int   mField8;                    // +0x08
    int   mHash;                      // +0x0c
    byte  mFlag;                      // +0x10
};
struct CBehavMsg {                    // 0x40-byte UI::BehaviorMessage
    void* mVtbl;                      // +0x00
    void* mField4;                    // +0x04
    void* mField8;                    // +0x08
    char  padC[0x24];
    int   mMsgId;                     // +0x30
    int   mField34;                   // +0x34
    int   mFlags;                     // +0x38
    int   mField3c;                   // +0x3c
};
struct CEditorRes {                   // 0x14-byte editor resource wrapper
    void* mVtbl;                      // +0x00
    void* mField4;                    // +0x04
    CRefVtbl* mObj;                   // +0x08
    CRefVtbl* mValue;                 // +0x0c
    void* mCallback;                  // +0x10
};
struct EditorResCtor { void* ctor(); };                              // 0xad7c30
struct ArgSpecParse { void parse(void* args, void* parser); };       // 0x83b9d0
extern "C" void* SP_cAppStateManager_AddMessage(void* self, void* a, void* msg, int b); // 0x7e4190
void CArgCmd2::FUN_00ad6960(void* a)
{
    SimCmd* c = (SimCmd*)this;
    c->mObjectName = 0;
    c->mObjectPosType = 1;
    ((ArgSpecParse*)((char*)this + 0x10))->parse(a, *(void**)((char*)this + 4));

    CSummObj* s = (CSummObj*)operator_new6(0x14, "Simulator", 0, 0, 0, 0);
    if (s) {
        s->mVtbl1 = (void*)0x13ec458;
        s->mField8 = 0;
        s->mVtbl0 = (void*)0x145af7c;
        s->mVtbl1 = (void*)0x149bad8;
        s->mHash = 0;
        s->mFlag = 1;
        ((CRefVtbl*)s)->v00();
    }
    s->mHash = EA_Hash_FNV1_String8(c->mObjectName, 0x811c9dc5, 1);
    s->mFlag = c->mObjectPosType;

    CBehavMsg* m = (CBehavMsg*)operator_new6(0x40, "Simulator", 0, 0, 0, 0);
    if (m) {
        m->mMsgId = 0;
        m->mVtbl = (void*)0x13eb90c;
        m->mField4 = 0;
        m->mVtbl = (void*)0x13eb844;
        m->mFlags = 0;
        ((CRefVtbl*)m)->v04();
    }
    m->mMsgId = 0x4470a41;

    CEditorRes* r = (CEditorRes*)operator_new6(0x14, "Simulator", 0, 0, 0, 0);
    if (r) {
        r = (CEditorRes*)((EditorResCtor*)r)->ctor();
        if (r) r->mObj->v00();
    }
    CRefVtbl* old = r->mValue;
    if ((void*)s != (void*)old) {
        ((CRefVtbl*)s)->v00();
        r->mValue = (CRefVtbl*)s;
        if (old) old->v04();
    }
    r->mCallback = (void*)0xad2910;
    CRefVtbl* sub = r->mObj;
    if ((m->mFlags & 1) && m->mField8) ((CRefVtbl*)m->mField8)->v04();
    m->mField8 = sub;
    if (sub) sub->v00();
    m->mFlags |= 1;
    SP_cAppStateManager_AddMessage(*(void**)((char*)this + 0xc), a, m, 0);
    sub->v04();
    ((CRefVtbl*)m)->v08();
    ((CRefVtbl*)s)->v04();
}

// ===========================================================================
// @ 0x00ad6b00
// ===========================================================================
extern "C" void FUN_0083bcd0(void* self, ...);                        // 0x83bcd0
struct CmdBaseCtor { void baseCtor(); };                              // 0x83c800
struct ArgSpecCtor { void specCtor(bool named); };                    // 0x83a9f0
extern char gEffectPosType[];                                         // 0x15662e0
void* SimCmd::init()
{
    SimCmd* c = this;
    ((CmdBaseCtor*)this)->baseCtor();
    *(void**)this = (void*)0x145afdc;
    ((ArgSpecCtor*)((char*)this + 0x10))->specCtor(true);
    FUN_0083bcd0((char*)this + 0x10,
                 "Adds a referencable object",
                 ":positionType",
                 gEffectPosType,
                 "<objectName:cstring>",
                 &c->mObjectName,
                 "object identifier (name)",
                 "-initialRelativePosition^ <posType:positionType> <posName:cstring> <position:vector3>",
                 0,
                 &c->mObjectPosType,
                 &c->mInitialPosName,
                 &c->mInitialPos[0],
                 "initial position",
                 "-face^ <facingType:positionType> <facingName:cstring> [facingOffset:vector3]",
                 1,
                 &c->mFaceState,
                 &c->mFaceName,
                 &c->mFaceOffset[0],
                 "face a position with an optional offset",
                 "-useFootprintRadius^",
                 2,
                 "uses the foot radius of the actor as an offset multiplier",
                 "-useTargetWidth^",
                 3,
                 "uses the max width of the target object as an offset multiplier",
                 "-useTargetHeight^",
                 4,
                 "uses the height of the target object as an offset multiplier",
                 0);
    return this;
}

// ===========================================================================
// @ 0x00ad6bc0
// ===========================================================================
struct CSummActor {                   // 0x3c-byte actor settings summarizer
    void* mVtbl0;                     // +0x00
    void* mVtbl1;                     // +0x04
    int   mField8;                    // +0x08
    int   mHashName;                  // +0x0c
    int   mPosType;                   // +0x10
    int   mHashPos;                   // +0x14
    int   mFacingState;               // +0x18
    float mInitialPos[3];             // +0x1c
    int   mFaceKind;                  // +0x28
    int   mHashFace;                  // +0x2c
    float mFaceOffset[3];             // +0x30
};
extern float gDefaultPosX, gDefaultPosY, gDefaultPosZ;                // 0x167a4bc/c0/c4
void CArgCmd2::FUN_00ad6bc0(void* a)
{
    SimCmd* c = (SimCmd*)this;
    c->mObjectName = 0;
    c->mInitialPos[0] = gDefaultPosX;
    c->mInitialPos[1] = gDefaultPosY;
    c->mInitialPos[2] = gDefaultPosZ;
    c->mFaceState = 0;
    c->mFaceName = 0;
    c->mFaceOffset[0] = gDefaultPosX;
    c->mFaceOffset[1] = gDefaultPosY;
    c->mFaceOffset[2] = gDefaultPosZ;
    ((ArgSpecParse*)((char*)this + 0x10))->parse(a, *(void**)((char*)this + 4));

    CSummActor* s = (CSummActor*)operator_new6(0x3c, "Simulator", 0, 0, 0, 0);
    if (s) {
        s->mVtbl1 = (void*)0x13ec458;
        s->mField8 = 0;
        s->mVtbl0 = (void*)0x145aff4;
        s->mVtbl1 = (void*)0x149bad8;
        s->mHashName = 0;
        s->mPosType = 0;
        s->mFacingState = 3;
        s->mInitialPos[0] = gDefaultPosX;
        s->mInitialPos[1] = gDefaultPosY;
        s->mInitialPos[2] = gDefaultPosZ;
        s->mFaceKind = 0;
        s->mHashFace = 0;
        s->mFaceOffset[0] = gDefaultPosX;
        s->mFaceOffset[1] = gDefaultPosY;
        s->mFaceOffset[2] = gDefaultPosZ;
        ((CRefVtbl*)s)->v00();
    }
    s->mHashName = EA_Hash_FNV1_String8(c->mObjectName, 0x811c9dc5, 1);
    if (c->mFlags & 1) {
        s->mInitialPos[0] = c->mInitialPos[0];
        s->mInitialPos[1] = c->mInitialPos[1];
        s->mInitialPos[2] = c->mInitialPos[2];
        s->mPosType = c->mObjectPosType;
        s->mHashPos = EA_Hash_FNV1_String8(c->mInitialPosName, 0x811c9dc5, 1);
    }
    if (c->mFlags & 2) {
        s->mFaceKind = c->mFaceState;
        s->mHashFace = EA_Hash_FNV1_String8(c->mFaceName, 0x811c9dc5, 1);
        s->mFaceOffset[0] = c->mFaceOffset[0];
        s->mFaceOffset[1] = c->mFaceOffset[1];
        s->mFaceOffset[2] = c->mFaceOffset[2];
    }
    if (c->mFlags & 4) s->mFacingState = 0;
    else if (c->mFlags & 8) s->mFacingState = 1;
    else s->mFacingState = (~(c->mFlags >> 4)) & 1 | 2;

    CBehavMsg* m = (CBehavMsg*)operator_new6(0x40, "Simulator", 0, 0, 0, 0);
    if (m) {
        m->mMsgId = 0;
        m->mVtbl = (void*)0x13eb90c;
        m->mField4 = 0;
        m->mVtbl = (void*)0x13eb844;
        m->mFlags = 0;
        ((CRefVtbl*)m)->v04();
    }
    m->mMsgId = 0x4470a41;

    CEditorRes* r = (CEditorRes*)operator_new6(0x14, "Simulator", 0, 0, 0, 0);
    if (r) {
        r = (CEditorRes*)((EditorResCtor*)r)->ctor();
        if (r) r->mObj->v00();
    }
    CRefVtbl* old = r->mValue;
    if ((void*)s != (void*)old) {
        ((CRefVtbl*)s)->v00();
        r->mValue = (CRefVtbl*)s;
        if (old) old->v04();
    }
    r->mCallback = (void*)0xad3190;
    CRefVtbl* sub = r->mObj;
    if ((m->mFlags & 1) && m->mField8) ((CRefVtbl*)m->mField8)->v04();
    m->mField8 = sub;
    if (sub) sub->v00();
    m->mFlags |= 1;
    SP_cAppStateManager_AddMessage(*(void**)((char*)this + 0xc), a, m, 0);
    sub->v04();
    ((CRefVtbl*)m)->v08();
    ((CRefVtbl*)s)->v04();
}

// ===========================================================================
// @ 0x00ad6ec0
// ===========================================================================
struct ArgSpecDtor { void dtor(); };                                  // 0x405050
struct CmdBaseDtor { void dtor(); };                                  // 0x83c750
void* CArgCmd2::FUN_00ad6ec0(byte flags)
{
    void* self = this;
    void* p = *(void**)((char*)self + 0xdc);
    if (p && *(int*)((char*)p - 4)) operator_delete(p);
    ((ArgSpecDtor*)((char*)self + 0x10))->dtor();
    ((CmdBaseDtor*)self)->dtor();
    if (flags & 1) operator_delete(self);
    return self;
}

// ===========================================================================
// @ 0x00ad6f10
// ===========================================================================
void* CArgCmd2::FUN_00ad6f10(byte flags)
{
    void* self = this;
    ((ArgSpecDtor*)((char*)self + 0x10))->dtor();
    ((CmdBaseDtor*)self)->dtor();
    if (flags & 1) operator_delete(self);
    return self;
}

// ===========================================================================
// @ 0x00ad6f40
// ===========================================================================
struct TriggerMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void Register(int id, void* cmd);                          // vtbl+0x10
};
struct CmdAddActor  { CmdAddActor*  init(); };                        // 0xad5590
struct CmdMoveActor { CmdMoveActor* init(); };                        // 0xad5900
struct CmdPlayAnim  { CmdPlayAnim*  init(); };                        // 0xad5d90
struct CmdPlayAnim2 { CmdPlayAnim2* init(); };                        // 0xad6240
struct CmdSetState  { CmdSetState*  init(); };                        // 0xad66c0
struct CmdSimple    { void baseInit(); };                             // 0x83c800
struct CmdSetState2 { CmdSetState2* init(); };                        // 0xad68e0

extern int gAddObjectCmdId;                                           // 0x1566330
extern int gAddActorCmdId;                                            // 0x1566334
extern int gMoveActorCmdId;                                           // 0x1566388
extern int gPlayAnimationCmdId;                                       // 0x156638c
extern int gPlayAnimation2CmdId;                                      // 0x1566390
extern int gSetStateCmdId;                                            // 0x1566394
extern int gSimpleCmdId;                                              // 0x1566398
extern int gSetState2CmdId;                                           // 0x156639c

extern "C" void* GetTriggerMgr();                                     // 0xb3d4d0
void FUN_00ad6f40(void)
{
    void* o;
    o = operator_new6(0x104, "Simulator", 0, 0, 0, 0);
    void* cmd = o ? ((SimCmd*)o)->init() : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gAddObjectCmdId, cmd);
    o = operator_new6(0xfc, "Simulator", 0, 0, 0, 0);
    cmd = o ? ((CmdAddActor*)o)->init() : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gAddActorCmdId, cmd);
    o = operator_new6(0x108, "Simulator", 0, 0, 0, 0);
    cmd = o ? ((CmdMoveActor*)o)->init() : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gMoveActorCmdId, cmd);
    o = operator_new6(0x100, "Simulator", 0, 0, 0, 0);
    cmd = o ? ((CmdPlayAnim*)o)->init() : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gPlayAnimationCmdId, cmd);
    o = operator_new6(0x108, "Simulator", 0, 0, 0, 0);
    cmd = o ? ((CmdPlayAnim2*)o)->init() : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gPlayAnimation2CmdId, cmd);
    o = operator_new6(0xe0, "Simulator", 0, 0, 0, 0);
    cmd = o ? ((CmdSetState*)o)->init() : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gSetStateCmdId, cmd);
    o = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    cmd = o ? (((CmdSimple*)o)->baseInit(), *(void**)o = (void*)0x145a6a8, o) : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gSimpleCmdId, cmd);
    o = operator_new6(0xe0, "Simulator", 0, 0, 0, 0);
    cmd = o ? ((CmdSetState2*)o)->init() : 0;
    ((TriggerMgr*)GetTriggerMgr())->Register(gSetState2CmdId, cmd);
}

// ===========================================================================
// @ 0x00ad7150
// ===========================================================================
extern "C" int __stdcall FUN_00b320d0(int id);                       // 0xb320d0
bool FUN_00ad7150(void)
{
    return FUN_00b320d0(0x4bf38a8) > 0;
}

// ===========================================================================
// @ 0x00ad7170
// ===========================================================================
int FUN_00ad7170(uint32* p)
{
    if (((p[3] & 0x7fffffff) < 0x7f800001) &&
        ((p[0] & 0x7fffffff) < 0x7f800001) &&
        ((p[1] & 0x7fffffff) < 0x7f800001) &&
        ((p[2] & 0x7fffffff) < 0x7f800001)) {
        return 0;
    }
    return 1;
}

// ===========================================================================
// @ 0x00ad7200
// ===========================================================================
int FUN_00ad7200(const char* s)
{
    uint32 h = EA_Hash_FNV1_String8(s, 0x811c9dc5, 1);
    if (h < 0x6f0f5a3e) {
        if (h == 0x6f0f5a3d) return 8;
        if (h == 0x419c2c6e) return 0x17;
        if (h == 0x4e846817) return 7;
        if (h == 0x6e13411a) return 4;
    } else {
        if (h == 0xa9d28bb0) return 2;
        if (h == 0xff5e06be) return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00ad72e0
// ===========================================================================
void* PtrSlot::FUN_00ad72e0(PtrSlot* p)
{
    void** self = (void**)this;
    *self = p;
    if (p) (*(void (__thiscall*)(void*))(*(void**)((char*)*(void**)p + 0xbc)))(p);
    return self;
}

// ===========================================================================
// @ 0x00ad7300
// ===========================================================================
void* PtrSlot::FUN_00ad7300(PtrSlot* p)
{
    void** self = (void**)this;
    *self = p;
    if (p) ((CSub*)((char*)p + 8))->AddRef();
    return self;
}

// ===========================================================================
// @ 0x00ad7320
// ===========================================================================
void* PtrSlot::FUN_00ad7320(PtrSlot* p)
{
    void** self = (void**)this;
    void* old = *self;
    if (p != old) {
        if (p) ((CSub*)((char*)p + 8))->AddRef();
        *self = p;
        if (old) ((CSub*)((char*)old + 8))->Release();
    }
    return self;
}

// ===========================================================================
// @ 0x00ad73a0
// ===========================================================================
void** FUN_00ad73a0(void** first, void** last, void** out)
{
    if (first == last) return out;
    do {
        void* a = *first;
        void* b = *out;
        if (a != b) {
            if (a) ((CSub*)((char*)a + 8))->AddRef();
            *out = a;
            if (b) ((CSub*)((char*)b + 8))->Release();
        }
        ++first; ++out;
    } while (first != last);
    return out;
}

// ===========================================================================
// @ 0x00ad7400
// ===========================================================================
void** FUN_00ad7400(void* last_, void* first_, void** out)
{
    char* last = (char*)last_;
    char* first = (char*)first_;
    while (first != last) {
        void* a = *(void**)(first - 4);
        void* b = out[-1];
        first -= 4; --out;
        if (a != b) {
            if (a) ((CSub*)((char*)a + 8))->AddRef();
            *out = a;
            if (b) ((CSub*)((char*)b + 8))->Release();
        }
    }
    return out;
}

// ===========================================================================
// @ 0x00ad7470
// ===========================================================================
struct SubObj { virtual void s00(); virtual void s04(); virtual void s08(); };
void CUID::FUN_00ad7470()
{
    SubObj* p;
    p = *(SubObj* volatile*)&m50;
    *(void**)this = (void*)0x145b328;
    *(void**)((char*)this + 4) = (void*)0x145b30c;
    *(void**)((char*)this + 8) = (void*)0x145b2fc;
    if (p) p->s08();
    p = (SubObj*)m4c; if (p) p->s04();
    p = (SubObj*)m48; if (p) p->s04();
    p = (SubObj*)m44; if (p) p->s04();
    p = (SubObj*)m40; if (p) p->s04();
    p = (SubObj*)m3c; if (p) p->s04();
    p = (SubObj*)m38; if (p) p->s04();
    p = (SubObj*)m34; if (p) p->s04();
    p = (SubObj*)m30; if (p) p->s04();
    p = (SubObj*)m2c; if (p) p->s04();
    p = (SubObj*)m28; if (p) p->s04();
    p = (SubObj*)m24; if (p) p->s04();
    p = (SubObj*)m20; if (p) p->s04();
    p = (SubObj*)m1c; if (p) p->s04();
    p = (SubObj*)m18; if (p) p->s04();
    p = (SubObj*)m14; if (p) p->s04();
    p = (SubObj*)m10; if (p) p->s08();
    *(void**)((char*)this + 8) = (void*)0x13ec458;
    *(void**)((char*)this + 4) = (void*)0x13eb938;
    *(void**)this = (void*)0x13eb394;
}

// ===========================================================================
// @ 0x00ad75c0
// ===========================================================================
extern "C" void FUN_00832790(void* p);                                // 0x832790
extern "C" void FUN_00811ad0(void* p, int n);                         // 0x811ad0
void CUID::FUN_00ad75c0()
{
    void* self = this;
    if (*(int*)((char*)self + 0x10) != 0) {
        FUN_00832790(*(void**)((char*)self + 0x50));
        SubObj* p = *(SubObj**)((char*)self + 0x50);
        if (p) { *(void**)((char*)self + 0x50) = 0; p->s08(); }
        FUN_00811ad0(*(void**)((char*)self + 0x10), 1);
        SubObj* q = *(SubObj**)((char*)self + 0x10);
        if (q) { *(void**)((char*)self + 0x10) = 0; q->s08(); }
    }
}

// ===========================================================================
// @ 0x00ad7610
// ===========================================================================
extern "C" bool FUN_00685520(int n);                                  // 0x685520
struct CUIWidget80 {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void w40(); virtual void w44(); virtual void w48(); virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68(); virtual void w6c();
    virtual void w70(); virtual void w74(); virtual void w78(); virtual void w7c();
    virtual void w80(int a);              // +0x80
};
void CUID::FUN_00ad7610(int r)
{
    void* self = this;
    if (FUN_00685520(2)) {
        CUIWidget80* w = *(CUIWidget80**)((char*)self + 0x18);
        w->w80(r);
    }
}

// ===========================================================================
// @ 0x00ad7640
// ===========================================================================
void CUID::FUN_00ad7640(int a)
{
    void* self = this;
    if (FUN_00685520(2)) {
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x18) + 0x7c)))(*(void**)((char*)self + 0x18), 1, a);
    }
}

// ===========================================================================
// @ 0x00ad7670
// ===========================================================================
struct CSubtitleSet { void Set(int a, float b, int c, int d, float e); }; // 0x832d50
void CUID::FUN_00ad7670(int a, float b, int c, int d, float e)
{
    void* self = this;
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x14) + 0x7c)))(*(void**)((char*)self + 0x14), 1, 0);
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x1c) + 0x7c)))(*(void**)((char*)self + 0x1c), 1, 1);
    ((CSubtitleSet*)*(void**)((char*)self + 0x50))->Set(a, b, c, d, e);
}

// ===========================================================================
// @ 0x00ad76c0
// ===========================================================================
void CUID::FUN_00ad76c0()
{
    void* self = this;
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x1c) + 0x7c)))(*(void**)((char*)self + 0x1c), 1, 0);
    ((CSubtitleSet*)*(void**)((char*)self + 0x50))->Set(0, 1.0f, 0, 1, 0.0f);
}

// ===========================================================================
// @ 0x00ad76f0
// ===========================================================================
extern "C" void* EA_UTFWin_GetManager();                              // 0x957f30
void CUID::FUN_00ad76f0(int show)
{
    void* self = this;
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x20) + 0x7c)))(*(void**)((char*)self + 0x20), 1, show);
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x2c) + 0x7c)))(*(void**)((char*)self + 0x2c), 1, show);
    if ((char)show != 0) {
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x28) + 0x7c)))(*(void**)((char*)self + 0x28), 1, 0);
        CGUI* m = (CGUI*)EA_UTFWin_GetManager();
        m->g4c(0, *(int*)((char*)self + 0x20));
    }
}

// ===========================================================================
// @ 0x00ad7740
// ===========================================================================
void CUID::FUN_00ad7740(int show)
{
    void* self = this;
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x28) + 0x7c)))(*(void**)((char*)self + 0x28), 1, show);
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x2c) + 0x7c)))(*(void**)((char*)self + 0x2c), 1, show);
    if ((char)show != 0) {
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x20) + 0x7c)))(*(void**)((char*)self + 0x20), 1, 0);
        CGUI* m = (CGUI*)EA_UTFWin_GetManager();
        m->g4c(0, *(int*)((char*)self + 0x28));
    }
}

// ===========================================================================
// @ 0x00ad7790
// ===========================================================================
void CUID::FUN_00ad7790(int show)
{
    void* self = this;
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x30) + 0x7c)))(*(void**)((char*)self + 0x30), 1, show);
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x34) + 0x7c)))(*(void**)((char*)self + 0x34), 1, show);
}

// ===========================================================================
// @ 0x00ad77c0
// ===========================================================================
void CUID::FUN_00ad77c0(int show)
{
    void* self = this;
    if (FUN_00685520(2)) {
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x30) + 0x7c)))(*(void**)((char*)self + 0x30), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x34) + 0x7c)))(*(void**)((char*)self + 0x34), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x38) + 0x7c)))(*(void**)((char*)self + 0x38), 1, show);
    }
}

// ===========================================================================
// @ 0x00ad7810
// ===========================================================================
void CUID::FUN_00ad7810(int show)
{
    void* self = this;
    if (FUN_00685520(2)) {
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x30) + 0x7c)))(*(void**)((char*)self + 0x30), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x34) + 0x7c)))(*(void**)((char*)self + 0x34), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x3c) + 0x7c)))(*(void**)((char*)self + 0x3c), 1, show);
    }
}

// ===========================================================================
// @ 0x00ad7860
// ===========================================================================
void CUID::FUN_00ad7860(int show)
{
    void* self = this;
    if (FUN_00685520(2)) {
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x30) + 0x7c)))(*(void**)((char*)self + 0x30), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x34) + 0x7c)))(*(void**)((char*)self + 0x34), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x40) + 0x7c)))(*(void**)((char*)self + 0x40), 1, show);
    }
}

// ===========================================================================
// @ 0x00ad78b0
// ===========================================================================
void CUID::FUN_00ad78b0(int show)
{
    void* self = this;
    if (FUN_00685520(2)) {
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x30) + 0x7c)))(*(void**)((char*)self + 0x30), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x34) + 0x7c)))(*(void**)((char*)self + 0x34), 1, show);
        (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x44) + 0x7c)))(*(void**)((char*)self + 0x44), 1, show);
    }
}

// ===========================================================================
// @ 0x00ad7900
// ===========================================================================
extern "C" void FUN_008099a0(void* p, int a, int b);                  // 0x8099a0
extern "C" void FUN_00809c50(void* p, int a, int b);                  // 0x809c50
void CUID::FUN_00ad7900(char on)
{
    void* self = this;
    if (on != 0) {
        FUN_008099a0(*(void**)((char*)self + 0x4c), 0, 0);
        *(byte*)((char*)self + 0x54) = 1;
        return;
    }
    if (*(char*)((char*)self + 0x54) != 0) {
        FUN_00809c50(*(void**)((char*)self + 0x4c), 0, 0);
        *(byte*)((char*)self + 0x54) = 0;
    }
}

// ===========================================================================
// @ 0x00ad7940
// ===========================================================================
struct CActionTarget {
    char data[0x30];
    CActionTarget();
};
CActionTarget::CActionTarget()
{
    *(float*)(data + 0x00) = DAT_0167a548;
    *(float*)(data + 0x04) = DAT_0167a54c;
    *(float*)(data + 0x08) = DAT_0167a550;
    *(float*)(data + 0x1c) = 1.0f;
    *(float*)(data + 0x20) = 1.0f;
    *(float*)(data + 0x24) = 1.0f;
    *(float*)(data + 0x28) = 1.0f;
    *(int*)(data + 0x2c) = 0;
    *(float*)(data + 0x0c) = 0.0f;
    *(float*)(data + 0x10) = 0.0f;
    *(float*)(data + 0x14) = 0.0f;
    *(float*)(data + 0x18) = 0.0f;
}
