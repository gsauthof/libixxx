#!/usr/bin/env python3

import subprocess
import sys

def get_fn_list():
    o = subprocess.check_output(r'''awk ' /\/\/|#/ { gsub("(//|#).*", "") }   /namespace/ {next} /}/ {skip=0} skip {next} /[(]/ { x=1 } x { s=s $0 } /{/ { skip=1} /[;{]/ { gsub(" +", " ", s); gsub("^ +", "", s); gsub(" +$", "", s); print s; s=""; x=0; next } ' ixxx/{ansi,posix,pthread,socket,linux}.hh | sed 's/(.*//' | awk '{print $NF}' | tr -d '*' | grep -v '^$' | sort -u''',
            shell=True, universal_newlines=True)
    return o.splitlines()

def mk_exceptions(fns):
    for fn in fns:
        print('Function {}_error::function() const {{ return Function::{}; }}'.format(fn, fn.upper()))
        print('const char* {0}_error::name() const {{ return "{0}"; }}'.format(fn))

def mk_exceptions_header(fns):
    print('enum class Function {')
    print(',\n'.join('    '+fn.upper() for fn in fns))
    print('};')
    for fn in fns:
      print('''class {}_error : public sys_error {{
    public:
        using sys_error::sys_error;
        Function function() const override;
        const char* name() const override;
}};'''.format(fn))

def main(argv):
    fns = get_fn_list()
    print('// Autogenerated by mk_boilerplate.py - begin')
    if '-h' in argv:
        mk_exceptions_header(fns)
    else:
        mk_exceptions(fns)
    print('// Autogenerated by mk_boilerplate.py - end')


if __name__ == '__main__':
    sys.exit(main(sys.argv))
