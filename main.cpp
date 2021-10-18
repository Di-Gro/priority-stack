#include <iostream>
#include <vector>

#include "PriorityStack.h"

using namespace std;


int main() {
    PriorityStack<int> s;

    // вторая цифра - приоритет
    vector<int> vec1 = {
       11,21,31,41,51,61,
       12,22,32,42,52,62,
       13,23,33,43,53,63,
       14,24,34,44,54,64,
    };
    vector<int> vec2 = {
        12,22,32,42,52,62,
        14,24,34,44,54,64,
        13,23,33,43,53,63,
        11,21,31,41,51,61
    };

    cout << "target: ";
    for (int v : vec1)
        cout << v << " ";
    cout << "\n";

    cout << "  push: ";
    for (auto it = --vec2.end(); it >= vec2.begin(); it--) {
        cout << *it << " ";
        int p = *it % 10;
        s.Push(p, *it);
    }
    cout << "\n";

    bool success = true;

    cout << "   pop: ";
    for (int v : vec1) {
        if (s.IsEmpty()) {
            success = false;
            break;
        }
        int poped = s.Pop();
        cout << poped << " ";

        if (poped != v) {
            success = false;
            break;
        }
    }
    cout << "\n";

    if(!s.IsEmpty() || !success)
        cout << "Input and output arrays are not equal" << "\n";

}
