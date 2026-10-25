// Slice s0070ced0: SP::cLightingWorld / cLightingManager lifetime + eastl::vector<SP::cLightingConfig>.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

inline void* operator new(size_t, void* p) { return p; }

// ---- masked external helpers -------------------------------------------------
void* __cdecl EAlloc(size_t n, const char* name, int a, unsigned b, const char* file, int line); // 0x00f473a0
void  __cdecl EFree(void* p);                                                                    // 0x00f47380
void* __cdecl GAlloc(size_t n, unsigned align, int a, const char* name, int b, int c, int d, int e); // 0x00f473d0
int*  __cdecl GFree(void* p);                                                                    // 0x00f47380 (with size arg in map path)

void __cdecl   InitAtmBuffer(void* p, int zero, int n);          // 0x011e073e
void* __cdecl  ConfigRangeOp1(void*, void*, void*);              // 0x00708ec0
void* __cdecl   RBTreeIncrement(void* node);                     // 0x00921580
void* __cdecl   MessageServer(void);                             // 0x0067dcc0
void* __cdecl   PropertyManager(void);                           // 0x0067de30

// helper stubs (member functions => __thiscall, matching the original call sites)
struct HM { void Assign(const void*); };                          // 0x0041cb40
struct HD3D { void Op(int); };                                    // 0x00705db0
struct H63c { void Free(); };                                     // 0x0070a070
struct H608 { void Free(); };                                     // 0x00702500
struct H44c { void Free(); };                                     // 0x00706a40
struct HList { void Dtor(); };                                    // 0x00620230
struct HDeque { void Dtor(); };                                   // 0x0070c040
struct HMap { void* Find(void* key); };                           // 0x0074f200
struct HNuke { void Nuke(void* node); };                          // 0x00707690
struct HSmall { void Op(); };                                     // 0x0070a2a0
unsigned __fastcall F_70cce0(void* self, int, void* entry);                         // 0x0070cce0
int      __cdecl    F_705740(int n, const float* colour, float size, int* cells);   // 0x00705740
int      __cdecl    F_705050(int count, int* cells);                                // 0x00705050
void     __fastcall F_708d90(void* vec, int, unsigned n);                           // 0x00708d90
void     __fastcall F_708810(void* self, int, unsigned slot, int index, void* sample); // 0x00708810
unsigned __fastcall F_70c5e0(void* pool, int, void* sentinel);                      // 0x0070c5e0
void     __fastcall F_70c410(void* self, int, int node);                            // 0x0070c410
void     __fastcall F_705f40(void* self, int, void* info);                          // 0x00705f40

// cLocalLightInfo (0xc0 bytes); its cell list is an eastl::fixed_vector at +0x28 with an
// inline 0x80-byte buffer at +0x40 (header copied from the slot source in create()).
struct LocalLightInfo {
    unsigned char _d00[0x28];      // +0x00 position/size/colour/ratio/flags
    void* mpVecBegin;              // +0x28
    void* mpVecEnd;                // +0x2c
    void* mpVecCap;                // +0x30
    unsigned char _d34[4];         // +0x34
    void* mpInline;                // +0x38
    unsigned char mBuffer[0x80];   // +0x40
};
struct HShut { void Shutdown(); };                                // 0x0070a3f0
struct HNode { void Dtor(void* node); };                          // 0x00d0c930
struct HFill { void Fill(int id, void* cfg); };                   // 0x0070aed0
struct HSample { void Call(void* sample); };                      // 0x007094c0

struct MServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(int, int, int); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual void Unsubscribe(void* handler, int msg, int a3);
};

// cLightingConfig is 0x144 bytes; its special members live out of line in this module.
struct cLightingConfig {
    unsigned char _d[0x144];
    cLightingConfig();
    cLightingConfig(const cLightingConfig&);
    cLightingConfig& operator=(const cLightingConfig&);
    ~cLightingConfig();
};

cLightingConfig* __cdecl ConfigUninitCopy(cLightingConfig* first, cLightingConfig* last, cLightingConfig* dst); // 0x00708500
void             __cdecl ConfigDestruct(cLightingConfig* first, cLightingConfig* last, cLightingConfig* dst);   // 0x00706d60
cLightingConfig* __cdecl ConfigCopyBackward(cLightingConfig* first, cLightingConfig* last, cLightingConfig* dstEnd); // 0x00708f00
cLightingConfig* __cdecl ConfigUninitFillN(cLightingConfig* dst, unsigned n, const cLightingConfig* value, cLightingConfig* extra); // 0x00708480
cLightingConfig* __cdecl ConfigUninitMoveN(cLightingConfig* out, cLightingConfig* first, cLightingConfig* last, const cLightingConfig* value); // 0x00708400
void             __cdecl ConfigFill(cLightingConfig* first, cLightingConfig* last, const cLightingConfig* value);   // 0x0070a270

