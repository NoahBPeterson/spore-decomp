// Slice s00d3b920 - SporeApp 0x00d3b920..0x00d3c6a0
// SP::cCreatureModeStrategy (constructor / destructor / mode entry helpers) plus the
// eastl container helpers the strategy uses.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// ---- object types ------------------------------------------------------------

// eastl::vector payload that every cSPVector3 element carries (0x14 bytes).
struct VectorStore {
    void* mpBegin;                                 // 0x00
    void* mpEnd;                                   // 0x04
    void* mpCapacity;                              // 0x08
    void* mpAllocator;                             // 0x0c
    u32   mPad10;                                  // 0x10
    void  CopyFrom(const VectorStore& o);          // 0x00473460
};

// One 0x18-byte element of the strategy's vector-of-vectors.
struct cSPVector3 {
    float       mX;                                // 0x00
    VectorStore mStore;                            // 0x04
};

// The (begin, end) element pair the copy helpers walk; the original keeps both
// pointers in the incoming argument slots, so they are passed as one 8-byte value.
struct cSPVectorRange {
    cSPVector3* mpFirst;                           // 0x00
    cSPVector3* mpLast;                            // 0x04
};

// Node of the eastl::rbtree used for the strategy's sorted key map.
struct cRBNode {
    cRBNode* mpLeft;                               // 0x00
    cRBNode* mpRight;                              // 0x04
    cRBNode* mpParent;                             // 0x08
    u8       mbColor;                              // 0x0c
    u8       mPad0d[3];
    u32      mKeyFirst;                            // 0x10
    u32      mKeySecond;                           // 0x14
};

struct cKeyMap {                                   // the map FUN_00d3bcc0 searches
    u8       mPad000[0x08];
    cRBNode* mpHead;                               // 0x08  sentinel node
    cRBNode* mpRoot;                               // 0x0c
    u32**    LowerBound(u32** result, u32* key);   // 0x00d3bcc0
};

// ---- cCreatureModeStrategy ---------------------------------------------------
struct cCreatureModeStrategy {                     // SP::cCreatureModeStrategy
    void* mpVtblMode;                              // 0x000  SP::cIModeStrategy vtable
    void* mpVtblHandler;                           // 0x004  IHandler vtable
    u8    mSubsystem[0x1c];                        // 0x008  SP::cGonzagoSubsystem (own vtable at +0)
    void* mpField024;                              // 0x024
    u8    mEnterEditorSafetyTimer[0x20];           // 0x028  SP::cGonzagoTimer
    u8    mbField048;                              // 0x048
    u8    mbField049;                              // 0x049
    u8    mPad04a[2];
    void* mpEvoPointArray;                         // 0x04c  freed with operator_delete_array
    void* mpTexturePreload;                        // 0x050  AutoRefCount<TexturePreload>
    void* mpCreatureMissionManager;                // 0x054  AutoRefCount<cSPCreatureMissionManager>
    u8    mPad058[8];
    void* mpCreatureVerbPropList;                  // 0x060  AutoRefCount<cPropertyList>
    void* mpCreaturePropList;                      // 0x064  AutoRefCount<cPropertyList>
    void* mpEditorSession;                         // 0x068  released in FUN_00d3c610
    u8    mbField06c;                              // 0x06c
    u8    mPad06d[3];
    u32   mMessageRegistration;                    // 0x070  handler id (0 = not registered)
    void* mpMsgIdArray;                            // 0x074
    void* mpMsgHandler;                            // 0x078
    void* mpMsgServer;                             // 0x07c
    u32   mMsgIdCount;                             // 0x080
    u8    mPad084[4];
    u8    mFrameStopwatch[0x18];                   // 0x088  EA::Stopwatch
    void* mpInputStrategy;                         // 0x0a0  AutoRefCount<cCreatureModeInputStrategy>
    u32   mField0a4;                               // 0x0a4
    u32   mField0a8;                               // 0x0a8
    void* mpEditorResult;                          // 0x0ac  AutoRefCount<cEditorResultData>
    void* mpEditorResultData;                      // 0x0b0
    void* mpField0b4;                              // 0x0b4
    void* mpField0b8;                              // 0x0b8
    void* mpField0bc;                              // 0x0bc
    void* mpCreaturePaths;                         // 0x0c0  eastl vector payload (first word)
    void* mpField0c4;                              // 0x0c4
    u8    mPad0c8[8];
    void* mpField0d0;                              // 0x0d0
    void* mpField0d4;                              // 0x0d4  released in FUN_00d3c610
    void* mpField0d8;                              // 0x0d8
    u8    mbField0dc;                              // 0x0dc
    u8    mbCheckEvolution;                        // 0x0dd
    u8    mbDelayedTransitionFromCLG;              // 0x0de
    u8    mPad0df[0x0e4 - 0x0df];
    u8    mbField0e4;                              // 0x0e4
    u8    mbField0e5;                              // 0x0e5
    u8    mbField0e6;                              // 0x0e6
    u8    mPad0e7[0xf8 - 0xe7];

