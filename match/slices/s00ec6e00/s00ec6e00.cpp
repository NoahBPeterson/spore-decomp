// Slice s00ec6e00 -- SP cell-stage UI: unlocked-cards list + credits/window helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned short ushort;

// ---------------------------------------------------------------- globals
extern unsigned char g_16c7574[];      // 0x016c7574 (byte flags array; 0x16c7578 = [4])
extern unsigned char g_015abcd0;       // 0x015abcd0
extern void*         g_16c7aa4;        // 0x016c7aa4
extern void**        g_16c7584;        // 0x016c7584
extern void**        g_16c757c;        // 0x016c757c (singleton object; [0] = stage set)
extern float         g_16c7580;        // 0x016c7580
extern void*         g_16c7590;        // 0x016c7590 (pool object)
extern void**        g_16c759c;        // 0x016c759c (free-list begin)
extern void**        g_16c75a0;        // 0x016c75a0 (free-list end)
extern int           g_1440aec;        // 0x01440aec (iterator bias, == -4)

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00efc520(void);                       // 0x00efc520
void  __cdecl FUN_00ec6e00(void);                       // 0x00ec6e00
void* __cdecl SPUIHelpers_AutoSizeWindowForText(void*, int, int);  // 0x00806e40
int   __cdecl FUN_00830cf0(int);                        // 0x00830cf0
int   __cdecl FUN_00830d10(int);                        // 0x00830d10
int   __cdecl FUN_00830d60(void*, int);                 // 0x00830d60
int   __cdecl FUN_00830d30(void*, int);                 // 0x00830d30
int   __cdecl FUN_00830d20(int);                        // 0x00830d20
void  __cdecl FUN_008311f0(int, int);                   // 0x008311f0
void  __cdecl FUN_008312f0(int, int);                   // 0x008312f0
void  __cdecl FUN_00831270(int, int);                   // 0x00831270
void* __cdecl SP_WindowManager(void);                   // 0x0067caa0
void* __cdecl SP_PropertyManager(void);                 // 0x0067de30
void* __cdecl FUN_00805310(void*, int, void*);          // 0x00805310
void  __cdecl FUN_00806aa0(void*, void*, int);          // 0x00806aa0
int   __cdecl FUN_00ec6b20(int*, int);                  // 0x00ec6b20
int   __cdecl FUN_00ec6a00(void*);                      // 0x00ec6a00
int   __cdecl FUN_00ec6940(float*, float);              // 0x00ec6940
void  __cdecl FUN_008d2f30(void*, void*);               // 0x008d2f30
int   __cdecl FUN_00809970(void);                       // 0x00809970
int   __cdecl FUN_008053b0(void);                       // 0x008053b0
bool  __fastcall FUN_00f25730(void* self);              // 0x00f25730
bool  __fastcall FUN_00f25680(void* self);              // 0x00f25680
bool  __fastcall FUN_00f25670(void* self);              // 0x00f25670
bool  __fastcall FUN_00f25720(void* self);              // 0x00f25720
void* __fastcall FUN_00f3e8a0(void* pool, int, int idx);        // 0x00f3e8a0 (thiscall, ret 4)
void  __fastcall FUN_00f25190(void* self, int, void*, void*);   // 0x00f25190 (ret 8)
void  __fastcall FUN_00f28b80(void* self, int, void*);          // 0x00f28b80 (ret 4)
void  __fastcall FUN_0081b650(void* menu, int, int item, int flag);  // 0x0081b650 (thiscall, ret 8)
void  __cdecl SPUIHelpers_CreateImageFromResource(void*, int*, int, unsigned, unsigned); // 0x00806230
int*  __fastcall FUN_00ac20d0(int* self, int, int count, void* allocator);  // 0x00ac20d0 (ret 8)
void  __cdecl eastl_copy(void*, void*, void*, void*, void*);    // 0x0076ffd0 (5 pushes)
int*  __fastcall FUN_0041ea00(void* self);               // 0x0041ea00 (thiscall: value accessor)
void  __cdecl FUN_00f47380(void*);                       // 0x00f47380 (operator delete)
struct ILayout {
    void* FindWindowByID(unsigned, int);   // 0x008105b0 (thiscall: this=[g])
};

