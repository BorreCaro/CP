# Breakthroughs

Every problem I solve teaches me one thing I couldn't think of.
This is where they live.

---

## 2026-07-27

- **70 - Climbing Stairs** — _dp[i] = dp[i-1] + dp[i-2]. It's just Fibonacci — the number of ways to reach step i is the sum of ways to reach the two previous steps._
- **746 - Min Cost Climbing Stairs** — _Same Fibonacci skeleton as Climbing Stairs, but add cost[i] at each step and use min() instead of +. The top is past the last index, so answer = min(dp[n-1], dp[n-2])._
- **198 - House Robber** — _At each house, two options: skip (keep dp[i-1]) or rob (dp[i-2] + nums[i]). The answer is always max of the two. State definition is everything — once dp[i] is "best up to house i," the recurrence writes itself._
- **213 - House Robber II** — _A circle just means "run the linear DP twice, excluding each endpoint once." The recurrence doesn't change — only the range does. max(rob_linear(0, n-2), rob_linear(1, n-1))._
- **740 - Delete and Earn** — _Index by value, not by uniqueness. After building points[x] = x * freq[x], the House Robber recurrence applies directly. Compressing to unique values loses gap info and invents fake adjacency conflicts._
- **139 - Word Break** — _dp[i] = true means there EXISTS some valid cut point. The nested loop over ALL possible j (from 0 to i-1) is structurally required — you must scan every previous state, not follow a single pointer. `s.substr(j, i-j)` extracts the candidate word from position j of length i-j; if it matches AND dp[j] is true, you've found a segmentation. I was stuck on a greedy approach, committing to the first match and never backtracking — but you can't use one running pointer when you need to try ALL possible cuts._

## 2026-08-01

- **279 - Perfect Squares** — _I knew the pieces (enumerate all squares) but couldn't write the formula. The missing step was the state: dp[i] = minimum squares to make exactly i. Once the state exists, the recurrence writes itself by asking "what's the last square I add?" — every representation of i ends in some square s, and the rest is a representation of i - s, so dp[i] = min(dp[i-s] + 1) over all squares. It's literally Coin Change with coins = {1, 4, 9, ...}. Ingredients without the recipe (state + last-piece question) don't make a DP._
- **322 - Coin Change** — _The 279 → 322 transfer worked: same code, coins swapped for squares, solved in 5 minutes at 9/10. Only stumble: `if (x < amount) break` instead of `if (x > i) break` — the inner-loop guard must compare against the current subproblem i, never the global target amount. A wrong guard doesn't crash; it silently degrades the DP to only the smallest coin. Word Break took 2h, Perfect Squares was unsolvable alone, Coin Change was trivial — pattern recognition is the whole game._
- **139 - Word Break (re-solve)** — _2 hours → 3 minutes. The greedy trap isn't just learned, it's gone: the nested loop and dp[0] = true base case came out automatically, no hints. Spaced repetition works — this is the proof._
- **746 - Min Cost Climbing Stairs (re-solve, stuck)** — _My own diagnosis was right: "check my dp's state." I wrote dp[1] = min(cost[0], cost[1]) which mixes two state definitions (dp[0] = "cost to stand on step", dp[1] = "cheapest way to reach"), then cost[i] at i == n (out of bounds) and return dp[n-1] (wrong index — the top is step n). All three bugs are the SAME bug: the state was never pinned down. Write the state definition as a comment BEFORE coding._
- **213 - House Robber II (re-solve)** — _Decomposition and recurrence were automatic; the only bug was forgetting the n == 1 / n == 0 guards before indexing nums[1] and nums[2]. Guard tiny inputs before touching the recurrence._
- **377 - Combination Sum IV** — _I had the intuition — "get all the previous combinations" — but no correct formula, because the base case was wrong. Counting needs dp[0] = 1 (the empty sequence is one way, like 0! = 1), while min-cost problems need dp[0] = 0. Trace (x) alone: it's counted via dp[x] += dp[x-x] = dp[0]. And the +1 I kept adding was Coin Change's "count coins used" logic leaking in — ways are extended as whole blocks, not incremented per path. Plus: intermediates can overflow int (dp[630] ≈ 4.6×10¹⁸) while the final answer is 1 — unsigned int or clamp. Counting = add blocks, dp[0] = 1; cost = min, dp[0] = 0._
- **343 - Integer Break** — _The "leave it whole" escape hatch. Every segmentation problem I'd seen forced the remainder into a full subproblem — dp[i-x] always meant "decompose further." Integer Break is the first where a piece can stay as-is, and dp[i-j] alone can't express that: without j·(i−j), dp[4] = 3 instead of 4, because 2+2 (both pieces whole) is unreachable. The helper explained it directly instead of guiding me — that stung, because the skeleton was already mine. But I now know WHY the term exists, and the no-hints Day 3 re-solve proves ownership. Ask always: may the piece stay whole?_
- **3857 - Minimum Cost to Split into Ones** — _A new pattern family: interval split-cost. The condition I kept groping for — EVERY piece must be split all the way down, and you pay for the split itself — makes it dp[j] + dp[i−j] + j·(i−j) (both children recurse), not the segmentation shapes I knew: dp[i−x] + 1 consumes a piece, and Integer Break's max(j·(i−j), j·dp[i−j]) lets a piece stay whole. Three policies, same skeleton. Sanity check that made it land: every pair of final ones separates exactly once, so the answer is always n(n−1)/2 — and the DP silently agrees._

