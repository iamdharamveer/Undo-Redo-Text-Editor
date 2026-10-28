# Undo-Redo Text Editor

## Project Information

- **Project Name:** Undo-Redo Text Editor
- **Project Type:** Team Project
- **Team Members:**
  1. Dharamveer Kushwaha — UID: 25BCS11049
  2. Sarvesh Gupta — UID: 25BCS10169
- **Subject:** Advance Data Structure
- **Subject Code:** 25CSH-202
- **Semester:** 3rd Semester
- **Academic Session:** July–December 2026
- **Programming Language:** C++
- **GUI Framework:** Qt Widgets
- **Build System:** CMake
- **Main Data Structures:** Stack and Doubly Linked List

## Project Overview

The Undo-Redo Text Editor is a team academic project developed to demonstrate how data structures can be used in a text-editing application. It provides a graphical interface for editing text and performing common operations.

The C++ desktop application uses two stacks to manage Undo and Redo operations. It also maintains editing history, including an action description, a short text preview, and the time of the action.

A separate browser-based version of the project is available through the live website.

## Project Links

- **GitHub Repository:** https://github.com/iamdharamveer/Undo-Redo-Text-Editor
- **Live Website:** https://iamdharamveer.github.io/Undo-Redo-Text-Editor/

The live website is a browser-based demonstration. The C++ Qt application is a separate desktop implementation.

## Objectives

- Develop a simple text editor with a graphical interface.
- Implement Undo and Redo operations using stacks.
- Maintain editing history using a list.
- Provide basic text editing, clearing, opening, and saving features.
- Understand the practical use of data structures in C++.

## Features

- **Text Editing:** Users can enter and modify text.
- **Undo:** Restores the previous text state when available.
- **Redo:** Restores a text state that was undone.
- **Editing History:** Displays recorded actions with a short text preview and timestamp.
- **Clear:** Removes the current text. The change can be undone.
- **Open File:** Opens a selected text file.
- **Save File:** Saves the current text to a file.
- **Status Messages:** Displays short messages about editing, Undo, Redo, opening, and saving.

## Data Structures Used

### 1. Stack

A Stack follows the LIFO (Last In, First Out) principle. The last item added is the first item removed.

The application uses two stacks:

- `undoStack` stores previous text states.
- `redoStack` stores text states that can be restored by Redo.

When the user edits text, the previous state is pushed onto the Undo stack. During Undo, the current state is pushed onto the Redo stack and the previous state is restored. During Redo, the current state is pushed onto the Undo stack and the undone state is restored.

### 2. Doubly Linked List

The C++ application uses `std::list<HistoryEntry>` to store editing history. Each history entry contains:

- `action`: the action performed, such as editing, Undo, or Redo.
- `preview`: a short preview of the text.
- `time`: the time when the action was recorded.

The interface displays history entries in a list.

## How the Application Works

### Edit Text

1. The previous text state is stored in `undoStack`.
2. The user enters new text.
3. The new text becomes the current text.
4. The Redo stack is cleared because a new edit creates a new editing path.
5. The action is recorded in history.

### Undo

1. The application checks whether `undoStack` is empty.
2. The current text is pushed onto `redoStack`.
3. The previous text is restored from `undoStack`.
4. The Undo action is added to history.

### Redo

1. The application checks whether `redoStack` is empty.
2. The current text is pushed onto `undoStack`.
3. The text is restored from `redoStack`.
4. The Redo action is added to history.

### Clear

The Clear button removes the text. The text-change handler records the change, allowing it to be undone.

### Open and Save

The Open button loads text from a selected file. The Save button writes the current text to a selected file.

## Requirements

To build the C++ desktop application, the computer needs:

- A C++ compiler.
- Qt 6 with the Qt Widgets component.
- CMake.
- Qt Creator or another compatible CMake development environment.

A standard online C++ compiler generally cannot run the Qt desktop application directly because it requires Qt and a graphical environment.

## How to Build and Run

### Using Qt Creator

1. Install Qt 6 with Qt Widgets and a compatible C++ compiler.
2. Install CMake if it is not already available.
3. Download or clone the repository.
4. Open the project's `CMakeLists.txt` file in Qt Creator.
5. Select a compatible build kit.
6. Configure and build the project.
7. Run the application.

### Clone the Repository

```bash
git clone https://github.com/iamdharamveer/Undo-Redo-Text-Editor.git
```

After cloning, open the project in Qt Creator and build it using the included `CMakeLists.txt` file.

## Sample Working Scenario

Suppose the user enters `Hello` and then changes the text to `Hello World`.

- **Undo:** Restores `Hello`.
- **Redo:** Restores `Hello World`.
- **Clear:** Removes the current text.
- **History:** Shows recorded actions and text previews.
- **Save:** Saves the current text to a file.

## Time Complexity Analysis

Let **L** be the length of the text and **H** be the number of history entries.

| Operation | Approximate Time Complexity | Explanation |
|---|---|---|
| Basic stack operations | O(1) | `push`, `pop`, and `top` are constant-time operations, excluding string copying. |
| Edit Text | O(L) | Text comparison and copying may depend on text length. |
| Undo | O(L) | Restoring a text state may require copying the string. |
| Redo | O(L) | Restoring an undone state may require copying the string. |
| Add History Entry | O(L) | The text preview is prepared and stored. |
| Display History | O(H) entries plus displayed text length | Each history entry is visited and displayed. |

The actual running time depends on the length of the text and the number of history entries.

## Project Files

The repository includes these main files. Additional files may be present.

- `main.cpp` — C++ source code for the desktop application.
- `CMakeLists.txt` — CMake build configuration.
- `README.md` — project information and instructions.
- `index.html` — browser-based demonstration.
- Project report files — written project documentation.
- `.nojekyll` — file used for GitHub Pages deployment when required.

## Limitations

- The application provides basic text-editing features rather than advanced word-processing tools.
- Undo and Redo store complete text states, which may use more memory for large documents.
- Editing history is maintained during the current application session.
- The history panel displays recorded actions and previews; it does not provide a complete timeline-navigation feature.
- The C++ desktop application and browser-based demonstration are separate implementations and may differ in features and appearance.

## Future Improvements

Possible future improvements include:

- Character-level Undo and Redo.
- Keyboard shortcuts such as Ctrl+Z and Ctrl+Y.
- Search and replace.
- Support for more file formats.
- Selecting a history entry to restore a state.
- Automated tests for editing, Undo, Redo, and file operations.

These are possible extensions, not claims about current features.

## Learning Outcomes

This project demonstrates:

- The LIFO principle of Stack.
- The use of two stacks for Undo and Redo.
- The use of a list to store editing history.
- C++ Standard Template Library containers.
- GUI development using Qt Widgets.
- Basic file handling and event-driven programming.
- The practical application of data structures.

## Team Members

**1. Dharamveer Kushwaha**  
UID: 25BCS11049

**2. Sarvesh Gupta**  
UID: 25BCS10169

**Subject:** Advance Data Structure  
**Subject Code:** 25CSH-202  
**Semester:** 3rd Semester  
**Project Type:** Team Academic Project
