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
    void FUN_00ad7670(float f1, float f2, int a, float f3, int e);
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
extern "C" void* SP_cAppStateManager_AddMessage(void* self, int* m, int b); // 0x7e4190
// (best-effort: constructs refcounted command + BehaviorMessage and posts it)
void CArgCmd2::FUN_00ad6960(void* a)
{
    int self = (int)this;
    *(int*)(self + 0xd8) = 0;
    *(byte*)(self + 0xdc) = 1;
    FUN_0083b9d0((void*)(self + 0x10), a, *(void**)(self + 4));
}

// ===========================================================================
// @ 0x00ad6b00
// ===========================================================================
extern "C" void FUN_0083c800(void* self);                             // 0x83c800
extern "C" void FUN_0083a9f0(void* self, int n);                      // 0x83a9f0
extern "C" void FUN_0083bcd0(void* self, ...);                        // 0x83bcd0
void* FUN_00ad6b00(void* self)
{
    FUN_0083c800(self);
    *(void**)self = (void*)0x145afdc;
    FUN_0083a9f0((char*)self + 0x10, 1);
    void* args[24];
    for (int i = 0; i < 24; ++i) args[i] = 0;
    FUN_0083bcd0((char*)self + 0x10, "Adds a referencable object");
    return self;
}

// ===========================================================================
// @ 0x00ad6bc0
// ===========================================================================
void CArgCmd2::FUN_00ad6bc0(void* a)
{
    int self = (int)this;
    *(int*)(self + 0xd8) = 0;
    *(int*)(self + 0xe4) = *(int*)&DAT_0167a4bc;
    *(int*)(self + 0xe8) = *(int*)&DAT_0167a4c0;
    *(int*)(self + 0xec) = *(int*)&DAT_0167a4c4;
    *(int*)(self + 0xf0) = 0;
    *(int*)(self + 0xf4) = 0;
    *(int*)(self + 0xf8) = *(int*)&DAT_0167a4bc;
    *(int*)(self + 0xfc) = *(int*)&DAT_0167a4c0;
    *(int*)(self + 0x100) = *(int*)&DAT_0167a4c4;
    FUN_0083b9d0((void*)(self + 0x10), a, *(void**)(self + 4));
}

// ===========================================================================
// @ 0x00ad6ec0
// ===========================================================================
extern "C" void FUN_00405050(void* p);                                // 0x405050
extern "C" void FUN_0083c750(void* p);                                // 0x83c750
void* CArgCmd2::FUN_00ad6ec0(byte flags)
{
    void* self = this;
    void* p = *(void**)((char*)self + 0xdc);
    if (p && *(int*)((char*)p - 4)) operator_delete(p);
    FUN_00405050((char*)self + 0x10);
    FUN_0083c750(self);
    if (flags & 1) operator_delete(self);
    return self;
}

// ===========================================================================
// @ 0x00ad6f10
// ===========================================================================
void* CArgCmd2::FUN_00ad6f10(byte flags)
{
    void* self = this;
    FUN_00405050((char*)self + 0x10);
    FUN_0083c750(self);
    if (flags & 1) operator_delete(self);
    return self;
}

// ===========================================================================
// @ 0x00ad6f40
// ===========================================================================
extern "C" void* GetTriggerMgr();                                     // 0xb3d4d0
extern "C" void* FUN_00ad5590();
extern "C" void* FUN_00ad5900();
extern "C" void* FUN_00ad5d90();
extern "C" void* FUN_00ad6240();
extern "C" void* FUN_00ad66c0();
extern "C" void* FUN_00ad68e0();
void FUN_00ad6f40(void)
{
    void* o;
    o = operator_new6(0x104, "Simulator", 0, 0, 0, 0);
    void* cmd = o ? FUN_00ad6b00(o) : 0;
    void* tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x1566330, cmd);
    o = operator_new6(0xfc, "Simulator", 0, 0, 0, 0);
    cmd = o ? FUN_00ad5590() : 0;
    tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x1566334, cmd);
    o = operator_new6(0x108, "Simulator", 0, 0, 0, 0);
    cmd = o ? FUN_00ad5900() : 0;
    tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x1566388, cmd);
    o = operator_new6(0x100, "Simulator", 0, 0, 0, 0);
    cmd = o ? FUN_00ad5d90() : 0;
    tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x156638c, cmd);
    o = operator_new6(0x108, "Simulator", 0, 0, 0, 0);
    cmd = o ? FUN_00ad6240() : 0;
    tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x1566390, cmd);
    o = operator_new6(0xe0, "Simulator", 0, 0, 0, 0);
    cmd = o ? FUN_00ad66c0() : 0;
    tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x1566394, cmd);
    o = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    if (o) { FUN_0083c800(o); *(void**)o = (void*)0x145a6a8; }
    tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x1566398, o);
    o = operator_new6(0xe0, "Simulator", 0, 0, 0, 0);
    cmd = o ? FUN_00ad68e0() : 0;
    tm = (void*)GetTriggerMgr();
    (*(void (__thiscall*)(void*, void*, void*))((char*)*(void**)tm + 0x10))(tm, (void*)0x156639c, cmd);
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
    void* self = this;
    *(void**)self = (void*)0x145b328;
    *((void**)self + 1) = (void*)0x145b30c;
    *((void**)self + 2) = (void*)0x145b2fc;
    for (int off = 0x50; off >= 0x14; off -= 4) {
        SubObj* p = *(SubObj**)((char*)self + off);
        if (p) p->s04();
    }
    SubObj* p10 = *(SubObj**)((char*)self + 0x10);
    if (p10) p10->s08();
    *((void**)self + 2) = (void*)0x13ec458;
    *((void**)self + 1) = (void*)0x13eb938;
    *(void**)self = (void*)0x13eb394;
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
void CUID::FUN_00ad7610(int r)
{
    void* self = this;
    if (FUN_00685520(2)) {
        (*(void (__thiscall*)(void*))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x18) + 0x80)))(*(void**)((char*)self + 0x18));
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
extern "C" void FUN_00832d50(int a, int b, float c, float d, int e);  // 0x832d50
void CUID::FUN_00ad7670(float f1, float f2, int a, float f3, int e)
{
    void* self = this;
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x14) + 0x7c)))(*(void**)((char*)self + 0x14), 1, 0);
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x1c) + 0x7c)))(*(void**)((char*)self + 0x1c), 1, 1);
    FUN_00832d50(1, 0, f1, f2, e);
    (void)a; (void)f3;
}

// ===========================================================================
// @ 0x00ad76c0
// ===========================================================================
void CUID::FUN_00ad76c0()
{
    void* self = this;
    (*(void (__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)*(void**)((char*)self + 0x1c) + 0x7c)))(*(void**)((char*)self + 0x1c), 1, 0);
    FUN_00832d50(0, 0x3f800000, 0.0f, 1.0f, 0);
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
