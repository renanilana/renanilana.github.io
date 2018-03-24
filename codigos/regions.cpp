#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;
  unsigned char aux;
  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu biel.png" << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);
  
  int p1[2], p2[2],linhas, colunas;
  
  linhas = int(image.rows);
  cout << endl << "Linhas da imagem:" << linhas << endl;
  colunas = int(image.cols);
  cout << "Colunas da imagem:" << colunas << endl;
  
  cout << "Digite as coordenadas do ponto: " << endl;
  
  do{
    cout << "P1(x,y): ";
    for(int i = 0; i<2; i++)
      cin >> p1[i];
  }while(p1[0] < 0 || p1[0] >= linhas || p1[1] < 0 || p1[1] >= colunas);
  
  do{
    cout << "P2(x,y): ";
    for(int i = 0; i<2; i++)
      cin >> p2[i];
  }while(p2[0] < 0 || p2[0] >= linhas || p2[1] < 0 || p2[1] >= colunas);
  
  int minx, maxx, miny, maxy;
  if(p1[0] < p2[0]){
    minx = p1[0];
    maxx = p2[0];
  }
  else{
    minx = p2[0]; 
    maxx = p1[0];
  }
  if(p1[1] < p2[1]){
    miny = p1[1];
    maxy = p2[1];
  }
  else{
    miny = p2[1]; 
    maxy = p1[1];
  }

  for(int i=minx;i<=maxx;i++){
    for(int j=miny;j<=maxy;j++){
      aux = image.at<unsigned char>(i,j);
      image.at<unsigned char>(i,j) = 255 - aux;
    }
  }

  imshow("janela", image);  
  waitKey();
  return 0;
}