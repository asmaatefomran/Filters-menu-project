#include<bits/stdc++.h>
#include "bmplib.cpp"
#include <functional>
using namespace std;
using FunctionPtr = function<void()>;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char step[SIZE][SIZE];

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

void BlackandWhiteImage() {

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

void FlipImage() {
    int flip = SIZE - 1;
    string fpdir;
    cout << "please enter horizontal or vertical: ";
    cin >> fpdir;
    if (fpdir == "horizontal") {
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

//function to rotate the chosen photo
void Rotate_Image() {
    unsigned char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = image[i][j];
        }
    }
    int degree;
    cout << "Please enter the rotation degree: " << endl;
    cin >> degree;
    if (degree == 90) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - 1 - j][i];
            }
        }
    } else if (degree == 180) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - 1 - j][i];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - 1 - j][i];
            }
        }
    } else if (degree == 270) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - 1 - j][i];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - 1 - j][i];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - 1 - j][i];
            }
        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = temp[SIZE - 1 - j][i];
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
//--------------------------------------------------------------------------------------------
void DetectImageEdges() {
    unsigned char copy[SIZE][SIZE];
    BlackandWhiteImage();
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
void ZOOM_CHOOSEN_QUARTER() {
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
void merge_image(){
    loadImage2();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            image[i][j]=(image[i][j]+image2[i][j])/2;

        }

    }
}
void darkandlight_image(){
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
void shrink_image(){
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
void blur_image(){
    for (int i = 1; i <SIZE; i++) {
        for (int j = 1; j<SIZE; j++) {
            image[i][j]=(image[i][j+1]+image[i][j-1]+image[i-1][j]+image[i+1][j])/4;

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
void Skew_horizontal(){
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

}
//--------------------------------------------------------------------------------------------
//the user should be able to choose the filter from a list of filters
int main() {
    loadImage();
    FunctionPtr functions[] = {BlackandWhiteImage,  Invert_Image,merge_image,FlipImage,darkandlight_image, Rotate_Image, DetectImageEdges, ZOOM_CHOOSEN_QUARTER,shrink_image,blur_image,Shuffle_Image};
    while(true){
        cout << "Please choose a filter from the list below: " << endl;
        cout <<"1- Black & White Filter\n"
               <<"2- Invert Filter\n"
               <<"3- Merge Filter \n"
               <<"4- Flip Image\n"
               <<"5- Darken and Lighten Image \n"
               <<"6- Rotate Image\n"
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
        else if (choice=='1')functions[0]();
        else if (choice=='2')functions[1]();
        else if (choice=='3')functions[2]();
        else if (choice=='4')functions[3]();
        else if (choice=='5')functions[4]();
        else if (choice=='6')functions[5]();
        else if (choice=='7')functions[6]();
        else if (choice=='8')functions[7]();
        else if (choice=='9')functions[8]();
        else if (choice=='a')functions[9]();
        else if (choice=='b')functions[10]();
        else if (choice=='c')functions[11]();
        else if (choice=='d')functions[12]();
        else if (choice=='e')functions[13]();
        else if (choice=='f')functions[14]();
        else if (choice=='s')saveImage();
    }

    return 0;
}
