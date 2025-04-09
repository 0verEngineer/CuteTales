import argparse
import xml.etree.ElementTree as ET
import os


def get_rate(coverage_element, element_name):
    try:

        branch_rate_value = coverage_element.get(element_name)
        return branch_rate_value
    except ET.ParseError as e:
        print(f"Error parsing XML file: {e}")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None


def print_rate_as_percentage(value, text):
    if value is not None:
        percentage = "{:.2f}".format(float(value) * 100)
        print(f"{text}: {percentage}")
    else:
        print("Element not found or attribute not present.")


def main():
    parser = argparse.ArgumentParser(description='Read branch-rate value from an XML file.')
    parser.add_argument('xml_file', help='Path to the XML file')
    args = parser.parse_args()

    if not os.path.isfile(args.xml_file):
        print(f"File not found: {args.xml_file}")
        return

    tree = ET.parse(args.xml_file)
    coverage_element = tree.getroot()

    print_rate_as_percentage(get_rate(coverage_element, 'branch-rate'), "Test branch-coverage")
    print_rate_as_percentage(get_rate(coverage_element, 'line-rate'), "Test line-coverage")


if __name__ == "__main__":
    main()
