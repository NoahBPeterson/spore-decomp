// src/game/SPGonzago/_at_00e00000.cpp -- migrated from slice(s) s00e0a4c0, s00e094f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00e00000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGrid.h"
#include "SP/cSPCreatureBase.h"
#include "cSPUILayout.h"
#include "SP/cSpeciesProfile.h"

// unnamed retail callees and globals (address in the comment)
extern const float g_FloatOne;                               // 0x01485720  1.0f
extern wchar_t gEmptyString16[];                             // 0x01667bac  eastl::gEmptyString16

// ---- items of slice s00e094f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void  __cdecl FUN_00f47380(void* p);                         // 0x00f47380  operator delete[]
void  __cdecl FUN_00571db0(void*, void*, void*, void*, void*);  // 0x00571db0 EA::Messaging::RemoveHandler
char  __cdecl FUN_00807690(void* window, int32_t refresh);    // 0x00807690
extern const float g_FloatOne;                               // 0x01485720  1.0f
extern wchar_t gEmptyString16[];                             // 0x01667bac  eastl::gEmptyString16
struct cGrid;
struct cRefObject {                                          // refcounted object, release at +0x04
    PV(0)
    virtual void Release();                                  // +0x04
};
struct cGameObject {                                          // the caller's object (slot +0x0c query)
    PV(0) PV(1) PV(2)
    virtual void* v3(uint32_t kind);                          // +0x0c
};
struct cSPCreatureBase {
    void* GetSpeciesProfile();                                // 0x00c0bbd0
};
struct cNameProvider {                                        // queried with 0xe9cb8ba
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual void* v29();                                      // +0x74
};
struct WString;                                               // eastl::basic_string<wchar_t>
struct cSpeciesName {
    void GetUiName(WString* out);                             // 0x004da330
};
struct WString {                                              // eastl::basic_string<wchar_t>
    wchar_t* mBegin;                                          // +0x00
    wchar_t* mEnd;                                            // +0x04
    wchar_t* mCapacity;                                       // +0x08
    WString() : mBegin(gEmptyString16), mEnd(gEmptyString16), mCapacity(gEmptyString16 + 1) {}
    ~WString();
};
struct cGridMessage {                                        // grid refresh message
    uint32_t mPad00;                                          // +0x00
    uint32_t mPad04;                                          // +0x04
    uint32_t mPad08;                                          // +0x08
    uint32_t mPad0C;                                          // +0x0c
    uint32_t mType;                                           // +0x10
    uint32_t mPad14;                                          // +0x14
    void*    mTarget;                                         // +0x18
};
struct cVector18 {                                            // eastl vector living at +0x18
    void* mBegin;                                             // +0x00
    void* mEnd;                                               // +0x04
    void* mCapacity;                                          // +0x08
    void Destroy();                                           // 0x005c7f10
};
struct cGrid {
    void*    mField00;                                        // +0x00
    void*    mField04;                                        // +0x04
    void*    mField08;                                        // +0x08
    void*    mField0C;                                        // +0x0c
    uint32_t mField10;                                        // +0x10
    uint32_t mField14;                                        // +0x14
    int32_t* mData;                                           // +0x18
    int32_t* mDataEnd;                                        // +0x1c
    int32_t* mDataCap;                                        // +0x20
    uint32_t mField24;                                        // +0x24
    uint32_t mField28;                                        // +0x28
    int32_t  mStride;                                         // +0x2c
    int32_t* mRowBegin;                                       // +0x30
    int32_t* mRowEnd;                                         // +0x34
    uint32_t mRowCap;                                         // +0x38
    uint32_t mPad3C[2];                                       // +0x3c
    float    mField44;                                        // +0x44
    float    mField48;                                        // +0x48
    float    mField4C;                                        // +0x4c
    float    mField50;                                        // +0x50
    float    mField54;                                        // +0x54
    float    mField58;                                        // +0x58
    void*    mHandler;                                        // +0x5c
    void*    mHandlerArg0;                                    // +0x60
    void*    mHandlerArg1;                                    // +0x64
    void*    mHandlerArg2;                                    // +0x68
    void*    mHandlerArg3;                                    // +0x6c

