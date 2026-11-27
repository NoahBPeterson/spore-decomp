// src/game/Swarm/EffectsParser.cpp -- migrated from slice(s) s00a6dfc0, s00a6f110 by tools/migrate/rewrite.py
// Object file: Swarm/EffectsParser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/Swarm/cTransform.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void op_del_arr(void* p);   // 0xf47380 operator_delete__
extern float g_degToRad;                                 // 0x1676aa4
#include <xmmintrin.h>
#include <string.h>

// ---- items of slice s00a6f110 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
inline void* operator new(unsigned int, void* p) { return p; }
struct Vec3 { float x, y, z; };
struct cArguments {
    int* OptionArguments(const char* name, int count);                              // 0x838330 ret 8
    int* OptionArguments(const char* name, int* outCount, int minCount, int maxCount); // 0x838130 ret 0x10
    bool HasFlag(const char* name);                                                  // 0x8380b0 ret 4
};
struct FVec {
    float* b; float* e; float* c;
    void DoInsertValue(float* pos, const float& v);      // 0x455660 thiscall ret 8
    void push_back(const float& v)
    {
        if (e < c) { new (e) float(v); ++e; }
        else DoInsertValue(e, v);
    }
    ~FVec() { if (b && ((int*)b)[-1]) op_del_arr(b); }
};
struct LodScale { float emit, size, alpha; };
struct LodVec {
    LodScale* b; LodScale* e; LodScale* c;
    void resize(int n);                                  // 0xa6f010 thiscall ret 4
};
struct cTransform {
    u16 flags;
    u16 count;
    Vec3 pos;                                            // +0xc in the record
    float scale;                                         // +0x18
    void RotateZ(float a);                               // 0x7d1ac0 ret 4
    void RotateY(float a);                               // 0x6b9050 ret 4 (MatX::Rotate)
    void PreRotateX(float a);                            // 0x5a2d90 ret 4
};
struct DescRec {
    int type;
    u32 flags;                                           // +4
    cTransform xf;                                       // +8
    char pad[0x40 - 8 - sizeof(cTransform)];
    u8 lodBegin;                                         // +0x40
    u8 lodEnd;                                           // +0x41
    char pad1[2];
    LodVec lod;                                          // +0x44
    char pad2[0x70 - 0x50];
    u32 appFlags;                                        // +0x70
    u32 appFlagsMask;                                    // +0x74
    char pad3[2];
    u16 chance;                                          // +0x7a
    float timeScale;                                     // +0x7c
};
template <class R> inline R PV0(void* o, int off, int a) { return ((R (__thiscall *)(void*, int))(*(void***)o)[off / 4])(o, a); }
template <class R> inline R PV1(void* o, int off, void* ret, int a) { return ((R (__thiscall *)(void*, void*, int))(*(void***)o)[off / 4])(o, ret, a); }
static inline const int& imax(const int& a, const int& b) { return (a < b) ? b : a; }
struct cEffectsParser {
    char pad[0x14];
    void* mParser;                                       // +0x14

    float ParseFloat(int tok) { return PV0<float>(mParser, 0x98, tok); }
    u8    ParseByte(int tok) { return PV0<u8>(mParser, 0xa0, tok); }
    int   ParseInt(int tok) { return PV0<int>(mParser, 0x9c, tok); }
    bool  ParseBool(int tok) { return PV0<bool>(mParser, 0x94, tok); }

    // @ 0x00a6f110
    void ParseDescRecOptions(cArguments* args, DescRec* rec);
};
// ---- items of slice s00a6f110 end

