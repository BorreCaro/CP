# Problema G: Math United FC

- **Concurso:** XL Maratón Nacional de Programación Colombia (ICPC Colombia 2026)
- **Autor:** Juan Corena
- **Dificultad Estimada:** Media (Div 2C / Div 1A)
- **Estado:** Editorial de Referencia Oficial
- **Archivos de Referencia:**
  - Enunciado Oficial: [Problemset_ICPC_Colombia_2026.pdf](../../inputs/problemset/Problemset_ICPC_Colombia_2026.pdf)
  - Solución Oficial: [G_Math_United_FC.cpp](../../inputs/solutions/G_Math_United_FC.cpp)

---

## 1. Deconstrucción del Enunciado

Math United FC cuenta con un presupuesto inicial `B >= 0` (`0 <= B <= 10^9`) y se enfrenta al mercado de fichajes con una lista de `P` jugadores (`1 <= P <= 200000`) en un orden secuencial estricto.
El valor de cada jugador `P_i` (`-10^9 <= P_i <= 10^9`) define su categoría:
1. **Jugador Comercial (`P_i > 0`):** Genera ingresos netos al club, incrementando el presupuesto disponible.
2. **Prospecto Deportivo (`P_i <= 0`):** No genera ingresos inmediatos y reduce (o deja igual) el presupuesto disponible (su contratación cuesta `-P_i`).

Las decisiones deben tomarse sobre la marcha (*on-the-fly*) en el orden exacto de la lista. En ningún momento el presupuesto puede volverse negativo (`B < 0`).
Se debe determinar el **número máximo de prospectos deportivos** que es posible contratar respetando las restricciones financieras. La entrada finaliza con la línea `0 0`.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **`P <= 200000` y `B <= 10^9`:** Las decisiones deben tomarse en tiempo lineal o cuasilineal `O(P log P)`.
- **Elegir entre tomar o rechazar elementos con presupuesto no negativo acumulativo:** Clásica estructura de optimización voraz con arrepentimiento (*Greedy Buy-and-Regret* / *Potions Problem* / *Replacement Heuristic*).
- **Los comerciales siempre suman (`P_i > 0`):** Nunca existe incentivo alguno para rechazar un jugador comercial, pues solo aumenta la holgura presupuestaria disponible para futuros prospectos.

---

## 3. Modelo Matemático y Algorítmico / Invariantes

### Invariante de Contratación Voraz con Arrepentimiento
Queremos maximizar la cardinalidad del conjunto de prospectos elegidos `S`. Cada prospecto `j` contratado cuesta `cost_j = -P_j >= 0`.
Si en el paso actual contratamos un nuevo prospecto y nuestro presupuesto cae por debajo de cero (`B < 0`), **la única forma de restaurar la factibilidad financiera manteniendo el número de prospectos contratados lo más alto posible es expulsar exactamente un prospecto**.

¿A cuál prospecto debemos despedir?
Para maximizar el presupuesto remanente futuro sin reducir la cuenta total de prospectos más de lo estrictamente necesario, **debemos revocar la contratación del prospecto más caro contratado hasta el momento**:
`revocado = argmax_{k in S} (cost_k)`

Al reemplazar mentalmente el prospecto más caro por uno más barato (o simplemente descartar el más costoso para volver a tener `B >= 0`), la cantidad de prospectos se preserva o disminuye en 1, pero el presupuesto neto disponible queda estrictamente maximizado para todas las decisiones futuras.

### Mecánica con Cola de Prioridad Máxima (`std::priority_queue`)
1. Inicializar `priority_queue<long long> hired`.
2. Para cada jugador con valor `v`:
   - Si `v > 0`: `B += v`.
   - Si `v <= 0`: Contratar tentativamente: `B += v`, e insertar su costo `hired.push(-v)`.
   - Si `B < 0`: Arrepentirse del prospecto más caro:
     `B += hired.top()`;
     `hired.pop()`.
3. Al finalizar la lista, `hired.size()` es la respuesta óptima.

- **Complejidad Temporal:** `O(P log P)`, ya que cada prospecto se inserta y se extrae de la cola de prioridad a lo sumo una vez.
- **Complejidad Espacial:** `O(P)` para almacenar los elementos en el heap.

---

## 4. Implementación de Referencia Comentada (C++17)

```cpp
#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long B;
    int P;
    while (cin >> B >> P && (B != 0 || P != 0)) {
        // Max-heap que almacena los costos positivos de los prospectos contratados
        priority_queue<long long> hired;

        for (int i = 0; i < P; i++) {
            long long v;
            cin >> v;

            // Jugador comercial: ganancia neta, siempre se contrata
            if (v > 0) {
                B += v;
                continue;
            }

            // Prospecto deportivo: costo tentativo
            B += v;
            hired.push(-v);

            // Si el presupuesto se vuelve negativo, nos arrepentimos del más costoso
            if (B < 0) {
                B += hired.top();
                hired.pop();
            }
        }

        cout << hired.size() << '\n';
    }

    return 0;
}
```

---

## 5. Catálogo Preventivo de Antipatrones Cognitivos

1. **Enfoque Voraz Miope sin Arrepentimiento (*Naive Greedy Without Regret*):**
   Aceptar prospectos solo si el presupuesto actual lo permite (`if (B >= -v) B += v`), sin descartar nunca prospectos pasados. Un prospecto muy caro al inicio puede consumir todo el presupuesto e impedir contratar una gran cantidad de prospectos económicos posteriores.
2. **Intento de Programación Dinámica de Mochila (`O(P * B)`):**
   Modelar el problema como DP con estado `dp[i][b]`. Dado que `B <= 10^9`, una matriz de DP provocaría *Memory Limit Exceeded* (MLE) y *Time Limit Exceeded* (TLE) colosales.
3. **Desbordamiento de Enteros de 32 bits:**
   El presupuesto `B` alcanza `10^9` y cada jugador aporta hasta `10^9`. Con `P = 200000`, la suma acumulada de ingresos puede alcanzar `2 * 10^{14}`, desbordando los límites de `int`. `B` debe ser estrictamente `long long`.
