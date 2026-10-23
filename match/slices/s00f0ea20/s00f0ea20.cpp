// slice s00f0ea20 -- SP::cSPUISpace posse / minimap / verb-tray UI handlers.
//
// Retail build: VS2008 era (cl 15).  Every entry point here is a __thiscall
// member (this arrives in ECX), so the whole group is modelled as member
// functions of the owning UI classes.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

#include "types.h"
#include <math.h>

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// external callees (bodies live in other slices / are still stubs)
// ---------------------------------------------------------------------------
void* SP_NounManager();                              // 0x00b3d300
void* SP_App();                                      // 0x0067dd10
void* EA_Audio_GetSystemAT();                        // 0x00a206f0
void* SP_GameTimeManager(int);                       // 0x00b3d380
void* GetRecorderState();                            // 0x00435e90
void  SP_KillSetiEffects();                          // 0x00435ed0
void  SP_SetTimeFlowSetting(int);                    // 0x00b32450
void* EA_InterfaceCast(void*, ...);                  // 0x005ca960
void  SP_SetTooltipText(void*, void*);               // 0x00806de0
bool  VerbTray_HandleRebuild(void*, void*);          // 0x00d4a570
void  FUN_00d20950(uint);                            // 0x00d20950
void  FUN_00d491b0(int);                             // 0x00d491b0
bool  FUN_00d49820(void*);                           // 0x00d49820
void* FUN_00b60a50(void*);                           // 0x00b60a50
void  FUN_00ed4890(uint);                            // 0x00ed4890
void  FUN_00ef1360();                                // 0x00ef1360
void  FUN_00f19050();                                // 0x00f19050
void  FUN_00f1aae0(int);                             // 0x00f1aae0
void  FUN_00f1dd90(int);                             // 0x00f1dd90
void  FUN_00f1de30(int);                             // 0x00f1de30
void  FUN_00f1f4e0(int);                             // 0x00f1f4e0
void* FUN_00f3be30();                                // 0x00f3be30
void  operator_delete(void*);                        // 0x00f47380
void* EAAllocate(uint, const char*, int, int, int, int);   // 0x00f473a0
void  RBTreeInsert(void*, void*, void*, int);        // 0x009216a0
void* RBTreeIncrement(void*);                        // 0x00921580
void  RBTreeErase(void*, void*);                     // 0x00921880
void* FUN_009512c0();                                // 0x009512c0
void* FUN_009512d0(int, int, const char*, void*);    // 0x009512d0
void* FUN_00d539d0();                                // 0x00d539d0
uint  FUN_00d52e10(void*);                           // 0x00d52e10
float FUN_00bfc490(int, int);                        // 0x00bfc490
void* FUN_00b204d0(uint);                            // 0x00b204d0
void* FUN_00f3be60(void*);                           // 0x00f3be60
void* FUN_00f19660(void*, int);                      // 0x00f19660
bool  FUN_00f19c80(float);                           // 0x00f19c80
int   FUN_00cCombatant_GetDamageState(void*);
void  FUN_00e0df70(uint, void*, int);                // 0x00e0df70
void  FUN_00e0c490(void*, void*);                    // 0x00e0c490
void* FUN_00e0acf0();                                // 0x00e0acf0
void  FUN_00e0c1f0(void*);                           // 0x00e0c1f0
void  FUN_00e0e1a0();                                // 0x00e0e1a0
uint  GetFileCount();                                // 0x008e7f80
void  FUN_00d2ba90(void*);                           // 0x00d2ba90
void* IsMaxValue(void*, int, int);

extern uint8_t DAT_015ad6cc;                         // 0x015ad6cc
extern uint8_t DAT_015ad6d8;                         // 0x015ad6d8
extern uint8_t DAT_01186577;                         // 0x01186577
extern uint8_t DAT_016c7aa4;                         // 0x016c7aa4
extern uint8_t g_allocFileHdr;                       // 0x013ebb38
extern uint8_t g_allocTag;                           // 0x013f09b4
extern float   g_15ad5ec;                            // 0x015ad5ec

// ---------------------------------------------------------------------------
// UI classes
// ---------------------------------------------------------------------------
struct cSPUIPosse
{
    uint8_t   pad00[0xa4];
    uint64_t* itemsBegin;                            // +0xa4
    uint64_t* itemsEnd;                              // +0xa8

