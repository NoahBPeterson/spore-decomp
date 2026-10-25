// Slice s00de6170 -- 0x0dex region (intrusive list / container helpers).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (default /GS on).

// Local declarations used to reproduce the thiscall/cdecl call shapes of the
// eastl red-black-tree helpers this translation unit calls into.
class CFind70 {
public:
    void* find(void* out, void* key);
};
class CFind1c {
public:
    void* find(void* out, void* key);
};
class CInsert {
public:
    void* insert(void* out, void* key, unsigned int v);
};
void* __cdecl RBTreeIncrement(void* node);
void __cdecl RBTreeErase(void* a, void* b);
void __cdecl freeNode(void* p);

// @ 0x00de67b0 -- FUN_00de67b0 (__fastcall, this in ecx)
// Initialises the five intrusive list headers embedded in the object: three
// zero dwords + a flag byte + a trailing dword per list, plus the self-linked
// head pointers at +0x04, +0x20, +0x3c, +0x58 and +0x74.
int* __fastcall FUN_00de67b0(int param_1) {
    int zero = 0;
    int* p = (int*)param_1;
    p[2] = zero;
    p[3] = zero;
    p[4] = zero;
    p[3] = zero;
    *(char*)(param_1 + 0x10) = (char)zero;
    p[5] = zero;
    int* iVar1 = (int*)(param_1 + 4);
    *iVar1 = (int)iVar1;
    p[2] = (int)iVar1;
    p[9] = zero;
    p[10] = zero;
    p[0xb] = zero;
    p[10] = zero;
    *(char*)(param_1 + 0x2c) = (char)zero;
    p[0xc] = zero;
    iVar1 = (int*)(param_1 + 0x20);
    *iVar1 = (int)iVar1;
    p[9] = (int)iVar1;
    p[0x10] = zero;
    p[0x11] = zero;
    p[0x12] = zero;
    p[0x11] = zero;
    *(char*)(param_1 + 0x48) = (char)zero;
    p[0x13] = zero;
    iVar1 = (int*)(param_1 + 0x3c);
    *iVar1 = (int)iVar1;
    p[0x10] = (int)iVar1;
    p[0x17] = zero;
    p[0x18] = zero;
    p[0x19] = zero;
    iVar1 = (int*)(param_1 + 0x58);
    *iVar1 = (int)iVar1;
    p[0x17] = (int)iVar1;
    p[0x18] = zero;
    *(char*)(param_1 + 0x64) = (char)zero;
    p[0x1a] = zero;
    iVar1 = (int*)(param_1 + 0x74);
    iVar1[1] = zero;
    iVar1[2] = zero;
    iVar1[3] = zero;
    *iVar1 = (int)iVar1;
    p[0x1e] = (int)iVar1;
    p[0x1f] = zero;
    *(char*)(param_1 + 0x80) = (char)zero;
    p[0x21] = zero;
    return p;
}

// @ 0x00de6e80 -- FUN_00de6e80 (__thiscall: this in ecx, one stack argument)
// Removes the entry for `param_2` from the resource-manager rbtree at +0x70
// (inserting a fresh record if the key is unknown) and then unlinks the same
// key from the feedback-event rbtree at +0x1c.
struct S00de6e80 {
    void FUN_00de6e80(int param_2);
};

void S00de6e80::FUN_00de6e80(int param_2) {
    void* out[2];
    struct Key {
        unsigned int id;
        unsigned int h;
        unsigned int f;
    } key;
    key.id = (unsigned int)param_2;
    key.h = 0x011989b7u;
    key.f = 0x4084a100u;
    int* p = (int*)((CFind70*)((char*)this + 0x70))->find(out, &key);
    if (*p != (int)((char*)this + 0x74)) {
        *(unsigned char*)&out[0] = 0;
        ((CInsert*)this)->insert(out, &param_2, (unsigned int)(unsigned long)out[0]);
    }
    CFind1c* t = (CFind1c*)((char*)this + 0x1c);
    t->find(out, &param_2);
    unsigned int node = (unsigned int)(unsigned long)out[0];
    if (node != (unsigned int)(unsigned long)((char*)t + 4)) {
        *(int*)((char*)t + 0x14) -= 1;
        RBTreeIncrement((void*)(unsigned long)node);
        RBTreeErase((void*)(unsigned long)node, (void*)((char*)t + 4));
        freeNode((void*)(unsigned long)node);
    }
}

// ---------------------------------------------------------------------------
// Types shared by the GGE user-data family below.  Every member is named for
// the role its offset plays in the original (docs/matching.md).
// ---------------------------------------------------------------------------

// eastl red-black-tree control block.  The five trees of the main object sit
// exactly 0x1c bytes apart; mpRight points at mpLeft while the tree is empty
// and mpRoot is the node handed to the non-recursive subtree destructor.
struct ERBTree {
    void*         mpNode;    // +0x00
    void*         mpLeft;    // +0x04  (begin(); self-linked while empty)
    void*         mpRight;   // +0x08  (== &mpLeft while empty)
    void*         mpRoot;    // +0x0c  (root passed to DoNukeSubtree)
    union {
        unsigned char mFlag;     // +0x10  red/black flag byte
        unsigned int  mFlagWord; // +0x10  the whole word, zeroed by init passes
    };
    unsigned int  mCount;    // +0x14
    void*         mpPad18;   // +0x18
    void DoNukeSubtree(void* root);   // 0x9a9600
    void* find(void* out, void* key);                  // 0xe5c780
    void  insert(void* out, void* key, unsigned int);  // 0xa17a70
};

// Reference-counted interface object: the destructor below calls vtable slot 1
// to release and slot 2 to destroy.
struct CRefCounted {
    virtual void V00();      // +0x00
    virtual void Release();  // +0x04
    virtual void Destroy();  // +0x08
};

