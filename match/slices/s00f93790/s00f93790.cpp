// Slice s00f93790 -- 0x0f9xxxx region (SP::cTerrainResourceManager TU, mixed with
// the EASTL fixed_vector / SpVector COMDATs it instantiates).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP /arch:SSE
// /fp:fast (default /GS on).

struct Vector3 {
    float x, y, z;
};

// ?erase@?$SpVector@UVector3@@@@QAEPAUVector3@@PAU2@0@Z (0x50f740): the terrain
// code's own SpVector<T> (begin/end/capacity + two bookkeeping pointers).
template <class T>
class SpVector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    T* mpPool;
    T* mpStorage;
    T* erase(T* first, T* last);
};

// Object holding four SpVector<Vector3> members at +0x10 (stride 0x14) plus the
// "dirty" flag at +0x0c that FUN_00f93c00 clears.
class Self {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();

private:
    char pad4[8];

public:
    char mFlag;
    SpVector<Vector3> mVec[4];
};

void* __cdecl EAAllocate(unsigned int size, const char* pFile, int a, int b, int c, int d);
extern int g_vtblGmeRefCount;
extern int g_rdata149015c;
extern int g_rdata1490158;

// The retail initialiser keeps two writes to the same field (+0x04) apart, which
// the /O2 store eliminator would otherwise collapse, so the constructor region is
// fenced with the no-code barrier intrinsic.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// @ 0x00f939b0 -- FUN_00f939b0
// Allocates the 0x68-byte terrain resource manager, then initialises it: the
// GmeRefCount base vtable and the two data words at +0/+4, the flag bytes at
// +0x0c and +0x60, and the first three pointers of each of the four
// SpVector<Vector3> members at +0x10 (stride 0x14).
void* __fastcall FUN_00f939b0() {
    int zero = 0;
    int* p = (int*)EAAllocate(0x68, "Terrain/ResourceManager/cTerrainResourceManager", zero, zero, zero, zero);
    if (p != 0) {
        p[2] = zero;
        p[1] = (int)&g_vtblGmeRefCount;
        _ReadWriteBarrier();
        *((char*)p + 0xc) = (char)zero;
        p[0] = (int)&g_rdata149015c;
        p[1] = (int)&g_rdata1490158;
        _ReadWriteBarrier();
        p[4] = zero;
        p[5] = zero;
        p[6] = zero;
        p[9] = zero;
        p[10] = zero;
        p[0xb] = zero;
        p[0xe] = zero;
        p[0xf] = zero;
        p[0x10] = zero;
        p[0x13] = zero;
        p[0x14] = zero;
        p[0x15] = zero;
        *((char*)p + 0x60) = (char)zero;
        p[0x19] = zero;
        return p;
    }
    return 0;
}

// @ 0x00f93c00 -- FUN_00f93c00 (__fastcall, this in ecx)
// If the dirty flag at +0x0c is set, clears it, drains each of the four
// SpVector<Vector3> members at +0x10 (stride 0x14) and notifies through the
// tenth virtual slot (+0x24).
bool __fastcall FUN_00f93c00(Self* self) {
    if (self->mFlag != 0) {
        self->mFlag = 0;
        SpVector<Vector3>* p = &self->mVec[0];
        int n = 4;
        do {
            p->erase(p->mpBegin, p->mpEnd);
            p = (SpVector<Vector3>*)((char*)p + 0x14);
            --n;
        } while (n != 0);
        self->v9();
    }
    return true;
}

// ===========================================================================
// Completion-pass reconstructions of the seven remaining functions of this
// slice.  These are object-heavy (opaque vtables, EASTL containers): the
// source drives the vtables through typed function pointers and reproduces
// the Decompiler-level behaviour.  See nonmatching.txt for per-VA notes.
// ===========================================================================

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned short wchar16;

struct EVariant { u32 w0, w1, w2, w3; u16 flags; u16 typeId; };
struct Key { u32 mInstance, mType, mGroup; };

