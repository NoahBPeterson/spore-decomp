// Slice s00a6f110 (gold7): hash-table install helpers, description-record builders
// and the smooth-step / rate helpers that live next to them.
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
//  * 0x00a6f930  HashTable::FindOrInsert   -- find a key, else insert a default value
//  * 0x00a6f9c0  DescInstaller::InstallA   -- bind factory hook +0x1c into table +0x44
//  * 0x00a6fa50  DescInstaller::InstallB   -- bind factory hook +0x24 into table +0x78
//  * 0x00a6fc30  cEffectsParser::AddDescription
//  * 0x00a6fd40  cEffectsParser::AddAnonDescription
//  * 0x00a6fe20  cSmoothTrail::Advance
//  * 0x00a6fee0  cEmitter::Forward         -- temporarily set flag bits around a vcall
//  * 0x00a6ff20  cSmoothTrail::Reset
#include "types.h"
#include <string.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

inline void* operator new(unsigned int, void* p) { return p; }

extern "C" void op_del_arr(void* p);      // 0xf47380 operator_delete__

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// EA::ArgScript::HashTable  (0x20 bytes, buckets at +4, count at +8)
// ---------------------------------------------------------------------------
struct EString {
    char data[0x10];
    void assign(const char* begin, const char* end);      // 0x454cb0 ret 8
};

void MakeCaseInsensitive(EString* s);                     // 0x8409b0 cdecl

struct HTInsertOut {
    u32   mnHash;                                        // +0x00
    void* mpNode;                                        // +0x04
};

struct HashTable {
    char    pad0[4];
    void**  mpBucketArray;                               // +0x04
    int     mnBucketCount;                               // +0x08
    char    pad1[0x20 - 0x0c];

    struct iterator {
        void* mpNode;
        iterator() {}
        iterator(const iterator& o) : mpNode(o.mpNode) {}
        ~iterator() {}
        bool operator==(const iterator& o) const { return mpNode == o.mpNode; }
        bool operator!=(const iterator& o) const { return mpNode != o.mpNode; }
    };

    iterator find(const EString& key) const;             // 0x7e2ea0 (sret, ret 8)
    iterator end() const
    {
        iterator it;
        it.mpNode = mpBucketArray[mnBucketCount];
        return it;
    }
    void*  insert_node(HTInsertOut* out, const EString* key, u32 hash);  // 0xa6a810 ret 0xc
    void** FindOrInsert(const EString& key);             // @0xa6f930
};

// eastl::pair<const EString, void*> -- only its out-of-line ctor matters here.
struct HTPair {
    EString first;
    void*   second;
    HTPair(const EString& k, void* v);                   // 0x6a3f40
};

// ---------------------------------------------------------------------------
// 0x00a6f930 -- hash lookup with default insert (operator[]-like)
// ---------------------------------------------------------------------------
// @ 0x00a6f930
void** HashTable::FindOrInsert(const EString& key)
{
    iterator it = find(key);
    if (it.mpNode != end().mpNode)
        return (void**)((char*)it.mpNode + 0x10);

    HTInsertOut out;
    void* def = 0;
    HTPair pair(key, def);
    insert_node(&out, (const EString*)&pair, 0);
    return (void**)((char*)out.mpNode + 0x10);
}

// ---------------------------------------------------------------------------
// DescInstaller -- two parallel index -> HashTable maps plus the shared
// case-insensitive name buffer.
// ---------------------------------------------------------------------------
struct DescInstaller {
    char       pad0[0x20];
    void*      mFactory;                                 // +0x20
    char       pad1[0x20];
    HashTable* mTablesA;                                 // +0x44
    char       pad2[0x30];
    HashTable* mTablesB;                                 // +0x78
    char       pad3[0x3c4 - 0x7c];
    EString    mName;                                    // +0x3c4

    void InstallA(const char* name, int index, int arg);
    void InstallB(const char* name, int index, int arg);
};

template <class R> inline R PV2(void* o, int off, int a, int b)
{
    return ((R (__thiscall *)(void*, int, int))(*(void***)o)[off / 4])(o, a, b);
}

// @ 0x00a6f9c0
void DescInstaller::InstallA(const char* name, int index, int arg)
{
    HashTable::iterator it;
    mName.assign(name, name + strlen(name));
    MakeCaseInsensitive(&mName);

    HashTable* table = &mTablesA[index];
    it = table->find(mName);
    if (it == table->end()) {
        int value = PV2<int>(mFactory, 0x1c, index, arg);
        *table->FindOrInsert(mName) = (void*)value;
    }
}

// @ 0x00a6fa50
void DescInstaller::InstallB(const char* name, int index, int arg)
{
    mName.assign(name, name + strlen(name));
    MakeCaseInsensitive(&mName);

    HashTable* table = &mTablesB[index];
    if (table->find(mName) == table->end()) {
        int value = PV2<int>(mFactory, 0x24, index, arg);
        *table->FindOrInsert(mName) = (void*)value;
    }
}

// ---------------------------------------------------------------------------
// description record (0x84 bytes) and its LOD-scale vector
// ---------------------------------------------------------------------------
struct cTransform {
    u16  flags;                                          // +0x00
    u16  count;                                          // +0x02
    Vec3 pos;                                            // +0x04
    float scale;                                         // +0x10
};

