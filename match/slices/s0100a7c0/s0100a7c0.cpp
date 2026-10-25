// Slice s0100a7c0 -- four large game-engine entry points in SporeApp.exe
// (0x0100a7c0..0x0100b0a0).  Frozen batch gold6.  32-bit x86, MSVC 2008 SP1,
// flags /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
//
// All four functions reach deep into engine singletons (NounManager / TerrainEditor,
// TriggerManager, PropertyManager, StarManager, MessageServer, PlanetModel, SimSingleton)
// and build eastl::string / eastl::vector temporaries by value.  They are reconstructed
// structurally below; the recorded byte diffs come from register allocation, from the
// fully inlined eastl containers in retail and, for 0x0100a960, from the whole-program
// inlining of the SimSingleton accessor.

#include "types.h"

// ---------------------------------------------------------------- shared declarations

// 12-byte eastl string header passed by value to 0x0100a7c0
struct Str3 { char* mpBegin; char* mpEnd; char* mpCapacity; };

// 0x1c-byte element of the mission vector at this+0xc8
struct MissionElem {
    char*   mpBegin;    // +0x00
    char*   mpEnd;      // +0x04
    char*   mpCapacity; // +0x08
    int32_t m0C;        // +0x0c (owned by the string assign)
    int32_t m10;        // +0x10
    float   f14;        // +0x14
    int32_t m18;        // +0x18
    void AssignStr(char* first, char* last);            // 0x00454cb0
    void CopyFrom(const MissionElem* src);              // 0x01006630
};

// 0x14-byte element of the embassy vector at this+0xdc
struct EmbElem {
    void*   m00;        // 0x01495400
    void*   m04;        // 0x0149bad8
    int32_t m08;
    int32_t m0C;        // key
    int32_t m10;        // scaled value
};

struct MissionVec {
    MissionElem* mpBegin; MissionElem* mpEnd; MissionElem* mpCapacity;
    void PushSlow(MissionElem* end, const MissionElem* value);   // 0x01009af0
};
struct EmbVec {
    EmbElem* mpBegin; EmbElem* mpEnd; EmbElem* mpCapacity;
    void PushSlow(EmbElem* end, const EmbElem* value);           // 0x01009c60
};

// property instance: type tag at +0x12
struct Prop {
    char     pad00[0x12];
    uint16_t m12;
    float*   GetFloat();   // 0x0041ea70
    int32_t* GetInt();     // 0x0041e990
};

struct TriggerMgr {
    char    pad00[0x2c];
    int32_t m2C;
    void    Notify();      // 0x00addd90
};

struct NounMgr {
    void* GetCurrentTerrainSphere();   // 0x00f67d90
};

struct TerrainSphere {
    bool Contains(void* p);            // 0x00c772c0
};

struct ToolMgr {
    void* GetActiveTool();             // 0x00b1de80
};

struct EmbMap {
    void* Find();                      // 0x00ce6950
};

// mission / solar-system record carried through the noun lists
struct Mission {
    char    pad000[0x1f0];
    void*   mp1F0;                     // +0x1f0
    char    pad1F4[0x200 - 0x1f4];
    char    m200;                      // +0x200 (address taken)
    bool    IsActive();                // 0x00c5b6c0
    void*   GetOwner();                // 0x00c5b340
    void*   GetStarData();             // 0x00970b30
    void*   GetEmpire();               // 0x00c451e0
    float   GetSpeed();                // 0x00c5b860
};

struct MissionOwner {
    char  pad000[0x13c];
    void* mp13C;                       // +0x13c
    int32_t GetKind();                 // 0x00c70e00
};

struct EmbHolder {
    char  pad000[0x13c];
    void* mp13C;                       // +0x13c
};

struct Ufo {
    float* GetPosition();              // 0x005c65e0
    void   SetOwner(void* e);          // 0x00c3c360
    void   Refresh();                  // 0x00c37e60
    void   SetModel(void* p, int32_t a);          // 0x00c37180
    void   SetDestination(const float* p);        // 0x00c3bfe0
};

struct NounListEntry { char pad00[4]; void** mpBegin; void** mpEnd; };

struct NounMgr2 {
    NounListEntry* Query(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e);   // 0x00b21340
};

// solar-system record used by the mission walk
struct StarRec {
    int32_t GetID();                   // 0x00ff0420
    void    SetEmpire(void* p);        // 0x00ff3190
};

