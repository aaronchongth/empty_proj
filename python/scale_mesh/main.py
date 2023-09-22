import argparse
import os
import random
import shutil
import sys
import tempfile
import trimesh
from zipfile import ZipFile


def scale_mesh_and_save_to(mesh_path, scale, to_path, max_mesh_name_length):
    mesh = trimesh.load(mesh_path)
    try:
        scaled_mesh = mesh.apply_scale(scale)
    except:
        return None

    mesh_name = os.path.splitext(os.path.basename(mesh_path))[0]

    # Trim file name without extension
    trimmed_mesh_name = mesh_name[:(max_mesh_name_length - 4)]

    export_path = os.path.join(to_path, trimmed_mesh_name + '.obj')
    trimesh.exchange.export.export_mesh(scaled_mesh, export_path, 'obj')
    return export_path


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
        '-s', '--scale', type=int, default=1,
        help='Scales the meshes')
    parser.add_argument(
        '-l', '--max-mesh-name-length', type=int, default=50,
        help='Number of meshes to collect')
    args = parser.parse_args(argv[1:])

    if not os.path.isdir(args.input):
        print(f'Input directory does not exist: {args.input}')
        exit(1)

    if not os.path.isdir(args.output):
        print(f'Output directory does not exist: {args.output}')
        exit(1)

    meshes = os.listdir(args.input)
    for m in meshes:
        import_path = os.path.join(args.input, m)
        export_path = scale_mesh_and_save_to(import_path, args.scale, args.output, args.max_mesh_name_length)
        if export_path is not None:
            print(f'    Scaling {m} by {args.scale}, saving to {export_path}...')
        else:
            print(f'    Failed to scale {m}, skipping...')

if __name__ == '__main__':
    main(sys.argv)
