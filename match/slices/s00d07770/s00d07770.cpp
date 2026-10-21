// Slice s00d07770 — frozen batch gold4 (slice 103)
#include <intrin.h>
// SPUI / editor-economy class family: layout setup, city/tribe economy accessors.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// All `__thiscall` entry points are modelled as struct members (MSVC C3865).
// The struct names are arbitrary; only the generated code is compared.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ------------------------------------------------------------------ external data
extern void* g_vtbl_14790d0;      // 0x014790d0
extern void* g_vtbl_14790fc;      // 0x014790fc

// ------------------------------------------------------------------ callees
// Free (cdecl / stdcall) helpers.
int   __cdecl FUN_009399c0(void*, void*, ...);     // 0x009399c0  Sprintf16 (cdecl varargs)
void  __cdecl FUN_00f47380(void*);                 // 0x00f47380  operator delete
void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int); // 0x00f473a0
u32   __cdecl FUN_00458a40(void*);                 // 0x00458a40
void* __cdecl FUN_008014a0();                      // 0x008014a0
void* __cdecl FUN_0067cab0(u32);                   // 0x0067cab0
int   __cdecl FUN_00d09740(void*);                 // 0x00d09740
void* __cdecl FUN_0067de30();                      // 0x0067de30  SP::PropertyManager

// thiscall helpers, modelled as struct members so MSVC emits ecx-based calls.
struct Ext {
    void* NounMgr(void*);                          // 0x00b3d300
    void* NounLookup(void*);                       // 0x00b25f40
    void* DictGet(int, int, int);                  // 0x00bf0c60
    void* FindWindowByID(unsigned id, int b);      // 0x008105b0
    void* DialogCtor();                            // 0x00810000
    int   LayoutInit(const void*, int, unsigned);  // 0x008120d0
    int   SetParentWin(void*, int, unsigned);      // 0x008121b0
    void* FUN_b6f0c0(int);                         // 0x00b6f0c0
    void* Singleton();                             // 0x00b3d240
    u8    FindLocal(u32);                          // 0x00801bb0
    void* FindLocalV(unsigned);                    // vtable +0xc lookup

    void* Civ();                                   // 0x00bd9bf0
    int   V_bd9bb0();                              // 0x00bd9bb0
    int   V_bd9b70();                              // 0x00bd9b70
    int   V_bd8a00();                              // 0x00bd8a00
    int   V_bd8b10();                              // 0x00bd8b10
    int   V_bd8110();                              // 0x00bd8110
    int   V_bd89c0();                              // 0x00bd89c0
    int   V_bd8aa0();                              // 0x00bd8aa0
    int   VehicleSpecialty();                      // 0x00bd81d0
    int   V_bf1fd0(int);                           // 0x00bf1fd0
    int   V_bf0c50();                              // 0x00bf0c50
    int   V_113ab90();                             // 0x0113ab90
    int   AddCivicRadius(float, int);              // 0x00befd80
    int   SpendMoney(float);                       // 0x00bef710
    void  SendChanged();                           // 0x005a7840
    int   V_c8e6f0();                              // 0x00c8e6f0
    void  V_c8f660(int);                           // 0x00c8f660
    u8    V_c31a00(int);                           // 0x00c31a00
    int   V_c30cb0();                              // 0x00c30cb0
    int   V_bdb930(int);                           // 0x00bdb930
    u8    V_cd6e40(int);                           // 0x00cd6e40
    u8    V_cd6ef0(int);                           // 0x00cd6ef0
    void* ToolOfType(int);                         // 0x00c8f6e0
    int   GetFileCount();                          // 0x008e7f80

    u8    GetPropertyAsKeyInstance(int, void*);    // 0x006a12a0
    u8    TryGetUIntProperty(int, void*);          // 0x00410370
    u8    GetPropertyAsText(int, void*);           // 0x006a1360
    u8    StrLoad(int, int, int);                  // 0x006b54b0
    int*  PropGetInt();                            // 0x0041e990
    u32*  PropGetUInt();                           // 0x0041ea00
};

void* __cdecl FUN_00cd40b0(int);                   // 0x00cd40b0  cTribeModeStrategy::Instance
void* __cdecl FUN_00b6f0c0(int);                   // 0x00b6f0c0
void* __cdecl FUN_00b3d240();                      // 0x00b3d240

