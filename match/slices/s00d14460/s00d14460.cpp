// SporeApp.exe slice s00d14460 -- gameplay marker command (gold6, worker 36)

#include "types.h"
#include <stddef.h>

// ---------------------------------------------------------------------------
// small shared types
// ---------------------------------------------------------------------------

struct cVec3 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
};

struct cVec4 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
    float w;                                                // +0x0c
};

struct cMat4 {
    float m[16];                                            // +0x00
};

// ---------------------------------------------------------------------------
// engine sub-objects
// ---------------------------------------------------------------------------

// Spatial component of a noun (noun+0x34).
struct cSpatial {
    virtual void  p000();                                   // +0x00
    virtual void  p004();                                   // +0x04
    virtual void  p008();                                   // +0x08
    virtual void  p00c();                                   // +0x0c
    virtual void  p010();                                   // +0x10
    virtual void  p014();                                   // +0x14
    virtual void  p018();                                   // +0x18
    virtual void  p01c();                                   // +0x1c
    virtual void  p020();                                   // +0x20
    virtual void  p024();                                   // +0x24
    virtual void  p028();                                   // +0x28
    virtual void* GetPosition();                            // +0x2c
    virtual void  p030();                                   // +0x30
    virtual void  p034();                                   // +0x34
    virtual void  SetPosition(const void* pPosition);       // +0x38
    virtual void  SetOrientation(const void* pMatrix);      // +0x3c
};

// A noun (game object); +0x108 holds the definition values and +0x118 the value count.
struct cNoun {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04 (release)
    virtual void* v008();                                   // +0x08
    virtual void* v00c(uint32_t nType);                     // +0x0c (cast)
    virtual void  v010();                                   // +0x10
    virtual void  v014();                                   // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void  v038();                                   // +0x38
    virtual void  v03c();                                   // +0x3c
    virtual void  v040();                                   // +0x40
    virtual void  v044();                                   // +0x44
    virtual void  v048();                                   // +0x48
    virtual void  v04c();                                   // +0x4c
    virtual void  v050();                                   // +0x50
    virtual void  v054();                                   // +0x54
    virtual void  v058();                                   // +0x58
    virtual void  v05c();                                   // +0x5c
    virtual void  v060();                                   // +0x60
    virtual void  v064();                                   // +0x64
    virtual void  v068();                                   // +0x68
    virtual void  v06c();                                   // +0x6c
    virtual void  v070();                                   // +0x70
    virtual void  v074();                                   // +0x74
    virtual void  v078();                                   // +0x78
    uint8_t       mPad004[0x30];                            // +0x04 .. +0x33
    cSpatial      mSpatial;                                 // +0x34
    uint8_t       mPad038[0xd0];                            // +0x38 .. +0x107
    int32_t       mDefA;                                    // +0x108
    int32_t       mDefB;                                    // +0x10c
    int32_t       mDefC;                                    // +0x110
    int32_t       mDefD;                                    // +0x114
    int32_t       mValueCount;                              // +0x118
    int32_t       mValues[64];                              // +0x11c
};

// Terrain cursor used by the marker placement tool.
struct cTerrainCursor {
    virtual void  t000();                                   // +0x00
    virtual void  t004();                                   // +0x04
    virtual void  t008();                                   // +0x08
    virtual void  t00c();                                   // +0x0c
    virtual void  t010();                                   // +0x10
    virtual void  t014();                                   // +0x14
    virtual void  t018();                                   // +0x18
    virtual void  t01c();                                   // +0x1c
    virtual void  t020();                                   // +0x20
    virtual void  t024();                                   // +0x24
    virtual void  t028();                                   // +0x28
    virtual void  t02c();                                   // +0x2c
    virtual void  t030();                                   // +0x30
    virtual void  t034();                                   // +0x34
    virtual void  t038();                                   // +0x38
    virtual void  t03c();                                   // +0x3c
    virtual void  t040();                                   // +0x40
    virtual void  t044();                                   // +0x44
    virtual void  t048();                                   // +0x48
    virtual void  t04c();                                   // +0x4c
    virtual void  t050();                                   // +0x50
    virtual void  t054();                                   // +0x54
    virtual void  t058();                                   // +0x58
    virtual void  t05c();                                   // +0x5c
    virtual void  t060();                                   // +0x60
    virtual void  t064();                                   // +0x64
    virtual void  t068();                                   // +0x68
    virtual void  t06c();                                   // +0x6c
    virtual int32_t t070();                                 // +0x70
    virtual void  t074();                                   // +0x74
    virtual void  t078();                                   // +0x78
    virtual void  t07c();                                   // +0x7c
    virtual void  t080();                                   // +0x80
    virtual void  t084();                                   // +0x84
    virtual void  t088();                                   // +0x88
    virtual void  t08c();                                   // +0x8c
    virtual void  t090();                                   // +0x90
    virtual void  t094();                                   // +0x94
    virtual void  t098();                                   // +0x98
    virtual void  t09c();                                   // +0x9c
    virtual void  t0a0();                                   // +0xa0
    virtual void  t0a4();                                   // +0xa4
    virtual void  t0a8();                                   // +0xa8
    virtual void  t0ac(float fValue);                       // +0xac
    virtual void  t0b0(float fValue);                       // +0xb0
    virtual void  t0b4();                                   // +0xb4
    virtual void  t0b8(int32_t nMode);                      // +0xb8
};

