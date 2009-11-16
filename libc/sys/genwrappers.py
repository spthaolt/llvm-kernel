#!/bin/python

import sys

type_map = {'o': 'void', 'h': 'i8', 'H': 'i16', 
            'i': 'i32', 'l': 'i64', 's': 'i8' }

# Convert type signature 'sig' to its' LLVM type
# If array_as_ptr is True, convert arrays to pointers
def parse_type(sig, array_as_ptr):
    ptr = type = array_cnt = ''
    for x in sig:
        if x in type_map:
            type = type_map[x]
        if x == 'p' or x == 's':
            ptr += '*'
        if x == 'a':
            if array_as_ptr:
                ptr += '*'
            else:
                array_cnt = sig[sig.find('a[')+2:sig.find(']')]
        if x == 'S':
            type = '%struct.' + sig[sig.find('=')+1:]
        if x == 'v':
            type = '...'
        if x == '=':
            break

    if len(ptr) > 0 and type == 'void':
        type = 'i8'
    if len(array_cnt) > 0:
        type = '[%s x %s]' % (array_cnt, type)
    return type + ptr

# Build a dictionary with the syscall name-number association
def get_syscall_no(syscall_header_name):
    dict = {}
    header_file = open(syscall_header_name, 'r')
    for line in header_file.readlines():
        elems = line.split()
        if len(elems) != 3 or not elems[1].startswith('SYS_'):
            continue
        dict[elems[1][4:]] = elems[2]
    header_file.close()
    return dict

# Generate the structure definitions
def generate_structs(struct_file_name, out):
    print >>out, '; Automatically generated structures'
    struct_file = open(struct_file_name, 'r')
    for line in struct_file:
        line = line.strip()
        if len(line) == 0 or line[0] == '#':
            continue
        (name, field_list) = line.split('(')
        fields_raw = field_list.rstrip(')').split(',')
        field_types = [parse_type(x, False) for x in fields_raw]
        print >>out, '%%struct.%s = type { %s }' % (name, ', '.join(field_types))
    struct_file.close()
    print >>out

# Generate the system call wrappers
def generate_wrappers(syscall_file_name, syscall_no, out):
    print >>out, '; Imported intrinsics'
    print >>out, 'declare void @llvm.va_start(i8*) nounwind'
    print >>out, 'declare void @llvm.va_end(i8*) nounwind'
    print >>out, 'declare i8* @llvm.syscall.i8ptr(i32, ...) nounwind'
    print >>out, 'declare i32 @llvm.syscall.i32(i32, ...) nounwind'
    print >>out, 'declare i64 @llvm.syscall.i64(i32, ...) nounwind'
    print >>out, 'declare void @llvm.syscall.void(i32, ...) nounwind\n'

    print >>out, '; Automatically generated syscalls'
    syscall_file = open(syscall_file_name, 'r')
    for line in syscall_file.readlines():
        line = line.strip()
        if len(line) == 0 or line[0] == '#':
            continue

        (name, alias_list, params) = line.split()
        aliases = alias_list.split(',')
        (ret_type_raw, param_list) = params.split('(')
        params_raw = param_list.rstrip(')').split(',') 

        # Build list of types and names
        param_decl_list = []
        param_types_list = []
        for i in range(len(params_raw)):
            if len(params_raw[i]) == 0:
                continue
            ss = parse_type(params_raw[i], True)
            param_types_list.append(ss)
            if ss != '...':
                ss += ' %p' + str(i)
            param_decl_list.append(ss)

        if name not in syscall_no:
            print >>out, '; Unknown syscall: %s\n' % name
            continue
        syscall_nr = syscall_no[name]
        ret_type = parse_type(ret_type_raw, True)
        param_decl = ', '.join(param_decl_list)
        res_assign = res_name = param_decl2 = ''
        if len(param_decl) > 0:
            param_decl2 = ', ' + param_decl
        if ret_type != 'void':
            res_assign = '%res = '
            res_name = ' %res' 

        # Write all the aliases
        fn_alias = ' = alias weak %s(%s)* @%s' % (ret_type, 
                ', '.join(param_types_list), name)
        for al in aliases:
            if al == '-':
                continue
            print >>out, '@' + al + fn_alias

        # Write the contents of the wrapper function
        print >>out, 'define %s @%s(%s) nounwind {' % (ret_type, name, param_decl)  
        if '...' in param_decl2:
            # Vararg, replace it with pointer to first parameter
            param_decl2 = param_decl2.replace('...', 'i8** %va')
            print >>out, '\t%va = alloca i8*'
            print >>out, '\t%va2 = bitcast i8** %va to i8*'
            print >>out, '\tcall void @llvm.va_start(i8* %va2)'
        print >>out, '\t%scall %s (i32, ...)* @llvm.syscall.%s(i32 %s%s)' % (res_assign, 
                ret_type, ret_type.replace('*', 'ptr'), syscall_nr, param_decl2)
        if len(param_decl_list) > 0 and param_decl_list[-1] == '...':
            print >>out, '\tcall void @llvm.va_end(i8* %va2)'
        print >>out, '\tret %s%s' % (ret_type, res_name)
        print >>out, '}\n'
    syscall_file.close()

if __name__ == '__main__':
    syscall_no = get_syscall_no('syscall.h')
    generate_structs('structs.list', sys.stdout)
    generate_wrappers('syscalls.list', syscall_no, sys.stdout)

