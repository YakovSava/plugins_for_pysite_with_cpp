from os import listdir
from setuptools import Extension, setup

for file in listdir('c'):
	if file.endswith(('.c', '.cc', '.cpp', '.cxx')):
		setup(
			ext_modules=[Extension(
				name=file.split('.')[0],
				sources=[file],
				language='c++'
			)]			
		)