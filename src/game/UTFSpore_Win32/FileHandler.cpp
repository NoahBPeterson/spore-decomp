// src/game/UTFSpore_Win32/FileHandler.cpp -- migrated from slice(s) s008fc670 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/FileHandler.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" int __cdecl strcmp(const char*, const char*);
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
#include <intrin.h>
#pragma function(memcpy)
#pragma intrinsic(strcmp)

// ---- items of slice s008fc670 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl operator_delete__(void*);
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
inline void* operator new(unsigned size, const char* name, int a, int b, int c, int d)
{
    return operator_new(size, name, a, b, c, d);
}
typedef unsigned int size_type;
typedef int ptrdiff_t_;
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
template <typename T> inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
inline size_type CharStrlen(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p)
        ++p;
    return (size_type)(p - s);
}
inline int CharCompare(const wchar_t* p1, const wchar_t* p2, size_type n)
{
    for (; n > 0; ++p1, ++p2, --n) {
        if (*p1 != *p2)
            return (*p1 < *p2) ? -1 : 1;
    }
    return 0;
}
inline int StrCompare(const wchar_t* pBegin1, const wchar_t* pEnd1, const wchar_t* pBegin2, const wchar_t* pEnd2)
{
    const ptrdiff_t_ n1 = pEnd1 - pBegin1;
    const ptrdiff_t_ n2 = pEnd2 - pBegin2;
    const ptrdiff_t_ nMin = min_alt(n1, n2);
    const int cmp = CharCompare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
}
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    int compare(size_type pos1, size_type n1, const wchar_t* p) const
    {
        return StrCompare(mpBegin + pos1, mpBegin + pos1 + min_alt(n1, size() - pos1), p, p + CharStrlen(p));
    }
    void erase(wchar_t* first, wchar_t* last)
    {
        if (first != last) {
            memmove(first, last, (size_type)((mpEnd - last) + 1) * sizeof(wchar_t));
            mpEnd -= (last - first);
        }
    }
};
wchar_t* __cdecl PathComponentEnd(wchar_t* first, wchar_t* last, int n);    // 0x920da0
struct FStr96 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    const char* mpName;
    wchar_t* mpPoolBegin;
    wchar_t mBuf[96];
    FStr96()
    {
        mpPoolBegin = mBuf;
        mpBegin = mBuf;
        mpCapacity = mBuf + 96;
        mpEnd = mBuf;
        mBuf[0] = 0;
    }
    FStr96(const FStr96& x);                // 0x5d7270
    void DeallocateSelf()
    {
        if ((int)((mpCapacity - mpBegin) * 2) > 2 && mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    ~FStr96() { DeallocateSelf(); }
};
struct FSStream {
    virtual void d0();
    virtual void AddRef();                  // +4
    virtual void Release();                 // +8
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12();
    virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18();
    virtual bool Open(int access, int disp, int share, int flags);  // +0x4c
    char pad[0x22c - 4];
    FSStream(const wchar_t* path);          // 0x931e10
};
struct FileReq {
    char pad0[0xc];
    const char* mUrl;       // +0xc
    void SetContentType(const wchar_t* t);  // 0xa355e0
    void SetStream(FSStream* s);            // 0x836480
};
struct ReqProvider {
    void Complete(FileReq* r, int status);  // 0x8ffb40
};
struct HIt {
    void* node;
    void* bucket;
    HIt() {}
    HIt(const HIt& o) : node(o.node), bucket(o.bucket) {}
};
struct ExtMap {
    int mAlloc;
    void** mpBucketArray;   // +4
    unsigned mnBucketCount; // +8
    HIt find(const wchar_t* const& key);    // 0x8fbbf0
};
struct ExtNode { void* next; const wchar_t* second; };
bool __cdecl ConvertURLToFilePath(const char* url, FStr96* out);
void __cdecl PathSimplify(FStr96* s);       // 0x921140
FStr96* __cdecl PathJoin(FStr96* a, const FStr96* b);   // 0x921210
const wchar_t* __cdecl PathGetFileName(const FStr96* s);// 0x920ee0
struct FileHandler {
    void* vt;
    int rc;
    ReqProvider* mpProvider;    // +8
    ExtMap mExt;                // +0xc
    char pad[0x2c - 0x18];
    FStr96 mBase;               // +0x2c
    bool ProcessRequest(FileReq* req, int unused);
};
// ---- items of slice s008fc670 end

// @ 0x008fcbd0
void __cdecl StripLeadingDotComponents(WStr* s)
{
    wchar_t* pos = PathComponentEnd(s->mpBegin, s->mpEnd, 0);
    while (pos != s->mpEnd) {
        const size_type idx = (size_type)(pos - s->mpBegin);
        if (s->compare(0, idx, L".") != 0 && s->compare(0, idx, L"..") != 0 && s->compare(0, idx, L"") != 0)
            return;
        s->erase(s->mpBegin, pos + 1);
        pos = PathComponentEnd(s->mpBegin, s->mpEnd, 0);
    }
}

// @ 0x008fce50
bool FileHandler::ProcessRequest(FileReq* req, int unused)
{
    if (mpProvider == 0)
        return false;
    FStr96 path;
    if (ConvertURLToFilePath(req->mUrl, &path)) {
        PathSimplify(&path);
        StripLeadingDotComponents((WStr*)&path);
        if (path.mpBegin != path.mpEnd) {
            FStr96 full(mBase);
            PathJoin(&full, &path);
            const wchar_t* ext = PathGetFileName(&full);
            if (*ext == L'.')
                ++ext;
            HIt it = mExt.find(ext);
            if (it.node != mExt.mpBucketArray[mExt.mnBucketCount])
                req->SetContentType(((ExtNode*)it.node)->second);
            FSStream* fs = new("FileHandler/FileStream", 0, 0, 0, 0) FSStream(full.mpBegin);
            if (fs) {
                fs->AddRef();
                if (fs->Open(1, 6, 1, 0)) {
                    req->SetStream(fs);
                    mpProvider->Complete(req, 2);
                    fs->Release();
                    return true;
                }
                fs->Release();
            }
        }
    }
    mpProvider->Complete(req, 3);
    return false;
}