typedef int   (__thiscall *FM0)(void*);
typedef int   (__thiscall *FM1)(void*, int);
typedef int   (__thiscall *FM2)(void*, int, int);
typedef int   (__thiscall *FM3)(void*, int, int, int);
typedef int   (__thiscall *FM4)(void*, int, int, int, int);
typedef int   (__thiscall *FM5)(void*, int, int, int, int, int);
typedef void* (__thiscall *FP0)(void*);
typedef void* (__thiscall *FP1)(void*, int);
typedef void* (__thiscall *FP2)(void*, int, int);

extern "C" void* FUN_0067dcd0();                        // 0x0067dcd0 ResourceMan::GetManager
extern "C" void* FUN_0067de30();                        // 0x0067de30 SP::PropertyManager
extern "C" void* FUN_006b1f90(u32);                     // 0x006b1f90 SP_GetSaveArea
extern "C" void  FUN_00427fd0(EVariant*, void*);        // 0x00427fd0 Variant_SetInt
extern "C" void  FUN_00422f40(EVariant*, void*);        // 0x00422f40 Variant_SetVec12
extern "C" void  FUN_0093db80(EVariant*, int);          // 0x0093db80 Variant::Destruct
extern "C" int   FUN_0093dd80(EVariant*, u16, u16, const void*, u32, u32); // 0x0093dd80 Variant::Construct
extern "C" void  FUN_00f47380(void*);                   // 0x00f47380 operator delete
extern "C" void* FUN_00f473a0(u32, const char*, int, int, int, int); // 0x00f473a0 EAAllocate
extern "C" void* FUN_00926020(int, int, int, int, int, int); // 0x00926020 ZoneObject_new
extern "C" void* FUN_008d9f80(void*, int, int);         // 0x008d9f80 DatabasePackedFile ctor
extern "C" int   FUN_00931fa0(const wchar16*);          // 0x00931fa0 EA::IO::File::Exists
extern "C" void* FUN_0041e050(void*, const wchar16*, ...); // 0x0041e050 WStr_Format
extern "C" int   FUN_006a0ae0(void*, int, void*, void*); // 0x006a0ae0 eastl vector reserve
extern "C" int   FUN_006a0990(void*, int, void*, void*); // 0x006a0990 eastl vector probe
extern "C" void  FUN_00bed3e0(void*, void*);             // 0x00bed3e0 property refresh
extern "C" u32 __fastcall FUN_00a68fb0(void*, int, u32);// 0x00a68fb0 RandomUint32Uniform
extern "C" void* FUN_00425d30(void*, void*);             // 0x00425d30 Vec12_DoInsertValue
extern "C" void* FUN_004548d0(void*, int);               // 0x004548d0 vector set-size
extern "C" int   FUN_006a1110(void*, int, void*);        // 0x006a1110 GetPropertyAsVector3
extern "C" int   FUN_00fc2080(float, float);             // 0x00fc2080 TerraDistClass
extern "C" void* FUN_004e3e10(void*, void*);             // 0x004e3e10 SpVector<Key>::DoInsertKey
extern "C" void  FUN_0093a780(void*, void*, int, int);   // 0x0093a780 EA::IO::ReadInt32
extern "C" void  FUN_0093aa70(void*, const void*, int, int); // 0x0093aa70 EA::IO::WriteUint32
extern "C" int   FUN_006b4b60(void*, void*);             // 0x006b4b60 async-save
extern "C" void* FUN_006a1b90(void*, const char*);       // 0x006a1b90 cPropertyList ctor
extern "C" void  FUN_006a1710(void*, void*);             // 0x006a1710 cPropertyList::SetParent
extern "C" int   FUN_006a25a0(void*, u32);               // 0x006a25a0 cDirectPropertyList::GetDescription
extern "C" void  FUN_007dade0(u32);                      // 0x007dade0 SP::SetEffectSeed
extern "C" void  FUN_00512050(void*, void*, void*, void*); // 0x00512050 range construct
extern "C" void* FUN_00a11310(void*, void*, void*);      // 0x00a11310 copy to new storage
extern "C" void* FUN_00abced0(void*, void*, void*);      // 0x00abced0 copy_backward
extern "C" void* FUN_00b84c80(void*, void*, void*);      // 0x00b84c80 copy
extern "C" void* FUN_0041ea00(void*);                    // 0x0041ea00 Property::GetUInt