    void  Deactivate();                            // 0x00d3c380
    void  dtor();                                  // 0x00d3bb10
};

// ---- shared creature-mode globals --------------------------------------------
struct cCreatureModeGlobals {                      // 0x0169e2a8 block
    u32* mpSoundIds;                               // 0x00 (0x0169e2a8)
    u32* mpSoundIdsEnd;                            // 0x04 (0x0169e2ac)
    u8   mPad008[0x18 - 0x08];
    u8   mbField018;                               // 0x18 (0x0169e2c0)
    u8   mPad019[0x20 - 0x19];
    u8   mbNeedsSoundFlush;                        // 0x20 (0x0169e2c8)
    u8   mPad021[0x24 - 0x21];
    u8   mbField024;                               // 0x24 (0x0169e2cc)
    u8   mPad025[0x28 - 0x25];
    void* mpCurrentAudio;                          // 0x28 (0x0169e2d0)
    u16  mPad02c;
    void* mpPreviousAudio;                         // 0x2c (0x0169e2d4)
};

// ---- callees ----------------------------------------------------------------
void* __cdecl   FUN_0067caf0();                    // 0x0067caf0
void* __stdcall FUN_00b3d240(int a);               // 0x00b3d240
void  __cdecl   FUN_00d3bea0();                    // 0x00d3bea0
u32   __cdecl   FUN_00b95240(float f, u32 packed); // 0x00b95240
void* __cdecl   FUN_00b3d350();                    // 0x00b3d350 (SP::PlanetModel)
void  __cdecl   FUN_00e0ad00(int a);               // 0x00e0ad00
void  __cdecl   FUN_00e0be50();                    // 0x00e0be50
void  __cdecl   FUN_00d3b880(u32** result, cRBNode* node, u32* key, u8 inserted);  // 0x00d3b880
void* __cdecl   FUN_00d48ae0();                    // 0x00d48ae0
void* __cdecl   FUN_00b6c280();                    // 0x00b6c280
void  __cdecl   FUN_00d2cea0();                    // 0x00d2cea0
void* __cdecl   EA_Audio_GetSystemAT();            // 0x00a206f0
void* __cdecl   FUN_00b3d300();                    // 0x00b3d300 (SP::NounManager)
void* __cdecl   FUN_00b1fdb0();                    // 0x00b1fdb0 (GetAvatar)
void* __cdecl   FUN_00c04590();                    // 0x00c04590
void* __cdecl   FUN_00d51660();                    // 0x00d51660
void* __cdecl   FUN_00d4d6c0();                    // 0x00d4d6c0
void* __cdecl   FUN_00c6acc0();                    // 0x00c6acc0
void* __cdecl   FUN_00c6ee40();                    // 0x00c6ee40
void* __cdecl   FUN_00bc3130();                    // 0x00bc3130
void  __cdecl   FUN_00d3b520();                    // 0x00d3b520
void  __cdecl   FUN_00594ee0();                    // 0x00594ee0
void  __cdecl   FUN_00e0fc90();                    // 0x00e0fc90
void* __cdecl   FUN_009512c0();                    // 0x009512c0
void* __cdecl   FUN_009512d0();                    // 0x009512d0
void* __cdecl   FUN_01021260();                    // 0x01021260
void* __cdecl   FUN_00c707e0();                    // 0x00c707e0 (cPlanet::GetName)
void* __cdecl   FUN_0093b6c0();                    // 0x0093b6c0 (GetBuffer)
void* __cdecl   FUN_008105b0();                    // 0x008105b0 (FindWindowByID)
// thiscall callees are declared as members of small wrappers so that ecx carries
// the receiver object, exactly as the original calls them.
struct cGonzagoSubsystemBase { void ctor(); void dtor(); };   // 0x00b5b960 / 0x00b5b9a0
struct cGonzagoTimerBase     { void ctor(); void dtor(); };   // 0x00b63890 / 0x00b638b0
struct cStopwatchBase        { void ctor(int a, bool b); };   // 0x0093a560
struct cVectorBase           { void dtor(); };                // 0x005c7f10
void  __cdecl   FUN_00f47380(void* p);             // 0x00f47380 (operator_delete_array)
void  __cdecl   FUN_00571db0(int a, void* b, void* c, void* d, u32 e);  // 0x00571db0
void  __cdecl   FUN_00e0fb50();                    // 0x00e0fb50 (RemoveAllIcons)
void* __cdecl   FUN_009215c0(void* node);          // 0x009215c0 (eastl::RBTreeDecrement)
void  __cdecl   FUN_00594870(void* a, void* b, u32 c);   // 0x00595870
void  __cdecl   FUN_00594e20(void* a);             // 0x00594e20
u32   __cdecl   FUN_00a68fb0(u32 a);               // 0x00a68fb0 (RandomUint32Uniform)
void  __cdecl   FUN_007b1950();                    // 0x007b1950
void  __cdecl   FUN_00c8b0a0(void* p, int a);      // 0x00c8b0a0

