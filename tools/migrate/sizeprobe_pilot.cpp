#include <stddef.h>
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "SP/cPropertyManager.h"
#include "SP/cDirectPropertyList.h"
typedef eastl::multimap<EA::ResourceMan::Key, EA::ResourceMan::PFRecordBase*, eastl::less<EA::ResourceMan::Key>, EA::Allocator::EASTLCoreAllocator> RecMap;
#define SZ(name, T) char (*name)[sizeof(T)] = 1
#define OF(name, T, m) char (*name)[offsetof(T, m)] = 1
SZ(RecMap_, RecMap); SZ(rb_base_, eastl::rb_base<eastl::less<EA::ResourceMan::Key> >); SZ(CoreAlloc_, EA::Allocator::EASTLCoreAllocator);
SZ(PFRecordRead_, EA::ResourceMan::PFRecordRead); SZ(PFRecordBase_, EA::ResourceMan::PFRecordBase); SZ(MemoryStream_, EA::IO::MemoryStream); SZ(Record_, EA::ResourceMan::Record);
OF(PFRecordRead_mStreamMemory, EA::ResourceMan::PFRecordRead, mStreamMemory); OF(PFRecordRead_mnOpenCount, EA::ResourceMan::PFRecordRead, mnOpenCount);
SZ(DBPF_, EA::ResourceMan::DatabasePackedFile); SZ(cPropertyList_, SP::cPropertyList); SZ(cPropertyManager_, SP::cPropertyManager); SZ(cDirectPropertyList_, SP::cDirectPropertyList);
OF(DBPF_mpStream, EA::ResourceMan::DatabasePackedFile, mpStream); OF(DBPF_mMutex, EA::ResourceMan::DatabasePackedFile, mMutex); OF(DBPF_mpManager, EA::ResourceMan::DatabasePackedFile, mpManager); OF(DBPF_mOpenRecordMultiMap, EA::ResourceMan::DatabasePackedFile, mOpenRecordMultiMap); OF(DBPF_mActiveHoleTable, EA::ResourceMan::DatabasePackedFile, mActiveHoleTable); OF(DBPF_mHeader, EA::ResourceMan::DatabasePackedFile, mHeader);
