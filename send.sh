#!/bin/bash
git add .
read -p "please kindly input ur commit message:" message
git commit -m "$message"
git push
