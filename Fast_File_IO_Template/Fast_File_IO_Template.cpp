#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono> 

#define DATATYPE_SIZE 2
#define BUFFER_SIZE_MB 1
#define NROWS 30000
#define NCOLS 72000

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	FILE* CinFile = fopen("D:/Robert/Input_Data/Elevation/CONUS_ELEV_3_ARCSECONDS.bil", "r");;
	FILE* CoutFile = fopen("D:/Robert/TEST/test_out.bil", "w+");
	if (CinFile == NULL|| CoutFile == NULL)
	{
		std::cout << "Error opening files." << std::endl;
		return -1;
	}

	// Set up File Streams
	// std::ifstream inFile("D:/Robert/Input_Data/Elevation/CONUS_ELEV_3_ARCSECONDS.bil", std::ios::in | std::ios::binary);
	// std::ofstream outFile("D:/Robert/TEST/test_out.bil", std::ios::out | std::ios::binary);

	// Buffer and File Size
	long long int file_bytes = ((long long int)NROWS) * ((long long int)NCOLS) * ((long long int)DATATYPE_SIZE); // bytes
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


		// On the last iteration, the read size changes to the 
		// number of bytes remaining in the file.
		if (i == num_iterations - 1)
			read_size = remainder_bytes;

		fread(buffer, (size_t)DATATYPE_SIZE, (size_t)read_size/ (size_t)DATATYPE_SIZE, CinFile);
		///////////////////////
		// do something here //
		///////////////////////
		fwrite(buffer, (size_t)DATATYPE_SIZE, (size_t)read_size / (size_t)DATATYPE_SIZE, CoutFile);
	}
	
	// Close File Pointers
	fclose(CinFile);
	fclose(CoutFile);

	// Benchmark
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
	std::cout << "Time Taken = " << duration.count() << " seconds." << std::endl;
}