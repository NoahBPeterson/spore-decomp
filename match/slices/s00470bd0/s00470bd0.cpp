// Slice s00470bd0: editor bound-info helpers (SP::EditorUtils::AddInitialBoundInfo and friends).
// Built unoptimized: /Od /Ob1 /arch:SSE. Callees are declared with the convention seen at the call site.
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned long long u64;

struct Vec3 {
    float v[3];
    float& operator[](int i) { return v[i]; }
};
struct Vec2 {
    union { float v[2]; struct { float x, y; }; };
    float& operator[](int i) { return v[i]; }
};
struct Vec4 {
    float v[4];
    Vec4(float a, float b, float c, float d) { v[0] = a; v[1] = b; v[2] = c; v[3] = d; }
    float& operator[](int i) { return v[i]; }
};
struct Box {                 // 0x18 bytes: min then max
    Vec3 mMin;
    Vec3 mMax;
    void Reset();                                  // 0x409c00
    void AddPoint(const Box* b);                   // 0x43f050 (extends by another box)
    void SetCenterRadius(const Vec3* c, float r);  // 0x409ce0
};
struct Mat9 { float m[9]; };
struct Transform {
    u16 mFlags; u16 mCount;
    Vec3 mPos;
    float mScale;
    Mat9 mRot;
    Transform();                                   // 0x409930
    void SetScale(float s) { mScale = s; mCount++; }
    void SetRotation(const Mat9& r) { mRot = r; mFlags |= 2; mCount++; }
    void SetPosition(const Vec3& p) { mPos = p; mFlags |= 4; mCount++; }
};

extern Vec3 g_Vec3Zero;      // 0x15d4034
extern float g_DefaultX;     // 0x15d4104
extern float g_DefaultY;     // 0x15d4108
extern float g_Epsilon;      // 0x13ec478 (0.05)
extern float g_Zero;         // 0x1485378
extern float g_Third;        // 0x13eb8c8 (0.3)

// ---- max of four floats ----
inline float Max2(Vec4* p, int i, int j)
{
    float r;
    if ((*p)[i] >= (*p)[j]) r = (*p)[i]; else r = (*p)[j];
    return r;
}
inline float MaxF(const float& a, const float& b)
{
    float r;
    if (a >= b) r = a; else r = b;
    return r;
}
// @ 0x00470f20
float FUN_00470f20(Vec4* p)
{
    float l = Max2(p, 0, 1);
    float r = Max2(p, 2, 3);
    return MaxF(l, r);
}

struct Range { Box* mp; int mCount; float mBest; };

// @ 0x00470bd0
Vec2* FUN_00470bd0(Vec2* out, Box* a, int na, Box* b, int nb, float z)
{
    if (a == 0 || b == 0) {
        out->x = g_DefaultX;
        out->y = g_DefaultY;
        return out;
    }
    Vec2 result;
    result.x = g_DefaultX;
    result.y = g_DefaultY;
    float eps = g_Epsilon;

    Range ra; ra.mp = a; ra.mCount = na; ra.mBest = g_Zero;
    for (int i = 0; i < ra.mCount; i++) {
        if (ra.mp[i].mMax[2] > g_Zero) {
            Vec4 v(ra.mp[i].mMax[0], ra.mp[i].mMax[1], -ra.mp[i].mMin[0], -ra.mp[i].mMin[1]);
            float m = FUN_00470f20(&v);
            if (z - eps >= ra.mp[i].mMin[2] && ra.mp[i].mMax[2] >= z + eps && m > ra.mBest)
                ra.mBest = m;
        }
    }
    result[0] = ra.mBest;

    Range rb; rb.mp = b; rb.mCount = nb; rb.mBest = g_Zero;
    for (int j = 0; j < rb.mCount; j++) {
        if (rb.mp[j].mMax[2] > g_Zero) {
            Vec4 v(rb.mp[j].mMax[0], rb.mp[j].mMax[1], -rb.mp[j].mMin[0], -rb.mp[j].mMin[1]);
            float m = FUN_00470f20(&v);
            if (rb.mp[j].mMax[2] >= z && m > rb.mBest)
                rb.mBest = m;
        }
    }
    result[1] = rb.mBest;
    out->x = result.x;
    out->y = result.y;
    return out;
}

// ---- types for AddInitialBoundInfo ----
struct Variant {
    unsigned int mData[4];
    u16 mFlags;
    u16 mTypeId;
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() { if (mFlags & 4) Destruct(false); }
    template <typename T> Variant& operator=(const T& x);      // 0x428060 <float>, 0x478300 <Box>
    void Destruct(bool bReconstruct);                           // 0x93db80
};

struct Property {
    char pad[0x12];
    u16 mType;                       // +0x12
    bool* GetBool();                 // 0x41e920
    int*  GetInt();                  // 0x41e990
};

struct IPropList {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void Set(u32 id, const Variant* v);                 // slot 5 (+0x14)
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool Get(u32 id, Property** out);                   // slot 9 (+0x24)
};

