// Slice s00e45760 (batch gold4) -- SP::cSPUITimeline message dispatch plus its
// small UI helpers (property copy, visibility/colour setters, nested layout
// configuration, ctor / Init).  Module flags:
//   /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The retail code views the object through the register the original keeps in
// esi; methods on the base sub-object are reached with an explicit
// `(char*)this - 4` cast (this matches every `lea ecx,[esi-4]` in the
// disassembly).  All offsets below are the retail ones, recovered from this and
// the sibling slice s00e40700.

#include "../../include/types.h"

// Native pointer-sized integer (the code uses void*/int address casts below).
typedef unsigned int uintptr_t;

// ------------------------------------------------------------------ UTFWin model
struct Object {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual void ScalarDeletingDtor();     // +0x08
};

struct Rect  { float x, y, z, w; };
struct Point { float x; float y; };

struct IWindow : Object {
    virtual void pad0c();                              // +0x0c
    virtual IWindow* GetParent();                      // +0x10
    virtual void pad14();                              // +0x14
    virtual void pad18();                              // +0x18
    virtual void pad1c();                              // +0x1c
    virtual void pad20();                              // +0x20
    virtual void pad24();                              // +0x24
    virtual void pad28();                              // +0x28
    virtual void pad2c();                              // +0x2c
    virtual void pad30();                              // +0x30
    virtual const Rect* GetArea();                     // +0x34
    virtual const Rect* GetRealArea();                 // +0x38
    virtual void pad3c();                              // +0x3c
    virtual void pad40();                              // +0x40
    virtual void pad44();                              // +0x44
    virtual void pad48();                              // +0x48
    virtual void pad4c();                              // +0x4c
    virtual void pad50();                              // +0x50
    virtual void pad54();                              // +0x54
    virtual void pad58();                              // +0x58
    virtual void SetShadeColor(uint32_t c);            // +0x5c
    virtual void pad60();                              // +0x60
    virtual void pad64();                              // +0x64
    virtual void pad68();                              // +0x68
    virtual void SetLayoutArea(const Rect& r);         // +0x6c
    virtual void SetLayoutLocation(float x, float y);  // +0x70
    virtual void pad74();                              // +0x74
    virtual void pad78();                              // +0x78
    virtual void SetEnabled(int a, int b);             // +0x7c
    virtual void pad80();                              // +0x80
    virtual void pad84();                              // +0x84
    virtual void pad88();                              // +0x88
    virtual void pad8c();                              // +0x8c
    virtual void pad90();                              // +0x90
    virtual void pad94();                              // +0x94
    virtual void pad98();                              // +0x98
    virtual void pad9c();                              // +0x9c
    virtual void padA0();                              // +0xa0
    virtual void padA4();                              // +0xa4
    virtual void padA8();                              // +0xa8
    virtual void padAc();                              // +0xac
    virtual void padB0();                              // +0xb0
    virtual void padB4();                              // +0xb4
    virtual void padB8();                              // +0xb8
    virtual void padBc();                              // +0xbc
    virtual Point ToGlobalCoordinates(Point p);        // +0xc0
    virtual Point ToLocalCoordinates(Point p);         // +0xc4
    virtual void padC8();                              // +0xc8
    virtual void padCc();                              // +0xcc
    virtual void padD0();                              // +0xd0
    virtual void padD4();                              // +0xd4
    virtual void AddWindow(IWindow* w);                // +0xd8
    virtual void RemoveWindow(IWindow* w);             // +0xdc
};

// IWindow-shaped object whose vtable +0x38 returns a Rect* (the [this+0x54] /
// [this+0x58] "view" objects).
struct IRectOwner : IWindow {
    // vtable +0x38 is IWindow::GetRealArea
};

class cSPUILayout : public Object { public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
    bool     Init();                                        // 0x00828250
    void     FUN_00827fa0(int key, int val);                // 0x00827fa0
    void*    AsInterface(int id);                           // 0x00828020
    IWindow* GetRootWindow();                               // 0x00828100
};

class cSPUIPropertyLayout : public cSPUILayout { public:
    void SetRootWindowId(uint32_t id);                      // 0x00c87bc0
    char InitLayout(int* param);                            // 0x00e462c0
    uint32_t OnLayoutMessage(int a, int* msg);              // 0x00e463d0
};

// ------------------------------------------------------------------ misc types
struct AnimatorS { void Update(); };                        // 0x007f63b0
struct LimitStopwatch {
    bool IsTimeUp();                                        // 0x005ff1c0
};
struct cCameraManager {
    int ActiveControllerIndex();                            // 0x0098f940
};

struct RenderCtx {
    void* Begin2D(void* mode);                              // 0x0095bc10
    void  End2D();                                          // 0x0095bb20
};

