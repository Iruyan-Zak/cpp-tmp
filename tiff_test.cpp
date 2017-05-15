#include <cstdlib>
#include <tiff.h>
#include <tiffio.h>

int main() {
    unsigned width=400;
    unsigned height=400; 
    char* buffer=(char *)malloc(width*height*sizeof(char)); 
    for(unsigned i=0;i<width;i++){ 
        for(unsigned j=0;j<height;j++){ 
            buffer[j*width+i]=i%255; 
        } 
    } 
    TIFF *image; image=TIFFOpen("test.tif","w"); //test.tifというファイルをつくる
    if(image==NULL){ 
        return 0; 
    } 
    //TIFFのタグ（補足情報）設定
    TIFFSetField(image,TIFFTAG_IMAGEWIDTH,width); //画像幅
    TIFFSetField(image,TIFFTAG_IMAGELENGTH,height); //画像の高さ
    TIFFSetField(image,TIFFTAG_BITSPERSAMPLE,8); //画像の深さは8bit
    TIFFSetField(image,TIFFTAG_SAMPLESPERPIXEL,1); //色の数は1
    TIFFSetField(image,TIFFTAG_COMPRESSION,COMPRESSION_NONE);//圧縮なし 
    TIFFSetField(image,TIFFTAG_PHOTOMETRIC,PHOTOMETRIC_MINISBLACK); //0が黒で、最大値が白
    TIFFSetField(image,TIFFTAG_FILLORDER,FILLORDER_MSB2LSB); 
    TIFFSetField(image,TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG); 
    TIFFSetField(image,TIFFTAG_ORIENTATION,ORIENTATION_TOPLEFT); 
    TIFFSetField(image,TIFFTAG_XRESOLUTION,72.0); //横方向解像度
    TIFFSetField(image,TIFFTAG_YRESOLUTION,72.0); //高さ方向解像度
    TIFFSetField(image,TIFFTAG_RESOLUTIONUNIT,RESUNIT_CENTIMETER);//解像度の単位はセンチメートル 
    TIFFSetField(image,TIFFTAG_SOFTWARE,"SoftName"); //ソフトの名前
    TIFFWriteEncodedStrip(image,0,buffer,width*height); 
    TIFFClose(image); 
    free(buffer);
}