static u32 gModeInstance;                          // 0x0169e2b0-like global slot
static cCreatureModeGlobals& gModes = *(cCreatureModeGlobals*)0x0169e2a8;
static cCreatureModeStrategy* gStrategy = 0;       // _spInstance_cCreatureModeStrategy

// ---- vtable-call helpers -----------------------------------------------------
static inline void  VT_04_0(void* p) { ((void (__thiscall*)(void*))((void***)p)[1])(p); }
static inline void  VT_08_0(void* p) { ((void (__thiscall*)(void*))((void***)p)[2])(p); }
static inline void  VT_0C_1(void* p, int a) { ((void (__thiscall*)(void*, int))((void***)p)[3])(p, a); }
static inline void  VT_38_0(void* p) { ((void (__thiscall*)(void*))((void***)p)[0x38 / 4])(p); }
static inline void  VT_38_1(void* p, u32 a) { ((void (__thiscall*)(void*, u32))((void***)p)[0x38 / 4])(p, a); }
static inline void  VT_40_1(void* p, u32 a, u32 b) { ((void (__thiscall*)(void*, u32, u32))((void***)p)[0x40 / 4])(p, a, b); }
static inline void  VT_58_0(void* p) { ((void (__thiscall*)(void*))((void***)p)[0x58 / 4])(p); }
static inline void  VT_C0_1(void* p, u32 a) { ((void (__thiscall*)(void*, u32))((void***)p)[0xc0 / 4])(p, a); }

// Direct thiscall callees used by Deactivate(); declared as members so the original's
// "ecx = receiver, direct call" shape is reproduced with a relocatable call site.
struct cDeactivateNotifyA { void Notify(); };      // 0x0067a120
struct cDeactivateNotifyB { void Notify(); };      // 0x00b33ce0
struct cDeactivateNotifyC { void Notify(); };      // 0x00b33cf0