// virtual-call helpers used by the already-settled bodies below
typedef void* (__thiscall *FV_1)(void*);
typedef void* (__thiscall *FV_i)(void*, int);
typedef int   (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_v)(void*);
typedef int   (__thiscall *FB_i)(void*, int);
typedef bool  (__thiscall *FBb_i)(void*, int);

// ---------------------------------------------------------------- small types
struct Float2 { float x, y; };

// 0x20-byte entry of the cell UI state array (see FUN_00ec73c0 / FUN_00ec6d00).
struct CellEntry {
    char   used;            // +0x00
    char   pad_01[3];
    void*  window;          // +0x04
    int    value;           // +0x08
    char   pad_0c[0x14];
};
// 0x158-byte singleton describing the 10 visible cells.
struct CellUIState {
    int        pad_00[1];
    CellEntry  entries[10]; // +0x04
    int        count;       // +0x144
    int        pad_148;
    CellEntry* current;     // +0x14c
    int        posX;        // +0x150
    int        posY;        // +0x154
};
struct StageRecord { char pad_00[0x4a8]; int mode; char pad_4ac[0x34]; };  // 0x4e0
struct StageSet    { char pad_00[0x70]; StageRecord* frames; };
struct ListObj     { StageSet* set; void** begin; void** end; };
struct GameRoot    { char pad_00[0x74]; void* pool; };

struct UIObject {                       // header of every window/menu object
    void** vt;
    void*  Cast(int tag) {
        return ((void*(__thiscall*)(void*, int))vt[0x0c / 4])(this, tag);
    }
    void*  FindChild(unsigned id, int flag) {
        return ((void*(__thiscall*)(void*, unsigned, int))vt[0xf0 / 4])(this, id, flag);
    }
    void*  GetText() {
        return ((void*(__thiscall*)(void*))vt[0x3c / 4])(this);
    }
    void   ComputeRect(Float2* out, Float2 pos) {
        ((void(__thiscall*)(void*, Float2*, Float2))vt[0xc4 / 4])(this, out, pos);
    }
    float* GetRect2() {
        return ((float*(__thiscall*)(void*))vt[0x38 / 4])(this);
    }
    void   SetVisible(int a, int b) {
        ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(this, a, b);
    }
    void   SetState(unsigned v) {
        ((void(__thiscall*)(void*, unsigned))vt[0x5c / 4])(this, v);
    }
    void   SetText(const wchar_t* t) {
        ((void(__thiscall*)(void*, const wchar_t*))vt[0x80 / 4])(this, t);
    }
};

struct MenuItem {
    void*    vt;            // +0x00
    UIObject inner;         // +0x04
};

// 0x158-byte object produced by 0x00805310 and exposed through tag 0x4c058cf.
struct UnlockedCard {
    char pad_00[0x888];
    int  key;               // +0x888
};

// eastl::basic_string<wchar_t> (12-byte SSO-enabled string).
struct WideString { unsigned short *begin, *end, *cap; };
struct VecObj { int field0; void* begin; void* end; void* capacity; void* allocator; };

// ---------------------------------------------------------------- 0x00ec6e00
// @ 0x00ec6e00
void FUN_00ec6e00(void)
{
    *(int*)g_16c7574 = 0;
    g_16c7574[4] = 0;
    int idx = (int)FUN_00efc520();
    void* gg = g_16c7aa4;
    char* pool = *(char**)((char*)gg + 0x74);
    char* p = *(char**)(pool + 0x10);
    char* it = *(char**)(p + 0x2bf4);
    if (it != *(char**)(p + 0x2bf8)) {
        do {
            int v = *(int*)(*(char**)(it + 0x78) + idx * 0x4e0 + 0x4a8);
            if ((unsigned)(v - 2) < 4)
                g_16c7574[v - 1] = 1;
            it += 0x27e8;
        } while (it != *(char**)(*(char**)(*(char**)((char*)g_16c7aa4 + 0x74) + 0x10) + 0x2bf8));
    }
    g_015abcd0 = 0;
}

// ---------------------------------------------------------------- 0x00ec6e70
unsigned char FUN_00ec6e70(int i)
{
    if (g_015abcd0 != 0)
        FUN_00ec6e00();
    return g_16c7574[i];
}

