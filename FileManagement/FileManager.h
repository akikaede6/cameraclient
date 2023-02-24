#ifndef _FILEMANAGEMENT_FILEMANAGER_H_
#define _FILEMANAGEMENT_FILEMANAGER_H_

#include "FileWriter.h"
#include <queue>
#include <QString>

class FileManager
{
public:
    FileManager(const std::string& directoryPath, const QString &bearing, const int& maxCount);
    ~FileManager();

    int  writeFile(const char* data, const uint64_t& size);

private:
    void initFileQue();

    std::queue<FileWriter>  itsFileWriters;
    int                     itsMaxFileCount;
    std::string             itsDirectoryPath;
};


#endif
