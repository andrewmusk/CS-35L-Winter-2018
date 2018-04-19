Some of the problems I ran into while editing the main.c program were as follows:


When I first looked at the program I was unsure of how to make the program multithreaded
or what I should be looking for. When looking through the program I realised that the main
thing I cauld change was the main method and not the helper functions. In the main method
there were a series of nested loops that were used to calculate the pixels and each
loop was independant of the other. Therefore, this is good to multithread because
no race conditions are needed.

I started but pulling out the computationally heavy code, the nested loops, from the 
main program and put them into their own method called process.
The first issue I ran into was that I 
forgot to make some of the necessary variables in the program global so
that all the programs could access them and so that later, the threads
could use them

Next I noticed that the program executed successfully but the printing was
completely wrong. I assumed this was because multiple threads were executing at once and
so the order of printing could get jumbled. To get around this I
created a global array that the pixels are added to, which is outputted 
after the execution for each pixel. 

Another problem that I ran into was that I was going to divide the width
of the image into the number of threads and then the threads would run through
their consecutive columns. However, i realised that I had issues when the width
didn't divide well. Instead I let the loop run from the thread number and let it
increment by the thread number, so that it would run on columns on a multiple of 
the thread number.

Another error I ran into was that I was casting the 64-bit pointers to 
32-bits and so I instead made the type long instead of int. 

When checking how much faster our program ran, I noticed that it was almost
exactly equal to the non-threaded program divided by the number of threads.
This is becuase most of the computationally heavy work was done in the loops
which was divided into threads. 