// ---------------------------------------------------------------- 0x00ec6ea0
// @ 0x00ec6ea0
int FUN_00ec6ea0(int** param_1, int* param_2)
{
    int* piVar3 = (int*)param_1[0];
    if (piVar3 == (int*)param_1[1])
        return -1;
    int iVar2 = (int)(((char*)param_1[1] - (char*)piVar3) >> 3);
    int iVar1 = 0;
    if (iVar2 > 0) {
        do {
            if (*piVar3 == param_2[0] && piVar3[1] == param_2[1])
                return iVar1;
            ++iVar1;
            piVar3 += 2;
        } while (iVar1 < iVar2);
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ec6ee0
// @ 0x00ec6ee0
void FUN_00ec6ee0(int* param_1, int* param_2, char param_3)
{
    char* a = (char*)((FV_i)(*(void***)param_1)[0xa8 / 4])(param_1, 0);
    char* pcVar2 = a ? (char*)((FV_i)(*(void***)a)[0xc / 4])(a, 0x53eb526) : 0;
    char* b = (char*)((FV_i)(*(void***)param_2)[0xa8 / 4])(param_2, 0);
    char* esi = b ? (char*)((FV_i)(*(void***)b)[0xc / 4])(b, 0x53eb526) : 0;
    int u1 = FUN_00830cf0(0);
    ((FV_ii)(*(void***)pcVar2)[0xc / 4])(pcVar2, 0, u1);
    (void)esi;
    int u3 = (param_3 == 0) ? FUN_00830d10(0) : -1;
    FUN_008311f0(0, u3);
    char tmp[8];
    int u4 = FUN_00830d60(tmp, 0);
    ((FV_ii)(*(void***)pcVar2)[0xc / 4])(pcVar2, 0, u4);
    int u5 = FUN_00830d30(tmp, 0);
    FUN_008312f0(0, u5);
    int u6 = FUN_00830d20(0);
    FUN_00831270(0, u6);
    ((FV_v)(*(void***)param_1)[0x90 / 4])(param_1);
}

// ---------------------------------------------------------------- 0x00ec6fc0
// @ 0x00ec6fc0
void FUN_00ec6fc0(int param_1, int param_2, int* param_3)
{
    char* piVar3 = param_3 ? (char*)((FV_i)(*(void***)param_3)[0xc / 4])(param_3, 0xf15f4bd) : 0;
    char buf[16];
    float f0, f2;
    ((void(__thiscall*)(void*, void*, void*, void*))(*(void***)piVar3)[0x34 / 4])(piVar3, &buf, &f0, &f2);
    (void)f0; (void)f2;
    SPUIHelpers_AutoSizeWindowForText(param_3, 0, 0);
    (void)param_1; (void)param_2;
}

// ---------------------------------------------------------------- 0x00ec70a0
void FUN_00ec70a0(int param)
{
    char* w = (char*)((ILayout*)*g_16c7584)->FindWindowByID(0x8de6960, 1);
    ((FV_ii)(*(void***)w)[0x7c / 4])(w, 0x400, param);
}

// ---------------------------------------------------------------- 0x00ec70d0
// @ 0x00ec70d0
void FUN_00ec70d0(void* param_1)
{
    int    local_20, local_1c;     // integer drag coordinates
    float  local_18, local_14;     // their float images
    Float2 rectA, rectB;
    int    newIndex;

    FUN_008d2f30(&local_20, &local_1c);
    local_18 = (float)(int)local_1c;
    local_14 = (float)(int)local_20;

    UIObject* win = *(UIObject**)((char*)param_1 + 4);
    Float2 posA; posA.x = local_14; posA.y = local_18;
    win->ComputeRect(&rectA, posA);

    CellUIState* g = (CellUIState*)*g_16c7584;
    Float2 posB; posB.x = (float)g->posX; posB.y = (float)g->posY;
    win->ComputeRect(&rectB, posB);

    float* p = win->GetRect2();
    newIndex = *(int*)((char*)param_1 + 8);
    ((void(__thiscall*)(void*, float, float))(win->vt[0x64 / 4]))(
        win, p[0] - (rectA.x - rectB.x), p[1] - (rectA.y - rectB.y));
    g->posX = (int)local_14;
    g->posY = (int)local_18;

    int idx = FUN_00ec6940((float*)&rectB, (p[3] - p[1]) - 1.0f);
    win->SetState(idx == -1 ? 0x77ff0000u : 0xffffffffu);

    for (int i = 0; i < 0x140; i += 0xa0) {
        CellEntry* e = (CellEntry*)((char*)g + 4 + i);
        if (!e->used)
            continue;
        if (newIndex < e->value && newIndex != -1)
            e->value--;
        if (idx <= e->value && idx != -1)
            e->value++;
    }
    *(int*)((char*)param_1 + 8) = idx;
}

// ---------------------------------------------------------------- 0x00ec7320
// @ 0x00ec7320
void FUN_00ec7320(int* param_1)
{
    char* p1 = (char*)((FV_1)(*(void***)param_1)[0x10 / 4])(param_1);
    char* g = (char*)*g_16c7584;
    if (*(int*)(g + 0x14c) != 0 && p1 == *(char**)(*(int*)(g + 0x14c) + 4))
        ((FB_i)(*(void***)p1)[0x5c / 4])(p1, -1);
    char* p2 = (char*)((FV_1)(*(void***)p1)[0x10 / 4])(p1);
    ((FV_v)(*(void***)p2)[0xe8 / 4])(p2);
    (void)p2;
}

// ---------------------------------------------------------------- 0x00ec73c0
// @ 0x00ec73c0
bool FUN_00ec73c0(int param_1)
{
    char* g = (char*)*g_16c7584;
    char* esi = g + 4;
    int i = 0;
    while (!(esi[0] != 0 && *(int*)(esi + 4) == param_1)) {
        ++i;
        esi += 0x20;
        if (i > 9)
            return false;
    }
    (void)param_1;
    if (esi == g + 0x14c)
        return false;
    return true;
}

// ---------------------------------------------------------------- 0x00ec7490
// @ 0x00ec7490
bool FUN_00ec7490(int* param_1, int param_2, char param_3)
{
    if (param_1 == 0)
        return false;
    char* wm = (char*)SP_WindowManager();
    char* r = (char*)((FV_i)(*(void***)wm)[0x48 / 4])(wm, param_2);
    if ((int*)r == param_1)
        return true;
    if (param_3 == 0)
        return false;
    if (((FBb_i)(*(void***)param_1)[0xf8 / 4])(param_1, (int)r))
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x00ec74e0
// @ 0x00ec74e0
bool FUN_00ec74e0(void)
{
    char* iVar1 = *(char**)(*(char**)((char*)g_16c7aa4 + 0x14) + 0x18);
    char* w = (char*)((ILayout*)*g_16c7584)->FindWindowByID(0x73e6ba0, 1);
    if (FUN_00809970() != 0)
        return false;
    if (FUN_008053b0() != 0)
        return false;
    if (w != 0) {
        char* wm = (char*)SP_WindowManager();
        char* r = (char*)((FV_i)(*(void***)wm)[0x48 / 4])(wm, 0);
        if (w == r)
            return false;
        if (((FB_i)(*(void***)w)[0xf8 / 4])(w, (int)r))
            return false;
    }
    char* p = *(char**)(iVar1 + 0x20);
    if (p == 0)
        return true;
    {
        char* wm = (char*)SP_WindowManager();
        char* r = (char*)((FV_i)(*(void***)wm)[0x48 / 4])(wm, 0);
        if (p != r && !((FB_i)(*(void***)p)[0xf8 / 4])(p, (int)r))
            return true;
    }
    return false;
}

// ---------------------------------------------------------------- 0x00ec7580
// @ 0x00ec7580
bool FUN_00ec7580(int* param_1)
{
    if (!FUN_00f25730(param_1))
        return false;
    int  value = 0;
    char* sp = 0;
    void* pm = SP_PropertyManager();
    bool ok = ((bool(__thiscall*)(void*, int, int, void**))(*(void***)pm)[0x2c / 4])(
        pm, *param_1, param_1[2], (void**)&sp);
    if (!ok) {
        if (sp)
            ((void(__thiscall*)(void*))(*(void***)sp)[0x4 / 4])(sp);
        return false;
    }
    if (sp) {
        char* out = 0;
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)sp)[0x24 / 4])(sp, 0x1ea08337u, (void**)&out)
            && *(ushort*)(out + 0x12) == 10) {
            value = *FUN_0041ea00(out);
        }
        ((void(__thiscall*)(void*))(*(void***)sp)[0x4 / 4])(sp);
    }
    return value == 0xf;
}

