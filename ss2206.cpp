#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

// Objectクラス作成
class Object{
    public:
    // メンバ変数
    // txtファイルの内容をpair型のvectorで記録する
    vector<pair<const string, string>> txt_config;
    // mhdファイルの内容をpair型のvectorで記録する
    vector<pair<const string, string>> mhd_config;

    // メンバ関数
    Object() {};    // コンストラクタ
    ~Object() {};   // ディストラクタ
    void LoadTxtFile(string file_name);
    void LoadMhdFile(string& file_name);
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
        if(i == 0) {txt_config.push_back(make_pair("Input", line));}                     // Input
        if(i == 1) {txt_config.push_back(make_pair("Output", line));}                    // Output
        if(i == 2) {txt_config.push_back(make_pair("ImageProcessing", line));}           // ImageProcessing
        if(i == 3) {txt_config.push_back(make_pair("WindowProcessing", line));}          // WindowProcessing
        if(i == 4) {txt_config.push_back(make_pair("WindowLevel", line));}               // WindowLevel
        if(i == 5) {txt_config.push_back(make_pair("WindowWidth", line));}               // WindowWidth
        if(i == 6) {txt_config.push_back(make_pair("MovingAverageFilterKernel", line));} // MovingAverageFilterKernel
        if(i == 7) {txt_config.push_back(make_pair("MedianFilterKernel", line));}        // MedianFilterKernel
        if(i == 7){
            for(const auto &[a, b]: txt_config){
            cout << a << ", " << b << endl;
            }
        }
        i ++;
    }
    reading_file.close();
}

// LoadMhdFile()関数　mhdファイルから画像情報を読み取る関数
void Object::LoadMhdFile(string& file_name){
    cout << file_name << endl;
}

// メイン関数 -----------------------------------------------------
int main(int argc, char *argv[]){
    
    Object obj;
    string file_name(argv[1]);

    // コマンド引数　例外処理
    if(argc < 2){
        cout << "No program parameters provided !" << endl;
        exit(-1);
    }

    // 1. テキストファイルから必要な情報を取得
    obj.LoadTxtFile(file_name);
    // 2. mhdファイルから画像情報を取得
    cout << obj.txt_config[0].second << endl;
    
    // obj.LoadMhdFile(obj.txt_config[0].second);
    return 0;
}