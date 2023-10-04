#include<bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void BlackandWhiteImage() {

    int average , sum=0 , total = 256*256;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            sum += image[i][j];
        }
    }
    average = sum / total;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if(image[i][j]>average){
                image[i][j]= 225;
            }
            else{
                image[i][j]= 0;
            }
        }
    }
}

void FlipImage() {
    int flip= SIZE-1;
    string fpdir;
    cout<<"please enter horizontal or vertical: ";
    cin>>fpdir;
    if(fpdir=="horizontal") {
        for (int i = SIZE - 1; i >= 0; i--) {
            for (int j = 0; j < SIZE; j++) {
                step[flip - i][j] = image[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = step[i][j];
            }
        }
    }
    else{
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE-1; j >= 0; j--) {
                step[i][flip-j] = image[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = step[i][j];
            }
        }
    }
}


