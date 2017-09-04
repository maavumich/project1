#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo $DIRi
spd-say "YEE"
$DIR/image_encrypt -d $DIR/win0.jpg $DIR/win0d.jpg
xdg-open $DIR/win0d.jpg

