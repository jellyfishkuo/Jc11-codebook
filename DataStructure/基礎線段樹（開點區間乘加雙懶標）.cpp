用途： 原 codebook 僅有基礎加值，
此處提供標準的區間乘法、
區間加法與區間求和的雙標記下傳
（Push Down）模板。
#define maxn 100005
long long st[maxn << 2], mul[maxn << 2], add_tag[maxn << 2], data[maxn];
long long mod;

void push_up(int i) { 
    st[i]=(st[i<<1]+st[i<<1|1])%mod; }

void build(int l, int r, int i) {
    mul[i] = 1; add_tag[i] = 0;
    if (l == r) { 
        st[i] = data[l] % mod; 
        return; }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1); 
    build(mid + 1, r, i << 1 | 1);
    push_up(i);
}

// 核心雙標記下傳：先乘後加
void push_down(int i, int l, int r) {
    int mid = (l + r) >> 1;
    int ls = i << 1, rs = i << 1 | 1;
    if (mul[i] != 1) {
        st[ls] = (st[ls] * mul[i]) % mod; 
        mul[ls] = (mul[ls] * mul[i]) % mod;
        add_tag[ls] = (add_tag[ls] * mul[i]) % mod;
        st[rs] = (st[rs] * mul[i]) % mod; 
        mul[rs] = (mul[rs] * mul[i]) % mod;
        add_tag[rs] = (add_tag[rs] * mul[i]) % mod;
        mul[i] = 1;
    }
    if (add_tag[i] != 0) {
        st[ls] = (st[ls] + add_tag[i] * (mid - l + 1)) % mod; 
        add_tag[ls] = (add_tag[ls] + add_tag[i]) % mod;
        st[rs] = (st[rs] + add_tag[i] * (r - mid)) % mod; 
        add_tag[rs] = (add_tag[rs] + add_tag[i]) % mod;
        add_tag[i] = 0;
    }
}

void update(int ql, int qr, int l, int r, int i, long long v_mul, long long v_add) {
    if (ql <= l && r <= qr) {
        st[i] = (st[i] * v_mul + v_add * (r - l + 1)) % mod;
        mul[i] = (mul[i] * v_mul) % mod;
        add_tag[i] = (add_tag[i] * v_mul + v_add) % mod;
        return;
    }
    push_down(i, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) 
        update(ql, qr, l, mid, i << 1, v_mul, v_add);
    if (qr > mid) 
        update(ql, qr, mid + 1, r, i << 1 | 1, v_mul, v_add);
    push_up(i);
}