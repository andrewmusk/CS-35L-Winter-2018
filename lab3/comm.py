#!/usr/bin/python                                                                                                                                                                  

"""   
This program is a version of the comm command. It works the same way but this version
allows you to have -u as an argument. This supports unsorted files as arguments
"""

import sys
from optparse import OptionParser

class compare:
    def __init__(self, file1,file2,options):
        self.options = options
        self.words1 = []
        self.words2 =[]
        self.common = []
        self.repeats1 = []
        self.repeats2 = []
        self.newlist = []
    
        if file1=="-":
            words1=sys.stdin.readlines()
            try:
                second = open (file2, 'r')
                self.words2 = second.readlines()
                second.close()
            except:
                parser.error("Invalid File")

        elif file2=="-":
            words2=sys.stdin.readlines()
            try:
                first = open (file1, 'r')
                self.words1 = first.readlines()
                first.close()
            except:
                parser.error("Invalid File")
        else:
            try:
                first = open (file1, 'r')
                second = open (file2, 'r')
                self.words1 = first.readlines()
                self.words2 = second.readlines()
                first.close()
                second.close()
            except:
                parser.error("Invalid File")
                    
    def newLines(self):
        count=0
        for i in self.words1:
            if not self.words1[count].endswith('\n'):
                self.words1[count]+='\n'
                count=count+1
    
        count=0
        for i in self.words2:
            if not self.words2[count].endswith('\n'):
                self.words2[count]+='\n'
            count=count+1

    def sort_comparison(self):
        self.newLines()
        for i in self.words1:
            if i in self.words2 and i not in self.common:
                self.common.append(i)
    
        counter=0
        for i in self.words1:
            if i in self.common and i not in self.repeats1:
                self.words1.remove(self.words1[counter])
                self.repeats1.append(i)
            counter=counter+1

        counter=0
        for i in self.words2:
            if i in self.common and i not in self.repeats2:
                self.words2.remove(self.words2[counter])
                self.repeats2.append(i)
            counter=counter+1

        self.All=sorted(self.words1+self.common+self.words2)
        for i in self.All:
            if i not in self.newlist:
                self.newlist.append(i)

        for i in self.newlist:
            if i in self.common and self.options.one==0 and self.options.two==0 and self.options.three==0:
                sys.stdout.write('\t'+'\t'+i)
            if i in self.common and self.options.one==1 and self.options.two==0 and self.options.three==0:
                sys.stdout.write('\t'+i)
            if i in self.common and self.options.one==0 and self.options.two==1 and self.options.three==0:
                sys.stdout.write('\t'+i)
            if i in self.common and self.options.one==1 and self.options.two==1 and self.options.three==0:
                sys.stdout.write(i)
            if i in self.words1 and self.options.one==0:
                sys.stdout.write(i)
            if i in self.words2 and self.options.one==0 and self.options.two==0:
                sys.stdout.write('\t'+i)
            if i in self.words2 and self.options.one==1 and self.options.two==0:
                    sys.stdout.write(i)
                        
    def unsort_comparison(self):
        self.newLines()
        for i in self.words1:
            if i in self.words2 and i not in self.common:
                self.common.append(i)

        for i in self.common:
            if not i in self.repeats1:
                self.words2.remove(i)
                self.repeats1.append(i)

        if self.options.one==0 and self.options.two==0 and self.options.three==0:
            for i in self.words1:
                if i in self.common and i not in self.repeats2:
                    sys.stdout.write('\t'+'\t'+i)
                    self.repeats2.append(i)
                else:
                    sys.stdout.write(i)
    
        if self.options.one==1 and self.options.two==0 and self.options.three==0:
            for i in self.words1:
                if i in self.common and i not in self.repeats2:
                    sys.stdout.write('\t'+i)
                    self.repeats2.append(i)
                            
        if self.options.one==0 and self.options.two==1 and self.options.three==0:
            for i in self.words1:
                if i in self.common and i not in self.repeats2:
                    sys.stdout.write('\t'+i)
                    self.repeats2.append(i)
                else:
                    sys.stdout.write(i)
        if self.options.one==0 and self.options.two==0 and self.options.three==1:
            for i in self.words1:
                if i in self.common and i not in self.repeats2:
                    self.repeats2.append(i)
                else:
                    sys.stdout.write(i)
    
        if self.options.one==1 and self.options.two==1 and self.options.three==0:
            for i in self.words1:
                if i in self.common and i not in self.repeats2:
                    self.repeats2.append(i)
                        
        if self.options.one==1 and self.options.two==0 and self.options.three==1:
            for i in self.words1:
                if i in self.common and i not in self.repeats2:
                    self.repeats2.append(i)
        if self.options.one==0 and self.options.two==1 and self.options.three==1:
            for i in self.words1:
                if i in self.common and i not in self.repeats2:
                    self.repeats2.append(i)
                else:
                    sys.stdout.write(i)
    
        if self.options.one==0 and self.options.two==0:
            for i in self.words2:
                sys.stdout.write('\t'+i)

        if self.options.one==1 and self.options.two==0:
            for i in self.words2:
                sys.stdout.write(i)



def main():
    version_msg = "%prog 2.0"
    usage_msg = "%prog [-123u] FILE1 FILE2"                                                                                                                                       
    parser = OptionParser(version=version_msg, usage=usage_msg)  
    parser.add_option("-u", action="store_true", dest="unsorted", default=0)
    parser.add_option("-1", action="store_true", dest="one", default=0)
    parser.add_option("-2", action="store_true", dest="two", default=0)
    parser.add_option("-3", action="store_true", dest="three", default=0)
    options, args = parser.parse_args(sys.argv[1:])
    
    if len(args)!=2:
        parser.error("Invalid number of operands")
    
    """Reading in files"""

    file1=args[0]
    file2=args[1]
    try:
        comparison = compare(file1,file2,options)
        sort = bool(options.unsorted)
        if not sort:
            comparison.sort_comparison()
        else:
            comparison.unsort_comparison()
    except IOError as e:
        errorno = e.errno
        strerror = e.strerror
        parser.error("I/O error({0}): {1}".format(errno, strerror))

                                                                                                                                                                                                                                                                                                                    
if __name__ == "__main__":
    main()
