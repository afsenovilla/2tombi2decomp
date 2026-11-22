#!/usr/bin/env python3
"""Magic-number division solver: which constant divisor gcc turned into a multiply by MULT.

  python3 -I tools/magicdiv.py MULT [--shift S] [--unsigned]

gcc compiles `x / d` (d constant) as `mult x, MULT; mfhi t; [addu t, t, x;] sra t, t, S; srl u, x, 31; subu
t, t, u` (signed) or `multu; mfhi; srl t, t, S` (unsigned). Give the multiplier the asm loads (lui/ori, in hex)
and the shift (the sra / srl amount after the mfhi); without --shift every shift is listed (d and 2d share the
multiplier, one shift apart). Prints each divisor whose gcc expansion (Hacker's Delight magic numbers, the same
as gcc 2.8's) is exactly this one: write `x / d` (`x % d` adds a multiply back) in the source. Unsigned divisions
that need the add fix-up (`srl 1; addu`) are not covered.
"""
import argparse, random


def sx(v):
    return v - (1 << 32) if v & 0x80000000 else v


def quotient(n, m, s, add, unsigned):
    if unsigned:
        return ((n * m) >> 32) >> s
    hi = (n * sx(m)) >> 32
    if add:
        hi += n
    return (hi >> s) - (n >> 31)


def tdiv(n, d):
    """C division: truncated toward zero."""
    q = abs(n) // abs(d)
    return -q if (n < 0) != (d < 0) else q


def tests(unsigned):
    r = random.Random(1)
    lo, hi = (0, (1 << 32) - 1) if unsigned else (-(1 << 31), (1 << 31) - 1)
    vals = [lo, hi, 0, 1, 2, 3, 100, 1000, 65535, 65536] + [r.randint(lo, hi) for _ in range(3000)]
    if not unsigned:
        vals += [-1, -2, -3, -100, -65536]
    return vals


def magic_signed(d):
    """(multiplier, shift, add x) gcc uses for a signed division by d > 1 (Hacker's Delight 10-1)."""
    two31 = 1 << 31
    anc = two31 - 1 - two31 % d
    p, q1, r1, q2, r2 = 31, two31 // anc, two31 % anc, two31 // d, two31 % d
    while True:
        p += 1
        q1, r1 = 2 * q1, 2 * r1
        if r1 >= anc:
            q1, r1 = q1 + 1, r1 - anc
        q2, r2 = 2 * q2, 2 * r2
        if r2 >= d:
            q2, r2 = q2 + 1, r2 - d
        delta = d - r2
        if not (q1 < delta or (q1 == delta and r1 == 0)):
            break
    m = (q2 + 1) & 0xFFFFFFFF
    return m, p - 32, bool(m & 0x80000000)


def magic_unsigned(d):
    """(multiplier, shift) of an unsigned division by d without the add fix-up (None when it needs one)."""
    for s in range(32):
        m = -(-(1 << (32 + s)) // d)
        if m < (1 << 32) and m * d - (1 << (32 + s)) <= (1 << s):
            return m, s
    return None


def solve(m, shifts, unsigned):
    out = []
    vals = tests(unsigned)
    for s in shifts:
        for add in ((False,) if unsigned else (False, True)):
            meff = m if unsigned else sx(m) + ((1 << 32) if add else 0)
            if meff == 0:
                continue
            d0 = round((1 << (32 + s)) / meff)
            for d in {d0 - 1, d0, d0 + 1}:
                if d in (0, 1, -1):
                    continue
                ok = all(quotient(n, m, s, add, unsigned) == tdiv(n, d) for n in vals)
                if ok:
                    out.append((d, s, add))
    out = sorted(set(out))
    # keep the divisor whose own gcc expansion is exactly this one (x / 3 and x / 6 >> 1 are the same numbers)
    out = [r for r in out if 1 < r[0] < (1 << (32 if unsigned else 31))]
    exact = [r for r in out if ((magic_unsigned(r[0]) == (m, r[1])) if unsigned
                                else magic_signed(r[0]) == (m, r[1], r[2]))]
    return [r + (True,) for r in exact] or [r + (False,) for r in out[:6]]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mult", help="the multiplier, e.g. 0x2AAAAAAB")
    ap.add_argument("--shift", type=int)
    ap.add_argument("--unsigned", action="store_true")
    a = ap.parse_args()
    m = int(a.mult, 0) & 0xFFFFFFFF
    res = solve(m, [a.shift] if a.shift is not None else range(32), a.unsigned)
    if not res:
        print("no divisor found")
    for d, s, add, exact in res:
        print("x / %d   (shift %d%s)%s" % (d, s, ", addu x" if add else "",
                                         "" if exact else "  not gcc's own multiplier for it: check by compiling"))


if __name__ == "__main__":
    main()
