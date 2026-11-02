// src/game/SPAudio/_at_00a40000.cpp -- migrated from slice(s) s00a4d340, s00a49670, s00a488d0, s00a478b0, s00a469b0, s00a459d0, s00a41c40, s00a40cd0 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00a40000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// unnamed retail callees and globals (address in the comment)
extern char PTR_AddRef_01453c30[];

// ---- items of slice s00a40cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int);
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
namespace EA {
namespace Audio {
int* GetSystemAT();                                              // 0x00a206f0
}
}
namespace EA {
namespace Audio {
class Sound_s00a4_0cd0 { public:
    char ConfigureSound();                                       // 0x00a20060
    void TickInternal(int a, float b, int c);                    // 0x00a1c710
    void SetPropertyInternal(int key, float v, int arg);         // 0x00a1d9c0
    void Stop(int a, char flags);                                // 0x00a1bba0
    char BeginTick();                                            // 0x00a1af50
    char Init_1b730();                                           // 0x00a1b730
    char Start_1b8a0(double v);                                  // 0x00a1b8a0
    char Check_ef6410();                                         // 0x00ef6410
    void Dtor_8dde10();                                          // 0x008dde10
};
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace ISystem {
int* GetSingletonPtr();                          // 0x00a67c60
}
}
}
}
namespace SP {
struct cLocalLightInfo_s00a4_0cd0 {
    void Dtor(int value);                        // 0x009276c0
};
}
namespace SP {
extern void* DAT_016c8b44;
}
extern char PTR_AddRef_01453c30[];
char __stdcall FUN_008dde50(int a, int b, int c, int d);
struct AddRefObj {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    void CTor();                              // 0x008ddff0  (thiscall ctor)
    void Dtor();                              // 0x00a41710
};
struct FactoryObj {
    VP VP VP VP VP VP VP VP VP
    virtual char Create(int key, int* obj, int a, int b);   // +0x24
    char Run(int key, int* out, int a, int b);              // 0x00a417b0
};
// ---- items of slice s00a40cd0 end

// ---- items of slice s00a41c40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyString16[];   // 0x01667bac
void* operator new(unsigned int, const char*, int, int, const char*, int);
void operator delete(void*);
void operator delete[](void*);
namespace EA {
namespace Audio {
class ResponseCurve_s00a4_1c40
{
public:
    ResponseCurve_s00a4_1c40();                                        // 0x00a1aa50
    ~ResponseCurve_s00a4_1c40() throw();
    float GetOutputValue(float value) const;                // 0x00a1a110

    void* mpData;               // +0x00
    char mPad_04[0x0c];         // +0x04
    void* mpAllocation;         // +0x10
    char mPad_14[0x350];        // +0x14  (sizeof == 0x364)
};
}
}
namespace EA {
namespace Audio {
ResponseCurve_s00a4_1c40::~ResponseCurve_s00a4_1c40() throw()
{
    if (mpData && mpData != mpAllocation)
        operator delete(mpData);
}
}
}
namespace EA {
namespace Audio {
class Sound_s00a4_1c40
{
public:
    Sound_s00a4_1c40();                                                // 0x00a1fbb0
    virtual ~Sound_s00a4_1c40();                                       // 0x00a1f4d0
    void CommitAllProperties();                             // 0x00a1d080
};
}
}
struct TeString
{
    const void* mpBegin;        // +0x00
    const void* mpEnd;          // +0x04
    const void* mpCapacity;     // +0x08

