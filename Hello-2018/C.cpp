#include <cstdio>
long long p[33];
int main() {
    int n;
    long long m;
    for(int i = 0; i < 31; i++) p[i] = 1ll << 60;
    scanf("%d %lld", &n, &m);
    for(int i = 0; i < n; i++) scanf("%lld", &p[i]);
    for(int i = 0; i < 30; i++) if((p[i] << 1) < p[i + 1]) p[i + 1] = p[i] << 1;
    
    long long ans = 1ll << 60, sum = 0;
    for(int i = 30; i >= 0; i--) {
        if(m - (1ll << i) > 0) {
            m -= 1ll << i;
            sum += p[i];
        }
        if(sum + p[i] < ans) ans = sum + p[i];
    }
    printf("%lld\n",ans);
    return 0;
}

