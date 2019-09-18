#include <cstdio>

int ans[200010][2];
int last[200010];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int m = (n - 1) / k;
    int r = (n - 1) % k;
    
    int tmp = 2;
    int sz = 0;
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < m; j++) {
            if(j == 0) ans[sz][0] = 1;
            else ans[sz][0] = tmp - 1;
            
            ans[sz][1] = tmp++;
            sz++;
        }
        last[i] = tmp - 1;
    }
    for(int i = 0; i < r; i++) {
        ans[sz][0] = last[i];
        ans[sz][1] = tmp++;
        sz++;
    }
    if(r == 0) printf("%d\n", m * 2);
    else if(r == 1) printf("%d\n", m * 2 + 1);
    else printf("%d\n", m * 2 + 2);
    for(int i = 0; i < sz; i++) printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}

