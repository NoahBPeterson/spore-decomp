// Slice s00ed57e0 : stage/panel callout + mode-update helpers (UI panel).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef          int   s32;

// ------------------------------------------------------------------ retail data
#define G16C7AA4       (*(void**)0x016c7aa4)          // app / scenario global
#define G16065F8       (*(const u8*)0x016065f8)
#define G16065D8       (*(const u32*)0x016065d8)
#define G16065DC       (*(const u32*)0x016065dc)
#define G16065EC       (*(const u32*)0x016065ec)
#define F16C76FC       (*(const float*)0x016c76fc)
#define F16C7700       (*(const float*)0x016c7700)
#define F16C7704       (*(const float*)0x016c7704)
#define F1485720       (*(const float*)0x01485720)     // _HK_REAL_ONE
#define MAT_DEFAULT    ((void*)0x016c76d8)
#define VTBL_13EB90C   ((void*)0x013eb90c)
#define VTBL_13EB844   ((void*)0x013eb844)

// ------------------------------------------------------------------ indirect-call shapes
typedef void  (__thiscall* FnV0)(void*);
typedef void  (__thiscall* FnV1)(void*, void*);
typedef void  (__thiscall* FnV2)(void*, u32, void*);
typedef void  (__thiscall* FnPost)(void*, u32, void*, int);
typedef void* (__thiscall* FnP0)(void*);
typedef void* (__thiscall* FnP1)(void*, u32);
typedef float (__thiscall* FnF0)(void*);
typedef u32   (__thiscall* FnU0)(void*);
typedef void  (__thiscall* FnVis)(void*, int, int);

struct ObjV                            // generic view: thiscall callees as members
{
    // panel / page plumbing
    void  FUN_00ed5330(u32);             // 0x00ed5330  Panel::SetMode
    void  FUN_00ed4c70(int);             // 0x00ed4c70  Panel::Select
    void  FUN_00ed5890(u32);             // 0x00ed5890  page (set page id)
    void  FUN_00ed59e0(u32);             // 0x00ed59e0
    void  FUN_00ed2f30();                // 0x00ed2f30
    void  FUN_00edb6c0();                // 0x00edb6c0
    void  FUN_00ed0660();                // 0x00ed0660  cEditorPage::Shutdown
    void  FUN_00ed0030(u32);             // 0x00ed0030  cEditorPage::Update
    void  FUN_00e02e10();                // 0x00e02e10
    void  FUN_00ee12c0();                // 0x00ee12c0
    void  FUN_00ee3f20(u32);             // 0x00ee3f20
    void  FUN_00ef79d0();                // 0x00ef79d0
    void  FUN_00ef72b0();                // 0x00ef72b0  ScenarioTutorials_ClearPending
    void  FUN_00f190a0();                // 0x00f190a0  cScenarioPlayProgressBar::Reset
    void  FUN_00f44dd0();                // 0x00f44dd0
    // scenario / tutorial glue
    char  FUN_00ec5a60(void*, int, int); // 0x00ec5a60
    char  FUN_00ec4320();                // 0x00ec4320
    int   FUN_00a42730();                // 0x00a42730  GetCurrentGameMode
    void* FUN_00f3d780(void*);           // 0x00f3d780
    float FUN_00f3e910();                // 0x00f3e910
    float FUN_00f325b0();                // 0x00f325b0
    char  FUN_00f41270(int*);            // 0x00f41270  sim (mode out)
    char  FUN_00f3b920();                // 0x00f3b920
    void  FUN_005a7410(float);           // 0x005a7410
    void* FUN_008105b0(u32, int);        // 0x008105b0  cSPUILayout::FindWindowByID
    void  FUN_00811ad0(int);             // 0x00811ad0  cSPUILayout::Shutdown
    void  FUN_005fdf40();                // 0x005fdf40  UI::AchievementNotifier::Update
    // geometry
    void* FUN_00b81630(void*, void*);            // 0x00b81630
    void* FUN_00b7f1f0(void*, void*, void*);     // 0x00b7f1f0  BuildSurfaceOrientation_2
    void  FUN_0041cb40(void*);                   // 0x0041cb40  Matrix3::Assign
};

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