    TeString()
        : mpBegin(gEmptyString16),
          mpEnd(gEmptyString16),
          mpCapacity((char*)gEmptyString16 + 1)
    {
    }
    ~TeString() throw();
};
TeString::~TeString() throw()
{
    if ((const char*)mpCapacity - (const char*)mpBegin > 1 && mpBegin)
        operator delete((void*)mpBegin);
}
namespace SP {
namespace Audio {
struct __declspec(novtable) CurveSource
{
    VP VP VP
    virtual void Slot0c(unsigned int id, float value, int flag);   // +0x0c
    virtual bool Slot10(unsigned int id, float* pOut);             // +0x10
};
}
}
namespace SP {
namespace Audio {
struct __declspec(novtable) ThirdBase
{
    VP VP
};
}
}
namespace SP {
namespace Audio {
class cSound : public EA::Audio::Sound_s00a4_1c40, public CurveSource, public ThirdBase
{
public:
    static void* operator new(unsigned int size);           // 0x00a41cc0

    cSound();
    ~cSound();

    float ComputeGainAttenuation(float a, float b, float c, float d, float e);  // 0x00a41c40
    void CommitAllProperties();                             // 0x00a41d30

    char mPad_0c[0x44 - 0x0c];      // +0x0c
    void* mpObj44;                  // +0x44
    char mPad_48[0xce4 - 0x48];     // +0x48
    unsigned int mFlags;            // +0xce4
    char mPad_ce8[0x1e10 - 0xce8];  // +0xce8
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve1e10;    // +0x1e10
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve2174;    // +0x2174
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve24d8;    // +0x24d8
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve283c;    // +0x283c
    int mStartContext;              // +0x2ba0
    bool mb2ba4;                    // +0x2ba4
    bool mb2ba5;                    // +0x2ba5
    TeString mName;                 // +0x2ba8
    int mPad_2bb4;                  // +0x2bb4  (sizeof == 0x2bb8)
};
}
}
using SP::Audio::cSound;
namespace SP {
namespace Audio {
class cEmitterSndPlayer
{
public:
    static void* operator new(unsigned int size);   // 0x00a38f30
    cEmitterSndPlayer();                            // 0x00a38d90
    char mData[0xe08];
};
}
}
namespace SP {
namespace Audio {
class cEmitterEAPD
{
public:
    static void* operator new(unsigned int size);   // 0x00a37a70
    cEmitterEAPD();                                 // 0x00a37b10
    char mData[0x38];
};
}
}
// ---- items of slice s00a41c40 end

// ---- items of slice s00a459d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int* __cdecl    Eapd_Debug_ObjectError();                   // 0x008de1a0
void* operator new(unsigned, const char*, int, int, int, int);         // 0x00f473a0
void  operator delete(void*, const char*, int, int, int, int);         // 0x00f47410
struct ErrHost {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17(int, void*, int);
};
struct ErrBase { ErrBase(); virtual void v0(); };                // 0x00a19d60
struct ErrObj : ErrBase {
    static void* operator new(unsigned, const char*, int, int, int, int);   // 0x00926020
    static void  operator delete(void*, const char*, int, int, int, int);   // 0x00926060
    char m_pad[0x70 - 4];
};
// ---- items of slice s00a459d0 end

// ---- items of slice s00a469b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    mHash;   // +0
    const char* mpName;  // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {          // 12 bytes
    int32_t a_type;
    union {
        float    w_float;
        int32_t  w_index;
        t_symbol w_symbol;
    } a_w;
};
}
}
}
// ---- items of slice s00a469b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { void atom_string(const t_atom* a, char* buf, int bufsize); }}}  // 0x00a469b0 (stays in the slice: not this object's)

