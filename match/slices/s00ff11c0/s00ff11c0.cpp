// Slice s00ff11c0 - SporeApp 0x00ff11c0..0x00ff2060
// Simulator::cCivData / cCityData and ornament-vector value helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
void __cdecl operator_delete_array(void* p);      // 0x00f47380
void* __cdecl memcpy_fn(void* dst, const void* src, unsigned int n);   // 0x011e0744

// eastl::basic_string<wchar_t>
struct cWString {
    void* mpBegin;                 // 0x00
    void* mpEnd;                   // 0x04
    void* mpCap;                   // 0x08

    void assign(const void* first, const void* last);   // 0x00423650
};

// ---------------------------------------------------------------------------------------------
// Ornament data records
// ---------------------------------------------------------------------------------------------
// 0x38-byte record with two flag bytes.
struct cOrnamentDataA {
    float mF00;                    // 0x00
    float mF04;                    // 0x04
    float mF08;                    // 0x08
    float mF0c;                    // 0x0c
    float mF10;                    // 0x10
    float mF14;                    // 0x14
    float mF18;                    // 0x18
    float mF1c;                    // 0x1c
    int   mField20;                // 0x20
    bool  mFlag24;                 // 0x24
    bool  mFlag25;                 // 0x25
    int   mField28;                // 0x28
    int   mField2c;                // 0x2c
    int   mField30;                // 0x30
    int   mField34;                // 0x34

    cOrnamentDataA& operator=(const cOrnamentDataA& o);   // 0x00ff11c0
};

// 0x38-byte record made of plain integers after the float block.
struct cOrnamentDataB {
    float mF00;                    // 0x00
    float mF04;                    // 0x04
    float mF08;                    // 0x08
    float mF0c;                    // 0x0c
    float mF10;                    // 0x10
    float mF14;                    // 0x14
    float mF18;                    // 0x18
    float mF1c;                    // 0x1c
    int   mField20;                // 0x20
    int   mField24;                // 0x24
    int   mField28;                // 0x28
    int   mField2c;                // 0x2c
    int   mField30;                // 0x30
    u8    mPad0034[0x38 - 0x34];

    cOrnamentDataB& operator=(const cOrnamentDataB& o);   // 0x00ff1230
};

// @ 0x00ff11c0
cOrnamentDataA& cOrnamentDataA::operator=(const cOrnamentDataA& o)
{
    mF00 = o.mF00;
    mF04 = o.mF04;
    mF08 = o.mF08;
    mF0c = o.mF0c;
    mF10 = o.mF10;
    mF14 = o.mF14;
    mF18 = o.mF18;
    mF1c = o.mF1c;
    mField20 = o.mField20;
    mFlag24 = o.mFlag24;
    mFlag25 = o.mFlag25;
    mField28 = o.mField28;
    mField2c = o.mField2c;
    mField30 = o.mField30;
    mField34 = o.mField34;
    return *this;
}

// @ 0x00ff1230
cOrnamentDataB& cOrnamentDataB::operator=(const cOrnamentDataB& o)
{
    mF00 = o.mF00;
    mF04 = o.mF04;
    mF08 = o.mF08;
    mF0c = o.mF0c;
    mF10 = o.mF10;
    mF14 = o.mF14;
    mF18 = o.mF18;
    mF1c = o.mF1c;
    mField20 = o.mField20;
    mField24 = o.mField24;
    mField28 = o.mField28;
    mField2c = o.mField2c;
    mField30 = o.mField30;
    return *this;
}

// ---------------------------------------------------------------------------------------------
// UI text holders: two embedded strings that can be re-assigned from a source
// string unless the source is the embedded string itself.
// ---------------------------------------------------------------------------------------------
struct cTextHolder {
    u8        mPad0000[0x40];
    cWString  mText40;             // 0x40
    u8        mPad004c[0x50 - 0x4c];
    cWString  mText50;             // 0x50

    void SetText40(const cWString* src);   // 0x00ff14f0
    void SetText50(const cWString* src);   // 0x00ff1510
};

// @ 0x00ff14f0
void cTextHolder::SetText40(const cWString* src)
{
    if (src != &mText40)
        mText40.assign(src->mpBegin, src->mpEnd);
}

// @ 0x00ff1510
void cTextHolder::SetText50(const cWString* src)
{
    if (src != &mText50)
        mText50.assign(src->mpBegin, src->mpEnd);
}

// ---------------------------------------------------------------------------------------------
// Simulator::cCivData
// ---------------------------------------------------------------------------------------------
struct cCityData {
    u8 mPad0000[0x38];

    ~cCityData();                  // 0x00ff13c0
};

struct cCivData {
    u8           mPad0000[0x28];
    int*         mpValues28;       // 0x28
    int*         mpValuesEnd2c;    // 0x2c
    u8           mPad0030[0x3c - 0x30];
    cCityData**  mpCities3c;       // 0x3c
    cCityData**  mpCitiesEnd40;    // 0x40

    void EraseCity(int index);     // 0x00ff1fb0
    void EraseValue(int value);    // 0x00ff1ff0
};

// @ 0x00ff1fb0
// Destroys and removes the city at `index`, compacting the pointer array.
void cCivData::EraseCity(int index)
{
    cCityData* city = mpCities3c[index];
    if (city != 0) {
        city->~cCityData();
        operator_delete_array(city);
    }
    mpCities3c[index] = mpCitiesEnd40[-1];
    --mpCitiesEnd40;
}

// @ 0x00ff1ff0
// Removes the first occurrence of `value` from the value list.
void cCivData::EraseValue(int value)
{
    int* first = mpValues28;
    int* last = mpValuesEnd2c;
    while (first != last && *first != value)
        ++first;
    if (first != last) {
        if (value != 0)
            operator_delete_array((void*)value);
        if (first + 1 < last)
            memcpy_fn(first, first + 1, (unsigned int)((char*)last - (char*)(first + 1)));
        mpValuesEnd2c = last - 1;
    }
}
