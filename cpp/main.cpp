// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:Image_Filters.cpp
// Last Modification Date:	10/10/2023
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
using FunctionPtr = function<void()>;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char step[SIZE][SIZE];
unsigned char Cimage[SIZE][SIZE][RGB];
unsigned char Cimage2[SIZE][SIZE][RGB];

void cloadImage () {
    char cimageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> cimageFileName;

    // Add to it .bmp extension and load image
    strcat (cimageFileName, ".bmp");
    readRGBBMP(cimageFileName, Cimage);
}
void cloadImage2 () {
    char cimageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> cimageFileName;

    // Add to it .bmp extension and load image
    strcat (cimageFileName, ".bmp");
    readRGBBMP(cimageFileName, Cimage2);
}
void csaveImage () {
    char CimageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> CimageFileName;

    // Add to it .bmp extension and load image
    strcat (CimageFileName, ".bmp");
    writeRGBBMP(CimageFileName, Cimage);
}
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void loadImage2 () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name that you want to be merged: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}

void saveImage() {
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
//------------------------------------------------------------------------------------
//function to convert each pixel to black or white based on the average
void Black_White_Image() {

    int average, sum = 0, total = 256 * 256;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum += image[i][j];
        }
    }
    average = sum / total;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > average) {
                image[i][j] = 225;
            } else {
                image[i][j] = 0;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------
//function to invert each pixel of the chosen photo
void Invert_Image() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] == 0)image[i][j] = 225;
            else if (image[i][j] == 225)image[i][j] = 0;
            else image[i][j] = 255 - image[i][j];
        }
    }
}
////a function will create a new image, with every pixel equal the average gray level of the corresponding pixels in the images to merge.
void Merge_Image(){
    loadImage2();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            image[i][j]=(image[i][j]+image2[i][j])/2;

        }

    }
}
//----------------------------------------------------------------------------------------
//function to flip the photo horizontally or vertically
void Flip_Image() {
    int flip = SIZE - 1;
    char fpdir;
    cout << "please enter (h)orizontal or (v)ertical: ";
    cin >> fpdir;
    if (fpdir == 'h') {
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
    } else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 1; j >= 0; j--) {
                step[i][flip - j] = image[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = step[i][j];
            }
        }
    }
}
//-----------------------------------------------------------------------------------------
//function to rotate the chosen photo
void Rotate_Image() {
    unsigned char temp[SIZE][SIZE];
    int degree;
    cout << "Please enter the rotation degree: " << endl;
    cin >> degree;
    if (degree == 90) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[j][SIZE-1-i] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j];
            }
        }
    } else if (degree == 180) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[SIZE-1-i][SIZE-1-j] = image[i][j] ;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j];
            }
        }

    } else if (degree == 270) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[SIZE - 1 - j][i] = image[i][j] ;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j];
            }
        }

    }
}
//--------------------------------------------------------------------------------------------------
//function allows the user to make the image darker or lighter by 50%
void Darken_and_Lighten_Image(){
    int x;
    cout<<"enter 1 if you want image to be darker or 2 to make image lighter "<<endl;
    cin>>x;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j< SIZE; j++){
            if(x==1){

                image[i][j]-=image[i][j]/2;

            }
            else if(x==2)
            {
                image[i][j]+=(256-image[i][j])/2;
            }
        }
    }
}
//--------------------------------------------------------------------------------------
//function to detect the edges as pencil outline
void Detect_Image_Edges() {
    unsigned char copy[SIZE][SIZE];
    Black_White_Image();
    bool black=false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((image[i][j] != image[i][j - 1])||(image[i][j] != image[i][j + 1])||(image[i][j] != image[i - 1][j])||(image[i][j] != image[i + 1][j]))
                black = true;
            if(black)
                copy[i][j]=0;
            else
                copy[i][j]=255;

            black=false;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j]=copy[i][j];
        }
    }
}

