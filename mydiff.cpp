/**Created by Shiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a functional main that reads two command line arguments and create File object for them. This
 function compares two files named as parameters to this command with one another and reports if they are the
 same or different. **/

#include "File.h"

using namespace std;

int main(int argc,char* argv[]){
    if(argc != 3)
        cout<<"Two arguments are expected!"<<endl;//make sure two arguments are passed
    else{
        File *f1 = new File(argv[1]); //create two File objects based on the arguments passed
        File *f2 = new File(argv[2]);

        f1->compare(f2); //call the method compare()

    }

    return 0;
}