// Two-slot eastl iterator/insert helper used by the container routines.
struct CFindMixin {
    void* find(void* out, void* key);                 // 0xe5c780
    void  insert(void* out, void* key, unsigned int);  // 0xa17a70
};

// A record-stream source: the reader exposes a stream object through slot
// +0x20 and repositions it through slot +0x1c, while the stream object itself
// hands out the EA::IO stream through slot +0x18.
struct CRecordStream {
    virtual void V00(); virtual void V04(); virtual void V08();
    virtual void V0c(); virtual void V10(); virtual void V14();
    virtual void* GetStream();   // +0x18
};
struct CRecordSource {
    virtual void V00(); virtual void V04(); virtual void V08();
    virtual void V0c(); virtual void V10(); virtual void V14();
    virtual void* GetStream();   // +0x18
    virtual void  Next();        // +0x1c
    virtual CRecordStream* GetSource();  // +0x20
    virtual void  V24();
};

void EA_IO_ReadInt32(void* stream, void* dst, int count, int separator);  // 0x93a780

// @ 0x00de6840 -- FUN_00de6840 (__cdecl: (record reader, tree))
// Clears the tree and refills it from the reader: the entry count is read
// through the reader's virtual stream accessors, then each record is read,
// the reader is advanced and the record re-inserted into the tree.
void __cdecl FUN_00de6840(CRecordSource* reader, ERBTree* tree) {
    unsigned int count = 0;
    unsigned int value;
    void* iter[2];
    unsigned int i;
    union { unsigned int mDword; unsigned char mByte; } flag;

    tree->DoNukeSubtree(tree->mpRoot);
    tree->mpLeft = &tree->mpLeft;
    tree->mpRight = &tree->mpLeft;
    tree->mpRoot = 0;
    tree->mFlag = 0;
    tree->mCount = 0;
    void* stream = reader->GetSource()->GetStream();
    EA_IO_ReadInt32(stream, &count, 1, 0);
    i = 0;
    while (i < count) {
        stream = reader->GetSource()->GetStream();
        EA_IO_ReadInt32(stream, &value, 1, 0);
        reader->Next();
        flag.mByte = 0;
        ((CFindMixin*)tree)->insert(iter, &value, flag.mDword);
        i++;
    }
    reader->Next();
}

// ---------------------------------------------------------------------------
// Simulator / planet-model interfaces touched by the minimap helpers.
// ---------------------------------------------------------------------------

// Object embedded at +0x04 of the simulator state; only its +0x3c entry point
// (shared with cBigEditorObject::Activate-style layout) is used here.
struct CSimMinimapSink {
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38();
    virtual void SetMinimap(int x, int y);      // +0x3c
};

struct CListNode {
    CListNode* mpNext;      // +0x00
};

// State returned by FUN_00b3d360 (the active Simulator/star-map object).
struct CSimState {
    void*           mpVtbl00;   // +0x00
    CSimMinimapSink mSink;      // +0x04
    unsigned int    mPad08[6];  // +0x08 .. +0x1f
    CListNode       mListHead;  // +0x20 (self-linked circular list)
    unsigned int    mPad24[4];  // +0x24 .. +0x33
    unsigned int    mCount34;   // +0x34
    bool IsWorldActive(unsigned int* pKey);   // 0xb7d4f0
    void AttachPlanet(void* planet);          // 0xb7daf0
};

struct CPlanetModel {
    void UpdateMinimap(int x, int y, int z);    // 0xb8c330
};

struct CBigEditorObject {
    void Activate(char, const char* tag, char); // 0xe3e350
};

CSimState*       __cdecl FUN_00b3d360();        // 0xb3d360
CPlanetModel*    __cdecl SP_PlanetModel();      // 0xb3d350
CBigEditorObject* __cdecl FUN_00b3d410();       // 0xb3d410

extern unsigned char DAT_016a0e08;
extern unsigned char DAT_016a140c;
extern unsigned char DAT_016a0e18;
extern unsigned int  DAT_016a1408;

// eastl::wstring header (+0x00 begin, +0x04 end, +0x08 capacity).
struct CWString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
};

// Layout sub-object at +0x144 (constructed by 0x810000, destroyed by 0x811fe0).
struct CSPUILayout {
    unsigned int mData[6];      // +0x00 .. +0x17
    void Construct();           // 0x810000
    void Destroy();             // 0x811fe0
};

// Container at +0x1d8 (destroyed by FUN_004b5440).
struct CDe1d8Block {
    unsigned int mBegin;        // +0x00
    unsigned int mEnd;          // +0x04
    unsigned int mCap;          // +0x08
    void Destroy();             // 0x4b5440
};

void __cdecl EA_OperatorDelete(void* p);      // 0xf47380
void __cdecl EA_Messaging_RemoveHandler(void* handler, void* a, void* b, void* c, void* d); // 0x571db0

// Frees an eastl wide-string buffer that is no longer backed by the shared
// empty string: the original evens the byte span and compares it against two
// with a signed test.
__forceinline void FreeStringBuffer(wchar_t* begin, wchar_t* cap) {
    long bytes = (long)((char*)cap - (char*)begin);
    if (((bytes & ~1L) > 2) && begin != 0)
        EA_OperatorDelete(begin);
}

