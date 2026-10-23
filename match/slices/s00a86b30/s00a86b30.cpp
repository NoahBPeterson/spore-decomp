// Slice s00a86b30: creature/plant simulator object family.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

typedef unsigned int uint;

// ---- element subobject at +0x40 ------------------------------------------
struct ElemTail {
    int a, b, c, d, e, f;
    void __thiscall CopyFrom(const ElemTail* o);   // 0x006f50f0
    ElemTail& __thiscall operator=(const ElemTail& o);  // 0x006f5cd0
};

// ---- 0x58-byte element ----------------------------------------------------
struct Elem {
    void* p0;        // +0x00
    int   pad4;      // +0x04 (not copied)
    void* p8;        // +0x08
    void* pc;        // +0x0c
    float f10;       // +0x10
    float f14, f18, f1c, f20, f24, f28, f2c, f30, f34;
    void* p38;       // +0x38
    void* p3c;       // +0x3c
    ElemTail tail;   // +0x40

    Elem* __thiscall CopyFrom(const Elem* o);
    Elem* __thiscall AssignFrom(const Elem* o);
};

// @ 0x00a87280
Elem* __thiscall Elem::CopyFrom(const Elem* o)
{
    p0 = o->p0;
    p8 = o->p8;
    pc = o->pc;
    f10 = o->f10;
    f14 = o->f14;
    f18 = o->f18;
    f1c = o->f1c;
    f20 = o->f20;
    f24 = o->f24;
    f28 = o->f28;
    f2c = o->f2c;
    f30 = o->f30;
    f34 = o->f34;
    p38 = o->p38;
    p3c = o->p3c;
    tail.CopyFrom(&o->tail);
    return this;
}

// @ 0x00a873c0
Elem* __thiscall Elem::AssignFrom(const Elem* o)
{
    p0 = o->p0;
    p8 = o->p8;
    pc = o->pc;
    f10 = o->f10;
    f14 = o->f14;
    f18 = o->f18;
    f1c = o->f1c;
    f20 = o->f20;
    f24 = o->f24;
    f28 = o->f28;
    f2c = o->f2c;
    f30 = o->f30;
    f34 = o->f34;
    p38 = o->p38;
    p3c = o->p3c;
    tail = o->tail;
    return this;
}

// ---- 0x58-byte element vector ---------------------------------------------
struct ElemVec {
    Elem* begin;
    Elem* end;
    Elem* cap;
};

extern bool __cdecl WriteUint32(void* stream, const uint* v, int count, int endian);  // 0x0093aa70
extern void __cdecl WriteElem(void* stream, const Elem* e);                            // 0x00a7f1d0

// @ 0x00a871e0
void* __cdecl SerializeElems(void* stream, ElemVec* v)
{
    int count = (int)((char*)v->end - (char*)v->begin) / 0x58;
    int written = count;
    WriteUint32(stream, (const uint*)&written, 1, 0);
    for (uint i = 0; i < (uint)count; i++)
        WriteElem(stream, &v->begin[i]);
    return stream;
}

// ---- vectors and the simulator object -------------------------------------
void __cdecl operator_delete__(void* p);   // 0x00f47380
void* __cdecl EAAllocate(unsigned size, const char* alloc, int a, int b, const char* file, int line); // 0x00f473a0

struct SimVectorF {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    __declspec(nothrow) ~SimVectorF() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin); }
};

