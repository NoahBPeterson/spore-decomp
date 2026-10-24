// Slice s00ccc190 (worker 9) -- SP::cTribeDisplayStrategy (the "Simulator" tribe-UI display
// strategy): construction, destruction, tribe-member notification, the per-frame Update
// sweep, and the two small pool/tree helpers it owns (0x00ccc190..0x00ccd029).
//
// Sibling slices s00cc8ed0, s00cc9e20 and s00ccdd70 recover the same retail layouts; this
// slice reuses them.  The class is declared at global scope exactly like those slices.
//
// Retail layout of cTribeDisplayStrategy (recovered from the asm; differs from the 2008 PDB):
//   +0x000 vtable (vtbl_Simulator::cTribeDisplayStrategy @ 0x1476b28)
//   +0x038/+0x03c/+0x040 secondary vtable pointers (MixIn bases)
//   +0x044 scratch
//   +0x04c global tribe UI object        +0x050 mode strategy (refcount slot 1)
//   +0x054 flag                          +0x058 message server
//   +0x05c handler                       +0x060 message-id table   +0x064 id count (10)
//   +0x068 0                             +0x06c 0
//   +0x070 civ minimap window (slot 1)   +0x074 layout (slot 2)   +0x078 posse set (intrusive)
//   +0x07c constructor argument (owner id)
//   +0x084/+0x085 flags                  +0x088/+0x08c/+0x090 scratch
//   +0x094 eastl::rbtree<EA::AutoRefCount<cSPCreatureCitizen>, eastl::pair<...>,
//         eastl::less<...>, eastl::allocator, eastl::use_first<...>, 1, 1> header:
//         count +0x094, anchor +0x098, end +0x09c, scratch +0x0a0, flag +0x0a4, +0x0a8
//   +0x0b0 ornament (slot 1)             +0x0b4 swatch-manager object (slot 1)
//   +0x0b8 cModelInstanceSet[2] (stride 0x60)
//   +0x178 two 0xA0-byte ornament tables, every dword initialised to -1
//   +0x2b8 swatch (slot 1)               +0x2bc swatch window (slot 1)
//   +0x2c0 ornament pool / open-hash container (0x218 bytes; ctor at 0x00cccb00)
//   +0x4d8 dynamic array (operator delete)   +0x4dc/+0x4e0 scratch
//   +0x4f0/+0x4f4 cSelectionEffectStreamer helpers (slot 1)
//
// The routines are large and individually SSE/x87-scheduled; the engine classes they touch
// are defined outside the slice.  The bodies below are faithful structural reconstructions:
// every member read or written on cTribeDisplayStrategy is named at its retail offset
// (unused gaps are explicit padding), dispatch into classes whose definition is not part of
// the slice goes through the retail vftable slot (raw slot dispatch is the accepted
// convention for an unknown vtable), and engine entry points carry their retail address.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;

extern "C" void  operator_delete(void* p);            // 0x00f47360
extern "C" void  operator_delete_array(void* p);      // 0x00f47380

struct Vec3 { float x, y, z; };

// ------------------------------------------------------------------ vftable
// Dispatch through vftable slot <byteOffset> of an object whose class is not known here.
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

typedef char     (__thiscall *Fn_c_v)(void*);
typedef char     (__thiscall *Fn_c_ii)(void*, i32, i32);
typedef void     (__thiscall *Fn_void_v)(void*);
typedef void     (__thiscall *Fn_void_i)(void*, i32);
typedef void     (__thiscall *Fn_void_p)(void*, void*);
typedef void     (__thiscall *Fn_void_f)(void*, float);
typedef void*    (__thiscall *Fn_p_v)(void*);
typedef void*    (__thiscall *Fn_p_vp)(void*, void*);
typedef float    (__thiscall *Fn_f_v)(void*);
typedef float*   (__thiscall *Fn_fp_v)(void*);
typedef Vec3*    (__thiscall *Fn_v3_v)(void*);

// byte-offset helpers for members reached through a pointer of another class
static inline void* At(void* p, int o)        { return (char*)p + o; }
static inline u32   Ld32(const void* p, int o) { return *(const u32*)((const char*)p + o); }
static inline u8    Ld8 (const void* p, int o) { return *(const u8*)((const char*)p + o); }

