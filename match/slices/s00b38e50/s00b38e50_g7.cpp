// Slice s00b38e50 (gold7): heap helpers (sift-down + pop-heap) for an 8-byte
// ref-counted element type {ResourcePtr; float}.
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef uint8_t u8;
typedef uint32_t u32;

// ---------------------------------------------------------------- resource objects
// Release is a manager call at vtable +0x170 with (object, threaded-flag).
struct ResManager {
    virtual void v000();
    virtual void v004();
    virtual void v008();
    virtual void v00c();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01c();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02c();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03c();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04c();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05c();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06c();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07c();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08c();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09c();
    virtual void v0a0();
    virtual void v0a4();
    virtual void v0a8();
    virtual void v0ac();
    virtual void v0b0();
    virtual void v0b4();
    virtual void v0b8();
    virtual void v0bc();
    virtual void v0c0();
    virtual void v0c4();
    virtual void v0c8();
    virtual void v0cc();
    virtual void v0d0();
    virtual void v0d4();
    virtual void v0d8();
    virtual void v0dc();
    virtual void v0e0();
    virtual void v0e4();
    virtual void v0e8();
    virtual void v0ec();
    virtual void v0f0();
    virtual void v0f4();
    virtual void v0f8();
    virtual void v0fc();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10c();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11c();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12c();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13c();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14c();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15c();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16c();
    virtual void Release(void* object, char threaded);  // +0x170
};

struct Res {
    ResManager* mpManager;   // +0x00
    u32 mFlags;              // +0x04
    u8 pad08[0x40 - 0x08];
    int mRefCount;           // +0x40

    void AddRef() { ++mRefCount; }
    void Release()
    {
        if (mRefCount > 1)
            --mRefCount;
        else
        {
            bool threaded = (mFlags >> 31) & 1;
            mpManager->Release(this, (char)threaded);
        }
    }
};

struct SmartPtr {
    Res* mpRes;                                        // +0x00

    SmartPtr() {}
    SmartPtr(const SmartPtr& o) : mpRes(o.mpRes) { if (mpRes) mpRes->AddRef(); }
    ~SmartPtr() { if (mpRes) mpRes->Release(); }

    SmartPtr& operator=(Res* p);                       // 0x00478db0 (not inlined)

    __forceinline SmartPtr& operator=(const SmartPtr& o)
    {
        Res* p = o.mpRes;
        if (p != mpRes)
        {
            Res* old = mpRes;
            if (p)
                p->AddRef();
            mpRes = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------- heap element
struct Elem {
    SmartPtr mObj;   // +0x00
    float mVal;      // +0x04

    Elem() {}
    Elem(const Elem& o) : mObj(o.mObj), mVal(o.mVal) {}
    ~Elem() {}

    __forceinline Elem& operator=(const Elem& o)
    {
        mObj = o.mObj;
        mVal = o.mVal;
        return *this;
    }
};

struct Cmp {
    bool Less(const Elem& a, const Elem& b);           // 0x00b385d0
};

void PushHeap(Elem* first, int topIndex, int holeIndex, Elem value, Cmp comp);  // 0x00b38bf0

// @ 0x00b39970
void SiftDown(Elem* first, int topIndex, int length, int holeIndex, Elem value, Cmp comp)
{
    int child = 2 * holeIndex + 2;
    if (child < length)
    {
        do
        {
            if (comp.Less(first[child], first[child - 1]))
                --child;
            first[holeIndex] = first[child];
            holeIndex = child;
            child = 2 * child + 2;
        } while (child < length);
    }
    if (child == length)
    {
        first[holeIndex] = first[child - 1];
        holeIndex = child - 1;
    }
    PushHeap(first, topIndex, holeIndex, value, comp);
}

// @ 0x00b39ac0
void PopHeap(Elem* first, Elem* last, Cmp comp)
{
    Elem* pLast = last - 1;
    Elem value = *pLast;
    pLast->mObj = first->mObj.mpRes;
    pLast->mVal = first->mVal;
    SiftDown(first, 0, (int)(last - first) - 1, 0, value, comp);
}
