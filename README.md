# スキルゼミ課題 SS2206
## 課題名：画像のフィルタリング
氏名：山本 香織

## 開発環境
- Windows 10 WSL
- g++ (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0

## 実行方法
```bash
$ g++ ss2206.cpp
$ ./a.out ProcessingParameter.txt
```
- 実行時引数は指定されたテキストファイル名.argv[1]によりテキストファイル名を取得

## 実行結果
```
階調変換を行った。
エッジ検出フィルタ処理を行った。
実行完了
```
- CT_original_SobelXという名前のmhdファイルとrawファイルが生成された。

## 階層構造
```
.
├── CT_Noise.mhd
├── CT_Noise.raw
├── CT_Original.mhd
├── CT_Original.raw
├── CT_Original_SobelX.mhd
├── CT_Original_SobelX.raw
├── ProcessingParameter.txt
├── README.md
├── a.out
└── ss2206.cpp

0 directories, 10 files
```

## コメント
- main()関数を簡潔にするために関数化をできるだけ行った。
- 時間がなかったので、滝瀬さんのコードを参考にしました。自分なりに改良してやったんですけど、mhd_file_nameに".mhd"をappend使用としたらCT_originalが.mhdriginalになってしまい、なぜか先頭に文字列が挿入されてしまいました。原因がわからなかったので、自分が本来やりたかったコードを残してあります。
- 本来自分はファイル読み織の際にイコールを見つけたらそれ以前を消して、ファイル情報だけを残し、残ったstring型の文字をtupleに突っ込む形をとりたかった。正規表現の使い方を調べても＝に関するものを見つけられずに、滝瀬さんのをそのまま参考にした形になってしまったので、自分なりに調べたい。
- 

## 参考資料
- [ファイルの読み込み](https://code-database.com/knowledges/123)
- [コマンド引数の定義](http://cplplus.web.fc2.com/Last2.html)
- [find関数の使い方](https://www.sejuku.net/blog/49318)
- [vectorのpair型の追加方法](https://osazo-ml-cv.hatenablog.com/entry/2022/01/29/225021)