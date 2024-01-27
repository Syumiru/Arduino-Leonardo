/**
 * 【PGM】
 * 野生ポケモン所持アイテム入手自動化
 * 【使用インクルードライセンス】
 * NintendoSwitchControlLibrary：MIT
 * © 2021 lefmarna/troter
 * https://github.com/lefmarna/NintendoSwitchControlLibrary/blob/master/LICENSE
 * 【実行環境整備】
 * ①Switch本体ストレージにSVのデータがあることを確認する
 * ②Switch本体ストレージに5GB以上の空きを用意する
 * ③Arduino Leonardoおよび指定インクルードが使用可能であること
 * 【実行環境整備（ソフト）】
 * ①実行回数に合わせたポイントマックスを所持
 * ②とくせいマジシャンのポケモン（クレッフィ）
 * ③PGMのPPを実機に合わせる
 * ④盗む対象ポケモンを他のポケモンが出現しないような場所へ誘導
 * ⑤メインメニューのカーソルは先頭ポケモンorバッグに合わせておく
 * ⑥相手の使用してくるモーションが最長のわざに合わせて待機時間を変更
 * 【実行手順】
 * ①ループ上限は初期値無制限
 * ②使いたい場合はセーブ/終了処理の有効化※誤動作した場合のリスクが大きくなります
 * ③1セーブ間のループ上限/ループ上限の変更※初期値はそれぞれ100/1000
 * ④1周目は戦闘画面からスタート
 * 【配布元】
 * https://github.com/Syumiru/Arduino-Leonardo
 * 【開発者】
 * Syumiru(https://twitter.com/PokeSyumiru)
 * 【変更履歴】
 * v1.0 初版作成
 * v2.0 わざ「すりかえ」「トリック」を利用した形からとくせい「マジシャン」を利用した形に変更
 * v2.0.1 入力漏れ防止処理追加
 * 【既知の問題】
 * 1000回実行したところ想定より十数回分のアイテムが不足していました。
 * →v2.0.1により1000回に2回程度になったことを確認済
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
// 使用インクルード
#include <NintendoSwitchControlLibrary.h>

//変数定義
//ループ回数
int LoopCnt;
//わざ使用回数
int AllMoveCnt;
//わざ使用回数上限
int MaxMove;
//わざ123使用回数上限
int MaxMove123PP;
//わざ12使用回数上限
int MaxMove12PP;
//わざ1最大PP
int MaxMove1PP = 56;
//わざ2最大PP
int MaxMove2PP = 48;
//わざ3最大PP
int MaxMove3PP = 40;
//わざ4最大PP
int MaxMove4PP = 32;
//わざ選択
int MoveChoise = 0;
//わざ待機時間(たいあたり初回モーション読込に時間が掛かる場合があるっぽいので考慮する場合は+1秒)
int MoveWaitTime = 15000;
//1セーブ間のループ上限
int SaveLmt = 998;
//ループ上限
int LoopLmt = 998;

//起動時の動作（Arduinoにおいて記述必須）
void setup() {
  //Bボタンを10回連打しマイコン認識
  pushButton(Button::B, 200, 10);
  //わざ使用回数上限計算
  CalcMoveLimit();
}

//ループ処理（Arduinoにおいて記述必須）
void loop() {
  //メイン処理
  Main();
  //セーブ処理
  //Save();
  //処理回数が上限に到達した場合
  if ( LoopCnt >= LoopLmt ) {
    //終了処理
    End();
  }
}

//メイン処理
void Main() {
  //1セーブ間のループ上限を指定
  for (int i = 0; i < SaveLmt; i++) {
    //全てのわざを使用した場合
    if ( AllMoveCnt == MaxMove ) {
      //ポケモン回復
      RecoveryPP();
      //リセットするため技使用回数をクリア
      AllMoveCnt = 0;
      //リセットするためわざ選択をクリア
      MoveChoise = 0;
    }
    //たたかうを選択するためAボタン
    pushButton(Button::A, 500, 1);
    //わざ使用回数により押下する回数を変更
    if ( AllMoveCnt == MaxMove1PP ) {
      MoveChoise = 1;
      MoveWaitTime = 15000;
    }
    else if ( AllMoveCnt == MaxMove12PP ) {
      MoveChoise = 2;
      MoveWaitTime = 13000;
    }
    else if ( AllMoveCnt == MaxMove123PP ) {
      MoveChoise = 3;
      MoveWaitTime = 15000; // （急所でギリギリ処理続行されたことを確認済）
    }
    //下十字キーを押下しわざにカーソルを合わせる
    pushHat(Hat::DOWN, 750, MoveChoise);
    //わざを選択するためAボタン(急所考慮する必要がある)
    pushButton(Button::A, 500, 1);//入力抜けがあったので2回にしてみる
    pushButton(Button::A, MoveWaitTime, 1);
    //上十字キーを押下しにげるにカーソルを合わせる
    pushHat(Hat::UP, 500, 1);
    //にげるを選択するためAボタン(入力抜けがあったので2回にしてみる)
    pushButton(Button::A, 0, 2);
    //ループ回数をインクリメント
    LoopCnt++;
    //わざ使用回数をインクリメント
    AllMoveCnt++;
    //対象ポケモンにボールを投げるためZRを19回押下(待機時間含む)
    pushButton(Button::ZR, 500, 19);
  }
}

//わざ使用回数上限計算
void CalcMoveLimit() {
  //わざ使用回数上限設定
  MaxMove = MaxMove1PP + MaxMove2PP + MaxMove3PP+ MaxMove4PP;
  //わざ123使用回数上限設定
  MaxMove123PP = MaxMove1PP + MaxMove2PP + MaxMove3PP;
  //わざ12使用回数上限設定
  MaxMove12PP = MaxMove1PP + MaxMove2PP;
}

//PP回復
void RecoveryPP() {
  //下十字キーを2回押下しバッグにカーソルを合わせる
  pushHat(Hat::DOWN, 1500, 2);
  //Aボタンでバッグを開く
  pushButton(Button::A, 1000, 1);
  //上十字キーを1回押下しPPMAXにカーソルを合わせる
  pushHat(Hat::UP, 1000, 1);
  //AボタンでPPMAXを選択
  pushButton(Button::A, 1000, 1);
  //Aボタンでつかうを選択
  pushButton(Button::A, 1000, 1);
  //Aボタンで先頭ポケモンを選択
  pushButton(Button::A, 0, 2);
  //14秒待機
  delay(14000);
}

//セーブ処理
void Save() {
  //メインメニューを開く
  pushButton(Button::X, 1000, 1);
  //レポートをRボタンで決定
  pushButton(Button::R, 1500, 1);
  //Aボタンでレポートを記録
  pushButton(Button::A, 4000, 1);
  //Bボタンを5回連打しメインメニュー前まで戻す
  pushButton(Button::B, 200, 5);  
}

//処理終了
void End() {
  //HOMEボタンでswitchメニュー表示
  pushButton(Button::HOME, 1000);
  //下十字キーを押下しNintendo Switch Onlineにカーソルを合わせる
  pushHat(Hat::DOWN, 200, 1);
  //右十字キーを6回押下しスリープにカーソルを合わせる
  pushHat(Hat::RIGHT, 200, 6);
  //スリープを選択
  pushButton(Button::A, 200, 3);
}
