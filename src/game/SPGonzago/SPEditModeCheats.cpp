// src/game/SPGonzago/SPEditModeCheats.cpp -- migrated from slice(s) s00d14460 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPEditModeCheats.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl ascii_stricmp(const char* pA, const char* pB);  // msvcr90!_stricmp
extern "C" __declspec(dllimport) float __cdecl sqrtf(float fValue);   // msvcr90!sqrtf
extern const char* kCommandName;                            // 0x015825e0
#include <stddef.h>

// ---- items of slice s00d14460 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct cGameNounManager {
    void* mpVTable;                                         // +0x00
    uint8_t mPad004[0x34];                                  // +0x04 .. +0x37
    void* GetGameDataVector(void* pA, void* pB, void* pC, void* pD, void* pE);   // 0x00b21340
    void  RemoveNoun();                                     // 0x00b225d0
    void* CreateNoun(uint32_t nType);                       // 0x00b22640
};
struct cParser;
struct cArguments;
struct cArgumentSpec {
    uint8_t mPad00[0xc8];                                   // +0x00 .. +0xc7

    void  Init(bool bFlag);                                 // 0x0083a9f0
    void  Parse(cArguments* pArguments, cParser* pParser);   // 0x0083b9d0
    void  Done();                                           // 0x00405050
    const char* HelpString(const char* pName, int32_t nFlags);   // 0x0083a2f0
};
void __cdecl ArgScript_ConstructSpec(cArgumentSpec* pSpec, const char* pComment,
                                     const char* pTypeSpec, void* pTypeValue, const char* pTypeName,
                                     const char* pIdSpec, void* pIdValue, const char* pIdDesc,
                                     const char* pDefSpec, void* pDefValue, const char* pDefName,
                                     const char* pGroupSpec, void* pGroupValue, const char* pGroupName,
                                     const char* pPosSpec, void* pPosValue, const char* pPosName,
                                     const char* pOrientSpec, void* pOrientValue, const char* pOrientName,
                                     int32_t nTerm);        // 0x0083bcd0
struct cArguments {
    uint8_t mPad00[0x40];                                   // +0x00 .. +0x3f

    void  Init();                                           // 0x00837ff0
    void  Done();                                           // 0x00837fa0
    void  SplitIntoArguments(const wchar_t* pText);         // 0x008383c0
    void* MainArguments(int32_t nMin);                      // 0x00838320
    void* MainArguments(void** ppOut, int32_t nA, int32_t nB);   // 0x00838020
};
struct cMetaCommandBase {
    void* mpVTable;                                         // +0x00
    uint8_t mPad004[0x0c];                                  // +0x04 .. +0x0f

    void Init();                                            // 0x0083c840
    void Done();                                            // 0x0083c7c0
};
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
struct cPlanetModel {
    static cPlanetModel* FromVector(void* pOut, const void* pDir);   // 0x00b3d350
    void* BuildSurfaceOrientation();                        // 0x00b7f190
    void* DirectionToSurfacePosition();                     // 0x00b815a0
};
struct cTypeEntry {
    const char* mpName;                                     // +0x00
    void*       mpValue;                                    // +0x04
};
void* __cdecl FNVHash(const char* pText, uint32_t nHash, int32_t nSome);   // 0x00932e80
extern "C" __declspec(dllimport) int __cdecl ascii_stricmp(const char* pA, const char* pB);  // msvcr90!_stricmp
extern "C" __declspec(dllimport) float __cdecl sqrtf(float fValue);   // msvcr90!sqrtf
cGameNounManager* __cdecl SP_GetNounManager();              // 0x00b3d300 (global form)
cCameraCtl* __cdecl GetCameraCtl();                         // 0x00b3d280
extern cTypeEntry gTypeTable[];                             // 0x015825e8
extern cVec3      gDefaultPosition;                         // 0x0169d620
extern cVec4      gDefaultOrientation;                      // 0x0169d62c
extern const char* kCommandName;                            // 0x015825e0
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
// ---- items of slice s00d14460 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cTypeEntry gTypeTable[];                             // 0x015825e8
extern cVec3      gDefaultPosition;                         // 0x0169d620
extern cVec4      gDefaultOrientation;                      // 0x0169d62c

// @ 0x00d14460
const char* cCommandGameplayMarker::Description(int32_t nFlags)
{
    return mArgSpec.HelpString(kCommandName, nFlags);
}

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