extern void* __cdecl MessageServer();                    // 0x0067dcc0
extern void  __cdecl FUN_00efc8c0(int);                  // 0x00efc8c0  ScenarioTutorials_SetActive
extern void  __cdecl FUN_00571db0(void*, void*, void*, void*, void*);   // 0x00571db0  EA::Messaging::RemoveHandler
extern void* __cdecl FUN_0067cae0();                     // 0x0067cae0
extern void* __cdecl FUN_0059c190(void*, void*);         // 0x0059c190  Matrix3FromQuaternion
extern void* __cdecl PlanetModel();                      // 0x00b3d350  SP::PlanetModel

// MessageBasicRC<5>/SlotMessage posted through the message server (0x40 bytes).
// mData[5] is 5 eight-byte slots: only the low dword of each is used here, and they are
// named scalars so cl does not emit a /GS cookie for the stack object.
struct SlotMsg
{
    void*         mVtbl;        // +0x00
    volatile long mRefCount;    // +0x04
    u32           mD0;          // +0x08  Data[0].lo
    u32           mD0h;         // +0x0c
    u32           mD1;          // +0x10  Data[1].lo
    u32           mD1h;         // +0x14
    u32           mD2;          // +0x18  Data[2].lo
    u32           mD2h;         // +0x1c
    u32           mD3;          // +0x20  Data[3].lo
    u32           mD3h;         // +0x24
    u32           mD4;          // +0x28  Data[4].lo
    u32           mD4h;         // +0x2c
    u32           mId;          // +0x30
    u32           mField34;     // +0x34
    u32           mRCFlags;     // +0x38
    u32           mField3c;     // +0x3c

    SlotMsg(u32 id) : mId(id)
    {
        mVtbl = VTBL_13EB90C;
        _InterlockedExchange(&mRefCount, 0);
        mVtbl = VTBL_13EB844;
        mRCFlags = 0;
    }
    void FUN_00421cf0();        // 0x00421cf0  SlotMessage::Destruct
};

// ------------------------------------------------------------------ geometry locals
struct XV3 { float x, y, z; };
struct XV4 { float x, y, z, w; };
struct XMat33 { float m00, m01, m02, m10, m11, m12, m20, m21, m22; };

struct XLocal                          // block handed to the vtbl+0x18 update call
{
    u16    mFlags;                     // +0x00
    u16    mCount;                     // +0x02
    float  mPosX;                      // +0x04
    float  mPosY;                      // +0x08
    float  mPosZ;                      // +0x0c
    float  mW;                         // +0x10
    XMat33 mRot;                       // +0x14
};



// ------------------------------------------------------------------ functions

// @ 0x00ed57e0
void __fastcall FUN_00ed57e0(void* self_, int dummy, u32* param_2)
{
    char* self = (char*)self_;

    if (*param_2 != 0)
    {
        void* holder = *(void**)(self - 0xfc);
        void* src = holder
                  ? (void*)((FnP1)(*(void***)holder)[0xc / 4])(holder, 0x774c96f)
                  : 0;
        u32 d0 = *(u32*)((char*)src + 8);

        SlotMsg msg(0);
        msg.mD0 = d0;
        msg.mD1 = param_2[1];
        msg.mD2 = param_2[2];
        msg.mD3 = param_2[0];

        void* srv = MessageServer();
        ((FnPost)(*(void***)srv)[0x14 / 4])(srv, 0x774e2dc, &msg, 0);

        msg.FUN_00421cf0();
    }

    ((ObjV*)*(void**)((char*)G16C7AA4 + 0xd4))->FUN_00ef72b0();
}

// @ 0x00ed5890
void __fastcall FUN_00ed5890(void* self_, int dummy, u32 param_2)
{
    char* self = (char*)self_;

    if (param_2 == *(u32*)(self + 0x1c))
        return;

    SlotMsg msg(0x74baf67);
    msg.mD0 = param_2;
    msg.mD1 = *(u32*)(self + 0x1c);

    void* srv = MessageServer();
    ((FnPost)(*(void***)srv)[0x14 / 4])(srv, msg.mId, &msg, 0);

    *(u32*)(self + 0x1c) = param_2;

    msg.FUN_00421cf0();
}