// The GGE user-data container built by FUN_00de6be0 and torn down by
// FUN_00de6170.  Member offsets mirror the original exactly; see the note on
// ERBTree above for why +0x00 is the end() target of an iteration while
// rbtree::find compares against &mpLeft.
struct CGGEUserData {
    void*           mpVtbl00;      // +0x000
    void*           mpVtbl04;      // +0x004
    void*           mpVtbl08;      // +0x008
    void*           mpVtbl0c;      // +0x00c
    void*           mpHandler;     // +0x010 (EA::Messaging handler)
    void*           mHandlerArg0;  // +0x014
    void*           mHandlerArg1;  // +0x018
    void*           mHandlerArg2;  // +0x01c
    void*           mHandlerArg3;  // +0x020
    void*           mpHeap24;      // +0x024
    unsigned int    mZero28;       // +0x028
    unsigned int    mZero2c;       // +0x02c
    unsigned int    mPad30;        // +0x030
    unsigned int    mPad34;        // +0x034
    unsigned int    mZero38;       // +0x038
    ERBTree         mTree3c;       // +0x03c
    ERBTree         mTree58;       // +0x058
    ERBTree         mTree74;       // +0x074
    ERBTree         mTree90;       // +0x090
    ERBTree         mTreeAc;       // +0x0ac
    unsigned char   mFlagC8;       // +0x0c8
    unsigned char   mFlagC9;       // +0x0c9
    unsigned char   mPadCa[2];     // +0x0ca
    unsigned int    mZeroCc;       // +0x0cc
    CWString        mPath;         // +0x0d0
    unsigned int    mPadDc;        // +0x0dc
    unsigned int    mZeroE0;       // +0x0e0
    unsigned char   mFlagE4;       // +0x0e4
    unsigned char   mPadE5[3];     // +0x0e5
    unsigned int    mZeroE8;       // +0x0e8
    unsigned char   mByteEc;       // +0x0ec
    unsigned char   mByteEd;       // +0x0ed
    unsigned char   mByteEe;       // +0x0ee
    unsigned char   mByteEf;       // +0x0ef
    unsigned int    mZeroF0;       // +0x0f0
    unsigned char   mByteF4;       // +0x0f4
    unsigned char   mPadF5[3];     // +0x0f5
    unsigned int    mZeroF8;       // +0x0f8
    unsigned int    mZeroFc;       // +0x0fc
    unsigned char   mByte100;      // +0x100
    unsigned char   mByte101;      // +0x101
    unsigned char   mByte102;      // +0x102
    unsigned char   mFlag103;      // +0x103
    unsigned char   mByte104;      // +0x104
    unsigned char   mPad105[3];    // +0x105
    unsigned int    mZero108;      // +0x108
    unsigned int    mConst10c;     // +0x10c (initialised to 9)
    void*           mpHeap110;     // +0x110
    unsigned int    mZero114;      // +0x114
    unsigned int    mZero118;      // +0x118
    unsigned int    mPad11c;       // +0x11c
    unsigned int    mPad120;       // +0x120
    ERBTree         mTree124;      // +0x124
    unsigned int    mPad140;       // +0x140
    CSPUILayout     mLayout144;    // +0x144
    CRefCounted*    mpRef15c;      // +0x15c
    CRefCounted*    mpRef160;      // +0x160
    CRefCounted*    mpRef164;      // +0x164
    CRefCounted*    mpRef168;      // +0x168
    CRefCounted*    mpRef16c;      // +0x16c
    CRefCounted*    mpRef170;      // +0x170
    CRefCounted*    mpRef174;      // +0x174
    unsigned int    mZero178;      // +0x178
    unsigned char   mByte17c;      // +0x17c
    unsigned char   mPad17d[3];    // +0x17d
    unsigned int    mPad180;       // +0x180
    unsigned int    mZero184;      // +0x184
    unsigned int    mZero188;      // +0x188
    unsigned int    mZero18c;      // +0x18c
    unsigned int    mZero190;      // +0x190
    float           mZero194;      // +0x194
    CRefCounted*    mpRef198;      // +0x198
    CRefCounted*    mpRef19c;      // +0x19c
    CRefCounted*    mpRef1a0;      // +0x1a0
    CRefCounted*    mpRef1a4;      // +0x1a4
    CRefCounted*    mpRef1a8;      // +0x1a8
    CRefCounted*    mpRef1ac;      // +0x1ac
    CRefCounted*    mpRef1b0;      // +0x1b0
    CRefCounted*    mpRef1b4;      // +0x1b4
    CRefCounted*    mpRef1b8;      // +0x1b8
    CRefCounted*    mpRef1bc;      // +0x1bc
    CRefCounted*    mpRef1c0;      // +0x1c0
    CRefCounted*    mpRef1c4;      // +0x1c4
    CRefCounted*    mpRef1c8;      // +0x1c8
    CRefCounted*    mpRef1cc;      // +0x1cc
    CRefCounted*    mpRef1d0;      // +0x1d0
    CRefCounted*    mpRef1d4;      // +0x1d4
    CDe1d8Block     mBlock1d8;     // +0x1d8
    unsigned int    mPad1e4;       // +0x1e4
    unsigned int    mPad1e8;       // +0x1e8
    unsigned int    mZero1ec;      // +0x1ec
    unsigned char   mByte1f0;      // +0x1f0
    unsigned char   mByte1f1;      // +0x1f1
    unsigned char   mPad1f2[3];    // +0x1f2
    unsigned char   mByte1f5;      // +0x1f5
    unsigned char   mByte1f6;      // +0x1f6
    unsigned char   mPad1f7;       // +0x1f7
    unsigned int    mZero1f8;      // +0x1f8
    unsigned int    mZero1fc;      // +0x1fc
    unsigned int    mPad200[19];   // +0x200 .. +0x24b
    unsigned char   mByte24c;      // +0x24c
    unsigned char   mByte24d;      // +0x24d
    unsigned char   mPad24e[2];    // +0x24e
    void*           mpPtr250;      // +0x250
    ERBTree         mTree254;      // +0x254
    unsigned char   mByte270;      // +0x270
    unsigned char   mByte271;      // +0x271

