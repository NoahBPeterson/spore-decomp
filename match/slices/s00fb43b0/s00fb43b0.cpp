// s00fb43b0 : SP::cTerrainSphereQuad::RebuildIndices (retail layout)
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

struct LockInfo { short* ptr; int a; int b; };

struct IndexBuf {
    int Lock(int mode, LockInfo* out);          // 0x011f4f20
    void Unlock(LockInfo* in);                   // 0x011f4fd0
};
struct IndexBufHolder { int pad0; IndexBuf* buf; };

struct TerrainMap;
struct MapQuery { float x, y; int face; };

struct TerrainMap {
    float GetFloat(MapQuery* q);                 // 0x00f8d620 SP::cTerrainMap<unsigned short>::GetFloat
};

struct SphereInfo {
    char pad0[8];
    TerrainMap* map;
    char pad1[0x38 - 0xc];
    float f38;
};

struct SphereB {
    float Height();                              // 0x00fd9400
    float* Get(float* out);                      // 0x00fb9400
};

struct Sphere {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual SphereInfo* Info();                  // +0x0c
    virtual SphereB* Source();                   // +0x10
};

void Memset32(void* p, int value, int count);    // 0x0092cb00

extern const float kBias;                        // 0x015b1588
extern const float kRange;                       // 0x015b1584

struct Quad;
struct Decal { char pad[0x10]; };

struct Quad {
    Sphere* mSphere;                             // +0x00
    char pad04[0x18 - 4];
    int mChunkRes;                               // +0x18
    int mFace;                                   // +0x1c
    char pad20[0x58 - 0x20];
    float mOffsetX;                              // +0x58
    float mOffsetY;                              // +0x5c
    float mSize;                                 // +0x60
    char pad64[0x6c - 0x64];
    bool mSkip;                                  // +0x6c
    char pad6d[0x91 - 0x6d];
    bool mDirtyIndices;                          // +0x91
    char pad92[0x94 - 0x92];
    IndexBufHolder* mIB;                         // +0x94
    int mNumTotal;                               // +0x98
    int mNumBelow;                               // +0x9c
    int mNumAbove;                               // +0xa0
    char pada4[0x154 - 0xa4];
    Decal* mDecalsBegin;                         // +0x154
    Decal* mDecalsEnd;                           // +0x158
    char pad15c[0x168 - 0x15c];
    uint64_t mQuadMask;                          // +0x168
    uint32_t* mMap;                              // +0x170
    int mMapSize;                                // +0x174
    int mMapStride;                              // +0x178

    void RebuildIndices();
    void FUN_00faf070(int col, int row, int n8);                 // 0x00faf070
    bool RebuildDecalIndices(Decal* d);                          // 0x00fb3f10
};

