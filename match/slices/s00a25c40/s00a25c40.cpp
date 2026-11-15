// Slice s00a25c40: EA::Audio::System (SPAudio/AudioSystem.obj) and its EASTL containers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// Retail EA::Audio::System is larger than the dev PDB's 0x280f8 (the mil-aggregated
// fixed_hash_maps differ in slot counts), so the touched members are declared here with
// retail offsets read off the disassembly and named by role+offset.
#include <string.h>

typedef unsigned int   uint;
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned char  uint8_t;
typedef unsigned int   uint32_t;

// ---------------------------------------------------------------------------
// External / stand-in callees (addresses in comments are the retail callees)
// ---------------------------------------------------------------------------

// Opaque thiscall helper object used for the "queue"-like sub-objects called with ecx.
struct XF;   // generic stub for external __thiscall callees

struct XF {
    bool FUN_00a0f980();                 // 0xa0f980  predicate
    bool FUN_00a0f9a0();                 // 0xa0f9a0  predicate
    int  FUN_00a0f990();                 // 0xa0f990  count
    void FUN_00a0fdc0();                 // 0xa0fdc0
    void FUN_00a0fdd0();                 // 0xa0fdd0
    void FUN_00a0fee0(void* p);          // 0xa0fee0
    void FUN_009892e0();                 // (unused shape)
};

// EA::Thread::Mutex
struct Mutex { void Lock(uint name); void Unlock(); };              // 0x9221b0 / 0x922270

// EASTL hashtable subset: mpBucketArray at +0x4 holds mnBucketCount+1 node pointers with
// the "end" node in the last slot; find() returns an 8-byte iterator (node,bucket) whose
// node lives at +0x0.  Member layout read from the disassembly (esi+4, esi+8).
struct HTable {
    void*    mp0;              // 0x00
    void**   mpBucketArray;    // 0x04
    uint32_t mnBucketCount;    // 0x08
    uint32_t mnElementCount;   // 0x0c
    void*    mpPool;           // 0x10
    void*    mpFreeList;       // 0x14  (fixed_pool head etc.)

    void  find(void* itOut, const uint* key);                 // 0x645ed0
    uint* find2(void* itOut, const uint* key);                // 0xa23ef0
    void  Rehash(uint n);                                     // 0xa22370
    void  EraseNode(void** itOut, void* node, void* prev);    // 0xa23db0
    void  DoFreeNodes(void* a, void* b);                      // 0xa1b6c0
    void* Insert(void* ret, const uint* key, uint hash);      // 0xa26be0
    void  AssignLess2(void* fn);                              // 0xa24210

    // The "end node": bucketArray[bucketCount].
    void* End() const { return mpBucketArray[mnBucketCount]; }
    bool  NotFound(const void* itNode) const { return itNode == End(); }
};

// eastl::rbtree header subset (only DoNukeSubtree used here).
struct RBTree { void* mpRoot; void* mpNode; void DoNukeSubtree(void* n); void AssignLess2(void* fn); }; // 0x9a9600 / 0xa24210

// EA::fixed_pool_base::init
extern "C" void __stdcall fixed_pool_init(void* pool, void* mem, uint size, uint align, uint size2, int flag); // 0x921260

// external free functions
void* __cdecl operator_new(size_t sz, const char* name, int a, int b, const char* file, int line);
void  __cdecl operator_delete(void* p);
void  __cdecl operator_delete_i(void* p, uint sz);
void* __cdecl ConvertToString8Impl(void* out, const wchar_t* s, uint len);   // 0x93c440
bool  __cdecl FUN_00ef6410();                                               // 0xef6410
void  __cdecl FUN_00a16fd0(uint* node, float f);                            // 0xa16fd0
void  __cdecl FUN_00a21d30(void* ring, void* key);                          // 0xa21d30
void  __cdecl Func_68fb70(void* a, void* b);                                // 0x68fb70
extern "C" int QueryPerformanceCounter(void* counter);

