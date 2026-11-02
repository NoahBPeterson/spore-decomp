// src/game/SPAudio/AudioResponseCurve.cpp -- migrated from slice(s) s00a1a590, s00a196f0, s009515e0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioResponseCurve.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <new>
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Envelope.h"
#include "EA/Audio/ResourceInstrumentBank.h"
#include "EA/Audio/Sound.h"

// ---- items of slice s009515e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
template <typename T>
class generic_iterator { public:
  T* mIterator;
  explicit generic_iterator(T* x) : mIterator(x) {}
  generic_iterator& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};
}
namespace eastl {
template <typename T>
inline bool operator!=(const generic_iterator<T>& a, const generic_iterator<T>& b) { return a.mIterator != b.mIterator; }
}
struct Rec20 { int a[5]; };
// ---- items of slice s009515e0 end

// ---- items of slice s00a196f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* f_00f473a0(int size, const char* name, int a, int b, const char* file, int line);
extern void  f_00f47380(void* p);                                        // operator delete
extern void* f_011e0744(void* dst, void* src, unsigned bytes);           // DoInsertValue
extern void* f_00951bb0(void* a, void* b, void* c);
extern void* f_00951bf0(void* a, void* b, void* c);
extern void  f_008f05f0(void* a, void* b, void* c, void* d);            // cdecl (plain ret)
extern void  f_008f0640(void* a, void* b, void* c, void* d);            // cdecl (plain ret; 4th arg unused)
extern void  f_00f96e70(void* a, void* b, void* c);                     // cdecl (plain ret)
extern void  f_00c50ad0(void* a, void* b, void* c);                     // cdecl (plain ret)
static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct ResponseCurveData {
    float mfInputValue;          // 0x00
    float mfOutputValue;         // 0x04
    float mfPreviousInputValue;  // 0x08
    float mfPreviousOutputValue; // 0x0c
    float mfDeltaRatio;          // 0x10
};
struct ResponseCurve {
    ResponseCurveData* mpBegin;   // 0x000
    ResponseCurveData* mpEnd;     // 0x004
    ResponseCurveData* mpCap;     // 0x008
    char               mPad[0x360 - 0x0c];
    int                mNumPoints; // 0x360

    float GetOutputValue(float x);
    bool  GetMaxInput(float* out);
    bool  GetMinInput(float* out);
};
struct FloatVec {
    float* mpBegin;
    float* mpEnd;
    float* mpCap;
    void insert(float* pos, const float& value);
    void pushBack(const float& value);
};
struct RcdVec {
    ResponseCurveData* mpBegin;
    ResponseCurveData* mpEnd;
    ResponseCurveData* mpCap;
    int                mPad;
    void*              mpFixed;
    void insertN(int pos, unsigned count, const ResponseCurveData& value);
    void resize(unsigned n);
};
// ---- items of slice s00a196f0 end

// ---- items of slice s00a1a590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* p);          // operator delete
static __forceinline void** VtOf(void* p) { return *(void***)p; }
void  __cdecl FUN_00ab94c0(void* self, uint32_t cap);    // FloatVec::reserve
void  __cdecl FUN_00a1a1e0(void* vec, float* val);       // FloatVec::push_back
void  __cdecl FUN_00a1a500(void* vec, uint32_t n);       // RcdVec::resize
double __cdecl FUN_0092dc50(const char* s, float* out);  // eastl::atof
int   __cdecl isalnum(int c);                            // CRT import (via 0x13cc510 thunk)
struct FloatVec_s00a1_a590 {
    float* mpBegin;       // +0x00
    float* mpEnd;         // +0x04
    float* mpCapacity;    // +0x08
    float* mpPoolBegin;   // +0x0c
    char   mPool[0x100];  // +0x10
};
struct ResponseCurve_s00a1_a590 {
    ResponseCurveData* mpBegin;    // +0x00
    ResponseCurveData* mpEnd;      // +0x04
    ResponseCurveData* mpCapacity; // +0x08
    uint8_t            pad0c[4];
    ResponseCurveData* mpPoolBegin;// +0x10
    uint8_t            pad14[4];
    ResponseCurveData  mBuffer[42];// +0x18
    uint32_t           mCount;     // +0x360

