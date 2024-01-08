#!/bin/bash
exec "$1" <<EOF
The fibonacci() function is inefficient. (Very much so!)
EOF
