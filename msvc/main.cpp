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
#include "stdafx.h"
#include <image/image_profilter.hpp>
#include <utility/open_file_dialog_winapi.hpp>


namespace {
/*******************************************************************************************/// ***
/**
 * Windows のパス区切りを定義します
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = '\\';



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
void fittingDisplayImageSize(const cv::Mat &src, int profileHeight, cv::Mat &dst)
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



/*******************************************************************************************/// ***
/**
 * メディアンフィルタを施す関数オブジェクトを定義します
 *
 * プロファイル表示しているとき，特定のキーを押すとメディアンフィルタを施すように
 * ImageProcessingCommand を継承したメディアンフィルタの関数オブジェクトを定義します．
 *
 *************************************************************************************************/
class MedianFilter : public show_profile_image::ImageProcessingCommand
{
public:
    MedianFilter()
      : kernelSize_(show_profile_image::DEFAULT_KERNEL_SIZE)
    {
    }


    virtual ~MedianFilter()
    {
    }


    virtual void operator()(const cv::Mat &src, cv::Mat &dst) const
    {
        cv::medianBlur(src, dst, kernelSize_);
    }


    virtual int kernelSize() const
    {
        return kernelSize_;
    }


    virtual void setKernelSize(int kernel)
    {
        kernelSize_ = kernel;
    }


private:
    int kernelSize_;
};



} // namespace



int _tmain(int argc, _TCHAR* argv[])
{
    using namespace show_profile_image;
    _tsetlocale(LC_ALL, _T(""));

    std::wstring filename;
    if (argc < 2) {
        filename = openFileDialog(L"画像ファイル (*.jpg;*tif;*png)|*.jpg;*tif;*png");
    } else {
        filename = std::wstring(argv[1]);
    }



    ImageProfiler imageProfiler;
    imageProfiler.setCaption(toString(createCaption(filename)));

    // m キーを押したとき，メディアンフィルタを施す
    imageProfiler.addImageProcessingCommand('m', std::make_shared<MedianFilter>());

    cv::Mat im = cv::imread(toString(filename));
    fittingDisplayImageSize(im, imageProfiler.profileHeight(), im);

    imageProfiler.setImage(im);
    imageProfiler.show();
    return 0;
}

