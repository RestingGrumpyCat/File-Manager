/**Created by Shiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a functional main that takes command line arguments. This is used to move and rename files around.**/


#include "File.h"


using namespace std;

//this is to rename and move file around

int main(int argc,char* argv[]){

    if(argc != 3) //make sure two arguments are passed
        cout<< "Two arguments are expected!"<<endl;
    else{
        File *f1 = new File(argv[1]); //create a File object with the first argument

        if (f1->reName(argv[2]) != 0) {  //if rename() fails
            if (f1->getEN() == EXDEV) {   //is because two arguments given are at different file systems
                if (S_ISREG(f1->getType())) { //and the file is a regular file
                    ofstream myfile;
                    myfile.open(argv[1]);
                    f1->dump(myfile); //we copy the file to the file stream
                    f1->remove(argv[1]); //and delete the file
                }
                else{

                }

            }


        }



    }
    return 0;
}