// ---------------------------------------------------------------- 0x00ec7640
// @ 0x00ec7640
bool FUN_00ec7640(int* param_1)
{
    ListObj* list = (ListObj*)*g_16c757c;
    int mode = list->set->frames[(int)FUN_00efc520()].mode;
    int kind = param_1[0];
    int dec = mode - 1;
    if (kind == 1) {
        if (mode != 1 && dec != 1 && param_1[1] == dec)
            return false;
    } else if (kind == 2) {
        StageSet* stage = (StageSet*)FUN_00f3e8a0(*(void**)((char*)g_16c7aa4 + 0x74), 0, param_1[1]);
        if (list->set == stage)
            return false;
        if (!FUN_00f25680(stage) && !FUN_00f25670(stage) && !FUN_00f25720(stage) && !FUN_00ec7580((int*)stage))
            return false;
    } else if (kind == 8 && dec == 1) {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------- 0x00ec76e0
// @ 0x00ec76e0
void FUN_00ec76e0(void** out)
{
    int count = (int)((char*)g_16c75a0 - (char*)g_16c759c) >> 2;
    void* obj;
    void* holder;
    if (count == 0) {
        holder = 0;
        FUN_00805310(&g_16c7590, 0, &holder);
        obj = holder ? ((UIObject*)holder)->Cast(0x4c058cf) : 0;
        *out = obj;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x0 / 4])(obj);
    } else {
        obj = g_16c759c[count - 1];
        *out = obj;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x0 / 4])(obj);
        g_16c75a0--;
        holder = *g_16c75a0;
    }
    if (holder)
        ((void(__thiscall*)(void*))(*(void***)holder)[0x4 / 4])(holder);
}

