#!/usr/bin/env python

# This script will clone and update all relevant repositories to the current release. 
# It also simplifies the entire process of building the application.
#
# To clone all the directories:
#   $ python getdeps.py


import  sys, os, getopt, multiprocessing, platform, shutil
from subprocess import call

def pullAll():
    os.system("git -C ./ncl pull")

def cloneAllDeps():
    os.system("git pull")
    os.system("git submodule update --init")

def buildExe():
    os.system("mkdir build")
    os.chdir("build")
    os.system("cmake ..")
    os.system("make")

def winBuild():
    os.system("cd ncl")
    os.system("mkdir build")
    os.system("cd build")
    os.system("cmake ..")
    os.system("cmake .. -G \"Visual Studio 16 2019\"")
    os.system("cmake --build .")
    os.system("cd ../..")
    os.system("mkdir build")
    os.system("cd build")
    os.system("cmake ..")
    os.system("cmake .. -G \"Visual Studio 16 2019\"")
    os.system("cmake --build .")

def main(argv):
    args = ["update"]
    if (len(argv) > 0):
        if (argv[0] == "update"):
            print("Updating libraries")
            pullAll()
        elif (argv[0] == "build"):
            print("Building diffmatrix")
            cloneAllDeps()
            if platform.system != "Windows":
                buildExe()
            else:
                winBuild()
        else:
            print("Unrecognised argument")
    else:
        print("Fetching all diffmatrix dependencies.")
        cloneAllDeps()

if __name__ == "__main__":
    main(sys.argv[1:])