// Manager of all nouns.
struct cGameNounManager {
    void* mpVTable;                                         // +0x00
    uint8_t mPad004[0x34];                                  // +0x04 .. +0x37
    void* GetGameDataVector(void* pA, void* pB, void* pC, void* pD, void* pE);   // 0x00b21340
    void  RemoveNoun();                                     // 0x00b225d0
    void* CreateNoun(uint32_t nType);                       // 0x00b22640
};

struct cParser;
struct cArguments;

// ArgScript: argument spec of a command.
struct cArgumentSpec {
    uint8_t mPad00[0xc8];                                   // +0x00 .. +0xc7

    void  Init(bool bFlag);                                 // 0x0083a9f0
    void  Parse(cArguments* pArguments, cParser* pParser);   // 0x0083b9d0
    void  Done();                                           // 0x00405050
    const char* HelpString(const char* pName, int32_t nFlags);   // 0x0083a2f0
};

// Builds the command's argument spec (the spec object is passed on the stack).
void __cdecl ArgScript_ConstructSpec(cArgumentSpec* pSpec, const char* pComment,
                                     const char* pTypeSpec, void* pTypeValue, const char* pTypeName,
                                     const char* pIdSpec, void* pIdValue, const char* pIdDesc,
                                     const char* pDefSpec, void* pDefValue, const char* pDefName,
                                     const char* pGroupSpec, void* pGroupValue, const char* pGroupName,
                                     const char* pPosSpec, void* pPosValue, const char* pPosName,
                                     const char* pOrientSpec, void* pOrientValue, const char* pOrientName,
                                     int32_t nTerm);        // 0x0083bcd0

// ArgScript: parsed argument list.
struct cArguments {
    uint8_t mPad00[0x40];                                   // +0x00 .. +0x3f

    void  Init();                                           // 0x00837ff0
    void  Done();                                           // 0x00837fa0
    void  SplitIntoArguments(const wchar_t* pText);         // 0x008383c0
    void* MainArguments(int32_t nMin);                      // 0x00838320
    void* MainArguments(void** ppOut, int32_t nA, int32_t nB);   // 0x00838020
};

// ArgScript: base of every meta command.
struct cMetaCommandBase {
    void* mpVTable;                                         // +0x00
    uint8_t mPad004[0x0c];                                  // +0x04 .. +0x0f

    void Init();                                            // 0x0083c840
    void Done();                                            // 0x0083c7c0
};