void Quad::RebuildIndices()
{
    if (mSkip) {
        mDirtyIndices = false;
        return;
    }
    LockInfo lock;
    if (!mIB->buf->Lock(2, &lock)) return;
    short* buf = lock.ptr;
    SphereInfo* info = mSphere->Info();
    SphereB* src = mSphere->Source();
    TerrainMap* map = info->map;
    float h = src->Height();
    float mid = h * 2.0f - 1.0f;
    float tmp[2];
    float w = src->Get(tmp)[1] * 2.0f;
    if (mMap) Memset32(mMap, 0, mMapSize);
    float step = mSize / (float)mChunkRes;
    float lo = (mid - w) - kBias;
    float hi = kRange / info->f38 + w + mid;
    for (int i = 0; i <= mChunkRes; i++) {
        for (int j = 0; j <= mChunkRes; j++) {
            MapQuery q;
            q.x = (float)j * step + mOffsetX;
            q.y = (float)i * step + mOffsetY;
            q.face = mFace;
            float v = map->GetFloat(&q);
            uint32_t above = lo <= v;
            uint32_t below = v <= hi;
            int a = j / 32;
            int r = j % 32;
            int p0 = mMapStride * i + a;
            mMap[p0] |= above << r;
            mMap[mMapSize / 2 + p0] |= below << r;
            int p1 = mMapStride * (i + 1) + a;
            mMap[p1] |= above << r;
            mMap[mMapSize / 2 + p1] |= below << r;
            int j1 = j + 1;
            int a1 = j1 / 32;
            int r1 = j1 % 32;
            int p2 = mMapStride * i + a1;
            mMap[p2] |= above << r1;
            mMap[mMapSize / 2 + p2] |= below << r1;
            int p3 = mMapStride * (i + 1) + a1;
            mMap[p3] |= above << r1;
            mMap[mMapSize / 2 + p3] |= below << r1;
        }
    }
    if (mQuadMask != 0) {
        int n8 = mChunkRes / 8;
        int bit = 0;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if ((mQuadMask & ((uint64_t)1 << bit)) != 0)
                    FUN_00faf070(col, row, n8);
                bit++;
            }
        }
    }
    int n = mChunkRes + 2;
    int cnt1 = 0, cnt2 = 0, cntNz = 0;
    for (int r = 0; r < n; r++) {
        int s1a = 0, s1b = 0, s2a = 0, s2b = 0, nza = 0, nzb = 0;
        int c = 0;
        if (1 < n) {
            do {
                int a = (c / 32) + mMapStride * r;
                int sh = c % 32;
                uint32_t code = ((mMap[a] >> sh) & 1) + (((mMap[mMapSize / 2 + a] >> sh) & 1) * 2);
                s1a += code & 1;
                s2a += code & 2;
                nza += code != 0;
                int c1 = c + 1;
                int a1 = (c1 / 32) + mMapStride * r;
                int sh1 = c1 % 32;
                uint32_t code1 = ((mMap[a1] >> sh1) & 1) + (((mMap[mMapSize / 2 + a1] >> sh1) & 1) * 2);
                s1b += code1 & 1;
                s2b += code1 & 2;
                nzb += code1 != 0;
                c += 2;
            } while (c < mChunkRes + 1);
        }
        if (c < n) {
            int a = (c / 32) + mMapStride * r;
            int sh = c % 32;
            uint32_t code = ((mMap[a] >> sh) & 1) + (((mMap[mMapSize / 2 + a] >> sh) & 1) * 2);
            cnt1 += code & 1;
            cnt2 += code & 2;
            cntNz += code != 0;
        }
        cntNz += nza + nzb;
        cnt2 += s2a + s2b;
        cnt1 += s1b + s1a;
    }
    mNumAbove = cntNz * 6;
    mNumTotal = cnt1 * 6;
    mNumBelow = cnt2 * 3;
    short* tbl[4];
    tbl[0] = 0;
    tbl[1] = buf;
    tbl[2] = buf + cnt1 * 6;
    tbl[3] = buf + (cntNz * 6 - cnt2 * 3);
    int base = 0;
    for (int r = 0; r < n; r++) {
        for (uint32_t c = 0; (int)c < n; c++) {
            int a = r * mMapStride + (c >> 5);
            uint32_t sh = c & 0x1f;
            short* p = tbl[((mMap[a] >> sh) & 1) + (((mMap[mMapSize / 2 + a] >> sh) & 1) * 2)];
            if (p) {
                tbl[((mMap[a] >> sh) & 1) + (((mMap[mMapSize / 2 + a] >> sh) & 1) * 2)] = p + 6;
                short v = (short)(base + c);
                p[0] = v + 1;
                p[1] = (short)n + 2 + v;
                short t = (short)n + 1 + v;
                p[2] = t;
                p[3] = t;
                p[4] = v;
                p[5] = v + 1;
            }
        }
        base += mChunkRes + 3;
    }
    mIB->buf->Unlock(&lock);
    int nd = (int)(mDecalsEnd - mDecalsBegin);
    for (int k = 0; k < nd; k++) {
        if (!RebuildDecalIndices(mDecalsBegin + k)) return;
    }
    mDirtyIndices = false;
}

// ---------------------------------------------------------------------------
// Remaining s00fb43b0 functions (5 VAs). Object layout follows the existing Quad
// (cTerrainSphereQuad) with the fields used by these members named below.
// ---------------------------------------------------------------------------
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

