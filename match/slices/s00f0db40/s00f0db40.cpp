// Slice s00f0db40: SporeApp HUD / spatial-object update functions.
//
//  00f0db40  cSpatialObject-derived LoadModel wrapper (model flag/attachment setup)
//  00f0dc10  per-frame transform / visibility update for a placeable effect
//  00f0df20  scale+transform message push (visitor style)
//  00f0e040  cCommunity transform push (func54h wrapper)
//  00f0e150  cCommunity transform push (func58h wrapper)
//  00f0e250  small "is-active" predicate, virtual slot 0x28 & 1
//  00f0e2a0  float-range / 2-int / flag constant selector (obfuscated hashing)
//  00f0e380  SP::sUpdateUIThumbnail (avatar UI image / pose refresh)
//  00f0e4a0  HUD visibility switch
//  00f0e520  3-way timer / visibility state machine
//  00f0e6c0  tail call into 0xe14900 when the global mode field is clear
//  00f0e6e0  HUD avatar/craft panel update (float + number strings)
//
// All object members are addressed by byte offset because only a partial PDB is
// available; the offsets are documented per field below.
//
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// vtable call helpers (__thiscall function pointers keep ECX == this and the
// original callee-pops stack shape).
// ---------------------------------------------------------------------------
typedef char     (__thiscall *PF_Char0)(void*);
typedef void     (__thiscall *PF_Void0)(void*);
typedef void     (__thiscall *PF_Void1i)(void*, int);
typedef void     (__thiscall *PF_Void1u)(void*, unsigned);
typedef void     (__thiscall *PF_Void1f)(void*, float);
typedef void     (__thiscall *PF_Void1p)(void*, void*);
typedef void     (__thiscall *PF_Void2ii)(void*, int, int);
typedef void     (__thiscall *PF_Void2pi)(void*, void*, int);
typedef void     (__thiscall *PF_Void2pp)(void*, void*, void*);
typedef void     (__thiscall *PF_Void3ip)(void*, int, void*, int);
typedef void     (__thiscall *PF_Void4)(void*, void*, int, int, int);
typedef void*    (__thiscall *PF_P1u)(void*, unsigned);
typedef void*    (__thiscall *PF_P4)(void*, void*, int, int, int);
typedef void*    (__thiscall *PF_P2pp)(void*, void*, void*);

#define VTOF(p) (*(void***)(p))

// ---------------------------------------------------------------------------
// Globals referenced by this object file.
// ---------------------------------------------------------------------------
extern void*  g_16c7aa4;        // 0x16c7aa4  global app object
extern float  g_16c7fc0;        // 0x16c7fc0  identity matrix
extern float  g_16c7fe4;        // 0x16c7fe4
extern float  g_16c7fe8;        // 0x16c7fe8
extern float  g_16c7fec;        // 0x16c7fec
extern float  g_1485720;        // 0x1485720
extern float  g_1582ff0;        // 0x1582ff0
extern float  g_1582ff4;        // 0x1582ff4
extern float  g_1687a00;        // 0x1687a00
extern float  g_1687a0c;        // 0x1687a0c
extern float  g_1687a10;        // 0x1687a10

// ---------------------------------------------------------------------------
// Math / message types.
// ---------------------------------------------------------------------------
struct Quat { float x, y, z, w; };

struct Matrix33 {
    float m[9];
    void Assign(const void* src);                       // 0x41cb40
};

Matrix33& Matrix3FromQuaternion(Matrix33& out, const Quat& q);   // 0x59c190

// Transform message: +00 flags, +02 sequence, +04 x, +08 y, +0c z, +10 w,
// +14 Matrix33 (36 bytes).
struct XformMsg {
    unsigned short flags;       // +0x00
    unsigned short seq;         // +0x02
    float x, y, z, w;           // +0x04..+0x13
    Matrix33 mat;               // +0x14
    void Ctor();                                        // 0x434040
    void SetPosition(void* v);                          // 0x571d40
};