// ============================================================================
// thiscall entry points, modelled as members.
// ============================================================================

struct C103 {
    void  FillCounts();                    // 0x00d07770
    void* Destroy(u8 flags);               // 0x00d07890
    u8    CreateLayout(void* param);       // 0x00d078d0
    void* Init(void* param);               // 0x00d07a40
    u8    PickEventId();                   // 0x00d07ab0
    int   GetValue(int which);             // 0x00d07bb0
    void  SetValue(int which, int amount); // 0x00d07ca0
    int   GetFlag(int which);              // 0x00d07d00
    void  SetFlag(int which, int v);       // 0x00d07d20
    u8    CanAffordScalar(int desc, int amount); // 0x00d07d50
    int   GetTribeValue(int which);        // 0x00d07d70
    void  SetTribeValue(int which, int v); // 0x00d07e10
    int   CanAffordEmpire(int* desc);      // 0x00d07e40
    u8    TribeHasTool(int* desc);         // 0x00d081f0
    int   CanAffordTribe(int* desc);       // 0x00d082a0
};

struct C103M { u8 DoProbe(int which, int v); };

// ================================================================ 0x00d07770
// Fill the three numeric text fields of the dialog by formatting the three
// resource counts named by the object.
// @ 0x00d07770
void C103::FillCounts() {
    char* p = (char*)this;
    u16 buf[32];

    void* noun = ((Ext*)*(void**)(*(int*)(p + 8) + 0x84))->NounMgr(*(void**)(*(int*)(p + 8) + 0x84));
    void* obj = ((Ext*)noun)->NounLookup(noun);
    if (obj == 0) return;

    void* a = ((Ext*)obj)->DictGet(2, -1, 0);
    void* b = ((Ext*)obj)->DictGet(2, -1, 1);
    void* c = ((Ext*)obj)->DictGet(2, -1, 2);

    void* w = ((Ext*)*(void**)(p + 4))->FindWindowByID(0x62770ed, 1);
    if (w != 0) {
        FUN_009399c0(buf, (void*)0x13f01bc, a);
        (*(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x80))(w, buf);
    }
    w = ((Ext*)*(void**)(p + 4))->FindWindowByID(0x62770ee, 1);
    if (w != 0) {
        FUN_009399c0(buf, (void*)0x13f01bc, b);
        (*(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x80))(w, buf);
    }
    w = ((Ext*)*(void**)(p + 4))->FindWindowByID(0x62770ef, 1);
    if (w != 0) {
        FUN_009399c0(buf, (void*)0x13f01bc, c);
        (*(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x80))(w, buf);
    }
}

// ================================================================ 0x00d07890
// Destructor: release the two owned interface pointers and optionally delete.
// @ 0x00d07890
void* C103::Destroy(u8 flags) {
    int* p = (int*)this;
    *(void**)p = &g_vtbl_14790d0;
    _ReadWriteBarrier();
    int* a = (int*)p[2];
    if (a != 0) (*(void(__thiscall**)(int*))((char*)*(int**)a + 4))(a);
    int* b = (int*)p[1];
    if (b != 0) (*(void(__thiscall**)(int*))((char*)*(int**)b + 8))(b);
    if (flags & 1) FUN_00f47380(this);
    return this;
}

