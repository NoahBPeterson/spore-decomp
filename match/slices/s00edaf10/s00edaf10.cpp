// Scenario edit-mode "script acts" bar UI + the naming-base class it derives from.
// Built with /O2 (SSE float) and the EA framework; virtual calls via vtable slots.
//
// Flags: /O2 /MD /Gy /EP /TP /arch:SSE2

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short wchar16;

// ---------------------------------------------------------------------------
// stub vtable-call typedefs (thiscall)
// ---------------------------------------------------------------------------
typedef void  (__thiscall *FnV)(void*);
typedef int   (__thiscall *FnI)(void*, int);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPII)(void*, int, int);
typedef void* (__thiscall *FnPI)(void*, int);
typedef int   (__thiscall *FnII)(void*, int, int);
typedef int   (__thiscall *FnIII)(void*, int, int, void*);

// ---------------------------------------------------------------------------
// externals with real names (addresses masked, so declarations set conventions)
// ---------------------------------------------------------------------------
extern char* g_pMagic;                 // 0x016c7aa4

extern void* operator_new(uint32_t size, const char* name, int, int, const char*, int); // 0x00f473a0
extern void  operator_delete(void*);   // 0x00f47380

// cSPEditorNaming (base)
extern void cSPEditorNaming_ctor();    // 0x005bfff0
extern void cSPEditorNaming_Shutdown(); // 0x005bfb90
extern void cSPEditorNaming_SetExpanded(); // 0x005c0380

// EA framework / helpers
extern int  cSPUILayout_Init();        // 0x008120d0
extern int  EA_Messaging_MessageServer();  // 0x0067dcc0
extern void EA_Messaging_RemoveHandler();  // 0x00571db0
extern int  ScenarioTutorials_GetActive(); // 0x00efc520

// ---------------------------------------------------------------------------
// class A: the cSPEditorNaming-derived acts-bar UI (size >= 0xe0)
// ---------------------------------------------------------------------------
struct ActsBarUI {
    char pad[0xe0];
    void FUN_00edaf10();   // ctor piece? (see below)
    void FUN_00edb120(int idx);   // 0x00edb120
    void FUN_00edb6c0();          // 0x00edb6c0
    void FUN_00edb730();          // 0x00edb730
    void FUN_00edb9b0(int on);    // 0x00edb9b0
    void FUN_00edbcb0();          // 0x00edbcb0
    void FUN_00edbd30(int on);    // 0x00edbd30
    void FUN_00edbdd0(int a);     // 0x00edbdd0
    int  FUN_00edbef0(int id, int* p); // 0x00edbef0
};

// class B: cScenarioEditModeScriptActsBarUI (size 0x50)
struct cScenarioEditModeScriptActsBarUI {
    char pad[0x50];
    void ctor();      // 0x00edbe00
    void dtor();      // 0x00edbe60
};

// ---------------------------------------------------------------------------
// 0x00edaf10  constructor body for class A
// ---------------------------------------------------------------------------
// @ 0x00edaf10
ActsBarUI* __fastcall FUN_00edaf10(ActsBarUI* self)
{
    cSPEditorNaming_ctor();
    *(void**)((char*)self + 0x00) = (void*)0x148a440;
    *(void**)((char*)self + 0x04) = (void*)0x148a430;
    *(void**)((char*)self + 0x08) = (void*)0x148a420;
    *(uint32_t*)((char*)self + 0x38) = 0;
    void* p = (char*)self + 0x54;
    *(void**)((char*)self + 0x4c) = p;
    *(void**)((char*)self + 0x40) = p;
    *(void**)((char*)self + 0x3c) = p;
    *(void**)((char*)self + 0x44) = (char*)p + 0x28;
    *(uint32_t*)((char*)self + 0x8c) = 0;
    *(uint32_t*)((char*)self + 0x90) = 0;
    *(uint32_t*)((char*)self + 0x94) = 0;
    *(uint32_t*)((char*)self + 0x98) = 0;
    *(uint32_t*)((char*)self + 0x9c) = 0;
    *(uint32_t*)((char*)self + 0xa0) = 0;
    *(uint32_t*)((char*)self + 0xa4) = 0;
    *(uint32_t*)((char*)self + 0xa8) = 0;
    *(uint32_t*)((char*)self + 0xac) = 0;
    *(uint32_t*)((char*)self + 0xb0) = 0;
    *(uint32_t*)((char*)self + 0xb4) = 0;
    *(uint32_t*)((char*)self + 0xb8) = 0;
    *(uint32_t*)((char*)self + 0xcc) = 0;
    *(uint32_t*)((char*)self + 0xd0) = 0;
    *(uint32_t*)((char*)self + 0xd4) = 0;
    *(uint32_t*)((char*)self + 0xd8) = 0;
    *(uint32_t*)((char*)self + 0xdc) = 0;
    return self;
}

