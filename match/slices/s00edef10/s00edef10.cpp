// Slice s00edef10 -- 0x00edef10..0x00edfec0  (/O2 /MD /Gy /TP /fp:fast)
//
// Spore scenario-editor "behavior" UI helpers (UI::cScenarioEditModeBehaviorUI
// and friends) plus Simulator::cHideOnMoveScreenPosition.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void* DAT_016c7aa4;
extern int   DAT_0148a708[];

struct Mgrs {
    char pad00[0x10];
    int  f10;
    int  F3e8a0(int);
    int  F45970();
    int  F45a80();
    int  F41a10(int);
    int  F3be60(int);
};
#define MGR()  (*(Mgrs**)((char*)DAT_016c7aa4 + 0x74))

#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VCP0(p,off)     (((void*(__thiscall*)(void*))     VTP(p)[(off)/4])((void*)(p)))
#define VCP1(p,off,a)   (((void*(__thiscall*)(void*,int)) VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VCP2(p,off,a,b) (((void*(__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VCP3(p,off,a,b,c) (((void*(__thiscall*)(void*,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c)))
#define VCP2F(p,off,a,b,f) (((void*(__thiscall*)(void*,int,int,float))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(float)(f)))

extern "C" int FindWindowByID(void*, int, int);
extern "C" int FUN_00eece20(int);
extern "C" int FUN_00efc520();
extern "C" int FUN_00f078a0();
extern "C" int FUN_00f3e8a0(int, int);
extern "C" int FUN_00f26440(void*, int);
extern "C" int FUN_00f28c10(void*, int);
extern "C" void* SP_WindowManager(); // 0x0067caa0
extern "C" void* SP_MessageServer(); // 0x0067dcc0
extern "C" void* SP_PropertyManager(); // 0x0067de30
extern "C" int  SP_GetPropertyAsFloatArray(void*, int, void*, void*); // 0x006a08b0
extern "C" void SPUIHelpers_RemoveWindowCallback(void*, void*);
extern "C" void SPUIHelpers_CreateCallbackWinProc(void*, void*, int, int, void*);
extern "C" void SPUIHelpers_SetDrawableImage(void*, int, int, int);
extern "C" void* EA_UTFWin_MultiHeapObject_operator_new(int);   // 0x0080fee0 (equiv t2)
extern "C" void* FUN_00b3d320(); // 0x00b3d320
extern "C" void* FUN_00b1de80(); // 0x00b1de80
extern "C" void  FUN_00ed39a0(int); // 0x00ed39a0
extern "C" void  FUN_00edce20(int); // 0x00edce20
extern "C" void  FUN_00644b10(void*); // 0x00644b10
extern "C" void  FUN_00644b60(void*); // 0x00644b60
extern "C" void  SP_cSPUIAssetBrowser_AdvancedLaunch(void*); // 0x0064a990
extern "C" int   FNVHash(int, int, int); // 0x00932e80

// ---- completion helpers (0x00edf090 .. 0x00edfb30) ------------------------
extern int DAT_015ac654;
extern int DAT_0148a720[];
extern int DAT_0148a754[];
extern int DAT_0148a764[];
extern int DAT_0148a774[];
extern unsigned DAT_0148a734;
extern unsigned DAT_0148a760;
extern unsigned DAT_0148a770;
extern unsigned DAT_0148a788;

struct Key3 { int h0, h4, h8; };

extern "C" void* FUN_00f473a0(int, const char*, int, int, int, int);  // 0x00f473a0
extern "C" void* FUN_005c66a0(void*);                                // 0x005c66a0
extern "C" void* FUN_005c64e0(void*);                                // 0x005c64e0
extern "C" void* FUN_005c6810(void*, Key3*, int, int);               // 0x005c6810
extern "C" void* FUN_00ece990(void*);                                // 0x00ece990
extern "C" char  FUN_008068d0(void*, int, int);                      // 0x008068d0
extern "C" int   FUN_00edcec0(int*, int*, unsigned*);                // 0x00edcec0
extern "C" void  FUN_00edcf60(void*, float);                         // 0x00edcf60
extern "C" int   FUN_0040cf10(void*, int, float*);                   // 0x0040cf10
extern "C" int   FUN_00881ae0(long long, wchar_t*, int);             // 0x00881ae0
extern "C" int   FUN_00b5b800();                                     // 0x00b5b800
extern "C" void  FUN_0064a990(void*);                                // 0x0064a990
extern "C" void  FUN_005f2290(void*, int);                           // 0x005f2290
extern "C" void  FUN_00ecd990(void*, float);                         // 0x00ecd990