// =============================================================================
// @ 0x00d3b920
// Constructs the elements of [first,last) into the buffer tracked by `cursor`,
// advancing the cursor past the last element constructed.
cSPVector3** FUN_00d3b920(cSPVector3** cursor, cSPVectorRange range, cSPVector3* out)
{
    *cursor = out;
    while (range.mpFirst != range.mpLast) {
        cSPVector3* dst = *cursor;
        if (dst) {
            dst->mX = range.mpFirst->mX;
            dst->mStore.CopyFrom(range.mpFirst->mStore);
        }
        *cursor = *cursor + 1;
        range.mpFirst = range.mpFirst + 1;
    }
    return cursor;
}

// =============================================================================
// @ 0x00d3b970
// Copies `count` elements from src to dst (dst may be null; the count is in
// elements and is decremented before the destination pointer advances).
void FUN_00d3b970(cSPVector3* dst, u32 count, const cSPVector3* src)
{
    cSPVector3* p = dst;
    while (0 < count) {
        if (p) {
            p->mX = src->mX;
            p->mStore.CopyFrom(src->mStore);
        }
        --count;
        ++p;
    }
}

// =============================================================================
// The strategy's vtables.  Addressing them through symbols (never through their
// numeric addresses) keeps the generated references relocatable, like the
// original's.
extern "C" char g_vtblIModePre[];                  // initial SP::cIModeStrategy vtable
extern "C" char g_vtblHandlerPre[];                // initial IHandler vtable
extern "C" char g_vtblCreatureMode[];              // SP::cCreatureModeStrategy vtable
extern "C" char g_vtblCreatureModeHandler[];       // SP::cCreatureModeStrategy handler vtable
extern "C" char g_vtblCreatureModeRefCount[];      // cRefCount base vtable
extern "C" char g_vtblCreatureModeGonzago[];       // SP::cIGonzagoSubsystem vtable

// @ 0x00d3b9b0
// SP::cCreatureModeStrategy construction: installs the three vtable bases,
// constructs the embedded subsystem/timer/stopwatch and clears every member.
cCreatureModeStrategy* FUN_00d3b9b0(cCreatureModeStrategy* self)
{
    self->mpVtblMode = (void*)g_vtblIModePre;
    self->mpVtblHandler = (void*)g_vtblHandlerPre;
    ((cGonzagoSubsystemBase*)self->mSubsystem)->ctor();
    self->mpVtblMode = (void*)g_vtblCreatureMode;
    self->mpVtblHandler = (void*)g_vtblCreatureModeHandler;
    *(void**)&self->mSubsystem[0] = (void*)g_vtblCreatureModeGonzago;
    *(void**)&self->mSubsystem[4] = (void*)g_vtblCreatureModeRefCount;
    self->mpField024 = 0;
    ((cGonzagoTimerBase*)self->mEnterEditorSafetyTimer)->ctor();
    self->mbField048 = 0;
    self->mbField049 = 0;
    self->mpEvoPointArray = 0;
    self->mpTexturePreload = 0;
    self->mpCreatureMissionManager = 0;
    self->mpCreatureVerbPropList = 0;
    self->mpCreaturePropList = 0;
    self->mpEditorSession = 0;
    self->mbField06c = 0;
    self->mMessageRegistration = 0;
    self->mpMsgIdArray = 0;
    self->mpMsgHandler = 0;
    self->mpMsgServer = 0;
    self->mMsgIdCount = 0;
    ((cStopwatchBase*)self->mFrameStopwatch)->ctor(0, false);
    self->mpInputStrategy = 0;
    self->mpEditorResult = 0;
    self->mField0a4 = 0xffffffff;
    self->mField0a8 = 0xffffffff;
    self->mpEditorResultData = 0;
    self->mpField0b4 = 0;
    self->mpField0b8 = 0;
    self->mpField0bc = 0;
    self->mpCreaturePaths = 0;
    self->mpField0c4 = 0;
    self->mpField0d0 = 0;
    self->mpField0d4 = 0;
    self->mpField0d8 = 0;
    self->mbField0dc = 0;
    self->mbCheckEvolution = 1;
    self->mbDelayedTransitionFromCLG = 0;
    *(u32*)&self->mPad0df[1] = 1;                  // 0x0e0
    self->mbField0e4 = 0;
    self->mbField0e5 = 0;
    self->mbField0e6 = 0;
    gStrategy = self;
    return self;
}

