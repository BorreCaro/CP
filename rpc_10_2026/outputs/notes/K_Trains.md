# Problema K: Trains

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Fácil (Div 3B / Div 2A - Simulación Cinemática 1D)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución del Equipo: [K_Trains.cpp](../../inputs/solutions/K_Trains.cpp)

---

## 1. Insight Clave

💡 En el instante `t`, el `i`-ésimo tren ocupa el intervalo cerrado de celdas `[tl, tr]` donde `tl = p + v * t` (con `v = +s` si `d == 'R'` y `v = -s` si `d == 'L'`) y `tr = tl + l - 1`. La locomotora (`'!'`) se ubica siempre en el extremo frontal del movimiento (`tr` si `d == 'R'`, `tl` si `d == 'L'`), y el resto del intervalo corresponde a vagones (`'#'`).

---

## 2. Análisis de la Solución en Vivo

La solución enviada en vivo (`Trains.cpp`) resolvió el problema mediante simulación directa por cada vía:
- Calculó `tl` y `tr` según la dirección `d`.
- Recorrió `j = 0 .. n - 1` imprimiendo `'!'`, `'#'` o `'='`.
- **Nota sobre Tipos de Datos:** Con `|p| <= 10^5`, `s <= 10^5` y `t <= 10^4`, el desplazamiento máximo es `t * s = 10^9`, que cabe en un entero de 32 bits con signo (`<= 2 * 10^9`), aunque emplear `long long` para `tl` y `tr` es una buena práctica defensiva ante incrementos de cotas.

---

## 3. Patrón de Recurrencia / Sesgo Cognitivo

- **Asimetría de la Locomotora Frontal (*Directional Head Asymmetry*):** Al trasladar un intervalo rígido `[p, p + l - 1]`, el error más frecuente es asumir que `p` es siempre el frente del tren o invertir el orden de `tl` y `tr` cuando se mueve hacia la izquierda (`'L'`). Mantener siempre `tl <= tr` como los bordes izquierdo y derecho del intervalo y cambiar únicamente qué extremo recibe `'!'` (`tr` para `'R'`, `tl` para `'L'`) elimina errores por desfasaje (*off-by-one*).

---

## 4. Lógica Correcta & Código Limpio

- **Complejidad Temporal:** `O(n * m)` con `n * m <= 4 * 10^6`.
- **Complejidad Espacial:** `O(n)` por línea de salida.

```cpp
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long t;
    if (!(cin >> n >> m >> t)) return 0;

    for (int i = 0; i < m; ++i) {
        long long p, s, l;
        char d;
        cin >> p >> s >> d >> l;

        long long tl = (d == 'R') ? (p + t * s) : (p - t * s);
        long long tr = tl + l - 1;
        long long engine = (d == 'R') ? tr : tl;

        string line(n, '=');
        long long start = max(0LL, tl);
        long long end = min((long long)n - 1, tr);

        for (long long j = start; j <= end; ++j) {
            line[j] = (j == engine) ? '!' : '#';
        }
        cout << line << "\n";
    }

    return 0;
}
```
