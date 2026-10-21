// Slice s00ed9f10 -- 0x00ed9f10 .. 0x00edae80 (15 functions).
//
// SP::Simulator::cScenarioEditModeInputStrategy -- the scenario-editor input strategy: the
// IWindow message handlers, constructor/destructor, the editor-mode cursor/trigger setup,
// the cSPEditorNaming-derived naming widget, and the tutorial-entry helpers.
//
// The class multiply-inherits; the primary vtable lives at +0x00, the naming sub-object at
// +0x3c and a RefCount/IMsgHandler sub-object at +0x44 (which is why a couple of bodies
// adjust `this` by -0x44 or hand out interior pointers).
//
// Built with /O2 and the EA framework; every callee outside the slice is declared by address
// and called through extern vtable slots, exactly as the retail does.
//
// Flags: /O2 /MD /Gy /TP

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;

typedef void  (__thiscall *FnV)(void*);
typedef int   (__thiscall *FnI)(void*, int);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPI)(void*, int);
typedef void* (__thiscall *FnPII)(void*, int, int);
typedef void* (__thiscall *FnPIII)(void*, int, int, int);
typedef void* (__thiscall *FnPIIII)(void*, int, int, int, int);
typedef int   (__thiscall *FnII)(void*, int, int);
typedef int   (__thiscall *FnIII)(void*, int, int, int);
typedef void  (__thiscall *FnVI)(void*, int);

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern char* g_pMagic;                 // 0x016c7aa4
extern char* g_pStrategy;              // 0x015ad298
extern char* g_pStrategySelf;          // 0x015ad328
extern uint8_t g_bEditorMode;          // 0x016065f8
extern uint8_t g_modeObj[];            // 0x016065d8
extern uint32_t g_msgTable[];          // 0x0148a238  (0x7c bytes of message ids)
extern uint32_t g_menuTable[];         // 0x015ac448  (0x78 entries of 0xc bytes)

// The inner ResourceMan vtable call used by 0xedabf0 / 0xedad00 returns a bool in al.
struct ResourceMan {
    virtual void Unk00();
    virtual void Unk04();
    virtual void Unk08();
    virtual bool Load(const void* key, int, int, int, int, int);  // slot +0x0c
};

