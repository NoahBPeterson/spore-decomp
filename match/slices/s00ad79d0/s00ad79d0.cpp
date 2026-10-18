// Slice s00ad79d0 -- Simulator screen / camera-info / editor-resource glue.
//
//   * 0x00ad79d0  camera-info initialiser (two vectors)
//   * 0x00ad7a30  camera-info default constructor
//   * 0x00ad7af0..0x00ad7b70  camera-info accessors (delegate through +0x2c)
//   * 0x00ad7b90  camera-info location fetch
//   * 0x00ad7c30 / 0x00ad7ca0  editor-resource ctor / copy ctor
//   * 0x00ad7d40..0x00ad7df0  simulator screen teardown/CinematicState helpers
//   * 0x00ad7e20..0x00ad7e90  modal-window helpers
//   * 0x00ad7ec0 / 0x00ad7f00  intrusive-pointer assign / camera-info assign
//   * 0x00ad81b0  filter-copy over an array of intrusive pointers
//   * 0x00ad8280 / 0x00ad8300 / 0x00ad87d0  screen ctor / init / show
//   * 0x00ad8960 / 0x00ad89b0  screen deleting dtor / transform submission
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>
#include <intrin.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

// ------------------------------------------------------------------ thiscall vtable thunks
typedef void  (__thiscall *TC_v0)(void*);
typedef void* (__thiscall *TC_p0)(void*);
typedef float (__thiscall *TC_f0)(void*);
typedef int   (__thiscall *TC_i0)(void*);
typedef char  (__thiscall *TC_c0)(void*);
typedef void  (__thiscall *TC_i1)(void*, int);
typedef void* (__thiscall *TC_pi)(void*, int);
typedef void* (__thiscall *TC_ps)(void*, const char*);
typedef void  (__thiscall *TC_pv)(void*, void*);
typedef void  (__thiscall *TC_v2)(void*, void*, void*);
typedef void  (__thiscall *TC_ii)(void*, int, int);
typedef void  (__thiscall *TC_iii)(void*, int, int, int);
typedef void* (__thiscall *TC_pii)(void*, int, int);

#define VFN(obj, off, T) ((T)(*(void***)(obj))[((off) >> 2)])

// ------------------------------------------------------------------ externs
extern "C" void* __cdecl GetCurrentGameMode();                 // 0x00b5b800
extern "C" void* __cdecl MessageServer();                     // 0x0067dcc0
extern "C" char  __cdecl FUN_00685520(int);                   // 0x00685520
extern "C" void  __cdecl SPUIHelpers_EndModal(void*, void*, void*); // 0x00809c50
extern "C" void* __cdecl spore_new(int, const char*, int, int, int, int); // 0x00f473a0
extern "C" void  __cdecl spore_del(void*);                    // 0x00f47380
extern "C" void* __cdecl Matrix33_Convert(void*, void*);      // 0x0041ded0
extern "C" void* __cdecl QuaternionFromMatrix33(void*, void*); // 0x00472b80

// ------------------------------------------------------------------ literals / vtables
extern char  S_Simulator[];    // 0x013f09b4 "Simulator"
extern char  S_stopCurrent[];  // 0x0145b338 "stopCurrentCinematic"
extern char  S_switchExit[];   // 0x0145b004 "switchToExitState"
extern float KF_1485720;       // 0x01485720
extern float KF_167a548;       // 0x0167a548
extern float KF_167a54c;       // 0x0167a54c
extern float KF_167a550;       // 0x0167a550
extern char  VT_145b2f8[];     // 0x0145b2f8
extern char  VT_145b2ec[];     // 0x0145b2ec
extern char  VT_13eb938[];     // 0x013eb938
extern char  VT_145b328[];     // 0x0145b328
extern char  VT_145b30c[];     // 0x0145b30c
extern char  VT_145b2fc[];     // 0x0145b2fc
extern char  VT_145b38c[];     // 0x0145b38c
extern char  VT_145b380[];     // 0x0145b380
extern char  VT_13ef094[];     // 0x013ef094
extern char  VT_14426a0[];     // 0x014426a0
extern char  VT_13ec458[];     // 0x013ec458

