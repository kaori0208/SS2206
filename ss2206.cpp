#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

// Objectクラス作成
class Object{
    private:
    // txtファイルの内容をtupple型で記録する
    // vector<tupple<const string, string>> txtConfig = {{"Input",""},
    //                                                  {"Output",""},
    //                                                  {"ImageProcessing",""},
    //                                                  {"WindowProcessing",""},
    //                                                  {"WindowLevel",""}, 
    //                                                  {"WindowWidth",""},
    //                                                  {"MovingAverageFilterKernel",""},
    //                                                  {"MedianFilterKernel",""}};
    public:
    // Object();
    // ~Object();
    void LoadTxtFile(string file_name);
    // LoadMhdFile();
};
// Object::Object(){}
// Object::~Object(){}

// LoadTxtFile()関数　txtファイルから情報を読み取る関数
void Object::LoadTxtFile(string file_name){

    // テキストファイル読み込み
    ifstream reading_file;
    vector<string> lines;
    string line;
    reading_file.open(file_name);

    // ファイル読み込み　例外処理
    if(!reading_file.is_open()){
        cout << "Could not open file." << endl;
        exit(-1);
    }

    // テキストファイルの情報を読み取る
    while (getline(reading_file, line)){
        lines.push_back(line);
    }
    for (const auto &i : lines){
        cout << i << endl;
    }
    reading_file.close();
}

// LoadMhdFile()関数　mhdファイルから画像情報を読み取る関数
// Object::LoadMhdFile(){
//     return 0;
// }

// メイン関数 -----------------------------------------------------
int main(int argc, char *argv[]){
    
    Object obj;

    // コマンド引数　例外処理
    if(argc < 2){
        cout << "No program parameters provided !" << endl;
        exit(-1);
    }

    string file_name(argv[1]);
    // 1. テキストファイルから必要な情報を取得
    obj.LoadTxtFile(file_name);

    return 0;
}