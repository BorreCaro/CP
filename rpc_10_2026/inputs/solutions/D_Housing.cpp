#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Node {
    int sum;
    int min_pref, max_pref;
    int min_suff, max_suff;
};

Node merge_nodes(const Node& L, const Node& R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.min_pref = min(L.min_pref, L.sum + R.min_pref);
    res.max_pref = max(L.max_pref, L.sum + R.max_pref);
    res.min_suff = min(R.min_suff, R.sum + L.min_suff);
    res.max_suff = max(R.max_suff, R.sum + L.max_suff);
    return res;
}

Node make_leaf(int val) {
    return {val, val, val, val, val};
}

int n;
vector<Node> tree;

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = make_leaf(1);
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        tree[node] = make_leaf(val);
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) update(2 * node, l, mid, idx, val);
    else update(2 * node + 1, mid + 1, r, idx, val);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    if (qr <= mid) return query(2 * node, l, mid, ql, qr);
    if (ql > mid) return query(2 * node + 1, mid + 1, r, ql, qr);
    return merge_nodes(
        query(2 * node, l, mid, ql, qr),
        query(2 * node + 1, mid + 1, r, ql, qr)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    vector<int> a(n + 1), pos(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    tree.resize(4 * n + 4);
    build(1, 1, n);

    vector<bool> ans(n + 1, false);

    // Barrido por valor creciente x = 1 .. n
    // Antes de procesar x: todo valor < x vale -1 y todo valor > x vale +1
    for (int x = 1; x <= n; ++x) {
        int i = pos[x];

        int minL = INF, maxL = -INF;
        int minR = INF, maxR = -INF;

        if (i > 1) {
            Node left_res = query(1, 1, n, 1, i - 1);
            minL = left_res.min_suff;
            maxL = left_res.max_suff;
        }
        if (i < n) {
            Node right_res = query(1, 1, n, i + 1, n);
            minR = right_res.min_pref;
            maxR = right_res.max_pref;
        }

        bool ok = false;
        if (minL <= 0 && maxL >= 0) ok = true; // Subarreglo [l..i] de balance 0 con l < i
        if (minR <= 0 && maxR >= 0) ok = true; // Subarreglo [i..r] de balance 0 con r > i
        if (maxL > 0 && minR < 0) ok = true;   // Balance +1 a la izquierda y -1 a la derecha
        if (minL < 0 && maxR > 0) ok = true;   // Balance -1 a la izquierda y +1 a la derecha

        ans[i] = ok;

        // Ahora el elemento x pasa a ser menor que los futuros x' > x
        update(1, 1, n, i, -1);
    }

    for (int i = 1; i <= n; ++i) {
        cout << (ans[i] ? "YES" : "NO") << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
