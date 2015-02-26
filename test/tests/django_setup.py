# skip-if: True
import sys

from django.core.management import execute_from_command_line

import os
import shutil
if os.path.exists("testsite"):
    shutil.rmtree("testsite")

sys.argv += ["startproject", "testsite"]
sys.exit(execute_from_command_line())
