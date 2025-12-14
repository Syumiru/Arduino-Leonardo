/**
 * 【PGM】
 * ユカリトーナメント∞自動化
 * 【使用インクルードライセンス】
 * NintendoSwitchControlLibrary：MIT
 * © 2021 lefmarna/troter
 * https://github.com/lefmarna/NintendoSwitchControlLibrary/blob/master/LICENSE
 * 【実行環境】
 * ハード：Switch2初期型
 * ソフト：Switch2版ゲームカード/本体メモリにDLC
 * 進行状況：DLCクリア後強化ユカリ
 * メタグロス@メタルコート
 * C抜け5VいじっぱりH32A252B224（より良い配分はありそう。確定で食らうのはメレシーのステルスロック、クチートのかみくだく、次点でニンフィアのシャドーボール。かみくだくとシャドボ急所で落ちるかも？要確認）
 * Aボタン:ヘビーボンバー
 * Xボタン:マグネットボム（アイアンヘッドでは火力不足でピクシーを落とせない可能性あり）
 * 【実行手順】
 * ①コメントアウトしている移動処理を有効化すればFT可能なら自動化開始可能
 * ②実行上限時間を設定
 * ③メインコントローラを外しマイコン操作可能とする（メニュー画面を開いておきコントローラを外すことを想定）
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
unsigned long StartTime;
//時給６０万想定のため15時間９００万を上限として設定
const unsigned long SleepTime = 54000000UL;
//起動時の動作（Arduinoにおいて記述必須）
void setup() {
  //起動時間を格納
  StartTime = millis();
  //Bボタンを10回連打しマイコン認識
  pushButton(Button::B, 200, 10);
}

//ループ処理（Arduinoにおいて記述必須）
void loop() {
  //移動処理
  //move_to_Hotel();
  //設定時間までループ
  while (millis() - StartTime < SleepTime) {
    //メイン処理
    Yukari_Tournament_infinity();
  }
  //終了処理
  End();
}

//メイン処理（ディレイを100以下はわざやロックオンの誤動作を確認済）
void Yukari_Tournament_infinity() {
  //対戦ポケモンをロックオン
  SwitchControlLibrary().pressButton(Button::ZL);
  SwitchControlLibrary().sendReport();
  //ディレイ
  delay(200);
  //話しかけるor技選択
  pushButton(Button::A, 200, 1);
  //技選択(Yはローリング、Bはキャンセルするため除外、ZL同時押し中にメニューは開かない)
  pushButton(Button::X, 200, 1);
  //対戦ポケモンをアンロック    
  SwitchControlLibrary().releaseButton(Button::ZL);
  SwitchControlLibrary().sendReport();
  //ディレイ
  delay(200);
}

//移動処理
void move_to_Hotel() {
  //＋ボタンでメニューを開く
  pushButton(Button::PLUS, 300, 1);
  //Yボタンで移動スポットを開く
  pushButton(Button::Y, 300, 1);
  //－ボタンでカテゴリを開く
  pushButton(Button::MINUS, 300, 1);
  //下十字キーで施設にカーソルを合わせる
  pushHat(Hat::DOWN, 100, 1);
  //Aボタンでゾーンを選択
  pushButton(Button::A, 300, 1);
  //上十字キーでゾーンにカーソルを合わせる
  pushHat(Hat::UP, 55, 7);
  //Aボタンで移動先を指定
  pushButton(Button::A, 500, 1);
  //Aボタンではいを押下
  pushButton(Button::A, 300, 1);
  //ロード時間待機
  delay(4000);
  //ホテルに入ってエレベータに乗りユカリに近づく
  tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 12500, Button::A); 
}
//処理終了
void End() {
  //HOMEボタン長押し   
  SwitchControlLibrary().pressButton(Button::HOME);
  //ディレイ
  delay(1000);
  //スリープを選択
  pushButton(Button::A, 100, 1);
}
