nclude <cstdio>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

string dist[2][256]; // 0 : no |,   1 : yes |

struct node {
    string s;
    int types;
    int state;
    node() { s = ""; types = 0; state = 0; }
    node(string s, int types, int state) { (this->s).assign(s); this->types = types; this->state = state; }
    const bool operator< (const node &a) const {
        if(s.length() == a.s.length()) return s > a.s;
        return s.length() > a.s.length();
    }
};

string ft[6] = { "x", "y", "z", "!x", "!y", "!z" };
int tt[6] = { 240, 204, 170, 255 ^ 240, 255 ^ 204, 255 ^ 170 };

int cmp(string &x, string &y) {
    if(x.length() < y.length()) return -1;
    if(x.length() > y.length()) return 1;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main() {
    int mxbit = (1 << 8) - 1;
    
    
    priority_queue<node> pq;
    
    for(int i = 0; i < 6; i++) pq.push(node(ft[i], 0, tt[i]));
    
    while(pq.size()) {
        node tmp = pq.top();
        pq.pop();
        if(dist[tmp.types][tmp.state].length()) continue;
        dist[tmp.types][tmp.state].assign(tmp.s);
        
        if(tmp.types == 0) {
            node sub;
            for(int i = 0; i < 6; i++) {
                sub.s = tmp.s + "&" + ft[i];
                sub.types = 0;
                sub.state = tmp.state & tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                
                sub.s = ft[i] + "&" + tmp.s;
                sub.types = 0;
                sub.state = tmp.state & tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                
                sub.s = tmp.s + "|" + ft[i];
                sub.types = 1;
                sub.state = tmp.state | tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                
                sub.s = ft[i] + "|" + tmp.s;
                sub.types = 1;
                sub.state = tmp.state | tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
            }
            
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 255; j++) {
                    if(dist[i][j].length() == 0) continue;
                    
                    string ss;
                    if(i == 1) ss = "(" + dist[i][j] + ")";
                    else ss = dist[i][j];
                    
                    sub.s = tmp.s + "&" + ss;
                    sub.types = 0;
                    sub.state = tmp.state & j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                    
                    sub.s = ss + "&" + tmp.s;
                    sub.types = 0;
                    sub.state = tmp.state & j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                    
                    sub.s = tmp.s + "|" + ss;
                    sub.types = 1;
                    sub.state = tmp.state | j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                    
                    sub.s = ss + "|" + tmp.s;
                    sub.types = 1;
                    sub.state = tmp.state | j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                }
            }
        }
        
        if(tmp.types == 1) {
            node sub;
            for(int i = 0; i < 6; i++) {
                sub.s = "(" + tmp.s + ")&" + ft[i];
                sub.types = 0;
                sub.state = tmp.state & tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                
                sub.s = ft[i] + "&(" + tmp.s + ")";
                sub.types = 0;
                sub.state = tmp.state & tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                
                sub.s = tmp.s + "|" + ft[i];
                sub.types = 1;
                sub.state = tmp.state | tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                
                sub.s = ft[i] + "|" + tmp.s;
                sub.types = 1;
                sub.state = tmp.state | tt[i];
                
                if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
            }
            
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 255; j++) {
                    if(dist[i][j].length() == 0) continue;
                    
                    string ss;
                    if(i == 1) ss = "(" + dist[i][j] + ")";
                    else ss = dist[i][j];
                    
                    sub.s = "(" + tmp.s + ")&" + ss;
                    sub.types = 0;
                    sub.state = tmp.state & j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                    
                    sub.s = ss + "&(" + tmp.s + ")";
                    sub.types = 0;
                    sub.state = tmp.state & j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                    
                    sub.s = tmp.s + "|" + ss;
                    sub.types = 1;
                    sub.state = tmp.state | j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                    
                    sub.s = ss + "|" + tmp.s;
                    sub.types = 1;
                    sub.state = tmp.state | j;
                    
                    if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
                }
            }
        }
        
        node sub;
        
        sub.s = "!(" + tmp.s + ")";
        sub.types = 0;
        sub.state = mxbit ^ tmp.state;
        
        if(dist[sub.types][sub.state].length() == 0) pq.push(sub);
    }
    
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        char cc[9];
        scanf("%s", cc);
        int sum = 0;
        for(int i = 0; i < 8; i++) {
            if(cc[i] == '0') continue;
            sum += 1 << i;
        }
        if(dist[1][sum].length() == 0 || cmp(dist[0][sum], dist[1][sum]) <= 0)
            printf("%s\n", dist[0][sum].data());
        else
            printf("%s\n", dist[1][sum].data());
    }
    return 0;
}