// ================================================================ 0x00d078d0
// Create / install the dialog layout and seed its colour swatches.
// @ 0x00d078d0
u8 C103::CreateLayout(void* param) {
    char* p = (char*)this;
    void* mem = FUN_00f473a0(0x18, (const char*)0x13eb430, 0, 0, 0, 0);
    void* dlg = (mem != 0) ? ((Ext*)mem)->DialogCtor() : 0;

    void* old = *(void**)(p + 4);
    if (dlg != old) {
        if (dlg != 0) (*(void(__thiscall**)(void*))((char*)*(void**)dlg + 4))(dlg);
        *(void**)(p + 4) = dlg;
        if (old != 0) (*(void(__thiscall**)(void*))((char*)*(void**)old + 8))(old);
    }

    int key[3];
    key[2] = 0x04046410;
    key[1] = 0x0510a95b;
    key[0] = 0x23ccc8ad;

    u8 ok = ((Ext*)*(void**)(p + 4))->LayoutInit(key, 1, 0x5b598fa);
    if (ok == 0) return 0;

    ((Ext*)*(void**)(p + 4))->SetParentWin(param, 1, 0x5b598fa);

    void* w = ((Ext*)*(void**)(p + 4))->FindWindowByID(0x53439d0, 1);
    if (w != 0) {
        void** vt = *(void***)w;
        float* r = (float*)(*(void*(__thiscall**)(void*))((char*)vt + 0x34))(w);
        (*(void(__thiscall**)(void*, float, float))((char*)vt + 0x64))(w, -(r[2] - r[0]), 0.0f);
    }

    u32 col = FUN_00458a40(FUN_00b6f0c0(0x53dbcf1));

    void* a = ((Ext*)*(void**)(p + 4))->FindWindowByID(0x62770e0, 1);
    if (a != 0) (*(void(__thiscall**)(void*, u32))((char*)*(void**)a + 0x5c))(a, col);
    void* b = ((Ext*)*(void**)(p + 4))->FindWindowByID(0x62770e1, 1);
    if (b != 0) (*(void(__thiscall**)(void*, u32))((char*)*(void**)b + 0x5c))(b, col);
    void* c = ((Ext*)*(void**)(p + 4))->FindWindowByID(0x62770e2, 1);
    if (c != 0) (*(void(__thiscall**)(void*, u32))((char*)*(void**)c + 0x5c))(c, col);
    return 1;
}

// ================================================================ 0x00d07a40
// @ 0x00d07a40
void* C103::Init(void* param) {
    int* p = (int*)this;
    FUN_008014a0();
    p[2] = (int)param;
    *(void**)p = &g_vtbl_14790fc;
    return this;
}

// ================================================================ 0x00d07ab0
// Decide which "economy event" id the editor should report.
// @ 0x00d07ab0
u8 C103::PickEventId() {
    void* q = FUN_00b3d240();
    void* mgr = (*(void*(__thiscall**)(void*))((char*)*(void**)q + 0x34))(q);
    u32 id;
    if (mgr != 0) {
        void* v1 = ((Ext*)mgr)->FindLocalV(0xe89adf71);
        void* v2 = ((Ext*)mgr)->FindLocalV(0xe9cb8ba);
        void* v3 = ((Ext*)mgr)->FindLocalV(0x137e8e0);
        void* v4 = ((Ext*)mgr)->FindLocalV(0x436f315);
        void* v5 = ((Ext*)mgr)->FindLocalV(0x175cdc9);
        void* v6;
        u8 ok;
        if (v1 != 0) {
            ok = (*(u8(__thiscall**)(void*))((char*)*(void**)v1 + 0x10))(v1);
            if (ok == 0) goto fallback;
        }
        if (v2 == 0) {
            if (v3 == 0) {
                if (v4 == 0) {
                    if (v5 == 0) goto fallback;
                    v6 = (char*)v5 + 0x70;
                } else {
                    v6 = (char*)v4 + 0x34;
                }
                ok = (*(u8(__thiscall**)(void*))((char*)*(void**)v6 + 0x58))(v6);
            } else {
                v6 = (char*)v3 + 0x34;
                ok = (*(u8(__thiscall**)(void*))((char*)*(void**)v6 + 0x58))(v6);
                if (ok == 0) goto fallback;
                ok = (u8)FUN_00d09740(v3);
            }
        } else {
            v6 = (char*)v2 + 0x34;
            ok = (*(u8(__thiscall**)(void*))((char*)*(void**)v6 + 0x58))(v6);
            if (ok == 0) goto fallback;
            ok = (u8)FUN_00d09740(v2);
        }
        if (ok != 0) {
            id = 0x648fbf1;
            goto dispatch;
        }
    }
fallback:
    id = 0x1002;
dispatch:
    ((Ext*)FUN_0067cab0(id))->FindLocal(id);
    return 0;
}

