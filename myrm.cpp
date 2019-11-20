/**Created by Shiyu Wang; Student Number:250890597; Created on Thurs, Oct 3rd, 2019;
This is a functional main that takes command line arguments. This removes the given files listed as parameters to this command.**/

#include "File.h"
using namespace std;

int main(int argc,char* argv[]) {
    for(int i= 1; i< argc; i++){ //take a number of command line arguments and
        remove(argv[i]); //delete them
    }
    return 0;
}