// ---------------------------------------------------------------------------
// 0x00edb120  refresh one acts-bar entry (heavy UI)
// ---------------------------------------------------------------------------
extern int  FUN_00edabf0(int idx);          // 0x00edabf0
extern int  FUN_00f04060();                 // 0x00f04060
extern void* cSPUILayout_FindWindowByID(void* layout, int id, int deep); // 0x008105b0
extern uint32_t SPUIHelpers_GetImageFromTexture(int, int, int, int);      // 0x008060d0
extern void SPUIHelpers_SetDrawableImage(void*, uint32_t, int);           // 0x008068d0
extern void SPUIHelpers_SetWindowImage(void*, void*, int);                // 0x00807bb0
extern void SPUIHelpers_SetTooltipText(void*);                            // 0x00806de0
extern int  cGameData_GetPoliticalID(void*);                              // 0x005aacf0
extern int  FUN_0067dd60();                                               // 0x0067dd60
extern void cString_ctor(void*, int, int, int);                           // 0x006b5770
extern int  cString_GetText(void*, int, int);                             // 0x006b55c0
extern void cString_dtor(void*);                                          // 0x006b5240
extern int  WStr_Format(wchar16*, wchar16*, int, int);                    // 0x0041e050
extern void FUN_00f3bfc0();                                               // 0x00f3bfc0
extern void FUN_00edadd0();                                               // 0x00edadd0
extern void FUN_00f03ff0();                                               // 0x00f03ff0
extern void FUN_00efbbe0(int, int);                                       // 0x00efbbe0

// @ 0x00edb120
void ActsBarUI::FUN_00edb120(int idx)
{
    char* self = (char*)this;
    int b1 = FUN_00edabf0(idx) != 0;
    int b2 = FUN_00edabf0(idx) != 0;
    int maxVal = b2 ? -3 : -2;
    (void)maxVal;
    char* g = g_pMagic;
    int active = FUN_00f04060();
    bool shown = (idx != 0) || b1 ? true : (active != 0);
    char* layout = (char*)cSPUILayout_FindWindowByID(*(void**)(self + 0x18), 0x7c7a720, 1);
    // primary button window
    void* w = (*(FnPII)(*(void**)(*(char**)layout + 0xf0)))(layout, 0x447b980, 1);
    if (w) {
        int wantShow = 1; (void)wantShow;
        (*(FnII)(*(void**)(*(char**)w + 0x7c)))(w, 2, shown);
    }
    void* w2 = (*(FnPII)(*(void**)(*(char**)layout + 0xf0)))(layout, 0x447b968, 1);
    if (w2)
        (*(FnII)(*(void**)(*(char**)w2 + 0x7c)))(w2, 2, shown);
    void* icon = (*(FnPII)(*(void**)(*(char**)layout + 0xf0)))(layout, 0x771fb08, 1);
    int state = *(int*)(self + 0x7c + idx * 4);
    uint32_t label = 0x7736327;
    if (state == -3) {
        *(int*)(self + 0xbc + idx * 4) = 2;
        SPUIHelpers_SetWindowImage(icon, 0, -1);
    } else if (state == -1) {
        *(int*)(self + 0xbc + idx * 4) = 3;
        int* q = (int*)(self + 0x8c + idx * 0xc);
        q[0] = 0; q[1] = 0; q[2] = 0;
        label = 0x7736326;
    } else if (state == -2) {
        *(int*)(self + 0xbc + idx * 4) = 0;
        int* q = (int*)(self + 0x8c + idx * 0xc);
        q[0] = 0; q[1] = 0; q[2] = 0;
        int pid = cGameData_GetPoliticalID(*(void**)(g + 0x74));
        if (pid) {
            char* sys = (char*)FUN_0067dd60();
            (*(FnII)(*(void**)(*(char**)sys + 0x2c)))(sys, pid, 0);
            (*(FnII)(*(void**)(*(char**)sys + 0x2c)))(sys, pid, 0);
        }
        label = 0x7736328;
    } else {
        *(int*)(self + 0xbc + idx * 4) = 1;
        int* q = (int*)(self + 0x8c + idx * 0xc);
        uint32_t tex = SPUIHelpers_GetImageFromTexture(q[0], q[2], -1, -1);
        SPUIHelpers_SetDrawableImage(icon, tex, -1);
    }
    if (idx == 0)
        label = 0x7736325;
    uint32_t a = SPUIHelpers_GetImageFromTexture(0, 0, -1, -1);
    (void)a;
    SPUIHelpers_SetTooltipText(0);
}

