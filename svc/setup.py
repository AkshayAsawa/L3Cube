from distutils.core import setup

files = ["README.md", "svc.py"]

setup(name = "svc",
	version = "1.0",
	description = "Simple-Version Control Program",
	packages = ['.'],
	package_data = {'package' : files },
	scripts = ["bin/svc"],
	long_description = """Usage: svc <filename> or svc <commit_number>""" 
) 
