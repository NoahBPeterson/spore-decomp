// Slice s00b28da0 (batch gold7).  Region 0x00b28da0-0x00b2981a.
// SP::Simulator save-game bootstrap: rebuild the two simulator data vectors,
// then the full save-bootstrap (00b28ec0) and the reload/stats path (00b294c0).
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "s00b28da0.h"

// ---------------------------------------------------------------------------
// typed views of the (opaque) game objects the two big paths walk
// ---------------------------------------------------------------------------
struct HomeObj {                    // "player home planet" object
    uint8_t  pad00[0x2c];
    uint32_t m2c;                   // +0x02c  flags
    uint8_t  pad30[0x194 - 0x30];
    uint32_t m194;                  // +0x194  selected game-mode slot
};

struct PlanetIface {                // interface reached through PlanetModel+0x24
    virtual void     v00();
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual void     v2c();
    virtual void     v30();
    virtual void     v34();
    virtual void     v38();
    virtual void     v3c();
    virtual void     v40();
    virtual void     v44();
    virtual void     v48();
    virtual void     v4c();
    virtual void     v50();
    virtual void     v54();
    virtual void     v58();
    virtual void     v5c();
    virtual void     v60();
    virtual void     v64();
    virtual void     v68();
    virtual void     v6c();
    virtual void     v70();
    virtual void     v74();
    virtual void     v78();
    virtual void     v7c();
    virtual void     v80();
    virtual uint32_t v84();
};

struct PlanetObj {
    uint8_t        pad00[0x24];
    PlanetIface*   mp24;            // +0x24
};
typedef PlanetObj ForeignModel;

struct PropListIface {              // SP::cPropertyList (0x38 bytes)
    virtual uint32_t v00();
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual void     v2c(uint32_t src);
};

struct PropMgrIface {               // SP::PropertyManager
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34(void* list, uint32_t keyA, uint32_t keyB);
};

// ===========================================================================
// 0x00b28da0 - rebuild the simulator tribe / sim-object data vectors
// ===========================================================================
// @ 0x00b28da0
void __cdecl FUN_00b28da0(void* self)
{
    C710Owner* o = (C710Owner*)self;
    o->FUN_00c710e0();
    o->FUN_00c71100();

    NounMgr* nm = NounManager();
    GDVec* vec = (GDVec*)nm->GetGameDataVector((void*)&FUN_00cd7d10,
                                               (void*)&FUN_00d3d420,
                                               (void*)&FUN_00accbb0,
                                               (void*)&FUN_00b1e500,
                                               (void*)&g_18c6d19);
    int n = (int)(vec->mEnd - vec->mBegin);
    for (int i = 0; i < n; ++i)
    {
        TribeData* raw = (TribeData*)FUN_00f473a0(0x18, "Simulator", 0, 0, 0, 0);
        void* made = raw ? (void*)raw->Ctor(vec->mBegin[i]) : 0;
        o->FUN_00c710f0(made);
    }

    NounMgr* nm2 = NounManager();
    GDVec* vec2 = (GDVec*)nm2->GetGameDataVector((void*)&FUN_00b21080,
                                                 (void*)&FUN_00d3d420,
                                                 (void*)&FUN_00b236c0,
                                                 (void*)&FUN_00b1e500,
                                                 (void*)&g_18c816a);
    int n2 = (int)(vec2->mEnd - vec2->mBegin);
    for (int j = 0; j < n2; ++j)
    {
        SimObjData* raw = (SimObjData*)FUN_00f473a0(0x50, "Simulator", 0, 0, 0, 0);
        void* made = raw ? (void*)raw->Ctor(vec2->mBegin[j]) : 0;
        o->FUN_00c710b0(made);
    }

    void* v = FUN_010212f0();
    StarMgr* sm = StarManager();
    C4F030Obj* r = sm->FUN_00c4f030((uint32_t)v);
    r->FUN_00d056c0();
}

// ===========================================================================
// 0x00b28ec0 - save-game bootstrap: emit the "saving" wrap, apply the mode
// switch, build the eastl save path, run the FTP job, start the async save.
// ===========================================================================
// the "message wrap" object the original pushes as the message payload: two
// vtable pointers followed by the two payload dwords.
struct MsgWrapObj {
    void*    vtbl0;      // +0x00
    void*    vtbl1;      // +0x04
    uint32_t a;          // +0x08
    uint32_t b;          // +0x0c
};

