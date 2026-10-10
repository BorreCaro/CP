# Pattern: Segmentation DP

## Pattern Name: **Linear Partition DP** (a.k.a. Sequence Segmentation DP)

### Description

This pattern applies when you're given a **linear sequence** (a string or array) and asked whether — or how well — it can be **split into contiguous pieces**, where each piece must independently satisfy some condition.

The key mental shift: instead of asking "how do I cut this string?" directly, you ask a smaller question at every position: **"is this prefix (or subarray ending here) reachable/valid, given everything before it?"** You build the answer from the ground up, left to right, reusing work you've already done.

### When to recognize it

Ask yourself: _"Can/should I split this sequence into pieces, where each piece needs to pass some test?"_ If yes, this pattern likely applies. Common signals in the problem statement:

- "segmented into..."
- "partitioned into..."
- "split into subarrays/substrings such that each..."
- "break into words / numbers / groups"

### The General Template

**State:**

```
dp[i] = true/best-value, representing: "the first i elements of the sequence
         can be validly partitioned"
         (or: "the best score achievable partitioning the first i elements")
```

**Base case:**

```
dp[0] = true (or 0, or the neutral value) — an empty prefix is trivially valid
```

**Transition:**

```
For each i from 1 to n:
    For each j from 0 to i-1:
        if dp[j] is valid/true AND segment(j, i) satisfies the condition:
            dp[i] = combine(dp[i], dp[j], segment(j, i))
```

Where:

- `segment(j, i)` is the piece from index `j` to `i` (exclusive) — a substring, subarray, etc.
- `combine(...)` depends on what you're optimizing:
  - **Existence (true/false):** `dp[i] = dp[i] OR (dp[j] AND valid(segment))`
  - **Counting ways:** `dp[i] += dp[j]` (if segment is valid)
  - **Min/max cost:** `dp[i] = min(dp[i], dp[j] + cost(segment))`

**Answer:** `dp[n]` (the whole sequence).

**Complexity:** Typically **O(n²)** for the two nested loops, times whatever it costs to check/validate `segment(j, i)` (O(1) for a hash lookup, O(k) for a palindrome check, etc.).

### Problem Family (all share this exact skeleton)

| Problem                        | What `segment(j, i)` must satisfy | What `dp[i]` tracks            |
| ------------------------------ | --------------------------------- | ------------------------------ |
| **Word Break**                 | Is a word in the dictionary       | Reachable? (bool)              |
| **Word Break II**              | Is a word in the dictionary       | All valid segmentations (list) |
| **Palindrome Partitioning II** | Is a palindrome                   | Min cuts needed                |
| **Perfect Squares**            | Is a perfect square number        | Min pieces to sum to n         |
| **Decode Ways**                | Is a valid 1 or 2-digit code      | Number of ways to decode       |

### The core intuition to keep

You're not trying to _guess_ the right split in one shot. You're asking, at every prefix length, **"is there some earlier valid stopping point I could have chained from?"** — and because you scan left to right, `dp[j]` for any `j < i` is already known by the time you need it. That's what turns an exponential "try every possible split" search into a polynomial one: **you never re-derive whether a prefix is valid; you just look it up.**

Try spotting this shape cold on **Palindrome Partitioning II** or **Perfect Squares** next — see if you can write the recurrence yourself before coding.

### 🟢 Solved Problems

| ID   | Title                                                                  | Confidence  | Core idea                                                                                              |
| ---- | ---------------------------------------------------------------------- | ----------- | ------------------------------------------------------------------------------------------------------ |
| 139  | [Word Break](139_Word_Break.md)                                        | 10/10       | Existence: `dp[i] = OR over j of (dp[j] && s[j..i) in dict)`                                           |
| 279  | [Perfect Squares](279_Perfect_Squares.md)                              | 9/10        | Min: `dp[i] = min over squares s ≤ i of (dp[i-s] + 1)` — last-piece decomposition                      |
| 343  | [Integer Break](343_Integer_Break.md)                                  | 10/10       | Max: `dp[i] = max over cuts j of (j·(i−j), j·dp[i−j])` — the "leave whole" twist                       |
| 1043 | [Partition Array for Max Sum](1043_Partition_Array_for_Maximum_Sum.md) | 6/10        | Max over bounded windows: `dp[i] = max over j ≤ k of dp[i-j] + max(window)·j` — the Decode Ways engine |
| 91   | [Decode Ways](91_Decode_Ways.md)                                       | 7/10 (est.) | Count + gates: `dp[i] = (s[i-1]!='0' ? dp[i-1] : 0) + (10 ≤ two ≤ 26 ? dp[i-2] : 0)`                   |

> 🏆 **THE BOSS FELL — 91 Decode Ways cleared on 08-15.** The segmentation family is now COMPLETE: OR (139) · min (279) · max (343) · count (91/377), unbounded and bounded pieces. 🔴 **1043 (6/10) is the only item left** — third occurrence of its index/cap class; special protocol 08-18 (convention + j=1 check + cap before the loops). Next: 639 Decode Ways II (the sequel) or move to the interval classics.

### ⏳ Next up

- [639 - Decode Ways II](https://leetcode.com/problems/decode-ways-ii/) — the sequel: same gates plus `'*'` wildcards (harder)
- [140 - Word Break II](https://leetcode.com/problems/word-break-ii/) — return all segmentations (backtracking)
- [322 - Coin Change](https://leetcode.com/problems/coin-change/) — ✅ solved 2026-08-01 (9/10, filed under [knapsack-dp](../knapsack-dp/322_Coin_Change.md)) — it was indeed Perfect Squares with coins swapped in
- [343 - Integer Break](https://leetcode.com/problems/integer-break/) — ✅ solved 2026-08-01 (6/10, [note](343_Integer_Break.md)) — max operator + "leave whole" twist
