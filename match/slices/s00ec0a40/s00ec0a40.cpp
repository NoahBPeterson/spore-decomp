// Slice s00ec0a40 -- behavior-tree "stimulus" evaluators over SP::cCombatant / cSPCreatureBase.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char u8;
typedef unsigned short ushort;
struct Rec { uint d[8]; };   // 32-byte behavior-tree stimulus record copied to obj+0x688
struct Key2 { uint a, b; };  // 8-byte (2-dword) hash key passed by address

// ---------------------------------------------------------------- globals
void*  g_16c7aa4;                    // 0x016c7aa4  cThingManager/simulator singleton
u8     g_16c74a0;                    // 0x016c74a0  (3 floats used by ctor)
u8     g_16c74a4;
u8     g_16c74a8;
const float g_f1470f1c = 2.0f;       // 0x01470f1c
const float g_f1486110 = 5.0f;       // 0x01486110
const float g_f1488900 = 1.0f;       // 0x01488900
const float g_f13ec4d0 = 100.0f;     // 0x013ec4d0

// ---------------------------------------------------------------- foreign helpers
void*  __cdecl FUN_00d99420(void* a, void* b);   // 0x00d99420
void   __cdecl FUN_00d996e0(void* a, void* b);   // 0x00d996e0
void*  __fastcall FUN_00d997e0(void* o);         // 0x00d997e0  GetAny
// @ 0x00c04590
struct H_00c04590 {
    void* __thiscall Get();
};
// @ 0x00c04750
struct H_00c04750 {
    void* __thiscall Get();
};
// @ 0x00c7d070
struct H_00c7d070 {
    void* __thiscall Beg();
};
// @ 0x00c7d080
struct H_00c7d080 {
    void* __thiscall Beg();
};
// @ 0x00c7d090
u8     __cdecl FUN_00c7d090(void* b, void* a);         // key compare
// @ 0x00c7da70
struct H_00c7da70 {
    u8 __thiscall Has(void* v);
};
// @ 0x00c70110
struct H_00c70110 {
    void __thiscall Assign(void* src);
};
// @ 0x00c0f780
struct H_00c0f780 {
    int __thiscall Count();
};
// @ 0x00c0f8a0
struct H_00c0f8a0 {
    void* __thiscall At(int idx);
};
// 0x00bc96a0  foreign view of the stimulus table used by the evaluators below
struct H_00bc96a0 {
    void* __thiscall Play(int a, int flags);
};
// 0x00bc97f0
void*  __cdecl FUN_00bc97f0(void* o, int a, int b, float f, void* c);
// @ 0x008e7f80
struct H_008e7f80 {
    int __thiscall GetFileCount();
};
void*  __cdecl FUN_00ec0110(void* o);            // 0x00ec0110
void*  __cdecl FUN_00ec0250(void* o);            // 0x00ec0250
u8     __cdecl FUN_00ec0340(void* o);            // 0x00ec0340
u8     __cdecl FUN_00c13c60(void* o, int a, int b);   // 0x00c13c60
void*  __cdecl FUN_00d2ec10(void* o);            // 0x00d2ec10

// vtable-call helpers (this in ecx)
struct C { char pad[0xb4c]; char* f0b4c; };
struct Vt {
    void*  CallC(void* o, int key);              // slot 0xc
    void*  CallB8(void* o, int key);             // slot 0xb8
    u8     Call2c(void* o);                      // slot 0x2c
    void*  Call20(void* o);                      // slot 0x20
    int    Call4c(void* o);                      // slot 0x4c
    void*  Call10(void* o);                      // slot 0x10
    void*  Call58(void* o);                      // slot 0x58
    u8     CallD4(void* o);                      // slot 0xd4
};

// ================================================================ 0x00ec0a40
// @ 0x00ec0a40
double __cdecl FUN_00ec0a40(void* self_, void* a2, void* a3, void* a4, void* stimuli, u8* out, void* a7, void* evt) {
    char* s = (char*)self_;
    if (stimuli) FUN_00d997e0(stimuli);
    *out = 1;
    void* u = FUN_00d99420((char*)*(void**)(s + 0xb4c) + 0x1d0, *(void**)((char*)evt + 0x2d));
    FUN_00d996e0(u, stimuli);
    char* c = (char*)((H_00c04590*)s)->Get();
    int flag;
    if (s == *(char**)(c + 0x164) && *(void**)(c + 0x168) != (void*)(c + 0x168))
        flag = 1;
    else
        flag = 0;
    *(int*)((char*)stimuli + 0x18) = flag;
    char* f = (char*)*(void**)((char*)stimuli + 4);
    int n = ((H_008e7f80*)f)->GetFileCount();
    if (n == 2) return 0.0;
    void* o = (*(void*(__thiscall**)(char*))((char*)*(void**)f + 0xc))(f);
    u8 r = (*(u8(__thiscall**)(void*))((char*)*(void**)o + 0x2c))(o);
    if (r != 0) return 0.0;
    return 1.0;
}

