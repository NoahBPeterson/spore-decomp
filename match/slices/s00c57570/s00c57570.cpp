// Slice s00c57570 -- multi-delivery mission: element assignment, the two range-walk passes over the
// buyer/item vectors and the fetch-item name accessor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace eastl {

class wstring {
public:
    void assign(const wchar_t* pFirst, const wchar_t* pLast); // 0x00423650
};

} // namespace eastl

namespace SP {

// Ref-counted mission payload carried by the delivery entries.
class cMissionTarget {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018();
    virtual void NotifyContext(void* pContext);          // +0x1c
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8();
    virtual void NotifyAssigned();                       // +0xbc
    virtual void ReleaseTarget();                        // +0xc0
};

// One buyer entry (12 bytes): payload pointer plus two dwords.
struct tBuyerInfo {
    cMissionTarget* mpTarget;                            // +0x00
    int32_t         mField4;                             // +0x04
    int32_t         mField8;                             // +0x08

    tBuyerInfo* operator=(const tBuyerInfo& src);
};

// One item entry (20 bytes): payload pointer, three floats and a flag.
struct tItemInfo {
    cMissionTarget* mpTarget;                            // +0x00
    float           mField4;                             // +0x04
    float           mField8;                             // +0x08
    float           mFieldC;                             // +0x0c
    bool            mField10;                            // +0x10

    tItemInfo* operator=(const tItemInfo& src);
    tItemInfo* FUN_00c57a80(cMissionTarget* pTarget, bool flag, float f1, float f2, float f3);
};

struct cBuyerRange {
    tBuyerInfo* mpBegin;                                 // +0x00
    tBuyerInfo* mpEnd;                                   // +0x04
};

struct cItemRange {
    tItemInfo*  mpBegin;                                 // +0x00
    tItemInfo*  mpEnd;                                   // +0x04
};

// Localised text slot; GetText returns the unterminated wide buffer.
class cString_s006b_47a0 {
public:
    const wchar_t* GetText();                            // 0x006b55c0
};

class cSPMissionMultiDelivery {
public:
    void  GetDynamicResponseID();
    void  OnDelivery();
    void  GetFetchItemName(eastl::wstring* pOut);
    void  FUN_00c575e0();
    void  FUN_00c576d0();
    void  FUN_00c57720();
    void  FUN_00c57780();
    void  FUN_00c57810();
    void  FUN_00c57930();
    void  FUN_00c57a10();
    void  FUN_00c57a80();
    void  FUN_00c57ad0();
    void  FUN_00c57e50();
    void  FUN_00c582a0();
    void  FUN_00c58310();
    void  FUN_00c58360();
    void  FUN_00c58530();
    void  FUN_00c58600();

    uint8_t             pad000[0x23c];                   // +0x000 .. +0x23b
    cString_s006b_47a0  mFetchItemName;                  // +0x23c
};

} // namespace SP

using namespace SP;

// @ 0xc57570 SP::WriteSTLSequence
void __cdecl WriteSTLSequence_tItemInfo(void* pWriter, cItemRange* pRange)
{
    (void)pWriter;
    (void)pRange;
}

