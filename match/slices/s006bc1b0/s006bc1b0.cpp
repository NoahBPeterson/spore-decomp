// Slice s006bc1b0 — EA::ResourceMan::DatabasePackedFile core (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "s006bc1b0.h"

struct RecordInfo { uint32 f0, f4, f8, fc; uint16 f10; char f12; };

// @ 0x006bc2d0
bool DatabasePackedFile::FUN_006bc2d0(uint64* out, uint32 a, uint32 b)
{
    bool result = false;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) {
        *out = mHoleTable0.FUN_006bfc50(a, b);
        result = true;
    }
    return result;
}

// @ 0x006bc370
bool DatabasePackedFile::FUN_006bc370(uint64* out)
{
    if (mpIndex != 0) {
        *out = ((int64_t(__thiscall*)(void*))(*(void***)mpIndex)[0x14 / 4])(mpIndex);
        return true;
    }
    return false;
}

// @ 0x006bc3a0
bool DatabasePackedFile::FUN_006bc3a0(uint32 flags, float ratio)
{
    field_544 = flags;
    if (ratio >= 0.0f)
        field_548 = ratio;
    return true;
}

// @ 0x006bc3e0
int DatabasePackedFile::FUN_006bc3e0(uint32 a, int n)
{
    if (field_4e8 != 0 && (uint32)(n - 0x32) <= 0xf423ce)
        return 1;
    return 0;
}

// @ 0x006bc870
bool DatabasePackedFile::FUN_006bc870(const char* h)
{
    int64_t fileSize = mFile.FUN_00928fc0();
    bool valid = false;
    if (*(const uint32*)h == 0x46424244 && *(const uint32*)(h + 4) <= 2 &&
        *(const uint32*)(h + 0x24) < 0x7ffffff) {
        uint64 indexOffset = *(const uint64*)(h + 0x38);
        uint64 end = (uint64)*(const uint32*)(h + 0x28) + indexOffset;
        if (indexOffset < (uint64)fileSize && end <= (uint64)fileSize &&
            *(const uint32*)(h + 0x34) != 0)
            valid = true;
    }
    return valid;
}

// @ 0x006bca70
void DatabasePackedFile::FUN_006bca70()
{
    uint64 pos = mFile.FUN_00928fc0();
    uint32 lo = (uint32)pos;
    uint32 hi = (uint32)(pos >> 32);
    ((void(__thiscall*)(void*, int, int, uint32, uint32))(*(void***)mpIndex)[0x40 / 4])
        (mpIndex, 0, 0, lo, hi);
}

// @ 0x006bcd30
bool DatabasePackedFile::FUN_006bcd30()
{
    bool result = false;
    if (mnAccessFlags != 0) {
        while (mapCount != 0) {
            ((void(__thiscall*)(void*, void*))(*(void***)this)[0x3c / 4])
                (this, *(void**)((char*)mapRoot + 0x1c));
        }
        result = true;
    }
    return result;
}

// @ 0x006bc420
char DatabasePackedFile::FUN_006bc420(char p2, void* p3, char p4)
{
    char result = 0;
    if (p2 != 0) {
        void* cur = field_5a4;
        if (cur != 0 && p3 != cur) {
            ((void(__thiscall*)(void*, int, void*, char))(*(void***)this)[0x44 / 4])
                (this, 0, cur, p4);
        }
        if (p3 != 0) {
            if (p4 != 0) {
                field_5a4 = p3;
                result = 1;
            } else {
                result = ((bool(__thiscall*)(void*, int, void*, int))(*(void***)p3)[0x50 / 4])
                    (p3, 1, this, 0);
            }
        }
    } else {
        if (p3 != 0 && p3 != field_5a4)
            return false;
        if (p4 != 0) {
            field_5a4 = 0;
            result = 1;
        } else {
            void* cur = field_5a4;
            result = ((bool(__thiscall*)(void*, int, void*, int))(*(void***)cur)[0x50 / 4])
                (cur, 0, this, 0);
        }
    }
    return result;
}