- **1043 - Partition Array for Maximum Sum** — _The missing move: define the LAST piece as a window of length j ≤ k ending at i, value max·len. I kept thinking forward ("which element anchors a group?") instead of backward ("what's the last piece?"). Once the piece is the window, dp[i] = max over j ≤ k of dp[i-j] + mx·j — and bounded pieces mean only k candidates, the same scan Decode Ways needs with pieces of 1-2 digits. My gap pattern: when pieces are given I'm fine; when I must define them (squares in 279, windows here) I stall — because defining the piece IS the state._
- **1043 - Partition Array for Maximum Sum (deep re-study)** — _The loop trick that fixes my whole off-by-one class: think in "elements I'm considering", not indices. i = current position, j = how many elements back → window start = arr[i-j+1], piece-size cap = min(k, i+1), dp[i+1] holds the best for arr[0..i]. j=1 touches arr[i]; j=k touches arr[i-k+1]. Same question serves Decode Ways (pieces of length 1-2). Trace confusion resolved: arr=[1,15,7,9], k=3 → 54 comes from [1,15,7]+[9] (45+9), not [1,15]+[7,9] (48)._

## 2026-08-04

**Redemption Day — the full re-solve session. Average confidence 6.4 — 8.7/10; 11 of 13 problems now ≥ 8.**

- **343 - Integer Break (re-solve)** — _2:37, 10/10, ZERO hints: max({dp[i], dp[i-j]\*j, (i-j)\*j}) written alone. The stolen solve is officially repaid — the Day 3 verdict came back: it's mine. The whole-piece term appeared by itself._
- **3857 - Split into Ones (re-solve)** — _15:45 and I forgot +dp[j] again — both children must recurse, that's the interval signature. I "solved" it with a max-variant that only passes because the total cost is invariant: every pair of final units separates exactly once, so ANY consistent recurrence lands on n(n−1)/2. An accidental AC is not understanding — Day 7 re-solve with both children._
- **198 - House Robber (re-solve)** — _dp[1] = max(nums[0], nums[1]) is not intuition — it's the base case. Under "best considering houses 0..i", at i=1 you face two adjacent houses: the take/skip decision at the boundary where dp[i-2] doesn't exist yet. Base cases are the recurrence applied at the start of the array._
- **746 - Min Cost (re-solve)** — _The base-case reflex error fired AGAIN (dp[1] = min(cost[0], cost[1]) from memory), but I caught it by thinking about the state, not by luck — 3:13, 9/10. The state-first habit is forming._
- **The init lesson (from 279, 53, 377)** — _Initialization is part of the recurrence: 0 for sums/counts, big sentinel for min, INT_MIN for max, dp[0] = 1 for counting (i-x = 0 must be reachable)._

