#!/usr/bin/env python3

import argparse
from jinja2 import Environment, FileSystemLoader
import os
import sys


def create_model_directory(model_dir: str) -> bool:
    if os.path.isdir(model_dir) or os.path.exists(model_dir):
        print(f'Model directory already exists: {model_dir}')
        return False

    os.mkdir(model_dir)
    return True


def create_model_config(model_name: str, model_dir: str, args: argparse.Namespace) -> bool:
    config_file_path = os.path.join(model_dir, 'model.config')
    if os.path.exists(config_file_path):
        print(f'Config file already exists: {config_file_path}')
        return False

    environment = Environment(loader=FileSystemLoader(args.templates))
    template = environment.get_template('model.config')
    config_content = template.render(
        name=model_name,
        sdf_version=args.sdf_version,
        author=args.author,
        email=args.email,
        description=args.description)

    with open(config_file_path, mode='w', encoding='utf-8') as message:
        message.write(config_content)

    print(f'{model_name}/model.config written')
    return True


def create_model_sdf(model_name: str, model_dir:str, args: argparse.Namespace) -> bool:
    sdf_file_path = os.path.join(model_dir, 'model.sdf')
    if os.path.exists(sdf_file_path):
        print(f'SDF file already exists: {sdf_file_path}')
        return False

    environment = Environment(loader=FileSystemLoader(args.templates))
    template = environment.get_template('model.sdf')
    sdf_content = template.render(
        name=model_name,
        sdf_version=args.sdf_version)

    with open(sdf_file_path, mode='w', encoding='utf-8') as message:
        message.write(sdf_content)

    print(f'{model_name}/model.sdf written')
    return True


def main(argv=sys.argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input', help='Path to directory holding all the models')
    parser.add_argument('-o', '--output', help='Where to create the model')
    parser.add_argument('-s', '--sdf-version', default='1.9')
    parser.add_argument('-t', '--templates', default='templates/')
    args = parser.parse_args(argv[1:])

    if not os.path.isdir(args.input):
        print(f'Input directory does not exist: {args.input}')
        exit(1)

    if not os.path.isdir(args.output):
        print(f'Output directory does not exist: {args.output}')
        exit(1)

    environment = Environment(loader=FileSystemLoader(args.templates))
    template = environment.get_template('model_photo_shoot.sdf')

    models = os.listdir(args.input)
    for model in models:
        sdf_content = template.render(
            model_name=model,
            sdf_version=args.sdf_version)

        model_photoshoot_world = model + '.sdf'
        output_path = os.path.join(args.output, model_photoshoot_world)
        with open(output_path, mode='w', encoding='utf-8') as message:
            message.write(sdf_content)
        print(f'Photoshoot world for {model} written')


if __name__ == '__main__':
    main(sys.argv)
