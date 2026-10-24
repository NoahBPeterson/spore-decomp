// Slice s00e0a4c0 -- palette/tiled-layout grid owner: page rebuilding, palette ramp
// generation, scroll-frame placement and camera-facing sprite helpers.
//
// The retail class is unnamed in the PDB; every function here except UpdatePallete is a
// FUN_* with no symbol.  Its members are recovered from the disassembly (+0x04/+0x08 the
// two scroll-frame windows, +0x0c a ResourceMan::Key, +0x18 the palette-page ref vector,
// +0x30 the selected-index vector, +0x5c the message handler and +0x280 the 0x81-entry
// palette table).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef int           i32;

struct Float3 { float x, y, z; };
struct cPaletteGrid;

// ---------------------------------------------------------------------------------------------
// retail globals
// ---------------------------------------------------------------------------------------------
float g_1485720;
float g_1471064;
float g_1470f1c;
float g_13eb1bc;
float g_13eb8b0;
float g_15a4bfc;
float g_15a4c00;
float g_16a2024;
float g_16a203c;
float g_15a4cb8;
u32   g_16a2028;
u32   g_16a202c;
u8    g_16a1fa0;
u32   g_16a2040;
u32   g_16a2044;
u32   g_16a2048;
u32   g_16a1f9c;
u32   g_16a1f98;

extern "C" {
void*  __cdecl memcpy(void*, const void*, unsigned int);
double __cdecl sqrt(double);
double __cdecl atan2(double, double);
double __cdecl fabs(double);
double __cdecl sin(double);
double __cdecl cos(double);
}

// ---------------------------------------------------------------------------------------------
// retail interfaces
// ---------------------------------------------------------------------------------------------
struct IWin;

struct ISlot {
    virtual void v00();
    virtual void v04();
    virtual void v08();
};

struct IWin {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void* v0C(u32 name);
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void* v1C();
    virtual void  v20();
    virtual void  v24();
    virtual void  v28();
    virtual void  v2C();
    virtual void  v30();
    virtual void  v34();
    virtual void* v38();
    virtual void  v3C();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual IWin* v4C();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58();
    virtual void  v5C();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6C(void* child);
    virtual void  v70(float x, float y);
    virtual void  v74();
    virtual void  v78();
    virtual void  v7C(int a, int b);
    virtual void  v80();
    virtual void  v84();
    virtual bool  v88(void* a, void* b);
    virtual void  v8C();
    virtual void  v90();
    virtual void  v94(void* p);
    virtual void  v98();
    virtual void  v9C();
    virtual void  vA0();
    virtual void  vA4();
    virtual void  vA8();
    virtual void  vAC();
    virtual void  vB0();
    virtual void  vB4();
    virtual void  vB8();
    virtual void  vBC();
    virtual void  vC0();
    virtual void  vC4();
    virtual void  vC8();
    virtual void  vCC();
    virtual void  vD0();
    virtual void  vD4();
    virtual void  vD8(void* child);
};

struct cSPUILayout {
    cSPUILayout* ctor();                                   // 0x00810000
    bool Init(const void* key, bool b, u32 name);          // 0x008120d0
    bool SetParentWin(void* parent, bool b, u32 name);     // 0x008121b0
    u8 pad[0x18];
};

struct cHelper {
    void Set(float v, int index);                          // 0x0082e340
};

struct cObj95 {
    void Set(float v);                                     // 0x0095ed60
};

// EA::AutoRefCount-like temporary: AddRef on construction, Release on destruction.
struct AutoRef {
    cSPUILayout* p;
    AutoRef(cSPUILayout* q) : p(q) {
        if (q != 0)
            ((ISlot*)q)->v04();
    }
    ~AutoRef() {
        if (p != 0)
            ((ISlot*)p)->v08();
    }
};

// eastl::vector<AutoRefCount<...> > / eastl::vector<u32> layout
struct cRefVector {
    u32*  mBegin;
    u32*  mEnd;
    u32*  mCap;
    void  Reserve(u32 n);                                  // 0x00d01790
    void* erase(u32* first, u32* last);                    // 0x005c2170
    void  DoInsert(u32* pos, void** val);                  // 0x005c8480
};