// =============================================================================
// @ 0x00d3bb10
// SP::cCreatureModeStrategy::~cCreatureModeStrategy - reinstalls the base vtables,
// releases every owned object and tears the embedded bases down.
void cCreatureModeStrategy::dtor()
{
    // NOTE: the member offsets are the ones the constructor writes; the releases are
    // the vtable slot-4/8 releases and the typed helpers seen in the original.
    mpVtblMode = (void*)g_vtblCreatureMode;
    mpVtblHandler = (void*)g_vtblCreatureModeHandler;
    *(void**)&mSubsystem[4] = (void*)g_vtblCreatureModeRefCount;
    *(void**)&mSubsystem[0] = (void*)g_vtblCreatureModeGonzago;
    if (mpField024)
        VT_04_0(mpField024);
    if (mpTexturePreload)
        VT_04_0(mpTexturePreload);
    if (mpCreatureMissionManager)
        VT_08_0(mpCreatureMissionManager);
    ((cVectorBase*)&mpCreaturePaths)->dtor();
    if (mpCreatureVerbPropList)
        VT_04_0(mpCreatureVerbPropList);
    if (mpCreaturePropList)
        VT_04_0(mpCreaturePropList);
    if (mMessageRegistration != 0) {
        u32 id = mMessageRegistration;
        void* server = mpMsgServer;
        void* handler = mpMsgHandler;
        void* ids = mpMsgIdArray;
        u32 count = mMsgIdCount;
        mMessageRegistration = 0;
        FUN_00571db0(id, server, handler, ids, count);
    }
    if (mpMsgIdArray)
        VT_04_0(mpMsgIdArray);
    if (mpEditorSession)
        VT_04_0(mpEditorSession);
    if (mpInputStrategy)
        VT_04_0(mpInputStrategy);
    if (mpEditorResult)
        VT_04_0(mpEditorResult);
    FUN_00b95240(0.0f, (u32)mbField0e4 | ((u32)mbField0e5 << 8) | ((u32)mbField0e6 << 16));
    if (mpEvoPointArray)
        FUN_00f47380(mpEvoPointArray);
    if (mpField0d4)
        VT_04_0(mpField0d4);
    ((cGonzagoTimerBase*)mEnterEditorSafetyTimer)->dtor();
    ((cGonzagoSubsystemBase*)mSubsystem)->dtor();
}

// =============================================================================
// @ 0x00d3bcc0
// eastl::rbtree key lookup: finds the first node whose key is >= the probe key and
// reports it (with an "inserted" flag) through the caller's result buffer.
u32** cKeyMap::LowerBound(u32** result, u32* key)
{
    cRBNode* node = (cRBNode*)&mpHead;                  // walk starts at the header
    bool wentLeft = true;
    if (mpRoot) {
        cRBNode* cur = mpRoot;
        do {
            node = cur;
            if ((u32)cur->mKeyFirst < key[1] ||
                ((u32)cur->mKeyFirst <= key[1] && (u32)cur->mKeySecond <= key[0]))
                wentLeft = false;
            else
                wentLeft = true;
            cur = wentLeft ? (cRBNode*)cur->mpRight : (cRBNode*)cur->mpLeft;
        } while (cur);
    }
    cRBNode* lower = node;
    if (wentLeft) {
        if (node == mpHead)
            goto insert;
        lower = (cRBNode*)FUN_009215c0(node);
    }
    if (key[1] < (u32)lower->mKeyFirst ||
        (key[1] <= (u32)lower->mKeyFirst && key[0] <= (u32)lower->mKeySecond)) {
        *result = (u32*)lower;
        *(u8*)(result + 1) = 0;
        return result;
    }
insert:
    FUN_00d3b880(result, node, key, 0);
    *result = (u32*)key;
    *(u8*)(result + 1) = 1;
    return result;
}

