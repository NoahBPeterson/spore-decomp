// Slice s011e2b30: RenderWare arena unfix/refix pipeline (rw::core::arena).
//   /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//
// Layout as read off the retail code:
//   * ArenaIterator carries a 0x6c-byte RefixContextImpl at +0x0c; the arena pointer is at +0x78,
//     the write offset at +0x7c, the original offset at +0x9c, the dict cursors at +0xa0/+0xa8, the
//     atom table at +0xb0, the four resource descriptors at +0xc0 and the atom singleton at +0xe0;
//   * UnfixContextImpl is the stack context the unfix pass fills in: arena +0x00, types +0x04,
//     external arenas +0x08, subreferences +0x0c, atom table +0x10, atom callback +0x14,
//     iterator +0x1c, base +0x20, size +0x24, extra size +0x28, alignment +0x2c.
#include <string.h>

namespace rw {
namespace core {
namespace arena {

struct Arena;
struct ArenaIterator;
struct UnfixContextImpl;
struct RefixContextImpl;
struct AtomSingleton;
struct UnfixRefixAtoms;
struct DynamicArenaSubreferencesData;
struct DynamicAtomTable;
struct ArenaSectionTypes;
struct ArenaSectionExternalArenas;
struct ArenaSectionSubreferences;
struct ArenaSectionAtoms;
struct ArenaSectionManifest;
struct ArenaDictEntry;
struct ArenaTypeRecord;
struct ArenaSectionHeader;
struct ArenaSectionList;
struct AtomTableRoot;

// {base, alignment} pair, 8 bytes: the ctors fill four of them with {0, 1}.
struct SizeAndAlignment
{
    unsigned int mnBase;                // +0x00  size, offset or base value
    unsigned int mnAlignment;           // +0x04

    SizeAndAlignment() : mnBase(0), mnAlignment(1) {}
    SizeAndAlignment(unsigned int nBase, unsigned int nAlign)
        : mnBase(nBase), mnAlignment(nAlign) {}
};

// One arena dictionary entry (0x18 bytes): type id 0 marks a free entry.
struct ArenaDictEntry
{
    void* mpBase;                       // +0x00
    void* mpReloc;                      // +0x04  offset the resource was written at
    unsigned int mnSize;                // +0x08
    unsigned int mnAlign;               // +0x0c
    unsigned int mnTypeIndex;           // +0x10
    unsigned int mnTypeId;              // +0x14
};

// Type record of the manifest: type id, refix callback (+0x08) and fixup callback (+0x0c).
struct ArenaTypeRecord
{
    unsigned int mnTypeId;              // +0x00
    unsigned int mnValue;               // +0x04
    unsigned int (*mpRefixCB)(void* pBase, void* pOffset, ArenaIterator* pIterator);  // +0x08
    unsigned int (*mpFixupCB)(void* pBase, ArenaIterator* pIterator);                 // +0x0c
};

// One unfixed subreference record, 8 bytes (index 0x800000 | n).
struct SubreferenceRecord
{
    unsigned int mnObjectId;            // +0x00
    unsigned int mnOffset;              // +0x04
};

struct AtomTableEntry
{
    unsigned int mnKey;                 // +0x00
    unsigned int mnValue;               // +0x04
};

// Root of the global atom table (0x016f2984), followed by the 0x400-entry table itself.
struct AtomTableRoot
{
    unsigned int mnFirst;               // +0x00
    unsigned int mnSecond;              // +0x04
    unsigned int mnThird;               // +0x08
    AtomTableRoot* Build(AtomTableEntry* pEntries, unsigned int nCount);   // 0x011e29c0
};

// The allocator interface the refix pass reaches through the atom singleton (vtable slot 1).
struct AtomSingleton
{
    virtual void Release();                                         // slot 0
    virtual void Allocate(void* pOut, const SizeAndAlignment* pRequests,
                          unsigned int nFlags);                     // slot 1
};

// Subreference bookkeeping of one iterator (at ArenaIterator + 0xe4).
struct DynamicArenaSubreferencesData
{
    void Init(AtomSingleton* pSingleton);                           // 0x011eb410
    unsigned int AddNewSubreference();                              // 0x011eb490
    char mData[0x40];                                               // +0x00
};

// Atom table of one iterator (at ArenaIterator + 0xb0).
struct DynamicAtomTable
{
    void Init(AtomSingleton* pSingleton);                           // 0x011eaaf0
    unsigned int mn00;                                              // +0x00
    unsigned int mnNumTables;                                       // +0x04
    unsigned int mn08;                                              // +0x08
};

struct ArenaSectionTypes
{
    char mPad_00[0x08];                 // +0x00
    ArenaTypeRecord** mpTypes;          // +0x08
};

// External-arena dictionary: the section holds a resource-arena block whose dict is at +0x08.
struct DynamicArenaDict
{
    char mPad_00[0x08];                 // +0x00
    ArenaDictEntry* mpDict;             // +0x08
};

struct ArenaSectionExternalArenas
{
    char mPad_00[0x08];                         // +0x00
    DynamicArenaDict* mpResourceArenas;         // +0x08
};

struct ArenaSectionSubreferences
{
    char mPad_00[0x14];                 // +0x00
    SubreferenceRecord* mpRecords;      // +0x14

