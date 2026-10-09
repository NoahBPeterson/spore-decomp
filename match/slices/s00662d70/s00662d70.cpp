// Slice s00662d70: SP::cSPUIFeedList / UI::cSPUIFeedList and helpers.
// UI module: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include "types.h"
#include <intrin.h>

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPi)(void*, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef int(__thiscall* FnRetI)(void*);

static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* CopyImpl(void* first, void* last, void* dest);
extern "C" void  FUN_00646d70(void* first, void* last);
extern "C" void  EA_Messaging_RemoveHandler(void* a, void* b, void* c, void* d, void* e); // 0x00571db0
extern "C" void* SP_AssetBrowser(); // 0x00401030
extern "C" float GetPropertyT_f(int obj, int key, float def);   // 0x00401030 (equiv t3)
extern "C" void  SPUIHelpers_UpdateScrollFrameVertical(void* w);
extern "C" int   cTribeTool_GetTutorialToolPrice(int obj, int key, int def); // 0x004e1c30
extern "C" void* SP_PropertyManager();
extern "C" void* SP_MessageServer();
extern "C" int   __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
extern "C" void  cSPUILayout_Init(void* self, const void* key, int a, int id);
extern "C" void  cSPUILayout_SetParentWin(void* self, void* parent, int a, int id);
extern "C" void  cSPUILayout_SetReloadCallback(void* self, void* fn, void* ctx);
extern "C" void  SPUIHelpers_SetWindowAreaToParent(void* w);
extern "C" void  SPUIHelpers_UpdateMouseFocus(int v);   // 0x00804f50 (equiv t2)
extern "C" void  cSPUIFeedListCategory_Shutdown(void* c);

extern int gVtA;   // 0x013eb384 (equiv t3)
extern int gVtB;   // 0x013ec458 (equiv t2)
extern int gVtC;   // 0x0140016c (equiv t2)
extern int gVtD;   // 0x0140015c (equiv t2)
extern int gVtE;   // 0x0140014c (equiv t2)
extern int gVtF;   // 0x013eb394 (equiv t3)
extern int gVtG;   // 0x013eb938 (equiv t3)
extern "C" void  FUN_00662b40(void* p);
extern "C" void  FUN_00662c70(void* p);
extern "C" void* FUN_00662c10(void* v);
extern "C" void* FUN_006629a0(int v);
extern "C" void* FUN_00662960(int v);
extern "C" void  FUN_006629e0(void* p);
extern "C" void  FUN_00663ef0(int v);
extern "C" void  FUN_00664390(float a, float b, float c, float d);
extern "C" void  FUN_0082a450();

// ---------------------------------------------------------------------------
struct cSPUIFeedList {
    char  vt[0xc];                     // 0x00
    bool  mIsVisible;                  // 0x10
    bool  mWheel;                      // 0x11
    bool  m12;                         // 0x12
    bool  m13;                         // 0x13
    float mTarget;                     // 0x14
    float mActual;                     // 0x18
    float mMax;                        // 0x1c
    void* mpLayout;                    // 0x20
    void* mpWinParent;                 // 0x24
    void* mpWinRoot;                   // 0x28
    void* mpWinList;                   // 0x2c
    void* mpWinScrollRoot;             // 0x30
    void* mpWinScrollClientArea;       // 0x34
    void* mCatBegin;                   // 0x38
    void* mCatEnd;                     // 0x3c
    void* mCatCap;                     // 0x40
    void* m44;                         // 0x44
    char  pad48[4];                    // 0x48
    void* mpSelectedFeed;              // 0x4c
    void* mpServer;                    // 0x50
    void* mpHandler;                   // 0x54
    void* mpIdArray;                   // 0x58
    int   mnIdArrayCount;              // 0x5c
    int   mnPriority;                  // 0x60
    void* mpConfig;                    // 0x64

    void* Ctor();
    void  Dtor();
    void  ShutdownCategories();
};

struct VecAutoRef {
    void* begin; void* end; void* cap;
    void erase(void* first, void* last);
};

// @ 0x00663040
void* cSPUIFeedList::Ctor() {
    char* p = (char*)this;
    *(void* volatile*)&p[4] = &gVtA;
    *(void* volatile*)&p[8] = &gVtB;
    *(int* volatile*)(p + 0xc) = 0;
    *(void**)(p + 0) = &gVtC;
    *(void**)(p + 4) = &gVtD;
    *(void**)(p + 8) = &gVtE;
    *(char*)(p + 0x10) = 0;
    *(char*)(p + 0x11) = 0;
    *(char*)(p + 0x12) = 0;
    *(char*)(p + 0x13) = 0;
    *(float*)(p + 0x14) = 0.0f;
    *(float*)(p + 0x18) = 0.0f;
    *(float*)(p + 0x1c) = 0.0f;
    *(void**)(p + 0x20) = 0; *(void**)(p + 0x24) = 0; *(void**)(p + 0x28) = 0;
    *(void**)(p + 0x2c) = 0; *(void**)(p + 0x30) = 0; *(void**)(p + 0x34) = 0;
    *(void**)(p + 0x38) = 0; *(void**)(p + 0x3c) = 0; *(void**)(p + 0x40) = 0;
    *(void**)(p + 0x4c) = 0;
    *(void**)(p + 0x50) = 0; *(void**)(p + 0x54) = 0; *(void**)(p + 0x58) = 0;
    *(void**)(p + 0x5c) = 0; *(void**)(p + 0x60) = 0; *(void**)(p + 0x64) = 0;
    *(void**)(p + 0x68) = 0;
    return p;
}

// @ 0x006630e0
void cSPUIFeedList::Dtor() {
    char* p = (char*)this;
    *(void**)(p + 0) = &gVtC;
    *(void**)(p + 4) = &gVtD;
    *(void**)(p + 8) = &gVtE;
    void* a = *(void**)(p + 0x68);
    if (a) (*(FnP)Vslot(a, 4))(a);
    void* h = *(void**)(p + 0x54);
    if (h) { void* cfg = *(void**)(p + 0x64); *(void**)(p + 0x54) = 0;
             EA_Messaging_RemoveHandler(h, *(void**)(p + 0x58), *(void**)(p + 0x5c), *(void**)(p + 0x60), cfg); }
    a = *(void**)(p + 0x50); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x4c); if (a) (*(FnP)Vslot(a, 0xc))(a);
    // vector dtor at 0x38
    { void* v = p + 0x38; (*(void(__thiscall*)(void*))0x5c9c30)(v); }
    a = *(void**)(p + 0x34); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x30); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x2c); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x28); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x24); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x20); if (a) (*(FnP)Vslot(a, 8))(a);
    *(void**)(p + 8) = &gVtB;
    *(void**)(p + 4) = &gVtF;
    *(void**)(p + 0) = &gVtG;
}

