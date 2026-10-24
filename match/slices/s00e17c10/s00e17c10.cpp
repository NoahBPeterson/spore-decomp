// Slice s00e17c10 -- Spore UI cUIMissionCard / cUIMissionCardPanel cluster.
//
// Modelled types (retail member offsets are read from the disassembly; the PDB
// layout differs, so objects are modelled locally with role-named members and
// explicit padding for the untouched gaps):
//   cUIMissionCard       mission card widget: base card @0x00.., animator @0x28,
//                        mission trackers @0x9c, collapse/expanded flags @0x10/@0x11
//   cUIMissionCardPanel  mission card panel: layout @0x18, current card @0x1c,
//                        mission map @0x3c (rbtree), current mission @0x38
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef int            i32;

#define FORCEINLINE __forceinline

// --------------------------------------------------------------- extern decls
extern "C" void  *SP_GetCurrentGameMode();                  // 0x00b5b800
extern "C" void   FUN_00810590(void *layout, int v, int f); // 0x00810590 cSPUILayout::SetVisibility
extern "C" void   FUN_00811ad0(void *layout, int f);        // 0x00811ad0 cSPUILayout::Shutdown
extern "C" bool   FUN_00810070(void *layout);               // 0x00810070 cSPUILayout::IsVisible
extern "C" void   FUN_00e5c780(void *tree, void *out, void *key); // 0x00e5c780 eastl::rbtree find
extern "C" void  *FUN_00921580(void *node);                 // 0x00921580 RBTreeIncrement
extern "C" void  *operator_delete_array(void *p);           // 0x00f47380
extern "C" void  *FUN_00b3d3f0();                           // 0x00b3d3f0
extern "C" void   FUN_00e30a60(void *o, u32 v);             // 0x00e30a60
extern "C" void   FUN_00e30ae0(void *o, u32 v);             // 0x00e30ae0
extern "C" float  SPUI_GetElapsedSeconds();                 // 0x00805080
extern "C" bool   FUN_007f6340(void *animator);             // 0x007f6340 cSPUIAnimator::Empty
extern "C" void   FUN_007f63b0(void *animator);             // 0x007f63b0 cSPUIAnimator::Update
extern "C" bool   FUN_00c44c90(void *mission);              // 0x00c44c90
extern "C" bool   FUN_00e15060(void *card, char b);         // 0x00e15060 cUICard::Init
extern "C" void   FUN_00e25bd0(void *vec, void *first, void *last); // 0x00e25bd0 vector::erase
extern "C" void   FUN_00e492d0(void *o);                    // 0x00e492d0
extern "C" void   FUN_00571db0(u32 a, u32 b, u32 c, u32 d, u32 e); // 0x00571db0 RemoveHandler
extern "C" void  *operator_new(u32 size, u32 file, u32 line, u32 a, u32 b, u32 c); // 0x00f473a0
extern "C" void  *FUN_00e147a0(void *o);                     // 0x00e147a0
extern "C" void  *FUN_00e141a0(void *o);                     // 0x00e141a0
extern "C" void  *FUN_00e4a6e0(void *o);                     // 0x00e4a6e0
extern "C" void   FUN_00aea5d0(void **v, void *last, void *val); // 0x00aea5d0 vector push_back
extern "C" void   FUN_00e168d0(void *card, u32 mission, u32 b);  // 0x00e168d0
extern "C" void   FUN_00e18050(void **a, void **b, u32 c);    // 0x00e18050
extern "C" void   FUN_00e14b70(void *panel);                 // 0x00e14b70 UpdateCardPositions
extern "C" void   FUN_00e49360(void *o, void *v);            // 0x00e49360
extern "C" void   FUN_00e49a40(void *o, void *v);            // 0x00e49a40
extern "C" void  *FUN_006c0200(void *o);                     // 0x006c0200
extern "C" void   FUN_006782c0(void *first, void *last, void *dst); // 0x006782c0 copy
extern "C" bool   FUN_00c44c80(void *mission);               // 0x00c44c80 cSPMission::IsActive
extern "C" bool   FUN_00febe50(void *mgr, void *mission, u32 b); // 0x00febe50
extern "C" void  *FUN_00febc70(void *mgr);                   // 0x00febc70
extern "C" void  *GetMissionManager();                       // 0x00feb9f0
extern "C" void  *FUN_00fedd50(void *mgr);                   // 0x00fedd50 GetMissionList
extern "C" void  *SP_SpaceGameGet();                         // 0x01002bd0
extern "C" void  *FUN_00bfc5f0(void *o);                     // 0x00bfc5f0 SetGameDataOwner2
extern "C" void  *FUN_00575ea0(void *o);                     // 0x00575ea0 GetDefaultIconDrawable
extern "C" bool   FUN_00e15cd0(void *panel, void *mission);  // 0x00e15cd0 HasMissionCard
extern "C" void   FUN_00e15c70(void *panel, void *mission);  // 0x00e15c70 CollapseOtherMissionCards
extern "C" void   FUN_00e5c780_find(void *tree, void *out, void *key); // 0x00e5c780
extern "C" void  *MessageServer();                           // 0x0067dcc0
extern "C" bool   FUN_008120d0(void *layout, void *key, bool b, int c); // 0x008120d0 cSPUILayout::Init
extern "C" bool   FUN_008121b0(void *layout, void *parent, bool b, u32 id); // 0x008121b0 SetParentWin
extern "C" void  *FUN_008105b0(void *layout, int id, bool b); // 0x008105b0 FindWindowByID
extern "C" void   FUN_00810570(void *o);                     // 0x00810570
extern "C" void  *FUN_00810000(void *o);                     // 0x00810000 cConnectionDialog ctor

