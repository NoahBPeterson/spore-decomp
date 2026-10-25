// Slice s004db1b0: SP::cSpeciesCheat and Skinner::PaintSystem destructor/init helpers.
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

// Reserved stack slots that stand in for the dead locals an original /Od inline body still
// allocates (the frame is part of the byte image even when the slots are never stored to).
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

// distinct stub callee classes so each call is a separate masked relocation
struct Sub0 { void f(); };
struct Sub1 { void f(); };
struct Sub2 { void f(); };
struct Sub3 { void f(); };
struct SubDtor { void f(); };

struct IVtbl9 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(int a, int b);
};

extern int g_paintSystemVtblA[];
extern int g_paintSystemVtblB[];

struct PaintSystem {
    void Destroy();
};

// @ 0x004DB3E0  (Skinner::PaintSystem destructor body)
void PaintSystem::Destroy()
{
    *(void**)this = (void*)g_paintSystemVtblA;
    ((Sub0*)this)->f();
    int* p = (int*)((char*)this + 0xd0);
    if (*p != 0)
        ((Sub1*)p)->f();
    ((Sub2*)((char*)this + 0xb0))->f();
    ((Sub3*)((char*)this + 0x84))->f();
    ((Sub3*)((char*)this + 0x64))->f();
    ((Sub3*)((char*)this + 0x44))->f();
    ((Sub3*)((char*)this + 0x24))->f();
    ((Sub3*)((char*)this + 4))->f();
    *(void**)this = (void*)g_paintSystemVtblB;
}

// @ 0x004DB620
struct Connector {
    void* mpObj;    // +0
    int   mnB;      // +4
    int   mnC;      // +8
    int   mnD;      // +0xc
    int   mnE;      // +0x10
    void Reset() { mpObj = 0; mnB = 0; mnC = 0; mnD = 0; mnE = 0; }
    void Init(void* pObj, int b, int c, uint32_t n);
};

void Connector::Init(void* pObj, int b, int c, uint32_t n)
{
    mpObj = pObj;
    mnB = b;
    mnC = c;
    mnD = n;
    mnE = 0;
    if (pObj != 0 && b != 0 && mnC != 0) {
        for (uint32_t i = 0; i < n; i = i + 1) {
            ((IVtbl9*)pObj)->v09(b, *(int*)(c + i * 4));
        }
    }
}

// @ 0x004DB6B0  SP::cSpeciesCheat::Description
struct SpeciesCheat {
    const char* Description(int param);
};

const char* SpeciesCheat::Description(int param)
{
    if (param == 0)
        return "Used to test species queries to the OTDB";
    else
        return "[-<param> <min> <max> [-<param> <min> <max>]...] | [-dump <param>] | [-dumpFull <param>]\n"
           "-cost <min> <max>\n-baseGear <min> <max>\n-height <min> <max>\n-carnivore <min> <max>\n"
           "-herbivore <min> <max>\n-numGraspers <min> <max>\n-totalAttack <min> <max>\n"
           "-attack <min> <max>\n-cuteness <min> <max>\n-totalSocial <min> <max>\n-social <min> <max>\n"
           "-numFeet <min> <max>\n-meanLookingScore <min> <max>\n-biteCapRange <min> <max>\n"
           "-strikeCapRange <min> <max>\n-chargeCapRange <min> <max>\n-spitCapRange <min> <max>\n"
           "-singCapRange <min> <max>\n-danceCapRange <min> <max>\n-charmCapRange <min> <max>\n"
           "-poseCapRange <min> <max>\n-glideCapRange <min> <max>\n-stealthCapRange <min> <max>\n"
           "-sprintCapRange <min> <max>\n-senseCapRange <min> <max>\n-healthCapRange <min> <max>\n";
}

