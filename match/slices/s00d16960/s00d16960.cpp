// s00d16960 -- SP::cGameEditInputStrategy::PopulateLoadDialogGridWithLevels
// Reconstructed from the retail disassembly: it fills the level-loader dialog grid with the
// level files the resource manager knows about, twice (a level pass and a planet-scope pass,
// told apart by the filter's group id), then resets the grid's selection and scroll state.
//
//   0x00d16960  cGameEditInputStrategy::PopulateLoadDialogGridWithLevels   thiscall, ret 0
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"
#pragma pack(push, 4)

void EASTL_free(void* p);                                  // 0x00f47380

// ---------------------------------------------------------------- resource manager types
namespace EA {
namespace ResourceMan {

struct Key {
    uint32_t mInstanceID;   // +0x00
    uint32_t mTypeID;       // +0x04
    uint32_t mGroupID;      // +0x08
};

// eastl::vector<Key, eastl::sp_vector_allocator>: 0x14 bytes.  The allocator slot is two words and
// the second one is never written, so only the three pointers are zeroed before the key-list call.
struct KeyVec {
    Key* mpBegin;           // +0x00
    Key* mpEnd;             // +0x04
    Key* mpCapacity;        // +0x08
    uint32_t mAllocator;    // +0x0c
    uint32_t mAllocatorPad; // +0x10
};

// A record filter (EA::ResourceMan::KeyFilter-derived): its vtable pointer plus the group and type
// ids it keeps.  The caller restores the base vtable before the temporary is dropped.
struct KeyFilter {
    void* mpVtbl;           // +0x00
    uint32_t mGroupID;      // +0x04
    uint32_t mTypeID;       // +0x08
};

// Every slot is declared so that a named slot sits at its retail vtable offset.
struct IResourceManager {
    virtual ~IResourceManager();
    virtual bool Initialize();
    virtual bool Dispose();
    virtual bool GetResource();
    virtual bool GetResourceAsync();
    virtual bool GetLoadedResource();
    virtual bool ReloadResource();
    virtual bool GetPrivateResource();
    virtual bool WriteResource();
    virtual void SetTypeMapping();
    virtual int GetRecordTypesFromResourceType();
    virtual int GetTypeMapping();
    virtual int FindRecord();
    virtual int GetKeyList();
    virtual int GetRecordKeyList(KeyVec* pKeys, KeyFilter* pFilter, int flags);   // 0x38
    virtual int GetRecordKeyList2();
    virtual bool RegisterChangeNotification();
    virtual bool RegisterFactory();
    virtual int FindFactory();
    virtual int GetFactoryList();
    virtual bool RegisterDatabase();
    virtual bool IsDatabaseRegistered();
    virtual int FindDatabase();
    virtual int GetDatabaseList();
    virtual void DoDatabaseChanged();
    virtual bool RegisterCache();
    virtual int FindCache();
    virtual bool CacheResource();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual int GetFileName(const Key* pKey, void* pName);                        // 0x7c
};

}  // namespace ResourceMan
}  // namespace EA

EA::ResourceMan::IResourceManager* GetManager();           // 0x0067dcd0
extern void* vtPropFilter[];                               // 0x013f662c
extern void* vtIMsgHandler[];                              // 0x013eb394 (base-filter vtable)

// ---------------------------------------------------------------- 16-bit string
// Three pointers plus the allocator flag; the empty string is a static one-character buffer,
// so an empty string's capacity is its begin + 1 element and only a heap buffer is released.
extern wchar_t gEmptyString16[];                           // 0x01667bac

class string16 {
 public:
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    int mAllocator;         // +0x0c

