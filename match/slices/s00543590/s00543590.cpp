// Slice s00543590: Swarm/Feed paint-variable + Atom link-attribute helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <wchar.h>

// ---------------------------------------------------------------- externals
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)

// Attribute-name pointer globals: the parser loads the pointer, then compares wide strings.
extern const wchar_t* gAttrRel;        // 0x013f396c  L"rel"
extern const wchar_t* gAttrTerm;       // 0x013f3970  L"term"
extern const wchar_t* gAttrHref;       // 0x013f3974  L"href"
extern const wchar_t* gAttrTerm2;      // 0x013f3978  L"term"  (category handler copy)
extern const wchar_t* gAttrScheme;     // 0x013f397c  L"scheme"
extern const wchar_t* gAttrEnclosure;  // 0x013f3980  L"enclosure"
extern const wchar_t* gAttrSelf;       // 0x013f3984  L"self"

unsigned int FNV1_String16(const wchar_t* s, unsigned int hash, int lower);  // 0x00932f30
extern "C" __declspec(dllimport) unsigned long wcstoul(const wchar_t*, wchar_t**, int);
void  __cdecl String8_Sprintf(void* self, const char* fmt, ...);              // 0x00472fe0
void* __cdecl String8_CtorSprintf(void* self, int tag, const char* fmt, ...); // 0x00472f50
void  __cdecl EA_Free(void* p);                                              // 0x00f47380

// ---------------------------------------------------------------- string types
struct Alloc {                       // empty allocator: passed by reference (1-byte temp)
    char mDummy;
    Alloc() {}
};

struct String8 {                     // eastl::basic_string<char>: 0x10 bytes
    char* mpBegin;                   // +0x00
    char* mpEnd;                     // +0x04
    char* mpCapacity;                // +0x08
    char* mpAllocator;               // +0x0c
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
};

struct String16 {                    // eastl::basic_string<wchar_t>: 0x0c bytes
    wchar_t* mpBegin;                // +0x00
    wchar_t* mpEnd;                  // +0x04
    wchar_t* mpCapacity;             // +0x08
    String16(const wchar_t* p, const Alloc& a = Alloc());  // 0x0041df50 (by value: sret)
    void FreeBuffer();                                     // 0x004237d0
    ~String16() { FreeBuffer(); }
};

// ---------------------------------------------------------------- link map
struct LinkNode {                    // eastl::pair<const wchar_t*, unsigned int>
    const wchar_t* mpKey;            // +0x00
    unsigned int   mnValue;          // +0x04
};

struct LinkRange {                   // iterator pair returned by find()
    LinkNode* first;                 // +0x00
    LinkNode* second;                // +0x04
};

struct LinkMap {                     // vector_map<const wchar_t*, unsigned int, char16less>
    LinkNode* mpBegin;               // +0x00
    LinkNode* mpEnd;                 // +0x04
    LinkNode* mpCapacity;            // +0x08
    void find(LinkRange& out, const wchar_t* const& key);  // 0x00548910
};

extern LinkMap gLinkMap;             // 0x015e2f54

// ---------------------------------------------------------------- entry / document
struct LinkStringMap {               // vector_map<unsigned int, String8, less<unsigned int>>
    String8* mpBegin;                // +0x00
    String8* mpEnd;                  // +0x04
    String8* mpCapacity;             // +0x08
    String8* op_index(const void* key);                    // 0x00546930
};

struct TagList {                     // vector<String16>
    String16* mpBegin;               // +0x00
    String16* mpEnd;                 // +0x04
    String16* mpCapacity;            // +0x08
    void push_back(const String16& v);                     // 0x00546a60
};

struct UintList {                    // vector<unsigned long>
    unsigned long* mpBegin;          // +0x00
    unsigned long* mpEnd;            // +0x04
    unsigned long* mpCapacity;       // +0x08
    void push_back(const unsigned long& v);                // 0x00546b00
};

struct AtomEntry40 {
    char mPad00[0x8c];
    LinkStringMap mLinkMap;          // +0x8c
    char mPad98[0x10];
    String8 mThumbLink;              // +0xa8
    String8 mAssetLink;              // +0xb8
    unsigned int mnAssetType;        // +0xc8
    char mPadCC[0x14];
    TagList mTags;                   // +0xe0
    char mPadEC[0x0c];
    UintList mUintList;              // +0xf8
};

struct AtomDocument40 {
    char mPad00[0x50];
    String8 mSelfLink;               // +0x50
};

namespace EA {
template <typename T>
class AutoRefCount {
 public:
    T* mpObject;                     // +0x00
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}

struct Ctx40 {
    char mPad00[0x20];
    EA::AutoRefCount<AtomDocument40> mpDocument;  // +0x20
    bool mbInDoc;                                 // +0x24
    char mPad25[3];
    AtomEntry40* mpCurEntry;                      // +0x28