// ---------------------------------------------------------------------------
// External helpers.
// ---------------------------------------------------------------------------
extern "C" void*         f_ModelManager();              // 0x67dd80
extern "C" void*         f_00eedba0(void* out, void* self);  // 0xeedba0
extern "C" void*         f_006c0200();                  // 0x6c0200
extern "C" int           f_00efc910();                  // 0xefc910 ScenarioTutorials_GetObjectA
extern "C" void*         f_App();                       // 0x67dd10
extern "C" void*         f_NounManager();               // 0xb3d300 SP_NounManager
extern "C" void*         f_GetTriggerMgr();             // 0xb3d4d0
extern "C" char          f_00809970();                  // 0x809970
extern "C" void          f_00d49450();                  // 0xd49450
extern "C" void          f_00d2e4a0(int a, int b);      // 0xd2e4a0
extern "C" void          f_00b6c280();                  // 0xb6c280
extern "C" char          f_SetWindowImage(void* w, void* img, int a); // 0x807bb0
extern "C" void          f_SetNumberString(int n, int hi, char* buf, unsigned size); // 0x881ae0
extern "C" void          f_00e14900Run(void* self);     // 0xe14900

namespace SP {
int GetPropertyT(void* list, unsigned key, int* out);   // 0x40cf10
}

// ---------------------------------------------------------------------------
// External object types (only the members this slice touches are declared).
// ---------------------------------------------------------------------------
struct IModelMgr {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24();
    virtual unsigned w28(unsigned key, int a);          // 0x67dd80 result, slot 0x28
};

struct CSpatialObject {
    char LoadModel(void* param);                        // 0xc8a550
};

struct CVpScale {
    void SetViewportScale(float v);                     // 0xf0d6a0
};

struct CTarget {
    void Run();                                         // 0xe14900
};

struct CCommunityBase {
    void func54h(void* p);                              // 0xc88670
    void func58h(void* p);                              // 0xc886d0
};

struct CGlobalUI {
    void* FindWindowByID(unsigned id);                  // 0xe012b0
    void  SetFloat(unsigned id, float v);               // 0xe012d0
    void  SetVisibility(char v);                        // 0xe01350
    void* GetLayout();                                  // 0x93b6c0
};

struct CLayout {
    void* FindWindowByID(unsigned id, int b);           // 0x8105b0
};

struct CTimerBar {
    void SetVisibility(char v);                         // 0xd2bc90
};

struct CNounMgr {
    void* GetAvatar();                                  // 0xb1fdb0
    void* GetItemID();                                  // 0xb1f9c0
};

struct CAvatar {
    void* GetSome();                                    // 0xc0ee60
    char  IsFlagSet();                                  // 0xc0b7a0
};

struct CPosse {
    void* FindItem(void* item);                         // 0xe24c90
};

struct CCraft {
    void* GetIcon();                                    // 0xc0bc00
};

struct CGameData {
    void* Make();                                       // 0xb18530
};

struct CGameData2 {
    void* Get();                                        // 0xf25190
};

struct CTimer {
    float Get();                                        // 0xbfc490
};

struct IFlagObj {
    virtual void x00(); virtual void x04(); virtual void x08(); virtual void x0c();
    virtual void x10(); virtual void x14(); virtual void x18(); virtual void x1c();
    virtual void x20(); virtual void x24();
    virtual char x28();
};

struct IApp {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
    virtual void a50(); virtual void a54();
    virtual void* GetViewer(void* out, int a, int b, int c);   // slot 0x58
};

struct CViewer {
    void GetCameraLocationInfo(void* out, int a, int b, int c);  // 0x7c3d30
};

struct Img { unsigned a, b, c; };

// ===========================================================================
// 0x00f0db40 -- model flag / attachment setup around cSpatialObject::LoadModel
// ===========================================================================
struct CSpatialEx {
    char m00f0db40(void* param);
};

// @ 0x00f0db40
char CSpatialEx::m00f0db40(void* param)
{
    char* s = (char*)this;
    *(unsigned*)(s + 0x50) |= 8;
    char r = ((CSpatialObject*)s)->LoadModel(param);
    if (*(int*)(s + 0x9c) != 0) {
        void* mm = f_ModelManager();
        char* o0 = *(char**)(s + 0x9c);
        unsigned i0 = ((IModelMgr*)mm)->w28(0x6669387, 0);
        if (i0 < 0x40)
            *(unsigned*)(o0 + 0x44 + (i0 >> 5) * 4) |= 1u << (i0 & 0x1f);
        mm = f_ModelManager();
        char* o1 = *(char**)(s + 0x9c);
        unsigned i1 = ((IModelMgr*)mm)->w28(0x7aa969b, 0);
        if (i1 < 0x40)
            *(unsigned*)(o1 + 0x44 + (i1 >> 5) * 4) |= 1u << (i1 & 0x1f);
        *(unsigned*)(*(int*)(s + 0x9c) + 4) |= 2;
        unsigned tmp[3];
        char* o = *(char**)(s + 0x9c);
        unsigned* res = (unsigned*)f_00eedba0(tmp, s - 0x34);
        *(unsigned*)(o + 0x4c) = res[0];
        *(unsigned*)(o + 0x50) = res[1];
        *(unsigned*)(o + 0x54) = res[2];
    }
    return r;
}

