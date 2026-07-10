用途： 用整數的二進制位元表示狀態集合，常用於旅行推銷員問題（TSP）或棋盤格子放置問題。
// 經典 TSP 問題：求解經過所有節點恰好一次的最短路徑
int dist_mat[20][20];
int dp[1 << 20][20]; // dp[被訪問節點集合 mask][當前所在的節點]

int solve_tsp(int n) {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; ++i) dp[1 << i][i] = 0; // 起點初始化
    
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue; // u 必須在目前的集合中
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue; // v 必須不在目前的集合中
                int next_mask = mask | (1 << v);
                dp[next_mask][v] = min(dp[next_mask][v], dp[mask][u] + dist_mat[u][v]);
            }
        }
    }
    return dp[(1 << n) - 1][0]; // 假設最終回到節點 0
}