struct VHide { void f00edd440(float*, float*); };
struct Viso   { bool F26440(int); int F28c10(int); };
struct Sub    { void F72b0(); };

struct Ed {
    char pad[0x300];
    int  F070(int);
    void F090(int);
    void FEF10();
    void F410();
    void F4C0();
    void F510();
    void* FE10(int*, int, int);
    bool FEA0(float*, float*);
    void FBF0(int*);
};

// ============================================================ 0x00edf070
// @ 0x00edf070
int Ed::F070(int param)
{
    int* self = (int*)this;
    void* p = *(void**)((char*)self + 0x18);
    if (p != 0)
        return (int)VCP2(p, 0xf0, param, 1);
    return 0;
}

// ============================================================ 0x00edf240
// @ 0x00edf240
void __fastcall f00edf240(int* self)
{
    int sel = *(int*)((char*)self + 0x24);
    if (sel == 0)
        return;
    void* p;
    void* w = *(void**)((char*)self + 0x18);
    if (w != 0)
        p = VCP2(w, 0xf0, sel, 1);
    else
        p = 0;
    *(int*)((char*)self + 0x24) = 0;
    if (p != 0) {
        void* q = VCP1(p, 0xc, 0x8ed27e7a);
        if (q != 0)
            VC2(q, 0x28, 4, 0);
    }
    void* r = VCP2(p, 0xf0, 0x742be58, 1);
    if (r != 0)
        VC2(r, 0x7c, 1, 0);
}

// ============================================================ 0x00edf2c0
// static helper: for the two palette ids, add/remove the callback.
void __cdecl f00edf2c0(int p1, int p2);
// ============================================================ 0x00edf370
bool __cdecl f00edf370(int p1, int* p2, int p3);
// ============================================================ 0x00edf3c0
void __cdecl f00edf3c0(int p1, int p2, char flag);

// ============================================================ 0x00edf410
struct LitMgr { char pad[4]; void* GetWorldMainWindow(); };
// @ 0x00edf410
void Ed::F410()
{
    int* self = (int*)this;
    char* t = (char*)self;
    if (*(int*)(t + 0x30) == 0)
        return;
    void* wm = SP_WindowManager();
    VC2(wm, 0x5c, 1, *(int*)(t + 0x30));
    void* alloc = EA_UTFWin_MultiHeapObject_operator_new(0x5b598fa);
    void* mw = ((LitMgr*)alloc)->GetWorldMainWindow();
    VC1(mw, 0xdc, *(int*)(t + 0x30));
    VC1(*(void**)(t + 0x34), 0xd8, *(int*)(t + 0x30));
    void* pd = *(void**)(t + 0x34);
    if (pd != 0) {
        *(int*)(t + 0x34) = 0;
        VC0(pd, 4);
    }
    VC1(*(void**)(t + 0x30), 0x6c, (int)(t + 0x38));
    VC1(*(void**)(t + 0x30), 0x5c, -1);
    VC1(*(void**)(t + 0x30), 0x78, 0x747d67b);
    void* p3 = *(void**)(t + 0x30);
    if (p3 != 0) {
        *(int*)(t + 0x30) = 0;
        VC0(p3, 4);
    }
}

// ============================================================ 0x00edf4c0
// @ 0x00edf4c0
void Ed::F4C0()
{
    int* self = (int*)this;
    char* t = (char*)self;
    int p14 = *(int*)(t + 0x14);
    if (p14 == 0)
        return;
    int w = *(int*)(t + 0x18);
    f00edf2c0(w, 1);
    SPUIHelpers_RemoveWindowCallback((void*)w, (void*)&f00edf370);
    VC0((void*)(p14 + 0x24), 8);
    VC0((void*)p14, 8);
    *(int*)(t + 0x14) = 0;
}