    void UnfixData(ArenaIterator* pIterator);                        // 0x011e4720
    void RefixData(ArenaIterator* pIterator);                        // 0x011e4820
};

struct ArenaSectionAtoms
{
    void SetAtomTableAndUnfixIt(unsigned int nIndex, Arena* pArena); // 0x011e4db0
};

struct ArenaSectionManifest
{
    virtual void Destroy();                                          // slot 0
    virtual void Unfix(UnfixContextImpl* pContext);                  // slot 1

    ArenaSectionTypes* Types();                                      // 0x011e4600
    ArenaSectionExternalArenas* ExternalArenas();                    // 0x011e4610
    ArenaSectionSubreferences* Subreferences();                      // 0x011e4620
    ArenaSectionAtoms* Atoms();                                      // 0x011e4630
};

// Reference-fixup context, embedded in the iterator at +0x0c (0x6c bytes).
struct RefixContextImpl
{
    SizeAndAlignment m_descriptors[4];  // +0x00  requested resource descriptors
    void (*mpWriteCB)(const void* pData, unsigned int nSize, unsigned int nDelta);            // +0x20
    void (*mpWriteCBWithData)(const void* pData, unsigned int nSize, unsigned int nDelta,
                              void* pContext);                                                // +0x24
    void* mpWriteCBData;                // +0x28
    void* mp2c;                         // +0x2c
    void* mpBaseResources[4];           // +0x30
    SizeAndAlignment m_sizes[4];        // +0x40  sizes written per resource descriptor
    void* mpAtomTable;                  // +0x60
    UnfixRefixAtoms* mpAtomCallback;    // +0x64
    void* mpBaseObjectPtr;              // +0x68

    RefixContextImpl();
    ArenaIterator* Iterator();
    void Init(SizeAndAlignment* pDescriptors);                       // 0x011e2d50
    void Serialize(ArenaDictEntry* pEntry);                          // 0x011e2e40
};

// The unfix context the unfix pass hands to the section serializers.
struct UnfixContextImpl
{
    Arena* mpArena;                     // +0x00
    ArenaSectionTypes* mpTypes;         // +0x04
    ArenaSectionExternalArenas* mpExternalArenas;       // +0x08
    ArenaSectionSubreferences* mpSubrefs;               // +0x0c
    DynamicAtomTable* mpAtomTable;      // +0x10
    UnfixRefixAtoms* mpAtomCallback;    // +0x14
    unsigned int mnFlags;               // +0x18
    ArenaIterator* mpIterator;          // +0x1c
    unsigned int mnBase;                // +0x20
    unsigned int mnSize;                // +0x24
    unsigned int mnExtraSize;           // +0x28
    unsigned int mnAlignment;           // +0x2c

    unsigned int AddSubref(void* pBase, unsigned int nObjectId, unsigned int nOffset);   // 0x011e2c60
    void Serialize(ArenaDictEntry* pEntry);                          // 0x011e21e0
};

struct Arena
{
    char mPad_00[0x20];                 // +0x00
    unsigned int mnUsed;                // +0x20
    unsigned int mnNumUsed;             // +0x24
    char mPad_28[0x08];                 // +0x28
    ArenaDictEntry* mpDict;             // +0x30
    ArenaSectionManifest* mpSections;   // +0x34
    char mPad_38[0x04];                 // +0x38
    UnfixContextImpl* mpUnfixContext;   // +0x3c

    unsigned int AddObject(unsigned int nType, unsigned int nSize, unsigned int nAlign);  // 0x011e3300
    unsigned int UnfixStart(ArenaIterator* pIterator, unsigned int nOffset);              // 0x011e3350

    static unsigned int UnfixNext(ArenaIterator* pIterator);        // 0x011e34d0
    static unsigned int RefixStart(ArenaIterator* pIterator);       // 0x011e3780
    static unsigned int RefixNext(ArenaIterator* pIterator);        // 0x011e3940
    static bool FixupNext(ArenaIterator* pIterator);                // 0x011e39e0
    static void GetResourceDescriptor(SizeAndAlignment* pOut, unsigned int nCount,
                                      unsigned int nFlags, void* pUnused,
                                      ArenaSectionList* pManifest,
                                      SizeAndAlignment* pExtra);    // 0x011e3190
    static void WriteDictionary(Arena* pArena, ArenaIterator* pIterator);   // 0x011e2760
};

// The unfix/refix cursor handed around by the arena.
struct ArenaIterator
{
    unsigned int* mpResult;             // +0x000  *mpResult is the fixup success flag
    void* mp004;                        // +0x004
    void* mp008;                        // +0x008
    RefixContextImpl mRefix;            // +0x00c
    Arena* mpArena;                     // +0x078
    unsigned int mnOffset;              // +0x07c
    Arena** mpArenaPtr;                 // +0x080
    unsigned int* mpOrigOffsetPtr;      // +0x084
    ArenaDictEntry** mpDictStartPtr;    // +0x088
    void** mpA4Ptr;                     // +0x08c
    unsigned int* mpDictEntryPtr;       // +0x090
    void (**mpWriteCBPtr)(const void*, unsigned int, unsigned int);   // +0x094
    ArenaIterator* mpSelf;              // +0x098
    unsigned int mnOrigOffset;          // +0x09c
    ArenaDictEntry* mpDictStart;        // +0x0a0
    void* mpA4;                         // +0x0a4
    unsigned int mnDictEntry;           // +0x0a8
    bool mbArenaLocalAtomTableAdded;    // +0x0ac
    char mPad_0ad[0x03];                // +0x0ad
    DynamicAtomTable mAtomTable;        // +0x0b0
    UnfixRefixAtoms* mpUnfixRefixAtoms; // +0x0bc
    SizeAndAlignment mResourceDescriptor[4];   // +0x0c0
    AtomSingleton* mpAtomSingleton;     // +0x0e0
    DynamicArenaSubreferencesData mSubreferences;    // +0x0e4
    unsigned int mn124;                 // +0x124
    unsigned int mn128;                 // +0x128
    unsigned int mn12c;                 // +0x12c
    unsigned int mn130;                 // +0x130

