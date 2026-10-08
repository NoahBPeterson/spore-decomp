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
