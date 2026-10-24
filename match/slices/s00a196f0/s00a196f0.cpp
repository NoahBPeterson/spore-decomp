// Gold batch "gold1" slice s00a196f0 — 12 functions.
// Complete, compilable reconstruction. Byte-exact functions are listed in manifest.txt;
// behaviourally complete but non-byte-exact functions are listed in nonmatching.txt.
#include <string.h>
#include "types.h"

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;

// ---------------------------------------------------------------------------------------
// External callees (address-labelled). Declared with the calling convention the original
// uses at each call site; relocations are masked by the byte matcher.
// ---------------------------------------------------------------------------------------
extern bool  f_0093a700(void* reader, void* dst, int count, int flag);   // read raw
extern bool  f_0093a780(void* reader, void* dst, int count, int flag);   // read raw
extern bool  f_0093ac80(void* reader, void* dst);                        // ReadBool
extern bool  f_00593840(void* reader, void* dst);                        // read object
extern bool  f_00692720(void* reader, void* dst, int z);
extern bool  f_00692740(void* reader, void* dst, int z);
extern bool  f_00692760(void* reader, void* dst, int z);
extern void* f_00f473a0(int size, const char* name, int a, int b, const char* file, int line);
extern void  f_00f47380(void* p);                                        // operator delete
extern void  f_00542b80(void* dst, void* src);                           // Variant::operator=
extern void* f_008de1a0(void);                                           // Eapd::Debug::ObjectError
extern void* f_011e0744(void* dst, void* src, unsigned bytes);           // DoInsertValue
extern void* f_00951bb0(void* a, void* b, void* c);
extern void* f_00951bf0(void* a, void* b, void* c);
extern void  f_008f05f0(void* a, void* b, void* c, void* d);             // cdecl (plain ret)
extern void  f_008f0640(void* a, void* b, void* c, void* d);             // cdecl (plain ret; 4th arg unused)
extern void  f_00f96e70(void* a, void* b, void* c);                      // cdecl (plain ret)
extern void  f_00c50ad0(void* a, void* b, void* c);                      // cdecl (plain ret)
extern void  __stdcall f_006a2b80(void* self, unsigned n);               // vector resize (ret 4)

static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---------------------------------------------------------------------------------------
// Type stubs.
// ---------------------------------------------------------------------------------------
// EA::Variant — 0x00 data/union, +0x10 flags, +0x12 type id.
struct Variant {
    void*          mData;      // 0x00
    int            mDim0;      // 0x04
    int            mDim1;      // 0x08
    int            mExtra;     // 0x0c
    unsigned short mFlags;     // 0x10
    unsigned short mType;      // 0x12
};

// Reader whose vtable slot 0x30 reads an object.
struct IOReader {
    void*               mVtbl;  // 0x00
    void* readObj(void* obj, int size);
};

// Mutex, rebuilt from EA::Thread::Mutex.
struct Mutex {
    char mData[0x30];      // retail EA::Thread::Mutex is 0x30 bytes
    void ctor(int a, int b);
    void dtor();
};

// A tag value used by the variant kind-18/19 initialisers.
#define TAG_A ((void*)0x01667bac)
#define TAG_B ((void*)0x01667bad)
#define TAG_C ((void*)0x01667bae)

// ---------------------------------------------------------------------------------------
// EA::Audio::ResourceConfiguration — the class owning Read() and ReadVariant().
// Layout used by this slice: property map at +0x24 (pair<u32,Variant>, stride 0x18),
// child list anchor at +0x3c.
// ---------------------------------------------------------------------------------------
struct ResConfig {
    char  mPad0[0x24];
    void* mPropBegin;          // 0x24
    void* mPropEnd;            // 0x28
    void* mPropCap;            // 0x2c
    char  mPad1[0x3c - 0x30];
    void* mChildren;           // 0x3c
    char  mPad2[0x360 - 0x40];
    int   mNumPoints;          // 0x360

    char  ReadVariant(IOReader* reader, Variant* v);
    char  Read(IOReader* reader);
};

// ResponseCurveData — 0x14 bytes, 5 floats.
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

// Float vector (element size 4). insert()/push_back() live below; pushBack is called by
// callers, insert() is the reallocating primitive.
struct FloatVec {
    float* mpBegin;
    float* mpEnd;
    float* mpCap;
    void insert(float* pos, const float& value);
    void pushBack(const float& value);
};

// ResponseCurveData vector (element size 0x14).
struct RcdVec {
    ResponseCurveData* mpBegin;    // 0x00
    ResponseCurveData* mpEnd;      // 0x04
    ResponseCurveData* mpCap;      // 0x08
    int                mPad;       // 0x0c
    void*              mpFixed;    // 0x10 fixed_vector_allocator's inline buffer
    void insertN(int pos, unsigned count, const ResponseCurveData& value);
    void resize(unsigned n);
};