// ---------------------------------------------------------------------------
// externals with real names (addresses masked; declarations set conventions)
// ---------------------------------------------------------------------------
extern "C" int   EA_Audio_GetSystemAT();              // 0x00a206f0
extern "C" void* FUN_00b3d230();                      // 0x00b3d230
extern "C" void* FUN_00b3d240();                      // 0x00b3d240
extern "C" void* GameInputManager();                  // 0x00b3d250
extern "C" void  ScenarioTutorials_CloseWindow();     // 0x00efcae0
extern "C" void  __fastcall FUN_00b1b830(void*, void*); // 0x00b1b830
extern "C" void  __fastcall FUN_00e4b990(void*, void*);// 0x00e4b990
extern "C" void  __fastcall FUN_008014a0(void*);      // 0x008014a0
extern "C" void  __fastcall FUN_008014b0(void*);      // 0x008014b0
extern "C" void* FUN_0067de40();                      // 0x0067de40
extern "C" void* CursorManager();                     // 0x0067cab0
extern "C" void* MessageServer();                     // 0x0067dcc0
extern "C" void  RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
extern "C" int   cSPEditorNaming_HandleMessage(void*, int, void*); // 0x005bf9d0
extern "C" void  __fastcall cSPEditorNaming_dtor(void*);// 0x005c0070
extern "C" void  __fastcall Vec2b_Free(void*);        // 0x008e2b20
extern "C" int   IsModifierKeyDown(int);              // 0x008d2fb0
extern "C" void* SP_App();                            // 0x0067dd10
extern "C" int   cTerrainCameraController_KeysHeld(void*); // 0x00b0f9a0
extern "C" int   FUN_00809970();                      // 0x00809970
extern "C" void  FUN_00f01f40(uint32_t, void*);       // 0x00f01f40
extern "C" void  ScenarioTutorials_ReleaseInput();    // 0x00efc860
extern "C" void  ScenarioTutorials_CaptureInput();    // 0x00efc890
extern "C" void* GetRecorderState();                  // 0x00435e90
extern "C" void  cSPUISpace_KillSetiEffects(uint32_t, uint32_t); // 0x00435ed0
extern "C" void  SetGlobalProperty(uint32_t, float);  // 0x005ca880
extern "C" void  FUN_00ed4b60(void*);                 // 0x00ed4b60
extern "C" void  FUN_00ed76e0(void*, int);            // 0x00ed76e0
extern "C" void  FUN_00ed4840(void*);                 // 0x00ed4840
extern "C" void  FUN_00ed48b0(void*);                 // 0x00ed48b0
extern "C" void  FUN_00ed9b40(void*);                 // 0x00ed9b40
extern "C" void  FUN_00ed9b80(void*);                 // 0x00ed9b80
extern "C" void  FUN_00ed9bd0(void*);                 // 0x00ed9bd0
extern "C" void  FUN_00ed9c20(void*);                 // 0x00ed9c20
extern "C" void  FUN_00ed9c60(void*);                 // 0x00ed9c60
extern "C" void  FUN_00ee9260(void*);                 // 0x00ee9260
extern "C" void  cSPPaletteItem_GetPriority(void*);   // 0x00641770
extern "C" void  FUN_00f03ff0(int, void*, int);       // 0x00f03ff0
extern "C" void  FUN_00f01e60(void*);                 // 0x00f01e60
extern "C" void  ScenarioTutorials_TickStopwatch(int);// 0x00efe310
extern "C" void  ScenarioTutorials_SetTargetVisible(int); // 0x00efe4a0
extern "C" void  ScenarioTutorials_ToggleTarget(float);// 0x00efe510
extern "C" void  FUN_00e09bf0(void*);                 // 0x00e09bf0
extern "C" void* GetRefCounted18(void*);              // 0x00eebf80
extern "C" void  cUIBanningContent_ShowConfirmationDialog(int); // 0x00dd1aa0
extern "C" void  operator_delete(void*);              // 0x00f47380
extern "C" void  CursorTable_AddCursor(void*, void*, void*, void*, void*, void*); // 0x00802050
extern "C" int   Menu2_OnMenuItemSelected(void*, void*, void*); // 0x0081bef0
extern "C" void* Hashtable_DoFindNode(void*, const void*);      // 0x006ab760
extern "C" ResourceMan* ResourceMan_GetManager();     // 0x0067dcd0

// ===========================================================================
// class: SP::Simulator::cScenarioEditModeInputStrategy
// ===========================================================================
struct InputStrategy {
    void*    mVtbl;               // +0x00
    uint32_t mField04;            // +0x04
    void*    mList08;             // +0x08
    void*    mList0c;             // +0x0c
    void*    mList10;             // +0x10
    uint8_t  mFlag14;             // +0x14
    uint32_t mField18;            // +0x18
    uint32_t mField1c;            // +0x1c
    uint32_t mField20;            // +0x20
    void*    mList24;             // +0x24
    uint32_t mField28;            // +0x28
    uint32_t mField2c;            // +0x2c
    uint8_t  mFlag30;             // +0x30
    uint32_t mField34;            // +0x34
    uint32_t mMenu38;             // +0x38
    uint32_t mNaming3c;           // +0x3c  cSPEditorNaming sub-object
    uint32_t mSub44;              // +0x44  RefCount/IMsgHandler vtable
    uint32_t mField48;            // +0x48
    uint32_t mField4c;            // +0x4c
    uint8_t  mFlag50;             // +0x50
    uint8_t  mFlag51;             // +0x51
    void*    mMsgServer54;        // +0x54
    void*    mHandler58;          // +0x58
    uint32_t mHandlerId5c;        // +0x5c
    uint32_t mHandlerCount60;     // +0x60
    uint32_t mHandler64;          // +0x64
    uint32_t mCursorState6c;      // +0x6c
    uint32_t mEntry7c[4];         // +0x7c
    uint32_t mEntry8c[4][3];      // +0x8c .. +0xbb
    uint32_t mEntryBc[4];         // +0xbc
    uint32_t mHandlerCc;          // +0xcc
    uint32_t mHandlerD0;          // +0xd0
    uint32_t mHandlerD4;          // +0xd4
    uint32_t mHandlerD8;          // +0xd8
    uint32_t mHandlerDc;          // +0xdc

