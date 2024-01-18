/**
 * 【PGM】
 * ポケモンSV ~ver1.1.0 バグイドンアイテム増殖グリッチ
 * 【使用インクルードライセンス】
 * NintendoSwitchControll：MIT
 * © 2020 interimadd/takeutchi/kurimoun
 * https://github.com/interimadd/NintendoSwitchControll/blob/master/LICENSE.txt
 * 【実行環境整備】
 * ①Arduino Leonardoおよび指定インクルードが使用可能であること
 * 【実行環境整備（ソフト）】
 * 以下を参照してください
 * https://syumiru-pokemon.blogspot.com/2022/12/SVver1.1.0glitch.html
 * 【実行手順】
 * 以下を参照してください
 * https://syumiru-pokemon.blogspot.com/2022/12/SVver1.1.0glitch.html
 * 【配布元】
 * https://github.com/Syumiru/Arduino-Leonardo
 * 【開発者】
 * Syumiru(https://twitter.com/PokeSyumiru)
 * 【変更履歴】
 * v2.5.1 ライセンス追記等
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
#include <auto_command_util.h>

//使用グローバル変数
//1アイテム毎の上限ループ回数設定
int LoopCnt = 990;
//上限処理回数設定
int LmtCnt = 1980;
//対象メニュー(1:ボール、3:きのみ、4:どうぐ、5:わざマシン)
int Num = 4;
//ループ回数カウント
int Cnt;

//起動時の動作（Arduinoにおいて記述必須）
void setup() {
}

//ループ処理（Arduinoにおいて記述必須）
void loop() {
  //メイン処理
  Main();
  //終了処理
  End();
  //アイテム入替
  SwitchItems();
}

//メイン処理
void Main() {
  //ループ回数を指定
  for (int i = 0; i < LoopCnt; i++) {
    //メイン処理前の状況にリセット
    Reset();
    //○ライドンを選択しサブメニューを開く
    pushButton(Button::A, 100, 1);
    //1回目で上ボタンを入力し「やめる」へカーソルを合わせる
    pushHatButton(Hat::UP, 100, 1);
    //2回目で上ボタンを入力し「ライドフォルムに戻す」へカーソルを合わせる
    pushHatButton(Hat::UP, 100, 1);
    //「ライドフォルムに戻す」を選択
    pushButton(Button::A, 300, 1);
    //メッセージ「○ライドンをライドフォルムにしますか？」が表示されるため選択肢ポップアップを表示する
    pushButton(Button::A, 300, 1);
    pushButton(Button::A, 300, 1);
    //「はい」を選択
    pushButton(Button::A, 2200, 1);
    //メッセージ「○ライドンはライドフォルムに変化した！」を閉じる
    pushButton(Button::A, 300, 1);
    //手持ちの○ライドンにカーソルを合わせる
    pushHatButton(Hat::UP, 100, 1);
    //右にカーソルを合わせる
    pushHatButton(Hat::RIGHT, 100, 1);
    //Aボタンを押下しボックスを開く
    pushButton(Button::A, 2000, 1);
    //もちものに切替
    pushButton(Button::X, 100, 1);
    //バトルチームに切替
    pushButton(Button::X, 100, 1);
    //○ライドンボックスに切替
    pushButton(Button::L, 100, 1);
    //○ライドンを選択しサブメニューを開く
    pushButton(Button::A, 100, 1);
    //下ボタンを1回押下し「強さを見る」にカーソルを合わせる
    pushHatButton(Hat::DOWN, 200, 1);
    //下ボタンを1回押下し「もちものを変える」にカーソルを合わせる
    pushHatButton(Hat::DOWN, 200, 1);
    //下ボタンを1回押下し「もちものをしまう」にカーソルを合わせる
    pushHatButton(Hat::DOWN, 200, 1);
    //「もちものをしまう」を選択
    pushButton(Button::A, 300, 1);
    //ループ回数をインクリメント
    Cnt++;
  }
}

//メイン処理前の状況にリセット
void Reset() {
  //Bボタンを10回連打しメインメニュー前まで戻す
  pushButton(Button::B, 200, 10);
  //メインメニューを開く
  pushButton(Button::X, 600, 1);
  //左十字キーを押下し手持ちにカーソルを合わせる
  pushHatButton(Hat::LEFT, 200, 1);
  //上十字キーを押し続け先頭の手持ちにカーソルを合わせる
  pushHatButtonContinuous(Hat::UP, 500);
  //下十字キーを押下し再度○ライドンにカーソルを合わせる
  pushHatButton(Hat::DOWN, 200, 1);
}

//アイテム持ち替え
void SwitchItems() {
  //Bボタンを10回連打しメインメニュー前まで戻す
  pushButton(Button::B, 200, 10);
  //メインメニューを開く
  pushButton(Button::X, 500, 1);
  //右十字キーを押し続けメインメニューにカーソルを合わせる
  pushHatButtonContinuous(Hat::RIGHT, 500);
  //上十字キーを押し続けバッグにカーソルを合わせる
  pushHatButtonContinuous(Hat::UP, 1000);
  //バッグを選択
  pushButton(Button::A, 500, 1);
  //対象メニューにカーソルを合わせる
  pushHatButton(Hat::RIGHT, 200, Num);
  //お気に入りを外す
  pushButton(Button::PLUS, 200, 1);
  //対象を選択
  pushButton(Button::A, 200, 1);
  //下十字キーを押下し「もたせる」にカーソルを合わせる
  pushHatButton(Hat::DOWN, 200, 1);
  //「もたせる」を選択
  pushButton(Button::A, 200, 1);
  //下十字キーを押下し○ライドンにカーソルを合わせる
  pushHatButton(Hat::DOWN, 200, 1);
  //○ライドンを選択
  pushButton(Button::A, 300, 1);
  //「はい」を選択
  pushButton(Button::A, 300, 1);
  //メッセージ「持たせた！」をおくる
  pushButton(Button::A, 300, 1);
}

//処理終了
void End() {
  //処理回数が上限に到達した場合
  if ( Cnt >= LmtCnt ) {
    //HOMEボタンでswitchメニュー表示
    pushButton(Button::HOME, 500);
    //下十字キーを押下しNintendo Switch Onlineにカーソルを合わせる
    pushHatButton(Hat::DOWN, 200, 1);
    //右十字キーを6回押下しスリープにカーソルを合わせる
    pushHatButton(Hat::RIGHT, 200, 6);
    //スリープを選択
    pushButton(Button::A, 200, 3);
  }
}