// Full retail layout of SP::cTerrainSphereQuad as used by the initializer and the decal
// functions (fields named only where the code reads/writes them).
struct TerrainSphereQuad {
    int m0;                     // +0x00
    int m4;                     // +0x04
    int m8;                     // +0x08
    int mc;                     // +0x0c
    int m10;                    // +0x10
    int m14;                    // +0x14
    int m18;                    // +0x18
    int m1c;                    // +0x1c
    float m20, m24, m28, m2c;   // +0x20 .. +0x2c
    float m30;                  // +0x30
    float m34, m38, m3c;        // +0x34 .. +0x3c
    char pad40[0x64 - 0x40];
    float m64;                  // +0x64
    float m68;                  // +0x68
    uint8_t m6c;                // +0x6c
    char pad6d[0x70 - 0x6d];
    int m70[3];                 // +0x70 .. +0x78 (bit patterns of a broadcast float)
    int m7c[3];                 // +0x7c .. +0x84
    float m88;                  // +0x88
    float m8c;                  // +0x8c
    uint8_t m90;                // +0x90
    uint8_t m91;                // +0x91
    char pad92[0x94 - 0x92];
    int m94, m98, m9c, ma0;     // +0x94 .. +0xa0
    char padA4[0x154 - 0xa4];
    int m154, m158, m15c;       // +0x154 ..
    char pad160[0x168 - 0x160];
    int m168, m16c, m170, m174, m178;
    char pad17c[0x18c - 0x17c];
    int m18c, m190, m194;
    char pad198[0x1a0 - 0x198];
    int m1a0, m1a4, m1a8;
};

extern "C" void* __cdecl operator_delete(void* p);   // 0x00f47380

struct DecalRec { char bytes[0x10]; };

struct SphQuad {
    char pad00[0x1c];
    int mFace;                          // +0x1c
    char pad20[0x20 - 0x1c];
    float mMinX;                        // +0x20
    float mMinY;                        // +0x24
    float mMaxX;                        // +0x28
    float mMaxY;                        // +0x2c
    char pad30[0x68 - 0x30];
    unsigned int m68;                   // +0x68
    char pad6c[0x70 - 0x6c];
    int m70;                            // +0x70
    char pad74[0x80 - 0x74];
    int mDecalBegin;                    // +0x80
    int mDecalEnd;                      // +0x84
    char pad88[0x154 - 0x88];
    DecalRec* mDecalsBegin;             // +0x154
    DecalRec* mDecalsEnd;               // +0x158

    void FUN_00fb4c10(unsigned int n);                  // 0x00fb4c10
    void FUN_00fb4e10(int* owner, int arg3, unsigned int arg4,
                      int* p5, int* p6, int arg7);      // 0x00fb4e10
    void FUN_00fb4a50(int* arg);                        // 0x00fb4a50
    bool FUN_00fb3f10(DecalRec* d);                     // 0x00fb3f10 (RebuildDecalIndices)
};

extern "C" void __stdcall FUN_00fb39b0(int dst, unsigned int n, void* buf);   // 0x00fb39b0
extern "C" void __stdcall FUN_00fb3240(int a, int b);                        // 0x00fb3240
// __thiscall image callees: MSVC 7.1 rejects __thiscall on free functions, so declare them as
// members of a holder whose qualified names still end with the target identifiers.
struct Fb3e20Ops { void FUN_00fb3e20(); void FUN_00fb4340(); };
extern "C" void __stdcall FUN_00fb2550(void* p);                          // 0x00fb2550
extern "C" void __stdcall FUN_00c19d10(void* dst, void* src);             // 0x00c19d10
extern "C" void __stdcall FUN_00fb1b80();                                 // 0x00fb1b80
extern "C" void __stdcall FUN_00faf890();                                 // 0x00faf890
extern "C" void __stdcall FUN_00faef90();                                 // 0x00faef90
extern "C" void __stdcall FUN_00fb0bd0(int n);                            // 0x00fb0bd0
#include <math.h>
extern const uint8_t DAT_01491094[];
extern int DAT_015b1544;
extern int DAT_015b1548;
extern int DAT_015b154c;
extern int DAT_016d664c;
extern int DAT_016d6650;

// @ 0x00fb4c10
void SphQuad::FUN_00fb4c10(unsigned int n)
{
    int* self = (int*)this;
    char buf[200];
    if (n > (unsigned int)((self[1] - self[0]) / 200)) {
        FUN_00fb39b0(self[1], n - (self[1] - self[0]) / 200, buf);
    } else {
        FUN_00fb3240(self[0] + n * 200, self[1]);
    }
}