// ================================================================ 0x00d07bb0
// Integer value accessor keyed by enum index (city economy).
// @ 0x00d07bb0
int C103::GetValue(int which) {
    char* p = (char*)this;
    switch (which) {
    case 0: {
        void* civ = ((Ext*)*(void**)(p + 8))->Civ();
        return (int)*(float*)((char*)civ + 0x98);
    }
    case 1: {
        int a = ((Ext*)*(void**)(p + 8))->V_bd9bb0();
        int b = ((Ext*)*(void**)(p + 8))->V_bd8a00();
        return b - a;
    }
    case 2: {
        int a = ((Ext*)*(void**)(p + 8))->V_bd9b70();
        int b = ((Ext*)*(void**)(p + 8))->V_bd8b10();
        return b - a;
    }
    case 4: {
        ((Ext*)*(void**)(p + 8))->Civ();
        int spec = ((Ext*)*(void**)(p + 8))->VehicleSpecialty();
        Ext* civ = (Ext*)((Ext*)*(void**)(p + 8))->Civ();
        int a = civ->V_bf1fd0(spec);
        int b = (int)civ->DictGet(spec, -1, 0);
        return a - b;
    }
    case 5: {
        void* civ = ((Ext*)*(void**)(p + 8))->Civ();
        int a = ((Ext*)civ)->V_113ab90();
        int b = ((Ext*)civ)->V_bf0c50();
        return a - b;
    }
    default:
        return 0;
    }
}

// ================================================================ 0x00d07ca0
// @ 0x00d07ca0
void C103::SetValue(int which, int amount) {
    char* p = (char*)this;
    if (which != 0) return;
    if (amount > 0) {
        Ext* civ = (Ext*)((Ext*)*(void**)(p + 8))->Civ();
        civ->AddCivicRadius((float)amount, 0);
        ((Ext*)this)->SendChanged();
        return;
    }
    Ext* civ = (Ext*)((Ext*)*(void**)(p + 8))->Civ();
    civ->SpendMoney((float)(-amount));
    ((Ext*)this)->SendChanged();
}

// ================================================================ 0x00d07d00
// @ 0x00d07d00
int C103::GetFlag(int which) {
    char* p = (char*)this;
    if (which == 0)
        return ((Ext*)*(void**)(p + 8))->V_c8e6f0();
    return 0;
}

// ================================================================ 0x00d07d20
// @ 0x00d07d20
void C103::SetFlag(int which, int v) {
    char* p = (char*)this;
    if (which != 0) return;
    ((Ext*)*(void**)(p + 8))->V_c8f660(v);
    ((Ext*)this)->SendChanged();
}

// ================================================================ 0x00d07d50
// @ 0x00d07d50
u8 C103::CanAffordScalar(int desc, int amount) {
    int r = (*(int(__thiscall**)(void*, int))((char*)*(int**)this + 4))(this, desc);
    return (r >= amount) ? 1 : 0;
}

// ================================================================ 0x00d07d70
// Integer value accessor keyed by enum index (tribe economy).
// @ 0x00d07d70
int C103::GetTribeValue(int which) {
    char* p = (char*)this;
    switch (which) {
    case 0:
        return ((Ext*)*(void**)(p + 8))->V_c30cb0();
    case 7: {
        int t = ((Ext*)*(void**)(p + 0xc))->V_bd9bb0();
        t += ((Ext*)*(void**)(p + 0xc))->V_bd9b70();
        return ((Ext*)*(void**)(p + 0xc))->V_bd8110() - t;
    }
    case 1: {
        int a = ((Ext*)*(void**)(p + 0xc))->V_bd9bb0();
        int b = ((Ext*)*(void**)(p + 0xc))->V_bd89c0();
        return b - a;
    }
    case 2: {
        int a = ((Ext*)*(void**)(p + 0xc))->V_bd9b70();
        int b = ((Ext*)*(void**)(p + 0xc))->V_bd8aa0();
        return b - a;
    }
    default:
        return 0;
    }
}

// ================================================================ 0x00d07e10
// @ 0x00d07e10
void C103::SetTribeValue(int which, int v) {
    char* p = (char*)this;
    if (which != 0) return;
    ((Ext*)*(void**)(p + 8))->V_c31a00(v);
    ((Ext*)this)->SendChanged();
}

