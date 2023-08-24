

import os
import subprocess

input_directory = "./../test_cases/"  # Replace with your input directory path
output_directory = "./../test_cases/"  # Replace with your output directory path
cpp_program = "./main"        # Replace with your C++ program's executable path
input_files = [filename for filename in os.listdir(input_directory) if filename.startswith("input")]

for input_filename in input_files:
    input_path = os.path.join(input_directory, input_filename)

    # Extract the index from the input filename (assuming it's in the format "inputX.txt")
    index = input_filename.replace("input", "").replace(".txt", "")

    output_filename = f"output{index}.txt"
    output_path = os.path.join(output_directory, output_filename)

    # Run the C++ program with input and output file arguments
    subprocess.run([cpp_program, input_path, output_path], stdout=subprocess.PIPE)

    print(f"Generated {output_filename}")
# In this version of the script, the subprocess.run command runs your C++ program with the input and output file paths as command-line arguments. Make sure your C++ program handles command-line arguments appropriately using argc and argv.





