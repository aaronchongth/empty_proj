#!/usr/bin/env python3

import argparse
import jinja2
import sys





def main(argv=sys.argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--mesh', help='Path to glb file')
    parser.add_argument('-o', '--output', help='Where to create the model')
    parser.add_argument('-s', '--sdf-version', default='1.9')
    parser.add_argument('-a', '--author', default='')
    parser.add_argument('-e', '--email', default='')
    parser.add_argument('-d', '--description', default='')
    args = parser.parse_args(argv[1:])


if __name__ == '__main__':
    main(sys.argv)