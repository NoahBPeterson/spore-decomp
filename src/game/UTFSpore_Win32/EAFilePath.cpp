// src/game/UTFSpore_Win32/EAFilePath.cpp -- migrated from slice(s) s00930180, s0092f220 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAFilePath.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <wchar.h>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned);
extern "C" void WString_insert2(void*, const void*, unsigned);

// ---- items of slice s0092f220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned);
extern "C" void WString_insert2(void*, const void*, unsigned);
bool EnsureTrailingPathSeparator(unsigned short* path, int length);
int  ConcatenatePathComponents(unsigned short* dst, const unsigned short* c1, const unsigned short* c2);
namespace EA {
namespace IO {
struct FilePath {
    unsigned short mPath[520];
    bool SafeReplace(const unsigned short* a, const unsigned short* b,
                     const unsigned short* c, const unsigned short* d,
                     unsigned short e, unsigned short f);
};
}  // namespace EA::IO
}
using EA::IO::FilePath;
// ---- items of slice s0092f220 end

// ---- items of slice s00930180 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) wchar_t* _wgetdcwd(int drive, wchar_t* buffer, int maxlen);
extern "C" __declspec(dllimport) int _getdrive(void);
typedef unsigned int uint32;
namespace EA {
namespace IO {
void SplitPathPtrs(const wchar_t* path, const wchar_t** pDir, const wchar_t** pName, const wchar_t** pExt);
}
}
namespace EA {
namespace IO {
bool IsFilePathSeparator(wchar_t c);
}
}
namespace EA {
namespace IO {
void GetCurrentWorkingDirectory(wchar_t* buf);          // Directory::
}
}
namespace EA {
namespace IO {
void FullPath(wchar_t* dest, const wchar_t* src, uint32 unused, int mode);
}
}
namespace EA {
namespace IO {
wchar_t* FullPath(wchar_t* dest, const wchar_t* src, const wchar_t* base, int mode);
}
}
namespace EA {
namespace IO {
class FilePath_s0093_0180
{
public:
    wchar_t mPath[520];                                 // +0x0, size 0x410

    void SafeReplace(wchar_t* a, wchar_t* b, const wchar_t* c, const wchar_t* d, wchar_t e, wchar_t f);  // 0x0092fcd0 (EA::IO::FilePath::SafeReplace)
    void AppendDirectory();  // 0x00930f90 (EA::IO::FilePath::AppendDirectory)
    const wchar_t* GetExtension();  // 0x00930c10 (EA::IO::FilePath::GetExtension)
    uint32 GetDirectory(wchar_t* buffer, uint32 maxLen);  // 0x00930c30 (EA::IO::FilePath::GetDirectory)
    uint32 GetFileName(wchar_t* buffer, uint32 maxLen);  // 0x00930cb0 (EA::IO::FilePath::GetFileName)
    uint32 GetDriveAndDirectory(wchar_t* buffer, uint32 maxLen);  // 0x00930d20 (EA::IO::FilePath::GetDriveAndDirectory)
    void ReplacePathComponent(int param_2, int param_3, const wchar_t* src, bool flag);  // 0x00930fc0 (EA::IO::FilePath::ReplacePathComponent)
    void FUN_00931100(const wchar_t* src, bool flag);
    bool FUN_00930da0(const wchar_t* path);
    wchar_t* FUN_00930f60(const wchar_t* src);
};
}
}
namespace EA {
namespace IO {
void* VectorDoInsertValue(void* self, const void* value, uint32 pos); // 0x011e0744
}
}
// ---- items of slice s00930180 end