// ---- items of slice s00a478b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom_s00a4_78b0 {           // 12 bytes
    int a_type;
    union {
        float    w_float;
        int      w_index;
        t_symbol w_symbol;
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
enum { A_NULL = 0, A_FLOAT = 1, A_SYMBOL = 2, A_SEMI = 3, A_COMMA = 4, A_DEFFLOAT = 5, A_DEFSYM = 6,
       A_DOLLAR = 7, A_DOLLSYM = 8, A_GIMME = 9 };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
enum { MAXPDARG = 5 };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_class* t_pd;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_methodentry {     // 0x24 bytes
    t_symbol me_name;      // +0
    void*    me_fun;       // +8
    int      me_arg[MAXPDARG + 1];   // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    char pad00[8];
    t_symbol       c_helpname;                                  // +0x08 ("<name>-help")
    char pad10[0xc];
    t_methodentry* c_methods;                                   // +0x1c
    int            c_nmethod;                                   // +0x20
    char pad24[4];
    void (*c_bangmethod)(t_pd* x);                              // +0x28
    void (*c_floatmethod)(t_pd* x, float f);                    // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);                // +0x30
    void (*c_listmethod)(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);   // +0x34
    void (*c_anymethod)(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);    // +0x38
    void*          c_propertiesfn;                              // +0x3c
    void*          c_savefn;                                    // +0x40
    void*          c_drawfunction;                              // +0x44
    char           c_pad48;                                     // +0x48
    char           c_gobj;         // +0x49: graphical object (has an outlet list)
    char           c_pad4a[2];
    t_class*       c_next;                                      // +0x4c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_bang;        // 0x16758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_list;        // 0x16758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol s_symbol;      // 0x1675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  obj_list(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);              // 0x00a49b40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_gui(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);               // 0x00c2e4e0 (empty stub)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  class_addfloat(t_pd* x, float f);                                   // 0x00a48910
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void pd_defaultlist(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv);   // 0x00a47d70
}
}
}
// ---- items of slice s00a478b0 end

// ---- items of slice s00a488d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_clock {
    double   c_settime;   // +0
    int      c_set;       // +8
    void*    c_owner;     // +0xc
    void*    c_method;    // +0x10
    t_clock* c_next;      // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_clock*    s_clocklist;     // 0x1675410
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern double      s_systime;       // 0x1675418
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern double      s_time;          // 0x1675420
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern double      s_realtime;      // 0x1675428
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const float  gTickScale;     // 0x145440c  (sched_tick's clamp constant)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_lock();                                                              // 0xa49d00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
char  glob_init();                                                             // 0xa49be0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
char  glob_setup();                                                            // 0xa51f40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
char  s_loader_setup();                                                        // 0xa51f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
char  s_list_setup();                                                          // 0xa52000
}
}
}
// ---- items of slice s00a488d0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { bool mess_init(); }}}  // 0x00a48f60 (stays in the slice: not this object's)

// ---- items of slice s00a49670 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a4_9670;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_object;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_inlet;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outconnect;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_class_s00a4_9670* t_pd_s00a4_9670;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_methodentry_s00a4_9670 {
    t_symbol me_name;     // +0
    void*    me_fun;      // +8
    int      me_arg[6];   // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a4_9670 {
    char pad00[0x1c];
    t_methodentry_s00a4_9670* c_methods;                        // +0x1c
    int            c_nmethod;                        // +0x20
    char pad24[4];
    void (*c_bangmethod)(t_pd_s00a4_9670* x);                   // +0x28
    void (*c_floatmethod)(t_pd_s00a4_9670* x, float f);         // +0x2c
    void (*c_symbolmethod)(t_pd_s00a4_9670* x, t_symbol s);     // +0x30
    char pad34[0x49 - 0x34];
    char c_isobject;                                 // +0x49 (pd_checkobject)
    char c_firstin;                                  // +0x4a (first inlet is the object)
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj {
    t_class_s00a4_9670* g_pd;        // +0x00
    t_gobj*  g_next;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_object : t_gobj {
    void*     te_binbuf;  // +0x08
    t_outlet* te_outlet;  // +0x0c
    t_inlet*  te_inlet;   // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_inlet {              // 0x28
    t_class_s00a4_9670*  i_pd;           // +0x00
    t_inlet*  i_next;         // +0x04
    t_object* i_owner;        // +0x08
    t_pd_s00a4_9670*     i_dest;         // +0x0c
    t_symbol  i_symfrom;      // +0x10
    union {
        t_symbol i_symto;     // +0x18 (message inlet)
        void*    i_destp;     // +0x18 (float/symbol inlet destination)
    } u;
    t_symbol  i_symempty;     // +0x20
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_inlet*      oc_to;      // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet {             // 0x1c
    t_object*     o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};
}
}
}
// ---- items of slice s00a49670 end

