// slice s00ef6db0 -- Simulator::cSPScenarioModeSporepediaLargeAssetView (reset / key removal /
// message handling) and UI::cScenarioTutorialsChecklistUI (ctor, dtor, state helpers, tooltip
// toggles, window helpers) plus the EASTL hashtable internals instantiated in the same TU.
//
// Module flags (to confirm): /O2 /MD /Gy /EHsc /TP  (x87 float args, direct E8 CRT/EASTL calls,
// IAT only for sscanf).
#include "types.h"

// ---------------------------------------------------------------------------
// globals / external helpers
// ---------------------------------------------------------------------------
struct Simulator;
extern Simulator* gSimulator;          // 0x016c7aa4
extern void*      gAppPreferences;     // 0x015fd91c
extern char       g_16c7b80[];         // 0x016c7b80
extern uint32_t   g_16c7b84;           // 0x016c7b84
extern char       g_16c7b60[];         // 0x016c7b60
extern int        g_15acef0;           // 0x015acef0

extern "C" int   sscanf(const char*, const char*, ...);
extern "C" void* memcpy(void*, const void*, unsigned);
extern "C" void  free(void*);

// ---------------------------------------------------------------------------
// virtual-call helpers
// ---------------------------------------------------------------------------
typedef int   (__thiscall *FN0_i)(void*);
typedef void  (__thiscall *FN0_v)(void*);
typedef void  (__thiscall *FN1_i)(void*, int);
typedef void  (__thiscall *FN2_ii)(void*, int, int);
typedef void* (__thiscall *FN1_p)(void*, void*);
typedef void* (__thiscall *FN0_p)(void*);
typedef void  (__thiscall *FN1_v)(void*, int);
typedef int   (__thiscall *FN1_pi)(void*, int);
typedef void  (__thiscall *FN2_ip)(void*, int, void*);
typedef int   (__thiscall *FN2_ipr)(void*, int, void*);
typedef void* (__thiscall *FN2_pi)(void*, void*, int);

