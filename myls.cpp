/**Created by Shiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a functional main that takes command line arguments and print the files it contains if the argument is a
 directory. For other types of files, it will show the file's name, just as ls would. If no argument is given
 this function prints the contents of the current working directory. This function also supports the "-l" option
 which displays the content in a long format, try it, kinda of a hassle to implement.**/


#include "File.h"

using namespace std;

int main(int argc,char* argv[]){

    char cwd[50]; //prepare a block of memory for current working dir
    char * str; //prepare a pointer for that block of memory too
    char child[50]; //prepared a block of memory for each child of a directory
    char* r = child; //also the pointer for that newborn


    if(argc == 1){ //if no commandline argument given; case: myls
        File *f1 = new File(getcwd(cwd, sizeof(cwd))); //create an object for the current directory return by getcwd()
        int len = strlen(getcwd(cwd, sizeof(cwd))); //get its length

        for (auto i = f1->getChildren().begin(); i != f1->getChildren().end();++i ) { //for every child of this dir
            str = (*i)->getName(); //get its name
            int range = strlen((*i)->getName()); //get the length of its name

            for(int j = len+1, k =0; j < range+1;j++,k++){
                child[k] = *(str+j) ; //remove the part of the directory, leave just the child file name
            }
            cout << r << endl; //print the names of each child file
        }
    }

    else if(strcmp(argv[1],"-l")==0) { //if option -l is given


        if (argc == 2) { //case: myls -l

            File *f1 = new File(getcwd(cwd, sizeof(cwd))); //create an object for the current directory return by getcwd()
            int len = strlen(getcwd(cwd, sizeof(cwd)));//get its length

            for (auto i = f1->getChildren().begin(); i != f1->getChildren().end(); ++i) {//for every child of this dir
                str = (*i)->getName();//get its name
                int range = strlen((*i)->getName());//get the length of its name

                    for (int j = len + 1, k = 0; j < range + 1; j++, k++) {
                        child[k] = *(str + j);//remove the part of the directory, leave just the child file name
                    }

                    //print out the permission, owner name and ID, group name and ID, and block size for each child file
                cout << ((S_ISDIR((*i)->getType())) ? "d" : "-") << (((*i)->getType() & S_IRUSR) ? "r" : "-") <<
                (((*i)->getType() & S_IWUSR) ? "w" : "-") << (((*i)->getType() & S_IXUSR) ? "x" : "-") <<
                (((*i)->getType() & S_IRGRP) ? "r" : "-") << (((*i)->getType() & S_IWGRP) ? "w" : "-") <<
                (((*i)->getType() & S_IXGRP) ? "x" : "-") << (((*i)->getType() & S_IROTH) ? "r" : "-") <<
                (((*i)->getType() & S_IWOTH) ? "w" : "-") << (((*i)->getType() & S_IXOTH) ? "x" : "-")<< " "<<
                (*i)->getOwnerName()<<" "<<(*i)->getOwnerID()<<" "<< (*i)->getGname() << " "<<(*i)->getGroupID()<<
                " "<<(*i)->getBlockSize()<<" "<<r << endl;

                }
        }


        else { //case: myls -l filename
            File *f1 = new File(argv[2]);
            if (f1->getEN() == 0) { //make sure the child is born

                if (S_ISDIR(f1->getType())) {//case: myls -l directoryName
                    int len = strlen(argv[2]);

                    for (auto i = f1->getChildren().begin(); i != f1->getChildren().end(); ++i) { //for each child file
                        str = (*i)->getName();
                        int range = strlen((*i)->getName());

                        for (int j = len + 1, k = 0; j < range + 1; j++, k++) {
                            child[k] = *(str + j); //remove the path, extract just the file name
                        }

                        //print out the permission, owner name and ID, group name and ID, and block size for each child file
                        cout << ((S_ISDIR((*i)->getType())) ? "d" : "-") << (((*i)->getType() & S_IRUSR) ? "r" : "-") <<
                             (((*i)->getType() & S_IWUSR) ? "w" : "-") << (((*i)->getType() & S_IXUSR) ? "x" : "-") <<
                             (((*i)->getType() & S_IRGRP) ? "r" : "-") << (((*i)->getType() & S_IWGRP) ? "w" : "-") <<
                             (((*i)->getType() & S_IXGRP) ? "x" : "-") << (((*i)->getType() & S_IROTH) ? "r" : "-") <<
                             (((*i)->getType() & S_IWOTH) ? "w" : "-") << (((*i)->getType() & S_IXOTH) ? "x" : "-")
                             << " "<<(*i)->getOwnerName() << " " << (*i)->getOwnerID() << " " << (*i)->getGname() << " "
                             << (*i)->getGroupID() <<" " << (*i)->getBlockSize() << " " << r << endl;

                    }
                }


                else {//case: myls -l non-directoryName

                    File *f1 = new File(argv[2]);
                    if (f1->getEN() == 0) { //make sure the child is born successfully
                        //print out its information in a long format
                        cout << ((S_ISDIR(f1->getType())) ? "d" : "-") << ((f1->getType() & S_IRUSR) ? "r" : "-") <<
                             ((f1->getType() & S_IWUSR) ? "w" : "-") << ((f1->getType() & S_IXUSR) ? "x" : "-") <<
                             ((f1->getType() & S_IRGRP) ? "r" : "-") << ((f1->getType() & S_IWGRP) ? "w" : "-") <<
                             ((f1->getType() & S_IXGRP) ? "x" : "-") << ((f1->getType() & S_IROTH) ? "r" : "-") <<
                             ((f1->getType() & S_IWOTH) ? "w" : "-") << ((f1->getType() & S_IXOTH) ? "x" : "-") << " "
                             <<f1->getOwnerName() << " " << f1->getOwnerID() << " " << f1->getGname() << " "
                             << f1->getGroupID() <<" " << f1->getBlockSize() << " " << f1->getName() << endl;

                    }
                }
            }
        }
    }

    else{//arguments given without the option "-l"
        File *f2 = new File(argv[1]);
        if (f2->getEN() == 0) { //make sure the child is born successfully


            if (S_ISDIR(f2->getType())) {//case: myls directoryName
                for (auto i = f2->getChildren().begin(); i != f2->getChildren().end(); ++i)
                    cout << (*i)->getName() << "  "; //for each child, simply print its name

            }

            else {  //case: myls non-directoryName
                File *f1 = new File(argv[1]);
                if (f1->getEN() == 0) { //make sure the child is not dead
                    cout << argv[1] << endl; //echo the name
                }
            }
        }
    }
    return 0;
}