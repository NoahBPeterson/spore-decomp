// Slice s00c8fbb0 -- cTribe accessors: centre/political-centre lookup, chieftain/leader query and
// the helper that drops the tribe's attached noun.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

struct tVec3 {
    float mX;                                           // +0x00
    float mY;                                           // +0x04
    float mZ;                                           // +0x08
};

// Object that can report a world position (slot +0x2c).
class cPositionSource {
public:
    virtual void p000(); virtual void p004(); virtual void p008(); virtual void p00c();
    virtual void p010(); virtual void p014(); virtual void p018(); virtual void p01c();
    virtual void p020(); virtual void p024(); virtual void p028();
    virtual tVec3* GetPosition();                        // +0x2c
};

class cGameNounManager;

cGameNounManager* __cdecl NounManager();                 // 0x00b3d300

class cGameNounManager {
public:
    void RemoveNoun(void* pNoun);                        // 0x00b225d0
};

// Ref-counted noun handle: slot +0x04 releases the reference.
class cNounRef {
public:
    virtual void n00();
    virtual void Release();                              // +0x04
};

// Begin/end byte range of a pointer vector returned by cTribe::GetPointerList().
struct cPointerVector {
    char* mpBegin;                                       // +0x00
    char* mpEnd;                                         // +0x04
};

// File list of a community; only the count accessor is used here.
struct cFileList {
    int GetFileCount();                                  // 0x008e7f80
};

// Leader object: slot +0x0c resolves an interface by four-character id.
class cLeaderObject {
public:
    virtual void l00(); virtual void l04(); virtual void l08();
    virtual void* QueryInterface(uint32_t interfaceId);  // +0x0c
};

class cCommunity {
public:
    uint8_t         pad000[0x34];                        // +0x000 .. +0x033
    cPositionSource mPosition;                           // +0x034
    uint8_t         pad048[0xe8];                        // +0x048 .. +0x11f
    cFileList       mFileList;                           // +0x120
};

class cTribe {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054();
    virtual tVec3* GetPoliticalCenterOrCenter(tVec3* pOut); // +0x58
    virtual void v05c(); virtual void v060(); virtual void v064(); virtual void v068();
    virtual void v06c(); virtual void v070(); virtual void v074(); virtual void v078();
    virtual void v07c(); virtual void v080(); virtual void v084(); virtual void v088();
    virtual void v08c();
    virtual cPointerVector* GetPointerList();            // +0x90
    virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void ClearPointer(void* pEntry);             // +0xa0

    uint8_t         pad004[0x11c];                       // +0x004 .. +0x11f
    cPositionSource mPosition;                           // +0x120
    uint8_t         pad124[0x214];                       // +0x124 .. +0x337
    int32_t         mPointerCount;                       // +0x338
    bool            mPointersDirty;                      // +0x33c
    uint8_t         pad33d[3];                           // +0x33d .. +0x33f
    void**          mpPointerStackBegin;                 // +0x340
    void**          mpPointerStackEnd;                   // +0x344
    uint8_t         pad348[0x20];                        // +0x348 .. +0x367
    cCommunity*     mpCommunity;                         // +0x368
    uint8_t         pad36c[0x1664];                      // +0x36c .. +0x19cf
    cNounRef*       mpAttachedNoun;                      // +0x19d0

    void  UpdateRoboTribeness(float amount);
    tVec3* GetCenter(tVec3* pOut);
    tVec3* GetPoliticalCenter(tVec3* pOut);
    void* GetChieftain();
    void  PromoteChieftain(uint32_t civId);
    void  GetClosestWater(tVec3* pOut);
    void  InitDomesticatedAnimalsHerd(uint32_t speciesId);
    void  FUN_00c8fc50(bool flag);
    void  FUN_00c90470();
    bool  FUN_00c905a0();

