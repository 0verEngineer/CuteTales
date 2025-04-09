#ifndef CUTETALES_FILEPATHUTIL_UTEST_H
#define CUTETALES_FILEPATHUTIL_UTEST_H

#include <QtTest/QTest>
#include "app/utils/FilePathUtil.h"

using namespace QTest;

class FilePathUtil_UTest : public QObject
{
Q_OBJECT

private slots:
    void test_getFileName() {
        QString absoluteFilePath = "/home/user/.CuteTales/test.txt";
        QString fileName = FilePathUtil::getFileName(absoluteFilePath);
        QCOMPARE(fileName, QString("test.txt"));
    }

    void test_getNameAndPathCombined() {
        QString path = "/home/user/.CuteTales/";
        QString name = "test.txt";
        QString result = FilePathUtil::getNameAndPathCombined(path, name);
        QCOMPARE(result, QString("/home/user/.CuteTales/test.txt"));

        path = "/home/user/.CuteTales";
        result = FilePathUtil::getNameAndPathCombined(path, name);
        QCOMPARE(result, QString("/home/user/.CuteTales/test.txt"));
    }

    void test_appendSlashIfNotPresent() {
        QString path = "/home/user/.CuteTales";
        FilePathUtil::appendSlashIfNotPresent(path);
        QCOMPARE(path, QString("/home/user/.CuteTales/"));

        path = "/home/user/.CuteTales/";
        FilePathUtil::appendSlashIfNotPresent(path);
        QCOMPARE(path, QString("/home/user/.CuteTales/"));
    }
};

QTEST_MAIN(FilePathUtil_UTest)
#include "FilePathUtil_UTest.moc"

#endif //CUTETALES_FILEPATHUTIL_UTEST_H