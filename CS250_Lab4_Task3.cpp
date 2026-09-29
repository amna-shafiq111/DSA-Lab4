#include <iostream>
#include <string>
using namespace std;

struct BitNode
{
    int bit;
    BitNode* prev;
    BitNode* next;

    BitNode(int b)
    {
        bit = b;
        prev = nullptr;
        next = nullptr;
    }
};

class BinaryDLL
{
private:
    BitNode* head;
    BitNode* tail;

public:

    BinaryDLL()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~BinaryDLL()
    {
        clear();
    }

    void clear()
    {
        BitNode* current = head;

        while (current != nullptr)
        {
            BitNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = nullptr;
        tail = nullptr;
    }

    void appendBit(int bit)
    {
        BitNode* newNode = new BitNode(bit);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void fromString(string binary)
    {
        clear();

        for (char c : binary)
        {
            if (c == '0' || c == '1')
            {
                appendBit(c - '0');
            }
        }
    }

    string toString() const
    {
        string result;
        BitNode* current = head;

        while (current != nullptr)
        {
            result += char('0' + current->bit);
            current = current->next;
        }

        return result;
    }

    void display() const
    {
        BitNode* current = head;

        while (current != nullptr)
        {
            cout << current->bit;
            current = current->next;
        }

        cout << endl;
    }

    // 1's complement
    void onesComplement()
    {
        BitNode* current = head;

        while (current != nullptr)
        {
            current->bit = 1 - current->bit;
            current = current->next;
        }
    }

    // Add 1 to the binary number
    void addOne()
    {
        BitNode* current = tail;
        int carry = 1;

        while (current != nullptr && carry == 1)
        {
            if (current->bit == 0)
            {
                current->bit = 1;
                carry = 0;
            }
            else
            {
                current->bit = 0;
                carry = 1;
            }

            current = current->prev;
        }

        if (carry == 1)
        {
            BitNode* newNode = new BitNode(1);

            newNode->next = head;

            if (head != nullptr)
                head->prev = newNode;

            head = newNode;

            if (tail == nullptr)
                tail = newNode;
        }
    }

    // 2's complement
    void twosComplement()
    {
        onesComplement();
        addOne();
    }

    // Convert binary to decimal
    long long toDecimal() const
    {
        long long decimal = 0;

        BitNode* current = head;

        while (current != nullptr)
        {
            decimal = decimal * 2 + current->bit;
            current = current->next;
        }

        return decimal;
    }

    // Binary addition
    static BinaryDLL add(const BinaryDLL& a, const BinaryDLL& b)
    {
        BinaryDLL result;

        BitNode* p = a.tail;
        BitNode* q = b.tail;

        int carry = 0;

        while (p != nullptr || q != nullptr || carry != 0)
        {
            int sum = carry;

            if (p != nullptr)
            {
                sum += p->bit;
                p = p->prev;
            }

            if (q != nullptr)
            {
                sum += q->bit;
                q = q->prev;
            }

            result.prependBit(sum % 2);

            carry = sum / 2;
        }

        return result;
    }

    void prependBit(int bit)
    {
        BitNode* newNode = new BitNode(bit);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Left shift
    void shiftLeft(int positions)
    {
        for (int i = 0; i < positions; i++)
        {
            appendBit(0);
        }
    }

    // Binary multiplication using repeated addition and shifting
    static BinaryDLL multiply(const BinaryDLL& a, const BinaryDLL& b)
    {
        BinaryDLL result;
        result.fromString("0");

        BinaryDLL multiplicand;
        multiplicand.fromString(a.toString());

        BitNode* current = b.tail;

        while (current != nullptr)
        {
            if (current->bit == 1)
            {
                BinaryDLL temp = add(result, multiplicand);
                result = temp;
            }

            current = current->prev;

            if (current != nullptr)
            {
                multiplicand.shiftLeft(1);
            }
        }

        return result;
    }
};

int main()
{
    BinaryDLL number;
    BinaryDLL secondNumber;

    int choice;

    do
    {
        cout << "\n========== BINARY ARITHMETIC MENU ==========\n";
        cout << "1. Store Binary Number\n";
        cout << "2. Display Binary Number\n";
        cout << "3. 1's Complement\n";
        cout << "4. 2's Complement\n";
        cout << "5. Binary Addition\n";
        cout << "6. Binary Multiplication\n";
        cout << "7. Binary to Decimal\n";
        cout << "8. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string binary;

            cout << "Enter binary number: ";
            cin >> binary;

            number.fromString(binary);

            cout << "Binary number stored successfully.\n";
        }

        else if (choice == 2)
        {
            cout << "Binary: ";
            number.display();
        }

        else if (choice == 3)
        {
            number.onesComplement();

            cout << "1's Complement: ";
            number.display();
        }

        else if (choice == 4)
        {
            number.twosComplement();

            cout << "2's Complement: ";
            number.display();
        }

        else if (choice == 5)
        {
            string binary;

            cout << "Enter second binary number: ";
            cin >> binary;

            secondNumber.fromString(binary);

            BinaryDLL result = BinaryDLL::add(number, secondNumber);

            cout << "Addition Result: ";
            result.display();
        }

        else if (choice == 6)
        {
            string binary;

            cout << "Enter second binary number: ";
            cin >> binary;

            secondNumber.fromString(binary);

            BinaryDLL result = BinaryDLL::multiply(number, secondNumber);

            cout << "Multiplication Result: ";
            result.display();
        }

        else if (choice == 7)
        {
            cout << "Decimal: "
                 << number.toDecimal()
                 << endl;
        }

        else if (choice == 8)
        {
            cout << "Exiting...\n";
        }

        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}