// Slice s00bc5730 -- loads a property-file record (instance/group) into the large
// fixed_vector-based description struct whose ctor is 0x00bc4630 (see s00bc34c0 "Big").
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (cmov + SSE stores; no EH frame for the
// string locals; a 256-byte char buffer without a security cookie).
#include "types.h"
#include <string.h>

typedef unsigned short char16;

extern "C" void __cdecl operator_delete_arr(void* p);              // 0x00f47380 (operator delete[])
extern const char16 gEmptyString16[1];                              // 0x01667bac

// ---- EASTL strings (16 bytes: begin/end/capacity + allocator) ---------------------------
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t mAllocator;
    string16() {
        mpBegin = mpEnd = (char16*)gEmptyString16;
        mpCapacity = mpBegin + 1;
    }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_arr(mpBegin);
        }
    }
};
struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    ~string8() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_arr(mpBegin);
        }
    }
    const char* c_str() const { return mpBegin; }
};
string8 ConvertToString8(const string16& s);                        // 0x0093c570 EA::ConvertToString8

struct fixed_string32 {                                             // fixed_string<char, 32>
    char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator; char* mpBuffer;
    char mBuffer[32];
    void assign(const char* first, const char* last);               // 0x00836910
    fixed_string32& operator=(const char* p) {
        assign(p, p + strlen(p));
        return *this;
    }
};

// ---- property access -------------------------------------------------------------------
struct Property {
    uint32_t mData;      // +0x00 (or pointer to the data when (mFlags & 0x30))
    uint32_t pad04[3];
    uint16_t mFlags;     // +0x10
    uint16_t mType;      // +0x12 (1 bool, 10 uint32, 13 float)
};
template <typename T>
static inline T& PropData(Property* p) {
    T* data = (T*)p;
    if (p->mFlags & 0x30)
        data = *(T**)p;
    return *data;
}

struct cPropertyList {
    virtual void AddRef();
    virtual void Release();
    virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5(); virtual void vf6();
    virtual bool HasProperty(uint32_t id);                          // slot 7 (+0x1c)
    virtual void vf8();
    virtual bool GetProperty(uint32_t id, Property** out);          // slot 9 (+0x24)
};
struct IPropertyManager {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3();
    virtual void vf4(); virtual void vf5(); virtual void vf6(); virtual void vf7();
    virtual void vf8(); virtual void vf9(); virtual void vf10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** out);  // slot 11
};
IPropertyManager* PropertyManager();                                // 0x0067de30 SP::PropertyManager

static inline uint32_t PropUInt32(cPropertyList* list, uint32_t id, uint32_t def) {
    Property* p;
    if (list && list->GetProperty(id, &p) && p->mType == 10)
        return PropData<uint32_t>(p);
    return def;
}
static inline float PropFloat(cPropertyList* list, uint32_t id, float def) {
    Property* p;
    if (list && list->GetProperty(id, &p) && p->mType == 13)
        return PropData<float>(p);
    return def;
}
static inline bool PropBool(cPropertyList* list, uint32_t id, bool def) {
    Property* p;
    if (list && list->GetProperty(id, &p) && p->mType == 1)
        return PropData<bool>(p);
    return def;
}

struct Vector2 { float x, y; Vector2() {} Vector2(float a, float b) : x(a), y(b) {} };
struct Vector3 { float x, y, z; Vector3() {} };

bool GetPropertyAsString16(cPropertyList* list, uint32_t id, string16& out);                 // 0x006a1400
bool GetPropertyAsUint32Array(cPropertyList* list, uint32_t id, int* count, uint32_t** out); // 0x006a0840
bool GetPropertyAsFloatArray(cPropertyList* list, uint32_t id, int* count, float** out);     // 0x006a08b0
bool GetPropertyAsVector2Array(cPropertyList* list, uint32_t id, int* count, Vector2** out); // 0x006a0920
bool GetPropertyAsVector3Array(cPropertyList* list, uint32_t id, int* count, Vector3** out); // 0x006a0ae0
bool GetPropertyAsBoolArray(cPropertyList* list, uint32_t id, int* count, bool** out);       // 0x006a0760

// ---- EASTL fixed_vector (begin/end/capacity, allocator words, inline buffer) -------------
struct random_access_iterator_tag {};

template <typename T> struct is_pod_copy { enum { value = 0 }; };
template <> struct is_pod_copy<uint32_t> { enum { value = 1 }; };
template <> struct is_pod_copy<float> { enum { value = 1 }; };
template <> struct is_pod_copy<bool> { enum { value = 1 }; };

