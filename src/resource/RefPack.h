#pragma once
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace Spore::Resource {

// EA RefPack (QFS) LZ77 decompression as used by DBPF compressed entries.
// Returns std::nullopt on malformed input instead of reading out of bounds.
std::optional<std::vector<uint8_t>> RefPackDecompress(const uint8_t* src, size_t srcSize);

// Size field from the RefPack header, or nullopt if the header is invalid.
std::optional<uint32_t> RefPackDecompressedSize(const uint8_t* src, size_t srcSize);

}  // namespace Spore::Resource
