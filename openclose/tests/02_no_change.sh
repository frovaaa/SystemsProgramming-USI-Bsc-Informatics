#!/bin/bash
exec "$1" <<EOF
this text should be copied verbatim to the output, since
there are no open/close pairs in it.
EOF