## 2026-08-09

**The bounds day — and the proof the method works.**

- **3857 - Split into Ones (re-solve)** — _15:45 → 2:10. The both-children recurrence came out COLD; only base case + dp-init values were buggy. 8/10, one final confirmation pass on 08-12 — but the interval signature is now mine._
- **1043 - Partition Max (re-solve)** — _16 min, had to see the solution: `j < min(k, i+1)` runs only k−1 lengths — the cap must be `<=`. The state and loop trick were RIGHT; the bounds audit was skipped. Same class as 139._
- **139 - Word Break (re-solve)** — _Looped to n−1, but the answer reads dp[n]. The nested loop and dp[0]=true were automatic — the boundary was off by one. Same failure class as 1043: bounds audit._
- **740 (5 min, 9/10) and 213 (3 min, 9/10)** — _Clean re-solves, logic remembered without the solutions._
- **The meta-proof** — _"I didn't remember the solutions but remembered the logic" — that's EXACTLY what spaced repetition produces: the pattern in long-term memory, rote details faded. Two of today's stalls were bounds/indexing, not concepts — a habit to build, not a hole in understanding._

## 2026-08-15

**Near-clean sweep: 139 (2:22, 10/10), 3857 (3 min, 10/10 — final pass), 70 (1:10, 10/10). 12 of 13 at ≥ 8.**

- **139 - Word Break (re-solve)** — _2:22, 10/10 — including the dp[n] answer line that slipped on 08-09. The regression is closed; the bounds audit worked when it mattered._
- **3857 - Split into Ones (final pass)** — _3 min, 10/10, clean. From 15:45 and a forgotten +dp[j] to 3 minutes in 11 days. The interval signature is reflex._
- **1043 - Partition Max (re-solve, still stuck)** — _Third occurrence of the same class, but the diagnosis finally sharpened: my final code was CORRECT (1-indexed arr[i-j], dp[i-j], j <= min(k, i)) — I was flipping between 0-indexed and 1-indexed conventions mid-attempt. The recurrence was never the problem; the convention switch was. Protocol for 08-18: write the convention, the j=1 check (window = arr[i-1]), and the cap BEFORE the loops._
- **The convention lesson** — _When indexing a window: choose the convention once, then verify j=1 touches the LAST element. Every 1043 failure is the same root: mixing two conventions in one attempt._
- **91 - Decode Ways (NEW SOLVE — THE BOSS FELL)** — _Three mechanical bugs, each mapping to a KEY_TIPS row: ASCII char math (s[i-2]*10 = 49*10, not 1\*10), an n==2 hardcode ("10" is 1 way, not 2), and a continue that dropped the 1-char gate ("27" → 0 instead of 1). The insight that fixed it: the two gates are INDEPENDENT TERMS OF A SUM, not branches of an if-else. dp[i] = (s[i-1]!='0' ? dp[i-1] : 0) + (10<=two<=26 ? dp[i-2] : 0). Zero traps fall out of the gates by themselves — "06" → 0, "10" → 1, "210" → 1 — no special-casing. The segmentation family is COMPLETE._
- **55 - Jump Game (NEW SOLVE)** — _The scan-all-previous DP (dp[i] = any reachable j with nums[j]+j >= i) is correct but O(n²) and "really slow." The insight: reachability is MONOTONE — reaching i means reaching everything before it — so a single running frontier mx = max(mx, i+nums[i]) replaces the whole nested loop. It's the ONE case where greedy is provably correct, the reverse of the Word Break trap._
- **45 - Jump Game II (NEW SOLVE, 7 min, 10/10)** — _The min-jump sequel: the DP (dp[i] = min over reachable j of dp[j]+1) transferred cleanly, but the O(n) trick needs a SECOND pointer. Jump Game's single mx frontier tells you how far you can reach, not how many jumps — you need `end` (the current level's boundary) and the `i == end` trigger to count when a new jump begins. Minimum jumps = BFS levels: frontier + level boundary._
- **300 - Longest Increasing Subsequence (NEW SOLVE, 13 min)** — _The REAL scan-all-previous problem, the reverse of Jump Game: here greedy does NOT work, the nested loop is genuinely required. I only thought of the DP — the O(n log n) patience-sorting trick (res[k] = minimal tail of a length-k+1 subsequence, lower_bound to replace) is a SEPARATE algorithm I wouldn't derive from the DP. Also: answer is max(dp), not dp[n-1], because the LIS might not end at the last index._