// @ 0x00b28ec0
void __fastcall FUN_00b28ec0(void* self, void* dummy, const void* name, uint8_t flag)
{
    (void)self;
    (void)dummy;
    if (name == 0)
        return;
    if (((const wchar_t*)name)[0] == 0)
        return;

    // --- emit the "message begin" wrap (key 0x1a0219e) --------------------
    MsgWrapObj wrap;
    wrap.vtbl0 = g_vtblRefBaseA22b;
    wrap.vtbl1 = 0;
    wrap.a = 1;
    wrap.b = 0;
    void* ms = MessageServerv();
    {
        typedef void (__thiscall *TEmit)(void*, uint32_t, void*, uint32_t);
        TEmit emit = (TEmit)(*(void***)ms)[5];
        emit(ms, 0x1a0219e, &wrap, 0);
    }

    void* avatar = ((void* (__thiscall*)(void*))FUN_004df420v)(GetSetting9v());

    if (flag != 0)
    {
        HomeObj* home = (HomeObj*)((void* (*)(void))FUN_01021300)();
        if (home != 0)
        {
            void* key = FUN_00c30c60v();
            StarMgr* sm = StarManager();
            sm->FUN_00c4f030((uint32_t)key);
            FUN_00bb3750v();
            void* t = FUN_01021230v();
            (void)t;
            if (avatar != 0)
                FUN_00c8b570v(avatar);

            HomeObj* h2 = (HomeObj*)FUN_01021370v();
            uint32_t mode = GetCurrentGameMode();
            switch (mode)
            {
            case 0x1654c00:
                FUN_00c8b590v(0);
                h2->m194 = 0;
                break;
            case 0x1654c01:
                FUN_00c8b590v(1);
                h2->m194 = 1;
                break;
            case 0x1654c02:
                FUN_00c8b590v(2);
                h2->m194 = 2;
                FUN_00ae9790v();
                (void)h2;
                break;
            case 0x1654c04:
                FUN_00c8b590v(4);
                h2->m194 = 4;
                FUN_00ae9790v();
                (void)h2;
                break;
            case 0x1654c05:
                FUN_00c8b590v(5);
                h2->m194 = 5;
                break;
            }
            FUN_00baecc0v(0, flag);
            if (h2 != 0)
                ((void (__thiscall*)(void*))(*(void***)h2)[1])(h2);
        }
    }

    // --- build the eastl save path: <name>.tmp ---------------------------
    EWStr base;
    base.mBegin = 0;
    base.mEnd = 0;
    base.mCap = 0;
    base.range_initialize((const wchar_t*)name);
    EWStr ext;
    ext.mBegin = 0;
    ext.mEnd = 0;
    ext.mCap = 0;
    ext.range_initialize((const wchar_t*)&g_wstrLtmp);

    EWStr out;
    out.mBegin = 0;
    out.mEnd = 0;
    out.mCap = 0;
    EWStr* picked = (EWStr*)PathPickv(&out, &base, &ext);
    if (picked != &out)
        out.assign(picked->mBegin, picked->mEnd);
    if (out.mCap != 0 && out.mCap != out.mBegin)
        FUN_00f47380v(out.mBegin);

    // --- FTP job + achievements + the async handoff ----------------------
    void* job = (void*)FUN_00ecdba0v();
    if (job != 0)
    {
        FUN_00692ea0v();
        FUN_00b268a0v(0);
        void* cnt = FUN_00b3d230v();
        ((void (__thiscall*)(void*, uint32_t))(*(void***)cnt)[0x48 / 4])(cnt, 0);
        FUN_00675250v(0);
        FUN_006755c0v(0);
        if (GetCurrentGameMode() == 0x1654c00)
            FUN_00e5c4d0v(0);
        FUN_00693900v();
    }
    FUN_006b4840v();
}

