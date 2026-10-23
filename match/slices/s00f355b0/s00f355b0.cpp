// Slice s00f355b0 -- SP::cAppModeTerrainEditor script editor: container reset, script
// record push helpers, script playback, noun placement/removal and the two window-switch
// entry points.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The editor object is a plain 0x1b4-byte struct.  Every container member is SP::SimpleVector<T>
// (begin / end / capacity plus two words of allocator state = 0x14 bytes), so a run of members
// is spaced exactly 0x14 apart, which is what the original code shows at +0x14 .. +0xb4.
#include "types.h"
#include <new>

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;

struct Vector3 { float x, y, z; };

// ---- EA::ResourceMan::Key (0xc bytes) ------------------------------------------------------
struct Key {
    u32 m_id;
    u32 m_type;
    u32 m_group;
};

// ---- 0x38-byte transform block --------------------------------------------------------------
struct cSPTransform {
    float m[14];
    cSPTransform(const cSPTransform& other);   // 0x00538000
};

// ---- ref-counted game object ----------------------------------------------------------------
struct cRefCounted {
    virtual void AddRef();       // vtable +0x00
    virtual void Release();      // vtable +0x04
};

struct cNoun : cRefCounted {
    char pad008[0x68 - 0x08];
    u8   m_flag68;               // +0x68
};

// ---- element of the noun placement list (0x10 bytes) ----------------------------------------
struct NounEntry {
    cNoun* m_noun;               // +0x0
    void*  m_owner;              // +0x4
    u32    m_index;              // +0x8
    float  m_weight;             // +0xc

    NounEntry() : m_noun(0), m_owner(0), m_index(0), m_weight(0.0f) {}
    NounEntry(cNoun* n, void* o, u32 i, float w)
        : m_noun(n), m_owner(o), m_index(i), m_weight(w)
    {
        if (m_noun) m_noun->AddRef();
    }
    NounEntry(const NounEntry& o)
        : m_noun(o.m_noun), m_owner(o.m_owner), m_index(o.m_index), m_weight(o.m_weight)
    {
        if (m_noun) m_noun->AddRef();
    }
    ~NounEntry()
    {
        if (m_noun) m_noun->Release();
    }
};

// ---- SP::SimpleVector<T> --------------------------------------------------------------------
template<class T>
struct SimpleVector {
    T*  mBegin;
    T*  mEnd;
    T*  mCap;
    u32 mAllocA;
    u32 mAllocB;

    // out-of-line growth helper (external; relocated by the checker)
    void DoInsertValue(T* pos, const T* value);
    void clear_range(T* first, T* last);
    void resize(u32 n, const T& value);
    void DoAssignFromIterator(const T* first, const T* last, void* ctx);

    void push_back(const T& v)
    {
        T* p = mEnd;
        if (p < mCap)
        {
            mEnd = p + 1;
            if (p) new (p) T(v);
        }
        else
        {
            DoInsertValue(p, &v);
        }
    }
    void clear() { mEnd = mBegin; }
    u32 count() const { return (u32)(mEnd - mBegin); }
    bool empty() const { return mBegin == mEnd; }
};

// ---- SP::SimpleVector<eastl::string> (only ever grows with a default element here) -----------
struct StringVector {
    void* mBegin;
    void* mEnd;
    void* mCap;
    u32   mAllocA;
    u32   mAllocB;

    void InsertDefault();
};

// ---- the object -----------------------------------------------------------------------------
struct cEditor {
    char   pad000[0x0c];
    void*  m_props;                     // +0x0c  cPropertyList*
    char   pad010[0x04];
    SimpleVector<Key>           m_keys;         // +0x14
    SimpleVector<cSPTransform>  m_xforms;       // +0x28
    SimpleVector<float>         m_floatsA;      // +0x3c
    SimpleVector<float>         m_floatsB;      // +0x50
    SimpleVector<u32>           m_ints;         // +0x64
    StringVector                m_names;        // +0x78
    SimpleVector<float>         m_floatsC;      // +0x8c
    SimpleVector<Key>           m_keysB;        // +0xa0
    SimpleVector<cSPTransform>  m_xformsB;      // +0xb4
    float  m_c8;                        // +0xc8
    char   pad0cc[0x198 - 0x0cc];
    u32    m_198;                       // +0x198
    SimpleVector<NounEntry>     m_nouns;        // +0x19c
    u32    m_1b0;                       // +0x1b0