    void* Init();                                             // 0x00e0a390
    void  Destroy();                                          // 0x00e0a400
    void  LayoutCells();                                      // 0x00e0a270
    bool  HandleMessage(uint32_t id, void* msg);              // 0x00e0a480
    int32_t CellStart(int32_t row, int32_t col);              // 0x00e09ca0
    void  FUN_00e09d10();                                     // 0x00e09d10
    void* FUN_01077ae0(int32_t element);                      // 0x01077ae0
};
struct cCell {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual void v27(float* rect);                            // +0x6c
};
// ---- items of slice s00e094f0 end

// ---- items of slice s00e0a4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*  __cdecl memcpy(void*, const void*, unsigned int);
#pragma warning(disable : 4100)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)
typedef unsigned int  u32;
typedef unsigned char u8;
struct Float3 { float x, y, z; };
struct cPaletteGrid;
struct IWin;
struct ISlot {
    virtual void v00();
    virtual void v04();
    virtual void v08();
};
struct IWin {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void* v0C(u32 name);
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void* v1C();
    virtual void  v20();
    virtual void  v24();
    virtual void  v28();
    virtual void  v2C();
    virtual void  v30();
    virtual void  v34();
    virtual void* v38();
    virtual void  v3C();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual IWin* v4C();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58();
    virtual void  v5C();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6C(void* child);
    virtual void  v70(float x, float y);
    virtual void  v74();
    virtual void  v78();
    virtual void  v7C(int a, int b);
    virtual void  v80();
    virtual void  v84();
    virtual bool  v88(void* a, void* b);
    virtual void  v8C();
    virtual void  v90();
    virtual void  v94(void* p);
    virtual void  v98();
    virtual void  v9C();
    virtual void  vA0();
    virtual void  vA4();
    virtual void  vA8();
    virtual void  vAC();
    virtual void  vB0();
    virtual void  vB4();
    virtual void  vB8();
    virtual void  vBC();
    virtual void  vC0();
    virtual void  vC4();
    virtual void  vC8();
    virtual void  vCC();
    virtual void  vD0();
    virtual void  vD4();
    virtual void  vD8(void* child);
};
struct cSPUILayout_s00e0_a4c0 {
    cSPUILayout_s00e0_a4c0* ctor();                                   // 0x00810000
    bool Init(const void* key, bool b, u32 name);          // 0x008120d0
    bool SetParentWin(void* parent, bool b, u32 name);     // 0x008121b0
    u8 pad[0x18];
};
struct AutoRef {
    cSPUILayout_s00e0_a4c0* p;
    AutoRef(cSPUILayout_s00e0_a4c0* q) : p(q) {
        if (q != 0)
            ((ISlot*)q)->v04();
    }
    ~AutoRef() {
        if (p != 0)
            ((ISlot*)p)->v08();
    }
};
struct cRefVector {
    u32*  mBegin;
    u32*  mEnd;
    u32*  mCap;
    void  Reserve(u32 n);                                  // 0x00d01790
    void* erase(u32* first, u32* last);                    // 0x005c2170
    void  DoInsert(u32* pos, void** val);                  // 0x005c8480
};
struct cU32Vector {
    u32* mBegin;
    u32* mEnd;
    u32* mCap;
    void erase(u32* first, u32* last) {
        u32* e = mEnd;
        memcpy(first, last, (u32)((char*)e - (char*)last));
        mEnd -= (last - first);
    }
    void DoInsertValueI(u32* pos, const u32& val);          // 0x004558a0
    void DoAssign(const int* first, const int* last, u32 n);// 0x004d04f0
};
struct cPaletteGrid {
    u8 pad00[4];
    void* mWin4;            // +0x04
    void* mWin8;            // +0x08
    u32 mKey0C;             // +0x0c
    u32 mKey10;             // +0x10
    u32 mKey14;             // +0x14
    cRefVector mPages;      // +0x18
    u8 pad24[0x0c];
    cU32Vector mSel;        // +0x30
    u8 pad3C[0x20];
    u32 mHandler;           // +0x5c
    u32 mHandlerA0;         // +0x60
    u32 mHandlerA1;         // +0x64
    u32 mHandlerA2;         // +0x68
    u32 mHandlerA3;         // +0x6c
    u8 pad70[0x19c];
    IWin* mTarget;          // +0x20c
    u8 pad210[8];
    float m218;             // +0x218
    float m21C;             // +0x21c
    float m220;             // +0x220
    u8 pad224[0x15];
    u8 m239;                // +0x239
    u8 pad23A[2];
    int m23C;               // +0x23c
    u8 pad240[0x40];
    u8 mPal[0x81];          // +0x280
    u8 pad301[0x53];
    float m354;             // +0x354
    u8 pad358[4];
    u32 m35C;               // +0x35c
    u8 pad360[0x630];
    float m990;             // +0x990
    float m994;             // +0x994
    float m998;             // +0x998
    float m99C;             // +0x99c
    float m9A0;             // +0x9a0

