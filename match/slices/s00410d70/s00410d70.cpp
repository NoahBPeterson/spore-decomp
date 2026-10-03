// Editor sprite-bake job: destructor, and two methods of the owning editor object
// (a completion callback and a per-frame accounting step).
// Built unoptimized: /Od /Ob1 /arch:SSE.
#include <intrin.h>
#include "types.h"

extern "C" {
extern void* vtbl_Editor_cEditorResource[];
extern void* vtbl_Simulator_cCreatureAbility[];
extern void* vtbl_BakeJob_Final0[];   // 0x013eb928
extern void* vtbl_BakeJob_Final1[];   // 0x013eb924
}

// Message dispatcher singleton (FUN_0067dcc0).
struct MessageManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post3(uint32_t id, uint32_t a, uint32_t b);       // +0x14
    virtual void Post4(uint32_t id, uint32_t a, uint32_t b, uint32_t c); // +0x18
};
MessageManager* __cdecl GetMessageManager();            // 0x0067dcc0

// Base pieces of the bake job (see s004103c0 for the constructor).
struct BakeJobDtor {
    void** vp;                // +0
    void** vp2;               // +4
    uint32_t pad8;            // +8 (refcount)
    bool mbDone;              // +0xC
    ~BakeJobDtor();
};

// @ 0x00410d70
BakeJobDtor::~BakeJobDtor()
{
    vp = vtbl_BakeJob_Final0;
    vp2 = vtbl_BakeJob_Final1;
    if (!mbDone) {
        GetMessageManager()->Post4(0x29d3c4c, 0, 0, 0);
    }
    vp2 = vtbl_Simulator_cCreatureAbility;
    vp = vtbl_Editor_cEditorResource;
}

// ---- helpers for the editor object methods ----
struct CursorSource {          // FUN_0067dd40; slot 47 (+0xbc) fills a pair of ids
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46();
    virtual void GetCurrent(uint32_t* out);
    virtual void q48();
};
CursorSource* __cdecl GetCursorSource();                // 0x0067dd40

struct SlotInfo { uint32_t pad[3]; uint16_t mX; uint16_t mY; };   // mX at +0xc, mY at +0xe
struct SlotTable {             // FUN_0067dda0; slot 6 (+0x18) looks an entry up by key
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5();
    virtual SlotInfo* Lookup(uint32_t lo, uint32_t hi);
};
SlotTable* __cdecl GetSlotTable();                      // 0x0067dda0

// 0x14-byte callback record copied by value into FUN_0046f2a0.
struct Callback {
    uint32_t d[5];
    Callback(const Callback& o);                        // 0x0041eae0
};
struct Request {               // object returned by FUN_00761420
    int Open(int a, int b, uint32_t* out);              // 0x011ef750
    int GetHandle(int a);                               // 0x011f0000
    void Close(uint32_t* h);                            // 0x011ef880
};
struct SlotRef {
    void Bind(uint32_t h, int handle, int c);           // 0x011f0440
};
struct FlagCheck { bool IsSet(); };                     // 0x00526430
Request* __cdecl CreateRequest(uint16_t x, uint16_t y, int a, int b, int c);   // 0x00761420
void __cdecl DestroyRequest(Request* r);                                       // 0x00761110
void __cdecl SubmitCallback(Callback cb, Request* r, int arg);                 // 0x0046f2a0

struct EditorHost {            // object with vtable slot 7 (+0x1c) not needed here
    uint8_t pad0[0x238];
    uint16_t mFlags;           // +0x238
    uint8_t pad1[0x338 - 0x23a];
    uint8_t mCallbackObj[0x400 - 0x338];
    int mCallbackArg;          // +0x400
    uint8_t pad2[0x424 - 0x404];
    bool mbPending;            // +0x424
    bool mbHaveOwner;          // +0x425
    uint8_t pad3[2];
    int mOwner;                // +0x428
    bool OnUpdate(int unused);
};

