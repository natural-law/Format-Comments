#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import os
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
import shutil
import string
import urllib
import urllib2
import json

KEYFROM = ''
API_KEY = ''

from argparse import ArgumentParser

stripRE = re.compile("(?P<begin>(^\s*\/\*\*?\s*)|(^\s*\*\/?\s*)|(^\s*))(?P<content>[^*/]*)(?P<end>\*+\/\s*$)?")
elementRE = re.compile("(?P<element>@(?P<name>[\w~]+)\s+(?P<content>[^@]*))")
paramRE = re.compile("(?P<element>@param\s+(?P<pname>\w+)\s+(?P<content>[^@]*))")
indentRE = re.compile("(?P<indent>^\s*)")
tagFilterRE = re.compile("((@lua)|(@js)|(@name)|(@static)|(@see)|(@since)|(@addtogroup)|(@\{)|(@\}))")


def getTranslate(txt):
    unicode(txt, 'utf-8')
    url = 'http://fanyi.youdao.com/openapi.do'
    data = {
        'keyfrom': KEYFROM,
        'key': API_KEY,
        'type': 'data',
        'doctype': 'json',
        'version': 1.1,
        'q': txt
    }
    data = urllib.urlencode(data)
    url = url+'?'+data
    req = urllib2.Request(url)
    response = urllib2.urlopen(req)
    result = json.loads(response.read())
    print(result)
    if result.get('translation'):
        translatedText = result['translation']
        return translatedText[0]
    else:
        return txt

# Translate
def translate(elements):
    for idx, element in enumerate(elements):
        if elements[idx] != "":
            elements[idx] = getTranslate(elements[idx])
    return elements

def reformat_comment(inputStr, target):
    lines = inputStr.split("\n")
    oneLine = False
    if string.join(lines).strip() == lines[0].strip():
        oneLine = True
    targetRE = re.compile("@~"+string.lower(target))
    result = inputStr
    elements = []
    currentElement = {"language": False, "begin": 0, "end": 0, "content": []}
    index = 0

    # Check target, exist then continue
    if re.search(targetRE, inputStr) != None:
        return inputStr

    indent = len(re.match(indentRE, lines[0]).group("indent"))

    for index, line in enumerate(lines):
        foundSub = False
        langTag = False

        stripped = re.match(stripRE, line)
        if stripped != None:
            content = stripped.group("content")
            # Filte tag
            if re.match(tagFilterRE, content) != None:
                currentElement["end"] = index;
                elements.append(currentElement)
                currentElement = {"language": langTag, "begin": index, "end": 0, "content": [""]}
                continue

            # Parameter
            element = re.match(paramRE, content)
            if element != None:
                foundSub = True
                currentElement["end"] = index;
                elements.append(currentElement)
                currentElement = {"language": langTag, "begin": index, "end": 0, "content": []}
                currentElement["content"].append(element.group("content"))
                langTag = False
            else:
                lineElements = re.findall(elementRE, line)
                for element in lineElements:
                    foundSub = True
                    # Language tag and not english
                    if element[1][0] == "~":
                        langTag = True
                        if element[1] != "~english":
                            continue

                    currentElement["end"] = index;
                    elements.append(currentElement)
                    currentElement = {"language": langTag, "begin": index, "end": 0, "content": []}
                    currentElement["content"].append(element[2])
                    langTag = False

            if not foundSub:
                currentElement["content"].append(content)

    currentElement["end"] = index-1
    elements.append(currentElement)

    tobeTranslate = []
    for element in elements:
        for line in element["content"]:
            tobeTranslate.append(line)

    translated = translate(tobeTranslate)

    index = 0
    lineNb = 0
    offset = 0
    for element in elements:
        content = element["content"]
        if len(content) == 0:
            continue

        if string.join(content).strip() == "":
            index = index+len(content)
            continue

        # Generate lines
        # Append
        begin = element["begin"]
        if element["language"] != True:
            if content[0].strip() == "":
                lines[begin+offset] = lines[begin+offset] + "@~english"
            else:
                lines[begin+offset] = string.replace(lines[begin+offset], content[0], "@~english "+content[0])

        if oneLine:
            strip = re.match(stripRE, lines[begin])
            lines[begin] = "{}{} @~{} {}{}".format(strip.group("begin"), 
                                                  strip.group("content"), 
                                                  target,
                                                  translated[index],
                                                  strip.group("end"))
            break

        # Replace with translated language
        for idx, line in enumerate(element["content"]):
            if idx == 0:
                element["content"][idx] = "{} * @~{} {}".format(" "*indent, target, translated[index])
            else:
                element["content"][idx] = "{} * {}".format(" "*indent, translated[index])
            index = index+1

        # Add translated language
        end = element["end"]
        for i in range(0, end-begin):
            lines.insert(end+offset, element["content"][i])
            offset = offset+1

    result = ""
    for line in lines:
        result = "{}{}\n".format(result, line)

    return result

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
        if line_str.startswith('/*'):
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
                    replace_str = reformat_comment(''.join(seg_lines), "chinese")
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
    parser.add_argument("-s", "--src-file", required=True, dest="src_file",
                        help="Specify the source file.")
    parser.add_argument("-d", "--dst-file", dest="dst_file",
                        help="Specify the output file.")

    (args, unknown) = parser.parse_known_args()

    src_file = os.path.expanduser(args.src_file)
    if not os.path.isabs(src_file):
        src_file = os.path.abspath(src_file)

    src_file = os.path.normpath(src_file)
    if not os.path.isfile(src_file):
        print('%s is not a valid folder path.' % src_file)
        sys.exit(1)

    if args.dst_file is None:
        dst_file = src_file
    else:
        dst_file = os.path.expanduser(args.dst_file)
        if not os.path.isabs(dst_file):
            dst_file = os.path.abspath(dst_file)

    dst_file = os.path.normpath(dst_file)
    parse_header(src_file, dst_file)

    # source_path = os.path.expanduser(args.src_path)
    # if not os.path.isabs(source_path):
    #     source_path = os.path.abspath(source_path)

    # source_path = os.path.normpath(source_path)
    # if not os.path.isdir(source_path):
    #     print('%s is not a valid folder path.' % source_path)
    #     sys.exit(1)

    # if args.dst_path is None:
    #     dst_path = os.path.expanduser('~/OutputHeaders')
    # else:
    #     dst_path = os.path.expanduser(args.dst_path)
    #     if not os.path.isabs(dst_path):
    #         dst_path = os.path.abspath(dst_path)

    # dst_path = os.path.normpath(dst_path)
    # if source_path != dst_path:
    #     if os.path.exists(dst_path):
    #         shutil.rmtree(dst_path)
    #     os.makedirs(dst_path)

    # for root, dirs, files in os.walk(source_path):
    #     for f in files:
    #         name, ext = os.path.splitext(f)
    #         if ext == '.h':
    #             full_path = os.path.join(root, f)
    #             rel_path = os.path.relpath(full_path, source_path)
    #             dst_file_path = os.path.join(dst_path, rel_path)
    #             parse_header(full_path, dst_file_path)

