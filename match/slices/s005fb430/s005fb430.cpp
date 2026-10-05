// Slice s005fb430 - cImportExport retail destructor + UpdateExportThumb, cIDGenerator::CreateKey.
// Flags: /O2 /MD /Gy /TP
#include "../s005fa8d0/s005fa8d0.h"

// A refcounted-buffer vector: freed only when the buffer's header refcount is non-zero.
struct RefVec {
  void* mpBegin;
  ~RefVec() {
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
  }
};

struct IHandlerBase {
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual ~IHandlerBase() {}
};

// Retail cImportExport: same map block as the dev PDB, but 8 string16 members after the
// embedding image. Layout used by the destructor at 0x005fb900.
struct cImportExportRetail : IHandlerBase {
  eastl::NameKeyMap mNameToKeyMap;   // +0x04
  eastl::KeyNameMap mKeyToNameMap;   // +0x24
  uint32_t mnMachineID;              // +0x44
  SP::Thumbnail::GuidKeyMap mGuidToKeyMap;  // +0x48
  SP::Thumbnail::KeyGuidMap mKeyToGuidMap;  // +0x68
  RefVec mVec88;                     // +0x88
  char pad8c[0xe0 - 0x8c];           // +0x8c
  RefVec mVecE0;                     // +0xe0
  char padE4[0x104 - 0xe4];          // +0xe4
  eastl::string16 s104, s114, s124, s134, s144, s154, s164, s174;
  ~cImportExportRetail();

  unsigned char UpdateExportThumb(void* param_2);   // 0x005fb430
};

// @ 0x005fb900
cImportExportRetail::~cImportExportRetail() {}

// @ 0x005fb430
unsigned char cImportExportRetail::UpdateExportThumb(void* param_2)
{
  // Reconstructed (behavioural) form of the multi-step image-update routine.
  (void)param_2;
  return 0;
}

// --- cIDGenerator -----------------------------------------------------------------------
struct cIDGenerator {
  uint32_t mnStartInstance;                       // +0x00
  uint32_t mEntityCounterMap_pad[7];              // +0x04 (eastl::map<int,uint32>)
  uint32_t mTypeCounterMap_pad[7];                // +0x20 (eastl::map<uint32,uint32>)
  uint32_t CreateKey(uint32_t group, uint32_t type);   // 0x005fbb00
};

// @ 0x005fbb00
uint32_t cIDGenerator::CreateKey(uint32_t group, uint32_t type)
{
  // Reconstructed (behavioural) skeleton.
  (void)group;
  (void)type;
  return 0;
}
