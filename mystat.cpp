/**Created by Shiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a functional main that his outputs all of the information on the file named as a parameter to this command. **/
#include "File.h"

using namespace std;


int main(int argc,char* argv[]){
    File *f1 = new File(argv[1]); //create the File object based on the argument passed

    //pull out filename and print out
    cout<<"File name: "<< f1->getName()<<endl; //as straightforward as it looks, prints out all the attributes

    //print out file type based on its type
    cout<<"File type: "<<(S_ISREG(f1->getType()) ? "Regular" : "")<<(S_ISDIR(f1->getType()) ? "Directory" : "")
    <<(S_ISCHR(f1->getType()) ? "Character Device" : "")<<(S_ISBLK(f1->getType()) ? "block device" : "")
    <<(S_ISFIFO(f1->getType()) ? "FIFO (named pipe)" : "")<<(S_ISLNK(f1->getType()) ? "symbolic link" : "")
    <<(S_ISSOCK(f1->getType()) ? "socket" : "")<<endl;

    cout<<"File size: "<< f1->getSize()<<endl;
    cout<<"File block size: "<<f1->getBlockSize()<<endl;

    cout<<"Owner name: "<< f1->getOwnerName()<<endl;
    cout<<"Owner ID: "<< f1->getOwnerID()<<endl;
    cout<<"Group name : "<< f1->getGname()<<endl;
    cout<<"Group ID: "<< f1->getGroupID()<<endl;

    cout<<"File permission: "<<((f1->getType() & S_IRUSR) ? "r" : "-")<<
        ((f1->getType() & S_IWUSR) ? "w" : "-") << ((f1->getType() & S_IXUSR) ? "x" : "-") <<
        ((f1->getType() & S_IRGRP) ? "r" : "-") << ((f1->getType() & S_IWGRP) ? "w" : "-") <<
        ((f1->getType() & S_IXGRP) ? "x" : "-") << ((f1->getType() & S_IROTH) ? "r" : "-") <<
        ((f1->getType() & S_IWOTH) ? "w" : "-") << ((f1->getType() & S_IXOTH) ? "x" : "-") << endl;


    cout<< "File Access time: "<<endl;
    cout<<f1->getAtime()<" seconds"<<"   "<<f1->getAtime().tv_nsec<<" nano seconds"<<endl;
    cout<< "File Modification Time: "<<endl;
    cout<<f1->getMtime()<<" seconds"<<"   "<<f1->getMtime().tv_nsec<<" nano seconds"<<endl;
    cout<< "File Status Change Time: "<<endl;
    cout<<f1->getSCtime()<<" seconds"<<"   "<<f1->getSCtime().tv_nsec<<" nano seconds"<<endl;



}