    bool  SetResponseCurveData(const float* pts, int32_t n);  // 0x00a1a590 (ResponseCurve::SetResponseCurveData)
    bool  InitFromConfiguration(void* cfg, uint32_t key);  // 0x00a1a9d0 (ResponseCurve::InitFromConfiguration)
    ResponseCurve_s00a1_a590();
    uint8_t ParseString(char* str, char sep);
};
// ---- items of slice s00a1a590 end

// @ 0x00951bb0
Rec20* uninitialized_copy_Rec20(const Rec20* first, const Rec20* last, Rec20* dest)
{
  for (; first != last; ++first, ++dest)
    ::new (dest) Rec20(*first);
  return dest;
}

// @ 0x00951bf0
Rec20* copy_Rec20(const Rec20* first, const Rec20* last, Rec20* dest)
{
  for (; first != last; ++first, ++dest)
    *dest = *first;
  return dest;
}

// @ 0x00a1a110
float EA::Audio::ResponseCurve::GetOutputValue(float x) const
{
    int count = mnResponseCurveDataArraySize;
    int hi = count - 1;
    int lo = 0;
    if (hi > 0) {
        ResponseCurveData* base = mResponseCurveDataArray.mpBegin;
        do {
            int mid = (hi + lo) >> 1;
            if (base[mid].mfInputValue > x) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        } while (hi > lo);
        if (lo > 0) {
            if (lo >= count - 1 && x >= base[count - 1].mfInputValue) {
                return base[count - 1].mfOutputValue;
            }
            return (x - base[lo].mfPreviousInputValue) * base[lo].mfDeltaRatio +
                   base[lo].mfPreviousOutputValue;
        }
    }
    return mResponseCurveDataArray.mpBegin[0].mfOutputValue;
}

// @ 0x00a1a1a0
bool ResponseCurve::GetMaxInput(float* out)
{
    ResponseCurveData* end = mpEnd;
    if (mpBegin == end) return false;
    *out = end[-1].mfInputValue;
    return true;
}

// @ 0x00a1a1c0
bool ResponseCurve::GetMinInput(float* out)
{
    ResponseCurveData* begin = mpBegin;
    if (begin == mpEnd) return false;
    *out = begin[0].mfInputValue;
    return true;
}

// @ 0x00a1a1e0
void FloatVec::insert(float* pos, const float& value)
{
    float* end = mpEnd;
    if (end != mpCap) {
        const float* src = &value;
        if (pos <= &value && &value < end) {
            src = &value + 1;
        }
        if (end != 0) {
            end[0] = end[-1];
        }
        unsigned s = (unsigned)((char*)end - 4 - (char*)pos);
        memmove((char*)end - ((s >> 2) * 4), pos, s);
        *pos = *src;
        mpEnd = end + 1;
        return;
    }

    unsigned n = (unsigned)(end - mpBegin);
    unsigned newcap;
    if (n == 0) {
        newcap = 1;
    } else {
        newcap = n * 2;
        if (newcap == 0) {
            float* dst = 0;
            unsigned s = (unsigned)((char*)pos - (char*)mpBegin);
            float* p = (float*)f_011e0744(dst, mpBegin, s);
            p = (float*)((char*)p + ((s >> 2) * 4));
            if (p != 0) *p = value;
            float* oldend = mpEnd;
            float* q = (float*)f_011e0744(p + 1, pos, (unsigned)((char*)oldend - (char*)pos));
            float* oldbegin = mpBegin;
            if (oldbegin != 0 && oldbegin != mpCap) f_00f47380(oldbegin);
            mpBegin = dst;
            mpEnd = (float*)((char*)q + ((((unsigned)((char*)oldend - (char*)pos)) >> 2) * 4));
            mpCap = (float*)((char*)dst + newcap * 4);
            return;
        }
    }

    float* dst = (float*)f_00f473a0((int)(newcap * 4), "EASTL", 0, 0, kAllocFile, 0xd1);
    unsigned s = (unsigned)((char*)pos - (char*)mpBegin);
    float* p = (float*)f_011e0744(dst, mpBegin, s);
    p = (float*)((char*)p + ((s >> 2) * 4));
    if (p != 0) *p = value;
    float* oldend = mpEnd;
    float* q = (float*)f_011e0744(p + 1, pos, (unsigned)((char*)oldend - (char*)pos));
    float* oldbegin = mpBegin;
    if (oldbegin != 0 && oldbegin != mpCap) f_00f47380(oldbegin);
    mpBegin = dst;
    mpEnd = (float*)((char*)q + ((((unsigned)((char*)oldend - (char*)pos)) >> 2) * 4));
    mpCap = (float*)((char*)dst + newcap * 4);
}

