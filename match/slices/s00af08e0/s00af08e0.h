// Slice s00af08e0 — cSPUILayoutManager time-of-day lookup tables.
// EASTL hash map keyed by u32; values embed a red-black tree of millisecond
// ranges. Lookups convert the current time of day to a millisecond stamp.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#pragma once

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long long u64;

struct Node;

// ---------------------------------------------------------------------------
// Red-black tree node: header, then pair<const u32, world>
// ---------------------------------------------------------------------------
struct Node
{
    Node* left;    // +0x00
    Node* right;   // +0x04
    Node* parent;  // +0x08
    u8 color;      // +0x0c
    u8 pad[3];
    int key;       // +0x10
    int t0;        // +0x14
    int t1;        // +0x18
    u32 v;         // +0x1c (float value, copied verbatim)
};

// Hashtable bucket-chain node. +0x10 is the embedded tree's root, +0x20 the
// next chain entry.
struct HashNode
{
    u32 key;        // +0x00
    u32 unk04;      // +0x04
    u32 unk08;      // +0x08
    u32 unk0c;      // +0x0c
    Node* tree;     // +0x10
    u32 unk14;      // +0x14
    u32 unk18;      // +0x18
    u32 unk1c;      // +0x1c
    HashNode* next; // +0x20
};

// Iterator pair returned by the hashtable find.
struct HIter
{
    void* a;
    void* b;
};

// Node reclaimed by the chain walker: value word first, next link second.
struct InnerNode
{
    void* val;       // +0x00
    InnerNode* next; // +0x04
};

// Embedded red-black tree (0x1c bytes).
struct RBTree
{
    u32 unk00;      // +0x00
    void* base;     // +0x04 (self)
    void* end;      // +0x08 (self)
    Node* root;     // +0x0c
    u8 flag;        // +0x10
    u8 pad[3];
    u32 size;       // +0x14
    u32 unk18;      // +0x18

    void FindBounds(HIter* out, const int* key);
    Node* Clone(Node* src, void* parent);
};

// Hash table object: two of these live in the layout manager.
struct HashTable
{
    u32 unk00;           // +0x00
    HashNode** buckets;  // +0x04
    u32 bucketCount;     // +0x08
    u32 size;            // +0x0c
    float f10;           // +0x10
    float f14;           // +0x14
    u32 unk18;           // +0x18
    u32 pad1c;           // +0x1c (padding: object is 0x20 bytes)

    void __thiscall FreeChains(HashNode** buckets, u32 count);
    void* __thiscall GetOrCreate(const u32* key);
};

// A world record stored in the trees (fields from the builders below).
struct Block { u32 q[8]; };
struct Vec3 { float x, y, z; };

struct World
{
    RBTree tree;         // +0x00 .. +0x1b
    u32 gap1c;           // +0x1c
    u32 f20;             // +0x20
    u32 f24;             // +0x24
    Vec3 p;              // +0x28
    u32 d34, d38, d3c;   // +0x34
    u8 flag40;           // +0x40
    u8 pad41[7];
    Vec3 q;              // +0x48
    float f54;           // +0x54
    u32 pad58[0x1d];     // +0x58 .. +0xcb
    Vec3 r6;             // +0xcc
    Vec3 r5;             // +0xd8
    Vec3 r7;             // +0xe4
};

// Hash value: key + embedded world record.
struct Pair { u32 key; World w; };

// Layout manager: two hash tables plus an init flag.
struct LayoutMgr
{
    HashTable t1;   // +0x00
    HashTable t2;   // +0x20
    u8 mbInit;      // +0x40

    void ClearBucketChains();
    void BuildTables();
    bool LookupA(void* entity, int key, float* out);
    bool LookupB(void* entity, int key, float* out);
    bool LookupC(void* entity, int key, float* out);
};

// Timer-carrying object built by 0x00af14b0.
struct ListNode { ListNode* next; ListNode* prev; u8 str[0x10]; };  // 0x18
struct ListHead { ListNode* next; ListNode* prev; };               // 0x08

struct TimerOwner
{
    u32 vtable;      // +0x00 = 0x0145c1bc
    u32 pad04;
    ListHead head;   // +0x08
    u32 pad10;
    u32 pad14;
    u8 timer[0x28];  // +0x18 SP::cGonzagoTimer