// ============================================================ 0x00edf370
// @ 0x00edf370
bool __cdecl f00edf370(int p1, int* p2, int p3)
{
    if (*(int*)((char*)p2 + 8) == 0xc) {
        int v = *(int*)(*(int*)((char*)p3 + 0x4c) + 0x118);
        if (v == 0 || (((*(u32*)(v + 4) >> 0xe) & 1) && !(((*(u32*)(v + 4) >> 0x12)) & 1)))
            f00edf3c0(p1, p3, 0);
    }
    return false;
}

// ============================================================ 0x00edf3c0
// 0x00edf2c0 reads a third argument in EDI (retail's caller leaves p2 there: `mov edi,[esp+0x10]`
// and keeps it in a callee-saved register across the call), which no C++ convention reproduces.
// Load it explicitly around each call and keep EDI saved, as the original does (push edi/pop edi).
// @ 0x00edf3c0
void __cdecl f00edf3c0(int p1, int p2, char flag)
{
    if (flag) {
        __asm { mov eax, p2 }
        __asm { push edi }
        __asm { mov edi, eax }
        f00edf2c0(p1, 0);
        __asm { pop edi }
        SPUIHelpers_CreateCallbackWinProc((void*)p1, (void*)&f00edf370, 2, 0, (void*)p2);
    } else {
        __asm { mov eax, p2 }
        __asm { push edi }
        __asm { mov edi, eax }
        f00edf2c0(p1, 1);
        __asm { pop edi }
        SPUIHelpers_RemoveWindowCallback((void*)p1, (void*)&f00edf370);
    }
}

// ============================================================ 0x00edfce0
// @ 0x00edfce0
bool __cdecl f00edfce0(void* obj, int* p2)
{
    bool b = ((Viso*)obj)->F26440(*p2) == 0;
    if (b) {
        MGR()->F45970();
        ((Viso*)obj)->F28c10(*p2);
        MGR()->F45a80();
    }
    return b;
}

// ============================================================ 0x00edfd30
// @ 0x00edfd30
bool __cdecl f00edfd30(char* p1, char* p2)
{
    char a = *p1;
    char b = *p2;
    bool diff = (a != b);
    if (diff) {
        MGR()->F45970();
        *p1 = *p2;
        MGR()->F45a80();
    }
    return diff;
}

// ============================================================ 0x00edfda0
// @ 0x00edfda0
bool __cdecl f00edfda0(int* p1, int* p2)
{
    bool diff = (*p1 != *p2);
    if (diff) {
        MGR()->F45970();
        *p1 = *p2;
        MGR()->F45a80();
    }
    return diff;
}

// ============================================================ 0x00edfd70
// 0x00edfda0 is called as a real function here (retail: `call 0xedfda0; add esp,8`), so use a
// body-less declaration of the same VA: a local definition would be inlined into this leaf.
extern "C" bool FUN_00edfda0(int*, int*);
// @ 0x00edfd70
bool __cdecl f00edfd70(int p1, u32 p2, int p3, u32* p4)
{
    bool r = false;
    if (p2 < *p4)
        r = FUN_00edfda0((int*)p1, (int*)(p3 + p2 * 4));
    return r;
}

// ============================================================ 0x00edfde0
// @ 0x00edfde0
bool __fastcall f00edfde0(int self)
{
    u32 v = *(u32*)(self + 0x224);
    if (((v >> 4) & 1) != 0 || ((v >> 1) & 1) != 0 || ((v >> 2) & 1) != 0)
        return true;
    return false;
}

// ============================================================ 0x00edfea0
// @ 0x00edfea0
bool Ed::FEA0(float* out1, float* out2)
{
    int self = (int)this;
    *out1 = *(float*)(self + 0x18);
    *out2 = *(float*)(self + 0x1c);
    return true;
}

// ============================================================ 0x00edfec0
// @ 0x00edfec0
void __fastcall f00edfec0(int self)
{
    void (*fp)(int) = *(void(**)(int))(self + 0x10);
    if (fp != 0)
        fp(*(int*)(self + 0x14));
}

// ============================================================ 0x00edfe10
// @ 0x00edfe10
void* Ed::FE10(int* p2, int p3, int p4)
{
    void* self = this;
    char* t = (char*)self;
    *(void**)(t + 4) = (void*)0x13ec458;
    *(int*)(t + 8) = 0;
    *(void**)(t) = (void*)0x148a930;
    *(void**)(t + 4) = (void*)0x14651ac;
    *(int*)(t + 0xc) = (int)p2;
    if (p2 != 0)
        VC0((void*)p2, 0xbc);
    *(int*)(t + 0x14) = p4;
    *(int*)(t + 0x10) = p3;
    *(float*)(t + 0x1c) = 0.0f;
    *(float*)(t + 0x18) = 0.0f;
    ((VHide*)self)->f00edd440((float*)(t + 0x18), (float*)(t + 0x1c));
    return self;
}

