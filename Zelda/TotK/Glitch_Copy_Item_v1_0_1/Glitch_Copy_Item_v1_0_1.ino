/**
 * 【PGM】
 * ver1.0.0対応アイテム増殖グリッチ自動化
 * 【使用インクルードライセンス】
 * NintendoSwitchControlLibrary：MIT
 * © 2021 lefmarna/troter
 * https://github.com/lefmarna/NintendoSwitchControlLibrary/blob/master/LICENSE
 * 【実行環境整備】
 * ①TotK ver1.0.0
 * ②増殖するアイテムを用意
 * ③地底の安全地帯でミネルゴーレムに乗る
 * 【実行手順】
 * ①ループ上限は初期値無制限
 * ②1セーブ間のループ上限/ループ上限の変更※初期値はそれぞれ100/1000
 * ③増殖したいアイテムにカーソルをあわせPGM実行
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
//ループ回数
int LoopCnt;
//1セーブ間のループ上限
int SaveLmt = 1000;
//ループ上限
int LoopLmt = 200;

//起動時の動作（Arduinoにおいて記述必須）
void setup() {
  //Bボタンを10回連打しマイコン認識
  pushButton(Button::B, 200, 10);
  //Aボタンでコントローラ認識画面からゲーム画面に戻る
  pushButton(Button::A, 200, 1);
  //ディレイ
  delay(1000);
}

//ループ処理（Arduinoにおいて記述必須）
void loop() {
  //メイン処理
  Main();
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
    //アイテムを選択するためAボタン
    pushButton(Button::A, 100, 1);
    //手に持つにカーソルを合わせるため下十字キー
    pushHat(Hat::DOWN, 200, 1);
    //手に持つを選択するためAボタン
    pushButton(Button::A, 100, 5);
    //ディレイ
    delay(100);
    //アイテムを並び替えるためYボタン    
    SwitchControlLibrary().pressButton(Button::Y);
    //メニュー画面を閉じるためBボタン
    SwitchControlLibrary().pressButton(Button::B);
    //YB同時押しコマンド送信
    SwitchControlLibrary().sendReport();
    //ディレイ
    delay(100);
    //アイテムを並び替えるためYボタン    
    SwitchControlLibrary().releaseButton(Button::Y);
    //メニュー画面を閉じるためBボタン
    SwitchControlLibrary().releaseButton(Button::B);
    //YB同時押しコマンド送信
    SwitchControlLibrary().sendReport();
    //ディレイ
    delay(1100);
    //アイテムを拾うためAボタン(たまにアイテムを取りこぼしているので多めに)
    pushButton(Button::A, 100, 6);
    //メニュー画面を開くため+ボタン
    pushButton(Button::PLUS, 200, 1);
    //ループ回数をインクリメント
    LoopCnt++;
  }
}

//処理終了
void End() {
  //HOMEボタンでswitchメニュー表示
  pushButton(Button::HOME, 1000);
  //下十字キーを押下しNintendo Switch Onlineにカーソルを合わせる
  pushHat(Hat::DOWN, 200, 1);
  //右十字キーを8回押下しスリープにカーソルを合わせる
  pushHat(Hat::RIGHT, 200, 8);
  //スリープを選択
  pushButton(Button::A, 200, 3);
}