// eastl::vector<int>-ish (resize @ 0x007eb820; the element base pointer lives at
// +0x0c, matching the original's `*(int*)(param_2 + 0xc)` element accesses).
struct IntVector { uint8_t pad00[0x0c]; int* begin; int* end; int* cap; void resize(uint32_t n); };

// ------------------------------------------------------------------ callees
extern "C" {
void*  __cdecl SP_WindowManager();                                       // 0x0067caa0
void*  __cdecl SP_MessageServer();                                       // 0x0067dcc0
void*  __cdecl SP_GetCurrentGameMode();                                  // 0x00b5b800
void   __cdecl SP_GetPropertyAsKeyInstance(int obj, int key, void* out); // 0x006a12a0
void   __cdecl SP_GetPropertyAsText(int obj, int key, void* out);        // 0x006a1360
bool   __cdecl GetBoolProperty(int obj, int key, void* out);             // 0x00407190
void   __cdecl SetGlobalProperty(int key, float v);                      // 0x005ca880
float  __cdecl FUN_005a6e00(float v);                                   // 0x005a6e00 Clamp01
void*  __cdecl f_b3d410(int a);                                          // 0x00b3d410
void   __cdecl FUN_00808b20(void* a, void* b, char c);                   // 0x00808b20
void   __cdecl FUN_005e4560(void* a, void* b);                           // 0x005e4560
void*  __cdecl FUN_005e2cb0(void* a);                                    // 0x005e2cb0
void   __cdecl FUN_005e2ca0(void* a);                                    // 0x005e2ca0
void   __cdecl CPL_ctor(void* self);                                     // 0x008286d0
void   __cdecl FUN_00e3b390(void* evt, int a, int b);                    // 0x00e3b390
}

// Globals (retail addresses; contents are all runtime state).
extern float   DAT_01485378;                                // 0x01485378
extern float   DAT_01485720;                                // 0x01485720
extern float   DAT_01477fc0;                                // 0x01477fc0
extern float   DAT_01471064;                                // 0x01471064
extern uint8_t DAT_015a5a85;                                // 0x015a5a85
extern float   DAT_015a5a88;                                // 0x015a5a88
extern float   DAT_015a5a8c;                                // 0x015a5a8c
extern float   DAT_015a5a90;                                // 0x015a5a90
extern int     DAT_015a5b30;                                // 0x015a5b30

// ------------------------------------------------------------------ cSPUITimeline
struct cSPUITimeline {
    uint8_t       pad000[0x0c];             // +0x00
    cSPUILayout*  mpLayout0c;               // +0x0c
    cSPUIPropertyLayout* mpLayout10;        // +0x10
    cSPUIPropertyLayout* mpLayout14;        // +0x14
    uint8_t       pad018[0x08];             // +0x18
    IWindow*      mpWin20;                  // +0x20
    uint8_t       pad024[0x14];             // +0x24
    IWindow*      mpWindow1;                // +0x38
    uint8_t       pad03c[0x0c];             // +0x3c
    IWindow*      mpWindow2;                // +0x48
    uint8_t       pad04c[0x04];             // +0x4c
    void*         mpField50;                // +0x50
    IRectOwner*   mpView54;                 // +0x54
    IRectOwner*   mpView58;                 // +0x58
    uint8_t       pad05c[0x28];             // +0x5c
    float         m_f84;                    // +0x84
    float         m_f88;                    // +0x88
    uint8_t       pad08c[0x1c];             // +0x8c
    uint32_t      m_fieldA8;                // +0xa8
    uint8_t       pad0ac[0x30];             // +0xac
    float         m_f_dc;                   // +0xdc
    uint8_t       mb_e0;                    // +0xe0
    uint8_t       pad0e1[0x03];             // +0xe1
    uint32_t      m_fieldE4;                // +0xe4
    uint8_t       pad0e8[0x20];             // +0xe8
    uint8_t       mb108;                    // +0x108
    uint8_t       pad109[0x77];             // +0x109
    int*          mpArr180;                 // +0x180
    int*          mpArr184;                 // +0x184
    uint8_t       pad188[0xbd];             // +0x188
    uint8_t       mb245;                    // +0x245
    uint8_t       pad246[0x02];             // +0x246
    float         m_f248;                   // +0x248
    uint8_t       pad24c[0x1c];             // +0x24c
    uint8_t       mb268;                    // +0x268
    uint8_t       mb269;                    // +0x269
    uint8_t       pad26a[0x02];             // +0x26a
    float         m_f26c;                   // +0x26c
    float         m_f270;                   // +0x270
    uint8_t       pad274[0xd8];             // +0x274
    LimitStopwatch m_stopwatch;             // +0x34c
    uint8_t       pad350[0x1c];             // +0x350
    uint8_t       mb36c;                    // +0x36c
    uint8_t       mb36d;                    // +0x36d
    uint8_t       pad36e[0xe6];             // +0x36e
    AnimatorS*    mpAnimator;               // +0x454
    uint8_t       pad458[0x30];             // +0x458
    uint8_t       mb488;                    // +0x488

