用途： 經典的可持久化資料結構。常用於在 
O(log n) 時間內查詢動態或靜態區間的第 K 小數。
// 區間第 K 小可持久化線段樹
struct PersistentSegmentTree {
    struct Node { int l, r, sum; } st[maxn * 40];
    int root[maxn], cnt;
    
    void init() { cnt = 0; root[0] = 0; st[0] = {0, 0, 0}; }
    
    int update(int pre, int l, int r, int x) {
        int dir = ++cnt; st[dir] = st[pre]; st[dir].sum++;
        if (l == r) return dir;
        int mid = (l + r) >> 1;
        if (x <= mid) st[dir].l = update(st[pre].l, l, mid, x);
        else st[dir].r = update(st[pre].r, mid + 1, r, x);
        return dir;
    }
    
    int query(int u, int v, int l, int r, int k) {
        if (l == r) return l;
        int count = st[st[v].l].sum - st[st[u].l].sum; 
        // 前綴和差值即為區間內的頻率
        int mid = (l + r) >> 1;
        if (k <= count) return query(st[u].l, st[v].l, l, mid, k);
        else return query(st[u].r, st[v].r, mid + 1, r, k - count);
    }
};