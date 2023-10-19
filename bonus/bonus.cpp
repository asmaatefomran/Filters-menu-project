// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:Image_Filters.cpp
// Last Modification Date:	19/10/2023
/*Team Members:
 * 1- Hadeer Abdelhady
 *    ID:20221229
 *    Email:hadearabdelhady10@gmail.com
 * 2- Aya Ehab Rmamdan :
 *    ID:20221209
 *    Email:ayaehap567@gmail.com
 * 3- Asmaa Atef
 *    ID:20221020
 *    Email:asmaatef6789@gmail.com
 *
 * */
#include<bits/stdc++.h>
#include "bmplib.cpp"
#include <functional>
using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char step[SIZE][SIZE][RGB];

void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
void loadImage2 () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name that you want to be merged: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);
}

void saveImage() {
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

void cBlack_White_Image() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int gray=0,change;
            for(int k = 0;k<3;k++){
                gray+=image[i][j][k];
            }
            gray/=3;
            if(gray>127)
                change=255;
            else change =0;
            for(int k=0;k<3;k++) {
                image[i][j][k]=change;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------
//function to invert each pixel of the chosen photo
void cInvert_Image() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k =0 ;k<RGB; k++){
                image[i][j][k] = 255 - image[i][j][k]
            }
        }
    }
}
//-----------------------------------------------------------------------------------------
void cMerge_image_color(){
    loadImage2 ();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            for(int k =0;k<RGB;k++){
                image[i][j][k]=(image[i][j][k]+image2[i][j][k])/2;
            }
        }
    }
}
//----------------------------------------------------------------------------------------
void cFlip_Image() {
    int flip = SIZE - 1;
    char fpdir;
    cout << "please enter (h)orizontal or (v)ertical: ";
    cin >> fpdir;
    if (fpdir == 'h') {
        for (int i = SIZE - 1; i >= 0; i--) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++){
                    step[flip - i][j][k] = image[i][j][k];
                }

            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++){
                    image[i][j][k] = step[i][j][k];
                }

            }
        }
    } else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 1; j >= 0; j--) {
                for(int k = 0; k < RGB; k++) {
                    step[i][flip - j][k] = image[i][j][k];
                }
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++) {
                    image[i][j][k] = step[i][j][k];
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------------------
//function to rotate the chosen photo
void cRotate_Image() {
    unsigned char temp[SIZE][SIZE][RGB];
    int degree;
    cout << "Please enter the rotation degree: " << endl;
    cin >> degree;
    if (degree == 90) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++) {
                    temp[j][SIZE - 1 - i][k] = image[i][j][k];
                }
            }
        }
    } else if (degree == 180) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++) {
                    temp[SIZE - 1 - i][SIZE - 1 - j][k] = image[i][j][k];
                }
            }
        }
    } else if (degree == 270) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++) {
                    temp[SIZE - 1 - j][i][k] = image[i][j][k];
                }
            }
        }

    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++) {
                image[i][j][k] = temp[i][j][k];
            }
        }
    }
}
//--------------------------------------------------------------------------------------------
void cDarken_and_Lighten_Image() {
    int z;
    cout << "enter 1 if you want image to be darker or 2 to make image lighter " << endl;
    cin >> z;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            for(int k = 0; k < RGB; k++){
                if(z==1)
                {
                    image[i][j][k]-=image[i][j][k]/2;
                }
                else if (z == 2) {
                    image[i][j][k] += (256 - image[i][j][k]) / 2;

                }
            }
        }
    }
}
//--------------------------------------------------------------------------------------
void cDetect_Image_Edges() {
    unsigned char copy[SIZE][SIZE][RGB];
    Black_White_Image();
    bool black=false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                if ((image[i][j][k] != image[i][j - 1][k]) || (image[i][j][k] != image[i][j + 1][k]) ||
                    (image[i][j][k] != image[i - 1][j][k]) || (image[i][j][k] != image[i + 1][j][k]))
                    black = true;
                if (black)
                    copy[i][j][k] = 0;
                else
                    copy[i][j][k] = 255;

                black = false;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = copy[i][j][k];
            }
        }
    }
}
//--------------------------------------------------------------------------------------------
//function to divide the photo into 4 quarters and chose one to zoom in to the original size
void cEnlarge_Image() {
    int quarter;
    unsigned char temp[SIZE / 2][SIZE / 2][RGP];
    cout << "please enter the chosen quarter: ";
    cin >> quarter;
    if (quarter == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for(int k = 0; k < RGB; k++) {
                    temp[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (quarter == 2) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for(int k = 0; k < RGB; k++) {
                    temp[i][j][k] = image[i][j + SIZE / 2][k];
                }
            }
        }
    } else if (quarter == 3) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for(int k = 0; k < RGB; k++) {
                    temp[i][j][k] = image[i + SIZE / 2][j][k];
                }
            }
        }
    } else if (quarter == 4) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for(int k = 0; k < RGB; k++) {
                    temp[i][j][k] = image[i + SIZE / 2][j + SIZE / 2][k];
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++) {
                image[i][j][k] = temp[i / 2][j / 2][k];
            }
        }
    }
}
//---------------------------------------------------------------------------------------
void cShrink_image(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            for(int k = 0; k < RGB; k++){
                image2[i][j][k]=255;
            }}}
    int z;
    cout<<"if you want to  shrink to 1/2 enter 1 and for shrinking to 1/3 enter 2 and for shrinking to1/4 enter 3"<<endl;
    cin>>z;
    if(z==1)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int k = 0; k < RGB; k++){
                    image2[i/2][j/2][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int k = 0; k < RGB; k++){
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if(z==2)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int k = 0; k < RGB; k++){
                    image2[i/3][j/3][k]=image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int k = 0; k < RGB; k++){
                    image[i][j][k]=image2[i][j][k];
                }
            }
        }
    }
    else if(z==3)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int k = 0; k < RGB; k++){
                    image2[i/4][j/4][k]=image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int k = 0; k < RGB; k++){
                    image[i][j][k]=image2[i][j][k];
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------
void cMirror_Image() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    char dir;
    cin >> dir;
    if(dir == 'l') {
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE/2 ; j++){
                for(int k = 0; k < 3; k++) {
                    image[i][SIZE - 1 - j][k] = image[i][j][k];
                }
            }
        }
    }
    else if(dir == 'r') {
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE/2; j++){
                for(int k = 0; k < 3; k++) {
                    image[i][j][k] = image[i][SIZE - 1 - j][k];
                }
            }
        }
    }
    else if(dir == 'u'){
        for(int i = 0; i < SIZE/2; i++){
            for(int j = 0; j < SIZE; j++){
                for(int k = 0; k < 3; k++) {
                    image[SIZE - 1 - i][j][k] = image[i][j][k];
                }
            }
        }
    }
    else {
        for(int i = 0; i < SIZE/2; i++){
            for(int j = 0; j < SIZE; j++){
                for(int k = 0; k < 3; k++) {
                    image[i][j][k] = image[SIZE - 1 - i][j][k];
                }
            }
        }
    }
}
//--------------------------------------------------------------------------------------------
void cShuffle_Image(){
    unsigned char temp[SIZE][SIZE];
    unsigned char aa[SIZE/2][SIZE/2];
    unsigned char bb[SIZE/2][SIZE/2];
    unsigned char cc[SIZE/2][SIZE/2];
    unsigned char dd[SIZE/2][SIZE/2];
    for (int i = 0 ; i < SIZE/2;i++){
        for (int j = 0 ; j < SIZE/2;j++){
            aa[i][j]=image[i][j];
            bb[i][j]=image[i][j+SIZE/2];
            cc[i][j]= image[i+SIZE/2][j];
            dd[i][j]=image[i+SIZE/2][j+SIZE/2];
        }
    }
    unordered_map<int,string>mp;
    cout <<"Please enter the order: ";int n=4;
    while(n--){
        int ord; cin>>ord;
        if (ord==1){
            mp.insert({1,"aa"});
        }
        else if (ord==2){
            mp.insert({2,"bb"});
        }
        else if (ord==3){
            mp.insert({3,"cc"});
        }
        else if (ord==4){
            mp.insert({4,"dd"});
        }
    }
    int count = 1 ;
    for (auto i :mp){
        if (count ==1){
            if (i.first==1){
                for (int i = 0 ; i < SIZE/2;i++){
                    for (int j = 0 ; j < SIZE/2;j++){
                        image [i][j]=dd[i][j];}}}
            if (i.first==2){
                for (int i = 0 ; i < SIZE/2;i++){
                    for (int j = 0 ; j < SIZE/2;j++){
                        image [i][j]=cc[i][j];}}}
            if (i.first==3){
                for (int i = 0 ; i < SIZE/2;i++){
                    for (int j = 0 ; j < SIZE/2;j++){
                        image [i][j]=bb[i][j];}}}
            if (i.first==4){
                for (int i = 0 ; i < SIZE/2;i++){
                    for (int j = 0 ; j < SIZE/2;j++){
                        image [i][j]=aa[i][j];}}}
        }
        else if (count ==2) {
            if (i.first == 1) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i][j+SIZE/2] = dd[i][j];}}}
            if (i.first == 2) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i][j+SIZE/2] = cc[i][j];}}}
            if (i.first == 3) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i][j+SIZE/2] = bb[i][j];}}}
            if (i.first == 4) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i][j+SIZE/2] = aa[i][j];}}}
        }
        else if (count ==3) {
            if (i.first == 1) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j] = dd[i][j];}}}
            if (i.first == 2) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j] = cc[i][j];}}}
            if (i.first == 3) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j] = bb[i][j];}}}
            if (i.first == 4) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j] = aa[i][j];}}}}
        else if (count ==4) {
            if (i.first == 1) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j+SIZE/2] = dd[i][j];}}}
            if (i.first == 2) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j+SIZE/2] = cc[i][j];}}}
            if (i.first == 3) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j+SIZE/2] = bb[i][j];}}}
            if (i.first == 4) {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i+SIZE/2][j+SIZE/2] = aa[i][j];}}}}
        count++;
    }
}
//-------------------------------------------------------------------------------------------------------------
void cBlur_Image(){
    for (int i = 1; i <SIZE-1; i++) {
        for (int j = 1; j<SIZE-1; j++) {
            for(int k =0 ; k < RGB; k++){
                image[i][j][k]=(image[i][j+1][k]+image[i][j-1][k]+image[i-1][j][k]+image[i+1][j][k]+image[i-1][j+1][k]+image[i-1][j-1][k]+image[i+1][j-1][k]+image[i+1][j+1][k])/8;
            }
        }
    }

}
//------------------------------------------------------------------------------------------------------------
void cCrop() {
    cout<<"please enter the point X and Y: ";
    int x,y,w,l;
    cin>>x>>y;
    cout<<"please enter the length and width: ";
    cin>>l>>w;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0; k<3; k++){
                if(i>x && j>y && i<x+l && j<y+w)continue;
                else image[i][j][k]=255;
            }
        }
    }

}/*
  //-----------------------------------------------------------------------------------------------------
void Skew_Horizontal(){
    // Define skew factor (adjust as needed)
    float skewFactorX = 0.2; // Adjust for the desired skew effect

    unsigned char image2[SIZE*2][SIZE*2];

// Perform horizontal skewing up
    for (int y = 0; y < 256; ++y) {
        for (int x = 0; x < 256; ++x) {
            int newX = x + skewFactorX * y; // Calculate new X position
            if (newX >= 0 && newX < 512) {
                image2[y][newX] = image[y][x]; // Interpolate pixel values
            }
        }
    }

}*/
//--------------------------------------------------------------------------------------------
//the user should be able to choose the filter from a list of filters
int main() {
    loadImage();
    while(true){
        cout << "Please choose a filter from the list below: " << endl;
        cout <<"1- Black & White Filter\n"
             <<"2- Invert Filter\n"
             <<"3- Merge Filter \n"
             <<"4- Flip Image\n"
             <<"5- Rotate Image \n"
             <<"6- Darken and Lighten Image\n"
             <<"7- Detect Image Edges \n"
             <<"8- Enlarge Image\n"
             <<"9- Shrink Image\n"
             <<"a- Mirror 1/2 Image\n"
             <<"b- Shuffle Image\n"
             <<"c- Blur Image\n"
             <<"d- Crop Image\n"
             <<"e- Skew Image Right \n"
             <<"f- Skew Image Up\n"
             <<"s- Save the image to a file\n"
             <<"0- Exit";
        char choice;cin>>choice;
        if (choice=='0')break;
        else if (choice=='1')cBlack_White_Image();
        else if (choice=='2')cInvert_Image();
        else if (choice=='3')cMerge_Image();
        else if (choice=='4')cFlip_Image();
        else if (choice=='5')cRotate_Image();
        else if (choice=='6')cDarken_and_Lighten_Image();
        else if (choice=='7')cDetect_Image_Edges();
        else if (choice=='8')cEnlarge_Image();
        else if (choice=='9')cShrink_Image();
        else if (choice=='a')cMirror_Image();
            //else if (choice=='b')cShuffle_Image();
        else if (choice=='c')cBlur_Image();
        else if (choice=='d')cCrop();
            //else if (choice=='e');
            //else if (choice=='f')cSkew_Horizontal();
        else if (choice=='s')saveImage();
    }
    return 0;
}
