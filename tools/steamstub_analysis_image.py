#!/usr/bin/env python3
"""Produce a NON-RUNNABLE analysis image of a SteamStub v3.1 x86 protected PE.

The code section is decrypted in place so disassemblers can read it, but the PE
entry point is deliberately left on the DRM stub (which would re-decrypt the
already-plain code and crash). The original entry point is written to a JSON
sidecar for use by the Ghidra import scripts. Output is for local analysis only.
"""
import json, struct, sys
import pefile
from Crypto.Cipher import AES

HDR_SIZE = 0xF0
SIG = 0xC0DEC0DF
FLAG_NO_ENCRYPTION = 0x04

def steam_xor(buf: bytearray, key: int = 0) -> int:
    off = 0
    if key == 0:
        key = struct.unpack_from("<I", buf, 0)[0]
        off = 4
    for x in range(off, len(buf), 4):
        val = struct.unpack_from("<I", buf, x)[0]
        struct.pack_into("<I", buf, x, val ^ key)
        key = val
    return key

def parse_header(h: bytes) -> dict:
    f = {}
    (f["xor_key"], f["signature"], f["image_base"], f["entry_point"], f["bind_offset"],
     _, f["oep"], _, f["payload_size"], f["drmp_off"], f["drmp_size"], f["app_id"],
     f["flags"], f["bind_vsize"], _, f["code_va"], f["code_raw_size"]) = \
        struct.unpack_from("<IIQQIIQIIIIIIIIQQ", h, 0)
    o = struct.calcsize("<IIQQIIQIIIIIIIIQQ")
    f["aes_key"], f["aes_iv"], f["stolen"] = h[o:o+0x20], h[o+0x20:o+0x30], h[o+0x30:o+0x40]
    return f

def main(src, dst, meta_path):
    pe = pefile.PE(src)
    data = bytearray(open(src, "rb").read())
    ep_off = pe.get_offset_from_rva(pe.OPTIONAL_HEADER.AddressOfEntryPoint)
    hdr = bytearray(data[ep_off - HDR_SIZE:ep_off])
    steam_xor(hdr)
    h = parse_header(hdr)
    if h["signature"] != SIG:
        sys.exit(f"bad SteamStub signature {h['signature']:#x}")
    if h["flags"] & FLAG_NO_ENCRYPTION:
        sys.exit("code section not encrypted; nothing to do")
    sec = next(s for s in pe.sections
               if s.VirtualAddress <= h["code_va"] < s.VirtualAddress + s.Misc_VirtualSize)
    raw = sec.PointerToRawData
    n = h["code_raw_size"]
    iv = AES.new(h["aes_key"], AES.MODE_ECB).decrypt(h["aes_iv"])
    blob = h["stolen"] + bytes(data[raw:raw + n])
    blob += b"\0" * (-len(blob) % 16)
    plain = AES.new(h["aes_key"], AES.MODE_CBC, iv).decrypt(blob)[:n]
    data[raw:raw + n] = plain
    open(dst, "wb").write(data)
    meta = {k: (v if isinstance(v, int) else v.hex()) for k, v in h.items()
            if k not in ("aes_key", "aes_iv", "stolen", "xor_key")}
    meta["code_section"] = sec.Name.rstrip(b"\0").decode()
    meta["oep_va"] = pe.OPTIONAL_HEADER.ImageBase + h["oep"]
    json.dump(meta, open(meta_path, "w"), indent=2)
    print(json.dumps(meta, indent=2))

if __name__ == "__main__":
    main(*sys.argv[1:4])