// cUIMissionCard methods
extern "C" void   FUN_00e30990(void *o, u32 arg);           // 0x00e30990

// ============================================================ cUIMissionCard
struct cUIMissionCard {
    u8   m_pad00[0x10];
    u8   m_collapsed;       // +0x10
    u8   m_animated;        // +0x11
    u8   m_pad12[0x16];
    void *m_animator;       // +0x28
    u8   m_pad2c[0x70];
    void *m_mission;        // +0x9c

    void DoCollapse();      // 0x00e17d60
    void DoExpand();        // 0x00e17cf0
    void UpdateDetails(char flag); // 0x00e17c10
    void Update();          // 0x00e17d70
    void Setup(void *mission, char a, char b); // 0x00e17f40
    void UpdateFromMission(void *m); // 0x00e16090
    void SetMissionSub(void *m);     // 0x00e17570
    void InitForCreature(int a, int state); // 0x00e133b0
    void ResizeToContent(int a, int state); // 0x00e13b50
};

// mission object: vtable only (slot 0x0c = substream lookup by hash, 0x64/0x68 = state flags)
struct cSPMission {
    void **m_vtbl;          // +0x00
};

// @ 0x00e17c10
void cUIMissionCard::UpdateDetails(char flag)
{
    if (m_mission == 0) {
        return;
    }
    u32 mode = (u32)(unsigned long)SP_GetCurrentGameMode();
    switch (mode) {
    case 0x1654c00:
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04: {
        void *pc = m_mission;
        void *sub;
        if (pc != 0) {
            sub = ((void *(__thiscall *)(void *, u32))(*(void ***)pc)[0x0c / 4])(pc, 0x14066ce5);
        } else {
            sub = 0;
        }
        UpdateFromMission(sub);
        break;
    }
    case 0x1654c05: {
        void *pc = m_mission;
        void *sub;
        if (pc != 0) {
            sub = ((void *(__thiscall *)(void *, u32))(*(void ***)pc)[0x0c / 4])(pc, 0x2aa5ada);
        } else {
            sub = 0;
        }
        SetMissionSub(sub);
        break;
    }
    }
    if (flag == 0) {
        int state;
        if (((bool (__thiscall *)(void *))(*(void ***)m_mission)[0x64 / 4])(m_mission)) {
            state = 1;
        } else if (((bool (__thiscall *)(void *))(*(void ***)m_mission)[0x68 / 4])(m_mission)) {
            state = 2;
        } else {
            state = 0;
        }
        if (m_collapsed != 0) {
            InitForCreature(1, state);
        } else {
            ResizeToContent(1, state);
        }
    }
}

// @ 0x00e17d60
void cUIMissionCard::DoCollapse()
{
    m_collapsed = 0;
    m_animated = 1;
    UpdateDetails(0);
}

// @ 0x00e17d70
void cUIMissionCard::Update()
{
    SPUI_GetElapsedSeconds();
    if (m_animator != 0) {
        if (!((bool (__thiscall *)(void *))FUN_007f6340)(m_animator)) {
            m_animated = 1;
            ((void (__thiscall *)(void *))FUN_007f63b0)(m_animator);
        }
    }
    if ((u32)(unsigned long)SP_GetCurrentGameMode() == 0x1654c05) {
        void *sub;
        if (m_mission != 0) {
            sub = ((void *(__thiscall *)(void *, u32))(*(void ***)m_mission)[0x0c / 4])(m_mission, 0x2aa5ada);
        } else {
            sub = 0;
        }
        if (((bool (__thiscall *)(void *))FUN_00c44c90)(sub)) {
            u32 n = ((u32 (__thiscall *)(void *))(*(void ***)sub)[0xac / 4])(sub);
            if (n > 0) {
                UpdateDetails(1);
            }
        }
    }
}