// ============================================================ 0x00edfb30
struct Host { char pad[0x18]; void FB30(int, int, char, int); };
extern char g_host_15ac6f0[];
struct LaunchBlock {
    int  id;           // +0x00
    int  gameMode;     // +0x04
    int  m08, m0c;
    char b10, b11, b12, b13, b14; char p15[3];
    int  m18, m1c, m20;
    char b24; char p25[3];
    int  m28;
    char b2c; char p2d[3];
    int  m30, m34, m38, m3c, m40, m44;
};
// @ 0x00edfb30
void Host::FB30(int p2, int p3, char p4, int p5)
{
    char* t = (char*)this;
    *(int*)(t + 0x10) = p5;
    *(char*)(t + 0x14) = p4;
    *(int*)(t + 0xc) = p3;
    *(int*)(t + 8) = p2;
    int edi = MGR()->F3e8a0(p2);

    LaunchBlock L;
    ((void(__thiscall*)(void*))FUN_00644b10)(&L);
    L.id = FNVHash((int)"ScenarioGameplaySkinning", 0x811c9dc5, 1);
    L.gameMode = FUN_00b5b800();
    L.m30 = 0xad0e52;
    L.m18 = *(int*)(edi + 0x28);
    L.m1c = *(int*)(edi + 0x2c);
    L.m20 = *(int*)(edi + 0x30);
    L.m38 = (int)this;
    L.b24 = 0;
    L.b11 = 1;

    void* ms = SP_MessageServer();
    VC2(ms, 0x24, (int)(t + 4), 0x30c11c7);
    SP_cSPUIAssetBrowser_AdvancedLaunch(&L);
    ((void(__thiscall*)(void*))FUN_00644b60)(&L);
}

// ============================================================ 0x00edfcc0
// @ 0x00edfcc0
void __cdecl f00edfcc0(int p1, int p2, int p3, int p4)
{
    ((Host*)g_host_15ac6f0)->FB30(p1, p2, (char)p3, p4);
}

// ============================================================ 0x00edfbf0
struct Data {
    char pad[8];
    int  F45970(); int F45a80();
    int  m00f27670(); int m00f253e0();
};
// 0x00ed39a0 is ScnRecBody::DeselectTwo: thiscall, ECX = the record body reached through the
// 0x16c7aa4+0x14 manager's +0x14 field, one stack argument.
struct RecBody { void m00ed39a0(int); };
#define RECBODY()  (*(RecBody**)((char*)*(void**)((char*)DAT_016c7aa4 + 0x14) + 0x14))
extern "C" int FUN_00f27670(void*);
extern "C" int FUN_00f253e0(void*);
// @ 0x00edfbf0
void Ed::FBF0(int* param)
{
    int* self = (int*)this;
    char* t = (char*)self;
    MGR()->F45970();
    int o = MGR()->F3e8a0(*(int*)(t + 8));
    if (*(char*)(t + 0x14) == 0) {
        int old = *(int*)(o + 0x24);
        *(int*)(o + 0x24) = 2;
        *(int*)(o + 0x28) = param[0];
        *(int*)(o + 0x2c) = param[1];
        *(int*)(o + 0x30) = param[2];
        *(char*)(o + 0x44) = 0;
        char c = (char)((Data*)o)->m00f27670();
        if (c == 0)
            c = (char)((Data*)o)->m00f253e0();
        if (c != 0 && *(int*)(o + 0x48) == 0 && old == 0)
            *(int*)(o + 0x48) = 1;
    } else {
        *(int*)(o + 0x48) = 2;
        *(int*)(o + 0x50) = param[0];
        *(int*)(o + 0x54) = param[1];
        *(int*)(o + 0x58) = param[2];
        *(char*)(o + 0x6c) = 0;
    }
    RECBODY()->m00ed39a0(*(int*)(t + 8));
    MGR()->F41a10(*(int*)(t + 8));
    MGR()->F45a80();
}