struct IRefCounted {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct CSPUILayout {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    void Shutdown(int);
    void* FindWindowByID(int, int);
};

struct CPlayerInventory {
    int  FindCategoryIndex();
    void f5cb180(int);
    void f5ca910();
    CPlayerInventory* f5cae30();
    CPlayerInventory* f5cae30(int);
    CPlayerInventory* f5c2e50();
    CPlayerInventory* GetPlayerInventory();
    CPlayerInventory* GetPlayerInventory3(int, int, int);
    CPlayerInventory* GetPlayerInventory2(int, int);
};

struct CSpaceGame {
    CPlayerInventory* GetPlayerInventory();
    CPlayerInventory* GetPlayerInventory3(int, int, int);
    CPlayerInventory* GetPlayerInventory2(int, int);
    void* f_00641770();
};

struct CResource {
    void* GetAllocator();
};

struct Simulator {
    bool f_ef00d0();
};

struct CSpaceSim {
    void* f_ed4b50(int);
};

struct CDirectPropertyList {
    void SetBoolProperty();
};

struct CAllocMgr {
    void* f_00f3be60(void*);
};

struct CAutoRef {
    void* AsPPTypeParam(int);
};

struct CString {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    int   mAllocator;
    CString(unsigned, void*, int);
    ~CString();
    const char* GetText(int, int);
};

struct CMgrResult {
    char pad[0x84];
    int  f84;
    int  f88;
};

// ---------------------------------------------------------------------------
// module-level function declarations (real names from PDB where known)
// ---------------------------------------------------------------------------
void* __cdecl SP_MessageServer();                            // 0x0067dcc0
void* __cdecl SP_ConfigManager();                            // 0x0067dd30
void* __cdecl SP_GameTimeManager();                          // 0x00b3d380
void* __cdecl SP_GetSaveArea(int, int);                      // 0x006b1f90
void  __cdecl SP_SaveResource(void*, void*);                 // 0x006b1d50
void* __cdecl FUN_00641770();                                // 0x00641770
void* __cdecl FUN_0067cb30();                                // 0x0067cb30
void* __cdecl FUN_0067caf0();                                // 0x0067caf0
void* __cdecl FUN_0067aaf0();                                // 0x0067aaf0
void* __cdecl FUN_00ef00d0();                                // 0x00ef00d0
void* __cdecl FUN_00ed4b50(int);                             // 0x00ed4b50
void  __cdecl FUN_00ef5e90(void*, void*);                    // 0x00ef5e90
void* __cdecl FUN_005810a0();                                // 0x005810a0
void* __cdecl FUN_005ca910();                                // 0x005ca910
void* __cdecl FUN_00f3be60(void*);                           // 0x00f3be60
void* __cdecl FUN_00efc520();                                // 0x00efc520
void* __cdecl FUN_00f3e8a0(void*, void*);                    // 0x00f3e8a0
void* __cdecl FUN_00ef7b90(uint32_t);                        // 0x00ef7b90
void* __cdecl FUN_004eb930(void*, int);                      // 0x004eb930
void* __cdecl FUN_00ef6f00(void*, void*);                    // 0x00ef6f00
void* __cdecl FUN_00ef4bd0();                                // 0x00ef4bd0
void  __cdecl FUN_00efa0b0(void*, int, int);                 // 0x00efa0b0
void  __cdecl RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
void* __cdecl FUN_00555a20(void*, void*, void*, uint8_t);    // 0x00555a20
char* __cdecl Property_GetBool();                            // 0x0041e920
void* __cdecl FUN_00612f50(int, int, void*, int);            // 0x00612f50

void  __cdecl SetTooltipText(void*);                         // 0x00806de0
void  __cdecl AnchorWindowToWindow(void*, void*, int, int);  // 0x00807340
void  __cdecl UI_CalloutMessageBox(int, void*);              // 0x00809db0
void  __cdecl EA_Variant_SetBool(void*, void*);              // 0x00422e20
void  __cdecl EA_Variant_Destruct(void*, int);               // 0x0093db80

// vtable address placeholders (relocations are masked during comparison)
extern void* gVtbl_A;   // 0x0148b59c
extern void* gVtbl_B;   // 0x0148b58c
extern void* gVtbl_C;   // 0x013eb938
extern void* gVtbl_D;   // 0x013ec458
extern void* gVtbl_E;   // 0x0148b584

// ===========================================================================
// Simulator::cSPScenarioModeSporepediaLargeAssetView
// ===========================================================================
struct CAssetView {
    void Reset();
    bool RemoveKey(void* key);
    bool HandleMessage(uint32_t msg, void* arg1);
    void sub_ef75b0(int category, int a, int b);
    void sub_ef7600(int category, int a, int b);
    void sub_ef7640(int category, char flag);
    void sub_ef76a0(int category, char flag);
    void sub_efa0b0(int, int);
    void sub_ef4bd0();
    void clear();
};

struct CVec {
    void* begin;        // +0x00
    void* end;          // +0x04
    void f_ef6f00(void*, void*);
    void clear();
    bool RemoveKey(void*);
};

// @ 0x00ef6db0
void CAssetView::Reset()
{
    char* self = (char*)this;
    *(uint8_t*)(self + 0x9d) = 0;
    void* p = *(void**)(self + 0x78);
    if (p != 0) {
        *(void**)(self + 0x78) = 0;
        ((IRefCounted*)*(void**)((char*)p + 0x10))->v1();
    }
    p = *(void**)(self + 0x7c);
    if (p != 0) {
        *(void**)(self + 0x7c) = 0;
        ((IRefCounted*)p)->v1();
    }
    *(int*)(self + 0x94) = -1;
    *(int*)(self + 0x98) = -1;
    p = *(void**)(self + 0x80);
    if (p != 0) {
        *(void**)(self + 0x80) = 0;
        ((IRefCounted*)p)->v1();
    }
    void* h = *(void**)(self + 0xcc);
    if (h != 0) {
        void* a0 = *(void**)(self + 0xd0);
        void* a1 = *(void**)(self + 0xd4);
        void* a2 = *(void**)(self + 0xd8);
        void* a3 = *(void**)(self + 0xdc);
        *(void**)(self + 0xcc) = 0;
        RemoveHandler(h, a0, a1, a2, a3);
    }
    *(uint8_t*)(self + 0x9e) = 0;
    *(uint8_t*)(self + 0x9f) = 0;
    void* begin = *(void**)(self + 0xa0);
    void* end   = *(void**)(self + 0xa4);
    memcpy(begin, end, 0);
    int n = (int)((char*)end - (char*)begin) >> 2;
    *(void**)(self + 0xa4) = (char*)end + (-n) * 4;
    CSPUILayout* L = *(CSPUILayout**)(self + 0xc);
    if (L != 0) {
        L->Shutdown(1);
        L = *(CSPUILayout**)(self + 0xc);
        if (L != 0) {
            *(void**)(self + 0xc) = 0;
            L->v2();
        }
    }
}

// @ 0x00ef6ea0
bool CAssetView::RemoveKey(void* key)
{
    char* self = (char*)this;
    uint32_t* begin = *(uint32_t**)(self + 0);
    uint32_t* end   = *(uint32_t**)(self + 4);
    uint32_t* pos = (uint32_t*)FUN_00555a20(begin, end, key, *(uint8_t*)(self + 0x28));
    if (pos == end || *(uint32_t*)key < *pos)
        pos = end;
    if (pos != end) {
        uint32_t* src = pos + 1;
        if (src < end)
            memcpy(pos, src, (int)end - (int)src);
        *(int*)(self + 4) -= 4;
        return true;
    }
    return false;
}

// @ 0x00ef6f20
bool CAssetView::HandleMessage(uint32_t msg, void* arg1)
{
    char* self = (char*)this;
    CAssetView* owner = (CAssetView*)(self - 4);
    CVec* vec = (CVec*)(self + 0xc0);
    if (msg == 0x1dd7bda9) {
        char* a = (char*)arg1;
        bool flag = (*(int*)a != 1);
        void* o = *(void**)(a + 4);
        if (o == 0)
            return false;
        int id = ((FN0_i)((*(void***)o)[4]))(o);
        if (id == 0x226182d1) {
            o = *(void**)(a + 4);
            if (o == 0)
                return false;
            if (*(int*)((char*)o + 0xf0) != *(int*)(self + 0xb4) ||
                *(int*)((char*)o + 0xf4) != *(int*)(self + 0xb8))
                return false;
            if (flag) {
                *(uint8_t*)(self + 0xbf) = 0;
                vec->clear();
                return false;
            }
            vec->f_ef6f00(*(void**)((char*)o + 0xf8), *(void**)((char*)o + 0xfc));
            return false;
        }
        if (id == 0x326ffe34) {
            o = *(void**)(a + 4);
            if (o == 0)
                return false;
            void* layoutObj = *(void**)(self + 0x98);
            int r = ((FN0_i)((*(void***)layoutObj)[0x10]))(layoutObj);
            if ((char)FUN_004eb930((char*)o + 0x14, r) != 0) {
                if (flag) {
                    *(uint8_t*)(self + 0xbf) = 0;
                    vec->clear();
                    return false;
                }
                vec->RemoveKey((char*)o + 0x10);
                if (*(int*)(self + 0xc0) == *(int*)(self + 0xc4)) {
                    *(uint8_t*)(self + 0xbf) = 0;
                    owner->sub_ef4bd0();
                    return false;
                }
            }
            return false;
        }
        if (id == 0x3053c62 && *(int*)((char*)o + 0xc) == 1) {
            int64_t v = -1;
            if (sscanf(*(const char**)((char*)o + 0x1c), "tag:spore.com,2006:user/%I64u", &v) == 1 &&
                *(void**)(self + 0x98) != 0) {
                void* layoutObj = *(void**)(self + 0x98);
                int64_t cur = ((int64_t(__thiscall*)(void*))(*(void***)layoutObj)[0x15])(layoutObj);
                if (cur == v) {
                    if (*(void**)(self + 0x4c) != 0)
                        ((FN2_ii)((*(void***)*(void**)(self + 0x4c))[0x1f]))(*(void**)(self + 0x4c), 1, 0);
                    if (flag) {
                        if (*(void**)(self + 0x48) != 0)
                            ((FN2_ii)((*(void***)*(void**)(self + 0x48))[0x1f]))(*(void**)(self + 0x48), 1, 1);
                        UI_CalloutMessageBox(0, (void*)0x015acee4);
                    } else {
                        if (*(void**)(self + 0x50) != 0)
                            ((FN2_ii)((*(void***)*(void**)(self + 0x50))[0x1f]))(*(void**)(self + 0x50), 1, 1);
                        void* ms = SP_MessageServer();
                        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x53dd093, 0);
                    }
                }
            }
            return false;
        }
        return false;
    }
    if (msg == 0x7a43c598) {
        int v[3];
        v[0] = ((int*)arg1)[0];
        v[1] = ((int*)arg1)[1];
        v[2] = ((int*)arg1)[2];
        void* ms = SP_MessageServer();
        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x14ac4938, 0);
        ms = SP_MessageServer();
        ((FN2_ip)((*(void***)ms)[5]))(ms, 0xcadf3aca, (void*)v);
        return false;
    }
    if (msg == 0x9818ab6c && arg1 != 0) {
        char* a = (char*)arg1;
        if (*(int*)(self + 0xb4) == *(int*)(a + 8) && *(int*)(self + 0xb8) == *(int*)(a + 0xc)) {
            void* x = FUN_0067cb30();
            void* obj = *(void**)((char*)x + 0x5c);
            CAutoRef tmp;
            if (*(char*)a == 0) {
                void* p = tmp.AsPPTypeParam(0);
                if ((char)FUN_00612f50(*(int*)(self + 0xb4), *(int*)(self + 0xb8), p, 0) != 0) {
                    FUN_005810a0();
                    FUN_00ef5e90(owner, 0);
                }
            } else {
                void* p = tmp.AsPPTypeParam(0);
                FUN_00612f50(*(int*)(self + 0xb4), *(int*)(self + 0xb8), p, 0);
                (void)obj;
            }
            *(uint8_t*)(self + 0xbe) = 0;
        }
        return false;
    }
    return false;
}