// ---------------------------------------------------------------- 0x00ec7770
// @ 0x00ec7770
void FUN_00ec7770(void* menu, UIObject* win, void* resource, int mode, const wchar_t* text)
{
    void* item = 0;
    FUN_00ec76e0(&item);
    FUN_0081b650(menu, 0, (int)item, 1);
    UIObject* inner = (UIObject*)((char*)item + 4);
    UIObject* p1002 = (UIObject*)inner->FindChild(0xcdfb1002u, 0);
    UIObject* p1004 = (UIObject*)inner->FindChild(0xcdfb1004u, 0);
    UIObject* p1005 = (UIObject*)inner->FindChild(0xcdfb1005u, 0);
    p1002->SetVisible(1, 0);
    p1004->SetVisible(1, 0);
    p1005->SetVisible(1, 0);
    UIObject* chosen;
    if (mode == 0) {
        FUN_00ec6ee0((int*)p1002, (int*)win, 0);
        p1002->SetVisible(1, 1);
        chosen = p1002;
    } else if (mode == 1) {
        FUN_00ec6ee0((int*)p1004, (int*)win, 0);
        p1004->SetVisible(1, 1);
        chosen = p1004;
    } else {
        chosen = 0;
        if (mode == 2) {
            FUN_00806aa0(p1005, resource, 0);
            p1005->SetVisible(1, 1);
            chosen = p1005;
        }
    }
    UIObject* p1003 = (UIObject*)inner->FindChild(0xcdfb1003u, 0);
    p1003->SetText(text);
    FUN_00ec6fc0((int)chosen, 0, (int*)p1003);
    ((void(__thiscall*)(void*))(*(void***)item)[0x4 / 4])(item);
}

// ---------------------------------------------------------------- 0x00ec78e0
// @ 0x00ec78e0
void FUN_00ec78e0(int param_1, int param_2)
{
    char* w = (char*)((ILayout*)*g_16c7584)->FindWindowByID(param_2, 1);
    (void)w;
    (void)param_1;
}