// ------------------------------------------------------------------ helper objects
struct cSPUILayout {
    void* ctor();                          // 0x00810000
    void  Init(void*, int, void*);         // 0x008120d0
    void* FindWindowByID(int, int);        // 0x008105b0
    void  SetVisibility(int);              // 0x00810590
};
struct cSPUISubtitles {
    void* ctor();                          // 0x00832900
    void  SetWindow(void*);                // 0x008329b0
    void  Set(int, float, int, int, float); // 0x00832d50
};
struct C0d660 {
    void call(void*);                  // 0x00c0d660
};

// ------------------------------------------------------------------ types
struct CamInfo {                       // 0x30 bytes: pos(3f) + quat(4f) + 4f + ptr
    float x, y, z;                     // +0x00
    float w0, w1, w2, w3;              // +0x0c
    float v0, v1, v2, v3;              // +0x1c
    void* p2c;                         // +0x2c

    CamInfo* init(void*, float*);      // 0x00ad79d0
    CamInfo* initDefault(void*);       // 0x00ad7a30
    float    getSpan();                // 0x00ad7af0
    float    getV1();                  // 0x00ad7b10
    float    getV0();                  // 0x00ad7b30
    void*    forwardC();               // 0x00ad7b50
    void*    getPtr();                 // 0x00ad7b70
    void*    getLocation(void*);       // 0x00ad7b90
    CamInfo* assign(CamInfo*);         // 0x00ad7f00
};

struct EditorRes {                     // 0x34 bytes
    void* vt0;                         // +0x00
    int   f4;                          // +0x04
    void* vt8;                         // +0x08
    void* fC;                          // +0x0c
    float f10, f14, f18, f1c, f20, f24;// +0x10
    uchar b28, b29, b2a, b2b, b2c, b2d, b2e; // +0x28
    int   f30;                         // +0x30
    EditorRes* ctor();                 // 0x00ad7c30
    EditorRes* copyCtor(EditorRes*);   // 0x00ad7ca0
};

struct PtrField {
    void*  p;
    void** assign(void**);             // 0x00ad7ec0
};

struct Screen {                        // screen object
    void* vt0;                         // +0x00
    void* vt4;                         // +0x04
    void* vt8;                         // +0x08
    int   f0c;                         // +0x0c
    cSPUILayout*     layout;           // +0x10
    void* win[15];                     // +0x14 .. +0x4c
    cSPUISubtitles*  subtitles;        // +0x50
    uchar flag54;                      // +0x54

    Screen* ctor();                    // 0x00ad8280
    void    init();                    // 0x00ad8300
    void    show(char);                // 0x00ad87d0
    void    fnA(int);                  // 0x00ad76f0
    void    fnB(int);                  // 0x00ad7740
    int     isModal();                 // 0x00ad7e20
    void    setModal(int);             // 0x00ad7e40
    void    setX(int);                 // 0x00ad7e90
};

struct Sim {                           // the large simulator object
    void* vt0;                         // +0x00
    char  pad04[4];
    void* vt8;                         // +0x08
    char  pad0c[0x3d - 0x0c];
    uchar f3d;                         // +0x3d
    char  pad3e[0x6c - 0x3e];
    void* f6c;                         // +0x6c
    char  pad70[0x13c - 0x70];
    void* f13c;                        // +0x13c
    void* f140;                        // +0x140
    char  pad144[0x150 - 0x144];
    int   f150;                        // +0x150
    char  pad154[0x15d - 0x154];
    uchar f15d;                        // +0x15d
    char  pad15e[0x164 - 0x15e];
    void* f164;                        // +0x164
    char  pad168[0x16c - 0x168];
    void* f16c;                        // +0x16c

    void  release16c();                // 0x00ad7d40
    void  stopCinematic();             // 0x00ad7d60
    void  goStop();                    // 0x00ad7dc0
    void  goExit();                    // 0x00ad7df0
    void  sendXform(int*, uchar);      // 0x00ad89b0
    void* dtor(uchar);                 // 0x00ad8960
};

// base sub-object type used for the dead-store vtable stores
struct SRBase {
    void* vt0; char pad04[4]; void* vt8; int f0c;
};
struct SRSub {
    void vfn0() { VFN(this, 0, TC_v0)(this); }
    void vfn4() { VFN(this, 4, TC_v0)(this); }
};