// ===========================================================================
// 0x00f0dc10 -- per-frame transform / visibility update
// ===========================================================================
struct CPlaceableUpdate {
    void m00f0dc10();
};

// @ 0x00f0dc10
void CPlaceableUpdate::m00f0dc10()
{
    char* s = (char*)this;
    int mode = *(int*)((char*)g_16c7aa4 + 0xcc);
    if (mode == 2 && *(int*)(s + 0xd0) != 0)
        *(unsigned*)(*(int*)(s + 0xd0) + 4) &= ~1u;

    int obj = (int)f_006c0200();
    if (obj == 0)
        return;

    if (*(char*)(s + 0x120) == 0 && *(int*)(s + 0xd0) != 0) {
        SP::GetPropertyT(*(void**)(*(int*)(s + 0xd0) + 0x90), 0x2a907b8, (int*)(s + 0x14c));
        *(char*)(s + 0x120) = 1;
    }
    if (*(int*)(s + 0x14) == 0)
        return;
    if (*(int*)(s + 0xd0) == 0)
        return;

    char c5 = ((PF_Char0)VTOF(*(void**)(s + 0x14))[0x14 / 4])(*(void**)(s + 0x14));

    int host = *(int*)(s + 0xd0);
    unsigned tmp;
    unsigned* res = (unsigned*)f_00eedba0(&tmp, s);
    *(unsigned*)(host + 0x4c) = res[0];
    *(unsigned*)(host + 0x50) = res[1];
    *(unsigned*)(host + 0x54) = res[2];

    if (*(float*)(s + 0x124) != *(float*)(obj + 0x1e4))
        ((CVpScale*)s)->SetViewportScale(*(float*)(obj + 0x1e4));
    if (*(float*)(s + 0x98) != *(float*)(obj + 0x20))
        ((PF_Void1f)VTOF(*(void**)(s + 0x34))[0x40 / 4])(*(void**)(s + 0x34), *(float*)(obj + 0x20));

    char c6 = *(char*)(s + 0xac);
    char stale = 0;
    if (mode == 1) {
        stale = 1;
        if (f_00efc910() != obj)
            stale = 0;
    }

    void* app = f_App();
    float loc[3];
    void* viewer = ((IApp*)app)->GetViewer(loc, 0, 0, 0);
    ((CViewer*)viewer)->GetCameraLocationInfo(loc, 0, 0, 0);

    float dx = loc[0] - *(float*)(s + 0x38);
    float dy = loc[1] - *(float*)(s + 0x3c);
    float dz = loc[2] - *(float*)(s + 0x40);
    float dist = sqrtf(dx * dx + dy * dy + dz * dz);

    char b4 = (*(char*)(s + 0x11c) != 0) && (c6 == 0);
    char b13 = (mode == 1);
    if (dist > *(float*)(s + 0x14c)) {
        b4 = 0;
        b13 = 0;
    }

    if (*(char*)(s + 0x11e) != 0 &&
        ((*(char*)(s + 0x11d) == 0 && stale != 0) ||
         (*(char*)(s + 0x11f) == 0 && c5 != 0))) {
        ((PF_Void1i)VTOF(*(void**)(s + 0x118))[0xc / 4])(*(void**)(s + 0x118), b13);
        *(char*)(s + 0x121) = 0;
    }

    void* vis = *(void**)(s + 0x118);
    if (vis != 0) {
        char r = ((PF_Char0)VTOF(vis)[0x10 / 4])(vis);
        if (!b4 && r != 0) {
            if (*(char*)(s + 0x11e) == 0) {
                ((PF_Void1i)VTOF(vis)[0xc / 4])(vis, b13);
            } else if (*(char*)(s + 0x121) != 0) {
                goto done;
            }
        } else {
            if (*(char*)(s + 0x11e) != 0 && *(char*)(s + 0x121) != 0)
                goto done;
        }
        if (b4 && r == 0) {
            *(char*)(s + 0x121) = 1;
            XformMsg msg;
            msg.Ctor();
            *(unsigned short*)((char*)&msg + 2) += 1;
            msg.w = *(float*)(s + 0x98);
            msg.SetPosition((void*)(s + 0x38));
            Matrix33 m;
            msg.mat = Matrix3FromQuaternion(m, *(Quat*)(s + 0x44));
            msg.flags |= 2;
            msg.seq++;
            ((PF_Void1p)VTOF(vis)[0x14 / 4])(vis, &msg);
            ((PF_Void3ip)VTOF(vis)[0x44 / 4])(vis, 0x15, (char*)s + 0x98, 1);
            ((PF_Void1i)VTOF(vis)[0x8 / 4])(vis, 0);
        }
    }
done:
    *(char*)(s + 0x11f) = c5;
    *(char*)(s + 0x11d) = stale;
}