extern void* g_015fd918;   // 0x015fd918 SP app-properties cDirectPropertyList*
extern void* gEmptyString16; // 0x01667bac eastl::gEmptyString16

// @ 0x00f93790 -- 'anonymous namespace'::cTerrainCheat::Execute candidate.
// Runs one arg-script "terrain" command: pulls the property list for the
// character key, tags it with four name hashes, assigns the integer variant
// 0x3ad556a and hands the result to the ResourceMan save path.
extern "C" void __stdcall FUN_00f93790(void* ctx)
{
    u32* p = (u32*)ctx;
    void* local = 0;
    void* pm = FUN_0067de30();
    if (local) { void* t = local; local = 0; ((FM0)(*(void***)t)[1])(t); }
    u8 ok = (u8)((FM3)(*(void***)pm)[0x2c / 4])(pm, p[0], p[2], (int)&local);
    if (ok) {
        void* obj = local;
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x3ad5568);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x3ad5569);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x43b29e1);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x43b29e2);
        EVariant v; v.w0 = v.w1 = v.w2 = v.w3 = 0; v.flags = 0; v.typeId = 0;
        int zero = 0;
        FUN_00427fd0(&v, &zero);
        ((FM2)(*(void***)obj)[0x14 / 4])(obj, 0x3ad556a, (int)&v);
        if (v.flags & 4) FUN_0093db80(&v, 0);
        void* mgr = FUN_0067dcd0();
        void* sa = FUN_006b1f90(0x31389b5);
        ((FM3)(*(void***)mgr)[0x20 / 4])(mgr, (int)obj, 0, (int)sa);
    }
    if (local) { void* t = local; local = 0; ((FM0)(*(void***)t)[1])(t); }
}

// @ 0x00f938b0 -- eastl::vector<Key,fixed_vector_allocator<12,16,4,0,1>>::
// DoInsertValue-style helper (the vector arrives in esi in the original).
// Collects the vector's element count through the ResourceMan manager and the
// property manager, then walks the save area.
extern "C" void FUN_00f938b0(void* vec)
{
    void* mgr = FUN_0067dcd0();
    u32 block[4];
    block[0] = 0x1490124; block[1] = 0; block[2] = 0; block[3] = 0;
    ((FM2)(*(void***)mgr)[0x34 / 4])(mgr, (int)&block[1], (int)&block[0]);
    void* pm = FUN_0067de30();
    int count = (int)((u32)(block[0] - (u32)vec) / 0xc);
    ((FM2)(*(void***)pm)[0x3c / 4])(pm, (int)vec, count);
    void* sa = FUN_006b1f90(0x31389b5);
    int n = ((FM2)(*(void***)sa)[0x30 / 4])(sa, (int)&block[0], (int)&block[1]);
    if (n > 0) {
        int base = (int)block[1];
        for (int i = 0; i < n; ++i)
            ((FM1)(*(void***)sa)[0x40 / 4])(sa, base + i);
    }
    if (block[0] && *(u32*)(block[0] - 4)) FUN_00f47380((void*)block[0]);
}

