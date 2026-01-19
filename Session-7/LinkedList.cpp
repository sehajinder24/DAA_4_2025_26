#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* addAtEnd(Node* head, int val) {
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

Node* deleteAtEnd(Node* head) {
    if (head == NULL)
        return NULL;

    if (head->next == NULL) {
        delete head;
        return NULL;
    }

    Node* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    delete temp->next;
    temp->next = NULL;
    return head;
}

Node* findMiddle(Node* head) {
    if (head == NULL)
        return NULL;

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* reverse(Node* head) {
    if (head == NULL)
        return NULL;

    stack<Node*> st;
    Node* temp = head;

    while (temp != NULL) {
        st.push(temp);
        temp = temp->next;
    }

    head = st.top();
    st.pop();
    temp = head;

    while (!st.empty()) {
        temp->next = st.top();
        st.pop();
        temp = temp->next;
    }

    temp->next = NULL;
    return head;
}

void display(Node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* head = NULL;

    head = addAtEnd(head, 10);
    head = addAtEnd(head, 20);
    head = addAtEnd(head, 30);
    head = addAtEnd(head, 40);
    head = addAtEnd(head, 50);
	head = addAtEnd(head, 60);
	
	cout<<"Old Linked List\n";
    display(head);

    head = deleteAtEnd(head);
    Node* mid = findMiddle(head);
    cout << "Middle node after deletion of last node : " << mid->data << endl;
	
	cout <<"\nReversed list : ";
    head = reverse(head);
    display(head);

    return 0;
}