    bool  DoMessage(int cmd, int* msg);                     // 0x00e45760
    float FUN_00e460d0();                                   // 0x00e460d0
    void  FUN_00e46140(void* out);                          // 0x00e46140
    void  FUN_00e46180(void* out);                          // 0x00e46180
    void  GetItemColor(void* out, uint32_t idx);            // 0x00e461c0
    void  SetItemColor(uint32_t idx, unsigned char on);    // 0x00e46210
};

// ------------------------------------------------------------------ cTimelinePanel
// The base sub-object (reached via `(char*)this - 4`); only the callees used by
// DoMessage are declared.
struct cTimelinePanel {
    void  BeginCloseTimeline();                             // 0x00e37970
    bool  FUN_00e37750();                                   // 0x00e37750
    void  FUN_00e37f90(void* out, int idx, int which);      // 0x00e37f90
    void* FUN_00e37e50(int idx, int which);                 // 0x00e37e50
    void  FUN_00e400f0(float v);                            // 0x00e400f0
    bool  FUN_00e3c1a0(void* a, void* b, void* c, void* d,
                       int e, int f, int g, float h);       // 0x00e3c1a0
    void  FUN_00e423a0(int a);                              // 0x00e423a0
    void  FUN_00e45460();                                   // 0x00e45460
    void  FUN_00e3afb0();                                   // 0x00e3afb0
    void  FUN_00e38240();                                   // 0x00e38240
    void  Show(int a);                                      // 0x00e44200
    void  FUN_00e3b390(void* evt, int a, int b);            // 0x00e3b390
    void  FUN_00e37d70(float v);                            // 0x00e37d70
};

static inline cTimelinePanel* BASE(cSPUITimeline* self) {
    return (cTimelinePanel*)((char*)self - 4);
}