struct StarRecHolder {
    char  pad000[0x13c];
    void* mp13C;                       // +0x13c
};

struct Empire {
    void SetHome(void* p);             // 0x00c35310
};

struct StarMgrObj {
    void* GetEmpireByID();             // 0x00ba9370
};

struct SimSingleton {
    void* Ctor();                      // 0x00ae5c30
    void  ShutdownEntries();           // 0x00ae5930
    void  Rebuild();                   // 0x00c2e4e0
};

struct SortObj {
    void* SortGroups();                          // 0x00b8de30
    void  SortBanners(int32_t a, int32_t b);     // 0x00bb9b00
};

struct BannerRoot {
    void* GetSort();                   // 0x00ba6dc0
};

struct SpaceTool {
    void* GetData();                   // 0x00ff3f00
    void  Apply(void* data);           // 0x00ff4540
};
struct SpaceToolData {
    bool IsValid();                    // 0x0104cc90
};

// engine objects that are only ever used as an anonymous `this` in this slice
struct Raw {
    void* FB8DEC0(int32_t i);          // 0x00b8dec0
    void* FB25F40(int32_t id);         // 0x00b25f40
    void  F1034840();                  // 0x01034840
    void  Fb5a390();                   // 0x00b5a390
    void  Fbbf860();                   // 0x00bbf860
    void  Fb2ed10();                   // 0x00b2ed10
    void  Fb0c190(int32_t v);          // 0x00b0c190
    void  Fb781d0();                   // 0x00b781d0
    void  F104f250();                  // 0x0104f250
    void  Ffa2c0();                    // 0x00ffa2c0
    void  Fac4fe0();                   // 0x00ac4fe0
    void  Facc770();                   // 0x00acc770
    void  F106e270();                  // 0x0106e270
    void  F1034950(int32_t a, int32_t b);   // 0x01034950
    void  F421cf0();                   // 0x00421cf0
    void  Fc86c70(int32_t v);          // 0x00c86c70
    void* Fc8b770();                   // 0x00c8b770
    void* Fffc230();                   // 0x00ffc230
};

// ---------------------------------------------------------------- externs

void*   __cdecl FUN_00f473a0(size_t n, const char* name, int32_t a, int32_t b, int32_t c, int32_t d);   // 0x00f473a0
void    __cdecl FUN_00f47380(void* p);                                    // 0x00f47380
TriggerMgr* __cdecl FUN_00b3d4d0(void);                                   // 0x00b3d4d0
NounMgr*    __cdecl FUN_00b3d300(void);                                   // 0x00b3d300
ToolMgr*    __cdecl FUN_00b3d320(void);                                   // 0x00b3d320
void*       __cdecl FUN_00b3d2a0(int32_t key);                            // 0x00b3d2a0
void*       __cdecl FUN_0067de30(void);                                   // 0x0067de30
void*       __cdecl FUN_01021260(void);                                   // 0x01021260
void*       __cdecl FUN_0067ddd0(void);                                   // 0x0067ddd0
void*       __cdecl FUN_0067dcc0(void);                                   // 0x0067dcc0
void*       __cdecl FUN_0067dcd0(void);                                   // 0x0067dcd0
void*       __cdecl FUN_0067ddc0(void);                                   // 0x0067ddc0
void*       __cdecl FUN_0067de00(void);                                   // 0x0067de00
void*       __cdecl FUN_00b3d350(void);                                   // 0x00b3d350
void*       __cdecl FUN_00b3d330(void);                                   // 0x00b3d330
void*       __cdecl FUN_00b3d390(void);                                   // 0x00b3d390
void*       __cdecl FUN_00b3d3b0(void);                                   // 0x00b3d3b0
void*       __cdecl FUN_00b3d3c0(void);                                   // 0x00b3d3c0
void*       __cdecl FUN_00b3d430(void);                                   // 0x00b3d430
void*       __cdecl FUN_00b3d440(void);                                   // 0x00b3d440
void*       __cdecl FUN_00b3d470(void);                                   // 0x00b3d470
void*       __cdecl FUN_00b3d480(void);                                   // 0x00b3d480
void*       __cdecl FUN_00b3d290(void);                                   // 0x00b3d290
void*       __cdecl FUN_00b3d310(void);                                   // 0x00b3d310
void        __cdecl FUN_0106e270(void* p);                                // 0x0106e270
void        __cdecl FUN_01021960(int32_t v);                              // 0x01021960
void*       __cdecl FUN_01021230(void);                                   // 0x01021230
void*       __cdecl FUN_00ffbe50();                                       // 0x00ffbe50
void        __cdecl FUN_00b6c280();                                       // 0x00b6c280
void        __cdecl FUN_00cfeac0();                                       // 0x00cfeac0
void*       __cdecl FUN_0069b600(void* out, void* facing, void* up);      // 0x0069b600
void*       __cdecl FUN_0102ac50(int32_t kind, void* owner);              // 0x0102ac50
void        __cdecl FUN_0102c340(void* p, int32_t v);                     // 0x0102c340
void        __cdecl FUN_006782c0(void** first, void** last, void** dest); // 0x006782c0
void*       __cdecl FUN_01006280(void* first, void* last, void* dest);    // 0x01006280
void        __cdecl FUN_00aea5d0(void** end, void** value);               // 0x00aea5d0