// @ 0x00fb4c90
TerrainSphereQuad* __fastcall FUN_00fb4c90(TerrainSphereQuad* p)
{
    p->m0 = 0;
    p->m4 = 0;
    p->m18 = 0;
    p->m1c = 0;
    p->m20 = 0.0f;
    p->m24 = 0.0f;
    float k30 = *(const float*)0x01485720;
    p->m28 = 0.0f;
    p->m2c = 0.0f;
    p->m30 = k30;
    p->m34 = *(const float*)0x015b1544;
    p->m38 = *(const float*)0x015b1548;
    p->m3c = *(const float*)0x015b154c;
    p->m6c = 0;
    p->m64 = 0.0f;
    p->m68 = 0.0f;
    float f70 = *(const float*)0x014910f0;
    {
        float tmp[3];
        tmp[0] = f70;
        tmp[1] = f70;
        tmp[2] = f70;
        p->m70[0] = *(int*)&tmp[0];
        p->m70[1] = *(int*)&tmp[1];
        p->m70[2] = *(int*)&tmp[2];
    }
    float f7c = *(const float*)0x013f51ac;
    {
        float tmp[3];
        tmp[0] = f7c;
        tmp[1] = f7c;
        tmp[2] = f7c;
        p->m7c[0] = *(int*)&tmp[0];
        p->m7c[1] = *(int*)&tmp[1];
        p->m7c[2] = *(int*)&tmp[2];
    }
    p->m90 = 0;
    p->m91 = 0;
    p->m94 = 0;
    p->m98 = 0;
    p->m9c = 0;
    p->ma0 = 0;
    p->m88 = 0.0f;
    p->m8c = 0.0f;
    p->m154 = 0;
    p->m158 = 0;
    p->m15c = 0;
    p->m168 = 0;
    p->m16c = 0;
    p->m170 = 0;
    p->m174 = 0;
    p->m178 = 0;
    p->m18c = 0;
    p->m190 = 0;
    p->m194 = 0;
    p->m1a0 = 0;
    p->m1a4 = 0;
    p->m1a8 = 0;
    p->m8 = 0;
    p->mc = 0;
    p->m10 = 0;
    p->m14 = 0;
    int c = DAT_016d664c + 1;
    if (DAT_016d6650 <= c)
        DAT_016d6650 = c;
    DAT_016d664c = c;
    return p;
}

// @ 0x00fb4e10
void SphQuad::FUN_00fb4e10(int* owner, int arg3, unsigned int arg4,
                           int* p5, int* p6, int arg7)
{
    int* self = (int*)this;
    int iVar2 = owner[0x75];
    self[7] = arg4;
    self[0] = (int)owner;
    self[1] = arg3;
    self[8] = p5[0];
    self[9] = p5[1];
    self[10] = p6[0];
    self[0xb] = p6[1];
    float* fs = (float*)self;
    float fVar7 = ((fs[9] + fs[0xb]) * 0.5f) * 2.0f - 1.0f;
    float fVar5 = ((fs[8] + fs[10]) * 0.5f) * 2.0f - 1.0f;
    int iVar4 = ((int)arg4 >> 1) * 4;
    float fVar6 = 1.0f / sqrtf((fVar5 * fVar5 + fVar7 * fVar7) + 1.0f);
    float fVar8 = fVar6;
    if ((arg4 & 1) != 0)
        fVar8 = -fVar6;
    float local_c[3];
    local_c[DAT_01491094[iVar4]] = fVar8 * fVar5;
    local_c[DAT_01491094[iVar4 + 1]] = fVar6 * fVar7;
    local_c[DAT_01491094[iVar4 + 2]] = fVar8;
    fVar6 = 1.0f / sqrtf((local_c[0] * local_c[0] + (local_c[1] * local_c[1] + local_c[2] * local_c[2])) + 1e-08f);
    local_c[0] = fVar6 * local_c[0];
    self[0xd] = (int)local_c[0];
    local_c[1] = local_c[1] * fVar6;
    self[0xe] = (int)local_c[1];
    local_c[2] = local_c[2] * fVar6;
    self[0xf] = (int)local_c[2];
    *(uint8_t*)(self + 0x1b) = (uint8_t)(arg7 == 2);
    self[0x5f] = p5[0];
    self[0x60] = p5[1];
    self[0x61] = p6[0];
    iVar4 = p6[1];
    self[6] = iVar2;
    self[0x62] = iVar4;
    ((void (__thiscall*)(int*))((int*)*owner)[3])(owner);
    ((void (__thiscall*)(int))((int*)*self)[4])(*self);
    if (arg3 == 0)
        fVar6 = 1.0f;
    else
        fVar6 = *(float*)(arg3 + 0x30) * 0.5f;
    self[0xc] = (int)fVar6;
    int* piVar1 = *(int**)(*self + 0xa4c);
    int iVar2b = *piVar1;
    int iVar3 = *(int*)(iVar2b + 8);
    if (iVar3 == piVar1[1]) {
        iVar2b = 0;
    } else {
        *piVar1 = iVar3;
        *(int*)(iVar3 + 0xc) = 0;
        *(int*)(iVar2b + 8) = 0;
        *(int*)(iVar2b + 0xc) = 0;
        piVar1[2] = piVar1[2] + 1;
        iVar3 = piVar1[2];
        if (piVar1[2] < piVar1[3])
            iVar3 = piVar1[3];
        piVar1[3] = iVar3;
    }
    self[0x25] = iVar2b;
    FUN_00faf890();
    FUN_00fb1b80();
    FUN_00faef90();
    FUN_00fb0bd0(1);
    *(uint8_t*)(self + 0x24) = 1;
    *(uint8_t*)((char*)self + 0x91) = 1;
    if (arg3 != 0) {
        int n = (*(int*)(arg3 + 0x158) - *(int*)(arg3 + 0x154)) >> 4;
        int off = 0;
        if (n > 0) {
            do {
                ((SphQuad*)*(int*)(off + *(int*)(arg3 + 0x154)))->FUN_00fb4a50((int*)arg3);
                off += 0x10;
            } while (--n != 0);
        }
    }
}