// ============================================================ cUIMissionCardPanel
// The original panel is a composite: two non-polymorphic sub-objects that receive
// their own "this" (a message handler at +0x0c and another handler record at
// +0x24).  Modelling them as real bases makes cl reproduce the subobject this and
// the shift back to the panel itself.
struct cPanelHead0c {               // +0x00
    void **m_vtbl00;                // +0x00
    void  *m_sub04;                 // +0x04
    void  *m_slotVtbl08;            // +0x08
};

struct cPanelMsg0c {                // +0x0c  (OnMessage's this)
    void  *m_slotVtbl0c;            // +0x0c
    u32    m_field10;               // +0x10
    void  *m_field14;               // +0x14
    void  *m_layout;                // +0x18
    void  *m_card;                  // +0x1c

    char   OnMessage(u32 msg, void *arg); // 0x00e18600
};

struct cPanelMsg24 {                // +0x20
    void  *m_handlerObj;            // +0x20
};

struct cPanelHandler24 {            // +0x24  (HandleMessage's this)
    void  *m_handlerArg1;           // +0x24

    char   HandleMessage(u32 msg, void *arg); // 0x00e18380
};

struct cUIMissionCardPanel : cPanelHead0c, cPanelMsg0c, cPanelMsg24, cPanelHandler24 {
    union {                 // +0x28: message-handler view / card-vector view
        struct {
            void *m_handlerArg2; // +0x28
            u32   m_handlerN;    // +0x2c
            void *m_handlerArg4; // +0x30
        };
        struct {
            void **m_vec28;      // +0x28 vector begin
            void **m_vec2c;      // +0x2c vector end
            union {              // +0x30: vector capacity / layout object
                void **m_vec30;
                void  *m_visObj;
            };
        };
    };
    void *m_treeBegin34;    // +0x34
    void *m_curMission;     // +0x38
    void *m_field3c;        // +0x3c
    void *m_treeBase40;     // +0x40
    u8    m_pad44[0x14];
    void *m_field58;        // +0x58
    void *m_field5c;        // +0x5c
    u8    m_pad60[0x14];
    void *m_tree74;         // +0x74

    void SetVisibleSlot(int v);          // 0x00e18860
    void ShutdownCard();                 // 0x00e18810
    void ClearTree();                    // 0x00e18a90
    void *FindMission(u32 id);           // 0x00e18b10
    bool  ShouldShow(u32 id);            // 0x00e18c70
    void  ForEach(u32 a, u32 b);         // 0x00e18ac0
    void  Refresh();                     // 0x00e17df0
    void  UpdateCardDetails(void *mission); // 0x00e17e40
    void  ShutdownA();                   // 0x00e18a30
    void  ShutdownB();                   // 0x00e18b50
    void  SetSlotAndMission(u32 slot); // 0x00e18cb0
    void *InitHints(void *param);        // 0x00e188b0
    void  DestroyMembers();              // 0x00e18980
    void *Construct();                   // 0x00e18bb0
    bool  RemoveMissionCard(void *mission); // 0x00e17fb0
    void *AddMissionCard(u32 mission);   // 0x00e18150
    void *SetupMissionCard(void *mission, u32 a, u32 b, char c); // 0x00e18200
    void  RefreshFromMissionList();      // 0x00e184d0
    void  OnNotify(u32 a, u32 b, u32 c, u32 d); // 0x00e186d0
};

// @ 0x00e18860
void cUIMissionCardPanel::SetVisibleSlot(int v)
{
    if (m_layout != 0) {
        return ((void (__thiscall *)(void *, int))FUN_00810590)(m_layout, 1);
    }
}

// @ 0x00e18810
void cUIMissionCardPanel::ShutdownCard()
{
    void *card = m_card;
    if (card != 0) {
        m_card = 0;
        ((void (__thiscall *)(void *))(*(void ***)card)[1])(card);
    }
    void *lay = m_layout;
    if (lay != 0) {
        ((void (__thiscall *)(void *, int))FUN_00811ad0)(lay, 1);
        lay = m_layout;
        if (lay != 0) {
            m_layout = 0;
            ((void (__thiscall *)(void *))(*(void ***)lay)[2])(lay);
        }
    }
    m_field10 = 0xffffffff;
}

// @ 0x00e18a90
void cUIMissionCardPanel::ClearTree()
{
    void *node = m_treeBegin34;
    void *base = &m_treeBegin34;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    *(void **)base = base;
    *(void **)((u8 *)base + 4) = base;
}

// @ 0x00e18b10
void *cUIMissionCardPanel::FindMission(u32 id)
{
    void *result = 0;
    void *out;
    void *base = (u8 *)this + 0x40;
    ((void (__thiscall *)(void *, void **, u32 *))FUN_00e5c780)(
        (u8 *)this + 0x3c, &out, &id);
    if (base != out) {
        result = *(void **)((u8 *)out + 0x14);
    }
    return result;
}

