#!/usr/bin/python3
import re
import argparse

def find_matches_in_file(file_path, pattern):
    regex = re.compile(pattern)
    matches_found = []

    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, 1):
                for match in regex.finditer(line):
                    matches_found.append({
                        "line": line_num,
                        "start": match.start(),
                        "end": match.end(),
                        "text": match.group()
                    })
    except FileNotFoundError:
        print("File not found. Please check the path.")
        
    return matches_found

parser = argparse.ArgumentParser()
parser.add_argument("--length", required=True, type=str)
parser.add_argument("--path", required=True, type=str)
args = parser.parse_args()

# --- Configuration ---
PATH = args.path
MY_REGEX = r"=[\(\)<>]{"+args.length+"}= 1\n"

results = find_matches_in_file(PATH, MY_REGEX)

print(len(results))