    InputStrategy* FUN_00edaa80();
    void  FUN_00edab50();
    void  FUN_00eda9a0();
    void  FUN_00eda130();
    int   FUN_00eda2f0(uint32_t msg, void* data);
    int   FUN_00edae50(uint32_t msg, void* data);
    void  FUN_00edae80();
    void  FUN_00edaca0();
    void  FUN_00edad00();
    void  FUN_00edadd0();
    int   FUN_00eda6f0(uint32_t msg, void* data);
};

// The scenario recorder object at g_pMagic+0xd8; 0x00f04060 is its row-count thiscall.
struct Recorder { int FUN_00f04060(); };

// The input-strategy "self" on the input side of the class, derived from cSPEditorNaming.
struct NamingBase {
    int HandleMessage(uint32_t msg, void* data);      // 0x005bf9d0
};

// the free-standing entry 0x00ed9f10 (thiscall in ECX = the input-strategy object)
extern "C" int FUN_00ed9f10(void* self, void* a, void* b);

// ===========================================================================
// 0x00ed9f10 -- toggle the scenario-edit "trigger config" state for a palette item.
// ===========================================================================
// @ 0x00ed9f10
extern "C" int FUN_00ed9f10(void* self, void* a, void* b)
{
    (void)self; (void)a;
    if (!EA_Audio_GetSystemAT())
        return 0;
    uint32_t* pmsg = (uint32_t*)b;
    if (!pmsg)
        return 0;
    void* obj = (void*)*pmsg;
    if (!obj)
        return 0;
    void** vt = *(void***)obj;
    void* r = ((FnPI)vt[0xc / 4])(obj, 0x31e56741u);
    if (!r)
        return 0;
    if (*(uint32_t*)((char*)r + 0x50) != 0xb1b104u)
        return 0;
    char* sub = (char*)r + 0x4c;
    uint32_t* rc = (uint32_t*)(sub + 4);
    if (*rc != 0)
        *rc -= 1;
    *pmsg = 0;
    return 1;
}

// ===========================================================================
// 0x00eda130 -- install the editor-mode cursors, triggers and message filters.
// ===========================================================================
// @ 0x00eda130
void InputStrategy::FUN_00eda130()
{
    char* self = (char*)this;
    char* si = (self != 0) ? (self + 0x3c) : (char*)0;
    void** in = (void**)FUN_00b3d230();
    ((FnI)(*(void***)in)[0x38 / 4])(in, 1);
    void** gim = (void**)GameInputManager();
    ((FnPIII)(*(void***)gim)[0x10 / 4])(gim, (int)"TriggerConfigScenarioEdit", 0, 1);
    void* fr = ((FnPI)(*(void***)gim)[0x14 / 4])(gim, 0x13f9b6c);   // L"fr-fr"
    void* found = Hashtable_DoFindNode(fr, (const void*)0x13f9b6c);
    void* name = found ? (void*)0x148a394 : (void*)0x1477770;
    ((FnPIII)(*(void***)gim)[0x10 / 4])(gim, (int)name, 0, 0);
    ((FnPI)(*(void***)gim)[0x3c / 4])(gim, (int)"UIMachineScenarioEdit");
    void* cm = CursorManager();
    CursorTable_AddCursor(cm, (void*)0x747d67b, (void*)0x13f9b6c, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x747d67c, (void*)0x13f9b48, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x7e4330b, (void*)0x148a358, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x7e4330c, (void*)0x148a334, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0xe84563d4u, (void*)0x148a30c, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0xf728e452u, (void*)0x148a2e4, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x7391920bu, (void*)0x148a2bc, (void*)1, 0, 0);

    char* handler = (self != 0) ? (self + 0x44) : (char*)0;
    void* srv = MessageServer();
    *(void**)(self + 0x54) = srv;
    *(void**)(self + 0x58) = handler;
    *(uint32_t*)(self + 0x5c) = (uint32_t)g_msgTable;
    *(uint32_t*)(self + 0x60) = 0x1f;
    *(uint32_t*)(self + 0x64) = 0;
    if (srv && handler) {
        for (unsigned off = 0; off < 0x7c; off += 4)
            ((FnII)(*(void***)srv)[0x24 / 4])(srv, (int)handler, (int)g_msgTable[off / 4]);
    }

    void** b = (void**)FUN_00b3d240();
    uint32_t local = 0;
    ((FnII)(*(void***)b)[0x2c / 4])(b, (int)&local, 1);
    if (si && *(uint32_t*)(si - 4) != 0)
        operator_delete(si);
}