// ================================================================ 0x00ec0ae0
// @ 0x00ec0ae0
double __cdecl FUN_00ec0ae0(void* self_, void* a2, void* a3, void* a4, void* stimuli, u8* out, void* a7, void* evt) {
    char* s = (char*)self_;
    char* c = (char*)((H_00c04590*)s)->Get();
    if (s == *(char**)(c + 0x164) && *(void**)(c + 0x168) != (void*)(c + 0x168))
        return 0.0;
    if (stimuli) FUN_00d997e0(stimuli);
    *out = 1;
    void* u = FUN_00d99420((char*)*(void**)(s + 0xb4c) + 0x1d0, *(void**)((char*)evt + 0x2d));
    FUN_00d996e0(u, stimuli);
    char* f = (char*)*(void**)((char*)stimuli + 4);
    int n = ((H_008e7f80*)f)->GetFileCount();
    if (n != 2) {
        void* o = (*(void*(__thiscall**)(char*))((char*)*(void**)f + 0xc))(f);
        u8 r = (*(u8(__thiscall**)(void*))((char*)*(void**)o + 0x2c))(o);
        if (r) return 0.0;
        void* g = (*(void*(__thiscall**)(char*))((char*)*(void**)f + 0xc))(f);
        if (((H_00c7da70*)(s + 0x670))->Has(g)) return 1.0;
    }
    return 0.0;
}

// ================================================================ 0x00ec0b90
// @ 0x00ec0b90
u8 __cdecl FUN_00ec0b90(int self, void* a2, void* a3, void* a4, void* a5, u8* out) {
    char* s = (char*)self;
    if (out) {
        *(float*)(out + 4) = g_f1470f1c;
        *(int*)(out + 0) = 0;
        *(float*)(out + 8) = 0.0f;
        out[0xc] = 1;
        out[0xd] = 0;
        *(float*)(out + 0x10) = *(float*)&g_16c74a0;
        *(float*)(out + 0x14) = *(float*)&g_16c74a4;
        *(float*)(out + 0x18) = *(float*)&g_16c74a8;
    }
    char* v = (char*)((H_00bc96a0*)((char*)*(void**)(s + 0xb4c) + 8))->Play(0, 0x40000);
    if (v == 0 || *(int*)(v + 0xc) != 6) return 1;
    char* p = *(char**)(v + 0x14);
    if (p == 0) return 0;
    void* g = (*(void*(__thiscall**)(char*, int))((char*)*(void**)p + 0xc))(p, 0x1186577);
    if (g == 0) return 0;
    ((H_00c70110*)out)->Assign(g);
    out[0xd] = 1;
    return 1;
}

// ================================================================ 0x00ec0c40
// @ 0x00ec0c40
double __cdecl FUN_00ec0c40(void* self) {
    char* s = (char*)self;
    void* mgr = *(void**)0x016c7aa4;
    int limit = *(int*)(*(char**)((char*)mgr + 0x78) + 0xb8);
    char* c = (char*)((H_00c04750*)s)->Get();
    if (*(int*)(c + 0x4b8) == 4) return 1.0;
    c = (char*)((H_00c04750*)s)->Get();
    if (*(int*)(c + 0x4b8) == 6 && *(int*)(s + 0x1648) <= limit) return 1.0;
    return 0.0;
}

// ================================================================ 0x00ec0c90
// @ 0x00ec0c90
u8 __cdecl FUN_00ec0c90(void* obj, void* key) {
    u8 res = 0;
    if (obj != 0) {
        void* s = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)obj + 0xc))(obj, 0xd0036e08);
        if (s != 0) {
            int idx = ((H_00c0f780*)s)->Count();
            if (idx != -1) {
                void* o = ((H_00c0f8a0*)s)->At(idx);
                if (o != 0) {
                    void* g = (*(void*(__thiscall**)(void*, int))((char*)*(void**)o + 0xb8))(o, 0x17f243b);
                    if (g != 0)
                        res = FUN_00c7d090(key, g);
                }
            }
        }
    }
    return res;
}

