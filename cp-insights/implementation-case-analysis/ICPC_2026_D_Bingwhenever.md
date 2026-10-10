# ICPC 2026 D - Bingwhenever

**Type:** Implementation / Case Analysis
**Rating / Context:** Div 3B / Div 2A (ICPC Colombia 2026)
**Tag:** hash-map-timestamp-lookup-static-finish

## Key Insight

💡 Mapear cada bola al paso de extracción `when[x]` permite determinar el tiempo de finalización de cada jugador directamente como `finish[i] = max_{x in card[i]} when[x]`, evitando la costosa simulación paso a paso.

## Pattern Trigger

"`N <= 10^3` jugadores con `K <= 10^3` números en sus cartones y `B <= 10^5` bolas extraídas en un orden prefijado, con números hasta `10^9`."

## Breakthrough

Invertir la perspectiva del tiempo: en lugar de simular el avance de las bolas y actualizar cartones, evaluar estáticamente en qué turno se llena cada cartón con una única pasada sobre sus `K` números.

## Code Spotlight

```cpp
unordered_map<int, int> when;
when.reserve(2 * b);
for (int s = 1; s <= b; s++) { int x; cin >> x; when[x] = s; }
for (int i = 0; i < n; i++) {
    for (int x : card[i]) finish[i] = max(finish[i], when[x]);
    best = min(best, finish[i]);
}
```

## Example

Input: 3 jugadores con bolas extraídas `5, 7, 3, 2, 10, 11, 15, 4`. Bob tiene `{3, 4, 7, 10}`.
Output: `alice charles`
Why: Los números de Alice y Charles se extraen para el paso 7 (bola 15), mientras que el último número de Bob (4) sale en el paso 8.

---

**Generated:** 2026-10-10
