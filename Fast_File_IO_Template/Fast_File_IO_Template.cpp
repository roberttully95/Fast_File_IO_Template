#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>

#define NUM_FILE_DATA 2160000000
#define DATATYPE_SIZE 2
#define BUFFER_SIZE_MB 1
#define INPUT_FILE "D:/Robert/Input_Data/Elevation/CONUS_ELEV_3_ARCSECONDS.bil"
#define OUTPUT_FILE "D:/Robert/TEST/test_out.bil"

int main()
{
	FILE* CinFile = fopen(INPUT_FILE, "rb");
	FILE* CoutFile = fopen(OUTPUT_FILE, "w+b");

	if (CinFile == NULL || CoutFile == NULL)
		return -1; // opening & creating files unsuccessful

	// Buffer and File Size
	long long int file_bytes = (long long int)NUM_FILE_DATA * (long long int)DATATYPE_SIZE;
	long long int buffer_bytes = ((long long int)1024) * ((long long int)1024) * BUFFER_SIZE_MB;

	// Calculate Remainder
	long long int remainder_bytes = file_bytes % buffer_bytes;
	if (remainder_bytes == 0)
		remainder_bytes = buffer_bytes;

	// Create Buffer
	char* buffer = new char[buffer_bytes];

	// Read all data and Write Data
	int num_blocks = (int)ceil((double)file_bytes / (double)buffer_bytes);
	long long int read_size = buffer_bytes;

	for (int i = 0; i < num_blocks; i++) {

		// On last iteration, read_size changes to the bytes remaining in the file.
		if (i == num_blocks - 1)
			read_size = remainder_bytes;

		long long int size_read = fread(buffer, (size_t)DATATYPE_SIZE, (size_t)read_size / (size_t)DATATYPE_SIZE, CinFile);
		if (size_read != read_size / DATATYPE_SIZE)
			return -2; // reading file unsuccessful
		
		///////////////////////
		// do something here //
		///////////////////////

		size_t desired_write_size = (size_t)(read_size / DATATYPE_SIZE); // can change based on application
		long long int size_written = fwrite(buffer, (size_t)DATATYPE_SIZE, desired_write_size, CoutFile);
		if (size_written != desired_write_size)
			return -3; // writing file unsuccessful
	}

	// Close File Pointers
	fclose(CinFile);
	fclose(CoutFile);
}