// ================================================================ 0x00ec0d00
// @ 0x00ec0d00
u8 __cdecl FUN_00ec0d00(void* self_, void* entry_) {
    char* s = (char*)self_;
    uint* e = (uint*)entry_;
    switch (*e) {
    case 0:
    case 4:
    case 6:
        return 1;
    case 1: {
        void* v = ((H_00c7d070*)(s + 0x670))->Beg();
        char** it = *(char***)v;
        char** end = *(char***)((char*)v + 4);
        for (; it != end; ++it) {
            char* p = *it;
            if (p == 0) continue;
            void* g = (*(void*(__thiscall**)(char*, int))((char*)*(void**)p + 0xb8))(p, 0x17f243b);
            if (g == 0) continue;
            if ((*(u8(__thiscall**)(void*))((char*)*(void**)g + 0x2c))(g)) continue;
            if (FUN_00c7d090(e + 1, g)) return 1;
        }
        return 0;
    }
    case 2: {
        if ((*(uint*)(*(char**)(s + 0xb4c) + 0x1c8) & 0x400) == 0) return 0;
        void* p = FUN_00ec0110(s);
        if (p == 0) return 0;
        void* g = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)p + 0xc))(p, e + 1);
        if (FUN_00c7d090(e + 1, g)) return 1;
        return 0;
    }
    case 3:
        return FUN_00ec0c90(s, e + 1);
    case 5: {
        void* v = ((H_00c7d080*)(s + 0x670))->Beg();
        char** it = *(char***)v;
        char** end = *(char***)((char*)v + 4);
        for (; it != end; ++it) {
            char* p = *it;
            if (p == 0) continue;
            void* g = (*(void*(__thiscall**)(char*, int))((char*)*(void**)p + 0xb8))(p, 0x17f243b);
            if (g == 0) continue;
            if ((*(u8(__thiscall**)(void*))((char*)*(void**)g + 0x2c))(g)) continue;
            if (FUN_00c7d090(e + 1, g)) return 1;
        }
        return 0;
    }
    case 7: {
        float a = *(float*)(s + 0x5e0);
        float b = (*(float(__thiscall**)(char*))((char*)*(void**)(s + 0x5a8) + 0x58))(s + 0x5a8);
        int pct;
        if (a == b) pct = 100;
        else pct = (int)((a / b) * 100.0f);
        if (e[1] == 5) return (u8)(pct > (int)e[2]);
        if (e[1] != 6) return 0;
        return (u8)(pct < (int)e[2]);
    }
    case 8: {
        if (*(int*)(s + 0xe8c) != -1) return 0;
        float a = *(float*)(s + 0xe58);
        float b = *(float*)(s + 0xe5c);
        int pct;
        if (a == b) pct = 100;
        else pct = (int)((a / b) * 100.0f);
        if (e[1] == 5) return (u8)(pct > (int)e[2]);
        if (e[1] != 6) return 0;
        return (u8)(pct < (int)e[2]);
    }
    default:
        return 1;
    }
}

// ================================================================ 0x00ec0f50
// @ 0x00ec0f50
u8 __cdecl FUN_00ec0f50(void* self, void* a2, uint* e) {
    if (*e != 4) return 1;
    return FUN_00ec0c90(a2, e + 1);
}

