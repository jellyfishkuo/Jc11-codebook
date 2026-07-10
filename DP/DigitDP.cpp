用途： 求解閉區間 [L, R] 中滿足特定條件
（如：不包含特定數位、特定數位出現次數、
特殊整除性質）的數字個數。
// 範例：
// 求在 [L, R] 之間有多少個數字不包含數位 '4'
int digits[20];
long long dp[20][2]; 
// dp[當前位數][是否受到上限限制]

long long dfs(int pos, bool limit, bool lead) {
    if (pos < 0) return 1; 
    // 成功構造一個合法數字
    if (!limit && !lead && dp[pos][0] != -1) 
        return dp[pos][0];
    
    int up = limit ? digits[pos] : 9;
    long long ans = 0;
    
    for (int i = 0; i <= up; ++i) {
        if (i == 4) continue; 
        // 剪枝：跳過不合法的數位
        ans += dfs(pos - 1, limit && (i == digits[pos]), lead && (i == 0));
    }
    
    if (!limit && !lead) 
        dp[pos][0] = ans;
    return ans;
}

long long solve(long long n) {
    int len = 0;
    while (n) { 
        digits[len++] = n % 10; 
        n /= 10; }
    memset(dp, -1, sizeof(dp));
    return dfs(len - 1, true, true);
}