// ===========================================================================
// 0x00b294c0 - reload / stats path: resolve the save name (defaulting to the
// global, sanitising path separators), rebuild the singleton + property list,
// then run the bootstrap and the GameModeSave.
// ===========================================================================
// @ 0x00b294c0
uint8_t __fastcall FUN_00b294c0(void* self, void* dummy, const void* name, uint8_t flag)
{
    (void)dummy;
    if (FUN_00baad00v() == 0)
        return 0;
    if (flag != 0 && FUN_00b282e0v(self) == 0)
        return 0;

    EWStr* defName = (EWStr*)&g_defName167df60;

    if (name == 0)
    {
        void* home = FUN_01021370v();
        EWStr* src = (EWStr*)FUN_00ecdba0v();
        if (src != defName)
            defName->assign(src->mBegin, src->mEnd);

        EWStr joined;
        joined.mBegin = 0;
        joined.mEnd = 0;
        joined.mCap = 0;
        void* picked = PathJoinv(&joined, defName, g_u__spo_15689a8);
        EWStr* r = (EWStr*)picked;
        if (r != defName)
            defName->assign(r->mBegin, r->mEnd);
        if (joined.mCap != 0 && joined.mCap != joined.mBegin)
            FUN_00f47380v(joined.mBegin);
        (void)home;
    }
    else
    {
        const wchar_t* p = (const wchar_t*)name;
        while (*p != 0)
            ++p;
        defName->assign((uint32_t*)name, (uint32_t*)p);
    }

    // backslash / slash  ->  underscore  in the resolved save name
    uint32_t len = (uint32_t)(defName->mEnd - defName->mBegin);
    for (uint32_t i = 0; i < len; ++i)
    {
        wchar_t ch = (wchar_t)defName->mBegin[i];
        if (ch == L'\\' || ch == L'/')
            defName->mBegin[i] = (uint32_t)L'_';
    }

    if (flag != 0)
    {
        void* ms = MessageServerv();
        typedef void (__thiscall *TEmit)(void*, uint32_t, void*, uint32_t);
        ((TEmit)(*(void***)ms)[5])(ms, 0x680c633, defName->mBegin, 0);
    }

    uint32_t mode = GetCurrentGameMode();
    int needRebuild = 1;
    if (mode == 0x1654c04)
    {
        NounMgr* nm = NounManager();
        GDVec* v = (GDVec*)nm->GetGameDataVector((void*)&FUN_00cd7d10,
                                                 (void*)&FUN_00d3d420,
                                                 (void*)&FUN_00acdff0,
                                                 (void*)&FUN_00b1e500,
                                                 (void*)&g_18c43e8);
        if ((uint32_t)(v->mEnd - v->mBegin) <= 1)
            needRebuild = 1;
    }
    if (needRebuild)
    {
        void* s = *(void**)g_singleton167a60c;
        if (s == 0)
        {
            void* raw = FUN_00f473a0(0xc8, (const char*)g_str145f924, 0, 0, 0, 0);
            s = raw ? FUN_00ae5c30v(raw) : 0;
            *(void**)g_singleton167a60c = s;
        }
        FUN_00ae5930v(s);
    }

    FUN_006b2350v();

    if (flag != 0)
    {
        void* planets = FUN_00bb9950v();
        uint32_t m = GetCurrentGameMode();
        uint32_t sel = 0;
        switch (m)
        {
        case 0x1654c00: FUN_00bb9ad0v(1); sel = 1; break;
        case 0x1654c01: sel = 1; break;
        case 0x1654c02: sel = 2; break;
        case 0x1654c04: sel = 4; break;
        case 0x1654c05: sel = 5; break;
        }
        FUN_00bb9ad0v(sel);
        FUN_00bb9b00v(0x80, sel);
        FUN_00bb9b00v(2, 1);
        HomeObj* h = (HomeObj*)FUN_01021370v();
        if (h != 0)
            h->m2c |= 1;
        (void)planets;
    }

    FUN_006b4840v();

    {
        ForeignModel* pm = (ForeignModel*)PlanetModelV();
        if (flag == 0)
        {
            if (pm->mp24 != 0)
            {
                PlanetIface* p = pm->mp24;
                p->v80();
                uint32_t key = p->v84();
                PropListIface* list = (PropListIface*)FUN_00f473a0(0x38, (const char*)g_str145ed5c, 0, 0, 0, 0);
                list = list ? (PropListIface*)FUN_006a1c40v(list) : 0;
                if (list != 0)
                    list->v00();
                list->v2c(key);
                PropMgrIface* mgr = (PropMgrIface*)FUN_0067de30v();
                mgr->v34(list, 0xbb3685dc, 0x4729a47);
                list->v04();
            }
        }
        else if (pm->mp24 != 0)
        {
            pm->mp24->v84();
        }
    }

    FUN_00b28ec0v(self, 0, defName, flag);
    FUN_006b4840v();

    if (flag != 0)
    {
        if (FUN_00baad00v() == 0)
            return 0;
        return FUN_00b28750v(self);
    }
    return 1;
}
