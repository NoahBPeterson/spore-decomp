#pragma once
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace Spore::Resource {

// EA RefPack (QFS) as implemented in SporeApp.exe.
//
// Deliberate divergence: the original decoder (0x0092C340) performs no bounds
// checks. Ours validates every read/write and fails instead; on well-formed
// input the output is identical.

// @ 0x0092C270 — big-endian read of 1..4 bytes.
uint32_t RefPackReadBE(const uint8_t* p, int count);

// @ 0x0092CAD0 — ((b0 << 8 | b1) & 0x1FFF) == 0x10FB. Note this rejects the
// 0x01 "compressed size present" flag even though the decoder could skip it.
bool RefPackIsValidHeader(const uint8_t* src, size_t srcSize);

// @ 0x0092CA60 with dst == nullptr — decompressed size from the header.
std::optional<uint32_t> RefPackDecompressedSize(const uint8_t* src, size_t srcSize);

// @ 0x0092CA60 + 0x0092C340 — validate header, decode. Fails if the output
// would exceed the header's declared size or if input runs out.
std::optional<std::vector<uint8_t>> RefPackDecompress(const uint8_t* src, size_t srcSize);

}  // namespace Spore::Resource
