// eastl::vector<SP::cTextureChart, ...> helpers (retail offsets from disasm).
#include "types.h"

extern "C" void* __cdecl F_f473a0(uint32_t size, const char* name, int a, int b,
                                  const char* file, int line);   // 0x00f473a0 EASTL allocate

struct Vec8 { float x, y; };
struct VecAny {
    int* begin; int* end; int* cap;
    void Append(void* pos, void* val);   // 0x00722410 (thiscall, ret 8)
    __declspec(noinline) void Assign(int n, int value, int dummy);
    void Push8(Vec8* val);
    void* Construct(int n, int val);     // 0x00722ca0
    void Insert18(void* pos, int n, const void* val);   // 0x00722580
    void Insert28(void* pos, int n, const void* val);   // 0x00722770
};
typedef VecAny VecAppend8;

extern "C" void* __stdcall AllocConstruct38(int n, const void* a, const void* b); // 00722990
extern "C" void  __cdecl F_f337a0(void* out, const void* a, const void* b, void* dst, int n); // 0x00f337a0
extern "C" void* __cdecl F_4763a0(void* dst, void* src, void* limit);   // 0x004763a0 EASTL copy/move range
extern "C" void  __cdecl F_f47380(void* p);                              // 0x00f47380 EASTL deallocate

// EASTL vector-insert internals used by VecInsert18 / VecInsert28
extern "C" void* __cdecl F_720d70(void* dst, void* src, int a, int b, void* c); // 0x00720d70 move-range
extern "C" void* __cdecl F_720d10(void* a, int n, void* dst, void* src);        // 0x00720d10
extern "C" void* __cdecl F_720c90(void* a, void* b, void* c, void* d, void* e); // 0x00720c90
extern "C" void* __cdecl F_720ea0(void* a, void* b, void* c);                   // 0x00720ea0
extern "C" void* __cdecl F_720200(void* dst, void* src, void* a);               // 0x00720200
extern "C" void* __cdecl F_7144b0(void* a, void* b, void* c);                   // 0x007144b0 fill
extern "C" void* __cdecl F_714910(void* a, void* b, void* c, void* d, void* e); // 0x00714910
extern "C" void* __cdecl F_cc8b50(void* a, void* b, void* c);                   // 0x00cc8b50 memmove
extern "C" void* __cdecl F_fb3210(void* a, void* b, void* c);                   // 0x00fb3210
extern "C" void* __cdecl F_952790(void* a, void* b, void* c);                   // 0x00952790

// chart record: 0x50-byte prefix followed by an eastl::vector<int> at +0x50
struct ChartRec {
    char m[0x50];
    int* vecBegin; int* vecEnd; int* vecCap;
    void* CopyFrom(const void* src);        // 0x007229f0
    void  SwapVecIfOwned(ChartRec* b);      // 0x00722ba0
};
// helper object used by FindOrInsertF / BuildTextureChart (3-dword vector at +4/+8)
// (FMap is defined next to its member functions below.)

