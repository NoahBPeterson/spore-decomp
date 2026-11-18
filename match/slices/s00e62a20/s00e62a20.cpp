// @ 0x00e62a20 : copy constructor of the 0x1290-byte cell record block
// (a SmallRec table of 0x40 entries followed by the tail cell state).
// The element copy constructor is SmallRec::SmallRec(const SmallRec&) 0x00e617e0,
// and the array copy goes through the CRT helper __ehvec_copy_construct 0x00406540.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast
#include "game/types.h"

extern "C" void __stdcall ehvec_ctor(void* dst, void* src, unsigned size,
                                     int count, void* ctor); // 0x00406540

struct Matrix33 {
    float m[3][3];
};

// 0x48-byte element of the record table (copy constructor at 0x00e617e0).
struct SmallRec {
    char     f00;   // +0x00
    int      f04;   // +0x04
    float    f08;   // +0x08
    float    f0c;   // +0x0c
    float    f10;   // +0x10
    Matrix33 rot;   // +0x14
    float    f38;   // +0x38
    float    f3c;   // +0x3c
    float    f40;   // +0x40
    float    f44;   // +0x44
    // No user-declared constructors: the implicit default constructor must stay
    // trivial so that the member array below needs no construction loop; the
    // elements are copy-constructed by the retail ctor 0x00e617e0 through
    // ehvec_ctor, exactly as the original copy constructor does.
};

// 52 bytes copied as one trivially-copyable block at +0x1204.
struct RecordTail {
    int w[13];
};

struct cCellRecordBlock {
    int          m0;          // +0x0000
    SmallRec     mRecs[0x40]; // +0x0004 .. +0x1204
    RecordTail   m1204;       // +0x1204
    float        m1238;       // +0x1238
    float        m123c;       // +0x123c
    float        m1240;       // +0x1240
    float        m1244;       // +0x1244
    unsigned char m1248;      // +0x1248
    float        m124c;       // +0x124c
    unsigned char m1250;      // +0x1250
    unsigned char m1251;      // +0x1251
    int          m1254;       // +0x1254
    float        m1258;       // +0x1258
    float        m125c;       // +0x125c
    float        m1260;       // +0x1260
    float        m1264;       // +0x1264
    float        m1268;       // +0x1268
    int          m126c;       // +0x126c
    float        m1270;       // +0x1270
    int          m1274;       // +0x1274
    int          m1278;       // +0x1278
    int          m127c;       // +0x127c
    int          m1280;       // +0x1280
    int          m1284;       // +0x1284
    int          m1288;       // +0x1288
    int          m128c;       // +0x128c
    cCellRecordBlock(const cCellRecordBlock& other);
};

cCellRecordBlock::cCellRecordBlock(const cCellRecordBlock& other)
{
    m0 = other.m0;
    ehvec_ctor((void*)&mRecs[0], (void*)&other.mRecs[0], 0x48, 0x40,
               (void*)0xe617e0); // SmallRec::SmallRec(const SmallRec&)
    m1204 = other.m1204;
    m1238 = other.m1238;
    m123c = other.m123c;
    m1240 = other.m1240;
    m1244 = other.m1244;
    m1248 = other.m1248;
    m124c = other.m124c;
    m1250 = other.m1250;
    m1251 = other.m1251;
    m1254 = other.m1254;
    m1258 = other.m1258;
    m125c = other.m125c;
    m1260 = other.m1260;
    m1264 = other.m1264;
    m1268 = other.m1268;
    m126c = other.m126c;
    m1270 = other.m1270;
    m1274 = other.m1274;
    m1278 = other.m1278;
    m127c = other.m127c;
    m1280 = other.m1280;
    m1284 = other.m1284;
    m1288 = other.m1288;
    m128c = other.m128c;
}
