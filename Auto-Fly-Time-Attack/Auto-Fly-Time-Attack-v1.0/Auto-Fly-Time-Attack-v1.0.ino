/**
 * PGM
 * そらとぶタイムアタック初級コース自動周回
 * 使用インクルードライセンス
 * NintendoSwitchControll：MIT
 * © 2020 interimadd/takeutchi/kurimoun
 * https://github.com/interimadd/NintendoSwitchControll/blob/master/LICENSE.txt
 * 実行手順
 * ①ループ回数は初期値999回です。お好きに変更ください。
 * ②コーストスクエア受付前でPGM実行
 * 配布元
 * https://github.com/Syumiru/Arduino-Leonardo
 * 免責事項
 * PGMの利用によって生じた何らかのトラブル・損失・損害等の一切の責任を負いかねますのでご了承ください。
 * PGMを利用する場合は、自己責任で行う必要があります。
 * 利用規定
 * 当サイトのPGMは以下の場合、ご利用をお断りします。
 * 1.公序良俗に反する目的での利用
 * 2.イメージを損なうような攻撃的・差別的・性的・過激な利用
 * 3.反社会的勢力や違法行為に関わる利用
 * 4.PGM自体やPGMがインストールされた物品をコンテンツ・商品として再配布・販売
 * 5.その他著作者が不適切と判断した場合
 * また、加工の有無、または加工の多少で著作権の譲渡や移動はありません。
*/
//使用インクルード
#include <auto_command_util.h>

//変数定義
//ループ回数
int LoopCnt = 999;

//起動時の動作（Arduinoにおいて記述必須）
void setup() {
  //Bボタンを10回連打しマイコン認識
  pushButton(Button::B, 200, 10);
}

//ループ処理（Arduinoにおいて記述必須）
void loop() {
  //メイン処理
  Main();
}

//メイン処理
void Main() {
  //ループ回数を指定
  for (int i = 0; i < LoopCnt; i++) {
    //受付に話しかけるためAボタン
    pushButton(Button::A, 1000, 3);
    //会話をめくるためAボタン
    pushButton(Button::A, 1000, 1);
    //挑戦する！を選択するためAボタン    
    pushButton(Button::A, 1000, 1);
    //会話をめくるためAボタン
    pushButton(Button::A, 1000, 1);
    //初級コース選択でAボタン
    pushButton(Button::A, 1000, 1);
    //24秒wait
    delay(24000);
    //2個目のリングを潜るため右斜め上
    tiltJoystick(15,-100,0,0,1000);
    //2.5秒wait
    delay(2500);
    //ゴールに向かい左斜め上を入力
    tiltJoystick(-30,-50,0,0,3000);
    //10秒wait     
    delay(10000);
    //ゴールに向かい左斜め上を入力
    tiltJoystick(-70,50,0,0,400);
    //30秒wait     
    delay(30000);
    //会話をめくるためAボタン
    pushButton(Button::A, 1000, 3);
    //会話をめくるためAボタン
    pushButton(Button::A, 1000, 1);
    //10秒wait     
    delay(10000);
    //ループ回数をインクリメント
    LoopCnt++;
  }
}
