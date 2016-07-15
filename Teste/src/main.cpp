#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include "../diff-match-patch-cpp-stl-master/diff_match_patch.h"
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

#define INPUT_FILE_PATH "../files/input/"
#define OUTPUT_FILE_PATH "../files/output/"
#define EXECUTION_FILE_PATH "../files/exec/"
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

void clear(){
    vector<boost::filesystem::path> files;
    get_all(EXECUTION_FILE_PATH, ".ex", files);
    if(!files.empty()){
        for(int i=0; i < files.size(); i++){
          string path = OUTPUT_FILE_PATH + files[i].string();
          boost::filesystem::remove(path);
        }
    }
}

void getInputFiles(vector<path>& inputFiles){
  get_all(INPUT_FILE_PATH, INPUT_EXTENSION, inputFiles);
}

void getOutputFiles(vector<path>& inputFiles){
  get_all(OUTPUT_FILE_PATH, OUTPUT_EXTENSION, inputFiles);
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
  return dmp.diff_prettyHtml(dmp.diff_main(text1, text2, true));
}

string getFileNameWithoutExtension(path path){
  string fileName = path.string();
  std::string::size_type pos = fileName.find('.');
  return fileName.substr(0, pos);
}

void executeFile(path file){
    string command = "gnome-terminal -x sh -c '";
    command += "cd " PROGRAM_PATH ";";
    command += " ./"  PROGRAM_NAME;
    command += " < ../Teste/files/input/" + file.string();
    command += " > ../Teste/files/exec/" + getFileNameWithoutExtension(file) + ".ex'";

    system(command.c_str());

    usleep(20000);
}

wstring getOutput(path path){
  string fileName = getFileNameWithoutExtension(path) + ".ex";
  fileName = EXECUTION_FILE_PATH + fileName;
  return readFile(fileName.c_str());
}

wstring getExpectedOutput(path path){
    string fileName = getFileNameWithoutExtension(path) + ".out";
    fileName = OUTPUT_FILE_PATH + fileName;
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
      // cout << "HTML com o diff:" << endl;
      // cout << compute_diff(output, expectedOutput) << endl;;
    }
}

int main(){
  clear();
  vector<boost::filesystem::path> inputFiles;
  getInputFiles(inputFiles);

  for(int i=0; i < inputFiles.size(); i++){
      executeFile(inputFiles[i]);
      wstring expectedOutput = getExpectedOutput(inputFiles[i]);
      wstring output = getOutput(inputFiles[i]);
      bool hasChange = hasChanges(output, expectedOutput);

      printResult(inputFiles[i], hasChange, output,expectedOutput);
  }
}

//http://htmledit.squarefree.com/
