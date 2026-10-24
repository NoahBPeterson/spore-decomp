// Slice s00d4d5c0 -- Spore Simulator drama-event manager + drama-event serializer
// cluster (cSPDramaManager, cDramaEventInstanceData and the per-event Write overrides).
// Range 0x00d4d5c0..0x00d4e4a0.  Module: SPGonzago/SPDrama.obj
// (the eastl::multimap model and the RBTree::equal_range callee are shared with the
//  sibling slice s00d4a930).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (see manifest.txt)
#include "types.h"

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed int     i32;

#define FORCEINLINE __forceinline

// ---------------------------------------------------------------- callee decls
// Every unnamed retail callee keeps its ghost address inside the identifier so the
// differential harness (tools/difftest/resolve.py) can bind the reference to the
// original address.
extern "C" void* __cdecl FUN_00f473a0(u32 n, const char* a, int b, int c, const char* d, int e); // 0xf473a0 operator_new
extern "C" void  __cdecl FUN_00f47380(void* p);                                   // 0xf47380 operator_delete_array
extern "C" void* __cdecl FUN_00921580(void* node);                                // 0x921580 eastl::RBTreeIncrement
extern "C" void  __cdecl FUN_009216a0(void* node, void* hint, void* anchor, int side); // 0x9216a0 eastl::RBTreeInsert
extern "C" bool  __cdecl FUN_0093aa70(void* istream, const void* data, u32 count, int flags); // 0x93aa70 EA::IO::WriteUint32
extern "C" void  __cdecl FUN_0093a780(void* istream, void* out, int count, int flags);        // 0x93a780 EA::IO::ReadInt32
extern "C" void* __cdecl FUN_00a35070(void* dst, void* end, void* src);           // 0xa35070 vector erase shift
extern "C" void* __cdecl FUN_0067de30();                                          // 0x67de30 SP::PropertyManager
extern "C" void* __cdecl FUN_00b5b800();                                          // 0xb5b800 SP::GetCurrentGameMode
extern "C" void* __cdecl FUN_00920090();                                          // 0x920090 property-event factory owner
extern "C" void* __cdecl FUN_00b3d300();                                          // 0xb3d300 SP::NounManager

// data addresses (arrays so the reference is emitted as an address, not folded)
extern u8   gModeA;                    // 0x01654c01
extern u8   gModeB;                    // 0x01654c02
extern u32  gDramaEventToBitArray[];   // 0x0147aef4 (indexed by drama-event type)
extern u32  gspDramaManagerInstance;   // 0x0169e43c
extern char gVtbl_cSPDramaManager0[];  // 0x0147b5ec
extern char gVtbl_cSPDramaManager8[];  // 0x0147b5c8
extern char gVtbl_ContentValidationSummarizer0[]; // 0x013ec458
extern char gVtbl_ContentValidationSummarizer8[]; // 0x013eb938
extern char RenameAllocator_013ebb38[];// 0x013ebb38 ("...EASTL/allocator.h")
extern char RenameSimulator_013f09b4[];// 0x013f09b4 ("Simulator")
extern u8   gDefaultVariant_015d1164[];// 0x015d1164 default property variant
extern u32  gKeyHash_015836c8;         // 0x015836c8

// per-event name strings handed to cVarListSerializer
extern char s_name_015838e4[];         // 0x015838e4
extern char s_name_01583920[];         // 0x01583920
extern char s_name_0158395c[];         // 0x0158395c
extern char s_name_015839d4[];         // 0x015839d4
extern char s_name_01583a10[];         // 0x01583a10
extern char s_name_01583a4c[];         // 0x01583a4c
extern char s_name_01583a88[];         // 0x01583a88
extern char s_name_01583ac4[];         // 0x01583ac4

// ---------------------------------------------------------------- stream helpers
// The serializer stream exposes: vtbl[0x18] -> istream, vtbl[0x1c] -> tick,
// vtbl[0x20] -> reader, vtbl[0x28] -> GetData(hash, out, flags).
typedef void* (__thiscall *StreamGetFn)(void* self);
typedef bool  (__thiscall *StreamTickFn)(void* self);
typedef bool  (__thiscall *StreamGetDataFn)(void* self, u32 hash, void** out, int flags);

// the vtable pointer is the object's first word
FORCEINLINE void** Vtbl(void* obj) { return *(void***)obj; }

