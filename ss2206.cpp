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
    // txtファイルの内容をpair型のvectorで記録する。行ごとで後から追加していく
    vector<pair<const string, string>> txtConfig;
    public:
    Object() {};    // コンストラクタ
    ~Object() {};   // ディストラクタ
    void LoadTxtFile(string file_name);
    // void LoadMhdFile();
};

// LoadTxtFile()関数　txtファイルから情報を読み取る関数
void Object::LoadTxtFile(string file_name){

    // テキストファイル読み込み
    ifstream reading_file;
    string line;
    reading_file.open(file_name);

    // ファイル読み込み　例外処理
    if(!reading_file.is_open()){
        cout << "Could not open file." << endl;
        exit(-1);
    }

    // テキストファイルの情報を読み取る
    int i = 0;
    while(getline(reading_file, line)){
        int equal_pos = line.find("=");
        line.erase(line.begin(), line.begin() + equal_pos + 2);
        if(i == 0) {txtConfig.push_back(make_pair("Input", line));}                     // Input
        if(i == 1) {txtConfig.push_back(make_pair("Output", line));}                    // Output
        if(i == 2) {txtConfig.push_back(make_pair("ImageProcessing", line));}           // ImageProcessing
        if(i == 3) {txtConfig.push_back(make_pair("WindowProcessing", line));}          // WindowProcessing
        if(i == 4) {txtConfig.push_back(make_pair("WindowLevel", line));}               // WindowLevel
        if(i == 5) {txtConfig.push_back(make_pair("WindowWidth", line));}               // WindowWidth
        if(i == 6) {txtConfig.push_back(make_pair("MovingAverageFilterKernel", line));} // MovingAverageFilterKernel
        if(i == 7) {txtConfig.push_back(make_pair("MedianFilterKernel", line));}        // MedianFilterKernel
        i ++;
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
    // for(int i = 0; i < 8; i ++ ){
    //     cout << txtConfig.first << ", " << txtConfig.second << endl;
    // }
    return 0;
}