#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int M = 1e4+10;
int m, Tdef, Tmax, Tmin, n;
string h;
struct IP{
    int state; //0:未分配；1:待分配；2:占用；3:过期
    int t;
    string owner;
} ip[M];

void update_ips_state(int tc) {
    for(int i = 1; i <= n; i++) {
        if(ip[i].t > 0 && ip[i].t <= tc) {
            if(ip[i].state==1) {
                ip[i].state = 0;
                ip[i].t = 0;
                ip[i].owner = "";
            } else {
                ip[i].state = 3;
                ip[i].t = 0;
            }
        }
    }
    return;
}

//检查是否有占用者为发送主机的ip
int get_ip_by_owner(string client) {
    for(int i = 1; i <= n; i++) 
        if(ip[i].owner == client)
            return i;
    return 0;
}
//选取特定状态的ip地址
int get_ip_by_state(int state) {
    for(int i=1;i<=n;i++) 
        if(ip[i].state == state)
            return i;
    return 0;
}

int main() {
    cin >> n >> Tdef >> Tmax >> Tmin >> h;
    cin >> m;
    while(m--) {
        int tc;
        string client,server,type;
        int id,te;
        cin >> tc >> client >> server >> type >> id >> te;
        if(server != h && server != "*") {
            if(type != "REQ") 
                continue;
        }
        if(type != "DIS" && type != "REQ")
            continue;
        if((server == "*" && type != "DIS") || (server == h && type == "DIS"))
            continue;

        update_ips_state(tc);
       
        if(type == "DIS") {
            int k = get_ip_by_owner(client);
            if(!k) 
                k = get_ip_by_state(0);
            if(!k) 
                k = get_ip_by_state(3);
            if(!k)
                continue;

            ip[k].state = 1;
            ip[k].owner = client;

            if(te == 0){
                ip[k].t = tc+Tdef;
            } else {
                int t = te-tc;
                //t不能小于最低时间也不能大于最长时间
                t = max(t, Tmin);
                t = min(t, Tmax);
                ip[k].t = tc + t;//更新过期时间
            }
            cout << h << " " << client << " OFR " << k << " " << ip[k].t << endl;
        } else {
            if(server != h) {
                for(int i = 1; i <= n; i++) {
                    if(ip[i].owner == client && ip[i].state == 1) {
                        ip[i].state = 0;
                        ip[i].owner = "";
                        ip[i].t = 0;
                    }
                }
                continue;
            }
            //2.检查ip地址是否在地址池中，且占有者为发送主机
            if(!(id >= 1 && id <=n && ip[id].owner == client)) {
                cout << h << " " << client << " NAK "<< id << " " << 0 << endl;
            } else {
                ip[id].state=2;
                if(te==0) {
                    ip[id].t = tc+Tdef;
                } else {
                    int t = te-tc;
                    t = max(t, Tmin);
                    t = min(t, Tmax);
                    ip[id].t = tc + t;
                }
                cout<< h << " " << client << " ACK " << id << " " << ip[id].t <<endl;
            }
        }
    }
    return 0;
}