// ================================================================================================
// @ 0x00ad79d0
CamInfo* CamInfo::init(void* pa, float* pb)
{
    float one = KF_1485720;
    float* d = (float*)this;
    float* a = (float*)pa;
    float* b = pb;
    d[0] = a[0];
    d[1] = a[1];
    d[2] = a[2];
    d[3] = b[0];
    d[4] = b[1];
    d[5] = b[2];
    d[6] = b[3];
    d[7] = one;
    d[8] = one;
    d[9] = one;
    d[10] = one;
    ((int*)d)[11] = 0;
    return this;
}

// ================================================================================================
// @ 0x00ad7a30
CamInfo* CamInfo::initDefault(void* owner)
{
    this->x = KF_167a548;
    this->y = KF_167a54c;
    this->z = KF_167a550;
    this->v0 = 0.0f;
    this->v1 = 0.0f;
    this->v2 = 0.0f;
    this->v3 = 0.0f;
    this->p2c = owner;
    if (owner)
        VFN(owner, 0xbc, TC_v0)(owner);
    this->w0 = 0.0f;
    this->w1 = 0.0f;
    this->w2 = 0.0f;
    this->w3 = 0.0f;
    return this;
}

// ================================================================================================
// @ 0x00ad7af0
float CamInfo::getSpan()
{
    void* p = this->p2c;
    if (p) {
        float* r = (float*)VFN(p, 0x68, TC_p0)(p);
        return r[5] - r[2];
    }
    return this->v3;
}

// ================================================================================================
// @ 0x00ad7b10
float CamInfo::getV1()
{
    void* p = this->p2c;
    if (p)
        return VFN(p, 0x70, TC_f0)(p);
    return this->v1;
}

// ================================================================================================
// @ 0x00ad7b30
float CamInfo::getV0()
{
    void* p = this->p2c;
    if (p)
        return VFN(p, 0x74, TC_f0)(p);
    return this->v0;
}

// ================================================================================================
// @ 0x00ad7b50
void* CamInfo::forwardC()
{
    void* p = this->p2c;
    if (p)
        return VFN(p, 0x2c, TC_p0)(p);
    return this;
}

// ================================================================================================
// @ 0x00ad7b70
void* CamInfo::getPtr()
{
    void* p = this->p2c;
    if (p)
        return VFN(p, 0x30, TC_p0)(p);
    return &this->w0;
}

// ================================================================================================
// @ 0x00ad7b90
void* CamInfo::getLocation(void* pout)
{
    if (GetCurrentGameMode() == (void*)0x1654c01 && this->p2c != 0) {
        void* r;
        if (this->p2c)
            r = VFN(this->p2c, 0xb8, TC_pi)(this->p2c, 0xce9f6639);
        else
            r = 0;
        ((C0d660*)r)->call(pout);
        return pout;
    }
    if (this->p2c) {
        float* v = (float*)VFN(this->p2c, 0x2c, TC_p0)(this->p2c);
        float* o = (float*)pout;
        o[0] = v[0];
        o[1] = v[1];
        o[2] = v[2];
        return pout;
    }
    float* o = (float*)pout;
    o[0] = this->x;
    o[1] = this->y;
    o[2] = this->z;
    return pout;
}

// ================================================================================================
// @ 0x00ad7c30
EditorRes* EditorRes::ctor()
{
    int z = 0;
    this->f4 = z;
    *(void* volatile*)&this->vt8 = &VT_13eb938;
    this->vt0 = &VT_145b2f8;
    this->vt8 = &VT_145b2ec;
    this->fC = (void*)z;
    return this;
}

// ================================================================================================
// @ 0x00ad7ca0
EditorRes* EditorRes::copyCtor(EditorRes* src)
{
    this->f4 = 0;
    *(void* volatile*)&this->vt8 = &VT_13eb938;
    _ReadWriteBarrier();
    this->vt0 = &VT_145b2f8;
    this->vt8 = &VT_145b2ec;
    this->fC = src->fC;
    if (this->fC)
        VFN(this->fC, 0, TC_v0)(this->fC);
    this->f10 = src->f10;
    this->f14 = src->f14;
    this->f18 = src->f18;
    this->f1c = src->f1c;
    this->f20 = src->f20;
    this->f24 = src->f24;
    this->b28 = src->b28;
    this->b29 = src->b29;
    this->b2a = src->b2a;
    this->b2b = src->b2b;
    this->b2c = src->b2c;
    this->b2d = src->b2d;
    this->b2e = src->b2e;
    this->f30 = src->f30;
    return this;
}

