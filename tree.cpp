#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

struct Node {
    int val;
    Node *left;
    Node *right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<Node*> nodes;
void middleOrder(Node* root)
{
    if(root == NULL) return;
    middleOrder(root->left);
    nodes.push_back(root);
    cout << "debug:"<< root->val << endl;
    middleOrder(root->right);
}
Node* treeToDoublyList(Node* root) {
    middleOrder(root);
    if(nodes.size() == 0)
        return NULL;
    else if(nodes.size() == 1) {
        nodes[0]->left = nodes[0];
        nodes[0]->right = nodes[0];
        return nodes[0];
    }
    else {
        nodes[0]->left = nodes[nodes.size() - 1];
        nodes[0]->right = nodes[1];
        nodes[nodes.size() - 1]->left = nodes[nodes.size() - 2];
        nodes[nodes.size() - 1]->right = nodes[0];
        for(int i = 2; i < nodes.size() - 1; i++)
        {
            nodes[i]->left = nodes[i - 1];
            nodes[i]->right = nodes[i + 1];
        }
        return nodes[0];
    }
}

// Node* deserialize(string data) {
//     if (data == "null") {
//         return nullptr;
//     }
//     stringstream ss(data);
//     string token;
//     getline(ss, token, ',');
//     int val = stoi(token);
//     Node* root = new Node(val);
//     root->left = deserialize(ss.str());
//     root->right = deserialize(ss.str());
//     return root;
// }

Node* deserialize(string data) {
    // 将字符串转化为数字vector
    vector<string> vals;
    stringstream ss(data);
    string val;
    while (getline(ss, val, ',')) {
        vals.push_back(val);
    }
    reverse(vals.begin(), vals.end());  // 将vector倒置，便于后续操作

    // 使用一个队列，从底向上创建二叉树
    queue<Node*> q;
    Node *root = nullptr;
    while (!vals.empty()) {
        string val = vals.back();
        vals.pop_back();
        if (val != "null") {
            int num = stoi(val);
            Node *node = new Node(num);
            if (q.empty()) {
                root = node;
            } else {
                Node *parent = q.front();
                if (!parent->left) {
                    parent->left = node;
                } else {
                    parent->right = node;
                }
                if (parent->left && parent->right) {
                    q.pop();
                }
            }
            q.push(node);
        } else {
            q.push(nullptr);
        }
    }
    return root;
}

int main() {
    string data = "8,-6,null,-8";
    Node* root = deserialize(data);
    cout << root->left->left->val << endl;
    // 在此处添加对根节点的处理操作
    Node *ans = treeToDoublyList(root);
    for(int i = 0; i < nodes.size(); i++)
        cout << nodes[i]->val << " ";
    
    cout << endl;
    return 0;
}
