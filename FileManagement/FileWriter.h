#ifndef _FILEMANAGEMENT_FILEWRITER_H_
#define _FILEMANAGEMENT_FILEWRITER_H_

#include <iostream>

class FileWriter
{
public:
    FileWriter(const char* directory, const uint64_t& MaxSize = DEFAULT_MAX_SIZE);//create as a new file
    FileWriter(const char* directory, const char* fileName, const uint64_t& MaxSize = DEFAULT_MAX_SIZE);//create as an exist file
    ~FileWriter();

    bool isFileOpen();
    void fileJustOpened();
    void fileJustClosed();
    bool isOutOfMaxSize();
    int  openFile();
    int  writeFile(const char* data, const uint64_t& size);
    int  closeFile();
    bool removeFile();
    std::string createFileName(const char* directory);
    void asAnAlreadyExistFile(const char* fileName);
    bool isFileAlreadyExist();
    void fileExpire();

public:
    static constexpr auto DEFAULT_MAX_SIZE = 100*1024*1024; //100M

private:
    size_t getFileSize(const char *fileName);

    bool        isAnAlreadyExistFile;
    bool        isOpen;
    bool        isExpire;
    int         itsFileHandle;
    std::string itsFileName;
    uint64_t    itsSize;
    uint64_t    itsMaxSize;

};




#endif