// @ 0x0092fcd0
bool EA::IO::FilePath::SafeReplace(const unsigned short* arg0, const unsigned short* arg1, const unsigned short* arg2, const unsigned short* arg3, unsigned short ch0, unsigned short ch1)
{
    if (arg1 == 0) {
        const unsigned short* p = arg0;
        while (*p++) {}
        arg1 = arg0 + ((p - (arg0 + 1)));
    }
    if (arg3 == 0) {
        const unsigned short* p = arg2;
        while (*p++) {}
        arg3 = arg2 + ((p - (arg2 + 1)));
    }
    int n2 = (int)(arg3 - arg2);
    const unsigned short* p1 = arg1;
    while (*p1++) {}
    int n1 = (int)(p1 - (arg1 + 1));
    if (n2 != 0) {
        if (*arg2 == ch0) ch0 = 0;
        if (arg3[-1] == ch1) ch1 = 0;
    }
    unsigned extra = (ch0 != 0) ? 1 : 0;
    if (ch1 != 0) extra++;
    int base = (int)((arg0 - mPath) ) ;
    if ((int)(extra + n1 + base + 1 + n2) > 0x208) return false;
    unsigned short* dst = (unsigned short*)arg0 + extra + n2;
    memmove(dst, arg1, n1 * 2 + 2);
    if (ch0) { *(unsigned short*)arg0 = ch0; arg0++; }
    extern void WString_insert2(void*, const void*, unsigned);
    WString_insert2((void*)&arg0, arg2, n2 * 2);
    if (ch1) dst[-1] = ch1;
    return true;
}


// @ 0x0092fe00
bool EnsureTrailingPathSeparator(unsigned short* path, int length)
{
    if (length == -1) {
        unsigned short* p = path;
        while (*p++) {}
        length = (int)(p - (path + 1));
    }
    if (length != 0) {
        unsigned int c = path[length - 1];
        if (c == '\\' || c == '/' || c == ':') return false;
    }
    path[length] = '\\';
    path[length + 1] = 0;
    return true;
}


// @ 0x0092fe60
int ConcatenatePathComponents(unsigned short* dst, const unsigned short* c1, const unsigned short* c2)
{
    unsigned short* p = dst;
    if (c1) {
        const unsigned short* start = c1;
        while ((*p++ = *c1++) != 0) {}
        --p;
        if (*start != 0) {
            unsigned int c = p[-1];
            if (p == dst || (c != '\\' && c != '/' && c != ':')) *p++ = '\\';
        }
    }
    if (c2) {
        while ((*p++ = *c2++) != 0) {}
        return (int)(--p - dst);
    }
    *p = 0;
    return (int)(p - dst);
}


// @ 0x0092fee0
int StripPathComponent(unsigned short* path, int component)
{
    unsigned short* p = path;
    switch (component) {
    case 1: {
        unsigned short* last = path;
        while (*p) {
            if (*p == '\\' || *p == '/' || *p == ':') {
                if (*p == ':' && (p[1] == 0 || ((p[1] == '\\' || p[1] == '/' || p[1] == ':') && p[2] == 0))) {
                    *path = 0;
                    return 0;
                }
            }
            ++p;
        }
        (void)last;
        return (int)(p - path);
    }
    case 2: case 4: case 8: case 0x10: {
        unsigned short* prev = path - 1;
        unsigned short* cur = path;
        unsigned short* cut = prev;
        while (*cur) {
            unsigned short c = *cur;
            if (c == '\\' || c == '/' || c == ':') {
                cut = cur;
            }
            prev = cur;
            ++cur;
        }
        if (component < 8 && prev + 1 == cur) cut = prev;
        cut[1] = 0;
        return (int)(cut + 1 - path);
    }
    case 0x20: {
        unsigned short* prev = path - 1;
        unsigned short* cur = path;
        unsigned short* cut = prev;
        while (*cur) {
            if (*cur == '\\' || *cur == '/' || *cur == ':') {
                cur++;
                continue;
            }
            if (*cur == '.') cut = cur;
            prev = cur;
            ++cur;
        }
        if (prev < cut) { *cut = 0; prev = cut; }
        return (int)(prev - path);
    }
    default: {
        unsigned short* start = path + 1;
        while (*path++) {}
        return (int)(path - start);
    }
    }
}


// @ 0x00930070
void SplitPathPtrs(unsigned short* path, void** pFile, void** pExt, void** pEnd)
{
    unsigned short* firstSep = 0;
    unsigned short* lastSep = 0;
    unsigned short* dot = 0;
    unsigned short* p = path;
    while (*p) {
        if (*p == '\\' || *p == '/' || *p == ':') {
            if (firstSep == 0) firstSep = p;
            lastSep = p;
            dot = 0;
        }
        if (*p == '.') dot = p;
        ++p;
    }
    *pFile = path;
    if (path[0] == '\\' && path[1] == '\\') {
        p = path + 2;
        int seps = 0;
        while (*p) {
            if (*p == '\\') {
                if (++seps == 2) break;
            } else if (*p == '/' || *p == ':') {
                break;
            }
            ++p;
        }
        *pFile = p;
        if (lastSep && lastSep < p) lastSep = *p ? p : 0;
        if (dot && dot < p) dot = 0;
    } else if (firstSep && *firstSep == ':') {
        *pFile = firstSep + 1;
    }
    *pExt = *pFile;
    if (lastSep) *pExt = lastSep + 1;
    if (dot) {
        *pEnd = dot;
        return;
    }
    unsigned short* e = (unsigned short*)*pFile;
    while (*e) ++e;
    *pEnd = e;
}

