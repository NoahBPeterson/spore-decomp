// Slice s0090dd30 -- XML/text tokeniser helpers (Scaleform-style reader).
//
//  0x0090dd30  scan text content (dispatch on the per-byte class table)
//  0x0090e1f0  scan one element / markup construct
//  0x0090e490  scan character data up to a terminator
//  0x0090e6a0  scan an attribute value
//  0x0090e890  skip to a matching class byte / check terminator
//
// The original module is whole-program optimised and uses a register ABI:
// EAX holds the cursor, EBX or ECX holds the reader object, and the remaining
// arguments (end, out) are pushed.  The reconstruction below passes every
// parameter explicitly; byte-exact output is therefore not attainable.
//
// Reader layout: +0x04c is a 256-entry byte-class table; +0x14c..+0x16c are
// class continuation callbacks (cdecl, called as cb(reader, cursor)).

typedef unsigned char byte;

struct NormalScanner;

typedef int (__cdecl* ScanCallback)(NormalScanner*, const byte*);

struct NormalScanner {
    byte          m_00[0x4c];
    byte          m_class[256];                 // +0x04c
    ScanCallback  m_14c;                        // +0x14c
    ScanCallback  m_150;                        // +0x150
    ScanCallback  m_154;                        // +0x154
    ScanCallback  m_158;                        // +0x158
    ScanCallback  m_15c;                        // +0x15c
    ScanCallback  m_160;                        // +0x160
    ScanCallback  m_164;                        // +0x164
    ScanCallback  m_168;                        // +0x168
    ScanCallback  m_16c;                        // +0x16c
};

// Other routines of the same module (all share the register ABI).
extern "C" int normal_scanComment(NormalScanner*, const byte* cur,
                                  const byte* end, const byte** out); // 0x0090cb20
extern "C" int normal_scanAtts(NormalScanner*, const byte* cur,
                               const byte* end, const byte** out);    // 0x0090cdd0
extern "C" int FUN_0090d320(NormalScanner*, const byte* cur,
                            const byte* end, const byte** out);       // 0x0090d320
extern "C" int FUN_0090d630(NormalScanner*, const byte* cur,
                            const byte* end, const byte** out);       // 0x0090d630
extern "C" int FUN_0090d830(NormalScanner*, const byte* cur,
                            const byte* end, const byte** out);       // 0x0090d830

static const byte kCDataPrefix[6] = { 'C', 'D', 'A', 'T', 'A', '[' };

