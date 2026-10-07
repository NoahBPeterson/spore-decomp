#include "types.h"

// Slice s005dec10: SP::cSPEditorUI dialog/save helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.

struct Layout {
    void* FindWindowByID(int, int);   // 0x8105b0
    char pad[0x18];
};
struct Widget {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual char Slot10();         // +0x28
};
__forceinline Widget* FindWindowRaw(void* base, int id)
{
    Widget* w = (Widget*)((Layout*)((char*)base + 0x14))->FindWindowByID(id, 1);
    if (!w)
        w = (Widget*)((Layout*)((char*)base + 0x2c))->FindWindowByID(id, 1);
    return w;
}
void __cdecl FUN_004a88d0(int);

// ---------------------------------------------------------------------------------------------
struct EditorFrame {
    char pad[0xcc];
    int mcc;              // +0xcc
    void FUN_005df470(int a, int b);
    void FUN_005df8d0();
};
// @ 0x005df8d0
void EditorFrame::FUN_005df8d0()
{
    mcc = 0x103;
    FUN_005df470(0x103, 1);
}

// ---------------------------------------------------------------------------------------------
struct DialogTarget { void DoDialogEnd(int code); };
struct EditorFrame2 {
    char pad[4];
    DialogTarget* mpTarget;   // +0x04
    void FUN_005dfb30(int a, int b);
};
// @ 0x005dfb30
void EditorFrame2::FUN_005dfb30(int a, int b)
{
    mpTarget->DoDialogEnd(b);
}

// ---------------------------------------------------------------------------------------------
struct EditorUI2 {
    char pad[0x5c];
    void* m5c;                // +0x5c
    char pad60[0x18];
    void* m78;                // +0x78
    char pad7c[0x50];
    int mcc;                  // +0xcc
    void FUN_005df470(int a, int b);
    void DoSaveAndExit();
};
// @ 0x005dfb40  SP::cSPEditorUI::DoSaveAndExit (complete; see nonmatching.txt)
void EditorUI2::DoSaveAndExit()
{
    void* a = m5c;
    char* b = *(char**)((char*)a + 0x7c);
    char* c = *(char**)(b + 0xc);
    if (c[0x44]) {
        void* base = *(void**)((char*)a + 0x78);
        Widget* w = FindWindowRaw(base, 0x3f67620);
        if ((w->Slot10() & 1) != 0)
            return;
    }
    FUN_004a88d0(0xf515d2c3);
    mcc = 0x102;
    FUN_005df470(0x102, 1);
}

// ---------------------------------------------------------------------------------------------
// Full editor UI object (retail offsets; they differ from the dev PDB by a shift).
struct Key12 { uint32_t a, b, c; };
struct Key16 { uint32_t a, b, c, d; };

struct Res {
    virtual void v0();
    virtual void Release();           // +4
    virtual void v2();
    virtual void* QueryInterface(uint32_t id);   // +0xc
};
struct EditorRes { char pad[0x18]; uint32_t mType; };
struct ResMgr {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const Key12* key, Res** out, int, int, int, int);   // +0xc
};
struct MsgServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void Post(uint32_t id, int, int, int);      // +0x18
};
struct ConfigMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void SetValue(uint32_t id, int v);          // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void Commit();                              // +0x3c
};
struct AudioSys {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual uint32_t GetValue();                        // +0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13();
    virtual void Begin(uint32_t id);                    // +0x38
    virtual void v15();
    virtual void SetParam(uint32_t id, uint32_t v);     // +0x40
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21();
    virtual void End();                                 // +0x58
};
struct WinObj {
    virtual void v0();
    virtual void Release();           // +4
    char pad[0x18];
    WinObj(void* a);                  // FUN_005fe600
    bool FUN_005fe5f0();
    uint32_t GetAccessFlags();        // 0xff0420
    uint32_t FUN_006c0200();
    void FUN_005fea60(uint32_t a, uint8_t b);
    void FUN_005fe6c0();
};
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);   // 0xf473a0
// AutoRefCount<IWinText>::operator=
struct RefPtr {
    WinObj* p;
    void assign(WinObj* o);   // 0xb5f950
};

struct AppBase {
    char pad[0x4b1];
    char m4b1;
    int GetEditorSaveability();                         // 0x57aaa0
    void FUN_00572190(Key16* out);
    Key16* FUN_00572160(Key16* out);
    Key16* GetMask(Key16* out);                         // 0x57a960
    void FUN_005724a0();
    bool FUN_00574d60();
    bool FUN_00573070(EditorRes* r);
    bool FUN_00573050();
    void FUN_00573fb0();
    void SetCurrentConfig(uint32_t cfg, Key12 key);   // 0x579720
    void LoadModelKey(const Key12* k, Key16 k16, int f);   // 0x58cee0
    void LoadModel(int a, int b, int c);                   // 0x58a350
    void FUN_005721b0(Key16 a, Key16 b);
};