## 2026-09-13

- **1157E - Minimum Array** — _`std::lower_bound(b.begin(), b.end(), val)` compiles on `std::set`/`multiset` but takes `O(n)` time because set iterators are bidirectional (not random-access), silently degrading an algorithm to `O(n^2)` TLE. Always use the member method `b.lower_bound(val)` for `O(log n)` balanced tree traversal. Also, minimizing `(a_i + b_j) % n` greedily queries `b.lower_bound(n - a_i)` and wraps around to `b.begin()` when reaching the end._
- **1857A - Array Coloring** — _Parity problems reduce entirely to counting odd numbers — even numbers contribute `0 mod 2`, eliminating the need for multi-branch case checks._
- **1859A - United We Stand** — _Separating strictly by max value (`c = {max(a)}`) makes divisibility impossible from `c` to `b`, while any all-equal array immediately yields `-1` as `b` would be empty._
- **1855B - Longest Divisors Interval** — _You never need to search arbitrary intervals `[l, r]`; the optimal interval is always the prefix `[1, k-1]` ending right before the first non-divisor, computable in `O(log n)` operations._
- **RPC 2026-08 A - Contest Advancement** — _Do not print greedily during pass 1; collect selected team IDs in a set or marker array, then do a final pass over the original ranking to preserve the true relative merit order._
- **RPC 2026-08 B - Digit Translation** — _Digit words have lengths 3 to 5 only (`O(1)` lookback); tracking both `dp_len[i]` and `dp_cnt[i]` in a single linear pass prevents exponential branching and duplicate counting across overlapping segments._
- **RPC 2026-08 C - Don't Hunger Together** — _Feasibility is monotonic, enabling binary search on the continuous daily rate; greedy consumption using Earliest Deadline First (EDF) via min-heap is provably optimal for perishable resources._
- **RPC 2026-08 D - Garden of Thorns** — _Linearity of expectation `E[sum X_i] = sum E[X_i]` decouples plants completely; each plant's protection probability is simply the circle-rectangle clipping area divided by the garden area._
- **RPC 2026-08 E - ICPC Team Generation** — _Monotonicity of preference intervals (`a_i <= a_j` and `b_i <= b_j`) implies inner trio members are automatically compatible if outer boundaries hold; greedy leftmost trio selection is optimal._
- **RPC 2026-08 F - Is Y a Vowel?** — _Avoid regex overhead or multiple string scans; a single linear pass with dual counters cleanly branches standard vowels vs. permissive vowels in `O(|S|)` time and `O(1)` memory._
- **RPC 2026-08 G - Lines Per Hour** — _Ascending greedy sorting maximizes the count of completed problems under a fixed line budget; beware of hardcoded sample constants and missing fallthrough returns._
- **RPC 2026-08 H - Magnesium Supplementation** — _Search factor pairs up to `sqrt(N) <= 10^6` rather than iterating limits up to `10^12`, and enforce 64-bit (`long long`) containers to avoid silent 32-bit integer overflow on large divisors._
- **RPC 2026-08 I - Missing Number** — _With `b < 10^5`, testing all 5 possible prefix lengths (`1 <= L <= 5`) eliminates all search branching; the remaining sequence parses deterministically in `O(|S|)` with at most one skipped number._
- **RPC 2026-08 J - Tip of Your Tongue** — _Equal prefix and suffix lengths enable rolling double-hashes grouped by length; Principle of Inclusion-Exclusion answers AND, OR, and XOR queries in `O(1)` time per query._
- **RPC 2026-08 K - Very Important Edge** — _Removing a tree edge cuts the MST into two components, repairable by the lightest crossing non-tree edge; sorting chords and applying DSU path compression updates each tree edge at most once._
- **RPC 2026-08 L - Water Journal** — _With only one missing entry, needing both distinct extremes (`a != b` with neither recorded) is impossible by the pigeonhole principle; check the complete 4-state boolean matrix._

