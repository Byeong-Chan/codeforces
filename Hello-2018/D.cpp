#include <cstdio>
#include <algorithm>

using namespace std;

struct node {
    int x;
    int pos;
    long long ti;
    const bool operator< (const node &a) const {
        return ti < a.ti;
    }
}o[200010];

int chk[200010];

int main() {
    int n;
    long long m;
    scanf("%d %lld", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d %lld", &o[i].x, &o[i].ti);
        o[i].pos = i;
    }
    sort(o, o + n);
    int l = 0, r = n;
    while(l <= r) {
        int mid = (l + r) >> 1;
        int sum = 0;
        long long lt = 0;
        for(int i = 0; i < n; i++) {
            if(sum == mid) break;
            if(o[i].x >= mid) {
                sum++;
                lt += o[i].ti;
            }
        }
        if(sum < mid || lt > m) r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", l - 1);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(sum == l - 1) break;
        if(o[i].x >= l - 1) {
            sum++;
            chk[o[i].pos] = 1;
        }
    }
    printf("%d\n", l - 1);
    for(int i = 0; i < n; i++) if(chk[i]) printf("%d ", i + 1);
    printf("\n");
    return 0;
}

