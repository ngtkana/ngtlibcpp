# Library
GitHub Pages にライブラリへのリンクをまとめてあります。

GitHub Pages 不調のため [こちら](docs/index.md) からお願いします。（`docs/index.md` への直リンク）


## できること
C++で書かれたライブラリ群を整形して、json に変換してくれます！

## 使い方
`script.ps1` を Powershell で実行すると、`./library/*.cpp` を検索してパースして、 `./test/test.json` に流し込んでくれます！

また、プレイスホルダーがあるなど、扱いに困っているスニペットは `json/fragments.json` に入れてあって、こちらもその後ろに流し込んでくれます。

## パースの方法

ライブラリファイル一つに対して、次のような json オブジェクトを生成します。
- スニペット名： ファイル名（`_`を` `に置換したもの）
- prefix： 同上
- body: ソース中の `//begin` から `//end` までをエスケープして行ごとに要素化して配列にする
- description: 無条件で `none`

## パースの例

```json
"disjoint　ngtgraph": {
  "prefix": "disjoint　ngtgraph",
  "body": [
    "class ngt_graph {",
    "\tint val;",
    "};",
  ],
  "description": "none"
}
```

※ disjoint_ngtgraph は架空のクラスです。

## 今後
- prefixを指定できるようにしたい（複数）
- 引数付きスニペット、依存ライブラリの扱いを考えたい（#defineを使うという説がありますが、ちょっと雑すぎる）
- コンストラクタやメンバに関する説明を自動生成してGitHub Pagesに流せるようにしたい

あと早く本番運用（コンテスト用スニペットとの連携）に移したいです！