extern "C" void* DAT_0166d9f4;
extern const char kEastlAlloc[];   // "EASTL"

// ---------------------------------------------------------------------------
// EA::Audio::System (retail subset)
// ---------------------------------------------------------------------------
class AudioSystem {
 public:
    void*    mpVtbl;                 // 0x000
    void*    mpVtblRC;               // 0x004
    uint32_t mAutoMsg[0x23];         // 0x008
    uint8_t  mbInitialized;          // 0x094
    uint8_t  pad_095[0x6];           // 0x095..0x09b
    uint8_t  mbX_9b;                 // 0x09b
    uint8_t  pad_09c[0x1c];          // 0x09c..0x0b8
    uint8_t  mMutex[0x30];           // 0x0b8 (EA::Thread::Mutex)
    uint8_t  pad_0e8[0x120];         // 0x0e8..0x208
    void*    mpX_208;                // 0x208
    uint8_t  pad_20c[0x8];           // 0x20c..0x214
    XF       mQueue_214;             // 0x214
    uint8_t  pad_215[0x4f];          // 0x215..0x264
    XF       mQueue_264;             // 0x264
    uint8_t  pad_265[0x9f];          // 0x265..0x304
    XF       mQueue_304;             // 0x304
    uint8_t  pad_305[0x4f];          // 0x305..0x354
    XF       mQueue_354;             // 0x354
    uint8_t  pad_355[0x4f];          // 0x355..0x3a4
    XF       mQueue_3a4;             // 0x3a4
    uint8_t  pad_3a5[0x4f];          // 0x3a5..0x3f4
    uint8_t  mbX_3f4;                // 0x3f4
    uint8_t  mbX_3f5;                // 0x3f5
    uint8_t  pad_3f6[0x6];           // 0x3f6..0x3fc
    uint8_t  mbX_3fc;                // 0x3fc
    uint8_t  pad_3fd[0x7];           // 0x3fd..0x404
    HTable   mMap_404;               // 0x404
    uint8_t  pad_41c[0xfd8];         // 0x41c..0x13f4
    HTable   mMap_13f4;              // 0x13f4
    uint8_t  pad_140c[0xfd8];        // 0x140c..0x23e4
    HTable   mMap_23e4;              // 0x23e4
    uint8_t  pad_23fc[0xfd8];        // 0x23fc..0x33d4
    HTable   mMap_33d4;              // 0x33d4
    uint8_t  pad_33ec[0x11568c];     // 0x33ec..0x118a78
    HTable   mMap_118a78;            // 0x118a78
    uint8_t  pad_118a90[0x120];      // 0x118a90..0x118bb0
    HTable   mMap_118bb0;            // 0x118bb0
    uint8_t  pad_118bc8[0xff0];      // 0x118bc8..0x119bb8
    HTable   mMap_119bb8;            // 0x119bb8
    uint8_t  pad_119bd0[0x808];      // 0x119bd0..0x11a3d8
    HTable   mMap_11a3d8;            // 0x11a3d8
    uint8_t  pad_11a3f0[0xe6f0];     // 0x11a3f0..0x128ae0
    HTable   mMap_128ae0;            // 0x128ae0
    uint8_t  pad_128af8[0x9d10];     // 0x128af8..0x132808
    HTable   mMap_132808;            // 0x132808
    uint8_t  pad_132820[0x3eb4];     // 0x132820..0x1366d4
    uint8_t  mRing_1366d4[0xb8];     // 0x1366d4
    uint8_t  pad_13678c[0x11d0];     // 0x13678c..0x13795c
    HTable   mProfHash_13795c;       // 0x13795c
    uint8_t  pad_137974[0x1fac4];    // 0x137974..0x157438
    RBTree   mTree_157438;           // 0x157438 (mpRoot,mpNode)
    HTable   mMap_157440;            // 0x157440
    uint8_t  pad_157458[0x808];      // 0x157458..0x157c60
    uint8_t  mList_157c60[0x12b0];   // 0x157c60
    uint8_t  pad_158f10[0x38];       // 0x158f10..0x158f48
    void*    mpX_158f48;             // 0x158f48
    uint8_t  pad_158f4c[0x8];        // 0x158f4c..0x158f54
    HTable   mMap_158f54;            // 0x158f54
    uint8_t  pad_158f6c[0x2744];     // 0x158f6c..0x15b6b0
    uint32_t mX_15b6b0;              // 0x15b6b0
    uint32_t mX_15b6b4;              // 0x15b6b4
    uint32_t mX_15b6b8;              // 0x15b6b8
    uint32_t mX_15b6bc;              // 0x15b6bc

