#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, imggrayscale, imgequalize;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat hist, histnovo;
  int nbins = 128;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }
  
  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImg(histh, histw, CV_8UC1, Scalar(0,0,0));
  Mat histImgNova(histh, histw, CV_8UC1, Scalar(0,0,0));

  while(1){
    cap >> image;
    cvtColor(image, imggrayscale, CV_BGR2GRAY);
    equalizeHist(imggrayscale,imgequalize);

    calcHist(&imggrayscale, 1, 0, Mat(), hist, 1,
             &nbins, &histrange,
             uniform, acummulate);

    calcHist(&imgequalize, 1, 0, Mat(), histnovo, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(histnovo, histnovo, 0, histImgNova.rows, NORM_MINMAX, -1, Mat());
    
    histImg.setTo(Scalar(0));
    histImgNova.setTo(Scalar(0));
    
    for(int i=0; i<nbins; i++){
      line(histImg,
           Point(i, histh),
           Point(i, histh-cvRound(hist.at<float>(i))),
           Scalar(255, 255, 255), 1, 8, 0);
      line(histImgNova,
           Point(i, histh),
           Point(i, histh-cvRound(histnovo.at<float>(i))),
           Scalar(255, 255, 255), 1, 8, 0);
    }
    histImg.copyTo(imgequalize(Rect(0, 0       ,nbins, histh)));
    histImgNova.copyTo(imggrayscale(Rect(0, 0       ,nbins, histh)));
    imshow("normal", imggrayscale);
    imshow("equalize", imgequalize);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}