template <typename T, int N>
struct fixed_vector {
    typedef T value_type;
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    T mBuffer[N];

    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }

    void DoInsertValues(T* position, size_type n, const value_type& value);   // out of line
    void DoInsertFromIterator(T* position, const T* first, const T* last,
                              random_access_iterator_tag);                    // out of line
    void resize(size_type n);                                                 // out of line (Elem98)

    void insert(T* position, const T* first, const T* last) {
        DoInsertFromIterator(position, first, last, random_access_iterator_tag());
    }
    T* erase(T* first, T* last) {
        if (is_pod_copy<T>::value) {
            memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        } else {
            T* dst = first;
            for (T* src = last; src != mpEnd; ++src, ++dst)
                *dst = *src;
        }
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void resize_inline(size_type n) {
        if (n > (size_type)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (size_type)(mpEnd - mpBegin), value_type());
        else
            erase(mpBegin + n, mpEnd);
    }
};

struct Elem16 { uint32_t a, b, c, d; };
typedef fixed_vector<Elem16, 8> Elem98;            // 0x98 bytes; resize = 0x00bc45c0
typedef char chk_elem98[(sizeof(Elem98) == 0x98) ? 1 : -1];

// The description struct filled here (layout: s00bc34c0 "Big", ctor 0x00bc4630).
struct PropRecord {
    uint32_t mValue0;                              // +0x000
    int mCount;                                    // +0x004
    fixed_vector<uint32_t, 8> mIndices;            // +0x008
    fixed_vector<Vector2, 32> mVec2A;              // +0x040
    fixed_vector<float, 32> mAngles;               // +0x158
    fixed_vector<bool, 32> mFlags;                 // +0x1f0
    fixed_vector<Vector3, 2> mVec3;                // +0x228
    fixed_vector<Vector2, 2> mVec2B;               // +0x258
    fixed_vector<Elem98, 8> mLists;                // +0x280; resize = 0x00bc5340
    fixed_string32 mName;                          // +0x758
    float mF78C;                                   // +0x78c
    float mF790;                                   // +0x790
    uint32_t mU794;                                // +0x794
    uint32_t mU798;                                // +0x798
    bool mB79C;                                    // +0x79c
    bool mB79D;                                    // +0x79d
    uint32_t mU7A0;                                // +0x7a0
    uint32_t mU7A4;                                // +0x7a4
    uint32_t mU7A8;                                // +0x7a8
    uint32_t mBitMask;                             // +0x7ac
    uint32_t mFourCC;                              // +0x7b0
};
typedef char chk_rec[(sizeof(PropRecord) == 0x7b4) ? 1 : -1];

extern const float kAngleScale;                    // 0x0168ab34 (runtime-initialised)

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