// ---- items of slice s00a4d340 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class_s00a4_d340;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_rtext;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj_s00a4_d340 {
    t_class_s00a4_d340* g_pd;      // +0x00
    t_gobj_s00a4_d340*  g_next;    // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_text {        // t_object
    t_gobj_s00a4_d340  te_g;       // +0x00
    uint32_t pad08[3];  // binbuf, outlet, inlet
    int16_t te_xpix;    // +0x14
    int16_t te_ypix;    // +0x16
    uint32_t pad18[4];
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_editor {
    uint32_t pad00[3];
    void*    e_textedfor;   // +0x0c
    uint32_t pad10[2];
    t_gobj_s00a4_d340*  e_grab;        // +0x18
    void*    e_motionfn;    // +0x1c
    void*    e_keyfn;       // +0x20
    uint32_t pad24[4];
    int      e_xwas;        // +0x34
    int      e_ywas;        // +0x38
    uint32_t pad3c[5];
    unsigned e_onmotion : 3; // +0x50
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist {
    t_text    gl_obj;        // +0x00
    t_gobj_s00a4_d340*   gl_list;       // +0x28
    t_glist*  gl_owner;      // +0x2c
    int       gl_pixwidth;   // +0x30
    int       gl_pixheight;  // +0x34
    float     gl_x1;         // +0x38
    float     gl_y1;         // +0x3c
    float     gl_x2;         // +0x40
    float     gl_y2;         // +0x44
    int       gl_screenx1;   // +0x48
    int       gl_screeny1;   // +0x4c
    int       gl_screenx2;   // +0x50
    int       gl_screeny2;   // +0x54
    int       gl_xmargin;    // +0x58
    int       gl_ymargin;    // +0x5c
    t_editor* gl_editor;     // +0x60
    uint32_t  pad64[5];
    unsigned  gl_havewindow : 1;   // +0x78
    unsigned  gl_mapped : 1;
    unsigned  gl_dirty : 1;
    unsigned  gl_loading : 1;
    unsigned  gl_willvis : 1;
    unsigned  gl_edit : 1;
    unsigned  gl_isdeleting : 1;
    unsigned  gl_goprect : 1;
    unsigned  gl_isgraph : 1;
    unsigned  gl_hidetext : 1;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_rtext* glist_findrtext(t_glist* x, t_text* y);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a4ee20(t_rtext* rtext);
}
}
}
// ---- items of slice s00a4d340 end

// @ 0x00a416e0
int __stdcall FUN_00a416e0(int* p, unsigned n)
{
    if (p != 0) {
        if (n >= 1) {
            *p = 0x22d2c83;
        } else {
            return 0;
        }
    }
    return 1;
}

// @ 0x00a41710
void AddRefObj::Dtor()
{
    *(int*)this = (int)PTR_AddRef_01453c30;
    if (*(int*)((char*)this + 0x14) != 0) {
        int* s = EA::Audio::GetSystemAT();
        if (s) ((void(**)(int*))*((int**)s))[0xC0 / 4]((int*)s);
        int* e = EA::Audio::Eapd::ISystem::GetSingletonPtr();
        if (e) ((void(**)(int*, int))(*((int**)e)))[0x50 / 4]((int*)e, *(int*)((char*)this + 0x14));
        s = EA::Audio::GetSystemAT();
        if (s) ((void(**)(int*))*((int**)s))[0xC4 / 4]((int*)s);
    }
    ((EA::Audio::Sound_s00a4_0cd0*)this)->Dtor_8dde10();
}