## 2026-09-19

- **1520D - Same Differences** — _Decouple relational equation between two indices: rewrite a_j - a_i = j - i as a_j - j = a_i - i, reducing an O(N^2) search over pairs to an O(N) frequency counting problem over invariant values b_i = a_i - i. Accumulate pair counts with 64-bit integers (long long) to prevent overflow up to N*(N-1)/2._
- **702B - Powers of Two** — _Since a_i <= 10^9, pair sums are strictly bounded by 2 * 10^9 < 2^31, leaving only 31 candidate powers of two. Instead of O(N^2) pair matching, compute powers on the fly in O(1) via bit shifts and query complement frequencies in O(31 * N). Beware of signed 32-bit overflow with 1 << 31 (undefined behavior); always use 1LL << k._

## 2026-09-26

- **RPC 2026-09 A - Alejandro, lee por favor** — _Never update frequency using the encrypted character read from input; the state update depends strictly on the original decrypted letter L = (E - c + 26) % 26._
- **RPC 2026-09 B - Betito el viajero** — _Recursive DFS on a 1000 x 1000 grid risks 10^6 stack frames and instant SIGSEGV; an iterative queue<pair<int,int>> BFS consumes heap memory safely without recursion limits._
- **RPC 2026-09 C - Company** — _Condition P_i < i guarantees an inherent reverse topological order: no adjacency lists, no recursion, and no LCA queries are needed; a simple for (int i = N; i >= 1; --i) pass computes edge contributions and subtree diameters in under 20 MB._
- **RPC 2026-09 D - Dangerous Odyssey** — _Islands (R) are landmasses that provide shelter radius under Manhattan distance but cannot be sailed through; ship navigation must be strictly restricted to open water . and arrival at A._
- **RPC 2026-09 E - Enarmonía** — _Greedy choice of immediate echoes burns the K switch budget prematurely; DP top-down memoization or a 2-layer rolling array explores all feasible switch points in O(T^2 * K)._
- **RPC 2026-09 F - Flipando colores con la DIAN** — _A naive greedy choice on available roots fails when a slow root blocks an ultra-dense descendant; Lawler's theorem proves contraction must collapse the global max-density child into its current parent._
- **RPC 2026-09 G - Guanex y el diámetro con actualizaciones** — _In any tree, the furthest node from any arbitrary vertex x is always at least one of the endpoints of any diameter; full BFS recomputations are completely avoided by tracking max(diam, dist(x, A), dist(x, B)) with Binary Lifting LCA in O(log V)._
- **RPC 2026-09 H - Humbertov y su taza de café** — _Common factor (1/3) * pi cancels completely; evaluate f(x) = x * (r^2 + rx^2 + r * rx) directly with rx = r + (R - r) * (x / h) using 100 binary search iterations to reach < 10^-25 precision._
- **RPC 2026-09 I - Internal Triangles** — _Do not compute n * (n - 1) * (n - 2) directly in 64-bit integer (n^3 <= 10^54 overflows long long); reduce each factor modulo 10^9 + 7 first and multiply by modular inverse inv(6) = 166666668._
- **RPC 2026-09 J - Juan y sus ovejas** — _Initialize total = N and each size sz[i] = 1; isolated vertices never mentioned in pairs are automatically preserved as independent classes of size 1 in DSU._
- **RPC 2026-09 K - K-th shortest path** — _Edge weights reach 10^8 and N <= 10^4, so path length reaches 10^12; using int and inf = 1e9 causes fatal overflow and incorrect paths; all distances must be long long with INF = 1e18._
- **RPC 2026-09 L - Locate Tobby’s nest** — _Backtrack from B to A without storing parent pointers by simply stepping to any orthogonal neighbor with distance d[u] - 1, and strictly enforce the author's tie-break rule: smaller column first, then smaller row._
- **RPC 2026-09 M - Marble tilt maze** — _Board stabilization after every single-cell slide means tilts generate multiple cost-1 intermediate states rather than only full-obstacle stops; evaluate concurrent marble motion cell-by-cell prioritizing the forward marble along (r * dr + c * dc) to handle convoy clearances and prune invalid hole or boundary falls immediately._

