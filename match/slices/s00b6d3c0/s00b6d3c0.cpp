// Slice s00b6d3c0 -- 0x00b6d3c0 (2056 bytes): per-frame dispatcher over the world-label event queue.
// It walks every pending queue entry that is armed (+0x50) and, by the kind of the object the entry refers to
// (FUN_00b67c70 -> 0..16), hands the entry's position/flag, the object's name and a few of its properties to
// one of 12 per-kind handlers (spawn a floating label / marker for that kind).  Names are Claude-coined.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };

#define PV(n) virtual void pv##n();

// ---- object interfaces reached through vf+0xc (QueryInterface-like: Cast(id)) ----
struct SubD {                                                   // embedded at ObjD+0x34
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32)
    virtual float V51();                                        // +0xcc
};
struct ObjD {                                                   // id 0x0137e8e0
    int pad_vptr;
    char pad04[0x34 - 4];
    SubD mSub;                                                  // +0x34
    char pad38[0xb1c - 0x38];
    int mY1;                                                    // +0xb1c
    int mY2;                                                    // +0xb20
    float FUN_00c9f330();                                       // 0x00c9f330
};
struct ObjA {                                                   // id 0x0116d858
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual int V22();                                          // +0x58
};
struct ObjC {                                                   // id 0xce9f6639 (creature)
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual bool V53();                                         // +0xd4
};
struct ObjB {                                                   // id 0x4f176642
    int FUN_00c22dc0();                                         // 0x00c22dc0
};
struct Obj {                                                    // the thing a queue entry refers to
    PV(00) PV(01) PV(02)
    virtual void* Cast(uint32_t id);                            // +0x0c
};

void __cdecl EA_Free(void* p);                                    // 0x00f47380 (operator delete[])

// ---- eastl::fixed_string<wchar_t, 35>: begin/end/cap, allocator pad, 36-wchar buffer ----
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      pad;
    wchar_t  mBuffer[36];
    ~WString() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin && mpBegin != mBuffer)
            EA_Free(mpBegin);
    }
};

// ---- empire colour ----
struct cEmpire { Vec3 GetColor(); };                            // 0x00c32cd0 (sret, ret 4)
cEmpire* GetPlayerEmpire();                                     // 0x01021300 (cdecl)

struct Event {
    char pad00[4];
    Obj* mpObj;                                                 // +0x04
    char mFlag;                                                 // +0x08
    float mX;                                                   // +0x0c
    float mY;                                                   // +0x10
    char pad14[0x50 - 0x14];
    int mArmed;                                                 // +0x50
};

struct Mgr {
    char pad00[0x38];
    int f38, f3c;
    char pad40[0x50 - 0x40];
    int f50;                                                    // +0x50
    Event* FUN_00b72230(int* cookie);                           // 0x00b72230 (thiscall, next entry)
};
extern Mgr* g_pMgr;                                             // 0x01687348

extern const Vec3 kLabelColor;                                  // 0x0156b008
extern const wchar_t kEmptyStr[];                               // 0x013ec468

void  FUN_00b6d1d0(int a);                                      // 0x00b6d1d0 (cdecl)
int   FUN_00e31100();                                           // 0x00e31100 (cdecl, GetPriority)
unsigned FUN_00b67c70(Obj* o);                                  // 0x00b67c70 (cdecl, kind 0..16)
int   FUN_00b67b90(Obj* o);                                     // 0x00b67b90 (cdecl)
int   FUN_00b681d0(Obj* o);                                     // 0x00b681d0 (cdecl)
int   FUN_00b68250(Obj* o);                                     // 0x00b68250 (cdecl)
int   FUN_00b682a0(Obj* o);                                     // 0x00b682a0 (cdecl)
float FUN_00b685e0(Obj* o);                                     // 0x00b685e0 (cdecl)
Vec3  FUN_00b677e0(Obj* o);                                     // 0x00b677e0 (cdecl, sret)
WString FUN_00b6baf0(Obj* o);                                   // 0x00b6baf0 (cdecl, sret)