namespace SP {

// @ 0xc575e0 SP::cSPMissionMultiDelivery::FUN_00c575e0
void __thiscall cSPMissionMultiDelivery::FUN_00c575e0()
{
}

// @ 0xc57690 SP::tItemInfo::operator=
tItemInfo* __thiscall tItemInfo::operator=(const tItemInfo& src)
{
    mpTarget = src.mpTarget;
    if (mpTarget)
        mpTarget->NotifyAssigned();
    mField4 = src.mField4;
    mField8 = src.mField8;
    mFieldC = src.mFieldC;
    mField10 = src.mField10;
    return this;
}

// @ 0xc576d0 SP::tBuyerInfo::operator=
tBuyerInfo* __thiscall tBuyerInfo::operator=(const tBuyerInfo& src)
{
    cMissionTarget* pOld = mpTarget;
    cMissionTarget* pNew = src.mpTarget;
    if (pNew != pOld) {
        if (pNew)
            pNew->NotifyAssigned();
        mpTarget = pNew;
        if (pOld)
            pOld->ReleaseTarget();
    }
    mField4 = src.mField4;
    mField8 = src.mField8;
    return this;
}

// @ 0xc57720 SP::cSPMissionMultiDelivery::FUN_00c57720
void __thiscall cSPMissionMultiDelivery::FUN_00c57720()
{
}

// @ 0xc57780 SP::cSPMissionMultiDelivery::FUN_00c57780
void __thiscall cSPMissionMultiDelivery::FUN_00c57780()
{
}

// @ 0xc57810 SP::cSPMissionMultiDelivery::FUN_00c57810
void __thiscall cSPMissionMultiDelivery::FUN_00c57810()
{
}

// @ 0xc578c0 SP::copy_impl_buyer
void __cdecl copy_impl_buyer(tBuyerInfo* pDest, tBuyerInfo* pFirst, tBuyerInfo* pLast)
{
    (void)pDest;
    (void)pFirst;
    (void)pLast;
}

// @ 0xc57930 SP::cSPMissionMultiDelivery::FUN_00c57930
void __thiscall cSPMissionMultiDelivery::FUN_00c57930()
{
}

// @ 0xc579a0 SP::copy_impl_item
void __cdecl copy_impl_item(tItemInfo* pDest, tItemInfo* pFirst, tItemInfo* pLast)
{
    (void)pDest;
    (void)pFirst;
    (void)pLast;
}

// @ 0xc57a10 SP::cSPMissionMultiDelivery::FUN_00c57a10
void __thiscall cSPMissionMultiDelivery::FUN_00c57a10()
{
}

// @ 0xc57a80 SP::tItemInfo::FUN_00c57a80
tItemInfo* __thiscall tItemInfo::FUN_00c57a80(cMissionTarget* pTarget, bool flag,
                                              float f1, float f2, float f3)
{
    mpTarget = 0;
    if (pTarget) {
        pTarget->NotifyAssigned();
        mpTarget = pTarget;
    }
    mField10 = flag;
    mField4 = f1;
    mField8 = f2;
    mFieldC = f3;
    return this;
}

// @ 0xc57ad0 SP::cSPMissionMultiDelivery::FUN_00c57ad0
void __thiscall cSPMissionMultiDelivery::FUN_00c57ad0()
{
}

// @ 0xc57d00 SP::cSPMissionMultiDelivery::GetDynamicResponseID
void __thiscall cSPMissionMultiDelivery::GetDynamicResponseID()
{
}

// @ 0xc57e50 SP::cSPMissionMultiDelivery::FUN_00c57e50
void __thiscall cSPMissionMultiDelivery::FUN_00c57e50()
{
}

// @ 0xc57ef0 SP::cSPMissionMultiDelivery::OnDelivery
void __thiscall cSPMissionMultiDelivery::OnDelivery()
{
}

// @ 0xc58070 SP::FUN_00c58070
bool __cdecl FUN_00c58070(void* pContext, cBuyerRange* pRange)
{
    tBuyerInfo* pEnd = pRange->mpEnd;
    for (tBuyerInfo* p = pRange->mpBegin; p != pEnd; ++p) {
        if (p) {
            cMissionTarget* pTarget = p->mpTarget;
            if (pTarget)
                pTarget->NotifyContext(pContext);
        }
    }
    return true;
}

// @ 0xc580b0 SP::FUN_00c580b0
bool __cdecl FUN_00c580b0(void* pContext, cItemRange* pRange)
{
    tItemInfo* pEnd = pRange->mpEnd;
    for (tItemInfo* p = pRange->mpBegin; p != pEnd; ++p) {
        if (p) {
            cMissionTarget* pTarget = p->mpTarget;
            if (pTarget)
                pTarget->NotifyContext(pContext);
        }
    }
    return true;
}

// @ 0xc58170 Simulator::cMissionMultiDelivery::cMissionMultiDelivery
void __fastcall cMissionMultiDeliveryCtor(void* this_, int unused)
{
    (void)this_;
}

// @ 0xc58260 SP::cSPMissionMultiDelivery::GetFetchItemName
void __thiscall cSPMissionMultiDelivery::GetFetchItemName(eastl::wstring* pOut)
{
    const wchar_t* pText = mFetchItemName.GetText();
    const wchar_t* pEnd = pText;
    while (*pEnd)
        ++pEnd;
    int32_t length = (int32_t)(pEnd - pText);
    pOut->assign(pText, pText + length);
}

// @ 0xc582a0 SP::cSPMissionMultiDelivery::FUN_00c582a0
void __thiscall cSPMissionMultiDelivery::FUN_00c582a0()
{
}

// @ 0xc58310 SP::cSPMissionMultiDelivery::FUN_00c58310
void __thiscall cSPMissionMultiDelivery::FUN_00c58310()
{
}

// @ 0xc58360 SP::cSPMissionMultiDelivery::FUN_00c58360
void __thiscall cSPMissionMultiDelivery::FUN_00c58360()
{
}

// @ 0xc58530 SP::cSPMissionMultiDelivery::FUN_00c58530
void __thiscall cSPMissionMultiDelivery::FUN_00c58530()
{
}

// @ 0xc58600 SP::cSPMissionMultiDelivery::FUN_00c58600
void __thiscall cSPMissionMultiDelivery::FUN_00c58600()
{
}

} // namespace SP