// ================================================================================================
// @ 0x00ad7d40
void Sim::release16c()
{
    void* p = this->f16c;
    if (p) {
        this->f16c = 0;
        void* obj = (char*)p + 8;
        VFN(obj, 4, TC_v0)(obj);
    }
}

// ================================================================================================
// @ 0x00ad7d60
void Sim::stopCinematic()
{
    if (this->f164 != 0) {
        VFN(this->f164, 0xc, TC_i1)(this->f164, 0);
        void* p = this->f164;
        if (p) {
            this->f164 = 0;
            VFN(p, 4, TC_v0)(p);
        }
        void* ms = MessageServer();
        VFN(ms, 0x14, TC_iii)(ms, (int)0x5b07be5, 0, 0);
    }
}

// ================================================================================================
// @ 0x00ad7dc0
void Sim::goStop()
{
    void* o = this->f140;
    void* r = VFN(o, 0x38, TC_ps)(o, S_stopCurrent);
    this->f150 = (int)r;
    uchar one = 1;
    this->f15d = one;
    this->f3d = one;
}

// ================================================================================================
// @ 0x00ad7df0
void Sim::goExit()
{
    void* o = this->f140;
    void* r = VFN(o, 0x38, TC_ps)(o, S_switchExit);
    this->f150 = (int)r;
    uchar one = 1;
    this->f15d = one;
    this->f3d = one;
}

// ================================================================================================
// @ 0x00ad7e20
int Screen::isModal()
{
    void* w = this->win[12];
    void* sub = *(void**)((char*)w + 0x34);
    return VFN(sub, 0x28, TC_i0)(sub) & 1;
}

// ================================================================================================
// @ 0x00ad7e40
void Screen::setModal(int param)
{
    void* w0 = this->win[12];
    if (w0 != 0) {
        void* w34 = *(void**)((char*)w0 + 0x34);
        char b = (char)(VFN(w34, 0x28, TC_c0)(w34) & 1);
        if (b != (char)param) {
            void* w = this->win[12];
            void* w30 = *(void**)((char*)w + 0x30);
            VFN(w30, 0x7c, TC_ii)(w30, 1, param);
            void* w342 = *(void**)((char*)w + 0x34);
            VFN(w342, 0x7c, TC_ii)(w342, 1, param);
        }
    }
}

// ================================================================================================
// @ 0x00ad7e90
void Screen::setX(int param)
{
    void* w = this->win[12];
    if (w) {
        void* w48 = *(void**)((char*)w + 0x48);
        VFN(w48, 0x7c, TC_ii)(w48, 1, param);
    }
}

// ================================================================================================
// @ 0x00ad7ec0
void** PtrField::assign(void** src)
{
    void* nw = *src;
    void* old = this->p;
    if (nw != old) {
        if (nw)
            VFN(nw, 0xbc, TC_v0)(nw);
        this->p = nw;
        if (old)
            VFN(old, 0xc0, TC_v0)(old);
    }
    return &this->p;
}

// ================================================================================================
// @ 0x00ad7f00
CamInfo* CamInfo::assign(CamInfo* s)
{
    this->x = s->x;
    this->y = s->y;
    this->z = s->z;
    this->w0 = s->w0;
    this->w1 = s->w1;
    this->w2 = s->w2;
    this->w3 = s->w3;
    this->v0 = s->v0;
    this->v1 = s->v1;
    this->v2 = s->v2;
    this->v3 = s->v3;
    this->p2c = s->p2c;
    if (this->p2c)
        VFN(this->p2c, 0xbc, TC_v0)(this->p2c);
    return this;
}

// ================================================================================================
// @ 0x00ad81b0
extern "C" void** __cdecl FUN_00ad81b0(void** begin, void** end, void** dst, char (__cdecl *pred)(void*))
{
    if (begin != end) {
        do {
            if (!pred(*begin)) {
                void* nw = *begin;
                void* old = *dst;
                if (nw != old) {
                    if (nw)
                        VFN((char*)nw + 8, 0, TC_v0)((char*)nw + 8);
                    *dst = nw;
                    if (old)
                        VFN((char*)old + 8, 4, TC_v0)((char*)old + 8);
                }
                dst++;
            }
            begin++;
        } while (begin != end);
    }
    return dst;
}