// Forward declarations for the free helpers defined below (called before their
// definitions by FUN_00e463d0 / FUN_00e462c0's neighbours).
struct VecContainer;                                        // 0x00e45fe0 (member: IsMember)
struct VisNode;                                             // 0x00e46020 (member: SetVisibleRecursive)
void FUN_00e45e90(int a1, IntVector* out, uint32_t key, int obj);  // 0x00e45e90
struct PropLayoutCtor;                                     // 0x00e46260 (member: Construct)
// OnLayoutMessage / InitLayout are members of cSPUIPropertyLayout (declared above).
// ================================================================== 0x00e45760
// bool SP::cSPUITimeline::DoMessage(int cmd, int* msg)
// @ 0x00e45760
bool cSPUITimeline::DoMessage(int cmd, int* msg)
{
    cTimelinePanel* base = BASE(this);
    uint32_t uVar10 = *(uint32_t*)((char*)msg + 8);
    bool bVar11;

    if (uVar10 < 7) {
        if (uVar10 == 6) {
            if (*(int*)((char*)msg + 0x18) != 1000)
                return false;
            if (base->FUN_00e37750())
                return false;
            if (cmd == (int)(uintptr_t)mpWindow1) {
                m_f270 = *(float*)((char*)msg + 0xc);
                int* piVar2 = (int*)SP_WindowManager();
                ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x58))(piVar2, 1, (int)(uintptr_t)mpWindow1);
                mb268 = 1;
                return false;
            }
            if (cmd != (int)(uintptr_t)mpWindow2)
                return false;
            {
                int* piVar2 = (int*)SP_WindowManager();
                ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x58))(piVar2, 1, (int)(uintptr_t)mpWindow2);
                Point p = *(Point*)((char*)msg + 0xc);
                Point* r = ((Point*(__thiscall*)(void*, Point))*(void**)(*(int*)mpWindow2 + 0xc4))(mpWindow2, p);
                base->FUN_00e400f0(r->x);
                mb269 = 1;
                return false;
            }
        }
        if (uVar10 != 1)
            return false;
        if (*(int*)((char*)msg + 0x10) != 0x1b && *(int*)((char*)msg + 0x10) != 0x54)
            return false;
        if (*(int*)((char*)msg + 0x14) != 0)
            return false;
        bVar11 = mb36d == 0;
    } else {
        if (uVar10 > 0x287259f6u)
            return false;
        if (uVar10 != 0x287259f6u) {
            switch (uVar10 - 7) {
            case 0:
                goto code_r0x00e45bff;
            case 1:
                if (base->FUN_00e37750())
                    return false;
                if (mb268 != 0 && cmd == (int)(uintptr_t)mpWindow1) {
                    m_f26c = (m_f270 - *(float*)((char*)msg + 0xc)) + m_f26c;
                    m_f270 = *(float*)((char*)msg + 0xc);
                }
                if (mb269 == 0)
                    return false;
                if (cmd != (int)(uintptr_t)mpWindow2)
                    return false;
                {
                    Point p = *(Point*)((char*)msg + 0xc);
                    Point* r = ((Point*(__thiscall*)(void*, Point))*(void**)(*(int*)mpWindow2 + 0xc4))(mpWindow2, p);
                    base->FUN_00e400f0(r->x);
                    return false;
                }
            case 2:
                if (base->FUN_00e37750())
                    return false;
                if (cmd != (int)(uintptr_t)mpWindow1 && cmd != (int)(uintptr_t)mpWindow2)
                    return false;
                m_f26c = (float)*(int*)((char*)msg + 0x18) + m_f26c;
                return false;
            case 5:
                if (cmd == (int)(uintptr_t)mpWindow1) {
                    uint8_t* gm = (uint8_t*)SP_GetCurrentGameMode();
                    if (gm != (uint8_t*)0x01654c00)
                        return false;
                    base->FUN_00e423a0(0x14);
                    return false;
                }
                if (mb36c != 0) {
                    if (mb488 == 0) {
                        base->FUN_00e38240();
                        return false;
                    }
                    base->FUN_00e45460();
                    base->FUN_00e3afb0();
                    mpAnimator->Update();
                    return false;
                }
                if (mb36d == 0)
                    return false;
                if (!m_stopwatch.IsTimeUp())
                    return false;
                mb36d = 0;
                base->Show(0);
                {
                    int* ms = (int*)SP_MessageServer();
                    ((void(__thiscall*)(int*, int, int, int))*(void**)(*ms + 0x14))(ms, 0x4471c60, 0, 0);
                }
                {
                    int* ms = (int*)SP_MessageServer();
                    ((void(__thiscall*)(int*, int, int, int))*(void**)(*ms + 0x14))(ms, 0x445f729, 0, 0);
                }
                return false;
            case 6:
                break;   // big body below
            default:
                return false;
            }

            // case 6 -- 0x00e4587b
            if (cmd != (int)(uintptr_t)mpField50)
                return false;
            if (mpField50 == 0)
                return false;
            if (mb36d != 0)
                return false;

            {
                int* piVar2 = (int*)SP_WindowManager();
                int* p2 = (int*)((int*(__thiscall*)(int*))*(void**)(*piVar2 + 4))(piVar2);
                float* pfVar4 = (float*)((float*(__thiscall*)(int*))*(void**)(*p2 + 0x38))(p2);
                float fStack_4c = pfVar4[2] - pfVar4[0];
                mb245 = 0;

                int iVar8 = (int)(mpArr184 - mpArr180);
                uint32_t uStack_58 = (uint32_t)iVar8;
                int iStack_54 = 0;
                if (iVar8 > 0) {
                    uint32_t u = 0;
                    do {
                        int iVar5 = ((cCameraManager*)mpArr180[u])->ActiveControllerIndex();
                        if (iVar5 != 0) {
                            float fStack_38;
                            base->FUN_00e37f90(&fStack_38, u, 0);
                            if (0.0f <= fStack_38) {
                                int* wm = (int*)SP_WindowManager();
                                int* wp = (int*)((int*(__thiscall*)(int*))*(void**)(*wm + 4))(wm);
                                float* rf = (float*)((float*(__thiscall*)(int*))*(void**)(*wp + 0x38))(wp);
                                if (fStack_38 <= rf[2] - rf[0]) {
                                    if ((int)u < (int)uStack_58)
                                        uStack_58 = u;
                                    if (iStack_54 < (int)u)
                                        iStack_54 = (int)u;
                                }
                            }
                        }
                        ++u;
                    } while ((int)u < iVar8);
                }

                float fStack_34 = 0.0f;
                if (mpView58 != 0) {
                    int* pv = (int*)mpView58;
                    float* pfVar4b = (float*)((float*(__thiscall*)(void*, int, int))*(void**)(*pv + 0xc0))(pv, 0, 0);
                    fStack_34 = pfVar4b[1];
                    float fStack_38 = pfVar4b[0];
                    SetGlobalProperty(0x2f304a54, (m_f84 - fStack_38) / fStack_4c);
                    m_f84 = fStack_38;
                    m_f88 = fStack_34;
                }

                RenderCtx* pRVar9 = *(RenderCtx**)((char*)msg + 0x18);
                void* uStack_50 = pRVar9->Begin2D(0);
                int iStack_48 = iStack_54 + 1;
                int j = (int)uStack_58 - 1;
                if (j <= iStack_48) {
                    do {
                        if (j > 0 && j < (int)(mpArr184 - mpArr180)) {
                            int iVar5 = ((cCameraManager*)mpArr180[j])->ActiveControllerIndex();
                            DAT_015a5a85 = iVar5 != 0 ? 1 : 0;
                        }
                        if (DAT_015a5a85 != 0) {
                            float fStack_54 = 1.0f;
                            cCameraManager* pcVar6 = (cCameraManager*)base->FUN_00e37e50(j, 0);
                            if (pcVar6 != 0 && *(int*)((char*)pcVar6 + 0xe4) == (int)0xbeb528cb) {
                                int idx = ((cCameraManager*)pcVar6)->ActiveControllerIndex();
                                if (idx != 0) {
                                    fStack_54 = (float)FUN_005a6e00(*(float*)(*(int*)(idx + 0xc) + 100));
                                }
                            }
                            float fStack_3c, fStack_40, fStack_38;
                            base->FUN_00e37f90(&fStack_38, j, -2);
                            base->FUN_00e37f90(&fStack_3c, j, -1);
                            base->FUN_00e37f90(&uStack_50, j, 0);
                            base->FUN_00e37f90(&fStack_40, j, 1);
                            if (fStack_38 == fStack_40) {
                                fStack_40 = fStack_40 + 300.0f;
                                fStack_3c = fStack_34;
                            }
                            bool cVar1 = base->FUN_00e3c1a0(&fStack_38, &fStack_38, &fStack_38, &fStack_40,
                                                            (int)(uintptr_t)uStack_50, 1, (int)uStack_58, fStack_54);
                            if (cVar1 != 0) {
                                base->FUN_00e3c1a0(&fStack_38, &fStack_38, &fStack_38, &fStack_40,
                                                   (int)(uintptr_t)uStack_50, 0, (int)uStack_58, fStack_54);
                            }
                        }
                        ++j;
                    } while (j <= iStack_48);
                }
                pRVar9->End2D();

                if (mpView58 == 0)
                    return false;
                if (mpView54 == 0)
                    return false;
                if (mb245 != 0)
                    return false;
                {
                    int* pv = (int*)mpView54;
                    float* pfVar4c = (float*)((float*(__thiscall*)(void*))*(void**)(*pv + 0x38))(pv);
                    if (*pfVar4c <= fStack_4c * 0.5f)
                        return false;
                }
                {
                    int* p58 = *(int**)&mpView58;
                    int iVar8b = *p58;
                    float* puVar3 = (float*)((float*(__thiscall*)(int*))*(void**)(iVar8b + 0x38))(p58);
                    ((void(__thiscall*)(void*, float, float))*(void**)(iVar8b + 0x70))(p58, puVar3[0], m_f248);
                }
                return false;
            }
        }
        bVar11 = *(int*)((char*)msg + 0xc) == 0x446e560;
    }
    if (!bVar11)
        return false;
    base->BeginCloseTimeline();
    return true;

