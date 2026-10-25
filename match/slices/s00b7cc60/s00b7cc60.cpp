// Slice s00b7cc60: Pie-menu rebuild + commodity-node menu + a family of small container
// helpers (destroy/move/copy of 0x18-byte WStr-ish elements) and the property-manager probes.
//
// The 0x18-byte element is { wchar_t* begin; wchar_t* end; wchar_t* cap; int f0c; int f10; int f14; }.
// cfa0/d000 build one with an SSO fallback to the static empty string at 0x01667bac; d0d0/d120 copy
// ranges; cf10/cf50 destroy ranges.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

typedef unsigned char uchar;
typedef unsigned int  uint;

// generic vtable-bearing object
#define VS(n) virtual void vs##n();
struct IV {
    VS(0)  VS(1)  VS(2)  VS(3)  VS(4)  VS(5)  VS(6)  VS(7)
    VS(8)  VS(9)  VS(10) VS(11) VS(12) VS(13) VS(14) VS(15)
    VS(16) VS(17) VS(18) VS(19) VS(20) VS(21) VS(22) VS(23)
    VS(24) VS(25) VS(26) VS(27) VS(28) VS(29) VS(30) VS(31)
    VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47)
    VS(48) VS(49) VS(50) VS(51) VS(52) VS(53) VS(54) VS(55)
    VS(56) VS(57) VS(58) VS(59) VS(60) VS(61) VS(62) VS(63)
    VS(64) VS(65) VS(66) VS(67)
};
#undef VS
#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// ---- the 0x18-byte string-ish element -------------------------------------------------
struct WStr {
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCap;     // +0x08
    int   f0c;       // +0x0c
    int   f10;       // +0x10
    int   f14;       // +0x14
    void  AllocateSelf(int n);                                  // 0x00429760
    void  assign(const void* begin, const void* end);           // 0x00423650
    WStr* copy(const WStr* src);                                // 0x00b7cfa0
};
void DoInsertValue(void* dst, const void* src, unsigned size);  // 0x011e0744 (memcpy)

// the vector-of-WStr owner: its destroy_range helper is a thiscall member (ecx=this, ret 8)
struct WVec {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCap;      // +0x08
    void destroy_range(int* begin, int* end);                   // 0x00b7cf10
};
struct AllocHeader { int mSize; };  // eastl allocation header (at mem-4)

