#include <QApplication>
#include "libmanage.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LibraryManager libraryManager;
    libraryManager.show();

    return app.exec();
}