    void FUN_00e09d10();    // 0x00e09d10
    bool LayoutCells();     // 0x00e0a270 (declared bool: callers return its eax)
    bool AddPages(u32 count); // 0x00e0a680
};
void*  __cdecl FUN_00f473a0(u32 size, const char* name, u32 a, u32 b, u32 c, u32 d);
void*  __cdecl FUN_00807600(const wchar_t* name, void** out, int flag);
void   __cdecl FUN_008076f0(void* p);
void   __cdecl FUN_00571db0(u32 h, u32 a0, u32 a1, u32 a2, u32 a3);
// ---- items of slice s00e0a4c0 end

// @ 0x00e09b10
const wchar_t* __cdecl FUN_00e09b10(cGameObject* obj)
{
    if (obj != 0) {
        void* creature = obj->v3(0xce9f6639);
        if (creature != 0) {
            void* profile = ((cSPCreatureBase*)creature)->GetSpeciesProfile();
            if (profile != 0) {
                static WString s_Name;
                ((cSpeciesName*)profile)->GetUiName(&s_Name);
                return s_Name.mBegin;
            }
        }
        void* plain = obj->v3(0xe9cb8ba);
        if (plain != 0) {
            return (const wchar_t*)((cNameProvider*)plain)->v29();
        }
        void* third = obj->v3(0x137e8e0);
        if (third != 0) {
            return *(const wchar_t**)((char*)third + 0xcc8);
        }
        void* fourth = obj->v3(0xb033b403);
        if (fourth != 0) {
            return *(const wchar_t**)((char*)fourth + 0x7e0);
        }
    }
    return 0;
}

// @ 0x00e09ca0
int32_t cGrid::CellStart(int32_t row, int32_t col)
{
    if (mRowBegin == mRowEnd) {
        return mData[mStride * row + col];
    }
    int32_t sum = 0;
    int32_t extra = 0;
    uint32_t twice = 0;
    if (row >= 2) {
        uint32_t n = ((uint32_t)(row - 2) >> 1) + 1;
        sum = mRowBegin[row] * (int32_t)n;
        twice = n + n;
    }
    if (twice < row) {
        extra = mRowBegin[row];
    }
    int32_t index = sum;
    index += sum;
    index += extra;
    index += col;
    return mData[index];
}

// @ 0x00e0a270
void cGrid::LayoutCells()
{
    bool merged = mRowBegin != mRowEnd;
    uint32_t row = 0;
    uint32_t col = 0;
    uint32_t off = 0;
    int32_t count = (int32_t)(mDataEnd - mData);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        float x1 = (float)col * (mField4C + mField54) + mField44;
        float y1 = (float)row * (mField50 + mField58) + mField48;
        float rect[4];
        rect[0] = x1;
        rect[1] = y1;
        rect[2] = x1 + mField54;
        rect[3] = y1 + mField58;
        ((cCell*)FUN_01077ae0(mData[i]))->v27(rect);
        ++col;
        if (col == (uint32_t)mStride) {
            col = 0;
            ++row;
        } else if (merged && col == *(int32_t*)((char*)mRowBegin + off)) {
            col = 0;
            ++row;
            off += 4;
        }
    }
    FUN_00807690(mField04, 1);
}

