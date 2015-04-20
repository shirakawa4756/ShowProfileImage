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
#ifndef SHOW_PROFILE_IMAGE_IMAGE_PROCESSING_COMMAND
#define SHOW_PROFILE_IMAGE_IMAGE_PROCESSING_COMMAND

#include <algorithm>
#include <map>
#include <string>


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace show_profile_image {
/*******************************************************************************************/// ***
/**
 * 既定のカーネルサイズ
 *
 *************************************************************************************************/
const int DEFAULT_KERNEL_SIZE = 3;

class ImageProcessingCommand
{
public:
    /**
     *
     */
    virtual ~ImageProcessingCommand() {}


    /**
     *
     */
    virtual void operator()(const cv::Mat &src, cv::Mat &dst) const = 0;


    /**
     *
     */
    virtual int kernelSize() const = 0;


    /**
     *
     */
    virtual void setKernelSize(int kernel) = 0;
};


typedef std::shared_ptr<ImageProcessingCommand> ImageProcessingCommandPtr;




/*******************************************************************************************/// ***
/**
 * ボックスフィルタを施します
 *
 *************************************************************************************************/
class BoxFilter : public ImageProcessingCommand
{
public:
    /**
     * コンストラクタ
     */
    BoxFilter() : kernelSize_(DEFAULT_KERNEL_SIZE, DEFAULT_KERNEL_SIZE) {}


    /**
     * デストラクタ
     */
    virtual ~BoxFilter() {}


    /**
     * ボックスフィルタを施します
     */
    void operator()(const cv::Mat &src, cv::Mat &dst) const
    {
        cv::blur(src, dst, kernelSize_);
    }


    /**
     * カーネルサイズを取得します
     */
    virtual int kernelSize() const
    {
        return kernelSize_.width;
    }


    /**
     * カーネルサイズを設定します
     */
    virtual void setKernelSize(int kernel)
    {
        kernelSize_.width  = kernel;
        kernelSize_.height = kernel;
    }


private:
    /**
     * カーネルサイズ
     */
    cv::Size kernelSize_;
};







/*******************************************************************************************/// ***
/**
* ボックスフィルタを施します
*
*************************************************************************************************/
class LaplacianFilter : public ImageProcessingCommand
{
public:
    /**
    * コンストラクタ
    */
    LaplacianFilter() : kernelSize_(DEFAULT_KERNEL_SIZE) {}


    /**
    * デストラクタ
    */
    virtual ~LaplacianFilter() {}


    /**
    * ボックスフィルタを施します
    */
    void operator()(const cv::Mat &src, cv::Mat &dst) const
    {
        cv::Mat tmp;
        cv::Laplacian(src, tmp, CV_32F, kernelSize_);

        double min = 0.0;
        double max = 0.0;
        cv::minMaxLoc(tmp, &min, &max);

        const double scale = std::max(std::abs(min), std::abs(max));
        cv::convertScaleAbs(tmp, dst, 255.0 / scale);
    }


    /**
    * カーネルサイズを取得します
    */
    virtual int kernelSize() const
    {
        return kernelSize_;
    }


    /**
    * カーネルサイズを設定します
    */
    virtual void setKernelSize(int kernel)
    {
        kernelSize_ = kernel;
    }


private:
    /**
    * カーネルサイズ
    */
    int kernelSize_;
};


} // namespace show_profile_image
#endif // #ifndef SHOW_PROFILE_IMAGE_IMAGE_PROCESSING_COMMAND