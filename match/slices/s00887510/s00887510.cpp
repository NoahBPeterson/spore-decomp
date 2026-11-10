// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE
// eastl::basic_string<wchar_t>::operator+=(wchar_t), out of line in the EAText module. Its only caller,
// EA::Text::BmpFont::ReadBmpFontInfo (0x00887530), appends the texture file name to
// BmpTextureInfo::mTextureFilePath one character at a time.
#include "types.h"

namespace eastl {

class allocator {
public:
    const char* mpName;
};

template <typename T, typename Allocator = allocator>
class basic_string {
public:
    void push_back(T c);                      // 0x00930ed0
    basic_string& operator+=(T c);

    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
};

// @ 0x00887510
template <typename T, typename Allocator>
basic_string<T, Allocator>& basic_string<T, Allocator>::operator+=(T c)
{
    push_back(c);
    return *this;
}

template class basic_string<wchar_t, allocator>;

}  // namespace eastl
