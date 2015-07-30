wasawasa
========
[![license](https://img.shields.io/badge/License-WTFPL2-blue.svg?style=flat)](http://www.wtfpl.net/txt/copying/)
[![yasuna](https://img.shields.io/badge/yasuna-kawaii-orange.svg?style=flat)](http://houbunsha.co.jp/comics/detail.php?p=%A5%AD%A5%EB%A5%DF%A1%BC%A5%D9%A5%A4%A5%D9%A1%BC)

![default](http://41.media.tumblr.com/953e8b381ebd3bbaa61991174be27a2e/tumblr_nizhz4ARCF1u2jamko1_1280.png)

わさわさするだけの（没キャラクラ）デバイスドライバ 。   
x86-64なLinux-3.18 - Linux-4.1.3にて動作を確認しています。  

## Build  
  適時カーネルヘッダを入れて`make`するだけ。

## Install  
  rootになって`make install`とすれば、自動でモジュールのコピーと`mknod`が実行されます。   
  削除したい場合は`make uninstall`と唱えて下さい。
  
  ※ 備考  
  インストール先は`Makefile`の`PREFIX`変数にて設定できます。    

  
## Usage  
#### モジュールのロード
```shellsession
# insmod /lib/modules/`uname -r`/kernel/drivers/block/wasawasa.ko
```

#### モジュールのアンロード
```shellsession
# rmmod wasawasa
```

あとは、`/dev/null`の代用とするなりしましょう。   
`# dd if=/dev/wasawasa of=/dev/sda`等とすれば、ディスクが*わさわさ*します。   
  
## Digression
ただ、このままではリブート後に`/dev/wasawasa`が消滅（自動作成されない）してしまいます。     
それを悲しく思う方は、udevにデバイス管理を依頼する、または`/etc/rc.local`などの起動スクリプトに    

```shellsession
insmod /lib/modules/`uname -r`/kernel/drivers/block/wasawasa.ko
mknod /dev/wasawasa c 254 0
chmod 0666 /dev/wasawasa
```
のような記述すると良いかもしれません。   

## License
[WTFPL version 2](http://www.wtfpl.net/txt/copying/)

## Author
sasairc (https://github.com/sasairc)