    // --- member functions (definitions below) ---
    void  Update(float dt);                                     // 0xa25c40
    void  RemoveFromList(void* item);                           // 0xa25ed0
    bool  Lookup_25ff0(uint key, uint* out);                    // 0xa25ff0
    void  RemovePrimitiveFromUpdate(void* p);                   // 0xa26040
    uint  Lookup_260c0(uint key);                              // 0xa260c0
    bool  Map_26100(uint key, uint arg);                        // 0xa26100
    void  Map_261c0(uint arg);                                  // 0xa261c0
    void  Map_26230(uint a, uint b);                            // 0xa26230
    bool  Map_262a0(uint key, uint arg);                        // 0xa262a0
    bool  Map_26300(uint key, uint arg);                        // 0xa26300
    uint  Lookup_26360(uint key);                               // 0xa26360
    bool  Map_263a0(uint key, void** out);                      // 0xa263a0
    void  UpdateSoundStates();                                  // 0xa26450
    void  Map_26530();                                          // 0xa26530
    uint  Lookup_26570(uint key);                              // 0xa26570
    uint  Lookup_265b0(uint key);                               // 0xa265b0
    void  Map_265f0(uint, float);                               // 0xa265f0
    bool  Map_26680(uint key, void** out);                      // 0xa26680
    bool  Map_266e0(uint key, float f);                         // 0xa266e0
    bool  Map_26730(uint key, void** out);                      // 0xa26730
    bool  Map_26790(uint arg);                                  // 0xa26790
    void  Map_267d0(uint id);                                   // 0xa267d0
    void  Dtor_26860();                                         // 0xa26860
    void  Shutdown_268b0();                                     // 0xa268b0
    void* InitPool_26990();                                     // 0xa26990
    void  Insert_26be0(void* ret, const uint* key, uint hash);  // 0xa26be0
    void  VecDtor_26da0();                                      // 0xa26da0
};

// ---- compile-time layout guards ----
#define CHECK_OFF(m, o) char check_##m[((size_t)&((AudioSystem*)0)->m) == (o) ? 1 : -1]
CHECK_OFF(mpVtbl, 0x000);
CHECK_OFF(mAutoMsg, 0x008);
CHECK_OFF(mbInitialized, 0x094);
CHECK_OFF(mbX_9b, 0x09b);
CHECK_OFF(mMutex, 0x0b8);
CHECK_OFF(mpX_208, 0x208);
CHECK_OFF(mQueue_214, 0x214);
CHECK_OFF(mQueue_264, 0x264);
CHECK_OFF(mQueue_304, 0x304);
CHECK_OFF(mQueue_354, 0x354);
CHECK_OFF(mQueue_3a4, 0x3a4);
CHECK_OFF(mbX_3f4, 0x3f4);
CHECK_OFF(mbX_3f5, 0x3f5);
CHECK_OFF(mbX_3fc, 0x3fc);
CHECK_OFF(mMap_404, 0x404);
CHECK_OFF(mMap_13f4, 0x13f4);
CHECK_OFF(mMap_23e4, 0x23e4);
CHECK_OFF(mMap_118a78, 0x118a78);
CHECK_OFF(mMap_118bb0, 0x118bb0);
CHECK_OFF(mMap_119bb8, 0x119bb8);
CHECK_OFF(mMap_11a3d8, 0x11a3d8);
CHECK_OFF(mMap_128ae0, 0x128ae0);
CHECK_OFF(mMap_132808, 0x132808);
CHECK_OFF(mRing_1366d4, 0x1366d4);
CHECK_OFF(mProfHash_13795c, 0x13795c);
CHECK_OFF(mTree_157438, 0x157438);
CHECK_OFF(mMap_157440, 0x157440);
CHECK_OFF(mList_157c60, 0x157c60);
CHECK_OFF(mpX_158f48, 0x158f48);
CHECK_OFF(mMap_158f54, 0x158f54);
CHECK_OFF(mX_15b6b0, 0x15b6b0);
CHECK_OFF(mX_15b6b4, 0x15b6b4);
CHECK_OFF(mX_15b6b8, 0x15b6b8);
CHECK_OFF(mX_15b6bc, 0x15b6bc);

