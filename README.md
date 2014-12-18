wasawasa
========

![default](https://cloud.githubusercontent.com/assets/9349287/5483849/a2d5852c-86be-11e4-8792-7008c6d888da.png)

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
`# dd if=/dev/wasawasa of=/dev/sda`等とすれば、ディスクが*わさわさ*します。   
  
#### Digression
このままでは、リブート後に`/dev/wasawasa`が消滅（自動作成されない）してしまいます。     
それを悲しく思う方は、udevにデバイス管理を依頼する、または`/etc/rc.local`などの起動スクリプトに    

```
insmod /lib/modules/`uname -r`/kernel/drivers/block/wasawasa.ko
mknod /dev/wasawasa c 254 0
chmod 0666 /dev/wasawasa
```
のような記述すると良いかもしれません。   

#### License  
  [どうとでも勝手にしやがれクソッタレ・公衆利用許諾書(WTFPL Version 2)] (http://www.wtfpl.net/txt/copying/)