    void FUN_00f359f0(const Key& key, cSPTransform* xform);
    void FUN_00f35a70(u32 keyId, u32 unused, cSPTransform* xform, u32 id, float f, float g);
    void FUN_00f35be0(u32 value);
    void FUN_00f35c80();
    void FUN_00f35f70();
    void FUN_00f36380();
    void FUN_00f363c0();
};

// ---- SP::SpVector<T> (the engine's own vector: begin / end / cap + allocator words) ----------
struct SpVectorV {
    Vector3* mBegin;
    Vector3* mEnd;
    Vector3* mCap;
    u32 mAllocA;
    u32 mAllocB;

    void resize(int n);
    void erase(Vector3* first, Vector3* last);
    int  count() const { return (int)(mEnd - mBegin); }
};

struct SpVectorF {
    float* mBegin;
    float* mEnd;
    float* mCap;
    u32 mAllocA;
    u32 mAllocB;

    void resize(int n);
    void FUN_0052c380(int n, const float* value);
    void FUN_004d04f0(const float* first, const float* last, void* ctx);
    int  count() const { return (int)(mEnd - mBegin); }
};

// ---- a script record owned by the living universe --------------------------------------------
struct cScriptRecord {
    char       pad000[0x2c];
    u32        m_flags;        // +0x2c
    char       pad030[0xbc - 0x30];
    void*      m_block;        // +0xbc  cAppModeTerrainEditor-ish script block
    char       pad0c0[0xd0 - 0xc0];
    SpVectorV  m_vecs;         // +0xd0
    char       pad0e4[0xf8 - 0xe4];
    SimpleVector<u32> m_ints;  // +0xf8
    float      m_scale;        // +0x10c
    SpVectorF  m_floats;       // +0x110

    void UpdateEditedScript(Vector3* begin, Vector3* end, void* planet);  // 0xa17b00
    void FUN_004548d0(int n);
};

// ---- objects touched by the script-play path -------------------------------------------------
struct cProperty {
    char pad000[0x12];
    u16  m_type;               // +0x12
    u32*   GetUInt();          // 0x0041ea00
    float* GetFloat();         // 0x0041ea70
};

struct cIngredient {
    cIngredient* FUN_00b90410();   // 0x00b90410
    u32          FUN_00b8f860();   // 0x00b8f860
};

cIngredient* FUN_00b3d420(void* p);                                    // 0x00b3d420
bool __cdecl GetPropertyAsIntArray(void* props, u32 key, int* outPtr, int* outCount);
bool __cdecl GetPropertyAsFloatArray(void* props, u32 key, float** outPtr, int* outCount);
bool __cdecl GetPropertyAsVector3Array(void* props, u32 key, Vector3** outPtr, int* outCount);
bool __cdecl GetPropertyAsVector3(void* props, u32 key, Vector3* out);
void __cdecl FUN_006a0990(void* props, u32 key, void** outPtr, int* outCount);
void __cdecl FUN_004d04f0(const void* begin, const void* end, void* planet);
void __cdecl FUN_004cd3c0(void* self, int n);
void __cdecl FUN_00b2bbe0();
void* __cdecl FUN_01021260();
void* __cdecl FUN_010212a0();

struct cPlanet {
    bool FUN_00c70c00();       // 0x00c70c00
    void* FUN_008414c0();      // 0x008414c0
};

// ---- referenced globals (absolute addresses; relocations are masked by the checker) ----------
extern void* g_selectedWindow;      // 0x015ad298
extern char  g_window15ad328;       // 0x015ad328
extern char  g_checklistUI;         // 0x016c7c08
extern char* g_livingUniverse;      // 0x016c7aa4
extern float g_one;                 // 0x01485720   1.0f
extern float g_half;                // 0x01471064   0.5f
extern float g_scale;               // 0x0140e968   0.015625f