// @ 0x00930180
namespace EA { namespace IO {
void SplitPath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* filename, wchar_t* ext)
{
    const wchar_t* pDir;
    const wchar_t* pName;
    const wchar_t* pExt;
    SplitPathPtrs(path, &pDir, &pName, &pExt);

    size_t nDrive = 0xff;
    size_t d = ((int)pDir - (int)path) >> 1;
    if (d <= 0xff) nDrive = d;

    size_t nDir = 0xff;
    d = ((int)pName - (int)pDir) >> 1;
    if (d <= 0xff) nDir = d;

    size_t nName = 0xff;
    d = ((int)pExt - (int)pName) >> 1;
    if (d <= 0xff) nName = d;

    size_t nExt = 0xff;
    if (wcslen(pExt) < 0x100) nExt = wcslen(pExt);

    if (drive != 0) {
        wcsncpy(drive, path, nDrive);
        drive[nDrive] = 0;
    }
    if (dir != 0) {
        wcsncpy(dir, pDir, nDir);
        dir[nDir] = 0;
    }
    if (filename != 0) {
        wcsncpy(filename, pName, nName);
        filename[nName] = 0;
    }
    if (ext != 0) {
        wcsncpy(ext, pExt, nExt);
        ext[nExt] = 0;
    }
}
}}  // namespace EA::IO

// @ 0x009302b0
namespace EA { namespace IO {
uint32 SplitDirectory(const wchar_t* path, wchar_t* out, uint32 maxCount)
{
    size_t len = wcslen(path);
    if (len == 0)
        return 0;

    int sVar5 = (int)len - 1;
    wchar_t last = path[sVar5];
    uint32 count = 0;
    uint32 local_10 = 0;
    size_t _Count = len - 1;
    size_t _Count_00 = _Count;
    if (last == L'\\' || last == L'/' || last == L':')
        sVar5 = (int)len - 2;

    if (out == 0)
        maxCount = 0xffffffff;

    if (sVar5 >= 0) {
        int local_8 = 0;
        uint32 local_c = 1;
        wchar_t* pwVar3 = out;
        wchar_t* local_4 = out;
        do {
            _Count = _Count_00;
            if (maxCount <= local_c)
                break;
            wchar_t wVar1 = path[sVar5];
            if (wVar1 == L'\\' || wVar1 == L'/' || wVar1 == L':') {
                _Count_00 = _Count_00 - (size_t)sVar5;
                _Count = (size_t)sVar5;
                if (out != 0)
                    wcsncpy(pwVar3, path + sVar5 + 1, _Count_00);
LAB_00930361:
                if (_Count_00 - 1 > 0xfe)
                    return 0;
                if (out != 0) {
                    wVar1 = out[local_8 + _Count_00 - 1];
                    pwVar3 = out + local_8 + _Count_00;
                    if (wVar1 == L'\\' || wVar1 == L'/' || wVar1 == L':') {
                        *pwVar3 = 0;
                    } else {
                        *pwVar3 = L'\\';
                        pwVar3[1] = 0;
                    }
                }
                local_c = local_c + 1;
                count = local_10 + 1;
                pwVar3 = local_4 + 0x104;
                local_8 = local_8 + 0x104;
                local_10 = count;
                local_4 = pwVar3;
            } else if (sVar5 == 0) {
                if (out != 0)
                    wcsncpy(pwVar3, path, _Count_00);
                _Count = 0;
                goto LAB_00930361;
            }
            sVar5 = sVar5 - 1;
            _Count_00 = _Count;
        } while (sVar5 >= 0);
    }

    if (_Count != 0 && count < maxCount) {
        if (_Count > 0xff)
            return 0;
        if (out != 0) {
            wcsncpy(out + count * 0x104, path, _Count);
            int iVar4 = (int)local_10 * 0x104 + (int)_Count;
            wchar_t* pwVar3 = out + iVar4;
            if (IsFilePathSeparator(out[iVar4 - 1])) {
                *pwVar3 = 0;
                return local_10 + 1;
            }
            *pwVar3 = L'\\';
            pwVar3[1] = 0;
        }
        count = local_10 + 1;
    }
    return count;
}
}}  // namespace EA::IO