// @ 0x00e18c70
bool cUIMissionCardPanel::ShouldShow(u32 id)
{
    if (m_visObj == 0
        || !((bool (__thiscall *)(void *))FUN_00810070)(m_visObj)) {
        return false;
    }
    if (id == 0) {
        return true;
    }
    if (FindMission(id) == m_curMission) {
        return true;
    }
    return false;
}// @ 0x00e18ac0
void cUIMissionCardPanel::ForEach(u32 a, u32 b)
{
    if (m_field58 != 0) {
        FUN_00e30990(m_field58, b);
    }
    void *node = m_treeBase40;
    void *base = (u8 *)this + 0x3c;
    while (node != base) {
        void *obj = *(void **)((u8 *)node + 0x14);
        ((void (__thiscall *)(void *, u32))(*(void ***)obj)[0x18 / 4])(obj, b);
        node = FUN_00921580(node);
    }
}

// @ 0x00e17df0
void cUIMissionCardPanel::Refresh()
{
    int n = (int)(m_vec2c - m_vec28);
    for (int i = 0; i < n; i++) {
        void *card = m_vec28[i];
        if (card == 0) {
            continue;
        }
        void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)card)[0x0c / 4])(card, 0x334c6eec);
        if (sub != 0) {
            ((cUIMissionCard *)sub)->UpdateDetails(0);
        }
    }
}

// @ 0x00e17e40
void cUIMissionCardPanel::UpdateCardDetails(void *mission)
{
    int count = (int)(m_vec2c - m_vec28);
    for (int i = 0; i < count; i++) {
        void *card = m_vec28[i];
        if (card == 0) {
            continue;
        }
        void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)card)[0x0c / 4])(card, 0x334c6eec);
        if (sub == 0) {
            continue;
        }
        if (*(void **)((u8 *)sub + 0x9c) != mission) {
            continue;
        }
        ((cUIMissionCard *)sub)->UpdateDetails(0);
    }
}

// @ 0x00e18a30
void cUIMissionCardPanel::ShutdownA()
{
    void *mgr = FUN_00b3d3f0();
    FUN_00e30a60(*(void **)((u8 *)mgr + 0x5c), m_field10);
    void *mgr2 = FUN_00b3d3f0();
    FUN_00e30ae0(*(void **)((u8 *)mgr2 + 0x5c), 0xf45f7d78);
    void *node = m_treeBegin34;
    void *base = &m_treeBegin34;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    *(void **)base = base;
    *(void **)((u8 *)base + 4) = base;
    if (m_layout != 0) {
        ((void (__thiscall *)(void *, int))FUN_00810590)(m_layout, 0);
    }
}

// @ 0x00e18b50
void cUIMissionCardPanel::ShutdownB()
{
    if (m_field5c != 0) {
        FUN_00e30a60(m_field5c, 0x6244208);
    }
    void *node = m_tree74;
    void *base = (u8 *)this + 0x74;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    *(void **)base = base;
    *(void **)((u8 *)base + 4) = base;
    void *n2 = m_treeBase40;
    void *b2 = (u8 *)this + 0x40;
    while (n2 != b2) {
        void *obj = *(void **)((u8 *)n2 + 0x14);
        ((void (__thiscall *)(void *))(*(void ***)obj)[0x2c / 4])(obj);
        n2 = FUN_00921580(n2);
    }
}

// ============================================================ cUIMissionCardList
struct cUIMissionCardList {
    u8     m_pad00[0x28];
    void **m_vec28;         // +0x28 vector begin
    void **m_vec2c;         // +0x2c vector end
    u8     m_pad30[0xc];
    void  *m_field3c;       // +0x3c
    void  *m_handler40;     // +0x40
    u32    m_h44, m_h48, m_h4c, m_h50; // +0x44..+0x50
    void  *m_field54;       // +0x54

    void ReleaseAll();                   // 0x00e180d0
    void RemoveHandlerAndRelease();      // 0x00e18340
};

// @ 0x00e180d0
void cUIMissionCardList::ReleaseAll()
{
    int n = (int)(m_vec2c - m_vec28);
    for (int i = 0; i < n; i++) {
        void *obj = m_vec28[i];
        ((void (__thiscall *)(void *))(*(void ***)obj)[0x1c / 4])(obj);
    }
    ((void (__thiscall *)(void *, void **, void **))FUN_00e25bd0)(&m_vec28, m_vec28, m_vec2c);
    if (m_field54 != 0) {
        void *lay = m_field54;
        ((void (__thiscall *)(void *, int))FUN_00811ad0)(lay, 1);
        if (lay != 0) {
            m_field54 = 0;
            ((void (__thiscall *)(void *))(*(void ***)lay)[2])(lay);
        }
    }
    if (m_field3c != 0) {
        void *h = m_field3c;
        ((void (__thiscall *)(void *))FUN_00e492d0)(h);
        if (h != 0) {
            m_field3c = 0;
            ((void (__thiscall *)(void *))(*(void ***)h)[3])(h);
        }
    }
}