// ArgScript: the script parser created by CreateParser().
struct cParser {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04
    virtual void  v008();                                   // +0x08
    virtual void  v00c();                                   // +0x0c
    virtual void  v010();                                   // +0x10
    virtual void* v014(void* pKey, void* pValue);           // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void* v038();                                   // +0x38
    virtual void  v03c(void* pArg);                         // +0x3c
    virtual void  v040();                                   // +0x40
    virtual void  v044();                                   // +0x44
    virtual void  v048();                                   // +0x48
    virtual void  v04c();                                   // +0x4c
    virtual void  v050();                                   // +0x50
    virtual void  v054();                                   // +0x54
    virtual void  v058();                                   // +0x58
    virtual void  v05c();                                   // +0x5c
    virtual void  v060();                                   // +0x60
    virtual void  v064();                                   // +0x64
    virtual void  v068();                                   // +0x68
    virtual void  v06c();                                   // +0x6c
    virtual void  v070();                                   // +0x70
    virtual void  v074();                                   // +0x74
    virtual void  v078();                                   // +0x78
    virtual void  v07c();                                   // +0x7c
    virtual void  v080();                                   // +0x80
    virtual void  v084();                                   // +0x84
    virtual void  v088();                                   // +0x88
    virtual void  v08c();                                   // +0x8c
    virtual void* v090(const void* pArg, const char* pText);   // +0x90
    virtual bool  v094(const wchar_t* pArg);                // +0x94
    virtual float v098(const wchar_t* pArg);                // +0x98
    virtual void* v09c(const wchar_t* pArg);                // +0x9c
    virtual void  v0a0();                                   // +0xa0
    virtual void  v0a4();                                   // +0xa4
    virtual void* v0a8(void* pOut, const void* pArg);       // +0xa8
    virtual void* v0ac(void* pOut, const void* pArg);       // +0xac
    virtual void  v0b0();                                   // +0xb0
    virtual void  v0b4();                                   // +0xb4
    virtual void  v0b8();                                   // +0xb8
    virtual void  v0bc(const wchar_t* pName);               // +0xbc
    virtual void  v0c0();                                   // +0xc0
    virtual void* v0c4();                                   // +0xc4
};

// Camera controller returned by GetCameraCtl().
struct cCameraCtl {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04
    virtual void  v008();                                   // +0x08
    virtual void  v00c();                                   // +0x0c
    virtual void  v010();                                   // +0x10
    virtual void  v014();                                   // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void  v038();                                   // +0x38

    void  GetForward(cVec3* pForward);                      // 0x00b13a10
    void  BlendTo(const void* pBlend, int32_t nFlag);       // 0x00b12dd0
    void  LookAt(float x, float y, float z);                // 0x00b10760
};

// Noun list returned by cGameNounManager::GetGameDataVector.
struct cNounList {
    uint8_t mPad00[0x04];                                   // +0x00 .. +0x03
    cNoun** mpBegin;                                        // +0x04
    cNoun** mpEnd;                                          // +0x08
};

// Local-object manager (CurMgr) used to look up ids.
struct cCurMgr {
    bool FindLocal(uint32_t nID);                           // 0x00801bb0
};

// Terraforming manager driven by the preview mode.
struct cTerraformingManager {
    void SetMode(int32_t nMode);                            // 0x00bc08d0
};

// Planet model used to project marker positions onto the planet surface.
struct cPlanetModel {
    static cPlanetModel* FromVector(void* pOut, const void* pDir);   // 0x00b3d350
    void* BuildSurfaceOrientation();                        // 0x00b7f190
    void* DirectionToSurfacePosition();                     // 0x00b815a0
};

// Entry of the type-name table used by ParseTypeEnum.
struct cTypeEntry {
    const char* mpName;                                     // +0x00
    void*       mpValue;                                    // +0x04
};

// ---------------------------------------------------------------------------
// helpers (external)
// ---------------------------------------------------------------------------

void* __cdecl operator_new(uint32_t nSize, const char* pFile, int32_t a, int32_t b,
                           const char* pAlloc, int32_t nLine);      // 0x00f473a0
void  __cdecl operator_delete_array(void* pBlock);          // 0x00f47380
void* __cdecl FNVHash(const char* pText, uint32_t nHash, int32_t nSome);   // 0x00932e80
extern "C" __declspec(dllimport) int __cdecl ascii_stricmp(const char* pA, const char* pB);  // msvcr90!_stricmp
extern "C" __declspec(dllimport) uint32_t __cdecl wide_to_ulong(const wchar_t* pText, wchar_t** ppEnd, int32_t nBase);   // msvcr90!wcstoul
extern "C" __declspec(dllimport) int __cdecl wide_compare(const wchar_t* pA, const wchar_t* pB);  // msvcr90!wcscmp
extern "C" __declspec(dllimport) float __cdecl sqrtf(float fValue);   // msvcr90!sqrtf
extern "C" __declspec(dllimport) double __cdecl wide_to_double(const wchar_t* pText, wchar_t** ppEnd);   // msvcr90!wcstod