    ArenaIterator();
    void UpdateSubreferencesData();                                  // 0x011e26f0
    unsigned int AddAlignOffset(unsigned int nAlign);                // 0x011e24b0
    unsigned int AddSizeOffset(unsigned int nSize);                  // 0x011e2470
    void Accumulate(const SizeAndAlignment* pSize);                  // 0x011e20a0
    void AccumulateRange(const SizeAndAlignment* pSize);             // 0x011e20d0

    // Inline size accumulator: bumps descriptor 0 by nSize and keeps its alignment valid.
    void AccumulateSize(unsigned int nSize)
    {
        if (mResourceDescriptor[0].mnAlignment < 2)
            mResourceDescriptor[0].mnAlignment = 1;
        mResourceDescriptor[0].mnBase += nSize;
    }
};

// Section header of the manifest's external-arena list.
struct ArenaSectionHeader
{
    unsigned int mnTypeId;              // +0x00
    unsigned int mnValue;               // +0x04
};

struct ArenaSectionList
{
    unsigned int mnCount;               // +0x04
    ArenaSectionHeader** mpSections;    // +0x08
};

// Arena header the refix pass writes in front of the fixed-up blocks (0x98 bytes); it is a copy of
// the arena itself with the write-time values patched in.
struct ArenaHeader
{
    char mPad_00[0x20];                 // +0x00
    unsigned int mnUsed;                // +0x20
    unsigned int mnNumUsed;             // +0x24
    unsigned int mnAlignment;           // +0x28
    unsigned int mnZero2c;              // +0x2c
    ArenaDictEntry* mpDict;             // +0x30
    unsigned int mnSectionsSize;        // +0x34
    unsigned int mnOffset;              // +0x38
    unsigned int mnZero3c;              // +0x3c
    unsigned int mnZero40;              // +0x40
    SizeAndAlignment mDescriptors[4];   // +0x44
    char mPad_64[0x20];                 // +0x64
    unsigned int mnZero84;              // +0x84
    unsigned int mnZero88;              // +0x88
    unsigned int mnZero8c;              // +0x8c
    unsigned int mnZero90;              // +0x90
    unsigned int mnZero94;              // +0x94
};

// Accumulator used by Arena::GetResourceDescriptor; it starts with its own descriptor array.
struct DescriptorList
{
    SizeAndAlignment m_descriptors[4];  // +0x00
    SizeAndAlignment mSectionA;         // +0x20
    char mPad_28[0x1c];                 // +0x28
    SizeAndAlignment mSectionB;         // +0x44
    char mPad_4c[0x14];                 // +0x4c
    SizeAndAlignment mSectionC;         // +0x60
    char mPad_68[0x18];                 // +0x68
    SizeAndAlignment mSectionD;         // +0x80

    DescriptorList();
    void Add(const SizeAndAlignment* pDescriptor);                   // 0x011e23b0
};

// State block Arena::AddObject hands to AddResourceToArena.
struct ArenaDictState
{
    ArenaDictEntry* mpFreeEntry;        // +0x00
    unsigned int* mpNumUsed;            // +0x04
    ArenaDictEntry* mpUsedEntry;        // +0x08
    unsigned int mnResult;              // +0x0c
};

// Writer state used when the local atom table is serialized into the arena (0x006c1320).
struct AtomTableStream
{
    SizeAndAlignment mSize;             // +0x00
    void Init(SizeAndAlignment* pSize);                              // 0x006c1320
};

struct Adder {};

}   // namespace arena
}   // namespace core
}   // namespace rw

using namespace rw::core::arena;

// ------------------------------------------------------------------ helpers defined elsewhere
AtomSingleton* rw_atom_singleton_get();                             // 0x011e58c0
unsigned int rw_sections_size_from(void* pSections);                // 0x011e5090
unsigned int rw_section_manifest_walk(ArenaSectionManifest* pManifest, unsigned int nSize,
                                      ArenaIterator* pIterator);    // 0x011e5170
