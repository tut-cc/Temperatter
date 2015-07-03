# Tweet-a-temperature

Tweet a temperature with your Raspberry Pi.

Raspberry Piで動く、室温をツイートするBotです。
  
RPiに接続する温度センサはSTTS751です。
なおAddr/~Thermピンのプルアップ抵抗は33kΩです。

## コンパイル
`gcc ptemp2.c -o ptemp2`

## 実行
`ruby temperatter2.rb`