    void FUN_00de6650(float x, float y);
};

// @ 0x00de6650 -- FUN_00de6650 (__thiscall: this in ecx, two float arguments)
// Rebuilds the minimap when the star-map state changed: tracks the transition
// of the "map open" flag, walks the simulator's world list to count worlds,
// forwards the scaled coordinates to the minimap and the planet model, and
// activates the editor object when the flag is toggled off.
void CGGEUserData::FUN_00de6650(float x, float y) {
    int roundedY = (int)(y * 1000.0f);
    int roundedX = (int)(x * 1000.0f);
    CSimState* sim = FUN_00b3d360();
    if (sim->mListHead.mpNext == &sim->mListHead && sim->mCount34 == 0) {
        if (DAT_016a140c == 0) {
            mTree58.DoNukeSubtree(mTree58.mpRoot);
            mTree58.mpLeft = &mTree58.mpLeft;
            mTree58.mpRight = &mTree58.mpLeft;
            mTree58.mpRoot = 0;
            mTree58.mFlag = 0;
            mTree58.mCount = 0;
        } else {
            mTree58.DoNukeSubtree(mTree58.mpRoot);
            mTree58.mpLeft = &mTree58.mpLeft;
            mTree58.mpRight = &mTree58.mpLeft;
            mTree58.mpRoot = 0;
            mTree58.mFlag = 0;
            mTree58.mCount = 0;
            DAT_016a140c = 0;
            if (DAT_016a0e18 != 0)
                FUN_00b3d410()->Activate(0, (const char*)0x1654c05, 0);
        }
    } else if (DAT_016a0e08 == 0) {
        if (DAT_016a140c != 0) {
            DAT_016a140c = 0;
            if (DAT_016a0e18 != 0)
                FUN_00b3d410()->Activate(0, (const char*)0x2ccd1d2, 0);
        }
    } else {
        DAT_016a140c = 1;
        CSimState* counted = FUN_00b3d360();
        unsigned int count = 0;
        for (CListNode* n = counted->mListHead.mpNext; n != &counted->mListHead; n = n->mpNext)
            count++;
        CSimState* target = FUN_00b3d360();
        target->mSink.SetMinimap(roundedY, roundedX);
        SP_PlanetModel()->UpdateMinimap(roundedY, 0, 0);
        if (count != DAT_016a1408)
            DAT_016a1408 = count;
    }
}

// ---------------------------------------------------------------------------
// World/feedback container used by FUN_00de7010 and FUN_00de6f20.  The first
// two trees are looked up through rbtree::find (which compares against
// &mpLeft); the third is walked directly from mpLeft to &mpNode.
// ---------------------------------------------------------------------------
struct CWorldEntry {          // node of the world tree at +0x3c
    void*        mpNode;      // +0x00
    void*        mpLeft;      // +0x04
    void*        mpRight;     // +0x08
    void*        mpPad0c;     // +0x0c
    unsigned int mId;         // +0x10 (property-list id)
    unsigned int mPad14;      // +0x14
    unsigned int mPad18;      // +0x18
    unsigned int mKey;        // +0x1c (rbtree key)
};

struct CPropertyList;
struct CGGEPlanet;
struct CBannerGroup;
struct CStarManager;

struct CPropertyList {
    void Construct();                           // 0xb8e180
    void AssignCopy(CPropertyList* src);        // 0xb8f030
    void SetKey(unsigned int* pKey, int flag);  // 0xb8dde0
    void SetId(unsigned int* pId);              // 0xb8da30
};
struct CGGEPlanet {
    void Construct();                           // 0xc725a0
    void SetProperties(CPropertyList* list);    // 0xc71750
};
struct CBannerGroup {
    CPropertyList* GetList(int index);          // 0xbbaa60
};
struct CStarManager {
    CBannerGroup* GetBannerGroup();             // 0xba6d80
};
CStarManager* __cdecl FUN_00b3d2a0(int);        // 0xb3d2a0
void* __cdecl EA_ZoneObjectNew(int size, const char* zone, int, int, int, int);        // 0xf473a0
void* __cdecl EA_ZoneObjectNewSim(int size, const char* zone, int, int, int, int);     // 0x926020

struct CFeedbackStore {
    ERBTree      mTree00;      // +0x00
    ERBTree      mTree1c;      // +0x1c
    unsigned int mPad38;       // +0x38
    ERBTree      mTree3c;      // +0x3c

    void FUN_00de6f20(unsigned int* pId, unsigned int* pKey);
    void FUN_00de7010();
};

// @ 0x00de6f20 -- FUN_00de6f20 (__thiscall: this in ecx, two stack arguments)
// Creates the Simulator/GGE property list and planet object for a world node
// that has no feedback entry yet, wires the record into the property list and
// inserts it into the tree at +0x1c.
void CFeedbackStore::FUN_00de6f20(unsigned int* pId, unsigned int* pKey) {
    void* it[2];
    union { unsigned int mDword; unsigned char mByte; } flag;

    if (*(void**)mTree00.find(it, pKey) != (void*)&mTree00.mpLeft)
        return;

    CStarManager* manager = FUN_00b3d2a0(0);
    CBannerGroup* group = manager->GetBannerGroup();
    CPropertyList* source = group->GetList(0);

    CPropertyList* list = 0;
    void* mem = EA_ZoneObjectNew(0x1b0, "Simulator/GGE", 0, 0, 0, 0);
    if (mem != 0) {
        ((CPropertyList*)mem)->Construct();
        list = (CPropertyList*)mem;
    }
    list->AssignCopy(source);
    list->SetKey(pKey, 0);
    list->SetId(pId);
    flag.mByte = 0;
    mTree1c.insert(it, pKey, flag.mDword);

    CGGEPlanet* planet = 0;
    void* memPlanet = EA_ZoneObjectNew(0x1c8, "Simulator/GGE", 0, 0, 0, 0);
    if (memPlanet != 0) {
        ((CGGEPlanet*)memPlanet)->Construct();
        planet = (CGGEPlanet*)memPlanet;
    }
    planet->SetProperties(list);
    FUN_00b3d360()->AttachPlanet(planet);
}

