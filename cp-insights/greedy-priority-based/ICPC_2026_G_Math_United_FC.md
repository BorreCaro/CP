# ICPC 2026 G - Math United FC

**Type:** Greedy / Priority-Based
**Rating / Context:** Div 2C / Div 1A (ICPC Colombia 2026)
**Tag:** buy-and-regret-max-heap-potions

## Key Insight

💡 Ante decisiones secuenciales donde el presupuesto no puede volverse negativo, aceptar tentativamente a cada prospecto con costo en un max-heap y, al entrar en déficit, arrepentirse revocando el prospecto más caro previamente contratado.

## Pattern Trigger

"Secuencia de `P <= 200000` jugadores con ingresos `P_i > 0` o costos `P_i <= 0`, maximizar prospectos contratados sin que el saldo `B` caiga por debajo de 0 en ningún paso."

## Breakthrough

Al violar el presupuesto `B < 0`, expulsar el prospecto de mayor costo `hired.top()` preserva o recupera la factibilidad dejando la máxima holgura posible para contrataciones futuras.

## Code Spotlight

```cpp
priority_queue<long long> hired;
for (int i = 0; i < P; i++) {
    long long v; cin >> v;
    if (v > 0) { B += v; continue; }
    B += v; hired.push(-v);
    if (B < 0) { B += hired.top(); hired.pop(); }
}
cout << hired.size() << '\n';
```

## Example

Input: `B = 9`, `P = 6`, jugadores `[-4, -7, 5, -6, -1, -4]`
Output: `3`
Why: Se contrata A (`-4`), luego tentativa B (`-7`, suma -2) se revoca B; se cobra C (`+5`), se contratan E (`-1`) y F (`-4`), logrando 3 prospectos (A, E, F).

---

**Generated:** 2026-10-10
