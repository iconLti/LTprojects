#include <iostream>
using namespace std;

const int MAX_DIGITS = 10; // 0..9

// Structures block
// ________________________________________________________________________________________________
// ________________________________________________________________________________________________
struct Set {
    char el;        // Character (digit)
    Set* next;      // Pointer to the next el

    Set(char e, Set* n = nullptr) : el(e), next(n) { }

    ~Set() {
        delete next;
    }
};


//helper function
// ________________________________________________________________________________________________
bool contains(Set* head, char el) {
    Set* current = head;
    while (current != nullptr) {
        if (current->el == el) {
            return true;
        }
        current = current->next;
    }

    return false;
}
// ________________________________________________________________________________________________


//Function to create a set through user input
Set* createStructureFromInput() {
    Set* head = nullptr;
    Set* tail = nullptr;

    char input;

    //Input cycle
    cout << "Enter set digits, finish with 'x': ";
    while (cin >> input && input != 'x') {
        
        Set* newNode = new Set(input); // New element

        if (head == nullptr && !isalpha(input)) {
            head = newNode;
        } else if (!contains(head, input) && !isalpha(input)) {
            tail->next = newNode; // Change addres of the field "next" of the pen. el.
        } else {
            continue;
        }

        tail = newNode;
    }

    return head;
}


void outputSet(Set *head) {
    Set* current = head;
    while (current != nullptr) {
        cout << current->el << " ";
        current = current->next;
    }
    cout << endl;
}
// ________________________________________________________________________________________________
// ________________________________________________________________________________________________


//Intersection 
// ________________________________________________________________________________________________
Set* intersectSets(Set* A, Set* B, Set* C, Set* D) {
    Set* resultHead = nullptr;
    Set* resultTail = nullptr;

    Set *current = A;

    while (current != nullptr) {
        char el = current->el;

        // because of intersection --> check if present in all the oter sets
        if (contains(B, el) && contains(C, el) && contains(D, el)) {
            Set *newNode = new Set(el);

            if (resultHead == nullptr) {
                resultHead = newNode;
            } else {
                resultTail->next = newNode;
            }

            resultTail = newNode;
        }

        current = current->next;
    }


    return resultHead;
}
// ________________________________________________________________________________________________



int main() {

    cout << sizeof(bool) << endl;

    Set* A =nullptr, * B = nullptr, * C = nullptr, * D = nullptr;
    cout << "Create set 'A'" << endl;
    A = createStructureFromInput();
    
    cout << "Create set 'B'" << endl;
    B = createStructureFromInput();
    
    cout << "Create set 'C'" << endl;
    C = createStructureFromInput();
    
    cout << "Create set 'D'" << endl;
    D = createStructureFromInput();

    Set* E = intersectSets(A, B, C, D);

    cout << "\nSet A: "; outputSet(A);
    cout << "Set B: "; outputSet(B);
    cout << "Set C: "; outputSet(C);
    cout << "Set D: "; outputSet(D); cout << endl;

    if (E != nullptr) {
        cout << "Set E (the intesection of all sets): "; outputSet(E); cout << endl;
    } else {
        cout << "\nEmpty set.. :(" << endl;
    }
   

    delete A;
    delete B;
    delete C;
    delete D;
    delete E;

    cout <<"\n\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}