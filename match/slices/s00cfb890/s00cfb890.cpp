// Slice s00cfb890 (0x00cfb890, 892 bytes): recreate the colour palettes an avatar/city editor
// shows: the avatar profile's own colour, then either every specialty colour of the three
// specialty tables plus the colours carried by the loaded city/noun game data (debug path), or
// the current terrain sphere's two colours and the colours of two of the three tables.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_00accc30[];
extern "C" unsigned char g_00b1e500[];
extern "C" unsigned char g_00cd7d10[];
extern "C" unsigned char g_00d3d420[];

// ---------------------------------------------------------------- colour record / vectors
struct Triple {                             // 12-byte colour record (three 32-bit components)
    uint32_t m0;
    uint32_t m4;
    uint32_t m8;
};

struct TripleVec {                          // eastl::vector<Triple, sp_vector_allocator>
    Triple* mBegin;                         // +0x00
    Triple* mEnd;                           // +0x04
    Triple* mCap;                           // +0x08
    void DoInsertValue(Triple* pos, const Triple& v);   // 0x004e3e10 (slow path of push_back)
    void push_back(const Triple& v) {
        if (mEnd < mCap) {
            Triple* p = mEnd;
            mEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mEnd, v);
        }
    }
};

// ---------------------------------------------------------------- specialty colour tables
struct ColorTable {                         // 0x1c-byte record, three of them live back to back
    uint8_t m00[0x1c];
    bool Contains(uint32_t key);                 // 0x00bf2c80
    void Insert(uint32_t key);                   // 0x00bf9300 (default-insert)
    Triple* LookupColor(uint32_t key);           // 0x00bf9700 (__thiscall, ret 4)
};

extern ColorTable g_colorTables[3];         // 0x0168caf0 .. 0x0168cb44
extern uint32_t        g_specialtyIds[12];       // 0x01478abc .. 0x01478aec
extern uint8_t         g_useAllSpecialtyColors;  // 0x0169d2be

static const uint32_t kNoSpecialty = 0x99e92f05u;    // marker stored in an unused specialty slot

// ---------------------------------------------------------------- game data objects
struct ColorHost {                          // object that owns the colour at +0x504
    uint8_t     mPad[0x504];
    Triple mColor;                          // +0x504
};

struct GameData {
    virtual void AddRef() = 0;              // +0x00
    virtual void Release() = 0;             // +0x04
    virtual void v08() = 0;                 // +0x08
    virtual void v0c() = 0;                 // +0x0c
    virtual void v10() = 0;                 // +0x10
    virtual void v14() = 0;                 // +0x14
    virtual void v18() = 0;                 // +0x18
    virtual void v1c() = 0;                 // +0x1c
    virtual void v20() = 0;                 // +0x20
    virtual void v24() = 0;                 // +0x24
    virtual void v28() = 0;                 // +0x28
    virtual bool IsHidden() = 0;            // +0x2c
    uint8_t     mPad[0xa4 - 0x04];           // vfptr occupies the first four bytes
    ColorHost* mColorHost;                  // +0xa4
};

struct GameDataVec {                        // eastl::vector<GameData*>
    GameData** mBegin;                      // +0x00
    GameData** mEnd;                        // +0x04
    GameData** mCap;                        // +0x08
};

struct GameDataHolder {                     // object returned by NounManager::GetGameDataVector
    uint32_t    m00;                        // +0x00
    GameDataVec mVec;                       // +0x04
};

// ---------------------------------------------------------------- singletons and callees
struct Profile {
    uint8_t     mPad[0x504];
    Triple mColor;                          // +0x504
};
struct ProfileManager {
    Profile* GetAvatarProfile();            // 0x004df420
};
ProfileManager* GetProfileManager();        // 0x00401090

struct TerrainSphere {
    uint8_t     mPad[0x1150];
    Triple mColorA;                         // +0x1150
    Triple mColorB;                         // +0x115c
};

