// Slice s00898390: lookup of a float pair from a record table, indexed through two vectors.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:IA32 /fp:fast
#include "types.h"

struct Rec { float f[8]; };

struct IntVec {
    char* begin;
    char* end;
    int size() const { return (end - begin) >> 2; }
    int& operator[](int i) { return ((int*)begin)[i]; }
};
struct ShortVec {
    char* begin;
    char* end;
    int size() const { return (end - begin) >> 1; }
};

struct S898390 {
    char     pad_000[0x444];
    ShortVec mVec444;              // +0x444
    char     pad_44c[0x46c - 0x44c];
    Rec*     mp46C;                // +0x46c
    char     pad_470[0x480 - 0x470];
    IntVec   mVec480;              // +0x480

    float get(int idx);
};

// @ 0x00898390
float S898390::get(int idx)
{
    if (idx != 0) {
        int v;
        if ((unsigned)idx < (unsigned)mVec480.size())
            v = mVec480[idx];
        else
            v = mVec444.size();
        if ((unsigned)v > 0)
            v--;
        Rec* p = mp46C;
        return p[v].f[3] + p[v].f[1];
    }
    return 0.0f;
}