void rw_section_manifest_default_alloc(const void* pData, unsigned int nSize,
                                       unsigned int nDelta);        // 0x012057f0
void* rw_section_init_descriptor(void* pOut, unsigned int nValue);       // 0x011e49d0
void* rw_section_init_table12(void* pOut, unsigned int nValue);          // 0x011e4ad0
void* rw_section_init_table1c(void* pOut);                               // 0x011e4be0
void* rw_section_init_table0c(void* pOut);                               // 0x011e4c30

template<class Adder>
unsigned int AddResourceToArena(unsigned int nType, unsigned int nAlign, unsigned int nSize,
                                ArenaDictState* pState);            // 0x011e2a00

unsigned int ArenaAccumulateNextResource(unsigned int nIndex, ArenaDictEntry* pDictBegin,
                                         ArenaDictEntry* pDictEnd, unsigned int* pSizes,
                                         ArenaDictEntry** ppEntry,
                                         unsigned int* pNextIndex);   // 0x011eb530
ArenaSectionManifest* rw_iter_manifest_a(void* pOut, ArenaIterator* pIterator);  // 0x011eb630
unsigned int rw_iter_manifest_b(Arena* pArena, ArenaIterator* pIterator);        // 0x011eb830
void rw_atom_table_walk(AtomTableStream* pStream, DynamicAtomTable* pAtomTable,
                        AtomSingleton* pSingleton, SizeAndAlignment* pOut);      // 0x011eaf70

// ------------------------------------------------------------------ atom table globals
extern unsigned int gnAtomTableState;                       // 0x016f4990
extern AtomTableEntry gapAtomTable[0x400];                  // 0x016f2990
extern AtomTableRoot gAtomTableRoot;                        // 0x016f2984
extern UnfixRefixAtoms gDefaultRuntimeUnfixRefixAtoms;      // 0x015d034c
extern char gIteratorHelper015d0348;                        // 0x015d0348

// --------------------------------------------------------------- RefixContextImpl
ArenaIterator* RefixContextImpl::Iterator()
{
    return (ArenaIterator*)((char*)this - 0x0c);
}

// @ 0x011e2cd0  rw::core::arena::RefixContextImpl::RefixContextImpl
RefixContextImpl::RefixContextImpl()
{
    for (unsigned int i = 0; i < 4; ++i)
        m_descriptors[i] = SizeAndAlignment();

    mpWriteCB = 0;
    mpWriteCBWithData = 0;
    mpWriteCBData = 0;
    mp2c = 0;
    mpBaseResources[0] = 0;
    mpBaseResources[1] = 0;
    mpBaseResources[2] = 0;
    mpBaseResources[3] = 0;

    for (unsigned int i = 0; i < 4; ++i)
        m_sizes[i] = SizeAndAlignment();

    mpAtomTable = 0;
    mpAtomCallback = &gDefaultRuntimeUnfixRefixAtoms;
}

// @ 0x011e2d50  rw::core::arena::RefixContextImpl::Init
void RefixContextImpl::Init(SizeAndAlignment* pDescriptors)
{
    mpBaseResources[0] = 0;
    mpBaseResources[1] = 0;
    mpBaseResources[2] = 0;
    mpBaseResources[3] = 0;

    SizeAndAlignment sizes[4];
    for (unsigned int i = 0; i < 4; ++i)
        m_sizes[i] = sizes[i];

    SizeAndAlignment requests[4];
    for (unsigned int i = 0; i < 4; ++i)
        requests[i] = pDescriptors[i];
    requests[0] = SizeAndAlignment();

    for (unsigned int i = 0; i < 4; ++i)
    {
        if (requests[i].mnBase != 0)
        {
            void** pAllocated = (void**)sizes;
            ArenaIterator* pIterator = (ArenaIterator*)((char*)this - 0x0c);
            pIterator->mpAtomSingleton->Allocate(sizes, requests, 0);
            mpBaseResources[0] = pAllocated[0];
            mpBaseResources[1] = pAllocated[1];
            mpBaseResources[2] = pAllocated[2];
            mpBaseResources[3] = pAllocated[3];
            for (unsigned int j = 0; j < 4; ++j)
                memset(mpBaseResources[j], 0, requests[j].mnBase);
            return;
        }
    }
}

// --------------------------------------------------------------- UnfixContextImpl
// @ 0x011e2c60  rw::core::arena::UnfixContextImpl::AddSubref
unsigned int UnfixContextImpl::AddSubref(void* pBase, unsigned int nObjectId, unsigned int nOffset)
{
    ArenaIterator* pIterator = mpIterator;
    unsigned int nIndex = pIterator->mSubreferences.AddNewSubreference();
    pIterator->UpdateSubreferencesData();

    ArenaDictEntry* pEntry = &mpExternalArenas->mpResourceArenas->mpDict[nIndex];
    pEntry->mpBase = pBase;
    pEntry->mpReloc = 0;
    pEntry->mnTypeId = 0;
    pEntry->mnSize = 0;
    pEntry->mnAlign = 0;

    SubreferenceRecord* pRecord = &mpSubrefs->mpRecords[nIndex];
    pRecord->mnObjectId = nObjectId;
    pRecord->mnOffset = nOffset;
    return nIndex | 0x00800000;
}