    void* FindItem(void* item);                      // 0x00e24c90
};

struct cSPUIMinimapWin
{
    void RemoveAllIcons();                           // 0x00e0fb50
    void FUN_00e0ad00(int);                          // 0x00e0ad00
    void RemoveIcon(void* id, int a, int b);         // 0x00e0f9c0
};

struct cGameNounManager
{
    void* GetItemID();                               // 0x00b1f9c0
    void* GetAvatar();                               // 0x00b1fdb0
};

struct cSPUIGlobalUI
{
    void* FindWindowByID(int id);                    // 0x00e012b0
};

struct UI_PosseItem
{
    void* ctor(void* item, void* dat);               // 0x00e25a60
};

struct UI_PosseItemGhost
{
    void* ctor(void* dat);                           // 0x00e25ad0
};

struct cString
{
    uint8_t buf[0x18];
    void        ctor();                              // 0x006b5060
    void        dtor();                              // 0x006b5240
    void        Load(uint a, uint b, int c);         // 0x006b54b0
    const void* c_str();                             // 0x006b55c0
};

struct cGonzagoTimer
{
    void Dtor();                                     // 0x00b638b0
};

struct PHTable
{
    uint8_t pad[0x1c];
    void FreeBuckets(void** first, uint count);      // 0x00a24480
};

// eastl red-black tree anchor (the object at this+0x2ec)
struct MinimapTree
{
    uint8_t  pad0[4];
    void*    left;                                   // +0x04
    void*    right;                                  // +0x08
    void*    parent;                                 // +0x0c
    uint8_t  color;                                  // +0x10
    uint8_t  pad11[3];
    uint32_t size;                                   // +0x14

    void Nuke(void* root);                           // 0x009a9600
};

// eastl red-black tree used by the posse insert helper
struct RBTree
{
    uint8_t  pad0[4];
    void*    left;                                   // +0x04 (anchor)
    uint8_t  pad8[0x0c];                             // +0x08 .. +0x13
    uint32_t count;                                  // +0x14

    void Insert(void** out, void* parent, uint32_t* key, char flag);
};

// the owner of the posse / minimap state
struct cSPUISpace
{
    uint8_t          pad00[0x60];
    cSPUIPosse*      posse;                          // +0x60
    uint8_t          pad64[0x2dc - 0x64];
    void*            field_2dc;                      // +0x2dc
    cSPUIMinimapWin* minimap;                        // +0x2e0
    float            timer;                          // +0x2e4
    uint8_t          flag_2e8;                       // +0x2e8
    uint8_t          pad2e9[3];
    MinimapTree      tree;                           // +0x2ec

    void RemovePosseUIForUFO(void* item);
    void RefreshGhostItems();
    void RemovePosseMember(void* item);
    void ResetMinimap();
    void UpdateIcons(float dt);
    void Destructor();
};

// ---------------------------------------------------------------------------
// small vtable-call helpers (inline so the call shape survives)
// ---------------------------------------------------------------------------
static inline void  vt_call0(void* o, int off)
{
    (*(void (__thiscall**)(void*))(*(char**)o + off))(o);
}
static inline void* vt_call1(void* o, int off, void* a)
{
    return (*(void* (__thiscall**)(void*, void*))(*(char**)o + off))(o, a);
}
static inline uint  vt_callU(void* o, int off)
{
    return (*(uint (__thiscall**)(void*))(*(char**)o + off))(o);
}
static inline float neg_nan()
{
    uint32_t u = 0xffc00000u;
    float f;
    *(uint32_t*)&f = u;
    return f;
}

// ---------------------------------------------------------------------------
// 0x00f0ea20 -- UI message dispatcher (SP::cCreatureDisplayStrategy::DoMessage)
// ---------------------------------------------------------------------------
struct cCreatureDisplayStrategy
{
    uint8_t pad00[0x24];
    void*   globalUI;                                // +0x24

    uint32_t DoMessage(uint32_t msg, int* data);
};