    void Dtor();
    void Add(const void* wstr);
    TimerOwner* Ctor();
    TimerOwner* Delete(u32 flags);
};

// ---------------------------------------------------------------------------
// External callees modelled as members so their __thiscall ABI matches.
// ---------------------------------------------------------------------------
struct XComp
{
    u32 __thiscall Get();           // 0xc04590
    u32 __thiscall GetPosition();   // 0xc6acc0
    u32 __thiscall GetAlt();        // 0xc23290
};

struct XTimeOfDay
{
    float __thiscall GetSeconds(u32 pos);   // 0xbc2b30
};

struct XSpeciesMgr
{
    void* __thiscall GetArchetype();        // 0x4e0050
};

struct XGonzago
{
    void __thiscall Dtor();
    void __thiscall Ctor();
};

struct XSPTimer
{
    void __thiscall Restart();
    void __thiscall Start();
};

struct XStopwatch
{
    u32 lo;              // +0x00
    u32 hi;              // +0x04
    u32 pad08;           // +0x08
    u32 pad0c;           // +0x0c
    u32 units;           // +0x10
    void __thiscall SetUnits(int units);
};

struct XList
{
    void __thiscall DoClear();
};

struct XWString
{
    void __thiscall Ctor(const void* src);
};

struct XClear
{
    void __thiscall ClearValue(void* p);    // 0x9a9600
};

struct XHash
{
    void __thiscall HashFind(HIter* out, const u32* key);              // 0xafb0d0
    void __thiscall HashInsert(HIter* result, const void* value, u8 unique);
};

struct XTreeCopy
{
    void __thiscall CopyFrom(const void* src);              // 0xaf0d40
};
struct XTreeNuke
{
    void __thiscall Nuke(void* root);                       // 0x9a9600
};
struct XHashIns
{
    void __thiscall InsertVal(HIter* out, const void* val, u8 unique);  // 0xaf0e40
};

struct XPropMgr
{
    bool __thiscall GetRecords(u32 id, void* out);
    bool __thiscall GetRecord(u32 key, u32 id, void* out);
};

extern "C" {
// 0x00f473a0 — EAAllocate(size, name, 0, 0, file, line)
void* __cdecl EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
// 0x00f47380 — operator delete
void __cdecl FreeMem(void* p);                                                   // 0xf47380
// 0x00921580 — eastl::RBTreeIncrement
Node* __cdecl RBTreeInc(Node* node);                                             // 0x921580
// 0x009216a0 — eastl::RBTreeInsert(node, parent, base, side)
void __cdecl RBTreeInsert(Node* node, void* parent, void* base, int side);       // 0x9216a0
// 0x00bc30b0 — SP::cTimeOfDay::Instance()
void* __cdecl Instance();                                                        // 0xbc30b0
// 0x00401090 — settings lookup
u32 __stdcall GetSetting9(u32 a, u32 b);                                         // 0x401090
// 0x0067de30 — SP::PropertyManager()
void* __cdecl PropertyManager();                                                 // 0x67de30
// 0x006a0990 — property row lookup
bool __cdecl FindProperty(void* rec, u32 key, int* count, int* data);            // 0x6a0990
// 0x00f473a0 — allocator again for the tree nodes in 0x00af1020
}

extern "C" {
extern u32 g_singleton_167ad74;      // 0x0167ad74
extern XStopwatch g_stopwatch;       // 0x0167adf0
extern u32 g_default34;              // 0x0167ae24
extern u32 g_default38;              // 0x0167ae28
extern u32 g_default3c;              // 0x0167ae2c
extern const float g_zero;           // 0x01485378
extern const float g_one;            // 0x01485720
extern const float g_two;            // 0x01470f1c
extern const float g_secPerDay;      // 0x0145c194 (86400.0f)
extern const float g_invDay;         // 0x0145c198 (1.1574074e-05f)
extern const float g_msPerSec;       // 0x013ec5b4 (1000.0f)
extern const float g_minScale;       // 0x013ebc4c (60.0f)
extern const float g_minScale2;      // 0x0145c19c (60000.0f)
extern const float g_eps;            // 0x0145c190 (1.5258789e-05f)
extern const char g_allocFile[];     // 0x013ebb38 (EASTL/allocator.h)
extern const char g_allocName[];     // 0x013f09b4 ("Simulator")
}