struct cU32Vector {
    u32* mBegin;
    u32* mEnd;
    u32* mCap;
    void erase(u32* first, u32* last) {
        u32* e = mEnd;
        memcpy(first, last, (u32)((char*)e - (char*)last));
        mEnd -= (last - first);
    }
    void DoInsertValueI(u32* pos, const u32& val);          // 0x004558a0
    void DoAssign(const int* first, const int* last, u32 n);// 0x004d04f0
};

// ---------------------------------------------------------------------------------------------
// the retail class
// ---------------------------------------------------------------------------------------------
struct cPaletteGrid {
    u8 pad00[4];
    void* mWin4;            // +0x04
    void* mWin8;            // +0x08
    u32 mKey0C;             // +0x0c
    u32 mKey10;             // +0x10
    u32 mKey14;             // +0x14
    cRefVector mPages;      // +0x18
    u8 pad24[0x0c];
    cU32Vector mSel;        // +0x30
    u8 pad3C[0x20];
    u32 mHandler;           // +0x5c
    u32 mHandlerA0;         // +0x60
    u32 mHandlerA1;         // +0x64
    u32 mHandlerA2;         // +0x68
    u32 mHandlerA3;         // +0x6c
    u8 pad70[0x19c];
    IWin* mTarget;          // +0x20c
    u8 pad210[8];
    float m218;             // +0x218
    float m21C;             // +0x21c
    float m220;             // +0x220
    u8 pad224[0x15];
    u8 m239;                // +0x239
    u8 pad23A[2];
    int m23C;               // +0x23c
    u8 pad240[0x40];
    u8 mPal[0x81];          // +0x280
    u8 pad301[0x53];
    float m354;             // +0x354
    u8 pad358[4];
    u32 m35C;               // +0x35c
    u8 pad360[0x630];
    float m990;             // +0x990
    float m994;             // +0x994
    float m998;             // +0x998
    float m99C;             // +0x99c
    float m9A0;             // +0x9a0

    void FUN_00e09d10();    // 0x00e09d10
    bool LayoutCells();     // 0x00e0a270 (declared bool: callers return its eax)
    bool AddPages(u32 count); // 0x00e0a680
};

// A sibling class: here +0x04 is an embedded UI window (its vptr lives at +4).
struct cPaletteGrid2 {
    u8 pad00[4];
    IWin mWin;              // +0x04
    u8 pad08[0x204];
    IWin* mTarget;          // +0x20c
};

// ---------------------------------------------------------------------------------------------
// retail callees
// ---------------------------------------------------------------------------------------------
void*  __cdecl FUN_00f473a0(u32 size, const char* name, u32 a, u32 b, u32 c, u32 d);
void*  __cdecl FUN_00807600(const wchar_t* name, void** out, int flag);
void   __cdecl FUN_008076f0(void* p);
void   __cdecl FUN_00571db0(u32 h, u32 a0, u32 a1, u32 a2, u32 a3);
__int64 __fastcall FUN_0093a3a0(void* ecx_this);
void*  __cdecl FUN_0067dd50();
float* __cdecl SPUIHelpers_GetBoundingScreenRect(float* out, IWin* win, char flag);

void   __cdecl UpdatePallete(u32* buf, int count, u32 colA, u32 colB, u32 colC, u32 divisor);

// ---------------------------------------------------------------------------------------------
// functions
// ---------------------------------------------------------------------------------------------

typedef bool (__thiscall *FN_AddPages)(cPaletteGrid*, u32);

