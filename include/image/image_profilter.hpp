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
// * �����BSD���C�Z���X�@�a��
//
// Copyright (c) 2015, shirakawa4756@github.com
// All rights reserved.
//
// �\�[�X�R�[�h�`�����o�C�i���`�����A�ύX���邩���Ȃ������킸�A
// �ȉ��̏����𖞂����ꍇ�Ɍ���A�ĔЕz����юg�p��������܂��B
//
// 1. �\�[�X�R�[�h���ĔЕz����ꍇ�A��L�̒��쌠�\���A�{�����ꗗ�A
//    ����щ��L�Ɛӏ������܂߂邱�ƁB
//
// 2. �o�C�i���`���ōĔЕz����ꍇ�A�Еz���ɕt���̃h�L�������g����
//    �����ɁA��L�̒��쌠�\���A�{�����ꗗ�A����щ��L�Ɛӏ�������
//    �߂邱�ƁB
//
// �{�\�t�g�E�F�A�́A���쌠�҂���уR���g���r���[�^�[�ɂ���āu����̂܂܁v�񋟂���Ă���A
// �����َ����킸�A���ƓI�Ȏg�p�\���A����ѓ���̖ړI�ɑ΂���K�����Ɋւ���Öق̕ۏ�
// ���܂߁A�܂�����Ɍ��肳��Ȃ��A�����Ȃ�ۏ؂�����܂���B
// ���쌠�҂��R���g���r���[�^�[���A���R�̂�������킸�A���Q�����̌�����������킸�A
// ���ӔC�̍������_��ł��邩���i�ӔC�ł��邩�i�ߎ����̑��́j�s�@�s�ׂł��邩���킸�A
// ���ɂ��̂悤�ȑ��Q����������\����m�炳��Ă����Ƃ��Ă��A�{�\�t�g�E�F�A�̎g�p��
// ����Ĕ��������i��֕i�܂��͑�p�T�[�r�X�̒��B�A�g�p�̑r���A�f�[�^�̑r���A���v�̑r���A
// �Ɩ��̒��f���܂߁A�܂�����Ɍ��肳��Ȃ��j���ڑ��Q�A�Ԑڑ��Q�A�����I�ȑ��Q�A���ʑ��Q�A
// �����I���Q�A�܂��͌��ʑ��Q�ɂ��āA��ؐӔC�𕉂�Ȃ����̂Ƃ��܂��B
//
//
// �ǂݍ��񂾉摜�̏c���v���t�@�C����\�����܂��D
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
 * ���͂��ꂽ�摜�̃v���t�@�C����\�����܂�.
 *
 * ���͂��ꂽ�摜(8bit 3�`�����l��)�̏c���̃v���t�@�C���摜��\�����܂��D
 * �\�����ꂽ�E�C���h�E��̃}�E�X�|�C���^�Ŏ����ꂽ���W�𒆐S�ɏc�Ɖ��̃v���t�@�C����
 * �\�����܂��D
 *
 * ���͉摜�̑傫���ɂ͐����͂���܂��񂪁C���摜�̑傫���ɉ����C�c�����Ƀv���t�@�C����\������
 * �̈悪�ǉ�����邽�߁C���摜�̑傫�����傫������ƕ\�������E�C���h�E�̓��j�^�[�ȏ�ɂȂ�܂��D
 *
 * �\���������E�C���h�E�����(�I������)�Ƃ��́C'q' �L�[�������Ă��������D
 *
 *
 * �摜��\�����邽�߂̍ŏ��̃R�[�h�͈ȉ��̒ʂ�ł��D
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
     * �R���X�g���N�^
     */
    ImageProfiler();


    /**
     * �v���t�@�C����\�������ʂ�\�������܂�
     */
    void show();


    /**
     * �v���t�@�C���̍������s�N�Z�����Ŏ擾���܂��D
     *
     * @return �v���t�@�C���̍���
     */
    int profileHeight() const
    {
        return profileHeight_;
    }


    /**
     * �摜�v���t�@�C����\������ Window �̕\����擾���܂�
     *
     * @return �\�薼
     */
    std::string caption() const
    {
        return caption_;
    }


    /**
     * �摜�v���t�@�C����\������ Window �̕\���ݒ肵�܂��D
     *
     * @param caption �\�薼
     */
    void setCaption(const std::string &caption)
    {
        caption_ = caption;
    }


    /**
     * �v���t�@�C����\������Ώۂ̉摜��ݒ肵�܂�
     *
     * @param image ���摜
     *
     */
    void setImage(const cv::Mat &image)
    {
        image_ = image;
    }


private:
    /**
     * �ŏ��v���t�@�C���̍����������܂�
     */
    static const int MIN_PROFILE_HEIGHT = 64;


    /**
     * ����̃v���t�@�C���̍������`���܂�
     *
     * �\�߃v���t�@�C���������`���Ă������Ƃɂ��C
     * ���ʂɃv���t�@�C�����������w�肵�Ȃ��Ă��摜�v���t�@�C����������悤�ɂ��܂��D
     */
    static const int DEFAULT_PROFILE_HEIGHT = 128;


    /**
     * �v���t�@�C���̈�̃}�[�W����ݒ肵�܂�
     *
     * �v���t�@�C����\������̈�̏㉺�܂��́C���E�ɑ΂�
     * �Ԋu��݂��邱�Ƃɂ���čŏ��l�ƍő�l�����₷�����܂��D
     */
    static const int MARGIN_PROFILE_HEIGHT = 16;


    /**
     * ����̃v���t�@�C�����̐������`���܂�
     *
     * �\�߃v���t�@�C�����̐������`���Ă������Ƃɂ��C
     * ���ʂɃv���t�@�C�����̐������w�肵�Ȃ��Ă��摜�v���t�@�C����������悤�ɂ��܂��D
     */
    static const int DEFAULT_PROFILE_LINE_WIDTH = 1;


    /**
     * �v���t�@�C������`���ۂ̋ߖT�����`���܂�
     *
     * �v���t�@�C�����́Ccv::line �ɂ���ĕ`�ʂ��܂����C
     * ���̂Ƃ��̋ߖT��(�ǂ̂悤�ȘA���x�Ő���`����)���w�肵�܂�
     */
    static const int DEFAULT_PROFILE_LINE_NEIGHBORHOOD = 8;


    /**
     * �v���t�@�C����\������̈�̔w�i�F��ݒ肵�܂�
     */
    static const cv::Scalar PROFILE_LINE_BACKGROUND_COLOR;


    /**
     * �v���t�@�C�����̊e�F�������܂�
     *
     * �v���t�@�C�����́C�e�F(�ԁC�΁C��)�ɉ����āC
     * �F��ς��ĕ\�����܂����C���̐F���w�肵�܂��D
     *
     * ���̏����͎��̒ʂ�ł��D
     *   0: �F�̃v���t�@�C����
     *   1: �ΐF�̃v���t�@�C����
     *   2: �ԐF�̃v���t�@�C����
     */
    static const cv::Scalar PROFILE_LINE_STROKE_COLORS[3];



    /**
     * �|�C���^�Ŏ����Ă���ꏊ�̏���\������ۂ̃t�H���g���̂�ݒ肵�܂�
     */
    static const int PUT_TEXT_FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;


    /**
     * �\������t�H���g�̃T�C�Y��ݒ肵�܂�
     */
    static const double PUT_TEXT_FONT_SIZE;


    /**
     * �\������t�H���g������ݒ肵�܂�
     */
    static const int PUT_TEXT_THICKNESS = 1;


    /**
     * �\������t�H���g�̐F���`���܂�
     */
    static const cv::Scalar PUT_TEXT_COLOR;


    /**
     * �\������t�H���g�̍s�Ԃ�ݒ肵�܂�
     * 
     * �s�Ԃ��s�N�Z���P�ʂŎw�肵�܂�
     */
    static const int DEFAULT_LINE_HEIGHT = 30;


    /**
     * �}�E�X�ʒu�̌������w�肵�܂�
     *
     * 5���ɂȂ邱�Ƃ͖ő��ɂȂ��̂�4���Ɏw�肵�܂�.
     */
    static const int MOUSE_POSITION_DEGIT = 4;


    /**
     * �}�E�X�ʒu�̐F����\������ۂ̌�����ݒ肵�܂�
     *
     * 8bit �摜��ǂݍ��݂��Ƃ�O��Ƃ��Ă���̂� 3�������w�肵�܂�.
     */
    static const int RGB_DEGIT = 3;


    /**
     * �}�E�X�ʒu�̐F����\������ʒu�̍��}�[�W�����w�肵�܂�
     *
     */
    static const int PUT_TEXT_RGB_MARGIN_LEFT = 28;


    /**
     * �v���t�@�C���̕\�����I�������邽�߂̃L�[��ݒ肵�܂�
     */
    static const int QUIT_KEY_SHOW_PROFILE = 'q';


    /**
     * cv::imshow �Ŕ�������R�[���o�b�N�֐����`���܂�
     */
    static void cvImShowCallBackFunc(int event, int x, int y, int flags, void* userdata);


    /**
     * �v���t�@�C���E�C���h�E�̃}�E�X��L�[�{�[�h�̏�Ԃ��X�V��(�󂯎��)�܂�
     *
     * ���ۂɂ́CcvImShowCallBackFunc ����e�������ۓ�������܂�
     */
    void updateWindowStatus(int mouseEvent, int x, int y, int flags);


    /**
     * �v���t�@�C����\�����邽�߂̊�{�I�ȍ\���𐶐����܂�
     *
     * ���͉摜�̃v���t�@�C����\�����邽�߂Ɉȉ����쐬���܂��D
     *    1. ���摜
     *    2. �������̃v���t�@�C����\�����邽�߂̗̈�
     *    3. �c�����̃v���t�@�C����\�����邽�߂̗̈�
     *    4. �}�E�X�|�C���^���N�_�Ƃ��ďc���̐�������
     *    5. ���݈ʒu�Ɗe�F�̋P�x�l��\��
     *
     */
    void createShowProfileImage();


    /**
     * �v���t�@�C����\�����邽�߂̊�{�I�ȍ\���𐶐����܂�
     *
     * ���͉摜�̃v���t�@�C����\�����邽�߂Ɉȉ����쐬���܂��D
     *    1. ���摜
     *    2. �������̃v���t�@�C����\�����邽�߂̗̈�
     *    2. �c�����̃v���t�@�C����\�����邽�߂̗̈�
     *
     */
    void createProfileBaseImage();



    /**
     * ���������̃v���t�@�C����`�ʂ��܂�.
     */
    void drawProfileHorizontal();


    /**
     * ���������̃v���t�@�C������`���܂�.
     */
    void drawProfileLineHorizontal(const cv::Mat &col, const cv::Scalar color);


    /**
     * ���������̃v���t�@�C����\�����܂�.
     */
    void drawProfileVertical();


    /**
     * ���������̃v���t�@�C����`���܂�
     */
    void drawProfileLineVertical(const cv::Mat &col, const cv::Scalar color);


    /**
     * ���݂̃}�E�X�ʒu��ɏ\������`���܂�
     */
    void drawMousePositionCrossLine();


    /**
     * �e�L�X�g��`�ʂ��܂�.
     *
     * �}�E�X�ʒu�̍��W�Ƃ��̐F���������܂�
     */
    void drawText();


    /**
     * ���݂̃}�E�X�ʒu(�摜���W)��\�����܂�
     */
    void drawTextMousePosition();


    /**
     * �}�E�X�ʒu��RGB�l��\�����܂�
     */
    void drawTextRGB();


    /**
     * �F(B)�̒l��\�����܂�
     */
    void drawTextBlue(uchar blue);


    /**
     * �ΐF(R)�̒l��\�����܂�
     */
    void drawTextRed(uchar red);


    /**
     * �ԐF(R)�̒l��\�����܂�
     */
    void drawTextGreen(uchar green);

    

    /** 
     * �\���p�̉摜�Ɏw�肵���e�L�X�g��\�������܂�
     *
     * �v���t�@�C���\���p�摜�Ɏw�肵���ꏊ�ɕ������\�������܂��D
     *
     * @param text �\�������镶����
     * @param point �\��������ꏊ
     */
    void putText(const std::string &text, const cv::Point &point);


    /**
     * window �̕\�����������܂�
     */
    std::string caption_;


    /**
     * �v���t�@�C���̍����������܂�
     */
    int profileHeight_;


    /**
     * ���摜�������܂�.
     *
     * CV_8UC3 ��z�肵�Ă��܂��D
     */
    cv::Mat image_;


    /**
     * �v���t�@�C�����܂߂��\������摜�������܂�
     */
    cv::Mat show_;


    /**
     * �}�E�X�|�C���^�Ŏw�������ꂽ���݂̉摜���W��ێ����܂�
     *
     * cv::imshow �ŕ\�����ꂽ�摜�ɑ΂��}�E�X�|�C���^���ǂ̍��W���w���Ă���̂��ۑ����܂��D
     */
    cv::Point nowMousePosition_;


    /**
     * �v���t�@�C����`�ʂ�������̑�����\���܂�
     */
    int lineWidthProfile_;


    /**
     * �t�H���g�T�C�Y�������܂�
     */
    int fontSize_;


    /**
     * �t�H���g�̍����������܂�
     */
    int fontHeight_;


    ///////////////////////////////////////////////////////////////////////////////////////////////
    //
    //
    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q�ɂ����������֎~���܂�.
    //
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ImageProfiler(const ImageProfiler &rhs);
    ImageProfiler& operator=(const ImageProfiler &rhs);
};
} // namespace show_profile_image
#endif