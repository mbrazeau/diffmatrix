#!/usr/bin/env python

import sys, os, getopt, multiprocessing, platform, shutil
from subprocess import call

def pullAll():
    os.system("git -C ../external/ncl pull")
    os.system("git -C ../external/wineditline pull")

def cloneLibs():
    if not os.path.exists("../external/ncl/"):
        os.system("git clone https://github.com/mtholder/ncl.git ../external/ncl/")
    if not os.path.exists("../external/wineditline"):
        os.system("git clone https://github.com/cdesjardins/wineditline.git ../external/wineditline")

def main(argv):
    cloneLibs()
    pullAll()
    os.system("cmake .")
    os.system("make")

if __name__ == "__main__":
    main(sys.argv[1:])
