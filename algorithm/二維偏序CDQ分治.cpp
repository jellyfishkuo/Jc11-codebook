用途： 處理多維屬性限制下的計數問題（如二維/三維逆序對、動態 LIS）。先將第一維排序，再利用分治法結合雙指針（或 BIT）處理第二、三維。
#include <bits/stdc++.h>
using namespace std;
#define maxn 200005

struct Element {
    int a, b, c, id, cnt, ans;
    bool operator==(const Element& rhs) const {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }
};

Element arr[maxn], tmp[maxn];
int bit[maxn], res[maxn], N, max_val;

void add(int idx, int val) {
    for (; idx <= max_val; idx += idx & -idx) bit[idx] += val;
}
int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) sum += bit[idx];
    return sum;
}

// CDQ分治核心：計算左半邊對右半邊的貢獻
void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid); cdq(mid + 1, r);

    // 依第二維 b 屬性進行雙指針歸併排序
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (arr[i].b <= arr[j].b) {
            add(arr[i].c, arr[i].cnt); // 放入左側，更新 BIT 的第三維 c
            tmp[k++] = arr[i++];
        } else {
            arr[j].ans += query(arr[j].c); // 查詢左側有多少元素的 c 滿足條件
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid) { add(arr[i].c, arr[i].cnt); tmp[k++] = arr[i++]; }
    while (j <= r) { arr[j].ans += query(arr[j].c); tmp[k++] = arr[j++]; }
    for (int idx = l; idx <= mid; idx++) add(arr[idx].c, -arr[idx].cnt); // 還原 BIT
    for (int idx = l; idx <= r; idx++) arr[idx] = tmp[idx];
}