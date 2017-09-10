#!/bin/bash
usage() { echo  $s 1>&2; exit 1; }

while getopts "s:" o; do
    case "${o}" in
        s)
            s=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ "$s" -eq "0" ]; then
    exit 0
fi

img=win1.jpg

if [ "$s" -lt "0" ]; then
    img=win0.jpg
fi


DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
spd-say "YEE"
$DIR/image_encrypt -d $DIR/$img $DIR/winImg.jpg
xdg-open $DIR/winImg.jpg