// ---- items of slice s00a6dfc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  MakeCaseInsensitive(void* s);                              // 0x8409b0
extern "C" void  v00a6e9e0(void** out, void* map);                          // 0xa6e9e0 map find
extern "C" void  v00a6ea80(void** out, void* map);                          // 0xa6ea80 map insert
extern "C" void  v00b20930(void** out, void* key);                          // 0xb20930 MapStrFind::Find
extern "C" const char** v00838330(void* args, const char* name, int n);      // 0x838330 OptionArguments
extern "C" const char** v00838130(void* args, const char* name, int* count, int lo, int hi); // 0x838130
extern "C" int   v008380b0(void* args, const char* flag);                   // 0x8380b0 HasFlag
extern "C" unsigned char v00840bb0(const char* s, const void* tbl);         // 0x840bb0 ParseEnum
extern const char  kTextureOpt[];   // 0x1455d84 "texture"
extern const char  kDrawOpt[];      // 0x1455e94 "draw"
extern const char  kBufferOpt[];    // 0x1455e8c "buffer"
extern const char  kLayerOpt[];     // 0x1455e84 "layer"
extern const char  kSortOffsetOpt[];// 0x1455e78 "sortOffset"
extern const char  kLightFlag[];    // 0x1455e70 "light"
extern const char  kNoFogFlag[];    // 0x1455e68 "noFog"
extern const char  kShadowFlag[];   // 0x142ee28 "shadow"
extern const char  kNoShadowFlag[]; // 0x1455e5c "noShadow"
extern const char  kNoCullFlag[];   // 0x1455e54 "noCull"
extern const char* gFlagUser1;      // 0x1554778 "user1"
extern const char* gFlagUser2;      // 0x155477c "user2"
extern const char* gFlagUser3;      // 0x1554780 "user3"
extern const char  gDecalEnumTbl[]; // 0x15546e8 enum table ptr
namespace EA {
namespace Swarm {
struct EString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void* mpAlloc;      // +0x0c
    void assign(const char* first, const char* last);   // 0x00454cb0
};
}
}
namespace EA {
namespace Swarm {
struct DrawInfoTarget;
}
}
namespace EA {
namespace Swarm {
class cEffectsParser_s00a6_dfc0 { public:
    char      _pad00[0x10];
    unsigned  mFlags;               // +0x10
    char      _pad14[0x0c];
    void*     mpColl;               // +0x20
    char      _pad24[0x20];
    int       m44;                  // +0x44
    char      _pad48[0x30];
    int       m78;                  // +0x78
    char      _pad7c[0x10];
    void*     mpSaveColl;           // +0x8c
    char      _pad90[0x28];
    char      mEditors[0x13 * 0x20]; // +0xb8
    char      mName[0x10];          // +0x3c4

    long long EffectsMapID(const char* s);                          // 00a6e600
    long long MapFindA(const char* s);                              // 00a6eaf0
    long long MapFindB(const char* s, int idx);                     // 00a6eb60
    long long MapFindC(const char* s, int idx);                     // 00a6ebd0
    long long LookupRes(int idx, const char* s);                    // 00a6ec40
    void      ParseDrawInfoOptions(void* args, void* obj, DrawInfoTarget* t); // 00a6ed80 0x00a6ed80
    int       GetInheritedA(int a, int depth, void* c);             // 00a6f090
    int       GetInheritedB(int a, int depth, void* c);             // 00a6f0d0
};
}
}
namespace EA {
namespace Swarm {
struct DrawInfoTarget {
    int      m00;               // +0x00
    int      m04;               // +0x04
    char     m08;               // +0x08
    char     mType;             // +0x09 (0xf = text; else decal)
    char     mFlags;            // +0x0a
    char     mBuffer;           // +0x0b
    short    mLayer;            // +0x0c
    char     _pad0e[2];
    float    mSortOffset;       // +0x10
    char     _pad14[4];
    unsigned mResA;             // +0x18
    unsigned mResB;             // +0x1c
};
}
}
// ---- items of slice s00a6dfc0 end

// ---- items of slice s00a6f110_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct EString_s00a6_f110__g7 {
    char data[0x10];
    void assign(const char* begin, const char* end);      // 0x454cb0 ret 8
};
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
        void** mpBucket;
        iterator() {}
        iterator(const iterator& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
        ~iterator() {}
        bool operator==(const iterator& o) const { return mpNode == o.mpNode; }
        bool operator!=(const iterator& o) const { return mpNode != o.mpNode; }
    };

    iterator find(const EString_s00a6_f110__g7& key) const;             // 0x7e2ea0 (sret, ret 8)
    iterator end() const
    {
        iterator it;
        it.mpNode = mpBucketArray[mnBucketCount];
        it.mpBucket = mpBucketArray + mnBucketCount;
        return it;
    }
    void*  insert_node(HTInsertOut* out, const EString_s00a6_f110__g7* key, u32 hash);  // 0xa6a810 ret 0xc
    void** FindOrInsert(const EString_s00a6_f110__g7& key);             // @0xa6f930
};
struct HTPair {
    EString_s00a6_f110__g7 first;
    void*   second;
    HTPair(const EString_s00a6_f110__g7& k, void* v);                   // 0x6a3f40
};
struct DescriptionFactory {
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
    virtual void* CreateDescription(int index, int arg); // +0x1c
};
struct DescInstaller {
    char       pad0[0x20];
    DescriptionFactory* mFactory;                       // +0x20
    char       pad1[0x20];
    HashTable* mTablesA;                                 // +0x44
    char       pad2[0x30];
    HashTable* mTablesB;                                 // +0x78
    char       pad3[0x3c4 - 0x7c];
    EString_s00a6_f110__g7    mName;                                    // +0x3c4

