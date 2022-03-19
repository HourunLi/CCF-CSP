#include <bits/stdc++.h>
using namespace std;

static unsigned long next_ = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    next_ = next_ * 1103515245 + 12345;
    return((unsigned)(next_/65536) % 32768);
}

struct Neur {
    double v, u, a, b, c, d;
    int times; 
}neurs[1005];

struct Junction {
    int src, dst;
    double w;
    int D;
}junctions[1005];

int r[2005];
int size[2005];
int edge[2005][1005];  // edge between [neurs or pulses] and junctions
double **Ik;

int main() {
    // freopen("./test.txt", "r", stdin);
    int N, S, P, T;
    cin >> N >> S >> P >> T;
    double delta_T;
    cin >> delta_T;
    int cnt = 0;
    int t;
    double v_, u_, a_, b_, c_, d_;

    while(cnt < N) {
        // cin >> t >> v_ >> u_ >> a_ >> b_ >> c_ >> d_;
        scanf("%d %lf %lf %lf %lf %lf %lf", &t, &v_, &u_, &a_, &b_, &c_, &d_);
        for(int i = 0; i < t; i++) {
            neurs[cnt].v = v_;
            neurs[cnt].u = u_;
            neurs[cnt].a = a_;
            neurs[cnt].b = b_;
            neurs[cnt].c = c_;
            neurs[cnt++].d = d_;
        }
    }

    for(int i = N; i < N+P; i++) {
        // cin >> r[i];
        scanf("%d", &r[i]);
    }

    int maxMod = 0, mod = 0;
    for(int i = 0; i < S; i++) {
        // cin >> junctions[i].src >> junctions[i].dst >> junctions[i].w >> junctions[i].D;
        scanf("%d %d %lf %d", &junctions[i].src, &junctions[i].dst, &junctions[i].w, &junctions[i].D);
        edge[junctions[i].src][size[junctions[i].src]++] = i;
        maxMod = max(maxMod, junctions[i].D);
    }

    mod = maxMod + 1;
    Ik = new double *[mod];
    for(int i = 0; i < mod; i++) {
        Ik[i] = new double[1005]();
    }
    size_t sizeOfIk = sizeof(double) * 1005;
    // simulate
    for(int i = 0; i < T; i++) {
        int t = i%mod;
        for(int j = 0; j < N; j++) {
            double v = neurs[j].v;
            double u = neurs[j].u;
            neurs[j].v = v + delta_T*(0.04*v*v + 5*v + 140 - u) + Ik[t][j];
            neurs[j].u = u + delta_T*neurs[j].a*(neurs[j].b*v - u);
            if(neurs[j].v >= 30) {
                for(int l = 0; l < size[j]; l++) {
                    Junction junc = junctions[edge[j][l]];
                    Ik[(i + junc.D)%mod][junc.dst] += junc.w;
                }
                ++neurs[j].times;
                neurs[j].v = neurs[j].c;
                neurs[j].u += neurs[j].d;
            }
        }

        for(int j = N; j < N+P; j++) {
            int mrand = myrand();
            if (r[j] > mrand) {
                for(int l = 0; l < size[j]; l++) {
                    Junction junc = junctions[edge[j][l]];
                    Ik[(i + junc.D)%mod][junc.dst] += junc.w;
                }
            }
        }
        memset(Ik[t], 0, sizeOfIk);
    }

    int timeRetMax = INT_MIN, timeRetMin = INT_MAX;
    double v_max = timeRetMax, v_min = timeRetMin;

    for(int i = 0; i < N; i++) {
        v_max = max(neurs[i].v, v_max);
        v_min = min(neurs[i].v, v_min);
        timeRetMax = max(timeRetMax, neurs[i].times);
        timeRetMin = min(timeRetMin, neurs[i].times);
    }

    printf("%.3f %.3f\n", v_min, v_max);
    printf("%d %d\n", timeRetMin, timeRetMax);
    
    return 0;
}