/**
 * 【PGM】
 * そらとぶタイムアタック初級コース自動周回
 * 【使用インクルードライセンス】
 * NintendoSwitchControll：MIT
 * © 2020 interimadd/takeutchi/kurimoun
 * https://github.com/interimadd/NintendoSwitchControll/blob/master/LICENSE.txt
 * 【実行環境整備】
 * ①Switch本体ストレージにSVのデータがあることを確認する
 * ②Switch本体ストレージに5GB以上の空きを用意する
 * ③Arduino Leonardoおよび指定インクルードが使用可能であること
 * 【周回効率を上げるには～各環境でのPGM調整のコツ～】 
 * マイコンの挙動が不定なため、
 * 挙動の差分を許容するような設計にしてます
 * 1周動画(https://x.com/PokeSyumiru/status/1735492152917197304?s=20)に近い形に調整推奨です 
 * 3点想定しているポイントを挙げます
 * ①2つ目のリングまで通過
 * ②最初の山は多少擦っても良い
 * ③ゴール手前の川から高台を出るor川の横の山を擦りつつ高台を出る
 * 【実行手順】
 * ①ループ上限は初期値無制限
 * ②使いたい場合はセーブ/終了処理の有効化※誤動作した場合のリスクが大きくなります
 * ③1セーブ間のループ上限/ループ上限の変更※初期値はそれぞれ100/1000
 * ④キャニオンエリア受付前でPGM実行
 * 【配布元】
 * https://github.com/Syumiru/Arduino-Leonardo
 * 【開発者】
 * Syumiru(https://twitter.com/PokeSyumiru)
 * 【Special Thanks】
 * ・セーブ機能提案
 * 修行僧様(https://twitter.com/s1140044)
 * ・実行環境標準化のヒント提供
 * 修行僧様(https://twitter.com/s1140044)
 * はんぺん様(https://twitter.com/hanpen_switch)
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

//変数定義
//ループ回数
int LoopCnt;
//1セーブ間のループ上限
int SaveLmt = 100;
//ループ上限
int LoopLmt = 1000;

//起動時の動作（Arduinoにおいて記述必須）
void setup() {
  //Bボタンを10回連打しマイコン認識
  pushButton(Button::B, 200, 10);
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
    //End();
  }
}

//メイン処理
void Main() {
  //1セーブ間のループ上限を指定
  for (int i = 0; i < SaveLmt; i++) {
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
    //24.75秒wait
    delay(24750);
    //2個目のリングを潜るため右斜め上
    tiltJoystick(15,-100,0,0,1000);
    //2.4秒wait
    delay(2400);
    //ゴールに向かい左斜め上を入力
    tiltJoystick(-30,-50,0,0,3000);
    //10秒wait     
    delay(10000);
    //ゴールに向かい左斜め下を入力
    tiltJoystick(-70,50,0,0,400);
    //34秒wait     
    delay(34000);
    //会話をめくるためBボタン（失敗時に受付に話かけないようにするため）
    pushButton(Button::B, 1000, 3);
    //会話をめくるためBボタン（失敗時に受付に話かけないようにするため）
    pushButton(Button::B, 1000, 1);
    //5秒wait
    delay(5000);
    //ループ回数をインクリメント
    LoopCnt++;
  }
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
  pushHatButton(Hat::DOWN, 200, 1);
  //右十字キーを6回押下しスリープにカーソルを合わせる
  pushHatButton(Hat::RIGHT, 200, 6);
  //スリープを選択
  pushButton(Button::A, 200, 3);
}
