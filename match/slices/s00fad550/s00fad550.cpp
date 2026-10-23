// Slice s00fad550 -- Spore terrain sphere decal runtime (SP::cTerrainSphereDecal).
//
//   00fad550  SP::cTerrainSphereDecal::DispatchStaticDecal   (thiscall, ret 8)
//   00fad730  SP::cTerrainSphereDecal constructor            (thiscall, ret)
//   00fad930  DecalEntryVector::DoGrow                       (thiscall, ret 8)
//   00fada70  DecalEntryVector::push_back                    (thiscall, ret 4)
//   00fadac0  SP::cTerrainSphereDecal teardown               (thiscall, ret)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------- rw::math --
struct Vector4 {
    float x, y, z, w;
};

struct Matrix33 {
    float m[9];
    void  Assign(const Matrix33& src);
};

// ------------------------------------------------------------ decal entries --
struct DecalEntry {
    int     m_index;    // +0x00
    Vector4 m_box;      // +0x04
};

struct DecalEntryVector {
    DecalEntry* mBegin;     // +0x00
    DecalEntry* mEnd;       // +0x04
    DecalEntry* mCapacity;  // +0x08

    void DoGrow(DecalEntry* pos, const DecalEntry* value);
    void push_back(const DecalEntry& value);
};

// ------------------------------------------------------- Spore decal object --
struct cTerrainSphereDecal;

extern "C" float sqrtf(float);
extern "C" long _InterlockedDecrement(volatile long* p);
extern "C" long _InterlockedExchangeAdd(volatile long* p, long v);

struct cDecalHost {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int  GetTarget();                       // vtable slot +0xc
    void         MergeFaceBox(Vector4 box, int index);
};

struct cTerrainMapSet {
    float GetHeightAt(const float* pos);
};

struct cTerrainEditor {
    bool SynthesizeAboveTextureDecal(void* host, cTerrainSphereDecal* decal, const float* pair,
                                     int index, Vector4 box, int param3);
};

namespace SP {
    cTerrainEditor* TerrainEditor();
}

struct U32Pair { u32 a, b; };

// --------------------------------------------------------------- extern data --
extern const float    kF_16ca628;                    // 0x16ca628
extern const float    kF_16ca62c;                    // 0x16ca62c
extern const float    kF_16ca630;                    // 0x16ca630
extern const Matrix33 kMat_16ca604;                  // 0x16ca604
extern const float    kF_16ca5c4;                    // 0x16ca5c4
extern const float    kF_16ca5c8;                    // 0x16ca5c8
extern const float    kF_16ca5cc;                    // 0x16ca5cc
extern const float    kF_16ca5d0;                    // 0x16ca5d0
extern const float    kF_16ca5d4;                    // 0x16ca5d4
extern const float    kF_16ca5d8;                    // 0x16ca5d8
extern const float    kF_16ca5dc;                    // 0x16ca5dc
extern const float    kF_15b14f8;                    // 0x15b14f8
extern const float    kF_15b14fc;                    // 0x15b14fc
extern const float    kF_15b1500;                    // 0x15b1500
extern const float    kF_15b1504;                    // 0x15b1504
extern const float    kF_15b1508;                    // 0x15b1508
extern const float    kF_15b150c;                    // 0x15b150c
extern const u8       kSwz_1491030[][4];             // 0x1491030
extern const U32Pair  kPairs_16ca3d4[];              // 0x16ca3d4
extern char           kVtbl_1491090;                 // 0x1491090

// ----------------------------------------------------------------- helpers --
extern "C" void* FUN_00fad040(void* first, void* last, void* dst);
extern "C" void  FUN_00fad0f0(void* dst, void* first, void* last);
extern "C" void  FUN_00fad0a0(void* a, void* b, void* c);
extern "C" void* EAAllocate(u32 size, const char* name, int flags, u32 align,
                            const char* file, int line);
void operator delete(void* p);

