from distutils.core import setup, Extension

module1 = Extension('vcryptor',
                    include_dirs = ['inc/'],
                    libraries = ['vcryptor'],
                    library_dirs = ['lib/'],
                    sources = ['src/vcryptormodule.c'])

setup (name = 'vcryptor',
       version = '1.0',
       description = 'Encrypts or decrypts files',
       author = 'Bryan A. Clifford',
       author_email = 'blackscout111@gmail.com',
       long_description = '''
vcryptor is a simple program that allows you to encrypt or decrypt a file based
on a simple polyalphabetic key-word based cypher that has been extended to
include all 256 ascii characters.

Note: you can also decrypt unencrypted files to effectively encrypt them.
''',
       ext_modules = [module1])