// ===========================================================================
// 0x00f0df20 -- scale/transform message push
// ===========================================================================
struct CPlaceableScale {
    void m00f0df20(float v);
};

// @ 0x00f0df20
void CPlaceableScale::m00f0df20(float v)
{
    char* s = (char*)this;
    *(float*)(s + 0x64) = v;
    *(float*)(s + 0x7c) = v;
    if (*(void**)(s + 0xe4) != 0 &&
        ((PF_Char0)VTOF(*(void**)(s + 0xe4))[0x10 / 4])(*(void**)(s + 0xe4))) {
        XformMsg msg;
        msg.flags = 0;
        msg.seq = 0;
        msg.x = g_16c7fe4;
        msg.y = g_16c7fe8;
        msg.z = g_16c7fec;
        msg.w = g_1485720;
        msg.mat.Assign(&g_16c7fc0);

        msg.flags |= 4;
        msg.seq += 2;
        msg.x = *(float*)(s + 4);
        msg.y = *(float*)(s + 8);
        msg.z = *(float*)(s + 0xc);
        msg.w = v;
        Matrix33 m;
        msg.mat = Matrix3FromQuaternion(m, *(Quat*)(s + 0x10));
        msg.flags |= 2;
        msg.seq++;
        ((PF_Void1p)VTOF(*(void**)(s + 0xe4))[0x14 / 4])(*(void**)(s + 0xe4), &msg);
        ((PF_Void3ip)VTOF(*(void**)(s + 0xe4))[0x44 / 4])(*(void**)(s + 0xe4), 0x15, (char*)s + 0x64, 1);
    }
}

// ===========================================================================
// 0x00f0e040 -- cCommunity transform push (func54h)
// ===========================================================================
struct CCommunity54 {
    void m00f0e040(void* param);
};

// @ 0x00f0e040
void CCommunity54::m00f0e040(void* param)
{
    char* s = (char*)this;
    ((CCommunityBase*)s)->func54h(param);
    *(char*)(s + 0xe8) = 1;
    if (*(void**)(s + 0xe4) != 0 &&
        ((PF_Char0)VTOF(*(void**)(s + 0xe4))[0x10 / 4])(*(void**)(s + 0xe4))) {
        XformMsg msg;
        msg.flags = 0;
        msg.seq = 0;
        msg.x = g_16c7fe4;
        msg.y = g_16c7fe8;
        msg.z = g_16c7fec;
        msg.w = g_1485720;
        msg.mat.Assign(&g_16c7fc0);

        msg.flags |= 4;
        msg.seq += 2;
        msg.x = *(float*)(s + 4);
        msg.y = *(float*)(s + 8);
        msg.z = *(float*)(s + 0xc);
        msg.w = *(float*)(s + 0x64);
        Matrix33 m;
        msg.mat = Matrix3FromQuaternion(m, *(Quat*)(s + 0x10));
        msg.flags |= 2;
        msg.seq++;
        ((PF_Void1p)VTOF(*(void**)(s + 0xe4))[0x14 / 4])(*(void**)(s + 0xe4), &msg);
    }
}

// ===========================================================================
// 0x00f0e150 -- cCommunity transform push (func58h)
// ===========================================================================
struct CCommunity58 {
    void m00f0e150(void* param);
};

