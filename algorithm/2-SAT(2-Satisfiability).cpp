用途： 求解一組布林變數在滿足若干個 $x \lor y$ 形式的條件下是否有可行解。利用強連通分量（SCC Tarjan）來判斷與構造解。
// 核心：若 (A 或 B) 為真，則 (!A -> B) 且 (!B -> A) 建立有向邊
struct TwoSat {
    int n;
    vector<vector<int>> G;
    vector<int> dfn, low, scc, stack;
    int timer, scc_cnt;
    bitset<200005> in_stack;

    void init(int vars) {
        n = vars;
        G.assign(2 * n, vector<int>());
        dfn.assign(2 * n, 0); low.assign(2 * n, 0);
        scc.assign(2 * n, 0); timer = scc_cnt = 0;
    }
    void add_clause(int u, bool u_val, int v, bool v_val) {
        // u_val == true 代表變數為真，false 代表變數為假
        int x = u + (u_val ? 0 : n);
        int y = v + (v_val ? 0 : n);
        int not_x = u + (u_val ? n : 0);
        int not_y = v + (v_val ? n : 0);
        G[not_x].push_back(y);     // !x -> y
        G[not_y].push_back(x);     // !y -> x
    }
    void tarjan(int u) {
        dfn[u] = low[u] = ++timer;
        stack.push_back(u); in_stack[u] = true;
        for (int v : G[u]) {
            if (!dfn[v]) {
                tarjan(v); low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            scc_cnt++; int v;
            do {
                v = stack.back(); stack.pop_back();
                in_stack[v] = false; scc[v] = scc_cnt;
            } while (v != u);
        }
    }
    bool solve(vector<bool>& ans) {
        for (int i = 0; i < 2 * n; ++i) if (!dfn[i]) tarjan(i);
        ans.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (scc[i] == scc[i + n]) return false; // x 與 !x 在同個 SCC 中，無解
            ans[i] = (scc[i] < scc[i + n]); // 拓撲序較後的 SCC 形式即為可行解
        }
        return true;
    }
};