
/**Created byShiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a functional main that reads a number of command line arguments and create File objects for them. This
 also displays the content of the filr to the console**/

#include "File.h"

using namespace std;

int main(int argc,char* argv[]){

    for(int i = 1; i< argc; i++) {  //read a number of command line arguments
        File *f1 = new File(argv[i]); //create corresponding file objects for each argument
        f1->dump(std::cout); //display its content to the screen
        cout<<endl;
    }

    return 0;
}