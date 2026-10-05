// s00466e20 -- /Od /Ob1 region.

extern unsigned int maskTable[];
extern char tableA[];
extern char tableB[];

// @ 0x00467980
struct ArrF {
    int pad0;
    char* data;
    unsigned short maskIdx;
    unsigned short stride;
    unsigned int get(int i);
};

unsigned int ArrF::get(int i)
{
    return *(unsigned int*)(data + stride * i) & maskTable[maskIdx];
}

// @ 0x004679b0
struct ArrG {
    int idx;
    int pad1;
    int b;
    int a;
    int f();
};

int ArrG::f()
{
    if (idx <= 0 || idx >= 10)
        return 0;
    if (idx == 9)
        return 1;
    int v9 = a - b;
    int t10 = tableA[idx];
    int cap = tableB[idx];
    return (v9 + t10) / cap;
}

// @ 0x00466e20
void F_00466e20() {}