// @ 0x00ed5910
void __fastcall FUN_00ed5910(void* self_)
{
    char* self = (char*)self_;

    switch (*(u32*)(self + 0x58))
    {
    case 2:
        *(u32*)(self + 0x58) = 0;
        return;

    case 5:
        FUN_00efc8c0(0);
        ((ObjV*)*(void**)((char*)G16C7AA4 + 0x78))->FUN_00f190a0();
        ((ObjV*)*(void**)((char*)G16C7AA4 + 0x74))->FUN_00f44dd0();
        *(u32*)(self + 0x58) = 0;
        return;

    case 1:
    case 3:
    case 6:
    case 7:
        ((ObjV*)self)->FUN_00ed5330(0x7eaf738);
        return;

    case 4:
        break;

    default:
        *(u32*)(self + 0x58) = 0;
        return;
    }

    void* owner = *(void**)((char*)G16C7AA4 + 0x1c);
    if (owner != 0 && ((ObjV*)owner)->FUN_00ec5a60(self + 0x48, 1, 0) != 0)
    {
        if (((ObjV*)owner)->FUN_00ec4320() != 0)
            return;
        if (((ObjV*)owner)->FUN_00a42730() == 2)
        {
            ((ObjV*)self)->FUN_00ed5330(0x7eaf738);
            return;
        }
    }

    *(u32*)(self + 0x58) = 0;
}

// @ 0x00ed59e0
void __fastcall FUN_00ed59e0(void* self_, int dummy, u32 mode)
{
    char* self = (char*)self_;
    (void)mode;

    if (*(void**)(self + 0x88) == 0)
        return;

    void* obj = ((ObjV*)*(void**)((char*)G16C7AA4 + 0x74))->FUN_00f3d780(*(void**)(self + 0x90));

    char* src;
    if (obj == 0)
        src = 0;
    else
        src = (char*)((FnP1)(*(void***)obj)[0xc / 4])(obj, 0x1186577);

    float fHeight = ((FnF0)(*(void***)src)[0x74 / 4])(src);

    if (*(void**)(self + 0x88) != 0)
    {
        XLocal local;
        XV3    pos;
        XV4    orient;
        XV4    dirOut;

        XV3* v = (XV3*)((FnP0)(*(void***)src)[0x2c / 4])(src);
        pos.x = v->x; pos.y = v->y; pos.z = v->z;

        XV4* q = (XV4*)((FnP0)(*(void***)src)[0x30 / 4])(src);
        orient = *q;

        void* r = ((ObjV*)PlanetModel())->FUN_00b81630(&dirOut, &pos);
        pos = *(XV3*)r;

        local.mPosX = pos.x;
        local.mPosY = pos.y;
        local.mPosZ = pos.z;
        local.mW = F1485720;
        ((ObjV*)&local.mRot)->FUN_0041cb40(MAT_DEFAULT);
        local.mRot = *(const XMat33*)MAT_DEFAULT;
        local.mFlags = 4;
        local.mCount = 1;

        void* qo = ((ObjV*)PlanetModel())->FUN_00b7f1f0(&dirOut, &pos, &orient);

        XMat33 mat;
        FUN_0059c190(&mat, qo);
        local.mRot = mat;

        local.mFlags = (u16)(local.mFlags | 2);
        local.mCount = (u16)(local.mCount + 2);
        local.mW = fHeight;

        void* target = *(void**)(self + 0x88);
        ((FnV1)(*(void***)target)[0x18 / 4])(target, &local);
    }

    if (*(void**)(self + 0x8c) != 0)
    {
        XLocal local;
        XV3    pos;
        XV4    orient;
        XV4    dirOut;

        XV3* v = (XV3*)((FnP0)(*(void***)src)[0x2c / 4])(src);
        pos.x = v->x; pos.y = v->y; pos.z = v->z;

        XV4* q = (XV4*)((FnP0)(*(void***)src)[0x30 / 4])(src);
        orient = *q;

        void* r = ((ObjV*)PlanetModel())->FUN_00b81630(&dirOut, &pos);
        pos = *(XV3*)r;

        local.mPosX = pos.x;
        local.mPosY = pos.y;
        local.mPosZ = pos.z;
        local.mW = F1485720;
        ((ObjV*)&local.mRot)->FUN_0041cb40(MAT_DEFAULT);
        local.mRot = *(const XMat33*)MAT_DEFAULT;
        local.mFlags = 4;
        local.mCount = 1;

        void* qo = ((ObjV*)PlanetModel())->FUN_00b7f1f0(&dirOut, &pos, &orient);

        XMat33 mat;
        FUN_0059c190(&mat, qo);
        local.mRot = mat;

        local.mFlags = (u16)(local.mFlags | 2);
        local.mCount = (u16)(local.mCount + 2);
        local.mW = fHeight;

        void* target = *(void**)(self + 0x8c);
        ((FnV1)(*(void***)target)[0x18 / 4])(target, &local);
    }
}

