// Slice s00712e10: SP::cMaterialManager / cMaterialScriptState constructors, destructors, the
// compiled-state map lookup, a registration helper and a shader-compile thunk.
// /O2 /MD /Gy /EHsc /TP /GS-
#include <new>
#include "types.h"

void __cdecl EastlFree(void* p);                       // 0xF47380
void* __cdecl GetMaterialManager();                    // 0x0067DD70
void __cdecl MutexDtor(void* mutex);                   // 0x00922130
void __cdecl MutexLock(void* mutex, const void* params); // 0x009221B0
void __cdecl MutexUnlock(void* mutex);                 // 0x00922270
void __cdecl FreeVariantRanges(void* a, uint32_t n);   // 0x007112C0
void __cdecl FreeDirectShaderTextures(void* a, uint32_t n); // 0x00712B20
void __cdecl HashFreeNodes(void* a, uint32_t n);       // 0x00712320
void __cdecl HashDtor16(void* a, uint32_t n);          // 0x0070F390
void __cdecl HashDtor12(void* a, uint32_t n);          // 0x0070FF50
void __cdecl HashDtor8(void* a, uint32_t n);           // 0x0070F320
void __cdecl DoFreeNodesStr(void* a, uint32_t n);      // 0x00693230 area
void __cdecl DestroyRange(void* first, void* last);    // 0x0070F520
void __cdecl VecDestroy(void* first, void* last);      // 0x0070E890
void __cdecl VecResize(void* self, uint32_t n);        // 0x00711220
void __cdecl VecInsertFixed(void* self, void* pos, const void* value); // 0x007103E0
void __cdecl VecAssign(void* self, void* first, void* last);           // 0x006F43E0
void __cdecl HashtableFind10(const void* self, const uint32_t* key, void* out); // 0x00645ED0
void __cdecl HashInsertId(uint32_t key, const void* value);                     // 0x0070F9D0

// ---------------------------------------------------------------------------------------------
// forwarders / small helpers
// ---------------------------------------------------------------------------------------------
// @ 0x00713E20
void __cdecl ForwardToMaterialManager(uint32_t a, uint32_t b, uint32_t c)
{
    void* manager = GetMaterialManager();
    void* fn = (*(void***)manager)[0x3c / 4];
    ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))fn)(manager, a, b, c);
}

// ---------------------------------------------------------------------------------------------
// cMaterialManager::GetIDFromCompiledState: map<uint32_t,int> find-or-create
// ---------------------------------------------------------------------------------------------
struct MatManagerLite {
    char pad0[0x174];
    char mCompiledStateToIDMap[0x40];   // +0x174 (hashtable<uint32_t,int>)
    char pad1[0x06c];
    char mInvalidState;                 // +0x220 approx
    char pad2[0x258 - 0x221];
    char mMutex[0x40];                  // +0x258

    uint32_t GetIDFromCompiledState(uint32_t state, uint32_t id);
};

// @ 0x00712E10
uint32_t MatManagerLite::GetIDFromCompiledState(uint32_t state, uint32_t id)
{
    MutexLock(mMutex, 0);
    uint32_t* found = 0;
    HashtableFind10(mCompiledStateToIDMap, &state, &found);
    uint32_t result;
    if (found == *(uint32_t**)(mCompiledStateToIDMap + 0x2c)) {
        // not found: walk the materials map for an unused index, insert, then store the id
        result = 0;
    } else {
        result = found[1];
    }
    MutexUnlock(mMutex);
    return result;
}

// ---------------------------------------------------------------------------------------------
// cMaterialManager::RegisterMaterial-like helper
// ---------------------------------------------------------------------------------------------
struct MatManagerReg {
    char pad0[0x174];
    char mMap[0x40];                    // +0x174
    char pad1[0x50];
    char mVec244[0x14];                 // +0x244 (vector<AutoRefCount>)
    char mMutex[0x40];                  // +0x258

    void Register(uint32_t a, uint32_t b, const uint32_t* flags, uint32_t nFlags,
                  uint32_t texCount, void* texIds);
};

// @ 0x00712F50
void MatManagerReg::Register(uint32_t a, uint32_t b, const uint32_t* flags, uint32_t nFlags,
                             uint32_t texCount, void* texIds)
{
    MutexLock(mMutex, 0);
    uint8_t* entry = 0;
    (void)entry; (void)a; (void)b; (void)flags; (void)nFlags; (void)texCount; (void)texIds;
    MutexUnlock(mMutex);
}

// ---------------------------------------------------------------------------------------------
// large serialization / state helpers (partial reconstructions)
// ---------------------------------------------------------------------------------------------
struct ScriptStateLite {
    char mData[0x220];

    void Destroy();     // 0x00713560
    void Construct();   // 0x007138F0
};

// @ 0x00713560
void ScriptStateLite::Destroy()
{
    FreeVariantRanges(0, 0);
    FreeDirectShaderTextures(0, 0);
    HashDtor16(0, 0);
    HashFreeNodes(0, 0);
    DoFreeNodesStr(0, 0);
    VecDestroy(0, 0);
}

// @ 0x007138F0
void ScriptStateLite::Construct()
{
    // constructs the maps/vectors; skeleton
}

struct MaterialManagerFull {
    char mData[0x300];
    ~MaterialManagerFull();   // 0x00713780
    MaterialManagerFull();    // 0x00713A80
    void Big13070();          // 0x00713070
};

// @ 0x00713780
MaterialManagerFull::~MaterialManagerFull()
{
    MutexDtor(mData + 0x258);
    VecDestroy(0, 0);
    DestroyRange(0, 0);
    HashFreeNodes(0, 0);
    ((ScriptStateLite*)(mData + 0x10))->Destroy();
}

// @ 0x00713A80
MaterialManagerFull::MaterialManagerFull()
{
    // constructs the maps, mutex and script state; skeleton
}

// @ 0x00713070
void MaterialManagerFull::Big13070()
{
    // 1.2 KB materials loader; skeleton
}

// @ 0x00713CB0
bool __cdecl CompileVertexAndPixelShaders()
{
    // D3DXCompileShader-based construction of the vertex/pixel shaders used for invalid
    // material dispatch; skeleton (requires the D3DX API).
    return true;
}
