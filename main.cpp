#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QStatusBar>
#include <QSplitter>
#include <QSignalBlocker>

#include <stack>
#include <list>

struct HistoryEntry {
    QString action;
    QString preview;
    QString time;
};

class TextEditorWindow : public QMainWindow {
    Q_OBJECT

public:
    TextEditorWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Undo-Redo Text Editor");
        resize(1000, 650);

        editor = new QPlainTextEdit(this);
        editor->setPlaceholderText("Start typing here...");
        editor->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        undoButton = new QPushButton("Undo", this);
        redoButton = new QPushButton("Redo", this);
        clearButton = new QPushButton("Clear", this);
        openButton = new QPushButton("Open", this);
        saveButton = new QPushButton("Save", this);

        historyList = new QListWidget(this);
        historyList->setMinimumWidth(260);

        auto *topBar = new QHBoxLayout;
        topBar->addWidget(openButton);
        topBar->addWidget(saveButton);
        topBar->addStretch();
        topBar->addWidget(undoButton);
        topBar->addWidget(redoButton);
        topBar->addWidget(clearButton);

        auto *editorBox = new QGroupBox("Editor", this);
        auto *editorLayout = new QVBoxLayout(editorBox);
        editorLayout->addWidget(editor);

        auto *historyBox = new QGroupBox("Editing History (oldest first)", this);
        auto *historyLayout = new QVBoxLayout(historyBox);
        historyLayout->addWidget(historyList);

        auto *splitter = new QSplitter(this);
        splitter->addWidget(editorBox);
        splitter->addWidget(historyBox);
        splitter->setStretchFactor(0, 4);
        splitter->setStretchFactor(1, 1);

        auto *central = new QWidget(this);
        auto *layout = new QVBoxLayout(central);
        layout->addLayout(topBar);
        layout->addWidget(splitter);
        setCentralWidget(central);

        currentText = editor->toPlainText();
        addHistory("Editor ready", currentText);

        connect(editor, &QPlainTextEdit::textChanged, this, &TextEditorWindow::onTextChanged);
        connect(undoButton, &QPushButton::clicked, this, &TextEditorWindow::undo);
        connect(redoButton, &QPushButton::clicked, this, &TextEditorWindow::redo);
        connect(clearButton, &QPushButton::clicked, this, &TextEditorWindow::clearText);
        connect(openButton, &QPushButton::clicked, this, &TextEditorWindow::openFile);
        connect(saveButton, &QPushButton::clicked, this, &TextEditorWindow::saveFile);

        updateButtons();
        statusBar()->showMessage("Ready");
    }

private slots:
    void onTextChanged() {
        if (restoring) return;
        const QString newText = editor->toPlainText();
        if (newText == currentText) return;

        undoStack.push(currentText);
        currentText = newText;
        while (!redoStack.empty()) redoStack.pop();
        addHistory("Text edited", currentText);
        updateButtons();
        statusBar()->showMessage("Changes recorded", 1500);
    }

    void undo() {
        if (undoStack.empty()) return;
        redoStack.push(currentText);
        currentText = undoStack.top();
        undoStack.pop();
        restoreEditorText(currentText);
        addHistory("Undo", currentText);
        updateButtons();
        statusBar()->showMessage("Undo completed", 1500);
    }

    void redo() {
        if (redoStack.empty()) return;
        undoStack.push(currentText);
        currentText = redoStack.top();
        redoStack.pop();
        restoreEditorText(currentText);
        addHistory("Redo", currentText);
        updateButtons();
        statusBar()->showMessage("Redo completed", 1500);
    }

    void clearText() {
        if (editor->toPlainText().isEmpty()) return;
        editor->clear();
    }

    void openFile() {
        const QString path = QFileDialog::getOpenFileName(
            this, "Open Text File", QString(), "Text Files (*.txt);;All Files (*)");
        if (path.isEmpty()) return;

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Open failed", "Could not open the selected file.");
            return;
        }

        QTextStream in(&file);
        const QString loadedText = in.readAll();
        // Treat loading as a single undoable operation.
        if (loadedText != currentText) {
            undoStack.push(currentText);
            while (!redoStack.empty()) redoStack.pop();
            currentText = loadedText;
            restoreEditorText(currentText);
            addHistory("Opened: " + QFileInfo(path).fileName(), currentText);
            updateButtons();
        }
        statusBar()->showMessage("File opened", 2000);
    }

    void saveFile() {
        const QString path = QFileDialog::getSaveFileName(
            this, "Save Text File", "document.txt", "Text Files (*.txt);;All Files (*)");
        if (path.isEmpty()) return;

        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Save failed", "Could not save the selected file.");
            return;
        }

        QTextStream out(&file);
        out << editor->toPlainText();
        statusBar()->showMessage("File saved", 2000);
    }

private:
    QPlainTextEdit *editor{};
    QPushButton *undoButton{};
    QPushButton *redoButton{};
    QPushButton *clearButton{};
    QPushButton *openButton{};
    QPushButton *saveButton{};
    QListWidget *historyList{};

    std::stack<QString> undoStack;
    std::stack<QString> redoStack;
    std::list<HistoryEntry> history; // std::list is a doubly linked list.
    QString currentText;
    bool restoring = false;

    void restoreEditorText(const QString &text) {
        restoring = true;
        editor->setPlainText(text);
        restoring = false;
    }

    void addHistory(const QString &action, const QString &text) {
        QString preview = text;
        preview.replace('\n', ' ');
        if (preview.size() > 70) preview = preview.left(67) + "...";

        HistoryEntry entry{action, preview, QDateTime::currentDateTime().toString("hh:mm:ss")};
        history.push_back(entry);

        const QString line = entry.time + " | " + entry.action +
            (entry.preview.isEmpty() ? "" : " | " + entry.preview);
        historyList->addItem(line);
        historyList->scrollToBottom();
    }

    void updateButtons() {
        undoButton->setEnabled(!undoStack.empty());
        redoButton->setEnabled(!redoStack.empty());
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TextEditorWindow window;
    window.show();
    return app.exec();
}

#include "main.moc"