// @ 0x00ef7280
int __cdecl FUN_00ef7280()
{
    void* cm = SP_ConfigManager();
    return ((FN1_pi)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0;
}

// @ 0x00ef72a0
bool __fastcall FUN_00ef72a0(char* p)
{
    if (*(int*)(p + 0x30) != -1)
        return true;
    return false;
}

// @ 0x00ef72b0
void __fastcall FUN_00ef72b0(char* p)
{
    if (*(char*)(p + 0x3d) != 0) {
        *(char*)(p + 0x3e) = 1;
        *(char*)(p + 0x3d) = 0;
    }
}

// @ 0x00ef72c0
void __fastcall FUN_00ef72c0(char* p)
{
    if (*(int*)(p + 0x30) != -1)
        *(char*)(p + 0x3f) = 1;
}

// @ 0x00ef72d0
int __stdcall FUN_00ef72d0(int k)
{
    if (k == 0x2a || k == 0x38 || k == 7 || k == 0xa2 || k == 0x8d || k == 0x24 ||
        k == 0xb || k == 0x74 || k == 0x27 || k == 0x3c || k == 0x17 || k == 0x3a)
        return 0;
    return 1;
}

// @ 0x00ef7330
int __stdcall FUN_00ef7330(int k)
{
    if (k == 7 || k == 0x8d || k == 0xa2 || k == 0x38)
        return 2;
    if (k == 0x24)
        return 1;
    if (k == 0xb || k == 0x74 || k == 0x27)
        return 0x1e;
    if (k == 0x3c)
        return 2;
    if (k == 0x17)
        return 1;
    return ((k != 0x3a) - 1) & 2;
}

// @ 0x00ef73c0
void __cdecl FUN_00ef73c0()
{
    if ((g_16c7b84 & 1) == 0) {
        g_16c7b84 |= 1;
        *(void**)g_16c7b80 = &gVtbl_E;
    }
    Simulator* sim = gSimulator;
    int mode = *(int*)((char*)sim + 0xd0);
    bool bIsSingle = (mode == 1 || mode == 2);
    bool bConfig = false;
    {
        void* cm = SP_ConfigManager();
        bConfig = ((FN1_pi)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) != 0;
    }
    char bKey = 0;
    void* prefs = gAppPreferences;
    if (prefs != 0) {
        if ((char)((FN2_ipr)((*(void***)prefs)[9]))(prefs, 0x7be69ad, 0) != 0) {
            char* b = (char*)Property_GetBool();
            bKey = *b;
        }
    }
    if (bIsSingle && bConfig && bKey == 0) {
        void* gt = SP_GameTimeManager();
        ((FN1_i)((*(void***)gt)[0x10]))(gt, 0x4bf38a7);
        FUN_0067caf0();
        FUN_0067aaf0();
        FUN_0067caf0();
        FUN_0067aaf0();
        FUN_0067caf0();
        FUN_0067aaf0();
        FUN_0067caf0();
        FUN_0067aaf0();
    }
}

// @ 0x00ef75b0
void CAssetView::sub_ef75b0(int category, int a, int b)
{
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* pinv = inv->GetPlayerInventory();
        if (pinv->FindCategoryIndex() == category) {
            sub_efa0b0(a, 0);
            sub_efa0b0(b, 0);
        }
    }
}