FORCEINLINE void* StreamReader(void* stream) {
    return ((StreamGetFn)Vtbl(stream)[0x20 / 4])(stream);
}
FORCEINLINE void* StreamIStream(void* reader) {
    return ((StreamGetFn)Vtbl(reader)[0x18 / 4])(reader);
}
FORCEINLINE bool StreamTick(void* stream) {
    return ((StreamTickFn)Vtbl(stream)[0x1c / 4])(stream);
}
FORCEINLINE bool StreamGetData(void* stream, u32 hash, void** out, int flags) {
    return ((StreamGetDataFn)Vtbl(stream)[0x28 / 4])(stream, hash, out, flags);
}

// ---------------------------------------------------------------- stream vcall views
// The retail writer stream is reached by genuine C++ virtual calls, which is what
// makes cl emit the canonical `mov eax,[obj]; mov edx,[eax+slot]; call edx` sequence.
struct OReader;
struct OStream {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual OReader* v8();                 // vtbl[0x20] -> reader
};
struct OReader {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5();
    virtual void* v6();                    // vtbl[0x18] -> istream
};

// ---------------------------------------------------------------- eastl rbtree
// rbtree_node_base: left/right/parent/colour; the multimap node appends key/value.
struct RBNode {
    RBNode* mpNodeLeft;    // +0x00
    RBNode* mpNodeRight;   // +0x04
    RBNode* mpNodeParent;  // +0x08
    u32     mColor;        // +0x0c
    u32     mKey;          // +0x10
    void*   mValue;        // +0x14
};

// the multimap object: a 4-byte gap then the anchor node (mpNodeParent = root,
// mpNodeRight = begin), with mnSize overlaid on the anchor's unused key slot.
struct RBTree {
    u32     m_gap0;        // +0x00
    RBNode  mAnchor;       // +0x04
    u32     mCount;        // +0x18 (overlays mAnchor.mValue)

    void  equalRange_00d4b450(RBNode** out, u32* key);             // 0x00d4b450
    void  insertUnique_00d4b4f0(RBNode** out, RBNode* hint, void* value, int isInsert); // 0x00d4b4f0
    void  destroyNodes_00d0c930(RBNode* root);                     // 0x00d0c930
};

// ---------------------------------------------------------------- auto-refcount
typedef void (__thiscall *RefFn)(void* self);
typedef void (__thiscall *SetFn)(void* self, int v);

// Genuine virtual calls so cl emits the canonical vcall sequence.
struct AutoRefObj {
    virtual void _ref_add();      // +0x00
    virtual void _ref_release();  // +0x04
};
struct GameDataObj {              // game-data entry object (predicate at +0x2c)
    virtual void _g0();
    virtual void _g1();
    virtual void _g2(); virtual void _g3(); virtual void _g4();
    virtual void _g5(); virtual void _g6(); virtual void _g7();
    virtual void _g8(); virtual void _g9(); virtual void _g10();
    virtual bool _gpred();        // +0x2c
};

FORCEINLINE void RefAddRef(void* obj) {
    ((AutoRefObj*)obj)->_ref_add();
}
FORCEINLINE void RefRelease(void* obj) {
    ((AutoRefObj*)obj)->_ref_release();
}

// ---------------------------------------------------------------- event object
// cDramaEventInstanceData: retail offsets are 0x10 below the 2008 PDB layout.
struct RefPair { u32 key; void* obj; };   // 8-byte element of the game-data vector
struct RefVec {
    u8* mBegin;            // +0x00
    u8* mEnd;              // +0x04
    u8* mCap;              // +0x08
    void eraseIF_00530c80(u8* first, u8* last);       // 0x530c80 (pair<int,float> erase)
    void eraseGD_00621f50(u8* first, u8* last);       // 0x621f50 (pair<u32,AutoRef> erase)
    void* insertAt_00d4cda0(void* pos, const void* value); // 0x00d4cda0
    void* insert_00d4d9b0(RefPair* pos, const RefPair* value); // 0x00d4d9b0
};

struct cDramaEventInstanceData {
    void** m_vtbl;             // +0x00
    u32    m_pad04[2];         // +0x04
    u8     mbActive;           // +0x0c
    u8     m_pad0d[3];         // +0x0d
    u32    mEventMask;         // +0x10
    u32    mType;              // +0x14
    u32    m_pad18[7];         // +0x18
    u32    mPropListKey[3];    // +0x34 (EA::ResourceMan::Key)
    void*  mpPropList;         // +0x40
    RefVec mData;              // +0x44
    u32    m_pad50[3];         // +0x50
    RefVec mGameDataMap;       // +0x5c