extern float         g_13ec5b4;     // 0x013ec5b4
extern float         g_1495390;     // 0x01495390
extern void*         g_167a60c;     // 0x0167a60c
extern void*         g_16dc0fc;     // 0x016dc0fc
extern float         g_16dc100;     // 0x016dc100
extern float         g_16dc104;     // 0x016dc104
extern float         g_16dc108;     // 0x016dc108
extern float         g_1485720;     // 0x01485720
extern float         g_16dc6f0[9];  // 0x016dc6f0
extern const uint8_t g_16dc714[16]; // 0x016dc714
extern char          g_1667bac;     // 0x01667bac (shared empty string)
extern char          g_1667bad;     // 0x01667bad

// ---------------------------------------------------------------- helpers

static void freeStr(Str3& s)
{
    if (s.mpCapacity - s.mpBegin > 1 && s.mpBegin != 0)
        FUN_00f47380(s.mpBegin);
}

static void freeElemStr(char* begin, char* capacity)
{
    if (capacity - begin > 1 && begin != 0)
        FUN_00f47380(begin);
}

static void* vcall(void* p, int byteOff)
{
    return ((void*(__thiscall*)(void*))(*((char**)*(void**)p + byteOff / 4)))(p);
}

static void vcall0(void* p, int byteOff)
{
    ((void(__thiscall*)(void*))(*((char**)*(void**)p + byteOff / 4)))(p);
}

static void vcall1(void* p, int byteOff, int32_t a)
{
    ((void(__thiscall*)(void*, int32_t))(*((char**)*(void**)p + byteOff / 4)))(p, a);
}

static void vcall2(void* p, int byteOff, int32_t a, int32_t b)
{
    ((void(__thiscall*)(void*, int32_t, int32_t))(*((char**)*(void**)p + byteOff / 4)))(p, a, b);
}

static bool vcallProp(void* p, int byteOff, int32_t id, void** out)
{
    return ((bool(__thiscall*)(void*, int32_t, void**))(*((char**)*(void**)p + byteOff / 4)))(p, id, out);
}

static void vrelease(void* p)
{
    if (p != 0)
        ((void(__thiscall*)(void*))(*((char**)*(void**)p + 1)))(p);
}

static void vaddref(void* p)
{
    if (p != 0)
        ((void(__thiscall*)(void*))(*((char**)*(void**)p + 0)))(p);
}

// ---------------------------------------------------------------- class

struct CSporeSim {
    char    pad0000[0x14];
    void*   mp14;                       // +0x14
    char    pad0018[0x54 - 0x18];
    void*   mp54;                       // +0x54
    char    pad0058[0x6c - 0x58];
    uint8_t m6C;                        // +0x6c
    char    pad006D[0x78 - 0x6d];
    char*   mp78;                       // +0x78  vector<void*> begin
    char*   mp7C;                       // +0x7c  vector<void*> end
    char*   mp80;                       // +0x80  vector<void*> capacity
    char    pad0084[0xc8 - 0x84];
    char*   mpC8;                       // +0xc8  vector<MissionElem> begin
    char*   mpCC;                       // +0xcc  vector<MissionElem> end
    char*   mpD0;                       // +0xd0  vector<MissionElem> capacity
    char    pad00D4[0xdc - 0xd4];
    char*   mpDC;                       // +0xdc  vector<EmbElem> begin
    char*   mpE0;                       // +0xe0  vector<EmbElem> end
    char*   mpE4;                       // +0xe4  vector<EmbElem> capacity

