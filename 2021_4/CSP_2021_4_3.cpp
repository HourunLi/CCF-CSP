#include<bits/stdc++.h>
using namespace std;
#define N 10005

int n, T_def, T_max, T_min;
string H;

struct IP{
    int state; // 0: free, 1: waiting fot allocation, 2 for occupied, 3 for expired
    int t;
    string owner; 
}ipPool[N];

void initIpPool() {
    for(int i = 1; i <= n; i++) {
        ipPool[i].state = 0;
        ipPool[i].owner = "";
        ipPool[i].t = 0;
    }
    return;
}

void updateIpState(int time) {
    for(int i = 1; i <= n; i++) {
        if(time >= ipPool[i].t)
            if(ipPool[i].state == 1) {
                ipPool[i].state = 0;
                ipPool[i].owner = "";
                ipPool[i].t = 0;
            }else if(ipPool[i].state == 2){
                ipPool[i].state = 3;
                ipPool[i].t = 0;
            }
    }
    return;
}
int getIpByOwner(string client) {
    for(int i = 1; i <= n; i++) {
        if(ipPool[i].owner == client) {
            return i;
        }
    }
    return 0;
}

int getTheLeastFreeIp() {
    for(int i = 1; i <= n; i++) {
        if(ipPool[i].state == 0) {
            return i;
        }
    }
    return 0;
}

int getTheLeastExpiredIp() {
    for(int i = 1; i <= n; i++) {
        if(ipPool[i].state == 3) {
            return i;
        }
    }
    return 0;
}

int main() {
    // freopen("./test.txt", "r", stdin);
    initIpPool();
    cin >> n >> T_def >> T_max >> T_min >> H;
    int t;
    cin >> t;
    string src, dst, type;
    int time, ip, expire;
    while(t--) {
        cin >> time >> src >> dst >> type >> ip >> expire;
        if(type != "DIS" && type != "REQ") continue;
        if(dst == "*" && type != "DIS") continue;
        if(dst == H && type == "DIS") continue;
        if(!(dst == H || dst == "*") && type != "REQ") continue;
        
        updateIpState(time);
        if(type == "DIS") {
            int ip = getIpByOwner(src);
            if(!ip) ip = getTheLeastFreeIp();
            if(!ip) ip = getTheLeastExpiredIp();
            if(!ip) continue;

            ipPool[ip].state = 1;
            ipPool[ip].owner = src;
            if(!expire) {
                ipPool[ip].t = time + T_def;
            }else{
                ipPool[ip].t = time + max(min(expire-time, T_max), T_min);
            }
            cout << H << " " << src << " OFR " << ip << " " << ipPool[ip].t << endl;   
        } else if (type == "REQ") {
            if(dst != H) {
                for(int i = 1; i <= n; i++) {
                    if(ipPool[i].state == 1 && ipPool[i].owner == src) {
                        ipPool[i].state = 0;
                        ipPool[i].owner = "";
                        ipPool[i].t = 0;
                    }
                }
                continue;
            }
            if(!(ip >= 1 && ip <= n && ipPool[ip].owner == src)) {
                cout << H << " " << src << " NAK " << ip << " " << 0 << endl;
                continue;
            }

            ipPool[ip].state = 2;
            if(!expire) {
                ipPool[ip].t = time + T_def;
            }else{
                ipPool[ip].t = time + max(min(expire-time, T_max), T_min);
            }
            cout << H << " " << src << " ACK " << ip << " " << ipPool[ip].t << endl;   
        }
    }
    return 0;
}