// @ 0x00de7010 -- FUN_00de7010 (__thiscall: this in ecx, no stack arguments)
// Walks the world tree at +0x3c (at most ten entries) and materialises the
// Simulator/GGE feedback records for every world that is not active and not
// already present in both feedback trees.
void CFeedbackStore::FUN_00de7010() {
    CSimState* sim = FUN_00b3d360();
    if (sim->mListHead.mpNext != &sim->mListHead || sim->mCount34 != 0)
        return;

    CWorldEntry* node = (CWorldEntry*)mTree3c.mpLeft;
    void* end = (void*)&mTree3c.mpNode;
    void* iter[2];
    unsigned int n = 0;
    if ((void*)node == end)
        return;
    do {
        if (n >= 10)
            return;
        unsigned int* pKey = &node->mKey;
        unsigned int* pId = &node->mId;
        bool skip = false;
        if (FUN_00b3d360()->IsWorldActive(pKey)) {
            if (*(void**)mTree00.find(iter, pKey) != (void*)&mTree00.mpLeft)
                skip = true;
            else if (*(void**)mTree1c.find(iter, pKey) != (void*)&mTree1c.mpLeft)
                skip = true;
        }
        if (!skip) {
            n++;
            FUN_00de6f20(pId, pKey);
        }
        node = (CWorldEntry*)RBTreeIncrement(node);
    } while ((void*)node != end);
}

// ---------------------------------------------------------------------------
// World-key container: nodes carry the 12-byte key at +0x10/+0x14/+0x18 and
// the tree control block is the usual ERBTree at +0x00 (end() == &mpLeft,
// element count at +0x14).
// ---------------------------------------------------------------------------
struct CWorldNode {
    CWorldNode*  mpParent;   // +0x00
    CWorldNode*  mpLeft;     // +0x04
    CWorldNode*  mpRight;    // +0x08
    CWorldNode*  mpPad0c;    // +0x0c
    unsigned int mId;        // +0x10
    unsigned int mPartB;     // +0x14
    unsigned int mPartC;     // +0x18
};

struct CWorldKey {
    unsigned int mId;        // +0x00
    unsigned int mPartB;     // +0x04
    unsigned int mPartC;     // +0x08
};

// The container's ordering predicate compares the id, then the last key word,
// then the middle word.
inline bool WorldKeyLess(const CWorldNode* node, const CWorldKey* key) {
    if (node->mId != key->mId)
        return node->mId < key->mId;
    if (node->mPartC != key->mPartC)
        return node->mPartC < key->mPartC;
    return node->mPartB < key->mPartB;
}
inline bool WorldKeyLess(const CWorldKey* key, const CWorldNode* node) {
    if (key->mId != node->mId)
        return key->mId < node->mId;
    if (key->mPartC != node->mPartC)
        return key->mPartC < node->mPartC;
    return key->mPartB < node->mPartB;
}

void __cdecl RBTreeInsert(void* node, void* parent, void* anchor, int side); // 0x9216a0

struct CWorldContainer {
    ERBTree tree;       // +0x00

    void* NewNode(CWorldKey* key);                                        // 0xde4e20
    void* InsertAfter(void** out, CWorldNode* pos, CWorldKey* key, int);  // 0xde5740
    void* InsertUnique(void** out, CWorldKey* key, int);                  // 0xde5f60
    void* Insert(void** out, CWorldNode* pos, CWorldKey* key, unsigned int reserved);
};

// @ 0x00de6900 -- FUN_00de6900 (__thiscall: this in ecx, four stack arguments)
// Inserts a key relative to a hint position, mirroring eastl::rbtree's hinted
// insert: an end/hint position takes the fast path against the current root,
// otherwise the position and its successor bracket the key and the node is
// linked through RBTreeInsert.  The last declared argument is not referenced by
// the original but is still popped by the callee (ret 0x10).
void* CWorldContainer::Insert(void** out, CWorldNode* pos, CWorldKey* key, unsigned int) {
    if (pos == (CWorldNode*)tree.mpLeft || pos == (CWorldNode*)&tree.mpLeft) {
        if (tree.mCount != 0) {
            CWorldNode* root = (CWorldNode*)tree.mpLeft;
            if (WorldKeyLess(root, key)) {
                InsertAfter(out, root, key, 0);
                return out;
            }
        }
        void* iter[2];
        union { unsigned int mDword; unsigned char mByte; } flag;
        flag.mByte = 0;
        InsertUnique(iter, key, flag.mDword);
        *out = iter[0];
        return out;
    }

    CWorldNode* next = (CWorldNode*)RBTreeIncrement(pos);
    if (WorldKeyLess(pos, key) && WorldKeyLess(key, next)) {
        if (pos->mpParent != 0) {
            void* node = NewNode(key);
            RBTreeInsert(node, next, &tree.mpLeft, 0);
            tree.mCount++;
            *out = node;
            return out;
        }
        InsertAfter(out, pos, key, 0);
        return out;
    }

    void* iter[2];
    union { unsigned int mDword; unsigned char mByte; } flag;
    flag.mByte = 0;
    InsertUnique(iter, key, flag.mDword);
    *out = iter[0];
    return out;
}

