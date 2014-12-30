#! /bin/sh
mkdir -p icons/{48,128}
inkscape --export-png=icons/128/tombola.png icons/tombola-128x128.svg
inkscape --export-png=icons/48/tombola.png icons/tombola-48x48.svg
autoreconf -if
