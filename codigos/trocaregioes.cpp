#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image, aux;
  Vec3b val;

  image = imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu biel.png" << endl;
  
  aux = imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!aux.data)
    cout << "nao abriu biel.png" << endl;
  namedWindow("janela",WINDOW_AUTOSIZE);

  //linhas e colunas
  int row, col, mrow, mcol;
  row = int(image.rows);
  col = int(image.cols);
  mrow = row/2;
  mcol = col/2;
  
  imshow("janela", image);  
  waitKey();
  
  // QUADRANTES:

  //    2     |    1
  // ------------------
  //    3     |    4

  //primeiro quadrante
  for(int i=0;i<mrow;i++){
    for(int j=mcol;j<col;j++){
      image.at<uchar>(i,j)=aux.at<uchar>(i+mrow,j-mcol);
    }
  }

  //terceiro quadrante
  for(int i=mrow;i<row;i++){
    for(int j=0;j<mcol;j++){
      image.at<uchar>(i,j)=aux.at<uchar>(i-mrow,j+mcol);
    }
  }

  //segundo quadrante
  for(int i=0;i<mrow;i++){
    for(int j=0;j<mcol;j++){
      image.at<uchar>(i,j)=aux.at<uchar>(i+mrow,j+mcol);
    }
  }

  //quarto quadrante
  for(int i=mrow;i<row;i++){
    for(int j=mcol;j<col;j++){
      image.at<uchar>(i,j)=aux.at<uchar>(i-mrow,j-mcol);
    }
  }
  
  imshow("janela", image);  
  waitKey();
  return 0;
}