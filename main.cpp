#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include<string>

using namespace std;

//FUNCTIONS FOR PASSING THE IMAGE
//ARGUMENT FORMAT FUNC(DATA, OUTPUT_FILENAME, SIZE)
void method_vector(vector<char>,char*,double );
void method_vector_pointer(vector<char>*,char *,double );
void method_vector_ref(vector<char>& , char * ,double );
void method_char(char*,char* ,double );

int main(int argc, char* argv[])
{

    if (argc != 4) //if total no. of arguments is not 4
    {   //then
        cerr << "COMMAND FORMAT:" //prompt ERROR and SHOW the COMMAND FORMAT
        << argv[0] // The command itself (<RunningFileName>)
        << " <input_image.bmp>"
        << " <output_image.bmp>"
        << " <USER_METHOD>" <<endl
        << "USER_METHOD: USE_VECTOR | USE_VECTOR_POINTER | USE_VECTOR_REF | USE_CHAR_ARRAY" <<endl;
        return 1;
    }

    long filesize=0;
    long beginfile, endfile; //integers for file sizing

    ifstream myfile; //imagefile input object
    myfile.open(argv[1], ios::in | ios::binary); //creating the file object

    if (myfile.is_open()) //Checking whether file was opened or not
    {
        myfile.seekg (0, ios::end); //Setting the pointer to the end
        endfile = myfile.tellg(); //Getting the current location of the pointer

        myfile.seekg (0, ios::beg); //Setting the pointer to the beginning
        beginfile = myfile.tellg(); //Location of the pointer

        filesize = endfile - beginfile; //filesize
        cout << "The file is "<<filesize/1024 <<" KBytes long."<<endl; // Displaying the file size
    }
    else
    {
        cout <<"File couldn't be open successfully.";
    }
    string user_method; //string for USE_OPTION
    string methods ("USE_VECTOR USE_VECTOR_POINTER USE_VECTOR_REF USE_CHAR_ARRAY"); //OPTIONS AVAILABLE
                    //OPTION POSITIONS ARE: 0, 11, 30, 45)
    int methodCharPosition=0; //variable for method first character position number in string "methods"
    user_method.assign(argv[3]); //Saving argv[3] in user_method string
    methodCharPosition=methods.find(user_method);   //find and compare user_method in methods string
                                                //and store the position of its first character
    vector<char> imagedata(filesize); //default image vector equal to filesize
    myfile.seekg(0, ios::beg); // point to beginning
    myfile.read(imagedata.data(),filesize); //read the file into the vector equal to filesize
    myfile.close(); //close the file object

    switch (methodCharPosition) //selecting the mode by switching according to user_method
    {
        case 0: //USE_VECTOR
            cout <<  endl <<"MODE: USE_VECTOR";
            method_vector(imagedata, argv[2], filesize); //method called
            break;
        case 11: //USE_VECTOR_POINTER
            cout<< endl << "MODE: USE_VECTOR_POINTER";
            method_vector_pointer(&imagedata, argv[2], filesize); //method called
            break;
        case 26: //USE_VECTOR_REF
            cout <<  endl << "MODE: USE_VECTOR_REF";
            method_vector_ref(imagedata, argv[2], filesize); //method called
            break;
        case 43: //USE_CHAR_ARRAY
            char *CharArrayImage;
            cout<< endl << "MODE: USE_CHAR_ARRAY";
            CharArrayImage = new char [filesize]; //memory space = filesize in bytes
            CharArrayImage = &(imagedata.at(0)); //CharMemory starts from first member of "imagedata"
            method_char(CharArrayImage, argv[2], filesize); //method called
            break;
        default:
            cout<< endl <<"WARNING: Option not available."; //Default case
    }

    return 0;
}

//===========================METHOD VECTOR ONLY==================================
void method_vector(vector<char> VectorOnly, char* OutputFileName,double filesize)
{
    ofstream OutputFile; //Output File Stream
    OutputFile.open(OutputFileName,ios::out | ios::binary); //Opening OutputFile
    double dstart = clock(); //Saving current clock
    for(long i = 0;i<filesize;i++) //For Loop to process image
    {
        if(i<54)
        OutputFile << VectorOnly[i];
        else
        OutputFile << char(255 - VectorOnly[i]); //inversion
    }
    double dDuration = clock() - dstart; //Calculating the req clocks
    cout <<endl<<"The File is processed in "<<dDuration/CLOCKS_PER_SEC << " secs." << endl; //File processing time
    OutputFile.close(); //closing the file
}



//===========================METHOD VECTOR POINTER==================================
void method_vector_pointer(vector<char>* VectorPointer,char *OutputFileName,double filesize)
{
    ofstream OutputFile; //Creating new file OutputFile
    OutputFile.open(OutputFileName,ios::out | ios::binary); //Opening OutputFile with OutputFileName as filename
    double dstart = clock(); //Saving current clock
    for(long i = 0;i<filesize;i++) //Processing image
    {
        if(i<54)
        OutputFile << VectorPointer->at(i);
        else
        OutputFile << char(255 - VectorPointer->at(i));
    }
    double dDuration = clock() - dstart; //Calculating the req clocks
    cout <<endl<<"The File is processed in "<<dDuration/CLOCKS_PER_SEC << " secs." << endl; //File processing time
    OutputFile.close(); //close the file
}

//===========================METHOD VECTOR REFERENCE==================================
void method_vector_ref(vector<char> &VectorReference, char *OutputFileName,double filesize)
{
    ofstream OutputFile; //Creating new file OutputFile
    OutputFile.open(OutputFileName,ios::out | ios::binary); //Opening OutputFile with OutputFileName as filename
    double dstart = clock(); //Saving current clock
    for(long i = 0;i<filesize;i++) //Processing image
    {
        if(i<54)
        OutputFile << VectorReference.at(i);
        else
        OutputFile << char(255 - VectorReference.at(i));
    }
    double dDuration = clock() - dstart; //Calculating the req clocks
    cout <<endl<<"The File is processed in "<<dDuration/CLOCKS_PER_SEC << " secs." << endl; //File processing time
    OutputFile.close(); //close the file
}

//===========================METHOD CHAR ARRAY==================================
void method_char(char* CharArrayImage,char* OutputFileName,double CSize)
{
    ofstream OutputFile; //Creating new file OutputFile
    OutputFile.open(OutputFileName,ios::out | ios::binary); //Opening OutputFile with OutputFileName as filename
    double dstart = clock(); //Saving current clock
    for(long i = 0;i<CSize;i++) //Processing image
    {
        if(i<54)
        OutputFile << CharArrayImage[i];
        else
        OutputFile << char(255 - CharArrayImage[i]);
    }
    double dDuration = clock() - dstart; //Calculating the req clocks
    cout <<endl<<"The File is processed in "<<dDuration/CLOCKS_PER_SEC << " secs." << endl; //File processing time
    OutputFile.close(); //close the file
}