// @ 0x00de6be0 -- FUN_00de6be0 (__fastcall: this in ecx, returns this)
// Constructor of the GGE user-data container.  Installs the two layers of
// vtables, clears the handler/refcount block, self-links the five intrusive
// lists through FUN_00de67b0, resets the path string to the shared empty
// eastl::wstring, initialises the remaining flags and the three embedded
// rbtree control blocks, runs the cSPUILayout constructor at +0x144 and clears
// the trailing object pointer.
CGGEUserData* __fastcall FUN_00de6be0(CGGEUserData* p) {
    // Known vtables/labels installed by the original sequence.
    p->mpVtbl04 = (void*)0x14426a0;
    p->mpVtbl08 = (void*)0x13eb384;
    p->mpVtbl00 = (void*)0x147e0fc;
    p->mpVtbl04 = (void*)0x147e0e0;
    p->mpVtbl08 = (void*)0x147e0d0;
    p->mpVtbl0c = (void*)0x147e0c4;

    p->mpHandler = 0;
    p->mHandlerArg0 = 0;
    p->mHandlerArg1 = 0;
    p->mHandlerArg2 = 0;
    p->mHandlerArg3 = 0;
    p->mpHeap24 = 0;
    p->mZero28 = 0;
    p->mZero2c = 0;
    p->mZero38 = 0;

    FUN_00de67b0((int)(unsigned long)&p->mTree3c);

    p->mFlagC9 = 0;
    p->mZeroCc = 0;
    p->mFlagC8 = 1;
    p->mPath.mpCap = (wchar_t*)0x1667bae;
    p->mPath.mpBegin = (wchar_t*)0x1667bac;   // eastl::gEmptyString16
    p->mPath.mpEnd = (wchar_t*)0x1667bac;
    p->mFlagE4 = 1;
    p->mFlag103 = 1;
    p->mZeroE0 = 0;
    p->mZeroE8 = 0;
    p->mByteEc = 0;
    p->mByteEd = 0;
    p->mByteEe = 0;
    p->mByteEf = 0;
    p->mZeroF0 = 0;
    p->mByteF4 = 0;
    p->mZeroF8 = 0;
    p->mZeroFc = 0;
    p->mByte100 = 0;
    p->mByte101 = 0;
    p->mByte102 = 0;
    p->mByte104 = 0;
    p->mZero108 = 0;
    p->mConst10c = 9;
    p->mpHeap110 = 0;
    p->mZero114 = 0;
    p->mZero118 = 0;

    // Control block at +0x124: cleared and then self-linked (both phases kept).
    // The leading word is left untouched by the original; the clear pass zeroes
    // the flag word as a whole, the link pass only its low byte.
    p->mTree124.mpRight = 0;
    p->mTree124.mpRoot = 0;
    p->mTree124.mFlagWord = 0;
    p->mTree124.mpRight = &p->mTree124.mpLeft;
    p->mTree124.mpRoot = 0;
    p->mTree124.mFlag = 0;
    p->mTree124.mCount = 0;
    p->mTree124.mpLeft = &p->mTree124.mpLeft;

    p->mLayout144.Construct();

    p->mpRef15c = 0;
    p->mpRef160 = 0;
    p->mpRef164 = 0;
    p->mpRef168 = 0;
    p->mpRef16c = 0;
    p->mpRef170 = 0;
    p->mpRef174 = 0;
    p->mZero178 = 0;
    p->mByte17c = 0;
    p->mZero184 = 0;
    p->mZero188 = 0;
    p->mZero18c = 0;
    p->mZero190 = 0;
    p->mZero194 = 0.0f;
    p->mpRef198 = 0;
    p->mpRef19c = 0;
    p->mpRef1a0 = 0;
    p->mpRef1a4 = 0;
    p->mpRef1a8 = 0;
    p->mpRef1ac = 0;
    p->mpRef1b0 = 0;
    p->mpRef1b4 = 0;
    p->mpRef1b8 = 0;
    p->mpRef1bc = 0;
    p->mpRef1c0 = 0;
    p->mpRef1c4 = 0;
    p->mpRef1c8 = 0;
    p->mpRef1cc = 0;
    p->mpRef1d0 = 0;
    p->mpRef1d4 = 0;
    p->mBlock1d8.mBegin = 0;
    p->mBlock1d8.mEnd = 0;
    p->mBlock1d8.mCap = 0;
    p->mZero1ec = 0;
    p->mByte1f0 = 0;
    p->mByte1f1 = 0;
    p->mByte1f5 = 0;
    p->mByte1f6 = 0;
    p->mZero1f8 = 0;
    p->mZero1fc = 0;
    p->mByte24c = 0;
    p->mByte24d = 0;
    p->mpPtr250 = 0;

    // Control block at +0x254: same cleared-then-self-linked shape.
    p->mTree254.mpRight = 0;
    p->mTree254.mpRoot = 0;
    p->mTree254.mFlagWord = 0;
    p->mTree254.mpRight = &p->mTree254.mpLeft;
    p->mTree254.mpRoot = 0;
    p->mTree254.mFlag = 0;
    p->mTree254.mCount = 0;
    p->mTree254.mpLeft = &p->mTree254.mpLeft;

    p->mByte270 = 0;
    p->mByte271 = 0;
    return p;
}

// EA heap allocation header: a non-zero cookie word marks a live block whose
// payload the destructor owns.
struct CHeapCookie {
    unsigned int mCookie;   // +0x00 (immediately before the payload)
};