// @ 0x00e0a4c0
bool __fastcall FUN_00e0a4c0(cPaletteGrid* ecx_this, void* edx, IWin* win, Float3* key)
{
    bool ok = false;
    if (win != 0) {
        IWin* old8 = (IWin*)ecx_this->mWin8;
        if (old8 != 0) {
            ecx_this->mWin8 = 0;
            old8->v04();
        }
        IWin* created = (IWin*)FUN_00807600(L"ScrollFrameVerticalGeneric", &ecx_this->mWin8, 1);
        IWin* old4 = (IWin*)ecx_this->mWin4;
        if (created != old4) {
            if (created != 0)
                created->v00();
            ecx_this->mWin4 = created;
            if (old4 != 0)
                old4->v04();
        }
        if (ecx_this->mWin4 != 0 && ecx_this->mWin8 != 0) {
            u32* k = (u32*)key;
            win->vD8(ecx_this->mWin4);
            IWin* w4 = (IWin*)ecx_this->mWin4;
            w4->v6C(win->v38());
            w4->v70(0.0f, 0.0f);
            ecx_this->mKey0C = k[0];
            ecx_this->mKey10 = k[1];
            ecx_this->mKey14 = k[2];
            ecx_this->FUN_00e09d10();
            ok = true;
        }
    }
    return ok;
}

// @ 0x00e0a5c0
void __fastcall FUN_00e0a5c0(cPaletteGrid* ecx_this, void* edx)
{
    if (ecx_this->mHandler != 0) {
        u32 h = ecx_this->mHandler;
        u32 a0 = ecx_this->mHandlerA0;
        u32 a1 = ecx_this->mHandlerA1;
        u32 a2 = ecx_this->mHandlerA2;
        u32 a3 = ecx_this->mHandlerA3;
        ecx_this->mHandler = 0;
        FUN_00571db0(h, a0, a1, a2, a3);
    }
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    FUN_008076f0(ecx_this->mWin4);
    if (ecx_this->mWin4 != 0) {
        ISlot* p = (ISlot*)ecx_this->mWin4;
        ecx_this->mWin4 = 0;
        p->v04();
    }
    if (ecx_this->mWin8 != 0) {
        ISlot* p = (ISlot*)ecx_this->mWin8;
        ecx_this->mWin8 = 0;
        p->v04();
    }
}

// @ 0x00e0a640
void __fastcall FUN_00e0a640(cPaletteGrid* ecx_this, void* edx)
{
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    ecx_this->mSel.erase(ecx_this->mSel.mBegin, ecx_this->mSel.mEnd);
}

// @ 0x00e0a680
bool cPaletteGrid::AddPages(u32 count)
{
    cRefVector& pages = mPages;
    pages.Reserve((u32)(pages.mEnd - pages.mBegin) + count);
    for (u32 i = 0; i < count; i++) {
        u8* mem = (u8*)FUN_00f473a0(0x18, "UI/TiledLayout", 0, 0, 0, 0);
        cSPUILayout* layout = 0;
        if (mem != 0)
            layout = ((cSPUILayout*)mem)->ctor();
        {
            AutoRef local(layout);
            if (pages.mEnd < pages.mCap) {
                u32* slot = pages.mEnd;
                pages.mEnd = slot + 1;
                if (slot != 0) {
                    *slot = (u32)layout;
                    if (layout != 0)
                        ((ISlot*)layout)->v04();
                }
            } else {
                pages.DoInsert(pages.mEnd, (void**)&local);
            }
        }
        if (!layout->Init(&mKey0C, false, 0x5b598fa))
            return false;
        layout->SetParentWin(mWin8, true, 0x5b598fa);
    }
    return true;
}

// @ 0x00e0a780
bool __fastcall FUN_00e0a780(cPaletteGrid* ecx_this, void* edx, Float3* key, u32 count)
{
    bool ok = false;
    u32* k = (u32*)key;
    ecx_this->mKey0C = k[0];
    ecx_this->mKey10 = k[1];
    ecx_this->mKey14 = k[2];
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    ecx_this->mSel.erase(ecx_this->mSel.mBegin, ecx_this->mSel.mEnd);
    if (ecx_this->AddPages(count)) {
        ecx_this->FUN_00e09d10();
        return ecx_this->LayoutCells();
    }
    return ok;
}