// ================================================================ 0x00ec0f70
// @ 0x00ec0f70
double __cdecl FUN_00ec0f70(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    Key2 lk; lk.a = p[4]; lk.b = p[5];
    if (p[0] == 2) {
        char* o = (char*)FUN_00ec0110(s);
        if (o != 0) {
            void* g = (*(void*(__thiscall**)(char*, uint*))((char*)*(void**)o + 0xc))(o, p + 1);
            if (FUN_00c7d090(p + 1, g)) {
                void* g2 = (*(void*(__thiscall**)(char*, uint*))((char*)*(void**)o + 0xc))(o, (uint*)&lk);
                if (FUN_00c7d090((uint*)&lk, g2)) {
                    if (stimuli) FUN_00d997e0(stimuli);
                    *out = 1;
                    *(void**)((char*)stimuli + 4) = o;
                    *(int*)((char*)stimuli + 0x18) = 0;
                    *(int*)((char*)stimuli + 8) = 0;
                    *(int*)((char*)stimuli + 0) = 0;
                    int* d = (int*)(s + 0x688);
                    for (int i = 0; i < 8; ++i) d[i] = (int)p[i];
                    return 1.0;
                }
            }
        }
    }
    {
        void* v = ((H_00c7d070*)(s + 0x670))->Beg();
        char** beg = *(char***)v;
        char** end = *(char***)((char*)v + 4);
        for (; beg != end; ++beg) {
            char* cp = *beg;
            if (cp == 0) continue;
            char* g = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)cp + 0xb8))(cp, 0x17f243b);
            if (g == 0) continue;
            if ((*(u8(__thiscall**)(char*))((char*)*(void**)g + 0x2c))(g)) continue;
            if (!FUN_00c7d090((uint*)&lk, g)) continue;
            char* rock = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)g + 0xc))(g, 0x13f94d4);
            if (rock == 0) continue;
            if (((H_008e7f80*)rock)->GetFileCount() == 2) continue;
            void* a = (*(void*(__thiscall**)(char*))((char*)*(void**)rock + 0x10))(rock);
            void* b = (*(void*(__thiscall**)(char*))((char*)*(void**)(s + 0x5a8) + 0x10))(s + 0x5a8);
            if (a == b) continue;
            if ((*(int(__thiscall**)(char*))((char*)*(void**)g + 0x4c))(g) == 1 &&
                (*(u8(__thiscall**)(char*))((char*)*(void**)s + 0xd4))(s)) continue;
            if (!FUN_00ec0f50(s, g, p)) continue;
            void* q = (*(void*(__thiscall**)(char*))((char*)*(void**)g + 0x20))(g);
            void* r = FUN_00ec0250(rock);
            if ((r != 0 && *(int*)((char*)r + 0x38) == 0xf) ||
                (q != (void*)0x18c84a9 && q != (void*)0x3a2511e && q != (void*)0x18c88e4)) {
                if (stimuli) FUN_00d997e0(stimuli);
                *out = 1;
                *(void**)((char*)stimuli + 4) = g;
                int* d = (int*)(s + 0x688);
                for (int i = 0; i < 8; ++i) d[i] = (int)p[i];
                return 1.0;
            }
        }
    }
    return 0.0;
}

// ================================================================ 0x00ec11c0
// @ 0x00ec11c0
double __cdecl FUN_00ec11c0(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    if (((H_00c0f780*)s)->Count() != -1) return 0.0;
    Key2 lk; lk.a = p[4]; lk.b = p[5];
    {
        void* v = ((H_00c7d070*)(s + 0x670))->Beg();
        char** beg = *(char***)v;
        char** end = *(char***)((char*)v + 4);
        for (; beg != end; ++beg) {
            char* cp = *beg;
            if (cp == 0) continue;
            char* g = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)cp + 0xb8))(cp, 0x17f243b);
            if (g == 0) continue;
            if ((*(u8(__thiscall**)(char*))((char*)*(void**)g + 0x2c))(g)) continue;
            if (!FUN_00c7d090((uint*)&lk, g)) continue;
            if ((*(void*(__thiscall**)(char*))((char*)*(void**)g + 0x20))(g) != (void*)0x3a2511e) continue;
            if (!FUN_00c13c60(cp, 0, 0)) continue;
            char* q = (char*)FUN_00d2ec10(cp);
            if (q != 0 && *(char**)(q + 0x108) != 0 && *(char**)(q + 0x108) != s) continue;
            if (!FUN_00ec0f50(s, g, p)) continue;
            void* r = FUN_00bc97f0((char*)*(void**)(s + 0xb4c) + 8, 0, 0x40000, g_f1486110, g);
            if (r) *(int*)((char*)r + 0xc) = 4;
            int* d = (int*)(s + 0x688);
            for (int i = 0; i < 8; ++i) d[i] = (int)p[i];
            return 1.0;
        }
    }
    return 0.0;
}