    bool AddMission(Str3 str, int32_t a4, int32_t a5, int32_t a6);   // 0x0100a7c0
    void ActivateSim();                                             // 0x0100a960
    void SyncEmbassy(void* mission);                                // 0x0100aec0
    void UpdateMissions();                                          // 0x0100b0a0
};

// NOTE: `str` is the caller's 12-byte eastl string home (begin/end/capacity); it is
// destroyed by this callee on every exit path, exactly as in retail.
// @ 0x0100a7c0
bool CSporeSim::AddMission(Str3 str, int32_t a4, int32_t a5, int32_t a6)
{
    if (a6 == 0) {
        TriggerMgr* tm = FUN_00b3d4d0();
        if (tm->m2C == 1 || tm->m2C == 2) {
            freeStr(str);
            return false;
        }
    }

    NounMgr* nm = FUN_00b3d300();
    void* sphere = nm->GetCurrentTerrainSphere();
    if (sphere != 0) {
        if (((TerrainSphere*)sphere)->Contains((void*)(size_t)a5)) {
            FUN_00b3d4d0()->Notify();
            freeStr(str);
            return false;
        }
    }

    MissionElem elem;
    elem.mpBegin    = &g_1667bac;
    elem.mpEnd      = &g_1667bac;
    elem.mpCapacity = &g_1667bad;
    elem.AssignStr(str.mpBegin, str.mpEnd);
    elem.m10 = a5;
    elem.m18 = a6;

    void* tool = FUN_00b3d320()->GetActiveTool();
    bool  got  = false;
    void* prop = 0;
    if (tool != 0)
        got = vcallProp(tool, 0x24, 0x80acc889, &prop);

    float value;
    if (got && ((Prop*)prop)->m12 == 0x0d)
        value = *((Prop*)prop)->GetFloat();
    else
        value = elem.f14;
    elem.f14 = value * g_13ec5b4;

    MissionVec* v = (MissionVec*)((char*)this + 0xc8);
    if (v->mpEnd < v->mpCapacity) {
        MissionElem* slot = v->mpEnd++;
        if (slot != 0)
            slot->CopyFrom(&elem);
    } else {
        v->PushSlow(v->mpEnd, &elem);
    }

    freeElemStr(elem.mpBegin, elem.mpCapacity);
    freeStr(str);
    return true;
}