// @ 0x00ef7600
void CAssetView::sub_ef7600(int category, int a, int b)
{
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    char* o = (char*)sg->f_00641770();
    if (o != 0 && *(int*)(o + 0x28) == category) {
        sub_efa0b0(a, 0);
        sub_efa0b0(b, 0);
    }
}

// @ 0x00ef7640
void CAssetView::sub_ef7640(int category, char flag)
{
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* pinv = inv->GetPlayerInventory();
        if (pinv->FindCategoryIndex() == category) {
            pinv = inv->GetPlayerInventory();
            if (pinv != 0) {
                pinv->f5cb180(1);
                char* x = (char*)FUN_0067caf0();
                if (*(char*)(x + 0x1a1) != 0 && flag == 0)
                    pinv->f5ca910();
            }
        }
    }
}

// @ 0x00ef76a0
void CAssetView::sub_ef76a0(int category, char flag)
{
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    char* o = (char*)sg->f_00641770();
    if (o != 0 && *(int*)(o + 0x28) == category) {
        CPlayerInventory* x = *(CPlayerInventory**)(o + 0x20);
        if (x != 0) {
            x->f5cb180(1);
            char* y = (char*)FUN_0067caf0();
            if (*(char*)(y + 0x1a1) != 0 && flag == 0)
                x->f5ca910();
        }
    }
}

