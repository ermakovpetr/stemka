### Stemka - вероятностный морфологический анализатор русского языка


### Автор
Андрей Коваленко
### Год создания
2002
### Официальный сайт
http://www.keva.ru/stemka/stemka.html

### Доступность
Представленный продукт доступен в исходных текстах и может использоваться в свободной форме с условием ссылки на источник.

### Установка
Для установки Stemka необходимо скачать архив с исходными кодами анализатора и скомпилировать их. При сборки исходников имеется нюанс: программа написана на C++, но при этом в Makefile используется компилятор языка Си. Это можно исправить явным заданием нужного компилятора: CC=g++.

```bash
% wget 'http://www.keva.ru/stemka/stemka.tar.gz'
% tar zxf stemka.tar.gz
% cd stemka
% CC=g++ make
````

### Использование
Командная строка
После успешной сборки в каталоге stemka появится выполняемый файл checkrus, являющийся приложением командной строки, принимающего по одному токену в каждой строке STDIN. При использования данного приложения стоит иметь в виду, что Stemka ориентирована на работу в кодировке Windows-1251, поэтому при различии кодовых страниц придётся выполнить перекодирование вручную. В случае Unix-подобных систем это делается чрезвычайно просто.

```bash
% echo -e "Андрюша\nмолодец\n." | iconv -f=utf8 -t=cp1251 -c | ./checkrus rus | iconv -f=cp1251 -t=utf8
Андрюш|а
молод|ец|
.
```

Очевидным образом можно обернуть вызов checkrus в простой скрипт.

```bash
#!/bin/sh
CHECKRUS=$(dirname $0)/checkrus
[ -x "$CHECKRUS" ] || exit 1
iconv -f=utf8 -t=cp1251 -c |
$CHECKRUS rus |
iconv -f=cp1251 -t=utf8 -c
```

Таким образом, можно использовать Stemka гораздо проще и удобнее.

```bash
% echo -e "Димочка\nтоже\nмолодец\n." | ./stemka.sh 
Димоч|к|а
тож|е
молод|ец|
.
```

### C/C++
Приятной особенностью Stemka является возможность использования анализатора в качестве библиотеки.

### Источник
http://nlpub.ru/Stemka