// @ 0x00de6170 -- FUN_00de6170 (__fastcall: this in ecx)
// Destructor of the GGE user-data container: reinstalls the base vtables,
// tears down the tree and pointer members in reverse construction order, frees
// the two heap blocks, the path string and the messaging handler, and finally
// leaves the two base-class vtables in place.
void __fastcall FUN_00de6170(CGGEUserData* p) {
    p->mpVtbl00 = (void*)0x147e0fc;
    p->mpVtbl04 = (void*)0x147e0e0;
    p->mpVtbl08 = (void*)0x147e0d0;
    p->mpVtbl0c = (void*)0x147e0c4;

    p->mTree254.DoNukeSubtree(p->mTree254.mpRoot);
    if (p->mpPtr250 != 0)
        ((CRefCounted*)p->mpPtr250)->Destroy();

    p->mBlock1d8.Destroy();

    if (p->mpRef1d4 != 0) p->mpRef1d4->Release();
    if (p->mpRef1d0 != 0) p->mpRef1d0->Release();
    if (p->mpRef1cc != 0) p->mpRef1cc->Release();
    if (p->mpRef1c8 != 0) p->mpRef1c8->Release();
    if (p->mpRef1c4 != 0) p->mpRef1c4->Release();
    if (p->mpRef1c0 != 0) p->mpRef1c0->Release();
    if (p->mpRef1bc != 0) p->mpRef1bc->Release();
    if (p->mpRef1b8 != 0) p->mpRef1b8->Release();
    if (p->mpRef1b4 != 0) p->mpRef1b4->Release();

    if (p->mpRef1b0 != 0) p->mpRef1b0->Release();
    if (p->mpRef1ac != 0) p->mpRef1ac->Release();
    if (p->mpRef1a8 != 0) p->mpRef1a8->Release();
    if (p->mpRef1a4 != 0) p->mpRef1a4->Release();
    if (p->mpRef1a0 != 0) p->mpRef1a0->Release();
    if (p->mpRef19c != 0) p->mpRef19c->Release();
    if (p->mpRef198 != 0) p->mpRef198->Release();

    if (p->mpRef174 != 0) p->mpRef174->Release();
    if (p->mpRef170 != 0) p->mpRef170->Release();
    if (p->mpRef16c != 0) p->mpRef16c->Release();
    if (p->mpRef168 != 0) p->mpRef168->Release();
    if (p->mpRef164 != 0) p->mpRef164->Release();
    if (p->mpRef160 != 0) p->mpRef160->Release();
    if (p->mpRef15c != 0) p->mpRef15c->Release();

    p->mLayout144.Destroy();
    p->mTree124.DoNukeSubtree(p->mTree124.mpRoot);

    if (p->mpHeap110 != 0 && ((CHeapCookie*)p->mpHeap110)[-1].mCookie != 0)
        EA_OperatorDelete(p->mpHeap110);

    // The path buffer is only owned when at least two wide characters were
    // allocated past the shared empty string.
    FreeStringBuffer(p->mPath.mpBegin, p->mPath.mpCap);

    p->mTreeAc.DoNukeSubtree(p->mTreeAc.mpRoot);
    p->mTree90.DoNukeSubtree(p->mTree90.mpRoot);
    p->mTree74.DoNukeSubtree(p->mTree74.mpRoot);
    p->mTree58.DoNukeSubtree(p->mTree58.mpRoot);
    p->mTree3c.DoNukeSubtree(p->mTree3c.mpRoot);

    if (p->mpHeap24 != 0 && ((CHeapCookie*)p->mpHeap24)[-1].mCookie != 0)
        EA_OperatorDelete(p->mpHeap24);

    if (p->mpHandler != 0) {
        void* handler = p->mpHandler;
        void* arg0 = p->mHandlerArg0;
        void* arg1 = p->mHandlerArg1;
        void* arg2 = p->mHandlerArg2;
        void* arg3 = p->mHandlerArg3;
        p->mpHandler = 0;
        EA_Messaging_RemoveHandler(handler, arg0, arg1, arg2, arg3);
    }

    p->mpVtbl04 = (void*)0x13eb938;
    p->mpVtbl08 = (void*)0x13eb394;
}

// eastl::wstring (16-bit characters) with the allocation layout used here.
struct CEastlString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08

    void RangeInitialize(const wchar_t* text);                 // 0x579a90
    void AllocateSelf(int capacity);                           // 0x429760
    void assign(const wchar_t* begin, const wchar_t* end);     // 0x423650
    void AssignFrom(const CEastlString* other);
};

void __cdecl EA_Memcpy(void* dst, const void* src, unsigned int size);  // 0x11e0744
CEastlString* __cdecl PathPick(CEastlString* out, CEastlString* in, CEastlString* dir); // 0x688f00

struct CStringPairView {   // the two leading pointers of a range view
    const wchar_t* mpBegin;    // +0x00
    const wchar_t* mpEnd;      // +0x04
};

void CEastlString::AssignFrom(const CEastlString* other) {
    assign(other->mpBegin, other->mpEnd);
}

// Save-area / database / serializer interfaces used by the loader.
struct ISaveArea {
    virtual void  V00();
    virtual void  V04();
    virtual void  V08();
    virtual void  V0c();
    virtual void  V10();
    virtual void  V14();
    virtual void  V18();
    virtual void  V1c();
    virtual void  V20();
    virtual void  V24();
    virtual wchar_t* GetSavePath();    // +0x28
};
ISaveArea* __cdecl SP_GetSaveArea(int tag);      // 0x6b1f90

// Sub-object at +0x04 of the packed-file wrapper: slot 0 adds a reference,
// slot 1 releases it.
struct CFileSink {
    virtual void AddRef();                     // +0x00
    virtual void Release();                    // +0x04
};
struct CDatabasePackedFile {
    void*     mPad00;                          // +0x00
    CFileSink mSink;                           // +0x04
    void Construct(const wchar_t* path, void* alloc, void* alloc2);   // 0x8d9f80
};

