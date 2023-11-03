set windows-shell := ["powershell", "-NoLogo", "-Command"]

compile name *deps:
    clang -g -fsanitize="address,undefined" -Wall -Wextra -Wno-deprecated-declarations ./{{name}}.c {{deps}} -o {{name}}.exe
run name *deps: (compile name deps) (runc name)

runc name:
    ./{{name}}