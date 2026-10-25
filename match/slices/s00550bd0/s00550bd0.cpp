// Slice s00550bd0: Pollinator::cAssetMetadata field setters / tag-list helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// ---- externals (the committed functions still call these by name) ----------
void  FUN_00423820(void* self, const void* first, const void* last);   // WStr range ctor
void  FUN_004237d0(void* self);                                       // WStr dtor
void  FUN_00554170();
void  FUN_005541e0();
void  FUN_006b8f40(void* v);
int*  FUN_00607a60();                                                  // SP::Pollen::AuthManager()
void* FUN_0067cb30();                                                  // SP::Pollen::cAuthState*
void  FUN_00553cc0(void* v);                                           // 0x00553cc0 VecStr::push_back
void  FUN_00554b60(void* first, void* last);                           // 0x00554b60 VecWStr::erase
void  WStr_Assign(void* self, const void* first, const void* last);    // 0x00423650 WStr::assign
void  WStr_Format(void* out, const void* fmt, int arg);                // 0x0041e050 cdecl
void  operator_delete(void* p);                                        // 0x00f47380
bool  GetParentServerID(void* pMeta, void* pOut1, void* pOut2);        // @ 0x00552080

extern char DAT_013f027c[];
extern char DAT_013f3da0[];
extern char DAT_013ec468[];

// ---- callees ---------------------------------------------------------------
struct Key {                       // EA::ResourceMan::Key
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};

struct DateTime {                  // EA::DateTime (halves kept apart: no 64-bit shifts)
    uint32_t mLow;
    uint32_t mHigh;
    void Set(int flags);                                          // @ 0x0092e3d0
};

struct WStr {                      // eastl::basic_string<wchar_t, eastl::allocator>
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    int       mAllocator;
    void assign(const uint16_t* first, const uint16_t* last);     // @ 0x00423650
    void Append(const void* first, const void* last);             // 0x00429580
};

struct Str8 {                      // eastl::basic_string<char, eastl::allocator>
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void assign(const char* first, const char* last);             // @ 0x0047d390
};

struct VecStr {                    // eastl::vector<eastl::string, eastl::sp_vector_allocator>
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mPad[2];
    void push_back(void* element);                                // @ 0x00553cc0
    void erase(void* first, void* last);                          // @ 0x00554760
};

struct VecWStr {                   // eastl::vector<eastl::basic_string<wchar_t>, ...>
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mPad[2];
    void push_back(void* element);                                // @ 0x00553f10
    void erase(void* first, void* last);                          // @ 0x00554b60
};

struct VecU32 {                    // eastl::vector_set<uint32_t>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mPad[2];
    void erase(void* first, void* last);                          // @ 0x004769b0
    void insert(void* result, const uint32_t* value);             // @ 0x00554020
};

struct cAssetDirectory {           // SP::Pollen::cAssetDirectory
    bool GetServerId(const void* pKey, void* pOut, bool flag) const;   // @ 0x0054e530
};

struct cAuthState {                // SP::Pollen::cAuthState
    char mPad_00[0x58];
    cAssetDirectory* mpAssetDirectory;    // +0x58
    DateTime mTime;                       // +0x60
};

struct SubAsset {                  // source metadata sub-object at +0xa4
    char mPad_00[0x08];
    WStr mStr_08;                      // +0x08
    DateTime mnID_18;                  // +0x18
};

struct SrcMeta {                   // source metadata passed as the 3rd argument
    int      mId_00;                   // +0x00
    char     mPad_04[0x14];
    WStr     mStr_18;                  // +0x18
    int      mId_28;                   // +0x28
    int      mId_2c;                   // +0x2c
    char     mPad_30[0x08];
    DateTime mTime_38;                 // +0x38
    char     mPad_40[0x18];
    DateTime mServerID_58;             // +0x58
    char     mPad_60[0x44];
    SubAsset* mpSub_a4;                // +0xa4
    char     mPad_a8[0x28];
    WStr     mStr_d0;                  // +0xd0
    void*    mpTagBegin;               // +0xe0
    void*    mpTagEnd;                 // +0xe4
    char     mPad_e8[0x10];
    uint32_t* mpU32Begin;              // +0xf8
    uint32_t* mpU32End;                // +0xfc
    char     mPad_100[0x10];
    uint8_t  mbFlag_110;               // +0x110
};

