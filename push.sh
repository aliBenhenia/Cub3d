#!/bin/bash

# Check if commit message is provided as an argument
if [ -z "$1" ]; then
    echo "Please provide a commit message."
    exit 1
fi

# Perform git add, commit, and push
git add .
git commit -m "$1"
git push

echo "Changes committed and pushed to the repository."
