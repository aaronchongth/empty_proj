#!/usr/bin/env python3

import argparse
import os
import subprocess
import sys


def main(argv=sys.argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--models', help='Path to directory holding all the models')
    parser.add_argument('-j', '--jwt', help='JWT token')
    parser.add_argument('-o', '--owner', help='Owner of models')
    parser.add_argument('-u', '--url', default='https://fuel.gazebosim.org')
    args = parser.parse_args(argv[1:])

    if not os.path.isdir(args.models):
        print(f'Models directory does not exist: {args.models}')
        exit(1)

    models = os.listdir(args.models)
    for model in models:
        model_path = os.path.join(args.models, model)
        if not os.path.isdir(model_path):
            print(f'Model directory does not exist: {model_path}')
            exit(1)
        print(model_path)

        subprocess.run(f'''gz fuel upload --header 'authorization: Bearer {args.jwt}' -o {args.owner} --model {os.path.abspath(model_path)} --url {args.url}''', shell=True)
        print(f'Uploaded model: {model}')


if __name__ == '__main__':
    main(sys.argv)
