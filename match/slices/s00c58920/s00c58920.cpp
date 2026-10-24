// s00c58920.cpp - reconstructed slice
// Compiler: MSVC 2008 SP1 (x86)
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
// ---------------------------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------------------------
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef int                i32;
typedef float              f32;
typedef unsigned short     wchar_t_;

struct cWString {
    void* mpBegin;                      // 0x00
    void* mpEnd;                        // 0x04
    void* mpCap;                        // 0x08
    void  assign(const void* begin, const void* end);  // 0x00423650
};

// eastl vector header: {begin, end, cap}
template <class T>
struct cVector {
    T*  mpBegin;                        // 0x00
    T*  mpEnd;                          // 0x04
    T*  mpCap;                          // 0x08
    void erase(T* first, T* last);      // inlined erase helper
};

// Out-of-line definition so the relocation resolves for testing.
template <class T>
void cVector<T>::erase(T* first, T* last)
{
    mpBegin = last;
}

struct cPlanet {
    void* vftable;                      // 0x00
    void* GetNameInternal();            // 0x00c707e0 -> returns cWString of the name
};

// Base mission class method (tail-called from the dispatch chain).
struct cSPMissionBase {
    i32 GetTagString(u32 tag, cWString* out);       // 0x00c491c0
};

struct cSPMissionMultiDelivery {
    u8 mPad0000[0x1f4];
    void* mpBuyerVecBegin;              // 0x1f4 (vector {begin,end,cap})
    void* mpBuyerVecEnd;                // 0x1f8
    u8 mPad1fc[0x208 - 0x1fc];
    void* mpItemVecBegin;               // 0x208
    void* mpItemVecEnd;                 // 0x20c
    u8 mPad210[0x21c - 0x210];
    void* mpHandleVecBegin;             // 0x21c
    void* mpHandleVecEnd;               // 0x220

    i32 GetFetchItemName(cWString* out);            // 0x00c58260
    i32 GetItemPlanetNameList(cWString* out);       // 0x00c58920
    i32 GetNumItemsNotDeliveredToBuyer(cPlanet* p); // 0x00c572c0
    u8  GetTagString(u32 tag, cWString* out);       // 0x00c58ad0
    u32 Cleanup();                                  // 0x00c59190
    void Reset();                                   // 0x00c49f90
};

// ---------------------------------------------------------------------------------------------
// Opaque extern callees referenced by absolute address.
// ---------------------------------------------------------------------------------------------
void __cdecl WStr_Assign(cWString* dst, const void* src);          // 0x00423650
void __cdecl WStr_Format(cWString* dst, const wchar_t_* fmt, ...); // 0x0041e050

// ---------------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------------
// @ 0x00c58ad0
// Tag-dispatch returning localized mission strings.
u8 cSPMissionMultiDelivery::GetTagString(u32 tag, cWString* out)
{
    if (tag == 0x97cc2aa3) {
        cPlanet* planet = *(cPlanet**)mpBuyerVecBegin;
        if (planet != 0) {
            cWString* name = (cWString*)planet->GetNameInternal();
            if (name != out)
                out->assign(name->mpBegin, name->mpEnd);
        }
        return 1;
    }
    if (tag == 0x659ef0ac) {
        GetFetchItemName(out);
        return 1;
    }
    if (tag == 0xaa6cdbb8) {
        GetItemPlanetNameList(out);
        return 1;
    }
    if (tag == 0x8aad4d34) {
        i32 n = GetNumItemsNotDeliveredToBuyer(*(cPlanet**)mpBuyerVecBegin);
        WStr_Format(out, (const wchar_t_*)0x013f01bc, n);
        return 1;
    }
    return ((cSPMissionBase*)this)->GetTagString(tag, out);
}

// @ 0x00c59190
// Releases mission vectors and star-map visuals, then trims the handle list.
struct cStarMap {
    void RemoveVisual(i32 handle, i32 flag);        // 0x01045a60
};

void* __stdcall GetStarMap(i32 handle, i32 flag);   // 0x01046fc0
void __cdecl MemCopy(void* dst, const void* src, u32 bytes);  // 0x011e0744

u32 cSPMissionMultiDelivery::Cleanup()
{
    // Release the buyer-info and item-info vectors.
    ((cVector<void>*)&mpBuyerVecBegin)->erase(mpBuyerVecBegin, mpBuyerVecEnd);
    ((cVector<void>*)&mpItemVecBegin)->erase(mpItemVecBegin, mpItemVecEnd);

    i32 count = (i32)(((char*)mpHandleVecEnd - (char*)mpHandleVecBegin) >> 2);
    for (i32 i = 0; i < count; ++i) {
        i32 handle = ((i32*)mpHandleVecBegin)[i];
        if (handle != -1) {
            cStarMap* map = (cStarMap*)GetStarMap(handle, 0);
            map->RemoveVisual(handle, 0);
        }
    }

    // Trim the handle list back to empty.
    MemCopy(mpHandleVecBegin, mpHandleVecEnd, 0);
    mpHandleVecEnd = (char*)mpHandleVecEnd + (i32)(((char*)mpHandleVecEnd - (char*)mpHandleVecBegin) >> 2) * -4;

    Reset();
    return 0;
}