// --------------------------------------------------------------- ArenaIterator
// @ 0x011e2fe0  rw::core::arena::ArenaIterator::ArenaIterator
ArenaIterator::ArenaIterator()
    : mpResult(0), mp004(0), mp008((void*)0x015d0348), mRefix()
{
    mpArena = 0;
    mnOffset = 0;
    mpArenaPtr = &mpArena;
    mpOrigOffsetPtr = &mnOrigOffset;
    mpDictStartPtr = &mpDictStart;
    mpA4Ptr = &mpA4;
    mpDictEntryPtr = &mnDictEntry;
    mpWriteCBPtr = &mRefix.mpWriteCB;
    mpSelf = this;

    mnOrigOffset = 0;
    mpA4 = 0;
    mpDictStart = 0;
    mnDictEntry = 0;

    mbArenaLocalAtomTableAdded = false;
    mpUnfixRefixAtoms = 0;

    for (unsigned int i = 0; i < 4; ++i)
        mResourceDescriptor[i] = SizeAndAlignment();

    mpAtomSingleton = rw_atom_singleton_get();
    mSubreferences.Init(mpAtomSingleton);
    mn124 = 0;
    mn128 = 0;
    mn12c = 0;
    mn130 = 0;
    mn124 = 0;

    mAtomTable.Init(mpAtomSingleton);
    mRefix.mpAtomTable = &mAtomTable;
}

// --------------------------------------------------------------- Arena::AddObject
// @ 0x011e3300  rw::core::arena::Arena::AddObject
unsigned int Arena::AddObject(unsigned int nType, unsigned int nSize, unsigned int nAlign)
{
    unsigned int* pNumUsed = &mnNumUsed;
    ArenaDictEntry* pFreeEntry = &mpDict[mnNumUsed];
    ArenaDictEntry* pUsedEntry = &mpDict[mnUsed];

    ArenaDictState state;
    state.mpNumUsed = pNumUsed;
    state.mpFreeEntry = pFreeEntry;
    state.mpUsedEntry = pUsedEntry;
    AddResourceToArena<Adder>(nType, nAlign, nSize, &state);
    return state.mnResult;
}

// --------------------------------------------------------------- Arena::UnfixStart
// @ 0x011e3350  rw::core::arena::Arena::UnfixStart
unsigned int Arena::UnfixStart(ArenaIterator* pIterator, unsigned int nOffset)
{
    pIterator->mnOrigOffset = nOffset;
    pIterator->mnOffset = nOffset;

    SizeAndAlignment descriptors[4];
    pIterator->mpArena = this;
    pIterator->mnDictEntry = 0;
    for (unsigned int i = 0; i < 4; ++i)
        pIterator->mResourceDescriptor[i] = descriptors[i];

    for (unsigned int i = 0; i < mnNumUsed; ++i)
        mpDict[i].mpReloc = 0;

    unsigned int nSectionsSize = rw_sections_size_from(mpSections);

    pIterator->mnOffset += 0x98;
    pIterator->AccumulateSize(0x98);
    pIterator->UpdateSubreferencesData();

    UnfixContextImpl context;
    context.mpAtomTable = &pIterator->mAtomTable;
    context.mpAtomCallback = &gDefaultRuntimeUnfixRefixAtoms;
    if (pIterator->mpUnfixRefixAtoms != 0)
        context.mpAtomCallback = pIterator->mpUnfixRefixAtoms;
    context.mnExtraSize = 0;
    context.mnBase = 0x98;
    context.mnSize = nSectionsSize;
    context.mnAlignment = 4;
    context.mpIterator = pIterator;
    context.mpArena = this;
    context.mpTypes = mpSections->Types();
    context.mpExternalArenas = mpSections->ExternalArenas();
    context.mpSubrefs = mpSections->Subreferences();
    mpUnfixContext = &context;

    mpSections->Unfix(&context);

    pIterator->mnOffset += context.mnExtraSize;
    pIterator->AccumulateSize(context.mnExtraSize);
    mpUnfixContext = 0;
    return 1;
}