// ================================================================ 0x00d07e40
// CanAffordWithReason — empire economy.
// @ 0x00d07e40
int C103::CanAffordEmpire(int* desc) {
    char* p = (char*)this;
    int s = 0;
    Ext* pm = (Ext*)FUN_0067de30();
    if (s != 0) { s = 0; (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s); }
    (*(void(__thiscall**)(void*, int, int, int*))((char*)*(void**)pm + 0x2c))(pm, desc[0], desc[2], &s);

    int kind;
    u8 got = ((Ext*)s)->GetPropertyAsKeyInstance(0x2196ad5, &kind);
    if (got != 0) {
        u32 k = (u32)kind;
        if (k < 0x42bf8c1d) {
            if (k == 0x42bf8c1d) goto ret1;
            if (k == 0x142462a) {
                u8 ok = (*(u8(__thiscall**)(void*, int, int))((char*)*(int**)this + 0xc))(this, 2, 1);
                if (ok != 0) goto dispatch;
                if (desc != 0) {
                    ((Ext*)desc)->StrLoad(0x496bfb26, 0x10a, 0);
                    ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x20a, 0);
                    *(int*)((char*)desc + 0x2c) = 0xb879e6e8;
                    *(int*)((char*)desc + 0x28) = 0xff00ff00;
                }
                if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                return 4;
            }
            if (k != 0xfcafd26 && k == 0x2b885df4) goto ret1;
            goto ret2;
        }
        if (k == 0x4d863c8b) goto dispatch;
        if (k == 0x81c74dbc) {
            if (desc[0] == 0x115fa309) {
                if (desc != 0) {
                    ((Ext*)desc)->StrLoad(0x496bfb26, 0x109, 0);
                    ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x209, 0);
                    *(int*)((char*)desc + 0x2c) = 0xb879e6e8;
                    *(int*)((char*)desc + 0x28) = 0xff00ff00;
                }
                if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                return 4;
            }
            goto ret2;
        }
        if (k != 0x8bfac054) goto ret2;
        {
            int v;
            u8 g = ((Ext*)s)->TryGetUIntProperty(0x64bd903, &v);
            if (g != 0) {
                int spec = ((Ext*)*(void**)(p + 8))->VehicleSpecialty();
                u8 ok = ((Ext*)spec)->V_bdb930(v);
                if (ok == 0) {
                    if (desc != 0) {
                        ((Ext*)desc)->StrLoad(0x496bfb26, 0x10b, 0);
                        ((Ext*)s)->GetPropertyAsText(0x64bdb29, (char*)desc + 0x14);
                        *(int*)((char*)desc + 0x2c) = 0x5c5418f;
                    }
                    if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                    return 7;
                }
                u8 ok4 = (*(u8(__thiscall**)(void*, int, int))((char*)*(int**)this + 0xc))(this, 4, 1);
                if (ok4 == 0) {
                    if (desc != 0) {
                        ((Ext*)desc)->StrLoad(0x496bfb26, 0x104, 0);
                        ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x204, 0);
                        *(int*)((char*)desc + 0x2c) = 0xb879e6e8;
                        *(int*)((char*)desc + 0x28) = 0xff00ff00;
                    }
                    if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                    return 5;
                }
                u8 ok5 = (*(u8(__thiscall**)(void*, int, int))((char*)*(int**)this + 0xc))(this, 5, 1);
                if (ok5 == 0) {
                    if (desc != 0) {
                        ((Ext*)desc)->StrLoad(0x496bfb26, 0x10c, 0);
                        ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x20c, 0);
                        *(int*)((char*)desc + 0x2c) = 0xb879e6e8;
                        *(int*)((char*)desc + 0x28) = 0xff00ff00;
                    }
                    if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                    return 5;
                }
            }
        }
    }

dispatch:
    {
        int u = 0;
        if (s != 0) {
            int prop;
            u8 has = (u8)(*(u8(__thiscall**)(int*, int, int*))((char*)*(int*)s + 0x24))((int*)s, 0x2166464, &prop);
            if (has != 0 && *(u16*)(prop + 0x12) == 9) {
                int* v = ((Ext*)(prop))->PropGetInt();
                u = *v;
            }
        }
        u8 ok = (*(u8(__thiscall**)(void*, int, int))((char*)*(int**)this + 0xc))(this, 0, u);
        if (ok != 0) goto ret1;
        if (desc != 0) {
            ((Ext*)desc)->StrLoad(0x496bfb26, 0x101, 0);
            ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x201, 0);
            *(int*)((char*)desc + 0x2c) = 0;
            *(u8*)((char*)desc + 0x30) = 1;
        }
    }
ret2:
    if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
    return 2;