// @ 0x00930480
namespace EA { namespace IO {
void FullPath(wchar_t* dest, const wchar_t* src, uint32 unused, int mode)
{
    wchar_t buf[522];
    size_t n;
    buf[0] = 0;

    if ((uint32)(mode - 3) > 2) {
        GetCurrentWorkingDirectory(buf);
        n = wcslen(buf);
        if (!IsFilePathSeparator(buf[n - 1])) {
            buf[n] = L'\\';
            buf[n + 1] = 0;
        }
        goto LAB_00930645;
    }

    {
        wchar_t c0 = src[0];
        if (c0 == 0 || src[1] == 0)
            goto LAB_00930537;
        if (c0 == L'\\' || c0 == L'/' || c0 == L':') {
            if (IsFilePathSeparator(src[1])) {
                buf[0] = L'\\';
                buf[1] = L'\\';
                buf[2] = 0;
                src += 2;
                goto LAB_00930645;
            }
        }
        if (src[1] != L':')
            goto LAB_00930537;
        {
            wchar_t w = (wchar_t)towlower(c0);
            if ((unsigned)(w - 0x61) > 0x19)
                goto LAB_00930537;
            w = (wchar_t)towlower(src[0]);
            {
                uint32 drive = (uint32)(w - 0x61);
                wchar_t c1 = src[2];
                src += 2;
                if ((c1 == L'\\' || c1 == L'/' || c1 == L':') && (int)drive >= 0) {
                    if (drive < 0x1a)
                        buf[0] = (wchar_t)(drive + L'a');
                    else
                        buf[0] = L'c';
                    buf[1] = L':';
                    buf[2] = L'\\';
                    buf[3] = 0;
                    src += 1;
                    goto LAB_00930645;
                }
                if (c1 == L'\\' || c1 == L'/' || c1 == L':') {
                    if (drive < 0x1a)
                        buf[0] = (wchar_t)(drive + L'a');
                    else
                        buf[0] = L'c';
                    buf[1] = L':';
                    buf[2] = L'\\';
                    buf[3] = 0;
                    src += 1;
                    goto LAB_00930645;
                }
                // _wgetdcwd(drive+1, buf, 0x209)
                if (_wgetdcwd((int)drive + 1, buf, 0x209) == 0)
                    GetCurrentWorkingDirectory(buf);
                n = wcslen(buf);
                if (!IsFilePathSeparator(buf[n - 1])) {
                    buf[n] = L'\\';
                    buf[n + 1] = 0;
                }
                goto LAB_00930645;
            }
        }
LAB_00930537:
        {
            int drive = _getdrive() - 1;
            wchar_t c1 = src[0];
            if ((c1 == L'\\' || c1 == L'/' || c1 == L':') && drive >= 0) {
                if ((unsigned)drive < 0x1a)
                    buf[0] = (wchar_t)(drive + L'a');
                else
                    buf[0] = L'c';
                buf[1] = L':';
                buf[2] = L'\\';
                buf[3] = 0;
                src += 1;
                goto LAB_00930645;
            }
            if (_wgetdcwd(drive + 1, buf, 0x209) == 0)
                GetCurrentWorkingDirectory(buf);
            n = wcslen(buf);
            if (!IsFilePathSeparator(buf[n - 1])) {
                buf[n] = L'\\';
                buf[n + 1] = 0;
            }
        }
    }

LAB_00930645:
    FullPath(dest, src, buf, mode);
}
}}  // namespace EA::IO

