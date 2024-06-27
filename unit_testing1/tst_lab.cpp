#include <QtTest>

// add necessary includes here

class lab : public QObject
{
    Q_OBJECT

public:
    lab();
    ~lab();

private slots:
    void test_case1();
};

lab::lab() {}

lab::~lab() {}

void lab::test_case1() {}

QTEST_APPLESS_MAIN(lab)

#include "tst_lab.moc"