// ---- externals ------------------------------------------------------------------------------
struct cScenarioTutorialsChecklistUI {
    void SetSelectedWindow(void* w);        // 0x00efe930
    void CommitPlacement(void* p);          // 0x00f00bd0
};

// ---- objects used by the script-play / placement paths ---------------------------------------
void* __cdecl FUN_00efe5a0();                   // 0x00efe5a0  currently selected noun

struct cManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual bool v3(void* p);                   // slot 3 / +0x0c
};
cManager* __cdecl GetManager();                 // 0x0067dcd0
void* __cdecl FUN_0067dd50();                   // 0x0067dd50

struct cTerrainOp {
    float FUN_00fb8a00();                       // 0x00fb8a00
    float FUN_00fb7b90();                       // 0x00fb7b90
    void  FUN_00fbaf50(int v);                  // 0x00fbaf50
    void  FUN_00fbaf10(int v);                  // 0x00fbaf10
    void  FUN_00fbd880(float a, float b);       // 0x00fbd880
    void  FUN_00fbd6b0(int v);                  // 0x00fbd6b0
    void  FUN_00fbee30();                       // 0x00fbee30
    void  FUN_00fb91d0(float x, float y, float z);
    void  FUN_00fbd6e0(float x, float y, float z);
    void  FUN_00fbd7b0(float x, float y, float z);
    void  FUN_00fb9240(float x, float y, float z);
    void  FUN_00fbf1c0(void* arg);              // 0x00fbf1c0
};

struct cPlanetModelInner {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual cTerrainOp* GetOp();                // slot 4 / +0x10
    void SetSlot35(void* p)
    {
        typedef void (__thiscall* Fn)(void*, void*);
        ((Fn)(*(void***)this)[35])(this, p);
    }
};

struct cPlanetModel {
    void* m_24;                                 // +0x24
    void FUN_00b8d8a0(void* obj);               // 0x00b8d8a0
};
cPlanetModel* __cdecl PlanetModel();            // 0x00b3d350

struct cTerraformManager {
    int FUN_00bbc670();                         // 0x00bbc670
};
cTerraformManager* __cdecl TerraformingManager(void* obj);   // 0x00b3d430

struct cScriptTarget {
    char  pad000[0x28];
    u32   m_28;                                 // +0x28
    char  pad02c[0xb0 - 0x2c];
    float m_b0;                                 // +0xb0
    float m_b4;                                 // +0xb4

    void* FUN_00b8da60(void** out, int a, int b, int c, int d);   // 0x00b8da60
    void* FUN_00b8d8e0(int a, int b);                             // 0x00b8d8e0
};

struct cSceneObject {
    Vector3* FUN_00b18e00_offset();             // vtable +0x2c
};

struct cPlanetDistribute {
    void FUN_00c82f80();                        // 0x00c82f80
};

struct cTerrainDistributeInfo {
    void SetInfoFromProps();                    // 0x00b2bbe0
};

void* __cdecl FUN_00b3d3b0();                   // 0x00b3d3b0
void* __cdecl EAAllocate(u32 size, const char* name, int a, int b, int line,
                         void* allocator);      // 0x00f473a0
void  __cdecl FreeBlock(void* p);               // 0x00f47380
extern void*  g_eastlAllocator;                 // 0x013ebb38
// noun manager accessors
struct cGameNounManager {
    void RemoveNoun(cNoun* n);              // 0x00b225d0
};
cGameNounManager* __cdecl NounManager();    // 0x00b3d300 (singleton getter)

// terrain-editor helpers
void FUN_00f34ef0(void* begin, void* end);          // 0x00f34ef0
void FUN_00f34dd0(void* pos, const void* value);    // 0x00f34dd0
void FUN_00f34f50(void* pos, const NounEntry* value); // 0x00f34f50
void FUN_00f32710(NounEntry* entry);                // 0x00f32710
bool FUN_00f33d70(void* self, NounEntry* out, void* a, void* b, u32 index, u32 flags); // 0x00f33d70
void* FUN_00b18e00(u32 id);                         // 0x00b18e00
void FUN_009473a0();                                // vector<string> default insert

