# File formats (observed; confirm each field against the exe loader before marking verified)

## DBPF (.package) — VERIFIED by corpus (108,918 entries, 70,149 compressed)
- Header 0x60 bytes LE: `DBPF`, major@0x04 (=3), minor@0x08 (=0), index count@0x24,
  index size@0x2C, index minor@0x3C (=3), index offset@0x40.
- Index: u32 flags; bits 0..2 mean type/group/unknown is constant, and each constant
  value follows in that order. Entry = [non-constant of type,group,unknown], instance,
  offset, diskSize|0x80000000, memSize, u16 compressed (0xFFFF = RefPack), u16 committed.
- RefPack: `flags, 0xFB, size(3 or 4 BE; 4 if flags&0x80)`, optional compressed-size field
  if flags&0x01. Standard QFS opcodes.

## .prop (type 0x00B1B104) — OBSERVED
- BE u32 property count. Each record: BE u32 id, BE u16 type, BE u16 flags.
- `flags & 0x30` → array: BE u32 count, BE u32 itemSize, then items.
- Payloads are **little-endian**: key = {instance, type, group} LE, vector floats LE.
  Single (non-array) key / vector3 values take 16 bytes (the last 4 are uninitialized padding).
- string16: u32 length (chars), UTF-16LE chars, no terminator.
- Observed types: 0x13 string16, 0x20 key, 0x31 vector3.
- Group/instance 0x01C7AC81 = file-extension ↔ type-ID map (string16 arrays).

### Exe cross-references (pre-Ghidra, from raw disassembly)
- DBPF header validation @ 0x008D8DB6: magic=='DBPF', major<=3, count<0x7FFFFFF,
  indexOffset<fileSize, indexOffset+indexSize<=fileSize. (Second magic use @ 0x008D8F84.)
- FNV-1 prime 0x01000193 used @ 0x0050E879 in an /Od-looking hash-table lookup
  (bucket = hash & 0x7FFF, 12-byte buckets). Mixed optimization levels per module.
