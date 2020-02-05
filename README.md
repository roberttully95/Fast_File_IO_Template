# Fast_File_IO_Template

### Description
Aims to improve the read/write time for large binary files. Does this by using a fixed size buffer to read and write larger chunks of data. Reading / writing performed using C-style fread / fwrite operations.   

### Limits
1. Not tested in the case of a buffer larger than the input data.
2. Currently only set to work with 2-byte datatypes. Several small things can be changed to modify this.
3. To view mapping files on global mapper, need to have an appropriate .hdr and .proj files created. These are not generated in this code.
