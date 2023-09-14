import argparse
import os
import random
import shutil
import sys
import tempfile
import trimesh
from zipfile import ZipFile


def pick_files_with_long_names(dir_path, min_name_length, extension=None):
    files = os.listdir(dir_path)
    targets = []
    if extension is not None:
        for file in files:
            if file.lower().endswith(extension):
                targets.append(file)
    else:
        for file in files:
            targets.append(file)

    result = []
    for t in targets:
        filename, ext = t.split('.', 1)
        if len(filename) >= min_name_length:
            result.append(t)
    return result


def extract_mesh_from_zip(path, to_path, min_name_length):
    directory, filename = os.path.split(path)
    filename, ext = filename.split('.', 1)
    allowed_filename = filename[:min_name_length]
    target_path = os.path.join(to_path, f'{allowed_filename}.obj')
    with ZipFile(path) as z:
        source = z.open('meshes/model.obj')
        target = open(target_path, 'wb')
        with source, target:
            shutil.copyfileobj(source, target)
    return target_path


def scale_mesh_and_save_to(mesh_path, scale, to_path):
    mesh = trimesh.load(mesh_path)
    scaled_mesh = mesh.apply_scale(scale)
    mesh_name = os.path.splitext(os.path.basename(mesh_path))[0]
    export_path = os.path.join(to_path, mesh_name + '.obj')
    trimesh.exchange.export.export_mesh(scaled_mesh, export_path, 'obj')


def main(argv=sys.argv):
    parser = argparse.ArgumentParser(
        description='This assumes that all the models were downloaded from Gazebo'
                    ' Fuel as zip files, located in the same directory. With the'
                    ' mesh files under the path MODEL/meshes/model.obj.'
    )
    parser.add_argument(
        '-i', '--input',
        help='Path to directory holding all downloaded fuel model zip files')
    parser.add_argument(
        '-o', '--output',
        help='Path to output directory where all the selected mesh files will be kept')
    parser.add_argument(
        '-l', '--max-mesh-name-length', type=int,
        help='Number of meshes to collect')
    parser.add_argument(
        '-s', '--scale', type=int, default=1,
        help='Scales the meshes')
    args = parser.parse_args(argv[1:])

    if not os.path.isdir(args.input):
        print(f'Input directory does not exist: {args.input}')
        exit(1)

    if not os.path.isdir(args.output):
        print(f'Output directory does not exist: {args.output}')
        exit(1)

    selected_zips = pick_files_with_long_names(args.input, args.max_mesh_name_length, '.zip')
    print(f'Picked {len(selected_zips)} files from {args.input} with names longer than {args.max_mesh_name_length}')
    print(selected_zips[0])

    to_perform_scaling = args.scale != 1

    unzip_dir = tempfile.mkdtemp() if to_perform_scaling else args.output
    selected_len = len(selected_zips)
    for i in range(selected_len):
        zip_file = selected_zips[i]
        zip_path = os.path.join(args.input, zip_file)
        extracted_path = extract_mesh_from_zip(zip_path, unzip_dir, args.max_mesh_name_length)
        print(f'{i}/{selected_len}: Extracting mesh from {zip_path} to {extracted_path}...')

        if to_perform_scaling:
            saved_path = scale_mesh_and_save_to(extracted_path, args.scale, args.output)
            print(f'    Scaling {extracted_path} by {args.scale}, saving to {saved_path}...')


if __name__ == '__main__':
    main(sys.argv)