## 2026-10-10

- **ICPC 2026 A - Balanced System Reactor** — _In an equation with n - 3 ones where a*b*c - (a+b+c) = m, fixing a <= m^(1/3) and b >= a uniquely determines c = (m + a + b) / (a * b - 1), reducing a 3D search to a fast bounded iteration in O(m^(2/3))._
- **ICPC 2026 B - Bankey** — _Decouple odd and even indices into independent parity prefix sums pre[i] = d[i] + pre[i-2], enabling O(1) evaluation of any length-M step-2 window via pre[i] - pre[i - 2*M]._
- **ICPC 2026 C - Into the Onion** — _Square the transition threshold condition dist <= 1.5 * d to 4 * dist^2 <= 9 * d^2 to execute convex hull peeling and layer-by-layer DP entirely in exact 64-bit integer arithmetic._
- **ICPC 2026 D - Bingwhenever** — _Invert the simulation: pre-record each ball's drawn timestamp when[x] in a hash map so each player's finish step is evaluated statically as finish[i] = max_{x in card[i]} when[x] in O(K)._
- **ICPC 2026 E - Custom Keypad** — _In partition DP over 26 letters, backtrack from right to left scanning cut index s in strictly descending order; the first s achieving the optimal cost dp[j-1][s] + cost[s][p-1] == dp[j][p] guarantees the rightmost separator._
- **ICPC 2026 F - Heist** — _Partition the room with Sutherland-Hodgman polygon clipping, then find the Chebyshev center of each convex cell via 60 iterations of binary search contracting edges inward by radius r._
- **ICPC 2026 G - Math United FC** — _When maintaining non-negative budget with on-the-fly choices, tentatively hire every prospect into a max-heap and immediately regret the single most expensive prospect whenever budget drops below zero._
- **ICPC 2026 H - HCubes Costs** — _Hypercube edge costs c(i) = i + 1 make any redundant flip strictly suboptimal; the shortest path between a and b simply flips each differing bit in a ^ b exactly once with cost sum ((a ^ b >> i) & 1) * (i + 1)._
- **ICPC 2026 I - Fair Workload Distribution** — _Deconstruct daily round-robin into a uniform base floor(M/N) for all workers and circular remainder intervals, processing queries offline with coordinate compression over queried workers and a Fenwick tree._
- **ICPC 2026 J - Courage is Contagious** — _Soldier threshold function f(c) = count(k_i <= c) is monotone non-decreasing, so discrete dynamics converge monotonically to the nearest fixed point: up[c_0] if f(c_0) >= c_0, down[c_0] otherwise._
- **ICPC 2026 K - Sample Median Preservation** — _For an odd sample of size K, having >= h + 1 elements smaller than the median and >= h + 1 larger requires 2h + 2 = K + 1 > K elements, proving the two bad events are strictly mutually exclusive and sum directly by complement._
- **ICPC 2026 L - Don't Ask Why 2D** — _Break 8 plane symmetries by fixing the first step to R and the first turn to U; because max degree in the contact graph is at most 2, optimal H-subsets for all B <= N can be solved via SOS bitmask DP in < 0.2 s._
- **ICPC 2026 M - Byte Flu** — _Model minimum device disconnection cost as a minimum vertex-cut problem, splitting normal nodes into (i_in, i_out) with capacity c_i and testing string connectivity with banded Levenshtein DP |i - j| <= K with early pruning._

---

**Last Updated:** 2026-10-10

