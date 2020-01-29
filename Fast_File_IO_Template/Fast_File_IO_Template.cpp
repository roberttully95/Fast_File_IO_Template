#include <iostream>
#include <sstream>
#include <fstream>

#define DATATYPE_SIZE 2
#define BUFFER_SIZE_MB 40

int main()
{
	// Set up File Streams
	std::ifstream inFile("D:/Robert/Input_Data/Elevation/CONUS_ELEV_3_ARCSECONDS.bil", std::ios::in | std::ios::binary);
	std::ofstream outFile("D:/Robert/TEST/test_out.bil", std::ios::out | std::ios::binary);

	// Buffer and File Size
	long long int file_data = ((long long int)30000) * ((long long int)72000); // not in bytes
	long long int file_bytes = file_data * ((long long int)DATATYPE_SIZE); // bytes
	long long int buffer_bytes = ((long long int)1024) * ((long long int)1024) * BUFFER_SIZE_MB;
	long long int buffer_data = buffer_bytes / ((long long int)DATATYPE_SIZE);

	// Calculate Remainder
	long long int remainder_data = file_data % buffer_data;
	long long int remainder_bytes = remainder_data * ((long long int)DATATYPE_SIZE);

	// Determine whether the final read of the data needs to be truncated.
	bool has_remainder = true;
	if (remainder_bytes == 0) {
		has_remainder = false;
	}

	// Create Buffer
	unsigned short* buffer = new unsigned short[buffer_data];

	// Determine the number of iterations that need to be made to traverse entire dataset.
	int num_iterations = (int)ceil((double)file_bytes / (double)buffer_bytes);
	for (int i = 0; i < num_iterations; i++) {

		// Remainder present, do truncated read
		if (i == num_iterations - 1 && has_remainder == true) {
			inFile.read(reinterpret_cast<char*>(buffer), (size_t)remainder_bytes);
			outFile.write(reinterpret_cast<char*>(buffer), (size_t)remainder_bytes);
			break;
		}

		// Read the entire buffer. This will always be the case until perhaps
		// the final iteration in which we require to perform a truncated read.
		inFile.read(reinterpret_cast<char*>(buffer), (size_t)buffer_bytes);
		outFile.write(reinterpret_cast<char*>(buffer), (size_t)buffer_bytes);
	}

	// Close File Pointers
	inFile.close();
	outFile.close();
}