void  operator_delete__(void* p);                               // 0x00f47380
void* operator_new(int size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0

struct ListNode { ListNode* mpPrev; ListNode* mpNext; void* mpPayload; };
struct ServerObj { char pad[0x2c]; int mMode; bool OnPieMsg(int msg, int arg); };

// ---- pie-menu terrain-editor state machine (00b7d810) --------------------------------
struct LookupResult {
    int   mField00;          // +0x00
    int   mField04;          // +0x04
    int   mField08;          // +0x08
    uchar mPad0c[4];         // +0x0c
    int   mField10;          // +0x10
};
struct EditorTarget {        // node payload / field30 object
    uchar mPad00[0x13c];     // +0x000
    void* mpField13c;        // +0x13c
};
struct PieVec {              // vector<0x18-byte entry>
    int* mpBegin;            // +0x00
    int* mpEnd;              // +0x04
    int* mpCap;              // +0x08
};
struct PieEntry {            // one 0x18-byte pie entry
    int   mField00;          // +0x00
    uchar mPad04[0x0c];      // +0x04
    int   mField10;          // +0x10
    int   mField14;          // +0x14
};
struct Vec3f { float x, y, z; };
struct Rect4f { float mLeft, mTop, mWidth, mHeight; };
struct Rect6f { float f0, f1, f2, f3, f4, f5; };
struct Obj188 { void* mpField00; };
struct PieEditor {
    uchar   mPad00[0x1c];    // +0x00
    ListNode mList;          // +0x1c (embedded sentinel)
    uint    mState28;        // +0x28
    uchar   mByte2c;         // +0x2c
    uchar   mFlag2d;         // +0x2d
    uchar   mPad2e[2];       // +0x2e..+0x2f
    void*   mpField30;       // +0x30
};
struct cPlanetModel {
    uchar mPad00[0x24];      // +0x00
    void* mpPlanet24;        // +0x24
    bool  FUN_00b8d8a0(unsigned a, bool refresh, unsigned c);   // 0x00b8d8a0
};
struct cPlanet {
    void SetRampEnabled(bool on);                               // 0x00fbd6b0
};

// ---- globals ---------------------------------------------------------------------------
void* DAT_0168817c;
void* DAT_01688150;
unsigned char DAT_01688154;

// ---- externs ---------------------------------------------------------------------------
void* __cdecl SP_MessageServer();                               // 0x0067dcc0
void* __cdecl SP_PropertyManager();                             // 0x0067de30
void* __cdecl SP_PlanetModel();
void* __cdecl SP_App();
void* __cdecl SP_GameInputManager();
int   __cdecl SP_TerrainEditor(int on);
void* __fastcall FUN_00c713e0(void* self);   // 0x00c713e0 (ecx receiver, no stack args)
void* __cdecl FUN_00b3d240();
void* __cdecl FUN_00b8da60();
void  __cdecl FUN_00b8d8a0(void* a, void* b, void* c);
void  __cdecl FUN_00b8c0f0();
void  __cdecl FUN_00f67890(void* p);
void  __cdecl FUN_00f678b0(void* p);
void  __cdecl FUN_00c70110(void* p);
void  __cdecl FUN_00f355b0(void* p);
void  __cdecl FUN_00fbd6b0(int p);
void* __cdecl FUN_0067dd50();
void  __cdecl FUN_01037a20(void* p);
void  __cdecl FUN_00818330();
void  __cdecl FUN_00817eb0(void* fn, void* arg);
void  __cdecl FUN_008182c0(void* fn, void* arg);
void  __cdecl FUN_0081a940(int a, int b, int c, int d);
void  __cdecl FUN_00819ad0(void* a, void* b, void* c, int d);
void  __cdecl FUN_00804ed0(void* a, void* b);
void  __cdecl FUN_007c4180(void* a, void* b);
void  __cdecl FUN_00805ea0(void* out);
void  __cdecl FUN_00b7c790();
void  __cdecl FUN_00b7c750();
void* __cdecl SPUIPieMenu_ctor(void* mem);
void* __cdecl SPUIPieMenuScreenPos_ctor(void* mem, int* arg);

// forward decls of the local helpers
int  __cdecl FUN_00b7cf50(int* begin, int* end, int dest);
int* __cdecl FUN_00b7d000(int* src, int* end, int* dst);
int* __cdecl FUN_00b7d0d0(int* begin, int* end, int* dst);
int* __cdecl FUN_00b7d120(int* first, int* last, int* outLast);
// retail ABI: this in ecx, pos and value on the stack (ret 8); edx is unused
void __fastcall FUN_00b7d180(int* vec, int /*edx unused*/, int* pos, int* value);
void __fastcall FUN_00b7d7b0(ListNode** p);

// =======================================================================================
// 00b7cc60 -- rebuild the pie menu
// =======================================================================================
// @ 0x00b7cc60
// retail ABI: ecx = pie vector, screen and flag on the stack, ret 8
void __fastcall FUN_00b7cc60(int* vec, int /*edx unused*/, int* screen, int flag)
{
    IV* pie = 0;
    if (DAT_0168817c != 0) {
        FUN_00818330();
        ((void(__thiscall*)(void*))VT(DAT_0168817c, 0x24))(DAT_0168817c);
        void* old = DAT_0168817c;
        if (old) {
            DAT_0168817c = 0;
            ((void(__thiscall*)(void*))VT(old, 4))(old);
        }
        void* gim = SP_GameInputManager();
        ((void(__thiscall*)(void*, int, int))VT(gim, 0x64))(gim, 0x4518450, 1);
    }
    DAT_01688150 = screen;
    DAT_01688154 = 1;
    void* mem = operator_new(200, "Simulator/Pie Menu", 0, 0, 0, 0);
    if (mem)
        pie = (IV*)((void*(__fastcall*)(void*))SPUIPieMenu_ctor)(mem);
    IV* old = (IV*)DAT_0168817c;
    if (pie != old) {
        if (pie) ((void(__thiscall*)(void*))VT(pie, 0))((void*)pie);
        DAT_0168817c = pie;
        if (old) ((void(__thiscall*)(void*))VT(old, 4))((void*)old);
    }
    char ok = ((char(__thiscall*)(IV*, const wchar_t*, const wchar_t*, int, int, int, int))VT(DAT_0168817c, 0x1c))
                  ((IV*)DAT_0168817c, L"PieMenuBase", L"PieMenuIcons", 0x40464100, 0, 0, 0);
    if (ok) {
        PieVec* pv = (PieVec*)vec;
        void* gp = DAT_0168817c;
        ((void(__fastcall*)(void*, int, void*, void*))FUN_00817eb0)(gp, 0, (void*)FUN_00b7c790, vec);
        int count = (int)((char*)pv->mpEnd - (char*)pv->mpBegin) / 0x18;
        for (int i = 0; i < count; i++) {
            PieEntry* e = (PieEntry*)((char*)pv->mpBegin + i * 0x18);
            ((void(__fastcall*)(void*, int, int, int, int, int))FUN_0081a940)
                (gp, 0, e->mField10, e->mField00, e->mField14, 1);
        }
        gp = DAT_0168817c;
        ((void(__fastcall*)(void*, int, void*, void*))FUN_008182c0)(gp, 0, (void*)FUN_00b7c750, vec);
    }

    float f1, f2;
    if (flag != 0 && screen != 0) {
        Rect6f rect;
        Vec3f pt;
        Vec3f out;
        Rect4f wa;
        Rect6f* r = (Rect6f*)((void*(__thiscall*)(int*, void*))VT(screen, 0x6c))(screen, &rect);
        pt.x = (r->f0 + r->f3) * 0.5f;
        pt.y = (r->f4 + r->f1) * 0.5f;
        pt.z = (r->f5 + r->f2) * 0.5f;
        void* app = SP_App();
        void* app2 = ((void*(__thiscall*)(void*, void*, void*))VT(app, 0x58))(app, &out, &pt);
        ((void(__fastcall*)(void*, int, void*, void*))FUN_007c4180)(app2, 0, &out, &pt);
        FUN_00805ea0(&wa);
        f1 = ((out.x + 1.0f) * wa.mWidth) * 0.5f;
        f2 = ((1.0f - out.y) * wa.mHeight) * 0.5f;
    } else {
        FUN_00804ed0(&f1, &f2);
    }

    void* srv = FUN_00b3d240();
    ((void(__thiscall*)(void*, int))VT(srv, 0x64))(srv, 0x303d8d78);
    void* sp = operator_new(0x14, "Simulator/cPieMenuScreenPosition", 0, 0, 0, 0);
    void* scr = sp ? ((void*(__fastcall*)(void*, int, int*))SPUIPieMenuScreenPos_ctor)(sp, 0, screen) : 0;
    ((void(__fastcall*)(void*, int, float, float, void*, int))FUN_00819ad0)
        (DAT_0168817c, 0, f1, f2, scr, 7);
}

// =======================================================================================
// 00b7cf10 -- destroy a range of 0x18-byte string elements
// =======================================================================================
// @ 0x00b7cf10
void WVec::destroy_range(int* begin, int* end)
{
    for (; begin < end; begin += 6) {
        int p = begin[0];
        int d = (begin[2] - p) & 0xfffffffe;
        if (d > 2 && p)
            operator_delete__((void*)p);
    }
}

// =======================================================================================
// 00b7cf50 -- destroy a range, returning the advanced output cursor
// =======================================================================================
// @ 0x00b7cf50
int FUN_00b7cf50(int* begin, int* end, int dest)
{
    while (begin != end) {
        int p = begin[0];
        int d = (begin[2] - p) & 0xfffffffe;
        if (d > 2 && p)
            operator_delete__((void*)p);
        begin += 6;
        dest += 0x18;
    }
    return dest;
}

// =======================================================================================
// 00b7cfa0 -- copy-construct a WStr
// =======================================================================================
// @ 0x00b7cfa0
WStr* WStr::copy(const WStr* src)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCap = 0;
    int count = (int)((const char*)src->mpEnd - (const char*)src->mpBegin) >> 1;
    AllocateSelf(count + 1);
    void* dst = mpBegin;
    DoInsertValue(dst, src->mpBegin, count * 2);
    void* e = (char*)dst + count * 2;
    mpEnd = e;
    *(unsigned short*)e = 0;
    f10 = src->f10;
    f14 = src->f14;
    return this;
}

