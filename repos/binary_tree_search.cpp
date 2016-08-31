#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct Tree
{
    int value;
    Tree* left;
    Tree* right;
    Tree() {}
    Tree(int a, Tree* pl, Tree* pr) : value(a), left(pl), right(pr) {}
};

Tree* create_tree()
{
    // 10, 7  21,  38  57  13,  62
    Tree* t_3_0 = new Tree(62, NULL, NULL);
    Tree* t_2_1 = new Tree(57, NULL, NULL);
    Tree* t_2_2 = new Tree(13, NULL, NULL);
    Tree* t_2_0 = new Tree(38, t_3_0, NULL);
    Tree* t_1_0 = new Tree(7, t_2_0, t_2_1);
    Tree* t_1_1 = new Tree(21, t_2_2, NULL);
    Tree* root = new Tree(10, t_1_0, t_1_1);
    return root;
}

void pre_order_search(Tree* root)
{
    stack<Tree*> s;
    Tree* node = root;
    while (node != NULL || !s.empty()) {
        while (node != NULL) {
            cout << node->value << " ";
            s.push(node);
            node = node->left;
        }
        if (!s.empty()) {
            node = s.top();
            s.pop();
            node = node->right;
        }
    }
}

void in_order_search(Tree* root)
{
    stack<Tree*> s;
    Tree* node = root;
    while (node != NULL || !s.empty()) {
        while (node != NULL) {
            s.push(node);
            node = node->left;
        }
        if (!s.empty()) {
            node = s.top();
            cout << node->value << " ";
            s.pop();
            node = node->right;
        }
    }
}
void pre_order_search_recursion(Tree* root)
{
    if (root != NULL)
    {
        cout << root->value << " ";
        pre_order_search_recursion(root->left);
        pre_order_search_recursion(root->right);
    }
}

void in_order_search_recursion(Tree* root)
{
    if (root != NULL)
    {
        in_order_search_recursion(root->left);
        cout << root->value << " ";
        in_order_search_recursion(root->right);
    }
}

void post_order_search_recursion(Tree* root)
{
    if (root != NULL)
    {
        in_order_search_recursion(root->left);
        in_order_search_recursion(root->right);
        cout << root->value << " ";
    }
}

void width_first_search(Tree* root)
{
    queue<Tree*> q;
    Tree* node;
    q.push(root);
    while (!q.empty()) {
        node = q.front();
        cout << node->value << " ";
        q.pop();
        if(node->left != NULL)
            q.push(node->left);
        if(node->right != NULL)
            q.push(node->right);
    }
}

void depth_first_search(Tree *root)
{
    stack<Tree *> s;
    s.push(root);
    while (!s.empty())
    {
        root = s.top();
        cout << root->value << " ";
        s.pop();
        if (root->right != NULL)
            s.push(root->right);
        if (root->left != NULL)
            s.push(root->left);
    }
}

int main()
{
    // create tree
    Tree* root;
    root = create_tree();
    // pre-order
    cout << "Result of pre-order search: ";
    pre_order_search(root);
    cout << endl;
    cout << "Result of pre-order search (recursion): ";
    pre_order_search_recursion(root);
    cout << endl;
    // in-order
    cout << "Result of in-order search: ";
    in_order_search(root);
    cout << endl;
    cout << "Result of in-order search (recursion): ";
    in_order_search_recursion(root);
    cout << endl;
    // post-order search
    cout << "Result of post-order search (recursion): ";
    post_order_search_recursion(root);
    cout << endl;
    // width first search
    cout << "Width first search: ";
    width_first_search(root);
    cout << endl;
    depth_first_search(root);
    cout << endl;
    return 0;
}
