
Name : Patricia Figueroa
Class : CSCI 3453
Lab# : 1
Due Date : Sept. 25, 2017 
Read Me

Description of the program 
The goal of this assignment is to write a C++ program to implement multithreaded matrix multiplication using Pthreads. 
enter image description here

Specifications of the Program

Create a separate worker thread to compute each row of the result matrix, instead of a thread for each element.
Do not initialize the contents of the A and B matrices statically. The A and B matrices will be initialized by reading data from an input file (see notes below).
Be able to process multiple sets of input matrices by continuing to read data in the specified format (described below). If any other character than an integer including negative number is specified, output an error message and terminate the program with a non-zero return code.
Each set of data processed must be labeled to indicate which set of data is being output (e.g.,Matrix A,Matrix B, etc).
Maximum size of Matrices can be 10000x10000 
Source files

Name: main.cpp 
Main program. 
This is the driver program that calls functions 
to read data from an input file, use the data make a new file, 
and print an output.

Circumstances of programs

The program runs successfully. 
The program was developed and tested on CLion 2017.1.1 and on csegrid. It was compiled, run, and tested on macOS Sierra.

How to build and run the program

Uncompress the homework. The homework file is compressed. 
To uncompress it use the following commands 
% unzip [PatriciaFigLab01]
Now you should see a directory named homework with the files: 
main.cpp

Build the program.
Change to the directory that contains the file by: 
% cd [PatriciaFigLab01]

Compile the program by: 
% make

Delete the obj files, executables, and core dump by 
%./make clean
     1458  
 StackEdit Viewer
 Synchronize
Open, save, collaborate in the Cloud
Publish
Export to the web
Sharing
Share document links
 Import from disk
 Export to disk
 Import from URL
 Convert HTML to Markdown
 Settings
 About

 New document
 Delete document
 Manage documents

Hello!
Title