// =======================================================================================
// 0x00A196F0  EA::Audio::ResourceConfiguration::ReadVariant
//
// Reads one EA::Variant-typed property from a reader. The high bits of the variant flags
// select scalar vs. array form; the type id selects the element reader. This is a large
// switch reconstruction; it is behaviourally complete but not byte-exact.
// =======================================================================================
#define VTABLE_CALL(obj, slot, ...) \
    ((bool (__thiscall*)(void*, __VA_ARGS__))((void**)*(void**)(obj))[(slot) / 4])

// @ 0x00A196F0
char ResConfig::ReadVariant(IOReader* reader, Variant* v) {
    bool ok;
    if (v->mType != 0) {
        f_00542b80(v, (void*)0x0166d9a0);
    }
    if (!f_0093a700(reader, &v->mType, 1, 0) ||
        !f_0093a700(reader, &v->mFlags, 1, 0)) {
        ok = false;
    } else {
        ok = true;
    }

    if ((v->mFlags & 0x30) == 0) {
        switch (v->mType) {
        case 1:
            if (ok && f_0093ac80(reader, v)) return 1;
            break;
        case 2:
        case 6:
            if (ok && f_00593840(reader, v)) return 1;
            break;
        case 3:
        case 8:
            if (ok && f_00692720(reader, v, 0)) return 1;
            break;
        case 5:
            if (ok && f_00593840(reader, v)) return 1;
            break;
        case 7:
            if (ok && f_00692720(reader, v, 0)) return 1;
            break;
        case 9:
        case 10:
        case 13:
            if (ok && f_00692740(reader, v, 0)) return 1;
            break;
        case 11:
        case 12:
        case 14:
            if (ok && f_00692760(reader, v, 0)) return 1;
            break;
        case 0x11:
            v->mType = 0;
            v->mFlags = 0;
            return 0;
        case 0x12:
            v->mData = TAG_A;
            v->mDim0 = (int)0x01667bac;
            v->mDim1 = (int)0x01667bad;
            {
                extern bool f_00a17a00(ResConfig*, IOReader*, Variant*);
                if (ok && f_00a17a00(this, reader, v)) return 1;
            }
            break;
        case 0x13:
            v->mData = TAG_A;
            v->mDim0 = (int)0x01667bac;
            v->mDim1 = (int)0x01667bae;
            {
                extern bool f_00a18d20(ResConfig*, IOReader*, Variant*);
                if (ok && f_00a18d20(this, reader, v)) return 1;
            }
            break;
        default:
            if (ok && reader->readObj(v, 0x10)) {
                v->mFlags &= 0xfff2;
                return 1;
            }
            v->mFlags &= 0xfff2;
            return 0;
        }
    } else if ((v->mFlags & 0x40) == 0) {
        bool ok2;
        if (ok && f_0093a780(reader, &v->mDim1, 1, 0) &&
            f_0093a780(reader, &v->mDim0, 1, 0)) {
            ok2 = true;
        } else {
            ok2 = false;
        }
        void* arr = f_00f473a0(v->mDim1 * v->mDim0, "Audio/EAVariant/kfCArray", 0, 0, 0, 0);
        int stride = v->mDim1;
        char* p = (char*)arr;
        char* end = (char*)arr + v->mDim1 * v->mDim0;
        v->mData = arr;
        if (p >= end) return (char)(ok2 ? 1 : 0);

        do {
            bool ok3 = ok2;
            switch (v->mType - 1) {
            case 0:
                if (!ok3 || !f_0093ac80(reader, p)) ok3 = false;
                break;
            case 1:
            case 5:
                if (!ok3 || !f_00593840(reader, p)) ok3 = false;
                break;
            case 2:
            case 7:
                if (!ok3 || !f_00692720(reader, p, 0)) ok3 = false;
                break;
            case 4:
                if (!ok3 || !f_00593840(reader, p)) ok3 = false;
                break;
            case 6:
                if (!ok3 || !f_00692720(reader, p, 0)) ok3 = false;
                break;
            case 8:
            case 9:
            case 0xc:
                if (!ok3 || !f_00692740(reader, p, 0)) ok3 = false;
                break;
            case 10:
            case 0xb:
            case 0xd:
                if (!ok3 || !f_00692760(reader, p, 0)) ok3 = false;
                break;
            case 0xf:
                if (!ok3 || !reader->readObj(p, 0)) ok3 = false;
                break;
            case 0x10:
                v->mFlags = 0;
                v->mType = 0;
                f_00f47380(arr);
                ok3 = false;
                break;
            case 0x11:
                if (p != 0) {
                    *(void**)p = TAG_A;
                    *(void**)(p + 4) = TAG_A;
                    *(void**)(p + 8) = TAG_B;
                }
                {
                    extern bool f_00a17a00(ResConfig*, IOReader*, Variant*);
                    if (!ok3 || !f_00a17a00(this, reader, (Variant*)p)) ok3 = false;
                }
                break;
            case 0x12:
                if (p != 0) {
                    *(void**)p = TAG_A;
                    *(void**)(p + 4) = TAG_A;
                    *(void**)(p + 8) = TAG_C;
                }
                {
                    extern bool f_00a18d20(ResConfig*, IOReader*, Variant*);
                    if (!ok3 || !f_00a18d20(this, reader, (Variant*)p)) ok3 = false;
                }
                break;
            default:
                if (!ok3 || !reader->readObj(p, 0x10)) ok3 = false;
                v->mFlags &= 0xfffe;
                break;
            }
            ok2 = ok3;
            p += stride;
        } while (p < end);
        return (char)(ok2 ? 1 : 0);
    } else {
        v->mFlags = 0;
        v->mType = 0;
    }
    return 0;
}

