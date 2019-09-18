#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
 
using namespace std;
 
int psum[4096][64][4];
int tr[256];
 
char o[100010];
char u[13];
 
void update(int a, int x, int val, int l) {
    x++;
    for(int i = x; i < 64; i++) psum[a][i][val] += l;
}
 
int query(int a, int x, int val) {
    x++;
    return psum[a][x][val];
}
 
int main() {
    tr['A'] = 0;
    tr['G'] = 1;
    tr['C'] = 2;
    tr['T'] = 3;
    
    scanf(" %s", o);
    int n = (int)strlen(o);
    for(int i = 0; i < n; i++) update(i % 2520, i / 2520, tr[o[i]], 1);
    
    int m;
    scanf(" %d", &m);
    for(int i = 0; i < m; i++) {
        int q;
        scanf(" %d", &q);
        if(q == 1) {
            int x;
            char c;
            scanf(" %d %c", &x, &c);
            x--;
            
            update(x % 2520, x / 2520, tr[o[x]], -1);
            o[x] = c;
            update(x % 2520, x / 2520, tr[o[x]], 1);
        }
        else {
            int x;
            int y;
            scanf(" %d %d", &x, &y);
            x--; y--;
 
            scanf(" %s", u);
            int ans = 0;
            int p = (int)strlen(u);
            for(int i = 0; i < min(p, y - x + 1); i++) {
                for(int j = (x + i) % 2520; j < 2520; j += p) {
                    if(j > y) continue;
                    int ty = y / 2520;
                    int tx = x / 2520;
                    if(y % 2520 < j) ty--;
                    if(x % 2520 > j) tx++;
                    if(tx > ty) continue;
                    ans += query(j, ty, tr[u[i]]) - query(j, tx - 1, tr[u[i]]);
                }
                for(int j = (x + i) % 2520 - p; j >= 0; j -= p) {
                    if(j > y) continue;
                    int ty = y / 2520;
                    int tx = x / 2520;
                    if(y % 2520 < j) ty--;
                    if(x % 2520 > j) tx++;
                    if(tx > ty) continue;
                    ans += query(j, ty, tr[u[i]]) - query(j, tx - 1, tr[u[i]]);
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