// per-kind handlers (the first group takes the entry in EAX in the original: approximated as arg 1)
bool FUN_00b6a970(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, Vec3 col, int a, int b, float dt);   // 0x00b6a970
void FUN_00b6a9d0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt);   // 0x00b6a9d0
void FUN_00b6adf0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt);   // 0x00b6adf0
void FUN_00b6b0a0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt);   // 0x00b6b0a0
void FUN_00b6aae0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt);   // 0x00b6aae0
void FUN_00b6abc0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, float f1, float f2, int c, int d, float dt);   // 0x00b6abc0
void FUN_00b6cc50(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cc50
void FUN_00b6c870(Event* e, int flag, const Vec2* pos, bool b, float dt);   // 0x00b6c870
void FUN_00b6cde0(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cde0
void FUN_00b6cf70(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cf70
void FUN_00b6d060(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6d060
void FUN_00b6ca10(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6ca10
void FUN_00b6cba0(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cba0
#undef PV

// @ 0x00b6d3c0
void ProcessLabelEvents(float dt)
{
    if (g_pMgr->f38 || g_pMgr->f3c) FUN_00b6d1d0(g_pMgr->f50);
    int cookie = FUN_00e31100();
    for (Event* e = g_pMgr->FUN_00b72230(&cookie); e; e = g_pMgr->FUN_00b72230(&cookie)) {
        if (!e->mArmed) continue;
        char flag = e->mFlag;
        Vec2 pos;
        pos.x = e->mX;
        pos.y = e->mY;
        switch (FUN_00b67c70(e->mpObj)) {
        case 13: {
            Obj* o = e->mpObj;
            FUN_00b6a970(e, flag, &pos, 0.0f, L"Food Pile", FUN_00b677e0(o), FUN_00b682a0(o), 0, dt);
            break;
        }
        case 0:
            FUN_00b6a970(e, flag, &pos, 0.0f, kEmptyStr, kLabelColor, 0, 0, dt);
            break;
        case 10: {
            Obj* o = e->mpObj;
            WString name = FUN_00b6baf0(o);
            FUN_00b6a970(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, GetPlayerEmpire()->GetColor(),
                         FUN_00b67b90(o), 0, dt);
            break;
        }
        case 2: {
            Obj* o = e->mpObj;
            int a = 0;
            if (o) {
                ObjA* r = (ObjA*)o->Cast(0x116d858);
                a = r ? r->V22() : 0;
            }
            WString name = FUN_00b6baf0(e->mpObj);
            FUN_00b6a9d0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(e->mpObj), a,
                         FUN_00b682a0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 4: {
            Obj* o = e->mpObj;
            WString name = FUN_00b6baf0(o);
            FUN_00b6adf0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(o), FUN_00b682a0(o),
                         FUN_00b68250(o), FUN_00b681d0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 5: {
            Obj* o = e->mpObj;
            WString name = FUN_00b6baf0(o);
            FUN_00b6b0a0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(o), FUN_00b682a0(o),
                         FUN_00b68250(o), FUN_00b681d0(o), dt);
            break;
        }
        case 3: {
            bool bv = false;
            if (e->mpObj) {
                ObjC* r = (ObjC*)e->mpObj->Cast(0xce9f6639);
                bv = r ? r->V53() : false;
            }
            Obj* o = e->mpObj;
            int b = 0;
            if (o) {
                ObjB* r = (ObjB*)o->Cast(0x4f176642);
                b = r ? r->FUN_00c22dc0() : 0;
            }
            WString name = FUN_00b6baf0(e->mpObj);
            FUN_00b6aae0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(e->mpObj), b,
                         FUN_00b682a0(o), FUN_00b67b90(o), bv, dt);
            break;
        }
        case 6: {
            Obj* o = e->mpObj;
            ObjD* d1 = o ? (ObjD*)o->Cast(0x137e8e0) : 0;
            float x1 = d1 ? d1->mSub.V51() : 0.0f;
            ObjD* d2 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            float x2 = d2 ? d2->FUN_00c9f330() : 0.0f;
            ObjD* d3 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            int y1 = d3 ? d3->mY1 : 0;
            ObjD* d4 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            int y2 = d4 ? d4->mY2 : -1;
            Obj* oe = e->mpObj;
            WString name = FUN_00b6baf0(oe);
            FUN_00b6abc0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(oe), y2, y1, x2, x1,
                         FUN_00b682a0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 11:
            FUN_00b6cc50(e, flag, &pos, dt);
            break;
        case 12: {
            bool bv = false;
            if (e->mpObj) {
                ObjC* r = (ObjC*)e->mpObj->Cast(0xce9f6639);
                bv = r ? r->V53() : false;
            }
            FUN_00b6c870(e, flag, &pos, bv, dt);
            break;
        }
        case 9:
            FUN_00b6cde0(e, flag, &pos, dt);
            break;
        case 7:
            FUN_00b6cf70(e, flag, &pos, dt);
            break;
        case 8:
            FUN_00b6d060(e, flag, &pos, dt);
            break;
        case 14:
            FUN_00b6ca10(e, flag, &pos, dt);
            break;
        case 16:
            FUN_00b6cba0(e, flag, &pos, dt);
            break;
        case 1:
        case 15:
            break;
        }
    }
}