// ================================================================ 0x00ec1320
// @ 0x00ec1320
double __cdecl FUN_00ec1320(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    if (!FUN_00ec0c90(s, p + 4)) return 0.0;
    Key2 lk; lk.a = p[6]; lk.b = p[7];
    char* edi = 0;
    {
        void* v = ((H_00c7d070*)(s + 0x670))->Beg();
        char** beg = *(char***)v;
        char** end = *(char***)((char*)v + 4);
        for (; beg != end; ++beg) {
            char* cp = *beg;
            if (cp == 0) continue;
            char* g = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)cp + 0xb8))(cp, 0x17f243b);
            if (g == 0) continue;
            if ((*(u8(__thiscall**)(char*))((char*)*(void**)g + 0x2c))(g)) continue;
            if (!FUN_00c7d090((uint*)&lk, g)) continue;
            char* rock = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)g + 0xc))(g, 0x13f94d4);
            if (rock != 0 && ((H_008e7f80*)rock)->GetFileCount() == 2) continue;
            void* q = (*(void*(__thiscall**)(char*))((char*)*(void**)g + 0x20))(g);
            if (q != (void*)0x18eb45e && q != (void*)0x70703b3 && q != (void*)0x18c6de8) continue;
            if (*p == 4 && !FUN_00ec0c90(g, p + 1)) continue;
            if (FUN_00ec0340(g)) continue;
            edi = g;
            break;
        }
    }
    if (edi == 0) return 0.0;
    int idx = ((H_00c0f780*)s)->Count();
    void* r = FUN_00bc97f0((char*)*(void**)(s + 0xb4c) + 8, 0, 0x40000, g_f1488900, edi);
    if (r) {
        *(int*)((char*)r + 0xc) = 6;
        *(int*)((char*)r + 0x10) = idx;
        *(char**)((char*)r + 0x14) = edi;
    }
    double res = 1.0;
    *(Rec*)(s + 0x688) = *(Rec*)p;
    return res;
}

// ================================================================ 0x00ec14c0
// @ 0x00ec14c0
double __cdecl FUN_00ec14c0(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    double res = 1.0;
    *(Rec*)(s + 0x688) = *(Rec*)p;
    return res;
}

// ================================================================ 0x00ec1500
// @ 0x00ec1500
double __cdecl FUN_00ec1500(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    Key2 lk; lk.a = p[1]; lk.b = p[2];
    if (p[0] != 2) return 0.0;
    char* o = (char*)FUN_00ec0110(s);
    if (o == 0) return 0.0;
    void* g = (*(void*(__thiscall**)(char*, uint*))((char*)*(void**)o + 0xc))(o, (uint*)&lk);
    if (!FUN_00c7d090((uint*)&lk, g)) return 0.0;
    if (stimuli) FUN_00d997e0(stimuli);
    *out = 1;
    *(void**)((char*)stimuli + 4) = o;
    double res = 1.0;
    *(Rec*)(s + 0x688) = *(Rec*)p;
    return res;
}

// ================================================================ 0x00ec15b0
// @ 0x00ec15b0
double __cdecl FUN_00ec15b0(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    void* r = ((H_00bc96a0*)((char*)*(void**)(s + 0xb4c) + 8))->Play(0, 0x40000);
    if (r == 0 || *(int*)((char*)r + 0xc) != 7) return 0.0;
    double res = 1.0;
    *(Rec*)(s + 0x688) = *(Rec*)p;
    return res;
}

// ================================================================ 0x00ec1610
// @ 0x00ec1610
double __cdecl FUN_00ec1610(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    void* mgr = *(void**)0x016c7aa4;
    int limit = *(int*)(*(char**)((char*)mgr + 0x78) + 0xb8);
    int v = *(int*)(s + 0x1648);
    if (v > limit) return 0.0;
    *(Rec*)(s + 0x688) = *(Rec*)p;
    return 1.0;
}

// ================================================================ 0x00ec1670
// @ 0x00ec1670
double __cdecl FUN_00ec1670(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    uint kind = p[1];
    if (kind != 0 && kind != 1 && kind != 2 && kind != 8) {
        int* d = (int*)(s + 0x688);
        for (int i = 0; i < 8; ++i) d[i] = (int)p[i];
        return 1.0;
    }
    Key2 lk; lk.a = p[1]; lk.b = p[2];
    {
        void* v = ((H_00c7d070*)(s + 0x670))->Beg();
        char** beg = *(char***)v;
        char** end = *(char***)((char*)v + 4);
        for (; beg != end; ++beg) {
            char* cp = *beg;
            if (cp == 0) continue;
            char* g = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)cp + 0xb8))(cp, 0x17f243b);
            if (g == 0) continue;
            if ((*(u8(__thiscall**)(char*))((char*)*(void**)g + 0x2c))(g)) continue;
            if (!FUN_00c7d090((uint*)&lk, g)) continue;
            if (*p == 4 && !FUN_00ec0c90(g, p + 1)) continue;
            FUN_00bc97f0((char*)*(void**)(s + 0xb4c) + 8, 0, 0x10000000, g_f1486110, g);
            int* d = (int*)(s + 0x688);
            for (int i = 0; i < 8; ++i) d[i] = (int)p[i];
            return 1.0;
        }
    }
    return 0.0;
}

