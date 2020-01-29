# Fast_File_IO_Template

### Description
Aims to improve the read/write time for large binary files. Does this by using a fixed size buffer to read and write larger chunks of data.  

### Limits
1. Uses ifstream / ofstream for file IO, rather than C-based read / fread.
2. Not tested in the case of a buffer larger than the input data.

### Applications
Uses when dealing with modifying / updating large datasets regularly. Reading single data elements at a time is not efficient. Example: For a 4 GB files of short ints, reading 1 MB at a time improves speed by a factor of ~ 10/15. This is getting close to the limit, as increasing the buffer size does not improve the time further.