cGameNounManager* __stdcall SP_NounManager(cNoun* pNoun);   // 0x00b3d300 (noun-taking form)
cGameNounManager* __cdecl SP_GetNounManager();              // 0x00b3d300 (global form)
cCameraCtl* __cdecl GetCameraCtl();                         // 0x00b3d280
void* __cdecl SP_GetGameTerrainCursor();                    // 0x00b30d70
void* __cdecl SP_TerraformingManager();                     // 0x00b3d430
void* __cdecl SP_CheatManager();                            // 0x0067de20
void* __cdecl SP_ResourceManager();                         // 0x0067dcd0
int32_t __cdecl SP_OpenRecordAsStream(const void* pKey, int32_t* pOut);   // 0x00686490
void  __cdecl SP_EraseEntry(int32_t nRecord);               // 0x006861d0
void* __cdecl ArgScript_CreateParser();                     // 0x008408d0
int32_t __cdecl FUN_00b99530(int32_t nA, int32_t nB, int32_t nC);   // 0x00b99530
void   __cdecl FUN_00ba1280();                              // 0x00ba1280
void*  __cdecl FUN_0067cab0();                               // 0x0067cab0
void   __cdecl FUN_0083b9d0(void* pA, void* pB);            // 0x0083b9d0
void   __stdcall FUN_010829f0(void* pArg);                  // 0x010829f0

extern cTypeEntry gTypeTable[];                             // 0x015825e8
extern cVec3      gDefaultPosition;                         // 0x0169d620
extern cVec4      gDefaultOrientation;                      // 0x0169d62c
extern const char* kCommandName;                            // 0x015825e0
extern const char* kTemplateName;                           // 0x015825e4

// ---------------------------------------------------------------------------
// the command object
// ---------------------------------------------------------------------------

struct cCommandGameplayMarker {
    void*          mpVTable;                                // +0x000
    cParser*       mpParser;                                // +0x004
    uint8_t        mPad008[0x08];                           // +0x008 .. +0x00f
    cArgumentSpec  mArgSpec;                                // +0x010
    cArguments     mArguments;                              // +0x0d8
    int32_t        mValueCount;                             // +0x118
    int32_t        mType;                                   // +0x11c
    int32_t        mID;                                     // +0x120
    int32_t        mDefinitionID;                           // +0x124
    int32_t        mGroupID;                                // +0x128
    cVec3          mPosition;                               // +0x12c
    cVec4          mOrientation;                            // +0x138
    cNoun*         mpGameplayMarker;                        // +0x148

    void* Init();                                           // 0x00d14e50
    void* Destroy(uint8_t nFlags);                          // 0x00d14f00
    const char* Description(int32_t nFlags);                // 0x00d14460
    void  SetFromArguments(cArguments* pArguments);         // 0x00d144d0
    void  OnEndParse(bool bCommit);                         // 0x00d14650
    void  SpawnMarker(cArguments* pArguments);              // 0x00d14830

    static void* ParseTypeEnum(const char* pName);          // 0x00d14600
};

struct cCommandGameplayMarkerTemplate : cCommandGameplayMarker {
    cVec3  mAlphaVector;                                    // +0x14c
    cVec3  mBetaVector;                                     // +0x158
    float  mAlpha;                                          // +0x164
    float  mBeta;                                           // +0x168

    void* Init(const cVec3* pAlpha, const cVec3* pBeta);    // 0x00d14f70
    bool  Parse(const wchar_t** ppArguments);               // 0x00d14690
    void  UpdateMarker(cArguments* pArguments);             // 0x00d14a60
};

// ---------------------------------------------------------------------------
// 0x00d14460 : help text of the command
// ---------------------------------------------------------------------------
// @ 0x00d14460
const char* cCommandGameplayMarker::Description(int32_t nFlags)
{
    return mArgSpec.HelpString(kCommandName, nFlags);
}