ResMgr* __cdecl GetManager();   // 0x67dcd0
MsgServer* __cdecl GetMessageServer();   // 0x67dcc0
ConfigMgr* __cdecl GetConfigManager();   // 0x67dd30
AudioSys* __cdecl GetSystemAT();   // 0xa206f0
uint32_t __cdecl RemapTypeId(uint32_t t);   // 0x432f10
EditorRes* __cdecl interface_cast_EditorRes(Res** r);   // 0x421eb0
struct Obj67 { void FUN_0067c830(); };
Obj67* __stdcall FUN_0067cac0(uint32_t id);
struct Obj45 { void FUN_0045ae10(); };
Obj45* __stdcall FUN_00401050(uint32_t id, int x);
void __cdecl CalloutMessageBox(void* where, const Key12* key);   // 0x809db0
bool __cdecl FUN_004f3d60(Key16 a, Key16 b);
void __cdecl FUN_004a88d0_(uint32_t id);

extern Key12 g1519958, g1519964, g1519970, g151997c, g1519988, g15199a0, g15199b8, g15199c4,
    g15199dc, g15199e8, g15199f4, g1519a0c, g1519a3c, g15199d0, g15199ec, g1519994, g1519a00;

struct EditorResOps : EditorRes { void FUN_004bac30(Key16* out, Key16 k, int f); };
void __cdecl AssetBrowserLaunch(uint32_t a, void* b, uint32_t c);
struct EUI {
    char pad0[0x5c];
    AppBase* app;                 // +0x5c
    char pad60[0x40];
    uint8_t ma0;                  // +0xa0
    char pada1[0x13];
    char mb4[8];                  // +0xb4 callout target
    Key12 mkey;                   // +0xbc
    uint32_t mc8;                 // +0xc8
    uint32_t mcc;                 // +0xcc
    uint8_t md0;                  // +0xd0
    char padd1[3];
    Key16 msaved;                 // +0xd4
    uint8_t me4;                  // +0xe4
    uint8_t me5;                  // +0xe5
    char pade6[2];
    RefPtr me8;                   // +0xe8
    uint8_t mec;                  // +0xec
    char paded[3];
    uint32_t mf0;                 // +0xf0
    uint8_t mf4;                  // +0xf4
    char padf5[3];
    uint32_t mf8;                 // +0xf8
    uint32_t mfc;                 // +0xfc

    void FUN_005dec10(uint32_t a);
    void FUN_005def30(uint32_t param);
    void FUN_005df470(uint32_t cmd, int b);
    bool FUN_005df8f0(Key12 key);
    bool FUN_005dc250(uint32_t cmd);
    void FUN_005dcaa0(uint32_t cmd, uint32_t flag);
    void FUN_005dca00(Key16 k);
    void FUN_005dc190(Key16 a, Key16 b, Key12 c);
    uint32_t FUN_005dd860(Key16 k);
    void FUN_005dd360(bool b);
    void FUN_005dc4d0(int a);
    void FUN_005dda30(int a);
    void FUN_005de9e0();
};

// @ 0x005dec10
void EUI::FUN_005dec10(uint32_t a)
{
    switch (a) {
    case 0x100: {
        ResMgr* mgr = GetManager();
        Res* res = 0;
        if (mgr && mgr->GetResource(&mkey, &res, 0, 0, 0, 0)) {
            EditorRes* er = interface_cast_EditorRes(&res);
            if (er) {
                uint32_t cfg = RemapTypeId(er->mType);
                if (md0 && app->FUN_00573070(er)) {
                    if (app->FUN_00573050()) {
                        app->SetCurrentConfig(cfg, mkey);
                    } else {
                        FUN_0067cac0(0xffc453c6)->FUN_0067c830();
                    }
                    if (res) res->Release();
                    return;
                }
            }
        }
        FUN_005dda30(0);
        Key16 tmp;
        Key16* k = app->FUN_00572160(&tmp);
        app->LoadModelKey(&mkey, *k, 1);
        FUN_00401050(0x3f1bf54, 0)->FUN_0045ae10();
        if (res) res->Release();
        return;
    }
    case 0x102:
        if (mec) {
            mc8 = 0x61c7098;
            WinObj* o = new ("Editor", 0, 0, 0, 0) WinObj(mb4);
            me8.assign(o);
            me8.p->FUN_005fea60(mf0, mf4);
            me8.p->FUN_005fe6c0();
        } else {
            app->LoadModel(1, 2, 1);
        }
        return;
    case 0x103:
        app->LoadModel(2, 2, 1);
        return;
    case 0x104:
        FUN_005de9e0();
        return;
    case 0x107:
        GetMessageServer()->Post(0x153c326, 0, 0, 0);
        return;
    }
}