// @ 0x0090dd30
int normalScanText(NormalScanner* s, const byte* cur,
                   const byte* end, const byte** out)
{
    const byte* p5;
    const byte* p6;
    int rem;
    int rem8;
    bool flag;

    if (cur == end)
        return -1;

    switch (s->m_class[*cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if (!s->m_158(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (!s->m_15c(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (!s->m_160(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 4;
        break;
    case 0x0f:
        return normal_scanAtts(s, cur, end, out);
    case 0x10: {
        int c2;
        int i;

        ++cur;
        if (cur == end)
            return -1;
        c2 = s->m_class[*cur];
        if (c2 == 0x14) {
            ++cur;
            if (end - cur < 6)
                return -1;
            i = 0;
            do {
                if (*cur != kCDataPrefix[i]) {
                    *out = cur;
                    return 0;
                }
                ++i;
                ++cur;
            } while (i < 6);
            *out = cur;
            return 8;
        }
        if (c2 == 0x1b)
            return normal_scanComment(s, cur, end, out);
        *out = cur;
        return 0;
    }
    case 0x11:
        return FUN_0090d320(s, cur, end, out);
    case 0x16:
    case 0x18:
        ++cur;
        break;
    default:
        *out = cur;
        return 0;
    }

    flag = false;
    if (cur == end)
        return -1;
    rem = (int)(end - cur);

    for (;;) {
        p5 = cur;
        rem8 = rem;
        p6 = cur;

        switch (s->m_class[*cur]) {
        case 5:
            if (rem < 2)
                return -2;
            if (!s->m_14c(s, cur)) {
                *out = cur;
                return 0;
            }
            cur += 2;
            rem -= 2;
            break;
        case 6:
            if (rem < 3)
                return -2;
            if (!s->m_150(s, cur)) {
                *out = cur;
                return 0;
            }
            cur += 3;
            rem -= 3;
            break;
        case 7:
            if (rem < 4)
                return -2;
            if (!s->m_154(s, cur)) {
                *out = cur;
                return 0;
            }
            cur += 4;
            rem -= 4;
            break;
        case 9:
        case 10:
        case 0x15:
            p5 = cur + 1;
            if (p5 == end)
                return -1;
            goto tail_dispatch;
        case 0x0b:
            *out = cur + 1;
            return 2;
        case 0x11:
            p6 = cur + 1;
            if (p6 == end)
                return -1;
            if (*p6 == '>') {
                *out = cur + 2;
                return 4;
            }
            *out = p6;
            return 0;
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            cur = p5 + 1;
            rem = rem8 - 1;
            break;
        case 0x17:
            if (flag) {
                *out = cur;
                return 0;
            }
            p5 = cur + 1;
            rem8 = rem - 1;
            flag = true;
            if (p5 == end)
                return -1;
            switch (s->m_class[*p5]) {
            case 5:
                if (rem8 < 2)
                    return -2;
                if (!s->m_158(s, p5)) {
                    *out = p5;
                    return 0;
                }
                cur = p5 + 2;
                rem = rem8 - 2;
                break;
            case 6:
                if (rem8 < 3)
                    return -2;
                p6 = p5;
                if (!s->m_15c(s, p5)) {
                    *out = p6;
                    return 0;
                }
                cur = p5 + 3;
                rem = rem8 - 3;
                break;
            case 7:
                if (rem8 < 4)
                    return -2;
                if (!s->m_160(s, p5)) {
                    *out = p5;
                    return 0;
                }
                cur = p5 + 4;
                rem = rem8 - 4;
                break;
            case 0x16:
            case 0x18:
                cur = p5 + 1;
                rem = rem8 - 1;
                break;
            case 0x1d:
                *out = p5;
                return 0;
            default:
                *out = p5;
                return 0;
            }
            break;
        default:
            *out = cur;
            return 0;
        }

        if (cur == end)
            return -1;
    }

tail_dispatch:
    for (;;) {
        switch (s->m_class[*p5]) {
        case 5:
            if (end - p5 < 2)
                return -2;
            if (!s->m_158(s, p5)) {
                *out = p5;
                return 0;
            }
            p5 += 2;
            break;
        case 6:
            if (end - p5 < 3)
                return -2;
            if (!s->m_15c(s, p5)) {
                *out = p5;
                return 0;
            }
            p5 += 3;
            break;
        case 7:
            if (end - p5 < 4)
                return -2;
            if (!s->m_160(s, p5)) {
                *out = p5;
                return 0;
            }
            p5 += 4;
            break;
        case 9:
        case 10:
        case 0x15:
            p5 += 1;
            if (p5 == end)
                return -1;
            continue;
        case 0x0b:
            *out = p5 + 1;
            return 2;
        case 0x11:
            p6 = p5 + 1;
            if (p6 == end)
                return -1;
            if (*p6 == '>') {
                *out = p5 + 2;
                return 4;
            }
            *out = p6;
            return 0;
        case 0x16:
        case 0x18:
            p5 += 1;
            break;
        case 0x1d:
            *out = p5;
            return 0;
        default:
            *out = p5;
            return 0;
        }
        return FUN_0090d830(s, p5, end, out);
    }
}

// @ 0x0090e1f0
int normalScanElement(NormalScanner* s, const byte* cur,
                      const byte* end, const byte** out)
{
    const byte* p5;
    const byte* pbA;
    const byte* pbB;
    int rem;

    if (cur == end)
        return -4;

    p5 = cur;
    switch (s->m_class[*cur]) {
    case 0:
    case 1:
    case 8:
        *out = cur;
        return 0;
    case 2:
        return normalScanText(s, cur + 1, end, out);
    case 3:
        return FUN_0090d630(s, cur + 1, end, out);
    case 4:
        p5 = cur + 1;
        if (p5 == end)
            return -5;
        if (*p5 == ']') {
            p5 = cur + 2;
            if (p5 == end)
                return -5;
            if (*p5 == '>') {
                *out = p5;
                return 0;
            }
            p5 = cur + 1;
        }
        break;
    case 5:
        if (end - cur < 2)
            return -2;
        if (s->m_164(s, cur) != 0) {
            *out = cur;
            return 0;
        }
        p5 = cur + 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (s->m_168(s, cur) != 0) {
            *out = cur;
            return 0;
        }
        p5 = cur + 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (s->m_16c(s, cur) != 0) {
            *out = cur;
            return 0;
        }
        p5 = cur + 4;
        break;
    case 9:
        p5 = cur + 1;
        if (p5 == end)
            return -3;
        if (s->m_class[*p5] == 0x0a)
            p5 = cur + 2;
        *out = p5;
        return 7;
    case 10:
        *out = cur + 1;
        return 7;
    default:
        p5 = cur + 1;
        break;
    }

    if (p5 != end) {
        pbA = p5 + 2;
        pbB = p5 + 1;
        rem = (int)(end - p5);
        do {
            switch (s->m_class[*p5]) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 8:
            case 9:
            case 10:
                *out = p5;
                return 6;
            case 4:
                if (pbB == end) {
                    *out = p5;
                    return 6;
                }
                if (*pbB == ']') {
                    if (pbA == end) {
                        *out = p5;
                        return 6;
                    }
                    if (*pbA == '>') {
                        *out = p5 + 2;
                        return 0;
                    }
                }
                p5 += 1;
                rem -= 1;
                pbB += 1;
                pbA += 1;
                break;
            case 5:
                if (rem < 2 || s->m_164(s, p5) != 0) {
                    *out = p5;
                    return 6;
                }
                p5 += 2;
                rem -= 2;
                pbB += 2;
                pbA += 2;
                break;
            case 6:
                if (rem < 3 || s->m_168(s, p5) != 0) {
                    *out = p5;
                    return 6;
                }
                p5 += 3;
                rem -= 3;
                pbB += 3;
                pbA += 3;
                break;
            case 7:
                if (rem < 4 || s->m_16c(s, p5) != 0) {
                    *out = p5;
                    return 6;
                }
                p5 += 4;
                rem -= 4;
                pbB += 4;
                pbA += 4;
                break;
            default:
                p5 += 1;
                rem -= 1;
                pbB += 1;
                pbA += 1;
                break;
            }
        } while (p5 != end);
    }

    *out = p5;
    return 6;
}

// @ 0x0090e490
int normalScanContent(NormalScanner* s, const byte* cur,
                      const byte* end, const byte** out)
{
    int rem;

    if (cur == end)
        return -0x16;

    switch (s->m_class[*cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if (!s->m_158(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (!s->m_15c(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (!s->m_160(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 4;
        break;
    case 9:
    case 10:
    case 0x15:
    case 0x1e:
        *out = cur;
        return 0x16;
    case 0x16:
    case 0x18:
        cur += 1;
        break;
    case 0x1d:
        *out = cur;
        return 0;
    default:
        *out = cur;
        return 0;
    }

    if (cur != end) {
        rem = (int)(end - cur);
        do {
            switch (s->m_class[*cur]) {
            case 5:
                if (rem < 2)
                    return -2;
                if (!s->m_14c(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 2;
                rem -= 2;
                break;
            case 6:
                if (rem < 3)
                    return -2;
                if (!s->m_150(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 3;
                rem -= 3;
                break;
            case 7:
                if (rem < 4)
                    return -2;
                if (!s->m_154(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 4;
                rem -= 4;
                break;
            case 0x12:
                *out = cur + 1;
                return 0x1c;
            case 0x16:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
                cur += 1;
                rem -= 1;
                break;
            case 0x1d:
                *out = cur;
                return 0;
            default:
                *out = cur;
                return 0;
            }
        } while (cur != end);
    }
    return -1;
}

// @ 0x0090e6a0
int normalScanAttValue(NormalScanner* s, const byte* cur,
                       const byte* end, const byte** out)
{
    int rem;

    if (cur == end)
        return -1;

    switch (s->m_class[*cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if (!s->m_158(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (!s->m_15c(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (!s->m_160(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 4;
        break;
    case 0x16:
    case 0x18:
        cur += 1;
        break;
    default:
        *out = cur;
        return 0;
    }

    if (cur != end) {
        rem = (int)(end - cur);
        do {
            switch (s->m_class[*cur]) {
            case 5:
                if (rem < 2)
                    return -2;
                if (!s->m_14c(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 2;
                rem -= 2;
                break;
            case 6:
                if (rem < 3)
                    return -2;
                if (!s->m_150(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 3;
                rem -= 3;
                break;
            case 7:
                if (rem < 4)
                    return -2;
                if (!s->m_154(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 4;
                rem -= 4;
                break;
            case 9:
            case 10:
            case 0x0b:
            case 0x15:
            case 0x1e:
            case 0x20:
            case 0x24:
                *out = cur;
                return 0x14;
            case 0x16:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
                cur += 1;
                rem -= 1;
                break;
            case 0x1d:
                *out = cur;
                return 0;
            default:
                *out = cur;
                return 0;
            }
        } while (cur != end);
    }
    return -0x14;
}

// @ 0x0090e890
int normalScanPast(NormalScanner* s, const byte* cur,
                   const byte* end, unsigned matchClass, const byte** out)
{
    int rem;
    unsigned cls;

    if (cur == end)
        return -1;

    rem = (int)(end - cur);
    do {
        cls = s->m_class[*cur];
        switch (cls) {
        case 0:
        case 1:
        case 8:
            *out = cur;
            return 0;
        case 5:
            if (rem < 2)
                return -2;
            if (s->m_164(s, cur) != 0) {
                *out = cur;
                return 0;
            }
            cur += 2;
            rem -= 2;
            break;
        case 6:
            if (rem < 3)
                return -2;
            if (s->m_168(s, cur) != 0) {
                *out = cur;
                return 0;
            }
            cur += 3;
            rem -= 3;
            break;
        case 7:
            if (rem < 4)
                return -2;
            if (s->m_16c(s, cur) != 0) {
                *out = cur;
                return 0;
            }
            cur += 4;
            rem -= 4;
            break;
        case 0x0c:
        case 0x0d:
            cur += 1;
            rem -= 1;
            if (cls == matchClass) {
                if (cur != end) {
                    *out = cur;
                    switch (s->m_class[*cur]) {
                    case 9:
                    case 10:
                    case 0x0b:
                    case 0x14:
                    case 0x15:
                    case 0x1e:
                        return 0x1b;
                    default:
                        return 0;
                    }
                }
                return -0x1b;
            }
            break;
        default:
            cur += 1;
            rem -= 1;
            break;
        }
    } while (cur != end);

    return -1;
}
