#!/bin/python
# usage:
#     cat clAmdFft.h | $0
import sys, re;

from common import remove_comments, getTokens, getParameters, postProcessParameters


try:
    if len(sys.argv) > 1:
        f = open(sys.argv[1], "r")
    else:
        f = sys.stdin
except:
    sys.exit("ERROR. Can't open input file")

fns = []

while True:
    line = f.readline()
    if len(line) == 0:
        break
    assert isinstance(line, str)
    line = line.strip()
    if line.startswith('CLAMDFFTAPI'):
        line = re.sub(r'\n', r'', line)
        while True:
            nl = f.readline()
            nl = nl.strip()
            nl = re.sub(r'\n', r'', nl)
            if len(nl) == 0:
                break;
            line += ' ' + nl

        line = remove_comments(line)

        parts = getTokens(line)

        fn = {}
        modifiers = []
        ret = []
        calling = []

        i = 0
        while True:
            if parts[i] == "CLAMDFFTAPI":
                modifiers.append(parts[i])
            else:
                break
            i += 1
        while (i < len(parts)):
            if not parts[i] == '(':
                ret.append(parts[i])
            else:
                del ret[-1]
                i -= 1
                break
            i += 1

        fn['modifiers'] = []  # modifiers
        fn['ret'] = ret
        fn['calling'] = calling

        name = parts[i]; i += 1;
        fn['name'] = name
        print 'name=' + name

        params = getParameters(i, parts)

        if len(params) > 0 and params[0] == 'void':
            del params[0]

        fn['params'] = params
        # print 'params="'+','.join(params)+'"'

        fns.append(fn)

f.close()

print 'Found %d functions' % len(fns)

postProcessParameters(fns)

from pprint import pprint
pprint(fns)

from common import *

ctx = {}
ctx['CLAMDFFT_REMAP_ORIGIN'] = generateRemapOrigin(fns)
ctx['CLAMDFFT_REMAP_DYNAMIC'] = generateRemapDynamic(fns)
ctx['CLAMDFFT_FN_DECLARATIONS'] = generateFnDeclaration(fns)

sys.stdout = open('../../../include/opencv2/ocl/cl_runtime/clamdfft_runtime.hpp', 'w')
ProcessTemplate('template/clamdfft_runtime.hpp.in', ctx)

ctx['CL_FN_ENUMS'] = generateEnums(fns, 'OPENCLAMDFFT_FN')
ctx['CL_FN_NAMES'] = generateNames(fns, 'openclamdfft_fn')
ctx['CL_FN_DEFINITIONS'] = generateFnDefinition(fns, 'openclamdfft_fn', 'OPENCLAMDFFT_FN')
ctx['CL_FN_PTRS'] = generatePtrs(fns, 'openclamdfft_fn')
ctx['CL_FN_SWITCH'] = generateTemplates(23, 'openclamdfft_fn', 'openclamdfft_check_fn', '')

sys.stdout = open('../clamdfft_runtime.cpp', 'w')
ProcessTemplate('template/clamdfft_runtime.cpp.in', ctx)
