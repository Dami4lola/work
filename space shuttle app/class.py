#!/usr/bin/python3

'''This script creates a class with the given name and creates a header file and a .cc file with the same name.
It also creates a constructor, copy constructor, a destructorm, and a print function. Delete what you don't need.
The script can be easily modified to create a class with a different set of functions.'''
import sys

if len(sys.argv)<2:
	print("no class name detected")
	exit()
	
cl = sys.argv[1]

caps = cl.upper()
title = cl[0].upper()+cl[1:]
print("Creating class: ",title)

result = '''
#ifndef {caps}_H
#define {caps}_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class {title} {{
		
	public:
		//constructor
		{title}();
		//copy constructor
		{title}({title}&);
		
		//destructor
		~{title}();
		
		void print();
	
	private:
	
}};
#endif'''.format(caps = caps,title = title)

f = open(title+".h",'w')
f.write(result)
f.close()

result = '''
#include "{title}.h"

{title}::{title}(){{


}}

{title}::{title}({title}& {cl}){{


}}


{title}::~{title}(){{


}}

void {title}::print(){{

}}'''.format(title = title, cl = cl)

f = open(title+".cc",'w')
f.write(result)
f.close()
