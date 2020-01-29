# Fast_File_IO_Template

### Description
Aims to improve the read/write time for large binary files. Does this by using a fixed size buffer to read and write larger chunks of data. C-based code is the fastest and is present in the 'C_Style_Reader' branch. Master branch contains the C++ ifstream / ofstream version. Both version reduce time required to read/write data greatly. C++ method is more secure, however, the C method is faster by a factor of ~ 2/3 times.

### Limits
1. Not tested in the case of a buffer larger than the input data.
2. Currently only set to work with 2-byte datatypes. Several small things can be changed to modify this.
3. C-style 