// ===========================================================================
// 0x00eda2f0 -- the primary message switch (IWindow::HandleMessage override).
// ===========================================================================
// @ 0x00eda2f0
int InputStrategy::FUN_00eda2f0(uint32_t msg, void* data)
{
    char* self = (char*)this;
    char* g = g_pStrategy;
    int allow = 1;
    if ((g_bEditorMode == 0) || (((FnP)(*(void***)g)[0x38 / 4])(g) != 0)) {
        allow = 0;
    } else {
        if ((IsModifierKeyDown(1000) != 0) || (IsModifierKeyDown(0x3ea) != 0) ||
            (IsModifierKeyDown(0x3e9) != 0)) {
            allow = 0;
        } else {
            void** app = (void**)SP_App();
            void* cam = ((FnP)(*(void***)app)[0x50 / 4])(app);
            void* sub = ((FnP)(*(void***)cam)[0x38 / 4])(cam);
            if (sub) {
                void* q = ((FnPI)(*(void***)sub)[0xc / 4])(sub, 0x11966ed);
                if (q)
                    allow = (cTerrainCameraController_KeysHeld(q) == 0);
            }
        }
    }

    switch (msg) {
    case 0x101:
        if (allow && *(void**)(g_pMagic + 0x14))
            FUN_00ed76e0(*(void**)(g_pMagic + 0x14), 2);
        return 1;
    case 0x106:
        if (allow && *(void**)(g_pMagic + 0x14))
            FUN_00ed4b60(*(void**)(g_pMagic + 0x14));
        return 1;
    case 0x238de9c:
        *(uint8_t*)(self + 0x51) = 1;
        return 1;
    case 0x3a127dc:
        if ((*(uint32_t*)((char*)data + 8) == 0x3a129ee) &&
            (*(uint32_t*)((char*)data + 0x10) == *(uint32_t*)(self + 0x6c))) {
            *(uint32_t*)(self + 0x6c) = 0;
            SetGlobalProperty(0x8dff6314u, 0.0f);
        }
        return 1;
    case 0x44eaa93:
    case 0x452e0ca:
        GetRecorderState();
        cSPUISpace_KillSetiEffects(0xe76c9b4fu, 0);
        FUN_00ed9b80(self);
        return 1;
    case 0x522f9cd:
        FUN_00ed9f10(self, 0, data);
        return 1;
    case 0x522f9ce:
        FUN_00ed9b40(self);
        return 1;
    case 0x620222b:
    case 0x620271c:
    case 0x62663dd:
        FUN_00ed9bd0(self);
        return 1;
    case 0x24ce123:
        if (g == g_pStrategySelf)
            ScenarioTutorials_ReleaseInput();
        return 1;
    case 0x24ce124:
        if ((FUN_00809970() == 0) && (g == g_pStrategySelf))
            FUN_00f01f40(0x24ce124, data);
        return 1;
    case 0x411e1e8d:
        if ((FUN_00809970() == 0) && (g == g_pStrategySelf))
            ScenarioTutorials_CaptureInput();
        return 1;
    case 0x7561116:
        return 1;
    case 0xf3327645:
        FUN_00ed9b80(self);
        return 1;
    case 0xc9d86390:
        if (allow) {
            FUN_00ed4840(g_modeObj);
            GetRecorderState();
            cSPUISpace_KillSetiEffects(0x5416f867u, 0);
            FUN_00ed9c20(g_modeObj);
            cSPPaletteItem_GetPriority(*(void**)(g_pMagic + 0x14));
            FUN_00ee9260(0);
        }
        return 1;
    case 0xc9d86391:
        if (allow) {
            FUN_00ed48b0(g_modeObj);
            GetRecorderState();
            cSPUISpace_KillSetiEffects(0x370d9c35u, 0);
            FUN_00ed9c60(g_modeObj);
            cSPPaletteItem_GetPriority(*(void**)(g_pMagic + 0x14));
            FUN_00ee9260(0);
        }
        return 1;
    case 0xc9d86392:
    case 0xc9d86393:
    case 0xc9d86394:
    case 0xc9d86395:
    case 0xc9d86396:
        if (allow)
            ((FnV)(*(void***)g)[msg - 0xc9d86392 + 1])(g);
        return 1;
    default:
        return 0;
    }
}