// ---------------------------------------------------------------------------
// addresses used by the three larger neighbours
// ---------------------------------------------------------------------------
extern char        g_013eb394[];      // 0x013eb394 base vtable (PainSystem/IHandler, folded)
extern char        g_013f08ec[];      // 0x013f08ec SP::cSPEditorSpeciesManager vtable
extern char        g_013eb824[];      // 0x013eb824 EA::ArgScript::cCommandBase vtable
extern char        g_013f099c[];      // 0x013f099c SP::cSpeciesCheat vtable
extern char        g_013ec458[];      // 0x013ec458 Simulator content-validation base vtable
extern char        g_013f0958[];      // 0x013f0958 intermediate summarizer vtable
extern char        g_013f0934[];      // 0x013f0934 SP::cSpeciesSummarizer vtable
extern char        g_013f08f4[];      // 0x013f08f4 SP::cPlantSummarizer vtable
extern const char  aSimulator_013f09b4[];   // 0x013f09b4 "Simulator"
extern const char  aSimSpecies_013f097c[];  // 0x013f097c "Simulator/cSpeciesSummarizer"
extern const char  aSimPlant_013f0918[];    // 0x013f0918 "Simulator/cPlantSummarizer"
extern uint32_t    DAT_013f09c0[];          // 0x013f09c0 two message ids
extern uint8_t     DAT_015d9c64;            // 0x015d9c64 one-shot initialisation guard

extern "C" void  __cdecl FUN_004d34f0(void);   // 0x004d34f0 static initialiser
extern "C" void* __cdecl FUN_0067cb40(void);   // 0x0067cb40 SP::ObjectTemplateDB
extern "C" void* __cdecl FUN_0067de20(void);   // 0x0067de20 SP::CheatManager
extern "C" void* __cdecl FUN_00883860(void);   // 0x00883860 EA::Messaging::GetServer
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);   // 0x00f473a0 named allocator

// ---------------------------------------------------------------------------
// 0x004DB1B0 SP::cSpeciesArchetype::~cSpeciesArchetype
// ---------------------------------------------------------------------------
struct WString {
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    uint32_t mAllocator;    // +0x0c (sp string allocator tag)
    void __thiscall FUN_004237d0();        // 0x004237d0 release the character buffer
    ~WString() { ScratchSlots<3>(); FUN_004237d0(); }
};

struct SpVectorAllocator {
    uint32_t mData[2];      // +0x00
};

template <class T>
struct SpVector {
    T* mpBegin;             // +0x00
    T* mpEnd;               // +0x04
    T* mpCapacity;          // +0x08
    SpVectorAllocator mAllocator;          // +0x0c
    void __thiscall FUN_00425990();        // 0x00425990 release the element buffer
    ~SpVector()
    {
        T* p = mpBegin;
        ScratchSlots<3>();
        for (; p < mpEnd; p = p + 1) {
        }
        FUN_00425990();
    }
};

struct IRefObject {
    virtual void v00();
    virtual void v01();
    virtual void v02();
};

struct AutoRefCount {
    IRefObject* mpObject;   // +0x00
    ~AutoRefCount()
    {
        if (mpObject != 0)
            mpObject->v01();
    }
};

struct cSpeciesArchetype {
    WString            mDebugName;             // +0x000
    uint8_t            m010[0x38c];            // +0x010 .. +0x39c
    SpVector<float>    mOriginDistances;       // +0x39c
    SpVector<uint32_t> mRelatedArchetypes;     // +0x3b0
    SpVector<uint32_t> mArchetypeGenerations;  // +0x3c4
    uint8_t            m3d8[4];                // +0x3d8 .. +0x3dc
    SpVector<uint32_t> mSchedulerTemplates;    // +0x3dc
    uint8_t            m3f0[0x4c];             // +0x3f0 .. +0x43c
    AutoRefCount       mPropertyList;          // +0x43c
    ~cSpeciesArchetype();
};

// @ 0x004DB1B0
cSpeciesArchetype::~cSpeciesArchetype()
{
}

// ---------------------------------------------------------------------------
// 0x004DB2C0 SP::cSPEditorSpeciesManager::cSPEditorSpeciesManager
// ---------------------------------------------------------------------------
struct HashContainer {      // eastl::hash_map, 0x20 bytes
    uint8_t mData[0x20];    // +0x00
    void __thiscall FUN_005640f0(void* pFlag);   // 0x005640f0 member initialiser
};

struct ResourceKey {
    uint32_t mType;         // +0x00
    uint32_t mGroup;        // +0x04
    uint32_t mInstance;     // +0x08
    void Reset() { mType = 0; mGroup = 0; mInstance = 0; }
};