// @ 0x00662d70
void cSPUIFeedList_Update(cSPUIFeedList* s) {
    char* p = (char*)s;
    if (!*(void**)(p + 0x34) || !*(void**)(p + 0x30)) return;
    float* r = (*(float*(__thiscall*)(void*))Vslot(*(void**)(p + 0x30), 0x38))(*(void**)(p + 0x30));
    float v[4];
    v[0] = r[0]; v[1] = r[1]; v[2] = r[2]; v[3] = r[3];
    SPUIHelpers_UpdateScrollFrameVertical(0);
    void* w = *(void**)(p + 0x34);
    float* ww = (float*)*(void**)((char*)w + 0x20);
    int a = (*(int(__thiscall*)(void*))Vslot(ww, 0x40))(ww);
    int b = (*(int(__thiscall*)(void*))Vslot(ww, 0x38))(ww);
    *(float*)(p + 0x1c) = (float)(b - a);
    void* inner = *(void**)((char*)*(void**)(p + 0x34) + 0x18);
    float* ir = (*(float*(__thiscall*)(void*))Vslot(inner, 0x38))(inner);
    v[2] = (ir[2] - ir[0]) + ir[0];
    (*(void(__thiscall*)(void*, void*))Vslot(*(void**)(p + 0x30), 0x6c))(*(void**)(p + 0x30), v);
    void* cli = *(void**)((char*)*(void**)(p + 0x34) + 0x20);
    if (cli) {
        int t1 = 0x96, t2 = 8;
        void* ab = SP_AssetBrowser();
        if (ab && *(void**)((char*)ab + 0x18)) {
            ab = SP_AssetBrowser();
            t1 = cTribeTool_GetTutorialToolPrice((int)*(void**)((char*)ab + 0x18), 0x2690b86e, 0x96);
            ab = SP_AssetBrowser();
            t2 = cTribeTool_GetTutorialToolPrice((int)*(void**)((char*)ab + 0x18), 0x908bbe2d, 8);
        }
        (*(void(__thiscall*)(void*, int))Vslot(cli, 0x4c))(cli, t1);
        (*(void(__thiscall*)(void*, int))Vslot(cli, 0x54))(cli, t2);
    }
}