// ===========================================================================
// 0x00eda6f0 -- message handler of the +0x44 sub-object (derived handler).
// ===========================================================================
// @ 0x00eda6f0
int InputStrategy::FUN_00eda6f0(uint32_t msg, void* data)
{
    InputStrategy* self = (InputStrategy*)((char*)this - 0x44);
    if (self->FUN_00eda2f0(msg, data))
        return 1;

    void** d = (void**)data;
    void* q1 = ((FnP)(*(void***)d)[0x10 / 4])(d);
    void* e = ((FnPI)(*(void***)q1)[0x1c / 4])(q1, 0);
    void* o1;
    if ((*(uint8_t*)((char*)e + 0x10) & 0x30) != 0)
        o1 = *(void**)e;
    else if (*(uint16_t*)((char*)e + 0x12) != 0)
        o1 = e;
    else
        o1 = 0;
    uint32_t v17f = 0;
    if (o1)
        v17f = (uint32_t)((FnPI)(*(void***)o1)[0xc / 4])(o1, 0x17f243b);

    void* e1 = ((FnPI)(*(void***)q1)[0x1c / 4])(q1, 1);
    int ebp = *(int*)e1;
    void* e4 = ((FnPI)(*(void***)q1)[0x1c / 4])(q1, 4);
    void* o4;
    if ((*(uint8_t*)((char*)e4 + 0x10) & 0x30) != 0)
        o4 = *(void**)e4;
    else if (*(uint16_t*)((char*)e4 + 0x12) != 0)
        o4 = e4;
    else
        o4 = 0;
    float f10 = *(float*)((char*)o4 + 8);
    void* q2 = ((FnP)(*(void***)d)[0x14 / 4])(d);
    void* esi = ((FnPI)(*(void***)q2)[0x1c / 4])(q2, 0);

    switch (msg) {
    case 0x25db76a: ScenarioTutorials_ToggleTarget(f10); return 1;
    case 0x25db76b:
        if (ebp == 6) { FUN_00f01e60((void*)v17f); return 1; }
        ScenarioTutorials_TickStopwatch(ebp == 4);
        return 1;
    case 0x25db76c: ScenarioTutorials_SetTargetVisible(ebp == 4); return 1;
    case 0x62663dc: FUN_00e09bf0((void*)v17f); return 1;
    case 0x7438ac6: ((FnII)(*(void***)self)[0x14 / 4])(self, ebp, v17f); return 1;
    case 0x7438ac7: {
        int r = ((FnII)(*(void***)self)[0x2c / 4])(self, ebp, v17f);
        if (r == 0) { *(uint32_t*)esi = 2; return 1; }
        if (r == 2) { *(uint32_t*)esi = 1; return 1; }
        return 1;
    }
    case 0x7478fb7:
        if (ebp == 1) {
            if (!((FnI)(*(void***)self)[0x24 / 4])(self, (int)v17f))
                *(uint32_t*)esi = 2;
            return 1;
        }
        if (ebp == 0) {
            ((FnV)(*(void***)self)[0x28 / 4])(self);
            return 1;
        }
        return 1;
    case 0x7da2d5a: {
        if (v17f == 0) return 0;
        uint32_t* r = (uint32_t*)GetRefCounted18((void*)v17f);
        if (!r) return 1;
        if (*r == 0xfffffffeu) return 1;
        uint32_t id = *r;
        void* srv = MessageServer();
        ((FnII)(*(void***)srv)[0x14 / 4])(srv, (int)&id, 0x7465518);
        return 1;
    }
    case 0xb332763d:
        cUIBanningContent_ShowConfirmationDialog((int)v17f);
        return 1;
    default:
        return 0;
    }
}