    bool Write(void* stream);                 // 0x00d4db50
    bool WriteData(void* stream);             // 0x00d4da10
    void ClearData();                         // 0x00d4dae0
};

// per-event Write overrides live on subclasses; only the writer body is modelled.
struct cNightPredatorEvent   { bool Write(void* stream); };  // 0x00d4dbe0
struct cUFOAbductionEvent    { bool Write(void* stream); };  // 0x00d4dc70
struct cBabyGameEvent        { bool Write(void* stream); };  // 0x00d4dd00
struct cRainStormEvent       { bool Write(void* stream); };  // 0x00d4dd90
struct cSeaMonsterEvent      { bool Write(void* stream); };  // 0x00d4de20
struct cTribeFoodRaidEvent   { bool Write(void* stream); };  // 0x00d4deb0
struct cMeteorStrikeEvent    { bool Write(void* stream); };  // 0x00d4df40

// ---------------------------------------------------------------- cVarListSerializer
struct cVarListSerializer {
    u8 m_data[0xa14];
    void ctor_00692f90(void* obj, const char* name, u32 sig);  // 0x692f90
    bool serialize_00692900(void* stream);                     // 0x692900
};

// ---------------------------------------------------------------- cGonzagoTimer
struct cGonzagoTimer {
    u8 m_data[0x20];
    void dtor_00b638b0();     // 0xb638b0
};

// ---------------------------------------------------------------- noun manager
struct cGameNounManager {
    void removeNoun_00b225d0(void* noun);   // 0xb225d0
};

// ---------------------------------------------------------------- drama manager
struct cSPDramaManager {
    void** m_vtbl;                // +0x00
    u8     m_pad04[0x0c];         // +0x04
    bool   mbShouldHaveStalker;   // +0x10
    void*  mpBabyTeacher;         // +0x14 (AutoRefCount)
    cGonzagoTimer mGameTimer;     // +0x18
    void*  mpMate;                // +0x38 (AutoRefCount)
    float  mCheckForMateTimer;    // +0x3c
    u32    mCurrentMateCallIndex; // +0x40
    i32    mNestUpgradeLevel;     // +0x44
    float  mNestItemProgress;     // +0x48
    void*  mpStalkerNPC;          // +0x4c (AutoRefCount)
    RBTree mDramaEvents;          // +0x50
    u32    mActiveDramaEventMask; // +0x6c

    void ConsumeDramaEvents(u32 eventType);    // 0x00d4d5c0
    void ConsumeAllDramaEvents();              // 0x00d4d6c0
    void TriggerDramaEvent(u32 eventType, u32 unused); // 0x00d4d790
    void TriggerEvent(cDramaEventInstanceData* ev, int flags); // 0x00d4d530
    ~cSPDramaManager();                        // 0x00d4dfd0 (destructor body)
    void Init();                               // 0x00d4e070
    void Shutdown();                           // 0x00d4e350
};

// ---------------------------------------------------------------- property probe
typedef bool (__thiscall *FindPropFn)(void* self, void* a, void* b, void** out);  // vtbl[0x2c]
typedef u8*  (__thiscall *VariantGetFn)(void* self, u32 hash);                    // vtbl[0x28]
typedef void* (__thiscall *MakeEventFn)(void* self, const char* name, u32 sig, u32 a, u32 b); // vtbl[0x20]

