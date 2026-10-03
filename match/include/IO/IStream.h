#pragma once
#include "types.h"

namespace IO {

// Slots are named only where recovered; placeholders keep vtable offsets exact.
class IStream {
 public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0C();
  virtual void slot10();
  virtual void slot14();
  virtual void slot18();
  /* 1Ch */ virtual uint32_t GetSize();
  /* 20h */ virtual void slot20();
  /* 24h */ virtual void slot24();
  /* 28h */ virtual bool SetPosition(int64_t pos);  // called as (pos, 0) by DBPF; exact type TBD
  /* 2Ch */ virtual void slot2C();
  /* 30h */ virtual int Read(void* dst, uint32_t size);
};

}  // namespace IO