    void InstallA(const char* name, int index, int arg);
    void InstallB(const char* name, int index, int arg);
};
template <class R> inline R PV2(void* o, int off, int a, int b)
{
    return ((R (__thiscall *)(void*, int, int))(*(void***)o)[off / 4])(o, a, b);
}
struct cTransform_s00a6_f110__g7 {
    u16  flags;                                          // +0x00
    u16  count;                                          // +0x02
    Vec3 pos;                                            // +0x04
    float scale;                                         // +0x10
};
struct FVec_s00a6_f110__g7 {
    float* b; float* e; float* c;
    ~FVec_s00a6_f110__g7() { if (b && ((int*)b)[-1]) op_del_arr(b); }
};
struct DescRec_s00a6_f110__g7 {
    int        type;                                     // +0x00
    u32        flags;                                    // +0x04
    cTransform_s00a6_f110__g7 xf;                                       // +0x08
    char       pad0[0x40 - 0x08 - sizeof(cTransform_s00a6_f110__g7)];
    u8         lodBegin;                                 // +0x40
    u8         lodEnd;                                   // +0x41
    char       pad1[2];
    FVec_s00a6_f110__g7       lod;                                      // +0x44
    char       pad2[0x70 - 0x50];
    u32        appFlags;                                 // +0x70
    u32        appFlagsMask;                             // +0x74
    u16        field78;                                  // +0x78
    char       pad3[0x80 - 0x7a];
    int        field80;                                  // +0x80

    DescRec_s00a6_f110__g7();                                           // 0x00a6e4b0
    DescRec_s00a6_f110__g7(const DescRec_s00a6_f110__g7&);                             // 0x00a6a2f0
};
struct RecVec {
    DescRec_s00a6_f110__g7* begin;                                      // +0x00
    DescRec_s00a6_f110__g7* end;                                        // +0x04
    DescRec_s00a6_f110__g7* cap;                                        // +0x08
    void PushEnd(DescRec_s00a6_f110__g7* pos, const DescRec_s00a6_f110__g7& v);        // 0x00a6fae0
    void push_back(const DescRec_s00a6_f110__g7& v)
    {
        if (end < cap) {
            DescRec_s00a6_f110__g7* p = end;
            end = p + 1;
            new (p) DescRec_s00a6_f110__g7(v);
        } else {
            PushEnd(end, v);
        }
    }
};
struct cArguments;
struct cEffectsParser_s00a6_f110__g7 {
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
    void ParseDescRecOptions(cArguments* args, DescRec_s00a6_f110__g7* rec);   // 0x00a6f110 ret 8

    void AddDescription(cArguments* args, const char* name, int type, bool flag);  // 0x00a6fc30 (cEffectsParser::AddDescription)
    void AddAnonDescription(cArguments* args, int a, int b, bool flag);  // 0x00a6fd40 (cEffectsParser::AddAnonDescription)
};
// ---- items of slice s00a6f110_g7 end