// @ 0x0100a960
void CSporeSim::ActivateSim()
{
    if (g_167a60c == 0) {
        SimSingleton* s = (SimSingleton*)FUN_00f473a0(
            0xc8, (const char*)0x145f924, 0, 0, 0, 0);
        if (s != 0)
            s = (SimSingleton*)s->Ctor();
        g_167a60c = s;
    }
    ((SimSingleton*)g_167a60c)->ShutdownEntries();

    EmbHolder* rec = (EmbHolder*)FUN_01021260();

    void* em = FUN_0067ddd0();
    vcall2(em, 0x98, 0x14, 0);
    em = FUN_0067ddd0();
    vcall0(vcall(em, 0x5c), 0x38);

    // space-tool data refresh
    if (g_16dc0fc != 0) {
        void* tool = *(void**)((char*)g_16dc0fc + 0x40);
        if (tool != 0) {
            SpaceToolData* data = (SpaceToolData*)((SpaceTool*)tool)->GetData();
            if (data != 0 && data->IsValid())
                ((SpaceTool*)tool)->Apply(data);
        }
    }

    // walk the +0x13c record's +0x15c vector and re-home each star
    if (rec->mp13C != 0) {
        int32_t count = (*(int32_t*)((char*)rec->mp13C + 0x160) -
                         *(int32_t*)((char*)rec->mp13C + 0x15c)) / 4;
        for (int32_t i = 0; i < count; ++i) {
            StarRec* sr = (StarRec*)((Raw*)rec->mp13C)->FB8DEC0(0);
            int32_t id = sr->GetID();
            void* empire = ((Raw*)FUN_00b3d300())->FB25F40(id);
            if (empire != 0) {
                void* home = (char*)empire + 0x6c;
                sr->SetEmpire(home);
                int32_t sid = sr->GetID();
                if (sid < 0) {
                    StarMgrObj* sm = (StarMgrObj*)FUN_00b3d2a0(sr->GetID());
                    Empire* e = (Empire*)sm->GetEmpireByID();
                    e->SetHome(home);
                }
            }
        }
    }

    // SlotMessage broadcast
    {
        struct SlotMsg {
            void*   mpVtbl;   // +0x00
            int32_t m04;      // +0x04
            void*   m08;      // +0x08
            char    pad[0x38 - 0x0c];
        } msg;
        msg.mpVtbl = (void*)0x13eb90c;
        msg.m04    = 0;
        msg.m08    = 0;
        msg.mpVtbl = (void*)0x13eb844;
        msg.m08    = FUN_01021260();
        void* srv = FUN_0067dcc0();
        ((void(__thiscall*)(void*, void*, int32_t, int32_t))(
            *((char**)*(void**)srv + 5)))(srv, &msg, 0x2489760, 0);
        ((Raw*)&msg)->F421cf0();
    }

    void* pm = FUN_00b3d350();
    void* pmObj = *(void**)((char*)pm + 0x24);
    if (pmObj != 0) {
        vcall0(pmObj, 0xac);
        vcall0(pmObj, 0x84);
    }

    if (mp14 != 0)
        FUN_0106e270(mp14);
    FUN_01021960(-1);

    {
        float tbl[16];
        tbl[0]  = g_16dc100;
        tbl[1]  = g_16dc104;
        tbl[2]  = g_16dc108;
        tbl[3]  = g_1485720;
        tbl[4]  = g_16dc6f0[0];
        tbl[5]  = g_16dc6f0[1];
        tbl[6]  = g_16dc6f0[2];
        tbl[7]  = g_16dc6f0[3];
        tbl[8]  = g_16dc6f0[4];
        tbl[9]  = g_16dc6f0[5];
        tbl[10] = g_16dc6f0[6];
        tbl[11] = g_16dc6f0[7];
        tbl[12] = 0.0f;
        tbl[13] = 0.0f;
        void* em2 = FUN_0067de00();
        ((void(__thiscall*)(void*, float*))(*((char**)*(void**)em2 + 0xdc / 4)))(em2, tbl);
    }

    ((Raw*)FUN_00b3d470())->F1034840();
    ((Raw*)FUN_00b3d310())->Fb5a390();

    if (m6C != 0 && pmObj != 0) {
        m6C = 0;
        vcall0(pmObj, 0x84);
    }

    if (mp54 != 0) {
        ((Raw*)mp54)->Ffa2c0();
        if (mp54 != 0) {
            void* old = mp54;
            mp54 = 0;
            vrelease(old);
        }
    }

    {
        void* x = FUN_01021230();
        if (x != 0) {
            void* y = ((Raw*)x)->Fc8b770();
            if (y != 0)
                ((Raw*)y)->Fc86c70(0);
        }
    }

    ((Raw*)FUN_00b3d430())->Fbbf860();
    ((Raw*)FUN_00b3d3b0())->Fb2ed10();
    ((Raw*)FUN_00b3d440())->Fb0c190(1);
    ((Raw*)FUN_00b3d3c0())->Fb781d0();
    ((Raw*)FUN_00b3d390())->F104f250();

    {
        void* em3 = FUN_0067ddd0();
        void* q = ((void*(__thiscall*)(void*, int32_t))(
            *((char**)*(void**)em3 + 0x54 / 4)))(em3, 0x3701a5c);
        vcall0(q, 0x34);
    }

    ((Raw*)FUN_00ffbe50())->Fffc230();
    ((Raw*)FUN_00b3d470())->F1034950(0, -1);

    {
        void* srv = FUN_0067dcd0();
        struct Pair { void* mpVtbl; int32_t m04; } p1, p2;
        p1.mpVtbl = (void*)0x13eb428; p1.m04 = 0x1c135da;
        ((void(__thiscall*)(void*, int32_t, void*))(
            *((char**)*(void**)srv + 0x70 / 4)))(srv, 0, &p1);
        p2.mpVtbl = (void*)0x13eb428; p2.m04 = 0xe6bce5;
        ((void(__thiscall*)(void*, int32_t, void*))(
            *((char**)*(void**)srv + 0x70 / 4)))(srv, 0, &p2);
    }

    ((Raw*)FUN_00b3d290())->Fac4fe0();

    if (g_167a60c == 0) {
        SimSingleton* s = (SimSingleton*)FUN_00f473a0(
            0xc8, (const char*)0x145f924, 0, 0, 0, 0);
        if (s != 0)
            s = (SimSingleton*)s->Ctor();
        g_167a60c = s;
    }
    ((SimSingleton*)g_167a60c)->Rebuild();

    {
        void* ticker = FUN_00b3d330();
        if (g_167a60c == 0) {
            SimSingleton* s = (SimSingleton*)FUN_00f473a0(
                0xc8, (const char*)0x145f924, 0, 0, 0, 0);
            if (s != 0)
                s = (SimSingleton*)s->Ctor();
            g_167a60c = s;
        }
        ((void(__thiscall*)(void*, void*))(
            *((char**)*(void**)ticker + 0x54 / 4)))(ticker, g_167a60c);
    }

    ((Raw*)FUN_00b3d480())->Facc770();
    FUN_00b6c280();

    {
        void* o = FUN_0067ddc0();
        if (o != 0) {
            vcall1(o, 0x28, 0);
            vcall0(o, 0x24);
        }
    }

    FUN_00cfeac0();

    // drain the mission element vector, freeing each inlined eastl string
    {
        MissionElem* first = (MissionElem*)(void*)mpC8;
        MissionElem* last  = (MissionElem*)(void*)mpCC;
        MissionElem* it = (MissionElem*)FUN_01006280(first, last, last);
        for (MissionElem* p = it; p < last; ++p)
            freeElemStr(p->mpBegin, p->mpCapacity);
        mpCC = (char*)(mpCC - ((char*)last - (char*)first));
    }

    FUN_00b3d4d0()->Notify();
}