// @ 0x00410dd0
bool EditorHost::OnUpdate(int)
{
    if (mFlags & 4) {
        int arg;
        int h;
        uint16_t x;
        uint16_t y;
        SlotInfo* info;
        uint32_t key[2];
        uint32_t handle[7];
        Request* req;
        key[0] = 0xffffffff;
        key[1] = 0xffffffff;
        GetCursorSource()->GetCurrent(key);
        info = GetSlotTable()->Lookup(key[0], key[1]);
        y = info->mY;
        x = info->mX;
        req = CreateRequest(x, y, 1, 0x208, 0x15);
        if (req->Open(2, 0, handle)) {
            h = req->GetHandle(0);
            ((SlotRef*)info)->Bind(handle[0], h, 0);
            req->Close(handle);
        }
        if (!((FlagCheck*)mCallbackObj)->IsSet()) {
            arg = mCallbackArg;
            SubmitCallback(*(Callback*)mCallbackObj, req, arg);
        }
        DestroyRequest(req);
    }
    if (mbPending) {
        GetMessageManager()->Post3(0x3fc3f13, 0, 0);
        mbPending = false;
    } else if (!mbHaveOwner || mOwner == 0) {
        GetMessageManager()->Post3(0x29d57f4, 0, 0);
    }
    return true;
}

// ---- per-frame accounting step ----
struct Releasable;
struct OwnerHolder {                 // *(this+0x3f0) points at one of these; its first field is the live object
    struct Target { virtual void v(); } * mpObj;
};
struct HolderTarget {
    virtual void p0();
};
void __fastcall ReleaseHolder(void* p);                // 0x0040f360 (thiscall)

struct RangeVector {                 // 16-byte elements, pointer at +0xc of each
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCap;
    void DestroyRange(void* first, void* last);        // 0x00548690
    int Count() { return (mpEnd - mpBegin) >> 4; }
    void* PtrAt(int i) { return *(void**)(mpBegin + i * 16 + 0xc); }
};
void __cdecl EASTL_allocator_deallocate(void* p);      // 0x00f47380

struct Timer {                       // 0x93a2e0 / 0x93a3a0 helpers
    uint8_t pad[0x14];
    float mScale;
    void Update();                   // 0x0093a2e0
    int64_t Read();                  // 0x0093a3a0
};

struct TimeSource {                  // FUN_0067dd40, slot 10 (+0x28)
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void Tick();
};
TimeSource* __cdecl GetTimeSource();                   // 0x0067dd40

struct EditorHost2 {
    void** vp;                                          // virtual slot 28 (+0x70) = SetPrebaked
    uint8_t pad0[0x228 - 4];
    uint8_t mSub[0x10];                                 // +0x228
    uint16_t mFlags;                                    // +0x238
    uint8_t pad1[2];
    uint32_t mpResource;                                // +0x23c
    uint8_t pad2[0x3f0 - 0x240];
    OwnerHolder* mpHolder;                              // +0x3f0
    uint8_t pad3[0x410 - 0x3f4];
    RangeVector mVec;                                   // +0x410
    uint8_t pad4[0x1114 - 0x41c];
    int mFrameCount;                                    // +0x1114
    uint8_t pad5[0x112c - 0x1118];
    int mBakeCount;                                     // +0x112c
    float mTotalTime;                                   // +0x1130
    float mLastTime;                                    // +0x1134
    Timer mTimerA;                                      // +0x1138
    Timer mTimerB;                                      // +0x1150
    bool OnFrame(int unused);
    void SubStep(void* sub, float b, float a);          // 0x004111e0
    void Finish(int arg);                               // 0x00411890
};

// @ 0x00410f90
bool EditorHost2::OnFrame(int)
{
    if (mpHolder) {
        OwnerHolder* h = mpHolder;
        ((void (__thiscall*)(void*, void*, int))(*(void***)(*(void***)h))[0x16c / 4])(*(void**)h, h, 0);
        OwnerHolder** pp = &mpHolder;
        if (*pp) {
            OwnerHolder* old = *pp;
            *pp = 0;
            if (old) {
                ReleaseHolder(old);
            }
        }
    }
    int i = 0;
    int n = mVec.Count();
    for (; i < n; ++i) {
        void* p = mVec.PtrAt(i);
        EASTL_allocator_deallocate(p);
    }
    mVec.DestroyRange(mVec.mpBegin, mVec.mpEnd);
    mTimerB.Update();
    float a = (float)mTimerB.Read() * mTimerB.mScale;
    float b = (float)mTimerA.Read() * mTimerA.mScale + a;
    mLastTime = b;
    mTotalTime += b;
    ++mBakeCount;
    if (mFlags & 0x40) {
        uint32_t res = mpResource;
        ((void (__thiscall*)(void*, uint32_t, bool, const wchar_t*))vp[0x70 / 4])
            (this, res + 8, (mFlags & 0x80) != 0, L"PreBaked");
    }
    ++mFrameCount;
    GetTimeSource()->Tick();
    SubStep(mSub, b, a);
    Finish(0);
    return true;
}