// ================================================================ 00d4d5c0
// @ 0x00d4d5c0
void cSPDramaManager::ConsumeDramaEvents(u32 eventType)
{
    RBNode* range[2];
    mDramaEvents.equalRange_00d4b450(range, &eventType);

    RBNode* n = range[0];
    if (range[0] != range[1]) {
        do {
            cDramaEventInstanceData* ev = (cDramaEventInstanceData*)n->mValue;
            if (ev->mbActive) {
                void** vt = (void**)ev->m_vtbl;
                ((RefFn)vt[0x34 / 4])(ev);
                ev->mbActive = 0;

                u32 type = ev->mType;
                RBNode* lo = &mDramaEvents.mAnchor;
                for (RBNode* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
                    if (type < a->mKey) { lo = a; a = a->mpNodeRight; }
                    else a = a->mpNodeLeft;
                }
                RBNode* hi = &mDramaEvents.mAnchor;
                for (RBNode* b = mDramaEvents.mAnchor.mpNodeParent; b != 0; ) {
                    if (b->mKey < type) b = b->mpNodeLeft;
                    else { hi = b; b = b->mpNodeRight; }
                }
                cDramaEventInstanceData* found = 0;
                for (RBNode* p = hi; p != lo; p = (RBNode*)FUN_00921580(p)) {
                    cDramaEventInstanceData* v = (cDramaEventInstanceData*)p->mValue;
                    if (v->mbActive) { found = v; break; }
                }

                u32 bit = gDramaEventToBitArray[type];
                if (found) mActiveDramaEventMask |= bit;
                else       mActiveDramaEventMask &= ~bit;
            }
            n = (RBNode*)FUN_00921580(n);
        } while (n != range[1]);
    }
}

// ================================================================ 00d4d6c0
// @ 0x00d4d6c0
void cSPDramaManager::ConsumeAllDramaEvents()
{
    RBNode* end = &mDramaEvents.mAnchor;
    RBNode* n = mDramaEvents.mAnchor.mpNodeRight;
    if (n != end) {
        do {
            cDramaEventInstanceData* ev = (cDramaEventInstanceData*)n->mValue;
            if (ev->mbActive) {
                void** vt = (void**)ev->m_vtbl;
                ((RefFn)vt[0x34 / 4])(ev);
                ev->mbActive = 0;

                u32 type = ev->mType;
                RBNode* lo = &mDramaEvents.mAnchor;
                for (RBNode* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
                    if (type < a->mKey) { lo = a; a = a->mpNodeRight; }
                    else a = a->mpNodeLeft;
                }
                RBNode* hi = &mDramaEvents.mAnchor;
                for (RBNode* b = mDramaEvents.mAnchor.mpNodeParent; b != 0; ) {
                    if (b->mKey < type) b = b->mpNodeLeft;
                    else { hi = b; b = b->mpNodeRight; }
                }
                cDramaEventInstanceData* found = 0;
                for (RBNode* p = hi; p != lo; p = (RBNode*)FUN_00921580(p)) {
                    cDramaEventInstanceData* v = (cDramaEventInstanceData*)p->mValue;
                    if (v->mbActive) { found = v; break; }
                }

                u32 bit = gDramaEventToBitArray[type];
                if (found) mActiveDramaEventMask |= bit;
                else       mActiveDramaEventMask &= ~bit;
            }
            n = (RBNode*)FUN_00921580(n);
        } while (n != end);
    }
}

// ================================================================ 00d4d790
// @ 0x00d4d790
void cSPDramaManager::TriggerDramaEvent(u32 eventType, u32 unused)
{
    u32 key = eventType;
    RBNode* range[2];
    mDramaEvents.equalRange_00d4b450(range, &key);
    RBNode* n = range[0];
    RBNode* const hi = range[1];
    while (n != hi) {
        cDramaEventInstanceData* ev = (cDramaEventInstanceData*)n->mValue;
        if (!ev->mbActive) {
            TriggerEvent(ev, 0);
        }
        n = (RBNode*)FUN_00921580(n);
    }
}

// ================================================================ 00d4d7f0
// Deserialiser for the drama-event multimap: clears the tree, re-initialises the
// anchor, then walks the stream reading (key, event) pairs into fresh nodes.
// @ 0x00d4d7f0
void FUN_00d4d7f0(void* stream, RBTree* tree)
{
    tree->destroyNodes_00d0c930(tree->mAnchor.mpNodeParent);
    tree->mAnchor.mpNodeLeft = &tree->mAnchor;
    tree->mAnchor.mpNodeRight = &tree->mAnchor;
    tree->mAnchor.mpNodeParent = 0;
    tree->mAnchor.mColor = 0;
    tree->mAnchor.mKey = 0;

    u32 count = 0;
    FUN_0093a780(StreamIStream(StreamReader(stream)), &count, 1, 0);

    u32 i = 0;
    if (count != 0) {
        do {
            u32 key;
            FUN_0093a780(StreamIStream(StreamReader(stream)), &key, 1, 0);
            StreamTick(stream);

            void* value = 0;
            if (value) { void* old = value; value = 0; RefRelease(old); }
            StreamGetData(stream, 0x558fe09, &value, 0);
            StreamTick(stream);

            // pair{key, value} with an extra addref for the node copy
            u32 pairKey = key;
            void* pairVal = value;
            if (pairVal) RefAddRef(pairVal);

            RBNode* hint = &tree->mAnchor;
            for (RBNode* a = tree->mAnchor.mpNodeParent; a != 0; ) {
                hint = a;
                if (key < a->mKey) a = a->mpNodeRight;
                else               a = a->mpNodeLeft;
            }
            int isInsert = 0;
            if (hint != &tree->mAnchor && !(key < hint->mKey)) isInsert = 1;

            RBNode* node = (RBNode*)FUN_00f473a0(0x18, RenameSimulator_013f09b4, 0, 0,
                                                 RenameAllocator_013ebb38, 0xd1);
            if (node) {
                node->mKey = pairKey;
                node->mValue = pairVal;
                if (pairVal) RefAddRef(pairVal);
            }
            FUN_009216a0(node, hint, &tree->mAnchor, isInsert);
            tree->mAnchor.mKey++;
            RefRelease(pairKey ? pairVal : pairVal);
            if (value) RefRelease(value);
            i++;
        } while (i < count);
    }
    StreamTick(stream);
}

