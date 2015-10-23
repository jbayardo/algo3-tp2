find experiments -type f -iname '*.sts' -exec sh -c 'cat {} | python extend.py | sponge {}' \;
