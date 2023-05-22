#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "unification.h"
#include <filesystem>
#include <dirent.h>
#include <direct.h>

using namespace std;
using namespace cv;

namespace fs = std::experimental::filesystem;

void loadFileList(string filename, vector<string> &img_sequence) {

    string folderpath = "./input/"+filename  ;
    cout << folderpath << endl;

    DIR* dir;
    struct dirent* ent;
    
    if ((dir = opendir(folderpath.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR)
                if ((string)ent->d_name != string(".") && (string)ent->d_name != string(".."))
                    img_sequence.push_back((string)ent->d_name);
        }
        closedir(dir);
    }
    else {
        /* could not open directory */
        perror("");
    }
    cout << "total number of images sequence = " << img_sequence.size() << endl;
    string result_dir = "./result/";
    _mkdir(result_dir.c_str());

    string dirname = result_dir + filename+"/";
    _mkdir(dirname.c_str());

    for (int i = 0; i < img_sequence.size(); i++) {
        _mkdir((dirname + img_sequence[i]).c_str());
    }
}

void main(int argc, char* argv[])
 {

    string input_dir = argv[1];

	cout<<"# Running CoColour ..."<<endl;
	clock_t start_time, end_time;

    vector<string> img_sequence;
    loadFileList(input_dir,img_sequence);
   
    for (int i = 0; i < img_sequence.size(); i++) {
       start_time = clock();
      
        string dataDir = "./input/" + input_dir + "/" + img_sequence[i];
        cout << dataDir << endl;
        vector<string> filePathList = Utils::get_filelist(dataDir);
        cout << "-Loaded " << filePathList.size() << " files." << endl;

        string result_dir = "./result/" +input_dir+"/"+ img_sequence[i] + "/";
        ToneUnifier unifier(filePathList, result_dir);

        unifier.unifyMultiTones();

        unifier.destroy();

        end_time = clock();
        cout << "# All done! Consumed " << double(end_time - start_time) / CLOCKS_PER_SEC << " seconds"<<endl <<endl;
    }

	//string dataDir = Utils::baseDir + "Images";
	//cout << dataDir << endl;
	//vector<string> filePathList = Utils::get_filelist(dataDir);
	//cout<<"-Loaded "<<filePathList.size()<<" files."<<endl;

	//ToneUnifier unifier(filePathList);   //! ToneUnifier LinearModel LinearGamma  
	//unifier.unifyMultiTones();

	//end_time = clock();
	//cout<<"# All done! Consumed "<<double(end_time-start_time)/CLOCKS_PER_SEC<<" seconds"<<endl;
}