// ---------------------------------------------------------------------------
// 0x00edb6c0  teardown of class A
// ---------------------------------------------------------------------------
extern void FUN_00e25bd0();            // eastl vector erase thunk, 0x00e25bd0
// @ 0x00edb6c0
void ActsBarUI::FUN_00edb6c0()
{
    char* self = (char*)this;
    void* p = *(void**)(self + 0x38);
    if (p) {
        *(void**)(self + 0x38) = 0;
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    }
    FUN_00e25bd0();                     // erase(this+0x3c, ...)
    int h = *(int*)(self + 0xcc);
    if (h) {
        *(int*)(self + 0xcc) = 0;
        EA_Messaging_RemoveHandler();
    }
    cSPEditorNaming_Shutdown();
}

// ---------------------------------------------------------------------------
// 0x00edb730  refresh all 4 entries
// ---------------------------------------------------------------------------
// @ 0x00edb730
void ActsBarUI::FUN_00edb730()
{
    for (int i = 0; i < 4; ++i)
        FUN_00edb120(i);
}

// ---------------------------------------------------------------------------
// 0x00edb750  handle message / draw update (heavy switch)
// ---------------------------------------------------------------------------
extern void FUN_00f3bfc0();  // (dup) declared above
// @ 0x00edb750
int FUN_00edb750(void* self, void* msg)
{
    uint32_t id = *(uint32_t*)((char*)msg + 8);
    if (id == 0x4cab02d) {
        return 0;
    } else if (id == 0x685a2b9) {
        return 0;
    } else if (id == 0x287259f6) {
        char* a = *(char**)((char*)msg + 4);
        (*(FnV)(*(void**)(*(char**)a + 0x1c)))(a);
        return 0;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00edb9b0  expand/collapse
// ---------------------------------------------------------------------------
// @ 0x00edb9b0
void ActsBarUI::FUN_00edb9b0(int on)
{
    char* self = (char*)this;
    cSPEditorNaming_SetExpanded();
    if (on) {
        FUN_00edadd0();
        for (int i = 0; i < 4; ++i)
            FUN_00edb120(i);
        return;
    }
    char* mgr = *(char**)(g_pMagic + 0x74);
    FUN_00f3bfc0();
    for (int i = 0; i < 4; ++i) {
        FUN_00f03ff0();
        FUN_00f3bfc0();
    }
    FUN_00efbbe0(0x16, 0x17);
    (void)mgr;
    (void)self;
}

// ---------------------------------------------------------------------------
// 0x00edba80  eastl::copy_backward_impl<...>::do_copy (RunInfo, stride 0x10)
// ---------------------------------------------------------------------------
struct RunInfo { uint32_t d[4]; };

// @ 0x00edba80
RunInfo* do_copy(RunInfo* first, RunInfo* last, RunInfo* result)
{
    while (first != last) {
        --last;
        --result;
        *result = *last;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00edbac0  UI init (badges-like)
// ---------------------------------------------------------------------------
extern void* cConnectionDialog_ctor();                 // 0x00810000
extern int   cSPUILayout_Init_(void*, int, int, int);  // 0x008120d0
extern void  cSPUILayout_SetParentWin(void*, void*, int, int); // 0x008121b0
extern void  cSPUILayout_SetVisibility(void*, int);    // 0x00810590
extern void* FUN_00f38c70();                            // 0x00f38c70
extern void  FUN_00f47630(void*);                       // 0x00f47630

// @ 0x00edbac0
int FUN_00edbac0(void* self, void* parent)
{
    char* s = (char*)self;
    char* dlg = 0;
    void* buf = operator_new(0x18, (const char*)0x013f6b3c, 0, 0, 0, 0);
    if (buf)
        dlg = (char*)cConnectionDialog_ctor();
    char* old = *(char**)(s + 0xc);
    if (dlg != old) {
        if (dlg)
            (*(FnV)(*(void**)(*(char**)dlg + 4)))(dlg);
        *(char**)(s + 0xc) = dlg;
        if (old)
            (*(FnV)(*(void**)(*(char**)old + 8)))(old);
    }
    if (!cSPUILayout_Init_(*(void**)(s + 0xc), (int)0x015ac580, 0, 0x5b598fa))
        return 0;
    char* old2 = *(char**)(s + 0x10);
    if (parent != old2) {
        if (parent)
            (*(FnV)(*(void**)(*(char**)parent)))(parent);
        *(char**)(s + 0x10) = (char*)parent;
        if (old2)
            (*(FnV)(*(void**)(*(char**)old2 + 4)))(old2);
    }
    cSPUILayout_SetParentWin(*(void**)(s + 0xc), *(void**)(s + 0x10), 1, 0x5b598fa);
    cSPUILayout_SetVisibility(*(void**)(s + 0xc), 0);
    char* w = (char*)cSPUILayout_FindWindowByID(*(void**)(s + 0xc), 0x743b980, 1);
    char* old3 = *(char**)(s + 0x14);
    if (w != old3) {
        if (w)
            (*(FnV)(*(void**)(*(char**)w)))(w);
        *(char**)(s + 0x14) = w;
        if (old3)
            (*(FnV)(*(void**)(*(char**)old3 + 4)))(old3);
    }
    if (!*(void**)(s + 0x14))
        return 0;
    float* r = (float*)(*(FnP)(*(void**)(*(char**)(s + 0x10) + 0x38)))(*(void**)(s + 0x10));
    float f1 = r[0];
    (*(FnIII)(*(void**)(*(char**)(s + 0x14) + 0x70)))(*(void**)(s + 0x14), 0, 0, 0);
    char* q = *(char**)(s + 0x14);
    float* r2 = (float*)(*(FnP)(*(void**)(*(char**)q + 0x38)))(q);
    float f2 = r2[3] - r2[1];
    (*(FnIII)(*(void**)(*(char**)q + 0x74)))(q, *(int*)&f1, *(int*)&f2, 0);
    void* found = cSPUILayout_FindWindowByID(*(void**)(s + 0xc), 0x7c3fbfe, 1);
    if (found) {
        void* obj = operator_new(0x44, (const char*)0x013f6b3c, 0, 0, 0, 0);
        if (obj)
            obj = (void*)FUN_00f38c70();
        else
            obj = 0;
        FUN_00f47630(obj);
        char* slot = *(char**)(s + 0x4c);
        void* f2 = cSPUILayout_FindWindowByID(*(void**)(s + 0xc), 0x7c3fbfe, 1);
        (*(FnI)(*(void**)(*(char**)slot + 0x10)))(slot, (int)f2);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00edbcb0  class B teardown
// ---------------------------------------------------------------------------
extern void FUN_007f8f00();                          // 0x007f8f00
extern void cSPUILayout_Shutdown(void*, int);        // 0x00811ad0

// @ 0x00edbcb0
void cScenarioEditModeScriptActsBarUI::dtor()
{
    char* s = (char*)this;
    char* c = *(char**)(s + 0x4c);
    if (c)
        (*(FnV)(*(void**)(*(char**)c + 0x14)))(c);
    FUN_007f8f00();
    int h = *(int*)(s + 0x18);
    if (h) {
        *(int*)(s + 0x18) = 0;
        EA_Messaging_RemoveHandler();
    }
    if (*(void**)(s + 0xc))
        cSPUILayout_Shutdown(*(void**)(s + 0xc), 1);
    char* p = *(char**)(s + 0x10);
    if (p) {
        *(void**)(s + 0x10) = 0;
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    }
    p = *(char**)(s + 0xc);
    if (p) {
        *(void**)(s + 0xc) = 0;
        (*(FnV)(*(void**)(*(char**)p + 8)))(p);
    }
}

// ---------------------------------------------------------------------------
// 0x00edbd30  register/unregister message handler
// ---------------------------------------------------------------------------
// @ 0x00edbd30
void FUN_00edbd30(void* self, int on)
{
    char* s = (char*)self;
    if (on) {
        char* h = (char*)EA_Messaging_MessageServer();
        char* sub = s ? s + 8 : 0;
        *(char**)(s + 0x18) = h;
        *(char**)(s + 0x1c) = sub;
        *(void**)(s + 0x20) = (void*)0x148a46c;
        *(int*)(s + 0x24) = 1;
        *(int*)(s + 0x28) = 0;
        if (h && sub)
            (*(FnII)(*(void**)(*(char**)h + 0x24)))(h, 0x7c41ae9, (int)sub);
    } else {
        int h = *(int*)(s + 0x18);
        if (h) {
            *(int*)(s + 0x18) = 0;
            EA_Messaging_RemoveHandler();
        }
    }
    char* w = *(char**)(s + 0x10);
    (*(FnII)(*(void**)(*(char**)w + 0x7c)))(w, 1, on);
    cSPUILayout_SetVisibility(*(void**)(s + 0xc), 1);
}

// ---------------------------------------------------------------------------
// 0x00edbdd0  tick
// ---------------------------------------------------------------------------
extern int  cSPUIAnimator_Empty(void*);   // 0x007f6340
extern void cSPUIAnimator_Update(void*);  // 0x007f63b0

// @ 0x00edbdd0
void FUN_00edbdd0(void* self, int a)
{
    char* s = (char*)self;
    char* c = *(char**)(s + 0x4c);
    if (c)
        (*(FnI)(*(void**)(*(char**)c + 0x18)))(c, a);
    if (!cSPUIAnimator_Empty(s + 0x2c))
        cSPUIAnimator_Update(s + 0x2c);
}

// ---------------------------------------------------------------------------
// 0x00edbe00  cScenarioEditModeScriptActsBarUI ctor
// ---------------------------------------------------------------------------
extern void cSPUIAnimator_ctor(void*);   // 0x007f83e0

// @ 0x00edbe00
void cScenarioEditModeScriptActsBarUI::ctor()
{
    char* s = (char*)this;
    *(int*)(s + 4) = 0;
    *(void**)(s + 8) = (void*)0x13eb394;
    *(void**)(s + 0) = (void*)0x148a478;
    *(void**)(s + 8) = (void*)0x148a470;
    *(int*)(s + 0xc) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    cSPUIAnimator_ctor(s + 0x2c);
    *(int*)(s + 0x4c) = 0;
}

// ---------------------------------------------------------------------------
// 0x00edbe60  cScenarioEditModeScriptActsBarUI dtor
// ---------------------------------------------------------------------------
extern void cSPUIAnimator_dtor(void*);   // 0x007f8c20

// @ 0x00edbe60
void cScenarioEditModeScriptActsBarUI_dtor_body(char* s)
{
    *(void**)(s + 0) = (void*)0x148a478;
    *(void**)(s + 8) = (void*)0x148a470;
    char* c = *(char**)(s + 0x4c);
    if (c)
        (*(FnV)(*(void**)(*(char**)c + 0xc)))(c);
    cSPUIAnimator_dtor(s + 0x2c);
    int h = *(int*)(s + 0x18);
    if (h) {
        *(int*)(s + 0x18) = 0;
        EA_Messaging_RemoveHandler();
    }
    char* p = *(char**)(s + 0x14);
    if (p)
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    p = *(char**)(s + 0x10);
    if (p)
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    p = *(char**)(s + 0xc);
    if (p)
        (*(FnV)(*(void**)(*(char**)p + 8)))(p);
    *(void**)(s + 0) = (void*)0x13ec458;
    *(void**)(s + 8) = (void*)0x13eb394;
}

// ---------------------------------------------------------------------------
// 0x00edbef0  message handler
// ---------------------------------------------------------------------------
extern int  FUN_00f3be60(int);           // 0x00f3be60
extern void FUN_00edfda0(int, int*);     // 0x00edfda0
extern int  EA_Audio_GetSystemAT();      // 0x00a206f0
extern void SP_cSPUISpace_KillSetiEffects(int, int); // 0x00435ed0
extern int  FUN_006c0200();              // 0x006c0200
extern int  FUN_00ee31d0();              // 0x00ee31d0

// @ 0x00edbef0
int FUN_00edbef0(char* self, int id, int* p)
{
    if (id != 0x7c41ae9)
        return 0;
    int a = *(int*)((char*)p + 8);
    if (*(void**)(g_pMagic + 0x74) != 0) {
        char* q = (char*)self;
        int cmp = *(int*)(q + 0x44) ? (*(int*)(q + 0x44) + 4) : 0;
        if (*(int*)((char*)p + 0x10) == cmp) {
            int idx = ScenarioTutorials_GetActive();
            int r = FUN_00f3be60(idx);
            if (r) {
                FUN_00edfda0(r + 0x78, &a);
                char* snd = (char*)EA_Audio_GetSystemAT();
                if (snd)
                    (*(FnP)(*(void**)(*(char**)snd + 0x20)))(snd);
                SP_cSPUISpace_KillSetiEffects(0xe76c9b4f, 0);
                FUN_006c0200();
                return FUN_00ee31d0();
            }
        }
    }
    return 0;
}

// helper declared after use above