// @ 0x00e18340
void cUIMissionCardList::RemoveHandlerAndRelease()
{
    ReleaseAll();
    if (m_handler40 != 0) {
        u32 h = (u32)m_handler40;
        m_handler40 = 0;
        FUN_00571db0(h, m_h44, m_h48, m_h4c, m_h50);
    }
}

// @ 0x00e17f40
void cUIMissionCard::Setup(void *mission, char a, char b)
{
    if (!((bool (__thiscall *)(void *, char))FUN_00e15060)(this, b)) {
        return;
    }
    if (mission != m_mission) {
        if (mission != 0) {
            ((void (__thiscall *)(void *))(*(void ***)mission)[0])(mission);
        }
        void *old = m_mission;
        m_mission = mission;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    UpdateDetails(0);
    void **vt = *(void ***)this;
    if (a != 0) {
        ((void (__thiscall *)(void *))vt[0x28 / 4])(this);
    } else {
        ((void (__thiscall *)(void *))vt[0x2c / 4])(this);
    }
}


// @ 0x00e17cf0
void cUIMissionCard::DoExpand()
{
    m_collapsed = 1;
    m_animated = 1;
    UpdateDetails(0);
    void *ms = MessageServer();
    ((void (__thiscall *)(void *, u32, void *))(*(void ***)ms)[0x14 / 4])(ms, 0xf46092d0, m_mission);
}

// @ 0x00e188b0
void *cUIMissionCardPanel::InitHints(void *param)
{
    void *raw = operator_new(0x18, 0x13f6b3c, 0, 0, 0, 0);
    void *obj = 0;
    if (raw != 0) {
        obj = ((void *(__thiscall *)(void *))FUN_00810000)(raw);
    }
    void *old = m_visObj;
    if (obj != old) {
        if (obj != 0) {
            ((void (__thiscall *)(void *))(*(void ***)obj)[1])(obj);
        }
        m_visObj = obj;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[2])(old);
        }
    }
    u32 key[3];
    key[0] = (u32)(unsigned long)param;
    key[1] = 0x510a95b;
    key[2] = 0x40464100;
    void *layout = m_visObj;
    if (((bool (__thiscall *)(void *, u32 *, bool, u32))FUN_008120d0)(layout, key, true, 0x8b96f855)) {
        ((void (__thiscall *)(void *, int))FUN_00810590)(layout, 0);
        void *w = ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(m_visObj, -1, true);
        return ((void *(__thiscall *)(void *, void *))(*(void ***)w)[0x104 / 4])(w, this);
    }
    if (m_visObj != 0) {
        m_visObj = 0;
        return ((void *(__thiscall *)(void *))(*(void ***)layout)[2])(layout);
    }
    return 0;
}

// @ 0x00e18980
void cUIMissionCardPanel::DestroyMembers()
{
    m_vtbl00 = (void **)0x14800bc;
    *(void **)((u8 *)this + 8) = (void *)0x14800a0;
    m_layout = (void *)0x1480098;
    void *base = (u8 *)this + 0x34;
    void *node = *(void **)base;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    if (m_treeBase40 != 0) {
        u32 h = (u32)m_treeBase40;
        m_treeBase40 = 0;
        FUN_00571db0(h, (u32)m_field3c, (u32)m_curMission, 0, 0);
    }
    if (m_field3c != 0) {
        ((void (__thiscall *)(void *))(*(void ***)m_field3c)[1])(m_field3c);
    }
    if (m_layout != 0) {
        ((void (__thiscall *)(void *))(*(void ***)m_layout)[2])(m_layout);
    }
    m_layout = (void *)0x13eb394;
    *(void **)((u8 *)this + 8) = (void *)0x13eb938;
    m_vtbl00 = (void **)0x13ec458;
}

// @ 0x00e18bb0
void *cUIMissionCardPanel::Construct()
{
    m_sub04 = 0;
    m_slotVtbl08 = (void *)0x14426a0;
    m_slotVtbl0c = (void *)0x13eb394;
    m_vtbl00 = (void **)0x14800bc;
    m_slotVtbl08 = (void *)0x14800a0;
    m_slotVtbl0c = (void *)0x1480098;
    m_field10 = 0xffffffff;
    m_field14 = 0;
    m_layout = 0;
    m_card = 0;
    m_treeBegin34 = (u8 *)this + 0x34;
    m_curMission = (u8 *)this + 0x34;
    u32 hash = 0x65ff54a;
    void *ms = MessageServer();
    m_handlerObj = ms;
    m_handlerArg1 = (void *)((u8 *)this + 0xc);
    m_handlerArg2 = &hash;
    m_handlerN = 1;
    m_handlerArg4 = 0;
    if (ms != 0 && m_handlerArg1 != 0) {
        ((void (__thiscall *)(void *, void *, void *))(*(void ***)ms)[0x24 / 4])(ms, m_handlerArg1, &hash);
    }
    return this;
}

