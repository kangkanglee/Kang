#include <iostream>
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

ListNode* reverse_list(ListNode* phead)
{
    ListNode* p_new_head;
    ListNode* p_previous = NULL;
    ListNode* p_next = NULL;
    ListNode* p_node = phead;
    while(p_node != NULL) {
        p_next = p_node->_pnext;
        p_node->_pnext = p_previous;
        if(p_next == NULL)
            p_new_head = p_node;
        p_previous = p_node;
        p_node = p_next;
    }
    return p_new_head;
}

ListNode* merge_list(ListNode* phead_1, ListNode* phead_2)
{
	ListNode* p_1;
	ListNode* p_2;
	ListNode* pnew_list_head;
	p_1 = phead_1;
	p_2 = phead_2;
	if(p_1->_value < p_2->_value) {
		pnew_list_head = p_1;
		p_1 = p_1->_pnext;
	}
	else {
		pnew_list_head = p_2;
		p_2 = p_2->_pnext;
	}
	ListNode* pnew_list_node = pnew_list_head;
	while(p_1 != NULL && p_2 != NULL) {
		if(p_1->_value <= p_2->_value) {
			pnew_list_node->_pnext = p_1;
			pnew_list_node = p_1;
			p_1 = p_1->_pnext;
		}
		else {
			pnew_list_node->_pnext = p_2;
			pnew_list_node = p_2;
			p_2 = p_2->_pnext;
		}
	}
	if(p_1 == NULL) {
		pnew_list_node->_pnext = p_2;
	}
	if(p_2 == NULL) {
		pnew_list_node->_pnext = p_1;
	}
	return pnew_list_head;
}

int main()
{
    //ListNode* phead;
    //ListNode first_node(100, NULL);
    //phead = &first_node;
    ListNode* phead_1 = new ListNode(10, NULL);
    //ListNode* phead = NULL;
    add_to_tail(phead_1, 20);
    add_to_tail(phead_1, 39);
    ListNode* phead_2 = new ListNode(8, NULL);
    //ListNode* phead = NULL;
    add_to_tail(phead_2, 28);
    add_to_tail(phead_2, 31);
    ListNode* new_list = merge_list(phead_1, phead_2);
    print_list(new_list);
    //add_to_tail(phead, 93);
    //delete_node(phead, 93);
    // print_reverse_list(phead);
    // phead = reverse_list(phead);
    // print_reverse_list(phead);
    //std::cout << "start";
    system("pause");
    return 0;
}
