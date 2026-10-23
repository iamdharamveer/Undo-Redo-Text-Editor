# Viva Questions and Answers

1. **What is the project?**  
   A GUI text editor with Undo, Redo, and editing history.

2. **Why is a stack used for Undo?**  
   Undo follows LIFO: the most recent previous state is restored first.

3. **Why do we need a Redo stack?**  
   It stores states that can be restored after an Undo operation.

4. **Why is the Redo stack cleared after a new edit?**  
   A new edit creates a different future, so the previous redo path is no longer valid.

5. **Which doubly linked list is used?**  
   `std::list<HistoryEntry>`, the C++ standard library's doubly linked list.

6. **What does a history entry contain?**  
   The action name, a short text preview, and a timestamp.

7. **What is LIFO?**  
   Last In, First Out.

8. **What is the time complexity of stack push and pop?**  
   O(1) for the stack operation itself, not counting text snapshot copying.

9. **What is the main limitation?**  
   It stores full text snapshots, which may use more memory for large documents.

10. **How can it be improved?**  
    Group keystrokes, store edit commands or diffs, add keyboard shortcuts, and preserve formatting.