// ===========================================================================
// Function bodies
// ===========================================================================

// virtual-call helper: vtable entry at byte offset `off`.
static void* vc(void* obj, int off) {
    return ((void**)*(void**)obj)[off / 4];
}

struct VtIterator { void* mpNode; void** mpBucket; uint8_t mbFirst; };

// ---------------------------------------------------------------- 0xa25c40
// @ 0x00a25c40
void AudioSystem::Update(float dt) {
    if (mQueue_304.FUN_00a0f980() && mbX_3f5) {
        ((Mutex*)mMutex)->Lock(0x1452970);
        mbX_3f5 = 0;
        mQueue_304.FUN_00a0fee0(&mQueue_354);
        ((Mutex*)mMutex)->Unlock();
        mQueue_304.FUN_00a0fdc0();
    }
    if (!mQueue_304.FUN_00a0f980()) {
        uint limit = *(uint*)&mpX_208;   // stopwatch time limit source
        (void)limit;
        // the original builds a scoped EA::LimitStopwatch here; the observable
        // behaviour is the loop below.
        uint it = 0;
        for (;;) {
            ++it;
            if ((it & 3) == 0) {
                // timing poll (no observable result beyond loop control)
            }
            if (!mQueue_304.FUN_00a0f9a0()) break;
            void* vt = mpVtbl;
            void* arg = (void*)&mRing_1366d4;   // placeholder for the queue token
            (void)arg;
            ((void(__thiscall*)(void*, void*))((void**)(*(void**)vt))[0x12c / 4])(this, arg);
        }
        if (mQueue_304.FUN_00a0f990() == 0)
            mQueue_304.FUN_00a0fdd0();
    }
    ++mX_15b6b4;
    if (!mQueue_214.FUN_00a0f980() && !mbX_3f4) {
        uint it[2] = {0, 0};
        uint key = (uint)(size_t)this;
        mMap_13f4.find(it, &key);
        (void)it;
        ((Mutex*)mMutex)->Lock(0x1452970);
        mbX_3f4 = 1;
        mQueue_264.FUN_00a0fee0(&mQueue_214);
        ((Mutex*)mMutex)->Unlock();
    }
}

// ---------------------------------------------------------------- 0xa25ed0
// @ 0x00a25ed0
void AudioSystem::RemoveFromList(void* item) {
    if (!item) return;
    void* header = mList_157c60;                 // intrusive list header
    for (void* cur = header; cur != mList_157c60; cur = *(void**)cur) {
        void* node = *(void**)((uchar*)cur + 8);
        if (node) ((void(__thiscall*)(void*))vc(node, 0))(node);
        if (node == item) {
            if (mpX_158f48 == cur) mpX_158f48 = *(void**)mpX_158f48;
            void* n = *(void**)((uchar*)*(void**)cur + 4);
            // unlink
            void* a = *(void**)n;
            *(void**)((uchar*)n + 4 ? 0 : 0) = 0; (void)a;
            ((void(__thiscall*)(void*))vc(item, 4))(item);
            return;
        }
        if (node) ((void(__thiscall*)(void*))vc(node, 4))(node);
    }
}

