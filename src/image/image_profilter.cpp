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
//
// 読み込んだ画像の縦横プロファイルを表示します．
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "image/image_profilter.hpp"

#ifndef USE_PRE_COMPLIE_HEADER
#   include <iomanip>
#   include <string>
#   include <sstream>
#
#   include <opencv2/opencv.hpp>
#   include <opencv2/opencv_library_reader.hpp>
#endif

#include "misc/string_convert.hpp"



namespace show_profile_image {
// 既定のウインドウ表題
const std::string DEFAULT_CAPTION = "Profile";

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// ShowProfile Class
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
const cv::Scalar ImageProfiler::PROFILE_LINE_BACKGROUND_COLOR = cv::Scalar::all(64);

const cv::Scalar ImageProfiler::PROFILE_LINE_STROKE_COLORS[3] = {
    CV_RGB(64, 160, 255), CV_RGB(64, 255, 64), CV_RGB(255, 64, 16)
};

const double ImageProfiler::PUT_TEXT_FONT_SIZE = 0.65;

const cv::Scalar ImageProfiler::PUT_TEXT_COLOR = cv::Scalar::all(255);


ImageProfiler::ImageProfiler()
  : profileHeight_(DEFAULT_PROFILE_HEIGHT),
    lineWidthProfile_(DEFAULT_PROFILE_LINE_WIDTH),
    fontHeight_(DEFAULT_LINE_HEIGHT),
    caption_(DEFAULT_CAPTION)
{
}



void ImageProfiler::cvImShowCallBackFunc(int event, int x, int y, int flags, void *imageProfilerPtr)
{
    ImageProfiler *profiler = static_cast<ImageProfiler*>(imageProfilerPtr);
    profiler->updateWindowStatus(event, x, y, flags);
}



void ImageProfiler::updateWindowStatus(int , int x, int y, int )
{
    nowMousePosition_.x = x;
    nowMousePosition_.y = y;
}



void ImageProfiler::show()
{
    // ウインドウの更新間隔を 60 fps にする
    static const int UPDATE_WINDOW_INTERVAL_60FPS = static_cast<int>(1000.0 / 60.0);

    cv::namedWindow(caption_);
    cv::setMouseCallback(caption_,
                         &ImageProfiler::cvImShowCallBackFunc, 
                         static_cast<void*>(this));

    int key = 0;
    while (tolower(key) != QUIT_KEY_SHOW_PROFILE) {
        createShowProfileImage();

        cv::imshow(caption_, show_);
        key = cv::waitKey(UPDATE_WINDOW_INTERVAL_60FPS);
    }
    cv::destroyWindow(caption_);
}



void ImageProfiler::createShowProfileImage()
{
    createProfileBaseImage();

    if (nowMousePosition_.x >= image_.cols - 1) return;
    if (nowMousePosition_.y >= image_.rows - 1) return;

    drawProfileHorizontal(); 
    drawProfileVertical();
    drawMousePositionCrossLine();
    drawText();
}


void ImageProfiler::createProfileBaseImage()
{
    cv::Size size(image_.cols + profileHeight_ + 2 * MARGIN_PROFILE_HEIGHT,
                  image_.rows + profileHeight_ + 2 * MARGIN_PROFILE_HEIGHT);
    show_.create(size, CV_8UC3);
    show_ = PROFILE_LINE_BACKGROUND_COLOR;


    cv::Mat src = show_(cv::Rect(0, 0, image_.cols, image_.rows));
    image_.copyTo(src);
}



void ImageProfiler::drawProfileHorizontal()
{
    const cv::Mat &horizon = image_.row(nowMousePosition_.y);

    std::vector<cv::Mat> mv;
    cv::split(horizon, mv);

    for (std::vector<cv::Mat>::size_type i = 0; i < mv.size(); ++i)
    {
        drawProfileLineHorizontal(mv[i], PROFILE_LINE_STROKE_COLORS[i]);
    }
}


void ImageProfiler::drawProfileLineHorizontal(const cv::Mat &horizon, const cv::Scalar color)
{
    const double scale = profileHeight_ / static_cast<double>(UCHAR_MAX);
    const int    offset = image_.rows + MARGIN_PROFILE_HEIGHT;

    cv::MatConstIterator_<uchar> it  = horizon.begin<uchar>();
    cv::MatConstIterator_<uchar> end = horizon.end<uchar>() - 1;

    for (int col = 0; it != end; ++it, ++col) {
        const int startLevel = static_cast<int>((UCHAR_MAX - *it) * scale + offset);
        const int endLevel   = static_cast<int>((UCHAR_MAX - *(it + 1)) * scale + offset);
        const cv::Point start(col, startLevel);
        const cv::Point end(col + 1, endLevel);

        cv::line(show_, start, end, color, lineWidthProfile_, DEFAULT_PROFILE_LINE_NEIGHBORHOOD);
    }
}



void ImageProfiler::drawProfileVertical()
{
    cv::Mat vertical = image_.col(nowMousePosition_.x);

    std::vector<cv::Mat> mv;
    cv::split(vertical, mv);

    for (std::vector<cv::Mat>::size_type i = 0; i < mv.size(); ++i)
    {
        drawProfileLineVertical(mv[i], PROFILE_LINE_STROKE_COLORS[i]);
    }
}



void ImageProfiler::drawProfileLineVertical(const cv::Mat &vertical, const cv::Scalar color)
{
    const double scale = profileHeight_ / static_cast<double>(UCHAR_MAX);
    const int    offset = image_.cols + MARGIN_PROFILE_HEIGHT;

    cv::MatConstIterator_<uchar> it  = vertical.begin<uchar>();
    cv::MatConstIterator_<uchar> end = vertical.end<uchar>() - 1;

    for (int row = 0; it != end; ++it, ++row) {
        const int startLevel = static_cast<int>((UCHAR_MAX - *it) * scale + offset);
        const int endLevel   = static_cast<int>((UCHAR_MAX - *(it + 1)) * scale + offset);
        const cv::Point start(startLevel, row);
        const cv::Point end(endLevel, row + 1);

        cv::line(show_, start, end, color, lineWidthProfile_, DEFAULT_PROFILE_LINE_NEIGHBORHOOD);
    }
}



void ImageProfiler::drawMousePositionCrossLine()
{
    cv::line(show_,
             cv::Point(0, nowMousePosition_.y),
             cv::Point(show_.cols, nowMousePosition_.y),
             cv::Scalar::all(UCHAR_MAX),
             lineWidthProfile_,
             DEFAULT_PROFILE_LINE_NEIGHBORHOOD);


    cv::line(show_,
             cv::Point(nowMousePosition_.x, 0),
             cv::Point(nowMousePosition_.x, show_.rows),
             cv::Scalar::all(UCHAR_MAX),
             lineWidthProfile_,
             DEFAULT_PROFILE_LINE_NEIGHBORHOOD);

}



void ImageProfiler::drawText()
{
    drawTextMousePosition();
    drawTextRGB();
}



void ImageProfiler::drawTextMousePosition()
{
    std::stringstream ss;
    ss << "("
       << std::setw(MOUSE_POSITION_DEGIT)
       << nowMousePosition_.x
       << ", "
       << std::setw(MOUSE_POSITION_DEGIT)
       << nowMousePosition_.y
       << ")";

    const cv::Point p(image_.cols + MARGIN_PROFILE_HEIGHT, 
                      image_.rows + MARGIN_PROFILE_HEIGHT + fontHeight_);
    putText(ss.str(), p);
}


void ImageProfiler::drawTextRGB()
{
    cv::Vec3b point = image_.at<cv::Vec3b>(nowMousePosition_);
    drawTextBlue(point[0]);
    drawTextGreen(point[1]);
    drawTextRed(point[2]);
}



void ImageProfiler::drawTextBlue(const uchar blue)
{
    std::stringstream ss;
    ss << "B: "
        << std::setw(RGB_DEGIT)
        << static_cast<int>(blue);

    const cv::Point p(image_.cols + MARGIN_PROFILE_HEIGHT + PUT_TEXT_RGB_MARGIN_LEFT,
                      image_.rows + MARGIN_PROFILE_HEIGHT + 2 * fontHeight_);
    putText(ss.str(), p);
}



void ImageProfiler::drawTextGreen(const uchar green)
{
    std::stringstream ss;
    ss << "G: "
        << std::setw(RGB_DEGIT)
        << static_cast<int>(green);

    const cv::Point p(image_.cols + MARGIN_PROFILE_HEIGHT + PUT_TEXT_RGB_MARGIN_LEFT,
                      image_.rows + MARGIN_PROFILE_HEIGHT + 3 * fontHeight_);
    putText(ss.str(), p);
}



void ImageProfiler::drawTextRed(const uchar red)
{
    std::stringstream ss;
    ss << "R: "
       << std::setw(RGB_DEGIT)
       << static_cast<int>(red);

    const cv::Point p(image_.cols + MARGIN_PROFILE_HEIGHT + PUT_TEXT_RGB_MARGIN_LEFT,
                      image_.rows + MARGIN_PROFILE_HEIGHT + 4 * fontHeight_);
    putText(ss.str(), p);
}



void ImageProfiler::putText(const std::string &text, const cv::Point &point)
{
    cv::putText(show_, text, point, PUT_TEXT_FONT_FACE, PUT_TEXT_FONT_SIZE,
                PUT_TEXT_COLOR, PUT_TEXT_THICKNESS, CV_AA);
}

} // namespace show_profile_image