// @ 0x00bc5730
bool ReadPropRecord(uint32_t instance, uint32_t group, PropRecord* out) {
    AutoRefCount<cPropertyList> list;
    if (!PropertyManager()->GetPropertyList(instance, group, &list.mpObject))
        return false;

    string16 name;
    int count = 0;
    for (int i = 1; i <= 12; ++i) {
        if (list.mpObject->HasProperty(0x0486668f + i))
            count = i;
    }
    if (count <= 0)
        return false;

    out->mValue0 = PropUInt32(list.mpObject, 0x048665c7, 0);
    if (GetPropertyAsString16(list.mpObject, 0x04ab07c9, name))
        out->mName = ConvertToString8(name).c_str();

    out->mLists.resize(count);
    for (int k = 0; k < count; ++k) {
        Elem98& e = out->mLists[k];
        int n = 0;
        uint32_t* values = 0;
        if (GetPropertyAsUint32Array(list.mpObject, 0x04866690 + k, &n, &values)) {
            e.resize(n);
            for (int i = 0; i < n; ++i)
                e[i].a = values[i];

            int m = 0;
            uint32_t* v1;
            if (GetPropertyAsUint32Array(list.mpObject, 0x048666a0 + k, &m, &v1)) {
                if (m > n)
                    m = n;
                for (int i = 0; i < m; ++i)
                    e[i].b = v1[i];
            }
            for (int i = m; i < n; ++i)
                e[i].b = 0;

            m = 0;
            uint32_t* v2;
            if (GetPropertyAsUint32Array(list.mpObject, 0x048666b0 + k, &m, &v2)) {
                if (m > n)
                    m = n;
                for (int i = 0; i < m; ++i)
                    e[i].c = v2[i];
            }
            for (int i = m; i < n; ++i)
                e[i].c = 0xffffffff;

            uint32_t* v3;
            if (GetPropertyAsUint32Array(list.mpObject, 0x048666c0 + k, &m, &v3)) {
                if (m > n)
                    m = n;
                for (int i = 0; i < m; ++i)
                    e[i].d = v3[i];
            }
            for (int i = m; i < n; ++i)
                e[i].d = 0;
        }
    }

    int total;
    uint32_t* indices;
    if (GetPropertyAsUint32Array(list.mpObject, 0x04877bf5, &total, &indices)) {
        out->mCount = total;
        out->mIndices.insert(out->mIndices.begin(), indices, indices + total);
    } else {
        out->mCount = count;
        total = count;
        out->mIndices.resize_inline(count);
        for (int i = 0; i < total; ++i)
            out->mIndices[i] = i;
    }

    int n;
    out->mVec2A.resize_inline(total);
    Vector2* vec2;
    if (GetPropertyAsVector2Array(list.mpObject, 0x04879d5a, &n, &vec2)) {
        if (n > total)
            n = total;
        int i;
        for (i = 0; i < n; ++i)
            out->mVec2A[i] = vec2[i];
        for (; i < total; ++i)
            out->mVec2A[i] = Vector2(0.0f, 0.0f);
    }

    out->mAngles.resize_inline(total);
    float* angles;
    if (GetPropertyAsFloatArray(list.mpObject, 0x049a2146, &n, &angles)) {
        if (n > total)
            n = total;
        int i;
        for (i = 0; i < n; ++i)
            out->mAngles[i] = angles[i] * kAngleScale * 0.0027777778f;
        for (; i < total; ++i)
            out->mAngles[i] = 0.0f;
    }

    out->mFlags.resize_inline(total);
    bool* flags;
    int i = 0;
    if (GetPropertyAsBoolArray(list.mpObject, 0x0611b46c, &n, &flags)) {
        if (n > total)
            n = total;
        for (; i < n; ++i)
            out->mFlags[i] = flags[i];
    }
    for (; i < total; ++i)
        out->mFlags[i] = false;

    out->mF78C = PropFloat(list.mpObject, 0x048a40a6, 0.0f);
    out->mF790 = PropFloat(list.mpObject, 0x048a40a7, 100.0f);
    out->mU794 = PropUInt32(list.mpObject, 0x049a3514, 0);
    out->mU798 = PropUInt32(list.mpObject, 0x04f38120, 0);
    out->mU7A0 = PropUInt32(list.mpObject, 0x04f38139, 0);
    out->mB79C = PropBool(list.mpObject, 0x05107c07, false);
    out->mU7A4 = PropUInt32(list.mpObject, 0x0564cc3e, 0xffffffff);
    out->mU7A8 = PropUInt32(list.mpObject, 0x0564e207, 0);
    out->mB79D = PropBool(list.mpObject, 0x05b05121, false);

    out->mFourCC = 0;
    string16 code;
    if (GetPropertyAsString16(list.mpObject, 0x057fb0b6, code)) {
        string8 code8 = ConvertToString8(code);
        char buf[256];
        strcpy(buf, code8.c_str());
        out->mFourCC = ((((uint32_t)(uint8_t)buf[3] << 8 | (uint8_t)buf[2]) << 8 |
                         (uint8_t)buf[1]) << 8) | (uint8_t)buf[0];
    }

    out->mBitMask = 0;
    int nBits = 0;
    uint32_t* bits = 0;
    if (GetPropertyAsUint32Array(list.mpObject, 0x056cd5ea, &nBits, &bits)) {
        for (int b = 0; b < nBits; ++b)
            out->mBitMask |= 1 << bits[b];
    }

    int nPos;
    Vector3* pos;
    if (GetPropertyAsVector3Array(list.mpObject, 0x0508d625, &nPos, &pos)) {
        out->mVec3.clear();
        out->mVec3.insert(out->mVec3.begin(), pos, pos + nPos);
        out->mVec2B.resize_inline(nPos);
        int nUV;
        Vector2* uv;
        if (GetPropertyAsVector2Array(list.mpObject, 0x0508d626, &nUV, &uv)) {
            if (nUV > nPos)
                nUV = nPos;
            int j;
            for (j = 0; j < nUV; ++j)
                out->mVec2B[j] = uv[j];
            // The original's zero-fill writes into mVec2A (+0x40), not mVec2B.
            for (; j < nPos; ++j)
                out->mVec2A[j] = Vector2(0.0f, 0.0f);
        }
    }
    return true;
}
