///////////////////////////////////////////////////////////////////////////////////////////////////
//
// 読み込んだ画像の縦横プロファイルを表示します．
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <image/image_profilter.hpp>


namespace {
#ifdef _WIN32
/*******************************************************************************************/// ***
/**
 * Windows のパス区切りを定義します
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = '\\';
#else
/*******************************************************************************************/// ***
/**
 * UNIX系 のパス区切りを定義します
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = L'/';
#endif



#ifdef _WIN32
/*******************************************************************************************/// ***
/**
 * ディスプレイの画面サイズを取得します
 *
 * 複数個のディスプレイが接続されていた場合はどうなるか分かりません．
 *
 * @param[out] width 横の解像度
 * @param[out] height 縦の解像度
 *
 *************************************************************************************************/
cv::Size getDisplaySize()
{
    const int width  = GetSystemMetrics(SM_CXSCREEN);
    const int height = GetSystemMetrics(SM_CYSCREEN);
    return cv::Size(width, height);
}
#endif



/*******************************************************************************************/// ***
/**
 * フルパスからファイル名を抽出します．
 *
 * 例えば，C:\dir\image\abc.png という文字列が入力された場合，
 * abc.png という文字列を返します．
 *
 * ex.
 *    C:\dir\image\abc.png  -> abc.png
 *
 * @param path フルパス名
 * @return ファイル名
 *
 *************************************************************************************************/
std::wstring getFilename(const std::wstring &path)
{
    std::wstring::size_type  pos = path.find_last_of(PATH_SEPARATOR);

    if (pos == std::wstring::npos) {
        return path;
    }

    return path.substr(pos + 1, path.size());
}



/*******************************************************************************************/// ***
/**
 * プロファイル情報を表示するウインドウの表題を作成します．
 *
 * 表題として，Profile Of `<filename>' という文字列を作成します．
 * 入力するファイル名は，フルパスでもよく，その場合は，ファイル名部分を抽出して
 * Profile Of `<filename>' という文字列を作成します．
 *
 * @param path フルパス
 * @return 表題
 *
 *************************************************************************************************/
std::wstring createCaption(const std::wstring &path)
{
    std::wstringstream wss;
    wss << L"Profile of "
        << "`"
        << getFilename(path.c_str())
        << "'";
    return wss.str();
}



/*******************************************************************************************/// ***
/**
 * プロファイル情報を表示する際，ディスプレイ解像度より大きくならないように元画像を縮小します
 *
 *************************************************************************************************/
void fittingDisplaySize(const cv::Mat &src, int profileHeight, cv::Mat &dst)
{
    // ウインドウのタイトルバーの高さ
    const int WINDOW_TITLE_HEIGHT = 80;

    // ディスプレイからはみ出ない画像サイズを計算する
    const cv::Size displaySize = getDisplaySize();
    const cv::Size fittingSize(displaySize.width - profileHeight,
                               displaySize.height - profileHeight - WINDOW_TITLE_HEIGHT);
    const cv::Point2d reduction(fittingSize.width / static_cast<double>(src.size().width),
                                fittingSize.height / static_cast<double>(src.size().height));
    const double reductionParcent = std::min(reduction.x, reduction.y);


    // 縮小する必要が無いときはそのまま終了する
    if (reductionParcent >= 1.0) {
        dst = src.clone();
        return;
    }

    // 元画像を縮小してディスプレイからはみ出ないようにする
    cv::resize(src, dst, cv::Size(), reductionParcent, reductionParcent, cv::INTER_LANCZOS4);
}

} // namespace



int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale(LC_ALL, _T(""));

    std::wstring filename;
    if (argc < 2) {
        filename = L"t.png";
    } else {
        filename = std::wstring(argv[1]);
    }


    show_profile_image::ImageProfiler imageProfiler;
    imageProfiler.setCaption(createCaption(filename));

    cv::Mat im = cv::imread(cv::fromUtf16(filename));
    fittingDisplaySize(im, imageProfiler.profileHeight(), im);

    imageProfiler.setImage(im);
    imageProfiler.show();

    return 0;
}

