#include <opencv2/aruco.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;
using namespace cv::aruco;

int main() {
    Mat markerImage;
    auto dic = getPredefinedDictionary(DICT_4X4_50);
    drawMarker(dic, 0, 200, markerImage);
    imwrite("marker.png", markerImage);

    Mat out(markerImage.size() * 2, markerImage.type(), Scalar(255));
    Rect roi(markerImage.size() / 2, markerImage.size());
    markerImage.copyTo(out(roi));
    imwrite("marker-padded.png", out);
}