// @ 0x00f0e150
void CCommunity58::m00f0e150(void* param)
{
    char* s = (char*)this;
    ((CCommunityBase*)s)->func58h(param);
    if (*(void**)(s + 0xe4) != 0 &&
        ((PF_Char0)VTOF(*(void**)(s + 0xe4))[0x10 / 4])(*(void**)(s + 0xe4))) {
        XformMsg msg;
        msg.flags = 0;
        msg.seq = 0;
        msg.x = g_16c7fe4;
        msg.y = g_16c7fe8;
        msg.z = g_16c7fec;
        msg.w = g_1485720;
        msg.mat.Assign(&g_16c7fc0);

        msg.flags |= 4;
        msg.seq += 2;
        msg.x = *(float*)(s + 4);
        msg.y = *(float*)(s + 8);
        msg.z = *(float*)(s + 0xc);
        msg.w = *(float*)(s + 0x64);
        Matrix33 m;
        msg.mat = Matrix3FromQuaternion(m, *(Quat*)(s + 0x10));
        msg.flags |= 2;
        msg.seq++;
        ((PF_Void1p)VTOF(*(void**)(s + 0xe4))[0x14 / 4])(*(void**)(s + 0xe4), &msg);
    }
}

// ===========================================================================
// 0x00f0e250 -- is-active predicate
// ===========================================================================
// @ 0x00f0e250
char m00f0e250(IFlagObj* p)
{
    if (p != 0)
        return p->x28() & 1;
    return 0;
}

// ===========================================================================
// 0x00f0e2a0 -- float-range / int / flag constant selector
// ===========================================================================
// @ 0x00f0e2a0
int m00f0e2a0(float a, int b, char c)
{
    bool b1 = true;
    bool b2 = false;
    if (a > g_1582ff0) {
        b1 = false;
        if (!(a > g_1582ff4))
            b2 = true;
    }
    if (c == 0) {
        switch (b) {
        case 1:
            if (b1)
                return 0xb69dc16a;
            return (-(int)b2 & 0x879b0692) + 0xae79fece;
        case 2:
            break;
        default:
            if (b1)
                return 0x4ccc8e63;
            return (-(int)b2 & 0x60e181dc) + 0x8fbc1ed7;
        }
    } else {
        switch (b) {
        case 1:
            if (b1)
                return 0xa231da2f;
            return (-(int)b2 & 0xd8ed2874) + 0x7d2bf7a3;
        case 2:
            break;
        default:
            if (b1)
                return 0xb490e2ec;
            return (-(int)b2 & 0x2917cb66) + 0x59861ae4;
        }
    }
    if (b1)
        return 0x3751ccea;
    return (-(int)b2 & 0x22551592) + 0x2f2e0a4e;
}

// ===========================================================================
// 0x00f0e380 -- SP::sUpdateUIThumbnail
// ===========================================================================
struct CHudThumbnail {
    void m00f0e380(char param);
};

// @ 0x00f0e380
void CHudThumbnail::m00f0e380(char param)
{
    char* s = (char*)this;
    void* nm = f_NounManager();
    void* av = ((CNounMgr*)nm)->GetAvatar();
    int   e = *(int*)((char*)av + 0xb20);
    Img img = *(Img*)(e + 0x504);
    img.b = 0x2f7d0004;
    void* w = ((CGlobalUI*)*(void**)(s + 0x5c))->FindWindowByID(0x3d99151);
    f_SetWindowImage(w, &img, -1);

    void* pose = *(void**)(s + 0x60);
    if (pose != 0) {
        struct ItemVec { void* begin; void* end; };
        ItemVec* v = (ItemVec*)((CNounMgr*)f_NounManager())->GetItemID();
        char* it = (char*)v->begin;
        char* end = (char*)v->end;
        for (; it != end; it += 4) {
            void* item = *(void**)it;
            if (((PF_Char0)VTOF(item)[0xd0 / 4])(item)) {
                void* p = ((CPosse*)pose)->FindItem(item);
                if (p != 0) {
                    Img im2 = *(Img*)(*(int*)((char*)item + 0xb20) + 0x504);
                    im2.b = 0x2f7d0004;
                    ((PF_Void2pi)VTOF(p)[0x90 / 4])(p, &im2, 0);
                }
            }
        }
    }

    f_00d49450();
    if (param == 0) {
        char r = ((CAvatar*)av)->IsFlagSet();
        f_00d2e4a0(r == 0, 0);
    }
}

// ===========================================================================
// 0x00f0e4a0 -- HUD visibility switch
// ===========================================================================
struct CHudVisibility {
    void m00f0e4a0(int v);
};