// @ 0x00e0a800
bool __fastcall FUN_00e0a800(cPaletteGrid* ecx_this, void* edx, u32 val)
{
    bool ok = false;
    u32 v = val;
    if (!ecx_this->AddPages(v))
        return ok;
    if (ecx_this->mSel.mBegin != ecx_this->mSel.mEnd) {
        u32* end = ecx_this->mSel.mEnd;
        if (end < ecx_this->mSel.mCap) {
            ecx_this->mSel.mEnd = end + 1;
            if (end != 0) {
                *end = v;
                return ecx_this->LayoutCells();
            }
        } else {
            ecx_this->mSel.DoInsertValueI(end, v);
        }
    }
    return ecx_this->LayoutCells();
}

// @ 0x00e0a870
bool __fastcall FUN_00e0a870(cPaletteGrid* ecx_this, void* edx, Float3* key, u32 count, int* array)
{
    bool ok = false;
    u32* k = (u32*)key;
    ecx_this->mKey0C = k[0];
    ecx_this->mKey10 = k[1];
    ecx_this->mKey14 = k[2];
    int even = 0;
    int odd = 0;
    u32 i = 0;
    u32 tail = 0;
    if (count >= 2) {
        u32 limit = count - 1;
        do {
            even += array[i];
            odd += array[i + 1];
            i += 2;
        } while (i < limit);
    }
    if (i < count)
        tail = (u32)array[i];
    tail += (u32)(even + odd);
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    ecx_this->mSel.erase(ecx_this->mSel.mBegin, ecx_this->mSel.mEnd);
    if (ecx_this->AddPages(tail)) {
        ecx_this->mSel.DoAssign(array, array + count, count);
        ecx_this->FUN_00e09d10();
        return ecx_this->LayoutCells();
    }
    return ok;
}

// @ 0x00e0a950
bool __cdecl FUN_00e0a950()
{
    if ((g_16a2028 | g_16a202c) != 0) {
        __int64 t = FUN_0093a3a0(&g_16a2028);
        double d = (double)t;
        return d * g_16a203c < g_15a4cb8;
    }
    return false;
}

// @ 0x00e0a9a0
void __cdecl FUN_00e0a9a0(const Float3* p, u32 a, u32 b)
{
    const u32* q = (const u32*)p;
    g_16a1fa0 = 1;
    g_16a2040 = q[0];
    g_16a2044 = q[1];
    g_16a2048 = q[2];
    g_16a1f9c = a;
    g_16a1f98 = b;
}

// @ 0x00e0a9e0
double __fastcall FUN_00e0a9e0(cPaletteGrid* ecx_this, void* edx, float a, float b)
{
    float s = ecx_this->m218 * b;
    int i = (int)s;
    if (s < (float)i)
        i--;
    if (i < 0)
        i = 0;
    else if (i > 0x80)
        i = 0x80;
    int range = (int)((0u - (u32)(ecx_this->m239 != 0)) & 0xffffff80u) + 0x100;
    double p = (double)(u32)ecx_this->mPal[i];
    double r = (double)range;
    return (((double)ecx_this->m21C * (double)a - p) * r) / (r - (p + p)) * (double)ecx_this->m220;
}

// @ 0x00e0aa80
double __fastcall FUN_00e0aa80(cPaletteGrid* ecx_this, void* edx, float a, float b)
{
    float s = ecx_this->m218 * b;
    int i = (int)s;
    if (s < (float)i)
        i--;
    if (i < 0)
        i = 0;
    else if (i > 0x80)
        i = 0x80;
    int range = (int)((0u - (u32)(ecx_this->m239 != 0)) & 0xffffff80u) + 0x100;
    double p = (double)(u32)ecx_this->mPal[i];
    double r = (double)range;
    return (p + ((r - (p + p)) * (double)ecx_this->m21C * (double)a) / r) * (double)ecx_this->m220;
}