struct IObject {
    virtual void s0();
    virtual void Release();                                     // slot 1 (+4)
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool Get(u32 id, Property** out);                   // slot 9 (+0x24)
};

struct IPropManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual bool GetObject(u32 a, u32 b, IObject** out);        // slot 11 (+0x2c)
};

struct ObjPtr { IObject* mp; };
struct RefState { bool b; int z0; int z1; int z2; };

// fixed_vector<Box,64>-like (begin/end/cap/alloc + buffer)
struct VecBox {
    Box* mpBegin; Box* mpEnd; Box* mpCap; int mAlloc;
    char buf[0x608];
    VecBox(bool* a);                                // 0x540470
    void Init();                                    // 0x41da70
    void push_back(const Box* b);                   // 0x41e8b0
    void reserve(int n);                            // 0x41e770
    void Free();                                    // 0x4fd940
};
struct VecU64 {
    u64* mpBegin; u64* mpEnd; u64* mpCap; int mAlloc;
    char buf[72];
    VecU64(bool* a);                                // 0x540470
    void Init();                                    // 0x4c5e30 (ids vector)
    void Init2();                                   // 0x41cfe0 (V2 vector)
    void push_back(const u64* v);                   // 0x475800
    void reserve(int n);                            // 0x4756f0
    void Free();                                    // 0x526a40 / 0x4cddd0
};
struct VecV2 {
    Vec2* mpBegin; Vec2* mpEnd; Vec2* mpCap; int mAlloc;
    char buf[72];
    void Init();                                    // 0x41cfe0
    void push_back(const Vec2* v);                  // 0x475670
    void Free();                                    // 0x526a40
};

IPropManager* __cdecl PropertyManager();                              // 0x67de30
IObject** __fastcall PropObjOut(ObjPtr* p);                           // 0x41d870
Vec3* __cdecl Vector3_Negate(Vec3* out, const Vec3* in);              // 0x422020
Vec3* __cdecl Vector3_MaxVec(Vec3* out, const Vec3* a, const Vec3* b); // 0x41bfb0
float __cdecl VectorLength(const Vec3* v);                            // 0x40ae50
bool  __cdecl GetPropertyAsFloatArray(IPropList* pl, u32 id, int* count, float** arr); // 0x6a08b0
void  __cdecl SortV2(Vec2* b, Vec2* e, bool flag);                    // 0x478620

namespace SP { namespace EditorUtils {

// @ 0x00471000
void AddInitialBoundInfo(u64* ids, Box* boxes, int count, int unused, IPropList* pl)
{
    if (boxes == 0 || pl == 0)
        return;

    Box bound;
    bound.Reset();
    for (int i = 0; i < count; i++)
        bound.AddPoint(&boxes[i]);

    {
        Variant v;
        v = bound;
        pl->Set(0xf9efba, &v);
    }
    Vec3 neg;
    Vec3* pn = Vector3_Negate(&neg, &bound.mMin);
    Vec3 negCopy;
    negCopy[0] = (*pn)[0]; negCopy[1] = (*pn)[1]; negCopy[2] = (*pn)[2];
    Vec3 mx;
    float radius = VectorLength(Vector3_MaxVec(&mx, &negCopy, &bound.mMax));
    {
        Variant v;
        v = radius;
        pl->Set(0xf9efb9, &v);
    }
    {
        Variant v;
        v = bound.mMax[2];
        pl->Set(0x254cf97, &v);
    }

    bool allocFlag;
    VecBox vbox(&allocFlag);
    vbox.Init();
    for (int i = 0; i < count && ids != 0; i++) {
        u32 lo = (u32)(ids[i] & 0xffffffff);
        u32 hi = (u32)(ids[i] >> 32);
        ObjPtr obj; obj.mp = 0;
        if (lo != 0 && hi != 0) {
            IPropManager* pm = PropertyManager();
            if (pm->GetObject(lo, hi, PropObjOut(&obj))) {
                RefState st; st.b = true; st.z0 = 0; st.z1 = 0; st.z2 = 0;
                IObject* o = obj.mp;
                Property* prop;
                if (o != 0 && o->Get(0x4bf2278, &prop) && prop->mType == 1)
                    st.b = *prop->GetBool();
                if (st.b)
                    vbox.push_back(&boxes[i]);
            }
        }
        if (obj.mp != 0)
            obj.mp->Release();
    }

    float f624 = g_Zero;
    float f4 = g_Zero;
    int nArr = 0;
    float* arr = 0;
    if (!GetPropertyAsFloatArray(pl, 0x4c6df19, &nArr, &arr)) {
        f624 = radius;
        f4 = radius;
    }
    VecV2 v2;
    v2.Init();
    for (int k = 0; k < nArr; k++) {
        float z = arr[k] * bound.mMax[2];
        int nb = (int)(vbox.mpEnd - vbox.mpBegin);
        Vec2 r;
        FUN_00470bd0(&r, vbox.mpBegin, nb, boxes, count, z);
        if (r[0] > g_Zero)
            v2.push_back(&r);
        f4 = r[1];
    }
    if ((unsigned)(v2.mpEnd - v2.mpBegin) != 0) {
        int n = 1;
        Property* prop;
        if (pl != 0 && pl->Get(0x52d8d4a, &prop) && prop->mType == 9)
            n = *prop->GetInt();
        SortV2(v2.mpBegin, v2.mpEnd, allocFlag);
        f624 = g_Zero;
        int cnt = 0;
        int size = (int)(v2.mpEnd - v2.mpBegin);
        int lim = 0;
        int m = (size < n) ? size : n;
        for (; lim < m; lim++) {
            Vec2* e = v2.mpBegin + lim;
            f624 = f624 + (*e)[0];
            cnt++;
        }
        int one = 1;
        const int* pd = (cnt < one) ? &one : &cnt;
        f624 = f624 / (float)*pd;
    }
    if (f624 == 0.0f)
        f624 = g_Third;
    {
        Variant v;
        v = f624;
        pl->Set(0x254cf89, &v);
    }
    {
        Variant v;
        v = f4;
        pl->Set(0x254cf8f, &v);
    }
    for (char* p = (char*)v2.mpBegin; p < (char*)v2.mpEnd; p += 8) {}
    v2.Free();
    for (char* p = (char*)vbox.mpBegin; p < (char*)vbox.mpEnd; p += 0x18) {}
    vbox.Free();
}

}}