    void FUN_00543b90(int* attrs);
    void FUN_00543bb0(int* attrs);
    void FUN_00543bd0(int* attrs);
    void FUN_00543bf0(int* attrs);
    void FUN_00543590(int* attrs);
    void FUN_005439d0(int* attrs);
    void FUN_00543c10(int* attrs, int mode);
};

// @ 0x00543b90
void Ctx40::FUN_00543b90(int* attrs) { FUN_00543c10(attrs, 1); }
// @ 0x00543bb0
void Ctx40::FUN_00543bb0(int* attrs) { FUN_00543c10(attrs, 2); }
// @ 0x00543bd0
void Ctx40::FUN_00543bd0(int* attrs) { FUN_00543c10(attrs, 3); }
// @ 0x00543bf0
void Ctx40::FUN_00543bf0(int* attrs) { FUN_00543c10(attrs, 4); }

// @ 0x00543590  SP::Feed::AtomParser::StartLink
void Ctx40::FUN_00543590(int* attrs)
{
    if (mbInDoc) {
        const wchar_t** p = (const wchar_t**)attrs;
        const wchar_t* pRel = 0;
        const wchar_t* pTerm = 0;
        const wchar_t* pHref = 0;
        while (*p != 0) {
            const wchar_t* key = *p++;
            const wchar_t* val = *p++;
            if (wcscmp(key, gAttrRel) == 0) {
                pRel = val;
                continue;
            }
            if (wcscmp(key, gAttrHref) == 0) {
                pHref = val;
                continue;
            }
            if (wcscmp(key, gAttrTerm) == 0)
                pTerm = val;
        }
        if (mpCurEntry != 0) {
            if (wcscmp(pHref, gAttrEnclosure) == 0 && pRel != 0 && pTerm != 0) {
                LinkRange res;
                gLinkMap.find(res, pRel);
                LinkNode* it = (res.first != res.second) ? res.first : gLinkMap.mpEnd;
                if (it != gLinkMap.mpEnd) {
                    unsigned int type = it->mnValue;
                    if (type == 0x2f7d0004) {
                        String8_Sprintf(&mpCurEntry->mThumbLink, "%ls", pTerm);
                    } else {
                        String8_Sprintf(&mpCurEntry->mAssetLink, "%ls", pTerm);
                        mpCurEntry->mnAssetType = type;
                    }
                }
            }
        } else {
            if (mpDocument != 0 && wcscmp(pHref, gAttrSelf) == 0 && pTerm != 0)
                String8_Sprintf(&mpDocument->mSelfLink, "%ls", pTerm);
        }
    }
}

// @ 0x005439d0  SP::Feed::AtomParser::StartCategory
void Ctx40::FUN_005439d0(int* attrs)
{
    if (mpCurEntry != 0) {
        const wchar_t** p = (const wchar_t**)attrs;
        const wchar_t* pTerm;
        unsigned int schemeHash;
        while (*p != 0) {
            const wchar_t* key = *p++;
            const wchar_t* val = *p++;
            if (wcscmp(key, gAttrTerm2) == 0) {
                pTerm = val;
                continue;
            }
            if (wcscmp(key, gAttrScheme) == 0)
                schemeHash = FNV1_String16(val, 0x811c9dc5, 1);
        }
        switch (schemeHash) {
        case 0x326cb657:
            mpCurEntry->mTags.push_back(String16(pTerm));
            break;
        case 0x9a5acf10: {
            unsigned long v = wcstoul(pTerm, 0, 0x10);
            mpCurEntry->mUintList.push_back(v);
            break;
        }
        default:
            break;
        }
    }
}

// @ 0x00543c10  SP::Feed::AtomParser::StartImage (shared by sp:image_1..4)
void Ctx40::FUN_00543c10(int* attrs, int mode)
{
    if (mbInDoc) {
        const wchar_t** p = (const wchar_t**)attrs;
        const wchar_t* pRel = 0;
        const wchar_t* pTerm = 0;
        while (*p != 0) {
            const wchar_t* key = *p++;
            const wchar_t* val = *p++;
            if (wcscmp(key, gAttrRel) == 0) {
                pRel = val;
                continue;
            }
            if (wcscmp(key, gAttrTerm) == 0)
                pTerm = val;
        }
        if (mpCurEntry != 0 && pRel != 0 && pTerm != 0) {
            LinkRange res;
            gLinkMap.find(res, pRel);
            LinkNode* it = (res.first != res.second) ? res.first : gLinkMap.mpEnd;
            if (it != gLinkMap.mpEnd) {
                unsigned int type = it->mnValue;
                if (type == 0x2f7d0004) {
                    unsigned char tag = 0;
                    String8 local;
                    String8* src = (String8*)String8_CtorSprintf(&local, tag, "%ls", pTerm);
                    String8* dst = mpCurEntry->mLinkMap.op_index(&mode);
                    if (src != dst)
                        dst->assign(src->mpBegin, src->mpEnd);
                    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin)
                        EA_Free(local.mpBegin);
                }
            }
        }
    }
}
