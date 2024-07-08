#include "libmanage.h"
#include <QLabel>
#include <QHashIterator>

LibraryManager::LibraryManager(QWidget *parent)
    : QWidget(parent) {

    // Создание полей ввода
    isbnInput = new QLineEdit(this);
    titleInput = new QLineEdit(this);
    authorInput = new QLineEdit(this);

    // Создание кнопок
    QPushButton *addButton = new QPushButton("Add Book", this);
    QPushButton *removeButton = new QPushButton("Remove Book", this);
    QPushButton *findButton = new QPushButton("Find Book", this);
    QPushButton *viewAllButton = new QPushButton("View All", this);

    // Подключение сигналов и слотов
    connect(addButton, &QPushButton::clicked, this, &LibraryManager::addBook);
    connect(removeButton, &QPushButton::clicked, this, &LibraryManager::removeBook);
    connect(findButton, &QPushButton::clicked, this, &LibraryManager::findBook);
    connect(viewAllButton, &QPushButton::clicked, this, &LibraryManager::viewAllBooks);

    // Создание таблицы для отображения книг
    bookTable = new QTableWidget(this);
    bookTable->setColumnCount(3);
    bookTable->setHorizontalHeaderLabels(QStringList() << "ISBN" << "Title" << "Author");

    // Создание и настройка макетов
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;

    inputLayout->addWidget(new QLabel("ISBN:"));
    inputLayout->addWidget(isbnInput);
    inputLayout->addWidget(new QLabel("Title:"));
    inputLayout->addWidget(titleInput);
    inputLayout->addWidget(new QLabel("Author:"));
    inputLayout->addWidget(authorInput);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(removeButton);
    mainLayout->addWidget(findButton);
    mainLayout->addWidget(viewAllButton);
    mainLayout->addWidget(bookTable);

    // Настройка главного окна
    setLayout(mainLayout);
    setWindowTitle("Library Manager");

    // Инициализация таблицы случайными значениями
    for (int i = 0; i < 10; ++i) {
        QString isbn = QString::number(rand() % 100000) + "-" + QString::number(rand() % 100000);
        QString title = "Book" + QString::number(i + 1);
        QString author = "Author" + QString::number(i + 1);
        bookHash.insert(isbn, {title, author});
    }
}

int LibraryManager::hashFunction(const QString &isbn) {
    // Простейшая хеш-функция для строк
    int hash = 0;
    for (QChar ch : isbn) {
        hash = (hash * 31 + ch.unicode()) % 1000; // Пример хеш-функции
    }
    return hash;
}

void LibraryManager::addBook() {
    QString isbn = isbnInput->text().trimmed();
    QString title = titleInput->text().trimmed();
    QString author = authorInput->text().trimmed();

    if (isbn.isEmpty() , title.isEmpty() , author.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled!");
        return;
    }

    if (bookHash.contains(isbn)) {
        QMessageBox::warning(this, "Duplicate ISBN", "A book with this ISBN already exists!");
        return;
    }

    Book newBook = {title, author};
    bookHash.insert(isbn, newBook);

    QMessageBox::information(this, "Book Added", "The book has been added successfully.");

    // Очистка полей ввода после добавления книги
    isbnInput->clear();
    titleInput->clear();
    authorInput->clear();
}

void LibraryManager::removeBook() {
    QString isbn = isbnInput->text().trimmed();

    if (isbn.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "ISBN must be filled!");
        return;
    }

    if (!bookHash.contains(isbn)) {
        QMessageBox::warning(this, "Book Not Found", "No book found with this ISBN!");
        return;
    }

    bookHash.remove(isbn);

    QMessageBox::information(this, "Book Removed", "The book has been removed successfully.");

    // Очистка поля ввода после удаления книги
    isbnInput->clear();
}

void LibraryManager::findBook() {
    QString isbn = isbnInput->text().trimmed();

    if (isbn.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "ISBN must be filled!");
        return;
    }
    if (!bookHash.contains(isbn)) {
        QMessageBox::warning(this, "Book Not Found", "No book found with this ISBN!");
        return;
    }

    Book foundBook = bookHash.value(isbn);
    QString bookDetails = QString("Title: %1\nAuthor: %2").arg(foundBook.title).arg(foundBook.author);
    QMessageBox::information(this, "Book Found", bookDetails);
}

void LibraryManager::viewAllBooks() {
    bookTable->setRowCount(0); // Очистка таблицы

    QHashIterator<QString, Book> i(bookHash);
    while (i.hasNext()) {
        i.next();
        int row = bookTable->rowCount();
        bookTable->insertRow(row);
        bookTable->setItem(row, 0, new QTableWidgetItem(i.key()));
        bookTable->setItem(row, 1, new QTableWidgetItem(i.value().title));
        bookTable->setItem(row, 2, new QTableWidgetItem(i.value().author));
    }
}