// @ 0x005dee70  (handler subobject at +8; `this` here is the IHandler part)
struct HandlerSub {
    char pad[0xac];
    char mac[0x14];              // +0xac (= EUI +0xb4)
    uint32_t mc0;                // +0xc0 (= EUI +0xc8)
    uint32_t mc4;                // +0xc4 (= EUI +0xcc)
    bool HandleMessage(uint32_t msg, int data);
};
bool HandlerSub::HandleMessage(uint32_t msg, int data)
{
#define ui ((EUI*)((char*)this - 8))
    switch (msg) {
    case 0x44db12e:
        ui->FUN_005dd360(data != 0);
        return false;
    case 0x165e841:
        if (mc4) {
            if (!ui->FUN_005dc250(mc4)) {
                mc0 = g1519958.a;
                CalloutMessageBox(mac, &g1519958);
                return false;
            }
            ui->FUN_005dec10(mc4);
            return false;
        }
        return false;
    case 0x5b98f52:
    case 0x5b96086:
    case 0x5bd6378:
    case 0x5c5594a:
    case 0x5dd52c7:
        if (mc4 == 0x10a)
            mc4 = 0;
        return false;
    }
    return false;
}
#undef ui

// @ 0x005def30  SP::cSPEditorUI::DoDialogEnd
void EUI::FUN_005def30(uint32_t param)
{
    AudioSys* au = GetSystemAT();
    uint32_t v = au ? au->GetValue() : 0;
    au = GetSystemAT();
    if (au) {
        au->Begin(0x3475365);
        au->SetParam(0x3475381, 0xa03e74b2);
        au->SetParam(0x3475385, v);
        au->End();
    }
    switch (mc8) {
    case 0x61c7098:
        if (!me8.p)
            return;
        if (me8.p->FUN_005fe5f0()) {
            mcc = 0;
        } else {
            mf8 = me8.p->GetAccessFlags();
            mfc = me8.p->FUN_006c0200();
            app->LoadModel(0, 2, me5);
        }
        if (me8.p) {
            WinObj* o = me8.p;
            me8.p = 0;
            o->Release();
        }
        return;
    case 0x604fa6b:
    case 0x604fab1:
        if (param == 0x5107b17) {
            GetConfigManager()->SetValue(0x604a51a, 0);
            GetConfigManager()->Commit();
        }
        if (mc8 == 0x604fa6b) {
            mcc = 0x100;
            FUN_004a88d0_(0xa03e74b2);
            FUN_005dc4d0(0);
            return;
        }
        if (mc8 == 0x604fab1) {
            mcc = 0x105;
            FUN_004a88d0_(0xa03e74b2);
            AssetBrowserLaunch(0xdb184acb, this, 0x54acb9f1);
        }
        return;
    case 0x3b182dc3:
    case 0x9a24fbe5:
        mcc = 0;
        return;
    case 0x7b355311:
    case 0xa1520d7f:
    case 0xb129f37e:
    case 0xf207647f:
        if (param == 0x5107b1a)
            FUN_005dcaa0(mcc, me5);
        return;
    case 0x3a5ea067:
    case 0x5cd172a9:
    case 0xc6bdfccc:
    case 0xe6c74f99:
    case 0xf46fbea9:
        if (param == 0x5107b1a)
            FUN_005dec10(mcc);
        return;
    case 0x3cc9f2f3:
        FUN_005dec10(mcc);
        return;
    case 0xa2509b6a:
        if (param == 0x5107b19) {
            mcc = 0;
        } else if (param == 0x5107b1a) {
            app->FUN_00573fb0();
        }
        return;
    case 0x811778da:
        if (param == 0x5107b19) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 1;
            } else {
                FUN_005dcaa0(mcc, 1);
            }
        } else if (param == 0x5107b1a) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 0;
            } else {
                FUN_005dcaa0(mcc, 0);
            }
        }
        return;
    case 0x12b8ba66:
    case 0x8bf4d3f2:
    case 0x9d533cda:
    case 0xbe186a9a:
        if (param == 0x5107b17) {
            FUN_005dec10(mcc);
        } else if (param == 0x5107b19) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 1;
            } else {
                FUN_005dcaa0(mcc, 1);
            }
        } else if (param == 0x5107b1a) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 0;
            } else {
                FUN_005dcaa0(mcc, 0);
            }
        }
        return;
    case 0x48ee60f0:
    case 0x53830374:
    case 0x7c1ea6a4:
    case 0xb016b570:
    case 0xc2b30789:
    case 0xcf4c3d25:
    case 0xeb3bc709:
    case 0xebdc80d5: {
        uint8_t flag = 0;
        if (mc8 == 0xebdc80d5 || mc8 == 0xc2b30789 || mc8 == 0xcf4c3d25 || mc8 == 0xeb3bc709)
            flag = 1;
        if (param == 0x5107b17) {
            FUN_005dec10(mcc);
        } else if (param == 0x5107b1a) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = flag;
            } else {
                FUN_005dcaa0(mcc, flag);
            }
        }
        return;
    }
    }
}

