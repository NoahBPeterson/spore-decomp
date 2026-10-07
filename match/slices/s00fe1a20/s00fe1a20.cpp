// Slice s00fe1a20: SP::cAppModeSpace::LoadStateMachine (Space mode input/UI state machine setup)
#include "types.h"

void __cdecl operator_delete__(void* p);   // 0xf47380

// A std-style vector<bool> (really 1-byte elements) living on the stack with a fixed 1-byte buffer.
struct BoolVec {
    char* b;
    char* e;
    char* cap;
    void __thiscall Construct(const bool* v);   // 0x57cc10
    void Destroy() { if (cap - b > 1 && b) operator_delete__(b); }
};

extern char g_vecBuf[2];     // 0x1667bac
extern bool g_falseConst;    // 0x13ec47c
void __cdecl BoolVec_DoInsertValue(void* pos, const void* value, int n);  // 0x11e0744 (vector<bool,fixed_vector_allocator>::DoInsertValue)

struct IGameInputManager {
    virtual void v0() {}
    virtual void v1() {}
    virtual void v2() {}
    virtual void v3() {}
    virtual void SetTriggerConfig(const char* name, int a, int b) = 0;  // +0x10
    virtual void v5() {}
    virtual void v6() {}
    virtual void v7() {}
    virtual void InstallStateMachine(void* sm, int a, int b) = 0;       // +0x20
};
struct ILocale {
    virtual void v0() {}
    virtual void v1() {}
    virtual void v2() {}
    virtual void v3() {}
    virtual void v4() {}
    virtual const void* GetLanguage() = 0;   // +0x14
};

IGameInputManager* __cdecl GameInputManager();   // 0xb3d250
ILocale* __cdecl GetLocaleManager();             // 0x67de40
bool __cdecl LanguageEquals(const void* str, const wchar_t* lit);  // 0x6ab760 (basic_string == wchar_t*)
void __cdecl DeclareMenuCommands();              // 0xd08930 (cCommunityEditor)

// The state-machine builder object that sits at frame +0x1c (cStateMachineBuilder; name guessed).
struct StateMachineBuilder {
    void __thiscall Init(void* tree);                       // 0xb198d0
    void __thiscall AddStateName(int idx, const char* s);   // 0xb1c080
    void __thiscall SetMachineName(const char* s);          // 0xb1b410
    void __thiscall AddTransition(int, int, int, int, unsigned, int, unsigned, int, int, int, BoolVec*, int); // 0xb1c8d0
};
struct CommandBase {
    void __thiscall Destroy();                // 0x83c750 EA::ArgScript::cCommandBase::~cCommandBase
};
struct NodeTree {
    void __thiscall Destroy(uint32_t root);   // 0xe4b990
};
struct BuilderCleanup {
    void __thiscall Destroy(uint32_t x);      // 0xb1b830
};

// @ 0xfe1a20
void __stdcall cAppModeSpace_LoadStateMachine(int mode)
{
    if (mode == 1)
        GameInputManager()->SetTriggerConfig("TriggerConfigSpaceFlight", 0, 1);
    else
        GameInputManager()->SetTriggerConfig("TriggerConfigSpaceGame", 0, 1);

    const char* wasd = "TriggerConfigWASD";
    if (LanguageEquals(GetLocaleManager()->GetLanguage(), L"fr-fr"))
        wasd = "TriggerConfigWASD_fr-fr";
    GameInputManager()->SetTriggerConfig(wasd, 0, 0);

    DeclareMenuCommands();

    uint32_t f[0x68 / 4];
    f[0x34 / 4] = 0;
    f[0x34 / 4] = (uint32_t)&f[0x34 / 4];
    f[0x38 / 4] = (uint32_t)&f[0x34 / 4];
    f[0x3c / 4] = 0;
    f[0x40 / 4] = 0;
    f[0x44 / 4] = 0;
    f[0x50 / 4] = (uint32_t)&f[0x50 / 4];
    f[0x54 / 4] = (uint32_t)&f[0x50 / 4];
    f[0x58 / 4] = 0;
    f[0x5c / 4] = 0;
    f[0x60 / 4] = 0;

    StateMachineBuilder& sm = *(StateMachineBuilder*)&f[0x1c / 4];
    sm.Init(&f[0x30 / 4]);
    sm.AddStateName(0, "Space: normal");
    sm.AddStateName(1, "Space: banning content");
    sm.AddStateName(2, "Space: inpsecting content");
    sm.SetMachineName("UIMachineCommunityEditor");

    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0x3ff, 0x3e8, 0x1007ae63, 1, 0x33cabf0, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0x40, 0x1b, -1, 0, 0x33cabf3, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 9, 0x3ff, 0x37ab944, -1, 0, 0x71d4dfc9, 0, 3, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(3, 9, 0x3ff, 0x3e86, -1, 0, 0, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 8, -1, 0, 0x2e81d88, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 1, 9, -1, 0, 0x62b45c3, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 9, -1, 0, 0x62b45bb, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 5, 0, 0x11, -1, 0, 0x62b4605, 1, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x11, -1, 0, 0x62b4605, 2, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0xdb, -1, 0, 0x62bfa72, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0xdd, -1, 0, 0x62bfa41, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x31, -1, 0, 0x6274486, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x32, -1, 0, 0x6274486, 1, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x33, -1, 0, 0x6274486, 2, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x34, -1, 0, 0x6274486, 3, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x35, -1, 0, 0x6274486, 4, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x36, -1, 0, 0x6274486, 5, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x37, -1, 0, 0x6274486, 6, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x38, -1, 0, 0x6274486, 7, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x39, -1, 0, 0x6274486, 8, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x30, -1, 0, 0x6274486, 9, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x4f, -1, 0, 0x33b7638, 1, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 5, 0, 0x4f, -1, 0, 0x33b7638, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0xb033b403, 0, 0x3056566, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0x436f315, 2, 0x4dd13d1, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0xd0036e08, 2, 0x5417b45, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0x137e8e0, 2, 0x54a7806, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0x244d3c0, 0, 0x57df7e0, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0x3ff, 0x3e8, 0x3275872, 0, 0x22d38ee, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0x3ff, 0x3ea, 0x3275872, 0, 0x22d38ee, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0x3ff, 0x3e8, 0x38cfb68, 0, 0x589c84b, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0x3ff, 0x3ea, 0x38cfb68, 0, 0x589c84b, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0, 0x3e8, 0, 0, 0x3065e0f, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(1, 1, 0x3ff, 0x3e8, -1, 0, 0x44ebe3f, -1, 1, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(1, 6, 0x3ff, -1, -1, 0, 0x456b08c, -1, 1, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(1, 4, 0x3ff, 0x1b, -1, 0, 0x44ecd59, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(2, 1, 0x3ff, 0x3e8, -1, 0, 0x62656dd, -1, 2, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(2, 6, 0x3ff, -1, -1, 0, 0x62656de, -1, 2, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(2, 4, 0x3ff, 0x1b, -1, 0, 0x62656df, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 6, 0x3ff, -1, 0xce9f6639, 0, 0x534052c, -1, -2, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 6, 0x3ff, -1, 0, 0, 0x534052c, -1, -2, 0, &v, 0);
        v.Destroy();
    }

    GameInputManager()->InstallStateMachine(&f[0x1c / 4], 0, 0);
    ((CommandBase*)&f[0x14 / 4])->Destroy();
    ((NodeTree*)&f[0x44 / 4])->Destroy(f[0x50 / 4]);
    ((BuilderCleanup*)&f[0x28 / 4])->Destroy(f[0x34 / 4]);
}
