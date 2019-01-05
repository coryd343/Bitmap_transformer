/*
* HW 2: Image Manipulation
* Author: Cory Davis
* Version: 4/13/17
*/

#include <stdio.h>
#define FILE1NAME "in1.bmp"
#define FILE2NAME "in2.bmp"
#define FILE3NAME "blend.bmp"
#define FILE4NAME "checker.bmp"
#define HEADERSIZE 54
#define IMGWIDTH 1224
#define IMGHEIGHT 408
#define PIXELBYTES 499392

void readFile(unsigned char header[HEADERSIZE], unsigned char pixels[PIXELBYTES], FILE *location);
unsigned char getAvg(unsigned char, unsigned char);
void blendPixels(unsigned char in1[PIXELBYTES], unsigned char in2[PIXELBYTES], unsigned char out[PIXELBYTES]);
void writeToFile(unsigned char header[HEADERSIZE], unsigned char pixels[PIXELBYTES], FILE *destination);
void checkerPixels(unsigned char in1[PIXELBYTES], unsigned char in2[PIXELBYTES], unsigned char out[PIXELBYTES]);

//Reads in two image files and creates two new files from them. The first blends both images, the second checkerboards them.
int main(void) {
    FILE *washington = fopen(FILE1NAME, "rb");
    FILE *lincoln = fopen(FILE2NAME, "rb");
    FILE *blend = fopen(FILE3NAME, "wb");
    FILE *checker = fopen(FILE4NAME, "wb");

    unsigned char img1Hdr[HEADERSIZE];
    unsigned char img1Pixels[PIXELBYTES];
    unsigned char img2Hdr[HEADERSIZE];
    unsigned char img2Pixels[PIXELBYTES];
    unsigned char blendArray[PIXELBYTES];
    unsigned char checkerArray[PIXELBYTES];
    
    //Read in image1
    readFile(img1Hdr, img1Pixels, washington);
    
    //Read in image2
    readFile(img2Hdr, img2Pixels, lincoln);
    
    //Blend operation
    blendPixels(img1Pixels, img2Pixels, blendArray);
    
    //Write blend to file
    writeToFile(img1Hdr, blendArray, blend);
    
    //Checker operation
    checkerPixels(img1Pixels, img2Pixels, checkerArray);
    
    //Write checker to file
    writeToFile(img1Hdr, checkerArray, checker);    
    
    fclose(washington);
    fclose(lincoln);
    fclose(blend);
    fclose(checker);
    return 0;
}

//Stores the header and pixel array of a bitmap file into the specified arrays.
void readFile(unsigned char header[HEADERSIZE], unsigned char pixels[PIXELBYTES], FILE *location) {
    fread(header, 1, HEADERSIZE, location);
    fread(pixels, 1, PIXELBYTES, location);
}

//Returns the average of the two specified values.
unsigned char getAvg(unsigned char first, unsigned char second) {
    unsigned char result = (unsigned char)(((unsigned int)first + (unsigned int)second) / 2);
    return result;
}

//Calls the average function on each pixel for the two given pixel arrays and stores them in the third.
void blendPixels(unsigned char in1[PIXELBYTES], unsigned char in2[PIXELBYTES], unsigned char out[PIXELBYTES]) {
    for(int i = 0; i < PIXELBYTES; i++) {
        out[i] = getAvg(in1[i], in2[i]);
    }
}

//Takes the given header and pixel array and writes them into the given file.
void writeToFile(unsigned char header[HEADERSIZE], unsigned char pixels[PIXELBYTES], FILE *destination) {
    fwrite(header, 1, HEADERSIZE, destination);
    fwrite(pixels, 1, PIXELBYTES, destination);
}

//Alternates writing pixels from each of the two input arrays in an 8x8 checkerboard pattern and stores them in the output array.
void checkerPixels(unsigned char in1[PIXELBYTES], unsigned char in2[PIXELBYTES], unsigned char out[PIXELBYTES]) {
    for(int i = 0; i < PIXELBYTES; i++) {
        if(i % (PIXELBYTES / 4) < (PIXELBYTES / 8)) { //If this is an 'A' row;
            if(i % 306 < 153) { //If this is an 'A' block;
                out[i] = in1[i];
            }
            else { //If this is a 'B' block;
                out[i] = in2[i];
            }
        }
        else { //If this is a 'B' row;
            if(i % 306 < 153) { //If this is a 'B' block;
                out[i] = in2[i];
            }
            else { //If this is an 'A' block;
                out[i] = in1[i];
            }
        }
    }
}