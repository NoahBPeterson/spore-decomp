#include <ctype.h>

inline bool IsSpaceChar(wchar_t c) {
    return iswctype(c, _SPACE) != 0;
}

struct Lexer_008952f0 {
    const char* mpCurrent;
    const char* mpEnd;
    const char* mpLineStart;
    int mnLine;

    bool CurrentChar(char& c) const {
        if (mpCurrent < mpEnd) {
            c = *mpCurrent;
            return true;
        }
        return false;
    }

    bool Match_008952f0();
};

// @ 0x008952f0
bool Lexer_008952f0::Match_008952f0() {
    bool skipped = false;
    char c;
    for (;;) {
        if (CurrentChar(c) && c == '\r') {
            mpCurrent++;
            if (mpCurrent < mpEnd && *mpCurrent == '\n') {
                mpCurrent++;
            }
            mnLine++;
            mpLineStart = mpCurrent;
            skipped = true;
        } else if (CurrentChar(c) && c == '\n') {
            mpCurrent++;
            mnLine++;
            mpLineStart = mpCurrent;
            skipped = true;
        } else if (CurrentChar(c) && IsSpaceChar(c)) {
            mpCurrent++;
            skipped = true;
        } else {
            break;
        }
    }
    return skipped;
}