struct Civilization {
    void SetupSpecialtyColors(ColorTable* table);   // 0x00bf4e50 (__thiscall, ret 4)
};

struct NounManager {
    GameDataHolder* GetGameDataVector(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e); // 0x00b21340
    Civilization* GetPlayerCivilization();  // 0x00b25fb0
    TerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
NounManager* GetNounManager();              // 0x00b3d300

// eastl's array new/delete of the pointer buffer (name/flags/debug/file from the inline
// allocator call in the original).
void* EAAllocateArray(uint32_t bytes, const char* name, int flags, int debugFlags,
                      const char* file, int line);          // 0x00f473a0
void  EAFreeArray(void* p);                                  // 0x00f47380
extern const char g_vectorName[];           // 0x013f09b4
extern const char g_vectorFile[];           // 0x013ebb38

// ---------------------------------------------------------------- editor palette
struct cEditorAvatarColors {
    uint8_t        mPad00[0x40];
    TripleVec mPalette;                     // +0x40
    uint8_t        mPad4c[0x54 - 0x4c];
    TripleVec mPaletteAux;                  // +0x54

    void BuildPalettes();
};

// @ 0x00cfb890
void cEditorAvatarColors::BuildPalettes()
{
    mPalette.push_back(GetProfileManager()->GetAvatarProfile()->mColor);

    if (g_useAllSpecialtyColors) {
        for (int i = 0; i < 12; ++i) {
            uint32_t specialty = g_specialtyIds[i];
            if (specialty != kNoSpecialty)
                g_colorTables[0].Insert(specialty);
        }

        GetNounManager()->GetPlayerCivilization()->SetupSpecialtyColors(&g_colorTables[0]);

        for (int table = 0; table < 3; ++table) {
            for (int i = 0; i < 12; ++i)
                mPalette.push_back(*g_colorTables[table].LookupColor(g_specialtyIds[i]));
        }

        NounManager* nouns = GetNounManager();
        GameDataVec& vec = nouns->GetGameDataVector((uint32_t)g_00cd7d10, (uint32_t)g_00d3d420, (uint32_t)g_00accc30,
                                                    (uint32_t)g_00b1e500, 0x01be418e)->mVec;
        uint32_t count = (uint32_t)(vec.mEnd - vec.mBegin);
        GameData** colors = count != 0
            ? (GameData**)EAAllocateArray(count * sizeof(GameData*), g_vectorName, 0, 0,
                                          g_vectorFile, 0xd1)
            : 0;
        GameData** end = vec.mEnd;
        GameData** dst = colors;
        for (GameData** src = vec.mBegin; src != end; ++src, ++dst) {
            if (dst) {
                *dst = *src;
                if (*dst)
                    (*dst)->AddRef();
            }
        }

        for (GameData** it = colors; it != dst; ++it)
            if (!(*it)->IsHidden())
                mPalette.push_back((*it)->mColorHost->mColor);

        for (GameData** it = colors; it < dst; ++it)
            if (*it)
                (*it)->Release();

        if (colors && ((int*)colors)[-1] != 0)
            EAFreeArray(colors);
    } else {
        mPalette.push_back(GetNounManager()->GetCurrentTerrainSphere()->mColorA);
        mPalette.push_back(GetNounManager()->GetCurrentTerrainSphere()->mColorB);

        for (int i = 0; i < 12; ++i) {
            uint32_t specialty = g_specialtyIds[i];
            if (!g_colorTables[1].Contains(specialty))
                g_colorTables[1].Insert(specialty);
            mPalette.push_back(*g_colorTables[1].LookupColor(specialty));
        }
        for (int i = 0; i < 12; ++i) {
            uint32_t specialty = g_specialtyIds[i];
            if (!g_colorTables[2].Contains(specialty))
                g_colorTables[2].Insert(specialty);
            mPaletteAux.push_back(*g_colorTables[2].LookupColor(specialty));
        }
    }
}
