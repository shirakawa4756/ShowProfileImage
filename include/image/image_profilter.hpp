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
     * �v���t�@�C���̍������w�肵�܂�.
     *
     * �v���t�@�C�����ǂ̒��x�̍����ŕ\�����邩�w�肵�܂��D
     * ������΍����قǍׂ����\������܂����C�v���t�@�C���̈悪�傫���Ȃ�܂��D
     *
     * �������C����̍ŏ�����(MIN_PROFILE_HEIGHT) �ȉ��ɂ͎w��ł��܂���D
     *
     * @param profileHeight �v���t�@�C���̍��� [px]
     *
     */
    void setProfileHeight(int profileHeight)
    {
        profileHeight_ = std::max(MIN_PROFILE_HEIGHT, profileHeight);
    }


    /**
     * �摜�v���t�@�C����\������ Window �̕\����擾���܂�
     *
     * @return �\�薼
     */
    std::wstring caption() const
    {
        return caption_;
    }


    /**
     * �摜�v���t�@�C����\������ Window �̕\���ݒ肵�܂��D
     *
     * @param caption �\�薼
     */
    void setCaption(const std::wstring &caption)
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
     * �|�C���^�Ŏ����Ă���ꏊ�̏���\������ۂ̃t�H���g���̂��w�肵�܂�
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
     * �v���t�@�C���̕\�����I�������邽�߂̃L�[��ݒ肵�܂�
     */
    static const int QUIT_KEY_SHOW_PROFILE = 'q';


    /**
     * cv::imshow �Ŕ�������R�[���o�b�N�֐����`���܂�
     */
    static void cvImShowCallBackFunc(int event, int x, int y, int flags, void* userdata);


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
     * ���������̃v���t�@�C����`�ʂ��܂�
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
     * �ΐF
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
    std::wstring caption_;


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