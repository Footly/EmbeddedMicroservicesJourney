import sys
sys.path.insert(0, './python_scripts')
from decode_json import DecodeJson
import argparse
from jinja2 import Template
import json

# Create a main argument parser that takes 3 parameters, the JSON input file, a GUID and the blueprint md
parser = argparse.ArgumentParser(description='Converts a JSON file to a header file')
parser.add_argument('input', type=str, help='The JSON file to read')
parser.add_argument('guid', type=str, help='The GUID of the swunit')
parser.add_argument('blueprint', type=str, help='The blueprint file to write to')
parser.add_argument('tag', type=str, help='The tag of the item')
args = parser.parse_args()

try:
    # Create a new instance of the DecodeJson class
    decoder = DecodeJson(args.input)

    # Search the item with the GUID
    item = decoder.search_by_id(args.guid)

    print(json.dumps(item, indent=4))

    #Check if within key "tags" there is the argument tag
    if args.tag not in item[0]["tags"]:
        raise Exception("The item is not a: " + args.tag)

    # Substitute all references in the item
    item = decoder.substitute_all_refs(item[0], args.input)

    # Read the blueprint template
    with open(args.blueprint, 'r') as file:
        blueprint_template = file.read()

    # Create a Jinja2 Template instance
    template = Template(blueprint_template)

    # Render the template with the item data
    rendered_content = template.render(item=item)

    # Dump the result into the stdout
    print(rendered_content)

except FileNotFoundError:
    print(f"Error: The file {args.input} was not found.")
except Exception as e:
    print(f"An error occurred: {e}")