    // Community queries reached through the tribe's shared base.
    void* GetLeader();                                   // 0x00c00650
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xc8fbb0 cTribe::UpdateRoboTribeness
void __thiscall cTribe::UpdateRoboTribeness(float amount)
{
    (void)amount;
}

// @ 0xc8fc50 cTribe::FUN_00c8fc50
void __thiscall cTribe::FUN_00c8fc50(bool flag)
{
    if (!flag && mPointersDirty) {
        cPointerVector* pList = GetPointerList();
        int32_t count = (int32_t)(pList->mpEnd - pList->mpBegin) >> 2;
        while (mpPointerStackBegin != mpPointerStackEnd) {
            ClearPointer(*(mpPointerStackEnd - 1));
        }
        mPointerCount = count;
    }
    mPointersDirty = flag;
}

// @ 0xc8fcc0 cTribe::GetCenter
tVec3* __thiscall cTribe::GetCenter(tVec3* pOut)
{
    tVec3* pPosition = mPosition.GetPosition();
    pOut->mX = pPosition->mX;
    pOut->mY = pPosition->mY;
    pOut->mZ = pPosition->mZ;
    return pOut;
}

// @ 0xc8fcf0 cTribe::GetPoliticalCenter
tVec3* __thiscall cTribe::GetPoliticalCenter(tVec3* pOut)
{
    if (mpCommunity) {
        cPositionSource* pSource = &mpCommunity->mPosition;
        tVec3* pPosition = pSource->GetPosition();
        pOut->mX = pPosition->mX;
        pOut->mY = pPosition->mY;
        pOut->mZ = pPosition->mZ;
        return pOut;
    }
    GetPoliticalCenterOrCenter(pOut);
    return pOut;
}

// @ 0xc8fd30 cTribe::GetChieftain
void* __thiscall cTribe::GetChieftain()
{
    cLeaderObject* pLeader = (cLeaderObject*)GetLeader();
    if (pLeader)
        return pLeader->QueryInterface(0x4f176642);
    return 0;
}

// @ 0xc8fd50 cTribe::PromoteChieftain
void __thiscall cTribe::PromoteChieftain(uint32_t civId)
{
    (void)civId;
}

// @ 0xc8fe20 cTribe::GetClosestWater
void __thiscall cTribe::GetClosestWater(tVec3* pOut)
{
    (void)pOut;
}

// @ 0xc8fef0 cTribe::InitDomesticatedAnimalsHerd
void __thiscall cTribe::InitDomesticatedAnimalsHerd(uint32_t speciesId)
{
    (void)speciesId;
}

// @ 0xc90470 FUN_00c90470
void __thiscall cTribe::FUN_00c90470()
{
    if (mpAttachedNoun) {
        NounManager()->RemoveNoun(mpAttachedNoun);
        cNounRef* pNoun = mpAttachedNoun;
        if (pNoun) {
            mpAttachedNoun = 0;
            pNoun->Release();
        }
    }
}

// @ 0xc904b0 FUN_00c904b0
void __fastcall FUN_00c904b0(cTribe* this_, int unused)
{
    (void)this_;
}

// @ 0xc905a0 FUN_00c905a0
bool __thiscall cTribe::FUN_00c905a0()
{
    return mpCommunity->mFileList.GetFileCount() == 2;
}

// @ 0xc905c0 FUN_00c905c0
void __fastcall FUN_00c905c0(cTribe* this_, int unused)
{
    (void)this_;
}

// @ 0xc908a0 FUN_00c908a0
void __fastcall FUN_00c908a0(cTribe* this_, int unused)
{
    (void)this_;
}

// @ 0xc90920 insertion_sort
void __cdecl insertion_sort(tVec3** pFirst, tVec3** pLast, void* pCompare)
{
    (void)pFirst; (void)pLast; (void)pCompare;
}

// @ 0xc90a40 insertion_sort
void __cdecl insertion_sort(tVec3** pFirst, tVec3** pLast)
{
    (void)pFirst; (void)pLast;
}

} // namespace SP