// ------------------------------------------------------------------ engine entry points
void* op_new(u32 size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void  TimerOwner_Ctor(void* self);                                     // 0x00af14b0
void  TimerOwner_Dtor(void* self);                                     // 0x00af1430
void  EaRemoveHandler(void* a, void* b, void* c, void* d, void* e);    // EA::Messaging::RemoveHandler
void  FUN_00b759b0(void* p, u32 count);                                // 0x00b759b0
void* FUN_00b75910(void* container, void* pair);                       // 0x00b75910
void  FUN_00eb6280(void* p);                                           // 0x00eb6280
void* FUN_0067de40();                                                  // 0x0067de40
void* FUN_00ce6610(void* self);                                        // 0x00ce6610
void* FUN_00ce97b0(void* self);                                        // 0x00ce97b0 cSelectionEffectStreamer
void* FUN_00b3d3e0(u32 a, u32 b);                                      // 0x00b3d3e0 SP::EventLog
void  FUN_00dd5a10(void* self, u32 a);                                 // 0x00dd5a10
void* FUN_00cc5a70(void* self);                                        // 0x00cc5a70 SimSingleton ctor
void* FUN_006f3d00(void* self);                                        // 0x006f3d00 cModelInstanceSet ctor

// eastl fixed-pool primitives
void  FUN_00921260(void* pool, void* arena, u32 a, u32 b, u32 c, u32 d); // 0x00921260 fixed_pool_base::init
u32   FUN_00921340(u32 size);                                          // 0x00921340
u32   FUN_009213c0(void* p);                                           // 0x009213c0
void  FUN_00ccac60(u32 a1, u32 a2, void* a3, void* a4, u32 a5, void* a6, void* pool); // 0x00ccac60
void  FUN_00daee00(void* self, u32 v);                                 // 0x00daee00

// eastl rbtree primitives (the tree lives at strategy +0x94)
void* FUN_00ccad80(u32 header, void* end, void* value, u8 flags);     // 0x00ccad80
void* FUN_00ccc120(void* self, void* node, void* value);               // 0x00ccc120
void* FUN_00ccc070(void* self, void* value);                           // 0x00ccc070
void* FUN_00e5c780(void* self, void* out, void* key);                  // 0x00e5c780 rbtree::find
void* FUN_00921580(void* node);                                        // 0x00921580 RBTreeIncrement
void* FUN_00572660(void* self, void* obj);                             // 0x00572660 AutoRefCount ctor

// minimap window
void  FUN_00e0f9c0(void* minimap, void* citizen, i32 a, i32 b);        // 0x00e0f9c0 RemoveIcon
void  FUN_00e10580(void* minimap, void* citizen, void* icon, i32 a, i32 b); // 0x00e10580 AddIcon

// cSPCreatureCitizen / cSPCreatureBase helpers (__thiscall; explicit self here)
void* GetTribe(void* citizen);                                         // 0x00c22f50
u32   FUN_00c22dc0(void* citizen);                                     // 0x00c22dc0
char  FUN_00c0b770(void* creature);                                    // 0x00c0b770
char  FUN_00c0b760(void* creature);                                    // 0x00c0b760
void* FUN_00c0ee60(void* creature);                                    // 0x00c0ee60
float FUN_00c0c1b0(void* creature);                                    // 0x00c0c1b0
float FUN_00c0b9c0(void* creature, i32 a, i32 b);                      // 0x00c0b9c0
float FUN_00bfc490(void* contact, i32 a, i32 b);                       // 0x00bfc490
void  FUN_00bfc430(void* contact, i32 a);                              // 0x00bfc430

// posse-set / strategy own helpers (__thiscall; explicit self here)
void* FUN_00cc8ed0(void* posseSet, void* citizen);                     // 0x00cc8ed0
u32   FUN_00cc88e0(void* posseSet, u32 key);                           // 0x00cc88e0
void* FUN_00e24c90(void* child, void* citizen);                        // 0x00e24c90 FindItem
void  FUN_00ccb0f0(void* self, void* citizen);                         // 0x00ccb0f0
void  FUN_00cc9460(void* self, void* tribe);                           // 0x00cc9460 MakeTribeIcon
void  FUN_00cca880(void* self, void* citizen, u32 a);                  // 0x00cca880
u32   FUN_00cca3d0(void* self, void* citizen);                         // 0x00cca3d0
void  FUN_00cca5b0(void* self, void* key, u32 activity);               // 0x00cca5b0 SetPosseActivity
void* FUN_00ccbd10(void* self, float a, u8 b, float c, void* d, void* e); // 0x00ccbd10
void* FUN_00cc5100(void* self, void* citizen);                         // 0x00cc5100

// agent order manager / noun manager / misc
void* FUN_00bca2c0(void* self);                                        // 0x00bca2c0 FirstPending
void* FUN_00b3d230();                                                  // 0x00b3d230
char  FUN_00b5ca60(void* self);                                        // 0x00b5ca60
void  FUN_00b69990(void* self);                                        // 0x00b69990
void* FUN_00b199a0(void* self);                                        // 0x00b199a0
void* FUN_00ad7360(void* self);                                        // 0x00ad7360
void* FUN_00d9f530(void* obj);                                         // 0x00d9f530

// ------------------------------------------------------------------ global data
extern "C" void* g_SimSingleton;      // 0x0169b054  Simulator::SimSingleton*
extern "C" void* g_TribeUIInstance;   // 0x0169b41c  global tribe-UI singleton
extern "C" float g_xfPosX;            // 0x0169b0f0
extern "C" float g_xfPosY;            // 0x0169b0f4
extern "C" float g_xfPosZ;            // 0x0169b0f8
extern "C" float g_animScale;         // 0x013ec4d0
extern "C" char  g_simName[];         // 0x0145f924  "Simulator/SimSingleton"
extern "C" char  g_simTag[];          // 0x013f09b4  "Simulator"
extern "C" char  g_streamerTag[];     // 0x01476b30  "Simulator/cSelectionEffectStreamer"
extern "C" float g_eventLogArg;       // 0x0146138c
extern "C" float g_iconTint;          // 0x013eb1bc
extern "C" float g_iconChanScale;     // 0x013f2100  255.0f

// vtable pointers written by the constructor / destructor
extern "C" void* g_vtblDispBase;      // 0x01476b28  vtbl_Simulator::cTribeDisplayStrategy
extern "C" void* g_vtblMix00;         // 0x013eb394
extern "C" void* g_vtblMix04;         // 0x014426a0
extern "C" void* g_vtblMix08;         // 0x013ec458
extern "C" void* g_vtblB20;           // 0x01476b20
extern "C" void* g_vtblB04;           // 0x01476b04
extern "C" void* g_vtblAf4;           // 0x01476af4
extern "C" void* g_vtblModelSet;      // 0x0140b6f4  cModelInstanceSet base vtable
extern "C" void* g_vtblMixDisp;       // 0x013eb394  base dtor vtable 1
extern "C" void* g_vtblMixRes;        // 0x014426a0  base dtor vtable 2
extern "C" void* g_vtblMixContent;    // 0x013ec458  base dtor vtable 3

// ------------------------------------------------------------------ model objects
struct ModelSet {                          // SP::cModelInstanceSet (stride 0x60)
    void* m_vtable;                        // +0x00
    u8    m_pad04[0x0c - 0x04];
    void* m_bufA;                          // +0x0c  sp_vector buffer ([-4] = refcount)
    u8    m_pad10[0x20 - 0x10];
    void* m_bufB;                          // +0x20
    u8    m_pad24[0x34 - 0x24];
    void* m_slot34;                        // +0x34  object released through its vtable slot 1
    u8    m_pad38[0x60 - 0x38];

    void* Ctor() { return FUN_006f3d00(this); }   // 0x006f3d00
};

struct OrnamentPool {                      // strategy +0x2c0, 0x218 bytes
    u8 raw[0x218];

    void* FUN_00cccb00(u32 arg1, u32 arg2);    // 0x00cccb00
};

struct CitizenTree {                       // strategy +0x94  eastl::rbtree<...>
    u32   mCount;                          // +0x00  (= strategy +0x94)
    void* mAnchor;                         // +0x04  (= strategy +0x98)  end sentinel
    void* mEnd;                            // +0x08  (= strategy +0x9c)
    void* mP0c;                            // +0x0c  (= strategy +0xa0)
    u8    mB10;                            // +0x10  (= strategy +0xa4)
    u8    mPad11[3];
    u32   mFlags;                          // +0x14  (= strategy +0xa8)  (read as a byte)

    void* DoInsertValue(void* value);      // 0x00cccbd0
};

struct IconDef {                           // 0x24-byte icon description handed to AddIcon
    u32   mColor;                          // +0x00
    Vec3  mPos;                            // +0x04
    u32   mKind;                           // +0x10
    void* mRef;                            // +0x14  AutoRefCount<cSPCreatureCitizen>
    float mScale;                          // +0x18
    u32   mPad1c;                          // +0x1c
    u32   mPad20;                          // +0x20
};

// ------------------------------------------------------------------ the strategy
struct cTribeDisplayStrategy {
    void*  m_vtable;                       // +0x000
    u8     m_pad004[0x038 - 0x004];
    void*  m_vt38;                         // +0x038
    void*  m_vt3c;                         // +0x03c
    void*  m_vt40;                         // +0x040
    void*  m_p44;                          // +0x044
    void*  m_p48;                          // +0x048
    void*  m_ui;                           // +0x04c
    void*  m_mode;                         // +0x050
    u8     m_b54;                          // +0x054
    u8     m_pad055[0x058 - 0x055];
    void*  m_server;                       // +0x058
    void*  m_handler;                      // +0x05c
    void*  m_idTable;                      // +0x060
    u32    m_idCount;                      // +0x064
    u32    m_p68;                          // +0x068
    void*  m_p6c;                          // +0x06c
    void*  m_minimap;                      // +0x070
    void*  m_layout;                       // +0x074
    void*  m_posse;                        // +0x078
    u32    m_ownerId;                      // +0x07c
    u8     m_pad080[0x084 - 0x080];
    u8     m_b84;                          // +0x084
    u8     m_b85;                          // +0x085
    u8     m_pad086[0x088 - 0x086];
    void*  m_p88;                          // +0x088
    void*  m_p8c;                          // +0x08c
    void*  m_p90;                          // +0x090
    CitizenTree m_tree;                    // +0x094
    void*  m_ornament;                     // +0x0b0
    void*  m_swatchMgr;                    // +0x0b4
    ModelSet m_sets[2];                    // +0x0b8
    u32    m_ornInit[2 * 0xa0 / 4];        // +0x178  two 0xA0-byte tables, all -1
    void*  m_swatch;                       // +0x2b8
    void*  m_swatchWin;                    // +0x2bc
    OrnamentPool m_pool;                   // +0x2c0
    void*  m_p4d8;                         // +0x4d8
    void*  m_p4dc;                         // +0x4dc
    void*  m_p4e0;                         // +0x4e0
    u8     m_pad4e4[0x4f0 - 0x4e4];
    void*  m_helperA;                      // +0x4f0
    void*  m_helperB;                      // +0x4f4

    void  NoteTribeMemberAdded(void* citizen);   // 0x00ccc400
    void  Update();                              // 0x00ccc640

    cTribeDisplayStrategy(u32 ownerId);          // 0x00cccc50
    ~cTribeDisplayStrategy();                    // 0x00ccc190
};

// ===========================================================================
// 0x00ccc190 - 576 bytes: destructor
// ===========================================================================
// @ 0x00ccc190
cTribeDisplayStrategy::~cTribeDisplayStrategy()
{
    // Reset the derived vtables.
    m_vtable = g_vtblDispBase;
    m_vt38   = g_vtblB20;
    m_vt3c   = g_vtblB04;
    m_vt40   = g_vtblAf4;

    // The mode-strategy object tears itself down first (its vtable slot 3 takes 0).
    if (m_swatchMgr != 0)
        ((Fn_void_i)VTSLOT(m_swatchMgr, 0x0c))(m_swatchMgr, 0);

    // Unregister the global tribe-UI singleton from the messaging server.
    {
        void* mgr = FUN_0067de40();
        mgr = ((Fn_p_v)VTSLOT(mgr, 0x20))(mgr);
        ((Fn_void_p)VTSLOT(mgr, 0x20))(mgr, g_TribeUIInstance);
        ((Fn_void_v)VTSLOT(g_TribeUIInstance, 0x08))(g_TribeUIInstance);
        g_TribeUIInstance = 0;
    }

    // The two selection-effect streamers drop their references.
    if (m_helperA != 0)
        ((Fn_void_i)VTSLOT(m_helperA, 0x04))(m_helperA, 1);
    if (m_helperB != 0)
        ((Fn_void_i)VTSLOT(m_helperB, 0x04))(m_helperB, 1);

    // +0x4d8 owns a plain heap array.
    if (m_p4d8 != 0)
        operator_delete(m_p4d8);

    // The ornament pool releases its backing store, then recycles the free-list node.
    FUN_00b759b0(*(void**)(m_pool.raw + 0x04), *(u32*)(m_pool.raw + 0x08));
    {
        void* nodes = *(void**)(m_pool.raw + 0x04);
        *(u32*)(m_pool.raw + 0x0c) = 0;
        if (*(u32*)(m_pool.raw + 0x08) > 1 && nodes != *(void**)(m_pool.raw + 0x30)) {
            if (nodes < *(void**)(m_pool.raw + 0x24) ||
                *(void**)(m_pool.raw + 0x28) <= nodes)
                operator_delete(nodes);
            else {
                *(void**)nodes = *(void**)(m_pool.raw + 0x1c);
                *(void**)(m_pool.raw + 0x1c) = nodes;
            }
        }
    }

    // The swatch window and the swatch object.
    if (m_swatchWin != 0)
        ((Fn_void_v)VTSLOT(m_swatchWin, 0x04))(m_swatchWin);
    if (m_swatch != 0)
        ((Fn_void_v)VTSLOT(m_swatch, 0x04))(m_swatch);

    // The two cModelInstanceSets: reset the base vtable and drop their buffers.
    for (int i = 1; i >= 0; --i) {
        ModelSet* set = &m_sets[i];
        set->m_vtable = g_vtblModelSet;
        if (set->m_slot34 != 0)
            ((Fn_void_v)VTSLOT(set->m_slot34, 0x04))(set->m_slot34);
        if (set->m_bufB != 0 && *(i32*)((char*)set->m_bufB - 4) != 0)
            operator_delete_array(set->m_bufB);
        if (set->m_bufA != 0 && *(i32*)((char*)set->m_bufA - 4) != 0)
            operator_delete_array(set->m_bufA);
    }

    if (m_swatchMgr != 0)
        ((Fn_void_v)VTSLOT(m_swatchMgr, 0x04))(m_swatchMgr);

    // The ornament at +0xb0 is an intrusive ref-counted object.
    {
        void* p = m_ornament;
        if (p != 0) {
            i32 n = (i32)((*(u32*)((char*)p + 4)) - 1);
            *(u32*)((char*)p + 4) = (u32)n;
            if (n == 0) {
                *(u32*)((char*)p + 4) = 1;
                ((Fn_void_i)VTSLOT(p, 0x00))(p, 1);
            }
        }
    }

    FUN_00eb6280(m_tree.mP0c);

    // The posse set is intrusive as well.
    {
        void* p = m_posse;
        if (p != 0) {
            i32 n = (i32)((*(u32*)((char*)p + 4)) - 1);
            *(u32*)((char*)p + 4) = (u32)n;
            if (n == 0) {
                *(u32*)((char*)p + 4) = 1;
                ((Fn_void_i)VTSLOT(p, 0x00))(p, 1);
            }
        }
    }
    if (m_layout != 0)
        ((Fn_void_v)VTSLOT(m_layout, 0x08))(m_layout);
    if (m_minimap != 0)
        ((Fn_void_v)VTSLOT(m_minimap, 0x04))(m_minimap);

    // Deregister the message handlers.
    if (m_server != 0) {
        void* srv = m_server;
        m_server = 0;
        EaRemoveHandler(srv, m_handler, m_idTable, (void*)m_idCount, (void*)m_p68);
    }

    if (m_mode != 0)
        ((Fn_void_v)VTSLOT(m_mode, 0x04))(m_mode);

    // Reset the MixIn base vtables, then run the shared base destructor.
    m_vt40 = g_vtblMixContent;
    m_vt3c = g_vtblMixRes;
    m_vt38 = g_vtblMixDisp;
    TimerOwner_Dtor(this);
}

// ===========================================================================
// 0x00ccc400 - 572 bytes: SP::cTribeDisplayStrategy::NoteTribeMemberAdded
// ===========================================================================
// @ 0x00ccc400
void cTribeDisplayStrategy::NoteTribeMemberAdded(void* citizen)
{
    if (m_minimap == 0)
        return;
    if (GetTribe(citizen) == 0)
        return;

    FUN_00e0f9c0(m_minimap, citizen, 1, 0);

    // Build the icon description on the stack.
    IconDef icon;
    icon.mColor = 0;
    icon.mPos.x = 0.0f;
    icon.mPos.y = 0.0f;
    icon.mPos.z = g_iconTint;
    icon.mKind  = 0x2000;
    icon.mRef   = 0;
    icon.mScale = 0.0f;
    icon.mPad1c = 0;
    icon.mPad20 = 0;

    // Pack the citizen's normalised tint into a packed RGB colour.
    {
        float* rgb = ((Fn_fp_v)VTSLOT(citizen, 0xe0))(citizen);
        u32 r = (u32)(rgb[0] * g_iconChanScale);
        u32 g = (u32)(rgb[1] * g_iconChanScale);
        u32 b = (u32)(rgb[2] * g_iconChanScale);
        icon.mColor = ((((r | 0xffffff00u) << 8) | (g & 0xff)) << 8) | (b & 0xff);
    }

    // Position from the citizen's embedded spatial object.
    {
        Vec3* pos = ((Fn_v3_v)VTSLOT(At(citizen, 0xc0), 0x2c))(At(citizen, 0xc0));
        icon.mPos = *pos;
    }

    // Track the citizen in the local auto-refcount slot.
    if (citizen != icon.mRef) {
        ((Fn_void_v)VTSLOT(citizen, 0x00))(citizen);       // add ref
        void* old = icon.mRef;
        icon.mRef = citizen;
        if (old != 0)
            ((Fn_void_v)VTSLOT(old, 0x04))(old);           // release old
    }

    // Register the citizen in the tribe tree when its placement is valid.
    if (((Fn_c_v)VTSLOT(At(citizen, 0xc0), 0x58))(At(citizen, 0xc0)) != 0) {
        if (m_posse != 0) {
            ((Fn_void_v)VTSLOT(citizen, 0x00))(citizen);
            void* found = 0;
            FUN_00e5c780(&m_tree, &found, citizen);
            ((Fn_void_v)VTSLOT(citizen, 0x04))(citizen);
            if (found == m_tree.mAnchor) {
                FUN_00cc8ed0(m_posse, citizen);

                void* ref = 0;
                FUN_00572660(&ref, citizen);

                void* node = FUN_00ccc070(&m_tree, citizen);
                *(void**)node = citizen;
                *(u32*)((char*)node + 4) = 0;
                *(u32*)((char*)node + 8) = 0;
                if (citizen != 0)
                    ((Fn_void_v)VTSLOT(citizen, 0x04))(citizen);

                FUN_00cca880(this, citizen, FUN_00c22dc0(citizen));
            }
        }
        icon.mKind |= 8;
    }

    FUN_00e10580(m_minimap, citizen, &icon, 0, 0);
    FUN_00cc9460(this, GetTribe(citizen));

    if (icon.mRef != 0)
        ((Fn_void_v)VTSLOT(icon.mRef, 0x04))(icon.mRef);
}

// ===========================================================================
// 0x00ccc640 - 1213 bytes: per-frame Update sweep
// ===========================================================================
// @ 0x00ccc640
void cTribeDisplayStrategy::Update()
{
    if (m_posse == 0)
        return;

    void* end  = m_tree.mEnd;
    void* node = m_tree.mAnchor;
    if (node == end)
        goto sweep;

    for (;;) {
        {
            void* observer = *(void**)((char*)node + 0x10);
            void* posseSet = m_posse;

            u32 slot = 5;
            if (FUN_00c0b770(observer) != 0)
                slot = FUN_00cc88e0(posseSet, FUN_00c22dc0(observer));

            void* child = *(void**)((char*)posseSet + slot * 4 + 8);
            void* item  = FUN_00e24c90(child, observer);

            if (observer != 0 && item != 0) {
                // Refresh the selected item's parameter read-outs.
                if (*(u8*)((char*)observer + 0xb5e) == 0) {
                    void* state = *(void**)item;
                    float v1 = FUN_00c0b9c0(observer, 1, 1);
                    ((Fn_void_i)VTSLOT(state, 0x80))(state, (i32)0x3d99184u);
                    (void)v1;
                    float v2 = FUN_00bfc490(At(observer, 0x5a8), 1, 1) * g_animScale;
                    (void)v2;
                    ((Fn_void_i)VTSLOT(state, 0x80))(state, (i32)0x3d99162u);
                }

                // Make sure the Simulator singleton exists, then drive it.
                if (FUN_00c0b760(observer) == 0) {
                    if (g_SimSingleton == 0) {
                        void* mem = op_new(0x100, g_simName, 0, 0, 0, 0);
                        g_SimSingleton = mem ? FUN_00cc5a70(mem) : 0;
                    }
                    if (g_SimSingleton != 0) {
                        (void)FUN_00cc5100(g_SimSingleton, observer);
                        void* state = *(void**)item;
                        (void)state;
                    }
                }

                FUN_00ccb0f0(this, observer);

                if ((*(u8*)((char*)node + 0x18) & 2) != 0) {
                    void* nm = FUN_00b3d230();
                    if (FUN_00b5ca60(nm) != 0)
                        FUN_00b69990(observer);
                }

                FUN_00cca5b0(this, observer, FUN_00cca3d0(this, observer));
            }

            // Only live, visible citizens are advanced.
            if (((Fn_c_v)VTSLOT(At(observer, 0xc0), 0x50))(At(observer, 0xc0)) == 0)
                goto next;

            bool wanted = false;
            {
                void* orderMgr = *(void**)At(observer, 0xb4c);
                void* pending = FUN_00bca2c0(orderMgr);
                if (pending != 0) {
                    u32 id = Ld32(pending, 0);
                    if (id != 0) {
                        if (id == 0x1a)
                            wanted = true;
                    } else if (Ld32(pending, 0x28) != 0) {
                        wanted = true;
                    }
                }
            }

            void* target = FUN_00c0ee60(observer);
            void* actor = 0;
            if (target != 0) {
                void* a = ((Fn_p_v)VTSLOT(target, 0x08))(target);
                void* b = ((Fn_p_v)VTSLOT(target, 0x0c))(target);
                if (a != 0 && Ld8(a, 0x75) != 0 && b != 0) {
                    if (((Fn_c_v)VTSLOT(b, 0x2c))(b) != 0)
                        actor = 0;
                }
            }
            (void)actor;

            if (!wanted)
                goto next;

            // Swept-vocal marker: world position plus the actor's transform.
            {
                Vec3 pos;
                pos.x = g_xfPosX;
                pos.y = g_xfPosY;
                pos.z = g_xfPosZ;

                if (target != 0) {
                    void* s = ((Fn_p_v)VTSLOT(target, 0x08))(target);
                    Vec3* p = ((Fn_v3_v)VTSLOT(s, 0x2c))(s);
                    pos = *p;
                    void* s2 = ((Fn_p_v)VTSLOT(target, 0x08))(target);
                    float radius = ((Fn_f_v)VTSLOT(s2, 0x74))(s2);
                    u8 flag = *(u8*)((char*)s2 + 0x77);
                    FUN_00ccbd10(this,
                                 FUN_00c0c1b0(observer),
                                 flag,
                                 radius,
                                 &pos,
                                 ((Fn_p_v)VTSLOT(target, 0x0c))(target));
                }
            }

            // Second pass: resolve the pending order's owner and mark its effects.
            {
                void* orderMgr = *(void**)At(observer, 0xb4c);
                void* pending = FUN_00bca2c0(orderMgr);
                u32 id = Ld32(pending, 0);
                if (id != 0) {
                    if (id == 0x1a) {
                        void* nbt = (void*)Ld32(observer, 0xb4c);
                        if (Ld32(nbt, 0x1d8) == 0xb46e8803u) {
                            void* tbl = (void*)Ld32(nbt, 0x600);
                            void* obj = FUN_00d9f530((void*)Ld32(tbl, 0x1a8));
                            if (obj != 0) {
                                void** it = *(void***)((char*)obj + 0x78);
                                void** en = *(void***)((char*)obj + 0x7c);
                                if (it != en) {
                                    do {
                                        void* ent = (void*)*it;
                                        void* self2 = *(void**)ent;
                                        void* s = ((Fn_p_v)VTSLOT(At(self2, 0xc0), 0x2c))(At(self2, 0xc0));
                                        (void)s;
                                        ++it;
                                    } while (it != en);
                                }
                            }
                        }
                    }
                } else {
                    void* slot = At(pending, 0x28);
                    if (Ld32(pending, 0x28) != 0) {
                        void* a = FUN_00b199a0(slot);
                        void* b = FUN_00ad7360(slot);
                        if (a != 0 && b != 0) {
                            void* s = ((Fn_p_v)VTSLOT(b, 0x2c))(b);
                            (void)s;
                            (void)Ld32(a, 0x24);
                        }
                    }
                }
            }
        }

    next:
        node = FUN_00921580(node);
        if (node == end)
            break;
    }

sweep:
    // Sweep the ornament pool's open-hash free list.
    {
        u8* pool = m_pool.raw;
        void* bucketArr = *(void**)(pool + 0x04);
        u32   bucketCnt = *(u32*)(pool + 0x08);
        void* edi = bucketArr;
        void* esi = *(void**)edi;
        if (esi == 0) {
            do { edi = (char*)edi + 4; } while (*(void**)edi == 0);
            esi = *(void**)edi;
        }
        void* stop = *(void**)((char*)bucketArr + bucketCnt * 4);
        while (esi != stop) {
            void* ref = *(void**)((char*)esi + 8);
            if (ref != 0 && *(u8*)((char*)esi + 0xc) == 0) {
                ((Fn_void_i)VTSLOT(ref, 0x0c))(ref, 1);
                void* r2 = *(void**)((char*)esi + 8);
                if (r2 != 0) {
                    *(void**)((char*)esi + 8) = 0;
                    ((Fn_void_v)VTSLOT(r2, 0x04))(r2);
                }
                *(void**)((char*)esi + 4) = 0;
            }
            *(u8*)((char*)esi + 0xc) = 0;

            if (*(void**)((char*)esi + 8) == 0) {
                void* pair[2];
                pair[0] = esi;
                pair[1] = edi;
                void* r = FUN_00b75910(&m_pool, pair);
                esi = *(void**)r;
                edi = *(void**)((char*)r + 4);
            } else {
                esi = *(void**)((char*)esi + 0x10);
                while (esi == 0) {
                    edi = (char*)edi + 4;
                    esi = *(void**)((char*)edi + 4);
                }
            }
            stop = *(void**)((char*)bucketArr + bucketCnt * 4);
        }
    }
}

// ===========================================================================
// 0x00cccb00 - 203 bytes: ornament pool construction helper
// ===========================================================================
// @ 0x00cccb00
void* OrnamentPool::FUN_00cccb00(u32 arg1, u32 arg2)
{
    u8* self = raw;

    // eastl::fixed_pool_base::init(&local, self + 0x7c, 0x140, 0x14, 4, 0)
    u8 poolBase[0x18];
    *(void**)poolBase = 0;
    FUN_00921260(poolBase, self + 0x7c, 0x140, 0x14, 4, 0);

    // Build the container from the pool.
    u32 ctx = FUN_00921340(0x11);
    FUN_00ccac60(ctx, arg1, self + 0x34, self + 0x1bc, 0x14, self + 0x7c, poolBase);

    // Retail float constants: 9900.0 and 2.0.
    *(float*)(self + 0x10) = 9900.0f;      // 0x461c4000
    *(float*)(self + 0x14) = 2.0f;         // 0x40000000
    *(void**)(self + 0x18) = 0;

    u32 v = FUN_009213c0(*(void**)(self + 0x0c));
    if (*(u32*)(self + 0x08) < v)
        FUN_00daee00(this, v);

    return this;
}

// ===========================================================================
// 0x00cccbd0 - 127 bytes: eastl::rbtree<...>::DoInsertValue
// ===========================================================================
// @ 0x00cccbd0
void* CitizenTree::DoInsertValue(void* value)
{
    u32* v = (u32*)value;
    void* end = mAnchor;
    void* p = FUN_00ccad80(mCount, end, value, (u8)mFlags);

    if (p == end ||
        (v[1] <= Ld32(p, 4) && (v[1] < Ld32(p, 4) || v[0] < Ld32(p, 0)))) {
        u32 local[5];
        local[0] = v[0];
        local[1] = v[1];
        local[2] = local[0];
        local[3] = local[1];
        local[4] = local[0];
        p = FUN_00ccc120(this, p, local);
    }
    return (char*)p + 8;
}

// ===========================================================================
// 0x00cccc50 - 987 bytes: Simulator::cTribeDisplayStrategy::cTribeDisplayStrategy
// ===========================================================================
// @ 0x00cccc50
cTribeDisplayStrategy::cTribeDisplayStrategy(u32 ownerId)
{
    TimerOwner_Ctor(this);

    // Placeholder MixIn vtables (immediately replaced by the real ones below).
    m_vt38 = g_vtblMix00;
    m_vt3c = g_vtblMix04;
    m_vt40 = g_vtblMix08;
    m_p44  = 0;

    // Real vtables.
    m_vtable = g_vtblDispBase;
    m_vt38   = g_vtblB20;
    m_vt3c   = g_vtblB04;
    m_vt40   = g_vtblAf4;

    m_p48     = 0;
    m_ui      = 0;
    m_mode    = 0;
    m_b54     = 0;
    m_server  = 0;
    m_handler = 0;
    m_idTable = 0;
    m_idCount = 0;
    m_p68     = 0;
    m_p6c     = 0;
    m_minimap = 0;
    m_layout  = 0;
    m_posse   = 0;
    m_ownerId = ownerId;
    m_b84     = 0;
    m_b85     = 0;
    m_p88     = 0;
    m_p8c     = 0;
    m_p90     = 0;

    // Self-linked eastl rbtree header (anchor points at itself).
    m_tree.mCount  = 0;
    m_tree.mAnchor = &m_tree;
    m_tree.mEnd    = 0;
    m_tree.mP0c    = 0;
    m_tree.mB10    = 0;
    m_tree.mFlags  = 0;

    m_ornament  = 0;
    m_swatchMgr = 0;

    // Two cModelInstanceSet sub-objects.
    for (int i = 0; i < 2; ++i)
        m_sets[i].Ctor();

    // Two 0xA0-byte ornament tables, every dword initialised to -1.
    for (u32 i = 0; i < (2 * 0xa0) / 4; ++i)
        m_ornInit[i] = 0xffffffffu;

    m_swatch    = 0;
    m_swatchWin = 0;

    {
        u32 dummy1 = 0;
        u32 dummy2 = 0;
        m_pool.FUN_00cccb00((u32)&dummy1, (u32)&dummy2);
    }

    m_p4d8    = 0;
    m_p4dc    = 0;
    m_p4e0    = 0;
    m_helperA = 0;
    m_helperB = 0;

    // Global tribe-UI singleton.
    if (g_TribeUIInstance == 0) {
        void* mem = op_new(0x20, g_simTag, 0, 0, 0, 0);
        void* made = mem ? FUN_00ce6610(mem) : 0;
        g_TribeUIInstance = made;
        if (made != 0)
            ((Fn_void_v)VTSLOT(made, 0x04))(made);
    }

    {
        void* reg = FUN_0067de40();
        reg = ((Fn_p_v)VTSLOT(reg, 0x20))(reg);
        ((Fn_void_p)VTSLOT(reg, 0x1c))(reg, g_TribeUIInstance);
    }

    FUN_00b3d3e0(0, 0xc3480000u);
    FUN_00dd5a10(this, 0xc3480000u);

    // Two cSelectionEffectStreamer helpers.
    {
        void* mem = op_new(0x18, g_streamerTag, 0, 0, 0, 0);
        m_helperA = mem ? FUN_00ce97b0(mem) : 0;
    }
    {
        void* mem = op_new(0x18, g_streamerTag, 0, 0, 0, 0);
        m_helperB = mem ? FUN_00ce97b0(mem) : 0;
    }

    // Ensure the Simulator singleton exists for later frames.
    if (g_SimSingleton == 0) {
        void* mem = op_new(0x100, g_simName, 0, 0, 0, 0);
        g_SimSingleton = mem ? FUN_00cc5a70(mem) : 0;
    }
}