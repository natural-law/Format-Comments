#!/usr/bin/python
import re
import os
import sys
import shutil

from argparse import ArgumentParser

def change_comment(param):
    # print('++++++++++++++++++++++')
    # print(param)
    # print('++++++++++++++++++++++\n')

    return param

def parse_header(src_file, dst_file):
    f = open(src_file)
    lines = f.readlines()
    f.close()

    seg_start = False
    seg_lines = []
    new_lines = []
    i = 0
    start_idx = -1
    for line in lines:
        line_str = line.strip()
        idx = i + 1
        if line_str.startswith('/**'):
            star_num = line_str.count('*')
            if star_num < 10:
                if seg_start:
                    print('Warning : last comment start at line %d is not end. (file : %s)' % (start_idx, src_file))
                seg_start = True
                start_idx = idx

        if seg_start:
            seg_lines.append(line)
            if line_str.endswith('*/'):
                seg_start = False
                if len(seg_lines) > 0:
                    replace_str = change_comment(''.join(seg_lines))
                    new_lines.append(replace_str)
                    seg_lines = []
        else:
            new_lines.append(line)

        i += 1

    dst_file_folder, ignore = os.path.split(dst_file)
    if not os.path.isdir(dst_file_folder):
        os.makedirs(dst_file_folder)

    f = open(dst_file, 'w')
    f.writelines(new_lines)
    f.close()

if __name__ == '__main__':

    parser = ArgumentParser(prog="parse_headers",
                            description='Parse header files.')
    parser.add_argument("-s", "--src-path", required=True, dest="src_path",
                        help="Specify the source path.")
    parser.add_argument("-d", "--dst-path", dest="dst_path",
                        help="Specify the output path.")

    (args, unknown) = parser.parse_known_args()

    source_path = os.path.expanduser(args.src_path)
    if not os.path.isabs(source_path):
        source_path = os.path.abspath(source_path)

    source_path = os.path.normpath(source_path)
    if not os.path.isdir(source_path):
        print('%s is not a valid folder path.' % source_path)
        sys.exit(1)

    if args.dst_path is None:
        dst_path = os.path.expanduser('~/OutputHeaders')
    else:
        dst_path = os.path.expanduser(args.dst_path)
        if not os.path.isabs(dst_path):
            dst_path = os.path.abspath(dst_path)

    dst_path = os.path.normpath(dst_path)
    if source_path != dst_path:
        if os.path.exists(dst_path):
            shutil.rmtree(dst_path)
        os.makedirs(dst_path)

    for root, dirs, files in os.walk(source_path):
        for f in files:
            name, ext = os.path.splitext(f)
            if ext == '.h':
                full_path = os.path.join(root, f)
                rel_path = os.path.relpath(full_path, source_path)
                dst_file_path = os.path.join(dst_path, rel_path)
                parse_header(full_path, dst_file_path)
