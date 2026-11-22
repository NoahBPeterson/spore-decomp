// src/game/SPEditors/SPPlayModeTokenTranslator.cpp -- migrated from slice(s) s00634490 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayModeTokenTranslator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlayModeTokenTranslator.h"
#include "SP/cSPPlayModeUI.h"
#include "SP/cSPPlayModePhotoBrowser.h"
#include "SP/cPropertyList.h"
#include "EA/Stopwatch.h"
#include "SP/cJob.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorUI.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"

// ---- items of slice s00634490 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memmove(void*, const void*, size_t);
struct wstring16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    wstring16& operator=(const wchar_t* p);   // 0x005c3d90
};
struct cStringTokenTranslator {
    virtual void v0();
    uint32_t pad;
    cStringTokenTranslator();     // 0x006b5870
};
struct cPlayModeTokenTranslator : cStringTokenTranslator {
    uint32_t pageCurrent;         // +0x08
    uint32_t pageCount;           // +0x0c
    uint32_t photoCurrent;        // +0x10
    uint32_t photoCount;          // +0x14
    const wchar_t* movieName;     // +0x18
    const wchar_t* moviePathname; // +0x1c
    uint32_t bgPageCurrent;       // +0x20
    uint32_t bgPageCount;         // +0x24
    uint32_t animPageCurrent;     // +0x28
    uint32_t animPageCount;       // +0x2c
    const wchar_t* videoURL;      // +0x30
    const wchar_t* statusMessage; // +0x34
    const wchar_t* gifName;       // +0x38
    const wchar_t* mayaExportName;// +0x3c
    const wchar_t* mayaExportPath;// +0x40
    const wchar_t* mYear;         // +0x44
    const wchar_t* mMonth;        // +0x48
    const wchar_t* mDayOfMonth;   // +0x4c
    const wchar_t* mTime;         // +0x50
    const wchar_t* mUnused54;     // +0x54
    const wchar_t* movieNamePrefix; // +0x58
    const wchar_t* mUnused5c;     // +0x5c

    cPlayModeTokenTranslator();
    bool TranslateToken(const wchar_t* token, wstring16* out);
};
struct PropertyListG {
    bool GetBool(uint32_t id);    // 0x006a25a0
};
extern PropertyListG* gPropList;  // 0x015fd918
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseFold);   // 0x00932f30
void SetNumberString(double v, wchar_t* buf, int len, int flag);          // 0x00881ea0
#define STR_CASE(h, field)                \
    case h:                               \
        if (field) {                      \
            *out = field;                 \
            return true;                  \
        }                                 \
        return false;
#define STR_CASE_FIX(h, field)            \
    case h:                               \
        if (field) {                      \
            *out = field;                 \
            FixSlashes(out);              \
            return true;                  \
        }                                 \
        return false;
#define NUM_CASE(h, field)                       \
    case h: {                                    \
        *out = L"";                              \
        wchar_t buf[64];                         \
        SetNumberString((double)(uint32_t)(field), buf, 0x40, 0); \
        buf[63] = 0;                             \
        *out = buf;                              \
        return true;                             \
    }
// ---- items of slice s00634490 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* memmove(void*, const void*, size_t);
extern PropertyListG* gPropList;  // 0x015fd918

// @ 0x00634640
static void FixSlashes(wstring16* s)
{
    char c = gPropList->GetBool(0x61b67b6) ? '/' : '\\';
    wchar_t sep = c;
    wchar_t* p = s->mpBegin;
    if (p != s->mpEnd) {
        do {
            if (*p == L'\\' || *p == L'/') {
                *p = sep;
                ++p;
                if (p == s->mpEnd)
                    break;
                while (*p == L'\\' || *p == L'/') {
                    memmove(p, p + 1, (uint32_t)(s->mpEnd - p) * 2);
                    s->mpEnd += -1;
                    if (p == s->mpEnd)
                        break;
                }
            } else {
                ++p;
            }
        } while (p != s->mpEnd);
    }
}

// @ 0x006346e0
bool cPlayModeTokenTranslator::TranslateToken(const wchar_t* token, wstring16* out)
{
    uint32_t h = FNV1_String16(token, 0x811c9dc5, 1);
    switch (h) {
        STR_CASE(0x15277637, movieName)
        STR_CASE_FIX(0x0ebf0c84, mayaExportPath)
        NUM_CASE(0x17629ad3, photoCount)
        NUM_CASE(0x1a6ef8ca, pageCurrent)
        NUM_CASE(0x1868fd54, bgPageCurrent)
        STR_CASE(0x227b55d7, mDayOfMonth)
        STR_CASE(0x248b7480, videoURL)
        NUM_CASE(0x3c5de426, animPageCurrent)
        STR_CASE(0x3fbf8399, mYear)
        STR_CASE(0x4dfeeba0, mayaExportName)
        STR_CASE(0x54798e40, mMonth)
        STR_CASE_FIX(0x5ae2d414, mUnused5c)
        NUM_CASE(0x7e083aa8, pageCount)
        STR_CASE(0x822d5473, statusMessage)
        STR_CASE(0x86110de6, mUnused54)
        NUM_CASE(0x8cdec7e6, bgPageCount)
        STR_CASE(0x8f2d29e5, movieNamePrefix)
        STR_CASE_FIX(0xaab49c2a, moviePathname)
        STR_CASE(0xd38ccf35, mTime)
        STR_CASE_FIX(0xd3f585c1, gifName)
        NUM_CASE(0xe6202d34, animPageCount)
        NUM_CASE(0xfa795731, photoCurrent)
    }
    return false;
}
