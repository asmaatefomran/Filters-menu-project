#include<bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
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


//--------------------------------------------------------------------------------------------
//the user should be able to choose the filter from a list of filters
int main() {
    loadImage();
    //the list of filters should be here
    saveImage();

    return 0;
}