// @ 0x00ed63a0
void __fastcall FUN_00ed63a0(void* self_)
{
    char* self = (char*)self_;

    if (*(void**)(self + 0x84) != 0)
        ((FnV1)(*(void***)*(void**)(self + 0x84))[0xc / 4])(*(void**)(self + 0x84), 0);

    ((ObjV*)self)->FUN_00ed4c70(1);

    void* h = *(void**)(self + 0x70);
    if (h != 0)
    {
        *(u32*)(self + 0x70) = 0;
        FUN_00571db0(h, *(void**)(self + 0x74), *(void**)(self + 0x78),
                     *(void**)(self + 0x7c), *(void**)(self + 0x80));
    }

    if (*(void**)(self + 0x44) != 0)
    {
        ((ObjV*)*(void**)(self + 0x44))->FUN_00e02e10();
        void* p = *(void**)(self + 0x44);
        if (p != 0)
        {
            *(u32*)(self + 0x44) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x14) != 0)
    {
        ((ObjV*)*(void**)(self + 0x14))->FUN_00ed2f30();
        void* p = *(void**)(self + 0x14);
        if (p != 0)
        {
            *(u32*)(self + 0x14) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    if (*(void**)(self + 0x28) != 0)
    {
        ((FnV0)(*(void***)*(void**)(self + 0x28))[0x14 / 4])(*(void**)(self + 0x28));
        void* p = *(void**)(self + 0x28);
        if (p != 0)
        {
            *(u32*)(self + 0x28) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    if (*(void**)(self + 0x18) != 0)
    {
        ((ObjV*)*(void**)(self + 0x18))->FUN_00ee12c0();
        void* p = *(void**)(self + 0x18);
        if (p != 0)
        {
            *(u32*)(self + 0x18) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    if (*(void**)(self + 0x2c) != 0)
    {
        ((ObjV*)*(void**)(self + 0x2c))->FUN_00edb6c0();
        void* p = *(void**)(self + 0x2c);
        if (p != 0)
        {
            *(u32*)(self + 0x2c) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x30) != 0)
    {
        ((ObjV*)*(void**)(self + 0x30))->FUN_00ed0660();
        void* p = *(void**)(self + 0x30);
        if (p != 0)
        {
            *(u32*)(self + 0x30) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x34) != 0)
    {
        ((ObjV*)*(void**)(self + 0x34))->FUN_00ed0660();
        void* p = *(void**)(self + 0x34);
        if (p != 0)
        {
            *(u32*)(self + 0x34) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    {
        char* slot = self + 0x38;
        for (int i = 0; i < 2; ++i, slot += 4)
        {
            if (*(void**)slot != 0)
            {
                ((ObjV*)*(void**)slot)->FUN_00ef79d0();
                void* p = *(void**)slot;
                if (p != 0)
                {
                    *(u32*)slot = 0;
                    ((FnV0)(*(void***)p)[4 / 4])(p);
                }
            }
        }
    }

    if (*(void**)(self + 0x40) != 0)
    {
        ((FnV0)(*(void***)*(void**)(self + 0x40))[0x88 / 4])(*(void**)(self + 0x40));
        void* p = *(void**)(self + 0x40);
        if (p != 0)
        {
            *(u32*)(self + 0x40) = 0;
            ((FnV0)(*(void***)p)[4 / 4])(p);
        }
    }

    if (*(void**)(self + 0x24) != 0)
    {
        ((ObjV*)*(void**)(self + 0x24))->FUN_00811ad0(1);
        void* p = *(void**)(self + 0x24);
        if (p != 0)
        {
            *(u32*)(self + 0x24) = 0;
            ((FnV0)(*(void***)p)[8 / 4])(p);
        }
    }

    ((ObjV*)self)->FUN_00ed5890(0xffffffff);
    *(u32*)(self + 0x20) = 0xffffffff;
}

// @ 0x00ed6540
void __fastcall FUN_00ed6540(void* self_, int dummy, int param_2)
{
    char* self = (char*)self_;
    void* sim = *(void**)((char*)G16C7AA4 + 0x74);

    if (*(void**)(self + 0x28) != 0)
        ((FnV1)(*(void***)*(void**)(self + 0x28))[0x1c / 4])(*(void**)(self + 0x28), (void*)param_2);

    if (*(void**)(self + 0x18) != 0)
        ((ObjV*)*(void**)(self + 0x18))->FUN_00ee3f20((u32)param_2);

    if (*(void**)(self + 0x30) != 0)
    {
        float f = ((ObjV*)sim)->FUN_00f3e910();
        ((ObjV*)*(void**)(self + 0x30))->FUN_005a7410(f);
        ((ObjV*)*(void**)(self + 0x30))->FUN_00ed0030((u32)param_2);
    }

    if (*(void**)(self + 0x34) != 0)
    {
        float f = ((ObjV*)*(void**)((char*)G16C7AA4 + 0x18))->FUN_00f325b0();
        ((ObjV*)*(void**)(self + 0x34))->FUN_005a7410(f);
        ((ObjV*)*(void**)(self + 0x34))->FUN_00ed0030((u32)param_2);
    }

    ((ObjV*)self)->FUN_00ed59e0((u32)param_2);

    int mode = 0;
    char haveSim = ((ObjV*)sim)->FUN_00f41270(&mode);
    char simOk = ((ObjV*)sim)->FUN_00f3b920();

    bool visA = ((haveSim != 0) || mode == 4 || mode == 2 || mode == 3) && (simOk != 0);

    void* wnd = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0x6fcb638, 1);
    u32 stateA = ((FnU0)(*(void***)wnd)[0x28 / 4])(wnd);
    if ((u32)((stateA >> 1) & 1) != (u32)visA)
        ((FnVis)(*(void***)wnd)[0x7c / 4])(wnd, 2, visA);

    bool visB = (haveSim != 0) || mode == 4 || mode == 2 || mode == 3 || mode == 5;

    void* wnd2 = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0xbbbb1001, 1);
    u32 stateB = ((FnU0)(*(void***)wnd2)[0x28 / 4])(wnd2);
    if ((u32)((stateB >> 1) & 1) != (u32)visB)
        ((FnVis)(*(void***)wnd2)[0x7c / 4])(wnd2, 2, visB);

    int showA = (G16065F8 != 0 && G16065EC != 0) ? 1 : 0;
    void* wnd3 = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0xb006ef6e, 1);
    if (wnd3 != 0)
        ((FnVis)(*(void***)wnd3)[0x7c / 4])(wnd3, 2, showA);

    int showB = (G16065F8 != 0 && (u32)((G16065DC - G16065D8) >> 2) > G16065EC) ? 1 : 0;
    void* wnd4 = ((ObjV*)*(void**)(self + 0x24))->FUN_008105b0(0xf006efa5, 1);
    if (wnd4 != 0)
        ((FnVis)(*(void***)wnd4)[0x7c / 4])(wnd4, 2, showB);

    ((ObjV*)FUN_0067cae0())->FUN_005fdf40();
}

// ---------------------------------------------------------------------------
// Panel::SyncState  (0x00ed5d70)
// ---------------------------------------------------------------------------

void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00f473a0
inline void* operator new(unsigned int, void* p) { return p; }       // placement new

extern const char kUITagAlloc[];                 // 0x013f6b3c  "UI"
extern const char kComplexityWorldName[];        // 0x01489f7c  "UI/cScenarioComplexityMeter/World"
extern const char kComplexityTerraName[];        // 0x01489f58  "UI/cScenarioComplexityMeter/Terra"
extern const char kChecklistUIName[];            // 0x01489f34  "UI/cScenarioTutorialsChecklistUI"
extern const char kScriptUIName[];               // 0x01489f14  "UI/cScenarioEditModeScriptUI"
extern const char kGlobalOptionsName[];          // 0x01489ef4  "Simulator/cSPUIGlobalOptions"
extern const char kPosseAllocName[];             // 0x01476ab8  "UI/Posse"
extern char       kPosseDatum[];                 // 0x015ac28c
extern char       kMessageHandlerStub[];         // 0x01489d38
extern float      kPosseMaxRange;                // 0x01486ebc

void* __cdecl GetAllocContext();                                            // 0x009512c0
void* __cdecl AllocNamed(u32 size, int align, const char* name, void* ctx); // 0x009512d0


#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PV1 virtual void CAT(_pv, __COUNTER__)();
#define PV5 PV1 PV1 PV1 PV1 PV1
#define PV20 PV5 PV5 PV5 PV5

struct SyncKey { u32 mA, mB, mC; };               // 12-byte resource key

struct IWinS;

class SyncLayout {                                // cSPUILayout
public:
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    SyncLayout();                                                     // 0x00810000
    bool  Init(const SyncKey* key, bool visible, u32 id);             // 0x008120d0
    void  Shutdown(u32 flags);                                        // 0x00811ad0
    void  SetVisibility(int visible);                                 // 0x00810590
    IWinS* FindWindowByID(u32 id, int recursive);                     // 0x008105b0
    u32 mPad[5];                                  // retail size 0x18
};

struct IWinS {
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    PV20 PV20 PV20 PV1 PV1 PV1                    // slots 2..64
    virtual void SetWinProc(void* proc);          // +0x104
};

struct WinProcS { void* mpVtbl; void* mpOwner; }; // 8-byte window proc object at Panel+0x08

struct SyncPage {                                 // cEditorPage
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncPage();                                                       // 0x00ed02c0
    void Init(IWinS* win, void* param);                               // 0x00ed0400
    u32 mPad[0x54 / 4];                           // retail size 0x58
};

struct SyncChecklist {                            // cScenarioTutorialsChecklistUI
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncChecklist();                                                  // 0x00ef7900
    void SelectCategory(IWinS* win, int which);                       // 0x00efb9c0
    u32 mPad[0x34 / 4];                           // retail size 0x38
};

struct SyncScenarioObj {                          // 0xa0 object built by 0x00ed2e40
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    SyncScenarioObj();                                                // 0x00ed2e40
    bool Setup();                                                     // 0x00ed3c00
    u32 mPad[0x9c / 4];                           // retail size 0xa0
};

struct SyncC40 {                                  // 0x40 object built by 0x00ee9180
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    virtual void pv3();                           // +0x0c
    virtual bool Init(int arg);                   // +0x10
    SyncC40();                                                        // 0x00ee9180
    u32 mPad[0x3c / 4];                           // retail size 0x40
};

struct SyncScriptUI {                             // cScenarioEditModeScriptUI
    virtual void pv0();                           // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    SyncScriptUI();                                                   // 0x00edd580
    bool Init();                                                      // 0x00ee3940
    u32 mPad[0x108 / 4];                          // retail size 0x10c
};

struct SyncMeter {                                // 0xe0 object built by 0x00edaf10
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncMeter();                                                      // 0x00edaf10
    void SetWindow(IWinS* win);                                       // 0x00edb4c0
    u32 mPad[0xdc / 4];                           // retail size 0xe0
};

struct SyncOptions {                              // cSPUIGlobalOptions
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    SyncOptions();                                                    // 0x00e00ec0
    u32 mPad[0x54 / 4];                           // retail size 0x58
};

struct SyncPosse {                                // 0x20c object built by 0x00e25710
    virtual int  AddRef();                        // +0x00
    virtual int  Release();                       // +0x04
    PV20 PV5 PV5 PV1                              // slots 2..32
    virtual bool SetDatum(const void* datum);     // +0x84
    PV1 PV1
    virtual void SetRange(float lo, float hi, int a, int b);          // +0x90
    PV5 PV1 PV1 PV1 PV1                           // slots 37..45
    virtual void SetCaption(const wchar_t* text); // +0xb8
    PV1
    virtual void SetFlag(int on);                 // +0xc0
    void SetField1e5(int on);                                         // 0x00e21950
    SyncPosse();                                                      // 0x00e25710
    u32 mPad[0x208 / 4];                          // retail size 0x20c
};

struct SyncWinMgr2 {
    PV20 PV20 PV20                                // slots 0..59
    virtual IWinS* FindWindow(u32 id, int recursive);                 // +0x0f0
};
struct SyncWinMgr {
    virtual void pv0();                           // +0x00
    virtual SyncWinMgr2* GetWindows();            // +0x04
};
SyncWinMgr* __cdecl WindowManager();                                 // 0x0067caa0

struct IMsgServerSync {
    PV5 PV1 PV1 PV1 PV1                           // slots 0..8
    virtual void AddListener(void* object, u32 id);                   // +0x24
};

struct SyncHandlerReg {                           // inline registration block at Panel+0x70
    void* mpServer;                               // +0x70
    void* mpObject;                               // +0x74
    void* mpFunc;                                 // +0x78
    u32   mFlags;                                 // +0x7c
    void* mExtra;                                 // +0x80
};

template <class T> struct SyncRef12 {             // AddRef slot1 / Release slot2
    T* mpObject;
    SyncRef12& operator=(T* q) {
        if (q != mpObject) {
            T* pOld = mpObject;
            if (q) q->AddRef();
            mpObject = q;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
};

template <class T> struct SyncRef01 {             // AddRef slot0 / Release slot1
    T* mpObject;
    SyncRef01& operator=(T* q) {
        if (q != mpObject) {
            T* pOld = mpObject;
            if (q) q->AddRef();
            mpObject = q;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
};

namespace SP {
class cString {
public:
    cString(u32 a, u32 b, const wchar_t* def);                        // 0x006b5770
    ~cString();                                                       // 0x006b5240
    const wchar_t* GetText();                                         // 0x006b55c0
    u32 mPad[5];                                  // retail size 0x14
};
}

struct SyncSim { char mPad[0xd0]; void* mpData; };                    // +0xd0
struct SyncApp { char mPad[0x74]; SyncSim* mpSim; };                  // +0x74
#define SYNC_APP (*(SyncApp**)0x016c7aa4)

struct Panel {
    char        mPad00[8];                        // +0x00
    WinProcS    mWinProc;                         // +0x08
    void*       mpMsgObject;                      // +0x10
    SyncRef12<SyncScenarioObj> mScn;              // +0x14
    SyncRef12<SyncScriptUI>    mScriptUI;         // +0x18
    u32         mPage;                            // +0x1c
    u32         mField20;                         // +0x20
    SyncRef12<SyncLayout>      mLayout;           // +0x24
    SyncRef12<SyncC40>         mC40;              // +0x28
    SyncRef01<SyncMeter>       mMeter;            // +0x2c
    SyncRef01<SyncPage>        mPageWorld;        // +0x30
    SyncRef01<SyncPage>        mPageTerra;        // +0x34
    SyncRef01<SyncChecklist>   mCheck1;           // +0x38
    SyncRef01<SyncChecklist>   mCheck2;           // +0x3c
    SyncRef01<SyncPosse>       mPosse;            // +0x40
    SyncRef01<SyncOptions>     mOptions;          // +0x44
    char        mPad48[0x28];                     // +0x48
    SyncHandlerReg mHandler;                      // +0x70
    char        mPad84[0x10];                     // +0x84
    u8          mField94;                         // +0x94

    void SetPage(u32 page);                       // 0x00ed5890
    bool SyncState();                             // 0x00ed5d70
};

// @ 0x00ed5d70
bool Panel::SyncState()
{
    SyncKey key = { 0x396f69f5, 0x510a95b, 0x40464100 };

    mLayout = new (kUITagAlloc, 0, 0, 0, 0) SyncLayout();
    if (!mLayout->Init(&key, true, 0x2edd95ca)) {
        mLayout->Shutdown(1);
        mLayout = 0;
        return false;
    }

    IWinS* win = mLayout->FindWindowByID(0xffffffff, 1);
    if (win)
        win->SetWinProc(&mWinProc);

    IWinS* w = mLayout->FindWindowByID(0x73bd748, 1);
    if (w) {
        mPageWorld = new (kComplexityWorldName, 0, 0, 0, 0) SyncPage();
        mPageWorld->Init(w, SYNC_APP->mpSim->mpData);
    }

    w = mLayout->FindWindowByID(0x74b85c8, 1);
    if (w) {
        mPageTerra = new (kComplexityTerraName, 0, 0, 0, 0) SyncPage();
        mPageTerra->Init(w, SYNC_APP->mpSim->mpData);
    }

    w = mLayout->FindWindowByID(0x771f0a0, 1);
    if (w) {
        mCheck1 = new (kChecklistUIName, 0, 0, 0, 0) SyncChecklist();
        mCheck1->SelectCategory(w, 0);
    }

    w = mLayout->FindWindowByID(0x7736c78, 1);
    if (w) {
        mCheck2 = new (kChecklistUIName, 0, 0, 0, 0) SyncChecklist();
        mCheck2->SelectCategory(w, 1);
    }

    mScn = new (kUITagAlloc, 0, 0, 0, 0) SyncScenarioObj();
    if (!mScn->Setup())
        mScn = 0;

    mC40 = new (kUITagAlloc, 0, 0, 0, 0) SyncC40();
    if (!mC40->Init(0))
        mC40 = 0;

    w = mLayout->FindWindowByID(0x7108388, 1);
    if (w) {
        mScriptUI = new (kScriptUIName, 0, 0, 0, 0) SyncScriptUI();
        if (!mScriptUI->Init())
            mScriptUI = 0;
    }

    w = mLayout->FindWindowByID(0x272eb68e, 1);
    if (w) {
        mMeter = new (kUITagAlloc, 0, 0, 0, 0) SyncMeter();
        mMeter->SetWindow(w);
    }

    if (mOptions.mpObject == 0)
        mOptions = new (kGlobalOptionsName, 0, 0, 0, 0) SyncOptions();

    mPosse = new (AllocNamed(0x20c, 4, kPosseAllocName, GetAllocContext())) SyncPosse();
    if (!mPosse->SetDatum(kPosseDatum)) {
        mPosse = 0;
    } else {
        SP::cString str(0xefdb68ec, 0x760b242, 0);
        mPosse->SetCaption(str.GetText());
        mPosse->SetRange(0.0f, kPosseMaxRange, 0, 0);
        mPosse->SetFlag(0);
        mPosse->SetField1e5(1);
    }

    IWinS* pw = WindowManager()->GetWindows()->FindWindow(0x774b060, 1);
    if (pw)
        pw->SetWinProc(&mWinProc);

    mHandler.mpServer = MessageServer();
    mHandler.mpObject = &mpMsgObject;
    mHandler.mpFunc = kMessageHandlerStub;
    mHandler.mFlags = 1;
    mHandler.mExtra = 0;
    if (mHandler.mpServer != 0 && mHandler.mpObject != 0)
        ((IMsgServerSync*)mHandler.mpServer)->AddListener(mHandler.mpObject, 0x30c11c7);

    if (mLayout.mpObject != 0)
        mLayout->SetVisibility(0);
    mField94 = 0;
    SetPage(0xffffffff);
    mField20 = 0xffffffff;
    return true;
}