struct FVec {
    float* b; float* e; float* c;
    ~FVec() { if (b && ((int*)b)[-1]) op_del_arr(b); }
};

struct DescRec {
    int        type;                                     // +0x00
    u32        flags;                                    // +0x04
    cTransform xf;                                       // +0x08
    char       pad0[0x40 - 0x08 - sizeof(cTransform)];
    u8         lodBegin;                                 // +0x40
    u8         lodEnd;                                   // +0x41
    char       pad1[2];
    FVec       lod;                                      // +0x44
    char       pad2[0x70 - 0x50];
    u32        appFlags;                                 // +0x70
    u32        appFlagsMask;                             // +0x74
    u16        field78;                                  // +0x78
    char       pad3[0x80 - 0x7a];
    int        field80;                                  // +0x80

    DescRec();                                           // 0x00a6e4b0
    DescRec(const DescRec&);                             // 0x00a6a2f0
};

struct RecVec {
    DescRec* begin;                                      // +0x00
    DescRec* end;                                        // +0x04
    DescRec* cap;                                        // +0x08
    void PushEnd(DescRec* pos, const DescRec& v);        // 0x00a6fae0
    void push_back(const DescRec& v)
    {
        if (end < cap) {
            DescRec* p = end;
            end = p + 1;
            new (p) DescRec(v);
        } else {
            PushEnd(end, v);
        }
    }
};

struct cArguments;

struct cEffectsParser {
    char   pad0[0x14];
    void*  mParser;                                      // +0x14
    char   pad1[0x20 - 0x18];
    void*  mFactory;                                     // +0x20
    char   pad2[0x32c - 0x24];
    u32    mFlags;                                       // +0x32c
    char   pad3[0x36c - 0x330];
    RecVec mDescs;                                        // +0x36c
    char   pad4[0x390 - 0x378];
    u16    mField390;                                    // +0x390
    char   pad5[0x39c - 0x392];
    u8     mFlag39c;                                     // +0x39c
    u8     mFlag39d;                                     // +0x39d

    int  MapFindB(const char* name, int type);           // 0x00a6eb60 ret 8
    void ParseDescRecOptions(cArguments* args, DescRec* rec);   // 0x00a6f110 ret 8

    void AddDescription(cArguments* args, const char* name, int type, bool flag);
    void AddAnonDescription(cArguments* args, int a, int b, bool flag);
};

// @ 0x00a6fc30
void cEffectsParser::AddDescription(cArguments* args, const char* name, int type, bool flag)
{
    DescRec rec;
    rec.field80 = MapFindB(name, type);
    if (rec.field80 >= 0) {
        rec.type = type;
        rec.field78 = mField390;

        u32 f = rec.flags;
        if (mFlag39c) f |= 2; else f &= ~2u;
        if (mFlag39d) f |= 8; else f &= ~8u;
        if (flag)     f |= 1; else f &= ~1u;
        rec.flags = f;

        ParseDescRecOptions(args, &rec);
        mDescs.push_back(rec);
        mFlags |= rec.appFlagsMask;
    }
}

// @ 0x00a6fd40
void cEffectsParser::AddAnonDescription(cArguments* args, int a, int b, bool flag)
{
    DescRec rec;
    int value = PV2<int>(mFactory, 0x1c, a, b);
    rec.field80 = value;
    rec.type = a;
    rec.field78 = mField390;
    if (flag) rec.flags |= 1; else rec.flags &= ~1u;

    ParseDescRecOptions(args, &rec);
    mDescs.push_back(rec);
    mFlags |= rec.appFlagsMask;
}

// ---------------------------------------------------------------------------
// 0x00a6fe20 / 0x00a6ff20 -- rate ramp used by the effect emitters
// ---------------------------------------------------------------------------
struct cSmoothTrail {
    char  pad0[0x14];
    void* mSource;                                       // +0x14
    char  pad1[0x80 - 0x18];
    int   mIndex;                                        // +0x80
    int   mPrevIndex;                                    // +0x84
    float mCurrent;                                      // +0x88

    void Advance(float delta, int count);
    void Reset();
};

// SSE clamp: the retail copy keeps the value in xmm0 and clamps it against the
// memory-homed bounds, so it is written as a short asm block.
__forceinline float Clamp(float value, float lo, float hi)
{
    __asm {
        movss xmm0, value
        maxss xmm0, lo
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}

// Truncating float->int of the retail copy: convert with the current SSE
// rounding mode, then step down when the rounded value overshoots.
__forceinline int FloorInt(float v)
{
    __asm {
        movss   xmm0, v
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov     ecx, eax
        sub     ecx, 1
        ucomiss xmm0, xmm1
        cmovb   eax, ecx
    }
}

// @ 0x00a6fe20
void cSmoothTrail::Advance(float delta, int count)
{
    float v = *(float*)((char*)mSource + 0x60) + delta;
    v = Clamp(v, 1.0f, (float)count - 1e-06f);
    if (v != mCurrent) {
        mPrevIndex = mIndex;
        mCurrent = v;
        float t = v;
        mIndex = FloorInt(t);
    }
}

// @ 0x00a6ff20
void cSmoothTrail::Reset()
{
    mIndex = 1;
    mPrevIndex = 1;
    mCurrent = 1.0f;
}
