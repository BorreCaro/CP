# RPC 2026-10 J - Shopping

**Type:** Math / Bitwise Greedy
**Rating / Context:** Div 2B (RPC 10 2026)
**Tag:** bitwise-or-subset-sums-carry-invariant

## Key Insight

💡 Bit `i` can be `1` in some subset sum iff the sum of all numbers modulo `2^(i + 1)` is at least `2^i`, which is equivalent to `carry > 0` at bit `i` when accumulating bit counts from LSB to MSB and halving `carry` at each step.

## Pattern Trigger

"Compute the bitwise OR of all possible subset sums for `n <= 10^5` and `sum(a_i) <= 10^18`."

## Breakthrough

If every `b_j = a_j mod 2^(i + 1) < 2^i` and `sum b_j >= 2^i`, adding `b_j` one by one takes steps strictly smaller than the interval width `2^i`, so a prefix sum is guaranteed to land inside `[2^i, 2^(i + 1) - 1]`.

## Code Spotlight

```cpp
unsigned long long ans = 0, carry = 0;
for (int bit = 0; bit < 62; ++bit) {
    for (int j = 0; j < n; ++j) carry += (a[j] >> bit) & 1ULL;
    if (carry > 0) ans |= (1ULL << bit);
    carry >>= 1;
}
```

## Example

Input: `a = [1, 2, 1]`
Output: `7`
Why: Subset sums are `0, 1, 2, 3, 4`, and `1 | 2 | 3 | 4 = 7`.

---

**Generated:** 2026-11-04