// @ 0x00a6ed80
namespace EA { namespace Swarm {
void cEffectsParser_s00a6_dfc0::ParseDrawInfoOptions(void* args, void* obj, DrawInfoTarget* t)
{
    void* self = this;
    char* ebp = (char*)self;
    char* edi = (char*)args;
    if (t->mType == 0x0f) {
        const char** oa = v00838330(args, kTextureOpt, 1);
        if (oa != 0) {
            char* name = (char*)oa[0];
            char* e = name;
            while (*e) ++e;
            ((EString*)(ebp + 0x3c4))->assign(name, e);
            MakeCaseInsensitive(ebp + 0x3c4);
            char* ep = ebp + 0xb8;
            void* local[3];
            {
                v00a6e9e0(local, ep);
            }
            if ((int)local[0] != *(int*)(*(int*)(ep + 4) + *(int*)(ep + 8) * 4)) {
                t->mResA = ((unsigned*)local[0])[4];
                t->mResB = ((unsigned*)local[0])[5];
                goto after_type;
            }
            {
                void* save = *(void**)(ebp + 0x8c);
                if (save != 0) {
                    char c = (*(char(__thiscall**)(void*, int, const char*, void*))(*((char**)save) + 8))(save, 0, name, local);
                    if (c) {
                        t->mResA = ((unsigned*)local)[0];
                        t->mResB = ((unsigned*)local)[1];
                        goto after_type;
                    }
                    if (((*(unsigned*)(ebp + 0x10) >> 1) & 1) == 0) {
                        void* it[2];
                        char* d = ebp + 0x3d4;
                        {
                            v00b20930(it, d);
                        }
                        if ((int)it[0] == (int)(ebp + 0x3d8)) {
                            v00a6ea80(it, d);
                        }
                    }
                }
                t->mResA = 0xffffffff;
                t->mResB = 0xffffffff;
            }
        }
    }
    else {
        int lc = 0;
        const char** oa = v00838130(args, kDrawOpt, &lc, 1, 2);
        (void)lc;
        if (oa != 0) {
            t->mType = (char)v00840bb0(oa[0], gDecalEnumTbl);
            if (lc > 1) {
                long long r = this->LookupRes(0, oa[1]);
                t->mResA = (unsigned)r;
                t->mResB = (unsigned)(r >> 32);
            }
        }
    }
after_type:
    {
        const char** oa = v00838330(args, kBufferOpt, 1);
        if (oa != 0) {
            unsigned char r = (*(unsigned char(__thiscall**)(void*, const char*))(*((char**)obj) + 0xa0))(obj, oa[0]);
            t->mBuffer = (char)r;
        }
    }
    {
        const char** oa = v00838330(args, kLayerOpt, 1);
        if (oa != 0) {
            short r = (*(short(__thiscall**)(void*, const char*))(*((char**)obj) + 0x9c))(obj, oa[0]);
            t->mLayer = r;
        }
    }
    {
        const char** oa = v00838330(args, kSortOffsetOpt, 1);
        if (oa != 0) {
            float r = (*(float(__thiscall**)(void*, const char*))(*((char**)obj) + 0x98))(obj, oa[0]);
            t->mSortOffset = r;
        }
    }
    if (v008380b0(edi, kLightFlag))
        t->mFlags |= 1;
    if (v008380b0(edi, kNoFogFlag))
        t->mFlags |= 2;
    if (v008380b0(edi, kShadowFlag))
        t->mFlags |= 8;
    if (v008380b0(edi, kNoShadowFlag))
        t->mFlags &= (char)0xf7;
    if (v008380b0(edi, kNoCullFlag))
        t->mFlags |= 0x10;
    if (v008380b0(edi, gFlagUser1))
        t->mFlags |= 0x20;
    if (v008380b0(edi, gFlagUser2))
        t->mFlags |= 0x40;
    if (v008380b0(edi, gFlagUser3))
        t->mFlags |= 0x80;
}
}}  // namespace EA::Swarm

// @ 0x00a6f090
namespace EA { namespace Swarm {
int cEffectsParser_s00a6_dfc0::GetInheritedA(int a, int depth, void* c)
{
    if (depth < 3)
        goto zero;
    {
        int idx = MapFindB(*(const char**)(a + 8), (int)c);
        if (idx < 0)
            goto zero;
        {
            char* coll = *(char**)((char*)this + 0x20);
            return (*(int(__thiscall**)(char*, int, void*))(*((char**)coll) + 0x20))(coll, idx, c);
        }
    }
zero:
    return 0;
}
}}  // namespace EA::Swarm

// @ 0x00a6f0d0
namespace EA { namespace Swarm {
int cEffectsParser_s00a6_dfc0::GetInheritedB(int a, int depth, void* c)
{
    if (depth < 3)
        goto zero;
    {
        int idx = MapFindC(*(const char**)(a + 8), (int)c);
        if (idx < 0)
            goto zero;
        {
            char* coll = *(char**)((char*)this + 0x20);
            return (*(int(__thiscall**)(char*, int, void*))(*((char**)coll) + 0x28))(coll, idx, c);
        }
    }
zero:
    return 0;
}
}}  // namespace EA::Swarm