// ================================================================ 00d4d9b0
// eastl::vector<pair<u32,AutoRef> >::insert(pos, value): fast path when appending.
// @ 0x00d4d9b0
void* RefVec::insert_00d4d9b0(RefPair* pos, const RefPair* value)
{
    RefPair* end = (RefPair*)mEnd;
    u32 idx = (u32)(((u8*)pos - mBegin) >> 3);
    if (pos == end && (u8*)end != mCap) {
        mEnd = (u8*)(end + 1);
        if (end) {
            end->key = value->key;
            void* obj = value->obj;
            end->obj = obj;
            if (obj) RefAddRef(obj);
        }
    } else {
        insertAt_00d4cda0(pos, value);
    }
    return mBegin + idx * 8;
}

// ================================================================ 00d4da10
// cDramaEventInstanceData data writer: writes the event signature, drops entries
// whose predicate is false from the game-data vector, then runs the var serializer.
// @ 0x00d4da10
bool cDramaEventInstanceData::WriteData(void* stream)
{
    u32 key;
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    key = 0x558fe09;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);

    u8* begin = mGameDataMap.mBegin;
    u8* end = mGameDataMap.mEnd;
    if (begin != end) {
        u8* next = begin + 8;
        do {
            void* obj = *(void**)(begin + 4);
            if (obj == 0 || ((GameDataObj*)obj)->_gpred()) {
                if (next < mGameDataMap.mEnd) {
                    FUN_00a35070(next, mGameDataMap.mEnd, begin);
                }
                mGameDataMap.mEnd -= 8;
                void* tail = *(void**)(mGameDataMap.mEnd + 4);
                if (tail) RefRelease(tail);
            }
            begin += 8;
            next += 8;
        } while (begin != end);
    }

    local.ctor_00692f90(this, (const char*)0x15836c8, 0x1a80d26);
    return local.serialize_00692900(stream);
}

// ================================================================ 00d4dae0
// Clears the event's associated data: releases the property list, drops the
// (int,float) vector and each game-data noun, then drops the game-data vector.
// @ 0x00d4dae0
void cDramaEventInstanceData::ClearData()
{
    if (mpPropList) {
        void* p = mpPropList;
        mpPropList = 0;
        RefRelease(p);
    }
    mData.eraseIF_00530c80(mData.mBegin, mData.mEnd);

    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    RefVec* map = &mGameDataMap;
    for (u8* p = map->mBegin, *e = map->mEnd; p != e; p += 8) {
        nm->removeNoun_00b225d0(*(void**)(p + 4));
    }
    map->eraseGD_00621f50(map->mBegin, map->mEnd);
}

// ================================================================ event Write overrides
// All eight share one body: emit the event signature, run the base data writer, then
// run the var serialiser under the per-event name. Written out per function so the
// compiler schedules each body exactly as the original does.