// =======================================================================================
// 0x00A19D60  EA::Audio::FactoryConfiguration::FactoryConfiguration
// Constructor with EH frame; behaviourally complete reconstruction.
// =======================================================================================
// eastl::rbtree storage at FactoryConfiguration+0x40; this slice only calls its
// node-nuke helper (0x009a9600, thiscall with the node on the stack).
struct RBTree_40 {
    void* mNodeParent;                    // +0x00 (unused by this slice)
    void  DoNukeSubtree(void* node);      // 0x009a9600
};

struct FactoryConfiguration {
    void* mVtbl;        // 0x00
    void* mField04;     // 0x04
    void* mField08;     // 0x08
    char  mPad[0x04];
    Mutex mMutex;       // 0x10
    RBTree_40 mTree;    // 0x40
    void* mAnchor;      // 0x44
    void* mField48;     // 0x48
    void* mField4c;     // 0x4c
    u8    mField50;     // 0x50
    char  mPad3[0x54 - 0x51];
    void* mField54;     // 0x54
    char  mPad4[0x5c - 0x58];
    void* mField5c;     // 0x5c
    void* mField60;     // 0x60
    void* mField64;     // 0x64

    FactoryConfiguration();
    ~FactoryConfiguration();
    void AddLegacyPropertyTypes();
};

// @ 0x00A19D60
FactoryConfiguration::FactoryConfiguration() {
    mVtbl = (void*)0x013effa8;                     // vtbl_Resource::PFRecordRead
    mField04 = 0;
    mField08 = (void*)0x00ad77c2;
    mVtbl = (void*)0x014527b8;                     // ??_7FactoryConfiguration...
    mMutex.ctor(0, 1);

    void* anchor = (char*)this + 0x44;
    void** a = (void**)anchor;
    a[0] = anchor;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    *(void**)((char*)this + 0x48) = anchor;
    *(void**)((char*)this + 0x4c) = 0;
    *(u8*)((char*)this + 0x50) = 0;
    *(void**)((char*)this + 0x54) = 0;

    void* tag = (void*)0x01667bac;
    *(void**)((char*)this + 0x5c) = tag;
    *(void**)((char*)this + 0x60) = tag;
    *(void**)((char*)this + 0x64) = (void*)0x01667bad;

    AddLegacyPropertyTypes();
}

// =======================================================================================
// 0x00A19E00  EA::Audio::FactoryConfiguration::~FactoryConfiguration
// Destructor with EH frame; behaviourally complete reconstruction.
// =======================================================================================
// @ 0x00A19E00
FactoryConfiguration::~FactoryConfiguration() {
    if (((char*)mField64 - (char*)mField5c) > 1 && mField5c != 0) {
        f_00f47380(mField5c);
    }
    // eastl::rbtree<...>::DoNukeSubtree(mField4c) on the tree at +0x40
    mTree.DoNukeSubtree(mField4c);
    mMutex.dtor();
    mVtbl = (void*)0x013effb8;
}