// ---- cAssetMetadata --------------------------------------------------------
struct Meta {
    char     mPad_00[0x08];
    Key      mKey_08;                  // +0x08 (EA::ResourceMan::Resource::mKey)
    char     mPad_14[0x04];
    DateTime mnAssetID;                // +0x18
    Key      mLocalKey;                // +0x20
    Key      mParentKey;               // +0x2c
    DateTime mnTimeStamp;              // +0x38
    DateTime mnServerID_40;            // +0x40
    DateTime mTime_48;                 // +0x48
    DateTime mTime_50;                 // +0x50
    WStr     mStr_58;                  // +0x58 (mAuthorStr)
    DateTime mTime_68;                 // +0x68
    int      mnID_70;                  // +0x70
    uint8_t  mbFlag_74;                // +0x74
    char     mPad_75[0x03];
    WStr     mStr_78;                  // +0x78 (mNameStr)
    WStr     mStr_88;                  // +0x88 (mSummaryStr)
    VecStr   mVecStr_98;               // +0x98 (mFeedURITable)
    VecWStr  mVecWStr_ac;              // +0xac (mTagList)
    VecU32   mVecU32_c0;               // +0xc0 (mConsequenceTraits)
    char     mPad_d4[0x2c];

    char FUN_00550b60(int key);
    char FUN_00550bd0(uint16_t* str);
    void FUN_00550cf0(WStr* out);
    char FUN_00550da0(int* param_2, int* param_3, int* param_4);
    char FUN_00551240(int* param_2, uint16_t* param_3, uint16_t* param_4, int param_5,
                      int* param_6, char param_7);
    char SetMetadata(uint32_t* param_2, int param_3, int param_4, int param_5, int param_6,
                     uint16_t* param_7, int param_8, int param_9, uint16_t* param_10,
                     uint16_t* param_11, int param_12, void* param_13, char param_14);
    void FUN_005519d0(uint16_t* a, uint16_t* b, int c);
    void FUN_00551af0(int a, int b);
};

// @ 0x00550bd0
char Meta::FUN_00550bd0(uint16_t* param_1)
{
    uint16_t* local_10 = param_1;
    uint16_t* local_6c = param_1;
    short sVar1;
    do { sVar1 = *local_6c; local_6c++; } while (sVar1 != 0);
    uint16_t* local_c = param_1 + (((int)local_6c - (int)(param_1 + 1)) >> 1);
    uint16_t* local_8 = 0;
    do {
        uint16_t* local_28;
        for (local_28 = local_10; local_28 != local_c && *local_28 != 0x2c; local_28++) { }
        local_8 = local_28;
        if (local_28 != local_10) {
            int local_20 = 0, local_1c = 0, local_18 = 0;
            FUN_00423820(&local_20, local_10, local_28);
            FUN_00554170();
            FUN_005541e0();
            FUN_006b8f40(&local_20);
            if (local_20 != local_1c) {
                FUN_00553cc0(&local_20);
            }
            FUN_004237d0(&local_20);
        }
        local_10 = local_8 + 1;
    } while (local_8 != local_c && local_10 != local_c);
    return 1;
}

// @ 0x00550cf0
void Meta::FUN_00550cf0(WStr* out)
{
    char* s = (char*)this;
    char* pe = *(char**)(s + 0xb0);
    bool first = true;
    for (char* p = *(char**)(s + 0xac); p != pe; p += 0x10) {
        if (!first) {
            uint16_t* sep = (uint16_t*)DAT_013f027c;
            uint16_t* q = sep;
            while (*q != 0) q++;
            out->Append(sep, sep + (((int)q - (int)sep) >> 1));
        }
        out->Append(*(void**)p, *(void**)(p + 4));
        first = false;
    }
}