// @ 0x006bc1b0
void DatabasePackedFile::MakeIndexModifiable()
{
    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    if (mpIndex != 0) {
        if (((bool(__thiscall*)(void*))(*(void***)mpIndex)[1])(mpIndex))
            return;
    }
    PFIndexModifiable* pNew = (PFIndexModifiable*)
        ((void*(__thiscall*)(void*, int))(*(void***)this)[0x7c / 4])(this, 3);
    if (mpIndex != 0) {
        uint32 count = ((uint32(__thiscall*)(void*))(*(void***)mpIndex)[0xc / 4])(mpIndex);
        if (count != 0) {
            void* pData = 0;
            uint32 nSize = 0;
            if (((bool(__thiscall*)(void*, void**, uint32*, uint32, int))(*(void***)mpIndex)[0x38 / 4])
                    (mpIndex, &pData, &nSize, count, 0)) {
                ((bool(__thiscall*)(void*, void*, uint32, uint32, int))(*(void***)pNew)[0x34 / 4])
                    (pNew, pData, nSize, count, 0);
                ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])
                    (mpAllocator, pData, 0);
            }
        }
        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x80 / 4])(this, mpIndex);
    }
    ((void(__thiscall*)(void*))(*(void***)this)[0x88 / 4])(this);
    mpIndex = pNew;
}

// @ 0x006bc310
bool DatabasePackedFile::FUN_006bc310(uint32 p2, uint32 p3, uint32 p4, uint32 p5, char p6)
{
    if ((p2 | p3) != 0 && (p4 | p5) != 0) {
        if ((field_544 & 0x10) != 0 && p6 == 0)
            mHoleTable1.FUN_006bfda0(p2, p3, p4, p5);
        else
            mHoleTable0.FUN_006bfda0(p2, p3, p4, p5);
        field_5a0 = true;
    }
    return true;
}

// @ 0x006bc4d0
bool DatabasePackedFile::FUN_006bc4d0(uint32 desiredAccess, int createDisposition, int bAutoOpen)
{
    char bl = 0;
    if (bAutoOpen != 0) {
        mnAutoOpenAccessFlags = desiredAccess;
        return true;
    }
    if (!mbInitialized || mnAccessFlags != 0)
        goto fail;
    mnAccessFlags = ((desiredAccess & 2) != 0) ? 3 : 1;
    if ((desiredAccess & 2) != 0) {
        if (createDisposition == 6) createDisposition = 4;
    } else {
        if (createDisposition == 6) createDisposition = 3;
    }
    mFile.SetPath(*(const wchar_t**)&mFilePath[0]);
    if (!mFile.FUN_00929470(mnAccessFlags, createDisposition, 1, 2))
        goto fail;
    {
        uint64 pos = mFile.FUN_00928fc0();
        if (((uint32)pos | (uint32)(pos >> 32)) == 0) {
            if ((mnAccessFlags & 2) == 0) { bl = 0; goto close; }
            bl = ((bool(__thiscall*)(void*))(*(void***)this)[0x64 / 4])(this);
            if (!bl) goto close;
        }
    }
    bl = ((bool(__thiscall*)(void*))(*(void***)this)[0x5c / 4])(this);
    if (bl) goto done;
    ((void(__thiscall*)(void*))(*(void***)mpIndex)[0x10 / 4])(mpIndex);
    if (mbEnableWriteOnCorruptFiles != 0 && (mnAccessFlags & 2) != 0) {
        bl = ((bool(__thiscall*)(void*))(*(void***)this)[0x64 / 4])(this);
        if (!bl) goto close;
        ((void(__thiscall*)(void*))(*(void***)this)[0x88 / 4])(this);
        field_4dc = true;
    }
    if (bl) goto done;
close:
    mFile.FUN_00929290();
    if (bl) goto done;
fail:
    mnAccessFlags = 0;
done:
    return bl;
}

// @ 0x006bc5f0
bool DatabasePackedFile::DeleteRecord()
{
    bool result = true;
    EA::Thread::AutoLock lock1(mIndexMutex, &g_mutexParam);
    EA::Thread::AutoLock lock2(mReadWriteMutex, &g_mutexParam);
    if ((mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) &&
        (field_4dc || field_5a0 || field_540)) {
        result = ((bool(__thiscall*)(void*))(*(void***)this)[0x74 / 4])(this);
        if (result) {
            result = ((bool(__thiscall*)(void*))(*(void***)this)[0x68 / 4])(this);
            if (result) {
                result = mFile.FUN_009290c0();
                if (result) {
                    mHoleTable0.FUN_006bff10(&mHoleTable1);
                    ((void(__thiscall*)(void*))(*(void***)mpIndex)[0x3c / 4])(mpIndex);
                }
            }
        }
    }
    return result;
}

// @ 0x006bc6f0
void* DatabasePackedFile::FUN_006bc6f0(uint32 a, uint32 b)
{
    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    void* result;
    if (mnAccessFlags != 0 || FUN_006bc0a0())
        result = ((void*(__thiscall*)(void*, uint32, uint32))(*(void***)mpIndex)[0x1c / 4])
            (mpIndex, a, b);
    else
        result = 0;
    return result;
}