// @ 0x00f0e4a0
void CHudVisibility::m00f0e4a0(int v)
{
    char* s = (char*)this;
    if (*(void**)(s + 0x5c) != 0)
        ((CGlobalUI*)*(void**)(s + 0x5c))->SetVisibility((char)v);

    void* p = *(void**)(s + 0x60);
    if (p != 0) {
        int b = 0;
        if ((char)v != 0) {
            int n = (*(int*)((char*)p + 0xa8) - *(int*)((char*)p + 0xa4)) >> 3;
            if ((unsigned)n > 0)
                b = 1;
        }
        ((PF_Void1i)VTOF(p)[0xc0 / 4])(p, b);
    }

    if ((char)v == 0)
        f_00b6c280();
    ((CTimerBar*)(s + 0xb0))->SetVisibility((char)v);

    void* q = *(void**)(s + 0x2e0);
    if (q != 0) {
        void* t = (char*)q + 4;
        ((PF_Void2ii)VTOF(t)[0x7c / 4])(t, 1, v);
    }
    *(char*)(s + 0x59) = (char)v;
}

// ===========================================================================
// 0x00f0e520 -- 3-way timer / visibility state machine
// ===========================================================================
struct CHudTimerVis {
    void m00f0e520(void* param);
};

// @ 0x00f0e520
void CHudTimerVis::m00f0e520(void* param)
{
    char* s = (char*)this;
    char* p = (char*)param;
    if (*(char*)(p + 0xb5e) == 0) {
        void* tm = f_GetTriggerMgr();
        int st = *(int*)((char*)tm + 0x2c);
        if (st != 1 && st != 2 && f_00809970() == 0) {
            float m = ((CTimer*)(p + 0x5a8))->Get() * g_1687a00;
            if (m < g_1687a10) {
                void* v140 = *(void**)(s + 0x140);
                void* v144 = *(void**)(s + 0x144);
                if (((PF_Char0)VTOF(v140)[0x10 / 4])(v140))
                    ((PF_Void1i)VTOF(v140)[0xc / 4])(v140, 0);
                if (((PF_Char0)VTOF(v144)[0x10 / 4])(v144))
                    return;
                ((PF_Void1i)VTOF(v144)[0x8 / 4])(v144, 0);
                return;
            }
            if (((CTimer*)(p + 0x5a8))->Get() * g_1687a00 < g_1687a0c) {
                void* v140 = *(void**)(s + 0x140);
                void* v144 = *(void**)(s + 0x144);
                if (!((PF_Char0)VTOF(v140)[0x10 / 4])(v140))
                    ((PF_Void1i)VTOF(v140)[0x8 / 4])(v140, 0);
                if (((PF_Char0)VTOF(v144)[0x10 / 4])(v144))
                    ((PF_Void1i)VTOF(v144)[0xc / 4])(v144, 0);
                return;
            }
        }
    }
    {
        void* v140 = *(void**)(s + 0x140);
        void* v144 = *(void**)(s + 0x144);
        if (((PF_Char0)VTOF(v140)[0x10 / 4])(v140))
            ((PF_Void1i)VTOF(v140)[0xc / 4])(v140, 0);
        if (((PF_Char0)VTOF(v144)[0x10 / 4])(v144))
            ((PF_Void1i)VTOF(v144)[0xc / 4])(v144, 0);
    }
}

// ===========================================================================
// 0x00f0e6c0 -- tail call when the global mode field is clear
// ===========================================================================
struct CHudTail {
    void m00f0e6c0();
};

// @ 0x00f0e6c0
void CHudTail::m00f0e6c0()
{
    if (*(int*)((char*)g_16c7aa4 + 0xd0) == 0)
        ((CTarget*)*(void**)((char*)this + 0x148))->Run();
}

// ===========================================================================
// 0x00f0e6e0 -- HUD avatar / craft panel update
// ===========================================================================
struct CHudCraftPanel {
    void m00f0e6e0();
};

