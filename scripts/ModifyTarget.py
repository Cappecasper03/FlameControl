import sys
import json

def modify_project_path(json_file, new_uproject_path):
    with open(json_file, "r", encoding="utf-8") as f:
        data = json.load(f)

    data["Project"] = new_uproject_path

    with open(json_file, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=4)


if __name__ == "__main__":
    destination_file = sys.argv[1]
    new_project_path = sys.argv[2]

    modify_project_path(destination_file, new_project_path)
