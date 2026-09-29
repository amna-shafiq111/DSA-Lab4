#include <iostream>
using namespace std;

struct Person
{
    int id;
    Person* next;

    Person(int i)
    {
        id = i;
        next = nullptr;
    }
};

class CircularList
{
private:
    Person* tail;

public:

    CircularList()
    {
        tail = nullptr;
    }

    ~CircularList()
    {
        if (tail == nullptr)
            return;

        Person* head = tail->next;
        Person* current = head;

        while (current != tail)
        {
            Person* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        delete tail;
        tail = nullptr;
    }

    // Create the circular linked list
    void createCircle(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            Person* newPerson = new Person(i);

            if (tail == nullptr)
            {
                tail = newPerson;
                tail->next = tail;
            }
            else
            {
                newPerson->next = tail->next;
                tail->next = newPerson;
                tail = newPerson;
            }
        }
    }

    // Solve the Josephus problem
    void josephus(int k)
    {
        if (tail == nullptr || k <= 0)
        {
            cout << "Invalid input." << endl;
            return;
        }

        Person* previous = tail;
        Person* current = tail->next;

        cout << "\n===== ELIMINATED ORDER =====" << endl;

        while (current != current->next)
        {
            // Move k - 1 positions
            for (int count = 1; count < k; count++)
            {
                previous = current;
                current = current->next;
            }

            // Eliminate current person
            cout << current->id << " ";

            previous->next = current->next;

            delete current;

            current = previous->next;
        }

        cout << "\n\nSurvivor: " << current->id << endl;

        delete current;
        tail = nullptr;
    }
};

int main()
{
    int n;
    int k;

    cout << "Enter number of people (N): ";
    cin >> n;

    cout << "Enter step count (k): ";
    cin >> k;

    if (n <= 0 || k <= 0)
    {
        cout << "N and k must be positive." << endl;
        return 0;
    }

    CircularList circle;

    circle.createCircle(n);

    circle.josephus(k);

    return 0;
}