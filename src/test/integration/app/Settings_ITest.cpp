#ifndef CUTETALES_SETTINGS_ITEST_CPP
#define CUTETALES_SETTINGS_ITEST_CPP

#include <QtTest/QTest>
#include "app/Settings.h"

using namespace QTest;

#define DB_PATH "../../../../assets/testData/testdb.sqlite"
#define TEST_DB_PATH DB_PATH ".now"

class Settings_ITest : public QObject
{
Q_OBJECT

private slots:
    void init()
    {

    }

    void cleanup()
    {

    }

    void test_settingsSave()
    {

    }
};

QTEST_MAIN(Settings_ITest)
#include "Settings_ITest.moc"

#endif //CUTETALES_SETTINGS_ITEST_CPP
