# HuffmanCode

**This Program is made for a Linux os**
**Compiling this on any other os will result in a segfault while decompressing**
**This is due to an error created while linking the files**


Use~
  To run the prgram pull the code from the git repo, and complie with the (make) command.
  Only .txt file using only the 256 asci values may be compressed
  
  To compress run ./compress <file.txt>
  this will create a new compressed file with extension .compress <file.txt>.compress
  
  To decompress rn ./decompress <file.txt.compress>
  this will create another new file with the extension .decompress 
  
About~
  This is a Huffman Compression program that uses a Linked List and Binary Tree
  
  The maximun compression possible from this program is about 74% the size of the original file
  However for small text files it is possible to have a compression 150% the size of the original file 
  >> small cases being less than 100 bytes
  