// ---- EA::Variant (0x14 bytes: 0x10 payload, u16 flags, u16 type id) --------------------------
struct Variant {
    char m_data[0x10];
    u16  m_flags;               // +0x10
    u16  m_type;                // +0x12

    Variant& operator=(const u32& value);   // 0x00427fd0
    void Destruct(bool b);                  // 0x0093db80
};

// ---- property list (virtual collection stored at cEditor+0x0c) --------------------------------
struct cPropertyList {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(u32 key, Variant* value);   // slot 5 / +0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(u32 key, void** value);     // slot 9 / +0x24
};

// ---- 0x00f359f0 -----------------------------------------------------------------------------
// 0x00f359f0  cEditor::FUN_00f359f0: append one key + one transform to the parallel lists.
// ===================================================================================================
// @ 0x00f359f0
void cEditor::FUN_00f359f0(const Key& key, cSPTransform* xform)
{
    m_keysB.push_back(key);
    m_xformsB.push_back(*xform);
}

// ===================================================================================================
// 0x00f35a70  cEditor::FUN_00f35a70: append one complete script row (key, transform, the two
// float columns, a name slot and the id) to the parallel containers.
// ===================================================================================================
// @ 0x00f35a70
void cEditor::FUN_00f35a70(u32 keyId, u32 unused, cSPTransform* xform,
                                                u32 id, float f, float g)
{
    Key key = { keyId, 0, 0 };
    m_keys.push_back(key);
    m_xforms.push_back(*xform);
    m_floatsA.push_back(g);
    m_floatsC.push_back(m_c8);
    m_floatsB.push_back(f > 0.0f ? f : 0.0f);
    m_names.InsertDefault();
    if (!m_keys.empty())
        m_ints.push_back(id);
}

// ===================================================================================================
// 0x00f35be0  cEditor::FUN_00f35be0: publish the selected value as a script property and keep the
// integer list the same length as the key list.
// ===================================================================================================
// @ 0x00f35be0
void cEditor::FUN_00f35be0(u32 value)
{
    Variant var;
    cPropertyList* props = (cPropertyList*)m_props;
    var.m_type = 10;
    var.m_flags = 2;
    var = value;
    props->SetProperty(0x2a907b7, &var);
    if (var.m_flags & 4) var.Destruct(false);
    if (m_keys.count() != m_ints.count())
        m_ints.resize(m_keys.count(), value);
}

// ===================================================================================================
// 0x00f36380  cEditor::FUN_00f36380: switch the checklist window to this editor and rebuild.
// ===================================================================================================
// @ 0x00f36380
void cEditor::FUN_00f36380()
{
    ((cScenarioTutorialsChecklistUI*)&g_window15ad328)->SetSelectedWindow(0);
    g_selectedWindow = &g_checklistUI;
    ((cScenarioTutorialsChecklistUI*)&g_checklistUI)->CommitPlacement(0);
    m_198 = *(u32*)(*(char**)&g_livingUniverse + 0x74);
    FUN_00f35f70();
}

// ===================================================================================================
// 0x00f363c0  cEditor::FUN_00f363c0: switch away from this editor and drop every placed noun.
// ===================================================================================================
// @ 0x00f363c0
void cEditor::FUN_00f363c0()
{
    u32 n = (u32)(m_nouns.mEnd - m_nouns.mBegin);
    for (u32 i = 0; i < n; i++)
    {
        NounManager()->RemoveNoun(m_nouns.mBegin[i].m_noun);
        if (m_nouns.mBegin[i].m_noun)
        {
            m_nouns.mBegin[i].m_noun = 0;
            m_nouns.mBegin[i].m_noun->Release();
        }
    }
    m_nouns.clear_range(m_nouns.mBegin, m_nouns.mEnd);
    m_1b0 = 0;
    ((cScenarioTutorialsChecklistUI*)&g_checklistUI)->CommitPlacement(0);
    g_selectedWindow = &g_window15ad328;
}