// ================================================================================================
// @ 0x00ad8280
Screen* Screen::ctor()
{
    *(void* volatile*)&this->vt4 = &VT_14426a0;
    _ReadWriteBarrier();
    *(void* volatile*)&this->vt8 = &VT_13ec458;
    _ReadWriteBarrier();
    int z = 0;
    this->f0c = z;
    this->vt0 = &VT_145b328;
    this->vt4 = &VT_145b30c;
    this->vt8 = &VT_145b2fc;
    this->layout = (cSPUILayout*)z;
    this->win[0] = (void*)z;
    this->win[1] = (void*)z;
    this->win[2] = (void*)z;
    this->win[3] = (void*)z;
    this->win[4] = (void*)z;
    this->win[5] = (void*)z;
    this->win[6] = (void*)z;
    this->win[7] = (void*)z;
    this->win[8] = (void*)z;
    this->win[9] = (void*)z;
    this->win[10] = (void*)z;
    this->win[11] = (void*)z;
    this->win[12] = (void*)z;
    this->win[13] = (void*)z;
    this->win[14] = (void*)z;
    this->subtitles = (cSPUISubtitles*)z;
    this->flag54 = (uchar)z;
    return this;
}

#define SETWIN(i, id) do { \
    void* nw_ = this->layout->FindWindowByID((int)(id), 1); \
    void* old_ = this->win[i]; \
    if (nw_ != old_) { \
        if (nw_) VFN(nw_, 0, TC_v0)(nw_); \
        this->win[i] = nw_; \
        if (old_) VFN(old_, 4, TC_v0)(old_); \
    } \
} while (0)

// ================================================================================================
// @ 0x00ad8300
void Screen::init()
{
    void* p = spore_new(0x18, S_Simulator, 0, 0, 0, 0);
    cSPUILayout* nw;
    if (p) nw = (cSPUILayout*)((cSPUILayout*)p)->ctor(); else nw = 0;
    cSPUILayout* oldL = this->layout;
    if (nw != oldL) {
        if (nw) VFN(nw, 4, TC_v0)(nw);
        this->layout = nw;
        if (oldL) VFN(oldL, 8, TC_v0)(oldL);
    }

    int buf[3];
    buf[0] = 0x8a27d4;
    buf[1] = 0x510a95b;
    buf[2] = 0x40464100;
    this->layout->Init(buf, 1, (void*)0x5b598f8);

    SETWIN(0, 0x445c9ab);
    SETWIN(1, 0x7980d2c);
    SETWIN(2, 0x67a0fc6);
    SETWIN(3, 0x445c99d);
    SETWIN(4, 0xfffffff2);
    SETWIN(5, 0x62ef353);
    SETWIN(6, 0x5b5a2c8);
    SETWIN(7, 0x45012ca);
    SETWIN(8, 0x45023d0);
    SETWIN(9, 0x7563379);
    SETWIN(10, 0x7563386);
    SETWIN(11, 0x78d4130);
    SETWIN(12, 0x7c76404);
    SETWIN(13, 0x5db9c49);
    SETWIN(14, 0xffffffff);

    VFN(this->win[14], 0x104, TC_pv)(this->win[14], (char*)this + 4);

    void* ps = spore_new(0x2a0, S_Simulator, 0, 0, 0, 0);
    cSPUISubtitles* ns;
    if (ps) ns = (cSPUISubtitles*)((cSPUISubtitles*)ps)->ctor(); else ns = 0;
    cSPUISubtitles* oldS = this->subtitles;
    if (ns != oldS) {
        if (ns) VFN(ns, 4, TC_v0)(ns);
        this->subtitles = ns;
        if (oldS) VFN(oldS, 8, TC_v0)(oldS);
    }

    void* w2 = this->win[2];
    void* handle = w2 ? VFN(w2, 0xc, TC_pi)(w2, 0xf15f4bd) : 0;
    this->subtitles->SetWindow(handle);
    this->subtitles->Set(0, 1.0f, 0, 1, 0.0f);

    VFN(this->win[7], 0x7c, TC_ii)(this->win[7], 1, 0);
    VFN(this->win[8], 0x7c, TC_ii)(this->win[8], 1, 0);
    VFN(this->win[0], 0x7c, TC_ii)(this->win[0], 1, 0);
    if (FUN_00685520(2)) {
        VFN(this->win[9], 0x7c, TC_ii)(this->win[9], 1, 0);
        VFN(this->win[10], 0x7c, TC_ii)(this->win[10], 1, 0);
        VFN(this->win[11], 0x7c, TC_ii)(this->win[11], 1, 0);
        VFN(this->win[12], 0x7c, TC_ii)(this->win[12], 1, 0);
        VFN(this->win[1], 0x7c, TC_ii)(this->win[1], 1, 0);
    }
    VFN(this->win[2], 0x7c, TC_ii)(this->win[2], 1, 0);
    if (this->flag54) {
        SPUIHelpers_EndModal(this->win[14], 0, 0);
        this->flag54 = 0;
    }
}

