#!/usr/bin/env python3

import argparse
import os
import subprocess
import sys


def main(argv=sys.argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--models', help='Path to directory holding all the models')
    parser.add_argument('-w', '--worlds', help='Path to generated world files for each model with photoshoot')
    args = parser.parse_args(argv[1:])

    if not os.path.isdir(args.models):
        print(f'Models directory does not exist: {args.models}')
        exit(1)

    if not os.path.isdir(args.worlds):
        print(f'Worlds directory does not exist: {args.worlds}')
        exit(1)

    os.environ['IGN_GAZEBO_RESOURCE_PATH'] = args.models

    models = os.listdir(args.models)
    for model in models:
        model_path = os.path.join(args.models, model)
        thumbnail_path = os.path.join(model_path, 'thumbnails')

        if os.path.isdir(thumbnail_path):
            print(f'Thumbnails directory already exists: {thumbnail_path}')
            exit(1)
        os.mkdir(thumbnail_path)

        world_path = os.path.join(args.worlds, model + '.sdf')
        if not os.path.exists(world_path):
            print(f'World file does not exist: {world_path}')
            exit(1)

        subprocess.run(f'''
            export GZ_SIM_RESOURCE_PATH={os.path.abspath(args.models)}
            cd {os.path.abspath(thumbnail_path)}
            gz sim -s -r -v 4 --iterations 50 {os.path.abspath(world_path)}''',
            shell=True, check=True,
            executable='/bin/bash')
        print(f'Generated thumbnails for {model} at {thumbnail_path}')


if __name__ == '__main__':
    main(sys.argv)