struct ConfigVec {
    cLightingConfig* mpBegin;     // +0x00
    cLightingConfig* mpEnd;       // +0x04
    cLightingConfig* mpCapacity;  // +0x08

    void DoInsertValue(cLightingConfig* position, const cLightingConfig& value);
    void DoInsertValues(cLightingConfig* position, unsigned n, const cLightingConfig& value);
};

// @ 0x0070ced0
void ConfigVec::DoInsertValue(cLightingConfig* position, const cLightingConfig& value)
{
    if (mpEnd != mpCapacity) // size < capacity
    {
        const cLightingConfig* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        new ((void*)mpEnd) cLightingConfig(*(mpEnd - 1));
        ConfigCopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    }
    else // size == capacity
    {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        cLightingConfig* pNewData;
        if (nNewSize == 0)
            pNewData = 0;
        else
            pNewData = (cLightingConfig*)EAlloc(nNewSize * sizeof(cLightingConfig), "Graphics", 0, 0, ALLOC_FILE, 0xd1);

        cLightingConfig* pNewEnd = ConfigUninitCopy(mpBegin, position, pNewData);
        ConfigDestruct(mpBegin, position, pNewData);
        new ((void*)pNewEnd) cLightingConfig(value);
        cLightingConfig* pEnd = ConfigUninitCopy(position, mpEnd, pNewEnd + 1);
        ConfigDestruct(position, mpEnd, pNewEnd + 1);

        cLightingConfig* pOld = mpBegin;
        if ((pOld != 0) && (*(int*)((char*)pOld - 4) != 0))
            EFree(pOld);

        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x0070d080
void ConfigVec::DoInsertValues(cLightingConfig* position, unsigned n, const cLightingConfig& value)
{
    if (n > (unsigned)(mpCapacity - mpEnd))
    {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        unsigned nNewSize = nPrevSize + n;
        if (nNewSize < nGrowSize)
            nNewSize = nGrowSize;
        cLightingConfig* pNewData = (nNewSize == 0)
            ? 0 : (cLightingConfig*)EAlloc(nNewSize * sizeof(cLightingConfig), "Graphics", 0, 0, ALLOC_FILE, 0xd1);

        cLightingConfig* pNewEnd = ConfigUninitCopy(mpBegin, position, pNewData);
        ConfigDestruct(mpBegin, position, pNewData);
        ConfigUninitFillN(pNewEnd, n, &value, mpBegin);
        cLightingConfig* pEnd = ConfigUninitCopy(position, mpEnd, pNewEnd + n);
        ConfigDestruct(position, mpEnd, pNewEnd + n);

        cLightingConfig* pOld = mpBegin;
        if ((pOld != 0) && (*(int*)((char*)pOld - 4) != 0))
            EFree(pOld);

        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewSize;
    }
    else if (n != 0)
    {
        cLightingConfig temp(value);
        const unsigned nExtra = (unsigned)(mpEnd - position);
        if (n < nExtra)
        {
            ConfigUninitMoveN(0, mpEnd - n, mpEnd, &temp);
            ConfigCopyBackward(position, mpEnd - n, mpEnd);
            ConfigFill(position, position + n, &temp);
        }
        else
        {
            ConfigUninitFillN(mpEnd, n - nExtra, &temp, mpEnd);
            ConfigUninitMoveN(0, position, mpEnd, &temp);
            ConfigFill(position, mpEnd, &temp);
        }
        mpEnd += n;
        temp.~cLightingConfig();
    }
}

// ---- cLightingWorld ----------------------------------------------------------
// Retail layout is 0x670 bytes (larger than the dev-PDB 0x5e0); access by offset.
struct cLightingWorld {
    unsigned char _b[0x670];
    cLightingWorld(char* debugName);
    ~cLightingWorld();
};

struct VObj { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
              virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
              virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
              virtual void f12(void*); virtual void f13(); };

// @ 0x0070d2c0
cLightingWorld::cLightingWorld(char* debugName)
{
    unsigned char* p = _b;
    unsigned char* q;

    *(void**)(p + 0x00) = (void*)0x0140c760;
    *(void**)(p + 0x04) = (void*)0x0140c74c;
    *(int*)(p + 0x08) = 0;
    *(void**)(p + 0x0c) = debugName;
    *(int*)(p + 0x10) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(float*)(p + 0x1c) = *(const float*)0x013f9c6c;
    *(float*)(p + 0x20) = *(const float*)0x013f9c6c;
    *(int*)(p + 0x24) = 0;
    *(float*)(p + 0x28) = *(const float*)0x013ec4d0;
    *(float*)(p + 0x2c) = *(const float*)0x013ec4d0;
    *(float*)(p + 0x30) = *(const float*)0x013f1cac;
    *(int*)(p + 0x34) = 4;
    *(int*)(p + 0x38) = 0x10;
    *(int*)(p + 0x3c) = 0xc8;
    *(float*)(p + 0x40) = *(const float*)0x01629884;
    *(float*)(p + 0x44) = *(const float*)0x01629888;
    *(float*)(p + 0x48) = *(const float*)0x0162988c;
    *(int*)(p + 0x4c) = 0;
    *(int*)(p + 0x50) = 0;
    *(int*)(p + 0x54) = 0;
    *(int*)(p + 0x60) = 0;
    *(unsigned short*)(p + 0x64) = 0;
    *(unsigned short*)(p + 0x66) = 0;
    *(float*)(p + 0x68) = *(const float*)0x01629858;
    *(float*)(p + 0x6c) = *(const float*)0x0162985c;
    *(float*)(p + 0x70) = *(const float*)0x01629860;
    *(float*)(p + 0x74) = *(const float*)0x01485720;
    ((HM*)(p + 0x78))->Assign((const void*)0x016299ac);
    *(unsigned short*)(p + 0x9c) = 0;
    *(unsigned short*)(p + 0x9e) = 0;
    *(float*)(p + 0xa0) = *(const float*)0x01629858;
    *(float*)(p + 0xa4) = *(const float*)0x0162985c;
    *(float*)(p + 0xa8) = *(const float*)0x01629860;
    *(float*)(p + 0xac) = *(const float*)0x01485720;
    ((HM*)(p + 0xb0))->Assign((const void*)0x016299ac);
    *(float*)(p + 0xd4) = *(const float*)0x01629858;
    *(float*)(p + 0xd8) = *(const float*)0x0162985c;
    *(float*)(p + 0xdc) = *(const float*)0x01629860;
    *(unsigned char*)(p + 0xe0) = 0;
    *(float*)(p + 0x240) = *(const float*)0x01629858;
    *(float*)(p + 0x244) = *(const float*)0x0162985c;
    *(float*)(p + 0x248) = *(const float*)0x01629860;
    *(int*)(p + 0x24c) = 0;
    *(int*)(p + 0x250) = 0;
    *(unsigned char*)(p + 0x260) = 0;
    *(unsigned char*)(p + 0x261) = 0;
    *(unsigned short*)(p + 0x262) = 0;
    *(int*)(p + 0x264) = 0;
    *(int*)(p + 0x268) = 0;
    *(int*)(p + 0x26c) = 0;
    *(int*)(p + 0x270) = 0;
    *(int*)(p + 0x280) = 0;
    *(int*)(p + 0x284) = 0;
    *(int*)(p + 0x288) = 0;
    *(int*)(p + 0x28c) = 0;
    *(int*)(p + 0x420) = 0;
    *(unsigned char*)(p + 0x424) = 0;
    *(int*)(p + 0x428) = 0;
    *(int*)(p + 0x42c) = 0;
    *(int*)(p + 0x430) = 0;
    *(int*)(p + 0x43c) = 0x7f;
    *(int*)(p + 0x440) = 0x3fffffff;
    *(int*)(p + 0x444) = 0x3fffffff;
    *(int*)(p + 0x448) = 0;
    q = p + 0x44c;
    *(int*)(q + 0x00) = 0;
    *(int*)(q + 0x04) = 0;
    *(int*)(q + 0x08) = 0;
    *(int*)(q + 0x0c) = 0;
    *(int*)(q + 0x10) = 0;
    *(int*)(q + 0x14) = 0;
    ((HD3D*)q)->Op(0);
    *(int*)(q + 0x18) = 0;
    *(int*)(q + 0x1c) = 0;
    *(int*)(q + 0x20) = 0;
    *(int*)(q + 0x24) = 0;
    q = p + 0x490;
    *(void**)(p + 0x488) = q;
    *(void**)(p + 0x47c) = q;
    *(void**)(p + 0x478) = q;
    *(void**)(p + 0x480) = q + 0x100;
    *(unsigned char*)(p + 0x590) = 0;
    *(int*)(p + 0x594) = 0;
    *(int*)(p + 0x598) = 0;
    *(int*)(p + 0x59c) = 0;
    *(int*)(p + 0x5ac) = 0x3fffffff;
    *(int*)(p + 0x5b0) = 0x3fffffff;
    *(int*)(p + 0x5a8) = 0x7f;
    *(int*)(p + 0x5b4) = 0;
    *(int*)(p + 0x5b8) = 0;
    *(int*)(p + 0x5bc) = 0;
    *(unsigned char*)(p + 0x5cc) = 0;
    *(int*)(p + 0x5d0) = 0;
    *(int*)(p + 0x5c8) = -1;
    *(int*)(p + 0x5d4) = 0;
    *(int*)(p + 0x5d8) = 0;
    *(int*)(p + 0x5dc) = 0;
    *(int*)(p + 0x5e8) = 0;
    *(int*)(p + 0x5ec) = 0;
    *(int*)(p + 0x5f0) = 0;
    *(int*)(p + 0x5fc) = 0;
    q = p + 0x600;
    *(void**)(q + 4) = q;
    *(void**)(q + 0) = q;
    *(int*)(p + 0x608) = 0;
    *(int*)(p + 0x60c) = 0;
    *(int*)(p + 0x610) = 0;
    *(int*)(p + 0x61c) = 0x7f;
    *(int*)(p + 0x620) = 0x3fffffff;
    *(int*)(p + 0x624) = 0x3fffffff;
    *(int*)(p + 0x628) = 0;
    *(int*)(p + 0x62c) = 0;
    *(int*)(p + 0x630) = 0;
    *(int*)(p + 0x63c) = 0;
    *(int*)(p + 0x640) = 0;
    *(int*)(p + 0x644) = 0;
    *(int*)(p + 0x650) = 0x7f;
    *(int*)(p + 0x654) = 0x3fffffff;
    *(int*)(p + 0x658) = 0x3fffffff;
    *(int*)(p + 0x65c) = -1;
    *(unsigned char*)(p + 0x660) = 0;
    *(int*)(p + 0x420) = 0;
    InitAtmBuffer(p + 0xf0, 0, 0x150);
}

// @ 0x0070d6d0
cLightingWorld::~cLightingWorld()
{
    unsigned char* p = _b;
    ((H63c*)(p + 0x63c))->Free();
    if ((*(int*)(p + 0x628) != 0) && (*(int*)(*(int*)(p + 0x628) - 4) != 0))
        EFree(*(void**)(p + 0x628));
    ((H608*)(p + 0x608))->Free();
    ((HList*)(p + 0x600))->Dtor();
    if ((*(int*)(p + 0x5e8) != 0) && (*(int*)(*(int*)(p + 0x5e8) - 4) != 0))
        EFree(*(void**)(p + 0x5e8));
    if ((*(int*)(p + 0x5d4) != 0) && (*(int*)(*(int*)(p + 0x5d4) - 4) != 0))
        EFree(*(void**)(p + 0x5d4));
    if ((*(int*)(p + 0x5b4) != 0) && (*(int*)(*(int*)(p + 0x5b4) - 4) != 0))
        EFree(*(void**)(p + 0x5b4));
    ((H608*)(p + 0x594))->Free();
    {
        int e = *(int*)(p + 0x478);
        if ((e != 0) && (e != *(int*)(p + 0x488)))
            EFree((void*)e);
    }
    ((H44c*)(p + 0x44c))->Free();
    if (*(void**)(p + 0x448) != 0)
        ((VObj*)*(void**)(p + 0x448))->f3();
    ((HDeque*)(p + 0x428))->Dtor();
    if (*(void**)(p + 0x24c) != 0)
        ((VObj*)*(void**)(p + 0x24c))->f1();
    if ((*(int*)(p + 0x4c) != 0) && (*(int*)(*(int*)(p + 0x4c) - 4) != 0))
        EFree(*(void**)(p + 0x4c));
    *(void**)(p + 0x04) = (void*)0x013ec458;
    *(void**)(p + 0x00) = (void*)0x013eb938;
}

// @ 0x0070dc90
struct cLightingManager {
    unsigned char _d[0x1e0];
    cLightingWorld* MakeWorld(int owner, int a3, void* arg4);
    char Shutdown();
};

cLightingWorld* cLightingManager::MakeWorld(int owner, int a3, void* arg4)
{
    cLightingWorld* world = (cLightingWorld*)GAlloc(0x670, 0x10, 0, "Graphics", 0, 0, 0, 0);
    if (world != 0)
        world = new (world) cLightingWorld((char*)owner);
    ((HSmall*)world)->Op();
    if (arg4 != 0)
        ((VObj*)world)->f12(arg4);
    void* slot = ((HMap*)((char*)this + 0x2c))->Find(&owner);
    void* old = *(void**)slot;
    if (world != old)
    {
        if (world != 0)
            ((VObj*)world)->f0();
        *(void**)slot = world;
        if (old != 0)
            ((VObj*)old)->f1();
    }
    return world;
}

// @ 0x0070d850  (SP::cLightingWorld::AddLight)
// thiscall: ecx = cLightingWorld*, 4 stack args (colour, position, strength, size), ret 0x10.
unsigned __fastcall cLightingWorld_AddLight(void* self, int, const float* colour,
                                            const float* position, float strength, float size)
{
    unsigned char* p = (unsigned char*)self;
    if (*(void**)(p + 0x10) == 0)
        return 0xffffffff;

    // Reserve a slot in the mLocalLightCells deque.  create() copy-constructs the slot's
    // cLocalLightInfo from this source object, so its embedded fixed_vector must at least
    // look empty (an inline buffer) or the copy would try to allocate.
    LocalLightInfo seed;
    seed.mpVecBegin = seed.mBuffer;
    seed.mpVecEnd = seed.mBuffer;
    seed.mpVecCap = seed.mBuffer + 0x80;
    seed.mpInline = seed.mBuffer;
    unsigned slot = F_70cce0(p + 0x428, 0, &seed);

    // Resolve the pooled cLocalLightInfo storage for that slot (block + 4 + lane*0xc4).
    unsigned char* info = (unsigned char*)(*(int*)(*(int*)(p + 0x428) + (slot >> 7) * 4)
                                           + (slot & 0x7f) * 0xc4 + 4);
    InitAtmBuffer(info, 0, 0xc0);

    *(float*)(info + 0x10) = colour[0];
    *(float*)(info + 0x14) = colour[1];
    *(float*)(info + 0x18) = colour[2];
    *(float*)(info + 0x00) = position[0];
    *(float*)(info + 0x04) = position[1];
    *(float*)(info + 0x08) = position[2];
    *(float*)(info + 0x1c) = strength / (size + 1e-06f);
    *(float*)(info + 0x0c) = size;
    *(unsigned char*)(info + 0x24) = 1;
    ++*(int*)(p + 0x5d0);

    // Gather the grid cells the light overlaps.  In this build mFlags (+0x24) is
    // always set, so the per-cell path below is never taken.
    int cells[16 * 5]; // 16 x {z, xMin, yMin, xMax, yMax}
    int buildCount = (int)slot;
    int cellCount = (int)slot;
    if (*(unsigned char*)(info + 0x24) == 0)
    {
        buildCount = F_705740(0x10, colour, size, cells);
        cellCount = F_705050(buildCount, cells);
    }

    if ((*(unsigned char*)(info + 0x24) == 0) && (cellCount < 0x11))
    {
        F_708d90(info + 0x28, 0, (unsigned)cellCount);
        int index = 0;
        for (int c = 0; c < buildCount; ++c)
        {
            const int* cell = cells + c * 5;
            for (int y = cell[2]; y < cell[4]; ++y)
            {
                for (int x = cell[1]; x < cell[3]; ++x)
                {
                    int gridIndex = (cell[0] * 0x10 + y) * 0x10 + x;
                    int* gridEntry = (int*)(*(int*)(p + 0x628) + gridIndex * 4);
                    unsigned sample = *(unsigned*)gridEntry;
                    if ((int)sample < 0)
                    {
                        // Allocate a new global light sample through the pool, using a
                        // scratch vector whose intrusive list is drained and freed here.
                        unsigned char tmp[0x34];
                        *(int*)(tmp + 0x00) = 0;
                        *(int*)(tmp + 0x04) = 0;
                        *(int*)(tmp + 0x08) = 0;
                        *(int*)(tmp + 0x14) = 0;
                        *(int*)(tmp + 0x18) = 0;
                        *(int*)(tmp + 0x1c) = 0;
                        *(int*)(tmp + 0x28) = 0;
                        *(void**)(tmp + 0x2c) = tmp + 0x2c;
                        *(void**)(tmp + 0x30) = tmp + 0x2c;

                        sample = F_70c5e0(p + 0x63c, 0, tmp + 0x2c);

                        unsigned char* node = *(unsigned char**)(tmp + 0x2c);
                        while (node != tmp + 0x2c)
                        {
                            unsigned char* next = *(unsigned char**)node;
                            *(void**)(node + 4) = 0;
                            *(void**)node = 0;
                            node = next;
                        }
                        *(void**)(tmp + 0x2c) = 0;
                        *(void**)(tmp + 0x30) = 0;
                        if ((*(int*)(tmp + 0x14) != 0) && (*(int*)(*(int*)(tmp + 0x14) - 4) != 0))
                            EFree(*(void**)(tmp + 0x14));
                        if ((*(int*)(tmp + 0x00) != 0) && (*(int*)(*(int*)(tmp + 0x00) - 4) != 0))
                            EFree(*(void**)(tmp + 0x00));

                        *gridEntry = (int)sample;
                    }

                    unsigned char* sampleData =
                        (unsigned char*)(*(int*)(*(int*)(p + 0x63c) + (sample >> 7) * 4)
                                         + (sample & 0x7f) * 0x38 + 4);
                    *(unsigned*)(*(int*)(info + 0x28) + index * 8) = sample;
                    F_708810(p, 0, slot, index, sampleData);
                    ++index;
                }
            }
        }
        *(unsigned char*)(p + 0x660) = 1;
    }
    else
    {
        // Dense path: a single sample covers the whole light bounds.
        bool wasEmpty = (*(int*)(p + 0x5d4) == *(int*)(p + 0x5d8));
        F_708d90(info + 0x28, 0, 1);
        *(int*)(*(int*)(info + 0x28)) = -1;
        F_708810(p, 0, slot, 0, p + 0x5d4);

        if (!wasEmpty)
        {
            *(unsigned char*)(p + 0x660) = 1;
        }
        else
        {
            // Drain the mPendingSamples intrusive list (sentinel at +0x600, nodes at link-4).
            unsigned char* node = *(unsigned char**)(p + 0x600);
            node = node ? node - 4 : 0;
            unsigned char* end = (unsigned char*)(p + 0x600) - 4;
            while (node != end)
            {
                F_70c410(p, 0, (int)node);
                unsigned char* next = *(unsigned char**)(node + 4);
                node = next ? next - 4 : 0;
            }
        }
    }

    if ((*(unsigned char*)(*(int*)(p + 0x10) + 0x134) != 0) && (*(int*)(p + 0x448) != 0))
        F_705f40(p, 0, info);

    if (*(unsigned char*)(p + 0x590) == 0)
    {
        *(unsigned char*)(p + 0x590) = 1;
        MServer* ms = (MServer*)MessageServer();
        ms->m5(0x2495f34, 0, 0);
    }
    return slot;
}

// @ 0x0070ddd0
char cLightingManager::Shutdown()
{
    unsigned char* p = (unsigned char*)this;
    void* ms = MessageServer();
    if (ms != 0)
    {
        void* handler = (this != 0) ? (p + 4) : 0;
        ((MServer*)ms)->Unsubscribe(handler, 0xf62def, (int)0xffffd8f1);
    }
    // clear mLightingStates + mIDToWorldMap
    void* r = ConfigRangeOp1((void*)*(int*)(p + 0x1c), (void*)*(int*)(p + 0x1c), (void*)*(int*)(p + 0x18));
    ((HNuke*)(p + 0x18))->Nuke(r);
    {
        int begin = *(int*)(p + 0x18);
        int end = *(int*)(p + 0x1c);
        *(int*)(p + 0x1c) = end + ((end - begin) / 0x144) * 0x144;
    }
    void* n = (void*)*(int*)(p + 0x34);
    void* head = (void*)(p + 0x30);
    while (n != head)
    {
        ((HShut*)*(void**)((char*)n + 0x14))->Shutdown();
        n = RBTreeIncrement(n);
    }
    ((HNode*)(p + 0x2c))->Dtor((void*)*(int*)(p + 0x38));
    *(int*)(p + 0x34) = (int)head;
    *(int*)(p + 0x30) = (int)head;
    *(int*)(p + 0x38) = 0;
    *(unsigned char*)(p + 0x3c) = 0;
    *(int*)(p + 0x40) = 0;
    return 1;
}