// @ 0x00662ea0
char cSPUIFeedList_DoMessage(cSPUIFeedList* s, int msg, int* data) {
    (void)msg;
    char* p = (char*)s;
    if (data[2] == 9) {
        if (data[1] == *(int*)(p + 0x30) || data[1] == *(int*)(*(int*)(p + 0x34) + 0x18)) {
            float mult = 0.8f;
            void* ab = SP_AssetBrowser();
            if (ab && *(void**)((char*)ab + 0x18)) {
                ab = SP_AssetBrowser();
                mult = GetPropertyT_f((int)*(void**)((char*)ab + 0x18), 0xfd92843d, 0.8f);
            }
            float t = *(float*)(p + 0x14) - (float)data[0x18/4] * mult;
            *(float*)(p + 0x14) = t;
            if (t <= 0.0f) t = 0.0f;
            if (*(float*)(p + 0x1c) <= t) t = *(float*)(p + 0x1c);
            *(float*)(p + 0x14) = t;
            *(char*)(p + 0x11) = 1;
            return 1;
        }
    }
    else if (data[2] == (int)0x8ef0c8dd) {
        int v = *(int*)(p + 0x34);
        if (data[1] == *(int*)(v + 0x10)) {
            if (!*(char*)(p + 0x11) && v) {
                *(float*)(p + 0x18) = (float)(*(int(__thiscall*)(void*))Vslot(*(void**)(v + 0x20), 0x28))(*(void**)(v + 0x20));
                *(float*)(p + 0x14) = (float)(*(int(__thiscall*)(void*))Vslot(*(void**)(*(int*)(p + 0x34) + 0x20), 0x28))(*(void**)(*(int*)(p + 0x34) + 0x20));
            }
            void* w = *(void**)(p + 0x28);
            if (w) {
                float* r = (*(float*(__thiscall*)(void*))Vslot(w, 0x38))(w);
                float vv[4];
                vv[0] = r[0]; vv[2] = r[2];
                float d = -(float)data[5] - r[1];
                vv[1] = r[1] + d; vv[3] = r[3] + d;
                (*(void(__thiscall*)(void*, void*))Vslot(w, 0x6c))(w, vv);
            }
            return 0;
        }
    }
    return 0;
}