code_r0x00e45bff:
    if (*(int*)((char*)msg + 0x18) != 1000)
        return false;
    if (base->FUN_00e37750())
        return false;
    if (cmd == (int)(uintptr_t)mpWindow1) {
        int* piVar2 = (int*)SP_WindowManager();
        ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x5c))(piVar2, 1, (int)(uintptr_t)mpWindow1);
        mb268 = 0;
        return false;
    }
    if (cmd != (int)(uintptr_t)mpWindow2)
        return false;
    {
        int* piVar2 = (int*)SP_WindowManager();
        ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x5c))(piVar2, 1, (int)(uintptr_t)mpWindow2);
        mb269 = 0;
        return false;
    }
}

// ================================================================== 0x00e45e90
// void FUN_00e45e90(int a1, IntVector* out, uint32_t key, int obj)
// Builds a 0x28-byte record into `out` from a property-layout object.
// @ 0x00e45e90
void FUN_00e45e90(int a1, IntVector* out, uint32_t key, int obj)
{
    uint8_t* self = (uint8_t*)a1;
    bool bVar2 = (key == 0x1e4cfa6d) || (key == 0x94995d55u);
    uint32_t uVar1 = *(uint32_t*)(*(int*)(self + 0xc) + 0x2c + (uint32_t)(bVar2 ? 0 : 1) * 4);
    uint32_t uVar4 = 0;
    uint32_t param_3 = 0;
    SP_GetPropertyAsKeyInstance(obj, 0x91ad064, &param_3);

    int param_1 = (int)uVar1;
    if (param_3 < 0xad56080du) {
        if (param_3 == 0xad56080cu) {
            uVar4 = 1;
        } else if (param_3 == 0x2db6dad3u) {
            uVar4 = 5;
        }
    } else if (param_3 == 0xbeb528cbu) {
        uVar4 = 4;
    } else if (param_3 == 0xf71fa311u) {
        uVar4 = 2;
        if (**(int**)(self + 0xc) == 0x7ae0330d) {
            param_1 = 2;
            uVar4 = 1;
        }
    }

    out->resize(0xc);
    int step = (-(uint32_t)bVar2 & 0xfffffffd);
    *(uint32_t*)((char*)out->begin + 0x00) = *(uint32_t*)(*(int*)(self + 0xc) + 8);
    *(uint32_t*)((char*)out->begin + 0x04) = *(uint32_t*)(*(int*)(self + 0xc) + (step + 6) * 4);
    *(uint32_t*)((char*)out->begin + 0x08) = *(uint32_t*)(*(int*)(self + 0xc) + (step + 7) * 4);
    *(uint32_t*)((char*)out->begin + 0x0c) = *(uint32_t*)(*(int*)(self + 0xc) + (step + 8) * 4);
    *(uint32_t*)((char*)out->begin + 0x10) = 0;
    *(uint32_t*)((char*)out->begin + 0x14) = *(uint32_t*)(*(int*)(self + 0xc) + 100);
    *(uint32_t*)((char*)out->begin + 0x18) = uVar4;
    *(uint32_t*)((char*)out->begin + 0x1c) = (uint32_t)param_1;
    *(uint32_t*)((char*)out->begin + 0x20) = 0xffffffffu;
    *(uint32_t*)((char*)out->begin + 0x24) = *(uint32_t*)(*(int*)(self + 0xc) + ((bVar2 ? 0 : 1) + 9) * 4);
}