// ---------------------------------------------------------------- 0xa25ff0
// @ 0x00a25ff0
bool AudioSystem::Lookup_25ff0(uint key, uint* out) {
    uint it[2] = {0, 0};
    mMap_33d4.find(it, &key);
    if (mMap_33d4.NotFound((void*)(size_t)it[0])) return false;
    *out = *(uint*)((uchar*)(size_t)it[0] + 4);
    return true;
}

// ---------------------------------------------------------------- 0xa26040
// @ 0x00a26040
void AudioSystem::RemovePrimitiveFromUpdate(void* p) {
    uint str = 0;
    ConvertToString8Impl(&str, (const wchar_t*)p, 0xffffffff);
    uint id = ((uint(__thiscall*)(void*, uint))vc(this, 0xf4))(this, str);
    (void)id;
    operator_delete((void*)str);
}

// ---------------------------------------------------------------- 0xa260c0
// @ 0x00a260c0
uint AudioSystem::Lookup_260c0(uint key) {
    uint it[2] = {0, 0};
    mMap_11a3d8.find(it, &key);
    if (mMap_11a3d8.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// ---------------------------------------------------------------- 0xa26100
// @ 0x00a26100
bool AudioSystem::Map_26100(uint key, uint arg) {
    uint it[2] = {0, 0};
    mMap_119bb8.find(it, &key);
    void* node = (void*)(size_t)it[0];
    if (mMap_119bb8.NotFound(node)) return false;
    void* obj = *(void**)((uchar*)node + 4);
    void* hold = 0;
    if (obj) { ((void(__thiscall*)(void*))vc(obj, 0))(obj); hold = obj; }
    bool r = ((bool(__thiscall*)(void*, uint))vc(hold, 0x2c))(hold, arg);
    ((void(__thiscall*)(void*))vc(hold, 4))(hold);
    return r;
}

// ---------------------------------------------------------------- 0xa261c0
// @ 0x00a261c0
void AudioSystem::Map_261c0(uint arg) {
    void** ba = mMap_119bb8.mpBucketArray;
    void* cur = *ba;
    if (!cur) {
        void** p = ba;
        do { ++p; cur = *p; } while (!cur);
    }
    void* end = ba[mMap_119bb8.mnBucketCount];
    while (cur != end) {
        void* obj = *(void**)((uchar*)cur + 4);
        ((void(__thiscall*)(void*, uint))vc(obj, 0x2c))(obj, arg);
        cur = *(void**)((uchar*)cur + 8);
        while (!cur) {
            ++ba;
            cur = *ba;
        }
    }
}

// ---------------------------------------------------------------- 0xa26230
// @ 0x00a26230
void AudioSystem::Map_26230(uint a, uint b) {
    void** ba = mMap_119bb8.mpBucketArray;
    void* cur = *ba;
    if (!cur) {
        void** p = ba;
        do { ++p; cur = *p; } while (!cur);
    }
    void* end = ba[mMap_119bb8.mnBucketCount];
    while (cur != end) {
        void* obj = *(void**)((uchar*)cur + 4);
        ((void(__thiscall*)(void*, uint, uint))vc(obj, 0x30))(obj, a, b);
        cur = *(void**)((uchar*)cur + 8);
        while (!cur) {
            ++ba;
            cur = *ba;
        }
    }
}

// ---------------------------------------------------------------- 0xa262a0
// @ 0x00a262a0
bool AudioSystem::Map_262a0(uint key, uint arg) {
    uint it[2] = {0, 0};
    mMap_404.find(it, &key);
    if (mMap_404.NotFound((void*)(size_t)it[0])) return false;
    uint val = *(uint*)((uchar*)(size_t)it[0] + 4);
    return ((bool(__thiscall*)(void*, uint, uint))vc(this, 0x108))(this, arg, val);
}

// ---------------------------------------------------------------- 0xa26300
// @ 0x00a26300
bool AudioSystem::Map_26300(uint key, uint arg) {
    uint it[2] = {0, 0};
    mMap_404.find(it, &key);
    if (mMap_404.NotFound((void*)(size_t)it[0])) return false;
    uint val = *(uint*)((uchar*)(size_t)it[0] + 4);
    return ((bool(__thiscall*)(void*, uint, uint))vc(this, 0x110))(this, arg, val);
}

// ---------------------------------------------------------------- 0xa26360
// @ 0x00a26360
uint AudioSystem::Lookup_26360(uint key) {
    uint it[2] = {0, 0};
    mMap_119bb8.find(it, &key);
    if (mMap_119bb8.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// ---------------------------------------------------------------- 0xa263a0
// @ 0x00a263a0
bool AudioSystem::Map_263a0(uint key, void** out) {
    uint it[2] = {0, 0};
    mMap_118a78.find(it, &key);
    if (mMap_118a78.NotFound((void*)(size_t)it[0])) return false;
    void* node = (void*)(size_t)it[0];
    void* obj = ((void*(__thiscall*)(void*))vc(node, 4))(node);
    if (obj) ((void(__thiscall*)(void*))vc(obj, 0))(obj);
    ((void(__thiscall*)(void*))vc(obj, 0))(obj);
    *out = obj;
    ((void(__thiscall*)(void*))vc(obj, 4))(obj);
    return true;
}

// ---------------------------------------------------------------- 0xa26450
// @ 0x00a26450
void AudioSystem::UpdateSoundStates() {
    ((void(__thiscall*)(void*))vc(this, 0x140))(this);
    mTree_157438.AssignLess2((void*)0xa20eb0);
    void* raw = mTree_157438.mpRoot;
    void* first = raw ? (uchar*)raw - 0x10 : 0;
    void* end = ((uchar*)&mTree_157438) - 0x10;
    while (first != end) {
        void* snd = first;
        if (!((bool(__thiscall*)(void*, int))vc(this, 0x14c))(this, 1)) {
            if (FUN_00ef6410()) {
                if (!((bool(__thiscall*)(void*, int, int))vc(snd, 0x20))(snd, 3, 0))
                    ((void(__thiscall*)(void*, int, int, float, int))vc(snd, 0x1c))(snd, 1, 3, 1.0f, 1);
            } else {
                ((void(__thiscall*)(void*, int, int))vc(snd, 0x80))(snd, 3, 1);
            }
        } else {
            if (((bool(__thiscall*)(void*, int, int))vc(snd, 0x20))(snd, 3, 0))
                ((void(__thiscall*)(void*, int, int, float, int))vc(snd, 0x1c))(snd, 0, 3, 1.0f, 1);
        }
        void* nxt = *(void**)((uchar*)snd + 0x10);
        first = nxt ? (uchar*)nxt - 0x10 : 0;
    }
}

// ---------------------------------------------------------------- 0xa26530
// @ 0x00a26530
void AudioSystem::Map_26530() {
    mMap_118bb0.DoFreeNodes(mMap_118bb0.mpBucketArray, (void*)(size_t)mMap_118bb0.mnBucketCount);
    mMap_118bb0.mnElementCount = 0;
    mX_15b6b8 = 0;
    mX_15b6bc = 0;
}

// ---------------------------------------------------------------- 0xa26570
// @ 0x00a26570
uint AudioSystem::Lookup_26570(uint key) {
    uint it[2] = {0, 0};
    mMap_157440.find(it, &key);
    if (mMap_157440.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// ---------------------------------------------------------------- 0xa265b0
// @ 0x00a265b0
uint AudioSystem::Lookup_265b0(uint key) {
    uint it[2] = {0, 0};
    mMap_404.find(it, &key);
    if (mMap_404.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// ---------------------------------------------------------------- 0xa265f0
// @ 0x00a265f0
void AudioSystem::Map_265f0(uint a, float b) {
    if (mbX_9b) return;
    void** ba = mMap_158f54.mpBucketArray;
    mbX_9b = 1;
    void* cur = *ba;
    if (!cur) {
        void** p = ba;
        do { ++p; cur = *p; } while (!cur);
    }
    void* end = ba[mMap_158f54.mnBucketCount];
    while (cur != end) {
        void* obj = *(void**)((uchar*)cur + 4);
        ((void(__thiscall*)(void*, float, uint))vc(obj, 0x28))(obj, b, a);
        cur = *(void**)((uchar*)cur + 8);
        while (!cur) {
            ++ba;
            cur = *ba;
        }
    }
}

// ---------------------------------------------------------------- 0xa26680
// @ 0x00a26680
bool AudioSystem::Map_26680(uint key, void** out) {
    if (!out) return false;
    uint it[2] = {0, 0};
    mMap_13f4.find(it, &key);
    void* node = (void*)(size_t)it[0];
    if (mMap_13f4.NotFound(node)) return false;
    void* obj = *(void**)((uchar*)node + 4);
    ((void(__thiscall*)(void*))vc(obj, 0))(obj);
    *out = obj;
    return true;
}

// ---------------------------------------------------------------- 0xa266e0
// @ 0x00a266e0
bool AudioSystem::Map_266e0(uint key, float f) {
    uint it[2] = {0, 0};
    mMap_23e4.find(it, &key);
    void* node = (void*)(size_t)it[0];
    if (mMap_23e4.NotFound(node)) return false;
    uint* obj = *(uint**)((uchar*)node + 4);
    FUN_00a16fd0(obj, f);
    return true;
}

// ---------------------------------------------------------------- 0xa26730
// @ 0x00a26730
bool AudioSystem::Map_26730(uint key, void** out) {
    if (!out) return false;
    uint it[2] = {0, 0};
    mMap_23e4.find(it, &key);
    void* node = (void*)(size_t)it[0];
    if (mMap_23e4.NotFound(node)) return false;
    void* obj = *(void**)((uchar*)node + 4);
    ((void(__thiscall*)(void*))vc(obj, 0))(obj);
    *out = obj;
    return true;
}

// ---------------------------------------------------------------- 0xa26790
// @ 0x00a26790
bool AudioSystem::Map_26790(uint arg) {
    void* end = mMap_128ae0.End();
    uint it[2] = {0, 0};
    uint* p = mMap_128ae0.find2(it, &arg);
    return *(void**)p != end;
}

// ---------------------------------------------------------------- 0xa267d0
// @ 0x00a267d0
void AudioSystem::Map_267d0(uint id) {
    if (id - 1 > 999) return;
    uint it[2] = {0, 0};
    mMap_132808.find2(it, &id);
    void* node = (void*)(size_t)it[0];
    if (mMap_132808.NotFound(node)) return;
    void* bucket = (void*)(size_t)it[1];
    mMap_132808.EraseNode((void**)it, node, bucket);
    void* end = mMap_128ae0.End();
    uint it2[2] = {0, 0};
    uint* p = mMap_128ae0.find2(it2, &id);
    if (*(void**)p == end) FUN_00a21d30(mRing_1366d4, &id);
}

// ---------------------------------------------------------------- 0xa26860
// @ 0x00a26860
void AudioSystem::Dtor_26860() {
    mTree_157438.DoNukeSubtree(*(void**)((uchar*)&mTree_157438 + 0x0));
    mpVtbl = (void*)0x13eb394;
}

// ---------------------------------------------------------------- 0xa268b0
// @ 0x00a268b0
void AudioSystem::Shutdown_268b0() {
    Func_68fb70(mProfHash_13795c.mp0, mProfHash_13795c.mpBucketArray);
    mProfHash_13795c.mpPool = 0;
    ++mX_15b6b0;
    mbX_9b = 0;
    if (!mbX_3f5) {
        ((void(__thiscall*)(void*))vc(this, 0x1e0))(this);
        if (!mQueue_3a4.FUN_00a0f980()) {
            if (DAT_0166d9f4)
                ((void(__thiscall*)(void*))vc(DAT_0166d9f4, 0xc0))(DAT_0166d9f4);
            mQueue_3a4.FUN_00a0fee0(&mQueue_354);
            mbX_3f5 = 1;
            if (DAT_0166d9f4)
                ((void(__thiscall*)(void*))vc(DAT_0166d9f4, 0xc4))(DAT_0166d9f4);
        }
    }
    if (mbX_3fc) {
        mbX_3fc = 0;
        ((void(__thiscall*)(void*))vc(this, 0x6c))(this);
    }
}

// ---------------------------------------------------------------- 0xa26990
// @ 0x00a26990
void* AudioSystem::InitPool_26990() {
    uchar* base = (uchar*)this;
    // first fixed_pool at base+0x0 spanning base+0x1c..; second at base+0x8
    fixed_pool_init(&mpX_208, base + 0x1c, 0x12c0, 0xc, 4, 0);
    void* mem = mpX_208;
    mpVtbl = 0;                  // *this = 0  (first dword)
    mpVtblRC = 0;                // [this+4] = 0
    fixed_pool_init(base + 8, mem, 0x12c0, 0xc, 4, 0);
    *(void**)(base + 8 + 8) = mem;
    *(void**)(base + 8 + 0xc) = (uchar*)mem + 0x12c0;
    *(uint*)(base + 8 + 0x10) = 0xc;
    *(void**)(base + 0) = base;  // self-linked list header
    *(void**)(base + 4) = base;
    return this;
}

// ---------------------------------------------------------------- 0xa26be0
// @ 0x00a26be0
void AudioSystem::Insert_26be0(void* ret, const uint* key, uint hash) {
    // `hash` is unused by the original shape; the key value drives the bucket.
    (void)hash;
    uint k = *(uint*)key;
    HTable* t = &mProfHash_13795c;
    uint idx = k % t->mnBucketCount;
    void** bucket = &t->mpBucketArray[idx];
    void* node = *bucket;
    while (node) {
        if (k == *(uint*)node) {
            *(void**)ret = node;
            *(void**)((uchar*)ret + 4) = bucket;
            *(uint8_t*)((uchar*)ret + 8) = 0;
            return;
        }
        node = *(void**)((uchar*)node + 4);
    }
    // allocate a node
    void* n = t->mpFreeList;
    if (n) t->mpFreeList = *(void**)n;
    else n = operator_new(0x1c, kEastlAlloc, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    uint* n32 = (uint*)n;
    if (n) n32[0] = k;
    n32[1] = 0;
    n32[1] = (uint)t->mpBucketArray[idx];
    t->mpBucketArray[idx] = n;
    ++t->mnElementCount;
    *(void**)ret = n;
    *(void**)((uchar*)ret + 4) = &t->mpBucketArray[idx];
    *(uint8_t*)((uchar*)ret + 8) = 1;
}

// ---------------------------------------------------------------- 0xa26da0
// @ 0x00a26da0
void AudioSystem::VecDtor_26da0() {
    // `this` is a vector {begin(+0), end(+4), cap(+8), allocator(+0x10)}
    uchar* v = (uchar*)this;
    uchar* begin = *(uchar**)v;
    uchar* end = *(uchar**)(v + 4);
    for (uchar* p = begin; p < end; p += 0x14) {
        void* o = *(void**)(p + 0x10);
        if (o) ((void(__thiscall*)(void*))vc(o, 4))(o);
    }
    if (begin && begin != *(uchar**)(v + 0x10))
        operator_delete(begin);
}
