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

wstring compute_diff(wstring text1, wstring text2){
  diff_match_patch<wstring> dmp;
  return dmp.diff_prettyHtml(dmp.diff_main(text1, text2, false));
}

void executeFile(path file){
    string command = "gnome-terminal -x sh -c '";
    command += "cd " PROGRAM_PATH ";";
    command += " ./"  PROGRAM_NAME;
    command += " < ../Teste/files/" + file.string();
    command += " > ../Teste/files/" TEMP_FILE "'";

    system(command.c_str());

    usleep(10000);
}

string getFileNameWithoutExtension(path path){
  string fileName = path.string();
  std::string::size_type pos = fileName.find('.');
  return fileName.substr(0, pos);
}

wstring getOutput(){
  string fileName = TEMP_FILE;
  fileName = FILE_PATH + fileName;
  return readFile(fileName.c_str());
}

wstring getExpectedOutput(path path){
    string fileName = getFileNameWithoutExtension(path) + ".out";
    fileName = FILE_PATH + fileName;
    return readFile(fileName.c_str());
}

bool hasChanges(wstring output, wstring expectedOutput){
    return expectedOutput.compare(output) != 0;
}

void printResult(path path, bool hasChange, wstring output, wstring expectedOutput){
    if(!hasChange){
      cout << path << ": " << "OK" << endl;
    }else{
      cout << path << ": " << "ERROOOUUU!" << endl;
      cout << "HTML com o diff:" << endl;
      cout << compute_diff(output, expectedOutput) << endl;;
    }
    cout << endl;
}

int main(){
  vector<boost::filesystem::path> inputFiles;
  vector<boost::filesystem::path> outputFiles;

  getInputFiles(inputFiles);
  getOutputFiles(outputFiles);

  for(int i=0; i < inputFiles.size(); i++){
      executeFile(inputFiles[i]);

      wstring expectedOutput = getExpectedOutput(inputFiles[i]);
      wstring output = getOutput();

      bool hasChange = hasChanges(output, expectedOutput);

      printResult(inputFiles[i], hasChange, output,expectedOutput);
  }
}

//http://htmledit.squarefree.com/