// ============================================================ 0x00edfa30
// @ 0x00edfa30
bool __cdecl f00edfa30(int index, float* out, char* lowClipped, char* highClipped, int propId)
{
    if (out == 0 || lowClipped == 0 || highClipped == 0)
        return false;
    void* volatile obj = 0;
    void* pm = SP_PropertyManager();
    void* old = obj;
    if (old != 0) {
        obj = 0;
        ((void(__thiscall*)(void*))VTP(old)[1])(old);
    }
    VCP3(pm, 0x2c, 0x2980610e, DAT_015ac654, &obj);
    if (obj == 0)
        return false;
    int count = 0;
    float* arr = 0;
    SP_GetPropertyAsFloatArray(obj, propId, &count, &arr);
    if (arr == 0 || count <= 2) {
        if (obj != 0)
            VC0(obj, 4);
        return false;
    }
    int i = index;
    *lowClipped = 0;
    *highClipped = 0;
    if (i <= 0) {
        i = 0;
        *lowClipped = 1;
    }
    int hi = count - 1;
    if (i >= hi) {
        i = hi;
        *highClipped = 1;
    }
    *out = arr[i];
    if (obj != 0)
        VC0(obj, 4);
    return true;
}

// ============================================================ 0x00edf730
// @ 0x00edf730
bool __cdecl f00edf730(float value, int* outIndex, int* outLow, int* outHigh, int propId)
{
    if (outIndex == 0 || outLow == 0 || outHigh == 0)
        return false;
    void* volatile obj = 0;
    void* pm = SP_PropertyManager();
    void* old = obj;
    if (old != 0) {
        obj = 0;
        ((void(__thiscall*)(void*))VTP(old)[1])(old);
    }
    VCP3(pm, 0x2c, 0x2980610e, DAT_015ac654, &obj);
    if (obj == 0)
        return false;
    int count = 0;
    float* arr = 0;
    SP_GetPropertyAsFloatArray(obj, propId, &count, &arr);
    if (arr == 0 || count <= 2) {
        if (obj != 0)
            VC0(obj, 4);
        return false;
    }
    *outLow = 0;
    *outHigh = count - 1;
    for (int i = 0; i < count; ++i) {
        if (arr[i] >= value) {
            *outIndex = i;
            if (obj != 0)
                VC0(obj, 4);
            return true;
        }
    }
    if (obj != 0)
        VC0(obj, 4);
    return false;
}

// ============================================================ 0x00edf2c0
// @ 0x00edf2c0
void __cdecl f00edf2c0(int p1, int p2)
{
    int ids[2];
    ids[0] = 0x3791005;
    ids[1] = 0x3791004;
    for (unsigned i = 0; i < 2; ++i) {
        void* e = VCP2((void*)p1, 0xf0, ids[i], 1);
        if (e == 0)
            continue;
        VC0(e, 0);
        VC2(e, 0x7c, 2, p2);
        VC1(e, 0xb8, 0);
        VC0(e, 4);
    }
}

// ============================================================ 0x00edef10
struct Win { char pad[4]; void* FindWindowByID(int, int); };
// @ 0x00edef10
void Ed::FEF10()
{
    int* self = (int*)this;
    char* t = (char*)self;
    int v = MGR()->F3e8a0(*(int*)(t + 0x20));
    if (v == 0)
        return;
    int h = FUN_00eece20(v);
    int val;
    switch (h) {
    case (int)0xe34e8a60: val = 0x79305e0; break;
    case (int)0xb10e526f: val = 0x79306c0; break;
    case (int)0xcf56099a: val = 0x79315e8; break;
    case (int)0xd37c1045:
    case 0x5b3d1d0d:      val = 0x7930648; break;
    case 0x6031c03a:      val = 0x79306f0; break;
    default:              val = 0x83ca530; break;
    }
    for (unsigned u = 0; u < 0x18; u += 4) {
        int id = *(int*)((char*)DAT_0148a708 + u);
        bool sel = (id == val);
        void* w = ((Win*)*(void**)(t + 0x10))->FindWindowByID(id, 1);
        if (w != 0)
            VC2(w, 0x7c, 1, sel);
    }
    void* nw = ((Win*)*(void**)(t + 0x10))->FindWindowByID(val, 1);
    void* old = *(void**)(t + 0x18);
    if (nw != old) {
        if (nw != 0)
            VC0(nw, 0);
        *(void**)(t + 0x18) = nw;
        if (old != 0)
            VC0(old, 4);
    }
    char flag;
    int m = FUN_00f078a0();
    if (m == 2) {
        flag = 1;
    } else {
        int n2 = FUN_00f078a0();
        flag = 0;
        if (n2 == 1)
            flag = 1;
    }
    void* p = *(void**)(t + 0x18);
    void* q = VCP2(p, 0xf0, 0x74656a0, 1);
    if (q != 0) {
        void* r = VCP1(q, 0xc, 0x8ed27e7a);
        if (r != 0)
            VC2(r, 0x28, 4, flag);
    }
}