// ================================================================== 0x00e45fe0
// bool __thiscall FUN_00e45fe0(int id)  -- membership test over [this+0xc0..0xc4)
// @ 0x00e45fe0
class hkVector4 { public: float x, y, z, w; };
struct Vector3  { float x, y, z; };

// Helper struct so the __thiscall membership test (ecx = self) is expressible.
struct VecContainer {
    bool IsMember(int id);                                  // 0x00e45fe0
};
bool VecContainer::IsMember(int id)
{
    int* self = (int*)this;
    int n = (*(int*)((char*)self + 0xc4) - *(int*)((char*)self + 0xc0)) >> 2;
    for (int i = 0; i < n; ++i) {
        if (*(int*)(*(int*)((char*)self + 0xc0) + i * 4) == id)
            return true;
    }
    return false;
}

// ================================================================== 0x00e46020
// void __thiscall FUN_00e46020(char on)  -- visibility fan-out
// @ 0x00e46020
// Helper struct so the __thiscall visibility fan-out (ecx = self) is expressible.
struct VisNode {
    void SetVisibleRecursive(char on);                      // 0x00e46020
};
void VisNode::SetVisibleRecursive(char on)
{
    char* self = (char*)this;
    self[0x6c] = on;
    uint32_t flag = (*(int*)(self + 0xc0) == *(int*)(self + 0xc4)) ? (uint32_t)(uint8_t)on : 0u;
    int* p20 = *(int**)(self + 0x20);
    if (p20 != 0)
        ((void(__thiscall*)(int*, int, uint32_t))*(void**)(*p20 + 0x7c))(p20, 1, flag);
    cSPUILayout* p10 = *(cSPUILayout**)(self + 0x10);
    if (p10 != 0) {
        int* w = (int*)p10->FindWindowByID(0x55541be1, true);
        if (w != 0)
            ((void(__thiscall*)(int*, int, uint32_t))*(void**)(*w + 0x7c))(w, 1, flag);
    }
    cSPUILayout* p14 = *(cSPUILayout**)(self + 0x14);
    if (p14 != 0) {
        int* w = (int*)p14->FindWindowByID(0x355430a0, true);
        if (w != 0)
            ((void(__thiscall*)(int*, int, uint32_t))*(void**)(*w + 0x7c))(w, 1, flag);
    }
    int count = (int)(*(int*)(self + 0xc4) - *(int*)(self + 0xc0)) >> 2;
    int i = 0;
    if (count > 0) {
        int* arr = *(int**)(self + 0xc0);
        do {
            ((VisNode*)*(char**)(arr + i * 4))->SetVisibleRecursive(on);
            ++i;
        } while (i < count);
    }
}

// ================================================================== 0x00e460d0
// float __thiscall cSPUITimeline::FUN_00e460d0()
// @ 0x00e460d0
float cSPUITimeline::FUN_00e460d0()
{
    if (mb_e0 != 0)
        return m_f_dc;
    float v;
    if (*(int*)((char*)this + 0xa8) == 0)
        v = 0.0f;
    else
        v = *(float*)(*(int*)(*(int*)((char*)this + 0xa8) + 0xc) + 4);

    int iVar1 = (int)f_b3d410(0);
    if (iVar1 != 0 && *(int*)((char*)this + 0xe4) != (int)0xbeb528cb) {
        f_b3d410(0);
        ((cTimelinePanel*)this)->FUN_00e37d70(v);
    }
    return v;
}