// ---- the caller: builds bound boxes from the object's item list ----
struct Item {                // 0x8c bytes
    char pad0[0x14];
    Vec3 mBoxMin;            // +0x14
    Vec3 mBoxMax;            // +0x20
    float mScale;            // +0x2c
    Mat9 mRot;               // +0x30
    Vec3 mPos;               // +0x54
    char pad1[0x84 - 0x60];
    u32 mIdHi;               // +0x84
    u32 mIdLo;               // +0x88
};
struct ItemVec { char* mpBegin; char* mpEnd; };
struct Editor {
    char pad0[0x18];
    int f18;
    char pad1[0x98 - 0x1c];
    ItemVec mItems;
};

struct BoxEx : Box {
    BoxEx(const Vec3* a, const Vec3* b);
    void TransformBy(const Transform* t);                  // 0x409dd0
};
struct Vec3C {                                              // Vector3 with a copy ctor at 0x4098a0
    float x, y, z;
    Vec3C(const Vec3& o);
};
struct BoxC {
    Vec3C mMin; Vec3C mMax;
    BoxC(const Vec3& a, const Vec3& b) : mMin(a), mMax(b) {}
    void SetCenterRadius(const Vec3* c, float r);          // 0x409ce0
    void TransformBy(const Transform* t);                  // 0x409dd0
};
struct VecBoxC {
    Box* mpBegin; Box* mpEnd; Box* mpCap; int mAlloc;
    char buf[0x608];
    VecBoxC(bool* a);                                       // 0x540470
    void Init();                                            // 0x41da70
    void push_back(const BoxC* b);                          // 0x41e8b0
    void reserve(int n);                                    // 0x41e770
    void Free();                                            // 0x4fd940
};
struct VecIds {
    u64* mpBegin; u64* mpEnd; u64* mpCap; int mAlloc;
    char buf[72];
    VecIds(bool* a);                                        // 0x540470
    void Init();                                            // 0x4c5e30
    void push_back(const u64* v);                           // 0x475800
    void reserve(int n);                                    // 0x4756f0
    void Free();                                            // 0x4cddd0
};
extern float g_BoxFallbackRadius;                           // 0x1488874

// @ 0x00471830
void FUN_00471830(Editor* self, IPropList* pl)
{
    if (self == 0)
        return;
    Item* data = (Item*)self->mItems.mpBegin;
    ItemVec* vp = &self->mItems;
    int n = (int)(vp->mpEnd - vp->mpBegin) / 0x8c;

    bool a1;
    VecBoxC boxes(&a1);
    boxes.Init();
    bool a2;
    VecIds ids(&a2);
    ids.Init();
    boxes.reserve(n);
    ids.reserve(n);

    for (int i = 0; i < n; i++) {
        Transform t;
        t.SetScale(data[i].mScale);
        t.SetRotation(data[i].mRot);
        t.SetPosition(data[i].mPos);
        BoxC box(data[i].mBoxMin, data[i].mBoxMax);
        bool bad = box.mMin.x > box.mMax.x ? true : false;   // inverted (empty) box test
        if (bad)
            box.SetCenterRadius(&g_Vec3Zero, g_BoxFallbackRadius);
        box.TransformBy(&t);
        boxes.push_back(&box);
        u64 id = ((u64)data[i].mIdHi << 32) | data[i].mIdLo;
        ids.push_back(&id);
    }
    Box* bb = boxes.mpBegin;
    SP::EditorUtils::AddInitialBoundInfo(ids.mpBegin, bb, n, self->f18, pl);
    ids.Free();
    for (char* p = (char*)boxes.mpBegin; p < (char*)boxes.mpEnd; p += 0x18) {}
    boxes.Free();
}
