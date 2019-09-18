#include <cstdio>
#include <cstring>
 
int tr[256];
int BIT[100010][13][13][4];
 
void update(int i, int v, int u, int val, int l) {
    i++;
    
    while(i <= 100005) {
        BIT[i][v][u][val] += l;
        i += i & (-i);
    }
}
 
int query(int i, int v, int u, int val) {
    i++;
    
    int sum = 0;
    
    while(i > 0) {
        sum += BIT[i][v][u][val];
        i -= i & (-i);
    }
    
    return sum;
}
 
char o[100010];
char u[100010];
 
int main() {
    tr['A'] = 0;
    tr['C'] = 1;
    tr['G'] = 2;
    tr['T'] = 3;
    scanf("%s", o);
    int n = (int)strlen(o);
    for(int i = 0; i < n; i++) for(int j = 1; j <= 10; j++) update(i, j, i % j, tr[o[i]], 1);
    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int q;
        scanf("%d", &q);
        if(q == 1) {
            int x;
            char c;
            scanf("%d", &x);
            x--;
            scanf(" %c", &c);
            for(int j = 1; j <= 10; j++) update(x, j, x % j, tr[o[x]], -1);
            o[x] = c;
            for(int j = 1; j <= 10; j++) update(x, j, x % j, tr[o[x]], 1);
        }
        else {
            int x, y;
            scanf("%d %d", &x, &y);
            x--;
            y--;
            scanf("%s", u);
            int len = (int)strlen(u);
            int ans = 0;
            for(int j = 0; j < len; j++) ans += query(y, len, (x + j) % len, tr[u[j]]) - query(x - 1, len, (x + j) % len, tr[u[j]]);
            printf("%d\n", ans);
        }
    }
    return 0;
}
