#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <sstream>
#include <fstream>

#define NUM_FILE_DATA 2160000000
#define DATATYPE_SIZE 2
#define BUFFER_SIZE_MB 1

int main()
{
	FILE* CinFile = fopen("D:/Robert/Input_Data/Elevation/CONUS_ELEV_3_ARCSECONDS.bil", "rb");;
	FILE* CoutFile = fopen("D:/Robert/TEST/test_out.bil", "w+b");

	if (CinFile == NULL || CoutFile == NULL)
		return -1;

	// Buffer and File Size
	long long int file_bytes = (long long int)NUM_FILE_DATA * (long long int)DATATYPE_SIZE;
	long long int buffer_bytes = ((long long int)1024) * ((long long int)1024) * BUFFER_SIZE_MB;

	// Calculate Remainder
	long long int remainder_bytes = file_bytes % buffer_bytes;
	if (remainder_bytes == 0)
		remainder_bytes = buffer_bytes;

	// Create Buffer
	unsigned short* buffer = new unsigned short[buffer_bytes/DATATYPE_SIZE];

	// Read all data and Write Data
	int num_iterations = (int)ceil((double)file_bytes / (double)buffer_bytes);
	long long int read_size = buffer_bytes;

	for (int i = 0; i < num_iterations; i++) {

		// On last iteration, read_size changes to the bytes remaining in the file.
		if (i == num_iterations - 1)
			read_size = remainder_bytes;

		fread(buffer, (size_t)DATATYPE_SIZE, (size_t)read_size / (size_t)DATATYPE_SIZE, CinFile);
		///////////////////////
		// do something here //
		///////////////////////
		fwrite(buffer, (size_t)DATATYPE_SIZE, (size_t)read_size / (size_t)DATATYPE_SIZE, CoutFile);
	}

	// Close File Pointers
	fclose(CinFile);
	fclose(CoutFile);
}