// @ 0x00d4db50
bool cDramaEventInstanceData::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x558fe09;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x15838e4, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dbe0
bool cNightPredatorEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599e34;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583920, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dc70
bool cUFOAbductionEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599eb8;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x158395c, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dd00
bool cBabyGameEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599f2c;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x15839d4, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dd90
bool cRainStormEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599f52;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583a10, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4de20
bool cSeaMonsterEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599f7c;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583a4c, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4deb0
bool cTribeFoodRaidEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5ed29d3;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583a88, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4df40
bool cMeteorStrikeEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x609eedc;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583ac4, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// ================================================================ 00d4dfd0
// @ 0x00d4dfd0
cSPDramaManager::~cSPDramaManager()  // modelled as the ctor-named destroying body
{
    *(void**)this = (void*)gVtbl_cSPDramaManager0;
    *(void**)((u8*)this + 8) = (void*)gVtbl_cSPDramaManager8;
    gspDramaManagerInstance = 0;
    RBTree* t = &mDramaEvents;
    t->destroyNodes_00d0c930(t->mAnchor.mpNodeParent);
    if (mpStalkerNPC) RefRelease(mpStalkerNPC);
    if (mpMate) RefRelease(mpMate);
    mGameTimer.dtor_00b638b0();
    if (mpBabyTeacher) RefRelease(mpBabyTeacher);
    *(void**)((u8*)this + 8) = (void*)gVtbl_ContentValidationSummarizer8;
    *(void**)this = (void*)gVtbl_ContentValidationSummarizer0;
}

// ================================================================ 00d4e070
// Property-driven setup: query the current mode's event-tuning property list,
// rebuild the event multimap, then instantiate one event object per property that
// resolves to a valid drama-event type.
typedef void  (__thiscall *PropQueryFn)(void* propMgr, u32 sig, RefVec* out);          // vtbl[0x48]
typedef bool  (__thiscall *PropFindFn)(void* propMgr, void* element, u32 sig, void** out); // vtbl[0x2c]

// @ 0x00d4e070
void cSPDramaManager::Init()
{
    u8* mode = (u8*)FUN_00b5b800();
    u32 sig;
    if (mode == &gModeA)      sig = 0xebcfbc7;
    else if (mode == &gModeB) sig = 0xe7ca1f54;
    else return;

    void* propMgr = FUN_0067de30();
    RefVec propList;
    propList.mBegin = 0;
    propList.mEnd = 0;
    propList.mCap = 0;
    ((PropQueryFn)Vtbl(propMgr)[0x48 / 4])(propMgr, sig, &propList);

    mDramaEvents.destroyNodes_00d0c930(mDramaEvents.mAnchor.mpNodeParent);
    mDramaEvents.mAnchor.mpNodeLeft = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeRight = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeParent = 0;
    mDramaEvents.mAnchor.mColor = 0;
    mDramaEvents.mAnchor.mKey = 0;

    void* factory = FUN_00920090();
    void* handle = 0;
    for (u8** it = (u8**)propList.mBegin; it != (u8**)propList.mEnd; ++it) {
        void* element = *it;
        if (handle) { void* old = handle; handle = 0; RefRelease(old); }
        if (!((PropFindFn)Vtbl(propMgr)[0x2c / 4])(propMgr, element, sig, &handle))
            continue;

        u8* prop = ((VariantGetFn)Vtbl(handle)[0x28 / 4])(handle, 0xb10f785d);
        u16 tag = *(u16*)(prop + 0x12);
        u8* vp;
        if (tag == 0x0a || tag == 0x10)
            vp = (*(u8*)(prop + 0x10) & 0x30) ? *(u8**)prop : prop;
        else
            vp = gDefaultVariant_015d1164;
        u32 type = *(u32*)vp;
        if (type > 8) continue;

        u32 evsig;
        switch (type) {
        case 0: evsig = 0x558fe09; break;
        case 1: evsig = 0x5599e34; break;
        case 2: evsig = 0x5599eb8; break;
        case 3: evsig = 0x5599ef6; break;
        case 4: evsig = 0x5599f2c; break;
        case 5: evsig = 0x5599f52; break;
        case 6: evsig = 0x5599f7c; break;
        case 7: evsig = 0x5ed29d3; break;
        default: evsig = 0x609eedc; break;
        }
        // the (name, sig) constants live in the jump table, kept as raw data addresses
        const char* name = (const char*)(evsig == 0x558fe09 ? 0x5599d0c :
                                         evsig == 0x5599e34 ? 0x5599e3b :
                                         evsig == 0x5599eb8 ? 0x5599ec7 :
                                         evsig == 0x5599ef6 ? 0x5599f00 :
                                         evsig == 0x5599f2c ? 0x5599f34 :
                                         evsig == 0x5599f52 ? 0x5599f5a :
                                         evsig == 0x5599f7c ? 0x5599f83 :
                                         evsig == 0x5ed29d3 ? 0x5ed29d9 : 0x609eedf);

        cDramaEventInstanceData* ev =
            (cDramaEventInstanceData*)((MakeEventFn)Vtbl(factory)[0x20 / 4])(factory, name, evsig, 0, 0);
        if (!ev) continue;

        ev->mType = type;
        void* oldProp = ev->mpPropList;
        if (handle != oldProp) {
            if (handle) RefAddRef(handle);
            ev->mpPropList = handle;
            if (oldProp) RefRelease(oldProp);
        }
        ev->mPropListKey[0] = *(u32*)((u8*)handle + 8);
        ev->mPropListKey[1] = *(u32*)((u8*)handle + 12);
        ev->mPropListKey[2] = *(u32*)((u8*)handle + 16);

        ((SetFn)Vtbl(ev)[0x28 / 4])(ev, 0);   // vtbl[0x28](0)
        RefAddRef(ev);
        u32 pairKey = type;
        void* pairVal = ev;
        RefAddRef(ev);

        RBNode* hint = &mDramaEvents.mAnchor;
        for (RBNode* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
            hint = a;
            if (type < a->mKey) a = a->mpNodeRight;
            else                a = a->mpNodeLeft;
        }
        RBNode* inserted = 0;
        mDramaEvents.insertUnique_00d4b4f0(&inserted, hint, &pairKey, 0);
        RefRelease(ev);
        RefRelease(ev);
    }

    if (handle) RefRelease(handle);
    if (propList.mBegin && *(u32*)(propList.mBegin - 4) != 0)
        FUN_00f47380(propList.mBegin);
}