// @ 0x00ef76f0
bool __cdecl FUN_00ef76f0()
{
    Simulator* sim = gSimulator;
    char* s = (char*)sim;
    char r = (char)sim->f_ef00d0();
    if (r == 0) {
        int mode = *(int*)(s + 0xcc);
        if (mode == 1) {
            char* o = *(char**)(s + 0x14);
            if (o == 0 || *(char*)(o + 0x94) == 0)
                return false;
        } else if (mode == 2) {
            char* o = *(char**)(s + 0x6c);
            if (o == 0 || *(char*)(o + 0x59) == 0)
                return false;
        } else {
            return false;
        }
        return true;
    }
    return false;
}

// @ 0x00ef7740
int __cdecl FUN_00ef7740()
{
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* a = inv->GetPlayerInventory3(0, 0, 0);
        CPlayerInventory* b = a->f5cae30();
        CPlayerInventory* c = b->f5c2e50();
        return (int)c->f5cae30();
    }
    return 0;
}

// @ 0x00ef7780
int __fastcall FUN_00ef7780(char* p)
{
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        int k = *(int*)(p + 0x44);
        if (k == -1)
            k = 5;
        CPlayerInventory* a = inv->GetPlayerInventory3(0, 0, k);
        CPlayerInventory* b = a->f5cae30();
        CPlayerInventory* c = b->f5c2e50();
        return (int)c->f5cae30();
    }
    return 0;
}

// @ 0x00ef77d0
int __cdecl FUN_00ef77d0()
{
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* a = inv->GetPlayerInventory3(1, 0, 0);
        CPlayerInventory* b = a->f5cae30();
        CPlayerInventory* c = b->f5c2e50();
        return (int)c->f5cae30();
    }
    return 0;
}

// @ 0x00ef7810
void __fastcall FUN_00ef7810(char* p, char param)
{
    *(int*)(p + 0x44) = -1;
    Simulator* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv == 0)
        return;
    CPlayerInventory* a = inv->GetPlayerInventory2(0, 0);
    CPlayerInventory* b = a->f5cae30();
    char* list = (char*)b->f5c2e50();
    int count = (*(int*)(list + 0x38) - *(int*)(list + 0x34)) >> 2;
    int i = (param != 0);
    while (i < count) {
        CPlayerInventory* x = b->f5cae30(i);
        int id;
        if (x == 0)
            id = 0;
        else
            id = ((FN1_pi)((*(void***)((char*)x + 0xc))[3]))((char*)x + 0xc, 0x722de63);
        void* alloc = ((CResource*)id)->GetAllocator();
        void* mgr = *(void**)((char*)gSimulator + 0x74);
        void* r = FUN_00f3e8a0(mgr, alloc);
        if (r != 0) {
            *(int*)(p + 0x44) = i;
            return;
        }
        i++;
    }
}

