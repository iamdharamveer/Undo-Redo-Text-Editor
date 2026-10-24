/*#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;
int main() {
    stack<string> undoStack, redoStack;
    vector<string> history;
    string text = "", newText;
    int choice;
    history.push_back(text);
    while (true) {
        cout << "\n\n--- UNDO-REDO TEXT EDITOR ---\n";
        cout << "Current Text: " << text << "\n";
        cout << "1. Edit Text\n";
        cout << "2. Undo\n";
        cout << "3. Redo\n";
        cout << "4. Show History\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            undoStack.push(text);
            cout << "Enter new text: ";
            getline(cin, newText);
            text = newText;
            while (!redoStack.empty())
                redoStack.pop();
            history.push_back(text);
            cout << "Text updated!\n";
        }
        else if (choice == 2) {
            if (!undoStack.empty()) {
                redoStack.push(text);
                text = undoStack.top();
                undoStack.pop();
                history.push_back(text);
                cout << "Undo successful!\n";
            } else {
                cout << "Nothing to undo!\n";
            }
        }
        else if (choice == 3) {
            if (!redoStack.empty()) {
                undoStack.push(text);
                text = redoStack.top();
                redoStack.pop();
                history.push_back(text);
                cout << "Redo successful!\n";
            } else {
                cout << "Nothing to redo!\n";
            }
        }
        else if (choice == 4) {
            cout << "\n--- EDITING HISTORY ---\n";
            for (int i = 0; i < history.size(); i++) {
                cout << i + 1 << ". ";

                if (history[i].empty())
                    cout << "[Empty Text]";
                else
                    cout << history[i];
                cout << "\n";
            }
        }
        else if (choice == 5) {
            cout << "Editor closed!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
*/
