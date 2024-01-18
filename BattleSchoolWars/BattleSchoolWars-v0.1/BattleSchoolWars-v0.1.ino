/**
 * 【PGM】
 * 学校最強大会自動周回
 * 【使用インクルードライセンス】
 * NintendoSwitchControll：MIT
 * © 2020 interimadd/takeutchi/kurimoun
 * https://github.com/interimadd/NintendoSwitchControll/blob/master/LICENSE.txt
 * 【配布元】
 * https://github.com/Syumiru/Arduino-Leonardo
 * 【開発者】
 * Syumiru(https://twitter.com/PokeSyumiru)
 * 【変更履歴】
 * v0.1 プロトタイプ作成
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
#include <auto_command_util.h>

//起動時の動作（Arduinoにおいて記述必須）
void setup() {
}

//ループ処理（Arduinoにおいて記述必須）
void loop() {
  //メイン処理
  Main();
}

//メイン処理
void Main() {
    //Aボタン
    pushButton(Button::A, 1, 10);

}