// @ 0x006bc7a0
bool DatabasePackedFile::FUN_006bc7a0()
{
    if (!mFile.FUN_00929900(0, 0, 0))
        return false;
    char buf[0x78];
    operator_new_array(buf, 0, 0x78);
    if (mFile.FUN_00929100(buf, 0x78) == 0)
        return false;
    *(uint32*)&field_510[0]  = *(uint32*)(buf + 0x08);
    *(uint32*)&field_510[1]  = *(uint32*)(buf + 0x0c);
    *(uint32*)&field_510[2]  = *(uint32*)(buf + 0x14);
    field_510[3] = 0;
    *(uint32*)&field_510[4]  = *(uint32*)(buf + 0x18);
    field_510[5] = 0;
    *(uint32*)&field_510[6]  = *(uint32*)(buf + 0x1c);
    *(uint32*)&field_510[8]  = *(uint32*)(buf + 0x34);
    *(uint32*)&field_510[9]  = *(uint32*)(buf + 0x38);
    *(uint32*)&field_510[10] = *(uint32*)(buf + 0x20);
    *(uint32*)&field_510[11] = *(uint32*)(buf + 0x24);
    return ((bool(__thiscall*)(void*, void*))(*(void***)this)[0x6c / 4])(this, buf);
}

// @ 0x006bc8e0
void DatabasePackedFile::FUN_006bc8e0()
{
    operator_new_array(&field_510[0], 0, 0x30);
    field_510[0] = field_4e0;
    field_510[1] = field_4e4;
    for (int i = 2; i < 12; ++i) field_510[i] = 0;
    field_540 = true;
    if (((bool(__thiscall*)(void*))(*(void***)this)[0x68 / 4])(this)) {
        mFile.FUN_009297a0(0x78, 0);
    }
}

// @ 0x006bc970
bool DatabasePackedFile::FUN_006bc970()
{
    if ((mnAccessFlags & 2) == 0)
        return false;
    if (mFile.FUN_00928f70() == -2)
        return false;
    if (!field_540)
        return true;
    if (!mFile.FUN_00929900(0, 0, 0))
        return false;
    PFHeader h;
    operator_new_array(&h, 0, 0x78);
    h.magic = 0x46424244;
    h.major = 2;
    h.minor = 0;
    h.userMajor = field_4e0;
    h.userMinor = field_4e4;
    h.flags = 0;
    h.created = 0;
    h.modified = 0;
    h.indexCount = field_510[10];
    h.indexMajor = 3;
    h.indexSize = field_510[7];
    h.indexOffset = field_510[6];
    h.holeCount = field_510[8];
    h.holeOffset = field_510[9];
    h.holeSize = field_510[11];
    h.indexMinor = 0;
    h.indexOffset2 = 0;
    if (!mFile.FUN_00929a70(&h, 0x78))
        return false;
    field_540 = false;
    return true;
}

// @ 0x006bca90
bool DatabasePackedFile::ReadFileSpan(uint32 a, uint32 b, uint32 c, uint32 d)
{
    EA::Thread::AutoLock lock(mReadWriteMutex, &g_mutexParam);
    if (mnAccessFlags == 0)
        return false;
    if (!mFile.FUN_00929900(b, c, 0))
        return false;
    return mFile.FUN_00929100((const void*)a, d) != -1;
}

// @ 0x006bcb50
bool DatabasePackedFile::FUN_006bcb50(uint32 a, uint32 b, uint32 c, uint32 d)
{
    EA::Thread::AutoLock lock(mReadWriteMutex, &g_mutexParam);
    if (mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) {
        if (mFile.FUN_00929900(b, c, 0))
            return mFile.FUN_00929a70((const void*)a, d);
    }
    return false;
}

// @ 0x006bcc10
bool DatabasePackedFile::DecompressData(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e)
{
    CompressionRefpack refpack;
    refpack.field_c = 0;
    if (!refpack.IsValidHeader((const void*)a, b))
        return false;
    int n = refpack.Decompress((const void*)a, b, 0, 0, 1);
    if (n == (int)c) {
        if (b != 0 && n != 0) {
            if (refpack.Decompress((const void*)a, b, (void*)e, d, 1) == 0)
                return false;
        }
        return true;
    }
    return false;
}

// @ 0x006bccb0
bool DatabasePackedFile::DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 name)
{
    bool result = false;
    if (b != 0 || c != 0) {
        void* buf = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
            (mpAllocator, name, "Resource/Raw", 0);
        if (buf != 0) {
            if (ReadFileSpan((uint32)buf, a, b, c)) {
                result = DecompressData((uint32)buf, name, d, c, b);
            }
            ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])(mpAllocator, buf, 0);
        }
    }
    return result;
}

