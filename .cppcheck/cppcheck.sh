#!/bin/sh

# before first commit, set the script as executable to git:
# git update-index --chmod=+x .cppcheck/cppcheck.sh

exec cppcheck \
  --enable=warning,style,performance \
  --inconclusive \
  --inline-suppr \
  --force \
  --check-level=exhaustive \
  --suppress=missingIncludeSystem \
  --suppressions-list=./.cppcheck/cppcheck.suppress \
  --error-exitcode=1 \
  .