// ================================================================================================
// @ 0x00ad87d0
void Screen::show(char param)
{
    this->layout->SetVisibility(1);
    if (param == 0) {
        VFN(this->win[2], 0x7c, TC_ii)(this->win[2], 1, 0);
        this->subtitles->Set(0, 1.0f, 0, 1, 0.0f);
        VFN(this->win[0], 0x7c, TC_ii)(this->win[0], 1, 0);
        if (FUN_00685520(2))
            VFN(this->win[1], 0x7c, TC_ii)(this->win[1], 1, 0);
        this->fnA(0);
        this->fnB(0);
        VFN(this->win[7], 0x7c, TC_ii)(this->win[7], 1, 0);
        VFN(this->win[8], 0x7c, TC_ii)(this->win[8], 1, 0);
        if (FUN_00685520(2)) {
            VFN(this->win[7], 0x7c, TC_ii)(this->win[7], 1, 0);
            VFN(this->win[8], 0x7c, TC_ii)(this->win[8], 1, 0);
            VFN(this->win[9], 0x7c, TC_ii)(this->win[9], 1, 0);
        }
        if (FUN_00685520(2)) {
            VFN(this->win[7], 0x7c, TC_ii)(this->win[7], 1, 0);
            VFN(this->win[8], 0x7c, TC_ii)(this->win[8], 1, 0);
            VFN(this->win[10], 0x7c, TC_ii)(this->win[10], 1, 0);
        }
        if (FUN_00685520(2)) {
            VFN(this->win[7], 0x7c, TC_ii)(this->win[7], 1, 0);
            VFN(this->win[8], 0x7c, TC_ii)(this->win[8], 1, 0);
            VFN(this->win[11], 0x7c, TC_ii)(this->win[11], 1, 0);
        }
        if (FUN_00685520(2)) {
            VFN(this->win[7], 0x7c, TC_ii)(this->win[7], 1, 0);
            VFN(this->win[8], 0x7c, TC_ii)(this->win[8], 1, 0);
            VFN(this->win[12], 0x7c, TC_ii)(this->win[12], 1, 0);
        }
    }
}

// ================================================================================================
// @ 0x00ad8960
void* Sim::dtor(uchar flags)
{
    *(void* volatile*)&this->vt0 = &VT_145b38c;
    *(void* volatile*)&this->vt8 = &VT_145b380;
    void* q = *(void* volatile*)&this->f6c;
    if (q && *(int*)((char*)q - 4) != 0)
        spore_del(q);
    *(void* volatile*)&this->vt8 = &VT_13eb938;
    *(void* volatile*)&this->vt0 = &VT_13ef094;
    if (flags & 1)
        spore_del(this);
    return this;
}

// ================================================================================================
// @ 0x00ad89b0
void Sim::sendXform(int* p, uchar flags)
{
    float pos[3];
    pos[0] = *(float*)((char*)p + 4);
    pos[1] = *(float*)((char*)p + 8);
    pos[2] = *(float*)((char*)p + 0xc);
    if (flags & 2) {
        float m1[9];
        Matrix33_Convert(m1, (char*)p + 0x14);
        float m2[9];
        for (int i = 0; i < 9; i++)
            m2[i] = m1[i];
        float quat[4];
        QuaternionFromMatrix33(quat, m2);
        if (flags & 0x10)
            VFN(this->f13c, 4, TC_v2)(this->f13c, (void*)0x101d51f, quat);
        else
            VFN(this->f13c, 4, TC_v2)(this->f13c, (void*)0x101d576, quat);
    }
    if (flags & 0x10)
        VFN(this->f13c, 4, TC_v2)(this->f13c, (void*)0x101b537, pos);
    else
        VFN(this->f13c, 4, TC_v2)(this->f13c, (void*)0x101b534, pos);
}
