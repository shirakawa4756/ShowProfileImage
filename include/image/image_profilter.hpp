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
     * プロファイルの高さを指定します.
     *
     * プロファイルをどの程度の高さで表示するか指定します．
     * 高ければ高いほど細かく表示されますが，プロファイル領域が大きくなります．
     *
     * ただし，既定の最小高さ(MIN_PROFILE_HEIGHT) 以下には指定できません．
     *
     * @param profileHeight プロファイルの高さ [px]
     *
     */
    void setProfileHeight(int profileHeight)
    {
        profileHeight_ = std::max(MIN_PROFILE_HEIGHT, profileHeight);
    }


    /**
     * 画像プロファイルを表示する Window の表題を取得します
     *
     * @return 表題名
     */
    std::wstring caption() const
    {
        return caption_;
    }


    /**
     * 画像プロファイルを表示する Window の表題を設定します．
     *
     * @param caption 表題名
     */
    void setCaption(const std::wstring &caption)
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
     * ポインタで示している場所の情報を表示する際のフォント書体を指定します
     *
     */
    static const int PUT_TEXT_FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;


    /**
     *
     */
    static const double PUT_TEXT_FONT_SIZE;


    static const int PUT_TEXT_THICKNESS = 1;

    /**
     *
     */
    static const cv::Scalar PUT_TEXT_COLOR;

    static const int DEFAULT_FONT_HEIGHT = 30;

    static const int MOUSE_POSITION_DEGIT = 4;

    static const int RGB_DEGIT = 3;

    static const int PUT_TEXT_RGB_X_OFFSET = 28;


    /**
     * プロファイルの表示を終了させるためのキーを設定します
     */
    static const int QUIT_KEY_SHOW_PROFILE = 'q';


    /**
     * cv::imshow で発生するコールバック関数を定義します
     */
    static void cvImShowCallBackFunc(int event, int x, int y, int flags, void* userdata);


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
     * 水平方向のプロファイルを描写します
     */
    void drawProfileHorizontal();


    /**
     *
     */
    void drawProfileLineHorizontal(const cv::Mat &col);


    /**
     *
     */
    void drawProfileVertical();


    /**
     *
     */
    void drawProfileLineVertical(const cv::Mat &col, const cv::Scalar color);


    /**
     *
     */
    void drawMousePositionCrossLine();


    /**
     *
     */
    void drawText();


    /**
     *
     */
    void drawTextMousePosition();


    /**
     *
     */
    void drawTextRGB();


    /**
     *
     */
    void drawTextBlue(uchar blue);


    /**
     *
     */
    void drawTextRed(uchar red);


    /**
     * 緑色
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
    std::wstring caption_;


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