// @ 0x006631c0
void cSPUIFeedList_UpdateScrolling(cSPUIFeedList* s, unsigned dt) {
    char* p = (char*)s;
    float speed = 6.0f;
    void* ab = SP_AssetBrowser();
    if (ab && *(void**)((char*)ab + 0x18)) {
        ab = SP_AssetBrowser();
        speed = GetPropertyT_f((int)*(void**)((char*)ab + 0x18), 0xac40f7e5, 6.0f);
    }
    if (*(void**)(p + 0x30) && *(float*)(p + 0x14) != *(float*)(p + 0x18)) {
        float f = (float)dt * speed * 0.001f;
        float cl = 0.0f;
        if (cl < f) cl = f;
        if (cl > 1.0f) cl = 1.0f;
        float v = (*(float*)(p + 0x14) - *(float*)(p + 0x18)) * cl + *(float*)(p + 0x18);
        *(float*)(p + 0x18) = v;
        void* cli = *(void**)(p + 0x34);
        if (cli) {
            void* inner = *(void**)((char*)cli + 0x20);
            (*(void(__thiscall*)(void*, int, int))Vslot(inner, 0x24))(inner, (int)v, 1);
        }
        float a = *(float*)(p + 0x18) - *(float*)(p + 0x14);
        if (a < 0) a = -a;
        if (!(a < 0.5f)) {
            *(float*)(p + 0x18) = *(float*)(p + 0x14);
        }
        SPUIHelpers_UpdateMouseFocus(1);
    }
    if (*(float*)(p + 0x18) == *(float*)(p + 0x14)) *(char*)(p + 0x11) = 0;
    cSPUIFeedList_Update(s);
    void* sel = *(void**)(p + 0x4c);
    if (sel) {
        FUN_00662b40(sel);
        sel = *(void**)(p + 0x4c);
        if (sel) { *(void**)(p + 0x4c) = 0; (*(FnP)Vslot(sel, 0xc))(sel); }
    }
    if (*(char*)(p + 0x13)) { FUN_00662c70(*(void**)(p + 0x50)); *(char*)(p + 0x13) = 0; }
}

// @ 0x00663350
void FUN_00663350(char* p, int param) {
    if (!*(void**)(p + 0x30)) return;
    float* r = (*(float*(__thiscall*)(void*))Vslot(*(void**)(p + 0x30), 0x38))(*(void**)(p + 0x30));
    float w = r[2] - r[0];
    int n = (int)((*(char**)(p + 0x3c) - *(char**)(p + 0x38)) >> 2);
    float y = 0.0f;
    for (int i = 0; i < n; ++i) {
        void* obj = *(void**)(*(int*)(p + 0x38) + i * 4);
        FUN_00663ef0(param);
        float rad = ((float(__thiscall*)(void*))0xad2810)(obj);
        float y2 = rad + y;
        FUN_00664390(0.0f, y, w, y2);
        y = y2;
    }
    (*(void(__thiscall*)(void*, float, float))Vslot(*(void**)(p + 0x30), 0x74))(*(void**)(p + 0x30), w, y);
    cSPUIFeedList_UpdateScrolling((cSPUIFeedList*)p, param);
}

// @ 0x00663430
void VecAutoRef::erase(void* first, void* last) {
    char* r = (char*)CopyImpl(last, end, first);
    char* e = (char*)end;
    while (r < e) {
        void* p = *(void**)r;
        if (p) (*(FnP)Vslot(p, 0xc))(p);
        r += 4;
    }
    *(int*)&end += -((((int)((char*)last - (char*)first)) >> 2) * 4);
}

// @ 0x00663490
void cSPUIFeedList::ShutdownCategories() {
    char* p = (char*)this;
    int n = (int)((*(char**)(p + 0x3c) - *(char**)(p + 0x38)) >> 2);
    for (int i = 0; i < n; ++i)
        cSPUIFeedListCategory_Shutdown(*(void**)(*(int*)(p + 0x38) + i * 4));
    ((VecAutoRef*)(p + 0x38))->erase(*(void**)(p + 0x38), *(void**)(p + 0x3c));
}

