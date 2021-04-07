#include "output_to_file.h"
#include "sparse_matrix.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <png.h>

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void write_png_file(char* file_name) {
  FILE *fp = fopen(file_name, "wb");
  if (!fp)
    printf("[write_png_file] File %s could not be opened for writing", file_name);

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    printf("[write_png_file] png_create_write_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    printf("[write_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during init_io");

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing header");

  png_set_IHDR(png_ptr, info_ptr, width, height,
   bit_depth, color_type, PNG_INTERLACE_NONE,
   PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing bytes");

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during end of write");

  png_write_end(png_ptr, NULL);

  for (y=0; y<height; y++)
    free(row_pointers[y]);
  free(row_pointers);

  fclose(fp);
}

void output_to_png(int* X, int* Y, int* V, Color*C, int sizeF, int rows, int columns,int cycle_number){
  	 
  bit_depth = 8;
  width = columns;  
  height = rows;
  color_type = PNG_COLOR_TYPE_RGB;

  number_of_passes = 7;
  row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height * 3);
  for (y=0; y<height; y++)
    row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width * 3);
//implementacja zmiany koloru komórki RGB
  for (y=0; y<height; y++) {
    png_byte* row = row_pointers[y];
    for (x=0; x<width; x++) {
      png_byte* ptr = &(row[x*3]);
      Color c = get_color(X,Y,V,C, y,x, sizeF);
      ptr[0] = c.R;
      ptr[1] = c.G;
      ptr[2] = c.B;
    }
  }
    char number[13];
    sprintf(number, "%d", cycle_number);
    char *dest = "../outputsPNG/outputPNG";
    char *exte = ".png";
    char *outp = (char*) malloc(1 + strlen(dest) + strlen(exte) + strlen(number));
    strcpy(outp,dest);
    strcat(outp,number);
    strcat(outp,exte);

    write_png_file(outp);
}


void output_to_txt(int* X, int* Y, int* V,int sizeF, int rows, int columns,int cycle_number){

    char number[13];
    sprintf(number, "%d", cycle_number);
    char *dest = "../outputsTXT/output";
    char *exte = ".txt";
    char *outp = (char*) malloc(1 + strlen(dest) + strlen(exte) + strlen(number));
    strcpy(outp,dest);
    strcat(outp,number);
    strcat(outp,exte);


    FILE *out = fopen(outp, "w");

    fprintf(out,"%d %d\n", rows,columns);
    for(int i=0;i<rows;i++){
        for(int j=0 ; j<columns ; j++){
            fprintf(out, "%d ", find_elem(X,Y,V,i,j,sizeF));
        }
        fprintf(out,"\n");
    }
    fclose(out);

}
