import os
import sys
import json
import subprocess


import sys
import os
from typing import Tuple
import json


def read_file_to_string(path: str) -> str:
    with open(path) as file:
        return file.read()


def read_template_files(path: str) -> Tuple[str, str, str]:

    normpath = os.path.normpath(path)
    dirname = os.path.split(normpath)[1]

    assert(dirname != '')

    c = read_file_to_string(f"{normpath}/{dirname}.ctp")
    h = read_file_to_string(f"{normpath}/{dirname}.htp")
    meta = json.loads(read_file_to_string(f"{normpath}/{dirname}.json"))

    return (c, h, meta)


def format_template_file(file: str) -> str:
    file = file.replace("{", "{{")
    file = file.replace("}", "}}")
    file = file.replace("{{{{", "{")
    file = file.replace("}}}}", "}")

    return file


def build_template(template_path, buildinfo):
    (c, h, meta) = read_template_files(template_path)
    c = format_template_file(c)
    h = format_template_file(h)

    target_dir = meta['TargetDir']
    os.makedirs(target_dir, exist_ok=True)
    file_name_template = meta['FileName']

    object_files = []
    subs = meta['Substitutions']
    for sub in subs:
        sub['TargetDir'] = target_dir

        filename = format_template_file(file_name_template).format(**sub)
        with open(f"{target_dir}/{filename}.c", "w") as file:
            file.write(c.format(**sub))
        with open(f"{target_dir}/{filename}.h", "w") as file:
            file.write(h.format(**sub))

        sourceinfo = {
            "name": filename,
            "path": f"{target_dir}/",
            "source": f"{filename}.c"
        }

        object_files.append(generate_object_file(sourceinfo, buildinfo))

    return object_files


def generate_object_file(sourceinfo, buildinfo):
    build_dir = os.path.normpath(buildinfo['BuildDir'])
    object_file = f"{build_dir}/{sourceinfo['name']}.o"

    # Assume that anything that _isn't_ main doesn't need linking.
    command = f"gcc -o {object_file} -c {os.path.normpath(sourceinfo['path'])}/{sourceinfo['source']} -I{os.path.normpath(sourceinfo['path'])} {buildinfo['Options']}"
    print(command)
    subprocess.run(command.split(' '))

    return object_file


def read_file_to_json(path):
    with open(path, "r") as file:
        return json.loads(file.read())


def main():

    buildinfo_path = ".buildinfo.json"
    if len(sys.argv) >= 2:
        buildinfo_path = sys.argv[1]

    buildinfo = read_file_to_json(buildinfo_path)
    build_dir = os.path.normpath(buildinfo['BuildDir'])
    os.makedirs(build_dir, exist_ok=True)

    object_files = []
    for template in buildinfo['Templates']:
        object_files.extend(build_template(template, buildinfo))

    main = None

    for sourceinfo in buildinfo['Sources']:
        if sourceinfo['name'] == "main":
            main = sourceinfo
            continue

        object_files.append(generate_object_file(sourceinfo, buildinfo))

    if (main != None):
        command = f"gcc -o {build_dir}/main {os.path.normpath(main['path'])}/{main['source']} {' '.join(object_files)} {buildinfo['Options']}"
        print(command)
        subprocess.run(command.split(' '))
        command = f"cp {build_dir}/main ."
        subprocess.run(command.split(' '))


if __name__ == "__main__":
    main()