// @ 0x00e0ab30
bool __fastcall FUN_00e0ab30(cPaletteGrid* ecx_this, void* edx, float a, float b, u8* out)
{
    if (FUN_00e0aa80(ecx_this, edx, 0.0, b) <= (double)a) {
        if ((double)a < FUN_00e0aa80(ecx_this, edx, (float)ecx_this->m23C, b)) {
            *out = 1;
            return false;
        }
    }
    *out = 0;
    return false;
}

// @ 0x00e0aba0
void __fastcall FUN_00e0aba0(cPaletteGrid* ecx_this, void* edx, void* obj)
{
    ((cObj95*)obj)->Set(ecx_this->m354);
}

// @ 0x00e0abc0
bool __fastcall FUN_00e0abc0(cPaletteGrid* ecx_this, void* edx, u32 a, u32 b, u32 c, void* d)
{
    ((IWin*)ecx_this)->v94(d);
    return true;
}

// @ 0x00e0abe0
void __fastcall FUN_00e0abe0(cPaletteGrid* ecx_this, void* edx, float a, float b, float c, char d)
{
    double ang = (double)g_15a4bfc - atan2((double)b, (double)a);
    float fa = (float)ang;
    double sph = atan2((double)c, sqrt((double)a * (double)a + (double)b * (double)b));
    float fv = (float)sph;

    if (d != 0 || fv < ecx_this->m998) {
        ecx_this->m998 = fv;
        if (d != 0)
            goto set_angles;
    }
    if (fv > ecx_this->m99C) {
        ecx_this->m99C = fv;
        if (d != 0) {
        set_angles:
            ecx_this->m990 = fa;
            ecx_this->m9A0 = fa;
            ecx_this->m994 = fa;
            return;
        }
    }
    if (fabs(ang - (double)ecx_this->m9A0) > (double)g_15a4c00) {
        if (ecx_this->m9A0 > fa)
            fa = g_16a2024 + fa;
        else
            fa = fa - g_16a2024;
    }
    if (fa < ecx_this->m990)
        ecx_this->m990 = fa;
    else if (fa > ecx_this->m994)
        ecx_this->m994 = fa;
}

// @ 0x00e0ad00
void __fastcall FUN_00e0ad00(cPaletteGrid* ecx_this, void* edx, u32 flags)
{
    ecx_this->m35C |= flags;
}

// @ 0x00e0ad10
void __cdecl UpdatePallete(u32* buf, int count, u32 colA, u32 colB, u32 colC, u32 divisor)
{
    u32 uVar8 = colC >> 16;
    u32 uVar1 = colC & 0xff;
    u32 uVar9 = colC >> 8;
    u32 uVar2 = colA & 0xff;
    int iVar3 = (int)(colB & 0xff) - (int)uVar2;
    u32 uVar12 = (colA >> 16) & 0xff;
    u32 uVar10 = (colA >> 8) & 0xff;
    int iVar13 = (int)((colB >> 8) & 0xff) - (int)uVar10;
    int iVar17 = (int)((colB >> 16) & 0xff) - (int)uVar12;
    u32 uVar4 = (u32)(count << 4) / divisor;
    int i = 0;
    int iVar15 = 0xff - count;
    int iVar5 = -count;
    int local34 = -(iVar3 * count);
    int iVar14 = -(iVar13 * count);
    int accB = 0;
    int accG = 0;
    int accR = 0;
    int iVar18 = -(iVar17 * count);

    do {
        if (count < i || count == 0) {
            if (iVar5 < 5) {
                buf[i] = 0xffbe9f50;
                buf[0x100 + i] = 0xffae8f40;
            } else {
                u32 rr = (u32)(iVar18 / iVar15 + (int)uVar12) & 0xff;
                u32 gg = (u32)(iVar14 / iVar15 + (int)uVar10) & 0xff;
                u32 bb = (u32)(local34 / iVar15 + (int)uVar2) & 0xff;
                u32 v = (rr << 16) | (gg << 8) | bb;
                buf[i] = v | 0xff000000;
                u32 p = (((rr * divisor) & 0xfffffff0) << 12) | (((gg << 8) & 0xff0) * divisor);
                p &= 0xffffff00;
                buf[0x100 + i] = p | ((bb * divisor) >> 4) | 0xff000000;
            }
        } else {
            buf[i] = (((accR / count) | 0xff00) << 8 | (accG / count)) << 8 | (accB / count);
            buf[0x100 + i] = (((accR / (int)uVar4) | 0xff00) << 8 | (accG / (int)uVar4)) << 8 |
                             (accB / (int)uVar4);
        }
        accR += (int)uVar8;
        accB += (int)uVar1;
        local34 += iVar3;
        iVar18 += iVar17;
        iVar14 += iVar13;
        accG += (int)uVar9;
        i++;
        iVar5++;
    } while (i < 0x100);
}

