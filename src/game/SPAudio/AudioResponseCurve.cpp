// src/game/SPAudio/AudioResponseCurve.cpp -- migrated from slice(s) s00a196f0, s009515e0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioResponseCurve.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <new>
#include "EA/Audio/ResponseCurve.h"

// ---- items of slice s009515e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
template <typename T>
struct generic_iterator {
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
extern void  __stdcall f_008f05f0(void* a, void* b, void* c, void* d);   // ret 0x10
extern void  __stdcall f_008f0640(void* a, void* b, void* c, void* d);   // ret 0x10
extern void  __stdcall f_00f96e70(void* a, void* b, void* c);            // ret 0xc
extern void  __stdcall f_00c50ad0(void* a, void* b, void* c);            // ret 0xc
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
    void insertN(int pos, unsigned count, const ResponseCurveData& value);
    void resize(unsigned n);
};
// ---- items of slice s00a196f0 end

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
        if (old != 0 && old != (char*)mpCap) f_00f47380(old);
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
    int have = (int)((char*)end - (char*)mpBegin) / 0x14;
    if (have < (int)n) {
        ResponseCurveData value = {};
        insertN((int)end, n - have, value);
        return;
    }
    ResponseCurveData* first = mpBegin + n;
    f_00951bf0(end, end, first);
    mpEnd = (ResponseCurveData*)((char*)end + ((int)((char*)first - (char*)end) / 0x14) * 0x14);
}