// @ 0x00f93a20 -- eastl::vector<Key,fixed_vector_allocator<12,32,4,0,1>>::
// insert of a [first,last) Key range into *this at position (arg1=position,
// arg2=first, arg3=last; 12-byte elements).
extern "C" void __fastcall FUN_00f93a20(void* self, int, int position, int first, int last, int arg4)
{
    (void)arg4;
    if (first == last) return;
    u32* v = (u32*)self;
    u32 n = (u32)(last - first) / 0xc;
    if (n <= ((v[2] - v[1]) / 0xc)) {
        int mpEnd = (int)v[1];
        u32 nMove = (u32)(mpEnd - position) / 0xc;
        if (n < nMove) {
            int tail = mpEnd - (int)n * 0xc;
            u32 local = 0;
            FUN_00512050(&local, (void*)tail, (void*)mpEnd, (void*)mpEnd);
            v[1] = (u32)mpEnd + n * 0xc;
            FUN_00abced0((void*)position, (void*)tail, (void*)mpEnd);
            FUN_00b84c80((void*)first, (void*)last, (void*)position);
            return;
        }
        // Construct the input tail past the end, slide the old tail right, then
        // drop the input head into the gap.
        int fplus = first + (int)nMove * 0xc;
        u32 outA = 0;
        FUN_00512050(&outA, (void*)fplus, (void*)last, (void*)mpEnd);
        v[1] = (u32)mpEnd + (n - nMove) * 0xc;
        int mpEnd2 = (int)v[1];
        u32 outB = 0;
        FUN_00512050(&outB, (void*)position, (void*)mpEnd, (void*)mpEnd2);
        v[1] = (u32)mpEnd2 + nMove * 0xc;
        FUN_00abced0((void*)first, (void*)fplus, (void*)(position + (int)nMove * 0xc));
        return;
    }
    // Grow: copy [begin,position) to fresh storage, construct the input there,
    // copy [position,end) after it, then swap in the new storage.
    u32 size = (v[1] - v[0]) / 0xc;
    u32 newCap = size * 2;
    if (size == 0) newCap = 1;
    if (newCap <= n + size) newCap = n + size;
    void* buf = 0;
    if (newCap != 0)
        buf = FUN_00f473a0(newCap * 0xc, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
    FUN_00a11310((void*)v[0], (void*)position, buf);
    void* mid = (char*)buf + ((u32)(position - v[0]));
    u32 outC = 0;
    FUN_00512050(&outC, (void*)first, (void*)last, mid);
    void* newEnd = (void*)outC;
    FUN_00a11310((void*)position, (void*)v[1], newEnd);
    void* final = (char*)newEnd + ((u32)(v[1] - position));
    u32 oldb = v[0];
    if (oldb && oldb != v[4]) FUN_00f47380((void*)oldb);
    v[0] = (u32)buf;
    v[1] = (u32)final;
    v[2] = (u32)buf + newCap * 0xc;
}

// @ 0x00f93c40 -- SP::cTerrainResourceManager::LoadPlanetDefinitions.
// Drops the current definition database, then (given a save-area name) mounts
// "<name>%ls.pld" into a fresh EA::ResourceMan::DatabasePackedFile.
extern "C" u8 __fastcall FUN_00f93c40(void* self, int, int param)
{
    void* mgr = FUN_0067dcd0();
    void* db = *(void**)((char*)self + 0x64);
    if (db) {
        ((FM3)(*(void***)mgr)[0x50 / 4])(mgr, 0, (int)db, 0);
        ((FM0)(*(void***)db)[0x1c / 4])(db);
        ((FM0)(*(void***)db)[8 / 4])(db);
        db = *(void**)((char*)self + 0x64);
        if (db) {
            *(void**)((char*)self + 0x64) = 0;
            ((FM0)(*(void***)((char*)db + 4))[4 / 4])((char*)db + 4);
        }
    }
    ((FM0)(*(void***)self)[0x24 / 4])(self);
    if (param == 0) return 1;

    void* str[3];
    str[0] = gEmptyString16; str[1] = gEmptyString16; str[2] = (void*)0x1667bae;
    void* sa = FUN_006b1f90(0x4729a47);
    void* name = (void*)((FP1)(*(void***)sa)[0x28 / 4])(sa, param);
    FUN_0041e050(str, (const wchar16*)0x14901e4, name);   // L"%ls%ls.pld"

    u8 result = 0;
    if (FUN_00931fa0((const wchar16*)str[0])) {
        void* raw = FUN_00926020(0x388, (int)"Terrain/ResourceManager/DatabasePackedFile", 0, 0, 0, 0);
        void* newdb = 0;
        if (raw) newdb = FUN_008d9f80(raw, 0, 0);
        void* old = *(void**)((char*)self + 0x64);
        if (newdb != old) {
            if (newdb) ((FM0)(*(void***)((char*)newdb + 4))[0 / 4])((char*)newdb + 4);
            *(void**)((char*)self + 0x64) = newdb;
            if (old) ((FM0)(*(void***)((char*)old + 4))[4 / 4])((char*)old + 4);
        }
        void* cur = *(void**)((char*)self + 0x64);
        ((FM0)(*(void***)cur)[4 / 4])(cur);
        ((FM1)(*(void***)cur)[0x2c / 4])(cur, (int)str[0]);
        if ((u8)((FM3)(*(void***)cur)[0x18 / 4])(cur, 1, 3, 0)) {
            ((FM3)(*(void***)mgr)[0x50 / 4])(mgr, 1, (int)cur, 0xfffffc18);
            result = 1;
        }
    }
    if ((((u32)((char*)str[2] - (char*)str[0]) & ~1u) > 2) && str[0])
        FUN_00f47380(str[0]);
    return result;
}

// @ 0x00f93dd0 -- SP::cTerrainResourceManager::ApplyScriptSets.
// Seeds the effect RNG, expands a set of script keys into a Key vector via the
// property manager, publishes it as a Variant, then folds in a single extra
// descriptor key.
extern "C" void __fastcall FUN_00f93dd0(void* self, int, u32 seed, void* obj)
{
    FUN_007dade0(seed);

    Key vecBuf[24];
    Key* vbeg = vecBuf;
    Key* vend = vecBuf;
    Key* vcap = vecBuf + 24;
    Key* vpool = vecBuf;
    u32 i;
    for (i = 0x40cf84e; i < 0x40cf858; ++i) {
        u32 a = 0, b = 0;
        if ((u8)FUN_006a0ae0(obj, (int)i, &a, &b)) {
            u32 r = FUN_00a68fb0((void*)0x016778dc, 0, a);
            Key* src = (Key*)b + r;
            if (vend < vcap) {
                if (vend) *vend = *src;
                ++vend;
            } else {
                FUN_00425d30(vend, src);
                ++vend;
            }
            ((FM1)(*(void***)obj)[0x18 / 4])(obj, (int)i);
        }
    }

    if (vbeg != vend) {
        Key extra[24];
        Key* ebeg = extra;
        Key* eend = extra;
        u32 a = 0, b = 0;
        if ((u8)FUN_006a0ae0(obj, 0x3abb0af, &a, &b)) {
            FUN_00bed3e0(&a, &b);
            u32 cnt = a;
            Key* src = (Key*)b;
            for (u32 k = 0; k < cnt; ++k) { *eend++ = *src++; }
        }
        void* selfv = (char*)self + 0x10;
        FUN_00f93a20(selfv, 0, (int)ebeg, (int)eend, 0, 0);
        EVariant v; v.w0 = v.w1 = v.w2 = v.w3 = 0; v.flags = 0; v.typeId = 0;
        FUN_0093dd80(&v, 0x20, 0x98, ebeg, 0xc, (u32)((char*)eend - (char*)ebeg) / 0xc);
        ((FM2)(*(void***)obj)[0x14 / 4])(obj, 0x3abb0af, (int)&v);
        if (v.flags & 4) FUN_0093db80(&v, 0);
        if (ebeg && ebeg != extra + 24) FUN_00f47380(ebeg);
    }

    u32 a = 0, b = 0;
    if ((u8)FUN_006a0990(obj, 0x40d6a39, &a, &b)) {
        u32 r = FUN_00a68fb0((void*)0x016778dc, 0, a);
        Key* src = (Key*)b + r;
        EVariant v;
        v.w0 = src->mInstance; v.w1 = src->mType; v.w2 = src->mGroup; v.w3 = 0;
        v.typeId = 0x31; v.flags = 2;
        ((FM2)(*(void***)obj)[0x14 / 4])(obj, 0x3a23f99, (int)&v);
        if (v.flags & 4) FUN_0093db80(&v, 0);
        ((FM1)(*(void***)obj)[0x18 / 4])(obj, 0x40d6a39);
    }

    if (vbeg && vbeg != vecBuf) FUN_00f47380(vbeg);
}

// @ 0x00f940a0 -- SP::cTerrainResourceManager::Init.
// One-shot initialiser: tries to load the per-level script tables from the
// save area, otherwise scans the property manager for terrain script
// properties and groups them by TerraDistClass bucket.
extern "C" u8 __fastcall FUN_00f940a0(void* self, int)
{
    char* s = (char*)self;
    if (s[0xc]) return 1;
    s[0xc] = 1;
    s[0x60] = 1;

    void* sa = FUN_006b1f90(0x11ac19c);
    u8 fromSave = 1;
    u32 keyBlk[3];
    keyBlk[0] = 0x5528db9; keyBlk[1] = 0x5528d58; keyBlk[2] = 0x40a00200;
    u32 local5c = 0;
    if ((u8)((FM4)(*(void***)sa)[0x34 / 4])(sa, (int)keyBlk, (int)&local5c, 1, 6)) {
        void* stream = (void*)((FP0)(*(void***)self)[0x18 / 4])(self);
        u32 v = 0;
        FUN_0093a780(stream, &v, 1, 0);
        if (((int)v < 0) && ((v & 0x7fffffff) == 2)) {
            fromSave = 0;
            char* p = s + 0x10;
            int n4 = 4;
            do {
                u32 cnt = 0;
                FUN_0093a780(stream, &cnt, 1, 0);
                FUN_004548d0(p, (int)cnt);
                FUN_0093a780(stream, *(void**)p, (int)((cnt * 0xc) >> 2), 0);
                p += 0x14;
            } while (--n4);
        }
        ((FM0)(*(void***)self)[0x24 / 4])(self);
    }

    if (fromSave) {
        void* pm = FUN_0067de30();
        u32 slot = 0;
        u32 v2[3];
        v2[0] = v2[1] = v2[2] = 0;
        u32 k;
        for (k = 0xa3; (int)k <= 0xab; ++k) {
            int key = (int)(((k & 0xff) | 0x418400) << 8);
            ((FM2)(*(void***)pm)[0x48 / 4])(pm, key, (int)v2);
            int count = (int)(v2[1] - v2[0]) >> 2;
            for (int idx = 0; idx < count; ++idx) {
                if (slot) { void* t = (void*)slot; slot = 0; ((FM0)(*(void***)t)[1])(t); }
                u8 ok = (u8)((FM3)(*(void***)pm)[0x2c / 4])(pm, *(int*)(v2[0] + idx * 4), key, (int)&slot);
                if (ok && !((FM1)(*(void***)(void*)slot)[0x1c / 4])((void*)slot, 0x6369b24)) {
                    int pv = 0;
                    if (slot && ((FM2)(*(void***)(void*)slot)[0x24 / 4])((void*)slot, 0xd2f669ec, (int)&pv) &&
                        *(u16*)(pv + 0x12) == 0xa) {
                        void* q = (*(u8*)(pv + 0x10) & 0x30) ? *(void**)pv : (void*)pv;
                        if (*(u32*)q == 0) continue;
                    }
                    u32 v3[3];
                    if (FUN_006a1110((void*)slot, 0x3a23f98, v3)) {
                        int dist = FUN_00fc2080(*(float*)&v3[1], *(float*)&v3[2]);
                        Key nk;
                        nk.mInstance = *(u32*)(v2[0] + idx * 4);
                        nk.mType = 0;
                        nk.mGroup = (u32)key;
                        char* bucket = s + 0x10 + dist * 0x14;
                        Key* end = *(Key**)(bucket + 4);
                        if (end < *(Key**)(bucket + 8)) {
                            *end = nk;
                            *(Key**)(bucket + 4) = end + 1;
                        } else {
                            FUN_004e3e10(bucket, &nk);
                        }
                    }
                }
            }
        }
        if (slot) { void* t = (void*)slot; ((FM0)(*(void***)t)[4 / 4])(t); }
    }

    {
        void* wsa = FUN_006b1f90(0x31389b5);
        int wv[3];
        wv[0] = wv[1] = wv[2] = 0;
        int res = (int)((FM5)(*(void***)self)[0x34 / 4])(self, (int)wv, (int)&wv[1], 2, 6, 1);
        if ((u8)res) {
            void* stream = (void*)((FP0)(*(void***)(void*)wv[1])[0x18 / 4])((void*)wv[1]);
            u32 marker = 0x80000002;
            FUN_0093aa70(stream, &marker, 1, 0);
            char* p = s + 0x10;
            int n4 = 4;
            do {
                u32 cnt = (u32)(*(u32*)(p + 4) - *(u32*)p) / 0xc;
                FUN_0093aa70(stream, &cnt, 1, 0);
                FUN_0093aa70(stream, *(void**)p, (int)(((cnt * 0xc) >> 2)), 0);
                p += 0x14;
            } while (--n4);
            ((FM0)(*(void***)(int)wv[1])[0x24 / 4])((void*)wv[1]);
        }
        if (wv[0] && *(u32*)(wv[0] - 4)) FUN_00f47380((void*)wv[0]);
    }

    ((FM0)(*(void***)self)[0x24 / 4])(self);
    return 1;
}

// @ 0x00f94480 -- SP::cTerrainResourceManager::CreatePlanetDefinitionFromScript.
// Builds a fresh "PlanetDefinition" cPropertyList from a script key (with a
// fallback for the 0xa100 planet group), applies the script sets, stores the
// descriptor key as a Variant and queues an async save.
// orig1=[esp+4] unused; orig2=[esp+8] script key ptr; orig3=[esp+0xc] extra key.
extern "C" void* __fastcall FUN_00f94480(void* self, int, int orig1, int orig2, int orig3)
{
    (void)orig1;
    void* pm = FUN_0067de30();
    void* local = 0;
    if (!(u8)((FM3)(*(void***)pm)[0x2c / 4])(pm, orig2, orig3, (int)&local)) {
        if (local) { void* t = local; ((FM0)(*(void***)t)[1])(t); }
        return 0;
    }
    if (!local) return 0;
    if (((FM1)(*(void***)local)[0x1c / 4])(local, 0x6369b24)) {
        void* t = local; ((FM0)(*(void***)t)[1])(t);
        return 0;
    }
    {
        int pv = 0;
        if (((FM2)(*(void***)local)[0x24 / 4])(local, 0xd2f669ec, (int)&pv) &&
            *(u16*)(pv + 0x12) == 0xa) {
            void* q = FUN_0041ea00((void*)pv);
            if (*(u32*)q < 1) {
                void* t = local; ((FM0)(*(void***)t)[1])(t);
                return 0;
            }
        }
    }

    void* list = FUN_00f473a0(0x38, "Terrain/ResourceManager/cPropertyList", 0, 0, 0, 0);
    void* cls = 0;
    if (list) cls = FUN_006a1b90(list, "PlanetDefinition");

    void* appProps = g_015fd918;
    if (FUN_006a25a0(appProps, 0x636d04e)) {
        ((FM1)(*(void***)cls)[0x34 / 4])(cls, (int)self);
    } else if ((orig3 & 0xff00) == 0xa100 && FUN_006a25a0(appProps, 0x636d04d)) {
        ((FM1)(*(void***)cls)[0x34 / 4])(cls, (int)self);
    } else {
        FUN_006a1710(cls, self);
    }

    FUN_00f93dd0(self, 0, *(u32*)orig2, cls);
    ((FM3)(*(void***)pm)[0x34 / 4])(pm, (int)cls, *(int*)orig2, *(int*)(orig2 + 8));

    EVariant v; v.w0 = v.w1 = v.w2 = v.w3 = 0; v.flags = 0; v.typeId = 0;
    v.typeId = 0x20; v.flags = 2;
    u32 vec[3];
    vec[0] = (u32)orig3; vec[1] = 0xb1b104; vec[2] = (u32)orig3;
    FUN_00422f40(&v, vec);
    ((FM2)(*(void***)cls)[0x14 / 4])(cls, 0x3d03f84, (int)&v);
    if (v.flags & 4) FUN_0093db80(&v, 0);

    void* sa = FUN_006b1f90(0x31389b5);
    FUN_006b4b60(cls, sa);

    if (local) { void* t = local; ((FM0)(*(void***)t)[1])(t); }
    return cls;
}