// =============================================================================
// @ 0x00d3bdb0
// Flushes (or re-enables) the pending creature-mode sound queue.
void FUN_00d3bdb0(char enable)
{
    u32 i = 0;
    if (gModes.mpPreviousAudio != 0) {
        VT_0C_1(gModes.mpPreviousAudio, enable != 0);
        void* p = gModes.mpPreviousAudio;
        gModes.mpPreviousAudio = 0;
        VT_04_0(p);
    }
    if (enable != 0 && gModes.mpSoundIds != gModes.mpSoundIdsEnd) {
        u32 count = (u32)(gModes.mpSoundIdsEnd - gModes.mpSoundIds);
        do {
            u32 id = gModes.mpSoundIds[i];
            void* sys = EA_Audio_GetSystemAT();
            if (sys) {
                VT_38_1(sys, 0x347536b);
                VT_40_1(sys, 0x3475385, id);
                VT_40_1(sys, 0x34753a0, 1);
                VT_58_0(sys);
            }
            ++i;
        } while (i < count);
        u32* begin = gModes.mpSoundIds;
        u32* end = gModes.mpSoundIdsEnd;
        FUN_00594870(begin, end, 0);
        gModes.mpSoundIdsEnd = end - (end - begin);
        gModes.mbNeedsSoundFlush = 0;
    }
}

// =============================================================================
// @ 0x00d3bea0
// Leaves creature mode: drops the audio object and clears the pending sound list.
void FUN_00d3bea0()
{
    if (gModes.mpCurrentAudio != 0) {
        VT_0C_1(gModes.mpCurrentAudio, 1);
        void* p = gModes.mpCurrentAudio;
        gModes.mpCurrentAudio = 0;
        VT_04_0(p);
    }
    gModes.mbField024 = 1;
    FUN_00d3bdb0(1);
    u32* begin = gModes.mpSoundIds;
    u32* end = gModes.mpSoundIdsEnd;
    gModes.mbField024 = 0;
    FUN_00594870(begin, end, 0);
    gModes.mbField018 = 0;
    gModes.mpSoundIdsEnd = end - (end - begin);
    gModes.mbNeedsSoundFlush = 0;
}

// =============================================================================
// @ 0x00d3bf30
// Removes every pending sound from the planet model's audio list and clears the
// global queue; returns 1.
u32 __fastcall FUN_00d3bf30(int self)
{
    u32 i = 0;
    *(u8*)(self + 0x30) = 0;
    void* planet = FUN_00b3d350();                     // SP::PlanetModel()
    void* audio = *(void**)((char*)planet + 0x24);
    u32 count = (u32)(*(u32**)(self + 0xc) - *(u32**)(self + 8));
    if (count != 0) {
        do {
            VT_C0_1(audio, *(u32*)(*(u32*)(self + 8) + i * 4));
            ++i;
        } while (i < count);
    }
    u32* begin = *(u32**)(self + 8);
    u32* end = *(u32**)(self + 0xc);
    FUN_00594870(begin, end, 0);
    *(u32*)(self + 0xc) = (u32)(end - (end - begin));
    *(u32*)(self + 0x34) = 0xbf800000;                 // -1.0f
    return 1;
}