// @ 0x00e0a390
void* cGrid::Init()
{
    mField00 = (void*)0x0147f604;
    mField04 = 0;
    mField08 = 0;
    mField0C = 0;
    mField10 = 0;
    mField14 = 0;
    mData = 0;
    mDataEnd = 0;
    mDataCap = 0;
    mStride = 1;
    mRowBegin = 0;
    mRowEnd = 0;
    mRowCap = 0;
    mField44 = 0.0f;
    mField48 = 0.0f;
    mField4C = 0.0f;
    mField50 = 0.0f;
    float one = g_FloatOne;
    mField54 = one;
    mField58 = one;
    mHandler = 0;
    mHandlerArg0 = 0;
    mHandlerArg1 = 0;
    mHandlerArg2 = 0;
    mHandlerArg3 = 0;
    return this;
}

// @ 0x00e0a400
void cGrid::Destroy()
{
    *(void* volatile*)&mField00 = (void*)0x0147f604;
    if (mHandler != 0) {
        void* handler = mHandler;
        mHandler = 0;
        FUN_00571db0(handler, mHandlerArg0, mHandlerArg1, mHandlerArg2, mHandlerArg3);
    }
    if (mRowBegin != 0 && ((int32_t*)mRowBegin)[-1] != 0) {
        FUN_00f47380(mRowBegin);
    }
    ((cVector18*)((char*)this + 0x18))->Destroy();
    if (mField08 != 0) {
        ((cRefObject*)mField08)->Release();
    }
    if (mField04 != 0) {
        ((cRefObject*)mField04)->Release();
    }
    mField00 = (void*)0x013eb394;
}

// @ 0x00e0a480
bool cGrid::HandleMessage(uint32_t id, void* msgPtr)
{
    cGridMessage* msg = (cGridMessage*)msgPtr;
    if (id == 0x00f62def && mData != mDataEnd && msg->mType == 0x068328d6
        && msg->mTarget == mField0C) {
        FUN_00e09d10();
        LayoutCells();
    }
    return true;
}

// @ 0x00e0a4c0
bool __fastcall FUN_00e0a4c0(cPaletteGrid* ecx_this, void* edx, IWin* win, Float3* key)
{
    bool ok = false;
    if (win != 0) {
        IWin* old8 = (IWin*)ecx_this->mWin8;
        if (old8 != 0) {
            ecx_this->mWin8 = 0;
            old8->v04();
        }
        IWin* created = (IWin*)FUN_00807600(L"ScrollFrameVerticalGeneric", &ecx_this->mWin8, 1);
        IWin* old4 = (IWin*)ecx_this->mWin4;
        if (created != old4) {
            if (created != 0)
                created->v00();
            ecx_this->mWin4 = created;
            if (old4 != 0)
                old4->v04();
        }
        if (ecx_this->mWin4 != 0 && ecx_this->mWin8 != 0) {
            u32* k = (u32*)key;
            win->vD8(ecx_this->mWin4);
            IWin* w4 = (IWin*)ecx_this->mWin4;
            w4->v6C(win->v38());
            w4->v70(0.0f, 0.0f);
            ecx_this->mKey0C = k[0];
            ecx_this->mKey10 = k[1];
            ecx_this->mKey14 = k[2];
            ecx_this->FUN_00e09d10();
            ok = true;
        }
    }
    return ok;
}

// @ 0x00e0a5c0
void __fastcall FUN_00e0a5c0(cPaletteGrid* ecx_this, void* edx)
{
    if (ecx_this->mHandler != 0) {
        u32 h = ecx_this->mHandler;
        u32 a0 = ecx_this->mHandlerA0;
        u32 a1 = ecx_this->mHandlerA1;
        u32 a2 = ecx_this->mHandlerA2;
        u32 a3 = ecx_this->mHandlerA3;
        ecx_this->mHandler = 0;
        FUN_00571db0(h, a0, a1, a2, a3);
    }
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    FUN_008076f0(ecx_this->mWin4);
    if (ecx_this->mWin4 != 0) {
        ISlot* p = (ISlot*)ecx_this->mWin4;
        ecx_this->mWin4 = 0;
        p->v04();
    }
    if (ecx_this->mWin8 != 0) {
        ISlot* p = (ISlot*)ecx_this->mWin8;
        ecx_this->mWin8 = 0;
        p->v04();
    }
}

