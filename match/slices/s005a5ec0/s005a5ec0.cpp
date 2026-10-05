// slice s005a5ec0 — SP::cSPEditorColorPicker (Init/Update/Clear) and cSPColorSwatch::Update.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>
#include "types.h"

#define PV(n) virtual void pv##n();

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }

struct Property {
    char pad[0x10];
    uint32_t mFlags;
    unsigned short mType;
    int* GetInt();
    uint32_t* GetUInt();
    float* GetFloat();
};

namespace EA {
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p) { if (p != mpObject) { T* t = mpObject; if (p) p->AddRef(); mpObject = p; if (t) t->Release(); } return *this; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() { int n = (*(volatile int*)&mnRefCount += -1); if (n == 0) { mnRefCount = 1; delete this; return 0; } return mnRefCount; }
    T mnRefCount;
};
namespace COM {
class IUnknown32 { public: virtual int AddRef() = 0; virtual int Release() = 0; };
}
struct RectT { float left, top, right, bottom; RectT() {} float Width() const { return right - left; } float Height() const { return bottom - top; } };
}

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t id, Property*& result);
};

namespace eastl {
struct sp_vector_allocator {
    uint32_t mData[2];
    sp_vector_allocator() {}
    void deallocate(void* p, size_t) { if (((uint32_t*)p)[-1]) operator delete[]((char*)p); }
};
template <typename T>
class sp_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector();
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](unsigned int i) { return mpBegin[i]; }
    T* erase(T* first, T* last);
};
template <typename T>
__declspec(noinline) sp_vector<T>::~sp_vector() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
template <typename T>
__declspec(noinline) T* sp_vector<T>::erase(T* first, T* last) {
    memmove(first, last, (char*)mpEnd - (char*)last);
    mpEnd -= (last - first);
    return first;
}
}

struct cSPColorRGB { float r, g, b; cSPColorRGB() {} cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {} };

class cSPColorSwatch {
public:
    void Cleanup();  // 0x005a5db0
    void Update(int deltaTime);  // 0x005a63d0
};

class cSPEditorColorPicker : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
public:
    EA::AutoRefCount<cSPColorSwatch> mSelectedSwatch;  // +0xc
    void* mWinRoot;             // +0x10
    float mRootWidth;           // +0x14
    float mRootHeight;          // +0x18
    cSPColorRGB mSelectedColor; // +0x1c
    int mUnknown28;             // +0x28
    int mSelectedIndex;         // +0x2c
    eastl::sp_vector<cSPColorSwatch*> mSwatches;  // +0x30
    int mNumColors;             // +0x44
    EA::AutoRefCount<cPropertyList> mColorPickerConfig;  // +0x48

    void Init(void* param);            // 0x005a5ec0
    void Clear();                      // 0x005a6390
    void Update(int deltaTime);        // 0x005a6db0
};

// ============================================================================
// @ 0x005a5ec0  SP::cSPEditorColorPicker::Init  (abridged)
void cSPEditorColorPicker::Init(void*) {
    mUnknown28 = 0;
    mSelectedIndex = 0;
    mNumColors = 5;
}

// @ 0x005a6390  SP::cSPEditorColorPicker::Clear
void cSPEditorColorPicker::Clear() {
    eastl::sp_vector<cSPColorSwatch*>& v = mSwatches;
    int n = (int)(v.mpEnd - v.mpBegin);
    for (int i = 0; i < n; i++)
        v.mpBegin[i]->Cleanup();
    v.erase(v.mpBegin, v.mpEnd);
}

// @ 0x005a63d0  SP::cSPColorSwatch::Update  (abridged)
void cSPColorSwatch::Update(int) {
}

// @ 0x005a6db0  SP::cSPEditorColorPicker::Update  (abridged)
void cSPEditorColorPicker::Update(int) {
}

inline float Maxf(float a, float b) { return a > b ? a : b; }
inline float Minf(float a, float b) { return a < b ? a : b; }

// @ 0x005a6e00
float FUN_005a6e00(float x) {
    return Minf(Maxf(0.0f, x), 1.0f);
}
