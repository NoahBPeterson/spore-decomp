// @ 0x00b5e9a0: update of the UI "world" (layout) visibility from the current game state.
// Builds a local eastl::fixed_hash_map<uint32_t, bool> (world id -> should be visible), then
// applies it to the cSPUILayoutManager: SetWorldVisible(id, v) for every entry whose current
// IsWorldVisible(id) differs. Layout world ids are retail hashes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no EH: the original has no SEH prolog).
#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

struct cLayoutMgr {
    bool IsWorldVisible(u32 id);                  // 0x00810760 (ret 4)
    void SetWorldVisible(u32 id, bool v);         // 0x00810660 (ret 8)
    bool AnyWorldHidden();                        // 0x00810730
};
cLayoutMgr* __cdecl GetLayoutManager();           // 0x00805070

struct cB3d320 { char pad[0x28]; u8 mFlag28; };
cB3d320* __cdecl GetB3d320();                     // 0x00b3d320
unsigned __cdecl GetCurrentGameMode();            // 0x00b5b800

struct cCreatureModeStrategy {
    bool F();                                     // 0x00d38880
    static cCreatureModeStrategy* Instance();     // 0x00d38840
};
struct cTribeModeStrategy {
    bool F();                                     // 0x00cd4490
    static cTribeModeStrategy* Instance();        // 0x00cd40b0
};
struct cCivModeStrategy {
    bool F();                                     // 0x00cf7a40
    static cCivModeStrategy* Get();               // 0x00cf74c0
};
struct cB3d410 {
    bool F();                                     // 0x00e36fa0
    bool G();                                     // 0x00e393b0
};
cB3d410* __cdecl GetB3d410();                     // 0x00b3d410
struct cB3d4d0 { char pad[0x2c]; int m2c; };
cB3d4d0* __cdecl GetB3d4d0();                     // 0x00b3d4d0
struct cB3d3f0 { bool F(int a); };                // 0x00e18c70 (ret 4)
cB3d3f0* __cdecl GetB3d3f0();                     // 0x00b3d3f0

struct cFlagObj {
    bool F1();                                    // 0x00644db0
    bool F2();                                    // 0x00644dd0
    char pad[0x1c];
    u8 mFlag;
};
cFlagObj* __cdecl SporeGuide();                   // 0x00401040
cFlagObj* __cdecl AssetBrowser();                 // 0x00401030

struct IWinMgr {
    virtual void v0();
    virtual void* Get4();
};
IWinMgr* __cdecl WindowManager();                 // 0x0067caa0
struct cWinObj {
    bool Test();                                  // 0x00812d70
    bool Test2();                                 // 0x00812d90
    void Set(bool b);                             // 0x00812d60 (ret 4)
};
struct cC10666a0 { bool F(); };                   // 0x01065b30
cC10666a0* __cdecl GetC10666a0();                 // 0x010666a0
bool __cdecl FUN_00e00b00();
bool __cdecl FUN_00e00ac0();

extern const u32 kWorldIds[12];                   // 0x014617dc
extern u8 gUiBusyFlag;                            // 0x01686af0
extern u8 gUiFlagB;                               // 0x01686af1

void __cdecl EA_operator_delete(void* p);          // 0x00f47380

// ---- eastl::fixed_hash_map<u32, bool, 17 buckets, 16 nodes> ----------------------------------
struct TagA {};
struct TagB {};
struct Pair { u32 first; bool second; Pair() {} Pair(const u32& a, const bool& b) : first(a), second(b) {} };
struct Node { u32 key; bool val; Node* next; };
struct Iter {
    Node* node; Node** bucket;
    Iter() {}
    Iter(Node* n, Node** b) : node(n), bucket(b) {}
    Iter(const Iter& o) : node(o.node), bucket(o.bucket) {}
};
struct InsertRet { Iter it; bool inserted; };
struct InsertTag {};

struct VisMap {
    u32 pad0;
    Node** mpBucketArray;     // +04
    u32 mnBucketCount;        // +08
    u32 mnElementCount;       // +0c
    u32 mRehashPolicy[3];     // +10
    void* mpPoolHead;         // +1c
    void* mpPoolNext;         // +20
    void* mpPoolBegin;        // +24
    void* mpPoolEnd;          // +28
    u32 mnNodeSize;           // +2c
    Node** mpBucketBuffer;    // +30
    void* mBucketBuffer[18];
    char mNodeBuffer[192];
    double mAlign8;