// @ 0x00930670
namespace EA { namespace IO {
wchar_t* FullPath(wchar_t* dest, const wchar_t* src, const wchar_t* base, int mode)
{
    if (src == 0)
        return 0;
    if (base == 0)
        return (wchar_t*)FullPath(dest, (const wchar_t*)src, (const wchar_t*)0x104, mode);

    const wchar_t* pEnd = src + wcslen(src);
    const wchar_t* pSeek = src;
    wchar_t* out = dest;

    const wchar_t* b0 = base;
    const wchar_t* b1 = base;
    const wchar_t* b2 = base;
    if (pSeek == pEnd) {
        SplitPathPtrs((const wchar_t*)base, &b0, &b1, &b2);
        const wchar_t* q = b0;
        if (*b0 == L'\\' || *b0 == L'/' || *b0 == L':')
            q = b0 + 1;
        pSeek = q;
        if (base == q) {
            goto LAB_0093076c;
        }
    }

    do {
        wchar_t* prev = out;
        wchar_t c = *b2++;
        if (c == L'/')
            c = L'\\';
        if (prev == dest + 0x104) {
            dest[0x103] = 0;
            return 0;
        }
        *prev = c;
        out = prev + 1;
    } while (b2 != pSeek);

    if (!IsFilePathSeparator(out[-1])) {
        if (out == dest + 0x104) {
            dest[0x103] = 0;
            return 0;
        }
        *out = L'\\';
        out = out + 1;
    }

LAB_0093076c:
    if (out == dest + 0x104) {
LAB_00930937:
        dest[0x103] = 0;
        return 0;
    }
    *out = 0;

    // now append src with . and .. processing
    {
        const wchar_t* dirStart;
        const wchar_t* nameStart;
        const wchar_t* extStart;
        SplitPathPtrs(dest, &dirStart, &nameStart, &extStart);
        bool bVar11 = (dirStart == dest);
        const wchar_t* cur = dirStart;
        if (*cur == L'\\' || *cur == L'/' || *cur == L':')
            cur = cur + 1;
        bool skip = false;
        char atStart = 1;

        do {
            wchar_t c = *pSeek++;
            if (c == L'\\' || c == L'/' || c == L':') {
                if (atStart == 0) {
                    atStart = 1;
                    if (c == L'/')
                        c = L'\\';
                    if (out == dest + 0x104)
                        goto LAB_00930937;
                    *out++ = c;
                }
                continue;
            }
            if (c == L'.') {
                if (atStart != 0) {
                    wchar_t nx = *pSeek;
                    if (nx == 0 || IsFilePathSeparator(nx)) {
                        if (dirStart < out && IsFilePathSeparator(out[-1]))
                            continue;
                    } else if (nx == L'.' &&
                               ((pSeek[1] == 0 || IsFilePathSeparator(pSeek[1])) && !skip)) {
                        const wchar_t* ps = out;
                        if (dirStart < out) {
                            int i = 0;
                            do {
                                if (IsFilePathSeparator(ps[-1]) && (++i > 1))
                                    break;
                                ps--;
                            } while (dirStart < ps);
                        }
                        if (!((*ps == L'.' && ps[1] == L'.') &&
                              !(ps[2] != 0 && !IsFilePathSeparator(ps[2])))) {
                            if (ps == dirStart)
                                skip = bVar11;
                            out = (wchar_t*)ps;
                            continue;   // loop back with pSeek already advanced
                        }
                    }
                }
                skip = false;
            } else {
                skip = false;
            }
            atStart = 0;
            if (out == dest + 0x104)
                goto LAB_00930937;
            *out++ = c;
            if (c == 0)
                return dest;
        } while (true);
    }
}
}}  // namespace EA::IO

// @ 0x00930950
namespace EA { namespace IO {
bool FUN_00930950(const wchar_t* path, int len)
{
    if ((uint32)(len - 3) <= 2) {
        int iVar1 = iswctype(path[0], 0x103);
        if (((iVar1 != 0) && path[1] == L':' && path[2] == L'\\') ||
            (path[0] == L'\\' && path[1] == L'\\'))
            return true;
    } else if (path[0] == L'\\') {
        return true;
    }
    return false;
}
}}  // namespace EA::IO

// @ 0x009309b0
namespace EA { namespace IO {
wchar_t* FUN_009309b0(wchar_t* dest, const wchar_t* src, const wchar_t* arg3, int arg4)
{
    if (FUN_00930950(src, 4)) {
        if (wcslen(src) < 0x103) {
            wchar_t* d = dest;
            while ((*d++ = *src++) != 0)
                ;
            return dest;
        }
        return 0;
    }
    return FullPath(dest, src, arg3, arg4);
}
}}  // namespace EA::IO

