// w1g1 slice s00509f50 -- table-index helpers and small vector ops.
//
// Flags: /Od /Ob1 /MD /Gy /TP (x87 fabs; /arch:SSE for movss copies).

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

float fabsf(float);
struct V3 { float x, y, z; };

// @ 0x0050a880  (component-wise abs)
V3* __cdecl AbsV3(V3* out, const V3* in)
{
    out->x = fabsf(in->x);
    out->y = fabsf(in->y);
    out->z = fabsf(in->z);
    return out;
}

// ---------------------------------------------------------------------------
int TableInsert(int self, int idx, uint32_t* key, int slot);   // 0x00509c80
extern const signed char gCode3[3];                            // 0x013f18d0
extern const signed char gOff3[3];                             // 0x013f18d8

struct SlotTable {
    char pad[0x200];

    // @ 0x00509f50
    void InsertEdge(int a, int b, uint32_t* key);

    // @ 0x0050a920
    uint8_t Adjacent(int a, int b, int c, int d);

    // @ 0x0050a730
    int FaceHelper(int face);

    // @ 0x0050a9e0
    void* CopyRecord(void** src);
};

void SlotTable::InsertEdge(int a, int b, uint32_t* key)
{
    uint32_t idx = (uint32_t)(a * 3 + b);
    signed char c = gCode3[idx % 3];
    int i = (int)(signed char)gOff3[idx % 3] + (int)idx;
    uint32_t* e = (uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + i * 4) * 8);
    if (*e == *key)
        *(uint32_t*)(*(int*)((char*)this + 0x80) + i * 4) = e[1];
    else
        TableInsert((int)this, i, key, -1);
    *(uint32_t*)(*(int*)((char*)this + 0x80) + idx * 4) =
        *(uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + idx * 4) * 8 + 4);
    *(uint32_t*)(*(int*)((char*)this + 0x80) + ((int)c + (int)idx) * 4) =
        *(uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + ((int)c + (int)idx) * 4) * 8 + 4);
    *(uint32_t*)(*(int*)((char*)this + 0x110) + a * 4) = ~*key;
}

uint8_t SlotTable::Adjacent(int a, int b, int c, int d)
{
    int i = d * 3 + (c + 1) % 3;
    int* t = *(int**)((char*)this + 0x6c);
    uint8_t result;
    if (t[(a * 3 + b)] == t[i]) {
        int j = t[(a * 3 + (b + 1) % 3)];
        if (j == t[(d * 3 + c)])
            result = 1;
        else
            result = 0;
    } else {
        result = 0;
    }
    return result;
}

int SlotTable::FaceHelper(int face)
{
    int base = *(int*)((char*)this + 8);
    int tab = *(int*)((char*)this + 0x58);
    return *(int*)(tab + (base + face * 0xc));
}

void CopyRangeA(const void* src);   // vector<float>::operator=
void CopyRangeB(const void* src);   // 0x0050db60
void CopyRangeC(const void* src);   // 0x0050dea0

void* SlotTable::CopyRecord(void** src)
{
    void** dst = (void**)this;
    dst[0] = src[0];
    dst[1] = src[1];
    CopyRangeA(src + 2);
    CopyRangeA(src + 7);
    CopyRangeA(src + 0xc);
    CopyRangeB(src + 0x11);
    dst[0x16] = src[0x16];
    dst[0x17] = src[0x17];
    dst[0x18] = src[0x18];
    dst[0x19] = src[0x19];
    dst[0x1a] = src[0x1a];
    CopyRangeA(src + 0x1b);
    CopyRangeC(src + 0x20);
    return this;
}

// @ 0x0050a0a0  (PARTIAL skeleton: 1.7 KB face-table builder)
void __fastcall BuildFaces(int self) { (void)self; }
