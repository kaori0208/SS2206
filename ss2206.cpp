#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// txtファイルとmhdファイルを読み込むクラス
class FileData{
    string input_filename;
    string output_filename;
    public:
    // FileData();
    // ~FileData();
    void LoadTxtFile();
    // LoadMhdFile();
};
// FileData::FileData(){}
// FileData::~FileData(){}

// LoadTxtFile()関数　txtファイルから情報を読み取る関数
void FileData::LoadTxtFile(){

    // テキストファイル読み込み
    string file_name = "ProcessingParameter.txt";
    ifstream reading_file;
    vector<string> lines;
    string line;
    reading_file.open(file_name);

    // ファイル読み込み例外処理
    if(!reading_file.is_open()){
        cout << "Could not open file." << endl;
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
// FileData::LoadMhdFile(){
//     return 0;
// }

// メイン関数 -----------------------------------------------------
int main(){
    // 1. テキストファイルから必要な情報を取得
    FileData ct1;
    ct1.LoadTxtFile();

    return 0;
}