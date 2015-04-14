#include "stdafx.h"
#include "image/image_profilter.hpp"


#ifndef USE_PRE_COMPLIE_HEADER
#   include <iomanip>
#   include <string>
#   include <sstream>

#   include <opencv2/opencv.hpp>
#   include <opencv2/opencv_library_reader.hpp>
#endif



namespace show_profile_image {
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// ShowProfile Class
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
const cv::Scalar ImageProfiler::PROFILE_LINE_BACKGROUND_COLOR = cv::Scalar::all(64);

const cv::Scalar ImageProfiler::PROFILE_LINE_STROKE_COLORS[3] = {
    CV_RGB(16, 32, 255), CV_RGB(16, 255, 32), CV_RGB(255, 32, 16)
};


const double ImageProfiler::PUT_TEXT_FONT_SIZE = 0.65;

const cv::Scalar ImageProfiler::PUT_TEXT_COLOR = cv::Scalar::all(255);


ImageProfiler::ImageProfiler()
  : profileHeight_(DEFAULT_PROFILE_HEIGHT),
    lineWidthProfile_(DEFAULT_PROFILE_LINE_WIDTH),
    fontHeight_(DEFAULT_FONT_HEIGHT)
{
}



void ImageProfiler::cvImShowCallBackFunc(int, int x, int y, int, void* userdata)
{
    cv::Point *point = static_cast<cv::Point*>(userdata);
    point->x = x;
    point->y = y;
}



void ImageProfiler::show()
{
    const std::string windowName = cv::fromUtf16(caption_);

    cv::namedWindow(windowName);
    cv::setMouseCallback(windowName,
                         &ImageProfiler::cvImShowCallBackFunc, 
                         static_cast<void*>(&nowMousePosition_));

    int key = 0;
    while (tolower(key) != QUIT_KEY_SHOW_PROFILE) {
        createShowProfileImage();

        cv::imshow(windowName, show_);
        key = cv::waitKey(1000 / 60); // 60fps
    }
    cv::destroyWindow(windowName);
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

    cv::MatConstIterator_<cv::Vec3b> it = horizon.begin<cv::Vec3b>();
    cv::MatConstIterator_<cv::Vec3b> end = horizon.end<cv::Vec3b>() - 1;

    const double scale = profileHeight_ / static_cast<double>(UCHAR_MAX);
    const int    offset = image_.rows + MARGIN_PROFILE_HEIGHT;

    int col = 0;
    for (; it != end; ++it) {
        const cv::Vec3b &color     = *it;
        const cv::Vec3b &colorNext = *(it + 1);
        for (int c = 0; c < 3; ++c) {
            const int cs = static_cast<int>((UCHAR_MAX - color[c]) * scale + offset);
            const int ce = static_cast<int>((UCHAR_MAX - colorNext[c]) * scale + offset);

            cv::line(show_, 
                     cv::Point(col, cs),cv::Point(col + 1, ce),
                     PROFILE_LINE_STROKE_COLORS[c],
                     lineWidthProfile_,
                     8);
        }
        ++col;
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

    const cv::Point p(image_.cols + MARGIN_PROFILE_HEIGHT + PUT_TEXT_RGB_X_OFFSET,
        image_.rows + MARGIN_PROFILE_HEIGHT + 2 * fontHeight_);
    putText(ss.str(), p);
}



void ImageProfiler::drawTextGreen(const uchar green)
{
    std::stringstream ss;
    ss << "G: "
        << std::setw(RGB_DEGIT)
        << static_cast<int>(green);

    const cv::Point p(image_.cols + MARGIN_PROFILE_HEIGHT + PUT_TEXT_RGB_X_OFFSET,
        image_.rows + MARGIN_PROFILE_HEIGHT + 3 * fontHeight_);
    putText(ss.str(), p);
}



void ImageProfiler::drawTextRed(const uchar red)
{
    std::stringstream ss;
    ss << "R: "
       << std::setw(RGB_DEGIT)
       << static_cast<int>(red);

    const cv::Point p(image_.cols + MARGIN_PROFILE_HEIGHT + PUT_TEXT_RGB_X_OFFSET,
        image_.rows + MARGIN_PROFILE_HEIGHT + 4 * fontHeight_);
    putText(ss.str(), p);
}



void ImageProfiler::putText(const std::string &text, const cv::Point &point)
{
    cv::putText(show_, text, point, PUT_TEXT_FONT_FACE, PUT_TEXT_FONT_SIZE,
                PUT_TEXT_COLOR, PUT_TEXT_THICKNESS, CV_AA);
}


} // namespace show_profile_image