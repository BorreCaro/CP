# RPC 2026-10 K - Trains

**Type:** Implementation / 1D Kinematics Simulation
**Rating / Context:** Div 3B / Div 2A (RPC 10 2026)
**Tag:** 1d-interval-translation-directional-head

## Key Insight

💡 At time `t`, a train starting at `[p, p + l - 1]` occupies `[tl, tr]` with `tl = p +- s * t` and `tr = tl + l - 1`; the engine `'!'` is at `tr` if moving right (`'R'`) and at `tl` if moving left (`'L'`).

## Pattern Trigger

"Render `m` parallel tracks of length `n` at time `t` where each train of length `l` moves at speed `s` left or right."

## Breakthrough

Keep `tl <= tr` ordered as the closed interval `[tl, tl + l - 1]` regardless of direction, and only branch on `d == 'R'` to choose the velocity sign and which endpoint receives `'!'`.

## Code Spotlight

```cpp
long long tl = (d == 'R') ? (p + t * s) : (p - t * s);
long long tr = tl + l - 1, engine = (d == 'R') ? tr : tl;
string line(n, '=');
for (long long j = max(0LL, tl); j <= min((long long)n - 1, tr); ++j)
    line[j] = (j == engine) ? '!' : '#';
```

## Example

Input: `n = 5, m = 1, t = 1`, train `p = 0, s = 1, d = 'R', l = 3`
Output: `=##!=`
Why: Interval shifts to `[1, 3]` with the engine at the right endpoint `3`.

---

**Generated:** 2026-11-04