// @ 0x00550da0
char Meta::FUN_00550da0(int* param_2, int* param_3, int* param_4)
{
    char result = 0;
    if (param_3 != 0) {
        int key = param_3[0];
        if (FUN_00550b60(key) != 0) {
            SrcMeta* src = (SrcMeta*)param_3;

            mLocalKey.mInstance = (uint32_t)param_2[0];
            mLocalKey.mType     = (uint32_t)param_2[1];
            mLocalKey.mGroup    = (uint32_t)param_2[2];

            mParentKey.mInstance = 0;
            mParentKey.mType     = 0;
            mParentKey.mGroup    = 0;

            mnTimeStamp  = src->mTime_38;
            mnServerID_40 = src->mServerID_58;

            mKey_08.mInstance = (uint32_t)param_2[0];
            mKey_08.mType     = 0x30bdee3;
            mKey_08.mGroup    = (uint32_t)param_2[2];

            mTime_48.mLow  = (uint32_t)src->mId_28;
            mTime_48.mHigh = (uint32_t)src->mId_2c;

            DateTime dt;
            dt.Set(1);
            mTime_50 = dt;

            FUN_0067cb30();

            SubAsset* sub = src->mpSub_a4;
            if (&sub->mStr_08 != &mStr_58) {
                mStr_58.assign(sub->mStr_08.mpBegin, sub->mStr_08.mpEnd);
            }
            mTime_68 = sub->mnID_18;

            int* am = (int*)FUN_00607a60();
            DateTime u = ((DateTime(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
            mbFlag_74 = (mTime_68.mLow == u.mLow && mTime_68.mHigh == u.mHigh);
            mnID_70 = -1;

            if (&src->mStr_18 != &mStr_78) {
                mStr_78.assign(src->mStr_18.mpBegin, src->mStr_18.mpEnd);
            }
            if (&src->mStr_d0 != &mStr_88) {
                mStr_88.assign(src->mStr_d0.mpBegin, src->mStr_d0.mpEnd);
            }

            if (*param_4 != param_4[1]) {
                mVecStr_98.push_back(param_4);
            }

            if (src->mbFlag_110 != 0) {
                Str8 tag = {0, 0, 0};
                const char* e = "tag:spore.com,2006:AssembledContent";
                const char* q = e;
                while (*q != 0) ++q;
                tag.assign(e, q);
                mVecStr_98.push_back(&tag);
                if (1 < (int)(tag.mpCapacity - tag.mpBegin) && tag.mpBegin != 0) {
                    operator_delete(tag.mpBegin);
                }
            }

            mVecWStr_ac.erase(mVecWStr_ac.mpBegin, mVecWStr_ac.mpEnd);
            for (void* it = src->mpTagBegin; it != src->mpTagEnd; it = (char*)it + 0x10) {
                mVecWStr_ac.push_back(it);
            }

            mVecU32_c0.erase(mVecU32_c0.mpBegin, mVecU32_c0.mpEnd);
            for (const uint32_t* it = src->mpU32Begin; it != src->mpU32End; ++it) {
                uint32_t sink[2];
                mVecU32_c0.insert(sink, it);
            }

            result = 1;
        }
    }
    return result;
}

// @ 0x00551240
char Meta::FUN_00551240(int* param_2, uint16_t* param_3, uint16_t* param_4, int param_5,
                        int* param_6, char param_7)
{
    mLocalKey.mInstance = (uint32_t)param_2[0];
    mLocalKey.mType     = (uint32_t)param_2[1];
    mLocalKey.mGroup    = (uint32_t)param_2[2];

    mKey_08.mInstance = (uint32_t)param_2[0];
    mKey_08.mType     = 0x30bdee3;
    mKey_08.mGroup    = (uint32_t)param_2[2];

    DateTime dt;
    dt.Set(1);
    mTime_48 = dt;
    mTime_50 = mTime_48;

    int* am = (int*)FUN_00607a60();
    int* p = ((int*(__thiscall*)(void*))((*(void***)am)[0x38 / 4]))(am);
    WStr_Format(&mStr_58, &DAT_013f3da0, *p);

    DateTime u = ((DateTime(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
    mTime_68 = u;
    mnID_70 = -1;
    mbFlag_74 = 1;

    {
        unsigned n = 0;
        while (param_3[n] != 0) ++n;
        if (n > 0xff) n = 0x100;
        mStr_78.assign(param_3, param_3 + n);
    }
    {
        unsigned n = 0;
        while (param_4[n] != 0) ++n;
        if (n > 0xfff) n = 0x1000;
        mStr_88.assign(param_4, param_4 + n);
    }

    mParentKey.mInstance = (uint32_t)param_6[0];
    mParentKey.mType     = (uint32_t)param_6[1];
    mParentKey.mGroup    = (uint32_t)param_6[2];

    mnTimeStamp.mLow = 0xffffffff;   mnTimeStamp.mHigh = 0xffffffff;
    mnServerID_40.mLow = 0xffffffff; mnServerID_40.mHigh = 0xffffffff;

    if (mParentKey.mInstance != 0
        && GetParentServerID(this, &mnTimeStamp, &mnServerID_40) == 0
        && ((mnTimeStamp.mLow & mnTimeStamp.mHigh) == 0xffffffff)) {
        cAuthState* st = (cAuthState*)FUN_0067cb30();
        if (st->mpAssetDirectory->GetServerId(&mParentKey, &mnTimeStamp, false)) {
            mnServerID_40 = mnTimeStamp;
        }
    }

    if (param_7 != 0) {
        cAuthState* st = (cAuthState*)FUN_0067cb30();
        mnAssetID = st->mTime;
    } else {
        mnAssetID.mLow = 0xffffffff;
        mnAssetID.mHigh = 0xffffffff;
    }

    mVecStr_98.erase(mVecStr_98.mpBegin, mVecStr_98.mpEnd);
    mVecStr_98.push_back(p);

    if (param_5 != 0) {
        mVecWStr_ac.erase(mVecWStr_ac.mpBegin, mVecWStr_ac.mpEnd);
        FUN_00550bd0((uint16_t*)param_5);
    }
    return 1;
}

// @ 0x00551620
char Meta::SetMetadata(uint32_t* param_2, int param_3, int param_4, int param_5, int param_6,
                       uint16_t* param_7, int param_8, int param_9, uint16_t* param_10,
                       uint16_t* param_11, int param_12, void* param_13, char param_14)
{
    mLocalKey.mInstance = param_2[0];
    mLocalKey.mType     = param_2[1];
    mLocalKey.mGroup    = param_2[2];

    mKey_08.mInstance = param_2[0];
    mKey_08.mType     = 0x30bdee3;
    mKey_08.mGroup    = param_2[2];

    mnAssetID.mLow  = (uint32_t)param_3;
    mnAssetID.mHigh = (uint32_t)param_4;
    mTime_48.mLow   = (uint32_t)param_5;
    mTime_48.mHigh  = (uint32_t)param_6;

    if (param_14 != 0) {
        DateTime dt;
        dt.Set(1);
        mTime_50 = dt;
    } else {
        mTime_50 = mTime_48;
    }

    {
        unsigned n = 0;
        while (param_7[n] != 0) ++n;
        if (n > 0xff) n = 0x100;
        mStr_58.assign(param_7, param_7 + n);
    }

    mTime_68.mLow  = (uint32_t)param_8;
    mTime_68.mHigh = (uint32_t)param_9;
    mnID_70 = -1;
    mbFlag_74 = 0;

    int* am = (int*)FUN_00607a60();
    DateTime u = ((DateTime(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
    mbFlag_74 = (mTime_68.mLow == u.mLow && mTime_68.mHigh == u.mHigh);

    {
        unsigned n = 0;
        while (param_10[n] != 0) ++n;
        if (n > 0xff) n = 0x100;
        mStr_78.assign(param_10, param_10 + n);
    }
    {
        unsigned n = 0;
        while (param_11[n] != 0) ++n;
        if (n > 0xfff) n = 0x1000;
        mStr_88.assign(param_11, param_11 + n);
    }

    FUN_00550bd0((uint16_t*)param_12);

    if (param_13 != 0) {
        mVecStr_98.erase(mVecStr_98.mpBegin, mVecStr_98.mpEnd);
        Str8 tag = {0, 0, 0};
        const char* e = (const char*)param_13;
        const char* q = e;
        while (*q != 0) ++q;
        tag.assign(e, q);
        mVecStr_98.push_back(&tag);
        if (1 < (int)(tag.mpCapacity - tag.mpBegin) && tag.mpBegin != 0) {
            operator_delete(tag.mpBegin);
        }
    }
    return 1;
}

// @ 0x005519d0
void Meta::FUN_005519d0(uint16_t* param_2, uint16_t* param_3, int param_4)
{
    char* s = (char*)this;
    {
        uint16_t* q = param_2; while (*q) q++;
        unsigned n = (unsigned)((q - param_2) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)(s + 0x78), param_2, param_2 + n);
    }
    {
        uint16_t* q = param_3; while (*q) q++;
        unsigned n = (unsigned)((q - param_3) >> 1);
        if (n > 0xfff) n = 0x1000;
        WStr_Assign((WStr*)(s + 0x88), param_3, param_3 + n);
    }
    if (param_4 != 0) {
        FUN_00554b60(*(void**)(s + 0xac), *(void**)(s + 0xb0));
        FUN_00550bd0((uint16_t*)param_4);
    }
}

// @ 0x00551af0
void Meta::FUN_00551af0(int a, int b)
{
    *(int*)((char*)this + 0x18) = a;
    *(int*)((char*)this + 0x1c) = b;
    int* am = (int*)FUN_00607a60();
    int* p = (int*)((int(__thiscall*)(void*))((*(void***)am)[0x38 / 4]))(am);
    WStr_Format((void*)((char*)this + 0x58), (void*)&DAT_013f3da0, *p);
    *(int64_t*)((char*)this + 0x68) = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
}