// @ 0x00a1a2f0
void RcdVec::insertN(int pos, unsigned count, const ResponseCurveData& value)
{
    char* p = (char*)pos;
    unsigned cap = (unsigned)(((char*)mpEnd - (char*)mpBegin) / 0x14);
    if (cap < count) {
        unsigned oldn = (unsigned)(((char*)mpEnd - (char*)mpBegin) / 0x14);
        unsigned newcap = oldn * 2;
        if (oldn == 0) newcap = 1;
        unsigned total = oldn + count;
        if (total < newcap) total = newcap;
        char* dst = (total == 0) ? 0
                   : (char*)f_00f473a0((int)(total * 0x14), "EASTL", 0, 0, kAllocFile, 0xd1);
        char* mid = (char*)f_00951bb0(mpBegin, p, dst);
        f_008f0640(mid, (char*)count, (void*)&value, p);
        char* newend = (char*)f_00951bb0(p, mpEnd, (char*)mid + count * 0x14);
        char* old = (char*)mpBegin;
        if (old != 0 && old != (char*)mpFixed) f_00f47380(old);
        mpBegin = (ResponseCurveData*)dst;
        mpEnd = (ResponseCurveData*)newend;
        mpCap = (ResponseCurveData*)(dst + total * 0x14);
        return;
    }
    if (count == 0) return;

    ResponseCurveData tmp = value;
    char* end = (char*)mpEnd;
    unsigned existing = (unsigned)(((char*)end - p) / 0x14);
    if (count < existing) {
        unsigned bytes = count * 0x14;
        char* src = end - count * 0x14;
        f_008f05f0((void*)&tmp, src, end, end);
        mpEnd = (ResponseCurveData*)((char*)mpEnd + bytes);
        f_00c50ad0(p, src, end);
        f_00f96e70(p, p + bytes, (void*)&tmp);
        return;
    }
    unsigned tail = count - existing;
    f_008f0640(end, (char*)tail, (void*)&tmp, p);
    mpEnd = (ResponseCurveData*)((char*)mpEnd + tail * 0x14);
    f_008f05f0(p, p, end, mpEnd);
    mpEnd = (ResponseCurveData*)((char*)mpEnd + existing * 0x14);
    f_00f96e70(p, end, (void*)&tmp);
}

// @ 0x00a1a4d0
void FloatVec::pushBack(const float& value)
{
    float* end = mpEnd;
    if (end < mpCap) {
        mpEnd = end + 1;
        if (end != 0) {
            end[0] = value;
            return;
        }
    } else {
        insert(end, value);
    }
}

// @ 0x00a1a500
void RcdVec::resize(unsigned n)
{
    ResponseCurveData* end = mpEnd;
    unsigned have = (unsigned)((int)((char*)end - (char*)mpBegin) / 0x14);
    if (have < n) {
        ResponseCurveData value;
        int* pz = (int*)&value;
        pz[0] = 0; pz[1] = 0; pz[2] = 0; pz[3] = 0; pz[4] = 0;
        insertN((int)end, n - have, value);
        return;
    }
    ResponseCurveData* first = mpBegin + n;
    f_00951bf0(end, end, first);
    mpEnd = (ResponseCurveData*)((char*)end + ((int)((char*)first - (char*)end) / 0x14) * 0x14);
}