// --------------------------------------------------------------- Arena::UnfixNext
// @ 0x011e34d0  rw::core::arena::Arena::UnfixNext
unsigned int Arena::UnfixNext(ArenaIterator* pIterator)
{
    unsigned int nAtomIndex = 0;
    Arena* pArena = pIterator->mpArena;

    if (!pIterator->mbArenaLocalAtomTableAdded
        && pIterator->mnDictEntry >= pArena->mnNumUsed
        && pIterator->mAtomTable.mnNumTables != 0)
    {
        SizeAndAlignment descriptor;
        SizeAndAlignment atomDescriptor;
        AtomTableStream stream;
        stream.Init(&descriptor);
        rw_atom_table_walk(&stream, &pIterator->mAtomTable, rw_atom_singleton_get(),
                           &atomDescriptor);
        nAtomIndex = pArena->AddObject(0x10010, descriptor.mnBase, descriptor.mnAlignment);
        pIterator->mbArenaLocalAtomTableAdded = true;
    }

    if (pIterator->mnDictEntry >= pArena->mnNumUsed)
    {
        pIterator->mnOffset = (pIterator->mnOffset + 3) & ~3u;
        pIterator->mResourceDescriptor[0].mnBase =
            (pIterator->mResourceDescriptor[0].mnBase + 3) & ~3u;
        if (pIterator->mResourceDescriptor[0].mnAlignment < 4)
            pIterator->mResourceDescriptor[0].mnAlignment = 4;

        pIterator->mpDictStart = (ArenaDictEntry*)pIterator->mnOffset;
        unsigned int nDictSize = pArena->mnNumUsed * 0x18;
        pIterator->mnOffset += nDictSize;
        pIterator->AccumulateSize(nDictSize);
        pArena->mpSections->Subreferences()->UnfixData(pIterator);
        return 0;
    }

    ArenaDictEntry* pEntry = &pArena->mpDict[pIterator->mnDictEntry];
    ++pIterator->mnDictEntry;

    if (pEntry->mpReloc == 0)
    {
        if (pEntry->mnTypeId < 0x10030 || pEntry->mnTypeId > 0x1003f)
        {
            pIterator->AddAlignOffset(pEntry->mnAlign);
            pEntry->mpReloc = (void*)pIterator->mnOffset;
            pIterator->AddSizeOffset(pEntry->mnSize);
            if (pIterator->mResourceDescriptor[0].mnAlignment < pEntry->mnAlign)
                pIterator->mResourceDescriptor[0].mnAlignment = pEntry->mnAlign;
        }
        else
        {
            SizeAndAlignment* pDescriptor =
                &pIterator->mResourceDescriptor[pEntry->mnTypeId - 0x1002f];
            if (pIterator->mResourceDescriptor[0].mnAlignment < pEntry->mnAlign)
                pIterator->mResourceDescriptor[0].mnAlignment = pEntry->mnAlign;

            SizeAndAlignment size;
            size.mnBase = 0;
            size.mnAlignment = pEntry->mnAlign;
            pIterator->Accumulate(&size);

            SizeAndAlignment range;
            range.mnBase = pEntry->mnSize;
            range.mnAlignment = pEntry->mnAlign;
            pEntry->mpReloc = (void*)pDescriptor->mnBase;
            pIterator->AccumulateRange(&range);
        }
    }

    if (pEntry->mnTypeId > 4)
    {
        UnfixContextImpl context;
        context.mnBase = (unsigned int)pEntry->mpReloc;
        context.mpArena = pArena;
        context.mpAtomTable = &pIterator->mAtomTable;
        context.mpAtomCallback = &gDefaultRuntimeUnfixRefixAtoms;
        if (pIterator->mpUnfixRefixAtoms != 0)
            context.mpAtomCallback = pIterator->mpUnfixRefixAtoms;
        context.mnExtraSize = 0;
        context.mnSize = pEntry->mnSize;
        context.mnAlignment = pEntry->mnAlign;
        context.mpIterator = pIterator;
        context.mpExternalArenas = pArena->mpSections->ExternalArenas();
        context.mpSubrefs = pArena->mpSections->Subreferences();
        pArena->mpUnfixContext = &context;
        context.mnFlags = 0;
        context.Serialize(pEntry);
        if (nAtomIndex != 0)
            pArena->mpSections->Atoms()->SetAtomTableAndUnfixIt(nAtomIndex, pArena);
        pArena->mpUnfixContext = 0;
        pIterator->AddSizeOffset(context.mnExtraSize);
    }
    return 1;
}

// --------------------------------------------------------------- Arena::RefixStart
// @ 0x011e3780  rw::core::arena::Arena::RefixStart
unsigned int Arena::RefixStart(ArenaIterator* pIterator)
{
    SizeAndAlignment requests[4];
    const SizeAndAlignment* pDescriptors =
        (const SizeAndAlignment*)rw_iter_manifest_a(requests, pIterator);
    for (unsigned int i = 0; i < 4; ++i)
        pIterator->mRefix.m_descriptors[i] = pDescriptors[i];
    pIterator->mRefix.Init(&pIterator->mRefix.m_descriptors[0]);

    Arena* pArena = pIterator->mpArena;
    if (pIterator->mResourceDescriptor[0].mnAlignment > 1
        && (pIterator->mnOrigOffset & (pIterator->mResourceDescriptor[0].mnAlignment - 1)) != 0
        && (pIterator->mRefix.mpWriteCB != 0 || pIterator->mRefix.mpWriteCBWithData != 0))
        return 0;

    unsigned int nSectionsSize = rw_sections_size_from(pArena->mpSections);

    if (pIterator->mRefix.mpWriteCB == 0 && pIterator->mRefix.mpWriteCBWithData == 0)
        pIterator->mRefix.mpWriteCB = rw_section_manifest_default_alloc;

    ArenaHeader header;
    memcpy(&header, pArena, sizeof(header));
    header.mnUsed = pArena->mnNumUsed;
    header.mnAlignment = pIterator->mResourceDescriptor[0].mnAlignment;
    header.mpDict = pIterator->mpDictStart;
    header.mnOffset = pIterator->mnOrigOffset;
    SizeAndAlignment* pDst = header.mDescriptors;
    const SizeAndAlignment* pSrc = pIterator->mRefix.m_descriptors;
    for (unsigned int i = 0; i < 4; ++i)
        *pDst++ = *pSrc++;
    header.mnZero2c = 0;
    header.mnSectionsSize = 0x98;
    header.mnZero3c = 0;
    header.mnZero40 = 0;
    header.mnZero84 = 0;
    header.mnZero88 = 0;
    header.mnZero8c = 0;
    header.mnZero90 = 0;
    header.mnZero94 = 0;

    pIterator->mnOffset = pIterator->mnOrigOffset;
    pIterator->mnDictEntry = 0;

    if (pIterator->mRefix.mpWriteCB != 0)
        pIterator->mRefix.mpWriteCB(&header, 0x98, 0);
    else
        pIterator->mRefix.mpWriteCBWithData(&header, 0x98, 0,
                                            pIterator->mRefix.mpWriteCBData);

    pIterator->mnOffset += 0x98;
    pIterator->AccumulateSize(0x98);
    rw_section_manifest_walk(pArena->mpSections,
                             pIterator->mnOrigOffset + nSectionsSize + 0x98, pIterator);
    return 1;
}

