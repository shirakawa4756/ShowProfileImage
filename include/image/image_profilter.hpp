///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) 2015, shirakawa4756@github.com
// All rights reserved.
//
// * 2 clause BSD license
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//   
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//
// * 二条項BSDライセンス　和訳
//
// Copyright (c) 2015, shirakawa4756@github.com
// All rights reserved.
//
// ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
// 以下の条件を満たす場合に限り、再頒布および使用が許可されます。
//
// 1. ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
//    および下記免責条項を含めること。
//
// 2. バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
//    資料に、上記の著作権表示、本条件一覧、および下記免責条項を含
//    めること。
//
// 本ソフトウェアは、著作権者およびコントリビューターによって「現状のまま」提供されており、
// 明示黙示を問わず、商業的な使用可能性、および特定の目的に対する適合性に関する暗黙の保証
// も含め、またそれに限定されない、いかなる保証もありません。
// 著作権者もコントリビューターも、事由のいかんを問わず、損害発生の原因いかんを問わず、
// かつ責任の根拠が契約であるか厳格責任であるか（過失その他の）不法行為であるかを問わず、
// 仮にそのような損害が発生する可能性を知らされていたとしても、本ソフトウェアの使用に
// よって発生した（代替品または代用サービスの調達、使用の喪失、データの喪失、利益の喪失、
// 業務の中断も含め、またそれに限定されない）直接損害、間接損害、偶発的な損害、特別損害、
// 懲罰的損害、または結果損害について、一切責任を負わないものとします。
//
//
// 読み込んだ画像の縦横プロファイルを表示します．
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SHOW_PROFILE_IMAGE_IMAGE_PROFILTER_HPP
#define SHOW_PROFILE_IMAGE_IMAGE_PROFILTER_HPP

#include <algorithm>
#include <string>

#include <opencv2/core/core.hpp>

namespace show_profile_image {
/*******************************************************************************************/// ***
/**
 * 入力された画像のプロファイルを表示します.
 *
 * 入力された画像(8bit 3チャンネル)の縦横のプロファイル画像を表示します．
 * 表示されたウインドウ上のマウスポインタで示された座標を中心に縦と横のプロファイルを
 * 表示します．
 *
 * 入力画像の大きさには制限はありませんが，元画像の大きさに加え，縦横共にプロファイルを表示する
 * 領域が追加されるため，元画像の大きさが大きすぎると表示されるウインドウはモニター以上になります．
 *
 * 表示させたウインドウを閉じる(終了する)ときは，'q' キーを押してください．
 *
 *
 * 画像を表示するための最小のコードは以下の通りです．
 *
 * @code
 * #include <opencv2/opencv.hpp>
 *
 * int main(int argc, char *argv[]) 
 * {
 *     cv::Mat im = cv::imread("lena.jpg");
 *
 *     show_prfile_image::ImageProfiler imageProfiler;
 *     imageProfiler.setImage(im);
 *     imageProfiler.show();
 *     
 *     return 0;
 * }
 * @endcode
 *
 *************************************************************************************************/
class ImageProfiler
{
public:
    /**
     * コンストラクタ
     */
    ImageProfiler();


    /**
     * プロファイルを表示する画面を表示させます
     */
    void show();


    /**
     * プロファイルの高さをピクセル数で取得します．
     *
     * @return プロファイルの高さ
     */
    int profileHeight() const
    {
        return profileHeight_;
    }


    /**
     * 画像プロファイルを表示する Window の表題を取得します
     *
     * @return 表題名
     */
    std::string caption() const
    {
        return caption_;
    }


    /**
     * 画像プロファイルを表示する Window の表題を設定します．
     *
     * @param caption 表題名
     */
    void setCaption(const std::string &caption)
    {
        caption_ = caption;
    }


    /**
     * プロファイルを表示する対象の画像を設定します
     *
     * @param image 元画像
     *
     */
    void setImage(const cv::Mat &image)
    {
        image_ = image;
    }


private:
    /**
     * 最小プロファイルの高さを示します
     */
    static const int MIN_PROFILE_HEIGHT = 64;


    /**
     * 既定のプロファイルの高さを定義します
     *
     * 予めプロファイル高さを定義しておくことにより，
     * 特別にプロファイルを高さを指定しなくても画像プロファイルを見られるようにします．
     */
    static const int DEFAULT_PROFILE_HEIGHT = 128;


    /**
     * プロファイル領域のマージンを設定します
     *
     * プロファイルを表示する領域の上下または，左右に対し
     * 間隔を設けることによって最小値と最大値を見やすくします．
     */
    static const int MARGIN_PROFILE_HEIGHT = 16;


    /**
     * 既定のプロファイル線の線幅を定義します
     *
     * 予めプロファイル線の線幅を定義しておくことにより，
     * 特別にプロファイル線の線幅を指定しなくても画像プロファイルを見られるようにします．
     */
    static const int DEFAULT_PROFILE_LINE_WIDTH = 1;


    /**
     * プロファイル線を描く際の近傍数を定義します
     *
     * プロファイル線は，cv::line によって描写しますが，
     * そのときの近傍数(どのような連結度で線を描くか)を指定します
     */
    static const int DEFAULT_PROFILE_LINE_NEIGHBORHOOD = 8;


    /**
     * プロファイルを表示する領域の背景色を設定します
     */
    static const cv::Scalar PROFILE_LINE_BACKGROUND_COLOR;


