# RPC 2026-10 B - Birthday

**Type:** Dynamic Programming / Digit DP
**Rating / Context:** Div 2C (RPC 10 2026)
**Tag:** digit-dp-inside-out-palindrome-modulo

## Key Insight

💡 Build palindromes from the center outward (`L - 2 -> L`) instead of from the outside in: wrapping a core of length `L - 2` and value `X` with digit `d` on both ends transforms `X` into `10 * X + d * (10^(L - 1) + 1)`, sharing one DP table across all lengths `1 <= L <= k` in `O(10 * k * p)`.

## Pattern Trigger

"Count palindromes of length at most `k` divisible by `p` for `k, p <= 2000` (where outside-in DP per length `L` would take `O(k^2 * p)` and TLE)."

## Breakthrough

Maintain two rolling arrays `dp_even[r]` and `dp_odd[r]` that allow leading zeros in inner cores; at each length `L`, add transitions with outer digit `d >= 1` and `nr == 0` to the global answer.

## Code Spotlight

```cpp
int coeff = (pow10[L - 1] + 1) % p;
for (int r = 0; r < p; ++r) {
    if (!prev_dp[r]) continue;
    int base_r = (r * 10) % p;
    for (int d = 0; d <= 9; ++d) {
        int nr = (base_r + d * coeff) % p;
        next_dp[nr] = (next_dp[nr] + prev_dp[r]) % MOD;
        if (d >= 1 && nr == 0) ans = (ans + prev_dp[r]) % MOD;
    }
}
```

## Example

Input: `k = 2, p = 3`
Output: `7`
Why: Valid palindromes `<= 2` digits divisible by 3 are `0, 3, 6, 9, 33, 66, 99`.

---

**Generated:** 2026-11-04