// --------------------------------------------------------------- Arena::RefixNext
// @ 0x011e3940  rw::core::arena::Arena::RefixNext
unsigned int Arena::RefixNext(ArenaIterator* pIterator)
{
    Arena* pArena = pIterator->mpArena;
    unsigned int sizes[4];
    sizes[0] = 0;
    sizes[1] = 0;
    sizes[2] = 0;
    sizes[3] = 0;
    ArenaDictEntry* pEntry = 0;
    unsigned int nIndex = pIterator->mnDictEntry;

    if (ArenaAccumulateNextResource(nIndex, pArena->mpDict,
                                    &pArena->mpDict[pArena->mnNumUsed], sizes, &pEntry,
                                    &nIndex) == 0)
    {
        WriteDictionary(pArena, pIterator);
        pIterator->mpArena->mpSections->Subreferences()->RefixData(pIterator);
        rw_iter_manifest_b(pArena, pIterator);
        return 0;
    }

    pIterator->mnDictEntry = nIndex;
    pIterator->mRefix.Serialize(pEntry);
    return 1;
}

// --------------------------------------------------------------- Arena::FixupNext
// @ 0x011e39e0  rw::core::arena::Arena::FixupNext
bool Arena::FixupNext(ArenaIterator* pIterator)
{
    Arena* pArena = pIterator->mpArena;
    ArenaDictEntry* pEntry;
    for (;;)
    {
        if (pArena->mnNumUsed <= pIterator->mnDictEntry)
            return false;
        pEntry = &pArena->mpDict[pIterator->mnDictEntry];
        ++pIterator->mnDictEntry;
        if (pEntry->mnTypeId != 0)
            break;
    }

    ArenaTypeRecord* pType =
        pArena->mpSections->Types()->mpTypes[pEntry->mnTypeIndex];
    pIterator->mnOffset = (unsigned int)pEntry->mpReloc;
    if (pType->mpFixupCB != 0)
    {
        if (pType->mpFixupCB(pEntry->mpBase, pIterator) == 0)
            *pIterator->mpResult = 0;
    }
    return *pIterator->mpResult != 0;
}

// --------------------------------------------------------------- RefixContextImpl::Serialize
// @ 0x011e2e40  rw::core::arena::RefixContextImpl::Serialize
void RefixContextImpl::Serialize(ArenaDictEntry* pEntry)
{
    ArenaIterator* pIterator = Iterator();

    unsigned int nTypeIndex = 0;
    for (;;)
    {
        ArenaSectionTypes* pTypes = pIterator->mpArena->mpSections->Types();
        if (pTypes->mpTypes[nTypeIndex]->mnTypeId == pEntry->mnTypeId)
            break;
        ++nTypeIndex;
    }

    ArenaTypeRecord* pType = pIterator->mpArena->mpSections->Types()->mpTypes[nTypeIndex];
    unsigned int nTypeId = pType->mnTypeId;
    pEntry->mnTypeId = nTypeId;

    if (nTypeId >= 0x10030 && nTypeId <= 0x1003f)
    {
        unsigned int nIndex = nTypeId - 0x1002f;
        unsigned int nSize = m_sizes[nIndex].mnBase;
        char* pBase = (char*)mpBaseResources[nIndex] + nSize;
        char* pAligned = pBase;
        if (pEntry->mnAlign > 1)
            pAligned = (char*)(((unsigned int)pBase + pEntry->mnAlign - 1)
                               & ~(pEntry->mnAlign - 1));
        memcpy(pAligned, pEntry->mpBase, pEntry->mnSize);
        m_sizes[nIndex].mnBase = (unsigned int)pAligned + nSize
                                 + (pEntry->mnSize - (unsigned int)pBase);
        return;
    }

    unsigned int nNewOffset = pIterator->mnOffset;
    if (pEntry->mnAlign > 1)
        nNewOffset = (nNewOffset + pEntry->mnAlign - 1) & ~(pEntry->mnAlign - 1);
    pEntry->mpReloc = (void*)nNewOffset;
    unsigned int nOldOffset = pIterator->mnOffset;
    pIterator->mnOffset = nNewOffset;
    pIterator->mResourceDescriptor[0].mnBase = (unsigned int)pEntry->mpReloc;
    unsigned int nDelta = nNewOffset - nOldOffset;

    if (mpWriteCB != 0)
        mpWriteCB(pEntry->mpBase, pEntry->mnSize, nDelta);
    else
        mpWriteCBWithData(pEntry->mpBase, pEntry->mnSize, nDelta, mpWriteCBData);

    pIterator->mnOffset += pEntry->mnSize;
    pIterator->AccumulateSize(pEntry->mnSize);

    mpBaseObjectPtr = pEntry->mpBase;
    pType->mpRefixCB(pEntry->mpBase, pEntry->mpReloc, pIterator);
}