// @ 0x00930a30
namespace EA { namespace IO {
wchar_t* FUN_00930a30(const wchar_t* src, wchar_t* dst, wchar_t sep)
{
    wchar_t* ret = dst;
    const wchar_t* p = src;
    if (*p != 0) {
        do {
            wchar_t c = *p;
            if (((c == L'\\' || c == L'/' || c == L':') && c != L':'))
                *dst = sep;
            else
                *dst = c;
            p++;
            dst++;
        } while (*p != 0);
        if (p != src) {
            wchar_t last = p[-1];
            if (last == L'\\' || last == L'/' || last == L':')
                goto LAB_00930a9d;
        }
    }
    *dst = sep;
    dst++;
LAB_00930a9d:
    *dst = 0;
    return ret;
}
}}  // namespace EA::IO

// @ 0x00930ab0
namespace EA { namespace IO {
bool IsSubdirectory(const wchar_t* parent, const wchar_t* child, int mode)
{
    bool bVar1 = true;
    const wchar_t* pwVar5 = parent;
    wchar_t wVar4 = parent[0];
    if (wVar4 != 0) {
        if (mode == 2 || mode == 3 || mode == 4 || (bVar1 = true, mode == 5))
            bVar1 = false;
        do {
            pwVar5 = parent;
            wchar_t wVar3 = child[0];
            if (wVar3 == 0)
                return false;
            if (wVar4 == L'\\' || wVar4 == L'/' || wVar4 == L':') {
                if (wVar3 != L'\\' && wVar3 != L'/' && wVar3 != L':')
                    return false;
            } else if (bVar1) {
                if (wVar3 != wVar4)
                    return false;
            } else {
                if ((wchar_t)towlower(wVar3) != (wchar_t)towlower(wVar4))
                    return false;
            }
            wVar4 = pwVar5[1];
            child = child + 1;
            parent = pwVar5 + 1;
        } while (wVar4 != 0);

        wVar4 = *pwVar5;
        if (((wVar4 != L'\\' && wVar4 != L'/' && wVar4 != L':')) &&
            (*child != 0 && !IsFilePathSeparator(*child)))
            return false;
    }
    return true;
}
}}  // namespace EA::IO

// @ 0x00930ba0
namespace EA { namespace IO {
const wchar_t* FUN_00930ba0(const wchar_t* first, const wchar_t* last, const wchar_t* setFirst, const wchar_t* setLast)
{
    if (first == last)
        return last;
    if (setFirst == setLast)
        return first;
    do {
        wchar_t c = *first;
        const wchar_t* ps = setFirst;
        while (c != *ps) {
            ps++;
            if (ps == setLast)
                return first;
        }
        first++;
    } while (first != last);
    return last;
}
}}  // namespace EA::IO

// @ 0x00930bf0
namespace EA { namespace IO {
const wchar_t* __fastcall FUN_00930bf0(const wchar_t* path)
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(path, &a, &b, &c);
    return b;
}
}}  // namespace EA::IO

// @ 0x00930c10
namespace EA { namespace IO {
const wchar_t* FilePath_s0093_0180::GetExtension()
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(mPath, &a, &b, &c);
    return c;
}
}}  // namespace EA::IO

// @ 0x00930c30
namespace EA { namespace IO {
uint32 FilePath_s0093_0180::GetDirectory(wchar_t* buffer, uint32 maxLen)
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(mPath, &a, &b, &c);
    uint32 n = (uint32)(((int)(c != 0 ? c : b + wcslen(b)) - (int)b) >> 1);
    if (n < maxLen) {
        VectorDoInsertValue(buffer, b, n * 2);
        *(wchar_t*)(n * 2 + (int)buffer) = 0;
    }
    return n;
}
}}  // namespace EA::IO

// @ 0x00930cb0
namespace EA { namespace IO {
uint32 FilePath_s0093_0180::GetFileName(wchar_t* buffer, uint32 maxLen)
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(mPath, &a, &b, &c);
    uint32 n = (uint32)wcslen(c);
    if (n < maxLen) {
        VectorDoInsertValue(buffer, c, n * 2);
        *(wchar_t*)(n * 2 + (int)buffer) = 0;
    }
    return n;
}
}}  // namespace EA::IO