// ===========================================================================
// 0x00eda9a0 -- close the naming window and drop the game-input capture.
// ===========================================================================
// @ 0x00eda9a0
void InputStrategy::FUN_00eda9a0()
{
    char* self = (char*)this;
    ScenarioTutorials_CloseWindow();
    uint32_t h = *(uint32_t*)(self + 0x54);
    if (h) {
        *(uint32_t*)(self + 0x54) = 0;
        RemoveHandler((void*)h, *(void**)(self + 0x58), *(void**)(self + 0x5c),
                      *(void**)(self + 0x60), *(void**)(self + 0x64));
    }
    void** gim = (void**)GameInputManager();
    uint8_t local[0x38];
    void* l1 = local;
    void* l2 = local + 0x1c;
    *(void**)(local + 0x00) = l1;
    *(void**)(local + 0x04) = l1;
    *(void**)(local + 0x1c) = l2;
    *(void**)(local + 0x20) = l2;
    ((FnIII)(*(void***)gim)[0x20 / 4])(gim, (int)local, 0, 0);
    FUN_00e4b990(local + 0x1c, *(void**)(local + 0x1c));
    FUN_00b1b830(local, *(void**)(local + 0x04));
    char* si = (this != 0) ? (self + 0x3c) : (char*)0;
    void** b = (void**)FUN_00b3d230();
    ((FnI)(*(void***)b)[0x40 / 4])(b, (int)si);
}

// ===========================================================================
// 0x00edaa80 -- constructor.
// ===========================================================================
// @ 0x00edaa80
InputStrategy* InputStrategy::FUN_00edaa80()
{
    char* self = (char*)this;
    *(void**)(self + 0x00) = (void*)0x14771e0;
    *(uint32_t*)(self + 0x0c) = 0;
    *(uint32_t*)(self + 0x10) = 0;
    *(uint32_t*)(self + 0x14) = 0;
    char* e8 = self + 8;
    *(void**)(e8) = e8;
    *(void**)(self + 0x0c) = e8;
    *(uint32_t*)(self + 0x10) = 0;
    *(uint8_t*)(self + 0x14) = 0;
    *(uint32_t*)(self + 0x18) = 0;
    *(uint32_t*)(self + 0x28) = 0;
    char* e24 = self + 0x24;
    *(void**)(e24 + 8) = 0;
    *(void**)(e24 + 0x0c) = 0;
    char* edi = self + 0x3c;
    *(void**)(e24) = e24;
    *(void**)(self + 0x28) = e24;
    *(uint32_t*)(self + 0x2c) = 0;
    *(uint8_t*)(self + 0x30) = 0;
    *(uint32_t*)(self + 0x34) = 0;
    FUN_008014a0(edi);
    *(void**)(self + 0x44) = (void*)0x13eb384;
    *(void**)(self + 0x4c) = 0;
    *(void**)(self + 0x48) = (void*)0x13ec458;
    *(uint8_t*)(self + 0x50) = 0;
    *(uint8_t*)(self + 0x51) = 0;
    *(void**)(self + 0x00) = (void*)0x148a40c;
    *(void**)(edi + 0) = (void*)0x148a3f4;
    *(void**)(self + 0x44) = (void*)0x148a3e4;
    *(void**)(self + 0x48) = (void*)0x148a3d4;
    *(uint32_t*)(self + 0x54) = 0;
    *(uint32_t*)(self + 0x58) = 0;
    *(uint32_t*)(self + 0x5c) = 0;
    *(uint32_t*)(self + 0x60) = 0;
    *(uint32_t*)(self + 0x64) = 0;
    *(uint32_t*)(self + 0x6c) = 0;
    return this;
}

