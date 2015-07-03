# Temperatter

Tweet a temperature with your Raspberry Pi.

Raspberry Piで動く、室温をツイートするBotです。
  
RPiに接続する温度センサはSTTS751です。
なおAddr/~Thermピンのプルアップ抵抗は33kΩです。

## 回路
Schematic  
![Schematic](https://github.com/tut-cc/Temperatter/blob/master/schematic.PNG)

## コンパイル
Compile  
`gcc ptemp2.c -o ptemp2`

## 実行
Run  
`ruby temperatter2.rb`  

The ptemp2(executable file) and temperatter2.rb must be in the same directory.