// ===================================================================================================
// 0x00f35c80  cAppModeTerrainEditor::ScriptPlay: replay the editor's property lists into the active
// planet record (script positions, ingredient ids, heights and the scale factor).
// ===================================================================================================
// @ 0x00f35c80
void cEditor::FUN_00f35c80()
{
    void* planet = FUN_01021260();
    cScriptRecord* record = (cScriptRecord*)FUN_010212a0();
    if (!record || !planet)
        return;

    record->m_flags |= 8;
    record->m_vecs.erase(record->m_vecs.mBegin, record->m_vecs.mEnd);

    int      posCount = 0;
    Vector3* posArray = 0;
    GetPropertyAsVector3Array(m_props, 0x4e13cb7, &posArray, &posCount);
    record->UpdateEditedScript(posArray, posArray + posCount, planet);

    int   ingCount = 0;
    void* ingArray = 0;
    if (!GetPropertyAsIntArray(m_props, 0x73154e0, (int*)&ingArray, &ingCount)
        || ingCount != posCount)
    {
        ingCount = posCount;
        record->m_ints.mEnd = record->m_ints.mBegin;

        u32 kindA = 0;
        u32 kindB = 0;
        u32 kindC = 0;
        for (int i = 0; i < ingCount; i++)
        {
            u32 id = FUN_00b3d420((char*)record->m_block + i * 0xc)
                         ->FUN_00b90410()
                         ->FUN_00b8f860();
            if (id == 0x29c388a)
            {
                record->m_ints.push_back(kindA);
                kindA++;
            }
            else if (id == 0x3a8be428)
            {
                record->m_ints.push_back(kindB);
                kindB++;
            }
            else if (id == 0x6d60a1cc)
            {
                record->m_ints.push_back(kindC);
                kindC++;
            }
        }
    }
    else
    {
        record->m_ints.DoAssignFromIterator((const u32*)ingArray,
                                            (const u32*)((char*)ingArray + ingCount * 4),
                                            planet);
    }

    record->m_scale = 1.0f;
    if (m_props)
    {
        void* prop = 0;
        cPropertyList* props = (cPropertyList*)m_props;
        if (props->GetProperty(0x73137bb, &prop)
            && ((cProperty*)prop)->m_type == 0xd)
        {
            record->m_scale = *((cProperty*)prop)->GetFloat();
        }
    }

    int    floatCount = 0;
    float* floatArray = 0;
    if (!GetPropertyAsFloatArray(m_props, 0x72bec91, &floatArray, &floatCount)
        || floatCount != posCount)
    {
        floatCount = posCount;
        float one = 1.0f;
        record->m_floats.FUN_0052c380(floatCount, &one);
    }
    else
    {
        record->m_floats.FUN_004d04f0(floatArray,
                                      floatArray + floatCount,
                                      planet);
    }

    if (ingCount != posCount || floatCount != posCount)
    {
        int n = ingCount > floatCount ? ingCount : floatCount;
        if (posCount > n)
            n = posCount;
        record->FUN_004548d0(n);
        FUN_004cd3c0(planet, n);
        record->m_floats.resize(n);
    }

    if (((cPlanet*)planet)->FUN_00c70c00())
    {
        cPlanetDistribute* dist = (cPlanetDistribute*)((cPlanet*)planet)->FUN_008414c0();
        dist->FUN_00c82f80();
        cTerrainDistributeInfo* info = (cTerrainDistributeInfo*)FUN_00b3d3b0();
        info->SetInfoFromProps();
    }
}

