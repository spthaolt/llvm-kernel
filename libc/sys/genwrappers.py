#!/bin/python

# Convert type signature 'sig' to its' LLVM type
# If array_as_ptr is True, convert arrays to pointers
def parse_type(sig, array_as_ptr):
    ptr = type = array_cnt = ''
    for x in sig:
        if x == 'o':
            type = 'void'
        if x == 'h':
            type = 'i8'
        if x == 'p':
            ptr = '*'
        if x == 'H':
            type = 'i16'
        if x == 'i':
            type = 'i32'
        if x == 'l':
            type = 'i64'
        if x == 's':
            type = 'i8'
            ptr = '*'
        if x == 'a':
            if array_as_ptr:
                ptr = '*'
            else:
                array_cnt = sig[sig.find('a[')+2:sig.find(']')]
        if x == 'S':
            type = '%struct.' + sig[sig.find('=')+1:]
        if x == 'v':
            type = '...'
        if x == '=':
            break

    if ptr == '*' and type == 'void':
        type = 'i8'
    if array_cnt != '':
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
    return dict

# Generate the structure definitions
def generate_structs(struct_file_name):
    print '; Automatically generated structures'
    struct_file = open(struct_file_name, 'r')
    for line in struct_file:
        line = line.strip()
        if len(line) == 0 or line[0] == '#':
            continue
        (name, field_list) = line.split('(')
        fields_raw = field_list.rstrip(')').split(',')
        field_types = [parse_type(x, False) for x in fields_raw]
        print '%%struct.%s = type { %s }' % (name, ', '.join(field_types))
    print

# Generate the system call wrappers
def generate_wrappers(syscall_file_name, syscall_no):
    print '; Imported intrinsics'
    print 'declare void @llvm.va_start(i8*) nounwind'
    print 'declare void @llvm.va_end(i8*) nounwind'
    print 'declare i8* @llvm.syscall.i8ptr(i32, ...) nounwind'
    print 'declare i32 @llvm.syscall.i32(i32, ...) nounwind'
    print 'declare i64 @llvm.syscall.i64(i32, ...) nounwind'
    print 'declare void @llvm.syscall.void(i32, ...) nounwind\n'

    print '; Automatically generated syscalls'
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
        for i in range(len(params_raw)):
            if len(params_raw[i]) == 0:
                continue
            ss = parse_type(params_raw[i], True)
            if ss != '...':
                ss += ' %p' + str(i)
            param_decl_list.append(ss)

        if name not in syscall_no:
            print '; Unknown syscall: %s\n' % name
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

        # Write the contents of the wrapper function
        print 'define %s @%s(%s) nounwind {' % (ret_type, name, param_decl)  
        if '...' in param_decl2:
            # Vararg, replace it with pointer to first parameter
            param_decl2 = param_decl2.replace('...', 'i8** %va')
            print '\t%va = alloca i8*'
            print '\t%va2 = bitcast i8** %va to i8*'
            print '\tcall void @llvm.va_start(i8* %va2)'
        print '\t%scall %s (i32, ...)* @llvm.syscall.%s(i32 %s%s)' % (res_assign, 
                ret_type, ret_type.replace('*', 'ptr'), syscall_nr, param_decl2)
        if len(param_decl_list) > 0 and param_decl_list[-1] == '...':
            print '\tcall void @llvm.va_end(i8* %va2)'
        print '\tret %s%s' % (ret_type, res_name)
        print '}\n'

if __name__ == '__main__':
    syscall_no = get_syscall_no('syscall.h')
    generate_structs('structs.list')
    generate_wrappers('syscalls.list', syscall_no)

