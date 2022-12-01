#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <regex>
#include <tuple>
#include <cstdlib>
#include <cmath>
#include <algorithm>

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
    vector<short> raw_img;  // LoadRawFileで使用する
    vector<unsigned char> processing_img;   // WindowProcessing()関数で使用する
    const int pixel_max = 255;

    // メンバ関数
    Object() {};    // コンストラクタ
    ~Object() {};   // ディストラクタ
    void LoadTxtFile(string txt_file_name);
    void LoadMhdFile(string mhd_file_name);
    void LoadRawFile(string raw_file_name);
    void WindowProcessing();
    void Sobel();
    void MovingAverage();
    void Median();
    void OutputRawFile(string output_raw_file);
    void OutputMhdFile(string output_mhd_file);
};

// LoadTxtFile()関数　txtファイルから情報を読み取る関数
void Object::LoadTxtFile(string txt_file_name){

    // テキストファイル読み込み
    ifstream reading_file(txt_file_name);
    string line;

    // テキストファイル読み込み　例外処理
    if(!reading_file){
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
        // if(i == 4) {txt_config.push_back(make_pair('window_level', line));}               // window_level
        // if(i == 5) {txt_config.push_back(make_pair('window_width', line));}               // window_width
        // if(i == 6) {txt_config.push_back(make_pair('MovingAverageFilterKernel', line));} // MovingAverageFilterKernel
        // if(i == 7) {txt_config.push_back(make_pair('MedianFilterKernel', line));}        // MedianFilterKernel
    //     i ++;
    // }

    // 正規表現の形から、vectorのget<0>pairと同じ文字列が来たら情報をget<1>pairにいれる
    smatch match;
    regex re(R"(^([^\s]*)(\s*)=\s*([^\s]*)(\s*)\s*([^\s]*)(\s*))"); //正規表現の定義
    while(getline(reading_file, line)){
        regex_match(line, match, re);
        for(int i = 0; i < txt_config.size(); i ++){
            if(match[1] == txt_config[i].first){
                get<1>(txt_config[i]) = match[3];
            }
        }
    }
}

// LoadMhdFile()関数　mhdファイルから画像情報を読み取る関数
void Object::LoadMhdFile(string mhd_file_name){

    // mhdファイル読み込み
    ifstream reading_file(mhd_file_name);
    string line;

    // mhdファイル読み込み　例外処理
    if(!reading_file){
        cout << "Could not open mhdfile." << endl;
        exit(-1);
    }

    // 正規表現の形から、vectorのtuple[0]と同じ文字列が来たら情報をtuple[1],[2]にいれる
    smatch match;
    regex re(R"(^([^\s]*)(\s*)=\s*([^\s]*)(\s*)\s*([^\s]*)(\s*))"); //正規表現の定義
    while(getline(reading_file, line)){
        regex_match(line, match, re);
        for(int i = 0; i < mhd_config.size(); i ++){
            if(match[1] == get<0>(mhd_config[i])){
                get<1>(mhd_config[i]) = match[3];
                get<2>(mhd_config[i]) = match[5];
            }
        }
    }
}

// LoadRawFile()関数　raw画像を読み込む関数
void Object::LoadRawFile(string raw_file_name){
    ifstream reading_file(raw_file_name, ios::in | ios_base::binary);

    //例外処理
    if(!reading_file){
        cout << "Can't open raw file." << endl;
        exit(-1);
    }

    //rawサイズの取得
    reading_file.seekg(0,ios::end);
    unsigned long long raw_size = reading_file.tellg();
    reading_file.seekg(0);

    //raw_imgにshort型で保存
    short short_row;
    raw_img.reserve(raw_size);
    while (reading_file.read(reinterpret_cast<char*>(&short_row), sizeof(short_row))){
        raw_img.push_back(short_row);
    }
}

// WindowProcessing()関数　WindowProcessing=Trueの場合に階調変換を行う関数
void Object::WindowProcessing(){
    int WindowLevel = stoi(get<1>(txt_config[4]));
    int WindowWidth = stoi(get<1>(txt_config[4]));

    double gradient = (double)pixel_max / WindowWidth;
    double intercept = gradient * ( (WindowWidth / 2) - WindowLevel);

    for(short val: raw_img){
        double func = gradient * val + intercept;

        if(func > pixel_max){
            func = pixel_max;
        }
        else if(func < 0){
            func = 0;
        }
        processing_img.push_back((short)func);
    }
}

// Sobel()関数　エッジ検出のフィルタ処理を行う関数
void Object::Sobel(){
    vector<int> weight_horizontal = { -1, 0, 1,
                                     -2, 0, 2,
                                     -1, 0, 1 };
    vector<int> weight_vertical = { -1, -2, -1,
                                    0,  0,  0,
                                    1,  2,  1 };
    int weight_size = 3;
    int start = -1;
    int end = -2;
    int image_width = stoi(get<1>(mhd_config[2]));
    int image_height = stoi (get<2>(mhd_config[2]));
    int width_step = image_width;
    double data_number = 0;

    if(image_width % 4 != 0){
        width_step = image_width + 4 - image_width % 4;
    }

    for(int i = 1; i < (image_height - 1); ++i){
        for(int j = 1; j < (image_width - 1); ++j){
            double data_horizontal = 0;
            double data_vertical = 0;
            for(int k = start; k < end; ++k){
                for(int l = start; l < end; ++l){
                    //X方向
                    data_horizontal += weight_horizontal[(k - start) * weight_size + (l - start)]
                                        * (unsigned char)processing_img[(i + k) * width_step + (j + l)];

                    //Y方向
                    data_vertical += weight_vertical[(k - start) * weight_size + (l - start)]
                                        * (unsigned char)processing_img[(i + k) * width_step + (j + l)];
                }
            }

            //SobelXの時の処理
            if(get<1>(txt_config[2]) == "SobelX"){
                data_number = data_horizontal;
            }
            //SobelYの時の処理
            else if(get<1>(txt_config[2]) == "SobelY"){
                data_number = data_vertical;
            }

            //data_numberの値の確認
            if(data_number > pixel_max){
                data_number = pixel_max;
            }
            else if(data_number < 0){
                data_number = -data_number;
            }

            vector<unsigned char> Tmp_processing_img = processing_img;
            Tmp_processing_img[i * width_step + j] = data_number;
        }
    }
 }

// MovingAverage()関数　移動平均のフィルタ処理を行う巻子
 void Object::MovingAverage(){
    int image_width = stoi(get<1>(mhd_config[2]));
    int image_height = stoi (get<2>(mhd_config[2]));
    int weight_size = stoi(get<1>(txt_config[6]));
    int padding = (weight_size - 1) / 2;
    int start = -padding;
    int end = start + weight_size;
    vector<float> weight((weight_size * weight_size), 1 / ((float)weight_size * weight_size));
    int width_step = image_width;

    if(image_width % 4 != 0){
        width_step = image_width + 4 - image_width % 4;
    }

    //各画素
    for(int i = padding; i < (image_height - padding); ++i){
        for(int j = padding; j < (image_width - padding); ++j){
            double data_tmp = 0;
            //カーネル内の計算
            for(int k = start; k < end; ++k){
                for(int l = start; l < end; ++l){
                    data_tmp += weight[(k - start) * weight_size + (l - start)]
                                        * (unsigned char)processing_img[(i + k) * width_step + (j + l)];
                }
            }

            //data_tmpの値の確認
            if(data_tmp > pixel_max){
                data_tmp = pixel_max;
            }
            else if(data_tmp < 0){
                data_tmp = -data_tmp;
            }

            vector<unsigned char> tmp_processing_img = processing_img;
            tmp_processing_img[i * width_step + j] = data_tmp;
        }
    }
}

// メディアンフィルタ処理を行う関数
void Object::Median(){
    int image_width = stoi(get<1>(mhd_config[2]));
    int image_height = stoi (get<2>(mhd_config[2]));
    int weight_size = stoi(get<1>(txt_config[7]));
    int padding = (weight_size - 1) / 2;
    int start = -padding;
    int end = start + weight_size;
    int med = floor((weight_size * weight_size) / 2);
    int width_step = image_width;
    vector<float> list;

    if(image_width % 4 != 0){
        width_step = image_width + 4 - image_width % 4;
    }

    for(int i = padding; i < (image_height - padding); ++i){
        for(int j = padding; j < (image_width - padding); ++j){
            double data_tmp = 0;
            list.clear();
            list.reserve(weight_size * weight_size);
            for(int k = start; k < end; ++k){
                for(int l = start; l < end; ++l){
                    list.push_back((unsigned char)processing_img[(i + k) * width_step + (j + l)]);
                }
            }

            sort(list.begin(), list.end());
            data_tmp = list[med];

            //data_tmpの値の確認
            if(data_tmp > pixel_max){
                data_tmp = pixel_max;
            }
            else if(data_tmp < 0){
                data_tmp = -data_tmp;
            }

            vector<unsigned char> tmp_processing_img = processing_img;
            tmp_processing_img[i * width_step + j] = data_tmp;
        }
    }
}

// OutputRawFile()関数　raw画像を出力する関数
void Object::OutputRawFile(string output_raw_file){
    ofstream output_file(output_raw_file, ios_base::binary);

    //rawファイル出力　例外処理
    if(!output_file){
        cout << "Fail to output rawfile." << endl;
        exit(-1);
    }

    //出力
    for(auto bin: processing_img){
        output_file.put(bin);
    }
}

// mhdファイルを作成する関数
void Object::OutputMhdFile(string output_mhd_file){
    ofstream output_file(output_mhd_file, ios_base::binary);

    //mhdファイル作成　例外処理
    if(!output_file){
        cout << "Fail to output mhdfile." << endl;
        exit(-1);
    }

    //出力
    get<1>(mhd_config[3]) = "MET_UCHAR";
    get<1>(mhd_config[6]) = get<1>(txt_config[1]) + ".raw";

    for(int i = 0; i < mhd_config.size(); i++){
        output_file << get<0>(mhd_config[i]) << " = " << get<1>(mhd_config[i]);
        if(i == 2 || i == 4){
            output_file << " " << get<2>(mhd_config[i]);
        }
        output_file << "\n";
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
    // cout << raw_file_name << endl;
    obj.LoadRawFile(raw_file_name);
    // 4. WindowProcessing = Trueの場合に階調変換を行う
    if(get<1>(obj.txt_config[3]) == "True"){
        cout << "階調変換を行った。" << endl;
        obj.WindowProcessing();
    }
    else{
        cout << "階調変換を行わなかった。" << endl;
    }
    // 5. 各種フィルタの実装
    // 実装なし
    if(get<1>(obj.txt_config[2]) == "None"){ //何もしない
        cout << "フィルタ処理は何も行わなかった。" << endl;
    }
    //エッジ検出フィルタ処理
    else if(get<1>(obj.txt_config[2]) == "SobelX" || get<1>(obj.txt_config[2]) == "SobelY"){
        cout << "エッジ検出フィルタ処理を行った。" << endl;
        obj.Sobel();
    }
    // 移動平均フィルタ処理
    else if(get<1>(obj.txt_config[2]) == "MovingAverage"){
        cout << "移動平均フィルタ処理を行った。" << endl;
        obj.MovingAverage();
    }
    // メディアンフィルタ処理
    else if(get<1>(obj.txt_config[2]) == "Median"){
        cout << "メディアンフィルタ処理を行った。" << endl;
        obj.Median();
    }
    else{
        cout << "処理可能な内容を記入してください" << endl;
        cout << "処理可能フィルタ名: None, SobelX, SobelY, MovingAverage, Median" << endl;
    }
    // 6. raw形式とmhd形式で結果を出力
    string output_raw_file = get<1>(obj.txt_config[1]) + ".raw";
    obj.OutputRawFile(output_raw_file);
    string output_mhd_file = get<1>(obj.txt_config[1]) + ".mhd";
    obj.OutputMhdFile(output_mhd_file);

    cout << "実行完了" << endl;
    return 0;
}