#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;


class Person {
public:
    string name;
    string ticket_number;

    Person(string name, string ticket_number) {
        this->name = name;
        this->ticket_number = ticket_number;
    }
};


class ConcertQueue {
private:
    queue<Person> q;
    int ticket_counter;
    mutex mtx;

public:
    ConcertQueue() : ticket_counter(1) {}

    void enqueue(string name) {
        lock_guard<mutex> lock(mtx);
        string ticket_number = "Ticket #" + to_string(ticket_counter);
        Person person(name, ticket_number);
        q.push(person);
        ticket_counter++;
        cout << person.name << " added to the queue with " << person.ticket_number << endl;
        cout << "Queue size: " << size() << endl;
    }

    void autoDequeue() {
        while (true) {
            this_thread::sleep_for(chrono::minutes(1));
            dequeue();
        }
    }

    void dequeue() {
        lock_guard<mutex> lock(mtx);
        if (!q.empty()) {
            Person person = q.front();
            q.pop();
            cout << "Dequeue: " << person.name << " received a ticket (" << person.ticket_number << ")" << endl;
            cout << "Queue size: " << size() << endl;
            if (!q.empty()) {
                Person next_person = q.front();
                cout << "Next in line: " << next_person.name << " (" << next_person.ticket_number << ")" << endl;
            }
        } else {
            cout << "The queue is empty." << endl;
        }
    }

    bool isEmpty() {
        lock_guard<mutex> lock(mtx);
        return q.empty();
    }

    int size() {
        lock_guard<mutex> lock(mtx);
        return q.size();
    }

    void peek() {
        lock_guard<mutex> lock(mtx);
        if (!q.empty()) {
            Person next_person = q.front();
            cout << "Next in line: " << next_person.name << " (" << next_person.ticket_number << ")" << endl;
        } else {
            cout << "The queue is empty." << endl;
        }
    }

    void position(const string &identifier) {
        lock_guard<mutex> lock(mtx); 
        int position = 1;
        queue<Person> temp = q;
        while (!temp.empty()) {
            Person person = temp.front();
            temp.pop();
            if (person.name == identifier || person.ticket_number == identifier) {
                cout << person.name << " is currently at position " << position << " in the queue." << endl;
                return;
            }
            position++;
        }
        cout << "No person found with name or ticket number: " << identifier << endl;
    }
};


void menu() {
    ConcertQueue concertQueue;


    thread autoDequeueThread(&ConcertQueue::autoDequeue, &concertQueue);

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!" << endl;

    int choice;
    string name;
    string identifier;

    while (true) {
        cout << "\n1. Enqueue a person" << endl;
        cout << "2. Check your position in the queue" << endl;
        cout << "3. Exit" << endl;

        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << "Enter the name: ";
                getline(cin, name);
                concertQueue.enqueue(name);
                break;
            case 2:
                cout << "Enter your name or ticket number: ";
                getline(cin, identifier);
                concertQueue.position(identifier);
                break;
            case 3:
                cout << "Exiting the system. Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid option. Please choose 1, 2, or 3." << endl;
                break;
        }
    }

    autoDequeueThread.join();
}


int main() {
    menu();
    return 0;
}