// ================================================================ 0x00ec17a0
// @ 0x00ec17a0
double __cdecl FUN_00ec17a0(void* self_, void* a2, void* a3, void* a5, void* stimuli, u8* out, int evt) {
    char* s = (char*)self_;
    uint* p = (uint*)(*(ushort*)((char*)evt + 0x12) * 0x20 + *(uint*)(s + 0x674));
    if (!FUN_00ec0d00(s, p)) return 0.0;
    if (!FUN_00ec0c90(s, p + 4)) return 0.0;
    double res = 1.0;
    *(Rec*)(s + 0x688) = *(Rec*)p;
    return res;
}

// ================================================================ 0x00ec17f0
// @ 0x00ec17f0
double __cdecl FUN_00ec17f0(void* self) {
    char* s = (char*)self;
    int* p = (int*)(s + 0x688);
    int v = *p;
    if (v == 1 || (uint)(v - 7) <= 1) {
        if (!FUN_00ec0d00(s, p)) {
            double r = 1.0;
            *p = 0;
            return r;
        }
    }
    return 0.0;
}

// ================================================================ stimulus slots
// The subsystem at *(creature+0xb4c) starts with eight 0x38-byte stimulus slots; the
// two active-bit masks follow the array at +0x1c0/+0x1c4.  Play()/queue() above reach
// this table through (char*)*(void**)(self+0xb4c) + 8.
struct IRefCounted {
    virtual void AddRef();    // +0x00
    virtual void Release();   // +0x04
};

struct Stimulus {
    uint         id;          // +0x00
    uint         mask;        // +0x04
    float        duration;    // +0x08
    uint         pad0c[8];    // +0x0c
    IRefCounted* object;      // +0x2c
    uint         pad30[2];    // +0x30
};

struct Stimuli {
    void SetStimulus(Stimulus* s, uint a, uint b, float c, IRefCounted* obj); // 0x00bc9700
    void* Find(uint a, uint b);
    Stimulus* Add(uint a, uint b, float c, IRefCounted* obj);

    Stimulus slot[8];         // +0x000
    uint     mMask0;          // +0x1c0
    uint     mMask1;          // +0x1c4
};

extern void (*g_0168b550)(void*);   // 0x0168b550  slot-changed callback
extern void (*g_0168b54c)(void*);   // 0x0168b54c  stimulus-set callback

// @ 0x00bc96a0
void* Stimuli::Find(uint a, uint b)
{
    if (((mMask0 & a) | (mMask1 & b)) == 0)
        return 0;
    for (uint i = 0; i < 8; ++i)
    {
        Stimulus* s = &slot[i];
        if ((s->id & a) | (s->mask & b))
        {
            if (g_0168b550)
                g_0168b550(s);
            return s;
        }
    }
    return 0;
}

// @ 0x00bc97f0
Stimulus* Stimuli::Add(uint a, uint b, float c, IRefCounted* obj)
{
    float best = 3.402823466e+38f;
    uint bestIndex = 0xffffffff;
    Stimulus* s = slot;
    for (uint i = 0; i < 8; ++i, ++s)
    {
        if ((s->id | s->mask) == 0)
        {
            best = 0.0f;
            bestIndex = i;
        }
        else if (s->id == a && s->mask == b)
        {
            SetStimulus(s, a, b, c, obj);
            return s;
        }
        else if (s->duration < best)
        {
            best = s->duration;
            bestIndex = i;
        }
    }
    s = &slot[bestIndex];
    mMask0 &= ~s->id;
    mMask0 |= a;
    mMask1 &= ~s->mask;
    mMask1 |= b;
    s->id = a;
    s->mask = b;
    s->duration = c;
    IRefCounted* old = s->object;
    if (obj != old)
    {
        if (obj)
            obj->AddRef();
        s->object = obj;
        if (old)
            old->Release();
    }
    if (g_0168b54c)
        g_0168b54c(s);
    return s;
}