    string16() {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~string16() {
        if ((((int)mpCapacity - (int)mpBegin) & ~1) > 2) {
            if (mpBegin) EASTL_free(mpBegin);
        }
    }
    const wchar_t* c_str() const { return mpBegin; }
};

// ---------------------------------------------------------------- the level-loader grid
class IWinGrid {
 public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(int);            // 0x88
    virtual void v08c(int);                                                      // 0x8c
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4();
    virtual void va8(int, int);                                                  // 0xa8
    virtual void v0ac(); virtual void v0b0(); virtual void v0b4(); virtual void v0b8();
    virtual void v0bc(); virtual void v0c0(); virtual void v0c4(); virtual void v0c8();
    virtual void v0cc(); virtual void v0d0(); virtual void v0d4(); virtual void v0d8();
    virtual void v0dc(); virtual void v0e0(); virtual void v0e4(); virtual void v0e8();
    virtual void v0ec(); virtual void v0f0(); virtual void v0f4(); virtual void v0f8();
    virtual void v0fc(); virtual void v100(); virtual void v104(); virtual void v108();
    virtual void v10c(); virtual void v110(); virtual void v114(); virtual void v118();
    virtual void v11c(); virtual void v120(); virtual void v124(); virtual void v128();
    virtual void v12c(); virtual void v130(); virtual void v134(); virtual void v138();
    virtual void v13c(); virtual void v140(); virtual void v144(); virtual void v148();
    virtual void v14c(); virtual void v150(); virtual void v154(); virtual void v158();
    virtual void v15c(); virtual void v160(); virtual void v164(); virtual void v168();
    virtual void v16c();                                                         // 0x16c begin update
    virtual void v170(); virtual void v174(); virtual void v178(); virtual void v17c();
    virtual void v180(); virtual void v184(); virtual void v188(); virtual void v18c();
    virtual void v190(); virtual void v194(); virtual void v198(); virtual void v19c();
    virtual void v1a0();
    virtual void v1a4(int nDialog, int nRow, const wchar_t* pText, int a, int b, int c);  // 0x1a4
    virtual void v1a8(); virtual void v1ac(); virtual void v1b0(); virtual void v1b4();
    virtual void v1b8(); virtual void v1bc(); virtual void v1c0(); virtual void v1c4();
    virtual void v1c8(); virtual void v1cc(); virtual void v1d0(); virtual void v1d4();
    virtual void v1d8(); virtual void v1dc(); virtual void v1e0(); virtual void v1e4();
    virtual void v1e8(); virtual void v1ec();
    virtual void v1f0(int a, int b, int c, int d);                               // 0x1f0
};

// ---------------------------------------------------------------- the input strategy
// Only the member this function uses is modelled: the level-loader grid at +0x88.
class cGameEditInputStrategy {
 public:
    void PopulateLoadDialogGridWithLevels();

    uint8_t mPad000[0x88];
    IWinGrid* mGridFileList;  // +0x88
};

// Cleared before the grid is refilled.
extern uint8_t gEditorFlag21;                              // 0x0169dc21

// @ 0x00d16960
void cGameEditInputStrategy::PopulateLoadDialogGridWithLevels()
{
    gEditorFlag21 = 0;
    mGridFileList->v16c();

    EA::ResourceMan::IResourceManager* pManager = GetManager();
    int nRow = 0;

    {
        EA::ResourceMan::KeyVec keys;
        keys.mpBegin = 0;
        keys.mpEnd = 0;
        keys.mpCapacity = 0;

        EA::ResourceMan::KeyFilter filter;
        filter.mpVtbl = vtPropFilter;
        filter.mGroupID = 0x047b8300u;
        filter.mTypeID = 0x02412c19u;
        pManager->GetRecordKeyList(&keys, &filter, 0);

        EA::ResourceMan::Key* pKey = keys.mpBegin;
        for (; pKey != keys.mpEnd; ++pKey, ++nRow) {
            string16 name;
            pManager->GetFileName(pKey, &name);
            mGridFileList->v1a4(0, nRow, name.c_str(), 0, 1, 0);
        }

        filter.mpVtbl = vtIMsgHandler;
        if (keys.mpBegin) {
            if (((int*)keys.mpBegin)[-1]) EASTL_free(keys.mpBegin);
        }
    }

    {
        EA::ResourceMan::KeyVec keys;
        keys.mpBegin = 0;
        keys.mpEnd = 0;
        keys.mpCapacity = 0;

        EA::ResourceMan::KeyFilter filter;
        filter.mpVtbl = vtPropFilter;
        filter.mGroupID = 0x3981db81u;
        filter.mTypeID = 0x02412c19u;
        pManager->GetRecordKeyList(&keys, &filter, 0);

        EA::ResourceMan::Key* pKey = keys.mpBegin;
        for (; pKey != keys.mpEnd; ++pKey, ++nRow) {
            string16 name;
            pManager->GetFileName(pKey, &name);
            mGridFileList->v1a4(0, nRow, name.c_str(), 0, 1, 0);
        }

        filter.mpVtbl = vtIMsgHandler;
        if (keys.mpBegin) {
            if (((int*)keys.mpBegin)[-1]) EASTL_free(keys.mpBegin);
        }
    }

    mGridFileList->v1f0(0, 0, 1, 0);
    mGridFileList->v08c(0);
    mGridFileList->v088(0);
    mGridFileList->va8(0, 0);
}

#pragma pack(pop)
