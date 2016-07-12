 // clang++ -I ../../Projeto2/boost_1_60_0/ main.cpp -o teste ../../Projeto2/boost_1_60_0/stage/lib/libboost_filesystem.a ../../Projeto2/boost_1_60_0/stage/lib/libboost_system.a
#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include "../diff-match-patch-cpp-stl-master/diff_match_patch.h"
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

#define FILE_PATH "../files/"
#define INPUT_EXTENSION ".in"
#define OUTPUT_EXTENSION ".out"
#define TEMP_FILE "temp_file.txt"
#define PROGRAM_PATH "../../Projeto2/"
#define PROGRAM_NAME "myparse"

using namespace std;
using namespace boost::filesystem;

// retirado de http://stackoverflow.com/questions/11140483/how-to-get-list-of-files-with-a-specific-extension-in-a-given-folder
// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories
void get_all(const path& root, const string& ext, vector<path>& ret)
{
    if(!exists(root) || !is_directory(root)) return;

    recursive_directory_iterator it(root);
    recursive_directory_iterator endit;

    while(it != endit)
    {
        if(is_regular_file(*it) && it->path().extension() == ext) ret.push_back(it->path().filename());
        ++it;
    }
}

void getInputFiles(vector<path>& inputFiles){
  get_all(FILE_PATH, INPUT_EXTENSION, inputFiles);
}

void getOutputFiles(vector<path>& inputFiles){
  get_all(FILE_PATH, OUTPUT_EXTENSION, inputFiles);
}

// https://github.com/leutloff/diff-match-patch-cpp-stl/blob/master/speedtest.cpp
wstring readFile(const char *filename) {
  std::wifstream file(filename);
  wstring text;
  getline(file, text, wstring::traits_type::to_char_type(wstring::traits_type::eof()));
  return text;
}

void compute_diff(wstring text1, wstring text2){
  diff_match_patch<wstring> dmp;
  wstring as = dmp.diff_prettyHtml(dmp.diff_main(text1, text2, false));
}

void executeFile(path file){
    string command = "gnome-terminal -x sh -c '";
    command += "cd " PROGRAM_PATH ";";
    command += " ./"  PROGRAM_NAME;
    command += " < ../Teste/files/" + file.string();
    command += " > ../Teste/files/" TEMP_FILE "'";

    system(command.c_str());

    usleep(50);
}

int main(){
  vector<boost::filesystem::path> inputFiles;
  vector<boost::filesystem::path> outputFiles;

  getInputFiles(inputFiles);
  getOutputFiles(outputFiles);

  for(int i=0; i < inputFiles.size(); i++){
      cout << inputFiles[i] << endl;
  }

  for(int i=0; i < outputFiles.size(); i++){
      cout << outputFiles[i] << endl;
  }
  string file = "../files/" + inputFiles[0].string();
  string filein = "../files/declaracao.in";
  string fileout = "../files/declaracao.in";
  wstring text1 = readFile(filein.c_str());
  wstring text2 = readFile(fileout.c_str());
  cout << text1.compare(text2);

    executeFile(inputFiles[0]);
  // compute_diff(readFile(filein.c_str()), readFile(fileout.c_str()));
}
