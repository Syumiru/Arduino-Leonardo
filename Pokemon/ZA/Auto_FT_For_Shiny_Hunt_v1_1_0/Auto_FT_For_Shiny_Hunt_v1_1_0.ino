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
int Sleep = 1;
//FT上限
//Switch1だとWZ19を1周約15秒500周で2時間くらい
//夜だと400では朝を迎える
int FTLmt = 300;
//十字キー下を押下する回数
int DownCnt = 18;
//ロード待ち時間(目安：Switch1→9.5秒だとダメなので10秒、Switch2→4秒)
int WaitLoadTime = 10000;

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
    //昼夜切替によるループ中断防止策
    //ダメそうならベンチで休憩する処理を追加する
    //時間帯限定ポケを考慮するなら長時間ループしないほうが良い
    //カメラ起動していた場合に備え、Bボタンでカメラを閉じる
    pushButton(Button::B, 100, 1);
    //＋ボタンでメニューを開く
    pushButton(Button::PLUS, 300, 1);
    //Yボタンで移動スポットを開く
    //昼夜切替によりローリング発生→ローリング中なので－ボタンを受け付けずAボタンでゾーン進入→敵対状態のコンボでFTできずループ中断される懸念はあるかも
    pushButton(Button::Y, 300, 1);
    //－ボタンでカテゴリを開く
    pushButton(Button::MINUS, 300, 1);
    //上十字キーでゾーンにカーソルを合わせる
    pushHat(Hat::UP, 100, 2);
    //Aボタンでゾーンを選択
    pushButton(Button::A, 300, 1);
    //下十字キーでゾーンにカーソルを合わせる
    //昼夜でバトルゾーンが増減するので下十字キーのみで操作し移動先指定ズレを防止
    //50でズレ発生60で安定（Switch1）
    pushHat(Hat::DOWN, 60, DownCnt);
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