ret1:
    if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
    return 1;
}

// ================================================================ 0x00d081f0
// @ 0x00d081f0
u8 C103::TribeHasTool(int* desc) {
    int s = 0;
    Ext* pm = (Ext*)FUN_0067de30();
    if (s != 0) { s = 0; (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s); }
    (*(void(__thiscall**)(void*, int, int, int*))((char*)*(void**)pm + 0x2c))(pm, desc[0], desc[2], &s);
    if (s == 0) return 0;
    {
        int prop;
        u8 has = (u8)(*(u8(__thiscall**)(int*, int, int*))((char*)*(int*)s + 0x24))((int*)s, 0x4294750, &prop);
        if (has == 0) { (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s); return 0; }
        if (*(u16*)(prop + 0x12) != 0xa) { (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s); return 0; }
        u32* pv = ((Ext*)prop)->PropGetUInt();
        int tid = *pv;
        if (tid == 0) { (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s); return 0; }
        u8 r = ((Ext*)FUN_00cd40b0(tid))->V_cd6e40(tid);
        (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
        return r;
    }
}

// ================================================================ 0x00d082a0
// CanAffordWithReason — tribe economy.
// @ 0x00d082a0
int C103::CanAffordTribe(int* desc) {
    char* p = (char*)this;
    int s = 0;
    Ext* pm = (Ext*)FUN_0067de30();
    if (s != 0) { s = 0; (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s); }
    (*(void(__thiscall**)(void*, int, int, int*))((char*)*(void**)pm + 0x2c))(pm, desc[0], desc[2], &s);

    int u = 0;
    if (s != 0) {
        int prop;
        u8 has = (u8)(*(u8(__thiscall**)(int*, int, int*))((char*)*(int*)s + 0x24))((int*)s, 0x2166464, &prop);
        if (has != 0 && *(u16*)(prop + 0x12) == 9) {
            int* v = ((Ext*)prop)->PropGetInt();
            u = *v;
        }
    }
    if (s != 0) {
        int prop;
        u8 has = (u8)(*(u8(__thiscall**)(int*, int, int*))((char*)*(int*)s + 0x24))((int*)s, 0x4294750, &prop);
        if (has != 0 && *(u16*)(prop + 0x12) == 0xa) {
            u32* pv = ((Ext*)prop)->PropGetUInt();
            int tid = *pv;
            if (tid != 0) {
                if (((Ext*)FUN_00cd40b0(tid))->V_cd6ef0(tid) == 0) {
                    if (desc != 0) {
                        ((Ext*)desc)->StrLoad(0x496bfb26, 0x107, 0);
                        ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x207, 0);
                        *(int*)((char*)desc + 0x2c) = 0x5c5418f;
                    }
                    (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                    return 7;
                }
                void* tool = ((Ext*)*(void**)(p + 8))->ToolOfType(tid);
                if (tool != 0) {
                    tool = ((Ext*)*(void**)(p + 8))->ToolOfType(tid);
                    if (tool != 0) {
                        tool = ((Ext*)*(void**)(p + 8))->ToolOfType(tid);
                        if (((Ext*)((char*)tool + 0x120))->GetFileCount() != 2) {
                            if (desc != 0) {
                                ((Ext*)desc)->StrLoad(0x496bfb26, 0x105, 0);
                                ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x205, 0);
                                *(int*)((char*)desc + 0x2c) = 0xb879e6e8;
                                *(int*)((char*)desc + 0x28) = 0xff00ff00;
                            }
                            (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                            return 6;
                        }
                    }
                }
                u8 ok = (*(u8(__thiscall**)(void*, int, int))((char*)*(int**)this + 0xc))(this, 0, u);
                if (ok == 0) {
                    if (desc != 0) {
                        ((Ext*)desc)->StrLoad(0x496bfb26, 0x101, 0);
                        ((Ext*)((char*)desc + 0x14))->StrLoad(0x496bfb26, 0x201, 0);
                        *(int*)((char*)desc + 0x2c) = 0;
                        *(u8*)((char*)desc + 0x30) = 1;
                    }
                    (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
                    return 2;
                }
            }
        }
    }
    if (s != 0) (*(void(__thiscall**)(int*))((char*)*(int*)s + 4))((int*)s);
    return 1;
}