// @ 0x00f0ea20
uint32_t cCreatureDisplayStrategy::DoMessage(uint32_t msg, int* data)
{
    uint32_t r = msg;
    uint32_t code = (uint32_t)data[2];
    if (code < 0x1c)
    {
        if (code == 0x1b)
        {
            int id = (int)vt_callU((void*)data[1], 0x1c);
            if ((uint32_t)(id + 0xfb354a92u) < 4)
            {
                void* sys = EA_Audio_GetSystemAT();
                if (sys != 0)
                {
                    vt_call0(sys, 0x20);
                    SP_KillSetiEffects();
                    return 0;
                }
                SP_KillSetiEffects();
                return 0;
            }
        }
        else if (code == 6)
        {
            void* a = SP_App();
            a = vt_call1(a, 0x50, 0);
            a = vt_call1(a, 0x38, 0);
            if (a != 0)
            {
                void* w = vt_call1(a, 0xc, (void*)0x2a7ecd2);
                if (w != 0)
                {
                    int id = (int)vt_callU((void*)data[1], 0x1c);
                    switch (id + -0x4cab56e)
                    {
                    case 0: r = 2; break;
                    case 1: r = 1; break;
                    case 2: r = 4; break;
                    case 3: r = 5; break;
                    default: return 0;
                    }
                    FUN_00d20950(r);
                    GetRecorderState();
                    SP_KillSetiEffects();
                    return 0;
                }
            }
        }
        else if (code == 7)
        {
            int id = (int)vt_callU((void*)data[1], 0x1c);
            if ((uint32_t)(id + 0xfb354a92u) < 4)
            {
                void* a = SP_App();
                a = vt_call1(a, 0x50, 0);
                void* b = vt_call1(a, 0x38, 0);
                void* c = FUN_00b60a50(b);
                if (c != 0)
                {
                    FUN_00d20950(0);
                    return 0;
                }
            }
        }
        else if (code == 0xd)
        {
            if (VerbTray_HandleRebuild((void*)msg, (void*)data[6]))
                return 1;
        }
    }
    else if (code == 0x7e1a521)
    {
        int t = (int)vt_callU((void*)*data, 0x1c);
        if (t == 0x7e495e0)
        {
            if (*data != 0 && (vt_callU((void*)*data, 0x28) & 1) != 0)
                return 0;
            if (*data != 0)
                (*(void (__thiscall**)(void*, int, int))(*(char**)*data + 0x7c))((void*)*data, 1, 1);
            FUN_00d491b0(0);
        }
    }
    else if (code == 0x287259f6)
    {
        if (FUN_00d49820((void*)data[3]))
            return 1;
        int id = data[3];
        if (id < 0x74b6422)
        {
            if (id == 0x74b6421)
            {
                r = 1;
                SP_GameTimeManager(1);
                SP_SetTimeFlowSetting(r);
                return 1;
            }
            if (id < 0x7104133)
            {
                if (id == 0x7104132)
                {
                    FUN_00f19050();
                    r = 2;
                }
                else
                {
                    if (id == 0x2c38aba)
                    {
                        GetRecorderState();
                        SP_KillSetiEffects();
                        FUN_00f1aae0(4);
                        return 1;
                    }
                    if (id == 0x562a141)
                    {
                        void* w = ((cSPUIGlobalUI*)globalUI)->FindWindowByID(0x34c963f);
                        void* btn = EA_InterfaceCast(w);
                        if (btn == 0)
                            return 1;
                        void* rec = GetRecorderState();
                        SP_KillSetiEffects();
                        void* o = EA_InterfaceCast((void*)msg, (void*)0xe76c9b4f, rec);
                        uint32_t v = vt_callU(o, 0x20);
                        msg = (msg & 0xffffff01u) | ((v >> 2 & 1) << 8);
                        (*(void (__thiscall**)(void*, int, uint32_t))(*(char**)btn + 0x28))(btn, 4, msg);
                        cString cs;
                        cs.ctor();
                        uint32_t which = (v >> 2 & 1) == 0 ? 0x615ffa7 : 0x615ffa8;
                        cs.Load(0xc0152a6d, which, 0);
                        void* txt = IsMaxValue(&cs, -1, 0);
                        SP_SetTooltipText(rec, txt);
                        cs.c_str();
                        cs.dtor();
                        return 1;
                    }
                    if (id != 0x7104130)
                        return 0;
                    FUN_00f19050();
                    r = 0;
                }
                FUN_00ed4890(r);
                FUN_00ef1360();
            }
            else if (id == 0x74b5328)
            {
                GetRecorderState();
                SP_KillSetiEffects();
                int n = *(int*)(*(int*)(*(int*)&DAT_016c7aa4 + 0x78) + 0xb8);
                if (0 < n)
                {
                    FUN_00f1f4e0(n + -1);
                    return 1;
                }
            }
            else
            {
                if (id != 0x74b5329)
                {
                    int d = id + -0x74b6420;
                    if (d != 0)
                        return 0;
                    SP_GameTimeManager(0);
                    SP_SetTimeFlowSetting(d);
                    return 1;
                }
                GetRecorderState();
                SP_KillSetiEffects();
                int tot = (int)FUN_00f3be30();
                int n = *(int*)(*(int*)(*(int*)&DAT_016c7aa4 + 0x78) + 0xb8);
                if (n < tot + -1)
                {
                    FUN_00f1f4e0(n + 1);
                    return 1;
                }
            }
            return 1;
        }
        if (id < 0x792dcc8)
        {
            if (id == 0x792dcc7) { FUN_00f1dd90(2); return 1; }
            if (id == 0x74b6422)
            {
                r = 2;
                SP_GameTimeManager(2);
                SP_SetTimeFlowSetting(r);
                return 1;
            }
            if (id == 0x792dcc5) { FUN_00f1dd90(0); return 1; }
            if (id == 0x792dcc6) { FUN_00f1dd90(1); return 1; }
        }
        else
        {
            if (id == 0x792dd06) { FUN_00f1de30(0); return 1; }
            if (id == 0x792dd07) { FUN_00f1de30(1); return 1; }
            if (id == 0x792dd08) { FUN_00f1de30(2); return 1; }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f0ef40 -- drop one posse item's UI
// ---------------------------------------------------------------------------
// @ 0x00f0ef40
void cSPUISpace::RemovePosseUIForUFO(void* item)
{
    if (this->posse == 0)
        return;
    void* it = this->posse->FindItem(item);
    if (it == 0)
        return;
    (*(void (__thiscall**)(void*, void*, int))(*(char**)this->posse + 0xa8))(this->posse, it, 1);
    uint64_t** begin = &this->posse->itemsBegin;
    if (begin[1] - begin[0] != 0)
        return;
    (*(void (__thiscall**)(void*, int))(*(char**)this->posse + 0xc0))(this->posse, 0);
}

// ---------------------------------------------------------------------------
// 0x00f0efa0 -- spawn ghost icons for every posse item not shown yet
// ---------------------------------------------------------------------------
// @ 0x00f0efa0
void cSPUISpace::RefreshGhostItems()
{
    if (this->posse == 0)
        return;
    cGameNounManager* nouns = (cGameNounManager*)SP_NounManager();
    uint32_t* v = (uint32_t*)nouns->GetItemID();
    uint32_t* end = (uint32_t*)v[1];
    for (uint32_t* it = (uint32_t*)*v; it != end; ++it)
    {
        void* p = this->posse->FindItem((void*)*it);
        if (p != 0)
        {
            float f = (float)(FUN_00bfc490(1, 1) * 100.0f);
            (*(void (__thiscall**)(void*, int, float))(*(char**)p + 0x80))(p, 0x3d99162, f);
        }
    }
    int n = (*(int*)((char*)this->posse + 0xa8) - *(int*)((char*)this->posse + 0xa4)) >> 3;
    uint32_t c = FUN_00d52e10(FUN_00d539d0());
    if ((uint32_t)n < c)
    {
        void* a = FUN_009512c0();
        void* pi = (void*)FUN_009512d0(0x14c, 4, "UI/PosseItemGhostShell", a);
        if (pi != 0)
            pi = ((UI_PosseItemGhost*)pi)->ctor(&DAT_015ad6d8);
        else
            pi = 0;
        (*(void (__thiscall**)(void*, void*))(*(char**)this->posse + 0xa4))(this->posse, pi);
        (*(void (__thiscall**)(void*, int))(*(char**)this->posse + 0xc0))(this->posse, 1);
    }
}

// ---------------------------------------------------------------------------
// 0x00f0f0a0 -- add a posse member and its UI item
// ---------------------------------------------------------------------------
// @ 0x00f0f0a0
void cSPUISpace::RemovePosseMember(void* item)
{
    if (this->posse == 0 || this->posse->FindItem(item) != 0)
        return;
    RemovePosseUIForUFO(0);
    void* a = FUN_009512c0();
    void* pi = (void*)FUN_009512d0(0x14c, 4, "UI/PosseItem", a);
    if (pi != 0)
        pi = ((UI_PosseItem*)pi)->ctor(item, &DAT_015ad6cc);
    else
        pi = 0;
    (*(void (__thiscall**)(void*, void*))(*(char**)this->posse + 0xa4))(this->posse, pi);
    (*(void (__thiscall**)(void*, int))(*(char**)this->posse + 0xc0))(this->posse, 1);
    uint32_t* src = (uint32_t*)(*(uint8_t**)((char*)item + 0xb20) + 0x504);
    struct { uint32_t a, b, c; } tmp;
    tmp.a = src[0];
    tmp.b = src[1];
    tmp.c = src[2];
    tmp.b = 0x2f7d0004;
    (*(void (__thiscall**)(void*, void*, int))(*(char**)pi + 0x90))(pi, &tmp, 0);
}

// ---------------------------------------------------------------------------
// 0x00f0f170 -- eastl rbtree node insert (allocate + link)
// ---------------------------------------------------------------------------
// @ 0x00f0f170
void RBTree::Insert(void** out, void* parent, uint32_t* key, char flag)
{
    uint32_t side;
    if (flag == 0 && parent != (void*)((char*)this + 4) &&
        *key >= *(uint32_t*)((char*)parent + 0x10))
        side = 1;
    else
        side = 0;
    void* n = EAAllocate(0x1c, (const char*)&g_allocTag, 0, 0, (int)(size_t)&g_allocFileHdr, 0xd1);
    uint32_t* dst = (uint32_t*)((char*)n + 0x10);
    if (dst != 0)
    {
        dst[0] = key[0];
        dst[1] = key[1];
        dst[2] = key[2];
    }
    RBTreeInsert(n, parent, (char*)this + 4, (int)side);
    ++count;
    *out = n;
}

// ---------------------------------------------------------------------------
// 0x00f0f290 -- tear down the minimap window and the icon rbtree
// ---------------------------------------------------------------------------
// @ 0x00f0f290
void cSPUISpace::ResetMinimap()
{
    if (this->minimap != 0)
    {
        this->minimap->RemoveAllIcons();
        this->minimap->FUN_00e0ad00(4);
        void* m = (void*)this->minimap;
        void* slot = m != 0 ? (char*)m + 4 : 0;
        void* inner = *(void**)((char*)m + 4);
        void* fn = *(void**)((char*)inner + 0x10);
        void* r = ((void* (__thiscall*)(void*))fn)((char*)m + 4);
        (*(void (__thiscall**)(void*, void*))(*(char**)r + 0xe0))(r, slot);
        if (this->minimap != 0)
        {
            cSPUIMinimapWin* old = this->minimap;
            this->minimap = 0;
            (*(void (__thiscall**)(void*))(*(char**)old + 4))(old);
        }
        this->timer = 0.0f;
        this->flag_2e8 = 0;
    }
    void* root = *(void**)((char*)this + 0x2f8);
    MinimapTree* t = (MinimapTree*)((char*)this + 0x2ec);
    t->Nuke(root);
    void** p = &t->left;
    t->parent = 0;
    t->color  = 0;
    t->size   = 0;
    t->right  = p;
    t->left   = p;
}

// ---------------------------------------------------------------------------
// 0x00f0f330 -- per-frame icon update
// ---------------------------------------------------------------------------
// @ 0x00f0f330
void cSPUISpace::UpdateIcons(float dt)
{
    cGameNounManager* nouns = (cGameNounManager*)SP_NounManager();
    void* avatar = nouns->GetAvatar();
    if (this->minimap == 0 || avatar == 0)
        return;

    float cxLast = 0.0f;
    void* piVar1 = (char*)avatar + 0xc0;
    float* pfVar7 = (float*)(*(void* (__thiscall**)(void*))(*(char**)piVar1 + 0x2c))(piVar1);
    dt = this->timer - dt;
    this->timer = dt;
    if (dt <= 0.0f)
    {
        this->timer = 5.0f;
        float f14 = pfVar7[0];
        float f3 = sqrtf(f14 * f14 + pfVar7[1] * pfVar7[1] + pfVar7[2] * pfVar7[2]);
        if (1.5258789e-05f < f3)
        {
            float f16 = (1.0f / f3) * g_15ad5ec;
            float s = 1.0f / (f3 + 1.5258789e-05f);
            float cx = f14 * s;
            float cy = pfVar7[1] * s;
            float cz = pfVar7[2] * s;
            cxLast = cx;
            float* pfVar8 = (float*)FUN_00e0acf0();
            if (f16 * f16 <
                ((pfVar8[0] - cx) * (pfVar8[0] - cx) +
                 (pfVar8[2] - cz) * (pfVar8[2] - cz)) +
                 (pfVar8[1] - cy) * (pfVar8[1] - cy))
                FUN_00e0c1f0(pfVar7);
        }
    }

    float best = neg_nan();
    void* n = FUN_00f3be60(*(void**)(*(int*)(*(int*)&DAT_016c7aa4 + 0x78) + 0xb8));
    int iEnd = *(int*)((char*)n + 0x88);
    float i = 0.0f;
    float cur = best;
    for (int e = *(int*)((char*)n + 0x84); (best = cur), e != iEnd; e += 0x188)
    {
        if (FUN_00f19c80(i) == 0)
        {
            void* child = (void*)FUN_00f19660(*(void**)((char*)e + 4), 0);
            best = i;
            if (child != 0)
                break;
            best = cur;
            if (cur == neg_nan())
                best = i;
        }
        i = (float)((int)i + 1);
        cur = best;
    }
    FUN_00e0df70(0x79965de, (void*)(*(int*)(*(int*)(*(int*)&DAT_016c7aa4 + 0x74) + 0x10) + 0x150), 0);

    int node = *(int*)((char*)this + 0x2f4);
    if (node != (int)((char*)this + 0x2f0))
    {
        int next;
        do
        {
            void* uVar13 = *(void**)(node + 0x14);
            float fStack_8 = *(float*)(node + 0x18);
            void* uVar2 = *(void**)(node + 0x10);
            int* piVar10 = (int*)FUN_00b204d0((uint)(size_t)uVar13);
            if (piVar10 == 0)
            {
            LAB_remove:
                this->minimap->RemoveIcon(uVar2, 1, 0);
                *(int*)((char*)this + 0x300) = *(int*)((char*)this + 0x300) + -1;
                next = (int)RBTreeIncrement((void*)node);
            LAB_erase:
                RBTreeErase((void*)node, (char*)this + 0x2f0);
                operator_delete((void*)node);
            }
            else
            {
                char cVar4 = (char)(*(uint (__thiscall**)(void*))(*(char**)piVar10 + 0x2c))(piVar10);
                if (cVar4 != 0)
                {
                LAB_remove2:
                    this->minimap->RemoveIcon(uVar2, 1, 0);
                    *(int*)((char*)this + 0x300) = *(int*)((char*)this + 0x300) + -1;
                    next = (int)RBTreeIncrement((void*)node);
                    goto LAB_erase;
                }
                bool bVar15 = fStack_8 != neg_nan();
                if (bVar15 && FUN_00f19c80(fStack_8))
                {
                    this->minimap->RemoveIcon(uVar2, 1, 0);
                    *(int*)((char*)this + 0x300) = *(int*)((char*)this + 0x300) + -1;
                    next = (int)RBTreeIncrement((void*)node);
                    goto LAB_erase;
                }
                int* p = (int*)(*(void* (__thiscall**)(void*, int))(*(char**)piVar10 + 0xc))(piVar10, (int)0xd0036e08);
                if (p != 0 && !bVar15 &&
                    FUN_00cCombatant_GetDamageState((char*)p + 0x5a8) == 2)
                    goto LAB_remove;
                p = (int*)(*(void* (__thiscall**)(void*, int))(*(char**)piVar10 + 0xc))(piVar10, (int)0x137e8e0);
                if (p != 0 && !bVar15 &&
                    FUN_00cCombatant_GetDamageState((char*)p + 0x508) == 2)
                    goto LAB_remove2;
                piVar10 = (int*)(*(void* (__thiscall**)(void*, void*))(*(char**)piVar10 + 0xc))(piVar10, &DAT_01186577);
                if (piVar10 != 0)
                {
                    void* uVar12;
                    void* uVar13b;
                    if (bVar15 && best == fStack_8)
                    {
                        uVar12 = (void*)1;
                        uVar13b = (void*)1;
                    }
                    else
                    {
                        uVar12 = 0;
                        uVar13b = 0;
                    }
                    uVar12 = (*(void* (__thiscall**)(void*, void*))(*(char**)piVar10 + 0x2c))(piVar10, uVar12);
                    FUN_00e0df70((uint)(size_t)uVar2, uVar12, (int)(size_t)uVar13b);
                }
                next = (int)RBTreeIncrement((void*)node);
            }
            node = next;
        } while (next != (int)((char*)this + 0x2f0));
    }

    void* v = (*(void* (__thiscall**)(void*, void*))(*(char**)piVar1 + 0x5c))(piVar1, (void*)&cxLast);
    FUN_00e0c490(piVar1, v);
    if ((GetFileCount() >> 0x18) != 0)
    {
        this->flag_2e8 = 0;
        this->minimap->FUN_00e0ad00(4);
        FUN_00e0e1a0();
    }
}

// ---------------------------------------------------------------------------
// 0x00f0f740 -- destructor
// ---------------------------------------------------------------------------
// @ 0x00f0f740
void cSPUISpace::Destructor()
{
    void** p = (void**)this;
    p[0]    = (void*)0x148bd60;
    p[0xe]  = (void*)0x148bd44;
    p[0xf]  = (void*)0x148bd34;
    p[0x10] = (void*)0x148bd24;
    this->tree.Nuke(*(void**)((char*)this + 0x2f8));
    if (this->minimap != 0)
        (*(void (__thiscall**)(void*))(*(char**)this->minimap + 4))(this->minimap);
    if (this->field_2dc != 0)
        (*(void (__thiscall**)(void*))(*(char**)this->field_2dc + 0x64))(this->field_2dc);
    {
        PHTable* t = (PHTable*)((char*)this + 0x14c);
        t->FreeBuckets((void**)*(void**)((char*)this + 0x150), *(uint*)((char*)this + 0x154));
        void* first = *(void**)((char*)this + 0x150);
        *(uint*)((char*)this + 0x158) = 0;
        if (*(uint*)((char*)this + 0x154) > 1 && first != *(void**)((char*)this + 0x17c))
        {
            if (first < *(void**)((char*)this + 0x170) || *(void**)((char*)this + 0x174) <= first)
                operator_delete(first);
            else
            {
                *(void**)first = *(void**)((char*)this + 0x168);
                *(void**)((char*)this + 0x168) = first;
            }
        }
    }
    if (*(void**)((char*)this + 0x148) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x148) + 4))(*(void**)((char*)this + 0x148));
    if (*(void**)((char*)this + 0x144) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x144) + 4))(*(void**)((char*)this + 0x144));
    if (*(void**)((char*)this + 0x140) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x140) + 4))(*(void**)((char*)this + 0x140));
    if (*(void**)((char*)this + 0x12c) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x12c) + 4))(*(void**)((char*)this + 0x12c));
    if (*(void**)((char*)this + 0x128) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x128) + 4))(*(void**)((char*)this + 0x128));
    FUN_00d2ba90((char*)this + 0xb0);
    ((cGonzagoTimer*)((char*)this + 0x90))->Dtor();
    ((cGonzagoTimer*)((char*)this + 0x70))->Dtor();
    if (*(void**)((char*)this + 0x68) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x68) + 4))(*(void**)((char*)this + 0x68));
    if (*(void**)((char*)this + 0x64) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x64) + 4))(*(void**)((char*)this + 0x64));
    if (*(void**)((char*)this + 0x50) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x50) + 4))(*(void**)((char*)this + 0x50));
    if (*(void**)((char*)this + 0x4c) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x4c) + 0x64))(*(void**)((char*)this + 0x4c));
    if (*(void**)((char*)this + 0x48) != 0)
        (*(void (__thiscall**)(void*))(*(char**)*(void**)((char*)this + 0x48) + 4))(*(void**)((char*)this + 0x48));
    p[0x10] = (void*)0x13ec458;
    p[0xf]  = (void*)0x13eb394;
    p[0xe]  = (void*)0x13eb938;
}
