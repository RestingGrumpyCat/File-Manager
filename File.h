

/**author: Shiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a the header file for the class File.This header file contains all the private attributes a File object
 should have also methods which can be used on File objects.**/

#include <iostream>
#include <ostream>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>



#ifndef FILE_H
#define FILE_H

class File{

public:


    File(char* filename);
    ~File();

    //getter methods//
    char* getName(){ return name; }
    int getType(){ return type; }

    char* getOwnerName(){ return ownerName;}
    int getOwnerID(){ return ownerID;}

    char* getGname(){ return groupName; }
    int getGroupID(){ return groupID; }

    int getPermission(){ return permission; }
    std::vector<File*> getChildren(){ return children; }
    float getSize(){ return size; }
    time_t getAtime(){ return accessTime; }
    time_t getMtime(){ return modTime; }
    time_t getSCtime(){ return statusChangeTime; }
    int getBlockSize(){ return blockSize; }
    int getEN(){ return errorNum; }
    char* getES(){return strerror(errorNum); }
   //setter method
    void setName(char* newname){reName(newname);}


    int expand(char* filename);
    int dump(std::ostream& myfile);
    int reName(char* newName);
    int remove(char* filename);
    int compare(File* file);



private:

    char name[50];
    char ownerName[50];
    char groupName[50];
    int permission;
    std::vector<File*> children;
    float size;
    int blockSize;
    time_t accessTime, modTime, statusChangeTime;
    int type,ownerID, groupID;
    int errorNum;




};




#endif //FILE_H
