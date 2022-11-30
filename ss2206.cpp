#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <regex>
#include <typeinfo>

using namespace std;

// Objectクラス作成
class Object{
    public:
    // メンバ変数
    // txtファイルの内容をpair型のvectorで記録する
    // vector<pair<const string, string>> txt_config;   ←自分が本来やりたかったpai型
    vector<pair<const string, string>> txt_config = {{"Input",""},
                                                     {"Output",""},
                                                     {"ImageProcessing",""},
                                                     {"WindowProcessing",""},
                                                     {"WindowLevel",""},
                                                     {"WindowWidth",""},
                                                     {"MovingAverageFilterKernel",""},
                                                     {"MedianFilterKernel",""}};
    // mhdファイルの内容をtuple型のvectorで記録する
    // vector<tuple<const string, string>> mhd_config;   ←自分が本来やりたかったpai型
    vector<tuple<const string, string, string>> mhd_config = {{"ObjectType","",""},
                                                              {"NDims","",""},
                                                              {"DimSize","",""},
                                                              {"ElementType","",""},
                                                              {"ElementSpacing","",""},
                                                              {"ElementByteOrderMSB","",""},
                                                              {"ElementDataFile","",""}};

    // メンバ関数
    Object() {};    // コンストラクタ
    ~Object() {};   // ディストラクタ
    void LoadTxtFile(string txt_file_name);
    void LoadMhdFile(string mhd_file_name);
};

// LoadTxtFile()関数　txtファイルから情報を読み取る関数
void Object::LoadTxtFile(string txt_file_name){

    // テキストファイル読み込み
    ifstream reading_file;
    string line;
    reading_file.open(txt_file_name);

    // テキストファイル読み込み　例外処理
    if(!reading_file.is_open()){
        cout << "Could not open txtfile." << endl;
        exit(-1);
    }
    
    // テキストファイルの情報を読み取る.先程作ったpair型にpush_backしてvectorを作りたかった
    // int i = 0;
    // while(getline(reading_file, line)){
        // int equal_pos = line.find('=');
        // line.erase(line.begin(), line.begin() + equal_pos + 2);
        // if(i == 0) {txt_config.push_back(make_pair('Input', line));}                     // Input
        // if(i == 1) {txt_config.push_back(make_pair('Output', line));}                    // Output
        // if(i == 2) {txt_config.push_back(make_pair('ImageProcessing', line));}           // ImageProcessing
        // if(i == 3) {txt_config.push_back(make_pair('WindowProcessing', line));}          // WindowProcessing
        // if(i == 4) {txt_config.push_back(make_pair('WindowLevel', line));}               // WindowLevel
        // if(i == 5) {txt_config.push_back(make_pair('WindowWidth', line));}               // WindowWidth
        // if(i == 6) {txt_config.push_back(make_pair('MovingAverageFilterKernel', line));} // MovingAverageFilterKernel
        // if(i == 7) {txt_config.push_back(make_pair('MedianFilterKernel', line));}        // MedianFilterKernel
    //     i ++;
    // }

    // 正規表現の形から、vectorのget<0>pairと同じ文字列が来たら情報をget<1>pairにいれる
    smatch match;
    regex re(R"(^([^\s]*)(\s*)=\s*([^\s]*)(\s*)\s*([^\s]*)(\s*))"); //正規表現の定義
    while(getline(reading_file, line)){
        regex_match(line, match, re);
        for(int i = 0; i < txt_config.size(); i++){
            if(match[1] == get<0>(txt_config[i])){
                get<1>(txt_config[i]) = match[3];
            }
        }
    }
    reading_file.close();
}

// LoadMhdFile()関数　mhdファイルから画像情報を読み取る関数
void Object::LoadMhdFile(string mhd_file_name){

    // mhdファイル読み込み
    ifstream reading_file;
    string line;
    reading_file.open(mhd_file_name);

    // mhdファイル読み込み　例外処理
    if(!reading_file.is_open()){
        cout << "Could not open mhdfile." << endl;
        exit(-1);
    }
    // mhdファイルの情報を読み取る.先程作ったtuple型にpush_backしてvectorを作りたかった
    // int i = 0;
    // while(getline(reading_file, line)){
        // int equal_pos = line.find('=');
        // line.erase(line.begin(), line.begin() + equal_pos + 2);
        // if(i == 0) {txt_config.push_back(make_pair('Input', line));}                     // Input
        // if(i == 1) {txt_config.push_back(make_pair('Output', line));}                    // Output
        // if(i == 2) {txt_config.push_back(make_pair('ImageProcessing', line));}           // ImageProcessing
        // if(i == 3) {txt_config.push_back(make_pair('WindowProcessing', line));}          // WindowProcessing
        // if(i == 4) {txt_config.push_back(make_pair('WindowLevel', line));}               // WindowLevel
        // if(i == 5) {txt_config.push_back(make_pair('WindowWidth', line));}               // WindowWidth
        // if(i == 6) {txt_config.push_back(make_pair('MovingAverageFilterKernel', line));} // MovingAverageFilterKernel
        // if(i == 7) {txt_config.push_back(make_pair('MedianFilterKernel', line));}        // MedianFilterKernel
    //     i ++;
    // }

    // 正規表現の形から、vectorのtuple[0]と同じ文字列が来たら情報をtuple[1],[2]にいれる
    smatch match;
    regex re(R"(^([^\s]*)(\s*)=\s*([^\s]*)(\s*)\s*([^\s]*)(\s*))"); //正規表現の定義
    while(getline(reading_file, line)){
        regex_match(line, match, re);
        for(int i = 0; i < mhd_config.size(); i++){
            if(match[1] == get<0>(mhd_config[i])){
                get<1>(mhd_config[i]) = match[3];
                get<2>(mhd_config[i]) = match[5];
            }
        }
    }
}

// メイン関数 -----------------------------------------------------
int main(int argc, char *argv[]){
    
    Object obj;
    string txt_file_name(argv[1]);

    // コマンド引数　例外処理
    if(argc < 2){
        cout << "No program parameters provided !" << endl;
        return -1;
    }

    // 1. テキストファイルから必要な情報を取得
    obj.LoadTxtFile(txt_file_name);
    // 2. mhdファイルから画像情報を取得
    string mhd_file_name = get<1>(obj.txt_config[0]);
    mhd_file_name.append(".mhd");
    obj.LoadMhdFile(mhd_file_name);
    // 3. raw画像の読み込み
    string raw_file_name = get<1>(obj.mhd_config[6]);
    // obj.LoadRawFile()
    return 0;
}