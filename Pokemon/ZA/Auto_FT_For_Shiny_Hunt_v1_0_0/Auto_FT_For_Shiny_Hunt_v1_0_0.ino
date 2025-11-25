/**
 * 【PGM】
 * 色違い厳選向けファストトラベル自動化
 * 【使用インクルードライセンス】
 * NintendoSwitchControlLibrary：MIT
 * © 2021 lefmarna/troter
 * https://github.com/lefmarna/NintendoSwitchControlLibrary/blob/master/LICENSE
 * 【実行環境整備】
 * ①ファストトラベル可能であること
 * 【実行手順】
 * ①各環境に併せて変数を変更
 * ②メインコントローラを外しマイコン操作可能とする（メニュー画面を開いてコントローラを外すことを想定）
 * 【配布元】
 * https://github.com/Syumiru/Arduino-Leonardo
 * 【開発者】
 * Syumiru(https://X.com/PokeSyumiru)
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
//使用インクルード
#include <NintendoSwitchControlLibrary.h>

//変数定義
//Switch1/2
int Sleep = 2;
//FT上限
int FTLmt = 1000;
//十字キー上を押下する回数
int UPCnt = 1;
//ロード待ち時間
int WaitLoadTime = 4000;

//起動時の動作（Arduinoにおいて記述必須）
void setup() {
  //Bボタンを10回連打しマイコン認識
  pushButton(Button::B, 200, 10);
}

//ループ処理（Arduinoにおいて記述必須）
void loop() {
  //メイン処理
  Main();
  //終了処理
  End();
}

//メイン処理
void Main() {
  for (int i = 0; i < FTLmt; i++) {
    //＋ボタンでメニューを開く
    pushButton(Button::PLUS, 300, 1);
    //Yボタンで移動スポットを開く
    pushButton(Button::Y, 300, 1);
    //上十字キーで移動先にカーソルを合わせる
    pushHat(Hat::UP, 300, UPCnt);
    //Aボタンで移動先を指定
    pushButton(Button::A, 500, 1);
    //Aボタンではいを押下
    pushButton(Button::A,WaitLoadTime, 1);
  }
}

//処理終了
void End() {
  if ( Sleep == 1 ) {
    //HOMEボタンでswitchメニュー表示
    pushButton(Button::HOME, 1000);
    //下十字キーを押下しNintendo Switch Onlineにカーソルを合わせる
    pushHat(Hat::DOWN, 200, 1);
    //右十字キーを8回押下しスリープにカーソルを合わせる
    pushHat(Hat::RIGHT, 200, 8);
    //スリープを選択
    pushButton(Button::A, 200, 3);
  }
  //HOMEボタンでswitchメニュー表示
  pushButton(Button::HOME, 1000);
  //下十字キーを押下しNintendo Switch Onlineにカーソルを合わせる
  pushHat(Hat::DOWN, 200, 1);
  //左十字キーを1回押下しスリープにカーソルを合わせる
  pushHat(Hat::LEFT, 200, 1);
  //スリープを選択
  pushButton(Button::A, 200, 2);
}