    VisMap(const TagA&, const TagB&);                     // 0x00d2d5c0 (ret 8)
    __declspec(noinline) Iter find(const u32& key)        // 0x00645ed0 (real body: tells cl it never writes key)
    {
        Node** bucket = mpBucketArray + (key % mnBucketCount);
        for (Node* p = *bucket; p; p = p->next)
            if (p->key == key)
                return Iter(p, bucket);
        Iter e;
        e.node = mpBucketArray[mnBucketCount];
        e.bucket = mpBucketArray + mnBucketCount;
        return e;
    }
    InsertRet DoInsertValue(const Pair& v, InsertTag t);  // 0x00c15fd0
    void DoFreeNodes(Node** buckets, u32 n);              // 0x00a1b6c0
    bool& operator[](const u32& key);                     // 0x00b5e050 (out-of-line copy)
    __forceinline bool* At(const u32& key)                              // same body, inlined
    {
        Iter it = find(key);
        Node* node = it.node;
        if (node == mpBucketArray[mnBucketCount]) {
            InsertRet r = DoInsertValue(Pair(key, false), InsertTag());
            node = r.it.node;
        }
        bool* pv = &node->val;
        return pv;
    }
    ~VisMap()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1 && mpBucketArray != mpBucketBuffer) {
            if ((void*)mpBucketArray >= mpPoolBegin && (void*)mpBucketArray < mpPoolEnd) {
                *(void**)mpBucketArray = mpPoolHead;
                mpPoolHead = mpBucketArray;
            } else
                EA_operator_delete(mpBucketArray);
        }
    }
};

// @ 0x00b5e9a0
void __stdcall UpdateWorldVisibility(int unused)
{
    TagA tagA;
    TagB tagB;
    VisMap map(tagA, tagB);
    cLayoutMgr* lm = GetLayoutManager();

    for (u32 i = 0; i < 12; i++) {
        const u32 id = kWorldIds[i];
        if (lm->IsWorldVisible(id))
            *map.At(id) = false;
    }

    unsigned mode = GetCurrentGameMode();
    bool busy;
    if (GetB3d320()->mFlag28 || gUiBusyFlag)
        busy = true;
    else
        busy = false;
    u8 flagB = gUiFlagB;
    if (!busy) {
        switch (mode) {
        case 0x1654c01:
            busy = cCreatureModeStrategy::Instance()->F();
            break;
        case 0x1654c02:
            busy = cTribeModeStrategy::Instance()->F();
            flagB = false;
            break;
        case 0x1654c04:
            busy = cCivModeStrategy::Get()->F();
            break;
        case 0x1654c05:
            busy = GetB3d410()->F();
            break;
        }
    }

    void* w = WindowManager()->Get4();
    cWinObj* wo = w ? (cWinObj*)((char*)w - 4) : 0;
    bool woA = wo && wo->Test();
    bool woB = wo && wo->Test2();

    if (busy) {
        { const u32 k = 0x614de4c; *map.At(k) = true; }
        wo->Set(false);
    } else if (GetB3d410()->G()) {
        { const u32 k = 0x5b598f6; *map.At(k) = true; }
    } else {
        int m = GetB3d4d0()->m2c;
        if (m == 1 || m == 2) {
            { const u32 k = 0x5b598f8; map[k] = true; }
        } else if (SporeGuide()->F1() || SporeGuide()->F2() || SporeGuide()->mFlag ||
                   AssetBrowser()->F1() || AssetBrowser()->F2() || AssetBrowser()->mFlag) {
            { const u32 k = 0x5b598f6; map[k] = true; }
        } else if (GetC10666a0() && GetC10666a0()->F()) {
            { const u32 k = 0x2edd95ca; map[k] = true; }
        } else if (FUN_00e00b00()) {
            { const u32 k = 0x5b598f6; map[k] = true; }
        } else if (FUN_00e00ac0()) {
            { const u32 k = 0x5b598f6; map[k] = true; }
            { const u32 k = 0x5f1bfc10; map[k] = true; }
        } else if (GetB3d3f0()->F(0)) {
            { const u32 k = 0xe9f70df9; map[k] = true; }
            { const u32 k = 0x5b598f6; map[k] = true; }
            { const u32 k = 0x2edd95ca; map[k] = true; }
            { const u32 k = 0x3469e7a3; map[k] = true; }
            { const u32 k = 0x08d0f4fb; map[k] = true; }
        } else if (woA) {
            { const u32 k = 0x5b598f6; map[k] = true; }
        } else {
            { const u32 k = 0xe9f70df9; map[k] = !flagB; }
            { const u32 k = 0x5b598f6; map[k] = true; }
            { const u32 k = 0x5f1bfc10; map[k] = true; }
            { const u32 k = 0x2edd95ca; map[k] = true; }
            { const u32 k = 0x3f608b3e; map[k] = true; }
            { const u32 k = 0x3469e7a3; map[k] = true; }
            { const u32 k = 0xec2fd2c3; map[k] = true; }
            { const u32 k = 0x08d0f4fb; map[k] = true; }
            { const u32 k = 0xcbdf6e1d; map[k] = true; }
        }
    }

    if (lm->AnyWorldHidden()) {
        { const u32 k = 0x62efc8c; *map.At(k) = true; }
        { const u32 k = 0xa01a43c8; *map.At(k) = !woB; }
    }

    Node** b = map.mpBucketArray;
    Node* n = *b;
    Node** pb = b;
    if (!n) {
        pb = b + 1;
        while (!*pb) ++pb;
        n = *pb;
    }
    Node* pEnd = b[map.mnBucketCount];
    while (n != pEnd) {
        u32 id = n->key;
        bool v = n->val;
        if (lm->IsWorldVisible(id) != v)
            lm->SetWorldVisible(id, v);
        n = n->next;
        if (!n) {
            do { ++pb; n = *pb; } while (!n);
        }
    }
}