// ------------------------------------------------------- the decal object --
struct cTerrainSphereDecal {
    void*       m_vtbl;         // +0x000
    int         m_04;           // +0x004
    u16         m_08;           // +0x008
    u16         m_0a;           // +0x00a
    float       m_0c;           // +0x00c
    float       m_10;           // +0x010
    float       m_14;           // +0x014
    float       m_18;           // +0x018
    Matrix33    m_mat;          // +0x01c
    float       m_40[8];        // +0x040
    float       m_60;           // +0x060
    float       m_64;           // +0x064
    int         m_68;           // +0x068
    int         m_6c;           // +0x06c
    int         m_70;           // +0x070
    int         m_74;           // +0x074
    void*       m_78;           // +0x078
    void*       m_7c;           // +0x07c
    DecalEntry* m_80;           // +0x080
    DecalEntry* m_84;           // +0x084
    int         m_88;           // +0x088
    int         m_8c;           // +0x08c
    int         m_90;           // +0x090
    float       m_94;           // +0x094
    float       m_98;           // +0x098
    int         m_9c;           // +0x09c
    float       m_a0;           // +0x0a0
    float       m_a4;           // +0x0a4
    float       m_a8;           // +0x0a8
    float       m_ac;           // +0x0ac
    float       m_b0;           // +0x0b0
    int         m_b4;           // +0x0b4
    int         m_b8;           // +0x0b8
    int         m_bc[0xc];      // +0x0bc .. +0x0ec
    float       m_ec[7];        // +0x0ec .. +0x108
    float       m_108[3];       // +0x108 .. +0x114
    float       m_114;          // +0x114
    float       m_118[3];       // +0x118 .. +0x124
    float       m_124;          // +0x124
    void*       m_128;          // +0x128

    cTerrainSphereDecal* Construct();
    void  Uninit();
    bool  DispatchStaticDecal(int index, int param3);
    void  Reset();              // 00fad000
};

// ------------------------------------------------------------------- copy --
static void CopyEntry(DecalEntry* dst, const DecalEntry* src)
{
    dst->m_index = src->m_index;
    dst->m_box.x = src->m_box.x;
    dst->m_box.y = src->m_box.y;
    dst->m_box.z = src->m_box.z;
    dst->m_box.w = src->m_box.w;
}

// @ 0x00fada70
void DecalEntryVector::push_back(const DecalEntry& value)
{
    DecalEntry* end = mEnd;
    if (end < mCapacity) {
        mEnd = end + 1;
        if (end)
            CopyEntry(end, &value);
    } else {
        DoGrow(end, &value);
    }
}