// @ 0x006bcd70
bool DatabasePackedFile::FUN_006bcd70(uint32 key)
{
    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    bool result = false;
    if ((mnAccessFlags & 2) != 0) {
        if (mnAccessFlags == 0) {
            if (!FUN_006bc0a0())
                return false;
        }
        if (((void*(__thiscall*)(void*, uint32))(*(void***)mpIndex)[0x28 / 4])(mpIndex, key) != 0) {
            void* out = 0;
            void** it = ((RBTreeHead*)((char*)this + 0x4f0))->find(&out, &key);
            if (*it == (char*)this + 0x4f4) {
                ((void(__thiscall*)(void*))(*(void***)this)[0x84 / 4])(this);
                RecordInfo ri;
                ri.f0 = 0; ri.f4 = 0; ri.f8 = 0; ri.fc = 0; ri.f10 = 0; ri.f12 = 0;
                if (((bool(__thiscall*)(void*, uint32, RecordInfo*))(*(void***)mpIndex)[0x30 / 4])
                        (mpIndex, key, &ri)) {
                    FUN_006bc310(ri.f0, ri.f4, ri.f8, 0, ri.f12 == 0);
                    field_4dc = true;
                    result = true;
                }
            }
        }
    }
    return result;
}

// @ 0x006bcea0
bool DatabasePackedFile::FUN_006bcea0()
{
    if (mnAccessFlags == 0 || (mnAccessFlags & 2) == 0 || !field_4dc)
        return true;
    uint32 n = ((uint32(__thiscall*)(void*))(*(void***)mpIndex)[0xc / 4])(mpIndex);
    void* pData = 0;
    uint32 nSize = 0;
    if (!((bool(__thiscall*)(void*, void**, uint32*, uint32))(*(void***)mpIndex)[0x38 / 4])
            (mpIndex, &pData, &nSize, n))
        return true;
    uint32 old3c = field_510[11];
    field_540 = true;
    bool result;
    if (n == 0) {
        result = FUN_006bc310(field_510[8], field_510[9], old3c, 0, 0);
        field_510[11] = 0; field_510[9] = 0; field_510[8] = 0; field_510[10] = 0;
        if (result) field_4dc = false;
        return result;
    }
    field_510[10] = n;
    field_510[11] = old3c;
    if (old3c != n || (field_544 & 0x10) != 0) {
        result = FUN_006bc310(field_510[8], field_510[9], old3c, 0, 0);
        if (result) {
            field_510[8] = 0; field_510[9] = 0;
            result = FUN_006bc2d0((uint64*)&field_510[8], field_510[11], 0);
            field_510[8] = 0; field_510[9] = 0;
            if (!result) {
                field_510[10] = 0; field_510[8] = 0; field_510[9] = 0; field_510[11] = 0;
                return result;
            }
        }
    }
    result = FUN_006bcb50(field_510[8], field_510[9], field_510[10], old3c);
    if (!result) {
        if (field_510[8] != 0 || field_510[9] != 0) {
            FUN_006bc310(field_510[8], field_510[9], field_510[11], 0, 0);
            field_510[11] = 0; field_510[9] = 0; field_510[8] = 0; field_510[10] = 0;
            return false;
        }
        if (field_540) return false;
        field_4dc = false;
        return false;
    }
    field_4dc = false;
    return result;
}

// @ 0x006bd070
void DatabasePackedFile::FUN_006bd070()
{
    int64_t pos = mFile.FUN_00928fc0();
    uint32 lo = (uint32)pos;
    uint32 hi = (uint32)(pos >> 32);
    mHoleTable0.FUN_006bef70(lo, hi);
    mHoleTable1.FUN_006bef70(lo, hi);
    if ((field_544 & 2) != 0) {
        mHoleTable0.FUN_006bef70(0, 0);
        mHoleTable0.FUN_006bff90(0, 0, 0x78, 0);
        if ((field_544 & 8) != 0) {
            FUN_006bcb50((uint32)"BUSY", 0, 0, 4);
            field_540 = true;
            field_4dc = true;
            return;
        }
        if (mHoleTable0.FUN_006bff90(field_510[8], field_510[9], field_510[11], 0) &&
            ((bool(__thiscall*)(void*, void*, int, int, uint32))(*(void***)mpIndex)[0x24 / 4])
                (mpIndex, &mHoleTable0, 0x78, 0, lo))
            return;
        mHoleTable0.FUN_006bef70(lo, hi);
        mHoleTable1.FUN_006bef70(lo, hi);
        field_544 &= ~2;
    }
}