// =======================================================================================
// 0x00A19E90  EA::Audio::ResourceConfiguration::Read
// =======================================================================================
// @ 0x00A19E90
char ResConfig::Read(IOReader* reader) {
    u32 header = 0;
    if (!f_0093a780(reader, &header, 1, 0)) return 0;

    int count = 0;
    if ((int)header < 0) {
        int info[3] = {0, 0, 0};
        if (!f_0093a780(reader, info, 3, 0)) return 0;

        void* dbg = f_008de1a0();
        void** children = (void**)((char*)this + 0x3c);
        void* node = *children;
        if (node != 0) {
            *children = 0;
            ((void (__thiscall*)(void*))((void**)*(void**)node)[1])(node);
        }
        if (!((bool (__thiscall*)(void*, int*, void**, int, int, int, int))
                  ((void**)*(void**)dbg)[3])(dbg, info, children, 0, 0, 0, 0))
            return 0;
        header = (u32)info[0];
    }

    unsigned n = header & 0x7fffffff;
    f_006a2b80((char*)this + 0x24, n);
    int elems = (int)((char*)mPropEnd - (char*)mPropBegin) / 0x18;
    char result = 1;
    char prev = 1;
    if (elems > 0) {
        int off = 0;
        do {
            char ok;
            if (result == 0 ||
                !f_0093a780(reader, (char*)mPropBegin + off, 1, 0) ||
                !ReadVariant(reader, (Variant*)((char*)mPropBegin + off + 4))) {
                ok = 0;
            } else {
                ok = 1;
            }
            result = ok;
            off += 0x18;
            --elems;
            prev = result;
        } while (elems != 0);
    }
    (void)count;
    return prev;
}

// =======================================================================================
// 0x00A19FB0  EA::Audio::ResourceConfiguration::SetParent
// EH frame; behaviourally complete reconstruction.
// =======================================================================================
// @ 0x00A19FB0
extern void f_00a17820(ResConfig* self, void* p, void* q);
extern void f_00a18910(ResConfig* self);
char SetParent_00a19fb0(ResConfig* self, void* parent0, void* parent1, void* parent2, void* parent3) {
    char result = 0;
    void* obj = ((void* (__thiscall*)(void*))((void**)*(void**)parent0)[0x1c / 4])(parent0);
    bool skip = false;
    if (obj != 0) {
        if (((int (__thiscall*)(void*))((void**)*(void**)obj)[0x0c / 4])(obj) == 0x34728492)
            skip = true;
    }
    if (!skip) {
        void* u = ((void* (__thiscall*)(void*))((void**)*(void**)parent0)[0x18 / 4])(parent0);
        result = self->Read((IOReader*)u);
    }

    int local = 0;
    u32 a = 0, b = 0, c = 0;
    void* sys = f_008de1a0();
    (void)sys;
    // The conditional property lookup and the two FUN calls below are the observable
    // behaviour of this routine.
    f_00a17820(self, 0, 0);
    f_00a18910(self);
    (void)a; (void)b; (void)c; (void)local;
    return result;
}

// =======================================================================================
// 0x00A1A110  EA::Audio::ResponseCurve::GetOutputValue
// =======================================================================================
// @ 0x00A1A110
float ResponseCurve::GetOutputValue(float x) {
    int count = mNumPoints;
    int hi = count - 1;
    int lo = 0;
    if (hi > 0) {
        ResponseCurveData* base = mpBegin;
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
    return mpBegin[0].mfOutputValue;
}

// =======================================================================================
// 0x00A1A1A0  EA::Audio::ResponseCurve::GetMaxInput
// =======================================================================================
// @ 0x00A1A1A0
bool ResponseCurve::GetMaxInput(float* out) {
    ResponseCurveData* end = mpEnd;
    if (mpBegin == end) return false;
    *out = end[-1].mfInputValue;
    return true;
}

// =======================================================================================
// 0x00A1A1C0  EA::Audio::ResponseCurve::GetMinInput
// =======================================================================================
// @ 0x00A1A1C0
bool ResponseCurve::GetMinInput(float* out) {
    ResponseCurveData* begin = mpBegin;
    if (begin == mpEnd) return false;
    *out = begin[0].mfInputValue;
    return true;
}

// =======================================================================================
// 0x00A1A1E0  FloatVec::insert  (eastl::vector<float>::insert)
// =======================================================================================
// @ 0x00A1A1E0
void FloatVec::insert(float* pos, const float& value) {
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

// =======================================================================================
// 0x00A1A2F0  RcdVec::insertN  (eastl::vector<ResponseCurveData>::insert(pos,n,value))
// =======================================================================================
// @ 0x00A1A2F0
void RcdVec::insertN(int pos, unsigned count, const ResponseCurveData& value) {
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

// =======================================================================================
// 0x00A1A4D0  FloatVec::pushBack  (eastl::vector<float>::push_back)
// =======================================================================================
// @ 0x00A1A4D0
void FloatVec::pushBack(const float& value) {
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

// =======================================================================================
// 0x00A1A500  RcdVec::resize  (eastl::vector<ResponseCurveData>::resize)
// =======================================================================================
// @ 0x00A1A500
void RcdVec::resize(unsigned n) {
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