// @ 0x00e18cb0
void cUIMissionCardPanel::SetSlotAndMission(u32 slot)
{
    void *out;
    ((void (__thiscall *)(void *, void **, u32 *))FUN_00e5c780)(
        (u8 *)this + 0x3c, &out, &slot);
    void *base = (u8 *)this + 0x40;
    if (out == base) {
        return;
    }
    void *m = *(void **)((u8 *)out + 0x14);
    if (m == 0) {
        return;
    }
    if (m_visObj != 0) {
        void *w = ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(m_visObj, (int)slot, true);
        if (w != 0) {
            void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)w)[0x0c / 4])(w, 0x8ed27e7a);
            if (sub != 0) {
                ((void (__thiscall *)(void *, int, int))(*(void ***)sub)[0x28 / 4])(sub, 4, 1);
            }
        }
    }
    m_treeBegin34 = (void *)slot;
    void *old = m_curMission;
    if (m != old) {
        if (m != 0) {
            ((void (__thiscall *)(void *))(*(void ***)m)[1])(m);
        }
        m_curMission = m;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[2])(old);
        }
    }
}

// @ 0x00e17fb0
bool cUIMissionCardPanel::RemoveMissionCard(void *mission)
{
    void **end = m_vec2c;
    for (void **it = m_vec28; it != end; ++it) {
        void *card = *it;
        if (card == 0) {
            continue;
        }
        void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)card)[0x0c / 4])(card, 0x334c6eec);
        if (sub == 0) {
            continue;
        }
        if (*(void **)((u8 *)sub + 0x9c) != mission) {
            continue;
        }
        if (m_field3c != 0) {
            if (((void *(__thiscall *)(void *))FUN_006c0200)(m_field3c) == sub) {
                ((void (__thiscall *)(void *, void *))FUN_00e49360)(m_field3c, 0);
            }
        }
        ((void (__thiscall *)(void *))(*(void ***)sub)[0x1c / 4])(sub);
        void **next = it + 1;
        if (next < m_vec2c) {
            FUN_006782c0(it, m_vec2c, next);
        }
        m_vec2c = m_vec2c - 1;
        void *tail = *m_vec2c;
        if (tail != 0) {
            ((void (__thiscall *)(void *))(*(void ***)tail)[1])(tail);
        }
        ((void (__thiscall *)(void *))FUN_00e14b70)(this);
        return true;
    }
    return false;
}

// @ 0x00e18150
void *cUIMissionCardPanel::AddMissionCard(u32 mission)
{
    void *raw = operator_new(0x9c, 0x13f6b3c, 0, 0, 0, 0);
    void *card = 0;
    if (raw != 0) {
        card = ((void *(__thiscall *)(void *))FUN_00e147a0)(raw);
    }
    void *addref = card;
    if (card != 0) {
        ((void (__thiscall *)(void *))(*(void ***)card)[0])(card);
    }
    if (m_vec2c < m_vec30) {
        void **slot = m_vec2c;
        m_vec2c = slot + 1;
        if (slot != 0) {
            *slot = card;
            if (card != 0) {
                ((void (__thiscall *)(void *))(*(void ***)card)[0])(card);
            }
        }
    } else {
        FUN_00aea5d0((void **)&m_vec28, m_vec2c, &addref);
    }
    if (addref != 0) {
        ((void (__thiscall *)(void *))(*(void ***)addref)[1])(addref);
    }
    ((void (__thiscall *)(void *, u32, u32))FUN_00e168d0)(card, mission, 0);
    ((void (__thiscall *)(void *))FUN_00e14b70)(this);
    return card;
}