// @ 0x006634d0
void FUN_006634d0(char* p) {
    int n = (int)((*(char**)(p + 0x3c) - *(char**)(p + 0x38)) >> 2);
    for (int i = 0; i < n; ++i)
        cSPUIFeedListCategory_Shutdown(*(void**)(*(int*)(p + 0x38) + i * 4));
    ((VecAutoRef*)(p + 0x38))->erase(*(void**)(p + 0x38), *(void**)(p + 0x3c));
    if (*(void**)(p + 0x30)) {
        void* local[3];
        local[0] = 0; local[1] = 0; local[2] = 0;
        (*(char(__thiscall*)(void*, int, void*, void*))Vslot(*(void**)(p + 0x68), 0x24))(*(void**)(p + 0x68), 0x744717c0, local, 0);
    }
}

// @ 0x00663680
void FUN_00663680(char* p, int layout, char reload) {
    if (!reload) {
        ((cSPUIFeedList*)p)->ShutdownCategories();
        if (*(void**)(p + 0x34)) {
            (*(void(__thiscall*)(void*, char*))Vslot(*(void**)((char*)*(void**)(p + 0x34) + 0x10), 0x108))(*(void**)((char*)*(void**)(p + 0x34) + 0x10), p);
            FUN_0082a450();
            void* q = *(void**)(p + 0x34);
            if (q) { *(void**)(p + 0x34) = 0; (*(FnP)Vslot(q, 4))(q); }
        }
        if (*(void**)(p + 0x30)) (*(void(__thiscall*)(void*, char*))Vslot(*(void**)(p + 0x30), 0x108))(*(void**)(p + 0x30), p);
        return;
    }
    (void)layout;
    FUN_006634d0(p);
}

// @ 0x00663860  ReloadCallback
void FUN_00663860(char* p, void* parent, int a, int b, void* cfg) {
    void* old = *(void**)(p + 0x24);
    if (parent != old) {
        if (parent) (*(FnP)Vslot(parent, 0))(parent);
        *(void**)(p + 0x24) = parent;
        if (old) (*(FnP)Vslot(old, 4))(old);
    }
    if (cfg) {
        void* o2 = *(void**)(p + 0x28);
        if (cfg != o2) { (*(FnP)Vslot(cfg, 0))(cfg); *(void**)(p + 0x28) = cfg; if (o2) (*(FnP)Vslot(o2, 4))(o2); }
    }
    else {
        void* w = (void*)0;
        (void)w;
    }
    (void)a; (void)b;
    // full property/layout init
    void* pm = SP_PropertyManager();
    void* o2 = *(void**)(p + 0x68);
    if (o2) { *(void**)(p + 0x68) = 0; (*(FnP)Vslot(o2, 4))(o2); }
    (*(void(__thiscall*)(void*, int, void**))Vslot(pm, 0x2c))(pm, 0x6edc12d4, (void**)(p + 0x68));
    *(char*)(p + 0x10) = 1;
}

// @ 0x00663a90
char FUN_00663a90(char* p, unsigned msg, int* data) {
    if (msg == 0x44db12e) { FUN_006634d0(p); return 0; }
    if (msg == 0x53dd093) {
        if (*(char*)(p + 0xc)) FUN_006629e0(p - 4);
        return 0;
    }
    if (msg == 0xb3d53f95 && *(char*)(p + 0xc)) {
        if (data) {
            if (!*(char*)(p + 0xe)) {
                void* g = (void*)0; (void)g;
            }
            void* arg = (void*)(unsigned)data[4];
            if (data[4] == 0) {
                if (*(char*)((char*)data + 0x14)) arg = FUN_006629a0(data[3]);
                else arg = FUN_00662960(data[3]);
            }
            FUN_00662c10(arg);
        }
    }
    return 0;
}

// @ 0x00663b80
char FUN_00663b80(int a, int b) {
    if (!a || !b) return 0;
    int x = *(int*)(a + 0xc4);
    int y = *(int*)(b + 0xc4);
    if (x != y) return (char)(x < y);
    const wchar_t* sa = *(const wchar_t**)(a + 0x18);
    const wchar_t* sb = *(const wchar_t**)(b + 0x18);
    if (sa && sb) {
        if (_wcsicmp(sa, sb) < 0) return 1;
    }
    return 0;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
