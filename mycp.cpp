
/**Created by Shiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a functional main that reads two command line arguments and create File object for first argument. This
 function is used to make a copy of a file from a source to a destination named as parameters to the
 command.**/

#include "File.h"

using namespace std;

int main(int argc,char* argv[]){

    if(argc != 3)  //make sure two arguments are passed
        cout<<"Two arguments are expected"<<endl;
    else{
        File *f1 = new File(argv[1]); //create a new File object for the first argument
        ofstream buffer;
        buffer.open(argv[2]); //create a file stream for output and open the file with the name of a second argument
        if(buffer.is_open()) { //make sure the file opens properly
            f1->dump(buffer); //dump file to the second file, namely copy the content to the second file
        }

        return 0;

    }
}