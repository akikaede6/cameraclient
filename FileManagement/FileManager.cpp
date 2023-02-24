#include "FileManager.h"

#include <QDir>
#include <QDebug>

FileManager::FileManager(const std::string& directoryPath, const QString &bearing, const int& maxCount)
    : itsFileWriters(), itsMaxFileCount(maxCount), itsDirectoryPath(directoryPath)
{
    if (!QString(itsDirectoryPath.c_str()).endsWith("/"))
        itsDirectoryPath.append("/");
    itsDirectoryPath.append(bearing.toStdString());
    if (!QString(itsDirectoryPath.c_str()).endsWith("/"))
        itsDirectoryPath.append("/");
    initFileQue();
}

FileManager::~FileManager()
{
    if(!itsFileWriters.empty())
    {
        auto& fileWriter = itsFileWriters.back();
        if(fileWriter.isFileOpen())
        {
            fileWriter.closeFile();
        }
    }
}

int  FileManager::writeFile(const char* data, const uint64_t& size)
{
    if(itsFileWriters.empty() || itsFileWriters.back().isFileAlreadyExist() || itsFileWriters.back().isOutOfMaxSize())
    {
        itsFileWriters.emplace(itsDirectoryPath.c_str(), FileWriter::DEFAULT_MAX_SIZE);
        if(itsFileWriters.size() > itsMaxFileCount)
        {
            itsFileWriters.front().fileExpire();
            std::cout << "文件满了 删除最旧的" << std::endl;
            itsFileWriters.pop();//remove the oldest one
        }
    }

    auto& fileWriter = itsFileWriters.back();
    if(!fileWriter.isFileOpen() && fileWriter.openFile() < 0)
    {
        return -1;
    }

    int ret = fileWriter.writeFile(data, size);

    if(fileWriter.isOutOfMaxSize())
    {
        ret = fileWriter.closeFile();
    }
    return ret;
}

void FileManager::initFileQue()
{
    QDir dirinfo(itsDirectoryPath.c_str());
    if (!dirinfo.exists())
    {
        dirinfo.mkpath(itsDirectoryPath.c_str());
        std::cout << "Dir is nonexistence" << std::endl;
        return;
    }
    dirinfo.setNameFilters(QStringList("*.H264"));
    QStringList fileList = dirinfo.entryList(QDir::Files);

    fileList.removeOne(".");
    fileList.removeOne("..");

    for(auto& file : fileList)
    {
        std::cout << file.toStdString() << std::endl;
        itsFileWriters.emplace(itsDirectoryPath.c_str(), file.toStdString().c_str(), FileWriter::DEFAULT_MAX_SIZE);
    }
}
