#include <iostream>
using namespace std;

class Stack {
private:
    int top;
    int maxSize;
    int* stackArray;

public:
    Stack(int size) {
        maxSize = size;
        stackArray = new int[maxSize];
        top = -1;
    }

    ~Stack() {
        delete[] stackArray;
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == maxSize - 1);
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack is full. Cannot push " << value << "." << endl;
        } else {
            stackArray[++top] = value;
            cout << "Pushed " << value << " onto the stack." << endl;
        }
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop." << endl;
        } else {
            cout << "Popped " << stackArray[top--] << " from the stack." << endl;
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty. No top element." << endl;
            return -1;
        } else {
            return stackArray[top];
        }
    }
};

int main() {
    Stack myStack(5);

    cout << "Is empty?: " << myStack.isEmpty() << endl;
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    cout << "Is full?: " << myStack.isFull() << endl;
    myStack.push(40);
    myStack.push(50);
    cout << "Top element: " << myStack.peek() << endl;
    cout << "Is full?: " << myStack.isFull() << endl;
    myStack.pop();
    myStack.pop();
    cout << "Top element after popping: " << myStack.peek() << endl;
    myStack.push(60);

    return 0;
}