// @ 0x0100aec0
void CSporeSim::SyncEmbassy(void* mission)
{
    EmbHolder* m = (EmbHolder*)mission;

    void* found = ((EmbMap*)m->mp13C)->Find();

    EmbElem elem;
    elem.m00 = (void*)0x1495400;
    elem.m04 = (void*)0x149bad8;
    elem.m08 = 0;
    elem.m0C = (int32_t)(size_t)found;
    elem.m10 = 1000;

    void* propMgr = FUN_0067de30();
    void* propObj = 0;
    ((void(__thiscall*)(void*, int32_t, int32_t, void**))(
        *((char**)*(void**)propMgr + 0x2c / 4)))(propMgr, 0x249e8357, 0x2ae0c7e, &propObj);

    int32_t kind = ((MissionOwner*)mission)->GetKind();
    int32_t value = 1000;
    void*   prop = 0;
    bool    got = false;

    switch (kind) {
    case 1:
        if (propObj != 0)
            got = vcallProp(propObj, 0x24, 0xa9856bd1, &prop);
        break;
    case 2:
        if (propObj != 0)
            got = vcallProp(propObj, 0x24, 0x897907de, &prop);
        break;
    case 4:
        if (propObj != 0)
            got = vcallProp(propObj, 0x24, 0xcf99dc04, &prop);
        break;
    default:
        break;
    }

    if (got && prop != 0 && ((Prop*)prop)->m12 == 9)
        value = *((Prop*)prop)->GetInt();

    elem.m10 = value * 1000;

    EmbVec* v = (EmbVec*)((char*)this + 0xdc);
    int32_t count = (int32_t)((v->mpEnd - v->mpBegin) / 0x14);
    for (int32_t i = 0; i < count; ++i) {
        if (v->mpBegin[i].m0C == elem.m0C) {
            vrelease(propObj);
            return;
        }
    }

    {
        BannerRoot* br = (BannerRoot*)FUN_00b3d2a0(elem.m0C);
        SortObj* sort = (SortObj*)br->GetSort();
        if (sort != 0) {
            void* s2 = sort->SortGroups();
            if (s2 != 0)
                ((SortObj*)s2)->SortBanners(8, 1);
        }
    }

    if (v->mpEnd < v->mpCapacity) {
        EmbElem* slot = v->mpEnd++;
        if (slot != 0) {
            slot->m04 = (void*)0x13ec458;
            slot->m08 = 0;
            slot->m00 = (void*)0x1495400;
            slot->m04 = (void*)0x149bad8;
            slot->m0C = elem.m0C;
            slot->m10 = elem.m10;
        }
    } else {
        v->PushSlow(v->mpEnd, &elem);
    }

    vrelease(propObj);
}