// =============================================================================
// @ 0x00d3bfa0
// SP::cCreatureModeStrategy::Update - per-frame mode update (not fully
// reconstructed: see the note below).
u64 FUN_00d3bfa0(int self, char a2, int a3, int a4)
{
    // NOTE: the original is a 954-byte routine that mixes the map lookup above with
    // the random-number and effect spawn paths.  Only the entry sequence could be
    // reconstructed faithfully; the remaining logic is left out.
    FUN_00594ee0();
    u32 v = 0;
    if (a2 != 0)
        v = FUN_00a68fb0(1);
    return (u64)v;
}

// =============================================================================
// @ 0x00d3c380
// SP::cCreatureModeStrategy::Deactivate - tears the mode UI down and hands over
// to the shared teardown.
void cCreatureModeStrategy::Deactivate()
{
    void* a = FUN_0067caf0();
    ((cDeactivateNotifyA*)a)->Notify();
    void* b = FUN_00b3d240(0);
    ((cDeactivateNotifyB*)b)->Notify();
    void* c = FUN_00b3d240(0);
    ((cDeactivateNotifyC*)c)->Notify();
    FUN_00d3bea0();
}

// =============================================================================
// @ 0x00d3c3b0
// Clears the global sound queue and removes every minimap icon while the creature
// mode overlay is up.
void FUN_00d3c3b0()
{
    u8* p1 = (u8*)0x01583354;
    u8* p2 = (u8*)0x01583358;
    *(u8*)0x01583344 = 1;
    *(u8*)0x01583345 = 1;
    *(u32*)0x01583348 = 0;
    *(u32*)0x0158334c = 0;
    *(u32*)0x01583350 = 0;
    FUN_00594870(p1, p2, 0);
    *(u32*)0x01583358 = (u32)(p2 - (p2 - p1));
    if (*(void**)0x0169e3e4 != 0) {
        FUN_00e0fb50();                                // cSPUIMinimapWin::RemoveAllIcons()
        FUN_00e0ad00(4);
    }
}

// =============================================================================
// @ 0x00d3c430
// SP::cCreatureModeStrategy::EnterEditor-like setup; not fully reconstructed.
void FUN_00d3c430()
{
    // NOTE: the original builds the minimap window and the name banner.  Only the
    // window lookups could be identified; the reconstruction is incomplete.
    FUN_0093b6c0();
    FUN_008105b0();
    FUN_009512c0();
    FUN_009512d0();
    FUN_00e0fc90();
    FUN_00e0be50();
    FUN_01021260();
    FUN_00c707e0();
}

// =============================================================================
// @ 0x00d3c610
// SP::cCreatureModeStrategy::Cleanup - drops the minimap/editor handles.
void FUN_00d3c610()
{
    FUN_00d3c3b0();
    if (*(void**)0x0169e3e4 != 0) {
        void* p = *(void**)0x0169e3e4;
        *(void**)0x0169e3e4 = 0;
        VT_04_0(p);
    }
    FUN_00d48ae0();
    FUN_00b6c280();
    cCreatureModeStrategy* s = gStrategy;
    if (s->mpEditorSession != 0) {
        FUN_00d2cea0();
        void* e = s->mpEditorSession;
        if (e) {
            s->mpEditorSession = 0;
            VT_04_0(*(void**)((char*)e + 0x38));
        }
    }
    if (s->mpField0d4 != 0) {
        FUN_007b1950();
        void* q = s->mpField0d4;
        if (q) {
            s->mpField0d4 = 0;
            VT_04_0(q);
            return;
        }
    }
}

// =============================================================================
// @ 0x00d3c6a0
// SP::cCreatureModeStrategy::NotifyWantToGoToEditor - starts the transition to the
// creature editor (not fully reconstructed).
void FUN_00d3c6a0()
{
    // NOTE: the original queries the avatar noun, its position and the planet name to
    // build the editor transition request; only the lookup sequence is reproduced.
    FUN_00b3d300();
    FUN_00b1fdb0();
    FUN_00c04590();
    FUN_00d51660();
    FUN_00d4d6c0();
    FUN_00c6acc0();
    FUN_00c6ee40();
    FUN_00bc3130();
}