// @ 0x00a417b0
char FactoryObj::Run(int key, int* out, int a, int b)
{
    if (out == 0) return 0;
    char result = 0;
    AddRefObj* obj = 0;
    __try {
        obj = (AddRefObj*)operator new(0x20, "Audio", 0, 0, 0, 0);
        if (obj == 0) {
            obj = 0;
        } else {
            obj->CTor();
            *(int*)obj = (int)PTR_AddRef_01453c30;
        }
        if (obj != 0) obj->AddRef();
        if (obj != 0) {
            bool store = false;
            if (key == 0) {
                result = 1;
                store = true;
            } else {
                result = Create(key, (int*)obj, a, b);
                if (result != 0)
                    store = true;
            }
            if (store) {
                *out = (int)obj;
                obj->AddRef();
            }
        }
        if (obj != 0) obj->Release();
    } __except (1) {
        result = 0;
    }
    return result;
}

// @ 0x00a418b0
unsigned char __stdcall FUN_00a418b0(int a, int self, int c, int d)
{
    int saved = *(int*)(self + 0x14);
    unsigned char result = 0;
    *(int*)(self + 0x14) = 0;
    volatile int va = a;
    char ok = FUN_008dde50(va, self, c, d);
    if (ok) {
        int* s = EA::Audio::GetSystemAT();
        if (s) ((void(__thiscall*)(int*))(*((int**)s))[0xC0 / 4])((int*)s);
        int* e = EA::Audio::Eapd::ISystem::GetSingletonPtr();
        result = 0;
        if (e)
            result = (unsigned char)((int(__thiscall*)(int*, int, int, int))(*((int**)e))[0x4C / 4])((int*)e, *(int*)(self + 0x14), *(int*)(self + 0x18), self + 0x1c);
        s = EA::Audio::GetSystemAT();
        if (s) ((void(__thiscall*)(int*))(*((int**)s))[0xC4 / 4])((int*)s);
    }
    if (saved != 0) ((SP::cLocalLightInfo_s00a4_0cd0*)SP::DAT_016c8b44)->Dtor(saved);
    return result;
}

// @ 0x00a41e10
namespace SP { namespace Audio {
cSound::~cSound()
{
}
}}  // namespace SP::Audio

// @ 0x00a420d0
SP::Audio::cEmitterSndPlayer* ConstructcEmitterSndPlayer()
{
    return new SP::Audio::cEmitterSndPlayer();
}

// @ 0x00a42130
SP::Audio::cEmitterEAPD* ConstructcEmitterEAPD()
{
    SP::Audio::cEmitterEAPD* p = new SP::Audio::cEmitterEAPD();
    return p ? (SP::Audio::cEmitterEAPD*)((char*)p + 4) : 0;
}

// @ 0x00a466d0
extern "C" bool __cdecl Audio_RegisterErrorHandler()
{
    int* p = Eapd_Debug_ObjectError();
    if (p) {
        ErrObj* obj = new("Audio", 0, 0, 0, 0) ErrObj;
        ((ErrHost*)p)->v17(1, obj, 0);
    }
    return p != 0;
}