// @ 0x00f0e6e0
void CHudCraftPanel::m00f0e6e0()
{
    char* s = (char*)this;
    void* nm = f_NounManager();
    void* av = ((CNounMgr*)nm)->GetAvatar();
    void* obj = ((CAvatar*)av)->GetSome();

    void* craft = 0;
    if (obj != 0)
        craft = ((PF_P1u)VTOF(obj)[0x5c / 4])(obj, 0xd0036e08);

    if (*(void**)(s + 0x2dc) != obj) {
        void* old = *(void**)(s + 0x2dc);
        if (obj != old) {
            if (obj != 0)
                ((PF_Void0)VTOF(obj)[0x60 / 4])(obj);
            *(void**)(s + 0x2dc) = obj;
            if (old != 0)
                ((PF_Void0)VTOF(old)[0x64 / 4])(old);
        }
        if (obj == 0) {
            CLayout* lay = (CLayout*)((CGlobalUI*)*(void**)(s + 0x5c))->GetLayout();
            void* w = lay->FindWindowByID(0x7bb7db1, 1);
            ((PF_Void2ii)VTOF(w)[0x7c / 4])(w, 1, 0);
        } else {
            void* w = ((CGlobalUI*)*(void**)(s + 0x5c))->FindWindowByID(0x7bb7db1);
            ((PF_Void2ii)VTOF(w)[0x7c / 4])(w, 1, 1);

            Img img;
            img.a = 0;
            img.b = 0;
            img.c = 0;
            char flag = 0;
            unsigned* src;
            if (craft != 0) {
                src = (unsigned*)((CCraft*)craft)->GetIcon();
            } else {
                unsigned tmp = 0;
                void* r = ((PF_P2pp)VTOF(obj)[0xc / 4])(obj, &tmp, &flag);
                void* gd = ((CGameData*)r)->Make();
                src = (unsigned*)((CGameData2*)gd)->Get();
            }
            img.a = src[0];
            img.b = src[1];
            img.c = src[2];
            if (img.b == 0xb1b104)
                img.c = 0x65928944;
            img.b = 0x2f7d0004;

            void* wi = ((CGlobalUI*)*(void**)(s + 0x5c))->FindWindowByID(0x7bb7e5a);
            f_SetWindowImage(wi, &img, -1);
            ((PF_Void1u)VTOF(wi)[0x5c / 4])(wi, flag ? 0x77ffffff : 0xffffffff);

            void* w2 = ((CGlobalUI*)*(void**)(s + 0x5c))->FindWindowByID(0x7bb7e31);
            ((PF_Void2ii)VTOF(w2)[0x7c / 4])(w2, 1, craft ? 1 : 0);
        }
    }

    if (*(void**)(s + 0x2dc) == 0)
        return;

    if (craft != 0) {
        float f = *(float*)((char*)craft + 0xe58) / *(float*)((char*)craft + 0xe5c);
        ((CGlobalUI*)*(void**)(s + 0x5c))->SetFloat(0x7bb7e48, f);

        CLayout* lay = (CLayout*)((CGlobalUI*)*(void**)(s + 0x5c))->GetLayout();
        void* w = lay->FindWindowByID(0x7bb7e31, 1);
        if (w != 0)
            ((PF_Void2ii)VTOF(w)[0x7c / 4])(w, 2, f * 100.0f < g_1687a0c);

        float f2 = *(float*)((char*)craft + 0xe58);
        int n = (int)f2;
        if ((float)n < f2)
            n++;

        lay = (CLayout*)((CGlobalUI*)*(void**)(s + 0x5c))->GetLayout();
        void* w3 = lay->FindWindowByID(0x7bb7e3e, 1);
        if (w3 != 0) {
            char buf[0x20];
            f_SetNumberString(n, n >> 31, buf, 0x20);
            ((PF_Void1p)VTOF(w3)[0x80 / 4])(w3, buf);
        }
    }

    {
        float t = ((CTimer*)*(void**)(s + 0x2dc))->Get();
        ((CGlobalUI*)*(void**)(s + 0x5c))->SetFloat(0x7bb7dec, t);

        CLayout* lay = (CLayout*)((CGlobalUI*)*(void**)(s + 0x5c))->GetLayout();
        void* w = lay->FindWindowByID(0x7bb7dc2, 1);
        if (w != 0)
            ((PF_Void2ii)VTOF(w)[0x7c / 4])(w, 2, t * 100.0f < g_1687a0c);

        float f3 = *(float*)(*(int*)(s + 0x2dc) + 0x38);
        int n = (int)f3;
        if ((float)n < f3)
            n++;

        lay = (CLayout*)((CGlobalUI*)*(void**)(s + 0x5c))->GetLayout();
        void* w2 = lay->FindWindowByID(0x7bb7dd4, 1);
        if (w2 != 0) {
            char buf[0x20];
            f_SetNumberString(n, n >> 31, buf, 0x20);
            ((PF_Void1p)VTOF(w2)[0x80 / 4])(w2, buf);
        }
    }
}
