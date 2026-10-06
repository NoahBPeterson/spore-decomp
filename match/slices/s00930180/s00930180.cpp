// Spore retail 00930180..00931250  --  EA::IO path utilities.
// Reconstructed from retail disassembly + dev-build PDB names.

#include "types.h"
#include <wchar.h>

typedef unsigned int uint32;

extern "C" {
__declspec(dllimport) wchar_t* _wgetdcwd(int drive, wchar_t* buffer, int maxlen);
__declspec(dllimport) int _getdrive(void);
}

namespace EA {
namespace IO {

// ---- external callees -------------------------------------------------------
void SplitPathPtrs(const wchar_t* path, const wchar_t** pDir, const wchar_t** pName, const wchar_t** pExt);
bool IsFilePathSeparator(wchar_t c);
void GetCurrentWorkingDirectory(wchar_t* buf);          // Directory::

void FullPath(wchar_t* dest, const wchar_t* src, uint32 unused, int mode);
wchar_t* FullPath(wchar_t* dest, const wchar_t* src, const wchar_t* base, int mode);

class FilePath
{
public:
    wchar_t mPath[520];                                 // +0x0, size 0x410

    void SafeReplace(wchar_t* a, wchar_t* b, const wchar_t* c, const wchar_t* d, wchar_t e, wchar_t f);
    void AppendDirectory();
    const wchar_t* GetExtension();
    uint32 GetDirectory(wchar_t* buffer, uint32 maxLen);
    uint32 GetFileName(wchar_t* buffer, uint32 maxLen);
    uint32 GetDriveAndDirectory(wchar_t* buffer, uint32 maxLen);
    void ReplacePathComponent(int param_2, int param_3, const wchar_t* src, bool flag);
    void FUN_00931100(const wchar_t* src, bool flag);
    bool FUN_00930da0(const wchar_t* path);
    wchar_t* FUN_00930f60(const wchar_t* src);
};

// Small helpers that are emitted out-of-line elsewhere in the binary.
void StringPushChar(void* str, wchar_t c);              // 0x00930ed0
void StringResize(void* str, size_t n);                 // 0x009310a0
void* VectorDoInsertValue(void* self, const void* value, uint32 pos); // 0x011e0744

// @ 0x00930180
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

// @ 0x009302b0
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

// @ 0x00930480
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

// @ 0x00930670
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

// @ 0x00930950
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

// @ 0x009309b0
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

// @ 0x00930a30
void FUN_00930a30(const wchar_t* src, wchar_t* dst, wchar_t sep)
{
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
}

// @ 0x00930ab0
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

// @ 0x00930ba0
// Returns the first character in [first,last) that is NOT in [setFirst,setLast).
const wchar_t* FUN_00930ba0(const wchar_t* first, const wchar_t* last,
                             const wchar_t* setFirst, const wchar_t* setLast)
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

// @ 0x00930bf0
const wchar_t* __fastcall FUN_00930bf0(const wchar_t* path)
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(path, &a, &b, &c);
    return b;
}

// @ 0x00930c10
const wchar_t* FilePath::GetExtension()
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(mPath, &a, &b, &c);
    return c;
}

// @ 0x00930c30
uint32 FilePath::GetDirectory(wchar_t* buffer, uint32 maxLen)
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

// @ 0x00930cb0
uint32 FilePath::GetFileName(wchar_t* buffer, uint32 maxLen)
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

// @ 0x00930d20
uint32 FilePath::GetDriveAndDirectory(wchar_t* buffer, uint32 maxLen)
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

// @ 0x00930da0
bool FilePath::FUN_00930da0(const wchar_t* path)
{
    uint32 local_4 = 0;
    FUN_009309b0(mPath, path, (const wchar_t*)&local_4, 4);
    return true;
}

// @ 0x00930dd0
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

// @ 0x00930f60
wchar_t* FilePath::FUN_00930f60(const wchar_t* src)
{
    uint32 local_4;
    mPath[0] = 0;
    local_4 = 0;
    FUN_009309b0(mPath, src, (const wchar_t*)&local_4, 4);
    return mPath;
}

// @ 0x00930f90
void FilePath::AppendDirectory()
{
    const wchar_t* a;
    const wchar_t* b;
    const wchar_t* c;
    SplitPathPtrs(mPath, &a, &b, &c);
    *(wchar_t*)b = 0;
}

// @ 0x00930fc0
void FilePath::ReplacePathComponent(int param_2, int param_3, const wchar_t* src, bool flag)
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

// @ 0x00931100
void FilePath::FUN_00931100(const wchar_t* src, bool flag)
{
    ReplacePathComponent(2, 4, src, flag);
}

// @ 0x00931250
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

} // namespace IO
} // namespace EA