struct cSPEditorSpeciesManager {
    void*          mpVtable;                 // +0x000
    HashContainer  mSpecies;                 // +0x004
    HashContainer  mOldSpeciesMapping;       // +0x024
    HashContainer  mPlantSpecies;            // +0x044
    HashContainer  mReplacementSpecies;      // +0x064
    HashContainer  mReplacementCache;        // +0x084
    ResourceKey    mAvatarSpeciesKey;        // +0x0a4
    HashContainer  mArchetypes;              // +0x0b0
    Connector      mMessageRegistration;     // +0x0d0
    void __thiscall FUN_004dd060();          // 0x004dd060 ReloadTuning
    cSPEditorSpeciesManager();
    void Init();
};

// @ 0x004DB2C0
cSPEditorSpeciesManager::cSPEditorSpeciesManager()
{
    // The six 1-byte hash_allocator() arguments are /Od temporaries placed by name
    // hash (highest hash -> lowest address); these names reproduce the retail order.
    uint8_t tag3, tag6, tag2, tag5, tag1, tag4;

    ScratchSlots<6>();
    *(void**)this = (void*)g_013eb394;
    *(void**)this = (void*)g_013f08ec;
    mSpecies.FUN_005640f0(&tag3);
    mOldSpeciesMapping.FUN_005640f0(&tag2);
    mPlantSpecies.FUN_005640f0(&tag6);
    mReplacementSpecies.FUN_005640f0(&tag1);
    mReplacementCache.FUN_005640f0(&tag5);
    mAvatarSpeciesKey.Reset();
    ScratchSlots<2>();
    mArchetypes.FUN_005640f0(&tag4);
    mMessageRegistration.Reset();
}

// ---------------------------------------------------------------------------
// 0x004DB470 SP::cSPEditorSpeciesManager::Init
// ---------------------------------------------------------------------------
struct CmdBaseIface {       // EA::ArgScript::cCommandBase
    void __thiscall FUN_0083c800();        // 0x0083c800 EA::ArgScript::cCommandBase::cCommandBase
};

struct SpeciesCheatObj {    // SP::cSpeciesCheat, 0x10 bytes
    uint8_t m00[0x10];
    SpeciesCheatObj()
    {
        ((CmdBaseIface*)this)->FUN_0083c800();
        *(void**)this = (void*)g_013eb824;
        *(void**)this = (void*)g_013f099c;
    }
};

struct SpeciesSummarizerObj {   // SP::cSpeciesSummarizer, 0x0c bytes
    void* mVtable;          // +0x00
    int   m04;              // +0x04
    void* mpOwner;          // +0x08
    SpeciesSummarizerObj(void* pOwner)
    {
        *(void**)this = (void*)g_013ec458;
        m04 = 0;
        *(void**)this = (void*)g_013f0958;
        *(void**)this = (void*)g_013f0934;
        mpOwner = pOwner;
    }
};

struct PlantSummarizerObj {     // SP::cPlantSummarizer, 0x0c bytes
    void* mVtable;          // +0x00
    int   m04;              // +0x04
    void* mpOwner;          // +0x08
    PlantSummarizerObj(void* pOwner)
    {
        *(void**)this = (void*)g_013ec458;
        m04 = 0;
        *(void**)this = (void*)g_013f0958;
        *(void**)this = (void*)g_013f08f4;
        mpOwner = pOwner;
    }
};

struct ObjectTemplateDBFace {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(void* p);
};

// @ 0x004DB470
void cSPEditorSpeciesManager::Init()
{
    void* mgr;
    void* server;

    ScratchSlots<1>();
    FUN_004d34f0();
    FUN_004dd060();
    server = FUN_00883860();
    mMessageRegistration.Init(server, (int)this, (int)DAT_013f09c0, 2);

    mgr = FUN_0067de20();
    if (mgr != 0) {
        new (aSimulator_013f09b4, 0, 0, 0, 0) SpeciesCheatObj();
    }

    if (DAT_015d9c64 == 0) {
        DAT_015d9c64 = 1;
        if (FUN_0067cb40() != 0) {
            ((ObjectTemplateDBFace*)FUN_0067cb40())->v31(
                new (aSimSpecies_013f097c, 0, 0, 0, 0) SpeciesSummarizerObj(this));
            ((ObjectTemplateDBFace*)FUN_0067cb40())->v31(
                new (aSimPlant_013f0918, 0, 0, 0, 0) PlantSummarizerObj(this));
        }
    }
}
