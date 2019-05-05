## できること
C++で書かれたライブラリ群を整形して、json に変換してくれます！

## 使い方
`script.ps1` を Powershell で実行すると、`./library/*.cpp` を検索してパースして、 `./test/test.json` に流し込んでくれます！


## パースの方法

まずは例を挙げて説明します。
例えば次のようなコードがあるとします。(filename: `disjoint_ngtgraph.cpp`)


```cpp
#include <bits/stdc++.h>
using namespace std;
// begin
class disjoint_ngtgraph {
  int val;
};
// end
```

これをパースすると、

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
のようになります。なお実際には複数のファイルをパースして並べるので、最後のファイル以外には最後のカンマが付き、またこの json ファイル全体をくるむ brace も追加されます。
※ disjoint_ngtgraph は架空のクラスです。

## 今後追加したい機能
1. description を抽出できるようにしたい。
2. 引数付きスニペットに対応したい
3. コメント付きのソースから、 json ファイルだけでなく、リファレンスの役割を果たす markdown ファイルを生成できるようにしたい。（難しそう）

2の使いどころですが、いわゆるライブラリではなく、よく使う　code fragments の呼び出しに使いたいと思っています。具体的には、例えば私は次のような sort のスニペットを持っているのですが、こういうものも同じように管理するためです。

```json
"Sort": {
  "prefix": "sort",
  "body": [
    "sort($1.begin(), $1.end());$0",
  ],
  "description": "ソート"
},
```