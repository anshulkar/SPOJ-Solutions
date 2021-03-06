#include <iostream>
#include<map>
#include<queue>
#define INF 100000
#define FOR(i,a,b) for(i=(a);i<(b);++i)
#define FORE(i,a,b) for(i=(a);i<=(b);++i)
#define REP(i,n) FOR(i,0,n)
#define REPE(i,n) FORE(i,0,n)
#define VI vector<int>
#define PII pair<int,int>
#define gc getchar
#define PB push_back
#define MP make_pair
#define MSET(x,y) memset((x),(y),sizeof(x))
#define gc getchar
#include<cstdio>
#include<utility>
#include<vector>
#include<cstring>
#include<algorithm>
#define MX 4000
void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 | c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

using namespace std;
int cap[MX][MX];
int from[MX];
int n;
bool done[MX];
int aug(int s,int t)
{
    MSET(from,-1);
    bool reached=false;
    int i;
    MSET(done,false);
    queue<int> Q;
        Q.push(s);
        done[s]=true;
        while(!Q.empty())
        {
            int cur=Q.front();
            Q.pop();
            FOR(i,0,n)
            {
                if(cap[cur][i]>0&& !done[i])
                {
                    Q.push(i);
                    done[i]=true;
                    from[i]=cur;
                    if(i==t)
                    {
                        reached=true;
                        break;
                    }
                }
                if(reached)break;
            }
            if(reached)break;
        }
        if(reached){
            int bottle=INF;
            int cur=t;
            int prev=from[cur];
            while(prev!=-1)
            {

                bottle=min(bottle,cap[prev][cur]);
                cur=prev;
                prev=from[cur];
            }
            cur=t;
            prev=from[cur];
            while(prev!=-1)
            {
                cap[prev][cur]-=bottle;
                cap[cur][prev]+=bottle;
                cur=prev;
                prev=from[cur];
            }
            return bottle;
        }
        else return -1;
}
int maxflow(int s,int t)
{
    int cnt=0;
    int flow=0;
    while(1)
    {
        int f=aug(s,t);
        if(f==-1)break;
        cnt++;
        flow+=f;
    }
    return flow;
}

map<char,int> code;
int main()
{
    int m;
    int cur=0;
    scanint(m);
    int i;
    MSET(cap,0);
    REP(i,m)
    {
        char a,b;
        int c;
        cin>>a>>b>>c;
        if(code.count(a)==0) {code[a]=cur;cur++;}
        if(code.count(b)==0) {code[b]=cur;cur++;}
        cap[code[a]][code[b]]=c+cap[code[a]][code[b]];
        cap[code[b]][code[a]]=c+cap[code[b]][code[a]];
    }
    n=cur;
    cout<<maxflow(code['A'],code['Z'])<<endl;
    return 0;
}