// ---------------------------------------------------------------------------
// 0x00d144d0 : build the marker transform from the parsed arguments
// ---------------------------------------------------------------------------
// @ 0x00d144d0
void cCommandGameplayMarker::SetFromArguments(cArguments* pArguments)
{
    void** pArgs = (void**)pArguments->MainArguments(3);
    cCameraCtl* pCamera = GetCameraCtl();
    if (!pCamera)
        return;

    cVec3 vBuffer;
    cVec3 vPosition = *(cVec3*)mpParser->v0a8(&vBuffer, pArgs[0]);
    (void)vPosition;

    cVec4 vOrientation;
    cVec4* pOrientation = (cVec4*)mpParser->v0ac(&vOrientation, pArgs[1]);
    float fBlend[4] = { pOrientation->x, pOrientation->y,
                        pOrientation->z, pOrientation->w };
    pCamera->BlendTo(fBlend, 1);

    cVec3 vLookAt = *(cVec3*)mpParser->v0a8(&vBuffer, pArgs[2]);
    pCamera->LookAt(vLookAt.x, vLookAt.y, vLookAt.z);
}

// ---------------------------------------------------------------------------
// 0x00d14600 : map a type name to its enum value
// ---------------------------------------------------------------------------
// @ 0x00d14600
void* cCommandGameplayMarker::ParseTypeEnum(const char* pName)
{
    const cTypeEntry* pEntry = gTypeTable;
    while (pEntry->mpName) {
        if (ascii_stricmp(pName, pEntry->mpName) == 0)
            return pEntry->mpValue;
        ++pEntry;
    }
    return FNVHash(pName, 0x811c9dc5, 1);
}

// ---------------------------------------------------------------------------
// 0x00d14650 : release the marker noun once parsing finished
// ---------------------------------------------------------------------------
// @ 0x00d14650
void cCommandGameplayMarker::OnEndParse(bool bCommit)
{
    if (bCommit)
        SP_NounManager(mpGameplayMarker)->RemoveNoun();

    if (cNoun* pOld = mpGameplayMarker) {
        mpGameplayMarker = 0;
        pOld->v004();
    }
}

// ---------------------------------------------------------------------------
// 0x00d14690 : parse one argument of the template command
// ---------------------------------------------------------------------------
// @ 0x00d14690
bool cCommandGameplayMarkerTemplate::Parse(const wchar_t** ppArguments)
{
    if ((uint32_t)mpGameplayMarker->mValueCount >= 0x20)
        return false;

    mArguments.SplitIntoArguments(*ppArguments);
    void* pUnused = 0;
    const wchar_t** pArgs = (const wchar_t**)mArguments.MainArguments(&pUnused, 2, 2);

    if (ascii_stricmp((const char*)pArgs[0], "triggerSourceFromDefinition") == 0) {
        mpParser->v094(pArgs[1]);
        return true;
    }
    if (ascii_stricmp((const char*)pArgs[0], "trigger") == 0) {
        mpParser->v09c(pArgs[1]);
        return true;
    }

    uint32_t nType = (uint32_t)ParseTypeEnum((const char*)pArgs[0]);
    cNoun* pMarker = mpGameplayMarker;
    switch (nType) {
    case 1: {
        bool bValue = mpParser->v094(pArgs[1]);
        pMarker->mValues[pMarker->mValueCount] = bValue ? 1 : 0;
        ++pMarker->mValueCount;
        return true;
    }
    case 9: {
        int32_t nValue = (int32_t)mpParser->v09c(pArgs[1]);
        pMarker->mValues[pMarker->mValueCount] = nValue;
        ++pMarker->mValueCount;
        return true;
    }
    case 13: {
        float fValue = mpParser->v098(pArgs[1]);
        *(float*)&pMarker->mValues[pMarker->mValueCount] = fValue;
        ++pMarker->mValueCount;
        return true;
    }
    default: {
        pMarker->mValues[pMarker->mValueCount] = (int32_t)mpParser->v09c(pArgs[1]);
        ++pMarker->mValueCount;
        return true;
    }
    }
}