// --------------------------------------------------------------- arena::Arena::GetResourceDescriptor
// @ 0x011e3190
void Arena::GetResourceDescriptor(SizeAndAlignment* pOut, unsigned int nCount, unsigned int nFlags,
                                  void* pUnused, ArenaSectionList* pManifest,
                                  SizeAndAlignment* pExtra)
{
    DescriptorList list;

    if (nFlags == 0)
    {
        list.Add((SizeAndAlignment*)rw_section_init_descriptor(&list.mSectionA,
                                                               pManifest->mnCount));
        for (unsigned int i = 0; i < pManifest->mnCount; ++i)
        {
            ArenaSectionHeader* pSection = pManifest->mpSections[i];
            if (pSection == 0)
                continue;
            switch (pSection->mnTypeId)
            {
            case 0x10005:
                list.Add((SizeAndAlignment*)rw_section_init_descriptor(&list.mSectionA,
                                                                       pSection->mnValue));
                break;
            case 0x10006:
                list.Add((SizeAndAlignment*)rw_section_init_table12(&list.mSectionB,
                                                                    pSection->mnValue));
                break;
            case 0x10007:
                list.Add((SizeAndAlignment*)rw_section_init_table1c(&list.mSectionC));
                break;
            case 0x10008:
                list.Add((SizeAndAlignment*)rw_section_init_table0c(&list.mSectionD));
                break;
            default:
                break;
            }
        }
        list.Add(pExtra);
    }

    SizeAndAlignment total;
    total.mnBase = nCount * 0x18;
    total.mnAlignment = 4;
    list.Add(&total);

    memcpy(pOut, list.m_descriptors, sizeof(list.m_descriptors));
}

// --------------------------------------------------------------- atom table singleton
// @ 0x011e3100
AtomTableRoot* AtomTableSingleton()
{
    unsigned int nState = gnAtomTableState;
    if ((nState & 1) == 0)
    {
        nState |= 1;
        gnAtomTableState = nState;
        for (unsigned int i = 0; i < 0x400; ++i)
        {
            gapAtomTable[i].mnKey = 0;
            gapAtomTable[i].mnValue = 0;
        }
    }

    if ((nState & 2) == 0)
    {
        nState |= 2;
        gnAtomTableState = nState;
        AtomTableRoot root;
        AtomTableRoot* pRoot = root.Build(gapAtomTable, 0x400);
        gAtomTableRoot.mnFirst = pRoot->mnFirst;
        gAtomTableRoot.mnSecond = pRoot->mnSecond;
        gAtomTableRoot.mnThird = 0;
    }
    return &gAtomTableRoot;
}

// --------------------------------------------------------------- atom-table lookup result
// The hash lookup at 0x011e2b30 writes the found slot index and the table size.  The
// iterator helper then turns that into the {entry,end} pointer pair used by the callers.
struct AtomLookupResult
{
    unsigned int mnIndex;               // +0x00
    unsigned int mnCount;               // +0x04
};

struct AtomLookupPair
{
    AtomTableEntry* mpEntry;            // +0x00  matching entry, or end
    AtomTableEntry* mpEnd;              // +0x04  one past the table
};

struct ArenaAtomField
{
    AtomTableEntry* mpEntries;          // +0x00
    unsigned int mnCount;               // +0x04

    void Lookup(AtomLookupResult* pResult, const unsigned int* pKey);   // 0x011e2b30
    AtomLookupPair* Find(AtomLookupPair* pPair, const unsigned int* pKey);   // 0x011e3a60
};

// @ 0x011e3a60  rw::core::arena::ArenaAtomField::Find
AtomLookupPair* ArenaAtomField::Find(AtomLookupPair* pPair, const unsigned int* pKey)
{
    AtomLookupResult result;
    Lookup(&result, pKey);

    AtomTableEntry* pEntry = mpEntries + result.mnIndex;
    AtomTableEntry* pEnd = mpEntries + mnCount;
    if (*pKey == pEntry->mnKey)
    {
        pPair->mpEntry = pEntry;
        pPair->mpEnd = pEnd;
    }
    else
    {
        pPair->mpEntry = pEnd;
        pPair->mpEnd = pEnd;
    }
    return pPair;
}
