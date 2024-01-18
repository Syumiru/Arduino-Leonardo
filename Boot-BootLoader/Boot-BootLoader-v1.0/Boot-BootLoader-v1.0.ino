/**
 * 【PGM】
 * ブートローダー起動用左右ライト交互点灯
 * 【実行手順】
 * 書込中にケーブルを引き抜くなどした場合に使用
 * RSTとGRDを通電させながらこのスケッチを書き込む
 * 【配布元】
 * https://github.com/Syumiru/Arduino-Leonardo
 * 【開発者】
 * Syumiru(https://twitter.com/PokeSyumiru)
 * 【免責事項】
 * PGMの利用によって生じた何らかのトラブル・損失・損害等の一切の責任を負いかねますのでご了承ください。
 * PGMを利用する場合は、自己責任で行う必要があります。
 * 【利用規定】
 * 当サイトのPGMは以下の場合、ご利用をお断りします。
 * 1.公序良俗に反する目的での利用
 * 2.イメージを損なうような攻撃的・差別的・性的・過激な利用
 * 3.反社会的勢力や違法行為に関わる利用
 * 4.PGM自体やPGMがインストールされた物品をコンテンツ・商品として再配布・販売
 * 5.その他著作者が不適切と判断した場合
 * また、加工の有無、または加工の多少で著作権の譲渡や移動はありません。
 */
#define TX_LED 30
#define RX_LED 17

void setup() {
  pinMode(TX_LED, OUTPUT);
  pinMode(RX_LED, OUTPUT);
}

void loop() {
  digitalWrite(TX_LED, LOW);
  delay(1000);
  digitalWrite(TX_LED, HIGH);
  delay(1000);
}
