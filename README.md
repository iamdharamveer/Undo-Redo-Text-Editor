# Undo-Redo Text Editor (C++ / Qt Widgets)

## Features
- Type and edit text in a GUI.
- Undo and redo text changes using two stacks.
- Show a time-stamped editing history.
- Clear the editor.
- Open and save `.txt` files.
- `std::list` stores history entries; it is a doubly linked list.

## Requirements
- C++ compiler (C++17)
- CMake 3.16+
- Qt 6 with the Widgets module
- Qt Creator is recommended, but not required.

## Build with Qt Creator
1. Install Qt 6 and Qt Creator from the official Qt website.
2. Open `CMakeLists.txt` in Qt Creator.
3. Select a desktop kit (e.g. MinGW 64-bit on Windows, or GCC/Clang on Linux/macOS).
4. Configure the project, then click Run.

## Build from a terminal
Run these commands from this folder, in an environment where Qt 6 and CMake are available:

```bash
cmake -S . -B build
cmake --build build
```

Then run the generated executable from the build directory. Exact executable path depends on your operating system and selected Qt kit.

### Windows note
If CMake cannot find Qt, configure `CMAKE_PREFIX_PATH` to your Qt installation, for example:
```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/mingw_64"
cmake --build build
```
Replace the example path with the actual Qt installation path and use the compiler kit matching your Qt installation.

## How it works
- On each text change, the previous document snapshot is pushed onto `undoStack`.
- Undo moves the current text to `redoStack` and restores the most recent undo snapshot.
- Redo moves the current text back to `undoStack` and restores the latest redo snapshot.
- Any new edit clears the redo stack because the old redo path is no longer valid.
- Each edit/undo/redo is recorded in the history panel. `std::list<HistoryEntry>` provides doubly linked list storage.

## Test checklist
1. Type `Hello` — history should show edits.
2. Click Undo — text should return to the previous snapshot.
3. Click Redo — `Hello` should return.
4. Undo, then type a new character — Redo should be disabled.
5. Clear the text — it should be undoable.
6. Open a `.txt` file — its content should appear.
7. Save the content to a `.txt` file and verify it in a text editor.

## Known limitation
This educational version stores a full text snapshot per text-change event. For very large documents, this can use significant memory. A production editor would usually group keystrokes and/or store edit commands or text diffs.