// @ 0x00ef78c0
int __cdecl FUN_00ef78c0()
{
    char* sim = (char*)gSimulator;
    CAllocMgr* mgr = *(CAllocMgr**)(sim + 0x74);
    void* a = FUN_00efc520();
    CMgrResult* r = (CMgrResult*)mgr->f_00f3be60(a);
    int* q = (int*)((char*)r + 0x84);
    return (q[1] - q[0]) / 0x188;
}

// ===========================================================================
// UI::cScenarioTutorialsChecklistUI
// ===========================================================================
struct CScenarioTutorialsChecklistUI {
    void sub_ef79d0();
    void sub_ef7a00();
    void sub_ef7a80();
    void sub_ef7b00();
    void sub_ef7b40();
};

// @ 0x00ef7900
void __fastcall FUN_00ef7900(char* p)
{
    int z = 0;
    *(void**)(p + 4) = &gVtbl_D;
    *(int*)(p + 8) = z;
    *(void**)p = &gVtbl_A;
    *(void**)(p + 4) = &gVtbl_B;
    *(int*)(p + 0xc) = z;
    *(int*)(p + 0x10) = z;
    *(int*)(p + 0x14) = z;
    *(int*)(p + 0x18) = z;
    *(int*)(p + 0x1c) = z;
    *(int*)(p + 0x20) = z;
    *(uint8_t*)(p + 0x24) = (uint8_t)z;
    int m = -1;
    *(uint8_t*)(p + 0x25) = 1;
    *(int*)(p + 0x28) = m;
    *(int*)(p + 0x34) = m;
}

// @ 0x00ef7950
void __fastcall FUN_00ef7950(char* p)
{
    *(void**)p = &gVtbl_A;
    *(void**)(p + 4) = &gVtbl_B;
    if (*(void**)(p + 0x20) != 0)
        ((IRefCounted*)*(void**)(p + 0x20))->v1();
    if (*(void**)(p + 0x1c) != 0)
        ((IRefCounted*)*(void**)(p + 0x1c))->v1();
    if (*(void**)(p + 0x18) != 0)
        ((IRefCounted*)*(void**)(p + 0x18))->v1();
    if (*(void**)(p + 0x14) != 0)
        ((IRefCounted*)*(void**)(p + 0x14))->v1();
    if (*(void**)(p + 0x10) != 0)
        ((IRefCounted*)*(void**)(p + 0x10))->v2();
    if (*(void**)(p + 0xc) != 0)
        ((IRefCounted*)*(void**)(p + 0xc))->v1();
    *(void**)p = &gVtbl_C;
    *(void**)(p + 4) = &gVtbl_D;
}

// @ 0x00ef79d0
void CScenarioTutorialsChecklistUI::sub_ef79d0()
{
    char* p = (char*)this;
    CSPUILayout* L = *(CSPUILayout**)(p + 0x10);
    if (L != 0) {
        L->Shutdown(1);
        L = *(CSPUILayout**)(p + 0x10);
        if (L != 0) {
            *(void**)(p + 0x10) = 0;
            L->v2();
        }
    }
}

// @ 0x00ef7a00
void CScenarioTutorialsChecklistUI::sub_ef7a00()
{
    char* p = (char*)this;
    if (*(char*)(p + 0x25) == 0) {
        void* tray = *(void**)(p + 0x20);
        ((FN2_ii)((*(void***)tray)[10]))(tray, 4, 1);
        CString s(0xf3108302, (void*)0x07a248a0, 0);
        tray = *(void**)(p + 0x20);
        const char* t = s.GetText(-1, 1);
        void* r = ((FN1_p)((*(void***)tray)[4]))(tray, (void*)t);
        SetTooltipText(r);
        AnchorWindowToWindow(*(void**)(p + 0xc), *(void**)(p + 0x14), 0x11, 0);
        *(char*)(p + 0x25) = 1;
        s.~CString();
    }
}

// @ 0x00ef7a80
void CScenarioTutorialsChecklistUI::sub_ef7a80()
{
    char* p = (char*)this;
    if (*(char*)(p + 0x25) != 0) {
        void* tray = *(void**)(p + 0x20);
        ((FN2_ii)((*(void***)tray)[10]))(tray, 1, 1);
        CString s(0xf3108302, (void*)0x07a24898, 0);
        tray = *(void**)(p + 0x20);
        const char* t = s.GetText(-1, 1);
        void* r = ((FN1_p)((*(void***)tray)[4]))(tray, (void*)t);
        SetTooltipText(r);
        AnchorWindowToWindow(*(void**)(p + 0xc), *(void**)(p + 0x14), 0x18, 0);
        *(char*)(p + 0x25) = 0;
        s.~CString();
    }
}

