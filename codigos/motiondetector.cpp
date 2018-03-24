#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat histR, histRnovo;
  int nbins = 64;
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
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgRnovo(histh, histw, CV_8UC3, Scalar(0,0,0));

  float diferenca;
  while(1){
    //primeira cena
    cap >> image;
    split (image, planes);
    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    //segunda cena
    cap >> image;
    split (image, planes);
    calcHist(&planes[0], 1, 0, Mat(), histRnovo, 1,
             &nbins, &histrange,
             uniform, acummulate);
    
    //compara as duas cenas
    diferenca = compareHist(histR, histRnovo, CV_COMP_CORREL);
    
    //cout << "\nDiferenca: " << diferenca << endl; usado para testar 
    //o limite na mudança de cena
    
    if(diferenca < 0.98){
      putText(image, "Alerta! Algo se moveu!", Point(width/2-200,height/2), 
    FONT_HERSHEY_TRIPLEX, 1, cvScalar(0,0,255), 1);
      cout << "\nAlerta! Algo se moveu!\n";
    }

    imshow("image", image);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}