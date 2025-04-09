
#ifndef CUTETALES_FILEPATHUTIL_H
#define CUTETALES_FILEPATHUTIL_H

#include <QString>


class FilePathUtil
{
public:
    static QString getFileName(const QString& absoluteFilePath) {
        return absoluteFilePath.split("/").last();
    }

    static QString getNameAndPathCombined(const QString& path, const QString& name) {
        QString result = path;
        if (!result.endsWith("/"))
            result.append("/");
        return result.append(name);
    }

    static void appendSlashIfNotPresent(QString& path) {
        if (!path.endsWith("/"))
            path.append("/");
    }
};

#endif //CUTETALES_FILEPATHUTIL_H
