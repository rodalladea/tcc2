import sys, os, re

#
# Parser helpers
#

def remove_comments(s):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return ""
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, s)


def getTokens(s):
    return re.findall(r'[a-z_A-Z0-9_]+|[^[a-z_A-Z0-9_ \n\r\t]', s)


def getParameter(pos, tokens):
    deep = 0
    p = []
    while True:
        if pos >= len(tokens):
            break
        if (tokens[pos] == ')' or tokens[pos] == ',') and deep == 0:
            if tokens[pos] == ')':
                pos = len(tokens)
            else:
                pos += 1
            break
        if tokens[pos] == '(':
            deep += 1
        if tokens[pos] == ')':
            deep -= 1
        p.append(tokens[pos])
        pos += 1
    return (' '.join(p), pos)


def getParameters(i, tokens):
    assert tokens[i] == '('
    i += 1

    params = []
    while True:
        if i >= len(tokens) or tokens[i] == ')':
            break

        (param, i) = getParameter(i, tokens)
        if len(param) > 0:
            params.append(param)
        else:
            assert False
            break

    if len(params) > 0 and params[0] == 'void':
        del params[0]

    return params

def postProcessParameters(fns):
    for fn in fns:
        fn['params_full'] = list(fn['params'])
        for i in range(len(fn['params'])):
            p = fn['params'][i]
            if p.find('(') != -1:
                p = re.sub(r'\* *([a-zA-Z0-9_]*) ?\)', '*)', p, 1)
                fn['params'][i] = p
                continue
            parts = re.findall(r'[a-z_A-Z0-9]+|\*', p)
            if len(parts) > 1:
                if parts[-1].find('*') == -1:
                    del parts[-1]
            fn['params'][i] = ' '.join(parts)

#
# Generator helpers
#

def outputToString(f):
    def wrapped(*args, **kwargs):
        from cStringIO import StringIO
        old_stdout = sys.stdout
        sys.stdout = str_stdout = StringIO()
        res = f(*args, **kwargs)
        assert res is None
        sys.stdout = old_stdout
        result = str_stdout.getvalue()
        result = re.sub(r'([^\n ]) [ ]+', r'\1 ', result)  # don't remove spaces at start of line
        result = re.sub(r' ,', ',', result)
        result = re.sub(r' \*', '*', result)
        result = re.sub(r'\( ', '(', result)
        result = re.sub(r' \)', ')', result)
        return result
    return wrapped

@outputToString
def generateEnums(fns, prefix='OPENCL_FN'):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    print 'enum %s_ID {' % prefix
    first = True
    for fn in fns:
        print '    %s_%s%s,' % (prefix, fn['name'], ' = 0' if first else '')
        first = False
    print '};'

@outputToString
def generateNames(fns, prefix='opencl_fn'):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    print 'const char* %s_names[] = {' % prefix
    for fn in fns:
        print '    "%s",' % (fn['name'])
    print '};'

@outputToString
def generatePtrs(fns, prefix='opencl_fn'):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    print 'void* %s_ptrs[] = {' % prefix
    for fn in fns:
        print '    &%s,' % (fn['name'])
    print '};'

@outputToString
def generateRemapOrigin(fns):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    for fn in fns:
        print '#define %s %s_' % (fn['name'], fn['name'])

@outputToString
def generateRemapDynamic(fns):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    for fn in fns:
        print '#undef %s' % (fn['name'])
        print '#define %s %s_pfn' % (fn['name'], fn['name'])

@outputToString
def generateParamsCfg(fns):
    for fn in fns:
        print '%s %d' % (fn['name'], len(fn['params']))

@outputToString
def generateFnDeclaration(fns):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    for fn in fns:
        print 'extern CL_RUNTIME_EXPORT %s %s (%s *%s)(%s);' % (' '.join(fn['modifiers']), ' '.join(fn['ret']), ' '.join(fn['calling']),
                                  fn['name'], ', '.join(fn['params'] if not fn.has_key('params_full') else fn['params_full']))

@outputToString
def generateFnDefinition(fns, lprefix='opencl_fn', uprefix='OPENCL_FN'):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    for fn in fns:
        print '%s%s (%s *%s)(%s) = %s%d<%s_%s, %s%s>::switch_fn;' % \
            ((' '.join(fn['modifiers'] + ' ') if len(fn['modifiers']) > 0 else ''),
             ' '.join(fn['ret']), ' '.join(fn['calling']), fn['name'], ', '.join(fn['params']), \
             lprefix, len(fn['params']), uprefix, fn['name'], ' '.join(fn['ret']), ('' if len(fn['params']) == 0 else ', ' + ', '.join(fn['params'])))

@outputToString
def generateTemplates(sz, lprefix, switch_name, calling_convention=''):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    for sz in range(sz):
        template_params = ['int ID', 'typename _R']
        types = []
        types_with_params = []
        params = []
        for i in range(1, sz + 1):
            template_params.append('typename _T%d' % i)
            types.append('_T%d' % i)
            types_with_params.append('_T%d p%d' % (i, i))
            params.append('p%d' % i)
        print 'template <%s>' % ', '.join(template_params)
        print 'struct %s%d' % (lprefix, sz)
        print '{'
        print '    typedef _R (%s *FN)(%s);' % (calling_convention, ', '.join(types))
        print '    static _R %s switch_fn(%s)' % (calling_convention, ', '.join(types_with_params))
        print '    { return ((FN)%s(ID))(%s); }' % (switch_name, ', '.join(params))
        print '};'
        print ''

@outputToString
def generateInlineWrappers(fns):
    print '// generated by %s' % os.path.basename(sys.argv[0])
    for fn in fns:
        print '#undef %s' % (fn['name'])
        print '#define %s %s_fn' % (fn['name'], fn['name'])
        params = []
        call_params = []
        for i in range(0, len(fn['params'])):
            t = fn['params'][i]
            if t.find('*)') >= 0:
                p = re.sub(r'\*\)', (' *p%d)' % i), t, 1)
                params.append(p)
            else:
                params.append('%s p%d' % (t, i))
            call_params.append('p%d' % (i))

        if len(fn['ret']) == 1 and fn['ret'][0] == 'void':
            print 'inline void %s(%s) { %s_pfn(%s); }' \
                    % (fn['name'], ', '.join(params), fn['name'], ', '.join(call_params))
        else:
            print 'inline %s %s(%s) { return %s_pfn(%s); }' \
                    % (' '.join(fn['ret']), fn['name'], ', '.join(params), fn['name'], ', '.join(call_params))

def ProcessTemplate(inputFile, ctx, noteLine='//\n// AUTOGENERATED, DO NOT EDIT\n//'):
    f = open(inputFile, "r")
    if noteLine:
        print noteLine
    for line in f:
        if line.startswith('@'):
            assert line[-1] == '\n'
            line = line[:-1]  # remove '\n'
            assert line[-1] == '@'
            name = line[1:-1]
            assert ctx.has_key(name), name
            line = ctx[name]
        print line,
    f.close()