// ===========================================================================
// 0x00edab50 -- destructor body.
// ===========================================================================
// @ 0x00edab50
void InputStrategy::FUN_00edab50()
{
    char* self = (char*)this;
    char* edi = self + 0x3c;
    *(void**)(self + 0x00) = (void*)0x148a40c;
    *(void**)(edi + 0) = (void*)0x148a3f4;
    *(void**)(self + 0x44) = (void*)0x148a3e4;
    *(void**)(self + 0x48) = (void*)0x148a3d4;
    uint32_t h = *(uint32_t*)(self + 0x54);
    if (h) {
        *(uint32_t*)(self + 0x54) = 0;
        RemoveHandler((void*)h, *(void**)(self + 0x58), *(void**)(self + 0x5c),
                      *(void**)(self + 0x60), *(void**)(self + 0x64));
    }
    *(void**)(self + 0x48) = (void*)0x13ec458;
    *(void**)(self + 0x44) = (void*)0x13eb394;
    FUN_008014b0(edi);
    *(void**)(self + 0x00) = (void*)0x14771e0;
    char* esi = self + 4;
    FUN_00e4b990(esi + 0x1c, *(void**)(esi + 0x28));
    FUN_00b1b830(esi, *(void**)(esi + 0x0c));
}

// ===========================================================================
// 0x00edabf0 -- load a scenario-editor resource by index.  Returns success.
// ===========================================================================
// @ 0x00edabf0
extern "C" unsigned char FUN_00edabf0(uint32_t idx)
{
    char* t = *(char**)(*(char**)(g_pMagic + 0x74) + 0x10);
    struct { uint32_t a; uint32_t b; uint32_t c; } key;
    key.a = *(uint32_t*)(t + 8);
    key.b = *(uint32_t*)(t + 0xc);
    uint32_t x = *(uint32_t*)(t + 0x10);
    uint32_t y = ((idx + 1) ^ x) & 0xff;
    key.c = y ^ x;
    key.b = 0x2f7d0004;
    ResourceMan* m = ResourceMan_GetManager();
    return (unsigned char)m->Load(&key, 0, 0, 0, 0, 0);
}

// ===========================================================================
// 0x00edac50 -- menu-item availability predicate.
// ===========================================================================
// @ 0x00edac50
extern "C" int FUN_00edac50(uint32_t idx)
{
    return FUN_00edabf0(idx) ? -3 : -2;
}

// ===========================================================================
// 0x00edac70 -- "current entry" count query.
// ===========================================================================
// @ 0x00edac70
extern "C" int FUN_00edac70(uint32_t idx)
{
    Recorder* rg = *(Recorder**)(g_pMagic + 0xd8);
    int n = rg->FUN_00f04060();
    if (n > 0)
        return n - 1;
    return (idx != 0) ? -1 : -2;
}

// ===========================================================================
// 0x00edaca0 -- dispatch the highlighted menu item to the popup-menu window.
// ===========================================================================
// @ 0x00edaca0
void InputStrategy::FUN_00edaca0()
{
    char* self = (char*)this;
    void* mgr = *(void**)(g_pMagic + 0x74);
    if (!mgr)
        return;
    uint32_t code = (uint32_t)((FnP)(*(void***)mgr)[8 / 4])(mgr);
    int n = (int)(*(uint32_t*)(self + 0x40) - *(uint32_t*)(self + 0x3c)) >> 2;
    if ((unsigned)n <= 0)
        return;
    int i = 0, off = 0;
    int limit = (int)(*(uint32_t*)(self + 0x40) - *(uint32_t*)(self + 0x3c)) >> 2;
    for (;;) {
        if ((unsigned)off >= 0x78)
            return;
        if (*(uint32_t*)((char*)g_menuTable + off) == code) {
            uint32_t item = *(uint32_t*)(*(uint32_t*)(self + 0x3c) + i * 4);
            Menu2_OnMenuItemSelected(*(void**)(self + 0x38), 0, (void*)item);
            return;
        }
        ++i;
        off += 0xc;
        if ((unsigned)i >= (unsigned)limit)
            return;
    }
}

