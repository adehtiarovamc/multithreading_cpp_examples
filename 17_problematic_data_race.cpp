#include <iostream>
#include <thread>
#include <chrono>

struct Node {
    int data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(int value) {
        Node* newNode = new Node{value, nullptr, nullptr};
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void printList() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* head;
    Node* tail;
};

void thread1Func(DoublyLinkedList& list) {
    for (int i = 0; i < 5; ++i) {
        list.append(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void thread2Func(DoublyLinkedList& list) {
    for (int i = 5; i < 10; ++i) {
        list.append(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    DoublyLinkedList list;

    std::thread t1(thread1Func, std::ref(list));
    std::thread t2(thread2Func, std::ref(list));

    t1.join();
    t2.join();

    list.printList();

    return 0;
}