// ---------------------------------------------------------------------------
// 0x00d14830 : create the gameplay marker noun from the command values
// ---------------------------------------------------------------------------
// @ 0x00d14830
void cCommandGameplayMarker::SpawnMarker(cArguments* pArguments)
{
    mpParser->v090(this, "end");

    mPosition = gDefaultPosition;
    mOrientation = gDefaultOrientation;
    mType = 0;
    mID = 0;
    mDefinitionID = 0;
    mGroupID = 0;

    mArgSpec.Parse(pArguments, mpParser);

    cNoun* pNoun = (cNoun*)SP_GetNounManager()->CreateNoun(0x036be27e);
    if (pNoun)
        pNoun = (cNoun*)pNoun->v00c(0x036be278);

    if (pNoun != mpGameplayMarker) {
        if (pNoun)
            pNoun->v000();
        mpGameplayMarker = pNoun;
        if (pNoun)
            pNoun->v004();
    }

    cNoun* pMarker = mpGameplayMarker;
    pMarker->mDefA = mType;
    pMarker->mDefB = mID;
    pMarker->mDefC = mDefinitionID;
    pMarker->mDefD = mGroupID;

    if (mPosition.x != gDefaultPosition.x ||
        mPosition.y != gDefaultPosition.y ||
        mPosition.z != gDefaultPosition.z)
        pMarker->mSpatial.SetPosition(&mPosition);

    if (mOrientation.x != gDefaultOrientation.x ||
        mOrientation.y != gDefaultOrientation.y ||
        mOrientation.z != gDefaultOrientation.z ||
        mOrientation.w != gDefaultOrientation.w)
        pMarker->mSpatial.SetOrientation(&mOrientation);
}

// ---------------------------------------------------------------------------
// 0x00d14a60 : refresh the marker noun from the command values
// ---------------------------------------------------------------------------
// @ 0x00d14a60
void cCommandGameplayMarkerTemplate::UpdateMarker(cArguments* pArguments)
{
    mpParser->v090(this, "end");

    mPosition = gDefaultPosition;
    mOrientation = gDefaultOrientation;
    mType = 0;
    mID = 0;
    mDefinitionID = 0;
    mGroupID = 0;
    mAlpha = 0.0f;
    mBeta = 0.0f;

    mArgSpec.Parse(pArguments, mpParser);

    cNoun* pNoun = (cNoun*)SP_GetNounManager()->CreateNoun(0x036be27e);
    if (pNoun)
        pNoun = (cNoun*)pNoun->v00c(0x036be278);

    if (pNoun != mpGameplayMarker) {
        if (pNoun)
            pNoun->v000();
        mpGameplayMarker = pNoun;
        if (pNoun)
            pNoun->v004();
    }

    cNoun* pMarker = mpGameplayMarker;
    pMarker->mDefA = mType;
    pMarker->mDefB = mID;
    pMarker->mDefC = mDefinitionID;
    pMarker->mDefD = mGroupID;

    if (mAlpha > 0.0f && mAlpha < 1.52587890625e-05f &&
        mBeta > 0.0f && mBeta < 1.52587890625e-05f) {
        pMarker->mSpatial.SetPosition(&mAlphaVector);
        cVec3 vSurface;
        cPlanetModel* pModel = cPlanetModel::FromVector(&vSurface, &mAlphaVector);
        pMarker->mSpatial.SetOrientation(pModel->BuildSurfaceOrientation());
        return;
    }

    cVec3 vAlpha = mAlphaVector;
    float fAlphaLength = 1.0f / sqrtf(vAlpha.x * vAlpha.x + vAlpha.y * vAlpha.y +
                                       vAlpha.z * vAlpha.z + 1e-08f);
    vAlpha.x *= fAlphaLength;
    vAlpha.y *= fAlphaLength;
    vAlpha.z *= fAlphaLength;

    float fDot = mBetaVector.x * vAlpha.x + mBetaVector.y * vAlpha.y +
                 mBetaVector.z * vAlpha.z;
    cVec3 vBeta;
    vBeta.x = mBetaVector.x - vAlpha.x * fDot;
    vBeta.y = mBetaVector.y - vAlpha.y * fDot;
    vBeta.z = mBetaVector.z - vAlpha.z * fDot;

    float fBetaLength = 1.0f / sqrtf(vBeta.x * vBeta.x + vBeta.y * vBeta.y +
                                     vBeta.z * vBeta.z + 1e-08f);
    vBeta.x *= fBetaLength;
    vBeta.y *= fBetaLength;
    vBeta.z *= fBetaLength;

    cVec3 vPosition;
    vPosition.x = mAlphaVector.x + mAlpha * (vBeta.y * vAlpha.z - vBeta.z * vAlpha.y) +
                  mBeta * vBeta.x;
    vPosition.y = mAlphaVector.y + mAlpha * (vBeta.z * vAlpha.x - vBeta.x * vAlpha.z) +
                  mBeta * vBeta.y;
    vPosition.z = mAlphaVector.z + mAlpha * (vAlpha.y * vBeta.x - vBeta.y * vAlpha.x) +
                  mBeta * vBeta.z;

    cVec3 vSurface;
    cPlanetModel* pModel = cPlanetModel::FromVector(&vSurface, &vPosition);
    pMarker->mSpatial.SetPosition(pModel->DirectionToSurfacePosition());

    cVec3 vOrientation;
    cPlanetModel* pOrientModel =
        cPlanetModel::FromVector(&vOrientation, pMarker->mSpatial.GetPosition());
    pMarker->mSpatial.SetOrientation(pOrientModel->BuildSurfaceOrientation());
}