// ===========================================================================
// 0x00edad00 -- rebuild the four tutorial entries.
// ===========================================================================
// @ 0x00edad00
void InputStrategy::FUN_00edad00()
{
    char* self = (char*)this;
    for (int i = 0; i < 4; ++i) {
        *(uint32_t*)(self + 0x8c + i * 0xc) = 0;
        char* e = self + 0x8c + i * 0xc;
        *(uint32_t*)(e + 4) = 0;
        *(uint32_t*)(e + 8) = 0;

        char* t = *(char**)(*(char**)(g_pMagic + 0x74) + 0x10);
        uint8_t ok = 0;
        if (*(int*)(t + 0x68 + i * 4) == 1) {
            struct { uint32_t a; uint32_t b; uint32_t c; } key;
            key.a = *(uint32_t*)(t + 8);
            key.c = (((i + 1) ^ *(uint32_t*)(t + 0x10)) & 0xff) ^ *(uint32_t*)(t + 0x10);
            key.b = 0x2f7d0004;
            ResourceMan* m = ResourceMan_GetManager();
            ok = (uint8_t)m->Load(&key, 0, 0, 0, 0, 0);
        }
        *(uint32_t*)(self + 0x7c + i * 4) = (ok == 0) ? 0xffffffffu : 0xfffffffdu;
        *(uint32_t*)(self + 0xbc + i * 4) = (ok == 0) ? 3u : 1u;
        if (i == 0 && ok == 0) {
            *(uint32_t*)(self + 0x7c) = 0xfffffffeu;
            *(uint32_t*)(self + 0xbc) = 0;
        }
    }
}

// ===========================================================================
// 0x00edadd0 -- bind the tutorial entries to the current recorder rows.
// ===========================================================================
// @ 0x00edadd0
void InputStrategy::FUN_00edadd0()
{
    char* self = (char*)this;
    Recorder* rg = *(Recorder**)(g_pMagic + 0xd8);
    int n = rg->FUN_00f04060();
    if (n <= 0)
        return;
    int* p = (int*)(*(int*)(*(int*)(g_pMagic + 0x74) + 0x10) + 0x68);
    int i = 0;
    do {
        if (*p != 0 && *p != 3)
            return;
        ++i;
        ++p;
    } while (i < 4);

    i = 0;
    char* dst = self + 0x8c;
    uint32_t* idx = (uint32_t*)(self + 0x7c);
    do {
        if (i < n) {
            *idx = (uint32_t)i;
            FUN_00f03ff0(i, dst, 0);
        }
        ++i;
        ++idx;
        dst += 0xc;
    } while (i < 4);
}

// ===========================================================================
// 0x00edae50 -- HandleMessage (the class's naming-widget override).
// ===========================================================================
// @ 0x00edae50
int InputStrategy::FUN_00edae50(uint32_t msg, void* data)
{
    char* self = (char*)this;
    if (msg == 0x7e1e46du)
        ((InputStrategy*)(self - 4))->FUN_00edad00();
    return ((NamingBase*)this)->HandleMessage(msg, data);
}

// ===========================================================================
// 0x00edae80 -- destructor for the cSPEditorNaming-derived naming widget.
// ===========================================================================
// @ 0x00edae80
void InputStrategy::FUN_00edae80()
{
    char* self = (char*)this;
    *(void**)(self + 0x00) = (void*)0x148a440;
    *(void**)(self + 0x04) = (void*)0x148a430;
    *(void**)(self + 0x08) = (void*)0x148a420;
    if (*(uint32_t*)(self + 0xcc) != 0) {
        uint32_t h = *(uint32_t*)(self + 0xcc);
        *(uint32_t*)(self + 0xcc) = 0;
        RemoveHandler((void*)h, *(void**)(self + 0xd0), *(void**)(self + 0xd4),
                      *(void**)(self + 0xd8), *(void**)(self + 0xdc));
    }
    Vec2b_Free(self + 0x3c);
    void* p = *(void**)(self + 0x38);
    if (p) {
        void* f = ((void**)*(void***)p)[4 / 4];
        ((FnV)f)(p);
    }
    cSPEditorNaming_dtor(self);
}