// @ 0x00930d20
namespace EA { namespace IO {
uint32 FilePath_s0093_0180::GetDriveAndDirectory(wchar_t* buffer, uint32 maxLen)
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(mPath, &a, &b, &c);
    uint32 n = (uint32)(((int)(b != 0 ? b : mPath + wcslen(mPath)) - (int)mPath) >> 1);
    if (n < maxLen) {
        VectorDoInsertValue(buffer, mPath, n * 2);
        *(wchar_t*)(n * 2 + (int)buffer) = 0;
    }
    return n;
}
}}  // namespace EA::IO

// @ 0x00930da0
namespace EA { namespace IO {
bool FilePath_s0093_0180::FUN_00930da0(const wchar_t* path)
{
    uint32 local_4 = 0;
    FUN_009309b0(mPath, path, (const wchar_t*)&local_4, 4);
    return true;
}
}}  // namespace EA::IO

// @ 0x00930dd0
namespace EA { namespace IO {
void FUN_00930dd0(const wchar_t* path, const wchar_t** outDir, const wchar_t** outName, const wchar_t** outExt)
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(path, &a, &b, &c);
    *outDir = a;
    *outName = b;
    *outExt = c;
}
}}  // namespace EA::IO

// @ 0x00930f60
namespace EA { namespace IO {
wchar_t* FilePath_s0093_0180::FUN_00930f60(const wchar_t* src)
{
    uint32 local_4;
    mPath[0] = 0;
    local_4 = 0;
    FUN_009309b0(mPath, src, (const wchar_t*)&local_4, 4);
    return mPath;
}
}}  // namespace EA::IO

// @ 0x00930f90
namespace EA { namespace IO {
void FilePath_s0093_0180::AppendDirectory()
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(mPath, &a, &b, &c);
    *(wchar_t*)b = 0;
}
}}  // namespace EA::IO

// @ 0x00930fc0
namespace EA { namespace IO {
void FilePath_s0093_0180::ReplacePathComponent(int param_2, int param_3, const wchar_t* src, bool flag)
{
    const wchar_t* comp[4];
    comp[0] = 0; comp[1] = 0; comp[2] = 0; comp[3] = 0;
    const wchar_t* pFVar4 = 0;
    const wchar_t* pFVar5 = 0;

    if (flag) {
        comp[0] = src;
        SplitPathPtrs(src, &comp[1], &comp[2], &comp[3]);
        pFVar4 = comp[param_2];
        pFVar5 = comp[param_3];
    }

    const wchar_t* q0 = 0, *q1 = 0, *q2 = 0, *q3 = 0;
    SplitPathPtrs(mPath, &q0, &q1, &q2);
    q3 = mPath;
    wchar_t uVar3 = 0;
    wchar_t uVar2 = 0;
    if (pFVar5 != pFVar4) {
        if (param_2 == 3)
            uVar3 = L'.';
        if (param_3 == 2)
            uVar2 = L'\\';
    }
    SafeReplace((wchar_t*)q0, (wchar_t*)q1, pFVar4, pFVar5, uVar3, uVar2);
}
}}  // namespace EA::IO

// @ 0x00931100
namespace EA { namespace IO {
void FilePath_s0093_0180::FUN_00931100(const wchar_t* src, bool flag)
{
    ReplacePathComponent(2, 4, src, flag);
}
}}  // namespace EA::IO

// @ 0x00931250
namespace EA { namespace IO {
bool MakeFileNameValid(const wchar_t* src, wchar_t* dst)
{
    wchar_t buf[260];
    buf[0] = 0;
    size_t n = 0;
    for (const wchar_t* p = src; *p; ++p) {
        wchar_t c = *p;
        if (!(c == L'<' || c == L'>' || c == L':' || c == L'\\' || c == L'/' ||
              c == L'"' || c == L'|' || c == L'*' || c == L'?'))
            buf[n++] = c;
    }
    buf[n] = 0;
    if (n > 0x100) {
        n = 0x100;
        buf[n] = 0;
    }
    wchar_t* d = dst;
    const wchar_t* s = buf;
    while ((*d++ = *s++) != 0)
        ;
    return n != 0;
}
}}  // namespace EA::IO
