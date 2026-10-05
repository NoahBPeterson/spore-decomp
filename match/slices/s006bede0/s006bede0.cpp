// Slice s006bede0 — PFIndexModifiable index/record methods + PFHoleTable rbtree (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "../s006bc1b0/s006bc1b0.h"

// ---------------------------------------------------------------------------
// @ 0x006bef70
void PFHoleTable::FUN_006bef70(uint32 a, uint32 b)
{
    // TODO(partial): rbtree insert/erase of a hole record.
}

// @ 0x006bf5a0
void PFHoleTable::FUN_006bf5a0()
{
    uint32* a = (uint32*)this;
    a[0] = 0xffffffff;
    a[1] = 0xffffffff;
    uint32* p = a + 3;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[0] = (uint32)p;
    a[4] = (uint32)p;
    a[5] = 0;
    *((uint8*)a + 0x18) = 0;
    a[7] = 0;
}

// @ 0x006bfc50
int64_t PFHoleTable::FUN_006bfc50(uint32 a, uint32 b)
{
    // TODO(partial): find largest hole fitting (size, offset).
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bede0
bool PFIndexModifiable::CheckFilesInRange(uint32 begin, uint32 end)
{
    // TODO(partial): iterate the record map testing each chunk range.
    return false;
}

// @ 0x006beeb0
bool PFIndexModifiable::CheckFilesInSizeRange(uint32 begin, uint32 size)
{
    // TODO(partial): iterate the record map testing each chunk size.
    return false;
}

// @ 0x006bf4e0
void* PFIndexModifiable::GetFileInfo(const Key* key)
{
    // TODO(partial): hashtable find + return &entry.info.
    return 0;
}

// @ 0x006bf520
bool PFIndexModifiable::RemoveFile(const Key* key, void* out)
{
    // TODO(partial): hashtable find + erase.
    return false;
}

// @ 0x006bfa00
void* PFIndexModifiable::GetFiles(void* dst, void* filter)
{
    // TODO(partial): iterate records matching an IKeyFilter.
    return 0;
}

// @ 0x006bfac0
void* PFIndexModifiable::GetAllFiles(void* dst)
{
    // TODO(partial): append every key to the destination vector.
    return 0;
}

// @ 0x006bfbc0
void* PFIndexModifiable::PutFileInfo(const Key* key, const void* info)
{
    // TODO(partial): insert-or-find then copy the record info.
    return 0;
}

// @ 0x006bf660
bool PFIndexModifiable::Read(void* data, uint32 size, uint32 count, int flag)
{
    // TODO(partial): parse DBPF index records into the map.
    return false;
}

// @ 0x006bf370
void* PFIndexModifiable::PFIndexModifiable_(void* allocator)
{
    // TODO(partial): constructor.
    return this;
}

// ---------------------------------------------------------------------------
// westl template instantiations / free helpers.
// ---------------------------------------------------------------------------
void FUN_006bf030(void* a, void* b);                 // 0x6bf030
void FUN_006bf140(void* a, void* b);                 // 0x6bf140
void FUN_006bf1e0(void* a);                          // 0x6bf1e0
void FUN_006bf240(void* a, void* b);                 // 0x6bf240
void FUN_006bf2c0(void* a, void* b, void* c);        // 0x6bf2c0
void FUN_006bf430(void* a);                          // 0x6bf430
void FUN_006bf5d0(void* a, void* b, void* c, void* d); // 0x6bf5d0
void* FUN_006bf7d0(void* a, void* b);                // 0x6bf7d0
void FUN_006bf8f0(void* a, void* b, void* c, void* d); // 0x6bf8f0
void* FUN_006bfc20(void* a, void* b, void* c);       // 0x6bfc20

// @ 0x006bf030
void FUN_006bf030(void*, void*) {}
// @ 0x006bf140
void FUN_006bf140(void*, void*) {}
// @ 0x006bf1e0
void FUN_006bf1e0(void*) {}
// @ 0x006bf240
void FUN_006bf240(void*, void*) {}
// @ 0x006bf2c0
void FUN_006bf2c0(void*, void*, void*) {}
// @ 0x006bf430
void FUN_006bf430(void*) {}
// @ 0x006bf5d0
void FUN_006bf5d0(void*, void*, void*, void*) {}
// @ 0x006bf7d0
void* FUN_006bf7d0(void*, void*) { return 0; }
// @ 0x006bf8f0
void FUN_006bf8f0(void*, void*, void*, void*) {}
// @ 0x006bfc20
void* FUN_006bfc20(void* a, void*, void*) { return a; }
