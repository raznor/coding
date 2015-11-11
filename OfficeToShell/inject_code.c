#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int ZIP_HEADER_OFFSET = 0x40; //normaly something around 0x30 but 0x40 is a save pick

	FILE* fin = fopen(argv[1], "r"); 
	FILE* fin_code = fopen(argv[2], "r");
	FILE* fout = fopen(argv[3], "w");
	
	//size of fin
	fseek(fin,0,SEEK_END);
	int fsize = ftell(fin);
	rewind(fin);

	//size of fin_code
	fseek(fin_code,0,SEEK_END);
	int fcodesize = ftell(fin_code);
	rewind(fin_code);

	//buffer for fin fin_code and fout
	unsigned char* buffin= (unsigned char*) malloc(fsize);
	unsigned char* buffin_code= (unsigned char*) malloc(fcodesize);
	unsigned char* buffout= (unsigned char*) malloc(fsize);

	//read from fin and fin_code
	fread(buffin,1, fsize,fin);
	fread(buffin_code,1,fcodesize,fin_code);

	//write to buffout, combine fin and fin_code into one buffer
	int count = 0;
	for(;count < fsize;count++) {
		if(count < ZIP_HEADER_OFFSET | count > (ZIP_HEADER_OFFSET+fcodesize)) {
			buffout[count] = buffin[count];
		} else {
			buffout[count] = buffin_code[count-ZIP_HEADER_OFFSET];
		}
	}

	//write buffout to file fout
	fwrite(buffout, 1, fsize, fout);

	//close and flush
	fclose(fin);
	fclose(fin_code);
	fclose(fout);

	return 0;
}
