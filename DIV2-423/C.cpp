#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int parents[10000010];
int nxt[10000010];

int fd(int u) {
    if(u == parents[u]) return u;
    else return parents[u] = fd(parents[u]);
}
void uni(int x, int y) {
    x = fd(x);
    y = fd(y);
    
    int tmp = max(nxt[x], nxt[y]);
    nxt[x] = tmp;
    nxt[y] = tmp;
    
    parents[y] = x;
}

char o[1000010];
char ans[10000010];

int main() {
    for(int i = 0; i < 10000010; i++) parents[i] = i;
    for(int i = 0; i < 10000010; i++) nxt[i] = i + 1;
    
    int n;
    scanf("%d",&n);
    int mxlen = 0;
    for(int i = 0; i < n; i++) {
        int m;
        scanf("%s %d", o, &m);
        int len = (int)strlen(o);
        for(int i = 0; i < m; i++) {
            int k;
            scanf("%d", &k);
            k--;
            if(mxlen < k + len) mxlen = k + len;
            
            int pre = -1;
            for(int j = k; ; j = nxt[fd(j)]) {
                if(j >= k + len) break;
                if(pre != -1) uni(pre, j);
                ans[j] = o[j - k];
                pre = j;
            }
        }
    }
    for(int i = 0; i < mxlen; i++) if(ans[i] == '\0') ans[i] = 'a';
    printf("%s\n", ans);
    return 0;
}

