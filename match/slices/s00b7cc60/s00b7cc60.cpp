// Slice s00b7cc60: Pie-menu rebuild + commodity-node menu + a family of small container
// helpers (destroy/move/copy of 0x18-byte WStr-ish elements) and the property-manager probes.
//
// The 0x18-byte element is { wchar_t* begin; wchar_t* end; wchar_t* cap; int f0c; int f10; int f14; }.
// cfa0/d000 build one with an SSO fallback to the static empty string at 0x01667bac; d0d0/d120 copy
// ranges; cf10/cf50 destroy ranges.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

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

void  operator_delete__(void* p);                               // 0x00f47380
void* operator_new(int size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0

struct ListNode { ListNode* mpPrev; ListNode* mpNext; void* mpPayload; };
struct ServerObj { char pad[0x2c]; int mMode; bool OnPieMsg(int msg, int arg); };

// ---- globals ---------------------------------------------------------------------------
void* DAT_0168817c;
void* DAT_01688150;
int   DAT_01688154;

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
void __fastcall FUN_00b7cc60(int* param_1, int* param_2)
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
        ((void(__thiscall*)(void*))VT(gim, 100))(gim);
    }
    DAT_01688150 = param_2;
    DAT_01688154 = 1;
    void* mem = operator_new(200, "Simulator/Pie Menu", 0, 0, 0, 0);
    if (mem)
        pie = (IV*)SPUIPieMenu_ctor(mem);
    IV* old = (IV*)DAT_0168817c;
    if (pie != old) {
        if (pie) ((void(__thiscall*)(void*))VT(pie, 0))((void*)pie);
        DAT_0168817c = pie;
        if (old) ((void(__thiscall*)(void*))VT(old, 4))((void*)old);
    }
    char ok = ((char(__thiscall*)(IV*, const wchar_t*, const wchar_t*, int, int))VT(DAT_0168817c, 0x1c))
                  ((IV*)DAT_0168817c, L"PieMenuBase", L"PieMenuIcons", 0x40464100, 0);
    if (ok) {
        FUN_00817eb0((void*)FUN_00b7c790, param_1);
        int count = (param_1[1] - param_1[0]) / 0x18;
        for (int i = 0; i < count; i++) {
            int base = param_1[0] + i * 0x18;
            FUN_0081a940(*(int*)(base + 0x10), *(int*)(base), *(int*)(base + 0x14), 1);
        }
        FUN_008182c0((void*)FUN_00b7c750, param_1);
    }
    float a, b;
    if (param_2 == 0) {
        FUN_00804ed0(&a, &b);
    } else {
        float rect[8];
        float* r = (float*)((void*(__thiscall*)(int*, void*))VT(param_2, 0x6c))(param_2, rect);
        a = (r[0] + r[3]) * 0.5f;
        IV* app = (IV*)SP_App();
        ((void(__thiscall*)(IV*, void*, float*))VT(app, 0x58))(app, rect, &a);
        FUN_007c4180(&a, rect);
        float wa[4];
        FUN_007c4180(wa, rect);
        a = wa[2] * 0.5f;
        b = wa[3] * 0.5f;
    }
    IV* x = (IV*)FUN_00b3d240();
    ((void(__thiscall*)(IV*, int))VT(x, 100))(x, 0x303d8d78);
    void* sp = operator_new(0x14, "Simulator/cPieMenuScreenPosition", 0, 0, 0, 0);
    void* scr = sp ? SPUIPieMenuScreenPos_ctor(sp, param_2) : 0;
    FUN_00819ad0(&a, 0, scr, 7);
}

