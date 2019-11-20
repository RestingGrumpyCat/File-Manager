/**author: Shiyu Wang; Created on Thurs, Oct 3rd, 2019;
This is a class whose every instance will represent a single file in the system with multiple attributes including
name, type, size etc. This class also contains support methods which operate on the file such as file rename function
and the function that compares contents of two files etc**/


#include "File.h"

using namespace std;

/**Function Name: File(); This function is the constructor which takes a filename as parameter and creates
 * an instance of the class. This function will obtain information from a file in the working directory with
 the name "filename" and store those information in different attributes. This function returns no value but will
 report an error message on operation failures.**/

File::File(char* filename){

    char* f = filename;  //assign pointer to filename
    char* n = name;      //assign pointer to name
    strcpy(name,filename); //use pointers to set the attribute name to parameter filename
    struct stat buf;
    if(stat(filename, &buf)==0){ //if stat() succeeds

        errorNum = 0;   //error code is 0 by default, representing successful operation
        type = buf.st_mode; //set each attribute with the value returned by stat()
        size = buf.st_size;
        ownerID = buf.st_uid;
        strcpy(ownerName,getpwuid(ownerID)->pw_name); //set owner name by the value returned from getpwuid()
        groupID = buf.st_gid;
        strcpy(groupName,getgrgid(groupID)->gr_name);
        permission = buf.st_mode;
        accessTime = buf.st_atime;
        modTime = buf.st_mtime;
        statusChangeTime = buf.st_ctime;
        blockSize = buf.st_blksize;

        if(S_ISDIR(type)){ //if this file is a directory, set children by the method expand()

            if(expand(filename)!= 0){//pass the filename and call expand(), report error if fail
                errorNum = errno;
                char *b = getES();
                cout<<b<<endl;
            }

        }
        else{
            //add nothing to the children vector if not a directory
        }

    }
    else{
        errorNum = errno; //set error number to be errno and print out error message if stat() fails
        char *e = getES();
        cout<<e<<endl;
    }

}


/**A destructor function, ~File(), that destroys and frees up any resources attached to the object the destructor
 * was called on. This function has neither parameter taken nor any return value.**/
File::~File(void){}


/**This function, expand(), operates on directories only and is used to fill in the children of the file object
 * this function was invoked upon. This function takes a filename as parameter. This function returns an error code,
 * indicating some kind of error except for 0 which represents a successful operation**/
int File::expand(char* filename) {


    char copy[50]; //prepare a block of memory
    std::fill(copy, copy+(50), 0); //clear this array before use
    char* k = copy;
    strcpy(k,filename); //create a copy of the filename
    strncat(k,"/",1); //append "/" to the filename so I can create relative path

    DIR *dirk;  //standard procedures for using opendir() and readdir()
    struct dirent *direntk;
    dirk = opendir(filename);

    if (dirk != NULL) { //make sure opendir() works successfully
        while ((direntk = readdir(dirk))!= NULL) { //make sure readdir() works successfully


            char* c = direntk->d_name; //obtain the children filename in the dir
            if(strcmp(c,".") == 0 ||strcmp(c,"..") == 0 ){ //filter out the the two unnecessary strings to report
                ;
            }
            else {
                strcat(k,c); //make up the relative file pathname

                File* file = new File(k); //create a new child for the vector
                children.push_back(file); //add the newborn to the vector
                strcpy(k," "); //clear the memory so next time we can fill it with new pathname

            }

        }

        closedir(dirk); //close directory as good practice
    }
    else { //if fail to open directory, report error
        errorNum = errno;
        char *e = getES();
        cout<<e<<endl;
    }

    return errorNum;

}

/**This function, dump(), will take a file stream as a parameter and dump the contents of the named file to that
 * file stream. This can be used to copy the file, display its contents to the terminal, and so on. Error message
 * will be reported on each failed operation. This function returns an error code, indicating some kinda of
 * error except for 0 which represents a successful operation**/
int File:: dump(ostream& myfile){

    ifstream input; //create input filestream so we can read file
    input.open(name, ios_base::in | ios_base::binary); //open the file for input and in binary mode so we can handle all different types of files

    if(input.is_open()) { //make sure the file has been open successfully

        char *m = new char[blockSize]; //allocate memory for file content
        while(input) { //use loop to read blocks of data
            input.read(m, blockSize); //read the file
            myfile.write(m, blockSize); //write the content into this file stream passed as parameter
        }
        delete[] m; //free memory

        input.close(); //close the file stream
    }
    else{//if fail to open the file, report the error
        errorNum = errno;
        char *e = getES();
        cout<<e<<endl;

    }
    return errorNum;

}

/**This function, reName(), changes the name of the file from its existing name to the new name provided as a parameter
 * to this function. In addition to changing the corresponding attribute of the file object in question, this will
 * change the name of the file on disk. This function returns an error code, indicating some kinda of error
 * except for 0 which represents a successful operation.**/
int File::reName(char* newname) {

    char* n =newname;
    char* old = name;

    if(rename(old,n)!=0){  //if rename() fails
        errorNum = errno; //report error
        char *e = getES();
        cout<<e<<endl;
    }


    int size = strlen(newname); //get length of the newname so we can use a loop
    for(int i = 0; i< size; i++) {
        name[i] = *(n+i); //set name to newname

    }

    return errorNum;
}



/**This function, remove(), removes the file from the file system. Both the physical file and the file object are deleted. This function
 * takes a filename as parameter and returns an error code, indicating some kind of error except for 0 which
 * represents a successful operation. **/

int File::remove(char* filename){

    if(unlink(filename)!=0){ //make sure unlink() is successful
        errorNum = errno; //if not report error message
        char *e = getES();
        cout<<e<<endl;

    }

    return errorNum;
}


/**This function, compare(), takes another one of the file objects as a parameter and will compare the contents of
 * the file object this function was invoked upon to this other file object. This function returns an error code,
 * indicating some kind of error except for 0 which represents a successful operation.  **/
int File::compare(File* file){

    int result;

    if(!S_ISREG(file->getType()))  //if this file is not a regular file, report error
        errorNum = ENOTSUP;

    else {  //if it is a regular file
        ifstream f1(name); //we create file streams for both files

        ifstream f2(file->getName());

        if(!f1.is_open() || !f2.is_open()) { //make sure both files open successfully, if not, report error message
            errorNum =errno;
            char* l = getES();
            cout<<l<<endl;
        }
        else{
            if(file->getBlockSize() != blockSize){ //if the blocksize is different, they're clearly different
                cout<<"Not the same!"<<endl; //report result
            }
            else{

                char buffer1[blockSize]; //if they have the same blocksize, prepare two memory blocks
                char buffer2[blockSize];

                for(int i =0; i< blockSize; i++){ //clear two memory blocks, so we can fill in with information
                    buffer1[i]=0;
                    buffer2[i]=0;
                }

                while(f1){ // while we haven't reached the end of the file
                    f1.read(buffer1,blockSize); //read both files
                    f2.read(buffer2,blockSize);
                    if(memcmp(buffer1,buffer2,blockSize) != 0) //and compare their contents
                        result = 1; //set result to be false

                    else
                        result = 0;//set result to be true

                }
                if(result == 1)
                    cout<<"Not the same!"<<endl;//report result
                else
                    cout<<"Same!"<<endl;

            }
        }

    }

    return errorNum;

}


