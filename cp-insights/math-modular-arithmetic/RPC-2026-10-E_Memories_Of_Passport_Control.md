# RPC 2026-10 E - Memories of Passport Control

**Type:** Math / Modular Arithmetic
**Rating / Context:** Div 3A / Div 2A (RPC 10 2026)
**Tag:** canonical-coin-change-quotient-remainder

## Key Insight

💡 With stamp denominations `{1, k}`, the minimum number of trips to reach total `s` is the integer quotient plus the remainder: `(s / k) + (s % k)`.

## Pattern Trigger

"Minimum number of operations of size `k` and size `1` to sum to exactly `s`."

## Breakthrough

Any `k` unit stamps can always be merged into one `k`-stamp batch, saving `k - 1` trips, so greedily taking `floor(s / k)` batches is globally optimal.

## Code Spotlight

```cpp
int k, s;
cin >> k >> s;
cout << (s / k) + (s % k) << "\n";
```

## Example

Input: `k = 9, s = 25`
Output: `9`
Why: `25 = 2 * 9 + 7 * 1`, giving `2 + 7 = 9` trips.

---

**Generated:** 2026-11-04
