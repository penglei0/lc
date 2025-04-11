"""Print all irreducible polynomials and Arithmetic Table of degree n over GF(2)"""
import argparse
import logging
import galois

# GF is short for Galois Field


def convert_to_cpp_array(arithmetic_table_file, output_cpp_file, degree):
    """convert arithmetic_table.txt into cpp code"""
    with open(arithmetic_table_file, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    cpp_arrays = {}
    current_table = None
    for line in lines:
        if "Multiplication Table" in line:
            current_table = f"Gf{degree}MultiplicationTable"
            cpp_arrays[current_table] = []
            logging.info("Found Multiplication Table")
            continue
        if "Division Table" in line:
            current_table = f"Gf{degree}DivisionTable"
            cpp_arrays[current_table] = []
            logging.info("Found Division Table")
            continue
        if current_table is None:
            logging.warning("LINE NOT FOUND: %s", line)
            logging.warning("No table found in the file.")
        if '|' not in line or line.startswith(("x * y |", "x / y |", "------|")):
            continue
        # Extract the row values after the first column
        row_values = line.split('|')[1].strip().split()
        cpp_arrays[current_table].extend(map(int, row_values))
    cpp_content = """/**
 * @file gf.cc
 * @author Lei Peng (plhitsz@outlook.com)
 * @brief 
 * @version 1.0
 * @date 2025-04-10
 * 
 * 
 */
#include <array>
#include <cstdint>

"""
    cpp_code = ""
    for table_name, cpp_array in cpp_arrays.items():
        cpp_array_str = ", ".join(map(str, cpp_array))
        cpp_content += f"std::array <uint8_t, {len(cpp_array)}> {table_name}"
        cpp_content += f"= {{{cpp_array_str}}};\n"
        cpp_content += "\n"

    cpp_content += "\n\n"
    with open(output_cpp_file, 'w', encoding='utf-8') as cpp_file:
        cpp_file.write(cpp_content)
    logging.info("C++ arrays saved to %s", output_cpp_file)
    return cpp_code


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    parser = argparse.ArgumentParser(
        description='Print all irreducible polynomials and Arithmetic Table of degree n over GF(2)')
    parser.add_argument(
        '--degree', type=int, default=4,
        help='The degree of the field GF(2^n). The degree must be a positive integer.')
    parser.add_argument(
        '--irreducible_poly', type=str, default=None,
        help='Optionally specify an irreducible polynomial of degree `n` over GF(2^n)'
        ' that defines the finite field arithmetic. The default is None')
    parser.add_argument(
        '--output', type=str, default='arithmetic_table.txt',
        help='Output file name for the arithmetic table. The default is arithmetic_table.txt')
    parser.add_argument(
        '--output_cpp', type=str, default='arithmetic_table.cc',
        help='Output file name for the arithmetic table. The default is arithmetic_table.cc')
    logging.info("finite field degree: %s",
                 parser.parse_args().degree)
    logging.info("irreducible_poly: %s", parser.parse_args().irreducible_poly)
    degree = parser.parse_args().degree
    all_irreducible_polys = galois.irreducible_polys(2, degree, reverse=True)
    for poly in all_irreducible_polys:
        logging.info("Irreducible polynomial of degree %d: %s",
                     degree, poly)
    GF = galois.GF(2**degree,
                   irreducible_poly=parser.parse_args().irreducible_poly)
    logging.info(GF.properties)
    multiplication_table = GF.arithmetic_table("*")
    logging.debug("Arithmetic Table for multiplication\n%s",
                  multiplication_table)
    division_table = GF.arithmetic_table("/")
    logging.info("Arithmetic Table for division\n%s", division_table)
    try:
        with open(parser.parse_args().output, 'w', encoding='utf-8') as stream:
            stream.write("Multiplication Table\n")
            stream.write(multiplication_table)
            stream.write("\nDivision Table\n")
            stream.write(division_table)
    except FileNotFoundError:
        logging.error("File not found: %s", parser.parse_args().output)
    convert_to_cpp_array(parser.parse_args().output,
                         parser.parse_args().output_cpp, degree)