// @ 0x00fb4a50
void SphQuad::FUN_00fb4a50(int* arg)
{
    int* self = (int*)this;
    int n = (arg[0x84 / 4] - arg[0x80 / 4]) / 0x14;
    int i = 0;
    if (n <= 0)
        return;
    int* begin = (int*)arg[0x80 / 4];
    int* p = begin;
    while (*p != self[0x1c / 4]) {
        i++;
        p += 5;
        if (i >= n)
            return;
    }

    float maxX = *(float*)((char*)self + 0x28);
    float maxY = *(float*)((char*)self + 0x2c);
    float minX = *(float*)((char*)self + 0x20);
    float minY = *(float*)((char*)self + 0x24);
    float bx = *(float*)((char*)begin + i * 0x14 + 4);
    float by = *(float*)((char*)begin + i * 0x14 + 8);
    float ex = *(float*)((char*)begin + i * 0x14 + 0xc);
    float ey = *(float*)((char*)begin + i * 0x14 + 0x10);
    if (!(maxX <= bx || maxX == bx) && minX < ex &&
        !(maxY <= by || maxY == by) && minY < ey && i >= 0)
    {
        int local_10 = arg[0];
        int local_c = 0;
        int local_8 = 0;
        int local_4 = 0;
        if (arg[0x70 / 4] == 9)
            FUN_00fb2550(&local_10);

        int* vertsBegin = (int*)self[0x154 / 4];
        int* vertsEnd = (int*)self[0x158 / 4];
        int count = ((char*)vertsEnd - (char*)vertsBegin) >> 4;
        int idx = count;
        int k = 0;
        if (count > 0) {
            int* e = vertsBegin;
            do {
                idx = k;
                if ((unsigned int)arg[0x68 / 4] < *(unsigned int*)(*e + 0x68))
                    break;
                e += 4;
                k++;
                idx = count;
            } while (k < count);
        }
        char* entry = (char*)vertsBegin + idx * 0x10;
        if (entry == (char*)vertsBegin && vertsBegin != vertsEnd) {
            self[0x154 / 4] = (int)(vertsBegin + 4);
            if (vertsBegin) {
                vertsBegin[0] = local_10;
                vertsBegin[1] = local_c;
                vertsBegin[2] = local_8;
                vertsBegin[3] = local_4;
            }
        } else {
            FUN_00c19d10(entry, &local_10);
        }
        if (local_8 != 0 || local_4 != 0) {
            self[0x168 / 4] |= local_8;
            self[0x16c / 4] |= local_4;
            *((char*)self + 0x91) = 1;
        }
        ((SphQuad*)self)->FUN_00fb3f10((DecalRec*)((char*)vertsBegin + idx * 0x10));
        int* child = self + 2;                 // +8
        int c = 4;
        do {
            if (*child)
                FUN_00fb4a50(arg);
            child++;
        } while (--c != 0);
    }
}

// @ 0x00fb5090
void __fastcall FUN_00fb5090(int* self)
{
    int* p = self + 2;                  // +8
    int n = 4;
    do {
        ((Fb3e20Ops*)*p)->FUN_00fb3e20();
        int o = *p;
        if (o) {
            ((Fb3e20Ops*)o)->FUN_00fb4340();
            operator_delete((void*)o);
        }
        *p = 0;
        p++;
    } while (--n != 0);
}
