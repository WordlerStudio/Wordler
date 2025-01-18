cd "$(dirname "$0")" || exit

ShowError() {
    code="$1"
    msg="${*:2}"
    printf "\033[1;31m[ ERROR ]:\033[91m $msg\033[0m\n"
    exit "$code"
}

type convert >/dev/null 2>&1 || {
    ShowError "program requires ImageMagick tool installed, install it to continue"
}

for file in "others/"*.{png,jpg,webp}; do
    if [ -e "$file" ]; then
        BaseName=$(basename "$file" | cut -f 1 -d '.')

        magick "$file" "$PWD/${BaseName}.bmp"
        echo "$file ---> ${BaseName}.bmp"
    fi
done