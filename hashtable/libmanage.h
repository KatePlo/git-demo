#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QWidget>
#include <QHash>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

struct Book {
    QString title;
    QString author;
};

class LibraryManager : public QWidget {
    Q_OBJECT

public:
    LibraryManager(QWidget *parent = nullptr);

private slots:
    void addBook();
    void removeBook();
    void findBook();
    void viewAllBooks();

private:
    QHash<QString, Book> bookHash;

    QLineEdit *isbnInput;
    QLineEdit *titleInput;
    QLineEdit *authorInput;

    QTableWidget *bookTable;

    // Объявление функции hashFunction
    int hashFunction(const QString &isbn);
};

#endif // LIBRARYMANAGER_H