// @ 0x005df470
void EUI::FUN_005df470(uint32_t cmd, int b)
{
    int sv = app->GetEditorSaveability();
    Key16 saved;
    app->FUN_00572190(&saved);
    mcc = cmd;
    me4 = 0;
    app->FUN_005724a0();
    Key12 loc;
    if (cmd != 0x103 && cmd != 0x107) {
        switch (sv) {
        case 1:
            msaved = saved;
            me4 = 1;
            // fall through
        case 0: {
            bool ok = app->FUN_00574d60();
            if (cmd == 0x101) {
                if (app->m4b1 != 0 || !ok) {
                    if (!me4) {
                        FUN_005dcaa0(0x101, 0);
                        return;
                    }
                    mc8 = FUN_005dd860(msaved);
                    me5 = 0;
                    return;
                }
                mc8 = g1519964.a;
                CalloutMessageBox(mb4, &g1519964);
                return;
            }
            if (ma0 == 0 && app->m4b1 == 0 && ok) {
                bool c = FUN_005dc250(cmd);
                loc = g1519a3c;
                if (!c) {
                    loc = g15199dc;
                    if (cmd != 0x100) {
                        loc = g1519a0c;
                        if (cmd != 0x104)
                            loc = g15199a0;
                    }
                }
            } else {
                if (FUN_005dc250(cmd)) {
                    if (!me4) {
                        FUN_005dcaa0(cmd, ok);
                        return;
                    }
                    mc8 = FUN_005dd860(msaved);
                    me5 = ok;
                    return;
                }
                if (!ok) {
                    loc = g15199c4;
                    if (cmd != 0x100) {
                        loc = g15199f4;
                        if (cmd != 0x104)
                            loc = g1519988;
                    }
                } else {
                    loc = g15199b8;
                    if (cmd != 0x100) {
                        loc = g15199e8;
                        if (cmd != 0x104)
                            loc = g151997c;
                    }
                }
            }
            mc8 = loc.a;
            CalloutMessageBox(mb4, &loc);
            return;
        }
        case 2:
            if (cmd != 0x101 && !FUN_005dc250(cmd)) {
                Key12 k;
                k = g1519994;
                if (cmd == 0x100) k = g15199d0;
                else if (cmd == 0x104) k = g1519a00;
                mc8 = k.a;
                Key16 tmp;
                Key16* m = app->GetMask(&tmp);
                FUN_005dc190(saved, *m, k);
                return;
            }
            FUN_005dca00(saved);
            mcc = 0;
            return;
        case 3:
            FUN_005dec10(cmd);
            return;
        case 4:
            if (cmd != 0x101 && !FUN_005dc250(cmd)) {
                FUN_005dec10(cmd);
                return;
            }
            FUN_005dca00(saved);
            mcc = 0;
            return;
        }
        return;
    }
    if (sv == 3 || sv == 4) {
        FUN_005dec10(cmd);
        return;
    }
    mc8 = g1519970.a;
    CalloutMessageBox(mb4, &g1519970);
}

// @ 0x005df8f0  SP::cAppModeEditorBase::HandleFileDrop
bool EUI::FUN_005df8f0(Key12 key)
{
    ResMgr* mgr = GetManager();
    Res* res = 0;
    md0 = 1;
    if (mgr && mgr->GetResource(&key, &res, 0, 0, 0, 0) && res) {
        EditorRes* er = (EditorRes*)res->QueryInterface(0x3c609f8);
        if (er) {
            Key16 tmp;
            Key16 out;
            Key16* k = app->FUN_00572160(&tmp);
            // FUN_004bac30(ecx=er, &out, *k, 1)
            ((EditorResOps*)er)->FUN_004bac30(&out, *k, 1);
            k = app->FUN_00572160(&tmp);
            if (!FUN_004f3d60(out, *k)) {
                Key16 z = { 0x4000000, 0, 0, 0 };
                app->FUN_005721b0(z, z);
                if (res) { res->Release(); }
                return false;
            }
            RemapTypeId(er->mType);
            if (!app->FUN_00573070(er)) {
                md0 = 0;
            } else if (!app->FUN_00573050()) {
                FUN_0067cac0(0xffc453c6)->FUN_0067c830();
                if (res) res->Release();
                return false;
            }
            mkey = key;
            mcc = 0x100;
            FUN_005df470(0x100, 1);
            if (res) res->Release();
            return true;
        }
    }
    Key16 z = { 0x4000000, 0, 0, 0 };
    app->FUN_005721b0(z, z);
    if (res) res->Release();
    return false;
}