    /**
     * プロファイル線の各色を示します
     *
     * プロファイル線は，各色(赤，緑，青)に応じて，
     * 色を変えて表示しますが，その色を指定します．
     *
     * その順序は次の通りです．
     *   0: 青色のプロファイル線
     *   1: 緑色のプロファイル線
     *   2: 赤色のプロファイル線
     */
    static const cv::Scalar PROFILE_LINE_STROKE_COLORS[3];



    /**
     * ポインタで示している場所の情報を表示する際のフォント書体を設定します
     */
    static const int PUT_TEXT_FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;


    /**
     * 表示するフォントのサイズを設定します
     */
    static const double PUT_TEXT_FONT_SIZE;


    /**
     * 表示するフォント太さを設定します
     */
    static const int PUT_TEXT_THICKNESS = 1;


    /**
     * 表示するフォントの色を定義します
     */
    static const cv::Scalar PUT_TEXT_COLOR;


    /**
     * 表示するフォントの行間を設定します
     * 
     * 行間をピクセル単位で指定します
     */
    static const int DEFAULT_LINE_HEIGHT = 30;


    /**
     * マウス位置の桁数を指定します
     *
     * 5桁になることは滅多にないので4桁に指定します.
     */
    static const int MOUSE_POSITION_DEGIT = 4;


    /**
     * マウス位置の色情報を表示する際の桁数を設定します
     *
     * 8bit 画像を読み込みことを前提としているので 3桁分を指定します.
     */
    static const int RGB_DEGIT = 3;


    /**
     * マウス位置の色情報を表示する位置の左マージンを指定します
     *
     */
    static const int PUT_TEXT_RGB_MARGIN_LEFT = 28;


    /**
     * プロファイルの表示を終了させるためのキーを設定します
     */
    static const int QUIT_KEY_SHOW_PROFILE = 'q';


    /**
     * cv::imshow で発生するコールバック関数を定義します
     */
    static void cvImShowCallBackFunc(int event, int x, int y, int flags, void* userdata);


    /**
     * プロファイルウインドウのマウスやキーボードの状態を更新し(受け取り)ます
     *
     * 実際には，cvImShowCallBackFunc から各引数が丸投げされます
     */
    void updateWindowStatus(int mouseEvent, int x, int y, int flags);


    /**
     * プロファイルを表示するための基本的な構成を生成します
     *
     * 入力画像のプロファイルを表示するために以下を作成します．
     *    1. 元画像
     *    2. 横方向のプロファイルを表示するための領域
     *    3. 縦方向のプロファイルを表示するための領域
     *    4. マウスポインタを起点として縦横の線を引く
     *    5. 現在位置と各色の輝度値を表示
     *
     */
    void createShowProfileImage();


    /**
     * プロファイルを表示するための基本的な構成を生成します
     *
     * 入力画像のプロファイルを表示するために以下を作成します．
     *    1. 元画像
     *    2. 横方向のプロファイルを表示するための領域
     *    2. 縦方向のプロファイルを表示するための領域
     *
     */
    void createProfileBaseImage();



    /**
     * 水平方向のプロファイルを描写します.
     */
    void drawProfileHorizontal();


    /**
     * 水平方向のプロファイル線を描きます.
     */
    void drawProfileLineHorizontal(const cv::Mat &col, const cv::Scalar color);


    /**
     * 垂直方向のプロファイルを表示します.
     */
    void drawProfileVertical();


    /**
     * 垂直方向のプロファイルを描きます
     */
    void drawProfileLineVertical(const cv::Mat &col, const cv::Scalar color);


    /**
     * 現在のマウス位置上に十字線を描きます
     */
    void drawMousePositionCrossLine();


    /**
     * テキストを描写します.
     *
     * マウス位置の座標とその色情報を示します
     */
    void drawText();


    /**
     * 現在のマウス位置(画像座標)を表示します
     */
    void drawTextMousePosition();


    /**
     * マウス位置のRGB値を表示します
     */
    void drawTextRGB();


    /**
     * 青色(B)の値を表示します
     */
    void drawTextBlue(uchar blue);


    /**
     * 緑色(R)の値を表示します
     */
    void drawTextRed(uchar red);


    /**
     * 赤色(R)の値を表示します
     */
    void drawTextGreen(uchar green);

    

    /** 
     * 表示用の画像に指定したテキストを表示させます
     *
     * プロファイル表示用画像に指定した場所に文字列を表示させます．
     *
     * @param text 表示させる文字列
     * @param point 表示させる場所
     */
    void putText(const std::string &text, const cv::Point &point);


    /**
     * window の表示名を示します
     */
    std::string caption_;


    /**
     * プロファイルの高さを示します
     */
    int profileHeight_;


    /**
     * 元画像を示します.
     *
     * CV_8UC3 を想定しています．
     */
    cv::Mat image_;


    /**
     * プロファイルを含めた表示する画像を示します
     */
    cv::Mat show_;


    /**
     * マウスポインタで指し示された現在の画像座標を保持します
     *
     * cv::imshow で表示された画像に対しマウスポインタがどの座標を指しているのか保存します．
     */
    cv::Point nowMousePosition_;


    /**
     * プロファイルを描写する線分の太さを表します
     */
    int lineWidthProfile_;


    /**
     * フォントサイズを示します
     */
    int fontSize_;


    /**
     * フォントの高さを示します
     */
    int fontHeight_;


    ///////////////////////////////////////////////////////////////////////////////////////////////
    //
    //
    // コピーコンストラクタと代入演算子による代入操作を禁止します.
    //
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ImageProfiler(const ImageProfiler &rhs);
    ImageProfiler& operator=(const ImageProfiler &rhs);
};
} // namespace show_profile_image
#endif