// @ 0x00e0a640
void __fastcall FUN_00e0a640(cPaletteGrid* ecx_this, void* edx)
{
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    ecx_this->mSel.erase(ecx_this->mSel.mBegin, ecx_this->mSel.mEnd);
}

// @ 0x00e0a680
bool cPaletteGrid::AddPages(u32 count)
{
    cRefVector& pages = mPages;
    pages.Reserve((u32)(pages.mEnd - pages.mBegin) + count);
    for (u32 i = 0; i < count; i++) {
        u8* mem = (u8*)FUN_00f473a0(0x18, "UI/TiledLayout", 0, 0, 0, 0);
        cSPUILayout_s00e0_a4c0* layout = 0;
        if (mem != 0)
            layout = ((cSPUILayout_s00e0_a4c0*)mem)->ctor();
        {
            AutoRef local(layout);
            if (pages.mEnd < pages.mCap) {
                u32* slot = pages.mEnd;
                pages.mEnd = slot + 1;
                if (slot != 0) {
                    *slot = (u32)layout;
                    if (layout != 0)
                        ((ISlot*)layout)->v04();
                }
            } else {
                pages.DoInsert(pages.mEnd, (void**)&local);
            }
        }
        if (!layout->Init(&mKey0C, false, 0x5b598fa))
            return false;
        layout->SetParentWin(mWin8, true, 0x5b598fa);
    }
    return true;
}

// @ 0x00e0a780
bool __fastcall FUN_00e0a780(cPaletteGrid* ecx_this, void* edx, Float3* key, u32 count)
{
    bool ok = false;
    u32* k = (u32*)key;
    ecx_this->mKey0C = k[0];
    ecx_this->mKey10 = k[1];
    ecx_this->mKey14 = k[2];
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    ecx_this->mSel.erase(ecx_this->mSel.mBegin, ecx_this->mSel.mEnd);
    if (ecx_this->AddPages(count)) {
        ecx_this->FUN_00e09d10();
        return ecx_this->LayoutCells();
    }
    return ok;
}

// @ 0x00e0a800
bool __fastcall FUN_00e0a800(cPaletteGrid* ecx_this, void* edx, u32 val)
{
    bool ok = false;
    if (!ecx_this->AddPages(val))
        return ok;
    if (ecx_this->mSel.mBegin != ecx_this->mSel.mEnd) {
        u32* end = ecx_this->mSel.mEnd;
        if (end < ecx_this->mSel.mCap) {
            ecx_this->mSel.mEnd = end + 1;
            if (end != 0) {
                *end = val;
                return ecx_this->LayoutCells();
            }
        } else {
            ecx_this->mSel.DoInsertValueI(end, val);
        }
    }
    return ecx_this->LayoutCells();
}

// @ 0x00e0a870
bool __fastcall FUN_00e0a870(cPaletteGrid* ecx_this, void* edx, Float3* key, u32 count, int* array)
{
    bool ok = false;
    u32* k = (u32*)key;
    ecx_this->mKey0C = k[0];
    ecx_this->mKey10 = k[1];
    ecx_this->mKey14 = k[2];
    int even = 0;
    int odd = 0;
    u32 i = 0;
    u32 tail = 0;
    if (count >= 2) {
        u32 limit = count - 1;
        do {
            even += array[i];
            odd += array[i + 1];
            i += 2;
        } while (i < limit);
    }
    if (i < count)
        tail = (u32)array[i];
    tail += (u32)(even + odd);
    ecx_this->mPages.erase(ecx_this->mPages.mBegin, ecx_this->mPages.mEnd);
    ecx_this->mSel.erase(ecx_this->mSel.mBegin, ecx_this->mSel.mEnd);
    if (ecx_this->AddPages(tail)) {
        ecx_this->mSel.DoAssign(array, array + count, count);
        ecx_this->FUN_00e09d10();
        return ecx_this->LayoutCells();
    }
    return ok;
}
