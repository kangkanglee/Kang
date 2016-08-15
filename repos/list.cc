nclude <iostream>
#include <stack>

using namespace std;

typedef struct ListNode *PtrToNode;

struct ListNode
{
    int _value;
    ListNode* _pnext;
    ListNode(int v = 0, ListNode* p = NULL) : _value(v), _pnext(p) {}
};

void add_to_tail(ListNode* phead, int d)
{
    ListNode *pnew = new ListNode(d, NULL);
    if (phead == NULL) {
        phead = pnew;
        return;
    }
    ListNode* pfinal = phead;
    while (pfinal->_pnext != NULL)
        pfinal = pfinal->_pnext;
    pfinal->_pnext = pnew;
}

bool delete_node(ListNode* phead, int d)
{
    if (phead == NULL)
        return false;
    else if (phead->_value == d) {
        phead = phead->_pnext;
    }
    else {
        ListNode* pnum = phead;
        while (pnum->_pnext != NULL && pnum->_pnext->_value != d)
            pnum = pnum->_pnext;
        if (pnum != NULL) {
            pnum->_pnext = pnum->_pnext->_pnext;
        }
    }
}

void print_list(ListNode* phead)
{
    ListNode* plist = phead;
    while (plist != NULL) {
        cout << plist->_value << endl;
        plist = plist->_pnext;
    }
}

void print_reverse_list(ListNode* phead)
{
    ListNode* plist = phead;
    stack<int> nums_stack;
    // push to stack
    while (plist != NULL) {
        nums_stack.push(plist->_value);
        plist = plist->_pnext;
    }
    // print
    while (!nums_stack.empty()) {
        int a = nums_stack.top();
        cout << a << endl;
        nums_stack.pop();
    }
}
int main()
{
    //ListNode* phead;
    //ListNode first_node(100, NULL);
    //phead = &first_node;
    ListNode* phead = new ListNode(100, NULL);
    //ListNode* phead = NULL;
    add_to_tail(phead, 0);
    add_to_tail(phead, 9);
    //add_to_tail(phead, 93);
    //delete_node(phead, 93);
    print_reverse_list(phead);
    //std::cout << "start";
    system("pause");
    return 0;
}