// The object database exposes its navigation interface through the base
// vtable and its stream interface through the sub-object at +0x04.
struct CDbBase {
    virtual void B00();                        // +0x00
    virtual void B04();                        // +0x04
    virtual void B08(); virtual void B0c();
    virtual void B10(); virtual void B14(); virtual void B18(); virtual void B1c();
    virtual void B20(); virtual void B24(); virtual void B28(); virtual void B2c();
    virtual void B30(); virtual void B34(); virtual void B38();
    virtual bool Init(int flags, int arg);     // +0x3c
};
struct CDbStream {
    virtual void S00();                        // +0x00
    virtual void S04();                        // +0x04
    virtual void S08();                        // +0x08
    virtual void S0c(); virtual void S10(); virtual void S14(); virtual void S18();
    virtual void Advance();                    // +0x1c
    virtual void S20(); virtual void S24(); virtual void S28();
    virtual void SetPath(const wchar_t* path); // +0x2c
};
struct CObjectDatabase {
    CDbBase   mBase;                           // +0x00
    CDbStream mStream;                         // +0x04
    void Construct(CDatabasePackedFile* file); // 0x69fa60
};

void __cdecl FUN_00693cd0(void* db, void* a, void* b, void* c);  // 0x693cd0

// Record produced by C3::ctorA (0x693cd0): sixteen bytes in the frame slot that
// the earlier PathPick result vacated.  The serializer deserialises the payload
// pointer at +0x08.
struct C3Record {
    void*       mpField00;   // +0x00
    void*       mpField04;   // +0x04
    void*       mpPayload;   // +0x08
    void*       mpField0c;   // +0x0c
    C3Record* Ctor(void* db, void* a, void* b, void* c);   // 0x693cd0
    void      Destroy();                                   // 0x693900
};

// Variable-list serializer.  Only its address is used here, but it occupies
// 0x48 bytes of the original frame, so the storage is spelled out to keep the
// neighbouring locals safe.
struct CVarListSerializer {
    unsigned char mStorage[0x48];                            // +0x00..+0x47
    void Construct(void* area, const void* name, int tag);   // 0x692f90
    void Read(void* arg);                                    // 0x693e10
};

// @ 0x00de63e0 -- FUN_00de63e0 (__fastcall: the incoming ecx is spilled to the
// frame and later forwarded as the first argument of the serializer
// constructor, so it is a real register argument)
// Loads L"GGEUserData.dat" out of the save area, resolves it through PathPick,
// opens it as a packed-file database, walks the object database and, when it
// initialises, reads the variable-list serializer payload.
void __fastcall FUN_00de63e0(void* owner) {
    CEastlString fileName;
    CEastlString savePath;
    CEastlString fullPath;

    fileName.mpBegin = 0;
    fileName.mpEnd = 0;
    fileName.mpCap = 0;
    fileName.RangeInitialize(L"GGEUserData.dat");

    ISaveArea* area = SP_GetSaveArea(0x4729a47);
    const wchar_t* rawSavePath = area->GetSavePath();

    savePath.mpBegin = 0;
    savePath.mpEnd = 0;
    savePath.mpCap = 0;
    savePath.RangeInitialize(rawSavePath);

    const wchar_t* saveBegin = savePath.mpBegin;
    int saveLen = (int)((char*)savePath.mpEnd - (char*)saveBegin) >> 1;

    fullPath.mpBegin = 0;
    fullPath.mpEnd = 0;
    fullPath.mpCap = 0;
    fullPath.AllocateSelf(saveLen + 1);
    wchar_t* fullBegin = fullPath.mpBegin;
    EA_Memcpy(fullBegin, saveBegin, (unsigned int)saveLen * 2);
    fullPath.mpEnd = fullBegin + saveLen;
    *fullPath.mpEnd = 0;

    // One frame slot serves two purposes in the original: PathPick's result
    // string, then the C3 record built inside the "initialised" branch.
    union {
        CEastlString mPicked;    // +0x00, 12 bytes
        C3Record     mRecord;    // +0x00, 16 bytes
    } scratch;

    CEastlString* picked = PathPick(&scratch.mPicked, &fullPath, &fileName);
    if (picked != &fullPath)
        fullPath.AssignFrom(picked);

    FreeStringBuffer(scratch.mPicked.mpBegin, scratch.mPicked.mpCap);

    CDatabasePackedFile* file = 0;
    void* fileMem = EA_ZoneObjectNewSim(0x388, "Simulator", 0, 0, 0, 0);
    if (fileMem != 0) {
        ((CDatabasePackedFile*)fileMem)->Construct(fullPath.mpBegin, 0, 0);
        file = (CDatabasePackedFile*)fileMem;
        if (file != 0)
            file->mSink.AddRef();
    }

    CObjectDatabase* db = 0;
    void* dbMem = EA_ZoneObjectNewSim(0x24, "Simulator", 0, 0, 0, 0);
    if (dbMem != 0) {
        ((CObjectDatabase*)dbMem)->Construct(file);
        db = (CObjectDatabase*)dbMem;
        if (db != 0)
            db->mBase.B00();
    }

    db->mStream.S04();
    db->mStream.SetPath(fullPath.mpBegin);

    if (db->mBase.Init(1, 0)) {
        CVarListSerializer serializer;
        scratch.mRecord.Ctor(db, (void*)0x1897c18, (void*)0x1897c18, (void*)0x1897c18);
        serializer.Construct(owner, (const void*)0x15a38b8, 0x1a80d26);
        serializer.Read(scratch.mRecord.mpPayload);
        db->mStream.Advance();
        scratch.mRecord.Destroy();
    }

    db->mStream.S08();
    db->mBase.B04();

    if (file != 0)
        file->mSink.Release();

    FreeStringBuffer(fullPath.mpBegin, fullPath.mpCap);
    FreeStringBuffer(savePath.mpBegin, savePath.mpCap);
    FreeStringBuffer(fileName.mpBegin, fileName.mpCap);
}