// @ 0x00e18200
void *cUIMissionCardPanel::SetupMissionCard(void *mission, u32 a, u32 b, char c)
{
    void *raw = operator_new(0xa0, 0x13f6b3c, 0, 0, 0, 0);
    void *card = 0;
    if (raw != 0) {
        card = ((void *(__thiscall *)(void *))FUN_00e141a0)(raw);
    }
    void *addref = card;
    if (card != 0) {
        ((void (__thiscall *)(void *))(*(void ***)card)[0])(card);
    }
    if (m_vec2c < m_vec30) {
        void **slot = m_vec2c;
        m_vec2c = slot + 1;
        if (slot != 0) {
            *slot = card;
            if (card != 0) {
                ((void (__thiscall *)(void *))(*(void ***)card)[0])(card);
            }
        }
    } else {
        FUN_00aea5d0((void **)&m_vec28, m_vec2c, &addref);
    }
    if (addref != 0) {
        ((void (__thiscall *)(void *))(*(void ***)addref)[1])(addref);
    }
    ((cUIMissionCard *)card)->Setup(mission, (char)a, (char)b);
    ((void (__thiscall *)(void **, void **, u32))FUN_00e18050)(m_vec28, m_vec2c, b);
    ((void (__thiscall *)(void *))FUN_00e14b70)(this);
    if (c != 0) {
        if (m_field3c != 0) {
            ((void (__thiscall *)(void *, void *))FUN_00e49360)(m_field3c, card);
        } else {
            void *rawObj = operator_new(0xa4, 0x13f09b4, 0, 0, 0, 0);
            void *obj = 0;
            if (rawObj != 0) {
                obj = ((void *(__thiscall *)(void *))FUN_00e4a6e0)(rawObj);
            }
            void *old = m_field3c;
            if (obj != old) {
                if (obj != 0) {
                    ((void (__thiscall *)(void *))(*(void ***)obj)[2])(obj);
                }
                m_field3c = obj;
                if (old != 0) {
                    ((void (__thiscall *)(void *))(*(void ***)old)[3])(old);
                }
            }
            ((void (__thiscall *)(void *, void *))FUN_00e49a40)(m_field3c, card);
        }
    }
    return card;
}

// @ 0x00e18380
char cPanelHandler24::HandleMessage(u32 msg, void *arg)
{
    cUIMissionCardPanel *self = static_cast<cUIMissionCardPanel *>(this);
    if (msg == 0x38cf2fd) {
        void *p = *(void **)((u8 *)arg + 8);
        if (p == 0) {
            return 0;
        }
        void *mission = *(void **)((u8 *)p + 0x17c);
        if (mission == 0) {
            mission = p;
        }
        if (((bool (__thiscall *)(void *, void *))FUN_00e15cd0)(self, mission)) {
            if (((bool (__thiscall *)(void *))FUN_00c44c80)(mission)) {
                if (((bool (__thiscall *)(void *, void *, u32))FUN_00febe50)(GetMissionManager(), mission, 0)
                    || ((void *(__thiscall *)(void *))FUN_00febc70)(GetMissionManager()) == mission) {
                    self->UpdateCardDetails(mission);
                } else {
                    self->RemoveMissionCard(mission);
                }
            } else {
                self->RemoveMissionCard(mission);
            }
            return 0;
        }
        if (((bool (__thiscall *)(void *, void *, u32))FUN_00febe50)(GetMissionManager(), mission, 0)) {
            if ((u32)(unsigned long)SP_GetCurrentGameMode() == 0x1654c05) {
                self->SetupMissionCard(mission, 1, 1, 0);
            } else {
                u8 r = ((u8 (__thiscall *)(void *))(*(void ***)mission)[0x180 / 4])(mission);
                self->SetupMissionCard(mission, r, 1, 0);
            }
            return 0;
        }
        if (((void *(__thiscall *)(void *))FUN_00febc70)(GetMissionManager()) == mission) {
            if ((u32)(unsigned long)SP_GetCurrentGameMode() == 0x1654c05) {
                self->SetupMissionCard(mission, 1, 1, 0);
            } else {
                self->SetupMissionCard(mission, 1, 0, 0);
            }
        }
        return 0;
    }
    if (msg == 0x38cf2ff) {
        void *p = *(void **)((u8 *)arg + 8);
        self->RemoveMissionCard(p);
        return 0;
    }
    if (msg == 0xf46092d0) {
        void *p = *(void **)((u8 *)arg + 8);
        ((void (__thiscall *)(void *, void *))FUN_00e15c70)(self, p);
        // eax must be zero-extended on return (upper bits are compared).
        volatile int zero = 0;
        return (char)(zero + 1);
    }
    return 0;
}

// @ 0x00e184d0
void cUIMissionCardPanel::RefreshFromMissionList()
{
    if ((u32)(unsigned long)SP_GetCurrentGameMode() != 0x1654c05) {
        return;
    }
    void *list = ((void *(__thiscall *)(void *))FUN_00fedd50)(GetMissionManager());
    void **begin = *(void ***)list;
    int n = (int)(*(void ***)((u8 *)list + 4) - begin);
    for (int i = 0; i < n; i++) {
        void *m = begin[i];
        if (m == 0) {
            continue;
        }
        void *mission = *(void **)((u8 *)m + 0x17c);
        if (mission == 0) {
            mission = m;
        }
        if (((bool (__thiscall *)(void *, void *))FUN_00e15cd0)(this, mission)) {
            continue;
        }
        if ((mission != 0 && ((bool (__thiscall *)(void *, void *, u32))FUN_00febe50)(GetMissionManager(), mission, 0))
            || ((void *(__thiscall *)(void *))FUN_00febc70)(GetMissionManager()) == mission) {
            SetupMissionCard(mission, 0, 1, 0);
        }
    }
    void *o = ((void *(__thiscall *)(void *))FUN_00575ea0)(
        ((void *(__thiscall *)(void *))FUN_00bfc5f0)(SP_SpaceGameGet()));
    if (o != 0) {
        AddMissionCard((u32)o);
    }
}