// =======================================================================================
// 00b7cf10 -- destroy a range of 0x18-byte string elements
// =======================================================================================
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
void __fastcall FUN_00b7d180(int* vec, int /*edx unused*/, int* pos, int* value)
{
    int* end = (int*)vec[1];
    if (end != (int*)vec[2]) {
        if (value <= end && end < value + 6)
            value += 6;
        if (end != 0)
            ((WVec*)vec)->destroy_range(end - 6, end);
        FUN_00b7d120(value, end - 6, end);
        if (value != (int*)vec[0])
            ((WStr*)value)->assign((const void*)value[0], (const void*)value[1]);
        vec[1] = vec[1] + 0x18;
        return;
    }
    int count = ((int)end - vec[0]) / 0x18;
    int cap;
    if (count == 0)
        cap = 1;
    else {
        cap = count * 2;
        if (cap == 0)
            cap = 0;
    }
    int* n;
    if (cap == 0)
        n = 0;
    else
        n = (int*)operator_new(cap * 0x18, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* mid = FUN_00b7d000((int*)vec[0], end, n);
    if (mid)
        ((WStr*)mid)->copy((const WStr*)value);
    int* newEnd = FUN_00b7d000(end, end, mid + 6);
    FUN_00b7cf50(end, end, (int)(mid + 6));
    if (vec[0] && *(int*)(vec[0] - 4) != 0)
        operator_delete__((void*)vec[0]);
    vec[0] = (int)n;
    vec[1] = (int)newEnd;
    vec[2] = (int)((char*)n + cap * 0x18);
}

// =======================================================================================
// 00b7d2e0 -- cCityInputStrategy::PrepareCommodityNodeMenu
// =======================================================================================
// retail: `this` in ecx, then name/a3/a4 on the stack (ret 0xc); the edx slot is unused
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
void __fastcall FUN_00b7d3e0(int p)
{
    IV* srv = (IV*)SP_MessageServer();
    ((void(__thiscall*)(IV*, int, int))VT(srv, 0x20))(srv, p - 4, 0x29ffa8d);
}

// =======================================================================================
// 00b7d420 -- message handler for the pie-menu screen-position request
// =======================================================================================
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
void __fastcall FUN_00b7d810(int param_1)
{
    switch (*(unsigned*)(param_1 + 0x28)) {
    case 0: {
        int* list = (int*)(param_1 + 0x1c);
        if ((int*)*list != list && *(int*)(param_1 + 0x30) == 0) {
            int pmodel = (int)SP_PlanetModel();
            int* pi = *(int**)(pmodel + 0x24);
            int i2 = *(int*)(*list + 8);
            if (*(int*)(i2 + 0x13c) == 0) {
                FUN_00b7d7b0((ListNode**)list);
                return;
            }
            if (pi == 0) {
                FUN_00c70110((void*)i2);
                FUN_00b7d7b0((ListNode**)list);
                SP_TerrainEditor(1);
                FUN_00f67890(0);
                int* g = (int*)FUN_00b8da60();
                if (*g == 0) {
                    void* x = FUN_00c713e0(0);
                    FUN_00b8d8a0(x, 0, 0);
                    int v = **(int**)(pmodel + 0x24);
                    FUN_0067dd50();
                    (*(void(**)(void*, void*))(v + 0x8c))(0, 0);
                    *(unsigned char*)(param_1 + 0x2d) = 1;
                    *(unsigned*)(param_1 + 0x28) = 1;
                    return;
                }
                FUN_00f355b0(*(void**)(*(int*)(param_1 + 0x30) + 0x13c));
                *(unsigned char*)(param_1 + 0x2d) = 1;
                *(unsigned*)(param_1 + 0x28) = 1;
                return;
            }
            int i5 = (*(int(**)(void))(*(int*)pi + 8))();
            int i4 = (int)FUN_00c713e0(0);
            if (*(int*)(i5 + 0x10) == *(int*)(i4 + 8)) {
                i5 = (*(int(**)(void))(*(int*)pi + 8))();
                int* pe = (int*)FUN_00c713e0(0);
                if (*(int*)(i5 + 8) == *pe &&
                    (*(char(**)(void))(*(int*)pi + 0xd8))() != 0) {
                    (*(void(**)(void))(*(int*)pi + 0x10))();
                    FUN_00fbd6b0(0);
                    SP_TerrainEditor(1);
                    FUN_00f678b0(0);
                    FUN_00c70110((void*)i2);
                    FUN_00b7d7b0((ListNode**)list);
                    int v2 = *pi;
                    FUN_0067dd50();
                    if (!(*(char(**)(void*, void*))(v2 + 0x94))(0, 0)) {
                        int v3 = *pi;
                        FUN_0067dd50();
                        (*(void(**)(void*, void*))(v3 + 0x8c))(0, 0);
                    }
                    *(unsigned char*)(param_1 + 0x2d) = 0;
                    *(unsigned*)(param_1 + 0x28) = 2;
                    return;
                }
            }
        }
        break;
    }
    case 1: {
        int pmodel = (int)SP_PlanetModel();
        int v = **(int**)(pmodel + 0x24);
        FUN_0067dd50();
        if (!(*(char(**)(void*, void*))(v + 0x94))(0, 0)) {
            int v2 = **(int**)(pmodel + 0x24);
            FUN_0067dd50();
            (*(void(**)(void*, void*))(v2 + 0x8c))(0, 0);
        }
        if (*(int**)(pmodel + 0x24) != 0 &&
            (*(char(**)(void))(**(int**)(pmodel + 0x24) + 0x50))() != 0) {
            *(unsigned*)(param_1 + 0x28) = 2;
            return;
        }
        break;
    }
    case 2:
        *(unsigned*)(param_1 + 0x28) = 3;
        FUN_01037a20(*(void**)(param_1 + 0x30));
        return;
    case 3:
        break;
    case 4: {
        if (*(char*)(param_1 + 0x2d) != 0) {
            SP_PlanetModel();
            FUN_00b8c0f0();
        }
        int* e = (int*)FUN_00c713e0(0);
        int v = *e;
        SP_TerrainEditor(0);
        FUN_00f67890(0);
        SP_TerrainEditor(0);
        FUN_00f678b0(0);
        *(unsigned*)(param_1 + 0x28) = 0;
        void* h = *(void**)(param_1 + 0x30);
        if (h != 0) {
            *(unsigned*)(param_1 + 0x30) = 0;
            ((void(__thiscall*)(void*))VT(h, 0xc0))(h);
        }
        *(unsigned char*)(param_1 + 0x2d) = 0;
        IV* srv = (IV*)SP_MessageServer();
        ((void(__thiscall*)(IV*, unsigned, int, int))VT(srv, 0x14))(srv, 0x99eda4cd, v, 0);
        break;
    }
    }
}