// ===================================================================================================
// 0x00f35f70  cEditor::FUN_00f35f70: rebuild the noun placement list of the checklist window.
// ===================================================================================================
// @ 0x00f35f70
void cEditor::FUN_00f35f70()
{
    if (g_selectedWindow != &g_checklistUI)
        return;

    int found = -1;
    if (!m_nouns.empty())
    {
        void* wanted = (void*)FUN_00efe5a0();
        if (wanted)
        {
            u32 n = m_nouns.count();
            for (u32 i = 0; i < n; i++)
            {
                if (m_nouns.mBegin[i].m_noun == wanted)
                    found = (int)i;
            }
        }
    }

    // drop every noun that is currently placed
    u32 n = m_nouns.count();
    for (u32 i = 0; i < n; i++)
    {
        NounManager()->RemoveNoun(m_nouns.mBegin[i].m_noun);
        if (m_nouns.mBegin[i].m_noun)
        {
            m_nouns.mBegin[i].m_noun = 0;
            m_nouns.mBegin[i].m_noun->Release();
        }
    }
    m_nouns.clear_range(m_nouns.mBegin, m_nouns.mEnd);

    // first pass: the main transform list, weighted by the owner's min/max height
    NounEntry entry;
    entry.m_weight = 1.0f;

    u32 xformOff = 0;
    u32 keyOff = 0;
    u32 count = m_xforms.count();
    for (u32 i = 0; i < count; i++)
    {
        Key* key = (Key*)((char*)m_keys.mBegin + keyOff);
        float f = m_floatsA.mBegin[i];
        if (FUN_00f33d70(this, &entry, (char*)m_xforms.mBegin + xformOff,
                         (void*)key->m_id, i, 0))
        {
            float lo = *(float*)((char*)entry.m_owner + 0x58);
            float hi = *(float*)((char*)entry.m_owner + 0x5c);
            float weight;
            if (hi > lo)
            {
                weight = (f - lo) / (hi - lo);
                if (weight < 0.0f) weight = 0.0f;
                if (weight > 1.0f) weight = 1.0f;
            }
            else
            {
                weight = 0.5f;
            }
            entry.m_weight = weight;
            m_nouns.push_back(entry);
            FUN_00f32710(&m_nouns.mEnd[-1]);
        }
        xformOff += 0x38;
        keyOff += 0xc;
    }

    // second pass: the secondary transform list, writing the placed object's position back
    xformOff = 0;
    keyOff = 0;
    count = m_xformsB.count();
    for (u32 i = 0; i < count; i++)
    {
        Key* key = (Key*)((char*)m_keysB.mBegin + keyOff);
        if (FUN_00f33d70(this, &entry, (char*)m_xformsB.mBegin + xformOff,
                         (void*)key->m_id, i, 0))
        {
            m_nouns.push_back(entry);
            NounEntry* placed = &m_nouns.mEnd[-1];
            void* obj = FUN_00b18e00((u32)placed->m_noun);
            cSPTransform* xform;
            if (((cNoun*)placed->m_owner)->m_flag68)
                xform = &m_xformsB.mBegin[placed->m_index];
            else
                xform = &m_xforms.mBegin[placed->m_index];

            Vector3* offset = ((cSceneObject*)obj)->FUN_00b18e00_offset();
            u8* dst = (u8*)xform;
            *(float*)(dst + 0x4) = offset->x;
            *(float*)(dst + 0x8) = offset->y;
            *(float*)(dst + 0xc) = offset->z;
            *(u16*)(dst + 0x0) |= 4;
            (*(u16*)(dst + 0x2))++;
        }
        xformOff += 0x38;
        keyOff += 0xc;
    }

    NounEntry* selected = 0;
    if (found >= 0 && found < (int)m_nouns.count())
        selected = &m_nouns.mBegin[found];
    m_1b0 = (u32)selected;

    ((cScenarioTutorialsChecklistUI*)&g_checklistUI)
        ->CommitPlacement(selected ? selected->m_noun : 0);

    if (entry.m_noun)
        entry.m_noun->Release();
}

