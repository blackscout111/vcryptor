################################################################################
README: vcryptor
################################################################################

DESCRIPTION
-----------
vcryptor is a simple program that allows you to encrypt or decrypt a file based
on a simple polyalphabetic key-word based cypher that has been extended to
include all 256 ASCII characters. This project contains both a python based GUI 
version and a command-line version of the program.

Note: you can also decrypt unencrypted files to effectively encrypt them.


INSTALL INSTRUCTIONS
--------------------
Installation is easy! Just perform the following commands in your terminal.

> make
> make clean

> python setup.py build    # These last two lines install the python module
> python setup.py install  # which allows you to use the cryption(...) function
                           # declared in vcryptor.h


USAGE INSTRUCTIONS
------------------

| Command-Line Usage |
Type the following command in your terminal

> ./vcryptor -h

Usage instructions for the command-line version will be displayed

| GUI Usage |
Type the following command in your terminal

> python pycryptor.py


BEWARE
------
This program will edit the binary data of a file. If the passwords for
encryption and decryption and/or the correct sequence is forgotten, the files
will be garbage. Back up your files.


LICENSE
-------
Feel free to use this code!  Please just reference me in the code that uses this
as "Bryan A. Clifford". Email me with any questions/comments/constructive
feedback at "blackscout111@gmail.com".