// @ 0x00ef7b00
void CScenarioTutorialsChecklistUI::sub_ef7b00()
{
    char* p = (char*)this;
    void* w = *(void**)(p + 0x14);
    void* r = ((FN2_pi)((*(void***)w)[0x3c]))(w, (void*)0x07a27050, 1);
    if (r != 0)
        ((FN2_ii)((*(void***)r)[0x1f]))(r, 2, 1);
    w = *(void**)(p + 0x1c);
    ((FN2_ii)((*(void***)w)[0x1f]))(w, 1, 1);
}

// @ 0x00ef7b40
void CScenarioTutorialsChecklistUI::sub_ef7b40()
{
    char* p = (char*)this;
    int id = *(int*)(p + 0x34);
    if (id == -1)
        return;
    CSPUILayout* L = *(CSPUILayout**)(p + 0x10);
    void* w = L->FindWindowByID(id + 1000, 1);
    w = ((FN0_p)((*(void***)w)[4]))(w);
    ((FN2_ii)((*(void***)w)[0x1f]))(w, 2, 0);
    ((CDirectPropertyList*)g_16c7b60)->SetBoolProperty();
    g_15acef0 = -1;
    *(int*)(p + 0x34) = -1;
}

// ===========================================================================
// EASTL hashtable internals instantiated in this TU
// ===========================================================================
struct CHash {
    void DoRehash(uint32_t n);
};

// @ 0x00ef7c00
void CHash::DoRehash(uint32_t n)
{
    char* self = (char*)this;
    void* buckets = FUN_00ef7b90(n);
    uint32_t i = 0;
    while (i < *(uint32_t*)(self + 8)) {
        void** p = (void**)(*(char**)(self + 4) + i * 4);
        while (*p != 0) {
            void* node = *p;
            uint32_t h = *(uint32_t*)node;
            *p = *(void**)((char*)node + 4);
            uint32_t idx = h % n;
            *(void**)((char*)node + 4) = *(void**)((char*)buckets + idx * 4);
            *(void**)((char*)buckets + idx * 4) = node;
            p = (void**)(*(char**)(self + 4) + i * 4);
        }
        i++;
    }
    void* old = *(void**)(self + 4);
    if (*(uint32_t*)(self + 8) > 1 && old != *(void**)(self + 0x30)) {
        if (old >= *(void**)(self + 0x24) && old < *(void**)(self + 0x28)) {
            *(void**)old = *(void**)(self + 0x1c);
            *(void**)(self + 0x1c) = old;
            *(void**)(self + 4) = buckets;
            *(uint32_t*)(self + 8) = n;
            return;
        }
        free(old);
    }
    *(void**)(self + 4) = buckets;
    *(uint32_t*)(self + 8) = n;
}

// @ 0x00ef7ca0
int __cdecl FUN_00ef7ca0(int a0, int* a1, int a2)
{
    int n = 0;
    while (a0 != a2) {
        a0 = *(int*)(a0 + 4);
        while (a0 == 0) {
            a1++;
            a0 = *a1;
        }
        n++;
    }
    return n;
}

// @ 0x00ef7ce0
void __fastcall FUN_00ef7ce0(char* p)
{
    if (*(int*)(p + 4) == -1)
        return;
    Simulator* sim = gSimulator;
    CSpaceSim* sg = *(CSpaceSim**)((char*)sim + 0x14);
    void* r = sg->f_ed4b50(*(int*)(p + 4));
    ((CScenarioTutorialsChecklistUI*)r)->sub_ef7a00();
}

// @ 0x00ef7d00
void __cdecl FUN_00ef7d00()
{
    void* prefs = gAppPreferences;
    char flag = 1;
    int64_t v;
    v = 2;
    EA_Variant_SetBool(&v, &flag);
    ((FN2_ip)((*(void***)prefs)[5]))(prefs, 0x7be69ad, &v);
    void* area = SP_GetSaveArea(0x11ac192, 0);
    SP_SaveResource(prefs, area);
    void* gt = SP_GameTimeManager();
    ((FN1_i)((*(void***)gt)[0x10]))(gt, 0x4bf38a7);
    if (((uint8_t*)&v)[8] & 4)
        EA_Variant_Destruct(&v, 0);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
