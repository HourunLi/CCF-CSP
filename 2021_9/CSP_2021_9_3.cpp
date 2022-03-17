#include <bits/stdc++.h>
using namespace std;
#define INF 2E9

const int MAX = 1e3+5;
int N, S, P, T;
double dt;
double u, v, a, b, c, d;
int rn, rns;
int maxd;
double maxv = -INF, minv = INF;
int maxtime = -INF, mintime = INF;
int r[MAX];
vector<int> G[MAX<<1]; //用vector容器存放节点连接情况

struct ce{
    double u, v, a, b, c, d;
    int time; //神经元发射脉冲的次数
} ces[MAX];

struct mc{
    int s, t;
    double w;
    int D;
} mcs[MAX];


//
static unsigned long next1 = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    next1 = next1 * 1103515245 + 12345;
    return((unsigned)(next1/65536) % 32768);
}
//


int main(){
    rns = 0;
    cin>> N >> S >> P >> T;
    cin >> dt;
    while (rns < N) {
        // cin>> rn >> v >> u >> a >> b >> c >> d;
        scanf("%d %lf %lf %lf %lf %lf %lf", &rn, &v, &u, &a, &b, &c, &d);
        //更新的是每段时间的神经元信息
        for(int i = rns; i < rns + rn; i++) {
            ces[i].v=v;
            ces[i].u=u;
            ces[i].a=a;
            ces[i].b=b;
            ces[i].c=c;
            ces[i].d=d;
            ces[i].time=0;
        }
        rns += rn; //为了满足rn之和=rns
    }

    for(int i = 0; i < P; i++)
        // cin >> r[i];
        scanf("%d", &r[i]);

    for(int i = 0; i < S; i++) {
        scanf("%d %d %lf %d", &mcs[i].s, &mcs[i].t, &mcs[i].w, &mcs[i].D);
        // cin>> mcs[i].s >> mcs[i].t >> mcs[i].w >> mcs[i].D;
        maxd = max(maxd, mcs[i].D);
        G[mcs[i].s].push_back(i);//存放节点连接情况
    }
    int mod = maxd+1;
    vector<vector<double>> I(mod, vector<double>(N));
    // double **I = new double*[mod];
    // for(int i = 0; i < mod; i++) {
    //     I[i] = new double[N]();
    // }

    for(int k = 0; k < T; k++) {
        //Ik表示每时刻受到的脉冲之和 所以每次都要清零
        for(int i = 0; i < N; i++)
            I[(k+maxd)%mod][i] = 0;
        
        //脉冲过程的模拟
        for(int i = 0; i < P; i++) {
            int my = myrand();
            if(r[i] > my){
                for(int j = 0; j < G[N+i].size();j++) { //传向连接的所有神经元
                    mc m = mcs[G[N+i][j]];
                    I[(k+m.D)%mod][m.t] += m.w;
                }
            }
        }
        
        for(int i = 0; i < N; i++) {
            double v1 = ces[i].v;
            double u1 = ces[i].u;
            double a1 = ces[i].a;
            double b1 = ces[i].b;
            ces[i].v = v1 + dt * (0.04*v1*v1 + 5*v1 + 140 - u1) + I[k%mod][i];
            ces[i].u = u1 + dt*a1*(b1*v1 - u1);
            if(ces[i].v >= 30) {
                ces[i].time++;
                for(int j = 0; j < G[i].size(); j++) {
                    mc m = mcs[G[i][j]];
                    I[(k+m.D)%mod][m.t] += m.w;
                }
                ces[i].v = ces[i].c;
                ces[i].u += ces[i].d;
            }
        }
        
    }

    for(int i = 0; i < N; i++) {
        maxv = max(maxv, ces[i].v);
        minv = min(minv, ces[i].v);
        maxtime = max(maxtime, ces[i].time);
        mintime = min(mintime, ces[i].time);
    }
    cout << fixed <<setprecision(3) << minv << " " << maxv<< endl;
    cout << mintime << " " << maxtime << endl;
    return 0;
}