// @ 0x0100b0a0
void CSporeSim::UpdateMissions()
{
    NounMgr* nm = FUN_00b3d300();
    NounListEntry* list = ((NounMgr2*)nm)->Query(0xcd7d10, 0xd3d420, 0x100a740, 0xb1e500, 0x3960c0e);
    void** it  = list->mpBegin;
    void** end = list->mpEnd;
    if (it == end)
        return;

    for (; it != end; ++it) {
        Mission* m = (Mission*)*it;

        // drop a stale UFO handle
        if (m->mp1F0 != 0) {
            if (vcall(m->mp1F0, 0x2c) != 0) {
                if (m->mp1F0 != 0) {
                    void* old = m->mp1F0;
                    m->mp1F0 = 0;
                    vrelease(old);
                }
            }
        }

        if (!m->IsActive()) {
            if (m->mp1F0 != 0) {
                FUN_0102c340(m->mp1F0, 0);

                // erase m->mp1F0 from the vector at this+0x78
                void** b = (void**)mp78;
                void** e = (void**)mp7C;
                void** p = b;
                while (p != e && *p != m->mp1F0)
                    ++p;
                if (p + 1 < e)
                    FUN_006782c0(p + 1, e, p);
                mp7C = mp7C - 4;
                {
                    void* tail = *(void**)mp7C;
                    if (tail != 0)
                        vrelease(tail);
                }
                if (m->mp1F0 != 0) {
                    void* old = m->mp1F0;
                    m->mp1F0 = 0;
                    vrelease(old);
                }
            }
            continue;
        }

        void* owner = m->GetOwner();
        void* starData = m->GetStarData();
        void* sortObj = 0;
        if (starData != 0)
            sortObj = ((SortObj*)((StarRecHolder*)starData)->mp13C)->SortGroups();

        if (m->mp1F0 == 0) {
            Ufo* ufo = (Ufo*)FUN_0102ac50(4, m->GetEmpire());
            if (m->GetEmpire() == 0)
                ufo->SetModel(&m->m200, 0);
            ufo->SetOwner(owner);
            ufo->Refresh();
            {
                // field vcall: (ufo+0x34)->vtable[0x40](float)
                void* sub = (char*)ufo + 0x34;
                void* vt  = *(void**)sub;
                ((void(__thiscall*)(void*, float))(*((char**)vt + 0x40 / 4)))(sub, g_1495390);
            }
            vaddref(ufo);

            {
                void** e = (void**)mp7C;
                if (e < (void**)mp80) {
                    mp7C = (char*)(e + 1);
                    if (e != 0) {
                        *e = ufo;
                        vaddref(ufo);
                    }
                } else {
                    FUN_00aea5d0(e, (void**)&ufo);
                }
            }
            vrelease(ufo);

            {
                void* old = m->mp1F0;
                if (ufo != old) {
                    vaddref(ufo);
                    m->mp1F0 = ufo;
                    if (old != 0)
                        vrelease(old);
                }
            }
        }

        if (m->mp1F0 == 0)
            continue;

        {
            Ufo* ufo = (Ufo*)m->mp1F0;
            float* from = ufo->GetPosition();
            float* to   = ((Ufo*)sortObj)->GetPosition();
            float  dt   = m->GetSpeed();

            float delta[3];
            delta[0] = (to[0] - from[0]) * dt;
            delta[1] = (to[1] - from[1]) * dt;
            delta[2] = (to[2] - from[2]) * dt;

            float* pos = ufo->GetPosition();
            float dest[3];
            dest[0] = pos[0] + delta[0];
            dest[1] = pos[1] + delta[1];
            dest[2] = pos[2] + delta[2];
            ufo->SetDestination(dest);

            float len = delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];
            float inv = 1.0f / len;
            float dir[3];
            dir[0] = delta[0] * inv;
            dir[1] = delta[1] * inv;
            dir[2] = delta[2] * inv;

            Ufo* target = (Ufo*)m->mp1F0;
            float quat[4];
            FUN_0069b600(quat, dir, (void*)g_16dc714);
            float* dst = (float*)((char*)target + 0x730);
            dst[0] = quat[0];
            dst[1] = quat[1];
            dst[2] = quat[2];
            dst[3] = quat[3];
            target->Refresh();
        }
    }
}
