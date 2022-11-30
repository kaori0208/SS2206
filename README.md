# スキルゼミ課題 SS2206
## 課題名：画像のフィルタリング
氏名：山本 香織

## 開発環境
- Windows 10 WSL
- c++

## 実行方法
```bash
$ g++ ss2206.cp
$ ./a.out ProcessingParameter.txt
```
- 実行時引数は指定されたテキストファイル名

## 実行結果
```

実行完了
```
- saveボタンを押した場合は、saveが表示される
- Xmingのインストールを行いました

## 階層構造
```
.
├── CT_Noise.mhd
├── CT_Noise.raw
├── CT_Original.mhd
├── CT_Original.raw
├── ProcessingParameter.txt
├── README.md
└── ss2206.cpp

0 directories, 7 files
```

## コメント
- main()関数を簡潔にするために関数化をできるだけ行った。
- 時間がなかったので、滝瀬さんのコードを参考にしました。自分なりに改良してやったんですけど、mhd_file_nameに".mhd"をappend使用としたらCT_originalが.mhdriginalになってしまい、なぜか先頭に文字列が挿入されてしまいました。原因がわからなかったので、自分が本来やりたかったコードを残してあります。

## 参考資料
- [ファイルの読み込み](https://code-database.com/knowledges/123)
- [コマンド引数の定義](http://cplplus.web.fc2.com/Last2.html)
- [find関数の使い方](https://www.sejuku.net/blog/49318)
- [vectorのpair型の追加方法](https://osazo-ml-cv.hatenablog.com/entry/2022/01/29/225021)