// #include <iostream>
// #include<vector>
// #include<map>
// #include<string>
// #include<set>
// #include<algorithm>
// #include<queue>
// using namespace std;
// double delay[1003][1003];   //每个结点在该时间步得到的(循环队列节约空间)
// double v[1001];  //每个结点的v值，当前时间步
// double u[1001];  //每个结点的u值，当前时间步
// double a[1001],b[1001],c[1001],d[1001];  //每个结点的常数
// int r[1001];  //发射结点的常数
// int f[1001];  //每个结点的发射次数
// struct ed
// {
//     int to;   //到达
//     double w;     //边容量
//     int D;
// };
// struct ed edge[1001];
// //和哪条边连接
// vector<ed> n_g[1001];
// vector<ed> r_g[1001];




// static unsigned long next_1 = 1;

// /* RAND_MAX assumed to be 32767 */
// int myrand(void) {
//     next_1 = next_1 * 1103515245 + 12345;
//     return((unsigned)(next_1/65536) % 32768);
// }


// int main()
// {
//     int N,S,P,T;
//     cin >> N >> S >> P >>T;
//     double delt;
//     cin >>delt;
//     int total = 0;
//     while(total < N)
//     {
//         int j;
//         cin >> j;
//         double v_1,u_1,a_1,b_1,c_1,d_1;
//         cin >> v_1 >> u_1 >> a_1 >> b_1 >> c_1 >> d_1;
//         for(int i = total;i < j + total ;i++)
//         {
//             v[i]  = v_1; u[i] = u_1; a[i] = a_1; b[i] = b_1; c[i] = c_1; d[i] = d_1;
//         }
//         total += j;
//     }
//     for(int j = 0;j<P;j++)
//         cin >> r[j];
//     int maxd = 0;
//     for(int j= 0;j<S;j++)
//     {
//         int s,t,D;
//         double w;
//         cin >> s >> t >> w >> D;
//         maxd = max(maxd,D);
//         struct ed y;
//         y.D = D; y.to =t ; y.w  = w;
//         if(s < N)
//         {
//             n_g[s].push_back(y);
//         }
//         else r_g[s - N].push_back(y);
//     }
//     for(int i = 0;i<N;i++)
//     {
//         f[i] = 0;
//                 for(int j = 0;j<=maxd;j++)
//             {
//                 delay[i][j] = 0;
//             }
//     }
//     int cur = 0;
//     for(int t = 1;t<=T;t++)
//     {
//         for(int  i = 0;i<N;i++)
//         {
//             double v_p = v[i];
//             double u_p = u[i];
//             v[i] = v_p  + delt * (0.04 * v_p * v_p + 5 * v_p + 140 - u_p) + delay[i][cur];  //接收当前脉冲
//             u[i] = u_p + delt * a[i] * (b[i] * v_p - u_p);
//             //cout << v[i] << endl;
//             if(v[i] >= 30)  //发送下一个脉冲
//             {
//                 v[i] = c[i];
//                 u[i] += d[i];
//                 for(int y = 0;y<n_g[i].size();y++)
//                 {
//                     struct ed x = n_g[i][y];
//                     delay[x.to][(cur + x.D) % (maxd + 1)] += x.w;
//                 }
//                 f[i]++;
//             }
//             delay[i][cur] = 0;  //队首清零准备放入队尾
//         }

//         for(int i = 0;i<P;i++)
//         {
//             int  z = myrand();
//             if(r[i] > z)   //发射
//             {
//                 for(int y = 0;y<r_g[i].size();y++)
//                 {
//                     struct ed x = r_g[i][y];
//                     delay[x.to][(cur + x.D) % (maxd + 1)] += x.w;
//                 }
//             }
//         }
//         cur = (cur + 1) % (maxd + 1);
//     }
//     double v_min = 1e10;
//     double v_max = -1e10;
//     int f_min = 1e9;
//     int f_max = -1e9;
//     for(int i = 0;i<N;i++)
//     {
//         v_min = min(v_min,v[i]);
//         v_max = max(v_max,v[i]);
//         f_min = min(f_min,f[i]);
//         f_max = max(f_max,f[i]);
//     }
//     printf("%.3lf %.3lf\n%d %d\n",v_min,v_max,f_min,f_max);
//     return 0;
// }