// @ 0x00a46bc0
namespace EA { namespace Audio { namespace Eapd {
void binbuf_vectortext(int argc, const t_atom* argv, char* buf, int bufsize)
{
    char atomtext[80];
    int i;

    *buf = 0;
    atomtext[0] = ' ';
    for (i = 0; i < argc; i++) {
        atom_string(argv, atomtext + 1, 79);
        strncat(buf, atomtext + (i == 0), bufsize);
        argv++;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47cb0
namespace EA { namespace Audio { namespace Eapd {
void pd_defaultbang(t_pd* x)
{
    t_class* c = *x;

    if (c->c_listmethod != pd_defaultlist)
        c->c_listmethod(x, s_list, 0, 0);
    else
        c->c_anymethod(x, s_bang, 0, 0);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47d00
namespace EA { namespace Audio { namespace Eapd {
void pd_defaultsymbol(t_pd* x, t_symbol s)
{
    t_atom_s00a4_78b0 a;

    a.a_w.w_symbol = s;
    a.a_type = A_SYMBOL;
    if ((*x)->c_listmethod != pd_defaultlist)
        (*x)->c_listmethod(x, s_list, 1, &a);
    else
        (*x)->c_anymethod(x, s_symbol, 1, &a);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a47d70
namespace EA { namespace Audio { namespace Eapd {
void pd_defaultlist(t_pd* x, t_symbol s, int argc, t_atom_s00a4_78b0* argv)
{
    if (argc == 0) {
        if ((*x)->c_bangmethod != pd_defaultbang) {
            (*x)->c_bangmethod(x);
            return;
        }
    }
    else if (argc == 1) {
        if (argv->a_type == A_FLOAT && (*x)->c_floatmethod != class_addfloat) {
            (*x)->c_floatmethod(x, argv->a_w.w_float);
            return;
        }
        if (argv->a_type == A_SYMBOL && (*x)->c_symbolmethod != pd_defaultsymbol) {
            (*x)->c_symbolmethod(x, argv->a_w.w_symbol);
            return;
        }
    }
    if ((*x)->c_anymethod != sys_gui) {
        (*x)->c_anymethod(x, s_list, argc, argv);
        return;
    }
    if ((*x)->c_gobj)
        obj_list(x, s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a492c0
namespace EA { namespace Audio { namespace Eapd {
void clock_setftime(double systime)
{
    s_time = systime;
    s_realtime = systime;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a492e0
namespace EA { namespace Audio { namespace Eapd {
void sched_tick(float nexttime)
{
    double base;
    if (nexttime > 0.0f) {
        base = s_realtime;
    } else {
        base = s_systime - s_realtime;
        if (base > (double)gTickScale)
            nexttime = gTickScale;
    }
    s_systime = base;
    double t = base + nexttime;
    while (s_clocklist && s_clocklist->c_settime <= t) {
        t_clock* c = s_clocklist;
        s_time = c->c_settime;
        if (c->c_set == 1)
            s_clocklist = c->c_next;
        c->c_set = 0;
        sys_lock();
        ((void (*)(void*))c->c_method)(c->c_owner);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a495e0
namespace EA { namespace Audio { namespace Eapd {
bool conf_init()
{
    bool ok = (mess_init() & 1) != 0;
    ok = ok & glob_init();
    ok = ok & glob_setup();
    ok = ok & s_loader_setup();
    ok = ok & s_list_setup();
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49720
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a49720(t_inlet* x, t_symbol s)
{
    if (x) {
        x->i_symempty.mHash = s.mHash;
        x->i_symempty.mpName = s.mpName;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a1e0
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a4a1e0(t_object* x, t_inlet* i)
{
    t_inlet* i2 = x->te_inlet;

    if (i2 == i || !i2)
        return;
    while (i2->i_next != i) {
        i2 = i2->i_next;
        if (!i2)
            return;
    }
    i2->i_next = i->i_next;
    i->i_next = x->te_inlet;
    x->te_inlet = i;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4a220
namespace EA { namespace Audio { namespace Eapd {
void FUN_00a4a220(t_object* x, t_outlet* o)
{
    t_outlet* o2 = x->te_outlet;

    if (o2 == o || !o2)
        return;
    while (o2->o_next != o) {
        o2 = o2->o_next;
        if (!o2)
            return;
    }
    o2->o_next = o->o_next;
    o->o_next = x->te_outlet;
    x->te_outlet = o;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4d3e0
namespace EA { namespace Audio { namespace Eapd {
void glist_retext(t_glist* x, t_text* y)
{
    if (x->gl_editor && x->gl_editor->e_textedfor) {
        t_rtext* rt = glist_findrtext(x, y);
        if (rt)
            FUN_00a4ee20(rt);
    }
}
}}}  // namespace EA::Audio::Eapd