// ================================================================== 0x00e46140
// void __thiscall cSPUITimeline::FUN_00e46140(void* out)
// @ 0x00e46140
void cSPUITimeline::FUN_00e46140(void* out)
{
    int obj = *(int*)((char*)this + 0x64);
    if (obj != 0) {
        if (mb108 != 0) {
            SP_GetPropertyAsText(obj, 0xd5624e29, out);
            return;
        }
        SP_GetPropertyAsText(obj, 0x66e8f2d2, out);
    }
}

// ================================================================== 0x00e46180
// void __thiscall cSPUITimeline::FUN_00e46180(void* out)
// @ 0x00e46180
void cSPUITimeline::FUN_00e46180(void* out)
{
    int obj = *(int*)((char*)this + 0x64);
    if (obj != 0) {
        if (mb108 != 0) {
            SP_GetPropertyAsText(obj, 0xd5624e2a, out);
            return;
        }
        SP_GetPropertyAsText(obj, 0x74f7a11b, out);
    }
}

// ================================================================== 0x00e461c0
// void __thiscall cSPUITimeline::GetItemColor(hkVector4* out, uint32_t idx)
// @ 0x00e461c0
void cSPUITimeline::GetItemColor(void* outv, uint32_t idx)
{
    float* out = (float*)outv;
    out[0] = DAT_015a5a88;
    out[1] = DAT_015a5a8c;
    out[2] = DAT_015a5a90;
    if (idx <= 2) {
        Vector3* p = (Vector3*)(*(int*)((char*)this + 0x50) + idx * 0xc);
        *(Vector3*)out = *p;
    }
}

// ================================================================== 0x00e46210
// void __thiscall cSPUITimeline::SetItemColor(uint32_t idx, char on)
// @ 0x00e46210
void cSPUITimeline::SetItemColor(uint32_t idx, unsigned char on)
{
    if (idx <= 2 && *(int*)((char*)this + 0xc) != 0) {
        cSPUILayout* lay = *(cSPUILayout**)((char*)this + 0xc);
        int* w = (int*)lay->FindWindowByID(idx + 0x6527160, true);
        if (w != 0) {
            uint32_t n = (uint32_t)(-(int32_t)(on ? 1 : 0));
            uint32_t color = (n & 0x8c8c8cu) + 0xff737373u;
            ((void(__thiscall*)(int*, uint32_t))*(void**)(*w + 0x5c))(w, color);
        }
    }
}

// ================================================================== 0x00e46260
// cSPUIPropertyLayout* __fastcall ctor (ecx = self)
// @ 0x00e46260
struct PropLayoutCtor {
    cSPUIPropertyLayout* Construct();                       // 0x00e46260
};
cSPUIPropertyLayout* PropLayoutCtor::Construct()
{
    cSPUIPropertyLayout* self = (cSPUIPropertyLayout*)this;
    CPL_ctor(self);
    *(uint32_t*)((char*)self + 0x00) = 0x1482370;
    *(uint32_t*)((char*)self + 0x04) = 0x1482360;
    *(uint32_t*)((char*)self + 0x78) = 0;
    *(uint32_t*)((char*)self + 0x7c) = 0;
    *(uint32_t*)((char*)self + 0x80) = 0;
    self->FUN_00827fa0(0x5adf0be7, DAT_015a5b30);
    self->SetRootWindowId(0x94e2c6d2);
    return self;
}

// ================================================================== 0x00e462c0
// char __thiscall cSPUIPropertyLayout::Init(int* param) (ecx = self)
// @ 0x00e462c0
char cSPUIPropertyLayout::InitLayout(int* param)
{
    cSPUIPropertyLayout* self = this;
    char c = self->Init();
    if (c != 0) {
        self->AsInterface(0);
        cSPUILayout* lay = (cSPUILayout*)((char*)self + 0xc);
        int* w;
        int* old;

        w = (int*)lay->FindWindowByID(0x94e2c6d2, true);
        old = *(int**)((char*)self + 0x78);
        if (w != old) {
            if (w != 0)
                ((void(__thiscall*)(int*))*(void**)*w)(w);
            *(int**)((char*)self + 0x78) = w;
            if (old != 0)
                ((void(__thiscall*)(int*))*(void**)(*old + 4))(old);
        }
        if (*(int**)((char*)self + 0x78) != 0 && param != 0) {
            int* p78 = *(int**)((char*)self + 0x78);
            int r = ((int(__thiscall*)(int*))*(void**)(*p78 + 0x10))(p78);
            if (r == 0)
                ((void(__thiscall*)(int*, int))*(void**)(*param + 0xd8))(param, (int)(uintptr_t)p78);
        }
        w = (int*)lay->FindWindowByID(0x674b828, true);
        old = *(int**)((char*)self + 0x7c);
        if (w != old) {
            if (w != 0)
                ((void(__thiscall*)(int*))*(void**)*w)(w);
            *(int**)((char*)self + 0x7c) = w;
            if (old != 0)
                ((void(__thiscall*)(int*))*(void**)(*old + 4))(old);
        }
        if (*(int**)((char*)self + 0x7c) != 0) {
            int* p7c = *(int**)((char*)self + 0x7c);
            ((void(__thiscall*)(int*, int, int))*(void**)(*p7c + 0x7c))(p7c, 1, 0);
        }

        w = (int*)lay->FindWindowByID(0x60c6eb8, true);
        old = *(int**)((char*)self + 0x80);
        if (w != old) {
            if (w != 0)
                ((void(__thiscall*)(int*))*(void**)*w)(w);
            *(int**)((char*)self + 0x80) = w;
            if (old != 0)
                ((void(__thiscall*)(int*))*(void**)(*old + 4))(old);
        }
    }
    return c;
}