// =======================================================================================
// 00b7d000 -- uninitialized_copy of WStr elements with SSO
// =======================================================================================
// @ 0x00b7d000
int* FUN_00b7d000(int* src, int* end, int* dst)
{
    if (src == end)
        return dst;
    do {
        if (dst) {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
            int s = src[0];
            int count = (src[1] - s) >> 1;
            unsigned n = (unsigned)count + 1;
            if (n < 2) {
                dst[0] = (int)0x1667bac;
                dst[1] = (int)0x1667bac;
                dst[2] = (int)0x1667bae;
            } else {
                int size = (int)n * 2;
                int m = (int)operator_new(size, "Simulator", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                dst[0] = m;
                dst[1] = m;
                dst[2] = m + size;
            }
            int base = dst[0];
            DoInsertValue((void*)base, (const void*)s, (unsigned)(count * 2));
            int e = base + count * 2;
            dst[1] = e;
            *(unsigned short*)e = 0;
            dst[4] = src[4];
            dst[5] = src[5];
        }
        src += 6;
        dst += 6;
    } while (src != end);
    return dst;
}

// =======================================================================================
// 00b7d0d0 -- copy a range of WStr elements
// =======================================================================================
// @ 0x00b7d0d0
int* FUN_00b7d0d0(int* begin, int* end, int* dst)
{
    while (begin != end) {
        if (begin != dst)
            ((WStr*)dst)->assign((const void*)begin[0], (const void*)begin[1]);
        dst[4] = begin[4];
        dst[5] = begin[5];
        begin += 6;
        dst += 6;
    }
    return dst;
}

// =======================================================================================
// 00b7d120 -- copy_backward a range of WStr elements
// =======================================================================================
// @ 0x00b7d120
int* FUN_00b7d120(int* first, int* last, int* outLast)
{
    while (last != first) {
        last -= 6;
        outLast -= 6;
        if (last != outLast)
            ((WStr*)outLast)->assign((const void*)last[0], (const void*)last[1]);
        outLast[4] = last[4];
        outLast[5] = last[5];
    }
    return outLast;
}

// =======================================================================================
// 00b7d170 -- trivial 3-field clear of a ScheduleLocation
// =======================================================================================
// @ 0x00b7d170
int* __fastcall FUN_00b7d170(int* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    return p;
}

// =======================================================================================
// 00b7d180 FUN_00b7d180 -- vector::insert of one WStr element
// =======================================================================================
// retail ABI: this in ecx, pos and value on the stack (ret 8); edx is unused
// @ 0x00b7d180
void __fastcall FUN_00b7d180(int* vec, int /*edx unused*/, int* pos, int* value)
{
    WVec* v = (WVec*)vec;
    WStr* end = (WStr*)v->mpEnd;
    if (end != (WStr*)v->mpCap) {
        if (pos <= value && value < (int*)end)
            value = (int*)((char*)value + 0x18);
        if (end)
            end->copy(end - 1);
        FUN_00b7d120(pos, (int*)(end - 1), (int*)end);
        if (value != pos)
            ((WStr*)pos)->assign(((WStr*)value)->mpBegin, ((WStr*)value)->mpEnd);
        ((WStr*)pos)->f10 = ((WStr*)value)->f10;
        ((WStr*)pos)->f14 = ((WStr*)value)->f14;
        v->mpEnd = (int*)(end + 1);
        return;
    }
    int count = (int)(end - (WStr*)v->mpBegin);
    int cap;
    if (count == 0)
        cap = 1;
    else {
        cap = count * 2;
        if (cap == 0)
            cap = 0;
    }
    WStr* n;
    if (cap == 0)
        n = 0;
    else
        n = (WStr*)operator_new(cap * 0x18, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    WStr* mid = (WStr*)FUN_00b7d000((int*)v->mpBegin, pos, (int*)n);
    FUN_00b7cf50((int*)v->mpBegin, pos, (int)n);
    if (mid)
        mid->copy((WStr*)value);
    WStr* newEnd = (WStr*)FUN_00b7d000(pos, (int*)end, (int*)(mid + 1));
    FUN_00b7cf50(pos, (int*)end, (int)(mid + 1));
    if (v->mpBegin && ((AllocHeader*)v->mpBegin)[-1].mSize != 0)
        operator_delete__((void*)v->mpBegin);
    v->mpEnd = (int*)newEnd;
    v->mpBegin = (int*)n;
    v->mpCap = (int*)((char*)n + cap * 0x18);
}

// =======================================================================================
// 00b7d2e0 -- cCityInputStrategy::PrepareCommodityNodeMenu
// =======================================================================================
// retail: `this` in ecx, then name/a3/a4 on the stack (ret 0xc); the edx slot is unused
// @ 0x00b7d2e0
void __fastcall FUN_00b7d2e0(void* self, int /*edx unused*/, short* name, int a3, int a4)
{
    WStr local;
    local.mpBegin = (void*)0x1667bac;
    local.mpEnd   = (void*)0x1667bac;
    local.mpCap   = (void*)0x1667bae;
    short* p = name;
    while (*p != 0)
        p++;
    local.assign(name, p);
    local.f10 = a3;
    local.f14 = a4;
    int* endp = (int*)*(void**)((char*)self + 4);
    int* cap  = (int*)*(void**)((char*)self + 8);
    if (endp < cap) {
        *(void**)((char*)self + 4) = (char*)endp + 0x18;
        if (endp)
            ((WStr*)endp)->copy(&local);
    } else {
        FUN_00b7d180((int*)self, 0, endp, (int*)&local);
    }
    int d = ((int)local.mpCap - (int)local.mpBegin) & 0xfffffffe;
    if (d > 2 && local.mpBegin)
        operator_delete__(local.mpBegin);
}

// =======================================================================================
// 00b7d390 -- destroy a WStr vector and reset its end
// =======================================================================================
// @ 0x00b7d390
void __fastcall FUN_00b7d390(int* p)
{
    int begin = p[0];
    int end = p[1];
    int* r = FUN_00b7d0d0((int*)end, (int*)end, (int*)begin);
    ((WVec*)p)->destroy_range(r, (int*)p[1]);
    int n = (end - begin) / 0x18;
    p[1] = p[1] - n * 0x18;
}

// =======================================================================================
// 00b7d3e0 -- dispatch the pie-menu state change to the message server
// =======================================================================================
// @ 0x00b7d3e0
void __fastcall FUN_00b7d3e0(int p)
{
    IV* srv = (IV*)SP_MessageServer();
    ((void(__thiscall*)(IV*, int, int))VT(srv, 0x20))(srv, p - 4, 0x29ffa8d);
}

// =======================================================================================
// 00b7d420 -- message handler for the pie-menu screen-position request
// =======================================================================================
// @ 0x00b7d420
bool ServerObj::OnPieMsg(int msg, int arg)
{
    bool r = true;
    if (msg == 0x29ffa8d && mMode == 3)
        mMode = 4;
    return r;
}

// =======================================================================================
// 00b7d440 -- stamp an id/flags into up to five UI rect descriptors
// =======================================================================================
// @ 0x00b7d440
void __stdcall FUN_00b7d440(int value, int a2, unsigned flags,
                            int* p4, int* p5, int* p6, int a7, int* p8, int* p9)
{
    int val = value;
    int zero = 0;
    if (p4) { p4[0] = val; p4[1] = zero; p4[2] = (flags & 0xe0ff28ff) | 0x2800; }
    if (p5) { p5[0] = val; p5[1] = zero; p5[2] = (flags & 0xe4ff28ff) | 0x4002800; }
    if (p6) { p6[0] = val; p6[1] = zero; p6[2] = (flags & 0xe5ff28ff) | 0x5002800; }
    if (p8) { p8[0] = val; p8[1] = zero; p8[2] = (flags & 0xe0ff28ff) | 0x2800; }
    if (p9) { p9[0] = val; p9[1] = zero; p9[2] = (flags & 0xe7ff28ff) | 0x7002800; }
}

// =======================================================================================
// 00b7d4f0 -- ask the property manager whether two flag variants exist
// =======================================================================================
// @ 0x00b7d4f0
int __stdcall FUN_00b7d4f0(int* p)
{
    int u1 = p[0];
    unsigned u2 = (unsigned)p[2];
    IV* pm = (IV*)SP_PropertyManager();
    char c = ((char(__thiscall*)(IV*, int, unsigned))VT(pm, 0x28))(pm, u1, (u2 & 0xe0ff28ff) | 0x2800);
    if (c) {
        pm = (IV*)SP_PropertyManager();
        c = ((char(__thiscall*)(IV*, int, unsigned))VT(pm, 0x28))(pm, u1, (u2 & 0xe7ff28ff) | 0x7002800);
        if (c)
            return 1;
    }
    return 0;
}

// =======================================================================================
// 00b7d580 FUN_00b7d580 -- property-manager round trip used when the selection is valid
// =======================================================================================
// @ 0x00b7d580
void __stdcall FUN_00b7d580(int p)
{
    int* a = (int*)FUN_00c713e0((void*)p);
    if (*a == 0)
        return;
    int* b = (int*)FUN_00c713e0((void*)p);
    if (*(int*)((char*)b + 8) == 0)
        return;
    int* e = (int*)FUN_00c713e0((void*)p);
    int v1 = e[0];
    unsigned fl = (unsigned)e[2];
    IV* pm = (IV*)SP_PropertyManager();
    if (!((char(__thiscall*)(IV*, int, unsigned))VT(pm, 0x28))(pm, v1, (fl & 0xe0ff28ff) | 0x2800))
        return;
    pm = (IV*)SP_PropertyManager();
    if (!((char(__thiscall*)(IV*, int, unsigned))VT(pm, 0x28))(pm, v1, (fl & 0xe7ff28ff) | 0x7002800))
        return;
    void* h1 = 0;
    pm = (IV*)SP_PropertyManager();
    ((void(__thiscall*)(IV*, int, unsigned, void**))VT(pm, 0x2c))(pm, v1, (fl & 0xe0ff28ff) | 0x2800, &h1);
    pm = (IV*)SP_PropertyManager();
    ((void(__thiscall*)(IV*, void*))VT(pm, 0x38))(pm, h1);
    if (h1) ((void(__thiscall*)(void*))VT(h1, 4))(h1);
    void* h2 = 0;
    pm = (IV*)SP_PropertyManager();
    ((void(__thiscall*)(IV*, int, unsigned, void**))VT(pm, 0x2c))(pm, v1, (fl & 0xe7ff28ff) | 0x7002800, &h2);
    pm = (IV*)SP_PropertyManager();
    ((void(__thiscall*)(IV*, void*))VT(pm, 0x38))(pm, h2);
    if (h2) { ((void(__thiscall*)(void*))VT(h2, 4))(h2); ((void(__thiscall*)(void*))VT(h2, 4))(h2); }
}

// =======================================================================================
// 00b7d750 -- prepend a node to a doubly linked list
// =======================================================================================
// @ 0x00b7d750
void __stdcall FUN_00b7d750(int head, void** payload)
{
    ListNode* n = (ListNode*)operator_new(0xc, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if ((char*)n + 8 != 0) {
        void* pv = *payload;
        n->mpPayload = pv;
        if (pv)
            ((void(__thiscall*)(void*))VT(pv, 0xbc))(pv);
    }
    ListNode* lst = (ListNode*)head;
    n->mpPrev = lst;
    n->mpNext = lst->mpNext;
    lst->mpNext->mpPrev = n;
    lst->mpNext = n;
}

// =======================================================================================
// 00b7d7b0 -- unlink and delete a list node
// =======================================================================================
// @ 0x00b7d7b0
void __fastcall FUN_00b7d7b0(ListNode** p)
{
    ListNode* n = *p;
    n->mpNext->mpPrev = n->mpPrev;
    n->mpPrev->mpNext = n->mpNext;
    void* pay = n->mpPayload;
    if (pay)
        ((void(__thiscall*)(void*))VT(pay, 0xc0))(pay);
    operator_delete__(n);
}

// =======================================================================================
// 00b7d810 -- pie-menu terrain-editor state machine
// =======================================================================================
// retail ABI: this in ecx, two unused stack args (ret 8)
// @ 0x00b7d810
void __fastcall FUN_00b7d810(PieEditor* self, int /*edx unused*/, int /*a2*/, int /*a3*/)
{
    switch (self->mState28) {
    case 0: {
        if (self->mList.mpPrev != &self->mList && self->mpField30 == 0) {
            cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
            void* planet = pm->mpPlanet24;
            EditorTarget* target = (EditorTarget*)self->mList.mpPrev->mpPayload;
            if (target->mpField13c == 0) {
                FUN_00b7d7b0((ListNode**)&self->mList);
                return;
            }
            if (planet == 0) {
                ((void(__fastcall*)(void*, int, void*))FUN_00c70110)(&self->mpField30, 0, target);
                FUN_00b7d7b0((ListNode**)&self->mList);
                void* te = ((void*(__cdecl*)())SP_TerrainEditor)();
                ((void(__fastcall*)(void*, int, int))FUN_00f67890)(te, 0, 1);
                EditorTarget* o30 = (EditorTarget*)self->mpField30;
                Obj188* g = (Obj188*)((void*(__fastcall*)(void*))FUN_00b8da60)(o30->mpField13c);
                if (g->mpField00 == 0) {
                    void* x = ((void*(__fastcall*)(void*, int, void*, void*))FUN_00c713e0)(o30, 0, 0, 0);
                    pm->FUN_00b8d8a0((unsigned)x, false, 0);
                    void* planet2 = pm->mpPlanet24;
                    void* key = FUN_0067dd50();
                    ((void(__thiscall*)(void*, void*))VT(planet2, 0x8c))(planet2, key);
                    self->mFlag2d = 1;
                    self->mState28 = 1;
                    return;
                }
                FUN_00f355b0(o30->mpField13c);
                self->mFlag2d = 1;
                self->mState28 = 1;
                return;
            }
            LookupResult* a = (LookupResult*)((void*(__thiscall*)(void*))VT(planet, 8))(planet);
            LookupResult* b = (LookupResult*)((void*(__fastcall*)(void*))FUN_00c713e0)(target);
            if (a->mField10 == b->mField08) {
                a = (LookupResult*)((void*(__thiscall*)(void*))VT(planet, 8))(planet);
                b = (LookupResult*)((void*(__fastcall*)(void*))FUN_00c713e0)(target);
                if (a->mField08 == b->mField00 &&
                    ((char(__thiscall*)(void*))VT(planet, 0xd8))(planet) != 0) {
                    void* r = ((void*(__thiscall*)(void*))VT(planet, 0x10))(planet);
                    ((cPlanet*)r)->SetRampEnabled(false);
                    void* te = ((void*(__cdecl*)())SP_TerrainEditor)();
                    ((void(__fastcall*)(void*, int, int))FUN_00f678b0)(te, 0, 1);
                    ((void(__fastcall*)(void*, int, void*))FUN_00c70110)(&self->mpField30, 0, target);
                    FUN_00b7d7b0((ListNode**)&self->mList);
                    void* key = FUN_0067dd50();
                    if (!((char(__thiscall*)(void*, void*))VT(planet, 0x94))(planet, key)) {
                        key = FUN_0067dd50();
                        ((void(__thiscall*)(void*, void*))VT(planet, 0x8c))(planet, key);
                    }
                    self->mFlag2d = 0;
                    self->mState28 = 2;
                    return;
                }
            }
        }
        break;
    }
    case 1: {
        cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
        void* planet = pm->mpPlanet24;
        void* key = FUN_0067dd50();
        if (!((char(__thiscall*)(void*, void*))VT(planet, 0x94))(planet, key)) {
            planet = pm->mpPlanet24;
            key = FUN_0067dd50();
            ((void(__thiscall*)(void*, void*))VT(planet, 0x8c))(planet, key);
        }
        planet = pm->mpPlanet24;
        if (planet != 0 &&
            ((char(__thiscall*)(void*))VT(planet, 0x50))(planet) != 0) {
            self->mState28 = 2;
            return;
        }
        break;
    }
    case 2:
        FUN_01037a20(self->mpField30);
        self->mState28 = 3;
        return;
    case 3:
        break;
    case 4: {
        if (self->mFlag2d != 0) {
            void* pm = SP_PlanetModel();
            ((void(__fastcall*)(void*))FUN_00b8c0f0)(pm);
        }
        LookupResult* e = (LookupResult*)((void*(__fastcall*)(void*))FUN_00c713e0)(self->mpField30);
        int v = e->mField00;
        void* te = ((void*(__cdecl*)())SP_TerrainEditor)();
        ((void(__fastcall*)(void*, int, int))FUN_00f67890)(te, 0, 0);
        te = ((void*(__cdecl*)())SP_TerrainEditor)();
        ((void(__fastcall*)(void*, int, int))FUN_00f678b0)(te, 0, 0);
        self->mState28 = 0;
        EditorTarget* o30 = (EditorTarget*)self->mpField30;
        if (o30 != 0) {
            self->mpField30 = 0;
            ((void(__thiscall*)(void*))VT(o30, 0xc0))(o30);
        }
        self->mFlag2d = 0;
        IV* srv = (IV*)SP_MessageServer();
        ((void(__thiscall*)(IV*, unsigned, int, int))VT(srv, 0x14))(srv, 0x99eda4cd, v, 0);
        break;
    }
    }
}