// ---------------------------------------------------------------- 0x00ec7950
// @ 0x00ec7950
void FUN_00ec7950(void* owner)
{
    ListObj* list = (ListObj*)*g_16c757c;
    for (int i = 0; i < (int)((char*)list->end - (char*)list->begin) >> 2; ++i) {
        int id = FUN_00ec6a00(list->begin[i]);
        UIObject* win = (UIObject*)((ILayout*)*g_16c7584)->FindWindowByID(id, 1);
        UIObject* panel = (UIObject*)win->FindChild(0xcdfb1002u, 0);
        UIObject* sub = (UIObject*)win->FindChild(0xcdfb1003u, 0);
        FUN_00ec7770(owner, panel, 0, 0, (const wchar_t*)sub->GetText());
    }
}

// ---------------------------------------------------------------- 0x00ec79f0
// @ 0x00ec79f0
int* FUN_00ec79f0(int param_2, int key)
{
    UIObject* sub = (UIObject*)((char*)param_2 + 4);
    void* it, *endIter;
    ((void(__thiscall*)(void*, void**))(sub->vt[0xcc / 4]))(sub, &it);
    ((void(__thiscall*)(void*, void**))(sub->vt[0xd0 / 4]))(sub, &endIter);
    while (it != endIter) {
        char* candidate = (char*)it + g_1440aec;
        if (candidate) {
            UnlockedCard* p = (UnlockedCard*)((UIObject*)candidate)->Cast(0x4c058cf);
            if (p && p->key == key)
                return (int*)candidate;
        }
        it = *(void**)it;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ec7a80
// @ 0x00ec7a80
void FUN_00ec7a80(void)
{
    void* holder = 0;
    FUN_00805310(&g_16c7590, 0, &holder);
    UnlockedCard* card = holder ? (UnlockedCard*)((UIObject*)holder)->Cast(0x4c058cf) : 0;
    UIObject* inner = (UIObject*)((char*)card + 4);
    float* selfR = inner->GetRect2();
    float  selfL = selfR[0], selfRr = selfR[2];
    UIObject* win = (UIObject*)inner->FindChild(0xcdfb1002u, 1);
    UIObject* sub = (UIObject*)inner->FindChild(0xcdfb1003u, 1);
    float* wr = win->GetRect2();
    float  wl = wr[0], wrr = wr[2];
    float* sr = sub->GetRect2();
    g_16c7580 = (selfRr - selfL) - ((sr[2] - sr[0]) + (wrr - wl));
    if (holder)
        ((void(__thiscall*)(void*))(*(void***)holder)[0x4 / 4])(holder);
}

// ---------------------------------------------------------------- 0x00ec7b90
// @ 0x00ec7b90
void FUN_00ec7b90(void* owner, int* desc)
{
    int kind = desc[0];
    if (kind == 2) {
        StageSet* stage = (StageSet*)FUN_00f3e8a0(*(void**)((char*)g_16c7aa4 + 0x74), 0, desc[1]);
        void*       res = 0, * flag = 0;
        FUN_00f25190(stage, 0, &res, &flag);
        WideString name;
        name.begin = (unsigned short*)0x1667bac;
        name.end   = (unsigned short*)0x1667bac;
        name.cap   = (unsigned short*)0x1667bae;
        FUN_00f28b80(stage, 0, &name);
        int img = 0;
        SPUIHelpers_CreateImageFromResource(&res, &img, 0, 0xffffffffu, 0xffffffffu);
        FUN_00ec7770(owner, 0, (void*)img, 2, (const wchar_t*)name.begin);
        if (img)
            ((void(__thiscall*)(void*))(*(void***)img)[0x4 / 4])((void*)img);
        if (name.cap - name.begin > 1 && name.begin != 0)
            FUN_00f47380(name.begin);
        (void)flag;
        return;
    }
    int sel = (kind == 1 || kind == 3 || kind == 8) ? 1 : 0;
    int id = FUN_00ec6b20(desc, sel);
    FUN_00ec78e0((int)owner, id);
}

// ---------------------------------------------------------------- 0x00ec7ca0
// @ 0x00ec7ca0
void* __fastcall FUN_00ec7ca0(void* dst_, int, void* src_)
{
    VecObj* dst = (VecObj*)dst_;
    VecObj* src = (VecObj*)src_;
    dst->field0 = src->field0;
    int count = (int)((char*)src->end - (char*)src->begin) >> 3;
    FUN_00ac20d0((int*)&dst->begin, 0, count, &src->allocator);
    void* tmp;
    eastl_copy(&tmp, src->begin, src->end, dst->begin, src);
    dst->end = tmp;
    return dst;
}