//--------------------------------------------------------------------------------------------
//function to divide the photo into 4 quarters and chose one to zoom in to the original size
void Enlarge_Image() {
    int quarter;
    unsigned char temp[SIZE / 2][SIZE / 2];
    cout << "please enter the chosen quarter: ";
    cin >> quarter;
    if (quarter == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                temp[i][j] = image[i][j];
            }
        }
    } else if (quarter == 2) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                temp[i][j] = image[i][j + SIZE / 2];
            }
        }
    } else if (quarter == 3) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                temp[i][j] = image[i + SIZE / 2][j];
            }
        }
    } else if (quarter == 4) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                temp[i][j] = image[i + SIZE / 2][j + SIZE / 2];
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = temp[i / 2][j / 2];
        }
    }
}
//this function allows the user to shrink the image dimensions to 1/2, 1/3 or 1/4 the original dimensions.
void Shrink_Image(){
    for (int i = 0; i <SIZE; i++) {
        for (int j = 0; j<SIZE; j++) {
            image2[i][j]=255;

        }
    }
    int x;
    cout<<"if you want to  shrink to 1/2 enter 1 and for shrinking to 1/3 enter 2 and for shrinking to1/4 enter 3"<<endl;
    cin>>x;
    if(x==1)
    {
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image2[i/2][j/2]=image[i][j];

            }
        }
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image[i][j]=image2[i][j];

            }
        }
    }
    else if(x==2)
    {
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image2[i/3][j/3]=image[i][j];

            }
        }
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image[i][j]=image2[i][j];

            }
        }

    }
    else if(x==3)
    {
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image2[i/4][j/4]=image[i][j];

            }
        }
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image[i][j]=image2[i][j];

            }
        }


    }
}
//------------------------------------------------------------------------------------------------------
void Mirror_Image() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    char dir;
    cin >> dir;
    if(dir == 'l') {
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE/2 ; j++){
                image[i][SIZE-1-j]=image[i][j];
            }
        }
    }
    else if(dir == 'r') {
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE/2; j++){
                image[i][j]=image[i][SIZE-1-j];
            }
        }
    }
    else if(dir == 'u'){
        for(int i = 0; i < SIZE/2; i++){
            for(int j = 0; j < SIZE; j++){
                image[SIZE-1-i][j]=image[i][j];
            }
        }
    }
    else {
        for(int i = 0; i < SIZE/2; i++){
            for(int j = 0; j < SIZE; j++){
                image[i][j]=image[SIZE-1-i][j];
            }
        }
    }
}
//--------------------------------------------------------------------------------------------
void Shuffle_Image(){
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
//this filter produces a bury version of the image.
void Blur_Image(){
    for (int i = 1; i <SIZE-1; i++) {
        for (int j = 1; j<SIZE-1; j++) {
            image[i][j]=(image[i][j+1]+image[i][j-1]+image[i-1][j]+image[i+1][j]+image[i-1][j+1]+image[i-1][j-1]+image[i+1][j-1]+image[i+1][j+1])/8;

        }
    }

}
//---------------------------------------------------------------------------------------------
void Crop() {
    cout<<"please enter the point X and Y: ";
    int x,y,w,l;
    cin>>x>>y;
    cout<<"please enter the length and the width: ";
    cin>>l>>w;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(i>x && j>y && i<x+l && j<y+w)continue;
            else image[i][j]=255;
        }
    }

}

//--------------------------------------------------------------------------------------------
void Up_Skew(){
    double rad ;
    cout<< "Enter the degree : \n";
    cin >> rad ;
    rad = ( rad * 22 ) / ( 180 * 7 ) ;//here we convert to rad by multiplying *22/7*180 as tan don't take degrees
    double mov = tan(rad) * 256 ;
    int move =int(mov);
    double step = mov / SIZE ; // عدد الخطوات
    unsigned char img_in[SIZE][SIZE+(int)mov]  ;
    for ( int i = 0 ; i < SIZE ; i++ )
        for ( int j = 0 ; j < SIZE+move ; j++ )
            img_in[i][j] = 255 ;
    //make the whole photo white
    for ( int i = 0 ; i < SIZE ; i++ )
        for ( int j = 0 ; j < SIZE ; j++ )
            img_in[i][j] = 255 ;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_in[i][j+(int)mov] = image[i][j] ;
        }
        mov -= step ;
    }
    int ss= (move+256)/256;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE+move; j++ ){
            image[i][j/ss] = img_in[i][j] ;
        }
    }
}