// ---------------------------------------------------------------------------
// 0x00d14e50 : construct the command
// ---------------------------------------------------------------------------
// @ 0x00d14e50
void* cCommandGameplayMarker::Init()
{
    ((cMetaCommandBase*)this)->Init();
    mpVTable = (void*)0x014799b0;
    mArgSpec.Init(true);
    mArguments.Init();
    mpGameplayMarker = 0;
    ArgScript_ConstructSpec(&mArgSpec, "Creates a gameplay marker",
                            "<type:int>", &mType, "type",
                            "<id:int>", &mID, (const char*)0x013fc890,
                            "<definitionId:int>", &mDefinitionID, "definitionId",
                            "<group:int>", &mGroupID, "group id",
                            "[position:vector3]", &mPosition, "position",
                            "[orientation:vector4]", &mOrientation, "orientation",
                            0);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00d14f00 : destroy the command
// ---------------------------------------------------------------------------
// @ 0x00d14f00
void* cCommandGameplayMarker::Destroy(uint8_t nFlags)
{
    mpVTable = (void*)0x014799b0;
    if (cNoun* pMarker = mpGameplayMarker)
        pMarker->v004();
    mArguments.Done();
    mArgSpec.Done();
    ((cMetaCommandBase*)this)->Done();
    if (nFlags & 1)
        operator_delete_array(this);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00d14f70 : construct the template command
// ---------------------------------------------------------------------------
// @ 0x00d14f70
void* cCommandGameplayMarkerTemplate::Init(const cVec3* pAlpha, const cVec3* pBeta)
{
    cCommandGameplayMarker::Init();
    mpVTable = (void*)0x01479a6c;
    mAlphaVector.x = pAlpha->x;
    mAlphaVector.y = pAlpha->y;
    mAlphaVector.z = pAlpha->z;
    mBetaVector.x = pBeta->x;
    mBetaVector.y = pBeta->y;
    mBetaVector.z = pBeta->z;
    ArgScript_ConstructSpec(&mArgSpec, "Creates a gameplay marker",
                            "<type:int>", &mType, "type",
                            "<id:int>", &mID, (const char*)0x013fc890,
                            "<definitionId:int>", &mDefinitionID, "definitionId",
                            "<group:int>", &mGroupID, "group id",
                            "<alpha:float>", &mAlpha, "alpha",
                            "<beta:float>", &mBeta, (const char*)0x01479aac,
                            0);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00d15090 : notify the gameplay systems of a new marker
// ---------------------------------------------------------------------------
// @ 0x00d15090
void __stdcall FUN_00d15090(void* pArg)
{
    FUN_010829f0(pArg);
    if (*(void**)0x0168d248) {
        cGameNounManager* pManager = SP_GetNounManager();
        cNounList* pList = (cNounList*)pManager->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                                   (void*)0x00acdff0, (void*)0x00b1e500,
                                                                   (void*)0x018c43e8);
        int32_t nCount = (int32_t)(pList->mpEnd - pList->mpBegin);
        cNoun*** pppBegin = &pList->mpBegin;
        for (int32_t i = 0; i < nCount; ++i)
            (*pppBegin)[i]->v078();
    }
}

// ---------------------------------------------------------------------------
// 0x00d15100 : leave the terraforming preview mode
// ---------------------------------------------------------------------------
// @ 0x00d15100
void __stdcall FUN_00d15100(int32_t nA, int32_t nB)
{
    (void)nA;
    (void)nB;
    if (*(uint8_t*)0x0169dc20) {
        *(uint8_t*)0x0169dc20 = 0;
        cTerraformingManager* pManager = (cTerraformingManager*)SP_TerraformingManager();
        if (pManager)
            pManager->SetMode(1);
    }
}

// ---------------------------------------------------------------------------
// 0x00d15160 : register the gameplay marker template with the script parser
// ---------------------------------------------------------------------------
// @ 0x00d15160
void __stdcall FUN_00d15160(const cVec3* pAlpha, int32_t nUnused)
{
    (void)nUnused;
    cCameraCtl* pCamera = GetCameraCtl();
    if (!pCamera)
        return;

    cVec3 vForward;
    pCamera->GetForward(&vForward);
    if (!SP_ResourceManager())
        return;

    int32_t nHandle = 0;
    struct StreamRequest {
        const cVec3* mpSeed;                                // +0x00
        uint32_t     mGroupID;                              // +0x04
        uint32_t     mTypeID;                               // +0x08
    } request;
    request.mpSeed = pAlpha;
    request.mGroupID = 0xf2b924b3;
    request.mTypeID = 0x72b924b5;
    int32_t nRecord = SP_OpenRecordAsStream(&request, &nHandle);

    if (nRecord != -1) {
        cParser* pParser = (cParser*)ArgScript_CreateParser();
        pParser->v008();
        cCommandGameplayMarkerTemplate* pTemplate =
            (cCommandGameplayMarkerTemplate*)operator_new(0x16c, "App/cCommandGameplayMarkerTemplate",
                                                         0, 0, 0, 0);
        if (pTemplate)
            pTemplate->Init(pAlpha, &vForward);
        else
            pTemplate = 0;
        pParser->v014((void*)kTemplateName, pTemplate);
        cParser* pCheat = (cParser*)SP_CheatManager();
        cParser* pWindow = (cParser*)pCheat->v038();
        pParser->v0bc((const wchar_t*)pWindow->v0c4());
        pParser->v03c(&nHandle);
        SP_EraseEntry(nRecord);
    }

    FUN_00b99530(1, 0, 0);
    FUN_00ba1280();
}

// ---------------------------------------------------------------------------
// 0x00d15280 : prepare the terrain cursor for placing a marker
// ---------------------------------------------------------------------------
// @ 0x00d15280
bool __stdcall FUN_00d15280(int32_t nA, int32_t nFlags, int32_t nC)
{
    (void)nA;
    (void)nC;
    ((cTerrainCursor*)SP_GetGameTerrainCursor())->t0b8(0);
    ((cTerrainCursor*)SP_GetGameTerrainCursor())->t0a4();
    ((cTerrainCursor*)SP_GetGameTerrainCursor())->t0ac(1.0f);
    ((cTerrainCursor*)SP_GetGameTerrainCursor())->t0b0(1.0f);

    cCurMgr* pManager = (cCurMgr*)FUN_0067cab0();
    pManager->FindLocal(0x1002);

    if (nFlags & 1)
        ((cTerrainCursor*)SP_GetGameTerrainCursor())->t064();
    ((cTerrainCursor*)SP_GetGameTerrainCursor())->t074();
    int32_t nZero = 0;
    return ((cTerrainCursor*)SP_GetGameTerrainCursor())->t070() == nZero;
}

// ---------------------------------------------------------------------------
// 0x00d15350 : store one parsed argument value into the marker noun
// ---------------------------------------------------------------------------
// @ 0x00d15350
void FUN_00d15350(cNoun* pNoun, int32_t nIndex, int32_t nType, const wchar_t* pValue)
{
    switch (nType) {
    case 1:
        pNoun->mValues[nIndex] = (wide_compare(pValue, L"true") == 0) ? 1 : 0;
        return;
    case 9:
        pNoun->mValues[nIndex] = (int32_t)wide_to_ulong(pValue, 0, 10);
        return;
    case 13: {
        wchar_t* pEnd;
        float fValue = (float)wide_to_double(pValue, &pEnd);
        *(float*)&pNoun->mValues[nIndex] = fValue;
        return;
    }
    default:
        pNoun->mValues[nIndex] = (int32_t)wide_to_ulong(pValue, 0, 10);
        return;
    }
}
