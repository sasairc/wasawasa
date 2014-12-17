wasawasa
========

![default](https://cloud.githubusercontent.com/assets/9349287/5473377/4ac2d712-864c-11e4-8081-d12b5118722a.png)

わさわさするだけの（没キャラクラ）デバイスドライバ 。   
Linux-3.18にて動作を確認しています。  

#### Build  
  適時カーネルヘッダを入れて`make`するだけ。

#### Install  
  rootになって`make install`とすれば、自動でモジュールのコピーとmknodが実行されます。   
  削除したい場合は`make uninstall`と唱えて下さい。
  
  ※ 備考  
  インストール先はMakefileのPREFIX変数にて設定できます。    

  
#### Usage  
* モジュールのロード
```
# insmod /lib/modules/`uname -r`/kernel/drivers/block/wasawasa.ko
```

* モジュールのアンロード
```
# rmmod wasawasa
```

あとは、/dev/nullの代用とするなりしましょう。   
`# dd if=/dev/wasawasa of=/dev/sda`とすれば、ディスクを*wasawasa*で初期化できます。

  
#### License  
  [どうとでも勝手にしやがれクソッタレ・公衆利用許諾書(WTFPL Version 2)] (http://www.wtfpl.net/txt/copying/)