// ============================================================ 0x00edf090
// @ 0x00edf090
void Ed::F090(int arg)
{
    int* self = (int*)this;
    char* t = (char*)self;
    int o = MGR()->F3e8a0(*(int*)(t + 0x20));
    if (o == 0)
        return;
    int base = FUN_00efc520() * 0x4e0 + *(int*)(o + 0x70);
    *(int*)(t + 0x24) = arg;

    void* w = *(void**)(t + 0x18);
    void* esi;
    if (w != 0) {
        esi = VCP2(w, 0xf0, arg, 1);
        if (esi != 0) {
            void* p = VCP1(esi, 0xc, 0x8ed27e7a);
            if (p != 0)
                VC2(p, 0x28, 4, 1);
        }
    } else {
        esi = 0;
    }
    void* q = VCP2(esi, 0xf0, 0x742be58, 1);
    if (q != 0)
        VC2(q, 0x7c, 1, 1);

    int id = 0x742cbe0;
    switch (arg) {
    case 0x742bd98:
        id = FUN_00edcec0((int*)(base + 0x4a8), DAT_0148a720, &DAT_0148a734) + 0x742cbe0;
        break;
    case 0x742bdb0:
        id = FUN_00edcec0((int*)(base + 0x4b0), DAT_0148a754, &DAT_0148a760) + 0x742cbe0;
        break;
    case 0x742bdc0:
        id = FUN_00edcec0((int*)(base + 0x4b4), DAT_0148a764, &DAT_0148a770) + 0x742cbe0;
        break;
    case 0x742bdd0:
        id = FUN_00edcec0((int*)(base + 0x4b8), DAT_0148a774, &DAT_0148a788) + 0x742cbe0;
        break;
    }

    void* r = VCP2(esi, 0xf0, id, 1);
    if (r != 0) {
        void* p = VCP1(r, 0xc, 0x8ed27e7a);
        if (p != 0)
            VC2(p, 0x28, 4, 1);
    }
}