// ================================================================ 00d4e350
// @ 0x00d4e350
void cSPDramaManager::Shutdown()
{
    ConsumeAllDramaEvents();

    RBNode* end = &mDramaEvents.mAnchor;
    RBNode* n = mDramaEvents.mAnchor.mpNodeRight;
    if (n != end) {
        do {
            cDramaEventInstanceData* ev = (cDramaEventInstanceData*)n->mValue;
            if (ev->mbActive) {
                ((RefFn)((void**)ev->m_vtbl)[0x34 / 4])(ev);
                ev->mbActive = 0;

                u32 type = ev->mType;
                RBNode* lo = &mDramaEvents.mAnchor;
                for (RBNode* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
                    if (type < a->mKey) { lo = a; a = a->mpNodeRight; }
                    else a = a->mpNodeLeft;
                }
                RBNode* hi = &mDramaEvents.mAnchor;
                for (RBNode* b = mDramaEvents.mAnchor.mpNodeParent; b != 0; ) {
                    if (b->mKey < type) b = b->mpNodeLeft;
                    else { hi = b; b = b->mpNodeRight; }
                }
                cDramaEventInstanceData* found = 0;
                for (RBNode* p = hi; p != lo; p = (RBNode*)FUN_00921580(p)) {
                    cDramaEventInstanceData* v = (cDramaEventInstanceData*)p->mValue;
                    if (v->mbActive) { found = v; break; }
                }

                u32 bit = gDramaEventToBitArray[type];
                if (found) mActiveDramaEventMask |= bit;
                else       mActiveDramaEventMask &= ~bit;
            }
            ((RefFn)((void**)ev->m_vtbl)[0x2c / 4])(ev);
            n = (RBNode*)FUN_00921580(n);
        } while (n != end);
    }

    mDramaEvents.destroyNodes_00d0c930(mDramaEvents.mAnchor.mpNodeParent);
    mDramaEvents.mAnchor.mpNodeLeft = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeRight = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeParent = 0;
    mDramaEvents.mAnchor.mColor = 0;
    mDramaEvents.mAnchor.mKey = 0;

    if (mpMate) { void* p = mpMate; mpMate = 0; RefRelease(p); }
    mCheckForMateTimer = 0.0f;
    mCurrentMateCallIndex = 0;
    mNestUpgradeLevel = 0;
    mNestItemProgress = 0.0f;
    if (mpStalkerNPC) { void* p = mpStalkerNPC; mpStalkerNPC = 0; RefRelease(p); }
    if (mpBabyTeacher) { void* p = mpBabyTeacher; mpBabyTeacher = 0; RefRelease(p); }
}