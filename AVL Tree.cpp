#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    int height;
};

int max(int a, int b);

int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int val) {
    Node* node = new Node();
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Node* rrotation(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    return x;
}

Node* lrotation(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    return y;
}

int getbalnce(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
        height(N->right);
}

Node* insertNode(Node* node, int val) {
    if (node == NULL)
        return (newNode(val));
    if (val < node->val)
        node->left = insertNode(node->left, val);
    else if (val > node->val)
        node->right = insertNode(node->right, val);
    else
        return node;

    node->height = 1 + max(height(node->left),
        height(node->right));
    int balnce = getbalnce(node);
    if (balnce > 1) {
        if (val < node->left->val) {
            return rrotation(node);
        }
        else if (val > node->left->val) {
            node->left = lrotation(node->left);
            return rrotation(node);
        }
    }
    if (balnce < -1) {
        if (val > node->right->val) {
            return lrotation(node);
        }
        else if (val < node->right->val) {
            node->right = rrotation(node->right);
            return lrotation(node);
        }
    }
    return node;
}

Node* min(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int val) {
    if (root == NULL)
        return root;
    if (val < root->val)
        root->left = deleteNode(root->left, val);
    else if (val > root->val)
        root->right = deleteNode(root->right, val);
    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            Node* temp = min(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right,
                temp->val);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),
        height(root->right));
    int balnce = getbalnce(root);
    if (balnce > 1) {
        if (getbalnce(root->left) >= 0) {
            return rrotation(root);
        }
        else {
            root->left = lrotation(root->left);
            return rrotation(root);
        }
    }
    if (balnce < -1) {
        if (getbalnce(root->right) <= 0) {
            return lrotation(root);
        }
        else {
            root->right = rrotation(root->right);
            return lrotation(root);
        }
    }
    return root;
}

void printTree(Node* root) {
    if (root != nullptr){
        cout << root->val;
        printTree(root->left);
        printTree(root->right);
    }
}

int main() {
    Node* root = NULL;
    root = insertNode(root, 33);
    root = insertNode(root, 13);
    root = insertNode(root, 53);
    root = insertNode(root, 9);
    root = insertNode(root, 21);
    root = insertNode(root, 61);
    root = insertNode(root, 8);
    root = insertNode(root, 11);
    printTree(root);
    root = deleteNode(root, 13);
    cout << "\n-----------------" << endl;
    printTree(root);
}