// @ 0x00a1a590
bool EA::Audio::ResponseCurve::SetResponseCurveData(float const * pts, int n)
{
    // clear() then resize(): the end pointer is rewound to begin and the vector re-grown
    // to n entries.
    mResponseCurveDataArray.mpEnd = mResponseCurveDataArray.mpBegin;
    FUN_00a1a500(this, (uint32_t)n);

    // The retail body fills four entries per iteration with an identical block; the shape
    // below is the same computation for one entry at a time.
    for (int32_t i = 0; i < n; ++i) {
        float in = pts[i * 2];
        float out = pts[i * 2 + 1];
        float prevIn, prevOut;
        if (i == 0) {
            prevIn = in - 0.0000000001f;
            prevOut = out;
        } else {
            prevIn = pts[i * 2 - 2];
            prevOut = pts[i * 2 - 1];
        }
        float delta = out - prevOut;
        float ratio;
        if (delta != 0.0f) {
            if (delta * 0.0000000001f < (in - prevIn))
                ratio = delta / (in - prevIn);
            else
                ratio = delta;
        } else {
            ratio = 0.0f;
        }
        ResponseCurveData* e = mResponseCurveDataArray.mpBegin + i;
        e->mfInputValue = in;
        e->mfOutputValue = out;
        e->mfPreviousInputValue = prevIn;
        e->mfPreviousOutputValue = prevOut;
        e->mfDeltaRatio = ratio;
    }

    mnResponseCurveDataArraySize = (uint32_t)(((char*)mResponseCurveDataArray.mpEnd - (char*)mResponseCurveDataArray.mpBegin) / 0x14);
    return mResponseCurveDataArray.mpBegin != mResponseCurveDataArray.mpEnd;
}

// @ 0x00a1a9d0
bool ResponseCurve_s00a1_a590::InitFromConfiguration(void* cfg, uint32_t key)
{
    float def[4];
    def[0] = 0.0f;
    def[1] = 0.0f;
    def[2] = 1.0f;
    def[3] = 1.0f;
    SetResponseCurveData(def, 2);

    if (cfg == 0)
        return false;

    float* pData = 0;
    float  count = 0.0f;
    if (!((int(__thiscall*)(void*, uint32_t, void*, void*))VtOf(cfg)[0x44 / 4])(cfg, key, &count, &pData))
        return false;

    SetResponseCurveData(pData, (int)count >> 1);
    return true;
}

// @ 0x00a1aa50
ResponseCurve_s00a1_a590::ResponseCurve_s00a1_a590()
{
    mpPoolBegin = &mBuffer[0];
    mpEnd = &mBuffer[0];
    mpBegin = &mBuffer[0];
    mpCapacity = &mBuffer[42];
    mCount = 0;

    float def[4];
    def[0] = 0.0f;
    def[1] = 0.0f;
    def[2] = 1.0f;
    def[3] = 1.0f;
    SetResponseCurveData(def, 2);
}

// @ 0x00a1aad0
uint8_t ResponseCurve_s00a1_a590::ParseString(char* str, char sep)
{
    // Without an explicit separator, take the first non-alphanumeric character.
    if (sep == '\0') {
        for (char* p = str; *p != '\0'; ++p) {
            if (isalnum((int)*p) == 0) {
                sep = *p;
                break;
            }
        }
    }

    // Count the separator occurrences (plus one).
    uint32_t count = 1;
    for (char* p = str; *p != '\0'; ++p) {
        if (*p == sep)
            ++count;
    }

    // An odd number of fields cannot form (x,y) pairs.
    if ((count & 1) != 0)
        return 0;

    FloatVec_s00a1_a590 vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;
    vec.mpPoolBegin = (float*)vec.mPool;
    FUN_00ab94c0(&vec, count);

    uint32_t i = 0;
    for (;;) {
        char buf[128];
        uint32_t j = 0;
        while (str[i] != '\0' && str[i] != sep) {
            if (j < 0x7f) {
                buf[j] = str[i];
                ++j;
            }
            ++i;
        }
        buf[j] = '\0';

        float value = (float)FUN_0092dc50(buf, 0);

        if (vec.mpEnd < vec.mpCapacity)
            *vec.mpEnd++ = value;
        else
            FUN_00a1a1e0(&vec, &value);

        if (str[i] == '\0')
            break;
        ++i;
    }

    uint8_t ok = SetResponseCurveData(vec.mpBegin, (int32_t)(count / 2));

    if (vec.mpBegin != 0 && vec.mpBegin != (float*)vec.mPool)
        FUN_00f47380(vec.mpBegin);
    return ok;
}
