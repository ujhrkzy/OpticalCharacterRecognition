#include <opencv2/opencv.hpp>
#include <opencv2/text.hpp>

int main(int argc, char** argv) {
    // 画像読み込み
    auto image = cv::imread("/Users/ujihirokazuya/Documents/abc.png");
    // グレースケール化
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_RGB2GRAY);
    // 文字認識クラスのインスタンス生成
    auto ocr = cv::text::OCRTesseract::create(
            "/usr/local/Cellar/tesseract/3.02.02_3/share/tessdata", "eng");

    std::string text;
    std::vector < cv::Rect > boxes;
    std::vector < std::string > words;
    std::vector<float> confidences;
    // 文字認識の実行
    ocr->run(gray, text, &boxes, &words, &confidences);

    // 結果出力
    printf("%s\n", text.c_str());
    // 文字のかたまりごとに出力
    printf(" 文字      | 位置       | 大きさ     | 信頼度\n");
    printf("-----------+------------+------------+----------\n");
    for (int i = 0; i < boxes.size(); i++) {

        printf("%-10s | (%3d, %3d) | (%3d, %3d) | %f\n", words[i].c_str(),
                boxes[i].x, boxes[i].y, boxes[i].width, boxes[i].height,
                confidences[i]);
    }
    return 0;
}