// @ 0x00722410  (vector<Vec8>::insert(end, value); thiscall, ret 8)
void VecAny::Append(void* posV, void* valV)
{
    Vec8* dst = (Vec8*)posV;
    Vec8* val = (Vec8*)valV;
    Vec8* end = (Vec8*)this->end;
    if (end != (Vec8*)this->cap) {
        Vec8* src = val;
        if (src < dst && src < end)
            src += 1;
        if (end) {
            end->x = end[-1].x;
            end->y = end[-1].y;
        }
        int* a = (int*)(end - 1);
        int* c = (int*)end;
        int* d = (int*)dst;
        while (a != d) {
            int t0 = a[-2];
            int t1 = a[-1];
            a -= 2;
            c -= 2;
            c[0] = t0;
            c[1] = t1;
        }
        dst->x = src->x;
        dst->y = src->y;
        this->end = (int*)(end + 1);
        return;
    }

    int count = (int)(end - (Vec8*)this->begin);
    int newCap = count > 0 ? count * 2 : 1;
    Vec8* nb;
    if (newCap)
        nb = (Vec8*)F_f473a0(newCap * 8, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        nb = 0;
    Vec8* ins = (Vec8*)F_4763a0((void*)this->begin, val, nb);
    if (ins) {
        ins->x = dst->x;
        ins->y = dst->y;
    }
    Vec8* tail = (Vec8*)F_4763a0(val, (void*)this->end, ins + 1);
    if (this->begin && (void*)this->begin != (void*)this->cap)
        F_f47380((void*)this->begin);
    this->begin = (int*)nb;
    this->end = (int*)tail;
    this->cap = (int*)(nb + newCap);
}

// @ 0x00722520
void __thiscall VecAny::Assign(int n, int value, int dummy)
{
    int* p;
    if (n != 0)
        p = (int*)F_f473a0(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        p = 0;
    this->begin = p;
    this->cap = p + n;
    this->end = p + n;
    if (n > 0) {
        for (; n != 0; n--)
            *p++ = value;
    }
    (void)dummy;
}

// @ 0x00722580  (vector<T18>::insert(pos, n, val); thiscall, ret 0xc)
void VecAny::Insert18(void* posV, int n, const void* valV)
{
    char* pos  = (char*)posV;
    char* end  = (char*)this->end;
    char* beg  = (char*)this->begin;
    int   cap  = (int)(((char*)this->cap - beg) / 0x18);
    if (n > cap) {
        // grow: newCap = max(count*2, 1); count = (end-beg)/0x18
        int count = (int)((end - beg) / 0x18);
        int newCap = count * 2;
        if (newCap == 0)
            newCap = 1;
        int total = count + n;
        if (newCap <= total)
            newCap = total;
        char* nb = 0;
        if (newCap)
            nb = (char*)F_f473a0(newCap * 0x18, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        char* mid = (char*)F_720200(nb, beg, pos);
        char* nend = (char*)F_714910(mid, (void*)n, (void*)valV, 0, 0);
        char* tail = (char*)F_720200((char*)this->end, end, nend);
        if (this->begin && ((int*)this->begin)[-1] != 0)
            F_f47380(this->begin);
        this->begin = (int*)nb;
        this->end   = (int*)tail;
        this->cap   = (int*)(nb + newCap * 0x18);
        return;
    }
    if (n <= 0)
        return;
    char tmp[0x18];
    void* vv = (void*)valV;
    const char* v = (const char*)valV;
    for (int i = 0; i < 0x18; i += 4)
        *(int*)(tmp + i) = *(const int*)(v + i);
    int remain = (int)(((char*)this->end - pos) / 0x18);
    if (n >= remain) {
        F_720d70(this->end, pos, remain, n, tmp);
        this->end = (int*)((char*)this->end + remain * 0x18);
        F_7144b0(this->end, (void*)n, tmp);
        this->end = (int*)((char*)this->end + (n - remain) * 0x18);
    } else {
        F_720d10(tmp, n, pos, vv);
        this->end = (int*)((char*)this->end + n * 0x18);
        F_720c90(this->end, pos, (void*)n, vv, 0);
        this->end = (int*)((char*)this->end + n * 0x18);
        F_952790((void*)n, vv, 0);
    }
}

// @ 0x00722770  (vector<T28>::insert(pos, n, val); thiscall, ret 0xc)
void VecAny::Insert28(void* posV, int n, const void* valV)
{
    char* pos  = (char*)posV;
    char* end  = (char*)this->end;
    char* beg  = (char*)this->begin;
    int   cap  = (int)(((char*)this->cap - beg) / 0x28);
    if (n > cap) {
        int count = (int)((end - beg) / 0x28);
        int newCap = count * 2;
        if (newCap == 0)
            newCap = 1;
        int total = count + n;
        if (newCap <= total)
            newCap = total;
        char* nb = 0;
        if (newCap)
            nb = (char*)F_f473a0(newCap * 0x28, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        char* mid = (char*)F_720ea0(nb, beg, pos);
        char* nend = (char*)F_720d10(mid, n, (void*)valV, 0);
        char* tail = (char*)F_720ea0((char*)this->end, end, nend);
        if (this->begin && ((int*)this->begin)[-1] != 0)
            F_f47380(this->begin);
        this->begin = (int*)nb;
        this->end   = (int*)tail;
        this->cap   = (int*)(nb + newCap * 0x28);
        return;
    }
    if (n <= 0)
        return;
    char tmp[0x28];
    void* vv = (void*)valV;
    const char* v = (const char*)valV;
    for (int i = 0; i < 0x28; i += 4)
        *(int*)(tmp + i) = *(const int*)(v + i);
    int remain = (int)(((char*)this->end - pos) / 0x28);
    if (n >= remain) {
        F_720c90(this->end, pos, (void*)remain, tmp, 0);
        this->end = (int*)((char*)this->end + remain * 0x28);
        F_fb3210((void*)n, tmp, (void*)n);
        F_720c90(this->end, (void*)n, vv, tmp, 0);
        this->end = (int*)((char*)this->end + n * 0x28);
        F_952790((void*)n, vv, 0);
    } else {
        F_720d10(tmp, n, pos, vv);
        this->end = (int*)((char*)this->end + n * 0x28);
        F_720c90(this->end, pos, (void*)n, vv, 0);
        this->end = (int*)((char*)this->end + n * 0x28);
        F_952790((void*)n, vv, 0);
    }
}

// @ 0x00722990  (allocate n*0x38 then default-construct the range; cdecl, ret 0xc)
void* __stdcall AllocConstruct38(int n, const void* a, const void* b)
{
    void* p;
    if (n != 0)
        p = F_f473a0(n * 0x38, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        p = 0;
    int tmp = 0;
    F_f337a0(&tmp, a, b, p, n);
    return p;
}

// @ 0x007229f0  (copy a chart record: 0x50-byte prefix + inner vector copy-ctor; thiscall, ret 4)
struct IVec { int* b; int* e; int* c; void Fn473b00(const IVec* src); }; // 0x00473b00 vector copy-ctor (thiscall)

void* ChartRec::CopyFrom(const void* src)
{
    const unsigned char* s = (const unsigned char*)src;
    unsigned char* d = (unsigned char*)this;
    *(int*)(d + 0x00) = *(const int*)(s + 0x00);
    *(int*)(d + 0x04) = *(const int*)(s + 0x04);
    *(int*)(d + 0x08) = *(const int*)(s + 0x08);
    *(int*)(d + 0x0c) = *(const int*)(s + 0x0c);
    *(int*)(d + 0x10) = *(const int*)(s + 0x10);
    *(int*)(d + 0x14) = *(const int*)(s + 0x14);
    *(int*)(d + 0x18) = *(const int*)(s + 0x18);
    *(float*)(d + 0x1c) = *(const float*)(s + 0x1c);
    *(float*)(d + 0x20) = *(const float*)(s + 0x20);
    *(float*)(d + 0x24) = *(const float*)(s + 0x24);
    *(int*)(d + 0x28) = *(const int*)(s + 0x28);
    *(int*)(d + 0x2c) = *(const int*)(s + 0x2c);
    *(int*)(d + 0x30) = *(const int*)(s + 0x30);
    *(int*)(d + 0x34) = *(const int*)(s + 0x34);
    *(int*)(d + 0x38) = *(const int*)(s + 0x38);
    *(int*)(d + 0x3c) = *(const int*)(s + 0x3c);
    *(int*)(d + 0x40) = *(const int*)(s + 0x40);
    *(int*)(d + 0x44) = *(const int*)(s + 0x44);
    *(int*)(d + 0x48) = *(const int*)(s + 0x48);
    *(int*)(d + 0x4c) = *(const int*)(s + 0x4c);
    ((IVec*)(d + 0x50))->Fn473b00((const IVec*)(s + 0x50));
    return this;
}

// @ 0x00722b20  (map×::find-or-insert; thiscall, ret 4)
struct FMap {
    int   field0;
    void* field4;
    int   field8;
    void  Find0(int* out, const void* key);   // 0x007219f0 (thiscall)
    void  Insert0(void* val, int* out);       // 0x00721a80 (thiscall)
    int   FindOrInsertF(float* key);          // 0x00722b20
};

int FMap::FindOrInsertF(float* key)
{
    int slot[1];
    this->Find0(slot, key);
    if (slot[0] == *(int*)((char*)this->field4 + this->field8 * 4)) {
        struct { float x; int p0; float y; int p1; float z; int p2; } val;
        val.x = key[0]; val.p0 = 0;
        val.y = key[1]; val.p1 = 0;
        val.z = key[2]; val.p2 = 0;
        this->Insert0(&val, slot);
    }
    return slot[0] + 0xc;
}

// @ 0x00722ba0  (swap two vectors; if either is not heap-owned, copy via +0x50 helper)
struct IVec2 { int* b; int* e; int* c; void Fn473a60(const IVec2* src); }; // 0x00473a60 copy-ctor helper (thiscall)

void ChartRec::SwapVecIfOwned(ChartRec* b)
{
    int* ab = this->vecBegin;
    if (!(ab && ab[-1] != 0)) {
        int* bb = b->vecBegin;
        if (!(bb && bb[-1] != 0)) {
            // neither is heap-owned: copy both through a temporary
            ChartRec tmp;
            ((IVec2*)&tmp)->Fn473a60((const IVec2*)this);
            ((IVec*)this)->Fn473b00((const IVec*)b);
            ((IVec*)b)->Fn473b00((const IVec*)&tmp);
            if (tmp.vecBegin) {
                if (tmp.vecBegin[-1] != 0)
                    F_f47380(tmp.vecBegin);
            }
            return;
        }
    }
    int* t0 = this->vecBegin; int* t1 = this->vecEnd; int* t2 = this->vecCap;
    this->vecBegin = b->vecBegin; this->vecEnd = b->vecEnd; this->vecCap = b->vecCap;
    b->vecBegin = t0; b->vecEnd = t1; b->vecCap = t2;
}

// @ 0x00722c60
void __thiscall VecAny::Push8(Vec8* val)
{
    Vec8* e = (Vec8*)this->end;
    if (e < (Vec8*)this->cap) {
        this->end = (int*)(e + 1);
        if (e != 0) {
            e->x = val->x;
            e->y = val->y;
            return;
        }
    } else {
        ((VecAppend8*)this)->Append(e, val);
    }
}

// @ 0x00722ca0  (construct a vector<int> in-place and Assign(n,val); thiscall, ret 8)
void* VecAny::Construct(int n, int val)
{
    this->begin = 0;
    this->end = 0;
    this->cap = 0;
    this->Assign(n, val, val);
    return this;
}

// @ 0x00722d00  (build a cTextureChart from a resource; thiscall-ish free fn, cdecl, 1 arg)
extern "C" void* __cdecl F_7366e0(int a);                                    // 0x007366e0
extern "C" int   __cdecl F_71ddc0(int a, int b, int c, int d, int e);        // 0x0071ddc0
extern "C" void* __cdecl F_6c3510(void* p);                                  // 0x006c3510 ctor
extern "C" void* __cdecl F_7219f0v(void* map, int* out, const void* key);    // 0x007219f0
extern "C" void* __cdecl F_7217c0(void* obj, void* out);                     // 0x007217c0
extern "C" int   __cdecl F_71e040(void* a, int b, int c);                    // 0x0071e040
extern "C" void* __cdecl F_7201b0(void* a, void* b);                         // 0x007201b0
extern "C" void* __cdecl F_71f040(void* a, int b, int c, void* d);           // 0x0071f040
extern "C" void* __cdecl F_7611f0(void* a, void* b, void* c);                // 0x007611f0
extern "C" void* __cdecl F_4b5ad0(void* a, void* b);                         // 0x004b5ad0

void __cdecl BuildTextureChart(int res)
{
    F_7366e0(res);
    int idx = F_71ddc0(res, 1, 0, 3, 0xe);
    if (idx < 0)
        return;

    char* p = (char*)*(void**)(res + 8) + idx * 0x20;
    if (*(int*)(p + 0xc) != 0)
        return;

    // local scratch (the original builds a 0x24 temporary + an int array)
    int  arr[1] = { 0 };            // esp+0x54 marker array (allocated below)
    float f60 = *(float*)0x1485720;
    float f64 = *(float*)0x1470f1c;
    int   n   = *(int*)(p + 0x10);
    int   base[1];
    (void)f60; (void)f64;

    void* vec = 0;
    if (*(int*)(p + 0x10) != 0) {
        vec = F_f473a0(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    int* ivec = (int*)vec;
    for (int i = 0; i < n; i++)
        ivec[i] = 0;
    (void)base; (void)arr;

    void* obj = F_f473a0(0x24, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    void* built = obj ? F_6c3510(obj) : 0;

    for (int k = 0; k < *(int*)(p + 0x10); k++) {
        unsigned short stride = *(unsigned short*)(p + 0x1a);
        float* src = (float*)(*(int*)(p + 0x14) + k * stride);
        int key[3];
        key[0] = *(int*)(src + 0);
        key[1] = *(int*)(src + 1);
        key[2] = *(int*)(src + 2);
        int slot[1];
        F_7219f0v(built, slot, 0);
        (void)slot; (void)key;
    }

    F_7217c0(built, 0);
    if (ivec && ivec[-1] != 0)
        F_f47380(ivec);
}