// @ 0x00a6f110
void cEffectsParser::ParseDescRecOptions(cArguments* args, DescRec* rec)
{
    int* p = args->OptionArguments("offset", 1);
    if (p) {
        Vec3 tmp;
        Vec3* v = (Vec3*)PV1<Vec3*>(mParser, 0xa8, &tmp, p[0]);
        float vy = v->y, vz = v->z, vx = v->x;
        rec->xf.pos.y = vy + rec->xf.pos.y;
        rec->xf.pos.z = vz + rec->xf.pos.z;
        rec->xf.pos.x = vx + rec->xf.pos.x;
        rec->xf.flags |= 4;
        rec->xf.count += 1;
    }

    p = args->OptionArguments("rotateZ", 1);
    if (p) rec->xf.RotateZ(ParseFloat(p[0]) * g_degToRad);
    p = args->OptionArguments("rotateY", 1);
    if (p) rec->xf.RotateY(ParseFloat(p[0]) * g_degToRad);
    p = args->OptionArguments("rotateX", 1);
    if (p) rec->xf.PreRotateX(ParseFloat(p[0]) * g_degToRad);

    p = args->OptionArguments("rotateXYZ", 3);
    if (p) {
        cTransform* xf = &rec->xf;
        xf->RotateZ(ParseFloat(p[2]) * g_degToRad);
        xf->RotateY(ParseFloat(p[1]) * g_degToRad);
        xf->PreRotateX(ParseFloat(p[0]) * g_degToRad);
    }
    p = args->OptionArguments("rotateZXY", 3);
    if (p) {
        cTransform* xf = &rec->xf;
        xf->RotateY(ParseFloat(p[2]) * g_degToRad);
        xf->PreRotateX(ParseFloat(p[1]) * g_degToRad);
        xf->RotateZ(ParseFloat(p[0]) * g_degToRad);
    }

    p = args->OptionArguments("scale", 1);
    if (p) {
        float s = ParseFloat(p[0]) * rec->xf.scale;
        rec->xf.flags |= 1;
        rec->xf.count += 1;
        rec->xf.scale = s;
    }

    int lodCount;
    p = args->OptionArguments("lodRange", 2);
    if (p) {
        rec->lodBegin = ParseByte(p[0]);
        rec->lodEnd = ParseByte(p[1]);
        lodCount = (int)rec->lodEnd - (int)rec->lodBegin + 1;
    } else {
        p = args->OptionArguments("lod", 1);
        if (p) {
            u8 b = ParseByte(p[0]);
            rec->lodBegin = b;
            rec->lodEnd = b + 1;
            lodCount = 2;
        } else {
            rec->lodBegin = 1;
            rec->lodEnd = 0xff;
            lodCount = 1;
        }
    }

    FVec emit = { 0, 0, 0 };
    FVec size = { 0, 0, 0 };
    FVec alpha = { 0, 0, 0 };
    int nLods = 0;
    int n;
    int* arr;

    arr = args->OptionArguments("emitScale", &n, 1, 0x7fffffff);
    if (arr) {
        nLods = imax(nLods, n);
        for (int i = 0; i < n; ++i) {
            float v = ParseFloat(arr[i]);
            emit.push_back(v);
        }
    }
    arr = args->OptionArguments("sizeScale", &n, 1, 0x7fffffff);
    if (arr) {
        nLods = imax(nLods, n);
        for (int i = 0; i < n; ++i) {
            float v = ParseFloat(arr[i]);
            size.push_back(v);
        }
    }
    arr = args->OptionArguments("alphaScale", &n, 1, 0x7fffffff);
    if (arr) {
        nLods = imax(nLods, n);
        for (int i = 0; i < n; ++i) {
            float v = ParseFloat(arr[i]);
            alpha.push_back(v);
        }
    }

    if (nLods != 0) {
        if (nLods != 1) nLods = lodCount;
        rec->lod.resize(nLods);
        int nE = (int)(emit.e - emit.b);
        int nS = (int)(size.e - size.b);
        int nA = (int)(alpha.e - alpha.b);
        float step = 0.0f;
        if (nLods > 1) step = 1.0f / (float)(nLods - 1);
        for (int i = 0; i < nLods; ++i) {
            float v;
            if (nE == 0) v = 1.0f;
            else if (nE == 1) v = emit.b[0];
            else if (nE == 2) v = (emit.b[1] - emit.b[0]) * (float)i * step + emit.b[0];
            else v = emit.b[i];
            rec->lod.b[i].emit = v;
            if (nS == 0) v = 1.0f;
            else if (nS == 1) v = size.b[0];
            else if (nS == 2) v = (size.b[1] - size.b[0]) * (float)i * step + size.b[0];
            else v = size.b[i];
            rec->lod.b[i].size = v;
            if (nA == 0) v = 1.0f;
            else if (nA == 1) v = alpha.b[0];
            else if (nA == 2) v = (alpha.b[1] - alpha.b[0]) * (float)i * step + alpha.b[0];
            else v = alpha.b[i];
            rec->lod.b[i].alpha = v;
        }
    }

    p = args->OptionArguments("prob", 1);
    if (p) {
        float f = ParseFloat(p[0]) * 65535.0f;
        rec->chance = (u16)_mm_cvtss_si32(_mm_set_ss(f));
    }
    p = args->OptionArguments("timeScale", 1);
    if (p) rec->timeScale = ParseFloat(p[0]);

    if (args->HasFlag("ignoreLength")) rec->flags |= 1;
    if (args->HasFlag("respectLength")) rec->flags &= ~1u;
    if (args->HasFlag("ignoreParams")) rec->flags |= 0x20;
    if (args->HasFlag("rigid")) rec->flags |= 0x40;

    p = args->OptionArguments("flag", 2);
    while (p) {
        int bit = ParseInt(p[0]);
        bool on = ParseBool(p[1]);
        u32 mask = 1u << bit;
        rec->appFlagsMask |= mask;
        if (on) rec->appFlags |= mask;
        p = args->OptionArguments("flag", 2);
    }
}

