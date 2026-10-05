// Slice s006bd150 — DatabasePackedFile compression/index/close/location helpers (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "../s006bc1b0/s006bc1b0.h"

// @ 0x006bd150
bool DatabasePackedFile::FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags)
{
    bool bWasNull = (*ppMem == 0);
    *pFlags = 0xffff;
    CompressionRefpack refpack;
    if (n - 1 < 39999999) {
        uint32 r = refpack.FUN_0092c9f0(src, n, 0, 0, 1);
        if (bWasNull && r != 0) {
            *pSize = r;
            *ppMem = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
                (mpAllocator, r, "Resource/PackedRecord", 0);
        }
        if (*ppMem != 0) {
            uint32 r2 = refpack.FUN_0092c9f0(src, n, *ppMem, *pSize, (n > 250000) + 1);
            *pSize = r2;
            if (r2 != 0xffffffff)
                return true;
            *pSize = 0;
            if (bWasNull && *ppMem != 0) {
                ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])
                    (mpAllocator, *ppMem, 0);
                *ppMem = 0;
            }
        }
        return false;
    }
    if (bWasNull) {
        *pSize = n;
        void* mem = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
            (mpAllocator, n, "Resource/PackedRecord", 0);
        *ppMem = mem;
        sub_11E0744(mem, src, n);
        return true;
    }
    if (*pSize < n) {
        *pSize = 0;
        return false;
    }
    *pSize = n;
    sub_11E0744(*ppMem, src, n);
    return true;
}

// @ 0x006bd300
void DatabasePackedFile::FUN_006bd300()
{
    // TODO(partial): full destructor (eastl multimap/hole-table/allocator teardown + vtable reset).
}

// @ 0x006bd430
char DatabasePackedFile::FUN_006bd430(char p2)
{
    char bl;
    if (mnAccessFlags == 0) {
        bl = 1;
        goto done;
    }
    if ((mnAccessFlags & 2) == 0) {
        bl = 1;
    } else {
        bl = (char)FUN_006bcd30();
        if (p2 != 0 && bl != 0) {
            ((void(__thiscall*)(void*))(*(void***)this)[0x24 / 4])(this);
            mFile.FUN_00929290();
            mnAccessFlags = 0;
            goto done;
        }
    }
    mFile.FUN_00929290();
    mnAccessFlags = 0;
done:
    ((void(__thiscall*)(void*, void*))(*(void***)this)[0x80 / 4])(this, mpIndex);
    mpIndex = 0;
    mHoleTable0.FUN_006bef70(0, 0);
    mHoleTable1.FUN_006bef70(0, 0);
    return bl;
}

// @ 0x006bd4d0
int DatabasePackedFile::FUN_006bd4d0(Key* key)
{
    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    int count = 0;
    if (mnAccessFlags != 0) {
        void* out = 0;
        void** it = ((RBTreeHead*)((char*)this + 0x4f0))->find(&out, key);
        char* end = (char*)this + 0x4f4;
        for (char* n = *(char**)it;
             n != end && *(uint32*)(n + 0x10) == key->type &&
             *(uint32*)(n + 0x14) == key->group && *(uint32*)(n + 0x18) == key->instance;
             n = (char*)RBTreeIncrement(n)) {
            count++;
        }
    }
    return count;
}

// @ 0x006bd580
bool DatabasePackedFile::FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6)
{
    *p4 = 0;
    *p5 = 0;
    if (!FUN_006bd150((void*)p2, (uint32)p3, p4, p5, (uint16*)&p6))
        return false;
    float a = (float)*p5;
    if ((int)*p5 < 0)
        a += 4294967296.0f;
    float b = (float)p3;
    if (p3 < 0)
        b += 4294967296.0f;
    if (a / b < field_4ec)
        return true;
    if (*p4 != 0)
        ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])(mpAllocator, *p4, 0);
    *p4 = 0;
    *p5 = 0;
    return false;
}

// @ 0x006bd650
bool DatabasePackedFile::SetLocation(const wchar_t* p)
{
    if (mnAccessFlags == 0) {
        const wchar_t* end = p;
        while (*end)
            ++end;
        ((WStringAssign*)((char*)this + 0x20))->assign(p, p + (end - p));
        return true;
    }
    return false;
}

// @ 0x006bd690
bool DatabasePackedFile::FUN_006bd690(void* p2)
{
    // TODO(partial): OpenRecord — open-record multimap lookup, decompress and index update.
    return false;
}

// @ 0x006bdc50
void* DatabasePackedFile::FUN_006bdc50(const wchar_t* p2, int p3)
{
    // TODO(partial): DatabasePackedFile constructor (all fields + embedded objects).
    return this;
}
