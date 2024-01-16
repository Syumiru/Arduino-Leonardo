/**
 * 【PGM】
 * 野生ポケモン所持アイテム入手自動化
 * 【使用インクルードライセンス】
 * NintendoSwitchControlLibrary：MIT
 * © 2021 lefmarna/troter
 * https://github.com/interimadd/NintendoSwitchControll/blob/master/LICENSE.txt
 * 【実行環境整備】
 * ①Switch本体ストレージにSVのデータがあることを確認する
 * ②Switch本体ストレージに5GB以上の空きを用意する
 * ③Arduino Leonardoおよび指定インクルードが使用可能であること
 * 【実行環境整備（ソフト）】
 * ①HPを全回復するアイテム（例：まんたんのくすり）のみをお気に入り登録し大量購入
 * ②極力他のポケモンが沸きにくい場所をロケハンしておく
 * ③メインメニューのカーソルは先頭ポケモンに合わせておく（後でデフォルトカーソル位置を確認しコード修正する
 * 【実行手順】
 * ①ループ上限は初期値無制限
 * ②使いたい場合はセーブ/終了処理の有効化※誤動作した場合のリスクが大きくなります
 * ③1セーブ間のループ上限/ループ上限の変更※初期値はそれぞれ100/1000
 * ④自動1周は戦闘画面でスタート
 * 【配布元】
 * https://github.com/Syumiru/Arduino-Leonardo
 * 【開発者】
 * Syumiru(https://twitter.com/PokeSyumiru)
 * 【Special Thanks】
 * なし
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
//わざ使用回数
int MoveCnt;
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
    //対象ポケモンをロックオンするため長押し開始
    SwitchControlLibrary().pressButton(Button::ZL);
    //1.5秒wait
    delay(1500);
    //ロックオン失敗の課題未解決のため試行錯誤中
    //緩やかでも坂道の下から上はダメっぽい？

    //カメラ追従設定あれば以下の処理要らないかも
    //戦闘でカメラが右にずれるから正面に合わせるための右にずらす処理だけで良いかも
    // 右スティックを右に0.15秒間倒す
    tiltRightStick(191, 128, 100);
    // 右スティックを左に0.30秒間倒す
    //tiltRightStick(64, 128, 200);
    // 右スティックを上に0.15秒間倒す
    //tiltRightStick(128, 192, 100);
    //対象ポケモンを捜索するため1秒に1回時計回りにスティックぐるぐる
    //spinRightStick(1000,1,1);
    
    //対象ポケモンにボールを投げるためZRを押下
    pushButton(Button::ZR, 1000, 1);
    
    //入力漏れっぽいのがあり周回が止まるため試行錯誤済
    //対象ポケモンにボールを投げるため1秒長押し
    //holdButton(Button::ZR, 1000);
    //手持ちポケモンを回収するためZRを押下
    //pushButton(Button::ZR, 2000, 1);
    //対象ポケモンにボールを投げるため2秒長押し
    //holdButton(Button::ZR, 2000);
    
    //長押し終了
    SwitchControlLibrary().releaseButton(Button::ZL);
    //6秒wait(不意をついた場合に長めに時間が必要)
    delay(6000);
    //たたかうを選択するためAボタン    
    pushButton(Button::A, 500, 1);
    if ( MoveCnt >= 10 ) {
      //下十字キーを押下し2番目のわざにカーソルを合わせる
      pushHat(Hat::DOWN, 500, 1);
    }
    //わざを選択するためAボタン(急所考慮で22秒)※26秒で回してた場合もあったのでブレがあるかも
    pushButton(Button::A, 22000, 1);
    //上十字キーを押下しにげるにカーソルを合わせる(500ミリでは入力抜けが起きた)
    pushHat(Hat::UP, 750, 1);
    //にげるを選択するためAボタン
    pushButton(Button::A, 500, 1);
    //3秒wait※元々4秒
    delay(3000);
    //ループ回数をインクリメント
    LoopCnt++;
    //わざ使用回数をインクリメント
    MoveCnt++;
    //20回わざを使用した場合
    if ( MoveCnt == 20 ) {
      //ポケモン回復
      RecoveryPokemon();
      //リセットするため技使用回数をクリア
      MoveCnt = 0;
    }
  }
}

//ポケモン回復
void RecoveryPokemon() {
  //1.5秒wait
  delay(1500);
  //メインメニューを開く
  pushButton(Button::X, 2000, 1);
  
  //HP回復
  //右十字キーを押下しバッグにカーソルを合わせる
  pushHat(Hat::RIGHT, 200, 1);
  //Aボタンでバッグを開く
  pushButton(Button::A, 1000, 1);
  //Aボタンでまんたんのくすりを選択
  pushButton(Button::A, 1000, 1);
  //Aボタンでつかうを選択
  pushButton(Button::A, 1000, 1);
  //Aボタンで先頭ポケモンを選択
  pushButton(Button::A, 2000, 1);
  //Bボタンでテキストおくり
  pushButton(Button::B, 1000, 1);
  //Bボタンでバッグを閉じる
  pushButton(Button::B, 1000, 1);

  //PP回復
  //左十字キーを押下し先頭ポケモンにカーソルを合わせる
  pushHat(Hat::LEFT, 200, 1);
  //先頭ポケモンを選択
  pushButton(Button::A, 1000, 1);
  //強さを見るを選択
  pushButton(Button::A, 1000, 1);
  //2秒追加待機
  delay(2000);
  //右十字キーを押下しステータスを表示
  pushHat(Hat::RIGHT, 200, 1);
  //わざを2つ忘れる
  Poof();
  //わざを2つ思い出す
  Remind();
  //わざを並び替える
  Switch();
  
  //Bボタンでメインメニュー画面へ戻る
  pushButton(Button::B, 1000, 1);
  //Bボタンでメインメニュー画面を閉じる
  pushButton(Button::B, 1000, 1);

}

//技忘れ処理
void Poof() {
  for (int j = 0; j < 2; j++) {
    //Aボタンでわざを思い出す/忘れるを選択
    pushButton(Button::A, 1500, 1);
   //下十字キーを押下しわざを忘れるにカーソルを合わせる
    pushHat(Hat::DOWN, 200, 1);
    //Aボタンでわざを忘れるを選択
    pushButton(Button::A, 1500, 1);
    //Aボタンでわざ1を選択
    pushButton(Button::A, 1500, 1);
    //Aボタンではいを選択
    pushButton(Button::A, 3000, 1);
    //Bボタンでメッセージ送り
    pushButton(Button::B, 1500, 1);
    //Bボタンでメッセージ送り
    pushButton(Button::B, 1500, 1);
  }
}

//技思い出し処理
void Remind() {
  for (int j = 0; j < 2; j++) {
    //Aボタンでわざを思い出す/忘れるを選択
    pushButton(Button::A, 1500, 1);
    //Aボタンでわざを思い出すを選択
    pushButton(Button::A, 1500, 1);
    //2週目の場合
    if ( j == 1 ) {
      //下十字キーを押下し2番目のわざにカーソルを合わせる
      pushHat(Hat::DOWN, 1000, 1);
      //下十字キーを押下し3番目のわざにカーソルを合わせる
      pushHat(Hat::DOWN, 1000, 1);
    }
    //Aボタンでわざを選択
    pushButton(Button::A, 1500, 1);
    //Aボタンではいを選択
    pushButton(Button::A, 1500, 1);
    //Bボタンでメッセージ送り
    pushButton(Button::B, 1500, 1);
  }
}

//技並び替え処理
void Switch() {
  //Yボタンでならびかえを選択
  pushButton(Button::Y, 1000, 1);

  //3つ目のわざを1つ目に並び替え
  //Aボタンでわざを選択
  pushButton(Button::A, 1000, 1);
  //下十字キーを押下し下にカーソルを合わせる
  pushHat(Hat::DOWN, 200, 1);
  //下十字キーを押下し下にカーソルを合わせる
  pushHat(Hat::DOWN, 200, 1);
  //Aボタンでわざを選択
  pushButton(Button::A, 1000, 1);

  //4つ目のわざを2つ目に並び替え
  //下十字キーを押下し下にカーソルを合わせる
  pushHat(Hat::DOWN, 200, 1);
  //Aボタンでわざを選択
  pushButton(Button::A, 1000, 1);
  //上十字キーを押下し上にカーソルを合わせる
  pushHat(Hat::UP, 200, 1);
  //上十字キーを押下し上にカーソルを合わせる
  pushHat(Hat::UP, 200, 1);
  //Aボタンでわざを選択
  pushButton(Button::A, 1000, 1);
  
  //Bボタンでステータス画面へ戻る
  pushButton(Button::B, 1000, 1);
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