struct SimVector58 {
    Elem* mpBegin;
    Elem* mpEnd;
    Elem* mpCapacity;
    void __thiscall FreeRange(Elem* first, Elem* last);   // 0x00a87300
    void __thiscall Insert(Elem* pos, unsigned count, const Elem* value);  // 0x00a87980
    SimVector58* __thiscall Assign(SimVector58* src);                      // 0x00a87b90
    void __thiscall EraseRange(Elem* first, Elem* last);                   // 0x00a87cd0
    void __thiscall Resize(unsigned n);
    __declspec(nothrow) ~SimVector58()
    {
        FreeRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};

struct Sim {
    char pad00[0x8];        // vptr + refcount
    char pad08[0x58];
    SimVectorF v60;         // +0x060
    char pad6c[0xc];
    SimVectorF v78;         // +0x078
    char pad84[0x8];
    SimVectorF v8c;         // +0x08c
    char pad98[0x8];
    SimVectorF va0;         // +0x0a0
    char pad_ac[0x20];
    SimVectorF vcc;         // +0x0cc
    char pad_d8[0x14];
    SimVectorF vec;         // +0x0ec
    char pad_f8[0xc];
    SimVector58 v104;       // +0x104
    char pad110[0x5c];
    SimVectorF v16c;        // +0x16c
};

// @ 0x00a87720
void __fastcall Sim_Dtor(Sim* self)
{
    self->v16c.~SimVectorF();
    self->v104.~SimVector58();
    self->vec.~SimVectorF();
    self->vcc.~SimVectorF();
    self->va0.~SimVectorF();
    self->v8c.~SimVectorF();
    self->v78.~SimVectorF();
    self->v60.~SimVectorF();
    *(void**)self = (void*)0x013ef094;
}

// ---- simulator constructor ------------------------------------------------
extern float gf_one;        // 0x01485720
extern float gfa;           // 0x016780dc
extern float gfb;           // 0x016780e0
extern float gfc;           // 0x016780e4
extern float gf_tenth;      // 0x01488874
extern float gf_neg_10000;  // 0x01418f90
extern float gf_pos_10000;  // 0x013f0620
extern char  g_default_matrix[];   // 0x01678188

struct Matrix3 {
    char data[0x24];
    void __thiscall Assign(const void* m);   // 0x0041cb40
};

template <class T> static inline T& Fld(void* base, unsigned off) { return *(T*)((char*)base + off); }
template <class T> static inline T* At(void* base, unsigned off) { return (T*)((char*)base + off); }

// @ 0x00a874f0
void* __fastcall SimCtor(Sim* self)
{
    float one = gf_one;
    unsigned short zlo = 0;
    unsigned short zhi = 0;
    Fld<unsigned>(self, 0x004) = 0;
    Fld<unsigned>(self, 0x000) = 0x01458270;
    Fld<unsigned>(self, 0x008) = 0;
    Fld<unsigned>(self, 0x00c) = 1;
    Fld<unsigned char>(self, 0x014) = 0;
    Fld<unsigned>(self, 0x018) = 0;
    Fld<unsigned char>(self, 0x01c) = 0;
    Fld<float>(self, 0x020) = one;
    Fld<unsigned>(self, 0x010) = 0xffffffff;
    Fld<unsigned short>(self, 0x026) = zhi;
    Fld<unsigned short>(self, 0x024) = zlo;
    Fld<float>(self, 0x028) = gfa;
    Fld<float>(self, 0x02c) = gfb;
    Fld<float>(self, 0x030) = gfc;
    Fld<float>(self, 0x034) = one;
    ((Matrix3*)((char*)self + 0x38))->Assign(g_default_matrix);
    Fld<float>(self, 0x05c) = gf_tenth;
    Fld<unsigned>(self, 0x060) = 0;
    Fld<unsigned>(self, 0x064) = 0;
    Fld<unsigned>(self, 0x068) = 0;
    Fld<float>(self, 0x074) = 0.0f;
    Fld<unsigned>(self, 0x078) = 0;
    Fld<unsigned>(self, 0x07c) = 0;
    Fld<unsigned>(self, 0x080) = 0;
    Fld<unsigned>(self, 0x08c) = 0;
    Fld<unsigned>(self, 0x090) = 0;
    Fld<unsigned>(self, 0x094) = 0;
    Fld<unsigned>(self, 0x0a0) = 0;
    Fld<unsigned>(self, 0x0a4) = 0;
    Fld<unsigned>(self, 0x0a8) = 0;
    Fld<float>(self, 0x0b4) = 0.0f;
    Fld<float>(self, 0x0b8) = 0.0f;
    Fld<float>(self, 0x0bc) = 0.0f;
    Fld<float>(self, 0x0c0) = 0.0f;
    Fld<float>(self, 0x0c4) = 0.0f;
    Fld<float>(self, 0x0c8) = 0.0f;
    Fld<unsigned>(self, 0x0cc) = 0;
    Fld<unsigned>(self, 0x0d0) = 0;
    Fld<unsigned>(self, 0x0d4) = 0;
    Fld<float>(self, 0x0e0) = gfa;
    Fld<float>(self, 0x0e4) = gfb;
    Fld<float>(self, 0x0e8) = gfc;
    Fld<unsigned>(self, 0x0ec) = 0;
    Fld<unsigned>(self, 0x0f0) = 0;
    Fld<unsigned>(self, 0x0f4) = 0;
    Fld<float>(self, 0x100) = 0.0f;
    Fld<unsigned>(self, 0x104) = 0;
    Fld<unsigned>(self, 0x108) = 0;
    Fld<unsigned>(self, 0x10c) = 0;
    Fld<unsigned>(self, 0x118) = 0xffffffff;
    Fld<unsigned>(self, 0x11c) = 0xffffffff;
    Fld<unsigned>(self, 0x120) = 0xffffffff;
    Fld<unsigned>(self, 0x124) = 0xffffffff;
    Fld<unsigned>(self, 0x128) = 0xffffffff;
    Fld<unsigned>(self, 0x12c) = 0xffffffff;
    Fld<float>(self, 0x130) = gf_neg_10000;
    Fld<float>(self, 0x134) = gf_pos_10000;
    Fld<unsigned>(self, 0x138) = 0xffffffff;
    Fld<unsigned>(self, 0x13c) = 0xffffffff;
    Fld<unsigned char>(self, 0x140) = 0;
    Fld<unsigned char>(self, 0x141) = 0;
    Fld<unsigned char>(self, 0x142) = 0;
    Fld<unsigned char>(self, 0x143) = 0;
    Fld<unsigned>(self, 0x150) = 0xffffffff;
    Fld<unsigned>(self, 0x154) = 0xffffffff;
    Fld<float>(self, 0x148) = 0.0f;
    Fld<unsigned short>(self, 0x144) = 0;
    Fld<unsigned char>(self, 0x158) = 0;
    Fld<unsigned>(self, 0x15c) = 0;
    Fld<unsigned>(self, 0x160) = 0;
    Fld<unsigned>(self, 0x164) = 0;
    Fld<float>(self, 0x168) = 0.0f;
    Fld<unsigned>(self, 0x16c) = 0;
    Fld<unsigned>(self, 0x170) = 0;
    Fld<unsigned>(self, 0x174) = 0;
    return self;
}

// ---- transform application ------------------------------------------------
struct TransOps {
    char data[0x38];
    TransOps* __thiscall Assign(const void* src);   // 0x00537dc0
};
extern TransOps* __cdecl MulTrans(TransOps* out, const void* a, const void* b);  // 0x007d5590

struct RefcThing {
    TransOps* __thiscall Assign(const void* src);   // 0x00537dc0
    unsigned short flags;    // +0x00
    unsigned short count;    // +0x02
    char pad04[0xc];
    float f10;               // +0x10
    char pad14[0x34];
    float f48;               // +0x48
};

struct Notifier {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4();
    virtual void Notify(void* p);    // +0x14
};

struct SimOps {
    void __thiscall Apply(void* a2, void* a3);
};

// @ 0x00a870b0
void __thiscall SimOps::Apply(void* a2, void* a3)
{
    if (Fld<unsigned char>(this, 0x7c) != 0)
        return;
    TransOps tmp;
    TransOps* dst = (TransOps*)((char*)this + 0x14);
    TransOps* r = MulTrans(&tmp, a2, a3);
    dst->Assign(r);
    if (((Fld<unsigned>(Fld<void*>(this, 0x0c), 0x08) >> 2) % 2) == 0)
        return;
    TransOps* other = Fld<TransOps*>(this, 0x90);
    if (other == 0)
        return;
    other->Assign(dst);
    float f = *Fld<float*>(Fld<void*>(this, 0x0c), 0x48) * Fld<float>(this, 0x68);
    RefcThing* t = Fld<RefcThing*>(this, 0x90);
    t->flags |= 1;
    t->count++;
    f *= t->f10;
    t->f10 = f;
    Fld<RefcThing*>(this, 0x90)->f48 = *Fld<float*>(Fld<void*>(this, 0x0c), 0x34) * Fld<float>(this, 0x6c);
    Fld<Notifier*>(this, 0x8c)->Notify(Fld<RefcThing*>(this, 0x90));
}

extern float gf_def3c;   // 0x01457d54

// @ 0x00a87e60
void __thiscall SimVector58::Resize(unsigned n)
{
    Elem* begin = mpBegin;
    unsigned want = n;
    int count = (int)((char*)mpEnd - (char*)begin) / 0x58;
    if (want > (unsigned)count) {
        Elem def;
        Fld<unsigned>(&def, 0x00) = 0;
        Fld<unsigned>(&def, 0x40) = 0;
        Fld<unsigned>(&def, 0x44) = 0;
        Fld<unsigned>(&def, 0x48) = 0;
        Fld<unsigned>(&def, 0x08) = 0xffffffff;
        Fld<unsigned>(&def, 0x0c) = 0xffffffff;
        Fld<unsigned>(&def, 0x3c) = 0xffffffff;
        Fld<float>(&def, 0x1c) = 0.0f;
        Fld<float>(&def, 0x20) = 0.0f;
        Fld<float>(&def, 0x24) = 0.0f;
        Fld<float>(&def, 0x2c) = 0.0f;
        Fld<float>(&def, 0x30) = 0.0f;
        Fld<float>(&def, 0x34) = 0.0f;
        Fld<float>(&def, 0x14) = gf_one;
        Fld<float>(&def, 0x18) = gf_one;
        Fld<float>(&def, 0x28) = gf_one;
        Fld<float>(&def, 0x38) = gf_def3c;
        Insert(mpEnd, want - (unsigned)count, &def);
        return;
    }
    EraseRange(begin + want, mpEnd);
}

// ---- vector assignment ----------------------------------------------------
struct VecInitStub { void __thiscall Init(int count, Elem** cap); };           // 0x00a87860
extern void* __cdecl VecDoAssign(void** out, Elem* begin, Elem* end, void* a, void* b); // 0x00a87340

struct VecAssigner {
    void* p0;
    void* p4;
    VecAssigner* __thiscall Assign(ElemVec* src);
};

// @ 0x00a87920
VecAssigner* __thiscall VecAssigner::Assign(ElemVec* src)
{
    int count = (int)((char*)src->end - (char*)src->begin) / 0x58;
    ((VecInitStub*)this)->Init(count, (Elem**)((char*)src + 0xc));
    VecDoAssign((void**)&src, src->begin, src->end, p0, src);
    p4 = src;
    return this;
}

// ---- vector primitives (EASTL) -------------------------------------------
extern Elem* __cdecl UninitCopy(Elem* first, Elem* last, Elem* dst);        // 0x00a87380
extern void  __cdecl DestroyRange3(Elem* first, Elem* last, Elem* mem);     // 0x00a87240
extern Elem* __cdecl FillElems(Elem* dst, unsigned count, const Elem* v);   // 0x00a87440
extern Elem* __cdecl CopyCtorElem(Elem* dst, const Elem* src);              // 0x00a87280
extern Elem* __cdecl CopyRange3(Elem* first, Elem* last, Elem* dst);        // 0x00a87470
extern void  __cdecl CopyBack3(Elem* first, Elem* last, Elem* dst);         // 0x00a874b0
extern void  __cdecl DestroyLocal3(Elem* first, Elem* last, const Elem* v); // 0x00a87810
extern Elem* __cdecl AllocCopyRange(unsigned count, Elem* first, Elem* last); // 0x00a878c0

// @ 0x00a87980
void __thiscall SimVector58::Insert(Elem* pos, unsigned count, const Elem* value)
{
    unsigned cap = (unsigned)(((char*)mpCapacity - (char*)mpBegin) / 0x58);
    if (cap < count) {
        unsigned oldCount = (unsigned)(((char*)mpEnd - (char*)mpBegin) / 0x58);
        unsigned newCap = oldCount * 2;
        if (oldCount == 0)
            newCap = 1;
        unsigned needed = oldCount + count;
        if (newCap < needed)
            newCap = needed;
        Elem* newMem = 0;
        if (newCap != 0)
            newMem = (Elem*)EAAllocate(newCap * 0x58, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        Elem* newPos = UninitCopy(mpBegin, pos, newMem);
        DestroyRange3(mpBegin, pos, newMem);
        Elem* newEnd = FillElems(newPos, count, value);
        newEnd = UninitCopy(pos, mpEnd, newEnd);
        DestroyRange3(pos, mpEnd, newMem + count);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpBegin = newMem;
        mpEnd = newEnd;
        mpCapacity = newMem + newCap;
        return;
    }
    if (count == 0)
        return;
    Elem tmp;
    CopyCtorElem(&tmp, value);
    Elem* oldEnd = mpEnd;
    unsigned after = (unsigned)(((char*)oldEnd - (char*)pos) / 0x58);
    if (count < after) {
        Elem* cut = oldEnd - count;
        VecDoAssign((void**)&pos, cut, oldEnd, oldEnd, pos);
        mpEnd = oldEnd + count;
        CopyBack3(pos, cut, oldEnd);
        Elem* newEnd = pos + count;
        DestroyLocal3(pos, newEnd, &tmp);
    } else {
        FillElems(oldEnd, count - after, &tmp);
        mpEnd = oldEnd + (count - after);
        VecDoAssign((void**)&pos, pos, oldEnd, mpEnd, pos);
        mpEnd = mpEnd + after;
        DestroyLocal3(pos, oldEnd, &tmp);
    }
}

// @ 0x00a87b90
SimVector58* __thiscall SimVector58::Assign(SimVector58* src)
{
    if (src == this)
        return this;
    unsigned srcCount = (unsigned)(((char*)src->mpEnd - (char*)src->mpBegin) / 0x58);
    unsigned myCap = (unsigned)(((char*)mpCapacity - (char*)mpBegin) / 0x58);
    if (myCap < srcCount) {
        Elem* nb = AllocCopyRange(srcCount, src->mpBegin, src->mpEnd);
        FreeRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpEnd = nb + srcCount;
        mpBegin = nb;
        mpCapacity = nb + srcCount;
        return this;
    }
    unsigned myCount = (unsigned)(((char*)mpEnd - (char*)mpBegin) / 0x58);
    if (myCount < srcCount) {
        CopyRange3(src->mpBegin, src->mpBegin + myCount, mpBegin);
        VecDoAssign((void**)&src, src->mpBegin + myCount, src->mpEnd, mpEnd, src->mpEnd);
        mpEnd = mpBegin + srcCount;
    } else {
        Elem* e = CopyRange3(src->mpBegin, src->mpEnd, mpBegin);
        FreeRange(e, mpEnd);
        mpEnd = mpBegin + srcCount;
    }
    return this;
}

// ---- curve sampling and simulation update --------------------------------
struct Vec3 {
    float x, y, z;
};

extern float gf_curve_eps;   // 0x01485378
extern void __cdecl MulVec(void* dst, const void* src);   // 0x00705290

static float __cdecl SampleCurve(const float* v, unsigned count, float t)
{
    unsigned segs = count - 1;
    if (segs == 0)
        return v[0];
    float fs = (float)segs;
    int i = (int)(fs * t);
    float frac = fs * t - (float)i;
    if (frac <= 0.0f)
        return v[i];
    return (v[i + 1] - v[i]) * frac + v[i];
}

static Vec3 __cdecl SampleVec3(const Vec3* v, unsigned count, float t)
{
    Vec3 r;
    unsigned segs = count - 1;
    if (segs == 0) {
        r = v[0];
        return r;
    }
    float fs = (float)segs;
    int i = (int)(fs * t);
    float frac = fs * t - (float)i;
    if (frac <= 0.0f) {
        r = v[i];
        return r;
    }
    r.x = (v[i + 1].x - v[i].x) * frac + v[i].x;
    r.y = (v[i + 1].y - v[i].y) * frac + v[i].y;
    r.z = (v[i + 1].z - v[i].z) * frac + v[i].z;
    return r;
}

struct SampleIface {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual bool QueryVec(const float* v);          // +0x18
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void Transform(const void* out, const float* in);   // +0x2c
};

struct SimUpd : Sim {
    void Update(float dt, float blend, void* ctx);
};

// @ 0x00a86b30
void __thiscall SimUpd::Update(float dt, float blend, void* ctx)
{
    if (Fld<void*>(this, 0x90) == 0)
        return;
    Fld<int>((char*)ctx, 0x28) += 1;
    float time = Fld<float>(this, 0x80) + dt;
    Fld<float>(this, 0x80) = time;
    float tt = Fld<float>(this, 0x84) * time;
    void* desc = Fld<void*>(this, 0x0c);
    char mode = *At<char>(desc, 0xd);
    if (mode == 0) {
        int n = (int)tt;
        if (tt < (float)n)
            n = n - 1;
        tt = tt - (float)n;
    } else if (tt > 1.0f) {
        if (mode == 1) {
            void** vt = *(void***)this;
            ((void(__thiscall*)(void*, int))vt[3])(this, 0);
            return;
        }
        tt = 1.0f;
    }

    unsigned n0 = (unsigned)((*(int*)((char*)desc + 0x60) - *(int*)((char*)desc + 0x5c)) >> 2);
    float c0 = SampleCurve(*(const float**)((char*)desc + 0x5c), n0, tt);
    float value = Fld<float>(this, 0x78) * Fld<float>(this, 0x64) * c0
        * ((Fld<float>(this, 0x58) - Fld<float>(this, 0x54)) * blend + Fld<float>(this, 0x54));
    void* target = Fld<void*>(this, 0x90);
    Vec3 ones;
    ones.x = 1.0f; ones.y = 1.0f; ones.z = 1.0f;

    if (((Fld<unsigned>((char*)desc, 0x08) >> 2) & 1) == 0) {
        ((TransOps*)((char*)target + 0x14))->Assign((char*)this + 0x14);

        unsigned n1 = (unsigned)((*(int*)((char*)desc + 0x4c) - *(int*)((char*)desc + 0x48)) >> 2);
        float c1 = SampleCurve(*(const float**)((char*)desc + 0x48), n1, tt);
        Fld<unsigned short>(target, 0x00) |= 1;
        Fld<unsigned short>(target, 0x02) += 1;
        Fld<float>(target, 0x10) = c1 * blend * Fld<float>(target, 0x10);

        unsigned n2 = (unsigned)((*(int*)((char*)desc + 0x38) - *(int*)((char*)desc + 0x34)) >> 2);
        float c2 = SampleCurve(*(const float**)((char*)desc + 0x34), n2, tt);
        Fld<float>(target, 0x48) = Fld<float>(this, 0x6c) * c2;

        unsigned n3 = (unsigned)((*(int*)((char*)desc + 0x88) - *(int*)((char*)desc + 0x84)) >> 2);
        float c3 = SampleCurve(*(const float**)((char*)desc + 0x84), n3, tt);
        Fld<float>(target, 0x4c) = Fld<float>(this, 0x74) * c3;

        Vec3* vb = *(Vec3**)((char*)desc + 0x70);
        Vec3* ve = *(Vec3**)((char*)desc + 0x74);
        if (vb != ve) {
            unsigned nv = (unsigned)((char*)ve - (char*)vb) / 0xc;
            ones = SampleVec3(vb, nv, tt);
        }

        SampleIface* iface = Fld<SampleIface*>(this, 0x88);
        if (iface != 0) {
            float local[3];
            local[0] = Fld<float>(this, 0x18);
            local[1] = Fld<float>(this, 0x1c);
            local[2] = Fld<float>(this, 0x20);
            if (iface->QueryVec(local)) {
                float out[4];
                iface->Transform(out, local);
                value = out[2] * value;
                MulVec(&ones, out);
            }
        }
        Fld<float>(target, 0x44) = value;
        Fld<float>(target, 0x38) = ones.x;
        Fld<float>(target, 0x3c) = ones.y;
        Fld<float>(target, 0x40) = ones.z;
    } else {
        if (Fld<float>(target, 0x44) == value)
            return;
        Fld<float>(target, 0x44) = value;
    }
    Fld<Notifier*>(this, 0x8c)->Notify(target);
}
