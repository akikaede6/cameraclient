#include "FileWriter.h"
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

FileWriter::FileWriter(const char* directory, const uint64_t& MaxSize)
    : isAnAlreadyExistFile(false), isOpen(false), isExpire(false), itsFileHandle(0), itsFileName(), itsSize(0), itsMaxSize(MaxSize)
{
    itsFileName = createFileName(directory);
    std::cout << "Create file " << itsFileName << std::endl;
}

FileWriter::FileWriter(const char* directory, const char* fileName, const uint64_t& MaxSize)
    : isAnAlreadyExistFile(true), isOpen(false), isExpire(false), itsFileHandle(0), itsFileName(), itsSize(0), itsMaxSize(MaxSize)
{
    std::stringstream sstr;
    sstr << directory;
    sstr << fileName;
    itsFileName = sstr.str();
    itsSize = getFileSize(itsFileName.c_str());
    std::cout << itsFileName << "  get file size : " << itsSize << std::endl;
}

FileWriter::~FileWriter()
{
    if(isExpire)
    {
        std::cout << "Remove : " << itsFileName  << std::endl;
        removeFile();
    }
}

bool FileWriter::isFileOpen()
{
    return isOpen;
}

void FileWriter::fileJustOpened()
{
    isOpen = true;
}

void FileWriter::fileJustClosed()
{
    isOpen = false;
}

bool FileWriter::isOutOfMaxSize()
{
    return itsSize > itsMaxSize;
}

int  FileWriter::openFile()
{
    itsFileHandle = open(itsFileName.c_str(), O_RDWR | O_CREAT, O_RDWR);
    if (itsFileHandle < 0)
    {
        fileJustClosed();
        printf("open dst_file : %s failed\n", itsFileName.c_str());
    }
    else
    {
        printf("open dst_file : %s success\n", itsFileName.c_str());
        fileJustOpened();
    }
    return itsFileHandle;
}

int  FileWriter::writeFile(const char* data, const uint64_t& size)
{
    if(isFileOpen())
    {
        std::cout << "write" << std::endl;
        return write(itsFileHandle, data, size);//write to file
    }
    else
    {
        printf("file is close\n");
        return -1;
    }
}

int  FileWriter::closeFile()
{
    fileJustClosed();
    return ::close(itsFileHandle);
}

bool  FileWriter::removeFile()
{
    fileJustClosed();
    return remove(itsFileName.c_str()) == 0;
    return true;
}

bool FileWriter::isFileAlreadyExist()
{
    return isAnAlreadyExistFile;
}

void FileWriter::fileExpire()
{
    isExpire = true;
}

void FileWriter::asAnAlreadyExistFile(const char* fileName)
{
    isAnAlreadyExistFile = true;
    itsFileName = fileName;
}

std::string FileWriter::createFileName(const char* directory)
{
    time_t tt;
    struct tm *t;
    tt = time(0);
    t = localtime(&tt);
    char char_time[50] = {};
    sprintf(char_time, "%04d_%02d_%02d_%02d:%02d:%02d", t->tm_year + 1900,
            t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    std::string str_system_time = static_cast<std::string>(char_time);

    std::stringstream sstr;
    sstr << directory;
    sstr << "Camera_Record_";
    sstr << str_system_time;
    sstr << ".H264";

    return sstr.str();
}

size_t FileWriter::getFileSize(const char *fileName)
{
    if (fileName == NULL)
    {
        return 0;
    }
    struct stat statbuf;
    stat(fileName, &statbuf);
    return statbuf.st_size;
}

