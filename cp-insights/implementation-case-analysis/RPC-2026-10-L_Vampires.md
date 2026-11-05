# RPC 2026-10 L - Vampires

**Type:** Implementation / Digit Permutation Validation
**Rating / Context:** Div 3B / Div 2A (RPC 10 2026)
**Tag:** vampire-numbers-string-sorting-parity-guard

## Key Insight

💡 Verify vampire fangs `(n, a, b)` by checking four exact conditions: `len(n) == 2 * len(a)` with `len(a) == len(b)`, `a * b == n`, `!(a % 10 == 0 && b % 10 == 0)`, and `sort(str(n)) == sort(str(a) + str(b))`.

## Pattern Trigger

"Given `n, a, b`, determine if `a` and `b` are valid half-length fangs whose product is `n` and whose digits permute to `n` without both ending in zero."

## Breakthrough

Never test half-length using integer division `len(n) / 2 == len(a)` (which truncates odd `len(n)`); always test `len(n) == 2 * len(a)`.

## Code Spotlight

```cpp
if (n.size() != 2 * a.size() || a.size() != b.size()) return false;
long long vn = stoll(n), va = stoll(a), vb = stoll(b);
if (va * vb != vn || (va % 10 == 0 && vb % 10 == 0)) return false;
string s = a + b;
sort(s.begin(), s.end()); sort(n.begin(), n.end());
return n == s;
```

## Example

Input: `n = 1260, a = 21, b = 60`
Output: `YES`
Why: `21 * 60 = 1260`, lengths are `4, 2, 2`, not both ending in `0`, and sorted digits match `0126`.

---

**Generated:** 2026-11-04
