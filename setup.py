from distutils.core import setup, Extension

module1 = Extension('vector',
                    sources = ['Vector.cpp', 'VectorExtension.cpp', 'VectorModule.cpp'])

setup (name = 'Vector',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