// ================================================================== 0x00e463d0
// uint __thiscall cSPUIPropertyLayout::OnMessage(int a, int* msg) (ecx = self)
// @ 0x00e463d0
uint32_t cSPUIPropertyLayout::OnLayoutMessage(int a, int* msg)
{
    uint8_t* self = (uint8_t*)this;
    uint32_t result = 0;
    switch (*(uint32_t*)((char*)msg + 8)) {
    case 6: case 7: case 8: case 9: {
        int v = (int)f_b3d410(0);
        if (*(int*)(v + 0x3c) == 0)
            break;
        int uVar2 = *(int*)((char*)msg + 0xc);
        int* piVar3 = *(int**)(self + 0x20);
        int uVar1 = *(int*)((char*)msg + 0x10);
        int iVar7 = (int)f_b3d410(0);
        int* piVar4 = *(int**)(iVar7 + 0x3c);
        uint32_t loc[8];
        ((void(__thiscall*)(int*, uint32_t*, int, int))*(void**)(*piVar3 + 0xc0))(piVar3, loc, uVar2, uVar1);
        uint32_t loc2[8];
        ((void(__thiscall*)(int*, uint32_t*))*(void**)(*piVar4 + 0xc4))(piVar4, loc2);
        for (int i = 0; i < 7; ++i)
            loc2[i] = *(uint32_t*)((char*)msg + i * 4);
        int iVar8 = (int)f_b3d410(0);
        result = ((uint32_t(__thiscall*)(int*, int, uint32_t*))*(void**)(*(int*)(iVar8 + 4) + 0x18))(*(int**)(iVar8 + 4), *(int*)(iVar8 + 0x3c), loc2);
        break;
    }
    case 0x1b: {
        uint8_t flag = 0;
        result = (uint32_t)GetBoolProperty(*(int*)(self + 0x64), 0x95503503, &flag);
        if ((char)result != 0 && flag != 0) {
            if (*(int*)(self + 0xa4) == 0) {
                int* p1 = *(int**)((char*)msg + 4);
                int v = ((int(__thiscall*)(int*))*(void**)(*p1 + 0x1c))(p1);
                if (v == 0x94e2c6d2) {
                    int* eax = (int*)f_b3d410(1);
                    FUN_00e3b390(eax, (int)(uintptr_t)self, (int)(uintptr_t)p1);
                }
            } else {
                FUN_005e4560(*(void**)(self + 0xa4), *(void**)(self + 0x20));
                cSPUIPropertyLayout* pcVar6 = (cSPUIPropertyLayout*)FUN_005e2cb0(*(void**)(self + 0xa4));
                if (pcVar6 != 0) {
                    void* root = pcVar6->GetRootWindow();
                    FUN_00808b20(*(void**)(self + 0x20), root, 0);
                }
            }
        }
        result &= 0xffffff00u;
        break;
    }
    case 0x1c: {
        uint8_t flag = 0;
        result = (uint32_t)GetBoolProperty(*(int*)(self + 0x64), 0x95503503, &flag);
        if ((char)result != 0 && flag != 0) {
            if (*(int*)(self + 0xa4) != 0) {
                FUN_005e2ca0(*(void**)(self + 0xa4));
                result &= 0xffffff00u;
                break;
            }
            int* p1 = *(int**)((char*)msg + 4);
            int v = ((int(__thiscall*)(int*))*(void**)(*p1 + 0x1c))(p1);
            if (v == 0x94e2c6d2) {
                int* eax = (int*)f_b3d410(0);
                FUN_00e3b390(eax, (int)(uintptr_t)self, (int)(uintptr_t)p1);
            }
        }
        result &= 0xffffff00u;
        break;
    }
    default:
        result &= 0xffffff00u;
        break;
    }
    return result & 0xffffff00u;
}
