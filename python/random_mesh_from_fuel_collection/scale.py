import trimesh
import os


if __name__ == '__main__':
    from_dir = 'before_scale'
    to_dir = 'to_intake'
    files = os.listdir(from_dir)
    for f in files:
        target = os.path.join(to_dir, f)
        mesh = trimesh.load(os.path.join(from_dir, f))
        scaled_mesh = mesh.apply_scale(1000)
        trimesh.exchange.export.export_mesh(scaled_mesh, target, 'obj')

