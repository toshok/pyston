import subprocess
import sys
import tempfile


def bytes_from_file(filename, chunksize=8192):
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(chunksize)
            if chunk:
                for b in chunk:
                    yield b
            else:
                break


if __name__ == "__main__":
    input_file = sys.argv[1]
    output_file = sys.argv[2]

    symbol = "_binary_" + input_file.replace('.', '_')
    with tempfile.NamedTemporaryFile(suffix=".c", delete=False) as c_file:
        print c_file.name
        c_file.write("// generated file\n")
        c_file.write("#include <stdlib.h>\n")
        c_file.write("char {}_start[] = {{\n  ".format(symbol))
        bytes_out = 0
        for b in bytes_from_file(input_file):
            prefix = ""
            if bytes_out > 0:
                if bytes_out % 8 == 0:
                    prefix = ",\n  "
                else:
                    prefix = ", "
            c_file.write("{}0x{:02x}".format(prefix, ord(b)))
            bytes_out += 1
        c_file.write("};\n")
        c_file.write(
            "const void* {0}_end = &{0}_start[sizeof({0}_start)-1];\n".format(symbol))
        c_file.write("int {0}_size = sizeof({0}_start);\n".format(symbol))

    code = subprocess.call(["clang", "-c", "-o", output_file, c_file.name])
    if not code:
        sys.exit(0)
    sys.exit(1)