// ============================================================ 0x00edf510
struct BehaviorUI {
    char  pad00[0x14];
    void* m14;        // +0x14  swatch item
    void* m18;        // +0x18  palette window
    char  pad1c[4];
    int   m20;        // +0x20  owner/game-object id
    int   m24;        // +0x24  selected item id
};
struct SwatchItem {
    char  pad00[0x24];
    void* m24;        // +0x24  embedded cSPPaletteItemUI vtable
    char  pad28[0x24];
    void* m4c;        // +0x4c
};
struct PaletteInfo {
    char  pad00[8];
    void* m08;        // +0x08
    char  pad0c[4];
    void* m10;        // +0x10
    char  pad14[4];
    u16   m18;        // +0x18
};
// @ 0x00edf510
void Ed::F510()
{
    BehaviorUI* self = (BehaviorUI*)this;
    if (self->m14 != 0)
        return;
    if (self->m18 == 0)
        return;
    void* palWin = VCP2(self->m18, 0xf0, 0x792e8a8, 1);
    if (palWin == 0)
        return;

    FUN_008068d0(palWin, 0, -1);

    void* pal = FUN_00f473a0(0x54, "UI/cScenarioEditModeBehaviorUI/PaletteItem", 0, 0, 0, 0);
    if (pal != 0) {
        pal = FUN_005c66a0(pal);
        if (pal != 0)
            VC0(pal, 4);
    }
    Key3 key;
    key.h0 = FNVHash((int)"BehaviorUIObject", 0x811c9dc5, 1);
    key.h4 = 0xb1b104;
    key.h8 = 0xd87454e6;
    if (!((char(__thiscall*)(void*, Key3*, int, int))FUN_005c6810)(pal, &key, 0, 0)) {
        if (pal != 0)
            VC0(pal, 8);
        return;
    }

    SwatchItem* sw = (SwatchItem*)FUN_00f473a0(0x6c, "UI/cScenarioEditModeBehaviorUI/SwatchItemUI", 0, 0, 0, 0);
    if (sw != 0)
        sw = (SwatchItem*)FUN_00ece990(sw);
    self->m14 = sw;
    VC0(sw, 4);

    PaletteInfo* info = (PaletteInfo*)FUN_00f473a0(0x34, "UI/cScenarioEditModeBehaviorUI/PaletteInfo", 0, 0, 0, 0);
    if (info != 0) {
        info = (PaletteInfo*)FUN_005c64e0(info);
        if (info != 0)
            VC0(info, 4);
    }
    if (info->m08 != 0) {
        int* rc = (int*)info->m08;
        info->m08 = 0;
        int n = rc[1] - 1;
        rc[1] = n;
        if (n == 0) {
            rc[1] = 1;
            ((void(__thiscall*)(void*, int))((void**)rc[0])[0])(rc, 1);
        }
    }
    if (info->m10 != 0) {
        void* p = info->m10;
        info->m10 = 0;
        VC0(p, 4);
    }
    info->m18 = 0x268a;

    VC2(palWin, 0x7c, 0x10, 1);

    void* sub = (char*)sw + 0x24;
    void* prev = VCP1(palWin, 0x10, (int)info);
    void** secVt = *(void***)((char*)this + 4);
    ((void(__thiscall*)(void*, int, int, int))secVt[1])(sub, (int)sw->m24, (int)palWin, (int)prev);

    ((void(__thiscall*)(void*, int))FUN_005f2290)(sw->m4c, 0);

    void* mgr = FUN_00b3d320();
    void* pl = ((void*(__thiscall*)(void*))FUN_00b1de80)(mgr);
    float h = 1.0f;
    FUN_0040cf10(pl, 0xa25ab8e0, &h);
    ((void(__thiscall*)(void*, float))FUN_00ecd990)(sw, h);
    ((void(__thiscall*)(void*, int))FUN_00edce20)(this, 0);
    VC0(info, 8);
    if (pal != 0)
        VC0(pal, 8);
}

// ============================================================ 0x00edf830
// @ 0x00edf830
void __cdecl f00edf830(void* wnd, float value, char a, char b, int propId, void* text)
{
    if (wnd == 0)
        return;
    VC2(wnd, 0x7c, 1, 1);
    void* caption = VCP2(wnd, 0xf0, 0x7918378, 1);
    if (caption != 0) {
        if (text != 0) {
            VC1(caption, 0x80, (int)text);
        } else {
            wchar_t buf[0x20];
            FUN_00881ae0((long long)value, buf, 0x20);
            VC1(caption, 0x80, (int)buf);
        }
        bool flag = (a == 0 && b == 0);
        VC2(caption, 0x7c, 1, flag);
    }

    int idx = 0;
    int low = 0;
    int high = 0;
    f00edf730(value, &idx, &low, &high, propId);

    void* ctrl = VCP2(wnd, 0xf0, 0x742cd10, 1);
    if (ctrl != 0) {
        void* cast = VCP1(ctrl, 0xc, 0xf00a8a0);
        if (cast != 0) {
            VC2(cast, 0x24, low, 0);
            VC2(cast, 0x2c, high, 0);
        }
    }

    float ratio = ((float)idx - (float)low) / (float)(high - low);
    FUN_00edcf60(VCP2(wnd, 0xf0, 0x742cd10, 1), ratio);

    void* v = VCP2(wnd, 0xf0, 0x769d5a63, 1);
    if (v != 0)
        VC2(v, 0x7c, 1, a);
    v = VCP2(wnd, 0xf0, 0x769d5a64, 1);
    if (v != 0)
        VC2(v, 0x7c, 1, b);
    v = VCP2(wnd, 0xf0, 0xb698347b, 1);
    if (v != 0)
        VC2(v, 0x7c, 1, a);
    v = VCP2(wnd, 0xf0, 0xb698347a, 1);
    if (v != 0)
        VC2(v, 0x7c, 1, b);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct Win {
    void FindWindowByID();   // 0x008105b0 (equiv t2)
};
}