void cshrink_image(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            for(int x=0;x<RGB;x++){
                Cimage2[i][j][x]=255;
            }}}
    int z;
    cout<<"if you want to  shrink to 1/2 enter 1 and for shrinking to 1/3 enter 2 and for shrinking to1/4 enter 3"<<endl;
    cin>>z;
    if(z==1)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int x=0;x<RGB;x++){
                    Cimage2[i/2][j/2][x]=Cimage[i][j][x];
                }


            }

        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int x=0;x<RGB;x++){
                    Cimage[i][j][x]=Cimage2[i][j][x];
                }


            }

        }

    }
    else if(z==2)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int x=0;x<RGB;x++){
                    Cimage2[i/3][j/3][x]=Cimage[i][j][x];
                }


            }

        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int x=0;x<RGB;x++){
                    Cimage[i][j][x]=Cimage2[i][j][x];
                }


            }

        }


    }
    else if(z==3)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int x=0;x<RGB;x++){
                    Cimage2[i/4][j/4][x]=Cimage[i][j][x];
                }


            }

        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++){
                for(int x=0;x<RGB;x++){
                    Cimage[i][j][x]=Cimage2[i][j][x];
                }


            }

        }



    }
}
void cBlur_Image(){
    for (int i = 1; i <SIZE-1; i++) {
        for (int j = 1; j<SIZE-1; j++) {
            for(int x=0;x<RGB;x++){
                Cimage[i][j][x]=(Cimage[i][j+1][x]+Cimage[i][j-1][x]+Cimage[i-1][j][x]+Cimage[i+1][j][x]+Cimage[i-1][j+1][x]+Cimage[i-1][j-1][x]+Cimage[i+1][j-1][x]+Cimage[i+1][j+1][x])/8;


            }

        }
    }

}
void cdarkandlight_image() {
    int z;
    cout << "enter 1 if you want image to be darker or 2 to make image lighter " << endl;
    cin >> z;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            for(int x=0;x<RGB;x++){
                if(z==1)
                {
                    Cimage[i][j][x]-=Cimage[i][j][x]/2;
                }
                else if (z == 2) {
                    Cimage[i][j][x] += (256 - Cimage[i][j][x]) / 2;


                }
            }


        }

    }



}
void merge_image_color(){
    cloadImage2 ();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            for(int x=0;x<RGB;x++){
                Cimage[i][j][x]=(Cimage[i][j][x]+Cimage2[i][j][x])/2;
            }


        }

    }
}
//the user should be able to choose the filter from a list of filters
int main() {
    while(true){
        cout << "Please choose a filter from the list below: " << endl;
        cout <<"l-load image\n"
             <<"1- Black & White Filter\n"
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
             <<"0- Exit\n";
        char choice;cin>>choice;
        if (choice=='0')break;
        else if (choice=='1')Black_White_Image();
        else if (choice=='2')Invert_Image();
        else if (choice=='3')Merge_Image();
        else if (choice=='4')Flip_Image();
        else if (choice=='5')Rotate_Image();
        else if (choice=='6')Darken_and_Lighten_Image();
        else if (choice=='7')Detect_Image_Edges();
        else if (choice=='8')Enlarge_Image();
        else if (choice=='9')Shrink_Image();
        else if (choice=='a')Mirror_Image();
        else if (choice=='b')Shuffle_Image();
        else if (choice=='c')Blur_Image();
        else if (choice=='d')Crop();
//        else if (choice=='e')Right_Skew();
        else if (choice=='f')Up_Skew();
        else if (choice=='s')saveImage();
        else if (choice=='l')loadImage();
    }
    return 0;
}