static float FUN_00e0af90_clamp(float v)
{
    if (v < -1.0f)
        v = -1.0f;
    if (v > 1.0f)
        v = 1.0f;
    return v;
}

// @ 0x00e0af90
void __cdecl FUN_00e0af90(IWin* win)
{
    float* src = (float*)((IWin*)FUN_0067dd50())->v1C();
    float m[8];
    float* d = m;
    int n = 8;
    do {
        *d++ = *src++;
    } while (--n);

    float rect[4];
    SPUIHelpers_GetBoundingScreenRect(rect, win, 0);

    float x0 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[3]) * rect[3] - 0.5f) * 2.0f);
    float y0 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[1]) * rect[1] - 0.5f) * 2.0f);
    float x1 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[3]) * rect[2] - 0.5f) * 2.0f);
    float y1 = FUN_00e0af90_clamp(((1.0f / (float)(int)m[1]) * rect[3] - 0.5f) * 2.0f);

    float ny0 = -y0;
    float ny1 = -y1;

    IWin* parent = win->v4C();
    cHelper* h = 0;
    if (parent != 0)
        h = (cHelper*)parent->v0C(0x5234b49);

    const float& xmin = (x0 > x1) ? x1 : x0;
    h->Set(xmin, 0);
    const float& ymin = (ny0 > ny1) ? ny1 : ny0;
    h->Set(ymin, 1);
    const float& xmax = (x1 > x0) ? x1 : x0;
    h->Set(xmax, 2);
    const float& ymax = (ny1 > ny0) ? ny1 : ny0;
    h->Set(ymax, 3);
    h->Set((float)fabs(1.0 / (double)(x1 - x0)), 4);
    h->Set((float)fabs(1.0 / (double)(ny1 - ny0)), 5);
}

// @ 0x00e0b230
void __fastcall FUN_00e0b230(cPaletteGrid2* ecx_this, void* edx, ISlot* arg)
{
    ISlot* old = (ISlot*)ecx_this->mTarget;
    if (arg != old) {
        if (arg != 0)
            arg->v00();
        ecx_this->mTarget = (IWin*)arg;
        if (old != 0)
            old->v04();
    }
    IWin* w = &ecx_this->mWin;
    w->v7C(0x10, 1);
    w->v7C(0x40, 1);
}

// @ 0x00e0b290
bool __fastcall FUN_00e0b290(cPaletteGrid2* ecx_this, void* edx, void* arg)
{
    IWin* t = ecx_this->mTarget;
    if (t != 0)
        return t->v88(arg, &ecx_this->mWin);
    return true;
}

// @ 0x00e0b2c0
void __cdecl FUN_00e0b2c0(float* out, u32 unused, float* a, float* b, float w)
{
    double f2 = atan2((double)b[2], sqrt((double)b[1] * (double)b[1] + (double)b[0] * (double)b[0]));
    double f4 = (f2 - 0.5 * (double)w) + (1.0 - (double)a[1]) * (double)w;
    double cc = cos(f4);
    double f3 = atan2((double)b[1], (double)b[0]);
    double f5 = (double)(1.0f - a[0]) * (double)w;
    f3 = (f5 + f5) + (((double)g_15a4bfc - f3) - (double)w);
    out[0] = (float)(sin(f3) * cc);
    out[1] = (float)(cos(f3) * cc);
    out[2] = (float)sin(f4);
}