// @ 0x00e18600
char cPanelMsg0c::OnMessage(u32 msg, void *arg)
{
    cUIMissionCardPanel *self = static_cast<cUIMissionCardPanel *>(this);
    char visible = 0;
    if (msg != 0x65ff54a || m_layout == 0) {
        return visible;
    }
    if (*(u32 *)((u8 *)arg + 0x10) != 0x40464100) {
        return visible;
    }
    void *mission = *(void **)((u8 *)arg + 0x18);
    u32 key = m_field10;
    void *cur = ((void *(__thiscall *)(void *, u32))self->m_vtbl00[0x30 / 4])(self, key);
    if (mission != cur) {
        return visible;
    }
    u32 saved14 = (u32)(unsigned long)m_field14;
    void *layout = m_layout;
    u32 savedCard = (u32)(unsigned long)m_card;
    u32 r570 = (u32)(unsigned long)((void *(__thiscall *)(void *))FUN_00810570)(layout);
    visible = ((bool (__thiscall *)(void *))FUN_00810070)(layout) ? 1 : 0;
    if (visible) {
        ((void (__thiscall *)(void *))self->m_vtbl00[0x20 / 4])(self);
    }
    ((void (__thiscall *)(void *))self->m_vtbl00[0x14 / 4])(self);
    ((void (__thiscall *)(void *, u32, u32, u32, u32))self->m_vtbl00[0x10 / 4])(
        self, key, saved14, r570, savedCard);
    if (visible) {
        ((void (__thiscall *)(void *, u32))self->m_vtbl00[0x1c / 4])(self, 0);
    }
    return 1;
}

// @ 0x00e186d0
void cUIMissionCardPanel::OnNotify(u32 a, u32 b, u32 c, u32 d)
{
    (void)c;
    (void)d;
    ((void (__thiscall *)(void *))m_vtbl00[0x14 / 4])(this);
    u32 r = ((u32 (__thiscall *)(void *, u32))m_vtbl00[0x30 / 4])(this, a);
    u32 key0 = a;
    u32 key1 = 0x510a95b;
    u32 key2 = 0x40464100;
    (void)key0;
    (void)key1;
    (void)key2;
    void *raw = operator_new(0x18, 0x13f6b3c, 0, 0, 0, 0);
    void *obj = 0;
    if (raw != 0) {
        obj = ((void *(__thiscall *)(void *))FUN_00810000)(raw);
    }
    m_field10 = a;
    m_field14 = (void *)(unsigned long)b;
    void *old = m_layout;
    if (obj != old) {
        if (obj != 0) {
            ((void (__thiscall *)(void *))(*(void ***)obj)[1])(obj);
        }
        m_layout = obj;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[2])(old);
        }
    }
    u32 k[3];
    k[0] = a;
    k[1] = 0x510a95b;
    k[2] = 0x40464100;
    if (!((bool (__thiscall *)(void *, u32 *, bool, u32))FUN_008120d0)(m_layout, k, false, 0x5b598fa)) {
        ((void (__thiscall *)(void *, u32))FUN_00811ad0)(m_layout, 1);
        if (m_layout != 0) {
            m_layout = 0;
            ((void (__thiscall *)(void *))(*(void ***)obj)[2])(obj);
        }
    }
    ((bool (__thiscall *)(void *, void *, bool, u32))FUN_008121b0)(m_layout, (void *)r, true, 0x5b598fa);
    ((void (__thiscall *)(void *, int))FUN_00810590)(m_layout, 0);
    void *w = ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(
        m_layout, (int)((u32 (__thiscall *)(void *, u32))m_vtbl00[0x34 / 4])(this, a), true);
    if (w != 0) {
        ((void (__thiscall *)(void *, void *))(*(void ***)w)[0x104 / 4])(w, (u8 *)this + 8);
    }
    void *oldCard = m_card;
    if ((void *)r != oldCard) {
        if (r != 0) {
            ((void (__thiscall *)(void *))(*(void ***)r)[0])((void *)r);
        }
        m_card = (void *)r;
        if (oldCard != 0) {
            ((void (__thiscall *)(void *))(*(void ***)oldCard)[1])(oldCard);
        }
    }
}

