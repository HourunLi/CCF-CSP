#include<bits/stdc++.h>
using namespace std;

enum TYPE{
    NOT,
    AND,
    OR,
    XOR,
    NAND,
    NOR
};

bool visited[505];

struct Node {
    enum TYPE type;
    int in_num[7], num;
    char in_type[7];
    int in[7];
    int out;
} nodes[505];

int getResult(int *input, int number, char type) {
    if(type == 'I') {
        return input[number];
    } else if(visited[number]) {
        return nodes[number].out;
    }

    visited[number] = true;
    for(int i = 1; i <= nodes[number].num; i++) {
        nodes[number].in[i] = getResult(input, nodes[number].in_num[i], nodes[number].in_type[i]);
    }

    switch (nodes[number].type) {
        case NOT:
            nodes[number].out = 1 - nodes[number].in[1];
            break;
        case AND:
            nodes[number].out = 1;
            for(int i = 1; i <= nodes[number].num; i++) {
                nodes[number].out &= nodes[number].in[i];
            }
            break;
        case OR:
            nodes[number].out = 0;
            for(int i = 1; i <= nodes[number].num; i++) {
                nodes[number].out |= nodes[number].in[i];
            }
            break;
        case XOR:
            nodes[number].out = 0;
            for(int i = 1; i <= nodes[number].num; i++) {
                nodes[number].out ^= nodes[number].in[i];
            }
            break;
        case NAND:
            nodes[number].out = 1;
            for(int i = 1; i <= nodes[number].num; i++) {
                nodes[number].out &= nodes[number].in[i];
            }
            nodes[number].out = 1 - nodes[number].out;
            break;
        case NOR:
            nodes[number].out = 0;
            for(int i = 1; i <= nodes[number].num; i++) {
                nodes[number].out |= nodes[number].in[i];
            }
            nodes[number].out = 1 - nodes[number].out;
            break;
    }
    return nodes[number].out;
}

// bool judge(int N) {
//     for(int i = 0; i < N; i++) {
//         if(is_circle(i)){
//             return false;
//         }
//     }
//     return 
// }
int main() {
    int Q;
    // freopen("test.txt", "r", stdin);
    cin >> Q;
    while(Q--) {
        memset(nodes, 0, sizeof(Node) * 505);
        int M, N, k;
        string func;
        cin >> M >> N; // N is the number of elements in the, M is the number of input
        for(int i = 1; i <= N; i++) {
            cin >> func;
            if(func == "NOT") {
                nodes[i].type = NOT;
            } else if(func == "AND") {
                nodes[i].type = AND;
            } else if(func == "OR") {
                nodes[i].type = OR;
            } else if(func == "XOR") {
                nodes[i].type = XOR;
            } else if(func == "NAND") {
                nodes[i].type = NAND;
            } else if(func == "NOR") {
                nodes[i].type = NOR;
            }
            cin >> k;
            nodes[i].num = k;
            for(int j = 1; j <= k; j++) {
                cin >> nodes[i].in_type[j] >> nodes[i].in_num[j];
            }
        }
        int S;
        cin >> S;
        int **input = new int*[S+1];
        for(int j = 1; j <= S; j++) {
            input[j] = new int[M+1];
            for(int l = 1; l <= M; l++) {
                cin >> input[j][l];
            }
        }

        memset(visited, 0, sizeof(visited));
        // bool flag = judge();
        // if(flag){
        //     cout << "LOOP\n";
        // }

        int number, s_i;
        for(int j = 1; j <= S; j++) {
            // cout << "---------\n";
            cin >> s_i;
            memset(visited, 0, sizeof(visited));
            for(int l = 1; l <= s_i; l++) {
                cin >> number;
                // if(!flag) 
                    cout << getResult(input[j], number, 'O') << " ";
            }
            // if(!flag) 
                cout << endl;
            // for(int i = 1; i <= N; i++) {
            //     cout << visited[i] << " " << i << " " << nodes[i].out << endl;
            // }
            // cout << "----------\n";
        }
    }
    return 0;
}