// ===================================================================================================
// 0x00f355b0  build the terrain "script" from the property list hanging off the target object.
// ===================================================================================================
// @ 0x00f355b0
void __cdecl FUN_00f355b0(cScriptTarget* target)
{
    int  idA = 0xb;
    int  idB = 0xb;
    Vector3 pos1, pos2, pos3, pos4, pos5;
    void*   refTemp = 0;
    float*  floatArray = 0;
    int     floatCount = 0;
    Vector3* vecArray = 0;
    int     vecCount = 0;
    SpVectorF heights = { 0, 0, 0, 0, 0 };
    SpVectorV vecs = { 0, 0, 0, 0, 0 };

    cManager* mgr = GetManager();
    if (refTemp)
    {
        void* old = refTemp;
        refTemp = 0;
        ((cRefCounted*)old)->Release();
    }

    void* temp = target->FUN_00b8da60(&refTemp, 0, 0, 0, 0);
    if (!mgr->v3(temp))
        goto done;
    if (!refTemp)
        goto done;

    {
        cPropertyList* props = (cPropertyList*)((char*)refTemp + 0x18);
        void* prop = 0;
        if (props->GetProperty(0x536250d, &prop)
            && ((cProperty*)prop)->m_type == 10)
        {
            idA = (int)*((cProperty*)prop)->GetUInt();
        }
        prop = 0;
        if (props->GetProperty(0x536250c, &prop)
            && ((cProperty*)prop)->m_type == 10)
        {
            idB = (int)*((cProperty*)prop)->GetUInt();
        }

        GetPropertyAsVector3(props, 0x3a23f99, &pos1);
        GetPropertyAsVector3(props, 0xb6929c95, &pos2);
        GetPropertyAsVector3(props, 0xb6929c94, &pos3);
        GetPropertyAsVector3(props, 0x968c496a, &pos4);
        GetPropertyAsVector3(props, 0x968c496b, &pos5);

        GetPropertyAsFloatArray(props, 0xb6929c92, &floatArray, &floatCount);
        heights.resize(floatCount);
        for (int i = 0; i < floatCount; i++)
            heights.mBegin[i] = floatArray[i];

        GetPropertyAsVector3Array(props, 0xb6929c93, &vecArray, &vecCount);
        vecs.resize(vecCount);
        for (int i = 0; i < vecCount; i++)
            vecs.mBegin[i] = vecArray[i];
    }

done:
    {
        void* planetEntry = target->FUN_00b8d8e0(0, 1);
        PlanetModel()->FUN_00b8d8a0(planetEntry);

        cPlanetModelInner* inner = (cPlanetModelInner*)((cPlanetModel*)PlanetModel())->m_24;
        cTerrainOp* op = inner->GetOp();

        target->m_b4 = op->FUN_00fb8a00();
        target->m_b0 = op->FUN_00fb7b90();
        target->m_28 = (u32)(TerraformingManager(target)->FUN_00bbc670() + 2);
        op->FUN_00fbaf50(idA);
        op->FUN_00fbaf10(idB);
        op->FUN_00fbd880((pos1.z - 0.5f) * 0.015625f,
                         (pos1.y - 0.5f) * 0.015625f);
        op->FUN_00fbd6b0(1);
        op->FUN_00fbee30();
        inner->SetSlot35((void*)FUN_0067dd50());
        op->FUN_00fb91d0(pos1.x, pos1.y, pos1.z);
        op->FUN_00fbd6e0(pos2.x, pos2.y, pos2.z);
        op->FUN_00fbd7b0(pos3.x, pos3.y, pos3.z);
        op->FUN_00fb9240(pos4.x, pos4.y, pos4.z);

        // hand the heights over as an eastl vector and release the temporaries
        int n = (int)(heights.mEnd - heights.mBegin);
        float** arg = (float**)&heights;      // 5-word aggregate passed by value
        if (n != 0)
        {
            float* block = (float*)EAAllocate(n * 4, "Simulator", 0, 0, 0xd1,
                                              g_eastlAllocator);
            for (int i = 0; i < n; i++)
                block[i] = heights.mBegin[i];
            heights.mBegin = block;
            heights.mEnd = block + n;
            heights.mCap = block + n;
        }
        (void)arg;
        op->FUN_00fbf1c0(&heights);

        if (refTemp)
        {
            void* old = refTemp;
            refTemp = 0;
            ((cRefCounted*)old)->Release();
        }
        if (heights.mBegin && *(u32*)((char*)heights.mBegin - 4) != 0)
            FreeBlock(heights.mBegin);
        if (vecs.mBegin && *(u32*)((char*)vecs.mBegin - 4) != 0)
            FreeBlock(vecs.mBegin);
    }
}