// @ 0x00fad930
void DecalEntryVector::DoGrow(DecalEntry* pos, const DecalEntry* value)
{
    if (mEnd != mCapacity) {
        const DecalEntry* src = value;
        if (src >= pos && src < mEnd)
            src = src + 1;
        if (mEnd)
            CopyEntry(mEnd, mEnd - 1);
        FUN_00fad0f0(pos, mEnd - 1, mEnd);
        CopyEntry(pos, src);
        ++mEnd;
    } else {
        int count = (int)((char*)mEnd - (char*)mBegin) / 0x14;
        int newCap;
        if (count != 0)
            newCap = count * 2;
        else
            newCap = 1;
        DecalEntry* newBuf;
        if (newCap)
            newBuf = (DecalEntry*)EAAllocate(newCap * 0x14, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        else
            newBuf = 0;
        DecalEntry* oldBegin = mBegin;
        DecalEntry* p = (DecalEntry*)FUN_00fad040(oldBegin, pos, newBuf);
        if (p)
            CopyEntry(p, value);
        const DecalEntry* oldEnd = mEnd;
        DecalEntry* newEnd = (DecalEntry*)FUN_00fad040(pos, (void*)oldEnd, p + 1);
        if (mBegin && ((int*)mBegin)[-1] != 0)
            operator delete(mBegin);
        mBegin = newBuf;
        mEnd = newEnd;
        mCapacity = newBuf + newCap;
    }
}

// @ 0x00fad730
cTerrainSphereDecal* cTerrainSphereDecal::Construct()
{
    m_08 = 0;
    m_0a = 0;
    m_0c = kF_16ca628;
    m_10 = kF_16ca62c;
    m_14 = kF_16ca630;
    m_18 = 1.0f;
    m_mat.Assign(kMat_16ca604);
    m_40[0] = 1.0f;
    m_40[1] = 1.0f;
    m_40[2] = 1.0f;
    m_40[3] = 1.0f;
    m_40[4] = 1.0f;
    m_40[5] = 1.0f;
    m_40[6] = 1.0f;
    m_40[7] = 1.0f;
    m_60 = 0.0f;
    m_64 = 0.0f;
    m_68 = 0;
    m_6c = 0;
    m_04 = 0;
    m_78 = 0;
    m_7c = 0;
    m_vtbl = &kVtbl_1491090;
    m_74 = -1;
    m_80 = 0;
    m_84 = 0;
    m_88 = 0;
    m_9c = 0;
    m_94 = 0.0f;
    m_98 = 0.0f;
    m_b4 = 0;
    m_b8 = 0;
    m_a0 = 0.0f;
    m_a4 = 0.0f;
    m_a8 = 0.0f;
    m_ac = 0.0f;
    m_b0 = 1.0f;
    m_ec[0] = kF_16ca5c4;
    m_ec[1] = kF_16ca5c8;
    m_ec[2] = kF_16ca5cc;
    m_ec[3] = kF_16ca5d0;
    m_ec[4] = kF_16ca5d4;
    m_ec[5] = kF_16ca5d8;
    m_ec[6] = kF_16ca5dc;
    m_108[0] = kF_15b14f8;
    m_108[1] = kF_15b14fc;
    m_108[2] = kF_15b1500;
    m_114 = 1.0f;
    m_118[0] = kF_15b1504;
    m_118[1] = kF_15b1508;
    m_118[2] = kF_15b150c;
    m_124 = 1.0f;
    m_128 = 0;
    return this;
}

// @ 0x00fad550
bool cTerrainSphereDecal::DispatchStaticDecal(int index, int param3)
{
    float* pf = (float*)((cDecalHost*)m_78)->GetTarget();

    float t1 = m_94 * 2.0f - 1.0f;
    float h  = ((pf[0x10] + pf[0xf]) * pf[0xe]) + pf[0xd];
    float t2 = m_98 * 2.0f - 1.0f;
    float inv = 1.0f / sqrtf(t2 * t2 + t1 * t1 + 1.0f);
    float s = inv;
    if (m_9c & 1)
        s = -s;

    const u8* swz = kSwz_1491030[m_9c >> 1];
    float axis[3];
    axis[swz[0]] = s * t1;
    axis[swz[1]] = inv * t2;
    axis[swz[2]] = s;

    if (h > ((cTerrainMapSet*)m_7c)->GetHeightAt(axis))
        m_b8 |= 1;
    else
        m_b8 &= ~1;

    for (u32 i = 0; i < (u32)(((char*)m_84 - (char*)m_80) / 0x14); i++) {
        if (m_80[i].m_index == index) {
            U32Pair pair = kPairs_16ca3d4[m_80[i].m_index];
            return SP::TerrainEditor()->SynthesizeAboveTextureDecal(m_78, this, (const float*)&pair,
                       m_80[i].m_index, m_80[i].m_box, param3) != 0;
        }
    }
    return true;
}

// @ 0x00fadac0
void cTerrainSphereDecal::Uninit()
{
    if ((m_b8 >> 3 & 1) == 0) {
        if ((m_b8 >> 4 & 1) != 0)
            Reset();
    } else {
        if ((u32)(((char*)m_84 - (char*)m_80) / 0x14) != 0) {
            u32 i = 0;
            do {
                cDecalHost* host = (cDecalHost*)m_78;
                if (host->GetTarget())
                    host->MergeFaceBox(m_80[i].m_box, m_80[i].m_index);
                host = (cDecalHost*)m_78;
                ++i;
            } while (i < (u32)(((char*)m_84 - (char*)m_80) / 0x14));
        }
    }
    FUN_00fad0a0(m_84, m_84, m_80);
    m_84 -= (int)((char*)m_84 - (char*)m_80) / 0x14;
    m_78 = 0;
    m_7c = 0;
    if (m_128) {
        volatile long* p = (volatile long*)((char*)m_128 + 8);
        m_128 = 0;
        _InterlockedDecrement(p);
        if (_InterlockedExchangeAdd(p, 0) >= 1)
            _InterlockedExchangeAdd(p, 0);
        else
            _InterlockedExchangeAdd(p, 1);
    }
    m_74 = -1;
}