// @ 0x00a6f930
void** HashTable::FindOrInsert(const EString_s00a6_f110__g7& key)
{
    iterator it = find(key);
    if (it.mpNode != end().mpNode)
        return (void**)((char*)it.mpNode + 0x10);

    HTInsertOut out;
    void* def = 0;
    HTPair pair(key, def);
    insert_node(&out, (const EString_s00a6_f110__g7*)&pair, 0);
    return (void**)((char*)out.mpNode + 0x10);
}

// @ 0x00a6f9c0
void DescInstaller::InstallA(const char* name, int index, int arg)
{
    mName.assign(name, name + strlen(name));
    MakeCaseInsensitive(&mName);

    HashTable* table = &mTablesA[index];
    HashTable::iterator it = table->find(mName);
    if (it.mpNode == table->mpBucketArray[table->mnBucketCount]) {
        void* value = mFactory->CreateDescription(index, arg);
        *table->FindOrInsert(mName) = value;
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

// @ 0x00a6fc30
void cEffectsParser_s00a6_f110__g7::AddDescription(cArguments* args, const char* name, int type, bool flag)
{    DescRec_s00a6_f110__g7 rec;
    rec.field80 = MapFindB(name, type);
    if (rec.field80 < 0)
        return;

    rec.type = type;
    rec.field78 = mField390;

    if (mFlag39c) rec.flags |= 2; else rec.flags &= ~2u;
    if (mFlag39d) rec.flags |= 8; else rec.flags &= ~8u;
    if (flag)     rec.flags |= 1; else rec.flags &= ~1u;

    ParseDescRecOptions(args, &rec);
    mDescs.push_back(rec);
    mFlags |= rec.appFlagsMask;
}

// @ 0x00a6fd40
void cEffectsParser_s00a6_f110__g7::AddAnonDescription(cArguments* args, int a, int b, bool flag)
{
    DescRec_s00a6_f110__g7 rec;
    int value = PV2<int>(mFactory, 0x1c, a, b);
    rec.field80 = value;
    rec.type = a;
    rec.field78 = mField390;
    if (flag) rec.flags |= 1; else rec.flags &= ~1u;

    ParseDescRecOptions(args, &rec);
    mDescs.push_back(rec);
    mFlags |= rec.appFlagsMask;
}
