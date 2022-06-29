#include<bits/stdc++.h>
using namespace std;
// #define DEBUG

#ifdef DEBUG
#define print(...) printf(__VA_ARGS__)
#else
#define print(...)
#endif
int cnt[2];
struct Node{
    int health, attack, num;
    Node *next;
    Node(int health, int attack, int num) : health(health), attack(attack), num(num) {
        next = NULL;
    }
};
Node *players[2];
void addNode(int p, Node *follower, int pos) {
    Node *head = players[p];
    Node *now = head;
    while(--pos) {
        print("%p\n", now);
        now = now->next;
    }
    Node *next = now->next;
    now->next = follower;
    follower->next = next;

    now = follower->next;
    while(now) {
        now->num++;
        now = now->next;
    }
    cnt[p]++;
    return;
}

Node *getNode(int p, int pos) {
    Node *head = players[p];
    Node *now = head;
    while(pos--) {
        now = now->next;
    }
    return now;
}

void deleteNode(int p, int pos) {
    Node *head = players[p];
    Node *now = head;
    while(--pos) {
        now = now->next;
    }
    Node *next = now->next->next;
    delete now->next;
    now->next = next;
    now = now->next;
    while(now) {
        now->num--;
        now = now->next;
    }
    cnt[p]--;
    return;
}


void checklist(int p) {
#ifdef DEBUG
    Node *now = players[p];
    cout << "{" << now->health << ", " << now->attack << ", " << now->num << "}"; 
    now = now->next;
    while(now) {
        cout << " -> {" << now->health << ", " << now->attack << ", " << now->num << "}"; 
        now = now->next;
    }
    cout << endl;
#endif
    return;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    int player = 1;
    bool flag = false;
    cin >> n;
    players[0] = new Node(30, 0, 0);
    players[1] = new Node(30, 0, 0);
    string action;
    while(n--) {
        cin >> action;
        if(action == "summon") {
            print("summon\n");
            int pos, ata, health;
            cin >> pos >> ata >> health;
            if(flag) continue;
            Node *follower = new Node(health, ata, pos);
            addNode(player, follower, pos);
            checklist(player);
        } else if(action == "attack") {
            print("attack\n");
            int attackerPos, defenderPos;
            cin >> attackerPos >> defenderPos;
            if(flag) continue;
            Node *attacker = getNode(player, attackerPos);
            Node *defender = getNode(1-player, defenderPos);
            attacker->health -= defender->attack;
            defender->health -= attacker->attack;
            if(attacker->health <= 0) {
                deleteNode(player, attackerPos);
            }
            if(defender->health <= 0 && defenderPos > 0) {
                deleteNode(1-player, defenderPos);
            }
            if(players[1]->health <= 0 || players[0]->health <= 0) flag = true;
            checklist(player);
            checklist(1-player);
        } else if(action == "end") {
            print("end\n");
            player = 1 - player;
        }
    }

    if(players[0]->health > 0 && players[1]->health > 0) {
        cout << 0 << endl;
    } else if(players[0]->health > 0) {
        cout << -1 << endl;
    } else if(players[1]->health > 0) {
        cout << 1 << endl;
    }

   
    cout << players[1]->health << endl;
    cout << cnt[1];
    Node *now = players[1]->next;
    while(now) {
        cout << " " << now->health;
        now = now->next;
    }
    cout << endl;


    cout << players[0]->health << endl;
    cout << cnt[0];
    now = players[0]->next;
    while(now) {
        cout << " " << now->health;
        now = now->next;
    }
    return 0;
}